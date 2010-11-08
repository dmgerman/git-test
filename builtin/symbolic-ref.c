macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|git_symbolic_ref_usage
r_static
r_const
r_char
op_star
r_const
id|git_symbolic_ref_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git symbolic-ref [options] name [ref]&quot;
comma
l_int|NULL
)brace
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
comma
r_int
id|quiet
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|die
c_func
(paren
l_string|&quot;ref %s is not a symbolic ref&quot;
comma
id|HEAD
)paren
suffix:semicolon
r_else
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
r_int
id|quiet
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
l_string|&quot;be quiet&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;m&squot;
comma
l_int|NULL
comma
op_amp
id|msg
comma
l_string|&quot;reason&quot;
comma
l_string|&quot;reason of the update&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|options
comma
id|git_symbolic_ref_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_logical_and
op_logical_neg
op_star
id|msg
)paren
id|die
c_func
(paren
l_string|&quot;Refusing to perform update with empty message&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_case
l_int|1
suffix:colon
id|check_symref
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|quiet
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;HEAD&quot;
)paren
op_logical_and
id|prefixcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;refs/&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Refusing to point HEAD outside of refs/&quot;
)paren
suffix:semicolon
id|create_symref
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
comma
id|msg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage_with_options
c_func
(paren
id|git_symbolic_ref_usage
comma
id|options
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
