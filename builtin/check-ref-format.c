multiline_comment|/*&n; * GIT - The information manager from hell&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|variable|builtin_check_ref_format_usage
r_static
r_const
r_char
id|builtin_check_ref_format_usage
(braket
)braket
op_assign
l_string|&quot;git check-ref-format [--print] &lt;refname&gt;&bslash;n&quot;
l_string|&quot;   or: git check-ref-format --branch &lt;branchname-shorthand&gt;&quot;
suffix:semicolon
multiline_comment|/*&n; * Remove leading slashes and replace each run of adjacent slashes in&n; * src with a single slash, and write the result to dst.&n; *&n; * This function is similar to normalize_path_copy(), but stripped down&n; * to meet check_ref_format&squot;s simpler needs.&n; */
DECL|function|collapse_slashes
r_static
r_void
id|collapse_slashes
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
id|ch
suffix:semicolon
r_char
id|prev
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|prev
op_eq
l_char|&squot;/&squot;
op_logical_and
id|ch
op_eq
id|prev
)paren
r_continue
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|ch
suffix:semicolon
id|prev
op_assign
id|ch
suffix:semicolon
)brace
op_star
id|dst
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|check_ref_format_branch
r_static
r_int
id|check_ref_format_branch
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|nongit
suffix:semicolon
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_check_branch_ref
c_func
(paren
op_amp
id|sb
comma
id|arg
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid branch name&quot;
comma
id|arg
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sb.buf
op_plus
l_int|11
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_ref_format_print
r_static
r_int
id|check_ref_format_print
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_char
op_star
id|refname
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|arg
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|arg
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|collapse_slashes
c_func
(paren
id|refname
comma
id|arg
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_check_ref_format
r_int
id|cmd_check_ref_format
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
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage
c_func
(paren
id|builtin_check_ref_format_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|3
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--branch&quot;
)paren
)paren
r_return
id|check_ref_format_branch
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|3
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--print&quot;
)paren
)paren
r_return
id|check_ref_format_print
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage
c_func
(paren
id|builtin_check_ref_format_usage
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|check_ref_format
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
eof
