multiline_comment|/*&n; * Copyright (C) 2010, Google Inc.&n; * and other copyright owners as documented in JGit&squot;s IP log.&n; *&n; * This program and the accompanying materials are made available&n; * under the terms of the Eclipse Distribution License v1.0 which&n; * accompanies this distribution, is reproduced below, and is&n; * available at http://www.eclipse.org/org/documents/edl-v10.php&n; *&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or&n; * without modification, are permitted provided that the following&n; * conditions are met:&n; *&n; * - Redistributions of source code must retain the above copyright&n; *   notice, this list of conditions and the following disclaimer.&n; *&n; * - Redistributions in binary form must reproduce the above&n; *   copyright notice, this list of conditions and the following&n; *   disclaimer in the documentation and/or other materials provided&n; *   with the distribution.&n; *&n; * - Neither the name of the Eclipse Foundation, Inc. nor the&n; *   names of its contributors may be used to endorse or promote&n; *   products derived from this software without specific prior&n; *   written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND&n; * CONTRIBUTORS &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR&n; * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,&n; * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;&n; * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)&n; * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF&n; * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
macro_line|#include &quot;xinclude.h&quot;
macro_line|#include &quot;xtypes.h&quot;
macro_line|#include &quot;xdiff.h&quot;
DECL|macro|MAX_PTR
mdefine_line|#define MAX_PTR&t;UINT_MAX
DECL|macro|MAX_CNT
mdefine_line|#define MAX_CNT&t;UINT_MAX
DECL|macro|LINE_END
mdefine_line|#define LINE_END(n) (line##n + count##n - 1)
DECL|macro|LINE_END_PTR
mdefine_line|#define LINE_END_PTR(n) (*line##n + *count##n - 1)
DECL|struct|histindex
r_struct
id|histindex
(brace
DECL|struct|record
r_struct
id|record
(brace
DECL|member|ptr
DECL|member|cnt
r_int
r_int
id|ptr
comma
id|cnt
suffix:semicolon
DECL|member|next
r_struct
id|record
op_star
id|next
suffix:semicolon
DECL|member|records
)brace
op_star
op_star
id|records
comma
multiline_comment|/* an occurrence */
DECL|member|line_map
op_star
op_star
id|line_map
suffix:semicolon
multiline_comment|/* map of line to record chain */
DECL|member|rcha
id|chastore_t
id|rcha
suffix:semicolon
DECL|member|next_ptrs
r_int
r_int
op_star
id|next_ptrs
suffix:semicolon
DECL|member|table_bits
r_int
r_int
id|table_bits
comma
DECL|member|records_size
id|records_size
comma
DECL|member|line_map_size
id|line_map_size
suffix:semicolon
DECL|member|max_chain_length
r_int
r_int
id|max_chain_length
comma
DECL|member|key_shift
id|key_shift
comma
DECL|member|ptr_shift
id|ptr_shift
suffix:semicolon
DECL|member|cnt
r_int
r_int
id|cnt
comma
DECL|member|has_common
id|has_common
suffix:semicolon
DECL|member|env
id|xdfenv_t
op_star
id|env
suffix:semicolon
DECL|member|xpp
id|xpparam_t
r_const
op_star
id|xpp
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|region
r_struct
id|region
(brace
DECL|member|begin1
DECL|member|end1
r_int
r_int
id|begin1
comma
id|end1
suffix:semicolon
DECL|member|begin2
DECL|member|end2
r_int
r_int
id|begin2
comma
id|end2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LINE_MAP
mdefine_line|#define LINE_MAP(i, a) (i-&gt;line_map[(a) - i-&gt;ptr_shift])
DECL|macro|NEXT_PTR
mdefine_line|#define NEXT_PTR(index, ptr) &bslash;&n;&t;(index-&gt;next_ptrs[(ptr) - index-&gt;ptr_shift])
DECL|macro|CNT
mdefine_line|#define CNT(index, ptr) &bslash;&n;&t;((LINE_MAP(index, ptr))-&gt;cnt)
DECL|macro|REC
mdefine_line|#define REC(env, s, l) &bslash;&n;&t;(env-&gt;xdf##s.recs[l - 1])
DECL|function|cmp_recs
r_static
r_int
id|cmp_recs
c_func
(paren
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xrecord_t
op_star
id|r1
comma
id|xrecord_t
op_star
id|r2
)paren
(brace
r_return
id|r1-&gt;ha
op_eq
id|r2-&gt;ha
op_logical_and
id|xdl_recmatch
c_func
(paren
id|r1-&gt;ptr
comma
id|r1-&gt;size
comma
id|r2-&gt;ptr
comma
id|r2-&gt;size
comma
id|xpp-&gt;flags
)paren
suffix:semicolon
)brace
DECL|macro|CMP_ENV
mdefine_line|#define CMP_ENV(xpp, env, s1, l1, s2, l2) &bslash;&n;&t;(cmp_recs(xpp, REC(env, s1, l1), REC(env, s2, l2)))
DECL|macro|CMP
mdefine_line|#define CMP(i, s1, l1, s2, l2) &bslash;&n;&t;(cmp_recs(i-&gt;xpp, REC(i-&gt;env, s1, l1), REC(i-&gt;env, s2, l2)))
DECL|macro|TABLE_HASH
mdefine_line|#define TABLE_HASH(index, side, line) &bslash;&n;&t;XDL_HASHLONG((REC(index-&gt;env, side, line))-&gt;ha, index-&gt;table_bits)
DECL|function|scanA
r_static
r_int
id|scanA
c_func
(paren
r_struct
id|histindex
op_star
id|index
comma
r_int
id|line1
comma
r_int
id|count1
)paren
(brace
r_int
r_int
id|ptr
comma
id|tbl_idx
suffix:semicolon
r_int
r_int
id|chain_len
suffix:semicolon
r_struct
id|record
op_star
op_star
id|rec_chain
comma
op_star
id|rec
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|LINE_END
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|line1
op_le
id|ptr
suffix:semicolon
id|ptr
op_decrement
)paren
(brace
id|tbl_idx
op_assign
id|TABLE_HASH
c_func
(paren
id|index
comma
l_int|1
comma
id|ptr
)paren
suffix:semicolon
id|rec_chain
op_assign
id|index-&gt;records
op_plus
id|tbl_idx
suffix:semicolon
id|rec
op_assign
op_star
id|rec_chain
suffix:semicolon
id|chain_len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|rec
)paren
(brace
r_if
c_cond
(paren
id|CMP
c_func
(paren
id|index
comma
l_int|1
comma
id|rec-&gt;ptr
comma
l_int|1
comma
id|ptr
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * ptr is identical to another element. Insert&n;&t;&t;&t;&t; * it onto the front of the existing element&n;&t;&t;&t;&t; * chain.&n;&t;&t;&t;&t; */
id|NEXT_PTR
c_func
(paren
id|index
comma
id|ptr
)paren
op_assign
id|rec-&gt;ptr
suffix:semicolon
id|rec-&gt;ptr
op_assign
id|ptr
suffix:semicolon
multiline_comment|/* cap rec-&gt;cnt at MAX_CNT */
id|rec-&gt;cnt
op_assign
id|XDL_MIN
c_func
(paren
id|MAX_CNT
comma
id|rec-&gt;cnt
op_plus
l_int|1
)paren
suffix:semicolon
id|LINE_MAP
c_func
(paren
id|index
comma
id|ptr
)paren
op_assign
id|rec
suffix:semicolon
r_goto
id|continue_scan
suffix:semicolon
)brace
id|rec
op_assign
id|rec-&gt;next
suffix:semicolon
id|chain_len
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chain_len
op_eq
id|index-&gt;max_chain_length
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This is the first time we have ever seen this particular&n;&t;&t; * element in the sequence. Construct a new chain for it.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|rec
op_assign
id|xdl_cha_alloc
c_func
(paren
op_amp
id|index-&gt;rcha
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|rec-&gt;ptr
op_assign
id|ptr
suffix:semicolon
id|rec-&gt;cnt
op_assign
l_int|1
suffix:semicolon
id|rec-&gt;next
op_assign
op_star
id|rec_chain
suffix:semicolon
op_star
id|rec_chain
op_assign
id|rec
suffix:semicolon
id|LINE_MAP
c_func
(paren
id|index
comma
id|ptr
)paren
op_assign
id|rec
suffix:semicolon
id|continue_scan
suffix:colon
suffix:semicolon
multiline_comment|/* no op */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|try_lcs
r_static
r_int
id|try_lcs
c_func
(paren
r_struct
id|histindex
op_star
id|index
comma
r_struct
id|region
op_star
id|lcs
comma
r_int
id|b_ptr
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
r_int
r_int
id|b_next
op_assign
id|b_ptr
op_plus
l_int|1
suffix:semicolon
r_struct
id|record
op_star
id|rec
op_assign
id|index-&gt;records
(braket
id|TABLE_HASH
c_func
(paren
id|index
comma
l_int|2
comma
id|b_ptr
)paren
)braket
suffix:semicolon
r_int
r_int
id|as
comma
id|ae
comma
id|bs
comma
id|be
comma
id|np
comma
id|rc
suffix:semicolon
r_int
id|should_break
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|rec
suffix:semicolon
id|rec
op_assign
id|rec-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|rec-&gt;cnt
OG
id|index-&gt;cnt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|index-&gt;has_common
)paren
id|index-&gt;has_common
op_assign
id|CMP
c_func
(paren
id|index
comma
l_int|1
comma
id|rec-&gt;ptr
comma
l_int|2
comma
id|b_ptr
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|as
op_assign
id|rec-&gt;ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CMP
c_func
(paren
id|index
comma
l_int|1
comma
id|as
comma
l_int|2
comma
id|b_ptr
)paren
)paren
r_continue
suffix:semicolon
id|index-&gt;has_common
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|should_break
op_assign
l_int|0
suffix:semicolon
id|np
op_assign
id|NEXT_PTR
c_func
(paren
id|index
comma
id|as
)paren
suffix:semicolon
id|bs
op_assign
id|b_ptr
suffix:semicolon
id|ae
op_assign
id|as
suffix:semicolon
id|be
op_assign
id|bs
suffix:semicolon
id|rc
op_assign
id|rec-&gt;cnt
suffix:semicolon
r_while
c_loop
(paren
id|line1
OL
id|as
op_logical_and
id|line2
OL
id|bs
op_logical_and
id|CMP
c_func
(paren
id|index
comma
l_int|1
comma
id|as
l_int|1
comma
l_int|2
comma
id|bs
l_int|1
)paren
)paren
(brace
id|as
op_decrement
suffix:semicolon
id|bs
op_decrement
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|rc
)paren
id|rc
op_assign
id|XDL_MIN
c_func
(paren
id|rc
comma
id|CNT
c_func
(paren
id|index
comma
id|as
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ae
OL
id|LINE_END
c_func
(paren
l_int|1
)paren
op_logical_and
id|be
OL
id|LINE_END
c_func
(paren
l_int|2
)paren
op_logical_and
id|CMP
c_func
(paren
id|index
comma
l_int|1
comma
id|ae
op_plus
l_int|1
comma
l_int|2
comma
id|be
op_plus
l_int|1
)paren
)paren
(brace
id|ae
op_increment
suffix:semicolon
id|be
op_increment
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|rc
)paren
id|rc
op_assign
id|XDL_MIN
c_func
(paren
id|rc
comma
id|CNT
c_func
(paren
id|index
comma
id|ae
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b_next
op_le
id|be
)paren
id|b_next
op_assign
id|be
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lcs-&gt;end1
id|lcs-&gt;begin1
OL
id|ae
id|as
op_logical_or
id|rc
OL
id|index-&gt;cnt
)paren
(brace
id|lcs-&gt;begin1
op_assign
id|as
suffix:semicolon
id|lcs-&gt;begin2
op_assign
id|bs
suffix:semicolon
id|lcs-&gt;end1
op_assign
id|ae
suffix:semicolon
id|lcs-&gt;end2
op_assign
id|be
suffix:semicolon
id|index-&gt;cnt
op_assign
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
id|np
op_le
id|ae
)paren
(brace
id|np
op_assign
id|NEXT_PTR
c_func
(paren
id|index
comma
id|np
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|0
)paren
(brace
id|should_break
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|should_break
)paren
r_break
suffix:semicolon
id|as
op_assign
id|np
suffix:semicolon
)brace
)brace
r_return
id|b_next
suffix:semicolon
)brace
DECL|function|find_lcs
r_static
r_int
id|find_lcs
c_func
(paren
r_struct
id|histindex
op_star
id|index
comma
r_struct
id|region
op_star
id|lcs
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
r_int
id|b_ptr
suffix:semicolon
r_if
c_cond
(paren
id|scanA
c_func
(paren
id|index
comma
id|line1
comma
id|count1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|index-&gt;cnt
op_assign
id|index-&gt;max_chain_length
op_plus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|b_ptr
op_assign
id|line2
suffix:semicolon
id|b_ptr
op_le
id|LINE_END
c_func
(paren
l_int|2
)paren
suffix:semicolon
)paren
id|b_ptr
op_assign
id|try_lcs
c_func
(paren
id|index
comma
id|lcs
comma
id|b_ptr
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
suffix:semicolon
r_return
id|index-&gt;has_common
op_logical_and
id|index-&gt;max_chain_length
OL
id|index-&gt;cnt
suffix:semicolon
)brace
DECL|function|fall_back_to_classic_diff
r_static
r_int
id|fall_back_to_classic_diff
c_func
(paren
r_struct
id|histindex
op_star
id|index
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
id|xpparam_t
id|xpp
suffix:semicolon
id|xpp.flags
op_assign
id|index-&gt;xpp-&gt;flags
op_amp
op_complement
id|XDF_DIFF_ALGORITHM_MASK
suffix:semicolon
r_return
id|xdl_fall_back_diff
c_func
(paren
id|index-&gt;env
comma
op_amp
id|xpp
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
suffix:semicolon
)brace
DECL|function|histogram_diff
r_static
r_int
id|histogram_diff
c_func
(paren
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|env
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
r_struct
id|histindex
id|index
suffix:semicolon
r_struct
id|region
id|lcs
suffix:semicolon
r_int
id|sz
suffix:semicolon
r_int
id|result
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count1
op_le
l_int|0
op_logical_and
id|count2
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|LINE_END
c_func
(paren
l_int|1
)paren
op_ge
id|MAX_PTR
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count1
)paren
(brace
r_while
c_loop
(paren
id|count2
op_decrement
)paren
(brace
id|env-&gt;xdf2.rchg
(braket
id|line2
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|count2
)paren
(brace
r_while
c_loop
(paren
id|count1
op_decrement
)paren
(brace
id|env-&gt;xdf1.rchg
(braket
id|line1
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|index
comma
l_int|0
comma
r_sizeof
(paren
id|index
)paren
)paren
suffix:semicolon
id|index.env
op_assign
id|env
suffix:semicolon
id|index.xpp
op_assign
id|xpp
suffix:semicolon
id|index.records
op_assign
l_int|NULL
suffix:semicolon
id|index.line_map
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* in case of early xdl_cha_free() */
id|index.rcha.head
op_assign
l_int|NULL
suffix:semicolon
id|index.table_bits
op_assign
id|xdl_hashbits
c_func
(paren
id|count1
)paren
suffix:semicolon
id|sz
op_assign
id|index.records_size
op_assign
l_int|1
op_lshift
id|index.table_bits
suffix:semicolon
id|sz
op_mul_assign
r_sizeof
(paren
r_struct
id|record
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|index.records
op_assign
(paren
r_struct
id|record
op_star
op_star
)paren
id|xdl_malloc
c_func
(paren
id|sz
)paren
)paren
)paren
r_goto
id|cleanup
suffix:semicolon
id|memset
c_func
(paren
id|index.records
comma
l_int|0
comma
id|sz
)paren
suffix:semicolon
id|sz
op_assign
id|index.line_map_size
op_assign
id|count1
suffix:semicolon
id|sz
op_mul_assign
r_sizeof
(paren
r_struct
id|record
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|index.line_map
op_assign
(paren
r_struct
id|record
op_star
op_star
)paren
id|xdl_malloc
c_func
(paren
id|sz
)paren
)paren
)paren
r_goto
id|cleanup
suffix:semicolon
id|memset
c_func
(paren
id|index.line_map
comma
l_int|0
comma
id|sz
)paren
suffix:semicolon
id|sz
op_assign
id|index.line_map_size
suffix:semicolon
id|sz
op_mul_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|index.next_ptrs
op_assign
(paren
r_int
r_int
op_star
)paren
id|xdl_malloc
c_func
(paren
id|sz
)paren
)paren
)paren
r_goto
id|cleanup
suffix:semicolon
id|memset
c_func
(paren
id|index.next_ptrs
comma
l_int|0
comma
id|sz
)paren
suffix:semicolon
multiline_comment|/* lines / 4 + 1 comes from xprepare.c:xdl_prepare_ctx() */
r_if
c_cond
(paren
id|xdl_cha_init
c_func
(paren
op_amp
id|index.rcha
comma
r_sizeof
(paren
r_struct
id|record
)paren
comma
id|count1
op_div
l_int|4
op_plus
l_int|1
)paren
OL
l_int|0
)paren
r_goto
id|cleanup
suffix:semicolon
id|index.ptr_shift
op_assign
id|line1
suffix:semicolon
id|index.max_chain_length
op_assign
l_int|64
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|lcs
comma
l_int|0
comma
r_sizeof
(paren
id|lcs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|find_lcs
c_func
(paren
op_amp
id|index
comma
op_amp
id|lcs
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
)paren
id|result
op_assign
id|fall_back_to_classic_diff
c_func
(paren
op_amp
id|index
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|lcs.begin1
op_eq
l_int|0
op_logical_and
id|lcs.begin2
op_eq
l_int|0
)paren
(brace
r_while
c_loop
(paren
id|count1
op_decrement
)paren
id|env-&gt;xdf1.rchg
(braket
id|line1
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|count2
op_decrement
)paren
id|env-&gt;xdf2.rchg
(braket
id|line2
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|histogram_diff
c_func
(paren
id|xpp
comma
id|env
comma
id|line1
comma
id|lcs.begin1
id|line1
comma
id|line2
comma
id|lcs.begin2
id|line2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|cleanup
suffix:semicolon
id|result
op_assign
id|histogram_diff
c_func
(paren
id|xpp
comma
id|env
comma
id|lcs.end1
op_plus
l_int|1
comma
id|LINE_END
c_func
(paren
l_int|1
)paren
id|lcs.end1
comma
id|lcs.end2
op_plus
l_int|1
comma
id|LINE_END
c_func
(paren
l_int|2
)paren
id|lcs.end2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
id|cleanup
suffix:colon
id|xdl_free
c_func
(paren
id|index.records
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|index.line_map
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|index.next_ptrs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|index.rcha
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|xdl_do_histogram_diff
r_int
id|xdl_do_histogram_diff
c_func
(paren
id|mmfile_t
op_star
id|file1
comma
id|mmfile_t
op_star
id|file2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|env
)paren
(brace
r_if
c_cond
(paren
id|xdl_prepare_env
c_func
(paren
id|file1
comma
id|file2
comma
id|xpp
comma
id|env
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|histogram_diff
c_func
(paren
id|xpp
comma
id|env
comma
id|env-&gt;xdf1.dstart
op_plus
l_int|1
comma
id|env-&gt;xdf1.dend
id|env-&gt;xdf1.dstart
op_plus
l_int|1
comma
id|env-&gt;xdf2.dstart
op_plus
l_int|1
comma
id|env-&gt;xdf2.dend
id|env-&gt;xdf2.dstart
op_plus
l_int|1
)paren
suffix:semicolon
)brace
eof
