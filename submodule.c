macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;submodule.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;diffcore.h&quot;
DECL|function|add_submodule_odb
r_static
r_int
id|add_submodule_odb
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|strbuf
id|objects_directory
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|alternate_object_database
op_star
id|alt_odb
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|objects_directory
comma
l_string|&quot;%s/.git/objects/&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_directory
c_func
(paren
id|objects_directory.buf
)paren
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* avoid adding it twice */
r_for
c_loop
(paren
id|alt_odb
op_assign
id|alt_odb_list
suffix:semicolon
id|alt_odb
suffix:semicolon
id|alt_odb
op_assign
id|alt_odb-&gt;next
)paren
r_if
c_cond
(paren
id|alt_odb-&gt;name
id|alt_odb-&gt;base
op_eq
id|objects_directory.len
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|alt_odb-&gt;base
comma
id|objects_directory.buf
comma
id|objects_directory.len
)paren
)paren
r_goto
id|done
suffix:semicolon
id|alt_odb
op_assign
id|xmalloc
c_func
(paren
id|objects_directory.len
op_plus
l_int|42
op_plus
r_sizeof
(paren
op_star
id|alt_odb
)paren
)paren
suffix:semicolon
id|alt_odb-&gt;next
op_assign
id|alt_odb_list
suffix:semicolon
id|strcpy
c_func
(paren
id|alt_odb-&gt;base
comma
id|objects_directory.buf
)paren
suffix:semicolon
id|alt_odb-&gt;name
op_assign
id|alt_odb-&gt;base
op_plus
id|objects_directory.len
suffix:semicolon
id|alt_odb-&gt;name
(braket
l_int|2
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|alt_odb-&gt;name
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|alt_odb-&gt;name
(braket
l_int|41
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|alt_odb_list
op_assign
id|alt_odb
suffix:semicolon
id|prepare_alt_odb
c_func
(paren
)paren
suffix:semicolon
id|done
suffix:colon
id|strbuf_release
c_func
(paren
op_amp
id|objects_directory
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|show_submodule_summary
r_void
id|show_submodule_summary
c_func
(paren
id|FILE
op_star
id|f
comma
r_const
r_char
op_star
id|path
comma
r_int
r_char
id|one
(braket
l_int|20
)braket
comma
r_int
r_char
id|two
(braket
l_int|20
)braket
comma
r_int
id|dirty_submodule
comma
r_const
r_char
op_star
id|del
comma
r_const
r_char
op_star
id|add
comma
r_const
r_char
op_star
id|reset
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
r_struct
id|commit
op_star
id|commit
comma
op_star
id|left
op_assign
id|left
comma
op_star
id|right
op_assign
id|right
suffix:semicolon
r_struct
id|commit_list
op_star
id|merge_bases
comma
op_star
id|list
suffix:semicolon
r_const
r_char
op_star
id|message
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_static
r_const
r_char
op_star
id|format
op_assign
l_string|&quot;  %m %s&quot;
suffix:semicolon
r_int
id|fast_forward
op_assign
l_int|0
comma
id|fast_backward
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|two
)paren
)paren
id|message
op_assign
l_string|&quot;(submodule deleted)&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|add_submodule_odb
c_func
(paren
id|path
)paren
)paren
id|message
op_assign
l_string|&quot;(not checked out)&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|one
)paren
)paren
id|message
op_assign
l_string|&quot;(new submodule)&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|left
op_assign
id|lookup_commit_reference
c_func
(paren
id|one
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|right
op_assign
id|lookup_commit_reference
c_func
(paren
id|two
)paren
)paren
)paren
id|message
op_assign
l_string|&quot;(commits not present)&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|message
)paren
(brace
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|rev.left_right
op_assign
l_int|1
suffix:semicolon
id|rev.first_parent_only
op_assign
l_int|1
suffix:semicolon
id|left-&gt;object.flags
op_or_assign
id|SYMMETRIC_LEFT
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|rev
comma
op_amp
id|left-&gt;object
comma
id|path
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|rev
comma
op_amp
id|right-&gt;object
comma
id|path
)paren
suffix:semicolon
id|merge_bases
op_assign
id|get_merge_bases
c_func
(paren
id|left
comma
id|right
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|merge_bases
)paren
(brace
r_if
c_cond
(paren
id|merge_bases-&gt;item
op_eq
id|left
)paren
id|fast_forward
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|merge_bases-&gt;item
op_eq
id|right
)paren
id|fast_backward
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|list
op_assign
id|merge_bases
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
id|list-&gt;item-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|rev
comma
op_amp
id|list-&gt;item-&gt;object
comma
id|sha1_to_hex
c_func
(paren
id|list-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
op_amp
id|rev
)paren
)paren
id|message
op_assign
l_string|&quot;(revision walker failed)&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dirty_submodule
op_amp
id|DIRTY_SUBMODULE_UNTRACKED
)paren
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;Submodule %s contains untracked content&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dirty_submodule
op_amp
id|DIRTY_SUBMODULE_MODIFIED
)paren
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;Submodule %s contains modified content&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|one
comma
id|two
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;Submodule %s %s..&quot;
comma
id|path
comma
id|find_unique_abbrev
c_func
(paren
id|one
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fast_backward
op_logical_and
op_logical_neg
id|fast_forward
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s&quot;
comma
id|find_unique_abbrev
c_func
(paren
id|two
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot; %s&bslash;n&quot;
comma
id|message
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s:&bslash;n&quot;
comma
id|fast_backward
ques
c_cond
l_string|&quot; (rewind)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|sb.buf
comma
id|sb.len
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|message
)paren
(brace
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
op_amp
id|rev
)paren
)paren
)paren
(brace
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|ctx.date_mode
op_assign
id|rev.date_mode
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|sb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|SYMMETRIC_LEFT
)paren
(brace
r_if
c_cond
(paren
id|del
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|del
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|add
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|add
)paren
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
id|format
comma
op_amp
id|sb
comma
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|reset
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;%s&quot;
comma
id|sb.buf
)paren
suffix:semicolon
)brace
id|clear_commit_marks
c_func
(paren
id|left
comma
op_complement
l_int|0
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|right
comma
op_complement
l_int|0
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
DECL|function|is_submodule_modified
r_int
id|is_submodule_modified
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|i
suffix:semicolon
id|ssize_t
id|len
suffix:semicolon
r_struct
id|child_process
id|cp
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;status&quot;
comma
l_string|&quot;--porcelain&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_const
r_char
op_star
id|env
(braket
id|LOCAL_REPO_ENV_SIZE
op_plus
l_int|3
)braket
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|dirty_submodule
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|line
comma
op_star
id|next_line
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
id|LOCAL_REPO_ENV_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|env
(braket
id|i
)braket
op_assign
id|local_repo_env
(braket
id|i
)braket
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%s/.git/&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_directory
c_func
(paren
id|buf.buf
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
multiline_comment|/* The submodule is not checked out, so it is not modified */
r_return
l_int|0
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
l_string|&quot;GIT_WORK_TREE=%s&quot;
comma
id|path
)paren
suffix:semicolon
id|env
(braket
id|i
op_increment
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;GIT_DIR=%s/.git&quot;
comma
id|path
)paren
suffix:semicolon
id|env
(braket
id|i
op_increment
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|env
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cp
comma
l_int|0
comma
r_sizeof
(paren
id|cp
)paren
)paren
suffix:semicolon
id|cp.argv
op_assign
id|argv
suffix:semicolon
id|cp.env
op_assign
id|env
suffix:semicolon
id|cp.git_cmd
op_assign
l_int|1
suffix:semicolon
id|cp.no_stdin
op_assign
l_int|1
suffix:semicolon
id|cp.out
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
id|cp
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not run git status --porcelain&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strbuf_read
c_func
(paren
op_amp
id|buf
comma
id|cp.out
comma
l_int|1024
)paren
suffix:semicolon
id|line
op_assign
id|buf.buf
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;?&squot;
)paren
op_logical_and
(paren
id|line
(braket
l_int|1
)braket
op_eq
l_char|&squot;?&squot;
)paren
)paren
(brace
id|dirty_submodule
op_or_assign
id|DIRTY_SUBMODULE_UNTRACKED
suffix:semicolon
r_if
c_cond
(paren
id|dirty_submodule
op_amp
id|DIRTY_SUBMODULE_MODIFIED
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
id|dirty_submodule
op_or_assign
id|DIRTY_SUBMODULE_MODIFIED
suffix:semicolon
r_if
c_cond
(paren
id|dirty_submodule
op_amp
id|DIRTY_SUBMODULE_UNTRACKED
)paren
r_break
suffix:semicolon
)brace
id|next_line
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_line
)paren
r_break
suffix:semicolon
id|next_line
op_increment
suffix:semicolon
id|len
op_sub_assign
(paren
id|next_line
id|line
)paren
suffix:semicolon
id|line
op_assign
id|next_line
suffix:semicolon
)brace
id|close
c_func
(paren
id|cp.out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|cp
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git status --porcelain failed&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|LOCAL_REPO_ENV_SIZE
suffix:semicolon
id|env
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|env
(braket
id|i
)braket
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|dirty_submodule
suffix:semicolon
)brace
eof
