macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|all_attrs
r_static
r_int
id|all_attrs
suffix:semicolon
DECL|variable|stdin_paths
r_static
r_int
id|stdin_paths
suffix:semicolon
DECL|variable|check_attr_usage
r_static
r_const
r_char
op_star
r_const
id|check_attr_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git check-attr [-a | --all | attr...] [--] pathname...&quot;
comma
l_string|&quot;git check-attr --stdin [-a | --all | attr...] &lt; &lt;list-of-paths&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|null_term_line
r_static
r_int
id|null_term_line
suffix:semicolon
DECL|variable|check_attr_options
r_static
r_const
r_struct
id|option
id|check_attr_options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;a&squot;
comma
l_string|&quot;all&quot;
comma
op_amp
id|all_attrs
comma
l_string|&quot;report all attributes set on file&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|stdin_paths
comma
l_string|&quot;read file names from stdin&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;z&squot;
comma
l_int|NULL
comma
op_amp
id|null_term_line
comma
l_string|&quot;input paths are terminated by a null character&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
DECL|function|output_attr
r_static
r_void
id|output_attr
c_func
(paren
r_int
id|cnt
comma
r_struct
id|git_attr_check
op_star
id|check
comma
r_const
r_char
op_star
id|file
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|check
(braket
id|j
)braket
dot
id|value
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;set&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_FALSE
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;unset&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_UNSET
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;unspecified&quot;
suffix:semicolon
id|quote_c_style
c_func
(paren
id|file
comma
l_int|NULL
comma
id|stdout
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;: %s: %s&bslash;n&quot;
comma
id|git_attr_name
c_func
(paren
id|check
(braket
id|j
)braket
dot
id|attr
)paren
comma
id|value
)paren
suffix:semicolon
)brace
)brace
DECL|function|check_attr
r_static
r_void
id|check_attr
c_func
(paren
r_int
id|cnt
comma
r_struct
id|git_attr_check
op_star
id|check
comma
r_const
r_char
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|check
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|git_check_attr
c_func
(paren
id|file
comma
id|cnt
comma
id|check
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git_check_attr died&quot;
)paren
suffix:semicolon
id|output_attr
c_func
(paren
id|cnt
comma
id|check
comma
id|file
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|git_all_attrs
c_func
(paren
id|file
comma
op_amp
id|cnt
comma
op_amp
id|check
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git_all_attrs died&quot;
)paren
suffix:semicolon
id|output_attr
c_func
(paren
id|cnt
comma
id|check
comma
id|file
)paren
suffix:semicolon
id|free
c_func
(paren
id|check
)paren
suffix:semicolon
)brace
)brace
DECL|function|check_attr_stdin_paths
r_static
r_void
id|check_attr_stdin_paths
c_func
(paren
r_int
id|cnt
comma
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_struct
id|strbuf
id|buf
comma
id|nbuf
suffix:semicolon
r_int
id|line_termination
op_assign
id|null_term_line
ques
c_cond
l_int|0
suffix:colon
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|nbuf
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
id|line_termination
)paren
op_ne
id|EOF
)paren
(brace
r_if
c_cond
(paren
id|line_termination
op_logical_and
id|buf.buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unquote_c_style
c_func
(paren
op_amp
id|nbuf
comma
id|buf.buf
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;line is badly quoted&quot;
)paren
suffix:semicolon
id|strbuf_swap
c_func
(paren
op_amp
id|buf
comma
op_amp
id|nbuf
)paren
suffix:semicolon
)brace
id|check_attr
c_func
(paren
id|cnt
comma
id|check
comma
id|buf.buf
)paren
suffix:semicolon
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;attribute to stdout&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
)brace
DECL|function|error_with_usage
r_static
id|NORETURN
r_void
id|error_with_usage
c_func
(paren
r_const
r_char
op_star
id|msg
)paren
(brace
id|error
c_func
(paren
l_string|&quot;%s&quot;
comma
id|msg
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|check_attr_usage
comma
id|check_attr_options
)paren
suffix:semicolon
)brace
DECL|function|cmd_check_attr
r_int
id|cmd_check_attr
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
r_struct
id|git_attr_check
op_star
id|check
suffix:semicolon
r_int
id|cnt
comma
id|i
comma
id|doubledash
comma
id|filei
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
id|check_attr_options
comma
id|check_attr_usage
comma
id|PARSE_OPT_KEEP_DASHDASH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|die
c_func
(paren
l_string|&quot;invalid cache&quot;
)paren
suffix:semicolon
)brace
id|doubledash
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|doubledash
OL
l_int|0
op_logical_and
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
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
id|i
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
id|doubledash
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/* Process --all and/or attribute arguments: */
r_if
c_cond
(paren
id|all_attrs
)paren
(brace
r_if
c_cond
(paren
id|doubledash
op_ge
l_int|1
)paren
id|error_with_usage
c_func
(paren
l_string|&quot;Attributes and --all both specified&quot;
)paren
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
id|filei
op_assign
id|doubledash
op_plus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|doubledash
op_eq
l_int|0
)paren
(brace
id|error_with_usage
c_func
(paren
l_string|&quot;No attribute specified&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|doubledash
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|argc
)paren
id|error_with_usage
c_func
(paren
l_string|&quot;No attribute specified&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stdin_paths
)paren
(brace
multiline_comment|/* Treat all arguments as attribute names. */
id|cnt
op_assign
id|argc
suffix:semicolon
id|filei
op_assign
id|argc
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Treat exactly one argument as an attribute name. */
id|cnt
op_assign
l_int|1
suffix:semicolon
id|filei
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|cnt
op_assign
id|doubledash
suffix:semicolon
id|filei
op_assign
id|doubledash
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Check file argument(s): */
r_if
c_cond
(paren
id|stdin_paths
)paren
(brace
r_if
c_cond
(paren
id|filei
OL
id|argc
)paren
id|error_with_usage
c_func
(paren
l_string|&quot;Can&squot;t specify files with --stdin&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|filei
op_ge
id|argc
)paren
id|error_with_usage
c_func
(paren
l_string|&quot;No file specified&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|all_attrs
)paren
(brace
id|check
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|check
op_assign
id|xcalloc
c_func
(paren
id|cnt
comma
r_sizeof
(paren
op_star
id|check
)paren
)paren
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_struct
id|git_attr
op_star
id|a
suffix:semicolon
id|name
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
id|a
op_assign
id|git_attr
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: not a valid attribute name&quot;
comma
id|name
)paren
suffix:semicolon
id|check
(braket
id|i
)braket
dot
id|attr
op_assign
id|a
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|stdin_paths
)paren
id|check_attr_stdin_paths
c_func
(paren
id|cnt
comma
id|check
)paren
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
id|filei
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
id|check_attr
c_func
(paren
id|cnt
comma
id|check
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;attribute to stdout&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
