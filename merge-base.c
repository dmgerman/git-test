macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|macro|PARENT1
mdefine_line|#define PARENT1 1
DECL|macro|PARENT2
mdefine_line|#define PARENT2 2
DECL|macro|UNINTERESTING
mdefine_line|#define UNINTERESTING 4
DECL|function|interesting
r_static
r_struct
id|commit
op_star
id|interesting
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
r_return
id|commit
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * A pathological example of how this thing works.&n; *&n; * Suppose we had this commit graph, where chronologically&n; * the timestamp on the commit are A &lt;= B &lt;= C &lt;= D &lt;= E &lt;= F&n; * and we are trying to figure out the merge base for E and F&n; * commits.&n; *&n; *                  F&n; *                 / &bslash;&n; *            E   A   D&n; *             &bslash; /   /  &n; *              B   /&n; *               &bslash; /&n; *                C&n; *&n; * First we push E and F to list to be processed.  E gets bit 1&n; * and F gets bit 2.  The list becomes:&n; *&n; *     list=F(2) E(1), result=empty&n; *&n; * Then we pop F, the newest commit, from the list.  Its flag is 2.&n; * We scan its parents, mark them reachable from the side that F is&n; * reachable from, and push them to the list:&n; *&n; *     list=E(1) D(2) A(2), result=empty&n; *&n; * Next pop E and do the same.&n; *&n; *     list=D(2) B(1) A(2), result=empty&n; *&n; * Next pop D and do the same.&n; *&n; *     list=C(2) B(1) A(2), result=empty&n; *&n; * Next pop C and do the same.&n; *&n; *     list=B(1) A(2), result=empty&n; *&n; * Now it is B&squot;s turn.  We mark its parent, C, reachable from B&squot;s side,&n; * and push it to the list:&n; *&n; *     list=C(3) A(2), result=empty&n; *&n; * Now pop C and notice it has flags==3.  It is placed on the result list,&n; * and the list now contains:&n; *&n; *     list=A(2), result=C(3)&n; *&n; * We pop A and do the same.&n; * &n; *     list=B(3), result=C(3)&n; *&n; * Next, we pop B and something very interesting happens.  It has flags==3&n; * so it is also placed on the result list, and its parents are marked&n; * uninteresting, retroactively, and placed back on the list:&n; *&n; *    list=C(7), result=C(7) B(3)&n; * &n; * Now, list does not have any interesting commit.  So we find the newest&n; * commit from the result list that is not marked uninteresting.  Which is&n; * commit B.&n; */
DECL|variable|show_all
r_static
r_int
id|show_all
op_assign
l_int|0
suffix:semicolon
DECL|function|merge_base
r_static
r_int
id|merge_base
c_func
(paren
r_struct
id|commit
op_star
id|rev1
comma
r_struct
id|commit
op_star
id|rev2
)paren
(brace
r_struct
id|commit_list
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|rev1
op_eq
id|rev2
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|rev1-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|parse_commit
c_func
(paren
id|rev1
)paren
suffix:semicolon
id|parse_commit
c_func
(paren
id|rev2
)paren
suffix:semicolon
id|rev1-&gt;object.flags
op_or_assign
l_int|1
suffix:semicolon
id|rev2-&gt;object.flags
op_or_assign
l_int|2
suffix:semicolon
id|insert_by_date
c_func
(paren
id|rev1
comma
op_amp
id|list
)paren
suffix:semicolon
id|insert_by_date
c_func
(paren
id|rev2
comma
op_amp
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|interesting
c_func
(paren
id|list
)paren
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
r_struct
id|commit_list
op_star
id|tmp
op_assign
id|list
comma
op_star
id|parents
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
op_amp
l_int|7
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_eq
l_int|3
)paren
(brace
id|insert_by_date
c_func
(paren
id|commit
comma
op_amp
id|result
)paren
suffix:semicolon
multiline_comment|/* Mark parents of a found merge uninteresting */
id|flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
)brace
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|p
op_assign
id|parents-&gt;item
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;object.flags
op_amp
id|flags
)paren
op_eq
id|flags
)paren
r_continue
suffix:semicolon
id|parse_commit
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;object.flags
op_or_assign
id|flags
suffix:semicolon
id|insert_by_date
c_func
(paren
id|p
comma
op_amp
id|list
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|result
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|result-&gt;item
suffix:semicolon
id|result
op_assign
id|result-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_all
)paren
r_return
l_int|0
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|merge_base_usage
r_static
r_const
r_char
id|merge_base_usage
(braket
)braket
op_assign
l_string|&quot;git-merge-base [--all] &lt;commit-id&gt; &lt;commit-id&gt;&quot;
suffix:semicolon
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
r_struct
id|commit
op_star
id|rev1
comma
op_star
id|rev2
suffix:semicolon
r_int
r_char
id|rev1key
(braket
l_int|20
)braket
comma
id|rev2key
(braket
l_int|20
)braket
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
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
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
l_string|&quot;-a&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
id|show_all
op_assign
l_int|1
suffix:semicolon
r_else
id|usage
c_func
(paren
id|merge_base_usage
)paren
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
op_logical_or
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|rev1key
)paren
op_logical_or
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|rev2key
)paren
)paren
id|usage
c_func
(paren
id|merge_base_usage
)paren
suffix:semicolon
id|rev1
op_assign
id|lookup_commit_reference
c_func
(paren
id|rev1key
)paren
suffix:semicolon
id|rev2
op_assign
id|lookup_commit_reference
c_func
(paren
id|rev2key
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev1
op_logical_or
op_logical_neg
id|rev2
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|merge_base
c_func
(paren
id|rev1
comma
id|rev2
)paren
suffix:semicolon
)brace
eof
