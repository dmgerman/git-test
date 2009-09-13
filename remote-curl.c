macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;walker.h&quot;
macro_line|#include &quot;http.h&quot;
DECL|function|get_refs
r_static
r_struct
id|ref
op_star
id|get_refs
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_const
r_char
op_star
id|url
)paren
(brace
r_struct
id|strbuf
id|buffer
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|data
comma
op_star
id|start
comma
op_star
id|mid
suffix:semicolon
r_char
op_star
id|ref_name
suffix:semicolon
r_char
op_star
id|refs_url
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|http_ret
suffix:semicolon
r_struct
id|ref
op_star
id|refs
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
id|ref
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
id|last_ref
op_assign
l_int|NULL
suffix:semicolon
id|refs_url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|url
)paren
op_plus
l_int|11
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|refs_url
comma
l_string|&quot;%s/info/refs&quot;
comma
id|url
)paren
suffix:semicolon
id|http_ret
op_assign
id|http_get_strbuf
c_func
(paren
id|refs_url
comma
op_amp
id|buffer
comma
id|HTTP_NO_CACHE
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|http_ret
)paren
(brace
r_case
id|HTTP_OK
suffix:colon
r_break
suffix:semicolon
r_case
id|HTTP_MISSING_TARGET
suffix:colon
id|die
c_func
(paren
l_string|&quot;%s not found: did you run git update-server-info on the&quot;
l_string|&quot; server?&quot;
comma
id|refs_url
)paren
suffix:semicolon
r_default
suffix:colon
id|http_error
c_func
(paren
id|refs_url
comma
id|http_ret
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;HTTP request failed&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|buffer.buf
suffix:semicolon
id|start
op_assign
l_int|NULL
suffix:semicolon
id|mid
op_assign
id|data
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|buffer.len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|start
)paren
(brace
id|start
op_assign
op_amp
id|data
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;t&squot;
)paren
id|mid
op_assign
op_amp
id|data
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|data
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|ref_name
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
id|ref
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ref
)paren
op_plus
id|strlen
c_func
(paren
id|ref_name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ref
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ref
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ref-&gt;name
comma
id|ref_name
)paren
suffix:semicolon
id|get_sha1_hex
c_func
(paren
id|start
comma
id|ref-&gt;old_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refs
)paren
id|refs
op_assign
id|ref
suffix:semicolon
r_if
c_cond
(paren
id|last_ref
)paren
id|last_ref-&gt;next
op_assign
id|ref
suffix:semicolon
id|last_ref
op_assign
id|ref
suffix:semicolon
id|start
op_assign
l_int|NULL
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
id|ref
op_assign
id|alloc_ref
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walker
op_member_access_from_pointer
id|fetch_ref
c_func
(paren
id|walker
comma
id|ref
)paren
op_logical_and
op_logical_neg
id|resolve_remote_symref
c_func
(paren
id|ref
comma
id|refs
)paren
)paren
(brace
id|ref-&gt;next
op_assign
id|refs
suffix:semicolon
id|refs
op_assign
id|ref
suffix:semicolon
)brace
r_else
(brace
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
id|free
c_func
(paren
id|refs_url
)paren
suffix:semicolon
r_return
id|refs
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
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|url
suffix:semicolon
r_struct
id|walker
op_star
id|walker
op_assign
l_int|NULL
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Remote needed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|remote
op_assign
id|remote_get
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|2
)paren
(brace
id|url
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
)brace
r_else
(brace
id|url
op_assign
id|remote-&gt;url
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf.buf
comma
l_string|&quot;fetch &quot;
)paren
)paren
(brace
r_char
op_star
id|obj
op_assign
id|buf.buf
op_plus
id|strlen
c_func
(paren
l_string|&quot;fetch &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walker
)paren
id|walker
op_assign
id|get_http_walker
c_func
(paren
id|url
comma
id|remote
)paren
suffix:semicolon
id|walker-&gt;get_all
op_assign
l_int|1
suffix:semicolon
id|walker-&gt;get_tree
op_assign
l_int|1
suffix:semicolon
id|walker-&gt;get_history
op_assign
l_int|1
suffix:semicolon
id|walker-&gt;get_verbosely
op_assign
l_int|0
suffix:semicolon
id|walker-&gt;get_recover
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|walker_fetch
c_func
(paren
id|walker
comma
l_int|1
comma
op_amp
id|obj
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Fetch failed.&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
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
id|buf.buf
comma
l_string|&quot;list&quot;
)paren
)paren
(brace
r_struct
id|ref
op_star
id|refs
suffix:semicolon
r_struct
id|ref
op_star
id|posn
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walker
)paren
id|walker
op_assign
id|get_http_walker
c_func
(paren
id|url
comma
id|remote
)paren
suffix:semicolon
id|refs
op_assign
id|get_refs
c_func
(paren
id|walker
comma
id|url
)paren
suffix:semicolon
r_for
c_loop
(paren
id|posn
op_assign
id|refs
suffix:semicolon
id|posn
suffix:semicolon
id|posn
op_assign
id|posn-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|posn-&gt;symref
)paren
id|printf
c_func
(paren
l_string|&quot;@%s %s&bslash;n&quot;
comma
id|posn-&gt;symref
comma
id|posn-&gt;name
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|posn-&gt;old_sha1
)paren
comma
id|posn-&gt;name
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
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
id|buf.buf
comma
l_string|&quot;capabilities&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;fetch&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
