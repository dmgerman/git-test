#!/bin/sh

test_description='git-send-email'
. ./test-lib.sh

PROG='git send-email'
test_expect_success \
    'prepare reference tree' \
    'echo "1A quick brown fox jumps over the" >file &&
     echo "lazy dog" >>file &&
     git add file
     GIT_AUTHOR_NAME="A" git commit -a -m "Initial."'

test_expect_success \
    'Setup helper tool' \
    'echo "#!/bin/sh" > fake.sendmail
     echo "shift" >> fake.sendmail
     echo "echo \"\$*\" > commandline" >> fake.sendmail
     echo "cat > msgtxt" >> fake.sendmail
     chmod +x ./fake.sendmail
     git add fake.sendmail
     GIT_AUTHOR_NAME="A" git commit -a -m "Second."'

test_expect_success \
    'Extract patches and send' \
    'git format-patch -n HEAD^1
     git send-email -from="Example <nobody@example.com>" --to=nobody@example.com --smtp-server="$(pwd)/fake.sendmail" ./0001*txt'

test_expect_success \
    'Verify commandline' \
    'cline=$(cat commandline)
     [ "$cline" == "nobody@example.com author@example.com" ]'

test_done
