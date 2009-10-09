macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;notes.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
multiline_comment|/*&n; * Use a non-balancing simple 16-tree structure with struct int_node as&n; * internal nodes, and struct leaf_node as leaf nodes. Each int_node has a&n; * 16-array of pointers to its children.&n; * The bottom 2 bits of each pointer is used to identify the pointer type&n; * - ptr &amp; 3 == 0 - NULL pointer, assert(ptr == NULL)&n; * - ptr &amp; 3 == 1 - pointer to next internal node - cast to struct int_node *&n; * - ptr &amp; 3 == 2 - pointer to note entry - cast to struct leaf_node *&n; * - ptr &amp; 3 == 3 - pointer to subtree entry - cast to struct leaf_node *&n; *&n; * The root node is a statically allocated struct int_node.&n; */
DECL|struct|int_node
r_struct
id|int_node
(brace
DECL|member|a
r_void
op_star
id|a
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Leaf nodes come in two variants, note entries and subtree entries,&n; * distinguished by the LSb of the leaf node pointer (see above).&n; * As a note entry, the key is the SHA1 of the referenced commit, and the&n; * value is the SHA1 of the note object.&n; * As a subtree entry, the key is the prefix SHA1 (w/trailing NULs) of the&n; * referenced commit, using the last byte of the key to store the length of&n; * the prefix. The value is the SHA1 of the tree object containing the notes&n; * subtree.&n; */
DECL|struct|leaf_node
r_struct
id|leaf_node
(brace
DECL|member|key_sha1
r_int
r_char
id|key_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|val_sha1
r_int
r_char
id|val_sha1
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PTR_TYPE_NULL
mdefine_line|#define PTR_TYPE_NULL     0
DECL|macro|PTR_TYPE_INTERNAL
mdefine_line|#define PTR_TYPE_INTERNAL 1
DECL|macro|PTR_TYPE_NOTE
mdefine_line|#define PTR_TYPE_NOTE     2
DECL|macro|PTR_TYPE_SUBTREE
mdefine_line|#define PTR_TYPE_SUBTREE  3
DECL|macro|GET_PTR_TYPE
mdefine_line|#define GET_PTR_TYPE(ptr)       ((uintptr_t) (ptr) &amp; 3)
DECL|macro|CLR_PTR_TYPE
mdefine_line|#define CLR_PTR_TYPE(ptr)       ((void *) ((uintptr_t) (ptr) &amp; ~3))
DECL|macro|SET_PTR_TYPE
mdefine_line|#define SET_PTR_TYPE(ptr, type) ((void *) ((uintptr_t) (ptr) | (type)))
DECL|macro|GET_NIBBLE
mdefine_line|#define GET_NIBBLE(n, sha1) (((sha1[n &gt;&gt; 1]) &gt;&gt; ((~n &amp; 0x01) &lt;&lt; 2)) &amp; 0x0f)
DECL|macro|SUBTREE_SHA1_PREFIXCMP
mdefine_line|#define SUBTREE_SHA1_PREFIXCMP(key_sha1, subtree_sha1) &bslash;&n;&t;(memcmp(key_sha1, subtree_sha1, subtree_sha1[19]))
DECL|variable|root_node
r_static
r_struct
id|int_node
id|root_node
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
suffix:semicolon
r_static
r_void
id|load_subtree
c_func
(paren
r_struct
id|leaf_node
op_star
id|subtree
comma
r_struct
id|int_node
op_star
id|node
comma
r_int
r_int
id|n
)paren
suffix:semicolon
multiline_comment|/*&n; * Search the tree until the appropriate location for the given key is found:&n; * 1. Start at the root node, with n = 0&n; * 2. If a[0] at the current level is a matching subtree entry, unpack that&n; *    subtree entry and remove it; restart search at the current level.&n; * 3. Use the nth nibble of the key as an index into a:&n; *    - If a[n] is an int_node, recurse from #2 into that node and increment n&n; *    - If a matching subtree entry, unpack that subtree entry (and remove it);&n; *      restart search at the current level.&n; *    - Otherwise, we have found one of the following:&n; *      - a subtree entry which does not match the key&n; *      - a note entry which may or may not match the key&n; *      - an unused leaf node (NULL)&n; *      In any case, set *tree and *n, and return pointer to the tree location.&n; */
DECL|function|note_tree_search
r_static
r_void
op_star
op_star
id|note_tree_search
c_func
(paren
r_struct
id|int_node
op_star
op_star
id|tree
comma
r_int
r_char
op_star
id|n
comma
r_const
r_int
r_char
op_star
id|key_sha1
)paren
(brace
r_struct
id|leaf_node
op_star
id|l
suffix:semicolon
r_int
r_char
id|i
suffix:semicolon
r_void
op_star
id|p
op_assign
(paren
op_star
id|tree
)paren
op_member_access_from_pointer
id|a
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|GET_PTR_TYPE
c_func
(paren
id|p
)paren
op_eq
id|PTR_TYPE_SUBTREE
)paren
(brace
id|l
op_assign
(paren
r_struct
id|leaf_node
op_star
)paren
id|CLR_PTR_TYPE
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SUBTREE_SHA1_PREFIXCMP
c_func
(paren
id|key_sha1
comma
id|l-&gt;key_sha1
)paren
)paren
(brace
multiline_comment|/* unpack tree and resume search */
(paren
op_star
id|tree
)paren
op_member_access_from_pointer
id|a
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|load_subtree
c_func
(paren
id|l
comma
op_star
id|tree
comma
op_star
id|n
)paren
suffix:semicolon
id|free
c_func
(paren
id|l
)paren
suffix:semicolon
r_return
id|note_tree_search
c_func
(paren
id|tree
comma
id|n
comma
id|key_sha1
)paren
suffix:semicolon
)brace
)brace
id|i
op_assign
id|GET_NIBBLE
c_func
(paren
op_star
id|n
comma
id|key_sha1
)paren
suffix:semicolon
id|p
op_assign
(paren
op_star
id|tree
)paren
op_member_access_from_pointer
id|a
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|GET_PTR_TYPE
c_func
(paren
id|p
)paren
)paren
(brace
r_case
id|PTR_TYPE_INTERNAL
suffix:colon
op_star
id|tree
op_assign
id|CLR_PTR_TYPE
c_func
(paren
id|p
)paren
suffix:semicolon
(paren
op_star
id|n
)paren
op_increment
suffix:semicolon
r_return
id|note_tree_search
c_func
(paren
id|tree
comma
id|n
comma
id|key_sha1
)paren
suffix:semicolon
r_case
id|PTR_TYPE_SUBTREE
suffix:colon
id|l
op_assign
(paren
r_struct
id|leaf_node
op_star
)paren
id|CLR_PTR_TYPE
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SUBTREE_SHA1_PREFIXCMP
c_func
(paren
id|key_sha1
comma
id|l-&gt;key_sha1
)paren
)paren
(brace
multiline_comment|/* unpack tree and resume search */
(paren
op_star
id|tree
)paren
op_member_access_from_pointer
id|a
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|load_subtree
c_func
(paren
id|l
comma
op_star
id|tree
comma
op_star
id|n
)paren
suffix:semicolon
id|free
c_func
(paren
id|l
)paren
suffix:semicolon
r_return
id|note_tree_search
c_func
(paren
id|tree
comma
id|n
comma
id|key_sha1
)paren
suffix:semicolon
)brace
multiline_comment|/* fall through */
r_default
suffix:colon
r_return
op_amp
(paren
(paren
op_star
id|tree
)paren
op_member_access_from_pointer
id|a
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * To find a leaf_node:&n; * Search to the tree location appropriate for the given key:&n; * If a note entry with matching key, return the note entry, else return NULL.&n; */
DECL|function|note_tree_find
r_static
r_struct
id|leaf_node
op_star
id|note_tree_find
c_func
(paren
r_struct
id|int_node
op_star
id|tree
comma
r_int
r_char
id|n
comma
r_const
r_int
r_char
op_star
id|key_sha1
)paren
(brace
r_void
op_star
op_star
id|p
op_assign
id|note_tree_search
c_func
(paren
op_amp
id|tree
comma
op_amp
id|n
comma
id|key_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|GET_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
op_eq
id|PTR_TYPE_NOTE
)paren
(brace
r_struct
id|leaf_node
op_star
id|l
op_assign
(paren
r_struct
id|leaf_node
op_star
)paren
id|CLR_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|key_sha1
comma
id|l-&gt;key_sha1
)paren
)paren
r_return
id|l
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Create a new blob object by concatenating the two given blob objects */
DECL|function|concatenate_notes
r_static
r_int
id|concatenate_notes
c_func
(paren
r_int
r_char
op_star
id|cur_sha1
comma
r_const
r_int
r_char
op_star
id|new_sha1
)paren
(brace
r_char
op_star
id|cur_msg
comma
op_star
id|new_msg
comma
op_star
id|buf
suffix:semicolon
r_int
r_int
id|cur_len
comma
id|new_len
comma
id|buf_len
suffix:semicolon
r_enum
id|object_type
id|cur_type
comma
id|new_type
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* read in both note blob objects */
id|new_msg
op_assign
id|read_sha1_file
c_func
(paren
id|new_sha1
comma
op_amp
id|new_type
comma
op_amp
id|new_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_msg
op_logical_or
op_logical_neg
id|new_len
op_logical_or
id|new_type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|new_msg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cur_msg
op_assign
id|read_sha1_file
c_func
(paren
id|cur_sha1
comma
op_amp
id|cur_type
comma
op_amp
id|cur_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cur_msg
op_logical_or
op_logical_neg
id|cur_len
op_logical_or
id|cur_type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|cur_msg
)paren
suffix:semicolon
id|free
c_func
(paren
id|new_msg
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|cur_sha1
comma
id|new_sha1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* we will separate the notes by a newline anyway */
r_if
c_cond
(paren
id|cur_msg
(braket
id|cur_len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|cur_len
op_decrement
suffix:semicolon
multiline_comment|/* concatenate cur_msg and new_msg into buf */
id|buf_len
op_assign
id|cur_len
op_plus
l_int|1
op_plus
id|new_len
suffix:semicolon
id|buf
op_assign
(paren
r_char
op_star
)paren
id|xmalloc
c_func
(paren
id|buf_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|cur_msg
comma
id|cur_len
)paren
suffix:semicolon
id|buf
(braket
id|cur_len
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|cur_len
op_plus
l_int|1
comma
id|new_msg
comma
id|new_len
)paren
suffix:semicolon
id|free
c_func
(paren
id|cur_msg
)paren
suffix:semicolon
id|free
c_func
(paren
id|new_msg
)paren
suffix:semicolon
multiline_comment|/* create a new blob object from buf */
id|ret
op_assign
id|write_sha1_file
c_func
(paren
id|buf
comma
id|buf_len
comma
l_string|&quot;blob&quot;
comma
id|cur_sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * To insert a leaf_node:&n; * Search to the tree location appropriate for the given leaf_node&squot;s key:&n; * - If location is unused (NULL), store the tweaked pointer directly there&n; * - If location holds a note entry that matches the note-to-be-inserted, then&n; *   concatenate the two notes.&n; * - If location holds a note entry that matches the subtree-to-be-inserted,&n; *   then unpack the subtree-to-be-inserted into the location.&n; * - If location holds a matching subtree entry, unpack the subtree at that&n; *   location, and restart the insert operation from that level.&n; * - Else, create a new int_node, holding both the node-at-location and the&n; *   node-to-be-inserted, and store the new int_node into the location.&n; */
DECL|function|note_tree_insert
r_static
r_void
id|note_tree_insert
c_func
(paren
r_struct
id|int_node
op_star
id|tree
comma
r_int
r_char
id|n
comma
r_struct
id|leaf_node
op_star
id|entry
comma
r_int
r_char
id|type
)paren
(brace
r_struct
id|int_node
op_star
id|new_node
suffix:semicolon
r_struct
id|leaf_node
op_star
id|l
suffix:semicolon
r_void
op_star
op_star
id|p
op_assign
id|note_tree_search
c_func
(paren
op_amp
id|tree
comma
op_amp
id|n
comma
id|entry-&gt;key_sha1
)paren
suffix:semicolon
m_assert
(paren
id|GET_PTR_TYPE
c_func
(paren
id|entry
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* no type bits set */
id|l
op_assign
(paren
r_struct
id|leaf_node
op_star
)paren
id|CLR_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|GET_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
)paren
(brace
r_case
id|PTR_TYPE_NULL
suffix:colon
m_assert
(paren
op_logical_neg
op_star
id|p
)paren
suffix:semicolon
op_star
id|p
op_assign
id|SET_PTR_TYPE
c_func
(paren
id|entry
comma
id|type
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|PTR_TYPE_NOTE
suffix:colon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|PTR_TYPE_NOTE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|l-&gt;key_sha1
comma
id|entry-&gt;key_sha1
)paren
)paren
(brace
multiline_comment|/* skip concatenation if l == entry */
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|l-&gt;val_sha1
comma
id|entry-&gt;val_sha1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|concatenate_notes
c_func
(paren
id|l-&gt;val_sha1
comma
id|entry-&gt;val_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;failed to concatenate note %s &quot;
l_string|&quot;into note %s for commit %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;val_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|l-&gt;val_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|l-&gt;key_sha1
)paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PTR_TYPE_SUBTREE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|SUBTREE_SHA1_PREFIXCMP
c_func
(paren
id|l-&gt;key_sha1
comma
id|entry-&gt;key_sha1
)paren
)paren
(brace
multiline_comment|/* unpack &squot;entry&squot; */
id|load_subtree
c_func
(paren
id|entry
comma
id|tree
comma
id|n
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PTR_TYPE_SUBTREE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|SUBTREE_SHA1_PREFIXCMP
c_func
(paren
id|entry-&gt;key_sha1
comma
id|l-&gt;key_sha1
)paren
)paren
(brace
multiline_comment|/* unpack &squot;l&squot; and restart insert */
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
id|load_subtree
c_func
(paren
id|l
comma
id|tree
comma
id|n
)paren
suffix:semicolon
id|free
c_func
(paren
id|l
)paren
suffix:semicolon
id|note_tree_insert
c_func
(paren
id|tree
comma
id|n
comma
id|entry
comma
id|type
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* non-matching leaf_node */
m_assert
(paren
id|GET_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
op_eq
id|PTR_TYPE_NOTE
op_logical_or
id|GET_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
op_eq
id|PTR_TYPE_SUBTREE
)paren
suffix:semicolon
id|new_node
op_assign
(paren
r_struct
id|int_node
op_star
)paren
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|int_node
)paren
comma
l_int|1
)paren
suffix:semicolon
id|note_tree_insert
c_func
(paren
id|new_node
comma
id|n
op_plus
l_int|1
comma
id|l
comma
id|GET_PTR_TYPE
c_func
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|SET_PTR_TYPE
c_func
(paren
id|new_node
comma
id|PTR_TYPE_INTERNAL
)paren
suffix:semicolon
id|note_tree_insert
c_func
(paren
id|new_node
comma
id|n
op_plus
l_int|1
comma
id|entry
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the entire notes data contained in the given tree */
DECL|function|note_tree_free
r_static
r_void
id|note_tree_free
c_func
(paren
r_struct
id|int_node
op_star
id|tree
)paren
(brace
r_int
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_void
op_star
id|p
op_assign
id|tree-&gt;a
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|GET_PTR_TYPE
c_func
(paren
id|p
)paren
)paren
(brace
r_case
id|PTR_TYPE_INTERNAL
suffix:colon
id|note_tree_free
c_func
(paren
id|CLR_PTR_TYPE
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|PTR_TYPE_NOTE
suffix:colon
r_case
id|PTR_TYPE_SUBTREE
suffix:colon
id|free
c_func
(paren
id|CLR_PTR_TYPE
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Convert a partial SHA1 hex string to the corresponding partial SHA1 value.&n; * - hex      - Partial SHA1 segment in ASCII hex format&n; * - hex_len  - Length of above segment. Must be multiple of 2 between 0 and 40&n; * - sha1     - Partial SHA1 value is written here&n; * - sha1_len - Max #bytes to store in sha1, Must be &gt;= hex_len / 2, and &lt; 20&n; * Returns -1 on error (invalid arguments or invalid SHA1 (not in hex format).&n; * Otherwise, returns number of bytes written to sha1 (i.e. hex_len / 2).&n; * Pads sha1 with NULs up to sha1_len (not included in returned length).&n; */
DECL|function|get_sha1_hex_segment
r_static
r_int
id|get_sha1_hex_segment
c_func
(paren
r_const
r_char
op_star
id|hex
comma
r_int
r_int
id|hex_len
comma
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|sha1_len
)paren
(brace
r_int
r_int
id|i
comma
id|len
op_assign
id|hex_len
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hex_len
op_mod
l_int|2
op_ne
l_int|0
op_logical_or
id|len
OG
id|sha1_len
)paren
r_return
l_int|1
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|val
op_assign
(paren
id|hexval
c_func
(paren
id|hex
(braket
l_int|0
)braket
)paren
op_lshift
l_int|4
)paren
op_or
id|hexval
c_func
(paren
id|hex
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
op_complement
l_int|0xff
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|sha1
op_increment
op_assign
id|val
suffix:semicolon
id|hex
op_add_assign
l_int|2
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|sha1_len
suffix:semicolon
id|i
op_increment
)paren
op_star
id|sha1
op_increment
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|load_subtree
r_static
r_void
id|load_subtree
c_func
(paren
r_struct
id|leaf_node
op_star
id|subtree
comma
r_struct
id|int_node
op_star
id|node
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_char
id|commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|prefix_len
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
id|buf
op_assign
id|fill_tree_descriptor
c_func
(paren
op_amp
id|desc
comma
id|subtree-&gt;val_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;Could not read %s for notes-index&quot;
comma
id|sha1_to_hex
c_func
(paren
id|subtree-&gt;val_sha1
)paren
)paren
suffix:semicolon
id|prefix_len
op_assign
id|subtree-&gt;key_sha1
(braket
l_int|19
)braket
suffix:semicolon
m_assert
(paren
id|prefix_len
op_star
l_int|2
op_ge
id|n
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|commit_sha1
comma
id|subtree-&gt;key_sha1
comma
id|prefix_len
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tree_entry
c_func
(paren
op_amp
id|desc
comma
op_amp
id|entry
)paren
)paren
(brace
r_int
id|len
op_assign
id|get_sha1_hex_segment
c_func
(paren
id|entry.path
comma
id|strlen
c_func
(paren
id|entry.path
)paren
comma
id|commit_sha1
op_plus
id|prefix_len
comma
l_int|20
id|prefix_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* entry.path is not a SHA1 sum. Skip */
id|len
op_add_assign
id|prefix_len
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If commit SHA1 is complete (len == 20), assume note object&n;&t;&t; * If commit SHA1 is incomplete (len &lt; 20), assume note subtree&n;&t;&t; */
r_if
c_cond
(paren
id|len
op_le
l_int|20
)paren
(brace
r_int
r_char
id|type
op_assign
id|PTR_TYPE_NOTE
suffix:semicolon
r_struct
id|leaf_node
op_star
id|l
op_assign
(paren
r_struct
id|leaf_node
op_star
)paren
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|leaf_node
)paren
comma
l_int|1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|l-&gt;key_sha1
comma
id|commit_sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|l-&gt;val_sha1
comma
id|entry.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|20
)paren
(brace
id|l-&gt;key_sha1
(braket
l_int|19
)braket
op_assign
(paren
r_int
r_char
)paren
id|len
suffix:semicolon
id|type
op_assign
id|PTR_TYPE_SUBTREE
suffix:semicolon
)brace
id|note_tree_insert
c_func
(paren
id|node
comma
id|n
comma
id|l
comma
id|type
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|initialize_notes
r_static
r_void
id|initialize_notes
c_func
(paren
r_const
r_char
op_star
id|notes_ref_name
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_struct
id|leaf_node
id|root_tree
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|notes_ref_name
op_logical_or
id|read_ref
c_func
(paren
id|notes_ref_name
comma
id|commit_sha1
)paren
op_logical_or
id|get_tree_entry
c_func
(paren
id|commit_sha1
comma
l_string|&quot;&quot;
comma
id|sha1
comma
op_amp
id|mode
)paren
)paren
r_return
suffix:semicolon
id|hashclr
c_func
(paren
id|root_tree.key_sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|root_tree.val_sha1
comma
id|sha1
)paren
suffix:semicolon
id|load_subtree
c_func
(paren
op_amp
id|root_tree
comma
op_amp
id|root_node
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|lookup_notes
r_static
r_int
r_char
op_star
id|lookup_notes
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
)paren
(brace
r_struct
id|leaf_node
op_star
id|found
op_assign
id|note_tree_find
c_func
(paren
op_amp
id|root_node
comma
l_int|0
comma
id|commit_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
)paren
r_return
id|found-&gt;val_sha1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|free_notes
r_void
id|free_notes
c_func
(paren
r_void
)paren
(brace
id|note_tree_free
c_func
(paren
op_amp
id|root_node
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|root_node
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|int_node
)paren
)paren
suffix:semicolon
id|initialized
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|get_commit_notes
r_void
id|get_commit_notes
c_func
(paren
r_const
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|output_encoding
comma
r_int
id|flags
)paren
(brace
r_static
r_const
r_char
id|utf8
(braket
)braket
op_assign
l_string|&quot;utf-8&quot;
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_char
op_star
id|msg
comma
op_star
id|msg_p
suffix:semicolon
r_int
r_int
id|linelen
comma
id|msglen
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
r_const
r_char
op_star
id|env
op_assign
id|getenv
c_func
(paren
id|GIT_NOTES_REF_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|env
)paren
id|notes_ref_name
op_assign
id|getenv
c_func
(paren
id|GIT_NOTES_REF_ENVIRONMENT
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|notes_ref_name
)paren
id|notes_ref_name
op_assign
id|GIT_NOTES_DEFAULT_REF
suffix:semicolon
id|initialize_notes
c_func
(paren
id|notes_ref_name
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
id|sha1
op_assign
id|lookup_notes
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sha1
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|msg
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
id|msglen
)paren
)paren
op_logical_or
op_logical_neg
id|msglen
op_logical_or
id|type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|output_encoding
op_logical_and
op_star
id|output_encoding
op_logical_and
id|strcmp
c_func
(paren
id|utf8
comma
id|output_encoding
)paren
)paren
(brace
r_char
op_star
id|reencoded
op_assign
id|reencode_string
c_func
(paren
id|msg
comma
id|output_encoding
comma
id|utf8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reencoded
)paren
(brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
id|msg
op_assign
id|reencoded
suffix:semicolon
id|msglen
op_assign
id|strlen
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* we will end the annotation by a newline anyway */
r_if
c_cond
(paren
id|msglen
op_logical_and
id|msg
(braket
id|msglen
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|msglen
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|NOTES_SHOW_HEADER
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
l_string|&quot;&bslash;nNotes:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|msg_p
op_assign
id|msg
suffix:semicolon
id|msg_p
OL
id|msg
op_plus
id|msglen
suffix:semicolon
id|msg_p
op_add_assign
id|linelen
op_plus
l_int|1
)paren
(brace
id|linelen
op_assign
id|strchrnul
c_func
(paren
id|msg_p
comma
l_char|&squot;&bslash;n&squot;
)paren
id|msg_p
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|NOTES_INDENT
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
l_string|&quot;    &quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|msg_p
comma
id|linelen
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
eof
