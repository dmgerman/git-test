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
l_string|&quot;git-reflog expire [--verbose] [--dry-run] [--stale-fix] [--expire=&lt;time&gt;] [--expire-unreachable=&lt;time&gt;] [--all] &lt;refs&gt;...&quot;
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
id|desc.buf
op_assign
id|tree-&gt;buffer
suffix:semicolon
id|desc.size
op_assign
id|tree-&gt;size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc.buf
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
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
id|type
comma
op_amp
id|desc.size
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
id|desc.buf
op_assign
id|data
suffix:semicolon
id|tree-&gt;buffer
op_assign
id|data
suffix:semicolon
)brace
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
id|cb-&gt;ref_commit
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
id|cb-&gt;ref_commit
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
id|newlog_path
op_assign
l_int|NULL
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ref
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;not a ref &squot;%s&squot;&quot;
comma
id|ref
)paren
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
multiline_comment|/* we take the lock for the ref itself to prevent it from&n;&t; * getting updated.&n;&t; */
id|lock
op_assign
id|lock_ref_sha1
c_func
(paren
id|ref
op_plus
l_int|5
comma
id|sha1
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
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|lock-&gt;log_file
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
r_if
c_cond
(paren
op_logical_neg
id|cb.ref_commit
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: ref &squot;%s&squot; does not point at a commit&bslash;n&quot;
comma
id|ref
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
r_if
c_cond
(paren
id|rename
c_func
(paren
id|newlog_path
comma
id|lock-&gt;log_file
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
id|lock-&gt;log_file
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|newlog_path
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.reflogexpire&quot;
)paren
)paren
id|default_reflog_expire
op_assign
id|approxidate
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.reflogexpireunreachable&quot;
)paren
)paren
id|default_reflog_expire_unreachable
op_assign
id|approxidate
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
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
id|git_config
c_func
(paren
id|reflog_expire_config
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
multiline_comment|/*&n;&t; * We can trust the commits and objects reachable from refs&n;&t; * even in older repository.  We cannot trust what&squot;s reachable&n;&t; * from reflog if the repository was pruned with older git.&n;&t; */
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--expire=&quot;
comma
l_int|9
)paren
)paren
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
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--expire-unreachable=&quot;
comma
l_int|21
)paren
)paren
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
id|status
op_or_assign
id|for_each_ref
c_func
(paren
id|expire_reflog
comma
op_amp
id|cb
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
id|usage
c_func
(paren
id|reflog_usage
)paren
suffix:semicolon
r_else
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
r_else
id|usage
c_func
(paren
id|reflog_usage
)paren
suffix:semicolon
)brace
eof
