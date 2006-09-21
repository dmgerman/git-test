macro_line|#include &quot;fetch.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;strbuf.h&quot;
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
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
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
r_struct
id|object
op_star
id|obj
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|entry.mode
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
id|entry.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tree
)paren
id|obj
op_assign
op_amp
id|tree-&gt;object
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
id|entry.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blob
)paren
id|obj
op_assign
op_amp
id|blob-&gt;object
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj
op_logical_or
id|process
c_func
(paren
id|obj
)paren
)paren
r_return
l_int|1
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
id|tree-&gt;size
op_assign
l_int|0
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
id|hashcpy
c_func
(paren
id|current_commit_sha1
comma
id|commit-&gt;object.sha1
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
id|OBJ_COMMIT
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
id|OBJ_TREE
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
id|OBJ_BLOB
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
id|OBJ_TAG
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
r_typename
(paren
id|obj-&gt;type
)paren
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
r_typename
(paren
id|obj-&gt;type
)paren
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
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
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
DECL|function|pull_targets_stdin
r_int
id|pull_targets_stdin
c_func
(paren
r_char
op_star
op_star
op_star
id|target
comma
r_const
r_char
op_star
op_star
op_star
id|write_ref
)paren
(brace
r_int
id|targets
op_assign
l_int|0
comma
id|targets_alloc
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
id|buf
suffix:semicolon
op_star
id|target
op_assign
l_int|NULL
suffix:semicolon
op_star
id|write_ref
op_assign
l_int|NULL
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|rf_one
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|tg_one
suffix:semicolon
id|read_line
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.eof
)paren
r_break
suffix:semicolon
id|tg_one
op_assign
id|buf.buf
suffix:semicolon
id|rf_one
op_assign
id|strchr
c_func
(paren
id|tg_one
comma
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rf_one
)paren
op_star
id|rf_one
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|targets
op_ge
id|targets_alloc
)paren
(brace
id|targets_alloc
op_assign
id|targets_alloc
ques
c_cond
id|targets_alloc
op_star
l_int|2
suffix:colon
l_int|64
suffix:semicolon
op_star
id|target
op_assign
id|xrealloc
c_func
(paren
op_star
id|target
comma
id|targets_alloc
op_star
r_sizeof
(paren
op_star
op_star
id|target
)paren
)paren
suffix:semicolon
op_star
id|write_ref
op_assign
id|xrealloc
c_func
(paren
op_star
id|write_ref
comma
id|targets_alloc
op_star
r_sizeof
(paren
op_star
op_star
id|write_ref
)paren
)paren
suffix:semicolon
)brace
(paren
op_star
id|target
)paren
(braket
id|targets
)braket
op_assign
id|xstrdup
c_func
(paren
id|tg_one
)paren
suffix:semicolon
(paren
op_star
id|write_ref
)paren
(braket
id|targets
)braket
op_assign
id|rf_one
ques
c_cond
id|xstrdup
c_func
(paren
id|rf_one
)paren
suffix:colon
l_int|NULL
suffix:semicolon
id|targets
op_increment
suffix:semicolon
)brace
r_return
id|targets
suffix:semicolon
)brace
DECL|function|pull_targets_free
r_void
id|pull_targets_free
c_func
(paren
r_int
id|targets
comma
r_char
op_star
op_star
id|target
comma
r_const
r_char
op_star
op_star
id|write_ref
)paren
(brace
r_while
c_loop
(paren
id|targets
op_decrement
)paren
(brace
id|free
c_func
(paren
id|target
(braket
id|targets
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_ref
op_logical_and
id|write_ref
(braket
id|targets
)braket
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|write_ref
(braket
id|targets
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|pull
r_int
id|pull
c_func
(paren
r_int
id|targets
comma
r_char
op_star
op_star
id|target
comma
r_const
r_char
op_star
op_star
id|write_ref
comma
r_const
r_char
op_star
id|write_ref_log_details
)paren
(brace
r_struct
id|ref_lock
op_star
op_star
id|lock
op_assign
id|xcalloc
c_func
(paren
id|targets
comma
r_sizeof
(paren
r_struct
id|ref_lock
op_star
)paren
)paren
suffix:semicolon
r_int
r_char
op_star
id|sha1
op_assign
id|xmalloc
c_func
(paren
id|targets
op_star
l_int|20
)paren
suffix:semicolon
r_char
op_star
id|msg
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|i
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
id|track_object_refs
op_assign
l_int|0
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
id|targets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|write_ref
op_logical_or
op_logical_neg
id|write_ref
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|lock
(braket
id|i
)braket
op_assign
id|lock_ref_sha1
c_func
(paren
id|write_ref
(braket
id|i
)braket
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
(braket
id|i
)braket
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Can&squot;t lock ref %s&quot;
comma
id|write_ref
(braket
id|i
)braket
)paren
suffix:semicolon
r_goto
id|unlock_and_fail
suffix:semicolon
)brace
)brace
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
comma
l_int|NULL
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
id|targets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|interpret_target
c_func
(paren
id|target
(braket
id|i
)braket
comma
op_amp
id|sha1
(braket
l_int|20
op_star
id|i
)braket
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Could not interpret %s as something to pull&quot;
comma
id|target
(braket
id|i
)braket
)paren
suffix:semicolon
r_goto
id|unlock_and_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|process
c_func
(paren
id|lookup_unknown_object
c_func
(paren
op_amp
id|sha1
(braket
l_int|20
op_star
id|i
)braket
)paren
)paren
)paren
r_goto
id|unlock_and_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loop
c_func
(paren
)paren
)paren
r_goto
id|unlock_and_fail
suffix:semicolon
r_if
c_cond
(paren
id|write_ref_log_details
)paren
(brace
id|msg
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|write_ref_log_details
)paren
op_plus
l_int|12
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|msg
comma
l_string|&quot;fetch from %s&quot;
comma
id|write_ref_log_details
)paren
suffix:semicolon
)brace
r_else
(brace
id|msg
op_assign
l_int|NULL
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
id|targets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|write_ref
op_logical_or
op_logical_neg
id|write_ref
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|write_ref_sha1
c_func
(paren
id|lock
(braket
id|i
)braket
comma
op_amp
id|sha1
(braket
l_int|20
op_star
id|i
)braket
comma
id|msg
ques
c_cond
id|msg
suffix:colon
l_string|&quot;fetch (unknown)&quot;
)paren
suffix:semicolon
id|lock
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|unlock_and_fail
suffix:semicolon
)brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|unlock_and_fail
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|targets
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|lock
(braket
id|i
)braket
)paren
id|unlock_ref
c_func
(paren
id|lock
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
