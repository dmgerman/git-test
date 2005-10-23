macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|quiet
r_static
r_int
id|quiet
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|variable|fetch_pack_usage
r_static
r_const
r_char
id|fetch_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-fetch-pack [-q] [-v] [--exec=upload-pack] [host:]directory &lt;refs&gt;...&quot;
suffix:semicolon
DECL|variable|exec
r_static
r_const
r_char
op_star
id|exec
op_assign
l_string|&quot;git-upload-pack&quot;
suffix:semicolon
DECL|macro|COMPLETE
mdefine_line|#define COMPLETE&t;(1U &lt;&lt; 0)
DECL|macro|COMMON
mdefine_line|#define COMMON&t;&t;(1U &lt;&lt; 1)
DECL|macro|COMMON_REF
mdefine_line|#define COMMON_REF&t;(1U &lt;&lt; 2 | COMMON)
DECL|macro|SEEN
mdefine_line|#define SEEN&t;&t;(1U &lt;&lt; 3)
DECL|macro|POPPED
mdefine_line|#define POPPED&t;&t;(1U &lt;&lt; 4)
DECL|variable|rev_list
r_static
r_struct
id|commit_list
op_star
id|rev_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|rev_list_end
r_static
r_struct
id|commit_list
op_star
id|rev_list_end
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|non_common_revs
r_static
r_int
r_int
id|non_common_revs
op_assign
l_int|0
suffix:semicolon
DECL|function|rev_list_append
r_static
r_void
id|rev_list_append
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
id|mark
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|mark
)paren
)paren
(brace
id|commit-&gt;object.flags
op_or_assign
id|mark
suffix:semicolon
r_if
c_cond
(paren
id|rev_list
op_eq
l_int|NULL
)paren
(brace
id|commit_list_insert
c_func
(paren
id|commit
comma
op_amp
id|rev_list
)paren
suffix:semicolon
id|rev_list_end
op_assign
id|rev_list
suffix:semicolon
)brace
r_else
(brace
id|commit_list_insert
c_func
(paren
id|commit
comma
op_amp
(paren
id|rev_list_end-&gt;next
)paren
)paren
suffix:semicolon
id|rev_list_end
op_assign
id|rev_list_end-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|COMMON
)paren
)paren
id|non_common_revs
op_increment
suffix:semicolon
)brace
)brace
DECL|function|rev_list_append_sha1
r_static
r_int
id|rev_list_append_sha1
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
id|object
op_star
id|o
op_assign
id|deref_tag
c_func
(paren
id|parse_object
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|commit_type
)paren
id|rev_list_append
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o
comma
id|SEEN
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mark_common
r_static
r_void
id|mark_common
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
id|commit
op_ne
l_int|NULL
op_logical_and
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|COMMON
)paren
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
(paren
r_struct
id|object
op_star
)paren
id|commit
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|COMMON
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|SEEN
)paren
)paren
id|rev_list_append
c_func
(paren
id|commit
comma
id|SEEN
)paren
suffix:semicolon
r_else
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|POPPED
)paren
)paren
id|non_common_revs
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o-&gt;parsed
)paren
id|parse_commit
c_func
(paren
id|commit
)paren
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
id|mark_common
c_func
(paren
id|parents-&gt;item
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;  Get the next rev to send, ignoring the common.&n;*/
DECL|function|get_rev
r_static
r_const
r_int
r_char
op_star
id|get_rev
c_func
(paren
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|commit
op_eq
l_int|NULL
)paren
(brace
r_int
r_int
id|mark
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
id|rev_list
op_eq
l_int|NULL
op_logical_or
id|non_common_revs
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|commit
op_assign
id|rev_list-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.parsed
)paren
)paren
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|POPPED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|COMMON
)paren
)paren
id|non_common_revs
op_decrement
suffix:semicolon
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|COMMON
)paren
(brace
multiline_comment|/* do not send &quot;have&quot;, and ignore ancestors */
id|commit
op_assign
l_int|NULL
suffix:semicolon
id|mark
op_assign
id|COMMON
op_or
id|SEEN
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|COMMON_REF
)paren
multiline_comment|/* send &quot;have&quot;, and ignore ancestors */
id|mark
op_assign
id|COMMON
op_or
id|SEEN
suffix:semicolon
r_else
multiline_comment|/* send &quot;have&quot;, also for its ancestors */
id|mark
op_assign
id|SEEN
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_if
c_cond
(paren
id|mark
op_amp
id|COMMON
)paren
id|mark_common
c_func
(paren
id|parents-&gt;item
)paren
suffix:semicolon
r_else
id|rev_list_append
c_func
(paren
id|parents-&gt;item
comma
id|mark
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
id|rev_list
op_assign
id|rev_list-&gt;next
suffix:semicolon
)brace
r_return
id|commit-&gt;object.sha1
suffix:semicolon
)brace
DECL|function|find_common
r_static
r_int
id|find_common
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
r_char
op_star
id|result_sha1
comma
r_struct
id|ref
op_star
id|refs
)paren
(brace
r_int
id|fetching
suffix:semicolon
r_int
id|count
op_assign
l_int|0
comma
id|flushes
op_assign
l_int|0
comma
id|multi_ack
op_assign
l_int|0
comma
id|retval
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
id|for_each_ref
c_func
(paren
id|rev_list_append_sha1
)paren
suffix:semicolon
id|fetching
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|refs
suffix:semicolon
id|refs
op_assign
id|refs-&gt;next
)paren
(brace
r_int
r_char
op_star
id|remote
op_assign
id|refs-&gt;old_sha1
suffix:semicolon
r_struct
id|object
op_star
id|o
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If that object is complete (i.e. it is an ancestor of a&n;&t;&t; * local ref), we tell them we have it but do not have to&n;&t;&t; * tell them about its ancestors, which they already know&n;&t;&t; * about.&n;&t;&t; *&n;&t;&t; * We use lookup_object here because we are only&n;&t;&t; * interested in the case we *know* the object is&n;&t;&t; * reachable and we have already scanned it.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|o
op_assign
id|lookup_object
c_func
(paren
id|remote
)paren
)paren
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|o-&gt;flags
op_amp
id|COMPLETE
)paren
)paren
(brace
id|o
op_assign
id|deref_tag
c_func
(paren
id|o
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|commit_type
)paren
id|rev_list_append
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o
comma
id|COMMON_REF
op_or
id|SEEN
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;want %s multi_ack&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|remote
)paren
)paren
suffix:semicolon
id|fetching
op_increment
suffix:semicolon
)brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fetching
)paren
r_return
l_int|1
suffix:semicolon
id|flushes
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|sha1
op_assign
id|get_rev
c_func
(paren
)paren
)paren
)paren
(brace
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;have %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;have %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
l_int|31
op_amp
op_increment
id|count
)paren
)paren
(brace
r_int
id|ack
suffix:semicolon
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|flushes
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We keep one window &quot;ahead&quot; of the other side, and&n;&t;&t;&t; * will wait for an ACK only on the next one&n;&t;&t;&t; */
r_if
c_cond
(paren
id|count
op_eq
l_int|32
)paren
r_continue
suffix:semicolon
r_do
(brace
id|ack
op_assign
id|get_ack
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|result_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
op_logical_and
id|ack
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;got ack %d %s&bslash;n&quot;
comma
id|ack
comma
id|sha1_to_hex
c_func
(paren
id|result_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|multi_ack
)paren
id|flushes
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ack
op_eq
l_int|2
)paren
(brace
id|multi_ack
op_assign
l_int|1
suffix:semicolon
id|mark_common
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|lookup_object
c_func
(paren
id|result_sha1
)paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|ack
)paren
(brace
suffix:semicolon
)brace
id|flushes
op_decrement
suffix:semicolon
)brace
)brace
id|done
suffix:colon
r_if
c_cond
(paren
id|multi_ack
)paren
(brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|flushes
op_increment
suffix:semicolon
)brace
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
id|flushes
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|flushes
)paren
(brace
r_if
c_cond
(paren
id|get_ack
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|result_sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;got ack %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|result_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|multi_ack
)paren
r_return
l_int|0
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|flushes
op_decrement
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|complete
r_static
r_struct
id|commit_list
op_star
id|complete
op_assign
l_int|NULL
suffix:semicolon
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
r_while
c_loop
(paren
id|o
op_logical_and
id|o-&gt;type
op_eq
id|tag_type
)paren
(brace
r_struct
id|tag
op_star
id|t
op_assign
(paren
r_struct
id|tag
op_star
)paren
id|o
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;tagged
)paren
r_break
suffix:semicolon
multiline_comment|/* broken repository */
id|o-&gt;flags
op_or_assign
id|COMPLETE
suffix:semicolon
id|o
op_assign
id|parse_object
c_func
(paren
id|t-&gt;tagged-&gt;sha1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o
op_logical_and
id|o-&gt;type
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
id|o
suffix:semicolon
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
DECL|function|mark_recent_complete_commits
r_static
r_void
id|mark_recent_complete_commits
c_func
(paren
r_int
r_int
id|cutoff
)paren
(brace
r_while
c_loop
(paren
id|complete
op_logical_and
id|cutoff
op_le
id|complete-&gt;item-&gt;date
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Marking %s as complete&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|complete-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
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
)brace
DECL|function|everything_local
r_static
r_int
id|everything_local
c_func
(paren
r_struct
id|ref
op_star
id|refs
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
r_int
id|cutoff
op_assign
l_int|0
suffix:semicolon
id|track_object_refs
op_assign
l_int|0
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|refs
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_struct
id|object
op_star
id|o
suffix:semicolon
id|o
op_assign
id|parse_object
c_func
(paren
id|ref-&gt;old_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
)paren
r_continue
suffix:semicolon
multiline_comment|/* We already have it -- which may mean that we were&n;&t;&t; * in sync with the other side at some time after&n;&t;&t; * that (it is OK if we guess wrong here).&n;&t;&t; */
r_if
c_cond
(paren
id|o-&gt;type
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
id|o
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cutoff
op_logical_or
id|cutoff
OL
id|commit-&gt;date
)paren
id|cutoff
op_assign
id|commit-&gt;date
suffix:semicolon
)brace
)brace
id|for_each_ref
c_func
(paren
id|mark_complete
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cutoff
)paren
id|mark_recent_complete_commits
c_func
(paren
id|cutoff
)paren
suffix:semicolon
r_for
c_loop
(paren
id|retval
op_assign
l_int|1
suffix:semicolon
id|refs
suffix:semicolon
id|refs
op_assign
id|refs-&gt;next
)paren
(brace
r_const
r_int
r_char
op_star
id|remote
op_assign
id|refs-&gt;old_sha1
suffix:semicolon
r_int
r_char
id|local
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|object
op_star
id|o
suffix:semicolon
id|o
op_assign
id|parse_object
c_func
(paren
id|remote
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_or
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|COMPLETE
)paren
)paren
(brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose
)paren
r_continue
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;want %s (%s)&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|remote
)paren
comma
id|refs-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|refs-&gt;new_sha1
comma
id|local
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose
)paren
r_continue
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;already have %s (%s)&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|remote
)paren
comma
id|refs-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fetch_pack
r_static
r_int
id|fetch_pack
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
id|nr_match
comma
r_char
op_star
op_star
id|match
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|get_remote_heads
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
op_amp
id|ref
comma
id|nr_match
comma
id|match
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref
)paren
(brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;no matching remote head&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|everything_local
c_func
(paren
id|ref
)paren
)paren
(brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_goto
id|all_done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|find_common
c_func
(paren
id|fd
comma
id|sha1
comma
id|ref
)paren
OL
l_int|0
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: no common commits&bslash;n&quot;
)paren
suffix:semicolon
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: unable to fork off git-unpack-objects&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|dup2
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;git-unpack-objects&quot;
comma
l_string|&quot;git-unpack-objects&quot;
comma
id|quiet
ques
c_cond
l_string|&quot;-q&quot;
suffix:colon
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects exec failed&quot;
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
id|die
c_func
(paren
l_string|&quot;waiting for git-unpack-objects: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died with error code %d&quot;
comma
id|code
)paren
suffix:semicolon
id|all_done
suffix:colon
r_while
c_loop
(paren
id|ref
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
id|ref-&gt;old_sha1
)paren
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|sig
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died of signal %d&quot;
comma
id|sig
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;Sherlock Holmes! git-unpack-objects died of unnatural causes %d!&quot;
comma
id|status
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
r_int
id|i
comma
id|ret
comma
id|nr_heads
suffix:semicolon
r_char
op_star
id|dest
op_assign
l_int|NULL
comma
op_star
op_star
id|heads
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|nr_heads
op_assign
l_int|0
suffix:semicolon
id|heads
op_assign
l_int|NULL
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
l_string|&quot;--exec=&quot;
comma
id|arg
comma
l_int|7
)paren
)paren
(brace
id|exec
op_assign
id|arg
op_plus
l_int|7
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
l_string|&quot;-q&quot;
comma
id|arg
)paren
)paren
(brace
id|quiet
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
l_string|&quot;-v&quot;
comma
id|arg
)paren
)paren
(brace
id|verbose
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|fetch_pack_usage
)paren
suffix:semicolon
)brace
id|dest
op_assign
id|arg
suffix:semicolon
id|heads
op_assign
id|argv
op_plus
id|i
op_plus
l_int|1
suffix:semicolon
id|nr_heads
op_assign
id|argc
id|i
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
id|usage
c_func
(paren
id|fetch_pack_usage
)paren
suffix:semicolon
id|pid
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|dest
comma
id|exec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
id|fetch_pack
c_func
(paren
id|fd
comma
id|nr_heads
comma
id|heads
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|finish_connect
c_func
(paren
id|pid
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
