multiline_comment|/*&n; * &quot;git rm&quot; builtin command&n; *&n; * Copyright (C) Linus Torvalds 2006&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|builtin_rm_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_rm_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git rm [options] [--] &lt;file&gt;...&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|nr
DECL|member|alloc
r_int
id|nr
comma
id|alloc
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
op_star
id|name
suffix:semicolon
DECL|variable|list
)brace
id|list
suffix:semicolon
DECL|function|add_list
r_static
r_void
id|add_list
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|list.nr
op_ge
id|list.alloc
)paren
(brace
id|list.alloc
op_assign
id|alloc_nr
c_func
(paren
id|list.alloc
)paren
suffix:semicolon
id|list.name
op_assign
id|xrealloc
c_func
(paren
id|list.name
comma
id|list.alloc
op_star
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
)brace
id|list.name
(braket
id|list.nr
op_increment
)braket
op_assign
id|name
suffix:semicolon
)brace
DECL|function|check_local_mod
r_static
r_int
id|check_local_mod
c_func
(paren
r_int
r_char
op_star
id|head
comma
r_int
id|index_only
)paren
(brace
multiline_comment|/*&n;&t; * Items in list are already sorted in the cache order,&n;&t; * so we could do this a lot more efficiently by using&n;&t; * tree_desc based traversal if we wanted to, but I am&n;&t; * lazy, and who cares if removal of files is a tad&n;&t; * slower than the theoretical maximum speed?&n;&t; */
r_int
id|i
comma
id|no_head
suffix:semicolon
r_int
id|errs
op_assign
l_int|0
suffix:semicolon
id|no_head
op_assign
id|is_null_sha1
c_func
(paren
id|head
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
id|list.nr
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
id|pos
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|list.name
(braket
id|i
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|local_changes
op_assign
l_int|0
suffix:semicolon
r_int
id|staged_changes
op_assign
l_int|0
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* removing unmerged entry */
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
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
op_ne
id|ENOENT
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: &squot;%s&squot;: %s&quot;
comma
id|ce-&gt;name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
multiline_comment|/* It already vanished from the working tree */
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
multiline_comment|/* if a file was removed and it is now a&n;&t;&t;&t; * directory, that is the same as ENOENT as&n;&t;&t;&t; * far as git is concerned; we do not track&n;&t;&t;&t; * directories.&n;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * &quot;rm&quot; of a path that has changes need to be treated&n;&t;&t; * carefully not to allow losing local changes&n;&t;&t; * accidentally.  A local change could be (1) file in&n;&t;&t; * work tree is different since the index; and/or (2)&n;&t;&t; * the user staged a content that is different from&n;&t;&t; * the current commit in the index.&n;&t;&t; *&n;&t;&t; * In such a case, you would need to --force the&n;&t;&t; * removal.  However, &quot;rm --cached&quot; (remove only from&n;&t;&t; * the index) is safe if the index matches the file in&n;&t;&t; * the work tree or the HEAD commit, as it means that&n;&t;&t; * the content being removed is available elsewhere.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Is the index different from the file in the work tree?&n;&t;&t; */
r_if
c_cond
(paren
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
)paren
id|local_changes
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Is the index different from the HEAD commit?  By&n;&t;&t; * definition, before the very initial commit,&n;&t;&t; * anything staged in the index is treated by the same&n;&t;&t; * way as changed from the HEAD.&n;&t;&t; */
r_if
c_cond
(paren
id|no_head
op_logical_or
id|get_tree_entry
c_func
(paren
id|head
comma
id|name
comma
id|sha1
comma
op_amp
id|mode
)paren
op_logical_or
id|ce-&gt;ce_mode
op_ne
id|create_ce_mode
c_func
(paren
id|mode
)paren
op_logical_or
id|hashcmp
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
)paren
)paren
id|staged_changes
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the index does not match the file in the work&n;&t;&t; * tree and if it does not match the HEAD commit&n;&t;&t; * either, (1) &quot;git rm&quot; without --cached definitely&n;&t;&t; * will lose information; (2) &quot;git rm --cached&quot; will&n;&t;&t; * lose information unless it is about removing an&n;&t;&t; * &quot;intent to add&quot; entry.&n;&t;&t; */
r_if
c_cond
(paren
id|local_changes
op_logical_and
id|staged_changes
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|index_only
op_logical_or
op_logical_neg
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_INTENT_TO_ADD
)paren
)paren
id|errs
op_assign
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot; has staged content different &quot;
l_string|&quot;from both the file and the HEAD&bslash;n&quot;
l_string|&quot;(use -f to force removal)&quot;
comma
id|name
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|index_only
)paren
(brace
r_if
c_cond
(paren
id|staged_changes
)paren
id|errs
op_assign
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot; has changes staged in the index&bslash;n&quot;
l_string|&quot;(use --cached to keep the file, &quot;
l_string|&quot;or -f to force removal)&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_changes
)paren
id|errs
op_assign
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot; has local modifications&bslash;n&quot;
l_string|&quot;(use --cached to keep the file, &quot;
l_string|&quot;or -f to force removal)&quot;
comma
id|name
)paren
suffix:semicolon
)brace
)brace
r_return
id|errs
suffix:semicolon
)brace
DECL|variable|lock_file
r_static
r_struct
id|lock_file
id|lock_file
suffix:semicolon
DECL|variable|show_only
DECL|variable|force
DECL|variable|index_only
DECL|variable|recursive
DECL|variable|quiet
r_static
r_int
id|show_only
op_assign
l_int|0
comma
id|force
op_assign
l_int|0
comma
id|index_only
op_assign
l_int|0
comma
id|recursive
op_assign
l_int|0
comma
id|quiet
op_assign
l_int|0
suffix:semicolon
DECL|variable|ignore_unmatch
r_static
r_int
id|ignore_unmatch
op_assign
l_int|0
suffix:semicolon
DECL|variable|builtin_rm_options
r_static
r_struct
id|option
id|builtin_rm_options
(braket
)braket
op_assign
(brace
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|show_only
)paren
comma
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;cached&quot;
comma
op_amp
id|index_only
comma
l_string|&quot;only remove from the index&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
comma
op_amp
id|force
comma
l_string|&quot;override the up-to-date check&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|NULL
comma
op_amp
id|recursive
comma
l_string|&quot;allow recursive removal&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;ignore-unmatch&quot;
comma
op_amp
id|ignore_unmatch
comma
l_string|&quot;exit with a zero status even if nothing matched&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
DECL|function|cmd_rm
r_int
id|cmd_rm
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
comma
id|newfd
suffix:semicolon
r_const
r_char
op_star
op_star
id|pathspec
suffix:semicolon
r_char
op_star
id|seen
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|builtin_rm_options
comma
id|builtin_rm_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|argc
)paren
id|usage_with_options
c_func
(paren
id|builtin_rm_usage
comma
id|builtin_rm_options
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|index_only
)paren
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
op_amp
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
suffix:semicolon
id|refresh_cache
c_func
(paren
id|REFRESH_QUIET
)paren
suffix:semicolon
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
)paren
suffix:semicolon
id|seen
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|seen
op_assign
id|xcalloc
c_func
(paren
id|i
comma
l_int|1
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
id|match_pathspec
c_func
(paren
id|pathspec
comma
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
comma
l_int|0
comma
id|seen
)paren
)paren
r_continue
suffix:semicolon
id|add_list
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pathspec
)paren
(brace
r_const
r_char
op_star
id|match
suffix:semicolon
r_int
id|seen_any
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
(paren
id|match
op_assign
id|pathspec
(braket
id|i
)braket
)paren
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ignore_unmatch
)paren
(brace
id|die
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
comma
id|match
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|seen_any
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|recursive
op_logical_and
id|seen
(braket
id|i
)braket
op_eq
id|MATCHED_RECURSIVELY
)paren
id|die
c_func
(paren
l_string|&quot;not removing &squot;%s&squot; recursively without -r&quot;
comma
op_star
id|match
ques
c_cond
id|match
suffix:colon
l_string|&quot;.&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|seen_any
)paren
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If not forced, the file, the index and the HEAD (if exists)&n;&t; * must match; but the file can already been removed, since&n;&t; * this sequence is a natural &quot;novice&quot; way:&n;&t; *&n;&t; *&t;rm F; git rm F&n;&t; *&n;&t; * Further, if HEAD commit exists, &quot;diff-index --cached&quot; must&n;&t; * report no changes unless forced.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1
)paren
)paren
id|hashclr
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_local_mod
c_func
(paren
id|sha1
comma
id|index_only
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * First remove the names from the index: we won&squot;t commit&n;&t; * the index unless all of them succeed.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|list.name
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|printf
c_func
(paren
l_string|&quot;rm &squot;%s&squot;&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|path
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git rm: unable to remove %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_only
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Then, unless we used &quot;--cached&quot;, remove the filenames from&n;&t; * the workspace. If we fail to remove the first one, we&n;&t; * abort the &quot;git rm&quot; (but once we&squot;ve successfully removed&n;&t; * any file at all, we&squot;ll go ahead and commit to it all:&n;&t; * by then we&squot;ve already committed ourselves and can&squot;t fail&n;&t; * in the middle)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|index_only
)paren
(brace
r_int
id|removed
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
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|list.name
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remove_path
c_func
(paren
id|path
)paren
)paren
(brace
id|removed
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
id|removed
)paren
id|die
c_func
(paren
l_string|&quot;git rm: %s: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|active_cache_changed
)paren
(brace
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
id|commit_locked_index
c_func
(paren
op_amp
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
