multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;path-list.h&quot;
multiline_comment|/*&n; * diff-files&n; */
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
id|path_list
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
id|path_list_insert
c_func
(paren
id|xstrdup
c_func
(paren
id|e-&gt;d_name
)paren
comma
id|list
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
r_struct
id|stat
id|st
suffix:semicolon
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
id|name1
)paren
(brace
r_if
c_cond
(paren
id|stat
c_func
(paren
id|name1
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
id|name1
)paren
suffix:semicolon
id|mode1
op_assign
id|st.st_mode
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name2
)paren
(brace
r_if
c_cond
(paren
id|stat
c_func
(paren
id|name2
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
id|name2
)paren
suffix:semicolon
id|mode2
op_assign
id|st.st_mode
suffix:semicolon
)brace
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
r_char
id|buffer1
(braket
id|PATH_MAX
)braket
comma
id|buffer2
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|path_list
id|p1
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
id|p2
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_int
id|len1
op_assign
l_int|0
comma
id|len2
op_assign
l_int|0
comma
id|i1
comma
id|i2
comma
id|ret
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
id|path_list_clear
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
id|len1
op_assign
id|strlen
c_func
(paren
id|name1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len1
OG
l_int|0
op_logical_and
id|name1
(braket
id|len1
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len1
op_decrement
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer1
comma
id|name1
comma
id|len1
)paren
suffix:semicolon
id|buffer1
(braket
id|len1
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name2
)paren
(brace
id|len2
op_assign
id|strlen
c_func
(paren
id|name2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len2
OG
l_int|0
op_logical_and
id|name2
(braket
id|len2
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len2
op_decrement
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer2
comma
id|name2
comma
id|len2
)paren
suffix:semicolon
id|buffer2
(braket
id|len2
op_increment
)braket
op_assign
l_char|&squot;/&squot;
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
id|path
comma
id|p2.items
(braket
id|i2
)braket
dot
id|path
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
id|n1
op_assign
id|buffer1
suffix:semicolon
id|strncpy
c_func
(paren
id|buffer1
op_plus
id|len1
comma
id|p1.items
(braket
id|i1
op_increment
)braket
dot
id|path
comma
id|PATH_MAX
id|len1
)paren
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
id|n2
op_assign
id|buffer2
suffix:semicolon
id|strncpy
c_func
(paren
id|buffer2
op_plus
id|len2
comma
id|p2.items
(braket
id|i2
op_increment
)braket
dot
id|path
comma
id|PATH_MAX
id|len2
)paren
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
id|path_list_clear
c_func
(paren
op_amp
id|p1
comma
l_int|0
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|p2
comma
l_int|0
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
id|o-&gt;reverse_diff
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
DECL|function|is_in_index
r_static
r_int
id|is_in_index
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
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|len
)paren
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
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
id|path
comma
id|len
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|c
op_assign
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
(braket
id|len
)braket
suffix:semicolon
r_return
id|c
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|c
op_eq
l_char|&squot;/&squot;
suffix:semicolon
)brace
DECL|function|handle_diff_files_args
r_static
r_int
id|handle_diff_files_args
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
op_star
id|silent
)paren
(brace
op_star
id|silent
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* revs-&gt;max_count == -2 means --no-index */
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
l_string|&quot;--base&quot;
)paren
)paren
id|revs-&gt;max_count
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
l_string|&quot;--ours&quot;
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|2
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
l_string|&quot;--theirs&quot;
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|3
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
l_string|&quot;-n&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--no-index&quot;
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|2
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
l_string|&quot;-q&quot;
)paren
)paren
op_star
id|silent
op_assign
l_int|1
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;invalid option: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs-&gt;max_count
op_eq
l_int|1
op_logical_and
id|revs-&gt;diffopt.nr_paths
op_eq
l_int|2
)paren
(brace
multiline_comment|/*&n;&t;&t; * If two files are specified, and at least one is untracked,&n;&t;&t; * default to no-index.&n;&t;&t; */
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_in_index
c_func
(paren
id|revs-&gt;diffopt.paths
(braket
l_int|0
)braket
)paren
op_logical_or
op_logical_neg
id|is_in_index
c_func
(paren
id|revs-&gt;diffopt.paths
(braket
l_int|1
)braket
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure there are NO revision (i.e. pending object) parameter,&n;&t; * rev.max_count is reasonable (0 &lt;= n &lt;= 3),&n;&t; * there is no other revision filtering parameters.&n;&t; */
r_if
c_cond
(paren
id|revs-&gt;pending.nr
op_logical_or
id|revs-&gt;max_count
OG
l_int|3
op_logical_or
id|revs-&gt;min_age
op_ne
l_int|1
op_logical_or
id|revs-&gt;max_age
op_ne
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;no revision allowed with diff-files&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;max_count
op_eq
l_int|1
op_logical_and
(paren
id|revs-&gt;diffopt.output_format
op_amp
id|DIFF_FORMAT_PATCH
)paren
)paren
id|revs-&gt;combine_merges
op_assign
id|revs-&gt;dense_combined_merges
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|run_diff_files_cmd
r_int
id|run_diff_files_cmd
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
)paren
(brace
r_int
id|silent_on_removed
suffix:semicolon
r_if
c_cond
(paren
id|handle_diff_files_args
c_func
(paren
id|revs
comma
id|argc
comma
id|argv
comma
op_amp
id|silent_on_removed
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;max_count
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|revs-&gt;diffopt.nr_paths
op_ne
l_int|2
)paren
r_return
id|error
c_func
(paren
l_string|&quot;need two files/directories with --no-index&quot;
)paren
suffix:semicolon
id|queue_diff
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|revs-&gt;diffopt.paths
(braket
l_int|0
)braket
comma
id|revs-&gt;diffopt.paths
(braket
l_int|1
)braket
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
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|run_diff_files
c_func
(paren
id|revs
comma
id|silent_on_removed
)paren
suffix:semicolon
)brace
DECL|function|run_diff_files
r_int
id|run_diff_files
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|silent_on_removed
)paren
(brace
r_int
id|entries
comma
id|i
suffix:semicolon
r_int
id|diff_unmerged_stage
op_assign
id|revs-&gt;max_count
suffix:semicolon
r_if
c_cond
(paren
id|diff_unmerged_stage
OL
l_int|0
)paren
id|diff_unmerged_stage
op_assign
l_int|2
suffix:semicolon
id|entries
op_assign
id|active_nr
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
comma
id|newmode
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
id|revs-&gt;prune_data
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
r_struct
id|combine_diff_path
op_star
id|dpath
suffix:semicolon
r_int
id|num_compare_stages
op_assign
l_int|0
suffix:semicolon
r_int
id|path_len
suffix:semicolon
id|path_len
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
id|dpath
op_assign
id|xmalloc
(paren
id|combine_diff_path_size
(paren
l_int|5
comma
id|path_len
)paren
)paren
suffix:semicolon
id|dpath-&gt;path
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|dpath-&gt;parent
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|dpath-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|dpath-&gt;len
op_assign
id|path_len
suffix:semicolon
id|memcpy
c_func
(paren
id|dpath-&gt;path
comma
id|ce-&gt;name
comma
id|path_len
)paren
suffix:semicolon
id|dpath-&gt;path
(braket
id|path_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|dpath-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|hashclr
c_func
(paren
id|dpath-&gt;sha1
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
(paren
id|dpath-&gt;parent
(braket
l_int|0
)braket
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|combine_diff_parent
)paren
op_star
l_int|5
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|entries
)paren
(brace
r_struct
id|cache_entry
op_star
id|nce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_int
id|stage
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|nce-&gt;name
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Stage #2 (ours) is the first parent,&n;&t;&t;&t;&t; * stage #3 (theirs) is the second.&n;&t;&t;&t;&t; */
id|stage
op_assign
id|ce_stage
c_func
(paren
id|nce
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_le
id|stage
)paren
(brace
r_int
id|mode
op_assign
id|ntohl
c_func
(paren
id|nce-&gt;ce_mode
)paren
suffix:semicolon
id|num_compare_stages
op_increment
suffix:semicolon
id|hashcpy
c_func
(paren
id|dpath-&gt;parent
(braket
id|stage
op_minus
l_int|2
)braket
dot
id|sha1
comma
id|nce-&gt;sha1
)paren
suffix:semicolon
id|dpath-&gt;parent
(braket
id|stage
op_minus
l_int|2
)braket
dot
id|mode
op_assign
id|canon_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|dpath-&gt;parent
(braket
id|stage
op_minus
l_int|2
)braket
dot
id|status
op_assign
id|DIFF_STATUS_MODIFIED
suffix:semicolon
)brace
multiline_comment|/* diff against the proper unmerged stage */
r_if
c_cond
(paren
id|stage
op_eq
id|diff_unmerged_stage
)paren
id|ce
op_assign
id|nce
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Compensate for loop update&n;&t;&t;&t; */
id|i
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;combine_merges
op_logical_and
id|num_compare_stages
op_eq
l_int|2
)paren
(brace
id|show_combined_diff
c_func
(paren
id|dpath
comma
l_int|2
comma
id|revs-&gt;dense_combined_merges
comma
id|revs
)paren
suffix:semicolon
id|free
c_func
(paren
id|dpath
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|free
c_func
(paren
id|dpath
)paren
suffix:semicolon
id|dpath
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Show the diff for the &squot;ce&squot; if we found the one&n;&t;&t;&t; * from the desired stage.&n;&t;&t;&t; */
id|diff_unmerge
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|ce-&gt;name
comma
l_int|0
comma
id|null_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
op_ne
id|diff_unmerged_stage
)paren
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
id|silent_on_removed
)paren
r_continue
suffix:semicolon
id|diff_addremove
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
l_char|&squot;-&squot;
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
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
op_logical_and
op_logical_neg
id|revs-&gt;diffopt.find_copies_harder
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
id|newmode
op_assign
id|canon_mode
c_func
(paren
id|st.st_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trust_executable_bit
op_logical_and
id|S_ISREG
c_func
(paren
id|newmode
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|oldmode
)paren
op_logical_and
(paren
(paren
id|newmode
op_xor
id|oldmode
)paren
op_eq
l_int|0111
)paren
)paren
id|newmode
op_assign
id|oldmode
suffix:semicolon
id|diff_change
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|oldmode
comma
id|newmode
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
comma
l_int|NULL
)paren
suffix:semicolon
)brace
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * diff-index&n; */
multiline_comment|/* A file entry went away or appeared */
DECL|function|diff_index_show_file
r_static
r_void
id|diff_index_show_file
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_const
r_char
op_star
id|prefix
comma
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|mode
)paren
(brace
id|diff_addremove
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|prefix
(braket
l_int|0
)braket
comma
id|ntohl
c_func
(paren
id|mode
)paren
comma
id|sha1
comma
id|ce-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|get_stat_data
r_static
r_int
id|get_stat_data
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_char
op_star
op_star
id|sha1p
comma
r_int
r_int
op_star
id|modep
comma
r_int
id|cached
comma
r_int
id|match_missing
)paren
(brace
r_int
r_char
op_star
id|sha1
op_assign
id|ce-&gt;sha1
suffix:semicolon
r_int
r_int
id|mode
op_assign
id|ce-&gt;ce_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cached
)paren
(brace
r_static
r_int
r_char
id|no_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|changed
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
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
op_eq
id|ENOENT
op_logical_and
id|match_missing
)paren
(brace
op_star
id|sha1p
op_assign
id|sha1
suffix:semicolon
op_star
id|modep
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
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
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mode
op_assign
id|ce_mode_from_stat
c_func
(paren
id|ce
comma
id|st.st_mode
)paren
suffix:semicolon
id|sha1
op_assign
id|no_sha1
suffix:semicolon
)brace
)brace
op_star
id|sha1p
op_assign
id|sha1
suffix:semicolon
op_star
id|modep
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_new_file
r_static
r_void
id|show_new_file
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_struct
id|cache_entry
op_star
r_new
comma
r_int
id|cached
comma
r_int
id|match_missing
)paren
(brace
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* New file in the index: it might actually be different in&n;&t; * the working copy.&n;&t; */
r_if
c_cond
(paren
id|get_stat_data
c_func
(paren
r_new
comma
op_amp
id|sha1
comma
op_amp
id|mode
comma
id|cached
comma
id|match_missing
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|diff_index_show_file
c_func
(paren
id|revs
comma
l_string|&quot;+&quot;
comma
r_new
comma
id|sha1
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|show_modified
r_static
r_int
id|show_modified
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
r_new
comma
r_int
id|report_missing
comma
r_int
id|cached
comma
r_int
id|match_missing
)paren
(brace
r_int
r_int
id|mode
comma
id|oldmode
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_if
c_cond
(paren
id|get_stat_data
c_func
(paren
r_new
comma
op_amp
id|sha1
comma
op_amp
id|mode
comma
id|cached
comma
id|match_missing
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|report_missing
)paren
id|diff_index_show_file
c_func
(paren
id|revs
comma
l_string|&quot;-&quot;
comma
id|old
comma
id|old-&gt;sha1
comma
id|old-&gt;ce_mode
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs-&gt;combine_merges
op_logical_and
op_logical_neg
id|cached
op_logical_and
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|old-&gt;sha1
)paren
op_logical_or
id|hashcmp
c_func
(paren
id|old-&gt;sha1
comma
r_new
op_member_access_from_pointer
id|sha1
)paren
)paren
)paren
(brace
r_struct
id|combine_diff_path
op_star
id|p
suffix:semicolon
r_int
id|pathlen
op_assign
id|ce_namelen
c_func
(paren
r_new
)paren
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
id|combine_diff_path_size
c_func
(paren
l_int|2
comma
id|pathlen
)paren
)paren
suffix:semicolon
id|p-&gt;path
op_assign
(paren
r_char
op_star
)paren
op_amp
id|p-&gt;parent
(braket
l_int|2
)braket
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;len
op_assign
id|pathlen
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;path
comma
r_new
op_member_access_from_pointer
id|name
comma
id|pathlen
)paren
suffix:semicolon
id|p-&gt;path
(braket
id|pathlen
)braket
op_assign
l_int|0
suffix:semicolon
id|p-&gt;mode
op_assign
id|ntohl
c_func
(paren
id|mode
)paren
suffix:semicolon
id|hashclr
c_func
(paren
id|p-&gt;sha1
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;parent
comma
l_int|0
comma
l_int|2
op_star
r_sizeof
(paren
r_struct
id|combine_diff_parent
)paren
)paren
suffix:semicolon
id|p-&gt;parent
(braket
l_int|0
)braket
dot
id|status
op_assign
id|DIFF_STATUS_MODIFIED
suffix:semicolon
id|p-&gt;parent
(braket
l_int|0
)braket
dot
id|mode
op_assign
id|ntohl
c_func
(paren
r_new
op_member_access_from_pointer
id|ce_mode
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|p-&gt;parent
(braket
l_int|0
)braket
dot
id|sha1
comma
r_new
op_member_access_from_pointer
id|sha1
)paren
suffix:semicolon
id|p-&gt;parent
(braket
l_int|1
)braket
dot
id|status
op_assign
id|DIFF_STATUS_MODIFIED
suffix:semicolon
id|p-&gt;parent
(braket
l_int|1
)braket
dot
id|mode
op_assign
id|ntohl
c_func
(paren
id|old-&gt;ce_mode
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|p-&gt;parent
(braket
l_int|1
)braket
dot
id|sha1
comma
id|old-&gt;sha1
)paren
suffix:semicolon
id|show_combined_diff
c_func
(paren
id|p
comma
l_int|2
comma
id|revs-&gt;dense_combined_merges
comma
id|revs
)paren
suffix:semicolon
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|oldmode
op_assign
id|old-&gt;ce_mode
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|oldmode
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|old-&gt;sha1
)paren
op_logical_and
op_logical_neg
id|revs-&gt;diffopt.find_copies_harder
)paren
r_return
l_int|0
suffix:semicolon
id|mode
op_assign
id|ntohl
c_func
(paren
id|mode
)paren
suffix:semicolon
id|oldmode
op_assign
id|ntohl
c_func
(paren
id|oldmode
)paren
suffix:semicolon
id|diff_change
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|oldmode
comma
id|mode
comma
id|old-&gt;sha1
comma
id|sha1
comma
id|old-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_cache
r_static
r_int
id|diff_cache
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_struct
id|cache_entry
op_star
op_star
id|ac
comma
r_int
id|entries
comma
r_const
r_char
op_star
op_star
id|pathspec
comma
r_int
id|cached
comma
r_int
id|match_missing
)paren
(brace
r_while
c_loop
(paren
id|entries
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
op_star
id|ac
suffix:semicolon
r_int
id|same
op_assign
(paren
id|entries
OG
l_int|1
)paren
op_logical_and
id|ce_same_name
c_func
(paren
id|ce
comma
id|ac
(braket
l_int|1
)braket
)paren
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
r_goto
id|skip_entry
suffix:semicolon
r_switch
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* No stage 1 entry? That means it&squot;s a new file */
r_if
c_cond
(paren
op_logical_neg
id|same
)paren
(brace
id|show_new_file
c_func
(paren
id|revs
comma
id|ce
comma
id|cached
comma
id|match_missing
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Show difference between old and new */
id|show_modified
c_func
(paren
id|revs
comma
id|ac
(braket
l_int|1
)braket
comma
id|ce
comma
l_int|1
comma
id|cached
comma
id|match_missing
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* No stage 3 (merge) entry?&n;&t;&t;&t; * That means it&squot;s been deleted.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|same
)paren
(brace
id|diff_index_show_file
c_func
(paren
id|revs
comma
l_string|&quot;-&quot;
comma
id|ce
comma
id|ce-&gt;sha1
comma
id|ce-&gt;ce_mode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* We come here with ce pointing at stage 1&n;&t;&t;&t; * (original tree) and ac[1] pointing at stage&n;&t;&t;&t; * 3 (unmerged).  show-modified with&n;&t;&t;&t; * report-missing set to false does not say the&n;&t;&t;&t; * file is deleted but reports true if work&n;&t;&t;&t; * tree does not have it, in which case we&n;&t;&t;&t; * fall through to report the unmerged state.&n;&t;&t;&t; * Otherwise, we show the differences between&n;&t;&t;&t; * the original tree and the work tree.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cached
op_logical_and
op_logical_neg
id|show_modified
c_func
(paren
id|revs
comma
id|ce
comma
id|ac
(braket
l_int|1
)braket
comma
l_int|0
comma
id|cached
comma
id|match_missing
)paren
)paren
r_break
suffix:semicolon
id|diff_unmerge
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|ce-&gt;name
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|ce-&gt;sha1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|diff_unmerge
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|ce-&gt;name
comma
l_int|0
comma
id|null_sha1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;impossible cache entry stage&quot;
)paren
suffix:semicolon
)brace
id|skip_entry
suffix:colon
multiline_comment|/*&n;&t;&t; * Ignore all the different stages for this file,&n;&t;&t; * we&squot;ve handled the relevant cases now.&n;&t;&t; */
r_do
(brace
id|ac
op_increment
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entries
op_logical_and
id|ce_same_name
c_func
(paren
id|ce
comma
id|ac
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This turns all merge entries into &quot;stage 3&quot;. That guarantees that&n; * when we read in the new tree (into &quot;stage 1&quot;), we won&squot;t lose sight&n; * of the fact that we had unmerged entries.&n; */
DECL|function|mark_merge_entries
r_static
r_void
id|mark_merge_entries
c_func
(paren
r_void
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
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|ce-&gt;ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_STAGEMASK
)paren
suffix:semicolon
)brace
)brace
DECL|function|run_diff_index
r_int
id|run_diff_index
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|cached
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|object
op_star
id|ent
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_const
r_char
op_star
id|tree_name
suffix:semicolon
r_int
id|match_missing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;&t; * Backward compatibility wart - &quot;diff-index -m&quot; does&n;&t; * not mean &quot;do not ignore merges&quot;, but totally different.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;ignore_merges
)paren
id|match_missing
op_assign
l_int|1
suffix:semicolon
id|mark_merge_entries
c_func
(paren
)paren
suffix:semicolon
id|ent
op_assign
id|revs-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|item
suffix:semicolon
id|tree_name
op_assign
id|revs-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|name
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|ent-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad tree object %s&quot;
comma
id|tree_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_tree
c_func
(paren
id|tree
comma
l_int|1
comma
id|revs-&gt;prune_data
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to read tree object %s&quot;
comma
id|tree_name
)paren
suffix:semicolon
id|ret
op_assign
id|diff_cache
c_func
(paren
id|revs
comma
id|active_cache
comma
id|active_nr
comma
id|revs-&gt;prune_data
comma
id|cached
comma
id|match_missing
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
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_diff_cache
r_int
id|do_diff_cache
c_func
(paren
r_const
r_int
r_char
op_star
id|tree_sha1
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_struct
id|rev_info
id|revs
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|dst
suffix:semicolon
r_struct
id|cache_entry
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * This is used by git-blame to run diff-cache internally;&n;&t; * it potentially needs to repeatedly run this, so we will&n;&t; * start by removing the higher order entries the last round&n;&t; * left behind.&n;&t; */
id|dst
op_assign
id|active_cache
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
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
r_if
c_cond
(paren
id|last
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|last-&gt;name
)paren
)paren
r_continue
suffix:semicolon
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|last
op_assign
id|ce
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
l_int|0
suffix:semicolon
id|ce-&gt;ce_flags
op_and_assign
op_complement
id|htons
c_func
(paren
id|CE_STAGEMASK
)paren
suffix:semicolon
)brace
op_star
id|dst
op_increment
op_assign
id|ce
suffix:semicolon
)brace
id|active_nr
op_assign
id|dst
id|active_cache
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|revs.prune_data
op_assign
id|opt-&gt;paths
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|tree_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
id|die
c_func
(paren
l_string|&quot;bad tree object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tree_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_tree
c_func
(paren
id|tree
comma
l_int|1
comma
id|opt-&gt;paths
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to read tree %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tree_sha1
)paren
)paren
suffix:semicolon
r_return
id|diff_cache
c_func
(paren
op_amp
id|revs
comma
id|active_cache
comma
id|active_nr
comma
id|revs.prune_data
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
