macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#include &quot;connected.h&quot;
multiline_comment|/*&n; * If we feed all the commits we want to verify to this command&n; *&n; *  $ git rev-list --objects --stdin --not --all&n; *&n; * and if it does not error out, that means everything reachable from&n; * these commits locally exists and is connected to our existing refs.&n; * Note that this does _not_ validate the individual objects.&n; *&n; * Returns 0 if everything is connected, non-zero otherwise.&n; */
DECL|function|check_everything_connected
r_int
id|check_everything_connected
c_func
(paren
id|sha1_iterate_fn
id|fn
comma
r_int
id|quiet
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|child_process
id|rev_list
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;rev-list&quot;
comma
l_string|&quot;--objects&quot;
comma
l_string|&quot;--stdin&quot;
comma
l_string|&quot;--not&quot;
comma
l_string|&quot;--all&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_char
id|commit
(braket
l_int|41
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fn
c_func
(paren
id|cb_data
comma
id|sha1
)paren
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|quiet
)paren
id|argv
(braket
l_int|5
)braket
op_assign
l_string|&quot;--quiet&quot;
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rev_list
comma
l_int|0
comma
r_sizeof
(paren
id|rev_list
)paren
)paren
suffix:semicolon
id|rev_list.argv
op_assign
id|argv
suffix:semicolon
id|rev_list.git_cmd
op_assign
l_int|1
suffix:semicolon
id|rev_list.in
op_assign
l_int|1
suffix:semicolon
id|rev_list.no_stdout
op_assign
l_int|1
suffix:semicolon
id|rev_list.no_stderr
op_assign
id|quiet
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|rev_list
)paren
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not run &squot;git rev-list&squot;&quot;
)paren
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGPIPE
comma
id|SIG_IGN
)paren
suffix:semicolon
id|commit
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_do
(brace
id|memcpy
c_func
(paren
id|commit
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|rev_list.in
comma
id|commit
comma
l_int|41
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EPIPE
op_logical_and
id|errno
op_ne
id|EINVAL
)paren
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;failed write to rev-list: %s&quot;
)paren
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|err
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|fn
c_func
(paren
id|cb_data
comma
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close
c_func
(paren
id|rev_list.in
)paren
)paren
(brace
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;failed to close rev-list&squot;s stdin: %s&quot;
)paren
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|err
op_assign
l_int|1
suffix:semicolon
)brace
id|sigchain_pop
c_func
(paren
id|SIGPIPE
)paren
suffix:semicolon
r_return
id|finish_command
c_func
(paren
op_amp
id|rev_list
)paren
op_logical_or
id|err
suffix:semicolon
)brace
eof
