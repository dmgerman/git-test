macro_line|#include &quot;../git-compat-util.h&quot;
DECL|function|gitmkdtemp
r_char
op_star
id|gitmkdtemp
c_func
(paren
r_char
op_star
r_template
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|mktemp
c_func
(paren
r_template
)paren
op_logical_or
id|mkdir
c_func
(paren
r_template
comma
l_int|0700
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
r_template
suffix:semicolon
)brace
eof
