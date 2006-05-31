macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;tree.h&quot;
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
id|desc-&gt;buf
suffix:semicolon
r_int
r_int
id|size
op_assign
id|desc-&gt;size
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
id|desc-&gt;buf
op_assign
id|buf
op_plus
id|len
suffix:semicolon
id|desc-&gt;size
op_assign
id|size
id|len
suffix:semicolon
)brace
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
DECL|function|tree_entry_extract
r_const
r_int
r_char
op_star
id|tree_entry_extract
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
op_star
id|pathp
comma
r_int
r_int
op_star
id|modep
)paren
(brace
r_const
r_void
op_star
id|tree
op_assign
id|desc-&gt;buf
suffix:semicolon
r_int
r_int
id|size
op_assign
id|desc-&gt;size
suffix:semicolon
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
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
id|path
op_assign
id|get_mode
c_func
(paren
id|tree
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
id|size
OL
id|len
op_plus
l_int|20
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
suffix:semicolon
op_star
id|modep
op_assign
id|canon_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
r_return
id|sha1
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
r_const
r_void
op_star
id|tree
op_assign
id|desc-&gt;buf
comma
op_star
id|path
suffix:semicolon
r_int
r_int
id|len
comma
id|size
op_assign
id|desc-&gt;size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|path
op_assign
id|get_mode
c_func
(paren
id|tree
comma
op_amp
id|entry-&gt;mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file&quot;
)paren
suffix:semicolon
id|entry-&gt;path
op_assign
id|path
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|entry-&gt;pathlen
op_assign
id|len
suffix:semicolon
id|path
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
id|entry-&gt;sha1
op_assign
id|path
suffix:semicolon
id|path
op_add_assign
l_int|20
suffix:semicolon
id|len
op_assign
id|path
id|tree
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|size
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file&quot;
)paren
suffix:semicolon
id|desc-&gt;buf
op_assign
id|path
suffix:semicolon
id|desc-&gt;size
op_assign
id|size
id|len
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|traverse_trees
r_void
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
r_const
r_char
op_star
id|base
comma
id|traverse_callback_t
id|callback
)paren
(brace
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
l_int|1ul
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
id|n
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
l_int|1ul
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
id|callback
c_func
(paren
id|n
comma
id|mask
comma
id|entry
comma
id|base
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|entry
)paren
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
id|update_tree_entry
c_func
(paren
id|t
)paren
suffix:semicolon
id|entrylen
op_assign
id|strlen
c_func
(paren
id|entry
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
id|memcpy
c_func
(paren
id|result
comma
id|sha1
comma
l_int|20
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
id|memcpy
c_func
(paren
id|result
comma
id|sha1
comma
l_int|20
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
r_struct
id|tree_desc
id|t
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
id|t.size
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
r_return
l_int|1
suffix:semicolon
id|t.buf
op_assign
id|tree
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
eof
