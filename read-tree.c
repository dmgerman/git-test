multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|stage
r_static
r_int
id|stage
op_assign
l_int|0
suffix:semicolon
DECL|variable|update
r_static
r_int
id|update
op_assign
l_int|0
suffix:semicolon
DECL|function|unpack_tree
r_static
r_int
id|unpack_tree
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|buffer
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
id|buffer
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
id|read_tree
c_func
(paren
id|buffer
comma
id|size
comma
id|stage
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|path_matches
r_static
r_int
id|path_matches
c_func
(paren
r_struct
id|cache_entry
op_star
id|a
comma
r_struct
id|cache_entry
op_star
id|b
)paren
(brace
r_int
id|len
op_assign
id|ce_namelen
c_func
(paren
id|a
)paren
suffix:semicolon
r_return
id|ce_namelen
c_func
(paren
id|b
)paren
op_eq
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|same
r_static
r_int
id|same
c_func
(paren
r_struct
id|cache_entry
op_star
id|a
comma
r_struct
id|cache_entry
op_star
id|b
)paren
(brace
r_return
id|a-&gt;ce_mode
op_eq
id|b-&gt;ce_mode
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
suffix:semicolon
)brace
multiline_comment|/*&n; * This removes all trivial merges that don&squot;t change the tree&n; * and collapses them to state 0.&n; */
DECL|function|merge_entries
r_static
r_struct
id|cache_entry
op_star
id|merge_entries
c_func
(paren
r_struct
id|cache_entry
op_star
id|a
comma
r_struct
id|cache_entry
op_star
id|b
comma
r_struct
id|cache_entry
op_star
id|c
)paren
(brace
multiline_comment|/*&n;&t; * Ok, all three entries describe the same&n;&t; * filename, but maybe the contents or file&n;&t; * mode have changed?&n;&t; *&n;&t; * The trivial cases end up being the ones where two&n;&t; * out of three files are the same:&n;&t; *  - both destinations the same, trivially take either&n;&t; *  - one of the destination versions hasn&squot;t changed,&n;&t; *    take the other.&n;&t; *&n;&t; * The &quot;all entries exactly the same&quot; case falls out as&n;&t; * a special case of any of the &quot;two same&quot; cases.&n;&t; *&n;&t; * Here &quot;a&quot; is &quot;original&quot;, and &quot;b&quot; and &quot;c&quot; are the two&n;&t; * trees we are merging.&n;&t; */
r_if
c_cond
(paren
id|a
op_logical_and
id|b
op_logical_and
id|c
)paren
(brace
r_if
c_cond
(paren
id|same
c_func
(paren
id|b
comma
id|c
)paren
)paren
r_return
id|c
suffix:semicolon
r_if
c_cond
(paren
id|same
c_func
(paren
id|a
comma
id|b
)paren
)paren
r_return
id|c
suffix:semicolon
r_if
c_cond
(paren
id|same
c_func
(paren
id|a
comma
id|c
)paren
)paren
r_return
id|b
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * When a CE gets turned into an unmerged entry, we&n; * want it to be up-to-date&n; */
DECL|function|verify_uptodate
r_static
r_void
id|verify_uptodate
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
)paren
(brace
r_int
id|changed
op_assign
id|ce_match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
r_return
suffix:semicolon
id|errno
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Entry &squot;%s&squot; not uptodate. Cannot merge.&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If the old tree contained a CE that isn&squot;t even in the&n; * result, that&squot;s always a problem, regardless of whether&n; * it&squot;s up-to-date or not (ie it can be a file that we&n; * have updated but not committed yet).&n; */
DECL|function|reject_merge
r_static
r_void
id|reject_merge
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Entry &squot;%s&squot; would be overwritten by merge. Cannot merge.&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|merged_entry_internal
r_static
r_int
id|merged_entry_internal
c_func
(paren
r_struct
id|cache_entry
op_star
id|merge
comma
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
comma
r_int
id|allow_dirty
)paren
(brace
id|merge-&gt;ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_UPDATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
)paren
(brace
multiline_comment|/*&n;&t;&t; * See if we can re-use the old CE directly?&n;&t;&t; * That way we get the uptodate stat info.&n;&t;&t; *&n;&t;&t; * This also removes the UPDATE flag on&n;&t;&t; * a match.&n;&t;&t; */
r_if
c_cond
(paren
id|same
c_func
(paren
id|old
comma
id|merge
)paren
)paren
(brace
op_star
id|merge
op_assign
op_star
id|old
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|allow_dirty
)paren
(brace
id|verify_uptodate
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
)brace
id|merge-&gt;ce_flags
op_and_assign
op_complement
id|htons
c_func
(paren
id|CE_STAGEMASK
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|merge
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|merged_entry_allow_dirty
r_static
r_int
id|merged_entry_allow_dirty
c_func
(paren
r_struct
id|cache_entry
op_star
id|merge
comma
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
)paren
(brace
r_return
id|merged_entry_internal
c_func
(paren
id|merge
comma
id|old
comma
id|dst
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|merged_entry
r_static
r_int
id|merged_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|merge
comma
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
)paren
(brace
r_return
id|merged_entry_internal
c_func
(paren
id|merge
comma
id|old
comma
id|dst
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|deleted_entry
r_static
r_int
id|deleted_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|old
)paren
id|verify_uptodate
c_func
(paren
id|old
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
l_int|0
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|ce
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|causes_df_conflict
r_static
r_int
id|causes_df_conflict
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
id|stage
comma
r_struct
id|cache_entry
op_star
op_star
id|dst_
comma
r_struct
id|cache_entry
op_star
op_star
id|next_
comma
r_int
id|tail
)paren
(brace
multiline_comment|/* This is called during the merge operation and walking&n;&t; * the active_cache[] array is messy, because it is in the&n;&t; * middle of overlapping copy operation.  The invariants&n;&t; * are:&n;&t; * (1) active_cache points at the first (zeroth) entry.&n;&t; * (2) up to dst pointer are resolved entries.&n;&t; * (3) from the next pointer (head-inclusive) to the tail&n;&t; *     of the active_cache array have the remaining paths&n;&t; *     to be processed.  There can be a gap between dst&n;&t; *     and next.  Note that next is called &quot;src&quot; in the&n;&t; *     merge_cache() function, and tail is the original&n;&t; *     end of active_cache array when merge_cache() started.&n;&t; * (4) the path corresponding to *ce is not found in (2)&n;&t; *     or (3).  It is in the gap.&n;&t; *&n;&t; *  active_cache -----......+++++++++++++.&n;&t; *                    ^dst  ^next        ^tail&n;&t; */
r_int
id|i
comma
id|next
comma
id|dst
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
id|ce-&gt;name
suffix:semicolon
r_int
id|namelen
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
id|next
op_assign
id|next_
id|active_cache
suffix:semicolon
id|dst
op_assign
id|dst_
id|active_cache
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
id|tail
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|entlen
comma
id|len
suffix:semicolon
r_const
r_char
op_star
id|one
comma
op_star
id|two
suffix:semicolon
r_if
c_cond
(paren
id|dst
op_le
id|i
op_logical_and
id|i
OL
id|next
)paren
r_continue
suffix:semicolon
id|ce
op_assign
id|active_cache
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
op_ne
id|stage
)paren
r_continue
suffix:semicolon
multiline_comment|/* If ce-&gt;name is a prefix of path, then path is a file&n;&t;&t; * that hangs underneath ce-&gt;name, which is bad.&n;&t;&t; * If path is a prefix of ce-&gt;name, then it is the&n;&t;&t; * other way around which also is bad.&n;&t;&t; */
id|entlen
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
id|namelen
op_eq
id|entlen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OL
id|entlen
)paren
(brace
id|len
op_assign
id|namelen
suffix:semicolon
id|one
op_assign
id|path
suffix:semicolon
id|two
op_assign
id|ce-&gt;name
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|entlen
suffix:semicolon
id|one
op_assign
id|ce-&gt;name
suffix:semicolon
id|two
op_assign
id|path
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|one
comma
id|two
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|two
(braket
id|len
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|threeway_merge
r_static
r_int
id|threeway_merge
c_func
(paren
r_struct
id|cache_entry
op_star
id|stages
(braket
l_int|4
)braket
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
comma
r_struct
id|cache_entry
op_star
op_star
id|next
comma
r_int
id|tail
)paren
(brace
r_struct
id|cache_entry
op_star
id|old
op_assign
id|stages
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|a
op_assign
id|stages
(braket
l_int|1
)braket
comma
op_star
id|b
op_assign
id|stages
(braket
l_int|2
)braket
comma
op_star
id|c
op_assign
id|stages
(braket
l_int|3
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|merge
suffix:semicolon
r_int
id|count
suffix:semicolon
multiline_comment|/* #5ALT */
r_if
c_cond
(paren
op_logical_neg
id|a
op_logical_and
id|b
op_logical_and
id|c
op_logical_and
id|same
c_func
(paren
id|b
comma
id|c
)paren
)paren
(brace
r_if
c_cond
(paren
id|old
op_logical_and
op_logical_neg
id|same
c_func
(paren
id|b
comma
id|old
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|merged_entry_allow_dirty
c_func
(paren
id|b
comma
id|old
comma
id|dst
)paren
suffix:semicolon
)brace
multiline_comment|/* #2ALT and #3ALT */
r_if
c_cond
(paren
op_logical_neg
id|a
op_logical_and
(paren
op_logical_neg
op_logical_neg
id|b
op_ne
op_logical_neg
op_logical_neg
id|c
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The reason we need to worry about directory/file&n;&t;&t; * conflicts only in #2ALT and #3ALT case is this:&n;&t;&t; *&n;&t;&t; * (1) For all other cases that read-tree internally&n;&t;&t; *     resolves a path, we always have such a path in&n;&t;&t; *     *both* stage2 and stage3 when we begin.&n;&t;&t; *     Traditionally, the behaviour has been even&n;&t;&t; *     stricter and we did not resolve a path without&n;&t;&t; *     initially being in all of stage1, 2, and 3.&n;&t;&t; *&n;&t;&t; * (2) When read-tree finishes, all resolved paths (i.e.&n;&t;&t; *     the paths that are in stage0) must have come from&n;&t;&t; *     either stage2 or stage3.  It is not possible to&n;&t;&t; *     have a stage0 path as a result of a merge if&n;&t;&t; *     neither stage2 nor stage3 had that path.&n;&t;&t; *&n;&t;&t; * (3) It is guaranteed that just after reading the&n;&t;&t; *     stages, each stage cannot have directory/file&n;&t;&t; *     conflicts on its own, because they are populated&n;&t;&t; *     by reading hierarchy of a tree.  Combined with&n;&t;&t; *     (1) and (2) above, this means that no matter what&n;&t;&t; *     combination of paths we take from stage2 and&n;&t;&t; *     stage3 as a result of a merge, they cannot cause&n;&t;&t; *     a directory/file conflict situation (otherwise&n;&t;&t; *     the &quot;guilty&quot; path would have already had such a&n;&t;&t; *     conflict in the original stage, either stage2&n;&t;&t; *     or stage3).  Although its stage2 is synthesized&n;&t;&t; *     by overlaying the current index on top of &quot;our&n;&t;&t; *     head&quot; tree, --emu23 case also has this guarantee,&n;&t;&t; *     by calling add_cache_entry() to create such stage2&n;&t;&t; *     entries.&n;&t;&t; *&n;&t;&t; * (4) Only #2ALT and #3ALT lack the guarantee (1).&n;&t;&t; *     They resolve paths that exist only in stage2&n;&t;&t; *     or stage3.  The stage2 tree may have a file DF&n;&t;&t; *     while stage3 tree may have a file DF/DF.  If&n;&t;&t; *     #2ALT and #3ALT rules happen to apply to both&n;&t;&t; *     of them, we would end up having DF (coming from&n;&t;&t; *     stage2) and DF/DF (from stage3) in the result.&n;&t;&t; *     When we attempt to resolve a path that exists&n;&t;&t; *     only in stage2, we need to make sure there is&n;&t;&t; *     no path that would conflict with it in stage3&n;&t;&t; *     and vice versa.&n;&t;&t; */
r_if
c_cond
(paren
id|c
)paren
(brace
multiline_comment|/* #2ALT */
r_if
c_cond
(paren
op_logical_neg
id|causes_df_conflict
c_func
(paren
id|c
comma
l_int|2
comma
id|dst
comma
id|next
comma
id|tail
)paren
op_logical_and
(paren
op_logical_neg
id|old
op_logical_or
id|same
c_func
(paren
id|c
comma
id|old
)paren
)paren
)paren
r_return
id|merged_entry_allow_dirty
c_func
(paren
id|c
comma
id|old
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* #3ALT */
r_if
c_cond
(paren
op_logical_neg
id|causes_df_conflict
c_func
(paren
id|b
comma
l_int|3
comma
id|dst
comma
id|next
comma
id|tail
)paren
op_logical_and
(paren
op_logical_neg
id|old
op_logical_or
id|same
c_func
(paren
id|b
comma
id|old
)paren
)paren
)paren
r_return
id|merged_entry_allow_dirty
c_func
(paren
id|b
comma
id|old
comma
id|dst
)paren
suffix:semicolon
)brace
multiline_comment|/* otherwise we will apply the original rule */
)brace
multiline_comment|/* #14ALT */
r_if
c_cond
(paren
id|a
op_logical_and
id|b
op_logical_and
id|c
op_logical_and
id|same
c_func
(paren
id|a
comma
id|b
)paren
op_logical_and
op_logical_neg
id|same
c_func
(paren
id|a
comma
id|c
)paren
)paren
(brace
r_if
c_cond
(paren
id|old
op_logical_and
id|same
c_func
(paren
id|old
comma
id|c
)paren
)paren
r_return
id|merged_entry_allow_dirty
c_func
(paren
id|c
comma
id|old
comma
id|dst
)paren
suffix:semicolon
multiline_comment|/* otherwise the regular rule applies */
)brace
multiline_comment|/*&n;&t; * If we have an entry in the index cache (&quot;old&quot;), then we want&n;&t; * to make sure that it matches any entries in stage 2 (&quot;first&n;&t; * branch&quot;, aka &quot;b&quot;).&n;&t; */
r_if
c_cond
(paren
id|old
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|b
op_logical_or
op_logical_neg
id|same
c_func
(paren
id|old
comma
id|b
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|merge
op_assign
id|merge_entries
c_func
(paren
id|a
comma
id|b
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|merge
)paren
r_return
id|merged_entry
c_func
(paren
id|merge
comma
id|old
comma
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
)paren
id|verify_uptodate
c_func
(paren
id|old
)paren
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|a
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|a
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|b
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Two-way merge.&n; *&n; * The rule is to &quot;carry forward&quot; what is in the index without losing&n; * information across a &quot;fast forward&quot;, favoring a successful merge&n; * over a merge failure when it makes sense.  For details of the&n; * &quot;carry forward&quot; rule, please see &lt;Documentation/git-read-tree.txt&gt;.&n; *&n; */
DECL|function|twoway_merge
r_static
r_int
id|twoway_merge
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|src
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
comma
r_struct
id|cache_entry
op_star
op_star
id|next
comma
r_int
id|tail
)paren
(brace
r_struct
id|cache_entry
op_star
id|current
op_assign
id|src
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|oldtree
op_assign
id|src
(braket
l_int|1
)braket
comma
op_star
id|newtree
op_assign
id|src
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
l_int|3
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|current
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|oldtree
op_logical_and
op_logical_neg
id|newtree
)paren
op_logical_or
multiline_comment|/* 4 and 5 */
(paren
op_logical_neg
id|oldtree
op_logical_and
id|newtree
op_logical_and
id|same
c_func
(paren
id|current
comma
id|newtree
)paren
)paren
op_logical_or
multiline_comment|/* 6 and 7 */
(paren
id|oldtree
op_logical_and
id|newtree
op_logical_and
id|same
c_func
(paren
id|oldtree
comma
id|newtree
)paren
)paren
op_logical_or
multiline_comment|/* 14 and 15 */
(paren
id|oldtree
op_logical_and
id|newtree
op_logical_and
op_logical_neg
id|same
c_func
(paren
id|oldtree
comma
id|newtree
)paren
op_logical_and
multiline_comment|/* 18 and 19*/
id|same
c_func
(paren
id|current
comma
id|newtree
)paren
)paren
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|current
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oldtree
op_logical_and
op_logical_neg
id|newtree
op_logical_and
id|same
c_func
(paren
id|current
comma
id|oldtree
)paren
)paren
(brace
multiline_comment|/* 10 or 11 */
r_return
id|deleted_entry
c_func
(paren
id|oldtree
comma
id|current
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oldtree
op_logical_and
id|newtree
op_logical_and
id|same
c_func
(paren
id|current
comma
id|oldtree
)paren
op_logical_and
op_logical_neg
id|same
c_func
(paren
id|current
comma
id|newtree
)paren
)paren
(brace
multiline_comment|/* 20 or 21 */
r_return
id|merged_entry
c_func
(paren
id|newtree
comma
id|current
comma
id|dst
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* all other failures */
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|newtree
)paren
r_return
id|merged_entry
c_func
(paren
id|newtree
comma
id|current
comma
id|dst
)paren
suffix:semicolon
r_else
r_return
id|deleted_entry
c_func
(paren
id|oldtree
comma
id|current
comma
id|dst
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Two-way merge emulated with three-way merge.&n; *&n; * This treats &quot;read-tree -m H M&quot; by transforming it internally&n; * into &quot;read-tree -m H I+H M&quot;, where I+H is a tree that would&n; * contain the contents of the current index file, overlayed on&n; * top of H.  Unlike the traditional two-way merge, this leaves&n; * the stages in the resulting index file and lets the user resolve&n; * the merge conflicts using standard tools for three-way merge.&n; *&n; * This function is just to set-up such an arrangement, and the&n; * actual merge uses threeway_merge() function.&n; */
DECL|function|setup_emu23
r_static
r_void
id|setup_emu23
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* stage0 contains I, stage1 H, stage2 M.&n;&t; * move stage2 to stage3, and create stage2 entries&n;&t; * by scanning stage0 and stage1 entries.&n;&t; */
r_int
id|i
comma
id|namelen
comma
id|size
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
comma
op_star
id|stage2
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ce
op_assign
id|active_cache
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
op_ne
l_int|2
)paren
r_continue
suffix:semicolon
multiline_comment|/* hoist them up to stage 3 */
id|namelen
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|create_ce_flags
c_func
(paren
id|namelen
comma
l_int|3
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ce
op_assign
id|active_cache
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
OG
l_int|1
)paren
r_continue
suffix:semicolon
id|namelen
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|namelen
)paren
suffix:semicolon
id|stage2
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|stage2
comma
id|ce
comma
id|size
)paren
suffix:semicolon
id|stage2-&gt;ce_flags
op_assign
id|create_ce_flags
c_func
(paren
id|namelen
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_cache_entry
c_func
(paren
id|stage2
comma
id|ADD_CACHE_OK_TO_ADD
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;cannot merge index and our head tree&quot;
)paren
suffix:semicolon
multiline_comment|/* We are done with this name, so skip to next name */
r_while
c_loop
(paren
id|i
OL
id|active_nr
op_logical_and
id|ce_namelen
c_func
(paren
id|active_cache
(braket
id|i
)braket
)paren
op_eq
id|namelen
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|ce-&gt;name
comma
id|namelen
)paren
)paren
id|i
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
multiline_comment|/* compensate for the loop control */
)brace
)brace
multiline_comment|/*&n; * One-way merge.&n; *&n; * The rule is:&n; * - take the stat information from stage0, take the data from stage1&n; */
DECL|function|oneway_merge
r_static
r_int
id|oneway_merge
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|src
comma
r_struct
id|cache_entry
op_star
op_star
id|dst
comma
r_struct
id|cache_entry
op_star
op_star
id|next
comma
r_int
id|tail
)paren
(brace
r_struct
id|cache_entry
op_star
id|old
op_assign
id|src
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|a
op_assign
id|src
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_logical_or
id|src
(braket
l_int|3
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|old
op_logical_and
id|same
c_func
(paren
id|old
comma
id|a
)paren
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|old
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|merged_entry
c_func
(paren
id|a
comma
l_int|NULL
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|check_updates
r_static
r_void
id|check_updates
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|src
comma
r_int
id|nr
)paren
(brace
r_static
r_struct
id|checkout
id|state
op_assign
(brace
dot
id|base_dir
op_assign
l_string|&quot;&quot;
comma
dot
id|force
op_assign
l_int|1
comma
dot
id|quiet
op_assign
l_int|1
comma
dot
id|refresh_cache
op_assign
l_int|1
comma
)brace
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|htons
c_func
(paren
id|CE_UPDATE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nr
op_decrement
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce-&gt;ce_mode
)paren
(brace
r_if
c_cond
(paren
id|update
)paren
id|unlink
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|mask
)paren
(brace
id|ce-&gt;ce_flags
op_and_assign
op_complement
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|update
)paren
id|checkout_entry
c_func
(paren
id|ce
comma
op_amp
id|state
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|typedef|merge_fn_t
r_typedef
r_int
(paren
op_star
id|merge_fn_t
)paren
(paren
r_struct
id|cache_entry
op_star
op_star
comma
r_struct
id|cache_entry
op_star
op_star
comma
r_struct
id|cache_entry
op_star
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|merge_cache
r_static
r_void
id|merge_cache
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|src
comma
r_int
id|nr
comma
id|merge_fn_t
id|fn
)paren
(brace
r_struct
id|cache_entry
op_star
op_star
id|dst
op_assign
id|src
suffix:semicolon
r_int
id|tail
op_assign
id|nr
suffix:semicolon
r_while
c_loop
(paren
id|nr
)paren
(brace
r_int
id|entries
suffix:semicolon
r_struct
id|cache_entry
op_star
id|name
comma
op_star
id|ce
comma
op_star
id|stages
(braket
l_int|4
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
id|name
op_assign
id|ce
op_assign
op_star
id|src
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|stage
op_assign
id|ce_stage
c_func
(paren
id|ce
)paren
suffix:semicolon
id|stages
(braket
id|stage
)braket
op_assign
id|ce
suffix:semicolon
id|ce
op_assign
op_star
op_increment
id|src
suffix:semicolon
id|active_nr
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|nr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path_matches
c_func
(paren
id|ce
comma
id|name
)paren
)paren
r_break
suffix:semicolon
)brace
id|entries
op_assign
id|fn
c_func
(paren
id|stages
comma
id|dst
comma
id|src
comma
id|tail
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
id|reject_merge
c_func
(paren
id|name
)paren
suffix:semicolon
id|dst
op_add_assign
id|entries
suffix:semicolon
id|active_nr
op_add_assign
id|entries
suffix:semicolon
)brace
id|check_updates
c_func
(paren
id|active_cache
comma
id|active_nr
)paren
suffix:semicolon
)brace
DECL|function|read_cache_unmerged
r_static
r_int
id|read_cache_unmerged
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|deleted
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|dst
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
id|dst
op_assign
id|active_cache
suffix:semicolon
id|deleted
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
id|active_nr
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
id|active_cache
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
id|deleted
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|deleted
)paren
op_star
id|dst
op_assign
id|ce
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
id|active_nr
op_sub_assign
id|deleted
suffix:semicolon
r_return
id|deleted
suffix:semicolon
)brace
DECL|variable|read_tree_usage
r_static
r_char
op_star
id|read_tree_usage
op_assign
l_string|&quot;git-read-tree (&lt;sha&gt; | -m [-u] &lt;sha1&gt; [&lt;sha2&gt; [&lt;sha3&gt;]])&quot;
suffix:semicolon
DECL|variable|cache_file
r_static
r_struct
id|cache_file
id|cache_file
suffix:semicolon
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
r_int
id|i
comma
id|newfd
comma
id|merge
comma
id|reset
comma
id|emu23
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|newfd
op_assign
id|hold_index_file_for_update
c_func
(paren
op_amp
id|cache_file
comma
id|get_index_file
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newfd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to create new cachefile&quot;
)paren
suffix:semicolon
id|merge
op_assign
l_int|0
suffix:semicolon
id|reset
op_assign
l_int|0
suffix:semicolon
id|emu23
op_assign
l_int|0
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
multiline_comment|/* &quot;-u&quot; means &quot;update&quot;, meaning that a merge will update the working directory */
r_if
c_cond
(paren
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
id|update
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* This differs from &quot;-m&quot; in that we&squot;ll silently ignore unmerged entries */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--reset&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|stage
op_logical_or
id|merge
op_logical_or
id|emu23
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
id|reset
op_assign
l_int|1
suffix:semicolon
id|merge
op_assign
l_int|1
suffix:semicolon
id|stage
op_assign
l_int|1
suffix:semicolon
id|read_cache_unmerged
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* &quot;-m&quot; stands for &quot;merge&quot;, meaning we start in stage 1 */
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
r_if
c_cond
(paren
id|stage
op_logical_or
id|merge
op_logical_or
id|emu23
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache_unmerged
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you need to resolve your current index first&quot;
)paren
suffix:semicolon
id|stage
op_assign
l_int|1
suffix:semicolon
id|merge
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* &quot;-emu23&quot; uses 3-way merge logic to perform fast-forward */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--emu23&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|stage
op_logical_or
id|merge
op_logical_or
id|emu23
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache_unmerged
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you need to resolve your current index first&quot;
)paren
suffix:semicolon
id|merge
op_assign
id|emu23
op_assign
id|stage
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
OL
l_int|0
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stage
OG
l_int|3
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unpack_tree
c_func
(paren
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;failed to unpack tree object %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|stage
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|update
op_logical_and
op_logical_neg
id|merge
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|merge
)paren
(brace
r_static
r_const
id|merge_fn_t
id|merge_function
(braket
)braket
op_assign
(brace
(braket
l_int|1
)braket
op_assign
id|oneway_merge
comma
(braket
l_int|2
)braket
op_assign
id|twoway_merge
comma
(braket
l_int|3
)braket
op_assign
id|threeway_merge
comma
)brace
suffix:semicolon
id|merge_fn_t
id|fn
suffix:semicolon
r_if
c_cond
(paren
id|stage
template_param
l_int|4
)paren
id|die
c_func
(paren
l_string|&quot;just how do you expect me to merge %d trees?&quot;
comma
id|stage
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu23
op_logical_and
id|stage
op_ne
l_int|3
)paren
id|die
c_func
(paren
l_string|&quot;--emu23 takes only two trees&quot;
)paren
suffix:semicolon
id|fn
op_assign
id|merge_function
(braket
id|stage
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|stage
op_eq
l_int|3
op_logical_and
id|emu23
)paren
(brace
id|setup_emu23
c_func
(paren
)paren
suffix:semicolon
id|fn
op_assign
id|merge_function
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|merge_cache
c_func
(paren
id|active_cache
comma
id|active_nr
comma
id|fn
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_index_file
c_func
(paren
op_amp
id|cache_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
