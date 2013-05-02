multiline_comment|/*&n; * This program can either change modification time of the given&n; * file(s) or just print it. The program does not change atime nor&n; * ctime (their values are explicitly preserved).&n; *&n; * The mtime can be changed to an absolute value:&n; *&n; *&t;test-chmtime =&lt;seconds&gt; file...&n; *&n; * Relative to the current time as returned by time(3):&n; *&n; *&t;test-chmtime =+&lt;seconds&gt; (or =-&lt;seconds&gt;) file...&n; *&n; * Or relative to the current mtime of the file:&n; *&n; *&t;test-chmtime &lt;seconds&gt; file...&n; *&t;test-chmtime +&lt;seconds&gt; (or -&lt;seconds&gt;) file...&n; *&n; * Examples:&n; *&n; * To just print the mtime use --verbose and set the file mtime offset to 0:&n; *&n; *&t;test-chmtime -v +0 file&n; *&n; * To set the mtime to current time:&n; *&n; *&t;test-chmtime =+0 file&n; *&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &lt;utime.h&gt;
DECL|variable|usage_str
r_static
r_const
r_char
id|usage_str
(braket
)braket
op_assign
l_string|&quot;-v|--verbose (+|=|=+|=-|-)&lt;seconds&gt; &lt;file&gt;...&quot;
suffix:semicolon
DECL|function|timespec_arg
r_static
r_int
id|timespec_arg
c_func
(paren
r_const
r_char
op_star
id|arg
comma
r_int
r_int
op_star
id|set_time
comma
r_int
op_star
id|set_eq
)paren
(brace
r_char
op_star
id|test
suffix:semicolon
r_const
r_char
op_star
id|timespec
op_assign
id|arg
suffix:semicolon
op_star
id|set_eq
op_assign
(paren
op_star
id|timespec
op_eq
l_char|&squot;=&squot;
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|set_eq
)paren
(brace
id|timespec
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|timespec
op_eq
l_char|&squot;+&squot;
)paren
(brace
op_star
id|set_eq
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* relative &quot;in the future&quot; */
id|timespec
op_increment
suffix:semicolon
)brace
)brace
op_star
id|set_time
op_assign
id|strtol
c_func
(paren
id|timespec
comma
op_amp
id|test
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|test
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Not a base-10 integer: %s&bslash;n&quot;
comma
id|arg
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|set_eq
op_logical_and
op_star
id|set_time
OL
l_int|0
)paren
op_logical_or
op_star
id|set_eq
op_eq
l_int|2
)paren
(brace
id|time_t
id|now
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
op_star
id|set_time
op_add_assign
id|now
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_static
r_int
id|verbose
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* no mtime change by default */
r_int
id|set_eq
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|set_time
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
r_goto
id|usage
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--verbose&quot;
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-v&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|verbose
op_assign
l_int|1
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timespec_arg
c_func
(paren
id|argv
(braket
id|i
)braket
comma
op_amp
id|set_time
comma
op_amp
id|set_eq
)paren
)paren
op_increment
id|i
suffix:semicolon
r_else
r_goto
id|usage
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|stat
id|sb
suffix:semicolon
r_struct
id|utimbuf
id|utb
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|argv
(braket
id|i
)braket
comma
op_amp
id|sb
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to stat %s: %s&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef GIT_WINDOWS_NATIVE
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb.st_mode
op_amp
id|S_IWUSR
)paren
op_logical_and
id|chmod
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|sb.st_mode
op_or
id|S_IWUSR
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Could not make user-writable %s: %s&quot;
comma
id|argv
(braket
id|i
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|utb.actime
op_assign
id|sb.st_atime
suffix:semicolon
id|utb.modtime
op_assign
id|set_eq
ques
c_cond
id|set_time
suffix:colon
id|sb.st_mtime
op_plus
id|set_time
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_uintmax
id|mtime
op_assign
id|utb.modtime
OL
l_int|0
ques
c_cond
l_int|0
suffix:colon
id|utb.modtime
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%&quot;
id|PRIuMAX
l_string|&quot;&bslash;t%s&bslash;n&quot;
comma
id|mtime
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|utb.modtime
op_ne
id|sb.st_mtime
op_logical_and
id|utime
c_func
(paren
id|argv
(braket
id|i
)braket
comma
op_amp
id|utb
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to modify time on %s: %s&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|usage
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s %s&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|usage_str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
