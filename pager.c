macro_line|#include &quot;cache.h&quot;
multiline_comment|/*&n; * This is split up from the rest of git so that we might do&n; * something different on Windows, for example.&n; */
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
l_string|&quot;PAGER&quot;
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
l_string|&quot;-S&quot;
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
m_exit
(paren
l_int|255
)paren
suffix:semicolon
)brace
eof
