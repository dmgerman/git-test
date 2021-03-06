macro_line|#include &quot;../git-compat-util.h&quot;
DECL|function|gitunsetenv
r_void
id|gitunsetenv
(paren
r_const
r_char
op_star
id|name
)paren
(brace
macro_line|#if !defined(__MINGW32__)
r_extern
r_char
op_star
op_star
id|environ
suffix:semicolon
macro_line|#endif
r_int
id|src
comma
id|dst
suffix:semicolon
r_int
id|nmln
suffix:semicolon
id|nmln
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
id|dst
op_assign
l_int|0
suffix:semicolon
id|environ
(braket
id|src
)braket
suffix:semicolon
op_increment
id|src
)paren
(brace
r_int
id|enln
suffix:semicolon
id|enln
op_assign
id|strlen
c_func
(paren
id|environ
(braket
id|src
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enln
OG
id|nmln
)paren
(brace
multiline_comment|/* might match, and can test for &squot;=&squot; safely */
r_if
c_cond
(paren
l_int|0
op_eq
id|strncmp
(paren
id|environ
(braket
id|src
)braket
comma
id|name
comma
id|nmln
)paren
op_logical_and
l_char|&squot;=&squot;
op_eq
id|environ
(braket
id|src
)braket
(braket
id|nmln
)braket
)paren
multiline_comment|/* matches, so skip */
r_continue
suffix:semicolon
)brace
id|environ
(braket
id|dst
)braket
op_assign
id|environ
(braket
id|src
)braket
suffix:semicolon
op_increment
id|dst
suffix:semicolon
)brace
id|environ
(braket
id|dst
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
