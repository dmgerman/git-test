multiline_comment|/*&n;**  Do shell-style pattern matching for ?, &bslash;, [], and * characters.&n;**  It is 8bit clean.&n;**&n;**  Written by Rich $alz, mirror!rs, Wed Nov 26 19:03:17 EST 1986.&n;**  Rich $alz is now &lt;rsalz@bbn.com&gt;.&n;**&n;**  Modified by Wayne Davison to special-case &squot;/&squot; matching, to make &squot;**&squot;&n;**  work differently than &squot;*&squot;, and to fix the character-class code.&n;*/
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;wildmatch.h&quot;
DECL|typedef|uchar
r_typedef
r_int
r_char
id|uchar
suffix:semicolon
multiline_comment|/* What character marks an inverted character class? */
DECL|macro|NEGATE_CLASS
mdefine_line|#define NEGATE_CLASS&t;&squot;!&squot;
DECL|macro|NEGATE_CLASS2
mdefine_line|#define NEGATE_CLASS2&t;&squot;^&squot;
DECL|macro|CC_EQ
mdefine_line|#define CC_EQ(class, len, litmatch) ((len) == sizeof (litmatch)-1 &bslash;&n;&t;&t;&t;&t;    &amp;&amp; *(class) == *(litmatch) &bslash;&n;&t;&t;&t;&t;    &amp;&amp; strncmp((char*)class, litmatch, len) == 0)
macro_line|#if defined STDC_HEADERS || !defined isascii
DECL|macro|ISASCII
macro_line|# define ISASCII(c) 1
macro_line|#else
DECL|macro|ISASCII
macro_line|# define ISASCII(c) isascii(c)
macro_line|#endif
macro_line|#ifdef isblank
DECL|macro|ISBLANK
macro_line|# define ISBLANK(c) (ISASCII(c) &amp;&amp; isblank(c))
macro_line|#else
DECL|macro|ISBLANK
macro_line|# define ISBLANK(c) ((c) == &squot; &squot; || (c) == &squot;&bslash;t&squot;)
macro_line|#endif
macro_line|#ifdef isgraph
DECL|macro|ISGRAPH
macro_line|# define ISGRAPH(c) (ISASCII(c) &amp;&amp; isgraph(c))
macro_line|#else
DECL|macro|ISGRAPH
macro_line|# define ISGRAPH(c) (ISASCII(c) &amp;&amp; isprint(c) &amp;&amp; !isspace(c))
macro_line|#endif
DECL|macro|ISPRINT
mdefine_line|#define ISPRINT(c) (ISASCII(c) &amp;&amp; isprint(c))
DECL|macro|ISDIGIT
mdefine_line|#define ISDIGIT(c) (ISASCII(c) &amp;&amp; isdigit(c))
DECL|macro|ISALNUM
mdefine_line|#define ISALNUM(c) (ISASCII(c) &amp;&amp; isalnum(c))
DECL|macro|ISALPHA
mdefine_line|#define ISALPHA(c) (ISASCII(c) &amp;&amp; isalpha(c))
DECL|macro|ISCNTRL
mdefine_line|#define ISCNTRL(c) (ISASCII(c) &amp;&amp; iscntrl(c))
DECL|macro|ISLOWER
mdefine_line|#define ISLOWER(c) (ISASCII(c) &amp;&amp; islower(c))
DECL|macro|ISPUNCT
mdefine_line|#define ISPUNCT(c) (ISASCII(c) &amp;&amp; ispunct(c))
DECL|macro|ISSPACE
mdefine_line|#define ISSPACE(c) (ISASCII(c) &amp;&amp; isspace(c))
DECL|macro|ISUPPER
mdefine_line|#define ISUPPER(c) (ISASCII(c) &amp;&amp; isupper(c))
DECL|macro|ISXDIGIT
mdefine_line|#define ISXDIGIT(c) (ISASCII(c) &amp;&amp; isxdigit(c))
multiline_comment|/* Match pattern &quot;p&quot; against &quot;text&quot; */
DECL|function|dowild
r_static
r_int
id|dowild
c_func
(paren
r_const
id|uchar
op_star
id|p
comma
r_const
id|uchar
op_star
id|text
comma
r_int
r_int
id|flags
)paren
(brace
id|uchar
id|p_ch
suffix:semicolon
r_const
id|uchar
op_star
id|pattern
op_assign
id|p
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|p_ch
op_assign
op_star
id|p
)paren
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|text
op_increment
comma
id|p
op_increment
)paren
(brace
r_int
id|matched
comma
id|match_slash
comma
id|negated
suffix:semicolon
id|uchar
id|t_ch
comma
id|prev_ch
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t_ch
op_assign
op_star
id|text
)paren
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_and
id|p_ch
op_ne
l_char|&squot;*&squot;
)paren
r_return
id|WM_ABORT_ALL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_CASEFOLD
)paren
op_logical_and
id|ISUPPER
c_func
(paren
id|t_ch
)paren
)paren
id|t_ch
op_assign
id|tolower
c_func
(paren
id|t_ch
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_CASEFOLD
)paren
op_logical_and
id|ISUPPER
c_func
(paren
id|p_ch
)paren
)paren
id|p_ch
op_assign
id|tolower
c_func
(paren
id|p_ch
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|p_ch
)paren
(brace
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
multiline_comment|/* Literal match with following character.  Note that the test&n;&t;&t;&t; * in &quot;default&quot; handles the p[1] == &squot;&bslash;0&squot; failure case. */
id|p_ch
op_assign
op_star
op_increment
id|p
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|t_ch
op_ne
id|p_ch
)paren
r_return
id|WM_NOMATCH
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;?&squot;
suffix:colon
multiline_comment|/* Match anything but &squot;/&squot;. */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_PATHNAME
)paren
op_logical_and
id|t_ch
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|WM_NOMATCH
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;*&squot;
suffix:colon
r_if
c_cond
(paren
op_star
op_increment
id|p
op_eq
l_char|&squot;*&squot;
)paren
(brace
r_const
id|uchar
op_star
id|prev_p
op_assign
id|p
l_int|2
suffix:semicolon
r_while
c_loop
(paren
op_star
op_increment
id|p
op_eq
l_char|&squot;*&squot;
)paren
(brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|WM_PATHNAME
)paren
)paren
multiline_comment|/* without WM_PATHNAME, &squot;*&squot; == &squot;**&squot; */
id|match_slash
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|prev_p
OL
id|pattern
op_logical_or
op_star
id|prev_p
op_eq
l_char|&squot;/&squot;
)paren
op_logical_and
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|p
op_eq
l_char|&squot;/&squot;
op_logical_or
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Assuming we already match &squot;foo/&squot; and are at&n;&t;&t;&t;&t;&t; * &lt;star star slash&gt;, just assume it matches&n;&t;&t;&t;&t;&t; * nothing and go ahead match the rest of the&n;&t;&t;&t;&t;&t; * pattern with the remaining string. This&n;&t;&t;&t;&t;&t; * helps make foo/&lt;*&gt;&lt;*&gt;/bar (&lt;&gt; because&n;&t;&t;&t;&t;&t; * otherwise it breaks C comment syntax) match&n;&t;&t;&t;&t;&t; * both foo/bar and foo/a/bar.&n;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
id|dowild
c_func
(paren
id|p
op_plus
l_int|1
comma
id|text
comma
id|flags
)paren
op_eq
id|WM_MATCH
)paren
r_return
id|WM_MATCH
suffix:semicolon
id|match_slash
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_return
id|WM_ABORT_MALFORMED
suffix:semicolon
)brace
r_else
multiline_comment|/* without WM_PATHNAME, &squot;*&squot; == &squot;**&squot; */
id|match_slash
op_assign
id|flags
op_amp
id|WM_PATHNAME
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
multiline_comment|/* Trailing &quot;**&quot; matches everything.  Trailing &quot;*&quot; matches&n;&t;&t;&t;&t; * only if there are no more slash characters. */
r_if
c_cond
(paren
op_logical_neg
id|match_slash
)paren
(brace
r_if
c_cond
(paren
id|strchr
c_func
(paren
(paren
r_char
op_star
)paren
id|text
comma
l_char|&squot;/&squot;
)paren
op_ne
l_int|NULL
)paren
r_return
id|WM_NOMATCH
suffix:semicolon
)brace
r_return
id|WM_MATCH
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|match_slash
op_logical_and
op_star
id|p
op_eq
l_char|&squot;/&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * _one_ asterisk followed by a slash&n;&t;&t;&t;&t; * with WM_PATHNAME matches the next&n;&t;&t;&t;&t; * directory&n;&t;&t;&t;&t; */
r_const
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
(paren
r_char
op_star
)paren
id|text
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slash
)paren
r_return
id|WM_NOMATCH
suffix:semicolon
id|text
op_assign
(paren
r_const
id|uchar
op_star
)paren
id|slash
suffix:semicolon
multiline_comment|/* the slash is consumed by the top-level for loop */
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|t_ch
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Try to advance faster when an asterisk is&n;&t;&t;&t;&t; * followed by a literal. We know in this case&n;&t;&t;&t;&t; * that the the string before the literal&n;&t;&t;&t;&t; * must belong to &quot;*&quot;.&n;&t;&t;&t;&t; * If match_slash is false, do not look past&n;&t;&t;&t;&t; * the first slash as it cannot belong to &squot;*&squot;.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|is_glob_special
c_func
(paren
op_star
id|p
)paren
)paren
(brace
id|p_ch
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_CASEFOLD
)paren
op_logical_and
id|ISUPPER
c_func
(paren
id|p_ch
)paren
)paren
id|p_ch
op_assign
id|tolower
c_func
(paren
id|p_ch
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|t_ch
op_assign
op_star
id|text
)paren
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
(paren
id|match_slash
op_logical_or
id|t_ch
op_ne
l_char|&squot;/&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_CASEFOLD
)paren
op_logical_and
id|ISUPPER
c_func
(paren
id|t_ch
)paren
)paren
id|t_ch
op_assign
id|tolower
c_func
(paren
id|t_ch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t_ch
op_eq
id|p_ch
)paren
r_break
suffix:semicolon
id|text
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t_ch
op_ne
id|p_ch
)paren
r_return
id|WM_NOMATCH
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|matched
op_assign
id|dowild
c_func
(paren
id|p
comma
id|text
comma
id|flags
)paren
)paren
op_ne
id|WM_NOMATCH
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|match_slash
op_logical_or
id|matched
op_ne
id|WM_ABORT_TO_STARSTAR
)paren
r_return
id|matched
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|match_slash
op_logical_and
id|t_ch
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|WM_ABORT_TO_STARSTAR
suffix:semicolon
id|t_ch
op_assign
op_star
op_increment
id|text
suffix:semicolon
)brace
r_return
id|WM_ABORT_ALL
suffix:semicolon
r_case
l_char|&squot;[&squot;
suffix:colon
id|p_ch
op_assign
op_star
op_increment
id|p
suffix:semicolon
macro_line|#ifdef NEGATE_CLASS2
r_if
c_cond
(paren
id|p_ch
op_eq
id|NEGATE_CLASS2
)paren
id|p_ch
op_assign
id|NEGATE_CLASS
suffix:semicolon
macro_line|#endif
multiline_comment|/* Assign literal 1/0 because of &quot;matched&quot; comparison. */
id|negated
op_assign
id|p_ch
op_eq
id|NEGATE_CLASS
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|negated
)paren
(brace
multiline_comment|/* Inverted character class. */
id|p_ch
op_assign
op_star
op_increment
id|p
suffix:semicolon
)brace
id|prev_ch
op_assign
l_int|0
suffix:semicolon
id|matched
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|p_ch
)paren
r_return
id|WM_ABORT_ALL
suffix:semicolon
r_if
c_cond
(paren
id|p_ch
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
id|p_ch
op_assign
op_star
op_increment
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p_ch
)paren
r_return
id|WM_ABORT_ALL
suffix:semicolon
r_if
c_cond
(paren
id|t_ch
op_eq
id|p_ch
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p_ch
op_eq
l_char|&squot;-&squot;
op_logical_and
id|prev_ch
op_logical_and
id|p
(braket
l_int|1
)braket
op_logical_and
id|p
(braket
l_int|1
)braket
op_ne
l_char|&squot;]&squot;
)paren
(brace
id|p_ch
op_assign
op_star
op_increment
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p_ch
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
id|p_ch
op_assign
op_star
op_increment
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p_ch
)paren
r_return
id|WM_ABORT_ALL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t_ch
op_le
id|p_ch
op_logical_and
id|t_ch
op_ge
id|prev_ch
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_CASEFOLD
)paren
op_logical_and
id|ISLOWER
c_func
(paren
id|t_ch
)paren
)paren
(brace
id|uchar
id|t_ch_upper
op_assign
id|toupper
c_func
(paren
id|t_ch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t_ch_upper
op_le
id|p_ch
op_logical_and
id|t_ch_upper
op_ge
id|prev_ch
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
id|p_ch
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This makes &quot;prev_ch&quot; get set to 0. */
)brace
r_else
r_if
c_cond
(paren
id|p_ch
op_eq
l_char|&squot;[&squot;
op_logical_and
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_const
id|uchar
op_star
id|s
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|p
op_add_assign
l_int|2
suffix:semicolon
(paren
id|p_ch
op_assign
op_star
id|p
)paren
op_logical_and
id|p_ch
op_ne
l_char|&squot;]&squot;
suffix:semicolon
id|p
op_increment
)paren
(brace
)brace
multiline_comment|/*SHARED ITERATOR*/
r_if
c_cond
(paren
op_logical_neg
id|p_ch
)paren
r_return
id|WM_ABORT_ALL
suffix:semicolon
id|i
op_assign
id|p
id|s
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_or
id|p
(braket
l_int|1
)braket
op_ne
l_char|&squot;:&squot;
)paren
(brace
multiline_comment|/* Didn&squot;t find &quot;:]&quot;, so treat like a normal set. */
id|p
op_assign
id|s
l_int|2
suffix:semicolon
id|p_ch
op_assign
l_char|&squot;[&squot;
suffix:semicolon
r_if
c_cond
(paren
id|t_ch
op_eq
id|p_ch
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;alnum&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISALNUM
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;alpha&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISALPHA
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;blank&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISBLANK
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;cntrl&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISCNTRL
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;digit&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISDIGIT
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;graph&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISGRAPH
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;lower&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISLOWER
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;print&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISPRINT
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;punct&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISPUNCT
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;space&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISSPACE
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;upper&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISUPPER
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|WM_CASEFOLD
)paren
op_logical_and
id|ISLOWER
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CC_EQ
c_func
(paren
id|s
comma
id|i
comma
l_string|&quot;xdigit&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|ISXDIGIT
c_func
(paren
id|t_ch
)paren
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_else
multiline_comment|/* malformed [:class:] string */
r_return
id|WM_ABORT_ALL
suffix:semicolon
id|p_ch
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This makes &quot;prev_ch&quot; get set to 0. */
)brace
r_else
r_if
c_cond
(paren
id|t_ch
op_eq
id|p_ch
)paren
id|matched
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|prev_ch
op_assign
id|p_ch
comma
(paren
id|p_ch
op_assign
op_star
op_increment
id|p
)paren
op_ne
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|matched
op_eq
id|negated
op_logical_or
(paren
(paren
id|flags
op_amp
id|WM_PATHNAME
)paren
op_logical_and
id|t_ch
op_eq
l_char|&squot;/&squot;
)paren
)paren
r_return
id|WM_NOMATCH
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_return
op_star
id|text
ques
c_cond
id|WM_NOMATCH
suffix:colon
id|WM_MATCH
suffix:semicolon
)brace
multiline_comment|/* Match the &quot;pattern&quot; against the &quot;text&quot; string. */
DECL|function|wildmatch
r_int
id|wildmatch
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_const
r_char
op_star
id|text
comma
r_int
r_int
id|flags
comma
r_struct
id|wildopts
op_star
id|wo
)paren
(brace
r_return
id|dowild
c_func
(paren
(paren
r_const
id|uchar
op_star
)paren
id|pattern
comma
(paren
r_const
id|uchar
op_star
)paren
id|text
comma
id|flags
)paren
suffix:semicolon
)brace
eof
