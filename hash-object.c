multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; * Copyright (C) Junio C Hamano, 2005 &n; */
macro_line|#include &quot;cache.h&quot;
DECL|function|hash_object
r_static
r_void
id|hash_object
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|type
comma
r_int
id|write_object
)paren
(brace
r_int
id|fd
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
OL
l_int|0
op_logical_or
id|index_fd
c_func
(paren
id|sha1
comma
id|fd
comma
op_amp
id|st
comma
id|write_object
comma
id|type
)paren
)paren
id|die
c_func
(paren
id|write_object
ques
c_cond
l_string|&quot;Unable to add %s to database&quot;
suffix:colon
l_string|&quot;Unable to hash %s&quot;
comma
id|path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
DECL|variable|hash_object_usage
r_static
r_const
r_char
id|hash_object_usage
(braket
)braket
op_assign
l_string|&quot;git-hash-object [-t &lt;type&gt;] [-w] &lt;file&gt;...&quot;
suffix:semicolon
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
id|i
suffix:semicolon
r_const
r_char
op_star
id|type
op_assign
l_string|&quot;blob&quot;
suffix:semicolon
r_int
id|write_object
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
l_int|NULL
suffix:semicolon
r_int
id|prefix_length
op_assign
l_int|1
suffix:semicolon
r_int
id|no_more_flags
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|no_more_flags
op_logical_and
id|argv
(braket
id|i
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-t&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
op_le
op_increment
id|i
)paren
id|die
c_func
(paren
id|hash_object_usage
)paren
suffix:semicolon
id|type
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-w&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|prefix_length
OL
l_int|0
)paren
(brace
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|prefix_length
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
id|write_object
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|no_more_flags
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--help&quot;
)paren
)paren
id|usage
c_func
(paren
id|hash_object_usage
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
id|hash_object_usage
)paren
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|prefix_length
)paren
id|arg
op_assign
id|prefix_filename
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|arg
)paren
suffix:semicolon
id|hash_object
c_func
(paren
id|arg
comma
id|type
comma
id|write_object
)paren
suffix:semicolon
id|no_more_flags
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
