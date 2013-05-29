macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;credential.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|credential_lock
r_static
r_struct
id|lock_file
id|credential_lock
suffix:semicolon
DECL|function|parse_credential_file
r_static
r_void
id|parse_credential_file
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_struct
id|credential
op_star
id|c
comma
r_void
(paren
op_star
id|match_cb
)paren
(paren
r_struct
id|credential
op_star
)paren
comma
r_void
(paren
op_star
id|other_cb
)paren
(paren
r_struct
id|strbuf
op_star
)paren
)paren
(brace
id|FILE
op_star
id|fh
suffix:semicolon
r_struct
id|strbuf
id|line
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|credential
id|entry
op_assign
id|CREDENTIAL_INIT
suffix:semicolon
id|fh
op_assign
id|fopen
c_func
(paren
id|fn
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fh
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to open %s&quot;
comma
id|fn
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|line
comma
id|fh
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
id|credential_from_url
c_func
(paren
op_amp
id|entry
comma
id|line.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry.username
op_logical_and
id|entry.password
op_logical_and
id|credential_match
c_func
(paren
id|c
comma
op_amp
id|entry
)paren
)paren
(brace
r_if
c_cond
(paren
id|match_cb
)paren
(brace
id|match_cb
c_func
(paren
op_amp
id|entry
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|other_cb
)paren
id|other_cb
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
)brace
id|credential_clear
c_func
(paren
op_amp
id|entry
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fh
)paren
suffix:semicolon
)brace
DECL|function|print_entry
r_static
r_void
id|print_entry
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;username=%s&bslash;n&quot;
comma
id|c-&gt;username
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;password=%s&bslash;n&quot;
comma
id|c-&gt;password
)paren
suffix:semicolon
)brace
DECL|function|print_line
r_static
r_void
id|print_line
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
id|strbuf_addch
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|credential_lock.fd
comma
id|buf-&gt;buf
comma
id|buf-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|rewrite_credential_file
r_static
r_void
id|rewrite_credential_file
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_struct
id|credential
op_star
id|c
comma
r_struct
id|strbuf
op_star
id|extra
)paren
(brace
r_if
c_cond
(paren
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|credential_lock
comma
id|fn
comma
l_int|0
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to get credential storage lock&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extra
)paren
id|print_line
c_func
(paren
id|extra
)paren
suffix:semicolon
id|parse_credential_file
c_func
(paren
id|fn
comma
id|c
comma
l_int|NULL
comma
id|print_line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_lock_file
c_func
(paren
op_amp
id|credential_lock
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to commit credential store&quot;
)paren
suffix:semicolon
)brace
DECL|function|store_credential
r_static
r_void
id|store_credential
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_struct
id|credential
op_star
id|c
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity check that what we are storing is actually sensible.&n;&t; * In particular, we can&squot;t make a URL without a protocol field.&n;&t; * Without either a host or pathname (depending on the scheme),&n;&t; * we have no primary key. And without a username and password,&n;&t; * we are not actually storing a credential.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;protocol
op_logical_or
op_logical_neg
(paren
id|c-&gt;host
op_logical_or
id|c-&gt;path
)paren
op_logical_or
op_logical_neg
id|c-&gt;username
op_logical_or
op_logical_neg
id|c-&gt;password
)paren
r_return
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%s://&quot;
comma
id|c-&gt;protocol
)paren
suffix:semicolon
id|strbuf_addstr_urlencode
c_func
(paren
op_amp
id|buf
comma
id|c-&gt;username
comma
l_int|1
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|strbuf_addstr_urlencode
c_func
(paren
op_amp
id|buf
comma
id|c-&gt;password
comma
l_int|1
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;@&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;host
)paren
id|strbuf_addstr_urlencode
c_func
(paren
op_amp
id|buf
comma
id|c-&gt;host
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;path
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|strbuf_addstr_urlencode
c_func
(paren
op_amp
id|buf
comma
id|c-&gt;path
comma
l_int|0
)paren
suffix:semicolon
)brace
id|rewrite_credential_file
c_func
(paren
id|fn
comma
id|c
comma
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|remove_credential
r_static
r_void
id|remove_credential
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_struct
id|credential
op_star
id|c
)paren
(brace
multiline_comment|/*&n;&t; * Sanity check that we actually have something to match&n;&t; * against. The input we get is a restrictive pattern,&n;&t; * so technically a blank credential means &quot;erase everything&quot;.&n;&t; * But it is too easy to accidentally send this, since it is equivalent&n;&t; * to empty input. So explicitly disallow it, and require that the&n;&t; * pattern have some actual content to match.&n;&t; */
r_if
c_cond
(paren
id|c-&gt;protocol
op_logical_or
id|c-&gt;host
op_logical_or
id|c-&gt;path
op_logical_or
id|c-&gt;username
)paren
id|rewrite_credential_file
c_func
(paren
id|fn
comma
id|c
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|lookup_credential
r_static
r_int
id|lookup_credential
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_struct
id|credential
op_star
id|c
)paren
(brace
id|parse_credential_file
c_func
(paren
id|fn
comma
id|c
comma
id|print_entry
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|c-&gt;username
op_logical_and
id|c-&gt;password
suffix:semicolon
)brace
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
r_const
r_char
op_star
r_const
id|usage
(braket
)braket
op_assign
(brace
l_string|&quot;git credential-store [options] &lt;action&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
id|op
suffix:semicolon
r_struct
id|credential
id|c
op_assign
id|CREDENTIAL_INIT
suffix:semicolon
r_char
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;file&quot;
comma
op_amp
id|file
comma
l_string|&quot;path&quot;
comma
l_string|&quot;fetch and store credentials in &lt;path&gt;&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|umask
c_func
(paren
l_int|077
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|argv
comma
l_int|NULL
comma
id|options
comma
id|usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|usage
comma
id|options
)paren
suffix:semicolon
id|op
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
id|file
op_assign
id|expand_user_path
c_func
(paren
l_string|&quot;~/.git-credentials&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
id|die
c_func
(paren
l_string|&quot;unable to set up default path; use --file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|credential_read
c_func
(paren
op_amp
id|c
comma
id|stdin
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to read credential&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|op
comma
l_string|&quot;get&quot;
)paren
)paren
id|lookup_credential
c_func
(paren
id|file
comma
op_amp
id|c
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|op
comma
l_string|&quot;erase&quot;
)paren
)paren
id|remove_credential
c_func
(paren
id|file
comma
op_amp
id|c
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|op
comma
l_string|&quot;store&quot;
)paren
)paren
id|store_credential
c_func
(paren
id|file
comma
op_amp
id|c
)paren
suffix:semicolon
r_else
suffix:semicolon
multiline_comment|/* Ignore unknown operation. */
r_return
l_int|0
suffix:semicolon
)brace
eof
