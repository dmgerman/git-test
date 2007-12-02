multiline_comment|/*&n; * builtin-help.c&n; *&n; * Builtin help-related commands (help, usage, version)&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;common-cmds.h&quot;
multiline_comment|/* most GUI terminals set COLUMNS (although some don&squot;t export it) */
DECL|function|term_columns
r_static
r_int
id|term_columns
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|col_string
op_assign
id|getenv
c_func
(paren
l_string|&quot;COLUMNS&quot;
)paren
suffix:semicolon
r_int
id|n_cols
suffix:semicolon
r_if
c_cond
(paren
id|col_string
op_logical_and
(paren
id|n_cols
op_assign
id|atoi
c_func
(paren
id|col_string
)paren
)paren
OG
l_int|0
)paren
r_return
id|n_cols
suffix:semicolon
macro_line|#ifdef TIOCGWINSZ
(brace
r_struct
id|winsize
id|ws
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioctl
c_func
(paren
l_int|1
comma
id|TIOCGWINSZ
comma
op_amp
id|ws
)paren
)paren
(brace
r_if
c_cond
(paren
id|ws.ws_col
)paren
r_return
id|ws.ws_col
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|80
suffix:semicolon
)brace
DECL|function|mput_char
r_static
r_inline
r_void
id|mput_char
c_func
(paren
r_char
id|c
comma
r_int
r_int
id|num
)paren
(brace
r_while
c_loop
(paren
id|num
op_decrement
)paren
(brace
id|putchar
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
DECL|struct|cmdnames
r_static
r_struct
id|cmdnames
(brace
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|cnt
r_int
id|cnt
suffix:semicolon
DECL|struct|cmdname
r_struct
id|cmdname
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|names
)brace
op_star
op_star
id|names
suffix:semicolon
DECL|variable|main_cmds
DECL|variable|other_cmds
)brace
id|main_cmds
comma
id|other_cmds
suffix:semicolon
DECL|function|add_cmdname
r_static
r_void
id|add_cmdname
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_struct
id|cmdname
op_star
id|ent
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ent
)paren
op_plus
id|len
)paren
suffix:semicolon
id|ent-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|ent-&gt;name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|cmds-&gt;names
comma
id|cmds-&gt;cnt
op_plus
l_int|1
comma
id|cmds-&gt;alloc
)paren
suffix:semicolon
id|cmds-&gt;names
(braket
id|cmds-&gt;cnt
op_increment
)braket
op_assign
id|ent
suffix:semicolon
)brace
DECL|function|cmdname_compare
r_static
r_int
id|cmdname_compare
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|cmdname
op_star
id|a
op_assign
op_star
(paren
r_struct
id|cmdname
op_star
op_star
)paren
id|a_
suffix:semicolon
r_struct
id|cmdname
op_star
id|b
op_assign
op_star
(paren
r_struct
id|cmdname
op_star
op_star
)paren
id|b_
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|uniq
r_static
r_void
id|uniq
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmds-&gt;cnt
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|cmds-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cmds-&gt;names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|cmds-&gt;names
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|name
)paren
)paren
id|cmds-&gt;names
(braket
id|j
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|i
)braket
suffix:semicolon
id|cmds-&gt;cnt
op_assign
id|j
suffix:semicolon
)brace
DECL|function|exclude_cmds
r_static
r_void
id|exclude_cmds
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_struct
id|cmdnames
op_star
id|excludes
)paren
(brace
r_int
id|ci
comma
id|cj
comma
id|ei
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|ci
op_assign
id|cj
op_assign
id|ei
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ci
OL
id|cmds-&gt;cnt
op_logical_and
id|ei
OL
id|excludes-&gt;cnt
)paren
(brace
id|cmp
op_assign
id|strcmp
c_func
(paren
id|cmds-&gt;names
(braket
id|ci
)braket
op_member_access_from_pointer
id|name
comma
id|excludes-&gt;names
(braket
id|ei
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
id|cmds-&gt;names
(braket
id|cj
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmp
op_eq
l_int|0
)paren
id|ci
op_increment
comma
id|ei
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
id|ei
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ci
OL
id|cmds-&gt;cnt
)paren
id|cmds-&gt;names
(braket
id|cj
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
suffix:semicolon
id|cmds-&gt;cnt
op_assign
id|cj
suffix:semicolon
)brace
DECL|function|pretty_print_string_list
r_static
r_void
id|pretty_print_string_list
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_int
id|longest
)paren
(brace
r_int
id|cols
op_assign
l_int|1
comma
id|rows
suffix:semicolon
r_int
id|space
op_assign
id|longest
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* min 1 SP between words */
r_int
id|max_cols
op_assign
id|term_columns
c_func
(paren
)paren
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t print *on* the edge */
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|space
OL
id|max_cols
)paren
id|cols
op_assign
id|max_cols
op_div
id|space
suffix:semicolon
id|rows
op_assign
(paren
id|cmds-&gt;cnt
op_plus
id|cols
l_int|1
)paren
op_div
id|cols
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
id|rows
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;  &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cols
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|n
op_assign
id|j
op_star
id|rows
op_plus
id|i
suffix:semicolon
r_int
id|size
op_assign
id|space
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|cmds-&gt;cnt
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|cols
op_minus
l_int|1
op_logical_or
id|n
op_plus
id|rows
op_ge
id|cmds-&gt;cnt
)paren
id|size
op_assign
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%-*s&quot;
comma
id|size
comma
id|cmds-&gt;names
(braket
id|n
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|list_commands_in_dir
r_static
r_int
r_int
id|list_commands_in_dir
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
r_int
id|longest
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
l_string|&quot;git-&quot;
suffix:semicolon
r_int
id|prefix_len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
id|chdir
c_func
(paren
id|path
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|entlen
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|de-&gt;d_name
comma
id|prefix
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|de-&gt;d_name
comma
op_amp
id|st
)paren
op_logical_or
multiline_comment|/* stat, not lstat */
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
op_logical_or
op_logical_neg
(paren
id|st.st_mode
op_amp
id|S_IXUSR
)paren
)paren
r_continue
suffix:semicolon
id|entlen
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
id|prefix_len
suffix:semicolon
r_if
c_cond
(paren
id|has_extension
c_func
(paren
id|de-&gt;d_name
comma
l_string|&quot;.exe&quot;
)paren
)paren
id|entlen
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|longest
OL
id|entlen
)paren
id|longest
op_assign
id|entlen
suffix:semicolon
id|add_cmdname
c_func
(paren
id|cmds
comma
id|de-&gt;d_name
op_plus
id|prefix_len
comma
id|entlen
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|longest
suffix:semicolon
)brace
DECL|function|list_commands
r_static
r_void
id|list_commands
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|longest
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|env_path
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
suffix:semicolon
r_char
op_star
id|paths
comma
op_star
id|path
comma
op_star
id|colon
suffix:semicolon
r_const
r_char
op_star
id|exec_path
op_assign
id|git_exec_path
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exec_path
)paren
id|longest
op_assign
id|list_commands_in_dir
c_func
(paren
op_amp
id|main_cmds
comma
id|exec_path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|env_path
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;PATH not set&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|path
op_assign
id|paths
op_assign
id|xstrdup
c_func
(paren
id|env_path
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|colon
op_assign
id|strchr
c_func
(paren
id|path
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
op_star
id|colon
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|list_commands_in_dir
c_func
(paren
op_amp
id|other_cmds
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|longest
)paren
id|longest
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|colon
)paren
r_break
suffix:semicolon
id|path
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
)brace
id|free
c_func
(paren
id|paths
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|main_cmds.names
comma
id|main_cmds.cnt
comma
r_sizeof
(paren
op_star
id|main_cmds.names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
op_amp
id|main_cmds
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|other_cmds.names
comma
id|other_cmds.cnt
comma
r_sizeof
(paren
op_star
id|other_cmds.names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
op_amp
id|other_cmds
)paren
suffix:semicolon
id|exclude_cmds
c_func
(paren
op_amp
id|other_cmds
comma
op_amp
id|main_cmds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|main_cmds.cnt
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;available git commands in &squot;%s&squot;&bslash;n&quot;
comma
id|exec_path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;----------------------------&quot;
)paren
suffix:semicolon
id|mput_char
c_func
(paren
l_char|&squot;-&squot;
comma
id|strlen
c_func
(paren
id|exec_path
)paren
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pretty_print_string_list
c_func
(paren
op_amp
id|main_cmds
comma
id|longest
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|other_cmds.cnt
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;git commands available from elsewhere on your $PATH&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;---------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
id|pretty_print_string_list
c_func
(paren
op_amp
id|other_cmds
comma
id|longest
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|list_common_cmds_help
r_void
id|list_common_cmds_help
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|longest
op_assign
l_int|0
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
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|longest
OL
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
)paren
id|longest
op_assign
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
l_string|&quot;The most commonly used git commands are:&quot;
)paren
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
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;   %s   &quot;
comma
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|mput_char
c_func
(paren
l_char|&squot; &squot;
comma
id|longest
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|help
)paren
suffix:semicolon
)brace
)brace
DECL|function|cmd_to_page
r_static
r_const
r_char
op_star
id|cmd_to_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_cmd
)paren
r_return
l_string|&quot;git&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|git_cmd
comma
l_string|&quot;git&quot;
)paren
)paren
r_return
id|git_cmd
suffix:semicolon
r_else
(brace
r_int
id|page_len
op_assign
id|strlen
c_func
(paren
id|git_cmd
)paren
op_plus
l_int|4
suffix:semicolon
r_char
op_star
id|p
op_assign
id|xmalloc
c_func
(paren
id|page_len
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
comma
l_string|&quot;git-&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
op_plus
l_int|4
comma
id|git_cmd
)paren
suffix:semicolon
id|p
(braket
id|page_len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
)brace
DECL|function|show_man_page
r_static
r_void
id|show_man_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_const
r_char
op_star
id|page
op_assign
id|cmd_to_page
c_func
(paren
id|git_cmd
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;man&quot;
comma
l_string|&quot;man&quot;
comma
id|page
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|show_info_page
r_static
r_void
id|show_info_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_const
r_char
op_star
id|page
op_assign
id|cmd_to_page
c_func
(paren
id|git_cmd
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;info&quot;
comma
l_string|&quot;info&quot;
comma
id|page
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|show_html_page
r_static
r_void
id|show_html_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_const
r_char
op_star
id|page
op_assign
id|cmd_to_page
c_func
(paren
id|git_cmd
)paren
suffix:semicolon
id|execl_git_cmd
c_func
(paren
l_string|&quot;browse-help&quot;
comma
id|page
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|help_unknown_cmd
r_void
id|help_unknown_cmd
c_func
(paren
r_const
r_char
op_star
id|cmd
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: &squot;%s&squot; is not a git-command. See &squot;git --help&squot;.&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cmd_version
r_int
id|cmd_version
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
r_const
r_char
op_star
id|prefix
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;git version %s&bslash;n&quot;
comma
id|git_version_string
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_help
r_int
id|cmd_help
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
r_const
r_char
op_star
id|prefix
)paren
(brace
r_const
r_char
op_star
id|help_cmd
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
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
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|help_cmd
comma
l_string|&quot;--all&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|help_cmd
comma
l_string|&quot;-a&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;usage: %s&bslash;n&bslash;n&quot;
comma
id|git_usage_string
)paren
suffix:semicolon
id|list_commands
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
id|help_cmd
comma
l_string|&quot;--web&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|help_cmd
comma
l_string|&quot;-w&quot;
)paren
)paren
(brace
id|show_html_page
c_func
(paren
id|argc
OG
l_int|2
ques
c_cond
id|argv
(braket
l_int|2
)braket
suffix:colon
l_int|NULL
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
id|help_cmd
comma
l_string|&quot;--info&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|help_cmd
comma
l_string|&quot;-i&quot;
)paren
)paren
(brace
id|show_info_page
c_func
(paren
id|argc
OG
l_int|2
ques
c_cond
id|argv
(braket
l_int|2
)braket
suffix:colon
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|show_man_page
c_func
(paren
id|help_cmd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
