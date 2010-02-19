macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;utf8.h&quot;
multiline_comment|/* This code is originally from http://www.cl.cam.ac.uk/~mgk25/ucs/ */
DECL|struct|interval
r_struct
id|interval
(brace
DECL|member|first
r_int
id|first
suffix:semicolon
DECL|member|last
r_int
id|last
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* auxiliary function for binary search in interval table */
DECL|function|bisearch
r_static
r_int
id|bisearch
c_func
(paren
id|ucs_char_t
id|ucs
comma
r_const
r_struct
id|interval
op_star
id|table
comma
r_int
id|max
)paren
(brace
r_int
id|min
op_assign
l_int|0
suffix:semicolon
r_int
id|mid
suffix:semicolon
r_if
c_cond
(paren
id|ucs
template_param
id|table
(braket
id|max
)braket
dot
id|last
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|max
op_ge
id|min
)paren
(brace
id|mid
op_assign
(paren
id|min
op_plus
id|max
)paren
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ucs
OG
id|table
(braket
id|mid
)braket
dot
id|last
)paren
id|min
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ucs
OL
id|table
(braket
id|mid
)braket
dot
id|first
)paren
id|max
op_assign
id|mid
l_int|1
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The following two functions define the column width of an ISO 10646&n; * character as follows:&n; *&n; *    - The null character (U+0000) has a column width of 0.&n; *&n; *    - Other C0/C1 control characters and DEL will lead to a return&n; *      value of -1.&n; *&n; *    - Non-spacing and enclosing combining characters (general&n; *      category code Mn or Me in the Unicode database) have a&n; *      column width of 0.&n; *&n; *    - SOFT HYPHEN (U+00AD) has a column width of 1.&n; *&n; *    - Other format characters (general category code Cf in the Unicode&n; *      database) and ZERO WIDTH SPACE (U+200B) have a column width of 0.&n; *&n; *    - Hangul Jamo medial vowels and final consonants (U+1160-U+11FF)&n; *      have a column width of 0.&n; *&n; *    - Spacing characters in the East Asian Wide (W) or East Asian&n; *      Full-width (F) category as defined in Unicode Technical&n; *      Report #11 have a column width of 2.&n; *&n; *    - All remaining characters (including all printable&n; *      ISO 8859-1 and WGL4 characters, Unicode control characters,&n; *      etc.) have a column width of 1.&n; *&n; * This implementation assumes that ucs_char_t characters are encoded&n; * in ISO 10646.&n; */
DECL|function|git_wcwidth
r_static
r_int
id|git_wcwidth
c_func
(paren
id|ucs_char_t
id|ch
)paren
(brace
multiline_comment|/*&n;&t; * Sorted list of non-overlapping intervals of non-spacing characters,&n;&t; * generated by&n;&t; *   &quot;uniset +cat=Me +cat=Mn +cat=Cf -00AD +1160-11FF +200B c&quot;.&n;&t; */
r_static
r_const
r_struct
id|interval
id|combining
(braket
)braket
op_assign
(brace
(brace
l_int|0x0300
comma
l_int|0x0357
)brace
comma
(brace
l_int|0x035D
comma
l_int|0x036F
)brace
comma
(brace
l_int|0x0483
comma
l_int|0x0486
)brace
comma
(brace
l_int|0x0488
comma
l_int|0x0489
)brace
comma
(brace
l_int|0x0591
comma
l_int|0x05A1
)brace
comma
(brace
l_int|0x05A3
comma
l_int|0x05B9
)brace
comma
(brace
l_int|0x05BB
comma
l_int|0x05BD
)brace
comma
(brace
l_int|0x05BF
comma
l_int|0x05BF
)brace
comma
(brace
l_int|0x05C1
comma
l_int|0x05C2
)brace
comma
(brace
l_int|0x05C4
comma
l_int|0x05C4
)brace
comma
(brace
l_int|0x0600
comma
l_int|0x0603
)brace
comma
(brace
l_int|0x0610
comma
l_int|0x0615
)brace
comma
(brace
l_int|0x064B
comma
l_int|0x0658
)brace
comma
(brace
l_int|0x0670
comma
l_int|0x0670
)brace
comma
(brace
l_int|0x06D6
comma
l_int|0x06E4
)brace
comma
(brace
l_int|0x06E7
comma
l_int|0x06E8
)brace
comma
(brace
l_int|0x06EA
comma
l_int|0x06ED
)brace
comma
(brace
l_int|0x070F
comma
l_int|0x070F
)brace
comma
(brace
l_int|0x0711
comma
l_int|0x0711
)brace
comma
(brace
l_int|0x0730
comma
l_int|0x074A
)brace
comma
(brace
l_int|0x07A6
comma
l_int|0x07B0
)brace
comma
(brace
l_int|0x0901
comma
l_int|0x0902
)brace
comma
(brace
l_int|0x093C
comma
l_int|0x093C
)brace
comma
(brace
l_int|0x0941
comma
l_int|0x0948
)brace
comma
(brace
l_int|0x094D
comma
l_int|0x094D
)brace
comma
(brace
l_int|0x0951
comma
l_int|0x0954
)brace
comma
(brace
l_int|0x0962
comma
l_int|0x0963
)brace
comma
(brace
l_int|0x0981
comma
l_int|0x0981
)brace
comma
(brace
l_int|0x09BC
comma
l_int|0x09BC
)brace
comma
(brace
l_int|0x09C1
comma
l_int|0x09C4
)brace
comma
(brace
l_int|0x09CD
comma
l_int|0x09CD
)brace
comma
(brace
l_int|0x09E2
comma
l_int|0x09E3
)brace
comma
(brace
l_int|0x0A01
comma
l_int|0x0A02
)brace
comma
(brace
l_int|0x0A3C
comma
l_int|0x0A3C
)brace
comma
(brace
l_int|0x0A41
comma
l_int|0x0A42
)brace
comma
(brace
l_int|0x0A47
comma
l_int|0x0A48
)brace
comma
(brace
l_int|0x0A4B
comma
l_int|0x0A4D
)brace
comma
(brace
l_int|0x0A70
comma
l_int|0x0A71
)brace
comma
(brace
l_int|0x0A81
comma
l_int|0x0A82
)brace
comma
(brace
l_int|0x0ABC
comma
l_int|0x0ABC
)brace
comma
(brace
l_int|0x0AC1
comma
l_int|0x0AC5
)brace
comma
(brace
l_int|0x0AC7
comma
l_int|0x0AC8
)brace
comma
(brace
l_int|0x0ACD
comma
l_int|0x0ACD
)brace
comma
(brace
l_int|0x0AE2
comma
l_int|0x0AE3
)brace
comma
(brace
l_int|0x0B01
comma
l_int|0x0B01
)brace
comma
(brace
l_int|0x0B3C
comma
l_int|0x0B3C
)brace
comma
(brace
l_int|0x0B3F
comma
l_int|0x0B3F
)brace
comma
(brace
l_int|0x0B41
comma
l_int|0x0B43
)brace
comma
(brace
l_int|0x0B4D
comma
l_int|0x0B4D
)brace
comma
(brace
l_int|0x0B56
comma
l_int|0x0B56
)brace
comma
(brace
l_int|0x0B82
comma
l_int|0x0B82
)brace
comma
(brace
l_int|0x0BC0
comma
l_int|0x0BC0
)brace
comma
(brace
l_int|0x0BCD
comma
l_int|0x0BCD
)brace
comma
(brace
l_int|0x0C3E
comma
l_int|0x0C40
)brace
comma
(brace
l_int|0x0C46
comma
l_int|0x0C48
)brace
comma
(brace
l_int|0x0C4A
comma
l_int|0x0C4D
)brace
comma
(brace
l_int|0x0C55
comma
l_int|0x0C56
)brace
comma
(brace
l_int|0x0CBC
comma
l_int|0x0CBC
)brace
comma
(brace
l_int|0x0CBF
comma
l_int|0x0CBF
)brace
comma
(brace
l_int|0x0CC6
comma
l_int|0x0CC6
)brace
comma
(brace
l_int|0x0CCC
comma
l_int|0x0CCD
)brace
comma
(brace
l_int|0x0D41
comma
l_int|0x0D43
)brace
comma
(brace
l_int|0x0D4D
comma
l_int|0x0D4D
)brace
comma
(brace
l_int|0x0DCA
comma
l_int|0x0DCA
)brace
comma
(brace
l_int|0x0DD2
comma
l_int|0x0DD4
)brace
comma
(brace
l_int|0x0DD6
comma
l_int|0x0DD6
)brace
comma
(brace
l_int|0x0E31
comma
l_int|0x0E31
)brace
comma
(brace
l_int|0x0E34
comma
l_int|0x0E3A
)brace
comma
(brace
l_int|0x0E47
comma
l_int|0x0E4E
)brace
comma
(brace
l_int|0x0EB1
comma
l_int|0x0EB1
)brace
comma
(brace
l_int|0x0EB4
comma
l_int|0x0EB9
)brace
comma
(brace
l_int|0x0EBB
comma
l_int|0x0EBC
)brace
comma
(brace
l_int|0x0EC8
comma
l_int|0x0ECD
)brace
comma
(brace
l_int|0x0F18
comma
l_int|0x0F19
)brace
comma
(brace
l_int|0x0F35
comma
l_int|0x0F35
)brace
comma
(brace
l_int|0x0F37
comma
l_int|0x0F37
)brace
comma
(brace
l_int|0x0F39
comma
l_int|0x0F39
)brace
comma
(brace
l_int|0x0F71
comma
l_int|0x0F7E
)brace
comma
(brace
l_int|0x0F80
comma
l_int|0x0F84
)brace
comma
(brace
l_int|0x0F86
comma
l_int|0x0F87
)brace
comma
(brace
l_int|0x0F90
comma
l_int|0x0F97
)brace
comma
(brace
l_int|0x0F99
comma
l_int|0x0FBC
)brace
comma
(brace
l_int|0x0FC6
comma
l_int|0x0FC6
)brace
comma
(brace
l_int|0x102D
comma
l_int|0x1030
)brace
comma
(brace
l_int|0x1032
comma
l_int|0x1032
)brace
comma
(brace
l_int|0x1036
comma
l_int|0x1037
)brace
comma
(brace
l_int|0x1039
comma
l_int|0x1039
)brace
comma
(brace
l_int|0x1058
comma
l_int|0x1059
)brace
comma
(brace
l_int|0x1160
comma
l_int|0x11FF
)brace
comma
(brace
l_int|0x1712
comma
l_int|0x1714
)brace
comma
(brace
l_int|0x1732
comma
l_int|0x1734
)brace
comma
(brace
l_int|0x1752
comma
l_int|0x1753
)brace
comma
(brace
l_int|0x1772
comma
l_int|0x1773
)brace
comma
(brace
l_int|0x17B4
comma
l_int|0x17B5
)brace
comma
(brace
l_int|0x17B7
comma
l_int|0x17BD
)brace
comma
(brace
l_int|0x17C6
comma
l_int|0x17C6
)brace
comma
(brace
l_int|0x17C9
comma
l_int|0x17D3
)brace
comma
(brace
l_int|0x17DD
comma
l_int|0x17DD
)brace
comma
(brace
l_int|0x180B
comma
l_int|0x180D
)brace
comma
(brace
l_int|0x18A9
comma
l_int|0x18A9
)brace
comma
(brace
l_int|0x1920
comma
l_int|0x1922
)brace
comma
(brace
l_int|0x1927
comma
l_int|0x1928
)brace
comma
(brace
l_int|0x1932
comma
l_int|0x1932
)brace
comma
(brace
l_int|0x1939
comma
l_int|0x193B
)brace
comma
(brace
l_int|0x200B
comma
l_int|0x200F
)brace
comma
(brace
l_int|0x202A
comma
l_int|0x202E
)brace
comma
(brace
l_int|0x2060
comma
l_int|0x2063
)brace
comma
(brace
l_int|0x206A
comma
l_int|0x206F
)brace
comma
(brace
l_int|0x20D0
comma
l_int|0x20EA
)brace
comma
(brace
l_int|0x302A
comma
l_int|0x302F
)brace
comma
(brace
l_int|0x3099
comma
l_int|0x309A
)brace
comma
(brace
l_int|0xFB1E
comma
l_int|0xFB1E
)brace
comma
(brace
l_int|0xFE00
comma
l_int|0xFE0F
)brace
comma
(brace
l_int|0xFE20
comma
l_int|0xFE23
)brace
comma
(brace
l_int|0xFEFF
comma
l_int|0xFEFF
)brace
comma
(brace
l_int|0xFFF9
comma
l_int|0xFFFB
)brace
comma
(brace
l_int|0x1D167
comma
l_int|0x1D169
)brace
comma
(brace
l_int|0x1D173
comma
l_int|0x1D182
)brace
comma
(brace
l_int|0x1D185
comma
l_int|0x1D18B
)brace
comma
(brace
l_int|0x1D1AA
comma
l_int|0x1D1AD
)brace
comma
(brace
l_int|0xE0001
comma
l_int|0xE0001
)brace
comma
(brace
l_int|0xE0020
comma
l_int|0xE007F
)brace
comma
(brace
l_int|0xE0100
comma
l_int|0xE01EF
)brace
)brace
suffix:semicolon
multiline_comment|/* test for 8-bit control characters */
r_if
c_cond
(paren
id|ch
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ch
OL
l_int|32
op_logical_or
(paren
id|ch
op_ge
l_int|0x7f
op_logical_and
id|ch
OL
l_int|0xa0
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* binary search in table of non-spacing characters */
r_if
c_cond
(paren
id|bisearch
c_func
(paren
id|ch
comma
id|combining
comma
r_sizeof
(paren
id|combining
)paren
op_div
r_sizeof
(paren
r_struct
id|interval
)paren
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If we arrive here, ch is neither a combining nor a C0/C1&n;&t; * control character.&n;&t; */
r_return
l_int|1
op_plus
(paren
id|ch
op_ge
l_int|0x1100
op_logical_and
multiline_comment|/* Hangul Jamo init. consonants */
(paren
id|ch
op_le
l_int|0x115f
op_logical_or
id|ch
op_eq
l_int|0x2329
op_logical_or
id|ch
op_eq
l_int|0x232a
op_logical_or
multiline_comment|/* CJK ... Yi */
(paren
id|ch
op_ge
l_int|0x2e80
op_logical_and
id|ch
op_le
l_int|0xa4cf
op_logical_and
id|ch
op_ne
l_int|0x303f
)paren
op_logical_or
multiline_comment|/* Hangul Syllables */
(paren
id|ch
op_ge
l_int|0xac00
op_logical_and
id|ch
op_le
l_int|0xd7a3
)paren
op_logical_or
multiline_comment|/* CJK Compatibility Ideographs */
(paren
id|ch
op_ge
l_int|0xf900
op_logical_and
id|ch
op_le
l_int|0xfaff
)paren
op_logical_or
multiline_comment|/* CJK Compatibility Forms */
(paren
id|ch
op_ge
l_int|0xfe30
op_logical_and
id|ch
op_le
l_int|0xfe6f
)paren
op_logical_or
multiline_comment|/* Fullwidth Forms */
(paren
id|ch
op_ge
l_int|0xff00
op_logical_and
id|ch
op_le
l_int|0xff60
)paren
op_logical_or
(paren
id|ch
op_ge
l_int|0xffe0
op_logical_and
id|ch
op_le
l_int|0xffe6
)paren
op_logical_or
(paren
id|ch
op_ge
l_int|0x20000
op_logical_and
id|ch
op_le
l_int|0x2fffd
)paren
op_logical_or
(paren
id|ch
op_ge
l_int|0x30000
op_logical_and
id|ch
op_le
l_int|0x3fffd
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pick one ucs character starting from the location *start points at,&n; * and return it, while updating the *start pointer to point at the&n; * end of that character.  When remainder_p is not NULL, the location&n; * holds the number of bytes remaining in the string that we are allowed&n; * to pick from.  Otherwise we are allowed to pick up to the NUL that&n; * would eventually appear in the string.  *remainder_p is also reduced&n; * by the number of bytes we have consumed.&n; *&n; * If the string was not a valid UTF-8, *start pointer is set to NULL&n; * and the return value is undefined.&n; */
DECL|function|pick_one_utf8_char
id|ucs_char_t
id|pick_one_utf8_char
c_func
(paren
r_const
r_char
op_star
op_star
id|start
comma
r_int
op_star
id|remainder_p
)paren
(brace
r_int
r_char
op_star
id|s
op_assign
(paren
r_int
r_char
op_star
)paren
op_star
id|start
suffix:semicolon
id|ucs_char_t
id|ch
suffix:semicolon
r_int
id|remainder
comma
id|incr
suffix:semicolon
multiline_comment|/*&n;&t; * A caller that assumes NUL terminated text can choose&n;&t; * not to bother with the remainder length.  We will&n;&t; * stop at the first NUL.&n;&t; */
id|remainder
op_assign
(paren
id|remainder_p
ques
c_cond
op_star
id|remainder_p
suffix:colon
l_int|999
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remainder
OL
l_int|1
)paren
(brace
r_goto
id|invalid
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|s
OL
l_int|0x80
)paren
(brace
multiline_comment|/* 0xxxxxxx */
id|ch
op_assign
op_star
id|s
suffix:semicolon
id|incr
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0xe0
)paren
op_eq
l_int|0xc0
)paren
(brace
multiline_comment|/* 110XXXXx 10xxxxxx */
r_if
c_cond
(paren
id|remainder
OL
l_int|2
op_logical_or
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0xc0
)paren
op_ne
l_int|0x80
op_logical_or
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0xfe
)paren
op_eq
l_int|0xc0
)paren
r_goto
id|invalid
suffix:semicolon
id|ch
op_assign
(paren
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0x1f
)paren
op_lshift
l_int|6
)paren
op_or
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|incr
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xe0
)paren
(brace
multiline_comment|/* 1110XXXX 10Xxxxxx 10xxxxxx */
r_if
c_cond
(paren
id|remainder
OL
l_int|3
op_logical_or
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0xc0
)paren
op_ne
l_int|0x80
op_logical_or
(paren
id|s
(braket
l_int|2
)braket
op_amp
l_int|0xc0
)paren
op_ne
l_int|0x80
op_logical_or
multiline_comment|/* overlong? */
(paren
id|s
(braket
l_int|0
)braket
op_eq
l_int|0xe0
op_logical_and
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0xe0
)paren
op_eq
l_int|0x80
)paren
op_logical_or
multiline_comment|/* surrogate? */
(paren
id|s
(braket
l_int|0
)braket
op_eq
l_int|0xed
op_logical_and
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0xe0
)paren
op_eq
l_int|0xa0
)paren
op_logical_or
multiline_comment|/* U+FFFE or U+FFFF? */
(paren
id|s
(braket
l_int|0
)braket
op_eq
l_int|0xef
op_logical_and
id|s
(braket
l_int|1
)braket
op_eq
l_int|0xbf
op_logical_and
(paren
id|s
(braket
l_int|2
)braket
op_amp
l_int|0xfe
)paren
op_eq
l_int|0xbe
)paren
)paren
r_goto
id|invalid
suffix:semicolon
id|ch
op_assign
(paren
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0x0f
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0x3f
)paren
op_lshift
l_int|6
)paren
op_or
(paren
id|s
(braket
l_int|2
)braket
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|incr
op_assign
l_int|3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0xf8
)paren
op_eq
l_int|0xf0
)paren
(brace
multiline_comment|/* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
r_if
c_cond
(paren
id|remainder
template_param
l_int|0xf4
)paren
r_goto
id|invalid
suffix:semicolon
id|ch
op_assign
(paren
(paren
id|s
(braket
l_int|0
)braket
op_amp
l_int|0x07
)paren
op_lshift
l_int|18
)paren
op_or
(paren
(paren
id|s
(braket
l_int|1
)braket
op_amp
l_int|0x3f
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|s
(braket
l_int|2
)braket
op_amp
l_int|0x3f
)paren
op_lshift
l_int|6
)paren
op_or
(paren
id|s
(braket
l_int|3
)braket
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|incr
op_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|invalid
suffix:colon
op_star
id|start
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_add_assign
id|incr
suffix:semicolon
r_if
c_cond
(paren
id|remainder_p
)paren
op_star
id|remainder_p
op_assign
id|remainder
id|incr
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
multiline_comment|/*&n; * This function returns the number of columns occupied by the character&n; * pointed to by the variable start. The pointer is updated to point at&n; * the next character. When remainder_p is not NULL, it points at the&n; * location that stores the number of remaining bytes we can use to pick&n; * a character (see pick_one_utf8_char() above).&n; */
DECL|function|utf8_width
r_int
id|utf8_width
c_func
(paren
r_const
r_char
op_star
op_star
id|start
comma
r_int
op_star
id|remainder_p
)paren
(brace
id|ucs_char_t
id|ch
op_assign
id|pick_one_utf8_char
c_func
(paren
id|start
comma
id|remainder_p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|start
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|git_wcwidth
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the total number of columns required by a null-terminated&n; * string, assuming that the string is utf8.  Returns strlen() instead&n; * if the string does not look like a valid utf8 string.&n; */
DECL|function|utf8_strwidth
r_int
id|utf8_strwidth
c_func
(paren
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|width
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|orig
op_assign
id|string
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|string
)paren
r_return
id|strlen
c_func
(paren
id|orig
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|string
)paren
r_return
id|width
suffix:semicolon
id|width
op_add_assign
id|utf8_width
c_func
(paren
op_amp
id|string
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
DECL|function|is_utf8
r_int
id|is_utf8
c_func
(paren
r_const
r_char
op_star
id|text
)paren
(brace
r_while
c_loop
(paren
op_star
id|text
)paren
(brace
r_if
c_cond
(paren
op_star
id|text
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
op_star
id|text
op_eq
l_char|&squot;&bslash;t&squot;
op_logical_or
op_star
id|text
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|text
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|utf8_width
c_func
(paren
op_amp
id|text
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|text
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|strbuf_addchars
r_static
r_void
id|strbuf_addchars
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_int
id|c
comma
r_int
id|n
)paren
(brace
id|strbuf_grow
c_func
(paren
id|sb
comma
id|n
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|c
comma
id|n
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|sb
comma
id|sb-&gt;len
op_plus
id|n
)paren
suffix:semicolon
)brace
DECL|function|strbuf_add_indented_text
r_static
r_void
id|strbuf_add_indented_text
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_const
r_char
op_star
id|text
comma
r_int
id|indent
comma
r_int
id|indent2
)paren
(brace
r_if
c_cond
(paren
id|indent
OL
l_int|0
)paren
id|indent
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|text
)paren
(brace
r_const
r_char
op_star
id|eol
op_assign
id|strchrnul
c_func
(paren
id|text
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|eol
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|eol
op_increment
suffix:semicolon
id|strbuf_addchars
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
comma
id|indent
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|text
comma
id|eol
id|text
)paren
suffix:semicolon
id|text
op_assign
id|eol
suffix:semicolon
id|indent
op_assign
id|indent2
suffix:semicolon
)brace
)brace
DECL|function|display_mode_esc_sequence_len
r_static
r_int
id|display_mode_esc_sequence_len
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|s
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_increment
op_ne
l_char|&squot;&bslash;033&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_increment
op_ne
l_char|&squot;[&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|isdigit
c_func
(paren
op_star
id|p
)paren
op_logical_or
op_star
id|p
op_eq
l_char|&squot;;&squot;
)paren
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_increment
op_ne
l_char|&squot;m&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|p
id|s
suffix:semicolon
)brace
multiline_comment|/*&n; * Wrap the text, if necessary. The variable indent is the indent for the&n; * first line, indent2 is the indent for all other lines.&n; * If indent is negative, assume that already -indent columns have been&n; * consumed (and no extra indent is necessary for the first line).&n; */
DECL|function|strbuf_add_wrapped_text
r_int
id|strbuf_add_wrapped_text
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_const
r_char
op_star
id|text
comma
r_int
id|indent1
comma
r_int
id|indent2
comma
r_int
id|width
)paren
(brace
r_int
id|indent
comma
id|w
comma
id|assume_utf8
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|bol
comma
op_star
id|space
comma
op_star
id|start
op_assign
id|text
suffix:semicolon
r_int
id|orig_len
op_assign
id|buf-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|width
op_le
l_int|0
)paren
(brace
id|strbuf_add_indented_text
c_func
(paren
id|buf
comma
id|text
comma
id|indent1
comma
id|indent2
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|retry
suffix:colon
id|bol
op_assign
id|text
suffix:semicolon
id|w
op_assign
id|indent
op_assign
id|indent1
suffix:semicolon
id|space
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|indent
OL
l_int|0
)paren
(brace
id|w
op_assign
id|indent
suffix:semicolon
id|space
op_assign
id|text
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
id|c
suffix:semicolon
r_int
id|skip
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skip
op_assign
id|display_mode_esc_sequence_len
c_func
(paren
id|text
)paren
)paren
)paren
id|text
op_add_assign
id|skip
suffix:semicolon
id|c
op_assign
op_star
id|text
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
id|isspace
c_func
(paren
id|c
)paren
)paren
(brace
r_if
c_cond
(paren
id|w
OL
id|width
op_logical_or
op_logical_neg
id|space
)paren
(brace
r_const
r_char
op_star
id|start
op_assign
id|bol
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_and
id|text
op_eq
id|start
)paren
r_return
id|w
suffix:semicolon
r_if
c_cond
(paren
id|space
)paren
id|start
op_assign
id|space
suffix:semicolon
r_else
id|strbuf_addchars
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
comma
id|indent
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|start
comma
id|text
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
id|w
suffix:semicolon
id|space
op_assign
id|text
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;t&squot;
)paren
id|w
op_or_assign
l_int|0x07
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|space
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|space
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|strbuf_addch
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_goto
id|new_line
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|isalnum
c_func
(paren
op_star
id|space
)paren
)paren
r_goto
id|new_line
suffix:semicolon
r_else
id|strbuf_addch
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|w
op_increment
suffix:semicolon
id|text
op_increment
suffix:semicolon
)brace
r_else
(brace
id|new_line
suffix:colon
id|strbuf_addch
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|text
op_assign
id|bol
op_assign
id|space
op_plus
id|isspace
c_func
(paren
op_star
id|space
)paren
suffix:semicolon
id|space
op_assign
l_int|NULL
suffix:semicolon
id|w
op_assign
id|indent
op_assign
id|indent2
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|assume_utf8
)paren
(brace
id|w
op_add_assign
id|utf8_width
c_func
(paren
op_amp
id|text
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|text
)paren
(brace
id|assume_utf8
op_assign
l_int|0
suffix:semicolon
id|text
op_assign
id|start
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|buf
comma
id|orig_len
)paren
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
)brace
r_else
(brace
id|w
op_increment
suffix:semicolon
id|text
op_increment
suffix:semicolon
)brace
)brace
)brace
DECL|function|is_encoding_utf8
r_int
id|is_encoding_utf8
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|name
comma
l_string|&quot;utf-8&quot;
)paren
op_logical_or
op_logical_neg
id|strcasecmp
c_func
(paren
id|name
comma
l_string|&quot;utf8&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a buffer and its encoding, return it re-encoded&n; * with iconv.  If the conversion fails, returns NULL.&n; */
macro_line|#ifndef NO_ICONV
macro_line|#if defined(OLD_ICONV) || (defined(__sun__) &amp;&amp; !defined(_XPG6))
DECL|typedef|iconv_ibp
r_typedef
r_const
r_char
op_star
id|iconv_ibp
suffix:semicolon
macro_line|#else
DECL|typedef|iconv_ibp
r_typedef
r_char
op_star
id|iconv_ibp
suffix:semicolon
macro_line|#endif
DECL|function|reencode_string
r_char
op_star
id|reencode_string
c_func
(paren
r_const
r_char
op_star
id|in
comma
r_const
r_char
op_star
id|out_encoding
comma
r_const
r_char
op_star
id|in_encoding
)paren
(brace
id|iconv_t
id|conv
suffix:semicolon
r_int
id|insz
comma
id|outsz
comma
id|outalloc
suffix:semicolon
r_char
op_star
id|out
comma
op_star
id|outpos
suffix:semicolon
id|iconv_ibp
id|cp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_encoding
)paren
r_return
l_int|NULL
suffix:semicolon
id|conv
op_assign
id|iconv_open
c_func
(paren
id|out_encoding
comma
id|in_encoding
)paren
suffix:semicolon
r_if
c_cond
(paren
id|conv
op_eq
(paren
id|iconv_t
)paren
l_int|1
)paren
r_return
l_int|NULL
suffix:semicolon
id|insz
op_assign
id|strlen
c_func
(paren
id|in
)paren
suffix:semicolon
id|outsz
op_assign
id|insz
suffix:semicolon
id|outalloc
op_assign
id|outsz
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* for terminating NUL */
id|out
op_assign
id|xmalloc
c_func
(paren
id|outalloc
)paren
suffix:semicolon
id|outpos
op_assign
id|out
suffix:semicolon
id|cp
op_assign
(paren
id|iconv_ibp
)paren
id|in
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|cnt
op_assign
id|iconv
c_func
(paren
id|conv
comma
op_amp
id|cp
comma
op_amp
id|insz
comma
op_amp
id|outpos
comma
op_amp
id|outsz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
l_int|1
)paren
(brace
r_int
id|sofar
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_ne
id|E2BIG
)paren
(brace
id|free
c_func
(paren
id|out
)paren
suffix:semicolon
id|iconv_close
c_func
(paren
id|conv
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* insz has remaining number of bytes.&n;&t;&t;&t; * since we started outsz the same as insz,&n;&t;&t;&t; * it is likely that insz is not enough for&n;&t;&t;&t; * converting the rest.&n;&t;&t;&t; */
id|sofar
op_assign
id|outpos
id|out
suffix:semicolon
id|outalloc
op_assign
id|sofar
op_plus
id|insz
op_star
l_int|2
op_plus
l_int|32
suffix:semicolon
id|out
op_assign
id|xrealloc
c_func
(paren
id|out
comma
id|outalloc
)paren
suffix:semicolon
id|outpos
op_assign
id|out
op_plus
id|sofar
suffix:semicolon
id|outsz
op_assign
id|outalloc
id|sofar
l_int|1
suffix:semicolon
)brace
r_else
(brace
op_star
id|outpos
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|iconv_close
c_func
(paren
id|conv
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
macro_line|#endif
eof
