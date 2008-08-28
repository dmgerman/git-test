multiline_comment|/*&n; *  LibXDiff by Davide Libenzi ( File Differential Library )&n; *  Copyright (C) 2003-2006 Davide Libenzi, Johannes E. Schindelin&n; *&n; *  This library is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU Lesser General Public&n; *  License as published by the Free Software Foundation; either&n; *  version 2.1 of the License, or (at your option) any later version.&n; *&n; *  This library is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  Lesser General Public License for more details.&n; *&n; *  You should have received a copy of the GNU Lesser General Public&n; *  License along with this library; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#include &quot;xinclude.h&quot;
DECL|struct|s_xdmerge
r_typedef
r_struct
id|s_xdmerge
(brace
DECL|member|next
r_struct
id|s_xdmerge
op_star
id|next
suffix:semicolon
multiline_comment|/*&n;&t; * 0 = conflict,&n;&t; * 1 = no conflict, take first,&n;&t; * 2 = no conflict, take second.&n;&t; */
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/*&n;&t; * These point at the respective postimages.  E.g. &lt;i1,chg1&gt; is&n;&t; * how side #1 wants to change the common ancestor; if there is no&n;&t; * overlap, lines before i1 in the postimage of side #1 appear&n;&t; * in the merge result as a region touched by neither side.&n;&t; */
DECL|member|i1
DECL|member|i2
r_int
id|i1
comma
id|i2
suffix:semicolon
DECL|member|chg1
DECL|member|chg2
r_int
id|chg1
comma
id|chg2
suffix:semicolon
multiline_comment|/*&n;&t; * These point at the preimage; of course there is just one&n;&t; * preimage, that is from the shared common ancestor.&n;&t; */
DECL|member|i0
r_int
id|i0
suffix:semicolon
DECL|member|chg0
r_int
id|chg0
suffix:semicolon
DECL|typedef|xdmerge_t
)brace
id|xdmerge_t
suffix:semicolon
DECL|function|xdl_append_merge
r_static
r_int
id|xdl_append_merge
c_func
(paren
id|xdmerge_t
op_star
op_star
id|merge
comma
r_int
id|mode
comma
r_int
id|i0
comma
r_int
id|chg0
comma
r_int
id|i1
comma
r_int
id|chg1
comma
r_int
id|i2
comma
r_int
id|chg2
)paren
(brace
id|xdmerge_t
op_star
id|m
op_assign
op_star
id|merge
suffix:semicolon
r_if
c_cond
(paren
id|m
op_logical_and
(paren
id|i1
op_le
id|m-&gt;i1
op_plus
id|m-&gt;chg1
op_logical_or
id|i2
op_le
id|m-&gt;i2
op_plus
id|m-&gt;chg2
)paren
)paren
(brace
r_if
c_cond
(paren
id|mode
op_ne
id|m-&gt;mode
)paren
id|m-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|m-&gt;chg0
op_assign
id|i0
op_plus
id|chg0
id|m-&gt;i0
suffix:semicolon
id|m-&gt;chg1
op_assign
id|i1
op_plus
id|chg1
id|m-&gt;i1
suffix:semicolon
id|m-&gt;chg2
op_assign
id|i2
op_plus
id|chg2
id|m-&gt;i2
suffix:semicolon
)brace
r_else
(brace
id|m
op_assign
id|xdl_malloc
c_func
(paren
r_sizeof
(paren
id|xdmerge_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
r_return
l_int|1
suffix:semicolon
id|m-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|m-&gt;mode
op_assign
id|mode
suffix:semicolon
id|m-&gt;i0
op_assign
id|i0
suffix:semicolon
id|m-&gt;chg0
op_assign
id|chg0
suffix:semicolon
id|m-&gt;i1
op_assign
id|i1
suffix:semicolon
id|m-&gt;chg1
op_assign
id|chg1
suffix:semicolon
id|m-&gt;i2
op_assign
id|i2
suffix:semicolon
id|m-&gt;chg2
op_assign
id|chg2
suffix:semicolon
r_if
c_cond
(paren
op_star
id|merge
)paren
(paren
op_star
id|merge
)paren
op_member_access_from_pointer
id|next
op_assign
id|m
suffix:semicolon
op_star
id|merge
op_assign
id|m
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_cleanup_merge
r_static
r_int
id|xdl_cleanup_merge
c_func
(paren
id|xdmerge_t
op_star
id|c
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|xdmerge_t
op_star
id|next_c
suffix:semicolon
multiline_comment|/* were there conflicts? */
r_for
c_loop
(paren
suffix:semicolon
id|c
suffix:semicolon
id|c
op_assign
id|next_c
)paren
(brace
r_if
c_cond
(paren
id|c-&gt;mode
op_eq
l_int|0
)paren
id|count
op_increment
suffix:semicolon
id|next_c
op_assign
id|c-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|xdl_merge_cmp_lines
r_static
r_int
id|xdl_merge_cmp_lines
c_func
(paren
id|xdfenv_t
op_star
id|xe1
comma
r_int
id|i1
comma
id|xdfenv_t
op_star
id|xe2
comma
r_int
id|i2
comma
r_int
id|line_count
comma
r_int
id|flags
)paren
(brace
r_int
id|i
suffix:semicolon
id|xrecord_t
op_star
op_star
id|rec1
op_assign
id|xe1-&gt;xdf2.recs
op_plus
id|i1
suffix:semicolon
id|xrecord_t
op_star
op_star
id|rec2
op_assign
id|xe2-&gt;xdf2.recs
op_plus
id|i2
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
id|line_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|result
op_assign
id|xdl_recmatch
c_func
(paren
id|rec1
(braket
id|i
)braket
op_member_access_from_pointer
id|ptr
comma
id|rec1
(braket
id|i
)braket
op_member_access_from_pointer
id|size
comma
id|rec2
(braket
id|i
)braket
op_member_access_from_pointer
id|ptr
comma
id|rec2
(braket
id|i
)braket
op_member_access_from_pointer
id|size
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_recs_copy_0
r_static
r_int
id|xdl_recs_copy_0
c_func
(paren
r_int
id|use_orig
comma
id|xdfenv_t
op_star
id|xe
comma
r_int
id|i
comma
r_int
id|count
comma
r_int
id|add_nl
comma
r_char
op_star
id|dest
)paren
(brace
id|xrecord_t
op_star
op_star
id|recs
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
id|recs
op_assign
(paren
id|use_orig
ques
c_cond
id|xe-&gt;xdf1.recs
suffix:colon
id|xe-&gt;xdf2.recs
)paren
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|1
)paren
r_return
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
id|count
suffix:semicolon
id|size
op_add_assign
id|recs
(braket
id|i
op_increment
)braket
op_member_access_from_pointer
id|size
)paren
r_if
c_cond
(paren
id|dest
)paren
id|memcpy
c_func
(paren
id|dest
op_plus
id|size
comma
id|recs
(braket
id|i
)braket
op_member_access_from_pointer
id|ptr
comma
id|recs
(braket
id|i
)braket
op_member_access_from_pointer
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_nl
)paren
(brace
id|i
op_assign
id|recs
(braket
id|count
l_int|1
)braket
op_member_access_from_pointer
id|size
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
op_logical_or
id|recs
(braket
id|count
l_int|1
)braket
op_member_access_from_pointer
id|ptr
(braket
id|i
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
id|dest
)paren
id|dest
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|size
op_increment
suffix:semicolon
)brace
)brace
r_return
id|size
suffix:semicolon
)brace
DECL|function|xdl_recs_copy
r_static
r_int
id|xdl_recs_copy
c_func
(paren
id|xdfenv_t
op_star
id|xe
comma
r_int
id|i
comma
r_int
id|count
comma
r_int
id|add_nl
comma
r_char
op_star
id|dest
)paren
(brace
r_return
id|xdl_recs_copy_0
c_func
(paren
l_int|0
comma
id|xe
comma
id|i
comma
id|count
comma
id|add_nl
comma
id|dest
)paren
suffix:semicolon
)brace
DECL|function|xdl_orig_copy
r_static
r_int
id|xdl_orig_copy
c_func
(paren
id|xdfenv_t
op_star
id|xe
comma
r_int
id|i
comma
r_int
id|count
comma
r_int
id|add_nl
comma
r_char
op_star
id|dest
)paren
(brace
r_return
id|xdl_recs_copy_0
c_func
(paren
l_int|1
comma
id|xe
comma
id|i
comma
id|count
comma
id|add_nl
comma
id|dest
)paren
suffix:semicolon
)brace
DECL|function|fill_conflict_hunk
r_static
r_int
id|fill_conflict_hunk
c_func
(paren
id|xdfenv_t
op_star
id|xe1
comma
r_const
r_char
op_star
id|name1
comma
id|xdfenv_t
op_star
id|xe2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|size
comma
r_int
id|i
comma
r_int
id|style
comma
id|xdmerge_t
op_star
id|m
comma
r_char
op_star
id|dest
)paren
(brace
r_const
r_int
id|marker_size
op_assign
l_int|7
suffix:semicolon
r_int
id|marker1_size
op_assign
(paren
id|name1
ques
c_cond
id|strlen
c_func
(paren
id|name1
)paren
op_plus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_int
id|marker2_size
op_assign
(paren
id|name2
ques
c_cond
id|strlen
c_func
(paren
id|name2
)paren
op_plus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
multiline_comment|/* Before conflicting part */
id|size
op_add_assign
id|xdl_recs_copy
c_func
(paren
id|xe1
comma
id|i
comma
id|m-&gt;i1
id|i
comma
l_int|0
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
(brace
id|size
op_add_assign
id|marker_size
op_plus
l_int|1
op_plus
id|marker1_size
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
id|marker_size
suffix:semicolon
id|j
op_increment
)paren
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&lt;&squot;
suffix:semicolon
r_if
c_cond
(paren
id|marker1_size
)paren
(brace
id|dest
(braket
id|size
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
op_plus
id|size
op_plus
l_int|1
comma
id|name1
comma
id|marker1_size
l_int|1
)paren
suffix:semicolon
id|size
op_add_assign
id|marker1_size
suffix:semicolon
)brace
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
multiline_comment|/* Postimage from side #1 */
id|size
op_add_assign
id|xdl_recs_copy
c_func
(paren
id|xe1
comma
id|m-&gt;i1
comma
id|m-&gt;chg1
comma
l_int|1
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|style
op_eq
id|XDL_MERGE_DIFF3
)paren
(brace
multiline_comment|/* Shared preimage */
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
(brace
id|size
op_add_assign
id|marker_size
op_plus
l_int|1
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
id|marker_size
suffix:semicolon
id|j
op_increment
)paren
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;|&squot;
suffix:semicolon
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
id|size
op_add_assign
id|xdl_orig_copy
c_func
(paren
id|xe1
comma
id|m-&gt;i0
comma
id|m-&gt;chg0
comma
l_int|1
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
(brace
id|size
op_add_assign
id|marker_size
op_plus
l_int|1
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
id|marker_size
suffix:semicolon
id|j
op_increment
)paren
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;=&squot;
suffix:semicolon
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
multiline_comment|/* Postimage from side #2 */
id|size
op_add_assign
id|xdl_recs_copy
c_func
(paren
id|xe2
comma
id|m-&gt;i2
comma
id|m-&gt;chg2
comma
l_int|1
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
(brace
id|size
op_add_assign
id|marker_size
op_plus
l_int|1
op_plus
id|marker2_size
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
id|marker_size
suffix:semicolon
id|j
op_increment
)paren
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&gt;&squot;
suffix:semicolon
r_if
c_cond
(paren
id|marker2_size
)paren
(brace
id|dest
(braket
id|size
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
op_plus
id|size
op_plus
l_int|1
comma
id|name2
comma
id|marker2_size
l_int|1
)paren
suffix:semicolon
id|size
op_add_assign
id|marker2_size
suffix:semicolon
)brace
id|dest
(braket
id|size
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
DECL|function|xdl_fill_merge_buffer
r_static
r_int
id|xdl_fill_merge_buffer
c_func
(paren
id|xdfenv_t
op_star
id|xe1
comma
r_const
r_char
op_star
id|name1
comma
id|xdfenv_t
op_star
id|xe2
comma
r_const
r_char
op_star
id|name2
comma
id|xdmerge_t
op_star
id|m
comma
r_char
op_star
id|dest
comma
r_int
id|style
)paren
(brace
r_int
id|size
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|size
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;mode
op_eq
l_int|0
)paren
id|size
op_assign
id|fill_conflict_hunk
c_func
(paren
id|xe1
comma
id|name1
comma
id|xe2
comma
id|name2
comma
id|size
comma
id|i
comma
id|style
comma
id|m
comma
id|dest
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m-&gt;mode
op_eq
l_int|1
)paren
id|size
op_add_assign
id|xdl_recs_copy
c_func
(paren
id|xe1
comma
id|i
comma
id|m-&gt;i1
op_plus
id|m-&gt;chg1
id|i
comma
l_int|0
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m-&gt;mode
op_eq
l_int|2
)paren
id|size
op_add_assign
id|xdl_recs_copy
c_func
(paren
id|xe2
comma
id|m-&gt;i2
id|m-&gt;i1
op_plus
id|i
comma
id|m-&gt;i1
op_plus
id|m-&gt;chg2
id|i
comma
l_int|0
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_else
r_continue
suffix:semicolon
id|i
op_assign
id|m-&gt;i1
op_plus
id|m-&gt;chg1
suffix:semicolon
)brace
id|size
op_add_assign
id|xdl_recs_copy
c_func
(paren
id|xe1
comma
id|i
comma
id|xe1-&gt;xdf2.nrec
id|i
comma
l_int|0
comma
id|dest
ques
c_cond
id|dest
op_plus
id|size
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/*&n; * Sometimes, changes are not quite identical, but differ in only a few&n; * lines. Try hard to show only these few lines as conflicting.&n; */
DECL|function|xdl_refine_conflicts
r_static
r_int
id|xdl_refine_conflicts
c_func
(paren
id|xdfenv_t
op_star
id|xe1
comma
id|xdfenv_t
op_star
id|xe2
comma
id|xdmerge_t
op_star
id|m
comma
id|xpparam_t
r_const
op_star
id|xpp
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
id|mmfile_t
id|t1
comma
id|t2
suffix:semicolon
id|xdfenv_t
id|xe
suffix:semicolon
id|xdchange_t
op_star
id|xscr
comma
op_star
id|x
suffix:semicolon
r_int
id|i1
op_assign
id|m-&gt;i1
comma
id|i2
op_assign
id|m-&gt;i2
suffix:semicolon
multiline_comment|/* let&squot;s handle just the conflicts */
r_if
c_cond
(paren
id|m-&gt;mode
)paren
r_continue
suffix:semicolon
multiline_comment|/* no sense refining a conflict when one side is empty */
r_if
c_cond
(paren
id|m-&gt;chg1
op_eq
l_int|0
op_logical_or
id|m-&gt;chg2
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This probably does not work outside git, since&n;&t;&t; * we have a very simple mmfile structure.&n;&t;&t; */
id|t1.ptr
op_assign
(paren
r_char
op_star
)paren
id|xe1-&gt;xdf2.recs
(braket
id|m-&gt;i1
)braket
op_member_access_from_pointer
id|ptr
suffix:semicolon
id|t1.size
op_assign
id|xe1-&gt;xdf2.recs
(braket
id|m-&gt;i1
op_plus
id|m-&gt;chg1
l_int|1
)braket
op_member_access_from_pointer
id|ptr
op_plus
id|xe1-&gt;xdf2.recs
(braket
id|m-&gt;i1
op_plus
id|m-&gt;chg1
l_int|1
)braket
op_member_access_from_pointer
id|size
id|t1.ptr
suffix:semicolon
id|t2.ptr
op_assign
(paren
r_char
op_star
)paren
id|xe2-&gt;xdf2.recs
(braket
id|m-&gt;i2
)braket
op_member_access_from_pointer
id|ptr
suffix:semicolon
id|t2.size
op_assign
id|xe2-&gt;xdf2.recs
(braket
id|m-&gt;i2
op_plus
id|m-&gt;chg2
l_int|1
)braket
op_member_access_from_pointer
id|ptr
op_plus
id|xe2-&gt;xdf2.recs
(braket
id|m-&gt;i2
op_plus
id|m-&gt;chg2
l_int|1
)braket
op_member_access_from_pointer
id|size
id|t2.ptr
suffix:semicolon
r_if
c_cond
(paren
id|xdl_do_diff
c_func
(paren
op_amp
id|t1
comma
op_amp
id|t2
comma
id|xpp
comma
op_amp
id|xe
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|xdl_change_compact
c_func
(paren
op_amp
id|xe.xdf1
comma
op_amp
id|xe.xdf2
comma
id|xpp-&gt;flags
)paren
OL
l_int|0
op_logical_or
id|xdl_change_compact
c_func
(paren
op_amp
id|xe.xdf2
comma
op_amp
id|xe.xdf1
comma
id|xpp-&gt;flags
)paren
OL
l_int|0
op_logical_or
id|xdl_build_script
c_func
(paren
op_amp
id|xe
comma
op_amp
id|xscr
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|xscr
)paren
(brace
multiline_comment|/* If this happens, the changes are identical. */
id|xdl_free_env
c_func
(paren
op_amp
id|xe
)paren
suffix:semicolon
id|m-&gt;mode
op_assign
l_int|4
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|x
op_assign
id|xscr
suffix:semicolon
id|m-&gt;i1
op_assign
id|xscr-&gt;i1
op_plus
id|i1
suffix:semicolon
id|m-&gt;chg1
op_assign
id|xscr-&gt;chg1
suffix:semicolon
id|m-&gt;i2
op_assign
id|xscr-&gt;i2
op_plus
id|i2
suffix:semicolon
id|m-&gt;chg2
op_assign
id|xscr-&gt;chg2
suffix:semicolon
r_while
c_loop
(paren
id|xscr-&gt;next
)paren
(brace
id|xdmerge_t
op_star
id|m2
op_assign
id|xdl_malloc
c_func
(paren
r_sizeof
(paren
id|xdmerge_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m2
)paren
(brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe
)paren
suffix:semicolon
id|xdl_free_script
c_func
(paren
id|x
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xscr
op_assign
id|xscr-&gt;next
suffix:semicolon
id|m2-&gt;next
op_assign
id|m-&gt;next
suffix:semicolon
id|m-&gt;next
op_assign
id|m2
suffix:semicolon
id|m
op_assign
id|m2
suffix:semicolon
id|m-&gt;mode
op_assign
l_int|0
suffix:semicolon
id|m-&gt;i1
op_assign
id|xscr-&gt;i1
op_plus
id|i1
suffix:semicolon
id|m-&gt;chg1
op_assign
id|xscr-&gt;chg1
suffix:semicolon
id|m-&gt;i2
op_assign
id|xscr-&gt;i2
op_plus
id|i2
suffix:semicolon
id|m-&gt;chg2
op_assign
id|xscr-&gt;chg2
suffix:semicolon
)brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe
)paren
suffix:semicolon
id|xdl_free_script
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|line_contains_alnum
r_static
r_int
id|line_contains_alnum
c_func
(paren
r_const
r_char
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
)paren
r_if
c_cond
(paren
id|isalnum
c_func
(paren
op_star
(paren
id|ptr
op_increment
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lines_contain_alnum
r_static
r_int
id|lines_contain_alnum
c_func
(paren
id|xdfenv_t
op_star
id|xe
comma
r_int
id|i
comma
r_int
id|chg
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|chg
suffix:semicolon
id|chg
op_decrement
comma
id|i
op_increment
)paren
r_if
c_cond
(paren
id|line_contains_alnum
c_func
(paren
id|xe-&gt;xdf2.recs
(braket
id|i
)braket
op_member_access_from_pointer
id|ptr
comma
id|xe-&gt;xdf2.recs
(braket
id|i
)braket
op_member_access_from_pointer
id|size
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This function merges m and m-&gt;next, marking everything between those hunks&n; * as conflicting, too.&n; */
DECL|function|xdl_merge_two_conflicts
r_static
r_void
id|xdl_merge_two_conflicts
c_func
(paren
id|xdmerge_t
op_star
id|m
)paren
(brace
id|xdmerge_t
op_star
id|next_m
op_assign
id|m-&gt;next
suffix:semicolon
id|m-&gt;chg1
op_assign
id|next_m-&gt;i1
op_plus
id|next_m-&gt;chg1
id|m-&gt;i1
suffix:semicolon
id|m-&gt;chg2
op_assign
id|next_m-&gt;i2
op_plus
id|next_m-&gt;chg2
id|m-&gt;i2
suffix:semicolon
id|m-&gt;next
op_assign
id|next_m-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|next_m
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If there are less than 3 non-conflicting lines between conflicts,&n; * it appears simpler -- because it takes up less (or as many) lines --&n; * if the lines are moved into the conflicts.&n; */
DECL|function|xdl_simplify_non_conflicts
r_static
r_int
id|xdl_simplify_non_conflicts
c_func
(paren
id|xdfenv_t
op_star
id|xe1
comma
id|xdmerge_t
op_star
id|m
comma
r_int
id|simplify_if_no_alnum
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
r_return
id|result
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|xdmerge_t
op_star
id|next_m
op_assign
id|m-&gt;next
suffix:semicolon
r_int
id|begin
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_m
)paren
r_return
id|result
suffix:semicolon
id|begin
op_assign
id|m-&gt;i1
op_plus
id|m-&gt;chg1
suffix:semicolon
id|end
op_assign
id|next_m-&gt;i1
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mode
op_ne
l_int|0
op_logical_or
id|next_m-&gt;mode
op_ne
l_int|0
op_logical_or
(paren
id|end
id|begin
OG
l_int|3
op_logical_and
(paren
op_logical_neg
id|simplify_if_no_alnum
op_logical_or
id|lines_contain_alnum
c_func
(paren
id|xe1
comma
id|begin
comma
id|end
id|begin
)paren
)paren
)paren
)paren
(brace
id|m
op_assign
id|next_m
suffix:semicolon
)brace
r_else
(brace
id|result
op_increment
suffix:semicolon
id|xdl_merge_two_conflicts
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * level == 0: mark all overlapping changes as conflict&n; * level == 1: mark overlapping changes as conflict only if not identical&n; * level == 2: analyze non-identical changes for minimal conflict set&n; * level == 3: analyze non-identical changes for minimal conflict set, but&n; *             treat hunks not containing any letter or number as conflicting&n; *&n; * returns &lt; 0 on error, == 0 for no conflicts, else number of conflicts&n; */
DECL|function|xdl_do_merge
r_static
r_int
id|xdl_do_merge
c_func
(paren
id|xdfenv_t
op_star
id|xe1
comma
id|xdchange_t
op_star
id|xscr1
comma
r_const
r_char
op_star
id|name1
comma
id|xdfenv_t
op_star
id|xe2
comma
id|xdchange_t
op_star
id|xscr2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|flags
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|mmbuffer_t
op_star
id|result
)paren
(brace
id|xdmerge_t
op_star
id|changes
comma
op_star
id|c
suffix:semicolon
r_int
id|i0
comma
id|i1
comma
id|i2
comma
id|chg0
comma
id|chg1
comma
id|chg2
suffix:semicolon
r_int
id|level
op_assign
id|flags
op_amp
id|XDL_MERGE_LEVEL_MASK
suffix:semicolon
r_int
id|style
op_assign
id|flags
op_amp
id|XDL_MERGE_STYLE_MASK
suffix:semicolon
id|c
op_assign
id|changes
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|xscr1
op_logical_and
id|xscr2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|changes
)paren
id|changes
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|xscr1-&gt;i1
op_plus
id|xscr1-&gt;chg1
OL
id|xscr2-&gt;i1
)paren
(brace
id|i0
op_assign
id|xscr1-&gt;i1
suffix:semicolon
id|i1
op_assign
id|xscr1-&gt;i2
suffix:semicolon
id|i2
op_assign
id|xscr2-&gt;i2
id|xscr2-&gt;i1
op_plus
id|xscr1-&gt;i1
suffix:semicolon
id|chg0
op_assign
id|xscr1-&gt;chg1
suffix:semicolon
id|chg1
op_assign
id|xscr1-&gt;chg2
suffix:semicolon
id|chg2
op_assign
id|xscr1-&gt;chg1
suffix:semicolon
r_if
c_cond
(paren
id|xdl_append_merge
c_func
(paren
op_amp
id|c
comma
l_int|1
comma
id|i0
comma
id|chg0
comma
id|i1
comma
id|chg1
comma
id|i2
comma
id|chg2
)paren
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xscr1
op_assign
id|xscr1-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xscr2-&gt;i1
op_plus
id|xscr2-&gt;chg1
OL
id|xscr1-&gt;i1
)paren
(brace
id|i0
op_assign
id|xscr2-&gt;i1
suffix:semicolon
id|i1
op_assign
id|xscr1-&gt;i2
id|xscr1-&gt;i1
op_plus
id|xscr2-&gt;i1
suffix:semicolon
id|i2
op_assign
id|xscr2-&gt;i2
suffix:semicolon
id|chg0
op_assign
id|xscr2-&gt;chg1
suffix:semicolon
id|chg1
op_assign
id|xscr2-&gt;chg1
suffix:semicolon
id|chg2
op_assign
id|xscr2-&gt;chg2
suffix:semicolon
r_if
c_cond
(paren
id|xdl_append_merge
c_func
(paren
op_amp
id|c
comma
l_int|2
comma
id|i0
comma
id|chg0
comma
id|i1
comma
id|chg1
comma
id|i2
comma
id|chg2
)paren
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xscr2
op_assign
id|xscr2-&gt;next
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|level
OL
l_int|1
op_logical_or
id|xscr1-&gt;i1
op_ne
id|xscr2-&gt;i1
op_logical_or
id|xscr1-&gt;chg1
op_ne
id|xscr2-&gt;chg1
op_logical_or
id|xscr1-&gt;chg2
op_ne
id|xscr2-&gt;chg2
op_logical_or
id|xdl_merge_cmp_lines
c_func
(paren
id|xe1
comma
id|xscr1-&gt;i2
comma
id|xe2
comma
id|xscr2-&gt;i2
comma
id|xscr1-&gt;chg2
comma
id|xpp-&gt;flags
)paren
)paren
(brace
multiline_comment|/* conflict */
r_int
id|off
op_assign
id|xscr1-&gt;i1
id|xscr2-&gt;i1
suffix:semicolon
r_int
id|ffo
op_assign
id|off
op_plus
id|xscr1-&gt;chg1
id|xscr2-&gt;chg1
suffix:semicolon
id|i0
op_assign
id|xscr1-&gt;i1
suffix:semicolon
id|i1
op_assign
id|xscr1-&gt;i2
suffix:semicolon
id|i2
op_assign
id|xscr2-&gt;i2
suffix:semicolon
r_if
c_cond
(paren
id|off
OG
l_int|0
)paren
(brace
id|i0
op_sub_assign
id|off
suffix:semicolon
id|i1
op_sub_assign
id|off
suffix:semicolon
)brace
r_else
id|i2
op_add_assign
id|off
suffix:semicolon
id|chg0
op_assign
id|xscr1-&gt;i1
op_plus
id|xscr1-&gt;chg1
id|i0
suffix:semicolon
id|chg1
op_assign
id|xscr1-&gt;i2
op_plus
id|xscr1-&gt;chg2
id|i1
suffix:semicolon
id|chg2
op_assign
id|xscr2-&gt;i2
op_plus
id|xscr2-&gt;chg2
id|i2
suffix:semicolon
r_if
c_cond
(paren
id|ffo
OG
l_int|0
)paren
id|chg2
op_add_assign
id|ffo
suffix:semicolon
r_else
(brace
id|chg0
op_sub_assign
id|ffo
suffix:semicolon
id|chg1
op_sub_assign
id|ffo
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xdl_append_merge
c_func
(paren
op_amp
id|c
comma
l_int|0
comma
id|i0
comma
id|chg0
comma
id|i1
comma
id|chg1
comma
id|i2
comma
id|chg2
)paren
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|i1
op_assign
id|xscr1-&gt;i1
op_plus
id|xscr1-&gt;chg1
suffix:semicolon
id|i2
op_assign
id|xscr2-&gt;i1
op_plus
id|xscr2-&gt;chg1
suffix:semicolon
r_if
c_cond
(paren
id|i1
op_ge
id|i2
)paren
id|xscr2
op_assign
id|xscr2-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|i2
op_ge
id|i1
)paren
id|xscr1
op_assign
id|xscr1-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|xscr1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|changes
)paren
id|changes
op_assign
id|c
suffix:semicolon
id|i0
op_assign
id|xscr1-&gt;i1
suffix:semicolon
id|i1
op_assign
id|xscr1-&gt;i2
suffix:semicolon
id|i2
op_assign
id|xscr1-&gt;i1
op_plus
id|xe2-&gt;xdf2.nrec
id|xe2-&gt;xdf1.nrec
suffix:semicolon
id|chg0
op_assign
id|xscr1-&gt;chg1
suffix:semicolon
id|chg1
op_assign
id|xscr1-&gt;chg2
suffix:semicolon
id|chg2
op_assign
id|xscr1-&gt;chg1
suffix:semicolon
r_if
c_cond
(paren
id|xdl_append_merge
c_func
(paren
op_amp
id|c
comma
l_int|1
comma
id|i0
comma
id|chg0
comma
id|i1
comma
id|chg1
comma
id|i2
comma
id|chg2
)paren
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xscr1
op_assign
id|xscr1-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|xscr2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|changes
)paren
id|changes
op_assign
id|c
suffix:semicolon
id|i0
op_assign
id|xscr2-&gt;i1
suffix:semicolon
id|i1
op_assign
id|xscr2-&gt;i1
op_plus
id|xe1-&gt;xdf2.nrec
id|xe1-&gt;xdf1.nrec
suffix:semicolon
id|i2
op_assign
id|xscr2-&gt;i2
suffix:semicolon
id|chg0
op_assign
id|xscr2-&gt;chg1
suffix:semicolon
id|chg1
op_assign
id|xscr2-&gt;chg1
suffix:semicolon
id|chg2
op_assign
id|xscr2-&gt;chg2
suffix:semicolon
r_if
c_cond
(paren
id|xdl_append_merge
c_func
(paren
op_amp
id|c
comma
l_int|2
comma
id|i0
comma
id|chg0
comma
id|i1
comma
id|chg1
comma
id|i2
comma
id|chg2
)paren
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xscr2
op_assign
id|xscr2-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|changes
)paren
id|changes
op_assign
id|c
suffix:semicolon
multiline_comment|/* refine conflicts */
r_if
c_cond
(paren
id|level
OG
l_int|1
op_logical_and
(paren
id|xdl_refine_conflicts
c_func
(paren
id|xe1
comma
id|xe2
comma
id|changes
comma
id|xpp
)paren
OL
l_int|0
op_logical_or
id|xdl_simplify_non_conflicts
c_func
(paren
id|xe1
comma
id|changes
comma
id|level
OG
l_int|2
)paren
OL
l_int|0
)paren
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* output */
r_if
c_cond
(paren
id|result
)paren
(brace
r_int
id|size
op_assign
id|xdl_fill_merge_buffer
c_func
(paren
id|xe1
comma
id|name1
comma
id|xe2
comma
id|name2
comma
id|changes
comma
l_int|NULL
comma
id|style
)paren
suffix:semicolon
id|result-&gt;ptr
op_assign
id|xdl_malloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result-&gt;ptr
)paren
(brace
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|result-&gt;size
op_assign
id|size
suffix:semicolon
id|xdl_fill_merge_buffer
c_func
(paren
id|xe1
comma
id|name1
comma
id|xe2
comma
id|name2
comma
id|changes
comma
id|result-&gt;ptr
comma
id|style
)paren
suffix:semicolon
)brace
r_return
id|xdl_cleanup_merge
c_func
(paren
id|changes
)paren
suffix:semicolon
)brace
DECL|function|xdl_merge
r_int
id|xdl_merge
c_func
(paren
id|mmfile_t
op_star
id|orig
comma
id|mmfile_t
op_star
id|mf1
comma
r_const
r_char
op_star
id|name1
comma
id|mmfile_t
op_star
id|mf2
comma
r_const
r_char
op_star
id|name2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
r_int
id|flags
comma
id|mmbuffer_t
op_star
id|result
)paren
(brace
id|xdchange_t
op_star
id|xscr1
comma
op_star
id|xscr2
suffix:semicolon
id|xdfenv_t
id|xe1
comma
id|xe2
suffix:semicolon
r_int
id|status
suffix:semicolon
id|result-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
id|result-&gt;size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|xdl_do_diff
c_func
(paren
id|orig
comma
id|mf1
comma
id|xpp
comma
op_amp
id|xe1
)paren
OL
l_int|0
op_logical_or
id|xdl_do_diff
c_func
(paren
id|orig
comma
id|mf2
comma
id|xpp
comma
op_amp
id|xe2
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xdl_change_compact
c_func
(paren
op_amp
id|xe1.xdf1
comma
op_amp
id|xe1.xdf2
comma
id|xpp-&gt;flags
)paren
OL
l_int|0
op_logical_or
id|xdl_change_compact
c_func
(paren
op_amp
id|xe1.xdf2
comma
op_amp
id|xe1.xdf1
comma
id|xpp-&gt;flags
)paren
OL
l_int|0
op_logical_or
id|xdl_build_script
c_func
(paren
op_amp
id|xe1
comma
op_amp
id|xscr1
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xdl_change_compact
c_func
(paren
op_amp
id|xe2.xdf1
comma
op_amp
id|xe2.xdf2
comma
id|xpp-&gt;flags
)paren
OL
l_int|0
op_logical_or
id|xdl_change_compact
c_func
(paren
op_amp
id|xe2.xdf2
comma
op_amp
id|xe2.xdf1
comma
id|xpp-&gt;flags
)paren
OL
l_int|0
op_logical_or
id|xdl_build_script
c_func
(paren
op_amp
id|xe2
comma
op_amp
id|xscr2
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe2
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|xscr1
op_logical_or
id|xscr2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|xscr1
)paren
(brace
id|result-&gt;ptr
op_assign
id|xdl_malloc
c_func
(paren
id|mf2-&gt;size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result-&gt;ptr
comma
id|mf2-&gt;ptr
comma
id|mf2-&gt;size
)paren
suffix:semicolon
id|result-&gt;size
op_assign
id|mf2-&gt;size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|xscr2
)paren
(brace
id|result-&gt;ptr
op_assign
id|xdl_malloc
c_func
(paren
id|mf1-&gt;size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result-&gt;ptr
comma
id|mf1-&gt;ptr
comma
id|mf1-&gt;size
)paren
suffix:semicolon
id|result-&gt;size
op_assign
id|mf1-&gt;size
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|xdl_do_merge
c_func
(paren
op_amp
id|xe1
comma
id|xscr1
comma
id|name1
comma
op_amp
id|xe2
comma
id|xscr2
comma
id|name2
comma
id|flags
comma
id|xpp
comma
id|result
)paren
suffix:semicolon
)brace
id|xdl_free_script
c_func
(paren
id|xscr1
)paren
suffix:semicolon
id|xdl_free_script
c_func
(paren
id|xscr2
)paren
suffix:semicolon
)brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe1
)paren
suffix:semicolon
id|xdl_free_env
c_func
(paren
op_amp
id|xe2
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
eof
