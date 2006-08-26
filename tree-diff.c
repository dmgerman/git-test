multiline_comment|/*&n; * Helper functions for tree diff generation&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;tree.h&quot;
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
id|show_entry
c_func
(paren
r_struct
id|diff_options
op_star
id|opt
comma
r_const
r_char
op_star
id|prefix
comma
r_struct
id|tree_desc
op_star
id|desc
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
DECL|function|compare_tree_entry
r_static
r_int
id|compare_tree_entry
c_func
(paren
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
comma
r_const
r_char
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
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
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
id|t1
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
id|tree_entry_extract
c_func
(paren
id|t2
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
id|base_name_compare
c_func
(paren
id|path1
comma
id|pathlen1
comma
id|mode1
comma
id|path2
comma
id|pathlen2
comma
id|mode2
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
id|show_entry
c_func
(paren
id|opt
comma
l_string|&quot;-&quot;
comma
id|t1
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
id|show_entry
c_func
(paren
id|opt
comma
l_string|&quot;+&quot;
comma
id|t2
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
id|opt-&gt;find_copies_harder
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|sha2
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
id|show_entry
c_func
(paren
id|opt
comma
l_string|&quot;-&quot;
comma
id|t1
comma
id|base
)paren
suffix:semicolon
id|show_entry
c_func
(paren
id|opt
comma
l_string|&quot;+&quot;
comma
id|t2
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
id|opt-&gt;recursive
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
r_if
c_cond
(paren
id|opt-&gt;tree_in_recursive
)paren
id|opt
op_member_access_from_pointer
id|change
c_func
(paren
id|opt
comma
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
comma
id|opt
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
id|opt
op_member_access_from_pointer
id|change
c_func
(paren
id|opt
comma
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
r_struct
id|tree_desc
op_star
id|desc
comma
r_const
r_char
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
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
id|opt-&gt;nr_paths
)paren
r_return
l_int|1
suffix:semicolon
(paren
r_void
)paren
id|tree_entry_extract
c_func
(paren
id|desc
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
id|opt-&gt;nr_paths
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
id|opt-&gt;paths
(braket
id|i
)braket
suffix:semicolon
r_int
id|matchlen
op_assign
id|opt-&gt;pathlens
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
id|matchlen
OG
id|pathlen
)paren
(brace
r_if
c_cond
(paren
id|match
(braket
id|pathlen
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
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
r_continue
suffix:semicolon
)brace
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
multiline_comment|/* A whole sub-tree went away or appeared */
DECL|function|show_tree
r_static
r_void
id|show_tree
c_func
(paren
r_struct
id|diff_options
op_star
id|opt
comma
r_const
r_char
op_star
id|prefix
comma
r_struct
id|tree_desc
op_star
id|desc
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
id|desc-&gt;size
)paren
(brace
r_if
c_cond
(paren
id|interesting
c_func
(paren
id|desc
comma
id|base
comma
id|opt
)paren
)paren
id|show_entry
c_func
(paren
id|opt
comma
id|prefix
comma
id|desc
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|desc
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* A file entry went away or appeared */
DECL|function|show_entry
r_static
r_void
id|show_entry
c_func
(paren
r_struct
id|diff_options
op_star
id|opt
comma
r_const
r_char
op_star
id|prefix
comma
r_struct
id|tree_desc
op_star
id|desc
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
id|tree_entry_extract
c_func
(paren
id|desc
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
id|opt-&gt;recursive
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
r_struct
id|tree_desc
id|inner
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
id|inner.size
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
id|tree_type
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
id|inner.buf
op_assign
id|tree
suffix:semicolon
id|show_tree
c_func
(paren
id|opt
comma
id|prefix
comma
op_amp
id|inner
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
)brace
r_else
(brace
id|opt
op_member_access_from_pointer
id|add_remove
c_func
(paren
id|opt
comma
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
)brace
DECL|function|diff_tree
r_int
id|diff_tree
c_func
(paren
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
comma
r_const
r_char
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_while
c_loop
(paren
id|t1-&gt;size
op_or
id|t2-&gt;size
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;nr_paths
op_logical_and
id|t1-&gt;size
op_logical_and
op_logical_neg
id|interesting
c_func
(paren
id|t1
comma
id|base
comma
id|opt
)paren
)paren
(brace
id|update_tree_entry
c_func
(paren
id|t1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;nr_paths
op_logical_and
id|t2-&gt;size
op_logical_and
op_logical_neg
id|interesting
c_func
(paren
id|t2
comma
id|base
comma
id|opt
)paren
)paren
(brace
id|update_tree_entry
c_func
(paren
id|t2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|t1-&gt;size
)paren
(brace
id|show_entry
c_func
(paren
id|opt
comma
l_string|&quot;+&quot;
comma
id|t2
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|t2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|t2-&gt;size
)paren
(brace
id|show_entry
c_func
(paren
id|opt
comma
l_string|&quot;-&quot;
comma
id|t1
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|t1
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
id|t1
comma
id|t2
comma
id|base
comma
id|opt
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|update_tree_entry
c_func
(paren
id|t1
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
id|t1
)paren
suffix:semicolon
multiline_comment|/* Fallthrough */
r_case
l_int|1
suffix:colon
id|update_tree_entry
c_func
(paren
id|t2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;git-diff-tree: internal error&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_tree_sha1
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
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_void
op_star
id|tree1
comma
op_star
id|tree2
suffix:semicolon
r_struct
id|tree_desc
id|t1
comma
id|t2
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
id|tree_type
comma
op_amp
id|t1.size
comma
l_int|NULL
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
id|tree_type
comma
op_amp
id|t2.size
comma
l_int|NULL
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
id|t1.buf
op_assign
id|tree1
suffix:semicolon
id|t2.buf
op_assign
id|tree2
suffix:semicolon
id|retval
op_assign
id|diff_tree
c_func
(paren
op_amp
id|t1
comma
op_amp
id|t2
comma
id|base
comma
id|opt
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
DECL|function|count_paths
r_static
r_int
id|count_paths
c_func
(paren
r_const
r_char
op_star
op_star
id|paths
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|paths
op_increment
)paren
id|i
op_increment
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|diff_tree_release_paths
r_void
id|diff_tree_release_paths
c_func
(paren
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
id|free
c_func
(paren
id|opt-&gt;pathlens
)paren
suffix:semicolon
)brace
DECL|function|diff_tree_setup_paths
r_void
id|diff_tree_setup_paths
c_func
(paren
r_const
r_char
op_star
op_star
id|p
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
id|opt-&gt;nr_paths
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;pathlens
op_assign
l_int|NULL
suffix:semicolon
id|opt-&gt;paths
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
id|opt-&gt;paths
op_assign
id|p
suffix:semicolon
id|opt-&gt;nr_paths
op_assign
id|count_paths
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;nr_paths
op_eq
l_int|0
)paren
(brace
id|opt-&gt;pathlens
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|opt-&gt;pathlens
op_assign
id|xmalloc
c_func
(paren
id|opt-&gt;nr_paths
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
id|opt-&gt;nr_paths
suffix:semicolon
id|i
op_increment
)paren
id|opt-&gt;pathlens
(braket
id|i
)braket
op_assign
id|strlen
c_func
(paren
id|p
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
eof
