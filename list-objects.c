macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;list-objects.h&quot;
DECL|function|process_blob
r_static
r_void
id|process_blob
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_struct
id|blob
op_star
id|blob
comma
r_struct
id|object_array
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
id|object
op_star
id|obj
op_assign
op_amp
id|blob-&gt;object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;blob_objects
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
(paren
id|UNINTERESTING
op_or
id|SEEN
)paren
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
id|name
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|add_object
c_func
(paren
id|obj
comma
id|p
comma
id|path
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|process_tree
r_static
r_void
id|process_tree
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_struct
id|tree
op_star
id|tree
comma
r_struct
id|object_array
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
id|object
op_star
id|obj
op_assign
op_amp
id|tree-&gt;object
suffix:semicolon
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_struct
id|name_path
id|me
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;tree_objects
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
(paren
id|UNINTERESTING
op_or
id|SEEN
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
l_string|&quot;bad tree object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
id|name
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|add_object
c_func
(paren
id|obj
comma
id|p
comma
id|path
comma
id|name
)paren
suffix:semicolon
id|me.up
op_assign
id|path
suffix:semicolon
id|me.elem
op_assign
id|name
suffix:semicolon
id|me.elem_len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|desc
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
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
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|process_tree
c_func
(paren
id|revs
comma
id|lookup_tree
c_func
(paren
id|entry.sha1
)paren
comma
id|p
comma
op_amp
id|me
comma
id|entry.path
)paren
suffix:semicolon
r_else
id|process_blob
c_func
(paren
id|revs
comma
id|lookup_blob
c_func
(paren
id|entry.sha1
)paren
comma
id|p
comma
op_amp
id|me
comma
id|entry.path
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|tree-&gt;buffer
)paren
suffix:semicolon
id|tree-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|mark_edge_parents_uninteresting
r_static
r_void
id|mark_edge_parents_uninteresting
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
comma
id|show_edge_fn
id|show_edge
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|parent-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
)paren
r_continue
suffix:semicolon
id|mark_tree_uninteresting
c_func
(paren
id|parent-&gt;tree
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;edge_hint
op_logical_and
op_logical_neg
(paren
id|parent-&gt;object.flags
op_amp
id|SHOWN
)paren
)paren
(brace
id|parent-&gt;object.flags
op_or_assign
id|SHOWN
suffix:semicolon
id|show_edge
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|mark_edges_uninteresting
r_void
id|mark_edges_uninteresting
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_struct
id|rev_info
op_star
id|revs
comma
id|show_edge_fn
id|show_edge
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
(brace
id|mark_tree_uninteresting
c_func
(paren
id|commit-&gt;tree
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|mark_edge_parents_uninteresting
c_func
(paren
id|commit
comma
id|revs
comma
id|show_edge
)paren
suffix:semicolon
)brace
)brace
DECL|function|traverse_commit_list
r_void
id|traverse_commit_list
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_void
(paren
op_star
id|show_commit
)paren
(paren
r_struct
id|commit
op_star
)paren
comma
r_void
(paren
op_star
id|show_object
)paren
(paren
r_struct
id|object_array_entry
op_star
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|object_array
id|objects
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|revs
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|process_tree
c_func
(paren
id|revs
comma
id|commit-&gt;tree
comma
op_amp
id|objects
comma
l_int|NULL
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|show_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|revs-&gt;pending.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object_array_entry
op_star
id|pending
op_assign
id|revs-&gt;pending.objects
op_plus
id|i
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
id|pending-&gt;item
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|pending-&gt;name
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
(paren
id|UNINTERESTING
op_or
id|SEEN
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
id|add_object_array
c_func
(paren
id|obj
comma
id|name
comma
op_amp
id|objects
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
(brace
id|process_tree
c_func
(paren
id|revs
comma
(paren
r_struct
id|tree
op_star
)paren
id|obj
comma
op_amp
id|objects
comma
l_int|NULL
comma
id|name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_BLOB
)paren
(brace
id|process_blob
c_func
(paren
id|revs
comma
(paren
r_struct
id|blob
op_star
)paren
id|obj
comma
op_amp
id|objects
comma
l_int|NULL
comma
id|name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;unknown pending object %s (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
id|name
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|objects.nr
suffix:semicolon
id|i
op_increment
)paren
id|show_object
c_func
(paren
op_amp
id|objects.objects
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
eof
