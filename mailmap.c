macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;mailmap.h&quot;
DECL|function|read_mailmap
r_int
id|read_mailmap
c_func
(paren
r_struct
id|path_list
op_star
id|map
comma
r_const
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|repo_abbrev
)paren
(brace
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|f
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|end_of_name
comma
op_star
id|left_bracket
comma
op_star
id|right_bracket
suffix:semicolon
r_char
op_star
id|name
comma
op_star
id|email
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;#&squot;
)paren
(brace
r_static
r_const
r_char
id|abbrev
(braket
)braket
op_assign
l_string|&quot;# repo-abbrev:&quot;
suffix:semicolon
r_int
id|abblen
op_assign
r_sizeof
(paren
id|abbrev
)paren
l_int|1
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|repo_abbrev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|buffer
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buffer
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
id|abbrev
comma
id|abblen
)paren
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|repo_abbrev
)paren
id|free
c_func
(paren
op_star
id|repo_abbrev
)paren
suffix:semicolon
op_star
id|repo_abbrev
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|buffer
op_plus
id|abblen
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|cp
)paren
suffix:semicolon
id|cp
op_increment
)paren
suffix:semicolon
multiline_comment|/* nothing */
id|strcpy
c_func
(paren
op_star
id|repo_abbrev
comma
id|cp
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|left_bracket
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot;&lt;&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|right_bracket
op_assign
id|strchr
c_func
(paren
id|left_bracket
op_plus
l_int|1
comma
l_char|&squot;&gt;&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|right_bracket
op_eq
id|left_bracket
op_plus
l_int|1
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|end_of_name
op_assign
id|left_bracket
suffix:semicolon
id|end_of_name
op_ne
id|buffer
op_logical_and
id|isspace
c_func
(paren
id|end_of_name
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|end_of_name
op_decrement
)paren
multiline_comment|/* keep on looking */
r_if
c_cond
(paren
id|end_of_name
op_eq
id|buffer
)paren
r_continue
suffix:semicolon
id|name
op_assign
id|xmalloc
c_func
(paren
id|end_of_name
id|buffer
op_plus
l_int|1
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|name
comma
id|buffer
comma
id|end_of_name
id|buffer
op_plus
l_int|1
)paren
suffix:semicolon
id|email
op_assign
id|xmalloc
c_func
(paren
id|right_bracket
id|left_bracket
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
id|right_bracket
id|left_bracket
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|email
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|left_bracket
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|email
(braket
id|right_bracket
id|left_bracket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|path_list_insert
c_func
(paren
id|email
comma
id|map
)paren
op_member_access_from_pointer
id|util
op_assign
id|name
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_email
r_int
id|map_email
c_func
(paren
r_struct
id|path_list
op_star
id|map
comma
r_const
r_char
op_star
id|email
comma
r_char
op_star
id|name
comma
r_int
id|maxlen
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
comma
op_star
id|mailbuf
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* autocomplete common developers */
id|p
op_assign
id|strchr
c_func
(paren
id|email
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p
id|email
op_plus
l_int|1
OL
r_sizeof
(paren
id|buf
)paren
)paren
id|mailbuf
op_assign
id|buf
suffix:semicolon
r_else
id|mailbuf
op_assign
id|xmalloc
c_func
(paren
id|p
id|email
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* downcase the email address */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|p
id|email
suffix:semicolon
id|i
op_increment
)paren
id|mailbuf
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|email
(braket
id|i
)braket
)paren
suffix:semicolon
id|mailbuf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|item
op_assign
id|path_list_lookup
c_func
(paren
id|mailbuf
comma
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mailbuf
op_ne
id|buf
)paren
id|free
c_func
(paren
id|mailbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item
op_ne
l_int|NULL
)paren
(brace
r_const
r_char
op_star
id|realname
op_assign
(paren
r_const
r_char
op_star
)paren
id|item-&gt;util
suffix:semicolon
id|strlcpy
c_func
(paren
id|name
comma
id|realname
comma
id|maxlen
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
