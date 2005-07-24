macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|peek_remote_usage
r_static
r_const
r_char
id|peek_remote_usage
(braket
)braket
op_assign
l_string|&quot;git-peek-remote [--exec=upload-pack] [host:]directory&quot;
suffix:semicolon
DECL|variable|exec
r_static
r_const
r_char
op_star
id|exec
op_assign
l_string|&quot;git-upload-pack&quot;
suffix:semicolon
DECL|function|peek_remote
r_static
r_int
id|peek_remote
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
id|get_remote_heads
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
op_amp
id|ref
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ref
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&t;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
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
r_int
id|i
comma
id|ret
suffix:semicolon
r_char
op_star
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
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
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;--exec=&quot;
comma
id|arg
comma
l_int|7
)paren
)paren
id|exec
op_assign
id|arg
op_plus
l_int|7
suffix:semicolon
r_else
id|usage
c_func
(paren
id|peek_remote_usage
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dest
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
op_logical_or
id|i
op_ne
id|argc
l_int|1
)paren
id|usage
c_func
(paren
id|peek_remote_usage
)paren
suffix:semicolon
id|pid
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|dest
comma
id|exec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
id|peek_remote
c_func
(paren
id|fd
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|finish_connect
c_func
(paren
id|pid
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
