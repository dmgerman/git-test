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
DECL|function|builtin_exec_path
r_static
r_const
r_char
op_star
id|builtin_exec_path
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef __MINGW32__
r_return
id|GIT_EXEC_PATH
suffix:semicolon
macro_line|#else
r_int
id|len
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|q
comma
op_star
id|sl
suffix:semicolon
r_static
r_char
op_star
id|ep
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
r_return
id|ep
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|_pgmptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|2
)paren
r_return
id|ep
op_assign
l_string|&quot;.&quot;
suffix:semicolon
id|p
op_assign
id|ep
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|q
op_assign
id|_pgmptr
suffix:semicolon
id|sl
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* copy program name, turn &squot;&bslash;&bslash;&squot; into &squot;/&squot;, skip last part */
r_while
c_loop
(paren
(paren
op_star
id|p
op_assign
op_star
id|q
)paren
)paren
(brace
r_if
c_cond
(paren
op_star
id|q
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_or
op_star
id|q
op_eq
l_char|&squot;/&squot;
)paren
(brace
op_star
id|p
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|sl
op_assign
id|p
suffix:semicolon
)brace
id|p
op_increment
comma
id|q
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sl
)paren
op_star
id|sl
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
id|ep
(braket
l_int|0
)braket
op_assign
l_char|&squot;.&squot;
comma
id|ep
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|ep
suffix:semicolon
macro_line|#endif
)brace
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
id|builtin_exec_path
c_func
(paren
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
id|make_absolute_path
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
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|new_path
comma
l_int|0
)paren
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
id|builtin_exec_path
c_func
(paren
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
