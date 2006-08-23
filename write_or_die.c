macro_line|#include &quot;cache.h&quot;
DECL|function|write_or_die
r_void
id|write_or_die
c_func
(paren
r_int
id|fd
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
id|ssize_t
id|written
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|written
op_assign
id|xwrite
c_func
(paren
id|fd
comma
id|p
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
op_eq
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;disk full?&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|written
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EPIPE
)paren
m_exit
(paren
l_int|0
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;write error (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|count
op_sub_assign
id|written
suffix:semicolon
id|p
op_add_assign
id|written
suffix:semicolon
)brace
)brace
eof
