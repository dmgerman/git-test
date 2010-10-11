multiline_comment|/*&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|macro|COPY_BUFFER_LEN
mdefine_line|#define COPY_BUFFER_LEN 4096
DECL|function|buffer_init
r_int
id|buffer_init
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
comma
r_const
r_char
op_star
id|filename
)paren
(brace
id|buf-&gt;infile
op_assign
id|filename
ques
c_cond
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;r&quot;
)paren
suffix:colon
id|stdin
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf-&gt;infile
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|buffer_fdinit
r_int
id|buffer_fdinit
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
comma
r_int
id|fd
)paren
(brace
id|buf-&gt;infile
op_assign
id|fdopen
c_func
(paren
id|fd
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf-&gt;infile
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|buffer_tmpfile_init
r_int
id|buffer_tmpfile_init
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
id|buf-&gt;infile
op_assign
id|tmpfile
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf-&gt;infile
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|buffer_deinit
r_int
id|buffer_deinit
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;infile
op_eq
id|stdin
)paren
r_return
id|ferror
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
id|err
op_assign
id|ferror
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
id|err
op_or_assign
id|fclose
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|buffer_tmpfile_rewind
id|FILE
op_star
id|buffer_tmpfile_rewind
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
id|rewind
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
r_return
id|buf-&gt;infile
suffix:semicolon
)brace
DECL|function|buffer_tmpfile_prepare_to_read
r_int
id|buffer_tmpfile_prepare_to_read
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
r_int
id|pos
op_assign
id|ftell
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;ftell error: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fseek
c_func
(paren
id|buf-&gt;infile
comma
l_int|0
comma
id|SEEK_SET
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;seek error: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|pos
suffix:semicolon
)brace
DECL|function|buffer_ferror
r_int
id|buffer_ferror
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
r_return
id|ferror
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
)brace
DECL|function|buffer_read_char
r_int
id|buffer_read_char
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
r_return
id|fgetc
c_func
(paren
id|buf-&gt;infile
)paren
suffix:semicolon
)brace
multiline_comment|/* Read a line without trailing newline. */
DECL|function|buffer_read_line
r_char
op_star
id|buffer_read_line
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fgets
c_func
(paren
id|buf-&gt;line_buffer
comma
r_sizeof
(paren
id|buf-&gt;line_buffer
)paren
comma
id|buf-&gt;infile
)paren
)paren
multiline_comment|/* Error or data exhausted. */
r_return
l_int|NULL
suffix:semicolon
id|end
op_assign
id|buf-&gt;line_buffer
op_plus
id|strlen
c_func
(paren
id|buf-&gt;line_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|end
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|feof
c_func
(paren
id|buf-&gt;infile
)paren
)paren
suffix:semicolon
multiline_comment|/* No newline at end of file.  That&squot;s fine. */
r_else
multiline_comment|/*&n;&t;&t; * Line was too long.&n;&t;&t; * There is probably a saner way to deal with this,&n;&t;&t; * but for now let&squot;s return an error.&n;&t;&t; */
r_return
l_int|NULL
suffix:semicolon
r_return
id|buf-&gt;line_buffer
suffix:semicolon
)brace
DECL|function|buffer_read_string
r_char
op_star
id|buffer_read_string
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
comma
r_uint32
id|len
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf-&gt;blob_buffer
)paren
suffix:semicolon
id|strbuf_fread
c_func
(paren
op_amp
id|buf-&gt;blob_buffer
comma
id|len
comma
id|buf-&gt;infile
)paren
suffix:semicolon
r_return
id|ferror
c_func
(paren
id|buf-&gt;infile
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|buf-&gt;blob_buffer.buf
suffix:semicolon
)brace
DECL|function|buffer_read_binary
r_void
id|buffer_read_binary
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
comma
r_struct
id|strbuf
op_star
id|sb
comma
r_uint32
id|size
)paren
(brace
id|strbuf_fread
c_func
(paren
id|sb
comma
id|size
comma
id|buf-&gt;infile
)paren
suffix:semicolon
)brace
DECL|function|buffer_copy_bytes
r_void
id|buffer_copy_bytes
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
comma
r_uint32
id|len
)paren
(brace
r_char
id|byte_buffer
(braket
id|COPY_BUFFER_LEN
)braket
suffix:semicolon
r_uint32
id|in
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
op_logical_and
op_logical_neg
id|feof
c_func
(paren
id|buf-&gt;infile
)paren
op_logical_and
op_logical_neg
id|ferror
c_func
(paren
id|buf-&gt;infile
)paren
)paren
(brace
id|in
op_assign
id|len
OL
id|COPY_BUFFER_LEN
ques
c_cond
id|len
suffix:colon
id|COPY_BUFFER_LEN
suffix:semicolon
id|in
op_assign
id|fread
c_func
(paren
id|byte_buffer
comma
l_int|1
comma
id|in
comma
id|buf-&gt;infile
)paren
suffix:semicolon
id|len
op_sub_assign
id|in
suffix:semicolon
id|fwrite
c_func
(paren
id|byte_buffer
comma
l_int|1
comma
id|in
comma
id|stdout
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
(brace
id|buffer_skip_bytes
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
DECL|function|buffer_skip_bytes
r_void
id|buffer_skip_bytes
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
comma
r_uint32
id|len
)paren
(brace
r_char
id|byte_buffer
(braket
id|COPY_BUFFER_LEN
)braket
suffix:semicolon
r_uint32
id|in
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
op_logical_and
op_logical_neg
id|feof
c_func
(paren
id|buf-&gt;infile
)paren
op_logical_and
op_logical_neg
id|ferror
c_func
(paren
id|buf-&gt;infile
)paren
)paren
(brace
id|in
op_assign
id|len
OL
id|COPY_BUFFER_LEN
ques
c_cond
id|len
suffix:colon
id|COPY_BUFFER_LEN
suffix:semicolon
id|in
op_assign
id|fread
c_func
(paren
id|byte_buffer
comma
l_int|1
comma
id|in
comma
id|buf-&gt;infile
)paren
suffix:semicolon
id|len
op_sub_assign
id|in
suffix:semicolon
)brace
)brace
DECL|function|buffer_reset
r_void
id|buffer_reset
c_func
(paren
r_struct
id|line_buffer
op_star
id|buf
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buf-&gt;blob_buffer
)paren
suffix:semicolon
)brace
eof
