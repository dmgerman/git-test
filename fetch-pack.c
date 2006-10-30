macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|keep_pack
r_static
r_int
id|keep_pack
suffix:semicolon
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
DECL|variable|fetch_all
r_static
r_int
id|fetch_all
suffix:semicolon
DECL|variable|fetch_pack_usage
r_static
r_const
r_char
id|fetch_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-fetch-pack [--all] [-q] [-v] [-k] [--thin] [--exec=upload-pack] [host:]directory &lt;refs&gt;...&quot;
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
mdefine_line|#define COMMON_REF&t;(1U &lt;&lt; 2)
DECL|macro|SEEN
mdefine_line|#define SEEN&t;&t;(1U &lt;&lt; 3)
DECL|macro|POPPED
mdefine_line|#define POPPED&t;&t;(1U &lt;&lt; 4)
multiline_comment|/*&n; * After sending this many &quot;have&quot;s if we do not get any new ACK , we&n; * give up traversing our history.&n; */
DECL|macro|MAX_IN_VAIN
mdefine_line|#define MAX_IN_VAIN 256
DECL|variable|rev_list
r_static
r_struct
id|commit_list
op_star
id|rev_list
suffix:semicolon
DECL|variable|non_common_revs
DECL|variable|multi_ack
DECL|variable|use_thin_pack
DECL|variable|use_sideband
r_static
r_int
id|non_common_revs
comma
id|multi_ack
comma
id|use_thin_pack
comma
id|use_sideband
suffix:semicolon
DECL|function|rev_list_push
r_static
r_void
id|rev_list_push
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
id|insert_by_date
c_func
(paren
id|commit
comma
op_amp
id|rev_list
)paren
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
op_increment
suffix:semicolon
)brace
)brace
DECL|function|rev_list_insert_ref
r_static
r_int
id|rev_list_insert_ref
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
comma
id|path
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o
op_logical_and
id|o-&gt;type
op_eq
id|OBJ_COMMIT
)paren
id|rev_list_push
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
multiline_comment|/*&n;   This function marks a rev and its ancestors as common.&n;   In some cases, it is desirable to mark only the ancestors (for example&n;   when only the server does not yet know that they are common).&n;*/
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
comma
r_int
id|ancestors_only
comma
r_int
id|dont_parse
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
r_if
c_cond
(paren
op_logical_neg
id|ancestors_only
)paren
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
id|rev_list_push
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
id|ancestors_only
op_logical_and
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
op_logical_and
op_logical_neg
id|dont_parse
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
comma
l_int|0
comma
id|dont_parse
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
r_void
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
op_logical_neg
(paren
id|parents-&gt;item-&gt;object.flags
op_amp
id|SEEN
)paren
)paren
id|rev_list_push
c_func
(paren
id|parents-&gt;item
comma
id|mark
)paren
suffix:semicolon
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
comma
l_int|1
comma
l_int|0
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
id|retval
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|in_vain
op_assign
l_int|0
suffix:semicolon
r_int
id|got_continue
op_assign
l_int|0
suffix:semicolon
id|for_each_ref
c_func
(paren
id|rev_list_insert_ref
comma
l_int|NULL
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
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fetching
)paren
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;want %s%s%s%s%s%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|remote
)paren
comma
(paren
id|multi_ack
ques
c_cond
l_string|&quot; multi_ack&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
(paren
id|use_sideband
op_eq
l_int|2
ques
c_cond
l_string|&quot; side-band-64k&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
(paren
id|use_sideband
op_eq
l_int|1
ques
c_cond
l_string|&quot; side-band&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
(paren
id|use_thin_pack
ques
c_cond
l_string|&quot; thin-pack&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
l_string|&quot; ofs-delta&quot;
)paren
suffix:semicolon
r_else
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;want %s&bslash;n&quot;
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
r_if
c_cond
(paren
id|is_repository_shallow
c_func
(paren
)paren
)paren
id|write_shallow_commits
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_int|1
)paren
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
id|in_vain
op_increment
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
id|flushes
op_assign
l_int|0
suffix:semicolon
id|multi_ack
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
r_struct
id|commit
op_star
id|commit
op_assign
id|lookup_commit
c_func
(paren
id|result_sha1
)paren
suffix:semicolon
id|mark_common
c_func
(paren
id|commit
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|in_vain
op_assign
l_int|0
suffix:semicolon
id|got_continue
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|ack
)paren
suffix:semicolon
id|flushes
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|got_continue
op_logical_and
id|MAX_IN_VAIN
OL
id|in_vain
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
l_string|&quot;giving up&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* give up */
)brace
)brace
)brace
id|done
suffix:colon
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
(brace
id|multi_ack
op_assign
l_int|0
suffix:semicolon
id|flushes
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|flushes
op_logical_or
id|multi_ack
)paren
(brace
r_int
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
id|ack
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
l_string|&quot;got ack (%d) %s&bslash;n&quot;
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
r_return
l_int|0
suffix:semicolon
id|multi_ack
op_assign
l_int|1
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
id|OBJ_TAG
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
id|OBJ_COMMIT
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
DECL|function|filter_refs
r_static
r_void
id|filter_refs
c_func
(paren
r_struct
id|ref
op_star
op_star
id|refs
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
op_star
id|return_refs
suffix:semicolon
r_struct
id|ref
op_star
id|newlist
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
op_star
id|newtail
op_assign
op_amp
id|newlist
suffix:semicolon
r_struct
id|ref
op_star
id|ref
comma
op_star
id|next
suffix:semicolon
r_struct
id|ref
op_star
id|fastarray
(braket
l_int|32
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nr_match
op_logical_and
op_logical_neg
id|fetch_all
)paren
(brace
r_if
c_cond
(paren
id|ARRAY_SIZE
c_func
(paren
id|fastarray
)paren
OL
id|nr_match
)paren
id|return_refs
op_assign
id|xcalloc
c_func
(paren
id|nr_match
comma
r_sizeof
(paren
r_struct
id|ref
op_star
)paren
)paren
suffix:semicolon
r_else
(brace
id|return_refs
op_assign
id|fastarray
suffix:semicolon
id|memset
c_func
(paren
id|return_refs
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ref
op_star
)paren
op_star
id|nr_match
)paren
suffix:semicolon
)brace
)brace
r_else
id|return_refs
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
op_star
id|refs
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|next
)paren
(brace
id|next
op_assign
id|ref-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
op_logical_and
id|check_ref_format
c_func
(paren
id|ref-&gt;name
op_plus
l_int|5
)paren
)paren
suffix:semicolon
multiline_comment|/* trash */
r_else
r_if
c_cond
(paren
id|fetch_all
)paren
(brace
op_star
id|newtail
op_assign
id|ref
suffix:semicolon
id|ref-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|newtail
op_assign
op_amp
id|ref-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
r_int
id|order
op_assign
id|path_match
c_func
(paren
id|ref-&gt;name
comma
id|nr_match
comma
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|order
)paren
(brace
id|return_refs
(braket
id|order
op_minus
l_int|1
)braket
op_assign
id|ref
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* we will link it later */
)brace
)brace
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fetch_all
)paren
(brace
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
id|nr_match
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ref
op_assign
id|return_refs
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ref
)paren
(brace
op_star
id|newtail
op_assign
id|ref
suffix:semicolon
id|ref-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|newtail
op_assign
op_amp
id|ref-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|return_refs
op_ne
id|fastarray
)paren
id|free
c_func
(paren
id|return_refs
)paren
suffix:semicolon
)brace
op_star
id|refs
op_assign
id|newlist
suffix:semicolon
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
op_star
id|refs
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
op_star
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
id|OBJ_COMMIT
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
comma
l_int|NULL
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
multiline_comment|/*&n;&t; * Mark all complete remote refs as common refs.&n;&t; * Don&squot;t mark them common yet; the server has to be told so first.&n;&t; */
r_for
c_loop
(paren
id|ref
op_assign
op_star
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
op_assign
id|deref_tag
c_func
(paren
id|lookup_object
c_func
(paren
id|ref-&gt;old_sha1
)paren
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
id|o
op_logical_or
id|o-&gt;type
op_ne
id|OBJ_COMMIT
op_logical_or
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|COMPLETE
)paren
)paren
r_continue
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
(brace
id|rev_list_push
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
id|mark_common
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|filter_refs
c_func
(paren
id|refs
comma
id|nr_match
comma
id|match
)paren
suffix:semicolon
r_for
c_loop
(paren
id|retval
op_assign
l_int|1
comma
id|ref
op_assign
op_star
id|refs
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_const
r_int
r_char
op_star
id|remote
op_assign
id|ref-&gt;old_sha1
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
id|lookup_object
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
id|ref-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|hashcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|local
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
id|ref-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|setup_sideband
r_static
id|pid_t
id|setup_sideband
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
id|xd
(braket
l_int|2
)braket
)paren
(brace
id|pid_t
id|side_pid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_sideband
)paren
(brace
id|fd
(braket
l_int|0
)braket
op_assign
id|xd
(braket
l_int|0
)braket
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
id|xd
(braket
l_int|1
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* xd[] is talking with upload-pack; subprocess reads from&n;&t; * xd[0], spits out band#2 to stderr, and feeds us band#1&n;&t; * through our fd[0].&n;&t; */
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fd
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;fetch-pack: unable to set up pipe&quot;
)paren
suffix:semicolon
id|side_pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|side_pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;fetch-pack: unable to fork off sideband demultiplexer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|side_pid
)paren
(brace
multiline_comment|/* subprocess */
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xd
(braket
l_int|0
)braket
op_ne
id|xd
(braket
l_int|1
)braket
)paren
id|close
c_func
(paren
id|xd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recv_sideband
c_func
(paren
l_string|&quot;fetch-pack&quot;
comma
id|xd
(braket
l_int|0
)braket
comma
id|fd
(braket
l_int|1
)braket
comma
l_int|2
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|xd
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
id|fd
(braket
l_int|1
)braket
op_assign
id|xd
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|side_pid
suffix:semicolon
)brace
DECL|function|get_pack
r_static
r_int
id|get_pack
c_func
(paren
r_int
id|xd
(braket
l_int|2
)braket
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
comma
id|side_pid
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
id|side_pid
op_assign
id|setup_sideband
c_func
(paren
id|fd
comma
id|xd
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
l_string|&quot;fetch-pack: unable to fork off %s&quot;
comma
id|argv
(braket
l_int|0
)braket
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
id|execv_git_cmd
c_func
(paren
id|argv
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;%s exec failed&quot;
comma
id|argv
(braket
l_int|0
)braket
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
l_string|&quot;waiting for %s: %s&quot;
comma
id|argv
(braket
l_int|0
)braket
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
l_string|&quot;%s died with error code %d&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|code
)paren
suffix:semicolon
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
l_string|&quot;%s died of signal %d&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|sig
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;%s died of unnatural causes %d&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|explode_rx_pack
r_static
r_int
id|explode_rx_pack
c_func
(paren
r_int
id|xd
(braket
l_int|2
)braket
)paren
(brace
r_const
r_char
op_star
id|argv
(braket
l_int|3
)braket
op_assign
(brace
l_string|&quot;unpack-objects&quot;
comma
id|quiet
ques
c_cond
l_string|&quot;-q&quot;
suffix:colon
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_return
id|get_pack
c_func
(paren
id|xd
comma
id|argv
)paren
suffix:semicolon
)brace
DECL|function|keep_rx_pack
r_static
r_int
id|keep_rx_pack
c_func
(paren
r_int
id|xd
(braket
l_int|2
)braket
)paren
(brace
r_const
r_char
op_star
id|argv
(braket
l_int|6
)braket
suffix:semicolon
r_char
id|keep_arg
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|argv
(braket
id|n
op_increment
)braket
op_assign
l_string|&quot;index-pack&quot;
suffix:semicolon
id|argv
(braket
id|n
op_increment
)braket
op_assign
l_string|&quot;--stdin&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|argv
(braket
id|n
op_increment
)braket
op_assign
l_string|&quot;-v&quot;
suffix:semicolon
r_if
c_cond
(paren
id|use_thin_pack
)paren
id|argv
(braket
id|n
op_increment
)braket
op_assign
l_string|&quot;--fix-thin&quot;
suffix:semicolon
r_if
c_cond
(paren
id|keep_pack
OG
l_int|1
)paren
(brace
r_int
id|s
op_assign
id|sprintf
c_func
(paren
id|keep_arg
comma
l_string|&quot;--keep=fetch-pack %i on &quot;
comma
id|getpid
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gethostname
c_func
(paren
id|keep_arg
op_plus
id|s
comma
r_sizeof
(paren
id|keep_arg
)paren
id|s
)paren
)paren
id|strcpy
c_func
(paren
id|keep_arg
op_plus
id|s
comma
l_string|&quot;localhost&quot;
)paren
suffix:semicolon
id|argv
(braket
id|n
op_increment
)braket
op_assign
id|keep_arg
suffix:semicolon
)brace
id|argv
(braket
id|n
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|get_pack
c_func
(paren
id|xd
comma
id|argv
)paren
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
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_repository_shallow
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|server_supports
c_func
(paren
l_string|&quot;shallow&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Server does not support shallow clients&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;multi_ack&quot;
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
l_string|&quot;Server supports multi_ack&bslash;n&quot;
)paren
suffix:semicolon
id|multi_ack
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;side-band-64k&quot;
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
l_string|&quot;Server supports side-band-64k&bslash;n&quot;
)paren
suffix:semicolon
id|use_sideband
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;side-band&quot;
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
l_string|&quot;Server supports side-band&bslash;n&quot;
)paren
suffix:semicolon
id|use_sideband
op_assign
l_int|1
suffix:semicolon
)brace
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
op_amp
id|ref
comma
id|nr_match
comma
id|match
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
r_if
c_cond
(paren
id|keep_pack
op_ne
l_int|1
)paren
multiline_comment|/* When cloning, it is not unusual to have&n;&t;&t;&t; * no common commit.&n;&t;&t;&t; */
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: no common commits&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
(paren
id|keep_pack
)paren
ques
c_cond
id|keep_rx_pack
c_func
(paren
id|fd
)paren
suffix:colon
id|explode_rx_pack
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|die
c_func
(paren
l_string|&quot;git-fetch-pack: fetch failed.&quot;
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
id|setup_git_directory
c_func
(paren
)paren
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
l_string|&quot;--quiet&quot;
comma
id|arg
)paren
op_logical_or
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
l_string|&quot;--keep&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-k&quot;
comma
id|arg
)paren
)paren
(brace
id|keep_pack
op_increment
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
l_string|&quot;--thin&quot;
comma
id|arg
)paren
)paren
(brace
id|use_thin_pack
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
l_string|&quot;--all&quot;
comma
id|arg
)paren
)paren
(brace
id|fetch_all
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
id|ret
op_or_assign
id|finish_connect
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|nr_heads
)paren
(brace
multiline_comment|/* If the heads to pull were given, we should have&n;&t;&t; * consumed all of them by matching the remote.&n;&t;&t; * Otherwise, &squot;git-fetch remote no-such-ref&squot; would&n;&t;&t; * silently succeed without issuing an error.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_heads
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|heads
(braket
id|i
)braket
op_logical_and
id|heads
(braket
id|i
)braket
(braket
l_int|0
)braket
)paren
(brace
id|error
c_func
(paren
l_string|&quot;no such remote ref %s&quot;
comma
id|heads
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
op_logical_neg
op_logical_neg
id|ret
suffix:semicolon
)brace
eof
