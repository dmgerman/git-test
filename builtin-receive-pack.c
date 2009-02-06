macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;transport.h&quot;
DECL|variable|receive_pack_usage
r_static
r_const
r_char
id|receive_pack_usage
(braket
)braket
op_assign
l_string|&quot;git receive-pack &lt;git-dir&gt;&quot;
suffix:semicolon
DECL|enum|deny_action
r_enum
id|deny_action
(brace
DECL|enumerator|DENY_UNCONFIGURED
id|DENY_UNCONFIGURED
comma
DECL|enumerator|DENY_IGNORE
id|DENY_IGNORE
comma
DECL|enumerator|DENY_WARN
id|DENY_WARN
comma
DECL|enumerator|DENY_REFUSE
id|DENY_REFUSE
comma
)brace
suffix:semicolon
DECL|variable|deny_deletes
r_static
r_int
id|deny_deletes
op_assign
l_int|0
suffix:semicolon
DECL|variable|deny_non_fast_forwards
r_static
r_int
id|deny_non_fast_forwards
op_assign
l_int|0
suffix:semicolon
DECL|variable|deny_current_branch
r_static
r_enum
id|deny_action
id|deny_current_branch
op_assign
id|DENY_UNCONFIGURED
suffix:semicolon
DECL|variable|receive_fsck_objects
r_static
r_int
id|receive_fsck_objects
suffix:semicolon
DECL|variable|receive_unpack_limit
r_static
r_int
id|receive_unpack_limit
op_assign
l_int|1
suffix:semicolon
DECL|variable|transfer_unpack_limit
r_static
r_int
id|transfer_unpack_limit
op_assign
l_int|1
suffix:semicolon
DECL|variable|unpack_limit
r_static
r_int
id|unpack_limit
op_assign
l_int|100
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
DECL|function|parse_deny_action
r_static
r_enum
id|deny_action
id|parse_deny_action
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
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;ignore&quot;
)paren
)paren
r_return
id|DENY_IGNORE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;warn&quot;
)paren
)paren
r_return
id|DENY_WARN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;refuse&quot;
)paren
)paren
r_return
id|DENY_REFUSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
)paren
r_return
id|DENY_REFUSE
suffix:semicolon
r_return
id|DENY_IGNORE
suffix:semicolon
)brace
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
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;receive.denydeletes&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|deny_deletes
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
id|receive_unpack_limit
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;transfer.unpacklimit&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|transfer_unpack_limit
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;receive.fsckobjects&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|receive_fsck_objects
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
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;receive.denycurrentbranch&quot;
)paren
)paren
(brace
id|deny_current_branch
op_assign
id|parse_deny_action
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
DECL|variable|pre_receive_hook
r_static
r_const
r_char
id|pre_receive_hook
(braket
)braket
op_assign
l_string|&quot;hooks/pre-receive&quot;
suffix:semicolon
DECL|variable|post_receive_hook
r_static
r_const
r_char
id|post_receive_hook
(braket
)braket
op_assign
l_string|&quot;hooks/post-receive&quot;
suffix:semicolon
DECL|function|hook_status
r_static
r_int
id|hook_status
c_func
(paren
r_int
id|code
comma
r_const
r_char
op_star
id|hook_name
)paren
(brace
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
id|ERR_RUN_COMMAND_PIPE
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;hook pipe failed&quot;
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
id|hook_name
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
id|hook_name
)paren
suffix:semicolon
r_default
suffix:colon
id|error
c_func
(paren
l_string|&quot;%s exited with error code %d&quot;
comma
id|hook_name
comma
id|code
)paren
suffix:semicolon
r_return
id|code
suffix:semicolon
)brace
)brace
DECL|function|run_receive_hook
r_static
r_int
id|run_receive_hook
c_func
(paren
r_const
r_char
op_star
id|hook_name
)paren
(brace
r_static
r_char
id|buf
(braket
r_sizeof
(paren
id|commands-&gt;old_sha1
)paren
op_star
l_int|2
op_plus
id|PATH_MAX
op_plus
l_int|4
)braket
suffix:semicolon
r_struct
id|command
op_star
id|cmd
suffix:semicolon
r_struct
id|child_process
id|proc
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|have_input
op_assign
l_int|0
comma
id|code
suffix:semicolon
r_for
c_loop
(paren
id|cmd
op_assign
id|commands
suffix:semicolon
op_logical_neg
id|have_input
op_logical_and
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
id|have_input
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|have_input
op_logical_or
id|access
c_func
(paren
id|hook_name
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|hook_name
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|proc
comma
l_int|0
comma
r_sizeof
(paren
id|proc
)paren
)paren
suffix:semicolon
id|proc.argv
op_assign
id|argv
suffix:semicolon
id|proc.in
op_assign
l_int|1
suffix:semicolon
id|proc.stdout_to_stderr
op_assign
l_int|1
suffix:semicolon
id|code
op_assign
id|start_command
c_func
(paren
op_amp
id|proc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
r_return
id|hook_status
c_func
(paren
id|code
comma
id|hook_name
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
(brace
r_int
id|n
op_assign
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;%s %s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|cmd-&gt;old_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|cmd-&gt;new_sha1
)paren
comma
id|cmd-&gt;ref_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|proc.in
comma
id|buf
comma
id|n
)paren
op_ne
id|n
)paren
r_break
suffix:semicolon
)brace
)brace
id|close
c_func
(paren
id|proc.in
)paren
suffix:semicolon
r_return
id|hook_status
c_func
(paren
id|finish_command
c_func
(paren
op_amp
id|proc
)paren
comma
id|hook_name
)paren
suffix:semicolon
)brace
DECL|function|run_update_hook
r_static
r_int
id|run_update_hook
c_func
(paren
r_struct
id|command
op_star
id|cmd
)paren
(brace
r_static
r_const
r_char
id|update_hook
(braket
)braket
op_assign
l_string|&quot;hooks/update&quot;
suffix:semicolon
r_struct
id|child_process
id|proc
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|5
)braket
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
id|argv
(braket
l_int|0
)braket
op_assign
id|update_hook
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
id|cmd-&gt;ref_name
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
id|sha1_to_hex
c_func
(paren
id|cmd-&gt;old_sha1
)paren
suffix:semicolon
id|argv
(braket
l_int|3
)braket
op_assign
id|sha1_to_hex
c_func
(paren
id|cmd-&gt;new_sha1
)paren
suffix:semicolon
id|argv
(braket
l_int|4
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|proc
comma
l_int|0
comma
r_sizeof
(paren
id|proc
)paren
)paren
suffix:semicolon
id|proc.argv
op_assign
id|argv
suffix:semicolon
id|proc.no_stdin
op_assign
l_int|1
suffix:semicolon
id|proc.stdout_to_stderr
op_assign
l_int|1
suffix:semicolon
r_return
id|hook_status
c_func
(paren
id|run_command
c_func
(paren
op_amp
id|proc
)paren
comma
id|update_hook
)paren
suffix:semicolon
)brace
DECL|function|is_ref_checked_out
r_static
r_int
id|is_ref_checked_out
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|head
suffix:semicolon
r_if
c_cond
(paren
id|is_bare_repository
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|head
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
id|ref
)paren
suffix:semicolon
)brace
DECL|variable|warn_unconfigured_deny_msg
r_static
r_char
op_star
id|warn_unconfigured_deny_msg
(braket
)braket
op_assign
(brace
l_string|&quot;Updating the currently checked out branch may cause confusion,&quot;
comma
l_string|&quot;as the index and work tree do not reflect changes that are in HEAD.&quot;
comma
l_string|&quot;As a result, you may see the changes you just pushed into it&quot;
comma
l_string|&quot;reverted when you run &squot;git diff&squot; over there, and you may want&quot;
comma
l_string|&quot;to run &squot;git reset --hard&squot; before starting to work to recover.&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;You can set &squot;receive.denyCurrentBranch&squot; configuration variable to&quot;
comma
l_string|&quot;&squot;refuse&squot; in the remote repository to forbid pushing into its&quot;
comma
l_string|&quot;current branch.&quot;
l_string|&quot;&quot;
comma
l_string|&quot;To allow pushing into the current branch, you can set it to &squot;ignore&squot;;&quot;
comma
l_string|&quot;but this is not recommended unless you arranged to update its work&quot;
comma
l_string|&quot;tree to match what you pushed in some other way.&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;To squelch this message, you can set it to &squot;warn&squot;.&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;Note that the default will change in a future version of git&quot;
comma
l_string|&quot;to refuse updating the current branch unless you have the&quot;
comma
l_string|&quot;configuration variable set to either &squot;ignore&squot; or &squot;warn&squot;.&quot;
)brace
suffix:semicolon
DECL|function|warn_unconfigured_deny
r_static
r_void
id|warn_unconfigured_deny
c_func
(paren
r_void
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
id|ARRAY_SIZE
c_func
(paren
id|warn_unconfigured_deny_msg
)paren
suffix:semicolon
id|i
op_increment
)paren
id|warning
c_func
(paren
id|warn_unconfigured_deny_msg
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|update
r_static
r_const
r_char
op_star
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
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
multiline_comment|/* only refs/... are allowed */
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/&quot;
)paren
op_logical_or
id|check_ref_format
c_func
(paren
id|name
op_plus
l_int|5
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;refusing to create funny ref &squot;%s&squot; remotely&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;funny refname&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_ref_checked_out
c_func
(paren
id|name
)paren
)paren
(brace
r_switch
c_cond
(paren
id|deny_current_branch
)paren
(brace
r_case
id|DENY_IGNORE
suffix:colon
r_break
suffix:semicolon
r_case
id|DENY_UNCONFIGURED
suffix:colon
r_case
id|DENY_WARN
suffix:colon
id|warning
c_func
(paren
l_string|&quot;updating the current branch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deny_current_branch
op_eq
id|DENY_UNCONFIGURED
)paren
id|warn_unconfigured_deny
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DENY_REFUSE
suffix:colon
id|error
c_func
(paren
l_string|&quot;refusing to update checked out branch: %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;branch is currently checked out&quot;
suffix:semicolon
)brace
)brace
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
id|error
c_func
(paren
l_string|&quot;unpack should have generated %s, &quot;
l_string|&quot;but I can&squot;t find it!&quot;
comma
id|sha1_to_hex
c_func
(paren
id|new_sha1
)paren
)paren
suffix:semicolon
r_return
l_string|&quot;bad pack&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|deny_deletes
op_logical_and
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
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;denying ref deletion for %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;deletion prohibited&quot;
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
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
(brace
r_struct
id|object
op_star
id|old_object
comma
op_star
id|new_object
suffix:semicolon
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
id|old_object
op_assign
id|parse_object
c_func
(paren
id|old_sha1
)paren
suffix:semicolon
id|new_object
op_assign
id|parse_object
c_func
(paren
id|new_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_object
op_logical_or
op_logical_neg
id|new_object
op_logical_or
id|old_object-&gt;type
op_ne
id|OBJ_COMMIT
op_logical_or
id|new_object-&gt;type
op_ne
id|OBJ_COMMIT
)paren
(brace
id|error
c_func
(paren
l_string|&quot;bad sha1 objects for %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;bad ref&quot;
suffix:semicolon
)brace
id|old_commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|old_object
suffix:semicolon
id|new_commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|new_object
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
(brace
id|error
c_func
(paren
l_string|&quot;denying non-fast forward %s&quot;
l_string|&quot; (you should pull first)&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;non-fast forward&quot;
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|run_update_hook
c_func
(paren
id|cmd
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;hook declined to update %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;hook declined&quot;
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
op_logical_neg
id|parse_object
c_func
(paren
id|old_sha1
)paren
)paren
(brace
id|warning
(paren
l_string|&quot;Allowing deletion of corrupt ref.&quot;
)paren
suffix:semicolon
id|old_sha1
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|name
comma
id|old_sha1
comma
l_int|0
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;failed to delete %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;failed to delete&quot;
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* good */
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
(brace
id|error
c_func
(paren
l_string|&quot;failed to lock %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_string|&quot;failed to lock&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|new_sha1
comma
l_string|&quot;push&quot;
)paren
)paren
(brace
r_return
l_string|&quot;failed to write&quot;
suffix:semicolon
multiline_comment|/* error() already called */
)brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* good */
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
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
r_for
c_loop
(paren
id|argc
op_assign
l_int|0
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
r_if
c_cond
(paren
op_logical_neg
id|argc
op_logical_or
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
l_int|2
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
id|argv
comma
id|RUN_COMMAND_NO_STDIN
op_or
id|RUN_COMMAND_STDOUT_TO_STDERR
)paren
suffix:semicolon
)brace
DECL|function|execute_commands
r_static
r_void
id|execute_commands
c_func
(paren
r_const
r_char
op_star
id|unpacker_error
)paren
(brace
r_struct
id|command
op_star
id|cmd
op_assign
id|commands
suffix:semicolon
r_if
c_cond
(paren
id|unpacker_error
)paren
(brace
r_while
c_loop
(paren
id|cmd
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;n/a (unpacker error)&quot;
suffix:semicolon
id|cmd
op_assign
id|cmd-&gt;next
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|run_receive_hook
c_func
(paren
id|pre_receive_hook
)paren
)paren
(brace
r_while
c_loop
(paren
id|cmd
)paren
(brace
id|cmd-&gt;error_string
op_assign
l_string|&quot;pre-receive hook declined&quot;
suffix:semicolon
id|cmd
op_assign
id|cmd-&gt;next
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmd
)paren
(brace
id|cmd-&gt;error_string
op_assign
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
l_int|NULL
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
r_switch
c_cond
(paren
id|read_pack_header
c_func
(paren
l_int|0
comma
id|hdr
)paren
)paren
(brace
r_case
id|PH_ERROR_EOF
suffix:colon
r_return
l_string|&quot;eof before pack header was fully read&quot;
suffix:semicolon
r_case
id|PH_ERROR_PACK_SIGNATURE
suffix:colon
r_return
l_string|&quot;protocol error (pack signature mismatch detected)&quot;
suffix:semicolon
r_case
id|PH_ERROR_PROTOCOL
suffix:colon
r_return
l_string|&quot;protocol error (pack version unsupported)&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown error in parse_pack_header&quot;
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
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
l_string|&quot;--pack_header=%&quot;
id|PRIu32
l_string|&quot;,%&quot;
id|PRIu32
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
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|unpacker
(braket
l_int|4
)braket
suffix:semicolon
id|unpacker
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;unpack-objects&quot;
suffix:semicolon
r_if
c_cond
(paren
id|receive_fsck_objects
)paren
id|unpacker
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--strict&quot;
suffix:semicolon
id|unpacker
(braket
id|i
op_increment
)braket
op_assign
id|hdr_arg
suffix:semicolon
id|unpacker
(braket
id|i
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|code
op_assign
id|run_command_v_opt
c_func
(paren
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
l_int|7
)braket
suffix:semicolon
r_int
id|s
comma
id|status
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_char
id|keep_arg
(braket
l_int|256
)braket
suffix:semicolon
r_struct
id|child_process
id|ip
suffix:semicolon
id|s
op_assign
id|sprintf
c_func
(paren
id|keep_arg
comma
l_string|&quot;--keep=receive-pack %&quot;
id|PRIuMAX
l_string|&quot; on &quot;
comma
(paren
r_uintmax
)paren
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
id|i
op_increment
)braket
op_assign
l_string|&quot;index-pack&quot;
suffix:semicolon
id|keeper
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--stdin&quot;
suffix:semicolon
r_if
c_cond
(paren
id|receive_fsck_objects
)paren
id|keeper
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--strict&quot;
suffix:semicolon
id|keeper
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--fix-thin&quot;
suffix:semicolon
id|keeper
(braket
id|i
op_increment
)braket
op_assign
id|hdr_arg
suffix:semicolon
id|keeper
(braket
id|i
op_increment
)braket
op_assign
id|keep_arg
suffix:semicolon
id|keeper
(braket
id|i
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ip
comma
l_int|0
comma
r_sizeof
(paren
id|ip
)paren
)paren
suffix:semicolon
id|ip.argv
op_assign
id|keeper
suffix:semicolon
id|ip.out
op_assign
l_int|1
suffix:semicolon
id|ip.git_cmd
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
id|ip
)paren
)paren
r_return
l_string|&quot;index-pack fork failed&quot;
suffix:semicolon
id|pack_lockfile
op_assign
id|index_pack_lockfile
c_func
(paren
id|ip.out
)paren
suffix:semicolon
id|close
c_func
(paren
id|ip.out
)paren
suffix:semicolon
id|status
op_assign
id|finish_command
c_func
(paren
op_amp
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
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
DECL|function|add_refs_from_alternate
r_static
r_int
id|add_refs_from_alternate
c_func
(paren
r_struct
id|alternate_object_database
op_star
id|e
comma
r_void
op_star
id|unused
)paren
(brace
r_char
op_star
id|other
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|extra
suffix:semicolon
id|e-&gt;name
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|other
op_assign
id|xstrdup
c_func
(paren
id|make_absolute_path
c_func
(paren
id|e-&gt;base
)paren
)paren
suffix:semicolon
id|e-&gt;name
(braket
l_int|1
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|other
)paren
suffix:semicolon
r_while
c_loop
(paren
id|other
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|other
(braket
op_decrement
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|8
op_logical_or
id|memcmp
c_func
(paren
id|other
op_plus
id|len
l_int|8
comma
l_string|&quot;/objects&quot;
comma
l_int|8
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Is this a git repository with refs? */
id|memcpy
c_func
(paren
id|other
op_plus
id|len
l_int|8
comma
l_string|&quot;/refs&quot;
comma
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_directory
c_func
(paren
id|other
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|other
(braket
id|len
l_int|8
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|remote
op_assign
id|remote_get
c_func
(paren
id|other
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|other
)paren
suffix:semicolon
r_for
c_loop
(paren
id|extra
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
id|extra
suffix:semicolon
id|extra
op_assign
id|extra-&gt;next
)paren
(brace
id|add_extra_ref
c_func
(paren
l_string|&quot;.have&quot;
comma
id|extra-&gt;old_sha1
comma
l_int|0
)paren
suffix:semicolon
)brace
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
id|free
c_func
(paren
id|other
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_alternate_refs
r_static
r_void
id|add_alternate_refs
c_func
(paren
r_void
)paren
(brace
id|foreach_alt_odb
c_func
(paren
id|add_refs_from_alternate
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|cmd_receive_pack
r_int
id|cmd_receive_pack
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
r_const
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
id|xstrdup
c_func
(paren
id|arg
)paren
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
id|setup_path
c_func
(paren
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
r_if
c_cond
(paren
id|is_repository_shallow
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;attempt to push into a shallow repository&quot;
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|receive_pack_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|transfer_unpack_limit
)paren
id|unpack_limit
op_assign
id|transfer_unpack_limit
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0
op_le
id|receive_unpack_limit
)paren
id|unpack_limit
op_assign
id|receive_unpack_limit
suffix:semicolon
id|add_alternate_refs
c_func
(paren
)paren
suffix:semicolon
id|write_head_info
c_func
(paren
)paren
suffix:semicolon
id|clear_extra_refs
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
id|execute_commands
c_func
(paren
id|unpack_status
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
id|run_receive_hook
c_func
(paren
id|post_receive_hook
)paren
suffix:semicolon
id|run_update_post_hook
c_func
(paren
id|commands
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
