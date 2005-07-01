macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
DECL|function|verify_one_pack
r_static
r_int
id|verify_one_pack
c_func
(paren
r_char
op_star
id|arg
comma
r_int
id|verbose
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|arg
)paren
suffix:semicolon
r_struct
id|packed_git
op_star
id|g
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* Should name foo.idx, but foo.pack may be named;&n;&t;&t; * convert it to foo.idx&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
op_plus
id|len
l_int|5
comma
l_string|&quot;.pack&quot;
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|arg
op_plus
id|len
l_int|5
comma
l_string|&quot;.idx&quot;
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Should name foo.idx now */
r_if
c_cond
(paren
(paren
id|g
op_assign
id|add_packed_git
c_func
(paren
id|arg
comma
id|len
)paren
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* No?  did you name just foo? */
id|strcpy
c_func
(paren
id|arg
op_plus
id|len
comma
l_string|&quot;.idx&quot;
)paren
suffix:semicolon
id|len
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|g
op_assign
id|add_packed_git
c_func
(paren
id|arg
comma
id|len
)paren
)paren
)paren
r_break
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;packfile %s not found.&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
r_return
id|verify_pack
c_func
(paren
id|g
comma
id|verbose
)paren
suffix:semicolon
)brace
DECL|variable|verify_pack_usage
r_static
r_const
r_char
op_star
id|verify_pack_usage
op_assign
l_string|&quot;git-verify-pack [-v] &lt;pack&gt;...&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_char
op_star
op_star
id|av
)paren
(brace
r_int
id|errs
op_assign
l_int|0
suffix:semicolon
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
r_int
id|no_more_options
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|ac
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_more_options
op_logical_and
id|av
(braket
l_int|1
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
l_string|&quot;-v&quot;
comma
id|av
(braket
l_int|1
)braket
)paren
)paren
id|verbose
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--&quot;
comma
id|av
(braket
l_int|1
)braket
)paren
)paren
id|no_more_options
op_assign
l_int|1
suffix:semicolon
r_else
id|usage
c_func
(paren
id|verify_pack_usage
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|path
comma
id|av
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify_one_pack
c_func
(paren
id|path
comma
id|verbose
)paren
)paren
id|errs
op_increment
suffix:semicolon
)brace
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
op_logical_neg
id|errs
suffix:semicolon
)brace
eof
