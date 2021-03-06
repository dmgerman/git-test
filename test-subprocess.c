macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
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
r_struct
id|child_process
id|cp
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
r_int
id|nogit
op_assign
l_int|0
suffix:semicolon
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nogit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nogit
)paren
id|die
c_func
(paren
l_string|&quot;No git repo found&quot;
)paren
suffix:semicolon
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
l_string|&quot;--setup-work-tree&quot;
)paren
)paren
(brace
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
id|cp.git_cmd
op_assign
l_int|1
suffix:semicolon
id|cp.argv
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
id|argv
op_plus
l_int|1
suffix:semicolon
r_return
id|run_command
c_func
(paren
op_amp
id|cp
)paren
suffix:semicolon
)brace
eof
