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
l_string|&quot;git [--version] [--exec-path[=GIT_EXEC_PATH]] [-p|--paginate|--no-pager] [--bare] [--git-dir=GIT_DIR] [--work-tree=GIT_WORK_TREE] [--help] COMMAND [ARGS]&quot;
suffix:semicolon
DECL|variable|git_more_info_string
r_const
r_char
id|git_more_info_string
(braket
)braket
op_assign
l_string|&quot;See &squot;git help COMMAND&squot; for more information on a specific command.&quot;
suffix:semicolon
DECL|variable|use_pager
r_static
r_int
id|use_pager
op_assign
l_int|1
suffix:semicolon
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
DECL|member|val
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
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
id|c-&gt;val
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
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
id|c.val
op_assign
l_int|1
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
r_return
id|c.val
suffix:semicolon
)brace
DECL|function|commit_pager_choice
r_static
r_void
id|commit_pager_choice
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|use_pager
)paren
(brace
r_case
l_int|0
suffix:colon
id|setenv
c_func
(paren
l_string|&quot;GIT_PAGER&quot;
comma
l_string|&quot;cat&quot;
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|setup_pager
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
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
id|git_set_argv_exec_path
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
id|use_pager
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
l_string|&quot;--no-pager&quot;
)paren
)paren
(brace
id|use_pager
op_assign
l_int|0
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
id|is_bare_repository_cfg
op_assign
l_int|1
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
l_int|0
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
r_const
r_char
op_star
id|alias_command
suffix:semicolon
r_char
op_star
id|alias_string
suffix:semicolon
r_int
id|unused_nongit
suffix:semicolon
id|subdir
op_assign
id|setup_git_directory_gently
c_func
(paren
op_amp
id|unused_nongit
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
id|alias_string
op_assign
id|alias_lookup
c_func
(paren
id|alias_command
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
r_if
c_cond
(paren
op_star
id|argcp
OG
l_int|1
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
id|PATH_MAX
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|alias_string
)paren
suffix:semicolon
id|sq_quote_argv
c_func
(paren
op_amp
id|buf
comma
(paren
op_star
id|argv
)paren
op_plus
l_int|1
comma
id|PATH_MAX
)paren
suffix:semicolon
id|free
c_func
(paren
id|alias_string
)paren
suffix:semicolon
id|alias_string
op_assign
id|buf.buf
suffix:semicolon
)brace
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
id|use_pager
op_eq
l_int|1
op_logical_and
id|p-&gt;option
op_amp
id|RUN_SETUP
)paren
id|use_pager
op_assign
id|check_pager_config
c_func
(paren
id|p-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_pager
op_eq
l_int|1
op_logical_and
id|p-&gt;option
op_amp
id|USE_PAGER
)paren
id|use_pager
op_assign
l_int|1
suffix:semicolon
id|commit_pager_choice
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;option
op_amp
id|NEED_WORK_TREE
)paren
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
id|trace_argv_printf
c_func
(paren
id|argv
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
op_amp
l_int|0xff
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
l_string|&quot;checkout&quot;
comma
id|cmd_checkout
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;checkout-index&quot;
comma
id|cmd_checkout_index
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
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
l_string|&quot;clone&quot;
comma
id|cmd_clone
)brace
comma
(brace
l_string|&quot;clean&quot;
comma
id|cmd_clean
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;commit&quot;
comma
id|cmd_commit
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
)brace
comma
(brace
l_string|&quot;diff-files&quot;
comma
id|cmd_diff_files
comma
id|RUN_SETUP
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
l_string|&quot;fast-export&quot;
comma
id|cmd_fast_export
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;fetch&quot;
comma
id|cmd_fetch
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;fetch-pack&quot;
comma
id|cmd_fetch_pack
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
macro_line|#ifndef NO_CURL
(brace
l_string|&quot;http-fetch&quot;
comma
id|cmd_http_fetch
comma
id|RUN_SETUP
)brace
comma
macro_line|#endif
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
l_string|&quot;ls-remote&quot;
comma
id|cmd_ls_remote
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
l_string|&quot;merge&quot;
comma
id|cmd_merge
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
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
l_string|&quot;merge-ours&quot;
comma
id|cmd_merge_ours
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;merge-recursive&quot;
comma
id|cmd_merge_recursive
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
)brace
comma
(brace
l_string|&quot;merge-subtree&quot;
comma
id|cmd_merge_recursive
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
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
l_string|&quot;peek-remote&quot;
comma
id|cmd_ls_remote
)brace
comma
(brace
l_string|&quot;pickaxe&quot;
comma
id|cmd_blame
comma
id|RUN_SETUP
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
l_string|&quot;remote&quot;
comma
id|cmd_remote
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
l_string|&quot;reset&quot;
comma
id|cmd_reset
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
)brace
comma
(brace
l_string|&quot;send-pack&quot;
comma
id|cmd_send_pack
comma
id|RUN_SETUP
)brace
comma
(brace
l_string|&quot;shortlog&quot;
comma
id|cmd_shortlog
comma
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
l_string|&quot;status&quot;
comma
id|cmd_status
comma
id|RUN_SETUP
op_or
id|NEED_WORK_TREE
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
l_string|&quot;tag&quot;
comma
id|cmd_tag
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
l_string|&quot;verify-tag&quot;
comma
id|cmd_verify_tag
comma
id|RUN_SETUP
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
r_static
r_const
r_char
id|ext
(braket
)braket
op_assign
id|STRIP_EXTENSION
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|ext
)paren
OG
l_int|1
)paren
(brace
id|i
op_assign
id|strlen
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
id|strlen
c_func
(paren
id|ext
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
op_plus
id|i
comma
id|ext
)paren
)paren
(brace
r_char
op_star
id|argv0
op_assign
id|strdup
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|cmd
op_assign
id|argv0
suffix:semicolon
id|argv0
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
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
DECL|function|execv_dashed_external
r_static
r_void
id|execv_dashed_external
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|strbuf
id|cmd
suffix:semicolon
r_const
r_char
op_star
id|tmp
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|cmd
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot;git-%s&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * argv[0] must be the git command, but the argv array&n;&t; * belongs to the caller, and may be reused in&n;&t; * subsequent loop iterations. Save argv[0] and&n;&t; * restore it on error.&n;&t; */
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
id|cmd.buf
suffix:semicolon
id|trace_argv_printf
c_func
(paren
id|argv
comma
l_string|&quot;trace: exec:&quot;
)paren
suffix:semicolon
multiline_comment|/* execvp() can only ever return if it fails */
id|execvp
c_func
(paren
id|cmd.buf
comma
(paren
r_char
op_star
op_star
)paren
id|argv
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
id|argv
(braket
l_int|0
)braket
op_assign
id|tmp
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
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
op_logical_and
op_star
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
(paren
r_char
op_star
)paren
id|cmd
op_plus
id|strlen
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_const
r_char
op_star
id|cmd_path
op_assign
l_int|NULL
suffix:semicolon
r_int
id|done_alias
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Take the basename of argv[0] as the command&n;&t; * name, and the dirname as the default exec_path&n;&t; * if we don&squot;t have anything better.&n;&t; */
r_do
op_decrement
id|slash
suffix:semicolon
r_while
c_loop
(paren
id|cmd
op_le
id|slash
op_logical_and
op_logical_neg
id|is_dir_sep
c_func
(paren
op_star
id|slash
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_le
id|slash
)paren
(brace
op_star
id|slash
op_increment
op_assign
l_int|0
suffix:semicolon
id|cmd_path
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
id|commit_pager_choice
c_func
(paren
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
multiline_comment|/* The user didn&squot;t specify a command; give them help */
id|printf
c_func
(paren
l_string|&quot;usage: %s&bslash;n&bslash;n&quot;
comma
id|git_usage_string
)paren
suffix:semicolon
id|list_common_cmds_help
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|git_more_info_string
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|cmd
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * We use PATH to find git commands, but we prepend some higher&n;&t; * precidence paths: the &quot;--exec-path&quot; option, the GIT_EXEC_PATH&n;&t; * environment, and the $(gitexecdir) from the Makefile at build&n;&t; * time.&n;&t; */
id|setup_path
c_func
(paren
id|cmd_path
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
id|execv_dashed_external
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
