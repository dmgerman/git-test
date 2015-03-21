macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;ll-merge.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;merge-blobs.h&quot;
DECL|function|fill_mmfile_blob
r_static
r_int
id|fill_mmfile_blob
c_func
(paren
id|mmfile_t
op_star
id|f
comma
r_struct
id|blob
op_star
id|obj
)paren
(brace
r_void
op_star
id|buf
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|obj-&gt;object.sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|f-&gt;ptr
op_assign
id|buf
suffix:semicolon
id|f-&gt;size
op_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_mmfile
r_static
r_void
id|free_mmfile
c_func
(paren
id|mmfile_t
op_star
id|f
)paren
(brace
id|free
c_func
(paren
id|f-&gt;ptr
)paren
suffix:semicolon
)brace
DECL|function|three_way_filemerge
r_static
r_void
op_star
id|three_way_filemerge
c_func
(paren
r_const
r_char
op_star
id|path
comma
id|mmfile_t
op_star
id|base
comma
id|mmfile_t
op_star
id|our
comma
id|mmfile_t
op_star
id|their
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_int
id|merge_status
suffix:semicolon
id|mmbuffer_t
id|res
suffix:semicolon
multiline_comment|/*&n;&t; * This function is only used by cmd_merge_tree, which&n;&t; * does not respect the merge.conflictstyle option.&n;&t; * There is no need to worry about a label for the&n;&t; * common ancestor.&n;&t; */
id|merge_status
op_assign
id|ll_merge
c_func
(paren
op_amp
id|res
comma
id|path
comma
id|base
comma
l_int|NULL
comma
id|our
comma
l_string|&quot;.our&quot;
comma
id|their
comma
l_string|&quot;.their&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|merge_status
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|size
op_assign
id|res.size
suffix:semicolon
r_return
id|res.ptr
suffix:semicolon
)brace
DECL|function|common_outf
r_static
r_int
id|common_outf
c_func
(paren
r_void
op_star
id|priv_
comma
id|mmbuffer_t
op_star
id|mb
comma
r_int
id|nbuf
)paren
(brace
r_int
id|i
suffix:semicolon
id|mmfile_t
op_star
id|dst
op_assign
id|priv_
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
id|nbuf
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memcpy
c_func
(paren
id|dst-&gt;ptr
op_plus
id|dst-&gt;size
comma
id|mb
(braket
id|i
)braket
dot
id|ptr
comma
id|mb
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|dst-&gt;size
op_add_assign
id|mb
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|generate_common_file
r_static
r_int
id|generate_common_file
c_func
(paren
id|mmfile_t
op_star
id|res
comma
id|mmfile_t
op_star
id|f1
comma
id|mmfile_t
op_star
id|f2
)paren
(brace
r_int
r_int
id|size
op_assign
id|f1-&gt;size
OL
id|f2-&gt;size
ques
c_cond
id|f1-&gt;size
suffix:colon
id|f2-&gt;size
suffix:semicolon
r_void
op_star
id|ptr
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|xpparam_t
id|xpp
suffix:semicolon
id|xdemitconf_t
id|xecfg
suffix:semicolon
id|xdemitcb_t
id|ecb
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|xpp
comma
l_int|0
comma
r_sizeof
(paren
id|xpp
)paren
)paren
suffix:semicolon
id|xpp.flags
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|xecfg
comma
l_int|0
comma
r_sizeof
(paren
id|xecfg
)paren
)paren
suffix:semicolon
id|xecfg.ctxlen
op_assign
l_int|3
suffix:semicolon
id|xecfg.flags
op_assign
id|XDL_EMIT_COMMON
suffix:semicolon
id|ecb.outf
op_assign
id|common_outf
suffix:semicolon
id|res-&gt;ptr
op_assign
id|ptr
suffix:semicolon
id|res-&gt;size
op_assign
l_int|0
suffix:semicolon
id|ecb.priv
op_assign
id|res
suffix:semicolon
r_return
id|xdi_diff
c_func
(paren
id|f1
comma
id|f2
comma
op_amp
id|xpp
comma
op_amp
id|xecfg
comma
op_amp
id|ecb
)paren
suffix:semicolon
)brace
DECL|function|merge_blobs
r_void
op_star
id|merge_blobs
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|blob
op_star
id|base
comma
r_struct
id|blob
op_star
id|our
comma
r_struct
id|blob
op_star
id|their
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_void
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
id|mmfile_t
id|f1
comma
id|f2
comma
id|common
suffix:semicolon
multiline_comment|/*&n;&t; * Removed in either branch?&n;&t; *&n;&t; * NOTE! This depends on the caller having done the&n;&t; * proper warning about removing a file that got&n;&t; * modified in the other branch!&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|our
op_logical_or
op_logical_neg
id|their
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|our
)paren
id|our
op_assign
id|their
suffix:semicolon
r_return
id|read_sha1_file
c_func
(paren
id|our-&gt;object.sha1
comma
op_amp
id|type
comma
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fill_mmfile_blob
c_func
(paren
op_amp
id|f1
comma
id|our
)paren
OL
l_int|0
)paren
r_goto
id|out_no_mmfile
suffix:semicolon
r_if
c_cond
(paren
id|fill_mmfile_blob
c_func
(paren
op_amp
id|f2
comma
id|their
)paren
OL
l_int|0
)paren
r_goto
id|out_free_f1
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
(brace
r_if
c_cond
(paren
id|fill_mmfile_blob
c_func
(paren
op_amp
id|common
comma
id|base
)paren
OL
l_int|0
)paren
r_goto
id|out_free_f2_f1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|generate_common_file
c_func
(paren
op_amp
id|common
comma
op_amp
id|f1
comma
op_amp
id|f2
)paren
OL
l_int|0
)paren
r_goto
id|out_free_f2_f1
suffix:semicolon
)brace
id|res
op_assign
id|three_way_filemerge
c_func
(paren
id|path
comma
op_amp
id|common
comma
op_amp
id|f1
comma
op_amp
id|f2
comma
id|size
)paren
suffix:semicolon
id|free_mmfile
c_func
(paren
op_amp
id|common
)paren
suffix:semicolon
id|out_free_f2_f1
suffix:colon
id|free_mmfile
c_func
(paren
op_amp
id|f2
)paren
suffix:semicolon
id|out_free_f1
suffix:colon
id|free_mmfile
c_func
(paren
op_amp
id|f1
)paren
suffix:semicolon
id|out_no_mmfile
suffix:colon
r_return
id|res
suffix:semicolon
)brace
eof
