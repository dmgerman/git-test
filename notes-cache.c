macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;notes-cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|function|notes_cache_match_validity
r_static
r_int
id|notes_cache_match_validity
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_char
op_star
id|validity
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
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|pretty_print_context
id|pretty_ctx
suffix:semicolon
r_struct
id|strbuf
id|msg
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|read_ref
c_func
(paren
id|ref
comma
id|sha1
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pretty_ctx
comma
l_int|0
comma
r_sizeof
(paren
id|pretty_ctx
)paren
)paren
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
l_string|&quot;%s&quot;
comma
op_amp
id|msg
comma
op_amp
id|pretty_ctx
)paren
suffix:semicolon
id|strbuf_trim
c_func
(paren
op_amp
id|msg
)paren
suffix:semicolon
id|ret
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|msg.buf
comma
id|validity
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|msg
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|notes_cache_init
r_void
id|notes_cache_init
c_func
(paren
r_struct
id|notes_cache
op_star
id|c
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|validity
)paren
(brace
r_struct
id|strbuf
id|ref
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|c
)paren
)paren
suffix:semicolon
id|c-&gt;validity
op_assign
id|xstrdup
c_func
(paren
id|validity
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|ref
comma
l_string|&quot;refs/notes/%s&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|notes_cache_match_validity
c_func
(paren
id|ref.buf
comma
id|validity
)paren
)paren
id|flags
op_assign
id|NOTES_INIT_EMPTY
suffix:semicolon
id|init_notes
c_func
(paren
op_amp
id|c-&gt;tree
comma
id|ref.buf
comma
id|combine_notes_overwrite
comma
id|flags
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|ref
)paren
suffix:semicolon
)brace
DECL|function|notes_cache_write
r_int
id|notes_cache_write
c_func
(paren
r_struct
id|notes_cache
op_star
id|c
)paren
(brace
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
op_logical_neg
id|c-&gt;tree.initialized
op_logical_or
op_logical_neg
id|c-&gt;tree.ref
op_logical_or
op_logical_neg
op_star
id|c-&gt;tree.ref
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;tree.dirty
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|write_notes_tree
c_func
(paren
op_amp
id|c-&gt;tree
comma
id|tree_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|commit_tree
c_func
(paren
id|c-&gt;validity
comma
id|tree_sha1
comma
l_int|NULL
comma
id|commit_sha1
comma
l_int|NULL
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|update_ref
c_func
(paren
l_string|&quot;update notes cache&quot;
comma
id|c-&gt;tree.ref
comma
id|commit_sha1
comma
l_int|NULL
comma
l_int|0
comma
id|QUIET_ON_ERR
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|notes_cache_get
r_char
op_star
id|notes_cache_get
c_func
(paren
r_struct
id|notes_cache
op_star
id|c
comma
r_int
r_char
id|key_sha1
(braket
l_int|20
)braket
comma
r_int
op_star
id|outsize
)paren
(brace
r_const
r_int
r_char
op_star
id|value_sha1
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|value_sha1
op_assign
id|get_note
c_func
(paren
op_amp
id|c-&gt;tree
comma
id|key_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value_sha1
)paren
r_return
l_int|NULL
suffix:semicolon
id|value
op_assign
id|read_sha1_file
c_func
(paren
id|value_sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
op_star
id|outsize
op_assign
id|size
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|notes_cache_put
r_int
id|notes_cache_put
c_func
(paren
r_struct
id|notes_cache
op_star
id|c
comma
r_int
r_char
id|key_sha1
(braket
l_int|20
)braket
comma
r_const
r_char
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_int
r_char
id|value_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|data
comma
id|size
comma
l_string|&quot;blob&quot;
comma
id|value_sha1
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|add_note
c_func
(paren
op_amp
id|c-&gt;tree
comma
id|key_sha1
comma
id|value_sha1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
