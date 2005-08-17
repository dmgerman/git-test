multiline_comment|/*&n; * Another stupid program, this one parsing the headers of an&n; * email to figure out authorship and subject&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;ctype.h&gt;
DECL|variable|cmitmsg
DECL|variable|patchfile
r_static
id|FILE
op_star
id|cmitmsg
comma
op_star
id|patchfile
suffix:semicolon
DECL|variable|keep_subject
r_static
r_int
id|keep_subject
op_assign
l_int|0
suffix:semicolon
DECL|variable|line
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
DECL|variable|date
r_static
r_char
id|date
(braket
l_int|1000
)braket
suffix:semicolon
DECL|variable|name
r_static
r_char
id|name
(braket
l_int|1000
)braket
suffix:semicolon
DECL|variable|email
r_static
r_char
id|email
(braket
l_int|1000
)braket
suffix:semicolon
DECL|variable|subject
r_static
r_char
id|subject
(braket
l_int|1000
)braket
suffix:semicolon
DECL|function|sanity_check
r_static
r_char
op_star
id|sanity_check
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|email
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
template_param
l_int|60
)paren
r_return
id|email
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;@&squot;
)paren
op_logical_or
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;&lt;&squot;
)paren
op_logical_or
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;&gt;&squot;
)paren
)paren
r_return
id|email
suffix:semicolon
r_return
id|name
suffix:semicolon
)brace
DECL|function|handle_from
r_static
r_int
id|handle_from
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_char
op_star
id|at
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;@&squot;
)paren
suffix:semicolon
r_char
op_star
id|dst
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|at
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If we already have one email, don&squot;t take any confusing lines&n;&t; */
r_if
c_cond
(paren
op_star
id|email
op_logical_and
id|strchr
c_func
(paren
id|at
op_plus
l_int|1
comma
l_char|&squot;@&squot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|at
OG
id|line
)paren
(brace
r_char
id|c
op_assign
id|at
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|c
)paren
op_logical_or
id|c
op_eq
l_char|&squot;&lt;&squot;
)paren
r_break
suffix:semicolon
id|at
op_decrement
suffix:semicolon
)brace
id|dst
op_assign
id|email
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|at
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
id|c
op_eq
l_char|&squot;&gt;&squot;
op_logical_or
id|isspace
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
op_star
id|at
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
)brace
op_star
id|dst
op_increment
op_assign
l_int|0
suffix:semicolon
id|at
op_assign
id|line
op_plus
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_while
c_loop
(paren
id|at
OG
id|line
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
op_decrement
id|at
suffix:semicolon
r_if
c_cond
(paren
id|isalnum
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
op_star
id|at
op_assign
l_int|0
suffix:semicolon
)brace
id|at
op_assign
id|line
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|at
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|isalnum
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|at
op_increment
suffix:semicolon
)brace
id|at
op_assign
id|sanity_check
c_func
(paren
id|at
comma
id|email
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|name
comma
id|at
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|handle_date
r_static
r_void
id|handle_date
c_func
(paren
r_char
op_star
id|line
)paren
(brace
id|strcpy
c_func
(paren
id|date
comma
id|line
)paren
suffix:semicolon
)brace
DECL|function|handle_subject
r_static
r_void
id|handle_subject
c_func
(paren
r_char
op_star
id|line
)paren
(brace
id|strcpy
c_func
(paren
id|subject
comma
id|line
)paren
suffix:semicolon
)brace
DECL|function|check_line
r_static
r_void
id|check_line
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;From:&quot;
comma
l_int|5
)paren
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
l_int|5
)braket
)paren
)paren
id|handle_from
c_func
(paren
id|line
op_plus
l_int|6
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;Date:&quot;
comma
l_int|5
)paren
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
l_int|5
)braket
)paren
)paren
id|handle_date
c_func
(paren
id|line
op_plus
l_int|6
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;Subject:&quot;
comma
l_int|8
)paren
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
l_int|8
)braket
)paren
)paren
id|handle_subject
c_func
(paren
id|line
op_plus
l_int|9
)paren
suffix:semicolon
)brace
DECL|function|cleanup_subject
r_static
r_char
op_star
id|cleanup_subject
c_func
(paren
r_char
op_star
id|subject
)paren
(brace
r_if
c_cond
(paren
id|keep_subject
)paren
r_return
id|subject
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
id|len
comma
id|remove
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|subject
)paren
(brace
r_case
l_char|&squot;r&squot;
suffix:colon
r_case
l_char|&squot;R&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;e:&quot;
comma
id|subject
op_plus
l_int|1
comma
l_int|2
)paren
)paren
(brace
id|subject
op_add_assign
l_int|3
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
r_case
l_char|&squot;:&squot;
suffix:colon
id|subject
op_increment
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;[&squot;
suffix:colon
id|p
op_assign
id|strchr
c_func
(paren
id|subject
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|subject
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|p
)paren
suffix:semicolon
id|remove
op_assign
id|p
id|subject
suffix:semicolon
r_if
c_cond
(paren
id|remove
op_le
id|len
op_star
l_int|2
)paren
(brace
id|subject
op_assign
id|p
op_plus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|subject
suffix:semicolon
)brace
)brace
DECL|function|cleanup_space
r_static
r_void
id|cleanup_space
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|buf
)paren
op_ne
l_int|0
)paren
(brace
id|buf
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|c
)paren
)paren
(brace
id|buf
(braket
l_int|1
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|c
op_assign
op_star
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|c
)paren
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|buf
comma
id|buf
op_plus
l_int|1
comma
id|len
)paren
suffix:semicolon
id|c
op_assign
op_star
id|buf
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|handle_rest
r_static
r_void
id|handle_rest
c_func
(paren
r_void
)paren
(brace
id|FILE
op_star
id|out
op_assign
id|cmitmsg
suffix:semicolon
r_char
op_star
id|sub
op_assign
id|cleanup_subject
c_func
(paren
id|subject
)paren
suffix:semicolon
id|cleanup_space
c_func
(paren
id|name
)paren
suffix:semicolon
id|cleanup_space
c_func
(paren
id|date
)paren
suffix:semicolon
id|cleanup_space
c_func
(paren
id|email
)paren
suffix:semicolon
id|cleanup_space
c_func
(paren
id|sub
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Author: %s&bslash;nEmail: %s&bslash;nSubject: %s&bslash;nDate: %s&bslash;n&bslash;n&quot;
comma
id|name
comma
id|email
comma
id|sub
comma
id|date
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;diff -&quot;
comma
id|line
comma
l_int|6
)paren
op_logical_or
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;---&quot;
comma
id|line
comma
l_int|3
)paren
op_logical_or
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;Index: &quot;
comma
id|line
comma
l_int|7
)paren
)paren
id|out
op_assign
id|patchfile
suffix:semicolon
id|fputs
c_func
(paren
id|line
comma
id|out
)paren
suffix:semicolon
)brace
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
suffix:semicolon
r_if
c_cond
(paren
id|out
op_eq
id|cmitmsg
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No patch found&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|cmitmsg
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|patchfile
)paren
suffix:semicolon
)brace
DECL|function|eatspace
r_static
r_int
id|eatspace
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|len
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
id|len
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
)paren
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|handle_body
r_static
r_void
id|handle_body
c_func
(paren
r_void
)paren
(brace
r_int
id|has_from
op_assign
l_int|0
suffix:semicolon
r_int
id|has_date
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First lines of body can have From: and Date: */
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
id|len
op_assign
id|eatspace
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;From:&quot;
comma
id|line
comma
l_int|5
)paren
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
l_int|5
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|has_from
op_logical_and
id|handle_from
c_func
(paren
id|line
op_plus
l_int|6
)paren
)paren
(brace
id|has_from
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;Date:&quot;
comma
id|line
comma
l_int|5
)paren
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
l_int|5
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|has_date
)paren
(brace
id|handle_date
c_func
(paren
id|line
op_plus
l_int|6
)paren
suffix:semicolon
id|has_date
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|line
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|handle_rest
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|read_one_header_line
r_static
r_int
id|read_one_header_line
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|sz
comma
id|FILE
op_star
id|in
)paren
(brace
r_int
id|ofs
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ofs
OL
id|sz
)paren
(brace
r_int
id|peek
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
id|fgets
c_func
(paren
id|line
op_plus
id|ofs
comma
id|sz
id|ofs
comma
id|in
)paren
op_eq
l_int|NULL
)paren
r_return
id|ofs
suffix:semicolon
id|len
op_assign
id|eatspace
c_func
(paren
id|line
op_plus
id|ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
id|ofs
suffix:semicolon
id|peek
op_assign
id|fgetc
c_func
(paren
id|in
)paren
suffix:semicolon
id|ungetc
c_func
(paren
id|peek
comma
id|in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peek
op_eq
l_char|&squot; &squot;
op_logical_or
id|peek
op_eq
l_char|&squot;&bslash;t&squot;
)paren
(brace
multiline_comment|/* Yuck, 2822 header &quot;folding&quot; */
id|ofs
op_add_assign
id|len
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_return
id|ofs
op_plus
id|len
suffix:semicolon
)brace
r_return
id|ofs
suffix:semicolon
)brace
DECL|function|usage
r_static
r_void
id|usage
c_func
(paren
r_void
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;mailinfo msg-file patch-file &lt; email&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|mailinfo_usage
r_static
r_const
r_char
id|mailinfo_usage
(braket
)braket
op_assign
l_string|&quot;git-mailinfo [-k] msg patch &lt;mail &gt;info&quot;
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
r_while
c_loop
(paren
l_int|1
OL
id|argc
op_logical_and
id|argv
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
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
l_int|1
)braket
comma
l_string|&quot;-k&quot;
)paren
)paren
id|keep_subject
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s&bslash;n&quot;
comma
id|mailinfo_usage
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
)paren
id|usage
c_func
(paren
)paren
suffix:semicolon
id|cmitmsg
op_assign
id|fopen
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmitmsg
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|patchfile
op_assign
id|fopen
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|patchfile
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|len
op_assign
id|read_one_header_line
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
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
id|handle_body
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|check_line
c_func
(paren
id|line
comma
id|len
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
