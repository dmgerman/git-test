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
DECL|variable|object_type_strings
r_static
r_const
r_char
op_star
id|object_type_strings
(braket
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* OBJ_NONE = 0 */
l_string|&quot;commit&quot;
comma
multiline_comment|/* OBJ_COMMIT = 1 */
l_string|&quot;tree&quot;
comma
multiline_comment|/* OBJ_TREE = 2 */
l_string|&quot;blob&quot;
comma
multiline_comment|/* OBJ_BLOB = 3 */
l_string|&quot;tag&quot;
comma
multiline_comment|/* OBJ_TAG = 4 */
)brace
suffix:semicolon
DECL|function|typename
r_const
r_char
op_star
r_typename
(paren
r_int
r_int
id|type
)paren
(brace
r_if
c_cond
(paren
id|type
op_ge
id|ARRAY_SIZE
c_func
(paren
id|object_type_strings
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|object_type_strings
(braket
id|type
)braket
suffix:semicolon
)brace
DECL|function|type_from_string_gently
r_int
id|type_from_string_gently
c_func
(paren
r_const
r_char
op_star
id|str
comma
id|ssize_t
id|len
comma
r_int
id|gentle
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|object_type_strings
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
id|object_type_strings
(braket
id|i
)braket
comma
id|len
)paren
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|gentle
)paren
r_return
l_int|1
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid object type &bslash;&quot;%s&bslash;&quot;&quot;
comma
id|str
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a numerical hash value between 0 and n-1 for the object with&n; * the specified sha1.  n must be a power of 2.  Please note that the&n; * return value is *not* consistent across computer architectures.&n; */
DECL|function|hash_obj
r_static
r_int
r_int
id|hash_obj
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|n
)paren
(brace
r_return
id|sha1hash
c_func
(paren
id|sha1
)paren
op_amp
(paren
id|n
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert obj into the hash table hash, which has length size (which&n; * must be a power of 2).  On collisions, simply overflow to the next&n; * empty bucket.&n; */
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
r_int
id|j
op_assign
id|hash_obj
c_func
(paren
id|obj-&gt;sha1
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
multiline_comment|/*&n; * Look up the record for the given sha1 in the hash map stored in&n; * obj_hash.  Return NULL if it was not found.&n; */
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
r_int
id|i
comma
id|first
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
id|first
op_assign
id|i
op_assign
id|hash_obj
c_func
(paren
id|sha1
comma
id|obj_hash_size
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
r_if
c_cond
(paren
id|obj
op_logical_and
id|i
op_ne
id|first
)paren
(brace
multiline_comment|/*&n;&t;&t; * Move object to where we started to look for it so&n;&t;&t; * that we do not need to walk the hash table the next&n;&t;&t; * time we look for it.&n;&t;&t; */
r_struct
id|object
op_star
id|tmp
op_assign
id|obj_hash
(braket
id|i
)braket
suffix:semicolon
id|obj_hash
(braket
id|i
)braket
op_assign
id|obj_hash
(braket
id|first
)braket
suffix:semicolon
id|obj_hash
(braket
id|first
)braket
op_assign
id|tmp
suffix:semicolon
)brace
r_return
id|obj
suffix:semicolon
)brace
multiline_comment|/*&n; * Increase the size of the hash map stored in obj_hash to the next&n; * power of 2 (but at least 32).  Copy the existing values to the new&n; * hash map.&n; */
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
multiline_comment|/*&n;&t; * Note that this size must always be power-of-2 to match hash_obj&n;&t; * above.&n;&t; */
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
id|xcalloc
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
DECL|function|create_object
r_void
op_star
id|create_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_void
op_star
id|o
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|o
suffix:semicolon
id|obj-&gt;parsed
op_assign
l_int|0
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|0
suffix:semicolon
id|obj-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|hashcpy
c_func
(paren
id|obj-&gt;sha1
comma
id|sha1
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
r_return
id|obj
suffix:semicolon
)brace
DECL|function|object_as_type
r_void
op_star
id|object_as_type
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_enum
id|object_type
id|type
comma
r_int
id|quiet
)paren
(brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|type
)paren
r_return
id|obj
suffix:semicolon
r_else
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_NONE
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_COMMIT
)paren
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
)paren
op_member_access_from_pointer
id|index
op_assign
id|alloc_commit_index
c_func
(paren
)paren
suffix:semicolon
id|obj-&gt;type
op_assign
id|type
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|error
c_func
(paren
l_string|&quot;object %s is a %s, not a %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
r_typename
(paren
id|type
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
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
id|obj
op_assign
id|create_object
c_func
(paren
id|sha1
comma
id|alloc_object_node
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
DECL|function|parse_object_buffer
r_struct
id|object
op_star
id|parse_object_buffer
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_enum
id|object_type
id|type
comma
r_int
r_int
id|size
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|eaten_p
)paren
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
op_star
id|eaten_p
op_assign
l_int|0
suffix:semicolon
id|obj
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_BLOB
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
r_if
c_cond
(paren
id|blob
)paren
(brace
r_if
c_cond
(paren
id|parse_blob_buffer
c_func
(paren
id|blob
comma
id|buffer
comma
id|size
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|obj
op_assign
op_amp
id|blob-&gt;object
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_TREE
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
r_if
c_cond
(paren
id|tree
)paren
(brace
id|obj
op_assign
op_amp
id|tree-&gt;object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;buffer
)paren
id|tree-&gt;object.parsed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;object.parsed
)paren
(brace
r_if
c_cond
(paren
id|parse_tree_buffer
c_func
(paren
id|tree
comma
id|buffer
comma
id|size
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|eaten_p
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_COMMIT
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
r_if
c_cond
(paren
id|commit
)paren
(brace
r_if
c_cond
(paren
id|parse_commit_buffer
c_func
(paren
id|commit
comma
id|buffer
comma
id|size
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_cached_commit_buffer
c_func
(paren
id|commit
comma
l_int|NULL
)paren
)paren
(brace
id|set_commit_buffer
c_func
(paren
id|commit
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
op_star
id|eaten_p
op_assign
l_int|1
suffix:semicolon
)brace
id|obj
op_assign
op_amp
id|commit-&gt;object
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_TAG
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
r_if
c_cond
(paren
id|tag
)paren
(brace
r_if
c_cond
(paren
id|parse_tag_buffer
c_func
(paren
id|tag
comma
id|buffer
comma
id|size
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|obj
op_assign
op_amp
id|tag-&gt;object
suffix:semicolon
)brace
)brace
r_else
(brace
id|warning
c_func
(paren
l_string|&quot;object %s has unknown type id %d&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|type
)paren
suffix:semicolon
id|obj
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|obj
suffix:semicolon
)brace
DECL|function|parse_object_or_die
r_struct
id|object
op_star
id|parse_object_or_die
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
id|name
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o
)paren
r_return
id|o
suffix:semicolon
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to parse object: %s&quot;
)paren
comma
id|name
ques
c_cond
id|name
suffix:colon
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
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
r_enum
id|object_type
id|type
suffix:semicolon
r_int
id|eaten
suffix:semicolon
r_const
r_int
r_char
op_star
id|repl
op_assign
id|lookup_replace_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
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
id|obj
op_logical_and
id|obj-&gt;parsed
)paren
r_return
id|obj
suffix:semicolon
r_if
c_cond
(paren
(paren
id|obj
op_logical_and
id|obj-&gt;type
op_eq
id|OBJ_BLOB
)paren
op_logical_or
(paren
op_logical_neg
id|obj
op_logical_and
id|has_sha1_file
c_func
(paren
id|sha1
)paren
op_logical_and
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
op_eq
id|OBJ_BLOB
)paren
)paren
(brace
r_if
c_cond
(paren
id|check_sha1_signature
c_func
(paren
id|repl
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;sha1 mismatch %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|repl
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|parse_blob_buffer
c_func
(paren
id|lookup_blob
c_func
(paren
id|sha1
)paren
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
id|lookup_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
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
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|check_sha1_signature
c_func
(paren
id|repl
comma
id|buffer
comma
id|size
comma
r_typename
(paren
id|type
)paren
)paren
OL
l_int|0
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;sha1 mismatch %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|repl
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|obj
op_assign
id|parse_object_buffer
c_func
(paren
id|sha1
comma
id|type
comma
id|size
comma
id|buffer
comma
op_amp
id|eaten
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eaten
)paren
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
multiline_comment|/*&n; * A zero-length string to which object_array_entry::name can be&n; * initialized without requiring a malloc/free.&n; */
DECL|variable|object_array_slopbuf
r_static
r_char
id|object_array_slopbuf
(braket
l_int|1
)braket
suffix:semicolon
DECL|function|add_object_array_with_mode_context
r_static
r_void
id|add_object_array_with_mode_context
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
comma
r_int
id|mode
comma
r_struct
id|object_context
op_star
id|context
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
r_struct
id|object_array_entry
op_star
id|entry
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
id|entry
op_assign
op_amp
id|objects
(braket
id|nr
)braket
suffix:semicolon
id|entry-&gt;item
op_assign
id|obj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|entry-&gt;name
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
op_star
id|name
)paren
multiline_comment|/* Use our own empty string instead of allocating one: */
id|entry-&gt;name
op_assign
id|object_array_slopbuf
suffix:semicolon
r_else
id|entry-&gt;name
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|entry-&gt;mode
op_assign
id|mode
suffix:semicolon
id|entry-&gt;context
op_assign
id|context
suffix:semicolon
id|array-&gt;nr
op_assign
op_increment
id|nr
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
id|add_object_array_with_mode
c_func
(paren
id|obj
comma
id|name
comma
id|array
comma
id|S_IFINVALID
)paren
suffix:semicolon
)brace
DECL|function|add_object_array_with_mode
r_void
id|add_object_array_with_mode
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
comma
r_int
id|mode
)paren
(brace
id|add_object_array_with_mode_context
c_func
(paren
id|obj
comma
id|name
comma
id|array
comma
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|add_object_array_with_context
r_void
id|add_object_array_with_context
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
comma
r_struct
id|object_context
op_star
id|context
)paren
(brace
r_if
c_cond
(paren
id|context
)paren
id|add_object_array_with_mode_context
c_func
(paren
id|obj
comma
id|name
comma
id|array
comma
id|context-&gt;mode
comma
id|context
)paren
suffix:semicolon
r_else
id|add_object_array_with_mode_context
c_func
(paren
id|obj
comma
id|name
comma
id|array
comma
id|S_IFINVALID
comma
id|context
)paren
suffix:semicolon
)brace
DECL|function|object_array_filter
r_void
id|object_array_filter
c_func
(paren
r_struct
id|object_array
op_star
id|array
comma
id|object_array_each_func_t
id|want
comma
r_void
op_star
id|cb_data
)paren
(brace
r_int
id|nr
op_assign
id|array-&gt;nr
comma
id|src
comma
id|dst
suffix:semicolon
r_struct
id|object_array_entry
op_star
id|objects
op_assign
id|array-&gt;objects
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
id|dst
op_assign
l_int|0
suffix:semicolon
id|src
OL
id|nr
suffix:semicolon
id|src
op_increment
)paren
(brace
r_if
c_cond
(paren
id|want
c_func
(paren
op_amp
id|objects
(braket
id|src
)braket
comma
id|cb_data
)paren
)paren
(brace
r_if
c_cond
(paren
id|src
op_ne
id|dst
)paren
id|objects
(braket
id|dst
)braket
op_assign
id|objects
(braket
id|src
)braket
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|objects
(braket
id|src
)braket
dot
id|name
op_ne
id|object_array_slopbuf
)paren
id|free
c_func
(paren
id|objects
(braket
id|src
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
id|array-&gt;nr
op_assign
id|dst
suffix:semicolon
)brace
multiline_comment|/*&n; * Return true iff array already contains an entry with name.&n; */
DECL|function|contains_name
r_static
r_int
id|contains_name
c_func
(paren
r_struct
id|object_array
op_star
id|array
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|nr
op_assign
id|array-&gt;nr
comma
id|i
suffix:semicolon
r_struct
id|object_array_entry
op_star
id|object
op_assign
id|array-&gt;objects
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
id|nr
suffix:semicolon
id|i
op_increment
comma
id|object
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|object-&gt;name
comma
id|name
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|object_array_remove_duplicates
r_void
id|object_array_remove_duplicates
c_func
(paren
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
comma
id|src
suffix:semicolon
r_struct
id|object_array_entry
op_star
id|objects
op_assign
id|array-&gt;objects
suffix:semicolon
id|array-&gt;nr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
l_int|0
suffix:semicolon
id|src
OL
id|nr
suffix:semicolon
id|src
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|contains_name
c_func
(paren
id|array
comma
id|objects
(braket
id|src
)braket
dot
id|name
)paren
)paren
(brace
r_if
c_cond
(paren
id|src
op_ne
id|array-&gt;nr
)paren
id|objects
(braket
id|array-&gt;nr
)braket
op_assign
id|objects
(braket
id|src
)braket
suffix:semicolon
id|array-&gt;nr
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|objects
(braket
id|src
)braket
dot
id|name
op_ne
id|object_array_slopbuf
)paren
id|free
c_func
(paren
id|objects
(braket
id|src
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|clear_object_flags
r_void
id|clear_object_flags
c_func
(paren
r_int
id|flags
)paren
(brace
r_int
id|i
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
id|obj
)paren
id|obj-&gt;flags
op_and_assign
op_complement
id|flags
suffix:semicolon
)brace
)brace
eof
