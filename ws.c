multiline_comment|/*&n; * Whitespace rules&n; *&n; * Copyright (c) 2007 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
DECL|struct|whitespace_rule
r_static
r_struct
id|whitespace_rule
(brace
DECL|member|rule_name
r_const
r_char
op_star
id|rule_name
suffix:semicolon
DECL|member|rule_bits
r_int
id|rule_bits
suffix:semicolon
DECL|variable|whitespace_rule_names
)brace
id|whitespace_rule_names
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;trailing-space&quot;
comma
id|WS_TRAILING_SPACE
)brace
comma
(brace
l_string|&quot;space-before-tab&quot;
comma
id|WS_SPACE_BEFORE_TAB
)brace
comma
(brace
l_string|&quot;indent-with-non-tab&quot;
comma
id|WS_INDENT_WITH_NON_TAB
)brace
comma
(brace
l_string|&quot;cr-at-eol&quot;
comma
id|WS_CR_AT_EOL
)brace
comma
)brace
suffix:semicolon
DECL|function|parse_whitespace_rule
r_int
id|parse_whitespace_rule
c_func
(paren
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|rule
op_assign
id|WS_DEFAULT_RULE
suffix:semicolon
r_while
c_loop
(paren
id|string
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|ep
suffix:semicolon
r_int
id|negated
op_assign
l_int|0
suffix:semicolon
id|string
op_assign
id|string
op_plus
id|strspn
c_func
(paren
id|string
comma
l_string|&quot;, &bslash;t&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|ep
op_assign
id|strchr
c_func
(paren
id|string
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ep
)paren
id|len
op_assign
id|strlen
c_func
(paren
id|string
)paren
suffix:semicolon
r_else
id|len
op_assign
id|ep
id|string
suffix:semicolon
r_if
c_cond
(paren
op_star
id|string
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|negated
op_assign
l_int|1
suffix:semicolon
id|string
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
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
id|whitespace_rule_names
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|whitespace_rule_names
(braket
id|i
)braket
dot
id|rule_name
comma
id|string
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|negated
)paren
id|rule
op_and_assign
op_complement
id|whitespace_rule_names
(braket
id|i
)braket
dot
id|rule_bits
suffix:semicolon
r_else
id|rule
op_or_assign
id|whitespace_rule_names
(braket
id|i
)braket
dot
id|rule_bits
suffix:semicolon
r_break
suffix:semicolon
)brace
id|string
op_assign
id|ep
suffix:semicolon
)brace
r_return
id|rule
suffix:semicolon
)brace
DECL|function|setup_whitespace_attr_check
r_static
r_void
id|setup_whitespace_attr_check
c_func
(paren
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_static
r_struct
id|git_attr
op_star
id|attr_whitespace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_whitespace
)paren
id|attr_whitespace
op_assign
id|git_attr
c_func
(paren
l_string|&quot;whitespace&quot;
comma
l_int|10
)paren
suffix:semicolon
id|check
(braket
l_int|0
)braket
dot
id|attr
op_assign
id|attr_whitespace
suffix:semicolon
)brace
DECL|function|whitespace_rule
r_int
id|whitespace_rule
c_func
(paren
r_const
r_char
op_star
id|pathname
)paren
(brace
r_struct
id|git_attr_check
id|attr_whitespace_rule
suffix:semicolon
id|setup_whitespace_attr_check
c_func
(paren
op_amp
id|attr_whitespace_rule
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_checkattr
c_func
(paren
id|pathname
comma
l_int|1
comma
op_amp
id|attr_whitespace_rule
)paren
)paren
(brace
r_const
r_char
op_star
id|value
suffix:semicolon
id|value
op_assign
id|attr_whitespace_rule.value
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
(brace
multiline_comment|/* true (whitespace) */
r_int
id|all_rule
op_assign
l_int|0
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
id|whitespace_rule_names
)paren
suffix:semicolon
id|i
op_increment
)paren
id|all_rule
op_or_assign
id|whitespace_rule_names
(braket
id|i
)braket
dot
id|rule_bits
suffix:semicolon
r_return
id|all_rule
suffix:semicolon
)brace
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
(brace
multiline_comment|/* false (-whitespace) */
r_return
l_int|0
suffix:semicolon
)brace
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
(brace
multiline_comment|/* reset to default (!whitespace) */
r_return
id|whitespace_rule_cfg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* string */
r_return
id|parse_whitespace_rule
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
id|whitespace_rule_cfg
suffix:semicolon
)brace
)brace
multiline_comment|/* The returned string should be freed by the caller. */
DECL|function|whitespace_error_string
r_char
op_star
id|whitespace_error_string
c_func
(paren
r_int
id|ws
)paren
(brace
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|ws
op_amp
id|WS_TRAILING_SPACE
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|err
comma
l_string|&quot;trailing whitespace&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ws
op_amp
id|WS_SPACE_BEFORE_TAB
)paren
(brace
r_if
c_cond
(paren
id|err.len
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|err
comma
l_string|&quot;, &quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|err
comma
l_string|&quot;space before tab in indent&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ws
op_amp
id|WS_INDENT_WITH_NON_TAB
)paren
(brace
r_if
c_cond
(paren
id|err.len
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|err
comma
l_string|&quot;, &quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|err
comma
l_string|&quot;indent with spaces&quot;
)paren
suffix:semicolon
)brace
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|err
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* If stream is non-NULL, emits the line after checking. */
DECL|function|ws_check_emit_1
r_static
r_int
id|ws_check_emit_1
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
id|ws_rule
comma
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|set
comma
r_const
r_char
op_star
id|reset
comma
r_const
r_char
op_star
id|ws
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|written
op_assign
l_int|0
suffix:semicolon
r_int
id|trailing_whitespace
op_assign
l_int|1
suffix:semicolon
r_int
id|trailing_newline
op_assign
l_int|0
suffix:semicolon
r_int
id|trailing_carriage_return
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Logic is simpler if we temporarily ignore the trailing newline. */
r_if
c_cond
(paren
id|len
OG
l_int|0
op_logical_and
id|line
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|trailing_newline
op_assign
l_int|1
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ws_rule
op_amp
id|WS_CR_AT_EOL
)paren
op_logical_and
id|len
OG
l_int|0
op_logical_and
id|line
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|trailing_carriage_return
op_assign
l_int|1
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Check for trailing whitespace. */
r_if
c_cond
(paren
id|ws_rule
op_amp
id|WS_TRAILING_SPACE
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|len
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|line
(braket
id|i
)braket
)paren
)paren
(brace
id|trailing_whitespace
op_assign
id|i
suffix:semicolon
id|result
op_or_assign
id|WS_TRAILING_SPACE
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Check for space before tab in initial indent. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|line
(braket
id|i
)braket
op_eq
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|i
)braket
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ws_rule
op_amp
id|WS_SPACE_BEFORE_TAB
)paren
op_logical_and
id|written
OL
id|i
)paren
(brace
id|result
op_or_assign
id|WS_SPACE_BEFORE_TAB
suffix:semicolon
r_if
c_cond
(paren
id|stream
)paren
(brace
id|fputs
c_func
(paren
id|ws
comma
id|stream
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|line
op_plus
id|written
comma
id|i
id|written
comma
l_int|1
comma
id|stream
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|reset
comma
id|stream
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|stream
)paren
id|fwrite
c_func
(paren
id|line
op_plus
id|written
comma
id|i
id|written
comma
l_int|1
comma
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stream
)paren
id|fwrite
c_func
(paren
id|line
op_plus
id|i
comma
l_int|1
comma
l_int|1
comma
id|stream
)paren
suffix:semicolon
id|written
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Check for indent using non-tab. */
r_if
c_cond
(paren
(paren
id|ws_rule
op_amp
id|WS_INDENT_WITH_NON_TAB
)paren
op_logical_and
id|i
id|written
op_ge
l_int|8
)paren
(brace
id|result
op_or_assign
id|WS_INDENT_WITH_NON_TAB
suffix:semicolon
r_if
c_cond
(paren
id|stream
)paren
(brace
id|fputs
c_func
(paren
id|ws
comma
id|stream
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|line
op_plus
id|written
comma
id|i
id|written
comma
l_int|1
comma
id|stream
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|reset
comma
id|stream
)paren
suffix:semicolon
)brace
id|written
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stream
)paren
(brace
multiline_comment|/*&n;&t;&t; * Now the rest of the line starts at &quot;written&quot;.&n;&t;&t; * The non-highlighted part ends at &quot;trailing_whitespace&quot;.&n;&t;&t; */
r_if
c_cond
(paren
id|trailing_whitespace
op_eq
l_int|1
)paren
id|trailing_whitespace
op_assign
id|len
suffix:semicolon
multiline_comment|/* Emit non-highlighted (middle) segment. */
r_if
c_cond
(paren
id|trailing_whitespace
id|written
OG
l_int|0
)paren
(brace
id|fputs
c_func
(paren
id|set
comma
id|stream
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|line
op_plus
id|written
comma
id|trailing_whitespace
id|written
comma
l_int|1
comma
id|stream
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|reset
comma
id|stream
)paren
suffix:semicolon
)brace
multiline_comment|/* Highlight errors in trailing whitespace. */
r_if
c_cond
(paren
id|trailing_whitespace
op_ne
id|len
)paren
(brace
id|fputs
c_func
(paren
id|ws
comma
id|stream
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|line
op_plus
id|trailing_whitespace
comma
id|len
id|trailing_whitespace
comma
l_int|1
comma
id|stream
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|reset
comma
id|stream
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|trailing_carriage_return
)paren
id|fputc
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trailing_newline
)paren
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stream
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|ws_check_emit
r_void
id|ws_check_emit
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
id|ws_rule
comma
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|set
comma
r_const
r_char
op_star
id|reset
comma
r_const
r_char
op_star
id|ws
)paren
(brace
(paren
r_void
)paren
id|ws_check_emit_1
c_func
(paren
id|line
comma
id|len
comma
id|ws_rule
comma
id|stream
comma
id|set
comma
id|reset
comma
id|ws
)paren
suffix:semicolon
)brace
DECL|function|ws_check
r_int
id|ws_check
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
id|ws_rule
)paren
(brace
r_return
id|ws_check_emit_1
c_func
(paren
id|line
comma
id|len
comma
id|ws_rule
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|ws_blank_line
r_int
id|ws_blank_line
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
id|ws_rule
)paren
(brace
multiline_comment|/*&n;&t; * We _might_ want to treat CR differently from other&n;&t; * whitespace characters when ws_rule has WS_CR_AT_EOL, but&n;&t; * for now we just use this stupid definition.&n;&t; */
r_while
c_loop
(paren
id|len
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
op_star
id|line
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|line
op_increment
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Copy the line to the buffer while fixing whitespaces */
DECL|function|ws_fix_copy
r_int
id|ws_fix_copy
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_int
id|ws_rule
comma
r_int
op_star
id|error_count
)paren
(brace
multiline_comment|/*&n;&t; * len is number of bytes to be copied from src, starting&n;&t; * at src.  Typically src[len-1] is &squot;&bslash;n&squot;, unless this is&n;&t; * the incomplete last line.&n;&t; */
r_int
id|i
suffix:semicolon
r_int
id|add_nl_to_tail
op_assign
l_int|0
suffix:semicolon
r_int
id|add_cr_to_tail
op_assign
l_int|0
suffix:semicolon
r_int
id|fixed
op_assign
l_int|0
suffix:semicolon
r_int
id|last_tab_in_indent
op_assign
l_int|1
suffix:semicolon
r_int
id|last_space_in_indent
op_assign
l_int|1
suffix:semicolon
r_int
id|need_fix_leading_space
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/*&n;&t; * Strip trailing whitespace&n;&t; */
r_if
c_cond
(paren
(paren
id|ws_rule
op_amp
id|WS_TRAILING_SPACE
)paren
op_logical_and
(paren
l_int|2
op_le
id|len
op_logical_and
id|isspace
c_func
(paren
id|src
(braket
id|len
op_minus
l_int|2
)braket
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|src
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|add_nl_to_tail
op_assign
l_int|1
suffix:semicolon
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|len
op_logical_and
id|src
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|add_cr_to_tail
op_assign
op_logical_neg
op_logical_neg
(paren
id|ws_rule
op_amp
id|WS_CR_AT_EOL
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
OL
id|len
op_logical_and
id|isspace
c_func
(paren
id|src
(braket
id|len
l_int|1
)braket
)paren
)paren
(brace
r_while
c_loop
(paren
l_int|0
OL
id|len
op_logical_and
id|isspace
c_func
(paren
id|src
(braket
id|len
op_minus
l_int|1
)braket
)paren
)paren
id|len
op_decrement
suffix:semicolon
id|fixed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Check leading whitespaces (indent)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|ch
op_assign
id|src
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;t&squot;
)paren
(brace
id|last_tab_in_indent
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ws_rule
op_amp
id|WS_SPACE_BEFORE_TAB
)paren
op_logical_and
l_int|0
op_le
id|last_space_in_indent
)paren
id|need_fix_leading_space
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot; &squot;
)paren
(brace
id|last_space_in_indent
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ws_rule
op_amp
id|WS_INDENT_WITH_NON_TAB
)paren
op_logical_and
l_int|8
op_le
id|i
id|last_tab_in_indent
)paren
id|need_fix_leading_space
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|buf
op_assign
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|need_fix_leading_space
)paren
(brace
multiline_comment|/* Process indent ourselves */
r_int
id|consecutive_spaces
op_assign
l_int|0
suffix:semicolon
r_int
id|last
op_assign
id|last_tab_in_indent
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ws_rule
op_amp
id|WS_INDENT_WITH_NON_TAB
)paren
(brace
multiline_comment|/* have &quot;last&quot; point at one past the indent */
r_if
c_cond
(paren
id|last_tab_in_indent
OL
id|last_space_in_indent
)paren
id|last
op_assign
id|last_space_in_indent
op_plus
l_int|1
suffix:semicolon
r_else
id|last
op_assign
id|last_tab_in_indent
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * between src[0..last-1], strip the funny spaces,&n;&t;&t; * updating them to tab as needed.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|ch
op_assign
id|src
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ne
l_char|&squot; &squot;
)paren
(brace
id|consecutive_spaces
op_assign
l_int|0
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|ch
suffix:semicolon
)brace
r_else
(brace
id|consecutive_spaces
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|consecutive_spaces
op_eq
l_int|8
)paren
(brace
op_star
id|dst
op_increment
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
id|consecutive_spaces
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
l_int|0
OL
id|consecutive_spaces
op_decrement
)paren
op_star
id|dst
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|len
op_sub_assign
id|last
suffix:semicolon
id|src
op_add_assign
id|last
suffix:semicolon
id|fixed
op_assign
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_cr_to_tail
)paren
id|dst
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_if
c_cond
(paren
id|add_nl_to_tail
)paren
id|dst
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|fixed
op_logical_and
id|error_count
)paren
(paren
op_star
id|error_count
)paren
op_increment
suffix:semicolon
r_return
id|dst
op_plus
id|len
id|buf
suffix:semicolon
)brace
eof
