macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|receive_pack_usage
r_static
r_const
r_char
id|receive_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-receive-pack &lt;git-dir&gt;&quot;
suffix:semicolon
DECL|variable|deny_non_fast_forwards
r_static
r_int
id|deny_non_fast_forwards
op_assign
l_int|0
suffix:semicolon
DECL|variable|unpack_limit
r_static
r_int
id|unpack_limit
op_assign
l_int|5000
suffix:semicolon
DECL|variable|report_status
r_static
r_int
id|report_status
suffix:semicolon
DECL|variable|capabilities
r_static
r_char
id|capabilities
(braket
)braket
op_assign
l_string|&quot; report-status delete-refs &quot;
suffix:semicolon
DECL|variable|capabilities_sent
r_static
r_int
id|capabilities_sent
suffix:semicolon
DECL|function|receive_pack_config
r_static
r_int
id|receive_pack_config
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
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;receive.denynonfastforwards&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|deny_non_fast_forwards
op_assign
id|git_config_bool
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;receive.unpacklimit&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|unpack_limit
op_assign
id|git_config_int
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_ref
r_static
r_int
id|show_ref
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
r_if
c_cond
(paren
id|capabilities_sent
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|path
)paren
suffix:semicolon
r_else
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s%c%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|path
comma
l_int|0
comma
id|capabilities
)paren
suffix:semicolon
id|capabilities_sent
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_head_info
r_static
r_void
id|write_head_info
c_func
(paren
r_void
)paren
(brace
id|for_each_ref
c_func
(paren
id|show_ref
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capabilities_sent
)paren
id|show_ref
c_func
(paren
l_string|&quot;capabilities^{}&quot;
comma
id|null_sha1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|struct|command
r_struct
id|command
(brace
DECL|member|next
r_struct
id|command
op_star
id|next
suffix:semicolon
DECL|member|error_string
r_const
r_char
op_star
id|error_string
suffix:semicolon
DECL|member|old_sha1
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|new_sha1
r_int
r_char
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|ref_name
r_char
id|ref_name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
multiline_comment|/* more */
)brace
suffix:semicolon
DECL|variable|commands
r_static
r_struct
id|command
op_star
id|commands
suffix:semicolon
DECL|variable|update_hook
r_static
r_char
id|update_hook
(braket
)braket
op_assign
l_string|&quot;hooks/update&quot;
suffix:semicolon
DECL|function|run_update_hook
r_static
r_int
id|run_update_hook
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_char
op_star
id|old_hex
comma
r_char
op_star
id|new_hex
)paren
(brace
r_int
id|code
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|update_hook
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|code
op_assign
id|run_command
c_func
(paren
id|update_hook
comma
id|refname
comma
id|old_hex
comma
id|new_hex
comma
l_int|NULL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_FORK
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;hook fork failed&quot;
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_EXEC
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;hook execute failed&quot;
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;waitpid failed&quot;
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID_WRONG_PID
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;waitpid is confused&quot;
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID_SIGNAL
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;%s died of signal&quot;
comma
id|update_hook
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID_NOEXIT
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;%s died strangely&quot;
comma
id|update_hook
)paren
suffix:semicolon
r_default
suffix:colon
id|error
c_func
(paren
l_string|&quot;%s exited with error code %d&quot;
comma
id|update_hook
comma
id|code
)paren
suffix:semicolon
r_return
id|code
suffix:semicolon
)brace
)brace
DECL|function|update
r_static
r_int
id|update
c_func
(paren
r_struct
id|command
op_star
id|cmd
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|cmd-&gt;ref_name
suffix:semicolon
r_int
r_char
op_star
id|old_sha1
op_assign
id|cmd-&gt;old_sha1
suffix:semicolon
r_int
r_char
op_star
id|new_sha1
op_assign
id|cmd-&gt;new_sha1
suffix:semicolon
r_char
id|new_hex
(braket
l_int|41
)braket
comma
id|old_hex
(braket
l_int|41
)braket
suffix:semicolon
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
id|cmd-&gt;error_string
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
op_logical_and
id|check_ref_format
c_func
(paren
id|name
op_plus
l_int|5
)paren
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;funny refname&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;refusing to create funny ref &squot;%s&squot; locally&quot;
comma
id|name
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|new_hex
comma
id|sha1_to_hex
c_func
(paren
id|new_sha1
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|old_hex
comma
id|sha1_to_hex
c_func
(paren
id|old_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|new_sha1
)paren
op_logical_and
op_logical_neg
id|has_sha1_file
c_func
(paren
id|new_sha1
)paren
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;bad pack&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unpack should have generated %s, &quot;
l_string|&quot;but I can&squot;t find it!&quot;
comma
id|new_hex
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|deny_non_fast_forwards
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|new_sha1
)paren
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|old_sha1
)paren
)paren
(brace
r_struct
id|commit
op_star
id|old_commit
comma
op_star
id|new_commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|bases
comma
op_star
id|ent
suffix:semicolon
id|old_commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|parse_object
c_func
(paren
id|old_sha1
)paren
suffix:semicolon
id|new_commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|parse_object
c_func
(paren
id|new_sha1
)paren
suffix:semicolon
id|bases
op_assign
id|get_merge_bases
c_func
(paren
id|old_commit
comma
id|new_commit
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ent
op_assign
id|bases
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
op_logical_neg
id|hashcmp
c_func
(paren
id|old_sha1
comma
id|ent-&gt;item-&gt;object.sha1
)paren
)paren
r_break
suffix:semicolon
id|free_commit_list
c_func
(paren
id|bases
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
id|error
c_func
(paren
l_string|&quot;denying non-fast forward;&quot;
l_string|&quot; you should pull first&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|run_update_hook
c_func
(paren
id|name
comma
id|old_hex
comma
id|new_hex
)paren
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;hook declined&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;hook declined to update %s&quot;
comma
id|name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|new_sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|name
comma
id|old_sha1
)paren
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;failed to delete&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;failed to delete %s&quot;
comma
id|name
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %s -&gt; deleted&bslash;n&quot;
comma
id|name
comma
id|old_hex
)paren
suffix:semicolon
)brace
r_else
(brace
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|name
comma
id|old_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;failed to lock&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;failed to lock %s&quot;
comma
id|name
)paren
suffix:semicolon
)brace
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|new_sha1
comma
l_string|&quot;push&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %s -&gt; %s&bslash;n&quot;
comma
id|name
comma
id|old_hex
comma
id|new_hex
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|update_post_hook
r_static
r_char
id|update_post_hook
(braket
)braket
op_assign
l_string|&quot;hooks/post-update&quot;
suffix:semicolon
DECL|function|run_update_post_hook
r_static
r_void
id|run_update_post_hook
c_func
(paren
r_struct
id|command
op_star
id|cmd
)paren
(brace
r_struct
id|command
op_star
id|cmd_p
suffix:semicolon
r_int
id|argc
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|update_post_hook
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|argc
op_assign
l_int|1
comma
id|cmd_p
op_assign
id|cmd
suffix:semicolon
id|cmd_p
suffix:semicolon
id|cmd_p
op_assign
id|cmd_p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|cmd_p-&gt;error_string
)paren
r_continue
suffix:semicolon
id|argc
op_increment
suffix:semicolon
)brace
id|argv
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|argv
)paren
op_star
(paren
l_int|1
op_plus
id|argc
)paren
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|update_post_hook
suffix:semicolon
r_for
c_loop
(paren
id|argc
op_assign
l_int|1
comma
id|cmd_p
op_assign
id|cmd
suffix:semicolon
id|cmd_p
suffix:semicolon
id|cmd_p
op_assign
id|cmd_p-&gt;next
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|cmd_p-&gt;error_string
)paren
r_continue
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|cmd_p-&gt;ref_name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
comma
id|cmd_p-&gt;ref_name
)paren
suffix:semicolon
id|argv
(braket
id|argc
)braket
op_assign
id|p
suffix:semicolon
id|argc
op_increment
suffix:semicolon
)brace
id|argv
(braket
id|argc
)braket
op_assign
l_int|NULL
suffix:semicolon
id|run_command_v_opt
c_func
(paren
id|argc
comma
id|argv
comma
id|RUN_COMMAND_NO_STDIO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets called after(if) we&squot;ve successfully&n; * unpacked the data payload.&n; */
DECL|function|execute_commands
r_static
r_void
id|execute_commands
c_func
(paren
r_void
)paren
(brace
r_struct
id|command
op_star
id|cmd
op_assign
id|commands
suffix:semicolon
r_while
c_loop
(paren
id|cmd
)paren
(brace
id|update
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|cmd
op_assign
id|cmd-&gt;next
suffix:semicolon
)brace
id|run_update_post_hook
c_func
(paren
id|commands
)paren
suffix:semicolon
)brace
DECL|function|read_head_info
r_static
r_void
id|read_head_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|command
op_star
op_star
id|p
op_assign
op_amp
id|commands
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
comma
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|command
op_star
id|cmd
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_int
id|len
comma
id|reflen
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
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
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|83
op_logical_or
id|line
(braket
l_int|40
)braket
op_ne
l_char|&squot; &squot;
op_logical_or
id|line
(braket
l_int|81
)braket
op_ne
l_char|&squot; &squot;
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
comma
id|old_sha1
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|41
comma
id|new_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: expected old/new/ref, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
id|refname
op_assign
id|line
op_plus
l_int|82
suffix:semicolon
id|reflen
op_assign
id|strlen
c_func
(paren
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reflen
op_plus
l_int|82
OL
id|len
)paren
(brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|refname
op_plus
id|reflen
op_plus
l_int|1
comma
l_string|&quot;report-status&quot;
)paren
)paren
id|report_status
op_assign
l_int|1
suffix:semicolon
)brace
id|cmd
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|command
)paren
op_plus
id|len
l_int|80
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|cmd-&gt;old_sha1
comma
id|old_sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|cmd-&gt;new_sha1
comma
id|new_sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd-&gt;ref_name
comma
id|line
op_plus
l_int|82
comma
id|len
l_int|81
)paren
suffix:semicolon
id|cmd-&gt;error_string
op_assign
l_string|&quot;n/a (unpacker error)&quot;
suffix:semicolon
id|cmd-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|p
op_assign
id|cmd
suffix:semicolon
id|p
op_assign
op_amp
id|cmd-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|parse_pack_header
r_static
r_const
r_char
op_star
id|parse_pack_header
c_func
(paren
r_struct
id|pack_header
op_star
id|hdr
)paren
(brace
r_char
op_star
id|c
op_assign
(paren
r_char
op_star
)paren
id|hdr
suffix:semicolon
id|ssize_t
id|remaining
op_assign
r_sizeof
(paren
r_struct
id|pack_header
)paren
suffix:semicolon
r_do
(brace
id|ssize_t
id|r
op_assign
id|xread
c_func
(paren
l_int|0
comma
id|c
comma
id|remaining
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_le
l_int|0
)paren
r_return
l_string|&quot;eof before pack header was fully read&quot;
suffix:semicolon
id|remaining
op_sub_assign
id|r
suffix:semicolon
id|c
op_add_assign
id|r
suffix:semicolon
)brace
r_while
c_loop
(paren
id|remaining
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;hdr_signature
op_ne
id|htonl
c_func
(paren
id|PACK_SIGNATURE
)paren
)paren
r_return
l_string|&quot;protocol error (pack signature mismatch detected)&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pack_version_ok
c_func
(paren
id|hdr-&gt;hdr_version
)paren
)paren
r_return
l_string|&quot;protocol error (pack version unsupported)&quot;
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|pack_lockfile
r_static
r_const
r_char
op_star
id|pack_lockfile
suffix:semicolon
DECL|function|unpack
r_static
r_const
r_char
op_star
id|unpack
c_func
(paren
r_void
)paren
(brace
r_struct
id|pack_header
id|hdr
suffix:semicolon
r_const
r_char
op_star
id|hdr_err
suffix:semicolon
r_char
id|hdr_arg
(braket
l_int|38
)braket
suffix:semicolon
id|hdr_err
op_assign
id|parse_pack_header
c_func
(paren
op_amp
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr_err
)paren
r_return
id|hdr_err
suffix:semicolon
id|snprintf
c_func
(paren
id|hdr_arg
comma
r_sizeof
(paren
id|hdr_arg
)paren
comma
l_string|&quot;--pack_header=%u,%u&quot;
comma
id|ntohl
c_func
(paren
id|hdr.hdr_version
)paren
comma
id|ntohl
c_func
(paren
id|hdr.hdr_entries
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohl
c_func
(paren
id|hdr.hdr_entries
)paren
OL
id|unpack_limit
)paren
(brace
r_int
id|code
suffix:semicolon
r_const
r_char
op_star
id|unpacker
(braket
l_int|3
)braket
suffix:semicolon
id|unpacker
(braket
l_int|0
)braket
op_assign
l_string|&quot;unpack-objects&quot;
suffix:semicolon
id|unpacker
(braket
l_int|1
)braket
op_assign
id|hdr_arg
suffix:semicolon
id|unpacker
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|code
op_assign
id|run_command_v_opt
c_func
(paren
l_int|1
comma
id|unpacker
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|NULL
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_FORK
suffix:colon
r_return
l_string|&quot;unpack fork failed&quot;
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_EXEC
suffix:colon
r_return
l_string|&quot;unpack execute failed&quot;
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID
suffix:colon
r_return
l_string|&quot;waitpid failed&quot;
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID_WRONG_PID
suffix:colon
r_return
l_string|&quot;waitpid is confused&quot;
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID_SIGNAL
suffix:colon
r_return
l_string|&quot;unpacker died of signal&quot;
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID_NOEXIT
suffix:colon
r_return
l_string|&quot;unpacker died strangely&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unpacker exited with error code&quot;
suffix:semicolon
)brace
)brace
r_else
(brace
r_const
r_char
op_star
id|keeper
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
comma
id|s
comma
id|len
comma
id|status
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_char
id|keep_arg
(braket
l_int|256
)braket
suffix:semicolon
r_char
id|packname
(braket
l_int|46
)braket
suffix:semicolon
id|s
op_assign
id|sprintf
c_func
(paren
id|keep_arg
comma
l_string|&quot;--keep=receive-pack %i on &quot;
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
id|keeper
(braket
l_int|0
)braket
op_assign
l_string|&quot;index-pack&quot;
suffix:semicolon
id|keeper
(braket
l_int|1
)braket
op_assign
l_string|&quot;--stdin&quot;
suffix:semicolon
id|keeper
(braket
l_int|2
)braket
op_assign
l_string|&quot;--fix-thin&quot;
suffix:semicolon
id|keeper
(braket
l_int|3
)braket
op_assign
id|hdr_arg
suffix:semicolon
id|keeper
(braket
l_int|4
)braket
op_assign
id|keep_arg
suffix:semicolon
id|keeper
(braket
l_int|5
)braket
op_assign
l_int|NULL
suffix:semicolon
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
r_return
l_string|&quot;index-pack pipe failed&quot;
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
r_return
l_string|&quot;index-pack fork failed&quot;
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
l_int|1
)braket
comma
l_int|1
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
id|execv_git_cmd
c_func
(paren
id|keeper
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;execv of index-pack failed&quot;
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The first thing we expects from index-pack&squot;s output&n;&t;&t; * is &quot;pack&bslash;t%40s&bslash;n&quot; or &quot;keep&bslash;t%40s&bslash;n&quot; (46 bytes) where&n;&t;&t; * %40s is the newly created pack SHA1 name.  In the &quot;keep&quot;&n;&t;&t; * case, we need it to remove the corresponding .keep file&n;&t;&t; * later on.  If we don&squot;t get that then tough luck with it.&n;&t;&t; */
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
template_param
l_int|0
suffix:semicolon
id|len
op_add_assign
id|s
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
r_if
c_cond
(paren
id|len
op_eq
l_int|46
op_logical_and
id|packname
(braket
l_int|45
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|memcmp
c_func
(paren
id|packname
comma
l_string|&quot;keep&bslash;t&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|packname
(braket
l_int|45
)braket
op_assign
l_int|0
suffix:semicolon
id|snprintf
c_func
(paren
id|path
comma
r_sizeof
(paren
id|path
)paren
comma
l_string|&quot;%s/pack/pack-%s.keep&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|packname
op_plus
l_int|5
)paren
suffix:semicolon
id|pack_lockfile
op_assign
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
multiline_comment|/* Then wrap our index-pack process. */
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
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
r_return
l_string|&quot;waitpid failed&quot;
suffix:semicolon
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
r_return
l_string|&quot;index-pack exited with error code&quot;
suffix:semicolon
id|reprepare_packed_git
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
l_string|&quot;index-pack abnormal exit&quot;
suffix:semicolon
)brace
)brace
DECL|function|report
r_static
r_void
id|report
c_func
(paren
r_const
r_char
op_star
id|unpack_status
)paren
(brace
r_struct
id|command
op_star
id|cmd
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;unpack %s&bslash;n&quot;
comma
id|unpack_status
ques
c_cond
id|unpack_status
suffix:colon
l_string|&quot;ok&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cmd
op_assign
id|commands
suffix:semicolon
id|cmd
suffix:semicolon
id|cmd
op_assign
id|cmd-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cmd-&gt;error_string
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ok %s&bslash;n&quot;
comma
id|cmd-&gt;ref_name
)paren
suffix:semicolon
r_else
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ng %s %s&bslash;n&quot;
comma
id|cmd-&gt;ref_name
comma
id|cmd-&gt;error_string
)paren
suffix:semicolon
)brace
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|delete_only
r_static
r_int
id|delete_only
c_func
(paren
r_struct
id|command
op_star
id|cmd
)paren
(brace
r_while
c_loop
(paren
id|cmd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|cmd-&gt;new_sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|cmd
op_assign
id|cmd-&gt;next
suffix:semicolon
)brace
r_return
l_int|1
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
suffix:semicolon
r_char
op_star
id|dir
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
)paren
(brace
r_char
op_star
id|arg
op_assign
op_star
id|argv
op_increment
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
multiline_comment|/* Do flag handling here */
id|usage
c_func
(paren
id|receive_pack_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir
)paren
id|usage
c_func
(paren
id|receive_pack_usage
)paren
suffix:semicolon
id|dir
op_assign
id|arg
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
id|usage
c_func
(paren
id|receive_pack_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enter_repo
c_func
(paren
id|dir
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: unable to chdir or not a git archive&quot;
comma
id|dir
)paren
suffix:semicolon
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|receive_pack_config
)paren
suffix:semicolon
id|write_head_info
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* EOF */
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|read_head_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commands
)paren
(brace
r_const
r_char
op_star
id|unpack_status
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|delete_only
c_func
(paren
id|commands
)paren
)paren
id|unpack_status
op_assign
id|unpack
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unpack_status
)paren
id|execute_commands
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pack_lockfile
)paren
id|unlink
c_func
(paren
id|pack_lockfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|report_status
)paren
id|report
c_func
(paren
id|unpack_status
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
