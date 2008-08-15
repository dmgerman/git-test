#!/bin/bash
#
# Copyright (c) Jim Meyering
#
test_description='diff honors config option, diff.suppress-blank-empty'

. ./test-lib.sh

cat <<\EOF > exp ||
diff --git a/f b/f
index 5f6a263..8cb8bae 100644
--- a/f
+++ b/f
@@ -1,2 +1,2 @@

-x
+y
EOF
exit 1

test_expect_success \
    "$test_description" \
    'printf "\nx\n" > f &&
     git add f &&
     git commit -q -m. f &&
     printf "\ny\n" > f &&
     git config --bool diff.suppress-blank-empty true &&
     git diff f > actual &&
     test_cmp exp actual &&
     perl -i.bak -p -e "s/^\$/ /" exp &&
     git config --bool diff.suppress-blank-empty false &&
     git diff f > actual &&
     test_cmp exp actual &&
     git config --bool --unset diff.suppress-blank-empty &&
     git diff f > actual &&
     test_cmp exp actual
     '

test_done
