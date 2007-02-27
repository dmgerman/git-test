multiline_comment|/*&n; *  LibXDiff by Davide Libenzi ( File Differential Library )&n; *  Copyright (C) 2003&t;Davide Libenzi&n; *&n; *  This library is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU Lesser General Public&n; *  License as published by the Free Software Foundation; either&n; *  version 2.1 of the License, or (at your option) any later version.&n; *&n; *  This library is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  Lesser General Public License for more details.&n; *&n; *  You should have received a copy of the GNU Lesser General Public&n; *  License along with this library; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#include &quot;xinclude.h&quot;
DECL|macro|XDL_GUESS_NLINES
mdefine_line|#define XDL_GUESS_NLINES 256
DECL|function|xdl_bogosqrt
r_int
id|xdl_bogosqrt
c_func
(paren
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Classical integer square root approximation using shifts.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
id|n
op_rshift_assign
l_int|2
)paren
id|i
op_lshift_assign
l_int|1
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|xdl_emit_diffrec
r_int
id|xdl_emit_diffrec
c_func
(paren
r_char
r_const
op_star
id|rec
comma
r_int
id|size
comma
r_char
r_const
op_star
id|pre
comma
r_int
id|psize
comma
id|xdemitcb_t
op_star
id|ecb
)paren
(brace
r_int
id|i
op_assign
l_int|2
suffix:semicolon
id|mmbuffer_t
id|mb
(braket
l_int|3
)braket
suffix:semicolon
id|mb
(braket
l_int|0
)braket
dot
id|ptr
op_assign
(paren
r_char
op_star
)paren
id|pre
suffix:semicolon
id|mb
(braket
l_int|0
)braket
dot
id|size
op_assign
id|psize
suffix:semicolon
id|mb
(braket
l_int|1
)braket
dot
id|ptr
op_assign
(paren
r_char
op_star
)paren
id|rec
suffix:semicolon
id|mb
(braket
l_int|1
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
op_logical_and
id|rec
(braket
id|size
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|mb
(braket
l_int|2
)braket
dot
id|ptr
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;&bslash;n&bslash;&bslash; No newline at end of file&bslash;n&quot;
suffix:semicolon
id|mb
(braket
l_int|2
)braket
dot
id|size
op_assign
id|strlen
c_func
(paren
id|mb
(braket
l_int|2
)braket
dot
id|ptr
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ecb
op_member_access_from_pointer
id|outf
c_func
(paren
id|ecb-&gt;priv
comma
id|mb
comma
id|i
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_mmfile_first
r_void
op_star
id|xdl_mmfile_first
c_func
(paren
id|mmfile_t
op_star
id|mmf
comma
r_int
op_star
id|size
)paren
(brace
op_star
id|size
op_assign
id|mmf-&gt;size
suffix:semicolon
r_return
id|mmf-&gt;ptr
suffix:semicolon
)brace
DECL|function|xdl_mmfile_next
r_void
op_star
id|xdl_mmfile_next
c_func
(paren
id|mmfile_t
op_star
id|mmf
comma
r_int
op_star
id|size
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xdl_mmfile_size
r_int
id|xdl_mmfile_size
c_func
(paren
id|mmfile_t
op_star
id|mmf
)paren
(brace
r_return
id|mmf-&gt;size
suffix:semicolon
)brace
DECL|function|xdl_cha_init
r_int
id|xdl_cha_init
c_func
(paren
id|chastore_t
op_star
id|cha
comma
r_int
id|isize
comma
r_int
id|icount
)paren
(brace
id|cha-&gt;head
op_assign
id|cha-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
id|cha-&gt;isize
op_assign
id|isize
suffix:semicolon
id|cha-&gt;nsize
op_assign
id|icount
op_star
id|isize
suffix:semicolon
id|cha-&gt;ancur
op_assign
id|cha-&gt;sncur
op_assign
l_int|NULL
suffix:semicolon
id|cha-&gt;scurr
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_cha_free
r_void
id|xdl_cha_free
c_func
(paren
id|chastore_t
op_star
id|cha
)paren
(brace
id|chanode_t
op_star
id|cur
comma
op_star
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|cur
op_assign
id|cha-&gt;head
suffix:semicolon
(paren
id|tmp
op_assign
id|cur
)paren
op_ne
l_int|NULL
suffix:semicolon
)paren
(brace
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
id|xdl_free
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
)brace
DECL|function|xdl_cha_alloc
r_void
op_star
id|xdl_cha_alloc
c_func
(paren
id|chastore_t
op_star
id|cha
)paren
(brace
id|chanode_t
op_star
id|ancur
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ancur
op_assign
id|cha-&gt;ancur
)paren
op_logical_or
id|ancur-&gt;icurr
op_eq
id|cha-&gt;nsize
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ancur
op_assign
(paren
id|chanode_t
op_star
)paren
id|xdl_malloc
c_func
(paren
r_sizeof
(paren
id|chanode_t
)paren
op_plus
id|cha-&gt;nsize
)paren
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|ancur-&gt;icurr
op_assign
l_int|0
suffix:semicolon
id|ancur-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cha-&gt;tail
)paren
id|cha-&gt;tail-&gt;next
op_assign
id|ancur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cha-&gt;head
)paren
id|cha-&gt;head
op_assign
id|ancur
suffix:semicolon
id|cha-&gt;tail
op_assign
id|ancur
suffix:semicolon
id|cha-&gt;ancur
op_assign
id|ancur
suffix:semicolon
)brace
id|data
op_assign
(paren
r_char
op_star
)paren
id|ancur
op_plus
r_sizeof
(paren
id|chanode_t
)paren
op_plus
id|ancur-&gt;icurr
suffix:semicolon
id|ancur-&gt;icurr
op_add_assign
id|cha-&gt;isize
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|xdl_cha_first
r_void
op_star
id|xdl_cha_first
c_func
(paren
id|chastore_t
op_star
id|cha
)paren
(brace
id|chanode_t
op_star
id|sncur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cha-&gt;sncur
op_assign
id|sncur
op_assign
id|cha-&gt;head
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|cha-&gt;scurr
op_assign
l_int|0
suffix:semicolon
r_return
(paren
r_char
op_star
)paren
id|sncur
op_plus
r_sizeof
(paren
id|chanode_t
)paren
op_plus
id|cha-&gt;scurr
suffix:semicolon
)brace
DECL|function|xdl_cha_next
r_void
op_star
id|xdl_cha_next
c_func
(paren
id|chastore_t
op_star
id|cha
)paren
(brace
id|chanode_t
op_star
id|sncur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sncur
op_assign
id|cha-&gt;sncur
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|cha-&gt;scurr
op_add_assign
id|cha-&gt;isize
suffix:semicolon
r_if
c_cond
(paren
id|cha-&gt;scurr
op_eq
id|sncur-&gt;icurr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|sncur
op_assign
id|cha-&gt;sncur
op_assign
id|sncur-&gt;next
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|cha-&gt;scurr
op_assign
l_int|0
suffix:semicolon
)brace
r_return
(paren
r_char
op_star
)paren
id|sncur
op_plus
r_sizeof
(paren
id|chanode_t
)paren
op_plus
id|cha-&gt;scurr
suffix:semicolon
)brace
DECL|function|xdl_guess_lines
r_int
id|xdl_guess_lines
c_func
(paren
id|mmfile_t
op_star
id|mf
)paren
(brace
r_int
id|nl
op_assign
l_int|0
comma
id|size
comma
id|tsize
op_assign
l_int|0
suffix:semicolon
r_char
r_const
op_star
id|data
comma
op_star
id|cur
comma
op_star
id|top
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur
op_assign
id|data
op_assign
id|xdl_mmfile_first
c_func
(paren
id|mf
comma
op_amp
id|size
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|top
op_assign
id|data
op_plus
id|size
suffix:semicolon
id|nl
OL
id|XDL_GUESS_NLINES
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|cur
op_ge
id|top
)paren
(brace
id|tsize
op_add_assign
(paren
r_int
)paren
(paren
id|cur
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cur
op_assign
id|data
op_assign
id|xdl_mmfile_next
c_func
(paren
id|mf
comma
op_amp
id|size
)paren
)paren
)paren
r_break
suffix:semicolon
id|top
op_assign
id|data
op_plus
id|size
suffix:semicolon
)brace
id|nl
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cur
op_assign
id|memchr
c_func
(paren
id|cur
comma
l_char|&squot;&bslash;n&squot;
comma
id|top
id|cur
)paren
)paren
)paren
id|cur
op_assign
id|top
suffix:semicolon
r_else
id|cur
op_increment
suffix:semicolon
)brace
id|tsize
op_add_assign
(paren
r_int
)paren
(paren
id|cur
id|data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nl
op_logical_and
id|tsize
)paren
id|nl
op_assign
id|xdl_mmfile_size
c_func
(paren
id|mf
)paren
op_div
(paren
id|tsize
op_div
id|nl
)paren
suffix:semicolon
r_return
id|nl
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|xdl_recmatch
r_int
id|xdl_recmatch
c_func
(paren
r_const
r_char
op_star
id|l1
comma
r_int
id|s1
comma
r_const
r_char
op_star
id|l2
comma
r_int
id|s2
comma
r_int
id|flags
)paren
(brace
r_int
id|i1
comma
id|i2
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|XDF_IGNORE_WHITESPACE
)paren
(brace
r_for
c_loop
(paren
id|i1
op_assign
id|i2
op_assign
l_int|0
suffix:semicolon
id|i1
OL
id|s1
op_logical_and
id|i2
OL
id|s2
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|l1
(braket
id|i1
)braket
)paren
)paren
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|l1
(braket
id|i1
)braket
)paren
op_logical_and
id|i1
OL
id|s1
)paren
id|i1
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|l2
(braket
id|i2
)braket
)paren
)paren
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|l2
(braket
id|i2
)braket
)paren
op_logical_and
id|i2
OL
id|s2
)paren
id|i2
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i1
OL
id|s1
op_logical_and
id|i2
OL
id|s2
op_logical_and
id|l1
(braket
id|i1
op_increment
)braket
op_ne
id|l2
(braket
id|i2
op_increment
)braket
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|i1
op_ge
id|s1
op_logical_and
id|i2
op_ge
id|s2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|XDF_IGNORE_WHITESPACE_CHANGE
)paren
(brace
r_for
c_loop
(paren
id|i1
op_assign
id|i2
op_assign
l_int|0
suffix:semicolon
id|i1
OL
id|s1
op_logical_and
id|i2
OL
id|s2
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|l1
(braket
id|i1
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|l2
(braket
id|i2
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|l1
(braket
id|i1
)braket
)paren
op_logical_and
id|i1
OL
id|s1
)paren
id|i1
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|l2
(braket
id|i2
)braket
)paren
op_logical_and
id|i2
OL
id|s2
)paren
id|i2
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|l1
(braket
id|i1
op_increment
)braket
op_ne
id|l2
(braket
id|i2
op_increment
)braket
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
id|i1
op_ge
id|s1
op_logical_and
id|i2
op_ge
id|s2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|XDF_IGNORE_WHITESPACE_AT_EOL
)paren
(brace
r_for
c_loop
(paren
id|i1
op_assign
id|i2
op_assign
l_int|0
suffix:semicolon
id|i1
OL
id|s1
op_logical_and
id|i2
OL
id|s2
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|l1
(braket
id|i1
)braket
op_ne
id|l2
(braket
id|i2
)braket
)paren
(brace
r_while
c_loop
(paren
id|i1
OL
id|s1
op_logical_and
id|isspace
c_func
(paren
id|l1
(braket
id|i1
)braket
)paren
)paren
id|i1
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|i2
OL
id|s2
op_logical_and
id|isspace
c_func
(paren
id|l2
(braket
id|i2
)braket
)paren
)paren
id|i2
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i1
OL
id|s1
op_logical_or
id|i2
OL
id|s2
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|i1
op_increment
suffix:semicolon
id|i2
op_increment
suffix:semicolon
)brace
r_return
id|i1
op_ge
id|s1
op_logical_and
id|i2
op_ge
id|s2
suffix:semicolon
)brace
r_else
r_return
id|s1
op_eq
id|s2
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|l1
comma
id|l2
comma
id|s1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_hash_record
r_int
r_int
id|xdl_hash_record
c_func
(paren
r_char
r_const
op_star
op_star
id|data
comma
r_char
r_const
op_star
id|top
comma
r_int
id|flags
)paren
(brace
r_int
r_int
id|ha
op_assign
l_int|5381
suffix:semicolon
r_char
r_const
op_star
id|ptr
op_assign
op_star
id|data
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ptr
OL
id|top
op_logical_and
op_star
id|ptr
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|ptr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|isspace
c_func
(paren
op_star
id|ptr
)paren
op_logical_and
(paren
id|flags
op_amp
id|XDF_WHITESPACE_FLAGS
)paren
)paren
(brace
r_const
r_char
op_star
id|ptr2
op_assign
id|ptr
suffix:semicolon
r_while
c_loop
(paren
id|ptr
op_plus
l_int|1
OL
id|top
op_logical_and
id|isspace
c_func
(paren
id|ptr
(braket
l_int|1
)braket
)paren
op_logical_and
id|ptr
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|ptr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|XDF_IGNORE_WHITESPACE_CHANGE
op_logical_and
id|ptr
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|ha
op_add_assign
(paren
id|ha
op_lshift
l_int|5
)paren
suffix:semicolon
id|ha
op_xor_assign
(paren
r_int
r_int
)paren
l_char|&squot; &squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|XDF_IGNORE_WHITESPACE_AT_EOL
op_logical_and
id|ptr
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
id|ptr2
op_ne
id|ptr
op_plus
l_int|1
)paren
(brace
id|ha
op_add_assign
(paren
id|ha
op_lshift
l_int|5
)paren
suffix:semicolon
id|ha
op_xor_assign
(paren
r_int
r_int
)paren
op_star
id|ptr2
suffix:semicolon
id|ptr2
op_increment
suffix:semicolon
)brace
)brace
r_continue
suffix:semicolon
)brace
id|ha
op_add_assign
(paren
id|ha
op_lshift
l_int|5
)paren
suffix:semicolon
id|ha
op_xor_assign
(paren
r_int
r_int
)paren
op_star
id|ptr
suffix:semicolon
)brace
op_star
id|data
op_assign
id|ptr
OL
id|top
ques
c_cond
id|ptr
op_plus
l_int|1
suffix:colon
id|ptr
suffix:semicolon
r_return
id|ha
suffix:semicolon
)brace
DECL|function|xdl_hashbits
r_int
r_int
id|xdl_hashbits
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|val
op_assign
l_int|1
comma
id|bits
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|val
OL
id|size
op_logical_and
id|bits
OL
id|CHAR_BIT
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|val
op_lshift_assign
l_int|1
comma
id|bits
op_increment
)paren
suffix:semicolon
r_return
id|bits
ques
c_cond
id|bits
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|xdl_num_out
r_int
id|xdl_num_out
c_func
(paren
r_char
op_star
id|out
comma
r_int
id|val
)paren
(brace
r_char
op_star
id|ptr
comma
op_star
id|str
op_assign
id|out
suffix:semicolon
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
id|ptr
op_assign
id|buf
op_plus
r_sizeof
(paren
id|buf
)paren
l_int|1
suffix:semicolon
op_star
id|ptr
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
(brace
op_star
op_decrement
id|ptr
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|val
op_assign
id|val
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|val
op_logical_and
id|ptr
OG
id|buf
suffix:semicolon
id|val
op_div_assign
l_int|10
)paren
op_star
op_decrement
id|ptr
op_assign
l_string|&quot;0123456789&quot;
(braket
id|val
op_mod
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ptr
)paren
r_for
c_loop
(paren
suffix:semicolon
op_star
id|ptr
suffix:semicolon
id|ptr
op_increment
comma
id|str
op_increment
)paren
op_star
id|str
op_assign
op_star
id|ptr
suffix:semicolon
r_else
op_star
id|str
op_increment
op_assign
l_char|&squot;0&squot;
suffix:semicolon
op_star
id|str
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|str
id|out
suffix:semicolon
)brace
DECL|function|xdl_atol
r_int
id|xdl_atol
c_func
(paren
r_char
r_const
op_star
id|str
comma
r_char
r_const
op_star
op_star
id|next
)paren
(brace
r_int
id|val
comma
id|base
suffix:semicolon
r_char
r_const
op_star
id|top
suffix:semicolon
r_for
c_loop
(paren
id|top
op_assign
id|str
suffix:semicolon
id|XDL_ISDIGIT
c_func
(paren
op_star
id|top
)paren
suffix:semicolon
id|top
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
op_star
id|next
op_assign
id|top
suffix:semicolon
r_for
c_loop
(paren
id|val
op_assign
l_int|0
comma
id|base
op_assign
l_int|1
comma
id|top
op_decrement
suffix:semicolon
id|top
op_ge
id|str
suffix:semicolon
id|top
op_decrement
comma
id|base
op_mul_assign
l_int|10
)paren
id|val
op_add_assign
id|base
op_star
(paren
r_int
)paren
(paren
op_star
id|top
l_char|&squot;0&squot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|xdl_emit_hunk_hdr
r_int
id|xdl_emit_hunk_hdr
c_func
(paren
r_int
id|s1
comma
r_int
id|c1
comma
r_int
id|s2
comma
r_int
id|c2
comma
r_const
r_char
op_star
id|func
comma
r_int
id|funclen
comma
id|xdemitcb_t
op_star
id|ecb
)paren
(brace
r_int
id|nb
op_assign
l_int|0
suffix:semicolon
id|mmbuffer_t
id|mb
suffix:semicolon
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
l_string|&quot;@@ -&quot;
comma
l_int|4
)paren
suffix:semicolon
id|nb
op_add_assign
l_int|4
suffix:semicolon
id|nb
op_add_assign
id|xdl_num_out
c_func
(paren
id|buf
op_plus
id|nb
comma
id|c1
ques
c_cond
id|s1
suffix:colon
id|s1
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
l_int|1
)paren
(brace
id|memcpy
c_func
(paren
id|buf
op_plus
id|nb
comma
l_string|&quot;,&quot;
comma
l_int|1
)paren
suffix:semicolon
id|nb
op_add_assign
l_int|1
suffix:semicolon
id|nb
op_add_assign
id|xdl_num_out
c_func
(paren
id|buf
op_plus
id|nb
comma
id|c1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|buf
op_plus
id|nb
comma
l_string|&quot; +&quot;
comma
l_int|2
)paren
suffix:semicolon
id|nb
op_add_assign
l_int|2
suffix:semicolon
id|nb
op_add_assign
id|xdl_num_out
c_func
(paren
id|buf
op_plus
id|nb
comma
id|c2
ques
c_cond
id|s2
suffix:colon
id|s2
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c2
op_ne
l_int|1
)paren
(brace
id|memcpy
c_func
(paren
id|buf
op_plus
id|nb
comma
l_string|&quot;,&quot;
comma
l_int|1
)paren
suffix:semicolon
id|nb
op_add_assign
l_int|1
suffix:semicolon
id|nb
op_add_assign
id|xdl_num_out
c_func
(paren
id|buf
op_plus
id|nb
comma
id|c2
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|buf
op_plus
id|nb
comma
l_string|&quot; @@&quot;
comma
l_int|3
)paren
suffix:semicolon
id|nb
op_add_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|func
op_logical_and
id|funclen
)paren
(brace
id|buf
(braket
id|nb
op_increment
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
id|funclen
OG
r_sizeof
(paren
id|buf
)paren
id|nb
l_int|1
)paren
id|funclen
op_assign
r_sizeof
(paren
id|buf
)paren
id|nb
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|nb
comma
id|func
comma
id|funclen
)paren
suffix:semicolon
id|nb
op_add_assign
id|funclen
suffix:semicolon
)brace
id|buf
(braket
id|nb
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|mb.ptr
op_assign
id|buf
suffix:semicolon
id|mb.size
op_assign
id|nb
suffix:semicolon
r_if
c_cond
(paren
id|ecb
op_member_access_from_pointer
id|outf
c_func
(paren
id|ecb-&gt;priv
comma
op_amp
id|mb
comma
l_int|1
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
