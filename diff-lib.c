multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;submodule.h&quot;
multiline_comment|/*&n; * diff-files&n; */
multiline_comment|/*&n; * Has the work tree entity been removed?&n; *&n; * Return 1 if it was removed from the work tree, 0 if an entity to be&n; * compared with the cache entry ce still exists (the latter includes&n; * the case where a directory that is not a submodule repository&n; * exists for ce that is a submodule -- it is a submodule that is not&n; * checked out).  Return negative for an error.&n; */
DECL|function|check_removed
r_static
r_int
id|check_removed
c_func
(paren
r_const
r_struct
id|cache_entry
op_star
id|ce
comma
r_struct
id|stat
op_star
id|st
)paren
(brace
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|ce-&gt;name
comma
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
op_ne
id|ENOENT
op_logical_and
id|errno
op_ne
id|ENOTDIR
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_symlink_leading_path
c_func
(paren
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st-&gt;st_mode
)paren
)paren
(brace
r_int
r_char
id|sub
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If ce is already a gitlink, we can have a plain&n;&t;&t; * directory (i.e. the submodule is not checked out),&n;&t;&t; * or a checked out submodule.  Either case this is not&n;&t;&t; * a case where something was removed from the work tree,&n;&t;&t; * so we will return 0.&n;&t;&t; *&n;&t;&t; * Otherwise, if the directory is not a submodule&n;&t;&t; * repository, that means ce which was a blob turned into&n;&t;&t; * a directory --- the blob was removed!&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_logical_and
id|resolve_gitlink_ref
c_func
(paren
id|ce-&gt;name
comma
l_string|&quot;HEAD&quot;
comma
id|sub
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|run_diff_files
r_int
id|run_diff_files
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
r_int
id|option
)paren
(brace
r_int
id|entries
comma
id|i
suffix:semicolon
r_int
id|diff_unmerged_stage
op_assign
id|revs-&gt;max_count
suffix:semicolon
r_int
id|silent_on_removed
op_assign
id|option
op_amp
id|DIFF_SILENT_ON_REMOVED
suffix:semicolon
r_int
id|ce_option
op_assign
(paren
(paren
id|option
op_amp
id|DIFF_RACY_IS_MODIFIED
)paren
ques
c_cond
id|CE_MATCH_RACY_IS_DIRTY
suffix:colon
l_int|0
)paren
suffix:semicolon
id|diff_set_mnemonic_prefix
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
l_string|&quot;i/&quot;
comma
l_string|&quot;w/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_unmerged_stage
OL
l_int|0
)paren
id|diff_unmerged_stage
op_assign
l_int|2
suffix:semicolon
id|entries
op_assign
id|active_nr
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
id|stat
id|st
suffix:semicolon
r_int
r_int
id|oldmode
comma
id|newmode
suffix:semicolon
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
r_int
id|changed
suffix:semicolon
r_int
id|dirty_submodule
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|QUICK
)paren
op_logical_and
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|HAS_CHANGES
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_path_match
c_func
(paren
id|ce
comma
id|revs-&gt;prune_data
)paren
)paren
r_continue
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
r_struct
id|combine_diff_path
op_star
id|dpath
suffix:semicolon
r_int
id|num_compare_stages
op_assign
l_int|0
suffix:semicolon
r_int
id|path_len
suffix:semicolon
id|path_len
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
id|dpath
op_assign
id|xmalloc
c_func
(paren
id|combine_diff_path_size
c_func
(paren
l_int|5
comma
id|path_len
)paren
)paren
suffix:semicolon
id|dpath-&gt;path
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|dpath-&gt;parent
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|dpath-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|dpath-&gt;len
op_assign
id|path_len
suffix:semicolon
id|memcpy
c_func
(paren
id|dpath-&gt;path
comma
id|ce-&gt;name
comma
id|path_len
)paren
suffix:semicolon
id|dpath-&gt;path
(braket
id|path_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|hashclr
c_func
(paren
id|dpath-&gt;sha1
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
(paren
id|dpath-&gt;parent
(braket
l_int|0
)braket
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|combine_diff_parent
)paren
op_star
l_int|5
)paren
suffix:semicolon
id|changed
op_assign
id|check_removed
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
id|dpath-&gt;mode
op_assign
id|ce_mode_from_stat
c_func
(paren
id|ce
comma
id|st.st_mode
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|changed
OL
l_int|0
)paren
(brace
id|perror
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
id|silent_on_removed
)paren
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|entries
)paren
(brace
r_struct
id|cache_entry
op_star
id|nce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_int
id|stage
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|nce-&gt;name
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Stage #2 (ours) is the first parent,&n;&t;&t;&t;&t; * stage #3 (theirs) is the second.&n;&t;&t;&t;&t; */
id|stage
op_assign
id|ce_stage
c_func
(paren
id|nce
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_le
id|stage
)paren
(brace
r_int
id|mode
op_assign
id|nce-&gt;ce_mode
suffix:semicolon
id|num_compare_stages
op_increment
suffix:semicolon
id|hashcpy
c_func
(paren
id|dpath-&gt;parent
(braket
id|stage
op_minus
l_int|2
)braket
dot
id|sha1
comma
id|nce-&gt;sha1
)paren
suffix:semicolon
id|dpath-&gt;parent
(braket
id|stage
op_minus
l_int|2
)braket
dot
id|mode
op_assign
id|ce_mode_from_stat
c_func
(paren
id|nce
comma
id|mode
)paren
suffix:semicolon
id|dpath-&gt;parent
(braket
id|stage
op_minus
l_int|2
)braket
dot
id|status
op_assign
id|DIFF_STATUS_MODIFIED
suffix:semicolon
)brace
multiline_comment|/* diff against the proper unmerged stage */
r_if
c_cond
(paren
id|stage
op_eq
id|diff_unmerged_stage
)paren
id|ce
op_assign
id|nce
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Compensate for loop update&n;&t;&t;&t; */
id|i
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;combine_merges
op_logical_and
id|num_compare_stages
op_eq
l_int|2
)paren
(brace
id|show_combined_diff
c_func
(paren
id|dpath
comma
l_int|2
comma
id|revs-&gt;dense_combined_merges
comma
id|revs
)paren
suffix:semicolon
id|free
c_func
(paren
id|dpath
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|free
c_func
(paren
id|dpath
)paren
suffix:semicolon
id|dpath
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Show the diff for the &squot;ce&squot; if we found the one&n;&t;&t;&t; * from the desired stage.&n;&t;&t;&t; */
id|diff_unmerge
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|ce-&gt;name
comma
l_int|0
comma
id|null_sha1
)paren
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
id|diff_unmerged_stage
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ce_uptodate
c_func
(paren
id|ce
)paren
op_logical_or
id|ce_skip_worktree
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* If CE_VALID is set, don&squot;t look at workdir for file removal */
id|changed
op_assign
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_VALID
)paren
ques
c_cond
l_int|0
suffix:colon
id|check_removed
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
r_if
c_cond
(paren
id|changed
OL
l_int|0
)paren
(brace
id|perror
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
id|silent_on_removed
)paren
r_continue
suffix:semicolon
id|diff_addremove
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
l_char|&squot;-&squot;
comma
id|ce-&gt;ce_mode
comma
id|ce-&gt;sha1
comma
id|ce-&gt;name
comma
l_int|0
)paren
suffix:semicolon
r_continue
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
comma
id|ce_option
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_logical_and
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|IGNORE_SUBMODULES
)paren
op_logical_and
(paren
op_logical_neg
id|changed
op_logical_or
(paren
id|revs-&gt;diffopt.output_format
op_amp
id|DIFF_FORMAT_PATCH
)paren
)paren
)paren
(brace
id|dirty_submodule
op_assign
id|is_submodule_modified
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dirty_submodule
)paren
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
(brace
id|ce_mark_uptodate
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|FIND_COPIES_HARDER
)paren
)paren
r_continue
suffix:semicolon
)brace
id|oldmode
op_assign
id|ce-&gt;ce_mode
suffix:semicolon
id|newmode
op_assign
id|ce_mode_from_stat
c_func
(paren
id|ce
comma
id|st.st_mode
)paren
suffix:semicolon
id|diff_change
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|oldmode
comma
id|newmode
comma
id|ce-&gt;sha1
comma
(paren
id|changed
ques
c_cond
id|null_sha1
suffix:colon
id|ce-&gt;sha1
)paren
comma
id|ce-&gt;name
comma
l_int|0
comma
id|dirty_submodule
)paren
suffix:semicolon
)brace
id|diffcore_std
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * diff-index&n; */
multiline_comment|/* A file entry went away or appeared */
DECL|function|diff_index_show_file
r_static
r_void
id|diff_index_show_file
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
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
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|mode
comma
r_int
id|dirty_submodule
)paren
(brace
id|diff_addremove
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|prefix
(braket
l_int|0
)braket
comma
id|mode
comma
id|sha1
comma
id|ce-&gt;name
comma
id|dirty_submodule
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
r_const
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
comma
r_int
id|cached
comma
r_int
id|match_missing
comma
r_int
op_star
id|dirty_submodule
comma
r_struct
id|diff_options
op_star
id|diffopt
)paren
(brace
r_const
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
id|cached
op_logical_and
op_logical_neg
id|ce_uptodate
c_func
(paren
id|ce
)paren
)paren
(brace
r_int
id|changed
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|changed
op_assign
id|check_removed
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
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|changed
)paren
(brace
r_if
c_cond
(paren
id|match_missing
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
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_logical_and
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
id|diffopt
comma
id|IGNORE_SUBMODULES
)paren
op_logical_and
(paren
op_logical_neg
id|changed
op_logical_or
(paren
id|diffopt-&gt;output_format
op_amp
id|DIFF_FORMAT_PATCH
)paren
)paren
)paren
(brace
op_star
id|dirty_submodule
op_assign
id|is_submodule_modified
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dirty_submodule
)paren
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mode
op_assign
id|ce_mode_from_stat
c_func
(paren
id|ce
comma
id|st.st_mode
)paren
suffix:semicolon
id|sha1
op_assign
id|null_sha1
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
id|rev_info
op_star
id|revs
comma
r_struct
id|cache_entry
op_star
r_new
comma
r_int
id|cached
comma
r_int
id|match_missing
)paren
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
id|dirty_submodule
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * New file in the index: it might actually be different in&n;&t; * the working copy.&n;&t; */
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
comma
id|cached
comma
id|match_missing
comma
op_amp
id|dirty_submodule
comma
op_amp
id|revs-&gt;diffopt
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|diff_index_show_file
c_func
(paren
id|revs
comma
l_string|&quot;+&quot;
comma
r_new
comma
id|sha1
comma
id|mode
comma
id|dirty_submodule
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
id|rev_info
op_star
id|revs
comma
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
comma
r_int
id|cached
comma
r_int
id|match_missing
)paren
(brace
r_int
r_int
id|mode
comma
id|oldmode
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|dirty_submodule
op_assign
l_int|0
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
comma
id|cached
comma
id|match_missing
comma
op_amp
id|dirty_submodule
comma
op_amp
id|revs-&gt;diffopt
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
id|diff_index_show_file
c_func
(paren
id|revs
comma
l_string|&quot;-&quot;
comma
id|old
comma
id|old-&gt;sha1
comma
id|old-&gt;ce_mode
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs-&gt;combine_merges
op_logical_and
op_logical_neg
id|cached
op_logical_and
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|old-&gt;sha1
)paren
op_logical_or
id|hashcmp
c_func
(paren
id|old-&gt;sha1
comma
r_new
op_member_access_from_pointer
id|sha1
)paren
)paren
)paren
(brace
r_struct
id|combine_diff_path
op_star
id|p
suffix:semicolon
r_int
id|pathlen
op_assign
id|ce_namelen
c_func
(paren
r_new
)paren
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
id|combine_diff_path_size
c_func
(paren
l_int|2
comma
id|pathlen
)paren
)paren
suffix:semicolon
id|p-&gt;path
op_assign
(paren
r_char
op_star
)paren
op_amp
id|p-&gt;parent
(braket
l_int|2
)braket
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;len
op_assign
id|pathlen
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;path
comma
r_new
op_member_access_from_pointer
id|name
comma
id|pathlen
)paren
suffix:semicolon
id|p-&gt;path
(braket
id|pathlen
)braket
op_assign
l_int|0
suffix:semicolon
id|p-&gt;mode
op_assign
id|mode
suffix:semicolon
id|hashclr
c_func
(paren
id|p-&gt;sha1
)paren
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;parent
comma
l_int|0
comma
l_int|2
op_star
r_sizeof
(paren
r_struct
id|combine_diff_parent
)paren
)paren
suffix:semicolon
id|p-&gt;parent
(braket
l_int|0
)braket
dot
id|status
op_assign
id|DIFF_STATUS_MODIFIED
suffix:semicolon
id|p-&gt;parent
(braket
l_int|0
)braket
dot
id|mode
op_assign
r_new
op_member_access_from_pointer
id|ce_mode
suffix:semicolon
id|hashcpy
c_func
(paren
id|p-&gt;parent
(braket
l_int|0
)braket
dot
id|sha1
comma
r_new
op_member_access_from_pointer
id|sha1
)paren
suffix:semicolon
id|p-&gt;parent
(braket
l_int|1
)braket
dot
id|status
op_assign
id|DIFF_STATUS_MODIFIED
suffix:semicolon
id|p-&gt;parent
(braket
l_int|1
)braket
dot
id|mode
op_assign
id|old-&gt;ce_mode
suffix:semicolon
id|hashcpy
c_func
(paren
id|p-&gt;parent
(braket
l_int|1
)braket
dot
id|sha1
comma
id|old-&gt;sha1
)paren
suffix:semicolon
id|show_combined_diff
c_func
(paren
id|p
comma
l_int|2
comma
id|revs-&gt;dense_combined_merges
comma
id|revs
)paren
suffix:semicolon
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
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
id|hashcmp
c_func
(paren
id|sha1
comma
id|old-&gt;sha1
)paren
op_logical_and
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|FIND_COPIES_HARDER
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|diff_change
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
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
l_int|0
comma
id|dirty_submodule
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets a mix of an existing index and a tree, one pathname entry&n; * at a time. The index entry may be a single stage-0 one, but it could&n; * also be multiple unmerged entries (in which case idx_pos/idx_nr will&n; * give you the position and number of entries in the index).&n; */
DECL|function|do_oneway_diff
r_static
r_void
id|do_oneway_diff
c_func
(paren
r_struct
id|unpack_trees_options
op_star
id|o
comma
r_struct
id|cache_entry
op_star
id|idx
comma
r_struct
id|cache_entry
op_star
id|tree
)paren
(brace
r_struct
id|rev_info
op_star
id|revs
op_assign
id|o-&gt;unpack_data
suffix:semicolon
r_int
id|match_missing
comma
id|cached
suffix:semicolon
multiline_comment|/* if the entry is not checked out, don&squot;t examine work tree */
id|cached
op_assign
id|o-&gt;index_only
op_logical_or
(paren
id|idx
op_logical_and
(paren
(paren
id|idx-&gt;ce_flags
op_amp
id|CE_VALID
)paren
op_logical_or
id|ce_skip_worktree
c_func
(paren
id|idx
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Backward compatibility wart - &quot;diff-index -m&quot; does&n;&t; * not mean &quot;do not ignore merges&quot;, but &quot;match_missing&quot;.&n;&t; *&n;&t; * But with the revision flag parsing, that&squot;s found in&n;&t; * &quot;!revs-&gt;ignore_merges&quot;.&n;&t; */
id|match_missing
op_assign
op_logical_neg
id|revs-&gt;ignore_merges
suffix:semicolon
r_if
c_cond
(paren
id|cached
op_logical_and
id|idx
op_logical_and
id|ce_stage
c_func
(paren
id|idx
)paren
)paren
(brace
id|diff_unmerge
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|idx-&gt;name
comma
id|idx-&gt;ce_mode
comma
id|idx-&gt;sha1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Something added to the tree?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
(brace
id|show_new_file
c_func
(paren
id|revs
comma
id|idx
comma
id|cached
comma
id|match_missing
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Something removed from the tree?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|idx
)paren
(brace
id|diff_index_show_file
c_func
(paren
id|revs
comma
l_string|&quot;-&quot;
comma
id|tree
comma
id|tree-&gt;sha1
comma
id|tree-&gt;ce_mode
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Show difference between old and new */
id|show_modified
c_func
(paren
id|revs
comma
id|tree
comma
id|idx
comma
l_int|1
comma
id|cached
comma
id|match_missing
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The unpack_trees() interface is designed for merging, so&n; * the different source entries are designed primarily for&n; * the source trees, with the old index being really mainly&n; * used for being replaced by the result.&n; *&n; * For diffing, the index is more important, and we only have a&n; * single tree.&n; *&n; * We&squot;re supposed to advance o-&gt;pos to skip what we have already processed.&n; *&n; * This wrapper makes it all more readable, and takes care of all&n; * the fairly complex unpack_trees() semantic requirements, including&n; * the skipping, the path matching, the type conflict cases etc.&n; */
DECL|function|oneway_diff
r_static
r_int
id|oneway_diff
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|src
comma
r_struct
id|unpack_trees_options
op_star
id|o
)paren
(brace
r_struct
id|cache_entry
op_star
id|idx
op_assign
id|src
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|tree
op_assign
id|src
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|rev_info
op_star
id|revs
op_assign
id|o-&gt;unpack_data
suffix:semicolon
multiline_comment|/*&n;&t; * Unpack-trees generates a DF/conflict entry if&n;&t; * there was a directory in the index and a tree&n;&t; * in the tree. From a diff standpoint, that&squot;s a&n;&t; * delete of the tree and a create of the file.&n;&t; */
r_if
c_cond
(paren
id|tree
op_eq
id|o-&gt;df_conflict_entry
)paren
id|tree
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ce_path_match
c_func
(paren
id|idx
ques
c_cond
id|idx
suffix:colon
id|tree
comma
id|revs-&gt;prune_data
)paren
)paren
id|do_oneway_diff
c_func
(paren
id|o
comma
id|idx
comma
id|tree
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|run_diff_index
r_int
id|run_diff_index
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|cached
)paren
(brace
r_struct
id|object
op_star
id|ent
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_const
r_char
op_star
id|tree_name
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
suffix:semicolon
r_struct
id|tree_desc
id|t
suffix:semicolon
id|ent
op_assign
id|revs-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|item
suffix:semicolon
id|tree_name
op_assign
id|revs-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|name
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|ent-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad tree object %s&quot;
comma
id|tree_name
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|opts.head_idx
op_assign
l_int|1
suffix:semicolon
id|opts.index_only
op_assign
id|cached
suffix:semicolon
id|opts.diff_index_cached
op_assign
(paren
id|cached
op_logical_and
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|FIND_COPIES_HARDER
)paren
)paren
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|opts.fn
op_assign
id|oneway_diff
suffix:semicolon
id|opts.unpack_data
op_assign
id|revs
suffix:semicolon
id|opts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.dst_index
op_assign
l_int|NULL
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unpack_trees
c_func
(paren
l_int|1
comma
op_amp
id|t
comma
op_amp
id|opts
)paren
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
id|diff_set_mnemonic_prefix
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
l_string|&quot;c/&quot;
comma
id|cached
ques
c_cond
l_string|&quot;i/&quot;
suffix:colon
l_string|&quot;w/&quot;
)paren
suffix:semicolon
id|diffcore_fix_diff_index
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_diff_cache
r_int
id|do_diff_cache
c_func
(paren
r_const
r_int
r_char
op_star
id|tree_sha1
comma
r_struct
id|diff_options
op_star
id|opt
)paren
(brace
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_struct
id|rev_info
id|revs
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|dst
suffix:semicolon
r_struct
id|cache_entry
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
suffix:semicolon
r_struct
id|tree_desc
id|t
suffix:semicolon
multiline_comment|/*&n;&t; * This is used by git-blame to run diff-cache internally;&n;&t; * it potentially needs to repeatedly run this, so we will&n;&t; * start by removing the higher order entries the last round&n;&t; * left behind.&n;&t; */
id|dst
op_assign
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
r_if
c_cond
(paren
id|last
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|last-&gt;name
)paren
)paren
r_continue
suffix:semicolon
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|last
op_assign
id|ce
suffix:semicolon
id|ce-&gt;ce_flags
op_or_assign
id|CE_REMOVE
suffix:semicolon
)brace
op_star
id|dst
op_increment
op_assign
id|ce
suffix:semicolon
)brace
id|active_nr
op_assign
id|dst
id|active_cache
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|revs.prune_data
op_assign
id|opt-&gt;paths
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|tree_sha1
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
id|sha1_to_hex
c_func
(paren
id|tree_sha1
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|opts.head_idx
op_assign
l_int|1
suffix:semicolon
id|opts.index_only
op_assign
l_int|1
suffix:semicolon
id|opts.diff_index_cached
op_assign
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|FIND_COPIES_HARDER
)paren
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|opts.fn
op_assign
id|oneway_diff
suffix:semicolon
id|opts.unpack_data
op_assign
op_amp
id|revs
suffix:semicolon
id|opts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.dst_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unpack_trees
c_func
(paren
l_int|1
comma
op_amp
id|t
comma
op_amp
id|opts
)paren
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|index_differs_from
r_int
id|index_differs_from
c_func
(paren
r_const
r_char
op_star
id|def
comma
r_int
id|diff_flags
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
op_amp
id|rev
comma
id|def
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|QUICK
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|EXIT_WITH_STATUS
)paren
suffix:semicolon
id|rev.diffopt.flags
op_or_assign
id|diff_flags
suffix:semicolon
id|run_diff_index
c_func
(paren
op_amp
id|rev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev.pending.alloc
)paren
id|free
c_func
(paren
id|rev.pending.objects
)paren
suffix:semicolon
r_return
(paren
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|rev.diffopt
comma
id|HAS_CHANGES
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
eof
