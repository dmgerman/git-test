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
macro_line|#ifndef WIN32
DECL|variable|child_err
r_static
r_int
id|child_err
op_assign
l_int|2
suffix:semicolon
DECL|function|die_child
r_static
id|NORETURN
r_void
id|die_child
c_func
(paren
r_const
r_char
op_star
id|err
comma
id|va_list
id|params
)paren
(brace
r_char
id|msg
(braket
l_int|4096
)braket
suffix:semicolon
r_int
id|len
op_assign
id|vsnprintf
c_func
(paren
id|msg
comma
r_sizeof
(paren
id|msg
)paren
comma
id|err
comma
id|params
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
id|msg
)paren
)paren
id|len
op_assign
r_sizeof
(paren
id|msg
)paren
suffix:semicolon
id|write
c_func
(paren
id|child_err
comma
l_string|&quot;fatal: &quot;
comma
l_int|7
)paren
suffix:semicolon
id|write
c_func
(paren
id|child_err
comma
id|msg
comma
id|len
)paren
suffix:semicolon
id|write
c_func
(paren
id|child_err
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
m_exit
(paren
l_int|128
)paren
suffix:semicolon
)brace
DECL|function|set_cloexec
r_static
r_inline
r_void
id|set_cloexec
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
id|flags
op_assign
id|fcntl
c_func
(paren
id|fd
comma
id|F_GETFD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_ge
l_int|0
)paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFD
comma
id|flags
op_or
id|FD_CLOEXEC
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|wait_or_whine
r_static
r_int
id|wait_or_whine
c_func
(paren
id|pid_t
id|pid
comma
r_const
r_char
op_star
id|argv0
comma
r_int
id|silent_exec_failure
)paren
(brace
r_int
id|status
comma
id|code
op_assign
l_int|1
suffix:semicolon
id|pid_t
id|waiting
suffix:semicolon
r_int
id|failed_errno
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|waiting
op_assign
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
)paren
OL
l_int|0
op_logical_and
id|errno
op_eq
id|EINTR
)paren
suffix:semicolon
multiline_comment|/* nothing */
r_if
c_cond
(paren
id|waiting
OL
l_int|0
)paren
(brace
id|failed_errno
op_assign
id|errno
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;waitpid for %s failed: %s&quot;
comma
id|argv0
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|waiting
op_ne
id|pid
)paren
(brace
id|error
c_func
(paren
l_string|&quot;waitpid is confused (%s)&quot;
comma
id|argv0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
id|code
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s died of signal %d&quot;
comma
id|argv0
comma
id|code
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This return value is chosen so that code &amp; 0xff&n;&t;&t; * mimics the exit code that a POSIX shell would report for&n;&t;&t; * a program that died from this signal.&n;&t;&t; */
id|code
op_sub_assign
l_int|128
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Convert special exit code when execvp failed.&n;&t;&t; */
r_if
c_cond
(paren
id|code
op_eq
l_int|127
)paren
(brace
id|code
op_assign
l_int|1
suffix:semicolon
id|failed_errno
op_assign
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|silent_exec_failure
)paren
id|error
c_func
(paren
l_string|&quot;cannot run %s: %s&quot;
comma
id|argv0
comma
id|strerror
c_func
(paren
id|ENOENT
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|error
c_func
(paren
l_string|&quot;waitpid is confused (%s)&quot;
comma
id|argv0
)paren
suffix:semicolon
)brace
id|errno
op_assign
id|failed_errno
suffix:semicolon
r_return
id|code
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
comma
id|need_err
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
comma
id|fderr
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|failed_errno
op_assign
id|failed_errno
suffix:semicolon
multiline_comment|/*&n;&t; * In case of errors we must keep the promise to close FDs&n;&t; * that have been passed in via -&gt;in and -&gt;out.&n;&t; */
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
(brace
id|failed_errno
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;out
OG
l_int|0
)paren
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
r_goto
id|fail_pipe
suffix:semicolon
)brace
id|cmd-&gt;in
op_assign
id|fdin
(braket
l_int|1
)braket
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
id|failed_errno
op_assign
id|errno
suffix:semicolon
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
r_goto
id|fail_pipe
suffix:semicolon
)brace
id|cmd-&gt;out
op_assign
id|fdout
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|need_err
op_assign
op_logical_neg
id|cmd-&gt;no_stderr
op_logical_and
id|cmd-&gt;err
OL
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|need_err
)paren
(brace
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fderr
)paren
OL
l_int|0
)paren
(brace
id|failed_errno
op_assign
id|errno
suffix:semicolon
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
id|close_pair
c_func
(paren
id|fdout
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;out
)paren
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
id|fail_pipe
suffix:colon
id|error
c_func
(paren
l_string|&quot;cannot create pipe for %s: %s&quot;
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|strerror
c_func
(paren
id|failed_errno
)paren
)paren
suffix:semicolon
id|errno
op_assign
id|failed_errno
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|cmd-&gt;err
op_assign
id|fderr
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|trace_argv_printf
c_func
(paren
id|cmd-&gt;argv
comma
l_string|&quot;trace: run_command:&quot;
)paren
suffix:semicolon
macro_line|#ifndef WIN32
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
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
op_logical_neg
id|cmd-&gt;pid
)paren
(brace
multiline_comment|/*&n;&t;&t; * Redirect the channel to write syscall error messages to&n;&t;&t; * before redirecting the process&squot;s stderr so that all die()&n;&t;&t; * in subsequent call paths use the parent&squot;s stderr.&n;&t;&t; */
r_if
c_cond
(paren
id|cmd-&gt;no_stderr
op_logical_or
id|need_err
)paren
(brace
id|child_err
op_assign
id|dup
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|set_cloexec
c_func
(paren
id|child_err
)paren
suffix:semicolon
)brace
id|set_die_routine
c_func
(paren
id|die_child
)paren
suffix:semicolon
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
id|cmd-&gt;no_stderr
)paren
id|dup_devnull
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|need_err
)paren
(brace
id|dup2
c_func
(paren
id|fderr
(braket
l_int|1
)braket
comma
l_int|2
)paren
suffix:semicolon
id|close_pair
c_func
(paren
id|fderr
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
id|cmd-&gt;dir
op_logical_and
id|chdir
c_func
(paren
id|cmd-&gt;dir
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;exec &squot;%s&squot;: cd to &squot;%s&squot; failed&quot;
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|cmd-&gt;dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;env
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|cmd-&gt;env
suffix:semicolon
id|cmd-&gt;env
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strchr
c_func
(paren
op_star
id|cmd-&gt;env
comma
l_char|&squot;=&squot;
)paren
)paren
id|putenv
c_func
(paren
(paren
r_char
op_star
)paren
op_star
id|cmd-&gt;env
)paren
suffix:semicolon
r_else
id|unsetenv
c_func
(paren
op_star
id|cmd-&gt;env
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cmd-&gt;preexec_cb
)paren
id|cmd
op_member_access_from_pointer
id|preexec_cb
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t;&t; * Do not check for cmd-&gt;silent_exec_failure; the parent&n;&t;&t; * process will check it when it sees this exit code.&n;&t;&t; */
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
m_exit
(paren
l_int|127
)paren
suffix:semicolon
r_else
id|die_errno
c_func
(paren
l_string|&quot;cannot exec &squot;%s&squot;&quot;
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
id|cmd-&gt;pid
OL
l_int|0
)paren
id|error
c_func
(paren
l_string|&quot;cannot fork() for %s: %s&quot;
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|strerror
c_func
(paren
id|failed_errno
op_assign
id|errno
)paren
)paren
suffix:semicolon
macro_line|#else
(brace
r_int
id|s0
op_assign
l_int|1
comma
id|s1
op_assign
l_int|1
comma
id|s2
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* backups of stdin, stdout, stderr */
r_const
r_char
op_star
op_star
id|sargv
op_assign
id|cmd-&gt;argv
suffix:semicolon
r_char
op_star
op_star
id|env
op_assign
id|environ
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;no_stdin
)paren
(brace
id|s0
op_assign
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|dup_devnull
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|need_in
)paren
(brace
id|s0
op_assign
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
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
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;in
)paren
(brace
id|s0
op_assign
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|cmd-&gt;in
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd-&gt;no_stderr
)paren
(brace
id|s2
op_assign
id|dup
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|dup_devnull
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|need_err
)paren
(brace
id|s2
op_assign
id|dup
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|fderr
(braket
l_int|1
)braket
comma
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd-&gt;no_stdout
)paren
(brace
id|s1
op_assign
id|dup
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|dup_devnull
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;stdout_to_stderr
)paren
(brace
id|s1
op_assign
id|dup
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|dup2
c_func
(paren
l_int|2
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|need_out
)paren
(brace
id|s1
op_assign
id|dup
c_func
(paren
l_int|1
)paren
suffix:semicolon
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
id|s1
op_assign
id|dup
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|cmd-&gt;out
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd-&gt;dir
)paren
id|die
c_func
(paren
l_string|&quot;chdir in start_command() not implemented&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;env
)paren
id|env
op_assign
id|make_augmented_environ
c_func
(paren
id|cmd-&gt;env
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;git_cmd
)paren
(brace
id|cmd-&gt;argv
op_assign
id|prepare_git_cmd
c_func
(paren
id|cmd-&gt;argv
)paren
suffix:semicolon
)brace
id|cmd-&gt;pid
op_assign
id|mingw_spawnvpe
c_func
(paren
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|cmd-&gt;argv
comma
id|env
)paren
suffix:semicolon
id|failed_errno
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;pid
OL
l_int|0
op_logical_and
(paren
op_logical_neg
id|cmd-&gt;silent_exec_failure
op_logical_or
id|errno
op_ne
id|ENOENT
)paren
)paren
id|error
c_func
(paren
l_string|&quot;cannot spawn %s: %s&quot;
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;env
)paren
id|free_environ
c_func
(paren
id|env
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;git_cmd
)paren
id|free
c_func
(paren
id|cmd-&gt;argv
)paren
suffix:semicolon
id|cmd-&gt;argv
op_assign
id|sargv
suffix:semicolon
r_if
c_cond
(paren
id|s0
op_ge
l_int|0
)paren
id|dup2
c_func
(paren
id|s0
comma
l_int|0
)paren
comma
id|close
c_func
(paren
id|s0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s1
op_ge
l_int|0
)paren
id|dup2
c_func
(paren
id|s1
comma
l_int|1
)paren
comma
id|close
c_func
(paren
id|s1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s2
op_ge
l_int|0
)paren
id|dup2
c_func
(paren
id|s2
comma
l_int|2
)paren
comma
id|close
c_func
(paren
id|s2
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|close_pair
c_func
(paren
id|fdout
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;out
)paren
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_err
)paren
id|close_pair
c_func
(paren
id|fderr
)paren
suffix:semicolon
id|errno
op_assign
id|failed_errno
suffix:semicolon
r_return
l_int|1
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
)paren
id|close
c_func
(paren
id|cmd-&gt;out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_err
)paren
id|close
c_func
(paren
id|fderr
(braket
l_int|1
)braket
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
r_return
id|wait_or_whine
c_func
(paren
id|cmd-&gt;pid
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|cmd-&gt;silent_exec_failure
)paren
suffix:semicolon
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
DECL|function|prepare_run_command_v_opt
r_static
r_void
id|prepare_run_command_v_opt
c_func
(paren
r_struct
id|child_process
op_star
id|cmd
comma
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
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cmd
)paren
)paren
suffix:semicolon
id|cmd-&gt;argv
op_assign
id|argv
suffix:semicolon
id|cmd-&gt;no_stdin
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
id|cmd-&gt;git_cmd
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
id|cmd-&gt;stdout_to_stderr
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
id|cmd-&gt;silent_exec_failure
op_assign
id|opt
op_amp
id|RUN_SILENT_EXEC_FAILURE
ques
c_cond
l_int|1
suffix:colon
l_int|0
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
id|prepare_run_command_v_opt
c_func
(paren
op_amp
id|cmd
comma
id|argv
comma
id|opt
)paren
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
DECL|function|run_command_v_opt_cd_env
r_int
id|run_command_v_opt_cd_env
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
comma
r_const
r_char
op_star
id|dir
comma
r_const
r_char
op_star
r_const
op_star
id|env
)paren
(brace
r_struct
id|child_process
id|cmd
suffix:semicolon
id|prepare_run_command_v_opt
c_func
(paren
op_amp
id|cmd
comma
id|argv
comma
id|opt
)paren
suffix:semicolon
id|cmd.dir
op_assign
id|dir
suffix:semicolon
id|cmd.env
op_assign
id|env
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
macro_line|#ifdef WIN32
DECL|function|run_thread
r_static
r_int
id|__stdcall
id|run_thread
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|async
op_star
id|async
op_assign
id|data
suffix:semicolon
r_return
id|async
op_member_access_from_pointer
id|proc
c_func
(paren
id|async-&gt;fd_for_proc
comma
id|async-&gt;data
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|start_async
r_int
id|start_async
c_func
(paren
r_struct
id|async
op_star
id|async
)paren
(brace
r_int
id|pipe_out
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pipe_out
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot create pipe: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|async-&gt;out
op_assign
id|pipe_out
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#ifndef WIN32
multiline_comment|/* Flush stdio before fork() to avoid cloning buffers */
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|async-&gt;pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|async-&gt;pid
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;fork (async) failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close_pair
c_func
(paren
id|pipe_out
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|async-&gt;pid
)paren
(brace
id|close
c_func
(paren
id|pipe_out
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
op_logical_neg
op_logical_neg
id|async
op_member_access_from_pointer
id|proc
c_func
(paren
id|pipe_out
(braket
l_int|1
)braket
comma
id|async-&gt;data
)paren
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|pipe_out
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#else
id|async-&gt;fd_for_proc
op_assign
id|pipe_out
(braket
l_int|1
)braket
suffix:semicolon
id|async-&gt;tid
op_assign
(paren
id|HANDLE
)paren
id|_beginthreadex
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|run_thread
comma
id|async
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|async-&gt;tid
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot create thread: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close_pair
c_func
(paren
id|pipe_out
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|finish_async
r_int
id|finish_async
c_func
(paren
r_struct
id|async
op_star
id|async
)paren
(brace
macro_line|#ifndef WIN32
r_int
id|ret
op_assign
id|wait_or_whine
c_func
(paren
id|async-&gt;pid
comma
l_string|&quot;child process&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#else
id|DWORD
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|WaitForSingleObject
c_func
(paren
id|async-&gt;tid
comma
id|INFINITE
)paren
op_ne
id|WAIT_OBJECT_0
)paren
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;waiting for thread failed: %lu&quot;
comma
id|GetLastError
c_func
(paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|GetExitCodeThread
c_func
(paren
id|async-&gt;tid
comma
op_amp
id|ret
)paren
)paren
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;cannot get thread exit code: %lu&quot;
comma
id|GetLastError
c_func
(paren
)paren
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|async-&gt;tid
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|function|run_hook
r_int
id|run_hook
c_func
(paren
r_const
r_char
op_star
id|index_file
comma
r_const
r_char
op_star
id|name
comma
dot
dot
dot
)paren
(brace
r_struct
id|child_process
id|hook
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv
op_assign
l_int|NULL
comma
op_star
id|env
(braket
l_int|2
)braket
suffix:semicolon
r_char
id|index
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|alloc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;hooks/%s&quot;
comma
id|name
)paren
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|name
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|argv
comma
id|i
op_plus
l_int|1
comma
id|alloc
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|git_path
c_func
(paren
l_string|&quot;hooks/%s&quot;
comma
id|name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argv
(braket
id|i
op_minus
l_int|1
)braket
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|argv
comma
id|i
op_plus
l_int|1
comma
id|alloc
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_const
r_char
op_star
)paren
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hook
comma
l_int|0
comma
r_sizeof
(paren
id|hook
)paren
)paren
suffix:semicolon
id|hook.argv
op_assign
id|argv
suffix:semicolon
id|hook.no_stdin
op_assign
l_int|1
suffix:semicolon
id|hook.stdout_to_stderr
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|index_file
)paren
(brace
id|snprintf
c_func
(paren
id|index
comma
r_sizeof
(paren
id|index
)paren
comma
l_string|&quot;GIT_INDEX_FILE=%s&quot;
comma
id|index_file
)paren
suffix:semicolon
id|env
(braket
l_int|0
)braket
op_assign
id|index
suffix:semicolon
id|env
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|hook.env
op_assign
id|env
suffix:semicolon
)brace
id|ret
op_assign
id|run_command
c_func
(paren
op_amp
id|hook
)paren
suffix:semicolon
id|free
c_func
(paren
id|argv
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
