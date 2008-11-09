macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;send-pack.h&quot;
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
op_assign
(brace
multiline_comment|/* .receivepack = */
l_string|&quot;git-receive-pack&quot;
comma
)brace
suffix:semicolon
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
l_string|&quot;--all-progress&quot;
comma
l_string|&quot;--revs&quot;
comma
l_string|&quot;--stdout&quot;
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
r_if
c_cond
(paren
id|args.use_thin_pack
)paren
id|argv
(braket
l_int|4
)braket
op_assign
l_string|&quot;--thin&quot;
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
id|die
c_func
(paren
l_string|&quot;git pack-objects failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We feed the pack-objects we just spawned with revision&n;&t; * parameters by writing to the pipe.&n;&t; */
r_while
c_loop
(paren
id|refs
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
op_logical_neg
id|is_null_sha1
c_func
(paren
id|refs-&gt;old_sha1
)paren
op_logical_and
id|has_sha1_file
c_func
(paren
id|refs-&gt;old_sha1
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|buf
op_plus
l_int|1
comma
id|sha1_to_hex
c_func
(paren
id|refs-&gt;old_sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;^&squot;
suffix:semicolon
id|buf
(braket
l_int|41
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_or_whine
c_func
(paren
id|po.in
comma
id|buf
comma
l_int|42
comma
l_string|&quot;send-pack: send refs&quot;
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|refs-&gt;new_sha1
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|sha1_to_hex
c_func
(paren
id|refs-&gt;new_sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|buf
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_or_whine
c_func
(paren
id|po.in
comma
id|buf
comma
l_int|41
comma
l_string|&quot;send-pack: send refs&quot;
)paren
)paren
r_break
suffix:semicolon
)brace
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
id|finish_command
c_func
(paren
op_amp
id|po
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;pack-objects died with strange error&quot;
)paren
suffix:semicolon
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
id|OBJ_COMMIT
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
id|OBJ_COMMIT
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
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* we already know it starts with refs/ to get here */
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|refname
op_plus
l_int|5
)paren
)paren
r_return
l_int|0
suffix:semicolon
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
id|hashcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|sha1
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
comma
l_int|NULL
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
DECL|function|update_tracking_ref
r_static
r_void
id|update_tracking_ref
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_struct
id|refspec
id|rs
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;status
op_ne
id|REF_STATUS_OK
op_logical_and
id|ref-&gt;status
op_ne
id|REF_STATUS_UPTODATE
)paren
r_return
suffix:semicolon
id|rs.src
op_assign
id|ref-&gt;name
suffix:semicolon
id|rs.dst
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote_find_tracking
c_func
(paren
id|remote
comma
op_amp
id|rs
)paren
)paren
(brace
r_if
c_cond
(paren
id|args.verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;updating local tracking ref &squot;%s&squot;&bslash;n&quot;
comma
id|rs.dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;deletion
)paren
(brace
id|delete_ref
c_func
(paren
id|rs.dst
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|update_ref
c_func
(paren
l_string|&quot;update by push&quot;
comma
id|rs.dst
comma
id|ref-&gt;new_sha1
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|free
c_func
(paren
id|rs.dst
)paren
suffix:semicolon
)brace
)brace
DECL|function|prettify_ref
r_static
r_const
r_char
op_star
id|prettify_ref
c_func
(paren
r_const
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|ref-&gt;name
suffix:semicolon
r_return
id|name
op_plus
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/heads/&quot;
)paren
ques
c_cond
l_int|11
suffix:colon
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/tags/&quot;
)paren
ques
c_cond
l_int|10
suffix:colon
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/remotes/&quot;
)paren
ques
c_cond
l_int|13
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|macro|SUMMARY_WIDTH
mdefine_line|#define SUMMARY_WIDTH (2 * DEFAULT_ABBREV + 3)
DECL|function|print_ref_status
r_static
r_void
id|print_ref_status
c_func
(paren
r_char
id|flag
comma
r_const
r_char
op_star
id|summary
comma
r_struct
id|ref
op_star
id|to
comma
r_struct
id|ref
op_star
id|from
comma
r_const
r_char
op_star
id|msg
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %c %-*s &quot;
comma
id|flag
comma
id|SUMMARY_WIDTH
comma
id|summary
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s -&gt; %s&quot;
comma
id|prettify_ref
c_func
(paren
id|from
)paren
comma
id|prettify_ref
c_func
(paren
id|to
)paren
)paren
suffix:semicolon
r_else
id|fputs
c_func
(paren
id|prettify_ref
c_func
(paren
id|to
)paren
comma
id|stderr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
(brace
id|fputs
c_func
(paren
l_string|&quot; (&quot;
comma
id|stderr
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|msg
comma
id|stderr
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;)&squot;
comma
id|stderr
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
)brace
DECL|function|status_abbrev
r_static
r_const
r_char
op_star
id|status_abbrev
c_func
(paren
r_int
r_char
id|sha1
(braket
l_int|20
)braket
)paren
(brace
r_return
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|DEFAULT_ABBREV
)paren
suffix:semicolon
)brace
DECL|function|print_ok_ref_status
r_static
r_void
id|print_ok_ref_status
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_if
c_cond
(paren
id|ref-&gt;deletion
)paren
id|print_ref_status
c_func
(paren
l_char|&squot;-&squot;
comma
l_string|&quot;[deleted]&quot;
comma
id|ref
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
id|print_ref_status
c_func
(paren
l_char|&squot;*&squot;
comma
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/tags/&quot;
)paren
ques
c_cond
l_string|&quot;[new tag]&quot;
suffix:colon
l_string|&quot;[new branch]&quot;
)paren
comma
id|ref
comma
id|ref-&gt;peer_ref
comma
l_int|NULL
)paren
suffix:semicolon
r_else
(brace
r_char
id|quickref
(braket
l_int|84
)braket
suffix:semicolon
r_char
id|type
suffix:semicolon
r_const
r_char
op_star
id|msg
suffix:semicolon
id|strcpy
c_func
(paren
id|quickref
comma
id|status_abbrev
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;nonfastforward
)paren
(brace
id|strcat
c_func
(paren
id|quickref
comma
l_string|&quot;...&quot;
)paren
suffix:semicolon
id|type
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;forced update&quot;
suffix:semicolon
)brace
r_else
(brace
id|strcat
c_func
(paren
id|quickref
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|type
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|msg
op_assign
l_int|NULL
suffix:semicolon
)brace
id|strcat
c_func
(paren
id|quickref
comma
id|status_abbrev
c_func
(paren
id|ref-&gt;new_sha1
)paren
)paren
suffix:semicolon
id|print_ref_status
c_func
(paren
id|type
comma
id|quickref
comma
id|ref
comma
id|ref-&gt;peer_ref
comma
id|msg
)paren
suffix:semicolon
)brace
)brace
DECL|function|print_one_push_status
r_static
r_int
id|print_one_push_status
c_func
(paren
r_struct
id|ref
op_star
id|ref
comma
r_const
r_char
op_star
id|dest
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;To %s&bslash;n&quot;
comma
id|dest
)paren
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
id|print_ref_status
c_func
(paren
l_char|&squot;X&squot;
comma
l_string|&quot;[no match]&quot;
comma
id|ref
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NODELETE
suffix:colon
id|print_ref_status
c_func
(paren
l_char|&squot;!&squot;
comma
l_string|&quot;[rejected]&quot;
comma
id|ref
comma
l_int|NULL
comma
l_string|&quot;remote does not support deleting refs&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_UPTODATE
suffix:colon
id|print_ref_status
c_func
(paren
l_char|&squot;=&squot;
comma
l_string|&quot;[up to date]&quot;
comma
id|ref
comma
id|ref-&gt;peer_ref
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NONFASTFORWARD
suffix:colon
id|print_ref_status
c_func
(paren
l_char|&squot;!&squot;
comma
l_string|&quot;[rejected]&quot;
comma
id|ref
comma
id|ref-&gt;peer_ref
comma
l_string|&quot;non-fast forward&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REMOTE_REJECT
suffix:colon
id|print_ref_status
c_func
(paren
l_char|&squot;!&squot;
comma
l_string|&quot;[remote rejected]&quot;
comma
id|ref
comma
id|ref-&gt;deletion
ques
c_cond
l_int|NULL
suffix:colon
id|ref-&gt;peer_ref
comma
id|ref-&gt;remote_status
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_EXPECTING_REPORT
suffix:colon
id|print_ref_status
c_func
(paren
l_char|&squot;!&squot;
comma
l_string|&quot;[remote failure]&quot;
comma
id|ref
comma
id|ref-&gt;deletion
ques
c_cond
l_int|NULL
suffix:colon
id|ref-&gt;peer_ref
comma
l_string|&quot;remote failed to report status&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_OK
suffix:colon
id|print_ok_ref_status
c_func
(paren
id|ref
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|print_push_status
r_static
r_void
id|print_push_status
c_func
(paren
r_const
r_char
op_star
id|dest
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
id|ref
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|args.verbose
)paren
(brace
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
r_if
c_cond
(paren
id|ref-&gt;status
op_eq
id|REF_STATUS_UPTODATE
)paren
id|n
op_add_assign
id|print_one_push_status
c_func
(paren
id|ref
comma
id|dest
comma
id|n
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|ref-&gt;status
op_eq
id|REF_STATUS_OK
)paren
id|n
op_add_assign
id|print_one_push_status
c_func
(paren
id|ref
comma
id|dest
comma
id|n
)paren
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
r_if
c_cond
(paren
id|ref-&gt;status
op_ne
id|REF_STATUS_NONE
op_logical_and
id|ref-&gt;status
op_ne
id|REF_STATUS_UPTODATE
op_logical_and
id|ref-&gt;status
op_ne
id|REF_STATUS_OK
)paren
id|n
op_add_assign
id|print_one_push_status
c_func
(paren
id|ref
comma
id|dest
comma
id|n
)paren
suffix:semicolon
)brace
)brace
DECL|function|refs_pushed
r_static
r_int
id|refs_pushed
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
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
DECL|function|do_send_pack
r_static
r_int
id|do_send_pack
c_func
(paren
r_int
id|in
comma
r_int
id|out
comma
r_struct
id|remote
op_star
id|remote
comma
r_const
r_char
op_star
id|dest
comma
r_int
id|nr_refspec
comma
r_const
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
id|ask_for_status_report
op_assign
l_int|0
suffix:semicolon
r_int
id|allow_deleting_refs
op_assign
l_int|0
suffix:semicolon
r_int
id|expect_status_report
op_assign
l_int|0
suffix:semicolon
r_int
id|flags
op_assign
id|MATCH_REFS_NONE
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|args.send_all
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
id|REF_NORMAL
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
id|flags
)paren
)paren
(brace
id|close
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|close
c_func
(paren
id|out
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
id|ref-&gt;peer_ref
)paren
id|hashcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|ref-&gt;peer_ref-&gt;new_sha1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|args.send_mirror
)paren
r_continue
suffix:semicolon
id|ref-&gt;deletion
op_assign
id|is_null_sha1
c_func
(paren
id|ref-&gt;new_sha1
)paren
suffix:semicolon
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
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|ref-&gt;old_sha1
comma
id|ref-&gt;new_sha1
)paren
)paren
(brace
id|ref-&gt;status
op_assign
id|REF_STATUS_UPTODATE
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* This part determines what can overwrite what.&n;&t;&t; * The rules are:&n;&t;&t; *&n;&t;&t; * (0) you can always use --force or +A:B notation to&n;&t;&t; *     selectively force individual ref pairs.&n;&t;&t; *&n;&t;&t; * (1) if the old thing does not exist, it is OK.&n;&t;&t; *&n;&t;&t; * (2) if you do not have the old thing, you are not allowed&n;&t;&t; *     to overwrite it; you would not know what you are losing&n;&t;&t; *     otherwise.&n;&t;&t; *&n;&t;&t; * (3) if both new and old are commit-ish, and new is a&n;&t;&t; *     descendant of old, it is OK.&n;&t;&t; *&n;&t;&t; * (4) regardless of all of the above, removing :B is&n;&t;&t; *     always allowed.&n;&t;&t; */
id|ref-&gt;nonfastforward
op_assign
op_logical_neg
id|ref-&gt;deletion
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
op_logical_and
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
id|ref-&gt;new_sha1
comma
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;nonfastforward
op_logical_and
op_logical_neg
id|ref-&gt;force
op_logical_and
op_logical_neg
id|args.force_update
)paren
(brace
id|ref-&gt;status
op_assign
id|REF_STATUS_REJECT_NONFASTFORWARD
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
op_logical_neg
id|args.dry_run
)paren
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
)brace
id|ref-&gt;status
op_assign
id|expect_status_report
ques
c_cond
id|REF_STATUS_EXPECTING_REPORT
suffix:colon
id|REF_STATUS_OK
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
op_logical_and
op_logical_neg
id|args.dry_run
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
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
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
id|print_push_status
c_func
(paren
id|dest
comma
id|remote_refs
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
id|update_tracking_ref
c_func
(paren
id|remote
comma
id|ref
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|refs_pushed
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
DECL|function|verify_remote_names
r_static
r_void
id|verify_remote_names
c_func
(paren
r_int
id|nr_heads
comma
r_const
r_char
op_star
op_star
id|heads
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
id|nr_heads
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|local
op_assign
id|heads
(braket
id|i
)braket
suffix:semicolon
r_const
r_char
op_star
id|remote
op_assign
id|strrchr
c_func
(paren
id|heads
(braket
id|i
)braket
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|local
op_eq
l_char|&squot;+&squot;
)paren
id|local
op_increment
suffix:semicolon
multiline_comment|/* A matching refspec is okay.  */
r_if
c_cond
(paren
id|remote
op_eq
id|local
op_logical_and
id|remote
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_continue
suffix:semicolon
id|remote
op_assign
id|remote
ques
c_cond
(paren
id|remote
op_plus
l_int|1
)paren
suffix:colon
id|local
suffix:semicolon
r_switch
c_cond
(paren
id|check_ref_format
c_func
(paren
id|remote
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* ok */
r_case
id|CHECK_REF_FORMAT_ONELEVEL
suffix:colon
multiline_comment|/* ok but a single level -- that is fine for&n;&t;&t;&t; * a match pattern.&n;&t;&t;&t; */
r_case
id|CHECK_REF_FORMAT_WILDCARD
suffix:colon
multiline_comment|/* ok but ends with a pattern-match character */
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;remote part of refspec is not a valid name in %s&quot;
comma
id|heads
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
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
id|nr_heads
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
op_star
id|heads
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
id|args.receivepack
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
id|args.receivepack
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
id|args.send_all
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
(paren
r_const
r_char
op_star
op_star
)paren
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
multiline_comment|/*&n;&t; * --all and --mirror are incompatible; neither makes sense&n;&t; * with any refspecs.&n;&t; */
r_if
c_cond
(paren
(paren
id|heads
op_logical_and
(paren
id|args.send_all
op_logical_or
id|args.send_mirror
)paren
)paren
op_logical_or
(paren
id|args.send_all
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
r_return
id|send_pack
c_func
(paren
op_amp
id|args
comma
id|dest
comma
id|remote
comma
id|nr_heads
comma
id|heads
)paren
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
id|my_args
comma
r_const
r_char
op_star
id|dest
comma
r_struct
id|remote
op_star
id|remote
comma
r_int
id|nr_heads
comma
r_const
r_char
op_star
op_star
id|heads
)paren
(brace
r_int
id|fd
(braket
l_int|2
)braket
comma
id|ret
suffix:semicolon
r_struct
id|child_process
op_star
id|conn
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|args
comma
id|my_args
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|verify_remote_names
c_func
(paren
id|nr_heads
comma
id|heads
)paren
suffix:semicolon
id|conn
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|dest
comma
id|args.receivepack
comma
id|args.verbose
ques
c_cond
id|CONNECT_VERBOSE
suffix:colon
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|do_send_pack
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
id|remote
comma
id|dest
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
multiline_comment|/* do_send_pack always closes fd[1] */
id|ret
op_or_assign
id|finish_connect
c_func
(paren
id|conn
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|ret
suffix:semicolon
)brace
eof
