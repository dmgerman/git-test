macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;arpa/inet.h&gt;
macro_line|#include &lt;netdb.h&gt;
DECL|variable|server_capabilities
r_static
r_char
op_star
id|server_capabilities
op_assign
l_int|NULL
suffix:semicolon
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
id|ignore_funny
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
id|strdup
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
id|ignore_funny
op_logical_and
l_int|45
OL
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
op_logical_and
id|check_ref_format
c_func
(paren
id|name
op_plus
l_int|5
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
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;ACK &quot;
comma
l_int|4
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
DECL|member|force
r_char
id|force
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A:B means fast forward remote B with local A.&n; * +A:B means overwrite remote B with local A.&n; * +A is a shorthand for +A:A.&n; * A is a shorthand for A:A.&n; */
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
id|xcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rs
)paren
comma
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
r_if
c_cond
(paren
op_star
id|sp
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|rs
(braket
id|i
)braket
dot
id|force
op_assign
l_int|1
suffix:semicolon
id|sp
op_increment
suffix:semicolon
)brace
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
(brace
id|matched_dst-&gt;peer_ref
op_assign
id|matched_src
suffix:semicolon
id|matched_dst-&gt;force
op_assign
id|rs
(braket
id|i
)braket
dot
id|force
suffix:semicolon
)brace
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
r_for
c_loop
(paren
id|ap
op_assign
id|he-&gt;h_addr_list
suffix:semicolon
op_star
id|ap
suffix:semicolon
id|ap
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
r_continue
suffix:semicolon
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
id|git_tcp_connect_sock
c_func
(paren
id|host
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
)brace
DECL|variable|git_proxy_command
r_static
r_char
op_star
id|git_proxy_command
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|rhost_name
r_static
r_const
r_char
op_star
id|rhost_name
op_assign
l_int|NULL
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
id|xmalloc
c_func
(paren
id|matchlen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|git_proxy_command
comma
id|value
comma
id|matchlen
)paren
suffix:semicolon
id|git_proxy_command
(braket
id|matchlen
)braket
op_assign
l_int|0
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
id|execlp
c_func
(paren
id|git_proxy_command
comma
id|git_proxy_command
comma
id|host
comma
id|port
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
l_string|&quot;fork failed&quot;
)paren
suffix:semicolon
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
id|c
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_if
c_cond
(paren
id|path
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
r_else
id|path
op_assign
id|host
suffix:semicolon
)brace
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
id|strdup
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
id|strdup
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
id|prog
comma
id|host
comma
id|path
)paren
suffix:semicolon
r_else
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
id|execlp
c_func
(paren
id|ssh
comma
id|ssh_basename
comma
id|host
comma
id|command
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
id|command
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
