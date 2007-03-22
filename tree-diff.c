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
r_int
id|baselen
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
comma
r_int
id|baselen
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
r_int
id|baselen
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
id|tree_entry_len
c_func
(paren
id|path1
comma
id|sha1
)paren
suffix:semicolon
id|pathlen2
op_assign
id|tree_entry_len
c_func
(paren
id|path2
comma
id|sha2
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
comma
id|baselen
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
comma
id|baselen
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
comma
id|baselen
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
comma
id|baselen
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
id|baselen
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
multiline_comment|/*&n; * Is a tree entry interesting given the pathspec we have?&n; *&n; * Return:&n; *  - 2 for &quot;yes, and all subsequent entries will be&quot;&n; *  - 1 for yes&n; *  - zero for no&n; *  - negative for &quot;no, and no subsequent entries will be either&quot;&n; */
DECL|function|tree_entry_interesting
r_static
r_int
id|tree_entry_interesting
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
r_int
id|baselen
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
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_int
id|never_interesting
op_assign
l_int|1
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
id|pathlen
op_assign
id|tree_entry_len
c_func
(paren
id|path
comma
id|sha1
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
r_int
id|m
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* signals that we haven&squot;t called strncmp() */
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
multiline_comment|/*&n;&t;&t;&t; * The base is a subdirectory of a path which&n;&t;&t;&t; * was specified, so all of them are interesting.&n;&t;&t;&t; */
r_return
l_int|2
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
id|never_interesting
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We have not seen any match that sorts later&n;&t;&t;&t; * than the current path.&n;&t;&t;&t; */
multiline_comment|/*&n;&t;&t;&t; * Does match sort strictly earlier than path&n;&t;&t;&t; * with their common parts?&n;&t;&t;&t; */
id|m
op_assign
id|strncmp
c_func
(paren
id|match
comma
id|path
comma
(paren
id|matchlen
OL
id|pathlen
)paren
ques
c_cond
id|matchlen
suffix:colon
id|pathlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If we come here even once, that means there is at&n;&t;&t;&t; * least one pathspec that would sort equal to or&n;&t;&t;&t; * later than the path we are currently looking at.&n;&t;&t;&t; * In other words, if we have never reached this point&n;&t;&t;&t; * after iterating all pathspecs, it means all&n;&t;&t;&t; * pathspecs are either outside of base, or inside the&n;&t;&t;&t; * base but sorts strictly earlier than the current&n;&t;&t;&t; * one.  In either case, they will never match the&n;&t;&t;&t; * subsequent entries.  In such a case, we initialized&n;&t;&t;&t; * the variable to -1 and that is what will be&n;&t;&t;&t; * returned, allowing the caller to terminate early.&n;&t;&t;&t; */
id|never_interesting
op_assign
l_int|0
suffix:semicolon
)brace
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
id|m
op_eq
l_int|1
)paren
multiline_comment|/*&n;&t;&t;&t; * we cheated and did not do strncmp(), so we do&n;&t;&t;&t; * that here.&n;&t;&t;&t; */
id|m
op_assign
id|strncmp
c_func
(paren
id|match
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If common part matched earlier then it is a hit,&n;&t;&t; * because we rejected the case where path is not a&n;&t;&t; * leading directory and is shorter than match.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|never_interesting
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
comma
r_int
id|baselen
)paren
(brace
r_int
id|all_interesting
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|desc-&gt;size
)paren
(brace
r_int
id|show
suffix:semicolon
r_if
c_cond
(paren
id|all_interesting
)paren
id|show
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|show
op_assign
id|tree_entry_interesting
c_func
(paren
id|desc
comma
id|base
comma
id|baselen
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show
op_eq
l_int|2
)paren
id|all_interesting
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|show
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
comma
id|baselen
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
comma
r_int
id|baselen
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
r_enum
id|object_type
id|type
suffix:semicolon
r_int
id|pathlen
op_assign
id|tree_entry_len
c_func
(paren
id|path
comma
id|sha1
)paren
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
id|baselen
comma
id|path
comma
id|pathlen
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
r_int
r_int
id|size
suffix:semicolon
id|tree
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
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
id|type
op_ne
id|OBJ_TREE
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
id|init_tree_desc
c_func
(paren
op_amp
id|inner
comma
id|tree
comma
id|size
)paren
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
comma
id|baselen
op_plus
l_int|1
op_plus
id|pathlen
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
DECL|function|skip_uninteresting
r_static
r_void
id|skip_uninteresting
c_func
(paren
r_struct
id|tree_desc
op_star
id|t
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_int
id|all_interesting
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|t-&gt;size
)paren
(brace
r_int
id|show
suffix:semicolon
r_if
c_cond
(paren
id|all_interesting
)paren
id|show
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|show
op_assign
id|tree_entry_interesting
c_func
(paren
id|t
comma
id|base
comma
id|baselen
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show
op_eq
l_int|2
)paren
id|all_interesting
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|show
)paren
(brace
id|update_tree_entry
c_func
(paren
id|t
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Skip it all? */
r_if
c_cond
(paren
id|show
OL
l_int|0
)paren
id|t-&gt;size
op_assign
l_int|0
suffix:semicolon
r_return
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
r_int
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
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;quiet
op_logical_and
id|opt-&gt;has_changes
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;nr_paths
)paren
(brace
id|skip_uninteresting
c_func
(paren
id|t1
comma
id|base
comma
id|baselen
comma
id|opt
)paren
suffix:semicolon
id|skip_uninteresting
c_func
(paren
id|t2
comma
id|base
comma
id|baselen
comma
id|opt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|t1-&gt;size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|t2-&gt;size
)paren
r_break
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
comma
id|baselen
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
comma
id|baselen
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
id|baselen
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
id|tree_type
comma
op_amp
id|size1
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
id|size2
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
id|init_tree_desc
c_func
(paren
op_amp
id|t1
comma
id|tree1
comma
id|size1
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t2
comma
id|tree2
comma
id|size2
)paren
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
DECL|function|diff_root_tree_sha1
r_int
id|diff_root_tree_sha1
c_func
(paren
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
r_int
id|retval
suffix:semicolon
r_void
op_star
id|tree
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|tree_desc
id|empty
comma
id|real
suffix:semicolon
id|tree
op_assign
id|read_object_with_reference
c_func
(paren
r_new
comma
id|tree_type
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
id|tree
)paren
id|die
c_func
(paren
l_string|&quot;unable to read root tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
r_new
)paren
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|real
comma
id|tree
comma
id|size
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|empty
comma
l_string|&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|diff_tree
c_func
(paren
op_amp
id|empty
comma
op_amp
id|real
comma
id|base
comma
id|opt
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
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
