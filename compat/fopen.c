macro_line|#include &quot;../git-compat-util.h&quot;
DECL|macro|fopen
macro_line|#undef fopen
DECL|function|git_fopen
id|FILE
op_star
id|git_fopen
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|mode
)paren
(brace
id|FILE
op_star
id|fp
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|mode
(braket
l_int|0
)braket
op_eq
l_char|&squot;w&squot;
op_logical_or
id|mode
(braket
l_int|0
)braket
op_eq
l_char|&squot;a&squot;
)paren
r_return
id|fopen
c_func
(paren
id|path
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fp
op_assign
id|fopen
c_func
(paren
id|path
comma
id|mode
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fileno
c_func
(paren
id|fp
)paren
comma
op_amp
id|st
)paren
)paren
(brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
id|errno
op_assign
id|EISDIR
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|fp
suffix:semicolon
)brace
eof
