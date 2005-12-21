macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
multiline_comment|/* Help to copy the thing properly quoted for the shell safety.&n; * any single quote is replaced with &squot;&bslash;&squot;&squot;, any exclamation point&n; * is replaced with &squot;&bslash;!&squot;, and the whole thing is enclosed in a&n; *&n; * E.g.&n; *  original     sq_quote     result&n; *  name     ==&gt; name      ==&gt; &squot;name&squot;&n; *  a b      ==&gt; a b       ==&gt; &squot;a b&squot;&n; *  a&squot;b      ==&gt; a&squot;&bslash;&squot;&squot;b    ==&gt; &squot;a&squot;&bslash;&squot;&squot;b&squot;&n; *  a!b      ==&gt; a&squot;&bslash;!&squot;b    ==&gt; &squot;a&squot;&bslash;!&squot;b&squot;&n; */
DECL|macro|EMIT
macro_line|#undef EMIT
DECL|macro|EMIT
mdefine_line|#define EMIT(x) ( (++len &lt; n) &amp;&amp; (*bp++ = (x)) )
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
r_int
id|sq_quote_buf
c_func
(paren
r_char
op_star
id|dst
comma
r_int
id|n
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
r_char
op_star
id|bp
op_assign
id|dst
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|EMIT
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
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
id|EMIT
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
)paren
suffix:semicolon
id|EMIT
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
)paren
suffix:semicolon
id|EMIT
c_func
(paren
id|c
)paren
suffix:semicolon
id|EMIT
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|EMIT
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
id|EMIT
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
op_star
id|bp
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|sq_quote
r_char
op_star
id|sq_quote
c_func
(paren
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_int
id|cnt
suffix:semicolon
id|cnt
op_assign
id|sq_quote_buf
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|src
)paren
op_plus
l_int|1
suffix:semicolon
id|buf
op_assign
id|xmalloc
c_func
(paren
id|cnt
)paren
suffix:semicolon
id|sq_quote_buf
c_func
(paren
id|buf
comma
id|cnt
comma
id|src
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
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
multiline_comment|/*&n; * C-style name quoting.&n; *&n; * Does one of three things:&n; *&n; * (1) if outbuf and outfp are both NULL, inspect the input name and&n; *     counts the number of bytes that are needed to hold c_style&n; *     quoted version of name, counting the double quotes around&n; *     it but not terminating NUL, and returns it.  However, if name&n; *     does not need c_style quoting, it returns 0.&n; *&n; * (2) if outbuf is not NULL, it must point at a buffer large enough&n; *     to hold the c_style quoted version of name, enclosing double&n; *     quotes, and terminating NUL.  Fills outbuf with c_style quoted&n; *     version of name enclosed in double-quote pair.  Return value&n; *     is undefined.&n; *&n; * (3) if outfp is not NULL, outputs c_style quoted version of name,&n; *     but not enclosed in double-quote pair.  Return value is undefined.&n; */
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
r_int
id|namelen
comma
r_char
op_star
id|outbuf
comma
id|FILE
op_star
id|outfp
comma
r_int
id|no_dq
)paren
(brace
DECL|macro|EMIT
macro_line|#undef EMIT
DECL|macro|EMIT
mdefine_line|#define EMIT(c) &bslash;&n;&t;(outbuf ? (*outbuf++ = (c)) : outfp ? fputc(c, outfp) : (count++))
DECL|macro|EMITQ
mdefine_line|#define EMITQ() EMIT(&squot;&bslash;&bslash;&squot;)
r_const
r_char
op_star
id|sp
suffix:semicolon
r_int
id|ch
comma
id|count
op_assign
l_int|0
comma
id|needquote
op_assign
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
r_for
c_loop
(paren
id|sp
op_assign
id|name
suffix:semicolon
id|sp
OL
id|name
op_plus
id|namelen
suffix:semicolon
id|sp
op_increment
)paren
(brace
id|ch
op_assign
op_star
id|sp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ch
OL
l_char|&squot; &squot;
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;&quot;&squot;
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
op_logical_or
(paren
id|ch
op_eq
l_int|0177
)paren
)paren
(brace
id|needquote
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|ch
)paren
(brace
r_case
l_char|&squot;&bslash;a&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;a&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;b&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;b&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;f&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;f&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;r&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;r&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;t&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;v&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
id|ch
op_assign
l_char|&squot;v&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
multiline_comment|/* fallthru */
r_case
l_char|&squot;&quot;&squot;
suffix:colon
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* octal */
id|EMITQ
c_func
(paren
)paren
suffix:semicolon
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
id|ch
op_assign
(paren
id|ch
op_amp
l_int|07
)paren
op_plus
l_char|&squot;0&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|EMIT
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|outbuf
)paren
op_star
id|outbuf
op_assign
l_int|0
suffix:semicolon
r_return
id|needquote
ques
c_cond
id|count
suffix:colon
l_int|0
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
r_char
op_star
id|outbuf
comma
id|FILE
op_star
id|outfp
comma
r_int
id|no_dq
)paren
(brace
r_int
id|cnt
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|quote_c_style_counted
c_func
(paren
id|name
comma
id|cnt
comma
id|outbuf
comma
id|outfp
comma
id|no_dq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * C-style name unquoting.&n; *&n; * Quoted should point at the opening double quote.  Returns&n; * an allocated memory that holds unquoted name, which the caller&n; * should free when done.  Updates endp pointer to point at&n; * one past the ending double quote if given.&n; */
DECL|function|unquote_c_style
r_char
op_star
id|unquote_c_style
c_func
(paren
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
r_const
r_char
op_star
id|sp
suffix:semicolon
r_char
op_star
id|name
op_assign
l_int|NULL
comma
op_star
id|outp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|count
op_assign
l_int|0
comma
id|ch
comma
id|ac
suffix:semicolon
DECL|macro|EMIT
macro_line|#undef EMIT
DECL|macro|EMIT
mdefine_line|#define EMIT(c) (outp ? (*outp++ = (c)) : (count++))
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
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* first pass counts and allocates, second pass fills */
r_for
c_loop
(paren
id|sp
op_assign
id|quoted
suffix:semicolon
(paren
id|ch
op_assign
op_star
id|sp
op_increment
)paren
op_ne
l_char|&squot;&quot;&squot;
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
r_switch
c_cond
(paren
id|ch
op_assign
op_star
id|sp
op_increment
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
r_case
l_char|&squot;0&squot;
dot
dot
dot
l_char|&squot;7&squot;
suffix:colon
multiline_comment|/* octal */
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
id|sp
op_increment
)paren
OL
l_char|&squot;0&squot;
op_logical_or
l_char|&squot;7&squot;
OL
id|ch
)paren
r_return
l_int|NULL
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
id|sp
op_increment
)paren
OL
l_char|&squot;0&squot;
op_logical_or
l_char|&squot;7&squot;
OL
id|ch
)paren
r_return
l_int|NULL
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
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* malformed */
)brace
)brace
id|EMIT
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name
)paren
(brace
op_star
id|outp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|endp
)paren
op_star
id|endp
op_assign
id|sp
suffix:semicolon
r_return
id|name
suffix:semicolon
)brace
id|outp
op_assign
id|name
op_assign
id|xmalloc
c_func
(paren
id|count
op_plus
l_int|1
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
id|prefix
comma
r_int
id|prefix_len
comma
r_const
r_char
op_star
id|name
comma
r_int
id|quote
comma
id|FILE
op_star
id|out
)paren
(brace
r_int
id|needquote
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quote
)paren
(brace
id|no_quote
suffix:colon
r_if
c_cond
(paren
id|prefix_len
)paren
id|fprintf
c_func
(paren
id|out
comma
l_string|&quot;%.*s&quot;
comma
id|prefix_len
comma
id|prefix
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|name
comma
id|out
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|needquote
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|prefix_len
)paren
id|needquote
op_assign
id|quote_c_style_counted
c_func
(paren
id|prefix
comma
id|prefix_len
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|needquote
)paren
id|needquote
op_assign
id|quote_c_style
c_func
(paren
id|name
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
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
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix_len
)paren
id|quote_c_style_counted
c_func
(paren
id|prefix
comma
id|prefix_len
comma
l_int|NULL
comma
id|out
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
id|out
comma
l_int|1
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|out
)paren
suffix:semicolon
)brace
r_else
r_goto
id|no_quote
suffix:semicolon
)brace
eof
