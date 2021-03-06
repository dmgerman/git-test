macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|update_server_info_usage
r_static
r_const
r_char
op_star
r_const
id|update_server_info_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git update-server-info [--force]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_update_server_info
r_int
id|cmd_update_server_info
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
id|force
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
id|OPT__FORCE
c_func
(paren
op_amp
id|force
comma
id|N_
c_func
(paren
l_string|&quot;update the info files from scratch&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
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
id|update_server_info_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
id|usage_with_options
c_func
(paren
id|update_server_info_usage
comma
id|options
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|update_server_info
c_func
(paren
id|force
)paren
suffix:semicolon
)brace
eof
