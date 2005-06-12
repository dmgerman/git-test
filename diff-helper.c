multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|pickaxe
r_static
r_const
r_char
op_star
id|pickaxe
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pickaxe_opts
r_static
r_int
id|pickaxe_opts
op_assign
l_int|0
suffix:semicolon
DECL|variable|orderfile
r_static
r_const
r_char
op_star
id|orderfile
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|diff_filter
r_static
r_const
r_char
op_star
id|diff_filter
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|inter_name_termination
r_static
r_int
id|inter_name_termination
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
DECL|function|flush_them
r_static
r_void
id|flush_them
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
id|diffcore_std_no_resolve
c_func
(paren
id|av
op_plus
l_int|1
comma
id|pickaxe
comma
id|pickaxe_opts
comma
id|orderfile
comma
id|diff_filter
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
id|DIFF_FORMAT_PATCH
)paren
suffix:semicolon
)brace
DECL|variable|diff_helper_usage
r_static
r_const
r_char
op_star
id|diff_helper_usage
op_assign
l_string|&quot;git-diff-helper [-z] [-S&lt;string&gt;] [-O&lt;orderfile&gt;] paths...&quot;
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
r_const
r_char
op_star
id|garbage_flush_format
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
l_char|&squot;z&squot;
)paren
id|line_termination
op_assign
id|inter_name_termination
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
l_char|&squot;S&squot;
)paren
(brace
id|pickaxe
op_assign
id|av
(braket
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_string|&quot;--pickaxe-all&quot;
)paren
)paren
id|pickaxe_opts
op_assign
id|DIFF_PICKAXE_ALL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_string|&quot;--diff-filter=&quot;
comma
l_int|14
)paren
)paren
id|diff_filter
op_assign
id|av
(braket
l_int|1
)braket
op_plus
l_int|14
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_string|&quot;-O&quot;
comma
l_int|2
)paren
)paren
id|orderfile
op_assign
id|av
(braket
l_int|1
)braket
op_plus
l_int|2
suffix:semicolon
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
id|garbage_flush_format
op_assign
(paren
id|line_termination
op_eq
l_int|0
)paren
ques
c_cond
l_string|&quot;%s&quot;
suffix:colon
l_string|&quot;%s&bslash;n&quot;
suffix:semicolon
multiline_comment|/* the remaining parameters are paths patterns */
id|diff_setup
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|old_mode
comma
id|new_mode
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
r_char
id|old_path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|status
comma
id|score
comma
id|two_paths
suffix:semicolon
r_char
id|new_path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|ep
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
r_switch
c_cond
(paren
id|sb.buf
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;:&squot;
suffix:colon
multiline_comment|/* parse the first part up to the status */
id|cp
op_assign
id|sb.buf
op_plus
l_int|1
suffix:semicolon
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
op_star
id|cp
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_break
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
op_star
id|cp
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_break
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
r_break
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_break
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
r_break
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_break
suffix:semicolon
id|status
op_assign
op_star
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
l_string|&quot;MCRNDU&quot;
comma
id|status
)paren
)paren
r_break
suffix:semicolon
id|two_paths
op_assign
id|score
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_char|&squot;R&squot;
op_logical_or
id|status
op_eq
l_char|&squot;C&squot;
)paren
id|two_paths
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* pick up score if exists */
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|cp
comma
l_string|&quot;%d&quot;
comma
op_amp
id|score
)paren
op_ne
l_int|1
)paren
id|score
op_assign
l_int|0
suffix:semicolon
id|cp
op_assign
id|strchr
c_func
(paren
id|cp
comma
id|inter_name_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
id|inter_name_termination
)paren
r_break
suffix:semicolon
multiline_comment|/* first pathname */
r_if
c_cond
(paren
op_logical_neg
id|line_termination
)paren
(brace
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
id|strcpy
c_func
(paren
id|old_path
comma
id|sb.buf
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|two_paths
)paren
id|strcpy
c_func
(paren
id|old_path
comma
id|cp
)paren
suffix:semicolon
r_else
(brace
id|ep
op_assign
id|strchr
c_func
(paren
id|cp
comma
id|inter_name_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ep
)paren
r_break
suffix:semicolon
id|strncpy
c_func
(paren
id|old_path
comma
id|cp
comma
id|ep
op_minus
id|cp
)paren
suffix:semicolon
id|old_path
(braket
id|ep
op_minus
id|cp
)braket
op_assign
l_int|0
suffix:semicolon
id|cp
op_assign
id|ep
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* second pathname */
r_if
c_cond
(paren
op_logical_neg
id|two_paths
)paren
id|strcpy
c_func
(paren
id|new_path
comma
id|old_path
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|line_termination
)paren
(brace
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
id|strcpy
c_func
(paren
id|new_path
comma
id|sb.buf
)paren
suffix:semicolon
)brace
r_else
id|strcpy
c_func
(paren
id|new_path
comma
id|cp
)paren
suffix:semicolon
)brace
id|diff_helper_input
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
id|old_path
comma
id|status
comma
id|score
comma
id|new_path
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|flush_them
c_func
(paren
id|ac
comma
id|av
)paren
suffix:semicolon
id|printf
c_func
(paren
id|garbage_flush_format
comma
id|sb.buf
)paren
suffix:semicolon
)brace
id|flush_them
c_func
(paren
id|ac
comma
id|av
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
