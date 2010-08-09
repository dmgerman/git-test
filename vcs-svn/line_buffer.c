multiline_comment|/*&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;obj_pool.h&quot;
DECL|macro|LINE_BUFFER_LEN
mdefine_line|#define LINE_BUFFER_LEN 10000
DECL|macro|COPY_BUFFER_LEN
mdefine_line|#define COPY_BUFFER_LEN 4096
multiline_comment|/* Create memory pool for char sequence of known length */
id|obj_pool_gen
c_func
(paren
id|blob
comma
r_char
comma
l_int|4096
)paren
DECL|variable|line_buffer
r_static
r_char
id|line_buffer
(braket
id|LINE_BUFFER_LEN
)braket
suffix:semicolon
DECL|variable|byte_buffer
r_static
r_char
id|byte_buffer
(braket
id|COPY_BUFFER_LEN
)braket
suffix:semicolon
DECL|variable|infile
r_static
id|FILE
op_star
id|infile
suffix:semicolon
DECL|function|buffer_init
r_int
id|buffer_init
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
(brace
id|infile
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
id|infile
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
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|infile
op_eq
id|stdin
)paren
r_return
id|ferror
c_func
(paren
id|infile
)paren
suffix:semicolon
id|err
op_assign
id|ferror
c_func
(paren
id|infile
)paren
suffix:semicolon
id|err
op_or_assign
id|fclose
c_func
(paren
id|infile
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Read a line without trailing newline. */
DECL|function|buffer_read_line
r_char
op_star
id|buffer_read_line
c_func
(paren
r_void
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
id|line_buffer
comma
r_sizeof
(paren
id|line_buffer
)paren
comma
id|infile
)paren
)paren
multiline_comment|/* Error or data exhausted. */
r_return
l_int|NULL
suffix:semicolon
id|end
op_assign
id|line_buffer
op_plus
id|strlen
c_func
(paren
id|line_buffer
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
id|infile
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
id|line_buffer
suffix:semicolon
)brace
DECL|function|buffer_read_string
r_char
op_star
id|buffer_read_string
c_func
(paren
r_uint32
id|len
)paren
(brace
r_char
op_star
id|s
suffix:semicolon
id|blob_free
c_func
(paren
id|blob_pool.size
)paren
suffix:semicolon
id|s
op_assign
id|blob_pointer
c_func
(paren
id|blob_alloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|s
(braket
id|fread
c_func
(paren
id|s
comma
l_int|1
comma
id|len
comma
id|infile
)paren
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|ferror
c_func
(paren
id|infile
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|s
suffix:semicolon
)brace
DECL|function|buffer_copy_bytes
r_void
id|buffer_copy_bytes
c_func
(paren
r_uint32
id|len
)paren
(brace
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
id|infile
)paren
op_logical_and
op_logical_neg
id|ferror
c_func
(paren
id|infile
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
id|infile
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
r_uint32
id|len
)paren
(brace
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
id|infile
)paren
op_logical_and
op_logical_neg
id|ferror
c_func
(paren
id|infile
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
id|infile
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
r_void
)paren
(brace
id|blob_reset
c_func
(paren
)paren
suffix:semicolon
)brace
eof
