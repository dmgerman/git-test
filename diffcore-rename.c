multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;hash.h&quot;
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
DECL|function|basename_same
r_static
r_int
id|basename_same
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
)paren
(brace
r_int
id|src_len
op_assign
id|strlen
c_func
(paren
id|src-&gt;path
)paren
comma
id|dst_len
op_assign
id|strlen
c_func
(paren
id|dst-&gt;path
)paren
suffix:semicolon
r_while
c_loop
(paren
id|src_len
op_logical_and
id|dst_len
)paren
(brace
r_char
id|c1
op_assign
id|src-&gt;path
(braket
op_decrement
id|src_len
)braket
suffix:semicolon
r_char
id|c2
op_assign
id|dst-&gt;path
(braket
op_decrement
id|dst_len
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
(paren
op_logical_neg
id|src_len
op_logical_or
id|src-&gt;path
(braket
id|src_len
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
op_logical_and
(paren
op_logical_neg
id|dst_len
op_logical_or
id|dst-&gt;path
(braket
id|dst_len
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
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
r_int
id|score
suffix:semicolon
DECL|member|name_score
r_int
id|name_score
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
multiline_comment|/*&n;&t; * Need to check that source and destination sizes are&n;&t; * filled in before comparing them.&n;&t; *&n;&t; * If we already have &quot;cnt_data&quot; filled in, we know it&squot;s&n;&t; * all good (avoid checking the size for zero, as that&n;&t; * is a possible size - we really should have a flag to&n;&t; * say whether the size is valid or not!)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|src-&gt;cnt_data
op_logical_and
id|diff_populate_filespec
c_func
(paren
id|src
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
op_logical_neg
id|dst-&gt;cnt_data
op_logical_and
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
op_logical_neg
id|src-&gt;cnt_data
op_logical_and
id|diff_populate_filespec
c_func
(paren
id|src
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
op_logical_neg
id|dst-&gt;cnt_data
op_logical_and
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
id|src
comma
id|dst
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
id|src-&gt;rename_used
op_increment
suffix:semicolon
id|src-&gt;count
op_increment
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
id|dst-&gt;count
op_increment
suffix:semicolon
id|dp
op_assign
id|diff_queue
c_func
(paren
l_int|NULL
comma
id|src
comma
id|dst
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
multiline_comment|/* sink the unused ones to the bottom */
r_if
c_cond
(paren
id|a-&gt;dst
OL
l_int|0
)paren
r_return
(paren
l_int|0
op_le
id|b-&gt;dst
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|b-&gt;dst
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;score
op_eq
id|b-&gt;score
)paren
r_return
id|b-&gt;name_score
id|a-&gt;name_score
suffix:semicolon
r_return
id|b-&gt;score
id|a-&gt;score
suffix:semicolon
)brace
DECL|struct|file_similarity
r_struct
id|file_similarity
(brace
DECL|member|src_dst
DECL|member|index
r_int
id|src_dst
comma
id|index
suffix:semicolon
DECL|member|filespec
r_struct
id|diff_filespec
op_star
id|filespec
suffix:semicolon
DECL|member|next
r_struct
id|file_similarity
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|function|find_identical_files
r_static
r_int
id|find_identical_files
c_func
(paren
r_struct
id|file_similarity
op_star
id|src
comma
r_struct
id|file_similarity
op_star
id|dst
)paren
(brace
r_int
id|renames
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Walk over all the destinations ...&n;&t; */
r_do
(brace
r_struct
id|diff_filespec
op_star
id|target
op_assign
id|dst-&gt;filespec
suffix:semicolon
r_struct
id|file_similarity
op_star
id|p
comma
op_star
id|best
suffix:semicolon
r_int
id|i
op_assign
l_int|100
comma
id|best_score
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * .. to find the best source match&n;&t;&t; */
id|best
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|src
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|score
suffix:semicolon
r_struct
id|diff_filespec
op_star
id|source
op_assign
id|p-&gt;filespec
suffix:semicolon
multiline_comment|/* False hash collision? */
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|source-&gt;sha1
comma
id|target-&gt;sha1
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Non-regular files? If so, the modes must match! */
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|source-&gt;mode
)paren
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|target-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|source-&gt;mode
op_ne
id|target-&gt;mode
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/* Give higher scores to sources that haven&squot;t been used already */
id|score
op_assign
op_logical_neg
id|source-&gt;rename_used
suffix:semicolon
id|score
op_add_assign
id|basename_same
c_func
(paren
id|source
comma
id|target
)paren
suffix:semicolon
r_if
c_cond
(paren
id|score
OG
id|best_score
)paren
(brace
id|best
op_assign
id|p
suffix:semicolon
id|best_score
op_assign
id|score
suffix:semicolon
r_if
c_cond
(paren
id|score
op_eq
l_int|2
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* Too many identical alternatives? Pick one */
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|i
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|best
)paren
(brace
id|record_rename_pair
c_func
(paren
id|dst-&gt;index
comma
id|best-&gt;index
comma
id|MAX_SCORE
)paren
suffix:semicolon
id|renames
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|dst
op_assign
id|dst-&gt;next
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
r_return
id|renames
suffix:semicolon
)brace
DECL|function|free_similarity_list
r_static
r_void
id|free_similarity_list
c_func
(paren
r_struct
id|file_similarity
op_star
id|p
)paren
(brace
r_while
c_loop
(paren
id|p
)paren
(brace
r_struct
id|file_similarity
op_star
id|entry
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
DECL|function|find_same_files
r_static
r_int
id|find_same_files
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|file_similarity
op_star
id|p
op_assign
id|ptr
suffix:semicolon
r_struct
id|file_similarity
op_star
id|src
op_assign
l_int|NULL
comma
op_star
id|dst
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Split the hash list up into sources and destinations */
r_do
(brace
r_struct
id|file_similarity
op_star
id|entry
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;src_dst
OL
l_int|0
)paren
(brace
id|entry-&gt;next
op_assign
id|src
suffix:semicolon
id|src
op_assign
id|entry
suffix:semicolon
)brace
r_else
(brace
id|entry-&gt;next
op_assign
id|dst
suffix:semicolon
id|dst
op_assign
id|entry
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we have both sources *and* destinations, see if&n;&t; * we can match them up&n;&t; */
id|ret
op_assign
(paren
id|src
op_logical_and
id|dst
)paren
ques
c_cond
id|find_identical_files
c_func
(paren
id|src
comma
id|dst
)paren
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Free the hashes and return the number of renames found */
id|free_similarity_list
c_func
(paren
id|src
)paren
suffix:semicolon
id|free_similarity_list
c_func
(paren
id|dst
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hash_filespec
r_static
r_int
r_int
id|hash_filespec
c_func
(paren
r_struct
id|diff_filespec
op_star
id|filespec
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filespec-&gt;sha1_valid
)paren
(brace
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|filespec
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hash_sha1_file
c_func
(paren
id|filespec-&gt;data
comma
id|filespec-&gt;size
comma
l_string|&quot;blob&quot;
comma
id|filespec-&gt;sha1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|hash
comma
id|filespec-&gt;sha1
comma
r_sizeof
(paren
id|hash
)paren
)paren
suffix:semicolon
r_return
id|hash
suffix:semicolon
)brace
DECL|function|insert_file_table
r_static
r_void
id|insert_file_table
c_func
(paren
r_struct
id|hash_table
op_star
id|table
comma
r_int
id|src_dst
comma
r_int
id|index
comma
r_struct
id|diff_filespec
op_star
id|filespec
)paren
(brace
r_void
op_star
op_star
id|pos
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_struct
id|file_similarity
op_star
id|entry
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
id|entry-&gt;src_dst
op_assign
id|src_dst
suffix:semicolon
id|entry-&gt;index
op_assign
id|index
suffix:semicolon
id|entry-&gt;filespec
op_assign
id|filespec
suffix:semicolon
id|entry-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|hash
op_assign
id|hash_filespec
c_func
(paren
id|filespec
)paren
suffix:semicolon
id|pos
op_assign
id|insert_hash
c_func
(paren
id|hash
comma
id|entry
comma
id|table
)paren
suffix:semicolon
multiline_comment|/* We already had an entry there? */
r_if
c_cond
(paren
id|pos
)paren
(brace
id|entry-&gt;next
op_assign
op_star
id|pos
suffix:semicolon
op_star
id|pos
op_assign
id|entry
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Find exact renames first.&n; *&n; * The first round matches up the up-to-date entries,&n; * and then during the second round we try to match&n; * cache-dirty entries as well.&n; */
DECL|function|find_exact_renames
r_static
r_int
id|find_exact_renames
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|hash_table
id|file_table
suffix:semicolon
id|init_hash
c_func
(paren
op_amp
id|file_table
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
id|rename_src_nr
suffix:semicolon
id|i
op_increment
)paren
id|insert_file_table
c_func
(paren
op_amp
id|file_table
comma
l_int|1
comma
id|i
comma
id|rename_src
(braket
id|i
)braket
dot
id|one
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
id|rename_dst_nr
suffix:semicolon
id|i
op_increment
)paren
id|insert_file_table
c_func
(paren
op_amp
id|file_table
comma
l_int|1
comma
id|i
comma
id|rename_dst
(braket
id|i
)braket
dot
id|two
)paren
suffix:semicolon
multiline_comment|/* Find the renames */
id|i
op_assign
id|for_each_hash
c_func
(paren
op_amp
id|file_table
comma
id|find_same_files
)paren
suffix:semicolon
multiline_comment|/* .. and free the hash data structure */
id|free_hash
c_func
(paren
op_amp
id|file_table
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|macro|NUM_CANDIDATE_PER_DST
mdefine_line|#define NUM_CANDIDATE_PER_DST 4
DECL|function|record_if_better
r_static
r_void
id|record_if_better
c_func
(paren
r_struct
id|diff_score
id|m
(braket
)braket
comma
r_struct
id|diff_score
op_star
id|o
)paren
(brace
r_int
id|i
comma
id|worst
suffix:semicolon
multiline_comment|/* find the worst one */
id|worst
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
id|NUM_CANDIDATE_PER_DST
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|score_compare
c_func
(paren
op_amp
id|m
(braket
id|i
)braket
comma
op_amp
id|m
(braket
id|worst
)braket
)paren
OG
l_int|0
)paren
id|worst
op_assign
id|i
suffix:semicolon
multiline_comment|/* is it better than the worst one? */
r_if
c_cond
(paren
id|score_compare
c_func
(paren
op_amp
id|m
(braket
id|worst
)braket
comma
id|o
)paren
OG
l_int|0
)paren
id|m
(braket
id|worst
)braket
op_assign
op_star
id|o
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
multiline_comment|/*&n;&t;&t;&t; * If the source is a broken &quot;delete&quot;, and&n;&t;&t;&t; * they did not really want to get broken,&n;&t;&t;&t; * that means the source actually stays.&n;&t;&t;&t; * So we increment the &quot;rename_used&quot; score&n;&t;&t;&t; * by one, to indicate ourselves as a user&n;&t;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;broken_pair
op_logical_and
op_logical_neg
id|p-&gt;score
)paren
id|p-&gt;one-&gt;rename_used
op_increment
suffix:semicolon
id|register_rename_src
c_func
(paren
id|p-&gt;one
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
(brace
multiline_comment|/*&n;&t;&t;&t; * Increment the &quot;rename_used&quot; score by&n;&t;&t;&t; * one, to indicate ourselves as a user.&n;&t;&t;&t; */
id|p-&gt;one-&gt;rename_used
op_increment
suffix:semicolon
id|register_rename_src
c_func
(paren
id|p-&gt;one
comma
id|p-&gt;score
)paren
suffix:semicolon
)brace
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
)paren
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* nothing to do */
multiline_comment|/*&n;&t; * We really want to cull the candidates list early&n;&t; * with cheap tests in order to avoid doing deltas.&n;&t; */
id|rename_count
op_assign
id|find_exact_renames
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Did we only want exact renames? */
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
multiline_comment|/*&n;&t; * Calculate how many renames are left (but all the source&n;&t; * files still remain as options for rename/copies!)&n;&t; */
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
multiline_comment|/* All done? */
r_if
c_cond
(paren
op_logical_neg
id|num_create
)paren
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/*&n;&t; * This basically does a test for the rename matrix not&n;&t; * growing larger than a &quot;rename_limit&quot; square matrix, ie:&n;&t; *&n;&t; *    num_create * num_src &gt; rename_limit * rename_limit&n;&t; *&n;&t; * but handles the potential overflow case specially (and we&n;&t; * assume at least 32-bit integers)&n;&t; */
r_if
c_cond
(paren
id|rename_limit
op_le
l_int|0
op_logical_or
id|rename_limit
OG
l_int|32767
)paren
id|rename_limit
op_assign
l_int|32767
suffix:semicolon
r_if
c_cond
(paren
(paren
id|num_create
OG
id|rename_limit
op_logical_and
id|num_src
OG
id|rename_limit
)paren
op_logical_or
(paren
id|num_create
op_star
id|num_src
OG
id|rename_limit
op_star
id|rename_limit
)paren
)paren
(brace
r_if
c_cond
(paren
id|options-&gt;warn_on_too_large_rename
)paren
id|warning
c_func
(paren
l_string|&quot;too many files (created: %d deleted: %d), skipping inexact rename detection&quot;
comma
id|num_create
comma
id|num_src
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|mx
op_assign
id|xcalloc
c_func
(paren
id|num_create
op_star
id|NUM_CANDIDATE_PER_DST
comma
r_sizeof
(paren
op_star
id|mx
)paren
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
r_struct
id|diff_score
op_star
id|m
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
id|m
op_assign
op_amp
id|mx
(braket
id|dst_cnt
op_star
id|NUM_CANDIDATE_PER_DST
)braket
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
id|NUM_CANDIDATE_PER_DST
suffix:semicolon
id|j
op_increment
)paren
id|m
(braket
id|j
)braket
dot
id|dst
op_assign
l_int|1
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
id|this_src
suffix:semicolon
id|this_src.score
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
id|this_src.name_score
op_assign
id|basename_same
c_func
(paren
id|one
comma
id|two
)paren
suffix:semicolon
id|this_src.dst
op_assign
id|i
suffix:semicolon
id|this_src.src
op_assign
id|j
suffix:semicolon
id|record_if_better
c_func
(paren
id|m
comma
op_amp
id|this_src
)paren
suffix:semicolon
id|diff_free_filespec_blob
c_func
(paren
id|one
)paren
suffix:semicolon
)brace
multiline_comment|/* We do not need the text anymore */
id|diff_free_filespec_blob
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
id|dst_cnt
op_star
id|NUM_CANDIDATE_PER_DST
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
id|dst_cnt
op_star
id|NUM_CANDIDATE_PER_DST
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_rename_dst
op_star
id|dst
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mx
(braket
id|i
)braket
dot
id|dst
OL
l_int|0
)paren
op_logical_or
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
)paren
r_break
suffix:semicolon
multiline_comment|/* there is no more usable pair. */
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
id|rename_src
(braket
id|mx
(braket
id|i
)braket
dot
id|src
)braket
dot
id|one-&gt;rename_used
)paren
r_continue
suffix:semicolon
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dst_cnt
op_star
id|NUM_CANDIDATE_PER_DST
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_rename_dst
op_star
id|dst
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mx
(braket
id|i
)braket
dot
id|dst
OL
l_int|0
)paren
op_logical_or
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
)paren
r_break
suffix:semicolon
multiline_comment|/* there is no more usable pair. */
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
r_if
c_cond
(paren
id|p-&gt;one-&gt;rename_used
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
id|free_filespec
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
