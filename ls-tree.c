multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|line_termination
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|recursive
r_int
id|recursive
op_assign
l_int|0
suffix:semicolon
DECL|struct|path_prefix
r_struct
id|path_prefix
(brace
DECL|member|prev
r_struct
id|path_prefix
op_star
id|prev
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|function|print_path_prefix
r_static
r_void
id|print_path_prefix
c_func
(paren
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_if
c_cond
(paren
id|prefix-&gt;prev
)paren
id|print_path_prefix
c_func
(paren
id|prefix-&gt;prev
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|prefix-&gt;name
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|list_recursive
r_static
r_void
id|list_recursive
c_func
(paren
r_void
op_star
id|buffer
comma
r_const
r_int
r_char
op_star
id|type
comma
r_int
r_int
id|size
comma
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_struct
id|path_prefix
id|this_prefix
suffix:semicolon
id|this_prefix.prev
op_assign
id|prefix
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;tree&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;expected a &squot;tree&squot; node&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
op_plus
l_int|1
suffix:semicolon
r_void
op_star
id|eltbuf
suffix:semicolon
r_char
id|elttype
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|eltsize
suffix:semicolon
r_int
r_char
op_star
id|sha1
op_assign
id|buffer
op_plus
id|namelen
suffix:semicolon
r_char
op_star
id|path
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot; &squot;
)paren
op_plus
l_int|1
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|namelen
op_plus
l_int|20
op_logical_or
id|sscanf
c_func
(paren
id|buffer
comma
l_string|&quot;%o&quot;
comma
op_amp
id|mode
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;corrupt &squot;tree&squot; file&quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|sha1
op_plus
l_int|20
suffix:semicolon
id|size
op_sub_assign
id|namelen
op_plus
l_int|20
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%06o&bslash;t%s&bslash;t%s&bslash;t&quot;
comma
id|mode
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
ques
c_cond
l_string|&quot;tree&quot;
suffix:colon
l_string|&quot;blob&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|print_path_prefix
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|path
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|recursive
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|eltbuf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|elttype
comma
op_amp
id|eltsize
)paren
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|this_prefix.name
op_assign
id|path
suffix:semicolon
id|list_recursive
c_func
(paren
id|eltbuf
comma
id|elttype
comma
id|eltsize
comma
op_amp
id|this_prefix
)paren
suffix:semicolon
id|free
c_func
(paren
id|eltbuf
)paren
suffix:semicolon
)brace
)brace
DECL|function|list
r_static
r_int
id|list
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|buffer
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
l_string|&quot;tree&quot;
comma
op_amp
id|size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
id|die
c_func
(paren
l_string|&quot;unable to read sha1 file&quot;
)paren
suffix:semicolon
id|list_recursive
c_func
(paren
id|buffer
comma
l_string|&quot;tree&quot;
comma
id|size
comma
l_int|NULL
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ls_tree_usage
r_static
r_const
r_char
op_star
id|ls_tree_usage
op_assign
l_string|&quot;ls-tree [-r] [-z] &lt;key&gt;&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
op_logical_and
id|argv
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
r_switch
c_cond
(paren
id|argv
(braket
l_int|1
)braket
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;z&squot;
suffix:colon
id|line_termination
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;r&squot;
suffix:colon
id|recursive
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
id|ls_tree_usage
)paren
suffix:semicolon
)brace
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage
c_func
(paren
id|ls_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|sha1
)paren
OL
l_int|0
)paren
id|usage
c_func
(paren
id|ls_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list
c_func
(paren
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;list failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
