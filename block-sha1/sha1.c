multiline_comment|/*&n; * Based on the Mozilla SHA1 (see mozilla-sha1/sha1.c),&n; * optimized to do word accesses rather than byte accesses,&n; * and to avoid unnecessary copies into the context array.&n; */
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;arpa/inet.h&gt;
macro_line|#include &quot;sha1.h&quot;
multiline_comment|/* Hash one 64-byte block of data */
r_static
r_void
id|blk_SHA1Block
c_func
(paren
id|blk_SHA_CTX
op_star
id|ctx
comma
r_const
r_int
r_int
op_star
id|data
)paren
suffix:semicolon
DECL|function|blk_SHA1_Init
r_void
id|blk_SHA1_Init
c_func
(paren
id|blk_SHA_CTX
op_star
id|ctx
)paren
(brace
id|ctx-&gt;lenW
op_assign
l_int|0
suffix:semicolon
id|ctx-&gt;size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Initialize H with the magic constants (see FIPS180 for constants)&n;&t; */
id|ctx-&gt;H
(braket
l_int|0
)braket
op_assign
l_int|0x67452301
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|1
)braket
op_assign
l_int|0xefcdab89
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|2
)braket
op_assign
l_int|0x98badcfe
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|3
)braket
op_assign
l_int|0x10325476
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|4
)braket
op_assign
l_int|0xc3d2e1f0
suffix:semicolon
)brace
DECL|function|blk_SHA1_Update
r_void
id|blk_SHA1_Update
c_func
(paren
id|blk_SHA_CTX
op_star
id|ctx
comma
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|lenW
op_assign
id|ctx-&gt;lenW
suffix:semicolon
id|ctx-&gt;size
op_add_assign
(paren
r_int
r_int
r_int
)paren
id|len
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* Read the data into W and process blocks as they get full&n;&t; */
r_if
c_cond
(paren
id|lenW
)paren
(brace
r_int
id|left
op_assign
l_int|64
id|lenW
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|left
)paren
id|left
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|lenW
op_plus
(paren
r_char
op_star
)paren
id|ctx-&gt;W
comma
id|data
comma
id|left
)paren
suffix:semicolon
id|lenW
op_assign
(paren
id|lenW
op_plus
id|left
)paren
op_amp
l_int|63
suffix:semicolon
id|len
op_sub_assign
id|left
suffix:semicolon
id|data
op_add_assign
id|left
suffix:semicolon
id|ctx-&gt;lenW
op_assign
id|lenW
suffix:semicolon
r_if
c_cond
(paren
id|lenW
)paren
r_return
suffix:semicolon
id|blk_SHA1Block
c_func
(paren
id|ctx
comma
id|ctx-&gt;W
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
op_ge
l_int|64
)paren
(brace
id|blk_SHA1Block
c_func
(paren
id|ctx
comma
id|data
)paren
suffix:semicolon
id|data
op_add_assign
l_int|64
suffix:semicolon
id|len
op_sub_assign
l_int|64
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
)paren
(brace
id|memcpy
c_func
(paren
id|ctx-&gt;W
comma
id|data
comma
id|len
)paren
suffix:semicolon
id|ctx-&gt;lenW
op_assign
id|len
suffix:semicolon
)brace
)brace
DECL|function|blk_SHA1_Final
r_void
id|blk_SHA1_Final
c_func
(paren
r_int
r_char
id|hashout
(braket
l_int|20
)braket
comma
id|blk_SHA_CTX
op_star
id|ctx
)paren
(brace
r_static
r_const
r_int
r_char
id|pad
(braket
l_int|64
)braket
op_assign
(brace
l_int|0x80
)brace
suffix:semicolon
r_int
r_int
id|padlen
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Pad with a binary 1 (ie 0x80), then zeroes, then length&n;&t; */
id|padlen
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
id|ctx-&gt;size
op_rshift
l_int|32
)paren
suffix:semicolon
id|padlen
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
id|ctx-&gt;size
)paren
suffix:semicolon
id|blk_SHA1_Update
c_func
(paren
id|ctx
comma
id|pad
comma
l_int|1
op_plus
(paren
l_int|63
op_amp
(paren
l_int|55
id|ctx-&gt;lenW
)paren
)paren
)paren
suffix:semicolon
id|blk_SHA1_Update
c_func
(paren
id|ctx
comma
id|padlen
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Output hash&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(paren
(paren
r_int
r_int
op_star
)paren
id|hashout
)paren
(braket
id|i
)braket
op_assign
id|htonl
c_func
(paren
id|ctx-&gt;H
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#if defined(__i386__) || defined(__x86_64__)
DECL|macro|SHA_ASM
mdefine_line|#define SHA_ASM(op, x, n) ({ unsigned int __res; __asm__(op &quot; %1,%0&quot;:&quot;=r&quot; (__res):&quot;i&quot; (n), &quot;0&quot; (x)); __res; })
DECL|macro|SHA_ROL
mdefine_line|#define SHA_ROL(x,n)&t;SHA_ASM(&quot;rol&quot;, x, n)
DECL|macro|SHA_ROR
mdefine_line|#define SHA_ROR(x,n)&t;SHA_ASM(&quot;ror&quot;, x, n)
macro_line|#else
DECL|macro|SHA_ROT
mdefine_line|#define SHA_ROT(X,l,r)&t;(((X) &lt;&lt; (l)) | ((X) &gt;&gt; (r)))
DECL|macro|SHA_ROL
mdefine_line|#define SHA_ROL(X,n)&t;SHA_ROT(X,n,32-(n))
DECL|macro|SHA_ROR
mdefine_line|#define SHA_ROR(X,n)&t;SHA_ROT(X,32-(n),n)
macro_line|#endif
multiline_comment|/* This &quot;rolls&quot; over the 512-bit array */
DECL|macro|W
mdefine_line|#define W(x) (array[(x)&amp;15])
multiline_comment|/*&n; * Where do we get the source from? The first 16 iterations get it from&n; * the input data, the next mix it from the 512-bit array.&n; */
DECL|macro|SHA_SRC
mdefine_line|#define SHA_SRC(t) htonl(data[t])
DECL|macro|SHA_MIX
mdefine_line|#define SHA_MIX(t) SHA_ROL(W(t+13) ^ W(t+8) ^ W(t+2) ^ W(t), 1)
DECL|macro|SHA_ROUND
mdefine_line|#define SHA_ROUND(t, input, fn, constant) &bslash;&n;&t;TEMP = input(t); W(t) = TEMP; &bslash;&n;&t;TEMP += SHA_ROL(A,5) + (fn) + E + (constant); &bslash;&n;&t;E = D; D = C; C = SHA_ROR(B, 2); B = A; A = TEMP
DECL|macro|T_0_15
mdefine_line|#define T_0_15(t)  SHA_ROUND(t, SHA_SRC, (((C^D)&amp;B)^D) , 0x5a827999 )
DECL|macro|T_16_19
mdefine_line|#define T_16_19(t) SHA_ROUND(t, SHA_MIX, (((C^D)&amp;B)^D) , 0x5a827999 )
DECL|macro|T_20_39
mdefine_line|#define T_20_39(t) SHA_ROUND(t, SHA_MIX, (B^C^D) , 0x6ed9eba1 )
DECL|macro|T_40_59
mdefine_line|#define T_40_59(t) SHA_ROUND(t, SHA_MIX, ((B&amp;C)+(D&amp;(B^C))) , 0x8f1bbcdc )
DECL|macro|T_60_79
mdefine_line|#define T_60_79(t) SHA_ROUND(t, SHA_MIX, (B^C^D) ,  0xca62c1d6 )
DECL|function|blk_SHA1Block
r_static
r_void
id|blk_SHA1Block
c_func
(paren
id|blk_SHA_CTX
op_star
id|ctx
comma
r_const
r_int
r_int
op_star
id|data
)paren
(brace
r_int
r_int
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|TEMP
suffix:semicolon
r_int
r_int
id|array
(braket
l_int|16
)braket
suffix:semicolon
id|A
op_assign
id|ctx-&gt;H
(braket
l_int|0
)braket
suffix:semicolon
id|B
op_assign
id|ctx-&gt;H
(braket
l_int|1
)braket
suffix:semicolon
id|C
op_assign
id|ctx-&gt;H
(braket
l_int|2
)braket
suffix:semicolon
id|D
op_assign
id|ctx-&gt;H
(braket
l_int|3
)braket
suffix:semicolon
id|E
op_assign
id|ctx-&gt;H
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Round 1 - iterations 0-16 take their input from &squot;data&squot; */
id|T_0_15
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|12
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|13
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|15
)paren
suffix:semicolon
multiline_comment|/* Round 1 - tail. Input from 512-bit mixing array */
id|T_16_19
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|T_16_19
c_func
(paren
l_int|17
)paren
suffix:semicolon
id|T_16_19
c_func
(paren
l_int|18
)paren
suffix:semicolon
id|T_16_19
c_func
(paren
l_int|19
)paren
suffix:semicolon
multiline_comment|/* Round 2 */
id|T_20_39
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|21
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|22
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|23
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|24
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|25
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|26
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|27
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|28
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|29
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|30
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|31
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|32
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|33
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|34
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|35
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|36
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|37
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|38
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|39
)paren
suffix:semicolon
multiline_comment|/* Round 3 */
id|T_40_59
c_func
(paren
l_int|40
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|41
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|42
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|43
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|44
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|45
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|46
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|47
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|48
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|49
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|51
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|52
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|53
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|54
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|55
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|56
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|57
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|58
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|59
)paren
suffix:semicolon
multiline_comment|/* Round 4 */
id|T_60_79
c_func
(paren
l_int|60
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|61
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|62
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|63
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|64
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|65
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|66
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|67
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|68
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|69
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|70
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|71
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|72
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|73
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|74
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|75
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|76
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|77
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|78
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|79
)paren
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|0
)braket
op_add_assign
id|A
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|1
)braket
op_add_assign
id|B
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|2
)braket
op_add_assign
id|C
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|3
)braket
op_add_assign
id|D
suffix:semicolon
id|ctx-&gt;H
(braket
l_int|4
)braket
op_add_assign
id|E
suffix:semicolon
)brace
eof
