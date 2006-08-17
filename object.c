macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
DECL|variable|obj_hash
r_static
r_struct
id|object
op_star
op_star
id|obj_hash
suffix:semicolon
DECL|variable|nr_objs
DECL|variable|obj_hash_size
r_static
r_int
id|nr_objs
comma
id|obj_hash_size
suffix:semicolon
DECL|function|get_max_object_index
r_int
r_int
id|get_max_object_index
c_func
(paren
r_void
)paren
(brace
r_return
id|obj_hash_size
suffix:semicolon
)brace
DECL|function|get_indexed_object
r_struct
id|object
op_star
id|get_indexed_object
c_func
(paren
r_int
r_int
id|idx
)paren
(brace
r_return
id|obj_hash
(braket
id|idx
)braket
suffix:semicolon
)brace
DECL|variable|type_names
r_const
r_char
op_star
id|type_names
(braket
)braket
op_assign
(brace
l_string|&quot;none&quot;
comma
l_string|&quot;commit&quot;
comma
l_string|&quot;tree&quot;
comma
l_string|&quot;blob&quot;
comma
l_string|&quot;tag&quot;
comma
l_string|&quot;bad type 5&quot;
comma
l_string|&quot;bad type 6&quot;
comma
l_string|&quot;delta&quot;
comma
l_string|&quot;bad&quot;
comma
)brace
suffix:semicolon
DECL|function|hash_obj
r_static
r_int
r_int
id|hash_obj
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|hash
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|obj-&gt;sha1
suffix:semicolon
r_return
id|hash
op_mod
id|n
suffix:semicolon
)brace
DECL|function|insert_obj_hash
r_static
r_void
id|insert_obj_hash
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_struct
id|object
op_star
op_star
id|hash
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|j
op_assign
id|hash_obj
c_func
(paren
id|obj
comma
id|size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|hash
(braket
id|j
)braket
)paren
(brace
id|j
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ge
id|size
)paren
id|j
op_assign
l_int|0
suffix:semicolon
)brace
id|hash
(braket
id|j
)braket
op_assign
id|obj
suffix:semicolon
)brace
DECL|function|hashtable_index
r_static
r_int
id|hashtable_index
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|i
comma
id|sha1
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
id|i
op_mod
id|obj_hash_size
)paren
suffix:semicolon
)brace
DECL|function|lookup_object
r_struct
id|object
op_star
id|lookup_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_hash
)paren
r_return
l_int|NULL
suffix:semicolon
id|i
op_assign
id|hashtable_index
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|obj
op_assign
id|obj_hash
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|obj-&gt;sha1
)paren
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|obj_hash_size
)paren
id|i
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|obj
suffix:semicolon
)brace
DECL|function|grow_object_hash
r_static
r_void
id|grow_object_hash
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|new_hash_size
op_assign
id|obj_hash_size
OL
l_int|32
ques
c_cond
l_int|32
suffix:colon
l_int|2
op_star
id|obj_hash_size
suffix:semicolon
r_struct
id|object
op_star
op_star
id|new_hash
suffix:semicolon
id|new_hash
op_assign
id|calloc
c_func
(paren
id|new_hash_size
comma
r_sizeof
(paren
r_struct
id|object
op_star
)paren
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
id|obj_hash_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|obj_hash
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_continue
suffix:semicolon
id|insert_obj_hash
c_func
(paren
id|obj
comma
id|new_hash
comma
id|new_hash_size
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|obj_hash
)paren
suffix:semicolon
id|obj_hash
op_assign
id|new_hash
suffix:semicolon
id|obj_hash_size
op_assign
id|new_hash_size
suffix:semicolon
)brace
DECL|function|created_object
r_void
id|created_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|object
op_star
id|obj
)paren
(brace
id|obj-&gt;parsed
op_assign
l_int|0
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|0
suffix:semicolon
id|obj-&gt;type
op_assign
id|OBJ_NONE
suffix:semicolon
id|obj-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|obj-&gt;sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_hash_size
l_int|1
op_le
id|nr_objs
op_star
l_int|2
)paren
id|grow_object_hash
c_func
(paren
)paren
suffix:semicolon
id|insert_obj_hash
c_func
(paren
id|obj
comma
id|obj_hash
comma
id|obj_hash_size
)paren
suffix:semicolon
id|nr_objs
op_increment
suffix:semicolon
)brace
DECL|function|lookup_object_type
r_struct
id|object
op_star
id|lookup_object_type
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|type
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|type
)paren
(brace
r_return
id|lookup_unknown_object
c_func
(paren
id|sha1
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
id|type
comma
id|blob_type
)paren
)paren
(brace
r_return
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
r_return
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
r_return
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
r_return
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
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|union|any_object
r_union
id|any_object
(brace
DECL|member|object
r_struct
id|object
id|object
suffix:semicolon
DECL|member|commit
r_struct
id|commit
id|commit
suffix:semicolon
DECL|member|tree
r_struct
id|tree
id|tree
suffix:semicolon
DECL|member|blob
r_struct
id|blob
id|blob
suffix:semicolon
DECL|member|tag
r_struct
id|tag
id|tag
suffix:semicolon
)brace
suffix:semicolon
DECL|function|lookup_unknown_object
r_struct
id|object
op_star
id|lookup_unknown_object
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
(brace
r_union
id|any_object
op_star
id|ret
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ret
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
id|OBJ_NONE
suffix:semicolon
r_return
op_amp
id|ret-&gt;object
suffix:semicolon
)brace
r_return
id|obj
suffix:semicolon
)brace
DECL|function|parse_object
r_struct
id|object
op_star
id|parse_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
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
id|buffer
)paren
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_if
c_cond
(paren
id|check_sha1_signature
c_func
(paren
id|sha1
comma
id|buffer
comma
id|size
comma
id|type
)paren
OL
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;sha1 mismatch %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
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
r_struct
id|blob
op_star
id|blob
op_assign
id|lookup_blob
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|parse_blob_buffer
c_func
(paren
id|blob
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
op_amp
id|blob-&gt;object
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
r_struct
id|tree
op_star
id|tree
op_assign
id|lookup_tree
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|obj
op_assign
op_amp
id|tree-&gt;object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;object.parsed
)paren
(brace
id|parse_tree_buffer
c_func
(paren
id|tree
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
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
r_struct
id|commit
op_star
id|commit
op_assign
id|lookup_commit
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|parse_commit_buffer
c_func
(paren
id|commit
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;buffer
)paren
(brace
id|commit-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|obj
op_assign
op_amp
id|commit-&gt;object
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
r_struct
id|tag
op_star
id|tag
op_assign
id|lookup_tag
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|parse_tag_buffer
c_func
(paren
id|tag
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
op_amp
id|tag-&gt;object
suffix:semicolon
)brace
r_else
(brace
id|obj
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|object_list_insert
r_struct
id|object_list
op_star
id|object_list_insert
c_func
(paren
r_struct
id|object
op_star
id|item
comma
r_struct
id|object_list
op_star
op_star
id|list_p
)paren
(brace
r_struct
id|object_list
op_star
id|new_list
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|object_list
)paren
)paren
suffix:semicolon
id|new_list-&gt;item
op_assign
id|item
suffix:semicolon
id|new_list-&gt;next
op_assign
op_star
id|list_p
suffix:semicolon
op_star
id|list_p
op_assign
id|new_list
suffix:semicolon
r_return
id|new_list
suffix:semicolon
)brace
DECL|function|object_list_append
r_void
id|object_list_append
c_func
(paren
r_struct
id|object
op_star
id|item
comma
r_struct
id|object_list
op_star
op_star
id|list_p
)paren
(brace
r_while
c_loop
(paren
op_star
id|list_p
)paren
(brace
id|list_p
op_assign
op_amp
(paren
(paren
op_star
id|list_p
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
op_star
id|list_p
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|object_list
)paren
)paren
suffix:semicolon
(paren
op_star
id|list_p
)paren
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
(paren
op_star
id|list_p
)paren
op_member_access_from_pointer
id|item
op_assign
id|item
suffix:semicolon
)brace
DECL|function|object_list_length
r_int
id|object_list_length
c_func
(paren
r_struct
id|object_list
op_star
id|list
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
id|list
op_assign
id|list-&gt;next
suffix:semicolon
id|ret
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|object_list_contains
r_int
id|object_list_contains
c_func
(paren
r_struct
id|object_list
op_star
id|list
comma
r_struct
id|object
op_star
id|obj
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;item
op_eq
id|obj
)paren
r_return
l_int|1
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_object_array
r_void
id|add_object_array
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|object_array
op_star
id|array
)paren
(brace
r_int
id|nr
op_assign
id|array-&gt;nr
suffix:semicolon
r_int
id|alloc
op_assign
id|array-&gt;alloc
suffix:semicolon
r_struct
id|object_array_entry
op_star
id|objects
op_assign
id|array-&gt;objects
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
id|alloc
)paren
(brace
id|alloc
op_assign
(paren
id|alloc
op_plus
l_int|32
)paren
op_star
l_int|2
suffix:semicolon
id|objects
op_assign
id|xrealloc
c_func
(paren
id|objects
comma
id|alloc
op_star
r_sizeof
(paren
op_star
id|objects
)paren
)paren
suffix:semicolon
id|array-&gt;alloc
op_assign
id|alloc
suffix:semicolon
id|array-&gt;objects
op_assign
id|objects
suffix:semicolon
)brace
id|objects
(braket
id|nr
)braket
dot
id|item
op_assign
id|obj
suffix:semicolon
id|objects
(braket
id|nr
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|array-&gt;nr
op_assign
op_increment
id|nr
suffix:semicolon
)brace
eof
