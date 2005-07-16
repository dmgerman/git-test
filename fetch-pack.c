macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|quiet
r_static
r_int
id|quiet
suffix:semicolon
DECL|variable|fetch_pack_usage
r_static
r_const
r_char
id|fetch_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-fetch-pack [-q] [--exec=upload-pack] [host:]directory [heads]* &lt; mycommitlist&quot;
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
comma
r_int
r_char
op_star
id|remote
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
comma
id|retval
suffix:semicolon
id|FILE
op_star
id|revs
suffix:semicolon
id|revs
op_assign
id|popen
c_func
(paren
l_string|&quot;git-rev-list $(git-rev-parse --all)&quot;
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs
)paren
id|die
c_func
(paren
l_string|&quot;unable to run &squot;git-rev-list&squot;&quot;
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
l_string|&quot;want %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|remote
)paren
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
id|flushes
op_assign
l_int|1
suffix:semicolon
id|retval
op_assign
l_int|1
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
id|revs
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
(brace
id|flushes
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|flushes
op_decrement
suffix:semicolon
)brace
)brace
id|pclose
c_func
(paren
id|revs
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
l_string|&quot;done&bslash;n&quot;
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
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Eventually we&squot;ll want to be able to fetch multiple heads.&n; *&n; * Right now we&squot;ll just require a single match.&n; */
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
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
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
id|nr_match
comma
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref
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
id|die
c_func
(paren
l_string|&quot;no matching remote head&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ref-&gt;next
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
id|die
c_func
(paren
l_string|&quot;multiple remote heads&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|find_common
c_func
(paren
id|fd
comma
id|sha1
comma
id|ref-&gt;old_sha1
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
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: unable to fork off git-unpack-objects&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|dup2
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
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
id|execlp
c_func
(paren
l_string|&quot;git-unpack-objects&quot;
comma
l_string|&quot;git-unpack-objects&quot;
comma
id|quiet
ques
c_cond
l_string|&quot;-q&quot;
suffix:colon
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects exec failed&quot;
)paren
suffix:semicolon
)brace
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
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
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
id|EINTR
)paren
id|die
c_func
(paren
l_string|&quot;waiting for git-unpack-objects: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died with error code %d&quot;
comma
id|code
)paren
suffix:semicolon
id|puts
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|sig
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died of signal %d&quot;
comma
id|sig
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;Sherlock Holmes! git-unpack-objects died of unnatural causes %d!&quot;
comma
id|status
)paren
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
(brace
id|exec
op_assign
id|arg
op_plus
l_int|7
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
