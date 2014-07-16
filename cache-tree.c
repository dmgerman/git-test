macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#ifndef DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
macro_line|#endif
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
(brace
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
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
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
id|ALLOC_GROW
c_func
(paren
id|it-&gt;down
comma
id|it-&gt;subtree_nr
op_plus
l_int|1
comma
id|it-&gt;subtree_alloc
)paren
suffix:semicolon
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
DECL|function|do_invalidate_path
r_static
r_int
id|do_invalidate_path
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
macro_line|#if DEBUG
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree invalidate &lt;%s&gt;&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
l_int|0
suffix:semicolon
id|slash
op_assign
id|strchrnul
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|namelen
op_assign
id|slash
id|path
suffix:semicolon
id|it-&gt;entry_count
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|slash
)paren
(brace
r_int
id|pos
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
l_int|1
suffix:semicolon
)brace
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
id|do_invalidate_path
c_func
(paren
id|down-&gt;cache_tree
comma
id|slash
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cache_tree_invalidate_path
r_void
id|cache_tree_invalidate_path
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|do_invalidate_path
c_func
(paren
id|istate-&gt;cache_tree
comma
id|path
)paren
)paren
id|istate-&gt;cache_changed
op_or_assign
id|CACHE_TREE_CHANGED
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
comma
r_int
id|flags
)paren
(brace
r_int
id|i
comma
id|funny
suffix:semicolon
r_int
id|silent
op_assign
id|flags
op_amp
id|WRITE_TREE_SILENT
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
r_const
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
id|silent
)paren
r_return
l_int|1
suffix:semicolon
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
op_star
id|skip_count
comma
r_int
id|flags
)paren
(brace
r_struct
id|strbuf
id|buffer
suffix:semicolon
r_int
id|missing_ok
op_assign
id|flags
op_amp
id|WRITE_TREE_MISSING_OK
suffix:semicolon
r_int
id|dryrun
op_assign
id|flags
op_amp
id|WRITE_TREE_DRY_RUN
suffix:semicolon
r_int
id|to_invalidate
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|skip_count
op_assign
l_int|0
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
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|entries
)paren
(brace
r_const
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
comma
id|subskip
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
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
op_amp
id|subskip
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subcnt
OL
l_int|0
)paren
r_return
id|subcnt
suffix:semicolon
id|i
op_add_assign
id|subcnt
suffix:semicolon
id|sub-&gt;count
op_assign
id|subcnt
suffix:semicolon
multiline_comment|/* to be used in the next loop */
op_star
id|skip_count
op_add_assign
id|subskip
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
id|strbuf_init
c_func
(paren
op_amp
id|buffer
comma
l_int|8192
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|entries
)paren
(brace
r_const
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
id|sub-&gt;count
suffix:semicolon
id|sha1
op_assign
id|sub-&gt;cache_tree-&gt;sha1
suffix:semicolon
id|mode
op_assign
id|S_IFDIR
suffix:semicolon
r_if
c_cond
(paren
id|sub-&gt;cache_tree-&gt;entry_count
OL
l_int|0
)paren
id|to_invalidate
op_assign
l_int|1
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
id|ce-&gt;ce_mode
suffix:semicolon
id|entlen
op_assign
id|pathlen
id|baselen
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mode
op_ne
id|S_IFGITLINK
op_logical_and
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
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;invalid object %06o %s for &squot;%.*s&squot;&quot;
comma
id|mode
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|entlen
op_plus
id|baselen
comma
id|path
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * CE_REMOVE entries are removed before the index is&n;&t;&t; * written to disk. Skip them to remain consistent&n;&t;&t; * with the future on-disk index.&n;&t;&t; */
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_REMOVE
)paren
(brace
op_star
id|skip_count
op_assign
op_star
id|skip_count
op_plus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * CE_INTENT_TO_ADD entries exist on on-disk index but&n;&t;&t; * they are not part of generated trees. Invalidate up&n;&t;&t; * to root to force cache-tree users to read elsewhere.&n;&t;&t; */
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_INTENT_TO_ADD
)paren
(brace
id|to_invalidate
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|strbuf_grow
c_func
(paren
op_amp
id|buffer
comma
id|entlen
op_plus
l_int|100
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buffer
comma
l_string|&quot;%o %.*s%c&quot;
comma
id|mode
comma
id|entlen
comma
id|path
op_plus
id|baselen
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|buffer
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
macro_line|#if DEBUG
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree update-one %o %.*s&bslash;n&quot;
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
id|hash_sha1_file
c_func
(paren
id|buffer.buf
comma
id|buffer.len
comma
id|tree_type
comma
id|it-&gt;sha1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|buffer.buf
comma
id|buffer.len
comma
id|tree_type
comma
id|it-&gt;sha1
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
id|it-&gt;entry_count
op_assign
id|to_invalidate
ques
c_cond
l_int|1
suffix:colon
id|i
op_star
id|skip_count
suffix:semicolon
macro_line|#if DEBUG
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cache-tree update-one (%d ent, %d subtree) %s&bslash;n&quot;
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
id|index_state
op_star
id|istate
comma
r_int
id|flags
)paren
(brace
r_struct
id|cache_tree
op_star
id|it
op_assign
id|istate-&gt;cache_tree
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|cache
op_assign
id|istate-&gt;cache
suffix:semicolon
r_int
id|entries
op_assign
id|istate-&gt;cache_nr
suffix:semicolon
r_int
id|skip
comma
id|i
op_assign
id|verify_cache
c_func
(paren
id|cache
comma
id|entries
comma
id|flags
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
op_amp
id|skip
comma
id|flags
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
id|istate-&gt;cache_changed
op_or_assign
id|CACHE_TREE_CHANGED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_one
r_static
r_void
id|write_one
c_func
(paren
r_struct
id|strbuf
op_star
id|buffer
comma
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
r_int
id|i
suffix:semicolon
multiline_comment|/* One &quot;cache-tree&quot; entry consists of the following:&n;&t; * path (NUL terminated)&n;&t; * entry_count, subtree_nr (&quot;%d %d&bslash;n&quot;)&n;&t; * tree-sha1 (missing if invalid)&n;&t; * subtree_nr &quot;cache-tree&quot; entries for subtrees.&n;&t; */
id|strbuf_grow
c_func
(paren
id|buffer
comma
id|pathlen
op_plus
l_int|100
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buffer
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|buffer
comma
l_string|&quot;%c%d %d&bslash;n&quot;
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
id|strbuf_add
c_func
(paren
id|buffer
comma
id|it-&gt;sha1
comma
l_int|20
)paren
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
id|write_one
c_func
(paren
id|buffer
comma
id|down-&gt;cache_tree
comma
id|down-&gt;name
comma
id|down-&gt;namelen
)paren
suffix:semicolon
)brace
)brace
DECL|function|cache_tree_write
r_void
id|cache_tree_write
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_struct
id|cache_tree
op_star
id|root
)paren
(brace
id|write_one
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;&quot;
comma
l_int|0
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
r_const
r_char
op_star
id|cp
suffix:semicolon
r_char
op_star
id|ep
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
id|cp
op_assign
id|buf
suffix:semicolon
id|it-&gt;entry_count
op_assign
id|strtol
c_func
(paren
id|cp
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_eq
id|ep
)paren
r_goto
id|free_return
suffix:semicolon
id|cp
op_assign
id|ep
suffix:semicolon
id|subtree_nr
op_assign
id|strtol
c_func
(paren
id|cp
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_eq
id|ep
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
id|hashcpy
c_func
(paren
id|it-&gt;sha1
comma
(paren
r_const
r_int
r_char
op_star
)paren
id|buf
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
DECL|function|cache_tree_find
r_static
r_struct
id|cache_tree
op_star
id|cache_tree_find
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
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|path
)paren
(brace
r_const
r_char
op_star
id|slash
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|sub
suffix:semicolon
id|slash
op_assign
id|strchrnul
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Between path and slash is the name of the subtree&n;&t;&t; * to look for.&n;&t;&t; */
id|sub
op_assign
id|find_subtree
c_func
(paren
id|it
comma
id|path
comma
id|slash
id|path
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
r_return
l_int|NULL
suffix:semicolon
id|it
op_assign
id|sub-&gt;cache_tree
suffix:semicolon
id|path
op_assign
id|slash
suffix:semicolon
r_while
c_loop
(paren
op_star
id|path
op_eq
l_char|&squot;/&squot;
)paren
id|path
op_increment
suffix:semicolon
)brace
r_return
id|it
suffix:semicolon
)brace
DECL|function|write_cache_as_tree
r_int
id|write_cache_as_tree
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|entries
comma
id|was_valid
comma
id|newfd
suffix:semicolon
r_struct
id|lock_file
op_star
id|lock_file
suffix:semicolon
multiline_comment|/*&n;&t; * We can&squot;t free this memory, it becomes part of a linked list&n;&t; * parsed atexit()&n;&t; */
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
r_return
id|WRITE_TREE_UNREADABLE_INDEX
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|WRITE_TREE_IGNORE_CACHE_TREE
)paren
id|cache_tree_free
c_func
(paren
op_amp
(paren
id|active_cache_tree
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|active_cache_tree
)paren
id|active_cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|was_valid
op_assign
id|cache_tree_fully_valid
c_func
(paren
id|active_cache_tree
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|was_valid
)paren
(brace
r_if
c_cond
(paren
id|cache_tree_update
c_func
(paren
op_amp
id|the_index
comma
id|flags
)paren
OL
l_int|0
)paren
r_return
id|WRITE_TREE_UNMERGED_INDEX
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|newfd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|write_locked_index
c_func
(paren
op_amp
id|the_index
comma
id|lock_file
comma
id|COMMIT_LOCK
)paren
)paren
id|newfd
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Not being able to write is fine -- we are only interested&n;&t;&t; * in updating the cache-tree part, and if the next caller&n;&t;&t; * ends up using the old index with unupdated cache-tree part&n;&t;&t; * it misses the work we did here, but that is just a&n;&t;&t; * performance penalty and not a big deal.&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_struct
id|cache_tree
op_star
id|subtree
op_assign
id|cache_tree_find
c_func
(paren
id|active_cache_tree
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subtree
)paren
r_return
id|WRITE_TREE_PREFIX_ERROR
suffix:semicolon
id|hashcpy
c_func
(paren
id|sha1
comma
id|subtree-&gt;sha1
)paren
suffix:semicolon
)brace
r_else
id|hashcpy
c_func
(paren
id|sha1
comma
id|active_cache_tree-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|newfd
)paren
id|rollback_lock_file
c_func
(paren
id|lock_file
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prime_cache_tree_rec
r_static
r_void
id|prime_cache_tree_rec
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_struct
id|tree
op_star
id|tree
)paren
(brace
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_int
id|cnt
suffix:semicolon
id|hashcpy
c_func
(paren
id|it-&gt;sha1
comma
id|tree-&gt;object.sha1
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|desc
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|tree_entry
c_func
(paren
op_amp
id|desc
comma
op_amp
id|entry
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|cnt
op_increment
suffix:semicolon
r_else
(brace
r_struct
id|cache_tree_sub
op_star
id|sub
suffix:semicolon
r_struct
id|tree
op_star
id|subtree
op_assign
id|lookup_tree
c_func
(paren
id|entry.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subtree-&gt;object.parsed
)paren
id|parse_tree
c_func
(paren
id|subtree
)paren
suffix:semicolon
id|sub
op_assign
id|cache_tree_sub
c_func
(paren
id|it
comma
id|entry.path
)paren
suffix:semicolon
id|sub-&gt;cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|prime_cache_tree_rec
c_func
(paren
id|sub-&gt;cache_tree
comma
id|subtree
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sub-&gt;cache_tree-&gt;entry_count
suffix:semicolon
)brace
)brace
id|it-&gt;entry_count
op_assign
id|cnt
suffix:semicolon
)brace
DECL|function|prime_cache_tree
r_void
id|prime_cache_tree
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_struct
id|tree
op_star
id|tree
)paren
(brace
id|cache_tree_free
c_func
(paren
op_amp
id|istate-&gt;cache_tree
)paren
suffix:semicolon
id|istate-&gt;cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|prime_cache_tree_rec
c_func
(paren
id|istate-&gt;cache_tree
comma
id|tree
)paren
suffix:semicolon
id|istate-&gt;cache_changed
op_or_assign
id|CACHE_TREE_CHANGED
suffix:semicolon
)brace
multiline_comment|/*&n; * find the cache_tree that corresponds to the current level without&n; * exploding the full path into textual form.  The root of the&n; * cache tree is given as &quot;root&quot;, and our current level is &quot;info&quot;.&n; * (1) When at root level, info-&gt;prev is NULL, so it is &quot;root&quot; itself.&n; * (2) Otherwise, find the cache_tree that corresponds to one level&n; *     above us, and find ourselves in there.&n; */
DECL|function|find_cache_tree_from_traversal
r_static
r_struct
id|cache_tree
op_star
id|find_cache_tree_from_traversal
c_func
(paren
r_struct
id|cache_tree
op_star
id|root
comma
r_struct
id|traverse_info
op_star
id|info
)paren
(brace
r_struct
id|cache_tree
op_star
id|our_parent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;prev
)paren
r_return
id|root
suffix:semicolon
id|our_parent
op_assign
id|find_cache_tree_from_traversal
c_func
(paren
id|root
comma
id|info-&gt;prev
)paren
suffix:semicolon
r_return
id|cache_tree_find
c_func
(paren
id|our_parent
comma
id|info-&gt;name.path
)paren
suffix:semicolon
)brace
DECL|function|cache_tree_matches_traversal
r_int
id|cache_tree_matches_traversal
c_func
(paren
r_struct
id|cache_tree
op_star
id|root
comma
r_struct
id|name_entry
op_star
id|ent
comma
r_struct
id|traverse_info
op_star
id|info
)paren
(brace
r_struct
id|cache_tree
op_star
id|it
suffix:semicolon
id|it
op_assign
id|find_cache_tree_from_traversal
c_func
(paren
id|root
comma
id|info
)paren
suffix:semicolon
id|it
op_assign
id|cache_tree_find
c_func
(paren
id|it
comma
id|ent-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|it
op_logical_and
id|it-&gt;entry_count
OG
l_int|0
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|ent-&gt;sha1
comma
id|it-&gt;sha1
)paren
)paren
r_return
id|it-&gt;entry_count
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|update_main_cache_tree
r_int
id|update_main_cache_tree
c_func
(paren
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|the_index.cache_tree
)paren
id|the_index.cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
r_return
id|cache_tree_update
c_func
(paren
op_amp
id|the_index
comma
id|flags
)paren
suffix:semicolon
)brace
eof
