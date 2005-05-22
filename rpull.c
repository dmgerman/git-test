macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;rsh.h&quot;
macro_line|#include &quot;pull.h&quot;
DECL|variable|fd_in
r_static
r_int
id|fd_in
suffix:semicolon
DECL|variable|fd_out
r_static
r_int
id|fd_out
suffix:semicolon
DECL|function|fetch
r_int
id|fetch
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|ret
suffix:semicolon
id|write
c_func
(paren
id|fd_out
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|ret
op_assign
id|write_sha1_from_fd
c_func
(paren
id|sha1
comma
id|fd_in
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|pull_say
c_func
(paren
l_string|&quot;got %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
id|ret
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
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
op_star
id|commit_id
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_int
id|arg
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|arg
OL
id|argc
op_logical_and
id|argv
(braket
id|arg
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;t&squot;
)paren
(brace
id|get_tree
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;c&squot;
)paren
(brace
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;a&squot;
)paren
(brace
id|get_all
op_assign
l_int|1
suffix:semicolon
id|get_tree
op_assign
l_int|1
suffix:semicolon
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;v&squot;
)paren
(brace
id|get_verbosely
op_assign
l_int|1
suffix:semicolon
)brace
id|arg
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
id|arg
op_plus
l_int|2
)paren
(brace
id|usage
c_func
(paren
l_string|&quot;git-rpull [-c] [-t] [-a] [-v] commit-id url&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|commit_id
op_assign
id|argv
(braket
id|arg
)braket
suffix:semicolon
id|url
op_assign
id|argv
(braket
id|arg
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|setup_connection
c_func
(paren
op_amp
id|fd_in
comma
op_amp
id|fd_out
comma
l_string|&quot;git-rpush&quot;
comma
id|url
comma
id|arg
comma
id|argv
op_plus
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pull
c_func
(paren
id|commit_id
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
