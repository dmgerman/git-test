macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;parse-options.h&quot;
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
DECL|member|out
r_const
r_char
op_star
op_star
id|out
suffix:semicolon
DECL|member|argc
DECL|member|cpidx
r_int
id|argc
comma
id|cpidx
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
comma
op_star
id|arg
suffix:semicolon
r_const
r_int
id|unset
op_assign
id|flags
op_amp
id|OPT_UNSET
suffix:semicolon
r_if
c_cond
(paren
id|unset
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
id|unset
op_logical_and
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_NONEG
)paren
)paren
r_return
id|opterror
c_func
(paren
id|opt
comma
l_string|&quot;isn&squot;t available&quot;
comma
id|flags
)paren
suffix:semicolon
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
(brace
r_switch
c_cond
(paren
id|opt-&gt;type
)paren
(brace
r_case
id|OPTION_CALLBACK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_NOARG
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_case
id|OPTION_BOOLEAN
suffix:colon
r_case
id|OPTION_BIT
suffix:colon
r_case
id|OPTION_SET_INT
suffix:colon
r_case
id|OPTION_SET_PTR
suffix:colon
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
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|arg
op_assign
id|p-&gt;opt
ques
c_cond
id|p-&gt;opt
suffix:colon
(paren
id|p-&gt;argc
OG
l_int|1
ques
c_cond
id|p-&gt;argv
(braket
l_int|1
)braket
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opt-&gt;type
)paren
(brace
r_case
id|OPTION_BIT
suffix:colon
r_if
c_cond
(paren
id|unset
)paren
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_and_assign
op_complement
id|opt-&gt;defval
suffix:semicolon
r_else
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_or_assign
id|opt-&gt;defval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_BOOLEAN
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
id|unset
ques
c_cond
l_int|0
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_SET_INT
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
id|unset
ques
c_cond
l_int|0
suffix:colon
id|opt-&gt;defval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_SET_PTR
suffix:colon
op_star
(paren
r_void
op_star
op_star
)paren
id|opt-&gt;value
op_assign
id|unset
ques
c_cond
l_int|NULL
suffix:colon
(paren
r_void
op_star
)paren
id|opt-&gt;defval
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
id|unset
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
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
op_logical_and
op_logical_neg
id|p-&gt;opt
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
id|opt-&gt;defval
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
id|OPTION_CALLBACK
suffix:colon
r_if
c_cond
(paren
id|unset
)paren
r_return
(paren
op_star
id|opt-&gt;callback
)paren
(paren
id|opt
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_NOARG
)paren
r_return
(paren
op_star
id|opt-&gt;callback
)paren
(paren
id|opt
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
op_logical_and
op_logical_neg
id|p-&gt;opt
)paren
r_return
(paren
op_star
id|opt-&gt;callback
)paren
(paren
id|opt
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
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
r_return
(paren
op_star
id|opt-&gt;callback
)paren
(paren
id|opt
comma
id|get_arg
c_func
(paren
id|p
)paren
comma
l_int|0
)paren
suffix:semicolon
r_case
id|OPTION_INTEGER
suffix:colon
r_if
c_cond
(paren
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
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
op_logical_and
op_logical_neg
id|p-&gt;opt
)paren
(brace
op_star
(paren
r_int
op_star
)paren
id|opt-&gt;value
op_assign
id|opt-&gt;defval
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
r_const
r_char
op_star
id|arg_end
op_assign
id|strchr
c_func
(paren
id|arg
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_const
r_struct
id|option
op_star
id|abbrev_option
op_assign
l_int|NULL
comma
op_star
id|ambiguous_option
op_assign
l_int|NULL
suffix:semicolon
r_int
id|abbrev_flags
op_assign
l_int|0
comma
id|ambiguous_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg_end
)paren
id|arg_end
op_assign
id|arg
op_plus
id|strlen
c_func
(paren
id|arg
)paren
suffix:semicolon
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
id|options-&gt;type
op_eq
id|OPTION_ARGUMENT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rest
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rest
op_eq
l_char|&squot;=&squot;
)paren
r_return
id|opterror
c_func
(paren
id|options
comma
l_string|&quot;takes no value&quot;
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rest
)paren
r_continue
suffix:semicolon
id|p-&gt;out
(braket
id|p-&gt;cpidx
op_increment
)braket
op_assign
id|arg
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rest
)paren
(brace
multiline_comment|/* abbreviated? */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|options-&gt;long_name
comma
id|arg
comma
id|arg_end
id|arg
)paren
)paren
(brace
id|is_abbreviated
suffix:colon
r_if
c_cond
(paren
id|abbrev_option
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * If this is abbreviated, it is&n;&t;&t;&t;&t;&t; * ambiguous. So when there is no&n;&t;&t;&t;&t;&t; * exact match later, we need to&n;&t;&t;&t;&t;&t; * error out.&n;&t;&t;&t;&t;&t; */
id|ambiguous_option
op_assign
id|abbrev_option
suffix:semicolon
id|ambiguous_flags
op_assign
id|abbrev_flags
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|OPT_UNSET
)paren
op_logical_and
op_star
id|arg_end
)paren
id|p-&gt;opt
op_assign
id|arg_end
op_plus
l_int|1
suffix:semicolon
id|abbrev_option
op_assign
id|options
suffix:semicolon
id|abbrev_flags
op_assign
id|flags
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* negated and abbreviated very much? */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
l_string|&quot;no-&quot;
comma
id|arg
)paren
)paren
(brace
id|flags
op_or_assign
id|OPT_UNSET
suffix:semicolon
r_goto
id|is_abbreviated
suffix:semicolon
)brace
multiline_comment|/* negated? */
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
multiline_comment|/* abbreviated and negated? */
r_if
c_cond
(paren
op_logical_neg
id|rest
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|options-&gt;long_name
comma
id|arg
op_plus
l_int|3
)paren
)paren
r_goto
id|is_abbreviated
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
r_if
c_cond
(paren
id|ambiguous_option
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Ambiguous option: %s &quot;
l_string|&quot;(could be --%s%s or --%s%s)&quot;
comma
id|arg
comma
(paren
id|ambiguous_flags
op_amp
id|OPT_UNSET
)paren
ques
c_cond
l_string|&quot;no-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ambiguous_option-&gt;long_name
comma
(paren
id|abbrev_flags
op_amp
id|OPT_UNSET
)paren
ques
c_cond
l_string|&quot;no-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|abbrev_option-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|abbrev_option
)paren
r_return
id|get_value
c_func
(paren
id|p
comma
id|abbrev_option
comma
id|abbrev_flags
)paren
suffix:semicolon
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
DECL|function|check_typos
r_void
id|check_typos
c_func
(paren
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
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|arg
)paren
OL
l_int|3
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;no-&quot;
)paren
)paren
(brace
id|error
(paren
l_string|&quot;did you mean `--%s` (with two dashes ?)&quot;
comma
id|arg
)paren
suffix:semicolon
m_exit
(paren
l_int|129
)paren
suffix:semicolon
)brace
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
op_logical_neg
id|options-&gt;long_name
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|options-&gt;long_name
comma
id|arg
)paren
)paren
(brace
id|error
(paren
l_string|&quot;did you mean `--%s` (with two dashes ?)&quot;
comma
id|arg
)paren
suffix:semicolon
m_exit
(paren
l_int|129
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
id|NORETURN
r_void
id|usage_with_options_internal
c_func
(paren
r_const
r_char
op_star
r_const
op_star
comma
r_const
r_struct
id|option
op_star
comma
r_int
)paren
suffix:semicolon
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
id|argv
comma
id|argc
l_int|1
comma
l_int|0
comma
l_int|NULL
)brace
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
r_if
c_cond
(paren
id|flags
op_amp
id|PARSE_OPT_STOP_AT_NON_OPTION
)paren
r_break
suffix:semicolon
id|args.out
(braket
id|args.cpidx
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
r_if
c_cond
(paren
id|args.opt
)paren
id|check_typos
c_func
(paren
id|arg
op_plus
l_int|1
comma
id|options
)paren
suffix:semicolon
r_while
c_loop
(paren
id|args.opt
)paren
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
l_string|&quot;help-all&quot;
)paren
)paren
id|usage_with_options_internal
c_func
(paren
id|usagestr
comma
id|options
comma
l_int|1
)paren
suffix:semicolon
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
id|args.out
op_plus
id|args.cpidx
comma
id|args.argv
comma
id|args.argc
op_star
r_sizeof
(paren
op_star
id|args.out
)paren
)paren
suffix:semicolon
id|args.out
(braket
id|args.cpidx
op_plus
id|args.argc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|args.cpidx
op_plus
id|args.argc
suffix:semicolon
)brace
DECL|macro|USAGE_OPTS_WIDTH
mdefine_line|#define USAGE_OPTS_WIDTH 24
DECL|macro|USAGE_GAP
mdefine_line|#define USAGE_GAP         2
DECL|function|usage_with_options_internal
r_void
id|usage_with_options_internal
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
comma
r_int
id|full
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s&bslash;n&quot;
comma
op_star
id|usagestr
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|usagestr
op_logical_and
op_star
op_star
id|usagestr
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;   or: %s&bslash;n&quot;
comma
op_star
id|usagestr
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|usagestr
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;    %s&bslash;n&quot;
comma
op_star
id|usagestr
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;type
op_ne
id|OPTION_GROUP
)paren
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
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
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|opts-&gt;help
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|opts-&gt;help
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|full
op_logical_and
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_HIDDEN
)paren
)paren
r_continue
suffix:semicolon
id|pos
op_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;    &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;short_name
)paren
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
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
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;, &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;long_name
)paren
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
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
id|OPTION_ARGUMENT
suffix:colon
r_break
suffix:semicolon
r_case
id|OPTION_INTEGER
suffix:colon
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;[&lt;n&gt;]&quot;
)paren
suffix:semicolon
r_else
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; &lt;n&gt;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPTION_CALLBACK
suffix:colon
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NOARG
)paren
r_break
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_case
id|OPTION_STRING
suffix:colon
r_if
c_cond
(paren
id|opts-&gt;argh
)paren
(brace
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; [&lt;%s&gt;]&quot;
comma
id|opts-&gt;argh
)paren
suffix:semicolon
r_else
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; &lt;%s&gt;&quot;
comma
id|opts-&gt;argh
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; [...]&quot;
)paren
suffix:semicolon
r_else
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; ...&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* OPTION_{BIT,BOOLEAN,SET_INT,SET_PTR} */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
op_le
id|USAGE_OPTS_WIDTH
)paren
id|pad
op_assign
id|USAGE_OPTS_WIDTH
id|pos
suffix:semicolon
r_else
(brace
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
id|pad
op_assign
id|USAGE_OPTS_WIDTH
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
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
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
m_exit
(paren
l_int|129
)paren
suffix:semicolon
)brace
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
id|usage_with_options_internal
c_func
(paren
id|usagestr
comma
id|opts
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*----- some often used options -----*/
macro_line|#include &quot;cache.h&quot;
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
eof
