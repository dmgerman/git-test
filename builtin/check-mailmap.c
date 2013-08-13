macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;mailmap.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;string-list.h&quot;
DECL|variable|use_stdin
r_static
r_int
id|use_stdin
suffix:semicolon
DECL|variable|check_mailmap_usage
r_static
r_const
r_char
op_star
r_const
id|check_mailmap_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git check-mailmap [options] &lt;contact&gt;...&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|check_mailmap_options
r_static
r_const
r_struct
id|option
id|check_mailmap_options
(braket
)braket
op_assign
(brace
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|use_stdin
comma
id|N_
c_func
(paren
l_string|&quot;also read contacts from stdin&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
DECL|function|check_mailmap
r_static
r_void
id|check_mailmap
c_func
(paren
r_struct
id|string_list
op_star
id|mailmap
comma
r_const
r_char
op_star
id|contact
)paren
(brace
r_const
r_char
op_star
id|name
comma
op_star
id|mail
suffix:semicolon
r_int
id|namelen
comma
id|maillen
suffix:semicolon
r_struct
id|ident_split
id|ident
suffix:semicolon
r_if
c_cond
(paren
id|split_ident_line
c_func
(paren
op_amp
id|ident
comma
id|contact
comma
id|strlen
c_func
(paren
id|contact
)paren
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to parse contact: %s&quot;
)paren
comma
id|contact
)paren
suffix:semicolon
id|name
op_assign
id|ident.name_begin
suffix:semicolon
id|namelen
op_assign
id|ident.name_end
id|ident.name_begin
suffix:semicolon
id|mail
op_assign
id|ident.mail_begin
suffix:semicolon
id|maillen
op_assign
id|ident.mail_end
id|ident.mail_begin
suffix:semicolon
id|map_user
c_func
(paren
id|mailmap
comma
op_amp
id|mail
comma
op_amp
id|maillen
comma
op_amp
id|name
comma
op_amp
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namelen
)paren
id|printf
c_func
(paren
l_string|&quot;%.*s &quot;
comma
(paren
r_int
)paren
id|namelen
comma
id|name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&lt;%.*s&gt;&bslash;n&quot;
comma
(paren
r_int
)paren
id|maillen
comma
id|mail
)paren
suffix:semicolon
)brace
DECL|function|cmd_check_mailmap
r_int
id|cmd_check_mailmap
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|string_list
id|mailmap
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|check_mailmap_options
comma
id|check_mailmap_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
op_logical_and
op_logical_neg
id|use_stdin
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;no contacts specified&quot;
)paren
)paren
suffix:semicolon
id|read_mailmap
c_func
(paren
op_amp
id|mailmap
comma
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
op_increment
id|i
)paren
id|check_mailmap
c_func
(paren
op_amp
id|mailmap
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;stdout&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_stdin
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
id|check_mailmap
c_func
(paren
op_amp
id|mailmap
comma
id|buf.buf
)paren
suffix:semicolon
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;stdout&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
id|clear_mailmap
c_func
(paren
op_amp
id|mailmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof