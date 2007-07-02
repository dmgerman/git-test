#!/bin/sh
# Copyright (c) 2007, Nanako Shiraishi

USAGE='[ | list | show | apply | clear]'

. git-sh-setup
require_work_tree

TMP="$GIT_DIR/.git-stash.$$"
trap 'rm -f "$TMP-*"' 0

ref_stash=refs/stash

no_changes () {
	git-diff-index --quiet --cached HEAD &&
	git-diff-files --quiet
}

clear_stash () {
	logfile="$GIT_DIR/logs/$ref_stash" &&
	mkdir -p "$(dirname "$logfile")" &&
	: >"$logfile"
}

save_stash () {
	if no_changes
	then
		echo >&2 'No local changes to save'
		exit 0
	fi
	test -f "$GIT_DIR/logs/$ref_stash" ||
		clear_stash || die "Cannot initialize stash"

	# state of the base commit
	if b_commit=$(git-rev-parse --verify HEAD)
	then
		head=$(git-log --abbrev-commit --pretty=oneline -n 1 HEAD)
	else
		die "You do not have the initial commit yet"
	fi

	if branch=$(git-symbolic-ref -q HEAD)
	then
		branch=${branch#refs/heads/}
	else
		branch='(no branch)'
	fi
	msg=$(printf '%s: %s' "$branch" "$head")

	# state of the index
	i_tree=$(git-write-tree) &&
	i_commit=$(printf 'index on %s' "$msg" |
		git-commit-tree $i_tree -p $b_commit) ||
		die "Cannot save the current index state"

	# state of the working tree
	w_tree=$( (
		GIT_INDEX_FILE="$TMP-index" &&
		export GIT_INDEX_FILE &&

		rm -f "$TMP-index" &&
		git-read-tree $i_tree &&
		git-add -u &&
		git-write-tree &&
		rm -f "$TMP-index"
	) ) ||
		die "Cannot save the current worktree state"

	# create the stash
	w_commit=$(printf 'WIP on %s' "$msg" |
		git-commit-tree $w_tree -p $b_commit -p $i_commit) ||
		die "Cannot record working tree state"

	git-update-ref -m "$msg" $ref_stash $w_commit ||
		die "Cannot save the current status"
	printf >&2 'Saved WIP on %s\n' "$msg"
}

have_stash () {
	git-rev-parse --verify $ref_stash >/dev/null 2>&1
}

list_stash () {
	have_stash || return 0
	git-log --pretty=oneline -g "$@" $ref_stash |
	sed -n -e 's/^[.0-9a-f]* refs\///p'
}

show_stash () {
	flags=$(git-rev-parse --no-revs --flags "$@")
	if test -z "$flags"
	then
		flags=--stat
	fi
	s=$(git-rev-parse --revs-only --no-flags --default $ref_stash "$@")

	w_commit=$(git-rev-parse --verify "$s") &&
	b_commit=$(git-rev-parse --verify "$s^") &&
	git-diff $flags $b_commit $w_commit
}

apply_stash () {
	git-diff-files --quiet ||
		die 'Cannot restore on top of a dirty state'

	# current index state
	c_tree=$(git-write-tree) ||
		die 'Cannot apply a stash in the middle of a merge'

	s=$(git-rev-parse --revs-only --no-flags --default $ref_stash "$@") &&
	w_tree=$(git-rev-parse --verify "$s:") &&
	b_tree=$(git-rev-parse --verify "$s^:") ||
		die "$*: no valid stashed state found"

	eval "
		GITHEAD_$w_tree='Stashed changes' &&
		GITHEAD_$c_tree='Updated upstream' &&
		GITHEAD_$b_tree='Version stash was based on' &&
		export GITHEAD_$w_tree GITHEAD_$c_tree GITHEAD_$b_tree
	"

	if git-merge-recursive $b_tree -- $c_tree $w_tree
	then
		# No conflict
		a="$TMP-added" &&
		git-diff --cached --name-only --diff-filter=A $c_tree >"$a" &&
		git-read-tree --reset $c_tree &&
		git-update-index --add --stdin <"$a" ||
			die "Cannot unstage modified files"
		git-status
		rm -f "$a"
	else
		# Merge conflict; keep the exit status from merge-recursive
		exit
	fi
}

# Main command set
case "$1" in
list | '')
	test $# -gt 0 && shift
	if test $# = 0
	then
		set x -n 10
		shift
	fi
	list_stash "$@"
	;;
show)
	shift
	show_stash "$@"
	;;
apply)
	shift
	apply_stash "$@"
	;;
clear)
	clear_stash
	;;
save)
	save_stash && git-reset --hard
	;;
*)
	usage
esac
