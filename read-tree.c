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
multiline_comment|/*&n; * Two-way merge.&n; *&n; * The rule is: &n; *  - every current entry has to match the old tree&n; *  - if the current entry matches the new tree, we leave it&n; *    as-is. Otherwise we require that it be up-to-date.&n; */
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
comma
op_star
id|b
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
id|old
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|a
op_logical_or
op_logical_neg
id|same
c_func
(paren
id|old
comma
id|a
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b
)paren
r_return
id|merged_entry
c_func
(paren
id|b
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
r_return
l_int|0
suffix:semicolon
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
op_star
id|a
op_assign
op_star
id|old
suffix:semicolon
id|a-&gt;ce_flags
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
id|a
suffix:semicolon
r_return
l_int|1
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
DECL|variable|read_tree_usage
r_static
r_char
op_star
id|read_tree_usage
op_assign
l_string|&quot;git-read-tree (&lt;sha&gt; | -m &lt;sha1&gt; [&lt;sha2&gt; [&lt;sha3&gt;]])&quot;
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
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|stage
)paren
id|die
c_func
(paren
l_string|&quot;-m needs to come first&quot;
)paren
suffix:semicolon
id|read_cache
c_func
(paren
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|active_cache
(braket
id|i
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you need to resolve your current index first&quot;
)paren
suffix:semicolon
)brace
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
id|merge_cache
c_func
(paren
id|active_cache
comma
id|active_nr
comma
id|merge_function
(braket
id|stage
op_minus
l_int|1
)braket
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
