macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
multiline_comment|/*&n; * revision.h leaves the low 16 bits of the &quot;flags&quot; field of the&n; * revision data structure unused. We use it for a &quot;reachable from&n; * this commit &lt;N&gt;&quot; bitmask.&n; */
DECL|macro|MAX_COMMITS
mdefine_line|#define MAX_COMMITS 16
DECL|variable|show_edges
r_static
r_int
id|show_edges
op_assign
l_int|0
suffix:semicolon
DECL|variable|basemask
r_static
r_int
id|basemask
op_assign
l_int|0
suffix:semicolon
DECL|function|read_cache_file
r_static
r_void
id|read_cache_file
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|die
c_func
(paren
l_string|&quot;no revtree cache file yet&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Some revisions are less interesting than others.&n; *&n; * For example, if we use a cache-file, that one may contain&n; * revisions that were never used. They are never interesting.&n; *&n; * And sometimes we&squot;re only interested in &quot;edge&quot; commits, ie&n; * places where the marking changes between parent and child.&n; */
DECL|function|interesting
r_static
r_int
id|interesting
c_func
(paren
r_struct
id|commit
op_star
id|rev
)paren
(brace
r_int
id|mask
op_assign
id|rev-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|show_edges
)paren
(brace
r_struct
id|commit_list
op_star
id|p
op_assign
id|rev-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|mask
op_ne
id|p-&gt;item-&gt;object.flags
)paren
r_return
l_int|1
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
op_amp
id|basemask
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|process_commit
r_void
id|process_commit
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_struct
id|commit
op_star
id|obj
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
id|obj
op_logical_and
id|obj-&gt;object.parsed
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
op_logical_or
id|parse_commit
c_func
(paren
id|obj
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to parse commit (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|parents
op_assign
id|obj-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
id|process_commit
c_func
(paren
id|parents-&gt;item-&gt;object.sha1
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Usage: git-rev-tree [--edges] [--cache &lt;cache-file&gt;] &lt;commit-id&gt; [&lt;commit-id2&gt;]&n; *&n; * The cache-file can be quite important for big trees. This is an&n; * expensive operation if you have to walk the whole chain of&n; * parents in a tree with a long revision history.&n; */
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|sha1
(braket
id|MAX_COMMITS
)braket
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * First - pick up all the revisions we can (both from&n;&t; * caches and from commit file chains).&n;&t; */
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
l_string|&quot;--cache&quot;
)paren
)paren
(brace
id|read_cache_file
c_func
(paren
id|argv
(braket
op_increment
id|i
)braket
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
l_string|&quot;--edges&quot;
)paren
)paren
(brace
id|show_edges
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;^&squot;
)paren
(brace
id|arg
op_increment
suffix:semicolon
id|basemask
op_or_assign
l_int|1
op_lshift
id|nr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr
op_ge
id|MAX_COMMITS
op_logical_or
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
(braket
id|nr
)braket
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;git-rev-tree [--edges] [--cache &lt;cache-file&gt;] &lt;commit-id&gt; [&lt;commit-id&gt;]&quot;
)paren
suffix:semicolon
id|process_commit
c_func
(paren
id|sha1
(braket
id|nr
)braket
)paren
suffix:semicolon
id|nr
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now we have the maximal tree. Walk the different sha files back to the root.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
id|mark_reachable
c_func
(paren
op_amp
id|lookup_commit
c_func
(paren
id|sha1
(braket
id|i
)braket
)paren
op_member_access_from_pointer
id|object
comma
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now print out the results..&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_objs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|objs
(braket
id|i
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|commit_type
)paren
r_continue
suffix:semicolon
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|obj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interesting
c_func
(paren
id|commit
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%lu %s:%d&quot;
comma
id|commit-&gt;date
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
id|obj-&gt;flags
)paren
suffix:semicolon
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|printf
c_func
(paren
l_string|&quot; %s:%d&quot;
comma
id|sha1_to_hex
c_func
(paren
id|p-&gt;item-&gt;object.sha1
)paren
comma
id|p-&gt;item-&gt;object.flags
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
