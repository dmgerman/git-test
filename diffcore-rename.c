multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;delta.h&quot;
DECL|struct|diff_rename_pool
r_struct
id|diff_rename_pool
(brace
DECL|member|s
r_struct
id|diff_filespec
op_star
op_star
id|s
suffix:semicolon
DECL|member|nr
DECL|member|alloc
r_int
id|nr
comma
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|function|diff_rename_pool_clear
r_static
r_void
id|diff_rename_pool_clear
c_func
(paren
r_struct
id|diff_rename_pool
op_star
id|pool
)paren
(brace
id|pool-&gt;s
op_assign
l_int|NULL
suffix:semicolon
id|pool-&gt;nr
op_assign
id|pool-&gt;alloc
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|diff_rename_pool_add
r_static
r_void
id|diff_rename_pool_add
c_func
(paren
r_struct
id|diff_rename_pool
op_star
id|pool
comma
r_struct
id|diff_filespec
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|s-&gt;mode
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* no trees, please */
r_if
c_cond
(paren
id|pool-&gt;alloc
op_le
id|pool-&gt;nr
)paren
(brace
id|pool-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|pool-&gt;alloc
)paren
suffix:semicolon
id|pool-&gt;s
op_assign
id|xrealloc
c_func
(paren
id|pool-&gt;s
comma
r_sizeof
(paren
op_star
(paren
id|pool-&gt;s
)paren
)paren
op_star
id|pool-&gt;alloc
)paren
suffix:semicolon
)brace
id|pool-&gt;s
(braket
id|pool-&gt;nr
)braket
op_assign
id|s
suffix:semicolon
id|pool-&gt;nr
op_increment
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
id|memcmp
c_func
(paren
id|src-&gt;sha1
comma
id|dst-&gt;sha1
comma
l_int|20
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|src
)paren
op_logical_or
id|diff_populate_filespec
c_func
(paren
id|dst
)paren
)paren
multiline_comment|/* this is an error but will be caught downstream */
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
r_struct
id|diff_filespec
op_star
id|src
suffix:semicolon
DECL|member|dst
r_struct
id|diff_filespec
op_star
id|dst
suffix:semicolon
DECL|member|score
r_int
id|score
suffix:semicolon
DECL|member|rank
r_int
id|rank
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
multiline_comment|/* src points at a file that existed in the original tree (or&n;&t; * optionally a file in the destination tree) and dst points&n;&t; * at a newly created file.  They may be quite similar, in which&n;&t; * case we want to say src is renamed to dst or src is copied into&n;&t; * dst, and then some edit has been applied to dst.&n;&t; *&n;&t; * Compare them and return how similar they are, representing&n;&t; * the score as an integer between 0 and 10000, except&n;&t; * where they match exactly it is considered better than anything&n;&t; * else.&n;&t; */
r_void
op_star
id|delta
suffix:semicolon
r_int
r_int
id|delta_size
comma
id|base_size
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
id|delta_size
op_assign
(paren
(paren
id|src-&gt;size
OL
id|dst-&gt;size
)paren
ques
c_cond
(paren
id|dst-&gt;size
id|src-&gt;size
)paren
suffix:colon
(paren
id|src-&gt;size
id|dst-&gt;size
)paren
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
multiline_comment|/* We would not consider edits that change the file size so&n;&t; * drastically.  delta_size must be smaller than&n;&t; * (MAX_SCORE-minimum_score)/MAX_SCORE * min(src-&gt;size, dst-&gt;size).&n;&t; * Note that base_size == 0 case is handled here already&n;&t; * and the final score computation below would not have a&n;&t; * divide-by-zero issue.&n;&t; */
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
id|delta
op_assign
id|diff_delta
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
id|delta_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We currently punt here, but we may later end up parsing the&n;&t; * delta to really assess the extent of damage.  A big consecutive&n;&t; * remove would produce small delta_size that affects quite a&n;&t; * big portion of the file.&n;&t; */
id|free
c_func
(paren
id|delta
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now we will give some score to it.  100% edit gets 0 points&n;&t; * and 0% edit gets MAX_SCORE points.&n;&t; */
id|score
op_assign
id|MAX_SCORE
(paren
id|MAX_SCORE
op_star
id|delta_size
op_div
id|base_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|score
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|MAX_SCORE
OL
id|score
)paren
r_return
id|MAX_SCORE
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
r_struct
id|diff_queue_struct
op_star
id|outq
comma
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
id|rank
comma
r_int
id|score
)paren
(brace
multiline_comment|/* The rank is used to sort the final output, because there&n;&t; * are certain dependencies.&n;&t; *&n;&t; *  - rank #0 depends on deleted ones.&n;&t; *  - rank #1 depends on kept files before they are modified.&n;&t; *  - rank #2 depends on kept files after they are modified;&n;&t; *    currently not used.&n;&t; *&n;&t; * Therefore, the final output order should be:&n;&t; *&n;&t; *  1. rank #0 rename/copy diffs.&n;&t; *  2. deletions in the original.&n;&t; *  3. rank #1 rename/copy diffs.&n;&t; *  4. additions and modifications in the original.&n;&t; *  5. rank #2 rename/copy diffs; currently not used.&n;&t; *&n;&t; * To achieve this sort order, we give xform_work the number&n;&t; * above.&n;&t; */
r_struct
id|diff_filepair
op_star
id|dp
op_assign
id|diff_queue
c_func
(paren
id|outq
comma
id|src
comma
id|dst
)paren
suffix:semicolon
id|dp-&gt;xfrm_work
op_assign
(paren
id|rank
op_star
l_int|2
op_plus
l_int|1
)paren
op_or
(paren
id|score
op_lshift
id|RENAME_SCORE_SHIFT
)paren
suffix:semicolon
id|dst-&gt;xfrm_flags
op_or_assign
id|RENAME_DST_MATCHED
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|debug_filespec
c_func
(paren
r_struct
id|diff_filespec
op_star
id|s
comma
r_int
id|x
comma
r_const
r_char
op_star
id|one
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;queue[%d] %s (%s) %s %06o %s&bslash;n&quot;
comma
id|x
comma
id|one
comma
id|s-&gt;path
comma
id|DIFF_FILE_VALID
c_func
(paren
id|s
)paren
ques
c_cond
l_string|&quot;valid&quot;
suffix:colon
l_string|&quot;invalid&quot;
comma
id|s-&gt;mode
comma
id|s-&gt;sha1_valid
ques
c_cond
id|sha1_to_hex
c_func
(paren
id|s-&gt;sha1
)paren
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;queue[%d] %s size %lu flags %d&bslash;n&quot;
comma
id|x
comma
id|one
comma
id|s-&gt;size
comma
id|s-&gt;xfrm_flags
)paren
suffix:semicolon
)brace
r_static
r_void
id|debug_filepair
c_func
(paren
r_const
r_struct
id|diff_filepair
op_star
id|p
comma
r_int
id|i
)paren
(brace
id|debug_filespec
c_func
(paren
id|p-&gt;one
comma
id|i
comma
l_string|&quot;one&quot;
)paren
suffix:semicolon
id|debug_filespec
c_func
(paren
id|p-&gt;two
comma
id|i
comma
l_string|&quot;two&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;pair flags %d, orig order %d, score %d&bslash;n&quot;
comma
(paren
id|p-&gt;xfrm_work
op_amp
(paren
(paren
l_int|1
op_lshift
id|RENAME_SCORE_SHIFT
)paren
l_int|1
)paren
)paren
comma
id|p-&gt;orig_order
comma
(paren
id|p-&gt;xfrm_work
op_rshift
id|RENAME_SCORE_SHIFT
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|debug_queue
c_func
(paren
r_const
r_char
op_star
id|msg
comma
r_struct
id|diff_queue_struct
op_star
id|q
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|msg
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;q-&gt;nr = %d&bslash;n&quot;
comma
id|q-&gt;nr
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
id|debug_filepair
c_func
(paren
id|p
comma
id|i
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|macro|debug_queue
mdefine_line|#define debug_queue(a,b) do { ; /*nothing*/ } while(0)
macro_line|#endif
multiline_comment|/*&n; * We sort the outstanding diff entries according to the rank (see&n; * comment at the beginning of record_rename_pair) and tiebreak with&n; * the order in the original input.&n; */
DECL|function|rank_compare
r_static
r_int
id|rank_compare
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
id|diff_filepair
op_star
id|a
op_assign
op_star
(paren
r_const
r_struct
id|diff_filepair
op_star
op_star
)paren
id|a_
suffix:semicolon
r_const
r_struct
id|diff_filepair
op_star
id|b
op_assign
op_star
(paren
r_const
r_struct
id|diff_filepair
op_star
op_star
)paren
id|b_
suffix:semicolon
r_int
id|a_rank
op_assign
id|a-&gt;xfrm_work
op_amp
(paren
(paren
l_int|1
op_lshift
id|RENAME_SCORE_SHIFT
)paren
l_int|1
)paren
suffix:semicolon
r_int
id|b_rank
op_assign
id|b-&gt;xfrm_work
op_amp
(paren
(paren
l_int|1
op_lshift
id|RENAME_SCORE_SHIFT
)paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a_rank
op_ne
id|b_rank
)paren
r_return
id|a_rank
id|b_rank
suffix:semicolon
r_return
id|a-&gt;orig_order
id|b-&gt;orig_order
suffix:semicolon
)brace
multiline_comment|/*&n; * We sort the rename similarity matrix with the score, in descending&n; * order (more similar first).&n; */
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
DECL|function|needs_to_stay
r_static
r_int
id|needs_to_stay
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_int
id|i
comma
r_struct
id|diff_filespec
op_star
id|it
)paren
(brace
multiline_comment|/* If it will be used in later entry (either stay or used&n;&t; * as the source of rename/copy), we need to copy, not rename.&n;&t; */
r_while
c_loop
(paren
id|i
OL
id|q-&gt;nr
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
op_increment
)braket
suffix:semicolon
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
multiline_comment|/* removed is fine */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|p-&gt;one-&gt;path
comma
id|it-&gt;path
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* not relevant */
multiline_comment|/* p has its src set to *it and it is not a delete;&n;&t;&t; * it will be used for in-place change or rename/copy,&n;&t;&t; * so we cannot rename it out.&n;&t;&t; */
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_scoreopt_parse
r_int
id|diff_scoreopt_parse
c_func
(paren
r_const
r_char
op_star
id|opt
)paren
(brace
r_int
id|diglen
comma
id|num
comma
id|scale
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|opt
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
op_logical_or
(paren
id|opt
(braket
l_int|1
)braket
op_ne
l_char|&squot;M&squot;
op_logical_and
id|opt
(braket
l_int|1
)braket
op_ne
l_char|&squot;C&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* that is not a -M nor -C option */
id|diglen
op_assign
id|strspn
c_func
(paren
id|opt
op_plus
l_int|2
comma
l_string|&quot;0123456789&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diglen
op_eq
l_int|0
op_logical_or
id|strlen
c_func
(paren
id|opt
op_plus
l_int|2
)paren
op_ne
id|diglen
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* use default */
id|sscanf
c_func
(paren
id|opt
op_plus
l_int|2
comma
l_string|&quot;%d&quot;
comma
op_amp
id|num
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|scale
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|diglen
suffix:semicolon
id|i
op_increment
)paren
id|scale
op_mul_assign
l_int|10
suffix:semicolon
multiline_comment|/* user says num divided by scale and we say internally that&n;&t; * is MAX_SCORE * num / scale.&n;&t; */
r_return
id|MAX_SCORE
op_star
id|num
op_div
id|scale
suffix:semicolon
)brace
DECL|function|diffcore_rename
r_void
id|diffcore_rename
c_func
(paren
r_int
id|detect_rename
comma
r_int
id|minimum_score
)paren
(brace
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
id|diff_rename_pool
id|created
comma
id|deleted
comma
id|stay
suffix:semicolon
r_struct
id|diff_rename_pool
op_star
(paren
id|srcs
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_struct
id|diff_score
op_star
id|mx
suffix:semicolon
r_int
id|h
comma
id|i
comma
id|j
suffix:semicolon
r_int
id|num_create
comma
id|num_src
comma
id|dst_cnt
comma
id|src_cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minimum_score
)paren
id|minimum_score
op_assign
id|DEFAULT_MINIMUM_SCORE
suffix:semicolon
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
id|diff_rename_pool_clear
c_func
(paren
op_amp
id|created
)paren
suffix:semicolon
id|diff_rename_pool_clear
c_func
(paren
op_amp
id|deleted
)paren
suffix:semicolon
id|diff_rename_pool_clear
c_func
(paren
op_amp
id|stay
)paren
suffix:semicolon
id|srcs
(braket
l_int|0
)braket
op_assign
op_amp
id|deleted
suffix:semicolon
id|srcs
(braket
l_int|1
)braket
op_assign
op_amp
id|stay
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
id|diff_rename_pool_add
c_func
(paren
op_amp
id|created
comma
id|p-&gt;two
)paren
suffix:semicolon
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
id|diff_rename_pool_add
c_func
(paren
op_amp
id|deleted
comma
id|p-&gt;one
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|1
OL
id|detect_rename
)paren
multiline_comment|/* find copy, too */
id|diff_rename_pool_add
c_func
(paren
op_amp
id|stay
comma
id|p-&gt;one
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|created.nr
op_eq
l_int|0
)paren
r_goto
id|cleanup
suffix:semicolon
multiline_comment|/* nothing to do */
multiline_comment|/* We really want to cull the candidates list early&n;&t; * with cheap tests in order to avoid doing deltas.&n;&t; *&n;&t; * With the current callers, we should not have already&n;&t; * matched entries at this point, but it is nonetheless&n;&t; * checked for sanity.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|created.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|created.s
(braket
id|i
)braket
op_member_access_from_pointer
id|xfrm_flags
op_amp
id|RENAME_DST_MATCHED
)paren
r_continue
suffix:semicolon
multiline_comment|/* we have matched exactly already */
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
r_sizeof
(paren
id|srcs
)paren
op_div
r_sizeof
(paren
id|srcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|h
op_increment
)paren
(brace
r_struct
id|diff_rename_pool
op_star
id|p
op_assign
id|srcs
(braket
id|h
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
id|p-&gt;nr
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_exact_match
c_func
(paren
id|p-&gt;s
(braket
id|j
)braket
comma
id|created.s
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|record_rename_pair
c_func
(paren
op_amp
id|outq
comma
id|p-&gt;s
(braket
id|j
)braket
comma
id|created.s
(braket
id|i
)braket
comma
id|h
comma
id|MAX_SCORE
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* we are done with this entry */
)brace
)brace
)brace
id|debug_queue
c_func
(paren
l_string|&quot;done detecting exact&quot;
comma
op_amp
id|outq
)paren
suffix:semicolon
multiline_comment|/* Have we run out the created file pool?  If so we can avoid&n;&t; * doing the delta matrix altogether.&n;&t; */
r_if
c_cond
(paren
id|outq.nr
op_eq
id|created.nr
)paren
r_goto
id|flush_rest
suffix:semicolon
id|num_create
op_assign
(paren
id|created.nr
id|outq.nr
)paren
suffix:semicolon
id|num_src
op_assign
id|deleted.nr
op_plus
id|stay.nr
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
id|created.nr
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
r_if
c_cond
(paren
id|created.s
(braket
id|i
)braket
op_member_access_from_pointer
id|xfrm_flags
op_amp
id|RENAME_DST_MATCHED
)paren
r_continue
suffix:semicolon
multiline_comment|/* dealt with exact match already. */
r_for
c_loop
(paren
id|src_cnt
op_assign
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
r_sizeof
(paren
id|srcs
)paren
op_div
r_sizeof
(paren
id|srcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|h
op_increment
)paren
(brace
r_struct
id|diff_rename_pool
op_star
id|p
op_assign
id|srcs
(braket
id|h
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
id|p-&gt;nr
suffix:semicolon
id|j
op_increment
comma
id|src_cnt
op_increment
)paren
(brace
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
id|src_cnt
)braket
suffix:semicolon
id|m-&gt;src
op_assign
id|p-&gt;s
(braket
id|j
)braket
suffix:semicolon
id|m-&gt;dst
op_assign
id|created.s
(braket
id|i
)braket
suffix:semicolon
id|m-&gt;score
op_assign
id|estimate_similarity
c_func
(paren
id|m-&gt;src
comma
id|m-&gt;dst
comma
id|minimum_score
)paren
suffix:semicolon
id|m-&gt;rank
op_assign
id|h
suffix:semicolon
)brace
)brace
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
r_if
c_cond
(paren
id|mx
(braket
id|i
)braket
dot
id|dst-&gt;xfrm_flags
op_amp
id|RENAME_DST_MATCHED
)paren
r_continue
suffix:semicolon
multiline_comment|/* alreayd done, either exact or fuzzy. */
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
multiline_comment|/* there is not any more diffs applicable. */
id|record_rename_pair
c_func
(paren
op_amp
id|outq
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
id|dst
comma
id|mx
(braket
id|i
)braket
dot
id|rank
comma
id|mx
(braket
id|i
)braket
dot
id|score
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|mx
)paren
suffix:semicolon
id|debug_queue
c_func
(paren
l_string|&quot;done detecting fuzzy&quot;
comma
op_amp
id|outq
)paren
suffix:semicolon
id|flush_rest
suffix:colon
multiline_comment|/* At this point, we have found some renames and copies and they&n;&t; * are kept in outq.  The original list is still in *q.&n;&t; *&n;&t; * Scan the original list and move them into the outq; we will sort&n;&t; * outq and swap it into the queue supplied to pass that to&n;&t; * downstream, so we assign the sort keys in this loop.&n;&t; *&n;&t; * See comments at the top of record_rename_pair for numbers used&n;&t; * to assign xfrm_work.&n;&t; *&n;&t; * Note that we have not annotated the diff_filepair with any comment&n;&t; * so there is nothing other than p to free.&n;&t; */
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
id|dp
comma
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
multiline_comment|/* creation or unmerged entries */
id|dp
op_assign
id|diff_queue
c_func
(paren
op_amp
id|outq
comma
id|p-&gt;one
comma
id|p-&gt;two
)paren
suffix:semicolon
id|dp-&gt;xfrm_work
op_assign
l_int|4
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
multiline_comment|/* deletion */
id|dp
op_assign
id|diff_queue
c_func
(paren
op_amp
id|outq
comma
id|p-&gt;one
comma
id|p-&gt;two
)paren
suffix:semicolon
id|dp-&gt;xfrm_work
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* modification, or stay as is */
id|dp
op_assign
id|diff_queue
c_func
(paren
op_amp
id|outq
comma
id|p-&gt;one
comma
id|p-&gt;two
)paren
suffix:semicolon
id|dp-&gt;xfrm_work
op_assign
l_int|4
suffix:semicolon
)brace
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|debug_queue
c_func
(paren
l_string|&quot;done copying original&quot;
comma
op_amp
id|outq
)paren
suffix:semicolon
multiline_comment|/* Sort outq */
id|qsort
c_func
(paren
id|outq.queue
comma
id|outq.nr
comma
r_sizeof
(paren
id|outq.queue
(braket
l_int|0
)braket
)paren
comma
id|rank_compare
)paren
suffix:semicolon
id|debug_queue
c_func
(paren
l_string|&quot;done sorting&quot;
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
id|q-&gt;nr
op_assign
id|q-&gt;alloc
op_assign
l_int|0
suffix:semicolon
id|q-&gt;queue
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Copy it out to q, removing duplicates. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|outq.nr
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
id|outq.queue
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
multiline_comment|/* created or unmerged */
r_if
c_cond
(paren
id|p-&gt;two-&gt;xfrm_flags
op_amp
id|RENAME_DST_MATCHED
)paren
suffix:semicolon
multiline_comment|/* rename/copy created it already */
r_else
id|diff_queue
c_func
(paren
id|q
comma
id|p-&gt;one
comma
id|p-&gt;two
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
multiline_comment|/* deleted */
r_if
c_cond
(paren
id|p-&gt;one-&gt;xfrm_flags
op_amp
id|RENAME_SRC_GONE
)paren
suffix:semicolon
multiline_comment|/* rename/copy deleted it already */
r_else
id|diff_queue
c_func
(paren
id|q
comma
id|p-&gt;one
comma
id|p-&gt;two
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|p-&gt;one-&gt;path
comma
id|p-&gt;two-&gt;path
)paren
)paren
(brace
multiline_comment|/* rename or copy */
r_struct
id|diff_filepair
op_star
id|dp
op_assign
id|diff_queue
c_func
(paren
id|q
comma
id|p-&gt;one
comma
id|p-&gt;two
)paren
suffix:semicolon
r_int
id|msglen
op_assign
(paren
id|strlen
c_func
(paren
id|p-&gt;one-&gt;path
)paren
op_plus
id|strlen
c_func
(paren
id|p-&gt;two-&gt;path
)paren
op_plus
l_int|100
)paren
suffix:semicolon
r_int
id|score
op_assign
(paren
id|p-&gt;xfrm_work
op_rshift
id|RENAME_SCORE_SHIFT
)paren
suffix:semicolon
id|dp-&gt;xfrm_msg
op_assign
id|xmalloc
c_func
(paren
id|msglen
)paren
suffix:semicolon
multiline_comment|/* if we have a later entry that is a rename/copy&n;&t;&t;&t; * that depends on p-&gt;one, then we copy here.&n;&t;&t;&t; * otherwise we rename it.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|needs_to_stay
c_func
(paren
op_amp
id|outq
comma
id|i
op_plus
l_int|1
comma
id|p-&gt;one
)paren
)paren
(brace
multiline_comment|/* copy it */
id|sprintf
c_func
(paren
id|dp-&gt;xfrm_msg
comma
l_string|&quot;similarity index %d%%&bslash;n&quot;
l_string|&quot;copy from %s&bslash;n&quot;
l_string|&quot;copy to %s&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
l_float|0.5
op_plus
id|score
op_star
l_int|100
op_div
id|MAX_SCORE
)paren
comma
id|p-&gt;one-&gt;path
comma
id|p-&gt;two-&gt;path
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* rename it, and mark it as gone. */
id|p-&gt;one-&gt;xfrm_flags
op_or_assign
id|RENAME_SRC_GONE
suffix:semicolon
id|sprintf
c_func
(paren
id|dp-&gt;xfrm_msg
comma
l_string|&quot;similarity index %d%%&bslash;n&quot;
l_string|&quot;rename old %s&bslash;n&quot;
l_string|&quot;rename new %s&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
l_float|0.5
op_plus
id|score
op_star
l_int|100
op_div
id|MAX_SCORE
)paren
comma
id|p-&gt;one-&gt;path
comma
id|p-&gt;two-&gt;path
)paren
suffix:semicolon
)brace
)brace
r_else
multiline_comment|/* otherwise it is a modified (or stayed) entry */
id|diff_queue
c_func
(paren
id|q
comma
id|p-&gt;one
comma
id|p-&gt;two
)paren
suffix:semicolon
id|diff_free_filepair
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|outq.queue
)paren
suffix:semicolon
id|debug_queue
c_func
(paren
l_string|&quot;done collapsing&quot;
comma
id|q
)paren
suffix:semicolon
id|cleanup
suffix:colon
id|free
c_func
(paren
id|created.s
)paren
suffix:semicolon
id|free
c_func
(paren
id|deleted.s
)paren
suffix:semicolon
id|free
c_func
(paren
id|stay.s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
