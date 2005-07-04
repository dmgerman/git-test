macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
DECL|variable|fetch_pack_usage
r_static
r_const
r_char
id|fetch_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-fetch-pack [host:]directory [heads]* &lt; mycommitlist&quot;
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
DECL|function|get_ack
r_static
r_int
id|get_ack
c_func
(paren
r_int
id|fd
comma
r_int
r_char
op_star
id|result_sha1
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: expected ACK/NAK, got EOF&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;NAK&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;ACK &quot;
comma
l_int|3
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|4
comma
id|result_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;git-fetch_pack: expected ACK/NAK, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
)brace
DECL|function|find_common
r_static
r_int
id|find_common
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
r_char
op_star
id|result_sha1
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|count
op_assign
l_int|0
comma
id|flushes
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|line
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: expected object name, got crud&quot;
)paren
suffix:semicolon
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;have %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
l_int|31
op_amp
op_increment
id|count
)paren
)paren
(brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|flushes
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We keep one window &quot;ahead&quot; of the other side, and&n;&t;&t;&t; * will wait for an ACK only on the next one&n;&t;&t;&t; */
r_if
c_cond
(paren
id|count
op_eq
l_int|32
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|get_ack
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|result_sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|flushes
op_decrement
suffix:semicolon
)brace
)brace
id|flushes
op_increment
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
id|flushes
)paren
(brace
id|flushes
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|get_ack
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|result_sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_remote_heads
r_static
r_int
id|get_remote_heads
c_func
(paren
r_int
id|fd
comma
r_int
id|nr_match
comma
r_char
op_star
op_star
id|match
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|42
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: protocol error - expected ref descriptor, got &squot;%s&auml;&squot;&quot;
comma
id|line
)paren
suffix:semicolon
id|refname
op_assign
id|line
op_plus
l_int|41
suffix:semicolon
r_if
c_cond
(paren
id|nr_match
op_logical_and
op_logical_neg
id|path_match
c_func
(paren
id|refname
comma
id|nr_match
comma
id|match
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|refname
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_pack
r_static
r_int
id|fetch_pack
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
id|nr_match
comma
r_char
op_star
op_star
id|match
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|get_remote_heads
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|nr_match
comma
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|find_common
c_func
(paren
id|fd
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: no common commits&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;common commit: %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
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
comma
id|nr_heads
suffix:semicolon
r_char
op_star
id|dest
op_assign
l_int|NULL
comma
op_star
op_star
id|heads
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
id|nr_heads
op_assign
l_int|0
suffix:semicolon
id|heads
op_assign
l_int|NULL
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
multiline_comment|/* Arguments go here */
id|usage
c_func
(paren
id|fetch_pack_usage
)paren
suffix:semicolon
)brace
id|dest
op_assign
id|arg
suffix:semicolon
id|heads
op_assign
id|argv
op_plus
id|i
op_plus
l_int|1
suffix:semicolon
id|nr_heads
op_assign
id|argc
id|i
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
id|usage
c_func
(paren
id|fetch_pack_usage
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
id|fetch_pack
c_func
(paren
id|fd
comma
id|nr_heads
comma
id|heads
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
