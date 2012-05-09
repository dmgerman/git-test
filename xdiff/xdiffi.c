multiline_comment|/*&n; *  LibXDiff by Davide Libenzi ( File Differential Library )&n; *  Copyright (C) 2003&t;Davide Libenzi&n; *&n; *  This library is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU Lesser General Public&n; *  License as published by the Free Software Foundation; either&n; *  version 2.1 of the License, or (at your option) any later version.&n; *&n; *  This library is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  Lesser General Public License for more details.&n; *&n; *  You should have received a copy of the GNU Lesser General Public&n; *  License along with this library; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#include &quot;xinclude.h&quot;
DECL|macro|XDL_MAX_COST_MIN
mdefine_line|#define XDL_MAX_COST_MIN 256
DECL|macro|XDL_HEUR_MIN_COST
mdefine_line|#define XDL_HEUR_MIN_COST 256
DECL|macro|XDL_LINE_MAX
mdefine_line|#define XDL_LINE_MAX (long)((1UL &lt;&lt; (CHAR_BIT * sizeof(long) - 1)) - 1)
DECL|macro|XDL_SNAKE_CNT
mdefine_line|#define XDL_SNAKE_CNT 20
DECL|macro|XDL_K_HEUR
mdefine_line|#define XDL_K_HEUR 4
DECL|struct|s_xdpsplit
r_typedef
r_struct
id|s_xdpsplit
(brace
DECL|member|i1
DECL|member|i2
r_int
id|i1
comma
id|i2
suffix:semicolon
DECL|member|min_lo
DECL|member|min_hi
r_int
id|min_lo
comma
id|min_hi
suffix:semicolon
DECL|typedef|xdpsplit_t
)brace
id|xdpsplit_t
suffix:semicolon
r_static
r_int
id|xdl_split
c_func
(paren
r_int
r_int
r_const
op_star
id|ha1
comma
r_int
id|off1
comma
r_int
id|lim1
comma
r_int
r_int
r_const
op_star
id|ha2
comma
r_int
id|off2
comma
r_int
id|lim2
comma
r_int
op_star
id|kvdf
comma
r_int
op_star
id|kvdb
comma
r_int
id|need_min
comma
id|xdpsplit_t
op_star
id|spl
comma
id|xdalgoenv_t
op_star
id|xenv
)paren
suffix:semicolon
r_static
id|xdchange_t
op_star
id|xdl_add_change
c_func
(paren
id|xdchange_t
op_star
id|xscr
comma
r_int
id|i1
comma
r_int
id|i2
comma
r_int
id|chg1
comma
r_int
id|chg2
)paren
suffix:semicolon
multiline_comment|/*&n; * See &quot;An O(ND) Difference Algorithm and its Variations&quot;, by Eugene Myers.&n; * Basically considers a &quot;box&quot; (off1, off2, lim1, lim2) and scan from both&n; * the forward diagonal starting from (off1, off2) and the backward diagonal&n; * starting from (lim1, lim2). If the K values on the same diagonal crosses&n; * returns the furthest point of reach. We might end up having to expensive&n; * cases using this algorithm is full, so a little bit of heuristic is needed&n; * to cut the search and to return a suboptimal point.&n; */
DECL|function|xdl_split
r_static
r_int
id|xdl_split
c_func
(paren
r_int
r_int
r_const
op_star
id|ha1
comma
r_int
id|off1
comma
r_int
id|lim1
comma
r_int
r_int
r_const
op_star
id|ha2
comma
r_int
id|off2
comma
r_int
id|lim2
comma
r_int
op_star
id|kvdf
comma
r_int
op_star
id|kvdb
comma
r_int
id|need_min
comma
id|xdpsplit_t
op_star
id|spl
comma
id|xdalgoenv_t
op_star
id|xenv
)paren
(brace
r_int
id|dmin
op_assign
id|off1
id|lim2
comma
id|dmax
op_assign
id|lim1
id|off2
suffix:semicolon
r_int
id|fmid
op_assign
id|off1
id|off2
comma
id|bmid
op_assign
id|lim1
id|lim2
suffix:semicolon
r_int
id|odd
op_assign
(paren
id|fmid
id|bmid
)paren
op_amp
l_int|1
suffix:semicolon
r_int
id|fmin
op_assign
id|fmid
comma
id|fmax
op_assign
id|fmid
suffix:semicolon
r_int
id|bmin
op_assign
id|bmid
comma
id|bmax
op_assign
id|bmid
suffix:semicolon
r_int
id|ec
comma
id|d
comma
id|i1
comma
id|i2
comma
id|prev1
comma
id|best
comma
id|dd
comma
id|v
comma
id|k
suffix:semicolon
multiline_comment|/*&n;&t; * Set initial diagonal values for both forward and backward path.&n;&t; */
id|kvdf
(braket
id|fmid
)braket
op_assign
id|off1
suffix:semicolon
id|kvdb
(braket
id|bmid
)braket
op_assign
id|lim1
suffix:semicolon
r_for
c_loop
(paren
id|ec
op_assign
l_int|1
suffix:semicolon
suffix:semicolon
id|ec
op_increment
)paren
(brace
r_int
id|got_snake
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We need to extent the diagonal &quot;domain&quot; by one. If the next&n;&t;&t; * values exits the box boundaries we need to change it in the&n;&t;&t; * opposite direction because (max - min) must be a power of two.&n;&t;&t; * Also we initialize the external K value to -1 so that we can&n;&t;&t; * avoid extra conditions check inside the core loop.&n;&t;&t; */
r_if
c_cond
(paren
id|fmin
OG
id|dmin
)paren
id|kvdf
(braket
op_decrement
id|fmin
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_else
op_increment
id|fmin
suffix:semicolon
r_if
c_cond
(paren
id|fmax
OL
id|dmax
)paren
id|kvdf
(braket
op_increment
id|fmax
op_plus
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
r_else
op_decrement
id|fmax
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
id|fmax
suffix:semicolon
id|d
op_ge
id|fmin
suffix:semicolon
id|d
op_sub_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|kvdf
(braket
id|d
l_int|1
)braket
op_ge
id|kvdf
(braket
id|d
op_plus
l_int|1
)braket
)paren
id|i1
op_assign
id|kvdf
(braket
id|d
l_int|1
)braket
op_plus
l_int|1
suffix:semicolon
r_else
id|i1
op_assign
id|kvdf
(braket
id|d
op_plus
l_int|1
)braket
suffix:semicolon
id|prev1
op_assign
id|i1
suffix:semicolon
id|i2
op_assign
id|i1
id|d
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i1
OL
id|lim1
op_logical_and
id|i2
OL
id|lim2
op_logical_and
id|ha1
(braket
id|i1
)braket
op_eq
id|ha2
(braket
id|i2
)braket
suffix:semicolon
id|i1
op_increment
comma
id|i2
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i1
id|prev1
OG
id|xenv-&gt;snake_cnt
)paren
id|got_snake
op_assign
l_int|1
suffix:semicolon
id|kvdf
(braket
id|d
)braket
op_assign
id|i1
suffix:semicolon
r_if
c_cond
(paren
id|odd
op_logical_and
id|bmin
op_le
id|d
op_logical_and
id|d
op_le
id|bmax
op_logical_and
id|kvdb
(braket
id|d
)braket
op_le
id|i1
)paren
(brace
id|spl-&gt;i1
op_assign
id|i1
suffix:semicolon
id|spl-&gt;i2
op_assign
id|i2
suffix:semicolon
id|spl-&gt;min_lo
op_assign
id|spl-&gt;min_hi
op_assign
l_int|1
suffix:semicolon
r_return
id|ec
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * We need to extent the diagonal &quot;domain&quot; by one. If the next&n;&t;&t; * values exits the box boundaries we need to change it in the&n;&t;&t; * opposite direction because (max - min) must be a power of two.&n;&t;&t; * Also we initialize the external K value to -1 so that we can&n;&t;&t; * avoid extra conditions check inside the core loop.&n;&t;&t; */
r_if
c_cond
(paren
id|bmin
OG
id|dmin
)paren
id|kvdb
(braket
op_decrement
id|bmin
l_int|1
)braket
op_assign
id|XDL_LINE_MAX
suffix:semicolon
r_else
op_increment
id|bmin
suffix:semicolon
r_if
c_cond
(paren
id|bmax
OL
id|dmax
)paren
id|kvdb
(braket
op_increment
id|bmax
op_plus
l_int|1
)braket
op_assign
id|XDL_LINE_MAX
suffix:semicolon
r_else
op_decrement
id|bmax
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
id|bmax
suffix:semicolon
id|d
op_ge
id|bmin
suffix:semicolon
id|d
op_sub_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|kvdb
(braket
id|d
l_int|1
)braket
OL
id|kvdb
(braket
id|d
op_plus
l_int|1
)braket
)paren
id|i1
op_assign
id|kvdb
(braket
id|d
l_int|1
)braket
suffix:semicolon
r_else
id|i1
op_assign
id|kvdb
(braket
id|d
op_plus
l_int|1
)braket
l_int|1
suffix:semicolon
id|prev1
op_assign
id|i1
suffix:semicolon
id|i2
op_assign
id|i1
id|d
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i1
OG
id|off1
op_logical_and
id|i2
OG
id|off2
op_logical_and
id|ha1
(braket
id|i1
l_int|1
)braket
op_eq
id|ha2
(braket
id|i2
l_int|1
)braket
suffix:semicolon
id|i1
op_decrement
comma
id|i2
op_decrement
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev1
id|i1
OG
id|xenv-&gt;snake_cnt
)paren
id|got_snake
op_assign
l_int|1
suffix:semicolon
id|kvdb
(braket
id|d
)braket
op_assign
id|i1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|odd
op_logical_and
id|fmin
op_le
id|d
op_logical_and
id|d
op_le
id|fmax
op_logical_and
id|i1
op_le
id|kvdf
(braket
id|d
)braket
)paren
(brace
id|spl-&gt;i1
op_assign
id|i1
suffix:semicolon
id|spl-&gt;i2
op_assign
id|i2
suffix:semicolon
id|spl-&gt;min_lo
op_assign
id|spl-&gt;min_hi
op_assign
l_int|1
suffix:semicolon
r_return
id|ec
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|need_min
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the edit cost is above the heuristic trigger and if&n;&t;&t; * we got a good snake, we sample current diagonals to see&n;&t;&t; * if some of the, have reached an &quot;interesting&quot; path. Our&n;&t;&t; * measure is a function of the distance from the diagonal&n;&t;&t; * corner (i1 + i2) penalized with the distance from the&n;&t;&t; * mid diagonal itself. If this value is above the current&n;&t;&t; * edit cost times a magic factor (XDL_K_HEUR) we consider&n;&t;&t; * it interesting.&n;&t;&t; */
r_if
c_cond
(paren
id|got_snake
op_logical_and
id|ec
OG
id|xenv-&gt;heur_min
)paren
(brace
r_for
c_loop
(paren
id|best
op_assign
l_int|0
comma
id|d
op_assign
id|fmax
suffix:semicolon
id|d
op_ge
id|fmin
suffix:semicolon
id|d
op_sub_assign
l_int|2
)paren
(brace
id|dd
op_assign
id|d
OG
id|fmid
ques
c_cond
id|d
id|fmid
suffix:colon
id|fmid
id|d
suffix:semicolon
id|i1
op_assign
id|kvdf
(braket
id|d
)braket
suffix:semicolon
id|i2
op_assign
id|i1
id|d
suffix:semicolon
id|v
op_assign
(paren
id|i1
id|off1
)paren
op_plus
(paren
id|i2
id|off2
)paren
id|dd
suffix:semicolon
r_if
c_cond
(paren
id|v
OG
id|XDL_K_HEUR
op_star
id|ec
op_logical_and
id|v
OG
id|best
op_logical_and
id|off1
op_plus
id|xenv-&gt;snake_cnt
op_le
id|i1
op_logical_and
id|i1
OL
id|lim1
op_logical_and
id|off2
op_plus
id|xenv-&gt;snake_cnt
op_le
id|i2
op_logical_and
id|i2
OL
id|lim2
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|1
suffix:semicolon
id|ha1
(braket
id|i1
id|k
)braket
op_eq
id|ha2
(braket
id|i2
id|k
)braket
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|k
op_eq
id|xenv-&gt;snake_cnt
)paren
(brace
id|best
op_assign
id|v
suffix:semicolon
id|spl-&gt;i1
op_assign
id|i1
suffix:semicolon
id|spl-&gt;i2
op_assign
id|i2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|best
OG
l_int|0
)paren
(brace
id|spl-&gt;min_lo
op_assign
l_int|1
suffix:semicolon
id|spl-&gt;min_hi
op_assign
l_int|0
suffix:semicolon
r_return
id|ec
suffix:semicolon
)brace
r_for
c_loop
(paren
id|best
op_assign
l_int|0
comma
id|d
op_assign
id|bmax
suffix:semicolon
id|d
op_ge
id|bmin
suffix:semicolon
id|d
op_sub_assign
l_int|2
)paren
(brace
id|dd
op_assign
id|d
OG
id|bmid
ques
c_cond
id|d
id|bmid
suffix:colon
id|bmid
id|d
suffix:semicolon
id|i1
op_assign
id|kvdb
(braket
id|d
)braket
suffix:semicolon
id|i2
op_assign
id|i1
id|d
suffix:semicolon
id|v
op_assign
(paren
id|lim1
id|i1
)paren
op_plus
(paren
id|lim2
id|i2
)paren
id|dd
suffix:semicolon
r_if
c_cond
(paren
id|v
OG
id|XDL_K_HEUR
op_star
id|ec
op_logical_and
id|v
OG
id|best
op_logical_and
id|off1
OL
id|i1
op_logical_and
id|i1
op_le
id|lim1
id|xenv-&gt;snake_cnt
op_logical_and
id|off2
OL
id|i2
op_logical_and
id|i2
op_le
id|lim2
id|xenv-&gt;snake_cnt
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|ha1
(braket
id|i1
op_plus
id|k
)braket
op_eq
id|ha2
(braket
id|i2
op_plus
id|k
)braket
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|k
op_eq
id|xenv-&gt;snake_cnt
l_int|1
)paren
(brace
id|best
op_assign
id|v
suffix:semicolon
id|spl-&gt;i1
op_assign
id|i1
suffix:semicolon
id|spl-&gt;i2
op_assign
id|i2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|best
OG
l_int|0
)paren
(brace
id|spl-&gt;min_lo
op_assign
l_int|0
suffix:semicolon
id|spl-&gt;min_hi
op_assign
l_int|1
suffix:semicolon
r_return
id|ec
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Enough is enough. We spent too much time here and now we collect&n;&t;&t; * the furthest reaching path using the (i1 + i2) measure.&n;&t;&t; */
r_if
c_cond
(paren
id|ec
op_ge
id|xenv-&gt;mxcost
)paren
(brace
r_int
id|fbest
comma
id|fbest1
comma
id|bbest
comma
id|bbest1
suffix:semicolon
id|fbest
op_assign
id|fbest1
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
id|fmax
suffix:semicolon
id|d
op_ge
id|fmin
suffix:semicolon
id|d
op_sub_assign
l_int|2
)paren
(brace
id|i1
op_assign
id|XDL_MIN
c_func
(paren
id|kvdf
(braket
id|d
)braket
comma
id|lim1
)paren
suffix:semicolon
id|i2
op_assign
id|i1
id|d
suffix:semicolon
r_if
c_cond
(paren
id|lim2
OL
id|i2
)paren
id|i1
op_assign
id|lim2
op_plus
id|d
comma
id|i2
op_assign
id|lim2
suffix:semicolon
r_if
c_cond
(paren
id|fbest
OL
id|i1
op_plus
id|i2
)paren
(brace
id|fbest
op_assign
id|i1
op_plus
id|i2
suffix:semicolon
id|fbest1
op_assign
id|i1
suffix:semicolon
)brace
)brace
id|bbest
op_assign
id|bbest1
op_assign
id|XDL_LINE_MAX
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
id|bmax
suffix:semicolon
id|d
op_ge
id|bmin
suffix:semicolon
id|d
op_sub_assign
l_int|2
)paren
(brace
id|i1
op_assign
id|XDL_MAX
c_func
(paren
id|off1
comma
id|kvdb
(braket
id|d
)braket
)paren
suffix:semicolon
id|i2
op_assign
id|i1
id|d
suffix:semicolon
r_if
c_cond
(paren
id|i2
OL
id|off2
)paren
id|i1
op_assign
id|off2
op_plus
id|d
comma
id|i2
op_assign
id|off2
suffix:semicolon
r_if
c_cond
(paren
id|i1
op_plus
id|i2
OL
id|bbest
)paren
(brace
id|bbest
op_assign
id|i1
op_plus
id|i2
suffix:semicolon
id|bbest1
op_assign
id|i1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|lim1
op_plus
id|lim2
)paren
id|bbest
OL
id|fbest
(paren
id|off1
op_plus
id|off2
)paren
)paren
(brace
id|spl-&gt;i1
op_assign
id|fbest1
suffix:semicolon
id|spl-&gt;i2
op_assign
id|fbest
id|fbest1
suffix:semicolon
id|spl-&gt;min_lo
op_assign
l_int|1
suffix:semicolon
id|spl-&gt;min_hi
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|spl-&gt;i1
op_assign
id|bbest1
suffix:semicolon
id|spl-&gt;i2
op_assign
id|bbest
id|bbest1
suffix:semicolon
id|spl-&gt;min_lo
op_assign
l_int|0
suffix:semicolon
id|spl-&gt;min_hi
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ec
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Rule: &quot;Divide et Impera&quot;. Recursively split the box in sub-boxes by calling&n; * the box splitting function. Note that the real job (marking changed lines)&n; * is done in the two boundary reaching checks.&n; */
DECL|function|xdl_recs_cmp
r_int
id|xdl_recs_cmp
c_func
(paren
id|diffdata_t
op_star
id|dd1
comma
r_int
id|off1
comma
r_int
id|lim1
comma
id|diffdata_t
op_star
id|dd2
comma
r_int
id|off2
comma
r_int
id|lim2
comma
r_int
op_star
id|kvdf
comma
r_int
op_star
id|kvdb
comma
r_int
id|need_min
comma
id|xdalgoenv_t
op_star
id|xenv
)paren
(brace
r_int
r_int
r_const
op_star
id|ha1
op_assign
id|dd1-&gt;ha
comma
op_star
id|ha2
op_assign
id|dd2-&gt;ha
suffix:semicolon
multiline_comment|/*&n;&t; * Shrink the box by walking through each diagonal snake (SW and NE).&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|off1
OL
id|lim1
op_logical_and
id|off2
OL
id|lim2
op_logical_and
id|ha1
(braket
id|off1
)braket
op_eq
id|ha2
(braket
id|off2
)braket
suffix:semicolon
id|off1
op_increment
comma
id|off2
op_increment
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|off1
OL
id|lim1
op_logical_and
id|off2
OL
id|lim2
op_logical_and
id|ha1
(braket
id|lim1
l_int|1
)braket
op_eq
id|ha2
(braket
id|lim2
l_int|1
)braket
suffix:semicolon
id|lim1
op_decrement
comma
id|lim2
op_decrement
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If one dimension is empty, then all records on the other one must&n;&t; * be obviously changed.&n;&t; */
r_if
c_cond
(paren
id|off1
op_eq
id|lim1
)paren
(brace
r_char
op_star
id|rchg2
op_assign
id|dd2-&gt;rchg
suffix:semicolon
r_int
op_star
id|rindex2
op_assign
id|dd2-&gt;rindex
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|off2
OL
id|lim2
suffix:semicolon
id|off2
op_increment
)paren
id|rchg2
(braket
id|rindex2
(braket
id|off2
)braket
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|off2
op_eq
id|lim2
)paren
(brace
r_char
op_star
id|rchg1
op_assign
id|dd1-&gt;rchg
suffix:semicolon
r_int
op_star
id|rindex1
op_assign
id|dd1-&gt;rindex
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|off1
OL
id|lim1
suffix:semicolon
id|off1
op_increment
)paren
id|rchg1
(braket
id|rindex1
(braket
id|off1
)braket
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|xdpsplit_t
id|spl
suffix:semicolon
id|spl.i1
op_assign
id|spl.i2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Divide ...&n;&t;&t; */
r_if
c_cond
(paren
id|xdl_split
c_func
(paren
id|ha1
comma
id|off1
comma
id|lim1
comma
id|ha2
comma
id|off2
comma
id|lim2
comma
id|kvdf
comma
id|kvdb
comma
id|need_min
comma
op_amp
id|spl
comma
id|xenv
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * ... et Impera.&n;&t;&t; */
r_if
c_cond
(paren
id|xdl_recs_cmp
c_func
(paren
id|dd1
comma
id|off1
comma
id|spl.i1
comma
id|dd2
comma
id|off2
comma
id|spl.i2
comma
id|kvdf
comma
id|kvdb
comma
id|spl.min_lo
comma
id|xenv
)paren
OL
l_int|0
op_logical_or
id|xdl_recs_cmp
c_func
(paren
id|dd1
comma
id|spl.i1
comma
id|lim1
comma
id|dd2
comma
id|spl.i2
comma
id|lim2
comma
id|kvdf
comma
id|kvdb
comma
id|spl.min_hi
comma
id|xenv
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_do_diff
r_int
id|xdl_do_diff
c_func
(paren
id|mmfile_t
op_star
id|mf1
comma
id|mmfile_t
op_star
id|mf2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|xe
)paren
(brace
r_int
id|ndiags
suffix:semicolon
r_int
op_star
id|kvd
comma
op_star
id|kvdf
comma
op_star
id|kvdb
suffix:semicolon
id|xdalgoenv_t
id|xenv
suffix:semicolon
id|diffdata_t
id|dd1
comma
id|dd2
suffix:semicolon
r_if
c_cond
(paren
id|XDF_DIFF_ALG
c_func
(paren
id|xpp-&gt;flags
)paren
op_eq
id|XDF_PATIENCE_DIFF
)paren
r_return
id|xdl_do_patience_diff
c_func
(paren
id|mf1
comma
id|mf2
comma
id|xpp
comma
id|xe
)paren
suffix:semicolon
r_if
c_cond
(paren
id|XDF_DIFF_ALG
c_func
(paren
id|xpp-&gt;flags
)paren
op_eq
id|XDF_HISTOGRAM_DIFF
)paren
r_return
id|xdl_do_histogram_diff
c_func
(paren
id|mf1
comma
id|mf2
comma
id|xpp
comma
id|xe
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xdl_prepare_env
c_func
(paren
id|mf1
comma
id|mf2
comma
id|xpp
comma
id|xe
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate and setup K vectors to be used by the differential algorithm.&n;&t; * One is to store the forward path and one to store the backward path.&n;&t; */
id|ndiags
op_assign
id|xe-&gt;xdf1.nreff
op_plus
id|xe-&gt;xdf2.nreff
op_plus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|kvd
op_assign
(paren
r_int
op_star
)paren
id|xdl_malloc
c_func
(paren
(paren
l_int|2
op_star
id|ndiags
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
(brace
id|xdl_free_env
c_func
(paren
id|xe
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|kvdf
op_assign
id|kvd
suffix:semicolon
id|kvdb
op_assign
id|kvdf
op_plus
id|ndiags
suffix:semicolon
id|kvdf
op_add_assign
id|xe-&gt;xdf2.nreff
op_plus
l_int|1
suffix:semicolon
id|kvdb
op_add_assign
id|xe-&gt;xdf2.nreff
op_plus
l_int|1
suffix:semicolon
id|xenv.mxcost
op_assign
id|xdl_bogosqrt
c_func
(paren
id|ndiags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xenv.mxcost
OL
id|XDL_MAX_COST_MIN
)paren
id|xenv.mxcost
op_assign
id|XDL_MAX_COST_MIN
suffix:semicolon
id|xenv.snake_cnt
op_assign
id|XDL_SNAKE_CNT
suffix:semicolon
id|xenv.heur_min
op_assign
id|XDL_HEUR_MIN_COST
suffix:semicolon
id|dd1.nrec
op_assign
id|xe-&gt;xdf1.nreff
suffix:semicolon
id|dd1.ha
op_assign
id|xe-&gt;xdf1.ha
suffix:semicolon
id|dd1.rchg
op_assign
id|xe-&gt;xdf1.rchg
suffix:semicolon
id|dd1.rindex
op_assign
id|xe-&gt;xdf1.rindex
suffix:semicolon
id|dd2.nrec
op_assign
id|xe-&gt;xdf2.nreff
suffix:semicolon
id|dd2.ha
op_assign
id|xe-&gt;xdf2.ha
suffix:semicolon
id|dd2.rchg
op_assign
id|xe-&gt;xdf2.rchg
suffix:semicolon
id|dd2.rindex
op_assign
id|xe-&gt;xdf2.rindex
suffix:semicolon
r_if
c_cond
(paren
id|xdl_recs_cmp
c_func
(paren
op_amp
id|dd1
comma
l_int|0
comma
id|dd1.nrec
comma
op_amp
id|dd2
comma
l_int|0
comma
id|dd2.nrec
comma
id|kvdf
comma
id|kvdb
comma
(paren
id|xpp-&gt;flags
op_amp
id|XDF_NEED_MINIMAL
)paren
op_ne
l_int|0
comma
op_amp
id|xenv
)paren
OL
l_int|0
)paren
(brace
id|xdl_free
c_func
(paren
id|kvd
)paren
suffix:semicolon
id|xdl_free_env
c_func
(paren
id|xe
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xdl_free
c_func
(paren
id|kvd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_add_change
r_static
id|xdchange_t
op_star
id|xdl_add_change
c_func
(paren
id|xdchange_t
op_star
id|xscr
comma
r_int
id|i1
comma
r_int
id|i2
comma
r_int
id|chg1
comma
r_int
id|chg2
)paren
(brace
id|xdchange_t
op_star
id|xch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xch
op_assign
(paren
id|xdchange_t
op_star
)paren
id|xdl_malloc
c_func
(paren
r_sizeof
(paren
id|xdchange_t
)paren
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|xch-&gt;next
op_assign
id|xscr
suffix:semicolon
id|xch-&gt;i1
op_assign
id|i1
suffix:semicolon
id|xch-&gt;i2
op_assign
id|i2
suffix:semicolon
id|xch-&gt;chg1
op_assign
id|chg1
suffix:semicolon
id|xch-&gt;chg2
op_assign
id|chg2
suffix:semicolon
r_return
id|xch
suffix:semicolon
)brace
DECL|function|xdl_change_compact
r_int
id|xdl_change_compact
c_func
(paren
id|xdfile_t
op_star
id|xdf
comma
id|xdfile_t
op_star
id|xdfo
comma
r_int
id|flags
)paren
(brace
r_int
id|ix
comma
id|ixo
comma
id|ixs
comma
id|ixref
comma
id|grpsiz
comma
id|nrec
op_assign
id|xdf-&gt;nrec
suffix:semicolon
r_char
op_star
id|rchg
op_assign
id|xdf-&gt;rchg
comma
op_star
id|rchgo
op_assign
id|xdfo-&gt;rchg
suffix:semicolon
id|xrecord_t
op_star
op_star
id|recs
op_assign
id|xdf-&gt;recs
suffix:semicolon
multiline_comment|/*&n;&t; * This is the same of what GNU diff does. Move back and forward&n;&t; * change groups for a consistent and pretty diff output. This also&n;&t; * helps in finding joinable change groups and reduce the diff size.&n;&t; */
r_for
c_loop
(paren
id|ix
op_assign
id|ixo
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/*&n;&t;&t; * Find the first changed line in the to-be-compacted file.&n;&t;&t; * We need to keep track of both indexes, so if we find a&n;&t;&t; * changed lines group on the other file, while scanning the&n;&t;&t; * to-be-compacted file, we need to skip it properly. Note&n;&t;&t; * that loops that are testing for changed lines on rchg* do&n;&t;&t; * not need index bounding since the array is prepared with&n;&t;&t; * a zero at position -1 and N.&n;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|ix
OL
id|nrec
op_logical_and
op_logical_neg
id|rchg
(braket
id|ix
)braket
suffix:semicolon
id|ix
op_increment
)paren
r_while
c_loop
(paren
id|rchgo
(braket
id|ixo
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ix
op_eq
id|nrec
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Record the start of a changed-group in the to-be-compacted file&n;&t;&t; * and find the end of it, on both to-be-compacted and other file&n;&t;&t; * indexes (ix and ixo).&n;&t;&t; */
id|ixs
op_assign
id|ix
suffix:semicolon
r_for
c_loop
(paren
id|ix
op_increment
suffix:semicolon
id|rchg
(braket
id|ix
)braket
suffix:semicolon
id|ix
op_increment
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|rchgo
(braket
id|ixo
)braket
suffix:semicolon
id|ixo
op_increment
)paren
suffix:semicolon
r_do
(brace
id|grpsiz
op_assign
id|ix
id|ixs
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If the line before the current change group, is equal to&n;&t;&t;&t; * the last line of the current change group, shift backward&n;&t;&t;&t; * the group.&n;&t;&t;&t; */
r_while
c_loop
(paren
id|ixs
OG
l_int|0
op_logical_and
id|recs
(braket
id|ixs
l_int|1
)braket
op_member_access_from_pointer
id|ha
op_eq
id|recs
(braket
id|ix
l_int|1
)braket
op_member_access_from_pointer
id|ha
op_logical_and
id|xdl_recmatch
c_func
(paren
id|recs
(braket
id|ixs
l_int|1
)braket
op_member_access_from_pointer
id|ptr
comma
id|recs
(braket
id|ixs
l_int|1
)braket
op_member_access_from_pointer
id|size
comma
id|recs
(braket
id|ix
l_int|1
)braket
op_member_access_from_pointer
id|ptr
comma
id|recs
(braket
id|ix
l_int|1
)braket
op_member_access_from_pointer
id|size
comma
id|flags
)paren
)paren
(brace
id|rchg
(braket
op_decrement
id|ixs
)braket
op_assign
l_int|1
suffix:semicolon
id|rchg
(braket
op_decrement
id|ix
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * This change might have joined two change groups,&n;&t;&t;&t;&t; * so we try to take this scenario in account by moving&n;&t;&t;&t;&t; * the start index accordingly (and so the other-file&n;&t;&t;&t;&t; * end-of-group index).&n;&t;&t;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|rchg
(braket
id|ixs
l_int|1
)braket
suffix:semicolon
id|ixs
op_decrement
)paren
suffix:semicolon
r_while
c_loop
(paren
id|rchgo
(braket
op_decrement
id|ixo
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Record the end-of-group position in case we are matched&n;&t;&t;&t; * with a group of changes in the other file (that is, the&n;&t;&t;&t; * change record before the end-of-group index in the other&n;&t;&t;&t; * file is set).&n;&t;&t;&t; */
id|ixref
op_assign
id|rchgo
(braket
id|ixo
l_int|1
)braket
ques
c_cond
id|ix
suffix:colon
id|nrec
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If the first line of the current change group, is equal to&n;&t;&t;&t; * the line next of the current change group, shift forward&n;&t;&t;&t; * the group.&n;&t;&t;&t; */
r_while
c_loop
(paren
id|ix
OL
id|nrec
op_logical_and
id|recs
(braket
id|ixs
)braket
op_member_access_from_pointer
id|ha
op_eq
id|recs
(braket
id|ix
)braket
op_member_access_from_pointer
id|ha
op_logical_and
id|xdl_recmatch
c_func
(paren
id|recs
(braket
id|ixs
)braket
op_member_access_from_pointer
id|ptr
comma
id|recs
(braket
id|ixs
)braket
op_member_access_from_pointer
id|size
comma
id|recs
(braket
id|ix
)braket
op_member_access_from_pointer
id|ptr
comma
id|recs
(braket
id|ix
)braket
op_member_access_from_pointer
id|size
comma
id|flags
)paren
)paren
(brace
id|rchg
(braket
id|ixs
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|rchg
(braket
id|ix
op_increment
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * This change might have joined two change groups,&n;&t;&t;&t;&t; * so we try to take this scenario in account by moving&n;&t;&t;&t;&t; * the start index accordingly (and so the other-file&n;&t;&t;&t;&t; * end-of-group index). Keep tracking the reference&n;&t;&t;&t;&t; * index in case we are shifting together with a&n;&t;&t;&t;&t; * corresponding group of changes in the other file.&n;&t;&t;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|rchg
(braket
id|ix
)braket
suffix:semicolon
id|ix
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|rchgo
(braket
op_increment
id|ixo
)braket
)paren
id|ixref
op_assign
id|ix
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|grpsiz
op_ne
id|ix
id|ixs
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Try to move back the possibly merged group of changes, to match&n;&t;&t; * the recorded postion in the other file.&n;&t;&t; */
r_while
c_loop
(paren
id|ixref
OL
id|ix
)paren
(brace
id|rchg
(braket
op_decrement
id|ixs
)braket
op_assign
l_int|1
suffix:semicolon
id|rchg
(braket
op_decrement
id|ix
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|rchgo
(braket
op_decrement
id|ixo
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_build_script
r_int
id|xdl_build_script
c_func
(paren
id|xdfenv_t
op_star
id|xe
comma
id|xdchange_t
op_star
op_star
id|xscr
)paren
(brace
id|xdchange_t
op_star
id|cscr
op_assign
l_int|NULL
comma
op_star
id|xch
suffix:semicolon
r_char
op_star
id|rchg1
op_assign
id|xe-&gt;xdf1.rchg
comma
op_star
id|rchg2
op_assign
id|xe-&gt;xdf2.rchg
suffix:semicolon
r_int
id|i1
comma
id|i2
comma
id|l1
comma
id|l2
suffix:semicolon
multiline_comment|/*&n;&t; * Trivial. Collects &quot;groups&quot; of changes and creates an edit script.&n;&t; */
r_for
c_loop
(paren
id|i1
op_assign
id|xe-&gt;xdf1.nrec
comma
id|i2
op_assign
id|xe-&gt;xdf2.nrec
suffix:semicolon
id|i1
op_ge
l_int|0
op_logical_or
id|i2
op_ge
l_int|0
suffix:semicolon
id|i1
op_decrement
comma
id|i2
op_decrement
)paren
r_if
c_cond
(paren
id|rchg1
(braket
id|i1
l_int|1
)braket
op_logical_or
id|rchg2
(braket
id|i2
l_int|1
)braket
)paren
(brace
r_for
c_loop
(paren
id|l1
op_assign
id|i1
suffix:semicolon
id|rchg1
(braket
id|i1
l_int|1
)braket
suffix:semicolon
id|i1
op_decrement
)paren
suffix:semicolon
r_for
c_loop
(paren
id|l2
op_assign
id|i2
suffix:semicolon
id|rchg2
(braket
id|i2
l_int|1
)braket
suffix:semicolon
id|i2
op_decrement
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xch
op_assign
id|xdl_add_change
c_func
(paren
id|cscr
comma
id|i1
comma
id|i2
comma
id|l1
id|i1
comma
id|l2
id|i2
)paren
)paren
)paren
(brace
id|xdl_free_script
c_func
(paren
id|cscr
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|cscr
op_assign
id|xch
suffix:semicolon
)brace
op_star
id|xscr
op_assign
id|cscr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_free_script
r_void
id|xdl_free_script
c_func
(paren
id|xdchange_t
op_star
id|xscr
)paren
(brace
id|xdchange_t
op_star
id|xch
suffix:semicolon
r_while
c_loop
(paren
(paren
id|xch
op_assign
id|xscr
)paren
op_ne
l_int|NULL
)paren
(brace
id|xscr
op_assign
id|xscr-&gt;next
suffix:semicolon
id|xdl_free
c_func
(paren
id|xch
)paren
suffix:semicolon
)brace
)brace
DECL|function|xdl_call_hunk_func
r_static
r_int
id|xdl_call_hunk_func
c_func
(paren
id|xdfenv_t
op_star
id|xe
comma
id|xdchange_t
op_star
id|xscr
comma
id|xdemitcb_t
op_star
id|ecb
comma
id|xdemitconf_t
r_const
op_star
id|xecfg
)paren
(brace
id|xdchange_t
op_star
id|xch
comma
op_star
id|xche
suffix:semicolon
r_for
c_loop
(paren
id|xch
op_assign
id|xscr
suffix:semicolon
id|xch
suffix:semicolon
id|xch
op_assign
id|xche-&gt;next
)paren
(brace
id|xche
op_assign
id|xdl_get_hunk
c_func
(paren
id|xch
comma
id|xecfg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xecfg
op_member_access_from_pointer
id|hunk_func
c_func
(paren
id|xch-&gt;i1
comma
id|xche-&gt;i1
op_plus
id|xche-&gt;chg1
id|xch-&gt;i1
comma
id|xch-&gt;i2
comma
id|xche-&gt;i2
op_plus
id|xche-&gt;chg2
id|xch-&gt;i2
comma
id|ecb-&gt;priv
)paren
OL
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
DECL|function|xdl_diff
r_int
id|xdl_diff
c_func
(paren
id|mmfile_t
op_star
id|mf1
comma
id|mmfile_t
op_star
id|mf2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdemitconf_t
r_const
op_star
id|xecfg
comma
id|xdemitcb_t
op_star
id|ecb
)paren
(brace
id|xdchange_t
op_star
id|xscr
suffix:semicolon
id|xdfenv_t
id|xe
suffix:semicolon
id|emit_func_t
id|ef
op_assign
id|xecfg-&gt;emit_func
ques
c_cond
(paren
id|emit_func_t
)paren
id|xecfg-&gt;emit_func
suffix:colon
id|xdl_emit_diff
suffix:semicolon
r_if
c_cond
(paren
id|xecfg-&gt;hunk_func
)paren
id|ef
op_assign
id|xdl_call_hunk_func
suffix:semicolon
r_if
c_cond
(paren
id|xdl_do_diff
c_func
(paren
id|mf1
comma
id|mf2
comma
id|xpp
comma
op_amp
id|xe
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
id|xscr
)paren
(brace
r_if
c_cond
(paren
id|ef
c_func
(paren
op_amp
id|xe
comma
id|xscr
comma
id|ecb
comma
id|xecfg
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_script
c_func
(paren
id|xscr
)paren
suffix:semicolon
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
id|xdl_free_script
c_func
(paren
id|xscr
)paren
suffix:semicolon
)brace
id|xdl_free_env
c_func
(paren
op_amp
id|xe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
