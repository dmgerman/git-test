multiline_comment|/*&n;*&n;* Copyright 2005, Lukas Sandstrom &lt;lukass@etek.chalmers.se&gt;&n;*&n;* This file is licensed under the GPL v2.&n;*&n;*/
macro_line|#include &quot;builtin.h&quot;
DECL|macro|BLKSIZE
mdefine_line|#define BLKSIZE 512
DECL|variable|pack_redundant_usage
r_static
r_const
r_char
id|pack_redundant_usage
(braket
)braket
op_assign
l_string|&quot;git pack-redundant [--verbose] [--alt-odb] (--all | &lt;filename.pack&gt;...)&quot;
suffix:semicolon
DECL|variable|load_all_packs
DECL|variable|verbose
DECL|variable|alt_odb
r_static
r_int
id|load_all_packs
comma
id|verbose
comma
id|alt_odb
suffix:semicolon
DECL|struct|llist_item
r_struct
id|llist_item
(brace
DECL|member|next
r_struct
id|llist_item
op_star
id|next
suffix:semicolon
DECL|member|sha1
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|llist
r_static
r_struct
id|llist
(brace
DECL|member|front
r_struct
id|llist_item
op_star
id|front
suffix:semicolon
DECL|member|back
r_struct
id|llist_item
op_star
id|back
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|variable|all_objects
)brace
op_star
id|all_objects
suffix:semicolon
multiline_comment|/* all objects which must be present in local packfiles */
DECL|struct|pack_list
r_static
r_struct
id|pack_list
(brace
DECL|member|next
r_struct
id|pack_list
op_star
id|next
suffix:semicolon
DECL|member|pack
r_struct
id|packed_git
op_star
id|pack
suffix:semicolon
DECL|member|unique_objects
r_struct
id|llist
op_star
id|unique_objects
suffix:semicolon
DECL|member|all_objects
r_struct
id|llist
op_star
id|all_objects
suffix:semicolon
DECL|variable|local_packs
DECL|variable|altodb_packs
)brace
op_star
id|local_packs
op_assign
l_int|NULL
comma
op_star
id|altodb_packs
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|pll
r_struct
id|pll
(brace
DECL|member|next
r_struct
id|pll
op_star
id|next
suffix:semicolon
DECL|member|pl
r_struct
id|pack_list
op_star
id|pl
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|free_nodes
r_static
r_struct
id|llist_item
op_star
id|free_nodes
suffix:semicolon
DECL|function|llist_item_put
r_static
r_inline
r_void
id|llist_item_put
c_func
(paren
r_struct
id|llist_item
op_star
id|item
)paren
(brace
id|item-&gt;next
op_assign
id|free_nodes
suffix:semicolon
id|free_nodes
op_assign
id|item
suffix:semicolon
)brace
DECL|function|llist_item_get
r_static
r_inline
r_struct
id|llist_item
op_star
id|llist_item_get
c_func
(paren
r_void
)paren
(brace
r_struct
id|llist_item
op_star
r_new
suffix:semicolon
r_if
c_cond
(paren
id|free_nodes
)paren
(brace
r_new
op_assign
id|free_nodes
suffix:semicolon
id|free_nodes
op_assign
id|free_nodes-&gt;next
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_new
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|llist_item
)paren
op_star
id|BLKSIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|BLKSIZE
suffix:semicolon
id|i
op_increment
)paren
id|llist_item_put
c_func
(paren
op_amp
r_new
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
r_new
suffix:semicolon
)brace
DECL|function|llist_free
r_static
r_void
id|llist_free
c_func
(paren
r_struct
id|llist
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
(paren
id|list-&gt;back
op_assign
id|list-&gt;front
)paren
)paren
(brace
id|list-&gt;front
op_assign
id|list-&gt;front-&gt;next
suffix:semicolon
id|llist_item_put
c_func
(paren
id|list-&gt;back
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
DECL|function|llist_init
r_static
r_inline
r_void
id|llist_init
c_func
(paren
r_struct
id|llist
op_star
op_star
id|list
)paren
(brace
op_star
id|list
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|llist
)paren
)paren
suffix:semicolon
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|front
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|back
op_assign
l_int|NULL
suffix:semicolon
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|size
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|llist_copy
r_static
r_struct
id|llist
op_star
id|llist_copy
c_func
(paren
r_struct
id|llist
op_star
id|list
)paren
(brace
r_struct
id|llist
op_star
id|ret
suffix:semicolon
r_struct
id|llist_item
op_star
r_new
comma
op_star
id|old
comma
op_star
id|prev
suffix:semicolon
id|llist_init
c_func
(paren
op_amp
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret-&gt;size
op_assign
id|list-&gt;size
)paren
op_eq
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_new
op_assign
id|ret-&gt;front
op_assign
id|llist_item_get
c_func
(paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|sha1
op_assign
id|list-&gt;front-&gt;sha1
suffix:semicolon
id|old
op_assign
id|list-&gt;front-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|old
)paren
(brace
id|prev
op_assign
r_new
suffix:semicolon
r_new
op_assign
id|llist_item_get
c_func
(paren
)paren
suffix:semicolon
id|prev-&gt;next
op_assign
r_new
suffix:semicolon
r_new
op_member_access_from_pointer
id|sha1
op_assign
id|old-&gt;sha1
suffix:semicolon
id|old
op_assign
id|old-&gt;next
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
id|ret-&gt;back
op_assign
r_new
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|llist_insert
r_static
r_inline
r_struct
id|llist_item
op_star
id|llist_insert
c_func
(paren
r_struct
id|llist
op_star
id|list
comma
r_struct
id|llist_item
op_star
id|after
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|llist_item
op_star
r_new
op_assign
id|llist_item_get
c_func
(paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|sha1
op_assign
id|sha1
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|after
op_ne
l_int|NULL
)paren
(brace
r_new
op_member_access_from_pointer
id|next
op_assign
id|after-&gt;next
suffix:semicolon
id|after-&gt;next
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
id|after
op_eq
id|list-&gt;back
)paren
id|list-&gt;back
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* insert in front */
r_if
c_cond
(paren
id|list-&gt;size
op_eq
l_int|0
)paren
id|list-&gt;back
op_assign
r_new
suffix:semicolon
r_else
r_new
op_member_access_from_pointer
id|next
op_assign
id|list-&gt;front
suffix:semicolon
id|list-&gt;front
op_assign
r_new
suffix:semicolon
)brace
id|list-&gt;size
op_increment
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
DECL|function|llist_insert_back
r_static
r_inline
r_struct
id|llist_item
op_star
id|llist_insert_back
c_func
(paren
r_struct
id|llist
op_star
id|list
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_return
id|llist_insert
c_func
(paren
id|list
comma
id|list-&gt;back
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|llist_insert_sorted_unique
r_static
r_inline
r_struct
id|llist_item
op_star
id|llist_insert_sorted_unique
c_func
(paren
r_struct
id|llist
op_star
id|list
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|llist_item
op_star
id|hint
)paren
(brace
r_struct
id|llist_item
op_star
id|prev
op_assign
l_int|NULL
comma
op_star
id|l
suffix:semicolon
id|l
op_assign
(paren
id|hint
op_eq
l_int|NULL
)paren
ques
c_cond
id|list-&gt;front
suffix:colon
id|hint
suffix:semicolon
r_while
c_loop
(paren
id|l
)paren
(brace
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|l-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
multiline_comment|/* we insert before this entry */
r_return
id|llist_insert
c_func
(paren
id|list
comma
id|prev
comma
id|sha1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
(brace
multiline_comment|/* already exists */
r_return
id|l
suffix:semicolon
)brace
id|prev
op_assign
id|l
suffix:semicolon
id|l
op_assign
id|l-&gt;next
suffix:semicolon
)brace
multiline_comment|/* insert at the end */
r_return
id|llist_insert_back
c_func
(paren
id|list
comma
id|sha1
)paren
suffix:semicolon
)brace
multiline_comment|/* returns a pointer to an item in front of sha1 */
DECL|function|llist_sorted_remove
r_static
r_inline
r_struct
id|llist_item
op_star
id|llist_sorted_remove
c_func
(paren
r_struct
id|llist
op_star
id|list
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|llist_item
op_star
id|hint
)paren
(brace
r_struct
id|llist_item
op_star
id|prev
comma
op_star
id|l
suffix:semicolon
id|redo_from_start
suffix:colon
id|l
op_assign
(paren
id|hint
op_eq
l_int|NULL
)paren
ques
c_cond
id|list-&gt;front
suffix:colon
id|hint
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|l
)paren
(brace
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|l-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
multiline_comment|/* not in list, since sorted */
r_return
id|prev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
(brace
multiline_comment|/* found */
r_if
c_cond
(paren
id|prev
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|hint
op_ne
l_int|NULL
op_logical_and
id|hint
op_ne
id|list-&gt;front
)paren
(brace
multiline_comment|/* we don&squot;t know the previous element */
id|hint
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|redo_from_start
suffix:semicolon
)brace
id|list-&gt;front
op_assign
id|l-&gt;next
suffix:semicolon
)brace
r_else
id|prev-&gt;next
op_assign
id|l-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|l
op_eq
id|list-&gt;back
)paren
id|list-&gt;back
op_assign
id|prev
suffix:semicolon
id|llist_item_put
c_func
(paren
id|l
)paren
suffix:semicolon
id|list-&gt;size
op_decrement
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
id|prev
op_assign
id|l
suffix:semicolon
id|l
op_assign
id|l-&gt;next
suffix:semicolon
)brace
r_return
id|prev
suffix:semicolon
)brace
multiline_comment|/* computes A&bslash;B */
DECL|function|llist_sorted_difference_inplace
r_static
r_void
id|llist_sorted_difference_inplace
c_func
(paren
r_struct
id|llist
op_star
id|A
comma
r_struct
id|llist
op_star
id|B
)paren
(brace
r_struct
id|llist_item
op_star
id|hint
comma
op_star
id|b
suffix:semicolon
id|hint
op_assign
l_int|NULL
suffix:semicolon
id|b
op_assign
id|B-&gt;front
suffix:semicolon
r_while
c_loop
(paren
id|b
)paren
(brace
id|hint
op_assign
id|llist_sorted_remove
c_func
(paren
id|A
comma
id|b-&gt;sha1
comma
id|hint
)paren
suffix:semicolon
id|b
op_assign
id|b-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|pack_list_insert
r_static
r_inline
r_struct
id|pack_list
op_star
id|pack_list_insert
c_func
(paren
r_struct
id|pack_list
op_star
op_star
id|pl
comma
r_struct
id|pack_list
op_star
id|entry
)paren
(brace
r_struct
id|pack_list
op_star
id|p
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pack_list
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|entry
comma
r_sizeof
(paren
r_struct
id|pack_list
)paren
)paren
suffix:semicolon
id|p-&gt;next
op_assign
op_star
id|pl
suffix:semicolon
op_star
id|pl
op_assign
id|p
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|pack_list_size
r_static
r_inline
r_int
id|pack_list_size
c_func
(paren
r_struct
id|pack_list
op_star
id|pl
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|ret
op_increment
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pack_list_difference
r_static
r_struct
id|pack_list
op_star
id|pack_list_difference
c_func
(paren
r_const
r_struct
id|pack_list
op_star
id|A
comma
r_const
r_struct
id|pack_list
op_star
id|B
)paren
(brace
r_struct
id|pack_list
op_star
id|ret
suffix:semicolon
r_const
r_struct
id|pack_list
op_star
id|pl
suffix:semicolon
r_if
c_cond
(paren
id|A
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|pl
op_assign
id|B
suffix:semicolon
r_while
c_loop
(paren
id|pl
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|A-&gt;pack
op_eq
id|pl-&gt;pack
)paren
r_return
id|pack_list_difference
c_func
(paren
id|A-&gt;next
comma
id|B
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
id|ret
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pack_list
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ret
comma
id|A
comma
r_sizeof
(paren
r_struct
id|pack_list
)paren
)paren
suffix:semicolon
id|ret-&gt;next
op_assign
id|pack_list_difference
c_func
(paren
id|A-&gt;next
comma
id|B
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cmp_two_packs
r_static
r_void
id|cmp_two_packs
c_func
(paren
r_struct
id|pack_list
op_star
id|p1
comma
r_struct
id|pack_list
op_star
id|p2
)paren
(brace
r_int
r_int
id|p1_off
op_assign
l_int|0
comma
id|p2_off
op_assign
l_int|0
comma
id|p1_step
comma
id|p2_step
suffix:semicolon
r_const
r_int
r_char
op_star
id|p1_base
comma
op_star
id|p2_base
suffix:semicolon
r_struct
id|llist_item
op_star
id|p1_hint
op_assign
l_int|NULL
comma
op_star
id|p2_hint
op_assign
l_int|NULL
suffix:semicolon
id|p1_base
op_assign
id|p1-&gt;pack-&gt;index_data
suffix:semicolon
id|p2_base
op_assign
id|p2-&gt;pack-&gt;index_data
suffix:semicolon
id|p1_base
op_add_assign
l_int|256
op_star
l_int|4
op_plus
(paren
(paren
id|p1-&gt;pack-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|8
)paren
suffix:semicolon
id|p2_base
op_add_assign
l_int|256
op_star
l_int|4
op_plus
(paren
(paren
id|p2-&gt;pack-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|8
)paren
suffix:semicolon
id|p1_step
op_assign
(paren
id|p1-&gt;pack-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|20
suffix:semicolon
id|p2_step
op_assign
(paren
id|p2-&gt;pack-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|20
suffix:semicolon
r_while
c_loop
(paren
id|p1_off
OL
id|p1-&gt;pack-&gt;num_objects
op_star
id|p1_step
op_logical_and
id|p2_off
OL
id|p2-&gt;pack-&gt;num_objects
op_star
id|p2_step
)paren
(brace
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|p1_base
op_plus
id|p1_off
comma
id|p2_base
op_plus
id|p2_off
)paren
suffix:semicolon
multiline_comment|/* cmp ~ p1 - p2 */
r_if
c_cond
(paren
id|cmp
op_eq
l_int|0
)paren
(brace
id|p1_hint
op_assign
id|llist_sorted_remove
c_func
(paren
id|p1-&gt;unique_objects
comma
id|p1_base
op_plus
id|p1_off
comma
id|p1_hint
)paren
suffix:semicolon
id|p2_hint
op_assign
id|llist_sorted_remove
c_func
(paren
id|p2-&gt;unique_objects
comma
id|p1_base
op_plus
id|p1_off
comma
id|p2_hint
)paren
suffix:semicolon
id|p1_off
op_add_assign
id|p1_step
suffix:semicolon
id|p2_off
op_add_assign
id|p2_step
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
multiline_comment|/* p1 has the object, p2 doesn&squot;t */
id|p1_off
op_add_assign
id|p1_step
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* p2 has the object, p1 doesn&squot;t */
id|p2_off
op_add_assign
id|p2_step
suffix:semicolon
)brace
)brace
)brace
DECL|function|pll_free
r_static
r_void
id|pll_free
c_func
(paren
r_struct
id|pll
op_star
id|l
)paren
(brace
r_struct
id|pll
op_star
id|old
suffix:semicolon
r_struct
id|pack_list
op_star
id|opl
suffix:semicolon
r_while
c_loop
(paren
id|l
)paren
(brace
id|old
op_assign
id|l
suffix:semicolon
r_while
c_loop
(paren
id|l-&gt;pl
)paren
(brace
id|opl
op_assign
id|l-&gt;pl
suffix:semicolon
id|l-&gt;pl
op_assign
id|opl-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|opl
)paren
suffix:semicolon
)brace
id|l
op_assign
id|l-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* all the permutations have to be free()d at the same time,&n; * since they refer to each other&n; */
DECL|function|get_permutations
r_static
r_struct
id|pll
op_star
id|get_permutations
c_func
(paren
r_struct
id|pack_list
op_star
id|list
comma
r_int
id|n
)paren
(brace
r_struct
id|pll
op_star
id|subset
comma
op_star
id|ret
op_assign
l_int|NULL
comma
op_star
id|new_pll
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|list
op_eq
l_int|NULL
op_logical_or
id|pack_list_size
c_func
(paren
id|list
)paren
OL
id|n
op_logical_or
id|n
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|1
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
id|new_pll
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|new_pll
)paren
)paren
suffix:semicolon
id|new_pll-&gt;pl
op_assign
l_int|NULL
suffix:semicolon
id|pack_list_insert
c_func
(paren
op_amp
id|new_pll-&gt;pl
comma
id|list
)paren
suffix:semicolon
id|new_pll-&gt;next
op_assign
id|ret
suffix:semicolon
id|ret
op_assign
id|new_pll
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_while
c_loop
(paren
id|list-&gt;next
)paren
(brace
id|subset
op_assign
id|get_permutations
c_func
(paren
id|list-&gt;next
comma
id|n
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|subset
)paren
(brace
id|new_pll
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|new_pll
)paren
)paren
suffix:semicolon
id|new_pll-&gt;pl
op_assign
id|subset-&gt;pl
suffix:semicolon
id|pack_list_insert
c_func
(paren
op_amp
id|new_pll-&gt;pl
comma
id|list
)paren
suffix:semicolon
id|new_pll-&gt;next
op_assign
id|ret
suffix:semicolon
id|ret
op_assign
id|new_pll
suffix:semicolon
id|subset
op_assign
id|subset-&gt;next
suffix:semicolon
)brace
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|is_superset
r_static
r_int
id|is_superset
c_func
(paren
r_struct
id|pack_list
op_star
id|pl
comma
r_struct
id|llist
op_star
id|list
)paren
(brace
r_struct
id|llist
op_star
id|diff
suffix:semicolon
id|diff
op_assign
id|llist_copy
c_func
(paren
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|llist_sorted_difference_inplace
c_func
(paren
id|diff
comma
id|pl-&gt;all_objects
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff-&gt;size
op_eq
l_int|0
)paren
(brace
multiline_comment|/* we&squot;re done */
id|llist_free
c_func
(paren
id|diff
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
id|llist_free
c_func
(paren
id|diff
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sizeof_union
r_static
r_int
id|sizeof_union
c_func
(paren
r_struct
id|packed_git
op_star
id|p1
comma
r_struct
id|packed_git
op_star
id|p2
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|p1_off
op_assign
l_int|0
comma
id|p2_off
op_assign
l_int|0
comma
id|p1_step
comma
id|p2_step
suffix:semicolon
r_const
r_int
r_char
op_star
id|p1_base
comma
op_star
id|p2_base
suffix:semicolon
id|p1_base
op_assign
id|p1-&gt;index_data
suffix:semicolon
id|p2_base
op_assign
id|p2-&gt;index_data
suffix:semicolon
id|p1_base
op_add_assign
l_int|256
op_star
l_int|4
op_plus
(paren
(paren
id|p1-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|8
)paren
suffix:semicolon
id|p2_base
op_add_assign
l_int|256
op_star
l_int|4
op_plus
(paren
(paren
id|p2-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|8
)paren
suffix:semicolon
id|p1_step
op_assign
(paren
id|p1-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|20
suffix:semicolon
id|p2_step
op_assign
(paren
id|p2-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|20
suffix:semicolon
r_while
c_loop
(paren
id|p1_off
OL
id|p1-&gt;num_objects
op_star
id|p1_step
op_logical_and
id|p2_off
OL
id|p2-&gt;num_objects
op_star
id|p2_step
)paren
(brace
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|p1_base
op_plus
id|p1_off
comma
id|p2_base
op_plus
id|p2_off
)paren
suffix:semicolon
multiline_comment|/* cmp ~ p1 - p2 */
r_if
c_cond
(paren
id|cmp
op_eq
l_int|0
)paren
(brace
id|ret
op_increment
suffix:semicolon
id|p1_off
op_add_assign
id|p1_step
suffix:semicolon
id|p2_off
op_add_assign
id|p2_step
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
multiline_comment|/* p1 has the object, p2 doesn&squot;t */
id|p1_off
op_add_assign
id|p1_step
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* p2 has the object, p1 doesn&squot;t */
id|p2_off
op_add_assign
id|p2_step
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* another O(n^2) function ... */
DECL|function|get_pack_redundancy
r_static
r_int
id|get_pack_redundancy
c_func
(paren
r_struct
id|pack_list
op_star
id|pl
)paren
(brace
r_struct
id|pack_list
op_star
id|subset
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pl
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|subset
op_assign
id|pl-&gt;next
)paren
)paren
(brace
r_while
c_loop
(paren
id|subset
)paren
(brace
id|ret
op_add_assign
id|sizeof_union
c_func
(paren
id|pl-&gt;pack
comma
id|subset-&gt;pack
)paren
suffix:semicolon
id|subset
op_assign
id|subset-&gt;next
suffix:semicolon
)brace
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pack_set_bytecount
r_static
r_inline
id|off_t
id|pack_set_bytecount
c_func
(paren
r_struct
id|pack_list
op_star
id|pl
)paren
(brace
id|off_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|ret
op_add_assign
id|pl-&gt;pack-&gt;pack_size
suffix:semicolon
id|ret
op_add_assign
id|pl-&gt;pack-&gt;index_size
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|minimize
r_static
r_void
id|minimize
c_func
(paren
r_struct
id|pack_list
op_star
op_star
id|min
)paren
(brace
r_struct
id|pack_list
op_star
id|pl
comma
op_star
id|unique
op_assign
l_int|NULL
comma
op_star
id|non_unique
op_assign
l_int|NULL
comma
op_star
id|min_perm
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pll
op_star
id|perm
comma
op_star
id|perm_all
comma
op_star
id|perm_ok
op_assign
l_int|NULL
comma
op_star
id|new_perm
suffix:semicolon
r_struct
id|llist
op_star
id|missing
suffix:semicolon
id|off_t
id|min_perm_size
op_assign
l_int|0
comma
id|perm_size
suffix:semicolon
r_int
id|n
suffix:semicolon
id|pl
op_assign
id|local_packs
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
r_if
c_cond
(paren
id|pl-&gt;unique_objects-&gt;size
)paren
id|pack_list_insert
c_func
(paren
op_amp
id|unique
comma
id|pl
)paren
suffix:semicolon
r_else
id|pack_list_insert
c_func
(paren
op_amp
id|non_unique
comma
id|pl
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
multiline_comment|/* find out which objects are missing from the set of unique packs */
id|missing
op_assign
id|llist_copy
c_func
(paren
id|all_objects
)paren
suffix:semicolon
id|pl
op_assign
id|unique
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|llist_sorted_difference_inplace
c_func
(paren
id|missing
comma
id|pl-&gt;all_objects
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
multiline_comment|/* return if there are no objects missing from the unique set */
r_if
c_cond
(paren
id|missing-&gt;size
op_eq
l_int|0
)paren
(brace
op_star
id|min
op_assign
id|unique
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* find the permutations which contain all missing objects */
r_for
c_loop
(paren
id|n
op_assign
l_int|1
suffix:semicolon
id|n
op_le
id|pack_list_size
c_func
(paren
id|non_unique
)paren
op_logical_and
op_logical_neg
id|perm_ok
suffix:semicolon
id|n
op_increment
)paren
(brace
id|perm_all
op_assign
id|perm
op_assign
id|get_permutations
c_func
(paren
id|non_unique
comma
id|n
)paren
suffix:semicolon
r_while
c_loop
(paren
id|perm
)paren
(brace
r_if
c_cond
(paren
id|is_superset
c_func
(paren
id|perm-&gt;pl
comma
id|missing
)paren
)paren
(brace
id|new_perm
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pll
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|new_perm
comma
id|perm
comma
r_sizeof
(paren
r_struct
id|pll
)paren
)paren
suffix:semicolon
id|new_perm-&gt;next
op_assign
id|perm_ok
suffix:semicolon
id|perm_ok
op_assign
id|new_perm
suffix:semicolon
)brace
id|perm
op_assign
id|perm-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|perm_ok
)paren
r_break
suffix:semicolon
id|pll_free
c_func
(paren
id|perm_all
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|perm_ok
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;Internal error: No complete sets found!&quot;
)paren
suffix:semicolon
multiline_comment|/* find the permutation with the smallest size */
id|perm
op_assign
id|perm_ok
suffix:semicolon
r_while
c_loop
(paren
id|perm
)paren
(brace
id|perm_size
op_assign
id|pack_set_bytecount
c_func
(paren
id|perm-&gt;pl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|min_perm_size
op_logical_or
id|min_perm_size
OG
id|perm_size
)paren
(brace
id|min_perm_size
op_assign
id|perm_size
suffix:semicolon
id|min_perm
op_assign
id|perm-&gt;pl
suffix:semicolon
)brace
id|perm
op_assign
id|perm-&gt;next
suffix:semicolon
)brace
op_star
id|min
op_assign
id|min_perm
suffix:semicolon
multiline_comment|/* add the unique packs to the list */
id|pl
op_assign
id|unique
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|pack_list_insert
c_func
(paren
id|min
comma
id|pl
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|load_all_objects
r_static
r_void
id|load_all_objects
c_func
(paren
r_void
)paren
(brace
r_struct
id|pack_list
op_star
id|pl
op_assign
id|local_packs
suffix:semicolon
r_struct
id|llist_item
op_star
id|hint
comma
op_star
id|l
suffix:semicolon
id|llist_init
c_func
(paren
op_amp
id|all_objects
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|hint
op_assign
l_int|NULL
suffix:semicolon
id|l
op_assign
id|pl-&gt;all_objects-&gt;front
suffix:semicolon
r_while
c_loop
(paren
id|l
)paren
(brace
id|hint
op_assign
id|llist_insert_sorted_unique
c_func
(paren
id|all_objects
comma
id|l-&gt;sha1
comma
id|hint
)paren
suffix:semicolon
id|l
op_assign
id|l-&gt;next
suffix:semicolon
)brace
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
multiline_comment|/* remove objects present in remote packs */
id|pl
op_assign
id|altodb_packs
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|llist_sorted_difference_inplace
c_func
(paren
id|all_objects
comma
id|pl-&gt;all_objects
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/* this scales like O(n^2) */
DECL|function|cmp_local_packs
r_static
r_void
id|cmp_local_packs
c_func
(paren
r_void
)paren
(brace
r_struct
id|pack_list
op_star
id|subset
comma
op_star
id|pl
op_assign
id|local_packs
suffix:semicolon
r_while
c_loop
(paren
(paren
id|subset
op_assign
id|pl
)paren
)paren
(brace
r_while
c_loop
(paren
(paren
id|subset
op_assign
id|subset-&gt;next
)paren
)paren
id|cmp_two_packs
c_func
(paren
id|pl
comma
id|subset
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|scan_alt_odb_packs
r_static
r_void
id|scan_alt_odb_packs
c_func
(paren
r_void
)paren
(brace
r_struct
id|pack_list
op_star
id|local
comma
op_star
id|alt
suffix:semicolon
id|alt
op_assign
id|altodb_packs
suffix:semicolon
r_while
c_loop
(paren
id|alt
)paren
(brace
id|local
op_assign
id|local_packs
suffix:semicolon
r_while
c_loop
(paren
id|local
)paren
(brace
id|llist_sorted_difference_inplace
c_func
(paren
id|local-&gt;unique_objects
comma
id|alt-&gt;all_objects
)paren
suffix:semicolon
id|local
op_assign
id|local-&gt;next
suffix:semicolon
)brace
id|llist_sorted_difference_inplace
c_func
(paren
id|all_objects
comma
id|alt-&gt;all_objects
)paren
suffix:semicolon
id|alt
op_assign
id|alt-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|add_pack
r_static
r_struct
id|pack_list
op_star
id|add_pack
c_func
(paren
r_struct
id|packed_git
op_star
id|p
)paren
(brace
r_struct
id|pack_list
id|l
suffix:semicolon
r_int
r_int
id|off
op_assign
l_int|0
comma
id|step
suffix:semicolon
r_const
r_int
r_char
op_star
id|base
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;pack_local
op_logical_and
op_logical_neg
(paren
id|alt_odb
op_logical_or
id|verbose
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|l.pack
op_assign
id|p
suffix:semicolon
id|llist_init
c_func
(paren
op_amp
id|l.all_objects
)paren
suffix:semicolon
r_if
c_cond
(paren
id|open_pack_index
c_func
(paren
id|p
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|base
op_assign
id|p-&gt;index_data
suffix:semicolon
id|base
op_add_assign
l_int|256
op_star
l_int|4
op_plus
(paren
(paren
id|p-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|8
)paren
suffix:semicolon
id|step
op_assign
(paren
id|p-&gt;index_version
OL
l_int|2
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|20
suffix:semicolon
r_while
c_loop
(paren
id|off
OL
id|p-&gt;num_objects
op_star
id|step
)paren
(brace
id|llist_insert_back
c_func
(paren
id|l.all_objects
comma
id|base
op_plus
id|off
)paren
suffix:semicolon
id|off
op_add_assign
id|step
suffix:semicolon
)brace
multiline_comment|/* this list will be pruned in cmp_two_packs later */
id|l.unique_objects
op_assign
id|llist_copy
c_func
(paren
id|l.all_objects
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pack_local
)paren
r_return
id|pack_list_insert
c_func
(paren
op_amp
id|local_packs
comma
op_amp
id|l
)paren
suffix:semicolon
r_else
r_return
id|pack_list_insert
c_func
(paren
op_amp
id|altodb_packs
comma
op_amp
id|l
)paren
suffix:semicolon
)brace
DECL|function|add_pack_file
r_static
r_struct
id|pack_list
op_star
id|add_pack_file
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|packed_git
op_star
id|p
op_assign
id|packed_git
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|filename
)paren
OL
l_int|40
)paren
id|die
c_func
(paren
l_string|&quot;Bad pack filename: %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|p-&gt;pack_name
comma
id|filename
)paren
)paren
r_return
id|add_pack
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;Filename %s not found in packed_git&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
DECL|function|load_all
r_static
r_void
id|load_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|packed_git
op_star
id|p
op_assign
id|packed_git
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|add_pack
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|cmd_pack_redundant
r_int
id|cmd_pack_redundant
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
r_int
id|i
suffix:semicolon
r_struct
id|pack_list
op_star
id|min
comma
op_star
id|red
comma
op_star
id|pl
suffix:semicolon
r_struct
id|llist
op_star
id|ignore
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_char
id|buf
(braket
l_int|42
)braket
suffix:semicolon
multiline_comment|/* 40 byte sha1 + &bslash;n + &bslash;0 */
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage
c_func
(paren
id|pack_redundant_usage
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
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
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
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
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|load_all_packs
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
l_string|&quot;--verbose&quot;
)paren
)paren
(brace
id|verbose
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
l_string|&quot;--alt-odb&quot;
)paren
)paren
(brace
id|alt_odb
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|pack_redundant_usage
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
id|prepare_packed_git
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|load_all_packs
)paren
id|load_all
c_func
(paren
)paren
suffix:semicolon
r_else
r_while
c_loop
(paren
op_star
(paren
id|argv
op_plus
id|i
)paren
op_ne
l_int|NULL
)paren
id|add_pack_file
c_func
(paren
op_star
(paren
id|argv
op_plus
id|i
op_increment
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_packs
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;Zero packs found!&quot;
)paren
suffix:semicolon
id|load_all_objects
c_func
(paren
)paren
suffix:semicolon
id|cmp_local_packs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alt_odb
)paren
id|scan_alt_odb_packs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ignore objects given on stdin */
id|llist_init
c_func
(paren
op_amp
id|ignore
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isatty
c_func
(paren
l_int|0
)paren
)paren
(brace
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|stdin
)paren
)paren
(brace
id|sha1
op_assign
id|xmalloc
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buf
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Bad sha1 on stdin: %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|llist_insert_sorted_unique
c_func
(paren
id|ignore
comma
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
id|llist_sorted_difference_inplace
c_func
(paren
id|all_objects
comma
id|ignore
)paren
suffix:semicolon
id|pl
op_assign
id|local_packs
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|llist_sorted_difference_inplace
c_func
(paren
id|pl-&gt;unique_objects
comma
id|ignore
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
id|minimize
c_func
(paren
op_amp
id|min
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;There are %lu packs available in alt-odbs.&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|pack_list_size
c_func
(paren
id|altodb_packs
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;The smallest (bytewise) set of packs is:&bslash;n&quot;
)paren
suffix:semicolon
id|pl
op_assign
id|min
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;t%s&bslash;n&quot;
comma
id|pl-&gt;pack-&gt;pack_name
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;containing %lu duplicate objects &quot;
l_string|&quot;with a total size of %lukb.&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|get_pack_redundancy
c_func
(paren
id|min
)paren
comma
(paren
r_int
r_int
)paren
id|pack_set_bytecount
c_func
(paren
id|min
)paren
op_div
l_int|1024
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;A total of %lu unique objects were considered.&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|all_objects-&gt;size
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Redundant packs (with indexes):&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pl
op_assign
id|red
op_assign
id|pack_list_difference
c_func
(paren
id|local_packs
comma
id|min
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pl
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n%s&bslash;n&quot;
comma
id|sha1_pack_index_name
c_func
(paren
id|pl-&gt;pack-&gt;sha1
)paren
comma
id|pl-&gt;pack-&gt;pack_name
)paren
suffix:semicolon
id|pl
op_assign
id|pl-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%luMB of redundant packs in total.&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|pack_set_bytecount
c_func
(paren
id|red
)paren
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
