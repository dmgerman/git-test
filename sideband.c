macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
multiline_comment|/*&n; * Receive multiplexed output stream over git native protocol.&n; * in_stream is the input stream from the remote, which carries data&n; * in pkt_line format with band designator.  Demultiplex it into out&n; * and err and return error appropriately.  Band #1 carries the&n; * primary payload.  Things coming over band #2 is not necessarily&n; * error; they are usually informative message on the standard error&n; * stream, aka &quot;verbose&quot;).  A message over band #3 is a signal that&n; * the remote died unexpectedly.  A flush() concludes the stream.&n; */
DECL|macro|PREFIX
mdefine_line|#define PREFIX &quot;remote:&quot;
DECL|macro|ANSI_SUFFIX
mdefine_line|#define ANSI_SUFFIX &quot;&bslash;033[K&quot;
DECL|macro|DUMB_SUFFIX
mdefine_line|#define DUMB_SUFFIX &quot;        &quot;
DECL|macro|FIX_SIZE
mdefine_line|#define FIX_SIZE 10  /* large enough for any of the above */
DECL|function|recv_sideband
r_int
id|recv_sideband
c_func
(paren
r_const
r_char
op_star
id|me
comma
r_int
id|in_stream
comma
r_int
id|out
)paren
(brace
r_int
id|pf
op_assign
id|strlen
c_func
(paren
id|PREFIX
)paren
suffix:semicolon
r_int
id|sf
suffix:semicolon
r_char
id|buf
(braket
id|LARGE_PACKET_MAX
op_plus
l_int|2
op_star
id|FIX_SIZE
)braket
suffix:semicolon
r_char
op_star
id|suffix
comma
op_star
id|term
suffix:semicolon
r_int
id|skip_pf
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|PREFIX
comma
id|pf
)paren
suffix:semicolon
id|term
op_assign
id|getenv
c_func
(paren
l_string|&quot;TERM&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|term
op_logical_and
id|strcmp
c_func
(paren
id|term
comma
l_string|&quot;dumb&quot;
)paren
)paren
id|suffix
op_assign
id|ANSI_SUFFIX
suffix:semicolon
r_else
id|suffix
op_assign
id|DUMB_SUFFIX
suffix:semicolon
id|sf
op_assign
id|strlen
c_func
(paren
id|suffix
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|band
comma
id|len
suffix:semicolon
id|len
op_assign
id|packet_read
c_func
(paren
id|in_stream
comma
id|buf
op_plus
id|pf
comma
id|LARGE_PACKET_MAX
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|1
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: protocol error: no band designator&bslash;n&quot;
comma
id|me
)paren
suffix:semicolon
r_return
id|SIDEBAND_PROTOCOL_ERROR
suffix:semicolon
)brace
id|band
op_assign
id|buf
(braket
id|pf
)braket
op_amp
l_int|0xff
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_switch
c_cond
(paren
id|band
)paren
(brace
r_case
l_int|3
suffix:colon
id|buf
(braket
id|pf
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|buf
(braket
id|pf
op_plus
l_int|1
op_plus
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
r_return
id|SIDEBAND_REMOTE_ERROR
suffix:semicolon
r_case
l_int|2
suffix:colon
id|buf
(braket
id|pf
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_do
(brace
r_char
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_int
id|brk
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * If the last buffer didn&squot;t end with a line&n;&t;&t;&t;&t; * break then we should not print a prefix&n;&t;&t;&t;&t; * this time around.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|skip_pf
)paren
(brace
id|b
op_add_assign
id|pf
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|len
op_add_assign
id|pf
op_plus
l_int|1
suffix:semicolon
id|brk
op_add_assign
id|pf
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Look for a line break. */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|brk
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|brk
OG
id|len
)paren
(brace
id|brk
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b
(braket
id|brk
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|b
(braket
id|brk
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t;&t; * Let&squot;s insert a suffix to clear the end&n;&t;&t;&t;&t; * of the screen line if a line break was&n;&t;&t;&t;&t; * found.  Also, if we don&squot;t skip the&n;&t;&t;&t;&t; * prefix, then a non-empty string must be&n;&t;&t;&t;&t; * present too.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|brk
OG
(paren
id|skip_pf
ques
c_cond
l_int|0
suffix:colon
(paren
id|pf
op_plus
l_int|1
op_plus
l_int|1
)paren
)paren
)paren
(brace
r_char
id|save
(braket
id|FIX_SIZE
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|save
comma
id|b
op_plus
id|brk
comma
id|sf
)paren
suffix:semicolon
id|b
(braket
id|brk
op_plus
id|sf
l_int|1
)braket
op_assign
id|b
(braket
id|brk
l_int|1
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|b
op_plus
id|brk
l_int|1
comma
id|suffix
comma
id|sf
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s&quot;
comma
id|brk
op_plus
id|sf
comma
id|b
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|b
op_plus
id|brk
comma
id|save
comma
id|sf
)paren
suffix:semicolon
id|len
op_sub_assign
id|brk
suffix:semicolon
)brace
r_else
(brace
r_int
id|l
op_assign
id|brk
ques
c_cond
id|brk
suffix:colon
id|len
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s&quot;
comma
id|l
comma
id|b
)paren
suffix:semicolon
id|len
op_sub_assign
id|l
suffix:semicolon
)brace
id|skip_pf
op_assign
op_logical_neg
id|brk
suffix:semicolon
id|memmove
c_func
(paren
id|buf
op_plus
id|pf
op_plus
l_int|1
comma
id|b
op_plus
id|brk
comma
id|len
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_int|1
suffix:colon
id|write_or_die
c_func
(paren
id|out
comma
id|buf
op_plus
id|pf
op_plus
l_int|1
comma
id|len
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: protocol error: bad band #%d&bslash;n&quot;
comma
id|me
comma
id|band
)paren
suffix:semicolon
r_return
id|SIDEBAND_PROTOCOL_ERROR
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fd is connected to the remote side; send the sideband data&n; * over multiplexed packet stream.&n; */
DECL|function|send_sideband
id|ssize_t
id|send_sideband
c_func
(paren
r_int
id|fd
comma
r_int
id|band
comma
r_const
r_char
op_star
id|data
comma
id|ssize_t
id|sz
comma
r_int
id|packet_max
)paren
(brace
id|ssize_t
id|ssz
op_assign
id|sz
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
id|data
suffix:semicolon
r_while
c_loop
(paren
id|sz
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|hdr
(braket
l_int|5
)braket
suffix:semicolon
id|n
op_assign
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|packet_max
l_int|5
OL
id|n
)paren
id|n
op_assign
id|packet_max
l_int|5
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|band
)paren
(brace
id|sprintf
c_func
(paren
id|hdr
comma
l_string|&quot;%04x&quot;
comma
id|n
op_plus
l_int|5
)paren
suffix:semicolon
id|hdr
(braket
l_int|4
)braket
op_assign
id|band
suffix:semicolon
id|write_or_die
c_func
(paren
id|fd
comma
id|hdr
comma
l_int|5
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
c_func
(paren
id|hdr
comma
l_string|&quot;%04x&quot;
comma
id|n
op_plus
l_int|4
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|fd
comma
id|hdr
comma
l_int|4
)paren
suffix:semicolon
)brace
id|write_or_die
c_func
(paren
id|fd
comma
id|p
comma
id|n
)paren
suffix:semicolon
id|p
op_add_assign
id|n
suffix:semicolon
id|sz
op_sub_assign
id|n
suffix:semicolon
)brace
r_return
id|ssz
suffix:semicolon
)brace
eof
