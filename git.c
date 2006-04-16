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
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;common-cmds.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#ifndef PATH_MAX
DECL|macro|PATH_MAX
macro_line|# define PATH_MAX 4096
macro_line|#endif
DECL|variable|git_usage
r_static
r_const
r_char
id|git_usage
(braket
)braket
op_assign
l_string|&quot;Usage: git [--version] [--exec-path[=GIT_EXEC_PATH]] [--help] COMMAND [ ARGS ]&quot;
suffix:semicolon
multiline_comment|/* most gui terms set COLUMNS (although some don&squot;t export it) */
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
op_assign
l_int|0
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
DECL|function|oom
r_static
r_void
id|oom
c_func
(paren
r_void
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: out of memory&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
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
DECL|struct|cmdname
r_static
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
DECL|variable|cmdname
)brace
op_star
op_star
id|cmdname
suffix:semicolon
DECL|variable|cmdname_alloc
DECL|variable|cmdname_cnt
r_static
r_int
id|cmdname_alloc
comma
id|cmdname_cnt
suffix:semicolon
DECL|function|add_cmdname
r_static
r_void
id|add_cmdname
c_func
(paren
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
suffix:semicolon
r_if
c_cond
(paren
id|cmdname_alloc
op_le
id|cmdname_cnt
)paren
(brace
id|cmdname_alloc
op_assign
id|cmdname_alloc
op_plus
l_int|200
suffix:semicolon
id|cmdname
op_assign
id|realloc
c_func
(paren
id|cmdname
comma
id|cmdname_alloc
op_star
r_sizeof
(paren
op_star
id|cmdname
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmdname
)paren
id|oom
c_func
(paren
)paren
suffix:semicolon
)brace
id|ent
op_assign
id|malloc
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
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
id|oom
c_func
(paren
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
id|cmdname
(braket
id|cmdname_cnt
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
DECL|function|pretty_print_string_list
r_static
r_void
id|pretty_print_string_list
c_func
(paren
r_struct
id|cmdname
op_star
op_star
id|cmdname
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
id|cmdname_cnt
op_plus
id|cols
l_int|1
)paren
op_div
id|cols
suffix:semicolon
id|qsort
c_func
(paren
id|cmdname
comma
id|cmdname_cnt
comma
r_sizeof
(paren
op_star
id|cmdname
)paren
comma
id|cmdname_compare
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
id|cmdname_cnt
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
id|cmdname_cnt
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
id|cmdname
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
DECL|function|list_commands
r_static
r_void
id|list_commands
c_func
(paren
r_const
r_char
op_star
id|exec_path
comma
r_const
r_char
op_star
id|pattern
)paren
(brace
r_int
r_int
id|longest
op_assign
l_int|0
suffix:semicolon
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|dirlen
suffix:semicolon
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|exec_path
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
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: &squot;%s&squot;: %s&bslash;n&quot;
comma
id|exec_path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|dirlen
op_assign
id|strlen
c_func
(paren
id|exec_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PATH_MAX
l_int|20
OL
id|dirlen
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: insanely long exec-path &squot;%s&squot;&bslash;n&quot;
comma
id|exec_path
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|path
comma
id|exec_path
comma
id|dirlen
)paren
suffix:semicolon
id|path
(braket
id|dirlen
op_increment
)braket
op_assign
l_char|&squot;/&squot;
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
id|strncmp
c_func
(paren
id|de-&gt;d_name
comma
l_string|&quot;git-&quot;
comma
l_int|4
)paren
)paren
r_continue
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|dirlen
comma
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|path
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
suffix:semicolon
r_if
c_cond
(paren
l_int|4
OL
id|entlen
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|de-&gt;d_name
op_plus
id|entlen
l_int|4
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
id|de-&gt;d_name
op_plus
l_int|4
comma
id|entlen
op_minus
l_int|4
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;git commands available in &squot;%s&squot;&bslash;n&quot;
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
id|cmdname
comma
id|longest
l_int|4
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|list_common_cmds_help
r_static
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
l_string|&quot;    %s&quot;
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
op_plus
l_int|4
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
id|puts
c_func
(paren
l_string|&quot;(use &squot;git help -a&squot; to get a list of all installed git commands)&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef __GNUC__
r_static
r_void
id|cmd_usage
c_func
(paren
r_int
id|show_all
comma
r_const
r_char
op_star
id|exec_path
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|__format__
c_func
(paren
id|__printf__
comma
l_int|3
comma
l_int|4
)paren
comma
id|__noreturn__
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|function|cmd_usage
r_static
r_void
id|cmd_usage
c_func
(paren
r_int
id|show_all
comma
r_const
r_char
op_star
id|exec_path
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_if
c_cond
(paren
id|fmt
)paren
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;git: &quot;
)paren
suffix:semicolon
id|vprintf
c_func
(paren
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_else
id|puts
c_func
(paren
id|git_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exec_path
)paren
(brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_all
)paren
id|list_commands
c_func
(paren
id|exec_path
comma
l_string|&quot;git-*&quot;
)paren
suffix:semicolon
r_else
id|list_common_cmds_help
c_func
(paren
)paren
suffix:semicolon
)brace
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|git_cmd
comma
l_string|&quot;git&quot;
comma
l_int|3
)paren
)paren
id|page
op_assign
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
id|malloc
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
id|page
op_assign
id|p
suffix:semicolon
)brace
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
DECL|function|cmd_version
r_static
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
r_char
op_star
op_star
id|envp
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;git version %s&bslash;n&quot;
comma
id|GIT_VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_help
r_static
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
r_char
op_star
op_star
id|envp
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
op_logical_neg
id|help_cmd
)paren
id|cmd_usage
c_func
(paren
l_int|0
comma
id|git_exec_path
c_func
(paren
)paren
comma
l_int|NULL
)paren
suffix:semicolon
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
id|cmd_usage
c_func
(paren
l_int|1
comma
id|git_exec_path
c_func
(paren
)paren
comma
l_int|NULL
)paren
suffix:semicolon
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
DECL|macro|LOGSIZE
mdefine_line|#define LOGSIZE (65536)
DECL|function|cmd_log_wc
r_static
r_int
id|cmd_log_wc
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
comma
r_struct
id|rev_info
op_star
id|rev
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|LOGSIZE
)paren
suffix:semicolon
r_const
r_char
op_star
id|commit_prefix
op_assign
l_string|&quot;commit &quot;
suffix:semicolon
r_int
id|shown
op_assign
l_int|0
suffix:semicolon
id|rev-&gt;abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
id|rev-&gt;commit_format
op_assign
id|CMIT_FMT_DEFAULT
suffix:semicolon
id|rev-&gt;no_commit_id
op_assign
l_int|1
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
id|rev
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|commit_prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
id|rev
)paren
suffix:semicolon
id|setup_pager
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|shown
op_logical_and
id|rev-&gt;diff
op_logical_and
id|rev-&gt;commit_format
op_ne
id|CMIT_FMT_ONELINE
)paren
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|commit_prefix
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev-&gt;abbrev_commit
op_logical_and
id|rev-&gt;abbrev
)paren
id|fputs
c_func
(paren
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|rev-&gt;abbrev
)paren
comma
id|stdout
)paren
suffix:semicolon
r_else
id|fputs
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev-&gt;parents
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
op_amp
(paren
id|parents-&gt;item-&gt;object
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;flags
op_amp
id|TMP_MARK
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
)paren
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|TMP_MARK
suffix:semicolon
)brace
multiline_comment|/* TMP_MARK is a general purpose flag that can&n;&t;&t;&t; * be used locally, but the user should clean&n;&t;&t;&t; * things up after it is done with them.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
id|parents-&gt;item-&gt;object.flags
op_and_assign
op_complement
id|TMP_MARK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rev-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pretty_print_commit
c_func
(paren
id|rev-&gt;commit_format
comma
id|commit
comma
op_complement
l_int|0
comma
id|buf
comma
id|LOGSIZE
comma
id|rev-&gt;abbrev
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev-&gt;diff
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;---&bslash;n&quot;
)paren
suffix:semicolon
id|log_tree_commit
c_func
(paren
id|rev
comma
id|commit
)paren
suffix:semicolon
)brace
id|shown
op_assign
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|commit-&gt;buffer
)paren
suffix:semicolon
id|commit-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_wc
r_static
r_int
id|cmd_wc
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
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
id|rev.diff
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.recursive
op_assign
l_int|1
suffix:semicolon
r_return
id|cmd_log_wc
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
op_amp
id|rev
)paren
suffix:semicolon
)brace
DECL|function|cmd_show
r_static
r_int
id|cmd_show
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
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
id|rev.diff
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.recursive
op_assign
l_int|1
suffix:semicolon
id|rev.combine_merges
op_assign
l_int|1
suffix:semicolon
id|rev.dense_combined_merges
op_assign
l_int|1
suffix:semicolon
id|rev.ignore_merges
op_assign
l_int|0
suffix:semicolon
id|rev.no_walk
op_assign
l_int|1
suffix:semicolon
r_return
id|cmd_log_wc
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
op_amp
id|rev
)paren
suffix:semicolon
)brace
DECL|function|cmd_log
r_static
r_int
id|cmd_log
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
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
r_return
id|cmd_log_wc
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
op_amp
id|rev
)paren
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
id|cmd_wc
)brace
comma
(brace
l_string|&quot;show&quot;
comma
id|cmd_show
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
