macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|merge_tree_usage
r_static
r_const
r_char
id|merge_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-merge-tree &lt;base-tree&gt; &lt;branch1&gt; &lt;branch2&gt;&quot;
suffix:semicolon
DECL|variable|resolve_directories
r_static
r_int
id|resolve_directories
op_assign
l_int|1
suffix:semicolon
r_static
r_void
id|merge_trees
c_func
(paren
r_struct
id|tree_desc
id|t
(braket
l_int|3
)braket
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
DECL|function|fill_tree_descriptor
r_static
r_void
op_star
id|fill_tree_descriptor
c_func
(paren
r_struct
id|tree_desc
op_star
id|desc
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_void
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|sha1
)paren
(brace
id|buf
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
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
id|desc-&gt;size
op_assign
id|size
suffix:semicolon
id|desc-&gt;buf
op_assign
id|buf
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|struct|name_entry
r_struct
id|name_entry
(brace
DECL|member|sha1
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
DECL|member|path
r_const
r_char
op_star
id|path
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|pathlen
r_int
id|pathlen
suffix:semicolon
)brace
suffix:semicolon
DECL|function|entry_clear
r_static
r_void
id|entry_clear
c_func
(paren
r_struct
id|name_entry
op_star
id|a
)paren
(brace
id|memset
c_func
(paren
id|a
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|a
)paren
)paren
suffix:semicolon
)brace
DECL|function|entry_compare
r_static
r_int
id|entry_compare
c_func
(paren
r_struct
id|name_entry
op_star
id|a
comma
r_struct
id|name_entry
op_star
id|b
)paren
(brace
r_return
id|base_name_compare
c_func
(paren
id|a-&gt;path
comma
id|a-&gt;pathlen
comma
id|a-&gt;mode
comma
id|b-&gt;path
comma
id|b-&gt;pathlen
comma
id|b-&gt;mode
)paren
suffix:semicolon
)brace
DECL|function|entry_extract
r_static
r_void
id|entry_extract
c_func
(paren
r_struct
id|tree_desc
op_star
id|t
comma
r_struct
id|name_entry
op_star
id|a
)paren
(brace
id|a-&gt;sha1
op_assign
id|tree_entry_extract
c_func
(paren
id|t
comma
op_amp
id|a-&gt;path
comma
op_amp
id|a-&gt;mode
)paren
suffix:semicolon
id|a-&gt;pathlen
op_assign
id|strlen
c_func
(paren
id|a-&gt;path
)paren
suffix:semicolon
)brace
multiline_comment|/* An empty entry never compares same, not even to another empty entry */
DECL|function|same_entry
r_static
r_int
id|same_entry
c_func
(paren
r_struct
id|name_entry
op_star
id|a
comma
r_struct
id|name_entry
op_star
id|b
)paren
(brace
r_return
id|a-&gt;sha1
op_logical_and
id|b-&gt;sha1
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|a-&gt;sha1
comma
id|b-&gt;sha1
comma
l_int|20
)paren
op_logical_and
id|a-&gt;mode
op_eq
id|b-&gt;mode
suffix:semicolon
)brace
DECL|function|sha1_to_hex_zero
r_static
r_const
r_char
op_star
id|sha1_to_hex_zero
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|sha1
)paren
r_return
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_return
l_string|&quot;0000000000000000000000000000000000000000&quot;
suffix:semicolon
)brace
DECL|function|resolve
r_static
r_void
id|resolve
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_struct
id|name_entry
op_star
id|branch1
comma
r_struct
id|name_entry
op_star
id|result
)paren
(brace
r_char
id|branch1_sha1
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* If it&squot;s already branch1, don&squot;t bother showing it */
r_if
c_cond
(paren
op_logical_neg
id|branch1
)paren
r_return
suffix:semicolon
id|memcpy
c_func
(paren
id|branch1_sha1
comma
id|sha1_to_hex_zero
c_func
(paren
id|branch1-&gt;sha1
)paren
comma
l_int|41
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;0 %06o-&gt;%06o %s-&gt;%s %s%s&bslash;n&quot;
comma
id|branch1-&gt;mode
comma
id|result-&gt;mode
comma
id|branch1_sha1
comma
id|sha1_to_hex_zero
c_func
(paren
id|result-&gt;sha1
)paren
comma
id|base
comma
id|result-&gt;path
)paren
suffix:semicolon
)brace
DECL|function|unresolved_directory
r_static
r_int
id|unresolved_directory
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_struct
id|name_entry
id|n
(braket
l_int|3
)braket
)paren
(brace
r_int
id|baselen
suffix:semicolon
r_char
op_star
id|newbase
suffix:semicolon
r_struct
id|name_entry
op_star
id|p
suffix:semicolon
r_struct
id|tree_desc
id|t
(braket
l_int|3
)braket
suffix:semicolon
r_void
op_star
id|buf0
comma
op_star
id|buf1
comma
op_star
id|buf2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_directories
)paren
r_return
l_int|0
suffix:semicolon
id|p
op_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mode
)paren
(brace
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mode
)paren
id|p
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|p-&gt;mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
id|newbase
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
id|p-&gt;pathlen
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
id|p-&gt;path
comma
id|p-&gt;pathlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
op_plus
id|p-&gt;pathlen
comma
l_string|&quot;/&quot;
comma
l_int|2
)paren
suffix:semicolon
id|buf0
op_assign
id|fill_tree_descriptor
c_func
(paren
id|t
op_plus
l_int|0
comma
id|n
(braket
l_int|0
)braket
dot
id|sha1
)paren
suffix:semicolon
id|buf1
op_assign
id|fill_tree_descriptor
c_func
(paren
id|t
op_plus
l_int|1
comma
id|n
(braket
l_int|1
)braket
dot
id|sha1
)paren
suffix:semicolon
id|buf2
op_assign
id|fill_tree_descriptor
c_func
(paren
id|t
op_plus
l_int|2
comma
id|n
(braket
l_int|2
)braket
dot
id|sha1
)paren
suffix:semicolon
id|merge_trees
c_func
(paren
id|t
comma
id|newbase
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf0
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf1
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf2
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|unresolved
r_static
r_void
id|unresolved
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_struct
id|name_entry
id|n
(braket
l_int|3
)braket
)paren
(brace
r_if
c_cond
(paren
id|unresolved_directory
c_func
(paren
id|base
comma
id|n
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|n
(braket
l_int|0
)braket
dot
id|sha1
)paren
id|printf
c_func
(paren
l_string|&quot;1 %06o %s %s%s&bslash;n&quot;
comma
id|n
(braket
l_int|0
)braket
dot
id|mode
comma
id|sha1_to_hex
c_func
(paren
id|n
(braket
l_int|0
)braket
dot
id|sha1
)paren
comma
id|base
comma
id|n
(braket
l_int|0
)braket
dot
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
(braket
l_int|1
)braket
dot
id|sha1
)paren
id|printf
c_func
(paren
l_string|&quot;2 %06o %s %s%s&bslash;n&quot;
comma
id|n
(braket
l_int|1
)braket
dot
id|mode
comma
id|sha1_to_hex
c_func
(paren
id|n
(braket
l_int|1
)braket
dot
id|sha1
)paren
comma
id|base
comma
id|n
(braket
l_int|1
)braket
dot
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
(braket
l_int|2
)braket
dot
id|sha1
)paren
id|printf
c_func
(paren
l_string|&quot;3 %06o %s %s%s&bslash;n&quot;
comma
id|n
(braket
l_int|2
)braket
dot
id|mode
comma
id|sha1_to_hex
c_func
(paren
id|n
(braket
l_int|2
)braket
dot
id|sha1
)paren
comma
id|base
comma
id|n
(braket
l_int|2
)braket
dot
id|path
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Merge two trees together (t[1] and t[2]), using a common base (t[0])&n; * as the origin.&n; *&n; * This walks the (sorted) trees in lock-step, checking every possible&n; * name. Note that directories automatically sort differently from other&n; * files (see &quot;base_name_compare&quot;), so you&squot;ll never see file/directory&n; * conflicts, because they won&squot;t ever compare the same.&n; *&n; * IOW, if a directory changes to a filename, it will automatically be&n; * seen as the directory going away, and the filename being created.&n; *&n; * Think of this as a three-way diff.&n; *&n; * The output will be either:&n; *  - successful merge&n; *&t; &quot;0 mode sha1 filename&quot;&n; *    NOTE NOTE NOTE! FIXME! We really really need to walk the index&n; *    in parallel with this too!&n; * &n; *  - conflict:&n; *&t;&quot;1 mode sha1 filename&quot;&n; *&t;&quot;2 mode sha1 filename&quot;&n; *&t;&quot;3 mode sha1 filename&quot;&n; *    where not all of the 1/2/3 lines may exist, of course.&n; *&n; * The successful merge rules are the same as for the three-way merge&n; * in git-read-tree.&n; */
DECL|function|merge_trees
r_static
r_void
id|merge_trees
c_func
(paren
r_struct
id|tree_desc
id|t
(braket
l_int|3
)braket
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|name_entry
id|entry
(braket
l_int|3
)braket
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|last
suffix:semicolon
id|last
op_assign
l_int|1
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|t
(braket
id|i
)braket
dot
id|size
)paren
r_continue
suffix:semicolon
id|entry_extract
c_func
(paren
id|t
op_plus
id|i
comma
id|entry
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last
op_ge
l_int|0
)paren
(brace
r_int
id|cmp
op_assign
id|entry_compare
c_func
(paren
id|entry
op_plus
id|i
comma
id|entry
op_plus
id|last
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Is the new name bigger than the old one?&n;&t;&t;&t;&t; * Ignore it&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Is the new name smaller than the old one?&n;&t;&t;&t;&t; * Ignore all old ones&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
id|mask
op_assign
l_int|0
suffix:semicolon
)brace
id|mask
op_or_assign
l_int|1u
op_lshift
id|i
suffix:semicolon
id|last
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Update the tree entries we&squot;ve walked, and clear&n;&t;&t; * all the unused name-entries.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
(paren
l_int|1u
op_lshift
id|i
)paren
)paren
(brace
id|update_tree_entry
c_func
(paren
id|t
op_plus
id|i
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|entry_clear
c_func
(paren
id|entry
op_plus
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* Same in both? */
r_if
c_cond
(paren
id|same_entry
c_func
(paren
id|entry
op_plus
l_int|1
comma
id|entry
op_plus
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
id|entry
(braket
l_int|0
)braket
dot
id|sha1
)paren
(brace
id|resolve
c_func
(paren
id|base
comma
l_int|NULL
comma
id|entry
op_plus
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|same_entry
c_func
(paren
id|entry
op_plus
l_int|0
comma
id|entry
op_plus
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|entry
(braket
l_int|2
)braket
dot
id|sha1
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry
(braket
l_int|2
)braket
dot
id|mode
)paren
)paren
(brace
id|resolve
c_func
(paren
id|base
comma
id|entry
op_plus
l_int|1
comma
id|entry
op_plus
l_int|2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|same_entry
c_func
(paren
id|entry
op_plus
l_int|0
comma
id|entry
op_plus
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
id|entry
(braket
l_int|1
)braket
dot
id|sha1
op_logical_and
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry
(braket
l_int|1
)braket
dot
id|mode
)paren
)paren
(brace
id|resolve
c_func
(paren
id|base
comma
l_int|NULL
comma
id|entry
op_plus
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|unresolved
c_func
(paren
id|base
comma
id|entry
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_tree_descriptor
r_static
r_void
op_star
id|get_tree_descriptor
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
id|rev
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|rev
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unknown rev %s&quot;
comma
id|rev
)paren
suffix:semicolon
id|buf
op_assign
id|fill_tree_descriptor
c_func
(paren
id|desc
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a tree&quot;
comma
id|rev
)paren
suffix:semicolon
r_return
id|buf
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
r_struct
id|tree_desc
id|t
(braket
l_int|3
)braket
suffix:semicolon
r_void
op_star
id|buf1
comma
op_star
id|buf2
comma
op_star
id|buf3
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|4
)paren
id|usage
c_func
(paren
id|merge_tree_usage
)paren
suffix:semicolon
id|buf1
op_assign
id|get_tree_descriptor
c_func
(paren
id|t
op_plus
l_int|0
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|buf2
op_assign
id|get_tree_descriptor
c_func
(paren
id|t
op_plus
l_int|1
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|buf3
op_assign
id|get_tree_descriptor
c_func
(paren
id|t
op_plus
l_int|2
comma
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|merge_trees
c_func
(paren
id|t
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf1
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf2
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
