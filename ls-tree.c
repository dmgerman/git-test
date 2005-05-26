multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|recursive
r_static
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
DECL|macro|DEBUG
mdefine_line|#define DEBUG(fmt, ...)&t;
DECL|function|string_path_prefix
r_static
r_int
id|string_path_prefix
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|blen
comma
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
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
(brace
id|len
op_assign
id|string_path_prefix
c_func
(paren
id|buff
comma
id|blen
comma
id|prefix-&gt;prev
)paren
suffix:semicolon
id|buff
op_add_assign
id|len
suffix:semicolon
id|blen
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|blen
OG
l_int|0
)paren
(brace
op_star
id|buff
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|len
op_increment
suffix:semicolon
id|buff
op_increment
suffix:semicolon
id|blen
op_decrement
suffix:semicolon
)brace
)brace
id|strncpy
c_func
(paren
id|buff
comma
id|prefix-&gt;name
comma
id|blen
)paren
suffix:semicolon
r_return
id|len
op_plus
id|strlen
c_func
(paren
id|prefix-&gt;name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
(brace
id|print_path_prefix
c_func
(paren
id|prefix-&gt;prev
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
id|fputs
c_func
(paren
id|prefix-&gt;name
comma
id|stdout
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * return:&n; * &t;-1 if prefix is *not* a subset of path&n; * &t; 0 if prefix == path&n; * &t; 1 if prefix is a subset of path&n; */
DECL|function|pathcmp
r_static
r_int
id|pathcmp
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_char
id|buff
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|len
comma
id|slen
suffix:semicolon
r_if
c_cond
(paren
id|prefix
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|string_path_prefix
c_func
(paren
id|buff
comma
r_sizeof
id|buff
comma
id|prefix
)paren
suffix:semicolon
id|slen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slen
OL
id|len
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|path
comma
id|buff
comma
id|len
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|slen
op_eq
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * match may be NULL, or a *sorted* list of paths&n; */
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
comma
r_char
op_star
op_star
id|match
comma
r_int
id|matches
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
r_if
c_cond
(paren
id|matches
)paren
id|recursive
op_assign
l_int|1
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
op_assign
l_int|NULL
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
r_const
r_char
op_star
id|matched
op_assign
l_int|NULL
suffix:semicolon
r_int
id|mtype
op_assign
l_int|1
suffix:semicolon
r_int
id|mindex
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
id|this_prefix.name
op_assign
id|path
suffix:semicolon
r_for
c_loop
(paren
id|mindex
op_assign
l_int|0
suffix:semicolon
id|mindex
OL
id|matches
suffix:semicolon
id|mindex
op_increment
)paren
(brace
id|mtype
op_assign
id|pathcmp
c_func
(paren
id|match
(braket
id|mindex
)braket
comma
op_amp
id|this_prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtype
op_ge
l_int|0
)paren
(brace
id|matched
op_assign
id|match
(braket
id|mindex
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * If we&squot;re not matching, or if this is an exact match,&n;&t;&t; * print out the info&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|matches
op_logical_or
(paren
id|matched
op_ne
l_int|NULL
op_logical_and
id|mtype
op_eq
l_int|0
)paren
)paren
(brace
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
op_amp
id|this_prefix
)paren
suffix:semicolon
id|putchar
c_func
(paren
id|line_termination
)paren
suffix:semicolon
)brace
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
id|matches
op_logical_and
op_logical_neg
id|matched
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
multiline_comment|/* If this is an exact directory match, we may have&n;&t;&t; * directory files following this path. Match on them.&n;&t;&t; * Otherwise, we&squot;re at a pach subcomponent, and we need&n;&t;&t; * to try to match again.&n;&t;&t; */
r_if
c_cond
(paren
id|mtype
op_eq
l_int|0
)paren
id|mindex
op_increment
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
comma
op_amp
id|match
(braket
id|mindex
)braket
comma
id|matches
op_minus
id|mindex
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
DECL|function|qcmp
r_static
r_int
id|qcmp
c_func
(paren
r_const
r_void
op_star
id|a
comma
r_const
r_void
op_star
id|b
)paren
(brace
r_return
id|strcmp
c_func
(paren
op_star
(paren
r_char
op_star
op_star
)paren
id|a
comma
op_star
(paren
r_char
op_star
op_star
)paren
id|b
)paren
suffix:semicolon
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
comma
r_char
op_star
op_star
id|path
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
r_int
id|npaths
suffix:semicolon
r_for
c_loop
(paren
id|npaths
op_assign
l_int|0
suffix:semicolon
id|path
(braket
id|npaths
)braket
op_ne
l_int|NULL
suffix:semicolon
id|npaths
op_increment
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|path
comma
id|npaths
comma
r_sizeof
(paren
r_char
op_star
)paren
comma
id|qcmp
)paren
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
l_int|NULL
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
comma
id|path
comma
id|npaths
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
l_string|&quot;git-ls-tree [-r] [-z] &lt;key&gt; [paths...]&quot;
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
OL
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
comma
op_amp
id|argv
(braket
l_int|2
)braket
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
