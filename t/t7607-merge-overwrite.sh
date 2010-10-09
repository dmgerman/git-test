#!/bin/sh

test_description='git-merge

Do not overwrite changes.'

. ./test-lib.sh

test_expect_success 'setup' '
	test_commit c0 c0.c &&
	test_commit c1 c1.c &&
	test_commit c1a c1.c "c1 a" &&
	git reset --hard c0 &&
	test_commit c2 c2.c &&
	git reset --hard c0 &&
	mkdir sub &&
	echo "sub/f" > sub/f &&
	git add sub/f &&
	git commit -m sub &&
	git tag sub &&
	echo "VERY IMPORTANT CHANGES" > important
'

test_expect_success 'will not overwrite untracked file' '
	git reset --hard c1 &&
	cp important c2.c &&
	test_must_fail git merge c2 &&
	test_path_is_missing .git/MERGE_HEAD &&
	test_cmp important c2.c
'

test_expect_success 'will overwrite tracked file' '
	git reset --hard c1 &&
	cp important c2.c &&
	git add c2.c &&
	git commit -m important &&
	git checkout c2
'

test_expect_success 'will not overwrite new file' '
	git reset --hard c1 &&
	cp important c2.c &&
	git add c2.c &&
	test_must_fail git merge c2 &&
	test_path_is_missing .git/MERGE_HEAD &&
	test_cmp important c2.c
'

test_expect_success 'will not overwrite staged changes' '
	git reset --hard c1 &&
	cp important c2.c &&
	git add c2.c &&
	rm c2.c &&
	test_must_fail git merge c2 &&
	test_path_is_missing .git/MERGE_HEAD &&
	git checkout c2.c &&
	test_cmp important c2.c
'

test_expect_success 'will not overwrite removed file' '
	git reset --hard c1 &&
	git rm c1.c &&
	git commit -m "rm c1.c" &&
	cp important c1.c &&
	test_must_fail git merge c1a &&
	test_cmp important c1.c
'

test_expect_success 'will not overwrite re-added file' '
	git reset --hard c1 &&
	git rm c1.c &&
	git commit -m "rm c1.c" &&
	cp important c1.c &&
	git add c1.c &&
	test_must_fail git merge c1a &&
	test_path_is_missing .git/MERGE_HEAD &&
	test_cmp important c1.c
'

test_expect_success 'will not overwrite removed file with staged changes' '
	git reset --hard c1 &&
	git rm c1.c &&
	git commit -m "rm c1.c" &&
	cp important c1.c &&
	git add c1.c &&
	rm c1.c &&
	test_must_fail git merge c1a &&
	test_path_is_missing .git/MERGE_HEAD &&
	git checkout c1.c &&
	test_cmp important c1.c
'

test_expect_success 'will not overwrite untracked subtree' '
	git reset --hard c0 &&
	rm -rf sub &&
	mkdir -p sub/f &&
	cp important sub/f/important &&
	test_must_fail git merge sub &&
	test_path_is_missing .git/MERGE_HEAD &&
	test_cmp important sub/f/important
'

test_expect_success 'will not overwrite untracked file in leading path' '
	git reset --hard c0 &&
	rm -rf sub &&
	cp important sub &&
	test_must_fail git merge sub &&
	test_path_is_missing .git/MERGE_HEAD &&
	test_cmp important sub
'

test_expect_failure SYMLINKS 'will not overwrite untracked symlink in leading path' '
	git reset --hard c0 &&
	rm -rf sub &&
	mkdir sub2 &&
	ln -s sub2 sub &&
	test_must_fail git merge sub &&
	test_path_is_missing .git/MERGE_HEAD
'

test_expect_success SYMLINKS 'will not be confused by symlink in leading path' '
	git reset --hard c0 &&
	rm -rf sub &&
	ln -s sub2 sub &&
	git add sub &&
	git commit -m ln &&
	git checkout sub
'

test_done
