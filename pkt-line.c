macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
multiline_comment|/*&n; * Write a packetized stream, where each line is preceded by&n; * its length (including the header) as a 4-byte hex number.&n; * A length of &squot;zero&squot; means end of stream (and a length of 1-3&n; * would be an error).&n; *&n; * This is all pretty stupid, but we use this packetized line&n; * format to make a streaming format possible without ever&n; * over-running the read buffers. That way we&squot;ll never read&n; * into what might be the pack data (which should go to another&n; * process entirely).&n; *&n; * The writing side could use stdio, but since the reading&n; * side can&squot;t, we stay with pure read/write interfaces.&n; */
DECL|function|safe_write
id|ssize_t
id|safe_write
c_func
(paren
r_int
id|fd
comma
r_const
r_void
op_star
id|buf
comma
id|ssize_t
id|n
)paren
(brace
id|ssize_t
id|nn
op_assign
id|n
suffix:semicolon
r_while
c_loop
(paren
id|n
)paren
(brace
r_int
id|ret
op_assign
id|xwrite
c_func
(paren
id|fd
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|buf
op_assign
(paren
r_char
op_star
)paren
id|buf
op_plus
id|ret
suffix:semicolon
id|n
op_sub_assign
id|ret
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;write error (disk full?)&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;write error (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_return
id|nn
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
id|safe_write
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
DECL|macro|hex
mdefine_line|#define hex(a) (hexchar[(a) &amp; 15])
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
r_static
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
r_static
r_char
id|hexchar
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
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
id|va_end
c_func
(paren
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
id|safe_write
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
DECL|function|safe_read
r_static
r_void
id|safe_read
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
id|ssize_t
id|ret
op_assign
id|read_in_full
c_func
(paren
id|fd
comma
id|buffer
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
id|die
c_func
(paren
l_string|&quot;read error (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ret
OL
id|size
)paren
id|die
c_func
(paren
l_string|&quot;The remote end hung up unexpectedly&quot;
)paren
suffix:semicolon
)brace
DECL|function|packet_read_line
r_int
id|packet_read_line
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
r_int
id|n
suffix:semicolon
r_int
id|len
suffix:semicolon
r_char
id|linelen
(braket
l_int|4
)braket
suffix:semicolon
id|safe_read
c_func
(paren
id|fd
comma
id|linelen
comma
l_int|4
)paren
suffix:semicolon
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
id|die
c_func
(paren
l_string|&quot;protocol error: bad line length character&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
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
id|safe_read
c_func
(paren
id|fd
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
id|buffer
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
