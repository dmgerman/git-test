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
DECL|variable|timestamp
r_static
r_int
r_int
id|timestamp
suffix:semicolon
DECL|variable|abbrev
r_static
r_int
id|abbrev
op_assign
l_int|7
suffix:semicolon
DECL|variable|verbose
DECL|variable|dry_run
DECL|variable|quiet
r_static
r_int
id|verbose
op_assign
l_int|0
comma
id|dry_run
op_assign
l_int|0
comma
id|quiet
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
DECL|function|length_callback
r_int
id|length_callback
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Callback: &bslash;&quot;%s&bslash;&quot;, %d&bslash;n&quot;
comma
(paren
id|arg
ques
c_cond
id|arg
suffix:colon
l_string|&quot;not set&quot;
)paren
comma
id|unset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* do not support unset */
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
id|strlen
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|number_callback
r_int
id|number_callback
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
id|strtol
c_func
(paren
id|arg
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|OPT_BIT
c_func
(paren
l_char|&squot;4&squot;
comma
l_string|&quot;or4&quot;
comma
op_amp
id|boolean
comma
l_string|&quot;bitwise-or boolean with ...0100&quot;
comma
l_int|4
)paren
comma
id|OPT_NEGBIT
c_func
(paren
l_int|0
comma
l_string|&quot;neg-or4&quot;
comma
op_amp
id|boolean
comma
l_string|&quot;same as --no-or4&quot;
comma
l_int|4
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
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
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;set23&quot;
comma
op_amp
id|integer
comma
l_string|&quot;set integer to 23&quot;
comma
l_int|23
)paren
comma
id|OPT_DATE
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|NULL
comma
op_amp
id|timestamp
comma
l_string|&quot;get timestamp of &lt;time&gt;&quot;
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_char|&squot;L&squot;
comma
l_string|&quot;length&quot;
comma
op_amp
id|integer
comma
l_string|&quot;str&quot;
comma
l_string|&quot;get length of &lt;str&gt;&quot;
comma
id|length_callback
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;String options&quot;
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
id|OPT_STRING
c_func
(paren
l_char|&squot;o&squot;
comma
l_int|NULL
comma
op_amp
id|string
comma
l_string|&quot;str&quot;
comma
l_string|&quot;get another string&quot;
)paren
comma
id|OPT_SET_PTR
c_func
(paren
l_int|0
comma
l_string|&quot;default-string&quot;
comma
op_amp
id|string
comma
l_string|&quot;set string to default&quot;
comma
(paren
r_int
r_int
)paren
l_string|&quot;default&quot;
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Magic arguments&quot;
)paren
comma
id|OPT_ARGUMENT
c_func
(paren
l_string|&quot;quux&quot;
comma
l_string|&quot;means --quux&quot;
)paren
comma
id|OPT_NUMBER_CALLBACK
c_func
(paren
op_amp
id|integer
comma
l_string|&quot;set integer to NUM&quot;
comma
id|number_callback
)paren
comma
(brace
id|OPTION_BOOLEAN
comma
l_char|&squot;+&squot;
comma
l_int|NULL
comma
op_amp
id|boolean
comma
l_int|NULL
comma
l_string|&quot;same as -b&quot;
comma
id|PARSE_OPT_NOARG
op_or
id|PARSE_OPT_NONEG
op_or
id|PARSE_OPT_NODASH
)brace
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Standard options&quot;
)paren
comma
id|OPT__ABBREV
c_func
(paren
op_amp
id|abbrev
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|dry_run
)paren
comma
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
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
l_int|NULL
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
l_string|&quot;integer: %u&bslash;n&quot;
comma
id|integer
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;timestamp: %lu&bslash;n&quot;
comma
id|timestamp
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
id|printf
c_func
(paren
l_string|&quot;abbrev: %d&bslash;n&quot;
comma
id|abbrev
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;verbose: %d&bslash;n&quot;
comma
id|verbose
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;quiet: %s&bslash;n&quot;
comma
id|quiet
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;dry run: %s&bslash;n&quot;
comma
id|dry_run
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
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
