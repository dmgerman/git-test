macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;netdb.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;arpa/inet.h&gt;
macro_line|#include &lt;syslog.h&gt;
DECL|variable|log_syslog
r_static
r_int
id|log_syslog
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|variable|daemon_usage
r_static
r_const
r_char
id|daemon_usage
(braket
)braket
op_assign
l_string|&quot;git-daemon [--verbose] [--syslog] [--inetd | --port=n]&quot;
suffix:semicolon
DECL|function|logreport
r_static
r_void
id|logreport
c_func
(paren
r_int
id|priority
comma
r_const
r_char
op_star
id|err
comma
id|va_list
id|params
)paren
(brace
multiline_comment|/* We should do a single write so that it is atomic and output&n;&t; * of several processes do not get intermingled. */
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|buflen
suffix:semicolon
r_int
id|maxlen
comma
id|msglen
suffix:semicolon
multiline_comment|/* sizeof(buf) should be big enough for &quot;[pid] &bslash;n&quot; */
id|buflen
op_assign
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;[%ld] &quot;
comma
(paren
r_int
)paren
id|getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|maxlen
op_assign
r_sizeof
(paren
id|buf
)paren
id|buflen
l_int|1
suffix:semicolon
multiline_comment|/* -1 for our own LF */
id|msglen
op_assign
id|vsnprintf
c_func
(paren
id|buf
op_plus
id|buflen
comma
id|maxlen
comma
id|err
comma
id|params
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_syslog
)paren
(brace
id|syslog
c_func
(paren
id|priority
comma
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* maxlen counted our own LF but also counts space given to&n;&t; * vsnprintf for the terminating NUL.  We want to make sure that&n;&t; * we have space for our own LF and NUL after the &quot;meat&quot; of the&n;&t; * message, so truncate it at maxlen - 1.&n;&t; */
r_if
c_cond
(paren
id|msglen
OG
id|maxlen
l_int|1
)paren
id|msglen
op_assign
id|maxlen
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|msglen
OL
l_int|0
)paren
id|msglen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Protect against weird return values. */
id|buflen
op_add_assign
id|msglen
suffix:semicolon
id|buf
(braket
id|buflen
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|buflen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|write
c_func
(paren
l_int|2
comma
id|buf
comma
id|buflen
)paren
suffix:semicolon
)brace
DECL|function|logerror
r_void
id|logerror
c_func
(paren
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
id|logreport
c_func
(paren
id|LOG_ERR
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
)brace
DECL|function|lognotice
r_void
id|lognotice
c_func
(paren
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose
)paren
r_return
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
id|logreport
c_func
(paren
id|LOG_INFO
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
)brace
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
id|lognotice
c_func
(paren
l_string|&quot;Request for &squot;%s&squot;&quot;
comma
id|dir
)paren
suffix:semicolon
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
(brace
id|logerror
c_func
(paren
l_string|&quot;Cannot chdir(&squot;%s&squot;): %s&quot;
comma
id|dir
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
(brace
id|logerror
c_func
(paren
l_string|&quot;Not a valid gitd-enabled repository: &squot;%s&squot;&quot;
comma
id|dir
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We&squot;ll ignore SIGTERM from now on, we have a&n;&t; * good client.&n;&t; */
id|signal
c_func
(paren
id|SIGTERM
comma
id|SIG_IGN
)paren
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
id|logerror
c_func
(paren
l_string|&quot;Protocol error: &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * We count spawned/reaped separately, just to avoid any&n; * races when updating them from signals. The SIGCHLD handler&n; * will only update children_reaped, and the fork logic will&n; * only update children_spawned.&n; *&n; * MAX_CHILDREN should be a power-of-two to make the modulus&n; * operation cheap. It should also be at least twice&n; * the maximum number of connections we will ever allow.&n; */
DECL|macro|MAX_CHILDREN
mdefine_line|#define MAX_CHILDREN 128
DECL|variable|max_connections
r_static
r_int
id|max_connections
op_assign
l_int|25
suffix:semicolon
multiline_comment|/* These are updated by the signal handler */
DECL|variable|children_reaped
r_static
r_volatile
r_int
r_int
id|children_reaped
op_assign
l_int|0
suffix:semicolon
DECL|variable|dead_child
r_static
id|pid_t
id|dead_child
(braket
id|MAX_CHILDREN
)braket
suffix:semicolon
multiline_comment|/* These are updated by the main loop */
DECL|variable|children_spawned
r_static
r_int
r_int
id|children_spawned
op_assign
l_int|0
suffix:semicolon
DECL|variable|children_deleted
r_static
r_int
r_int
id|children_deleted
op_assign
l_int|0
suffix:semicolon
DECL|struct|child
r_static
r_struct
id|child
(brace
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|addrlen
r_int
id|addrlen
suffix:semicolon
DECL|member|address
r_struct
id|sockaddr_storage
id|address
suffix:semicolon
DECL|variable|live_child
)brace
id|live_child
(braket
id|MAX_CHILDREN
)braket
suffix:semicolon
DECL|function|add_child
r_static
r_void
id|add_child
c_func
(paren
r_int
id|idx
comma
id|pid_t
id|pid
comma
r_struct
id|sockaddr
op_star
id|addr
comma
r_int
id|addrlen
)paren
(brace
id|live_child
(braket
id|idx
)braket
dot
id|pid
op_assign
id|pid
suffix:semicolon
id|live_child
(braket
id|idx
)braket
dot
id|addrlen
op_assign
id|addrlen
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|live_child
(braket
id|idx
)braket
dot
id|address
comma
id|addr
comma
id|addrlen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Walk from &quot;deleted&quot; to &quot;spawned&quot;, and remove child &quot;pid&quot;.&n; *&n; * We move everything up by one, since the new &quot;deleted&quot; will&n; * be one higher.&n; */
DECL|function|remove_child
r_static
r_void
id|remove_child
c_func
(paren
id|pid_t
id|pid
comma
r_int
id|deleted
comma
r_int
id|spawned
)paren
(brace
r_struct
id|child
id|n
suffix:semicolon
id|deleted
op_mod_assign
id|MAX_CHILDREN
suffix:semicolon
id|spawned
op_mod_assign
id|MAX_CHILDREN
suffix:semicolon
r_if
c_cond
(paren
id|live_child
(braket
id|deleted
)braket
dot
id|pid
op_eq
id|pid
)paren
(brace
id|live_child
(braket
id|deleted
)braket
dot
id|pid
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n
op_assign
id|live_child
(braket
id|deleted
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|child
id|m
suffix:semicolon
id|deleted
op_assign
(paren
id|deleted
op_plus
l_int|1
)paren
op_mod
id|MAX_CHILDREN
suffix:semicolon
r_if
c_cond
(paren
id|deleted
op_eq
id|spawned
)paren
id|die
c_func
(paren
l_string|&quot;could not find dead child %d&bslash;n&quot;
comma
id|pid
)paren
suffix:semicolon
id|m
op_assign
id|live_child
(braket
id|deleted
)braket
suffix:semicolon
id|live_child
(braket
id|deleted
)braket
op_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|m.pid
op_eq
id|pid
)paren
r_return
suffix:semicolon
id|n
op_assign
id|m
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This gets called if the number of connections grows&n; * past &quot;max_connections&quot;.&n; *&n; * We _should_ start off by searching for connections&n; * from the same IP, and if there is some address wth&n; * multiple connections, we should kill that first.&n; *&n; * As it is, we just &quot;randomly&quot; kill 25% of the connections,&n; * and our pseudo-random generator sucks too. I have no&n; * shame.&n; *&n; * Really, this is just a place-holder for a _real_ algorithm.&n; */
DECL|function|kill_some_children
r_static
r_void
id|kill_some_children
c_func
(paren
r_int
id|signo
comma
r_int
id|start
comma
r_int
id|stop
)paren
(brace
id|start
op_mod_assign
id|MAX_CHILDREN
suffix:semicolon
id|stop
op_mod_assign
id|MAX_CHILDREN
suffix:semicolon
r_while
c_loop
(paren
id|start
op_ne
id|stop
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|start
op_amp
l_int|3
)paren
)paren
id|kill
c_func
(paren
id|live_child
(braket
id|start
)braket
dot
id|pid
comma
id|signo
)paren
suffix:semicolon
id|start
op_assign
(paren
id|start
op_plus
l_int|1
)paren
op_mod
id|MAX_CHILDREN
suffix:semicolon
)brace
)brace
DECL|function|check_max_connections
r_static
r_void
id|check_max_connections
c_func
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|active
suffix:semicolon
r_int
id|spawned
comma
id|reaped
comma
id|deleted
suffix:semicolon
id|spawned
op_assign
id|children_spawned
suffix:semicolon
id|reaped
op_assign
id|children_reaped
suffix:semicolon
id|deleted
op_assign
id|children_deleted
suffix:semicolon
r_while
c_loop
(paren
id|deleted
OL
id|reaped
)paren
(brace
id|pid_t
id|pid
op_assign
id|dead_child
(braket
id|deleted
op_mod
id|MAX_CHILDREN
)braket
suffix:semicolon
id|remove_child
c_func
(paren
id|pid
comma
id|deleted
comma
id|spawned
)paren
suffix:semicolon
id|deleted
op_increment
suffix:semicolon
)brace
id|children_deleted
op_assign
id|deleted
suffix:semicolon
id|active
op_assign
id|spawned
id|deleted
suffix:semicolon
r_if
c_cond
(paren
id|active
op_le
id|max_connections
)paren
r_break
suffix:semicolon
multiline_comment|/* Kill some unstarted connections with SIGTERM */
id|kill_some_children
c_func
(paren
id|SIGTERM
comma
id|deleted
comma
id|spawned
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active
op_le
id|max_connections
op_lshift
l_int|1
)paren
r_break
suffix:semicolon
multiline_comment|/* If the SIGTERM thing isn&squot;t helping use SIGKILL */
id|kill_some_children
c_func
(paren
id|SIGKILL
comma
id|deleted
comma
id|spawned
)paren
suffix:semicolon
id|sleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
id|sockaddr
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
r_char
id|addrbuf
(braket
l_int|256
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
id|port
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pid
)paren
(brace
r_int
id|idx
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
id|idx
op_assign
id|children_spawned
op_mod
id|MAX_CHILDREN
suffix:semicolon
id|children_spawned
op_increment
suffix:semicolon
id|add_child
c_func
(paren
id|idx
comma
id|pid
comma
id|addr
comma
id|addrlen
)paren
suffix:semicolon
id|check_max_connections
c_func
(paren
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|addr-&gt;sa_family
op_eq
id|AF_INET
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|sin_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
id|inet_ntop
c_func
(paren
id|AF_INET
comma
op_amp
id|sin_addr-&gt;sin_addr
comma
id|addrbuf
comma
r_sizeof
(paren
id|addrbuf
)paren
)paren
suffix:semicolon
id|port
op_assign
id|sin_addr-&gt;sin_port
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr-&gt;sa_family
op_eq
id|AF_INET6
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|sin6_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|addrbuf
suffix:semicolon
op_star
id|buf
op_increment
op_assign
l_char|&squot;[&squot;
suffix:semicolon
op_star
id|buf
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* stpcpy() is cool */
id|inet_ntop
c_func
(paren
id|AF_INET6
comma
op_amp
id|sin6_addr-&gt;sin6_addr
comma
id|buf
comma
r_sizeof
(paren
id|addrbuf
)paren
l_int|1
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;]&quot;
)paren
suffix:semicolon
id|port
op_assign
id|sin6_addr-&gt;sin6_port
suffix:semicolon
)brace
id|lognotice
c_func
(paren
l_string|&quot;Connection from %s:%d&quot;
comma
id|addrbuf
comma
id|port
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
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
op_assign
id|waitpid
c_func
(paren
l_int|1
comma
op_amp
id|status
comma
id|WNOHANG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OG
l_int|0
)paren
(brace
r_int
id|reaped
op_assign
id|children_reaped
suffix:semicolon
id|dead_child
(braket
id|reaped
op_mod
id|MAX_CHILDREN
)braket
op_assign
id|pid
suffix:semicolon
id|children_reaped
op_assign
id|reaped
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* XXX: Custom logging, since we don&squot;t wanna getpid() */
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_char
op_star
id|dead
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
OG
l_int|0
)paren
id|dead
op_assign
l_string|&quot; (with error)&quot;
suffix:semicolon
r_if
c_cond
(paren
id|log_syslog
)paren
id|syslog
c_func
(paren
id|LOG_INFO
comma
l_string|&quot;[%d] Disconnected%s&quot;
comma
id|pid
comma
id|dead
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;[%d] Disconnected%s&bslash;n&quot;
comma
id|pid
comma
id|dead
)paren
suffix:semicolon
)brace
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
r_struct
id|addrinfo
id|hints
comma
op_star
id|ai0
comma
op_star
id|ai
suffix:semicolon
r_int
id|gai
suffix:semicolon
r_int
id|socknum
op_assign
l_int|0
comma
op_star
id|socklist
op_assign
l_int|NULL
suffix:semicolon
r_int
id|maxfd
op_assign
l_int|1
suffix:semicolon
id|fd_set
id|fds_init
comma
id|fds
suffix:semicolon
r_char
id|pbuf
(braket
id|NI_MAXSERV
)braket
suffix:semicolon
id|signal
c_func
(paren
id|SIGCHLD
comma
id|child_handler
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|pbuf
comma
l_string|&quot;%d&quot;
comma
id|port
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hints
comma
l_int|0
comma
r_sizeof
(paren
id|hints
)paren
)paren
suffix:semicolon
id|hints.ai_family
op_assign
id|AF_UNSPEC
suffix:semicolon
id|hints.ai_socktype
op_assign
id|SOCK_STREAM
suffix:semicolon
id|hints.ai_protocol
op_assign
id|IPPROTO_TCP
suffix:semicolon
id|hints.ai_flags
op_assign
id|AI_PASSIVE
suffix:semicolon
id|gai
op_assign
id|getaddrinfo
c_func
(paren
l_int|NULL
comma
id|pbuf
comma
op_amp
id|hints
comma
op_amp
id|ai0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gai
)paren
id|die
c_func
(paren
l_string|&quot;getaddrinfo() failed: %s&bslash;n&quot;
comma
id|gai_strerror
c_func
(paren
id|gai
)paren
)paren
suffix:semicolon
id|FD_ZERO
c_func
(paren
op_amp
id|fds_init
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ai
op_assign
id|ai0
suffix:semicolon
id|ai
suffix:semicolon
id|ai
op_assign
id|ai-&gt;ai_next
)paren
(brace
r_int
id|sockfd
suffix:semicolon
r_int
op_star
id|newlist
suffix:semicolon
id|sockfd
op_assign
id|socket
c_func
(paren
id|ai-&gt;ai_family
comma
id|ai-&gt;ai_socktype
comma
id|ai-&gt;ai_protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sockfd
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sockfd
op_ge
id|FD_SETSIZE
)paren
(brace
id|error
c_func
(paren
l_string|&quot;too large socket descriptor.&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|sockfd
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#ifdef IPV6_V6ONLY
r_if
c_cond
(paren
id|ai-&gt;ai_family
op_eq
id|AF_INET6
)paren
(brace
r_int
id|on
op_assign
l_int|1
suffix:semicolon
id|setsockopt
c_func
(paren
id|sockfd
comma
id|IPPROTO_IPV6
comma
id|IPV6_V6ONLY
comma
op_amp
id|on
comma
r_sizeof
(paren
id|on
)paren
)paren
suffix:semicolon
multiline_comment|/* Note: error is not fatal */
)brace
macro_line|#endif
r_if
c_cond
(paren
id|bind
c_func
(paren
id|sockfd
comma
id|ai-&gt;ai_addr
comma
id|ai-&gt;ai_addrlen
)paren
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|sockfd
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* not fatal */
)brace
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
(brace
id|close
c_func
(paren
id|sockfd
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* not fatal */
)brace
id|newlist
op_assign
id|realloc
c_func
(paren
id|socklist
comma
r_sizeof
(paren
r_int
)paren
op_star
(paren
id|socknum
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newlist
)paren
id|die
c_func
(paren
l_string|&quot;memory allocation failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|socklist
op_assign
id|newlist
suffix:semicolon
id|socklist
(braket
id|socknum
op_increment
)braket
op_assign
id|sockfd
suffix:semicolon
id|FD_SET
c_func
(paren
id|sockfd
comma
op_amp
id|fds_init
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxfd
OL
id|sockfd
)paren
id|maxfd
op_assign
id|sockfd
suffix:semicolon
)brace
id|freeaddrinfo
c_func
(paren
id|ai0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|socknum
op_eq
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to allocate any listen sockets on port %u&quot;
comma
id|port
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|i
suffix:semicolon
id|fds
op_assign
id|fds_init
suffix:semicolon
r_if
c_cond
(paren
id|select
c_func
(paren
id|maxfd
op_plus
l_int|1
comma
op_amp
id|fds
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
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
(brace
id|error
c_func
(paren
l_string|&quot;select failed, resuming: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|sleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|socknum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|sockfd
op_assign
id|socklist
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|FD_ISSET
c_func
(paren
id|sockfd
comma
op_amp
id|fds
)paren
)paren
(brace
r_struct
id|sockaddr_storage
id|ss
suffix:semicolon
r_int
id|sslen
op_assign
r_sizeof
(paren
id|ss
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
r_struct
id|sockaddr
op_star
)paren
op_amp
id|ss
comma
op_amp
id|sslen
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
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|ss
comma
id|sslen
)paren
suffix:semicolon
)brace
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--verbose&quot;
)paren
)paren
(brace
id|verbose
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
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
l_string|&quot;--syslog&quot;
)paren
)paren
(brace
id|log_syslog
op_assign
l_int|1
suffix:semicolon
id|openlog
c_func
(paren
l_string|&quot;git-daemon&quot;
comma
l_int|0
comma
id|LOG_DAEMON
)paren
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
(brace
id|fclose
c_func
(paren
id|stderr
)paren
suffix:semicolon
singleline_comment|//FIXME: workaround
r_return
id|execute
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|serve
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
eof
