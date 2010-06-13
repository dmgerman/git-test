macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
DECL|variable|merge_tree_usage
r_static
r_const
r_char
id|merge_tree_usage
(braket
)braket
op_assign
l_string|&quot;git merge-tree &lt;base-tree&gt; &lt;branch1&gt; &lt;branch2&gt;&quot;
suffix:semicolon
DECL|variable|resolve_directories
r_static
r_int
id|resolve_directories
op_assign
l_int|1
suffix:semicolon
DECL|struct|merge_list
r_struct
id|merge_list
(brace
DECL|member|next
r_struct
id|merge_list
op_star
id|next
suffix:semicolon
DECL|member|link
r_struct
id|merge_list
op_star
id|link
suffix:semicolon
multiline_comment|/* other stages for this object */
DECL|member|stage
r_int
r_int
id|stage
suffix:colon
l_int|2
comma
DECL|member|flags
id|flags
suffix:colon
l_int|30
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|path
r_const
r_char
op_star
id|path
suffix:semicolon
DECL|member|blob
r_struct
id|blob
op_star
id|blob
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|merge_result
DECL|variable|merge_result_end
r_static
r_struct
id|merge_list
op_star
id|merge_result
comma
op_star
op_star
id|merge_result_end
op_assign
op_amp
id|merge_result
suffix:semicolon
DECL|function|add_merge_entry
r_static
r_void
id|add_merge_entry
c_func
(paren
r_struct
id|merge_list
op_star
id|entry
)paren
(brace
op_star
id|merge_result_end
op_assign
id|entry
suffix:semicolon
id|merge_result_end
op_assign
op_amp
id|entry-&gt;next
suffix:semicolon
)brace
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
DECL|function|explanation
r_static
r_const
r_char
op_star
id|explanation
c_func
(paren
r_struct
id|merge_list
op_star
id|entry
)paren
(brace
r_switch
c_cond
(paren
id|entry-&gt;stage
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_string|&quot;merged&quot;
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_string|&quot;added in remote&quot;
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|entry-&gt;link
)paren
r_return
l_string|&quot;added in both&quot;
suffix:semicolon
r_return
l_string|&quot;added in local&quot;
suffix:semicolon
)brace
multiline_comment|/* Existed in base */
id|entry
op_assign
id|entry-&gt;link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
l_string|&quot;removed in both&quot;
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;link
)paren
r_return
l_string|&quot;changed in both&quot;
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;stage
op_eq
l_int|3
)paren
r_return
l_string|&quot;removed in local&quot;
suffix:semicolon
r_return
l_string|&quot;removed in remote&quot;
suffix:semicolon
)brace
r_extern
r_void
op_star
id|merge_file
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|blob
op_star
comma
r_struct
id|blob
op_star
comma
r_struct
id|blob
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|function|result
r_static
r_void
op_star
id|result
c_func
(paren
r_struct
id|merge_list
op_star
id|entry
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_struct
id|blob
op_star
id|base
comma
op_star
id|our
comma
op_star
id|their
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;stage
)paren
r_return
id|read_sha1_file
c_func
(paren
id|entry-&gt;blob-&gt;object.sha1
comma
op_amp
id|type
comma
id|size
)paren
suffix:semicolon
id|base
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;stage
op_eq
l_int|1
)paren
(brace
id|base
op_assign
id|entry-&gt;blob
suffix:semicolon
id|entry
op_assign
id|entry-&gt;link
suffix:semicolon
)brace
id|our
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_logical_and
id|entry-&gt;stage
op_eq
l_int|2
)paren
(brace
id|our
op_assign
id|entry-&gt;blob
suffix:semicolon
id|entry
op_assign
id|entry-&gt;link
suffix:semicolon
)brace
id|their
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|their
op_assign
id|entry-&gt;blob
suffix:semicolon
r_return
id|merge_file
c_func
(paren
id|entry-&gt;path
comma
id|base
comma
id|our
comma
id|their
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|origin
r_static
r_void
op_star
id|origin
c_func
(paren
r_struct
id|merge_list
op_star
id|entry
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;stage
op_eq
l_int|2
)paren
r_return
id|read_sha1_file
c_func
(paren
id|entry-&gt;blob-&gt;object.sha1
comma
op_amp
id|type
comma
id|size
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;link
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|show_outf
r_static
r_int
id|show_outf
c_func
(paren
r_void
op_star
id|priv_
comma
id|mmbuffer_t
op_star
id|mb
comma
r_int
id|nbuf
)paren
(brace
r_int
id|i
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
id|nbuf
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%.*s&quot;
comma
(paren
r_int
)paren
id|mb
(braket
id|i
)braket
dot
id|size
comma
id|mb
(braket
id|i
)braket
dot
id|ptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_diff
r_static
r_void
id|show_diff
c_func
(paren
r_struct
id|merge_list
op_star
id|entry
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|mmfile_t
id|src
comma
id|dst
suffix:semicolon
id|xpparam_t
id|xpp
suffix:semicolon
id|xdemitconf_t
id|xecfg
suffix:semicolon
id|xdemitcb_t
id|ecb
suffix:semicolon
id|xpp.flags
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|xecfg
comma
l_int|0
comma
r_sizeof
(paren
id|xecfg
)paren
)paren
suffix:semicolon
id|xecfg.ctxlen
op_assign
l_int|3
suffix:semicolon
id|ecb.outf
op_assign
id|show_outf
suffix:semicolon
id|ecb.priv
op_assign
l_int|NULL
suffix:semicolon
id|src.ptr
op_assign
id|origin
c_func
(paren
id|entry
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|src.ptr
)paren
id|size
op_assign
l_int|0
suffix:semicolon
id|src.size
op_assign
id|size
suffix:semicolon
id|dst.ptr
op_assign
id|result
c_func
(paren
id|entry
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst.ptr
)paren
id|size
op_assign
l_int|0
suffix:semicolon
id|dst.size
op_assign
id|size
suffix:semicolon
id|xdi_diff
c_func
(paren
op_amp
id|src
comma
op_amp
id|dst
comma
op_amp
id|xpp
comma
op_amp
id|xecfg
comma
op_amp
id|ecb
)paren
suffix:semicolon
id|free
c_func
(paren
id|src.ptr
)paren
suffix:semicolon
id|free
c_func
(paren
id|dst.ptr
)paren
suffix:semicolon
)brace
DECL|function|show_result_list
r_static
r_void
id|show_result_list
c_func
(paren
r_struct
id|merge_list
op_star
id|entry
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|explanation
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
r_do
(brace
r_struct
id|merge_list
op_star
id|link
op_assign
id|entry-&gt;link
suffix:semicolon
r_static
r_const
r_char
op_star
id|desc
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;result&quot;
comma
l_string|&quot;base&quot;
comma
l_string|&quot;our&quot;
comma
l_string|&quot;their&quot;
)brace
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  %-6s %o %s %s&bslash;n&quot;
comma
id|desc
(braket
id|entry-&gt;stage
)braket
comma
id|entry-&gt;mode
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;blob-&gt;object.sha1
)paren
comma
id|entry-&gt;path
)paren
suffix:semicolon
id|entry
op_assign
id|link
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entry
)paren
suffix:semicolon
)brace
DECL|function|show_result
r_static
r_void
id|show_result
c_func
(paren
r_void
)paren
(brace
r_struct
id|merge_list
op_star
id|walk
suffix:semicolon
id|walk
op_assign
id|merge_result
suffix:semicolon
r_while
c_loop
(paren
id|walk
)paren
(brace
id|show_result_list
c_func
(paren
id|walk
)paren
suffix:semicolon
id|show_diff
c_func
(paren
id|walk
)paren
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
suffix:semicolon
)brace
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
id|hashcmp
c_func
(paren
id|a-&gt;sha1
comma
id|b-&gt;sha1
)paren
op_logical_and
id|a-&gt;mode
op_eq
id|b-&gt;mode
suffix:semicolon
)brace
DECL|function|create_entry
r_static
r_struct
id|merge_list
op_star
id|create_entry
c_func
(paren
r_int
id|stage
comma
r_int
id|mode
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|merge_list
op_star
id|res
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
id|res-&gt;stage
op_assign
id|stage
suffix:semicolon
id|res-&gt;path
op_assign
id|path
suffix:semicolon
id|res-&gt;mode
op_assign
id|mode
suffix:semicolon
id|res-&gt;blob
op_assign
id|lookup_blob
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|traverse_path
r_static
r_char
op_star
id|traverse_path
c_func
(paren
r_const
r_struct
id|traverse_info
op_star
id|info
comma
r_const
r_struct
id|name_entry
op_star
id|n
)paren
(brace
r_char
op_star
id|path
op_assign
id|xmalloc
c_func
(paren
id|traverse_path_len
c_func
(paren
id|info
comma
id|n
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|make_traverse_path
c_func
(paren
id|path
comma
id|info
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|resolve
r_static
r_void
id|resolve
c_func
(paren
r_const
r_struct
id|traverse_info
op_star
id|info
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
r_struct
id|merge_list
op_star
id|orig
comma
op_star
id|final
suffix:semicolon
r_const
r_char
op_star
id|path
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
id|path
op_assign
id|traverse_path
c_func
(paren
id|info
comma
id|result
)paren
suffix:semicolon
id|orig
op_assign
id|create_entry
c_func
(paren
l_int|2
comma
id|branch1-&gt;mode
comma
id|branch1-&gt;sha1
comma
id|path
)paren
suffix:semicolon
id|final
op_assign
id|create_entry
c_func
(paren
l_int|0
comma
id|result-&gt;mode
comma
id|result-&gt;sha1
comma
id|path
)paren
suffix:semicolon
id|final-&gt;link
op_assign
id|orig
suffix:semicolon
id|add_merge_entry
c_func
(paren
id|final
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
r_struct
id|traverse_info
op_star
id|info
comma
r_struct
id|name_entry
id|n
(braket
l_int|3
)braket
)paren
(brace
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
id|newbase
op_assign
id|traverse_path
c_func
(paren
id|info
comma
id|p
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
DECL|function|link_entry
r_static
r_struct
id|merge_list
op_star
id|link_entry
c_func
(paren
r_int
id|stage
comma
r_const
r_struct
id|traverse_info
op_star
id|info
comma
r_struct
id|name_entry
op_star
id|n
comma
r_struct
id|merge_list
op_star
id|entry
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_struct
id|merge_list
op_star
id|link
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n-&gt;mode
)paren
r_return
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|path
op_assign
id|entry-&gt;path
suffix:semicolon
r_else
id|path
op_assign
id|traverse_path
c_func
(paren
id|info
comma
id|n
)paren
suffix:semicolon
id|link
op_assign
id|create_entry
c_func
(paren
id|stage
comma
id|n-&gt;mode
comma
id|n-&gt;sha1
comma
id|path
)paren
suffix:semicolon
id|link-&gt;link
op_assign
id|entry
suffix:semicolon
r_return
id|link
suffix:semicolon
)brace
DECL|function|unresolved
r_static
r_void
id|unresolved
c_func
(paren
r_const
r_struct
id|traverse_info
op_star
id|info
comma
r_struct
id|name_entry
id|n
(braket
l_int|3
)braket
)paren
(brace
r_struct
id|merge_list
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|unresolved_directory
c_func
(paren
id|info
comma
id|n
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Do them in reverse order so that the resulting link&n;&t; * list has the stages in order - link_entry adds new&n;&t; * links at the front.&n;&t; */
id|entry
op_assign
id|link_entry
c_func
(paren
l_int|3
comma
id|info
comma
id|n
op_plus
l_int|2
comma
id|entry
)paren
suffix:semicolon
id|entry
op_assign
id|link_entry
c_func
(paren
l_int|2
comma
id|info
comma
id|n
op_plus
l_int|1
comma
id|entry
)paren
suffix:semicolon
id|entry
op_assign
id|link_entry
c_func
(paren
l_int|1
comma
id|info
comma
id|n
op_plus
l_int|0
comma
id|entry
)paren
suffix:semicolon
id|add_merge_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Merge two trees together (t[1] and t[2]), using a common base (t[0])&n; * as the origin.&n; *&n; * This walks the (sorted) trees in lock-step, checking every possible&n; * name. Note that directories automatically sort differently from other&n; * files (see &quot;base_name_compare&quot;), so you&squot;ll never see file/directory&n; * conflicts, because they won&squot;t ever compare the same.&n; *&n; * IOW, if a directory changes to a filename, it will automatically be&n; * seen as the directory going away, and the filename being created.&n; *&n; * Think of this as a three-way diff.&n; *&n; * The output will be either:&n; *  - successful merge&n; *&t; &quot;0 mode sha1 filename&quot;&n; *    NOTE NOTE NOTE! FIXME! We really really need to walk the index&n; *    in parallel with this too!&n; *&n; *  - conflict:&n; *&t;&quot;1 mode sha1 filename&quot;&n; *&t;&quot;2 mode sha1 filename&quot;&n; *&t;&quot;3 mode sha1 filename&quot;&n; *    where not all of the 1/2/3 lines may exist, of course.&n; *&n; * The successful merge rules are the same as for the three-way merge&n; * in git-read-tree.&n; */
DECL|function|threeway_callback
r_static
r_int
id|threeway_callback
c_func
(paren
r_int
id|n
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|dirmask
comma
r_struct
id|name_entry
op_star
id|entry
comma
r_struct
id|traverse_info
op_star
id|info
)paren
(brace
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
id|info
comma
l_int|NULL
comma
id|entry
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|mask
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
id|info
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
r_return
id|mask
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
id|info
comma
l_int|NULL
comma
id|entry
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
)brace
id|unresolved
c_func
(paren
id|info
comma
id|entry
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
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
r_struct
id|traverse_info
id|info
suffix:semicolon
id|setup_traverse_info
c_func
(paren
op_amp
id|info
comma
id|base
)paren
suffix:semicolon
id|info.fn
op_assign
id|threeway_callback
suffix:semicolon
id|traverse_trees
c_func
(paren
l_int|3
comma
id|t
comma
op_amp
id|info
)paren
suffix:semicolon
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
DECL|function|cmd_merge_tree
r_int
id|cmd_merge_tree
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
comma
r_const
r_char
op_star
id|prefix
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
op_ne
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
id|show_result
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
