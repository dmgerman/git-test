macro_line|#include &quot;cache.h&quot;
DECL|variable|recursive
r_static
r_int
id|recursive
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|diff_tree_sha1
c_func
(paren
r_const
r_int
r_char
op_star
id|old
comma
r_const
r_int
r_char
op_star
r_new
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
DECL|function|update_tree_entry
r_static
r_void
id|update_tree_entry
c_func
(paren
r_void
op_star
op_star
id|bufp
comma
r_int
r_int
op_star
id|sizep
)paren
(brace
r_void
op_star
id|buf
op_assign
op_star
id|bufp
suffix:semicolon
r_int
r_int
id|size
op_assign
op_star
id|sizep
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
op_plus
l_int|1
op_plus
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|len
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file&quot;
)paren
suffix:semicolon
op_star
id|bufp
op_assign
id|buf
op_plus
id|len
suffix:semicolon
op_star
id|sizep
op_assign
id|size
id|len
suffix:semicolon
)brace
DECL|function|extract
r_static
r_const
r_int
r_char
op_star
id|extract
c_func
(paren
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
op_star
id|pathp
comma
r_int
r_int
op_star
id|modep
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|tree
)paren
op_plus
l_int|1
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|tree
op_plus
id|len
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
id|strchr
c_func
(paren
id|tree
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
id|size
OL
id|len
op_plus
l_int|20
op_logical_or
id|sscanf
c_func
(paren
id|tree
comma
l_string|&quot;%o&quot;
comma
id|modep
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file&quot;
)paren
suffix:semicolon
op_star
id|pathp
op_assign
id|path
op_plus
l_int|1
suffix:semicolon
r_return
id|sha1
suffix:semicolon
)brace
DECL|function|malloc_base
r_static
r_char
op_star
id|malloc_base
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_const
r_char
op_star
id|path
comma
r_int
id|pathlen
)paren
(brace
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_char
op_star
id|newbase
op_assign
id|malloc
c_func
(paren
id|baselen
op_plus
id|pathlen
op_plus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
op_plus
id|pathlen
comma
l_string|&quot;/&quot;
comma
l_int|2
)paren
suffix:semicolon
r_return
id|newbase
suffix:semicolon
)brace
r_static
r_void
id|show_file
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
multiline_comment|/* A whole sub-tree went away or appeared */
DECL|function|show_tree
r_static
r_void
id|show_tree
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_while
c_loop
(paren
id|size
)paren
(brace
id|show_file
c_func
(paren
id|prefix
comma
id|tree
comma
id|size
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|tree
comma
op_amp
id|size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* A file entry went away or appeared */
DECL|function|show_file
r_static
r_void
id|show_file
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_int
id|mode
suffix:semicolon
r_const
r_char
op_star
id|path
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|extract
c_func
(paren
id|tree
comma
id|size
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recursive
op_logical_and
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|newbase
op_assign
id|malloc_base
c_func
(paren
id|base
comma
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
r_void
op_star
id|tree
suffix:semicolon
id|tree
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
op_logical_or
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
l_string|&quot;corrupt tree sha %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|show_tree
c_func
(paren
id|prefix
comma
id|tree
comma
id|size
comma
id|newbase
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s%o&bslash;t%s&bslash;t%s&bslash;t%s%s%c&quot;
comma
id|prefix
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
comma
id|base
comma
id|path
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|compare_tree_entry
r_static
r_int
id|compare_tree_entry
c_func
(paren
r_void
op_star
id|tree1
comma
r_int
r_int
id|size1
comma
r_void
op_star
id|tree2
comma
r_int
r_int
id|size2
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_int
id|mode1
comma
id|mode2
suffix:semicolon
r_const
r_char
op_star
id|path1
comma
op_star
id|path2
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
comma
op_star
id|sha2
suffix:semicolon
r_int
id|cmp
comma
id|pathlen1
comma
id|pathlen2
suffix:semicolon
r_char
id|old_sha1_hex
(braket
l_int|50
)braket
suffix:semicolon
id|sha1
op_assign
id|extract
c_func
(paren
id|tree1
comma
id|size1
comma
op_amp
id|path1
comma
op_amp
id|mode1
)paren
suffix:semicolon
id|sha2
op_assign
id|extract
c_func
(paren
id|tree2
comma
id|size2
comma
op_amp
id|path2
comma
op_amp
id|mode2
)paren
suffix:semicolon
id|pathlen1
op_assign
id|strlen
c_func
(paren
id|path1
)paren
suffix:semicolon
id|pathlen2
op_assign
id|strlen
c_func
(paren
id|path2
)paren
suffix:semicolon
id|cmp
op_assign
id|cache_name_compare
c_func
(paren
id|path1
comma
id|pathlen1
comma
id|path2
comma
id|pathlen2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|tree1
comma
id|size1
comma
id|base
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|tree2
comma
id|size2
comma
id|base
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|sha1
comma
id|sha2
comma
l_int|20
)paren
op_logical_and
id|mode1
op_eq
id|mode2
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If the filemode has changed to/from a directory from/to a regular&n;&t; * file, we need to consider it a remove and an add.&n;&t; */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
op_ne
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|tree1
comma
id|size1
comma
id|base
)paren
suffix:semicolon
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|tree2
comma
id|size2
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|recursive
op_logical_and
id|S_ISDIR
c_func
(paren
id|mode1
)paren
)paren
(brace
r_int
id|retval
suffix:semicolon
r_char
op_star
id|newbase
op_assign
id|malloc_base
c_func
(paren
id|base
comma
id|path1
comma
id|pathlen1
)paren
suffix:semicolon
id|retval
op_assign
id|diff_tree_sha1
c_func
(paren
id|sha1
comma
id|sha2
comma
id|newbase
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;*%o-&gt;%o&bslash;t%s&bslash;t%s-&gt;%s&bslash;t%s%s%c&quot;
comma
id|mode1
comma
id|mode2
comma
id|S_ISDIR
c_func
(paren
id|mode1
)paren
ques
c_cond
l_string|&quot;tree&quot;
suffix:colon
l_string|&quot;blob&quot;
comma
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|sha2
)paren
comma
id|base
comma
id|path1
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_tree
r_static
r_int
id|diff_tree
c_func
(paren
r_void
op_star
id|tree1
comma
r_int
r_int
id|size1
comma
r_void
op_star
id|tree2
comma
r_int
r_int
id|size2
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_while
c_loop
(paren
id|size1
op_or
id|size2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|size1
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|tree2
comma
id|size2
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|tree2
comma
op_amp
id|size2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size2
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|tree1
comma
id|size1
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|tree1
comma
op_amp
id|size1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|compare_tree_entry
c_func
(paren
id|tree1
comma
id|size1
comma
id|tree2
comma
id|size2
comma
id|base
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|tree1
comma
op_amp
id|size1
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_int|0
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|tree1
comma
op_amp
id|size1
)paren
suffix:semicolon
multiline_comment|/* Fallthrough */
r_case
l_int|1
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|tree2
comma
op_amp
id|size2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;diff-tree: internal error&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_tree_sha1
r_static
r_int
id|diff_tree_sha1
c_func
(paren
r_const
r_int
r_char
op_star
id|old
comma
r_const
r_int
r_char
op_star
r_new
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_void
op_star
id|tree1
comma
op_star
id|tree2
suffix:semicolon
r_int
r_int
id|size1
comma
id|size2
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|tree1
op_assign
id|read_sha1_file
c_func
(paren
id|old
comma
id|type
comma
op_amp
id|size1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree1
op_logical_or
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
l_string|&quot;unable to read source tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|old
)paren
)paren
suffix:semicolon
id|tree2
op_assign
id|read_sha1_file
c_func
(paren
r_new
comma
id|type
comma
op_amp
id|size2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree2
op_logical_or
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
l_string|&quot;unable to read destination tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
r_new
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|diff_tree
c_func
(paren
id|tree1
comma
id|size1
comma
id|tree2
comma
id|size2
comma
id|base
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree1
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree2
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
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
id|old
(braket
l_int|20
)braket
comma
r_new
(braket
l_int|20
)braket
suffix:semicolon
r_while
c_loop
(paren
id|argc
OG
l_int|3
)paren
(brace
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-r&quot;
)paren
)paren
(brace
id|recursive
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
l_string|&quot;diff-tree [-r] &lt;tree sha1&gt; &lt;tree sha1&gt;&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
op_logical_or
id|get_sha1_hex
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|old
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
r_new
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;diff-tree &lt;tree sha1&gt; &lt;tree sha1&gt;&quot;
)paren
suffix:semicolon
r_return
id|diff_tree_sha1
c_func
(paren
id|old
comma
r_new
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
eof
