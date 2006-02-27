macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;revision.h&quot;
DECL|function|path_name
r_static
r_char
op_star
id|path_name
c_func
(paren
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|name_path
op_star
id|p
suffix:semicolon
r_char
op_star
id|n
comma
op_star
id|m
suffix:semicolon
r_int
id|nlen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_int
id|len
op_assign
id|nlen
op_plus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|path
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;up
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;elem_len
)paren
id|len
op_add_assign
id|p-&gt;elem_len
op_plus
l_int|1
suffix:semicolon
)brace
id|n
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
id|m
op_assign
id|n
op_plus
id|len
(paren
id|nlen
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|m
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|path
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;up
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;elem_len
)paren
(brace
id|m
op_sub_assign
id|p-&gt;elem_len
op_plus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|m
comma
id|p-&gt;elem
comma
id|p-&gt;elem_len
)paren
suffix:semicolon
id|m
(braket
id|p-&gt;elem_len
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|add_object
r_struct
id|object_list
op_star
op_star
id|add_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_struct
id|object_list
op_star
op_star
id|p
comma
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|object_list
op_star
id|entry
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
id|entry-&gt;item
op_assign
id|obj
suffix:semicolon
id|entry-&gt;next
op_assign
op_star
id|p
suffix:semicolon
id|entry-&gt;name
op_assign
id|path_name
c_func
(paren
id|path
comma
id|name
)paren
suffix:semicolon
op_star
id|p
op_assign
id|entry
suffix:semicolon
r_return
op_amp
id|entry-&gt;next
suffix:semicolon
)brace
DECL|function|mark_blob_uninteresting
r_static
r_void
id|mark_blob_uninteresting
c_func
(paren
r_struct
id|blob
op_star
id|blob
)paren
(brace
r_if
c_cond
(paren
id|blob-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_return
suffix:semicolon
id|blob-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
)brace
DECL|function|mark_tree_uninteresting
r_void
id|mark_tree_uninteresting
c_func
(paren
r_struct
id|tree
op_star
id|tree
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
op_amp
id|tree-&gt;object
suffix:semicolon
r_struct
id|tree_entry_list
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|UNINTERESTING
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|parse_tree
c_func
(paren
id|tree
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad tree %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|entry
op_assign
id|tree-&gt;entries
suffix:semicolon
id|tree-&gt;entries
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_struct
id|tree_entry_list
op_star
id|next
op_assign
id|entry-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;directory
)paren
id|mark_tree_uninteresting
c_func
(paren
id|entry-&gt;item.tree
)paren
suffix:semicolon
r_else
id|mark_blob_uninteresting
c_func
(paren
id|entry-&gt;item.blob
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|mark_parents_uninteresting
r_void
id|mark_parents_uninteresting
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|parents-&gt;item
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Normally we haven&squot;t parsed the parent&n;&t;&t; * yet, so we won&squot;t have a parent of a parent&n;&t;&t; * here. However, it may turn out that we&squot;ve&n;&t;&t; * reached this commit some other way (where it&n;&t;&t; * wasn&squot;t uninteresting), in which case we need&n;&t;&t; * to mark its parents recursively too..&n;&t;&t; */
r_if
c_cond
(paren
id|commit-&gt;parents
)paren
id|mark_parents_uninteresting
c_func
(paren
id|commit
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * A missing commit is ok iff its parent is marked&n;&t;&t; * uninteresting.&n;&t;&t; *&n;&t;&t; * We just mark such a thing parsed, so that when&n;&t;&t; * it is popped next time around, we won&squot;t be trying&n;&t;&t; * to parse it and get an error.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
id|commit-&gt;object.parsed
op_assign
l_int|1
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|add_pending_object
r_static
r_void
id|add_pending_object
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|add_object
c_func
(paren
id|obj
comma
op_amp
id|revs-&gt;pending_objects
comma
l_int|NULL
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|get_commit_reference
r_static
r_struct
id|commit
op_star
id|get_commit_reference
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_const
r_char
op_star
id|name
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|object
op_star
id|object
suffix:semicolon
id|object
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
op_logical_neg
id|object
)paren
id|die
c_func
(paren
l_string|&quot;bad object %s&quot;
comma
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tag object? Look what it points to..&n;&t; */
r_while
c_loop
(paren
id|object-&gt;type
op_eq
id|tag_type
)paren
(brace
r_struct
id|tag
op_star
id|tag
op_assign
(paren
r_struct
id|tag
op_star
)paren
id|object
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;tag_objects
op_logical_and
op_logical_neg
(paren
id|object-&gt;flags
op_amp
id|UNINTERESTING
)paren
)paren
id|add_pending_object
c_func
(paren
id|revs
comma
id|object
comma
id|tag-&gt;tag
)paren
suffix:semicolon
id|object
op_assign
id|parse_object
c_func
(paren
id|tag-&gt;tagged-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
id|die
c_func
(paren
l_string|&quot;bad object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;tagged-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Commit object? Just return it, we&squot;ll do all the complex&n;&t; * reachability crud.&n;&t; */
r_if
c_cond
(paren
id|object-&gt;type
op_eq
id|commit_type
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|object
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|commit
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to parse commit %s&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
(brace
id|mark_parents_uninteresting
c_func
(paren
id|commit
)paren
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|commit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Tree object? Either mark it uniniteresting, or add it&n;&t; * to the list of objects to look at later..&n;&t; */
r_if
c_cond
(paren
id|object-&gt;type
op_eq
id|tree_type
)paren
(brace
r_struct
id|tree
op_star
id|tree
op_assign
(paren
r_struct
id|tree
op_star
)paren
id|object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;tree_objects
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
(brace
id|mark_tree_uninteresting
c_func
(paren
id|tree
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|add_pending_object
c_func
(paren
id|revs
comma
id|object
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Blob object? You know the drill by now..&n;&t; */
r_if
c_cond
(paren
id|object-&gt;type
op_eq
id|blob_type
)paren
(brace
r_struct
id|blob
op_star
id|blob
op_assign
(paren
r_struct
id|blob
op_star
)paren
id|object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;blob_objects
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
(brace
id|mark_blob_uninteresting
c_func
(paren
id|blob
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|add_pending_object
c_func
(paren
id|revs
comma
id|object
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;%s is unknown object&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|add_one_commit
r_static
r_void
id|add_one_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|rev_info
op_star
id|revs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|commit
op_logical_or
(paren
id|commit-&gt;object.flags
op_amp
id|SEEN
)paren
)paren
r_return
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|SEEN
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|commit
comma
op_amp
id|revs-&gt;commits
)paren
suffix:semicolon
)brace
DECL|variable|all_flags
r_static
r_int
id|all_flags
suffix:semicolon
DECL|variable|all_revs
r_static
r_struct
id|rev_info
op_star
id|all_revs
suffix:semicolon
DECL|function|handle_one_ref
r_static
r_int
id|handle_one_ref
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|get_commit_reference
c_func
(paren
id|all_revs
comma
id|path
comma
id|sha1
comma
id|all_flags
)paren
suffix:semicolon
id|add_one_commit
c_func
(paren
id|commit
comma
id|all_revs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_all
r_static
r_void
id|handle_all
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|flags
)paren
(brace
id|all_revs
op_assign
id|revs
suffix:semicolon
id|all_flags
op_assign
id|flags
suffix:semicolon
id|for_each_ref
c_func
(paren
id|handle_one_ref
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse revision information, filling in the &quot;rev_info&quot; structure,&n; * and removing the used arguments from the argument list.&n; *&n; * Returns the number of arguments left (&quot;new argc&quot;).&n; */
DECL|function|setup_revisions
r_int
id|setup_revisions
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_struct
id|rev_info
op_star
id|revs
)paren
(brace
r_int
id|i
comma
id|flags
comma
id|seen_dashdash
suffix:semicolon
r_const
r_char
op_star
id|def
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
op_star
id|unrecognized
op_assign
id|argv
op_plus
l_int|1
suffix:semicolon
r_int
id|left
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|revs
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|revs
)paren
)paren
suffix:semicolon
id|revs-&gt;lifo
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;dense
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|revs-&gt;max_age
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;min_age
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;max_count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* First, search for &quot;--&quot; */
id|seen_dashdash
op_assign
l_int|0
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
r_continue
suffix:semicolon
id|argv
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|argc
op_assign
id|i
suffix:semicolon
id|revs-&gt;paths
op_assign
id|get_pathspec
c_func
(paren
id|revs-&gt;prefix
comma
id|argv
op_plus
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|seen_dashdash
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|flags
op_assign
l_int|0
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|dotdot
suffix:semicolon
r_int
id|local_flags
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--max-count=&quot;
comma
l_int|12
)paren
)paren
(brace
id|revs-&gt;max_count
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|12
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--max-age=&quot;
comma
l_int|10
)paren
)paren
(brace
id|revs-&gt;max_age
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
)paren
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--min-age=&quot;
comma
l_int|10
)paren
)paren
(brace
id|revs-&gt;min_age
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
)paren
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|handle_all
c_func
(paren
id|revs
comma
id|flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--not&quot;
)paren
)paren
(brace
id|flags
op_xor_assign
id|UNINTERESTING
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--default&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;bad --default argument&quot;
)paren
suffix:semicolon
id|def
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--topo-order&quot;
)paren
)paren
(brace
id|revs-&gt;topo_order
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--date-order&quot;
)paren
)paren
(brace
id|revs-&gt;lifo
op_assign
l_int|0
suffix:semicolon
id|revs-&gt;topo_order
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--dense&quot;
)paren
)paren
(brace
id|revs-&gt;dense
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--sparse&quot;
)paren
)paren
(brace
id|revs-&gt;dense
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--remove-empty&quot;
)paren
)paren
(brace
id|revs-&gt;remove_empty_trees
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--objects&quot;
)paren
)paren
(brace
id|revs-&gt;tag_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;tree_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;blob_objects
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--objects-edge&quot;
)paren
)paren
(brace
id|revs-&gt;tag_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;tree_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;blob_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;edge_hint
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--unpacked&quot;
)paren
)paren
(brace
id|revs-&gt;unpacked
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|unrecognized
op_increment
op_assign
id|arg
suffix:semicolon
id|left
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dotdot
op_assign
id|strstr
c_func
(paren
id|arg
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dotdot
)paren
(brace
r_int
r_char
id|from_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|next
op_assign
id|dotdot
op_plus
l_int|2
suffix:semicolon
op_star
id|dotdot
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|next
)paren
id|next
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
comma
id|from_sha1
)paren
op_logical_and
op_logical_neg
id|get_sha1
c_func
(paren
id|next
comma
id|sha1
)paren
)paren
(brace
r_struct
id|commit
op_star
id|exclude
suffix:semicolon
r_struct
id|commit
op_star
id|include
suffix:semicolon
id|exclude
op_assign
id|get_commit_reference
c_func
(paren
id|revs
comma
id|arg
comma
id|from_sha1
comma
id|flags
op_xor
id|UNINTERESTING
)paren
suffix:semicolon
id|include
op_assign
id|get_commit_reference
c_func
(paren
id|revs
comma
id|next
comma
id|sha1
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exclude
op_logical_or
op_logical_neg
id|include
)paren
id|die
c_func
(paren
l_string|&quot;Invalid revision range %s..%s&quot;
comma
id|arg
comma
id|next
)paren
suffix:semicolon
id|add_one_commit
c_func
(paren
id|exclude
comma
id|revs
)paren
suffix:semicolon
id|add_one_commit
c_func
(paren
id|include
comma
id|revs
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|dotdot
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
id|local_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;^&squot;
)paren
(brace
id|local_flags
op_assign
id|UNINTERESTING
suffix:semicolon
id|arg
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
OL
l_int|0
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|seen_dashdash
op_logical_or
id|local_flags
)paren
id|die
c_func
(paren
l_string|&quot;bad revision &squot;%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* If we didn&squot;t have a &quot;--&quot;, all filenames must exist */
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OL
id|argc
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|argv
(braket
id|j
)braket
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: %s&quot;
comma
id|arg
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|revs-&gt;paths
op_assign
id|get_pathspec
c_func
(paren
id|revs-&gt;prefix
comma
id|argv
op_plus
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|commit
op_assign
id|get_commit_reference
c_func
(paren
id|revs
comma
id|arg
comma
id|sha1
comma
id|flags
op_xor
id|local_flags
)paren
suffix:semicolon
id|add_one_commit
c_func
(paren
id|commit
comma
id|revs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|def
op_logical_and
op_logical_neg
id|revs-&gt;commits
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
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|def
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad default revision &squot;%s&squot;&quot;
comma
id|def
)paren
suffix:semicolon
id|commit
op_assign
id|get_commit_reference
c_func
(paren
id|revs
comma
id|def
comma
id|sha1
comma
l_int|0
)paren
suffix:semicolon
id|add_one_commit
c_func
(paren
id|commit
comma
id|revs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs-&gt;paths
)paren
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
op_star
id|unrecognized
op_assign
l_int|NULL
suffix:semicolon
r_return
id|left
suffix:semicolon
)brace
eof
