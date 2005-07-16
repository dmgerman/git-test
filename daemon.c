macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
DECL|variable|daemon_usage
r_static
r_const
r_char
id|daemon_usage
(braket
)braket
op_assign
l_string|&quot;git-daemon [--inetd | --port=n]&quot;
suffix:semicolon
multiline_comment|/* We don&squot;t actually do anything about this yet */
DECL|variable|max_connections
r_static
r_int
id|max_connections
op_assign
l_int|10
suffix:semicolon
multiline_comment|/*&n; * We count spawned/reaped separately, just to avoid any&n; * races when updating them from signals. The SIGCHLD handler&n; * will only update children_reaped, and the fork logic will&n; * only update children_spawned.&n; */
DECL|variable|children_spawned
r_static
r_int
r_int
id|children_spawned
op_assign
l_int|0
suffix:semicolon
DECL|variable|children_reaped
r_static
r_int
r_int
id|children_reaped
op_assign
l_int|0
suffix:semicolon
DECL|function|upload
r_static
r_int
id|upload
c_func
(paren
r_char
op_star
id|dir
comma
r_int
id|dirlen
)paren
(brace
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|dir
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|chdir
c_func
(paren
l_string|&quot;.git&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Security on the cheap.&n;&t; *&n;&t; * We want a readable HEAD, usable &quot;objects&quot; directory, and &n;&t; * a &quot;git-daemon-export-ok&quot; flag that says that the other side&n;&t; * is ok with us doing this.&n;&t; */
r_if
c_cond
(paren
id|access
c_func
(paren
l_string|&quot;git-daemon-export-ok&quot;
comma
id|F_OK
)paren
op_logical_or
id|access
c_func
(paren
l_string|&quot;objects/00&quot;
comma
id|X_OK
)paren
op_logical_or
id|access
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|R_OK
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* git-upload-pack only ever reads stuff, so this is safe */
id|execlp
c_func
(paren
l_string|&quot;git-upload-pack&quot;
comma
l_string|&quot;git-upload-pack&quot;
comma
l_string|&quot;.&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|execute
r_static
r_int
id|execute
c_func
(paren
r_void
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
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
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
id|len
op_logical_and
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
id|strncmp
c_func
(paren
l_string|&quot;git-upload-pack /&quot;
comma
id|line
comma
l_int|17
)paren
)paren
r_return
id|upload
c_func
(paren
id|line
op_plus
l_int|16
comma
id|len
l_int|16
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;got bad connection &squot;%s&squot;&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|handle
r_static
r_void
id|handle
c_func
(paren
r_int
id|incoming
comma
r_struct
id|sockaddr_in
op_star
id|addr
comma
r_int
id|addrlen
)paren
(brace
id|pid_t
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
)paren
(brace
r_int
id|active
suffix:semicolon
id|close
c_func
(paren
id|incoming
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
suffix:semicolon
id|active
op_assign
op_increment
id|children_spawned
id|children_reaped
suffix:semicolon
r_if
c_cond
(paren
id|active
OG
id|max_connections
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Fixme! This is where you&squot;d have to do something to&n;&t;&t;&t; * limit the number of children. Like killing off random&n;&t;&t;&t; * ones, or at least the ones that haven&squot;t even gotten&n;&t;&t;&t; * started yet.&n;&t;&t;&t; */
)brace
r_return
suffix:semicolon
)brace
id|dup2
c_func
(paren
id|incoming
comma
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|incoming
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|incoming
)paren
suffix:semicolon
m_exit
(paren
id|execute
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|child_handler
r_static
r_void
id|child_handler
c_func
(paren
r_int
id|signo
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|waitpid
c_func
(paren
l_int|1
comma
l_int|NULL
comma
id|WNOHANG
)paren
OG
l_int|0
)paren
(brace
id|children_reaped
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|serve
r_static
r_int
id|serve
c_func
(paren
r_int
id|port
)paren
(brace
r_int
id|sockfd
suffix:semicolon
r_struct
id|sockaddr_in
id|addr
suffix:semicolon
id|signal
c_func
(paren
id|SIGCHLD
comma
id|child_handler
)paren
suffix:semicolon
id|sockfd
op_assign
id|socket
c_func
(paren
id|PF_INET
comma
id|SOCK_STREAM
comma
id|IPPROTO_IP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sockfd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to open socket (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|addr
comma
l_int|0
comma
r_sizeof
(paren
id|addr
)paren
)paren
suffix:semicolon
id|addr.sin_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|addr.sin_family
op_assign
id|AF_INET
suffix:semicolon
r_if
c_cond
(paren
id|bind
c_func
(paren
id|sockfd
comma
(paren
r_void
op_star
)paren
op_amp
id|addr
comma
r_sizeof
(paren
id|addr
)paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to bind to port %d (%s)&quot;
comma
id|port
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|listen
c_func
(paren
id|sockfd
comma
l_int|5
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to listen to port %d (%s)&quot;
comma
id|port
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|sockaddr_in
id|in
suffix:semicolon
id|socklen_t
id|addrlen
op_assign
r_sizeof
(paren
id|in
)paren
suffix:semicolon
r_int
id|incoming
op_assign
id|accept
c_func
(paren
id|sockfd
comma
(paren
r_void
op_star
)paren
op_amp
id|in
comma
op_amp
id|addrlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|incoming
OL
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|errno
)paren
(brace
r_case
id|EAGAIN
suffix:colon
r_case
id|EINTR
suffix:colon
r_case
id|ECONNABORTED
suffix:colon
r_continue
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;accept returned %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
)brace
id|handle
c_func
(paren
id|incoming
comma
op_amp
id|in
comma
id|addrlen
)paren
suffix:semicolon
)brace
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
id|port
op_assign
id|DEFAULT_GIT_PORT
suffix:semicolon
r_int
id|inetd_mode
op_assign
l_int|0
suffix:semicolon
r_int
id|i
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
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--port=&quot;
comma
l_int|7
)paren
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
id|n
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|7
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|7
)braket
op_logical_and
op_logical_neg
op_star
id|end
)paren
(brace
id|port
op_assign
id|n
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--inetd&quot;
)paren
)paren
(brace
id|inetd_mode
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|daemon_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inetd_mode
)paren
r_return
id|execute
c_func
(paren
)paren
suffix:semicolon
r_return
id|serve
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
eof
