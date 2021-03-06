macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;submodule.h&quot;
DECL|variable|log_tree_opt
r_static
r_struct
id|rev_info
id|log_tree_opt
suffix:semicolon
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
id|log_tree_commit
c_func
(paren
op_amp
id|log_tree_opt
comma
id|commit
)paren
suffix:semicolon
)brace
multiline_comment|/* Diff one or more commits. */
DECL|function|stdin_diff_commit
r_static
r_int
id|stdin_diff_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_char
op_star
id|line
comma
r_int
id|len
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
suffix:semicolon
multiline_comment|/* Free the real parent list */
id|free_commit_list
c_func
(paren
id|commit-&gt;parents
)paren
suffix:semicolon
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
id|log_tree_commit
c_func
(paren
op_amp
id|log_tree_opt
comma
id|commit
)paren
suffix:semicolon
)brace
multiline_comment|/* Diff two trees. */
DECL|function|stdin_diff_trees
r_static
r_int
id|stdin_diff_trees
c_func
(paren
r_struct
id|tree
op_star
id|tree1
comma
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|tree
op_star
id|tree2
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
l_int|82
op_logical_or
op_logical_neg
id|isspace
c_func
(paren
id|line
(braket
l_int|40
)braket
)paren
op_logical_or
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
r_return
id|error
c_func
(paren
l_string|&quot;Need exactly two trees, separated by a space&quot;
)paren
suffix:semicolon
id|tree2
op_assign
id|lookup_tree
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree2
op_logical_or
id|parse_tree
c_func
(paren
id|tree2
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|oid_to_hex
c_func
(paren
op_amp
id|tree1-&gt;object.oid
)paren
comma
id|oid_to_hex
c_func
(paren
op_amp
id|tree2-&gt;object.oid
)paren
)paren
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|tree1-&gt;object.oid.hash
comma
id|tree2-&gt;object.oid.hash
comma
l_string|&quot;&quot;
comma
op_amp
id|log_tree_opt.diffopt
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
op_amp
id|log_tree_opt
)paren
suffix:semicolon
r_return
l_int|0
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
id|object
op_star
id|obj
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
id|obj
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_COMMIT
)paren
r_return
id|stdin_diff_commit
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
comma
id|line
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
r_return
id|stdin_diff_trees
c_func
(paren
(paren
r_struct
id|tree
op_star
)paren
id|obj
comma
id|line
comma
id|len
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;Object %s is a %s, not a commit or tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_typename
(paren
id|obj-&gt;type
)paren
)paren
suffix:semicolon
r_return
l_int|1
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
l_string|&quot;git diff-tree [--stdin] [-m] [-c] [--cc] [-s] [-v] [--pretty] [-t] [-r] [--root] &quot;
l_string|&quot;[&lt;common-diff-options&gt;] &lt;tree-ish&gt; [&lt;tree-ish&gt;] [&lt;path&gt;...]&bslash;n&quot;
l_string|&quot;  -r            diff recursively&bslash;n&quot;
l_string|&quot;  --root        include the initial commit as diff against /dev/null&bslash;n&quot;
id|COMMON_DIFF_OPTIONS_HELP
suffix:semicolon
DECL|function|diff_tree_tweak_rev
r_static
r_void
id|diff_tree_tweak_rev
c_func
(paren
r_struct
id|rev_info
op_star
id|rev
comma
r_struct
id|setup_revision_opt
op_star
id|opt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rev-&gt;diffopt.output_format
)paren
(brace
r_if
c_cond
(paren
id|rev-&gt;dense_combined_merges
)paren
id|rev-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
r_else
id|rev-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_RAW
suffix:semicolon
)brace
)brace
DECL|function|cmd_diff_tree
r_int
id|cmd_diff_tree
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
id|nr_sha1
suffix:semicolon
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_struct
id|object
op_star
id|tree1
comma
op_star
id|tree2
suffix:semicolon
r_static
r_struct
id|rev_info
op_star
id|opt
op_assign
op_amp
id|log_tree_opt
suffix:semicolon
r_struct
id|setup_revision_opt
id|s_r_opt
suffix:semicolon
r_int
id|read_stdin
op_assign
l_int|0
suffix:semicolon
id|init_revisions
c_func
(paren
id|opt
comma
id|prefix
)paren
suffix:semicolon
id|gitmodules_config
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_diff_basic_config
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* no &quot;diff&quot; UI options */
id|opt-&gt;abbrev
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;diff
op_assign
l_int|1
suffix:semicolon
id|opt-&gt;disable_stdin
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|s_r_opt
comma
l_int|0
comma
r_sizeof
(paren
id|s_r_opt
)paren
)paren
suffix:semicolon
id|s_r_opt.tweak
op_assign
id|diff_tree_tweak_rev
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
id|opt
comma
op_amp
id|s_r_opt
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|argc
OG
l_int|0
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
op_star
op_increment
id|argv
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
id|usage
c_func
(paren
id|diff_tree_usage
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * NOTE! We expect &quot;a ^b&quot; to be equal to &quot;a..b&quot;, so we&n;&t; * reverse the order of the objects if the second one&n;&t; * is marked UNINTERESTING.&n;&t; */
id|nr_sha1
op_assign
id|opt-&gt;pending.nr
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
id|tree1
op_assign
id|opt-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|item
suffix:semicolon
id|diff_tree_commit_sha1
c_func
(paren
id|tree1-&gt;oid.hash
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tree1
op_assign
id|opt-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|item
suffix:semicolon
id|tree2
op_assign
id|opt-&gt;pending.objects
(braket
l_int|1
)braket
dot
id|item
suffix:semicolon
r_if
c_cond
(paren
id|tree2-&gt;flags
op_amp
id|UNINTERESTING
)paren
(brace
r_struct
id|object
op_star
id|tmp
op_assign
id|tree2
suffix:semicolon
id|tree2
op_assign
id|tree1
suffix:semicolon
id|tree1
op_assign
id|tmp
suffix:semicolon
)brace
id|diff_tree_sha1
c_func
(paren
id|tree1-&gt;oid.hash
comma
id|tree2-&gt;oid.hash
comma
l_string|&quot;&quot;
comma
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
id|opt
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_stdin
)paren
(brace
r_int
id|saved_nrl
op_assign
l_int|0
suffix:semicolon
r_int
id|saved_dcctc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;diffopt.detect_rename
)paren
id|opt-&gt;diffopt.setup
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
id|get_sha1_hex
c_func
(paren
id|line
comma
id|sha1
)paren
)paren
(brace
id|fputs
c_func
(paren
id|line
comma
id|stdout
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
r_else
(brace
id|diff_tree_stdin
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_nrl
OL
id|opt-&gt;diffopt.needed_rename_limit
)paren
id|saved_nrl
op_assign
id|opt-&gt;diffopt.needed_rename_limit
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;diffopt.degraded_cc_to_c
)paren
id|saved_dcctc
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|opt-&gt;diffopt.degraded_cc_to_c
op_assign
id|saved_dcctc
suffix:semicolon
id|opt-&gt;diffopt.needed_rename_limit
op_assign
id|saved_nrl
suffix:semicolon
)brace
r_return
id|diff_result_code
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
