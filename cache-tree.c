macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
DECL|function|cache_tree
r_struct
id|cache_tree
op_star
id|cache_tree
c_func
(paren
r_void
)paren
(brace
r_struct
id|cache_tree
op_star
id|it
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|cache_tree
)paren
)paren
suffix:semicolon
id|it-&gt;entry_count
op_assign
l_int|1
suffix:semicolon
r_return
id|it
suffix:semicolon
)brace
DECL|function|cache_tree_free
r_void
id|cache_tree_free
c_func
(paren
r_struct
id|cache_tree
op_star
op_star
id|it_p
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|cache_tree
op_star
id|it
op_assign
op_star
id|it_p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
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
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|it-&gt;down
(braket
id|i
)braket
)paren
id|cache_tree_free
c_func
(paren
op_amp
id|it-&gt;down
(braket
id|i
)braket
op_member_access_from_pointer
id|cache_tree
)paren
suffix:semicolon
id|free
c_func
(paren
id|it-&gt;down
)paren
suffix:semicolon
id|free
c_func
(paren
id|it
)paren
suffix:semicolon
op_star
id|it_p
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|subtree_name_cmp
r_static
r_int
id|subtree_name_cmp
c_func
(paren
r_const
r_char
op_star
id|one
comma
r_int
id|onelen
comma
r_const
r_char
op_star
id|two
comma
r_int
id|twolen
)paren
(brace
r_if
c_cond
(paren
id|onelen
OL
id|twolen
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|twolen
OL
id|onelen
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|memcmp
c_func
(paren
id|one
comma
id|two
comma
id|onelen
)paren
suffix:semicolon
)brace
DECL|function|subtree_pos
r_static
r_int
id|subtree_pos
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
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
r_struct
id|cache_tree_sub
op_star
op_star
id|down
op_assign
id|it-&gt;down
suffix:semicolon
r_int
id|lo
comma
id|hi
suffix:semicolon
id|lo
op_assign
l_int|0
suffix:semicolon
id|hi
op_assign
id|it-&gt;subtree_nr
suffix:semicolon
r_while
c_loop
(paren
id|lo
OL
id|hi
)paren
(brace
r_int
id|mi
op_assign
(paren
id|lo
op_plus
id|hi
)paren
op_div
l_int|2
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|mdl
op_assign
id|down
(braket
id|mi
)braket
suffix:semicolon
r_int
id|cmp
op_assign
id|subtree_name_cmp
c_func
(paren
id|path
comma
id|pathlen
comma
id|mdl-&gt;name
comma
id|mdl-&gt;namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|mi
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
id|hi
op_assign
id|mi
suffix:semicolon
r_else
id|lo
op_assign
id|mi
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|lo
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|find_subtree
r_static
r_struct
id|cache_tree_sub
op_star
id|find_subtree
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_const
r_char
op_star
id|path
comma
r_int
id|pathlen
comma
r_int
id|create
)paren
(brace
r_struct
id|cache_tree_sub
op_star
id|down
suffix:semicolon
r_int
id|pos
op_assign
id|subtree_pos
c_func
(paren
id|it
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
r_return
id|it-&gt;down
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|create
)paren
r_return
l_int|NULL
suffix:semicolon
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|it-&gt;subtree_alloc
op_le
id|it-&gt;subtree_nr
)paren
(brace
id|it-&gt;subtree_alloc
op_assign
id|alloc_nr
c_func
(paren
id|it-&gt;subtree_alloc
)paren
suffix:semicolon
id|it-&gt;down
op_assign
id|xrealloc
c_func
(paren
id|it-&gt;down
comma
id|it-&gt;subtree_alloc
op_star
r_sizeof
(paren
op_star
id|it-&gt;down
)paren
)paren
suffix:semicolon
)brace
id|it-&gt;subtree_nr
op_increment
suffix:semicolon
id|down
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|down
)paren
op_plus
id|pathlen
op_plus
l_int|1
)paren
suffix:semicolon
id|down-&gt;cache_tree
op_assign
l_int|NULL
suffix:semicolon
id|down-&gt;namelen
op_assign
id|pathlen
suffix:semicolon
id|memcpy
c_func
(paren
id|down-&gt;name
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|down-&gt;name
(braket
id|pathlen
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|it-&gt;subtree_nr
)paren
id|memmove
c_func
(paren
id|it-&gt;down
op_plus
id|pos
op_plus
l_int|1
comma
id|it-&gt;down
op_plus
id|pos
comma
r_sizeof
(paren
id|down
)paren
op_star
(paren
id|it-&gt;subtree_nr
id|pos
l_int|1
)paren
)paren
suffix:semicolon
id|it-&gt;down
(braket
id|pos
)braket
op_assign
id|down
suffix:semicolon
r_return
id|down
suffix:semicolon
)brace
DECL|function|cache_tree_sub
r_struct
id|cache_tree_sub
op_star
id|cache_tree_sub
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|find_subtree
c_func
(paren
id|it
comma
id|path
comma
id|pathlen
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cache_tree_invalidate_path
r_void
id|cache_tree_invalidate_path
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_const
r_char
op_star
id|path
)paren
(brace
multiline_comment|/* a/b/c&n;&t; * ==&gt; invalidate self&n;&t; * ==&gt; find &quot;a&quot;, have it invalidate &quot;b/c&quot;&n;&t; * a&n;&t; * ==&gt; invalidate self&n;&t; * ==&gt; if &quot;a&quot; exists as a subtree, remove it.&n;&t; */
r_const
r_char
op_star
id|slash
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|down
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
suffix:semicolon
id|slash
op_assign
id|strchr
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|it-&gt;entry_count
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slash
)paren
(brace
r_int
id|pos
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|pos
op_assign
id|subtree_pos
c_func
(paren
id|it
comma
id|path
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
(brace
id|cache_tree_free
c_func
(paren
op_amp
id|it-&gt;down
(braket
id|pos
)braket
op_member_access_from_pointer
id|cache_tree
)paren
suffix:semicolon
id|free
c_func
(paren
id|it-&gt;down
(braket
id|pos
)braket
)paren
suffix:semicolon
multiline_comment|/* 0 1 2 3 4 5&n;&t;&t;&t; *       ^     ^subtree_nr = 6&n;&t;&t;&t; *       pos&n;&t;&t;&t; * move 4 and 5 up one place (2 entries)&n;&t;&t;&t; * 2 = 6 - 3 - 1 = subtree_nr - pos - 1&n;&t;&t;&t; */
id|memmove
c_func
(paren
id|it-&gt;down
op_plus
id|pos
comma
id|it-&gt;down
op_plus
id|pos
op_plus
l_int|1
comma
r_sizeof
(paren
r_struct
id|cache_tree_sub
op_star
)paren
op_star
(paren
id|it-&gt;subtree_nr
id|pos
l_int|1
)paren
)paren
suffix:semicolon
id|it-&gt;subtree_nr
op_decrement
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|namelen
op_assign
id|slash
id|path
suffix:semicolon
id|down
op_assign
id|find_subtree
c_func
(paren
id|it
comma
id|path
comma
id|namelen
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|down
)paren
id|cache_tree_invalidate_path
c_func
(paren
id|down-&gt;cache_tree
comma
id|slash
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|verify_cache
r_static
r_int
id|verify_cache
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|cache
comma
r_int
id|entries
)paren
(brace
r_int
id|i
comma
id|funny
suffix:semicolon
multiline_comment|/* Verify that the tree is merged */
id|funny
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|10
OL
op_increment
id|funny
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: unmerged (%s)&bslash;n&quot;
comma
id|ce-&gt;name
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|funny
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Also verify that the cache does not have path and path/file&n;&t; * at the same time.  At this point we know the cache has only&n;&t; * stage 0 entries.&n;&t; */
id|funny
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
id|entries
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* path/file always comes after path because of the way&n;&t;&t; * the cache is sorted.  Also path can appear only once,&n;&t;&t; * which means conflicting one would immediately follow.&n;&t;&t; */
r_const
r_char
op_star
id|this_name
op_assign
id|cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
r_const
r_char
op_star
id|next_name
op_assign
id|cache
(braket
id|i
op_plus
l_int|1
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
r_int
id|this_len
op_assign
id|strlen
c_func
(paren
id|this_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this_len
OL
id|strlen
c_func
(paren
id|next_name
)paren
op_logical_and
id|strncmp
c_func
(paren
id|this_name
comma
id|next_name
comma
id|this_len
)paren
op_eq
l_int|0
op_logical_and
id|next_name
(braket
id|this_len
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
l_int|10
OL
op_increment
id|funny
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;You have both %s and %s&bslash;n&quot;
comma
id|this_name
comma
id|next_name
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|funny
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|discard_unused_subtrees
r_static
r_void
id|discard_unused_subtrees
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
)paren
(brace
r_struct
id|cache_tree_sub
op_star
op_star
id|down
op_assign
id|it-&gt;down
suffix:semicolon
r_int
id|nr
op_assign
id|it-&gt;subtree_nr
suffix:semicolon
r_int
id|dst
comma
id|src
suffix:semicolon
r_for
c_loop
(paren
id|dst
op_assign
id|src
op_assign
l_int|0
suffix:semicolon
id|src
OL
id|nr
suffix:semicolon
id|src
op_increment
)paren
(brace
r_struct
id|cache_tree_sub
op_star
id|s
op_assign
id|down
(braket
id|src
)braket
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;used
)paren
id|down
(braket
id|dst
op_increment
)braket
op_assign
id|s
suffix:semicolon
r_else
(brace
id|cache_tree_free
c_func
(paren
op_amp
id|s-&gt;cache_tree
)paren
suffix:semicolon
id|free
c_func
(paren
id|s
)paren
suffix:semicolon
id|it-&gt;subtree_nr
op_decrement
suffix:semicolon
)brace
)brace
)brace
DECL|function|cache_tree_fully_valid
r_int
id|cache_tree_fully_valid
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|it-&gt;entry_count
OL
l_int|0
op_logical_or
op_logical_neg
id|has_sha1_file
c_func
(paren
id|it-&gt;sha1
)paren
)paren
r_return
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
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cache_tree_fully_valid
c_func
(paren
id|it-&gt;down
(braket
id|i
)braket
op_member_access_from_pointer
id|cache_tree
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|update_one
r_static
r_int
id|update_one
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_struct
id|cache_entry
op_star
op_star
id|cache
comma
r_int
id|entries
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
id|missing_ok
comma
r_int
id|dryrun
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
id|buffer
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|it-&gt;entry_count
op_logical_and
id|has_sha1_file
c_func
(paren
id|it-&gt;sha1
)paren
)paren
r_return
id|it-&gt;entry_count
suffix:semicolon
multiline_comment|/*&n;&t; * We first scan for subtrees and update them; we start by&n;&t; * marking existing subtrees -- the ones that are unmarked&n;&t; * should not be in the result.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
id|it-&gt;down
(braket
id|i
)braket
op_member_access_from_pointer
id|used
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Find the subtrees and update them.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|cache
(braket
id|i
)braket
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|sub
suffix:semicolon
r_const
r_char
op_star
id|path
comma
op_star
id|slash
suffix:semicolon
r_int
id|pathlen
comma
id|sublen
comma
id|subcnt
suffix:semicolon
id|path
op_assign
id|ce-&gt;name
suffix:semicolon
id|pathlen
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
op_le
id|baselen
op_logical_or
id|memcmp
c_func
(paren
id|base
comma
id|path
comma
id|baselen
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* at the end of this level */
id|slash
op_assign
id|strchr
c_func
(paren
id|path
op_plus
id|baselen
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slash
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * a/bbb/c (base = a/, slash = /c)&n;&t;&t; * ==&gt;&n;&t;&t; * path+baselen = bbb/c, sublen = 3&n;&t;&t; */
id|sublen
op_assign
id|slash
(paren
id|path
op_plus
id|baselen
)paren
suffix:semicolon
id|sub
op_assign
id|find_subtree
c_func
(paren
id|it
comma
id|path
op_plus
id|baselen
comma
id|sublen
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sub-&gt;cache_tree
)paren
id|sub-&gt;cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|subcnt
op_assign
id|update_one
c_func
(paren
id|sub-&gt;cache_tree
comma
id|cache
op_plus
id|i
comma
id|entries
id|i
comma
id|path
comma
id|baselen
op_plus
id|sublen
op_plus
l_int|1
comma
id|missing_ok
comma
id|dryrun
)paren
suffix:semicolon
id|i
op_add_assign
id|subcnt
l_int|1
suffix:semicolon
id|sub-&gt;used
op_assign
l_int|1
suffix:semicolon
)brace
id|discard_unused_subtrees
c_func
(paren
id|it
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Then write out the tree object for this level.&n;&t; */
id|size
op_assign
l_int|8192
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|offset
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|cache
(braket
id|i
)braket
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|sub
suffix:semicolon
r_const
r_char
op_star
id|path
comma
op_star
id|slash
suffix:semicolon
r_int
id|pathlen
comma
id|entlen
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
id|path
op_assign
id|ce-&gt;name
suffix:semicolon
id|pathlen
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
op_le
id|baselen
op_logical_or
id|memcmp
c_func
(paren
id|base
comma
id|path
comma
id|baselen
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* at the end of this level */
id|slash
op_assign
id|strchr
c_func
(paren
id|path
op_plus
id|baselen
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
(brace
id|entlen
op_assign
id|slash
(paren
id|path
op_plus
id|baselen
)paren
suffix:semicolon
id|sub
op_assign
id|find_subtree
c_func
(paren
id|it
comma
id|path
op_plus
id|baselen
comma
id|entlen
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sub
)paren
id|die
c_func
(paren
l_string|&quot;cache-tree.c: &squot;%.*s&squot; in &squot;%s&squot; not found&quot;
comma
id|entlen
comma
id|path
op_plus
id|baselen
comma
id|path
)paren
suffix:semicolon
id|i
op_add_assign
id|sub-&gt;cache_tree-&gt;entry_count
l_int|1
suffix:semicolon
id|sha1
op_assign
id|sub-&gt;cache_tree-&gt;sha1
suffix:semicolon
id|mode
op_assign
id|S_IFDIR
suffix:semicolon
)brace
r_else
(brace
id|sha1
op_assign
id|ce-&gt;sha1
suffix:semicolon
id|mode
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
id|entlen
op_assign
id|pathlen
id|baselen
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|missing_ok
op_logical_and
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;invalid object %s&quot;
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
op_logical_neg
id|ce-&gt;ce_mode
)paren
r_continue
suffix:semicolon
multiline_comment|/* entry being removed */
r_if
c_cond
(paren
id|size
OL
id|offset
op_plus
id|entlen
op_plus
l_int|100
)paren
(brace
id|size
op_assign
id|alloc_nr
c_func
(paren
id|offset
op_plus
id|entlen
op_plus
l_int|100
)paren
suffix:semicolon
id|buffer
op_assign
id|xrealloc
c_func
(paren
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|offset
comma
l_string|&quot;%o %.*s&quot;
comma
id|mode
comma
id|entlen
comma
id|path
op_plus
id|baselen
)paren
suffix:semicolon
id|buffer
(braket
id|offset
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
op_plus
id|offset
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|20
suffix:semicolon
macro_line|#if DEBUG
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree %o %.*s&bslash;n&quot;
comma
id|mode
comma
id|entlen
comma
id|path
op_plus
id|baselen
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|dryrun
)paren
(brace
r_int
r_char
id|hdr
(braket
l_int|200
)braket
suffix:semicolon
r_int
id|hdrlen
suffix:semicolon
id|write_sha1_file_prepare
c_func
(paren
id|buffer
comma
id|offset
comma
id|tree_type
comma
id|it-&gt;sha1
comma
id|hdr
comma
op_amp
id|hdrlen
)paren
suffix:semicolon
)brace
r_else
id|write_sha1_file
c_func
(paren
id|buffer
comma
id|offset
comma
id|tree_type
comma
id|it-&gt;sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|it-&gt;entry_count
op_assign
id|i
suffix:semicolon
macro_line|#if DEBUG
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree (%d ent, %d subtree) %s&bslash;n&quot;
comma
id|it-&gt;entry_count
comma
id|it-&gt;subtree_nr
comma
id|sha1_to_hex
c_func
(paren
id|it-&gt;sha1
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|i
suffix:semicolon
)brace
DECL|function|cache_tree_update
r_int
id|cache_tree_update
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_struct
id|cache_entry
op_star
op_star
id|cache
comma
r_int
id|entries
comma
r_int
id|missing_ok
comma
r_int
id|dryrun
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|verify_cache
c_func
(paren
id|cache
comma
id|entries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|i
op_assign
id|update_one
c_func
(paren
id|it
comma
id|cache
comma
id|entries
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|missing_ok
comma
id|dryrun
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
id|i
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_one
r_static
r_void
op_star
id|write_one
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_char
op_star
id|path
comma
r_int
id|pathlen
comma
r_char
op_star
id|buffer
comma
r_int
r_int
op_star
id|size
comma
r_int
r_int
op_star
id|offset
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* One &quot;cache-tree&quot; entry consists of the following:&n;&t; * path (NUL terminated)&n;&t; * entry_count, subtree_nr (&quot;%d %d&bslash;n&quot;)&n;&t; * tree-sha1 (missing if invalid)&n;&t; * subtree_nr &quot;cache-tree&quot; entries for subtrees.&n;&t; */
r_if
c_cond
(paren
op_star
id|size
OL
op_star
id|offset
op_plus
id|pathlen
op_plus
l_int|100
)paren
(brace
op_star
id|size
op_assign
id|alloc_nr
c_func
(paren
op_star
id|offset
op_plus
id|pathlen
op_plus
l_int|100
)paren
suffix:semicolon
id|buffer
op_assign
id|xrealloc
c_func
(paren
id|buffer
comma
op_star
id|size
)paren
suffix:semicolon
)brace
op_star
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
op_star
id|offset
comma
l_string|&quot;%.*s%c%d %d&bslash;n&quot;
comma
id|pathlen
comma
id|path
comma
l_int|0
comma
id|it-&gt;entry_count
comma
id|it-&gt;subtree_nr
)paren
suffix:semicolon
macro_line|#if DEBUG
r_if
c_cond
(paren
l_int|0
op_le
id|it-&gt;entry_count
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree &lt;%.*s&gt; (%d ent, %d subtree) %s&bslash;n&quot;
comma
id|pathlen
comma
id|path
comma
id|it-&gt;entry_count
comma
id|it-&gt;subtree_nr
comma
id|sha1_to_hex
c_func
(paren
id|it-&gt;sha1
)paren
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree &lt;%.*s&gt; (%d subtree) invalid&bslash;n&quot;
comma
id|pathlen
comma
id|path
comma
id|it-&gt;subtree_nr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
l_int|0
op_le
id|it-&gt;entry_count
)paren
(brace
id|memcpy
c_func
(paren
id|buffer
op_plus
op_star
id|offset
comma
id|it-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
op_star
id|offset
op_add_assign
l_int|20
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_tree_sub
op_star
id|down
op_assign
id|it-&gt;down
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
r_struct
id|cache_tree_sub
op_star
id|prev
op_assign
id|it-&gt;down
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|subtree_name_cmp
c_func
(paren
id|down-&gt;name
comma
id|down-&gt;namelen
comma
id|prev-&gt;name
comma
id|prev-&gt;namelen
)paren
op_le
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;fatal - unsorted cache subtree&quot;
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|write_one
c_func
(paren
id|down-&gt;cache_tree
comma
id|down-&gt;name
comma
id|down-&gt;namelen
comma
id|buffer
comma
id|size
comma
id|offset
)paren
suffix:semicolon
)brace
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|cache_tree_write
r_void
op_star
id|cache_tree_write
c_func
(paren
r_struct
id|cache_tree
op_star
id|root
comma
r_int
r_int
op_star
id|size_p
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
r_int
id|size
op_assign
l_int|8192
suffix:semicolon
r_char
op_star
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
op_star
id|size_p
op_assign
l_int|0
suffix:semicolon
id|path
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|write_one
c_func
(paren
id|root
comma
id|path
comma
l_int|0
comma
id|buffer
comma
op_amp
id|size
comma
id|size_p
)paren
suffix:semicolon
)brace
DECL|function|read_one
r_static
r_struct
id|cache_tree
op_star
id|read_one
c_func
(paren
r_const
r_char
op_star
op_star
id|buffer
comma
r_int
r_int
op_star
id|size_p
)paren
(brace
r_const
r_char
op_star
id|buf
op_assign
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
op_assign
op_star
id|size_p
suffix:semicolon
r_struct
id|cache_tree
op_star
id|it
suffix:semicolon
r_int
id|i
comma
id|subtree_nr
suffix:semicolon
id|it
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* skip name, but make sure name exists */
r_while
c_loop
(paren
id|size
op_logical_and
op_star
id|buf
)paren
(brace
id|size
op_decrement
suffix:semicolon
id|buf
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_goto
id|free_return
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
id|it
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%d %d&bslash;n&quot;
comma
op_amp
id|it-&gt;entry_count
comma
op_amp
id|subtree_nr
)paren
op_ne
l_int|2
)paren
r_goto
id|free_return
suffix:semicolon
r_while
c_loop
(paren
id|size
op_logical_and
op_star
id|buf
op_logical_and
op_star
id|buf
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|size
op_decrement
suffix:semicolon
id|buf
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_goto
id|free_return
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|it-&gt;entry_count
)paren
(brace
r_if
c_cond
(paren
id|size
OL
l_int|20
)paren
r_goto
id|free_return
suffix:semicolon
id|memcpy
c_func
(paren
id|it-&gt;sha1
comma
id|buf
comma
l_int|20
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|20
suffix:semicolon
id|size
op_sub_assign
l_int|20
suffix:semicolon
)brace
macro_line|#if DEBUG
r_if
c_cond
(paren
l_int|0
op_le
id|it-&gt;entry_count
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree &lt;%s&gt; (%d ent, %d subtree) %s&bslash;n&quot;
comma
op_star
id|buffer
comma
id|it-&gt;entry_count
comma
id|subtree_nr
comma
id|sha1_to_hex
c_func
(paren
id|it-&gt;sha1
)paren
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree &lt;%s&gt; (%d subtrees) invalid&bslash;n&quot;
comma
op_star
id|buffer
comma
id|subtree_nr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Just a heuristic -- we do not add directories that often but&n;&t; * we do not want to have to extend it immediately when we do,&n;&t; * hence +2.&n;&t; */
id|it-&gt;subtree_alloc
op_assign
id|subtree_nr
op_plus
l_int|2
suffix:semicolon
id|it-&gt;down
op_assign
id|xcalloc
c_func
(paren
id|it-&gt;subtree_alloc
comma
r_sizeof
(paren
r_struct
id|cache_tree_sub
op_star
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
id|subtree_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* read each subtree */
r_struct
id|cache_tree
op_star
id|sub
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|subtree
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|buf
suffix:semicolon
id|sub
op_assign
id|read_one
c_func
(paren
op_amp
id|buf
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sub
)paren
r_goto
id|free_return
suffix:semicolon
id|subtree
op_assign
id|cache_tree_sub
c_func
(paren
id|it
comma
id|name
)paren
suffix:semicolon
id|subtree-&gt;cache_tree
op_assign
id|sub
suffix:semicolon
)brace
r_if
c_cond
(paren
id|subtree_nr
op_ne
id|it-&gt;subtree_nr
)paren
id|die
c_func
(paren
l_string|&quot;cache-tree: internal error&quot;
)paren
suffix:semicolon
op_star
id|buffer
op_assign
id|buf
suffix:semicolon
op_star
id|size_p
op_assign
id|size
suffix:semicolon
r_return
id|it
suffix:semicolon
id|free_return
suffix:colon
id|cache_tree_free
c_func
(paren
op_amp
id|it
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|cache_tree_read
r_struct
id|cache_tree
op_star
id|cache_tree_read
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
l_int|0
)braket
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* not the whole tree */
r_return
id|read_one
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
)paren
suffix:semicolon
)brace
eof
