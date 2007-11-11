macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|boolean
r_static
r_int
id|boolean
op_assign
l_int|0
suffix:semicolon
DECL|variable|integer
r_static
r_int
id|integer
op_assign
l_int|0
suffix:semicolon
DECL|variable|string
r_static
r_char
op_star
id|string
op_assign
l_int|NULL
suffix:semicolon
DECL|function|main
r_int
id|main
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
)paren
(brace
r_const
r_char
op_star
id|usage
(braket
)braket
op_assign
(brace
l_string|&quot;test-parse-options &lt;options&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;b&squot;
comma
l_string|&quot;boolean&quot;
comma
op_amp
id|boolean
comma
l_string|&quot;get a boolean&quot;
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_char|&squot;i&squot;
comma
l_string|&quot;integer&quot;
comma
op_amp
id|integer
comma
l_string|&quot;get a integer&quot;
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_char|&squot;j&squot;
comma
l_int|NULL
comma
op_amp
id|integer
comma
l_string|&quot;get a integer, too&quot;
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;string options&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;s&squot;
comma
l_string|&quot;string&quot;
comma
op_amp
id|string
comma
l_string|&quot;string&quot;
comma
l_string|&quot;get a string&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;string2&quot;
comma
op_amp
id|string
comma
l_string|&quot;str&quot;
comma
l_string|&quot;get another string&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;st&quot;
comma
op_amp
id|string
comma
l_string|&quot;st&quot;
comma
l_string|&quot;get another string (pervert ordering)&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|options
comma
id|usage
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;boolean: %d&bslash;n&quot;
comma
id|boolean
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;integer: %d&bslash;n&quot;
comma
id|integer
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;string: %s&bslash;n&quot;
comma
id|string
ques
c_cond
id|string
suffix:colon
l_string|&quot;(not set)&quot;
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;arg %02d: %s&bslash;n&quot;
comma
id|i
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
