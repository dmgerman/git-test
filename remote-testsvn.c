macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;url.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;vcs-svn/svndump.h&quot;
macro_line|#include &quot;notes.h&quot;
macro_line|#include &quot;argv-array.h&quot;
DECL|variable|url
r_static
r_const
r_char
op_star
id|url
suffix:semicolon
DECL|variable|dump_from_file
r_static
r_int
id|dump_from_file
suffix:semicolon
DECL|variable|private_ref
r_static
r_const
r_char
op_star
id|private_ref
suffix:semicolon
DECL|variable|remote_ref
r_static
r_const
r_char
op_star
id|remote_ref
op_assign
l_string|&quot;refs/heads/master&quot;
suffix:semicolon
DECL|variable|marksfilename
DECL|variable|notes_ref
r_static
r_const
r_char
op_star
id|marksfilename
comma
op_star
id|notes_ref
suffix:semicolon
DECL|struct|rev_note
DECL|member|rev_nr
r_struct
id|rev_note
(brace
r_int
r_int
id|rev_nr
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|cmd_capabilities
c_func
(paren
r_const
r_char
op_star
id|line
)paren
suffix:semicolon
r_static
r_int
id|cmd_import
c_func
(paren
r_const
r_char
op_star
id|line
)paren
suffix:semicolon
r_static
r_int
id|cmd_list
c_func
(paren
r_const
r_char
op_star
id|line
)paren
suffix:semicolon
DECL|typedef|input_command_handler
r_typedef
r_int
(paren
op_star
id|input_command_handler
)paren
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|struct|input_command_entry
r_struct
id|input_command_entry
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|fn
id|input_command_handler
id|fn
suffix:semicolon
DECL|member|batchable
r_int
r_char
id|batchable
suffix:semicolon
multiline_comment|/* whether the command starts or is part of a batch */
)brace
suffix:semicolon
DECL|variable|input_command_list
r_static
r_const
r_struct
id|input_command_entry
id|input_command_list
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;capabilities&quot;
comma
id|cmd_capabilities
comma
l_int|0
)brace
comma
(brace
l_string|&quot;import&quot;
comma
id|cmd_import
comma
l_int|1
)brace
comma
(brace
l_string|&quot;list&quot;
comma
id|cmd_list
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|cmd_capabilities
r_static
r_int
id|cmd_capabilities
c_func
(paren
r_const
r_char
op_star
id|line
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;import&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;bidi-import&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;refspec %s:%s&bslash;n&bslash;n&quot;
comma
id|remote_ref
comma
id|private_ref
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|terminate_batch
r_static
r_void
id|terminate_batch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* terminate a current batch&squot;s fast-import stream */
id|printf
c_func
(paren
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
multiline_comment|/* NOTE: &squot;ref&squot; refers to a git reference, while &squot;rev&squot; refers to a svn revision. */
DECL|function|read_ref_note
r_static
r_char
op_star
id|read_ref_note
c_func
(paren
r_const
r_int
r_char
id|sha1
(braket
l_int|20
)braket
)paren
(brace
r_const
r_int
r_char
op_star
id|note_sha1
suffix:semicolon
r_char
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|msglen
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
id|init_notes
c_func
(paren
l_int|NULL
comma
id|notes_ref
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
(paren
id|note_sha1
op_assign
id|get_note
c_func
(paren
l_int|NULL
comma
id|sha1
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* note tree not found */
r_if
c_cond
(paren
op_logical_neg
(paren
id|msg
op_assign
id|read_sha1_file
c_func
(paren
id|note_sha1
comma
op_amp
id|type
comma
op_amp
id|msglen
)paren
)paren
)paren
id|error
c_func
(paren
l_string|&quot;Empty notes tree. %s&quot;
comma
id|notes_ref
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|msglen
op_logical_or
id|type
op_ne
id|OBJ_BLOB
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Note contains unusable content. &quot;
l_string|&quot;Is something else using this notes tree? %s&quot;
comma
id|notes_ref
)paren
suffix:semicolon
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
id|msg
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free_notes
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
id|msg
suffix:semicolon
)brace
DECL|function|parse_rev_note
r_static
r_int
id|parse_rev_note
c_func
(paren
r_const
r_char
op_star
id|msg
comma
r_struct
id|rev_note
op_star
id|res
)paren
(brace
r_const
r_char
op_star
id|key
comma
op_star
id|value
comma
op_star
id|end
suffix:semicolon
r_int
id|len
suffix:semicolon
r_while
c_loop
(paren
op_star
id|msg
)paren
(brace
id|end
op_assign
id|strchrnul
c_func
(paren
id|msg
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|len
op_assign
id|end
id|msg
suffix:semicolon
id|key
op_assign
l_string|&quot;Revision-number: &quot;
suffix:semicolon
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|msg
comma
id|key
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
id|value
op_assign
id|msg
op_plus
id|strlen
c_func
(paren
id|key
)paren
suffix:semicolon
id|i
op_assign
id|strtol
c_func
(paren
id|value
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|value
op_logical_or
id|i
template_param
id|UINT32_MAX
)paren
r_return
l_int|1
suffix:semicolon
id|res-&gt;rev_nr
op_assign
id|i
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|msg
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* didn&squot;t find it */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|note2mark_cb
r_static
r_int
id|note2mark_cb
c_func
(paren
r_const
r_int
r_char
op_star
id|object_sha1
comma
r_const
r_int
r_char
op_star
id|note_sha1
comma
r_char
op_star
id|note_path
comma
r_void
op_star
id|cb_data
)paren
(brace
id|FILE
op_star
id|file
op_assign
(paren
id|FILE
op_star
)paren
id|cb_data
suffix:semicolon
r_char
op_star
id|msg
suffix:semicolon
r_int
r_int
id|msglen
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_struct
id|rev_note
id|note
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|msg
op_assign
id|read_sha1_file
c_func
(paren
id|note_sha1
comma
op_amp
id|type
comma
op_amp
id|msglen
)paren
)paren
op_logical_or
op_logical_neg
id|msglen
op_logical_or
id|type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parse_rev_note
c_func
(paren
id|msg
comma
op_amp
id|note
)paren
)paren
r_return
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|fprintf
c_func
(paren
id|file
comma
l_string|&quot;:%d %s&bslash;n&quot;
comma
id|note.rev_nr
comma
id|sha1_to_hex
c_func
(paren
id|object_sha1
)paren
)paren
OL
l_int|1
)paren
r_return
l_int|3
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|regenerate_marks
r_static
r_void
id|regenerate_marks
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|FILE
op_star
id|marksfile
op_assign
id|fopen
c_func
(paren
id|marksfilename
comma
l_string|&quot;w+&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|marksfile
)paren
id|die_errno
c_func
(paren
l_string|&quot;Couldn&squot;t create mark file %s.&quot;
comma
id|marksfilename
)paren
suffix:semicolon
id|ret
op_assign
id|for_each_note
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|note2mark_cb
comma
id|marksfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;Regeneration of marks failed, returned %d.&quot;
comma
id|ret
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|marksfile
)paren
suffix:semicolon
)brace
DECL|function|check_or_regenerate_marks
r_static
r_void
id|check_or_regenerate_marks
c_func
(paren
r_int
id|latestrev
)paren
(brace
id|FILE
op_star
id|marksfile
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|line
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|latestrev
OL
l_int|1
)paren
r_return
suffix:semicolon
id|init_notes
c_func
(paren
l_int|NULL
comma
id|notes_ref
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|marksfile
op_assign
id|fopen
c_func
(paren
id|marksfilename
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|marksfile
)paren
(brace
id|regenerate_marks
c_func
(paren
)paren
suffix:semicolon
id|marksfile
op_assign
id|fopen
c_func
(paren
id|marksfilename
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|marksfile
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot read marks file %s!&quot;
comma
id|marksfilename
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|marksfile
)paren
suffix:semicolon
)brace
r_else
(brace
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;:%d &quot;
comma
id|latestrev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|line
comma
id|marksfile
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|line.buf
comma
id|sb.buf
)paren
)paren
(brace
id|found
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fclose
c_func
(paren
id|marksfile
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|regenerate_marks
c_func
(paren
)paren
suffix:semicolon
)brace
id|free_notes
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
)brace
DECL|function|cmd_import
r_static
r_int
id|cmd_import
c_func
(paren
r_const
r_char
op_star
id|line
)paren
(brace
r_int
id|code
suffix:semicolon
r_int
id|dumpin_fd
suffix:semicolon
r_char
op_star
id|note_msg
suffix:semicolon
r_int
r_char
id|head_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|startrev
suffix:semicolon
r_struct
id|argv_array
id|svndump_argv
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
r_struct
id|child_process
id|svndump_proc
suffix:semicolon
r_if
c_cond
(paren
id|read_ref
c_func
(paren
id|private_ref
comma
id|head_sha1
)paren
)paren
id|startrev
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|note_msg
op_assign
id|read_ref_note
c_func
(paren
id|head_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|note_msg
op_eq
l_int|NULL
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;No note found for %s.&quot;
comma
id|private_ref
)paren
suffix:semicolon
id|startrev
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_struct
id|rev_note
id|note
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
id|parse_rev_note
c_func
(paren
id|note_msg
comma
op_amp
id|note
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Revision number couldn&squot;t be parsed from note.&quot;
)paren
suffix:semicolon
id|startrev
op_assign
id|note.rev_nr
op_plus
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|note_msg
)paren
suffix:semicolon
)brace
)brace
id|check_or_regenerate_marks
c_func
(paren
id|startrev
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dump_from_file
)paren
(brace
id|dumpin_fd
op_assign
id|open
c_func
(paren
id|url
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dumpin_fd
OL
l_int|0
)paren
(brace
id|die_errno
c_func
(paren
l_string|&quot;Couldn&squot;t open svn dump file %s.&quot;
comma
id|url
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|memset
c_func
(paren
op_amp
id|svndump_proc
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|child_process
)paren
)paren
suffix:semicolon
id|svndump_proc.out
op_assign
l_int|1
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|svndump_argv
comma
l_string|&quot;svnrdump&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|svndump_argv
comma
l_string|&quot;dump&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|svndump_argv
comma
id|url
)paren
suffix:semicolon
id|argv_array_pushf
c_func
(paren
op_amp
id|svndump_argv
comma
l_string|&quot;-r%u:HEAD&quot;
comma
id|startrev
)paren
suffix:semicolon
id|svndump_proc.argv
op_assign
id|svndump_argv.argv
suffix:semicolon
id|code
op_assign
id|start_command
c_func
(paren
op_amp
id|svndump_proc
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
l_string|&quot;Unable to start %s, code %d&quot;
comma
id|svndump_proc.argv
(braket
l_int|0
)braket
comma
id|code
)paren
suffix:semicolon
id|dumpin_fd
op_assign
id|svndump_proc.out
suffix:semicolon
)brace
multiline_comment|/* setup marks file import/export */
id|printf
c_func
(paren
l_string|&quot;feature import-marks-if-exists=%s&bslash;n&quot;
l_string|&quot;feature export-marks=%s&bslash;n&quot;
comma
id|marksfilename
comma
id|marksfilename
)paren
suffix:semicolon
id|svndump_init_fd
c_func
(paren
id|dumpin_fd
comma
id|STDIN_FILENO
)paren
suffix:semicolon
id|svndump_read
c_func
(paren
id|url
comma
id|private_ref
comma
id|notes_ref
)paren
suffix:semicolon
id|svndump_deinit
c_func
(paren
)paren
suffix:semicolon
id|svndump_reset
c_func
(paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|dumpin_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dump_from_file
)paren
(brace
id|code
op_assign
id|finish_command
c_func
(paren
op_amp
id|svndump_proc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
id|warning
c_func
(paren
l_string|&quot;%s, returned %d&quot;
comma
id|svndump_proc.argv
(braket
l_int|0
)braket
comma
id|code
)paren
suffix:semicolon
id|argv_array_clear
c_func
(paren
op_amp
id|svndump_argv
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_list
r_static
r_int
id|cmd_list
c_func
(paren
r_const
r_char
op_star
id|line
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;? %s&bslash;n&bslash;n&quot;
comma
id|remote_ref
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_command
r_static
r_int
id|do_command
c_func
(paren
r_struct
id|strbuf
op_star
id|line
)paren
(brace
r_const
r_struct
id|input_command_entry
op_star
id|p
op_assign
id|input_command_list
suffix:semicolon
r_static
r_struct
id|string_list
id|batchlines
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_static
r_const
r_struct
id|input_command_entry
op_star
id|batch_cmd
suffix:semicolon
multiline_comment|/*&n;&t; * commands can be grouped together in a batch.&n;&t; * Batches are ended by &bslash;n. If no batch is active the program ends.&n;&t; * During a batch all lines are buffered and passed to the handler function&n;&t; * when the batch is terminated.&n;&t; */
r_if
c_cond
(paren
id|line-&gt;len
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|batch_cmd
)paren
(brace
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|batchlines
)paren
id|batch_cmd
op_member_access_from_pointer
id|fn
c_func
(paren
id|item-&gt;string
)paren
suffix:semicolon
id|terminate_batch
c_func
(paren
)paren
suffix:semicolon
id|batch_cmd
op_assign
l_int|NULL
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|batchlines
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* end of the batch, continue reading other commands. */
)brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* end of command stream, quit */
)brace
r_if
c_cond
(paren
id|batch_cmd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|starts_with
c_func
(paren
id|batch_cmd-&gt;name
comma
id|line-&gt;buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Active %s batch interrupted by %s&quot;
comma
id|batch_cmd-&gt;name
comma
id|line-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* buffer batch lines */
id|string_list_append
c_func
(paren
op_amp
id|batchlines
comma
id|line-&gt;buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|input_command_list
suffix:semicolon
id|p-&gt;name
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|line-&gt;buf
comma
id|p-&gt;name
)paren
op_logical_and
(paren
id|strlen
c_func
(paren
id|p-&gt;name
)paren
op_eq
id|line-&gt;len
op_logical_or
id|line-&gt;buf
(braket
id|strlen
c_func
(paren
id|p-&gt;name
)paren
)braket
op_eq
l_char|&squot; &squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;batchable
)paren
(brace
id|batch_cmd
op_assign
id|p
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|batchlines
comma
id|line-&gt;buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|p
op_member_access_from_pointer
id|fn
c_func
(paren
id|line-&gt;buf
)paren
suffix:semicolon
)brace
)brace
id|die
c_func
(paren
l_string|&quot;Unknown command &squot;%s&squot;&bslash;n&quot;
comma
id|line-&gt;buf
)paren
suffix:semicolon
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
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
comma
id|url_sb
op_assign
id|STRBUF_INIT
comma
id|private_ref_sb
op_assign
id|STRBUF_INIT
comma
id|marksfilename_sb
op_assign
id|STRBUF_INIT
comma
id|notes_ref_sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_static
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_const
r_char
op_star
id|url_in
suffix:semicolon
id|git_extract_argv0_path
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|3
)paren
(brace
id|usage
c_func
(paren
l_string|&quot;git-remote-svn &lt;remote-name&gt; [&lt;url&gt;]&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|remote
op_assign
id|remote_get
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|url_in
op_assign
(paren
id|argc
op_eq
l_int|3
)paren
ques
c_cond
id|argv
(braket
l_int|2
)braket
suffix:colon
id|remote-&gt;url
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|url_in
comma
l_string|&quot;file://&quot;
)paren
)paren
(brace
id|dump_from_file
op_assign
l_int|1
suffix:semicolon
id|url
op_assign
id|url_decode
c_func
(paren
id|url_in
op_plus
r_sizeof
(paren
l_string|&quot;file://&quot;
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|dump_from_file
op_assign
l_int|0
suffix:semicolon
id|end_url_with_slash
c_func
(paren
op_amp
id|url_sb
comma
id|url_in
)paren
suffix:semicolon
id|url
op_assign
id|url_sb.buf
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|private_ref_sb
comma
l_string|&quot;refs/svn/%s/master&quot;
comma
id|remote-&gt;name
)paren
suffix:semicolon
id|private_ref
op_assign
id|private_ref_sb.buf
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|notes_ref_sb
comma
l_string|&quot;refs/notes/%s/revs&quot;
comma
id|remote-&gt;name
)paren
suffix:semicolon
id|notes_ref
op_assign
id|notes_ref_sb.buf
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|marksfilename_sb
comma
l_string|&quot;%s/info/fast-import/remote-svn/%s.marks&quot;
comma
id|get_git_dir
c_func
(paren
)paren
comma
id|remote-&gt;name
)paren
suffix:semicolon
id|marksfilename
op_assign
id|marksfilename_sb.buf
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
(brace
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|stdin
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Error reading command stream&quot;
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;Unexpected end of command stream&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_command
c_func
(paren
op_amp
id|buf
)paren
)paren
r_break
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf
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
id|strbuf_release
c_func
(paren
op_amp
id|url_sb
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|private_ref_sb
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|notes_ref_sb
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|marksfilename_sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
