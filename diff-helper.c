multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &lt;limits.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|detect_rename
r_static
r_int
id|detect_rename
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_score_opt
r_static
r_int
id|diff_score_opt
op_assign
l_int|0
suffix:semicolon
DECL|function|parse_oneside_change
r_static
r_int
id|parse_oneside_change
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_int
op_star
id|mode
comma
r_int
r_char
op_star
id|sha1
comma
r_char
op_star
id|path
)paren
(brace
r_int
id|ch
comma
id|m
suffix:semicolon
id|m
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_logical_and
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;7&squot;
)paren
(brace
id|m
op_assign
(paren
id|m
op_lshift
l_int|3
)paren
op_or
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
op_star
id|mode
op_assign
id|m
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;&bslash;tblob&bslash;t&quot;
comma
l_int|6
)paren
op_logical_and
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot; blob &quot;
comma
l_int|6
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|cp
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;t&squot;
)paren
op_logical_and
op_star
id|cp
op_ne
l_char|&squot; &squot;
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
op_increment
id|cp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_diff_raw_output
r_static
r_int
id|parse_diff_raw_output
c_func
(paren
r_const
r_char
op_star
id|buf
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
comma
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|cp
op_assign
id|buf
suffix:semicolon
r_int
id|ch
comma
id|old_mode
comma
id|new_mode
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|cp
op_increment
)paren
(brace
r_case
l_char|&squot;U&squot;
suffix:colon
id|diff_unmerge
c_func
(paren
id|cp
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|parse_oneside_change
c_func
(paren
id|cp
comma
op_amp
id|new_mode
comma
id|new_sha1
comma
id|path
)paren
suffix:semicolon
id|diff_addremove
c_func
(paren
l_char|&squot;+&squot;
comma
id|new_mode
comma
id|new_sha1
comma
id|path
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
id|parse_oneside_change
c_func
(paren
id|cp
comma
op_amp
id|old_mode
comma
id|old_sha1
comma
id|path
)paren
suffix:semicolon
id|diff_addremove
c_func
(paren
l_char|&squot;-&squot;
comma
id|old_mode
comma
id|old_sha1
comma
id|path
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;*&squot;
suffix:colon
id|old_mode
op_assign
id|new_mode
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_logical_and
(paren
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;7&squot;
)paren
)paren
(brace
id|old_mode
op_assign
(paren
id|old_mode
op_lshift
l_int|3
)paren
op_or
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;-&gt;&quot;
comma
l_int|2
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_logical_and
(paren
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;7&squot;
)paren
)paren
(brace
id|new_mode
op_assign
(paren
id|new_mode
op_lshift
l_int|3
)paren
op_or
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;&bslash;tblob&bslash;t&quot;
comma
l_int|6
)paren
op_logical_and
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot; blob &quot;
comma
l_int|6
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|cp
comma
id|old_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;-&gt;&quot;
comma
l_int|2
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|cp
comma
id|new_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;t&squot;
)paren
op_logical_and
op_star
id|cp
op_ne
l_char|&squot; &squot;
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
op_increment
id|cp
)paren
suffix:semicolon
id|diff_change
c_func
(paren
id|old_mode
comma
id|new_mode
comma
id|old_sha1
comma
id|new_sha1
comma
id|path
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|diff_helper_usage
r_static
r_const
r_char
op_star
id|diff_helper_usage
op_assign
l_string|&quot;git-diff-helper [-z] [-R] [-M] paths...&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
)paren
(brace
r_struct
id|strbuf
id|sb
suffix:semicolon
r_int
id|reverse
op_assign
l_int|0
suffix:semicolon
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|ac
op_logical_and
id|av
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|av
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;R&squot;
)paren
id|reverse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|av
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;z&squot;
)paren
id|line_termination
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|av
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;M&squot;
)paren
(brace
id|detect_rename
op_assign
l_int|1
suffix:semicolon
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|av
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
id|usage
c_func
(paren
id|diff_helper_usage
)paren
suffix:semicolon
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
)brace
multiline_comment|/* the remaining parameters are paths patterns */
id|diff_setup
c_func
(paren
id|detect_rename
comma
id|diff_score_opt
comma
id|reverse
comma
l_int|1
comma
id|av
op_plus
l_int|1
comma
id|ac
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|status
suffix:semicolon
id|read_line
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb.eof
)paren
r_break
suffix:semicolon
id|status
op_assign
id|parse_diff_raw_output
c_func
(paren
id|sb.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|diff_flush
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|sb.buf
comma
id|line_termination
)paren
suffix:semicolon
)brace
)brace
id|diff_flush
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
