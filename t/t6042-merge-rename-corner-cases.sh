#!/bin/sh

test_description="recursive merge corner cases w/ renames but not criss-crosses"
# t6036 has corner cases that involve both criss-cross merges and renames

. ./test-lib.sh

test_expect_success 'setup rename/delete + untracked file' '
	echo "A pretty inscription" >ring &&
	git add ring &&
	test_tick &&
	git commit -m beginning &&

	git branch people &&
	git checkout -b rename-the-ring &&
	git mv ring one-ring-to-rule-them-all &&
	test_tick &&
	git commit -m fullname &&

	git checkout people &&
	git rm ring &&
	echo gollum >owner &&
	git add owner &&
	test_tick &&
	git commit -m track-people-instead-of-objects &&
	echo "Myyy PRECIOUSSS" >ring
'

test_expect_failure "Does git preserve Gollum's precious artifact?" '
	test_must_fail git merge -s recursive rename-the-ring &&

	# Make sure git did not delete an untracked file
	test -f ring
'

# Testcase setup for rename/modify/add-source:
#   Commit A: new file: a
#   Commit B: modify a slightly
#   Commit C: rename a->b, add completely different a
#
# We should be able to merge B & C cleanly

test_expect_success 'setup rename/modify/add-source conflict' '
	git rm -rf . &&
	git clean -fdqx &&
	rm -rf .git &&
	git init &&

	printf "1\n2\n3\n4\n5\n6\n7\n" >a &&
	git add a &&
	git commit -m A &&
	git tag A &&

	git checkout -b B A &&
	echo 8 >>a &&
	git add a &&
	git commit -m B &&

	git checkout -b C A &&
	git mv a b &&
	echo something completely different >a &&
	git add a &&
	git commit -m C
'

test_expect_failure 'rename/modify/add-source conflict resolvable' '
	git checkout B^0 &&

	git merge -s recursive C^0 &&

	test $(git rev-parse B:a) = $(git rev-parse b) &&
	test $(git rev-parse C:a) = $(git rev-parse a)
'

test_expect_success 'setup resolvable conflict missed if rename missed' '
	git rm -rf . &&
	git clean -fdqx &&
	rm -rf .git &&
	git init &&

	printf "1\n2\n3\n4\n5\n" >a &&
	echo foo >b &&
	git add a b &&
	git commit -m A &&
	git tag A &&

	git checkout -b B A &&
	git mv a c &&
	echo "Completely different content" >a &&
	git add a &&
	git commit -m B &&

	git checkout -b C A &&
	echo 6 >>a &&
	git add a &&
	git commit -m C
'

test_expect_failure 'conflict caused if rename not detected' '
	git checkout -q C^0 &&
	git merge -s recursive B^0 &&

	test 3 -eq $(git ls-files -s | wc -l) &&
	test 0 -eq $(git ls-files -u | wc -l) &&
	test 0 -eq $(git ls-files -o | wc -l) &&

	test 6 -eq $(wc -l < c) &&
	test $(git rev-parse HEAD:a) = $(git rev-parse B:a) &&
	test $(git rev-parse HEAD:b) = $(git rev-parse A:b)
'

test_expect_success 'setup conflict resolved wrong if rename missed' '
	git reset --hard &&
	git clean -f &&

	git checkout -b D A &&
	echo 7 >>a &&
	git add a &&
	git mv a c &&
	echo "Completely different content" >a &&
	git add a &&
	git commit -m D &&

	git checkout -b E A &&
	git rm a &&
	echo "Completely different content" >>a &&
	git add a &&
	git commit -m E
'

test_expect_failure 'missed conflict if rename not detected' '
	git checkout -q E^0 &&
	test_must_fail git merge -s recursive D^0
'

# Tests for undetected rename/add-source causing a file to erroneously be
# deleted (and for mishandled rename/rename(1to1) causing the same issue).
#
# This test uses a rename/rename(1to1)+add-source conflict (1to1 means the
# same file is renamed on both sides to the same thing; it should trigger
# the 1to2 logic, which it would do if the add-source didn't cause issues
# for git's rename detection):
#   Commit A: new file: a
#   Commit B: rename a->b
#   Commit C: rename a->b, add unrelated a

test_expect_success 'setup undetected rename/add-source causes data loss' '
	git rm -rf . &&
	git clean -fdqx &&
	rm -rf .git &&
	git init &&

	printf "1\n2\n3\n4\n5\n" >a &&
	git add a &&
	git commit -m A &&
	git tag A &&

	git checkout -b B A &&
	git mv a b &&
	git commit -m B &&

	git checkout -b C A &&
	git mv a b &&
	echo foobar >a &&
	git add a &&
	git commit -m C
'

test_expect_failure 'detect rename/add-source and preserve all data' '
	git checkout B^0 &&

	git merge -s recursive C^0 &&

	test 2 -eq $(git ls-files -s | wc -l) &&
	test 2 -eq $(git ls-files -u | wc -l) &&
	test 0 -eq $(git ls-files -o | wc -l) &&

	test -f a &&
	test -f b &&

	test $(git rev-parse HEAD:b) = $(git rev-parse A:a) &&
	test $(git rev-parse HEAD:a) = $(git rev-parse C:a)
'

test_expect_failure 'detect rename/add-source and preserve all data, merge other way' '
	git checkout C^0 &&

	git merge -s recursive B^0 &&

	test 2 -eq $(git ls-files -s | wc -l) &&
	test 2 -eq $(git ls-files -u | wc -l) &&
	test 0 -eq $(git ls-files -o | wc -l) &&

	test -f a &&
	test -f b &&

	test $(git rev-parse HEAD:b) = $(git rev-parse A:a) &&
	test $(git rev-parse HEAD:a) = $(git rev-parse C:a)
'

test_expect_success 'setup content merge + rename/directory conflict' '
	git rm -rf . &&
	git clean -fdqx &&
	rm -rf .git &&
	git init &&

	printf "1\n2\n3\n4\n5\n6\n" >file &&
	git add file &&
	test_tick &&
	git commit -m base &&
	git tag base &&

	git checkout -b right &&
	echo 7 >>file &&
	mkdir newfile &&
	echo junk >newfile/realfile &&
	git add file newfile/realfile &&
	test_tick &&
	git commit -m right &&

	git checkout -b left-conflict base &&
	echo 8 >>file &&
	git add file &&
	git mv file newfile &&
	test_tick &&
	git commit -m left &&

	git checkout -b left-clean base &&
	echo 0 >newfile &&
	cat file >>newfile &&
	git add newfile &&
	git rm file &&
	test_tick &&
	git commit -m left
'

test_expect_failure 'rename/directory conflict + clean content merge' '
	git reset --hard &&
	git reset --hard &&
	git clean -fdqx &&

	git checkout left-clean^0 &&

	test_must_fail git merge -s recursive right^0 &&

	test 2 -eq $(git ls-files -s | wc -l) &&
	test 1 -eq $(git ls-files -u | wc -l) &&
	test 1 -eq $(git ls-files -o | wc -l) &&

	echo 0 >expect &&
	git cat-file -p base:file >>expect &&
	echo 7 >>expect &&
	test_cmp expect newfile~HEAD &&

	test $(git rev-parse :2:newfile) = $(git hash-object expect) &&

	test -f newfile/realfile &&
	test -f newfile~HEAD
'

test_expect_failure 'rename/directory conflict + content merge conflict' '
	git reset --hard &&
	git reset --hard &&
	git clean -fdqx &&

	git checkout left-conflict^0 &&

	test_must_fail git merge -s recursive right^0 &&

	test 4 -eq $(git ls-files -s | wc -l) &&
	test 3 -eq $(git ls-files -u | wc -l) &&
	test 1 -eq $(git ls-files -o | wc -l) &&

	git cat-file -p left-conflict:newfile >left &&
	git cat-file -p base:file    >base &&
	git cat-file -p right:file   >right &&
	test_must_fail git merge-file \
		-L "HEAD:newfile" \
		-L "" \
		-L "right^0:file" \
		left base right &&
	test_cmp left newfile~HEAD &&

	test $(git rev-parse :1:newfile) = $(git rev-parse base:file) &&
	test $(git rev-parse :2:newfile) = $(git rev-parse left-conflict:newfile) &&
	test $(git rev-parse :3:newfile) = $(git rev-parse right:file) &&

	test -f newfile/realfile &&
	test -f newfile~HEAD
'

test_expect_success 'setup content merge + rename/directory conflict w/ disappearing dir' '
	git reset --hard &&
	git rm -rf . &&
	git clean -fdqx &&
	rm -rf .git &&
	git init &&

	mkdir sub &&
	printf "1\n2\n3\n4\n5\n6\n" >sub/file &&
	git add sub/file &&
	test_tick &&
	git commit -m base &&
	git tag base &&

	git checkout -b right &&
	echo 7 >>sub/file &&
	git add sub/file &&
	test_tick &&
	git commit -m right &&

	git checkout -b left base &&
	echo 0 >newfile &&
	cat sub/file >>newfile &&
	git rm sub/file &&
	mv newfile sub &&
	git add sub &&
	test_tick &&
	git commit -m left
'

test_expect_success 'disappearing dir in rename/directory conflict handled' '
	git reset --hard &&
	git clean -fdqx &&

	git checkout left^0 &&

	git merge -s recursive right^0 &&

	test 1 -eq $(git ls-files -s | wc -l) &&
	test 0 -eq $(git ls-files -u | wc -l) &&
	test 0 -eq $(git ls-files -o | wc -l) &&

	echo 0 >expect &&
	git cat-file -p base:sub/file >>expect &&
	echo 7 >>expect &&
	test_cmp expect sub &&

	test -f sub
'

test_done
