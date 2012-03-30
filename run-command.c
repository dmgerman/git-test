macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;argv-array.h&quot;
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
macro_line|#ifndef WIN32
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
macro_line|#endif
DECL|function|locate_in_PATH
r_static
r_char
op_star
id|locate_in_PATH
c_func
(paren
r_const
r_char
op_star
id|file
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_const
r_char
op_star
id|end
op_assign
id|strchrnul
c_func
(paren
id|p
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
multiline_comment|/* POSIX specifies an empty entry as the current directory. */
r_if
c_cond
(paren
id|end
op_ne
id|p
)paren
(brace
id|strbuf_add
c_func
(paren
op_amp
id|buf
comma
id|p
comma
id|end
id|p
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|buf.buf
comma
id|F_OK
)paren
)paren
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|end
)paren
r_break
suffix:semicolon
id|p
op_assign
id|end
op_plus
l_int|1
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|exists_in_PATH
r_static
r_int
id|exists_in_PATH
c_func
(paren
r_const
r_char
op_star
id|file
)paren
(brace
r_char
op_star
id|r
op_assign
id|locate_in_PATH
c_func
(paren
id|file
)paren
suffix:semicolon
id|free
c_func
(paren
id|r
)paren
suffix:semicolon
r_return
id|r
op_ne
l_int|NULL
suffix:semicolon
)brace
DECL|function|sane_execvp
r_int
id|sane_execvp
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_char
op_star
r_const
id|argv
(braket
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|execvp
c_func
(paren
id|file
comma
id|argv
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* cannot happen ;-) */
multiline_comment|/*&n;&t; * When a command can&squot;t be found because one of the directories&n;&t; * listed in $PATH is unsearchable, execvp reports EACCES, but&n;&t; * careful usability testing (read: analysis of occasional bug&n;&t; * reports) reveals that &quot;No such file or directory&quot; is more&n;&t; * intuitive.&n;&t; *&n;&t; * We avoid commands with &quot;/&quot;, because execvp will not do $PATH&n;&t; * lookups in that case.&n;&t; *&n;&t; * The reassignment of EACCES to errno looks like a no-op below,&n;&t; * but we need to protect against exists_in_PATH overwriting errno.&n;&t; */
r_if
c_cond
(paren
id|errno
op_eq
id|EACCES
op_logical_and
op_logical_neg
id|strchr
c_func
(paren
id|file
comma
l_char|&squot;/&squot;
)paren
)paren
id|errno
op_assign
id|exists_in_PATH
c_func
(paren
id|file
)paren
ques
c_cond
id|EACCES
suffix:colon
id|ENOENT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|prepare_shell_cmd
r_static
r_const
r_char
op_star
op_star
id|prepare_shell_cmd
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|argc
comma
id|nargc
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
op_star
id|nargv
suffix:semicolon
r_for
c_loop
(paren
id|argc
op_assign
l_int|0
suffix:semicolon
id|argv
(braket
id|argc
)braket
suffix:semicolon
id|argc
op_increment
)paren
suffix:semicolon
multiline_comment|/* just counting */
multiline_comment|/* +1 for NULL, +3 for &quot;sh -c&quot; plus extra $0 */
id|nargv
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|nargv
)paren
op_star
(paren
id|argc
op_plus
l_int|1
op_plus
l_int|3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;BUG: shell command is empty&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcspn
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;|&amp;;&lt;&gt;()$`&bslash;&bslash;&bslash;&quot;&squot; &bslash;t&bslash;n*?[#~=%&quot;
)paren
op_ne
id|strlen
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
)paren
(brace
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
l_string|&quot;sh&quot;
suffix:semicolon
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
l_string|&quot;-c&quot;
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_else
(brace
r_struct
id|strbuf
id|arg0
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|arg0
comma
l_string|&quot;%s &bslash;&quot;$@&bslash;&quot;&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|arg0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|argc
op_assign
l_int|0
suffix:semicolon
id|argv
(braket
id|argc
)braket
suffix:semicolon
id|argc
op_increment
)paren
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
id|argv
(braket
id|argc
)braket
suffix:semicolon
id|nargv
(braket
id|nargc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|nargv
suffix:semicolon
)brace
macro_line|#ifndef WIN32
DECL|function|execv_shell_cmd
r_static
r_int
id|execv_shell_cmd
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_const
r_char
op_star
op_star
id|nargv
op_assign
id|prepare_shell_cmd
c_func
(paren
id|argv
)paren
suffix:semicolon
id|trace_argv_printf
c_func
(paren
id|nargv
comma
l_string|&quot;trace: exec:&quot;
)paren
suffix:semicolon
id|sane_execvp
c_func
(paren
id|nargv
(braket
l_int|0
)braket
comma
(paren
r_char
op_star
op_star
)paren
id|nargv
)paren
suffix:semicolon
id|free
c_func
(paren
id|nargv
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef WIN32
DECL|variable|child_err
r_static
r_int
id|child_err
op_assign
l_int|2
suffix:semicolon
DECL|variable|child_notifier
r_static
r_int
id|child_notifier
op_assign
l_int|1
suffix:semicolon
DECL|function|notify_parent
r_static
r_void
id|notify_parent
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * execvp failed.  If possible, we&squot;d like to let start_command&n;&t; * know, so failures like ENOENT can be handled right away; but&n;&t; * otherwise, finish_command will still report the error.&n;&t; */
id|xwrite
c_func
(paren
id|child_notifier
comma
l_string|&quot;&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
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
id|vwritef
c_func
(paren
id|child_err
comma
l_string|&quot;fatal: &quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
m_exit
(paren
l_int|128
)paren
suffix:semicolon
)brace
DECL|function|error_child
r_static
r_void
id|error_child
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
id|vwritef
c_func
(paren
id|child_err
comma
l_string|&quot;error: &quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifndef WIN32
(brace
r_int
id|notify_pipe
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
id|notify_pipe
)paren
)paren
id|notify_pipe
(braket
l_int|0
)braket
op_assign
id|notify_pipe
(braket
l_int|1
)braket
op_assign
l_int|1
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
id|set_error_routine
c_func
(paren
id|error_child
)paren
suffix:semicolon
id|close
c_func
(paren
id|notify_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|set_cloexec
c_func
(paren
id|notify_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|child_notifier
op_assign
id|notify_pipe
(braket
l_int|1
)braket
suffix:semicolon
id|atexit
c_func
(paren
id|notify_parent
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
r_else
r_if
c_cond
(paren
id|cmd-&gt;err
OG
l_int|1
)paren
(brace
id|dup2
c_func
(paren
id|cmd-&gt;err
comma
l_int|2
)paren
suffix:semicolon
id|close
c_func
(paren
id|cmd-&gt;err
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
(brace
multiline_comment|/*&n;&t;&t;&t; * We cannot predict what the pre-exec callback does.&n;&t;&t;&t; * Forgo parent notification.&n;&t;&t;&t; */
id|close
c_func
(paren
id|child_notifier
)paren
suffix:semicolon
id|child_notifier
op_assign
l_int|1
suffix:semicolon
id|cmd
op_member_access_from_pointer
id|preexec_cb
c_func
(paren
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
r_if
c_cond
(paren
id|cmd-&gt;use_shell
)paren
(brace
id|execv_shell_cmd
c_func
(paren
id|cmd-&gt;argv
)paren
suffix:semicolon
)brace
r_else
(brace
id|sane_execvp
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
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cmd-&gt;silent_exec_failure
)paren
id|error
c_func
(paren
l_string|&quot;cannot run %s: %s&quot;
comma
id|cmd-&gt;argv
(braket
l_int|0
)braket
comma
id|strerror
c_func
(paren
id|ENOENT
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|127
)paren
suffix:semicolon
)brace
r_else
(brace
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
multiline_comment|/*&n;&t; * Wait for child&squot;s execvp. If the execvp succeeds (or if fork()&n;&t; * failed), EOF is seen immediately by the parent. Otherwise, the&n;&t; * child process sends a single byte.&n;&t; * Note that use of this infrastructure is completely advisory,&n;&t; * therefore, we keep error checks minimal.&n;&t; */
id|close
c_func
(paren
id|notify_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|notify_pipe
(braket
l_int|0
)braket
comma
op_amp
id|notify_pipe
(braket
l_int|1
)braket
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * At this point we know that fork() succeeded, but execvp()&n;&t;&t; * failed. Errors have been reported to our stderr.&n;&t;&t; */
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
id|failed_errno
op_assign
id|errno
suffix:semicolon
id|cmd-&gt;pid
op_assign
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|notify_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
(brace
r_int
id|fhin
op_assign
l_int|0
comma
id|fhout
op_assign
l_int|1
comma
id|fherr
op_assign
l_int|2
suffix:semicolon
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
id|fhin
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
id|O_RDWR
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|need_in
)paren
id|fhin
op_assign
id|dup
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
id|fhin
op_assign
id|dup
c_func
(paren
id|cmd-&gt;in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;no_stderr
)paren
id|fherr
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
id|O_RDWR
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|need_err
)paren
id|fherr
op_assign
id|dup
c_func
(paren
id|fderr
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;err
OG
l_int|2
)paren
id|fherr
op_assign
id|dup
c_func
(paren
id|cmd-&gt;err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;no_stdout
)paren
id|fhout
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
id|O_RDWR
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;stdout_to_stderr
)paren
id|fhout
op_assign
id|dup
c_func
(paren
id|fherr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|need_out
)paren
id|fhout
op_assign
id|dup
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
id|fhout
op_assign
id|dup
c_func
(paren
id|cmd-&gt;out
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
r_else
r_if
c_cond
(paren
id|cmd-&gt;use_shell
)paren
(brace
id|cmd-&gt;argv
op_assign
id|prepare_shell_cmd
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
comma
id|cmd-&gt;dir
comma
id|fhin
comma
id|fhout
comma
id|fherr
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
id|fhin
op_ne
l_int|0
)paren
id|close
c_func
(paren
id|fhin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fhout
op_ne
l_int|1
)paren
id|close
c_func
(paren
id|fhout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fherr
op_ne
l_int|2
)paren
id|close
c_func
(paren
id|fherr
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
r_else
r_if
c_cond
(paren
id|cmd-&gt;err
)paren
id|close
c_func
(paren
id|cmd-&gt;err
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
r_else
r_if
c_cond
(paren
id|cmd-&gt;err
)paren
id|close
c_func
(paren
id|cmd-&gt;err
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
id|cmd-&gt;use_shell
op_assign
id|opt
op_amp
id|RUN_USING_SHELL
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
macro_line|#ifndef NO_PTHREADS
DECL|variable|main_thread
r_static
id|pthread_t
id|main_thread
suffix:semicolon
DECL|variable|main_thread_set
r_static
r_int
id|main_thread_set
suffix:semicolon
DECL|variable|async_key
r_static
id|pthread_key_t
id|async_key
suffix:semicolon
DECL|function|run_thread
r_static
r_void
op_star
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
r_intptr
id|ret
suffix:semicolon
id|pthread_setspecific
c_func
(paren
id|async_key
comma
id|async
)paren
suffix:semicolon
id|ret
op_assign
id|async
op_member_access_from_pointer
id|proc
c_func
(paren
id|async-&gt;proc_in
comma
id|async-&gt;proc_out
comma
id|async-&gt;data
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ret
suffix:semicolon
)brace
DECL|function|die_async
r_static
id|NORETURN
r_void
id|die_async
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
id|vreportf
c_func
(paren
l_string|&quot;fatal: &quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pthread_equal
c_func
(paren
id|main_thread
comma
id|pthread_self
c_func
(paren
)paren
)paren
)paren
(brace
r_struct
id|async
op_star
id|async
op_assign
id|pthread_getspecific
c_func
(paren
id|async_key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|async-&gt;proc_in
op_ge
l_int|0
)paren
id|close
c_func
(paren
id|async-&gt;proc_in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|async-&gt;proc_out
op_ge
l_int|0
)paren
id|close
c_func
(paren
id|async-&gt;proc_out
)paren
suffix:semicolon
id|pthread_exit
c_func
(paren
(paren
r_void
op_star
)paren
l_int|128
)paren
suffix:semicolon
)brace
m_exit
(paren
l_int|128
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
r_int
id|proc_in
comma
id|proc_out
suffix:semicolon
id|need_in
op_assign
id|async-&gt;in
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
r_if
c_cond
(paren
id|async-&gt;out
OG
l_int|0
)paren
id|close
c_func
(paren
id|async-&gt;out
)paren
suffix:semicolon
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
)brace
id|async-&gt;in
op_assign
id|fdin
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|need_out
op_assign
id|async-&gt;out
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
r_else
r_if
c_cond
(paren
id|async-&gt;in
)paren
id|close
c_func
(paren
id|async-&gt;in
)paren
suffix:semicolon
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
)brace
id|async-&gt;out
op_assign
id|fdout
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|need_in
)paren
id|proc_in
op_assign
id|fdin
(braket
l_int|0
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|async-&gt;in
)paren
id|proc_in
op_assign
id|async-&gt;in
suffix:semicolon
r_else
id|proc_in
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|need_out
)paren
id|proc_out
op_assign
id|fdout
(braket
l_int|1
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|async-&gt;out
)paren
id|proc_out
op_assign
id|async-&gt;out
suffix:semicolon
r_else
id|proc_out
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef NO_PTHREADS
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
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|async-&gt;pid
)paren
(brace
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
l_int|1
)braket
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
id|proc_in
comma
id|proc_out
comma
id|async-&gt;data
)paren
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
id|async-&gt;in
)paren
id|close
c_func
(paren
id|async-&gt;in
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
id|async-&gt;out
)paren
id|close
c_func
(paren
id|async-&gt;out
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|main_thread_set
)paren
(brace
multiline_comment|/*&n;&t;&t; * We assume that the first time that start_async is called&n;&t;&t; * it is from the main thread.&n;&t;&t; */
id|main_thread_set
op_assign
l_int|1
suffix:semicolon
id|main_thread
op_assign
id|pthread_self
c_func
(paren
)paren
suffix:semicolon
id|pthread_key_create
c_func
(paren
op_amp
id|async_key
comma
l_int|NULL
)paren
suffix:semicolon
id|set_die_routine
c_func
(paren
id|die_async
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|proc_in
op_ge
l_int|0
)paren
id|set_cloexec
c_func
(paren
id|proc_in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_out
op_ge
l_int|0
)paren
id|set_cloexec
c_func
(paren
id|proc_out
)paren
suffix:semicolon
id|async-&gt;proc_in
op_assign
id|proc_in
suffix:semicolon
id|async-&gt;proc_out
op_assign
id|proc_out
suffix:semicolon
(brace
r_int
id|err
op_assign
id|pthread_create
c_func
(paren
op_amp
id|async-&gt;tid
comma
l_int|NULL
comma
id|run_thread
comma
id|async
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
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
id|err
)paren
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
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
id|async-&gt;in
)paren
id|close
c_func
(paren
id|async-&gt;in
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
id|async-&gt;out
)paren
id|close
c_func
(paren
id|async-&gt;out
)paren
suffix:semicolon
r_return
l_int|1
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
macro_line|#ifdef NO_PTHREADS
r_return
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
r_void
op_star
id|ret
op_assign
(paren
r_void
op_star
)paren
(paren
r_intptr
)paren
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pthread_join
c_func
(paren
id|async-&gt;tid
comma
op_amp
id|ret
)paren
)paren
id|error
c_func
(paren
l_string|&quot;pthread_join failed&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
r_intptr
)paren
id|ret
suffix:semicolon
macro_line|#endif
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
r_struct
id|argv_array
id|argv
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
r_const
r_char
op_star
id|p
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
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
id|git_path
c_func
(paren
l_string|&quot;hooks/%s&quot;
comma
id|name
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
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
)paren
)paren
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
id|p
)paren
suffix:semicolon
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
id|argv.argv
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
id|argv_array_clear
c_func
(paren
op_amp
id|argv
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
