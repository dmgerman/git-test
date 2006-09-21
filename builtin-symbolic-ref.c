macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|git_symbolic_ref_usage
r_static
r_const
r_char
id|git_symbolic_ref_usage
(braket
)braket
op_assign
l_string|&quot;git-symbolic-ref name [ref]&quot;
suffix:semicolon
DECL|function|check_symref
r_static
r_void
id|check_symref
c_func
(paren
r_const
r_char
op_star
id|HEAD
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|flag
suffix:semicolon
r_const
r_char
op_star
id|refs_heads_master
op_assign
id|resolve_ref
c_func
(paren
id|HEAD
comma
id|sha1
comma
l_int|0
comma
op_amp
id|flag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refs_heads_master
)paren
id|die
c_func
(paren
l_string|&quot;No such ref: %s&quot;
comma
id|HEAD
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|flag
op_amp
id|REF_ISSYMREF
)paren
)paren
id|die
c_func
(paren
l_string|&quot;ref %s is not a symbolic ref&quot;
comma
id|HEAD
)paren
suffix:semicolon
id|puts
c_func
(paren
id|refs_heads_master
)paren
suffix:semicolon
)brace
DECL|function|cmd_symbolic_ref
r_int
id|cmd_symbolic_ref
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
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_case
l_int|2
suffix:colon
id|check_symref
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|create_symref
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
id|git_symbolic_ref_usage
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
