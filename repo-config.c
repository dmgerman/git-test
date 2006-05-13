macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;regex.h&gt;
DECL|variable|git_config_set_usage
r_static
r_const
r_char
id|git_config_set_usage
(braket
)braket
op_assign
l_string|&quot;git-repo-config [ --bool | --int ] [--get | --get-all | --get-regexp | --replace-all | --unset | --unset-all] name [value [value_regex]] | --list&quot;
suffix:semicolon
DECL|variable|key
r_static
r_char
op_star
id|key
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|key_regexp
r_static
id|regex_t
op_star
id|key_regexp
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|regexp
r_static
id|regex_t
op_star
id|regexp
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|show_keys
r_static
r_int
id|show_keys
op_assign
l_int|0
suffix:semicolon
DECL|variable|use_key_regexp
r_static
r_int
id|use_key_regexp
op_assign
l_int|0
suffix:semicolon
DECL|variable|do_all
r_static
r_int
id|do_all
op_assign
l_int|0
suffix:semicolon
DECL|variable|do_not_match
r_static
r_int
id|do_not_match
op_assign
l_int|0
suffix:semicolon
DECL|variable|seen
r_static
r_int
id|seen
op_assign
l_int|0
suffix:semicolon
DECL|enumerator|T_RAW
DECL|enumerator|T_INT
DECL|enumerator|T_BOOL
DECL|variable|type
r_static
r_enum
(brace
id|T_RAW
comma
id|T_INT
comma
id|T_BOOL
)brace
id|type
op_assign
id|T_RAW
suffix:semicolon
DECL|function|show_all_config
r_static
r_int
id|show_all_config
c_func
(paren
r_const
r_char
op_star
id|key_
comma
r_const
r_char
op_star
id|value_
)paren
(brace
r_if
c_cond
(paren
id|value_
)paren
id|printf
c_func
(paren
l_string|&quot;%s=%s&bslash;n&quot;
comma
id|key_
comma
id|value_
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|key_
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_config
r_static
r_int
id|show_config
c_func
(paren
r_const
r_char
op_star
id|key_
comma
r_const
r_char
op_star
id|value_
)paren
(brace
r_char
id|value
(braket
l_int|256
)braket
suffix:semicolon
r_const
r_char
op_star
id|vptr
op_assign
id|value
suffix:semicolon
r_int
id|dup_error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|value_
op_eq
l_int|NULL
)paren
id|value_
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_key_regexp
op_logical_and
id|strcmp
c_func
(paren
id|key_
comma
id|key
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|use_key_regexp
op_logical_and
id|regexec
c_func
(paren
id|key_regexp
comma
id|key_
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|regexp
op_ne
l_int|NULL
op_logical_and
(paren
id|do_not_match
op_xor
id|regexec
c_func
(paren
id|regexp
comma
id|value_
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|show_keys
)paren
id|printf
c_func
(paren
l_string|&quot;%s &quot;
comma
id|key_
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seen
op_logical_and
op_logical_neg
id|do_all
)paren
id|dup_error
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|T_INT
)paren
id|sprintf
c_func
(paren
id|value
comma
l_string|&quot;%d&quot;
comma
id|git_config_int
c_func
(paren
id|key_
comma
id|value_
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|type
op_eq
id|T_BOOL
)paren
id|vptr
op_assign
id|git_config_bool
c_func
(paren
id|key_
comma
id|value_
)paren
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
suffix:semicolon
r_else
id|vptr
op_assign
id|value_
suffix:semicolon
id|seen
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dup_error
)paren
(brace
id|error
c_func
(paren
l_string|&quot;More than one value for the key %s: %s&quot;
comma
id|key_
comma
id|vptr
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|vptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_value
r_static
r_int
id|get_value
c_func
(paren
r_const
r_char
op_star
id|key_
comma
r_const
r_char
op_star
id|regex_
)paren
(brace
r_char
op_star
id|tl
suffix:semicolon
id|key
op_assign
id|strdup
c_func
(paren
id|key_
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tl
op_assign
id|key
op_plus
id|strlen
c_func
(paren
id|key
)paren
op_minus
l_int|1
suffix:semicolon
id|tl
op_ge
id|key
op_logical_and
op_star
id|tl
op_ne
l_char|&squot;.&squot;
suffix:semicolon
op_decrement
id|tl
)paren
op_star
id|tl
op_assign
id|tolower
c_func
(paren
op_star
id|tl
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tl
op_assign
id|key
suffix:semicolon
op_star
id|tl
op_logical_and
op_star
id|tl
op_ne
l_char|&squot;.&squot;
suffix:semicolon
op_increment
id|tl
)paren
op_star
id|tl
op_assign
id|tolower
c_func
(paren
op_star
id|tl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_key_regexp
)paren
(brace
id|key_regexp
op_assign
(paren
id|regex_t
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
id|regex_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regcomp
c_func
(paren
id|key_regexp
comma
id|key
comma
id|REG_EXTENDED
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Invalid key pattern: %s&bslash;n&quot;
comma
id|key_
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|regex_
)paren
(brace
r_if
c_cond
(paren
id|regex_
(braket
l_int|0
)braket
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|do_not_match
op_assign
l_int|1
suffix:semicolon
id|regex_
op_increment
suffix:semicolon
)brace
id|regexp
op_assign
(paren
id|regex_t
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
id|regex_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regcomp
c_func
(paren
id|regexp
comma
id|regex_
comma
id|REG_EXTENDED
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Invalid pattern: %s&bslash;n&quot;
comma
id|regex_
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|git_config
c_func
(paren
id|show_config
)paren
suffix:semicolon
id|free
c_func
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regexp
)paren
(brace
id|regfree
c_func
(paren
id|regexp
)paren
suffix:semicolon
id|free
c_func
(paren
id|regexp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_all
)paren
r_return
op_logical_neg
id|seen
suffix:semicolon
r_return
(paren
id|seen
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
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
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
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
l_int|1
)braket
comma
l_string|&quot;--int&quot;
)paren
)paren
id|type
op_assign
id|T_INT
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--bool&quot;
)paren
)paren
id|type
op_assign
id|T_BOOL
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--list&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-l&quot;
)paren
)paren
r_return
id|git_config
c_func
(paren
id|show_all_config
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_case
l_int|2
suffix:colon
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_int|NULL
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--unset&quot;
)paren
)paren
r_return
id|git_config_set
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
)paren
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--unset-all&quot;
)paren
)paren
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--get&quot;
)paren
)paren
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
)paren
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--get-all&quot;
)paren
)paren
(brace
id|do_all
op_assign
l_int|1
suffix:semicolon
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
)paren
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
l_int|1
)braket
comma
l_string|&quot;--get-regexp&quot;
)paren
)paren
(brace
id|show_keys
op_assign
l_int|1
suffix:semicolon
id|use_key_regexp
op_assign
l_int|1
suffix:semicolon
id|do_all
op_assign
l_int|1
suffix:semicolon
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_return
id|git_config_set
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--unset&quot;
)paren
)paren
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
comma
id|argv
(braket
l_int|3
)braket
comma
l_int|0
)paren
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--unset-all&quot;
)paren
)paren
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
comma
id|argv
(braket
l_int|3
)braket
comma
l_int|1
)paren
suffix:semicolon
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
l_int|1
)braket
comma
l_string|&quot;--get&quot;
)paren
)paren
r_return
id|get_value
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
l_int|1
)braket
comma
l_string|&quot;--get-all&quot;
)paren
)paren
(brace
id|do_all
op_assign
l_int|1
suffix:semicolon
r_return
id|get_value
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
l_int|1
)braket
comma
l_string|&quot;--get-regexp&quot;
)paren
)paren
(brace
id|show_keys
op_assign
l_int|1
suffix:semicolon
id|use_key_regexp
op_assign
l_int|1
suffix:semicolon
id|do_all
op_assign
l_int|1
suffix:semicolon
r_return
id|get_value
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
l_int|1
)braket
comma
l_string|&quot;--replace-all&quot;
)paren
)paren
r_return
id|git_config_set_multivar
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
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
r_else
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|argv
(braket
l_int|2
)braket
comma
id|argv
(braket
l_int|3
)braket
comma
l_int|0
)paren
suffix:semicolon
r_case
l_int|5
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--replace-all&quot;
)paren
)paren
r_return
id|git_config_set_multivar
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
comma
id|argv
(braket
l_int|4
)braket
comma
l_int|1
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
id|usage
c_func
(paren
id|git_config_set_usage
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
