macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;levenshtein.h&quot;
multiline_comment|/*&n; * This function implements the Damerau-Levenshtein algorithm to&n; * calculate a distance between strings.&n; *&n; * Basically, it says how many letters need to be swapped, substituted,&n; * deleted from, or added to string1, at least, to get string2.&n; *&n; * The idea is to build a distance matrix for the substrings of both&n; * strings.  To avoid a large space complexity, only the last three rows&n; * are kept in memory (if swaps had the same or higher cost as one deletion&n; * plus one insertion, only two rows would be needed).&n; *&n; * At any stage, &quot;i + 1&quot; denotes the length of the current substring of&n; * string1 that the distance is calculated for.&n; *&n; * row2 holds the current row, row1 the previous row (i.e. for the substring&n; * of string1 of length &quot;i&quot;), and row0 the row before that.&n; *&n; * In other words, at the start of the big loop, row2[j + 1] contains the&n; * Damerau-Levenshtein distance between the substring of string1 of length&n; * &quot;i&quot; and the substring of string2 of length &quot;j + 1&quot;.&n; *&n; * All the big loop does is determine the partial minimum-cost paths.&n; *&n; * It does so by calculating the costs of the path ending in characters&n; * i (in string1) and j (in string2), respectively, given that the last&n; * operation is a substition, a swap, a deletion, or an insertion.&n; *&n; * This implementation allows the costs to be weighted:&n; *&n; * - w (as in &quot;sWap&quot;)&n; * - s (as in &quot;Substitution&quot;)&n; * - a (for insertion, AKA &quot;Add&quot;)&n; * - d (as in &quot;Deletion&quot;)&n; *&n; * Note that this algorithm calculates a distance _iff_ d == a.&n; */
DECL|function|levenshtein
r_int
id|levenshtein
c_func
(paren
r_const
r_char
op_star
id|string1
comma
r_const
r_char
op_star
id|string2
comma
r_int
id|w
comma
r_int
id|s
comma
r_int
id|a
comma
r_int
id|d
)paren
(brace
r_int
id|len1
op_assign
id|strlen
c_func
(paren
id|string1
)paren
comma
id|len2
op_assign
id|strlen
c_func
(paren
id|string2
)paren
suffix:semicolon
r_int
op_star
id|row0
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
(paren
id|len2
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_int
op_star
id|row1
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
(paren
id|len2
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_int
op_star
id|row2
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
(paren
id|len2
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
op_le
id|len2
suffix:semicolon
id|j
op_increment
)paren
id|row1
(braket
id|j
)braket
op_assign
id|j
op_star
id|a
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
id|len1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
op_star
id|dummy
suffix:semicolon
id|row2
(braket
l_int|0
)braket
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_star
id|d
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|len2
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* substitution */
id|row2
(braket
id|j
op_plus
l_int|1
)braket
op_assign
id|row1
(braket
id|j
)braket
op_plus
id|s
op_star
(paren
id|string1
(braket
id|i
)braket
op_ne
id|string2
(braket
id|j
)braket
)paren
suffix:semicolon
multiline_comment|/* swap */
r_if
c_cond
(paren
id|i
OG
l_int|0
op_logical_and
id|j
OG
l_int|0
op_logical_and
id|string1
(braket
id|i
l_int|1
)braket
op_eq
id|string2
(braket
id|j
)braket
op_logical_and
id|string1
(braket
id|i
)braket
op_eq
id|string2
(braket
id|j
l_int|1
)braket
op_logical_and
id|row2
(braket
id|j
op_plus
l_int|1
)braket
OG
id|row0
(braket
id|j
l_int|1
)braket
op_plus
id|w
)paren
id|row2
(braket
id|j
op_plus
l_int|1
)braket
op_assign
id|row0
(braket
id|j
l_int|1
)braket
op_plus
id|w
suffix:semicolon
multiline_comment|/* deletion */
r_if
c_cond
(paren
id|row2
(braket
id|j
op_plus
l_int|1
)braket
OG
id|row1
(braket
id|j
op_plus
l_int|1
)braket
op_plus
id|d
)paren
id|row2
(braket
id|j
op_plus
l_int|1
)braket
op_assign
id|row1
(braket
id|j
op_plus
l_int|1
)braket
op_plus
id|d
suffix:semicolon
multiline_comment|/* insertion */
r_if
c_cond
(paren
id|row2
(braket
id|j
op_plus
l_int|1
)braket
OG
id|row2
(braket
id|j
)braket
op_plus
id|a
)paren
id|row2
(braket
id|j
op_plus
l_int|1
)braket
op_assign
id|row2
(braket
id|j
)braket
op_plus
id|a
suffix:semicolon
)brace
id|dummy
op_assign
id|row0
suffix:semicolon
id|row0
op_assign
id|row1
suffix:semicolon
id|row1
op_assign
id|row2
suffix:semicolon
id|row2
op_assign
id|dummy
suffix:semicolon
)brace
id|i
op_assign
id|row1
(braket
id|len2
)braket
suffix:semicolon
id|free
c_func
(paren
id|row0
)paren
suffix:semicolon
id|free
c_func
(paren
id|row1
)paren
suffix:semicolon
id|free
c_func
(paren
id|row2
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
