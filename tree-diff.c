multiline_comment|/*&n; * Helper functions for tree diff generation&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
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
DECL|function|malloc_fullname
r_static
r_char
op_star
id|malloc_fullname
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
id|fullname
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
id|pathlen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fullname
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fullname
op_plus
id|baselen
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|fullname
(braket
id|baselen
op_plus
id|pathlen
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|fullname
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
r_char
op_star
id|fullname
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
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|FIND_COPIES_HARDER
)paren
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
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|RECURSIVE
)paren
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
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|TREE_IN_RECURSIVE
)paren
)paren
(brace
id|newbase
(braket
id|baselen
op_plus
id|pathlen1
)braket
op_assign
l_int|0
suffix:semicolon
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
id|newbase
)paren
suffix:semicolon
id|newbase
(braket
id|baselen
op_plus
id|pathlen1
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
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
id|fullname
op_assign
id|malloc_fullname
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
id|fullname
)paren
suffix:semicolon
id|free
c_func
(paren
id|fullname
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
multiline_comment|/*&n;&t;&t;&t; * If the base is a subdirectory of a path which&n;&t;&t;&t; * was specified, all of them are interesting.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|matchlen
op_logical_or
id|base
(braket
id|matchlen
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
id|match
(braket
id|matchlen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|2
suffix:semicolon
multiline_comment|/* Just a random prefix match */
r_continue
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
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|RECURSIVE
)paren
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
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|TREE_IN_RECURSIVE
)paren
)paren
(brace
id|newbase
(braket
id|baselen
op_plus
id|pathlen
)braket
op_assign
l_int|0
suffix:semicolon
id|opt
op_member_access_from_pointer
id|add_remove
c_func
(paren
id|opt
comma
op_star
id|prefix
comma
id|mode
comma
id|sha1
comma
id|newbase
)paren
suffix:semicolon
id|newbase
(braket
id|baselen
op_plus
id|pathlen
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
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
r_char
op_star
id|fullname
op_assign
id|malloc_fullname
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
id|fullname
)paren
suffix:semicolon
id|free
c_func
(paren
id|fullname
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
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|QUIET
)paren
op_logical_and
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|HAS_CHANGES
)paren
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
l_string|&quot;git diff-tree: internal error&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Does it look like the resulting diff might be due to a rename?&n; *  - single entry&n; *  - not a valid previous file&n; */
DECL|function|diff_might_be_rename
r_static
r_inline
r_int
id|diff_might_be_rename
c_func
(paren
r_void
)paren
(brace
r_return
id|diff_queued_diff.nr
op_eq
l_int|1
op_logical_and
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|diff_queued_diff.queue
(braket
l_int|0
)braket
op_member_access_from_pointer
id|one
)paren
suffix:semicolon
)brace
DECL|function|try_to_follow_renames
r_static
r_void
id|try_to_follow_renames
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
r_struct
id|diff_options
id|diff_opts
suffix:semicolon
r_struct
id|diff_queue_struct
op_star
id|q
op_assign
op_amp
id|diff_queued_diff
suffix:semicolon
r_struct
id|diff_filepair
op_star
id|choice
suffix:semicolon
r_const
r_char
op_star
id|paths
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Remove the file creation entry from the diff queue, and remember it */
id|choice
op_assign
id|q-&gt;queue
(braket
l_int|0
)braket
suffix:semicolon
id|q-&gt;nr
op_assign
l_int|0
suffix:semicolon
id|diff_setup
c_func
(paren
op_amp
id|diff_opts
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|diff_opts
comma
id|RECURSIVE
)paren
suffix:semicolon
id|diff_opts.detect_rename
op_assign
id|DIFF_DETECT_RENAME
suffix:semicolon
id|diff_opts.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
id|diff_opts.single_follow
op_assign
id|opt-&gt;paths
(braket
l_int|0
)braket
suffix:semicolon
id|diff_opts.break_opt
op_assign
id|opt-&gt;break_opt
suffix:semicolon
id|paths
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|diff_tree_setup_paths
c_func
(paren
id|paths
comma
op_amp
id|diff_opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_setup_done
c_func
(paren
op_amp
id|diff_opts
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to set up diff options to follow renames&quot;
)paren
suffix:semicolon
id|diff_tree
c_func
(paren
id|t1
comma
id|t2
comma
id|base
comma
op_amp
id|diff_opts
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|diff_opts
)paren
suffix:semicolon
id|diff_tree_release_paths
c_func
(paren
op_amp
id|diff_opts
)paren
suffix:semicolon
multiline_comment|/* Go through the new set of filepairing, and see if we find a more interesting one */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Found a source? Not only do we use that for the new&n;&t;&t; * diff_queued_diff, we will also use that as the path in&n;&t;&t; * the future!&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|p-&gt;status
op_eq
l_char|&squot;R&squot;
op_logical_or
id|p-&gt;status
op_eq
l_char|&squot;C&squot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;two-&gt;path
comma
id|opt-&gt;paths
(braket
l_int|0
)braket
)paren
)paren
(brace
multiline_comment|/* Switch the file-pairs around */
id|q-&gt;queue
(braket
id|i
)braket
op_assign
id|choice
suffix:semicolon
id|choice
op_assign
id|p
suffix:semicolon
multiline_comment|/* Update the path we use from now on.. */
id|diff_tree_release_paths
c_func
(paren
id|opt
)paren
suffix:semicolon
id|opt-&gt;paths
(braket
l_int|0
)braket
op_assign
id|xstrdup
c_func
(paren
id|p-&gt;one-&gt;path
)paren
suffix:semicolon
id|diff_tree_setup_paths
c_func
(paren
id|opt-&gt;paths
comma
id|opt
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Then, discard all the non-relevant file pairs...&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
id|diff_free_filepair
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * .. and re-instate the one we want (which might be either the&n;&t; * original one, or the rename/copy we found)&n;&t; */
id|q-&gt;queue
(braket
l_int|0
)braket
op_assign
id|choice
suffix:semicolon
id|q-&gt;nr
op_assign
l_int|1
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
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|FOLLOW_RENAMES
)paren
op_logical_and
id|diff_might_be_rename
c_func
(paren
)paren
)paren
(brace
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
id|try_to_follow_renames
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
)brace
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
