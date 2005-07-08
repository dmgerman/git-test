macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|function|get_ack
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
DECL|function|path_match
r_int
id|path_match
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|nr
comma
r_char
op_star
op_star
id|match
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|s
op_assign
id|match
(braket
id|i
)braket
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
id|len
OG
id|pathlen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|path
op_plus
id|pathlen
id|len
comma
id|s
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OG
id|len
op_logical_and
id|path
(braket
id|pathlen
id|len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
op_star
id|s
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * First, make it shell-safe.  We do this by just disallowing any&n; * special characters. Somebody who cares can do escaping and let&n; * through the rest. But since we&squot;re doing to feed this to ssh as&n; * a command line, we&squot;re going to be pretty damn anal for now.&n; */
DECL|function|shell_safe
r_static
r_char
op_star
id|shell_safe
c_func
(paren
r_char
op_star
id|url
)paren
(brace
r_char
op_star
id|n
op_assign
id|url
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_static
r_const
r_char
id|flags
(braket
l_int|256
)braket
op_assign
(brace
(braket
l_char|&squot;0&squot;
dot
dot
dot
l_char|&squot;9&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;a&squot;
dot
dot
dot
l_char|&squot;z&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;A&squot;
dot
dot
dot
l_char|&squot;Z&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;.&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;/&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;-&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;+&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;:&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;_&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;@&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;,&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;~&squot;
)braket
op_assign
l_int|1
comma
(braket
l_char|&squot;^&squot;
)braket
op_assign
l_int|1
comma
)brace
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|n
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|flags
(braket
id|c
)braket
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;I don&squot;t like &squot;%c&squot;. Sue me.&quot;
comma
id|c
)paren
suffix:semicolon
)brace
r_return
id|url
suffix:semicolon
)brace
multiline_comment|/*&n; * Yeah, yeah, fixme. Need to pass in the heads etc.&n; */
DECL|function|git_connect
r_int
id|git_connect
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_char
op_star
id|url
comma
r_const
r_char
op_star
id|prog
)paren
(brace
r_char
id|command
(braket
l_int|1024
)braket
suffix:semicolon
r_const
r_char
op_star
id|host
comma
op_star
id|path
suffix:semicolon
r_char
op_star
id|colon
suffix:semicolon
r_int
id|pipefd
(braket
l_int|2
)braket
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|url
op_assign
id|shell_safe
c_func
(paren
id|url
)paren
suffix:semicolon
id|host
op_assign
l_int|NULL
suffix:semicolon
id|path
op_assign
id|url
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|url
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|colon
)paren
(brace
op_star
id|colon
op_assign
l_int|0
suffix:semicolon
id|host
op_assign
id|url
suffix:semicolon
id|path
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|command
comma
r_sizeof
(paren
id|command
)paren
comma
l_string|&quot;%s %s&quot;
comma
id|prog
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pipefd
(braket
l_int|0
)braket
)paren
OL
l_int|0
op_logical_or
id|pipe
c_func
(paren
id|pipefd
(braket
l_int|1
)braket
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to create pipe pair for communication&quot;
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
op_logical_neg
id|pid
)paren
(brace
id|dup2
c_func
(paren
id|pipefd
(braket
l_int|1
)braket
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|pipefd
(braket
l_int|0
)braket
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipefd
(braket
l_int|0
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipefd
(braket
l_int|0
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipefd
(braket
l_int|1
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipefd
(braket
l_int|1
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host
)paren
id|execlp
c_func
(paren
l_string|&quot;ssh&quot;
comma
l_string|&quot;ssh&quot;
comma
id|host
comma
id|command
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|execlp
c_func
(paren
l_string|&quot;sh&quot;
comma
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
id|command
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;exec failed&quot;
)paren
suffix:semicolon
)brace
id|fd
(braket
l_int|0
)braket
op_assign
id|pipefd
(braket
l_int|0
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
id|pipefd
(braket
l_int|1
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|close
c_func
(paren
id|pipefd
(braket
l_int|0
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipefd
(braket
l_int|1
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
DECL|function|finish_connect
r_int
id|finish_connect
c_func
(paren
id|pid_t
id|pid
)paren
(brace
r_int
id|ret
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|ret
op_assign
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
