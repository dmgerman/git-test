macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|diff_cache_usage
r_static
r_const
r_char
id|diff_cache_usage
(braket
)braket
op_assign
l_string|&quot;git-diff-index [-m] [--cached] &quot;
l_string|&quot;[&lt;common diff options&gt;] &lt;tree-ish&gt; [&lt;path&gt;...]&quot;
id|COMMON_DIFF_OPTIONS_HELP
suffix:semicolon
DECL|function|cmd_diff_index
r_int
id|cmd_diff_index
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
r_struct
id|rev_info
id|rev
suffix:semicolon
r_int
id|cached
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
id|prefix
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
multiline_comment|/* no &quot;diff&quot; UI options */
id|rev.abbrev
op_assign
l_int|0
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
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
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
l_string|&quot;--cached&quot;
)paren
)paren
id|cached
op_assign
l_int|1
suffix:semicolon
r_else
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
op_logical_neg
id|rev.diffopt.output_format
)paren
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_RAW
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure there is one revision (i.e. pending object),&n;&t; * and there is no revision filtering parameters.&n;&t; */
r_if
c_cond
(paren
id|rev.pending.nr
op_ne
l_int|1
op_logical_or
id|rev.max_count
op_ne
l_int|1
op_logical_or
id|rev.min_age
op_ne
l_int|1
op_logical_or
id|rev.max_age
op_ne
l_int|1
)paren
id|usage
c_func
(paren
id|diff_cache_usage
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
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|run_diff_index
c_func
(paren
op_amp
id|rev
comma
id|cached
)paren
suffix:semicolon
)brace
eof
