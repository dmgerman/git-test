macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;bisect.h&quot;
DECL|variable|git_bisect_helper_usage
r_static
r_const
r_char
op_star
r_const
id|git_bisect_helper_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git bisect--helper --next-all [--no-checkout]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_bisect__helper
r_int
id|cmd_bisect__helper
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
id|next_all
op_assign
l_int|0
suffix:semicolon
r_int
id|no_checkout
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;next-all&quot;
comma
op_amp
id|next_all
comma
id|N_
c_func
(paren
l_string|&quot;perform &squot;git bisect next&squot;&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;no-checkout&quot;
comma
op_amp
id|no_checkout
comma
id|N_
c_func
(paren
l_string|&quot;update BISECT_HEAD instead of checking out the current commit&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
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
id|git_bisect_helper_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_all
)paren
id|usage_with_options
c_func
(paren
id|git_bisect_helper_usage
comma
id|options
)paren
suffix:semicolon
multiline_comment|/* next-all */
r_return
id|bisect_next_all
c_func
(paren
id|prefix
comma
id|no_checkout
)paren
suffix:semicolon
)brace
eof
