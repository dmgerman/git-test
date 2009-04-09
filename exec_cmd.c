macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|macro|MAX_ARGS
mdefine_line|#define MAX_ARGS&t;32
r_extern
r_char
op_star
op_star
id|environ
suffix:semicolon
DECL|variable|argv_exec_path
r_static
r_const
r_char
op_star
id|argv_exec_path
suffix:semicolon
DECL|variable|argv0_path
r_static
r_const
r_char
op_star
id|argv0_path
suffix:semicolon
DECL|function|system_path
r_const
r_char
op_star
id|system_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_absolute_path
c_func
(paren
id|path
)paren
op_logical_and
id|argv0_path
)paren
(brace
r_struct
id|strbuf
id|d
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|d
comma
l_string|&quot;%s/%s&quot;
comma
id|argv0_path
comma
id|path
)paren
suffix:semicolon
id|path
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|d
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|path
suffix:semicolon
)brace
DECL|function|git_set_argv0_path
r_void
id|git_set_argv0_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|argv0_path
op_assign
id|path
suffix:semicolon
)brace
DECL|function|git_set_argv_exec_path
r_void
id|git_set_argv_exec_path
c_func
(paren
r_const
r_char
op_star
id|exec_path
)paren
(brace
id|argv_exec_path
op_assign
id|exec_path
suffix:semicolon
multiline_comment|/*&n;&t; * Propagate this setting to external programs.&n;&t; */
id|setenv
c_func
(paren
id|EXEC_PATH_ENVIRONMENT
comma
id|exec_path
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the highest-priority, location to look for git programs. */
DECL|function|git_exec_path
r_const
r_char
op_star
id|git_exec_path
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
id|argv_exec_path
)paren
r_return
id|argv_exec_path
suffix:semicolon
id|env
op_assign
id|getenv
c_func
(paren
id|EXEC_PATH_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|env
op_logical_and
op_star
id|env
)paren
(brace
r_return
id|env
suffix:semicolon
)brace
r_return
id|system_path
c_func
(paren
id|GIT_EXEC_PATH
)paren
suffix:semicolon
)brace
DECL|function|add_path
r_static
r_void
id|add_path
c_func
(paren
r_struct
id|strbuf
op_star
id|out
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|path
op_logical_and
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|path
)paren
)paren
id|strbuf_addstr
c_func
(paren
id|out
comma
id|path
)paren
suffix:semicolon
r_else
id|strbuf_addstr
c_func
(paren
id|out
comma
id|make_nonrelative_path
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|out
comma
id|PATH_SEP
)paren
suffix:semicolon
)brace
)brace
DECL|function|setup_path
r_void
id|setup_path
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|old_path
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
suffix:semicolon
r_struct
id|strbuf
id|new_path
op_assign
id|STRBUF_INIT
suffix:semicolon
id|add_path
c_func
(paren
op_amp
id|new_path
comma
id|argv_exec_path
)paren
suffix:semicolon
id|add_path
c_func
(paren
op_amp
id|new_path
comma
id|getenv
c_func
(paren
id|EXEC_PATH_ENVIRONMENT
)paren
)paren
suffix:semicolon
id|add_path
c_func
(paren
op_amp
id|new_path
comma
id|system_path
c_func
(paren
id|GIT_EXEC_PATH
)paren
)paren
suffix:semicolon
id|add_path
c_func
(paren
op_amp
id|new_path
comma
id|argv0_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_path
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
id|old_path
)paren
suffix:semicolon
r_else
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
l_string|&quot;/usr/local/bin:/usr/bin:/bin&quot;
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;PATH&quot;
comma
id|new_path.buf
comma
l_int|1
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|new_path
)paren
suffix:semicolon
)brace
DECL|function|prepare_git_cmd
r_const
r_char
op_star
op_star
id|prepare_git_cmd
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
l_int|2
)paren
)paren
suffix:semicolon
id|nargv
(braket
l_int|0
)braket
op_assign
l_string|&quot;git&quot;
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
id|nargv
(braket
id|argc
op_plus
l_int|1
)braket
op_assign
id|argv
(braket
id|argc
)braket
suffix:semicolon
id|nargv
(braket
id|argc
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|nargv
suffix:semicolon
)brace
DECL|function|execv_git_cmd
r_int
id|execv_git_cmd
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
id|prepare_git_cmd
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
multiline_comment|/* execvp() can only ever return if it fails */
id|execvp
c_func
(paren
l_string|&quot;git&quot;
comma
(paren
r_char
op_star
op_star
)paren
id|nargv
)paren
suffix:semicolon
id|trace_printf
c_func
(paren
l_string|&quot;trace: exec failed: %s&bslash;n&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
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
DECL|function|execl_git_cmd
r_int
id|execl_git_cmd
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
dot
dot
dot
)paren
(brace
r_int
id|argc
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
id|MAX_ARGS
op_plus
l_int|1
)braket
suffix:semicolon
r_const
r_char
op_star
id|arg
suffix:semicolon
id|va_list
id|param
suffix:semicolon
id|va_start
c_func
(paren
id|param
comma
id|cmd
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|cmd
suffix:semicolon
id|argc
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|argc
OL
id|MAX_ARGS
)paren
(brace
id|arg
op_assign
id|argv
(braket
id|argc
op_increment
)braket
op_assign
id|va_arg
c_func
(paren
id|param
comma
r_char
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_break
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|param
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAX_ARGS
op_le
id|argc
)paren
r_return
id|error
c_func
(paren
l_string|&quot;too many args to run %s&quot;
comma
id|cmd
)paren
suffix:semicolon
id|argv
(braket
id|argc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|execv_git_cmd
c_func
(paren
id|argv
)paren
suffix:semicolon
)brace
eof
