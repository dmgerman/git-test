macro_line|#include &quot;../git-compat-util.h&quot;
multiline_comment|/*&n; * A merge sort implementation, simplified from the qsort implementation&n; * by Mike Haertel, which is a part of the GNU C Library.&n; */
DECL|function|msort_with_tmp
r_static
r_void
id|msort_with_tmp
c_func
(paren
r_void
op_star
id|b
comma
r_int
id|n
comma
r_int
id|s
comma
r_int
(paren
op_star
id|cmp
)paren
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
)paren
comma
r_char
op_star
id|t
)paren
(brace
r_char
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|b1
comma
op_star
id|b2
suffix:semicolon
r_int
id|n1
comma
id|n2
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|1
)paren
r_return
suffix:semicolon
id|n1
op_assign
id|n
op_div
l_int|2
suffix:semicolon
id|n2
op_assign
id|n
id|n1
suffix:semicolon
id|b1
op_assign
id|b
suffix:semicolon
id|b2
op_assign
(paren
r_char
op_star
)paren
id|b
op_plus
(paren
id|n1
op_star
id|s
)paren
suffix:semicolon
id|msort_with_tmp
c_func
(paren
id|b1
comma
id|n1
comma
id|s
comma
id|cmp
comma
id|t
)paren
suffix:semicolon
id|msort_with_tmp
c_func
(paren
id|b2
comma
id|n2
comma
id|s
comma
id|cmp
comma
id|t
)paren
suffix:semicolon
id|tmp
op_assign
id|t
suffix:semicolon
r_while
c_loop
(paren
id|n1
OG
l_int|0
op_logical_and
id|n2
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cmp
c_func
(paren
id|b1
comma
id|b2
)paren
op_le
l_int|0
)paren
(brace
id|memcpy
c_func
(paren
id|tmp
comma
id|b1
comma
id|s
)paren
suffix:semicolon
id|tmp
op_add_assign
id|s
suffix:semicolon
id|b1
op_add_assign
id|s
suffix:semicolon
op_decrement
id|n1
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|tmp
comma
id|b2
comma
id|s
)paren
suffix:semicolon
id|tmp
op_add_assign
id|s
suffix:semicolon
id|b2
op_add_assign
id|s
suffix:semicolon
op_decrement
id|n2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|n1
OG
l_int|0
)paren
id|memcpy
c_func
(paren
id|tmp
comma
id|b1
comma
id|n1
op_star
id|s
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|b
comma
id|t
comma
(paren
id|n
id|n2
)paren
op_star
id|s
)paren
suffix:semicolon
)brace
DECL|function|git_qsort
r_void
id|git_qsort
c_func
(paren
r_void
op_star
id|b
comma
r_int
id|n
comma
r_int
id|s
comma
r_int
(paren
op_star
id|cmp
)paren
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
)paren
)paren
(brace
r_const
r_int
id|size
op_assign
id|n
op_star
id|s
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|buf
)paren
)paren
(brace
multiline_comment|/* The temporary array fits on the small on-stack buffer. */
id|msort_with_tmp
c_func
(paren
id|b
comma
id|n
comma
id|s
comma
id|cmp
comma
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* It&squot;s somewhat large, so malloc it.  */
r_char
op_star
id|tmp
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|msort_with_tmp
c_func
(paren
id|b
comma
id|n
comma
id|s
comma
id|cmp
comma
id|tmp
)paren
suffix:semicolon
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
)brace
eof
