macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;argv-array.h&quot;
DECL|variable|git_update_ref_usage
r_static
r_const
r_char
op_star
r_const
id|git_update_ref_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git update-ref [&lt;options&gt;] -d &lt;refname&gt; [&lt;old-val&gt;]&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git update-ref [&lt;options&gt;]    &lt;refname&gt; &lt;new-val&gt; [&lt;old-val&gt;]&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git update-ref [&lt;options&gt;] --stdin [-z]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|line_termination
r_static
r_char
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|update_flags
r_static
r_int
id|update_flags
suffix:semicolon
DECL|variable|msg
r_static
r_const
r_char
op_star
id|msg
suffix:semicolon
multiline_comment|/*&n; * Parse one whitespace- or NUL-terminated, possibly C-quoted argument&n; * and append the result to arg.  Return a pointer to the terminator.&n; * Die if there is an error in how the argument is C-quoted.  This&n; * function is only used if not -z.&n; */
DECL|function|parse_arg
r_static
r_const
r_char
op_star
id|parse_arg
c_func
(paren
r_const
r_char
op_star
id|next
comma
r_struct
id|strbuf
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
op_star
id|next
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
r_const
r_char
op_star
id|orig
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|unquote_c_style
c_func
(paren
id|arg
comma
id|next
comma
op_amp
id|next
)paren
)paren
id|die
c_func
(paren
l_string|&quot;badly quoted argument: %s&quot;
comma
id|orig
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|next
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|next
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unexpected character after quoted argument: %s&quot;
comma
id|orig
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
op_star
id|next
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|next
)paren
)paren
id|strbuf_addch
c_func
(paren
id|arg
comma
op_star
id|next
op_increment
)paren
suffix:semicolon
)brace
r_return
id|next
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse the reference name immediately after &quot;command SP&quot;.  If not&n; * -z, then handle C-quoting.  Return a pointer to a newly allocated&n; * string containing the name of the reference, or NULL if there was&n; * an error.  Update *next to point at the character that terminates&n; * the argument.  Die if C-quoting is malformed or the reference name&n; * is invalid.&n; */
DECL|function|parse_refname
r_static
r_char
op_star
id|parse_refname
c_func
(paren
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
op_star
id|next
)paren
(brace
r_struct
id|strbuf
id|ref
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|line_termination
)paren
(brace
multiline_comment|/* Without -z, use the next argument */
op_star
id|next
op_assign
id|parse_arg
c_func
(paren
op_star
id|next
comma
op_amp
id|ref
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* With -z, use everything up to the next NUL */
id|strbuf_addstr
c_func
(paren
op_amp
id|ref
comma
op_star
id|next
)paren
suffix:semicolon
op_star
id|next
op_add_assign
id|ref.len
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ref.len
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|ref
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_refname_format
c_func
(paren
id|ref.buf
comma
id|REFNAME_ALLOW_ONELEVEL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;invalid ref format: %s&quot;
comma
id|ref.buf
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|ref
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The value being parsed is &lt;oldvalue&gt; (as opposed to &lt;newvalue&gt;; the&n; * difference affects which error messages are generated):&n; */
DECL|macro|PARSE_SHA1_OLD
mdefine_line|#define PARSE_SHA1_OLD 0x01
multiline_comment|/*&n; * For backwards compatibility, accept an empty string for update&squot;s&n; * &lt;newvalue&gt; in binary mode to be equivalent to specifying zeros.&n; */
DECL|macro|PARSE_SHA1_ALLOW_EMPTY
mdefine_line|#define PARSE_SHA1_ALLOW_EMPTY 0x02
multiline_comment|/*&n; * Parse an argument separator followed by the next argument, if any.&n; * If there is an argument, convert it to a SHA-1, write it to sha1,&n; * set *next to point at the character terminating the argument, and&n; * return 0.  If there is no argument at all (not even the empty&n; * string), return 1 and leave *next unchanged.  If the value is&n; * provided but cannot be converted to a SHA-1, die.  flags can&n; * include PARSE_SHA1_OLD and/or PARSE_SHA1_ALLOW_EMPTY.&n; */
DECL|function|parse_next_sha1
r_static
r_int
id|parse_next_sha1
c_func
(paren
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
op_star
id|next
comma
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|command
comma
r_const
r_char
op_star
id|refname
comma
r_int
id|flags
)paren
(brace
r_struct
id|strbuf
id|arg
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|next
op_eq
id|input-&gt;buf
op_plus
id|input-&gt;len
)paren
r_goto
id|eof
suffix:semicolon
r_if
c_cond
(paren
id|line_termination
)paren
(brace
multiline_comment|/* Without -z, consume SP and use next argument */
r_if
c_cond
(paren
op_logical_neg
op_star
op_star
id|next
op_logical_or
op_star
op_star
id|next
op_eq
id|line_termination
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|next
op_ne
l_char|&squot; &squot;
)paren
id|die
c_func
(paren
l_string|&quot;%s %s: expected SP but got: %s&quot;
comma
id|command
comma
id|refname
comma
op_star
id|next
)paren
suffix:semicolon
(paren
op_star
id|next
)paren
op_increment
suffix:semicolon
op_star
id|next
op_assign
id|parse_arg
c_func
(paren
op_star
id|next
comma
op_amp
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg.len
)paren
(brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg.buf
comma
id|sha1
)paren
)paren
r_goto
id|invalid
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Without -z, an empty value means all zeros: */
id|hashclr
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* With -z, read the next NUL-terminated line */
r_if
c_cond
(paren
op_star
op_star
id|next
)paren
id|die
c_func
(paren
l_string|&quot;%s %s: expected NUL but got: %s&quot;
comma
id|command
comma
id|refname
comma
op_star
id|next
)paren
suffix:semicolon
(paren
op_star
id|next
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|next
op_eq
id|input-&gt;buf
op_plus
id|input-&gt;len
)paren
r_goto
id|eof
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|arg
comma
op_star
id|next
)paren
suffix:semicolon
op_star
id|next
op_add_assign
id|arg.len
suffix:semicolon
r_if
c_cond
(paren
id|arg.len
)paren
(brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg.buf
comma
id|sha1
)paren
)paren
r_goto
id|invalid
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|PARSE_SHA1_ALLOW_EMPTY
)paren
(brace
multiline_comment|/* With -z, treat an empty value as all zeros: */
id|warning
c_func
(paren
l_string|&quot;%s %s: missing &lt;newvalue&gt;, treating as zero&quot;
comma
id|command
comma
id|refname
)paren
suffix:semicolon
id|hashclr
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * With -z, an empty non-required value means&n;&t;&t;&t; * unspecified:&n;&t;&t;&t; */
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|arg
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|invalid
suffix:colon
id|die
c_func
(paren
id|flags
op_amp
id|PARSE_SHA1_OLD
ques
c_cond
l_string|&quot;%s %s: invalid &lt;oldvalue&gt;: %s&quot;
suffix:colon
l_string|&quot;%s %s: invalid &lt;newvalue&gt;: %s&quot;
comma
id|command
comma
id|refname
comma
id|arg.buf
)paren
suffix:semicolon
id|eof
suffix:colon
id|die
c_func
(paren
id|flags
op_amp
id|PARSE_SHA1_OLD
ques
c_cond
l_string|&quot;%s %s: unexpected end of input when reading &lt;oldvalue&gt;&quot;
suffix:colon
l_string|&quot;%s %s: unexpected end of input when reading &lt;newvalue&gt;&quot;
comma
id|command
comma
id|refname
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following five parse_cmd_*() functions parse the corresponding&n; * command.  In each case, next points at the character following the&n; * command name and the following space.  They each return a pointer&n; * to the character terminating the command, and die with an&n; * explanatory message if there are any parsing problems.  All of&n; * these functions handle either text or binary format input,&n; * depending on how line_termination is set.&n; */
DECL|function|parse_cmd_update
r_static
r_const
r_char
op_star
id|parse_cmd_update
c_func
(paren
r_struct
id|ref_transaction
op_star
id|transaction
comma
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
id|next
)paren
(brace
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_int
r_char
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|have_old
suffix:semicolon
id|refname
op_assign
id|parse_refname
c_func
(paren
id|input
comma
op_amp
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refname
)paren
id|die
c_func
(paren
l_string|&quot;update: missing &lt;ref&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_next_sha1
c_func
(paren
id|input
comma
op_amp
id|next
comma
id|new_sha1
comma
l_string|&quot;update&quot;
comma
id|refname
comma
id|PARSE_SHA1_ALLOW_EMPTY
)paren
)paren
id|die
c_func
(paren
l_string|&quot;update %s: missing &lt;newvalue&gt;&quot;
comma
id|refname
)paren
suffix:semicolon
id|have_old
op_assign
op_logical_neg
id|parse_next_sha1
c_func
(paren
id|input
comma
op_amp
id|next
comma
id|old_sha1
comma
l_string|&quot;update&quot;
comma
id|refname
comma
id|PARSE_SHA1_OLD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|next
op_ne
id|line_termination
)paren
id|die
c_func
(paren
l_string|&quot;update %s: extra input: %s&quot;
comma
id|refname
comma
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_transaction_update
c_func
(paren
id|transaction
comma
id|refname
comma
id|new_sha1
comma
id|old_sha1
comma
id|update_flags
comma
id|have_old
comma
id|msg
comma
op_amp
id|err
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
id|update_flags
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|refname
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
DECL|function|parse_cmd_create
r_static
r_const
r_char
op_star
id|parse_cmd_create
c_func
(paren
r_struct
id|ref_transaction
op_star
id|transaction
comma
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
id|next
)paren
(brace
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_int
r_char
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
id|refname
op_assign
id|parse_refname
c_func
(paren
id|input
comma
op_amp
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refname
)paren
id|die
c_func
(paren
l_string|&quot;create: missing &lt;ref&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_next_sha1
c_func
(paren
id|input
comma
op_amp
id|next
comma
id|new_sha1
comma
l_string|&quot;create&quot;
comma
id|refname
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
l_string|&quot;create %s: missing &lt;newvalue&gt;&quot;
comma
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|new_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;create %s: zero &lt;newvalue&gt;&quot;
comma
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|next
op_ne
id|line_termination
)paren
id|die
c_func
(paren
l_string|&quot;create %s: extra input: %s&quot;
comma
id|refname
comma
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_transaction_create
c_func
(paren
id|transaction
comma
id|refname
comma
id|new_sha1
comma
id|update_flags
comma
id|msg
comma
op_amp
id|err
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
id|update_flags
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|refname
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
DECL|function|parse_cmd_delete
r_static
r_const
r_char
op_star
id|parse_cmd_delete
c_func
(paren
r_struct
id|ref_transaction
op_star
id|transaction
comma
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
id|next
)paren
(brace
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|have_old
suffix:semicolon
id|refname
op_assign
id|parse_refname
c_func
(paren
id|input
comma
op_amp
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refname
)paren
id|die
c_func
(paren
l_string|&quot;delete: missing &lt;ref&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_next_sha1
c_func
(paren
id|input
comma
op_amp
id|next
comma
id|old_sha1
comma
l_string|&quot;delete&quot;
comma
id|refname
comma
id|PARSE_SHA1_OLD
)paren
)paren
(brace
id|have_old
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|old_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;delete %s: zero &lt;oldvalue&gt;&quot;
comma
id|refname
)paren
suffix:semicolon
id|have_old
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|next
op_ne
id|line_termination
)paren
id|die
c_func
(paren
l_string|&quot;delete %s: extra input: %s&quot;
comma
id|refname
comma
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_transaction_delete
c_func
(paren
id|transaction
comma
id|refname
comma
id|old_sha1
comma
id|update_flags
comma
id|have_old
comma
id|msg
comma
op_amp
id|err
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
id|update_flags
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|refname
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
DECL|function|parse_cmd_verify
r_static
r_const
r_char
op_star
id|parse_cmd_verify
c_func
(paren
r_struct
id|ref_transaction
op_star
id|transaction
comma
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
id|next
)paren
(brace
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_int
r_char
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
id|refname
op_assign
id|parse_refname
c_func
(paren
id|input
comma
op_amp
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refname
)paren
id|die
c_func
(paren
l_string|&quot;verify: missing &lt;ref&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_next_sha1
c_func
(paren
id|input
comma
op_amp
id|next
comma
id|old_sha1
comma
l_string|&quot;verify&quot;
comma
id|refname
comma
id|PARSE_SHA1_OLD
)paren
)paren
id|hashclr
c_func
(paren
id|old_sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|new_sha1
comma
id|old_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|next
op_ne
id|line_termination
)paren
id|die
c_func
(paren
l_string|&quot;verify %s: extra input: %s&quot;
comma
id|refname
comma
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_transaction_update
c_func
(paren
id|transaction
comma
id|refname
comma
id|new_sha1
comma
id|old_sha1
comma
id|update_flags
comma
l_int|1
comma
id|msg
comma
op_amp
id|err
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
id|update_flags
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|refname
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
DECL|function|parse_cmd_option
r_static
r_const
r_char
op_star
id|parse_cmd_option
c_func
(paren
r_struct
id|strbuf
op_star
id|input
comma
r_const
r_char
op_star
id|next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|next
comma
l_string|&quot;no-deref&quot;
comma
l_int|8
)paren
op_logical_and
id|next
(braket
l_int|8
)braket
op_eq
id|line_termination
)paren
id|update_flags
op_or_assign
id|REF_NODEREF
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;option unknown: %s&quot;
comma
id|next
)paren
suffix:semicolon
r_return
id|next
op_plus
l_int|8
suffix:semicolon
)brace
DECL|function|update_refs_stdin
r_static
r_void
id|update_refs_stdin
c_func
(paren
r_struct
id|ref_transaction
op_star
id|transaction
)paren
(brace
r_struct
id|strbuf
id|input
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|input
comma
l_int|0
comma
l_int|1000
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;could not read from stdin&quot;
)paren
suffix:semicolon
id|next
op_assign
id|input.buf
suffix:semicolon
multiline_comment|/* Read each line dispatch its command */
r_while
c_loop
(paren
id|next
OL
id|input.buf
op_plus
id|input.len
)paren
(brace
r_if
c_cond
(paren
op_star
id|next
op_eq
id|line_termination
)paren
id|die
c_func
(paren
l_string|&quot;empty command in input&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|isspace
c_func
(paren
op_star
id|next
)paren
)paren
id|die
c_func
(paren
l_string|&quot;whitespace before command: %s&quot;
comma
id|next
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|next
comma
l_string|&quot;update &quot;
)paren
)paren
id|next
op_assign
id|parse_cmd_update
c_func
(paren
id|transaction
comma
op_amp
id|input
comma
id|next
op_plus
l_int|7
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|next
comma
l_string|&quot;create &quot;
)paren
)paren
id|next
op_assign
id|parse_cmd_create
c_func
(paren
id|transaction
comma
op_amp
id|input
comma
id|next
op_plus
l_int|7
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|next
comma
l_string|&quot;delete &quot;
)paren
)paren
id|next
op_assign
id|parse_cmd_delete
c_func
(paren
id|transaction
comma
op_amp
id|input
comma
id|next
op_plus
l_int|7
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|next
comma
l_string|&quot;verify &quot;
)paren
)paren
id|next
op_assign
id|parse_cmd_verify
c_func
(paren
id|transaction
comma
op_amp
id|input
comma
id|next
op_plus
l_int|7
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|next
comma
l_string|&quot;option &quot;
)paren
)paren
id|next
op_assign
id|parse_cmd_option
c_func
(paren
op_amp
id|input
comma
id|next
op_plus
l_int|7
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;unknown command: %s&quot;
comma
id|next
)paren
suffix:semicolon
id|next
op_increment
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|input
)paren
suffix:semicolon
)brace
DECL|function|cmd_update_ref
r_int
id|cmd_update_ref
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
r_const
r_char
op_star
id|refname
comma
op_star
id|oldval
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|oldsha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_delete
op_assign
l_int|0
comma
id|no_deref
op_assign
l_int|0
comma
id|read_stdin
op_assign
l_int|0
comma
id|end_null
op_assign
l_int|0
comma
id|flags
op_assign
l_int|0
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
l_char|&squot;m&squot;
comma
l_int|NULL
comma
op_amp
id|msg
comma
id|N_
c_func
(paren
l_string|&quot;reason&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;reason of the update&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
r_delete
comma
id|N_
c_func
(paren
l_string|&quot;delete the reference&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;no-deref&quot;
comma
op_amp
id|no_deref
comma
id|N_
c_func
(paren
l_string|&quot;update &lt;refname&gt; not the one it points to&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;z&squot;
comma
l_int|NULL
comma
op_amp
id|end_null
comma
id|N_
c_func
(paren
l_string|&quot;stdin has NUL-terminated arguments&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|read_stdin
comma
id|N_
c_func
(paren
l_string|&quot;read updates from stdin&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
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
id|options
comma
id|git_update_ref_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_logical_and
op_logical_neg
op_star
id|msg
)paren
id|die
c_func
(paren
l_string|&quot;Refusing to perform update with empty message.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_stdin
)paren
(brace
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|ref_transaction
op_star
id|transaction
suffix:semicolon
id|transaction
op_assign
id|ref_transaction_begin
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transaction
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
r_delete
op_logical_or
id|no_deref
op_logical_or
id|argc
OG
l_int|0
)paren
id|usage_with_options
c_func
(paren
id|git_update_ref_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end_null
)paren
id|line_termination
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|update_refs_stdin
c_func
(paren
id|transaction
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_transaction_commit
c_func
(paren
id|transaction
comma
op_amp
id|err
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
id|ref_transaction_free
c_func
(paren
id|transaction
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end_null
)paren
id|usage_with_options
c_func
(paren
id|git_update_ref_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
r_delete
)paren
(brace
r_if
c_cond
(paren
id|argc
template_param
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|git_update_ref_usage
comma
id|options
)paren
suffix:semicolon
id|refname
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|oldval
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
op_star
id|value
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|3
)paren
id|usage_with_options
c_func
(paren
id|git_update_ref_usage
comma
id|options
)paren
suffix:semicolon
id|refname
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|value
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|oldval
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|value
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s: not a valid SHA1&quot;
comma
id|value
)paren
suffix:semicolon
)brace
id|hashclr
c_func
(paren
id|oldsha1
)paren
suffix:semicolon
multiline_comment|/* all-zero hash in case oldval is the empty string */
r_if
c_cond
(paren
id|oldval
op_logical_and
op_star
id|oldval
op_logical_and
id|get_sha1
c_func
(paren
id|oldval
comma
id|oldsha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s: not a valid old SHA1&quot;
comma
id|oldval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_deref
)paren
id|flags
op_assign
id|REF_NODEREF
suffix:semicolon
r_if
c_cond
(paren
r_delete
)paren
r_return
id|delete_ref
c_func
(paren
id|refname
comma
id|oldval
ques
c_cond
id|oldsha1
suffix:colon
l_int|NULL
comma
id|flags
)paren
suffix:semicolon
r_else
r_return
id|update_ref
c_func
(paren
id|msg
comma
id|refname
comma
id|sha1
comma
id|oldval
ques
c_cond
id|oldsha1
suffix:colon
l_int|NULL
comma
id|flags
comma
id|UPDATE_REFS_DIE_ON_ERR
)paren
suffix:semicolon
)brace
eof
