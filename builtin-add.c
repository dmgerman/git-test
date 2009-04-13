multiline_comment|/*&n; * &quot;git add&quot; builtin command&n; *&n; * Copyright (C) 2006 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
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
l_string|&quot;git add [options] [--] &lt;filepattern&gt;...&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|patch_interactive
DECL|variable|add_interactive
r_static
r_int
id|patch_interactive
comma
id|add_interactive
suffix:semicolon
DECL|variable|take_worktree_changes
r_static
r_int
id|take_worktree_changes
suffix:semicolon
DECL|function|fill_pathspec_matches
r_static
r_void
id|fill_pathspec_matches
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
comma
r_char
op_star
id|seen
comma
r_int
id|specs
)paren
(brace
r_int
id|num_unmatched
op_assign
l_int|0
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Since we are walking the index as if we were walking the directory,&n;&t; * we have to mark the matched pathspec as seen; otherwise we will&n;&t; * mistakenly think that the user gave a pathspec that did not match&n;&t; * anything.&n;&t; */
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
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
)paren
id|num_unmatched
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_unmatched
)paren
r_return
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
id|match_pathspec
c_func
(paren
id|pathspec
comma
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
comma
l_int|0
comma
id|seen
)paren
suffix:semicolon
)brace
)brace
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
id|fill_pathspec_matches
c_func
(paren
id|pathspec
comma
id|seen
comma
id|specs
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
DECL|function|treat_gitlinks
r_static
r_void
id|treat_gitlinks
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathspec
op_logical_or
op_logical_neg
op_star
id|pathspec
)paren
r_return
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
(brace
r_int
id|len
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|j
)braket
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|len2
op_assign
id|strlen
c_func
(paren
id|pathspec
(braket
id|j
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len2
op_le
id|len
op_logical_or
id|pathspec
(braket
id|j
)braket
(braket
id|len
)braket
op_ne
l_char|&squot;/&squot;
op_logical_or
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|pathspec
(braket
id|j
)braket
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|len2
op_eq
id|len
op_plus
l_int|1
)paren
multiline_comment|/* strip trailing slash */
id|pathspec
(braket
id|j
)braket
op_assign
id|xstrndup
c_func
(paren
id|ce-&gt;name
comma
id|len
)paren
suffix:semicolon
r_else
id|die
(paren
l_string|&quot;Path &squot;%s&squot; is in submodule &squot;%.*s&squot;&quot;
comma
id|pathspec
(braket
id|j
)braket
comma
id|len
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
)brace
)brace
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
id|dir-&gt;flags
op_or_assign
id|DIR_COLLECT_IGNORED
suffix:semicolon
id|setup_standard_excludes
c_func
(paren
id|dir
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
id|refresh_index
c_func
(paren
op_amp
id|the_index
comma
id|verbose
ques
c_cond
id|REFRESH_SAY_CHANGED
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
DECL|function|validate_pathspec
r_static
r_const
r_char
op_star
op_star
id|validate_pathspec
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
r_const
r_char
op_star
op_star
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
id|pathspec
)paren
(brace
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|pathspec
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|has_symlink_leading_path
c_func
(paren
op_star
id|p
comma
id|strlen
c_func
(paren
op_star
id|p
)paren
)paren
)paren
(brace
r_int
id|len
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is beyond a symbolic link&quot;
comma
op_star
id|p
op_plus
id|len
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|pathspec
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
)paren
(brace
r_int
id|status
comma
id|ac
suffix:semicolon
r_const
r_char
op_star
op_star
id|args
suffix:semicolon
r_const
r_char
op_star
op_star
id|pathspec
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|argc
)paren
(brace
id|pathspec
op_assign
id|validate_pathspec
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathspec
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|args
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_const
r_char
op_star
)paren
comma
(paren
id|argc
op_plus
l_int|4
)paren
)paren
suffix:semicolon
id|ac
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|ac
op_increment
)braket
op_assign
l_string|&quot;add--interactive&quot;
suffix:semicolon
r_if
c_cond
(paren
id|patch_interactive
)paren
id|args
(braket
id|ac
op_increment
)braket
op_assign
l_string|&quot;--patch&quot;
suffix:semicolon
id|args
(braket
id|ac
op_increment
)braket
op_assign
l_string|&quot;--&quot;
suffix:semicolon
r_if
c_cond
(paren
id|argc
)paren
(brace
id|memcpy
c_func
(paren
op_amp
(paren
id|args
(braket
id|ac
)braket
)paren
comma
id|pathspec
comma
r_sizeof
(paren
r_const
r_char
op_star
)paren
op_star
id|argc
)paren
suffix:semicolon
id|ac
op_add_assign
id|argc
suffix:semicolon
)brace
id|args
(braket
id|ac
)braket
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|run_command_v_opt
c_func
(paren
id|args
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
id|free
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|status
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
DECL|variable|ignore_add_errors
DECL|variable|addremove
DECL|variable|intent_to_add
r_static
r_int
id|ignore_add_errors
comma
id|addremove
comma
id|intent_to_add
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
l_char|&squot;p&squot;
comma
l_string|&quot;patch&quot;
comma
op_amp
id|patch_interactive
comma
l_string|&quot;interactive patching&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
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
l_string|&quot;update&quot;
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
l_char|&squot;N&squot;
comma
l_string|&quot;intent-to-add&quot;
comma
op_amp
id|intent_to_add
comma
l_string|&quot;record only the fact that the path will be added later&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;A&squot;
comma
l_string|&quot;all&quot;
comma
op_amp
id|addremove
comma
l_string|&quot;add all, noticing removal of tracked files&quot;
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
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;ignore-errors&quot;
comma
op_amp
id|ignore_add_errors
comma
l_string|&quot;just skip files which cannot be added because of errors&quot;
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
id|strcasecmp
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
l_string|&quot;adding files failed&quot;
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
r_int
id|newfd
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
r_int
id|flags
suffix:semicolon
r_int
id|add_new_files
suffix:semicolon
r_int
id|require_pathspec
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
comma
id|argv
comma
id|prefix
)paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|add_config
comma
l_int|NULL
)paren
suffix:semicolon
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
l_string|&quot;-A and -u are mutually incompatible&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addremove
op_logical_or
id|take_worktree_changes
)paren
op_logical_and
op_logical_neg
id|argc
)paren
(brace
r_static
r_const
r_char
op_star
id|here
(braket
l_int|2
)braket
op_assign
(brace
l_string|&quot;.&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|argc
op_assign
l_int|1
suffix:semicolon
id|argv
op_assign
id|here
suffix:semicolon
)brace
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
id|take_worktree_changes
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
id|validate_pathspec
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
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
id|treat_gitlinks
c_func
(paren
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_new_files
)paren
multiline_comment|/* This picks up the paths that are not tracked */
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
id|exit_status
op_or_assign
id|add_files_to_cache
c_func
(paren
id|prefix
comma
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
id|exit_status
suffix:semicolon
)brace
eof
