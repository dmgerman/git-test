multiline_comment|/*&n; * &quot;git add&quot; builtin command&n; *&n; * Copyright (C) 2006 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|builtin_add_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_add_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git-add [options] [--] &lt;filepattern&gt;...&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|take_worktree_changes
r_static
r_int
id|take_worktree_changes
suffix:semicolon
DECL|variable|excludes_file
r_static
r_const
r_char
op_star
id|excludes_file
suffix:semicolon
DECL|function|prune_directory
r_static
r_void
id|prune_directory
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_const
r_char
op_star
op_star
id|pathspec
comma
r_int
id|prefix
)paren
(brace
r_char
op_star
id|seen
suffix:semicolon
r_int
id|i
comma
id|specs
suffix:semicolon
r_struct
id|dir_entry
op_star
op_star
id|src
comma
op_star
op_star
id|dst
suffix:semicolon
r_for
c_loop
(paren
id|specs
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|specs
)braket
suffix:semicolon
id|specs
op_increment
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|seen
op_assign
id|xcalloc
c_func
(paren
id|specs
comma
l_int|1
)paren
suffix:semicolon
id|src
op_assign
id|dst
op_assign
id|dir-&gt;entries
suffix:semicolon
id|i
op_assign
id|dir-&gt;nr
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
(brace
r_struct
id|dir_entry
op_star
id|entry
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|match_pathspec
c_func
(paren
id|pathspec
comma
id|entry-&gt;name
comma
id|entry-&gt;len
comma
id|prefix
comma
id|seen
)paren
)paren
op_star
id|dst
op_increment
op_assign
id|entry
suffix:semicolon
)brace
id|dir-&gt;nr
op_assign
id|dst
id|dir-&gt;entries
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
id|specs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
op_logical_and
op_logical_neg
id|file_exists
c_func
(paren
id|pathspec
(braket
id|i
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
comma
id|pathspec
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|seen
)paren
suffix:semicolon
)brace
DECL|function|fill_directory
r_static
r_void
id|fill_directory
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_const
r_char
op_star
op_star
id|pathspec
comma
r_int
id|ignored_too
)paren
(brace
r_const
r_char
op_star
id|path
comma
op_star
id|base
suffix:semicolon
r_int
id|baselen
suffix:semicolon
multiline_comment|/* Set up the default git porcelain excludes */
id|memset
c_func
(paren
id|dir
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ignored_too
)paren
(brace
id|dir-&gt;collect_ignored
op_assign
l_int|1
suffix:semicolon
id|dir-&gt;exclude_per_dir
op_assign
l_string|&quot;.gitignore&quot;
suffix:semicolon
id|path
op_assign
id|git_path
c_func
(paren
l_string|&quot;info/exclude&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|path
comma
id|R_OK
)paren
)paren
id|add_excludes_from_file
c_func
(paren
id|dir
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|excludes_file
op_ne
l_int|NULL
op_logical_and
op_logical_neg
id|access
c_func
(paren
id|excludes_file
comma
id|R_OK
)paren
)paren
id|add_excludes_from_file
c_func
(paren
id|dir
comma
id|excludes_file
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Calculate common prefix for the pathspec, and&n;&t; * use that to optimize the directory walk&n;&t; */
id|baselen
op_assign
id|common_prefix
c_func
(paren
id|pathspec
)paren
suffix:semicolon
id|path
op_assign
l_string|&quot;.&quot;
suffix:semicolon
id|base
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|baselen
)paren
id|path
op_assign
id|base
op_assign
id|xmemdupz
c_func
(paren
op_star
id|pathspec
comma
id|baselen
)paren
suffix:semicolon
multiline_comment|/* Read the directory and prune it */
id|read_directory
c_func
(paren
id|dir
comma
id|path
comma
id|base
comma
id|baselen
comma
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
)paren
id|prune_directory
c_func
(paren
id|dir
comma
id|pathspec
comma
id|baselen
)paren
suffix:semicolon
)brace
DECL|function|update_callback
r_static
r_void
id|update_callback
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_options
op_star
id|opt
comma
r_void
op_star
id|cbdata
)paren
(brace
r_int
id|i
comma
id|verbose
suffix:semicolon
id|verbose
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|cbdata
)paren
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
id|p-&gt;one-&gt;path
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;status
)paren
(brace
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;unexpected diff status %c&quot;
comma
id|p-&gt;status
)paren
suffix:semicolon
r_case
id|DIFF_STATUS_UNMERGED
suffix:colon
r_case
id|DIFF_STATUS_MODIFIED
suffix:colon
r_case
id|DIFF_STATUS_TYPE_CHANGED
suffix:colon
id|add_file_to_cache
c_func
(paren
id|path
comma
id|verbose
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_DELETED
suffix:colon
id|remove_file_from_cache
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|printf
c_func
(paren
l_string|&quot;remove &squot;%s&squot;&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|add_files_to_cache
r_void
id|add_files_to_cache
c_func
(paren
r_int
id|verbose
comma
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
op_star
id|files
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
id|prefix
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
id|rev.prune_data
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|files
)paren
suffix:semicolon
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_CALLBACK
suffix:semicolon
id|rev.diffopt.format_callback
op_assign
id|update_callback
suffix:semicolon
id|rev.diffopt.format_callback_data
op_assign
op_amp
id|verbose
suffix:semicolon
id|run_diff_files
c_func
(paren
op_amp
id|rev
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|refresh
r_static
r_void
id|refresh
c_func
(paren
r_int
id|verbose
comma
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_char
op_star
id|seen
suffix:semicolon
r_int
id|i
comma
id|specs
suffix:semicolon
r_for
c_loop
(paren
id|specs
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|specs
)braket
suffix:semicolon
id|specs
op_increment
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|seen
op_assign
id|xcalloc
c_func
(paren
id|specs
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
suffix:semicolon
id|refresh_index
c_func
(paren
op_amp
id|the_index
comma
id|verbose
ques
c_cond
l_int|0
suffix:colon
id|REFRESH_QUIET
comma
id|pathspec
comma
id|seen
)paren
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
id|specs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
)paren
id|die
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
comma
id|pathspec
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|seen
)paren
suffix:semicolon
)brace
DECL|function|git_add_config
r_static
r_int
id|git_add_config
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
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.excludesfile&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
id|die
c_func
(paren
l_string|&quot;core.excludesfile without value&quot;
)paren
suffix:semicolon
id|excludes_file
op_assign
id|xstrdup
c_func
(paren
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
)paren
suffix:semicolon
)brace
DECL|function|interactive_add
r_int
id|interactive_add
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|argv
(braket
l_int|2
)braket
op_assign
(brace
l_string|&quot;add--interactive&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_return
id|run_command_v_opt
c_func
(paren
id|argv
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
)brace
DECL|variable|lock_file
r_static
r_struct
id|lock_file
id|lock_file
suffix:semicolon
DECL|variable|ignore_error
r_static
r_const
r_char
id|ignore_error
(braket
)braket
op_assign
l_string|&quot;The following paths are ignored by one of your .gitignore files:&bslash;n&quot;
suffix:semicolon
DECL|variable|verbose
DECL|variable|show_only
DECL|variable|ignored_too
DECL|variable|refresh_only
r_static
r_int
id|verbose
op_assign
l_int|0
comma
id|show_only
op_assign
l_int|0
comma
id|ignored_too
op_assign
l_int|0
comma
id|refresh_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|add_interactive
r_static
r_int
id|add_interactive
op_assign
l_int|0
suffix:semicolon
DECL|variable|builtin_add_options
r_static
r_struct
id|option
id|builtin_add_options
(braket
)braket
op_assign
(brace
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|show_only
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;i&squot;
comma
l_string|&quot;interactive&quot;
comma
op_amp
id|add_interactive
comma
l_string|&quot;interactive picking&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_int|NULL
comma
op_amp
id|ignored_too
comma
l_string|&quot;allow adding otherwise ignored files&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;u&squot;
comma
l_int|NULL
comma
op_amp
id|take_worktree_changes
comma
l_string|&quot;update tracked files&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;refresh&quot;
comma
op_amp
id|refresh_only
comma
l_string|&quot;don&squot;t add, only refresh the index&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
DECL|function|cmd_add
r_int
id|cmd_add
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
id|newfd
comma
id|orig_argc
op_assign
id|argc
suffix:semicolon
r_const
r_char
op_star
op_star
id|pathspec
suffix:semicolon
r_struct
id|dir_struct
id|dir
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|builtin_add_options
comma
id|builtin_add_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_interactive
)paren
(brace
r_if
c_cond
(paren
id|add_interactive
op_ne
l_int|1
op_logical_or
id|orig_argc
op_ne
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;add --interactive does not take any parameters&quot;
)paren
suffix:semicolon
m_exit
(paren
id|interactive_add
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|git_config
c_func
(paren
id|git_add_config
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
op_amp
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|take_worktree_changes
)paren
(brace
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
suffix:semicolon
id|add_files_to_cache
c_func
(paren
id|verbose
comma
id|prefix
comma
id|argv
)paren
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Nothing specified, nothing added.&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Maybe you wanted to say &squot;git add .&squot;?&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|refresh_only
)paren
(brace
id|refresh
c_func
(paren
id|verbose
comma
id|pathspec
)paren
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
id|fill_directory
c_func
(paren
op_amp
id|dir
comma
id|pathspec
comma
id|ignored_too
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_only
)paren
(brace
r_const
r_char
op_star
id|sep
op_assign
l_string|&quot;&quot;
comma
op_star
id|eof
op_assign
l_string|&quot;&quot;
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
id|dir.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|sep
comma
id|dir.entries
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|sep
op_assign
l_string|&quot; &quot;
suffix:semicolon
id|eof
op_assign
l_string|&quot;&bslash;n&quot;
suffix:semicolon
)brace
id|fputs
c_func
(paren
id|eof
comma
id|stdout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir.ignored_nr
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
id|ignore_error
)paren
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
id|dir.ignored_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|dir.ignored
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Use -f if you really want to add them.&bslash;n&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;no files added&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dir.nr
suffix:semicolon
id|i
op_increment
)paren
id|add_file_to_cache
c_func
(paren
id|dir.entries
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|verbose
)paren
suffix:semicolon
id|finish
suffix:colon
r_if
c_cond
(paren
id|active_cache_changed
)paren
(brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|close
c_func
(paren
id|newfd
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
op_amp
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
