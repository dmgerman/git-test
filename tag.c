macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
DECL|macro|PGP_SIGNATURE
mdefine_line|#define PGP_SIGNATURE &quot;-----BEGIN PGP SIGNATURE-----&quot;
DECL|macro|PGP_MESSAGE
mdefine_line|#define PGP_MESSAGE &quot;-----BEGIN PGP MESSAGE-----&quot;
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
r_if
c_cond
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
id|tagged
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
r_else
id|o
op_assign
l_int|NULL
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
DECL|function|parse_tag_date
r_static
r_int
r_int
id|parse_tag_date
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|tail
)paren
(brace
r_const
r_char
op_star
id|dateptr
suffix:semicolon
r_while
c_loop
(paren
id|buf
OL
id|tail
op_logical_and
op_star
id|buf
op_increment
op_ne
l_char|&squot;&gt;&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_ge
id|tail
)paren
r_return
l_int|0
suffix:semicolon
id|dateptr
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|buf
OL
id|tail
op_logical_and
op_star
id|buf
op_increment
op_ne
l_char|&squot;&bslash;n&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_ge
id|tail
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* dateptr &lt; buf &amp;&amp; buf[-1] == &squot;&bslash;n&squot;, so strtoul will stop at buf-1 */
r_return
id|strtoul
c_func
(paren
id|dateptr
comma
l_int|NULL
comma
l_int|10
)paren
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
r_const
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
r_char
id|sha1
(braket
l_int|20
)braket
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
id|bufptr
op_assign
id|data
suffix:semicolon
r_const
r_char
op_star
id|tail
op_assign
id|bufptr
op_plus
id|size
suffix:semicolon
r_const
r_char
op_star
id|nl
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
id|bufptr
comma
l_int|7
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|bufptr
op_plus
l_int|7
comma
id|sha1
)paren
op_logical_or
id|bufptr
(braket
l_int|47
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|bufptr
op_add_assign
l_int|48
suffix:semicolon
multiline_comment|/* &quot;object &quot; + sha1 + &quot;&bslash;n&quot; */
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|bufptr
comma
l_string|&quot;type &quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|bufptr
op_add_assign
l_int|5
suffix:semicolon
id|nl
op_assign
id|memchr
c_func
(paren
id|bufptr
comma
l_char|&squot;&bslash;n&squot;
comma
id|tail
id|bufptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nl
op_logical_or
r_sizeof
(paren
id|type
)paren
op_le
(paren
id|nl
id|bufptr
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|strncpy
c_func
(paren
id|type
comma
id|bufptr
comma
id|nl
id|bufptr
)paren
suffix:semicolon
id|type
(braket
id|nl
id|bufptr
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|bufptr
op_assign
id|nl
op_plus
l_int|1
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
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|bufptr
comma
l_string|&quot;tag &quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|bufptr
op_add_assign
l_int|4
suffix:semicolon
id|nl
op_assign
id|memchr
c_func
(paren
id|bufptr
comma
l_char|&squot;&bslash;n&squot;
comma
id|tail
id|bufptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nl
)paren
r_return
l_int|1
suffix:semicolon
id|item-&gt;tag
op_assign
id|xmemdupz
c_func
(paren
id|bufptr
comma
id|nl
id|bufptr
)paren
suffix:semicolon
id|bufptr
op_assign
id|nl
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|bufptr
comma
l_string|&quot;tagger &quot;
)paren
)paren
id|item-&gt;date
op_assign
id|parse_tag_date
c_func
(paren
id|bufptr
comma
id|tail
)paren
suffix:semicolon
r_else
id|item-&gt;date
op_assign
l_int|0
suffix:semicolon
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
DECL|function|parse_signature
r_int
id|parse_signature
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_char
op_star
id|eol
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
id|size
op_logical_and
id|prefixcmp
c_func
(paren
id|buf
op_plus
id|len
comma
id|PGP_SIGNATURE
)paren
op_logical_and
id|prefixcmp
c_func
(paren
id|buf
op_plus
id|len
comma
id|PGP_MESSAGE
)paren
)paren
(brace
id|eol
op_assign
id|memchr
c_func
(paren
id|buf
op_plus
id|len
comma
l_char|&squot;&bslash;n&squot;
comma
id|size
id|len
)paren
suffix:semicolon
id|len
op_add_assign
id|eol
ques
c_cond
id|eol
(paren
id|buf
op_plus
id|len
)paren
op_plus
l_int|1
suffix:colon
id|size
id|len
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
eof
