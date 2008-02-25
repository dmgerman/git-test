macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
DECL|variable|tag_type
r_const
r_char
op_star
id|tag_type
op_assign
l_string|&quot;tag&quot;
suffix:semicolon
DECL|function|deref_tag
r_struct
id|object
op_star
id|deref_tag
c_func
(paren
r_struct
id|object
op_star
id|o
comma
r_const
r_char
op_star
id|warn
comma
r_int
id|warnlen
)paren
(brace
r_while
c_loop
(paren
id|o
op_logical_and
id|o-&gt;type
op_eq
id|OBJ_TAG
)paren
id|o
op_assign
id|parse_object
c_func
(paren
(paren
(paren
r_struct
id|tag
op_star
)paren
id|o
)paren
op_member_access_from_pointer
id|tagged-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_and
id|warn
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|warnlen
)paren
id|warnlen
op_assign
id|strlen
c_func
(paren
id|warn
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;missing object referenced by &squot;%.*s&squot;&quot;
comma
id|warnlen
comma
id|warn
)paren
suffix:semicolon
)brace
r_return
id|o
suffix:semicolon
)brace
DECL|function|lookup_tag
r_struct
id|tag
op_star
id|lookup_tag
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
id|OBJ_TAG
comma
id|alloc_tag_node
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
id|OBJ_TAG
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|OBJ_TAG
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Object %s is a %s, not a tag&quot;
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
id|tag
op_star
)paren
id|obj
suffix:semicolon
)brace
DECL|function|parse_tag_buffer
r_int
id|parse_tag_buffer
c_func
(paren
r_struct
id|tag
op_star
id|item
comma
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|typelen
comma
id|taglen
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|type_line
comma
op_star
id|tag_line
comma
op_star
id|sig_line
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|start
op_assign
id|data
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
r_if
c_cond
(paren
id|size
OL
l_int|64
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
l_string|&quot;object &quot;
comma
id|data
comma
l_int|7
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
(paren
r_char
op_star
)paren
id|data
op_plus
l_int|7
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|type_line
op_assign
(paren
r_char
op_star
)paren
id|data
op_plus
l_int|48
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
l_string|&quot;&bslash;ntype &quot;
comma
id|type_line
op_minus
l_int|1
comma
l_int|6
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|tag_line
op_assign
id|memchr
c_func
(paren
id|type_line
comma
l_char|&squot;&bslash;n&squot;
comma
id|size
(paren
id|type_line
id|start
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tag_line
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;tag &quot;
comma
op_increment
id|tag_line
comma
l_int|4
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|sig_line
op_assign
id|memchr
c_func
(paren
id|tag_line
comma
l_char|&squot;&bslash;n&squot;
comma
id|size
(paren
id|tag_line
id|start
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sig_line
)paren
r_return
l_int|1
suffix:semicolon
id|sig_line
op_increment
suffix:semicolon
id|typelen
op_assign
id|tag_line
id|type_line
id|strlen
c_func
(paren
l_string|&quot;type &bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|typelen
op_ge
l_int|20
)paren
r_return
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|type
comma
id|type_line
op_plus
l_int|5
comma
id|typelen
)paren
suffix:semicolon
id|type
(braket
id|typelen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|taglen
op_assign
id|sig_line
id|tag_line
id|strlen
c_func
(paren
l_string|&quot;tag &bslash;n&quot;
)paren
suffix:semicolon
id|item-&gt;tag
op_assign
id|xmemdupz
c_func
(paren
id|tag_line
op_plus
l_int|4
comma
id|taglen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|blob_type
)paren
)paren
(brace
id|item-&gt;tagged
op_assign
op_amp
id|lookup_blob
c_func
(paren
id|sha1
)paren
op_member_access_from_pointer
id|object
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
id|type
comma
id|tree_type
)paren
)paren
(brace
id|item-&gt;tagged
op_assign
op_amp
id|lookup_tree
c_func
(paren
id|sha1
)paren
op_member_access_from_pointer
id|object
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
id|type
comma
id|commit_type
)paren
)paren
(brace
id|item-&gt;tagged
op_assign
op_amp
id|lookup_commit
c_func
(paren
id|sha1
)paren
op_member_access_from_pointer
id|object
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
id|type
comma
id|tag_type
)paren
)paren
(brace
id|item-&gt;tagged
op_assign
op_amp
id|lookup_tag
c_func
(paren
id|sha1
)paren
op_member_access_from_pointer
id|object
suffix:semicolon
)brace
r_else
(brace
id|error
c_func
(paren
l_string|&quot;Unknown type %s&quot;
comma
id|type
)paren
suffix:semicolon
id|item-&gt;tagged
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_tag
r_int
id|parse_tag
c_func
(paren
r_struct
id|tag
op_star
id|item
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.parsed
)paren
r_return
l_int|0
suffix:semicolon
id|data
op_assign
id|read_sha1_file
c_func
(paren
id|item-&gt;object.sha1
comma
op_amp
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
id|data
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
id|type
op_ne
id|OBJ_TAG
)paren
(brace
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Object %s not a tag&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|parse_tag_buffer
c_func
(paren
id|item
comma
id|data
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
