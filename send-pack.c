macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;connect.h&quot;
macro_line|#include &quot;send-pack.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;version.h&quot;
DECL|function|feed_object
r_static
r_int
id|feed_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|fd
comma
r_int
id|negative
)paren
(brace
r_char
id|buf
(braket
l_int|42
)braket
suffix:semicolon
r_if
c_cond
(paren
id|negative
op_logical_and
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|negative
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|negative
)paren
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;^&squot;
suffix:semicolon
id|buf
(braket
l_int|40
op_plus
id|negative
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|write_or_whine
c_func
(paren
id|fd
comma
id|buf
comma
l_int|41
op_plus
id|negative
comma
l_string|&quot;send-pack: send refs&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make a pack stream and spit it out into file descriptor fd&n; */
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
comma
r_struct
id|extra_have_objects
op_star
id|extra
comma
r_struct
id|send_pack_args
op_star
id|args
)paren
(brace
multiline_comment|/*&n;&t; * The child becomes pack-objects --revs; we feed&n;&t; * the revision parameters to it via its stdin and&n;&t; * let its stdout go back to the other end.&n;&t; */
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;pack-objects&quot;
comma
l_string|&quot;--all-progress-implied&quot;
comma
l_string|&quot;--revs&quot;
comma
l_string|&quot;--stdout&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_struct
id|child_process
id|po
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;use_thin_pack
)paren
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--thin&quot;
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;use_ofs_delta
)paren
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--delta-base-offset&quot;
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;quiet
op_logical_or
op_logical_neg
id|args-&gt;progress
)paren
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;-q&quot;
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;progress
)paren
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--progress&quot;
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|po
comma
l_int|0
comma
r_sizeof
(paren
id|po
)paren
)paren
suffix:semicolon
id|po.argv
op_assign
id|argv
suffix:semicolon
id|po.in
op_assign
l_int|1
suffix:semicolon
id|po.out
op_assign
id|args-&gt;stateless_rpc
ques
c_cond
l_int|1
suffix:colon
id|fd
suffix:semicolon
id|po.git_cmd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|po
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;git pack-objects failed&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We feed the pack-objects we just spawned with revision&n;&t; * parameters by writing to the pipe.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|extra-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|feed_object
c_func
(paren
id|extra-&gt;array
(braket
id|i
)braket
comma
id|po.in
comma
l_int|1
)paren
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
id|refs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|refs-&gt;old_sha1
)paren
op_logical_and
op_logical_neg
id|feed_object
c_func
(paren
id|refs-&gt;old_sha1
comma
id|po.in
comma
l_int|1
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|refs-&gt;new_sha1
)paren
op_logical_and
op_logical_neg
id|feed_object
c_func
(paren
id|refs-&gt;new_sha1
comma
id|po.in
comma
l_int|0
)paren
)paren
r_break
suffix:semicolon
id|refs
op_assign
id|refs-&gt;next
suffix:semicolon
)brace
id|close
c_func
(paren
id|po.in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;stateless_rpc
)paren
(brace
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|LARGE_PACKET_MAX
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|ssize_t
id|n
op_assign
id|xread
c_func
(paren
id|po.out
comma
id|buf
comma
id|LARGE_PACKET_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|send_sideband
c_func
(paren
id|fd
comma
l_int|1
comma
id|buf
comma
id|n
comma
id|LARGE_PACKET_MAX
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
id|close
c_func
(paren
id|po.out
)paren
suffix:semicolon
id|po.out
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|po
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
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
comma
r_struct
id|ref
op_star
id|refs
)paren
(brace
r_struct
id|ref
op_star
id|hint
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|line
op_assign
id|packet_read_line
c_func
(paren
id|in
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;unpack &quot;
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;did not receive remote status&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;unpack ok&quot;
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;unpack failed: %s&quot;
comma
id|line
op_plus
l_int|7
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|hint
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|refname
suffix:semicolon
r_char
op_star
id|msg
suffix:semicolon
id|line
op_assign
id|packet_read_line
c_func
(paren
id|in
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;ok &quot;
)paren
op_logical_and
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;ng &quot;
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;invalid ref status from remote: %s&quot;
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
id|refname
op_assign
id|line
op_plus
l_int|3
suffix:semicolon
id|msg
op_assign
id|strchr
c_func
(paren
id|refname
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
op_star
id|msg
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* first try searching at our hint, falling back to all refs */
r_if
c_cond
(paren
id|hint
)paren
id|hint
op_assign
id|find_ref_by_name
c_func
(paren
id|hint
comma
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hint
)paren
id|hint
op_assign
id|find_ref_by_name
c_func
(paren
id|refs
comma
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hint
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;remote reported status on unknown ref: %s&quot;
comma
id|refname
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hint-&gt;status
op_ne
id|REF_STATUS_EXPECTING_REPORT
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;remote reported status on unexpected ref: %s&quot;
comma
id|refname
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;o&squot;
op_logical_and
id|line
(braket
l_int|1
)braket
op_eq
l_char|&squot;k&squot;
)paren
id|hint-&gt;status
op_assign
id|REF_STATUS_OK
suffix:semicolon
r_else
(brace
id|hint-&gt;status
op_assign
id|REF_STATUS_REMOTE_REJECT
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|msg
)paren
id|hint-&gt;remote_status
op_assign
id|xstrdup
c_func
(paren
id|msg
)paren
suffix:semicolon
multiline_comment|/* start our next search from the next ref */
id|hint
op_assign
id|hint-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sideband_demux
r_static
r_int
id|sideband_demux
c_func
(paren
r_int
id|in
comma
r_int
id|out
comma
r_void
op_star
id|data
)paren
(brace
r_int
op_star
id|fd
op_assign
id|data
comma
id|ret
suffix:semicolon
macro_line|#ifdef NO_PTHREADS
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|ret
op_assign
id|recv_sideband
c_func
(paren
l_string|&quot;send-pack&quot;
comma
id|fd
(braket
l_int|0
)braket
comma
id|out
)paren
suffix:semicolon
id|close
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|send_pack
r_int
id|send_pack
c_func
(paren
r_struct
id|send_pack_args
op_star
id|args
comma
r_int
id|fd
(braket
)braket
comma
r_struct
id|child_process
op_star
id|conn
comma
r_struct
id|ref
op_star
id|remote_refs
comma
r_struct
id|extra_have_objects
op_star
id|extra_have
)paren
(brace
r_int
id|in
op_assign
id|fd
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|out
op_assign
id|fd
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|strbuf
id|req_buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|new_refs
suffix:semicolon
r_int
id|allow_deleting_refs
op_assign
l_int|0
suffix:semicolon
r_int
id|status_report
op_assign
l_int|0
suffix:semicolon
r_int
id|use_sideband
op_assign
l_int|0
suffix:semicolon
r_int
id|quiet_supported
op_assign
l_int|0
suffix:semicolon
r_int
id|agent_supported
op_assign
l_int|0
suffix:semicolon
r_int
id|cmds_sent
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|async
id|demux
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
id|status_report
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;delete-refs&quot;
)paren
)paren
id|allow_deleting_refs
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;ofs-delta&quot;
)paren
)paren
id|args-&gt;use_ofs_delta
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;side-band-64k&quot;
)paren
)paren
id|use_sideband
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;quiet&quot;
)paren
)paren
id|quiet_supported
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|server_supports
c_func
(paren
l_string|&quot;agent&quot;
)paren
)paren
id|agent_supported
op_assign
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
l_string|&quot;Perhaps you should specify a branch such as &squot;master&squot;.&bslash;n&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|ref-&gt;peer_ref
op_logical_and
op_logical_neg
id|args-&gt;send_mirror
)paren
r_continue
suffix:semicolon
multiline_comment|/* Check for statuses set by set_ref_status_for_push() */
r_switch
c_cond
(paren
id|ref-&gt;status
)paren
(brace
r_case
id|REF_STATUS_REJECT_NONFASTFORWARD
suffix:colon
r_case
id|REF_STATUS_REJECT_ALREADY_EXISTS
suffix:colon
r_case
id|REF_STATUS_REJECT_FETCH_FIRST
suffix:colon
r_case
id|REF_STATUS_REJECT_NEEDS_FORCE
suffix:colon
r_case
id|REF_STATUS_REJECT_STALE
suffix:colon
r_case
id|REF_STATUS_UPTODATE
suffix:colon
r_continue
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
multiline_comment|/* do nothing */
)brace
r_if
c_cond
(paren
id|ref-&gt;deletion
op_logical_and
op_logical_neg
id|allow_deleting_refs
)paren
(brace
id|ref-&gt;status
op_assign
id|REF_STATUS_REJECT_NODELETE
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ref-&gt;deletion
)paren
id|new_refs
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;dry_run
)paren
(brace
id|ref-&gt;status
op_assign
id|REF_STATUS_OK
suffix:semicolon
)brace
r_else
(brace
r_char
op_star
id|old_hex
op_assign
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
suffix:semicolon
r_char
op_star
id|new_hex
op_assign
id|sha1_to_hex
c_func
(paren
id|ref-&gt;new_sha1
)paren
suffix:semicolon
r_int
id|quiet
op_assign
id|quiet_supported
op_logical_and
(paren
id|args-&gt;quiet
op_logical_or
op_logical_neg
id|args-&gt;progress
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmds_sent
op_logical_and
(paren
id|status_report
op_logical_or
id|use_sideband
op_logical_or
id|quiet
op_logical_or
id|agent_supported
)paren
)paren
(brace
id|packet_buf_write
c_func
(paren
op_amp
id|req_buf
comma
l_string|&quot;%s %s %s%c%s%s%s%s%s&quot;
comma
id|old_hex
comma
id|new_hex
comma
id|ref-&gt;name
comma
l_int|0
comma
id|status_report
ques
c_cond
l_string|&quot; report-status&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|use_sideband
ques
c_cond
l_string|&quot; side-band-64k&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|quiet
ques
c_cond
l_string|&quot; quiet&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|agent_supported
ques
c_cond
l_string|&quot; agent=&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|agent_supported
ques
c_cond
id|git_user_agent_sanitized
c_func
(paren
)paren
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_else
id|packet_buf_write
c_func
(paren
op_amp
id|req_buf
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
id|ref-&gt;status
op_assign
id|status_report
ques
c_cond
id|REF_STATUS_EXPECTING_REPORT
suffix:colon
id|REF_STATUS_OK
suffix:semicolon
id|cmds_sent
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|args-&gt;stateless_rpc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|args-&gt;dry_run
op_logical_and
id|cmds_sent
)paren
(brace
id|packet_buf_flush
c_func
(paren
op_amp
id|req_buf
)paren
suffix:semicolon
id|send_sideband
c_func
(paren
id|out
comma
l_int|1
comma
id|req_buf.buf
comma
id|req_buf.len
comma
id|LARGE_PACKET_MAX
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|write_or_die
c_func
(paren
id|out
comma
id|req_buf.buf
comma
id|req_buf.len
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
id|out
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|req_buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_sideband
op_logical_and
id|cmds_sent
)paren
(brace
id|memset
c_func
(paren
op_amp
id|demux
comma
l_int|0
comma
r_sizeof
(paren
id|demux
)paren
)paren
suffix:semicolon
id|demux.proc
op_assign
id|sideband_demux
suffix:semicolon
id|demux.data
op_assign
id|fd
suffix:semicolon
id|demux.out
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_async
c_func
(paren
op_amp
id|demux
)paren
)paren
id|die
c_func
(paren
l_string|&quot;send-pack: unable to fork off sideband demultiplexer&quot;
)paren
suffix:semicolon
id|in
op_assign
id|demux.out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_refs
op_logical_and
id|cmds_sent
)paren
(brace
r_if
c_cond
(paren
id|pack_objects
c_func
(paren
id|out
comma
id|remote_refs
comma
id|extra_have
comma
id|args
)paren
OL
l_int|0
)paren
(brace
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
id|ref-&gt;status
op_assign
id|REF_STATUS_NONE
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;stateless_rpc
)paren
id|close
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_connection_is_socket
c_func
(paren
id|conn
)paren
)paren
id|shutdown
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|SHUT_WR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_sideband
)paren
id|finish_async
c_func
(paren
op_amp
id|demux
)paren
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|args-&gt;stateless_rpc
)paren
multiline_comment|/* Closed by pack_objects() via start_command() */
id|fd
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|args-&gt;stateless_rpc
op_logical_and
id|cmds_sent
)paren
id|packet_flush
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_report
op_logical_and
id|cmds_sent
)paren
id|ret
op_assign
id|receive_status
c_func
(paren
id|in
comma
id|remote_refs
)paren
suffix:semicolon
r_else
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;stateless_rpc
)paren
id|packet_flush
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_sideband
op_logical_and
id|cmds_sent
)paren
(brace
r_if
c_cond
(paren
id|finish_async
c_func
(paren
op_amp
id|demux
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;error in sideband demultiplexer&quot;
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|demux.out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;porcelain
)paren
r_return
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
r_switch
c_cond
(paren
id|ref-&gt;status
)paren
(brace
r_case
id|REF_STATUS_NONE
suffix:colon
r_case
id|REF_STATUS_UPTODATE
suffix:colon
r_case
id|REF_STATUS_OK
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
