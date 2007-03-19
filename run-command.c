macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
DECL|function|close_pair
r_static
r_inline
r_void
id|close_pair
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
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
)brace
DECL|function|dup_devnull
r_static
r_inline
r_void
id|dup_devnull
c_func
(paren
r_int
id|to
)paren
(brace
r_int
id|fd
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
id|O_RDWR
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|fd
comma
id|to
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|start_command
r_int
id|start_command
c_func
(paren
r_struct
id|child_process
op_star
id|cmd
)paren
(brace
r_int
id|need_in
comma
id|need_out
suffix:semicolon
r_int
id|fdin
(braket
l_int|2
)braket
comma
id|fdout
(braket
l_int|2
)braket
suffix:semicolon
id|need_in
op_assign
op_logical_neg
id|cmd-&gt;no_stdin
op_logical_and
id|cmd-&gt;in
OL
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|need_in
)paren
(brace
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fdin
)paren
OL
l_int|0
)paren
r_return
id|ERR_RUN_COMMAND_PIPE
suffix:semicolon
id|cmd-&gt;in
op_assign
id|fdin
(braket
l_int|1
)braket
suffix:semicolon
id|cmd-&gt;close_in
op_assign
l_int|1
suffix:semicolon
)brace
id|need_out
op_assign
op_logical_neg
id|cmd-&gt;no_stdout
op_logical_and
op_logical_neg
id|cmd-&gt;stdout_to_stderr
op_logical_and
id|cmd-&gt;out
OL
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|need_out
)paren
(brace
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fdout
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|need_in
)paren
id|close_pair
c_func
(paren
id|fdin
)paren
suffix:semicolon
r_return
id|ERR_RUN_COMMAND_PIPE
suffix:semicolon
)brace
id|cmd-&gt;out
op_assign
id|fdout
(braket
l_int|0
)braket
suffix:semicolon
id|cmd-&gt;close_out
op_assign
l_int|1
suffix:semicolon
)brace
id|cmd-&gt;pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;pid
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|need_in
)paren
id|close_pair
c_func
(paren
id|fdin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_out
)paren
id|close_pair
c_func
(paren
id|fdout
)paren
suffix:semicolon
r_return
id|ERR_RUN_COMMAND_FORK
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cmd-&gt;pid
)paren
(brace
r_if
c_cond
(paren
id|cmd-&gt;no_stdin
)paren
id|dup_devnull
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|need_in
)paren
(brace
id|dup2
c_func
(paren
id|fdin
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close_pair
c_func
(paren
id|fdin
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;in
)paren
(brace
id|dup2
c_func
(paren
id|cmd-&gt;in
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|cmd-&gt;in
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd-&gt;no_stdout
)paren
id|dup_devnull
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;stdout_to_stderr
)paren
id|dup2
c_func
(paren
l_int|2
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|need_out
)paren
(brace
id|dup2
c_func
(paren
id|fdout
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close_pair
c_func
(paren
id|fdout
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;out
OG
l_int|1
)paren
(brace
id|dup2
c_func
(paren
id|cmd-&gt;out
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd-&gt;git_cmd
)paren
(brace
id|execv_git_cmd
c_func
(paren
id|cmd-&gt;argv
)paren
suffix:semicolon
)brace
r_else
(brace
id|execvp
c_func
(paren
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
(paren
r_char
op_star
r_const
op_star
)paren
id|cmd-&gt;argv
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;exec %s failed.&quot;
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|need_in
)paren
id|close
c_func
(paren
id|fdin
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;in
)paren
id|close
c_func
(paren
id|cmd-&gt;in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_out
)paren
id|close
c_func
(paren
id|fdout
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;out
OG
l_int|1
)paren
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|finish_command
r_int
id|finish_command
c_func
(paren
r_struct
id|child_process
op_star
id|cmd
)paren
(brace
r_if
c_cond
(paren
id|cmd-&gt;close_in
)paren
id|close
c_func
(paren
id|cmd-&gt;in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;close_out
)paren
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|status
comma
id|code
suffix:semicolon
id|pid_t
id|waiting
op_assign
id|waitpid
c_func
(paren
id|cmd-&gt;pid
comma
op_amp
id|status
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waiting
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EINTR
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;waitpid failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|ERR_RUN_COMMAND_WAITPID
suffix:semicolon
)brace
r_if
c_cond
(paren
id|waiting
op_ne
id|cmd-&gt;pid
)paren
r_return
id|ERR_RUN_COMMAND_WAITPID_WRONG_PID
suffix:semicolon
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
r_return
id|ERR_RUN_COMMAND_WAITPID_SIGNAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
r_return
id|ERR_RUN_COMMAND_WAITPID_NOEXIT
suffix:semicolon
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
r_return
id|code
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|run_command
r_int
id|run_command
c_func
(paren
r_struct
id|child_process
op_star
id|cmd
)paren
(brace
r_int
id|code
op_assign
id|start_command
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
r_return
id|code
suffix:semicolon
r_return
id|finish_command
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|run_command_v_opt
r_int
id|run_command_v_opt
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
comma
r_int
id|opt
)paren
(brace
r_struct
id|child_process
id|cmd
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cmd
comma
l_int|0
comma
r_sizeof
(paren
id|cmd
)paren
)paren
suffix:semicolon
id|cmd.argv
op_assign
id|argv
suffix:semicolon
id|cmd.no_stdin
op_assign
id|opt
op_amp
id|RUN_COMMAND_NO_STDIN
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|cmd.git_cmd
op_assign
id|opt
op_amp
id|RUN_GIT_CMD
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|cmd.stdout_to_stderr
op_assign
id|opt
op_amp
id|RUN_COMMAND_STDOUT_TO_STDERR
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
id|run_command
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
)brace
eof
