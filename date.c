multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|function|my_mktime
r_static
id|time_t
id|my_mktime
c_func
(paren
r_struct
id|tm
op_star
id|tm
)paren
(brace
r_static
r_const
r_int
id|mdays
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
)brace
suffix:semicolon
r_int
id|year
op_assign
id|tm-&gt;tm_year
l_int|70
suffix:semicolon
r_int
id|month
op_assign
id|tm-&gt;tm_mon
suffix:semicolon
r_int
id|day
op_assign
id|tm-&gt;tm_mday
suffix:semicolon
r_if
c_cond
(paren
id|year
template_param
l_int|129
)paren
multiline_comment|/* algo only works for 1970-2099 */
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|month
template_param
l_int|11
)paren
multiline_comment|/* array bounds */
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|month
OL
l_int|2
op_logical_or
(paren
id|year
op_plus
l_int|2
)paren
op_mod
l_int|4
)paren
id|day
op_decrement
suffix:semicolon
r_return
(paren
id|year
op_star
l_int|365
op_plus
(paren
id|year
op_plus
l_int|1
)paren
op_div
l_int|4
op_plus
id|mdays
(braket
id|month
)braket
op_plus
id|day
)paren
op_star
l_int|24
op_star
l_int|60
op_star
l_int|60UL
op_plus
id|tm-&gt;tm_hour
op_star
l_int|60
op_star
l_int|60
op_plus
id|tm-&gt;tm_min
op_star
l_int|60
op_plus
id|tm-&gt;tm_sec
suffix:semicolon
)brace
DECL|variable|month_names
r_static
r_const
r_char
op_star
id|month_names
(braket
)braket
op_assign
(brace
l_string|&quot;January&quot;
comma
l_string|&quot;February&quot;
comma
l_string|&quot;March&quot;
comma
l_string|&quot;April&quot;
comma
l_string|&quot;May&quot;
comma
l_string|&quot;June&quot;
comma
l_string|&quot;July&quot;
comma
l_string|&quot;August&quot;
comma
l_string|&quot;September&quot;
comma
l_string|&quot;October&quot;
comma
l_string|&quot;November&quot;
comma
l_string|&quot;December&quot;
)brace
suffix:semicolon
DECL|variable|weekday_names
r_static
r_const
r_char
op_star
id|weekday_names
(braket
)braket
op_assign
(brace
l_string|&quot;Sundays&quot;
comma
l_string|&quot;Mondays&quot;
comma
l_string|&quot;Tuesdays&quot;
comma
l_string|&quot;Wednesdays&quot;
comma
l_string|&quot;Thursdays&quot;
comma
l_string|&quot;Fridays&quot;
comma
l_string|&quot;Saturdays&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * The &quot;tz&quot; thing is passed in as this strange &quot;decimal parse of tz&quot;&n; * thing, which means that tz -0100 is passed in as the integer -100,&n; * even though it means &quot;sixty minutes off&quot;&n; */
DECL|function|show_date
r_const
r_char
op_star
id|show_date
c_func
(paren
r_int
r_int
id|time
comma
r_int
id|tz
)paren
(brace
r_struct
id|tm
op_star
id|tm
suffix:semicolon
id|time_t
id|t
suffix:semicolon
r_static
r_char
id|timebuf
(braket
l_int|200
)braket
suffix:semicolon
r_int
id|minutes
suffix:semicolon
id|minutes
op_assign
id|tz
OL
l_int|0
ques
c_cond
id|tz
suffix:colon
id|tz
suffix:semicolon
id|minutes
op_assign
(paren
id|minutes
op_div
l_int|100
)paren
op_star
l_int|60
op_plus
(paren
id|minutes
op_mod
l_int|100
)paren
suffix:semicolon
id|minutes
op_assign
id|tz
OL
l_int|0
ques
c_cond
id|minutes
suffix:colon
id|minutes
suffix:semicolon
id|t
op_assign
id|time
op_plus
id|minutes
op_star
l_int|60
suffix:semicolon
id|tm
op_assign
id|gmtime
c_func
(paren
op_amp
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tm
)paren
r_return
l_int|NULL
suffix:semicolon
id|sprintf
c_func
(paren
id|timebuf
comma
l_string|&quot;%.3s %.3s %d %02d:%02d:%02d %d %+05d&quot;
comma
id|weekday_names
(braket
id|tm-&gt;tm_wday
)braket
comma
id|month_names
(braket
id|tm-&gt;tm_mon
)braket
comma
id|tm-&gt;tm_mday
comma
id|tm-&gt;tm_hour
comma
id|tm-&gt;tm_min
comma
id|tm-&gt;tm_sec
comma
id|tm-&gt;tm_year
op_plus
l_int|1900
comma
id|tz
)paren
suffix:semicolon
r_return
id|timebuf
suffix:semicolon
)brace
multiline_comment|/*&n; * Check these. And note how it doesn&squot;t do the summer-time conversion.&n; *&n; * In my world, it&squot;s always summer, and things are probably a bit off&n; * in other ways too.&n; */
r_static
r_const
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|dst
r_int
id|dst
suffix:semicolon
DECL|variable|timezone_names
)brace
id|timezone_names
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;IDLW&quot;
comma
l_int|12
comma
l_int|0
comma
)brace
comma
multiline_comment|/* International Date Line West */
(brace
l_string|&quot;NT&quot;
comma
l_int|11
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Nome */
(brace
l_string|&quot;CAT&quot;
comma
l_int|10
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Central Alaska */
(brace
l_string|&quot;HST&quot;
comma
l_int|10
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Hawaii Standard */
(brace
l_string|&quot;HDT&quot;
comma
l_int|10
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Hawaii Daylight */
(brace
l_string|&quot;YST&quot;
comma
l_int|9
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Yukon Standard */
(brace
l_string|&quot;YDT&quot;
comma
l_int|9
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Yukon Daylight */
(brace
l_string|&quot;PST&quot;
comma
l_int|8
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Pacific Standard */
(brace
l_string|&quot;PDT&quot;
comma
l_int|8
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Pacific Daylight */
(brace
l_string|&quot;MST&quot;
comma
l_int|7
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Mountain Standard */
(brace
l_string|&quot;MDT&quot;
comma
l_int|7
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Mountain Daylight */
(brace
l_string|&quot;CST&quot;
comma
l_int|6
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Central Standard */
(brace
l_string|&quot;CDT&quot;
comma
l_int|6
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Central Daylight */
(brace
l_string|&quot;EST&quot;
comma
l_int|5
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Eastern Standard */
(brace
l_string|&quot;EDT&quot;
comma
l_int|5
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Eastern Daylight */
(brace
l_string|&quot;AST&quot;
comma
l_int|3
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Atlantic Standard */
(brace
l_string|&quot;ADT&quot;
comma
l_int|3
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Atlantic Daylight */
(brace
l_string|&quot;WAT&quot;
comma
l_int|1
comma
l_int|0
comma
)brace
comma
multiline_comment|/* West Africa */
(brace
l_string|&quot;GMT&quot;
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Greenwich Mean */
(brace
l_string|&quot;UTC&quot;
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Universal (Coordinated) */
(brace
l_string|&quot;WET&quot;
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Western European */
(brace
l_string|&quot;BST&quot;
comma
l_int|0
comma
l_int|1
comma
)brace
comma
multiline_comment|/* British Summer */
(brace
l_string|&quot;CET&quot;
comma
op_plus
l_int|1
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Central European */
(brace
l_string|&quot;MET&quot;
comma
op_plus
l_int|1
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Middle European */
(brace
l_string|&quot;MEWT&quot;
comma
op_plus
l_int|1
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Middle European Winter */
(brace
l_string|&quot;MEST&quot;
comma
op_plus
l_int|1
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Middle European Summer */
(brace
l_string|&quot;CEST&quot;
comma
op_plus
l_int|1
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Central European Summer */
(brace
l_string|&quot;MESZ&quot;
comma
op_plus
l_int|1
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Middle European Summer */
(brace
l_string|&quot;FWT&quot;
comma
op_plus
l_int|1
comma
l_int|0
comma
)brace
comma
multiline_comment|/* French Winter */
(brace
l_string|&quot;FST&quot;
comma
op_plus
l_int|1
comma
l_int|1
comma
)brace
comma
multiline_comment|/* French Summer */
(brace
l_string|&quot;EET&quot;
comma
op_plus
l_int|2
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Eastern Europe, USSR Zone 1 */
(brace
l_string|&quot;EEST&quot;
comma
op_plus
l_int|2
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Eastern European Daylight */
(brace
l_string|&quot;WAST&quot;
comma
op_plus
l_int|7
comma
l_int|0
comma
)brace
comma
multiline_comment|/* West Australian Standard */
(brace
l_string|&quot;WADT&quot;
comma
op_plus
l_int|7
comma
l_int|1
comma
)brace
comma
multiline_comment|/* West Australian Daylight */
(brace
l_string|&quot;CCT&quot;
comma
op_plus
l_int|8
comma
l_int|0
comma
)brace
comma
multiline_comment|/* China Coast, USSR Zone 7 */
(brace
l_string|&quot;JST&quot;
comma
op_plus
l_int|9
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Japan Standard, USSR Zone 8 */
(brace
l_string|&quot;EAST&quot;
comma
op_plus
l_int|10
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Eastern Australian Standard */
(brace
l_string|&quot;EADT&quot;
comma
op_plus
l_int|10
comma
l_int|1
comma
)brace
comma
multiline_comment|/* Eastern Australian Daylight */
(brace
l_string|&quot;GST&quot;
comma
op_plus
l_int|10
comma
l_int|0
comma
)brace
comma
multiline_comment|/* Guam Standard, USSR Zone 9 */
(brace
l_string|&quot;NZT&quot;
comma
op_plus
l_int|11
comma
l_int|0
comma
)brace
comma
multiline_comment|/* New Zealand */
(brace
l_string|&quot;NZST&quot;
comma
op_plus
l_int|11
comma
l_int|0
comma
)brace
comma
multiline_comment|/* New Zealand Standard */
(brace
l_string|&quot;NZDT&quot;
comma
op_plus
l_int|11
comma
l_int|1
comma
)brace
comma
multiline_comment|/* New Zealand Daylight */
(brace
l_string|&quot;IDLE&quot;
comma
op_plus
l_int|12
comma
l_int|0
comma
)brace
comma
multiline_comment|/* International Date Line East */
)brace
suffix:semicolon
DECL|function|match_string
r_static
r_int
id|match_string
c_func
(paren
r_const
r_char
op_star
id|date
comma
r_const
r_char
op_star
id|str
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|date
suffix:semicolon
id|date
op_increment
comma
id|str
op_increment
comma
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|date
op_eq
op_star
id|str
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|toupper
c_func
(paren
op_star
id|date
)paren
op_eq
id|toupper
c_func
(paren
op_star
id|str
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isalnum
c_func
(paren
op_star
id|date
)paren
)paren
r_break
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|skip_alpha
r_static
r_int
id|skip_alpha
c_func
(paren
r_const
r_char
op_star
id|date
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|isalpha
c_func
(paren
id|date
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n;* Parse month, weekday, or timezone name&n;*/
DECL|function|match_alpha
r_static
r_int
id|match_alpha
c_func
(paren
r_const
r_char
op_star
id|date
comma
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|offset
)paren
(brace
r_int
id|i
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
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|match
op_assign
id|match_string
c_func
(paren
id|date
comma
id|month_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_ge
l_int|3
)paren
(brace
id|tm-&gt;tm_mon
op_assign
id|i
suffix:semicolon
r_return
id|match
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|match
op_assign
id|match_string
c_func
(paren
id|date
comma
id|weekday_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_ge
l_int|3
)paren
(brace
id|tm-&gt;tm_wday
op_assign
id|i
suffix:semicolon
r_return
id|match
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|timezone_names
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|match
op_assign
id|match_string
c_func
(paren
id|date
comma
id|timezone_names
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_ge
l_int|3
)paren
(brace
r_int
id|off
op_assign
id|timezone_names
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
multiline_comment|/* This is bogus, but we like summer */
id|off
op_add_assign
id|timezone_names
(braket
id|i
)braket
dot
id|dst
suffix:semicolon
multiline_comment|/* Only use the tz name offset if we don&squot;t have anything better */
r_if
c_cond
(paren
op_star
id|offset
op_eq
l_int|1
)paren
op_star
id|offset
op_assign
l_int|60
op_star
id|off
suffix:semicolon
r_return
id|match
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
l_string|&quot;PM&quot;
)paren
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|tm-&gt;tm_hour
OG
l_int|0
op_logical_and
id|tm-&gt;tm_hour
OL
l_int|12
)paren
id|tm-&gt;tm_hour
op_add_assign
l_int|12
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
multiline_comment|/* BAD CRAP */
r_return
id|skip_alpha
c_func
(paren
id|date
)paren
suffix:semicolon
)brace
DECL|function|is_date
r_static
r_int
id|is_date
c_func
(paren
r_int
id|year
comma
r_int
id|month
comma
r_int
id|day
comma
r_struct
id|tm
op_star
id|tm
)paren
(brace
r_if
c_cond
(paren
id|month
OG
l_int|0
op_logical_and
id|month
template_param
l_int|0
op_logical_and
id|day
OL
l_int|32
)paren
(brace
r_if
c_cond
(paren
id|year
op_eq
l_int|1
)paren
(brace
id|tm-&gt;tm_mon
op_assign
id|month
op_minus
l_int|1
suffix:semicolon
id|tm-&gt;tm_mday
op_assign
id|day
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|year
op_ge
l_int|1970
op_logical_and
id|year
OL
l_int|2100
)paren
(brace
id|year
op_sub_assign
l_int|1900
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|year
OG
l_int|70
op_logical_and
id|year
OL
l_int|100
)paren
(brace
multiline_comment|/* ok */
)brace
r_else
r_if
c_cond
(paren
id|year
OL
l_int|38
)paren
(brace
id|year
op_add_assign
l_int|100
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
id|tm-&gt;tm_mon
op_assign
id|month
op_minus
l_int|1
suffix:semicolon
id|tm-&gt;tm_mday
op_assign
id|day
suffix:semicolon
id|tm-&gt;tm_year
op_assign
id|year
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|match_multi_number
r_static
r_int
id|match_multi_number
c_func
(paren
r_int
r_int
id|num
comma
r_char
id|c
comma
r_const
r_char
op_star
id|date
comma
r_char
op_star
id|end
comma
r_struct
id|tm
op_star
id|tm
)paren
(brace
r_int
id|num2
comma
id|num3
suffix:semicolon
id|num2
op_assign
id|strtol
c_func
(paren
id|end
op_plus
l_int|1
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
id|num3
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
op_eq
id|c
op_logical_and
id|isdigit
c_func
(paren
id|end
(braket
l_int|1
)braket
)paren
)paren
id|num3
op_assign
id|strtol
c_func
(paren
id|end
op_plus
l_int|1
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Time? Date? */
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;:&squot;
suffix:colon
r_if
c_cond
(paren
id|num3
OL
l_int|0
)paren
id|num3
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num
OL
l_int|25
op_logical_and
id|num2
op_ge
l_int|0
op_logical_and
id|num2
OL
l_int|60
op_logical_and
id|num3
op_ge
l_int|0
op_logical_and
id|num3
op_le
l_int|60
)paren
(brace
id|tm-&gt;tm_hour
op_assign
id|num
suffix:semicolon
id|tm-&gt;tm_min
op_assign
id|num2
suffix:semicolon
id|tm-&gt;tm_sec
op_assign
id|num3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
r_case
l_char|&squot;/&squot;
suffix:colon
r_if
c_cond
(paren
id|num
OG
l_int|70
)paren
(brace
multiline_comment|/* yyyy-mm-dd? */
r_if
c_cond
(paren
id|is_date
c_func
(paren
id|num
comma
id|num2
comma
id|num3
comma
id|tm
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* yyyy-dd-mm? */
r_if
c_cond
(paren
id|is_date
c_func
(paren
id|num
comma
id|num3
comma
id|num2
comma
id|tm
)paren
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* mm/dd/yy ? */
r_if
c_cond
(paren
id|is_date
c_func
(paren
id|num3
comma
id|num
comma
id|num2
comma
id|tm
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* dd/mm/yy ? */
r_if
c_cond
(paren
id|is_date
c_func
(paren
id|num3
comma
id|num2
comma
id|num
comma
id|tm
)paren
)paren
r_break
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|end
id|date
suffix:semicolon
)brace
multiline_comment|/*&n; * We&squot;ve seen a digit. Time? Year? Date? &n; */
DECL|function|match_digit
r_static
r_int
id|match_digit
c_func
(paren
r_const
r_char
op_star
id|date
comma
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|offset
comma
r_int
op_star
id|tm_gmt
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
r_int
id|num
suffix:semicolon
id|num
op_assign
id|strtoul
c_func
(paren
id|date
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Seconds since 1970? We trigger on that for anything after Jan 1, 2000&n;&t; */
r_if
c_cond
(paren
id|num
OG
l_int|946684800
)paren
(brace
id|time_t
id|time
op_assign
id|num
suffix:semicolon
r_if
c_cond
(paren
id|gmtime_r
c_func
(paren
op_amp
id|time
comma
id|tm
)paren
)paren
(brace
op_star
id|tm_gmt
op_assign
l_int|1
suffix:semicolon
r_return
id|end
id|date
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Check for special formats: num[:-/]num[same]num&n;&t; */
r_switch
c_cond
(paren
op_star
id|end
)paren
(brace
r_case
l_char|&squot;:&squot;
suffix:colon
r_case
l_char|&squot;/&squot;
suffix:colon
r_case
l_char|&squot;-&squot;
suffix:colon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|end
(braket
l_int|1
)braket
)paren
)paren
(brace
r_int
id|match
op_assign
id|match_multi_number
c_func
(paren
id|num
comma
op_star
id|end
comma
id|date
comma
id|end
comma
id|tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
)paren
r_return
id|match
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * None of the special formats? Try to guess what&n;&t; * the number meant. We use the number of digits&n;&t; * to make a more educated guess..&n;&t; */
id|n
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|n
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|isdigit
c_func
(paren
id|date
(braket
id|n
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* Four-digit year or a timezone? */
r_if
c_cond
(paren
id|n
op_eq
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|num
op_le
l_int|1200
op_logical_and
op_star
id|offset
op_eq
l_int|1
)paren
(brace
r_int
r_int
id|minutes
op_assign
id|num
op_mod
l_int|100
suffix:semicolon
r_int
r_int
id|hours
op_assign
id|num
op_div
l_int|100
suffix:semicolon
op_star
id|offset
op_assign
id|hours
op_star
l_int|60
op_plus
id|minutes
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num
OG
l_int|1900
op_logical_and
id|num
OL
l_int|2100
)paren
id|tm-&gt;tm_year
op_assign
id|num
l_int|1900
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * NOTE! We will give precedence to day-of-month over month or&n;&t; * year numbers in the 1-12 range. So 05 is always &quot;mday 5&quot;,&n;&t; * unless we already have a mday..&n;&t; *&n;&t; * IOW, 01 Apr 05 parses as &quot;April 1st, 2005&quot;.&n;&t; */
r_if
c_cond
(paren
id|num
OG
l_int|0
op_logical_and
id|num
OL
l_int|32
op_logical_and
id|tm-&gt;tm_mday
OL
l_int|0
)paren
(brace
id|tm-&gt;tm_mday
op_assign
id|num
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/* Two-digit year? */
r_if
c_cond
(paren
id|n
op_eq
l_int|2
op_logical_and
id|tm-&gt;tm_year
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|num
OL
l_int|10
op_logical_and
id|tm-&gt;tm_mday
op_ge
l_int|0
)paren
(brace
id|tm-&gt;tm_year
op_assign
id|num
op_plus
l_int|100
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num
op_ge
l_int|70
)paren
(brace
id|tm-&gt;tm_year
op_assign
id|num
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|num
OG
l_int|0
op_logical_and
id|num
OL
l_int|32
)paren
(brace
id|tm-&gt;tm_mday
op_assign
id|num
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num
OG
l_int|1900
)paren
(brace
id|tm-&gt;tm_year
op_assign
id|num
l_int|1900
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num
OG
l_int|70
)paren
(brace
id|tm-&gt;tm_year
op_assign
id|num
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num
OG
l_int|0
op_logical_and
id|num
OL
l_int|13
)paren
(brace
id|tm-&gt;tm_mon
op_assign
id|num
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|match_tz
r_static
r_int
id|match_tz
c_func
(paren
r_const
r_char
op_star
id|date
comma
r_int
op_star
id|offp
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_int
id|offset
op_assign
id|strtoul
c_func
(paren
id|date
op_plus
l_int|1
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_int
id|min
comma
id|hour
suffix:semicolon
r_int
id|n
op_assign
id|end
id|date
l_int|1
suffix:semicolon
id|min
op_assign
id|offset
op_mod
l_int|100
suffix:semicolon
id|hour
op_assign
id|offset
op_div
l_int|100
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t accept any random crap.. At least 3 digits, and&n;&t; * a valid minute. We might want to check that the minutes&n;&t; * are divisible by 30 or something too.&n;&t; */
r_if
c_cond
(paren
id|min
template_param
l_int|2
)paren
(brace
id|offset
op_assign
id|hour
op_star
l_int|60
op_plus
id|min
suffix:semicolon
r_if
c_cond
(paren
op_star
id|date
op_eq
l_char|&squot;-&squot;
)paren
id|offset
op_assign
id|offset
suffix:semicolon
op_star
id|offp
op_assign
id|offset
suffix:semicolon
)brace
r_return
id|end
id|date
suffix:semicolon
)brace
DECL|function|date_string
r_static
r_int
id|date_string
c_func
(paren
r_int
r_int
id|date
comma
r_int
id|offset
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|sign
op_assign
l_char|&squot;+&squot;
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
(brace
id|offset
op_assign
id|offset
suffix:semicolon
id|sign
op_assign
l_char|&squot;-&squot;
suffix:semicolon
)brace
r_return
id|snprintf
c_func
(paren
id|buf
comma
id|len
comma
l_string|&quot;%lu %c%02d%02d&quot;
comma
id|date
comma
id|sign
comma
id|offset
op_div
l_int|60
comma
id|offset
op_mod
l_int|60
)paren
suffix:semicolon
)brace
multiline_comment|/* Gr. strptime is crap for this; it doesn&squot;t have a way to require RFC2822&n;   (i.e. English) day/month names, and it doesn&squot;t work correctly with %z. */
DECL|function|parse_date
r_int
id|parse_date
c_func
(paren
r_const
r_char
op_star
id|date
comma
r_char
op_star
id|result
comma
r_int
id|maxlen
)paren
(brace
r_struct
id|tm
id|tm
suffix:semicolon
r_int
id|offset
comma
id|tm_gmt
suffix:semicolon
id|time_t
id|then
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tm
comma
l_int|0
comma
r_sizeof
(paren
id|tm
)paren
)paren
suffix:semicolon
id|tm.tm_year
op_assign
l_int|1
suffix:semicolon
id|tm.tm_mon
op_assign
l_int|1
suffix:semicolon
id|tm.tm_mday
op_assign
l_int|1
suffix:semicolon
id|tm.tm_isdst
op_assign
l_int|1
suffix:semicolon
id|offset
op_assign
l_int|1
suffix:semicolon
id|tm_gmt
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|match
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|c
op_assign
op_star
id|date
suffix:semicolon
multiline_comment|/* Stop at end of string or newline */
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|isalpha
c_func
(paren
id|c
)paren
)paren
id|match
op_assign
id|match_alpha
c_func
(paren
id|date
comma
op_amp
id|tm
comma
op_amp
id|offset
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|c
)paren
)paren
id|match
op_assign
id|match_digit
c_func
(paren
id|date
comma
op_amp
id|tm
comma
op_amp
id|offset
comma
op_amp
id|tm_gmt
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|c
op_eq
l_char|&squot;-&squot;
op_logical_or
id|c
op_eq
l_char|&squot;+&squot;
)paren
op_logical_and
id|isdigit
c_func
(paren
id|date
(braket
l_int|1
)braket
)paren
)paren
id|match
op_assign
id|match_tz
c_func
(paren
id|date
comma
op_amp
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match
)paren
(brace
multiline_comment|/* BAD CRAP */
id|match
op_assign
l_int|1
suffix:semicolon
)brace
id|date
op_add_assign
id|match
suffix:semicolon
)brace
multiline_comment|/* mktime uses local timezone */
id|then
op_assign
id|my_mktime
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
l_int|1
)paren
id|offset
op_assign
(paren
id|then
id|mktime
c_func
(paren
op_amp
id|tm
)paren
)paren
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|then
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tm_gmt
)paren
id|then
op_sub_assign
id|offset
op_star
l_int|60
suffix:semicolon
r_return
id|date_string
c_func
(paren
id|then
comma
id|offset
comma
id|result
comma
id|maxlen
)paren
suffix:semicolon
)brace
DECL|function|datestamp
r_void
id|datestamp
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|bufsize
)paren
(brace
id|time_t
id|now
suffix:semicolon
r_int
id|offset
suffix:semicolon
id|time
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
id|offset
op_assign
id|my_mktime
c_func
(paren
id|localtime
c_func
(paren
op_amp
id|now
)paren
)paren
id|now
suffix:semicolon
id|offset
op_div_assign
l_int|60
suffix:semicolon
id|date_string
c_func
(paren
id|now
comma
id|offset
comma
id|buf
comma
id|bufsize
)paren
suffix:semicolon
)brace
DECL|function|update_tm
r_static
r_void
id|update_tm
c_func
(paren
r_struct
id|tm
op_star
id|tm
comma
r_int
r_int
id|sec
)paren
(brace
id|time_t
id|n
op_assign
id|mktime
c_func
(paren
id|tm
)paren
id|sec
suffix:semicolon
id|localtime_r
c_func
(paren
op_amp
id|n
comma
id|tm
)paren
suffix:semicolon
)brace
DECL|function|date_yesterday
r_static
r_void
id|date_yesterday
c_func
(paren
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|num
)paren
(brace
id|update_tm
c_func
(paren
id|tm
comma
l_int|24
op_star
l_int|60
op_star
l_int|60
)paren
suffix:semicolon
)brace
DECL|function|date_time
r_static
r_void
id|date_time
c_func
(paren
r_struct
id|tm
op_star
id|tm
comma
r_int
id|hour
)paren
(brace
r_if
c_cond
(paren
id|tm-&gt;tm_hour
OL
id|hour
)paren
id|date_yesterday
c_func
(paren
id|tm
comma
l_int|NULL
)paren
suffix:semicolon
id|tm-&gt;tm_hour
op_assign
id|hour
suffix:semicolon
id|tm-&gt;tm_min
op_assign
l_int|0
suffix:semicolon
id|tm-&gt;tm_sec
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|date_midnight
r_static
r_void
id|date_midnight
c_func
(paren
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|num
)paren
(brace
id|date_time
c_func
(paren
id|tm
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|date_noon
r_static
r_void
id|date_noon
c_func
(paren
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|num
)paren
(brace
id|date_time
c_func
(paren
id|tm
comma
l_int|12
)paren
suffix:semicolon
)brace
DECL|function|date_tea
r_static
r_void
id|date_tea
c_func
(paren
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|num
)paren
(brace
id|date_time
c_func
(paren
id|tm
comma
l_int|17
)paren
suffix:semicolon
)brace
DECL|struct|special
r_static
r_const
r_struct
id|special
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
r_struct
id|tm
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|variable|special
)brace
id|special
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;yesterday&quot;
comma
id|date_yesterday
)brace
comma
(brace
l_string|&quot;noon&quot;
comma
id|date_noon
)brace
comma
(brace
l_string|&quot;midnight&quot;
comma
id|date_midnight
)brace
comma
(brace
l_string|&quot;tea&quot;
comma
id|date_tea
)brace
comma
(brace
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|number_name
r_static
r_const
r_char
op_star
id|number_name
(braket
)braket
op_assign
(brace
l_string|&quot;zero&quot;
comma
l_string|&quot;one&quot;
comma
l_string|&quot;two&quot;
comma
l_string|&quot;three&quot;
comma
l_string|&quot;four&quot;
comma
l_string|&quot;five&quot;
comma
l_string|&quot;six&quot;
comma
l_string|&quot;seven&quot;
comma
l_string|&quot;eight&quot;
comma
l_string|&quot;nine&quot;
comma
l_string|&quot;ten&quot;
comma
)brace
suffix:semicolon
DECL|struct|typelen
r_static
r_const
r_struct
id|typelen
(brace
DECL|member|type
r_const
r_char
op_star
id|type
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|variable|typelen
)brace
id|typelen
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;seconds&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;minutes&quot;
comma
l_int|60
)brace
comma
(brace
l_string|&quot;hours&quot;
comma
l_int|60
op_star
l_int|60
)brace
comma
(brace
l_string|&quot;days&quot;
comma
l_int|24
op_star
l_int|60
op_star
l_int|60
)brace
comma
(brace
l_string|&quot;weeks&quot;
comma
l_int|7
op_star
l_int|24
op_star
l_int|60
op_star
l_int|60
)brace
comma
(brace
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|approxidate_alpha
r_static
r_const
r_char
op_star
id|approxidate_alpha
c_func
(paren
r_const
r_char
op_star
id|date
comma
r_struct
id|tm
op_star
id|tm
comma
r_int
op_star
id|num
)paren
(brace
r_const
r_struct
id|typelen
op_star
id|tl
suffix:semicolon
r_const
r_struct
id|special
op_star
id|s
suffix:semicolon
r_const
r_char
op_star
id|end
op_assign
id|date
suffix:semicolon
r_int
id|n
op_assign
l_int|1
comma
id|i
suffix:semicolon
r_while
c_loop
(paren
id|isalpha
c_func
(paren
op_star
op_increment
id|end
)paren
)paren
id|n
op_increment
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
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|match
op_assign
id|match_string
c_func
(paren
id|date
comma
id|month_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_ge
l_int|3
)paren
(brace
id|tm-&gt;tm_mon
op_assign
id|i
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|s
op_assign
id|special
suffix:semicolon
id|s-&gt;name
suffix:semicolon
id|s
op_increment
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|s-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
id|s-&gt;name
)paren
op_eq
id|len
)paren
(brace
id|s
op_member_access_from_pointer
id|fn
c_func
(paren
id|tm
comma
id|num
)paren
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|num
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|11
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|number_name
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
id|number_name
(braket
id|i
)braket
)paren
op_eq
id|len
)paren
(brace
op_star
id|num
op_assign
id|i
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
l_string|&quot;last&quot;
)paren
op_eq
l_int|4
)paren
op_star
id|num
op_assign
l_int|1
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
id|tl
op_assign
id|typelen
suffix:semicolon
r_while
c_loop
(paren
id|tl-&gt;type
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|tl-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
id|tl-&gt;type
)paren
op_ge
id|len
op_minus
l_int|1
)paren
(brace
id|update_tm
c_func
(paren
id|tm
comma
id|tl-&gt;length
op_star
op_star
id|num
)paren
suffix:semicolon
op_star
id|num
op_assign
l_int|0
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
id|tl
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|match
op_assign
id|match_string
c_func
(paren
id|date
comma
id|weekday_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
op_ge
l_int|3
)paren
(brace
r_int
id|diff
comma
id|n
op_assign
op_star
id|num
l_int|1
suffix:semicolon
op_star
id|num
op_assign
l_int|0
suffix:semicolon
id|diff
op_assign
id|tm-&gt;tm_wday
id|i
suffix:semicolon
r_if
c_cond
(paren
id|diff
op_le
l_int|0
)paren
id|n
op_increment
suffix:semicolon
id|diff
op_add_assign
l_int|7
op_star
id|n
suffix:semicolon
id|update_tm
c_func
(paren
id|tm
comma
id|diff
op_star
l_int|24
op_star
l_int|60
op_star
l_int|60
)paren
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
l_string|&quot;months&quot;
)paren
op_ge
l_int|5
)paren
(brace
r_int
id|n
op_assign
id|tm-&gt;tm_mon
op_star
id|num
suffix:semicolon
op_star
id|num
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|n
OL
l_int|0
)paren
(brace
id|n
op_add_assign
l_int|12
suffix:semicolon
id|tm-&gt;tm_year
op_decrement
suffix:semicolon
)brace
id|tm-&gt;tm_mon
op_assign
id|n
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|match_string
c_func
(paren
id|date
comma
l_string|&quot;years&quot;
)paren
op_ge
l_int|4
)paren
(brace
id|tm-&gt;tm_year
op_sub_assign
op_star
id|num
suffix:semicolon
op_star
id|num
op_assign
l_int|0
suffix:semicolon
r_return
id|end
suffix:semicolon
)brace
r_return
id|end
suffix:semicolon
)brace
DECL|function|approxidate
r_int
r_int
id|approxidate
c_func
(paren
r_const
r_char
op_star
id|date
)paren
(brace
r_int
id|number
op_assign
l_int|0
suffix:semicolon
r_struct
id|tm
id|tm
comma
id|now
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_char
id|buffer
(braket
l_int|50
)braket
suffix:semicolon
r_if
c_cond
(paren
id|parse_date
c_func
(paren
id|date
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
OG
l_int|0
)paren
r_return
id|strtoul
c_func
(paren
id|buffer
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
id|localtime_r
c_func
(paren
op_amp
id|tv.tv_sec
comma
op_amp
id|tm
)paren
suffix:semicolon
id|now
op_assign
id|tm
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|date
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
id|date
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|c
)paren
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
id|number
op_assign
id|strtoul
c_func
(paren
id|date
op_minus
l_int|1
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
id|date
op_assign
id|end
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isalpha
c_func
(paren
id|c
)paren
)paren
id|date
op_assign
id|approxidate_alpha
c_func
(paren
id|date
op_minus
l_int|1
comma
op_amp
id|tm
comma
op_amp
id|number
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|number
OG
l_int|0
op_logical_and
id|number
OL
l_int|32
)paren
id|tm.tm_mday
op_assign
id|number
suffix:semicolon
r_if
c_cond
(paren
id|tm.tm_mon
OG
id|now.tm_mon
op_logical_and
id|tm.tm_year
op_eq
id|now.tm_year
)paren
id|tm.tm_year
op_decrement
suffix:semicolon
r_return
id|mktime
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
)brace
eof
