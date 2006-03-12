multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
DECL|function|should_break
r_static
r_int
id|should_break
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
id|break_score
comma
r_int
op_star
id|merge_score_p
)paren
(brace
multiline_comment|/* dst is recorded as a modification of src.  Are they so&n;&t; * different that we are better off recording this as a pair&n;&t; * of delete and create?&n;&t; *&n;&t; * There are two criteria used in this algorithm.  For the&n;&t; * purposes of helping later rename/copy, we take both delete&n;&t; * and insert into account and estimate the amount of &quot;edit&quot;.&n;&t; * If the edit is very large, we break this pair so that&n;&t; * rename/copy can pick the pieces up to match with other&n;&t; * files.&n;&t; *&n;&t; * On the other hand, we would want to ignore inserts for the&n;&t; * pure &quot;complete rewrite&quot; detection.  As long as most of the&n;&t; * existing contents were removed from the file, it is a&n;&t; * complete rewrite, and if sizable chunk from the original&n;&t; * still remains in the result, it is not a rewrite.  It does&n;&t; * not matter how much or how little new material is added to&n;&t; * the file.&n;&t; *&n;&t; * The score we leave for such a broken filepair uses the&n;&t; * latter definition so that later clean-up stage can find the&n;&t; * pieces that should not have been broken according to the&n;&t; * latter definition after rename/copy runs, and merge the&n;&t; * broken pair that have a score lower than given criteria&n;&t; * back together.  The break operation itself happens&n;&t; * according to the former definition.&n;&t; *&n;&t; * The minimum_edit parameter tells us when to break (the&n;&t; * amount of &quot;edit&quot; required for us to consider breaking the&n;&t; * pair).  We leave the amount of deletion in *merge_score_p&n;&t; * when we return.&n;&t; *&n;&t; * The value we return is 1 if we want the pair to be broken,&n;&t; * or 0 if we do not.&n;&t; */
r_int
r_int
id|delta_size
comma
id|base_size
comma
id|src_copied
comma
id|literal_added
comma
id|src_removed
suffix:semicolon
op_star
id|merge_score_p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* assume no deletion --- &quot;do not break&quot;&n;&t;&t;&t;     * is the default.&n;&t;&t;&t;     */
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
multiline_comment|/* leave symlink rename alone */
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
l_int|0
suffix:semicolon
multiline_comment|/* they are the same */
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
r_if
c_cond
(paren
id|base_size
OL
id|MINIMUM_BREAK_SIZE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we do not break too small filepair */
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
l_int|NULL
comma
l_int|NULL
comma
l_int|0
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
multiline_comment|/* sanity */
r_if
c_cond
(paren
id|src-&gt;size
OL
id|src_copied
)paren
id|src_copied
op_assign
id|src-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;size
OL
id|literal_added
op_plus
id|src_copied
)paren
(brace
r_if
c_cond
(paren
id|src_copied
OL
id|dst-&gt;size
)paren
id|literal_added
op_assign
id|dst-&gt;size
id|src_copied
suffix:semicolon
r_else
id|literal_added
op_assign
l_int|0
suffix:semicolon
)brace
id|src_removed
op_assign
id|src-&gt;size
id|src_copied
suffix:semicolon
multiline_comment|/* Compute merge-score, which is &quot;how much is removed&n;&t; * from the source material&quot;.  The clean-up stage will&n;&t; * merge the surviving pair together if the score is&n;&t; * less than the minimum, after rename/copy runs.&n;&t; */
op_star
id|merge_score_p
op_assign
id|src_removed
op_star
id|MAX_SCORE
op_div
id|src-&gt;size
suffix:semicolon
multiline_comment|/* Extent of damage, which counts both inserts and&n;&t; * deletes.&n;&t; */
id|delta_size
op_assign
id|src_removed
op_plus
id|literal_added
suffix:semicolon
r_if
c_cond
(paren
id|delta_size
op_star
id|MAX_SCORE
op_div
id|base_size
OL
id|break_score
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* If you removed a lot without adding new material, that is&n;&t; * not really a rewrite.&n;&t; */
r_if
c_cond
(paren
(paren
id|src-&gt;size
op_star
id|break_score
OL
id|src_removed
op_star
id|MAX_SCORE
)paren
op_logical_and
(paren
id|literal_added
op_star
l_int|20
OL
id|src_removed
)paren
op_logical_and
(paren
id|literal_added
op_star
l_int|20
OL
id|src_copied
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|diffcore_break
r_void
id|diffcore_break
c_func
(paren
r_int
id|break_score
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
multiline_comment|/* When the filepair has this much edit (insert and delete),&n;&t; * it is first considered to be a rewrite and broken into a&n;&t; * create and delete filepair.  This is to help breaking a&n;&t; * file that had too much new stuff added, possibly from&n;&t; * moving contents from another file, so that rename/copy can&n;&t; * match it with the other file.&n;&t; *&n;&t; * int break_score; we reuse incoming parameter for this.&n;&t; */
multiline_comment|/* After a pair is broken according to break_score and&n;&t; * subjected to rename/copy, both of them may survive intact,&n;&t; * due to lack of suitable rename/copy peer.  Or, the caller&n;&t; * may be calling us without using rename/copy.  When that&n;&t; * happens, we merge the broken pieces back into one&n;&t; * modification together if the pair did not have more than&n;&t; * this much delete.  For this computation, we do not take&n;&t; * insert into account at all.  If you start from a 100-line&n;&t; * file and delete 97 lines of it, it does not matter if you&n;&t; * add 27 lines to it to make a new 30-line file or if you add&n;&t; * 997 lines to it to make a 1000-line file.  Either way what&n;&t; * you did was a rewrite of 97%.  On the other hand, if you&n;&t; * delete 3 lines, keeping 97 lines intact, it does not matter&n;&t; * if you add 3 lines to it to make a new 100-line file or if&n;&t; * you add 903 lines to it to make a new 1000-line file.&n;&t; * Either way you did a lot of additions and not a rewrite.&n;&t; * This merge happens to catch the latter case.  A merge_score&n;&t; * of 80% would be a good default value (a broken pair that&n;&t; * has score lower than merge_score will be merged back&n;&t; * together).&n;&t; */
r_int
id|merge_score
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* See comment on DEFAULT_BREAK_SCORE and&n;&t; * DEFAULT_MERGE_SCORE in diffcore.h&n;&t; */
id|merge_score
op_assign
(paren
id|break_score
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|break_score
op_assign
(paren
id|break_score
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|break_score
)paren
id|break_score
op_assign
id|DEFAULT_BREAK_SCORE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|merge_score
)paren
id|merge_score
op_assign
id|DEFAULT_MERGE_SCORE
suffix:semicolon
id|outq.nr
op_assign
id|outq.alloc
op_assign
l_int|0
suffix:semicolon
id|outq.queue
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
r_int
id|score
suffix:semicolon
multiline_comment|/* We deal only with in-place edit of non directory.&n;&t;&t; * We do not break anything else.&n;&t;&t; */
r_if
c_cond
(paren
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
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|p-&gt;one-&gt;mode
)paren
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|p-&gt;two-&gt;mode
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;one-&gt;path
comma
id|p-&gt;two-&gt;path
)paren
)paren
(brace
r_if
c_cond
(paren
id|should_break
c_func
(paren
id|p-&gt;one
comma
id|p-&gt;two
comma
id|break_score
comma
op_amp
id|score
)paren
)paren
(brace
multiline_comment|/* Split this into delete and create */
r_struct
id|diff_filespec
op_star
id|null_one
comma
op_star
id|null_two
suffix:semicolon
r_struct
id|diff_filepair
op_star
id|dp
suffix:semicolon
multiline_comment|/* Set score to 0 for the pair that&n;&t;&t;&t;&t; * needs to be merged back together&n;&t;&t;&t;&t; * should they survive rename/copy.&n;&t;&t;&t;&t; * Also we do not want to break very&n;&t;&t;&t;&t; * small files.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|score
OL
id|merge_score
)paren
id|score
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* deletion of one */
id|null_one
op_assign
id|alloc_filespec
c_func
(paren
id|p-&gt;one-&gt;path
)paren
suffix:semicolon
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
id|null_one
)paren
suffix:semicolon
id|dp-&gt;score
op_assign
id|score
suffix:semicolon
id|dp-&gt;broken_pair
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* creation of two */
id|null_two
op_assign
id|alloc_filespec
c_func
(paren
id|p-&gt;two-&gt;path
)paren
suffix:semicolon
id|dp
op_assign
id|diff_queue
c_func
(paren
op_amp
id|outq
comma
id|null_two
comma
id|p-&gt;two
)paren
suffix:semicolon
id|dp-&gt;score
op_assign
id|score
suffix:semicolon
id|dp-&gt;broken_pair
op_assign
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* not diff_free_filepair(), we are&n;&t;&t;&t;&t;&t;  * reusing one and two here.&n;&t;&t;&t;&t;&t;  */
r_continue
suffix:semicolon
)brace
)brace
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
r_return
suffix:semicolon
)brace
DECL|function|merge_broken
r_static
r_void
id|merge_broken
c_func
(paren
r_struct
id|diff_filepair
op_star
id|p
comma
r_struct
id|diff_filepair
op_star
id|pp
comma
r_struct
id|diff_queue_struct
op_star
id|outq
)paren
(brace
multiline_comment|/* p and pp are broken pairs we want to merge */
r_struct
id|diff_filepair
op_star
id|c
op_assign
id|p
comma
op_star
id|d
op_assign
id|pp
comma
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
)paren
(brace
multiline_comment|/* this must be a delete half */
id|d
op_assign
id|p
suffix:semicolon
id|c
op_assign
id|pp
suffix:semicolon
)brace
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|d-&gt;one
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error in merge #1&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_FILE_VALID
c_func
(paren
id|d-&gt;two
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error in merge #2&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_FILE_VALID
c_func
(paren
id|c-&gt;one
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error in merge #3&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|c-&gt;two
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error in merge #4&quot;
)paren
suffix:semicolon
id|dp
op_assign
id|diff_queue
c_func
(paren
id|outq
comma
id|d-&gt;one
comma
id|c-&gt;two
)paren
suffix:semicolon
id|dp-&gt;score
op_assign
id|p-&gt;score
suffix:semicolon
id|diff_free_filespec_data
c_func
(paren
id|d-&gt;two
)paren
suffix:semicolon
id|diff_free_filespec_data
c_func
(paren
id|c-&gt;one
)paren
suffix:semicolon
id|free
c_func
(paren
id|d
)paren
suffix:semicolon
id|free
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|diffcore_merge_broken
r_void
id|diffcore_merge_broken
c_func
(paren
r_void
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
r_int
id|i
comma
id|j
suffix:semicolon
id|outq.nr
op_assign
id|outq.alloc
op_assign
l_int|0
suffix:semicolon
id|outq.queue
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
id|p
)paren
multiline_comment|/* we already merged this with its peer */
r_continue
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;broken_pair
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;one-&gt;path
comma
id|p-&gt;two-&gt;path
)paren
)paren
(brace
multiline_comment|/* If the peer also survived rename/copy, then&n;&t;&t;&t; * we merge them back together.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|j
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
OL
id|q-&gt;nr
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|pp
op_assign
id|q-&gt;queue
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;broken_pair
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|pp-&gt;one-&gt;path
comma
id|pp-&gt;two-&gt;path
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;one-&gt;path
comma
id|pp-&gt;two-&gt;path
)paren
)paren
(brace
multiline_comment|/* Peer survived.  Merge them */
id|merge_broken
c_func
(paren
id|p
comma
id|pp
comma
op_amp
id|outq
)paren
suffix:semicolon
id|q-&gt;queue
(braket
id|j
)braket
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|q-&gt;nr
op_le
id|j
)paren
multiline_comment|/* The peer did not survive, so we keep&n;&t;&t;&t;&t; * it in the output.&n;&t;&t;&t;&t; */
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
r_return
suffix:semicolon
)brace
eof
