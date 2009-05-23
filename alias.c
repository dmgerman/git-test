macro_line|#include &quot;cache.h&quot;
DECL|variable|alias_key
r_static
r_const
r_char
op_star
id|alias_key
suffix:semicolon
DECL|variable|alias_val
r_static
r_char
op_star
id|alias_val
suffix:semicolon
DECL|function|alias_lookup_cb
r_static
r_int
id|alias_lookup_cb
c_func
(paren
r_const
r_char
op_star
id|k
comma
r_const
r_char
op_star
id|v
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|k
comma
l_string|&quot;alias.&quot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|k
op_plus
l_int|6
comma
id|alias_key
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|v
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|k
)paren
suffix:semicolon
id|alias_val
op_assign
id|xstrdup
c_func
(paren
id|v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alias_lookup
r_char
op_star
id|alias_lookup
c_func
(paren
r_const
r_char
op_star
id|alias
)paren
(brace
id|alias_key
op_assign
id|alias
suffix:semicolon
id|alias_val
op_assign
l_int|NULL
suffix:semicolon
id|git_config
c_func
(paren
id|alias_lookup_cb
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|alias_val
suffix:semicolon
)brace
DECL|function|split_cmdline
r_int
id|split_cmdline
c_func
(paren
r_char
op_star
id|cmdline
comma
r_const
r_char
op_star
op_star
op_star
id|argv
)paren
(brace
r_int
id|src
comma
id|dst
comma
id|count
op_assign
l_int|0
comma
id|size
op_assign
l_int|16
suffix:semicolon
r_char
id|quoted
op_assign
l_int|0
suffix:semicolon
op_star
id|argv
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_char
op_star
)paren
op_star
id|size
)paren
suffix:semicolon
multiline_comment|/* split alias_string */
(paren
op_star
id|argv
)paren
(braket
id|count
op_increment
)braket
op_assign
id|cmdline
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
id|cmdline
(braket
id|src
)braket
suffix:semicolon
)paren
(brace
r_char
id|c
op_assign
id|cmdline
(braket
id|src
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quoted
op_logical_and
id|isspace
c_func
(paren
id|c
)paren
)paren
(brace
id|cmdline
(braket
id|dst
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cmdline
(braket
op_increment
id|src
)braket
op_logical_and
id|isspace
c_func
(paren
id|cmdline
(braket
id|src
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* skip */
id|ALLOC_GROW
c_func
(paren
op_star
id|argv
comma
id|count
op_plus
l_int|1
comma
id|size
)paren
suffix:semicolon
(paren
op_star
id|argv
)paren
(braket
id|count
op_increment
)braket
op_assign
id|cmdline
op_plus
id|dst
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|quoted
op_logical_and
(paren
id|c
op_eq
l_char|&squot;&bslash;&squot;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&quot;&squot;
)paren
)paren
(brace
id|quoted
op_assign
id|c
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
id|quoted
)paren
(brace
id|quoted
op_assign
l_int|0
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
id|quoted
op_ne
l_char|&squot;&bslash;&squot;&squot;
)paren
(brace
id|src
op_increment
suffix:semicolon
id|c
op_assign
id|cmdline
(braket
id|src
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|free
c_func
(paren
op_star
id|argv
)paren
suffix:semicolon
op_star
id|argv
op_assign
l_int|NULL
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;cmdline ends with &bslash;&bslash;&quot;
)paren
suffix:semicolon
)brace
)brace
id|cmdline
(braket
id|dst
op_increment
)braket
op_assign
id|c
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
id|cmdline
(braket
id|dst
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|quoted
)paren
(brace
id|free
c_func
(paren
op_star
id|argv
)paren
suffix:semicolon
op_star
id|argv
op_assign
l_int|NULL
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unclosed quote&quot;
)paren
suffix:semicolon
)brace
id|ALLOC_GROW
c_func
(paren
op_star
id|argv
comma
id|count
op_plus
l_int|1
comma
id|size
)paren
suffix:semicolon
(paren
op_star
id|argv
)paren
(braket
id|count
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
eof
