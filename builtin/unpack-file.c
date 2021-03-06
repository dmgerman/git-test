macro_line|#include &quot;builtin.h&quot;
DECL|function|create_temp_file
r_static
r_char
op_star
id|create_temp_file
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_char
id|path
(braket
l_int|50
)braket
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|type
op_ne
id|OBJ_BLOB
)paren
id|die
c_func
(paren
l_string|&quot;unable to read blob object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|xsnprintf
c_func
(paren
id|path
comma
r_sizeof
(paren
id|path
)paren
comma
l_string|&quot;.merge_file_XXXXXX&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|xmkstemp
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
id|buf
comma
id|size
)paren
op_ne
id|size
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to write temp-file&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
DECL|function|cmd_unpack_file
r_int
id|cmd_unpack_file
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;git unpack-file &lt;sha1&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|puts
c_func
(paren
id|create_temp_file
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
