multiline_comment|/*&n; * patch-delta.c:&n; * recreate a buffer from a source and the delta produced by diff-delta.c&n; *&n; * (C) 2005 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;delta.h&quot;
DECL|function|patch_delta
r_void
op_star
id|patch_delta
c_func
(paren
r_void
op_star
id|src_buf
comma
r_int
r_int
id|src_size
comma
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
id|dst_size
)paren
(brace
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
op_star
id|dst_buf
comma
op_star
id|out
comma
id|cmd
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|i
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
l_int|NULL
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
multiline_comment|/* make sure the orig file size matches what we expect */
id|cmd
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|size
op_assign
id|cmd
op_amp
op_complement
l_int|0x80
suffix:semicolon
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
r_if
c_cond
(paren
id|size
op_ne
id|src_size
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* now the result size */
id|cmd
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|size
op_assign
id|cmd
op_amp
op_complement
l_int|0x80
suffix:semicolon
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
id|dst_buf
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_buf
)paren
r_return
l_int|NULL
suffix:semicolon
id|out
op_assign
id|dst_buf
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
r_const
r_int
r_char
op_star
id|buf
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
id|buf
op_assign
(paren
id|cmd
op_amp
l_int|0x40
)paren
ques
c_cond
id|dst_buf
suffix:colon
id|src_buf
suffix:semicolon
id|memcpy
c_func
(paren
id|out
comma
id|buf
op_plus
id|cp_off
comma
id|cp_size
)paren
suffix:semicolon
id|out
op_add_assign
id|cp_size
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|out
comma
id|data
comma
id|cmd
)paren
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
id|dst_buf
op_ne
id|size
)paren
(brace
id|free
c_func
(paren
id|dst_buf
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|dst_size
op_assign
id|size
suffix:semicolon
r_return
id|dst_buf
suffix:semicolon
)brace
eof
