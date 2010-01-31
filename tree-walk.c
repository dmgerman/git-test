macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;tree.h&quot;
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
id|df_name_compare
c_func
(paren
id|a-&gt;path
comma
id|tree_entry_len
c_func
(paren
id|a-&gt;path
comma
id|a-&gt;sha1
)paren
comma
id|a-&gt;mode
comma
id|b-&gt;path
comma
id|tree_entry_len
c_func
(paren
id|b-&gt;path
comma
id|b-&gt;sha1
)paren
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
id|n-&gt;path
comma
id|n-&gt;sha1
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
id|n-&gt;path
comma
id|n-&gt;sha1
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
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|dirmask
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
id|dirmask
op_and_assign
id|mask
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Clear all the unused name-entries.&n;&t;&t; */
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
r_continue
suffix:semicolon
id|entry_clear
c_func
(paren
id|entry
op_plus
id|i
)paren
suffix:semicolon
)brace
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
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|mask
op_and_assign
id|ret
suffix:semicolon
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
id|update_tree_entry
c_func
(paren
id|t
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
id|ret
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
id|tree_entry_len
c_func
(paren
id|entry
comma
id|sha1
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
r_struct
id|tree_desc
id|t
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
r_return
l_int|0
suffix:semicolon
)brace
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
