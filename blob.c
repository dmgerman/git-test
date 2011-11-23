macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;blob.h&quot;
DECL|variable|blob_type
r_const
r_char
op_star
id|blob_type
op_assign
l_string|&quot;blob&quot;
suffix:semicolon
DECL|function|lookup_blob
r_struct
id|blob
op_star
id|lookup_blob
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
id|create_object
c_func
(paren
id|sha1
comma
id|OBJ_BLOB
comma
id|alloc_blob_node
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;type
)paren
id|obj-&gt;type
op_assign
id|OBJ_BLOB
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|OBJ_BLOB
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Object %s is a %s, not a blob&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_typename
(paren
id|obj-&gt;type
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_struct
id|blob
op_star
)paren
id|obj
suffix:semicolon
)brace
DECL|function|parse_blob_buffer
r_int
id|parse_blob_buffer
c_func
(paren
r_struct
id|blob
op_star
id|item
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
id|item-&gt;object.parsed
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
