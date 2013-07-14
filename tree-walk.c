macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;pathspec.h&quot;
DECL|function|get_mode
r_static
r_const
r_char
op_star
id|get_mode
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
r_int
op_star
id|modep
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_int
r_int
id|mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot; &squot;
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|str
op_increment
)paren
op_ne
l_char|&squot; &squot;
)paren
(brace
r_if
c_cond
(paren
id|c
template_param
l_char|&squot;7&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_lshift
l_int|3
)paren
op_plus
(paren
id|c
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
op_star
id|modep
op_assign
id|mode
suffix:semicolon
r_return
id|str
suffix:semicolon
)brace
DECL|function|decode_tree_entry
r_static
r_void
id|decode_tree_entry
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
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
r_int
id|mode
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|24
op_logical_or
id|buf
(braket
id|size
l_int|21
)braket
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file&quot;
)paren
suffix:semicolon
id|path
op_assign
id|get_mode
c_func
(paren
id|buf
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
op_logical_neg
op_star
id|path
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Initialize the descriptor entry */
id|desc-&gt;entry.path
op_assign
id|path
suffix:semicolon
id|desc-&gt;entry.mode
op_assign
id|mode
suffix:semicolon
id|desc-&gt;entry.sha1
op_assign
(paren
r_const
r_int
r_char
op_star
)paren
(paren
id|path
op_plus
id|len
)paren
suffix:semicolon
)brace
DECL|function|init_tree_desc
r_void
id|init_tree_desc
c_func
(paren
r_struct
id|tree_desc
op_star
id|desc
comma
r_const
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
id|desc-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|desc-&gt;size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|decode_tree_entry
c_func
(paren
id|desc
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|fill_tree_descriptor
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
id|init_tree_desc
c_func
(paren
id|desc
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
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
op_star
id|a
op_assign
id|t-&gt;entry
suffix:semicolon
)brace
DECL|function|update_tree_entry
r_void
id|update_tree_entry
c_func
(paren
r_struct
id|tree_desc
op_star
id|desc
)paren
(brace
r_const
r_void
op_star
id|buf
op_assign
id|desc-&gt;buffer
suffix:semicolon
r_const
r_int
r_char
op_star
id|end
op_assign
id|desc-&gt;entry.sha1
op_plus
l_int|20
suffix:semicolon
r_int
r_int
id|size
op_assign
id|desc-&gt;size
suffix:semicolon
r_int
r_int
id|len
op_assign
id|end
(paren
r_const
r_int
r_char
op_star
)paren
id|buf
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
id|buf
op_assign
id|end
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|desc-&gt;buffer
op_assign
id|buf
suffix:semicolon
id|desc-&gt;size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|decode_tree_entry
c_func
(paren
id|desc
comma
id|buf
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|tree_entry
r_int
id|tree_entry
c_func
(paren
r_struct
id|tree_desc
op_star
id|desc
comma
r_struct
id|name_entry
op_star
id|entry
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;size
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
id|desc-&gt;entry
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|desc
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setup_traverse_info
r_void
id|setup_traverse_info
c_func
(paren
r_struct
id|traverse_info
op_star
id|info
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_static
r_struct
id|traverse_info
id|dummy
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
op_logical_and
id|base
(braket
id|pathlen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|pathlen
op_decrement
suffix:semicolon
id|info-&gt;pathlen
op_assign
id|pathlen
ques
c_cond
id|pathlen
op_plus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|info-&gt;name.path
op_assign
id|base
suffix:semicolon
id|info-&gt;name.sha1
op_assign
(paren
r_void
op_star
)paren
(paren
id|base
op_plus
id|pathlen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
)paren
id|info-&gt;prev
op_assign
op_amp
id|dummy
suffix:semicolon
)brace
DECL|function|make_traverse_path
r_char
op_star
id|make_traverse_path
c_func
(paren
r_char
op_star
id|path
comma
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
r_int
id|len
op_assign
id|tree_entry_len
c_func
(paren
id|n
)paren
suffix:semicolon
r_int
id|pathlen
op_assign
id|info-&gt;pathlen
suffix:semicolon
id|path
(braket
id|pathlen
op_plus
id|len
)braket
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
id|memcpy
c_func
(paren
id|path
op_plus
id|pathlen
comma
id|n-&gt;path
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathlen
)paren
r_break
suffix:semicolon
id|path
(braket
op_decrement
id|pathlen
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|n
op_assign
op_amp
id|info-&gt;name
suffix:semicolon
id|len
op_assign
id|tree_entry_len
c_func
(paren
id|n
)paren
suffix:semicolon
id|info
op_assign
id|info-&gt;prev
suffix:semicolon
id|pathlen
op_sub_assign
id|len
suffix:semicolon
)brace
r_return
id|path
suffix:semicolon
)brace
DECL|struct|tree_desc_skip
r_struct
id|tree_desc_skip
(brace
DECL|member|prev
r_struct
id|tree_desc_skip
op_star
id|prev
suffix:semicolon
DECL|member|ptr
r_const
r_void
op_star
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tree_desc_x
r_struct
id|tree_desc_x
(brace
DECL|member|d
r_struct
id|tree_desc
id|d
suffix:semicolon
DECL|member|skip
r_struct
id|tree_desc_skip
op_star
id|skip
suffix:semicolon
)brace
suffix:semicolon
DECL|function|name_compare
r_static
r_int
id|name_compare
c_func
(paren
r_const
r_char
op_star
id|a
comma
r_int
id|a_len
comma
r_const
r_char
op_star
id|b
comma
r_int
id|b_len
)paren
(brace
r_int
id|len
op_assign
(paren
id|a_len
OL
id|b_len
)paren
ques
c_cond
id|a_len
suffix:colon
id|b_len
suffix:semicolon
r_int
id|cmp
op_assign
id|memcmp
c_func
(paren
id|a
comma
id|b
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
)paren
r_return
id|cmp
suffix:semicolon
r_return
(paren
id|a_len
id|b_len
)paren
suffix:semicolon
)brace
DECL|function|check_entry_match
r_static
r_int
id|check_entry_match
c_func
(paren
r_const
r_char
op_star
id|a
comma
r_int
id|a_len
comma
r_const
r_char
op_star
id|b
comma
r_int
id|b_len
)paren
(brace
multiline_comment|/*&n;&t; * The caller wants to pick *a* from a tree or nothing.&n;&t; * We are looking at *b* in a tree.&n;&t; *&n;&t; * (0) If a and b are the same name, we are trivially happy.&n;&t; *&n;&t; * There are three possibilities where *a* could be hiding&n;&t; * behind *b*.&n;&t; *&n;&t; * (1) *a* == &quot;t&quot;,   *b* == &quot;ab&quot;  i.e. *b* sorts earlier than *a* no&n;&t; *                                matter what.&n;&t; * (2) *a* == &quot;t&quot;,   *b* == &quot;t-2&quot; and &quot;t&quot; is a subtree in the tree;&n;&t; * (3) *a* == &quot;t-2&quot;, *b* == &quot;t&quot;   and &quot;t-2&quot; is a blob in the tree.&n;&t; *&n;&t; * Otherwise we know *a* won&squot;t appear in the tree without&n;&t; * scanning further.&n;&t; */
r_int
id|cmp
op_assign
id|name_compare
c_func
(paren
id|a
comma
id|a_len
comma
id|b
comma
id|b_len
)paren
suffix:semicolon
multiline_comment|/* Most common case first -- reading sync&squot;d trees */
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|cmp
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OL
id|cmp
)paren
(brace
multiline_comment|/* a comes after b; it does not matter if it is case (3)&n;&t;&t;if (b_len &lt; a_len &amp;&amp; !memcmp(a, b, b_len) &amp;&amp; a[b_len] &lt; &squot;/&squot;)&n;&t;&t;&t;return 1;&n;&t;&t;*/
r_return
l_int|1
suffix:semicolon
multiline_comment|/* keep looking */
)brace
multiline_comment|/* b comes after a; are we looking at case (2)? */
r_if
c_cond
(paren
id|a_len
OL
id|b_len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|a
comma
id|b
comma
id|a_len
)paren
op_logical_and
id|b
(braket
id|a_len
)braket
OL
l_char|&squot;/&squot;
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* keep looking */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* a cannot appear in the tree */
)brace
multiline_comment|/*&n; * From the extended tree_desc, extract the first name entry, while&n; * paying attention to the candidate &quot;first&quot; name.  Most importantly,&n; * when looking for an entry, if there are entries that sorts earlier&n; * in the tree object representation than that name, skip them and&n; * process the named entry first.  We will remember that we haven&squot;t&n; * processed the first entry yet, and in the later call skip the&n; * entry we processed early when update_extended_entry() is called.&n; *&n; * E.g. if the underlying tree object has these entries:&n; *&n; *    blob    &quot;t-1&quot;&n; *    blob    &quot;t-2&quot;&n; *    tree    &quot;t&quot;&n; *    blob    &quot;t=1&quot;&n; *&n; * and the &quot;first&quot; asks for &quot;t&quot;, remember that we still need to&n; * process &quot;t-1&quot; and &quot;t-2&quot; but extract &quot;t&quot;.  After processing the&n; * entry &quot;t&quot; from this call, the caller will let us know by calling&n; * update_extended_entry() that we can remember &quot;t&quot; has been processed&n; * already.&n; */
DECL|function|extended_entry_extract
r_static
r_void
id|extended_entry_extract
c_func
(paren
r_struct
id|tree_desc_x
op_star
id|t
comma
r_struct
id|name_entry
op_star
id|a
comma
r_const
r_char
op_star
id|first
comma
r_int
id|first_len
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|tree_desc
id|probe
suffix:semicolon
r_struct
id|tree_desc_skip
op_star
id|skip
suffix:semicolon
multiline_comment|/*&n;&t; * Extract the first entry from the tree_desc, but skip the&n;&t; * ones that we already returned in earlier rounds.&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;d.size
)paren
(brace
id|entry_clear
c_func
(paren
id|a
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* not found */
)brace
id|entry_extract
c_func
(paren
op_amp
id|t-&gt;d
comma
id|a
)paren
suffix:semicolon
r_for
c_loop
(paren
id|skip
op_assign
id|t-&gt;skip
suffix:semicolon
id|skip
suffix:semicolon
id|skip
op_assign
id|skip-&gt;prev
)paren
r_if
c_cond
(paren
id|a-&gt;path
op_eq
id|skip-&gt;ptr
)paren
r_break
suffix:semicolon
multiline_comment|/* found */
r_if
c_cond
(paren
op_logical_neg
id|skip
)paren
r_break
suffix:semicolon
multiline_comment|/* We have processed this entry already. */
id|update_tree_entry
c_func
(paren
op_amp
id|t-&gt;d
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|first
op_logical_or
op_logical_neg
id|a-&gt;path
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * The caller wants &quot;first&quot; from this tree, or nothing.&n;&t; */
id|path
op_assign
id|a-&gt;path
suffix:semicolon
id|len
op_assign
id|tree_entry_len
c_func
(paren
id|a
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|check_entry_match
c_func
(paren
id|first
comma
id|first_len
comma
id|path
comma
id|len
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|entry_clear
c_func
(paren
id|a
)paren
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We need to look-ahead -- we suspect that a subtree whose&n;&t; * name is &quot;first&quot; may be hiding behind the current entry &quot;path&quot;.&n;&t; */
id|probe
op_assign
id|t-&gt;d
suffix:semicolon
r_while
c_loop
(paren
id|probe.size
)paren
(brace
id|entry_extract
c_func
(paren
op_amp
id|probe
comma
id|a
)paren
suffix:semicolon
id|path
op_assign
id|a-&gt;path
suffix:semicolon
id|len
op_assign
id|tree_entry_len
c_func
(paren
id|a
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|check_entry_match
c_func
(paren
id|first
comma
id|first_len
comma
id|path
comma
id|len
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|entry_clear
c_func
(paren
id|a
)paren
suffix:semicolon
r_case
l_int|0
suffix:colon
r_return
suffix:semicolon
r_default
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|probe
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* keep looking */
)brace
id|entry_clear
c_func
(paren
id|a
)paren
suffix:semicolon
)brace
DECL|function|update_extended_entry
r_static
r_void
id|update_extended_entry
c_func
(paren
r_struct
id|tree_desc_x
op_star
id|t
comma
r_struct
id|name_entry
op_star
id|a
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;d.entry.path
op_eq
id|a-&gt;path
)paren
(brace
id|update_tree_entry
c_func
(paren
op_amp
id|t-&gt;d
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we have returned this entry early */
r_struct
id|tree_desc_skip
op_star
id|skip
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|skip
)paren
)paren
suffix:semicolon
id|skip-&gt;ptr
op_assign
id|a-&gt;path
suffix:semicolon
id|skip-&gt;prev
op_assign
id|t-&gt;skip
suffix:semicolon
id|t-&gt;skip
op_assign
id|skip
suffix:semicolon
)brace
)brace
DECL|function|free_extended_entry
r_static
r_void
id|free_extended_entry
c_func
(paren
r_struct
id|tree_desc_x
op_star
id|t
)paren
(brace
r_struct
id|tree_desc_skip
op_star
id|p
comma
op_star
id|s
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|t-&gt;skip
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|p
)paren
(brace
id|p
op_assign
id|s-&gt;prev
suffix:semicolon
id|free
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
)brace
DECL|function|prune_traversal
r_static
r_inline
r_int
id|prune_traversal
c_func
(paren
r_struct
id|name_entry
op_star
id|e
comma
r_struct
id|traverse_info
op_star
id|info
comma
r_struct
id|strbuf
op_star
id|base
comma
r_int
id|still_interesting
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;pathspec
op_logical_or
id|still_interesting
op_eq
l_int|2
)paren
r_return
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|still_interesting
OL
l_int|0
)paren
r_return
id|still_interesting
suffix:semicolon
r_return
id|tree_entry_interesting
c_func
(paren
id|e
comma
id|base
comma
l_int|0
comma
id|info-&gt;pathspec
)paren
suffix:semicolon
)brace
DECL|function|traverse_trees
r_int
id|traverse_trees
c_func
(paren
r_int
id|n
comma
r_struct
id|tree_desc
op_star
id|t
comma
r_struct
id|traverse_info
op_star
id|info
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|name_entry
op_star
id|entry
op_assign
id|xmalloc
c_func
(paren
id|n
op_star
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|tree_desc_x
op_star
id|tx
op_assign
id|xcalloc
c_func
(paren
id|n
comma
r_sizeof
(paren
op_star
id|tx
)paren
)paren
suffix:semicolon
r_struct
id|strbuf
id|base
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|interesting
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
id|n
suffix:semicolon
id|i
op_increment
)paren
id|tx
(braket
id|i
)braket
dot
id|d
op_assign
id|t
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;prev
)paren
(brace
id|strbuf_grow
c_func
(paren
op_amp
id|base
comma
id|info-&gt;pathlen
)paren
suffix:semicolon
id|make_traverse_path
c_func
(paren
id|base.buf
comma
id|info-&gt;prev
comma
op_amp
id|info-&gt;name
)paren
suffix:semicolon
id|base.buf
(braket
id|info-&gt;pathlen
op_minus
l_int|1
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|base
comma
id|info-&gt;pathlen
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|mask
comma
id|dirmask
suffix:semicolon
r_const
r_char
op_star
id|first
op_assign
l_int|NULL
suffix:semicolon
r_int
id|first_len
op_assign
l_int|0
suffix:semicolon
r_struct
id|name_entry
op_star
id|e
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e
op_assign
id|entry
op_plus
id|i
suffix:semicolon
id|extended_entry_extract
c_func
(paren
id|tx
op_plus
id|i
comma
id|e
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * A tree may have &quot;t-2&quot; at the current location even&n;&t;&t; * though it may have &quot;t&quot; that is a subtree behind it,&n;&t;&t; * and another tree may return &quot;t&quot;.  We want to grab&n;&t;&t; * all &quot;t&quot; from all trees to match in such a case.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e
op_assign
id|entry
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;path
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|tree_entry_len
c_func
(paren
id|e
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
(brace
id|first
op_assign
id|e-&gt;path
suffix:semicolon
id|first_len
op_assign
id|len
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name_compare
c_func
(paren
id|e-&gt;path
comma
id|len
comma
id|first
comma
id|first_len
)paren
OL
l_int|0
)paren
(brace
id|first
op_assign
id|e-&gt;path
suffix:semicolon
id|first_len
op_assign
id|len
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|first
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e
op_assign
id|entry
op_plus
id|i
suffix:semicolon
id|extended_entry_extract
c_func
(paren
id|tx
op_plus
id|i
comma
id|e
comma
id|first
comma
id|first_len
)paren
suffix:semicolon
multiline_comment|/* Cull the ones that are not the earliest */
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;path
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|tree_entry_len
c_func
(paren
id|e
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name_compare
c_func
(paren
id|e-&gt;path
comma
id|len
comma
id|first
comma
id|first_len
)paren
)paren
id|entry_clear
c_func
(paren
id|e
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Now we have in entry[i] the earliest name from the trees */
id|mask
op_assign
l_int|0
suffix:semicolon
id|dirmask
op_assign
l_int|0
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|entry
(braket
id|i
)braket
dot
id|path
)paren
r_continue
suffix:semicolon
id|mask
op_or_assign
l_int|1ul
op_lshift
id|i
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|entry
(braket
id|i
)braket
dot
id|mode
)paren
)paren
id|dirmask
op_or_assign
l_int|1ul
op_lshift
id|i
suffix:semicolon
id|e
op_assign
op_amp
id|entry
(braket
id|i
)braket
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
id|interesting
op_assign
id|prune_traversal
c_func
(paren
id|e
comma
id|info
comma
op_amp
id|base
comma
id|interesting
)paren
suffix:semicolon
r_if
c_cond
(paren
id|interesting
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|interesting
)paren
(brace
id|ret
op_assign
id|info
op_member_access_from_pointer
id|fn
c_func
(paren
id|n
comma
id|mask
comma
id|dirmask
comma
id|entry
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|error
op_assign
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;show_all_errors
)paren
r_break
suffix:semicolon
)brace
id|mask
op_and_assign
id|ret
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
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
id|n
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|mask
op_amp
(paren
l_int|1ul
op_lshift
id|i
)paren
)paren
id|update_extended_entry
c_func
(paren
id|tx
op_plus
id|i
comma
id|entry
op_plus
id|i
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|entry
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
id|n
suffix:semicolon
id|i
op_increment
)paren
id|free_extended_entry
c_func
(paren
id|tx
op_plus
id|i
)paren
suffix:semicolon
id|free
c_func
(paren
id|tx
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|base
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|find_tree_entry
r_static
r_int
id|find_tree_entry
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
id|name
comma
r_int
r_char
op_star
id|result
comma
r_int
op_star
id|mode
)paren
(brace
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|t-&gt;size
)paren
(brace
r_const
r_char
op_star
id|entry
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|entrylen
comma
id|cmp
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
id|t
comma
op_amp
id|entry
comma
id|mode
)paren
suffix:semicolon
id|entrylen
op_assign
id|tree_entry_len
c_func
(paren
op_amp
id|t-&gt;entry
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entrylen
OG
id|namelen
)paren
r_continue
suffix:semicolon
id|cmp
op_assign
id|memcmp
c_func
(paren
id|name
comma
id|entry
comma
id|entrylen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|entrylen
op_eq
id|namelen
)paren
(brace
id|hashcpy
c_func
(paren
id|result
comma
id|sha1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name
(braket
id|entrylen
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
op_star
id|mode
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|entrylen
op_eq
id|namelen
)paren
(brace
id|hashcpy
c_func
(paren
id|result
comma
id|sha1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|get_tree_entry
c_func
(paren
id|sha1
comma
id|name
op_plus
id|entrylen
comma
id|result
comma
id|mode
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_tree_entry
r_int
id|get_tree_entry
c_func
(paren
r_const
r_int
r_char
op_star
id|tree_sha1
comma
r_const
r_char
op_star
id|name
comma
r_int
r_char
op_star
id|sha1
comma
r_int
op_star
id|mode
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
r_int
r_char
id|root
(braket
l_int|20
)braket
suffix:semicolon
id|tree
op_assign
id|read_object_with_reference
c_func
(paren
id|tree_sha1
comma
id|tree_type
comma
op_amp
id|size
comma
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|hashcpy
c_func
(paren
id|sha1
comma
id|root
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_struct
id|tree_desc
id|t
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t
comma
id|tree
comma
id|size
)paren
suffix:semicolon
id|retval
op_assign
id|find_tree_entry
c_func
(paren
op_amp
id|t
comma
id|name
comma
id|sha1
comma
id|mode
)paren
suffix:semicolon
)brace
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
DECL|function|match_entry
r_static
r_int
id|match_entry
c_func
(paren
r_const
r_struct
id|name_entry
op_star
id|entry
comma
r_int
id|pathlen
comma
r_const
r_char
op_star
id|match
comma
r_int
id|matchlen
comma
r_enum
id|interesting
op_star
id|never_interesting
)paren
(brace
r_int
id|m
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* signals that we haven&squot;t called strncmp() */
r_if
c_cond
(paren
op_star
id|never_interesting
op_ne
id|entry_not_interesting
)paren
(brace
multiline_comment|/*&n;&t;&t; * We have not seen any match that sorts later&n;&t;&t; * than the current path.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Does match sort strictly earlier than path&n;&t;&t; * with their common parts?&n;&t;&t; */
id|m
op_assign
id|strncmp
c_func
(paren
id|match
comma
id|entry-&gt;path
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we come here even once, that means there is at&n;&t;&t; * least one pathspec that would sort equal to or&n;&t;&t; * later than the path we are currently looking at.&n;&t;&t; * In other words, if we have never reached this point&n;&t;&t; * after iterating all pathspecs, it means all&n;&t;&t; * pathspecs are either outside of base, or inside the&n;&t;&t; * base but sorts strictly earlier than the current&n;&t;&t; * one.  In either case, they will never match the&n;&t;&t; * subsequent entries.  In such a case, we initialized&n;&t;&t; * the variable to -1 and that is what will be&n;&t;&t; * returned, allowing the caller to terminate early.&n;&t;&t; */
op_star
id|never_interesting
op_assign
id|entry_not_interesting
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pathlen
OG
id|matchlen
)paren
r_return
l_int|0
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
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry-&gt;mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|m
op_eq
l_int|1
)paren
multiline_comment|/*&n;&t;&t; * we cheated and did not do strncmp(), so we do&n;&t;&t; * that here.&n;&t;&t; */
id|m
op_assign
id|strncmp
c_func
(paren
id|match
comma
id|entry-&gt;path
comma
id|pathlen
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If common part matched earlier then it is a hit,&n;&t; * because we rejected the case where path is not a&n;&t; * leading directory and is shorter than match.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|match_dir_prefix
r_static
r_int
id|match_dir_prefix
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
id|match
comma
r_int
id|matchlen
)paren
(brace
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If the base is a subdirectory of a path which&n;&t; * was specified, all of them are interesting.&n;&t; */
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
l_int|1
suffix:semicolon
multiline_comment|/* Just a random prefix match */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform matching on the leading non-wildcard part of&n; * pathspec. item-&gt;nowildcard_len must be greater than zero. Return&n; * non-zero if base is matched.&n; */
DECL|function|match_wildcard_base
r_static
r_int
id|match_wildcard_base
c_func
(paren
r_const
r_struct
id|pathspec_item
op_star
id|item
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_int
op_star
id|matched
)paren
(brace
r_const
r_char
op_star
id|match
op_assign
id|item-&gt;match
suffix:semicolon
multiline_comment|/* the wildcard part is not considered in this function */
r_int
id|matchlen
op_assign
id|item-&gt;nowildcard_len
suffix:semicolon
r_if
c_cond
(paren
id|baselen
)paren
(brace
r_int
id|dirlen
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Return early if base is longer than the&n;&t;&t; * non-wildcard part but it does not match.&n;&t;&t; */
r_if
c_cond
(paren
id|baselen
op_ge
id|matchlen
)paren
(brace
op_star
id|matched
op_assign
id|matchlen
suffix:semicolon
r_return
op_logical_neg
id|strncmp
c_func
(paren
id|base
comma
id|match
comma
id|matchlen
)paren
suffix:semicolon
)brace
id|dirlen
op_assign
id|matchlen
suffix:semicolon
r_while
c_loop
(paren
id|dirlen
op_logical_and
id|match
(braket
id|dirlen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|dirlen
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Return early if base is shorter than the&n;&t;&t; * non-wildcard part but it does not match. Note that&n;&t;&t; * base ends with &squot;/&squot; so we are sure it really matches&n;&t;&t; * directory&n;&t;&t; */
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
r_return
l_int|0
suffix:semicolon
op_star
id|matched
op_assign
id|baselen
suffix:semicolon
)brace
r_else
op_star
id|matched
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * we could have checked entry against the non-wildcard part&n;&t; * that is not in base and does similar never_interesting&n;&t; * optimization as in match_entry. For now just be happy with&n;&t; * base comparison.&n;&t; */
r_return
id|entry_interesting
suffix:semicolon
)brace
multiline_comment|/*&n; * Is a tree entry interesting given the pathspec we have?&n; *&n; * Pre-condition: either baselen == base_offset (i.e. empty path)&n; * or base[baselen-1] == &squot;/&squot; (i.e. with trailing slash).&n; */
DECL|function|tree_entry_interesting
r_enum
id|interesting
id|tree_entry_interesting
c_func
(paren
r_const
r_struct
id|name_entry
op_star
id|entry
comma
r_struct
id|strbuf
op_star
id|base
comma
r_int
id|base_offset
comma
r_const
r_struct
id|pathspec
op_star
id|ps
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|pathlen
comma
id|baselen
op_assign
id|base-&gt;len
id|base_offset
suffix:semicolon
r_enum
id|interesting
id|never_interesting
op_assign
id|ps-&gt;has_wildcard
ques
c_cond
id|entry_not_interesting
suffix:colon
id|all_entries_not_interesting
suffix:semicolon
id|GUARD_PATHSPEC
c_func
(paren
id|ps
comma
id|PATHSPEC_FROMTOP
op_or
id|PATHSPEC_MAXDEPTH
op_or
id|PATHSPEC_LITERAL
op_or
id|PATHSPEC_GLOB
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ps-&gt;nr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ps-&gt;recursive
op_logical_or
op_logical_neg
(paren
id|ps-&gt;magic
op_amp
id|PATHSPEC_MAXDEPTH
)paren
op_logical_or
id|ps-&gt;max_depth
op_eq
l_int|1
)paren
r_return
id|all_entries_interesting
suffix:semicolon
r_return
id|within_depth
c_func
(paren
id|base-&gt;buf
op_plus
id|base_offset
comma
id|baselen
comma
op_logical_neg
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry-&gt;mode
)paren
comma
id|ps-&gt;max_depth
)paren
ques
c_cond
id|entry_interesting
suffix:colon
id|entry_not_interesting
suffix:semicolon
)brace
id|pathlen
op_assign
id|tree_entry_len
c_func
(paren
id|entry
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ps-&gt;nr
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_const
r_struct
id|pathspec_item
op_star
id|item
op_assign
id|ps-&gt;items
op_plus
id|i
suffix:semicolon
r_const
r_char
op_star
id|match
op_assign
id|item-&gt;match
suffix:semicolon
r_const
r_char
op_star
id|base_str
op_assign
id|base-&gt;buf
op_plus
id|base_offset
suffix:semicolon
r_int
id|matchlen
op_assign
id|item-&gt;len
comma
id|matched
op_assign
l_int|0
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
op_logical_neg
id|match_dir_prefix
c_func
(paren
id|base_str
comma
id|match
comma
id|matchlen
)paren
)paren
r_goto
id|match_wildcards
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ps-&gt;recursive
op_logical_or
op_logical_neg
(paren
id|ps-&gt;magic
op_amp
id|PATHSPEC_MAXDEPTH
)paren
op_logical_or
id|ps-&gt;max_depth
op_eq
l_int|1
)paren
r_return
id|all_entries_interesting
suffix:semicolon
r_return
id|within_depth
c_func
(paren
id|base_str
op_plus
id|matchlen
op_plus
l_int|1
comma
id|baselen
id|matchlen
l_int|1
comma
op_logical_neg
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry-&gt;mode
)paren
comma
id|ps-&gt;max_depth
)paren
ques
c_cond
id|entry_interesting
suffix:colon
id|entry_not_interesting
suffix:semicolon
)brace
multiline_comment|/* Either there must be no base, or the base must match. */
r_if
c_cond
(paren
id|baselen
op_eq
l_int|0
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|base_str
comma
id|match
comma
id|baselen
)paren
)paren
(brace
r_if
c_cond
(paren
id|match_entry
c_func
(paren
id|entry
comma
id|pathlen
comma
id|match
op_plus
id|baselen
comma
id|matchlen
id|baselen
comma
op_amp
id|never_interesting
)paren
)paren
r_return
id|entry_interesting
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;nowildcard_len
OL
id|item-&gt;len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_fnmatch
c_func
(paren
id|item
comma
id|match
op_plus
id|baselen
comma
id|entry-&gt;path
comma
id|item-&gt;nowildcard_len
id|baselen
)paren
)paren
r_return
id|entry_interesting
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Match all directories. We&squot;ll try to&n;&t;&t;&t;&t; * match files later on.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|ps-&gt;recursive
op_logical_and
id|S_ISDIR
c_func
(paren
id|entry-&gt;mode
)paren
)paren
r_return
id|entry_interesting
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|match_wildcards
suffix:colon
r_if
c_cond
(paren
id|item-&gt;nowildcard_len
op_eq
id|item-&gt;len
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;nowildcard_len
op_logical_and
op_logical_neg
id|match_wildcard_base
c_func
(paren
id|item
comma
id|base_str
comma
id|baselen
comma
op_amp
id|matched
)paren
)paren
r_return
id|entry_not_interesting
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Concatenate base and entry-&gt;path into one and do&n;&t;&t; * fnmatch() on it.&n;&t;&t; *&n;&t;&t; * While we could avoid concatenation in certain cases&n;&t;&t; * [1], which saves a memcpy and potentially a&n;&t;&t; * realloc, it turns out not worth it. Measurement on&n;&t;&t; * linux-2.6 does not show any clear improvements,&n;&t;&t; * partly because of the nowildcard_len optimization&n;&t;&t; * in git_fnmatch(). Avoid micro-optimizations here.&n;&t;&t; *&n;&t;&t; * [1] if match_wildcard_base() says the base&n;&t;&t; * directory is already matched, we only need to match&n;&t;&t; * the rest, which is shorter so _in theory_ faster.&n;&t;&t; */
id|strbuf_add
c_func
(paren
id|base
comma
id|entry-&gt;path
comma
id|pathlen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_fnmatch
c_func
(paren
id|item
comma
id|match
comma
id|base-&gt;buf
op_plus
id|base_offset
comma
id|item-&gt;nowildcard_len
)paren
)paren
(brace
id|strbuf_setlen
c_func
(paren
id|base
comma
id|base_offset
op_plus
id|baselen
)paren
suffix:semicolon
r_return
id|entry_interesting
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|base
comma
id|base_offset
op_plus
id|baselen
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Match all directories. We&squot;ll try to match files&n;&t;&t; * later on.&n;&t;&t; * max_depth is ignored but we may consider support it&n;&t;&t; * in future, see&n;&t;&t; * http://thread.gmane.org/gmane.comp.version-control.git/163757/focus=163840&n;&t;&t; */
r_if
c_cond
(paren
id|ps-&gt;recursive
op_logical_and
id|S_ISDIR
c_func
(paren
id|entry-&gt;mode
)paren
)paren
r_return
id|entry_interesting
suffix:semicolon
)brace
r_return
id|never_interesting
suffix:semicolon
multiline_comment|/* No matches */
)brace
eof
