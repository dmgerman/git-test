multiline_comment|/*&n; * Copyright (c) 2005, 2006 Rene Scharfe&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tar.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|builtin_get_tar_commit_id_usage
r_static
r_const
r_char
id|builtin_get_tar_commit_id_usage
(braket
)braket
op_assign
l_string|&quot;git get-tar-commit-id &lt; &lt;tarfile&gt;&quot;
suffix:semicolon
multiline_comment|/* ustar header + extended global header content */
DECL|macro|RECORDSIZE
mdefine_line|#define RECORDSIZE&t;(512)
DECL|macro|HEADERSIZE
mdefine_line|#define HEADERSIZE (2 * RECORDSIZE)
DECL|function|cmd_get_tar_commit_id
r_int
id|cmd_get_tar_commit_id
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
r_char
id|buffer
(braket
id|HEADERSIZE
)braket
suffix:semicolon
r_struct
id|ustar_header
op_star
id|header
op_assign
(paren
r_struct
id|ustar_header
op_star
)paren
id|buffer
suffix:semicolon
r_char
op_star
id|content
op_assign
id|buffer
op_plus
id|RECORDSIZE
suffix:semicolon
id|ssize_t
id|n
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_get_tar_commit_id_usage
)paren
suffix:semicolon
id|n
op_assign
id|read_in_full
c_func
(paren
l_int|0
comma
id|buffer
comma
id|HEADERSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|HEADERSIZE
)paren
id|die
c_func
(paren
l_string|&quot;git get-tar-commit-id: read error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|header-&gt;typeflag
(braket
l_int|0
)braket
op_ne
l_char|&squot;g&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|content
comma
l_string|&quot;52 comment=&quot;
comma
l_int|11
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|n
op_assign
id|write_in_full
c_func
(paren
l_int|1
comma
id|content
op_plus
l_int|11
comma
l_int|41
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|41
)paren
id|die_errno
c_func
(paren
l_string|&quot;git get-tar-commit-id: write error&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
