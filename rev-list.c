macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;epoch.h&quot;
DECL|macro|SEEN
mdefine_line|#define SEEN&t;&t;(1u &lt;&lt; 0)
DECL|macro|INTERESTING
mdefine_line|#define INTERESTING&t;(1u &lt;&lt; 1)
DECL|macro|COUNTED
mdefine_line|#define COUNTED&t;&t;(1u &lt;&lt; 2)
DECL|macro|SHOWN
mdefine_line|#define SHOWN&t;&t;(1u &lt;&lt; 3)
DECL|variable|rev_list_usage
r_static
r_const
r_char
id|rev_list_usage
(braket
)braket
op_assign
l_string|&quot;usage: git-rev-list [OPTION] commit-id &lt;commit-id&gt;&bslash;n&quot;
l_string|&quot;  --max-count=nr&bslash;n&quot;
l_string|&quot;  --max-age=epoch&bslash;n&quot;
l_string|&quot;  --min-age=epoch&bslash;n&quot;
l_string|&quot;  --bisect&bslash;n&quot;
l_string|&quot;  --objects&bslash;n&quot;
l_string|&quot;  --unpacked&bslash;n&quot;
l_string|&quot;  --header&bslash;n&quot;
l_string|&quot;  --pretty&bslash;n&quot;
l_string|&quot;  --merge-order [ --show-breaks ]&quot;
suffix:semicolon
DECL|variable|unpacked
r_static
r_int
id|unpacked
op_assign
l_int|0
suffix:semicolon
DECL|variable|bisect_list
r_static
r_int
id|bisect_list
op_assign
l_int|0
suffix:semicolon
DECL|variable|tag_objects
r_static
r_int
id|tag_objects
op_assign
l_int|0
suffix:semicolon
DECL|variable|tree_objects
r_static
r_int
id|tree_objects
op_assign
l_int|0
suffix:semicolon
DECL|variable|blob_objects
r_static
r_int
id|blob_objects
op_assign
l_int|0
suffix:semicolon
DECL|variable|verbose_header
r_static
r_int
id|verbose_header
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_parents
r_static
r_int
id|show_parents
op_assign
l_int|0
suffix:semicolon
DECL|variable|hdr_termination
r_static
r_int
id|hdr_termination
op_assign
l_int|0
suffix:semicolon
DECL|variable|prefix
r_static
r_const
r_char
op_star
id|prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|max_age
r_static
r_int
r_int
id|max_age
op_assign
l_int|1
suffix:semicolon
DECL|variable|min_age
r_static
r_int
r_int
id|min_age
op_assign
l_int|1
suffix:semicolon
DECL|variable|max_count
r_static
r_int
id|max_count
op_assign
l_int|1
suffix:semicolon
DECL|variable|commit_format
r_static
r_enum
id|cmit_fmt
id|commit_format
op_assign
id|CMIT_FMT_RAW
suffix:semicolon
DECL|variable|merge_order
r_static
r_int
id|merge_order
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_breaks
r_static
r_int
id|show_breaks
op_assign
l_int|0
suffix:semicolon
DECL|variable|stop_traversal
r_static
r_int
id|stop_traversal
op_assign
l_int|0
suffix:semicolon
DECL|variable|topo_order
r_static
r_int
id|topo_order
op_assign
l_int|0
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
id|commit-&gt;object.flags
op_or_assign
id|SHOWN
suffix:semicolon
r_if
c_cond
(paren
id|show_breaks
)paren
(brace
id|prefix
op_assign
l_string|&quot;| &quot;
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|DISCONTINUITY
)paren
(brace
id|prefix
op_assign
l_string|&quot;^ &quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|BOUNDARY
)paren
(brace
id|prefix
op_assign
l_string|&quot;= &quot;
suffix:semicolon
)brace
)brace
id|printf
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|prefix
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_parents
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
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|parents-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose_header
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
id|commit_format
comma
id|commit-&gt;buffer
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
)brace
DECL|function|filter_commit
r_static
r_int
id|filter_commit
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
id|stop_traversal
op_logical_and
(paren
id|commit-&gt;object.flags
op_amp
id|BOUNDARY
)paren
)paren
r_return
id|STOP
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
(paren
id|UNINTERESTING
op_or
id|SHOWN
)paren
)paren
r_return
id|CONTINUE
suffix:semicolon
r_if
c_cond
(paren
id|min_age
op_ne
l_int|1
op_logical_and
(paren
id|commit-&gt;date
OG
id|min_age
)paren
)paren
r_return
id|CONTINUE
suffix:semicolon
r_if
c_cond
(paren
id|max_age
op_ne
l_int|1
op_logical_and
(paren
id|commit-&gt;date
OL
id|max_age
)paren
)paren
(brace
id|stop_traversal
op_assign
l_int|1
suffix:semicolon
r_return
id|merge_order
ques
c_cond
id|CONTINUE
suffix:colon
id|STOP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|max_count
op_ne
l_int|1
op_logical_and
op_logical_neg
id|max_count
op_decrement
)paren
r_return
id|STOP
suffix:semicolon
r_return
id|DO
suffix:semicolon
)brace
DECL|function|process_commit
r_static
r_int
id|process_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_int
id|action
op_assign
id|filter_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|STOP
)paren
(brace
r_return
id|STOP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action
op_eq
id|CONTINUE
)paren
(brace
r_return
id|CONTINUE
suffix:semicolon
)brace
id|show_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
r_return
id|CONTINUE
suffix:semicolon
)brace
DECL|function|add_object
r_static
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
id|name
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
DECL|function|process_blob
r_static
r_struct
id|object_list
op_star
op_star
id|process_blob
c_func
(paren
r_struct
id|blob
op_star
id|blob
comma
r_struct
id|object_list
op_star
op_star
id|p
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
id|blob_objects
)paren
r_return
id|p
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
id|p
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
r_return
id|add_object
c_func
(paren
id|obj
comma
id|p
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|process_tree
r_static
r_struct
id|object_list
op_star
op_star
id|process_tree
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_struct
id|object_list
op_star
op_star
id|p
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
id|tree_entry_list
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree_objects
)paren
r_return
id|p
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
id|p
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
id|p
op_assign
id|add_object
c_func
(paren
id|obj
comma
id|p
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|tree-&gt;entries
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;directory
)paren
id|p
op_assign
id|process_tree
c_func
(paren
id|entry-&gt;item.tree
comma
id|p
comma
id|entry-&gt;name
)paren
suffix:semicolon
r_else
id|p
op_assign
id|process_blob
c_func
(paren
id|entry-&gt;item.blob
comma
id|p
comma
id|entry-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|variable|pending_objects
r_static
r_struct
id|object_list
op_star
id|pending_objects
op_assign
l_int|NULL
suffix:semicolon
DECL|function|show_commit_list
r_static
r_void
id|show_commit_list
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_struct
id|object_list
op_star
id|objects
op_assign
l_int|NULL
comma
op_star
op_star
id|p
op_assign
op_amp
id|objects
comma
op_star
id|pending
suffix:semicolon
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
id|pop_most_recent_commit
c_func
(paren
op_amp
id|list
comma
id|SEEN
)paren
suffix:semicolon
id|p
op_assign
id|process_tree
c_func
(paren
id|commit-&gt;tree
comma
id|p
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|process_commit
c_func
(paren
id|commit
)paren
op_eq
id|STOP
)paren
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|pending
op_assign
id|pending_objects
suffix:semicolon
id|pending
suffix:semicolon
id|pending
op_assign
id|pending-&gt;next
)paren
(brace
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
id|tag_type
)paren
(brace
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
id|p
op_assign
id|add_object
c_func
(paren
id|obj
comma
id|p
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
id|tree_type
)paren
(brace
id|p
op_assign
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
id|p
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
id|blob_type
)paren
(brace
id|p
op_assign
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
id|p
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
r_while
c_loop
(paren
id|objects
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|objects-&gt;item-&gt;sha1
)paren
comma
id|objects-&gt;name
)paren
suffix:semicolon
id|objects
op_assign
id|objects-&gt;next
suffix:semicolon
)brace
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
op_logical_neg
id|blob_objects
)paren
r_return
suffix:semicolon
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
r_static
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
op_logical_neg
id|tree_objects
)paren
r_return
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
r_while
c_loop
(paren
id|entry
)paren
(brace
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
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|mark_parents_uninteresting
r_static
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
r_if
c_cond
(paren
id|tree_objects
)paren
id|mark_tree_uninteresting
c_func
(paren
id|commit-&gt;tree
)paren
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
multiline_comment|/*&n;&t;&t; * A missing commit is ok iff its parent is marked &n;&t;&t; * uninteresting.&n;&t;&t; *&n;&t;&t; * We just mark such a thing parsed, so that when&n;&t;&t; * it is popped next time around, we won&squot;t be trying&n;&t;&t; * to parse it and get an error.&n;&t;&t; */
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
DECL|function|everybody_uninteresting
r_static
r_int
id|everybody_uninteresting
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
id|list
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
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
r_int
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
id|p
op_assign
id|p-&gt;next
suffix:semicolon
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
DECL|function|limit_list
r_static
r_struct
id|commit_list
op_star
id|limit_list
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|newlist
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
op_star
id|p
op_assign
op_amp
id|newlist
suffix:semicolon
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
id|pop_most_recent_commit
c_func
(paren
op_amp
id|list
comma
id|SEEN
)paren
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
op_amp
id|commit-&gt;object
suffix:semicolon
r_if
c_cond
(paren
id|unpacked
op_logical_and
id|has_sha1_pack
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
id|obj-&gt;flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
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
r_if
c_cond
(paren
id|everybody_uninteresting
c_func
(paren
id|list
)paren
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|commit_list_insert
c_func
(paren
id|commit
comma
id|p
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bisect_list
)paren
id|newlist
op_assign
id|find_bisection
c_func
(paren
id|newlist
)paren
suffix:semicolon
r_return
id|newlist
suffix:semicolon
)brace
DECL|function|add_pending_object
r_static
r_void
id|add_pending_object
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
)paren
(brace
id|add_object
c_func
(paren
id|obj
comma
op_amp
id|pending_objects
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
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|flags
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
id|object
op_star
id|object
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
id|usage
c_func
(paren
id|rev_list_usage
)paren
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
id|tag_objects
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
id|mark_parents_uninteresting
c_func
(paren
id|commit
)paren
suffix:semicolon
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
id|tree_objects
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
id|blob_objects
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
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|commit_list
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|limited
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
r_int
id|flags
suffix:semicolon
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
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
id|max_count
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
id|max_age
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
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
l_string|&quot;--min-age=&quot;
comma
l_int|10
)paren
)paren
(brace
id|min_age
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
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
l_string|&quot;--header&quot;
)paren
)paren
(brace
id|verbose_header
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
l_string|&quot;--pretty&quot;
comma
l_int|8
)paren
)paren
(brace
id|commit_format
op_assign
id|get_commit_format
c_func
(paren
id|arg
op_plus
l_int|8
)paren
suffix:semicolon
id|verbose_header
op_assign
l_int|1
suffix:semicolon
id|hdr_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|prefix
op_assign
l_string|&quot;commit &quot;
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
l_string|&quot;--parents&quot;
)paren
)paren
(brace
id|show_parents
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
l_string|&quot;--objects&quot;
)paren
)paren
(brace
id|tag_objects
op_assign
l_int|1
suffix:semicolon
id|tree_objects
op_assign
l_int|1
suffix:semicolon
id|blob_objects
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
id|unpacked
op_assign
l_int|1
suffix:semicolon
id|limited
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
l_string|&quot;--merge-order&quot;
)paren
)paren
(brace
id|merge_order
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
l_string|&quot;--show-breaks&quot;
)paren
)paren
(brace
id|show_breaks
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
l_string|&quot;--topo-order&quot;
)paren
)paren
(brace
id|topo_order
op_assign
l_int|1
suffix:semicolon
id|limited
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|flags
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
id|flags
op_assign
id|UNINTERESTING
suffix:semicolon
id|arg
op_increment
suffix:semicolon
id|limited
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_breaks
op_logical_and
op_logical_neg
id|merge_order
)paren
id|usage
c_func
(paren
id|rev_list_usage
)paren
suffix:semicolon
id|commit
op_assign
id|get_commit_reference
c_func
(paren
id|arg
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|SEEN
)paren
r_continue
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
id|list
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|merge_order
)paren
(brace
id|sort_by_date
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|limited
)paren
id|list
op_assign
id|limit_list
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|topo_order
)paren
id|sort_in_topological_order
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
id|show_commit_list
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sort_list_in_merge_order
c_func
(paren
id|list
comma
op_amp
id|process_commit
)paren
)paren
(brace
id|die
c_func
(paren
l_string|&quot;merge order sort failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
