multiline_comment|/*&n; * &quot;git mv&quot; builtin command&n; *&n; * Copyright (C) 2006 Johannes Schindelin&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|builtin_mv_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_mv_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git mv [options] &lt;source&gt;... &lt;destination&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|copy_pathspec
r_static
r_const
r_char
op_star
op_star
id|copy_pathspec
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
op_star
id|pathspec
comma
r_int
id|count
comma
r_int
id|base_name
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
op_star
id|result
op_assign
id|xmalloc
c_func
(paren
(paren
id|count
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
comma
id|pathspec
comma
id|count
op_star
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
id|result
(braket
id|count
)braket
op_assign
l_int|NULL
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|length
op_assign
id|strlen
c_func
(paren
id|result
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|0
op_logical_and
id|is_dir_sep
c_func
(paren
id|result
(braket
id|i
)braket
(braket
id|length
l_int|1
)braket
)paren
)paren
id|result
(braket
id|i
)braket
op_assign
id|xmemdupz
c_func
(paren
id|result
(braket
id|i
)braket
comma
id|length
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base_name
)paren
id|result
(braket
id|i
)braket
op_assign
id|basename
c_func
(paren
(paren
r_char
op_star
)paren
id|result
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
id|get_pathspec
c_func
(paren
id|prefix
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|add_slash
r_static
r_const
r_char
op_star
id|add_slash
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
(braket
id|len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_char
op_star
id|with_slash
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|with_slash
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|with_slash
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|with_slash
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|with_slash
suffix:semicolon
)brace
r_return
id|path
suffix:semicolon
)brace
DECL|variable|lock_file
r_static
r_struct
id|lock_file
id|lock_file
suffix:semicolon
DECL|function|cmd_mv
r_int
id|cmd_mv
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
id|force
op_assign
l_int|0
comma
id|ignore_errors
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|builtin_mv_options
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
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
comma
op_amp
id|force
comma
l_string|&quot;force move/rename even if target exists&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;k&squot;
comma
l_int|NULL
comma
op_amp
id|ignore_errors
comma
l_string|&quot;skip move/rename errors&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_const
r_char
op_star
op_star
id|source
comma
op_star
op_star
id|destination
comma
op_star
op_star
id|dest_path
suffix:semicolon
r_enum
id|update_mode
(brace
id|BOTH
op_assign
l_int|0
comma
id|WORKING_DIRECTORY
comma
id|INDEX
)brace
op_star
id|modes
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_struct
id|string_list
id|src_for_dst
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
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
id|builtin_mv_options
comma
id|builtin_mv_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|argc
OL
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|builtin_mv_usage
comma
id|builtin_mv_options
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
id|source
op_assign
id|copy_pathspec
c_func
(paren
id|prefix
comma
id|argv
comma
id|argc
comma
l_int|0
)paren
suffix:semicolon
id|modes
op_assign
id|xcalloc
c_func
(paren
id|argc
comma
r_sizeof
(paren
r_enum
id|update_mode
)paren
)paren
suffix:semicolon
id|dest_path
op_assign
id|copy_pathspec
c_func
(paren
id|prefix
comma
id|argv
op_plus
id|argc
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest_path
(braket
l_int|0
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* special case: &quot;.&quot; was normalized to &quot;&quot; */
id|destination
op_assign
id|copy_pathspec
c_func
(paren
id|dest_path
(braket
l_int|0
)braket
comma
id|argv
comma
id|argc
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|dest_path
(braket
l_int|0
)braket
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|dest_path
(braket
l_int|0
)braket
op_assign
id|add_slash
c_func
(paren
id|dest_path
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|destination
op_assign
id|copy_pathspec
c_func
(paren
id|dest_path
(braket
l_int|0
)braket
comma
id|argv
comma
id|argc
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|builtin_mv_usage
comma
id|builtin_mv_options
)paren
suffix:semicolon
id|destination
op_assign
id|dest_path
suffix:semicolon
)brace
multiline_comment|/* Checking */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
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
id|src
op_assign
id|source
(braket
id|i
)braket
comma
op_star
id|dst
op_assign
id|destination
(braket
id|i
)braket
suffix:semicolon
r_int
id|length
comma
id|src_is_dir
suffix:semicolon
r_const
r_char
op_star
id|bad
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|show_only
)paren
id|printf
c_func
(paren
l_string|&quot;Checking rename of &squot;%s&squot; to &squot;%s&squot;&bslash;n&quot;
comma
id|src
comma
id|dst
)paren
suffix:semicolon
id|length
op_assign
id|strlen
c_func
(paren
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|src
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
id|bad
op_assign
l_string|&quot;bad source&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|src
comma
id|dst
comma
id|length
)paren
op_logical_and
(paren
id|dst
(braket
id|length
)braket
op_eq
l_int|0
op_logical_or
id|dst
(braket
id|length
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
(brace
id|bad
op_assign
l_string|&quot;can not move directory into itself&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|src_is_dir
op_assign
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
op_logical_and
id|lstat
c_func
(paren
id|dst
comma
op_amp
id|st
)paren
op_eq
l_int|0
)paren
id|bad
op_assign
l_string|&quot;cannot move directory over file&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|src_is_dir
)paren
(brace
r_const
r_char
op_star
id|src_w_slash
op_assign
id|add_slash
c_func
(paren
id|src
)paren
suffix:semicolon
r_int
id|len_w_slash
op_assign
id|length
op_plus
l_int|1
suffix:semicolon
r_int
id|first
comma
id|last
suffix:semicolon
id|modes
(braket
id|i
)braket
op_assign
id|WORKING_DIRECTORY
suffix:semicolon
id|first
op_assign
id|cache_name_pos
c_func
(paren
id|src_w_slash
comma
id|len_w_slash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first
op_ge
l_int|0
)paren
id|die
(paren
l_string|&quot;Huh? %.*s is in index?&quot;
comma
id|len_w_slash
comma
id|src_w_slash
)paren
suffix:semicolon
id|first
op_assign
l_int|1
id|first
suffix:semicolon
r_for
c_loop
(paren
id|last
op_assign
id|first
suffix:semicolon
id|last
OL
id|active_nr
suffix:semicolon
id|last
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|active_cache
(braket
id|last
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|path
comma
id|src_w_slash
comma
id|len_w_slash
)paren
)paren
r_break
suffix:semicolon
)brace
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|src_w_slash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last
id|first
OL
l_int|1
)paren
id|bad
op_assign
l_string|&quot;source directory is empty&quot;
suffix:semicolon
r_else
(brace
r_int
id|j
comma
id|dst_len
suffix:semicolon
r_if
c_cond
(paren
id|last
id|first
OG
l_int|0
)paren
(brace
id|source
op_assign
id|xrealloc
c_func
(paren
id|source
comma
(paren
id|argc
op_plus
id|last
id|first
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|destination
op_assign
id|xrealloc
c_func
(paren
id|destination
comma
(paren
id|argc
op_plus
id|last
id|first
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|modes
op_assign
id|xrealloc
c_func
(paren
id|modes
comma
(paren
id|argc
op_plus
id|last
id|first
)paren
op_star
r_sizeof
(paren
r_enum
id|update_mode
)paren
)paren
suffix:semicolon
)brace
id|dst
op_assign
id|add_slash
c_func
(paren
id|dst
)paren
suffix:semicolon
id|dst_len
op_assign
id|strlen
c_func
(paren
id|dst
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|last
id|first
suffix:semicolon
id|j
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|active_cache
(braket
id|first
op_plus
id|j
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
id|source
(braket
id|argc
op_plus
id|j
)braket
op_assign
id|path
suffix:semicolon
id|destination
(braket
id|argc
op_plus
id|j
)braket
op_assign
id|prefix_path
c_func
(paren
id|dst
comma
id|dst_len
comma
id|path
op_plus
id|length
op_plus
l_int|1
)paren
suffix:semicolon
id|modes
(braket
id|argc
op_plus
id|j
)braket
op_assign
id|INDEX
suffix:semicolon
)brace
id|argc
op_add_assign
id|last
id|first
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|cache_name_pos
c_func
(paren
id|src
comma
id|length
)paren
OL
l_int|0
)paren
id|bad
op_assign
l_string|&quot;not under version control&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|dst
comma
op_amp
id|st
)paren
op_eq
l_int|0
)paren
(brace
id|bad
op_assign
l_string|&quot;destination exists&quot;
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * only files can overwrite each other:&n;&t;&t;&t;&t; * check both source and destination&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Warning: %s;&quot;
l_string|&quot; will overwrite!&bslash;n&quot;
comma
id|bad
)paren
suffix:semicolon
id|bad
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|bad
op_assign
l_string|&quot;Cannot overwrite&quot;
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|string_list_has_string
c_func
(paren
op_amp
id|src_for_dst
comma
id|dst
)paren
)paren
id|bad
op_assign
l_string|&quot;multiple sources for the same target&quot;
suffix:semicolon
r_else
id|string_list_insert
c_func
(paren
id|dst
comma
op_amp
id|src_for_dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad
)paren
(brace
r_if
c_cond
(paren
id|ignore_errors
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|argc
OG
l_int|0
)paren
(brace
id|memmove
c_func
(paren
id|source
op_plus
id|i
comma
id|source
op_plus
id|i
op_plus
l_int|1
comma
(paren
id|argc
id|i
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|destination
op_plus
id|i
comma
id|destination
op_plus
id|i
op_plus
l_int|1
comma
(paren
id|argc
id|i
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
)brace
r_else
id|die
(paren
l_string|&quot;%s, source=%s, destination=%s&quot;
comma
id|bad
comma
id|src
comma
id|dst
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|src
op_assign
id|source
(braket
id|i
)braket
comma
op_star
id|dst
op_assign
id|destination
(braket
id|i
)braket
suffix:semicolon
r_enum
id|update_mode
id|mode
op_assign
id|modes
(braket
id|i
)braket
suffix:semicolon
r_int
id|pos
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
l_string|&quot;Renaming %s to %s&bslash;n&quot;
comma
id|src
comma
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
op_logical_and
id|mode
op_ne
id|INDEX
op_logical_and
id|rename
c_func
(paren
id|src
comma
id|dst
)paren
OL
l_int|0
op_logical_and
op_logical_neg
id|ignore_errors
)paren
id|die_errno
(paren
l_string|&quot;renaming &squot;%s&squot; failed&quot;
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|WORKING_DIRECTORY
)paren
r_continue
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|src
comma
id|strlen
c_func
(paren
id|src
)paren
)paren
suffix:semicolon
m_assert
(paren
id|pos
op_ge
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
)paren
id|rename_cache_entry_at
c_func
(paren
id|pos
comma
id|dst
)paren
suffix:semicolon
)brace
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
l_int|0
suffix:semicolon
)brace
eof
