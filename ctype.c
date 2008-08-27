multiline_comment|/*&n; * Sane locale-independent, ASCII ctype.&n; *&n; * No surprises, and works with signed and unsigned chars.&n; */
macro_line|#include &quot;cache.h&quot;
multiline_comment|/* Just so that no insane platform contaminate namespace with these symbols */
DECL|macro|SS
macro_line|#undef SS
DECL|macro|AA
macro_line|#undef AA
DECL|macro|DD
macro_line|#undef DD
DECL|macro|SS
mdefine_line|#define SS GIT_SPACE
DECL|macro|AA
mdefine_line|#define AA GIT_ALPHA
DECL|macro|DD
mdefine_line|#define DD GIT_DIGIT
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
id|SS
comma
id|SS
comma
l_int|0
comma
l_int|0
comma
id|SS
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* 0-15 */
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
multiline_comment|/* 16-15 */
id|SS
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
multiline_comment|/* 32-15 */
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
comma
id|DD
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
multiline_comment|/* 48-15 */
l_int|0
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
multiline_comment|/* 64-15 */
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
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
multiline_comment|/* 80-15 */
l_int|0
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
multiline_comment|/* 96-15 */
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
comma
id|AA
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
multiline_comment|/* 112-15 */
multiline_comment|/* Nothing in the 128.. range */
)brace
suffix:semicolon
eof
