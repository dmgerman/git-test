macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|git_usage_string
r_const
r_char
id|git_usage_string
(braket
)braket
op_assign
l_string|&quot;git [--version] [--exec-path[=GIT_EXEC_PATH]] [-p|--paginate] [--bare] [--git-dir=GIT_DIR] [--work-tree=GIT_WORK_TREE] [--help] COMMAND [ARGS]&quot;
suffix:semicolon
DECL|function|prepend_to_path
r_static
r_void
id|prepend_to_path
c_func
(paren
r_const
r_char
op_star
id|dir
comma
r_int
id|len
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
r_char
op_star
id|path
suffix:semicolon
r_int
id|path_len
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_path
)paren
id|old_path
op_assign
l_string|&quot;/usr/local/bin:/usr/bin:/bin&quot;
suffix:semicolon
id|path_len
op_assign
id|len
op_plus
id|strlen
c_func
(paren
id|old_path
)paren
op_plus
l_int|1
suffix:semicolon
id|path
op_assign
id|xmalloc
c_func
(paren
id|path_len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|dir
comma
id|len
)paren
suffix:semicolon
id|path
(braket
id|len
)braket
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|path
op_plus
id|len
op_plus
l_int|1
comma
id|old_path
comma
id|path_len
id|len
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;PATH&quot;
comma
id|path
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
DECL|function|handle_options
r_static
r_int
id|handle_options
c_func
(paren
r_const
r_char
op_star
op_star
op_star
id|argv
comma
r_int
op_star
id|argc
comma
r_int
op_star
id|envchanged
)paren
(brace
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|argc
OG
l_int|0
)paren
(brace
r_const
r_char
op_star
id|cmd
op_assign
(paren
op_star
id|argv
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cmd
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * For legacy reasons, the &quot;version&quot; and &quot;help&quot;&n;&t;&t; * commands can be written with &quot;--&quot; prepended&n;&t;&t; * to make them look like flags.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--help&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--version&quot;
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Check remaining flags.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--exec-path&quot;
)paren
)paren
(brace
id|cmd
op_add_assign
l_int|11
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
l_char|&squot;=&squot;
)paren
id|git_set_exec_path
c_func
(paren
id|cmd
op_plus
l_int|1
)paren
suffix:semicolon
r_else
(brace
id|puts
c_func
(paren
id|git_exec_path
c_func
(paren
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;-p&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--paginate&quot;
)paren
)paren
(brace
id|setup_pager
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--git-dir&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_star
id|argc
OL
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No directory given for --git-dir.&bslash;n&quot;
)paren
suffix:semicolon
id|usage
c_func
(paren
id|git_usage_string
)paren
suffix:semicolon
)brace
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
(paren
op_star
id|argv
)paren
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|envchanged
)paren
op_star
id|envchanged
op_assign
l_int|1
suffix:semicolon
(paren
op_star
id|argv
)paren
op_increment
suffix:semicolon
(paren
op_star
id|argc
)paren
op_decrement
suffix:semicolon
id|handled
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--git-dir=&quot;
)paren
)paren
(brace
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
id|cmd
op_plus
l_int|10
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|envchanged
)paren
op_star
id|envchanged
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--work-tree&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_star
id|argc
OL
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No directory given for --work-tree.&bslash;n&quot;
)paren
suffix:semicolon
id|usage
c_func
(paren
id|git_usage_string
)paren
suffix:semicolon
)brace
id|setenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
comma
(paren
op_star
id|argv
)paren
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|envchanged
)paren
op_star
id|envchanged
op_assign
l_int|1
suffix:semicolon
(paren
op_star
id|argv
)paren
op_increment
suffix:semicolon
(paren
op_star
id|argc
)paren
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--work-tree=&quot;
)paren
)paren
(brace
id|setenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
comma
id|cmd
op_plus
l_int|12
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|envchanged
)paren
op_star
id|envchanged
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;--bare&quot;
)paren
)paren
(brace
r_static
r_char
id|git_dir
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
id|getcwd
c_func
(paren
id|git_dir
comma
r_sizeof
(paren
id|git_dir
)paren
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|envchanged
)paren
op_star
id|envchanged
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unknown option: %s&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
id|usage
c_func
(paren
id|git_usage_string
)paren
suffix:semicolon
)brace
(paren
op_star
id|argv
)paren
op_increment
suffix:semicolon
(paren
op_star
id|argc
)paren
op_decrement
suffix:semicolon
id|handled
op_increment
suffix:semicolon
)brace
r_return
id|handled
suffix:semicolon
)brace
DECL|variable|alias_command
r_static
r_const
r_char
op_star
id|alias_command
suffix:semicolon
DECL|variable|alias_string
r_static
r_char
op_star
id|alias_string
suffix:semicolon
DECL|function|git_alias_config
r_static
r_int
id|git_alias_config
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;alias.&quot;
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
id|alias_command
)paren
)paren
(brace
id|alias_string
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|split_cmdline
r_static
r_int
id|split_cmdline
c_func
(paren
r_char
op_star
id|cmdline
comma
r_const
r_char
op_star
op_star
op_star
id|argv
)paren
(brace
r_int
id|src
comma
id|dst
comma
id|count
op_assign
l_int|0
comma
id|size
op_assign
l_int|16
suffix:semicolon
r_char
id|quoted
op_assign
l_int|0
suffix:semicolon
op_star
id|argv
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_char
op_star
)paren
op_star
id|size
)paren
suffix:semicolon
multiline_comment|/* split alias_string */
(paren
op_star
id|argv
)paren
(braket
id|count
op_increment
)braket
op_assign
id|cmdline
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
id|dst
op_assign
l_int|0
suffix:semicolon
id|cmdline
(braket
id|src
)braket
suffix:semicolon
)paren
(brace
r_char
id|c
op_assign
id|cmdline
(braket
id|src
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quoted
op_logical_and
id|isspace
c_func
(paren
id|c
)paren
)paren
(brace
id|cmdline
(braket
id|dst
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cmdline
(braket
op_increment
id|src
)braket
op_logical_and
id|isspace
c_func
(paren
id|cmdline
(braket
id|src
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* skip */
r_if
c_cond
(paren
id|count
op_ge
id|size
)paren
(brace
id|size
op_add_assign
l_int|16
suffix:semicolon
op_star
id|argv
op_assign
id|xrealloc
c_func
(paren
op_star
id|argv
comma
r_sizeof
(paren
r_char
op_star
)paren
op_star
id|size
)paren
suffix:semicolon
)brace
(paren
op_star
id|argv
)paren
(braket
id|count
op_increment
)braket
op_assign
id|cmdline
op_plus
id|dst
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|quoted
op_logical_and
(paren
id|c
op_eq
l_char|&squot;&bslash;&squot;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;&quot;&squot;
)paren
)paren
(brace
id|quoted
op_assign
id|c
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
id|quoted
)paren
(brace
id|quoted
op_assign
l_int|0
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
id|quoted
op_ne
l_char|&squot;&bslash;&squot;&squot;
)paren
(brace
id|src
op_increment
suffix:semicolon
id|c
op_assign
id|cmdline
(braket
id|src
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|free
c_func
(paren
op_star
id|argv
)paren
suffix:semicolon
op_star
id|argv
op_assign
l_int|NULL
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;cmdline ends with &bslash;&bslash;&quot;
)paren
suffix:semicolon
)brace
)brace
id|cmdline
(braket
id|dst
op_increment
)braket
op_assign
id|c
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
)brace
id|cmdline
(braket
id|dst
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|quoted
)paren
(brace
id|free
c_func
(paren
op_star
id|argv
)paren
suffix:semicolon
op_star
id|argv
op_assign
l_int|NULL
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unclosed quote&quot;
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|handle_alias
r_static
r_int
id|handle_alias
c_func
(paren
r_int
op_star
id|argcp
comma
r_const
r_char
op_star
op_star
op_star
id|argv
)paren
(brace
r_int
id|nongit
op_assign
l_int|0
comma
id|envchanged
op_assign
l_int|0
comma
id|ret
op_assign
l_int|0
comma
id|saved_errno
op_assign
id|errno
suffix:semicolon
r_const
r_char
op_star
id|subdir
suffix:semicolon
r_int
id|count
comma
id|option_count
suffix:semicolon
r_const
r_char
op_star
op_star
id|new_argv
suffix:semicolon
id|subdir
op_assign
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
id|alias_command
op_assign
(paren
op_star
id|argv
)paren
(braket
l_int|0
)braket
suffix:semicolon
id|git_config
c_func
(paren
id|git_alias_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alias_string
)paren
(brace
r_if
c_cond
(paren
id|alias_string
(braket
l_int|0
)braket
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|trace_printf
c_func
(paren
l_string|&quot;trace: alias to shell cmd: %s =&gt; %s&bslash;n&quot;
comma
id|alias_command
comma
id|alias_string
op_plus
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|system
c_func
(paren
id|alias_string
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
op_logical_and
id|WIFEXITED
c_func
(paren
id|ret
)paren
op_logical_and
id|WEXITSTATUS
c_func
(paren
id|ret
)paren
op_ne
l_int|127
)paren
m_exit
(paren
id|WEXITSTATUS
c_func
(paren
id|ret
)paren
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Failed to run &squot;%s&squot; when expanding alias &squot;%s&squot;&bslash;n&quot;
comma
id|alias_string
op_plus
l_int|1
comma
id|alias_command
)paren
suffix:semicolon
)brace
id|count
op_assign
id|split_cmdline
c_func
(paren
id|alias_string
comma
op_amp
id|new_argv
)paren
suffix:semicolon
id|option_count
op_assign
id|handle_options
c_func
(paren
op_amp
id|new_argv
comma
op_amp
id|count
comma
op_amp
id|envchanged
)paren
suffix:semicolon
r_if
c_cond
(paren
id|envchanged
)paren
id|die
c_func
(paren
l_string|&quot;alias &squot;%s&squot; changes environment variables&bslash;n&quot;
l_string|&quot;You can use &squot;!git&squot; in the alias to do this.&quot;
comma
id|alias_command
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|new_argv
id|option_count
comma
id|new_argv
comma
id|count
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|new_argv
op_sub_assign
id|option_count
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;empty alias for %s&quot;
comma
id|alias_command
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|alias_command
comma
id|new_argv
(braket
l_int|0
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;recursive alias: %s&quot;
comma
id|alias_command
)paren
suffix:semicolon
id|trace_argv_printf
c_func
(paren
id|new_argv
comma
id|count
comma
l_string|&quot;trace: alias expansion: %s =&gt;&quot;
comma
id|alias_command
)paren
suffix:semicolon
id|new_argv
op_assign
id|xrealloc
c_func
(paren
id|new_argv
comma
r_sizeof
(paren
r_char
op_star
)paren
op_star
(paren
id|count
op_plus
op_star
id|argcp
op_plus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* insert after command name */
id|memcpy
c_func
(paren
id|new_argv
op_plus
id|count
comma
op_star
id|argv
op_plus
l_int|1
comma
r_sizeof
(paren
r_char
op_star
)paren
op_star
op_star
id|argcp
)paren
suffix:semicolon
id|new_argv
(braket
id|count
op_plus
op_star
id|argcp
)braket
op_assign
l_int|NULL
suffix:semicolon
op_star
id|argv
op_assign
id|new_argv
suffix:semicolon
op_star
id|argcp
op_add_assign
id|count
l_int|1
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|subdir
)paren
id|chdir
c_func
(paren
id|subdir
)paren
suffix:semicolon
id|errno
op_assign
id|saved_errno
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|git_version_string
r_const
r_char
id|git_version_string
(braket
)braket
op_assign
id|GIT_VERSION
suffix:semicolon
DECL|macro|RUN_SETUP
mdefine_line|#define RUN_SETUP&t;(1&lt;&lt;0)
DECL|macro|USE_PAGER
mdefine_line|#define USE_PAGER&t;(1&lt;&lt;1)
multiline_comment|/*&n; * require working tree to be present -- anything uses this needs&n; * RUN_SETUP for reading from the configuration file.&n; */
DECL|macro|NEED_WORK_TREE
mdefine_line|#define NEED_WORK_TREE&t;(1&lt;&lt;2)
DECL|struct|cmd_struct
r_struct
id|cmd_struct
(brace
DECL|member|cmd
r_const
r_char
op_star
id|cmd
suffix:semicolon
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
comma
r_const
r_char
op_star
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|member|option
r_int
id|option
suffix:semicolon
)brace
suffix:semicolon
DECL|function|run_command
r_static
r_int
id|run_command
c_func
(paren
r_struct
id|cmd_struct
op_star
id|p
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|status
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_const
r_char
op_star
id|prefix
suffix:semicolon
id|prefix
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;option
op_amp
id|RUN_SETUP
)paren
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;option
op_amp
id|USE_PAGER
)paren
id|setup_pager
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;option
op_amp
id|NEED_WORK_TREE
)paren
op_logical_and
(paren
op_logical_neg
id|is_inside_work_tree
c_func
(paren
)paren
op_logical_or
id|is_inside_git_dir
c_func
(paren
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s must be run in a work tree&quot;
comma
id|p-&gt;cmd
)paren
suffix:semicolon
id|trace_argv_printf
c_func
(paren
id|argv
comma
id|argc
comma
l_string|&quot;trace: built-in: git&quot;
)paren
suffix:semicolon
id|status
op_assign
id|p
op_member_access_from_pointer
id|fn
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
multiline_comment|/* Somebody closed stdout? */
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fileno
c_func
(paren
id|stdout
)paren
comma
op_amp
id|st
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Ignore write errors for pipes and sockets.. */
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|st.st_mode
)paren
op_logical_or
id|S_ISSOCK
c_func
(paren
id|st.st_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Check for ENOSPC and EIO errors.. */
r_if
c_cond
(paren
id|fflush
c_func
(paren
id|stdout
)paren
)paren
id|die
c_func
(paren
l_string|&quot;write failure on standard output: %s&quot;
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
id|ferror
c_func
(paren
id|stdout
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unknown write failure on standard output&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|stdout
)paren
)paren
id|die
c_func
(paren
l_string|&quot;close failed on standard output: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_internal_command
r_static
r_void
id|handle_internal_command
c_func
(paren
r_int
id|argc
comma
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
id|cmd
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_static
r_struct
id|cmd_struct
id|commands
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;add&quot;
comma
id|cmd_add
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;annotate&quot;
comma
id|cmd_annotate
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;apply&quot;
comma
id|cmd_apply
)brace
comma
(brace
l_string|&quot;archive&quot;
comma
id|cmd_archive
)brace
comma
(brace
l_string|&quot;blame&quot;
comma
id|cmd_blame
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;branch&quot;
comma
id|cmd_branch
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;bundle&quot;
comma
id|cmd_bundle
)brace
comma
(brace
l_string|&quot;cat-file&quot;
comma
id|cmd_cat_file
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;checkout-index&quot;
comma
id|cmd_checkout_index
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;check-ref-format&quot;
comma
id|cmd_check_ref_format
)brace
comma
(brace
l_string|&quot;check-attr&quot;
comma
id|cmd_check_attr
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;cherry&quot;
comma
id|cmd_cherry
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;cherry-pick&quot;
comma
id|cmd_cherry_pick
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;commit-tree&quot;
comma
id|cmd_commit_tree
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;config&quot;
comma
id|cmd_config
)brace
comma
(brace
l_string|&quot;count-objects&quot;
comma
id|cmd_count_objects
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;describe&quot;
comma
id|cmd_describe
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;diff&quot;
comma
id|cmd_diff
comma
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;diff-files&quot;
comma
id|cmd_diff_files
)brace
comma
(brace
l_string|&quot;diff-index&quot;
comma
id|cmd_diff_index
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;diff-tree&quot;
comma
id|cmd_diff_tree
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;fetch--tool&quot;
comma
id|cmd_fetch__tool
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;fmt-merge-msg&quot;
comma
id|cmd_fmt_merge_msg
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;for-each-ref&quot;
comma
id|cmd_for_each_ref
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;format-patch&quot;
comma
id|cmd_format_patch
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;fsck&quot;
comma
id|cmd_fsck
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;fsck-objects&quot;
comma
id|cmd_fsck
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;gc&quot;
comma
id|cmd_gc
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;get-tar-commit-id&quot;
comma
id|cmd_get_tar_commit_id
)brace
comma
(brace
l_string|&quot;grep&quot;
comma
id|cmd_grep
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;help&quot;
comma
id|cmd_help
)brace
comma
(brace
l_string|&quot;init&quot;
comma
id|cmd_init_db
)brace
comma
(brace
l_string|&quot;init-db&quot;
comma
id|cmd_init_db
)brace
comma
(brace
l_string|&quot;log&quot;
comma
id|cmd_log
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;ls-files&quot;
comma
id|cmd_ls_files
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;ls-tree&quot;
comma
id|cmd_ls_tree
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;mailinfo&quot;
comma
id|cmd_mailinfo
)brace
comma
(brace
l_string|&quot;mailsplit&quot;
comma
id|cmd_mailsplit
)brace
comma
(brace
l_string|&quot;merge-base&quot;
comma
id|cmd_merge_base
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;merge-file&quot;
comma
id|cmd_merge_file
)brace
comma
(brace
l_string|&quot;mv&quot;
comma
id|cmd_mv
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;name-rev&quot;
comma
id|cmd_name_rev
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;pack-objects&quot;
comma
id|cmd_pack_objects
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;pickaxe&quot;
comma
id|cmd_blame
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;prune&quot;
comma
id|cmd_prune
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;prune-packed&quot;
comma
id|cmd_prune_packed
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;push&quot;
comma
id|cmd_push
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;read-tree&quot;
comma
id|cmd_read_tree
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;reflog&quot;
comma
id|cmd_reflog
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;repo-config&quot;
comma
id|cmd_config
)brace
comma
(brace
l_string|&quot;rerere&quot;
comma
id|cmd_rerere
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;rev-list&quot;
comma
id|cmd_rev_list
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;rev-parse&quot;
comma
id|cmd_rev_parse
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;revert&quot;
comma
id|cmd_revert
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;rm&quot;
comma
id|cmd_rm
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;runstatus&quot;
comma
id|cmd_runstatus
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;shortlog&quot;
comma
id|cmd_shortlog
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;show-branch&quot;
comma
id|cmd_show_branch
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;show&quot;
comma
id|cmd_show
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;stripspace&quot;
comma
id|cmd_stripspace
)brace
comma
(brace
l_string|&quot;symbolic-ref&quot;
comma
id|cmd_symbolic_ref
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;tar-tree&quot;
comma
id|cmd_tar_tree
)brace
comma
(brace
l_string|&quot;unpack-objects&quot;
comma
id|cmd_unpack_objects
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;update-index&quot;
comma
id|cmd_update_index
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;update-ref&quot;
comma
id|cmd_update_ref
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;upload-archive&quot;
comma
id|cmd_upload_archive
)brace
comma
(brace
l_string|&quot;version&quot;
comma
id|cmd_version
)brace
comma
(brace
l_string|&quot;whatchanged&quot;
comma
id|cmd_whatchanged
comma
id|RUN_SETUP
op_or
id|USE_PAGER
)brace
comma
(brace
l_string|&quot;write-tree&quot;
comma
id|cmd_write_tree
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;verify-pack&quot;
comma
id|cmd_verify_pack
)brace
comma
(brace
l_string|&quot;show-ref&quot;
comma
id|cmd_show_ref
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;pack-refs&quot;
comma
id|cmd_pack_refs
comma
id|RUN_SETUP
)brace
comma
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Turn &quot;git cmd --help&quot; into &quot;git help cmd&quot; */
r_if
c_cond
(paren
id|argc
OG
l_int|1
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--help&quot;
)paren
)paren
(brace
id|argv
(braket
l_int|1
)braket
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
id|cmd
op_assign
l_string|&quot;help&quot;
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|commands
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cmd_struct
op_star
id|p
op_assign
id|commands
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|p-&gt;cmd
comma
id|cmd
)paren
)paren
r_continue
suffix:semicolon
m_exit
(paren
id|run_command
c_func
(paren
id|p
comma
id|argc
comma
id|argv
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
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
id|cmd
op_assign
id|argv
(braket
l_int|0
)braket
ques
c_cond
id|argv
(braket
l_int|0
)braket
suffix:colon
l_string|&quot;git-help&quot;
suffix:semicolon
r_char
op_star
id|slash
op_assign
id|strrchr
c_func
(paren
id|cmd
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|exec_path
op_assign
l_int|NULL
suffix:semicolon
r_int
id|done_alias
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Take the basename of argv[0] as the command&n;&t; * name, and the dirname as the default exec_path&n;&t; * if it&squot;s an absolute path and we don&squot;t have&n;&t; * anything better.&n;&t; */
r_if
c_cond
(paren
id|slash
)paren
(brace
op_star
id|slash
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
l_char|&squot;/&squot;
)paren
id|exec_path
op_assign
id|cmd
suffix:semicolon
id|cmd
op_assign
id|slash
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * &quot;git-xxxx&quot; is the same as &quot;git xxxx&quot;, but we obviously:&n;&t; *&n;&t; *  - cannot take flags in between the &quot;git&quot; and the &quot;xxxx&quot;.&n;&t; *  - cannot execute it externally (since it would just do&n;&t; *    the same thing over again)&n;&t; *&n;&t; * So we just directly call the internal command handler, and&n;&t; * die if that one cannot handle it.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|cmd
comma
l_string|&quot;git-&quot;
)paren
)paren
(brace
id|cmd
op_add_assign
l_int|4
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|cmd
suffix:semicolon
id|handle_internal_command
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;cannot handle %s internally&quot;
comma
id|cmd
)paren
suffix:semicolon
)brace
multiline_comment|/* Look for flags.. */
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|handle_options
c_func
(paren
op_amp
id|argv
comma
op_amp
id|argc
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
id|argv
(braket
l_int|0
)braket
op_add_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Default command: &quot;help&quot; */
id|argv
(braket
l_int|0
)braket
op_assign
l_string|&quot;help&quot;
suffix:semicolon
id|argc
op_assign
l_int|1
suffix:semicolon
)brace
id|cmd
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * We search for git commands in the following order:&n;&t; *  - git_exec_path()&n;&t; *  - the path of the &quot;git&quot; command if we could find it&n;&t; *    in $0&n;&t; *  - the regular PATH.&n;&t; */
r_if
c_cond
(paren
id|exec_path
)paren
id|prepend_to_path
c_func
(paren
id|exec_path
comma
id|strlen
c_func
(paren
id|exec_path
)paren
)paren
suffix:semicolon
id|exec_path
op_assign
id|git_exec_path
c_func
(paren
)paren
suffix:semicolon
id|prepend_to_path
c_func
(paren
id|exec_path
comma
id|strlen
c_func
(paren
id|exec_path
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* See if it&squot;s an internal command */
id|handle_internal_command
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
multiline_comment|/* .. then try the external ones */
id|execv_git_cmd
c_func
(paren
id|argv
)paren
suffix:semicolon
multiline_comment|/* It could be an alias -- this works around the insanity&n;&t;&t; * of overriding &quot;git log&quot; with &quot;git show&quot; by having&n;&t;&t; * alias.log = show&n;&t;&t; */
r_if
c_cond
(paren
id|done_alias
op_logical_or
op_logical_neg
id|handle_alias
c_func
(paren
op_amp
id|argc
comma
op_amp
id|argv
)paren
)paren
r_break
suffix:semicolon
id|done_alias
op_assign
l_int|1
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
id|done_alias
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Expansion of alias &squot;%s&squot; failed; &quot;
l_string|&quot;&squot;%s&squot; is not a git-command&bslash;n&quot;
comma
id|cmd
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|help_unknown_cmd
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to run command &squot;%s&squot;: %s&bslash;n&quot;
comma
id|cmd
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
