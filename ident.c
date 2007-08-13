multiline_comment|/*&n; * ident.c&n; *&n; * create git identifier lines of the form &quot;name &lt;email&gt; date&quot;&n; *&n; * Copyright (C) 2005 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|git_default_date
r_static
r_char
id|git_default_date
(braket
l_int|50
)braket
suffix:semicolon
DECL|function|copy_gecos
r_static
r_void
id|copy_gecos
c_func
(paren
r_const
r_struct
id|passwd
op_star
id|w
comma
r_char
op_star
id|name
comma
r_int
id|sz
)paren
(brace
r_char
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_int
id|len
comma
id|nlen
suffix:semicolon
id|nlen
op_assign
id|strlen
c_func
(paren
id|w-&gt;pw_name
)paren
suffix:semicolon
multiline_comment|/* Traditionally GECOS field had office phone numbers etc, separated&n;&t; * with commas.  Also &amp; stands for capitalized form of the login name.&n;&t; */
r_for
c_loop
(paren
id|len
op_assign
l_int|0
comma
id|dst
op_assign
id|name
comma
id|src
op_assign
id|w-&gt;pw_gecos
suffix:semicolon
id|len
OL
id|sz
suffix:semicolon
id|src
op_increment
)paren
(brace
r_int
id|ch
op_assign
op_star
id|src
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ne
l_char|&squot;&amp;&squot;
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|0
op_logical_or
id|ch
op_eq
l_char|&squot;,&squot;
)paren
r_break
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_plus
id|nlen
OL
id|sz
)paren
(brace
multiline_comment|/* Sorry, Mr. McDonald... */
op_star
id|dst
op_increment
op_assign
id|toupper
c_func
(paren
op_star
id|w-&gt;pw_name
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|w-&gt;pw_name
op_plus
l_int|1
comma
id|nlen
l_int|1
)paren
suffix:semicolon
id|dst
op_add_assign
id|nlen
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
OL
id|sz
)paren
id|name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;Your parents must have hated you!&quot;
)paren
suffix:semicolon
)brace
DECL|function|copy_email
r_static
r_void
id|copy_email
c_func
(paren
r_const
r_struct
id|passwd
op_star
id|pw
)paren
(brace
multiline_comment|/*&n;&t; * Make up a fake email address&n;&t; * (name + &squot;@&squot; + hostname [+ &squot;.&squot; + domainname])&n;&t; */
r_int
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
id|git_default_email
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
id|git_default_email
comma
id|pw-&gt;pw_name
comma
id|len
)paren
suffix:semicolon
id|git_default_email
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
id|git_default_email
op_plus
id|len
comma
r_sizeof
(paren
id|git_default_email
)paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
id|git_default_email
op_plus
id|len
comma
l_char|&squot;.&squot;
)paren
)paren
(brace
r_struct
id|hostent
op_star
id|he
op_assign
id|gethostbyname
c_func
(paren
id|git_default_email
op_plus
id|len
)paren
suffix:semicolon
r_char
op_star
id|domainname
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|git_default_email
)paren
suffix:semicolon
id|git_default_email
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
r_if
c_cond
(paren
id|he
op_logical_and
(paren
id|domainname
op_assign
id|strchr
c_func
(paren
id|he-&gt;h_name
comma
l_char|&squot;.&squot;
)paren
)paren
)paren
id|strlcpy
c_func
(paren
id|git_default_email
op_plus
id|len
comma
id|domainname
op_plus
l_int|1
comma
r_sizeof
(paren
id|git_default_email
)paren
id|len
)paren
suffix:semicolon
r_else
id|strlcpy
c_func
(paren
id|git_default_email
op_plus
id|len
comma
l_string|&quot;(none)&quot;
comma
r_sizeof
(paren
id|git_default_email
)paren
id|len
)paren
suffix:semicolon
)brace
)brace
DECL|function|setup_ident
r_static
r_void
id|setup_ident
c_func
(paren
r_void
)paren
(brace
r_struct
id|passwd
op_star
id|pw
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Get the name (&quot;gecos&quot;) */
r_if
c_cond
(paren
op_logical_neg
id|git_default_name
(braket
l_int|0
)braket
)paren
(brace
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
id|copy_gecos
c_func
(paren
id|pw
comma
id|git_default_name
comma
r_sizeof
(paren
id|git_default_name
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|git_default_email
(braket
l_int|0
)braket
)paren
(brace
r_const
r_char
op_star
id|email
op_assign
id|getenv
c_func
(paren
l_string|&quot;EMAIL&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|email
op_logical_and
id|email
(braket
l_int|0
)braket
)paren
id|strlcpy
c_func
(paren
id|git_default_email
comma
id|email
comma
r_sizeof
(paren
id|git_default_email
)paren
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|pw
)paren
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
id|copy_email
c_func
(paren
id|pw
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* And set the default date */
r_if
c_cond
(paren
op_logical_neg
id|git_default_date
(braket
l_int|0
)braket
)paren
id|datestamp
c_func
(paren
id|git_default_date
comma
r_sizeof
(paren
id|git_default_date
)paren
)paren
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
multiline_comment|/*&n;&t; * Copy the rest to the buffer, but avoid the special&n;&t; * characters &squot;&bslash;n&squot; &squot;&lt;&squot; and &squot;&gt;&squot; that act as delimiters on&n;&t; * a identification line&n;&t; */
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
DECL|variable|au_env
r_static
r_const
r_char
id|au_env
(braket
)braket
op_assign
l_string|&quot;GIT_AUTHOR_NAME&quot;
suffix:semicolon
DECL|variable|co_env
r_static
r_const
r_char
id|co_env
(braket
)braket
op_assign
l_string|&quot;GIT_COMMITTER_NAME&quot;
suffix:semicolon
DECL|variable|env_hint
r_static
r_const
r_char
op_star
id|env_hint
op_assign
l_string|&quot;&bslash;n&quot;
l_string|&quot;*** Your name cannot be determined from your system services (gecos).&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;Run&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;  git config --global user.email &bslash;&quot;you@email.com&bslash;&quot;&bslash;n&quot;
l_string|&quot;  git config --global user.name &bslash;&quot;Your Name&bslash;&quot;&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;to set your account&bslash;&squot;s default identity.&bslash;n&quot;
l_string|&quot;Omit --global to set the identity only in this repository.&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
suffix:semicolon
DECL|function|fmt_ident
r_const
r_char
op_star
id|fmt_ident
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
comma
r_int
id|error_on_no_name
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
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
id|git_default_name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|email
)paren
id|email
op_assign
id|git_default_email
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|name
)paren
(brace
r_struct
id|passwd
op_star
id|pw
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|error_on_no_name
op_logical_and
id|name
op_eq
id|git_default_name
op_logical_and
id|env_hint
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
id|env_hint
comma
id|au_env
comma
id|co_env
)paren
suffix:semicolon
id|env_hint
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* warn only once, for &quot;git-var -l&quot; */
)brace
r_if
c_cond
(paren
l_int|0
OL
id|error_on_no_name
)paren
id|die
c_func
(paren
l_string|&quot;empty ident %s &lt;%s&gt; not allowed&quot;
comma
id|name
comma
id|email
)paren
suffix:semicolon
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
id|strlcpy
c_func
(paren
id|git_default_name
comma
id|pw-&gt;pw_name
comma
r_sizeof
(paren
id|git_default_name
)paren
)paren
suffix:semicolon
id|name
op_assign
id|git_default_name
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|date
comma
id|git_default_date
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
r_const
r_char
op_star
id|git_author_info
c_func
(paren
r_int
id|error_on_no_name
)paren
(brace
r_return
id|fmt_ident
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
comma
id|error_on_no_name
)paren
suffix:semicolon
)brace
DECL|function|git_committer_info
r_const
r_char
op_star
id|git_committer_info
c_func
(paren
r_int
id|error_on_no_name
)paren
(brace
r_return
id|fmt_ident
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
comma
id|error_on_no_name
)paren
suffix:semicolon
)brace
eof
