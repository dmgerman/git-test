multiline_comment|/*&n; * &quot;git mv&quot; builtin command&n; *&n; * Copyright (C) 2006 Johannes Schindelin&n; */
macro_line|#include &lt;fnmatch.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;path-list.h&quot;
DECL|variable|builtin_mv_usage
r_static
r_const
r_char
id|builtin_mv_usage
(braket
)braket
op_assign
l_string|&quot;git-mv [-n] [-f] (&lt;source&gt; &lt;destination&gt; | [-k] &lt;source&gt;... &lt;destination&gt;)&quot;
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
id|result
(braket
id|i
)braket
(braket
id|length
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_char
op_star
id|without_slash
op_assign
id|xmalloc
c_func
(paren
id|length
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|without_slash
comma
id|result
(braket
id|i
)braket
comma
id|length
l_int|1
)paren
suffix:semicolon
id|without_slash
(braket
id|length
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|result
(braket
id|i
)braket
op_assign
id|without_slash
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base_name
)paren
(brace
r_const
r_char
op_star
id|last_slash
op_assign
id|strrchr
c_func
(paren
id|result
(braket
id|i
)braket
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_slash
)paren
id|result
(braket
id|i
)braket
op_assign
id|last_slash
op_plus
l_int|1
suffix:semicolon
)brace
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
DECL|function|show_list
r_static
r_void
id|show_list
c_func
(paren
r_const
r_char
op_star
id|label
comma
r_struct
id|path_list
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;nr
OG
l_int|0
)paren
(brace
r_int
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|label
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
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|i
OG
l_int|0
ques
c_cond
l_string|&quot;, &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|path
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
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
comma
id|count
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
id|path_list
id|overwritten
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
r_struct
id|path_list
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
r_struct
id|path_list
id|added
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
r_struct
id|path_list
id|deleted
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
r_struct
id|path_list
id|changed
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
id|force
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
l_string|&quot;-k&quot;
)paren
)paren
(brace
id|ignore_errors
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|builtin_mv_usage
)paren
suffix:semicolon
)brace
id|count
op_assign
id|argc
id|i
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_mv_usage
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
op_plus
id|i
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
id|modes
op_assign
id|xcalloc
c_func
(paren
id|count
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
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
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
op_plus
id|i
comma
id|count
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
id|count
op_ne
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_mv_usage
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|length
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
id|source
(braket
id|i
)braket
comma
id|destination
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|source
(braket
id|i
)braket
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
r_if
c_cond
(paren
op_logical_neg
id|bad
op_logical_and
(paren
id|length
op_assign
id|strlen
c_func
(paren
id|source
(braket
id|i
)braket
)paren
)paren
op_ge
l_int|0
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|destination
(braket
id|i
)braket
comma
id|source
(braket
id|i
)braket
comma
id|length
)paren
op_logical_and
(paren
id|destination
(braket
id|i
)braket
(braket
id|length
)braket
op_eq
l_int|0
op_logical_or
id|destination
(braket
id|i
)braket
(braket
id|length
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
id|bad
op_assign
l_string|&quot;can not move directory into itself&quot;
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
r_const
r_char
op_star
id|dir
op_assign
id|source
(braket
id|i
)braket
comma
op_star
id|dest_dir
op_assign
id|destination
(braket
id|i
)braket
suffix:semicolon
r_int
id|first
comma
id|last
comma
id|len
op_assign
id|strlen
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|dest_dir
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
l_string|&quot;cannot move directory over file&quot;
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
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
id|source
(braket
id|i
)braket
comma
id|len
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
l_string|&quot;Huh? %s/ is in index?&quot;
comma
id|dir
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
id|dir
comma
id|len
)paren
op_logical_or
id|path
(braket
id|len
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|bad
)paren
(brace
r_int
id|j
comma
id|dst_len
op_assign
id|strlen
c_func
(paren
id|dest_dir
)paren
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
id|realloc
c_func
(paren
id|source
comma
(paren
id|count
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
id|realloc
c_func
(paren
id|destination
comma
(paren
id|count
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
id|realloc
c_func
(paren
id|modes
comma
(paren
id|count
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
id|dest_dir
op_assign
id|add_slash
c_func
(paren
id|dest_dir
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
id|count
op_plus
id|j
)braket
op_assign
id|path
suffix:semicolon
id|destination
(braket
id|count
op_plus
id|j
)braket
op_assign
id|prefix_path
c_func
(paren
id|dest_dir
comma
id|dst_len
comma
id|path
op_plus
id|len
)paren
suffix:semicolon
id|modes
(braket
id|count
op_plus
id|j
)braket
op_assign
id|INDEX
suffix:semicolon
)brace
id|count
op_add_assign
id|last
id|first
suffix:semicolon
)brace
r_goto
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bad
op_logical_and
id|lstat
c_func
(paren
id|destination
(braket
id|i
)braket
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
id|path_list_insert
c_func
(paren
id|destination
(braket
id|i
)braket
comma
op_amp
id|overwritten
)paren
suffix:semicolon
)brace
r_else
id|bad
op_assign
l_string|&quot;Cannot overwrite&quot;
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|bad
op_logical_and
id|cache_name_pos
c_func
(paren
id|source
(braket
id|i
)braket
comma
id|strlen
c_func
(paren
id|source
(braket
id|i
)braket
)paren
)paren
OL
l_int|0
)paren
id|bad
op_assign
l_string|&quot;not under version control&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bad
)paren
(brace
r_if
c_cond
(paren
id|path_list_has_path
c_func
(paren
op_amp
id|src_for_dst
comma
id|destination
(braket
id|i
)braket
)paren
)paren
id|bad
op_assign
l_string|&quot;multiple sources for the same target&quot;
suffix:semicolon
r_else
id|path_list_insert
c_func
(paren
id|destination
(braket
id|i
)braket
comma
op_amp
id|src_for_dst
)paren
suffix:semicolon
)brace
id|next
suffix:colon
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
id|count
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
id|count
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
id|count
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
)brace
)brace
r_else
id|die
(paren
l_string|&quot;%s, source=%s, destination=%s&quot;
comma
id|bad
comma
id|source
(braket
id|i
)braket
comma
id|destination
(braket
id|i
)braket
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
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
id|source
(braket
id|i
)braket
comma
id|destination
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
op_logical_and
id|modes
(braket
id|i
)braket
op_ne
id|INDEX
op_logical_and
id|rename
c_func
(paren
id|source
(braket
id|i
)braket
comma
id|destination
(braket
id|i
)braket
)paren
OL
l_int|0
op_logical_and
op_logical_neg
id|ignore_errors
)paren
id|die
(paren
l_string|&quot;renaming %s failed: %s&quot;
comma
id|source
(braket
id|i
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|modes
(braket
id|i
)braket
op_eq
id|WORKING_DIRECTORY
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cache_name_pos
c_func
(paren
id|source
(braket
id|i
)braket
comma
id|strlen
c_func
(paren
id|source
(braket
id|i
)braket
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|path_list_insert
c_func
(paren
id|source
(braket
id|i
)braket
comma
op_amp
id|deleted
)paren
suffix:semicolon
multiline_comment|/* destination can be a directory with 1 file inside */
r_if
c_cond
(paren
id|path_list_has_path
c_func
(paren
op_amp
id|overwritten
comma
id|destination
(braket
id|i
)braket
)paren
)paren
id|path_list_insert
c_func
(paren
id|destination
(braket
id|i
)braket
comma
op_amp
id|changed
)paren
suffix:semicolon
r_else
id|path_list_insert
c_func
(paren
id|destination
(braket
id|i
)braket
comma
op_amp
id|added
)paren
suffix:semicolon
)brace
r_else
id|path_list_insert
c_func
(paren
id|destination
(braket
id|i
)braket
comma
op_amp
id|added
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_only
)paren
(brace
id|show_list
c_func
(paren
l_string|&quot;Changed  : &quot;
comma
op_amp
id|changed
)paren
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;Adding   : &quot;
comma
op_amp
id|added
)paren
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;Deleting : &quot;
comma
op_amp
id|deleted
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|changed.nr
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
id|changed.items
(braket
id|i
)braket
dot
id|path
suffix:semicolon
r_int
id|i
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
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
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;Huh? Cache entry for %s unknown?&quot;
comma
id|path
)paren
suffix:semicolon
id|refresh_cache_entry
c_func
(paren
id|ce
comma
l_int|0
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
id|added.nr
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
id|added.items
(braket
id|i
)braket
dot
id|path
suffix:semicolon
id|add_file_to_index
c_func
(paren
id|path
comma
id|verbose
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
id|deleted.nr
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
id|deleted.items
(braket
id|i
)braket
dot
id|path
suffix:semicolon
id|remove_file_from_cache
c_func
(paren
id|path
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
