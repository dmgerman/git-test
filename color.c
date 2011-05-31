macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;color.h&quot;
DECL|variable|git_use_color_default
r_int
id|git_use_color_default
op_assign
l_int|0
suffix:semicolon
DECL|function|parse_color
r_static
r_int
id|parse_color
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_static
r_const
r_char
op_star
r_const
id|color_names
(braket
)braket
op_assign
(brace
l_string|&quot;normal&quot;
comma
l_string|&quot;black&quot;
comma
l_string|&quot;red&quot;
comma
l_string|&quot;green&quot;
comma
l_string|&quot;yellow&quot;
comma
l_string|&quot;blue&quot;
comma
l_string|&quot;magenta&quot;
comma
l_string|&quot;cyan&quot;
comma
l_string|&quot;white&quot;
)brace
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|color_names
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|str
op_assign
id|color_names
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncasecmp
c_func
(paren
id|name
comma
id|str
comma
id|len
)paren
op_logical_and
op_logical_neg
id|str
(braket
id|len
)braket
)paren
r_return
id|i
l_int|1
suffix:semicolon
)brace
id|i
op_assign
id|strtol
c_func
(paren
id|name
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
id|name
op_eq
id|len
op_logical_and
id|i
op_ge
l_int|1
op_logical_and
id|i
op_le
l_int|255
)paren
r_return
id|i
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
DECL|function|parse_attr
r_static
r_int
id|parse_attr
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_static
r_const
r_int
id|attr_values
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|5
comma
l_int|7
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
r_const
id|attr_names
(braket
)braket
op_assign
(brace
l_string|&quot;bold&quot;
comma
l_string|&quot;dim&quot;
comma
l_string|&quot;ul&quot;
comma
l_string|&quot;blink&quot;
comma
l_string|&quot;reverse&quot;
)brace
suffix:semicolon
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|attr_names
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|str
op_assign
id|attr_names
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncasecmp
c_func
(paren
id|name
comma
id|str
comma
id|len
)paren
op_logical_and
op_logical_neg
id|str
(braket
id|len
)braket
)paren
r_return
id|attr_values
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|color_parse
r_void
id|color_parse
c_func
(paren
r_const
r_char
op_star
id|value
comma
r_const
r_char
op_star
id|var
comma
r_char
op_star
id|dst
)paren
(brace
id|color_parse_mem
c_func
(paren
id|value
comma
id|strlen
c_func
(paren
id|value
)paren
comma
id|var
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|color_parse_mem
r_void
id|color_parse_mem
c_func
(paren
r_const
r_char
op_star
id|value
comma
r_int
id|value_len
comma
r_const
r_char
op_star
id|var
comma
r_char
op_star
id|dst
)paren
(brace
r_const
r_char
op_star
id|ptr
op_assign
id|value
suffix:semicolon
r_int
id|len
op_assign
id|value_len
suffix:semicolon
r_int
r_int
id|attr
op_assign
l_int|0
suffix:semicolon
r_int
id|fg
op_assign
l_int|2
suffix:semicolon
r_int
id|bg
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncasecmp
c_func
(paren
id|value
comma
l_string|&quot;reset&quot;
comma
id|len
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|dst
comma
id|GIT_COLOR_RESET
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* [fg [bg]] [attr]... */
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_const
r_char
op_star
id|word
op_assign
id|ptr
suffix:semicolon
r_int
id|val
comma
id|wordlen
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
id|word
(braket
id|wordlen
)braket
)paren
)paren
(brace
id|wordlen
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
id|ptr
op_assign
id|word
op_plus
id|wordlen
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
op_star
id|ptr
)paren
)paren
(brace
id|ptr
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
id|val
op_assign
id|parse_color
c_func
(paren
id|word
comma
id|wordlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ge
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|fg
op_eq
l_int|2
)paren
(brace
id|fg
op_assign
id|val
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bg
op_eq
l_int|2
)paren
(brace
id|bg
op_assign
id|val
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_goto
id|bad
suffix:semicolon
)brace
id|val
op_assign
id|parse_attr
c_func
(paren
id|word
comma
id|wordlen
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|val
)paren
id|attr
op_or_assign
(paren
l_int|1
op_lshift
id|val
)paren
suffix:semicolon
r_else
r_goto
id|bad
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attr
op_logical_or
id|fg
op_ge
l_int|0
op_logical_or
id|bg
op_ge
l_int|0
)paren
(brace
r_int
id|sep
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|dst
op_increment
op_assign
l_char|&squot;&bslash;033&squot;
suffix:semicolon
op_star
id|dst
op_increment
op_assign
l_char|&squot;[&squot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|bit
op_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|attr
op_amp
id|bit
)paren
)paren
r_continue
suffix:semicolon
id|attr
op_and_assign
op_complement
id|bit
suffix:semicolon
r_if
c_cond
(paren
id|sep
op_increment
)paren
op_star
id|dst
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|dst
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fg
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sep
op_increment
)paren
op_star
id|dst
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
r_if
c_cond
(paren
id|fg
OL
l_int|8
)paren
(brace
op_star
id|dst
op_increment
op_assign
l_char|&squot;3&squot;
suffix:semicolon
op_star
id|dst
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|fg
suffix:semicolon
)brace
r_else
(brace
id|dst
op_add_assign
id|sprintf
c_func
(paren
id|dst
comma
l_string|&quot;38;5;%d&quot;
comma
id|fg
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bg
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sep
op_increment
)paren
op_star
id|dst
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
r_if
c_cond
(paren
id|bg
OL
l_int|8
)paren
(brace
op_star
id|dst
op_increment
op_assign
l_char|&squot;4&squot;
suffix:semicolon
op_star
id|dst
op_increment
op_assign
l_char|&squot;0&squot;
op_plus
id|bg
suffix:semicolon
)brace
r_else
(brace
id|dst
op_add_assign
id|sprintf
c_func
(paren
id|dst
comma
l_string|&quot;48;5;%d&quot;
comma
id|bg
)paren
suffix:semicolon
)brace
)brace
op_star
id|dst
op_increment
op_assign
l_char|&squot;m&squot;
suffix:semicolon
)brace
op_star
id|dst
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
id|bad
suffix:colon
id|die
c_func
(paren
l_string|&quot;bad color value &squot;%.*s&squot; for variable &squot;%s&squot;&quot;
comma
id|value_len
comma
id|value
comma
id|var
)paren
suffix:semicolon
)brace
DECL|function|git_config_colorbool
r_int
id|git_config_colorbool
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
r_int
id|stdout_is_tty
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;never&quot;
)paren
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
l_string|&quot;always&quot;
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
l_string|&quot;auto&quot;
)paren
)paren
r_goto
id|auto_color
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|var
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Missing or explicit false to turn off colorization */
r_if
c_cond
(paren
op_logical_neg
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* any normal truth value defaults to &squot;auto&squot; */
id|auto_color
suffix:colon
r_if
c_cond
(paren
id|stdout_is_tty
OL
l_int|0
)paren
id|stdout_is_tty
op_assign
id|isatty
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stdout_is_tty
op_logical_or
(paren
id|pager_in_use
c_func
(paren
)paren
op_logical_and
id|pager_use_color
)paren
)paren
(brace
r_char
op_star
id|term
op_assign
id|getenv
c_func
(paren
l_string|&quot;TERM&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|term
op_logical_and
id|strcmp
c_func
(paren
id|term
comma
l_string|&quot;dumb&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_color_default_config
r_int
id|git_color_default_config
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
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
DECL|function|color_print_strbuf
r_void
id|color_print_strbuf
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|color
comma
r_const
r_struct
id|strbuf
op_star
id|sb
)paren
(brace
r_if
c_cond
(paren
op_star
id|color
)paren
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&quot;
comma
id|color
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&quot;
comma
id|sb-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|color
)paren
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&quot;
comma
id|GIT_COLOR_RESET
)paren
suffix:semicolon
)brace
DECL|function|color_vfprintf
r_static
r_int
id|color_vfprintf
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|color
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
comma
r_const
r_char
op_star
id|trail
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|color
)paren
id|r
op_add_assign
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&quot;
comma
id|color
)paren
suffix:semicolon
id|r
op_add_assign
id|vfprintf
c_func
(paren
id|fp
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|color
)paren
id|r
op_add_assign
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&quot;
comma
id|GIT_COLOR_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trail
)paren
id|r
op_add_assign
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&quot;
comma
id|trail
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|color_fprintf
r_int
id|color_fprintf
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|color
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|r
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|r
op_assign
id|color_vfprintf
c_func
(paren
id|fp
comma
id|color
comma
id|fmt
comma
id|args
comma
l_int|NULL
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|color_fprintf_ln
r_int
id|color_fprintf_ln
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|color
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|r
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|r
op_assign
id|color_vfprintf
c_func
(paren
id|fp
comma
id|color
comma
id|fmt
comma
id|args
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|color_is_nil
r_int
id|color_is_nil
c_func
(paren
r_const
r_char
op_star
id|c
)paren
(brace
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|c
comma
l_string|&quot;NIL&quot;
)paren
suffix:semicolon
)brace
eof
