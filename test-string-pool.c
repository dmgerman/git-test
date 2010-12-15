multiline_comment|/*&n; * test-string-pool.c: code to exercise the svn importer&squot;s string pool&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;vcs-svn/string_pool.h&quot;
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
id|argv
(braket
)braket
)paren
(brace
r_const
r_uint32
id|unequal
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;does not equal&quot;
)paren
suffix:semicolon
r_const
r_uint32
id|equal
op_assign
id|pool_intern
c_func
(paren
l_string|&quot;equals&quot;
)paren
suffix:semicolon
r_uint32
id|buf
(braket
l_int|3
)braket
suffix:semicolon
r_uint32
id|n
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
l_string|&quot;test-string-pool &lt;string&gt;,&lt;string&gt;&quot;
)paren
suffix:semicolon
id|n
op_assign
id|pool_tok_seq
c_func
(paren
l_int|3
comma
id|buf
comma
l_string|&quot;,-&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
l_int|3
)paren
id|die
c_func
(paren
l_string|&quot;too many strings&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;too few strings&quot;
)paren
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|buf
(braket
l_int|1
)braket
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_eq
id|buf
(braket
l_int|2
)braket
)paren
ques
c_cond
id|equal
suffix:colon
id|unequal
suffix:semicolon
id|pool_print_seq
c_func
(paren
l_int|3
comma
id|buf
comma
l_char|&squot; &squot;
comma
id|stdout
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stdout
)paren
suffix:semicolon
id|pool_reset
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
