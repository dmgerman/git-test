macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;log-tree.h&quot;
DECL|function|log_tree_diff_flush
r_int
id|log_tree_diff_flush
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
)paren
(brace
id|diffcore_std
c_func
(paren
op_amp
id|opt-&gt;diffopt
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
id|opt-&gt;diffopt.output_format
suffix:semicolon
id|opt-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|opt-&gt;diffopt.output_format
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
id|opt-&gt;header
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;no_commit_id
)paren
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|opt-&gt;header
comma
id|opt-&gt;diffopt.line_termination
)paren
suffix:semicolon
id|opt-&gt;header
op_assign
l_int|NULL
suffix:semicolon
)brace
id|diff_flush
c_func
(paren
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|diff_root_tree
r_static
r_int
id|diff_root_tree
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
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
id|tree_type
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
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
id|opt
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
r_struct
id|rev_info
op_star
id|opt
comma
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
id|opt-&gt;diffopt.abbrev
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
id|opt-&gt;verbose_header
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
id|opt-&gt;header_prefix
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
id|opt-&gt;commit_format
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
id|opt-&gt;always_show_header
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
DECL|function|do_diff_combined
r_static
r_int
id|do_diff_combined
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
comma
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_int
r_const
r_char
op_star
id|sha1
op_assign
id|commit-&gt;object.sha1
suffix:semicolon
id|opt-&gt;header
op_assign
id|generate_header
c_func
(paren
id|opt
comma
id|sha1
comma
id|sha1
comma
id|commit
)paren
suffix:semicolon
id|opt-&gt;header
op_assign
id|diff_tree_combined_merge
c_func
(paren
id|sha1
comma
id|opt-&gt;header
comma
id|opt-&gt;dense_combined_merges
comma
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;header
op_logical_and
id|opt-&gt;verbose_header
)paren
id|opt-&gt;header_prefix
op_assign
l_string|&quot;&bslash;ndiff-tree &quot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|log_tree_commit
r_int
id|log_tree_commit
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
comma
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
id|opt-&gt;show_root_diff
op_logical_and
op_logical_neg
id|commit-&gt;parents
)paren
(brace
id|opt-&gt;header
op_assign
id|generate_header
c_func
(paren
id|opt
comma
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
id|opt
comma
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
id|opt-&gt;ignore_merges
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt-&gt;combine_merges
)paren
r_return
id|do_diff_combined
c_func
(paren
id|opt
comma
id|commit
)paren
suffix:semicolon
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
r_int
r_const
r_char
op_star
id|psha1
op_assign
id|parent-&gt;object.sha1
suffix:semicolon
id|opt-&gt;header
op_assign
id|generate_header
c_func
(paren
id|opt
comma
id|sha1
comma
id|psha1
comma
id|commit
)paren
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|psha1
comma
id|sha1
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
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;header
op_logical_and
id|opt-&gt;verbose_header
)paren
id|opt-&gt;header_prefix
op_assign
l_string|&quot;&bslash;ndiff-tree &quot;
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
