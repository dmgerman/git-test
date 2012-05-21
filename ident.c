multiline_comment|/*&n; * ident.c&n; *&n; * create git identifier lines of the form &quot;name &lt;email&gt; date&quot;&n; *&n; * Copyright (C) 2005 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|git_default_name
r_static
r_struct
id|strbuf
id|git_default_name
op_assign
id|STRBUF_INIT
suffix:semicolon
DECL|variable|git_default_email
r_static
r_struct
id|strbuf
id|git_default_email
op_assign
id|STRBUF_INIT
suffix:semicolon
DECL|variable|git_default_date
r_static
r_char
id|git_default_date
(braket
l_int|50
)braket
suffix:semicolon
DECL|variable|user_ident_explicitly_given
r_int
id|user_ident_explicitly_given
suffix:semicolon
macro_line|#ifdef NO_GECOS_IN_PWENT
DECL|macro|get_gecos
mdefine_line|#define get_gecos(ignored) &quot;&amp;&quot;
macro_line|#else
DECL|macro|get_gecos
mdefine_line|#define get_gecos(struct_passwd) ((struct_passwd)-&gt;pw_gecos)
macro_line|#endif
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
r_struct
id|strbuf
op_star
id|name
)paren
(brace
r_char
op_star
id|src
suffix:semicolon
multiline_comment|/* Traditionally GECOS field had office phone numbers etc, separated&n;&t; * with commas.  Also &amp; stands for capitalized form of the login name.&n;&t; */
r_for
c_loop
(paren
id|src
op_assign
id|get_gecos
c_func
(paren
id|w
)paren
suffix:semicolon
op_star
id|src
op_logical_and
op_star
id|src
op_ne
l_char|&squot;,&squot;
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
id|strbuf_addch
c_func
(paren
id|name
comma
id|ch
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* Sorry, Mr. McDonald... */
id|strbuf_addch
c_func
(paren
id|name
comma
id|toupper
c_func
(paren
op_star
id|w-&gt;pw_name
)paren
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|name
comma
id|w-&gt;pw_name
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|add_mailname_host
r_static
r_int
id|add_mailname_host
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
id|FILE
op_star
id|mailname
suffix:semicolon
id|mailname
op_assign
id|fopen
c_func
(paren
l_string|&quot;/etc/mailname&quot;
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mailname
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
id|warning
c_func
(paren
l_string|&quot;cannot open /etc/mailname: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
id|buf
comma
id|mailname
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
(brace
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|mailname
)paren
)paren
id|warning
c_func
(paren
l_string|&quot;cannot read /etc/mailname: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|mailname
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* success! */
id|fclose
c_func
(paren
id|mailname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_domainname
r_static
r_void
id|add_domainname
c_func
(paren
r_struct
id|strbuf
op_star
id|out
)paren
(brace
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|hostent
op_star
id|he
suffix:semicolon
r_const
r_char
op_star
id|domainname
suffix:semicolon
r_if
c_cond
(paren
id|gethostname
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;cannot get host name: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strbuf_addstr
c_func
(paren
id|out
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot;.&squot;
)paren
)paren
r_return
suffix:semicolon
id|he
op_assign
id|gethostbyname
c_func
(paren
id|buf
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|out
comma
l_char|&squot;.&squot;
)paren
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
id|strbuf_addstr
c_func
(paren
id|out
comma
id|domainname
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;(none)&quot;
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
comma
r_struct
id|strbuf
op_star
id|email
)paren
(brace
multiline_comment|/*&n;&t; * Make up a fake email address&n;&t; * (name + &squot;@&squot; + hostname [+ &squot;.&squot; + domainname])&n;&t; */
id|strbuf_addstr
c_func
(paren
id|email
comma
id|pw-&gt;pw_name
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|email
comma
l_char|&squot;@&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|add_mailname_host
c_func
(paren
id|email
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* read from &quot;/etc/mailname&quot; (Debian) */
id|add_domainname
c_func
(paren
id|email
)paren
suffix:semicolon
)brace
DECL|function|ident_default_name
r_const
r_char
op_star
id|ident_default_name
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_default_name.len
)paren
id|copy_gecos
c_func
(paren
id|xgetpwuid_self
c_func
(paren
)paren
comma
op_amp
id|git_default_name
)paren
suffix:semicolon
r_return
id|git_default_name.buf
suffix:semicolon
)brace
DECL|function|ident_default_email
r_const
r_char
op_star
id|ident_default_email
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_default_email.len
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
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|git_default_email
comma
id|email
)paren
suffix:semicolon
id|user_ident_explicitly_given
op_or_assign
id|IDENT_MAIL_GIVEN
suffix:semicolon
)brace
r_else
id|copy_email
c_func
(paren
id|xgetpwuid_self
c_func
(paren
)paren
comma
op_amp
id|git_default_email
)paren
suffix:semicolon
)brace
r_return
id|git_default_email.buf
suffix:semicolon
)brace
DECL|function|ident_default_date
r_const
r_char
op_star
id|ident_default_date
c_func
(paren
r_void
)paren
(brace
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
r_return
id|git_default_date
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
r_return
id|c
op_le
l_int|32
op_logical_or
id|c
op_eq
l_char|&squot;.&squot;
op_logical_or
id|c
op_eq
l_char|&squot;,&squot;
op_logical_or
id|c
op_eq
l_char|&squot;:&squot;
op_logical_or
id|c
op_eq
l_char|&squot;;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&lt;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&gt;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&quot;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;&squot;&squot;
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
multiline_comment|/*&n;&t; * Copy the rest to the buffer, but avoid the special&n;&t; * characters &squot;&bslash;n&squot; &squot;&lt;&squot; and &squot;&gt;&squot; that act as delimiters on&n;&t; * an identification line&n;&t; */
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
multiline_comment|/*&n; * Reverse of fmt_ident(); given an ident line, split the fields&n; * to allow the caller to parse it.&n; * Signal a success by returning 0, but date/tz fields of the result&n; * can still be NULL if the input line only has the name/email part&n; * (e.g. reading from a reflog entry).&n; */
DECL|function|split_ident_line
r_int
id|split_ident_line
c_func
(paren
r_struct
id|ident_split
op_star
id|split
comma
r_const
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_const
r_char
op_star
id|cp
suffix:semicolon
r_int
id|span
suffix:semicolon
r_int
id|status
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|split
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|split
)paren
)paren
suffix:semicolon
id|split-&gt;name_begin
op_assign
id|line
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|line
suffix:semicolon
op_star
id|cp
op_logical_and
id|cp
OL
id|line
op_plus
id|len
suffix:semicolon
id|cp
op_increment
)paren
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;&lt;&squot;
)paren
(brace
id|split-&gt;mail_begin
op_assign
id|cp
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|split-&gt;mail_begin
)paren
r_return
id|status
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|split-&gt;mail_begin
l_int|2
suffix:semicolon
id|line
OL
id|cp
suffix:semicolon
id|cp
op_decrement
)paren
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
op_star
id|cp
)paren
)paren
(brace
id|split-&gt;name_end
op_assign
id|cp
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|split-&gt;name_end
)paren
r_return
id|status
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|split-&gt;mail_begin
suffix:semicolon
id|cp
OL
id|line
op_plus
id|len
suffix:semicolon
id|cp
op_increment
)paren
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;&gt;&squot;
)paren
(brace
id|split-&gt;mail_end
op_assign
id|cp
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|split-&gt;mail_end
)paren
r_return
id|status
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|split-&gt;mail_end
op_plus
l_int|1
suffix:semicolon
id|cp
OL
id|line
op_plus
id|len
op_logical_and
id|isspace
c_func
(paren
op_star
id|cp
)paren
suffix:semicolon
id|cp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
op_plus
id|len
op_le
id|cp
)paren
r_goto
id|person_only
suffix:semicolon
id|split-&gt;date_begin
op_assign
id|cp
suffix:semicolon
id|span
op_assign
id|strspn
c_func
(paren
id|cp
comma
l_string|&quot;0123456789&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|span
)paren
r_goto
id|person_only
suffix:semicolon
id|split-&gt;date_end
op_assign
id|split-&gt;date_begin
op_plus
id|span
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|split-&gt;date_end
suffix:semicolon
id|cp
OL
id|line
op_plus
id|len
op_logical_and
id|isspace
c_func
(paren
op_star
id|cp
)paren
suffix:semicolon
id|cp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
op_plus
id|len
op_le
id|cp
op_logical_or
(paren
op_star
id|cp
op_ne
l_char|&squot;+&squot;
op_logical_and
op_star
id|cp
op_ne
l_char|&squot;-&squot;
)paren
)paren
r_goto
id|person_only
suffix:semicolon
id|split-&gt;tz_begin
op_assign
id|cp
suffix:semicolon
id|span
op_assign
id|strspn
c_func
(paren
id|cp
op_plus
l_int|1
comma
l_string|&quot;0123456789&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|span
)paren
r_goto
id|person_only
suffix:semicolon
id|split-&gt;tz_end
op_assign
id|split-&gt;tz_begin
op_plus
l_int|1
op_plus
id|span
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|person_only
suffix:colon
id|split-&gt;date_begin
op_assign
l_int|NULL
suffix:semicolon
id|split-&gt;date_end
op_assign
l_int|NULL
suffix:semicolon
id|split-&gt;tz_begin
op_assign
l_int|NULL
suffix:semicolon
id|split-&gt;tz_end
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|env_hint
r_static
r_const
r_char
op_star
id|env_hint
op_assign
l_string|&quot;&bslash;n&quot;
l_string|&quot;*** Please tell me who you are.&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;Run&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;  git config --global user.email &bslash;&quot;you@example.com&bslash;&quot;&bslash;n&quot;
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
id|flag
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
r_int
id|error_on_no_name
op_assign
(paren
id|flag
op_amp
id|IDENT_ERROR_ON_NO_NAME
)paren
suffix:semicolon
r_int
id|name_addr_only
op_assign
(paren
id|flag
op_amp
id|IDENT_NO_DATE
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
id|ident_default_name
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|email
)paren
id|email
op_assign
id|ident_default_email
c_func
(paren
)paren
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
id|error_on_no_name
)paren
(brace
r_if
c_cond
(paren
id|name
op_eq
id|git_default_name.buf
)paren
id|fputs
c_func
(paren
id|env_hint
comma
id|stderr
)paren
suffix:semicolon
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
)brace
id|pw
op_assign
id|xgetpwuid_self
c_func
(paren
)paren
suffix:semicolon
id|name
op_assign
id|pw-&gt;pw_name
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|date
comma
id|ident_default_date
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_addr_only
op_logical_and
id|date_str
op_logical_and
id|date_str
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
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
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;invalid date format: %s&quot;
comma
id|date_str
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|name_addr_only
)paren
(brace
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
)brace
r_else
(brace
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
l_string|&quot;&gt;&quot;
)paren
suffix:semicolon
)brace
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
DECL|function|fmt_name
r_const
r_char
op_star
id|fmt_name
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
)paren
(brace
r_return
id|fmt_ident
c_func
(paren
id|name
comma
id|email
comma
l_int|NULL
comma
id|IDENT_ERROR_ON_NO_NAME
op_or
id|IDENT_NO_DATE
)paren
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
id|flag
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
id|flag
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
id|flag
)paren
(brace
r_if
c_cond
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_COMMITTER_NAME&quot;
)paren
)paren
id|user_ident_explicitly_given
op_or_assign
id|IDENT_NAME_GIVEN
suffix:semicolon
r_if
c_cond
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_COMMITTER_EMAIL&quot;
)paren
)paren
id|user_ident_explicitly_given
op_or_assign
id|IDENT_MAIL_GIVEN
suffix:semicolon
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
id|flag
)paren
suffix:semicolon
)brace
DECL|function|user_ident_sufficiently_given
r_int
id|user_ident_sufficiently_given
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef WINDOWS
r_return
(paren
id|user_ident_explicitly_given
op_amp
id|IDENT_MAIL_GIVEN
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|user_ident_explicitly_given
op_eq
id|IDENT_ALL_GIVEN
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|git_ident_config
r_int
id|git_ident_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;user.name&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|git_default_name
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|git_default_name
comma
id|value
)paren
suffix:semicolon
id|user_ident_explicitly_given
op_or_assign
id|IDENT_NAME_GIVEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;user.email&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|git_default_email
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|git_default_email
comma
id|value
)paren
suffix:semicolon
id|user_ident_explicitly_given
op_or_assign
id|IDENT_MAIL_GIVEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
