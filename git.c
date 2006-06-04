macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;builtin.h&quot;
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
r_char
op_star
id|path
comma
op_star
id|old_path
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
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
id|malloc
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
comma
r_char
op_star
op_star
id|envp
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
(brace
r_const
r_char
op_star
id|cmd
suffix:semicolon
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
r_char
op_star
op_star
)paren
suffix:semicolon
)brace
id|commands
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;version&quot;
comma
id|cmd_version
)brace
comma
(brace
l_string|&quot;help&quot;
comma
id|cmd_help
)brace
comma
(brace
l_string|&quot;log&quot;
comma
id|cmd_log
)brace
comma
(brace
l_string|&quot;whatchanged&quot;
comma
id|cmd_whatchanged
)brace
comma
(brace
l_string|&quot;show&quot;
comma
id|cmd_show
)brace
comma
(brace
l_string|&quot;push&quot;
comma
id|cmd_push
)brace
comma
(brace
l_string|&quot;format-patch&quot;
comma
id|cmd_format_patch
)brace
comma
(brace
l_string|&quot;count-objects&quot;
comma
id|cmd_count_objects
)brace
comma
(brace
l_string|&quot;diff&quot;
comma
id|cmd_diff
)brace
comma
(brace
l_string|&quot;grep&quot;
comma
id|cmd_grep
)brace
comma
(brace
l_string|&quot;rm&quot;
comma
id|cmd_rm
)brace
comma
(brace
l_string|&quot;add&quot;
comma
id|cmd_add
)brace
comma
(brace
l_string|&quot;rev-list&quot;
comma
id|cmd_rev_list
)brace
comma
(brace
l_string|&quot;init-db&quot;
comma
id|cmd_init_db
)brace
comma
(brace
l_string|&quot;tar-tree&quot;
comma
id|cmd_tar_tree
)brace
comma
(brace
l_string|&quot;upload-tar&quot;
comma
id|cmd_upload_tar
)brace
comma
(brace
l_string|&quot;check-ref-format&quot;
comma
id|cmd_check_ref_format
)brace
comma
(brace
l_string|&quot;ls-files&quot;
comma
id|cmd_ls_files
)brace
comma
(brace
l_string|&quot;ls-tree&quot;
comma
id|cmd_ls_tree
)brace
comma
(brace
l_string|&quot;tar-tree&quot;
comma
id|cmd_tar_tree
)brace
comma
(brace
l_string|&quot;read-tree&quot;
comma
id|cmd_read_tree
)brace
comma
(brace
l_string|&quot;commit-tree&quot;
comma
id|cmd_commit_tree
)brace
comma
(brace
l_string|&quot;apply&quot;
comma
id|cmd_apply
)brace
comma
(brace
l_string|&quot;show-branch&quot;
comma
id|cmd_show_branch
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
)brace
comma
(brace
l_string|&quot;diff-stages&quot;
comma
id|cmd_diff_stages
)brace
comma
(brace
l_string|&quot;diff-tree&quot;
comma
id|cmd_diff_tree
)brace
comma
(brace
l_string|&quot;cat-file&quot;
comma
id|cmd_cat_file
)brace
comma
(brace
l_string|&quot;rev-parse&quot;
comma
id|cmd_rev_parse
)brace
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
id|p
op_member_access_from_pointer
id|fn
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
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
comma
r_char
op_star
op_star
id|envp
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
r_char
id|git_command
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_const
r_char
op_star
id|exec_path
op_assign
l_int|NULL
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
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;git-&quot;
comma
l_int|4
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
comma
id|envp
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
multiline_comment|/* Default command: &quot;help&quot; */
id|cmd
op_assign
l_string|&quot;help&quot;
suffix:semicolon
multiline_comment|/* Look for flags.. */
r_while
c_loop
(paren
id|argc
OG
l_int|1
)paren
(brace
id|cmd
op_assign
op_star
op_increment
id|argv
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;--&quot;
comma
l_int|2
)paren
)paren
r_break
suffix:semicolon
id|cmd
op_add_assign
l_int|2
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
l_string|&quot;help&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;version&quot;
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Check remaining flags (which by now must be&n;&t;&t; * &quot;--exec-path&quot;, but maybe we will accept&n;&t;&t; * other arguments some day)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|cmd
comma
l_string|&quot;exec-path&quot;
comma
l_int|9
)paren
)paren
(brace
id|cmd
op_add_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
l_char|&squot;=&squot;
)paren
(brace
id|git_set_exec_path
c_func
(paren
id|cmd
op_plus
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
id|cmd_usage
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|argv
(braket
l_int|0
)braket
op_assign
id|cmd
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
multiline_comment|/* See if it&squot;s an internal command */
id|handle_internal_command
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
multiline_comment|/* .. then try the external ones */
id|execv_git_cmd
c_func
(paren
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
id|cmd_usage
c_func
(paren
l_int|0
comma
id|exec_path
comma
l_string|&quot;&squot;%s&squot; is not a git-command&quot;
comma
id|cmd
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to run command &squot;%s&squot;: %s&bslash;n&quot;
comma
id|git_command
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
