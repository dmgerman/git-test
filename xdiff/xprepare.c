multiline_comment|/*&n; *  LibXDiff by Davide Libenzi ( File Differential Library )&n; *  Copyright (C) 2003  Davide Libenzi&n; *&n; *  This library is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU Lesser General Public&n; *  License as published by the Free Software Foundation; either&n; *  version 2.1 of the License, or (at your option) any later version.&n; *&n; *  This library is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  Lesser General Public License for more details.&n; *&n; *  You should have received a copy of the GNU Lesser General Public&n; *  License along with this library; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#include &quot;xinclude.h&quot;
DECL|macro|XDL_KPDIS_RUN
mdefine_line|#define XDL_KPDIS_RUN 4
DECL|macro|XDL_MAX_EQLIMIT
mdefine_line|#define XDL_MAX_EQLIMIT 1024
DECL|macro|XDL_SIMSCAN_WINDOW
mdefine_line|#define XDL_SIMSCAN_WINDOW 100
DECL|struct|s_xdlclass
r_typedef
r_struct
id|s_xdlclass
(brace
DECL|member|next
r_struct
id|s_xdlclass
op_star
id|next
suffix:semicolon
DECL|member|ha
r_int
r_int
id|ha
suffix:semicolon
DECL|member|line
r_char
r_const
op_star
id|line
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|len1
DECL|member|len2
r_int
id|len1
comma
id|len2
suffix:semicolon
DECL|typedef|xdlclass_t
)brace
id|xdlclass_t
suffix:semicolon
DECL|struct|s_xdlclassifier
r_typedef
r_struct
id|s_xdlclassifier
(brace
DECL|member|hbits
r_int
r_int
id|hbits
suffix:semicolon
DECL|member|hsize
r_int
id|hsize
suffix:semicolon
DECL|member|rchash
id|xdlclass_t
op_star
op_star
id|rchash
suffix:semicolon
DECL|member|ncha
id|chastore_t
id|ncha
suffix:semicolon
DECL|member|rcrecs
id|xdlclass_t
op_star
op_star
id|rcrecs
suffix:semicolon
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|typedef|xdlclassifier_t
)brace
id|xdlclassifier_t
suffix:semicolon
r_static
r_int
id|xdl_init_classifier
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
comma
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_static
r_void
id|xdl_free_classifier
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
)paren
suffix:semicolon
r_static
r_int
id|xdl_classify_record
c_func
(paren
r_int
r_int
id|pass
comma
id|xdlclassifier_t
op_star
id|cf
comma
id|xrecord_t
op_star
op_star
id|rhash
comma
r_int
r_int
id|hbits
comma
id|xrecord_t
op_star
id|rec
)paren
suffix:semicolon
r_static
r_int
id|xdl_prepare_ctx
c_func
(paren
r_int
r_int
id|pass
comma
id|mmfile_t
op_star
id|mf
comma
r_int
id|narec
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdlclassifier_t
op_star
id|cf
comma
id|xdfile_t
op_star
id|xdf
)paren
suffix:semicolon
r_static
r_void
id|xdl_free_ctx
c_func
(paren
id|xdfile_t
op_star
id|xdf
)paren
suffix:semicolon
r_static
r_int
id|xdl_clean_mmatch
c_func
(paren
r_char
r_const
op_star
id|dis
comma
r_int
id|i
comma
r_int
id|s
comma
r_int
id|e
)paren
suffix:semicolon
r_static
r_int
id|xdl_cleanup_records
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
comma
id|xdfile_t
op_star
id|xdf1
comma
id|xdfile_t
op_star
id|xdf2
)paren
suffix:semicolon
r_static
r_int
id|xdl_trim_ends
c_func
(paren
id|xdfile_t
op_star
id|xdf1
comma
id|xdfile_t
op_star
id|xdf2
)paren
suffix:semicolon
r_static
r_int
id|xdl_optimize_ctxs
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
comma
id|xdfile_t
op_star
id|xdf1
comma
id|xdfile_t
op_star
id|xdf2
)paren
suffix:semicolon
DECL|function|xdl_init_classifier
r_static
r_int
id|xdl_init_classifier
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_int
id|i
suffix:semicolon
id|cf-&gt;flags
op_assign
id|flags
suffix:semicolon
id|cf-&gt;hbits
op_assign
id|xdl_hashbits
c_func
(paren
(paren
r_int
r_int
)paren
id|size
)paren
suffix:semicolon
id|cf-&gt;hsize
op_assign
l_int|1
op_lshift
id|cf-&gt;hbits
suffix:semicolon
r_if
c_cond
(paren
id|xdl_cha_init
c_func
(paren
op_amp
id|cf-&gt;ncha
comma
r_sizeof
(paren
id|xdlclass_t
)paren
comma
id|size
op_div
l_int|4
op_plus
l_int|1
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
op_logical_neg
(paren
id|cf-&gt;rchash
op_assign
(paren
id|xdlclass_t
op_star
op_star
)paren
id|xdl_malloc
c_func
(paren
id|cf-&gt;hsize
op_star
r_sizeof
(paren
id|xdlclass_t
op_star
)paren
)paren
)paren
)paren
(brace
id|xdl_cha_free
c_func
(paren
op_amp
id|cf-&gt;ncha
)paren
suffix:semicolon
r_return
l_int|1
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
id|cf-&gt;hsize
suffix:semicolon
id|i
op_increment
)paren
id|cf-&gt;rchash
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|cf-&gt;alloc
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cf-&gt;rcrecs
op_assign
(paren
id|xdlclass_t
op_star
op_star
)paren
id|xdl_malloc
c_func
(paren
id|cf-&gt;alloc
op_star
r_sizeof
(paren
id|xdlclass_t
op_star
)paren
)paren
)paren
)paren
(brace
id|xdl_free
c_func
(paren
id|cf-&gt;rchash
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|cf-&gt;ncha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|cf-&gt;count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_free_classifier
r_static
r_void
id|xdl_free_classifier
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
)paren
(brace
id|xdl_free
c_func
(paren
id|cf-&gt;rcrecs
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|cf-&gt;rchash
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|cf-&gt;ncha
)paren
suffix:semicolon
)brace
DECL|function|xdl_classify_record
r_static
r_int
id|xdl_classify_record
c_func
(paren
r_int
r_int
id|pass
comma
id|xdlclassifier_t
op_star
id|cf
comma
id|xrecord_t
op_star
op_star
id|rhash
comma
r_int
r_int
id|hbits
comma
id|xrecord_t
op_star
id|rec
)paren
(brace
r_int
id|hi
suffix:semicolon
r_char
r_const
op_star
id|line
suffix:semicolon
id|xdlclass_t
op_star
id|rcrec
suffix:semicolon
id|xdlclass_t
op_star
op_star
id|rcrecs
suffix:semicolon
id|line
op_assign
id|rec-&gt;ptr
suffix:semicolon
id|hi
op_assign
(paren
r_int
)paren
id|XDL_HASHLONG
c_func
(paren
id|rec-&gt;ha
comma
id|cf-&gt;hbits
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rcrec
op_assign
id|cf-&gt;rchash
(braket
id|hi
)braket
suffix:semicolon
id|rcrec
suffix:semicolon
id|rcrec
op_assign
id|rcrec-&gt;next
)paren
r_if
c_cond
(paren
id|rcrec-&gt;ha
op_eq
id|rec-&gt;ha
op_logical_and
id|xdl_recmatch
c_func
(paren
id|rcrec-&gt;line
comma
id|rcrec-&gt;size
comma
id|rec-&gt;ptr
comma
id|rec-&gt;size
comma
id|cf-&gt;flags
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rcrec
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|rcrec
op_assign
id|xdl_cha_alloc
c_func
(paren
op_amp
id|cf-&gt;ncha
)paren
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|rcrec-&gt;idx
op_assign
id|cf-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cf-&gt;count
OG
id|cf-&gt;alloc
)paren
(brace
id|cf-&gt;alloc
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rcrecs
op_assign
(paren
id|xdlclass_t
op_star
op_star
)paren
id|xdl_realloc
c_func
(paren
id|cf-&gt;rcrecs
comma
id|cf-&gt;alloc
op_star
r_sizeof
(paren
id|xdlclass_t
op_star
)paren
)paren
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|cf-&gt;rcrecs
op_assign
id|rcrecs
suffix:semicolon
)brace
id|cf-&gt;rcrecs
(braket
id|rcrec-&gt;idx
)braket
op_assign
id|rcrec
suffix:semicolon
id|rcrec-&gt;line
op_assign
id|line
suffix:semicolon
id|rcrec-&gt;size
op_assign
id|rec-&gt;size
suffix:semicolon
id|rcrec-&gt;ha
op_assign
id|rec-&gt;ha
suffix:semicolon
id|rcrec-&gt;len1
op_assign
id|rcrec-&gt;len2
op_assign
l_int|0
suffix:semicolon
id|rcrec-&gt;next
op_assign
id|cf-&gt;rchash
(braket
id|hi
)braket
suffix:semicolon
id|cf-&gt;rchash
(braket
id|hi
)braket
op_assign
id|rcrec
suffix:semicolon
)brace
(paren
id|pass
op_eq
l_int|1
)paren
ques
c_cond
id|rcrec-&gt;len1
op_increment
suffix:colon
id|rcrec-&gt;len2
op_increment
suffix:semicolon
id|rec-&gt;ha
op_assign
(paren
r_int
r_int
)paren
id|rcrec-&gt;idx
suffix:semicolon
id|hi
op_assign
(paren
r_int
)paren
id|XDL_HASHLONG
c_func
(paren
id|rec-&gt;ha
comma
id|hbits
)paren
suffix:semicolon
id|rec-&gt;next
op_assign
id|rhash
(braket
id|hi
)braket
suffix:semicolon
id|rhash
(braket
id|hi
)braket
op_assign
id|rec
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_prepare_ctx
r_static
r_int
id|xdl_prepare_ctx
c_func
(paren
r_int
r_int
id|pass
comma
id|mmfile_t
op_star
id|mf
comma
r_int
id|narec
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdlclassifier_t
op_star
id|cf
comma
id|xdfile_t
op_star
id|xdf
)paren
(brace
r_int
r_int
id|hbits
suffix:semicolon
r_int
id|i
comma
id|nrec
comma
id|hsize
comma
id|bsize
suffix:semicolon
r_int
r_int
id|hav
suffix:semicolon
r_char
r_const
op_star
id|blk
comma
op_star
id|cur
comma
op_star
id|top
comma
op_star
id|prev
suffix:semicolon
id|xrecord_t
op_star
id|crec
suffix:semicolon
id|xrecord_t
op_star
op_star
id|recs
comma
op_star
op_star
id|rrecs
suffix:semicolon
id|xrecord_t
op_star
op_star
id|rhash
suffix:semicolon
r_int
r_int
op_star
id|ha
suffix:semicolon
r_char
op_star
id|rchg
suffix:semicolon
r_int
op_star
id|rindex
suffix:semicolon
r_if
c_cond
(paren
id|xdl_cha_init
c_func
(paren
op_amp
id|xdf-&gt;rcha
comma
r_sizeof
(paren
id|xrecord_t
)paren
comma
id|narec
op_div
l_int|4
op_plus
l_int|1
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
op_logical_neg
(paren
id|recs
op_assign
(paren
id|xrecord_t
op_star
op_star
)paren
id|xdl_malloc
c_func
(paren
id|narec
op_star
r_sizeof
(paren
id|xrecord_t
op_star
)paren
)paren
)paren
)paren
(brace
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|hbits
op_assign
id|xdl_hashbits
c_func
(paren
(paren
r_int
r_int
)paren
id|narec
)paren
suffix:semicolon
id|hsize
op_assign
l_int|1
op_lshift
id|hbits
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rhash
op_assign
(paren
id|xrecord_t
op_star
op_star
)paren
id|xdl_malloc
c_func
(paren
id|hsize
op_star
r_sizeof
(paren
id|xrecord_t
op_star
)paren
)paren
)paren
)paren
(brace
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
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
id|hsize
suffix:semicolon
id|i
op_increment
)paren
id|rhash
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|nrec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur
op_assign
id|blk
op_assign
id|xdl_mmfile_first
c_func
(paren
id|mf
comma
op_amp
id|bsize
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
id|blk
op_plus
id|bsize
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|cur
op_assign
id|blk
op_assign
id|xdl_mmfile_next
c_func
(paren
id|mf
comma
op_amp
id|bsize
)paren
)paren
)paren
r_break
suffix:semicolon
id|top
op_assign
id|blk
op_plus
id|bsize
suffix:semicolon
)brace
id|prev
op_assign
id|cur
suffix:semicolon
id|hav
op_assign
id|xdl_hash_record
c_func
(paren
op_amp
id|cur
comma
id|top
comma
id|xpp-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nrec
op_ge
id|narec
)paren
(brace
id|narec
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rrecs
op_assign
(paren
id|xrecord_t
op_star
op_star
)paren
id|xdl_realloc
c_func
(paren
id|recs
comma
id|narec
op_star
r_sizeof
(paren
id|xrecord_t
op_star
)paren
)paren
)paren
)paren
(brace
id|xdl_free
c_func
(paren
id|rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|recs
op_assign
id|rrecs
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|crec
op_assign
id|xdl_cha_alloc
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
)paren
)paren
(brace
id|xdl_free
c_func
(paren
id|rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|crec-&gt;ptr
op_assign
id|prev
suffix:semicolon
id|crec-&gt;size
op_assign
(paren
r_int
)paren
(paren
id|cur
id|prev
)paren
suffix:semicolon
id|crec-&gt;ha
op_assign
id|hav
suffix:semicolon
id|recs
(braket
id|nrec
op_increment
)braket
op_assign
id|crec
suffix:semicolon
r_if
c_cond
(paren
id|xdl_classify_record
c_func
(paren
id|pass
comma
id|cf
comma
id|rhash
comma
id|hbits
comma
id|crec
)paren
OL
l_int|0
)paren
(brace
id|xdl_free
c_func
(paren
id|rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|rchg
op_assign
(paren
r_char
op_star
)paren
id|xdl_malloc
c_func
(paren
(paren
id|nrec
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_char
)paren
)paren
)paren
)paren
(brace
id|xdl_free
c_func
(paren
id|rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|rchg
comma
l_int|0
comma
(paren
id|nrec
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_char
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rindex
op_assign
(paren
r_int
op_star
)paren
id|xdl_malloc
c_func
(paren
(paren
id|nrec
op_plus
l_int|1
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
id|xdl_free
c_func
(paren
id|rchg
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
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
(paren
id|ha
op_assign
(paren
r_int
r_int
op_star
)paren
id|xdl_malloc
c_func
(paren
(paren
id|nrec
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
)paren
(brace
id|xdl_free
c_func
(paren
id|rindex
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|rchg
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xdf-&gt;nrec
op_assign
id|nrec
suffix:semicolon
id|xdf-&gt;recs
op_assign
id|recs
suffix:semicolon
id|xdf-&gt;hbits
op_assign
id|hbits
suffix:semicolon
id|xdf-&gt;rhash
op_assign
id|rhash
suffix:semicolon
id|xdf-&gt;rchg
op_assign
id|rchg
op_plus
l_int|1
suffix:semicolon
id|xdf-&gt;rindex
op_assign
id|rindex
suffix:semicolon
id|xdf-&gt;nreff
op_assign
l_int|0
suffix:semicolon
id|xdf-&gt;ha
op_assign
id|ha
suffix:semicolon
id|xdf-&gt;dstart
op_assign
l_int|0
suffix:semicolon
id|xdf-&gt;dend
op_assign
id|nrec
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_free_ctx
r_static
r_void
id|xdl_free_ctx
c_func
(paren
id|xdfile_t
op_star
id|xdf
)paren
(brace
id|xdl_free
c_func
(paren
id|xdf-&gt;rhash
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|xdf-&gt;rindex
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|xdf-&gt;rchg
l_int|1
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|xdf-&gt;ha
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|xdf-&gt;recs
)paren
suffix:semicolon
id|xdl_cha_free
c_func
(paren
op_amp
id|xdf-&gt;rcha
)paren
suffix:semicolon
)brace
DECL|function|xdl_prepare_env
r_int
id|xdl_prepare_env
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
id|enl1
comma
id|enl2
suffix:semicolon
id|xdlclassifier_t
id|cf
suffix:semicolon
id|enl1
op_assign
id|xdl_guess_lines
c_func
(paren
id|mf1
)paren
op_plus
l_int|1
suffix:semicolon
id|enl2
op_assign
id|xdl_guess_lines
c_func
(paren
id|mf2
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|xdl_init_classifier
c_func
(paren
op_amp
id|cf
comma
id|enl1
op_plus
id|enl2
op_plus
l_int|1
comma
id|xpp-&gt;flags
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
id|xdl_prepare_ctx
c_func
(paren
l_int|1
comma
id|mf1
comma
id|enl1
comma
id|xpp
comma
op_amp
id|cf
comma
op_amp
id|xe-&gt;xdf1
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_classifier
c_func
(paren
op_amp
id|cf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xdl_prepare_ctx
c_func
(paren
l_int|2
comma
id|mf2
comma
id|enl2
comma
id|xpp
comma
op_amp
id|cf
comma
op_amp
id|xe-&gt;xdf2
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_ctx
c_func
(paren
op_amp
id|xe-&gt;xdf1
)paren
suffix:semicolon
id|xdl_free_classifier
c_func
(paren
op_amp
id|cf
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
(paren
id|xpp-&gt;flags
op_amp
id|XDF_PATIENCE_DIFF
)paren
op_logical_and
id|xdl_optimize_ctxs
c_func
(paren
op_amp
id|cf
comma
op_amp
id|xe-&gt;xdf1
comma
op_amp
id|xe-&gt;xdf2
)paren
OL
l_int|0
)paren
(brace
id|xdl_free_ctx
c_func
(paren
op_amp
id|xe-&gt;xdf2
)paren
suffix:semicolon
id|xdl_free_ctx
c_func
(paren
op_amp
id|xe-&gt;xdf1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|xdl_free_classifier
c_func
(paren
op_amp
id|cf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_free_env
r_void
id|xdl_free_env
c_func
(paren
id|xdfenv_t
op_star
id|xe
)paren
(brace
id|xdl_free_ctx
c_func
(paren
op_amp
id|xe-&gt;xdf2
)paren
suffix:semicolon
id|xdl_free_ctx
c_func
(paren
op_amp
id|xe-&gt;xdf1
)paren
suffix:semicolon
)brace
DECL|function|xdl_clean_mmatch
r_static
r_int
id|xdl_clean_mmatch
c_func
(paren
r_char
r_const
op_star
id|dis
comma
r_int
id|i
comma
r_int
id|s
comma
r_int
id|e
)paren
(brace
r_int
id|r
comma
id|rdis0
comma
id|rpdis0
comma
id|rdis1
comma
id|rpdis1
suffix:semicolon
multiline_comment|/*&n;&t; * Limits the window the is examined during the similar-lines&n;&t; * scan. The loops below stops when dis[i - r] == 1 (line that&n;&t; * has no match), but there are corner cases where the loop&n;&t; * proceed all the way to the extremities by causing huge&n;&t; * performance penalties in case of big files.&n;&t; */
r_if
c_cond
(paren
id|i
id|s
OG
id|XDL_SIMSCAN_WINDOW
)paren
id|s
op_assign
id|i
id|XDL_SIMSCAN_WINDOW
suffix:semicolon
r_if
c_cond
(paren
id|e
id|i
OG
id|XDL_SIMSCAN_WINDOW
)paren
id|e
op_assign
id|i
op_plus
id|XDL_SIMSCAN_WINDOW
suffix:semicolon
multiline_comment|/*&n;&t; * Scans the lines before &squot;i&squot; to find a run of lines that either&n;&t; * have no match (dis[j] == 0) or have multiple matches (dis[j] &gt; 1).&n;&t; * Note that we always call this function with dis[i] &gt; 1, so the&n;&t; * current line (i) is already a multimatch line.&n;&t; */
r_for
c_loop
(paren
id|r
op_assign
l_int|1
comma
id|rdis0
op_assign
l_int|0
comma
id|rpdis0
op_assign
l_int|1
suffix:semicolon
(paren
id|i
id|r
)paren
op_ge
id|s
suffix:semicolon
id|r
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dis
(braket
id|i
id|r
)braket
)paren
id|rdis0
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dis
(braket
id|i
id|r
)braket
op_eq
l_int|2
)paren
id|rpdis0
op_increment
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the run before the line &squot;i&squot; found only multimatch lines, we&n;&t; * return 0 and hence we don&squot;t make the current line (i) discarded.&n;&t; * We want to discard multimatch lines only when they appear in the&n;&t; * middle of runs with nomatch lines (dis[j] == 0).&n;&t; */
r_if
c_cond
(paren
id|rdis0
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|1
comma
id|rdis1
op_assign
l_int|0
comma
id|rpdis1
op_assign
l_int|1
suffix:semicolon
(paren
id|i
op_plus
id|r
)paren
op_le
id|e
suffix:semicolon
id|r
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dis
(braket
id|i
op_plus
id|r
)braket
)paren
id|rdis1
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dis
(braket
id|i
op_plus
id|r
)braket
op_eq
l_int|2
)paren
id|rpdis1
op_increment
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the run after the line &squot;i&squot; found only multimatch lines, we&n;&t; * return 0 and hence we don&squot;t make the current line (i) discarded.&n;&t; */
r_if
c_cond
(paren
id|rdis1
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|rdis1
op_add_assign
id|rdis0
suffix:semicolon
id|rpdis1
op_add_assign
id|rpdis0
suffix:semicolon
r_return
id|rpdis1
op_star
id|XDL_KPDIS_RUN
OL
(paren
id|rpdis1
op_plus
id|rdis1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to reduce the problem complexity, discard records that have no&n; * matches on the other file. Also, lines that have multiple matches&n; * might be potentially discarded if they happear in a run of discardable.&n; */
DECL|function|xdl_cleanup_records
r_static
r_int
id|xdl_cleanup_records
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
comma
id|xdfile_t
op_star
id|xdf1
comma
id|xdfile_t
op_star
id|xdf2
)paren
(brace
r_int
id|i
comma
id|nm
comma
id|nreff
comma
id|mlim
suffix:semicolon
id|xrecord_t
op_star
op_star
id|recs
suffix:semicolon
id|xdlclass_t
op_star
id|rcrec
suffix:semicolon
r_char
op_star
id|dis
comma
op_star
id|dis1
comma
op_star
id|dis2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dis
op_assign
(paren
r_char
op_star
)paren
id|xdl_malloc
c_func
(paren
id|xdf1-&gt;nrec
op_plus
id|xdf2-&gt;nrec
op_plus
l_int|2
)paren
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dis
comma
l_int|0
comma
id|xdf1-&gt;nrec
op_plus
id|xdf2-&gt;nrec
op_plus
l_int|2
)paren
suffix:semicolon
id|dis1
op_assign
id|dis
suffix:semicolon
id|dis2
op_assign
id|dis1
op_plus
id|xdf1-&gt;nrec
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mlim
op_assign
id|xdl_bogosqrt
c_func
(paren
id|xdf1-&gt;nrec
)paren
)paren
OG
id|XDL_MAX_EQLIMIT
)paren
id|mlim
op_assign
id|XDL_MAX_EQLIMIT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|xdf1-&gt;dstart
comma
id|recs
op_assign
op_amp
id|xdf1-&gt;recs
(braket
id|xdf1-&gt;dstart
)braket
suffix:semicolon
id|i
op_le
id|xdf1-&gt;dend
suffix:semicolon
id|i
op_increment
comma
id|recs
op_increment
)paren
(brace
id|rcrec
op_assign
id|cf-&gt;rcrecs
(braket
(paren
op_star
id|recs
)paren
op_member_access_from_pointer
id|ha
)braket
suffix:semicolon
id|nm
op_assign
id|rcrec
ques
c_cond
id|rcrec-&gt;len2
suffix:colon
l_int|0
suffix:semicolon
id|dis1
(braket
id|i
)braket
op_assign
(paren
id|nm
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|nm
op_ge
id|mlim
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|mlim
op_assign
id|xdl_bogosqrt
c_func
(paren
id|xdf2-&gt;nrec
)paren
)paren
OG
id|XDL_MAX_EQLIMIT
)paren
id|mlim
op_assign
id|XDL_MAX_EQLIMIT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|xdf2-&gt;dstart
comma
id|recs
op_assign
op_amp
id|xdf2-&gt;recs
(braket
id|xdf2-&gt;dstart
)braket
suffix:semicolon
id|i
op_le
id|xdf2-&gt;dend
suffix:semicolon
id|i
op_increment
comma
id|recs
op_increment
)paren
(brace
id|rcrec
op_assign
id|cf-&gt;rcrecs
(braket
(paren
op_star
id|recs
)paren
op_member_access_from_pointer
id|ha
)braket
suffix:semicolon
id|nm
op_assign
id|rcrec
ques
c_cond
id|rcrec-&gt;len1
suffix:colon
l_int|0
suffix:semicolon
id|dis2
(braket
id|i
)braket
op_assign
(paren
id|nm
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|nm
op_ge
id|mlim
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|nreff
op_assign
l_int|0
comma
id|i
op_assign
id|xdf1-&gt;dstart
comma
id|recs
op_assign
op_amp
id|xdf1-&gt;recs
(braket
id|xdf1-&gt;dstart
)braket
suffix:semicolon
id|i
op_le
id|xdf1-&gt;dend
suffix:semicolon
id|i
op_increment
comma
id|recs
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dis1
(braket
id|i
)braket
op_eq
l_int|1
op_logical_or
(paren
id|dis1
(braket
id|i
)braket
op_eq
l_int|2
op_logical_and
op_logical_neg
id|xdl_clean_mmatch
c_func
(paren
id|dis1
comma
id|i
comma
id|xdf1-&gt;dstart
comma
id|xdf1-&gt;dend
)paren
)paren
)paren
(brace
id|xdf1-&gt;rindex
(braket
id|nreff
)braket
op_assign
id|i
suffix:semicolon
id|xdf1-&gt;ha
(braket
id|nreff
)braket
op_assign
(paren
op_star
id|recs
)paren
op_member_access_from_pointer
id|ha
suffix:semicolon
id|nreff
op_increment
suffix:semicolon
)brace
r_else
id|xdf1-&gt;rchg
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|xdf1-&gt;nreff
op_assign
id|nreff
suffix:semicolon
r_for
c_loop
(paren
id|nreff
op_assign
l_int|0
comma
id|i
op_assign
id|xdf2-&gt;dstart
comma
id|recs
op_assign
op_amp
id|xdf2-&gt;recs
(braket
id|xdf2-&gt;dstart
)braket
suffix:semicolon
id|i
op_le
id|xdf2-&gt;dend
suffix:semicolon
id|i
op_increment
comma
id|recs
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dis2
(braket
id|i
)braket
op_eq
l_int|1
op_logical_or
(paren
id|dis2
(braket
id|i
)braket
op_eq
l_int|2
op_logical_and
op_logical_neg
id|xdl_clean_mmatch
c_func
(paren
id|dis2
comma
id|i
comma
id|xdf2-&gt;dstart
comma
id|xdf2-&gt;dend
)paren
)paren
)paren
(brace
id|xdf2-&gt;rindex
(braket
id|nreff
)braket
op_assign
id|i
suffix:semicolon
id|xdf2-&gt;ha
(braket
id|nreff
)braket
op_assign
(paren
op_star
id|recs
)paren
op_member_access_from_pointer
id|ha
suffix:semicolon
id|nreff
op_increment
suffix:semicolon
)brace
r_else
id|xdf2-&gt;rchg
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|xdf2-&gt;nreff
op_assign
id|nreff
suffix:semicolon
id|xdl_free
c_func
(paren
id|dis
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Early trim initial and terminal matching records.&n; */
DECL|function|xdl_trim_ends
r_static
r_int
id|xdl_trim_ends
c_func
(paren
id|xdfile_t
op_star
id|xdf1
comma
id|xdfile_t
op_star
id|xdf2
)paren
(brace
r_int
id|i
comma
id|lim
suffix:semicolon
id|xrecord_t
op_star
op_star
id|recs1
comma
op_star
op_star
id|recs2
suffix:semicolon
id|recs1
op_assign
id|xdf1-&gt;recs
suffix:semicolon
id|recs2
op_assign
id|xdf2-&gt;recs
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|lim
op_assign
id|XDL_MIN
c_func
(paren
id|xdf1-&gt;nrec
comma
id|xdf2-&gt;nrec
)paren
suffix:semicolon
id|i
OL
id|lim
suffix:semicolon
id|i
op_increment
comma
id|recs1
op_increment
comma
id|recs2
op_increment
)paren
r_if
c_cond
(paren
(paren
op_star
id|recs1
)paren
op_member_access_from_pointer
id|ha
op_ne
(paren
op_star
id|recs2
)paren
op_member_access_from_pointer
id|ha
)paren
r_break
suffix:semicolon
id|xdf1-&gt;dstart
op_assign
id|xdf2-&gt;dstart
op_assign
id|i
suffix:semicolon
id|recs1
op_assign
id|xdf1-&gt;recs
op_plus
id|xdf1-&gt;nrec
l_int|1
suffix:semicolon
id|recs2
op_assign
id|xdf2-&gt;recs
op_plus
id|xdf2-&gt;nrec
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|lim
op_sub_assign
id|i
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lim
suffix:semicolon
id|i
op_increment
comma
id|recs1
op_decrement
comma
id|recs2
op_decrement
)paren
r_if
c_cond
(paren
(paren
op_star
id|recs1
)paren
op_member_access_from_pointer
id|ha
op_ne
(paren
op_star
id|recs2
)paren
op_member_access_from_pointer
id|ha
)paren
r_break
suffix:semicolon
id|xdf1-&gt;dend
op_assign
id|xdf1-&gt;nrec
id|i
l_int|1
suffix:semicolon
id|xdf2-&gt;dend
op_assign
id|xdf2-&gt;nrec
id|i
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xdl_optimize_ctxs
r_static
r_int
id|xdl_optimize_ctxs
c_func
(paren
id|xdlclassifier_t
op_star
id|cf
comma
id|xdfile_t
op_star
id|xdf1
comma
id|xdfile_t
op_star
id|xdf2
)paren
(brace
r_if
c_cond
(paren
id|xdl_trim_ends
c_func
(paren
id|xdf1
comma
id|xdf2
)paren
OL
l_int|0
op_logical_or
id|xdl_cleanup_records
c_func
(paren
id|cf
comma
id|xdf1
comma
id|xdf2
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
eof
