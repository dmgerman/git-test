macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
DECL|variable|packet_buffer
r_char
id|packet_buffer
(braket
id|LARGE_PACKET_MAX
)braket
suffix:semicolon
DECL|variable|packet_trace_prefix
r_static
r_const
r_char
op_star
id|packet_trace_prefix
op_assign
l_string|&quot;git&quot;
suffix:semicolon
DECL|variable|trace_packet
r_static
r_struct
id|trace_key
id|trace_packet
op_assign
id|TRACE_KEY_INIT
c_func
(paren
id|PACKET
)paren
suffix:semicolon
DECL|function|packet_trace_identity
r_void
id|packet_trace_identity
c_func
(paren
r_const
r_char
op_star
id|prog
)paren
(brace
id|packet_trace_prefix
op_assign
id|xstrdup
c_func
(paren
id|prog
)paren
suffix:semicolon
)brace
DECL|function|packet_trace
r_static
r_void
id|packet_trace
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|len
comma
r_int
id|write
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|strbuf
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trace_want
c_func
(paren
op_amp
id|trace_packet
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* +32 is just a guess for header + quoting */
id|strbuf_init
c_func
(paren
op_amp
id|out
comma
id|len
op_plus
l_int|32
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|out
comma
l_string|&quot;packet: %12s%c &quot;
comma
id|packet_trace_prefix
comma
id|write
ques
c_cond
l_char|&squot;&gt;&squot;
suffix:colon
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_ge
l_int|4
op_logical_and
id|starts_with
c_func
(paren
id|buf
comma
l_string|&quot;PACK&quot;
)paren
)paren
op_logical_or
(paren
id|len
op_ge
l_int|5
op_logical_and
id|starts_with
c_func
(paren
id|buf
op_plus
l_int|1
comma
l_string|&quot;PACK&quot;
)paren
)paren
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|out
comma
l_string|&quot;PACK ...&quot;
)paren
suffix:semicolon
id|trace_disable
c_func
(paren
op_amp
id|trace_packet
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* XXX we should really handle printable utf8 */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* suppress newlines */
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_ge
l_int|0x20
op_logical_and
id|buf
(braket
id|i
)braket
op_le
l_int|0x7e
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|out
comma
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
op_amp
id|out
comma
l_string|&quot;&bslash;&bslash;%o&quot;
comma
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|strbuf_addch
c_func
(paren
op_amp
id|out
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|trace_strbuf
c_func
(paren
op_amp
id|trace_packet
comma
op_amp
id|out
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|out
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If we buffered things up above (we don&squot;t, but we should),&n; * we&squot;d flush it here&n; */
DECL|function|packet_flush
r_void
id|packet_flush
c_func
(paren
r_int
id|fd
)paren
(brace
id|packet_trace
c_func
(paren
l_string|&quot;0000&quot;
comma
l_int|4
comma
l_int|1
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|fd
comma
l_string|&quot;0000&quot;
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|packet_buf_flush
r_void
id|packet_buf_flush
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
id|packet_trace
c_func
(paren
l_string|&quot;0000&quot;
comma
l_int|4
comma
l_int|1
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
l_string|&quot;0000&quot;
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|macro|hex
mdefine_line|#define hex(a) (hexchar[(a) &amp; 15])
DECL|variable|buffer
r_static
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
DECL|function|format_packet
r_static
r_int
id|format_packet
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
(brace
r_static
r_char
id|hexchar
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
r_int
id|n
suffix:semicolon
id|n
op_assign
id|vsnprintf
c_func
(paren
id|buffer
op_plus
l_int|4
comma
r_sizeof
(paren
id|buffer
)paren
l_int|4
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
r_sizeof
(paren
id|buffer
)paren
op_minus
l_int|4
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: impossibly long line&quot;
)paren
suffix:semicolon
id|n
op_add_assign
l_int|4
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
id|hex
c_func
(paren
id|n
op_rshift
l_int|12
)paren
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|hex
c_func
(paren
id|n
op_rshift
l_int|8
)paren
suffix:semicolon
id|buffer
(braket
l_int|2
)braket
op_assign
id|hex
c_func
(paren
id|n
op_rshift
l_int|4
)paren
suffix:semicolon
id|buffer
(braket
l_int|3
)braket
op_assign
id|hex
c_func
(paren
id|n
)paren
suffix:semicolon
id|packet_trace
c_func
(paren
id|buffer
op_plus
l_int|4
comma
id|n
op_minus
l_int|4
comma
l_int|1
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|packet_write
r_void
id|packet_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|n
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|n
op_assign
id|format_packet
c_func
(paren
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|fd
comma
id|buffer
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|packet_buf_write
r_void
id|packet_buf_write
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
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|n
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|n
op_assign
id|format_packet
c_func
(paren
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|buffer
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|get_packet_data
r_static
r_int
id|get_packet_data
c_func
(paren
r_int
id|fd
comma
r_char
op_star
op_star
id|src_buf
comma
r_int
op_star
id|src_size
comma
r_void
op_star
id|dst
comma
r_int
id|size
comma
r_int
id|options
)paren
(brace
id|ssize_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
op_logical_and
id|src_buf
op_logical_and
op_star
id|src_buf
)paren
id|die
c_func
(paren
l_string|&quot;BUG: multiple sources given to packet_read&quot;
)paren
suffix:semicolon
multiline_comment|/* Read up to &quot;size&quot; bytes from our source, whatever it is. */
r_if
c_cond
(paren
id|src_buf
op_logical_and
op_star
id|src_buf
)paren
(brace
id|ret
op_assign
id|size
OL
op_star
id|src_size
ques
c_cond
id|size
suffix:colon
op_star
id|src_size
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
op_star
id|src_buf
comma
id|ret
)paren
suffix:semicolon
op_star
id|src_buf
op_add_assign
id|ret
suffix:semicolon
op_star
id|src_size
op_sub_assign
id|ret
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|read_in_full
c_func
(paren
id|fd
comma
id|dst
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;read error&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* And complain if we didn&squot;t get enough bytes to satisfy the read. */
r_if
c_cond
(paren
id|ret
OL
id|size
)paren
(brace
r_if
c_cond
(paren
id|options
op_amp
id|PACKET_READ_GENTLE_ON_EOF
)paren
r_return
l_int|1
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;The remote end hung up unexpectedly&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|packet_length
r_static
r_int
id|packet_length
c_func
(paren
r_const
r_char
op_star
id|linelen
)paren
(brace
r_int
id|n
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|4
suffix:semicolon
id|n
op_increment
)paren
(brace
r_int
r_char
id|c
op_assign
id|linelen
(braket
id|n
)braket
suffix:semicolon
id|len
op_lshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
(brace
id|len
op_add_assign
id|c
l_char|&squot;0&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;f&squot;
)paren
(brace
id|len
op_add_assign
id|c
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;F&squot;
)paren
(brace
id|len
op_add_assign
id|c
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|packet_read
r_int
id|packet_read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
op_star
id|src_buf
comma
r_int
op_star
id|src_len
comma
r_char
op_star
id|buffer
comma
r_int
id|size
comma
r_int
id|options
)paren
(brace
r_int
id|len
comma
id|ret
suffix:semicolon
r_char
id|linelen
(braket
l_int|4
)braket
suffix:semicolon
id|ret
op_assign
id|get_packet_data
c_func
(paren
id|fd
comma
id|src_buf
comma
id|src_len
comma
id|linelen
comma
l_int|4
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|len
op_assign
id|packet_length
c_func
(paren
id|linelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: bad line length character: %.4s&quot;
comma
id|linelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
id|packet_trace
c_func
(paren
l_string|&quot;0000&quot;
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|len
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|size
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: bad line length %d&quot;
comma
id|len
)paren
suffix:semicolon
id|ret
op_assign
id|get_packet_data
c_func
(paren
id|fd
comma
id|src_buf
comma
id|src_len
comma
id|buffer
comma
id|len
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|options
op_amp
id|PACKET_READ_CHOMP_NEWLINE
)paren
op_logical_and
id|len
op_logical_and
id|buffer
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|len
op_decrement
suffix:semicolon
id|buffer
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|packet_trace
c_func
(paren
id|buffer
comma
id|len
comma
l_int|0
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|packet_read_line_generic
r_static
r_char
op_star
id|packet_read_line_generic
c_func
(paren
r_int
id|fd
comma
r_char
op_star
op_star
id|src
comma
r_int
op_star
id|src_len
comma
r_int
op_star
id|dst_len
)paren
(brace
r_int
id|len
op_assign
id|packet_read
c_func
(paren
id|fd
comma
id|src
comma
id|src_len
comma
id|packet_buffer
comma
r_sizeof
(paren
id|packet_buffer
)paren
comma
id|PACKET_READ_CHOMP_NEWLINE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst_len
)paren
op_star
id|dst_len
op_assign
id|len
suffix:semicolon
r_return
id|len
ques
c_cond
id|packet_buffer
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|packet_read_line
r_char
op_star
id|packet_read_line
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|len_p
)paren
(brace
r_return
id|packet_read_line_generic
c_func
(paren
id|fd
comma
l_int|NULL
comma
l_int|NULL
comma
id|len_p
)paren
suffix:semicolon
)brace
DECL|function|packet_read_line_buf
r_char
op_star
id|packet_read_line_buf
c_func
(paren
r_char
op_star
op_star
id|src
comma
r_int
op_star
id|src_len
comma
r_int
op_star
id|dst_len
)paren
(brace
r_return
id|packet_read_line_generic
c_func
(paren
l_int|1
comma
id|src
comma
id|src_len
comma
id|dst_len
)paren
suffix:semicolon
)brace
eof
