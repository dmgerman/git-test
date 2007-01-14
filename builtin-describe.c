macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|macro|SEEN
mdefine_line|#define SEEN&t;&t;(1u&lt;&lt;0)
DECL|macro|MAX_TAGS
mdefine_line|#define MAX_TAGS&t;(FLAG_BITS - 1)
DECL|variable|describe_usage
r_static
r_const
r_char
id|describe_usage
(braket
)braket
op_assign
l_string|&quot;git-describe [--all] [--tags] [--abbrev=&lt;n&gt;] &lt;committish&gt;*&quot;
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
multiline_comment|/* Default to annotated tags only */
DECL|variable|tags
r_static
r_int
id|tags
suffix:semicolon
multiline_comment|/* But allow any tags if --tags is specified */
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
DECL|variable|names
DECL|variable|allocs
r_static
r_int
r_int
id|names
(braket
l_int|256
)braket
comma
id|allocs
(braket
l_int|256
)braket
suffix:semicolon
DECL|struct|commit_name
r_static
r_struct
id|commit_name
(brace
DECL|member|commit
r_struct
id|commit
op_star
id|commit
suffix:semicolon
DECL|member|prio
r_int
id|prio
suffix:semicolon
multiline_comment|/* annotated tag = 2, tag = 1, head = 0 */
DECL|member|path
r_char
id|path
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
multiline_comment|/* more */
DECL|variable|name_array
)brace
op_star
op_star
id|name_array
(braket
l_int|256
)braket
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
DECL|function|match
r_static
r_struct
id|commit_name
op_star
id|match
c_func
(paren
r_struct
id|commit
op_star
id|cmit
)paren
(brace
r_int
r_char
id|level0
op_assign
id|cmit-&gt;object.sha1
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|commit_name
op_star
op_star
id|p
op_assign
id|name_array
(braket
id|level0
)braket
suffix:semicolon
r_int
r_int
id|hi
op_assign
id|names
(braket
id|level0
)braket
suffix:semicolon
r_int
r_int
id|lo
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|lo
OL
id|hi
)paren
(brace
r_int
r_int
id|mi
op_assign
(paren
id|lo
op_plus
id|hi
)paren
op_div
l_int|2
suffix:semicolon
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|p
(braket
id|mi
)braket
op_member_access_from_pointer
id|commit-&gt;object.sha1
comma
id|cmit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
(brace
r_while
c_loop
(paren
id|mi
op_logical_and
id|p
(braket
id|mi
l_int|1
)braket
op_member_access_from_pointer
id|commit
op_eq
id|cmit
)paren
id|mi
op_decrement
suffix:semicolon
r_return
id|p
(braket
id|mi
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
id|hi
op_assign
id|mi
suffix:semicolon
r_else
id|lo
op_assign
id|mi
op_plus
l_int|1
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
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
)paren
(brace
r_int
id|idx
suffix:semicolon
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
r_struct
id|commit_name
op_star
id|name
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
r_int
r_char
id|m
op_assign
id|commit-&gt;object.sha1
(braket
l_int|0
)braket
suffix:semicolon
id|name-&gt;commit
op_assign
id|commit
suffix:semicolon
id|name-&gt;prio
op_assign
id|prio
suffix:semicolon
id|memcpy
c_func
(paren
id|name-&gt;path
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|idx
op_assign
id|names
(braket
id|m
)braket
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|allocs
(braket
id|m
)braket
)paren
(brace
id|allocs
(braket
id|m
)braket
op_assign
(paren
id|idx
op_plus
l_int|50
)paren
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
id|name_array
(braket
id|m
)braket
op_assign
id|xrealloc
c_func
(paren
id|name_array
(braket
id|m
)braket
comma
id|allocs
(braket
id|m
)braket
op_star
r_sizeof
(paren
op_star
id|name_array
)paren
)paren
suffix:semicolon
)brace
id|name_array
(braket
id|m
)braket
(braket
id|idx
)braket
op_assign
id|name
suffix:semicolon
id|names
(braket
id|m
)braket
op_assign
op_increment
id|idx
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
r_struct
id|object
op_star
id|object
suffix:semicolon
r_int
id|prio
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
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
multiline_comment|/* If --all, then any refs are used.&n;&t; * If --tags, then any tags are used.&n;&t; * Otherwise only annotated tags are used.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|path
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
)paren
)paren
(brace
r_if
c_cond
(paren
id|object-&gt;type
op_eq
id|OBJ_TAG
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
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compare_names
r_static
r_int
id|compare_names
c_func
(paren
r_const
r_void
op_star
id|_a
comma
r_const
r_void
op_star
id|_b
)paren
(brace
r_struct
id|commit_name
op_star
id|a
op_assign
op_star
(paren
r_struct
id|commit_name
op_star
op_star
)paren
id|_a
suffix:semicolon
r_struct
id|commit_name
op_star
id|b
op_assign
op_star
(paren
r_struct
id|commit_name
op_star
op_star
)paren
id|_b
suffix:semicolon
r_int
r_int
id|a_date
op_assign
id|a-&gt;commit-&gt;date
suffix:semicolon
r_int
r_int
id|b_date
op_assign
id|b-&gt;commit-&gt;date
suffix:semicolon
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|a-&gt;commit-&gt;object.sha1
comma
id|b-&gt;commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
)paren
r_return
id|cmp
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;prio
op_ne
id|b-&gt;prio
)paren
r_return
id|b-&gt;prio
id|a-&gt;prio
suffix:semicolon
r_return
(paren
id|a_date
OG
id|b_date
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|a_date
op_eq
id|b_date
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
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
id|a-&gt;name-&gt;prio
op_ne
id|b-&gt;name-&gt;prio
)paren
r_return
id|b-&gt;name-&gt;prio
id|a-&gt;name-&gt;prio
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
r_int
id|found
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
r_int
r_int
id|m
suffix:semicolon
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
r_for
c_loop
(paren
id|m
op_assign
l_int|0
suffix:semicolon
id|m
OL
id|ARRAY_SIZE
c_func
(paren
id|name_array
)paren
suffix:semicolon
id|m
op_increment
)paren
id|qsort
c_func
(paren
id|name_array
(braket
id|m
)braket
comma
id|names
(braket
id|m
)braket
comma
r_sizeof
(paren
op_star
id|name_array
(braket
id|m
)braket
)paren
comma
id|compare_names
)paren
suffix:semicolon
)brace
id|n
op_assign
id|match
c_func
(paren
id|cmit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|n-&gt;path
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|match
c_func
(paren
id|c
)paren
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
id|found
op_increment
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
id|free_commit_list
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match_cnt
)paren
id|die
c_func
(paren
l_string|&quot;cannot describe &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|cmit-&gt;object.sha1
)paren
)paren
suffix:semicolon
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
id|printf
c_func
(paren
l_string|&quot;%s-g%s&bslash;n&quot;
comma
id|all_matches
(braket
l_int|0
)braket
dot
id|name-&gt;path
comma
id|find_unique_abbrev
c_func
(paren
id|cmit-&gt;object.sha1
comma
id|abbrev
)paren
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
id|i
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
op_star
id|arg
op_ne
l_char|&squot;-&squot;
)paren
r_break
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
l_string|&quot;--debug&quot;
)paren
)paren
id|debug
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
l_string|&quot;--all&quot;
)paren
)paren
id|all
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
id|tags
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
l_string|&quot;--abbrev=&quot;
comma
l_int|9
)paren
)paren
(brace
id|abbrev
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|9
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|abbrev
OL
id|MINIMUM_ABBREV
op_logical_or
l_int|40
OL
id|abbrev
)paren
id|abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
)brace
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
l_string|&quot;--candidates=&quot;
comma
l_int|13
)paren
)paren
(brace
id|max_candidates
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|13
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_candidates
OL
l_int|1
)paren
id|max_candidates
op_assign
l_int|1
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
)brace
r_else
id|usage
c_func
(paren
id|describe_usage
)paren
suffix:semicolon
)brace
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_le
id|i
)paren
id|describe
c_func
(paren
l_string|&quot;HEAD&quot;
comma
l_int|1
)paren
suffix:semicolon
r_else
r_while
c_loop
(paren
id|i
OL
id|argc
)paren
(brace
id|describe
c_func
(paren
id|argv
(braket
id|i
)braket
comma
(paren
id|i
op_eq
id|argc
l_int|1
)paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
