macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|macro|OPT_SHORT
mdefine_line|#define OPT_SHORT 1
DECL|macro|OPT_UNSET
mdefine_line|#define OPT_UNSET 2
DECL|struct|optparse_t
r_struct
id|optparse_t
(brace
DECL|member|argv
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
DECL|member|argc
r_int
id|argc
suffix:semicolon
DECL|member|opt
r_const
r_char
op_star
id|opt
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_arg
r_static
r_inline
r_const
r_char
op_star
id|get_arg
c_func
(paren
r_struct
id|optparse_t
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;opt
)paren
(brace
r_const
r_char
op_star
id|res
op_assign
id|p-&gt;opt
suffix:semicolon
id|p-&gt;opt
op_assign
l_int|NULL
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|p-&gt;argc
op_decrement
suffix:semicolon
r_return
op_star
op_increment
id|p-&gt;argv
suffix:semicolon
)brace
DECL|function|skip_prefix
r_static
r_inline
r_const
r_char
op_star
id|skip_prefix
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
r_return
id|strncmp
c_func
(paren
id|str
comma
id|prefix
comma
id|len
)paren
ques
c_cond
l_int|NULL
suffix:colon
id|str
op_plus
id|len
suffix:semicolon
)brace
DECL|function|opterror
r_static
r_int
id|opterror
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
id|reason
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|OPT_SHORT
)paren
r_return
id|error
c_func
(paren
l_string|&quot;switch `%c&squot; %s&quot;
comma
id|opt-&gt;short_name
comma
id|reason
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|OPT_UNSET
)paren
r_return
id|error
c_func
(paren
l_string|&quot;option `no-%s&squot; %s&quot;
comma
id|opt-&gt;long_name
comma
id|reason
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;option `%s&squot; %s&quot;
comma
id|opt-&gt;long_name
comma
id|reason
)paren
suffix:semicolon
)brace
DECL|function|get_value
r_static
r_int
id|get_value
c_func
(paren
r_struct
id|optparse_t
op_star
id|p
comma
r_const
r_struct
id|option
op_star
id|opt
comma
r_int
id|flags
)paren
(brace
r_const
r_char
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;opt
op_logical_and
(paren
id|flags
op_amp
id|OPT_UNSET
)paren
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;takes no value&quot;
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opt-&gt;type
)paren
(brace
r_case
id|OPTION_BOOLEAN
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|OPT_SHORT
)paren
op_logical_and
id|p-&gt;opt
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;takes no value&quot;
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|OPT_UNSET
)paren
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
l_int|0
suffix:semicolon
r_else
(paren
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
)paren
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_STRING
suffix:colon
r_if
c_cond
(paren
id|flags
op_amp
id|OPT_UNSET
)paren
(brace
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|opt-&gt;value
op_assign
(paren
r_const
r_char
op_star
)paren
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;opt
op_logical_and
id|p-&gt;argc
op_le
l_int|1
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;requires a value&quot;
comma
id|flags
)paren
suffix:semicolon
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|opt-&gt;value
op_assign
id|get_arg
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_INTEGER
suffix:colon
r_if
c_cond
(paren
id|flags
op_amp
id|OPT_UNSET
)paren
(brace
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;opt
op_logical_and
id|p-&gt;argc
op_le
l_int|1
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;requires a value&quot;
comma
id|flags
)paren
suffix:semicolon
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
id|get_arg
c_func
(paren
id|p
)paren
comma
(paren
r_char
op_star
op_star
)paren
op_amp
id|s
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;expects a numerical value&quot;
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;should not happen, someone must be hit on the forehead&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|parse_short_opt
r_static
r_int
id|parse_short_opt
c_func
(paren
r_struct
id|optparse_t
op_star
id|p
comma
r_const
r_struct
id|option
op_star
id|options
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|options-&gt;type
op_ne
id|OPTION_END
suffix:semicolon
id|options
op_increment
)paren
(brace
r_if
c_cond
(paren
id|options-&gt;short_name
op_eq
op_star
id|p-&gt;opt
)paren
(brace
id|p-&gt;opt
op_assign
id|p-&gt;opt
(braket
l_int|1
)braket
ques
c_cond
id|p-&gt;opt
op_plus
l_int|1
suffix:colon
l_int|NULL
suffix:semicolon
r_return
id|get_value
c_func
(paren
id|p
comma
id|options
comma
id|OPT_SHORT
)paren
suffix:semicolon
)brace
)brace
r_return
id|error
c_func
(paren
l_string|&quot;unknown switch `%c&squot;&quot;
comma
op_star
id|p-&gt;opt
)paren
suffix:semicolon
)brace
DECL|function|parse_long_opt
r_static
r_int
id|parse_long_opt
c_func
(paren
r_struct
id|optparse_t
op_star
id|p
comma
r_const
r_char
op_star
id|arg
comma
r_const
r_struct
id|option
op_star
id|options
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|options-&gt;type
op_ne
id|OPTION_END
suffix:semicolon
id|options
op_increment
)paren
(brace
r_const
r_char
op_star
id|rest
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options-&gt;long_name
)paren
r_continue
suffix:semicolon
id|rest
op_assign
id|skip_prefix
c_func
(paren
id|arg
comma
id|options-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rest
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;no-&quot;
comma
l_int|3
)paren
)paren
r_continue
suffix:semicolon
id|flags
op_or_assign
id|OPT_UNSET
suffix:semicolon
id|rest
op_assign
id|skip_prefix
c_func
(paren
id|arg
op_plus
l_int|3
comma
id|options-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rest
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|rest
)paren
(brace
r_if
c_cond
(paren
op_star
id|rest
op_ne
l_char|&squot;=&squot;
)paren
r_continue
suffix:semicolon
id|p-&gt;opt
op_assign
id|rest
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|get_value
c_func
(paren
id|p
comma
id|options
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;unknown option `%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|parse_options
r_int
id|parse_options
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
r_struct
id|option
op_star
id|options
comma
r_const
r_char
op_star
r_const
id|usagestr
(braket
)braket
comma
r_int
id|flags
)paren
(brace
r_struct
id|optparse_t
id|args
op_assign
(brace
id|argv
op_plus
l_int|1
comma
id|argc
l_int|1
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|j
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|args.argc
suffix:semicolon
id|args.argc
op_decrement
comma
id|args.argv
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|args.argv
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_ne
l_char|&squot;-&squot;
op_logical_or
op_logical_neg
id|arg
(braket
l_int|1
)braket
)paren
(brace
id|argv
(braket
id|j
op_increment
)braket
op_assign
id|args.argv
(braket
l_int|0
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_ne
l_char|&squot;-&squot;
)paren
(brace
id|args.opt
op_assign
id|arg
op_plus
l_int|1
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_star
id|args.opt
op_eq
l_char|&squot;h&squot;
)paren
id|usage_with_options
c_func
(paren
id|usagestr
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_short_opt
c_func
(paren
op_amp
id|args
comma
id|options
)paren
OL
l_int|0
)paren
id|usage_with_options
c_func
(paren
id|usagestr
comma
id|options
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|args.opt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|arg
(braket
l_int|2
)braket
)paren
(brace
multiline_comment|/* &quot;--&quot; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|PARSE_OPT_KEEP_DASHDASH
)paren
)paren
(brace
id|args.argc
op_decrement
suffix:semicolon
id|args.argv
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
op_plus
l_int|2
comma
l_string|&quot;help&quot;
)paren
)paren
id|usage_with_options
c_func
(paren
id|usagestr
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_long_opt
c_func
(paren
op_amp
id|args
comma
id|arg
op_plus
l_int|2
comma
id|options
)paren
)paren
id|usage_with_options
c_func
(paren
id|usagestr
comma
id|options
)paren
suffix:semicolon
)brace
id|memmove
c_func
(paren
id|argv
op_plus
id|j
comma
id|args.argv
comma
id|args.argc
op_star
r_sizeof
(paren
op_star
id|argv
)paren
)paren
suffix:semicolon
id|argv
(braket
id|j
op_plus
id|args.argc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|j
op_plus
id|args.argc
suffix:semicolon
)brace
DECL|macro|USAGE_OPTS_WIDTH
mdefine_line|#define USAGE_OPTS_WIDTH 24
DECL|macro|USAGE_GAP
mdefine_line|#define USAGE_GAP         2
DECL|function|usage_with_options
r_void
id|usage_with_options
c_func
(paren
r_const
r_char
op_star
r_const
op_star
id|usagestr
comma
r_const
r_struct
id|option
op_star
id|opts
)paren
(brace
r_struct
id|strbuf
id|sb
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|sb
comma
l_int|4096
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
op_star
id|usagestr
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
op_increment
id|usagestr
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;    %s&bslash;n&quot;
comma
op_star
id|usagestr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;type
op_ne
id|OPTION_GROUP
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|opts-&gt;type
op_ne
id|OPTION_END
suffix:semicolon
id|opts
op_increment
)paren
(brace
r_int
id|pos
suffix:semicolon
r_int
id|pad
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;type
op_eq
id|OPTION_GROUP
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|opts-&gt;help
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|opts-&gt;help
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pos
op_assign
id|sb.len
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;    &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;short_name
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;-%c&quot;
comma
id|opts-&gt;short_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;long_name
op_logical_and
id|opts-&gt;short_name
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;, &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;long_name
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;--%s&quot;
comma
id|opts-&gt;long_name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opts-&gt;type
)paren
(brace
r_case
id|OPTION_INTEGER
suffix:colon
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
l_string|&quot; &lt;n&gt;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPTION_STRING
suffix:colon
r_if
c_cond
(paren
id|opts-&gt;argh
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot; &lt;%s&gt;&quot;
comma
id|opts-&gt;argh
)paren
suffix:semicolon
r_else
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
l_string|&quot; ...&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|pad
op_assign
id|sb.len
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|pad
op_le
id|USAGE_OPTS_WIDTH
)paren
id|pad
op_assign
id|USAGE_OPTS_WIDTH
id|pad
suffix:semicolon
r_else
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pad
op_assign
id|USAGE_OPTS_WIDTH
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%*s%s&bslash;n&quot;
comma
id|pad
op_plus
id|USAGE_GAP
comma
l_string|&quot;&quot;
comma
id|opts-&gt;help
)paren
suffix:semicolon
)brace
id|usage
c_func
(paren
id|sb.buf
)paren
suffix:semicolon
)brace
eof
