macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|quote_path_fully
r_int
id|quote_path_fully
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Help to copy the thing properly quoted for the shell safety.&n; * any single quote is replaced with &squot;&bslash;&squot;&squot;, any exclamation point&n; * is replaced with &squot;&bslash;!&squot;, and the whole thing is enclosed in a&n; *&n; * E.g.&n; *  original     sq_quote     result&n; *  name     ==&gt; name      ==&gt; &squot;name&squot;&n; *  a b      ==&gt; a b       ==&gt; &squot;a b&squot;&n; *  a&squot;b      ==&gt; a&squot;&bslash;&squot;&squot;b    ==&gt; &squot;a&squot;&bslash;&squot;&squot;b&squot;&n; *  a!b      ==&gt; a&squot;&bslash;!&squot;b    ==&gt; &squot;a&squot;&bslash;!&squot;b&squot;&n; */
DECL|function|need_bs_quote
r_static
r_inline
r_int
id|need_bs_quote
c_func
(paren
r_char
id|c
)paren
(brace
r_return
(paren
id|c
op_eq
l_char|&squot;&bslash;&squot;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;!&squot;
)paren
suffix:semicolon
)brace
DECL|function|sq_quote_buf
r_void
id|sq_quote_buf
c_func
(paren
r_struct
id|strbuf
op_star
id|dst
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|to_free
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;buf
op_eq
id|src
)paren
id|to_free
op_assign
id|strbuf_detach
c_func
(paren
id|dst
comma
l_int|NULL
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|dst
comma
l_char|&squot;&bslash;&squot;&squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|src
)paren
(brace
r_int
id|len
op_assign
id|strcspn
c_func
(paren
id|src
comma
l_string|&quot;&squot;!&quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|src
op_add_assign
id|len
suffix:semicolon
r_while
c_loop
(paren
id|need_bs_quote
c_func
(paren
op_star
id|src
)paren
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|dst
comma
l_string|&quot;&squot;&bslash;&bslash;&quot;
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|dst
comma
op_star
id|src
op_increment
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|dst
comma
l_char|&squot;&bslash;&squot;&squot;
)paren
suffix:semicolon
)brace
)brace
id|strbuf_addch
c_func
(paren
id|dst
comma
l_char|&squot;&bslash;&squot;&squot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|to_free
)paren
suffix:semicolon
)brace
DECL|function|sq_quote_print
r_void
id|sq_quote_print
c_func
(paren
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
id|c
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
comma
id|stream
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|need_bs_quote
c_func
(paren
id|c
)paren
)paren
(brace
id|fputs
c_func
(paren
l_string|&quot;&squot;&bslash;&bslash;&quot;
comma
id|stream
)paren
suffix:semicolon
id|fputc
c_func
(paren
id|c
comma
id|stream
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
comma
id|stream
)paren
suffix:semicolon
)brace
r_else
(brace
id|fputc
c_func
(paren
id|c
comma
id|stream
)paren
suffix:semicolon
)brace
)brace
id|fputc
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
comma
id|stream
)paren
suffix:semicolon
)brace
DECL|function|sq_quote_argv
r_void
id|sq_quote_argv
c_func
(paren
r_struct
id|strbuf
op_star
id|dst
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_int
id|maxlen
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Copy into destination buffer. */
id|strbuf_grow
c_func
(paren
id|dst
comma
l_int|255
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|argv
(braket
id|i
)braket
suffix:semicolon
op_increment
id|i
)paren
(brace
id|strbuf_addch
c_func
(paren
id|dst
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|sq_quote_buf
c_func
(paren
id|dst
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxlen
op_logical_and
id|dst-&gt;len
OG
id|maxlen
)paren
id|die
c_func
(paren
l_string|&quot;Too many or long arguments&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|sq_dequote
r_char
op_star
id|sq_dequote
c_func
(paren
r_char
op_star
id|arg
)paren
(brace
r_char
op_star
id|dst
op_assign
id|arg
suffix:semicolon
r_char
op_star
id|src
op_assign
id|arg
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_star
id|src
op_ne
l_char|&squot;&bslash;&squot;&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
op_star
op_increment
id|src
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;&squot;&squot;
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* We stepped out of sq */
r_switch
c_cond
(paren
op_star
op_increment
id|src
)paren
(brace
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
op_star
id|dst
op_assign
l_int|0
suffix:semicolon
r_return
id|arg
suffix:semicolon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
id|c
op_assign
op_star
op_increment
id|src
suffix:semicolon
r_if
c_cond
(paren
id|need_bs_quote
c_func
(paren
id|c
)paren
op_logical_and
op_star
op_increment
id|src
op_eq
l_char|&squot;&bslash;&squot;&squot;
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Fallthrough */
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* 1 means: quote as octal&n; * 0 means: quote as octal if (quote_path_fully)&n; * -1 means: never quote&n; * c: quote as &quot;&bslash;&bslash;c&quot;&n; */
DECL|macro|X8
mdefine_line|#define X8(x)   x, x, x, x, x, x, x, x
DECL|macro|X16
mdefine_line|#define X16(x)  X8(x), X8(x)
DECL|variable|sq_lookup
r_static
r_int
r_char
r_const
id|sq_lookup
(braket
l_int|256
)braket
op_assign
(brace
multiline_comment|/*           0    1    2    3    4    5    6    7 */
multiline_comment|/* 0x00 */
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_char|&squot;a&squot;
comma
multiline_comment|/* 0x08 */
l_char|&squot;b&squot;
comma
l_char|&squot;t&squot;
comma
l_char|&squot;n&squot;
comma
l_char|&squot;v&squot;
comma
l_char|&squot;f&squot;
comma
l_char|&squot;r&squot;
comma
l_int|1
comma
l_int|1
comma
multiline_comment|/* 0x10 */
id|X16
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* 0x20 */
l_int|1
comma
l_int|1
comma
l_char|&squot;&quot;&squot;
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
multiline_comment|/* 0x28 */
id|X16
c_func
(paren
l_int|1
)paren
comma
id|X16
c_func
(paren
l_int|1
)paren
comma
id|X16
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* 0x58 */
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_char|&squot;&bslash;&bslash;&squot;
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
multiline_comment|/* 0x60 */
id|X16
c_func
(paren
l_int|1
)paren
comma
id|X8
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* 0x78 */
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
multiline_comment|/* 0x80 */
multiline_comment|/* set to 0 */
)brace
suffix:semicolon
DECL|function|sq_must_quote
r_static
r_inline
r_int
id|sq_must_quote
c_func
(paren
r_char
id|c
)paren
(brace
r_return
id|sq_lookup
(braket
(paren
r_int
r_char
)paren
id|c
)braket
op_plus
id|quote_path_fully
OG
l_int|0
suffix:semicolon
)brace
multiline_comment|/* returns the longest prefix not needing a quote up to maxlen if positive.&n;   This stops at the first &bslash;0 because it&squot;s marked as a character needing an&n;   escape */
DECL|function|next_quote_pos
r_static
r_int
id|next_quote_pos
c_func
(paren
r_const
r_char
op_star
id|s
comma
id|ssize_t
id|maxlen
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|maxlen
OL
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|sq_must_quote
c_func
(paren
id|s
(braket
id|len
)braket
)paren
suffix:semicolon
id|len
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
id|maxlen
op_logical_and
op_logical_neg
id|sq_must_quote
c_func
(paren
id|s
(braket
id|len
)braket
)paren
suffix:semicolon
id|len
op_increment
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * C-style name quoting.&n; *&n; * (1) if sb and fp are both NULL, inspect the input name and counts the&n; *     number of bytes that are needed to hold c_style quoted version of name,&n; *     counting the double quotes around it but not terminating NUL, and&n; *     returns it.&n; *     However, if name does not need c_style quoting, it returns 0.&n; *&n; * (2) if sb or fp are not NULL, it emits the c_style quoted version&n; *     of name, enclosed with double quotes if asked and needed only.&n; *     Return value is the same as in (1).&n; */
DECL|function|quote_c_style_counted
r_static
r_int
id|quote_c_style_counted
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|ssize_t
id|maxlen
comma
r_struct
id|strbuf
op_star
id|sb
comma
id|FILE
op_star
id|fp
comma
r_int
id|no_dq
)paren
(brace
DECL|macro|EMIT
macro_line|#undef EMIT
DECL|macro|EMIT
mdefine_line|#define EMIT(c)                                 &bslash;&n;&t;do {                                        &bslash;&n;&t;&t;if (sb) strbuf_addch(sb, (c));          &bslash;&n;&t;&t;if (fp) fputc((c), fp);                 &bslash;&n;&t;&t;count++;                                &bslash;&n;&t;} while (0)
DECL|macro|EMITBUF
mdefine_line|#define EMITBUF(s, l)                           &bslash;&n;&t;do {                                        &bslash;&n;&t;&t;if (sb) strbuf_add(sb, (s), (l));       &bslash;&n;&t;&t;if (fp) fwrite((s), (l), 1, fp);        &bslash;&n;&t;&t;count += (l);                           &bslash;&n;&t;} while (0)
r_int
id|len
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
id|name
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|ch
suffix:semicolon
id|len
op_assign
id|next_quote_pos
c_func
(paren
id|p
comma
id|maxlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|maxlen
op_logical_or
op_logical_neg
id|p
(braket
id|len
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_dq
op_logical_and
id|p
op_eq
id|name
)paren
id|EMIT
c_func
(paren
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
id|EMITBUF
c_func
(paren
id|p
comma
id|len
)paren
suffix:semicolon
id|EMIT
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
)paren
suffix:semicolon
id|p
op_add_assign
id|len
suffix:semicolon
id|ch
op_assign
(paren
r_int
r_char
)paren
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sq_lookup
(braket
id|ch
)braket
op_ge
l_char|&squot; &squot;
)paren
(brace
id|EMIT
c_func
(paren
id|sq_lookup
(braket
id|ch
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|EMIT
c_func
(paren
(paren
(paren
id|ch
op_rshift
l_int|6
)paren
op_amp
l_int|03
)paren
op_plus
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|EMIT
c_func
(paren
(paren
(paren
id|ch
op_rshift
l_int|3
)paren
op_amp
l_int|07
)paren
op_plus
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|EMIT
c_func
(paren
(paren
(paren
id|ch
op_rshift
l_int|0
)paren
op_amp
l_int|07
)paren
op_plus
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
)brace
id|EMITBUF
c_func
(paren
id|p
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|name
)paren
multiline_comment|/* no ending quote needed */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_dq
)paren
id|EMIT
c_func
(paren
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|quote_c_style
r_int
id|quote_c_style
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|strbuf
op_star
id|sb
comma
id|FILE
op_star
id|fp
comma
r_int
id|nodq
)paren
(brace
r_return
id|quote_c_style_counted
c_func
(paren
id|name
comma
l_int|1
comma
id|sb
comma
id|fp
comma
id|nodq
)paren
suffix:semicolon
)brace
DECL|function|quote_two_c_style
r_void
id|quote_two_c_style
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|path
comma
r_int
id|nodq
)paren
(brace
r_if
c_cond
(paren
id|quote_c_style
c_func
(paren
id|prefix
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
op_logical_or
id|quote_c_style
c_func
(paren
id|path
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nodq
)paren
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
id|quote_c_style
c_func
(paren
id|prefix
comma
id|sb
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
id|quote_c_style
c_func
(paren
id|path
comma
id|sb
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nodq
)paren
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|prefix
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|path
)paren
suffix:semicolon
)brace
)brace
DECL|function|write_name_quoted
r_void
id|write_name_quoted
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|FILE
op_star
id|fp
comma
r_int
id|terminator
)paren
(brace
r_if
c_cond
(paren
id|terminator
)paren
(brace
id|quote_c_style
c_func
(paren
id|name
comma
l_int|NULL
comma
id|fp
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|fputs
c_func
(paren
id|name
comma
id|fp
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
id|terminator
comma
id|fp
)paren
suffix:semicolon
)brace
DECL|function|write_name_quotedpfx
r_extern
r_void
id|write_name_quotedpfx
c_func
(paren
r_const
r_char
op_star
id|pfx
comma
r_int
id|pfxlen
comma
r_const
r_char
op_star
id|name
comma
id|FILE
op_star
id|fp
comma
r_int
id|terminator
)paren
(brace
r_int
id|needquote
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|terminator
)paren
(brace
id|needquote
op_assign
id|next_quote_pos
c_func
(paren
id|pfx
comma
id|pfxlen
)paren
OL
id|pfxlen
op_logical_or
id|name
(braket
id|next_quote_pos
c_func
(paren
id|name
comma
l_int|1
)paren
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|needquote
)paren
(brace
id|fputc
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|fp
)paren
suffix:semicolon
id|quote_c_style_counted
c_func
(paren
id|pfx
comma
id|pfxlen
comma
l_int|NULL
comma
id|fp
comma
l_int|1
)paren
suffix:semicolon
id|quote_c_style
c_func
(paren
id|name
comma
l_int|NULL
comma
id|fp
comma
l_int|1
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|fp
)paren
suffix:semicolon
)brace
r_else
(brace
id|fwrite
c_func
(paren
id|pfx
comma
id|pfxlen
comma
l_int|1
comma
id|fp
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|name
comma
id|fp
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
id|terminator
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* quote path as relative to the given prefix */
DECL|function|quote_path_relative
r_char
op_star
id|quote_path_relative
c_func
(paren
r_const
r_char
op_star
id|in
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|out
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|needquote
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
id|strlen
c_func
(paren
id|in
)paren
suffix:semicolon
multiline_comment|/* &quot;../&quot; prefix itself does not need quoting, but &quot;in&quot; might. */
id|needquote
op_assign
id|next_quote_pos
c_func
(paren
id|in
comma
id|len
)paren
OL
id|len
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|out
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|out
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|needquote
)paren
id|strbuf_addch
c_func
(paren
id|out
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_int
id|off
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|prefix
(braket
id|off
)braket
op_logical_and
id|off
OL
id|len
op_logical_and
id|prefix
(braket
id|off
)braket
op_eq
id|in
(braket
id|off
)braket
)paren
r_if
c_cond
(paren
id|prefix
(braket
id|off
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|prefix
op_add_assign
id|off
op_plus
l_int|1
suffix:semicolon
id|in
op_add_assign
id|off
op_plus
l_int|1
suffix:semicolon
id|len
op_sub_assign
id|off
op_plus
l_int|1
suffix:semicolon
id|off
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|off
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|prefix
suffix:semicolon
id|prefix
op_increment
)paren
r_if
c_cond
(paren
op_star
id|prefix
op_eq
l_char|&squot;/&squot;
)paren
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;../&quot;
)paren
suffix:semicolon
)brace
id|quote_c_style_counted
(paren
id|in
comma
id|len
comma
id|out
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|needquote
)paren
id|strbuf_addch
c_func
(paren
id|out
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out-&gt;len
)paren
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;./&quot;
)paren
suffix:semicolon
r_return
id|out-&gt;buf
suffix:semicolon
)brace
multiline_comment|/*&n; * C-style name unquoting.&n; *&n; * Quoted should point at the opening double quote.&n; * + Returns 0 if it was able to unquote the string properly, and appends the&n; *   result in the strbuf `sb&squot;.&n; * + Returns -1 in case of error, and doesn&squot;t touch the strbuf. Though note&n; *   that this function will allocate memory in the strbuf, so calling&n; *   strbuf_release is mandatory whichever result unquote_c_style returns.&n; *&n; * Updates endp pointer to point at one past the ending double quote if given.&n; */
DECL|function|unquote_c_style
r_int
id|unquote_c_style
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|quoted
comma
r_const
r_char
op_star
op_star
id|endp
)paren
(brace
r_int
id|oldlen
op_assign
id|sb-&gt;len
comma
id|len
suffix:semicolon
r_int
id|ch
comma
id|ac
suffix:semicolon
r_if
c_cond
(paren
op_star
id|quoted
op_increment
op_ne
l_char|&squot;&quot;&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|len
op_assign
id|strcspn
c_func
(paren
id|quoted
comma
l_string|&quot;&bslash;&quot;&bslash;&bslash;&quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|quoted
comma
id|len
)paren
suffix:semicolon
id|quoted
op_add_assign
id|len
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|quoted
op_increment
)paren
(brace
r_case
l_char|&squot;&quot;&squot;
suffix:colon
r_if
c_cond
(paren
id|endp
)paren
op_star
id|endp
op_assign
id|quoted
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|ch
op_assign
op_star
id|quoted
op_increment
)paren
)paren
(brace
r_case
l_char|&squot;a&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;a&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;b&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;f&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;f&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;r&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;v&squot;
suffix:colon
id|ch
op_assign
l_char|&squot;&bslash;v&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
r_case
l_char|&squot;&quot;&squot;
suffix:colon
r_break
suffix:semicolon
multiline_comment|/* verbatim */
multiline_comment|/* octal values with first digit over 4 overflow */
r_case
l_char|&squot;0&squot;
suffix:colon
r_case
l_char|&squot;1&squot;
suffix:colon
r_case
l_char|&squot;2&squot;
suffix:colon
r_case
l_char|&squot;3&squot;
suffix:colon
id|ac
op_assign
(paren
(paren
id|ch
l_char|&squot;0&squot;
)paren
op_lshift
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ch
op_assign
op_star
id|quoted
op_increment
)paren
OL
l_char|&squot;0&squot;
op_logical_or
l_char|&squot;7&squot;
OL
id|ch
)paren
r_goto
id|error
suffix:semicolon
id|ac
op_or_assign
(paren
(paren
id|ch
l_char|&squot;0&squot;
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ch
op_assign
op_star
id|quoted
op_increment
)paren
OL
l_char|&squot;0&squot;
op_logical_or
l_char|&squot;7&squot;
OL
id|ch
)paren
r_goto
id|error
suffix:semicolon
id|ac
op_or_assign
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|ch
op_assign
id|ac
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
id|strbuf_addch
c_func
(paren
id|sb
comma
id|ch
)paren
suffix:semicolon
)brace
id|error
suffix:colon
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|oldlen
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* quoting as a string literal for other languages */
DECL|function|perl_quote_print
r_void
id|perl_quote_print
c_func
(paren
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_const
r_char
id|sq
op_assign
l_char|&squot;&bslash;&squot;&squot;
suffix:semicolon
r_const
r_char
id|bq
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
r_char
id|c
suffix:semicolon
id|fputc
c_func
(paren
id|sq
comma
id|stream
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
id|sq
op_logical_or
id|c
op_eq
id|bq
)paren
id|fputc
c_func
(paren
id|bq
comma
id|stream
)paren
suffix:semicolon
id|fputc
c_func
(paren
id|c
comma
id|stream
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
id|sq
comma
id|stream
)paren
suffix:semicolon
)brace
DECL|function|python_quote_print
r_void
id|python_quote_print
c_func
(paren
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_const
r_char
id|sq
op_assign
l_char|&squot;&bslash;&squot;&squot;
suffix:semicolon
r_const
r_char
id|bq
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
r_const
r_char
id|nl
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_char
id|c
suffix:semicolon
id|fputc
c_func
(paren
id|sq
comma
id|stream
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
id|nl
)paren
(brace
id|fputc
c_func
(paren
id|bq
comma
id|stream
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;n&squot;
comma
id|stream
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
id|sq
op_logical_or
id|c
op_eq
id|bq
)paren
id|fputc
c_func
(paren
id|bq
comma
id|stream
)paren
suffix:semicolon
id|fputc
c_func
(paren
id|c
comma
id|stream
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
id|sq
comma
id|stream
)paren
suffix:semicolon
)brace
DECL|function|tcl_quote_print
r_void
id|tcl_quote_print
c_func
(paren
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
id|c
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|stream
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;[&squot;
suffix:colon
r_case
l_char|&squot;]&squot;
suffix:colon
r_case
l_char|&squot;{&squot;
suffix:colon
r_case
l_char|&squot;}&squot;
suffix:colon
r_case
l_char|&squot;$&squot;
suffix:colon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
r_case
l_char|&squot;&quot;&squot;
suffix:colon
id|fputc
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|stream
)paren
suffix:semicolon
r_default
suffix:colon
id|fputc
c_func
(paren
id|c
comma
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;f&squot;
suffix:colon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&bslash;f&quot;
comma
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;r&squot;
suffix:colon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&bslash;r&quot;
comma
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&bslash;n&quot;
comma
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&bslash;t&quot;
comma
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;v&squot;
suffix:colon
id|fputs
c_func
(paren
l_string|&quot;&bslash;&bslash;v&quot;
comma
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fputc
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|stream
)paren
suffix:semicolon
)brace
eof
