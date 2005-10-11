macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|macro|MAXNAME
mdefine_line|#define MAXNAME (256)
DECL|variable|config_file
r_static
id|FILE
op_star
id|config_file
suffix:semicolon
DECL|variable|config_linenr
r_static
r_int
id|config_linenr
suffix:semicolon
DECL|function|get_next_char
r_static
r_int
id|get_next_char
c_func
(paren
r_void
)paren
(brace
r_int
id|c
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
id|c
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|f
op_assign
id|config_file
)paren
op_ne
l_int|NULL
)paren
(brace
id|c
op_assign
id|fgetc
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|config_linenr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
(brace
id|config_file
op_assign
l_int|NULL
suffix:semicolon
id|c
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
)brace
r_return
id|c
suffix:semicolon
)brace
DECL|function|parse_value
r_static
r_char
op_star
id|parse_value
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|value
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|quote
op_assign
l_int|0
comma
id|comment
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
comma
id|space
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|c
op_assign
id|get_next_char
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
r_sizeof
(paren
id|value
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
id|quote
)paren
r_return
l_int|NULL
suffix:semicolon
id|value
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
r_if
c_cond
(paren
id|comment
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|c
)paren
op_logical_and
op_logical_neg
id|quote
)paren
(brace
id|space
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|space
)paren
(brace
r_if
c_cond
(paren
id|len
)paren
id|value
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|space
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
id|c
op_assign
id|get_next_char
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
r_continue
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
id|c
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
id|c
op_assign
l_char|&squot;&bslash;b&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
id|c
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Some characters escape as themselves */
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
r_case
l_char|&squot;&quot;&squot;
suffix:colon
r_break
suffix:semicolon
multiline_comment|/* Reject unknown escape sequences */
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
id|value
(braket
id|len
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
id|quote
op_assign
l_int|1
op_minus
id|quote
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|quote
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
op_logical_or
id|c
op_eq
l_char|&squot;#&squot;
)paren
(brace
id|comment
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|value
(braket
id|len
op_increment
)braket
op_assign
id|c
suffix:semicolon
)brace
)brace
DECL|function|get_value
r_static
r_int
id|get_value
c_func
(paren
id|config_fn_t
id|fn
comma
r_char
op_star
id|name
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|c
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
multiline_comment|/* Get the full name */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
id|get_next_char
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isalnum
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|name
(braket
id|len
op_increment
)braket
op_assign
id|tolower
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|MAXNAME
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_or
id|c
op_eq
l_char|&squot;&bslash;t&squot;
)paren
id|c
op_assign
id|get_next_char
c_func
(paren
)paren
suffix:semicolon
id|value
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;=&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|value
op_assign
id|parse_value
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|fn
c_func
(paren
id|name
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|get_base_var
r_static
r_int
id|get_base_var
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|baselen
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|c
op_assign
id|get_next_char
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;]&squot;
)paren
r_return
id|baselen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isalnum
c_func
(paren
id|c
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|baselen
OG
id|MAXNAME
op_div
l_int|2
)paren
r_return
l_int|1
suffix:semicolon
id|name
(braket
id|baselen
op_increment
)braket
op_assign
id|tolower
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
DECL|function|git_parse_file
r_static
r_int
id|git_parse_file
c_func
(paren
id|config_fn_t
id|fn
)paren
(brace
r_int
id|comment
op_assign
l_int|0
suffix:semicolon
r_int
id|baselen
op_assign
l_int|0
suffix:semicolon
r_static
r_char
id|var
(braket
id|MAXNAME
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|c
op_assign
id|get_next_char
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* EOF? */
r_if
c_cond
(paren
op_logical_neg
id|config_file
)paren
r_return
l_int|0
suffix:semicolon
id|comment
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|comment
op_logical_or
id|isspace
c_func
(paren
id|c
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;#&squot;
op_logical_or
id|c
op_eq
l_char|&squot;;&squot;
)paren
(brace
id|comment
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;[&squot;
)paren
(brace
id|baselen
op_assign
id|get_base_var
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baselen
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|var
(braket
id|baselen
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
id|var
(braket
id|baselen
)braket
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isalpha
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|var
(braket
id|baselen
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_value
c_func
(paren
id|fn
comma
id|var
comma
id|baselen
op_plus
l_int|1
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;bad config file line %d&quot;
comma
id|config_linenr
)paren
suffix:semicolon
)brace
DECL|function|git_config_int
r_int
id|git_config_int
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
op_logical_and
op_star
id|value
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_int
id|val
op_assign
id|strtol
c_func
(paren
id|value
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|end
)paren
r_return
id|val
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;bad config value for &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|git_config_bool
r_int
id|git_config_bool
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|value
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;true&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;false&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|git_config_int
c_func
(paren
id|name
comma
id|value
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|git_default_config
r_int
id|git_default_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
)paren
(brace
multiline_comment|/* This needs a better name */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.filemode&quot;
)paren
)paren
(brace
id|trust_executable_bit
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Add other config variables here.. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_config
r_int
id|git_config
c_func
(paren
id|config_fn_t
id|fn
)paren
(brace
r_int
id|ret
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;config&quot;
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|f
)paren
(brace
id|config_file
op_assign
id|f
suffix:semicolon
id|config_linenr
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|git_parse_file
c_func
(paren
id|fn
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
