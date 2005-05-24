multiline_comment|/*&n; * cvs2git&n; *&n; * Copyright (C) Linus Torvalds 2005&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
DECL|variable|verbose
r_static
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * This is a really stupid program that takes cvsps output, and&n; * generates a a long _shell_script_ that will create the GIT archive&n; * from it. &n; *&n; * You&squot;ve been warned. I told you it was stupid.&n; *&n; * NOTE NOTE NOTE! In order to do branches correctly, this needs&n; * the fixed cvsps that has the &quot;Ancestor branch&quot; tag output.&n; * Hopefully David Mansfield will update his distribution soon&n; * enough (he&squot;s the one who wrote the patch, so at least we don&squot;t&n; * have to figt maintainer issues ;)&n; */
DECL|enum|state
r_enum
id|state
(brace
DECL|enumerator|Header
id|Header
comma
DECL|enumerator|Log
id|Log
comma
DECL|enumerator|Members
id|Members
)brace
suffix:semicolon
DECL|variable|rcsdir
r_static
r_char
op_star
id|rcsdir
suffix:semicolon
DECL|variable|date
r_static
r_char
id|date
(braket
l_int|100
)braket
suffix:semicolon
DECL|variable|author
r_static
r_char
id|author
(braket
l_int|100
)braket
suffix:semicolon
DECL|variable|branch
r_static
r_char
id|branch
(braket
l_int|100
)braket
suffix:semicolon
DECL|variable|ancestor
r_static
r_char
id|ancestor
(braket
l_int|100
)braket
suffix:semicolon
DECL|variable|tag
r_static
r_char
id|tag
(braket
l_int|100
)braket
suffix:semicolon
DECL|variable|log
r_static
r_char
id|log
(braket
l_int|32768
)braket
suffix:semicolon
DECL|variable|loglen
r_static
r_int
id|loglen
op_assign
l_int|0
suffix:semicolon
DECL|variable|initial_commit
r_static
r_int
id|initial_commit
op_assign
l_int|1
suffix:semicolon
DECL|function|lookup_author
r_static
r_void
id|lookup_author
c_func
(paren
r_char
op_star
id|n
comma
r_char
op_star
op_star
id|name
comma
r_char
op_star
op_star
id|email
)paren
(brace
multiline_comment|/*&n;&t; * FIXME!!! I&squot;m lazy and stupid.&n;&t; *&n;&t; * This could be something like&n;&t; *&n;&t; *&t;printf(&quot;lookup_author &squot;%s&squot;&bslash;n&quot;, n);&n;&t; *&t;*name = &quot;$author_name&quot;;&n;&t; *&t;*email = &quot;$author_email&quot;;&n;&t; *&n;&t; * and that would allow the script to do its own&n;&t; * lookups at run-time.&n;&t; */
op_star
id|name
op_assign
id|n
suffix:semicolon
op_star
id|email
op_assign
id|n
suffix:semicolon
)brace
DECL|function|prepare_commit
r_static
r_void
id|prepare_commit
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|author_name
comma
op_star
id|author_email
suffix:semicolon
r_char
op_star
id|src_branch
suffix:semicolon
id|lookup_author
c_func
(paren
id|author
comma
op_amp
id|author_name
comma
op_amp
id|author_email
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;export GIT_COMMITTER_NAME=%s&bslash;n&quot;
comma
id|author_name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;export GIT_COMMITTER_EMAIL=%s&bslash;n&quot;
comma
id|author_email
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;export GIT_COMMITTER_DATE=&squot;+0000 %s&squot;&bslash;n&quot;
comma
id|date
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;export GIT_AUTHOR_NAME=%s&bslash;n&quot;
comma
id|author_name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;export GIT_AUTHOR_EMAIL=%s&bslash;n&quot;
comma
id|author_email
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;export GIT_AUTHOR_DATE=&squot;+0000 %s&squot;&bslash;n&quot;
comma
id|date
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initial_commit
)paren
r_return
suffix:semicolon
id|src_branch
op_assign
op_star
id|ancestor
ques
c_cond
id|ancestor
suffix:colon
id|branch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|src_branch
comma
l_string|&quot;HEAD&quot;
)paren
)paren
id|src_branch
op_assign
l_string|&quot;master&quot;
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;ln -sf refs/heads/&squot;%s&squot; .git/HEAD&bslash;n&quot;
comma
id|src_branch
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Even if cvsps claims an ancestor, we&squot;ll let the new&n;&t; * branch name take precedence if it already exists&n;&t; */
r_if
c_cond
(paren
op_star
id|ancestor
)paren
(brace
id|src_branch
op_assign
id|branch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|src_branch
comma
l_string|&quot;HEAD&quot;
)paren
)paren
id|src_branch
op_assign
l_string|&quot;master&quot;
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;[ -e .git/refs/heads/&squot;%s&squot; ] &amp;&amp; ln -sf refs/heads/&squot;%s&squot; .git/HEAD&bslash;n&quot;
comma
id|src_branch
comma
id|src_branch
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;git-read-tree -m HEAD || exit 1&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;git-checkout-cache -f -u -a&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|commit
r_static
r_void
id|commit
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|cmit_parent
op_assign
id|initial_commit
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;-p HEAD&quot;
suffix:semicolon
r_const
r_char
op_star
id|dst_branch
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;tree=$(git-write-tree)&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;cat &gt; .cmitmsg &lt;&lt;EOFMSG&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Escape $ characters, and remove control characters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|loglen
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|c
op_assign
id|log
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;$&squot;
suffix:colon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
r_case
l_char|&squot;`&squot;
suffix:colon
id|putchar
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
dot
dot
dot
l_int|31
suffix:colon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;t&squot;
)paren
r_break
suffix:semicolon
r_case
l_int|128
dot
dot
dot
l_int|159
suffix:colon
r_continue
suffix:semicolon
)brace
id|putchar
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;nEOFMSG&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;commit=$(cat .cmitmsg | git-commit-tree $tree %s)&bslash;n&quot;
comma
id|cmit_parent
)paren
suffix:semicolon
id|dst_branch
op_assign
id|branch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|dst_branch
comma
l_string|&quot;HEAD&quot;
)paren
)paren
id|dst_branch
op_assign
l_string|&quot;master&quot;
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;echo $commit &gt; .git/refs/heads/&squot;%s&squot;&bslash;n&quot;
comma
id|dst_branch
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;echo &squot;Committed (to %s):&squot; ; cat .cmitmsg; echo&bslash;n&quot;
comma
id|dst_branch
)paren
suffix:semicolon
op_star
id|date
op_assign
l_int|0
suffix:semicolon
op_star
id|author
op_assign
l_int|0
suffix:semicolon
op_star
id|branch
op_assign
l_int|0
suffix:semicolon
op_star
id|ancestor
op_assign
l_int|0
suffix:semicolon
op_star
id|tag
op_assign
l_int|0
suffix:semicolon
id|loglen
op_assign
l_int|0
suffix:semicolon
id|initial_commit
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|get_rcs_name
r_static
r_void
id|get_rcs_name
c_func
(paren
r_char
op_star
id|rcspathname
comma
r_char
op_star
id|name
comma
r_char
op_star
id|dir
)paren
(brace
id|sprintf
c_func
(paren
id|rcspathname
comma
l_string|&quot;%s/%s,v&quot;
comma
id|rcsdir
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|rcspathname
comma
id|R_OK
)paren
)paren
r_return
suffix:semicolon
id|sprintf
c_func
(paren
id|rcspathname
comma
l_string|&quot;%s/Attic/%s,v&quot;
comma
id|rcsdir
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|rcspathname
comma
id|R_OK
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
id|sprintf
c_func
(paren
id|rcspathname
comma
l_string|&quot;%s/%.*s/Attic/%s,v&quot;
comma
id|rcsdir
comma
(paren
r_int
)paren
(paren
id|dir
id|name
)paren
comma
id|name
comma
id|dir
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|rcspathname
comma
id|R_OK
)paren
)paren
r_return
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unable to find RCS file for %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|update_file
r_static
r_void
id|update_file
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_static
r_char
id|rcspathname
(braket
l_int|4096
)braket
suffix:semicolon
r_char
op_star
id|name
comma
op_star
id|version
suffix:semicolon
r_char
op_star
id|dir
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|line
)paren
)paren
id|line
op_increment
suffix:semicolon
id|name
op_assign
id|line
suffix:semicolon
id|line
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
)paren
r_return
suffix:semicolon
op_star
id|line
op_increment
op_assign
l_int|0
suffix:semicolon
id|line
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
)paren
r_return
suffix:semicolon
op_star
id|line
op_increment
op_assign
l_int|0
suffix:semicolon
id|version
op_assign
id|line
suffix:semicolon
id|line
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;(&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
)paren
(brace
multiline_comment|/* &quot;(DEAD)&quot; */
id|printf
c_func
(paren
l_string|&quot;git-update-cache --force-remove &squot;%s&squot;&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dir
op_assign
id|strrchr
c_func
(paren
id|name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
id|printf
c_func
(paren
l_string|&quot;mkdir -p %.*s&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|dir
id|name
)paren
comma
id|name
)paren
suffix:semicolon
id|get_rcs_name
c_func
(paren
id|rcspathname
comma
id|name
comma
id|dir
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;co -q -p -r%s &squot;%s&squot; &gt; &squot;%s&squot;&bslash;n&quot;
comma
id|version
comma
id|rcspathname
comma
id|name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;git-update-cache --add -- &squot;%s&squot;&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|struct|hdrentry
r_struct
id|hdrentry
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|dest
r_char
op_star
id|dest
suffix:semicolon
DECL|variable|hdrs
)brace
id|hdrs
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Date:&quot;
comma
id|date
)brace
comma
(brace
l_string|&quot;Author:&quot;
comma
id|author
)brace
comma
(brace
l_string|&quot;Branch:&quot;
comma
id|branch
)brace
comma
(brace
l_string|&quot;Ancestor branch:&quot;
comma
id|ancestor
)brace
comma
(brace
l_string|&quot;Tag:&quot;
comma
id|tag
)brace
comma
(brace
l_string|&quot;Log:&quot;
comma
l_int|NULL
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_enum
id|state
id|state
op_assign
id|Header
suffix:semicolon
id|rcsdir
op_assign
id|getenv
c_func
(paren
l_string|&quot;RCSDIR&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rcsdir
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;I need an $RCSDIR&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;[ -d .git ] &amp;&amp; exit 1&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;git-init-db&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;mkdir -p .git/refs/heads&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;mkdir -p .git/refs/tags&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;ln -sf refs/heads/master .git/HEAD&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|linelen
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_while
c_loop
(paren
id|linelen
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
id|linelen
op_minus
l_int|1
)braket
)paren
)paren
id|line
(braket
op_decrement
id|linelen
)braket
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|state
)paren
(brace
r_struct
id|hdrentry
op_star
id|entry
suffix:semicolon
r_case
id|Header
suffix:colon
r_if
c_cond
(paren
id|verbose
)paren
id|printf
c_func
(paren
l_string|&quot;# H: %s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|hdrs
suffix:semicolon
id|entry-&gt;name
suffix:semicolon
id|entry
op_increment
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|entry-&gt;name
)paren
suffix:semicolon
r_char
op_star
id|val
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|entry-&gt;name
comma
id|line
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;dest
)paren
(brace
id|state
op_assign
id|Log
suffix:semicolon
r_break
suffix:semicolon
)brace
id|val
op_assign
id|line
op_plus
id|len
suffix:semicolon
id|linelen
op_sub_assign
id|len
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|val
)paren
)paren
(brace
id|val
op_increment
suffix:semicolon
id|linelen
op_decrement
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|entry-&gt;dest
comma
id|val
comma
id|linelen
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
id|Log
suffix:colon
r_if
c_cond
(paren
id|verbose
)paren
id|printf
c_func
(paren
l_string|&quot;# L: %s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;Members:&quot;
)paren
)paren
(brace
r_while
c_loop
(paren
id|loglen
op_logical_and
id|isspace
c_func
(paren
id|log
(braket
id|loglen
op_minus
l_int|1
)braket
)paren
)paren
id|log
(braket
op_decrement
id|loglen
)braket
op_assign
l_int|0
suffix:semicolon
id|prepare_commit
c_func
(paren
)paren
suffix:semicolon
id|state
op_assign
id|Members
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loglen
op_plus
id|linelen
op_plus
l_int|5
OG
r_sizeof
(paren
id|log
)paren
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|log
op_plus
id|loglen
comma
id|line
comma
id|linelen
)paren
suffix:semicolon
id|loglen
op_add_assign
id|linelen
suffix:semicolon
id|log
(braket
id|loglen
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|Members
suffix:colon
r_if
c_cond
(paren
id|verbose
)paren
id|printf
c_func
(paren
l_string|&quot;# M: %s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|linelen
)paren
(brace
id|commit
c_func
(paren
)paren
suffix:semicolon
id|state
op_assign
id|Header
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|update_file
c_func
(paren
id|line
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
