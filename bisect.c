macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;list-objects.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;sha1-lookup.h&quot;
macro_line|#include &quot;bisect.h&quot;
DECL|variable|skipped_sha1
r_static
r_int
r_char
(paren
op_star
id|skipped_sha1
)paren
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|skipped_sha1_nr
r_static
r_int
id|skipped_sha1_nr
suffix:semicolon
DECL|variable|skipped_sha1_alloc
r_static
r_int
id|skipped_sha1_alloc
suffix:semicolon
DECL|variable|rev_argv
r_static
r_const
r_char
op_star
op_star
id|rev_argv
suffix:semicolon
DECL|variable|rev_argv_nr
r_static
r_int
id|rev_argv_nr
suffix:semicolon
DECL|variable|rev_argv_alloc
r_static
r_int
id|rev_argv_alloc
suffix:semicolon
multiline_comment|/* bits #0-15 in revision.h */
DECL|macro|COUNTED
mdefine_line|#define COUNTED&t;&t;(1u&lt;&lt;16)
multiline_comment|/*&n; * This is a truly stupid algorithm, but it&squot;s only&n; * used for bisection, and we just don&squot;t care enough.&n; *&n; * We care just barely enough to avoid recursing for&n; * non-merge entries.&n; */
DECL|function|count_distance
r_static
r_int
id|count_distance
c_func
(paren
r_struct
id|commit_list
op_star
id|entry
)paren
(brace
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|entry-&gt;item
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
(paren
id|UNINTERESTING
op_or
id|COUNTED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|TREESAME
)paren
)paren
id|nr
op_increment
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|COUNTED
suffix:semicolon
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|entry
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|nr
op_add_assign
id|count_distance
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
)brace
r_return
id|nr
suffix:semicolon
)brace
DECL|function|clear_distance
r_static
r_void
id|clear_distance
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
id|commit-&gt;object.flags
op_and_assign
op_complement
id|COUNTED
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
)brace
DECL|macro|DEBUG_BISECT
mdefine_line|#define DEBUG_BISECT 0
DECL|function|weight
r_static
r_inline
r_int
id|weight
c_func
(paren
r_struct
id|commit_list
op_star
id|elem
)paren
(brace
r_return
op_star
(paren
(paren
r_int
op_star
)paren
(paren
id|elem-&gt;item-&gt;util
)paren
)paren
suffix:semicolon
)brace
DECL|function|weight_set
r_static
r_inline
r_void
id|weight_set
c_func
(paren
r_struct
id|commit_list
op_star
id|elem
comma
r_int
id|weight
)paren
(brace
op_star
(paren
(paren
r_int
op_star
)paren
(paren
id|elem-&gt;item-&gt;util
)paren
)paren
op_assign
id|weight
suffix:semicolon
)brace
DECL|function|count_interesting_parents
r_static
r_int
id|count_interesting_parents
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
id|p
suffix:semicolon
r_int
id|count
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
comma
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|halfway
r_static
r_inline
r_int
id|halfway
c_func
(paren
r_struct
id|commit_list
op_star
id|p
comma
r_int
id|nr
)paren
(brace
multiline_comment|/*&n;&t; * Don&squot;t short-cut something we are not going to return!&n;&t; */
r_if
c_cond
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|TREESAME
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_BISECT
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * 2 and 3 are halfway of 5.&n;&t; * 3 is halfway of 6 but 2 and 4 are not.&n;&t; */
r_switch
c_cond
(paren
l_int|2
op_star
id|weight
c_func
(paren
id|p
)paren
id|nr
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#if !DEBUG_BISECT
DECL|macro|show_list
mdefine_line|#define show_list(a,b,c,d) do { ; } while (0)
macro_line|#else
DECL|function|show_list
r_static
r_void
id|show_list
c_func
(paren
r_const
r_char
op_star
id|debug
comma
r_int
id|counted
comma
r_int
id|nr
comma
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s (%d/%d)&bslash;n&quot;
comma
id|debug
comma
id|counted
comma
id|nr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|commit_list
op_star
id|pp
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|commit-&gt;object.sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_char
op_star
id|ep
comma
op_star
id|sp
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%c%c%c &quot;
comma
(paren
id|flags
op_amp
id|TREESAME
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;T&squot;
comma
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
ques
c_cond
l_char|&squot;U&squot;
suffix:colon
l_char|&squot; &squot;
comma
(paren
id|flags
op_amp
id|COUNTED
)paren
ques
c_cond
l_char|&squot;C&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;util
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%3d&quot;
comma
id|weight
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;---&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %.*s&quot;
comma
l_int|8
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
id|commit-&gt;parents
suffix:semicolon
id|pp
suffix:semicolon
id|pp
op_assign
id|pp-&gt;next
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %.*s&quot;
comma
l_int|8
comma
id|sha1_to_hex
c_func
(paren
id|pp-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|sp
op_assign
id|strstr
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp
)paren
(brace
id|sp
op_add_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|ep
op_assign
id|sp
suffix:semicolon
op_star
id|ep
op_logical_and
op_star
id|ep
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|ep
op_increment
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %.*s&quot;
comma
(paren
r_int
)paren
(paren
id|ep
id|sp
)paren
comma
id|sp
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* DEBUG_BISECT */
DECL|function|best_bisection
r_static
r_struct
id|commit_list
op_star
id|best_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
id|nr
)paren
(brace
r_struct
id|commit_list
op_star
id|p
comma
op_star
id|best
suffix:semicolon
r_int
id|best_distance
op_assign
l_int|1
suffix:semicolon
id|best
op_assign
id|list
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|distance
suffix:semicolon
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|TREESAME
)paren
r_continue
suffix:semicolon
id|distance
op_assign
id|weight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
id|distance
OL
id|distance
)paren
id|distance
op_assign
id|nr
id|distance
suffix:semicolon
r_if
c_cond
(paren
id|distance
OG
id|best_distance
)paren
(brace
id|best
op_assign
id|p
suffix:semicolon
id|best_distance
op_assign
id|distance
suffix:semicolon
)brace
)brace
r_return
id|best
suffix:semicolon
)brace
DECL|struct|commit_dist
r_struct
id|commit_dist
(brace
DECL|member|commit
r_struct
id|commit
op_star
id|commit
suffix:semicolon
DECL|member|distance
r_int
id|distance
suffix:semicolon
)brace
suffix:semicolon
DECL|function|compare_commit_dist
r_static
r_int
id|compare_commit_dist
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|commit_dist
op_star
id|a
comma
op_star
id|b
suffix:semicolon
id|a
op_assign
(paren
r_struct
id|commit_dist
op_star
)paren
id|a_
suffix:semicolon
id|b
op_assign
(paren
r_struct
id|commit_dist
op_star
)paren
id|b_
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;distance
op_ne
id|b-&gt;distance
)paren
r_return
id|b-&gt;distance
id|a-&gt;distance
suffix:semicolon
multiline_comment|/* desc sort */
r_return
id|hashcmp
c_func
(paren
id|a-&gt;commit-&gt;object.sha1
comma
id|b-&gt;commit-&gt;object.sha1
)paren
suffix:semicolon
)brace
DECL|function|best_bisection_sorted
r_static
r_struct
id|commit_list
op_star
id|best_bisection_sorted
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
id|nr
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_struct
id|commit_dist
op_star
id|array
op_assign
id|xcalloc
c_func
(paren
id|nr
comma
r_sizeof
(paren
op_star
id|array
)paren
)paren
suffix:semicolon
r_int
id|cnt
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
comma
id|cnt
op_assign
l_int|0
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|distance
suffix:semicolon
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|TREESAME
)paren
r_continue
suffix:semicolon
id|distance
op_assign
id|weight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
id|distance
OL
id|distance
)paren
id|distance
op_assign
id|nr
id|distance
suffix:semicolon
id|array
(braket
id|cnt
)braket
dot
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
id|array
(braket
id|cnt
)braket
dot
id|distance
op_assign
id|distance
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
id|qsort
c_func
(paren
id|array
comma
id|cnt
comma
r_sizeof
(paren
op_star
id|array
)paren
comma
id|compare_commit_dist
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|name_decoration
op_star
id|r
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|r
)paren
op_plus
l_int|100
)paren
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
op_amp
(paren
id|array
(braket
id|i
)braket
dot
id|commit-&gt;object
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|r-&gt;name
comma
l_string|&quot;dist=%d&quot;
comma
id|array
(braket
id|i
)braket
dot
id|distance
)paren
suffix:semicolon
id|r-&gt;next
op_assign
id|add_decoration
c_func
(paren
op_amp
id|name_decoration
comma
id|obj
comma
id|r
)paren
suffix:semicolon
id|p-&gt;item
op_assign
id|array
(braket
id|i
)braket
dot
id|commit
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
)paren
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|free
c_func
(paren
id|array
)paren
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
multiline_comment|/*&n; * zero or positive weight is the number of interesting commits it can&n; * reach, including itself.  Especially, weight = 0 means it does not&n; * reach any tree-changing commits (e.g. just above uninteresting one&n; * but traversal is with pathspec).&n; *&n; * weight = -1 means it has one parent and its distance is yet to&n; * be computed.&n; *&n; * weight = -2 means it has more than one parent and its distance is&n; * unknown.  After running count_distance() first, they will get zero&n; * or positive distance.&n; */
DECL|function|do_find_bisection
r_static
r_struct
id|commit_list
op_star
id|do_find_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
id|nr
comma
r_int
op_star
id|weights
comma
r_int
id|find_all
)paren
(brace
r_int
id|n
comma
id|counted
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
id|counted
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
suffix:semicolon
id|p-&gt;item-&gt;util
op_assign
op_amp
id|weights
(braket
id|n
op_increment
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|count_interesting_parents
c_func
(paren
id|commit
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TREESAME
)paren
)paren
(brace
id|weight_set
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
id|counted
op_increment
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 count one&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * otherwise, it is known not to reach any&n;&t;&t;&t; * tree-changing commit and gets weight 0.&n;&t;&t;&t; */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|weight_set
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|weight_set
c_func
(paren
id|p
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|show_list
c_func
(paren
l_string|&quot;bisection 2 initialize&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If you have only one parent in the resulting set&n;&t; * then you can reach one commit more than that parent&n;&t; * can reach.  So we do not have to run the expensive&n;&t; * count_distance() for single strand of pearls.&n;&t; *&n;&t; * However, if you have more than one parents, you cannot&n;&t; * just add their distance and one for yourself, since&n;&t; * they usually reach the same ancestor and you would&n;&t; * end up counting them twice that way.&n;&t; *&n;&t; * So we will first count distance of merges the usual&n;&t; * way, and then fill the blanks using cheaper algorithm.&n;&t; */
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|weight
c_func
(paren
id|p
)paren
op_ne
l_int|2
)paren
r_continue
suffix:semicolon
id|weight_set
c_func
(paren
id|p
comma
id|count_distance
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|clear_distance
c_func
(paren
id|list
)paren
suffix:semicolon
multiline_comment|/* Does it happen to be at exactly half-way? */
r_if
c_cond
(paren
op_logical_neg
id|find_all
op_logical_and
id|halfway
c_func
(paren
id|p
comma
id|nr
)paren
)paren
r_return
id|p
suffix:semicolon
id|counted
op_increment
suffix:semicolon
)brace
id|show_list
c_func
(paren
l_string|&quot;bisection 2 count_distance&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|counted
OL
id|nr
)paren
(brace
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|commit_list
op_star
id|q
suffix:semicolon
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|weight
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|p-&gt;item-&gt;parents
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|weight
c_func
(paren
id|q
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * weight for p is unknown but q is known.&n;&t;&t;&t; * add one for p itself if p is to be counted,&n;&t;&t;&t; * otherwise inherit it from q directly.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TREESAME
)paren
)paren
(brace
id|weight_set
c_func
(paren
id|p
comma
id|weight
c_func
(paren
id|q
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|counted
op_increment
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 count one&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
)brace
r_else
id|weight_set
c_func
(paren
id|p
comma
id|weight
c_func
(paren
id|q
)paren
)paren
suffix:semicolon
multiline_comment|/* Does it happen to be at exactly half-way? */
r_if
c_cond
(paren
op_logical_neg
id|find_all
op_logical_and
id|halfway
c_func
(paren
id|p
comma
id|nr
)paren
)paren
r_return
id|p
suffix:semicolon
)brace
)brace
id|show_list
c_func
(paren
l_string|&quot;bisection 2 counted all&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|find_all
)paren
r_return
id|best_bisection
c_func
(paren
id|list
comma
id|nr
)paren
suffix:semicolon
r_else
r_return
id|best_bisection_sorted
c_func
(paren
id|list
comma
id|nr
)paren
suffix:semicolon
)brace
DECL|function|find_bisection
r_struct
id|commit_list
op_star
id|find_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
op_star
id|reaches
comma
r_int
op_star
id|all
comma
r_int
id|find_all
)paren
(brace
r_int
id|nr
comma
id|on_list
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
comma
op_star
id|best
comma
op_star
id|next
comma
op_star
id|last
suffix:semicolon
r_int
op_star
id|weights
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 entry&quot;
comma
l_int|0
comma
l_int|0
comma
id|list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Count the number of total and tree-changing items on the&n;&t; * list, while reversing the list.&n;&t; */
r_for
c_loop
(paren
id|nr
op_assign
id|on_list
op_assign
l_int|0
comma
id|last
op_assign
l_int|NULL
comma
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|next
)paren
(brace
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
id|next
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
id|p-&gt;next
op_assign
id|last
suffix:semicolon
id|last
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TREESAME
)paren
)paren
id|nr
op_increment
suffix:semicolon
id|on_list
op_increment
suffix:semicolon
)brace
id|list
op_assign
id|last
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 sorted&quot;
comma
l_int|0
comma
id|nr
comma
id|list
)paren
suffix:semicolon
op_star
id|all
op_assign
id|nr
suffix:semicolon
id|weights
op_assign
id|xcalloc
c_func
(paren
id|on_list
comma
r_sizeof
(paren
op_star
id|weights
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the real work of finding bisection commit. */
id|best
op_assign
id|do_find_bisection
c_func
(paren
id|list
comma
id|nr
comma
id|weights
comma
id|find_all
)paren
suffix:semicolon
r_if
c_cond
(paren
id|best
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|find_all
)paren
id|best-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|reaches
op_assign
id|weight
c_func
(paren
id|best
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|weights
)paren
suffix:semicolon
r_return
id|best
suffix:semicolon
)brace
DECL|function|register_ref
r_static
r_int
id|register_ref
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|refname
comma
l_string|&quot;bad&quot;
)paren
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|rev_argv
comma
id|rev_argv_nr
op_plus
l_int|1
comma
id|rev_argv_alloc
)paren
suffix:semicolon
id|rev_argv
(braket
id|rev_argv_nr
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;good-&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_char
op_star
id|good
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|hex
)paren
op_plus
l_int|2
)paren
suffix:semicolon
op_star
id|good
op_assign
l_char|&squot;^&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|good
op_plus
l_int|1
comma
id|hex
comma
id|strlen
c_func
(paren
id|hex
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|rev_argv
comma
id|rev_argv_nr
op_plus
l_int|1
comma
id|rev_argv_alloc
)paren
suffix:semicolon
id|rev_argv
(braket
id|rev_argv_nr
op_increment
)braket
op_assign
id|good
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;skip-&quot;
)paren
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|skipped_sha1
comma
id|skipped_sha1_nr
op_plus
l_int|1
comma
id|skipped_sha1_alloc
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|skipped_sha1
(braket
id|skipped_sha1_nr
op_increment
)braket
comma
id|sha1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_bisect_refs
r_static
r_int
id|read_bisect_refs
c_func
(paren
r_void
)paren
(brace
r_return
id|for_each_ref_in
c_func
(paren
l_string|&quot;refs/bisect/&quot;
comma
id|register_ref
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|read_bisect_paths
r_void
id|read_bisect_paths
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|str
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|filename
op_assign
id|git_path
c_func
(paren
l_string|&quot;BISECT_NAMES&quot;
)paren
suffix:semicolon
id|FILE
op_star
id|fp
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
id|die
c_func
(paren
l_string|&quot;Could not open file &squot;%s&squot;: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|str
comma
id|fp
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
r_char
op_star
id|quoted
suffix:semicolon
r_int
id|res
suffix:semicolon
id|strbuf_trim
c_func
(paren
op_amp
id|str
)paren
suffix:semicolon
id|quoted
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|str
comma
l_int|NULL
)paren
suffix:semicolon
id|res
op_assign
id|sq_dequote_to_argv
c_func
(paren
id|quoted
comma
op_amp
id|rev_argv
comma
op_amp
id|rev_argv_nr
comma
op_amp
id|rev_argv_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|die
c_func
(paren
l_string|&quot;Badly quoted content in file &squot;%s&squot;: %s&quot;
comma
id|filename
comma
id|quoted
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|str
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
)brace
DECL|function|skipcmp
r_static
r_int
id|skipcmp
c_func
(paren
r_const
r_void
op_star
id|a
comma
r_const
r_void
op_star
id|b
)paren
(brace
r_return
id|hashcmp
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
)brace
DECL|function|prepare_skipped
r_static
r_void
id|prepare_skipped
c_func
(paren
r_void
)paren
(brace
id|qsort
c_func
(paren
id|skipped_sha1
comma
id|skipped_sha1_nr
comma
r_sizeof
(paren
op_star
id|skipped_sha1
)paren
comma
id|skipcmp
)paren
suffix:semicolon
)brace
DECL|function|skipped_sha1_access
r_static
r_const
r_int
r_char
op_star
id|skipped_sha1_access
c_func
(paren
r_int
id|index
comma
r_void
op_star
id|table
)paren
(brace
r_int
r_char
(paren
op_star
id|skipped
)paren
(braket
l_int|20
)braket
op_assign
id|table
suffix:semicolon
r_return
id|skipped
(braket
id|index
)braket
suffix:semicolon
)brace
DECL|function|lookup_skipped
r_static
r_int
id|lookup_skipped
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_return
id|sha1_pos
c_func
(paren
id|sha1
comma
id|skipped_sha1
comma
id|skipped_sha1_nr
comma
id|skipped_sha1_access
)paren
suffix:semicolon
)brace
DECL|function|filter_skipped
r_struct
id|commit_list
op_star
id|filter_skipped
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_struct
id|commit_list
op_star
op_star
id|tried
comma
r_int
id|show_all
)paren
(brace
r_struct
id|commit_list
op_star
id|filtered
op_assign
l_int|NULL
comma
op_star
op_star
id|f
op_assign
op_amp
id|filtered
suffix:semicolon
op_star
id|tried
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skipped_sha1_nr
)paren
r_return
id|list
suffix:semicolon
id|prepare_skipped
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|next
op_assign
id|list-&gt;next
suffix:semicolon
id|list-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|lookup_skipped
c_func
(paren
id|list-&gt;item-&gt;object.sha1
)paren
)paren
(brace
multiline_comment|/* Move current to tried list */
op_star
id|tried
op_assign
id|list
suffix:semicolon
id|tried
op_assign
op_amp
id|list-&gt;next
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|show_all
)paren
r_return
id|list
suffix:semicolon
multiline_comment|/* Move current to filtered list */
op_star
id|f
op_assign
id|list
suffix:semicolon
id|f
op_assign
op_amp
id|list-&gt;next
suffix:semicolon
)brace
id|list
op_assign
id|next
suffix:semicolon
)brace
r_return
id|filtered
suffix:semicolon
)brace
DECL|function|bisect_rev_setup
r_static
r_void
id|bisect_rev_setup
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
id|init_revisions
c_func
(paren
id|revs
comma
id|prefix
)paren
suffix:semicolon
id|revs-&gt;abbrev
op_assign
l_int|0
suffix:semicolon
id|revs-&gt;commit_format
op_assign
id|CMIT_FMT_UNSPECIFIED
suffix:semicolon
multiline_comment|/* argv[0] will be ignored by setup_revisions */
id|ALLOC_GROW
c_func
(paren
id|rev_argv
comma
id|rev_argv_nr
op_plus
l_int|1
comma
id|rev_argv_alloc
)paren
suffix:semicolon
id|rev_argv
(braket
id|rev_argv_nr
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;bisect_rev_setup&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_bisect_refs
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;reading bisect refs failed&quot;
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|rev_argv
comma
id|rev_argv_nr
op_plus
l_int|1
comma
id|rev_argv_alloc
)paren
suffix:semicolon
id|rev_argv
(braket
id|rev_argv_nr
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;--&quot;
)paren
suffix:semicolon
id|read_bisect_paths
c_func
(paren
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|rev_argv
comma
id|rev_argv_nr
op_plus
l_int|1
comma
id|rev_argv_alloc
)paren
suffix:semicolon
id|rev_argv
(braket
id|rev_argv_nr
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|setup_revisions
c_func
(paren
id|rev_argv_nr
comma
id|rev_argv
comma
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|revs-&gt;limited
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|bisect_next_vars
r_int
id|bisect_next_vars
c_func
(paren
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|rev_info
id|revs
suffix:semicolon
r_int
id|reaches
op_assign
l_int|0
comma
id|all
op_assign
l_int|0
suffix:semicolon
id|bisect_rev_setup
c_func
(paren
op_amp
id|revs
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.tree_objects
)paren
id|mark_edges_uninteresting
c_func
(paren
id|revs.commits
comma
op_amp
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|revs.commits
op_assign
id|find_bisection
c_func
(paren
id|revs.commits
comma
op_amp
id|reaches
comma
op_amp
id|all
comma
op_logical_neg
op_logical_neg
id|skipped_sha1_nr
)paren
suffix:semicolon
r_return
id|show_bisect_vars
c_func
(paren
op_amp
id|revs
comma
id|reaches
comma
id|all
comma
id|BISECT_SHOW_TRIED
op_or
id|BISECT_SHOW_STRINGED
)paren
suffix:semicolon
)brace
eof
