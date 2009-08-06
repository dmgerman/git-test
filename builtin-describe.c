macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|macro|SEEN
mdefine_line|#define SEEN&t;&t;(1u&lt;&lt;0)
DECL|macro|MAX_TAGS
mdefine_line|#define MAX_TAGS&t;(FLAG_BITS - 1)
DECL|variable|describe_usage
r_static
r_const
r_char
op_star
r_const
id|describe_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git describe [options] &lt;committish&gt;*&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
multiline_comment|/* Display lots of verbose info */
DECL|variable|all
r_static
r_int
id|all
suffix:semicolon
multiline_comment|/* Any valid ref can be used */
DECL|variable|tags
r_static
r_int
id|tags
suffix:semicolon
multiline_comment|/* Allow lightweight tags */
DECL|variable|longformat
r_static
r_int
id|longformat
suffix:semicolon
DECL|variable|abbrev
r_static
r_int
id|abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
DECL|variable|max_candidates
r_static
r_int
id|max_candidates
op_assign
l_int|10
suffix:semicolon
DECL|variable|found_names
r_static
r_int
id|found_names
suffix:semicolon
DECL|variable|pattern
r_static
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|variable|always
r_static
r_int
id|always
suffix:semicolon
DECL|struct|commit_name
r_struct
id|commit_name
(brace
DECL|member|tag
r_struct
id|tag
op_star
id|tag
suffix:semicolon
DECL|member|prio
r_int
id|prio
suffix:semicolon
multiline_comment|/* annotated tag = 2, tag = 1, head = 0 */
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|path
r_char
id|path
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
multiline_comment|/* more */
)brace
suffix:semicolon
DECL|variable|prio_names
r_static
r_const
r_char
op_star
id|prio_names
(braket
)braket
op_assign
(brace
l_string|&quot;head&quot;
comma
l_string|&quot;lightweight&quot;
comma
l_string|&quot;annotated&quot;
comma
)brace
suffix:semicolon
DECL|function|add_to_known_names
r_static
r_void
id|add_to_known_names
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|commit
op_star
id|commit
comma
r_int
id|prio
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit_name
op_star
id|e
op_assign
id|commit-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
op_logical_or
id|e-&gt;prio
OL
id|prio
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|e
)paren
suffix:semicolon
id|e
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_name
)paren
op_plus
id|len
)paren
suffix:semicolon
id|e-&gt;tag
op_assign
l_int|NULL
suffix:semicolon
id|e-&gt;prio
op_assign
id|prio
suffix:semicolon
id|hashcpy
c_func
(paren
id|e-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|e-&gt;path
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|commit-&gt;util
op_assign
id|e
suffix:semicolon
)brace
id|found_names
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|get_name
r_static
r_int
id|get_name
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
r_int
id|might_be_tag
op_assign
op_logical_neg
id|prefixcmp
c_func
(paren
id|path
comma
l_string|&quot;refs/tags/&quot;
)paren
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|object
op_star
id|object
suffix:semicolon
r_int
r_char
id|peeled
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|is_tag
comma
id|prio
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all
op_logical_and
op_logical_neg
id|might_be_tag
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|peel_ref
c_func
(paren
id|path
comma
id|peeled
)paren
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|peeled
)paren
)paren
(brace
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|peeled
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
id|is_tag
op_assign
op_logical_neg
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|commit-&gt;object.sha1
)paren
suffix:semicolon
)brace
r_else
(brace
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
id|object
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
id|commit
op_logical_or
op_logical_neg
id|object
)paren
r_return
l_int|0
suffix:semicolon
id|is_tag
op_assign
id|object-&gt;type
op_eq
id|OBJ_TAG
suffix:semicolon
)brace
multiline_comment|/* If --all, then any refs are used.&n;&t; * If --tags, then any tags are used.&n;&t; * Otherwise only annotated tags are used.&n;&t; */
r_if
c_cond
(paren
id|might_be_tag
)paren
(brace
r_if
c_cond
(paren
id|is_tag
)paren
id|prio
op_assign
l_int|2
suffix:semicolon
r_else
id|prio
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pattern
op_logical_and
id|fnmatch
c_func
(paren
id|pattern
comma
id|path
op_plus
l_int|10
comma
l_int|0
)paren
)paren
id|prio
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|prio
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prio
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tags
op_logical_and
id|prio
OL
l_int|2
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|add_to_known_names
c_func
(paren
id|all
ques
c_cond
id|path
op_plus
l_int|5
suffix:colon
id|path
op_plus
l_int|10
comma
id|commit
comma
id|prio
comma
id|sha1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|possible_tag
r_struct
id|possible_tag
(brace
DECL|member|name
r_struct
id|commit_name
op_star
id|name
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|found_order
r_int
id|found_order
suffix:semicolon
DECL|member|flag_within
r_int
id|flag_within
suffix:semicolon
)brace
suffix:semicolon
DECL|function|compare_pt
r_static
r_int
id|compare_pt
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
id|possible_tag
op_star
id|a
op_assign
(paren
r_struct
id|possible_tag
op_star
)paren
id|a_
suffix:semicolon
r_struct
id|possible_tag
op_star
id|b
op_assign
(paren
r_struct
id|possible_tag
op_star
)paren
id|b_
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;depth
op_ne
id|b-&gt;depth
)paren
r_return
id|a-&gt;depth
id|b-&gt;depth
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;found_order
op_ne
id|b-&gt;found_order
)paren
r_return
id|a-&gt;found_order
id|b-&gt;found_order
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|finish_depth_computation
r_static
r_int
r_int
id|finish_depth_computation
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
comma
r_struct
id|possible_tag
op_star
id|best
)paren
(brace
r_int
r_int
id|seen_commits
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|list
)paren
(brace
r_struct
id|commit
op_star
id|c
op_assign
id|pop_commit
c_func
(paren
id|list
)paren
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
id|c-&gt;parents
suffix:semicolon
id|seen_commits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;object.flags
op_amp
id|best-&gt;flag_within
)paren
(brace
r_struct
id|commit_list
op_star
id|a
op_assign
op_star
id|list
suffix:semicolon
r_while
c_loop
(paren
id|a
)paren
(brace
r_struct
id|commit
op_star
id|i
op_assign
id|a-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i-&gt;object.flags
op_amp
id|best-&gt;flag_within
)paren
)paren
r_break
suffix:semicolon
id|a
op_assign
id|a-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_break
suffix:semicolon
)brace
r_else
id|best-&gt;depth
op_increment
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
id|parse_commit
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;object.flags
op_amp
id|SEEN
)paren
)paren
id|insert_by_date
c_func
(paren
id|p
comma
id|list
)paren
suffix:semicolon
id|p-&gt;object.flags
op_or_assign
id|c-&gt;object.flags
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
r_return
id|seen_commits
suffix:semicolon
)brace
DECL|function|display_name
r_static
r_void
id|display_name
c_func
(paren
r_struct
id|commit_name
op_star
id|n
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;prio
op_eq
l_int|2
op_logical_and
op_logical_neg
id|n-&gt;tag
)paren
(brace
id|n-&gt;tag
op_assign
id|lookup_tag
c_func
(paren
id|n-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n-&gt;tag
op_logical_or
id|parse_tag
c_func
(paren
id|n-&gt;tag
)paren
op_logical_or
op_logical_neg
id|n-&gt;tag-&gt;tag
)paren
id|die
c_func
(paren
l_string|&quot;annotated tag %s not available&quot;
comma
id|n-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|n-&gt;tag-&gt;tag
comma
id|all
ques
c_cond
id|n-&gt;path
op_plus
l_int|5
suffix:colon
id|n-&gt;path
)paren
)paren
id|warning
c_func
(paren
l_string|&quot;tag &squot;%s&squot; is really &squot;%s&squot; here&quot;
comma
id|n-&gt;tag-&gt;tag
comma
id|n-&gt;path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n-&gt;tag
)paren
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|n-&gt;tag-&gt;tag
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|n-&gt;path
)paren
suffix:semicolon
)brace
DECL|function|show_suffix
r_static
r_void
id|show_suffix
c_func
(paren
r_int
id|depth
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;-%d-g%s&quot;
comma
id|depth
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|abbrev
)paren
)paren
suffix:semicolon
)brace
DECL|function|describe
r_static
r_void
id|describe
c_func
(paren
r_const
r_char
op_star
id|arg
comma
r_int
id|last_one
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
id|commit
op_star
id|cmit
comma
op_star
id|gave_up_on
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|list
suffix:semicolon
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_name
op_star
id|n
suffix:semicolon
r_struct
id|possible_tag
id|all_matches
(braket
id|MAX_TAGS
)braket
suffix:semicolon
r_int
r_int
id|match_cnt
op_assign
l_int|0
comma
id|annotated_cnt
op_assign
l_int|0
comma
id|cur_match
suffix:semicolon
r_int
r_int
id|seen_commits
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|cmit
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
id|cmit
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a valid &squot;%s&squot; object&quot;
comma
id|arg
comma
id|commit_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
id|initialized
op_assign
l_int|1
suffix:semicolon
id|for_each_ref
c_func
(paren
id|get_name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found_names
)paren
id|die
c_func
(paren
l_string|&quot;cannot describe &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|n
op_assign
id|cmit-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
multiline_comment|/*&n;&t;&t; * Exact match to an existing ref.&n;&t;&t; */
id|display_name
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|longformat
)paren
id|show_suffix
c_func
(paren
l_int|0
comma
id|n-&gt;tag
ques
c_cond
id|n-&gt;tag-&gt;tagged-&gt;sha1
suffix:colon
id|sha1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|max_candidates
)paren
id|die
c_func
(paren
l_string|&quot;no tag exactly matches &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|cmit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;searching to describe %s&bslash;n&quot;
comma
id|arg
)paren
suffix:semicolon
id|list
op_assign
l_int|NULL
suffix:semicolon
id|cmit-&gt;object.flags
op_assign
id|SEEN
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|cmit
comma
op_amp
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit
op_star
id|c
op_assign
id|pop_commit
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
id|c-&gt;parents
suffix:semicolon
id|seen_commits
op_increment
suffix:semicolon
id|n
op_assign
id|c-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
r_if
c_cond
(paren
id|match_cnt
OL
id|max_candidates
)paren
(brace
r_struct
id|possible_tag
op_star
id|t
op_assign
op_amp
id|all_matches
(braket
id|match_cnt
op_increment
)braket
suffix:semicolon
id|t-&gt;name
op_assign
id|n
suffix:semicolon
id|t-&gt;depth
op_assign
id|seen_commits
l_int|1
suffix:semicolon
id|t-&gt;flag_within
op_assign
l_int|1u
op_lshift
id|match_cnt
suffix:semicolon
id|t-&gt;found_order
op_assign
id|match_cnt
suffix:semicolon
id|c-&gt;object.flags
op_or_assign
id|t-&gt;flag_within
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;prio
op_eq
l_int|2
)paren
id|annotated_cnt
op_increment
suffix:semicolon
)brace
r_else
(brace
id|gave_up_on
op_assign
id|c
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|cur_match
op_assign
l_int|0
suffix:semicolon
id|cur_match
OL
id|match_cnt
suffix:semicolon
id|cur_match
op_increment
)paren
(brace
r_struct
id|possible_tag
op_star
id|t
op_assign
op_amp
id|all_matches
(braket
id|cur_match
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|c-&gt;object.flags
op_amp
id|t-&gt;flag_within
)paren
)paren
id|t-&gt;depth
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|annotated_cnt
op_logical_and
op_logical_neg
id|list
)paren
(brace
r_if
c_cond
(paren
id|debug
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;finished search at %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|c-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|parse_commit
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;object.flags
op_amp
id|SEEN
)paren
)paren
id|insert_by_date
c_func
(paren
id|p
comma
op_amp
id|list
)paren
suffix:semicolon
id|p-&gt;object.flags
op_or_assign
id|c-&gt;object.flags
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|match_cnt
)paren
(brace
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|cmit-&gt;object.sha1
suffix:semicolon
r_if
c_cond
(paren
id|always
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|abbrev
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;cannot describe &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
id|qsort
c_func
(paren
id|all_matches
comma
id|match_cnt
comma
r_sizeof
(paren
id|all_matches
(braket
l_int|0
)braket
)paren
comma
id|compare_pt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gave_up_on
)paren
(brace
id|insert_by_date
c_func
(paren
id|gave_up_on
comma
op_amp
id|list
)paren
suffix:semicolon
id|seen_commits
op_decrement
suffix:semicolon
)brace
id|seen_commits
op_add_assign
id|finish_depth_computation
c_func
(paren
op_amp
id|list
comma
op_amp
id|all_matches
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
(brace
r_for
c_loop
(paren
id|cur_match
op_assign
l_int|0
suffix:semicolon
id|cur_match
OL
id|match_cnt
suffix:semicolon
id|cur_match
op_increment
)paren
(brace
r_struct
id|possible_tag
op_star
id|t
op_assign
op_amp
id|all_matches
(braket
id|cur_match
)braket
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %-11s %8d %s&bslash;n&quot;
comma
id|prio_names
(braket
id|t-&gt;name-&gt;prio
)braket
comma
id|t-&gt;depth
comma
id|t-&gt;name-&gt;path
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;traversed %lu commits&bslash;n&quot;
comma
id|seen_commits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gave_up_on
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;more than %i tags found; listed %i most recent&bslash;n&quot;
l_string|&quot;gave up search at %s&bslash;n&quot;
comma
id|max_candidates
comma
id|max_candidates
comma
id|sha1_to_hex
c_func
(paren
id|gave_up_on-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
)brace
id|display_name
c_func
(paren
id|all_matches
(braket
l_int|0
)braket
dot
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|abbrev
)paren
id|show_suffix
c_func
(paren
id|all_matches
(braket
l_int|0
)braket
dot
id|depth
comma
id|cmit-&gt;object.sha1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|last_one
)paren
id|clear_commit_marks
c_func
(paren
id|cmit
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cmd_describe
r_int
id|cmd_describe
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
id|contains
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;contains&quot;
comma
op_amp
id|contains
comma
l_string|&quot;find the tag that comes after the commit&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;debug&quot;
comma
op_amp
id|debug
comma
l_string|&quot;debug search strategy on stderr&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;all&quot;
comma
op_amp
id|all
comma
l_string|&quot;use any ref in .git/refs&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;tags&quot;
comma
op_amp
id|tags
comma
l_string|&quot;use any tag in .git/refs/tags&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;long&quot;
comma
op_amp
id|longformat
comma
l_string|&quot;always use long format&quot;
)paren
comma
id|OPT__ABBREV
c_func
(paren
op_amp
id|abbrev
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;exact-match&quot;
comma
op_amp
id|max_candidates
comma
l_string|&quot;only output exact matches&quot;
comma
l_int|0
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;candidates&quot;
comma
op_amp
id|max_candidates
comma
l_string|&quot;consider &lt;n&gt; most recent tags (default: 10)&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;match&quot;
comma
op_amp
id|pattern
comma
l_string|&quot;pattern&quot;
comma
l_string|&quot;only consider tags matching &lt;pattern&gt;&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;always&quot;
comma
op_amp
id|always
comma
l_string|&quot;show abbreviated commit object as fallback&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|options
comma
id|describe_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_candidates
OL
l_int|0
)paren
id|max_candidates
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|max_candidates
OG
id|MAX_TAGS
)paren
id|max_candidates
op_assign
id|MAX_TAGS
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|longformat
op_logical_and
id|abbrev
op_eq
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;--long is incompatible with --abbrev=0&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|contains
)paren
(brace
r_const
r_char
op_star
op_star
id|args
op_assign
id|xmalloc
c_func
(paren
(paren
l_int|7
op_plus
id|argc
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;name-rev&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--name-only&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--no-undefined&quot;
suffix:semicolon
r_if
c_cond
(paren
id|always
)paren
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--always&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all
)paren
(brace
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--tags&quot;
suffix:semicolon
r_if
c_cond
(paren
id|pattern
)paren
(brace
r_char
op_star
id|s
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
l_string|&quot;--refs=refs/tags/&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|pattern
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;--refs=refs/tags/%s&quot;
comma
id|pattern
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|s
suffix:semicolon
)brace
)brace
id|memcpy
c_func
(paren
id|args
op_plus
id|i
comma
id|argv
comma
id|argc
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|args
(braket
id|i
op_plus
id|argc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|cmd_name_rev
c_func
(paren
id|i
op_plus
id|argc
comma
id|args
comma
id|prefix
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
)paren
(brace
id|describe
c_func
(paren
l_string|&quot;HEAD&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|argc
op_decrement
OG
l_int|0
)paren
(brace
id|describe
c_func
(paren
op_star
id|argv
op_increment
comma
id|argc
op_eq
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
