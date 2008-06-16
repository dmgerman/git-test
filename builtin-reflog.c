macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;reachable.h&quot;
multiline_comment|/*&n; * reflog expire&n; */
DECL|variable|reflog_expire_usage
r_static
r_const
r_char
id|reflog_expire_usage
(braket
)braket
op_assign
l_string|&quot;git-reflog (show|expire) [--verbose] [--dry-run] [--stale-fix] [--expire=&lt;time&gt;] [--expire-unreachable=&lt;time&gt;] [--all] &lt;refs&gt;...&quot;
suffix:semicolon
DECL|variable|reflog_delete_usage
r_static
r_const
r_char
id|reflog_delete_usage
(braket
)braket
op_assign
l_string|&quot;git-reflog delete [--verbose] [--dry-run] [--rewrite] [--updateref] &lt;refs&gt;...&quot;
suffix:semicolon
DECL|variable|default_reflog_expire
r_static
r_int
r_int
id|default_reflog_expire
suffix:semicolon
DECL|variable|default_reflog_expire_unreachable
r_static
r_int
r_int
id|default_reflog_expire_unreachable
suffix:semicolon
DECL|struct|cmd_reflog_expire_cb
r_struct
id|cmd_reflog_expire_cb
(brace
DECL|member|revs
r_struct
id|rev_info
id|revs
suffix:semicolon
DECL|member|dry_run
r_int
id|dry_run
suffix:semicolon
DECL|member|stalefix
r_int
id|stalefix
suffix:semicolon
DECL|member|rewrite
r_int
id|rewrite
suffix:semicolon
DECL|member|updateref
r_int
id|updateref
suffix:semicolon
DECL|member|verbose
r_int
id|verbose
suffix:semicolon
DECL|member|expire_total
r_int
r_int
id|expire_total
suffix:semicolon
DECL|member|expire_unreachable
r_int
r_int
id|expire_unreachable
suffix:semicolon
DECL|member|recno
r_int
id|recno
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|expire_reflog_cb
r_struct
id|expire_reflog_cb
(brace
DECL|member|newlog
id|FILE
op_star
id|newlog
suffix:semicolon
DECL|member|ref
r_const
r_char
op_star
id|ref
suffix:semicolon
DECL|member|ref_commit
r_struct
id|commit
op_star
id|ref_commit
suffix:semicolon
DECL|member|cmd
r_struct
id|cmd_reflog_expire_cb
op_star
id|cmd
suffix:semicolon
DECL|member|last_kept_sha1
r_int
r_char
id|last_kept_sha1
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|collected_reflog
r_struct
id|collected_reflog
(brace
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|reflog
r_char
id|reflog
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|collect_reflog_cb
r_struct
id|collect_reflog_cb
(brace
DECL|member|e
r_struct
id|collected_reflog
op_star
op_star
id|e
suffix:semicolon
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|nr
r_int
id|nr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INCOMPLETE
mdefine_line|#define INCOMPLETE&t;(1u&lt;&lt;10)
DECL|macro|STUDYING
mdefine_line|#define STUDYING&t;(1u&lt;&lt;11)
DECL|function|tree_is_complete
r_static
r_int
id|tree_is_complete
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
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
r_int
id|complete
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
id|tree
op_assign
id|lookup_tree
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tree-&gt;object.flags
op_amp
id|SEEN
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tree-&gt;object.flags
op_amp
id|INCOMPLETE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree-&gt;buffer
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|data
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
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
id|data
)paren
(brace
id|tree-&gt;object.flags
op_or_assign
id|INCOMPLETE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tree-&gt;buffer
op_assign
id|data
suffix:semicolon
id|tree-&gt;size
op_assign
id|size
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
id|complete
op_assign
l_int|1
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
op_logical_neg
id|has_sha1_file
c_func
(paren
id|entry.sha1
)paren
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
op_logical_and
op_logical_neg
id|tree_is_complete
c_func
(paren
id|entry.sha1
)paren
)paren
)paren
(brace
id|tree-&gt;object.flags
op_or_assign
id|INCOMPLETE
suffix:semicolon
id|complete
op_assign
l_int|0
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|complete
)paren
id|tree-&gt;object.flags
op_or_assign
id|SEEN
suffix:semicolon
r_return
id|complete
suffix:semicolon
)brace
DECL|function|commit_is_complete
r_static
r_int
id|commit_is_complete
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|object_array
id|study
suffix:semicolon
r_struct
id|object_array
id|found
suffix:semicolon
r_int
id|is_incomplete
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* early return */
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|SEEN
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|INCOMPLETE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Find all commits that are reachable and are not marked as&n;&t; * SEEN.  Then make sure the trees and blobs contained are&n;&t; * complete.  After that, mark these commits also as SEEN.&n;&t; * If some of the objects that are needed to complete this&n;&t; * commit are missing, mark this commit as INCOMPLETE.&n;&t; */
id|memset
c_func
(paren
op_amp
id|study
comma
l_int|0
comma
r_sizeof
(paren
id|study
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|found
comma
l_int|0
comma
r_sizeof
(paren
id|found
)paren
)paren
suffix:semicolon
id|add_object_array
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_int|NULL
comma
op_amp
id|study
)paren
suffix:semicolon
id|add_object_array
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_int|NULL
comma
op_amp
id|found
)paren
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|STUDYING
suffix:semicolon
r_while
c_loop
(paren
id|study.nr
)paren
(brace
r_struct
id|commit
op_star
id|c
suffix:semicolon
r_struct
id|commit_list
op_star
id|parent
suffix:semicolon
id|c
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|study.objects
(braket
op_decrement
id|study.nr
)braket
dot
id|item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;object.parsed
op_logical_and
op_logical_neg
id|parse_object
c_func
(paren
id|c-&gt;object.sha1
)paren
)paren
id|c-&gt;object.flags
op_or_assign
id|INCOMPLETE
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;object.flags
op_amp
id|INCOMPLETE
)paren
(brace
id|is_incomplete
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c-&gt;object.flags
op_amp
id|SEEN
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|parent
op_assign
id|c-&gt;parents
suffix:semicolon
id|parent
suffix:semicolon
id|parent
op_assign
id|parent-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|p
op_assign
id|parent-&gt;item
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;object.flags
op_amp
id|STUDYING
)paren
r_continue
suffix:semicolon
id|p-&gt;object.flags
op_or_assign
id|STUDYING
suffix:semicolon
id|add_object_array
c_func
(paren
op_amp
id|p-&gt;object
comma
l_int|NULL
comma
op_amp
id|study
)paren
suffix:semicolon
id|add_object_array
c_func
(paren
op_amp
id|p-&gt;object
comma
l_int|NULL
comma
op_amp
id|found
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_incomplete
)paren
(brace
multiline_comment|/*&n;&t;&t; * make sure all commits in &quot;found&quot; array have all the&n;&t;&t; * necessary objects.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|found.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|commit
op_star
id|c
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|found.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree_is_complete
c_func
(paren
id|c-&gt;tree-&gt;object.sha1
)paren
)paren
(brace
id|is_incomplete
op_assign
l_int|1
suffix:semicolon
id|c-&gt;object.flags
op_or_assign
id|INCOMPLETE
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_incomplete
)paren
(brace
multiline_comment|/* mark all found commits as complete, iow SEEN */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|found.nr
suffix:semicolon
id|i
op_increment
)paren
id|found.objects
(braket
id|i
)braket
dot
id|item-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
)brace
)brace
multiline_comment|/* clear flags from the objects we traversed */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|found.nr
suffix:semicolon
id|i
op_increment
)paren
id|found.objects
(braket
id|i
)braket
dot
id|item-&gt;flags
op_and_assign
op_complement
id|STUDYING
suffix:semicolon
r_if
c_cond
(paren
id|is_incomplete
)paren
id|commit-&gt;object.flags
op_or_assign
id|INCOMPLETE
suffix:semicolon
r_else
(brace
multiline_comment|/*&n;&t;&t; * If we come here, we have (1) traversed the ancestry chain&n;&t;&t; * from the &quot;commit&quot; until we reach SEEN commits (which are&n;&t;&t; * known to be complete), and (2) made sure that the commits&n;&t;&t; * encountered during the above traversal refer to trees that&n;&t;&t; * are complete.  Which means that we know *all* the commits&n;&t;&t; * we have seen during this process are complete.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|found.nr
suffix:semicolon
id|i
op_increment
)paren
id|found.objects
(braket
id|i
)braket
dot
id|item-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
)brace
multiline_comment|/* free object arrays */
id|free
c_func
(paren
id|study.objects
)paren
suffix:semicolon
id|free
c_func
(paren
id|found.objects
)paren
suffix:semicolon
r_return
op_logical_neg
id|is_incomplete
suffix:semicolon
)brace
DECL|function|keep_entry
r_static
r_int
id|keep_entry
c_func
(paren
r_struct
id|commit
op_star
op_star
id|it
comma
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
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
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
op_logical_neg
id|commit
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure everything in this commit exists.&n;&t; *&n;&t; * We have walked all the objects reachable from the refs&n;&t; * and cache earlier.  The commits reachable by this commit&n;&t; * must meet SEEN commits -- and then we should mark them as&n;&t; * SEEN as well.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|commit_is_complete
c_func
(paren
id|commit
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|it
op_assign
id|commit
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|expire_reflog_ent
r_static
r_int
id|expire_reflog_ent
c_func
(paren
r_int
r_char
op_star
id|osha1
comma
r_int
r_char
op_star
id|nsha1
comma
r_const
r_char
op_star
id|email
comma
r_int
r_int
id|timestamp
comma
r_int
id|tz
comma
r_const
r_char
op_star
id|message
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|expire_reflog_cb
op_star
id|cb
op_assign
id|cb_data
suffix:semicolon
r_struct
id|commit
op_star
id|old
comma
op_star
r_new
suffix:semicolon
r_if
c_cond
(paren
id|timestamp
OL
id|cb-&gt;cmd-&gt;expire_total
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;cmd-&gt;rewrite
)paren
id|osha1
op_assign
id|cb-&gt;last_kept_sha1
suffix:semicolon
id|old
op_assign
r_new
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;cmd-&gt;stalefix
op_logical_and
(paren
op_logical_neg
id|keep_entry
c_func
(paren
op_amp
id|old
comma
id|osha1
)paren
op_logical_or
op_logical_neg
id|keep_entry
c_func
(paren
op_amp
r_new
comma
id|nsha1
)paren
)paren
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
id|timestamp
OL
id|cb-&gt;cmd-&gt;expire_unreachable
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cb-&gt;ref_commit
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|osha1
)paren
)paren
id|old
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|osha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|nsha1
)paren
)paren
r_new
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|nsha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old
op_logical_and
op_logical_neg
id|in_merge_bases
c_func
(paren
id|old
comma
op_amp
id|cb-&gt;ref_commit
comma
l_int|1
)paren
)paren
op_logical_or
(paren
r_new
op_logical_and
op_logical_neg
id|in_merge_bases
c_func
(paren
r_new
comma
op_amp
id|cb-&gt;ref_commit
comma
l_int|1
)paren
)paren
)paren
r_goto
id|prune
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cb-&gt;cmd-&gt;recno
op_logical_and
op_decrement
(paren
id|cb-&gt;cmd-&gt;recno
)paren
op_eq
l_int|0
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;newlog
)paren
(brace
r_char
id|sign
op_assign
(paren
id|tz
OL
l_int|0
)paren
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;+&squot;
suffix:semicolon
r_int
id|zone
op_assign
(paren
id|tz
OL
l_int|0
)paren
ques
c_cond
(paren
id|tz
)paren
suffix:colon
id|tz
suffix:semicolon
id|fprintf
c_func
(paren
id|cb-&gt;newlog
comma
l_string|&quot;%s %s %s %lu %c%04d&bslash;t%s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|osha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|nsha1
)paren
comma
id|email
comma
id|timestamp
comma
id|sign
comma
id|zone
comma
id|message
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|cb-&gt;last_kept_sha1
comma
id|nsha1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cb-&gt;cmd-&gt;verbose
)paren
id|printf
c_func
(paren
l_string|&quot;keep %s&quot;
comma
id|message
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|prune
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|cb-&gt;newlog
op_logical_or
id|cb-&gt;cmd-&gt;verbose
)paren
id|printf
c_func
(paren
l_string|&quot;%sprune %s&quot;
comma
id|cb-&gt;newlog
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;would &quot;
comma
id|message
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|expire_reflog
r_static
r_int
id|expire_reflog
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|unused
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|cmd_reflog_expire_cb
op_star
id|cmd
op_assign
id|cb_data
suffix:semicolon
r_struct
id|expire_reflog_cb
id|cb
suffix:semicolon
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
r_char
op_star
id|log_file
comma
op_star
id|newlog_path
op_assign
l_int|NULL
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we take the lock for the ref itself to prevent it from&n;&t; * getting updated.&n;&t; */
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot lock ref &squot;%s&squot;&quot;
comma
id|ref
)paren
suffix:semicolon
id|log_file
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;logs/%s&quot;
comma
id|ref
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|log_file
)paren
)paren
r_goto
id|finish
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmd-&gt;dry_run
)paren
(brace
id|newlog_path
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;logs/%s.lock&quot;
comma
id|ref
)paren
)paren
suffix:semicolon
id|cb.newlog
op_assign
id|fopen
c_func
(paren
id|newlog_path
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
)brace
id|cb.ref_commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
id|cb.ref
op_assign
id|ref
suffix:semicolon
id|cb.cmd
op_assign
id|cmd
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|ref
comma
id|expire_reflog_ent
comma
op_amp
id|cb
)paren
suffix:semicolon
id|finish
suffix:colon
r_if
c_cond
(paren
id|cb.newlog
)paren
(brace
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|cb.newlog
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;%s: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
comma
id|newlog_path
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|newlog_path
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;updateref
op_logical_and
(paren
id|write_in_full
c_func
(paren
id|lock-&gt;lock_fd
comma
id|sha1_to_hex
c_func
(paren
id|cb.last_kept_sha1
)paren
comma
l_int|40
)paren
op_ne
l_int|40
op_logical_or
id|write_in_full
c_func
(paren
id|lock-&gt;lock_fd
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
op_ne
l_int|1
op_logical_or
id|close_ref
c_func
(paren
id|lock
)paren
OL
l_int|0
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t write %s&quot;
comma
id|lock-&gt;lk-&gt;filename
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|newlog_path
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rename
c_func
(paren
id|newlog_path
comma
id|log_file
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;cannot rename %s to %s&quot;
comma
id|newlog_path
comma
id|log_file
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|newlog_path
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;updateref
op_logical_and
id|commit_ref
c_func
(paren
id|lock
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t set %s&quot;
comma
id|lock-&gt;ref_name
)paren
suffix:semicolon
)brace
r_else
(brace
id|adjust_shared_perm
c_func
(paren
id|log_file
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|newlog_path
)paren
suffix:semicolon
id|free
c_func
(paren
id|log_file
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|collect_reflog
r_static
r_int
id|collect_reflog
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|unused
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|collected_reflog
op_star
id|e
suffix:semicolon
r_struct
id|collect_reflog_cb
op_star
id|cb
op_assign
id|cb_data
suffix:semicolon
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|ref
)paren
suffix:semicolon
id|e
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|e
)paren
op_plus
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|e-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|e-&gt;reflog
comma
id|ref
comma
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|cb-&gt;e
comma
id|cb-&gt;nr
op_plus
l_int|1
comma
id|cb-&gt;alloc
)paren
suffix:semicolon
id|cb-&gt;e
(braket
id|cb-&gt;nr
op_increment
)braket
op_assign
id|e
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|reflog_expire_cfg
r_static
r_struct
id|reflog_expire_cfg
(brace
DECL|member|next
r_struct
id|reflog_expire_cfg
op_star
id|next
suffix:semicolon
DECL|member|expire_total
r_int
r_int
id|expire_total
suffix:semicolon
DECL|member|expire_unreachable
r_int
r_int
id|expire_unreachable
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|pattern
r_char
id|pattern
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
DECL|variable|reflog_expire_cfg
DECL|variable|reflog_expire_cfg_tail
)brace
op_star
id|reflog_expire_cfg
comma
op_star
op_star
id|reflog_expire_cfg_tail
suffix:semicolon
DECL|function|find_cfg_ent
r_static
r_struct
id|reflog_expire_cfg
op_star
id|find_cfg_ent
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_int
id|len
)paren
(brace
r_struct
id|reflog_expire_cfg
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reflog_expire_cfg_tail
)paren
id|reflog_expire_cfg_tail
op_assign
op_amp
id|reflog_expire_cfg
suffix:semicolon
r_for
c_loop
(paren
id|ent
op_assign
id|reflog_expire_cfg
suffix:semicolon
id|ent
suffix:semicolon
id|ent
op_assign
id|ent-&gt;next
)paren
r_if
c_cond
(paren
id|ent-&gt;len
op_eq
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ent-&gt;pattern
comma
id|pattern
comma
id|len
)paren
)paren
r_return
id|ent
suffix:semicolon
id|ent
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
(paren
r_sizeof
(paren
op_star
id|ent
)paren
op_plus
id|len
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;pattern
comma
id|pattern
comma
id|len
)paren
suffix:semicolon
id|ent-&gt;len
op_assign
id|len
suffix:semicolon
op_star
id|reflog_expire_cfg_tail
op_assign
id|ent
suffix:semicolon
id|reflog_expire_cfg_tail
op_assign
op_amp
(paren
id|ent-&gt;next
)paren
suffix:semicolon
r_return
id|ent
suffix:semicolon
)brace
DECL|function|parse_expire_cfg_value
r_static
r_int
id|parse_expire_cfg_value
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_int
r_int
op_star
id|expire
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;never&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;false&quot;
)paren
)paren
(brace
op_star
id|expire
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|expire
op_assign
id|approxidate
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* expiry timer slot */
DECL|macro|EXPIRE_TOTAL
mdefine_line|#define EXPIRE_TOTAL   01
DECL|macro|EXPIRE_UNREACH
mdefine_line|#define EXPIRE_UNREACH 02
DECL|function|reflog_expire_config
r_static
r_int
id|reflog_expire_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_const
r_char
op_star
id|lastdot
op_assign
id|strrchr
c_func
(paren
id|var
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_int
r_int
id|expire
suffix:semicolon
r_int
id|slot
suffix:semicolon
r_struct
id|reflog_expire_cfg
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lastdot
op_logical_or
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.&quot;
)paren
)paren
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|lastdot
comma
l_string|&quot;.reflogexpire&quot;
)paren
)paren
(brace
id|slot
op_assign
id|EXPIRE_TOTAL
suffix:semicolon
r_if
c_cond
(paren
id|parse_expire_cfg_value
c_func
(paren
id|var
comma
id|value
comma
op_amp
id|expire
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|lastdot
comma
l_string|&quot;.reflogexpireunreachable&quot;
)paren
)paren
(brace
id|slot
op_assign
id|EXPIRE_UNREACH
suffix:semicolon
r_if
c_cond
(paren
id|parse_expire_cfg_value
c_func
(paren
id|var
comma
id|value
comma
op_amp
id|expire
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lastdot
op_eq
id|var
op_plus
l_int|2
)paren
(brace
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
id|EXPIRE_TOTAL
suffix:colon
id|default_reflog_expire
op_assign
id|expire
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXPIRE_UNREACH
suffix:colon
id|default_reflog_expire_unreachable
op_assign
id|expire
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|ent
op_assign
id|find_cfg_ent
c_func
(paren
id|var
op_plus
l_int|3
comma
id|lastdot
(paren
id|var
op_plus
l_int|3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|slot
)paren
(brace
r_case
id|EXPIRE_TOTAL
suffix:colon
id|ent-&gt;expire_total
op_assign
id|expire
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXPIRE_UNREACH
suffix:colon
id|ent-&gt;expire_unreachable
op_assign
id|expire
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_reflog_expiry_param
r_static
r_void
id|set_reflog_expiry_param
c_func
(paren
r_struct
id|cmd_reflog_expire_cb
op_star
id|cb
comma
r_int
id|slot
comma
r_const
r_char
op_star
id|ref
)paren
(brace
r_struct
id|reflog_expire_cfg
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
(paren
id|EXPIRE_TOTAL
op_or
id|EXPIRE_UNREACH
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* both given explicitly -- nothing to tweak */
r_for
c_loop
(paren
id|ent
op_assign
id|reflog_expire_cfg
suffix:semicolon
id|ent
suffix:semicolon
id|ent
op_assign
id|ent-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|ent-&gt;pattern
comma
id|ref
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot
op_amp
id|EXPIRE_TOTAL
)paren
)paren
id|cb-&gt;expire_total
op_assign
id|ent-&gt;expire_total
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot
op_amp
id|EXPIRE_UNREACH
)paren
)paren
id|cb-&gt;expire_unreachable
op_assign
id|ent-&gt;expire_unreachable
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* Nothing matched -- use the default value */
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot
op_amp
id|EXPIRE_TOTAL
)paren
)paren
id|cb-&gt;expire_total
op_assign
id|default_reflog_expire
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot
op_amp
id|EXPIRE_UNREACH
)paren
)paren
id|cb-&gt;expire_unreachable
op_assign
id|default_reflog_expire_unreachable
suffix:semicolon
)brace
DECL|function|cmd_reflog_expire
r_static
r_int
id|cmd_reflog_expire
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
id|cmd_reflog_expire_cb
id|cb
suffix:semicolon
r_int
r_int
id|now
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_int
id|i
comma
id|status
comma
id|do_all
suffix:semicolon
r_int
id|explicit_expiry
op_assign
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|reflog_expire_config
comma
l_int|NULL
)paren
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
id|do_all
op_assign
id|status
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|default_reflog_expire_unreachable
)paren
id|default_reflog_expire_unreachable
op_assign
id|now
l_int|30
op_star
l_int|24
op_star
l_int|3600
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|default_reflog_expire
)paren
id|default_reflog_expire
op_assign
id|now
l_int|90
op_star
l_int|24
op_star
l_int|3600
suffix:semicolon
id|cb.expire_total
op_assign
id|default_reflog_expire
suffix:semicolon
id|cb.expire_unreachable
op_assign
id|default_reflog_expire_unreachable
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
l_string|&quot;--dry-run&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
id|cb.dry_run
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--expire=&quot;
)paren
)paren
(brace
id|cb.expire_total
op_assign
id|approxidate
c_func
(paren
id|arg
op_plus
l_int|9
)paren
suffix:semicolon
id|explicit_expiry
op_or_assign
id|EXPIRE_TOTAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--expire-unreachable=&quot;
)paren
)paren
(brace
id|cb.expire_unreachable
op_assign
id|approxidate
c_func
(paren
id|arg
op_plus
l_int|21
)paren
suffix:semicolon
id|explicit_expiry
op_or_assign
id|EXPIRE_UNREACH
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stale-fix&quot;
)paren
)paren
id|cb.stalefix
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--rewrite&quot;
)paren
)paren
id|cb.rewrite
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--updateref&quot;
)paren
)paren
id|cb.updateref
op_assign
l_int|1
suffix:semicolon
r_else
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
id|do_all
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--verbose&quot;
)paren
)paren
id|cb.verbose
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|reflog_expire_usage
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We can trust the commits and objects reachable from refs&n;&t; * even in older repository.  We cannot trust what&squot;s reachable&n;&t; * from reflog if the repository was pruned with older git.&n;&t; */
r_if
c_cond
(paren
id|cb.stalefix
)paren
(brace
id|init_revisions
c_func
(paren
op_amp
id|cb.revs
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cb.verbose
)paren
id|printf
c_func
(paren
l_string|&quot;Marking reachable objects...&quot;
)paren
suffix:semicolon
id|mark_reachable_objects
c_func
(paren
op_amp
id|cb.revs
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cb.verbose
)paren
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_all
)paren
(brace
r_struct
id|collect_reflog_cb
id|collected
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|collected
comma
l_int|0
comma
r_sizeof
(paren
id|collected
)paren
)paren
suffix:semicolon
id|for_each_reflog
c_func
(paren
id|collect_reflog
comma
op_amp
id|collected
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
id|collected.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|collected_reflog
op_star
id|e
op_assign
id|collected.e
(braket
id|i
)braket
suffix:semicolon
id|set_reflog_expiry_param
c_func
(paren
op_amp
id|cb
comma
id|explicit_expiry
comma
id|e-&gt;reflog
)paren
suffix:semicolon
id|status
op_or_assign
id|expire_reflog
c_func
(paren
id|e-&gt;reflog
comma
id|e-&gt;sha1
comma
l_int|0
comma
op_amp
id|cb
)paren
suffix:semicolon
id|free
c_func
(paren
id|e
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|collected.e
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|argc
)paren
(brace
r_const
r_char
op_star
id|ref
op_assign
id|argv
(braket
id|i
op_increment
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;%s points nowhere!&quot;
comma
id|ref
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|set_reflog_expiry_param
c_func
(paren
op_amp
id|cb
comma
id|explicit_expiry
comma
id|ref
)paren
suffix:semicolon
id|status
op_or_assign
id|expire_reflog
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|0
comma
op_amp
id|cb
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|count_reflog_ent
r_static
r_int
id|count_reflog_ent
c_func
(paren
r_int
r_char
op_star
id|osha1
comma
r_int
r_char
op_star
id|nsha1
comma
r_const
r_char
op_star
id|email
comma
r_int
r_int
id|timestamp
comma
r_int
id|tz
comma
r_const
r_char
op_star
id|message
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|cmd_reflog_expire_cb
op_star
id|cb
op_assign
id|cb_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cb-&gt;expire_total
op_logical_or
id|timestamp
OL
id|cb-&gt;expire_total
)paren
id|cb-&gt;recno
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_reflog_delete
r_static
r_int
id|cmd_reflog_delete
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
id|cmd_reflog_expire_cb
id|cb
suffix:semicolon
r_int
id|i
comma
id|status
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
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
l_string|&quot;--dry-run&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
id|cb.dry_run
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--rewrite&quot;
)paren
)paren
id|cb.rewrite
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--updateref&quot;
)paren
)paren
id|cb.updateref
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--verbose&quot;
)paren
)paren
id|cb.verbose
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|reflog_delete_usage
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
id|i
OL
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Nothing to delete?&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
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
id|spec
op_assign
id|strstr
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;@{&quot;
)paren
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
id|ep
comma
op_star
id|ref
suffix:semicolon
r_int
id|recno
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spec
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;Not a reflog: %s&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dwim_ref
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|spec
id|argv
(braket
id|i
)braket
comma
id|sha1
comma
op_amp
id|ref
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;%s points nowhere!&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|recno
op_assign
id|strtoul
c_func
(paren
id|spec
op_plus
l_int|2
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ep
op_eq
l_char|&squot;}&squot;
)paren
(brace
id|cb.recno
op_assign
id|recno
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|ref
comma
id|count_reflog_ent
comma
op_amp
id|cb
)paren
suffix:semicolon
)brace
r_else
(brace
id|cb.expire_total
op_assign
id|approxidate
c_func
(paren
id|spec
op_plus
l_int|2
)paren
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|ref
comma
id|count_reflog_ent
comma
op_amp
id|cb
)paren
suffix:semicolon
id|cb.expire_total
op_assign
l_int|0
suffix:semicolon
)brace
id|status
op_or_assign
id|expire_reflog
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|0
comma
op_amp
id|cb
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * main &quot;reflog&quot;&n; */
DECL|variable|reflog_usage
r_static
r_const
r_char
id|reflog_usage
(braket
)braket
op_assign
l_string|&quot;git-reflog (expire | ...)&quot;
suffix:semicolon
DECL|function|cmd_reflog
r_int
id|cmd_reflog
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
multiline_comment|/* With no command, we default to showing it. */
r_if
c_cond
(paren
id|argc
OL
l_int|2
op_logical_or
op_star
id|argv
(braket
l_int|1
)braket
op_eq
l_char|&squot;-&squot;
)paren
r_return
id|cmd_log_reflog
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;show&quot;
)paren
)paren
r_return
id|cmd_log_reflog
c_func
(paren
id|argc
l_int|1
comma
id|argv
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;expire&quot;
)paren
)paren
r_return
id|cmd_reflog_expire
c_func
(paren
id|argc
l_int|1
comma
id|argv
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;delete&quot;
)paren
)paren
r_return
id|cmd_reflog_delete
c_func
(paren
id|argc
l_int|1
comma
id|argv
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
multiline_comment|/* Not a recognized reflog command..*/
id|usage
c_func
(paren
id|reflog_usage
)paren
suffix:semicolon
)brace
eof
