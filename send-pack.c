macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
DECL|variable|send_pack_usage
r_static
r_const
r_char
id|send_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-send-pack [--all] [--exec=git-receive-pack] &lt;remote&gt; [&lt;head&gt;...]&bslash;n&quot;
l_string|&quot;  --all and explicit &lt;head&gt; specification are mutually exclusive.&quot;
suffix:semicolon
DECL|variable|exec
r_static
r_const
r_char
op_star
id|exec
op_assign
l_string|&quot;git-receive-pack&quot;
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
DECL|variable|send_all
r_static
r_int
id|send_all
op_assign
l_int|0
suffix:semicolon
DECL|variable|force_update
r_static
r_int
id|force_update
op_assign
l_int|0
suffix:semicolon
DECL|variable|use_thin_pack
r_static
r_int
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
DECL|function|is_zero_sha1
r_static
r_int
id|is_zero_sha1
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|sha1
op_increment
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|exec_pack_objects
r_static
r_void
id|exec_pack_objects
c_func
(paren
r_void
)paren
(brace
r_static
r_char
op_star
id|args
(braket
)braket
op_assign
(brace
l_string|&quot;pack-objects&quot;
comma
l_string|&quot;--stdout&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|execv_git_cmd
c_func
(paren
id|args
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-pack-objects exec failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|exec_rev_list
r_static
r_void
id|exec_rev_list
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
r_static
r_char
op_star
id|args
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|j
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;rev-list&quot;
suffix:semicolon
multiline_comment|/* 0 */
r_if
c_cond
(paren
id|use_thin_pack
)paren
multiline_comment|/* 1 */
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--objects-edge&quot;
suffix:semicolon
r_else
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--objects&quot;
suffix:semicolon
multiline_comment|/* First send the ones we care about most */
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
r_if
c_cond
(paren
l_int|900
OL
id|i
)paren
id|die
c_func
(paren
l_string|&quot;git-rev-list environment overflow&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_zero_sha1
c_func
(paren
id|ref-&gt;new_sha1
)paren
)paren
(brace
r_char
op_star
id|buf
op_assign
id|malloc
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|buf
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
l_int|50
comma
l_string|&quot;%s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;new_sha1
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|50
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_zero_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
op_logical_and
id|has_sha1_file
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
(brace
id|args
(braket
id|i
op_increment
)braket
op_assign
id|buf
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
l_int|50
comma
l_string|&quot;^%s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Then a handful of the remainder&n;&t; * NEEDSWORK: we would be better off if used the newer ones first.&n;&t; */
r_for
c_loop
(paren
id|ref
op_assign
id|refs
comma
id|j
op_assign
id|i
op_plus
l_int|16
suffix:semicolon
id|i
OL
l_int|900
op_logical_and
id|i
OL
id|j
op_logical_and
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|is_zero_sha1
c_func
(paren
id|ref-&gt;new_sha1
)paren
op_logical_and
op_logical_neg
id|is_zero_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
op_logical_and
id|has_sha1_file
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
(brace
r_char
op_star
id|buf
op_assign
id|malloc
c_func
(paren
l_int|42
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|buf
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
l_int|42
comma
l_string|&quot;^%s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
)brace
)brace
id|args
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|execv_git_cmd
c_func
(paren
id|args
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-rev-list exec failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|rev_list
r_static
r_void
id|rev_list
c_func
(paren
r_int
id|fd
comma
r_struct
id|ref
op_star
id|refs
)paren
(brace
r_int
id|pipe_fd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pack_objects_pid
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pipe_fd
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;rev-list setup: pipe failed&quot;
)paren
suffix:semicolon
id|pack_objects_pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pack_objects_pid
)paren
(brace
id|dup2
c_func
(paren
id|pipe_fd
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|fd
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|exec_pack_objects
c_func
(paren
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;pack-objects setup failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pack_objects_pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;pack-objects fork failed&quot;
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|pipe_fd
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|exec_rev_list
c_func
(paren
id|refs
)paren
suffix:semicolon
)brace
DECL|function|pack_objects
r_static
r_int
id|pack_objects
c_func
(paren
r_int
id|fd
comma
r_struct
id|ref
op_star
id|refs
)paren
(brace
id|pid_t
id|rev_list_pid
suffix:semicolon
id|rev_list_pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev_list_pid
)paren
(brace
id|rev_list
c_func
(paren
id|fd
comma
id|refs
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;rev-list setup failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rev_list_pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;rev-list fork failed&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t wait for the rev-list pipeline in the parent:&n;&t; * we end up waiting for the other end instead&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unmark_and_free
r_static
r_void
id|unmark_and_free
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
r_int
id|mark
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|temp
op_assign
id|list
suffix:semicolon
id|temp-&gt;item-&gt;object.flags
op_and_assign
op_complement
id|mark
suffix:semicolon
id|list
op_assign
id|temp-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|temp
)paren
suffix:semicolon
)brace
)brace
DECL|function|ref_newer
r_static
r_int
id|ref_newer
c_func
(paren
r_const
r_int
r_char
op_star
id|new_sha1
comma
r_const
r_int
r_char
op_star
id|old_sha1
)paren
(brace
r_struct
id|object
op_star
id|o
suffix:semicolon
r_struct
id|commit
op_star
id|old
comma
op_star
r_new
suffix:semicolon
r_struct
id|commit_list
op_star
id|list
comma
op_star
id|used
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Both new and old must be commit-ish and new is descendant of&n;&t; * old.  Otherwise we require --force.&n;&t; */
id|o
op_assign
id|deref_tag
c_func
(paren
id|parse_object
c_func
(paren
id|old_sha1
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
id|commit_type
)paren
r_return
l_int|0
suffix:semicolon
id|old
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|o
suffix:semicolon
id|o
op_assign
id|deref_tag
c_func
(paren
id|parse_object
c_func
(paren
id|new_sha1
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
id|commit_type
)paren
r_return
l_int|0
suffix:semicolon
r_new
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
id|parse_commit
c_func
(paren
r_new
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|used
op_assign
id|list
op_assign
l_int|NULL
suffix:semicolon
id|commit_list_insert
c_func
(paren
r_new
comma
op_amp
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_new
op_assign
id|pop_most_recent_commit
c_func
(paren
op_amp
id|list
comma
l_int|1
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
r_new
comma
op_amp
id|used
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
id|old
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|unmark_and_free
c_func
(paren
id|list
comma
l_int|1
)paren
suffix:semicolon
id|unmark_and_free
c_func
(paren
id|used
comma
l_int|1
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|variable|local_refs
DECL|variable|local_tail
r_static
r_struct
id|ref
op_star
id|local_refs
comma
op_star
op_star
id|local_tail
suffix:semicolon
DECL|variable|remote_refs
DECL|variable|remote_tail
r_static
r_struct
id|ref
op_star
id|remote_refs
comma
op_star
op_star
id|remote_tail
suffix:semicolon
DECL|function|one_local_ref
r_static
r_int
id|one_local_ref
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|refname
)paren
op_plus
l_int|1
suffix:semicolon
id|ref
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ref
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;name
comma
id|refname
comma
id|len
)paren
suffix:semicolon
op_star
id|local_tail
op_assign
id|ref
suffix:semicolon
id|local_tail
op_assign
op_amp
id|ref-&gt;next
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_local_heads
r_static
r_void
id|get_local_heads
c_func
(paren
r_void
)paren
(brace
id|local_tail
op_assign
op_amp
id|local_refs
suffix:semicolon
id|for_each_ref
c_func
(paren
id|one_local_ref
)paren
suffix:semicolon
)brace
DECL|function|receive_status
r_static
r_int
id|receive_status
c_func
(paren
r_int
id|in
)paren
(brace
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
id|packet_read_line
c_func
(paren
id|in
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|10
op_logical_or
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;unpack &quot;
comma
l_int|7
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;did not receive status back&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;unpack ok&bslash;n&quot;
comma
l_int|10
)paren
)paren
(brace
id|fputs
c_func
(paren
id|line
comma
id|stderr
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|len
op_assign
id|packet_read_line
c_func
(paren
id|in
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
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
id|len
OL
l_int|3
op_logical_or
(paren
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;ok&quot;
comma
l_int|2
)paren
op_logical_and
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;ng&quot;
comma
l_int|2
)paren
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;protocol error: %s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;ok&quot;
comma
l_int|2
)paren
)paren
r_continue
suffix:semicolon
id|fputs
c_func
(paren
id|line
comma
id|stderr
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|send_pack
r_static
r_int
id|send_pack
c_func
(paren
r_int
id|in
comma
r_int
id|out
comma
r_int
id|nr_refspec
comma
r_char
op_star
op_star
id|refspec
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|new_refs
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|ask_for_status_report
op_assign
l_int|0
suffix:semicolon
r_int
id|expect_status_report
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No funny business with the matcher */
id|remote_tail
op_assign
id|get_remote_heads
c_func
(paren
id|in
comma
op_amp
id|remote_refs
comma
l_int|0
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
id|get_local_heads
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Does the other end support the reporting? */
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;report-status&quot;
)paren
)paren
id|ask_for_status_report
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* match them up */
r_if
c_cond
(paren
op_logical_neg
id|remote_tail
)paren
id|remote_tail
op_assign
op_amp
id|remote_refs
suffix:semicolon
r_if
c_cond
(paren
id|match_refs
c_func
(paren
id|local_refs
comma
id|remote_refs
comma
op_amp
id|remote_tail
comma
id|nr_refspec
comma
id|refspec
comma
id|send_all
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote_refs
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No refs in common and none specified; doing nothing.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Finally, tell the other end!&n;&t; */
id|new_refs
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|remote_refs
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_char
id|old_hex
(braket
l_int|60
)braket
comma
op_star
id|new_hex
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref-&gt;peer_ref
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|ref-&gt;old_sha1
comma
id|ref-&gt;peer_ref-&gt;new_sha1
comma
l_int|20
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
l_string|&quot;&squot;%s&squot;: up-to-date&bslash;n&quot;
comma
id|ref-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* This part determines what can overwrite what.&n;&t;&t; * The rules are:&n;&t;&t; *&n;&t;&t; * (0) you can always use --force or +A:B notation to&n;&t;&t; *     selectively force individual ref pairs.&n;&t;&t; *&n;&t;&t; * (1) if the old thing does not exist, it is OK.&n;&t;&t; *&n;&t;&t; * (2) if you do not have the old thing, you are not allowed&n;&t;&t; *     to overwrite it; you would not know what you are losing&n;&t;&t; *     otherwise.&n;&t;&t; *&n;&t;&t; * (3) if both new and old are commit-ish, and new is a&n;&t;&t; *     descendant of old, it is OK.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|force_update
op_logical_and
op_logical_neg
id|is_zero_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
op_logical_and
op_logical_neg
id|ref-&gt;force
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|ref-&gt;old_sha1
)paren
op_logical_or
op_logical_neg
id|ref_newer
c_func
(paren
id|ref-&gt;peer_ref-&gt;new_sha1
comma
id|ref-&gt;old_sha1
)paren
)paren
(brace
multiline_comment|/* We do not have the remote ref, or&n;&t;&t;&t;&t; * we know that the remote ref is not&n;&t;&t;&t;&t; * an ancestor of what we are trying to&n;&t;&t;&t;&t; * push.  Either way this can be losing&n;&t;&t;&t;&t; * commits at the remote end and likely&n;&t;&t;&t;&t; * we were not up to date to begin with.&n;&t;&t;&t;&t; */
id|error
c_func
(paren
l_string|&quot;remote &squot;%s&squot; is not a strict &quot;
l_string|&quot;subset of local ref &squot;%s&squot;. &quot;
l_string|&quot;maybe you are not up-to-date and &quot;
l_string|&quot;need to pull first?&quot;
comma
id|ref-&gt;name
comma
id|ref-&gt;peer_ref-&gt;name
)paren
suffix:semicolon
id|ret
op_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|memcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|ref-&gt;peer_ref-&gt;new_sha1
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_zero_sha1
c_func
(paren
id|ref-&gt;new_sha1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot happen anymore&quot;
)paren
suffix:semicolon
id|ret
op_assign
l_int|3
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|new_refs
op_increment
suffix:semicolon
id|strcpy
c_func
(paren
id|old_hex
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
id|new_hex
op_assign
id|sha1_to_hex
c_func
(paren
id|ref-&gt;new_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ask_for_status_report
)paren
(brace
id|packet_write
c_func
(paren
id|out
comma
l_string|&quot;%s %s %s%c%s&quot;
comma
id|old_hex
comma
id|new_hex
comma
id|ref-&gt;name
comma
l_int|0
comma
l_string|&quot;report-status&quot;
)paren
suffix:semicolon
id|ask_for_status_report
op_assign
l_int|0
suffix:semicolon
id|expect_status_report
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|packet_write
c_func
(paren
id|out
comma
l_string|&quot;%s %s %s&quot;
comma
id|old_hex
comma
id|new_hex
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;updating &squot;%s&squot;&quot;
comma
id|ref-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ref-&gt;name
comma
id|ref-&gt;peer_ref-&gt;name
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; using &squot;%s&squot;&quot;
comma
id|ref-&gt;peer_ref-&gt;name
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;n  from %s&bslash;n  to   %s&bslash;n&quot;
comma
id|old_hex
comma
id|new_hex
)paren
suffix:semicolon
)brace
id|packet_flush
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_refs
)paren
id|pack_objects
c_func
(paren
id|out
comma
id|remote_refs
)paren
suffix:semicolon
id|close
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expect_status_report
)paren
(brace
r_if
c_cond
(paren
id|receive_status
c_func
(paren
id|in
)paren
)paren
id|ret
op_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|new_refs
op_logical_and
id|ret
op_eq
l_int|0
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Everything up-to-date&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
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
id|nr_heads
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
op_star
id|heads
op_assign
l_int|NULL
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
comma
id|ret
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|argv
op_increment
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
comma
id|argv
op_increment
)paren
(brace
r_char
op_star
id|arg
op_assign
op_star
id|argv
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
id|arg
comma
l_string|&quot;--exec=&quot;
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
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|send_all
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
l_string|&quot;--force&quot;
)paren
)paren
(brace
id|force_update
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
l_string|&quot;--verbose&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--thin&quot;
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
id|usage
c_func
(paren
id|send_pack_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
(brace
id|dest
op_assign
id|arg
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|heads
op_assign
id|argv
suffix:semicolon
id|nr_heads
op_assign
id|argc
id|i
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
id|send_pack_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|heads
op_logical_and
id|send_all
)paren
id|usage
c_func
(paren
id|send_pack_usage
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
id|send_pack
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|fd
(braket
l_int|1
)braket
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
