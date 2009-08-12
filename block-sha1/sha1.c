multiline_comment|/*&n; * Based on the Mozilla SHA1 (see mozilla-sha1/sha1.c),&n; * optimized to do word accesses rather than byte accesses,&n; * and to avoid unnecessary copies into the context array.&n; */
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;arpa/inet.h&gt;
macro_line|#include &quot;sha1.h&quot;
macro_line|#if defined(__i386__) || defined(__x86_64__)
multiline_comment|/*&n; * Force usage of rol or ror by selecting the one with the smaller constant.&n; * It _can_ generate slightly smaller code (a constant of 1 is special), but&n; * perhaps more importantly it&squot;s possibly faster on any uarch that does a&n; * rotate with a loop.&n; */
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
multiline_comment|/*&n; * If you have 32 registers or more, the compiler can (and should)&n; * try to change the array[] accesses into registers. However, on&n; * machines with less than ~25 registers, that won&squot;t really work,&n; * and at least gcc will make an unholy mess of it.&n; *&n; * So to avoid that mess which just slows things down, we force&n; * the stores to memory to actually happen (we might be better off&n; * with a &squot;W(t)=(val);asm(&quot;&quot;:&quot;+m&quot; (W(t))&squot; there instead, as&n; * suggested by Artur Skawina - that will also make gcc unable to&n; * try to do the silly &quot;optimize away loads&quot; part because it won&squot;t&n; * see what the value will be).&n; *&n; * Ben Herrenschmidt reports that on PPC, the C version comes close&n; * to the optimized asm with this (ie on PPC you don&squot;t want that&n; * &squot;volatile&squot;, since there are lots of registers).&n; *&n; * On ARM we get the best code generation by forcing a full memory barrier&n; * between each SHA_ROUND, otherwise gcc happily get wild with spilling and&n; * the stack frame size simply explode and performance goes down the drain.&n; */
macro_line|#if defined(__i386__) || defined(__x86_64__)
DECL|macro|setW
mdefine_line|#define setW(x, val) (*(volatile unsigned int *)&amp;W(x) = (val))
macro_line|#elif defined(__arm__)
DECL|macro|setW
mdefine_line|#define setW(x, val) do { W(x) = (val); __asm__(&quot;&quot;:::&quot;memory&quot;); } while (0)
macro_line|#else
DECL|macro|setW
mdefine_line|#define setW(x, val) (W(x) = (val))
macro_line|#endif
multiline_comment|/*&n; * Performance might be improved if the CPU architecture is OK with&n; * unaligned 32-bit loads and a fast ntohl() is available.&n; * Otherwise fall back to byte loads and shifts which is portable,&n; * and is faster on architectures with memory alignment issues.&n; */
macro_line|#if defined(__i386__) || defined(__x86_64__)
DECL|macro|get_be32
mdefine_line|#define get_be32(p)&t;ntohl(*(unsigned int *)(p))
DECL|macro|put_be32
mdefine_line|#define put_be32(p, v)&t;do { *(unsigned int *)(p) = htonl(v); } while (0)
macro_line|#else
DECL|macro|get_be32
mdefine_line|#define get_be32(p)&t;( &bslash;&n;&t;(*((unsigned char *)(p) + 0) &lt;&lt; 24) | &bslash;&n;&t;(*((unsigned char *)(p) + 1) &lt;&lt; 16) | &bslash;&n;&t;(*((unsigned char *)(p) + 2) &lt;&lt;  8) | &bslash;&n;&t;(*((unsigned char *)(p) + 3) &lt;&lt;  0) )
DECL|macro|put_be32
mdefine_line|#define put_be32(p, v)&t;do { &bslash;&n;&t;unsigned int __v = (v); &bslash;&n;&t;*((unsigned char *)(p) + 0) = __v &gt;&gt; 24; &bslash;&n;&t;*((unsigned char *)(p) + 1) = __v &gt;&gt; 16; &bslash;&n;&t;*((unsigned char *)(p) + 2) = __v &gt;&gt;  8; &bslash;&n;&t;*((unsigned char *)(p) + 3) = __v &gt;&gt;  0; } while (0)
macro_line|#endif
multiline_comment|/* This &quot;rolls&quot; over the 512-bit array */
DECL|macro|W
mdefine_line|#define W(x) (array[(x)&amp;15])
multiline_comment|/*&n; * Where do we get the source from? The first 16 iterations get it from&n; * the input data, the next mix it from the 512-bit array.&n; */
DECL|macro|SHA_SRC
mdefine_line|#define SHA_SRC(t) get_be32(data + t)
DECL|macro|SHA_MIX
mdefine_line|#define SHA_MIX(t) SHA_ROL(W(t+13) ^ W(t+8) ^ W(t+2) ^ W(t), 1)
DECL|macro|SHA_ROUND
mdefine_line|#define SHA_ROUND(t, input, fn, constant, A, B, C, D, E) do { &bslash;&n;&t;unsigned int TEMP = input(t); setW(t, TEMP); &bslash;&n;&t;E += TEMP + SHA_ROL(A,5) + (fn) + (constant); &bslash;&n;&t;B = SHA_ROR(B, 2); } while (0)
DECL|macro|T_0_15
mdefine_line|#define T_0_15(t, A, B, C, D, E)  SHA_ROUND(t, SHA_SRC, (((C^D)&amp;B)^D) , 0x5a827999, A, B, C, D, E )
DECL|macro|T_16_19
mdefine_line|#define T_16_19(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, (((C^D)&amp;B)^D) , 0x5a827999, A, B, C, D, E )
DECL|macro|T_20_39
mdefine_line|#define T_20_39(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, (B^C^D) , 0x6ed9eba1, A, B, C, D, E )
DECL|macro|T_40_59
mdefine_line|#define T_40_59(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, ((B&amp;C)+(D&amp;(B^C))) , 0x8f1bbcdc, A, B, C, D, E )
DECL|macro|T_60_79
mdefine_line|#define T_60_79(t, A, B, C, D, E) SHA_ROUND(t, SHA_MIX, (B^C^D) ,  0xca62c1d6, A, B, C, D, E )
DECL|function|blk_SHA1_Block
r_static
r_void
id|blk_SHA1_Block
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
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|1
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|2
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|3
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|4
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|5
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|6
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|7
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|8
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|9
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|10
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|11
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|12
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|13
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|14
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_0_15
c_func
(paren
l_int|15
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
multiline_comment|/* Round 1 - tail. Input from 512-bit mixing array */
id|T_16_19
c_func
(paren
l_int|16
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_16_19
c_func
(paren
l_int|17
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_16_19
c_func
(paren
l_int|18
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_16_19
c_func
(paren
l_int|19
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
multiline_comment|/* Round 2 */
id|T_20_39
c_func
(paren
l_int|20
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|21
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|22
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|23
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|24
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|25
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|26
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|27
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|28
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|29
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|30
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|31
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|32
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|33
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|34
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|35
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|36
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|37
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|38
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_20_39
c_func
(paren
l_int|39
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
multiline_comment|/* Round 3 */
id|T_40_59
c_func
(paren
l_int|40
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|41
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|42
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|43
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|44
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|45
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|46
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|47
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|48
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|49
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|50
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|51
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|52
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|53
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|54
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|55
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|56
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|57
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|58
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_40_59
c_func
(paren
l_int|59
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
multiline_comment|/* Round 4 */
id|T_60_79
c_func
(paren
l_int|60
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|61
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|62
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|63
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|64
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|65
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|66
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|67
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|68
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|69
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|70
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|71
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|72
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|73
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|74
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|75
comma
id|A
comma
id|B
comma
id|C
comma
id|D
comma
id|E
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|76
comma
id|E
comma
id|A
comma
id|B
comma
id|C
comma
id|D
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|77
comma
id|D
comma
id|E
comma
id|A
comma
id|B
comma
id|C
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|78
comma
id|C
comma
id|D
comma
id|E
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|T_60_79
c_func
(paren
l_int|79
comma
id|B
comma
id|C
comma
id|D
comma
id|E
comma
id|A
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
id|ctx-&gt;size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Initialize H with the magic constants (see FIPS180 for constants) */
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
id|ctx-&gt;size
op_amp
l_int|63
suffix:semicolon
id|ctx-&gt;size
op_add_assign
id|len
suffix:semicolon
multiline_comment|/* Read the data into W and process blocks as they get full */
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
r_if
c_cond
(paren
id|lenW
)paren
r_return
suffix:semicolon
id|blk_SHA1_Block
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
id|blk_SHA1_Block
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
multiline_comment|/* Pad with a binary 1 (ie 0x80), then zeroes, then length */
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
l_int|29
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
op_lshift
l_int|3
)paren
suffix:semicolon
id|i
op_assign
id|ctx-&gt;size
op_amp
l_int|63
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
id|i
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
multiline_comment|/* Output hash */
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
id|put_be32
c_func
(paren
id|hashout
op_plus
id|i
op_star
l_int|4
comma
id|ctx-&gt;H
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
eof
