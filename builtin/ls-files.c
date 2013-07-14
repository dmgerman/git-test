multiline_comment|/*&n; * This merges the file listing in the directory cache index&n; * with the actual working directory list, and shows different&n; * combinations of the two.&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;resolve-undo.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;pathspec.h&quot;
DECL|variable|abbrev
r_static
r_int
id|abbrev
suffix:semicolon
DECL|variable|show_deleted
r_static
r_int
id|show_deleted
suffix:semicolon
DECL|variable|show_cached
r_static
r_int
id|show_cached
suffix:semicolon
DECL|variable|show_others
r_static
r_int
id|show_others
suffix:semicolon
DECL|variable|show_stage
r_static
r_int
id|show_stage
suffix:semicolon
DECL|variable|show_unmerged
r_static
r_int
id|show_unmerged
suffix:semicolon
DECL|variable|show_resolve_undo
r_static
r_int
id|show_resolve_undo
suffix:semicolon
DECL|variable|show_modified
r_static
r_int
id|show_modified
suffix:semicolon
DECL|variable|show_killed
r_static
r_int
id|show_killed
suffix:semicolon
DECL|variable|show_valid_bit
r_static
r_int
id|show_valid_bit
suffix:semicolon
DECL|variable|line_terminator
r_static
r_int
id|line_terminator
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|debug_mode
r_static
r_int
id|debug_mode
suffix:semicolon
DECL|variable|prefix
r_static
r_const
r_char
op_star
id|prefix
suffix:semicolon
DECL|variable|max_prefix_len
r_static
r_int
id|max_prefix_len
suffix:semicolon
DECL|variable|prefix_len
r_static
r_int
id|prefix_len
suffix:semicolon
DECL|variable|pathspec
r_static
r_struct
id|pathspec
id|pathspec
suffix:semicolon
DECL|variable|error_unmatch
r_static
r_int
id|error_unmatch
suffix:semicolon
DECL|variable|ps_matched
r_static
r_char
op_star
id|ps_matched
suffix:semicolon
DECL|variable|with_tree
r_static
r_const
r_char
op_star
id|with_tree
suffix:semicolon
DECL|variable|exc_given
r_static
r_int
id|exc_given
suffix:semicolon
DECL|variable|exclude_args
r_static
r_int
id|exclude_args
suffix:semicolon
DECL|variable|tag_cached
r_static
r_const
r_char
op_star
id|tag_cached
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_unmerged
r_static
r_const
r_char
op_star
id|tag_unmerged
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_removed
r_static
r_const
r_char
op_star
id|tag_removed
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_other
r_static
r_const
r_char
op_star
id|tag_other
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_killed
r_static
r_const
r_char
op_star
id|tag_killed
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_modified
r_static
r_const
r_char
op_star
id|tag_modified
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_skip_worktree
r_static
r_const
r_char
op_star
id|tag_skip_worktree
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_resolve_undo
r_static
r_const
r_char
op_star
id|tag_resolve_undo
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|function|write_name
r_static
r_void
id|write_name
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
id|write_name_quoted_relative
c_func
(paren
id|name
comma
id|len
comma
id|prefix
comma
id|prefix_len
comma
id|stdout
comma
id|line_terminator
)paren
suffix:semicolon
)brace
DECL|function|show_dir_entry
r_static
r_void
id|show_dir_entry
c_func
(paren
r_const
r_char
op_star
id|tag
comma
r_struct
id|dir_entry
op_star
id|ent
)paren
(brace
r_int
id|len
op_assign
id|max_prefix_len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|ent-&gt;len
)paren
id|die
c_func
(paren
l_string|&quot;git ls-files: internal error - directory entry not superset of prefix&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match_pathspec_depth
c_func
(paren
op_amp
id|pathspec
comma
id|ent-&gt;name
comma
id|ent-&gt;len
comma
id|len
comma
id|ps_matched
)paren
)paren
r_return
suffix:semicolon
id|fputs
c_func
(paren
id|tag
comma
id|stdout
)paren
suffix:semicolon
id|write_name
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|show_other_files
r_static
r_void
id|show_other_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
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
id|dir-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dir_entry
op_star
id|ent
op_assign
id|dir-&gt;entries
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_name_is_other
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
)paren
r_continue
suffix:semicolon
id|show_dir_entry
c_func
(paren
id|tag_other
comma
id|ent
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_killed_files
r_static
r_void
id|show_killed_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
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
id|dir-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dir_entry
op_star
id|ent
op_assign
id|dir-&gt;entries
(braket
id|i
)braket
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|sp
suffix:semicolon
r_int
id|pos
comma
id|len
comma
id|killed
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|ent-&gt;name
suffix:semicolon
id|cp
id|ent-&gt;name
OL
id|ent-&gt;len
suffix:semicolon
id|cp
op_assign
id|sp
op_plus
l_int|1
)paren
(brace
id|sp
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sp
)paren
(brace
multiline_comment|/* If ent-&gt;name is prefix of an entry in the&n;&t;&t;&t;&t; * cache, it will be killed.&n;&t;&t;&t;&t; */
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
id|die
c_func
(paren
l_string|&quot;bug in show-killed-files&quot;
)paren
suffix:semicolon
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|active_nr
op_logical_and
id|ce_stage
c_func
(paren
id|active_cache
(braket
id|pos
)braket
)paren
)paren
id|pos
op_increment
suffix:semicolon
multiline_comment|/* skip unmerged */
r_if
c_cond
(paren
id|active_nr
op_le
id|pos
)paren
r_break
suffix:semicolon
multiline_comment|/* pos points at a name immediately after&n;&t;&t;&t;&t; * ent-&gt;name in the cache.  Does it expect&n;&t;&t;&t;&t; * ent-&gt;name to be a directory?&n;&t;&t;&t;&t; */
id|len
op_assign
id|ce_namelen
c_func
(paren
id|active_cache
(braket
id|pos
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ent-&gt;len
OL
id|len
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
op_logical_and
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
(braket
id|ent-&gt;len
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|killed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|sp
id|ent-&gt;name
)paren
)paren
(brace
multiline_comment|/* If any of the leading directories in&n;&t;&t;&t;&t; * ent-&gt;name is registered in the cache,&n;&t;&t;&t;&t; * ent-&gt;name will be killed.&n;&t;&t;&t;&t; */
id|killed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|killed
)paren
id|show_dir_entry
c_func
(paren
id|tag_killed
comma
id|dir-&gt;entries
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_ce_entry
r_static
r_void
id|show_ce_entry
c_func
(paren
r_const
r_char
op_star
id|tag
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_int
id|len
op_assign
id|max_prefix_len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|ce_namelen
c_func
(paren
id|ce
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git ls-files: internal error - cache entry not superset of prefix&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match_pathspec_depth
c_func
(paren
op_amp
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
id|len
comma
id|ps_matched
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_logical_and
op_star
id|tag
op_logical_and
id|show_valid_bit
op_logical_and
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_VALID
)paren
)paren
(brace
r_static
r_char
id|alttag
(braket
l_int|4
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|alttag
comma
id|tag
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isalpha
c_func
(paren
id|tag
(braket
l_int|0
)braket
)paren
)paren
id|alttag
(braket
l_int|0
)braket
op_assign
id|tolower
c_func
(paren
id|tag
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tag
(braket
l_int|0
)braket
op_eq
l_char|&squot;?&squot;
)paren
id|alttag
(braket
l_int|0
)braket
op_assign
l_char|&squot;!&squot;
suffix:semicolon
r_else
(brace
id|alttag
(braket
l_int|0
)braket
op_assign
l_char|&squot;v&squot;
suffix:semicolon
id|alttag
(braket
l_int|1
)braket
op_assign
id|tag
(braket
l_int|0
)braket
suffix:semicolon
id|alttag
(braket
l_int|2
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|alttag
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|tag
op_assign
id|alttag
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|show_stage
)paren
(brace
id|fputs
c_func
(paren
id|tag
comma
id|stdout
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%s%06o %s %d&bslash;t&quot;
comma
id|tag
comma
id|ce-&gt;ce_mode
comma
id|find_unique_abbrev
c_func
(paren
id|ce-&gt;sha1
comma
id|abbrev
)paren
comma
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
suffix:semicolon
)brace
id|write_name
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
suffix:semicolon
r_if
c_cond
(paren
id|debug_mode
)paren
(brace
r_struct
id|stat_data
op_star
id|sd
op_assign
op_amp
id|ce-&gt;ce_stat_data
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  ctime: %d:%d&bslash;n&quot;
comma
id|sd-&gt;sd_ctime.sec
comma
id|sd-&gt;sd_ctime.nsec
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  mtime: %d:%d&bslash;n&quot;
comma
id|sd-&gt;sd_mtime.sec
comma
id|sd-&gt;sd_mtime.nsec
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  dev: %d&bslash;tino: %d&bslash;n&quot;
comma
id|sd-&gt;sd_dev
comma
id|sd-&gt;sd_ino
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  uid: %d&bslash;tgid: %d&bslash;n&quot;
comma
id|sd-&gt;sd_uid
comma
id|sd-&gt;sd_gid
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  size: %d&bslash;tflags: %x&bslash;n&quot;
comma
id|sd-&gt;sd_size
comma
id|ce-&gt;ce_flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_ru_info
r_static
r_void
id|show_ru_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|the_index.resolve_undo
)paren
r_return
suffix:semicolon
id|for_each_string_list_item
c_func
(paren
id|item
comma
id|the_index.resolve_undo
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|item-&gt;string
suffix:semicolon
r_struct
id|resolve_undo_info
op_star
id|ui
op_assign
id|item-&gt;util
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|max_prefix_len
)paren
r_continue
suffix:semicolon
multiline_comment|/* outside of the prefix */
r_if
c_cond
(paren
op_logical_neg
id|match_pathspec_depth
c_func
(paren
op_amp
id|pathspec
comma
id|path
comma
id|len
comma
id|max_prefix_len
comma
id|ps_matched
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* uninterested */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ui-&gt;mode
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s%06o %s %d&bslash;t&quot;
comma
id|tag_resolve_undo
comma
id|ui-&gt;mode
(braket
id|i
)braket
comma
id|find_unique_abbrev
c_func
(paren
id|ui-&gt;sha1
(braket
id|i
)braket
comma
id|abbrev
)paren
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|write_name
c_func
(paren
id|path
comma
id|len
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|ce_excluded
r_static
r_int
id|ce_excluded
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_int
id|dtype
op_assign
id|ce_to_dtype
c_func
(paren
id|ce
)paren
suffix:semicolon
r_return
id|is_excluded
c_func
(paren
id|dir
comma
id|ce-&gt;name
comma
op_amp
id|dtype
)paren
suffix:semicolon
)brace
DECL|function|show_files
r_static
r_void
id|show_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* For cached/deleted files we don&squot;t need to even do the readdir */
r_if
c_cond
(paren
id|show_others
op_logical_or
id|show_killed
)paren
(brace
id|fill_directory
c_func
(paren
id|dir
comma
op_amp
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_others
)paren
id|show_other_files
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_killed
)paren
id|show_killed_files
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_cached
op_logical_or
id|show_stage
)paren
(brace
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
(paren
id|dir-&gt;flags
op_amp
id|DIR_SHOW_IGNORED
)paren
op_logical_and
op_logical_neg
id|ce_excluded
c_func
(paren
id|dir
comma
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|show_unmerged
op_logical_and
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_UPDATE
)paren
r_continue
suffix:semicolon
id|show_ce_entry
c_func
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
ques
c_cond
id|tag_unmerged
suffix:colon
(paren
id|ce_skip_worktree
c_func
(paren
id|ce
)paren
ques
c_cond
id|tag_skip_worktree
suffix:colon
id|tag_cached
)paren
comma
id|ce
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|show_deleted
op_logical_or
id|show_modified
)paren
(brace
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
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dir-&gt;flags
op_amp
id|DIR_SHOW_IGNORED
)paren
op_logical_and
op_logical_neg
id|ce_excluded
c_func
(paren
id|dir
comma
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_UPDATE
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce_skip_worktree
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_deleted
op_logical_and
id|err
)paren
id|show_ce_entry
c_func
(paren
id|tag_removed
comma
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_modified
op_logical_and
id|ce_modified
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
id|show_ce_entry
c_func
(paren
id|tag_modified
comma
id|ce
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Prune the index to only contain stuff starting with &quot;prefix&quot;&n; */
DECL|function|prune_cache
r_static
r_void
id|prune_cache
c_func
(paren
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|prefix
comma
id|max_prefix_len
)paren
suffix:semicolon
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
id|memmove
c_func
(paren
id|active_cache
comma
id|active_cache
op_plus
id|pos
comma
(paren
id|active_nr
id|pos
)paren
op_star
r_sizeof
(paren
r_struct
id|cache_entry
op_star
)paren
)paren
suffix:semicolon
id|active_nr
op_sub_assign
id|pos
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|last
op_assign
id|active_nr
suffix:semicolon
r_while
c_loop
(paren
id|last
OG
id|first
)paren
(brace
r_int
id|next
op_assign
(paren
id|last
op_plus
id|first
)paren
op_rshift
l_int|1
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|next
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|ce-&gt;name
comma
id|prefix
comma
id|max_prefix_len
)paren
)paren
(brace
id|first
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|last
op_assign
id|next
suffix:semicolon
)brace
id|active_nr
op_assign
id|last
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the tree specified with --with-tree option&n; * (typically, HEAD) into stage #1 and then&n; * squash them down to stage #0.  This is used for&n; * --error-unmatch to list and check the path patterns&n; * that were given from the command line.  We are not&n; * going to write this index out.&n; */
DECL|function|overlay_tree_on_cache
r_void
id|overlay_tree_on_cache
c_func
(paren
r_const
r_char
op_star
id|tree_name
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|pathspec
id|pathspec
suffix:semicolon
r_struct
id|cache_entry
op_star
id|last_stage0
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|tree_name
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;tree-ish %s not found.&quot;
comma
id|tree_name
)paren
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|sha1
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
l_string|&quot;bad tree-ish %s&quot;
comma
id|tree_name
)paren
suffix:semicolon
multiline_comment|/* Hoist the unmerged entries up to stage #3 to make room */
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
id|CE_STAGEMASK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_static
r_const
r_char
op_star
(paren
id|matchbuf
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|matchbuf
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|parse_pathspec
c_func
(paren
op_amp
id|pathspec
comma
id|PATHSPEC_ALL_MAGIC
comma
id|PATHSPEC_PREFER_CWD
comma
id|prefix
comma
id|matchbuf
)paren
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
op_amp
id|pathspec
comma
l_int|0
comma
r_sizeof
(paren
id|pathspec
)paren
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
l_int|1
comma
op_amp
id|pathspec
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree entries %s&quot;
comma
id|tree_name
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
id|last_stage0
op_assign
id|ce
suffix:semicolon
multiline_comment|/* fallthru */
r_default
suffix:colon
r_continue
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If there is stage #0 entry for this, we do not&n;&t;&t;&t; * need to show it.  We use CE_UPDATE bit to mark&n;&t;&t;&t; * such an entry.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|last_stage0
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|last_stage0-&gt;name
comma
id|ce-&gt;name
)paren
)paren
id|ce-&gt;ce_flags
op_or_assign
id|CE_UPDATE
suffix:semicolon
)brace
)brace
)brace
DECL|function|report_path_error
r_int
id|report_path_error
c_func
(paren
r_const
r_char
op_star
id|ps_matched
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
multiline_comment|/*&n;&t; * Make sure all pathspec matched; otherwise it is an error.&n;&t; */
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|num
comma
id|errors
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|num
OL
id|pathspec-&gt;nr
suffix:semicolon
id|num
op_increment
)paren
(brace
r_int
id|other
comma
id|found_dup
suffix:semicolon
r_if
c_cond
(paren
id|ps_matched
(braket
id|num
)braket
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The caller might have fed identical pathspec&n;&t;&t; * twice.  Do not barf on such a mistake.&n;&t;&t; * FIXME: parse_pathspec should have eliminated&n;&t;&t; * duplicate pathspec.&n;&t;&t; */
r_for
c_loop
(paren
id|found_dup
op_assign
id|other
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found_dup
op_logical_and
id|other
OL
id|pathspec-&gt;nr
suffix:semicolon
id|other
op_increment
)paren
(brace
r_if
c_cond
(paren
id|other
op_eq
id|num
op_logical_or
op_logical_neg
id|ps_matched
(braket
id|other
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|pathspec-&gt;items
(braket
id|other
)braket
dot
id|original
comma
id|pathspec-&gt;items
(braket
id|num
)braket
dot
id|original
)paren
)paren
multiline_comment|/*&n;&t;&t;&t;&t; * Ok, we have a match already.&n;&t;&t;&t;&t; */
id|found_dup
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found_dup
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any file(s) known to git.&quot;
comma
id|pathspec-&gt;items
(braket
id|num
)braket
dot
id|original
)paren
suffix:semicolon
id|errors
op_increment
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
id|errors
suffix:semicolon
)brace
DECL|variable|ls_files_usage
r_static
r_const
r_char
op_star
r_const
id|ls_files_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git ls-files [options] [&lt;file&gt;...]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|option_parse_z
r_static
r_int
id|option_parse_z
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
id|line_terminator
op_assign
id|unset
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|option_parse_exclude
r_static
r_int
id|option_parse_exclude
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|string_list
op_star
id|exclude_list
op_assign
id|opt-&gt;value
suffix:semicolon
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|string_list_append
c_func
(paren
id|exclude_list
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|option_parse_exclude_from
r_static
r_int
id|option_parse_exclude_from
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|dir_struct
op_star
id|dir
op_assign
id|opt-&gt;value
suffix:semicolon
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|add_excludes_from_file
c_func
(paren
id|dir
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|option_parse_exclude_standard
r_static
r_int
id|option_parse_exclude_standard
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|dir_struct
op_star
id|dir
op_assign
id|opt-&gt;value
suffix:semicolon
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|setup_standard_excludes
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_ls_files
r_int
id|cmd_ls_files
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
id|cmd_prefix
)paren
(brace
r_int
id|require_work_tree
op_assign
l_int|0
comma
id|show_tag
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_const
r_char
op_star
id|max_prefix
suffix:semicolon
r_struct
id|dir_struct
id|dir
suffix:semicolon
r_struct
id|exclude_list
op_star
id|el
suffix:semicolon
r_struct
id|string_list
id|exclude_list
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|option
id|builtin_ls_files_options
(braket
)braket
op_assign
(brace
(brace
id|OPTION_CALLBACK
comma
l_char|&squot;z&squot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|N_
c_func
(paren
l_string|&quot;paths are separated with NUL character&quot;
)paren
comma
id|PARSE_OPT_NOARG
comma
id|option_parse_z
)brace
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|NULL
comma
op_amp
id|show_tag
comma
id|N_
c_func
(paren
l_string|&quot;identify the file status with tags&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;v&squot;
comma
l_int|NULL
comma
op_amp
id|show_valid_bit
comma
id|N_
c_func
(paren
l_string|&quot;use lowercase letters for &squot;assume unchanged&squot; files&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;c&squot;
comma
l_string|&quot;cached&quot;
comma
op_amp
id|show_cached
comma
id|N_
c_func
(paren
l_string|&quot;show cached files in the output (default)&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;d&squot;
comma
l_string|&quot;deleted&quot;
comma
op_amp
id|show_deleted
comma
id|N_
c_func
(paren
l_string|&quot;show deleted files in the output&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;m&squot;
comma
l_string|&quot;modified&quot;
comma
op_amp
id|show_modified
comma
id|N_
c_func
(paren
l_string|&quot;show modified files in the output&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;o&squot;
comma
l_string|&quot;others&quot;
comma
op_amp
id|show_others
comma
id|N_
c_func
(paren
l_string|&quot;show other files in the output&quot;
)paren
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;i&squot;
comma
l_string|&quot;ignored&quot;
comma
op_amp
id|dir.flags
comma
id|N_
c_func
(paren
l_string|&quot;show ignored files in the output&quot;
)paren
comma
id|DIR_SHOW_IGNORED
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;s&squot;
comma
l_string|&quot;stage&quot;
comma
op_amp
id|show_stage
comma
id|N_
c_func
(paren
l_string|&quot;show staged contents&squot; object name in the output&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;k&squot;
comma
l_string|&quot;killed&quot;
comma
op_amp
id|show_killed
comma
id|N_
c_func
(paren
l_string|&quot;show files on the filesystem that need to be removed&quot;
)paren
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;directory&quot;
comma
op_amp
id|dir.flags
comma
id|N_
c_func
(paren
l_string|&quot;show &squot;other&squot; directories&squot; name only&quot;
)paren
comma
id|DIR_SHOW_OTHER_DIRECTORIES
)paren
comma
id|OPT_NEGBIT
c_func
(paren
l_int|0
comma
l_string|&quot;empty-directory&quot;
comma
op_amp
id|dir.flags
comma
id|N_
c_func
(paren
l_string|&quot;don&squot;t show empty directories&quot;
)paren
comma
id|DIR_HIDE_EMPTY_DIRECTORIES
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;u&squot;
comma
l_string|&quot;unmerged&quot;
comma
op_amp
id|show_unmerged
comma
id|N_
c_func
(paren
l_string|&quot;show unmerged files in the output&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;resolve-undo&quot;
comma
op_amp
id|show_resolve_undo
comma
id|N_
c_func
(paren
l_string|&quot;show resolve-undo information&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_char|&squot;x&squot;
comma
l_string|&quot;exclude&quot;
comma
op_amp
id|exclude_list
comma
id|N_
c_func
(paren
l_string|&quot;pattern&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;skip files matching pattern&quot;
)paren
comma
l_int|0
comma
id|option_parse_exclude
)brace
comma
(brace
id|OPTION_CALLBACK
comma
l_char|&squot;X&squot;
comma
l_string|&quot;exclude-from&quot;
comma
op_amp
id|dir
comma
id|N_
c_func
(paren
l_string|&quot;file&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;exclude patterns are read from &lt;file&gt;&quot;
)paren
comma
l_int|0
comma
id|option_parse_exclude_from
)brace
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;exclude-per-directory&quot;
comma
op_amp
id|dir.exclude_per_dir
comma
id|N_
c_func
(paren
l_string|&quot;file&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;read additional per-directory exclude patterns in &lt;file&gt;&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;exclude-standard&quot;
comma
op_amp
id|dir
comma
l_int|NULL
comma
id|N_
c_func
(paren
l_string|&quot;add the standard git exclusions&quot;
)paren
comma
id|PARSE_OPT_NOARG
comma
id|option_parse_exclude_standard
)brace
comma
(brace
id|OPTION_SET_INT
comma
l_int|0
comma
l_string|&quot;full-name&quot;
comma
op_amp
id|prefix_len
comma
l_int|NULL
comma
id|N_
c_func
(paren
l_string|&quot;make the output relative to the project top directory&quot;
)paren
comma
id|PARSE_OPT_NOARG
op_or
id|PARSE_OPT_NONEG
comma
l_int|NULL
)brace
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;error-unmatch&quot;
comma
op_amp
id|error_unmatch
comma
id|N_
c_func
(paren
l_string|&quot;if any &lt;file&gt; is not in the index, treat this as an error&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;with-tree&quot;
comma
op_amp
id|with_tree
comma
id|N_
c_func
(paren
l_string|&quot;tree-ish&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;pretend that paths removed since &lt;tree-ish&gt; are still present&quot;
)paren
)paren
comma
id|OPT__ABBREV
c_func
(paren
op_amp
id|abbrev
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;debug&quot;
comma
op_amp
id|debug_mode
comma
id|N_
c_func
(paren
l_string|&quot;show debugging data&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage_with_options
c_func
(paren
id|ls_files_usage
comma
id|builtin_ls_files_options
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dir
comma
l_int|0
comma
r_sizeof
(paren
id|dir
)paren
)paren
suffix:semicolon
id|prefix
op_assign
id|cmd_prefix
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
id|prefix_len
op_assign
id|strlen
c_func
(paren
id|prefix
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
id|builtin_ls_files_options
comma
id|ls_files_usage
comma
l_int|0
)paren
suffix:semicolon
id|el
op_assign
id|add_exclude_list
c_func
(paren
op_amp
id|dir
comma
id|EXC_CMDL
comma
l_string|&quot;--exclude option&quot;
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
id|exclude_list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|add_exclude
c_func
(paren
id|exclude_list.items
(braket
id|i
)braket
dot
id|string
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|el
comma
op_decrement
id|exclude_args
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_tag
op_logical_or
id|show_valid_bit
)paren
(brace
id|tag_cached
op_assign
l_string|&quot;H &quot;
suffix:semicolon
id|tag_unmerged
op_assign
l_string|&quot;M &quot;
suffix:semicolon
id|tag_removed
op_assign
l_string|&quot;R &quot;
suffix:semicolon
id|tag_modified
op_assign
l_string|&quot;C &quot;
suffix:semicolon
id|tag_other
op_assign
l_string|&quot;? &quot;
suffix:semicolon
id|tag_killed
op_assign
l_string|&quot;K &quot;
suffix:semicolon
id|tag_skip_worktree
op_assign
l_string|&quot;S &quot;
suffix:semicolon
id|tag_resolve_undo
op_assign
l_string|&quot;U &quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_modified
op_logical_or
id|show_others
op_logical_or
id|show_deleted
op_logical_or
(paren
id|dir.flags
op_amp
id|DIR_SHOW_IGNORED
)paren
op_logical_or
id|show_killed
)paren
id|require_work_tree
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|show_unmerged
)paren
multiline_comment|/*&n;&t;&t; * There&squot;s no point in showing unmerged unless&n;&t;&t; * you also show the stage information.&n;&t;&t; */
id|show_stage
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dir.exclude_per_dir
)paren
id|exc_given
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|require_work_tree
op_logical_and
op_logical_neg
id|is_inside_work_tree
c_func
(paren
)paren
)paren
id|setup_work_tree
c_func
(paren
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
multiline_comment|/* Find common prefix for all pathspec&squot;s */
id|max_prefix
op_assign
id|common_prefix
c_func
(paren
op_amp
id|pathspec
)paren
suffix:semicolon
id|max_prefix_len
op_assign
id|max_prefix
ques
c_cond
id|strlen
c_func
(paren
id|max_prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Treat unmatching pathspec elements as errors */
r_if
c_cond
(paren
id|pathspec.nr
op_logical_and
id|error_unmatch
)paren
id|ps_matched
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|pathspec.nr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dir.flags
op_amp
id|DIR_SHOW_IGNORED
)paren
op_logical_and
op_logical_neg
id|exc_given
)paren
id|die
c_func
(paren
l_string|&quot;ls-files --ignored needs some exclude pattern&quot;
)paren
suffix:semicolon
multiline_comment|/* With no flags, we default to showing the cached files */
r_if
c_cond
(paren
op_logical_neg
(paren
id|show_stage
op_logical_or
id|show_deleted
op_logical_or
id|show_others
op_logical_or
id|show_unmerged
op_logical_or
id|show_killed
op_logical_or
id|show_modified
op_logical_or
id|show_resolve_undo
)paren
)paren
id|show_cached
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|max_prefix
)paren
id|prune_cache
c_func
(paren
id|max_prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|with_tree
)paren
(brace
multiline_comment|/*&n;&t;&t; * Basic sanity check; show-stages and show-unmerged&n;&t;&t; * would not make any sense with this option.&n;&t;&t; */
r_if
c_cond
(paren
id|show_stage
op_logical_or
id|show_unmerged
)paren
id|die
c_func
(paren
l_string|&quot;ls-files --with-tree is incompatible with -s or -u&quot;
)paren
suffix:semicolon
id|overlay_tree_on_cache
c_func
(paren
id|with_tree
comma
id|max_prefix
)paren
suffix:semicolon
)brace
id|show_files
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_resolve_undo
)paren
id|show_ru_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ps_matched
)paren
(brace
r_int
id|bad
suffix:semicolon
id|bad
op_assign
id|report_path_error
c_func
(paren
id|ps_matched
comma
op_amp
id|pathspec
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Did you forget to &squot;git add&squot;?&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|bad
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
