macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|builtin_config_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_config_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git config [options]&quot;
comma
l_int|NULL
)brace
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
DECL|variable|use_global_config
DECL|variable|use_system_config
DECL|variable|use_local_config
r_static
r_int
id|use_global_config
comma
id|use_system_config
comma
id|use_local_config
suffix:semicolon
DECL|variable|given_config_file
r_static
r_const
r_char
op_star
id|given_config_file
suffix:semicolon
DECL|variable|actions
DECL|variable|types
r_static
r_int
id|actions
comma
id|types
suffix:semicolon
DECL|variable|get_color_slot
DECL|variable|get_colorbool_slot
r_static
r_const
r_char
op_star
id|get_color_slot
comma
op_star
id|get_colorbool_slot
suffix:semicolon
DECL|variable|end_null
r_static
r_int
id|end_null
suffix:semicolon
DECL|variable|respect_includes
r_static
r_int
id|respect_includes
op_assign
l_int|1
suffix:semicolon
DECL|macro|ACTION_GET
mdefine_line|#define ACTION_GET (1&lt;&lt;0)
DECL|macro|ACTION_GET_ALL
mdefine_line|#define ACTION_GET_ALL (1&lt;&lt;1)
DECL|macro|ACTION_GET_REGEXP
mdefine_line|#define ACTION_GET_REGEXP (1&lt;&lt;2)
DECL|macro|ACTION_REPLACE_ALL
mdefine_line|#define ACTION_REPLACE_ALL (1&lt;&lt;3)
DECL|macro|ACTION_ADD
mdefine_line|#define ACTION_ADD (1&lt;&lt;4)
DECL|macro|ACTION_UNSET
mdefine_line|#define ACTION_UNSET (1&lt;&lt;5)
DECL|macro|ACTION_UNSET_ALL
mdefine_line|#define ACTION_UNSET_ALL (1&lt;&lt;6)
DECL|macro|ACTION_RENAME_SECTION
mdefine_line|#define ACTION_RENAME_SECTION (1&lt;&lt;7)
DECL|macro|ACTION_REMOVE_SECTION
mdefine_line|#define ACTION_REMOVE_SECTION (1&lt;&lt;8)
DECL|macro|ACTION_LIST
mdefine_line|#define ACTION_LIST (1&lt;&lt;9)
DECL|macro|ACTION_EDIT
mdefine_line|#define ACTION_EDIT (1&lt;&lt;10)
DECL|macro|ACTION_SET
mdefine_line|#define ACTION_SET (1&lt;&lt;11)
DECL|macro|ACTION_SET_ALL
mdefine_line|#define ACTION_SET_ALL (1&lt;&lt;12)
DECL|macro|ACTION_GET_COLOR
mdefine_line|#define ACTION_GET_COLOR (1&lt;&lt;13)
DECL|macro|ACTION_GET_COLORBOOL
mdefine_line|#define ACTION_GET_COLORBOOL (1&lt;&lt;14)
DECL|macro|TYPE_BOOL
mdefine_line|#define TYPE_BOOL (1&lt;&lt;0)
DECL|macro|TYPE_INT
mdefine_line|#define TYPE_INT (1&lt;&lt;1)
DECL|macro|TYPE_BOOL_OR_INT
mdefine_line|#define TYPE_BOOL_OR_INT (1&lt;&lt;2)
DECL|macro|TYPE_PATH
mdefine_line|#define TYPE_PATH (1&lt;&lt;3)
DECL|variable|builtin_config_options
r_static
r_struct
id|option
id|builtin_config_options
(braket
)braket
op_assign
(brace
id|OPT_GROUP
c_func
(paren
l_string|&quot;Config file location&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;global&quot;
comma
op_amp
id|use_global_config
comma
l_string|&quot;use global config file&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;system&quot;
comma
op_amp
id|use_system_config
comma
l_string|&quot;use system config file&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;local&quot;
comma
op_amp
id|use_local_config
comma
l_string|&quot;use repository config file&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;file&quot;
comma
op_amp
id|given_config_file
comma
l_string|&quot;file&quot;
comma
l_string|&quot;use given config file&quot;
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Action&quot;
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;get&quot;
comma
op_amp
id|actions
comma
l_string|&quot;get value: name [value-regex]&quot;
comma
id|ACTION_GET
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;get-all&quot;
comma
op_amp
id|actions
comma
l_string|&quot;get all values: key [value-regex]&quot;
comma
id|ACTION_GET_ALL
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;get-regexp&quot;
comma
op_amp
id|actions
comma
l_string|&quot;get values for regexp: name-regex [value-regex]&quot;
comma
id|ACTION_GET_REGEXP
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;replace-all&quot;
comma
op_amp
id|actions
comma
l_string|&quot;replace all matching variables: name value [value_regex]&quot;
comma
id|ACTION_REPLACE_ALL
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;add&quot;
comma
op_amp
id|actions
comma
l_string|&quot;adds a new variable: name value&quot;
comma
id|ACTION_ADD
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;unset&quot;
comma
op_amp
id|actions
comma
l_string|&quot;removes a variable: name [value-regex]&quot;
comma
id|ACTION_UNSET
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;unset-all&quot;
comma
op_amp
id|actions
comma
l_string|&quot;removes all matches: name [value-regex]&quot;
comma
id|ACTION_UNSET_ALL
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;rename-section&quot;
comma
op_amp
id|actions
comma
l_string|&quot;rename section: old-name new-name&quot;
comma
id|ACTION_RENAME_SECTION
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;remove-section&quot;
comma
op_amp
id|actions
comma
l_string|&quot;remove a section: name&quot;
comma
id|ACTION_REMOVE_SECTION
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;l&squot;
comma
l_string|&quot;list&quot;
comma
op_amp
id|actions
comma
l_string|&quot;list all&quot;
comma
id|ACTION_LIST
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;e&squot;
comma
l_string|&quot;edit&quot;
comma
op_amp
id|actions
comma
l_string|&quot;opens an editor&quot;
comma
id|ACTION_EDIT
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;get-color&quot;
comma
op_amp
id|get_color_slot
comma
l_string|&quot;slot&quot;
comma
l_string|&quot;find the color configured: [default]&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;get-colorbool&quot;
comma
op_amp
id|get_colorbool_slot
comma
l_string|&quot;slot&quot;
comma
l_string|&quot;find the color setting: [stdout-is-tty]&quot;
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Type&quot;
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;bool&quot;
comma
op_amp
id|types
comma
l_string|&quot;value is &bslash;&quot;true&bslash;&quot; or &bslash;&quot;false&bslash;&quot;&quot;
comma
id|TYPE_BOOL
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;int&quot;
comma
op_amp
id|types
comma
l_string|&quot;value is decimal number&quot;
comma
id|TYPE_INT
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;bool-or-int&quot;
comma
op_amp
id|types
comma
l_string|&quot;value is --bool or --int&quot;
comma
id|TYPE_BOOL_OR_INT
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;path&quot;
comma
op_amp
id|types
comma
l_string|&quot;value is a path (file or directory name)&quot;
comma
id|TYPE_PATH
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Other&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;z&squot;
comma
l_string|&quot;null&quot;
comma
op_amp
id|end_null
comma
l_string|&quot;terminate values with NUL byte&quot;
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;includes&quot;
comma
op_amp
id|respect_includes
comma
l_string|&quot;respect include directives on lookup&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
DECL|function|check_argc
r_static
r_void
id|check_argc
c_func
(paren
r_int
id|argc
comma
r_int
id|min
comma
r_int
id|max
)paren
(brace
r_if
c_cond
(paren
id|argc
op_ge
id|min
op_logical_and
id|argc
op_le
id|max
)paren
r_return
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;wrong number of arguments&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_config_usage
comma
id|builtin_config_options
)paren
suffix:semicolon
)brace
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
id|must_free_vptr
op_assign
l_int|0
suffix:semicolon
r_int
id|dup_error
op_assign
l_int|0
suffix:semicolon
r_int
id|must_print_delim
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
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|key_
)paren
suffix:semicolon
id|must_print_delim
op_assign
l_int|1
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
id|types
op_eq
id|TYPE_INT
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
id|types
op_eq
id|TYPE_BOOL
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
id|types
op_eq
id|TYPE_BOOL_OR_INT
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
r_if
c_cond
(paren
id|types
op_eq
id|TYPE_PATH
)paren
(brace
id|git_config_pathname
c_func
(paren
op_amp
id|vptr
comma
id|key_
comma
id|value_
)paren
suffix:semicolon
id|must_free_vptr
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|value_
)paren
(brace
id|vptr
op_assign
id|value_
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Just show the key name */
id|vptr
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|must_print_delim
op_assign
l_int|0
suffix:semicolon
)brace
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
(brace
r_if
c_cond
(paren
id|must_print_delim
)paren
id|printf
c_func
(paren
l_string|&quot;%c&quot;
comma
id|key_delim
)paren
suffix:semicolon
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
)brace
r_if
c_cond
(paren
id|must_free_vptr
)paren
multiline_comment|/* If vptr must be freed, it&squot;s a pointer to a&n;&t;&t; * dynamically allocated buffer, it&squot;s safe to cast to&n;&t;&t; * const.&n;&t;&t;*/
id|free
c_func
(paren
(paren
r_char
op_star
)paren
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
r_int
id|ret
op_assign
id|CONFIG_GENERIC_ERROR
suffix:semicolon
r_char
op_star
id|global
op_assign
l_int|NULL
comma
op_star
id|xdg
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
r_struct
id|config_include_data
id|inc
op_assign
id|CONFIG_INCLUDE_INIT
suffix:semicolon
id|config_fn_t
id|fn
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
id|local
op_assign
id|given_config_file
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local
)paren
(brace
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
id|home_config_paths
c_func
(paren
op_amp
id|global
comma
op_amp
id|xdg
comma
l_string|&quot;config&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|use_key_regexp
)paren
(brace
r_char
op_star
id|tl
suffix:semicolon
multiline_comment|/*&n;&t;&t; * NEEDSWORK: this naive pattern lowercasing obviously does not&n;&t;&t; * work for more complex patterns like &quot;^[^.]*Foo.*bar&quot;.&n;&t;&t; * Perhaps we should deprecate this altogether someday.&n;&t;&t; */
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
id|tl
op_decrement
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
id|tl
op_increment
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
id|free
c_func
(paren
id|key
)paren
suffix:semicolon
id|ret
op_assign
id|CONFIG_INVALID_PATTERN
suffix:semicolon
r_goto
id|free_strings
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|git_config_parse_key
c_func
(paren
id|key_
comma
op_amp
id|key
comma
l_int|NULL
)paren
)paren
(brace
id|ret
op_assign
id|CONFIG_INVALID_KEY
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
id|ret
op_assign
id|CONFIG_INVALID_PATTERN
suffix:semicolon
r_goto
id|free_strings
suffix:semicolon
)brace
)brace
id|fn
op_assign
id|show_config
suffix:semicolon
id|data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|respect_includes
)paren
(brace
id|inc.fn
op_assign
id|fn
suffix:semicolon
id|inc.data
op_assign
id|data
suffix:semicolon
id|fn
op_assign
id|git_config_include
suffix:semicolon
id|data
op_assign
op_amp
id|inc
suffix:semicolon
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
id|fn
comma
id|system_wide
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_all
op_logical_and
id|xdg
)paren
id|git_config_from_file
c_func
(paren
id|fn
comma
id|xdg
comma
id|data
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
id|fn
comma
id|global
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_all
)paren
id|git_config_from_file
c_func
(paren
id|fn
comma
id|local
comma
id|data
)paren
suffix:semicolon
id|git_config_from_parameters
c_func
(paren
id|fn
comma
id|data
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
)paren
id|git_config_from_file
c_func
(paren
id|fn
comma
id|local
comma
id|data
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
id|fn
comma
id|global
comma
id|data
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
id|xdg
)paren
id|git_config_from_file
c_func
(paren
id|fn
comma
id|xdg
comma
id|data
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
id|fn
comma
id|system_wide
comma
id|data
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
id|free
c_func
(paren
id|xdg
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
id|types
op_eq
l_int|0
op_logical_or
id|types
op_eq
id|TYPE_PATH
)paren
multiline_comment|/*&n;&t;&t; * We don&squot;t do normalization for TYPE_PATH here: If&n;&t;&t; * the path is like ~/foobar/, we prefer to store&n;&t;&t; * &quot;~/foobar/&quot; in the config file, and to expand the ~&n;&t;&t; * when retrieving the value.&n;&t;&t; */
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
id|types
op_eq
id|TYPE_INT
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
id|types
op_eq
id|TYPE_BOOL
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
id|types
op_eq
id|TYPE_BOOL_OR_INT
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
r_void
id|get_color
c_func
(paren
r_const
r_char
op_star
id|def_color
)paren
(brace
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
id|git_config_with_options
c_func
(paren
id|git_get_color_config
comma
l_int|NULL
comma
id|given_config_file
comma
id|respect_includes
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
)brace
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
DECL|variable|get_color_ui_found
r_static
r_int
id|get_color_ui_found
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
id|get_colorbool_found
op_assign
id|git_config_colorbool
c_func
(paren
id|var
comma
id|value
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
id|var
comma
l_string|&quot;diff.color&quot;
)paren
)paren
id|get_diff_color_found
op_assign
id|git_config_colorbool
c_func
(paren
id|var
comma
id|value
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
id|var
comma
l_string|&quot;color.ui&quot;
)paren
)paren
id|get_color_ui_found
op_assign
id|git_config_colorbool
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
DECL|function|get_colorbool
r_static
r_int
id|get_colorbool
c_func
(paren
r_int
id|print
)paren
(brace
id|get_colorbool_found
op_assign
l_int|1
suffix:semicolon
id|get_diff_color_found
op_assign
l_int|1
suffix:semicolon
id|git_config_with_options
c_func
(paren
id|git_get_colorbool_config
comma
l_int|NULL
comma
id|given_config_file
comma
id|respect_includes
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
id|get_color_ui_found
suffix:semicolon
)brace
id|get_colorbool_found
op_assign
id|want_color
c_func
(paren
id|get_colorbool_found
)paren
suffix:semicolon
r_if
c_cond
(paren
id|print
)paren
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
r_else
r_return
id|get_colorbool_found
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
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
id|prefix
)paren
(brace
r_int
id|nongit
op_assign
op_logical_neg
id|startup_info-&gt;have_repository
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
id|given_config_file
op_assign
id|getenv
c_func
(paren
id|CONFIG_ENVIRONMENT
)paren
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
id|prefix
comma
id|builtin_config_options
comma
id|builtin_config_usage
comma
id|PARSE_OPT_STOP_AT_NON_OPTION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_global_config
op_plus
id|use_system_config
op_plus
id|use_local_config
op_plus
op_logical_neg
op_logical_neg
id|given_config_file
OG
l_int|1
)paren
(brace
id|error
c_func
(paren
l_string|&quot;only one config file at a time.&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_config_usage
comma
id|builtin_config_options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|use_global_config
)paren
(brace
r_char
op_star
id|user_config
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|xdg_config
op_assign
l_int|NULL
suffix:semicolon
id|home_config_paths
c_func
(paren
op_amp
id|user_config
comma
op_amp
id|xdg_config
comma
l_string|&quot;config&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_config
)paren
multiline_comment|/*&n;&t;&t;&t; * It is unknown if HOME/.gitconfig exists, so&n;&t;&t;&t; * we do not know if we should write to XDG&n;&t;&t;&t; * location; error out even if XDG_CONFIG_HOME&n;&t;&t;&t; * is set and points at a sane location.&n;&t;&t;&t; */
id|die
c_func
(paren
l_string|&quot;$HOME not set&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|user_config
comma
id|R_OK
)paren
op_logical_and
id|xdg_config
op_logical_and
op_logical_neg
id|access
c_func
(paren
id|xdg_config
comma
id|R_OK
)paren
)paren
id|given_config_file
op_assign
id|xdg_config
suffix:semicolon
r_else
id|given_config_file
op_assign
id|user_config
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|use_system_config
)paren
id|given_config_file
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
id|use_local_config
)paren
id|given_config_file
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;config&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|given_config_file
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_absolute_path
c_func
(paren
id|given_config_file
)paren
op_logical_and
id|prefix
)paren
id|given_config_file
op_assign
id|xstrdup
c_func
(paren
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
id|given_config_file
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|respect_includes
op_eq
l_int|1
)paren
id|respect_includes
op_assign
op_logical_neg
id|given_config_file
suffix:semicolon
r_if
c_cond
(paren
id|end_null
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
r_if
c_cond
(paren
id|HAS_MULTI_BITS
c_func
(paren
id|types
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;only one type at a time.&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_config_usage
comma
id|builtin_config_options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_color_slot
)paren
id|actions
op_or_assign
id|ACTION_GET_COLOR
suffix:semicolon
r_if
c_cond
(paren
id|get_colorbool_slot
)paren
id|actions
op_or_assign
id|ACTION_GET_COLORBOOL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|get_color_slot
op_logical_or
id|get_colorbool_slot
)paren
op_logical_and
id|types
)paren
(brace
id|error
c_func
(paren
l_string|&quot;--get-color and variable type are incoherent&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_config_usage
comma
id|builtin_config_options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|HAS_MULTI_BITS
c_func
(paren
id|actions
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;only one action at a time.&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_config_usage
comma
id|builtin_config_options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|actions
op_eq
l_int|0
)paren
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_case
l_int|1
suffix:colon
id|actions
op_assign
id|ACTION_GET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|actions
op_assign
id|ACTION_SET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|actions
op_assign
id|ACTION_SET_ALL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage_with_options
c_func
(paren
id|builtin_config_usage
comma
id|builtin_config_options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_LIST
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_with_options
c_func
(paren
id|show_all_config
comma
l_int|NULL
comma
id|given_config_file
comma
id|respect_includes
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|given_config_file
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to read config file &squot;%s&squot;&quot;
comma
id|given_config_file
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
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_EDIT
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|given_config_file
op_logical_and
id|nongit
)paren
id|die
c_func
(paren
l_string|&quot;not in a git directory&quot;
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
id|given_config_file
ques
c_cond
id|given_config_file
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
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_SET
)paren
(brace
r_int
id|ret
suffix:semicolon
id|check_argc
c_func
(paren
id|argc
comma
l_int|2
comma
l_int|2
)paren
suffix:semicolon
id|value
op_assign
id|normalize_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|ret
op_assign
id|git_config_set_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
)braket
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|CONFIG_NOTHING_SET
)paren
id|error
c_func
(paren
l_string|&quot;cannot overwrite multiple values with a single value&bslash;n&quot;
l_string|&quot;       Use a regexp, --add or --replace-all to change %s.&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_SET_ALL
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|2
comma
l_int|3
)paren
suffix:semicolon
id|value
op_assign
id|normalize_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|git_config_set_multivar_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
)braket
comma
id|value
comma
id|argv
(braket
l_int|2
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_ADD
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|2
comma
l_int|2
)paren
suffix:semicolon
id|value
op_assign
id|normalize_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|git_config_set_multivar_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
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
id|actions
op_eq
id|ACTION_REPLACE_ALL
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|2
comma
l_int|3
)paren
suffix:semicolon
id|value
op_assign
id|normalize_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|git_config_set_multivar_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
)braket
comma
id|value
comma
id|argv
(braket
l_int|2
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_GET
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_GET_ALL
)paren
(brace
id|do_all
op_assign
l_int|1
suffix:semicolon
id|check_argc
c_func
(paren
id|argc
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_GET_REGEXP
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
id|check_argc
c_func
(paren
id|argc
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
r_return
id|get_value
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_UNSET
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
)paren
r_return
id|git_config_set_multivar_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
)braket
comma
l_int|NULL
comma
id|argv
(braket
l_int|1
)braket
comma
l_int|0
)paren
suffix:semicolon
r_else
r_return
id|git_config_set_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
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
id|actions
op_eq
id|ACTION_UNSET_ALL
)paren
(brace
id|check_argc
c_func
(paren
id|argc
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
r_return
id|git_config_set_multivar_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
)braket
comma
l_int|NULL
comma
id|argv
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_RENAME_SECTION
)paren
(brace
r_int
id|ret
suffix:semicolon
id|check_argc
c_func
(paren
id|argc
comma
l_int|2
comma
l_int|2
)paren
suffix:semicolon
id|ret
op_assign
id|git_config_rename_section_in_file
c_func
(paren
id|given_config_file
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
id|die
c_func
(paren
l_string|&quot;No such section!&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_REMOVE_SECTION
)paren
(brace
r_int
id|ret
suffix:semicolon
id|check_argc
c_func
(paren
id|argc
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|git_config_rename_section_in_file
c_func
(paren
id|given_config_file
comma
id|argv
(braket
l_int|0
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
id|die
c_func
(paren
l_string|&quot;No such section!&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_GET_COLOR
)paren
(brace
id|get_color
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|actions
op_eq
id|ACTION_GET_COLORBOOL
)paren
(brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
id|color_stdout_is_tty
op_assign
id|git_config_bool
c_func
(paren
l_string|&quot;command line&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|get_colorbool
c_func
(paren
id|argc
op_ne
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_repo_config
r_int
id|cmd_repo_config
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;WARNING: git repo-config is deprecated in favor of git config.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|cmd_config
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
)paren
suffix:semicolon
)brace
eof
