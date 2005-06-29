multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; * The delta-parsing part is almost straight copy of patch-delta.c&n; * which is (C) 2005 Nicolas Pitre &lt;nico@cam.org&gt;.&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &quot;count-delta.h&quot;
DECL|function|get_hdr_size
r_static
r_int
r_int
id|get_hdr_size
c_func
(paren
r_const
r_int
r_char
op_star
op_star
id|datap
)paren
(brace
r_const
r_int
r_char
op_star
id|data
op_assign
op_star
id|datap
suffix:semicolon
r_int
r_char
id|cmd
op_assign
op_star
id|data
op_increment
suffix:semicolon
r_int
r_int
id|size
op_assign
id|cmd
op_amp
op_complement
l_int|0x80
suffix:semicolon
r_int
id|i
op_assign
l_int|7
suffix:semicolon
r_while
c_loop
(paren
id|cmd
op_amp
l_int|0x80
)paren
(brace
id|cmd
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|size
op_or_assign
(paren
id|cmd
op_amp
op_complement
l_int|0x80
)paren
op_lshift
id|i
suffix:semicolon
id|i
op_add_assign
l_int|7
suffix:semicolon
)brace
op_star
id|datap
op_assign
id|data
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE.  We do not _interpret_ delta fully.  As an approximation, we&n; * just count the number of bytes that are copied from the source, and&n; * the number of literal data bytes that are inserted.&n; *&n; * Number of bytes that are _not_ copied from the source is deletion,&n; * and number of inserted literal bytes are addition, so sum of them&n; * is the extent of damage.  xdelta can express an edit that copies&n; * data inside of the destination which originally came from the&n; * source.  We do not count that in the following routine, so we are&n; * undercounting the source material that remains in the final output&n; * that way.&n; */
DECL|function|count_delta
r_int
id|count_delta
c_func
(paren
r_void
op_star
id|delta_buf
comma
r_int
r_int
id|delta_size
comma
r_int
r_int
op_star
id|src_copied
comma
r_int
r_int
op_star
id|literal_added
)paren
(brace
r_int
r_int
id|copied_from_source
comma
id|added_literal
suffix:semicolon
r_const
r_int
r_char
op_star
id|data
comma
op_star
id|top
suffix:semicolon
r_int
r_char
id|cmd
suffix:semicolon
r_int
r_int
id|src_size
comma
id|dst_size
comma
id|out
suffix:semicolon
multiline_comment|/* the smallest delta size possible is 4 bytes */
r_if
c_cond
(paren
id|delta_size
OL
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
id|data
op_assign
id|delta_buf
suffix:semicolon
id|top
op_assign
id|delta_buf
op_plus
id|delta_size
suffix:semicolon
id|src_size
op_assign
id|get_hdr_size
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
id|dst_size
op_assign
id|get_hdr_size
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
id|added_literal
op_assign
id|copied_from_source
op_assign
id|out
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
id|top
)paren
(brace
id|cmd
op_assign
op_star
id|data
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x80
)paren
(brace
r_int
r_int
id|cp_off
op_assign
l_int|0
comma
id|cp_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x01
)paren
id|cp_off
op_assign
op_star
id|data
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x02
)paren
id|cp_off
op_or_assign
(paren
op_star
id|data
op_increment
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x04
)paren
id|cp_off
op_or_assign
(paren
op_star
id|data
op_increment
op_lshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x08
)paren
id|cp_off
op_or_assign
(paren
op_star
id|data
op_increment
op_lshift
l_int|24
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x10
)paren
id|cp_size
op_assign
op_star
id|data
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x20
)paren
id|cp_size
op_or_assign
(paren
op_star
id|data
op_increment
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp_size
op_eq
l_int|0
)paren
id|cp_size
op_assign
l_int|0x10000
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
l_int|0x40
)paren
multiline_comment|/* copy from dst */
suffix:semicolon
r_else
id|copied_from_source
op_add_assign
id|cp_size
suffix:semicolon
id|out
op_add_assign
id|cp_size
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* write literal into dst */
id|added_literal
op_add_assign
id|cmd
suffix:semicolon
id|out
op_add_assign
id|cmd
suffix:semicolon
id|data
op_add_assign
id|cmd
suffix:semicolon
)brace
)brace
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|data
op_ne
id|top
op_logical_or
id|out
op_ne
id|dst_size
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* delete size is what was _not_ copied from source.&n;&t; * edit size is that and literal additions.&n;&t; */
op_star
id|src_copied
op_assign
id|copied_from_source
suffix:semicolon
op_star
id|literal_added
op_assign
id|added_literal
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
