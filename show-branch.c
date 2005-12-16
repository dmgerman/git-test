macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;fnmatch.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|show_branch_usage
r_static
r_const
r_char
id|show_branch_usage
(braket
)braket
op_assign
l_string|&quot;git-show-branch [--all] [--heads] [--tags] [--topo-order] [--more=count | --list | --independent | --merge-base ] [&lt;refs&gt;...]&quot;
suffix:semicolon
DECL|macro|UNINTERESTING
mdefine_line|#define UNINTERESTING&t;01
DECL|macro|REV_SHIFT
mdefine_line|#define REV_SHIFT&t; 2
DECL|macro|MAX_REVS
mdefine_line|#define MAX_REVS&t;29 /* should not exceed bits_per_int - REV_SHIFT */
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
DECL|function|pop_one_commit
r_static
r_struct
id|commit
op_star
id|pop_one_commit
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list_p
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|list
suffix:semicolon
id|list
op_assign
op_star
id|list_p
suffix:semicolon
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
op_star
id|list_p
op_assign
id|list-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
id|commit
suffix:semicolon
)brace
DECL|struct|commit_name
r_struct
id|commit_name
(brace
DECL|member|head_name
r_const
r_char
op_star
id|head_name
suffix:semicolon
multiline_comment|/* which head&squot;s ancestor? */
DECL|member|generation
r_int
id|generation
suffix:semicolon
multiline_comment|/* how many parents away from head_name */
)brace
suffix:semicolon
multiline_comment|/* Name the commit as nth generation ancestor of head_name;&n; * we count only the first-parent relationship for naming purposes.&n; */
DECL|function|name_commit
r_static
r_void
id|name_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
id|head_name
comma
r_int
id|nth
)paren
(brace
r_struct
id|commit_name
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;object.util
)paren
id|commit-&gt;object.util
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_name
)paren
)paren
suffix:semicolon
id|name
op_assign
id|commit-&gt;object.util
suffix:semicolon
id|name-&gt;head_name
op_assign
id|head_name
suffix:semicolon
id|name-&gt;generation
op_assign
id|nth
suffix:semicolon
)brace
multiline_comment|/* Parent is the first parent of the commit.  We may name it&n; * as (n+1)th generation ancestor of the same head_name as&n; * commit is nth generation ancestor of, if that generation&n; * number is better than the name it already has.&n; */
DECL|function|name_parent
r_static
r_void
id|name_parent
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit
op_star
id|parent
)paren
(brace
r_struct
id|commit_name
op_star
id|commit_name
op_assign
id|commit-&gt;object.util
suffix:semicolon
r_struct
id|commit_name
op_star
id|parent_name
op_assign
id|parent-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit_name
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_name
op_logical_or
id|commit_name-&gt;generation
op_plus
l_int|1
OL
id|parent_name-&gt;generation
)paren
id|name_commit
c_func
(paren
id|parent
comma
id|commit_name-&gt;head_name
comma
id|commit_name-&gt;generation
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|name_first_parent_chain
r_static
r_int
id|name_first_parent_chain
c_func
(paren
r_struct
id|commit
op_star
id|c
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|c
)paren
(brace
r_struct
id|commit
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;object.util
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;parents
)paren
r_break
suffix:semicolon
id|p
op_assign
id|c-&gt;parents-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;object.util
)paren
(brace
id|name_parent
c_func
(paren
id|c
comma
id|p
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|c
op_assign
id|p
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|name_commits
r_static
r_void
id|name_commits
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_struct
id|commit
op_star
op_star
id|rev
comma
r_char
op_star
op_star
id|ref_name
comma
r_int
id|num_rev
)paren
(brace
r_struct
id|commit_list
op_star
id|cl
suffix:semicolon
r_struct
id|commit
op_star
id|c
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* First give names to the given heads */
r_for
c_loop
(paren
id|cl
op_assign
id|list
suffix:semicolon
id|cl
suffix:semicolon
id|cl
op_assign
id|cl-&gt;next
)paren
(brace
id|c
op_assign
id|cl-&gt;item
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;object.util
)paren
r_continue
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
id|num_rev
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rev
(braket
id|i
)braket
op_eq
id|c
)paren
(brace
id|name_commit
c_func
(paren
id|c
comma
id|ref_name
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Then commits on the first parent ancestry chain */
r_do
(brace
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cl
op_assign
id|list
suffix:semicolon
id|cl
suffix:semicolon
id|cl
op_assign
id|cl-&gt;next
)paren
(brace
id|i
op_add_assign
id|name_first_parent_chain
c_func
(paren
id|cl-&gt;item
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/* Finally, any unnamed commits */
r_do
(brace
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cl
op_assign
id|list
suffix:semicolon
id|cl
suffix:semicolon
id|cl
op_assign
id|cl-&gt;next
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_struct
id|commit_name
op_star
id|n
suffix:semicolon
r_int
id|nth
suffix:semicolon
id|c
op_assign
id|cl-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;object.util
)paren
r_continue
suffix:semicolon
id|n
op_assign
id|c-&gt;object.util
suffix:semicolon
id|parents
op_assign
id|c-&gt;parents
suffix:semicolon
id|nth
op_assign
l_int|0
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
r_char
id|newname
(braket
l_int|1000
)braket
comma
op_star
id|en
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
id|nth
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;object.util
)paren
r_continue
suffix:semicolon
id|en
op_assign
id|newname
suffix:semicolon
r_switch
c_cond
(paren
id|n-&gt;generation
)paren
(brace
r_case
l_int|0
suffix:colon
id|en
op_add_assign
id|sprintf
c_func
(paren
id|en
comma
l_string|&quot;%s&quot;
comma
id|n-&gt;head_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|en
op_add_assign
id|sprintf
c_func
(paren
id|en
comma
l_string|&quot;%s^&quot;
comma
id|n-&gt;head_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|en
op_add_assign
id|sprintf
c_func
(paren
id|en
comma
l_string|&quot;%s~%d&quot;
comma
id|n-&gt;head_name
comma
id|n-&gt;generation
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nth
op_eq
l_int|1
)paren
id|en
op_add_assign
id|sprintf
c_func
(paren
id|en
comma
l_string|&quot;^&quot;
)paren
suffix:semicolon
r_else
id|en
op_add_assign
id|sprintf
c_func
(paren
id|en
comma
l_string|&quot;^%d&quot;
comma
id|nth
)paren
suffix:semicolon
id|name_commit
c_func
(paren
id|p
comma
id|strdup
c_func
(paren
id|newname
)paren
comma
l_int|0
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|name_first_parent_chain
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|function|mark_seen
r_static
r_int
id|mark_seen
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit_list
op_star
op_star
id|seen_p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;object.flags
)paren
(brace
id|insert_by_date
c_func
(paren
id|commit
comma
id|seen_p
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|join_revs
r_static
r_void
id|join_revs
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list_p
comma
r_struct
id|commit_list
op_star
op_star
id|seen_p
comma
r_int
id|num_rev
comma
r_int
id|extra
)paren
(brace
r_int
id|all_mask
op_assign
(paren
(paren
l_int|1u
op_lshift
(paren
id|REV_SHIFT
op_plus
id|num_rev
)paren
)paren
l_int|1
)paren
suffix:semicolon
r_int
id|all_revs
op_assign
id|all_mask
op_amp
op_complement
(paren
(paren
l_int|1u
op_lshift
id|REV_SHIFT
)paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|list_p
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
id|still_interesting
op_assign
op_logical_neg
op_logical_neg
id|interesting
c_func
(paren
op_star
id|list_p
)paren
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|pop_one_commit
c_func
(paren
id|list_p
)paren
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
op_amp
id|all_mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|still_interesting
op_logical_and
id|extra
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|mark_seen
c_func
(paren
id|commit
comma
id|seen_p
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|all_revs
)paren
op_eq
id|all_revs
)paren
id|flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
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
r_int
id|this_flag
op_assign
id|p-&gt;object.flags
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|this_flag
op_amp
id|flags
)paren
op_eq
id|flags
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;object.parsed
)paren
id|parse_commit
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mark_seen
c_func
(paren
id|p
comma
id|seen_p
)paren
op_logical_and
op_logical_neg
id|still_interesting
)paren
id|extra
op_decrement
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
id|list_p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Postprocess to complete well-poisoning.&n;&t; *&n;&t; * At this point we have all the commits we have seen in&n;&t; * seen_p list (which happens to be sorted chronologically but&n;&t; * it does not really matter).  Mark anything that can be&n;&t; * reached from uninteresting commits not interesting.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|s
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
op_star
id|seen_p
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|s-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|c
op_assign
id|s-&gt;item
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|c-&gt;object.flags
op_amp
id|all_revs
)paren
op_ne
id|all_revs
)paren
op_logical_and
op_logical_neg
(paren
id|c-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* The current commit is either a merge base or&n;&t;&t;&t; * already uninteresting one.  Mark its parents&n;&t;&t;&t; * as uninteresting commits _only_ if they are&n;&t;&t;&t; * already parsed.  No reason to find new ones&n;&t;&t;&t; * here.&n;&t;&t;&t; */
id|parents
op_assign
id|c-&gt;parents
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
op_logical_neg
(paren
id|p-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
)paren
(brace
id|p-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
id|changed
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
r_break
suffix:semicolon
)brace
)brace
DECL|function|show_one_commit
r_static
r_void
id|show_one_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
id|no_name
)paren
(brace
r_char
id|pretty
(braket
l_int|256
)braket
comma
op_star
id|cp
suffix:semicolon
r_struct
id|commit_name
op_star
id|name
op_assign
id|commit-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.parsed
)paren
id|pretty_print_commit
c_func
(paren
id|CMIT_FMT_ONELINE
comma
id|commit-&gt;buffer
comma
op_complement
l_int|0
comma
id|pretty
comma
r_sizeof
(paren
id|pretty
)paren
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|pretty
comma
l_string|&quot;(unavailable)&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|pretty
comma
l_string|&quot;[PATCH] &quot;
comma
l_int|8
)paren
)paren
id|cp
op_assign
id|pretty
op_plus
l_int|8
suffix:semicolon
r_else
id|cp
op_assign
id|pretty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_name
)paren
(brace
r_if
c_cond
(paren
id|name
op_logical_and
id|name-&gt;head_name
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;[%s&quot;
comma
id|name-&gt;head_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name-&gt;generation
)paren
(brace
r_if
c_cond
(paren
id|name-&gt;generation
op_eq
l_int|1
)paren
id|printf
c_func
(paren
l_string|&quot;^&quot;
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;~%d&quot;
comma
id|name-&gt;generation
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;] &quot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;[%s] &quot;
comma
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
l_int|7
)paren
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
id|cp
)paren
suffix:semicolon
)brace
DECL|variable|ref_name
r_static
r_char
op_star
id|ref_name
(braket
id|MAX_REVS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|ref_name_cnt
r_static
r_int
id|ref_name_cnt
suffix:semicolon
DECL|function|compare_ref_name
r_static
r_int
id|compare_ref_name
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
r_const
r_char
op_star
r_const
op_star
id|a
op_assign
id|a_
comma
op_star
r_const
op_star
id|b
op_assign
id|b_
suffix:semicolon
r_return
id|strcmp
c_func
(paren
op_star
id|a
comma
op_star
id|b
)paren
suffix:semicolon
)brace
DECL|function|sort_ref_range
r_static
r_void
id|sort_ref_range
c_func
(paren
r_int
id|bottom
comma
r_int
id|top
)paren
(brace
id|qsort
c_func
(paren
id|ref_name
op_plus
id|bottom
comma
id|top
id|bottom
comma
r_sizeof
(paren
id|ref_name
(braket
l_int|0
)braket
)paren
comma
id|compare_ref_name
)paren
suffix:semicolon
)brace
DECL|function|append_ref
r_static
r_int
id|append_ref
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
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|MAX_REVS
op_le
id|ref_name_cnt
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: ignoring %s; &quot;
l_string|&quot;cannot handle more than %d refs&quot;
comma
id|refname
comma
id|MAX_REVS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ref_name
(braket
id|ref_name_cnt
op_increment
)braket
op_assign
id|strdup
c_func
(paren
id|refname
)paren
suffix:semicolon
id|ref_name
(braket
id|ref_name_cnt
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|append_head_ref
r_static
r_int
id|append_head_ref
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
)paren
(brace
r_int
r_char
id|tmp
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|ofs
op_assign
l_int|11
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads/&quot;
comma
id|ofs
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* If both heads/foo and tags/foo exists, get_sha1 would&n;&t; * get confused.&n;&t; */
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|refname
op_plus
id|ofs
comma
id|tmp
)paren
op_logical_or
id|memcmp
c_func
(paren
id|tmp
comma
id|sha1
comma
l_int|20
)paren
)paren
id|ofs
op_assign
l_int|5
suffix:semicolon
r_return
id|append_ref
c_func
(paren
id|refname
op_plus
id|ofs
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|append_tag_ref
r_static
r_int
id|append_tag_ref
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
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|append_ref
c_func
(paren
id|refname
op_plus
l_int|5
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|variable|match_ref_pattern
r_static
r_const
r_char
op_star
id|match_ref_pattern
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|match_ref_slash
r_static
r_int
id|match_ref_slash
op_assign
l_int|0
suffix:semicolon
DECL|function|count_slash
r_static
r_int
id|count_slash
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|s
)paren
r_if
c_cond
(paren
op_star
id|s
op_increment
op_eq
l_char|&squot;/&squot;
)paren
id|cnt
op_increment
suffix:semicolon
r_return
id|cnt
suffix:semicolon
)brace
DECL|function|append_matching_ref
r_static
r_int
id|append_matching_ref
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
)paren
(brace
multiline_comment|/* we want to allow pattern hold/&lt;asterisk&gt; to show all&n;&t; * branches under refs/heads/hold/, and v0.99.9? to show&n;&t; * refs/tags/v0.99.9a and friends.&n;&t; */
r_const
r_char
op_star
id|tail
suffix:semicolon
r_int
id|slash
op_assign
id|count_slash
c_func
(paren
id|refname
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tail
op_assign
id|refname
suffix:semicolon
op_star
id|tail
op_logical_and
id|match_ref_slash
OL
id|slash
suffix:semicolon
)paren
r_if
c_cond
(paren
op_star
id|tail
op_increment
op_eq
l_char|&squot;/&squot;
)paren
id|slash
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|tail
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fnmatch
c_func
(paren
id|match_ref_pattern
comma
id|tail
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;refs/heads/&quot;
comma
id|refname
comma
l_int|11
)paren
)paren
r_return
id|append_head_ref
c_func
(paren
id|refname
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;refs/tags/&quot;
comma
id|refname
comma
l_int|10
)paren
)paren
r_return
id|append_tag_ref
c_func
(paren
id|refname
comma
id|sha1
)paren
suffix:semicolon
r_return
id|append_ref
c_func
(paren
id|refname
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|snarf_refs
r_static
r_void
id|snarf_refs
c_func
(paren
r_int
id|head
comma
r_int
id|tag
)paren
(brace
r_if
c_cond
(paren
id|head
)paren
(brace
r_int
id|orig_cnt
op_assign
id|ref_name_cnt
suffix:semicolon
id|for_each_ref
c_func
(paren
id|append_head_ref
)paren
suffix:semicolon
id|sort_ref_range
c_func
(paren
id|orig_cnt
comma
id|ref_name_cnt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tag
)paren
(brace
r_int
id|orig_cnt
op_assign
id|ref_name_cnt
suffix:semicolon
id|for_each_ref
c_func
(paren
id|append_tag_ref
)paren
suffix:semicolon
id|sort_ref_range
c_func
(paren
id|orig_cnt
comma
id|ref_name_cnt
)paren
suffix:semicolon
)brace
)brace
DECL|function|rev_is_head
r_static
r_int
id|rev_is_head
c_func
(paren
r_char
op_star
id|head_path
comma
r_int
id|headlen
comma
r_char
op_star
id|name
comma
r_int
r_char
op_star
id|head_sha1
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|namelen
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|head_path
(braket
l_int|0
)braket
)paren
op_logical_or
id|memcmp
c_func
(paren
id|head_sha1
comma
id|sha1
comma
l_int|20
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|headlen
OL
id|namelen
)paren
op_logical_or
id|memcmp
c_func
(paren
id|head_path
op_plus
id|headlen
id|namelen
comma
id|name
comma
id|namelen
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|headlen
op_eq
id|namelen
op_logical_or
id|head_path
(braket
id|headlen
id|namelen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_merge_base
r_static
r_int
id|show_merge_base
c_func
(paren
r_struct
id|commit_list
op_star
id|seen
comma
r_int
id|num_rev
)paren
(brace
r_int
id|all_mask
op_assign
(paren
(paren
l_int|1u
op_lshift
(paren
id|REV_SHIFT
op_plus
id|num_rev
)paren
)paren
l_int|1
)paren
suffix:semicolon
r_int
id|all_revs
op_assign
id|all_mask
op_amp
op_complement
(paren
(paren
l_int|1u
op_lshift
id|REV_SHIFT
)paren
l_int|1
)paren
suffix:semicolon
r_int
id|exit_status
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|seen
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|pop_one_commit
c_func
(paren
op_amp
id|seen
)paren
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
op_amp
id|all_mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
op_logical_and
(paren
(paren
id|flags
op_amp
id|all_revs
)paren
op_eq
id|all_revs
)paren
)paren
(brace
id|puts
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|exit_status
op_assign
l_int|0
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
)brace
)brace
r_return
id|exit_status
suffix:semicolon
)brace
DECL|function|show_independent
r_static
r_int
id|show_independent
c_func
(paren
r_struct
id|commit
op_star
op_star
id|rev
comma
r_int
id|num_rev
comma
r_char
op_star
op_star
id|ref_name
comma
r_int
r_int
op_star
id|rev_mask
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
id|num_rev
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|rev
(braket
id|i
)braket
suffix:semicolon
r_int
r_int
id|flag
op_assign
id|rev_mask
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_eq
id|flag
)paren
id|puts
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
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
DECL|function|append_one_rev
r_static
r_void
id|append_one_rev
c_func
(paren
r_const
r_char
op_star
id|av
)paren
(brace
r_int
r_char
id|revkey
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
id|av
comma
id|revkey
)paren
)paren
(brace
id|append_ref
c_func
(paren
id|av
comma
id|revkey
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|av
comma
l_char|&squot;*&squot;
)paren
op_logical_or
id|strchr
c_func
(paren
id|av
comma
l_char|&squot;?&squot;
)paren
)paren
(brace
multiline_comment|/* glob style match */
r_int
id|saved_matches
op_assign
id|ref_name_cnt
suffix:semicolon
id|match_ref_pattern
op_assign
id|av
suffix:semicolon
id|match_ref_slash
op_assign
id|count_slash
c_func
(paren
id|av
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|append_matching_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_matches
op_eq
id|ref_name_cnt
op_logical_and
id|ref_name_cnt
OL
id|MAX_REVS
)paren
id|error
c_func
(paren
l_string|&quot;no matching refs with %s&quot;
comma
id|av
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_matches
op_plus
l_int|1
OL
id|ref_name_cnt
)paren
id|sort_ref_range
c_func
(paren
id|saved_matches
comma
id|ref_name_cnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;bad sha1 reference %s&quot;
comma
id|av
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_char
op_star
op_star
id|av
)paren
(brace
r_struct
id|commit
op_star
id|rev
(braket
id|MAX_REVS
)braket
comma
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|list
op_assign
l_int|NULL
comma
op_star
id|seen
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|rev_mask
(braket
id|MAX_REVS
)braket
suffix:semicolon
r_int
id|num_rev
comma
id|i
comma
id|extra
op_assign
l_int|0
suffix:semicolon
r_int
id|all_heads
op_assign
l_int|0
comma
id|all_tags
op_assign
l_int|0
suffix:semicolon
r_int
id|all_mask
comma
id|all_revs
suffix:semicolon
r_char
id|head_path
(braket
l_int|128
)braket
suffix:semicolon
r_const
r_char
op_star
id|head_path_p
suffix:semicolon
r_int
id|head_path_len
suffix:semicolon
r_int
r_char
id|head_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|merge_base
op_assign
l_int|0
suffix:semicolon
r_int
id|independent
op_assign
l_int|0
suffix:semicolon
r_int
id|no_name
op_assign
l_int|0
suffix:semicolon
r_int
id|sha1_name
op_assign
l_int|0
suffix:semicolon
r_int
id|shown_merge_point
op_assign
l_int|0
suffix:semicolon
r_int
id|topo_order
op_assign
l_int|0
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|ac
op_logical_and
id|av
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
id|av
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
l_string|&quot;--all&quot;
)paren
)paren
id|all_heads
op_assign
id|all_tags
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
id|arg
comma
l_string|&quot;--heads&quot;
)paren
)paren
id|all_heads
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
id|arg
comma
l_string|&quot;--tags&quot;
)paren
)paren
id|all_tags
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
id|arg
comma
l_string|&quot;--more&quot;
)paren
)paren
id|extra
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
id|arg
comma
l_string|&quot;--list&quot;
)paren
)paren
id|extra
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
id|arg
comma
l_string|&quot;--no-name&quot;
)paren
)paren
id|no_name
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
id|arg
comma
l_string|&quot;--sha1-name&quot;
)paren
)paren
id|sha1_name
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--more=&quot;
comma
l_int|7
)paren
)paren
id|extra
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|7
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--merge-base&quot;
)paren
)paren
id|merge_base
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
id|arg
comma
l_string|&quot;--independent&quot;
)paren
)paren
id|independent
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
id|arg
comma
l_string|&quot;--topo-order&quot;
)paren
)paren
id|topo_order
op_assign
l_int|1
suffix:semicolon
r_else
id|usage
c_func
(paren
id|show_branch_usage
)paren
suffix:semicolon
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
)brace
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
multiline_comment|/* Only one of these is allowed */
r_if
c_cond
(paren
l_int|1
OL
id|independent
op_plus
id|merge_base
op_plus
(paren
id|extra
op_ne
l_int|0
)paren
)paren
id|usage
c_func
(paren
id|show_branch_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|all_heads
op_plus
id|all_tags
)paren
id|snarf_refs
c_func
(paren
id|all_heads
comma
id|all_tags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac
)paren
(brace
r_while
c_loop
(paren
l_int|0
OL
id|ac
)paren
(brace
id|append_one_rev
c_func
(paren
op_star
id|av
)paren
suffix:semicolon
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* If no revs given, then add heads */
id|snarf_refs
c_func
(paren
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ref_name_cnt
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No revs to be shown.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|num_rev
op_assign
l_int|0
suffix:semicolon
id|ref_name
(braket
id|num_rev
)braket
suffix:semicolon
id|num_rev
op_increment
)paren
(brace
r_int
r_char
id|revkey
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|flag
op_assign
l_int|1u
op_lshift
(paren
id|num_rev
op_plus
id|REV_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAX_REVS
op_le
id|num_rev
)paren
id|die
c_func
(paren
l_string|&quot;cannot handle more than %d revs.&quot;
comma
id|MAX_REVS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|ref_name
(braket
id|num_rev
)braket
comma
id|revkey
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid ref.&bslash;n&quot;
comma
id|ref_name
(braket
id|num_rev
)braket
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|revkey
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
l_string|&quot;cannot find commit %s (%s)&quot;
comma
id|ref_name
(braket
id|num_rev
)braket
comma
id|revkey
)paren
suffix:semicolon
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
id|mark_seen
c_func
(paren
id|commit
comma
op_amp
id|seen
)paren
suffix:semicolon
multiline_comment|/* rev#0 uses bit REV_SHIFT, rev#1 uses bit REV_SHIFT+1,&n;&t;&t; * and so on.  REV_SHIFT bits from bit 0 are used for&n;&t;&t; * internal bookkeeping.&n;&t;&t; */
id|commit-&gt;object.flags
op_or_assign
id|flag
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_eq
id|flag
)paren
id|insert_by_date
c_func
(paren
id|commit
comma
op_amp
id|list
)paren
suffix:semicolon
id|rev
(braket
id|num_rev
)braket
op_assign
id|commit
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_rev
suffix:semicolon
id|i
op_increment
)paren
id|rev_mask
(braket
id|i
)braket
op_assign
id|rev
(braket
id|i
)braket
op_member_access_from_pointer
id|object.flags
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|extra
)paren
id|join_revs
c_func
(paren
op_amp
id|list
comma
op_amp
id|seen
comma
id|num_rev
comma
id|extra
)paren
suffix:semicolon
id|head_path_p
op_assign
id|resolve_ref
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
comma
id|head_sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head_path_p
)paren
(brace
id|head_path_len
op_assign
id|strlen
c_func
(paren
id|head_path_p
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|head_path
comma
id|head_path_p
comma
id|head_path_len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|head_path_len
op_assign
l_int|0
suffix:semicolon
id|head_path
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|merge_base
)paren
r_return
id|show_merge_base
c_func
(paren
id|seen
comma
id|num_rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|independent
)paren
r_return
id|show_independent
c_func
(paren
id|rev
comma
id|num_rev
comma
id|ref_name
comma
id|rev_mask
)paren
suffix:semicolon
multiline_comment|/* Show list; --more=-1 means list-only */
r_if
c_cond
(paren
l_int|1
OL
id|num_rev
op_logical_or
id|extra
OL
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_rev
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|j
suffix:semicolon
r_int
id|is_head
op_assign
id|rev_is_head
c_func
(paren
id|head_path
comma
id|head_path_len
comma
id|ref_name
(braket
id|i
)braket
comma
id|head_sha1
comma
id|rev
(braket
id|i
)braket
op_member_access_from_pointer
id|object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extra
OL
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;%c [%s] &quot;
comma
id|is_head
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|ref_name
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%c [%s] &quot;
comma
id|is_head
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot;!&squot;
comma
id|ref_name
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* header lines never need name */
id|show_one_commit
c_func
(paren
id|rev
(braket
id|i
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|extra
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_rev
suffix:semicolon
id|i
op_increment
)paren
id|putchar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|extra
OL
l_int|0
)paren
m_exit
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Sort topologically */
r_if
c_cond
(paren
id|topo_order
)paren
id|sort_in_topological_order
c_func
(paren
op_amp
id|seen
)paren
suffix:semicolon
multiline_comment|/* Give names to commits */
r_if
c_cond
(paren
op_logical_neg
id|sha1_name
op_logical_and
op_logical_neg
id|no_name
)paren
id|name_commits
c_func
(paren
id|seen
comma
id|rev
comma
id|ref_name
comma
id|num_rev
)paren
suffix:semicolon
id|all_mask
op_assign
(paren
(paren
l_int|1u
op_lshift
(paren
id|REV_SHIFT
op_plus
id|num_rev
)paren
)paren
l_int|1
)paren
suffix:semicolon
id|all_revs
op_assign
id|all_mask
op_amp
op_complement
(paren
(paren
l_int|1u
op_lshift
id|REV_SHIFT
)paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|seen
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|pop_one_commit
c_func
(paren
op_amp
id|seen
)paren
suffix:semicolon
r_int
id|this_flag
op_assign
id|commit-&gt;object.flags
suffix:semicolon
id|shown_merge_point
op_or_assign
(paren
(paren
id|this_flag
op_amp
id|all_revs
)paren
op_eq
id|all_revs
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|num_rev
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_rev
suffix:semicolon
id|i
op_increment
)paren
id|putchar
c_func
(paren
(paren
id|this_flag
op_amp
(paren
l_int|1u
op_lshift
(paren
id|i
op_plus
id|REV_SHIFT
)paren
)paren
)paren
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|show_one_commit
c_func
(paren
id|commit
comma
id|no_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shown_merge_point
op_logical_and
op_decrement
id|extra
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
