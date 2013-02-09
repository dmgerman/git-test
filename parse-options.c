macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;utf8.h&quot;
r_static
r_int
id|parse_options_usage
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
id|ctx
comma
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
id|err
)paren
suffix:semicolon
DECL|macro|OPT_SHORT
mdefine_line|#define OPT_SHORT 1
DECL|macro|OPT_UNSET
mdefine_line|#define OPT_UNSET 2
DECL|function|optbug
r_int
id|optbug
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
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;long_name
)paren
r_return
id|error
c_func
(paren
l_string|&quot;BUG: option &squot;%s&squot; %s&quot;
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
l_string|&quot;BUG: switch &squot;%c&squot; %s&quot;
comma
id|opt-&gt;short_name
comma
id|reason
)paren
suffix:semicolon
)brace
DECL|function|opterror
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
DECL|function|get_arg
r_static
r_int
id|get_arg
c_func
(paren
r_struct
id|parse_opt_ctx_t
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
comma
r_const
r_char
op_star
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;opt
)paren
(brace
op_star
id|arg
op_assign
id|p-&gt;opt
suffix:semicolon
id|p-&gt;opt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;argc
op_eq
l_int|1
op_logical_and
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_LASTARG_DEFAULT
)paren
)paren
(brace
op_star
id|arg
op_assign
(paren
r_const
r_char
op_star
)paren
id|opt-&gt;defval
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p-&gt;argc
OG
l_int|1
)paren
(brace
id|p-&gt;argc
op_decrement
suffix:semicolon
op_star
id|arg
op_assign
op_star
op_increment
id|p-&gt;argv
suffix:semicolon
)brace
r_else
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
l_int|0
suffix:semicolon
)brace
DECL|function|fix_filename
r_static
r_void
id|fix_filename
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|file
op_logical_or
op_logical_neg
op_star
id|file
op_logical_or
op_logical_neg
id|prefix
op_logical_or
id|is_absolute_path
c_func
(paren
op_star
id|file
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-&quot;
comma
op_star
id|file
)paren
)paren
r_return
suffix:semicolon
op_star
id|file
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
op_star
id|file
)paren
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
id|parse_opt_ctx_t
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
r_int
id|err
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
op_logical_and
(paren
id|opt-&gt;flags
op_amp
id|PARSE_OPT_NOARG
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
id|OPTION_LOWLEVEL_CALLBACK
suffix:colon
r_return
(paren
op_star
(paren
id|parse_opt_ll_cb
op_star
)paren
id|opt-&gt;callback
)paren
(paren
id|p
comma
id|opt
comma
id|unset
)paren
suffix:semicolon
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
id|OPTION_NEGBIT
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
op_or_assign
id|opt-&gt;defval
suffix:semicolon
r_else
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
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_COUNTUP
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
r_else
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
r_else
r_return
id|get_arg
c_func
(paren
id|p
comma
id|opt
comma
id|flags
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|opt-&gt;value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_FILENAME
suffix:colon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
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
r_else
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
r_else
id|err
op_assign
id|get_arg
c_func
(paren
id|p
comma
id|opt
comma
id|flags
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|opt-&gt;value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|fix_filename
c_func
(paren
id|p-&gt;prefix
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|opt-&gt;value
)paren
suffix:semicolon
r_return
id|err
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
ques
c_cond
(paren
l_int|1
)paren
suffix:colon
l_int|0
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
ques
c_cond
(paren
l_int|1
)paren
suffix:colon
l_int|0
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
ques
c_cond
(paren
l_int|1
)paren
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_arg
c_func
(paren
id|p
comma
id|opt
comma
id|flags
comma
op_amp
id|arg
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
(paren
op_star
id|opt-&gt;callback
)paren
(paren
id|opt
comma
id|arg
comma
l_int|0
)paren
ques
c_cond
(paren
l_int|1
)paren
suffix:colon
l_int|0
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
id|get_arg
c_func
(paren
id|p
comma
id|opt
comma
id|flags
comma
op_amp
id|arg
)paren
)paren
r_return
l_int|1
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
id|arg
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
id|parse_opt_ctx_t
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
r_const
r_struct
id|option
op_star
id|numopt
op_assign
l_int|NULL
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
multiline_comment|/*&n;&t;&t; * Handle the numerical option later, explicit one-digit&n;&t;&t; * options take precedence over it.&n;&t;&t; */
r_if
c_cond
(paren
id|options-&gt;type
op_eq
id|OPTION_NUMBER
)paren
id|numopt
op_assign
id|options
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numopt
op_logical_and
id|isdigit
c_func
(paren
op_star
id|p-&gt;opt
)paren
)paren
(brace
r_int
id|len
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|arg
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_while
c_loop
(paren
id|isdigit
c_func
(paren
id|p-&gt;opt
(braket
id|len
)braket
)paren
)paren
id|len
op_increment
suffix:semicolon
id|arg
op_assign
id|xmemdupz
c_func
(paren
id|p-&gt;opt
comma
id|len
)paren
suffix:semicolon
id|p-&gt;opt
op_assign
id|p-&gt;opt
(braket
id|len
)braket
ques
c_cond
id|p-&gt;opt
op_plus
id|len
suffix:colon
l_int|NULL
suffix:semicolon
id|rc
op_assign
(paren
op_star
id|numopt-&gt;callback
)paren
(paren
id|numopt
comma
id|arg
comma
l_int|0
)paren
ques
c_cond
(paren
l_int|1
)paren
suffix:colon
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_return
l_int|2
suffix:semicolon
)brace
DECL|function|parse_long_opt
r_static
r_int
id|parse_long_opt
c_func
(paren
r_struct
id|parse_opt_ctx_t
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
comma
op_star
id|long_name
op_assign
id|options-&gt;long_name
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
comma
id|opt_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|long_name
)paren
r_continue
suffix:semicolon
id|again
suffix:colon
id|rest
op_assign
id|skip_prefix
c_func
(paren
id|arg
comma
id|long_name
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
id|long_name
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
op_xor
id|opt_flags
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* negation allowed? */
r_if
c_cond
(paren
id|options-&gt;flags
op_amp
id|PARSE_OPT_NONEG
)paren
r_continue
suffix:semicolon
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;no-&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|long_name
comma
l_string|&quot;no-&quot;
)paren
)paren
(brace
id|long_name
op_add_assign
l_int|3
suffix:semicolon
id|opt_flags
op_or_assign
id|OPT_UNSET
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
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
id|long_name
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
id|long_name
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
op_xor
id|opt_flags
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
l_int|2
suffix:semicolon
)brace
DECL|function|parse_nodash_opt
r_static
r_int
id|parse_nodash_opt
c_func
(paren
r_struct
id|parse_opt_ctx_t
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|options-&gt;flags
op_amp
id|PARSE_OPT_NODASH
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|options-&gt;short_name
op_eq
id|arg
(braket
l_int|0
)braket
op_logical_and
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
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
r_return
l_int|2
suffix:semicolon
)brace
DECL|function|check_typos
r_static
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
DECL|function|parse_options_check
r_static
r_void
id|parse_options_check
c_func
(paren
r_const
r_struct
id|option
op_star
id|opts
)paren
(brace
r_int
id|err
op_assign
l_int|0
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
r_if
c_cond
(paren
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_LASTARG_DEFAULT
)paren
op_logical_and
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
)paren
id|err
op_or_assign
id|optbug
c_func
(paren
id|opts
comma
l_string|&quot;uses incompatible flags &quot;
l_string|&quot;LASTARG_DEFAULT and OPTARG&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NODASH
op_logical_and
(paren
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
op_logical_or
op_logical_neg
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NOARG
)paren
op_logical_or
op_logical_neg
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NONEG
)paren
op_logical_or
id|opts-&gt;long_name
)paren
)paren
id|err
op_or_assign
id|optbug
c_func
(paren
id|opts
comma
l_string|&quot;uses feature &quot;
l_string|&quot;not supported for dashless options&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opts-&gt;type
)paren
(brace
r_case
id|OPTION_COUNTUP
suffix:colon
r_case
id|OPTION_BIT
suffix:colon
r_case
id|OPTION_NEGBIT
suffix:colon
r_case
id|OPTION_SET_INT
suffix:colon
r_case
id|OPTION_SET_PTR
suffix:colon
r_case
id|OPTION_NUMBER
suffix:colon
r_if
c_cond
(paren
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
op_logical_or
op_logical_neg
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NOARG
)paren
)paren
id|err
op_or_assign
id|optbug
c_func
(paren
id|opts
comma
l_string|&quot;should not accept an argument&quot;
)paren
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
multiline_comment|/* ok. (usually accepts an argument) */
)brace
)brace
r_if
c_cond
(paren
id|err
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
)brace
DECL|function|parse_options_start
r_void
id|parse_options_start
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
id|ctx
comma
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
comma
r_const
r_struct
id|option
op_star
id|options
comma
r_int
id|flags
)paren
(brace
id|memset
c_func
(paren
id|ctx
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ctx
)paren
)paren
suffix:semicolon
id|ctx-&gt;argc
op_assign
id|argc
l_int|1
suffix:semicolon
id|ctx-&gt;argv
op_assign
id|argv
op_plus
l_int|1
suffix:semicolon
id|ctx-&gt;out
op_assign
id|argv
suffix:semicolon
id|ctx-&gt;prefix
op_assign
id|prefix
suffix:semicolon
id|ctx-&gt;cpidx
op_assign
(paren
(paren
id|flags
op_amp
id|PARSE_OPT_KEEP_ARGV0
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|ctx-&gt;flags
op_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|PARSE_OPT_KEEP_UNKNOWN
)paren
op_logical_and
(paren
id|flags
op_amp
id|PARSE_OPT_STOP_AT_NON_OPTION
)paren
)paren
id|die
c_func
(paren
l_string|&quot;STOP_AT_NON_OPTION and KEEP_UNKNOWN don&squot;t go together&quot;
)paren
suffix:semicolon
id|parse_options_check
c_func
(paren
id|options
)paren
suffix:semicolon
)brace
r_static
r_int
id|usage_with_options_internal
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
comma
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
comma
r_int
)paren
suffix:semicolon
DECL|function|parse_options_step
r_int
id|parse_options_step
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
id|ctx
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
)paren
(brace
r_int
id|internal_help
op_assign
op_logical_neg
(paren
id|ctx-&gt;flags
op_amp
id|PARSE_OPT_NO_INTERNAL_HELP
)paren
suffix:semicolon
multiline_comment|/* we must reset -&gt;opt, unknown short option leave it dangling */
id|ctx-&gt;opt
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ctx-&gt;argc
suffix:semicolon
id|ctx-&gt;argc
op_decrement
comma
id|ctx-&gt;argv
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|ctx-&gt;argv
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
id|parse_nodash_opt
c_func
(paren
id|ctx
comma
id|arg
comma
id|options
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ctx-&gt;flags
op_amp
id|PARSE_OPT_STOP_AT_NON_OPTION
)paren
r_return
id|PARSE_OPT_NON_OPTION
suffix:semicolon
id|ctx-&gt;out
(braket
id|ctx-&gt;cpidx
op_increment
)braket
op_assign
id|ctx-&gt;argv
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
id|ctx-&gt;opt
op_assign
id|arg
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|internal_help
op_logical_and
op_star
id|ctx-&gt;opt
op_eq
l_char|&squot;h&squot;
)paren
r_return
id|parse_options_usage
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|parse_short_opt
c_func
(paren
id|ctx
comma
id|options
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|parse_options_usage
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|1
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|ctx-&gt;opt
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
r_goto
id|unknown
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctx-&gt;opt
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
id|ctx-&gt;opt
)paren
(brace
r_if
c_cond
(paren
id|internal_help
op_logical_and
op_star
id|ctx-&gt;opt
op_eq
l_char|&squot;h&squot;
)paren
r_return
id|parse_options_usage
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|parse_short_opt
c_func
(paren
id|ctx
comma
id|options
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|parse_options_usage
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|1
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* fake a short option thing to hide the fact that we may have&n;&t;&t;&t;&t;&t; * started to parse aggregated stuff&n;&t;&t;&t;&t;&t; *&n;&t;&t;&t;&t;&t; * This is leaky, too bad.&n;&t;&t;&t;&t;&t; */
id|ctx-&gt;argv
(braket
l_int|0
)braket
op_assign
id|xstrdup
c_func
(paren
id|ctx-&gt;opt
l_int|1
)paren
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|ctx-&gt;argv
(braket
l_int|0
)braket
op_assign
l_char|&squot;-&squot;
suffix:semicolon
r_goto
id|unknown
suffix:semicolon
)brace
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
id|ctx-&gt;flags
op_amp
id|PARSE_OPT_KEEP_DASHDASH
)paren
)paren
(brace
id|ctx-&gt;argc
op_decrement
suffix:semicolon
id|ctx-&gt;argv
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|internal_help
op_logical_and
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
r_return
id|usage_with_options_internal
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|internal_help
op_logical_and
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
r_return
id|parse_options_usage
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|parse_long_opt
c_func
(paren
id|ctx
comma
id|arg
op_plus
l_int|2
comma
id|options
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|parse_options_usage
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|options
comma
l_int|1
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_goto
id|unknown
suffix:semicolon
)brace
r_continue
suffix:semicolon
id|unknown
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctx-&gt;flags
op_amp
id|PARSE_OPT_KEEP_UNKNOWN
)paren
)paren
r_return
id|PARSE_OPT_UNKNOWN
suffix:semicolon
id|ctx-&gt;out
(braket
id|ctx-&gt;cpidx
op_increment
)braket
op_assign
id|ctx-&gt;argv
(braket
l_int|0
)braket
suffix:semicolon
id|ctx-&gt;opt
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|PARSE_OPT_DONE
suffix:semicolon
)brace
DECL|function|parse_options_end
r_int
id|parse_options_end
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
id|ctx
)paren
(brace
id|memmove
c_func
(paren
id|ctx-&gt;out
op_plus
id|ctx-&gt;cpidx
comma
id|ctx-&gt;argv
comma
id|ctx-&gt;argc
op_star
r_sizeof
(paren
op_star
id|ctx-&gt;out
)paren
)paren
suffix:semicolon
id|ctx-&gt;out
(braket
id|ctx-&gt;cpidx
op_plus
id|ctx-&gt;argc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ctx-&gt;cpidx
op_plus
id|ctx-&gt;argc
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
r_char
op_star
id|prefix
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
id|parse_opt_ctx_t
id|ctx
suffix:semicolon
id|parse_options_start
c_func
(paren
op_amp
id|ctx
comma
id|argc
comma
id|argv
comma
id|prefix
comma
id|options
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|parse_options_step
c_func
(paren
op_amp
id|ctx
comma
id|options
comma
id|usagestr
)paren
)paren
(brace
r_case
id|PARSE_OPT_HELP
suffix:colon
m_exit
(paren
l_int|129
)paren
suffix:semicolon
r_case
id|PARSE_OPT_NON_OPTION
suffix:colon
r_case
id|PARSE_OPT_DONE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* PARSE_OPT_UNKNOWN */
r_if
c_cond
(paren
id|ctx.argv
(braket
l_int|0
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|error
c_func
(paren
l_string|&quot;unknown option `%s&squot;&quot;
comma
id|ctx.argv
(braket
l_int|0
)braket
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
c_func
(paren
l_string|&quot;unknown switch `%c&squot;&quot;
comma
op_star
id|ctx.opt
)paren
suffix:semicolon
)brace
id|usage_with_options
c_func
(paren
id|usagestr
comma
id|options
)paren
suffix:semicolon
)brace
id|precompose_argv
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_return
id|parse_options_end
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
)brace
DECL|function|usage_argh
r_static
r_int
id|usage_argh
c_func
(paren
r_const
r_struct
id|option
op_star
id|opts
comma
id|FILE
op_star
id|outfile
)paren
(brace
r_const
r_char
op_star
id|s
suffix:semicolon
r_int
id|literal
op_assign
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_LITERAL_ARGHELP
)paren
op_logical_or
op_logical_neg
id|opts-&gt;argh
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_OPTARG
)paren
r_if
c_cond
(paren
id|opts-&gt;long_name
)paren
id|s
op_assign
id|literal
ques
c_cond
l_string|&quot;[=%s]&quot;
suffix:colon
l_string|&quot;[=&lt;%s&gt;]&quot;
suffix:semicolon
r_else
id|s
op_assign
id|literal
ques
c_cond
l_string|&quot;[%s]&quot;
suffix:colon
l_string|&quot;[&lt;%s&gt;]&quot;
suffix:semicolon
r_else
id|s
op_assign
id|literal
ques
c_cond
l_string|&quot; %s&quot;
suffix:colon
l_string|&quot; &lt;%s&gt;&quot;
suffix:semicolon
r_return
id|utf8_fprintf
c_func
(paren
id|outfile
comma
id|s
comma
id|opts-&gt;argh
ques
c_cond
id|_
c_func
(paren
id|opts-&gt;argh
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;...&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|macro|USAGE_OPTS_WIDTH
mdefine_line|#define USAGE_OPTS_WIDTH 24
DECL|macro|USAGE_GAP
mdefine_line|#define USAGE_GAP         2
DECL|function|usage_with_options_internal
r_static
r_int
id|usage_with_options_internal
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
id|ctx
comma
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
comma
r_int
id|err
)paren
(brace
id|FILE
op_star
id|outfile
op_assign
id|err
ques
c_cond
id|stderr
suffix:colon
id|stdout
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usagestr
)paren
r_return
id|PARSE_OPT_HELP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|ctx
op_logical_and
id|ctx-&gt;flags
op_amp
id|PARSE_OPT_SHELL_EVAL
)paren
id|fprintf
c_func
(paren
id|outfile
comma
l_string|&quot;cat &lt;&lt;&bslash;&bslash;EOF&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf_ln
c_func
(paren
id|outfile
comma
id|_
c_func
(paren
l_string|&quot;usage: %s&quot;
)paren
comma
id|_
c_func
(paren
op_star
id|usagestr
op_increment
)paren
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
multiline_comment|/* TRANSLATORS: the colon here should align with the&n;&t;&t;   one in &quot;usage: %s&quot; translation */
id|fprintf_ln
c_func
(paren
id|outfile
comma
id|_
c_func
(paren
l_string|&quot;   or: %s&quot;
)paren
comma
id|_
c_func
(paren
op_star
id|usagestr
op_increment
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|usagestr
)paren
(brace
r_if
c_cond
(paren
op_star
op_star
id|usagestr
)paren
id|fprintf_ln
c_func
(paren
id|outfile
comma
id|_
c_func
(paren
l_string|&quot;    %s&quot;
)paren
comma
id|_
c_func
(paren
op_star
id|usagestr
)paren
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|usagestr
op_increment
suffix:semicolon
)brace
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
id|outfile
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
id|outfile
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
id|outfile
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|_
c_func
(paren
id|opts-&gt;help
)paren
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
id|outfile
comma
l_string|&quot;    &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;short_name
)paren
(brace
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NODASH
)paren
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|outfile
comma
l_string|&quot;%c&quot;
comma
id|opts-&gt;short_name
)paren
suffix:semicolon
r_else
id|pos
op_add_assign
id|fprintf
c_func
(paren
id|outfile
comma
l_string|&quot;-%c&quot;
comma
id|opts-&gt;short_name
)paren
suffix:semicolon
)brace
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
id|outfile
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
id|outfile
comma
l_string|&quot;--%s&quot;
comma
id|opts-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;type
op_eq
id|OPTION_NUMBER
)paren
id|pos
op_add_assign
id|utf8_fprintf
c_func
(paren
id|outfile
comma
id|_
c_func
(paren
l_string|&quot;-NUM&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_LITERAL_ARGHELP
)paren
op_logical_or
op_logical_neg
(paren
id|opts-&gt;flags
op_amp
id|PARSE_OPT_NOARG
)paren
)paren
id|pos
op_add_assign
id|usage_argh
c_func
(paren
id|opts
comma
id|outfile
)paren
suffix:semicolon
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
id|outfile
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
id|outfile
comma
l_string|&quot;%*s%s&bslash;n&quot;
comma
id|pad
op_plus
id|USAGE_GAP
comma
l_string|&quot;&quot;
comma
id|_
c_func
(paren
id|opts-&gt;help
)paren
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|outfile
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|ctx
op_logical_and
id|ctx-&gt;flags
op_amp
id|PARSE_OPT_SHELL_EVAL
)paren
id|fputs
c_func
(paren
l_string|&quot;EOF&bslash;n&quot;
comma
id|outfile
)paren
suffix:semicolon
r_return
id|PARSE_OPT_HELP
suffix:semicolon
)brace
DECL|function|usage_with_options
r_void
id|NORETURN
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
l_int|NULL
comma
id|usagestr
comma
id|opts
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
m_exit
(paren
l_int|129
)paren
suffix:semicolon
)brace
DECL|function|usage_msg_opt
r_void
id|NORETURN
id|usage_msg_opt
c_func
(paren
r_const
r_char
op_star
id|msg
comma
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
id|options
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&bslash;n&quot;
comma
id|msg
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|usagestr
comma
id|options
)paren
suffix:semicolon
)brace
DECL|function|parse_options_usage
r_static
r_int
id|parse_options_usage
c_func
(paren
r_struct
id|parse_opt_ctx_t
op_star
id|ctx
comma
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
id|err
)paren
(brace
r_return
id|usage_with_options_internal
c_func
(paren
id|ctx
comma
id|usagestr
comma
id|opts
comma
l_int|0
comma
id|err
)paren
suffix:semicolon
)brace
eof
