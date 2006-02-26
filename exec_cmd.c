macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
DECL|macro|MAX_ARGS
mdefine_line|#define MAX_ARGS&t;32
r_extern
r_char
op_star
op_star
id|environ
suffix:semicolon
DECL|variable|builtin_exec_path
r_static
r_const
r_char
op_star
id|builtin_exec_path
op_assign
id|GIT_EXEC_PATH
suffix:semicolon
DECL|variable|current_exec_path
r_static
r_const
r_char
op_star
id|current_exec_path
op_assign
l_int|NULL
suffix:semicolon
DECL|function|git_set_exec_path
r_void
id|git_set_exec_path
c_func
(paren
r_const
r_char
op_star
id|exec_path
)paren
(brace
id|current_exec_path
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
id|current_exec_path
)paren
r_return
id|current_exec_path
suffix:semicolon
id|env
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_EXEC_PATH&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|env
)paren
(brace
r_return
id|env
suffix:semicolon
)brace
r_return
id|builtin_exec_path
suffix:semicolon
)brace
DECL|function|execv_git_cmd
r_int
id|execv_git_cmd
c_func
(paren
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
id|git_command
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|len
comma
id|err
comma
id|i
suffix:semicolon
r_const
r_char
op_star
id|paths
(braket
)braket
op_assign
(brace
id|current_exec_path
comma
id|getenv
c_func
(paren
l_string|&quot;GIT_EXEC_PATH&quot;
)paren
comma
id|builtin_exec_path
)brace
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
r_sizeof
(paren
id|paths
)paren
op_div
r_sizeof
(paren
id|paths
(braket
l_int|0
)braket
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
r_const
r_char
op_star
id|exec_dir
op_assign
id|paths
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exec_dir
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_star
id|exec_dir
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|getcwd
c_func
(paren
id|git_command
comma
r_sizeof
(paren
id|git_command
)paren
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: cannot determine &quot;
l_string|&quot;current directory&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|git_command
)paren
suffix:semicolon
multiline_comment|/* Trivial cleanup */
r_while
c_loop
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|exec_dir
comma
l_string|&quot;./&quot;
comma
l_int|2
)paren
)paren
(brace
id|exec_dir
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
op_star
id|exec_dir
op_eq
l_char|&squot;/&squot;
)paren
id|exec_dir
op_increment
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|git_command
op_plus
id|len
comma
r_sizeof
(paren
id|git_command
)paren
id|len
comma
l_string|&quot;/%s&quot;
comma
id|exec_dir
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|git_command
comma
id|exec_dir
)paren
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|git_command
)paren
suffix:semicolon
id|len
op_add_assign
id|snprintf
c_func
(paren
id|git_command
op_plus
id|len
comma
r_sizeof
(paren
id|git_command
)paren
id|len
comma
l_string|&quot;/git-%s&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|git_command
)paren
op_le
id|len
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: command name given is too long.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* argv[0] must be the git command, but the argv array&n;&t;&t; * belongs to the caller, and my be reused in&n;&t;&t; * subsequent loop iterations. Save argv[0] and&n;&t;&t; * restore it on error.&n;&t;&t; */
id|tmp
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|git_command
suffix:semicolon
multiline_comment|/* execve() can only ever return if it fails */
id|execve
c_func
(paren
id|git_command
comma
id|argv
comma
id|environ
)paren
suffix:semicolon
id|err
op_assign
id|errno
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|tmp
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|execl_git_cmd
r_int
id|execl_git_cmd
c_func
(paren
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
r_char
op_star
id|argv
(braket
id|MAX_ARGS
op_plus
l_int|1
)braket
suffix:semicolon
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
