macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;credential.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|usage_msg
r_static
r_const
r_char
id|usage_msg
(braket
)braket
op_assign
l_string|&quot;git credential [fill|approve|reject]&quot;
suffix:semicolon
DECL|function|cmd_credential
r_int
id|cmd_credential
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
r_const
r_char
op_star
id|op
suffix:semicolon
r_struct
id|credential
id|c
op_assign
id|CREDENTIAL_INIT
suffix:semicolon
id|op
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
id|usage
c_func
(paren
id|usage_msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|credential_read
c_func
(paren
op_amp
id|c
comma
id|stdin
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to read credential from stdin&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|op
comma
l_string|&quot;fill&quot;
)paren
)paren
(brace
id|credential_fill
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
id|credential_write
c_func
(paren
op_amp
id|c
comma
id|stdout
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|op
comma
l_string|&quot;approve&quot;
)paren
)paren
(brace
id|credential_approve
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|op
comma
l_string|&quot;reject&quot;
)paren
)paren
(brace
id|credential_reject
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
)brace
r_else
(brace
id|usage
c_func
(paren
id|usage_msg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
