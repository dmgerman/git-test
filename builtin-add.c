multiline_comment|/*&n; * &quot;git add&quot; builtin command&n; *&n; * Copyright (C) 2006 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|variable|builtin_add_usage
r_static
r_const
r_char
id|builtin_add_usage
(braket
)braket
op_assign
l_string|&quot;git-add [-n] [-v] [-f] [--interactive] [--] &lt;filepattern&gt;...&quot;
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
r_int
id|how
op_assign
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
suffix:semicolon
multiline_comment|/*&n;&t;&t; * ignored entries can be added with exact match,&n;&t;&t; * but not with glob nor recursive.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|how
op_logical_or
(paren
id|entry-&gt;ignored_entry
op_logical_and
id|how
op_ne
id|MATCHED_EXACTLY
)paren
)paren
(brace
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
r_struct
id|stat
id|st
suffix:semicolon
r_const
r_char
op_star
id|match
suffix:semicolon
r_if
c_cond
(paren
id|seen
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
multiline_comment|/* Existing file? We must have ignored it */
id|match
op_assign
id|pathspec
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|lstat
c_func
(paren
id|match
comma
op_amp
id|st
)paren
)paren
r_continue
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
comma
id|match
)paren
suffix:semicolon
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
id|pathspec
)paren
id|dir-&gt;show_both
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
(brace
r_char
op_star
id|common
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|common
comma
op_star
id|pathspec
comma
id|baselen
)paren
suffix:semicolon
id|common
(braket
id|baselen
)braket
op_assign
l_int|0
suffix:semicolon
id|path
op_assign
id|base
op_assign
id|common
suffix:semicolon
)brace
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
DECL|variable|lock_file
r_static
r_struct
id|lock_file
id|lock_file
suffix:semicolon
DECL|variable|ignore_warning
r_static
r_const
r_char
id|ignore_warning
(braket
)braket
op_assign
l_string|&quot;The following paths are ignored by one of your .gitignore files:&bslash;n&quot;
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
suffix:semicolon
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
id|add_interactive
op_assign
l_int|0
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--interactive&quot;
comma
id|argv
(braket
id|i
)braket
)paren
)paren
id|add_interactive
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|add_interactive
)paren
(brace
r_const
r_char
op_star
id|args
(braket
)braket
op_assign
(brace
l_string|&quot;add--interactive&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_if
c_cond
(paren
id|add_interactive
op_ne
l_int|1
op_logical_or
id|argc
op_ne
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;add --interactive does not take any parameters&quot;
)paren
suffix:semicolon
id|execv_git_cmd
c_func
(paren
id|args
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|lock_file
comma
id|get_index_file
c_func
(paren
)paren
comma
l_int|1
)paren
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
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
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
l_string|&quot;-n&quot;
)paren
)paren
(brace
id|show_only
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
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|ignored_too
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
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|verbose
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|builtin_add_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_le
id|i
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
op_plus
id|i
)paren
suffix:semicolon
id|fill_directory
c_func
(paren
op_amp
id|dir
comma
id|pathspec
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
r_if
c_cond
(paren
op_logical_neg
id|ignored_too
op_logical_and
id|dir.entries
(braket
id|i
)braket
op_member_access_from_pointer
id|ignored_entry
)paren
r_continue
suffix:semicolon
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
op_logical_neg
id|ignored_too
)paren
(brace
r_int
id|has_ignored
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|has_ignored
OL
l_int|0
op_logical_and
id|i
OL
id|dir.nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dir.entries
(braket
id|i
)braket
op_member_access_from_pointer
id|ignored_entry
)paren
id|has_ignored
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|has_ignored
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
id|ignore_warning
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|has_ignored
suffix:semicolon
id|i
OL
id|dir.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dir.entries
(braket
id|i
)braket
op_member_access_from_pointer
id|ignored_entry
)paren
r_continue
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|dir.entries
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
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
id|add_file_to_index
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
id|commit_lock_file
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
