macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;send-pack.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;transport.h&quot;
DECL|variable|send_pack_usage
r_static
r_const
r_char
id|send_pack_usage
(braket
)braket
op_assign
l_string|&quot;git send-pack [--all | --mirror] [--dry-run] [--force] [--receive-pack=&lt;git-receive-pack&gt;] [--verbose] [--thin] [&lt;host&gt;:]&lt;directory&gt; [&lt;ref&gt;...]&bslash;n&quot;
l_string|&quot;  --all and explicit &lt;ref&gt; specification are mutually exclusive.&quot;
suffix:semicolon
DECL|variable|args
r_static
r_struct
id|send_pack_args
id|args
suffix:semicolon
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
r_char
op_star
id|p
op_assign
id|line
op_plus
id|strlen
c_func
(paren
id|line
)paren
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
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
l_string|&quot;ok &quot;
comma
l_int|3
)paren
op_logical_and
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;ng &quot;
comma
l_int|3
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
id|line
(braket
id|strlen
c_func
(paren
id|line
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
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
DECL|function|print_helper_status
r_static
r_void
id|print_helper_status
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_const
r_char
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|res
suffix:semicolon
r_switch
c_cond
(paren
id|ref-&gt;status
)paren
(brace
r_case
id|REF_STATUS_NONE
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;no match&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_OK
suffix:colon
id|res
op_assign
l_string|&quot;ok&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_UPTODATE
suffix:colon
id|res
op_assign
l_string|&quot;ok&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;up to date&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NONFASTFORWARD
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;non-fast forward&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NODELETE
suffix:colon
r_case
id|REF_STATUS_REMOTE_REJECT
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_EXPECTING_REPORT
suffix:colon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%s %s&quot;
comma
id|res
comma
id|ref-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;remote_status
)paren
id|msg
op_assign
id|ref-&gt;remote_status
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|quote_two_c_style
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;&quot;
comma
id|msg
comma
l_int|0
)paren
suffix:semicolon
)brace
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|safe_write
c_func
(paren
l_int|1
comma
id|buf.buf
comma
id|buf.len
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
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
id|args-&gt;quiet
)paren
)paren
(brace
id|packet_buf_write
c_func
(paren
op_amp
id|req_buf
comma
l_string|&quot;%s %s %s%c%s%s%s&quot;
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
id|safe_write
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
r_return
l_int|1
suffix:semicolon
)brace
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
DECL|function|cmd_send_pack
r_int
id|cmd_send_pack
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
r_int
id|i
comma
id|nr_refspecs
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
op_star
id|refspecs
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|remote_name
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|remote
op_star
id|remote
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|child_process
op_star
id|conn
suffix:semicolon
r_struct
id|extra_have_objects
id|extra_have
suffix:semicolon
r_struct
id|ref
op_star
id|remote_refs
comma
op_star
id|local_refs
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|helper_status
op_assign
l_int|0
suffix:semicolon
r_int
id|send_all
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|receivepack
op_assign
l_string|&quot;git-receive-pack&quot;
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
id|nonfastforward
op_assign
l_int|0
suffix:semicolon
r_int
id|progress
op_assign
l_int|1
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
r_const
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--receive-pack=&quot;
)paren
)paren
(brace
id|receivepack
op_assign
id|arg
op_plus
l_int|15
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exec=&quot;
)paren
)paren
(brace
id|receivepack
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--remote=&quot;
)paren
)paren
(brace
id|remote_name
op_assign
id|arg
op_plus
l_int|9
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
l_string|&quot;--dry-run&quot;
)paren
)paren
(brace
id|args.dry_run
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
l_string|&quot;--mirror&quot;
)paren
)paren
(brace
id|args.send_mirror
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
id|args.force_update
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
l_string|&quot;--quiet&quot;
)paren
)paren
(brace
id|args.quiet
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
id|args.verbose
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
l_string|&quot;--progress&quot;
)paren
)paren
(brace
id|progress
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
l_string|&quot;--no-progress&quot;
)paren
)paren
(brace
id|progress
op_assign
l_int|0
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
id|args.use_thin_pack
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
l_string|&quot;--stateless-rpc&quot;
)paren
)paren
(brace
id|args.stateless_rpc
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
l_string|&quot;--helper-status&quot;
)paren
)paren
(brace
id|helper_status
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
id|refspecs
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
id|argv
suffix:semicolon
id|nr_refspecs
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
multiline_comment|/*&n;&t; * --all and --mirror are incompatible; neither makes sense&n;&t; * with any refspecs.&n;&t; */
r_if
c_cond
(paren
(paren
id|refspecs
op_logical_and
(paren
id|send_all
op_logical_or
id|args.send_mirror
)paren
)paren
op_logical_or
(paren
id|send_all
op_logical_and
id|args.send_mirror
)paren
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
id|remote_name
)paren
(brace
id|remote
op_assign
id|remote_get
c_func
(paren
id|remote_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote_has_url
c_func
(paren
id|remote
comma
id|dest
)paren
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Destination %s is not a uri for %s&quot;
comma
id|dest
comma
id|remote_name
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|progress
op_eq
l_int|1
)paren
id|progress
op_assign
op_logical_neg
id|args.quiet
op_logical_and
id|isatty
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|args.progress
op_assign
id|progress
suffix:semicolon
r_if
c_cond
(paren
id|args.stateless_rpc
)paren
(brace
id|conn
op_assign
l_int|NULL
suffix:semicolon
id|fd
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|conn
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|dest
comma
id|receivepack
comma
id|args.verbose
ques
c_cond
id|CONNECT_VERBOSE
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|extra_have
comma
l_int|0
comma
r_sizeof
(paren
id|extra_have
)paren
)paren
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
id|remote_refs
comma
id|REF_NORMAL
comma
op_amp
id|extra_have
)paren
suffix:semicolon
id|transport_verify_remote_names
c_func
(paren
id|nr_refspecs
comma
id|refspecs
)paren
suffix:semicolon
id|local_refs
op_assign
id|get_local_heads
c_func
(paren
)paren
suffix:semicolon
id|flags
op_assign
id|MATCH_REFS_NONE
suffix:semicolon
r_if
c_cond
(paren
id|send_all
)paren
id|flags
op_or_assign
id|MATCH_REFS_ALL
suffix:semicolon
r_if
c_cond
(paren
id|args.send_mirror
)paren
id|flags
op_or_assign
id|MATCH_REFS_MIRROR
suffix:semicolon
multiline_comment|/* match them up */
r_if
c_cond
(paren
id|match_push_refs
c_func
(paren
id|local_refs
comma
op_amp
id|remote_refs
comma
id|nr_refspecs
comma
id|refspecs
comma
id|flags
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|set_ref_status_for_push
c_func
(paren
id|remote_refs
comma
id|args.send_mirror
comma
id|args.force_update
)paren
suffix:semicolon
id|ret
op_assign
id|send_pack
c_func
(paren
op_amp
id|args
comma
id|fd
comma
id|conn
comma
id|remote_refs
comma
op_amp
id|extra_have
)paren
suffix:semicolon
r_if
c_cond
(paren
id|helper_status
)paren
id|print_helper_status
c_func
(paren
id|remote_refs
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
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ret
op_or_assign
id|finish_connect
c_func
(paren
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|helper_status
)paren
id|transport_print_push_status
c_func
(paren
id|dest
comma
id|remote_refs
comma
id|args.verbose
comma
l_int|0
comma
op_amp
id|nonfastforward
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|args.dry_run
op_logical_and
id|remote
)paren
(brace
r_struct
id|ref
op_star
id|ref
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
id|transport_update_tracking_ref
c_func
(paren
id|remote
comma
id|ref
comma
id|args.verbose
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
op_logical_neg
id|transport_refs_pushed
c_func
(paren
id|remote_refs
)paren
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
eof
