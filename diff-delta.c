multiline_comment|/*&n; * diff-delta.c: generate a delta between two buffers&n; *&n; *  Many parts of this file have been lifted from LibXDiff version 0.10.&n; *  http://www.xmailserver.org/xdiff-lib.html&n; *&n; *  LibXDiff was written by Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *  Copyright (C) 2003&t;Davide Libenzi&n; *&n; *  Many mods for GIT usage by Nicolas Pitre &lt;nico@cam.org&gt;, (C) 2005.&n; *&n; *  This file is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU Lesser General Public&n; *  License as published by the Free Software Foundation; either&n; *  version 2.1 of the License, or (at your option) any later version.&n; *&n; *  Use of this within git automatically means that the LGPL&n; *  licensing gets turned into GPLv2 within this project.&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;zlib.h&gt;
macro_line|#include &quot;delta.h&quot;
multiline_comment|/* block size: min = 16, max = 64k, power of 2 */
DECL|macro|BLK_SIZE
mdefine_line|#define BLK_SIZE 16
DECL|macro|MIN
mdefine_line|#define MIN(a, b) ((a) &lt; (b) ? (a) : (b))
DECL|macro|GR_PRIME
mdefine_line|#define GR_PRIME 0x9e370001
DECL|macro|HASH
mdefine_line|#define HASH(v, shift) (((unsigned int)(v) * GR_PRIME) &gt;&gt; (shift))
DECL|struct|index
r_struct
id|index
(brace
DECL|member|ptr
r_const
r_int
r_char
op_star
id|ptr
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
DECL|member|next
r_struct
id|index
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|function|delta_index
r_static
r_struct
id|index
op_star
op_star
id|delta_index
c_func
(paren
r_const
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|bufsize
comma
r_int
r_int
op_star
id|hash_shift
)paren
(brace
r_int
r_int
id|hsize
comma
id|hshift
comma
id|entries
comma
id|blksize
comma
id|i
suffix:semicolon
r_const
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|index
op_star
id|entry
comma
op_star
op_star
id|hash
suffix:semicolon
r_void
op_star
id|mem
suffix:semicolon
multiline_comment|/* determine index hash size */
id|entries
op_assign
(paren
id|bufsize
op_plus
id|BLK_SIZE
l_int|1
)paren
op_div
id|BLK_SIZE
suffix:semicolon
id|hsize
op_assign
id|entries
op_div
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
(paren
l_int|1
op_lshift
id|i
)paren
OL
id|hsize
op_logical_and
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|hsize
op_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|hshift
op_assign
l_int|32
id|i
suffix:semicolon
op_star
id|hash_shift
op_assign
id|hshift
suffix:semicolon
multiline_comment|/* allocate lookup index */
id|mem
op_assign
id|malloc
c_func
(paren
id|hsize
op_star
r_sizeof
(paren
op_star
id|hash
)paren
op_plus
id|entries
op_star
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
r_return
l_int|NULL
suffix:semicolon
id|hash
op_assign
id|mem
suffix:semicolon
id|entry
op_assign
id|mem
op_plus
id|hsize
op_star
r_sizeof
(paren
op_star
id|hash
)paren
suffix:semicolon
id|memset
c_func
(paren
id|hash
comma
l_int|0
comma
id|hsize
op_star
r_sizeof
(paren
op_star
id|hash
)paren
)paren
suffix:semicolon
multiline_comment|/* then populate it */
id|data
op_assign
id|buf
op_plus
id|entries
op_star
id|BLK_SIZE
id|BLK_SIZE
suffix:semicolon
id|blksize
op_assign
id|bufsize
(paren
id|data
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|data
op_ge
id|buf
)paren
(brace
r_int
r_int
id|val
op_assign
id|adler32
c_func
(paren
l_int|0
comma
id|data
comma
id|blksize
)paren
suffix:semicolon
id|i
op_assign
id|HASH
c_func
(paren
id|val
comma
id|hshift
)paren
suffix:semicolon
id|entry-&gt;ptr
op_assign
id|data
suffix:semicolon
id|entry-&gt;val
op_assign
id|val
suffix:semicolon
id|entry-&gt;next
op_assign
id|hash
(braket
id|i
)braket
suffix:semicolon
id|hash
(braket
id|i
)braket
op_assign
id|entry
op_increment
suffix:semicolon
id|blksize
op_assign
id|BLK_SIZE
suffix:semicolon
id|data
op_sub_assign
id|BLK_SIZE
suffix:semicolon
)brace
r_return
id|hash
suffix:semicolon
)brace
multiline_comment|/* provide the size of the copy opcode given the block offset and size */
DECL|macro|COPYOP_SIZE
mdefine_line|#define COPYOP_SIZE(o, s) &bslash;&n;    (!!(o &amp; 0xff) + !!(o &amp; 0xff00) + !!(o &amp; 0xff0000) + !!(o &amp; 0xff000000) + &bslash;&n;     !!(s &amp; 0xff) + !!(s &amp; 0xff00) + 1)
multiline_comment|/* the maximum size for any opcode */
DECL|macro|MAX_OP_SIZE
mdefine_line|#define MAX_OP_SIZE COPYOP_SIZE(0xffffffff, 0xffffffff)
DECL|function|diff_delta
r_void
op_star
id|diff_delta
c_func
(paren
r_void
op_star
id|from_buf
comma
r_int
r_int
id|from_size
comma
r_void
op_star
id|to_buf
comma
r_int
r_int
id|to_size
comma
r_int
r_int
op_star
id|delta_size
comma
r_int
r_int
id|max_size
)paren
(brace
r_int
r_int
id|i
comma
id|outpos
comma
id|outsize
comma
id|inscnt
comma
id|hash_shift
suffix:semicolon
r_const
r_int
r_char
op_star
id|ref_data
comma
op_star
id|ref_top
comma
op_star
id|data
comma
op_star
id|top
suffix:semicolon
r_int
r_char
op_star
id|out
suffix:semicolon
r_struct
id|index
op_star
id|entry
comma
op_star
op_star
id|hash
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|from_size
op_logical_or
op_logical_neg
id|to_size
)paren
r_return
l_int|NULL
suffix:semicolon
id|hash
op_assign
id|delta_index
c_func
(paren
id|from_buf
comma
id|from_size
comma
op_amp
id|hash_shift
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash
)paren
r_return
l_int|NULL
suffix:semicolon
id|outpos
op_assign
l_int|0
suffix:semicolon
id|outsize
op_assign
l_int|8192
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outsize
op_ge
id|max_size
)paren
id|outsize
op_assign
id|max_size
op_plus
id|MAX_OP_SIZE
op_plus
l_int|1
suffix:semicolon
id|out
op_assign
id|malloc
c_func
(paren
id|outsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out
)paren
(brace
id|free
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ref_data
op_assign
id|from_buf
suffix:semicolon
id|ref_top
op_assign
id|from_buf
op_plus
id|from_size
suffix:semicolon
id|data
op_assign
id|to_buf
suffix:semicolon
id|top
op_assign
id|to_buf
op_plus
id|to_size
suffix:semicolon
multiline_comment|/* store reference buffer size */
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|from_size
suffix:semicolon
id|from_size
op_rshift_assign
l_int|7
suffix:semicolon
r_while
c_loop
(paren
id|from_size
)paren
(brace
id|out
(braket
id|outpos
l_int|1
)braket
op_or_assign
l_int|0x80
suffix:semicolon
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|from_size
suffix:semicolon
id|from_size
op_rshift_assign
l_int|7
suffix:semicolon
)brace
multiline_comment|/* store target buffer size */
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|to_size
suffix:semicolon
id|to_size
op_rshift_assign
l_int|7
suffix:semicolon
r_while
c_loop
(paren
id|to_size
)paren
(brace
id|out
(braket
id|outpos
l_int|1
)braket
op_or_assign
l_int|0x80
suffix:semicolon
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|to_size
suffix:semicolon
id|to_size
op_rshift_assign
l_int|7
suffix:semicolon
)brace
id|inscnt
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
r_int
r_int
id|moff
op_assign
l_int|0
comma
id|msize
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|blksize
op_assign
id|MIN
c_func
(paren
id|top
id|data
comma
id|BLK_SIZE
)paren
suffix:semicolon
r_int
r_int
id|val
op_assign
id|adler32
c_func
(paren
l_int|0
comma
id|data
comma
id|blksize
)paren
suffix:semicolon
id|i
op_assign
id|HASH
c_func
(paren
id|val
comma
id|hash_shift
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|hash
(braket
id|i
)braket
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_const
r_int
r_char
op_star
id|ref
op_assign
id|entry-&gt;ptr
suffix:semicolon
r_const
r_int
r_char
op_star
id|src
op_assign
id|data
suffix:semicolon
r_int
r_int
id|ref_size
op_assign
id|ref_top
id|ref
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;val
op_ne
id|val
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ref_size
OG
id|top
id|src
)paren
id|ref_size
op_assign
id|top
id|src
suffix:semicolon
r_while
c_loop
(paren
id|ref_size
op_logical_and
op_star
id|src
op_increment
op_eq
op_star
id|ref
)paren
(brace
id|ref
op_increment
suffix:semicolon
id|ref_size
op_decrement
suffix:semicolon
)brace
id|ref_size
op_assign
id|ref
id|entry-&gt;ptr
suffix:semicolon
r_if
c_cond
(paren
id|ref_size
OG
id|msize
)paren
(brace
multiline_comment|/* this is our best match so far */
id|moff
op_assign
id|entry-&gt;ptr
id|ref_data
suffix:semicolon
id|msize
op_assign
id|ref_size
suffix:semicolon
r_if
c_cond
(paren
id|msize
op_ge
l_int|0x10000
)paren
(brace
id|msize
op_assign
l_int|0x10000
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|msize
op_logical_or
id|msize
OL
id|COPYOP_SIZE
c_func
(paren
id|moff
comma
id|msize
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inscnt
)paren
id|outpos
op_increment
suffix:semicolon
id|out
(braket
id|outpos
op_increment
)braket
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|inscnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|inscnt
op_eq
l_int|0x7f
)paren
(brace
id|out
(braket
id|outpos
id|inscnt
l_int|1
)braket
op_assign
id|inscnt
suffix:semicolon
id|inscnt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
r_char
op_star
id|op
suffix:semicolon
r_if
c_cond
(paren
id|inscnt
)paren
(brace
id|out
(braket
id|outpos
id|inscnt
l_int|1
)braket
op_assign
id|inscnt
suffix:semicolon
id|inscnt
op_assign
l_int|0
suffix:semicolon
)brace
id|data
op_add_assign
id|msize
suffix:semicolon
id|op
op_assign
id|out
op_plus
id|outpos
op_increment
suffix:semicolon
id|i
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0xff
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
suffix:semicolon
id|i
op_or_assign
l_int|0x01
suffix:semicolon
)brace
id|moff
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0xff
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
suffix:semicolon
id|i
op_or_assign
l_int|0x02
suffix:semicolon
)brace
id|moff
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0xff
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
suffix:semicolon
id|i
op_or_assign
l_int|0x04
suffix:semicolon
)brace
id|moff
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0xff
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
suffix:semicolon
id|i
op_or_assign
l_int|0x08
suffix:semicolon
)brace
r_if
c_cond
(paren
id|msize
op_amp
l_int|0xff
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|msize
suffix:semicolon
id|i
op_or_assign
l_int|0x10
suffix:semicolon
)brace
id|msize
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|msize
op_amp
l_int|0xff
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|msize
suffix:semicolon
id|i
op_or_assign
l_int|0x20
suffix:semicolon
)brace
op_star
id|op
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|outpos
op_ge
id|outsize
id|MAX_OP_SIZE
)paren
(brace
r_void
op_star
id|tmp
op_assign
id|out
suffix:semicolon
id|outsize
op_assign
id|outsize
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outsize
op_ge
id|max_size
)paren
id|outsize
op_assign
id|max_size
op_plus
id|MAX_OP_SIZE
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outpos
OG
id|max_size
)paren
id|out
op_assign
l_int|NULL
suffix:semicolon
r_else
id|out
op_assign
id|realloc
c_func
(paren
id|out
comma
id|outsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out
)paren
(brace
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|free
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|inscnt
)paren
id|out
(braket
id|outpos
id|inscnt
l_int|1
)braket
op_assign
id|inscnt
suffix:semicolon
id|free
c_func
(paren
id|hash
)paren
suffix:semicolon
op_star
id|delta_size
op_assign
id|outpos
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
eof
