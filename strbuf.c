macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|function|prefixcmp
r_int
id|prefixcmp
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
id|str
op_increment
comma
id|prefix
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
op_star
id|prefix
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|str
op_ne
op_star
id|prefix
)paren
r_return
(paren
r_int
r_char
)paren
op_star
id|prefix
(paren
r_int
r_char
)paren
op_star
id|str
suffix:semicolon
)brace
DECL|function|suffixcmp
r_int
id|suffixcmp
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_const
r_char
op_star
id|suffix
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
comma
id|suflen
op_assign
id|strlen
c_func
(paren
id|suffix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|suflen
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
id|strcmp
c_func
(paren
id|str
op_plus
id|len
id|suflen
comma
id|suffix
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Used as the default -&gt;buf value, so that people can always assume&n; * buf is non NULL and -&gt;buf is NUL terminated even for a freshly&n; * initialized strbuf.&n; */
DECL|variable|strbuf_slopbuf
r_char
id|strbuf_slopbuf
(braket
l_int|1
)braket
suffix:semicolon
DECL|function|strbuf_init
r_void
id|strbuf_init
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|hint
)paren
(brace
id|sb-&gt;alloc
op_assign
id|sb-&gt;len
op_assign
l_int|0
suffix:semicolon
id|sb-&gt;buf
op_assign
id|strbuf_slopbuf
suffix:semicolon
r_if
c_cond
(paren
id|hint
)paren
id|strbuf_grow
c_func
(paren
id|sb
comma
id|hint
)paren
suffix:semicolon
)brace
DECL|function|strbuf_release
r_void
id|strbuf_release
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;alloc
)paren
(brace
id|free
c_func
(paren
id|sb-&gt;buf
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|strbuf_detach
r_char
op_star
id|strbuf_detach
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
op_star
id|sz
)paren
(brace
r_char
op_star
id|res
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|res
op_assign
id|sb-&gt;buf
suffix:semicolon
r_if
c_cond
(paren
id|sz
)paren
op_star
id|sz
op_assign
id|sb-&gt;len
suffix:semicolon
id|strbuf_init
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|strbuf_attach
r_void
id|strbuf_attach
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|alloc
)paren
(brace
id|strbuf_release
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;buf
op_assign
id|buf
suffix:semicolon
id|sb-&gt;len
op_assign
id|len
suffix:semicolon
id|sb-&gt;alloc
op_assign
id|alloc
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|sb-&gt;buf
(braket
id|sb-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|strbuf_grow
r_void
id|strbuf_grow
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|extra
)paren
(brace
r_int
id|new_buf
op_assign
op_logical_neg
id|sb-&gt;alloc
suffix:semicolon
r_if
c_cond
(paren
id|unsigned_add_overflows
c_func
(paren
id|extra
comma
l_int|1
)paren
op_logical_or
id|unsigned_add_overflows
c_func
(paren
id|sb-&gt;len
comma
id|extra
op_plus
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you want to use way too much memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_buf
)paren
id|sb-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|sb-&gt;buf
comma
id|sb-&gt;len
op_plus
id|extra
op_plus
l_int|1
comma
id|sb-&gt;alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_buf
)paren
id|sb-&gt;buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|strbuf_trim
r_void
id|strbuf_trim
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
)paren
(brace
r_char
op_star
id|b
op_assign
id|sb-&gt;buf
suffix:semicolon
r_while
c_loop
(paren
id|sb-&gt;len
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
(paren
r_int
r_char
)paren
id|sb-&gt;buf
(braket
id|sb-&gt;len
l_int|1
)braket
)paren
)paren
id|sb-&gt;len
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|sb-&gt;len
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
op_star
id|b
)paren
)paren
(brace
id|b
op_increment
suffix:semicolon
id|sb-&gt;len
op_decrement
suffix:semicolon
)brace
id|memmove
c_func
(paren
id|sb-&gt;buf
comma
id|b
comma
id|sb-&gt;len
)paren
suffix:semicolon
id|sb-&gt;buf
(braket
id|sb-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|strbuf_rtrim
r_void
id|strbuf_rtrim
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
)paren
(brace
r_while
c_loop
(paren
id|sb-&gt;len
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
(paren
r_int
r_char
)paren
id|sb-&gt;buf
(braket
id|sb-&gt;len
l_int|1
)braket
)paren
)paren
id|sb-&gt;len
op_decrement
suffix:semicolon
id|sb-&gt;buf
(braket
id|sb-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|strbuf_ltrim
r_void
id|strbuf_ltrim
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
)paren
(brace
r_char
op_star
id|b
op_assign
id|sb-&gt;buf
suffix:semicolon
r_while
c_loop
(paren
id|sb-&gt;len
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
op_star
id|b
)paren
)paren
(brace
id|b
op_increment
suffix:semicolon
id|sb-&gt;len
op_decrement
suffix:semicolon
)brace
id|memmove
c_func
(paren
id|sb-&gt;buf
comma
id|b
comma
id|sb-&gt;len
)paren
suffix:semicolon
id|sb-&gt;buf
(braket
id|sb-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|strbuf_split_buf
r_struct
id|strbuf
op_star
op_star
id|strbuf_split_buf
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|slen
comma
r_int
id|terminator
comma
r_int
id|max
)paren
(brace
r_struct
id|strbuf
op_star
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
comma
id|alloc
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
op_star
id|t
suffix:semicolon
r_while
c_loop
(paren
id|slen
)paren
(brace
r_int
id|len
op_assign
id|slen
suffix:semicolon
r_if
c_cond
(paren
id|max
op_le
l_int|0
op_logical_or
id|nr
op_plus
l_int|1
OL
id|max
)paren
(brace
r_const
r_char
op_star
id|end
op_assign
id|memchr
c_func
(paren
id|str
comma
id|terminator
comma
id|slen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
id|len
op_assign
id|end
id|str
op_plus
l_int|1
suffix:semicolon
)brace
id|t
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|strbuf
)paren
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
id|t
comma
id|len
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|t
comma
id|str
comma
id|len
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|ret
comma
id|nr
op_plus
l_int|2
comma
id|alloc
)paren
suffix:semicolon
id|ret
(braket
id|nr
op_increment
)braket
op_assign
id|t
suffix:semicolon
id|str
op_add_assign
id|len
suffix:semicolon
id|slen
op_sub_assign
id|len
suffix:semicolon
)brace
id|ALLOC_GROW
c_func
(paren
id|ret
comma
id|nr
op_plus
l_int|1
comma
id|alloc
)paren
suffix:semicolon
multiline_comment|/* In case string was empty */
id|ret
(braket
id|nr
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|strbuf_list_free
r_void
id|strbuf_list_free
c_func
(paren
r_struct
id|strbuf
op_star
op_star
id|sbs
)paren
(brace
r_struct
id|strbuf
op_star
op_star
id|s
op_assign
id|sbs
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
)paren
(brace
id|strbuf_release
c_func
(paren
op_star
id|s
)paren
suffix:semicolon
id|free
c_func
(paren
op_star
id|s
op_increment
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|sbs
)paren
suffix:semicolon
)brace
DECL|function|strbuf_cmp
r_int
id|strbuf_cmp
c_func
(paren
r_const
r_struct
id|strbuf
op_star
id|a
comma
r_const
r_struct
id|strbuf
op_star
id|b
)paren
(brace
r_int
id|len
op_assign
id|a-&gt;len
OL
id|b-&gt;len
ques
c_cond
id|a-&gt;len
suffix:colon
id|b-&gt;len
suffix:semicolon
r_int
id|cmp
op_assign
id|memcmp
c_func
(paren
id|a-&gt;buf
comma
id|b-&gt;buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
)paren
r_return
id|cmp
suffix:semicolon
r_return
id|a-&gt;len
OL
id|b-&gt;len
ques
c_cond
l_int|1
suffix:colon
id|a-&gt;len
op_ne
id|b-&gt;len
suffix:semicolon
)brace
DECL|function|strbuf_splice
r_void
id|strbuf_splice
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|pos
comma
r_int
id|len
comma
r_const
r_void
op_star
id|data
comma
r_int
id|dlen
)paren
(brace
r_if
c_cond
(paren
id|unsigned_add_overflows
c_func
(paren
id|pos
comma
id|len
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you want to use way too much memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|sb-&gt;len
)paren
id|die
c_func
(paren
l_string|&quot;`pos&squot; is too far after the end of the buffer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|len
OG
id|sb-&gt;len
)paren
id|die
c_func
(paren
l_string|&quot;`pos + len&squot; is too far after the end of the buffer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dlen
op_ge
id|len
)paren
id|strbuf_grow
c_func
(paren
id|sb
comma
id|dlen
id|len
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|sb-&gt;buf
op_plus
id|pos
op_plus
id|dlen
comma
id|sb-&gt;buf
op_plus
id|pos
op_plus
id|len
comma
id|sb-&gt;len
id|pos
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sb-&gt;buf
op_plus
id|pos
comma
id|data
comma
id|dlen
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_plus
id|dlen
id|len
)paren
suffix:semicolon
)brace
DECL|function|strbuf_insert
r_void
id|strbuf_insert
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|pos
comma
r_const
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|strbuf_splice
c_func
(paren
id|sb
comma
id|pos
comma
l_int|0
comma
id|data
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|strbuf_remove
r_void
id|strbuf_remove
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|pos
comma
r_int
id|len
)paren
(brace
id|strbuf_splice
c_func
(paren
id|sb
comma
id|pos
comma
id|len
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|strbuf_add
r_void
id|strbuf_add
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|strbuf_grow
c_func
(paren
id|sb
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|data
comma
id|len
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_plus
id|len
)paren
suffix:semicolon
)brace
DECL|function|strbuf_adddup
r_void
id|strbuf_adddup
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|pos
comma
r_int
id|len
)paren
(brace
id|strbuf_grow
c_func
(paren
id|sb
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|sb-&gt;buf
op_plus
id|pos
comma
id|len
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_plus
id|len
)paren
suffix:semicolon
)brace
DECL|function|strbuf_addf
r_void
id|strbuf_addf
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
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
id|sb
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|strbuf_vaddf
r_void
id|strbuf_vaddf
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
id|fmt
comma
id|va_list
id|ap
)paren
(brace
r_int
id|len
suffix:semicolon
id|va_list
id|cp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strbuf_avail
c_func
(paren
id|sb
)paren
)paren
id|strbuf_grow
c_func
(paren
id|sb
comma
l_int|64
)paren
suffix:semicolon
id|va_copy
c_func
(paren
id|cp
comma
id|ap
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|sb-&gt;alloc
id|sb-&gt;len
comma
id|fmt
comma
id|cp
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;BUG: your vsnprintf is broken (returned %d)&quot;
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|strbuf_avail
c_func
(paren
id|sb
)paren
)paren
(brace
id|strbuf_grow
c_func
(paren
id|sb
comma
id|len
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|sb-&gt;alloc
id|sb-&gt;len
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|strbuf_avail
c_func
(paren
id|sb
)paren
)paren
id|die
c_func
(paren
l_string|&quot;BUG: your vsnprintf is broken (insatiable)&quot;
)paren
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_plus
id|len
)paren
suffix:semicolon
)brace
DECL|function|strbuf_expand
r_void
id|strbuf_expand
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
id|format
comma
id|expand_fn_t
id|fn
comma
r_void
op_star
id|context
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|percent
suffix:semicolon
r_int
id|consumed
suffix:semicolon
id|percent
op_assign
id|strchrnul
c_func
(paren
id|format
comma
l_char|&squot;%&squot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|format
comma
id|percent
id|format
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|percent
)paren
r_break
suffix:semicolon
id|format
op_assign
id|percent
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|format
op_eq
l_char|&squot;%&squot;
)paren
(brace
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;%&squot;
)paren
suffix:semicolon
id|format
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|consumed
op_assign
id|fn
c_func
(paren
id|sb
comma
id|format
comma
id|context
)paren
suffix:semicolon
r_if
c_cond
(paren
id|consumed
)paren
id|format
op_add_assign
id|consumed
suffix:semicolon
r_else
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;%&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|strbuf_expand_dict_cb
r_int
id|strbuf_expand_dict_cb
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
id|placeholder
comma
r_void
op_star
id|context
)paren
(brace
r_struct
id|strbuf_expand_dict_entry
op_star
id|e
op_assign
id|context
suffix:semicolon
r_int
id|len
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|e-&gt;placeholder
op_logical_and
(paren
id|len
op_assign
id|strlen
c_func
(paren
id|e-&gt;placeholder
)paren
)paren
suffix:semicolon
id|e
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|placeholder
comma
id|e-&gt;placeholder
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
id|e-&gt;value
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|e-&gt;value
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|strbuf_addbuf_percentquote
r_void
id|strbuf_addbuf_percentquote
c_func
(paren
r_struct
id|strbuf
op_star
id|dst
comma
r_const
r_struct
id|strbuf
op_star
id|src
)paren
(brace
r_int
id|i
comma
id|len
op_assign
id|src-&gt;len
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|src-&gt;buf
(braket
id|i
)braket
op_eq
l_char|&squot;%&squot;
)paren
id|strbuf_addch
c_func
(paren
id|dst
comma
l_char|&squot;%&squot;
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|dst
comma
id|src-&gt;buf
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|strbuf_fread
r_int
id|strbuf_fread
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|size
comma
id|FILE
op_star
id|f
)paren
(brace
r_int
id|res
suffix:semicolon
r_int
id|oldalloc
op_assign
id|sb-&gt;alloc
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
id|size
)paren
suffix:semicolon
id|res
op_assign
id|fread
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
l_int|1
comma
id|size
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OG
l_int|0
)paren
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_plus
id|res
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|oldalloc
op_eq
l_int|0
)paren
id|strbuf_release
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|strbuf_read
id|ssize_t
id|strbuf_read
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|fd
comma
r_int
id|hint
)paren
(brace
r_int
id|oldlen
op_assign
id|sb-&gt;len
suffix:semicolon
r_int
id|oldalloc
op_assign
id|sb-&gt;alloc
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
id|hint
ques
c_cond
id|hint
suffix:colon
l_int|8192
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|ssize_t
id|cnt
suffix:semicolon
id|cnt
op_assign
id|xread
c_func
(paren
id|fd
comma
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|sb-&gt;alloc
id|sb-&gt;len
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|oldalloc
op_eq
l_int|0
)paren
id|strbuf_release
c_func
(paren
id|sb
)paren
suffix:semicolon
r_else
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
r_if
c_cond
(paren
op_logical_neg
id|cnt
)paren
r_break
suffix:semicolon
id|sb-&gt;len
op_add_assign
id|cnt
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
l_int|8192
)paren
suffix:semicolon
)brace
id|sb-&gt;buf
(braket
id|sb-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|sb-&gt;len
id|oldlen
suffix:semicolon
)brace
DECL|macro|STRBUF_MAXLINK
mdefine_line|#define STRBUF_MAXLINK (2*PATH_MAX)
DECL|function|strbuf_readlink
r_int
id|strbuf_readlink
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
id|path
comma
r_int
id|hint
)paren
(brace
r_int
id|oldalloc
op_assign
id|sb-&gt;alloc
suffix:semicolon
r_if
c_cond
(paren
id|hint
OL
l_int|32
)paren
id|hint
op_assign
l_int|32
suffix:semicolon
r_while
c_loop
(paren
id|hint
OL
id|STRBUF_MAXLINK
)paren
(brace
r_int
id|len
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
id|hint
)paren
suffix:semicolon
id|len
op_assign
id|readlink
c_func
(paren
id|path
comma
id|sb-&gt;buf
comma
id|hint
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ERANGE
)paren
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|len
OL
id|hint
)paren
(brace
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* .. the buffer was too small - try again */
id|hint
op_mul_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldalloc
op_eq
l_int|0
)paren
id|strbuf_release
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|strbuf_getwholeline
r_int
id|strbuf_getwholeline
c_func
(paren
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
id|term
)paren
(brace
r_int
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|feof
c_func
(paren
id|fp
)paren
)paren
r_return
id|EOF
suffix:semicolon
id|strbuf_reset
c_func
(paren
id|sb
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
id|fgetc
c_func
(paren
id|fp
)paren
)paren
op_ne
id|EOF
)paren
(brace
id|strbuf_grow
c_func
(paren
id|sb
comma
l_int|1
)paren
suffix:semicolon
id|sb-&gt;buf
(braket
id|sb-&gt;len
op_increment
)braket
op_assign
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
id|term
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch
op_eq
id|EOF
op_logical_and
id|sb-&gt;len
op_eq
l_int|0
)paren
r_return
id|EOF
suffix:semicolon
id|sb-&gt;buf
(braket
id|sb-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|strbuf_getline
r_int
id|strbuf_getline
c_func
(paren
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
id|term
)paren
(brace
r_if
c_cond
(paren
id|strbuf_getwholeline
c_func
(paren
id|sb
comma
id|fp
comma
id|term
)paren
)paren
r_return
id|EOF
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;buf
(braket
id|sb-&gt;len
op_minus
l_int|1
)braket
op_eq
id|term
)paren
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|strbuf_getwholeline_fd
r_int
id|strbuf_getwholeline_fd
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|fd
comma
r_int
id|term
)paren
(brace
id|strbuf_reset
c_func
(paren
id|sb
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
id|ch
suffix:semicolon
id|ssize_t
id|len
op_assign
id|xread
c_func
(paren
id|fd
comma
op_amp
id|ch
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_return
id|EOF
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|sb
comma
id|ch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
id|term
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|strbuf_read_file
r_int
id|strbuf_read_file
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
id|path
comma
r_int
id|hint
)paren
(brace
r_int
id|fd
comma
id|len
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|strbuf_read
c_func
(paren
id|sb
comma
id|fd
comma
id|hint
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|strbuf_add_lines
r_void
id|strbuf_add_lines
c_func
(paren
r_struct
id|strbuf
op_star
id|out
comma
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_while
c_loop
(paren
id|size
)paren
(brace
r_const
r_char
op_star
id|next
op_assign
id|memchr
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
comma
id|size
)paren
suffix:semicolon
id|next
op_assign
id|next
ques
c_cond
(paren
id|next
op_plus
l_int|1
)paren
suffix:colon
(paren
id|buf
op_plus
id|size
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|out
comma
id|prefix
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|out
comma
id|buf
comma
id|next
id|buf
)paren
suffix:semicolon
id|size
op_sub_assign
id|next
id|buf
suffix:semicolon
id|buf
op_assign
id|next
suffix:semicolon
)brace
id|strbuf_complete_line
c_func
(paren
id|out
)paren
suffix:semicolon
)brace
DECL|function|strbuf_addstr_xml_quoted
r_void
id|strbuf_addstr_xml_quoted
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_while
c_loop
(paren
op_star
id|s
)paren
(brace
r_int
id|len
op_assign
id|strcspn
c_func
(paren
id|s
comma
l_string|&quot;&bslash;&quot;&lt;&gt;&amp;&quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|s
comma
id|len
)paren
suffix:semicolon
id|s
op_add_assign
id|len
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|s
)paren
(brace
r_case
l_char|&squot;&quot;&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot;&amp;quot;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&lt;&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot;&amp;lt;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&gt;&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot;&amp;gt;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&amp;&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot;&amp;amp;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
suffix:semicolon
)brace
id|s
op_increment
suffix:semicolon
)brace
)brace
DECL|function|is_rfc3986_reserved
r_static
r_int
id|is_rfc3986_reserved
c_func
(paren
r_char
id|ch
)paren
(brace
r_switch
c_cond
(paren
id|ch
)paren
(brace
r_case
l_char|&squot;!&squot;
suffix:colon
r_case
l_char|&squot;*&squot;
suffix:colon
r_case
l_char|&squot;&bslash;&squot;&squot;
suffix:colon
r_case
l_char|&squot;(&squot;
suffix:colon
r_case
l_char|&squot;)&squot;
suffix:colon
r_case
l_char|&squot;;&squot;
suffix:colon
r_case
l_char|&squot;:&squot;
suffix:colon
r_case
l_char|&squot;@&squot;
suffix:colon
r_case
l_char|&squot;&amp;&squot;
suffix:colon
r_case
l_char|&squot;=&squot;
suffix:colon
r_case
l_char|&squot;+&squot;
suffix:colon
r_case
l_char|&squot;$&squot;
suffix:colon
r_case
l_char|&squot;,&squot;
suffix:colon
r_case
l_char|&squot;/&squot;
suffix:colon
r_case
l_char|&squot;?&squot;
suffix:colon
r_case
l_char|&squot;#&squot;
suffix:colon
r_case
l_char|&squot;[&squot;
suffix:colon
r_case
l_char|&squot;]&squot;
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|is_rfc3986_unreserved
r_static
r_int
id|is_rfc3986_unreserved
c_func
(paren
r_char
id|ch
)paren
(brace
r_return
id|isalnum
c_func
(paren
id|ch
)paren
op_logical_or
id|ch
op_eq
l_char|&squot;-&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;_&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;.&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;~&squot;
suffix:semicolon
)brace
DECL|function|strbuf_add_urlencode
r_static
r_void
id|strbuf_add_urlencode
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
id|s
comma
r_int
id|len
comma
r_int
id|reserved
)paren
(brace
id|strbuf_grow
c_func
(paren
id|sb
comma
id|len
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_char
id|ch
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|is_rfc3986_unreserved
c_func
(paren
id|ch
)paren
op_logical_or
(paren
op_logical_neg
id|reserved
op_logical_and
id|is_rfc3986_reserved
c_func
(paren
id|ch
)paren
)paren
)paren
id|strbuf_addch
c_func
(paren
id|sb
comma
id|ch
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;%%%02x&quot;
comma
id|ch
)paren
suffix:semicolon
)brace
)brace
DECL|function|strbuf_addstr_urlencode
r_void
id|strbuf_addstr_urlencode
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
id|s
comma
r_int
id|reserved
)paren
(brace
id|strbuf_add_urlencode
c_func
(paren
id|sb
comma
id|s
comma
id|strlen
c_func
(paren
id|s
)paren
comma
id|reserved
)paren
suffix:semicolon
)brace
DECL|function|printf_ln
r_int
id|printf_ln
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_int
id|ret
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|vprintf
c_func
(paren
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
op_logical_or
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|ret
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|fprintf_ln
r_int
id|fprintf_ln
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_int
id|ret
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|vfprintf
c_func
(paren
id|fp
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
op_logical_or
id|putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|fp
)paren
op_eq
id|EOF
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|ret
op_plus
l_int|1
suffix:semicolon
)brace
eof
