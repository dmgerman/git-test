multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
multiline_comment|/* Table of rename/copy destinations */
DECL|struct|diff_rename_dst
r_static
r_struct
id|diff_rename_dst
(brace
DECL|member|two
r_struct
id|diff_filespec
op_star
id|two
suffix:semicolon
DECL|member|pair
r_struct
id|diff_filepair
op_star
id|pair
suffix:semicolon
DECL|variable|rename_dst
)brace
op_star
id|rename_dst
suffix:semicolon
DECL|variable|rename_dst_nr
DECL|variable|rename_dst_alloc
r_static
r_int
id|rename_dst_nr
comma
id|rename_dst_alloc
suffix:semicolon
DECL|function|locate_rename_dst
r_static
r_struct
id|diff_rename_dst
op_star
id|locate_rename_dst
c_func
(paren
r_struct
id|diff_filespec
op_star
id|two
comma
r_int
id|insert_ok
)paren
(brace
r_int
id|first
comma
id|last
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|last
op_assign
id|rename_dst_nr
suffix:semicolon
r_while
c_loop
(paren
id|last
OG
id|first
)paren
(brace
r_int
id|next
op_assign
(paren
id|last
op_plus
id|first
)paren
op_rshift
l_int|1
suffix:semicolon
r_struct
id|diff_rename_dst
op_star
id|dst
op_assign
op_amp
(paren
id|rename_dst
(braket
id|next
)braket
)paren
suffix:semicolon
r_int
id|cmp
op_assign
id|strcmp
c_func
(paren
id|two-&gt;path
comma
id|dst-&gt;two-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|last
op_assign
id|next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|first
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* not found */
r_if
c_cond
(paren
op_logical_neg
id|insert_ok
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* insert to make it at &quot;first&quot; */
r_if
c_cond
(paren
id|rename_dst_alloc
op_le
id|rename_dst_nr
)paren
(brace
id|rename_dst_alloc
op_assign
id|alloc_nr
c_func
(paren
id|rename_dst_alloc
)paren
suffix:semicolon
id|rename_dst
op_assign
id|xrealloc
c_func
(paren
id|rename_dst
comma
id|rename_dst_alloc
op_star
r_sizeof
(paren
op_star
id|rename_dst
)paren
)paren
suffix:semicolon
)brace
id|rename_dst_nr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|first
OL
id|rename_dst_nr
)paren
id|memmove
c_func
(paren
id|rename_dst
op_plus
id|first
op_plus
l_int|1
comma
id|rename_dst
op_plus
id|first
comma
(paren
id|rename_dst_nr
id|first
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|rename_dst
)paren
)paren
suffix:semicolon
id|rename_dst
(braket
id|first
)braket
dot
id|two
op_assign
id|alloc_filespec
c_func
(paren
id|two-&gt;path
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|rename_dst
(braket
id|first
)braket
dot
id|two
comma
id|two-&gt;sha1
comma
id|two-&gt;mode
)paren
suffix:semicolon
id|rename_dst
(braket
id|first
)braket
dot
id|pair
op_assign
l_int|NULL
suffix:semicolon
r_return
op_amp
(paren
id|rename_dst
(braket
id|first
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Table of rename/copy src files */
DECL|struct|diff_rename_src
r_static
r_struct
id|diff_rename_src
(brace
DECL|member|one
r_struct
id|diff_filespec
op_star
id|one
suffix:semicolon
DECL|member|score
r_int
r_int
id|score
suffix:semicolon
multiline_comment|/* to remember the break score */
DECL|member|src_path_left
r_int
id|src_path_left
suffix:colon
l_int|1
suffix:semicolon
DECL|variable|rename_src
)brace
op_star
id|rename_src
suffix:semicolon
DECL|variable|rename_src_nr
DECL|variable|rename_src_alloc
r_static
r_int
id|rename_src_nr
comma
id|rename_src_alloc
suffix:semicolon
DECL|function|register_rename_src
r_static
r_struct
id|diff_rename_src
op_star
id|register_rename_src
c_func
(paren
r_struct
id|diff_filespec
op_star
id|one
comma
r_int
id|src_path_left
comma
r_int
r_int
id|score
)paren
(brace
r_int
id|first
comma
id|last
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|last
op_assign
id|rename_src_nr
suffix:semicolon
r_while
c_loop
(paren
id|last
OG
id|first
)paren
(brace
r_int
id|next
op_assign
(paren
id|last
op_plus
id|first
)paren
op_rshift
l_int|1
suffix:semicolon
r_struct
id|diff_rename_src
op_star
id|src
op_assign
op_amp
(paren
id|rename_src
(braket
id|next
)braket
)paren
suffix:semicolon
r_int
id|cmp
op_assign
id|strcmp
c_func
(paren
id|one-&gt;path
comma
id|src-&gt;one-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|src
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|last
op_assign
id|next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|first
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* insert to make it at &quot;first&quot; */
r_if
c_cond
(paren
id|rename_src_alloc
op_le
id|rename_src_nr
)paren
(brace
id|rename_src_alloc
op_assign
id|alloc_nr
c_func
(paren
id|rename_src_alloc
)paren
suffix:semicolon
id|rename_src
op_assign
id|xrealloc
c_func
(paren
id|rename_src
comma
id|rename_src_alloc
op_star
r_sizeof
(paren
op_star
id|rename_src
)paren
)paren
suffix:semicolon
)brace
id|rename_src_nr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|first
OL
id|rename_src_nr
)paren
id|memmove
c_func
(paren
id|rename_src
op_plus
id|first
op_plus
l_int|1
comma
id|rename_src
op_plus
id|first
comma
(paren
id|rename_src_nr
id|first
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|rename_src
)paren
)paren
suffix:semicolon
id|rename_src
(braket
id|first
)braket
dot
id|one
op_assign
id|one
suffix:semicolon
id|rename_src
(braket
id|first
)braket
dot
id|score
op_assign
id|score
suffix:semicolon
id|rename_src
(braket
id|first
)braket
dot
id|src_path_left
op_assign
id|src_path_left
suffix:semicolon
r_return
op_amp
(paren
id|rename_src
(braket
id|first
)braket
)paren
suffix:semicolon
)brace
DECL|function|is_exact_match
r_static
r_int
id|is_exact_match
c_func
(paren
r_struct
id|diff_filespec
op_star
id|src
comma
r_struct
id|diff_filespec
op_star
id|dst
comma
r_int
id|contents_too
)paren
(brace
r_if
c_cond
(paren
id|src-&gt;sha1_valid
op_logical_and
id|dst-&gt;sha1_valid
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|src-&gt;sha1
comma
id|dst-&gt;sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|contents_too
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|src
comma
l_int|1
)paren
op_logical_or
id|diff_populate_filespec
c_func
(paren
id|dst
comma
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|src-&gt;size
op_ne
id|dst-&gt;size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|src-&gt;sha1_valid
op_logical_and
id|dst-&gt;sha1_valid
)paren
r_return
op_logical_neg
id|hashcmp
c_func
(paren
id|src-&gt;sha1
comma
id|dst-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|src
comma
l_int|0
)paren
op_logical_or
id|diff_populate_filespec
c_func
(paren
id|dst
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|src-&gt;size
op_eq
id|dst-&gt;size
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|src-&gt;data
comma
id|dst-&gt;data
comma
id|src-&gt;size
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|diff_score
r_struct
id|diff_score
(brace
DECL|member|src
r_int
id|src
suffix:semicolon
multiline_comment|/* index in rename_src */
DECL|member|dst
r_int
id|dst
suffix:semicolon
multiline_comment|/* index in rename_dst */
DECL|member|score
r_int
id|score
suffix:semicolon
)brace
suffix:semicolon
DECL|function|estimate_similarity
r_static
r_int
id|estimate_similarity
c_func
(paren
r_struct
id|diff_filespec
op_star
id|src
comma
r_struct
id|diff_filespec
op_star
id|dst
comma
r_int
id|minimum_score
)paren
(brace
multiline_comment|/* src points at a file that existed in the original tree (or&n;&t; * optionally a file in the destination tree) and dst points&n;&t; * at a newly created file.  They may be quite similar, in which&n;&t; * case we want to say src is renamed to dst or src is copied into&n;&t; * dst, and then some edit has been applied to dst.&n;&t; *&n;&t; * Compare them and return how similar they are, representing&n;&t; * the score as an integer between 0 and MAX_SCORE.&n;&t; *&n;&t; * When there is an exact match, it is considered a better&n;&t; * match than anything else; the destination does not even&n;&t; * call into this function in that case.&n;&t; */
r_int
r_int
id|max_size
comma
id|delta_size
comma
id|base_size
comma
id|src_copied
comma
id|literal_added
suffix:semicolon
r_int
r_int
id|delta_limit
suffix:semicolon
r_int
id|score
suffix:semicolon
multiline_comment|/* We deal only with regular files.  Symlink renames are handled&n;&t; * only when they are exact matches --- in other words, no edits&n;&t; * after renaming.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|src-&gt;mode
)paren
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|dst-&gt;mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|max_size
op_assign
(paren
(paren
id|src-&gt;size
OG
id|dst-&gt;size
)paren
ques
c_cond
id|src-&gt;size
suffix:colon
id|dst-&gt;size
)paren
suffix:semicolon
id|base_size
op_assign
(paren
(paren
id|src-&gt;size
OL
id|dst-&gt;size
)paren
ques
c_cond
id|src-&gt;size
suffix:colon
id|dst-&gt;size
)paren
suffix:semicolon
id|delta_size
op_assign
id|max_size
id|base_size
suffix:semicolon
multiline_comment|/* We would not consider edits that change the file size so&n;&t; * drastically.  delta_size must be smaller than&n;&t; * (MAX_SCORE-minimum_score)/MAX_SCORE * min(src-&gt;size, dst-&gt;size).&n;&t; *&n;&t; * Note that base_size == 0 case is handled here already&n;&t; * and the final score computation below would not have a&n;&t; * divide-by-zero issue.&n;&t; */
r_if
c_cond
(paren
id|base_size
op_star
(paren
id|MAX_SCORE
op_minus
id|minimum_score
)paren
OL
id|delta_size
op_star
id|MAX_SCORE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|src
comma
l_int|0
)paren
op_logical_or
id|diff_populate_filespec
c_func
(paren
id|dst
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* error but caught downstream */
id|delta_limit
op_assign
(paren
r_int
r_int
)paren
(paren
id|base_size
op_star
(paren
id|MAX_SCORE
op_minus
id|minimum_score
)paren
op_div
id|MAX_SCORE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diffcore_count_changes
c_func
(paren
id|src-&gt;data
comma
id|src-&gt;size
comma
id|dst-&gt;data
comma
id|dst-&gt;size
comma
op_amp
id|src-&gt;cnt_data
comma
op_amp
id|dst-&gt;cnt_data
comma
id|delta_limit
comma
op_amp
id|src_copied
comma
op_amp
id|literal_added
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* How similar are they?&n;&t; * what percentage of material in dst are from source?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|dst-&gt;size
)paren
id|score
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* should not happen */
r_else
id|score
op_assign
(paren
r_int
)paren
(paren
id|src_copied
op_star
id|MAX_SCORE
op_div
id|max_size
)paren
suffix:semicolon
r_return
id|score
suffix:semicolon
)brace
DECL|function|record_rename_pair
r_static
r_void
id|record_rename_pair
c_func
(paren
r_int
id|dst_index
comma
r_int
id|src_index
comma
r_int
id|score
)paren
(brace
r_struct
id|diff_filespec
op_star
id|one
comma
op_star
id|two
comma
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_struct
id|diff_filepair
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|rename_dst
(braket
id|dst_index
)braket
dot
id|pair
)paren
id|die
c_func
(paren
l_string|&quot;internal error: dst already matched.&quot;
)paren
suffix:semicolon
id|src
op_assign
id|rename_src
(braket
id|src_index
)braket
dot
id|one
suffix:semicolon
id|one
op_assign
id|alloc_filespec
c_func
(paren
id|src-&gt;path
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|one
comma
id|src-&gt;sha1
comma
id|src-&gt;mode
)paren
suffix:semicolon
id|dst
op_assign
id|rename_dst
(braket
id|dst_index
)braket
dot
id|two
suffix:semicolon
id|two
op_assign
id|alloc_filespec
c_func
(paren
id|dst-&gt;path
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|two
comma
id|dst-&gt;sha1
comma
id|dst-&gt;mode
)paren
suffix:semicolon
id|dp
op_assign
id|diff_queue
c_func
(paren
l_int|NULL
comma
id|one
comma
id|two
)paren
suffix:semicolon
id|dp-&gt;renamed_pair
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|src-&gt;path
comma
id|dst-&gt;path
)paren
)paren
id|dp-&gt;score
op_assign
id|rename_src
(braket
id|src_index
)braket
dot
id|score
suffix:semicolon
r_else
id|dp-&gt;score
op_assign
id|score
suffix:semicolon
id|dp-&gt;source_stays
op_assign
id|rename_src
(braket
id|src_index
)braket
dot
id|src_path_left
suffix:semicolon
id|rename_dst
(braket
id|dst_index
)braket
dot
id|pair
op_assign
id|dp
suffix:semicolon
)brace
multiline_comment|/*&n; * We sort the rename similarity matrix with the score, in descending&n; * order (the most similar first).&n; */
DECL|function|score_compare
r_static
r_int
id|score_compare
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_const
r_struct
id|diff_score
op_star
id|a
op_assign
id|a_
comma
op_star
id|b
op_assign
id|b_
suffix:semicolon
r_return
id|b-&gt;score
id|a-&gt;score
suffix:semicolon
)brace
DECL|function|compute_stays
r_static
r_int
id|compute_stays
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_filespec
op_star
id|one
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|one-&gt;path
comma
id|p-&gt;two-&gt;path
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_PAIR_RENAME
c_func
(paren
id|p
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* something else is renamed into this */
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|diffcore_rename
r_void
id|diffcore_rename
c_func
(paren
r_struct
id|diff_options
op_star
id|options
)paren
(brace
r_int
id|detect_rename
op_assign
id|options-&gt;detect_rename
suffix:semicolon
r_int
id|minimum_score
op_assign
id|options-&gt;rename_score
suffix:semicolon
r_int
id|rename_limit
op_assign
id|options-&gt;rename_limit
suffix:semicolon
r_struct
id|diff_queue_struct
op_star
id|q
op_assign
op_amp
id|diff_queued_diff
suffix:semicolon
r_struct
id|diff_queue_struct
id|outq
suffix:semicolon
r_struct
id|diff_score
op_star
id|mx
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|rename_count
comma
id|contents_too
suffix:semicolon
r_int
id|num_create
comma
id|num_src
comma
id|dst_cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minimum_score
)paren
id|minimum_score
op_assign
id|DEFAULT_RENAME_SCORE
suffix:semicolon
id|rename_count
op_assign
l_int|0
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
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* unmerged */
r_else
r_if
c_cond
(paren
id|options-&gt;single_follow
op_logical_and
id|strcmp
c_func
(paren
id|options-&gt;single_follow
comma
id|p-&gt;two-&gt;path
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* not interested */
r_else
id|locate_rename_dst
c_func
(paren
id|p-&gt;two
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
(brace
multiline_comment|/* If the source is a broken &quot;delete&quot;, and&n;&t;&t;&t; * they did not really want to get broken,&n;&t;&t;&t; * that means the source actually stays.&n;&t;&t;&t; */
r_int
id|stays
op_assign
(paren
id|p-&gt;broken_pair
op_logical_and
op_logical_neg
id|p-&gt;score
)paren
suffix:semicolon
id|register_rename_src
c_func
(paren
id|p-&gt;one
comma
id|stays
comma
id|p-&gt;score
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|detect_rename
op_eq
id|DIFF_DETECT_COPY
)paren
id|register_rename_src
c_func
(paren
id|p-&gt;one
comma
l_int|1
comma
id|p-&gt;score
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rename_dst_nr
op_eq
l_int|0
op_logical_or
id|rename_src_nr
op_eq
l_int|0
op_logical_or
(paren
l_int|0
OL
id|rename_limit
op_logical_and
id|rename_limit
OL
id|rename_dst_nr
)paren
)paren
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* nothing to do */
multiline_comment|/* We really want to cull the candidates list early&n;&t; * with cheap tests in order to avoid doing deltas.&n;&t; * The first round matches up the up-to-date entries,&n;&t; * and then during the second round we try to match&n;&t; * cache-dirty entries as well.&n;&t; */
r_for
c_loop
(paren
id|contents_too
op_assign
l_int|0
suffix:semicolon
id|contents_too
OL
l_int|2
suffix:semicolon
id|contents_too
op_increment
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
id|rename_dst_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filespec
op_star
id|two
op_assign
id|rename_dst
(braket
id|i
)braket
dot
id|two
suffix:semicolon
r_if
c_cond
(paren
id|rename_dst
(braket
id|i
)braket
dot
id|pair
)paren
r_continue
suffix:semicolon
multiline_comment|/* dealt with an earlier round */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rename_src_nr
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|diff_filespec
op_star
id|one
op_assign
id|rename_src
(braket
id|j
)braket
dot
id|one
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_exact_match
c_func
(paren
id|one
comma
id|two
comma
id|contents_too
)paren
)paren
r_continue
suffix:semicolon
id|record_rename_pair
c_func
(paren
id|i
comma
id|j
comma
(paren
r_int
)paren
id|MAX_SCORE
)paren
suffix:semicolon
id|rename_count
op_increment
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* we are done with this entry */
)brace
)brace
)brace
multiline_comment|/* Have we run out the created file pool?  If so we can avoid&n;&t; * doing the delta matrix altogether.&n;&t; */
r_if
c_cond
(paren
id|rename_count
op_eq
id|rename_dst_nr
)paren
r_goto
id|cleanup
suffix:semicolon
r_if
c_cond
(paren
id|minimum_score
op_eq
id|MAX_SCORE
)paren
r_goto
id|cleanup
suffix:semicolon
id|num_create
op_assign
(paren
id|rename_dst_nr
id|rename_count
)paren
suffix:semicolon
id|num_src
op_assign
id|rename_src_nr
suffix:semicolon
id|mx
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mx
)paren
op_star
id|num_create
op_star
id|num_src
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dst_cnt
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|rename_dst_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|base
op_assign
id|dst_cnt
op_star
id|num_src
suffix:semicolon
r_struct
id|diff_filespec
op_star
id|two
op_assign
id|rename_dst
(braket
id|i
)braket
dot
id|two
suffix:semicolon
r_if
c_cond
(paren
id|rename_dst
(braket
id|i
)braket
dot
id|pair
)paren
r_continue
suffix:semicolon
multiline_comment|/* dealt with exact match already. */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rename_src_nr
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|diff_filespec
op_star
id|one
op_assign
id|rename_src
(braket
id|j
)braket
dot
id|one
suffix:semicolon
r_struct
id|diff_score
op_star
id|m
op_assign
op_amp
id|mx
(braket
id|base
op_plus
id|j
)braket
suffix:semicolon
id|m-&gt;src
op_assign
id|j
suffix:semicolon
id|m-&gt;dst
op_assign
id|i
suffix:semicolon
id|m-&gt;score
op_assign
id|estimate_similarity
c_func
(paren
id|one
comma
id|two
comma
id|minimum_score
)paren
suffix:semicolon
id|diff_free_filespec_data
c_func
(paren
id|one
)paren
suffix:semicolon
)brace
multiline_comment|/* We do not need the text anymore */
id|diff_free_filespec_data
c_func
(paren
id|two
)paren
suffix:semicolon
id|dst_cnt
op_increment
suffix:semicolon
)brace
multiline_comment|/* cost matrix sorted by most to least similar pair */
id|qsort
c_func
(paren
id|mx
comma
id|num_create
op_star
id|num_src
comma
r_sizeof
(paren
op_star
id|mx
)paren
comma
id|score_compare
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
id|num_create
op_star
id|num_src
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_rename_dst
op_star
id|dst
op_assign
op_amp
id|rename_dst
(braket
id|mx
(braket
id|i
)braket
dot
id|dst
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;pair
)paren
r_continue
suffix:semicolon
multiline_comment|/* already done, either exact or fuzzy. */
r_if
c_cond
(paren
id|mx
(braket
id|i
)braket
dot
id|score
OL
id|minimum_score
)paren
r_break
suffix:semicolon
multiline_comment|/* there is no more usable pair. */
id|record_rename_pair
c_func
(paren
id|mx
(braket
id|i
)braket
dot
id|dst
comma
id|mx
(braket
id|i
)braket
dot
id|src
comma
id|mx
(braket
id|i
)braket
dot
id|score
)paren
suffix:semicolon
id|rename_count
op_increment
suffix:semicolon
)brace
id|free
c_func
(paren
id|mx
)paren
suffix:semicolon
id|cleanup
suffix:colon
multiline_comment|/* At this point, we have found some renames and copies and they&n;&t; * are recorded in rename_dst.  The original list is still in *q.&n;&t; */
id|outq.queue
op_assign
l_int|NULL
suffix:semicolon
id|outq.nr
op_assign
id|outq.alloc
op_assign
l_int|0
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
r_struct
id|diff_filepair
op_star
id|pair_to_free
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
op_logical_and
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Creation&n;&t;&t;&t; *&n;&t;&t;&t; * We would output this create record if it has&n;&t;&t;&t; * not been turned into a rename/copy already.&n;&t;&t;&t; */
r_struct
id|diff_rename_dst
op_star
id|dst
op_assign
id|locate_rename_dst
c_func
(paren
id|p-&gt;two
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_logical_and
id|dst-&gt;pair
)paren
(brace
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|dst-&gt;pair
)paren
suffix:semicolon
id|pair_to_free
op_assign
id|p
suffix:semicolon
)brace
r_else
multiline_comment|/* no matching rename/copy source, so&n;&t;&t;&t;&t; * record this as a creation.&n;&t;&t;&t;&t; */
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
op_logical_and
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Deletion&n;&t;&t;&t; *&n;&t;&t;&t; * We would output this delete record if:&n;&t;&t;&t; *&n;&t;&t;&t; * (1) this is a broken delete and the counterpart&n;&t;&t;&t; *     broken create remains in the output; or&n;&t;&t;&t; * (2) this is not a broken delete, and rename_dst&n;&t;&t;&t; *     does not have a rename/copy to move p-&gt;one-&gt;path&n;&t;&t;&t; *     out of existence.&n;&t;&t;&t; *&n;&t;&t;&t; * Otherwise, the counterpart broken create&n;&t;&t;&t; * has been turned into a rename-edit; or&n;&t;&t;&t; * delete did not have a matching create to&n;&t;&t;&t; * begin with.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|DIFF_PAIR_BROKEN
c_func
(paren
id|p
)paren
)paren
(brace
multiline_comment|/* broken delete */
r_struct
id|diff_rename_dst
op_star
id|dst
op_assign
id|locate_rename_dst
c_func
(paren
id|p-&gt;one
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_logical_and
id|dst-&gt;pair
)paren
multiline_comment|/* counterpart is now rename/copy */
id|pair_to_free
op_assign
id|p
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rename_dst_nr
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rename_dst
(braket
id|j
)braket
dot
id|pair
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|rename_dst
(braket
id|j
)braket
dot
id|pair
op_member_access_from_pointer
id|one-&gt;path
comma
id|p-&gt;one-&gt;path
)paren
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
OL
id|rename_dst_nr
)paren
multiline_comment|/* this path remains */
id|pair_to_free
op_assign
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pair_to_free
)paren
suffix:semicolon
r_else
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|diff_unmodified_pair
c_func
(paren
id|p
)paren
)paren
multiline_comment|/* all the usual ones need to be kept */
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
r_else
multiline_comment|/* no need to keep unmodified pairs */
id|pair_to_free
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|pair_to_free
)paren
id|diff_free_filepair
c_func
(paren
id|pair_to_free
)paren
suffix:semicolon
)brace
id|diff_debug_queue
c_func
(paren
l_string|&quot;done copying original&quot;
comma
op_amp
id|outq
)paren
suffix:semicolon
id|free
c_func
(paren
id|q-&gt;queue
)paren
suffix:semicolon
op_star
id|q
op_assign
id|outq
suffix:semicolon
id|diff_debug_queue
c_func
(paren
l_string|&quot;done collapsing&quot;
comma
id|q
)paren
suffix:semicolon
multiline_comment|/* We need to see which rename source really stays here;&n;&t; * earlier we only checked if the path is left in the result,&n;&t; * but even if a path remains in the result, if that is coming&n;&t; * from copying something else on top of it, then the original&n;&t; * source is lost and does not stay.&n;&t; */
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
r_if
c_cond
(paren
id|DIFF_PAIR_RENAME
c_func
(paren
id|p
)paren
op_logical_and
id|p-&gt;source_stays
)paren
(brace
multiline_comment|/* If one appears as the target of a rename-copy,&n;&t;&t;&t; * then mark p-&gt;source_stays = 0; otherwise&n;&t;&t;&t; * leave it as is.&n;&t;&t;&t; */
id|p-&gt;source_stays
op_assign
id|compute_stays
c_func
(paren
id|q
comma
id|p-&gt;one
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
id|rename_dst_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|diff_free_filespec_data
c_func
(paren
id|rename_dst
(braket
id|i
)braket
dot
id|two
)paren
suffix:semicolon
id|free
c_func
(paren
id|rename_dst
(braket
id|i
)braket
dot
id|two
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|rename_dst
)paren
suffix:semicolon
id|rename_dst
op_assign
l_int|NULL
suffix:semicolon
id|rename_dst_nr
op_assign
id|rename_dst_alloc
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|rename_src
)paren
suffix:semicolon
id|rename_src
op_assign
l_int|NULL
suffix:semicolon
id|rename_src_nr
op_assign
id|rename_src_alloc
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
