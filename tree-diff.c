multiline_comment|/*&n; * Helper functions for tree diff generation&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;tree.h&quot;
r_static
r_void
id|show_path
c_func
(paren
r_struct
id|strbuf
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
comma
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
)paren
suffix:semicolon
DECL|function|compare_tree_entry
r_static
r_int
id|compare_tree_entry
c_func
(paren
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
comma
r_struct
id|strbuf
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_int
id|mode1
comma
id|mode2
suffix:semicolon
r_const
r_char
op_star
id|path1
comma
op_star
id|path2
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
comma
op_star
id|sha2
suffix:semicolon
r_int
id|cmp
comma
id|pathlen1
comma
id|pathlen2
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
id|t1
comma
op_amp
id|path1
comma
op_amp
id|mode1
)paren
suffix:semicolon
id|sha2
op_assign
id|tree_entry_extract
c_func
(paren
id|t2
comma
op_amp
id|path2
comma
op_amp
id|mode2
)paren
suffix:semicolon
id|pathlen1
op_assign
id|tree_entry_len
c_func
(paren
op_amp
id|t1-&gt;entry
)paren
suffix:semicolon
id|pathlen2
op_assign
id|tree_entry_len
c_func
(paren
op_amp
id|t2-&gt;entry
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE files and directories *always* compare differently,&n;&t; * even when having the same name.&n;&t; */
id|cmp
op_assign
id|base_name_compare
c_func
(paren
id|path1
comma
id|pathlen1
comma
id|mode1
comma
id|path2
comma
id|pathlen2
comma
id|mode2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|show_path
c_func
(paren
id|base
comma
id|opt
comma
id|t1
comma
multiline_comment|/*t2=*/
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
id|show_path
c_func
(paren
id|base
comma
id|opt
comma
multiline_comment|/*t1=*/
l_int|NULL
comma
id|t2
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|FIND_COPIES_HARDER
)paren
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|sha2
)paren
op_logical_and
id|mode1
op_eq
id|mode2
)paren
r_return
l_int|0
suffix:semicolon
id|show_path
c_func
(paren
id|base
comma
id|opt
comma
id|t1
comma
id|t2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* convert path, t1/t2 -&gt; opt-&gt;diff_*() callbacks */
DECL|function|emit_diff
r_static
r_void
id|emit_diff
c_func
(paren
r_struct
id|diff_options
op_star
id|opt
comma
r_struct
id|strbuf
op_star
id|path
comma
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
)paren
(brace
r_int
r_int
id|mode1
op_assign
id|t1
ques
c_cond
id|t1-&gt;entry.mode
suffix:colon
l_int|0
suffix:semicolon
r_int
r_int
id|mode2
op_assign
id|t2
ques
c_cond
id|t2-&gt;entry.mode
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mode1
op_logical_and
id|mode2
)paren
(brace
id|opt
op_member_access_from_pointer
id|change
c_func
(paren
id|opt
comma
id|mode1
comma
id|mode2
comma
id|t1-&gt;entry.sha1
comma
id|t2-&gt;entry.sha1
comma
l_int|1
comma
l_int|1
comma
id|path-&gt;buf
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_int
id|addremove
suffix:semicolon
r_if
c_cond
(paren
id|mode2
)paren
(brace
id|addremove
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|sha1
op_assign
id|t2-&gt;entry.sha1
suffix:semicolon
id|mode
op_assign
id|mode2
suffix:semicolon
)brace
r_else
(brace
id|addremove
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|sha1
op_assign
id|t1-&gt;entry.sha1
suffix:semicolon
id|mode
op_assign
id|mode1
suffix:semicolon
)brace
id|opt
op_member_access_from_pointer
id|add_remove
c_func
(paren
id|opt
comma
id|addremove
comma
id|mode
comma
id|sha1
comma
l_int|1
comma
id|path-&gt;buf
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* new path should be added to diff&n; *&n; * 3 cases on how/when it should be called and behaves:&n; *&n; *&t;!t1,  t2&t;-&gt; path added, parent lacks it&n; *&t; t1, !t2&t;-&gt; path removed from parent&n; *&t; t1,  t2&t;-&gt; path modified&n; */
DECL|function|show_path
r_static
r_void
id|show_path
c_func
(paren
r_struct
id|strbuf
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
comma
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
)paren
(brace
r_int
id|mode
suffix:semicolon
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_int
id|old_baselen
op_assign
id|base-&gt;len
suffix:semicolon
r_int
id|isdir
comma
id|recurse
op_assign
l_int|0
comma
id|emitthis
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* at least something has to be valid */
m_assert
(paren
id|t1
op_logical_or
id|t2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t2
)paren
(brace
multiline_comment|/* path present in resulting tree */
id|tree_entry_extract
c_func
(paren
id|t2
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|pathlen
op_assign
id|tree_entry_len
c_func
(paren
op_amp
id|t2-&gt;entry
)paren
suffix:semicolon
id|isdir
op_assign
id|S_ISDIR
c_func
(paren
id|mode
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * a path was removed - take path from parent. Also take&n;&t;&t; * mode from parent, to decide on recursion.&n;&t;&t; */
id|tree_entry_extract
c_func
(paren
id|t1
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|pathlen
op_assign
id|tree_entry_len
c_func
(paren
op_amp
id|t1-&gt;entry
)paren
suffix:semicolon
id|isdir
op_assign
id|S_ISDIR
c_func
(paren
id|mode
)paren
suffix:semicolon
id|mode
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|RECURSIVE
)paren
op_logical_and
id|isdir
)paren
(brace
id|recurse
op_assign
l_int|1
suffix:semicolon
id|emitthis
op_assign
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|TREE_IN_RECURSIVE
)paren
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
id|base
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emitthis
)paren
id|emit_diff
c_func
(paren
id|opt
comma
id|base
comma
id|t1
comma
id|t2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recurse
)paren
(brace
id|strbuf_addch
c_func
(paren
id|base
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|t1
ques
c_cond
id|t1-&gt;entry.sha1
suffix:colon
l_int|NULL
comma
id|t2
ques
c_cond
id|t2-&gt;entry.sha1
suffix:colon
l_int|NULL
comma
id|base-&gt;buf
comma
id|opt
)paren
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|base
comma
id|old_baselen
)paren
suffix:semicolon
)brace
DECL|function|skip_uninteresting
r_static
r_void
id|skip_uninteresting
c_func
(paren
r_struct
id|tree_desc
op_star
id|t
comma
r_struct
id|strbuf
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_enum
id|interesting
id|match
suffix:semicolon
r_while
c_loop
(paren
id|t-&gt;size
)paren
(brace
id|match
op_assign
id|tree_entry_interesting
c_func
(paren
op_amp
id|t-&gt;entry
comma
id|base
comma
l_int|0
comma
op_amp
id|opt-&gt;pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match
)paren
(brace
r_if
c_cond
(paren
id|match
op_eq
id|all_entries_not_interesting
)paren
id|t-&gt;size
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|update_tree_entry
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
)brace
DECL|function|diff_tree
r_int
id|diff_tree
c_func
(paren
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
comma
r_const
r_char
op_star
id|base_str
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_struct
id|strbuf
id|base
suffix:semicolon
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base_str
)paren
suffix:semicolon
multiline_comment|/* Enable recursion indefinitely */
id|opt-&gt;pathspec.recursive
op_assign
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|RECURSIVE
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|base
comma
id|PATH_MAX
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|base
comma
id|base_str
comma
id|baselen
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|diff_can_quit_early
c_func
(paren
id|opt
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;pathspec.nr
)paren
(brace
id|skip_uninteresting
c_func
(paren
id|t1
comma
op_amp
id|base
comma
id|opt
)paren
suffix:semicolon
id|skip_uninteresting
c_func
(paren
id|t2
comma
op_amp
id|base
comma
id|opt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|t1-&gt;size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|t2-&gt;size
)paren
r_break
suffix:semicolon
id|show_path
c_func
(paren
op_amp
id|base
comma
id|opt
comma
multiline_comment|/*t1=*/
l_int|NULL
comma
id|t2
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|t2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|t2-&gt;size
)paren
(brace
id|show_path
c_func
(paren
op_amp
id|base
comma
id|opt
comma
id|t1
comma
multiline_comment|/*t2=*/
l_int|NULL
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|t1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cmp
op_assign
id|compare_tree_entry
c_func
(paren
id|t1
comma
id|t2
comma
op_amp
id|base
comma
id|opt
)paren
suffix:semicolon
multiline_comment|/* t1 = t2 */
r_if
c_cond
(paren
id|cmp
op_eq
l_int|0
)paren
(brace
id|update_tree_entry
c_func
(paren
id|t1
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|t2
)paren
suffix:semicolon
)brace
multiline_comment|/* t1 &lt; t2 */
r_else
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|update_tree_entry
c_func
(paren
id|t1
)paren
suffix:semicolon
)brace
multiline_comment|/* t1 &gt; t2 */
r_else
(brace
id|update_tree_entry
c_func
(paren
id|t2
)paren
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Does it look like the resulting diff might be due to a rename?&n; *  - single entry&n; *  - not a valid previous file&n; */
DECL|function|diff_might_be_rename
r_static
r_inline
r_int
id|diff_might_be_rename
c_func
(paren
r_void
)paren
(brace
r_return
id|diff_queued_diff.nr
op_eq
l_int|1
op_logical_and
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|diff_queued_diff.queue
(braket
l_int|0
)braket
op_member_access_from_pointer
id|one
)paren
suffix:semicolon
)brace
DECL|function|try_to_follow_renames
r_static
r_void
id|try_to_follow_renames
c_func
(paren
r_struct
id|tree_desc
op_star
id|t1
comma
r_struct
id|tree_desc
op_star
id|t2
comma
r_const
r_char
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_struct
id|diff_options
id|diff_opts
suffix:semicolon
r_struct
id|diff_queue_struct
op_star
id|q
op_assign
op_amp
id|diff_queued_diff
suffix:semicolon
r_struct
id|diff_filepair
op_star
id|choice
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * follow-rename code is very specific, we need exactly one&n;&t; * path. Magic that matches more than one path is not&n;&t; * supported.&n;&t; */
id|GUARD_PATHSPEC
c_func
(paren
op_amp
id|opt-&gt;pathspec
comma
id|PATHSPEC_FROMTOP
op_or
id|PATHSPEC_LITERAL
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * We should reject wildcards as well. Unfortunately we&n;&t; * haven&squot;t got a reliable way to detect that &squot;foo&bslash;*bar&squot; in&n;&t; * fact has no wildcards. nowildcard_len is merely a hint for&n;&t; * optimization. Let it slip for now until wildmatch is taught&n;&t; * about dry-run mode and returns wildcard info.&n;&t; */
r_if
c_cond
(paren
id|opt-&gt;pathspec.has_wildcard
)paren
id|die
c_func
(paren
l_string|&quot;BUG:%s:%d: wildcards are not supported&quot;
comma
id|__FILE__
comma
id|__LINE__
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Remove the file creation entry from the diff queue, and remember it */
id|choice
op_assign
id|q-&gt;queue
(braket
l_int|0
)braket
suffix:semicolon
id|q-&gt;nr
op_assign
l_int|0
suffix:semicolon
id|diff_setup
c_func
(paren
op_amp
id|diff_opts
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|diff_opts
comma
id|RECURSIVE
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|diff_opts
comma
id|FIND_COPIES_HARDER
)paren
suffix:semicolon
id|diff_opts.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
id|diff_opts.single_follow
op_assign
id|opt-&gt;pathspec.items
(braket
l_int|0
)braket
dot
id|match
suffix:semicolon
id|diff_opts.break_opt
op_assign
id|opt-&gt;break_opt
suffix:semicolon
id|diff_opts.rename_score
op_assign
id|opt-&gt;rename_score
suffix:semicolon
id|diff_setup_done
c_func
(paren
op_amp
id|diff_opts
)paren
suffix:semicolon
id|diff_tree
c_func
(paren
id|t1
comma
id|t2
comma
id|base
comma
op_amp
id|diff_opts
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|diff_opts
)paren
suffix:semicolon
id|free_pathspec
c_func
(paren
op_amp
id|diff_opts.pathspec
)paren
suffix:semicolon
multiline_comment|/* Go through the new set of filepairing, and see if we find a more interesting one */
id|opt-&gt;found_follow
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Found a source? Not only do we use that for the new&n;&t;&t; * diff_queued_diff, we will also use that as the path in&n;&t;&t; * the future!&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|p-&gt;status
op_eq
l_char|&squot;R&squot;
op_logical_or
id|p-&gt;status
op_eq
l_char|&squot;C&squot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;two-&gt;path
comma
id|opt-&gt;pathspec.items
(braket
l_int|0
)braket
dot
id|match
)paren
)paren
(brace
r_const
r_char
op_star
id|path
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Switch the file-pairs around */
id|q-&gt;queue
(braket
id|i
)braket
op_assign
id|choice
suffix:semicolon
id|choice
op_assign
id|p
suffix:semicolon
multiline_comment|/* Update the path we use from now on.. */
id|path
(braket
l_int|0
)braket
op_assign
id|p-&gt;one-&gt;path
suffix:semicolon
id|path
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|free_pathspec
c_func
(paren
op_amp
id|opt-&gt;pathspec
)paren
suffix:semicolon
id|parse_pathspec
c_func
(paren
op_amp
id|opt-&gt;pathspec
comma
id|PATHSPEC_ALL_MAGIC
op_amp
op_complement
id|PATHSPEC_LITERAL
comma
id|PATHSPEC_LITERAL_PATH
comma
l_string|&quot;&quot;
comma
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The caller expects us to return a set of vanilla&n;&t;&t;&t; * filepairs to let a later call to diffcore_std()&n;&t;&t;&t; * it makes to sort the renames out (among other&n;&t;&t;&t; * things), but we already have found renames&n;&t;&t;&t; * ourselves; signal diffcore_std() not to muck with&n;&t;&t;&t; * rename information.&n;&t;&t;&t; */
id|opt-&gt;found_follow
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Then, discard all the non-relevant file pairs...&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
id|diff_free_filepair
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * .. and re-instate the one we want (which might be either the&n;&t; * original one, or the rename/copy we found)&n;&t; */
id|q-&gt;queue
(braket
l_int|0
)braket
op_assign
id|choice
suffix:semicolon
id|q-&gt;nr
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|diff_tree_sha1
r_int
id|diff_tree_sha1
c_func
(paren
r_const
r_int
r_char
op_star
id|old
comma
r_const
r_int
r_char
op_star
r_new
comma
r_const
r_char
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_void
op_star
id|tree1
comma
op_star
id|tree2
suffix:semicolon
r_struct
id|tree_desc
id|t1
comma
id|t2
suffix:semicolon
r_int
r_int
id|size1
comma
id|size2
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|tree1
op_assign
id|fill_tree_descriptor
c_func
(paren
op_amp
id|t1
comma
id|old
)paren
suffix:semicolon
id|tree2
op_assign
id|fill_tree_descriptor
c_func
(paren
op_amp
id|t2
comma
r_new
)paren
suffix:semicolon
id|size1
op_assign
id|t1.size
suffix:semicolon
id|size2
op_assign
id|t2.size
suffix:semicolon
id|retval
op_assign
id|diff_tree
c_func
(paren
op_amp
id|t1
comma
op_amp
id|t2
comma
id|base
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|base
op_logical_and
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|FOLLOW_RENAMES
)paren
op_logical_and
id|diff_might_be_rename
c_func
(paren
)paren
)paren
(brace
id|init_tree_desc
c_func
(paren
op_amp
id|t1
comma
id|tree1
comma
id|size1
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t2
comma
id|tree2
comma
id|size2
)paren
suffix:semicolon
id|try_to_follow_renames
c_func
(paren
op_amp
id|t1
comma
op_amp
id|t2
comma
id|base
comma
id|opt
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|tree1
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree2
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|diff_root_tree_sha1
r_int
id|diff_root_tree_sha1
c_func
(paren
r_const
r_int
r_char
op_star
r_new
comma
r_const
r_char
op_star
id|base
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_return
id|diff_tree_sha1
c_func
(paren
l_int|NULL
comma
r_new
comma
id|base
comma
id|opt
)paren
suffix:semicolon
)brace
eof
