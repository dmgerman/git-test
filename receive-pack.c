macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;run-command.h&quot;
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
DECL|variable|unpacker
r_static
r_const
r_char
id|unpacker
(braket
)braket
op_assign
l_string|&quot;git-unpack-objects&quot;
suffix:semicolon
DECL|variable|report_status
r_static
r_int
id|report_status
op_assign
l_int|0
suffix:semicolon
DECL|variable|capabilities
r_static
r_char
id|capabilities
(braket
)braket
op_assign
l_string|&quot;report-status&quot;
suffix:semicolon
DECL|variable|capabilities_sent
r_static
r_int
id|capabilities_sent
op_assign
l_int|0
suffix:semicolon
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
op_assign
l_int|NULL
suffix:semicolon
DECL|function|is_all_zeroes
r_static
r_int
id|is_all_zeroes
c_func
(paren
r_const
r_char
op_star
id|hex
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
l_int|40
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
id|hex
op_increment
op_ne
l_char|&squot;0&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|verify_old_ref
r_static
r_int
id|verify_old_ref
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_char
op_star
id|hex_contents
)paren
(brace
r_int
id|fd
comma
id|ret
suffix:semicolon
r_char
id|buffer
(braket
l_int|60
)braket
suffix:semicolon
r_if
c_cond
(paren
id|is_all_zeroes
c_func
(paren
id|hex_contents
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|name
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
id|read
c_func
(paren
id|fd
comma
id|buffer
comma
l_int|40
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|40
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
id|hex_contents
comma
l_int|40
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
l_string|&quot;%s died of signal&bslash;n&quot;
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
l_int|60
)braket
comma
op_star
id|old_hex
comma
op_star
id|lock_name
suffix:semicolon
r_int
id|newfd
comma
id|namelen
comma
id|written
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
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|lock_name
op_assign
id|xmalloc
c_func
(paren
id|namelen
op_plus
l_int|10
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|lock_name
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|lock_name
op_plus
id|namelen
comma
l_string|&quot;.lock&quot;
comma
l_int|6
)paren
suffix:semicolon
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
id|old_hex
op_assign
id|sha1_to_hex
c_func
(paren
id|old_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|safe_create_leading_directories
c_func
(paren
id|lock_name
)paren
suffix:semicolon
id|newfd
op_assign
id|open
c_func
(paren
id|lock_name
comma
id|O_CREAT
op_or
id|O_EXCL
op_or
id|O_WRONLY
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newfd
OL
l_int|0
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;can&squot;t lock&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unable to create %s (%s)&quot;
comma
id|lock_name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Write the ref with an ending &squot;&bslash;n&squot; */
id|new_hex
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|new_hex
(braket
l_int|41
)braket
op_assign
l_int|0
suffix:semicolon
id|written
op_assign
id|write
c_func
(paren
id|newfd
comma
id|new_hex
comma
l_int|41
)paren
suffix:semicolon
multiline_comment|/* Remove the &squot;&bslash;n&squot; again */
id|new_hex
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
id|close
c_func
(paren
id|newfd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
op_ne
l_int|41
)paren
(brace
id|unlink
c_func
(paren
id|lock_name
)paren
suffix:semicolon
id|cmd-&gt;error_string
op_assign
l_string|&quot;can&squot;t write&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unable to write %s&quot;
comma
id|lock_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verify_old_ref
c_func
(paren
id|name
comma
id|old_hex
)paren
OL
l_int|0
)paren
(brace
id|unlink
c_func
(paren
id|lock_name
)paren
suffix:semicolon
id|cmd-&gt;error_string
op_assign
l_string|&quot;raced&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;%s changed during push&quot;
comma
id|name
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
id|unlink
c_func
(paren
id|lock_name
)paren
suffix:semicolon
id|cmd-&gt;error_string
op_assign
l_string|&quot;hook declined&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;hook declined to update %s&bslash;n&quot;
comma
id|name
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
id|lock_name
comma
id|name
)paren
OL
l_int|0
)paren
(brace
id|unlink
c_func
(paren
id|lock_name
)paren
suffix:semicolon
id|cmd-&gt;error_string
op_assign
l_string|&quot;can&squot;t rename&quot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unable to replace %s&quot;
comma
id|name
)paren
suffix:semicolon
)brace
r_else
(brace
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
r_return
l_int|0
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|cmd_p-&gt;error_string
)paren
r_continue
suffix:semicolon
id|argv
(braket
id|argc
)braket
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
id|argv
(braket
id|argc
)braket
comma
id|cmd_p-&gt;ref_name
)paren
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
id|memcpy
c_func
(paren
id|cmd-&gt;old_sha1
comma
id|old_sha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd-&gt;new_sha1
comma
id|new_sha1
comma
l_int|20
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
DECL|function|unpack
r_static
r_const
r_char
op_star
id|unpack
c_func
(paren
r_int
op_star
id|error_code
)paren
(brace
r_int
id|code
op_assign
id|run_command
c_func
(paren
id|unpacker
comma
l_int|NULL
)paren
suffix:semicolon
op_star
id|error_code
op_assign
l_int|0
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
op_star
id|error_code
op_assign
id|code
suffix:semicolon
r_return
l_string|&quot;unpacker exited with error code&quot;
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
(brace
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: unable to chdir or not a git archive&quot;
comma
id|dir
)paren
suffix:semicolon
)brace
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
r_int
id|code
suffix:semicolon
r_const
r_char
op_star
id|unpack_status
op_assign
id|unpack
c_func
(paren
op_amp
id|code
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
