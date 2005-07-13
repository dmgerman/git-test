macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|variable|show_root_diff
r_static
r_int
id|show_root_diff
op_assign
l_int|0
suffix:semicolon
DECL|variable|verbose_header
r_static
r_int
id|verbose_header
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
DECL|variable|show_tree_entry_in_recursive
r_static
r_int
id|show_tree_entry_in_recursive
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
DECL|variable|diff_output_format
r_static
r_int
id|diff_output_format
op_assign
id|DIFF_FORMAT_HUMAN
suffix:semicolon
DECL|variable|detect_rename
r_static
r_int
id|detect_rename
op_assign
l_int|0
suffix:semicolon
DECL|variable|find_copies_harder
r_static
r_int
id|find_copies_harder
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_setup_opt
r_static
r_int
id|diff_setup_opt
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_score_opt
r_static
r_int
id|diff_score_opt
op_assign
l_int|0
suffix:semicolon
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
DECL|variable|diff_break_opt
r_static
r_int
id|diff_break_opt
op_assign
l_int|1
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
DECL|variable|header
r_static
r_const
r_char
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|header_prefix
r_static
r_const
r_char
op_star
id|header_prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|commit_format
r_static
r_enum
id|cmit_fmt
id|commit_format
op_assign
id|CMIT_FMT_RAW
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
r_const
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
r_int
r_int
id|mode
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
op_amp
id|mode
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
op_star
id|modep
op_assign
id|DIFF_FILE_CANON_MODE
c_func
(paren
id|mode
)paren
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
suffix:semicolon
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
id|find_copies_harder
op_logical_and
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
r_if
c_cond
(paren
id|show_tree_entry_in_recursive
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
r_if
c_cond
(paren
id|interesting
c_func
(paren
id|tree
comma
id|size
comma
id|base
)paren
)paren
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
l_string|&quot;git-diff-tree: internal error&quot;
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
l_string|&quot;tree&quot;
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
DECL|function|call_diff_setup
r_static
r_void
id|call_diff_setup
c_func
(paren
r_void
)paren
(brace
id|diff_setup
c_func
(paren
id|diff_setup_opt
)paren
suffix:semicolon
)brace
DECL|function|call_diff_flush
r_static
r_int
id|call_diff_flush
c_func
(paren
r_void
)paren
(brace
id|diffcore_std
c_func
(paren
l_int|NULL
comma
id|detect_rename
comma
id|diff_score_opt
comma
id|pickaxe
comma
id|pickaxe_opts
comma
id|diff_break_opt
comma
id|orderfile
comma
id|diff_filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_queue_is_empty
c_func
(paren
)paren
)paren
(brace
id|diff_flush
c_func
(paren
id|DIFF_FORMAT_NO_OUTPUT
)paren
suffix:semicolon
r_return
l_int|0
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
l_string|&quot;%s%c&quot;
comma
id|header
comma
id|diff_output_format
op_eq
id|DIFF_FORMAT_MACHINE
ques
c_cond
l_int|0
suffix:colon
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|header
op_assign
l_int|NULL
suffix:semicolon
)brace
id|diff_flush
c_func
(paren
id|diff_output_format
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|diff_tree_sha1_top
r_static
r_int
id|diff_tree_sha1_top
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
r_int
id|ret
suffix:semicolon
id|call_diff_setup
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|diff_tree_sha1
c_func
(paren
id|old
comma
r_new
comma
id|base
)paren
suffix:semicolon
id|call_diff_flush
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|diff_root_tree
r_static
r_int
id|diff_root_tree
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
id|call_diff_setup
c_func
(paren
)paren
suffix:semicolon
id|tree
op_assign
id|read_object_with_reference
c_func
(paren
r_new
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
id|retval
op_assign
id|diff_tree
c_func
(paren
l_string|&quot;&quot;
comma
l_int|0
comma
id|tree
comma
id|size
comma
id|base
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
id|call_diff_flush
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|generate_header
r_static
r_const
r_char
op_star
id|generate_header
c_func
(paren
r_const
r_char
op_star
id|commit
comma
r_const
r_char
op_star
id|parent
comma
r_const
r_char
op_star
id|msg
comma
r_int
r_int
id|len
)paren
(brace
r_static
r_char
id|this_header
(braket
l_int|16384
)braket
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose_header
)paren
r_return
id|commit
suffix:semicolon
id|offset
op_assign
id|sprintf
c_func
(paren
id|this_header
comma
l_string|&quot;%s%s (from %s)&bslash;n&quot;
comma
id|header_prefix
comma
id|commit
comma
id|parent
)paren
suffix:semicolon
id|offset
op_add_assign
id|pretty_print_commit
c_func
(paren
id|commit_format
comma
id|msg
comma
id|len
comma
id|this_header
op_plus
id|offset
comma
r_sizeof
(paren
id|this_header
)paren
id|offset
)paren
suffix:semicolon
r_return
id|this_header
suffix:semicolon
)brace
DECL|function|diff_tree_commit
r_static
r_int
id|diff_tree_commit
c_func
(paren
r_const
r_int
r_char
op_star
id|commit
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|size
comma
id|offset
suffix:semicolon
r_char
op_star
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
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
r_static
r_char
id|commit_name
(braket
l_int|60
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|commit_name
comma
id|sha1_to_hex
c_func
(paren
id|commit
)paren
)paren
suffix:semicolon
id|name
op_assign
id|commit_name
suffix:semicolon
)brace
multiline_comment|/* Root commit? */
r_if
c_cond
(paren
id|show_root_diff
op_logical_and
id|memcmp
c_func
(paren
id|buf
op_plus
l_int|46
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
(brace
id|header
op_assign
id|generate_header
c_func
(paren
id|name
comma
l_string|&quot;root&quot;
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|diff_root_tree
c_func
(paren
id|commit
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
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
r_int
r_char
id|parent
(braket
l_int|20
)braket
suffix:semicolon
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
id|header
op_assign
id|generate_header
c_func
(paren
id|name
comma
id|sha1_to_hex
c_func
(paren
id|parent
)paren
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|diff_tree_sha1_top
c_func
(paren
id|parent
comma
id|commit
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
op_logical_and
id|verbose_header
)paren
(brace
id|header_prefix
op_assign
l_string|&quot;&bslash;ndiff-tree &quot;
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Don&squot;t print multiple merge entries if we&n;&t;&t;&t; * don&squot;t print the diffs.&n;&t;&t;&t; */
)brace
id|offset
op_add_assign
l_int|48
suffix:semicolon
)brace
r_return
l_int|0
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
r_static
r_char
id|this_header
(braket
l_int|1000
)braket
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
id|diff_tree_sha1_top
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
id|line
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|diff_tree_commit
c_func
(paren
id|commit
comma
id|line
)paren
suffix:semicolon
)brace
DECL|variable|diff_tree_usage
r_static
r_char
op_star
id|diff_tree_usage
op_assign
l_string|&quot;git-diff-tree [--stdin] [-m] [-s] [-v] [--pretty] [-t] &quot;
l_string|&quot;[&lt;common diff options&gt;] &lt;tree-ish&gt; &lt;tree-ish&gt;&quot;
id|COMMON_DIFF_OPTIONS_HELP
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|nr_sha1
suffix:semicolon
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|2
)braket
(braket
l_int|20
)braket
suffix:semicolon
id|nr_sha1
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
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
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_ne
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|nr_sha1
OL
l_int|2
op_logical_and
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
(braket
id|nr_sha1
)braket
)paren
)paren
(brace
id|nr_sha1
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
l_string|&quot;--&quot;
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
l_string|&quot;-t&quot;
)paren
)paren
(brace
id|recursive
op_assign
id|show_tree_entry_in_recursive
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
l_string|&quot;-R&quot;
)paren
)paren
(brace
id|diff_setup_opt
op_or_assign
id|DIFF_SETUP_REVERSE
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
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-u&quot;
)paren
)paren
(brace
id|diff_output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-S&quot;
comma
l_int|2
)paren
)paren
(brace
id|pickaxe
op_assign
id|arg
op_plus
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-O&quot;
comma
l_int|2
)paren
)paren
(brace
id|orderfile
op_assign
id|arg
op_plus
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--diff-filter=&quot;
comma
l_int|14
)paren
)paren
(brace
id|diff_filter
op_assign
id|arg
op_plus
l_int|14
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
l_string|&quot;--pickaxe-all&quot;
)paren
)paren
(brace
id|pickaxe_opts
op_assign
id|DIFF_PICKAXE_ALL
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-M&quot;
comma
l_int|2
)paren
)paren
(brace
id|detect_rename
op_assign
id|DIFF_DETECT_RENAME
suffix:semicolon
r_if
c_cond
(paren
(paren
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
)paren
op_eq
l_int|1
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-C&quot;
comma
l_int|2
)paren
)paren
(brace
id|detect_rename
op_assign
id|DIFF_DETECT_COPY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
)paren
op_eq
l_int|1
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-B&quot;
comma
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|diff_break_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
)paren
op_eq
l_int|1
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
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
l_string|&quot;--find-copies-harder&quot;
)paren
)paren
(brace
id|find_copies_harder
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
l_string|&quot;--name-only&quot;
)paren
)paren
(brace
id|diff_output_format
op_assign
id|DIFF_FORMAT_NAME
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
l_string|&quot;--name-only-z&quot;
)paren
)paren
(brace
id|diff_output_format
op_assign
id|DIFF_FORMAT_NAME_Z
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
id|diff_output_format
op_assign
id|DIFF_FORMAT_MACHINE
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
id|diff_output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
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
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|verbose_header
op_assign
l_int|1
suffix:semicolon
id|header_prefix
op_assign
l_string|&quot;diff-tree &quot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--pretty&quot;
comma
l_int|8
)paren
)paren
(brace
id|verbose_header
op_assign
l_int|1
suffix:semicolon
id|header_prefix
op_assign
l_string|&quot;diff-tree &quot;
suffix:semicolon
id|commit_format
op_assign
id|get_commit_format
c_func
(paren
id|arg
op_plus
l_int|8
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--root&quot;
)paren
)paren
(brace
id|show_root_diff
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
id|find_copies_harder
op_logical_and
id|detect_rename
op_ne
id|DIFF_DETECT_COPY
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
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
r_switch
c_cond
(paren
id|nr_sha1
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|read_stdin
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|diff_tree_commit
c_func
(paren
id|sha1
(braket
l_int|0
)braket
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|diff_tree_sha1_top
c_func
(paren
id|sha1
(braket
l_int|0
)braket
comma
id|sha1
(braket
l_int|1
)braket
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|read_stdin
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|detect_rename
)paren
id|diff_setup_opt
op_or_assign
(paren
id|DIFF_SETUP_USE_SIZE_CACHE
op_or
id|DIFF_SETUP_USE_CACHE
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
