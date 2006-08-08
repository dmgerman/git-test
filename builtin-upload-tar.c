multiline_comment|/*&n; * Copyright (c) 2006 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|upload_tar_usage
r_static
r_const
r_char
id|upload_tar_usage
(braket
)braket
op_assign
l_string|&quot;git-upload-tar &lt;repo&gt;&quot;
suffix:semicolon
DECL|function|nak
r_static
r_int
id|nak
c_func
(paren
r_const
r_char
op_star
id|reason
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NACK %s&bslash;n&quot;
comma
id|reason
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cmd_upload_tar
r_int
id|cmd_upload_tar
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
id|len
suffix:semicolon
r_const
r_char
op_star
id|dir
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_char
id|buf
(braket
l_int|8192
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|base
op_assign
l_int|NULL
suffix:semicolon
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
r_int
id|ac
suffix:semicolon
r_const
r_char
op_star
id|av
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage
c_func
(paren
id|upload_tar_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|dir
)paren
OL
r_sizeof
(paren
id|buf
)paren
op_minus
l_int|1
)paren
id|strcpy
c_func
(paren
id|buf
comma
id|dir
)paren
suffix:semicolon
multiline_comment|/* enter-repo smudges its argument */
r_else
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NACK insanely long repository name %s&bslash;n&quot;
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enter_repo
c_func
(paren
id|buf
comma
l_int|0
)paren
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NACK not a git archive %s&bslash;n&quot;
comma
id|dir
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|5
op_logical_or
id|strncmp
c_func
(paren
l_string|&quot;want &quot;
comma
id|buf
comma
l_int|5
)paren
)paren
r_return
id|nak
c_func
(paren
l_string|&quot;expected want&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|buf
op_plus
l_int|5
comma
id|sha1
)paren
)paren
r_return
id|nak
c_func
(paren
l_string|&quot;expected sha1&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
OL
l_int|5
op_logical_or
id|strncmp
c_func
(paren
l_string|&quot;base &quot;
comma
id|buf
comma
l_int|5
)paren
)paren
r_return
id|nak
c_func
(paren
l_string|&quot;expected (optional) base&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|base
op_assign
id|strdup
c_func
(paren
id|buf
op_plus
l_int|5
)paren
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
)paren
r_return
id|nak
c_func
(paren
l_string|&quot;expected flush&quot;
)paren
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK&bslash;n&quot;
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ac
op_assign
l_int|0
suffix:semicolon
id|av
(braket
id|ac
op_increment
)braket
op_assign
l_string|&quot;tar-tree&quot;
suffix:semicolon
id|av
(braket
id|ac
op_increment
)braket
op_assign
id|hex
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
id|av
(braket
id|ac
op_increment
)braket
op_assign
id|base
suffix:semicolon
id|av
(braket
id|ac
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|execv_git_cmd
c_func
(paren
id|av
)paren
suffix:semicolon
multiline_comment|/* should it return that is an error */
r_return
l_int|1
suffix:semicolon
)brace
eof
