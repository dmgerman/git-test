multiline_comment|/*&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;sliding_window.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|function|input_error
r_static
r_int
id|input_error
c_func
(paren
r_struct
id|line_buffer
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_ferror
c_func
(paren
id|file
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;delta preimage ends early&quot;
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;cannot read delta preimage: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|skip_or_whine
r_static
r_int
id|skip_or_whine
c_func
(paren
r_struct
id|line_buffer
op_star
id|file
comma
id|off_t
id|gap
)paren
(brace
r_if
c_cond
(paren
id|buffer_skip_bytes
c_func
(paren
id|file
comma
id|gap
)paren
op_ne
id|gap
)paren
r_return
id|input_error
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_to_fill_or_whine
r_static
r_int
id|read_to_fill_or_whine
c_func
(paren
r_struct
id|line_buffer
op_star
id|file
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|width
)paren
(brace
id|buffer_read_binary
c_func
(paren
id|file
comma
id|buf
comma
id|width
id|buf-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;len
op_ne
id|width
)paren
r_return
id|input_error
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_overflow
r_static
r_int
id|check_overflow
c_func
(paren
id|off_t
id|a
comma
r_int
id|b
)paren
(brace
r_if
c_cond
(paren
id|b
OG
id|maximum_signed_value_of_type
c_func
(paren
id|off_t
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unrepresentable length in delta: &quot;
l_string|&quot;%&quot;
id|PRIuMAX
l_string|&quot; &gt; OFF_MAX&quot;
comma
(paren
r_uintmax
)paren
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signed_add_overflows
c_func
(paren
id|a
comma
(paren
id|off_t
)paren
id|b
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unrepresentable offset in delta: &quot;
l_string|&quot;%&quot;
id|PRIuMAX
l_string|&quot; + %&quot;
id|PRIuMAX
l_string|&quot; &gt; OFF_MAX&quot;
comma
(paren
r_uintmax
)paren
id|a
comma
(paren
r_uintmax
)paren
id|b
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|move_window
r_int
id|move_window
c_func
(paren
r_struct
id|sliding_view
op_star
id|view
comma
id|off_t
id|off
comma
r_int
id|width
)paren
(brace
id|off_t
id|file_offset
suffix:semicolon
m_assert
(paren
id|view
)paren
suffix:semicolon
m_assert
(paren
id|view-&gt;width
op_le
id|view-&gt;buf.len
)paren
suffix:semicolon
m_assert
(paren
op_logical_neg
id|check_overflow
c_func
(paren
id|view-&gt;off
comma
id|view-&gt;buf.len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_overflow
c_func
(paren
id|off
comma
id|width
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|off
OL
id|view-&gt;off
op_logical_or
id|off
op_plus
id|width
OL
id|view-&gt;off
op_plus
id|view-&gt;width
)paren
r_return
id|error
c_func
(paren
l_string|&quot;invalid delta: window slides left&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|view-&gt;max_off
op_ge
l_int|0
op_logical_and
id|view-&gt;max_off
OL
id|off
op_plus
id|width
)paren
r_return
id|error
c_func
(paren
l_string|&quot;delta preimage ends early&quot;
)paren
suffix:semicolon
id|file_offset
op_assign
id|view-&gt;off
op_plus
id|view-&gt;buf.len
suffix:semicolon
r_if
c_cond
(paren
id|off
OL
id|file_offset
)paren
(brace
multiline_comment|/* Move the overlapping region into place. */
id|strbuf_remove
c_func
(paren
op_amp
id|view-&gt;buf
comma
l_int|0
comma
id|off
id|view-&gt;off
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Seek ahead to skip the gap. */
r_if
c_cond
(paren
id|skip_or_whine
c_func
(paren
id|view-&gt;file
comma
id|off
id|file_offset
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|view-&gt;buf
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|view-&gt;buf.len
OG
id|width
)paren
suffix:semicolon
multiline_comment|/* Already read. */
r_else
r_if
c_cond
(paren
id|read_to_fill_or_whine
c_func
(paren
id|view-&gt;file
comma
op_amp
id|view-&gt;buf
comma
id|width
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|view-&gt;off
op_assign
id|off
suffix:semicolon
id|view-&gt;width
op_assign
id|width
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
