multiline_comment|/*&n; * Sane locale-independent, ASCII ctype.&n; *&n; * No surprises, and works with signed and unsigned chars.&n; */
macro_line|#include &quot;cache.h&quot;
r_enum
(brace
DECL|enumerator|S
id|S
op_assign
id|GIT_SPACE
comma
DECL|enumerator|A
id|A
op_assign
id|GIT_ALPHA
comma
DECL|enumerator|D
id|D
op_assign
id|GIT_DIGIT
comma
DECL|enumerator|G
id|G
op_assign
id|GIT_GLOB_SPECIAL
comma
multiline_comment|/* *, ?, [, &bslash;&bslash; */
)brace
suffix:semicolon
DECL|variable|sane_ctype
r_int
r_char
id|sane_ctype
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|S
comma
id|S
comma
l_int|0
comma
l_int|0
comma
id|S
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*   0.. 15 */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*  16.. 31 */
id|S
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|G
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*  32.. 47 */
id|D
comma
id|D
comma
id|D
comma
id|D
comma
id|D
comma
id|D
comma
id|D
comma
id|D
comma
id|D
comma
id|D
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|G
comma
multiline_comment|/*  48.. 63 */
l_int|0
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
multiline_comment|/*  64.. 79 */
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|G
comma
id|G
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/*  80.. 95 */
l_int|0
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
multiline_comment|/*  96..111 */
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
id|A
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 112..127 */
multiline_comment|/* Nothing in the 128.. range */
)brace
suffix:semicolon
eof
