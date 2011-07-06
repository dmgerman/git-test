multiline_comment|/*&n; * patch-delta.c:&n; * recreate a buffer from a source and the delta produced by diff-delta.c&n; *&n; * (C) 2005 Nicolas Pitre &lt;nico@fluxnic.net&gt;&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;delta.h&quot;
DECL|function|patch_delta
r_void
op_star
id|patch_delta
c_func
(paren
r_const
r_void
op_star
id|src_buf
comma
r_int
r_int
id|src_size
comma
r_const
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
r_if
c_cond
(paren
id|delta_size
OL
id|DELTA_SIZE_MIN
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
(paren
r_const
r_int
r_char
op_star
)paren
id|delta_buf
op_plus
id|delta_size
suffix:semicolon
multiline_comment|/* make sure the orig file size matches what we expect */
id|size
op_assign
id|get_delta_hdr_size
c_func
(paren
op_amp
id|data
comma
id|top
)paren
suffix:semicolon
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
id|size
op_assign
id|get_delta_hdr_size
c_func
(paren
op_amp
id|data
comma
id|top
)paren
suffix:semicolon
id|dst_buf
op_assign
id|xmallocz
c_func
(paren
id|size
)paren
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
(paren
r_int
)paren
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
id|cmd
op_amp
l_int|0x40
)paren
id|cp_size
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
id|unsigned_add_overflows
c_func
(paren
id|cp_off
comma
id|cp_size
)paren
op_logical_or
id|cp_off
op_plus
id|cp_size
OG
id|src_size
op_logical_or
id|cp_size
OG
id|size
)paren
r_break
suffix:semicolon
id|memcpy
c_func
(paren
id|out
comma
(paren
r_char
op_star
)paren
id|src_buf
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
id|size
op_sub_assign
id|cp_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd
)paren
(brace
r_if
c_cond
(paren
id|cmd
OG
id|size
)paren
r_break
suffix:semicolon
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
id|size
op_sub_assign
id|cmd
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * cmd == 0 is reserved for future encoding&n;&t;&t;&t; * extensions. In the mean time we must fail when&n;&t;&t;&t; * encountering them (might be data corruption).&n;&t;&t;&t; */
id|error
c_func
(paren
l_string|&quot;unexpected delta opcode 0&quot;
)paren
suffix:semicolon
r_goto
id|bad
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
id|size
op_ne
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;delta replay has gone wild&quot;
)paren
suffix:semicolon
id|bad
suffix:colon
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
id|out
id|dst_buf
suffix:semicolon
r_return
id|dst_buf
suffix:semicolon
)brace
eof
