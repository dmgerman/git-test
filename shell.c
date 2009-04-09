macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;strbuf.h&quot;
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
r_struct
id|commands
op_star
id|cmd
suffix:semicolon
r_int
id|devnull_fd
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
id|die
c_func
(paren
l_string|&quot;opening /dev/null failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
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
id|argv
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * We do not accept anything but &quot;-c&quot; followed by &quot;cmd arg&quot;,&n;&t; * where &quot;cmd&quot; is a very limited subset of git commands.&n;&t; */
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
id|die
c_func
(paren
l_string|&quot;What do you think I am? A shell?&quot;
)paren
suffix:semicolon
id|prog
op_assign
id|argv
(braket
l_int|2
)braket
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
id|die
c_func
(paren
l_string|&quot;unrecognized command &squot;%s&squot;&quot;
comma
id|prog
)paren
suffix:semicolon
)brace
eof
