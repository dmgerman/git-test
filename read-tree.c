multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|stage
r_static
r_int
id|stage
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
DECL|variable|lockfile_name
r_static
r_char
op_star
id|lockfile_name
suffix:semicolon
DECL|function|remove_lock_file
r_static
r_void
id|remove_lock_file
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|lockfile_name
)paren
id|unlink
c_func
(paren
id|lockfile_name
)paren
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
multiline_comment|/*&n; * This removes all trivial merges that don&squot;t change the tree&n; * and collapses them to state 0.&n; *&n; * _Any_ other merge is left to user policy.  That includes &quot;both&n; * created the same file&quot;, and &quot;both removed the same file&quot; - which are&n; * trivial, but the user might still want to _note_ it. &n; */
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
r_int
id|len
op_assign
id|ce_namelen
c_func
(paren
id|a
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Are they all the same filename? We won&squot;t do&n;&t; * any name merging&n;&t; */
r_if
c_cond
(paren
id|ce_namelen
c_func
(paren
id|b
)paren
op_ne
id|len
op_logical_or
id|ce_namelen
c_func
(paren
id|c
)paren
op_ne
id|len
op_logical_or
id|memcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
comma
id|len
)paren
op_logical_or
id|memcmp
c_func
(paren
id|a-&gt;name
comma
id|c-&gt;name
comma
id|len
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, all three entries describe the same&n;&t; * filename, but maybe the contents or file&n;&t; * mode have changed?&n;&t; *&n;&t; * The trivial cases end up being the ones where two&n;&t; * out of three files are the same:&n;&t; *  - both destinations the same, trivially take either&n;&t; *  - one of the destination versions hasn&squot;t changed,&n;&t; *    take the other.&n;&t; *&n;&t; * The &quot;all entries exactly the same&quot; case falls out as&n;&t; * a special case of any of the &quot;two same&quot; cases.&n;&t; *&n;&t; * Here &quot;a&quot; is &quot;original&quot;, and &quot;b&quot; and &quot;c&quot; are the two&n;&t; * trees we are merging.&n;&t; */
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
DECL|function|verify_cleared
r_static
r_void
id|verify_cleared
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_if
c_cond
(paren
id|ce
)paren
id|die
c_func
(paren
l_string|&quot;Entry &squot;%s&squot; would be overwritten by merge. Cannot merge.&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|old_match
r_static
r_int
id|old_match
c_func
(paren
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
id|a
)paren
(brace
r_return
id|old
op_logical_and
id|path_matches
c_func
(paren
id|old
comma
id|a
)paren
op_logical_and
id|same
c_func
(paren
id|old
comma
id|a
)paren
suffix:semicolon
)brace
DECL|function|trivially_merge_cache
r_static
r_void
id|trivially_merge_cache
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
r_struct
id|cache_entry
op_star
op_star
id|dst
op_assign
id|src
suffix:semicolon
r_struct
id|cache_entry
op_star
id|old
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|nr
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
comma
op_star
id|result
suffix:semicolon
id|ce
op_assign
id|src
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* We throw away original cache entries except for the stat information */
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|verify_cleared
c_func
(paren
id|old
)paren
suffix:semicolon
id|old
op_assign
id|ce
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|nr
op_decrement
suffix:semicolon
id|active_nr
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
OG
l_int|2
op_logical_and
(paren
id|result
op_assign
id|merge_entries
c_func
(paren
id|ce
comma
id|src
(braket
l_int|1
)braket
comma
id|src
(braket
l_int|2
)braket
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * See if we can re-use the old CE directly?&n;&t;&t;&t; * That way we get the uptodate stat info.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|old_match
c_func
(paren
id|old
comma
id|result
)paren
)paren
(brace
op_star
id|result
op_assign
op_star
id|old
suffix:semicolon
id|old
op_assign
l_int|NULL
suffix:semicolon
)brace
id|ce
op_assign
id|result
suffix:semicolon
id|ce-&gt;ce_flags
op_and_assign
op_complement
id|htons
c_func
(paren
id|CE_STAGEMASK
)paren
suffix:semicolon
id|src
op_add_assign
l_int|2
suffix:semicolon
id|nr
op_sub_assign
l_int|2
suffix:semicolon
id|active_nr
op_sub_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If we had an old entry that we now effectively&n;&t;&t; * overwrite, make sure it wasn&squot;t dirty.&n;&t;&t; */
r_if
c_cond
(paren
id|old_match
c_func
(paren
id|old
comma
id|ce
)paren
)paren
(brace
id|verify_uptodate
c_func
(paren
id|old
)paren
suffix:semicolon
id|old
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|dst
op_increment
op_assign
id|ce
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|nr
op_decrement
suffix:semicolon
)brace
id|verify_cleared
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
DECL|function|merge_stat_info
r_static
r_void
id|merge_stat_info
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
id|cache_entry
id|null_entry
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|dst
op_assign
id|src
suffix:semicolon
r_struct
id|cache_entry
op_star
id|old
op_assign
op_amp
id|null_entry
suffix:semicolon
r_while
c_loop
(paren
id|nr
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
id|ce
op_assign
id|src
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* We throw away original cache entries except for the stat information */
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|old
op_assign
id|ce
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|nr
op_decrement
suffix:semicolon
id|active_nr
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path_matches
c_func
(paren
id|ce
comma
id|old
)paren
op_logical_and
id|same
c_func
(paren
id|ce
comma
id|old
)paren
)paren
op_star
id|ce
op_assign
op_star
id|old
suffix:semicolon
id|ce-&gt;ce_flags
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
id|ce
suffix:semicolon
id|src
op_increment
suffix:semicolon
id|nr
op_decrement
suffix:semicolon
)brace
)brace
DECL|variable|read_tree_usage
r_static
r_char
op_star
id|read_tree_usage
op_assign
l_string|&quot;git-read-tree (&lt;sha&gt; | -m &lt;sha1&gt; [&lt;sha2&gt; &lt;sha3&gt;])&quot;
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
r_static
r_char
id|lockfile
(braket
id|MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
r_const
r_char
op_star
id|indexfile
op_assign
id|get_index_file
c_func
(paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|lockfile
comma
r_sizeof
(paren
id|lockfile
)paren
comma
l_string|&quot;%s.lock&quot;
comma
id|indexfile
)paren
suffix:semicolon
id|newfd
op_assign
id|open
c_func
(paren
id|lockfile
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0600
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
id|atexit
c_func
(paren
id|remove_lock_file
)paren
suffix:semicolon
id|lockfile_name
op_assign
id|lockfile
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
r_switch
c_cond
(paren
id|stage
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* Three-way merge */
id|trivially_merge_cache
c_func
(paren
id|active_cache
comma
id|active_nr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Just read a tree, merge with old cache contents */
id|merge_stat_info
c_func
(paren
id|active_cache
comma
id|active_nr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
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
)brace
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
id|rename
c_func
(paren
id|lockfile
comma
id|indexfile
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
suffix:semicolon
id|lockfile_name
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
