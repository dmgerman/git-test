macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
DECL|function|score_missing
r_static
r_int
id|score_missing
c_func
(paren
r_int
id|mode
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|score
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|score
op_assign
l_int|1000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|score
op_assign
l_int|500
suffix:semicolon
r_else
id|score
op_assign
l_int|50
suffix:semicolon
r_return
id|score
suffix:semicolon
)brace
DECL|function|score_differs
r_static
r_int
id|score_differs
c_func
(paren
r_int
id|mode1
comma
r_int
id|mode2
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|score
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
op_ne
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
id|score
op_assign
l_int|100
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode1
)paren
op_ne
id|S_ISLNK
c_func
(paren
id|mode2
)paren
)paren
id|score
op_assign
l_int|50
suffix:semicolon
r_else
id|score
op_assign
l_int|5
suffix:semicolon
r_return
id|score
suffix:semicolon
)brace
DECL|function|score_matches
r_static
r_int
id|score_matches
c_func
(paren
r_int
id|mode1
comma
r_int
id|mode2
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|score
suffix:semicolon
multiline_comment|/* Heh, we found SHA-1 collisions between different kind of objects */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
op_ne
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
id|score
op_assign
l_int|100
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode1
)paren
op_ne
id|S_ISLNK
c_func
(paren
id|mode2
)paren
)paren
id|score
op_assign
l_int|50
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
)paren
id|score
op_assign
l_int|1000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode1
)paren
)paren
id|score
op_assign
l_int|500
suffix:semicolon
r_else
id|score
op_assign
l_int|250
suffix:semicolon
r_return
id|score
suffix:semicolon
)brace
multiline_comment|/*&n; * Inspect two trees, and give a score that tells how similar they are.&n; */
DECL|function|score_trees
r_static
r_int
id|score_trees
c_func
(paren
r_const
r_int
r_char
op_star
id|hash1
comma
r_const
r_int
r_char
op_star
id|hash2
)paren
(brace
r_struct
id|tree_desc
id|one
suffix:semicolon
r_struct
id|tree_desc
id|two
suffix:semicolon
r_void
op_star
id|one_buf
comma
op_star
id|two_buf
suffix:semicolon
r_int
id|score
op_assign
l_int|0
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|one_buf
op_assign
id|read_sha1_file
c_func
(paren
id|hash1
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
id|one_buf
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_TREE
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|one
comma
id|one_buf
comma
id|size
)paren
suffix:semicolon
id|two_buf
op_assign
id|read_sha1_file
c_func
(paren
id|hash2
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
id|two_buf
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_TREE
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash2
)paren
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|two
comma
id|two_buf
comma
id|size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|one.size
op_or
id|two.size
)paren
(brace
r_const
r_int
r_char
op_star
id|elem1
op_assign
id|elem1
suffix:semicolon
r_const
r_int
r_char
op_star
id|elem2
op_assign
id|elem2
suffix:semicolon
r_const
r_char
op_star
id|path1
op_assign
id|path1
suffix:semicolon
r_const
r_char
op_star
id|path2
op_assign
id|path2
suffix:semicolon
r_int
id|mode1
op_assign
id|mode1
suffix:semicolon
r_int
id|mode2
op_assign
id|mode2
suffix:semicolon
r_int
id|cmp
suffix:semicolon
r_if
c_cond
(paren
id|one.size
)paren
id|elem1
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|one
comma
op_amp
id|path1
comma
op_amp
id|mode1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|two.size
)paren
id|elem2
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|two
comma
op_amp
id|path2
comma
op_amp
id|mode2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one.size
)paren
(brace
multiline_comment|/* two has more entries */
id|score
op_add_assign
id|score_missing
c_func
(paren
id|mode2
comma
id|path2
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|two
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|two.size
)paren
(brace
multiline_comment|/* two lacks this entry */
id|score
op_add_assign
id|score_missing
c_func
(paren
id|mode1
comma
id|path1
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|one
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cmp
op_assign
id|base_name_compare
c_func
(paren
id|path1
comma
id|strlen
c_func
(paren
id|path1
)paren
comma
id|mode1
comma
id|path2
comma
id|strlen
c_func
(paren
id|path2
)paren
comma
id|mode2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
multiline_comment|/* path1 does not appear in two */
id|score
op_add_assign
id|score_missing
c_func
(paren
id|mode1
comma
id|path1
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|one
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
multiline_comment|/* path2 does not appear in one */
id|score
op_add_assign
id|score_missing
c_func
(paren
id|mode2
comma
id|path2
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|two
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|elem1
comma
id|elem2
)paren
)paren
multiline_comment|/* they are different */
id|score
op_add_assign
id|score_differs
c_func
(paren
id|mode1
comma
id|mode2
comma
id|path1
)paren
suffix:semicolon
r_else
multiline_comment|/* same subtree or blob */
id|score
op_add_assign
id|score_matches
c_func
(paren
id|mode1
comma
id|mode2
comma
id|path1
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|one
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|two
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|one_buf
)paren
suffix:semicolon
id|free
c_func
(paren
id|two_buf
)paren
suffix:semicolon
r_return
id|score
suffix:semicolon
)brace
multiline_comment|/*&n; * Match one itself and its subtrees with two and pick the best match.&n; */
DECL|function|match_trees
r_static
r_void
id|match_trees
c_func
(paren
r_const
r_int
r_char
op_star
id|hash1
comma
r_const
r_int
r_char
op_star
id|hash2
comma
r_int
op_star
id|best_score
comma
r_char
op_star
op_star
id|best_match
comma
r_const
r_char
op_star
id|base
comma
r_int
id|recurse_limit
)paren
(brace
r_struct
id|tree_desc
id|one
suffix:semicolon
r_void
op_star
id|one_buf
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|one_buf
op_assign
id|read_sha1_file
c_func
(paren
id|hash1
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
id|one_buf
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_TREE
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|one
comma
id|one_buf
comma
id|size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|one.size
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_const
r_int
r_char
op_star
id|elem
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|score
suffix:semicolon
id|elem
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|one
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
r_goto
id|next
suffix:semicolon
id|score
op_assign
id|score_trees
c_func
(paren
id|elem
comma
id|hash2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|best_score
OL
id|score
)paren
(brace
r_char
op_star
id|newpath
suffix:semicolon
id|newpath
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base
)paren
op_plus
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|newpath
comma
l_string|&quot;%s%s&quot;
comma
id|base
comma
id|path
)paren
suffix:semicolon
id|free
c_func
(paren
op_star
id|best_match
)paren
suffix:semicolon
op_star
id|best_match
op_assign
id|newpath
suffix:semicolon
op_star
id|best_score
op_assign
id|score
suffix:semicolon
)brace
r_if
c_cond
(paren
id|recurse_limit
)paren
(brace
r_char
op_star
id|newbase
suffix:semicolon
id|newbase
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base
)paren
op_plus
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|2
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|newbase
comma
l_string|&quot;%s%s/&quot;
comma
id|base
comma
id|path
)paren
suffix:semicolon
id|match_trees
c_func
(paren
id|elem
comma
id|hash2
comma
id|best_score
comma
id|best_match
comma
id|newbase
comma
id|recurse_limit
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
)paren
suffix:semicolon
)brace
id|next
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|one
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|one_buf
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A tree &quot;hash1&quot; has a subdirectory at &quot;prefix&quot;.  Come up with a&n; * tree object by replacing it with another tree &quot;hash2&quot;.&n; */
DECL|function|splice_tree
r_static
r_int
id|splice_tree
c_func
(paren
r_const
r_int
r_char
op_star
id|hash1
comma
r_char
op_star
id|prefix
comma
r_const
r_int
r_char
op_star
id|hash2
comma
r_int
r_char
op_star
id|result
)paren
(brace
r_char
op_star
id|subpath
suffix:semicolon
r_int
id|toplen
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_int
r_char
op_star
id|rewrite_here
suffix:semicolon
r_const
r_int
r_char
op_star
id|rewrite_with
suffix:semicolon
r_int
r_char
id|subtree
(braket
l_int|20
)braket
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
id|status
suffix:semicolon
id|subpath
op_assign
id|strchr
c_func
(paren
id|prefix
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subpath
)paren
id|toplen
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
r_else
(brace
id|toplen
op_assign
id|subpath
id|prefix
suffix:semicolon
id|subpath
op_increment
suffix:semicolon
)brace
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|hash1
comma
op_amp
id|type
comma
op_amp
id|sz
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
l_string|&quot;cannot read tree %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|desc
comma
id|buf
comma
id|sz
)paren
suffix:semicolon
id|rewrite_here
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|desc.size
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|desc
comma
op_amp
id|name
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|name
)paren
op_eq
id|toplen
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|prefix
comma
id|toplen
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|die
c_func
(paren
l_string|&quot;entry %s in tree %s is not a tree&quot;
comma
id|name
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
id|rewrite_here
op_assign
(paren
r_int
r_char
op_star
)paren
id|sha1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|update_tree_entry
c_func
(paren
op_amp
id|desc
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rewrite_here
)paren
id|die
c_func
(paren
l_string|&quot;entry %.*s not found in tree %s&quot;
comma
id|toplen
comma
id|prefix
comma
id|sha1_to_hex
c_func
(paren
id|hash1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subpath
)paren
(brace
id|status
op_assign
id|splice_tree
c_func
(paren
id|rewrite_here
comma
id|subpath
comma
id|hash2
comma
id|subtree
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
id|rewrite_with
op_assign
id|subtree
suffix:semicolon
)brace
r_else
id|rewrite_with
op_assign
id|hash2
suffix:semicolon
id|hashcpy
c_func
(paren
id|rewrite_here
comma
id|rewrite_with
)paren
suffix:semicolon
id|status
op_assign
id|write_sha1_file
c_func
(paren
id|buf
comma
id|sz
comma
id|tree_type
comma
id|result
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * We are trying to come up with a merge between one and two that&n; * results in a tree shape similar to one.  The tree two might&n; * correspond to a subtree of one, in which case it needs to be&n; * shifted down by prefixing otherwise empty directories.  On the&n; * other hand, it could cover tree one and we might need to pick a&n; * subtree of it.&n; */
DECL|function|shift_tree
r_void
id|shift_tree
c_func
(paren
r_const
r_int
r_char
op_star
id|hash1
comma
r_const
r_int
r_char
op_star
id|hash2
comma
r_int
r_char
op_star
id|shifted
comma
r_int
id|depth_limit
)paren
(brace
r_char
op_star
id|add_prefix
suffix:semicolon
r_char
op_star
id|del_prefix
suffix:semicolon
r_int
id|add_score
comma
id|del_score
suffix:semicolon
id|add_score
op_assign
id|del_score
op_assign
id|score_trees
c_func
(paren
id|hash1
comma
id|hash2
)paren
suffix:semicolon
id|add_prefix
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|del_prefix
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * See if one&squot;s subtree resembles two; if so we need to prefix&n;&t; * two with a few fake trees to match the prefix.&n;&t; */
id|match_trees
c_func
(paren
id|hash1
comma
id|hash2
comma
op_amp
id|add_score
comma
op_amp
id|add_prefix
comma
l_string|&quot;&quot;
comma
id|depth_limit
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * See if two&squot;s subtree resembles one; if so we need to&n;&t; * pick only subtree of two.&n;&t; */
id|match_trees
c_func
(paren
id|hash2
comma
id|hash1
comma
op_amp
id|del_score
comma
op_amp
id|del_prefix
comma
l_string|&quot;&quot;
comma
id|depth_limit
)paren
suffix:semicolon
multiline_comment|/* Assume we do not have to do any shifting */
id|hashcpy
c_func
(paren
id|shifted
comma
id|hash2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_score
OL
id|del_score
)paren
(brace
multiline_comment|/* We need to pick a subtree of two */
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|del_prefix
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|get_tree_entry
c_func
(paren
id|hash2
comma
id|del_prefix
comma
id|shifted
comma
op_amp
id|mode
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot find path %s in tree %s&quot;
comma
id|del_prefix
comma
id|sha1_to_hex
c_func
(paren
id|hash2
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|add_prefix
)paren
r_return
suffix:semicolon
id|splice_tree
c_func
(paren
id|hash1
comma
id|add_prefix
comma
id|hash2
comma
id|shifted
)paren
suffix:semicolon
)brace
eof
