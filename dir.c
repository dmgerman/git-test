multiline_comment|/*&n; * This handles recursive filename detection with exclude&n; * files, index knowledge etc..&n; *&n; * Copyright (C) Linus Torvalds, 2005-2006&n; *&t;&t; Junio Hamano, 2005-2006&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
DECL|function|common_prefix
r_int
id|common_prefix
c_func
(paren
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
id|slash
comma
op_star
id|next
suffix:semicolon
r_int
id|prefix
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathspec
)paren
r_return
l_int|0
suffix:semicolon
id|path
op_assign
op_star
id|pathspec
suffix:semicolon
id|slash
op_assign
id|strrchr
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slash
)paren
r_return
l_int|0
suffix:semicolon
id|prefix
op_assign
id|slash
id|path
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|next
op_assign
op_star
op_increment
id|pathspec
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|prefix
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|path
comma
id|next
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|next
(braket
op_decrement
id|len
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|path
comma
id|next
comma
id|len
op_plus
l_int|1
)paren
)paren
r_continue
suffix:semicolon
id|prefix
op_assign
id|len
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|prefix
suffix:semicolon
)brace
multiline_comment|/*&n; * Does &squot;match&squot; matches the given name?&n; * A match is found if&n; *&n; * (1) the &squot;match&squot; string is leading directory of &squot;name&squot;, or&n; * (2) the &squot;match&squot; string is a wildcard and matches &squot;name&squot;, or&n; * (3) the &squot;match&squot; string is exactly the same as &squot;name&squot;.&n; *&n; * and the return value tells which case it was.&n; *&n; * It returns 0 when there is no match.&n; */
DECL|function|match_one
r_static
r_int
id|match_one
c_func
(paren
r_const
r_char
op_star
id|match
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
r_int
id|matchlen
suffix:semicolon
multiline_comment|/* If the match was just the prefix, we matched */
id|matchlen
op_assign
id|strlen
c_func
(paren
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|matchlen
)paren
r_return
id|MATCHED_RECURSIVELY
suffix:semicolon
multiline_comment|/*&n;&t; * If we don&squot;t match the matchstring exactly,&n;&t; * we need to match by fnmatch&n;&t; */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|match
comma
id|name
comma
id|matchlen
)paren
)paren
r_return
op_logical_neg
id|fnmatch
c_func
(paren
id|match
comma
id|name
comma
l_int|0
)paren
ques
c_cond
id|MATCHED_FNMATCH
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
(braket
id|matchlen
)braket
)paren
r_return
id|MATCHED_EXACTLY
suffix:semicolon
r_if
c_cond
(paren
id|match
(braket
id|matchlen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
id|name
(braket
id|matchlen
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|MATCHED_RECURSIVELY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a name and a list of pathspecs, see if the name matches&n; * any of the pathspecs.  The caller is also interested in seeing&n; * all pathspec matches some names it calls this function with&n; * (otherwise the user could have mistyped the unmatched pathspec),&n; * and a mark is left in seen[] array for pathspec element that&n; * actually matched anything.&n; */
DECL|function|match_pathspec
r_int
id|match_pathspec
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_int
id|prefix
comma
r_char
op_star
id|seen
)paren
(brace
r_int
id|retval
suffix:semicolon
r_const
r_char
op_star
id|match
suffix:semicolon
id|name
op_add_assign
id|prefix
suffix:semicolon
id|namelen
op_sub_assign
id|prefix
suffix:semicolon
r_for
c_loop
(paren
id|retval
op_assign
l_int|0
suffix:semicolon
(paren
id|match
op_assign
op_star
id|pathspec
op_increment
)paren
op_ne
l_int|NULL
suffix:semicolon
id|seen
op_increment
)paren
(brace
r_int
id|how
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_logical_and
op_star
id|seen
op_eq
id|MATCHED_EXACTLY
)paren
r_continue
suffix:semicolon
id|match
op_add_assign
id|prefix
suffix:semicolon
id|how
op_assign
id|match_one
c_func
(paren
id|match
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|how
)paren
(brace
r_if
c_cond
(paren
id|retval
OL
id|how
)paren
id|retval
op_assign
id|how
suffix:semicolon
r_if
c_cond
(paren
op_star
id|seen
OL
id|how
)paren
op_star
id|seen
op_assign
id|how
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|add_exclude
r_void
id|add_exclude
c_func
(paren
r_const
r_char
op_star
id|string
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_struct
id|exclude_list
op_star
id|which
)paren
(brace
r_struct
id|exclude
op_star
id|x
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|x
)paren
)paren
suffix:semicolon
id|x-&gt;pattern
op_assign
id|string
suffix:semicolon
id|x-&gt;base
op_assign
id|base
suffix:semicolon
id|x-&gt;baselen
op_assign
id|baselen
suffix:semicolon
r_if
c_cond
(paren
id|which-&gt;nr
op_eq
id|which-&gt;alloc
)paren
(brace
id|which-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|which-&gt;alloc
)paren
suffix:semicolon
id|which-&gt;excludes
op_assign
id|xrealloc
c_func
(paren
id|which-&gt;excludes
comma
id|which-&gt;alloc
op_star
r_sizeof
(paren
id|x
)paren
)paren
suffix:semicolon
)brace
id|which-&gt;excludes
(braket
id|which-&gt;nr
op_increment
)braket
op_assign
id|x
suffix:semicolon
)brace
DECL|function|add_excludes_from_file_1
r_static
r_int
id|add_excludes_from_file_1
c_func
(paren
r_const
r_char
op_star
id|fname
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_struct
id|exclude_list
op_star
id|which
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|fd
comma
id|i
suffix:semicolon
r_int
id|size
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|entry
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|fname
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
op_logical_or
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
id|size
op_assign
id|st.st_size
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|buf
op_assign
id|xmalloc
c_func
(paren
id|size
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
id|buf
comma
id|size
)paren
op_ne
id|size
)paren
r_goto
id|err
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|buf
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|entry
op_assign
id|buf
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
id|entry
op_ne
id|buf
op_plus
id|i
op_logical_and
id|entry
(braket
l_int|0
)braket
op_ne
l_char|&squot;#&squot;
)paren
(brace
id|buf
(braket
id|i
(paren
id|i
op_logical_and
id|buf
(braket
id|i
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)braket
op_assign
l_int|0
suffix:semicolon
id|add_exclude
c_func
(paren
id|entry
comma
id|base
comma
id|baselen
comma
id|which
)paren
suffix:semicolon
)brace
id|entry
op_assign
id|buf
op_plus
id|i
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
r_if
c_cond
(paren
l_int|0
op_le
id|fd
)paren
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|add_excludes_from_file
r_void
id|add_excludes_from_file
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
id|fname
)paren
(brace
r_if
c_cond
(paren
id|add_excludes_from_file_1
c_func
(paren
id|fname
comma
l_string|&quot;&quot;
comma
l_int|0
comma
op_amp
id|dir-&gt;exclude_list
(braket
id|EXC_FILE
)braket
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;cannot use %s as an exclude file&quot;
comma
id|fname
)paren
suffix:semicolon
)brace
DECL|function|push_exclude_per_directory
r_int
id|push_exclude_per_directory
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
id|base
comma
r_int
id|baselen
)paren
(brace
r_char
id|exclude_file
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|exclude_list
op_star
id|el
op_assign
op_amp
id|dir-&gt;exclude_list
(braket
id|EXC_DIRS
)braket
suffix:semicolon
r_int
id|current_nr
op_assign
id|el-&gt;nr
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;exclude_per_dir
)paren
(brace
id|memcpy
c_func
(paren
id|exclude_file
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|exclude_file
op_plus
id|baselen
comma
id|dir-&gt;exclude_per_dir
)paren
suffix:semicolon
id|add_excludes_from_file_1
c_func
(paren
id|exclude_file
comma
id|base
comma
id|baselen
comma
id|el
)paren
suffix:semicolon
)brace
r_return
id|current_nr
suffix:semicolon
)brace
DECL|function|pop_exclude_per_directory
r_void
id|pop_exclude_per_directory
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_int
id|stk
)paren
(brace
r_struct
id|exclude_list
op_star
id|el
op_assign
op_amp
id|dir-&gt;exclude_list
(braket
id|EXC_DIRS
)braket
suffix:semicolon
r_while
c_loop
(paren
id|stk
OL
id|el-&gt;nr
)paren
id|free
c_func
(paren
id|el-&gt;excludes
(braket
op_decrement
id|el-&gt;nr
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Scan the list and let the last match determines the fate.&n; * Return 1 for exclude, 0 for include and -1 for undecided.&n; */
DECL|function|excluded_1
r_static
r_int
id|excluded_1
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
id|pathlen
comma
r_struct
id|exclude_list
op_star
id|el
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|el-&gt;nr
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|el-&gt;nr
l_int|1
suffix:semicolon
l_int|0
op_le
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_struct
id|exclude
op_star
id|x
op_assign
id|el-&gt;excludes
(braket
id|i
)braket
suffix:semicolon
r_const
r_char
op_star
id|exclude
op_assign
id|x-&gt;pattern
suffix:semicolon
r_int
id|to_exclude
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|exclude
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|to_exclude
op_assign
l_int|0
suffix:semicolon
id|exclude
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
id|exclude
comma
l_char|&squot;/&squot;
)paren
)paren
(brace
multiline_comment|/* match basename */
r_const
r_char
op_star
id|basename
op_assign
id|strrchr
c_func
(paren
id|pathname
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|basename
op_assign
(paren
id|basename
)paren
ques
c_cond
id|basename
op_plus
l_int|1
suffix:colon
id|pathname
suffix:semicolon
r_if
c_cond
(paren
id|fnmatch
c_func
(paren
id|exclude
comma
id|basename
comma
l_int|0
)paren
op_eq
l_int|0
)paren
r_return
id|to_exclude
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* match with FNM_PATHNAME:&n;&t;&t;&t;&t; * exclude has base (baselen long) implicitly&n;&t;&t;&t;&t; * in front of it.&n;&t;&t;&t;&t; */
r_int
id|baselen
op_assign
id|x-&gt;baselen
suffix:semicolon
r_if
c_cond
(paren
op_star
id|exclude
op_eq
l_char|&squot;/&squot;
)paren
id|exclude
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OL
id|baselen
op_logical_or
(paren
id|baselen
op_logical_and
id|pathname
(braket
id|baselen
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
op_logical_or
id|strncmp
c_func
(paren
id|pathname
comma
id|x-&gt;base
comma
id|baselen
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|fnmatch
c_func
(paren
id|exclude
comma
id|pathname
op_plus
id|baselen
comma
id|FNM_PATHNAME
)paren
op_eq
l_int|0
)paren
r_return
id|to_exclude
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* undecided */
)brace
DECL|function|excluded
r_int
id|excluded
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
id|pathname
)paren
(brace
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|pathname
)paren
suffix:semicolon
r_int
id|st
suffix:semicolon
r_for
c_loop
(paren
id|st
op_assign
id|EXC_CMDL
suffix:semicolon
id|st
op_le
id|EXC_FILE
suffix:semicolon
id|st
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|excluded_1
c_func
(paren
id|pathname
comma
id|pathlen
comma
op_amp
id|dir-&gt;exclude_list
(braket
id|st
)braket
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_name
r_static
r_void
id|add_name
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
id|pathname
comma
r_int
id|len
)paren
(brace
r_struct
id|dir_entry
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
id|cache_name_pos
c_func
(paren
id|pathname
comma
id|len
)paren
op_ge
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;nr
op_eq
id|dir-&gt;alloc
)paren
(brace
r_int
id|alloc
op_assign
id|alloc_nr
c_func
(paren
id|dir-&gt;alloc
)paren
suffix:semicolon
id|dir-&gt;alloc
op_assign
id|alloc
suffix:semicolon
id|dir-&gt;entries
op_assign
id|xrealloc
c_func
(paren
id|dir-&gt;entries
comma
id|alloc
op_star
r_sizeof
(paren
id|ent
)paren
)paren
suffix:semicolon
)brace
id|ent
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ent
)paren
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|ent-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|pathname
comma
id|len
)paren
suffix:semicolon
id|ent-&gt;name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;entries
(braket
id|dir-&gt;nr
op_increment
)braket
op_assign
id|ent
suffix:semicolon
)brace
DECL|function|dir_exists
r_static
r_int
id|dir_exists
c_func
(paren
r_const
r_char
op_star
id|dirname
comma
r_int
id|len
)paren
(brace
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|dirname
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|active_nr
)paren
multiline_comment|/* can&squot;t */
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|strncmp
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|dirname
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a directory tree. We currently ignore anything but&n; * directories, regular files and symlinks. That&squot;s because git&n; * doesn&squot;t handle them at all yet. Maybe that will change some&n; * day.&n; *&n; * Also, we ignore the name &quot;.git&quot; (even if it is not a directory).&n; * That likely will not change.&n; */
DECL|function|read_directory_recursive
r_static
r_int
id|read_directory_recursive
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
id|path
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_int
id|check_only
)paren
(brace
id|DIR
op_star
id|fdir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_int
id|contents
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fdir
)paren
(brace
r_int
id|exclude_stk
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_char
id|fullname
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|fullname
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|exclude_stk
op_assign
id|push_exclude_per_directory
c_func
(paren
id|dir
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|fdir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_int|0
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|de-&gt;d_name
op_plus
l_int|1
comma
l_string|&quot;.&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|de-&gt;d_name
op_plus
l_int|1
comma
l_string|&quot;git&quot;
)paren
)paren
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fullname
op_plus
id|baselen
comma
id|de-&gt;d_name
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|excluded
c_func
(paren
id|dir
comma
id|fullname
)paren
op_ne
id|dir-&gt;show_ignored
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;show_ignored
op_logical_or
id|DTYPE
c_func
(paren
id|de
)paren
op_ne
id|DT_DIR
)paren
(brace
r_continue
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|DTYPE
c_func
(paren
id|de
)paren
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
r_case
id|DT_UNKNOWN
suffix:colon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|fullname
comma
op_amp
id|st
)paren
)paren
r_continue
suffix:semicolon
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
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
id|DT_DIR
suffix:colon
id|memcpy
c_func
(paren
id|fullname
op_plus
id|baselen
op_plus
id|len
comma
l_string|&quot;/&quot;
comma
l_int|2
)paren
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;show_other_directories
op_logical_and
op_logical_neg
id|dir_exists
c_func
(paren
id|fullname
comma
id|baselen
op_plus
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
id|dir-&gt;hide_empty_directories
op_logical_and
op_logical_neg
id|read_directory_recursive
c_func
(paren
id|dir
comma
id|fullname
comma
id|fullname
comma
id|baselen
op_plus
id|len
comma
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
id|contents
op_add_assign
id|read_directory_recursive
c_func
(paren
id|dir
comma
id|fullname
comma
id|fullname
comma
id|baselen
op_plus
id|len
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|DT_REG
suffix:colon
r_case
id|DT_LNK
suffix:colon
r_break
suffix:semicolon
)brace
id|contents
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|check_only
)paren
r_goto
id|exit_early
suffix:semicolon
r_else
id|add_name
c_func
(paren
id|dir
comma
id|fullname
comma
id|baselen
op_plus
id|len
)paren
suffix:semicolon
)brace
id|exit_early
suffix:colon
id|closedir
c_func
(paren
id|fdir
)paren
suffix:semicolon
id|pop_exclude_per_directory
c_func
(paren
id|dir
comma
id|exclude_stk
)paren
suffix:semicolon
)brace
r_return
id|contents
suffix:semicolon
)brace
DECL|function|cmp_name
r_static
r_int
id|cmp_name
c_func
(paren
r_const
r_void
op_star
id|p1
comma
r_const
r_void
op_star
id|p2
)paren
(brace
r_const
r_struct
id|dir_entry
op_star
id|e1
op_assign
op_star
(paren
r_const
r_struct
id|dir_entry
op_star
op_star
)paren
id|p1
suffix:semicolon
r_const
r_struct
id|dir_entry
op_star
id|e2
op_assign
op_star
(paren
r_const
r_struct
id|dir_entry
op_star
op_star
)paren
id|p2
suffix:semicolon
r_return
id|cache_name_compare
c_func
(paren
id|e1-&gt;name
comma
id|e1-&gt;len
comma
id|e2-&gt;name
comma
id|e2-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|read_directory
r_int
id|read_directory
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
id|path
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
)paren
(brace
multiline_comment|/*&n;&t; * Make sure to do the per-directory exclude for all the&n;&t; * directories leading up to our base.&n;&t; */
r_if
c_cond
(paren
id|baselen
)paren
(brace
r_if
c_cond
(paren
id|dir-&gt;exclude_per_dir
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|pp
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
id|pp
comma
id|base
comma
id|baselen
op_plus
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|pp
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
id|save
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
id|push_exclude_per_directory
c_func
(paren
id|dir
comma
id|pp
comma
id|p
op_minus
id|pp
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|save
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|save
)paren
r_break
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|p
op_increment
suffix:semicolon
r_else
id|p
op_assign
id|pp
op_plus
id|baselen
suffix:semicolon
)brace
id|free
c_func
(paren
id|pp
)paren
suffix:semicolon
)brace
)brace
id|read_directory_recursive
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
l_int|0
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|dir-&gt;entries
comma
id|dir-&gt;nr
comma
r_sizeof
(paren
r_struct
id|dir_entry
op_star
)paren
comma
id|cmp_name
)paren
suffix:semicolon
r_return
id|dir-&gt;nr
suffix:semicolon
)brace
r_int
DECL|function|file_exists
id|file_exists
c_func
(paren
r_const
r_char
op_star
id|f
)paren
(brace
r_struct
id|stat
id|sb
suffix:semicolon
r_return
id|stat
c_func
(paren
id|f
comma
op_amp
id|sb
)paren
op_eq
l_int|0
suffix:semicolon
)brace
eof
