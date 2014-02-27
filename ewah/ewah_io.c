multiline_comment|/**&n; * Copyright 2013, GitHub, Inc&n; * Copyright 2009-2013, Daniel Lemire, Cliff Moon,&n; *&t;David McIntosh, Robert Becho, Google Inc. and Veronika Zenz&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;ewok.h&quot;
DECL|function|ewah_serialize_native
r_int
id|ewah_serialize_native
c_func
(paren
r_struct
id|ewah_bitmap
op_star
id|self
comma
r_int
id|fd
)paren
(brace
r_uint32
id|write32
suffix:semicolon
r_int
id|to_write
op_assign
id|self-&gt;buffer_size
op_star
l_int|8
suffix:semicolon
multiline_comment|/* 32 bit -- bit size for the map */
id|write32
op_assign
(paren
r_uint32
)paren
id|self-&gt;bit_size
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
op_amp
id|write32
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/** 32 bit -- number of compressed 64-bit words */
id|write32
op_assign
(paren
r_uint32
)paren
id|self-&gt;buffer_size
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
op_amp
id|write32
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|self-&gt;buffer
comma
id|to_write
)paren
op_ne
id|to_write
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/** 32 bit -- position for the RLW */
id|write32
op_assign
id|self-&gt;rlw
id|self-&gt;buffer
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
op_amp
id|write32
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
r_return
(paren
l_int|3
op_star
l_int|4
)paren
op_plus
id|to_write
suffix:semicolon
)brace
DECL|function|ewah_serialize_to
r_int
id|ewah_serialize_to
c_func
(paren
r_struct
id|ewah_bitmap
op_star
id|self
comma
r_int
(paren
op_star
id|write_fun
)paren
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
r_int
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
id|eword_t
id|dump
(braket
l_int|2048
)braket
suffix:semicolon
r_const
r_int
id|words_per_dump
op_assign
r_sizeof
(paren
id|dump
)paren
op_div
r_sizeof
(paren
id|eword_t
)paren
suffix:semicolon
r_uint32
id|bitsize
comma
id|word_count
comma
id|rlw_pos
suffix:semicolon
r_const
id|eword_t
op_star
id|buffer
suffix:semicolon
r_int
id|words_left
suffix:semicolon
multiline_comment|/* 32 bit -- bit size for the map */
id|bitsize
op_assign
id|htonl
c_func
(paren
(paren
r_uint32
)paren
id|self-&gt;bit_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_fun
c_func
(paren
id|data
comma
op_amp
id|bitsize
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/** 32 bit -- number of compressed 64-bit words */
id|word_count
op_assign
id|htonl
c_func
(paren
(paren
r_uint32
)paren
id|self-&gt;buffer_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_fun
c_func
(paren
id|data
comma
op_amp
id|word_count
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/** 64 bit x N -- compressed words */
id|buffer
op_assign
id|self-&gt;buffer
suffix:semicolon
id|words_left
op_assign
id|self-&gt;buffer_size
suffix:semicolon
r_while
c_loop
(paren
id|words_left
op_ge
id|words_per_dump
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|words_per_dump
suffix:semicolon
op_increment
id|i
comma
op_increment
id|buffer
)paren
id|dump
(braket
id|i
)braket
op_assign
id|htonll
c_func
(paren
op_star
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_fun
c_func
(paren
id|data
comma
id|dump
comma
r_sizeof
(paren
id|dump
)paren
)paren
op_ne
r_sizeof
(paren
id|dump
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|words_left
op_sub_assign
id|words_per_dump
suffix:semicolon
)brace
r_if
c_cond
(paren
id|words_left
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|words_left
suffix:semicolon
op_increment
id|i
comma
op_increment
id|buffer
)paren
id|dump
(braket
id|i
)braket
op_assign
id|htonll
c_func
(paren
op_star
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_fun
c_func
(paren
id|data
comma
id|dump
comma
id|words_left
op_star
l_int|8
)paren
op_ne
id|words_left
op_star
l_int|8
)paren
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/** 32 bit -- position for the RLW */
id|rlw_pos
op_assign
(paren
r_uint8
op_star
)paren
id|self-&gt;rlw
(paren
r_uint8
op_star
)paren
id|self-&gt;buffer
suffix:semicolon
id|rlw_pos
op_assign
id|htonl
c_func
(paren
id|rlw_pos
op_div
r_sizeof
(paren
id|eword_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_fun
c_func
(paren
id|data
comma
op_amp
id|rlw_pos
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
r_return
(paren
l_int|3
op_star
l_int|4
)paren
op_plus
(paren
id|self-&gt;buffer_size
op_star
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|write_helper
r_static
r_int
id|write_helper
c_func
(paren
r_void
op_star
id|fd
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_return
id|write
c_func
(paren
(paren
r_intptr
)paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|ewah_serialize
r_int
id|ewah_serialize
c_func
(paren
r_struct
id|ewah_bitmap
op_star
id|self
comma
r_int
id|fd
)paren
(brace
r_return
id|ewah_serialize_to
c_func
(paren
id|self
comma
id|write_helper
comma
(paren
r_void
op_star
)paren
(paren
r_intptr
)paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|ewah_read_mmap
r_int
id|ewah_read_mmap
c_func
(paren
r_struct
id|ewah_bitmap
op_star
id|self
comma
r_void
op_star
id|map
comma
r_int
id|len
)paren
(brace
r_uint8
op_star
id|ptr
op_assign
id|map
suffix:semicolon
r_int
id|i
suffix:semicolon
id|self-&gt;bit_size
op_assign
id|get_be32
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|ptr
op_add_assign
r_sizeof
(paren
r_uint32
)paren
suffix:semicolon
id|self-&gt;buffer_size
op_assign
id|self-&gt;alloc_size
op_assign
id|get_be32
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|ptr
op_add_assign
r_sizeof
(paren
r_uint32
)paren
suffix:semicolon
id|self-&gt;buffer
op_assign
id|ewah_realloc
c_func
(paren
id|self-&gt;buffer
comma
id|self-&gt;alloc_size
op_star
r_sizeof
(paren
id|eword_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|self-&gt;buffer
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Copy the raw data for the bitmap as a whole chunk;&n;&t; * if we&squot;re in a little-endian platform, we&squot;ll perform&n;&t; * the endianness conversion in a separate pass to ensure&n;&t; * we&squot;re loading 8-byte aligned words.&n;&t; */
id|memcpy
c_func
(paren
id|self-&gt;buffer
comma
id|ptr
comma
id|self-&gt;buffer_size
op_star
r_sizeof
(paren
r_uint64
)paren
)paren
suffix:semicolon
id|ptr
op_add_assign
id|self-&gt;buffer_size
op_star
r_sizeof
(paren
r_uint64
)paren
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
id|self-&gt;buffer_size
suffix:semicolon
op_increment
id|i
)paren
id|self-&gt;buffer
(braket
id|i
)braket
op_assign
id|ntohll
c_func
(paren
id|self-&gt;buffer
(braket
id|i
)braket
)paren
suffix:semicolon
id|self-&gt;rlw
op_assign
id|self-&gt;buffer
op_plus
id|get_be32
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_return
(paren
l_int|3
op_star
l_int|4
)paren
op_plus
(paren
id|self-&gt;buffer_size
op_star
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|ewah_deserialize
r_int
id|ewah_deserialize
c_func
(paren
r_struct
id|ewah_bitmap
op_star
id|self
comma
r_int
id|fd
)paren
(brace
r_int
id|i
suffix:semicolon
id|eword_t
id|dump
(braket
l_int|2048
)braket
suffix:semicolon
r_const
r_int
id|words_per_dump
op_assign
r_sizeof
(paren
id|dump
)paren
op_div
r_sizeof
(paren
id|eword_t
)paren
suffix:semicolon
r_uint32
id|bitsize
comma
id|word_count
comma
id|rlw_pos
suffix:semicolon
id|eword_t
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
r_int
id|words_left
suffix:semicolon
id|ewah_clear
c_func
(paren
id|self
)paren
suffix:semicolon
multiline_comment|/* 32 bit -- bit size for the map */
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|bitsize
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
id|self-&gt;bit_size
op_assign
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|bitsize
)paren
suffix:semicolon
multiline_comment|/** 32 bit -- number of compressed 64-bit words */
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|word_count
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
id|self-&gt;buffer_size
op_assign
id|self-&gt;alloc_size
op_assign
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|word_count
)paren
suffix:semicolon
id|self-&gt;buffer
op_assign
id|ewah_realloc
c_func
(paren
id|self-&gt;buffer
comma
id|self-&gt;alloc_size
op_star
r_sizeof
(paren
id|eword_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|self-&gt;buffer
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/** 64 bit x N -- compressed words */
id|buffer
op_assign
id|self-&gt;buffer
suffix:semicolon
id|words_left
op_assign
id|self-&gt;buffer_size
suffix:semicolon
r_while
c_loop
(paren
id|words_left
op_ge
id|words_per_dump
)paren
(brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
id|dump
comma
r_sizeof
(paren
id|dump
)paren
)paren
op_ne
r_sizeof
(paren
id|dump
)paren
)paren
r_return
l_int|1
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
id|words_per_dump
suffix:semicolon
op_increment
id|i
comma
op_increment
id|buffer
)paren
op_star
id|buffer
op_assign
id|ntohll
c_func
(paren
id|dump
(braket
id|i
)braket
)paren
suffix:semicolon
id|words_left
op_sub_assign
id|words_per_dump
suffix:semicolon
)brace
r_if
c_cond
(paren
id|words_left
)paren
(brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
id|dump
comma
id|words_left
op_star
l_int|8
)paren
op_ne
id|words_left
op_star
l_int|8
)paren
r_return
l_int|1
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
id|words_left
suffix:semicolon
op_increment
id|i
comma
op_increment
id|buffer
)paren
op_star
id|buffer
op_assign
id|ntohll
c_func
(paren
id|dump
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/** 32 bit -- position for the RLW */
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|rlw_pos
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
id|self-&gt;rlw
op_assign
id|self-&gt;buffer
op_plus
id|ntohl
c_func
(paren
id|rlw_pos
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
