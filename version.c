macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;version.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|variable|git_version_string
r_const
r_char
id|git_version_string
(braket
)braket
op_assign
id|GIT_VERSION
suffix:semicolon
DECL|function|git_user_agent
r_const
r_char
op_star
id|git_user_agent
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_char
op_star
id|agent
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|agent
)paren
(brace
id|agent
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_USER_AGENT&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|agent
)paren
id|agent
op_assign
id|GIT_USER_AGENT
suffix:semicolon
)brace
r_return
id|agent
suffix:semicolon
)brace
DECL|function|git_user_agent_sanitized
r_const
r_char
op_star
id|git_user_agent_sanitized
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_char
op_star
id|agent
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|agent
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|i
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|git_user_agent
c_func
(paren
)paren
)paren
suffix:semicolon
id|strbuf_trim
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|buf.len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buf.buf
(braket
id|i
)braket
op_le
l_int|32
op_logical_or
id|buf.buf
(braket
id|i
)braket
op_ge
l_int|127
)paren
id|buf.buf
(braket
id|i
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
id|agent
op_assign
id|buf.buf
suffix:semicolon
)brace
r_return
id|agent
suffix:semicolon
)brace
eof
