multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
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
op_star
id|argv
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
op_logical_or
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|sha1
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;git-cat-file [-t | tagname] &lt;sha1&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-t&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
(brace
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
id|buf
op_assign
id|type
suffix:semicolon
id|size
op_assign
id|strlen
c_func
(paren
id|type
)paren
suffix:semicolon
id|type
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|size
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
id|buf
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
id|argv
(braket
l_int|1
)braket
comma
op_amp
id|size
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;git-cat-file %s: bad file&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
id|ret
op_assign
id|write
c_func
(paren
l_int|1
comma
id|buf
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
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EAGAIN
)paren
r_continue
suffix:semicolon
multiline_comment|/* Ignore epipe */
r_if
c_cond
(paren
id|errno
op_eq
id|EPIPE
)paren
r_break
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-cat-file: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|die
c_func
(paren
l_string|&quot;git-cat-file: disk full?&quot;
)paren
suffix:semicolon
)brace
id|size
op_sub_assign
id|ret
suffix:semicolon
id|buf
op_add_assign
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
