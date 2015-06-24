#!/bin/sh

test_description='git p4 fetching changes in multiple blocks'

. ./lib-git-p4.sh

test_expect_success 'start p4d' '
	start_p4d
'

create_restricted_group() {
	p4 group -i <<-EOF
	Group: restricted
	MaxResults: 7
	MaxScanRows: 40
	Users: author
	EOF
}

test_expect_success 'Create group with limited maxrows' '
	create_restricted_group
'

test_expect_success 'Create a repo with many changes' '
	(
		client_view "//depot/included/... //client/included/..." \
			    "//depot/excluded/... //client/excluded/..." &&
		mkdir -p "$cli/included" "$cli/excluded" &&
		cd "$cli/included" &&
		>file.txt &&
		p4 add file.txt &&
		p4 submit -d "Add file.txt" &&
		for i in $(test_seq 0 5)
		do
			>outer$i.txt &&
			p4 add outer$i.txt &&
			p4 submit -d "Adding outer$i.txt" &&
			for j in $(test_seq 0 5)
			do
				p4 edit file.txt &&
				echo $i$j >file.txt &&
				p4 submit -d "Commit $i$j" || exit
			done || exit
		done
	)
'

test_expect_success 'Default user cannot fetch changes' '
	! p4 changes -m 1 //depot/...
'

test_expect_success 'Clone the repo' '
	git p4 clone --dest="$git" --changes-block-size=7 --verbose //depot/included@all
'

test_expect_success 'All files are present' '
	echo file.txt >expected &&
	test_write_lines outer0.txt outer1.txt outer2.txt outer3.txt outer4.txt >>expected &&
	test_write_lines outer5.txt >>expected &&
	ls "$git" >current &&
	test_cmp expected current
'

test_expect_success 'file.txt is correct' '
	echo 55 >expected &&
	test_cmp expected "$git/file.txt"
'

test_expect_success 'Correct number of commits' '
	(cd "$git" && git log --oneline) >log &&
	wc -l log &&
	test_line_count = 43 log
'

test_expect_success 'Previous version of file.txt is correct' '
	(cd "$git" && git checkout HEAD^^) &&
	echo 53 >expected &&
	test_cmp expected "$git/file.txt"
'

# Test git-p4 sync, with some files outside the client specification.

p4_add_file() {
	(cd "$cli" &&
		>$1 &&
		p4 add $1 &&
		p4 submit -d "Added a file" $1
	)
}

test_expect_success 'Add some more files' '
	for i in $(test_seq 0 10)
	do
		p4_add_file "included/x$i" &&
		p4_add_file "excluded/x$i"
	done &&
	for i in $(test_seq 0 10)
	do
		p4_add_file "excluded/y$i"
	done
'

# This should pick up the 10 new files in "included", but not be confused
# by the additional files in "excluded"
test_expect_success 'Syncing files' '
	(
		cd "$git" &&
		git p4 sync --changes-block-size=7 &&
		git checkout p4/master &&
		ls -l x* > log &&
		test_line_count = 11 log
	)
'

test_expect_success 'kill p4d' '
	kill_p4d
'

test_done
