#!/bin/sh

test_description='git-blame'
. ./test-lib.sh

PROG='git blame -c'
. ../annotate-tests.sh

test_done
