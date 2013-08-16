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
id|show_object_fn
id|show
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
comma
r_void
op_star
id|cb_data
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
op_logical_neg
id|obj
)paren
id|die
c_func
(paren
l_string|&quot;bad blob object&quot;
)paren
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
id|show
c_func
(paren
id|obj
comma
id|path
comma
id|name
comma
id|cb_data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Processing a gitlink entry currently does nothing, since&n; * we do not recurse into the subproject.&n; *&n; * We *could* eventually add a flag that actually does that,&n; * which would involve:&n; *  - is the subproject actually checked out?&n; *  - if so, see if the subproject has already been added&n; *    to the alternates list, and add it if not.&n; *  - process the commit (or tag) the gitlink points to&n; *    recursively.&n; *&n; * However, it&squot;s unclear whether there is really ever any&n; * reason to see superprojects and subprojects as such a&n; * &quot;unified&quot; object pool (potentially resulting in a totally&n; * humongous pack - avoiding which was the whole point of&n; * having gitlinks in the first place!).&n; *&n; * So for now, there is just a note that we *could* follow&n; * the link, and how to do it. Whether it necessarily makes&n; * any sense what-so-ever to ever do that is another issue.&n; */
DECL|function|process_gitlink
r_static
r_void
id|process_gitlink
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_const
r_int
r_char
op_star
id|sha1
comma
id|show_object_fn
id|show
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
comma
r_void
op_star
id|cb_data
)paren
(brace
multiline_comment|/* Nothing to do */
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
id|show_object_fn
id|show
comma
r_struct
id|name_path
op_star
id|path
comma
r_struct
id|strbuf
op_star
id|base
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|cb_data
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
r_enum
id|interesting
id|match
op_assign
id|revs-&gt;diffopt.pathspec.nr
op_eq
l_int|0
ques
c_cond
id|all_entries_interesting
suffix:colon
id|entry_not_interesting
suffix:semicolon
r_int
id|baselen
op_assign
id|base-&gt;len
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
op_logical_neg
id|obj
)paren
id|die
c_func
(paren
l_string|&quot;bad tree object&quot;
)paren
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
id|show
c_func
(paren
id|obj
comma
id|path
comma
id|name
comma
id|cb_data
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
r_if
c_cond
(paren
op_logical_neg
id|match
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|base
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base-&gt;len
)paren
id|strbuf_addch
c_func
(paren
id|base
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
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
id|match
op_ne
id|all_entries_interesting
)paren
(brace
id|match
op_assign
id|tree_entry_interesting
c_func
(paren
op_amp
id|entry
comma
id|base
comma
l_int|0
comma
op_amp
id|revs-&gt;diffopt.pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_eq
id|all_entries_not_interesting
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|match
op_eq
id|entry_not_interesting
)paren
r_continue
suffix:semicolon
)brace
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
id|show
comma
op_amp
id|me
comma
id|base
comma
id|entry.path
comma
id|cb_data
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|entry.mode
)paren
)paren
id|process_gitlink
c_func
(paren
id|revs
comma
id|entry.sha1
comma
id|show
comma
op_amp
id|me
comma
id|entry.path
comma
id|cb_data
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
id|show
comma
op_amp
id|me
comma
id|entry.path
comma
id|cb_data
)paren
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|base
comma
id|baselen
)paren
suffix:semicolon
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
id|list
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|revs-&gt;commits
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
DECL|function|add_pending_tree
r_static
r_void
id|add_pending_tree
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
)paren
(brace
id|add_pending_object
c_func
(paren
id|revs
comma
op_amp
id|tree-&gt;object
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
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
id|show_commit_fn
id|show_commit
comma
id|show_object_fn
id|show_object
comma
r_void
op_star
id|data
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
id|strbuf
id|base
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|base
comma
id|PATH_MAX
)paren
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
multiline_comment|/*&n;&t;&t; * an uninteresting boundary commit may not have its tree&n;&t;&t; * parsed yet, but we are not going to show them anyway&n;&t;&t; */
r_if
c_cond
(paren
id|commit-&gt;tree
)paren
id|add_pending_tree
c_func
(paren
id|revs
comma
id|commit-&gt;tree
)paren
suffix:semicolon
id|show_commit
c_func
(paren
id|commit
comma
id|data
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
id|show_object
c_func
(paren
id|obj
comma
l_int|NULL
comma
id|name
comma
id|data
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
id|show_object
comma
l_int|NULL
comma
op_amp
id|base
comma
id|name
comma
id|data
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
id|show_object
comma
l_int|NULL
comma
id|name
comma
id|data
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
r_if
c_cond
(paren
id|revs-&gt;pending.nr
)paren
(brace
id|free
c_func
(paren
id|revs-&gt;pending.objects
)paren
suffix:semicolon
id|revs-&gt;pending.nr
op_assign
l_int|0
suffix:semicolon
id|revs-&gt;pending.alloc
op_assign
l_int|0
suffix:semicolon
id|revs-&gt;pending.objects
op_assign
l_int|NULL
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|base
)paren
suffix:semicolon
)brace
eof
