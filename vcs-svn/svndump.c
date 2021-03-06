multiline_comment|/*&n; * Parse and rearrange a svnadmin dump.&n; * Create the dump with:&n; * svnadmin dump --incremental -r&lt;startrev&gt;:&lt;endrev&gt; &lt;repository&gt; &gt;outfile&n; *&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;repo_tree.h&quot;
macro_line|#include &quot;fast_export.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;svndump.h&quot;
multiline_comment|/*&n; * Compare start of string to literal of equal length;&n; * must be guarded by length test.&n; */
DECL|macro|constcmp
mdefine_line|#define constcmp(s, ref) memcmp(s, ref, sizeof(ref) - 1)
DECL|macro|REPORT_FILENO
mdefine_line|#define REPORT_FILENO 3
DECL|macro|NODEACT_REPLACE
mdefine_line|#define NODEACT_REPLACE 4
DECL|macro|NODEACT_DELETE
mdefine_line|#define NODEACT_DELETE 3
DECL|macro|NODEACT_ADD
mdefine_line|#define NODEACT_ADD 2
DECL|macro|NODEACT_CHANGE
mdefine_line|#define NODEACT_CHANGE 1
DECL|macro|NODEACT_UNKNOWN
mdefine_line|#define NODEACT_UNKNOWN 0
multiline_comment|/* States: */
DECL|macro|DUMP_CTX
mdefine_line|#define DUMP_CTX 0&t;/* dump metadata */
DECL|macro|REV_CTX
mdefine_line|#define REV_CTX  1&t;/* revision metadata */
DECL|macro|NODE_CTX
mdefine_line|#define NODE_CTX 2&t;/* node metadata */
DECL|macro|INTERNODE_CTX
mdefine_line|#define INTERNODE_CTX 3&t;/* between nodes */
DECL|macro|DATE_RFC2822_LEN
mdefine_line|#define DATE_RFC2822_LEN 31
DECL|variable|input
r_static
r_struct
id|line_buffer
id|input
op_assign
id|LINE_BUFFER_INIT
suffix:semicolon
r_static
r_struct
(brace
DECL|member|action
DECL|member|srcRev
DECL|member|type
r_uint32
id|action
comma
id|srcRev
comma
id|type
suffix:semicolon
DECL|member|prop_length
DECL|member|text_length
id|off_t
id|prop_length
comma
id|text_length
suffix:semicolon
DECL|member|src
DECL|member|dst
r_struct
id|strbuf
id|src
comma
id|dst
suffix:semicolon
DECL|member|text_delta
DECL|member|prop_delta
r_uint32
id|text_delta
comma
id|prop_delta
suffix:semicolon
DECL|variable|node_ctx
)brace
id|node_ctx
suffix:semicolon
r_static
r_struct
(brace
DECL|member|revision
r_uint32
id|revision
suffix:semicolon
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
DECL|member|log
DECL|member|author
DECL|member|note
r_struct
id|strbuf
id|log
comma
id|author
comma
id|note
suffix:semicolon
DECL|variable|rev_ctx
)brace
id|rev_ctx
suffix:semicolon
r_static
r_struct
(brace
DECL|member|version
r_uint32
id|version
suffix:semicolon
DECL|member|uuid
DECL|member|url
r_struct
id|strbuf
id|uuid
comma
id|url
suffix:semicolon
DECL|variable|dump_ctx
)brace
id|dump_ctx
suffix:semicolon
DECL|function|reset_node_ctx
r_static
r_void
id|reset_node_ctx
c_func
(paren
r_char
op_star
id|fname
)paren
(brace
id|node_ctx.type
op_assign
l_int|0
suffix:semicolon
id|node_ctx.action
op_assign
id|NODEACT_UNKNOWN
suffix:semicolon
id|node_ctx.prop_length
op_assign
l_int|1
suffix:semicolon
id|node_ctx.text_length
op_assign
l_int|1
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|node_ctx.src
)paren
suffix:semicolon
id|node_ctx.srcRev
op_assign
l_int|0
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|node_ctx.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fname
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|node_ctx.dst
comma
id|fname
)paren
suffix:semicolon
id|node_ctx.text_delta
op_assign
l_int|0
suffix:semicolon
id|node_ctx.prop_delta
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|reset_rev_ctx
r_static
r_void
id|reset_rev_ctx
c_func
(paren
r_uint32
id|revision
)paren
(brace
id|rev_ctx.revision
op_assign
id|revision
suffix:semicolon
id|rev_ctx.timestamp
op_assign
l_int|0
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|rev_ctx.log
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|rev_ctx.author
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|rev_ctx.note
)paren
suffix:semicolon
)brace
DECL|function|reset_dump_ctx
r_static
r_void
id|reset_dump_ctx
c_func
(paren
r_const
r_char
op_star
id|url
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|dump_ctx.url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|url
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|dump_ctx.url
comma
id|url
)paren
suffix:semicolon
id|dump_ctx.version
op_assign
l_int|1
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|dump_ctx.uuid
)paren
suffix:semicolon
)brace
DECL|function|handle_property
r_static
r_void
id|handle_property
c_func
(paren
r_const
r_struct
id|strbuf
op_star
id|key_buf
comma
r_struct
id|strbuf
op_star
id|val
comma
r_uint32
op_star
id|type_set
)paren
(brace
r_const
r_char
op_star
id|key
op_assign
id|key_buf-&gt;buf
suffix:semicolon
r_int
id|keylen
op_assign
id|key_buf-&gt;len
suffix:semicolon
r_switch
c_cond
(paren
id|keylen
op_plus
l_int|1
)paren
(brace
r_case
r_sizeof
(paren
l_string|&quot;svn:log&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|key
comma
l_string|&quot;svn:log&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: unsets svn:log&quot;
)paren
suffix:semicolon
id|strbuf_swap
c_func
(paren
op_amp
id|rev_ctx.log
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;svn:author&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|key
comma
l_string|&quot;svn:author&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|strbuf_reset
c_func
(paren
op_amp
id|rev_ctx.author
)paren
suffix:semicolon
r_else
id|strbuf_swap
c_func
(paren
op_amp
id|rev_ctx.author
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;svn:date&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|key
comma
l_string|&quot;svn:date&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: unsets svn:date&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_date_basic
c_func
(paren
id|val-&gt;buf
comma
op_amp
id|rev_ctx.timestamp
comma
l_int|NULL
)paren
)paren
id|warning
c_func
(paren
l_string|&quot;invalid timestamp: %s&quot;
comma
id|val-&gt;buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;svn:executable&quot;
)paren
suffix:colon
r_case
r_sizeof
(paren
l_string|&quot;svn:special&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|keylen
op_eq
id|strlen
c_func
(paren
l_string|&quot;svn:executable&quot;
)paren
op_logical_and
id|constcmp
c_func
(paren
id|key
comma
l_string|&quot;svn:executable&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|keylen
op_eq
id|strlen
c_func
(paren
l_string|&quot;svn:special&quot;
)paren
op_logical_and
id|constcmp
c_func
(paren
id|key
comma
l_string|&quot;svn:special&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|type_set
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid dump: sets type twice&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
id|node_ctx.type
op_assign
id|REPO_MODE_BLB
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
id|type_set
op_assign
l_int|1
suffix:semicolon
id|node_ctx.type
op_assign
id|keylen
op_eq
id|strlen
c_func
(paren
l_string|&quot;svn:executable&quot;
)paren
ques
c_cond
id|REPO_MODE_EXE
suffix:colon
id|REPO_MODE_LNK
suffix:semicolon
)brace
)brace
DECL|function|die_short_read
r_static
r_void
id|die_short_read
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|buffer_ferror
c_func
(paren
op_amp
id|input
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;error reading dump file&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid dump: unexpected end of file&quot;
)paren
suffix:semicolon
)brace
DECL|function|read_props
r_static
r_void
id|read_props
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|strbuf
id|key
op_assign
id|STRBUF_INIT
suffix:semicolon
r_static
r_struct
id|strbuf
id|val
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|t
suffix:semicolon
multiline_comment|/*&n;&t; * NEEDSWORK: to support simple mode changes like&n;&t; *&t;K 11&n;&t; *&t;svn:special&n;&t; *&t;V 1&n;&t; *&t;*&n;&t; *&t;D 14&n;&t; *&t;svn:executable&n;&t; * we keep track of whether a mode has been set and reset to&n;&t; * plain file only if not.  We should be keeping track of the&n;&t; * symlink and executable bits separately instead.&n;&t; */
r_uint32
id|type_set
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|t
op_assign
id|buffer_read_line
c_func
(paren
op_amp
id|input
)paren
)paren
op_logical_and
id|strcmp
c_func
(paren
id|t
comma
l_string|&quot;PROPS-END&quot;
)paren
)paren
(brace
r_uint32
id|len
suffix:semicolon
r_const
r_char
id|type
op_assign
id|t
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|type
op_logical_or
id|t
(braket
l_int|1
)braket
op_ne
l_char|&squot; &squot;
)paren
id|die
c_func
(paren
l_string|&quot;invalid property line: %s&quot;
comma
id|t
)paren
suffix:semicolon
id|len
op_assign
id|atoi
c_func
(paren
op_amp
id|t
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|val
)paren
suffix:semicolon
id|buffer_read_binary
c_func
(paren
op_amp
id|input
comma
op_amp
id|val
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val.len
OL
id|len
)paren
id|die_short_read
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Discard trailing newline. */
id|ch
op_assign
id|buffer_read_char
c_func
(paren
op_amp
id|input
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
id|EOF
)paren
id|die_short_read
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: expected newline after %s&quot;
comma
id|val.buf
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_char|&squot;K&squot;
suffix:colon
id|strbuf_swap
c_func
(paren
op_amp
id|key
comma
op_amp
id|val
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
id|handle_property
c_func
(paren
op_amp
id|val
comma
l_int|NULL
comma
op_amp
id|type_set
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;V&squot;
suffix:colon
id|handle_property
c_func
(paren
op_amp
id|key
comma
op_amp
id|val
comma
op_amp
id|type_set
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;invalid property line: %s&quot;
comma
id|t
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|handle_node
r_static
r_void
id|handle_node
c_func
(paren
r_void
)paren
(brace
r_const
r_uint32
id|type
op_assign
id|node_ctx.type
suffix:semicolon
r_const
r_int
id|have_props
op_assign
id|node_ctx.prop_length
op_ne
l_int|1
suffix:semicolon
r_const
r_int
id|have_text
op_assign
id|node_ctx.text_length
op_ne
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Old text for this node:&n;&t; *  NULL&t;- directory or bug&n;&t; *  empty_blob&t;- empty&n;&t; *  &quot;&lt;dataref&gt;&quot;&t;- data retrievable from fast-import&n;&t; */
r_static
r_const
r_char
op_star
r_const
id|empty_blob
op_assign
l_string|&quot;::empty::&quot;
suffix:semicolon
r_const
r_char
op_star
id|old_data
op_assign
l_int|NULL
suffix:semicolon
r_uint32
id|old_mode
op_assign
id|REPO_MODE_BLB
suffix:semicolon
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_DELETE
)paren
(brace
r_if
c_cond
(paren
id|have_text
op_logical_or
id|have_props
op_logical_or
id|node_ctx.srcRev
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: deletion node has &quot;
l_string|&quot;copyfrom info, text, or properties&quot;
)paren
suffix:semicolon
id|repo_delete
c_func
(paren
id|node_ctx.dst.buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_REPLACE
)paren
(brace
id|repo_delete
c_func
(paren
id|node_ctx.dst.buf
)paren
suffix:semicolon
id|node_ctx.action
op_assign
id|NODEACT_ADD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node_ctx.srcRev
)paren
(brace
id|repo_copy
c_func
(paren
id|node_ctx.srcRev
comma
id|node_ctx.src.buf
comma
id|node_ctx.dst.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_ADD
)paren
id|node_ctx.action
op_assign
id|NODEACT_CHANGE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|have_text
op_logical_and
id|type
op_eq
id|REPO_MODE_DIR
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: directories cannot have text attached&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find old content (old_data) and decide on the new mode.&n;&t; */
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_CHANGE
op_logical_and
op_logical_neg
op_star
id|node_ctx.dst.buf
)paren
(brace
r_if
c_cond
(paren
id|type
op_ne
id|REPO_MODE_DIR
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: root of tree is not a regular file&quot;
)paren
suffix:semicolon
id|old_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_CHANGE
)paren
(brace
r_uint32
id|mode
suffix:semicolon
id|old_data
op_assign
id|repo_read_path
c_func
(paren
id|node_ctx.dst.buf
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|REPO_MODE_DIR
op_logical_and
id|type
op_ne
id|REPO_MODE_DIR
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: cannot modify a directory into a file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_ne
id|REPO_MODE_DIR
op_logical_and
id|type
op_eq
id|REPO_MODE_DIR
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: cannot modify a file into a directory&quot;
)paren
suffix:semicolon
id|node_ctx.type
op_assign
id|mode
suffix:semicolon
id|old_mode
op_assign
id|mode
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_ADD
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|REPO_MODE_DIR
)paren
id|old_data
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|have_text
)paren
id|old_data
op_assign
id|empty_blob
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;invalid dump: adds node without text&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|die
c_func
(paren
l_string|&quot;invalid dump: Node-path block lacks Node-action&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Adjust mode to reflect properties.&n;&t; */
r_if
c_cond
(paren
id|have_props
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|node_ctx.prop_delta
)paren
id|node_ctx.type
op_assign
id|type
suffix:semicolon
r_if
c_cond
(paren
id|node_ctx.prop_length
)paren
id|read_props
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Save the result.&n;&t; */
r_if
c_cond
(paren
id|type
op_eq
id|REPO_MODE_DIR
)paren
multiline_comment|/* directories are not tracked. */
r_return
suffix:semicolon
m_assert
(paren
id|old_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_data
op_eq
id|empty_blob
)paren
multiline_comment|/* For the fast_export_* functions, NULL means empty. */
id|old_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_text
)paren
(brace
id|fast_export_modify
c_func
(paren
id|node_ctx.dst.buf
comma
id|node_ctx.type
comma
id|old_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|node_ctx.text_delta
)paren
(brace
id|fast_export_modify
c_func
(paren
id|node_ctx.dst.buf
comma
id|node_ctx.type
comma
l_string|&quot;inline&quot;
)paren
suffix:semicolon
id|fast_export_data
c_func
(paren
id|node_ctx.type
comma
id|node_ctx.text_length
comma
op_amp
id|input
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fast_export_modify
c_func
(paren
id|node_ctx.dst.buf
comma
id|node_ctx.type
comma
l_string|&quot;inline&quot;
)paren
suffix:semicolon
id|fast_export_blob_delta
c_func
(paren
id|node_ctx.type
comma
id|old_mode
comma
id|old_data
comma
id|node_ctx.text_length
comma
op_amp
id|input
)paren
suffix:semicolon
)brace
DECL|function|begin_revision
r_static
r_void
id|begin_revision
c_func
(paren
r_const
r_char
op_star
id|remote_ref
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rev_ctx.revision
)paren
multiline_comment|/* revision 0 gets no git commit. */
r_return
suffix:semicolon
id|fast_export_begin_commit
c_func
(paren
id|rev_ctx.revision
comma
id|rev_ctx.author.buf
comma
op_amp
id|rev_ctx.log
comma
id|dump_ctx.uuid.buf
comma
id|dump_ctx.url.buf
comma
id|rev_ctx.timestamp
comma
id|remote_ref
)paren
suffix:semicolon
)brace
DECL|function|end_revision
r_static
r_void
id|end_revision
c_func
(paren
r_const
r_char
op_star
id|note_ref
)paren
(brace
r_struct
id|strbuf
id|mark
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|rev_ctx.revision
)paren
(brace
id|fast_export_end_commit
c_func
(paren
id|rev_ctx.revision
)paren
suffix:semicolon
id|fast_export_begin_note
c_func
(paren
id|rev_ctx.revision
comma
l_string|&quot;remote-svn&quot;
comma
l_string|&quot;Note created by remote-svn.&quot;
comma
id|rev_ctx.timestamp
comma
id|note_ref
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|mark
comma
l_string|&quot;:%&quot;
id|PRIu32
comma
id|rev_ctx.revision
)paren
suffix:semicolon
id|fast_export_note
c_func
(paren
id|mark.buf
comma
l_string|&quot;inline&quot;
)paren
suffix:semicolon
id|fast_export_buf_to_data
c_func
(paren
op_amp
id|rev_ctx.note
)paren
suffix:semicolon
)brace
)brace
DECL|function|svndump_read
r_void
id|svndump_read
c_func
(paren
r_const
r_char
op_star
id|url
comma
r_const
r_char
op_star
id|local_ref
comma
r_const
r_char
op_star
id|notes_ref
)paren
(brace
r_char
op_star
id|val
suffix:semicolon
r_char
op_star
id|t
suffix:semicolon
r_uint32
id|active_ctx
op_assign
id|DUMP_CTX
suffix:semicolon
r_uint32
id|len
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
id|url
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|t
op_assign
id|buffer_read_line
c_func
(paren
op_amp
id|input
)paren
)paren
)paren
(brace
id|val
op_assign
id|strchr
c_func
(paren
id|t
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
r_continue
suffix:semicolon
id|val
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|val
op_ne
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
id|val
op_increment
suffix:semicolon
multiline_comment|/* strlen(key) + 1 */
r_switch
c_cond
(paren
id|val
id|t
l_int|1
)paren
(brace
r_case
r_sizeof
(paren
l_string|&quot;SVN-fs-dump-format-version&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;SVN-fs-dump-format-version&quot;
)paren
)paren
r_continue
suffix:semicolon
id|dump_ctx.version
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dump_ctx.version
OG
l_int|3
)paren
id|die
c_func
(paren
l_string|&quot;expected svn dump format version &lt;= 3, found %&quot;
id|PRIu32
comma
id|dump_ctx.version
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;UUID&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;UUID&quot;
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|dump_ctx.uuid
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|dump_ctx.uuid
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Revision-number&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Revision-number&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_eq
id|NODE_CTX
)paren
id|handle_node
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_eq
id|REV_CTX
)paren
id|begin_revision
c_func
(paren
id|local_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_ne
id|DUMP_CTX
)paren
id|end_revision
c_func
(paren
id|notes_ref
)paren
suffix:semicolon
id|active_ctx
op_assign
id|REV_CTX
suffix:semicolon
id|reset_rev_ctx
c_func
(paren
id|atoi
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Node-path&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Node-&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|constcmp
c_func
(paren
id|t
op_plus
id|strlen
c_func
(paren
l_string|&quot;Node-&quot;
)paren
comma
l_string|&quot;path&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|active_ctx
op_eq
id|NODE_CTX
)paren
id|handle_node
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_eq
id|REV_CTX
)paren
id|begin_revision
c_func
(paren
id|local_ref
)paren
suffix:semicolon
id|active_ctx
op_assign
id|NODE_CTX
suffix:semicolon
id|reset_node_ctx
c_func
(paren
id|val
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
op_plus
id|strlen
c_func
(paren
l_string|&quot;Node-&quot;
)paren
comma
l_string|&quot;kind&quot;
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|val
comma
l_string|&quot;dir&quot;
)paren
)paren
id|node_ctx.type
op_assign
id|REPO_MODE_DIR
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|val
comma
l_string|&quot;file&quot;
)paren
)paren
id|node_ctx.type
op_assign
id|REPO_MODE_BLB
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unknown node-kind: %s&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Node-action&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Node-action&quot;
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|val
comma
l_string|&quot;delete&quot;
)paren
)paren
(brace
id|node_ctx.action
op_assign
id|NODEACT_DELETE
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
id|val
comma
l_string|&quot;add&quot;
)paren
)paren
(brace
id|node_ctx.action
op_assign
id|NODEACT_ADD
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
id|val
comma
l_string|&quot;change&quot;
)paren
)paren
(brace
id|node_ctx.action
op_assign
id|NODEACT_CHANGE
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
id|val
comma
l_string|&quot;replace&quot;
)paren
)paren
(brace
id|node_ctx.action
op_assign
id|NODEACT_REPLACE
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unknown node-action: %s&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
id|node_ctx.action
op_assign
id|NODEACT_UNKNOWN
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Node-copyfrom-path&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Node-copyfrom-path&quot;
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|node_ctx.src
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|node_ctx.src
comma
id|val
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Node-copyfrom-rev&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Node-copyfrom-rev&quot;
)paren
)paren
r_continue
suffix:semicolon
id|node_ctx.srcRev
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Text-content-length&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Text&quot;
)paren
op_logical_and
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Prop&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
op_plus
l_int|4
comma
l_string|&quot;-content-length&quot;
)paren
)paren
r_continue
suffix:semicolon
(brace
r_char
op_star
id|end
suffix:semicolon
r_uintmax
id|len
suffix:semicolon
id|len
op_assign
id|strtoumax
c_func
(paren
id|val
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
op_logical_neg
id|isdigit
c_func
(paren
op_star
id|val
)paren
op_logical_or
op_star
id|end
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: non-numeric length %s&quot;
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|maximum_signed_value_of_type
c_func
(paren
id|off_t
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unrepresentable length in dump: %s&quot;
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|t
op_eq
l_char|&squot;T&squot;
)paren
id|node_ctx.text_length
op_assign
(paren
id|off_t
)paren
id|len
suffix:semicolon
r_else
id|node_ctx.prop_length
op_assign
(paren
id|off_t
)paren
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
r_sizeof
(paren
l_string|&quot;Text-delta&quot;
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Text-delta&quot;
)paren
)paren
(brace
id|node_ctx.text_delta
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|val
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Prop-delta&quot;
)paren
)paren
r_continue
suffix:semicolon
id|node_ctx.prop_delta
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|val
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
l_string|&quot;Content-length&quot;
)paren
suffix:colon
r_if
c_cond
(paren
id|constcmp
c_func
(paren
id|t
comma
l_string|&quot;Content-length&quot;
)paren
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
id|t
op_assign
id|buffer_read_line
c_func
(paren
op_amp
id|input
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
id|die_short_read
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|t
)paren
id|die
c_func
(paren
l_string|&quot;invalid dump: expected blank line after content length header&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_eq
id|REV_CTX
)paren
(brace
id|read_props
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|active_ctx
op_eq
id|NODE_CTX
)paren
(brace
id|handle_node
c_func
(paren
)paren
suffix:semicolon
id|active_ctx
op_assign
id|INTERNODE_CTX
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unexpected content length header: %&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_skip_bytes
c_func
(paren
op_amp
id|input
comma
id|len
)paren
op_ne
id|len
)paren
id|die_short_read
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|buffer_ferror
c_func
(paren
op_amp
id|input
)paren
)paren
id|die_short_read
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_eq
id|NODE_CTX
)paren
id|handle_node
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_eq
id|REV_CTX
)paren
id|begin_revision
c_func
(paren
id|local_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_ctx
op_ne
id|DUMP_CTX
)paren
id|end_revision
c_func
(paren
id|notes_ref
)paren
suffix:semicolon
)brace
DECL|function|init
r_static
r_void
id|init
c_func
(paren
r_int
id|report_fd
)paren
(brace
id|fast_export_init
c_func
(paren
id|report_fd
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|dump_ctx.uuid
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|dump_ctx.url
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|rev_ctx.log
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|rev_ctx.author
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|rev_ctx.note
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|node_ctx.src
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|node_ctx.dst
comma
l_int|4096
)paren
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|reset_rev_ctx
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|reset_node_ctx
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|svndump_init
r_int
id|svndump_init
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
(brace
r_if
c_cond
(paren
id|buffer_init
c_func
(paren
op_amp
id|input
comma
id|filename
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot open %s: %s&quot;
comma
id|filename
ques
c_cond
id|filename
suffix:colon
l_string|&quot;NULL&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|init
c_func
(paren
id|REPORT_FILENO
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|svndump_init_fd
r_int
id|svndump_init_fd
c_func
(paren
r_int
id|in_fd
comma
r_int
id|back_fd
)paren
(brace
r_if
c_cond
(paren
id|buffer_fdinit
c_func
(paren
op_amp
id|input
comma
id|xdup
c_func
(paren
id|in_fd
)paren
)paren
)paren
(brace
r_return
id|error
c_func
(paren
l_string|&quot;cannot open fd %d: %s&quot;
comma
id|in_fd
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|init
c_func
(paren
id|xdup
c_func
(paren
id|back_fd
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|svndump_deinit
r_void
id|svndump_deinit
c_func
(paren
r_void
)paren
(brace
id|fast_export_deinit
c_func
(paren
)paren
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|reset_rev_ctx
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|reset_node_ctx
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|rev_ctx.log
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|rev_ctx.author
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|rev_ctx.note
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|node_ctx.src
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|node_ctx.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_deinit
c_func
(paren
op_amp
id|input
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Input error&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|stdout
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Output error&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|svndump_reset
r_void
id|svndump_reset
c_func
(paren
r_void
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|dump_ctx.uuid
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|dump_ctx.url
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|rev_ctx.log
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|rev_ctx.author
)paren
suffix:semicolon
)brace
eof
