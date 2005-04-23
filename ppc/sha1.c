multiline_comment|/*&n; * SHA-1 implementation.&n; *&n; * Copyright (C) 2005 Paul Mackerras &lt;paulus@samba.org&gt;&n; *&n; * This version assumes we are running on a big-endian machine.&n; * It calls an external sha1_core() to process blocks of 64 bytes.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;sha1.h&quot;
r_extern
r_void
id|sha1_core
c_func
(paren
r_uint32
op_star
id|hash
comma
r_const
r_int
r_char
op_star
id|p
comma
r_int
r_int
id|nblocks
)paren
suffix:semicolon
DECL|function|SHA1_Init
r_int
id|SHA1_Init
c_func
(paren
id|SHA_CTX
op_star
id|c
)paren
(brace
id|c-&gt;hash
(braket
l_int|0
)braket
op_assign
l_int|0x67452301
suffix:semicolon
id|c-&gt;hash
(braket
l_int|1
)braket
op_assign
l_int|0xEFCDAB89
suffix:semicolon
id|c-&gt;hash
(braket
l_int|2
)braket
op_assign
l_int|0x98BADCFE
suffix:semicolon
id|c-&gt;hash
(braket
l_int|3
)braket
op_assign
l_int|0x10325476
suffix:semicolon
id|c-&gt;hash
(braket
l_int|4
)braket
op_assign
l_int|0xC3D2E1F0
suffix:semicolon
id|c-&gt;len
op_assign
l_int|0
suffix:semicolon
id|c-&gt;cnt
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|SHA1_Update
r_int
id|SHA1_Update
c_func
(paren
id|SHA_CTX
op_star
id|c
comma
r_const
r_void
op_star
id|ptr
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|nb
suffix:semicolon
r_const
r_int
r_char
op_star
id|p
op_assign
id|ptr
suffix:semicolon
id|c-&gt;len
op_add_assign
id|n
op_lshift
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|c-&gt;cnt
op_logical_or
id|n
OL
l_int|64
)paren
(brace
id|nb
op_assign
l_int|64
id|c-&gt;cnt
suffix:semicolon
r_if
c_cond
(paren
id|nb
OG
id|n
)paren
id|nb
op_assign
id|n
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|c-&gt;buf.b
(braket
id|c-&gt;cnt
)braket
comma
id|p
comma
id|nb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;cnt
op_add_assign
id|nb
)paren
op_eq
l_int|64
)paren
(brace
id|sha1_core
c_func
(paren
id|c-&gt;hash
comma
id|c-&gt;buf.b
comma
l_int|1
)paren
suffix:semicolon
id|c-&gt;cnt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|nb
op_assign
id|n
op_rshift
l_int|6
suffix:semicolon
id|sha1_core
c_func
(paren
id|c-&gt;hash
comma
id|p
comma
id|nb
)paren
suffix:semicolon
id|nb
op_lshift_assign
l_int|6
suffix:semicolon
)brace
id|n
op_sub_assign
id|nb
suffix:semicolon
id|p
op_add_assign
id|nb
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|SHA1_Final
r_int
id|SHA1_Final
c_func
(paren
r_int
r_char
op_star
id|hash
comma
id|SHA_CTX
op_star
id|c
)paren
(brace
r_int
r_int
id|cnt
op_assign
id|c-&gt;cnt
suffix:semicolon
id|c-&gt;buf.b
(braket
id|cnt
op_increment
)braket
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OG
l_int|56
)paren
(brace
r_if
c_cond
(paren
id|cnt
OL
l_int|64
)paren
id|memset
c_func
(paren
op_amp
id|c-&gt;buf.b
(braket
id|cnt
)braket
comma
l_int|0
comma
l_int|64
id|cnt
)paren
suffix:semicolon
id|sha1_core
c_func
(paren
id|c-&gt;hash
comma
id|c-&gt;buf.b
comma
l_int|1
)paren
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
OL
l_int|56
)paren
id|memset
c_func
(paren
op_amp
id|c-&gt;buf.b
(braket
id|cnt
)braket
comma
l_int|0
comma
l_int|56
id|cnt
)paren
suffix:semicolon
id|c-&gt;buf.l
(braket
l_int|7
)braket
op_assign
id|c-&gt;len
suffix:semicolon
id|sha1_core
c_func
(paren
id|c-&gt;hash
comma
id|c-&gt;buf.b
comma
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hash
comma
id|c-&gt;hash
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
