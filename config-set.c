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
l_string|&quot;git-config-set [--get | --get-all | --replace-all | --unset | --unset-all] name [value [value_regex]]&quot;
suffix:semicolon
DECL|variable|key
r_static
r_char
op_star
id|key
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|value
r_static
r_char
op_star
id|value
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|regex
r_static
id|regex_t
op_star
id|regex
op_assign
l_int|NULL
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|key_
comma
id|key
)paren
op_logical_and
(paren
id|regex
op_eq
l_int|NULL
op_logical_or
(paren
id|do_not_match
op_xor
op_logical_neg
id|regexec
c_func
(paren
id|regex
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
)paren
(brace
r_if
c_cond
(paren
id|do_all
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|value_
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|seen
OG
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;More than one value: %s&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
id|free
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
id|value
op_assign
id|strdup
c_func
(paren
id|value_
)paren
suffix:semicolon
id|seen
op_increment
suffix:semicolon
)brace
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
r_int
id|i
suffix:semicolon
id|key
op_assign
id|malloc
c_func
(paren
id|strlen
c_func
(paren
id|key_
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|key_
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|key
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|key_
(braket
id|i
)braket
)paren
suffix:semicolon
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
id|regex
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
id|regex
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
id|i
op_assign
id|git_config
c_func
(paren
id|show_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
id|free
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regex
)paren
(brace
id|regfree
c_func
(paren
id|regex
)paren
suffix:semicolon
id|free
c_func
(paren
id|regex
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_all
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|seen
op_eq
l_int|1
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
