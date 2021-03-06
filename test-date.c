macro_line|#include &quot;cache.h&quot;
DECL|variable|usage_msg
r_static
r_const
r_char
op_star
id|usage_msg
op_assign
l_string|&quot;&bslash;n&quot;
l_string|&quot;  test-date show [time_t]...&bslash;n&quot;
l_string|&quot;  test-date parse [date]...&bslash;n&quot;
l_string|&quot;  test-date approxidate [date]...&bslash;n&quot;
suffix:semicolon
DECL|function|show_dates
r_static
r_void
id|show_dates
c_func
(paren
r_char
op_star
op_star
id|argv
comma
r_struct
id|timeval
op_star
id|now
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|argv
suffix:semicolon
id|argv
op_increment
)paren
(brace
id|time_t
id|t
op_assign
id|atoi
c_func
(paren
op_star
id|argv
)paren
suffix:semicolon
id|show_date_relative
c_func
(paren
id|t
comma
l_int|0
comma
id|now
comma
op_amp
id|buf
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s -&gt; %s&bslash;n&quot;
comma
op_star
id|argv
comma
id|buf.buf
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|parse_dates
r_static
r_void
id|parse_dates
c_func
(paren
r_char
op_star
op_star
id|argv
comma
r_struct
id|timeval
op_star
id|now
)paren
(brace
r_struct
id|strbuf
id|result
op_assign
id|STRBUF_INIT
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|argv
suffix:semicolon
id|argv
op_increment
)paren
(brace
r_int
r_int
id|t
suffix:semicolon
r_int
id|tz
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|result
)paren
suffix:semicolon
id|parse_date
c_func
(paren
op_star
id|argv
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|result.buf
comma
l_string|&quot;%lu %d&quot;
comma
op_amp
id|t
comma
op_amp
id|tz
)paren
op_eq
l_int|2
)paren
id|printf
c_func
(paren
l_string|&quot;%s -&gt; %s&bslash;n&quot;
comma
op_star
id|argv
comma
id|show_date
c_func
(paren
id|t
comma
id|tz
comma
id|DATE_MODE
c_func
(paren
id|ISO8601
)paren
)paren
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s -&gt; bad&bslash;n&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|result
)paren
suffix:semicolon
)brace
DECL|function|parse_approxidate
r_static
r_void
id|parse_approxidate
c_func
(paren
r_char
op_star
op_star
id|argv
comma
r_struct
id|timeval
op_star
id|now
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|argv
suffix:semicolon
id|argv
op_increment
)paren
(brace
id|time_t
id|t
suffix:semicolon
id|t
op_assign
id|approxidate_relative
c_func
(paren
op_star
id|argv
comma
id|now
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s -&gt; %s&bslash;n&quot;
comma
op_star
id|argv
comma
id|show_date
c_func
(paren
id|t
comma
l_int|0
comma
id|DATE_MODE
c_func
(paren
id|ISO8601
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|timeval
id|now
suffix:semicolon
r_const
r_char
op_star
id|x
suffix:semicolon
id|x
op_assign
id|getenv
c_func
(paren
l_string|&quot;TEST_DATE_NOW&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
)paren
(brace
id|now.tv_sec
op_assign
id|atoi
c_func
(paren
id|x
)paren
suffix:semicolon
id|now.tv_usec
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|gettimeofday
c_func
(paren
op_amp
id|now
comma
l_int|NULL
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|argv
)paren
id|usage
c_func
(paren
id|usage_msg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;show&quot;
)paren
)paren
id|show_dates
c_func
(paren
id|argv
op_plus
l_int|1
comma
op_amp
id|now
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;parse&quot;
)paren
)paren
id|parse_dates
c_func
(paren
id|argv
op_plus
l_int|1
comma
op_amp
id|now
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;approxidate&quot;
)paren
)paren
id|parse_approxidate
c_func
(paren
id|argv
op_plus
l_int|1
comma
op_amp
id|now
)paren
suffix:semicolon
r_else
id|usage
c_func
(paren
id|usage_msg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
