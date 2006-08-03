multiline_comment|/*&n; * &quot;git push&quot;&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|macro|MAX_URI
mdefine_line|#define MAX_URI (16)
DECL|variable|push_usage
r_static
r_const
r_char
id|push_usage
(braket
)braket
op_assign
l_string|&quot;git-push [--all] [--tags] [-f | --force] &lt;repository&gt; [&lt;refspec&gt;...]&quot;
suffix:semicolon
DECL|variable|all
DECL|variable|tags
DECL|variable|force
DECL|variable|thin
r_static
r_int
id|all
op_assign
l_int|0
comma
id|tags
op_assign
l_int|0
comma
id|force
op_assign
l_int|0
comma
id|thin
op_assign
l_int|1
suffix:semicolon
DECL|variable|execute
r_static
r_const
r_char
op_star
id|execute
op_assign
l_int|NULL
suffix:semicolon
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE (2084)
DECL|variable|buffer
r_static
r_char
id|buffer
(braket
id|BUF_SIZE
)braket
suffix:semicolon
DECL|variable|refspec
r_static
r_const
r_char
op_star
op_star
id|refspec
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|refspec_nr
r_static
r_int
id|refspec_nr
op_assign
l_int|0
suffix:semicolon
DECL|function|add_refspec
r_static
r_void
id|add_refspec
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
id|nr
op_assign
id|refspec_nr
op_plus
l_int|1
suffix:semicolon
id|refspec
op_assign
id|xrealloc
c_func
(paren
id|refspec
comma
id|nr
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|refspec
(braket
id|nr
op_minus
l_int|1
)braket
op_assign
id|ref
suffix:semicolon
id|refspec_nr
op_assign
id|nr
suffix:semicolon
)brace
DECL|function|expand_one_ref
r_static
r_int
id|expand_one_ref
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
multiline_comment|/* Ignore the &quot;refs/&quot; at the beginning of the refname */
id|ref
op_add_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ref
comma
l_string|&quot;tags/&quot;
comma
l_int|5
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|add_refspec
c_func
(paren
id|strdup
c_func
(paren
id|ref
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|expand_refspecs
r_static
r_void
id|expand_refspecs
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|all
)paren
(brace
r_if
c_cond
(paren
id|refspec_nr
)paren
id|die
c_func
(paren
l_string|&quot;cannot mix &squot;--all&squot; and a refspec&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * No need to expand &quot;--all&quot; - we&squot;ll just use&n;&t;&t; * the &quot;--all&quot; flag to send-pack&n;&t;&t; */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tags
)paren
r_return
suffix:semicolon
id|for_each_ref
c_func
(paren
id|expand_one_ref
)paren
suffix:semicolon
)brace
DECL|function|set_refspecs
r_static
r_void
id|set_refspecs
c_func
(paren
r_const
r_char
op_star
op_star
id|refs
comma
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|nr
)paren
(brace
r_int
id|bytes
op_assign
id|nr
op_star
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|refspec
op_assign
id|xrealloc
c_func
(paren
id|refspec
comma
id|bytes
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|refspec
comma
id|refs
comma
id|bytes
)paren
suffix:semicolon
id|refspec_nr
op_assign
id|nr
suffix:semicolon
)brace
id|expand_refspecs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_remotes_uri
r_static
r_int
id|get_remotes_uri
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_const
r_char
op_star
id|uri
(braket
id|MAX_URI
)braket
)paren
(brace
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;remotes/%s&quot;
comma
id|repo
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_int
id|has_explicit_refspec
op_assign
id|refspec_nr
op_logical_or
id|all
op_logical_or
id|tags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer
comma
id|BUF_SIZE
comma
id|f
)paren
)paren
(brace
r_int
id|is_refspec
suffix:semicolon
r_char
op_star
id|s
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;URL: &quot;
comma
id|buffer
comma
l_int|5
)paren
)paren
(brace
id|is_refspec
op_assign
l_int|0
suffix:semicolon
id|s
op_assign
id|buffer
op_plus
l_int|5
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;Push: &quot;
comma
id|buffer
comma
l_int|6
)paren
)paren
(brace
id|is_refspec
op_assign
l_int|1
suffix:semicolon
id|s
op_assign
id|buffer
op_plus
l_int|6
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
multiline_comment|/* Remove whitespace at the head.. */
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|s
)paren
)paren
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|s
)paren
r_continue
suffix:semicolon
multiline_comment|/* ..and at the end */
id|p
op_assign
id|s
op_plus
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|p
(braket
l_int|1
)braket
)paren
)paren
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_refspec
)paren
(brace
r_if
c_cond
(paren
id|n
OL
id|MAX_URI
)paren
id|uri
(braket
id|n
op_increment
)braket
op_assign
id|strdup
c_func
(paren
id|s
)paren
suffix:semicolon
r_else
id|error
c_func
(paren
l_string|&quot;more than %d URL&squot;s specified, ignoring the rest&quot;
comma
id|MAX_URI
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_refspec
op_logical_and
op_logical_neg
id|has_explicit_refspec
)paren
id|add_refspec
c_func
(paren
id|strdup
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
id|die
c_func
(paren
l_string|&quot;remote &squot;%s&squot; has no URL&quot;
comma
id|repo
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|variable|config_uri
r_static
r_const
r_char
op_star
op_star
id|config_uri
suffix:semicolon
DECL|variable|config_repo
r_static
r_const
r_char
op_star
id|config_repo
suffix:semicolon
DECL|variable|config_repo_len
r_static
r_int
id|config_repo_len
suffix:semicolon
DECL|variable|config_current_uri
r_static
r_int
id|config_current_uri
suffix:semicolon
DECL|variable|config_get_refspecs
r_static
r_int
id|config_get_refspecs
suffix:semicolon
DECL|function|get_remote_config
r_static
r_int
id|get_remote_config
c_func
(paren
r_const
r_char
op_star
id|key
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
id|strncmp
c_func
(paren
id|key
comma
l_string|&quot;remote.&quot;
comma
l_int|7
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|key
op_plus
l_int|7
comma
id|config_repo
comma
id|config_repo_len
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|key
op_plus
l_int|7
op_plus
id|config_repo_len
comma
l_string|&quot;.url&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|config_current_uri
OL
id|MAX_URI
)paren
id|config_uri
(braket
id|config_current_uri
op_increment
)braket
op_assign
id|strdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
id|error
c_func
(paren
l_string|&quot;more than %d URL&squot;s specified, ignoring the rest&quot;
comma
id|MAX_URI
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|config_get_refspecs
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|key
op_plus
l_int|7
op_plus
id|config_repo_len
comma
l_string|&quot;.push&quot;
)paren
)paren
id|add_refspec
c_func
(paren
id|strdup
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_config_remotes_uri
r_static
r_int
id|get_config_remotes_uri
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_const
r_char
op_star
id|uri
(braket
id|MAX_URI
)braket
)paren
(brace
id|config_repo_len
op_assign
id|strlen
c_func
(paren
id|repo
)paren
suffix:semicolon
id|config_repo
op_assign
id|repo
suffix:semicolon
id|config_current_uri
op_assign
l_int|0
suffix:semicolon
id|config_uri
op_assign
id|uri
suffix:semicolon
id|config_get_refspecs
op_assign
op_logical_neg
(paren
id|refspec_nr
op_logical_or
id|all
op_logical_or
id|tags
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|get_remote_config
)paren
suffix:semicolon
r_return
id|config_current_uri
suffix:semicolon
)brace
DECL|function|get_branches_uri
r_static
r_int
id|get_branches_uri
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_const
r_char
op_star
id|uri
(braket
id|MAX_URI
)braket
)paren
(brace
r_const
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
id|repo
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_int
id|n
op_assign
id|slash
ques
c_cond
id|slash
id|repo
suffix:colon
l_int|1000
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;branches/%.*s&quot;
comma
id|n
comma
id|repo
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_char
op_star
id|s
comma
op_star
id|p
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
l_int|0
suffix:semicolon
id|s
op_assign
id|fgets
c_func
(paren
id|buffer
comma
id|BUF_SIZE
comma
id|f
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|s
)paren
)paren
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|s
)paren
r_return
l_int|0
suffix:semicolon
id|p
op_assign
id|s
op_plus
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|p
(braket
l_int|1
)braket
)paren
)paren
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|p
id|s
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
id|len
op_add_assign
id|strlen
c_func
(paren
id|slash
)paren
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
id|strcat
c_func
(paren
id|p
comma
id|slash
)paren
suffix:semicolon
id|uri
(braket
l_int|0
)braket
op_assign
id|p
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Read remotes and branches file, fill the push target URI&n; * list.  If there is no command line refspecs, read Push: lines&n; * to set up the *refspec list as well.&n; * return the number of push target URIs&n; */
DECL|function|read_config
r_static
r_int
id|read_config
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_const
r_char
op_star
id|uri
(braket
id|MAX_URI
)braket
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
op_star
id|repo
op_ne
l_char|&squot;/&squot;
)paren
(brace
id|n
op_assign
id|get_remotes_uri
c_func
(paren
id|repo
comma
id|uri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
r_return
id|n
suffix:semicolon
id|n
op_assign
id|get_config_remotes_uri
c_func
(paren
id|repo
comma
id|uri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
r_return
id|n
suffix:semicolon
id|n
op_assign
id|get_branches_uri
c_func
(paren
id|repo
comma
id|uri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
r_return
id|n
suffix:semicolon
)brace
id|uri
(braket
l_int|0
)braket
op_assign
id|repo
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|do_push
r_static
r_int
id|do_push
c_func
(paren
r_const
r_char
op_star
id|repo
)paren
(brace
r_const
r_char
op_star
id|uri
(braket
id|MAX_URI
)braket
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_int
id|common_argc
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
r_int
id|argc
suffix:semicolon
id|n
op_assign
id|read_config
c_func
(paren
id|repo
comma
id|uri
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad repository &squot;%s&squot;&quot;
comma
id|repo
)paren
suffix:semicolon
id|argv
op_assign
id|xmalloc
c_func
(paren
(paren
id|refspec_nr
op_plus
l_int|10
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
l_string|&quot;dummy-send-pack&quot;
suffix:semicolon
id|argc
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|all
)paren
id|argv
(braket
id|argc
op_increment
)braket
op_assign
l_string|&quot;--all&quot;
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
id|argv
(braket
id|argc
op_increment
)braket
op_assign
l_string|&quot;--force&quot;
suffix:semicolon
r_if
c_cond
(paren
id|execute
)paren
id|argv
(braket
id|argc
op_increment
)braket
op_assign
id|execute
suffix:semicolon
id|common_argc
op_assign
id|argc
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|dest_argc
op_assign
id|common_argc
suffix:semicolon
r_int
id|dest_refspec_nr
op_assign
id|refspec_nr
suffix:semicolon
r_const
r_char
op_star
op_star
id|dest_refspec
op_assign
id|refspec
suffix:semicolon
r_const
r_char
op_star
id|dest
op_assign
id|uri
(braket
id|i
)braket
suffix:semicolon
r_const
r_char
op_star
id|sender
op_assign
l_string|&quot;git-send-pack&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dest
comma
l_string|&quot;http://&quot;
comma
l_int|7
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|dest
comma
l_string|&quot;https://&quot;
comma
l_int|8
)paren
)paren
id|sender
op_assign
l_string|&quot;git-http-push&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|thin
)paren
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
l_string|&quot;--thin&quot;
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|sender
suffix:semicolon
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
id|dest_refspec_nr
op_decrement
)paren
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
op_star
id|dest_refspec
op_increment
suffix:semicolon
id|argv
(braket
id|dest_argc
)braket
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
id|run_command_v
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|error
)paren
(brace
r_case
id|ERR_RUN_COMMAND_FORK
suffix:colon
id|die
c_func
(paren
l_string|&quot;unable to fork for %s&quot;
comma
id|sender
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_EXEC
suffix:colon
id|die
c_func
(paren
l_string|&quot;unable to exec %s&quot;
comma
id|sender
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID
suffix:colon
r_case
id|ERR_RUN_COMMAND_WAITPID_WRONG_PID
suffix:colon
r_case
id|ERR_RUN_COMMAND_WAITPID_SIGNAL
suffix:colon
r_case
id|ERR_RUN_COMMAND_WAITPID_NOEXIT
suffix:colon
id|die
c_func
(paren
l_string|&quot;%s died with strange error&quot;
comma
id|sender
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|error
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_push
r_int
id|cmd_push
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
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
id|repo
op_assign
l_string|&quot;origin&quot;
suffix:semicolon
multiline_comment|/* default repository */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
(brace
id|repo
op_assign
id|arg
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|all
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--tags&quot;
)paren
)paren
(brace
id|tags
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--force&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|force
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--thin&quot;
)paren
)paren
(brace
id|thin
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--no-thin&quot;
)paren
)paren
(brace
id|thin
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--exec=&quot;
comma
l_int|7
)paren
)paren
(brace
id|execute
op_assign
id|arg
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|push_usage
)paren
suffix:semicolon
)brace
id|set_refspecs
c_func
(paren
id|argv
op_plus
id|i
comma
id|argc
id|i
)paren
suffix:semicolon
r_return
id|do_push
c_func
(paren
id|repo
)paren
suffix:semicolon
)brace
eof
