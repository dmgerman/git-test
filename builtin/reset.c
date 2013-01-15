multiline_comment|/*&n; * &quot;git reset&quot; builtin command&n; *&n; * Copyright (c) 2007 Carlos Rica&n; *&n; * Based on git-reset.sh, which is&n; *&n; * Copyright (c) 2005, 2006 Linus Torvalds and Junio C Hamano&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;branch.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|variable|git_reset_usage
r_static
r_const
r_char
op_star
r_const
id|git_reset_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git reset [--mixed | --soft | --hard | --merge | --keep] [-q] [&lt;commit&gt;]&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git reset [-q] &lt;commit&gt; [--] &lt;paths&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git reset --patch [&lt;commit&gt;] [--] [&lt;paths&gt;...]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|enum|reset_type
DECL|enumerator|MIXED
DECL|enumerator|SOFT
DECL|enumerator|HARD
DECL|enumerator|MERGE
DECL|enumerator|KEEP
DECL|enumerator|NONE
r_enum
id|reset_type
(brace
id|MIXED
comma
id|SOFT
comma
id|HARD
comma
id|MERGE
comma
id|KEEP
comma
id|NONE
)brace
suffix:semicolon
DECL|variable|reset_type_names
r_static
r_const
r_char
op_star
id|reset_type_names
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;mixed&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;soft&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;hard&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;merge&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;keep&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|is_merge
r_static
r_inline
r_int
id|is_merge
c_func
(paren
r_void
)paren
(brace
r_return
op_logical_neg
id|access
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;MERGE_HEAD&quot;
)paren
comma
id|F_OK
)paren
suffix:semicolon
)brace
DECL|function|reset_index
r_static
r_int
id|reset_index
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|reset_type
comma
r_int
id|quiet
)paren
(brace
r_int
id|nr
op_assign
l_int|1
suffix:semicolon
r_struct
id|tree_desc
id|desc
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
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
id|opts.fn
op_assign
id|oneway_merge
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|opts.verbose_update
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|reset_type
)paren
(brace
r_case
id|KEEP
suffix:colon
r_case
id|MERGE
suffix:colon
id|opts.update
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HARD
suffix:colon
id|opts.update
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fallthrough */
r_default
suffix:colon
id|opts.reset
op_assign
l_int|1
suffix:semicolon
)brace
id|read_cache_unmerged
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset_type
op_eq
id|KEEP
)paren
(brace
r_int
r_char
id|head_sha1
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
id|head_sha1
)paren
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;You do not have a valid HEAD.&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fill_tree_descriptor
c_func
(paren
id|desc
comma
id|head_sha1
)paren
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Failed to find tree of HEAD.&quot;
)paren
)paren
suffix:semicolon
id|nr
op_increment
suffix:semicolon
id|opts.fn
op_assign
id|twoway_merge
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fill_tree_descriptor
c_func
(paren
id|desc
op_plus
id|nr
l_int|1
comma
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Failed to find tree of %s.&quot;
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unpack_trees
c_func
(paren
id|nr
comma
id|desc
comma
op_amp
id|opts
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|reset_type
op_eq
id|MIXED
op_logical_or
id|reset_type
op_eq
id|HARD
)paren
(brace
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|prime_cache_tree
c_func
(paren
op_amp
id|active_cache_tree
comma
id|tree
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_new_head_line
r_static
r_void
id|print_new_head_line
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_const
r_char
op_star
id|hex
comma
op_star
id|body
suffix:semicolon
id|hex
op_assign
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|DEFAULT_ABBREV
)paren
suffix:semicolon
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;HEAD is now at %s&quot;
)paren
comma
id|hex
)paren
suffix:semicolon
id|body
op_assign
id|strstr
c_func
(paren
id|commit-&gt;buffer
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|body
)paren
(brace
r_const
r_char
op_star
id|eol
suffix:semicolon
r_int
id|len
suffix:semicolon
id|body
op_add_assign
l_int|2
suffix:semicolon
id|eol
op_assign
id|strchr
c_func
(paren
id|body
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|len
op_assign
id|eol
ques
c_cond
id|eol
id|body
suffix:colon
id|strlen
c_func
(paren
id|body
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %.*s&bslash;n&quot;
comma
(paren
r_int
)paren
id|len
comma
id|body
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|update_index_refresh
r_static
r_int
id|update_index_refresh
c_func
(paren
r_int
id|fd
comma
r_struct
id|lock_file
op_star
id|index_lock
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|index_lock
)paren
(brace
id|index_lock
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
id|fd
op_assign
id|hold_locked_index
c_func
(paren
id|index_lock
comma
l_int|1
)paren
suffix:semicolon
)brace
id|refresh_index
c_func
(paren
op_amp
id|the_index
comma
(paren
id|flags
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
id|_
c_func
(paren
l_string|&quot;Unstaged changes after reset:&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|fd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
id|index_lock
)paren
)paren
r_return
id|error
(paren
l_string|&quot;Could not refresh index&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|update_index_from_diff
r_static
r_void
id|update_index_from_diff
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_options
op_star
id|opt
comma
r_void
op_star
id|data
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filespec
op_star
id|one
op_assign
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|one
suffix:semicolon
r_if
c_cond
(paren
id|one-&gt;mode
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|one-&gt;sha1
)paren
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
id|ce
op_assign
id|make_cache_entry
c_func
(paren
id|one-&gt;mode
comma
id|one-&gt;sha1
comma
id|one-&gt;path
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;make_cache_entry failed for path &squot;%s&squot;&quot;
)paren
comma
id|one-&gt;path
)paren
suffix:semicolon
id|add_cache_entry
c_func
(paren
id|ce
comma
id|ADD_CACHE_OK_TO_ADD
op_or
id|ADD_CACHE_OK_TO_REPLACE
)paren
suffix:semicolon
)brace
r_else
id|remove_file_from_cache
c_func
(paren
id|one-&gt;path
)paren
suffix:semicolon
)brace
)brace
DECL|function|read_from_tree
r_static
r_int
id|read_from_tree
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
comma
r_int
r_char
op_star
id|tree_sha1
comma
r_int
id|refresh_flags
)paren
(brace
r_struct
id|lock_file
op_star
id|lock
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
r_int
id|index_fd
suffix:semicolon
r_struct
id|diff_options
id|opt
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opt
comma
l_int|0
comma
r_sizeof
(paren
id|opt
)paren
)paren
suffix:semicolon
id|diff_tree_setup_paths
c_func
(paren
id|pathspec
comma
op_amp
id|opt
)paren
suffix:semicolon
id|opt.output_format
op_assign
id|DIFF_FORMAT_CALLBACK
suffix:semicolon
id|opt.format_callback
op_assign
id|update_index_from_diff
suffix:semicolon
id|index_fd
op_assign
id|hold_locked_index
c_func
(paren
id|lock
comma
l_int|1
)paren
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_diff_cache
c_func
(paren
id|tree_sha1
comma
op_amp
id|opt
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|opt
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|opt
)paren
suffix:semicolon
id|diff_tree_release_paths
c_func
(paren
op_amp
id|opt
)paren
suffix:semicolon
r_return
id|update_index_refresh
c_func
(paren
id|index_fd
comma
id|lock
comma
id|refresh_flags
)paren
suffix:semicolon
)brace
DECL|function|set_reflog_message
r_static
r_void
id|set_reflog_message
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|action
comma
r_const
r_char
op_star
id|rev
)paren
(brace
r_const
r_char
op_star
id|rla
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_REFLOG_ACTION&quot;
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rla
)paren
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;%s: %s&quot;
comma
id|rla
comma
id|action
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rev
)paren
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;reset: moving to %s&quot;
comma
id|rev
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;reset: %s&quot;
comma
id|action
)paren
suffix:semicolon
)brace
DECL|function|die_if_unmerged_cache
r_static
r_void
id|die_if_unmerged_cache
c_func
(paren
r_int
id|reset_type
)paren
(brace
r_if
c_cond
(paren
id|is_merge
c_func
(paren
)paren
op_logical_or
id|read_cache
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|unmerged_cache
c_func
(paren
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Cannot do a %s reset in the middle of a merge.&quot;
)paren
comma
id|_
c_func
(paren
id|reset_type_names
(braket
id|reset_type
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|parse_args
r_static
r_const
r_char
op_star
op_star
id|parse_args
c_func
(paren
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
comma
r_const
r_char
op_star
op_star
id|rev_ret
)paren
(brace
r_const
r_char
op_star
id|rev
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
r_int
r_char
id|unused
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Possible arguments are:&n;&t; *&n;&t; * git reset [-opts] &lt;rev&gt; &lt;paths&gt;...&n;&t; * git reset [-opts] &lt;rev&gt; -- &lt;paths&gt;...&n;&t; * git reset [-opts] -- &lt;paths&gt;...&n;&t; * git reset [-opts] &lt;paths&gt;...&n;&t; *&n;&t; * At this point, argv points immediately after [-opts].&n;&t; */
r_if
c_cond
(paren
id|argv
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|argv
op_increment
suffix:semicolon
multiline_comment|/* reset to HEAD, possibly with paths */
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
l_int|1
)braket
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
l_string|&quot;--&quot;
)paren
)paren
(brace
id|rev
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|argv
op_add_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Otherwise, argv[0] could be either &lt;rev&gt; or &lt;paths&gt; and&n;&t;&t; * has to be unambiguous.&n;&t;&t; */
r_else
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_committish
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|unused
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Ok, argv[0] looks like a rev; it should not&n;&t;&t;&t; * be a filename.&n;&t;&t;&t; */
id|verify_non_filename
c_func
(paren
id|prefix
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|rev
op_assign
op_star
id|argv
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Otherwise we treat this as a filename */
id|verify_filename
c_func
(paren
id|prefix
comma
id|argv
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
op_star
id|rev_ret
op_assign
id|rev
suffix:semicolon
r_return
id|argv
(braket
l_int|0
)braket
ques
c_cond
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|update_refs
r_static
r_int
id|update_refs
c_func
(paren
r_const
r_char
op_star
id|rev
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|update_ref_status
suffix:semicolon
r_struct
id|strbuf
id|msg
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
r_char
op_star
id|orig
op_assign
l_int|NULL
comma
id|sha1_orig
(braket
l_int|20
)braket
comma
op_star
id|old_orig
op_assign
l_int|NULL
comma
id|sha1_old_orig
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
l_string|&quot;ORIG_HEAD&quot;
comma
id|sha1_old_orig
)paren
)paren
id|old_orig
op_assign
id|sha1_old_orig
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1_orig
)paren
)paren
(brace
id|orig
op_assign
id|sha1_orig
suffix:semicolon
id|set_reflog_message
c_func
(paren
op_amp
id|msg
comma
l_string|&quot;updating ORIG_HEAD&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|update_ref
c_func
(paren
id|msg.buf
comma
l_string|&quot;ORIG_HEAD&quot;
comma
id|orig
comma
id|old_orig
comma
l_int|0
comma
id|MSG_ON_ERR
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|old_orig
)paren
id|delete_ref
c_func
(paren
l_string|&quot;ORIG_HEAD&quot;
comma
id|old_orig
comma
l_int|0
)paren
suffix:semicolon
id|set_reflog_message
c_func
(paren
op_amp
id|msg
comma
l_string|&quot;updating HEAD&quot;
comma
id|rev
)paren
suffix:semicolon
id|update_ref_status
op_assign
id|update_ref
c_func
(paren
id|msg.buf
comma
l_string|&quot;HEAD&quot;
comma
id|sha1
comma
id|orig
comma
l_int|0
comma
id|MSG_ON_ERR
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|msg
)paren
suffix:semicolon
r_return
id|update_ref_status
suffix:semicolon
)brace
DECL|function|cmd_reset
r_int
id|cmd_reset
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
id|reset_type
op_assign
id|NONE
comma
id|update_ref_status
op_assign
l_int|0
comma
id|quiet
op_assign
l_int|0
suffix:semicolon
r_int
id|patch_mode
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|rev
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
op_star
id|pathspec
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_const
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
id|N_
c_func
(paren
l_string|&quot;be quiet, only report errors&quot;
)paren
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;mixed&quot;
comma
op_amp
id|reset_type
comma
id|N_
c_func
(paren
l_string|&quot;reset HEAD and index&quot;
)paren
comma
id|MIXED
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;soft&quot;
comma
op_amp
id|reset_type
comma
id|N_
c_func
(paren
l_string|&quot;reset only HEAD&quot;
)paren
comma
id|SOFT
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;hard&quot;
comma
op_amp
id|reset_type
comma
id|N_
c_func
(paren
l_string|&quot;reset HEAD, index and working tree&quot;
)paren
comma
id|HARD
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;merge&quot;
comma
op_amp
id|reset_type
comma
id|N_
c_func
(paren
l_string|&quot;reset HEAD, index and working tree&quot;
)paren
comma
id|MERGE
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;keep&quot;
comma
op_amp
id|reset_type
comma
id|N_
c_func
(paren
l_string|&quot;reset HEAD but keep local changes&quot;
)paren
comma
id|KEEP
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;p&squot;
comma
l_string|&quot;patch&quot;
comma
op_amp
id|patch_mode
comma
id|N_
c_func
(paren
l_string|&quot;select hunks interactively&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
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
id|options
comma
id|git_reset_usage
comma
id|PARSE_OPT_KEEP_DASHDASH
)paren
suffix:semicolon
id|pathspec
op_assign
id|parse_args
c_func
(paren
id|argv
comma
id|prefix
comma
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_committish
c_func
(paren
id|rev
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Failed to resolve &squot;%s&squot; as a valid ref.&quot;
)paren
comma
id|rev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE: As &quot;git reset $treeish -- $path&quot; should be usable on&n;&t; * any tree-ish, this is not strictly correct. We are not&n;&t; * moving the HEAD to any commit; we are merely resetting the&n;&t; * entries in the index to that of a treeish.&n;&t; */
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not parse object &squot;%s&squot;.&quot;
)paren
comma
id|rev
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|sha1
comma
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|patch_mode
)paren
(brace
r_if
c_cond
(paren
id|reset_type
op_ne
id|NONE
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--patch is incompatible with --{hard,mixed,soft}&quot;
)paren
)paren
suffix:semicolon
r_return
id|run_add_interactive
c_func
(paren
id|rev
comma
l_string|&quot;--patch=reset&quot;
comma
id|pathspec
)paren
suffix:semicolon
)brace
multiline_comment|/* git reset tree [--] paths... can be used to&n;&t; * load chosen paths from the tree into the index without&n;&t; * affecting the working tree nor HEAD. */
r_if
c_cond
(paren
id|pathspec
)paren
(brace
r_if
c_cond
(paren
id|reset_type
op_eq
id|MIXED
)paren
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--mixed with paths is deprecated; use &squot;git reset -- &lt;paths&gt;&squot; instead.&quot;
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|reset_type
op_ne
id|NONE
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Cannot do %s reset with paths.&quot;
)paren
comma
id|_
c_func
(paren
id|reset_type_names
(braket
id|reset_type
)braket
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reset_type
op_eq
id|NONE
)paren
id|reset_type
op_assign
id|MIXED
suffix:semicolon
multiline_comment|/* by default */
r_if
c_cond
(paren
id|reset_type
op_ne
id|SOFT
op_logical_and
id|reset_type
op_ne
id|MIXED
)paren
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset_type
op_eq
id|MIXED
op_logical_and
id|is_bare_repository
c_func
(paren
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s reset is not allowed in a bare repository&quot;
)paren
comma
id|_
c_func
(paren
id|reset_type_names
(braket
id|reset_type
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
)paren
r_return
id|read_from_tree
c_func
(paren
id|pathspec
comma
id|sha1
comma
id|quiet
ques
c_cond
id|REFRESH_QUIET
suffix:colon
id|REFRESH_IN_PORCELAIN
)paren
suffix:semicolon
multiline_comment|/* Soft reset does not touch the index file nor the working tree&n;&t; * at all, but requires them in a good order.  Other resets reset&n;&t; * the index file to the tree object we are switching to. */
r_if
c_cond
(paren
id|reset_type
op_eq
id|SOFT
op_logical_or
id|reset_type
op_eq
id|KEEP
)paren
id|die_if_unmerged_cache
c_func
(paren
id|reset_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset_type
op_ne
id|SOFT
)paren
(brace
r_struct
id|lock_file
op_star
id|lock
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
r_int
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
id|lock
comma
l_int|1
)paren
suffix:semicolon
r_int
id|err
op_assign
id|reset_index
c_func
(paren
id|sha1
comma
id|reset_type
comma
id|quiet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset_type
op_eq
id|KEEP
op_logical_and
op_logical_neg
id|err
)paren
id|err
op_assign
id|reset_index
c_func
(paren
id|sha1
comma
id|MIXED
comma
id|quiet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not reset index file to revision &squot;%s&squot;.&quot;
)paren
comma
id|rev
)paren
suffix:semicolon
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
id|lock
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not write new index file.&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Any resets update HEAD to the head being switched to,&n;&t; * saving the previous head in ORIG_HEAD before. */
id|update_ref_status
op_assign
id|update_refs
c_func
(paren
id|rev
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset_type
op_eq
id|HARD
op_logical_and
op_logical_neg
id|update_ref_status
op_logical_and
op_logical_neg
id|quiet
)paren
id|print_new_head_line
c_func
(paren
id|commit
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|reset_type
op_eq
id|MIXED
)paren
multiline_comment|/* Report what has not been updated. */
id|update_index_refresh
c_func
(paren
l_int|0
comma
l_int|NULL
comma
id|quiet
ques
c_cond
id|REFRESH_QUIET
suffix:colon
id|REFRESH_IN_PORCELAIN
)paren
suffix:semicolon
id|remove_branch_state
c_func
(paren
)paren
suffix:semicolon
r_return
id|update_ref_status
suffix:semicolon
)brace
eof
