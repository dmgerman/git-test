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
r_if
c_cond
(paren
id|argc
op_eq
l_int|3
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;normalize_path_copy&quot;
)paren
)paren
(brace
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|PATH_MAX
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|rv
op_assign
id|normalize_path_copy
c_func
(paren
id|buf
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
id|buf
op_assign
l_string|&quot;++failed++&quot;
suffix:semicolon
id|puts
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ge
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;make_absolute_path&quot;
)paren
)paren
(brace
r_while
c_loop
(paren
id|argc
OG
l_int|2
)paren
(brace
id|puts
c_func
(paren
id|make_absolute_path
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|4
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;longest_ancestor_length&quot;
)paren
)paren
(brace
r_int
id|len
op_assign
id|longest_ancestor_length
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: unknown function name: %s&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
ques
c_cond
id|argv
(braket
l_int|1
)braket
suffix:colon
l_string|&quot;(there was none)&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
