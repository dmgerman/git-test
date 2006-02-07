macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|variable|show_root_diff
r_static
r_int
id|show_root_diff
op_assign
l_int|0
suffix:semicolon
DECL|variable|no_commit_id
r_static
r_int
id|no_commit_id
op_assign
l_int|0
suffix:semicolon
DECL|variable|verbose_header
r_static
r_int
id|verbose_header
op_assign
l_int|0
suffix:semicolon
DECL|variable|ignore_merges
r_static
r_int
id|ignore_merges
op_assign
l_int|1
suffix:semicolon
DECL|variable|combine_merges
r_static
r_int
id|combine_merges
op_assign
l_int|0
suffix:semicolon
DECL|variable|dense_combined_merges
r_static
r_int
id|dense_combined_merges
op_assign
l_int|0
suffix:semicolon
DECL|variable|read_stdin
r_static
r_int
id|read_stdin
op_assign
l_int|0
suffix:semicolon
DECL|variable|always_show_header
r_static
r_int
id|always_show_header
op_assign
l_int|0
suffix:semicolon
DECL|variable|header
r_static
r_const
r_char
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|header_prefix
r_static
r_const
r_char
op_star
id|header_prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|commit_format
r_static
r_enum
id|cmit_fmt
id|commit_format
op_assign
id|CMIT_FMT_RAW
suffix:semicolon
DECL|variable|diff_options
r_static
r_struct
id|diff_options
id|diff_options
suffix:semicolon
DECL|function|call_diff_flush
r_static
r_int
id|call_diff_flush
c_func
(paren
r_void
)paren
(brace
id|diffcore_std
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_queue_is_empty
c_func
(paren
)paren
)paren
(brace
r_int
id|saved_fmt
op_assign
id|diff_options.output_format
suffix:semicolon
id|diff_options.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
id|diff_options.output_format
op_assign
id|saved_fmt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|header
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|no_commit_id
)paren
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|header
comma
id|diff_options.line_termination
)paren
suffix:semicolon
id|header
op_assign
l_int|NULL
suffix:semicolon
)brace
id|diff_flush
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|diff_tree_sha1_top
r_static
r_int
id|diff_tree_sha1_top
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
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|diff_tree_sha1
c_func
(paren
id|old
comma
r_new
comma
id|base
comma
op_amp
id|diff_options
)paren
suffix:semicolon
id|call_diff_flush
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|diff_root_tree
r_static
r_int
id|diff_root_tree
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
)paren
(brace
r_int
id|retval
suffix:semicolon
r_void
op_star
id|tree
suffix:semicolon
r_struct
id|tree_desc
id|empty
comma
id|real
suffix:semicolon
id|tree
op_assign
id|read_object_with_reference
c_func
(paren
r_new
comma
l_string|&quot;tree&quot;
comma
op_amp
id|real.size
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
l_string|&quot;unable to read root tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
r_new
)paren
)paren
suffix:semicolon
id|real.buf
op_assign
id|tree
suffix:semicolon
id|empty.buf
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|empty.size
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|diff_tree
c_func
(paren
op_amp
id|empty
comma
op_amp
id|real
comma
id|base
comma
op_amp
id|diff_options
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
id|call_diff_flush
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|generate_header
r_static
r_const
r_char
op_star
id|generate_header
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_int
r_char
op_star
id|parent_sha1
comma
r_const
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_static
r_char
id|this_header
(braket
l_int|16384
)braket
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
id|abbrev
op_assign
id|diff_options.abbrev
suffix:semicolon
r_const
r_char
op_star
id|msg
op_assign
id|commit-&gt;buffer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose_header
)paren
r_return
id|sha1_to_hex
c_func
(paren
id|commit_sha1
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|msg
)paren
suffix:semicolon
id|offset
op_assign
id|sprintf
c_func
(paren
id|this_header
comma
l_string|&quot;%s%s &quot;
comma
id|header_prefix
comma
id|diff_unique_abbrev
c_func
(paren
id|commit_sha1
comma
id|abbrev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_sha1
op_ne
id|parent_sha1
)paren
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|this_header
op_plus
id|offset
comma
l_string|&quot;(from %s)&bslash;n&quot;
comma
id|parent_sha1
ques
c_cond
id|diff_unique_abbrev
c_func
(paren
id|parent_sha1
comma
id|abbrev
)paren
suffix:colon
l_string|&quot;root&quot;
)paren
suffix:semicolon
r_else
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|this_header
op_plus
id|offset
comma
l_string|&quot;(from parents)&bslash;n&quot;
)paren
suffix:semicolon
id|offset
op_add_assign
id|pretty_print_commit
c_func
(paren
id|commit_format
comma
id|commit
comma
id|len
comma
id|this_header
op_plus
id|offset
comma
r_sizeof
(paren
id|this_header
)paren
id|offset
comma
id|abbrev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|always_show_header
)paren
(brace
id|puts
c_func
(paren
id|this_header
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|this_header
suffix:semicolon
)brace
DECL|function|diff_tree_commit
r_static
r_int
id|diff_tree_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
r_const
r_char
op_star
id|sha1
op_assign
id|commit-&gt;object.sha1
suffix:semicolon
multiline_comment|/* Root commit? */
r_if
c_cond
(paren
id|show_root_diff
op_logical_and
op_logical_neg
id|commit-&gt;parents
)paren
(brace
id|header
op_assign
id|generate_header
c_func
(paren
id|sha1
comma
l_int|NULL
comma
id|commit
)paren
suffix:semicolon
id|diff_root_tree
c_func
(paren
id|sha1
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* More than one parent? */
r_if
c_cond
(paren
id|commit-&gt;parents
op_logical_and
id|commit-&gt;parents-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|ignore_merges
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|combine_merges
)paren
(brace
id|header
op_assign
id|generate_header
c_func
(paren
id|sha1
comma
id|sha1
comma
id|commit
)paren
suffix:semicolon
r_return
id|diff_tree_combined_merge
c_func
(paren
id|sha1
comma
id|header
comma
id|dense_combined_merges
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
id|header
op_assign
id|generate_header
c_func
(paren
id|sha1
comma
id|parent-&gt;object.sha1
comma
id|commit
)paren
suffix:semicolon
id|diff_tree_sha1_top
c_func
(paren
id|parent-&gt;object.sha1
comma
id|sha1
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
op_logical_and
id|verbose_header
)paren
(brace
id|header_prefix
op_assign
l_string|&quot;&bslash;ndiff-tree &quot;
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Don&squot;t print multiple merge entries if we&n;&t;&t;&t; * don&squot;t print the diffs.&n;&t;&t;&t; */
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_tree_commit_sha1
r_static
r_int
id|diff_tree_commit_sha1
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit
op_star
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
r_return
l_int|1
suffix:semicolon
r_return
id|diff_tree_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
)brace
DECL|function|diff_tree_stdin
r_static
r_int
id|diff_tree_stdin
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|line
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|commit
op_assign
id|lookup_commit
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
op_logical_or
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|line
(braket
l_int|40
)braket
)paren
op_logical_and
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|41
comma
id|sha1
)paren
)paren
(brace
multiline_comment|/* Graft the fake parents locally to the commit */
r_int
id|pos
op_assign
l_int|41
suffix:semicolon
r_struct
id|commit_list
op_star
op_star
id|pptr
comma
op_star
id|parents
suffix:semicolon
multiline_comment|/* Free the real parent list */
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
)paren
(brace
r_struct
id|commit_list
op_star
id|tmp
op_assign
id|parents-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|parents
)paren
suffix:semicolon
id|parents
op_assign
id|tmp
suffix:semicolon
)brace
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
id|pptr
op_assign
op_amp
(paren
id|commit-&gt;parents
)paren
suffix:semicolon
r_while
c_loop
(paren
id|line
(braket
id|pos
)braket
op_logical_and
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|line
op_plus
id|pos
comma
id|sha1
)paren
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|lookup_commit
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
(brace
id|pptr
op_assign
op_amp
id|commit_list_insert
c_func
(paren
id|parent
comma
id|pptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
id|pos
op_add_assign
l_int|41
suffix:semicolon
)brace
)brace
r_return
id|diff_tree_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
)brace
DECL|variable|diff_tree_usage
r_static
r_const
r_char
id|diff_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-diff-tree [--stdin] [-m] [-c] [--cc] [-s] [-v] [--pretty] [-t] [-r] [--root] &quot;
l_string|&quot;[&lt;common diff options&gt;] &lt;tree-ish&gt; [&lt;tree-ish&gt;] [&lt;path&gt;...]&bslash;n&quot;
l_string|&quot;  -r            diff recursively&bslash;n&quot;
l_string|&quot;  --root        include the initial commit as diff against /dev/null&bslash;n&quot;
id|COMMON_DIFF_OPTIONS_HELP
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
id|nr_sha1
suffix:semicolon
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|2
)braket
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_diff_config
)paren
suffix:semicolon
id|nr_sha1
op_assign
l_int|0
suffix:semicolon
id|diff_setup
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|diff_opt_cnt
suffix:semicolon
r_const
r_char
op_star
id|arg
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|arg
op_assign
op_star
id|argv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_ne
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|nr_sha1
OL
l_int|2
op_logical_and
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
(braket
id|nr_sha1
)braket
)paren
)paren
(brace
id|nr_sha1
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|diff_opt_cnt
op_assign
id|diff_opt_parse
c_func
(paren
op_amp
id|diff_options
comma
id|argv
comma
id|argc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_opt_cnt
OL
l_int|0
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|diff_opt_cnt
)paren
(brace
id|argv
op_add_assign
id|diff_opt_cnt
l_int|1
suffix:semicolon
id|argc
op_sub_assign
id|diff_opt_cnt
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
l_string|&quot;--&quot;
)paren
)paren
(brace
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_break
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
l_string|&quot;-r&quot;
)paren
)paren
(brace
id|diff_options.recursive
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
l_string|&quot;-t&quot;
)paren
)paren
(brace
id|diff_options.recursive
op_assign
l_int|1
suffix:semicolon
id|diff_options.tree_in_recursive
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
l_string|&quot;-m&quot;
)paren
)paren
(brace
id|ignore_merges
op_assign
l_int|0
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
l_string|&quot;-c&quot;
)paren
)paren
(brace
id|combine_merges
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
l_string|&quot;--cc&quot;
)paren
)paren
(brace
id|dense_combined_merges
op_assign
id|combine_merges
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
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|verbose_header
op_assign
l_int|1
suffix:semicolon
id|header_prefix
op_assign
l_string|&quot;diff-tree &quot;
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
l_string|&quot;--pretty&quot;
comma
l_int|8
)paren
)paren
(brace
id|verbose_header
op_assign
l_int|1
suffix:semicolon
id|header_prefix
op_assign
l_string|&quot;diff-tree &quot;
suffix:semicolon
id|commit_format
op_assign
id|get_commit_format
c_func
(paren
id|arg
op_plus
l_int|8
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
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
id|read_stdin
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
l_string|&quot;--root&quot;
)paren
)paren
(brace
id|show_root_diff
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
l_string|&quot;--no-commit-id&quot;
)paren
)paren
(brace
id|no_commit_id
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
l_string|&quot;--always&quot;
)paren
)paren
(brace
id|always_show_header
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|combine_merges
)paren
(brace
id|diff_options.output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
id|ignore_merges
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|diff_options.output_format
op_eq
id|DIFF_FORMAT_PATCH
)paren
id|diff_options.recursive
op_assign
l_int|1
suffix:semicolon
id|diff_tree_setup_paths
c_func
(paren
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
)paren
)paren
suffix:semicolon
id|diff_setup_done
c_func
(paren
op_amp
id|diff_options
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nr_sha1
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|read_stdin
)paren
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|diff_tree_commit_sha1
c_func
(paren
id|sha1
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|diff_tree_sha1_top
c_func
(paren
id|sha1
(braket
l_int|0
)braket
comma
id|sha1
(braket
l_int|1
)braket
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|read_stdin
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|diff_options.detect_rename
)paren
id|diff_options.setup
op_or_assign
(paren
id|DIFF_SETUP_USE_SIZE_CACHE
op_or
id|DIFF_SETUP_USE_CACHE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
)paren
id|diff_tree_stdin
c_func
(paren
id|line
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
