multiline_comment|/*&n; * &quot;git add&quot; builtin command&n; *&n; * Copyright (C) 2006 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;lockfile.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;pathspec.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;bulk-checkin.h&quot;
macro_line|#include &quot;argv-array.h&quot;
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
id|N_
c_func
(paren
l_string|&quot;git add [&lt;options&gt;] [--] &lt;pathspec&gt;...&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|patch_interactive
DECL|variable|add_interactive
DECL|variable|edit_interactive
r_static
r_int
id|patch_interactive
comma
id|add_interactive
comma
id|edit_interactive
suffix:semicolon
DECL|variable|take_worktree_changes
r_static
r_int
id|take_worktree_changes
suffix:semicolon
DECL|struct|update_callback_data
r_struct
id|update_callback_data
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|add_errors
r_int
id|add_errors
suffix:semicolon
)brace
suffix:semicolon
DECL|function|fix_unmerged_status
r_static
r_int
id|fix_unmerged_status
c_func
(paren
r_struct
id|diff_filepair
op_star
id|p
comma
r_struct
id|update_callback_data
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;status
op_ne
id|DIFF_STATUS_UNMERGED
)paren
r_return
id|p-&gt;status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data-&gt;flags
op_amp
id|ADD_CACHE_IGNORE_REMOVAL
)paren
op_logical_and
op_logical_neg
id|p-&gt;two-&gt;mode
)paren
multiline_comment|/*&n;&t;&t; * This is not an explicit add request, and the&n;&t;&t; * path is missing from the working tree (deleted)&n;&t;&t; */
r_return
id|DIFF_STATUS_DELETED
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t; * Either an explicit add request, or path exists&n;&t;&t; * in the working tree.  An attempt to explicitly&n;&t;&t; * add a path that does not exist in the working tree&n;&t;&t; * will be caught as an error by the caller immediately.&n;&t;&t; */
r_return
id|DIFF_STATUS_MODIFIED
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
suffix:semicolon
r_struct
id|update_callback_data
op_star
id|data
op_assign
id|cbdata
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
id|fix_unmerged_status
c_func
(paren
id|p
comma
id|data
)paren
)paren
(brace
r_default
suffix:colon
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unexpected diff status %c&quot;
)paren
comma
id|p-&gt;status
)paren
suffix:semicolon
r_case
id|DIFF_STATUS_MODIFIED
suffix:colon
r_case
id|DIFF_STATUS_TYPE_CHANGED
suffix:colon
r_if
c_cond
(paren
id|add_file_to_index
c_func
(paren
op_amp
id|the_index
comma
id|path
comma
id|data-&gt;flags
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data-&gt;flags
op_amp
id|ADD_CACHE_IGNORE_ERRORS
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;updating files failed&quot;
)paren
)paren
suffix:semicolon
id|data-&gt;add_errors
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_DELETED
suffix:colon
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|ADD_CACHE_IGNORE_REMOVAL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data-&gt;flags
op_amp
id|ADD_CACHE_PRETEND
)paren
)paren
id|remove_file_from_index
c_func
(paren
op_amp
id|the_index
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
(paren
id|ADD_CACHE_PRETEND
op_or
id|ADD_CACHE_VERBOSE
)paren
)paren
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;remove &squot;%s&squot;&bslash;n&quot;
)paren
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
r_int
id|add_files_to_cache
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
comma
r_int
id|flags
)paren
(brace
r_struct
id|update_callback_data
id|data
suffix:semicolon
r_struct
id|rev_info
id|rev
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|data.flags
op_assign
id|flags
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
r_if
c_cond
(paren
id|pathspec
)paren
id|copy_pathspec
c_func
(paren
op_amp
id|rev.prune_data
comma
id|pathspec
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
id|data
suffix:semicolon
id|rev.max_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* do not compare unmerged paths with stage #2 */
id|run_diff_files
c_func
(paren
op_amp
id|rev
comma
id|DIFF_RACY_IS_MODIFIED
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|data.add_errors
suffix:semicolon
)brace
DECL|function|prune_directory
r_static
r_char
op_star
id|prune_directory
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_struct
id|pathspec
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
id|seen
op_assign
id|xcalloc
c_func
(paren
id|pathspec-&gt;nr
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
id|dir_path_match
c_func
(paren
id|entry
comma
id|pathspec
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
id|add_pathspec_matches_against_index
c_func
(paren
id|pathspec
comma
id|seen
)paren
suffix:semicolon
r_return
id|seen
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
r_struct
id|pathspec
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
suffix:semicolon
id|seen
op_assign
id|xcalloc
c_func
(paren
id|pathspec-&gt;nr
comma
l_int|1
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
id|REFRESH_IN_PORCELAIN
suffix:colon
id|REFRESH_QUIET
comma
id|pathspec
comma
id|seen
comma
id|_
c_func
(paren
l_string|&quot;Unstaged changes after refreshing the index:&quot;
)paren
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
id|pathspec-&gt;nr
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
id|_
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
)paren
comma
id|pathspec-&gt;items
(braket
id|i
)braket
dot
id|match
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
DECL|function|run_add_interactive
r_int
id|run_add_interactive
c_func
(paren
r_const
r_char
op_star
id|revision
comma
r_const
r_char
op_star
id|patch_mode
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
)paren
(brace
r_int
id|status
comma
id|i
suffix:semicolon
r_struct
id|argv_array
id|argv
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
l_string|&quot;add--interactive&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|patch_mode
)paren
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
id|patch_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revision
)paren
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
id|revision
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
l_string|&quot;--&quot;
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
id|pathspec-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* pass original pathspec, to be re-parsed */
id|argv_array_push
c_func
(paren
op_amp
id|argv
comma
id|pathspec-&gt;items
(braket
id|i
)braket
dot
id|original
)paren
suffix:semicolon
id|status
op_assign
id|run_command_v_opt
c_func
(paren
id|argv.argv
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
id|argv_array_clear
c_func
(paren
op_amp
id|argv
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|interactive_add
r_int
id|interactive_add
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
comma
r_int
id|patch
)paren
(brace
r_struct
id|pathspec
id|pathspec
suffix:semicolon
id|parse_pathspec
c_func
(paren
op_amp
id|pathspec
comma
l_int|0
comma
id|PATHSPEC_PREFER_FULL
op_or
id|PATHSPEC_SYMLINK_LEADING_PATH
op_or
id|PATHSPEC_PREFIX_ORIGIN
comma
id|prefix
comma
id|argv
)paren
suffix:semicolon
r_return
id|run_add_interactive
c_func
(paren
l_int|NULL
comma
id|patch
ques
c_cond
l_string|&quot;--patch&quot;
suffix:colon
l_int|NULL
comma
op_amp
id|pathspec
)paren
suffix:semicolon
)brace
DECL|function|edit_patch
r_static
r_int
id|edit_patch
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
r_char
op_star
id|file
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;ADD_EDIT.patch&quot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|apply_argv
(braket
)braket
op_assign
(brace
l_string|&quot;apply&quot;
comma
l_string|&quot;--recount&quot;
comma
l_string|&quot;--cached&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|child_process
id|child
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
r_struct
id|rev_info
id|rev
suffix:semicolon
r_int
id|out
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|apply_argv
(braket
l_int|3
)braket
op_assign
id|file
suffix:semicolon
id|git_config
c_func
(paren
id|git_diff_basic_config
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* no &quot;diff&quot; UI options */
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
id|_
c_func
(paren
l_string|&quot;Could not read the index&quot;
)paren
)paren
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
id|rev.diffopt.context
op_assign
l_int|7
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
id|rev.diffopt.use_color
op_assign
l_int|0
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|IGNORE_DIRTY_SUBMODULES
)paren
suffix:semicolon
id|out
op_assign
id|open
c_func
(paren
id|file
comma
id|O_CREAT
op_or
id|O_WRONLY
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not open &squot;%s&squot; for writing.&quot;
)paren
comma
id|file
)paren
suffix:semicolon
id|rev.diffopt.file
op_assign
id|xfdopen
c_func
(paren
id|out
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
id|rev.diffopt.close_file
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|run_diff_files
c_func
(paren
op_amp
id|rev
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not write patch&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|launch_editor
c_func
(paren
id|file
comma
l_int|NULL
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
l_string|&quot;editing patch failed&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|file
comma
op_amp
id|st
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not stat &squot;%s&squot;&quot;
)paren
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|st.st_size
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Empty patch. Aborted.&quot;
)paren
)paren
suffix:semicolon
id|child.git_cmd
op_assign
l_int|1
suffix:semicolon
id|child.argv
op_assign
id|apply_argv
suffix:semicolon
r_if
c_cond
(paren
id|run_command
c_func
(paren
op_amp
id|child
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not apply &squot;%s&squot;&quot;
)paren
comma
id|file
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|file
)paren
suffix:semicolon
id|free
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
l_int|0
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
id|N_
c_func
(paren
l_string|&quot;The following paths are ignored by one of your .gitignore files:&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|verbose
DECL|variable|show_only
DECL|variable|ignored_too
DECL|variable|refresh_only
r_static
r_int
id|verbose
comma
id|show_only
comma
id|ignored_too
comma
id|refresh_only
suffix:semicolon
DECL|variable|ignore_add_errors
DECL|variable|intent_to_add
DECL|variable|ignore_missing
r_static
r_int
id|ignore_add_errors
comma
id|intent_to_add
comma
id|ignore_missing
suffix:semicolon
DECL|macro|ADDREMOVE_DEFAULT
mdefine_line|#define ADDREMOVE_DEFAULT 1
DECL|variable|addremove
r_static
r_int
id|addremove
op_assign
id|ADDREMOVE_DEFAULT
suffix:semicolon
DECL|variable|addremove_explicit
r_static
r_int
id|addremove_explicit
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* unspecified */
DECL|function|ignore_removal_cb
r_static
r_int
id|ignore_removal_cb
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
multiline_comment|/* if we are told to ignore, we are not adding removals */
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
op_logical_neg
id|unset
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
comma
id|N_
c_func
(paren
l_string|&quot;dry run&quot;
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
l_string|&quot;be verbose&quot;
)paren
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;i&squot;
comma
l_string|&quot;interactive&quot;
comma
op_amp
id|add_interactive
comma
id|N_
c_func
(paren
l_string|&quot;interactive picking&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;p&squot;
comma
l_string|&quot;patch&quot;
comma
op_amp
id|patch_interactive
comma
id|N_
c_func
(paren
l_string|&quot;select hunks interactively&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;e&squot;
comma
l_string|&quot;edit&quot;
comma
op_amp
id|edit_interactive
comma
id|N_
c_func
(paren
l_string|&quot;edit current diff and apply&quot;
)paren
)paren
comma
id|OPT__FORCE
c_func
(paren
op_amp
id|ignored_too
comma
id|N_
c_func
(paren
l_string|&quot;allow adding otherwise ignored files&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;u&squot;
comma
l_string|&quot;update&quot;
comma
op_amp
id|take_worktree_changes
comma
id|N_
c_func
(paren
l_string|&quot;update tracked files&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;N&squot;
comma
l_string|&quot;intent-to-add&quot;
comma
op_amp
id|intent_to_add
comma
id|N_
c_func
(paren
l_string|&quot;record only the fact that the path will be added later&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;A&squot;
comma
l_string|&quot;all&quot;
comma
op_amp
id|addremove_explicit
comma
id|N_
c_func
(paren
l_string|&quot;add changes from all tracked and untracked files&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;ignore-removal&quot;
comma
op_amp
id|addremove_explicit
comma
l_int|NULL
multiline_comment|/* takes no arguments */
comma
id|N_
c_func
(paren
l_string|&quot;ignore paths removed in the working tree (same as --no-all)&quot;
)paren
comma
id|PARSE_OPT_NOARG
comma
id|ignore_removal_cb
)brace
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;refresh&quot;
comma
op_amp
id|refresh_only
comma
id|N_
c_func
(paren
l_string|&quot;don&squot;t add, only refresh the index&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;ignore-errors&quot;
comma
op_amp
id|ignore_add_errors
comma
id|N_
c_func
(paren
l_string|&quot;just skip files which cannot be added because of errors&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;ignore-missing&quot;
comma
op_amp
id|ignore_missing
comma
id|N_
c_func
(paren
l_string|&quot;check if - even missing - files are ignored in dry run&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
DECL|function|add_config
r_static
r_int
id|add_config
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
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;add.ignoreerrors&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;add.ignore-errors&quot;
)paren
)paren
(brace
id|ignore_add_errors
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
DECL|function|add_files
r_static
r_int
id|add_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_int
id|flags
)paren
(brace
r_int
id|i
comma
id|exit_status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;ignored_nr
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
id|ignore_error
)paren
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
id|dir-&gt;ignored_nr
suffix:semicolon
id|i
op_increment
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|dir-&gt;ignored
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;Use -f if you really want to add them.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|exit_status
op_assign
l_int|1
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
id|dir-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|add_file_to_cache
c_func
(paren
id|dir-&gt;entries
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|flags
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ignore_add_errors
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;adding files failed&quot;
)paren
)paren
suffix:semicolon
id|exit_status
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|exit_status
suffix:semicolon
)brace
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
id|exit_status
op_assign
l_int|0
suffix:semicolon
r_struct
id|pathspec
id|pathspec
suffix:semicolon
r_struct
id|dir_struct
id|dir
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
id|add_new_files
suffix:semicolon
r_int
id|require_pathspec
suffix:semicolon
r_char
op_star
id|seen
op_assign
l_int|NULL
suffix:semicolon
id|git_config
c_func
(paren
id|add_config
comma
l_int|NULL
)paren
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
id|prefix
comma
id|builtin_add_options
comma
id|builtin_add_usage
comma
id|PARSE_OPT_KEEP_ARGV0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|patch_interactive
)paren
id|add_interactive
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|add_interactive
)paren
m_exit
(paren
id|interactive_add
c_func
(paren
id|argc
l_int|1
comma
id|argv
op_plus
l_int|1
comma
id|prefix
comma
id|patch_interactive
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|edit_interactive
)paren
r_return
id|edit_patch
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
)paren
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|addremove_explicit
)paren
id|addremove
op_assign
id|addremove_explicit
suffix:semicolon
r_else
r_if
c_cond
(paren
id|take_worktree_changes
op_logical_and
id|ADDREMOVE_DEFAULT
)paren
id|addremove
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &quot;-u&quot; was given but not &quot;-A&quot; */
r_if
c_cond
(paren
id|addremove
op_logical_and
id|take_worktree_changes
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;-A and -u are mutually incompatible&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|take_worktree_changes
op_logical_and
id|addremove_explicit
OL
l_int|0
op_logical_and
id|argc
)paren
multiline_comment|/* Turn &quot;git add pathspec...&quot; to &quot;git add -A pathspec...&quot; */
id|addremove
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
op_logical_and
id|ignore_missing
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Option --ignore-missing can only be used together with --dry-run&quot;
)paren
)paren
suffix:semicolon
id|add_new_files
op_assign
op_logical_neg
id|take_worktree_changes
op_logical_and
op_logical_neg
id|refresh_only
suffix:semicolon
id|require_pathspec
op_assign
op_logical_neg
(paren
id|take_worktree_changes
op_logical_or
(paren
l_int|0
OL
id|addremove_explicit
)paren
)paren
suffix:semicolon
id|hold_locked_index
c_func
(paren
op_amp
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
id|flags
op_assign
(paren
(paren
id|verbose
ques
c_cond
id|ADD_CACHE_VERBOSE
suffix:colon
l_int|0
)paren
op_or
(paren
id|show_only
ques
c_cond
id|ADD_CACHE_PRETEND
suffix:colon
l_int|0
)paren
op_or
(paren
id|intent_to_add
ques
c_cond
id|ADD_CACHE_INTENT
suffix:colon
l_int|0
)paren
op_or
(paren
id|ignore_add_errors
ques
c_cond
id|ADD_CACHE_IGNORE_ERRORS
suffix:colon
l_int|0
)paren
op_or
(paren
op_logical_neg
(paren
id|addremove
op_logical_or
id|take_worktree_changes
)paren
ques
c_cond
id|ADD_CACHE_IGNORE_REMOVAL
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|require_pathspec
op_logical_and
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
id|_
c_func
(paren
l_string|&quot;Nothing specified, nothing added.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;Maybe you wanted to say &squot;git add .&squot;?&bslash;n&quot;
)paren
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
id|_
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check the &quot;pathspec &squot;%s&squot; did not match any files&quot; block&n;&t; * below before enabling new magic.&n;&t; */
id|parse_pathspec
c_func
(paren
op_amp
id|pathspec
comma
l_int|0
comma
id|PATHSPEC_PREFER_FULL
op_or
id|PATHSPEC_SYMLINK_LEADING_PATH
op_or
id|PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE
comma
id|prefix
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_new_files
)paren
(brace
r_int
id|baselen
suffix:semicolon
multiline_comment|/* Set up the default git porcelain excludes */
id|memset
c_func
(paren
op_amp
id|dir
comma
l_int|0
comma
r_sizeof
(paren
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
id|dir.flags
op_or_assign
id|DIR_COLLECT_IGNORED
suffix:semicolon
id|setup_standard_excludes
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
)brace
multiline_comment|/* This picks up the paths that are not tracked */
id|baselen
op_assign
id|fill_directory
c_func
(paren
op_amp
id|dir
comma
op_amp
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec.nr
)paren
id|seen
op_assign
id|prune_directory
c_func
(paren
op_amp
id|dir
comma
op_amp
id|pathspec
comma
id|baselen
)paren
suffix:semicolon
)brace
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
op_amp
id|pathspec
)paren
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pathspec.nr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|seen
)paren
id|seen
op_assign
id|find_pathspecs_matching_against_index
c_func
(paren
op_amp
id|pathspec
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * file_exists() assumes exact match&n;&t;&t; */
id|GUARD_PATHSPEC
c_func
(paren
op_amp
id|pathspec
comma
id|PATHSPEC_FROMTOP
op_or
id|PATHSPEC_LITERAL
op_or
id|PATHSPEC_GLOB
op_or
id|PATHSPEC_ICASE
op_or
id|PATHSPEC_EXCLUDE
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
id|pathspec.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|pathspec.items
(braket
id|i
)braket
dot
id|match
suffix:semicolon
r_if
c_cond
(paren
id|pathspec.items
(braket
id|i
)braket
dot
id|magic
op_amp
id|PATHSPEC_EXCLUDE
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
op_logical_and
id|path
(braket
l_int|0
)braket
op_logical_and
(paren
(paren
id|pathspec.items
(braket
id|i
)braket
dot
id|magic
op_amp
(paren
id|PATHSPEC_GLOB
op_or
id|PATHSPEC_ICASE
)paren
)paren
op_logical_or
op_logical_neg
id|file_exists
c_func
(paren
id|path
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|ignore_missing
)paren
(brace
r_int
id|dtype
op_assign
id|DT_UNKNOWN
suffix:semicolon
r_if
c_cond
(paren
id|is_excluded
c_func
(paren
op_amp
id|dir
comma
id|path
comma
op_amp
id|dtype
)paren
)paren
id|dir_add_ignored
c_func
(paren
op_amp
id|dir
comma
id|path
comma
id|pathspec.items
(braket
id|i
)braket
dot
id|len
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
)paren
comma
id|pathspec.items
(braket
id|i
)braket
dot
id|original
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|seen
)paren
suffix:semicolon
)brace
id|plug_bulk_checkin
c_func
(paren
)paren
suffix:semicolon
id|exit_status
op_or_assign
id|add_files_to_cache
c_func
(paren
id|prefix
comma
op_amp
id|pathspec
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_new_files
)paren
id|exit_status
op_or_assign
id|add_files
c_func
(paren
op_amp
id|dir
comma
id|flags
)paren
suffix:semicolon
id|unplug_bulk_checkin
c_func
(paren
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
id|write_locked_index
c_func
(paren
op_amp
id|the_index
comma
op_amp
id|lock_file
comma
id|COMMIT_LOCK
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
)paren
suffix:semicolon
)brace
r_return
id|exit_status
suffix:semicolon
)brace
eof
