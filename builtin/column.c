macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;column.h&quot;
DECL|variable|builtin_column_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_column_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git column [options]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|colopts
r_static
r_int
r_int
id|colopts
suffix:semicolon
DECL|function|column_config
r_static
r_int
id|column_config
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
r_return
id|git_column_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
comma
op_amp
id|colopts
)paren
suffix:semicolon
)brace
DECL|function|cmd_column
r_int
id|cmd_column
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
id|string_list
id|list
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|column_options
id|copts
suffix:semicolon
r_const
r_char
op_star
id|command
op_assign
l_int|NULL
comma
op_star
id|real_command
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;command&quot;
comma
op_amp
id|real_command
comma
id|N_
c_func
(paren
l_string|&quot;name&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;lookup config vars&quot;
)paren
)paren
comma
id|OPT_COLUMN
c_func
(paren
l_int|0
comma
l_string|&quot;mode&quot;
comma
op_amp
id|colopts
comma
id|N_
c_func
(paren
l_string|&quot;layout to use&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;raw-mode&quot;
comma
op_amp
id|colopts
comma
id|N_
c_func
(paren
l_string|&quot;layout to use&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;width&quot;
comma
op_amp
id|copts.width
comma
id|N_
c_func
(paren
l_string|&quot;Maximum width&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;indent&quot;
comma
op_amp
id|copts.indent
comma
id|N_
c_func
(paren
l_string|&quot;string&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;Padding space on left border&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;nl&quot;
comma
op_amp
id|copts.nl
comma
id|N_
c_func
(paren
l_string|&quot;Padding space on right border&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;padding&quot;
comma
op_amp
id|copts.padding
comma
id|N_
c_func
(paren
l_string|&quot;Padding space between columns&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
multiline_comment|/* This one is special and must be the first one */
r_if
c_cond
(paren
id|argc
OG
l_int|1
op_logical_and
id|starts_with
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--command=&quot;
)paren
)paren
(brace
id|command
op_assign
id|argv
(braket
l_int|1
)braket
op_plus
l_int|10
suffix:semicolon
id|git_config
c_func
(paren
id|column_config
comma
(paren
r_void
op_star
)paren
id|command
)paren
suffix:semicolon
)brace
r_else
id|git_config
c_func
(paren
id|column_config
comma
l_int|NULL
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|copts
comma
l_int|0
comma
r_sizeof
(paren
id|copts
)paren
)paren
suffix:semicolon
id|copts.width
op_assign
id|term_columns
c_func
(paren
)paren
suffix:semicolon
id|copts.padding
op_assign
l_int|1
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
l_string|&quot;&quot;
comma
id|options
comma
id|builtin_column_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
)paren
id|usage_with_options
c_func
(paren
id|builtin_column_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|real_command
op_logical_or
id|command
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|real_command
op_logical_or
op_logical_neg
id|command
op_logical_or
id|strcmp
c_func
(paren
id|real_command
comma
id|command
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--command must be the first argument&quot;
)paren
)paren
suffix:semicolon
)brace
id|finalize_colopts
c_func
(paren
op_amp
id|colopts
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|strbuf_getline
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
id|string_list_append
c_func
(paren
op_amp
id|list
comma
id|sb.buf
)paren
suffix:semicolon
id|print_columns
c_func
(paren
op_amp
id|list
comma
id|colopts
comma
op_amp
id|copts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
