macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;argv-array.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;sigchain.h&quot;
DECL|variable|worktree_usage
r_static
r_const
r_char
op_star
r_const
id|worktree_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git worktree add [&lt;options&gt;] &lt;path&gt; &lt;branch&gt;&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git worktree prune [&lt;options&gt;]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|show_only
r_static
r_int
id|show_only
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|variable|expire
r_static
r_int
r_int
id|expire
suffix:semicolon
DECL|function|prune_worktree
r_static
r_int
id|prune_worktree
c_func
(paren
r_const
r_char
op_star
id|id
comma
r_struct
id|strbuf
op_star
id|reason
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
id|fd
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_directory
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees/%s&quot;
comma
id|id
)paren
)paren
)paren
(brace
id|strbuf_addf
c_func
(paren
id|reason
comma
id|_
c_func
(paren
l_string|&quot;Removing worktrees/%s: not a valid directory&quot;
)paren
comma
id|id
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file_exists
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees/%s/locked&quot;
comma
id|id
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees/%s/gitdir&quot;
comma
id|id
)paren
comma
op_amp
id|st
)paren
)paren
(brace
id|strbuf_addf
c_func
(paren
id|reason
comma
id|_
c_func
(paren
l_string|&quot;Removing worktrees/%s: gitdir file does not exist&quot;
)paren
comma
id|id
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fd
op_assign
id|open
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees/%s/gitdir&quot;
comma
id|id
)paren
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
(brace
id|strbuf_addf
c_func
(paren
id|reason
comma
id|_
c_func
(paren
l_string|&quot;Removing worktrees/%s: unable to read gitdir file (%s)&quot;
)paren
comma
id|id
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|len
op_assign
id|st.st_size
suffix:semicolon
id|path
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|read_in_full
c_func
(paren
id|fd
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
(paren
id|path
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|path
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
id|strbuf_addf
c_func
(paren
id|reason
comma
id|_
c_func
(paren
l_string|&quot;Removing worktrees/%s: invalid gitdir file&quot;
)paren
comma
id|id
)paren
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|path
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|path
)paren
)paren
(brace
r_struct
id|stat
id|st_link
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * the repo is moved manually and has not been&n;&t;&t; * accessed since?&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees/%s/link&quot;
comma
id|id
)paren
comma
op_amp
id|st_link
)paren
op_logical_and
id|st_link.st_nlink
OG
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|st.st_mtime
op_le
id|expire
)paren
(brace
id|strbuf_addf
c_func
(paren
id|reason
comma
id|_
c_func
(paren
l_string|&quot;Removing worktrees/%s: gitdir file points to non-existent location&quot;
)paren
comma
id|id
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_worktrees
r_static
r_void
id|prune_worktrees
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|reason
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|path
op_assign
id|STRBUF_INIT
suffix:semicolon
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees&quot;
)paren
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|d
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|d
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|d-&gt;d_name
comma
l_string|&quot;.&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|d-&gt;d_name
comma
l_string|&quot;..&quot;
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|reason
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prune_worktree
c_func
(paren
id|d-&gt;d_name
comma
op_amp
id|reason
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|show_only
op_logical_or
id|verbose
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|reason.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_only
)paren
r_continue
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|path
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|path
comma
id|git_path
c_func
(paren
l_string|&quot;worktrees/%s&quot;
comma
id|d-&gt;d_name
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|remove_dir_recursively
c_func
(paren
op_amp
id|path
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
op_logical_and
id|errno
op_eq
id|ENOTDIR
)paren
id|ret
op_assign
id|unlink
c_func
(paren
id|path.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;failed to remove: %s&quot;
)paren
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
)paren
id|rmdir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;worktrees&quot;
)paren
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|reason
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|path
)paren
suffix:semicolon
)brace
DECL|function|prune
r_static
r_int
id|prune
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|show_only
comma
id|N_
c_func
(paren
l_string|&quot;do not remove, show only&quot;
)paren
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
comma
id|N_
c_func
(paren
l_string|&quot;report pruned objects&quot;
)paren
)paren
comma
id|OPT_EXPIRY_DATE
c_func
(paren
l_int|0
comma
l_string|&quot;expire&quot;
comma
op_amp
id|expire
comma
id|N_
c_func
(paren
l_string|&quot;expire objects older than &lt;time&gt;&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|expire
op_assign
id|ULONG_MAX
suffix:semicolon
id|ac
op_assign
id|parse_options
c_func
(paren
id|ac
comma
id|av
comma
id|prefix
comma
id|options
comma
id|worktree_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac
)paren
id|usage_with_options
c_func
(paren
id|worktree_usage
comma
id|options
)paren
suffix:semicolon
id|prune_worktrees
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|junk_work_tree
r_static
r_char
op_star
id|junk_work_tree
suffix:semicolon
DECL|variable|junk_git_dir
r_static
r_char
op_star
id|junk_git_dir
suffix:semicolon
DECL|variable|is_junk
r_static
r_int
id|is_junk
suffix:semicolon
DECL|variable|junk_pid
r_static
id|pid_t
id|junk_pid
suffix:semicolon
DECL|function|remove_junk
r_static
r_void
id|remove_junk
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_junk
op_logical_or
id|getpid
c_func
(paren
)paren
op_ne
id|junk_pid
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|junk_git_dir
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|junk_git_dir
)paren
suffix:semicolon
id|remove_dir_recursively
c_func
(paren
op_amp
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|junk_work_tree
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|junk_work_tree
)paren
suffix:semicolon
id|remove_dir_recursively
c_func
(paren
op_amp
id|sb
comma
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
DECL|function|remove_junk_on_signal
r_static
r_void
id|remove_junk_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_junk
c_func
(paren
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|signo
)paren
suffix:semicolon
id|raise
c_func
(paren
id|signo
)paren
suffix:semicolon
)brace
DECL|function|worktree_basename
r_static
r_const
r_char
op_star
id|worktree_basename
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
op_star
id|olen
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|is_dir_sep
c_func
(paren
id|path
(braket
id|len
l_int|1
)braket
)paren
)paren
id|len
op_decrement
suffix:semicolon
r_for
c_loop
(paren
id|name
op_assign
id|path
op_plus
id|len
l_int|1
suffix:semicolon
id|name
OG
id|path
suffix:semicolon
id|name
op_decrement
)paren
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
op_star
id|name
)paren
)paren
(brace
id|name
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|olen
op_assign
id|len
suffix:semicolon
r_return
id|name
suffix:semicolon
)brace
DECL|function|add_worktree
r_static
r_int
id|add_worktree
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
op_star
id|child_argv
)paren
(brace
r_struct
id|strbuf
id|sb_git
op_assign
id|STRBUF_INIT
comma
id|sb_repo
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_struct
id|child_process
id|cp
suffix:semicolon
r_int
id|counter
op_assign
l_int|0
comma
id|len
comma
id|ret
suffix:semicolon
r_int
r_char
id|rev
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|file_exists
c_func
(paren
id|path
)paren
op_logical_and
op_logical_neg
id|is_empty_dir
c_func
(paren
id|path
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;&squot;%s&squot; already exists&quot;
)paren
comma
id|path
)paren
suffix:semicolon
id|name
op_assign
id|worktree_basename
c_func
(paren
id|path
comma
op_amp
id|len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|sb_repo
comma
id|git_path
c_func
(paren
l_string|&quot;worktrees/%.*s&quot;
comma
(paren
r_int
)paren
(paren
id|path
op_plus
id|len
id|name
)paren
comma
id|name
)paren
)paren
suffix:semicolon
id|len
op_assign
id|sb_repo.len
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories_const
c_func
(paren
id|sb_repo.buf
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not create leading directories of &squot;%s&squot;&quot;
)paren
comma
id|sb_repo.buf
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|stat
c_func
(paren
id|sb_repo.buf
comma
op_amp
id|st
)paren
)paren
(brace
id|counter
op_increment
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|sb_repo
comma
id|len
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb_repo
comma
l_string|&quot;%d&quot;
comma
id|counter
)paren
suffix:semicolon
)brace
id|name
op_assign
id|strrchr
c_func
(paren
id|sb_repo.buf
comma
l_char|&squot;/&squot;
)paren
op_plus
l_int|1
suffix:semicolon
id|junk_pid
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_junk
)paren
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|remove_junk_on_signal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|sb_repo.buf
comma
l_int|0777
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not create directory of &squot;%s&squot;&quot;
)paren
comma
id|sb_repo.buf
)paren
suffix:semicolon
id|junk_git_dir
op_assign
id|xstrdup
c_func
(paren
id|sb_repo.buf
)paren
suffix:semicolon
id|is_junk
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * lock the incomplete repo so prune won&squot;t delete it, unlock&n;&t; * after the preparation is over.&n;&t; */
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s/locked&quot;
comma
id|sb_repo.buf
)paren
suffix:semicolon
id|write_file
c_func
(paren
id|sb.buf
comma
l_int|1
comma
l_string|&quot;initializing&bslash;n&quot;
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb_git
comma
l_string|&quot;%s/.git&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories_const
c_func
(paren
id|sb_git.buf
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not create leading directories of &squot;%s&squot;&quot;
)paren
comma
id|sb_git.buf
)paren
suffix:semicolon
id|junk_work_tree
op_assign
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s/gitdir&quot;
comma
id|sb_repo.buf
)paren
suffix:semicolon
id|write_file
c_func
(paren
id|sb.buf
comma
l_int|1
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|real_path
c_func
(paren
id|sb_git.buf
)paren
)paren
suffix:semicolon
id|write_file
c_func
(paren
id|sb_git.buf
comma
l_int|1
comma
l_string|&quot;gitdir: %s/worktrees/%s&bslash;n&quot;
comma
id|real_path
c_func
(paren
id|get_git_common_dir
c_func
(paren
)paren
)paren
comma
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is to keep resolve_ref() happy. We need a valid HEAD&n;&t; * or is_git_directory() will reject the directory. Moreover, HEAD&n;&t; * in the new worktree must resolve to the same value as HEAD in&n;&t; * the current tree since the command invoked to populate the new&n;&t; * worktree will be handed the branch/ref specified by the user.&n;&t; * For instance, if the user asks for the new worktree to be based&n;&t; * at HEAD~5, then the resolved HEAD~5 in the new worktree must&n;&t; * match the resolved HEAD~5 in the current tree in order to match&n;&t; * the user&squot;s expectation.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref_unsafe
c_func
(paren
l_string|&quot;HEAD&quot;
comma
l_int|0
comma
id|rev
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to resolve HEAD&quot;
)paren
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s/HEAD&quot;
comma
id|sb_repo.buf
)paren
suffix:semicolon
id|write_file
c_func
(paren
id|sb.buf
comma
l_int|1
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|rev
)paren
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s/commondir&quot;
comma
id|sb_repo.buf
)paren
suffix:semicolon
id|write_file
c_func
(paren
id|sb.buf
comma
l_int|1
comma
l_string|&quot;../..&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;Enter %s (identifier %s)&quot;
)paren
comma
id|path
comma
id|name
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;GIT_CHECKOUT_NEW_WORKTREE&quot;
comma
l_string|&quot;1&quot;
comma
l_int|1
)paren
suffix:semicolon
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
id|sb_git.buf
comma
l_int|1
)paren
suffix:semicolon
id|setenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
comma
id|path
comma
l_int|1
)paren
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
id|cp.git_cmd
op_assign
l_int|1
suffix:semicolon
id|cp.argv
op_assign
id|child_argv
suffix:semicolon
id|ret
op_assign
id|run_command
c_func
(paren
op_amp
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|is_junk
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|junk_work_tree
)paren
suffix:semicolon
id|free
c_func
(paren
id|junk_git_dir
)paren
suffix:semicolon
id|junk_work_tree
op_assign
l_int|NULL
suffix:semicolon
id|junk_git_dir
op_assign
l_int|NULL
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s/locked&quot;
comma
id|sb_repo.buf
)paren
suffix:semicolon
id|unlink_or_warn
c_func
(paren
id|sb.buf
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
id|sb_repo
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb_git
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|add
r_static
r_int
id|add
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|force
op_assign
l_int|0
comma
id|detach
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|new_branch
op_assign
l_int|NULL
comma
op_star
id|new_branch_force
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|path
comma
op_star
id|branch
suffix:semicolon
r_struct
id|argv_array
id|cmd
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__FORCE
c_func
(paren
op_amp
id|force
comma
id|N_
c_func
(paren
l_string|&quot;checkout &lt;branch&gt; even if already checked out in other worktree&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;b&squot;
comma
l_int|NULL
comma
op_amp
id|new_branch
comma
id|N_
c_func
(paren
l_string|&quot;branch&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;create a new branch&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;B&squot;
comma
l_int|NULL
comma
op_amp
id|new_branch_force
comma
id|N_
c_func
(paren
l_string|&quot;branch&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;create or reset a branch&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;detach&quot;
comma
op_amp
id|detach
comma
id|N_
c_func
(paren
l_string|&quot;detach HEAD at named commit&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|ac
op_assign
id|parse_options
c_func
(paren
id|ac
comma
id|av
comma
id|prefix
comma
id|options
comma
id|worktree_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_branch
op_logical_and
id|new_branch_force
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;-b and -B are mutually exclusive&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac
op_ne
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|worktree_usage
comma
id|options
)paren
suffix:semicolon
id|path
op_assign
id|prefix
ques
c_cond
id|prefix_filename
c_func
(paren
id|prefix
comma
id|strlen
c_func
(paren
id|prefix
)paren
comma
id|av
(braket
l_int|0
)braket
)paren
suffix:colon
id|av
(braket
l_int|0
)braket
suffix:semicolon
id|branch
op_assign
id|av
(braket
l_int|1
)braket
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot;checkout&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
id|argv_array_push
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot;--ignore-other-worktrees&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_branch
)paren
id|argv_array_pushl
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot;-b&quot;
comma
id|new_branch
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_branch_force
)paren
id|argv_array_pushl
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot;-B&quot;
comma
id|new_branch_force
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|detach
)paren
id|argv_array_push
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot;--detach&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd
comma
id|branch
)paren
suffix:semicolon
r_return
id|add_worktree
c_func
(paren
id|path
comma
id|cmd.argv
)paren
suffix:semicolon
)brace
DECL|function|cmd_worktree
r_int
id|cmd_worktree
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
id|ac
OL
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|worktree_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_string|&quot;add&quot;
)paren
)paren
r_return
id|add
c_func
(paren
id|ac
l_int|1
comma
id|av
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_string|&quot;prune&quot;
)paren
)paren
r_return
id|prune
c_func
(paren
id|ac
l_int|1
comma
id|av
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|worktree_usage
comma
id|options
)paren
suffix:semicolon
)brace
eof
