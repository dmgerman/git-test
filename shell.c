macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;run-command.h&quot;
DECL|macro|COMMAND_DIR
mdefine_line|#define COMMAND_DIR &quot;git-shell-commands&quot;
DECL|macro|HELP_COMMAND
mdefine_line|#define HELP_COMMAND COMMAND_DIR &quot;/help&quot;
DECL|macro|NOLOGIN_COMMAND
mdefine_line|#define NOLOGIN_COMMAND COMMAND_DIR &quot;/no-interactive-login&quot;
DECL|function|do_generic_cmd
r_static
r_int
id|do_generic_cmd
c_func
(paren
r_const
r_char
op_star
id|me
comma
r_char
op_star
id|arg
)paren
(brace
r_const
r_char
op_star
id|my_argv
(braket
l_int|4
)braket
suffix:semicolon
id|setup_path
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
op_logical_or
op_logical_neg
(paren
id|arg
op_assign
id|sq_dequote
c_func
(paren
id|arg
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;bad argument&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|me
comma
l_string|&quot;git-&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;bad command&quot;
)paren
suffix:semicolon
id|my_argv
(braket
l_int|0
)braket
op_assign
id|me
op_plus
l_int|4
suffix:semicolon
id|my_argv
(braket
l_int|1
)braket
op_assign
id|arg
suffix:semicolon
id|my_argv
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|execv_git_cmd
c_func
(paren
id|my_argv
)paren
suffix:semicolon
)brace
DECL|function|do_cvs_cmd
r_static
r_int
id|do_cvs_cmd
c_func
(paren
r_const
r_char
op_star
id|me
comma
r_char
op_star
id|arg
)paren
(brace
r_const
r_char
op_star
id|cvsserver_argv
(braket
l_int|3
)braket
op_assign
(brace
l_string|&quot;cvsserver&quot;
comma
l_string|&quot;server&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
op_logical_or
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;server&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-cvsserver only handles server: %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|setup_path
c_func
(paren
)paren
suffix:semicolon
r_return
id|execv_git_cmd
c_func
(paren
id|cvsserver_argv
)paren
suffix:semicolon
)brace
DECL|function|is_valid_cmd_name
r_static
r_int
id|is_valid_cmd_name
c_func
(paren
r_const
r_char
op_star
id|cmd
)paren
(brace
multiline_comment|/* Test command contains no . or / characters */
r_return
id|cmd
(braket
id|strcspn
c_func
(paren
id|cmd
comma
l_string|&quot;./&quot;
)paren
)braket
op_eq
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|make_cmd
r_static
r_char
op_star
id|make_cmd
c_func
(paren
r_const
r_char
op_star
id|prog
)paren
(brace
r_char
op_star
id|prefix
op_assign
id|xmalloc
c_func
(paren
(paren
id|strlen
c_func
(paren
id|prog
)paren
op_plus
id|strlen
c_func
(paren
id|COMMAND_DIR
)paren
op_plus
l_int|2
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|prefix
comma
id|COMMAND_DIR
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|prefix
comma
l_string|&quot;/&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|prefix
comma
id|prog
)paren
suffix:semicolon
r_return
id|prefix
suffix:semicolon
)brace
DECL|function|cd_to_homedir
r_static
r_void
id|cd_to_homedir
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|home
op_assign
id|getenv
c_func
(paren
l_string|&quot;HOME&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|home
)paren
id|die
c_func
(paren
l_string|&quot;could not determine user&squot;s home directory; HOME is unset&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|home
)paren
op_eq
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;could not chdir to user&squot;s home directory&quot;
)paren
suffix:semicolon
)brace
DECL|function|run_shell
r_static
r_void
id|run_shell
c_func
(paren
r_void
)paren
(brace
r_int
id|done
op_assign
l_int|0
suffix:semicolon
r_static
r_const
r_char
op_star
id|help_argv
(braket
)braket
op_assign
(brace
id|HELP_COMMAND
comma
l_int|NULL
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|NOLOGIN_COMMAND
comma
id|F_OK
)paren
)paren
(brace
multiline_comment|/* Interactive login disabled. */
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
id|NOLOGIN_COMMAND
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|run_command_v_opt
c_func
(paren
id|argv
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
m_exit
(paren
l_int|127
)paren
suffix:semicolon
m_exit
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Print help if enabled */
id|run_command_v_opt
c_func
(paren
id|help_argv
comma
id|RUN_SILENT_EXEC_FAILURE
)paren
suffix:semicolon
r_do
(brace
r_struct
id|strbuf
id|line
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|prog
suffix:semicolon
r_char
op_star
id|full_cmd
suffix:semicolon
r_char
op_star
id|rawargs
suffix:semicolon
r_char
op_star
id|split_args
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
r_int
id|code
suffix:semicolon
r_int
id|count
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git&gt; &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|line
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|strbuf_trim
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
id|rawargs
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|line
comma
l_int|NULL
)paren
suffix:semicolon
id|split_args
op_assign
id|xstrdup
c_func
(paren
id|rawargs
)paren
suffix:semicolon
id|count
op_assign
id|split_cmdline
c_func
(paren
id|split_args
comma
op_amp
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;invalid command format &squot;%s&squot;: %s&bslash;n&quot;
comma
id|rawargs
comma
id|split_cmdline_strerror
c_func
(paren
id|count
)paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|split_args
)paren
suffix:semicolon
id|free
c_func
(paren
id|rawargs
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|prog
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|prog
comma
l_string|&quot;&quot;
)paren
)paren
(brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|prog
comma
l_string|&quot;quit&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|prog
comma
l_string|&quot;logout&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|prog
comma
l_string|&quot;exit&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|prog
comma
l_string|&quot;bye&quot;
)paren
)paren
(brace
id|done
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_valid_cmd_name
c_func
(paren
id|prog
)paren
)paren
(brace
id|full_cmd
op_assign
id|make_cmd
c_func
(paren
id|prog
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|full_cmd
suffix:semicolon
id|code
op_assign
id|run_command_v_opt
c_func
(paren
id|argv
comma
id|RUN_SILENT_EXEC_FAILURE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
op_eq
l_int|1
op_logical_and
id|errno
op_eq
id|ENOENT
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;unrecognized command &squot;%s&squot;&bslash;n&quot;
comma
id|prog
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|full_cmd
)paren
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;invalid command format &squot;%s&squot;&bslash;n&quot;
comma
id|prog
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|argv
)paren
suffix:semicolon
id|free
c_func
(paren
id|rawargs
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|done
)paren
suffix:semicolon
)brace
DECL|struct|commands
r_static
r_struct
id|commands
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|exec
r_int
(paren
op_star
id|exec
)paren
(paren
r_const
r_char
op_star
id|me
comma
r_char
op_star
id|arg
)paren
suffix:semicolon
DECL|variable|cmd_list
)brace
id|cmd_list
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;git-receive-pack&quot;
comma
id|do_generic_cmd
)brace
comma
(brace
l_string|&quot;git-upload-pack&quot;
comma
id|do_generic_cmd
)brace
comma
(brace
l_string|&quot;git-upload-archive&quot;
comma
id|do_generic_cmd
)brace
comma
(brace
l_string|&quot;cvs&quot;
comma
id|do_cvs_cmd
)brace
comma
(brace
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
op_star
id|prog
suffix:semicolon
r_const
r_char
op_star
op_star
id|user_argv
suffix:semicolon
r_struct
id|commands
op_star
id|cmd
suffix:semicolon
r_int
id|devnull_fd
suffix:semicolon
r_int
id|count
suffix:semicolon
id|git_setup_gettext
c_func
(paren
)paren
suffix:semicolon
id|git_extract_argv0_path
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Always open file descriptors 0/1/2 to avoid clobbering files&n;&t; * in die().  It also avoids not messing up when the pipes are&n;&t; * dup&squot;ed onto stdin/stdout/stderr in the child processes we spawn.&n;&t; */
id|devnull_fd
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
id|O_RDWR
)paren
suffix:semicolon
r_while
c_loop
(paren
id|devnull_fd
op_ge
l_int|0
op_logical_and
id|devnull_fd
op_le
l_int|2
)paren
id|devnull_fd
op_assign
id|dup
c_func
(paren
id|devnull_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devnull_fd
op_eq
l_int|1
)paren
id|die_errno
c_func
(paren
l_string|&quot;opening /dev/null failed&quot;
)paren
suffix:semicolon
id|close
(paren
id|devnull_fd
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Special hack to pretend to be a CVS server&n;&t; */
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
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
l_string|&quot;cvs server&quot;
)paren
)paren
(brace
id|argv
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Allow the user to run an interactive shell */
id|cd_to_homedir
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|COMMAND_DIR
comma
id|R_OK
op_or
id|X_OK
)paren
op_eq
l_int|1
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Interactive git shell is not enabled.&bslash;n&quot;
l_string|&quot;hint: ~/&quot;
id|COMMAND_DIR
l_string|&quot; should exist &quot;
l_string|&quot;and have read and execute access.&quot;
)paren
suffix:semicolon
)brace
id|run_shell
c_func
(paren
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
op_logical_or
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-c&quot;
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We do not accept any other modes except &quot;-c&quot; followed by&n;&t;&t; * &quot;cmd arg&quot;, where &quot;cmd&quot; is a very limited subset of git&n;&t;&t; * commands or a command in the COMMAND_DIR&n;&t;&t; */
id|die
c_func
(paren
l_string|&quot;Run with no arguments or with -c cmd&quot;
)paren
suffix:semicolon
)brace
id|prog
op_assign
id|xstrdup
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|prog
comma
l_string|&quot;git&quot;
comma
l_int|3
)paren
op_logical_and
id|isspace
c_func
(paren
id|prog
(braket
l_int|3
)braket
)paren
)paren
multiline_comment|/* Accept &quot;git foo&quot; as if the caller said &quot;git-foo&quot;. */
id|prog
(braket
l_int|3
)braket
op_assign
l_char|&squot;-&squot;
suffix:semicolon
r_for
c_loop
(paren
id|cmd
op_assign
id|cmd_list
suffix:semicolon
id|cmd-&gt;name
suffix:semicolon
id|cmd
op_increment
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|cmd-&gt;name
)paren
suffix:semicolon
r_char
op_star
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cmd-&gt;name
comma
id|prog
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
id|arg
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|prog
(braket
id|len
)braket
)paren
(brace
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
id|arg
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
id|arg
op_assign
id|prog
op_plus
id|len
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
m_exit
(paren
id|cmd
op_member_access_from_pointer
id|exec
c_func
(paren
id|cmd-&gt;name
comma
id|arg
)paren
)paren
suffix:semicolon
)brace
id|cd_to_homedir
c_func
(paren
)paren
suffix:semicolon
id|count
op_assign
id|split_cmdline
c_func
(paren
id|prog
comma
op_amp
id|user_argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|is_valid_cmd_name
c_func
(paren
id|user_argv
(braket
l_int|0
)braket
)paren
)paren
(brace
id|prog
op_assign
id|make_cmd
c_func
(paren
id|user_argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|user_argv
(braket
l_int|0
)braket
op_assign
id|prog
suffix:semicolon
id|execv
c_func
(paren
id|user_argv
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
id|user_argv
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|prog
)paren
suffix:semicolon
id|free
c_func
(paren
id|user_argv
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unrecognized command &squot;%s&squot;&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|free
c_func
(paren
id|prog
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid command format &squot;%s&squot;: %s&quot;
comma
id|argv
(braket
l_int|2
)braket
comma
id|split_cmdline_strerror
c_func
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
)brace
eof
