multiline_comment|/*&n; * GIT - The information manager from hell&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &lt;stdio.h&gt;
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_char
op_star
op_star
id|av
)paren
(brace
r_if
c_cond
(paren
id|ac
op_ne
l_int|2
)paren
id|usage
c_func
(paren
l_string|&quot;git-check-ref-format refname&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|av
(braket
l_int|1
)braket
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
