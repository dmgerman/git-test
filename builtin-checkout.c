macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;merge-recursive.h&quot;
macro_line|#include &quot;branch.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|variable|checkout_usage
r_static
r_const
r_char
op_star
r_const
id|checkout_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git checkout [options] &lt;branch&gt;&quot;
comma
l_string|&quot;git checkout [options] [&lt;branch&gt;] -- &lt;file&gt;...&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|post_checkout_hook
r_static
r_int
id|post_checkout_hook
c_func
(paren
r_struct
id|commit
op_star
id|old
comma
r_struct
id|commit
op_star
r_new
comma
r_int
id|changed
)paren
(brace
r_struct
id|child_process
id|proc
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|git_path
c_func
(paren
l_string|&quot;hooks/post-checkout&quot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|name
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|proc
comma
l_int|0
comma
r_sizeof
(paren
id|proc
)paren
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|name
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
id|xstrdup
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|old-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
id|xstrdup
c_func
(paren
id|sha1_to_hex
c_func
(paren
r_new
op_member_access_from_pointer
id|object.sha1
)paren
)paren
suffix:semicolon
id|argv
(braket
l_int|3
)braket
op_assign
id|changed
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;0&quot;
suffix:semicolon
id|argv
(braket
l_int|4
)braket
op_assign
l_int|NULL
suffix:semicolon
id|proc.argv
op_assign
id|argv
suffix:semicolon
id|proc.no_stdin
op_assign
l_int|1
suffix:semicolon
id|proc.stdout_to_stderr
op_assign
l_int|1
suffix:semicolon
r_return
id|run_command
c_func
(paren
op_amp
id|proc
)paren
suffix:semicolon
)brace
DECL|function|update_some
r_static
r_int
id|update_some
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
comma
r_int
id|stage
comma
r_void
op_star
id|context
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
r_return
id|READ_TREE_RECURSIVE
suffix:semicolon
id|len
op_assign
id|baselen
op_plus
id|strlen
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|ce
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|cache_entry_size
c_func
(paren
id|len
)paren
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
op_plus
id|baselen
comma
id|pathname
comma
id|len
id|baselen
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|create_ce_flags
c_func
(paren
id|len
comma
l_int|0
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|add_cache_entry
c_func
(paren
id|ce
comma
id|ADD_CACHE_OK_TO_ADD
op_or
id|ADD_CACHE_OK_TO_REPLACE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_tree_some
r_static
r_int
id|read_tree_some
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
id|read_tree_recursive
c_func
(paren
id|tree
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
comma
id|pathspec
comma
id|update_some
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* update the index with the given tree&squot;s info&n;&t; * for all args, expanding wildcards, and exit&n;&t; * with any non-zero return code.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|skip_same_name
r_static
r_int
id|skip_same_name
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
id|pos
)paren
(brace
r_while
c_loop
(paren
op_increment
id|pos
OL
id|active_nr
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|ce-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* skip */
r_return
id|pos
suffix:semicolon
)brace
DECL|function|checkout_paths
r_static
r_int
id|checkout_paths
c_func
(paren
r_struct
id|tree
op_star
id|source_tree
comma
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_int
id|pos
suffix:semicolon
r_struct
id|checkout
id|state
suffix:semicolon
r_static
r_char
op_star
id|ps_matched
suffix:semicolon
r_int
r_char
id|rev
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|flag
suffix:semicolon
r_struct
id|commit
op_star
id|head
suffix:semicolon
r_int
id|errs
op_assign
l_int|0
suffix:semicolon
r_int
id|newfd
suffix:semicolon
r_struct
id|lock_file
op_star
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|source_tree
)paren
id|read_tree_some
c_func
(paren
id|source_tree
comma
id|pathspec
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|pos
)braket
suffix:semicolon
id|pos
op_increment
)paren
suffix:semicolon
id|ps_matched
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|pos
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|active_nr
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
id|pathspec_match
c_func
(paren
id|pathspec
comma
id|ps_matched
comma
id|ce-&gt;name
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|report_path_error
c_func
(paren
id|ps_matched
comma
id|pathspec
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Any unmerged paths? */
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|active_nr
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pathspec_match
c_func
(paren
id|pathspec
comma
l_int|NULL
comma
id|ce-&gt;name
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;path &squot;%s&squot; is unmerged&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|pos
op_assign
id|skip_same_name
c_func
(paren
id|ce
comma
id|pos
)paren
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|errs
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Now we are committed to check them out */
id|memset
c_func
(paren
op_amp
id|state
comma
l_int|0
comma
r_sizeof
(paren
id|state
)paren
)paren
suffix:semicolon
id|state.force
op_assign
l_int|1
suffix:semicolon
id|state.refresh_cache
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|active_nr
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pathspec_match
c_func
(paren
id|pathspec
comma
l_int|NULL
comma
id|ce-&gt;name
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|errs
op_or_assign
id|checkout_entry
c_func
(paren
id|ce
comma
op_amp
id|state
comma
l_int|NULL
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pos
op_assign
id|skip_same_name
c_func
(paren
id|ce
comma
id|pos
)paren
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
suffix:semicolon
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|rev
comma
l_int|0
comma
op_amp
id|flag
)paren
suffix:semicolon
id|head
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|rev
comma
l_int|1
)paren
suffix:semicolon
id|errs
op_or_assign
id|post_checkout_hook
c_func
(paren
id|head
comma
id|head
comma
l_int|0
)paren
suffix:semicolon
r_return
id|errs
suffix:semicolon
)brace
DECL|function|show_local_changes
r_static
r_void
id|show_local_changes
c_func
(paren
r_struct
id|object
op_star
id|head
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
multiline_comment|/* I think we want full paths, even if we&squot;re in a subdirectory. */
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|rev.abbrev
op_assign
l_int|0
suffix:semicolon
id|rev.diffopt.output_format
op_or_assign
id|DIFF_FORMAT_NAME_STATUS
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|rev
comma
id|head
comma
l_int|NULL
)paren
suffix:semicolon
id|run_diff_index
c_func
(paren
op_amp
id|rev
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|describe_detached_head
r_static
r_void
id|describe_detached_head
c_func
(paren
r_char
op_star
id|msg
comma
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|strbuf
id|sb
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
id|pretty_print_commit
c_func
(paren
id|CMIT_FMT_ONELINE
comma
id|commit
comma
op_amp
id|sb
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s %s... %s&bslash;n&quot;
comma
id|msg
comma
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|DEFAULT_ABBREV
)paren
comma
id|sb.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
DECL|struct|checkout_opts
r_struct
id|checkout_opts
(brace
DECL|member|quiet
r_int
id|quiet
suffix:semicolon
DECL|member|merge
r_int
id|merge
suffix:semicolon
DECL|member|force
r_int
id|force
suffix:semicolon
DECL|member|writeout_error
r_int
id|writeout_error
suffix:semicolon
DECL|member|new_branch
r_char
op_star
id|new_branch
suffix:semicolon
DECL|member|new_branch_log
r_int
id|new_branch_log
suffix:semicolon
DECL|member|track
r_enum
id|branch_track
id|track
suffix:semicolon
)brace
suffix:semicolon
DECL|function|reset_tree
r_static
r_int
id|reset_tree
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_struct
id|checkout_opts
op_star
id|o
comma
r_int
id|worktree
)paren
(brace
r_struct
id|unpack_trees_options
id|opts
suffix:semicolon
r_struct
id|tree_desc
id|tree_desc
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|opts.head_idx
op_assign
l_int|1
suffix:semicolon
id|opts.update
op_assign
id|worktree
suffix:semicolon
id|opts.skip_unmerged
op_assign
op_logical_neg
id|worktree
suffix:semicolon
id|opts.reset
op_assign
l_int|1
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|opts.fn
op_assign
id|oneway_merge
suffix:semicolon
id|opts.verbose_update
op_assign
op_logical_neg
id|o-&gt;quiet
suffix:semicolon
id|opts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.dst_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|parse_tree
c_func
(paren
id|tree
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|tree_desc
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|unpack_trees
c_func
(paren
l_int|1
comma
op_amp
id|tree_desc
comma
op_amp
id|opts
)paren
)paren
(brace
r_case
l_int|2
suffix:colon
id|o-&gt;writeout_error
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We return 0 nevertheless, as the index is all right&n;&t;&t; * and more importantly we have made best efforts to&n;&t;&t; * update paths in the work tree, and we cannot revert&n;&t;&t; * them.&n;&t;&t; */
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
l_int|128
suffix:semicolon
)brace
)brace
DECL|struct|branch_info
r_struct
id|branch_info
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* The short name used */
DECL|member|path
r_const
r_char
op_star
id|path
suffix:semicolon
multiline_comment|/* The full name of a real branch */
DECL|member|commit
r_struct
id|commit
op_star
id|commit
suffix:semicolon
multiline_comment|/* The named commit */
)brace
suffix:semicolon
DECL|function|setup_branch_path
r_static
r_void
id|setup_branch_path
c_func
(paren
r_struct
id|branch_info
op_star
id|branch
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|branch-&gt;name
)paren
suffix:semicolon
id|branch-&gt;path
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|merge_working_tree
r_static
r_int
id|merge_working_tree
c_func
(paren
r_struct
id|checkout_opts
op_star
id|opts
comma
r_struct
id|branch_info
op_star
id|old
comma
r_struct
id|branch_info
op_star
r_new
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|lock_file
op_star
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
r_int
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;force
)paren
(brace
id|ret
op_assign
id|reset_tree
c_func
(paren
r_new
op_member_access_from_pointer
id|commit-&gt;tree
comma
id|opts
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_else
(brace
r_struct
id|tree_desc
id|trees
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_struct
id|unpack_trees_options
id|topts
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|topts
comma
l_int|0
comma
r_sizeof
(paren
id|topts
)paren
)paren
suffix:semicolon
id|topts.head_idx
op_assign
l_int|1
suffix:semicolon
id|topts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|topts.dst_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|topts.msgs.not_uptodate_file
op_assign
l_string|&quot;You have local changes to &squot;%s&squot;; cannot switch branches.&quot;
suffix:semicolon
id|refresh_cache
c_func
(paren
id|REFRESH_QUIET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unmerged_cache
c_func
(paren
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;you need to resolve your current index first&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* 2-way merge to the new branch */
id|topts.update
op_assign
l_int|1
suffix:semicolon
id|topts.merge
op_assign
l_int|1
suffix:semicolon
id|topts.gently
op_assign
id|opts-&gt;merge
suffix:semicolon
id|topts.verbose_update
op_assign
op_logical_neg
id|opts-&gt;quiet
suffix:semicolon
id|topts.fn
op_assign
id|twoway_merge
suffix:semicolon
id|topts.dir
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|topts.dir
)paren
)paren
suffix:semicolon
id|topts.dir-&gt;show_ignored
op_assign
l_int|1
suffix:semicolon
id|topts.dir-&gt;exclude_per_dir
op_assign
l_string|&quot;.gitignore&quot;
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|old-&gt;commit-&gt;object.sha1
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|trees
(braket
l_int|0
)braket
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
r_new
op_member_access_from_pointer
id|commit-&gt;object.sha1
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|trees
(braket
l_int|1
)braket
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
id|ret
op_assign
id|unpack_trees
c_func
(paren
l_int|2
comma
id|trees
comma
op_amp
id|topts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Unpack couldn&squot;t do a trivial merge; either&n;&t;&t;&t; * give up or do a real merge, depending on&n;&t;&t;&t; * whether the merge flag was used.&n;&t;&t;&t; */
r_struct
id|tree
op_star
id|result
suffix:semicolon
r_struct
id|tree
op_star
id|work
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;merge
)paren
r_return
l_int|1
suffix:semicolon
id|parse_commit
c_func
(paren
id|old-&gt;commit
)paren
suffix:semicolon
multiline_comment|/* Do more real merge */
multiline_comment|/*&n;&t;&t;&t; * We update the index fully, then write the&n;&t;&t;&t; * tree from the index, then merge the new&n;&t;&t;&t; * branch with the current tree, with the old&n;&t;&t;&t; * branch as the base. Then we reset the index&n;&t;&t;&t; * (but not the working tree) to the new&n;&t;&t;&t; * branch, leaving the working tree as the&n;&t;&t;&t; * merged version, but skipping unmerged&n;&t;&t;&t; * entries in the index.&n;&t;&t;&t; */
id|add_files_to_cache
c_func
(paren
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|work
op_assign
id|write_tree_from_memory
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|reset_tree
c_func
(paren
r_new
op_member_access_from_pointer
id|commit-&gt;tree
comma
id|opts
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|merge_trees
c_func
(paren
r_new
op_member_access_from_pointer
id|commit-&gt;tree
comma
id|work
comma
id|old-&gt;commit-&gt;tree
comma
r_new
op_member_access_from_pointer
id|name
comma
l_string|&quot;local&quot;
comma
op_amp
id|result
)paren
suffix:semicolon
id|ret
op_assign
id|reset_tree
c_func
(paren
r_new
op_member_access_from_pointer
id|commit-&gt;tree
comma
id|opts
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;force
)paren
id|show_local_changes
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|commit-&gt;object
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|report_tracking
r_static
r_void
id|report_tracking
c_func
(paren
r_struct
id|branch_info
op_star
r_new
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|branch
op_star
id|branch
op_assign
id|branch_get
c_func
(paren
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|format_tracking_info
c_func
(paren
id|branch
comma
op_amp
id|sb
)paren
)paren
r_return
suffix:semicolon
id|fputs
c_func
(paren
id|sb.buf
comma
id|stdout
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
DECL|function|update_refs_for_switch
r_static
r_void
id|update_refs_for_switch
c_func
(paren
r_struct
id|checkout_opts
op_star
id|opts
comma
r_struct
id|branch_info
op_star
id|old
comma
r_struct
id|branch_info
op_star
r_new
)paren
(brace
r_struct
id|strbuf
id|msg
suffix:semicolon
r_const
r_char
op_star
id|old_desc
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;new_branch
)paren
(brace
id|create_branch
c_func
(paren
id|old-&gt;name
comma
id|opts-&gt;new_branch
comma
r_new
op_member_access_from_pointer
id|name
comma
l_int|0
comma
id|opts-&gt;new_branch_log
comma
id|opts-&gt;track
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|name
op_assign
id|opts-&gt;new_branch
suffix:semicolon
id|setup_branch_path
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
id|strbuf_init
c_func
(paren
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
id|old_desc
op_assign
id|old-&gt;name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_desc
)paren
id|old_desc
op_assign
id|sha1_to_hex
c_func
(paren
id|old-&gt;commit-&gt;object.sha1
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|msg
comma
l_string|&quot;checkout: moving from %s to %s&quot;
comma
id|old_desc
comma
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|path
)paren
(brace
id|create_symref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
r_new
op_member_access_from_pointer
id|path
comma
id|msg.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;quiet
)paren
(brace
r_if
c_cond
(paren
id|old-&gt;path
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
r_new
op_member_access_from_pointer
id|path
comma
id|old-&gt;path
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Already on &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Switched to%s branch &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|opts-&gt;new_branch
ques
c_cond
l_string|&quot; a new&quot;
suffix:colon
l_string|&quot;&quot;
comma
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
r_new
op_member_access_from_pointer
id|name
comma
l_string|&quot;HEAD&quot;
)paren
)paren
(brace
id|update_ref
c_func
(paren
id|msg.buf
comma
l_string|&quot;HEAD&quot;
comma
r_new
op_member_access_from_pointer
id|commit-&gt;object.sha1
comma
l_int|NULL
comma
id|REF_NODEREF
comma
id|DIE_ON_ERR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;quiet
)paren
(brace
r_if
c_cond
(paren
id|old-&gt;path
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Note: moving to &bslash;&quot;%s&bslash;&quot; which isn&squot;t a local branch&bslash;nIf you want to create a new branch from this checkout, you may do so&bslash;n(now or later) by using -b with the checkout command again. Example:&bslash;n  git checkout -b &lt;new_branch_name&gt;&bslash;n&quot;
comma
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|describe_detached_head
c_func
(paren
l_string|&quot;HEAD is now at&quot;
comma
r_new
op_member_access_from_pointer
id|commit
)paren
suffix:semicolon
)brace
)brace
id|remove_branch_state
c_func
(paren
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;quiet
op_logical_and
(paren
r_new
op_member_access_from_pointer
id|path
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
r_new
op_member_access_from_pointer
id|name
comma
l_string|&quot;HEAD&quot;
)paren
)paren
)paren
id|report_tracking
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
DECL|function|switch_branches
r_static
r_int
id|switch_branches
c_func
(paren
r_struct
id|checkout_opts
op_star
id|opts
comma
r_struct
id|branch_info
op_star
r_new
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|branch_info
id|old
suffix:semicolon
r_int
r_char
id|rev
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|flag
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|old
comma
l_int|0
comma
r_sizeof
(paren
id|old
)paren
)paren
suffix:semicolon
id|old.path
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|rev
comma
l_int|0
comma
op_amp
id|flag
)paren
suffix:semicolon
id|old.commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|rev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flag
op_amp
id|REF_ISSYMREF
)paren
)paren
id|old.path
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|old.path
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|old.path
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
id|old.name
op_assign
id|old.path
op_plus
id|strlen
c_func
(paren
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_member_access_from_pointer
id|name
)paren
(brace
r_new
op_member_access_from_pointer
id|name
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
r_new
op_member_access_from_pointer
id|commit
op_assign
id|old.commit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_member_access_from_pointer
id|commit
)paren
id|die
c_func
(paren
l_string|&quot;You are on a branch yet to be born&quot;
)paren
suffix:semicolon
id|parse_commit
c_func
(paren
r_new
op_member_access_from_pointer
id|commit
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we were on a detached HEAD, but we are now moving to&n;&t; * a new commit, we want to mention the old commit once more&n;&t; * to remind the user that it might be lost.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;quiet
op_logical_and
op_logical_neg
id|old.path
op_logical_and
r_new
op_member_access_from_pointer
id|commit
op_ne
id|old.commit
)paren
id|describe_detached_head
c_func
(paren
l_string|&quot;Previous HEAD position was&quot;
comma
id|old.commit
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old.commit
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;quiet
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: You appear to be on a branch yet to be born.&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: Forcing checkout of %s.&bslash;n&quot;
comma
r_new
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
id|opts-&gt;force
op_assign
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|merge_working_tree
c_func
(paren
id|opts
comma
op_amp
id|old
comma
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|update_refs_for_switch
c_func
(paren
id|opts
comma
op_amp
id|old
comma
r_new
)paren
suffix:semicolon
id|ret
op_assign
id|post_checkout_hook
c_func
(paren
id|old.commit
comma
r_new
op_member_access_from_pointer
id|commit
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
op_logical_or
id|opts-&gt;writeout_error
suffix:semicolon
)brace
DECL|function|cmd_checkout
r_int
id|cmd_checkout
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|checkout_opts
id|opts
suffix:semicolon
r_int
r_char
id|rev
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|arg
suffix:semicolon
r_struct
id|branch_info
r_new
suffix:semicolon
r_struct
id|tree
op_star
id|source_tree
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|opts.quiet
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;b&squot;
comma
l_int|NULL
comma
op_amp
id|opts.new_branch
comma
l_string|&quot;new branch&quot;
comma
l_string|&quot;branch&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;l&squot;
comma
l_int|NULL
comma
op_amp
id|opts.new_branch_log
comma
l_string|&quot;log for new branch&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;t&squot;
comma
l_string|&quot;track&quot;
comma
op_amp
id|opts.track
comma
l_string|&quot;track&quot;
comma
id|BRANCH_TRACK_EXPLICIT
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_int|NULL
comma
op_amp
id|opts.force
comma
l_string|&quot;force&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;m&squot;
comma
l_int|NULL
comma
op_amp
id|opts.merge
comma
l_string|&quot;merge&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_int
id|has_dash_dash
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
r_new
comma
l_int|0
comma
r_sizeof
(paren
r_new
)paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|opts.track
op_assign
id|git_branch_track
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|options
comma
id|checkout_usage
comma
id|PARSE_OPT_KEEP_DASHDASH
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts.new_branch
op_logical_and
(paren
id|opts.track
op_ne
id|git_branch_track
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git checkout: --track and --no-track require -b&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts.force
op_logical_and
id|opts.merge
)paren
id|die
c_func
(paren
l_string|&quot;git checkout: -f and -m are incompatible&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * case 1: git checkout &lt;ref&gt; -- [&lt;paths&gt;]&n;&t; *&n;&t; *   &lt;ref&gt; must be a valid tree, everything after the &squot;--&squot; must be&n;&t; *   a path.&n;&t; *&n;&t; * case 2: git checkout -- [&lt;paths&gt;]&n;&t; *&n;&t; *   everything after the &squot;--&squot; must be paths.&n;&t; *&n;&t; * case 3: git checkout &lt;something&gt; [&lt;paths&gt;]&n;&t; *&n;&t; *   With no paths, if &lt;something&gt; is a commit, that is to&n;&t; *   switch to the branch or detach HEAD at it.&n;&t; *&n;&t; *   Otherwise &lt;something&gt; shall not be ambiguous.&n;&t; *   - If it&squot;s *only* a reference, treat it like case (1).&n;&t; *   - If it&squot;s only a path, treat it like case (2).&n;&t; *   - else: fail.&n;&t; *&n;&t; */
r_if
c_cond
(paren
id|argc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
multiline_comment|/* case (2) */
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_goto
id|no_reference
suffix:semicolon
)brace
id|arg
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|has_dash_dash
op_assign
(paren
id|argc
OG
l_int|1
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|rev
)paren
)paren
(brace
r_if
c_cond
(paren
id|has_dash_dash
)paren
multiline_comment|/* case (1) */
id|die
c_func
(paren
l_string|&quot;invalid reference: %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_goto
id|no_reference
suffix:semicolon
multiline_comment|/* case (3 -&gt; 2) */
)brace
multiline_comment|/* we can&squot;t end up being in (2) anymore, eat the argument */
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
r_new
dot
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|rev
comma
l_int|1
)paren
)paren
)paren
(brace
r_new
dot
id|name
op_assign
id|arg
suffix:semicolon
id|setup_branch_path
c_func
(paren
op_amp
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resolve_ref
c_func
(paren
r_new
dot
id|path
comma
id|rev
comma
l_int|1
comma
l_int|NULL
)paren
)paren
r_new
dot
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|rev
)paren
suffix:semicolon
r_else
r_new
dot
id|path
op_assign
l_int|NULL
suffix:semicolon
id|parse_commit
c_func
(paren
r_new
dot
id|commit
)paren
suffix:semicolon
id|source_tree
op_assign
r_new
dot
id|commit-&gt;tree
suffix:semicolon
)brace
r_else
id|source_tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|source_tree
)paren
multiline_comment|/* case (1): want a tree */
id|die
c_func
(paren
l_string|&quot;reference is not a tree: %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_dash_dash
)paren
(brace
multiline_comment|/* case (3 -&gt; 1) */
multiline_comment|/*&n;&t;&t;&t; * Do not complain the most common case&n;&t;&t;&t; *&t;git checkout branch&n;&t;&t;&t; * even if there happen to be a file called &squot;branch&squot;;&n;&t;&t;&t; * it would be extremely annoying.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|argc
)paren
id|verify_non_filename
c_func
(paren
l_int|NULL
comma
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
)brace
id|no_reference
suffix:colon
r_if
c_cond
(paren
id|argc
)paren
(brace
r_const
r_char
op_star
op_star
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathspec
)paren
id|die
c_func
(paren
l_string|&quot;invalid path specification&quot;
)paren
suffix:semicolon
multiline_comment|/* Checkout paths */
r_if
c_cond
(paren
id|opts.new_branch
op_logical_or
id|opts.force
op_logical_or
id|opts.merge
)paren
(brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
(brace
id|die
c_func
(paren
l_string|&quot;git checkout: updating paths is incompatible with switching branches/forcing&bslash;nDid you intend to checkout &squot;%s&squot; which can not be resolved as commit?&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|die
c_func
(paren
l_string|&quot;git checkout: updating paths is incompatible with switching branches/forcing&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|checkout_paths
c_func
(paren
id|source_tree
comma
id|pathspec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
dot
id|name
op_logical_and
op_logical_neg
r_new
dot
id|commit
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Cannot switch branch to a non-commit.&quot;
)paren
suffix:semicolon
)brace
r_return
id|switch_branches
c_func
(paren
op_amp
id|opts
comma
op_amp
r_new
)paren
suffix:semicolon
)brace
eof
