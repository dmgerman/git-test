multiline_comment|/*&n; * test-line-buffer.c: code to exercise the svn importer&squot;s input helper&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;vcs-svn/line_buffer.h&quot;
DECL|function|strtouint32
r_static
r_uint32
id|strtouint32
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_uintmax
id|n
op_assign
id|strtoumax
c_func
(paren
id|s
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|end
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|die
c_func
(paren
l_string|&quot;invalid count: %s&quot;
comma
id|s
)paren
suffix:semicolon
r_return
(paren
r_uint32
)paren
id|n
suffix:semicolon
)brace
DECL|function|handle_command
r_static
r_void
id|handle_command
c_func
(paren
r_const
r_char
op_star
id|command
comma
r_const
r_char
op_star
id|arg
comma
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
r_switch
c_cond
(paren
op_star
id|command
)paren
(brace
r_case
l_char|&squot;b&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;binary &quot;
)paren
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
id|buffer_read_binary
c_func
(paren
id|buf
comma
op_amp
id|sb
comma
id|strtouint32
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|sb.buf
comma
l_int|1
comma
id|sb.len
comma
id|stdout
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;copy &quot;
)paren
)paren
(brace
id|buffer_copy_bytes
c_func
(paren
id|buf
comma
id|strtouint32
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;s&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;skip &quot;
)paren
)paren
(brace
id|buffer_skip_bytes
c_func
(paren
id|buf
comma
id|strtouint32
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;unrecognized command: %s&quot;
comma
id|command
)paren
suffix:semicolon
)brace
)brace
DECL|function|handle_line
r_static
r_void
id|handle_line
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_struct
id|line_buffer
op_star
id|stdin_buf
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
id|die
c_func
(paren
l_string|&quot;no argument in line: %s&quot;
comma
id|line
)paren
suffix:semicolon
id|handle_command
c_func
(paren
id|line
comma
id|arg
op_plus
l_int|1
comma
id|stdin_buf
)paren
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
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_struct
id|line_buffer
id|stdin_buf
op_assign
id|LINE_BUFFER_INIT
suffix:semicolon
r_struct
id|line_buffer
id|file_buf
op_assign
id|LINE_BUFFER_INIT
suffix:semicolon
r_struct
id|line_buffer
op_star
id|input
op_assign
op_amp
id|stdin_buf
suffix:semicolon
r_const
r_char
op_star
id|filename
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
id|filename
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
)paren
id|filename
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_else
id|usage
c_func
(paren
l_string|&quot;test-line-buffer [file | &amp;fd] &lt; script&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_init
c_func
(paren
op_amp
id|stdin_buf
comma
l_int|NULL
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;open error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filename
)paren
(brace
r_if
c_cond
(paren
op_star
id|filename
op_eq
l_char|&squot;&amp;&squot;
)paren
(brace
r_if
c_cond
(paren
id|buffer_fdinit
c_func
(paren
op_amp
id|file_buf
comma
id|strtouint32
c_func
(paren
id|filename
op_plus
l_int|1
)paren
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;error opening fd %s&quot;
comma
id|filename
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|buffer_init
c_func
(paren
op_amp
id|file_buf
comma
id|filename
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;error opening %s&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
id|input
op_assign
op_amp
id|file_buf
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|s
op_assign
id|buffer_read_line
c_func
(paren
op_amp
id|stdin_buf
)paren
)paren
)paren
id|handle_line
c_func
(paren
id|s
comma
id|input
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filename
op_logical_and
id|buffer_deinit
c_func
(paren
op_amp
id|file_buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;error reading from %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_deinit
c_func
(paren
op_amp
id|stdin_buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;input error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|stdout
)paren
)paren
id|die
c_func
(paren
l_string|&quot;output error&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
