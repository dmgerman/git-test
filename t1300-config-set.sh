#!/bin/sh
#
# Copyright (c) 2005 Johannes Schindelin
#

test_description='Test git-config-set in different settings'

. ./test-lib.sh

test -f .git/config && rm .git/config

git-config-set core.penguin "little blue"

cat > expect << EOF
#
# This is the config file
#

[core]
	penguin = little blue
EOF

test_expect_success 'initial' 'cmp .git/config expect'

git-config-set Core.Movie BadPhysics

cat > expect << EOF
#
# This is the config file
#

[core]
	penguin = little blue
	Movie = BadPhysics
EOF

test_expect_success 'mixed case' 'cmp .git/config expect'

git-config-set Cores.WhatEver Second

cat > expect << EOF
#
# This is the config file
#

[core]
	penguin = little blue
	Movie = BadPhysics
[Cores]
	WhatEver = Second
EOF

test_expect_success 'similar section' 'cmp .git/config expect'

git-config-set CORE.UPPERCASE true

cat > expect << EOF
#
# This is the config file
#

[core]
	penguin = little blue
	Movie = BadPhysics
	UPPERCASE = true
[Cores]
	WhatEver = Second
EOF

test_expect_success 'similar section' 'cmp .git/config expect'

cat > .git/config << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
		haha   ="beta" # last silly comment
[nextSection] noNewline = ouch
EOF

git-config-set beta.haha alpha

cat > expect << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
	haha = alpha
[nextSection] noNewline = ouch
EOF

test_expect_success 'really mean test' 'cmp .git/config expect'

git-config-set nextsection.nonewline wow

cat > expect << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
	haha = alpha
[nextSection]
	nonewline = wow
EOF

test_expect_success 'really really mean test' 'cmp .git/config expect'

git-config-set beta.haha

cat > expect << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
[nextSection]
	nonewline = wow
EOF

test_expect_success 'unset' 'cmp .git/config expect'

git-config-set nextsection.NoNewLine "wow2 for me" "for me$"

cat > expect << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
[nextSection]
	nonewline = wow
	NoNewLine = wow2 for me
EOF

test_expect_success 'multivar' 'cmp .git/config expect'

git-config-set nextsection.nonewline "wow3" "wow$"

cat > expect << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
[nextSection]
	nonewline = wow3
	NoNewLine = wow2 for me
EOF

test_expect_success 'multivar replace' 'cmp .git/config expect'

test_expect_failure 'ambiguous unset' \
	'git-config-set --unset nextsection.nonewline'

test_expect_failure 'invalid unset' \
	'git-config-set --unset somesection.nonewline'

git-config-set --unset nextsection.nonewline "wow3$"

cat > expect << EOF
[beta] ; silly comment # another comment
noIndent= sillyValue ; 'nother silly comment

# empty line
		; comment
[nextSection]
	NoNewLine = wow2 for me
EOF

test_expect_success 'multivar unset' 'cmp .git/config expect'

test_expect_failure 'invalid key' 'git-config-set inval.2key blabla'

test_expect_success 'correct key' 'git-config-set 123456.a123 987'

test_done

