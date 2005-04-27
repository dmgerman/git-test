multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|function|matches_pathspec
r_static
r_int
id|matches_pathspec
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_char
op_star
op_star
id|spec
comma
r_int
id|cnt
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
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
r_int
id|speclen
op_assign
id|strlen
c_func
(paren
id|spec
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|spec
(braket
id|i
)braket
comma
id|name
comma
id|speclen
)paren
op_logical_and
id|speclen
op_le
id|namelen
op_logical_and
(paren
id|name
(braket
id|speclen
)braket
op_eq
l_int|0
op_logical_or
id|name
(braket
id|speclen
)braket
op_eq
l_char|&squot;/&squot;
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
r_struct
id|diff_spec
op_star
id|one
comma
r_char
op_star
id|path
)paren
(brace
r_int
id|ch
suffix:semicolon
id|one-&gt;file_valid
op_assign
id|one-&gt;sha1_valid
op_assign
l_int|1
suffix:semicolon
id|one-&gt;mode
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
id|one-&gt;mode
op_assign
(paren
id|one-&gt;mode
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
id|one-&gt;u.sha1
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
op_star
id|cp
op_increment
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PLEASE_WARN
mdefine_line|#define PLEASE_WARN -1
DECL|macro|WARNED_OURSELVES
mdefine_line|#define WARNED_OURSELVES -2
DECL|function|parse_diff_tree_output
r_static
r_int
id|parse_diff_tree_output
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_struct
id|diff_spec
op_star
id|old
comma
r_struct
id|diff_spec
op_star
r_new
comma
r_char
op_star
id|path
)paren
(brace
r_const
r_char
op_star
id|cp
op_assign
id|buf
suffix:semicolon
r_int
id|ch
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
r_return
id|WARNED_OURSELVES
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|old-&gt;file_valid
op_assign
l_int|0
suffix:semicolon
r_return
id|parse_oneside_change
c_func
(paren
id|cp
comma
r_new
comma
id|path
)paren
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
r_new
op_member_access_from_pointer
id|file_valid
op_assign
l_int|0
suffix:semicolon
r_return
id|parse_oneside_change
c_func
(paren
id|cp
comma
id|old
comma
id|path
)paren
suffix:semicolon
r_case
l_char|&squot;*&squot;
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|PLEASE_WARN
suffix:semicolon
)brace
multiline_comment|/* This is for &squot;*&squot; entries */
id|old-&gt;file_valid
op_assign
id|old-&gt;sha1_valid
op_assign
l_int|1
suffix:semicolon
r_new
op_member_access_from_pointer
id|file_valid
op_assign
r_new
op_member_access_from_pointer
id|sha1_valid
op_assign
l_int|1
suffix:semicolon
id|old-&gt;mode
op_assign
r_new
op_member_access_from_pointer
id|mode
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
id|old-&gt;mode
op_assign
(paren
id|old-&gt;mode
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
id|PLEASE_WARN
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
r_new
op_member_access_from_pointer
id|mode
op_assign
(paren
r_new
op_member_access_from_pointer
id|mode
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
)paren
r_return
id|PLEASE_WARN
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
id|old-&gt;u.sha1
)paren
)paren
r_return
id|PLEASE_WARN
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
id|PLEASE_WARN
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
r_new
op_member_access_from_pointer
id|u.sha1
)paren
)paren
r_return
id|PLEASE_WARN
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
l_char|&squot;&bslash;t&squot;
)paren
r_return
id|PLEASE_WARN
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|diff_tree_helper_usage
r_static
r_const
r_char
op_star
id|diff_tree_helper_usage
op_assign
l_string|&quot;diff-tree-helper [-R] [-z] paths...&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
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
id|reverse_diff
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
id|reverse_diff
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
id|usage
c_func
(paren
id|diff_tree_helper_usage
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
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|status
suffix:semicolon
r_struct
id|diff_spec
id|old
comma
r_new
suffix:semicolon
r_char
id|path
(braket
id|PATH_MAX
)braket
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
id|parse_diff_tree_output
c_func
(paren
id|sb.buf
comma
op_amp
id|old
comma
op_amp
r_new
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_if
c_cond
(paren
id|status
op_eq
id|PLEASE_WARN
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot parse %s&bslash;n&quot;
comma
id|sb.buf
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|1
OL
id|ac
op_logical_and
op_logical_neg
id|matches_pathspec
c_func
(paren
id|path
comma
id|av
op_plus
l_int|1
comma
id|ac
op_minus
l_int|1
)paren
)paren
r_continue
suffix:semicolon
id|run_external_diff
c_func
(paren
id|path
comma
op_amp
id|old
comma
op_amp
r_new
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
