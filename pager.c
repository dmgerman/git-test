macro_line|#include &quot;cache.h&quot;
multiline_comment|/*&n; * This is split up from the rest of git so that we might do&n; * something different on Windows, for example.&n; */
DECL|variable|spawned_pager
r_static
r_int
id|spawned_pager
suffix:semicolon
DECL|function|run_pager
r_static
r_void
id|run_pager
c_func
(paren
r_const
r_char
op_star
id|pager
)paren
(brace
multiline_comment|/*&n;&t; * Work around bug in &quot;less&quot; by not starting it until we&n;&t; * have real input&n;&t; */
id|fd_set
id|in
suffix:semicolon
id|FD_ZERO
c_func
(paren
op_amp
id|in
)paren
suffix:semicolon
id|FD_SET
c_func
(paren
l_int|0
comma
op_amp
id|in
)paren
suffix:semicolon
id|select
c_func
(paren
l_int|1
comma
op_amp
id|in
comma
l_int|NULL
comma
op_amp
id|in
comma
l_int|NULL
)paren
suffix:semicolon
id|execlp
c_func
(paren
id|pager
comma
id|pager
comma
l_int|NULL
)paren
suffix:semicolon
id|execl
c_func
(paren
l_string|&quot;/bin/sh&quot;
comma
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
id|pager
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|setup_pager
r_void
id|setup_pager
c_func
(paren
r_void
)paren
(brace
id|pid_t
id|pid
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_const
r_char
op_star
id|pager
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_PAGER&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isatty
c_func
(paren
l_int|1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pager
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pager_program
)paren
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
id|pager
op_assign
id|pager_program
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pager
)paren
id|pager
op_assign
id|getenv
c_func
(paren
l_string|&quot;PAGER&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pager
)paren
id|pager
op_assign
l_string|&quot;less&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
op_star
id|pager
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|pager
comma
l_string|&quot;cat&quot;
)paren
)paren
r_return
suffix:semicolon
id|spawned_pager
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* means we are emitting to terminal */
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fd
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* return in the child */
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|dup2
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The original process turns into the PAGER */
id|dup2
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;LESS&quot;
comma
l_string|&quot;FRSX&quot;
comma
l_int|0
)paren
suffix:semicolon
id|run_pager
c_func
(paren
id|pager
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unable to execute pager &squot;%s&squot;&quot;
comma
id|pager
)paren
suffix:semicolon
m_exit
(paren
l_int|255
)paren
suffix:semicolon
)brace
DECL|function|pager_in_use
r_int
id|pager_in_use
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|env
suffix:semicolon
r_if
c_cond
(paren
id|spawned_pager
)paren
r_return
l_int|1
suffix:semicolon
id|env
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_PAGER_IN_USE&quot;
)paren
suffix:semicolon
r_return
id|env
ques
c_cond
id|git_config_bool
c_func
(paren
l_string|&quot;GIT_PAGER_IN_USE&quot;
comma
id|env
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
