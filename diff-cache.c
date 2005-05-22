macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|cached_only
r_static
r_int
id|cached_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_output_format
r_static
r_int
id|diff_output_format
op_assign
id|DIFF_FORMAT_HUMAN
suffix:semicolon
DECL|variable|match_nonexisting
r_static
r_int
id|match_nonexisting
op_assign
l_int|0
suffix:semicolon
DECL|variable|detect_rename
r_static
r_int
id|detect_rename
op_assign
l_int|0
suffix:semicolon
DECL|variable|reverse_diff
r_static
r_int
id|reverse_diff
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_score_opt
r_static
r_int
id|diff_score_opt
op_assign
l_int|0
suffix:semicolon
DECL|variable|pickaxe
r_static
r_const
r_char
op_star
id|pickaxe
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* A file entry went away or appeared */
DECL|function|show_file
r_static
r_void
id|show_file
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|mode
)paren
(brace
id|diff_addremove
c_func
(paren
id|prefix
(braket
l_int|0
)braket
comma
id|ntohl
c_func
(paren
id|mode
)paren
comma
id|sha1
comma
id|ce-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|get_stat_data
r_static
r_int
id|get_stat_data
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_char
op_star
op_star
id|sha1p
comma
r_int
r_int
op_star
id|modep
)paren
(brace
r_int
r_char
op_star
id|sha1
op_assign
id|ce-&gt;sha1
suffix:semicolon
r_int
r_int
id|mode
op_assign
id|ce-&gt;ce_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cached_only
)paren
(brace
r_static
r_int
r_char
id|no_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|changed
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
op_logical_and
id|match_nonexisting
)paren
(brace
op_star
id|sha1p
op_assign
id|sha1
suffix:semicolon
op_star
id|modep
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
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
id|changed
)paren
(brace
id|mode
op_assign
id|create_ce_mode
c_func
(paren
id|st.st_mode
)paren
suffix:semicolon
id|sha1
op_assign
id|no_sha1
suffix:semicolon
)brace
)brace
op_star
id|sha1p
op_assign
id|sha1
suffix:semicolon
op_star
id|modep
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_new_file
r_static
r_void
id|show_new_file
c_func
(paren
r_struct
id|cache_entry
op_star
r_new
)paren
(brace
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* New file in the index: it might actually be different in the working copy */
r_if
c_cond
(paren
id|get_stat_data
c_func
(paren
r_new
comma
op_amp
id|sha1
comma
op_amp
id|mode
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
r_new
comma
id|sha1
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|show_modified
r_static
r_int
id|show_modified
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
r_new
comma
r_int
id|report_missing
)paren
(brace
r_int
r_int
id|mode
comma
id|oldmode
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_if
c_cond
(paren
id|get_stat_data
c_func
(paren
r_new
comma
op_amp
id|sha1
comma
op_amp
id|mode
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|report_missing
)paren
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|old
comma
id|old-&gt;sha1
comma
id|old-&gt;ce_mode
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|oldmode
op_assign
id|old-&gt;ce_mode
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|oldmode
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|sha1
comma
id|old-&gt;sha1
comma
l_int|20
)paren
op_logical_and
id|detect_rename
OL
id|DIFF_DETECT_COPY
)paren
r_return
l_int|0
suffix:semicolon
id|mode
op_assign
id|ntohl
c_func
(paren
id|mode
)paren
suffix:semicolon
id|oldmode
op_assign
id|ntohl
c_func
(paren
id|oldmode
)paren
suffix:semicolon
id|diff_change
c_func
(paren
id|oldmode
comma
id|mode
comma
id|old-&gt;sha1
comma
id|sha1
comma
id|old-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_cache
r_static
r_int
id|diff_cache
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|ac
comma
r_int
id|entries
)paren
(brace
r_while
c_loop
(paren
id|entries
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
op_star
id|ac
suffix:semicolon
r_int
id|same
op_assign
(paren
id|entries
OG
l_int|1
)paren
op_logical_and
id|ce_same_name
c_func
(paren
id|ce
comma
id|ac
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* No stage 1 entry? That means it&squot;s a new file */
r_if
c_cond
(paren
op_logical_neg
id|same
)paren
(brace
id|show_new_file
c_func
(paren
id|ce
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Show difference between old and new */
id|show_modified
c_func
(paren
id|ac
(braket
l_int|1
)braket
comma
id|ce
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* No stage 3 (merge) entry? That means it&squot;s been deleted */
r_if
c_cond
(paren
op_logical_neg
id|same
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|ce
comma
id|ce-&gt;sha1
comma
id|ce-&gt;ce_mode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* We come here with ce pointing at stage 1&n;&t;&t;&t; * (original tree) and ac[1] pointing at stage&n;&t;&t;&t; * 3 (unmerged).  show-modified with&n;&t;&t;&t; * report-mising set to false does not say the&n;&t;&t;&t; * file is deleted but reports true if work&n;&t;&t;&t; * tree does not have it, in which case we&n;&t;&t;&t; * fall through to report the unmerged state.&n;&t;&t;&t; * Otherwise, we show the differences between&n;&t;&t;&t; * the original tree and the work tree.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cached_only
op_logical_and
op_logical_neg
id|show_modified
c_func
(paren
id|ce
comma
id|ac
(braket
l_int|1
)braket
comma
l_int|0
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* fallthru */
r_case
l_int|3
suffix:colon
id|diff_unmerge
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;impossible cache entry stage&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Ignore all the different stages for this file,&n;&t;&t; * we&squot;ve handled the relevant cases now.&n;&t;&t; */
r_do
(brace
id|ac
op_increment
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entries
op_logical_and
id|ce_same_name
c_func
(paren
id|ce
comma
id|ac
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This turns all merge entries into &quot;stage 3&quot;. That guarantees that&n; * when we read in the new tree (into &quot;stage 1&quot;), we won&squot;t lose sight&n; * of the fact that we had unmerged entries.&n; */
DECL|function|mark_merge_entries
r_static
r_void
id|mark_merge_entries
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|ce-&gt;ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_STAGEMASK
)paren
suffix:semicolon
)brace
)brace
DECL|variable|diff_cache_usage
r_static
r_char
op_star
id|diff_cache_usage
op_assign
l_string|&quot;git-diff-cache [-p] [-r] [-z] [-m] [-M] [-C] [-R] [-S&lt;string&gt;] [--cached] &lt;tree-ish&gt;&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
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
)paren
(brace
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
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
id|ret
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argc
OG
l_int|2
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
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
l_string|&quot;-r&quot;
)paren
)paren
(brace
multiline_comment|/* We accept the -r flag just to look like git-diff-tree */
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
l_string|&quot;-p&quot;
)paren
)paren
(brace
id|diff_output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-M&quot;
comma
l_int|2
)paren
)paren
(brace
id|detect_rename
op_assign
id|DIFF_DETECT_RENAME
suffix:semicolon
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-C&quot;
comma
l_int|2
)paren
)paren
(brace
id|detect_rename
op_assign
id|DIFF_DETECT_COPY
suffix:semicolon
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
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
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|diff_output_format
op_assign
id|DIFF_FORMAT_MACHINE
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
l_string|&quot;-R&quot;
)paren
)paren
(brace
id|reverse_diff
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
l_string|&quot;-S&quot;
)paren
)paren
(brace
id|pickaxe
op_assign
id|arg
op_plus
l_int|2
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
l_string|&quot;-m&quot;
)paren
)paren
(brace
id|match_nonexisting
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
l_string|&quot;--cached&quot;
)paren
)paren
(brace
id|cached_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|diff_cache_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
l_int|2
op_logical_or
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|tree_sha1
)paren
)paren
id|usage
c_func
(paren
id|diff_cache_usage
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
multiline_comment|/* The rest is for paths restriction. */
id|diff_setup
c_func
(paren
id|reverse_diff
)paren
suffix:semicolon
id|mark_merge_entries
c_func
(paren
)paren
suffix:semicolon
id|tree
op_assign
id|read_object_with_reference
c_func
(paren
id|tree_sha1
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
id|tree
)paren
id|die
c_func
(paren
l_string|&quot;bad tree object %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_tree
c_func
(paren
id|tree
comma
id|size
comma
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree object %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|ret
op_assign
id|diff_cache
c_func
(paren
id|active_cache
comma
id|active_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|detect_rename
)paren
id|diffcore_rename
c_func
(paren
id|detect_rename
comma
id|diff_score_opt
)paren
suffix:semicolon
id|diffcore_prune
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pickaxe
)paren
id|diffcore_pickaxe
c_func
(paren
id|pickaxe
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_le
id|argc
)paren
id|diffcore_pathspec
c_func
(paren
id|argv
op_plus
l_int|1
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
id|diff_output_format
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
