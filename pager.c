macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#ifndef DEFAULT_PAGER
DECL|macro|DEFAULT_PAGER
mdefine_line|#define DEFAULT_PAGER &quot;less&quot;
macro_line|#endif
DECL|struct|pager_config
r_struct
id|pager_config
(brace
DECL|member|cmd
r_const
r_char
op_star
id|cmd
suffix:semicolon
DECL|member|want
r_int
id|want
suffix:semicolon
DECL|member|value
r_char
op_star
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is split up from the rest of git so that we can do&n; * something different on Windows.&n; */
DECL|variable|pager_argv
r_static
r_const
r_char
op_star
id|pager_argv
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|pager_process
r_static
r_struct
id|child_process
id|pager_process
suffix:semicolon
DECL|function|wait_for_pager
r_static
r_void
id|wait_for_pager
c_func
(paren
r_void
)paren
(brace
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stderr
)paren
suffix:semicolon
multiline_comment|/* signal EOF to pager */
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|finish_command
c_func
(paren
op_amp
id|pager_process
)paren
suffix:semicolon
)brace
DECL|function|wait_for_pager_signal
r_static
r_void
id|wait_for_pager_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|wait_for_pager
c_func
(paren
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|signo
)paren
suffix:semicolon
id|raise
c_func
(paren
id|signo
)paren
suffix:semicolon
)brace
DECL|function|git_pager
r_const
r_char
op_star
id|git_pager
c_func
(paren
r_int
id|stdout_is_tty
)paren
(brace
r_const
r_char
op_star
id|pager
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stdout_is_tty
)paren
r_return
l_int|NULL
suffix:semicolon
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
comma
l_int|NULL
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
id|DEFAULT_PAGER
suffix:semicolon
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
id|pager
op_assign
l_int|NULL
suffix:semicolon
r_return
id|pager
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
r_const
r_char
op_star
id|pager
op_assign
id|git_pager
c_func
(paren
id|isatty
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pager
op_logical_or
id|pager_in_use
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * force computing the width of the terminal before we redirect&n;&t; * the standard output to the pager.&n;&t; */
(paren
r_void
)paren
id|term_columns
c_func
(paren
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;GIT_PAGER_IN_USE&quot;
comma
l_string|&quot;true&quot;
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* spawn the pager */
id|pager_argv
(braket
l_int|0
)braket
op_assign
id|pager
suffix:semicolon
id|pager_process.use_shell
op_assign
l_int|1
suffix:semicolon
id|pager_process.argv
op_assign
id|pager_argv
suffix:semicolon
id|pager_process.in
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|getenv
c_func
(paren
l_string|&quot;LESS&quot;
)paren
)paren
(brace
r_static
r_const
r_char
op_star
id|env
(braket
)braket
op_assign
(brace
l_string|&quot;LESS=FRSX&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|pager_process.env
op_assign
id|env
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|pager_process
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* original process continues, but writes to the pipe */
id|dup2
c_func
(paren
id|pager_process.in
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isatty
c_func
(paren
l_int|2
)paren
)paren
id|dup2
c_func
(paren
id|pager_process.in
comma
l_int|2
)paren
suffix:semicolon
id|close
c_func
(paren
id|pager_process.in
)paren
suffix:semicolon
multiline_comment|/* this makes sure that the parent terminates after the pager */
id|sigchain_push_common
c_func
(paren
id|wait_for_pager_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|wait_for_pager
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
multiline_comment|/*&n; * Return cached value (if set) or $COLUMNS environment variable (if&n; * set and positive) or ioctl(1, TIOCGWINSZ).ws_col (if positive),&n; * and default to 80 if all else fails.&n; */
DECL|function|term_columns
r_int
id|term_columns
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|term_columns_at_startup
suffix:semicolon
r_char
op_star
id|col_string
suffix:semicolon
r_int
id|n_cols
suffix:semicolon
r_if
c_cond
(paren
id|term_columns_at_startup
)paren
r_return
id|term_columns_at_startup
suffix:semicolon
id|term_columns_at_startup
op_assign
l_int|80
suffix:semicolon
id|col_string
op_assign
id|getenv
c_func
(paren
l_string|&quot;COLUMNS&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|col_string
op_logical_and
(paren
id|n_cols
op_assign
id|atoi
c_func
(paren
id|col_string
)paren
)paren
OG
l_int|0
)paren
id|term_columns_at_startup
op_assign
id|n_cols
suffix:semicolon
macro_line|#ifdef TIOCGWINSZ
r_else
(brace
r_struct
id|winsize
id|ws
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioctl
c_func
(paren
l_int|1
comma
id|TIOCGWINSZ
comma
op_amp
id|ws
)paren
op_logical_and
id|ws.ws_col
)paren
id|term_columns_at_startup
op_assign
id|ws.ws_col
suffix:semicolon
)brace
macro_line|#endif
r_return
id|term_columns_at_startup
suffix:semicolon
)brace
multiline_comment|/*&n; * How many columns do we need to show this number in decimal?&n; */
DECL|function|decimal_width
r_int
id|decimal_width
c_func
(paren
r_uintmax
id|number
)paren
(brace
r_int
id|width
suffix:semicolon
r_for
c_loop
(paren
id|width
op_assign
l_int|1
suffix:semicolon
id|number
op_ge
l_int|10
suffix:semicolon
id|width
op_increment
)paren
id|number
op_div_assign
l_int|10
suffix:semicolon
r_return
id|width
suffix:semicolon
)brace
DECL|function|pager_command_config
r_static
r_int
id|pager_command_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|pager_config
op_star
id|c
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;pager.&quot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|var
op_plus
l_int|6
comma
id|c-&gt;cmd
)paren
)paren
(brace
r_int
id|b
op_assign
id|git_config_maybe_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_ge
l_int|0
)paren
id|c-&gt;want
op_assign
id|b
suffix:semicolon
r_else
(brace
id|c-&gt;want
op_assign
l_int|1
suffix:semicolon
id|c-&gt;value
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* returns 0 for &quot;no pager&quot;, 1 for &quot;use pager&quot;, and -1 for &quot;not specified&quot; */
DECL|function|check_pager_config
r_int
id|check_pager_config
c_func
(paren
r_const
r_char
op_star
id|cmd
)paren
(brace
r_struct
id|pager_config
id|c
suffix:semicolon
id|c.cmd
op_assign
id|cmd
suffix:semicolon
id|c.want
op_assign
l_int|1
suffix:semicolon
id|c.value
op_assign
l_int|NULL
suffix:semicolon
id|git_config
c_func
(paren
id|pager_command_config
comma
op_amp
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c.value
)paren
id|pager_program
op_assign
id|c.value
suffix:semicolon
r_return
id|c.want
suffix:semicolon
)brace
eof
