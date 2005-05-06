macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|silent
r_static
r_int
id|silent
op_assign
l_int|0
suffix:semicolon
DECL|variable|ignore_merges
r_static
r_int
id|ignore_merges
op_assign
l_int|1
suffix:semicolon
DECL|variable|recursive
r_static
r_int
id|recursive
op_assign
l_int|0
suffix:semicolon
DECL|variable|read_stdin
r_static
r_int
id|read_stdin
op_assign
l_int|0
suffix:semicolon
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|generate_patch
r_static
r_int
id|generate_patch
op_assign
l_int|0
suffix:semicolon
DECL|variable|header
r_static
r_const
r_char
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// What paths are we interested in?
DECL|variable|nr_paths
r_static
r_int
id|nr_paths
op_assign
l_int|0
suffix:semicolon
DECL|variable|paths
r_static
r_char
op_star
op_star
id|paths
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pathlens
r_static
r_int
op_star
id|pathlens
op_assign
l_int|NULL
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
id|xmalloc
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
id|header
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|header
)paren
suffix:semicolon
id|header
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|silent
)paren
r_return
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
r_if
c_cond
(paren
id|generate_patch
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|diff_addremove
c_func
(paren
id|prefix
(braket
l_int|0
)braket
comma
id|mode
comma
id|sha1
comma
id|base
comma
id|path
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%s%06o&bslash;t%s&bslash;t%s&bslash;t%s%s%c&quot;
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
id|line_termination
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
r_if
c_cond
(paren
id|header
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|header
)paren
suffix:semicolon
id|header
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|silent
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|generate_patch
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode1
)paren
)paren
id|diff_change
c_func
(paren
id|mode1
comma
id|mode2
comma
id|sha1
comma
id|sha2
comma
id|base
comma
id|path1
)paren
suffix:semicolon
)brace
r_else
(brace
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
l_string|&quot;*%06o-&gt;%06o&bslash;t%s&bslash;t%s-&gt;%s&bslash;t%s%s%c&quot;
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
id|line_termination
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|interesting
r_static
r_int
id|interesting
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
id|base
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|baselen
comma
id|pathlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_paths
)paren
r_return
l_int|1
suffix:semicolon
(paren
r_void
)paren
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
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
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
id|nr_paths
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|match
op_assign
id|paths
(braket
id|i
)braket
suffix:semicolon
r_int
id|matchlen
op_assign
id|pathlens
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|baselen
op_ge
id|matchlen
)paren
(brace
multiline_comment|/* If it doesn&squot;t match, move along... */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|base
comma
id|match
comma
id|matchlen
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* The base is a subdirectory of a path which was specified. */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Does the base match? */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|base
comma
id|match
comma
id|baselen
)paren
)paren
r_continue
suffix:semicolon
id|match
op_add_assign
id|baselen
suffix:semicolon
id|matchlen
op_sub_assign
id|baselen
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OG
id|matchlen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|path
comma
id|match
comma
id|pathlen
)paren
)paren
r_continue
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No matches */
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
id|nr_paths
op_logical_and
id|size1
op_logical_and
op_logical_neg
id|interesting
c_func
(paren
id|tree1
comma
id|size1
comma
id|base
)paren
)paren
(brace
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
r_if
c_cond
(paren
id|nr_paths
op_logical_and
id|size2
op_logical_and
op_logical_neg
id|interesting
c_func
(paren
id|tree2
comma
id|size2
comma
id|base
)paren
)paren
(brace
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
r_int
id|retval
suffix:semicolon
id|tree1
op_assign
id|read_object_with_reference
c_func
(paren
id|old
comma
l_string|&quot;tree&quot;
comma
op_amp
id|size1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree1
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
id|read_object_with_reference
c_func
(paren
r_new
comma
l_string|&quot;tree&quot;
comma
op_amp
id|size2
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree2
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
DECL|function|diff_tree_stdin
r_static
r_int
id|diff_tree_stdin
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_int
r_char
id|commit
(braket
l_int|20
)braket
comma
id|parent
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
comma
id|offset
suffix:semicolon
r_static
r_char
id|this_header
(braket
l_int|100
)braket
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|line
comma
id|commit
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|line
(braket
l_int|40
)braket
)paren
op_logical_and
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|41
comma
id|parent
)paren
)paren
(brace
id|line
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
id|line
(braket
l_int|81
)braket
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|this_header
comma
l_string|&quot;%s (from %s)&bslash;n&quot;
comma
id|line
comma
id|line
op_plus
l_int|41
)paren
suffix:semicolon
id|header
op_assign
id|this_header
suffix:semicolon
r_return
id|diff_tree_sha1
c_func
(paren
id|parent
comma
id|commit
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
id|buf
op_assign
id|read_object_with_reference
c_func
(paren
id|commit
comma
l_string|&quot;commit&quot;
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
id|buf
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* More than one parent? */
r_if
c_cond
(paren
id|ignore_merges
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buf
op_plus
l_int|46
op_plus
l_int|48
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|line
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
id|offset
op_assign
l_int|46
suffix:semicolon
r_while
c_loop
(paren
id|offset
op_plus
l_int|48
OL
id|size
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buf
op_plus
id|offset
op_plus
l_int|7
comma
id|parent
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|this_header
comma
l_string|&quot;%s (from %s)&bslash;n&quot;
comma
id|line
comma
id|sha1_to_hex
c_func
(paren
id|parent
)paren
)paren
suffix:semicolon
id|header
op_assign
id|this_header
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|parent
comma
id|commit
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|48
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|diff_tree_usage
r_static
r_char
op_star
id|diff_tree_usage
op_assign
l_string|&quot;diff-tree [-p] [-r] [-z] &lt;tree sha1&gt; &lt;tree sha1&gt;&quot;
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
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
op_star
id|arg
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|arg
op_assign
op_star
id|argv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
op_logical_or
op_star
id|arg
op_ne
l_char|&squot;-&squot;
)paren
r_break
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
l_string|&quot;-&quot;
)paren
)paren
(brace
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-p&quot;
)paren
)paren
(brace
id|recursive
op_assign
id|generate_patch
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_termination
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-m&quot;
)paren
)paren
(brace
id|ignore_merges
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-s&quot;
)paren
)paren
(brace
id|silent
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
id|read_stdin
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|read_stdin
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|2
op_logical_or
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|old
)paren
op_logical_or
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
r_new
)paren
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
id|argv
op_add_assign
l_int|2
suffix:semicolon
id|argc
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
(brace
r_int
id|i
suffix:semicolon
id|paths
op_assign
id|argv
suffix:semicolon
id|nr_paths
op_assign
id|argc
suffix:semicolon
id|pathlens
op_assign
id|xmalloc
c_func
(paren
id|nr_paths
op_star
r_sizeof
(paren
r_int
)paren
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
id|nr_paths
suffix:semicolon
id|i
op_increment
)paren
id|pathlens
(braket
id|i
)braket
op_assign
id|strlen
c_func
(paren
id|paths
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|read_stdin
)paren
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
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
)paren
id|diff_tree_stdin
c_func
(paren
id|line
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
