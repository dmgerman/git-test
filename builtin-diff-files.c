multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|diff_files_usage
r_static
r_const
r_char
id|diff_files_usage
(braket
)braket
op_assign
l_string|&quot;git-diff-files [-q] [-0/-1/2/3 |-c|--cc] [&lt;common diff options&gt;] [&lt;path&gt;...]&quot;
id|COMMON_DIFF_OPTIONS_HELP
suffix:semicolon
DECL|function|cmd_diff_files
r_int
id|cmd_diff_files
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
id|result
suffix:semicolon
r_int
id|options
op_assign
l_int|0
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
id|git_diff_basic_config
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
r_while
c_loop
(paren
l_int|1
OL
id|argc
op_logical_and
id|argv
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
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
l_int|1
)braket
comma
l_string|&quot;--base&quot;
)paren
)paren
id|rev.max_count
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--ours&quot;
)paren
)paren
id|rev.max_count
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--theirs&quot;
)paren
)paren
id|rev.max_count
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-q&quot;
)paren
)paren
id|options
op_or_assign
id|DIFF_SILENT_ON_REMOVED
suffix:semicolon
r_else
id|usage
c_func
(paren
id|diff_files_usage
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
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
multiline_comment|/*&n;&t; * Make sure there are NO revision (i.e. pending object) parameter,&n;&t; * rev.max_count is reasonable (0 &lt;= n &lt;= 3), and&n;&t; * there is no other revision filtering parameters.&n;&t; */
r_if
c_cond
(paren
id|rev.pending.nr
op_logical_or
id|rev.min_age
op_ne
l_int|1
op_logical_or
id|rev.max_age
op_ne
l_int|1
op_logical_or
l_int|3
OL
id|rev.max_count
)paren
id|usage
c_func
(paren
id|diff_files_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev.max_count
op_eq
l_int|1
op_logical_and
(paren
id|rev.diffopt.output_format
op_amp
id|DIFF_FORMAT_PATCH
)paren
)paren
id|rev.combine_merges
op_assign
id|rev.dense_combined_merges
op_assign
l_int|1
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
id|result
op_assign
id|run_diff_files
c_func
(paren
op_amp
id|rev
comma
id|options
)paren
suffix:semicolon
r_return
id|diff_result_code
c_func
(paren
op_amp
id|rev.diffopt
comma
id|result
)paren
suffix:semicolon
)brace
eof
