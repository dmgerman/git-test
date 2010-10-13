multiline_comment|/*&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;sliding_window.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;svndiff.h&quot;
multiline_comment|/*&n; * svndiff0 applier&n; *&n; * See http://svn.apache.org/repos/asf/subversion/trunk/notes/svndiff.&n; *&n; * svndiff0 ::= &squot;SVN&bslash;0&squot; window*&n; * window ::= int int int int int instructions inline_data;&n; * instructions ::= instruction*;&n; * instruction ::= view_selector int int&n; *   | copyfrom_data int&n; *   | packed_view_selector int&n; *   | packed_copyfrom_data&n; *   ;&n; * copyfrom_data ::= # binary 10 000000;&n; * packed_copyfrom_data ::= # copyfrom_data OR-ed with 6 bit value;&n; * int ::= highdigit* lowdigit;&n; * highdigit ::= # binary 1000 0000 OR-ed with 7 bit value;&n; * lowdigit ::= # 7 bit value;&n; */
DECL|macro|INSN_MASK
mdefine_line|#define INSN_MASK&t;0xc0
DECL|macro|INSN_COPYFROM_DATA
mdefine_line|#define INSN_COPYFROM_DATA&t;0x80
DECL|macro|OPERAND_MASK
mdefine_line|#define OPERAND_MASK&t;0x3f
DECL|macro|VLI_CONTINUE
mdefine_line|#define VLI_CONTINUE&t;0x80
DECL|macro|VLI_DIGIT_MASK
mdefine_line|#define VLI_DIGIT_MASK&t;0x7f
DECL|macro|VLI_BITS_PER_DIGIT
mdefine_line|#define VLI_BITS_PER_DIGIT 7
DECL|struct|window
r_struct
id|window
(brace
DECL|member|out
r_struct
id|strbuf
id|out
suffix:semicolon
DECL|member|instructions
r_struct
id|strbuf
id|instructions
suffix:semicolon
DECL|member|data
r_struct
id|strbuf
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|WINDOW_INIT
mdefine_line|#define WINDOW_INIT&t;{ STRBUF_INIT, STRBUF_INIT, STRBUF_INIT }
DECL|function|window_release
r_static
r_void
id|window_release
c_func
(paren
r_struct
id|window
op_star
id|ctx
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|ctx-&gt;out
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|ctx-&gt;instructions
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|ctx-&gt;data
)paren
suffix:semicolon
)brace
DECL|function|write_strbuf
r_static
r_int
id|write_strbuf
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
id|FILE
op_star
id|out
)paren
(brace
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|sb-&gt;buf
comma
l_int|1
comma
id|sb-&gt;len
comma
id|out
)paren
op_eq
id|sb-&gt;len
)paren
multiline_comment|/* Success. */
r_return
l_int|0
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;cannot write delta postimage: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|error_short_read
r_static
r_int
id|error_short_read
c_func
(paren
r_struct
id|line_buffer
op_star
id|input
)paren
(brace
r_if
c_cond
(paren
id|buffer_ferror
c_func
(paren
id|input
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;error reading delta: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;invalid delta: unexpected end of file&quot;
)paren
suffix:semicolon
)brace
DECL|function|read_chunk
r_static
r_int
id|read_chunk
c_func
(paren
r_struct
id|line_buffer
op_star
id|delta
comma
id|off_t
op_star
id|delta_len
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|strbuf_reset
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
op_star
id|delta_len
op_logical_or
id|buffer_read_binary
c_func
(paren
id|delta
comma
id|buf
comma
id|len
)paren
op_ne
id|len
)paren
r_return
id|error_short_read
c_func
(paren
id|delta
)paren
suffix:semicolon
op_star
id|delta_len
op_sub_assign
id|buf-&gt;len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_magic
r_static
r_int
id|read_magic
c_func
(paren
r_struct
id|line_buffer
op_star
id|in
comma
id|off_t
op_star
id|len
)paren
(brace
r_static
r_const
r_char
id|magic
(braket
)braket
op_assign
(brace
l_char|&squot;S&squot;
comma
l_char|&squot;V&squot;
comma
l_char|&squot;N&squot;
comma
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|read_chunk
c_func
(paren
id|in
comma
id|len
comma
op_amp
id|sb
comma
r_sizeof
(paren
id|magic
)paren
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sb.buf
comma
id|magic
comma
r_sizeof
(paren
id|magic
)paren
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;invalid delta: unrecognized file type&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_int
r_static
r_int
id|read_int
c_func
(paren
r_struct
id|line_buffer
op_star
id|in
comma
r_uintmax
op_star
id|result
comma
id|off_t
op_star
id|len
)paren
(brace
r_uintmax
id|rv
op_assign
l_int|0
suffix:semicolon
id|off_t
id|sz
suffix:semicolon
r_for
c_loop
(paren
id|sz
op_assign
op_star
id|len
suffix:semicolon
id|sz
suffix:semicolon
id|sz
op_decrement
)paren
(brace
r_const
r_int
id|ch
op_assign
id|buffer_read_char
c_func
(paren
id|in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
id|EOF
)paren
r_break
suffix:semicolon
id|rv
op_lshift_assign
id|VLI_BITS_PER_DIGIT
suffix:semicolon
id|rv
op_add_assign
(paren
id|ch
op_amp
id|VLI_DIGIT_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_amp
id|VLI_CONTINUE
)paren
r_continue
suffix:semicolon
op_star
id|result
op_assign
id|rv
suffix:semicolon
op_star
id|len
op_assign
id|sz
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|error_short_read
c_func
(paren
id|in
)paren
suffix:semicolon
)brace
DECL|function|parse_int
r_static
r_int
id|parse_int
c_func
(paren
r_const
r_char
op_star
op_star
id|buf
comma
r_int
op_star
id|result
comma
r_const
r_char
op_star
id|end
)paren
(brace
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|pos
suffix:semicolon
r_for
c_loop
(paren
id|pos
op_assign
op_star
id|buf
suffix:semicolon
id|pos
op_ne
id|end
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_int
r_char
id|ch
op_assign
op_star
id|pos
suffix:semicolon
id|rv
op_lshift_assign
id|VLI_BITS_PER_DIGIT
suffix:semicolon
id|rv
op_add_assign
(paren
id|ch
op_amp
id|VLI_DIGIT_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_amp
id|VLI_CONTINUE
)paren
r_continue
suffix:semicolon
op_star
id|result
op_assign
id|rv
suffix:semicolon
op_star
id|buf
op_assign
id|pos
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;invalid delta: unexpected end of instructions section&quot;
)paren
suffix:semicolon
)brace
DECL|function|read_offset
r_static
r_int
id|read_offset
c_func
(paren
r_struct
id|line_buffer
op_star
id|in
comma
id|off_t
op_star
id|result
comma
id|off_t
op_star
id|len
)paren
(brace
r_uintmax
id|val
suffix:semicolon
r_if
c_cond
(paren
id|read_int
c_func
(paren
id|in
comma
op_amp
id|val
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|val
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
l_string|&quot;unrepresentable offset in delta: %&quot;
id|PRIuMAX
l_string|&quot;&quot;
comma
id|val
)paren
suffix:semicolon
op_star
id|result
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_length
r_static
r_int
id|read_length
c_func
(paren
r_struct
id|line_buffer
op_star
id|in
comma
r_int
op_star
id|result
comma
id|off_t
op_star
id|len
)paren
(brace
r_uintmax
id|val
suffix:semicolon
r_if
c_cond
(paren
id|read_int
c_func
(paren
id|in
comma
op_amp
id|val
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
id|SIZE_MAX
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unrepresentable length in delta: %&quot;
id|PRIuMAX
l_string|&quot;&quot;
comma
id|val
)paren
suffix:semicolon
op_star
id|result
op_assign
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copyfrom_data
r_static
r_int
id|copyfrom_data
c_func
(paren
r_struct
id|window
op_star
id|ctx
comma
r_int
op_star
id|data_pos
comma
r_int
id|nbytes
)paren
(brace
r_const
r_int
id|pos
op_assign
op_star
id|data_pos
suffix:semicolon
r_if
c_cond
(paren
id|unsigned_add_overflows
c_func
(paren
id|pos
comma
id|nbytes
)paren
op_logical_or
id|pos
op_plus
id|nbytes
OG
id|ctx-&gt;data.len
)paren
r_return
id|error
c_func
(paren
l_string|&quot;invalid delta: copies unavailable inline data&quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|ctx-&gt;out
comma
id|ctx-&gt;data.buf
op_plus
id|pos
comma
id|nbytes
)paren
suffix:semicolon
op_star
id|data_pos
op_add_assign
id|nbytes
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_first_operand
r_static
r_int
id|parse_first_operand
c_func
(paren
r_const
r_char
op_star
op_star
id|buf
comma
r_int
op_star
id|out
comma
r_const
r_char
op_star
id|end
)paren
(brace
r_int
id|result
op_assign
(paren
r_int
r_char
)paren
op_star
(paren
op_star
id|buf
)paren
op_increment
op_amp
id|OPERAND_MASK
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
multiline_comment|/* immediate operand */
op_star
id|out
op_assign
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|parse_int
c_func
(paren
id|buf
comma
id|out
comma
id|end
)paren
suffix:semicolon
)brace
DECL|function|execute_one_instruction
r_static
r_int
id|execute_one_instruction
c_func
(paren
r_struct
id|window
op_star
id|ctx
comma
r_const
r_char
op_star
op_star
id|instructions
comma
r_int
op_star
id|data_pos
)paren
(brace
r_int
r_int
id|instruction
suffix:semicolon
r_const
r_char
op_star
id|insns_end
op_assign
id|ctx-&gt;instructions.buf
op_plus
id|ctx-&gt;instructions.len
suffix:semicolon
r_int
id|nbytes
suffix:semicolon
m_assert
(paren
id|ctx
)paren
suffix:semicolon
m_assert
(paren
id|instructions
op_logical_and
op_star
id|instructions
)paren
suffix:semicolon
m_assert
(paren
id|data_pos
)paren
suffix:semicolon
id|instruction
op_assign
(paren
r_int
r_char
)paren
op_star
op_star
id|instructions
suffix:semicolon
r_if
c_cond
(paren
id|parse_first_operand
c_func
(paren
id|instructions
comma
op_amp
id|nbytes
comma
id|insns_end
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|instruction
op_amp
id|INSN_MASK
)paren
op_ne
id|INSN_COPYFROM_DATA
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Unknown instruction %x&quot;
comma
id|instruction
)paren
suffix:semicolon
r_return
id|copyfrom_data
c_func
(paren
id|ctx
comma
id|data_pos
comma
id|nbytes
)paren
suffix:semicolon
)brace
DECL|function|apply_window_in_core
r_static
r_int
id|apply_window_in_core
c_func
(paren
r_struct
id|window
op_star
id|ctx
)paren
(brace
r_const
r_char
op_star
id|instructions
suffix:semicolon
r_int
id|data_pos
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Fill ctx-&gt;out.buf using data from the source, target,&n;&t; * and inline data views.&n;&t; */
r_for
c_loop
(paren
id|instructions
op_assign
id|ctx-&gt;instructions.buf
suffix:semicolon
id|instructions
op_ne
id|ctx-&gt;instructions.buf
op_plus
id|ctx-&gt;instructions.len
suffix:semicolon
)paren
r_if
c_cond
(paren
id|execute_one_instruction
c_func
(paren
id|ctx
comma
op_amp
id|instructions
comma
op_amp
id|data_pos
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|apply_one_window
r_static
r_int
id|apply_one_window
c_func
(paren
r_struct
id|line_buffer
op_star
id|delta
comma
id|off_t
op_star
id|delta_len
comma
id|FILE
op_star
id|out
)paren
(brace
r_struct
id|window
id|ctx
op_assign
id|WINDOW_INIT
suffix:semicolon
r_int
id|out_len
suffix:semicolon
r_int
id|instructions_len
suffix:semicolon
r_int
id|data_len
suffix:semicolon
m_assert
(paren
id|delta_len
)paren
suffix:semicolon
multiline_comment|/* &quot;source view&quot; offset and length already handled; */
r_if
c_cond
(paren
id|read_length
c_func
(paren
id|delta
comma
op_amp
id|out_len
comma
id|delta_len
)paren
op_logical_or
id|read_length
c_func
(paren
id|delta
comma
op_amp
id|instructions_len
comma
id|delta_len
)paren
op_logical_or
id|read_length
c_func
(paren
id|delta
comma
op_amp
id|data_len
comma
id|delta_len
)paren
op_logical_or
id|read_chunk
c_func
(paren
id|delta
comma
id|delta_len
comma
op_amp
id|ctx.instructions
comma
id|instructions_len
)paren
op_logical_or
id|read_chunk
c_func
(paren
id|delta
comma
id|delta_len
comma
op_amp
id|ctx.data
comma
id|data_len
)paren
)paren
r_goto
id|error_out
suffix:semicolon
id|strbuf_grow
c_func
(paren
op_amp
id|ctx.out
comma
id|out_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apply_window_in_core
c_func
(paren
op_amp
id|ctx
)paren
)paren
r_goto
id|error_out
suffix:semicolon
r_if
c_cond
(paren
id|ctx.out.len
op_ne
id|out_len
)paren
(brace
id|error
c_func
(paren
l_string|&quot;invalid delta: incorrect postimage length&quot;
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_strbuf
c_func
(paren
op_amp
id|ctx.out
comma
id|out
)paren
)paren
r_goto
id|error_out
suffix:semicolon
id|window_release
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_out
suffix:colon
id|window_release
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|svndiff0_apply
r_int
id|svndiff0_apply
c_func
(paren
r_struct
id|line_buffer
op_star
id|delta
comma
id|off_t
id|delta_len
comma
r_struct
id|sliding_view
op_star
id|preimage
comma
id|FILE
op_star
id|postimage
)paren
(brace
m_assert
(paren
id|delta
op_logical_and
id|preimage
op_logical_and
id|postimage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_magic
c_func
(paren
id|delta
comma
op_amp
id|delta_len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|delta_len
)paren
(brace
multiline_comment|/* For each window: */
id|off_t
id|pre_off
suffix:semicolon
r_int
id|pre_len
suffix:semicolon
r_if
c_cond
(paren
id|read_offset
c_func
(paren
id|delta
comma
op_amp
id|pre_off
comma
op_amp
id|delta_len
)paren
op_logical_or
id|read_length
c_func
(paren
id|delta
comma
op_amp
id|pre_len
comma
op_amp
id|delta_len
)paren
op_logical_or
id|move_window
c_func
(paren
id|preimage
comma
id|pre_off
comma
id|pre_len
)paren
op_logical_or
id|apply_one_window
c_func
(paren
id|delta
comma
op_amp
id|delta_len
comma
id|postimage
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
