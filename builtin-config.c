macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;color.h&quot;
DECL|variable|git_config_set_usage
r_static
r_const
r_char
id|git_config_set_usage
(braket
)braket
op_assign
l_string|&quot;git config [ --global | --system | [ -f | --file ] config-file ] [ --bool | --int | --bool-or-int ] [ -z | --null ] [--get | --get-all | --get-regexp | --replace-all | --add | --unset | --unset-all] name [value [value_regex]] | --rename-section old_name new_name | --remove-section name | --list | --get-color var [default] | --get-colorbool name [stdout-is-tty] | --edit | -e ]&quot;
suffix:semicolon
DECL|variable|key
r_static
r_char
op_star
id|key
suffix:semicolon
DECL|variable|key_regexp
r_static
id|regex_t
op_star
id|key_regexp
suffix:semicolon
DECL|variable|regexp
r_static
id|regex_t
op_star
id|regexp
suffix:semicolon
DECL|variable|show_keys
r_static
r_int
id|show_keys
suffix:semicolon
DECL|variable|use_key_regexp
r_static
r_int
id|use_key_regexp
suffix:semicolon
DECL|variable|do_all
r_static
r_int
id|do_all
suffix:semicolon
DECL|variable|do_not_match
r_static
r_int
id|do_not_match
suffix:semicolon
DECL|variable|seen
r_static
r_int
id|seen
suffix:semicolon
DECL|variable|delim
r_static
r_char
id|delim
op_assign
l_char|&squot;=&squot;
suffix:semicolon
DECL|variable|key_delim
r_static
r_char
id|key_delim
op_assign
l_char|&squot; &squot;
suffix:semicolon
DECL|variable|term
r_static
r_char
id|term
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|enumerator|T_RAW
DECL|enumerator|T_INT
DECL|enumerator|T_BOOL
DECL|enumerator|T_BOOL_OR_INT
DECL|variable|type
r_static
r_enum
(brace
id|T_RAW
comma
id|T_INT
comma
id|T_BOOL
comma
id|T_BOOL_OR_INT
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
comma
r_void
op_star
id|cb
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
l_string|&quot;%s%c%s%c&quot;
comma
id|key_
comma
id|delim
comma
id|value_
comma
id|term
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|key_
comma
id|term
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
comma
r_void
op_star
id|cb
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
op_logical_neg
op_logical_neg
id|regexec
c_func
(paren
id|regexp
comma
(paren
id|value_
ques
c_cond
id|value_
suffix:colon
l_string|&quot;&quot;
)paren
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
(brace
r_if
c_cond
(paren
id|value_
)paren
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|key_
comma
id|key_delim
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|key_
)paren
suffix:semicolon
)brace
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
ques
c_cond
id|value_
suffix:colon
l_string|&quot;&quot;
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
r_if
c_cond
(paren
id|type
op_eq
id|T_BOOL_OR_INT
)paren
(brace
r_int
id|is_bool
comma
id|v
suffix:semicolon
id|v
op_assign
id|git_config_bool_or_int
c_func
(paren
id|key_
comma
id|value_
comma
op_amp
id|is_bool
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bool
)paren
id|vptr
op_assign
id|v
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|value
comma
l_string|&quot;%d&quot;
comma
id|v
)paren
suffix:semicolon
)brace
r_else
id|vptr
op_assign
id|value_
ques
c_cond
id|value_
suffix:colon
l_string|&quot;&quot;
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
l_string|&quot;%s%c&quot;
comma
id|vptr
comma
id|term
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
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|tl
suffix:semicolon
r_char
op_star
id|global
op_assign
l_int|NULL
comma
op_star
id|repo_config
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|system_wide
op_assign
l_int|NULL
comma
op_star
id|local
suffix:semicolon
id|local
op_assign
id|config_exclusive_filename
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local
)paren
(brace
r_const
r_char
op_star
id|home
op_assign
id|getenv
c_func
(paren
l_string|&quot;HOME&quot;
)paren
suffix:semicolon
id|local
op_assign
id|repo_config
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;config&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_global
c_func
(paren
)paren
op_logical_and
id|home
)paren
id|global
op_assign
id|xstrdup
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/.gitconfig&quot;
comma
id|home
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_system
c_func
(paren
)paren
)paren
id|system_wide
op_assign
id|git_etc_gitconfig
c_func
(paren
)paren
suffix:semicolon
)brace
id|key
op_assign
id|xstrdup
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
id|xmalloc
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
r_goto
id|free_strings
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
id|xmalloc
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
r_goto
id|free_strings
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|do_all
op_logical_and
id|system_wide
)paren
id|git_config_from_file
c_func
(paren
id|show_config
comma
id|system_wide
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_all
op_logical_and
id|global
)paren
id|git_config_from_file
c_func
(paren
id|show_config
comma
id|global
comma
l_int|NULL
)paren
suffix:semicolon
id|git_config_from_file
c_func
(paren
id|show_config
comma
id|local
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|do_all
op_logical_and
op_logical_neg
id|seen
op_logical_and
id|global
)paren
id|git_config_from_file
c_func
(paren
id|show_config
comma
id|global
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|do_all
op_logical_and
op_logical_neg
id|seen
op_logical_and
id|system_wide
)paren
id|git_config_from_file
c_func
(paren
id|show_config
comma
id|system_wide
comma
l_int|NULL
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
id|ret
op_assign
op_logical_neg
id|seen
suffix:semicolon
r_else
id|ret
op_assign
(paren
id|seen
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
id|seen
OG
l_int|1
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
id|free_strings
suffix:colon
id|free
c_func
(paren
id|repo_config
)paren
suffix:semicolon
id|free
c_func
(paren
id|global
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|normalize_value
r_static
r_char
op_star
id|normalize_value
c_func
(paren
r_const
r_char
op_star
id|key
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_char
op_star
id|normalized
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|T_RAW
)paren
id|normalized
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
(brace
id|normalized
op_assign
id|xmalloc
c_func
(paren
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|T_INT
)paren
(brace
r_int
id|v
op_assign
id|git_config_int
c_func
(paren
id|key
comma
id|value
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|normalized
comma
l_string|&quot;%d&quot;
comma
id|v
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|T_BOOL
)paren
id|sprintf
c_func
(paren
id|normalized
comma
l_string|&quot;%s&quot;
comma
id|git_config_bool
c_func
(paren
id|key
comma
id|value
)paren
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|type
op_eq
id|T_BOOL_OR_INT
)paren
(brace
r_int
id|is_bool
comma
id|v
suffix:semicolon
id|v
op_assign
id|git_config_bool_or_int
c_func
(paren
id|key
comma
id|value
comma
op_amp
id|is_bool
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_bool
)paren
id|sprintf
c_func
(paren
id|normalized
comma
l_string|&quot;%d&quot;
comma
id|v
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|normalized
comma
l_string|&quot;%s&quot;
comma
id|v
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|normalized
suffix:semicolon
)brace
DECL|variable|get_color_found
r_static
r_int
id|get_color_found
suffix:semicolon
DECL|variable|get_color_slot
r_static
r_const
r_char
op_star
id|get_color_slot
suffix:semicolon
DECL|variable|get_colorbool_slot
r_static
r_const
r_char
op_star
id|get_colorbool_slot
suffix:semicolon
DECL|variable|parsed_color
r_static
r_char
id|parsed_color
(braket
id|COLOR_MAXLEN
)braket
suffix:semicolon
DECL|function|git_get_color_config
r_static
r_int
id|git_get_color_config
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
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
id|get_color_slot
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|color_parse
c_func
(paren
id|value
comma
id|var
comma
id|parsed_color
)paren
suffix:semicolon
id|get_color_found
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_color
r_static
r_int
id|get_color
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
multiline_comment|/*&n;&t; * grab the color setting for the given slot from the configuration,&n;&t; * or parse the default value if missing, and return ANSI color&n;&t; * escape sequence.&n;&t; *&n;&t; * e.g.&n;&t; * git config --get-color color.diff.whitespace &quot;blue reverse&quot;&n;&t; */
r_const
r_char
op_star
id|def_color
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_default
suffix:colon
id|usage
c_func
(paren
id|git_config_set_usage
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
id|def_color
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* fallthru */
r_case
l_int|1
suffix:colon
id|get_color_slot
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
id|get_color_found
op_assign
l_int|0
suffix:semicolon
id|parsed_color
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|git_config
c_func
(paren
id|git_get_color_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_color_found
op_logical_and
id|def_color
)paren
id|color_parse
c_func
(paren
id|def_color
comma
l_string|&quot;command line&quot;
comma
id|parsed_color
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|parsed_color
comma
id|stdout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|stdout_is_tty
r_static
r_int
id|stdout_is_tty
suffix:semicolon
DECL|variable|get_colorbool_found
r_static
r_int
id|get_colorbool_found
suffix:semicolon
DECL|variable|get_diff_color_found
r_static
r_int
id|get_diff_color_found
suffix:semicolon
DECL|function|git_get_colorbool_config
r_static
r_int
id|git_get_colorbool_config
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
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
id|get_colorbool_slot
)paren
)paren
(brace
id|get_colorbool_found
op_assign
id|git_config_colorbool
c_func
(paren
id|var
comma
id|value
comma
id|stdout_is_tty
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;diff.color&quot;
)paren
)paren
(brace
id|get_diff_color_found
op_assign
id|git_config_colorbool
c_func
(paren
id|var
comma
id|value
comma
id|stdout_is_tty
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;color.ui&quot;
)paren
)paren
(brace
id|git_use_color_default
op_assign
id|git_config_colorbool
c_func
(paren
id|var
comma
id|value
comma
id|stdout_is_tty
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_colorbool
r_static
r_int
id|get_colorbool
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
multiline_comment|/*&n;&t; * git config --get-colorbool &lt;slot&gt; [&lt;stdout-is-tty&gt;]&n;&t; *&n;&t; * returns &quot;true&quot; or &quot;false&quot; depending on how &lt;slot&gt;&n;&t; * is configured.&n;&t; */
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
)paren
id|stdout_is_tty
op_assign
id|git_config_bool
c_func
(paren
l_string|&quot;command line&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
id|stdout_is_tty
op_assign
id|isatty
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
id|usage
c_func
(paren
id|git_config_set_usage
)paren
suffix:semicolon
id|get_colorbool_found
op_assign
l_int|1
suffix:semicolon
id|get_diff_color_found
op_assign
l_int|1
suffix:semicolon
id|get_colorbool_slot
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|git_config
c_func
(paren
id|git_get_colorbool_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_colorbool_found
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|get_colorbool_slot
comma
l_string|&quot;color.diff&quot;
)paren
)paren
id|get_colorbool_found
op_assign
id|get_diff_color_found
suffix:semicolon
r_if
c_cond
(paren
id|get_colorbool_found
OL
l_int|0
)paren
id|get_colorbool_found
op_assign
id|git_use_color_default
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
(brace
r_return
id|get_colorbool_found
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|get_colorbool_found
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|cmd_config
r_int
id|cmd_config
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
id|unused_prefix
)paren
(brace
r_int
id|nongit
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
id|config_exclusive_filename
op_assign
id|getenv
c_func
(paren
id|CONFIG_ENVIRONMENT
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
l_string|&quot;--bool-or-int&quot;
)paren
)paren
id|type
op_assign
id|T_BOOL_OR_INT
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
(brace
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
id|git_config_set_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config
c_func
(paren
id|show_all_config
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|config_exclusive_filename
)paren
id|die
c_func
(paren
l_string|&quot;unable to read config file %s: %s&quot;
comma
id|config_exclusive_filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;error processing config file(s)&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
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
l_string|&quot;--global&quot;
)paren
)paren
(brace
r_char
op_star
id|home
op_assign
id|getenv
c_func
(paren
l_string|&quot;HOME&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|home
)paren
(brace
r_char
op_star
id|user_config
op_assign
id|xstrdup
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/.gitconfig&quot;
comma
id|home
)paren
)paren
suffix:semicolon
id|config_exclusive_filename
op_assign
id|user_config
suffix:semicolon
)brace
r_else
(brace
id|die
c_func
(paren
l_string|&quot;$HOME not set&quot;
)paren
suffix:semicolon
)brace
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
l_string|&quot;--system&quot;
)paren
)paren
id|config_exclusive_filename
op_assign
id|git_etc_gitconfig
c_func
(paren
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
l_string|&quot;--file&quot;
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
l_string|&quot;-f&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
id|usage
c_func
(paren
id|git_config_set_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_absolute_path
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
op_logical_and
id|prefix
)paren
id|config_exclusive_filename
op_assign
id|prefix_filename
c_func
(paren
id|prefix
comma
id|strlen
c_func
(paren
id|prefix
)paren
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_else
id|config_exclusive_filename
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
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
l_string|&quot;--null&quot;
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
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|term
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|delim
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|key_delim
op_assign
l_char|&squot;&bslash;n&squot;
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
l_string|&quot;--rename-section&quot;
)paren
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|4
)paren
id|usage
c_func
(paren
id|git_config_set_usage
)paren
suffix:semicolon
id|ret
op_assign
id|git_config_rename_section
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
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No such section!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
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
l_string|&quot;--remove-section&quot;
)paren
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
)paren
id|usage
c_func
(paren
id|git_config_set_usage
)paren
suffix:semicolon
id|ret
op_assign
id|git_config_rename_section
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
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No such section!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
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
l_string|&quot;--get-color&quot;
)paren
)paren
(brace
r_return
id|get_color
c_func
(paren
id|argc
op_minus
l_int|2
comma
id|argv
op_plus
l_int|2
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
l_string|&quot;--get-colorbool&quot;
)paren
)paren
(brace
r_return
id|get_colorbool
c_func
(paren
id|argc
op_minus
l_int|2
comma
id|argv
op_plus
l_int|2
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
l_string|&quot;--edit&quot;
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
l_string|&quot;-e&quot;
)paren
)paren
(brace
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
id|git_config_set_usage
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|launch_editor
c_func
(paren
id|config_exclusive_filename
ques
c_cond
id|config_exclusive_filename
suffix:colon
id|git_path
c_func
(paren
l_string|&quot;config&quot;
)paren
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
(brace
id|value
op_assign
id|normalize_value
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
r_return
id|git_config_set
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|value
)paren
suffix:semicolon
)brace
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
l_string|&quot;--add&quot;
)paren
)paren
(brace
id|value
op_assign
id|normalize_value
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
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|value
comma
l_string|&quot;^$&quot;
comma
l_int|0
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
(brace
id|value
op_assign
id|normalize_value
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
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|value
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|value
op_assign
id|normalize_value
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
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|value
comma
id|argv
(braket
l_int|3
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
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
(brace
id|value
op_assign
id|normalize_value
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
r_return
id|git_config_set_multivar
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|value
comma
id|argv
(braket
l_int|4
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
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
