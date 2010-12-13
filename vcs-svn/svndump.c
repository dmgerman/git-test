multiline_comment|/*&n; * Parse and rearrange a svnadmin dump.&n; * Create the dump with:&n; * svnadmin dump --incremental -r&lt;startrev&gt;:&lt;endrev&gt; &lt;repository&gt; &gt;outfile&n; *&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;repo_tree.h&quot;
macro_line|#include &quot;fast_export.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;obj_pool.h&quot;
macro_line|#include &quot;string_pool.h&quot;
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
DECL|macro|LENGTH_UNKNOWN
mdefine_line|#define LENGTH_UNKNOWN (~0)
DECL|macro|DATE_RFC2822_LEN
mdefine_line|#define DATE_RFC2822_LEN 31
multiline_comment|/* Create memory pool for log messages */
id|obj_pool_gen
c_func
(paren
id|log
comma
r_char
comma
l_int|4096
)paren
DECL|variable|input
r_static
r_struct
id|line_buffer
id|input
op_assign
id|LINE_BUFFER_INIT
suffix:semicolon
DECL|macro|REPORT_FILENO
mdefine_line|#define REPORT_FILENO 3
DECL|function|log_copy
r_static
r_char
op_star
id|log_copy
c_func
(paren
r_uint32
id|length
comma
r_const
r_char
op_star
id|log
)paren
(brace
r_char
op_star
id|buffer
suffix:semicolon
id|log_free
c_func
(paren
id|log_pool.size
)paren
suffix:semicolon
id|buffer
op_assign
id|log_pointer
c_func
(paren
id|log_alloc
c_func
(paren
id|length
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|buffer
comma
id|log
comma
id|length
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|action
DECL|member|propLength
DECL|member|textLength
DECL|member|srcRev
DECL|member|type
r_uint32
id|action
comma
id|propLength
comma
id|textLength
comma
id|srcRev
comma
id|type
suffix:semicolon
DECL|member|src
DECL|member|dst
r_uint32
id|src
(braket
id|REPO_MAX_PATH_DEPTH
)braket
comma
id|dst
(braket
id|REPO_MAX_PATH_DEPTH
)braket
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
DECL|member|author
r_uint32
id|revision
comma
id|author
suffix:semicolon
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
DECL|member|log
r_char
op_star
id|log
suffix:semicolon
DECL|variable|rev_ctx
)brace
id|rev_ctx
suffix:semicolon
r_static
r_struct
(brace
DECL|member|version
DECL|member|uuid
DECL|member|url
r_uint32
id|version
comma
id|uuid
comma
id|url
suffix:semicolon
DECL|variable|dump_ctx
)brace
id|dump_ctx
suffix:semicolon
r_static
r_struct
(brace
DECL|member|svn_log
DECL|member|svn_author
DECL|member|svn_date
DECL|member|svn_executable
DECL|member|svn_special
DECL|member|uuid
r_uint32
id|svn_log
comma
id|svn_author
comma
id|svn_date
comma
id|svn_executable
comma
id|svn_special
comma
id|uuid
comma
DECL|member|revision_number
DECL|member|node_path
DECL|member|node_kind
DECL|member|node_action
id|revision_number
comma
id|node_path
comma
id|node_kind
comma
id|node_action
comma
DECL|member|node_copyfrom_path
DECL|member|node_copyfrom_rev
DECL|member|text_content_length
id|node_copyfrom_path
comma
id|node_copyfrom_rev
comma
id|text_content_length
comma
DECL|member|prop_content_length
DECL|member|content_length
DECL|member|svn_fs_dump_format_version
id|prop_content_length
comma
id|content_length
comma
id|svn_fs_dump_format_version
comma
multiline_comment|/* version 3 format */
DECL|member|text_delta
DECL|member|prop_delta
id|text_delta
comma
id|prop_delta
suffix:semicolon
DECL|variable|keys
)brace
id|keys
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
id|node_ctx.propLength
op_assign
id|LENGTH_UNKNOWN
suffix:semicolon
id|node_ctx.textLength
op_assign
id|LENGTH_UNKNOWN
suffix:semicolon
id|node_ctx.src
(braket
l_int|0
)braket
op_assign
op_complement
l_int|0
suffix:semicolon
id|node_ctx.srcRev
op_assign
l_int|0
suffix:semicolon
id|pool_tok_seq
c_func
(paren
id|REPO_MAX_PATH_DEPTH
comma
id|node_ctx.dst
comma
l_string|&quot;/&quot;
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
id|rev_ctx.log
op_assign
l_int|NULL
suffix:semicolon
id|rev_ctx.author
op_assign
op_complement
l_int|0
suffix:semicolon
)brace
DECL|function|reset_dump_ctx
r_static
r_void
id|reset_dump_ctx
c_func
(paren
r_uint32
id|url
)paren
(brace
id|dump_ctx.url
op_assign
id|url
suffix:semicolon
id|dump_ctx.version
op_assign
l_int|1
suffix:semicolon
id|dump_ctx.uuid
op_assign
op_complement
l_int|0
suffix:semicolon
)brace
DECL|function|init_keys
r_static
r_void
id|init_keys
c_func
(paren
r_void
)paren
(brace
id|keys.svn_log
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;svn:log&quot;
)paren
suffix:semicolon
id|keys.svn_author
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;svn:author&quot;
)paren
suffix:semicolon
id|keys.svn_date
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;svn:date&quot;
)paren
suffix:semicolon
id|keys.svn_executable
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;svn:executable&quot;
)paren
suffix:semicolon
id|keys.svn_special
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;svn:special&quot;
)paren
suffix:semicolon
id|keys.uuid
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;UUID&quot;
)paren
suffix:semicolon
id|keys.revision_number
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Revision-number&quot;
)paren
suffix:semicolon
id|keys.node_path
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Node-path&quot;
)paren
suffix:semicolon
id|keys.node_kind
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Node-kind&quot;
)paren
suffix:semicolon
id|keys.node_action
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Node-action&quot;
)paren
suffix:semicolon
id|keys.node_copyfrom_path
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Node-copyfrom-path&quot;
)paren
suffix:semicolon
id|keys.node_copyfrom_rev
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Node-copyfrom-rev&quot;
)paren
suffix:semicolon
id|keys.text_content_length
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Text-content-length&quot;
)paren
suffix:semicolon
id|keys.prop_content_length
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Prop-content-length&quot;
)paren
suffix:semicolon
id|keys.content_length
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Content-length&quot;
)paren
suffix:semicolon
id|keys.svn_fs_dump_format_version
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;SVN-fs-dump-format-version&quot;
)paren
suffix:semicolon
multiline_comment|/* version 3 format (Subversion 1.1.0) */
id|keys.text_delta
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Text-delta&quot;
)paren
suffix:semicolon
id|keys.prop_delta
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;Prop-delta&quot;
)paren
suffix:semicolon
)brace
DECL|function|handle_property
r_static
r_void
id|handle_property
c_func
(paren
r_uint32
id|key
comma
r_const
r_char
op_star
id|val
comma
r_uint32
id|len
comma
r_uint32
op_star
id|type_set
)paren
(brace
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_log
)paren
(brace
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
multiline_comment|/* Value length excludes terminating nul. */
id|rev_ctx.log
op_assign
id|log_copy
c_func
(paren
id|len
op_plus
l_int|1
comma
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_author
)paren
(brace
id|rev_ctx.author
op_assign
id|pool_intern
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_date
)paren
(brace
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
id|val
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
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_executable
op_logical_or
id|key
op_eq
id|keys.svn_special
)paren
(brace
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
id|key
op_eq
id|keys.svn_executable
ques
c_cond
id|REPO_MODE_EXE
suffix:colon
id|REPO_MODE_LNK
suffix:semicolon
)brace
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
r_uint32
id|key
op_assign
op_complement
l_int|0
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
op_star
id|val
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
l_string|&quot;invalid property line: %s&bslash;n&quot;
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
id|val
op_assign
id|buffer_read_string
c_func
(paren
op_amp
id|input
comma
id|len
)paren
suffix:semicolon
id|buffer_skip_bytes
c_func
(paren
op_amp
id|input
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Discard trailing newline. */
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_char|&squot;K&squot;
suffix:colon
id|key
op_assign
id|pool_intern
c_func
(paren
id|val
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
id|key
op_assign
id|pool_intern
c_func
(paren
id|val
)paren
suffix:semicolon
id|val
op_assign
l_int|NULL
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_char|&squot;V&squot;
suffix:colon
id|handle_property
c_func
(paren
id|key
comma
id|val
comma
id|len
comma
op_amp
id|type_set
)paren
suffix:semicolon
id|key
op_assign
op_complement
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;invalid property line: %s&bslash;n&quot;
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
id|node_ctx.propLength
op_ne
id|LENGTH_UNKNOWN
suffix:semicolon
r_const
r_int
id|have_text
op_assign
id|node_ctx.textLength
op_ne
id|LENGTH_UNKNOWN
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
r_if
c_cond
(paren
id|node_ctx.text_delta
)paren
id|die
c_func
(paren
l_string|&quot;text deltas not supported&quot;
)paren
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
r_return
id|repo_delete
c_func
(paren
id|node_ctx.dst
)paren
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
id|node_ctx.dst
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
id|node_ctx.src
comma
id|node_ctx.dst
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
op_complement
op_star
id|node_ctx.dst
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
id|node_ctx.dst
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
id|node_ctx.propLength
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
id|REPO_MAX_PATH_DEPTH
comma
id|node_ctx.dst
comma
id|node_ctx.type
comma
id|old_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fast_export_modify
c_func
(paren
id|REPO_MAX_PATH_DEPTH
comma
id|node_ctx.dst
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
id|node_ctx.textLength
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
r_void
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
id|rev_ctx.author
comma
id|rev_ctx.log
comma
id|dump_ctx.uuid
comma
id|dump_ctx.url
comma
id|rev_ctx.timestamp
)paren
suffix:semicolon
)brace
DECL|function|end_revision
r_static
r_void
id|end_revision
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rev_ctx.revision
)paren
id|fast_export_end_commit
c_func
(paren
id|rev_ctx.revision
)paren
suffix:semicolon
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
r_uint32
id|key
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
id|pool_intern
c_func
(paren
id|url
)paren
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
id|strstr
c_func
(paren
id|t
comma
l_string|&quot;: &quot;
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
op_star
id|val
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|val
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|key
op_assign
id|pool_intern
c_func
(paren
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_fs_dump_format_version
)paren
(brace
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.uuid
)paren
(brace
id|dump_ctx.uuid
op_assign
id|pool_intern
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.revision_number
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.node_path
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.node_kind
)paren
(brace
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.node_action
)paren
(brace
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.node_copyfrom_path
)paren
(brace
id|pool_tok_seq
c_func
(paren
id|REPO_MAX_PATH_DEPTH
comma
id|node_ctx.src
comma
l_string|&quot;/&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.node_copyfrom_rev
)paren
(brace
id|node_ctx.srcRev
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.text_content_length
)paren
(brace
id|node_ctx.textLength
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.prop_content_length
)paren
(brace
id|node_ctx.propLength
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.text_delta
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.prop_delta
)paren
(brace
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
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.content_length
)paren
(brace
id|len
op_assign
id|atoi
c_func
(paren
id|val
)paren
suffix:semicolon
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
id|buffer_skip_bytes
c_func
(paren
op_amp
id|input
comma
id|len
)paren
suffix:semicolon
)brace
)brace
)brace
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
)paren
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
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|fast_export_init
c_func
(paren
id|REPORT_FILENO
)paren
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
op_complement
l_int|0
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
id|init_keys
c_func
(paren
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
id|log_reset
c_func
(paren
)paren
suffix:semicolon
id|fast_export_deinit
c_func
(paren
)paren
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
op_complement
l_int|0
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
id|log_reset
c_func
(paren
)paren
suffix:semicolon
id|fast_export_reset
c_func
(paren
)paren
suffix:semicolon
id|buffer_reset
c_func
(paren
op_amp
id|input
)paren
suffix:semicolon
id|reset_dump_ctx
c_func
(paren
op_complement
l_int|0
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
)brace
eof
