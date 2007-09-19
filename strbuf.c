macro_line|#include &quot;cache.h&quot;
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
id|memset
c_func
(paren
id|sb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sb
)paren
)paren
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
id|free
c_func
(paren
id|sb-&gt;buf
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sb
)paren
)paren
suffix:semicolon
)brace
DECL|function|strbuf_reset
r_void
id|strbuf_reset
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
id|sb-&gt;len
)paren
id|strbuf_setlen
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
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
)paren
(brace
r_char
op_star
id|res
op_assign
id|sb-&gt;buf
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
r_if
c_cond
(paren
id|sb-&gt;len
op_plus
id|extra
op_plus
l_int|1
op_le
id|sb-&gt;len
)paren
id|die
c_func
(paren
l_string|&quot;you want to use way too much memory&quot;
)paren
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
id|pos
op_plus
id|len
OL
id|pos
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
r_int
id|len
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
id|va_end
c_func
(paren
id|ap
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
id|len
op_assign
l_int|0
suffix:semicolon
)brace
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
id|va_start
c_func
(paren
id|ap
comma
id|fmt
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
id|va_end
c_func
(paren
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
(brace
id|die
c_func
(paren
l_string|&quot;this should not happen, your snprintf is broken&quot;
)paren
suffix:semicolon
)brace
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
(brace
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
)brace
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
r_int
id|ch
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|sb
comma
l_int|0
)paren
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
r_if
c_cond
(paren
id|ch
op_eq
id|term
)paren
r_break
suffix:semicolon
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
eof
