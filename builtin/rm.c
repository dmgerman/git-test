multiline_comment|/*&n; * &quot;git rm&quot; builtin command&n; *&n; * Copyright (C) Linus Torvalds 2006&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;lockfile.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;submodule.h&quot;
macro_line|#include &quot;pathspec.h&quot;
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
id|N_
c_func
(paren
l_string|&quot;git rm [&lt;options&gt;] [--] &lt;file&gt;...&quot;
)paren
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
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|is_submodule
r_char
id|is_submodule
suffix:semicolon
DECL|member|entry
)brace
op_star
id|entry
suffix:semicolon
DECL|variable|list
)brace
id|list
suffix:semicolon
DECL|function|get_ours_cache_pos
r_static
r_int
id|get_ours_cache_pos
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|pos
)paren
(brace
r_int
id|i
op_assign
id|pos
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
OL
id|active_nr
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|path
)paren
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
op_eq
l_int|2
)paren
r_return
id|i
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|print_error_files
r_static
r_void
id|print_error_files
c_func
(paren
r_struct
id|string_list
op_star
id|files_list
comma
r_const
r_char
op_star
id|main_msg
comma
r_const
r_char
op_star
id|hints_msg
comma
r_int
op_star
id|errs
)paren
(brace
r_if
c_cond
(paren
id|files_list-&gt;nr
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|strbuf
id|err_msg
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|err_msg
comma
id|main_msg
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
id|files_list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|err_msg
comma
l_string|&quot;&bslash;n    %s&quot;
comma
id|files_list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|advice_rm_hints
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|err_msg
comma
id|hints_msg
)paren
suffix:semicolon
op_star
id|errs
op_assign
id|error
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err_msg.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|err_msg
)paren
suffix:semicolon
)brace
)brace
DECL|function|error_removing_concrete_submodules
r_static
r_void
id|error_removing_concrete_submodules
c_func
(paren
r_struct
id|string_list
op_star
id|files
comma
r_int
op_star
id|errs
)paren
(brace
id|print_error_files
c_func
(paren
id|files
comma
id|Q_
c_func
(paren
l_string|&quot;the following submodule (or one of its nested &quot;
l_string|&quot;submodules)&bslash;n&quot;
l_string|&quot;uses a .git directory:&quot;
comma
l_string|&quot;the following submodules (or one of their nested &quot;
l_string|&quot;submodules)&bslash;n&quot;
l_string|&quot;use a .git directory:&quot;
comma
id|files-&gt;nr
)paren
comma
id|_
c_func
(paren
l_string|&quot;&bslash;n(use &squot;rm -rf&squot; if you really want to remove &quot;
l_string|&quot;it including all of its history)&quot;
)paren
comma
id|errs
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
id|files
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|check_submodules_use_gitfiles
r_static
r_int
id|check_submodules_use_gitfiles
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|errs
op_assign
l_int|0
suffix:semicolon
r_struct
id|string_list
id|files
op_assign
id|STRING_LIST_INIT_NODUP
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
id|name
op_assign
id|list.entry
(braket
id|i
)braket
dot
id|name
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_const
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_struct
id|stat
id|st
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
(brace
id|pos
op_assign
id|get_ours_cache_pos
c_func
(paren
id|name
comma
id|pos
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
)brace
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
op_logical_neg
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_logical_or
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
op_logical_or
id|is_empty_dir
c_func
(paren
id|name
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|submodule_uses_gitfile
c_func
(paren
id|name
)paren
)paren
id|string_list_append
c_func
(paren
op_amp
id|files
comma
id|name
)paren
suffix:semicolon
)brace
id|error_removing_concrete_submodules
c_func
(paren
op_amp
id|files
comma
op_amp
id|errs
)paren
suffix:semicolon
r_return
id|errs
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
r_struct
id|string_list
id|files_staged
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|string_list
id|files_cached
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|string_list
id|files_submodule
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|string_list
id|files_local
op_assign
id|STRING_LIST_INIT_NODUP
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
r_const
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
id|list.entry
(braket
id|i
)braket
dot
id|name
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
(brace
multiline_comment|/*&n;&t;&t;&t; * Skip unmerged entries except for populated submodules&n;&t;&t;&t; * that could lose history when removed.&n;&t;&t;&t; */
id|pos
op_assign
id|get_ours_cache_pos
c_func
(paren
id|name
comma
id|pos
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
r_if
c_cond
(paren
op_logical_neg
id|S_ISGITLINK
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|ce_mode
)paren
op_logical_or
id|is_empty_dir
c_func
(paren
id|name
)paren
)paren
r_continue
suffix:semicolon
)brace
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
op_logical_and
id|errno
op_ne
id|ENOTDIR
)paren
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: %s&quot;
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
multiline_comment|/* if a file was removed and it is now a&n;&t;&t;&t; * directory, that is the same as ENOENT as&n;&t;&t;&t; * far as git is concerned; we do not track&n;&t;&t;&t; * directories unless they are submodules.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * &quot;rm&quot; of a path that has changes need to be treated&n;&t;&t; * carefully not to allow losing local changes&n;&t;&t; * accidentally.  A local change could be (1) file in&n;&t;&t; * work tree is different since the index; and/or (2)&n;&t;&t; * the user staged a content that is different from&n;&t;&t; * the current commit in the index.&n;&t;&t; *&n;&t;&t; * In such a case, you would need to --force the&n;&t;&t; * removal.  However, &quot;rm --cached&quot; (remove only from&n;&t;&t; * the index) is safe if the index matches the file in&n;&t;&t; * the work tree or the HEAD commit, as it means that&n;&t;&t; * the content being removed is available elsewhere.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Is the index different from the file in the work tree?&n;&t;&t; * If it&squot;s a submodule, is its work tree modified?&n;&t;&t; */
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
op_logical_or
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_logical_and
op_logical_neg
id|ok_to_remove_submodule
c_func
(paren
id|ce-&gt;name
)paren
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
id|string_list_append
c_func
(paren
op_amp
id|files_staged
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
id|string_list_append
c_func
(paren
op_amp
id|files_cached
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_changes
)paren
(brace
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
id|submodule_uses_gitfile
c_func
(paren
id|name
)paren
)paren
id|string_list_append
c_func
(paren
op_amp
id|files_submodule
comma
id|name
)paren
suffix:semicolon
r_else
id|string_list_append
c_func
(paren
op_amp
id|files_local
comma
id|name
)paren
suffix:semicolon
)brace
)brace
)brace
id|print_error_files
c_func
(paren
op_amp
id|files_staged
comma
id|Q_
c_func
(paren
l_string|&quot;the following file has staged content different &quot;
l_string|&quot;from both the&bslash;nfile and the HEAD:&quot;
comma
l_string|&quot;the following files have staged content different&quot;
l_string|&quot; from both the&bslash;nfile and the HEAD:&quot;
comma
id|files_staged.nr
)paren
comma
id|_
c_func
(paren
l_string|&quot;&bslash;n(use -f to force removal)&quot;
)paren
comma
op_amp
id|errs
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|files_staged
comma
l_int|0
)paren
suffix:semicolon
id|print_error_files
c_func
(paren
op_amp
id|files_cached
comma
id|Q_
c_func
(paren
l_string|&quot;the following file has changes &quot;
l_string|&quot;staged in the index:&quot;
comma
l_string|&quot;the following files have changes &quot;
l_string|&quot;staged in the index:&quot;
comma
id|files_cached.nr
)paren
comma
id|_
c_func
(paren
l_string|&quot;&bslash;n(use --cached to keep the file,&quot;
l_string|&quot; or -f to force removal)&quot;
)paren
comma
op_amp
id|errs
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|files_cached
comma
l_int|0
)paren
suffix:semicolon
id|error_removing_concrete_submodules
c_func
(paren
op_amp
id|files_submodule
comma
op_amp
id|errs
)paren
suffix:semicolon
id|print_error_files
c_func
(paren
op_amp
id|files_local
comma
id|Q_
c_func
(paren
l_string|&quot;the following file has local modifications:&quot;
comma
l_string|&quot;the following files have local modifications:&quot;
comma
id|files_local.nr
)paren
comma
id|_
c_func
(paren
l_string|&quot;&bslash;n(use --cached to keep the file,&quot;
l_string|&quot; or -f to force removal)&quot;
)paren
comma
op_amp
id|errs
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|files_local
comma
l_int|0
)paren
suffix:semicolon
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
comma
id|N_
c_func
(paren
l_string|&quot;dry run&quot;
)paren
)paren
comma
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
id|N_
c_func
(paren
l_string|&quot;do not list removed files&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;cached&quot;
comma
op_amp
id|index_only
comma
id|N_
c_func
(paren
l_string|&quot;only remove from the index&quot;
)paren
)paren
comma
id|OPT__FORCE
c_func
(paren
op_amp
id|force
comma
id|N_
c_func
(paren
l_string|&quot;override the up-to-date check&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|NULL
comma
op_amp
id|recursive
comma
id|N_
c_func
(paren
l_string|&quot;allow recursive removal&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;ignore-unmatch&quot;
comma
op_amp
id|ignore_unmatch
comma
id|N_
c_func
(paren
l_string|&quot;exit with a zero status even if nothing matched&quot;
)paren
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
suffix:semicolon
r_struct
id|pathspec
id|pathspec
suffix:semicolon
r_char
op_star
id|seen
suffix:semicolon
id|gitmodules_config
c_func
(paren
)paren
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
id|prefix
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
id|_
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
)paren
suffix:semicolon
id|parse_pathspec
c_func
(paren
op_amp
id|pathspec
comma
l_int|0
comma
id|PATHSPEC_PREFER_CWD
op_or
id|PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP
comma
id|prefix
comma
id|argv
)paren
suffix:semicolon
id|refresh_index
c_func
(paren
op_amp
id|the_index
comma
id|REFRESH_QUIET
comma
op_amp
id|pathspec
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|seen
op_assign
id|xcalloc
c_func
(paren
id|pathspec.nr
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
r_const
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
id|ce_path_match
c_func
(paren
id|ce
comma
op_amp
id|pathspec
comma
id|seen
)paren
)paren
r_continue
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|list.entry
comma
id|list.nr
op_plus
l_int|1
comma
id|list.alloc
)paren
suffix:semicolon
id|list.entry
(braket
id|list.nr
)braket
dot
id|name
op_assign
id|xstrdup
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
id|list.entry
(braket
id|list.nr
)braket
dot
id|is_submodule
op_assign
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list.entry
(braket
id|list.nr
op_increment
)braket
dot
id|is_submodule
op_logical_and
op_logical_neg
id|is_staging_gitmodules_ok
c_func
(paren
)paren
)paren
id|die
(paren
id|_
c_func
(paren
l_string|&quot;Please, stage your changes to .gitmodules or stash them to proceed&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pathspec.nr
)paren
(brace
r_const
r_char
op_star
id|original
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
id|i
OL
id|pathspec.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|original
op_assign
id|pathspec.items
(braket
id|i
)braket
dot
id|original
suffix:semicolon
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
id|_
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any files&quot;
)paren
comma
id|original
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
id|_
c_func
(paren
l_string|&quot;not removing &squot;%s&squot; recursively without -r&quot;
)paren
comma
op_star
id|original
ques
c_cond
id|original
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
id|check_submodules_use_gitfiles
c_func
(paren
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
id|list.entry
(braket
id|i
)braket
dot
id|name
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
id|_
c_func
(paren
l_string|&quot;git rm: unable to remove %s&quot;
)paren
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
comma
id|gitmodules_modified
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
id|list.entry
(braket
id|i
)braket
dot
id|name
suffix:semicolon
r_if
c_cond
(paren
id|list.entry
(braket
id|i
)braket
dot
id|is_submodule
)paren
(brace
r_if
c_cond
(paren
id|is_empty_dir
c_func
(paren
id|path
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rmdir
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
r_if
c_cond
(paren
op_logical_neg
id|remove_path_from_gitmodules
c_func
(paren
id|path
)paren
)paren
id|gitmodules_modified
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remove_dir_recursively
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
)paren
(brace
id|removed
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remove_path_from_gitmodules
c_func
(paren
id|path
)paren
)paren
id|gitmodules_modified
op_assign
l_int|1
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|path
)paren
)paren
multiline_comment|/* Submodule was removed by user */
r_if
c_cond
(paren
op_logical_neg
id|remove_path_from_gitmodules
c_func
(paren
id|path
)paren
)paren
id|gitmodules_modified
op_assign
l_int|1
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
multiline_comment|/* Fallthrough and let remove_path() fail. */
)brace
)brace
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
id|die_errno
c_func
(paren
l_string|&quot;git rm: &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gitmodules_modified
)paren
id|stage_updated_gitmodules
c_func
(paren
)paren
suffix:semicolon
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
id|write_locked_index
c_func
(paren
op_amp
id|the_index
comma
op_amp
id|lock_file
comma
id|COMMIT_LOCK
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
