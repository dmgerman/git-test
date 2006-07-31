multiline_comment|/*&n; * GIT - The information manager from hell&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;builtin.h&quot;
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
op_ne
l_int|2
)paren
id|usage
c_func
(paren
l_string|&quot;git check-ref-format refname&quot;
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
