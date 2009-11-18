macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|struct|helper_data
r_struct
id|helper_data
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|helper
r_struct
id|child_process
op_star
id|helper
suffix:semicolon
DECL|member|fetch
r_int
id|fetch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|import
r_int
id|import
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* These go from remote name (as in &quot;list&quot;) to private name */
DECL|member|refspecs
r_struct
id|refspec
op_star
id|refspecs
suffix:semicolon
DECL|member|refspec_nr
r_int
id|refspec_nr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_helper
r_static
r_struct
id|child_process
op_star
id|get_helper
c_func
(paren
r_struct
id|transport
op_star
id|transport
)paren
(brace
r_struct
id|helper_data
op_star
id|data
op_assign
id|transport-&gt;data
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|child_process
op_star
id|helper
suffix:semicolon
id|FILE
op_star
id|file
suffix:semicolon
r_const
r_char
op_star
op_star
id|refspecs
op_assign
l_int|NULL
suffix:semicolon
r_int
id|refspec_nr
op_assign
l_int|0
suffix:semicolon
r_int
id|refspec_alloc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;helper
)paren
r_return
id|data-&gt;helper
suffix:semicolon
id|helper
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|helper
)paren
)paren
suffix:semicolon
id|helper-&gt;in
op_assign
l_int|1
suffix:semicolon
id|helper-&gt;out
op_assign
l_int|1
suffix:semicolon
id|helper-&gt;err
op_assign
l_int|0
suffix:semicolon
id|helper-&gt;argv
op_assign
id|xcalloc
c_func
(paren
l_int|4
comma
r_sizeof
(paren
op_star
id|helper-&gt;argv
)paren
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;remote-%s&quot;
comma
id|data-&gt;name
)paren
suffix:semicolon
id|helper-&gt;argv
(braket
l_int|0
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|helper-&gt;argv
(braket
l_int|1
)braket
op_assign
id|transport-&gt;remote-&gt;name
suffix:semicolon
id|helper-&gt;argv
(braket
l_int|2
)braket
op_assign
id|transport-&gt;url
suffix:semicolon
id|helper-&gt;git_cmd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
id|helper
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to run helper: git %s&quot;
comma
id|helper-&gt;argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|data-&gt;helper
op_assign
id|helper
suffix:semicolon
id|write_str_in_full
c_func
(paren
id|helper-&gt;in
comma
l_string|&quot;capabilities&bslash;n&quot;
)paren
suffix:semicolon
id|file
op_assign
id|xfdopen
c_func
(paren
id|helper-&gt;out
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
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
id|file
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
multiline_comment|/* child died, message supplied already */
r_if
c_cond
(paren
op_logical_neg
op_star
id|buf.buf
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf.buf
comma
l_string|&quot;fetch&quot;
)paren
)paren
id|data-&gt;fetch
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf.buf
comma
l_string|&quot;import&quot;
)paren
)paren
id|data-&gt;import
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;refspecs
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf.buf
comma
l_string|&quot;refspec &quot;
)paren
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|refspecs
comma
id|refspec_nr
op_plus
l_int|1
comma
id|refspec_alloc
)paren
suffix:semicolon
id|refspecs
(braket
id|refspec_nr
op_increment
)braket
op_assign
id|strdup
c_func
(paren
id|buf.buf
op_plus
id|strlen
c_func
(paren
l_string|&quot;refspec &quot;
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|refspecs
)paren
(brace
r_int
id|i
suffix:semicolon
id|data-&gt;refspec_nr
op_assign
id|refspec_nr
suffix:semicolon
id|data-&gt;refspecs
op_assign
id|parse_fetch_refspec
c_func
(paren
id|refspec_nr
comma
id|refspecs
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
id|refspec_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|refspecs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|refspecs
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|data-&gt;helper
suffix:semicolon
)brace
DECL|function|disconnect_helper
r_static
r_int
id|disconnect_helper
c_func
(paren
r_struct
id|transport
op_star
id|transport
)paren
(brace
r_struct
id|helper_data
op_star
id|data
op_assign
id|transport-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;helper
)paren
(brace
id|write_str_in_full
c_func
(paren
id|data-&gt;helper-&gt;in
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|data-&gt;helper-&gt;in
)paren
suffix:semicolon
id|finish_command
c_func
(paren
id|data-&gt;helper
)paren
suffix:semicolon
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|data-&gt;helper-&gt;argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|data-&gt;helper-&gt;argv
)paren
suffix:semicolon
id|free
c_func
(paren
id|data-&gt;helper
)paren
suffix:semicolon
id|data-&gt;helper
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_helper
r_static
r_int
id|release_helper
c_func
(paren
r_struct
id|transport
op_star
id|transport
)paren
(brace
r_struct
id|helper_data
op_star
id|data
op_assign
id|transport-&gt;data
suffix:semicolon
id|free_refspec
c_func
(paren
id|data-&gt;refspec_nr
comma
id|data-&gt;refspecs
)paren
suffix:semicolon
id|data-&gt;refspecs
op_assign
l_int|NULL
suffix:semicolon
id|disconnect_helper
c_func
(paren
id|transport
)paren
suffix:semicolon
id|free
c_func
(paren
id|transport-&gt;data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_with_fetch
r_static
r_int
id|fetch_with_fetch
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_int
id|nr_heads
comma
r_struct
id|ref
op_star
op_star
id|to_fetch
)paren
(brace
r_struct
id|child_process
op_star
id|helper
op_assign
id|get_helper
c_func
(paren
id|transport
)paren
suffix:semicolon
id|FILE
op_star
id|file
op_assign
id|xfdopen
c_func
(paren
id|helper-&gt;out
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
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
id|nr_heads
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_struct
id|ref
op_star
id|posn
op_assign
id|to_fetch
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|posn-&gt;status
op_amp
id|REF_STATUS_UPTODATE
)paren
r_continue
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;fetch %s %s&bslash;n&quot;
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
id|write_in_full
c_func
(paren
id|helper-&gt;in
comma
id|buf.buf
comma
id|buf.len
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|file
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
multiline_comment|/* child died, message supplied already */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_importer
r_static
r_int
id|get_importer
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_struct
id|child_process
op_star
id|fastimport
)paren
(brace
r_struct
id|child_process
op_star
id|helper
op_assign
id|get_helper
c_func
(paren
id|transport
)paren
suffix:semicolon
id|memset
c_func
(paren
id|fastimport
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fastimport
)paren
)paren
suffix:semicolon
id|fastimport-&gt;in
op_assign
id|helper-&gt;out
suffix:semicolon
id|fastimport-&gt;argv
op_assign
id|xcalloc
c_func
(paren
l_int|5
comma
r_sizeof
(paren
op_star
id|fastimport-&gt;argv
)paren
)paren
suffix:semicolon
id|fastimport-&gt;argv
(braket
l_int|0
)braket
op_assign
l_string|&quot;fast-import&quot;
suffix:semicolon
id|fastimport-&gt;argv
(braket
l_int|1
)braket
op_assign
l_string|&quot;--quiet&quot;
suffix:semicolon
id|fastimport-&gt;git_cmd
op_assign
l_int|1
suffix:semicolon
r_return
id|start_command
c_func
(paren
id|fastimport
)paren
suffix:semicolon
)brace
DECL|function|fetch_with_import
r_static
r_int
id|fetch_with_import
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_int
id|nr_heads
comma
r_struct
id|ref
op_star
op_star
id|to_fetch
)paren
(brace
r_struct
id|child_process
id|fastimport
suffix:semicolon
r_struct
id|child_process
op_star
id|helper
op_assign
id|get_helper
c_func
(paren
id|transport
)paren
suffix:semicolon
r_struct
id|helper_data
op_star
id|data
op_assign
id|transport-&gt;data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|ref
op_star
id|posn
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|get_importer
c_func
(paren
id|transport
comma
op_amp
id|fastimport
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Couldn&squot;t run fast-import&quot;
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
id|nr_heads
suffix:semicolon
id|i
op_increment
)paren
(brace
id|posn
op_assign
id|to_fetch
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|posn-&gt;status
op_amp
id|REF_STATUS_UPTODATE
)paren
r_continue
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;import %s&bslash;n&quot;
comma
id|posn-&gt;name
)paren
suffix:semicolon
id|write_in_full
c_func
(paren
id|helper-&gt;in
comma
id|buf.buf
comma
id|buf.len
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
id|disconnect_helper
c_func
(paren
id|transport
)paren
suffix:semicolon
id|finish_command
c_func
(paren
op_amp
id|fastimport
)paren
suffix:semicolon
id|free
c_func
(paren
id|fastimport.argv
)paren
suffix:semicolon
id|fastimport.argv
op_assign
l_int|NULL
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
id|nr_heads
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
r_private
suffix:semicolon
id|posn
op_assign
id|to_fetch
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|posn-&gt;status
op_amp
id|REF_STATUS_UPTODATE
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;refspecs
)paren
r_private
op_assign
id|apply_refspecs
c_func
(paren
id|data-&gt;refspecs
comma
id|data-&gt;refspec_nr
comma
id|posn-&gt;name
)paren
suffix:semicolon
r_else
r_private
op_assign
id|strdup
c_func
(paren
id|posn-&gt;name
)paren
suffix:semicolon
id|read_ref
c_func
(paren
r_private
comma
id|posn-&gt;old_sha1
)paren
suffix:semicolon
id|free
c_func
(paren
r_private
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch
r_static
r_int
id|fetch
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_int
id|nr_heads
comma
r_struct
id|ref
op_star
op_star
id|to_fetch
)paren
(brace
r_struct
id|helper_data
op_star
id|data
op_assign
id|transport-&gt;data
suffix:semicolon
r_int
id|i
comma
id|count
suffix:semicolon
id|count
op_assign
l_int|0
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
id|nr_heads
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|to_fetch
(braket
id|i
)braket
op_member_access_from_pointer
id|status
op_amp
id|REF_STATUS_UPTODATE
)paren
)paren
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;fetch
)paren
r_return
id|fetch_with_fetch
c_func
(paren
id|transport
comma
id|nr_heads
comma
id|to_fetch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;import
)paren
r_return
id|fetch_with_import
c_func
(paren
id|transport
comma
id|nr_heads
comma
id|to_fetch
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_refs_list
r_static
r_struct
id|ref
op_star
id|get_refs_list
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_int
id|for_push
)paren
(brace
r_struct
id|child_process
op_star
id|helper
suffix:semicolon
r_struct
id|ref
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
op_star
id|tail
op_assign
op_amp
id|ret
suffix:semicolon
r_struct
id|ref
op_star
id|posn
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|FILE
op_star
id|file
suffix:semicolon
id|helper
op_assign
id|get_helper
c_func
(paren
id|transport
)paren
suffix:semicolon
id|write_str_in_full
c_func
(paren
id|helper-&gt;in
comma
l_string|&quot;list&bslash;n&quot;
)paren
suffix:semicolon
id|file
op_assign
id|xfdopen
c_func
(paren
id|helper-&gt;out
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|eov
comma
op_star
id|eon
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|file
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
multiline_comment|/* child died, message supplied already */
r_if
c_cond
(paren
op_logical_neg
op_star
id|buf.buf
)paren
r_break
suffix:semicolon
id|eov
op_assign
id|strchr
c_func
(paren
id|buf.buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eov
)paren
id|die
c_func
(paren
l_string|&quot;Malformed response in ref list: %s&quot;
comma
id|buf.buf
)paren
suffix:semicolon
id|eon
op_assign
id|strchr
c_func
(paren
id|eov
op_plus
l_int|1
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
op_star
id|eov
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|eon
)paren
op_star
id|eon
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|tail
op_assign
id|alloc_ref
c_func
(paren
id|eov
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;@&squot;
)paren
(paren
op_star
id|tail
)paren
op_member_access_from_pointer
id|symref
op_assign
id|xstrdup
c_func
(paren
id|buf.buf
op_plus
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|buf.buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;?&squot;
)paren
id|get_sha1_hex
c_func
(paren
id|buf.buf
comma
(paren
op_star
id|tail
)paren
op_member_access_from_pointer
id|old_sha1
)paren
suffix:semicolon
id|tail
op_assign
op_amp
(paren
(paren
op_star
id|tail
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_for
c_loop
(paren
id|posn
op_assign
id|ret
suffix:semicolon
id|posn
suffix:semicolon
id|posn
op_assign
id|posn-&gt;next
)paren
id|resolve_remote_symref
c_func
(paren
id|posn
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|transport_helper_init
r_int
id|transport_helper_init
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|helper_data
op_star
id|data
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
comma
l_int|1
)paren
suffix:semicolon
id|data-&gt;name
op_assign
id|name
suffix:semicolon
id|transport-&gt;data
op_assign
id|data
suffix:semicolon
id|transport-&gt;get_refs_list
op_assign
id|get_refs_list
suffix:semicolon
id|transport-&gt;fetch
op_assign
id|fetch
suffix:semicolon
id|transport-&gt;disconnect
op_assign
id|release_helper
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
