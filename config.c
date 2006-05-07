multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; * Copyright (C) Johannes Schindelin, 2005&n; *&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;regex.h&gt;
DECL|macro|MAXNAME
mdefine_line|#define MAXNAME (256)
DECL|variable|config_file
r_static
id|FILE
op_star
id|config_file
suffix:semicolon
DECL|variable|config_file_name
r_static
r_const
r_char
op_star
id|config_file_name
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
l_char|&squot;&bslash;r&squot;
)paren
(brace
multiline_comment|/* DOS like systems */
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
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|ungetc
c_func
(paren
id|c
comma
id|f
)paren
suffix:semicolon
id|c
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
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
op_logical_and
id|c
op_ne
l_char|&squot;.&squot;
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
id|tolower
c_func
(paren
id|c
)paren
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
l_string|&quot;bad config file line %d in %s&quot;
comma
id|config_linenr
comma
id|config_file_name
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
l_string|&quot;bad config value for &squot;%s&squot; in %s&quot;
comma
id|name
comma
id|config_file_name
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.ignorestat&quot;
)paren
)paren
(brace
id|assume_unchanged
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.prefersymlinkrefs&quot;
)paren
)paren
(brace
id|prefer_symlink_refs
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.warnambiguousrefs&quot;
)paren
)paren
(brace
id|warn_ambiguous_refs
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;user.name&quot;
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|git_default_name
comma
id|value
comma
r_sizeof
(paren
id|git_default_name
)paren
)paren
suffix:semicolon
r_return
l_int|0
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
l_string|&quot;user.email&quot;
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|git_default_email
comma
id|value
comma
r_sizeof
(paren
id|git_default_email
)paren
)paren
suffix:semicolon
r_return
l_int|0
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
l_string|&quot;i18n.commitencoding&quot;
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|git_commit_encoding
comma
id|value
comma
r_sizeof
(paren
id|git_commit_encoding
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Add other config variables here and to Documentation/config.txt. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_config_from_file
r_int
id|git_config_from_file
c_func
(paren
id|config_fn_t
id|fn
comma
r_const
r_char
op_star
id|filename
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
id|filename
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
id|config_file_name
op_assign
id|filename
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
id|config_file_name
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|ret
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
r_return
id|git_config_from_file
c_func
(paren
id|fn
comma
id|git_path
c_func
(paren
l_string|&quot;config&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find all the stuff for git_config_set() below.&n; */
DECL|macro|MAX_MATCHES
mdefine_line|#define MAX_MATCHES 512
r_static
r_struct
(brace
DECL|member|baselen
r_int
id|baselen
suffix:semicolon
DECL|member|key
r_char
op_star
id|key
suffix:semicolon
DECL|member|do_not_match
r_int
id|do_not_match
suffix:semicolon
DECL|member|value_regex
id|regex_t
op_star
id|value_regex
suffix:semicolon
DECL|member|multi_replace
r_int
id|multi_replace
suffix:semicolon
DECL|member|offset
id|off_t
id|offset
(braket
id|MAX_MATCHES
)braket
suffix:semicolon
DECL|enumerator|START
DECL|enumerator|SECTION_SEEN
DECL|enumerator|SECTION_END_SEEN
DECL|enumerator|KEY_SEEN
DECL|member|state
r_enum
(brace
id|START
comma
id|SECTION_SEEN
comma
id|SECTION_END_SEEN
comma
id|KEY_SEEN
)brace
id|state
suffix:semicolon
DECL|member|seen
r_int
id|seen
suffix:semicolon
DECL|variable|store
)brace
id|store
suffix:semicolon
DECL|function|matches
r_static
r_int
id|matches
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
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|key
comma
id|store.key
)paren
op_logical_and
(paren
id|store.value_regex
op_eq
l_int|NULL
op_logical_or
(paren
id|store.do_not_match
op_xor
op_logical_neg
id|regexec
c_func
(paren
id|store.value_regex
comma
id|value
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|store_aux
r_static
r_int
id|store_aux
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
r_switch
c_cond
(paren
id|store.state
)paren
(brace
r_case
id|KEY_SEEN
suffix:colon
r_if
c_cond
(paren
id|matches
c_func
(paren
id|key
comma
id|value
)paren
)paren
(brace
r_if
c_cond
(paren
id|store.seen
op_eq
l_int|1
op_logical_and
id|store.multi_replace
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Warning: %s has multiple values&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|store.seen
op_ge
id|MAX_MATCHES
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Too many matches&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|store.offset
(braket
id|store.seen
)braket
op_assign
id|ftell
c_func
(paren
id|config_file
)paren
suffix:semicolon
id|store.seen
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SECTION_SEEN
suffix:colon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|key
comma
id|store.key
comma
id|store.baselen
op_plus
l_int|1
)paren
)paren
(brace
id|store.state
op_assign
id|SECTION_END_SEEN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
multiline_comment|/* do not increment matches: this is no match */
id|store.offset
(braket
id|store.seen
)braket
op_assign
id|ftell
c_func
(paren
id|config_file
)paren
suffix:semicolon
multiline_comment|/* fallthru */
r_case
id|SECTION_END_SEEN
suffix:colon
r_case
id|START
suffix:colon
r_if
c_cond
(paren
id|matches
c_func
(paren
id|key
comma
id|value
)paren
)paren
(brace
id|store.offset
(braket
id|store.seen
)braket
op_assign
id|ftell
c_func
(paren
id|config_file
)paren
suffix:semicolon
id|store.state
op_assign
id|KEY_SEEN
suffix:semicolon
id|store.seen
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strrchr
c_func
(paren
id|key
comma
l_char|&squot;.&squot;
)paren
id|key
op_eq
id|store.baselen
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|key
comma
id|store.key
comma
id|store.baselen
)paren
)paren
(brace
id|store.state
op_assign
id|SECTION_SEEN
suffix:semicolon
id|store.offset
(braket
id|store.seen
)braket
op_assign
id|ftell
c_func
(paren
id|config_file
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|store_write_section
r_static
r_void
id|store_write_section
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|key
)paren
(brace
id|write
c_func
(paren
id|fd
comma
l_string|&quot;[&quot;
comma
l_int|1
)paren
suffix:semicolon
id|write
c_func
(paren
id|fd
comma
id|key
comma
id|store.baselen
)paren
suffix:semicolon
id|write
c_func
(paren
id|fd
comma
l_string|&quot;]&bslash;n&quot;
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|store_write_pair
r_static
r_void
id|store_write_pair
c_func
(paren
r_int
id|fd
comma
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
r_int
id|i
suffix:semicolon
id|write
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;t&quot;
comma
l_int|1
)paren
suffix:semicolon
id|write
c_func
(paren
id|fd
comma
id|key
op_plus
id|store.baselen
op_plus
l_int|1
comma
id|strlen
c_func
(paren
id|key
op_plus
id|store.baselen
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|write
c_func
(paren
id|fd
comma
l_string|&quot; = &quot;
comma
l_int|3
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|value
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_switch
c_cond
(paren
id|value
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|write
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;&bslash;n&quot;
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
id|write
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;&bslash;t&quot;
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&quot;&squot;
suffix:colon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
id|write
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;&bslash;&quot;
comma
l_int|1
)paren
suffix:semicolon
r_default
suffix:colon
id|write
c_func
(paren
id|fd
comma
id|value
op_plus
id|i
comma
l_int|1
)paren
suffix:semicolon
)brace
id|write
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|find_beginning_of_line
r_static
r_int
id|find_beginning_of_line
c_func
(paren
r_const
r_char
op_star
id|contents
comma
r_int
id|size
comma
r_int
id|offset_
comma
r_int
op_star
id|found_bracket
)paren
(brace
r_int
id|equal_offset
op_assign
id|size
comma
id|bracket_offset
op_assign
id|size
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
id|offset_
op_minus
l_int|2
suffix:semicolon
id|offset
OG
l_int|0
op_logical_and
id|contents
(braket
id|offset
)braket
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|offset
op_decrement
)paren
r_switch
c_cond
(paren
id|contents
(braket
id|offset
)braket
)paren
(brace
r_case
l_char|&squot;=&squot;
suffix:colon
id|equal_offset
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;]&squot;
suffix:colon
id|bracket_offset
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bracket_offset
OL
id|equal_offset
)paren
(brace
op_star
id|found_bracket
op_assign
l_int|1
suffix:semicolon
id|offset
op_assign
id|bracket_offset
op_plus
l_int|1
suffix:semicolon
)brace
r_else
id|offset
op_increment
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
DECL|function|git_config_set
r_int
id|git_config_set
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
r_return
id|git_config_set_multivar
c_func
(paren
id|key
comma
id|value
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If value==NULL, unset in (remove from) config,&n; * if value_regex!=NULL, disregard key/value pairs where value does not match.&n; * if multi_replace==0, nothing, or only one matching key/value is replaced,&n; *     else all matching key/values (regardless how many) are removed,&n; *     before the new pair is written.&n; *&n; * Returns 0 on success.&n; *&n; * This function does this:&n; *&n; * - it locks the config file by creating &quot;.git/config.lock&quot;&n; *&n; * - it then parses the config using store_aux() as validator to find&n; *   the position on the key/value pair to replace. If it is to be unset,&n; *   it must be found exactly once.&n; *&n; * - the config file is mmap()ed and the part before the match (if any) is&n; *   written to the lock file, then the changed part and the rest.&n; *&n; * - the config file is removed and the lock file rename()d to it.&n; *&n; */
DECL|function|git_config_set_multivar
r_int
id|git_config_set_multivar
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
comma
r_const
r_char
op_star
id|value_regex
comma
r_int
id|multi_replace
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|fd
comma
id|in_fd
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_char
op_star
id|config_filename
op_assign
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;config&quot;
)paren
)paren
suffix:semicolon
r_char
op_star
id|lock_file
op_assign
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;config.lock&quot;
)paren
)paren
suffix:semicolon
r_const
r_char
op_star
id|last_dot
op_assign
id|strrchr
c_func
(paren
id|key
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Since &quot;key&quot; actually contains the section name and the real&n;&t; * key name separated by a dot, we have to know where the dot is.&n;&t; */
r_if
c_cond
(paren
id|last_dot
op_eq
l_int|NULL
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;key does not contain a section: %s&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
id|ret
op_assign
l_int|2
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|store.baselen
op_assign
id|last_dot
id|key
suffix:semicolon
id|store.multi_replace
op_assign
id|multi_replace
suffix:semicolon
multiline_comment|/*&n;&t; * Validate the key and while at it, lower case it for matching.&n;&t; */
id|store.key
op_assign
(paren
r_char
op_star
)paren
id|malloc
c_func
(paren
id|strlen
c_func
(paren
id|key
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
id|key
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|i
op_ne
id|store.baselen
op_logical_and
(paren
(paren
op_logical_neg
id|isalnum
c_func
(paren
id|key
(braket
id|i
)braket
)paren
op_logical_and
id|key
(braket
id|i
)braket
op_ne
l_char|&squot;.&squot;
)paren
op_logical_or
(paren
id|i
op_eq
id|store.baselen
op_plus
l_int|1
op_logical_and
op_logical_neg
id|isalpha
c_func
(paren
id|key
(braket
id|i
)braket
)paren
)paren
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;invalid key: %s&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
id|free
c_func
(paren
id|store.key
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
r_else
id|store.key
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|key
(braket
id|i
)braket
)paren
suffix:semicolon
id|store.key
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * The lock_file serves a purpose in addition to locking: the new&n;&t; * contents of .git/config will be written into it.&n;&t; */
id|fd
op_assign
id|open
c_func
(paren
id|lock_file
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;could not lock config file&bslash;n&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|store.key
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If .git/config does not exist yet, write a minimal version.&n;&t; */
id|in_fd
op_assign
id|open
c_func
(paren
id|config_filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_fd
OL
l_int|0
)paren
(brace
id|free
c_func
(paren
id|store.key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ENOENT
op_ne
id|errno
)paren
(brace
id|error
c_func
(paren
l_string|&quot;opening %s: %s&quot;
comma
id|config_filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_file
)paren
suffix:semicolon
id|ret
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* same as &quot;invalid config file&quot; */
r_goto
id|out_free
suffix:semicolon
)brace
multiline_comment|/* if nothing to unset, error out */
r_if
c_cond
(paren
id|value
op_eq
l_int|NULL
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_file
)paren
suffix:semicolon
id|ret
op_assign
l_int|5
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|store.key
op_assign
(paren
r_char
op_star
)paren
id|key
suffix:semicolon
id|store_write_section
c_func
(paren
id|fd
comma
id|key
)paren
suffix:semicolon
id|store_write_pair
c_func
(paren
id|fd
comma
id|key
comma
id|value
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_char
op_star
id|contents
suffix:semicolon
r_int
id|i
comma
id|copy_begin
comma
id|copy_end
comma
id|new_line
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|value_regex
op_eq
l_int|NULL
)paren
id|store.value_regex
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|value_regex
(braket
l_int|0
)braket
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|store.do_not_match
op_assign
l_int|1
suffix:semicolon
id|value_regex
op_increment
suffix:semicolon
)brace
r_else
id|store.do_not_match
op_assign
l_int|0
suffix:semicolon
id|store.value_regex
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
id|store.value_regex
comma
id|value_regex
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
id|value_regex
)paren
suffix:semicolon
id|free
c_func
(paren
id|store.value_regex
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_file
)paren
suffix:semicolon
id|ret
op_assign
l_int|6
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
)brace
id|store.offset
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|store.state
op_assign
id|START
suffix:semicolon
id|store.seen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * After this, store.offset will contain the *end* offset&n;&t;&t; * of the last match, or remain at 0 if no match was found.&n;&t;&t; * As a side effect, we make sure to transform only a valid&n;&t;&t; * existing config file.&n;&t;&t; */
r_if
c_cond
(paren
id|git_config
c_func
(paren
id|store_aux
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;invalid config file&bslash;n&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|store.key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|store.value_regex
op_ne
l_int|NULL
)paren
(brace
id|regfree
c_func
(paren
id|store.value_regex
)paren
suffix:semicolon
id|free
c_func
(paren
id|store.value_regex
)paren
suffix:semicolon
)brace
id|ret
op_assign
l_int|3
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|free
c_func
(paren
id|store.key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|store.value_regex
op_ne
l_int|NULL
)paren
(brace
id|regfree
c_func
(paren
id|store.value_regex
)paren
suffix:semicolon
id|free
c_func
(paren
id|store.value_regex
)paren
suffix:semicolon
)brace
multiline_comment|/* if nothing to unset, or too many matches, error out */
r_if
c_cond
(paren
(paren
id|store.seen
op_eq
l_int|0
op_logical_and
id|value
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|store.seen
OG
l_int|1
op_logical_and
id|multi_replace
op_eq
l_int|0
)paren
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_file
)paren
suffix:semicolon
id|ret
op_assign
l_int|5
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|fstat
c_func
(paren
id|in_fd
comma
op_amp
id|st
)paren
suffix:semicolon
id|contents
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|st.st_size
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|in_fd
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|in_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|store.seen
op_eq
l_int|0
)paren
id|store.seen
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|copy_begin
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|store.seen
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|store.offset
(braket
id|i
)braket
op_eq
l_int|0
)paren
(brace
id|store.offset
(braket
id|i
)braket
op_assign
id|copy_end
op_assign
id|st.st_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|store.state
op_ne
id|KEY_SEEN
)paren
(brace
id|copy_end
op_assign
id|store.offset
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
id|copy_end
op_assign
id|find_beginning_of_line
c_func
(paren
id|contents
comma
id|st.st_size
comma
id|store.offset
(braket
id|i
)braket
l_int|2
comma
op_amp
id|new_line
)paren
suffix:semicolon
multiline_comment|/* write the first part of the config */
r_if
c_cond
(paren
id|copy_end
OG
id|copy_begin
)paren
(brace
id|write
c_func
(paren
id|fd
comma
id|contents
op_plus
id|copy_begin
comma
id|copy_end
id|copy_begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_line
)paren
id|write
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
id|copy_begin
op_assign
id|store.offset
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* write the pair (value == NULL means unset) */
r_if
c_cond
(paren
id|value
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|store.state
op_eq
id|START
)paren
id|store_write_section
c_func
(paren
id|fd
comma
id|key
)paren
suffix:semicolon
id|store_write_pair
c_func
(paren
id|fd
comma
id|key
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* write the rest of the config */
r_if
c_cond
(paren
id|copy_begin
OL
id|st.st_size
)paren
id|write
c_func
(paren
id|fd
comma
id|contents
op_plus
id|copy_begin
comma
id|st.st_size
id|copy_begin
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|contents
comma
id|st.st_size
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|config_filename
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lock_file
comma
id|config_filename
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Could not rename the lock file?&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
l_int|4
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|out_free
suffix:colon
r_if
c_cond
(paren
id|config_filename
)paren
id|free
c_func
(paren
id|config_filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock_file
)paren
id|free
c_func
(paren
id|lock_file
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
