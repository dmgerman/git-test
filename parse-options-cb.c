macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;argv-array.h&quot;
multiline_comment|/*----- some often used options -----*/
DECL|function|parse_opt_abbrev_cb
r_int
id|parse_opt_abbrev_cb
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
r_int
id|v
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|v
op_assign
id|unset
ques
c_cond
l_int|0
suffix:colon
id|DEFAULT_ABBREV
suffix:semicolon
)brace
r_else
(brace
id|v
op_assign
id|strtol
c_func
(paren
id|arg
comma
(paren
r_char
op_star
op_star
)paren
op_amp
id|arg
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;expects a numerical value&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
op_logical_and
id|v
OL
id|MINIMUM_ABBREV
)paren
id|v
op_assign
id|MINIMUM_ABBREV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|v
OG
l_int|40
)paren
id|v
op_assign
l_int|40
suffix:semicolon
)brace
op_star
(paren
r_int
op_star
)paren
(paren
id|opt-&gt;value
)paren
op_assign
id|v
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_approxidate_cb
r_int
id|parse_opt_approxidate_cb
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
r_int
op_star
)paren
(paren
id|opt-&gt;value
)paren
op_assign
id|approxidate
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_expiry_date_cb
r_int
id|parse_opt_expiry_date_cb
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
r_return
id|parse_expiry_date
c_func
(paren
id|arg
comma
(paren
r_int
r_int
op_star
)paren
id|opt-&gt;value
)paren
suffix:semicolon
)brace
DECL|function|parse_opt_color_flag_cb
r_int
id|parse_opt_color_flag_cb
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
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
id|arg
op_assign
id|unset
ques
c_cond
l_string|&quot;never&quot;
suffix:colon
(paren
r_const
r_char
op_star
)paren
id|opt-&gt;defval
suffix:semicolon
id|value
op_assign
id|git_config_colorbool
c_func
(paren
l_int|NULL
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
OL
l_int|0
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;expects &bslash;&quot;always&bslash;&quot;, &bslash;&quot;auto&bslash;&quot;, or &bslash;&quot;never&bslash;&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_verbosity_cb
r_int
id|parse_opt_verbosity_cb
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
r_int
op_star
id|target
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
multiline_comment|/* --no-quiet, --no-verbose */
op_star
id|target
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt-&gt;short_name
op_eq
l_char|&squot;v&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|target
op_ge
l_int|0
)paren
(paren
op_star
id|target
)paren
op_increment
suffix:semicolon
r_else
op_star
id|target
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_star
id|target
op_le
l_int|0
)paren
(paren
op_star
id|target
)paren
op_decrement
suffix:semicolon
r_else
op_star
id|target
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_with_commit
r_int
id|parse_opt_with_commit
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
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;malformed object name %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_return
id|error
c_func
(paren
l_string|&quot;no such commit %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|commit
comma
id|opt-&gt;value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_tertiary
r_int
id|parse_opt_tertiary
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
r_int
op_star
id|target
op_assign
id|opt-&gt;value
suffix:semicolon
op_star
id|target
op_assign
id|unset
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_options_concat
r_int
id|parse_options_concat
c_func
(paren
r_struct
id|option
op_star
id|dst
comma
r_int
id|dst_size
comma
r_struct
id|option
op_star
id|src
)paren
(brace
r_int
id|i
comma
id|j
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
id|dst_size
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dst
(braket
id|i
)braket
dot
id|type
op_eq
id|OPTION_END
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dst_size
suffix:semicolon
id|i
op_increment
comma
id|j
op_increment
)paren
(brace
id|dst
(braket
id|i
)braket
op_assign
id|src
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
id|j
)braket
dot
id|type
op_eq
id|OPTION_END
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parse_opt_string_list
r_int
id|parse_opt_string_list
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
r_struct
id|string_list
op_star
id|v
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
(brace
id|string_list_clear
c_func
(paren
id|v
comma
l_int|0
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
id|arg
)paren
r_return
l_int|1
suffix:semicolon
id|string_list_append
c_func
(paren
id|v
comma
id|xstrdup
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_noop_cb
r_int
id|parse_opt_noop_cb
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * Recreates the command-line option in the strbuf.&n; */
DECL|function|recreate_opt
r_static
r_int
id|recreate_opt
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
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
id|strbuf_reset
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;long_name
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|unset
ques
c_cond
l_string|&quot;--no-&quot;
suffix:colon
l_string|&quot;--&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|opt-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|arg
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|opt-&gt;short_name
op_logical_and
op_logical_neg
id|unset
)paren
(brace
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;-&squot;
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|sb
comma
id|opt-&gt;short_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|arg
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * For an option opt, recreates the command-line option in opt-&gt;value which&n; * must be an char* initialized to NULL. This is useful when we need to pass&n; * the command-line option to another command. Since any previous value will be&n; * overwritten, this callback should only be used for options where the last&n; * one wins.&n; */
DECL|function|parse_opt_passthru
r_int
id|parse_opt_passthru
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
r_static
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
op_star
id|opt_value
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|recreate_opt
c_func
(paren
op_amp
id|sb
comma
id|opt
comma
id|arg
comma
id|unset
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|opt_value
)paren
id|free
c_func
(paren
op_star
id|opt_value
)paren
suffix:semicolon
op_star
id|opt_value
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|sb
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * For an option opt, recreate the command-line option, appending it to&n; * opt-&gt;value which must be a argv_array. This is useful when we need to pass&n; * the command-line option, which can be specified multiple times, to another&n; * command.&n; */
DECL|function|parse_opt_passthru_argv
r_int
id|parse_opt_passthru_argv
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
r_static
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|argv_array
op_star
id|opt_value
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|recreate_opt
c_func
(paren
op_amp
id|sb
comma
id|opt
comma
id|arg
comma
id|unset
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|argv_array_push
c_func
(paren
id|opt_value
comma
id|sb.buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
