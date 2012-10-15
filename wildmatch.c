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
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE 1
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
id|force_lower_case
)paren
(brace
id|uchar
id|p_ch
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
id|special
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
id|ABORT_ALL
suffix:semicolon
r_if
c_cond
(paren
id|force_lower_case
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
id|force_lower_case
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
id|NOMATCH
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
id|t_ch
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|NOMATCH
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
(paren
id|prev_p
op_eq
id|text
op_logical_or
op_star
id|prev_p
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
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
id|special
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
r_return
id|ABORT_MALFORMED
suffix:semicolon
)brace
r_else
id|special
op_assign
id|FALSE
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
id|special
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
id|NOMATCH
suffix:semicolon
)brace
r_return
id|MATCH
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
id|force_lower_case
)paren
)paren
op_ne
id|NOMATCH
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|special
op_logical_or
id|matched
op_ne
id|ABORT_TO_STARSTAR
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
id|special
op_logical_and
id|t_ch
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|ABORT_TO_STARSTAR
suffix:semicolon
id|t_ch
op_assign
op_star
op_increment
id|text
suffix:semicolon
)brace
r_return
id|ABORT_ALL
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
multiline_comment|/* Assign literal TRUE/FALSE because of &quot;matched&quot; comparison. */
id|special
op_assign
id|p_ch
op_eq
id|NEGATE_CLASS
ques
c_cond
id|TRUE
suffix:colon
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
id|special
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
id|FALSE
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
id|ABORT_ALL
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
id|ABORT_ALL
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
id|TRUE
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
id|ABORT_ALL
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
id|TRUE
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
id|ABORT_ALL
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
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
id|TRUE
suffix:semicolon
)brace
r_else
multiline_comment|/* malformed [:class:] string */
r_return
id|ABORT_ALL
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
id|TRUE
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
id|special
op_logical_or
id|t_ch
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|NOMATCH
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
id|NOMATCH
suffix:colon
id|MATCH
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
id|flags
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
op_amp
id|FNM_CASEFOLD
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
eof
