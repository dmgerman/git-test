multiline_comment|/*&n; * Parse and rearrange a svnadmin dump.&n; * Create the dump with:&n; * svnadmin dump --incremental -r&lt;startrev&gt;:&lt;endrev&gt; &lt;repository&gt; &gt;outfile&n; *&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;repo_tree.h&quot;
macro_line|#include &quot;fast_export.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;obj_pool.h&quot;
macro_line|#include &quot;string_pool.h&quot;
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
DECL|macro|DUMP_CTX
mdefine_line|#define DUMP_CTX 0
DECL|macro|REV_CTX
mdefine_line|#define REV_CTX  1
DECL|macro|NODE_CTX
mdefine_line|#define NODE_CTX 2
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
DECL|member|srcMode
DECL|member|mark
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
id|srcMode
comma
id|mark
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
id|node_ctx.srcMode
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
id|node_ctx.mark
op_assign
l_int|0
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
id|len
suffix:semicolon
r_uint32
id|key
op_assign
op_complement
l_int|0
suffix:semicolon
r_char
op_star
id|val
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|t
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
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|t
comma
l_string|&quot;K &quot;
comma
l_int|2
)paren
)paren
(brace
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
id|key
op_assign
id|pool_intern
c_func
(paren
id|buffer_read_string
c_func
(paren
id|len
)paren
)paren
suffix:semicolon
id|buffer_read_line
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|t
comma
l_string|&quot;V &quot;
comma
l_int|2
)paren
)paren
(brace
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
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_log
)paren
(brace
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Invalid timestamp: %s&bslash;n&quot;
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
)paren
(brace
id|node_ctx.type
op_assign
id|REPO_MODE_EXE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|key
op_eq
id|keys.svn_special
)paren
(brace
id|node_ctx.type
op_assign
id|REPO_MODE_LNK
suffix:semicolon
)brace
id|key
op_assign
op_complement
l_int|0
suffix:semicolon
id|buffer_read_line
c_func
(paren
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
r_if
c_cond
(paren
id|node_ctx.text_delta
op_logical_or
id|node_ctx.prop_delta
)paren
id|die
c_func
(paren
l_string|&quot;text and property deltas not supported&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node_ctx.propLength
op_ne
id|LENGTH_UNKNOWN
op_logical_and
id|node_ctx.propLength
)paren
id|read_props
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node_ctx.srcRev
)paren
id|node_ctx.srcMode
op_assign
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
id|node_ctx.textLength
op_ne
id|LENGTH_UNKNOWN
op_logical_and
id|node_ctx.type
op_ne
id|REPO_MODE_DIR
)paren
id|node_ctx.mark
op_assign
id|next_blob_mark
c_func
(paren
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
id|repo_delete
c_func
(paren
id|node_ctx.dst
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_CHANGE
op_logical_or
id|node_ctx.action
op_eq
id|NODEACT_REPLACE
)paren
(brace
r_if
c_cond
(paren
id|node_ctx.action
op_eq
id|NODEACT_REPLACE
op_logical_and
id|node_ctx.type
op_eq
id|REPO_MODE_DIR
)paren
id|repo_replace
c_func
(paren
id|node_ctx.dst
comma
id|node_ctx.mark
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|node_ctx.propLength
op_ne
id|LENGTH_UNKNOWN
)paren
id|repo_modify
c_func
(paren
id|node_ctx.dst
comma
id|node_ctx.type
comma
id|node_ctx.mark
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|node_ctx.textLength
op_ne
id|LENGTH_UNKNOWN
)paren
id|node_ctx.srcMode
op_assign
id|repo_replace
c_func
(paren
id|node_ctx.dst
comma
id|node_ctx.mark
)paren
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
id|node_ctx.srcRev
op_logical_and
id|node_ctx.propLength
op_ne
id|LENGTH_UNKNOWN
)paren
id|repo_modify
c_func
(paren
id|node_ctx.dst
comma
id|node_ctx.type
comma
id|node_ctx.mark
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|node_ctx.srcRev
op_logical_and
id|node_ctx.textLength
op_ne
id|LENGTH_UNKNOWN
)paren
id|node_ctx.srcMode
op_assign
id|repo_replace
c_func
(paren
id|node_ctx.dst
comma
id|node_ctx.mark
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|node_ctx.type
op_eq
id|REPO_MODE_DIR
op_logical_and
op_logical_neg
id|node_ctx.srcRev
)paren
op_logical_or
id|node_ctx.textLength
op_ne
id|LENGTH_UNKNOWN
)paren
id|repo_add
c_func
(paren
id|node_ctx.dst
comma
id|node_ctx.type
comma
id|node_ctx.mark
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node_ctx.propLength
op_eq
id|LENGTH_UNKNOWN
op_logical_and
id|node_ctx.srcMode
)paren
id|node_ctx.type
op_assign
id|node_ctx.srcMode
suffix:semicolon
r_if
c_cond
(paren
id|node_ctx.mark
)paren
id|fast_export_blob
c_func
(paren
id|node_ctx.type
comma
id|node_ctx.mark
comma
id|node_ctx.textLength
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|node_ctx.textLength
op_ne
id|LENGTH_UNKNOWN
)paren
id|buffer_skip_bytes
c_func
(paren
id|node_ctx.textLength
)paren
suffix:semicolon
)brace
DECL|function|handle_revision
r_static
r_void
id|handle_revision
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
id|repo_commit
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
l_string|&quot;expected svn dump format version &lt;= 3, found %d&quot;
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
op_ne
id|DUMP_CTX
)paren
id|handle_revision
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
id|REV_CTX
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
op_ne
id|DUMP_CTX
)paren
id|handle_revision
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
id|repo_init
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
id|repo_reset
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
id|buffer_reset
c_func
(paren
)paren
suffix:semicolon
id|repo_reset
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
)brace
eof
