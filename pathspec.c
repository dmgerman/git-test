macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;pathspec.h&quot;
multiline_comment|/*&n; * Finds which of the given pathspecs match items in the index.&n; *&n; * For each pathspec, sets the corresponding entry in the seen[] array&n; * (which should be specs items long, i.e. the same size as pathspec)&n; * to the nature of the &quot;closest&quot; (i.e. most specific) match found for&n; * that pathspec in the index, if it was a closer type of match than&n; * the existing entry.  As an optimization, matching is skipped&n; * altogether if seen[] already only contains non-zero entries.&n; *&n; * If seen[] has not already been written to, it may make sense&n; * to use find_used_pathspec() instead.&n; */
DECL|function|fill_pathspec_matches
r_void
id|fill_pathspec_matches
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
comma
r_char
op_star
id|seen
comma
r_int
id|specs
)paren
(brace
r_int
id|num_unmatched
op_assign
l_int|0
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Since we are walking the index as if we were walking the directory,&n;&t; * we have to mark the matched pathspec as seen; otherwise we will&n;&t; * mistakenly think that the user gave a pathspec that did not match&n;&t; * anything.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|specs
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
)paren
id|num_unmatched
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_unmatched
)paren
r_return
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
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Finds which of the given pathspecs match items in the index.&n; *&n; * This is a one-shot wrapper around fill_pathspec_matches() which&n; * allocates, populates, and returns a seen[] array indicating the&n; * nature of the &quot;closest&quot; (i.e. most specific) matches which each of&n; * the given pathspecs achieves against all items in the index.&n; */
DECL|function|find_used_pathspec
r_char
op_star
id|find_used_pathspec
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_char
op_star
id|seen
suffix:semicolon
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
id|pathspec
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
multiline_comment|/* just counting */
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
id|fill_pathspec_matches
c_func
(paren
id|pathspec
comma
id|seen
comma
id|i
)paren
suffix:semicolon
r_return
id|seen
suffix:semicolon
)brace
eof
