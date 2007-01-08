macro_line|#ifndef COUNTERPART_ENV_NAME
DECL|macro|COUNTERPART_ENV_NAME
mdefine_line|#define COUNTERPART_ENV_NAME &quot;GIT_SSH_UPLOAD&quot;
macro_line|#endif
macro_line|#ifndef COUNTERPART_PROGRAM_NAME
DECL|macro|COUNTERPART_PROGRAM_NAME
mdefine_line|#define COUNTERPART_PROGRAM_NAME &quot;git-ssh-upload&quot;
macro_line|#endif
macro_line|#ifndef MY_PROGRAM_NAME
DECL|macro|MY_PROGRAM_NAME
mdefine_line|#define MY_PROGRAM_NAME &quot;git-ssh-fetch&quot;
macro_line|#endif
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;rsh.h&quot;
macro_line|#include &quot;fetch.h&quot;
macro_line|#include &quot;refs.h&quot;
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
DECL|variable|remote_version
r_static
r_int
r_char
id|remote_version
suffix:semicolon
DECL|variable|local_version
r_static
r_int
r_char
id|local_version
op_assign
l_int|1
suffix:semicolon
DECL|function|force_write
r_static
id|ssize_t
id|force_write
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ret
OL
id|length
)paren
(brace
id|ssize_t
id|size
op_assign
id|write
c_func
(paren
id|fd
comma
(paren
r_char
op_star
)paren
id|buffer
op_plus
id|ret
comma
id|length
id|ret
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
r_return
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_add_assign
id|size
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|prefetches
r_static
r_int
id|prefetches
suffix:semicolon
DECL|variable|in_transit
r_static
r_struct
id|object_list
op_star
id|in_transit
suffix:semicolon
DECL|variable|end_of_transit
r_static
r_struct
id|object_list
op_star
op_star
id|end_of_transit
op_assign
op_amp
id|in_transit
suffix:semicolon
DECL|function|prefetch
r_void
id|prefetch
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
id|type
op_assign
l_char|&squot;o&squot;
suffix:semicolon
r_struct
id|object_list
op_star
id|node
suffix:semicolon
r_if
c_cond
(paren
id|prefetches
OG
l_int|100
)paren
(brace
id|fetch
c_func
(paren
id|in_transit-&gt;item-&gt;sha1
)paren
suffix:semicolon
)brace
id|node
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|object_list
)paren
)paren
suffix:semicolon
id|node-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|node-&gt;item
op_assign
id|lookup_unknown_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
op_star
id|end_of_transit
op_assign
id|node
suffix:semicolon
id|end_of_transit
op_assign
op_amp
id|node-&gt;next
suffix:semicolon
id|force_write
c_func
(paren
id|fd_out
comma
op_amp
id|type
comma
l_int|1
)paren
suffix:semicolon
id|force_write
c_func
(paren
id|fd_out
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|prefetches
op_increment
suffix:semicolon
)brace
DECL|variable|conn_buf
r_static
r_char
id|conn_buf
(braket
l_int|4096
)braket
suffix:semicolon
DECL|variable|conn_buf_posn
r_static
r_int
id|conn_buf_posn
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
r_int
r_char
id|remote
suffix:semicolon
r_struct
id|object_list
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|in_transit-&gt;item-&gt;sha1
)paren
)paren
(brace
multiline_comment|/* we must have already fetched it to clean the queue */
r_return
id|has_sha1_file
c_func
(paren
id|sha1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
id|prefetches
op_decrement
suffix:semicolon
id|temp
op_assign
id|in_transit
suffix:semicolon
id|in_transit
op_assign
id|in_transit-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_transit
)paren
id|end_of_transit
op_assign
op_amp
id|in_transit
suffix:semicolon
id|free
c_func
(paren
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conn_buf_posn
)paren
(brace
id|remote
op_assign
id|conn_buf
(braket
l_int|0
)braket
suffix:semicolon
id|memmove
c_func
(paren
id|conn_buf
comma
id|conn_buf
op_plus
l_int|1
comma
op_decrement
id|conn_buf_posn
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|xread
c_func
(paren
id|fd_in
comma
op_amp
id|remote
comma
l_int|1
)paren
OL
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* fprintf(stderr, &quot;Got %d&bslash;n&quot;, remote); */
r_if
c_cond
(paren
id|remote
OL
l_int|0
)paren
r_return
id|remote
suffix:semicolon
id|ret
op_assign
id|write_sha1_from_fd
c_func
(paren
id|sha1
comma
id|fd_in
comma
id|conn_buf
comma
l_int|4096
comma
op_amp
id|conn_buf_posn
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
DECL|function|get_version
r_static
r_int
id|get_version
c_func
(paren
r_void
)paren
(brace
r_char
id|type
op_assign
l_char|&squot;v&squot;
suffix:semicolon
id|write
c_func
(paren
id|fd_out
comma
op_amp
id|type
comma
l_int|1
)paren
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
r_if
c_cond
(paren
id|xread
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
(brace
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t read version from remote end&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_ref
r_int
id|fetch_ref
c_func
(paren
r_char
op_star
id|ref
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_char
id|remote
suffix:semicolon
r_char
id|type
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|write
c_func
(paren
id|fd_out
comma
op_amp
id|type
comma
l_int|1
)paren
suffix:semicolon
id|write
c_func
(paren
id|fd_out
comma
id|ref
comma
id|strlen
c_func
(paren
id|ref
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_in_full
c_func
(paren
id|fd_in
comma
op_amp
id|remote
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|remote
OL
l_int|0
)paren
r_return
id|remote
suffix:semicolon
r_if
c_cond
(paren
id|read_in_full
c_func
(paren
id|fd_in
comma
id|sha1
comma
l_int|20
)paren
op_ne
l_int|20
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ssh_fetch_usage
r_static
r_const
r_char
id|ssh_fetch_usage
(braket
)braket
op_assign
id|MY_PROGRAM_NAME
l_string|&quot; [-c] [-t] [-a] [-v] [--recover] [-w ref] commit-id url&quot;
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
r_const
r_char
op_star
id|write_ref
op_assign
l_int|NULL
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
id|arg
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|prog
suffix:semicolon
id|prog
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSH_PUSH&quot;
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
l_string|&quot;git-ssh-upload&quot;
suffix:semicolon
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
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
l_char|&squot;w&squot;
)paren
(brace
id|write_ref
op_assign
id|argv
(braket
id|arg
op_plus
l_int|1
)braket
suffix:semicolon
id|arg
op_increment
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
id|argv
(braket
id|arg
)braket
comma
l_string|&quot;--recover&quot;
)paren
)paren
(brace
id|get_recover
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
id|ssh_fetch_usage
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
r_if
c_cond
(paren
id|get_version
c_func
(paren
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
l_int|1
comma
op_amp
id|commit_id
comma
op_amp
id|write_ref
comma
id|url
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
