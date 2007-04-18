macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|check_attr_usage
r_static
r_const
r_char
id|check_attr_usage
(braket
)braket
op_assign
l_string|&quot;git-check-attr attr... [--] pathname...&quot;
suffix:semicolon
DECL|function|cmd_check_attr
r_int
id|cmd_check_attr
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
r_struct
id|git_attr_check
op_star
id|check
suffix:semicolon
r_int
id|cnt
comma
id|i
comma
id|doubledash
suffix:semicolon
id|doubledash
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|doubledash
OL
l_int|0
op_logical_and
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
id|doubledash
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/* If there is no double dash, we handle only one attribute */
r_if
c_cond
(paren
id|doubledash
OL
l_int|0
)paren
(brace
id|cnt
op_assign
l_int|1
suffix:semicolon
id|doubledash
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|cnt
op_assign
id|doubledash
l_int|1
suffix:semicolon
id|doubledash
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_le
l_int|0
op_logical_or
id|argc
OL
id|doubledash
)paren
id|usage
c_func
(paren
id|check_attr_usage
)paren
suffix:semicolon
id|check
op_assign
id|xcalloc
c_func
(paren
id|cnt
comma
r_sizeof
(paren
op_star
id|check
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_struct
id|git_attr
op_star
id|a
suffix:semicolon
id|name
op_assign
id|argv
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|a
op_assign
id|git_attr
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: not a valid attribute name&quot;
comma
id|name
)paren
suffix:semicolon
id|check
(braket
id|i
)braket
dot
id|attr
op_assign
id|a
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|doubledash
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|git_checkattr
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|cnt
comma
id|check
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git_checkattr died&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|check
(braket
id|j
)braket
dot
id|value
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;set&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_FALSE
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;unset&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_UNSET
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;unspecified&quot;
suffix:semicolon
id|write_name_quoted
c_func
(paren
l_string|&quot;&quot;
comma
l_int|0
comma
id|argv
(braket
id|i
)braket
comma
l_int|1
comma
id|stdout
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;: %s: %s&bslash;n&quot;
comma
id|argv
(braket
id|j
op_plus
l_int|1
)braket
comma
id|value
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
