multiline_comment|/*&n; * &quot;diff --no-index&quot; support&n; * Copyright (c) 2007 by Johannes Schindelin&n; * Copyright (c) 2008 by Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;string-list.h&quot;
DECL|function|read_directory
r_static
r_int
id|read_directory
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|string_list
op_star
id|list
)paren
(brace
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|e
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open directory %s&quot;
comma
id|path
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|e
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
l_string|&quot;.&quot;
comma
id|e-&gt;d_name
)paren
op_logical_and
id|strcmp
c_func
(paren
l_string|&quot;..&quot;
comma
id|e-&gt;d_name
)paren
)paren
id|string_list_insert
c_func
(paren
id|list
comma
id|e-&gt;d_name
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_mode
r_static
r_int
id|get_mode
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
op_star
id|mode
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;/dev/null&quot;
)paren
)paren
op_star
id|mode
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef _WIN32
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|path
comma
l_string|&quot;nul&quot;
)paren
)paren
op_star
id|mode
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-&quot;
)paren
)paren
op_star
id|mode
op_assign
id|create_ce_mode
c_func
(paren
l_int|0666
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not access &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
r_else
op_star
id|mode
op_assign
id|st.st_mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|queue_diff
r_static
r_int
id|queue_diff
c_func
(paren
r_struct
id|diff_options
op_star
id|o
comma
r_const
r_char
op_star
id|name1
comma
r_const
r_char
op_star
id|name2
)paren
(brace
r_int
id|mode1
op_assign
l_int|0
comma
id|mode2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_mode
c_func
(paren
id|name1
comma
op_amp
id|mode1
)paren
op_logical_or
id|get_mode
c_func
(paren
id|name2
comma
op_amp
id|mode2
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mode1
op_logical_and
id|mode2
op_logical_and
id|S_ISDIR
c_func
(paren
id|mode1
)paren
op_ne
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;file/directory conflict: %s, %s&quot;
comma
id|name1
comma
id|name2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
(brace
r_struct
id|strbuf
id|buffer1
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|buffer2
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|string_list
id|p1
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|string_list
id|p2
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_int
id|i1
comma
id|i2
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|len1
op_assign
l_int|0
comma
id|len2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|name1
op_logical_and
id|read_directory
c_func
(paren
id|name1
comma
op_amp
id|p1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|name2
op_logical_and
id|read_directory
c_func
(paren
id|name2
comma
op_amp
id|p2
)paren
)paren
(brace
id|string_list_clear
c_func
(paren
op_amp
id|p1
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name1
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|buffer1
comma
id|name1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer1.len
op_logical_and
id|buffer1.buf
(braket
id|buffer1.len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|buffer1
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|len1
op_assign
id|buffer1.len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name2
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|buffer2
comma
id|name2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer2.len
op_logical_and
id|buffer2.buf
(braket
id|buffer2.len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|buffer2
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|len2
op_assign
id|buffer2.len
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i1
op_assign
id|i2
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|ret
op_logical_and
(paren
id|i1
OL
id|p1.nr
op_logical_or
id|i2
OL
id|p2.nr
)paren
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|n1
comma
op_star
id|n2
suffix:semicolon
r_int
id|comp
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|buffer1
comma
id|len1
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|buffer2
comma
id|len2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i1
op_eq
id|p1.nr
)paren
id|comp
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i2
op_eq
id|p2.nr
)paren
id|comp
op_assign
l_int|1
suffix:semicolon
r_else
id|comp
op_assign
id|strcmp
c_func
(paren
id|p1.items
(braket
id|i1
)braket
dot
id|string
comma
id|p2.items
(braket
id|i2
)braket
dot
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|comp
OG
l_int|0
)paren
id|n1
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|buffer1
comma
id|p1.items
(braket
id|i1
op_increment
)braket
dot
id|string
)paren
suffix:semicolon
id|n1
op_assign
id|buffer1.buf
suffix:semicolon
)brace
r_if
c_cond
(paren
id|comp
OL
l_int|0
)paren
id|n2
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|buffer2
comma
id|p2.items
(braket
id|i2
op_increment
)braket
dot
id|string
)paren
suffix:semicolon
id|n2
op_assign
id|buffer2.buf
suffix:semicolon
)brace
id|ret
op_assign
id|queue_diff
c_func
(paren
id|o
comma
id|n1
comma
id|n2
)paren
suffix:semicolon
)brace
id|string_list_clear
c_func
(paren
op_amp
id|p1
comma
l_int|0
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|p2
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer1
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer2
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_else
(brace
r_struct
id|diff_filespec
op_star
id|d1
comma
op_star
id|d2
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|o
comma
id|REVERSE_DIFF
)paren
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_const
r_char
op_star
id|tmp_c
suffix:semicolon
id|tmp
op_assign
id|mode1
suffix:semicolon
id|mode1
op_assign
id|mode2
suffix:semicolon
id|mode2
op_assign
id|tmp
suffix:semicolon
id|tmp_c
op_assign
id|name1
suffix:semicolon
id|name1
op_assign
id|name2
suffix:semicolon
id|name2
op_assign
id|tmp_c
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|name1
)paren
id|name1
op_assign
l_string|&quot;/dev/null&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name2
)paren
id|name2
op_assign
l_string|&quot;/dev/null&quot;
suffix:semicolon
id|d1
op_assign
id|alloc_filespec
c_func
(paren
id|name1
)paren
suffix:semicolon
id|d2
op_assign
id|alloc_filespec
c_func
(paren
id|name2
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|d1
comma
id|null_sha1
comma
id|mode1
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|d2
comma
id|null_sha1
comma
id|mode2
)paren
suffix:semicolon
id|diff_queue
c_func
(paren
op_amp
id|diff_queued_diff
comma
id|d1
comma
id|d2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|path_outside_repo
r_static
r_int
id|path_outside_repo
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_const
r_char
op_star
id|work_tree
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_absolute_path
c_func
(paren
id|path
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|work_tree
op_assign
id|get_git_work_tree
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|work_tree
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|work_tree
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|path
comma
id|work_tree
comma
id|len
)paren
op_logical_or
(paren
id|path
(braket
id|len
)braket
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
id|path
(braket
id|len
)braket
op_ne
l_char|&squot;/&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_no_index
r_void
id|diff_no_index
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_int
id|nongit
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|no_index
op_assign
l_int|0
suffix:semicolon
r_int
id|options
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Were we asked to do --no-index explicitly? */
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
id|argv
(braket
id|i
)braket
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
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--no-index&quot;
)paren
)paren
id|no_index
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
id|i
)braket
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|no_index
op_logical_and
op_logical_neg
id|nongit
)paren
(brace
multiline_comment|/*&n;&t;&t; * Inside a git repository, without --no-index.  Only&n;&t;&t; * when a path outside the repository is given,&n;&t;&t; * e.g. &quot;git diff /var/tmp/[12]&quot;, or &quot;git diff&n;&t;&t; * Makefile /var/tmp/Makefile&quot;, allow it to be used as&n;&t;&t; * a colourful &quot;diff&quot; replacement.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|argc
op_ne
id|i
op_plus
l_int|2
)paren
op_logical_or
(paren
op_logical_neg
id|path_outside_repo
c_func
(paren
id|argv
(braket
id|i
)braket
)paren
op_logical_and
op_logical_neg
id|path_outside_repo
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
id|i
op_plus
l_int|2
)paren
id|usagef
c_func
(paren
l_string|&quot;git diff %s &lt;path&gt; &lt;path&gt;&quot;
comma
id|no_index
ques
c_cond
l_string|&quot;--no-index&quot;
suffix:colon
l_string|&quot;[--no-index]&quot;
)paren
suffix:semicolon
id|diff_setup
c_func
(paren
op_amp
id|revs-&gt;diffopt
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
l_int|2
suffix:semicolon
)paren
(brace
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--no-index&quot;
)paren
)paren
id|i
op_increment
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
id|i
)braket
comma
l_string|&quot;-q&quot;
)paren
)paren
(brace
id|options
op_or_assign
id|DIFF_SILENT_ON_REMOVED
suffix:semicolon
id|i
op_increment
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
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
id|i
op_increment
suffix:semicolon
r_else
(brace
id|j
op_assign
id|diff_opt_parse
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|argv
op_plus
id|i
comma
id|argc
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|j
)paren
id|die
c_func
(paren
l_string|&quot;invalid diff option/value: %s&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_add_assign
id|j
suffix:semicolon
)brace
)brace
id|setup_diff_pager
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
r_const
r_char
op_star
id|paths
(braket
l_int|3
)braket
suffix:semicolon
id|memset
c_func
(paren
id|paths
comma
l_int|0
comma
r_sizeof
(paren
id|paths
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|argv
(braket
id|argc
l_int|2
op_plus
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * stdin should be spelled as &squot;-&squot;; if you have&n;&t;&t;&t; * path that is &squot;-&squot;, spell it as ./-.&n;&t;&t;&t; */
id|p
op_assign
(paren
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;-&quot;
)paren
ques
c_cond
id|xstrdup
c_func
(paren
id|prefix_filename
c_func
(paren
id|prefix
comma
id|len
comma
id|p
)paren
)paren
suffix:colon
id|p
)paren
suffix:semicolon
id|paths
(braket
id|i
)braket
op_assign
id|p
suffix:semicolon
)brace
id|diff_tree_setup_paths
c_func
(paren
id|paths
comma
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
)brace
r_else
id|diff_tree_setup_paths
c_func
(paren
id|argv
op_plus
id|argc
l_int|2
comma
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|revs-&gt;diffopt.skip_stat_unmatch
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;diffopt.output_format
)paren
id|revs-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|EXIT_WITH_STATUS
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|NO_INDEX
)paren
suffix:semicolon
id|revs-&gt;max_count
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|diff_setup_done
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;diff_setup_done failed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|queue_diff
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|revs-&gt;diffopt.pathspec.raw
(braket
l_int|0
)braket
comma
id|revs-&gt;diffopt.pathspec.raw
(braket
l_int|1
)braket
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
id|diff_set_mnemonic_prefix
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
l_string|&quot;1/&quot;
comma
l_string|&quot;2/&quot;
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The return code for --no-index imitates diff(1):&n;&t; * 0 = no changes, 1 = changes, else error&n;&t; */
m_exit
(paren
id|revs-&gt;diffopt.found_changes
)paren
suffix:semicolon
)brace
eof
