multiline_comment|/*&n; * This merges the file listing in the directory cache index&n; * with the actual working directory list, and shows different&n; * combinations of the two.&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &lt;fnmatch.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|variable|show_deleted
r_static
r_int
id|show_deleted
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_cached
r_static
r_int
id|show_cached
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_others
r_static
r_int
id|show_others
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_ignored
r_static
r_int
id|show_ignored
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_stage
r_static
r_int
id|show_stage
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_unmerged
r_static
r_int
id|show_unmerged
op_assign
l_int|0
suffix:semicolon
DECL|variable|line_terminator
r_static
r_int
id|line_terminator
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|tag_cached
r_static
r_const
r_char
op_star
id|tag_cached
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_unmerged
r_static
r_const
r_char
op_star
id|tag_unmerged
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_removed
r_static
r_const
r_char
op_star
id|tag_removed
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_other
r_static
r_const
r_char
op_star
id|tag_other
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|nr_excludes
r_static
r_int
id|nr_excludes
suffix:semicolon
DECL|variable|excludes
r_static
r_const
r_char
op_star
op_star
id|excludes
suffix:semicolon
DECL|variable|excludes_alloc
r_static
r_int
id|excludes_alloc
suffix:semicolon
DECL|function|add_exclude
r_static
r_void
id|add_exclude
c_func
(paren
r_const
r_char
op_star
id|string
)paren
(brace
r_if
c_cond
(paren
id|nr_excludes
op_eq
id|excludes_alloc
)paren
(brace
id|excludes_alloc
op_assign
id|alloc_nr
c_func
(paren
id|excludes_alloc
)paren
suffix:semicolon
id|excludes
op_assign
id|realloc
c_func
(paren
id|excludes
comma
id|excludes_alloc
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
)brace
id|excludes
(braket
id|nr_excludes
op_increment
)braket
op_assign
id|string
suffix:semicolon
)brace
DECL|function|add_excludes_from_file
r_static
r_void
id|add_excludes_from_file
c_func
(paren
r_const
r_char
op_star
id|fname
)paren
(brace
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
)paren
r_goto
id|err
suffix:semicolon
id|size
op_assign
id|lseek
c_func
(paren
id|fd
comma
l_int|0
comma
id|SEEK_END
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
id|lseek
c_func
(paren
id|fd
comma
l_int|0
comma
id|SEEK_SET
)paren
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
suffix:semicolon
)brace
id|buf
op_assign
id|xmalloc
c_func
(paren
id|size
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
)paren
(brace
id|buf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|add_exclude
c_func
(paren
id|entry
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
suffix:semicolon
id|err
suffix:colon
id|perror
c_func
(paren
id|fname
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|excluded
r_static
r_int
id|excluded
c_func
(paren
r_const
r_char
op_star
id|pathname
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|nr_excludes
)paren
(brace
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_excludes
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|fnmatch
c_func
(paren
id|excludes
(braket
id|i
)braket
comma
id|basename
comma
l_int|0
)paren
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dir
r_static
r_const
r_char
op_star
op_star
id|dir
suffix:semicolon
DECL|variable|nr_dir
r_static
r_int
id|nr_dir
suffix:semicolon
DECL|variable|dir_alloc
r_static
r_int
id|dir_alloc
suffix:semicolon
DECL|function|add_name
r_static
r_void
id|add_name
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|name
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
id|nr_dir
op_eq
id|dir_alloc
)paren
(brace
id|dir_alloc
op_assign
id|alloc_nr
c_func
(paren
id|dir_alloc
)paren
suffix:semicolon
id|dir
op_assign
id|xrealloc
c_func
(paren
id|dir
comma
id|dir_alloc
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
)brace
id|name
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|name
comma
id|pathname
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|dir
(braket
id|nr_dir
op_increment
)braket
op_assign
id|name
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a directory tree. We currently ignore anything but&n; * directories, regular files and symlinks. That&squot;s because git&n; * doesn&squot;t handle them at all yet. Maybe that will change some&n; * day.&n; *&n; * Also, we currently ignore all names starting with a dot.&n; * That likely will not change.&n; */
DECL|function|read_directory
r_static
r_void
id|read_directory
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
id|base
comma
r_int
id|baselen
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_char
id|fullname
(braket
id|MAXPATHLEN
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
r_while
c_loop
(paren
(paren
id|de
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
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|excluded
c_func
(paren
id|de-&gt;d_name
)paren
op_ne
id|show_ignored
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
id|read_directory
c_func
(paren
id|fullname
comma
id|fullname
comma
id|baselen
op_plus
id|len
op_plus
l_int|1
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
id|add_name
c_func
(paren
id|fullname
comma
id|baselen
op_plus
id|len
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
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
r_char
op_star
id|n1
op_assign
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|p1
suffix:semicolon
r_const
r_char
op_star
id|n2
op_assign
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|p2
suffix:semicolon
r_int
id|l1
op_assign
id|strlen
c_func
(paren
id|n1
)paren
comma
id|l2
op_assign
id|strlen
c_func
(paren
id|n2
)paren
suffix:semicolon
r_return
id|cache_name_compare
c_func
(paren
id|n1
comma
id|l1
comma
id|n2
comma
id|l2
)paren
suffix:semicolon
)brace
DECL|function|show_files
r_static
r_void
id|show_files
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* For cached/deleted files we don&squot;t need to even do the readdir */
r_if
c_cond
(paren
id|show_others
)paren
(brace
id|read_directory
c_func
(paren
l_string|&quot;.&quot;
comma
l_string|&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|dir
comma
id|nr_dir
comma
r_sizeof
(paren
r_char
op_star
)paren
comma
id|cmp_name
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
id|nr_dir
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s%c&quot;
comma
id|tag_other
comma
id|dir
(braket
id|i
)braket
comma
id|line_terminator
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_cached
op_or
id|show_stage
)paren
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
id|excluded
c_func
(paren
id|ce-&gt;name
)paren
op_ne
id|show_ignored
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|show_unmerged
op_logical_and
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_stage
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s%c&quot;
comma
id|ce_stage
c_func
(paren
id|ce
)paren
ques
c_cond
id|tag_unmerged
suffix:colon
id|tag_cached
comma
id|ce-&gt;name
comma
id|line_terminator
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s%06o %s %d %s%c&quot;
comma
id|ce_stage
c_func
(paren
id|ce
)paren
ques
c_cond
id|tag_unmerged
suffix:colon
id|tag_cached
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
comma
id|ce_stage
c_func
(paren
id|ce
)paren
comma
id|ce-&gt;name
comma
id|line_terminator
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|show_deleted
)paren
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
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|excluded
c_func
(paren
id|ce-&gt;name
)paren
op_ne
id|show_ignored
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s%s%c&quot;
comma
id|tag_removed
comma
id|ce-&gt;name
comma
id|line_terminator
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|ls_files_usage
r_static
r_const
r_char
op_star
id|ls_files_usage
op_assign
l_string|&quot;ls-files [-z] [-t] (--[cached|deleted|others|stage|unmerged])* &quot;
l_string|&quot;[ --ignored [--exclude=&lt;pattern&gt;] [--exclude-from=&lt;file&gt;) ]&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
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
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_terminator
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-t&quot;
)paren
)paren
(brace
id|tag_cached
op_assign
l_string|&quot;H &quot;
suffix:semicolon
id|tag_unmerged
op_assign
l_string|&quot;M &quot;
suffix:semicolon
id|tag_removed
op_assign
l_string|&quot;R &quot;
suffix:semicolon
id|tag_other
op_assign
l_string|&quot;? &quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-c&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--cached&quot;
)paren
)paren
(brace
id|show_cached
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-d&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--deleted&quot;
)paren
)paren
(brace
id|show_deleted
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-o&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--others&quot;
)paren
)paren
(brace
id|show_others
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-i&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--ignored&quot;
)paren
)paren
(brace
id|show_ignored
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-s&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stage&quot;
)paren
)paren
(brace
id|show_stage
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-u&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--unmerged&quot;
)paren
)paren
(brace
multiline_comment|/* There&squot;s no point in showing unmerged unless&n;&t;&t;&t; * you also show the stage information.&n;&t;&t;&t; */
id|show_stage
op_assign
l_int|1
suffix:semicolon
id|show_unmerged
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-x&quot;
)paren
op_logical_and
id|i
op_plus
l_int|1
OL
id|argc
)paren
(brace
id|add_exclude
c_func
(paren
id|argv
(braket
op_increment
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--exclude=&quot;
comma
l_int|10
)paren
)paren
(brace
id|add_exclude
c_func
(paren
id|arg
op_plus
l_int|10
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-X&quot;
)paren
op_logical_and
id|i
op_plus
l_int|1
OL
id|argc
)paren
(brace
id|add_excludes_from_file
c_func
(paren
id|argv
(braket
op_increment
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--exclude-from=&quot;
comma
l_int|15
)paren
)paren
(brace
id|add_excludes_from_file
c_func
(paren
id|arg
op_plus
l_int|15
)paren
suffix:semicolon
)brace
r_else
id|usage
c_func
(paren
id|ls_files_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_ignored
op_logical_and
op_logical_neg
id|nr_excludes
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: --ignored needs some exclude pattern&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* With no flags, we default to showing the cached files */
r_if
c_cond
(paren
op_logical_neg
(paren
id|show_stage
op_or
id|show_deleted
op_or
id|show_others
op_or
id|show_unmerged
)paren
)paren
id|show_cached
op_assign
l_int|1
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
id|show_files
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
