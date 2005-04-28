macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;stdlib.h&gt;
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
(brace
r_struct
id|blob
op_star
id|ret
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|blob
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|blob
)paren
)paren
suffix:semicolon
id|created_object
c_func
(paren
id|sha1
comma
op_amp
id|ret-&gt;object
)paren
suffix:semicolon
id|ret-&gt;object.type
op_assign
id|blob_type
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|blob_type
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
id|obj-&gt;type
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
DECL|function|parse_blob
r_int
id|parse_blob
c_func
(paren
r_struct
id|blob
op_star
id|item
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.parsed
)paren
r_return
l_int|0
suffix:semicolon
id|item-&gt;object.parsed
op_assign
l_int|1
suffix:semicolon
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|item-&gt;object.sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|type
comma
id|blob_type
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Object %s not a blob&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
