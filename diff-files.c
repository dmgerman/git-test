multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|diff_files_usage
r_static
r_const
r_char
id|diff_files_usage
(braket
)braket
op_assign
l_string|&quot;git-diff-files [-q] &quot;
l_string|&quot;[&lt;common diff options&gt;] [&lt;path&gt;...]&quot;
id|COMMON_DIFF_OPTIONS_HELP
suffix:semicolon
DECL|variable|diff_options
r_static
r_struct
id|diff_options
id|diff_options
suffix:semicolon
DECL|variable|silent
r_static
r_int
id|silent
op_assign
l_int|0
suffix:semicolon
DECL|function|show_unmerge
r_static
r_void
id|show_unmerge
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|diff_unmerge
c_func
(paren
op_amp
id|diff_options
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|show_file
r_static
r_void
id|show_file
c_func
(paren
r_int
id|pfx
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
id|diff_addremove
c_func
(paren
op_amp
id|diff_options
comma
id|pfx
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|ce-&gt;sha1
comma
id|ce-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|show_modified
r_static
r_void
id|show_modified
c_func
(paren
r_int
id|oldmode
comma
r_int
id|mode
comma
r_const
r_int
r_char
op_star
id|old_sha1
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_char
op_star
id|path
)paren
(brace
id|diff_change
c_func
(paren
op_amp
id|diff_options
comma
id|oldmode
comma
id|mode
comma
id|old_sha1
comma
id|sha1
comma
id|path
comma
l_int|NULL
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
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_const
r_char
op_star
op_star
id|pathspec
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|entries
comma
id|i
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
id|diff_setup
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
op_logical_and
id|argv
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-q&quot;
)paren
)paren
id|silent
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-r&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* no-op */
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-s&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* no-op */
r_else
(brace
r_int
id|diff_opt_cnt
suffix:semicolon
id|diff_opt_cnt
op_assign
id|diff_opt_parse
c_func
(paren
op_amp
id|diff_options
comma
id|argv
op_plus
l_int|1
comma
id|argc
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_opt_cnt
OL
l_int|0
)paren
id|usage
c_func
(paren
id|diff_files_usage
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|diff_opt_cnt
)paren
(brace
id|argv
op_add_assign
id|diff_opt_cnt
suffix:semicolon
id|argc
op_sub_assign
id|diff_opt_cnt
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
id|usage
c_func
(paren
id|diff_files_usage
)paren
suffix:semicolon
)brace
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Find the directory, and set up the pathspec */
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
op_plus
l_int|1
)paren
suffix:semicolon
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_setup_done
c_func
(paren
op_amp
id|diff_options
)paren
OL
l_int|0
)paren
id|usage
c_func
(paren
id|diff_files_usage
)paren
suffix:semicolon
multiline_comment|/* At this point, if argc == 1, then we are doing everything.&n;&t; * Otherwise argv[1] .. argv[argc-1] have the explicit paths.&n;&t; */
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
r_int
id|oldmode
suffix:semicolon
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
r_int
id|changed
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_path_match
c_func
(paren
id|ce
comma
id|pathspec
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|show_unmerge
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|entries
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
id|i
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
multiline_comment|/* compensate for loop control increments */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
op_logical_and
id|errno
op_ne
id|ENOTDIR
)paren
(brace
id|perror
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|silent
)paren
r_continue
suffix:semicolon
id|show_file
c_func
(paren
l_char|&squot;-&squot;
comma
id|ce
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|changed
op_assign
id|ce_match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
op_logical_and
op_logical_neg
id|diff_options.find_copies_harder
)paren
r_continue
suffix:semicolon
id|oldmode
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
id|show_modified
c_func
(paren
id|oldmode
comma
id|DIFF_FILE_CANON_MODE
c_func
(paren
id|st.st_mode
)paren
comma
id|ce-&gt;sha1
comma
(paren
id|changed
ques
c_cond
id|null_sha1
suffix:colon
id|ce-&gt;sha1
)paren
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
id|diffcore_std
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
