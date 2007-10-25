macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|variable|server_capabilities
r_static
r_char
op_star
id|server_capabilities
suffix:semicolon
DECL|function|check_ref
r_static
r_int
id|check_ref
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|flags
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|5
op_logical_or
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Skip the &quot;refs/&quot; part */
id|name
op_add_assign
l_int|5
suffix:semicolon
id|len
op_sub_assign
l_int|5
suffix:semicolon
multiline_comment|/* REF_NORMAL means that we don&squot;t want the magic fake tag refs */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|REF_NORMAL
)paren
op_logical_and
id|check_ref_format
c_func
(paren
id|name
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* REF_HEADS means that we want regular branch heads */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|REF_HEADS
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;heads/&quot;
comma
l_int|6
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* REF_TAGS means that we want tags */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|REF_TAGS
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;tags/&quot;
comma
l_int|5
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* All type bits clear means that we are ok with anything */
r_return
op_logical_neg
(paren
id|flags
op_amp
op_complement
id|REF_NORMAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read all the refs from the other end&n; */
DECL|function|get_remote_heads
r_struct
id|ref
op_star
op_star
id|get_remote_heads
c_func
(paren
r_int
id|in
comma
r_struct
id|ref
op_star
op_star
id|list
comma
r_int
id|nr_match
comma
r_char
op_star
op_star
id|match
comma
r_int
r_int
id|flags
)paren
(brace
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_static
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|len
comma
id|name_len
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
id|in
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
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
id|buffer
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buffer
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
id|buffer
comma
id|old_sha1
)paren
op_logical_or
id|buffer
(braket
l_int|40
)braket
op_ne
l_char|&squot; &squot;
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: expected sha/ref, got &squot;%s&squot;&quot;
comma
id|buffer
)paren
suffix:semicolon
id|name
op_assign
id|buffer
op_plus
l_int|41
suffix:semicolon
id|name_len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
id|name_len
op_plus
l_int|41
)paren
(brace
r_if
c_cond
(paren
id|server_capabilities
)paren
id|free
c_func
(paren
id|server_capabilities
)paren
suffix:semicolon
id|server_capabilities
op_assign
id|xstrdup
c_func
(paren
id|name
op_plus
id|name_len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|check_ref
c_func
(paren
id|name
comma
id|name_len
comma
id|flags
)paren
)paren
r_continue
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
id|name
comma
id|nr_match
comma
id|match
)paren
)paren
r_continue
suffix:semicolon
id|ref
op_assign
id|alloc_ref
c_func
(paren
id|name_len
op_plus
l_int|1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ref-&gt;old_sha1
comma
id|old_sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;name
comma
id|buffer
op_plus
l_int|41
comma
id|name_len
op_plus
l_int|1
)paren
suffix:semicolon
op_star
id|list
op_assign
id|ref
suffix:semicolon
id|list
op_assign
op_amp
id|ref-&gt;next
suffix:semicolon
)brace
r_return
id|list
suffix:semicolon
)brace
DECL|function|server_supports
r_int
id|server_supports
c_func
(paren
r_const
r_char
op_star
id|feature
)paren
(brace
r_return
id|server_capabilities
op_logical_and
id|strstr
c_func
(paren
id|server_capabilities
comma
id|feature
)paren
op_ne
l_int|NULL
suffix:semicolon
)brace
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
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;ACK &quot;
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
(brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;continue&quot;
)paren
)paren
r_return
l_int|2
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
(paren
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|enum|protocol
r_enum
id|protocol
(brace
DECL|enumerator|PROTO_LOCAL
id|PROTO_LOCAL
op_assign
l_int|1
comma
DECL|enumerator|PROTO_SSH
id|PROTO_SSH
comma
DECL|enumerator|PROTO_GIT
id|PROTO_GIT
comma
)brace
suffix:semicolon
DECL|function|get_protocol
r_static
r_enum
id|protocol
id|get_protocol
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ssh&quot;
)paren
)paren
r_return
id|PROTO_SSH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;git&quot;
)paren
)paren
r_return
id|PROTO_GIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;git+ssh&quot;
)paren
)paren
r_return
id|PROTO_SSH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ssh+git&quot;
)paren
)paren
r_return
id|PROTO_SSH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;file&quot;
)paren
)paren
r_return
id|PROTO_LOCAL
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;I don&squot;t handle protocol &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|macro|STR_
mdefine_line|#define STR_(s)&t;# s
DECL|macro|STR
mdefine_line|#define STR(s)&t;STR_(s)
macro_line|#ifndef NO_IPV6
DECL|function|ai_name
r_static
r_const
r_char
op_star
id|ai_name
c_func
(paren
r_const
r_struct
id|addrinfo
op_star
id|ai
)paren
(brace
r_static
r_char
id|addr
(braket
id|INET_ADDRSTRLEN
)braket
suffix:semicolon
r_if
c_cond
(paren
id|AF_INET
op_eq
id|ai-&gt;ai_family
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|in
suffix:semicolon
id|in
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
id|ai-&gt;ai_addr
suffix:semicolon
id|inet_ntop
c_func
(paren
id|ai-&gt;ai_family
comma
op_amp
id|in-&gt;sin_addr
comma
id|addr
comma
r_sizeof
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|AF_INET6
op_eq
id|ai-&gt;ai_family
)paren
(brace
r_struct
id|sockaddr_in6
op_star
id|in
suffix:semicolon
id|in
op_assign
(paren
r_struct
id|sockaddr_in6
op_star
)paren
id|ai-&gt;ai_addr
suffix:semicolon
id|inet_ntop
c_func
(paren
id|ai-&gt;ai_family
comma
op_amp
id|in-&gt;sin6_addr
comma
id|addr
comma
r_sizeof
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|addr
comma
l_string|&quot;(unknown)&quot;
)paren
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns a connected socket() fd, or else die()s.&n; */
DECL|function|git_tcp_connect_sock
r_static
r_int
id|git_tcp_connect_sock
c_func
(paren
r_char
op_star
id|host
comma
r_int
id|flags
)paren
(brace
r_int
id|sockfd
op_assign
l_int|1
comma
id|saved_errno
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|colon
comma
op_star
id|end
suffix:semicolon
r_const
r_char
op_star
id|port
op_assign
id|STR
c_func
(paren
id|DEFAULT_GIT_PORT
)paren
suffix:semicolon
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
id|cnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|host
(braket
l_int|0
)braket
op_eq
l_char|&squot;[&squot;
)paren
(brace
id|end
op_assign
id|strchr
c_func
(paren
id|host
op_plus
l_int|1
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
(brace
op_star
id|end
op_assign
l_int|0
suffix:semicolon
id|end
op_increment
suffix:semicolon
id|host
op_increment
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|end
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
id|port
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|port
)paren
id|port
op_assign
l_string|&quot;&lt;none&gt;&quot;
suffix:semicolon
)brace
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
id|hints.ai_socktype
op_assign
id|SOCK_STREAM
suffix:semicolon
id|hints.ai_protocol
op_assign
id|IPPROTO_TCP
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Looking up %s ... &quot;
comma
id|host
)paren
suffix:semicolon
id|gai
op_assign
id|getaddrinfo
c_func
(paren
id|host
comma
id|port
comma
op_amp
id|hints
comma
op_amp
id|ai
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
l_string|&quot;Unable to look up %s (port %s) (%s)&quot;
comma
id|host
comma
id|port
comma
id|gai_strerror
c_func
(paren
id|gai
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;done.&bslash;nConnecting to %s (port %s) ... &quot;
comma
id|host
comma
id|port
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ai0
op_assign
id|ai
suffix:semicolon
id|ai
suffix:semicolon
id|ai
op_assign
id|ai-&gt;ai_next
)paren
(brace
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
(brace
id|saved_errno
op_assign
id|errno
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|connect
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
id|saved_errno
op_assign
id|errno
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s[%d: %s]: errno=%s&bslash;n&quot;
comma
id|host
comma
id|cnt
comma
id|ai_name
c_func
(paren
id|ai
)paren
comma
id|strerror
c_func
(paren
id|saved_errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|sockfd
)paren
suffix:semicolon
id|sockfd
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s &quot;
comma
id|ai_name
c_func
(paren
id|ai
)paren
)paren
suffix:semicolon
r_break
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
id|sockfd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to connect a socket (%s)&quot;
comma
id|strerror
c_func
(paren
id|saved_errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|sockfd
suffix:semicolon
)brace
macro_line|#else /* NO_IPV6 */
multiline_comment|/*&n; * Returns a connected socket() fd, or else die()s.&n; */
DECL|function|git_tcp_connect_sock
r_static
r_int
id|git_tcp_connect_sock
c_func
(paren
r_char
op_star
id|host
comma
r_int
id|flags
)paren
(brace
r_int
id|sockfd
op_assign
l_int|1
comma
id|saved_errno
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|colon
comma
op_star
id|end
suffix:semicolon
r_char
op_star
id|port
op_assign
id|STR
c_func
(paren
id|DEFAULT_GIT_PORT
)paren
comma
op_star
id|ep
suffix:semicolon
r_struct
id|hostent
op_star
id|he
suffix:semicolon
r_struct
id|sockaddr_in
id|sa
suffix:semicolon
r_char
op_star
op_star
id|ap
suffix:semicolon
r_int
r_int
id|nport
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|host
(braket
l_int|0
)braket
op_eq
l_char|&squot;[&squot;
)paren
(brace
id|end
op_assign
id|strchr
c_func
(paren
id|host
op_plus
l_int|1
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
(brace
op_star
id|end
op_assign
l_int|0
suffix:semicolon
id|end
op_increment
suffix:semicolon
id|host
op_increment
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|end
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
id|port
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Looking up %s ... &quot;
comma
id|host
)paren
suffix:semicolon
id|he
op_assign
id|gethostbyname
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|he
)paren
id|die
c_func
(paren
l_string|&quot;Unable to look up %s (%s)&quot;
comma
id|host
comma
id|hstrerror
c_func
(paren
id|h_errno
)paren
)paren
suffix:semicolon
id|nport
op_assign
id|strtoul
c_func
(paren
id|port
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
op_eq
id|port
op_logical_or
op_star
id|ep
)paren
(brace
multiline_comment|/* Not numeric */
r_struct
id|servent
op_star
id|se
op_assign
id|getservbyname
c_func
(paren
id|port
comma
l_string|&quot;tcp&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|se
)paren
id|die
c_func
(paren
l_string|&quot;Unknown port %s&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|nport
op_assign
id|se-&gt;s_port
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;done.&bslash;nConnecting to %s (port %s) ... &quot;
comma
id|host
comma
id|port
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
comma
id|ap
op_assign
id|he-&gt;h_addr_list
suffix:semicolon
op_star
id|ap
suffix:semicolon
id|ap
op_increment
comma
id|cnt
op_increment
)paren
(brace
id|sockfd
op_assign
id|socket
c_func
(paren
id|he-&gt;h_addrtype
comma
id|SOCK_STREAM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sockfd
OL
l_int|0
)paren
(brace
id|saved_errno
op_assign
id|errno
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|sa
comma
l_int|0
comma
r_sizeof
id|sa
)paren
suffix:semicolon
id|sa.sin_family
op_assign
id|he-&gt;h_addrtype
suffix:semicolon
id|sa.sin_port
op_assign
id|htons
c_func
(paren
id|nport
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sa.sin_addr
comma
op_star
id|ap
comma
id|he-&gt;h_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|connect
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
id|sa
comma
r_sizeof
id|sa
)paren
OL
l_int|0
)paren
(brace
id|saved_errno
op_assign
id|errno
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s[%d: %s]: errno=%s&bslash;n&quot;
comma
id|host
comma
id|cnt
comma
id|inet_ntoa
c_func
(paren
op_star
(paren
r_struct
id|in_addr
op_star
)paren
op_amp
id|sa.sin_addr
)paren
comma
id|strerror
c_func
(paren
id|saved_errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|sockfd
)paren
suffix:semicolon
id|sockfd
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s &quot;
comma
id|inet_ntoa
c_func
(paren
op_star
(paren
r_struct
id|in_addr
op_star
)paren
op_amp
id|sa.sin_addr
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
l_string|&quot;unable to connect a socket (%s)&quot;
comma
id|strerror
c_func
(paren
id|saved_errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CONNECT_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|sockfd
suffix:semicolon
)brace
macro_line|#endif /* NO_IPV6 */
DECL|function|git_tcp_connect
r_static
r_void
id|git_tcp_connect
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
id|host
comma
r_int
id|flags
)paren
(brace
r_int
id|sockfd
op_assign
id|git_tcp_connect_sock
c_func
(paren
id|host
comma
id|flags
)paren
suffix:semicolon
id|fd
(braket
l_int|0
)braket
op_assign
id|sockfd
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
id|dup
c_func
(paren
id|sockfd
)paren
suffix:semicolon
)brace
DECL|variable|git_proxy_command
r_static
r_char
op_star
id|git_proxy_command
suffix:semicolon
DECL|variable|rhost_name
r_static
r_const
r_char
op_star
id|rhost_name
suffix:semicolon
DECL|variable|rhost_len
r_static
r_int
id|rhost_len
suffix:semicolon
DECL|function|git_proxy_command_options
r_static
r_int
id|git_proxy_command_options
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.gitproxy&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|for_pos
suffix:semicolon
r_int
id|matchlen
op_assign
l_int|1
suffix:semicolon
r_int
id|hostlen
suffix:semicolon
r_if
c_cond
(paren
id|git_proxy_command
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* [core]&n;&t;&t; * ;# matches www.kernel.org as well&n;&t;&t; * gitproxy = netcatter-1 for kernel.org&n;&t;&t; * gitproxy = netcatter-2 for sample.xz&n;&t;&t; * gitproxy = netcatter-default&n;&t;&t; */
id|for_pos
op_assign
id|strstr
c_func
(paren
id|value
comma
l_string|&quot; for &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|for_pos
)paren
multiline_comment|/* matches everybody */
id|matchlen
op_assign
id|strlen
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
(brace
id|hostlen
op_assign
id|strlen
c_func
(paren
id|for_pos
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rhost_len
OL
id|hostlen
)paren
id|matchlen
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|for_pos
op_plus
l_int|5
comma
id|rhost_name
op_plus
id|rhost_len
id|hostlen
comma
id|hostlen
)paren
op_logical_and
(paren
(paren
id|rhost_len
op_eq
id|hostlen
)paren
op_logical_or
id|rhost_name
(braket
id|rhost_len
id|hostlen
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
)paren
id|matchlen
op_assign
id|for_pos
id|value
suffix:semicolon
r_else
id|matchlen
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|matchlen
)paren
(brace
multiline_comment|/* core.gitproxy = none for kernel.org */
r_if
c_cond
(paren
id|matchlen
op_eq
l_int|4
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|value
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
)paren
id|matchlen
op_assign
l_int|0
suffix:semicolon
id|git_proxy_command
op_assign
id|xmemdupz
c_func
(paren
id|value
comma
id|matchlen
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|git_use_proxy
r_static
r_int
id|git_use_proxy
c_func
(paren
r_const
r_char
op_star
id|host
)paren
(brace
id|rhost_name
op_assign
id|host
suffix:semicolon
id|rhost_len
op_assign
id|strlen
c_func
(paren
id|host
)paren
suffix:semicolon
id|git_proxy_command
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_PROXY_COMMAND&quot;
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_proxy_command_options
)paren
suffix:semicolon
id|rhost_name
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|git_proxy_command
op_logical_and
op_star
id|git_proxy_command
)paren
suffix:semicolon
)brace
DECL|function|git_proxy_connect
r_static
r_void
id|git_proxy_connect
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
id|host
)paren
(brace
r_const
r_char
op_star
id|port
op_assign
id|STR
c_func
(paren
id|DEFAULT_GIT_PORT
)paren
suffix:semicolon
r_char
op_star
id|colon
comma
op_star
id|end
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|child_process
id|proxy
suffix:semicolon
r_if
c_cond
(paren
id|host
(braket
l_int|0
)braket
op_eq
l_char|&squot;[&squot;
)paren
(brace
id|end
op_assign
id|strchr
c_func
(paren
id|host
op_plus
l_int|1
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
(brace
op_star
id|end
op_assign
l_int|0
suffix:semicolon
id|end
op_increment
suffix:semicolon
id|host
op_increment
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|end
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
id|port
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
)brace
id|argv
(braket
l_int|0
)braket
op_assign
id|git_proxy_command
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
id|host
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
id|port
suffix:semicolon
id|argv
(braket
l_int|3
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|proxy
comma
l_int|0
comma
r_sizeof
(paren
id|proxy
)paren
)paren
suffix:semicolon
id|proxy.argv
op_assign
id|argv
suffix:semicolon
id|proxy.in
op_assign
l_int|1
suffix:semicolon
id|proxy.out
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|proxy
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot start proxy %s&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|fd
(braket
l_int|0
)braket
op_assign
id|proxy.out
suffix:semicolon
multiline_comment|/* read from proxy stdout */
id|fd
(braket
l_int|1
)braket
op_assign
id|proxy.in
suffix:semicolon
multiline_comment|/* write to proxy stdin */
)brace
DECL|macro|MAX_CMD_LEN
mdefine_line|#define MAX_CMD_LEN 1024
DECL|function|get_port
r_char
op_star
id|get_port
c_func
(paren
r_char
op_star
id|host
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_char
op_star
id|p
op_assign
id|strchr
c_func
(paren
id|host
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|strtol
c_func
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|p
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * This returns 0 if the transport protocol does not need fork(2),&n; * or a process id if it does.  Once done, finish the connection&n; * with finish_connect() with the value returned from this function&n; * (it is safe to call finish_connect() with 0 to support the former&n; * case).&n; *&n; * Does not return a negative value on error; it just dies.&n; */
DECL|function|git_connect
id|pid_t
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
comma
r_int
id|flags
)paren
(brace
r_char
op_star
id|host
comma
op_star
id|path
op_assign
id|url
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
id|c
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
r_enum
id|protocol
id|protocol
op_assign
id|PROTO_LOCAL
suffix:semicolon
r_int
id|free_path
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|port
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Without this we cannot rely on waitpid() to tell&n;&t; * what happened to our children.&n;&t; */
id|signal
c_func
(paren
id|SIGCHLD
comma
id|SIG_DFL
)paren
suffix:semicolon
id|host
op_assign
id|strstr
c_func
(paren
id|url
comma
l_string|&quot;://&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host
)paren
(brace
op_star
id|host
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|protocol
op_assign
id|get_protocol
c_func
(paren
id|url
)paren
suffix:semicolon
id|host
op_add_assign
l_int|3
suffix:semicolon
id|c
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
(brace
id|host
op_assign
id|url
suffix:semicolon
id|c
op_assign
l_char|&squot;:&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host
(braket
l_int|0
)braket
op_eq
l_char|&squot;[&squot;
)paren
(brace
id|end
op_assign
id|strchr
c_func
(paren
id|host
op_plus
l_int|1
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
)paren
(brace
op_star
id|end
op_assign
l_int|0
suffix:semicolon
id|end
op_increment
suffix:semicolon
id|host
op_increment
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
)brace
r_else
id|end
op_assign
id|host
suffix:semicolon
id|path
op_assign
id|strchr
c_func
(paren
id|end
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|protocol
op_assign
id|PROTO_SSH
suffix:semicolon
op_star
id|path
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
r_else
id|path
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
op_logical_neg
op_star
id|path
)paren
id|die
c_func
(paren
l_string|&quot;No path specified. See &squot;man git-pull&squot; for valid url syntax&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * null-terminate hostname and point path to ~ for URL&squot;s like this:&n;&t; *    ssh://host.xz/~user/repo&n;&t; */
r_if
c_cond
(paren
id|protocol
op_ne
id|PROTO_LOCAL
op_logical_and
id|host
op_ne
id|url
)paren
(brace
r_char
op_star
id|ptr
op_assign
id|path
suffix:semicolon
r_if
c_cond
(paren
id|path
(braket
l_int|1
)braket
op_eq
l_char|&squot;~&squot;
)paren
id|path
op_increment
suffix:semicolon
r_else
(brace
id|path
op_assign
id|xstrdup
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|free_path
op_assign
l_int|1
suffix:semicolon
)brace
op_star
id|ptr
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Add support for ssh port: ssh://host.xy:&lt;port&gt;/...&n;&t; */
r_if
c_cond
(paren
id|protocol
op_eq
id|PROTO_SSH
op_logical_and
id|host
op_ne
id|url
)paren
id|port
op_assign
id|get_port
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_eq
id|PROTO_GIT
)paren
(brace
multiline_comment|/* These underlying connection commands die() if they&n;&t;&t; * cannot connect.&n;&t;&t; */
r_char
op_star
id|target_host
op_assign
id|xstrdup
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_use_proxy
c_func
(paren
id|host
)paren
)paren
id|git_proxy_connect
c_func
(paren
id|fd
comma
id|host
)paren
suffix:semicolon
r_else
id|git_tcp_connect
c_func
(paren
id|fd
comma
id|host
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Separate original protocol components prog and path&n;&t;&t; * from extended components with a NUL byte.&n;&t;&t; */
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;%s %s%chost=%s%c&quot;
comma
id|prog
comma
id|path
comma
l_int|0
comma
id|target_host
comma
l_int|0
)paren
suffix:semicolon
id|free
c_func
(paren
id|target_host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_path
)paren
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to fork&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_struct
id|strbuf
id|cmd
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|cmd
comma
id|MAX_CMD_LEN
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|cmd
comma
id|prog
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|cmd
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|sq_quote_buf
c_func
(paren
op_amp
id|cmd
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd.len
op_ge
id|MAX_CMD_LEN
)paren
id|die
c_func
(paren
l_string|&quot;command line too long&quot;
)paren
suffix:semicolon
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
id|protocol
op_eq
id|PROTO_SSH
)paren
(brace
r_const
r_char
op_star
id|ssh
comma
op_star
id|ssh_basename
suffix:semicolon
id|ssh
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSH&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ssh
)paren
id|ssh
op_assign
l_string|&quot;ssh&quot;
suffix:semicolon
id|ssh_basename
op_assign
id|strrchr
c_func
(paren
id|ssh
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ssh_basename
)paren
id|ssh_basename
op_assign
id|ssh
suffix:semicolon
r_else
id|ssh_basename
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
id|execlp
c_func
(paren
id|ssh
comma
id|ssh_basename
comma
id|host
comma
id|cmd.buf
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|execlp
c_func
(paren
id|ssh
comma
id|ssh_basename
comma
l_string|&quot;-p&quot;
comma
id|port
comma
id|host
comma
id|cmd.buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
id|unsetenv
c_func
(paren
id|ALTERNATE_DB_ENVIRONMENT
)paren
suffix:semicolon
id|unsetenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
suffix:semicolon
id|unsetenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
id|unsetenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
)paren
suffix:semicolon
id|unsetenv
c_func
(paren
id|GRAFT_ENVIRONMENT
)paren
suffix:semicolon
id|unsetenv
c_func
(paren
id|INDEX_ENVIRONMENT
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;sh&quot;
comma
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
id|cmd.buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|free_path
)paren
id|free
c_func
(paren
id|path
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
r_if
c_cond
(paren
id|pid
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
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
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
