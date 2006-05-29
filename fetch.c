macro_line|#include &quot;fetch.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|write_ref
r_const
r_char
op_star
id|write_ref
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|get_tree
r_int
id|get_tree
op_assign
l_int|0
suffix:semicolon
DECL|variable|get_history
r_int
id|get_history
op_assign
l_int|0
suffix:semicolon
DECL|variable|get_all
r_int
id|get_all
op_assign
l_int|0
suffix:semicolon
DECL|variable|get_verbosely
r_int
id|get_verbosely
op_assign
l_int|0
suffix:semicolon
DECL|variable|get_recover
r_int
id|get_recover
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_commit_sha1
r_static
r_int
r_char
id|current_commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|pull_say
r_void
id|pull_say
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
r_const
r_char
op_star
id|hex
)paren
(brace
r_if
c_cond
(paren
id|get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
id|fmt
comma
id|hex
)paren
suffix:semicolon
)brace
DECL|function|report_missing
r_static
r_void
id|report_missing
c_func
(paren
r_const
r_char
op_star
id|what
comma
r_const
r_int
r_char
op_star
id|missing
)paren
(brace
r_char
id|missing_hex
(braket
l_int|41
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|missing_hex
comma
id|sha1_to_hex
c_func
(paren
id|missing
)paren
)paren
suffix:semicolon
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Cannot obtain needed %s %s&bslash;nwhile processing commit %s.&bslash;n&quot;
comma
id|what
comma
id|missing_hex
comma
id|sha1_to_hex
c_func
(paren
id|current_commit_sha1
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|process
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
suffix:semicolon
DECL|function|process_tree
r_static
r_int
id|process_tree
c_func
(paren
r_struct
id|tree
op_star
id|tree
)paren
(brace
r_struct
id|tree_entry_list
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|parse_tree
c_func
(paren
id|tree
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|entry
op_assign
id|create_tree_entry_list
c_func
(paren
id|tree
)paren
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
(brace
r_struct
id|tree
op_star
id|tree
op_assign
id|lookup_tree
c_func
(paren
id|entry-&gt;sha1
)paren
suffix:semicolon
id|process_tree
c_func
(paren
id|tree
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|blob
op_star
id|blob
op_assign
id|lookup_blob
c_func
(paren
id|entry-&gt;sha1
)paren
suffix:semicolon
id|process
c_func
(paren
op_amp
id|blob-&gt;object
)paren
suffix:semicolon
)brace
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|COMPLETE
mdefine_line|#define COMPLETE&t;(1U &lt;&lt; 0)
DECL|macro|SEEN
mdefine_line|#define SEEN&t;&t;(1U &lt;&lt; 1)
DECL|macro|TO_SCAN
mdefine_line|#define TO_SCAN&t;&t;(1U &lt;&lt; 2)
DECL|variable|complete
r_static
r_struct
id|commit_list
op_star
id|complete
op_assign
l_int|NULL
suffix:semicolon
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
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|complete
op_logical_and
id|complete-&gt;item-&gt;date
op_ge
id|commit-&gt;date
)paren
(brace
id|pop_most_recent_commit
c_func
(paren
op_amp
id|complete
comma
id|COMPLETE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|COMPLETE
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|current_commit_sha1
comma
id|commit-&gt;object.sha1
comma
l_int|20
)paren
suffix:semicolon
id|pull_say
c_func
(paren
l_string|&quot;walk %s&bslash;n&quot;
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
id|get_tree
)paren
(brace
r_if
c_cond
(paren
id|process
c_func
(paren
op_amp
id|commit-&gt;tree-&gt;object
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_all
)paren
id|get_tree
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_history
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|process
c_func
(paren
op_amp
id|parents-&gt;item-&gt;object
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|process_tag
r_static
r_int
id|process_tag
c_func
(paren
r_struct
id|tag
op_star
id|tag
)paren
(brace
r_if
c_cond
(paren
id|parse_tag
c_func
(paren
id|tag
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|process
c_func
(paren
id|tag-&gt;tagged
)paren
suffix:semicolon
)brace
DECL|variable|process_queue
r_static
r_struct
id|object_list
op_star
id|process_queue
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|process_queue_end
r_static
r_struct
id|object_list
op_star
op_star
id|process_queue_end
op_assign
op_amp
id|process_queue
suffix:semicolon
DECL|function|process_object
r_static
r_int
id|process_object
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|commit_type
)paren
(brace
r_if
c_cond
(paren
id|process_commit
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
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
r_if
c_cond
(paren
id|process_tree
c_func
(paren
(paren
r_struct
id|tree
op_star
)paren
id|obj
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
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
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|tag_type
)paren
(brace
r_if
c_cond
(paren
id|process_tag
c_func
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;Unable to determine requirements &quot;
l_string|&quot;of type %s for %s&quot;
comma
id|obj-&gt;type
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|process
r_static
r_int
id|process
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
l_int|0
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
(brace
multiline_comment|/* We already have it, so we should scan it now. */
id|obj-&gt;flags
op_or_assign
id|TO_SCAN
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|COMPLETE
)paren
r_return
l_int|0
suffix:semicolon
id|prefetch
c_func
(paren
id|obj-&gt;sha1
)paren
suffix:semicolon
)brace
id|object_list_insert
c_func
(paren
id|obj
comma
id|process_queue_end
)paren
suffix:semicolon
id|process_queue_end
op_assign
op_amp
(paren
op_star
id|process_queue_end
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|loop
r_static
r_int
id|loop
c_func
(paren
r_void
)paren
(brace
r_struct
id|object_list
op_star
id|elem
suffix:semicolon
r_while
c_loop
(paren
id|process_queue
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|process_queue-&gt;item
suffix:semicolon
id|elem
op_assign
id|process_queue
suffix:semicolon
id|process_queue
op_assign
id|elem-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|elem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|process_queue
)paren
id|process_queue_end
op_assign
op_amp
id|process_queue
suffix:semicolon
multiline_comment|/* If we are not scanning this object, we placed it in&n;&t;&t; * the queue because we needed to fetch it first.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|obj-&gt;flags
op_amp
id|TO_SCAN
)paren
)paren
(brace
r_if
c_cond
(paren
id|fetch
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
(brace
id|report_missing
c_func
(paren
id|obj-&gt;type
ques
c_cond
id|obj-&gt;type
suffix:colon
l_string|&quot;object&quot;
comma
id|obj-&gt;sha1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;type
)paren
id|parse_object
c_func
(paren
id|obj-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|process_object
c_func
(paren
id|obj
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|interpret_target
r_static
r_int
id|interpret_target
c_func
(paren
r_char
op_star
id|target
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|target
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_ref_format
c_func
(paren
id|target
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fetch_ref
c_func
(paren
id|target
comma
id|sha1
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mark_complete
r_static
r_int
id|mark_complete
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
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit
)paren
(brace
id|commit-&gt;object.flags
op_or_assign
id|COMPLETE
suffix:semicolon
id|insert_by_date
c_func
(paren
id|commit
comma
op_amp
id|complete
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pull
r_int
id|pull
c_func
(paren
r_char
op_star
id|target
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
id|track_object_refs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_recover
)paren
id|for_each_ref
c_func
(paren
id|mark_complete
)paren
suffix:semicolon
r_if
c_cond
(paren
id|interpret_target
c_func
(paren
id|target
comma
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not interpret %s as something to pull&quot;
comma
id|target
)paren
suffix:semicolon
r_if
c_cond
(paren
id|process
c_func
(paren
id|lookup_unknown_object
c_func
(paren
id|sha1
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|loop
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_ref
)paren
id|write_ref_sha1_unlocked
c_func
(paren
id|write_ref
comma
id|sha1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
