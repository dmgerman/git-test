macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;builtin.h&quot;
multiline_comment|/* bits #0-15 in revision.h */
DECL|macro|COUNTED
mdefine_line|#define COUNTED&t;&t;(1u&lt;&lt;16)
DECL|variable|rev_list_usage
r_static
r_const
r_char
id|rev_list_usage
(braket
)braket
op_assign
l_string|&quot;git-rev-list [OPTION] &lt;commit-id&gt;... [ -- paths... ]&bslash;n&quot;
l_string|&quot;  limiting output:&bslash;n&quot;
l_string|&quot;    --max-count=nr&bslash;n&quot;
l_string|&quot;    --max-age=epoch&bslash;n&quot;
l_string|&quot;    --min-age=epoch&bslash;n&quot;
l_string|&quot;    --sparse&bslash;n&quot;
l_string|&quot;    --no-merges&bslash;n&quot;
l_string|&quot;    --remove-empty&bslash;n&quot;
l_string|&quot;    --all&bslash;n&quot;
l_string|&quot;    --stdin&bslash;n&quot;
l_string|&quot;  ordering output:&bslash;n&quot;
l_string|&quot;    --topo-order&bslash;n&quot;
l_string|&quot;    --date-order&bslash;n&quot;
l_string|&quot;  formatting output:&bslash;n&quot;
l_string|&quot;    --parents&bslash;n&quot;
l_string|&quot;    --objects | --objects-edge&bslash;n&quot;
l_string|&quot;    --unpacked&bslash;n&quot;
l_string|&quot;    --header | --pretty&bslash;n&quot;
l_string|&quot;    --abbrev=nr | --no-abbrev&bslash;n&quot;
l_string|&quot;    --abbrev-commit&bslash;n&quot;
l_string|&quot;  special purpose:&bslash;n&quot;
l_string|&quot;    --bisect&quot;
suffix:semicolon
DECL|variable|revs
r_static
r_struct
id|rev_info
id|revs
suffix:semicolon
DECL|variable|bisect_list
r_static
r_int
id|bisect_list
suffix:semicolon
DECL|variable|show_timestamp
r_static
r_int
id|show_timestamp
suffix:semicolon
DECL|variable|hdr_termination
r_static
r_int
id|hdr_termination
suffix:semicolon
DECL|variable|header_prefix
r_static
r_const
r_char
op_star
id|header_prefix
suffix:semicolon
DECL|function|show_commit
r_static
r_void
id|show_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_if
c_cond
(paren
id|show_timestamp
)paren
id|printf
c_func
(paren
l_string|&quot;%lu &quot;
comma
id|commit-&gt;date
)paren
suffix:semicolon
r_if
c_cond
(paren
id|header_prefix
)paren
id|fputs
c_func
(paren
id|header_prefix
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|BOUNDARY
)paren
id|putchar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.abbrev_commit
op_logical_and
id|revs.abbrev
)paren
id|fputs
c_func
(paren
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|revs.abbrev
)paren
comma
id|stdout
)paren
suffix:semicolon
r_else
id|fputs
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.parents
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
id|object
op_star
id|o
op_assign
op_amp
(paren
id|parents-&gt;item-&gt;object
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;flags
op_amp
id|TMP_MARK
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
)paren
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|TMP_MARK
suffix:semicolon
)brace
multiline_comment|/* TMP_MARK is a general purpose flag that can&n;&t;&t; * be used locally, but the user should clean&n;&t;&t; * things up after it is done with them.&n;&t;&t; */
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
id|parents-&gt;item-&gt;object.flags
op_and_assign
op_complement
id|TMP_MARK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs.commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.verbose_header
)paren
(brace
r_static
r_char
id|pretty_header
(braket
l_int|16384
)braket
suffix:semicolon
id|pretty_print_commit
c_func
(paren
id|revs.commit_format
comma
id|commit
comma
op_complement
l_int|0
comma
id|pretty_header
comma
r_sizeof
(paren
id|pretty_header
)paren
comma
id|revs.abbrev
comma
l_int|NULL
comma
l_int|NULL
comma
id|revs.relative_date
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|pretty_header
comma
id|hdr_termination
)paren
suffix:semicolon
)brace
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;parents
)paren
(brace
id|free_commit_list
c_func
(paren
id|commit-&gt;parents
)paren
suffix:semicolon
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free
c_func
(paren
id|commit-&gt;buffer
)paren
suffix:semicolon
id|commit-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|process_blob
r_static
r_void
id|process_blob
c_func
(paren
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
id|revs.blob_objects
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
id|revs.tree_objects
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
id|desc.buf
op_assign
id|tree-&gt;buffer
suffix:semicolon
id|desc.size
op_assign
id|tree-&gt;size
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
DECL|function|show_commit_list
r_static
r_void
id|show_commit_list
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
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
(brace
r_struct
id|object_array_entry
op_star
id|p
op_assign
id|objects.objects
op_plus
id|i
suffix:semicolon
multiline_comment|/* An object with name &quot;foo&bslash;n0000000...&quot; can be used to&n;&t;&t; * confuse downstream git-pack-objects very badly.&n;&t;&t; */
r_const
r_char
op_star
id|ep
op_assign
id|strchr
c_func
(paren
id|p-&gt;name
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s %.*s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|p-&gt;item-&gt;sha1
)paren
comma
(paren
r_int
)paren
(paren
id|ep
id|p-&gt;name
)paren
comma
id|p-&gt;name
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|p-&gt;item-&gt;sha1
)paren
comma
id|p-&gt;name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is a truly stupid algorithm, but it&squot;s only&n; * used for bisection, and we just don&squot;t care enough.&n; *&n; * We care just barely enough to avoid recursing for&n; * non-merge entries.&n; */
DECL|function|count_distance
r_static
r_int
id|count_distance
c_func
(paren
r_struct
id|commit_list
op_star
id|entry
)paren
(brace
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|entry-&gt;item
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
(paren
id|UNINTERESTING
op_or
id|COUNTED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs.prune_fn
op_logical_or
(paren
id|commit-&gt;object.flags
op_amp
id|TREECHANGE
)paren
)paren
id|nr
op_increment
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|COUNTED
suffix:semicolon
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|entry
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|nr
op_add_assign
id|count_distance
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
)brace
r_return
id|nr
suffix:semicolon
)brace
DECL|function|clear_distance
r_static
r_void
id|clear_distance
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
id|commit-&gt;object.flags
op_and_assign
op_complement
id|COUNTED
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|find_bisection
r_static
r_struct
id|commit_list
op_star
id|find_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_int
id|nr
comma
id|closest
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
comma
op_star
id|best
suffix:semicolon
id|nr
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|list
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|revs.prune_fn
op_logical_or
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|TREECHANGE
)paren
)paren
id|nr
op_increment
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|closest
op_assign
l_int|0
suffix:semicolon
id|best
op_assign
id|list
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|distance
suffix:semicolon
r_if
c_cond
(paren
id|revs.prune_fn
op_logical_and
op_logical_neg
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|TREECHANGE
)paren
)paren
r_continue
suffix:semicolon
id|distance
op_assign
id|count_distance
c_func
(paren
id|p
)paren
suffix:semicolon
id|clear_distance
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
id|distance
OL
id|distance
)paren
id|distance
op_assign
id|nr
id|distance
suffix:semicolon
r_if
c_cond
(paren
id|distance
OG
id|closest
)paren
(brace
id|best
op_assign
id|p
suffix:semicolon
id|closest
op_assign
id|distance
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|best
)paren
id|best-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_return
id|best
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
id|revs.edge_hint
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
id|printf
c_func
(paren
l_string|&quot;-%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|parent-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|mark_edges_uninteresting
r_static
r_void
id|mark_edges_uninteresting
c_func
(paren
r_struct
id|commit_list
op_star
id|list
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
)paren
suffix:semicolon
)brace
)brace
DECL|function|read_revisions_from_stdin
r_static
r_void
id|read_revisions_from_stdin
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
)paren
(brace
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|die
c_func
(paren
l_string|&quot;options not supported in --stdin mode&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle_revision_arg
c_func
(paren
id|line
comma
id|revs
comma
l_int|0
comma
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;bad revision &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
)brace
)brace
DECL|function|cmd_rev_list
r_int
id|cmd_rev_list
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
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|commit_list
op_star
id|list
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|read_from_stdin
op_assign
l_int|0
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
id|prefix
)paren
suffix:semicolon
id|revs.abbrev
op_assign
l_int|0
suffix:semicolon
id|revs.commit_format
op_assign
id|CMIT_FMT_UNSPECIFIED
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|revs
comma
l_int|NULL
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
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--header&quot;
)paren
)paren
(brace
id|revs.verbose_header
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
l_string|&quot;--timestamp&quot;
)paren
)paren
(brace
id|show_timestamp
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
l_string|&quot;--bisect&quot;
)paren
)paren
(brace
id|bisect_list
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
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|read_from_stdin
op_increment
)paren
id|die
c_func
(paren
l_string|&quot;--stdin given twice?&quot;
)paren
suffix:semicolon
id|read_revisions_from_stdin
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|rev_list_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs.commit_format
op_ne
id|CMIT_FMT_UNSPECIFIED
)paren
(brace
multiline_comment|/* The command line has a --pretty  */
id|hdr_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|revs.commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|header_prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_else
id|header_prefix
op_assign
l_string|&quot;commit &quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|revs.verbose_header
)paren
multiline_comment|/* Only --header was specified */
id|revs.commit_format
op_assign
id|CMIT_FMT_RAW
suffix:semicolon
id|list
op_assign
id|revs.commits
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|list
op_logical_and
(paren
op_logical_neg
(paren
id|revs.tag_objects
op_logical_or
id|revs.tree_objects
op_logical_or
id|revs.blob_objects
)paren
op_logical_and
op_logical_neg
id|revs.pending.nr
)paren
)paren
op_logical_or
id|revs.diff
)paren
id|usage
c_func
(paren
id|rev_list_usage
)paren
suffix:semicolon
id|save_commit_buffer
op_assign
id|revs.verbose_header
suffix:semicolon
id|track_object_refs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bisect_list
)paren
id|revs.limited
op_assign
l_int|1
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.tree_objects
)paren
id|mark_edges_uninteresting
c_func
(paren
id|revs.commits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bisect_list
)paren
id|revs.commits
op_assign
id|find_bisection
c_func
(paren
id|revs.commits
)paren
suffix:semicolon
id|show_commit_list
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
