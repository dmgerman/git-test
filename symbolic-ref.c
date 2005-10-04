macro_line|#include &quot;cache.h&quot;
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
r_const
r_char
op_star
id|git_HEAD
op_assign
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HEAD
)paren
)paren
suffix:semicolon
r_const
r_char
op_star
id|git_refs_heads_master
op_assign
id|resolve_ref
c_func
(paren
id|git_HEAD
comma
id|sha1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_refs_heads_master
)paren
(brace
multiline_comment|/* we want to strip the .git/ part */
r_int
id|pfxlen
op_assign
id|strlen
c_func
(paren
id|git_HEAD
)paren
id|strlen
c_func
(paren
id|HEAD
)paren
suffix:semicolon
id|puts
c_func
(paren
id|git_refs_heads_master
op_plus
id|pfxlen
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;No such ref: %s&quot;
comma
id|HEAD
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
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
)paren
(brace
id|setup_git_directory
c_func
(paren
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
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
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
