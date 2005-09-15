macro_line|#ifndef COUNTERPART_ENV_NAME
DECL|macro|COUNTERPART_ENV_NAME
mdefine_line|#define COUNTERPART_ENV_NAME &quot;GIT_SSH_FETCH&quot;
macro_line|#endif
macro_line|#ifndef COUNTERPART_PROGRAM_NAME
DECL|macro|COUNTERPART_PROGRAM_NAME
mdefine_line|#define COUNTERPART_PROGRAM_NAME &quot;git-ssh-fetch&quot;
macro_line|#endif
macro_line|#ifndef MY_PROGRAM_NAME
DECL|macro|MY_PROGRAM_NAME
mdefine_line|#define MY_PROGRAM_NAME &quot;git-ssh-upload&quot;
macro_line|#endif
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;rsh.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &lt;string.h&gt;
DECL|variable|local_version
r_static
r_int
r_char
id|local_version
op_assign
l_int|1
suffix:semicolon
DECL|variable|remote_version
r_static
r_int
r_char
id|remote_version
op_assign
l_int|0
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
DECL|function|serve_object
r_static
r_int
id|serve_object
c_func
(paren
r_int
id|fd_in
comma
r_int
id|fd_out
)paren
(brace
id|ssize_t
id|size
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|remote
suffix:semicolon
r_int
id|posn
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|size
op_assign
id|read
c_func
(paren
id|fd_in
comma
id|sha1
op_plus
id|posn
comma
l_int|20
id|posn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;git-ssh-upload: read &quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|1
suffix:semicolon
id|posn
op_add_assign
id|size
suffix:semicolon
)brace
r_while
c_loop
(paren
id|posn
OL
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Serving %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|remote
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git-ssh-upload: could not find %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|remote
op_assign
l_int|1
suffix:semicolon
)brace
id|write
c_func
(paren
id|fd_out
comma
op_amp
id|remote
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|write_sha1_to_fd
c_func
(paren
id|fd_out
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|serve_version
r_static
r_int
id|serve_version
c_func
(paren
r_int
id|fd_in
comma
r_int
id|fd_out
)paren
(brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd_in
comma
op_amp
id|remote_version
comma
l_int|1
)paren
OL
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
id|write
c_func
(paren
id|fd_out
comma
op_amp
id|local_version
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|serve_ref
r_static
r_int
id|serve_ref
c_func
(paren
r_int
id|fd_in
comma
r_int
id|fd_out
)paren
(brace
r_char
id|ref
(braket
id|PATH_MAX
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
id|posn
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|remote
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd_in
comma
id|ref
op_plus
id|posn
comma
l_int|1
)paren
OL
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
id|posn
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ref
(braket
id|posn
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Serving %s&bslash;n&quot;
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_ref_sha1
c_func
(paren
id|ref
comma
id|sha1
)paren
)paren
id|remote
op_assign
l_int|1
suffix:semicolon
id|write
c_func
(paren
id|fd_out
comma
op_amp
id|remote
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
)paren
r_return
l_int|0
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|service
r_static
r_void
id|service
c_func
(paren
r_int
id|fd_in
comma
r_int
id|fd_out
)paren
(brace
r_char
id|type
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_do
(brace
id|retval
op_assign
id|read
c_func
(paren
id|fd_in
comma
op_amp
id|type
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
id|perror
c_func
(paren
l_string|&quot;git-ssh-upload: read &quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
l_char|&squot;v&squot;
op_logical_and
id|serve_version
c_func
(paren
id|fd_in
comma
id|fd_out
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
l_char|&squot;o&squot;
op_logical_and
id|serve_object
c_func
(paren
id|fd_in
comma
id|fd_out
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
l_char|&squot;r&squot;
op_logical_and
id|serve_ref
c_func
(paren
id|fd_in
comma
id|fd_out
)paren
)paren
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|ssh_push_usage
r_static
r_const
r_char
id|ssh_push_usage
(braket
)braket
op_assign
id|MY_PROGRAM_NAME
l_string|&quot; [-c] [-t] [-a] [-w ref] commit-id url&quot;
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
r_int
id|arg
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|commit_id
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_int
id|fd_in
comma
id|fd_out
suffix:semicolon
r_const
r_char
op_star
id|prog
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
id|prog
op_assign
id|getenv
c_func
(paren
id|COUNTERPART_ENV_NAME
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prog
)paren
id|prog
op_assign
id|COUNTERPART_PROGRAM_NAME
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
l_char|&squot;w&squot;
)paren
id|arg
op_increment
suffix:semicolon
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
id|usage
c_func
(paren
id|ssh_push_usage
)paren
suffix:semicolon
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
id|get_sha1
c_func
(paren
id|commit_id
comma
id|sha1
)paren
)paren
id|usage
c_func
(paren
id|ssh_push_usage
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_sizeof
(paren
id|hex
)paren
)paren
suffix:semicolon
id|argv
(braket
id|arg
)braket
op_assign
id|hex
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
id|prog
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
id|service
c_func
(paren
id|fd_in
comma
id|fd_out
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
