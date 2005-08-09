macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;arpa/inet.h&gt;
macro_line|#include &lt;netdb.h&gt;
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
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ref
)paren
op_plus
id|len
l_int|40
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;old_sha1
comma
id|old_sha1
comma
l_int|20
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
id|len
l_int|40
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
DECL|struct|refspec
r_struct
id|refspec
(brace
DECL|member|src
r_char
op_star
id|src
suffix:semicolon
DECL|member|dst
r_char
op_star
id|dst
suffix:semicolon
)brace
suffix:semicolon
DECL|function|parse_ref_spec
r_static
r_struct
id|refspec
op_star
id|parse_ref_spec
c_func
(paren
r_int
id|nr_refspec
comma
r_char
op_star
op_star
id|refspec
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|refspec
op_star
id|rs
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rs
)paren
op_star
(paren
id|nr_refspec
op_plus
l_int|1
)paren
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
id|nr_refspec
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|sp
comma
op_star
id|dp
comma
op_star
id|ep
suffix:semicolon
id|sp
op_assign
id|refspec
(braket
id|i
)braket
suffix:semicolon
id|ep
op_assign
id|strchr
c_func
(paren
id|sp
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
(brace
id|dp
op_assign
id|ep
op_plus
l_int|1
suffix:semicolon
op_star
id|ep
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|dp
op_assign
id|sp
suffix:semicolon
id|rs
(braket
id|i
)braket
dot
id|src
op_assign
id|sp
suffix:semicolon
id|rs
(braket
id|i
)braket
dot
id|dst
op_assign
id|dp
suffix:semicolon
)brace
id|rs
(braket
id|nr_refspec
)braket
dot
id|src
op_assign
id|rs
(braket
id|nr_refspec
)braket
dot
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_return
id|rs
suffix:semicolon
)brace
DECL|function|count_refspec_match
r_static
r_int
id|count_refspec_match
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_struct
id|ref
op_star
id|refs
comma
r_struct
id|ref
op_star
op_star
id|matched_ref
)paren
(brace
r_int
id|match
suffix:semicolon
r_int
id|patlen
op_assign
id|strlen
c_func
(paren
id|pattern
)paren
suffix:semicolon
r_for
c_loop
(paren
id|match
op_assign
l_int|0
suffix:semicolon
id|refs
suffix:semicolon
id|refs
op_assign
id|refs-&gt;next
)paren
(brace
r_char
op_star
id|name
op_assign
id|refs-&gt;name
suffix:semicolon
r_int
id|namelen
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
id|namelen
OL
id|patlen
op_logical_or
id|memcmp
c_func
(paren
id|name
op_plus
id|namelen
id|patlen
comma
id|pattern
comma
id|patlen
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|namelen
op_ne
id|patlen
op_logical_and
id|name
(braket
id|namelen
id|patlen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
id|match
op_increment
suffix:semicolon
op_star
id|matched_ref
op_assign
id|refs
suffix:semicolon
)brace
r_return
id|match
suffix:semicolon
)brace
DECL|function|link_dst_tail
r_static
r_void
id|link_dst_tail
c_func
(paren
r_struct
id|ref
op_star
id|ref
comma
r_struct
id|ref
op_star
op_star
op_star
id|tail
)paren
(brace
op_star
op_star
id|tail
op_assign
id|ref
suffix:semicolon
op_star
id|tail
op_assign
op_amp
id|ref-&gt;next
suffix:semicolon
op_star
op_star
id|tail
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|try_explicit_object_name
r_static
r_struct
id|ref
op_star
id|try_explicit_object_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
id|ref
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ref
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
id|ref
suffix:semicolon
)brace
DECL|function|match_explicit_refs
r_static
r_int
id|match_explicit_refs
c_func
(paren
r_struct
id|ref
op_star
id|src
comma
r_struct
id|ref
op_star
id|dst
comma
r_struct
id|ref
op_star
op_star
op_star
id|dst_tail
comma
r_struct
id|refspec
op_star
id|rs
)paren
(brace
r_int
id|i
comma
id|errs
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|errs
op_assign
l_int|0
suffix:semicolon
id|rs
(braket
id|i
)braket
dot
id|src
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ref
op_star
id|matched_src
comma
op_star
id|matched_dst
suffix:semicolon
id|matched_src
op_assign
id|matched_dst
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|count_refspec_match
c_func
(paren
id|rs
(braket
id|i
)braket
dot
id|src
comma
id|src
comma
op_amp
id|matched_src
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* The source could be in the get_sha1() format&n;&t;&t;&t; * not a reference name.&n;&t;&t;&t; */
id|matched_src
op_assign
id|try_explicit_object_name
c_func
(paren
id|rs
(braket
id|i
)braket
dot
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|matched_src
)paren
r_break
suffix:semicolon
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;src refspec %s does not match any.&quot;
comma
id|rs
(braket
id|i
)braket
dot
id|src
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;src refspec %s matches more than one.&quot;
comma
id|rs
(braket
id|i
)braket
dot
id|src
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|count_refspec_match
c_func
(paren
id|rs
(braket
id|i
)braket
dot
id|dst
comma
id|dst
comma
op_amp
id|matched_dst
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|rs
(braket
id|i
)braket
dot
id|dst
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|rs
(braket
id|i
)braket
dot
id|dst
)paren
op_plus
l_int|1
suffix:semicolon
id|matched_dst
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dst
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|matched_dst-&gt;name
comma
id|rs
(braket
id|i
)braket
dot
id|dst
comma
id|len
)paren
suffix:semicolon
id|link_dst_tail
c_func
(paren
id|matched_dst
comma
id|dst_tail
)paren
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
id|rs
(braket
id|i
)braket
dot
id|src
comma
id|rs
(braket
id|i
)braket
dot
id|dst
)paren
op_logical_and
id|matched_src
)paren
(brace
multiline_comment|/* pushing &quot;master:master&quot; when&n;&t;&t;&t;&t; * remote does not have master yet.&n;&t;&t;&t;&t; */
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|matched_src-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
id|matched_dst
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dst
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|matched_dst-&gt;name
comma
id|matched_src-&gt;name
comma
id|len
)paren
suffix:semicolon
id|link_dst_tail
c_func
(paren
id|matched_dst
comma
id|dst_tail
)paren
suffix:semicolon
)brace
r_else
(brace
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;dst refspec %s does not match any &quot;
l_string|&quot;existing ref on the remote and does &quot;
l_string|&quot;not start with refs/.&quot;
comma
id|rs
(braket
id|i
)braket
dot
id|dst
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;dst refspec %s matches more than one.&quot;
comma
id|rs
(braket
id|i
)braket
dot
id|dst
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errs
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|matched_dst-&gt;peer_ref
)paren
(brace
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;dst ref %s receives from more than one src.&quot;
comma
id|matched_dst-&gt;name
)paren
suffix:semicolon
)brace
r_else
id|matched_dst-&gt;peer_ref
op_assign
id|matched_src
suffix:semicolon
)brace
r_return
id|errs
suffix:semicolon
)brace
DECL|function|find_ref_by_name
r_static
r_struct
id|ref
op_star
id|find_ref_by_name
c_func
(paren
r_struct
id|ref
op_star
id|list
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|list-&gt;name
comma
id|name
)paren
)paren
r_return
id|list
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|match_refs
r_int
id|match_refs
c_func
(paren
r_struct
id|ref
op_star
id|src
comma
r_struct
id|ref
op_star
id|dst
comma
r_struct
id|ref
op_star
op_star
op_star
id|dst_tail
comma
r_int
id|nr_refspec
comma
r_char
op_star
op_star
id|refspec
comma
r_int
id|all
)paren
(brace
r_struct
id|refspec
op_star
id|rs
op_assign
id|parse_ref_spec
c_func
(paren
id|nr_refspec
comma
id|refspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_refspec
)paren
r_return
id|match_explicit_refs
c_func
(paren
id|src
comma
id|dst
comma
id|dst_tail
comma
id|rs
)paren
suffix:semicolon
multiline_comment|/* pick the remainder */
r_for
c_loop
(paren
suffix:semicolon
id|src
suffix:semicolon
id|src
op_assign
id|src-&gt;next
)paren
(brace
r_struct
id|ref
op_star
id|dst_peer
suffix:semicolon
r_if
c_cond
(paren
id|src-&gt;peer_ref
)paren
r_continue
suffix:semicolon
id|dst_peer
op_assign
id|find_ref_by_name
c_func
(paren
id|dst
comma
id|src-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dst_peer
op_logical_and
id|dst_peer-&gt;peer_ref
)paren
op_logical_or
(paren
op_logical_neg
id|dst_peer
op_logical_and
op_logical_neg
id|all
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_peer
)paren
(brace
multiline_comment|/* Create a new one and link it */
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|src-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
id|dst_peer
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dst_peer
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst_peer-&gt;name
comma
id|src-&gt;name
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst_peer-&gt;new_sha1
comma
id|src-&gt;new_sha1
comma
l_int|20
)paren
suffix:semicolon
id|link_dst_tail
c_func
(paren
id|dst_peer
comma
id|dst_tail
)paren
suffix:semicolon
)brace
id|dst_peer-&gt;peer_ref
op_assign
id|src
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
DECL|function|git_tcp_connect
r_static
r_int
id|git_tcp_connect
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_const
r_char
op_star
id|prog
comma
r_char
op_star
id|host
comma
r_char
op_star
id|path
)paren
(brace
r_int
id|sockfd
op_assign
l_int|1
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
l_string|&quot;Unable to look up %s (%s)&quot;
comma
id|host
comma
id|gai_strerror
c_func
(paren
id|gai
)paren
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
r_continue
suffix:semicolon
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
id|errno
)paren
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
id|sockfd
suffix:semicolon
id|packet_write
c_func
(paren
id|sockfd
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|prog
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
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
r_enum
id|protocol
id|protocol
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
id|protocol
op_assign
id|PROTO_LOCAL
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
id|protocol
op_assign
id|PROTO_SSH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|path
comma
l_string|&quot;//&quot;
comma
l_int|2
)paren
)paren
(brace
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
id|path
op_plus
l_int|2
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
(brace
r_int
id|nr
op_assign
id|slash
id|path
l_int|2
suffix:semicolon
id|memmove
c_func
(paren
id|path
comma
id|path
op_plus
l_int|2
comma
id|nr
)paren
suffix:semicolon
id|path
(braket
id|nr
)braket
op_assign
l_int|0
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
op_assign
id|path
suffix:semicolon
id|path
op_assign
id|slash
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|protocol
op_eq
id|PROTO_GIT
)paren
r_return
id|git_tcp_connect
c_func
(paren
id|fd
comma
id|prog
comma
id|host
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
id|sq_quote
c_func
(paren
id|path
)paren
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
