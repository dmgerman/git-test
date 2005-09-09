multiline_comment|/*&n; * ident.c&n; *&n; * create git identifier lines of the form &quot;name &lt;email&gt; date&quot;&n; *&n; * Copyright (C) 2005 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;pwd.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;ctype.h&gt;
DECL|variable|real_email
r_static
r_char
id|real_email
(braket
l_int|1000
)braket
suffix:semicolon
DECL|variable|real_name
r_static
r_char
id|real_name
(braket
l_int|1000
)braket
suffix:semicolon
DECL|variable|real_date
r_static
r_char
id|real_date
(braket
l_int|50
)braket
suffix:semicolon
DECL|function|setup_ident
r_int
id|setup_ident
c_func
(paren
r_void
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|passwd
op_star
id|pw
op_assign
id|getpwuid
c_func
(paren
id|getuid
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pw
)paren
id|die
c_func
(paren
l_string|&quot;You don&squot;t exist. Go away!&quot;
)paren
suffix:semicolon
multiline_comment|/* Get the name (&quot;gecos&quot;) */
id|len
op_assign
id|strlen
c_func
(paren
id|pw-&gt;pw_gecos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
r_sizeof
(paren
id|real_name
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Your parents must have hated you!&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|real_name
comma
id|pw-&gt;pw_gecos
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Make up a fake email address (name + &squot;@&squot; + hostname [+ &squot;.&squot; + domainname]) */
id|len
op_assign
id|strlen
c_func
(paren
id|pw-&gt;pw_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
id|real_email
)paren
op_div
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;Your sysadmin must hate you!&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|real_email
comma
id|pw-&gt;pw_name
comma
id|len
)paren
suffix:semicolon
id|real_email
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;@&squot;
suffix:semicolon
id|gethostname
c_func
(paren
id|real_email
op_plus
id|len
comma
r_sizeof
(paren
id|real_email
)paren
id|len
)paren
suffix:semicolon
macro_line|#ifndef NO_GETDOMAINNAME
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
id|real_email
op_plus
id|len
comma
l_char|&squot;.&squot;
)paren
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|real_email
)paren
suffix:semicolon
id|real_email
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
id|getdomainname
c_func
(paren
id|real_email
op_plus
id|len
comma
r_sizeof
(paren
id|real_email
)paren
op_minus
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* And set the default date */
id|datestamp
c_func
(paren
id|real_date
comma
r_sizeof
(paren
id|real_date
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_raw
r_static
r_int
id|add_raw
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|str
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_plus
id|len
OG
id|size
)paren
r_return
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|offset
comma
id|str
comma
id|len
)paren
suffix:semicolon
r_return
id|offset
op_plus
id|len
suffix:semicolon
)brace
DECL|function|crud
r_static
r_int
id|crud
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_static
r_char
id|crud_array
(braket
l_int|256
)braket
suffix:semicolon
r_static
r_int
id|crud_array_initialized
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|crud_array_initialized
)paren
(brace
r_int
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
op_le
l_int|31
suffix:semicolon
op_increment
id|k
)paren
id|crud_array
(braket
id|k
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot; &squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;.&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;,&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;:&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;;&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;&lt;&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;&gt;&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;&quot;&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array
(braket
l_char|&squot;&bslash;&squot;&squot;
)braket
op_assign
l_int|1
suffix:semicolon
id|crud_array_initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|crud_array
(braket
id|c
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy over a string to the destination, but avoid special&n; * characters (&squot;&bslash;n&squot;, &squot;&lt;&squot; and &squot;&gt;&squot;) and remove crud at the end&n; */
DECL|function|copy
r_static
r_int
id|copy
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
multiline_comment|/* Remove crud from the beginning.. */
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|crud
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
multiline_comment|/* Remove crud from the end.. */
id|len
op_assign
id|strlen
c_func
(paren
id|src
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|c
op_assign
id|src
(braket
id|len
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|crud
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
op_decrement
id|len
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Copy the rest to the buffer, but avoid the special&n;&t; * characters &squot;&bslash;n&squot; &squot;&lt;&squot; and &squot;&gt;&squot; that act as delimeters on&n;&t; * a identification line&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
r_case
l_char|&squot;&lt;&squot;
suffix:colon
r_case
l_char|&squot;&gt;&squot;
suffix:colon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ge
id|size
)paren
r_return
id|size
suffix:semicolon
id|buf
(braket
id|offset
op_increment
)braket
op_assign
id|c
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|get_ident
r_char
op_star
id|get_ident
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|email
comma
r_const
r_char
op_star
id|date_str
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
r_char
id|date
(braket
l_int|50
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
id|real_name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|email
)paren
id|email
op_assign
id|real_email
suffix:semicolon
id|strcpy
c_func
(paren
id|date
comma
id|real_date
)paren
suffix:semicolon
r_if
c_cond
(paren
id|date_str
)paren
id|parse_date
c_func
(paren
id|date_str
comma
id|date
comma
r_sizeof
(paren
id|date
)paren
)paren
suffix:semicolon
id|i
op_assign
id|copy
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
l_int|0
comma
id|name
)paren
suffix:semicolon
id|i
op_assign
id|add_raw
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|i
comma
l_string|&quot; &lt;&quot;
)paren
suffix:semicolon
id|i
op_assign
id|copy
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|i
comma
id|email
)paren
suffix:semicolon
id|i
op_assign
id|add_raw
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|i
comma
l_string|&quot;&gt; &quot;
)paren
suffix:semicolon
id|i
op_assign
id|copy
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|i
comma
id|date
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
r_sizeof
(paren
id|buffer
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Impossibly long personal identifier&quot;
)paren
suffix:semicolon
id|buffer
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|git_author_info
r_char
op_star
id|git_author_info
c_func
(paren
r_void
)paren
(brace
r_return
id|get_ident
c_func
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_AUTHOR_NAME&quot;
)paren
comma
id|getenv
c_func
(paren
l_string|&quot;GIT_AUTHOR_EMAIL&quot;
)paren
comma
id|getenv
c_func
(paren
l_string|&quot;GIT_AUTHOR_DATE&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|git_committer_info
r_char
op_star
id|git_committer_info
c_func
(paren
r_void
)paren
(brace
r_return
id|get_ident
c_func
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_COMMITTER_NAME&quot;
)paren
comma
id|getenv
c_func
(paren
l_string|&quot;GIT_COMMITTER_EMAIL&quot;
)paren
comma
id|getenv
c_func
(paren
l_string|&quot;GIT_COMMITTER_DATE&quot;
)paren
)paren
suffix:semicolon
)brace
eof
