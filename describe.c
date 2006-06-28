macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|macro|SEEN
mdefine_line|#define SEEN (1u &lt;&lt; 0)
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
DECL|variable|all
r_static
r_int
id|all
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default to annotated tags only */
DECL|variable|tags
r_static
r_int
id|tags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* But allow any tags if --tags is specified */
DECL|variable|abbrev
r_static
r_int
id|abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
DECL|variable|names
DECL|variable|allocs
r_static
r_int
id|names
op_assign
l_int|0
comma
id|allocs
op_assign
l_int|0
suffix:semicolon
DECL|struct|commit_name
r_static
r_struct
id|commit_name
(brace
DECL|member|commit
r_const
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
op_assign
l_int|NULL
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
id|i
op_assign
id|names
suffix:semicolon
r_struct
id|commit_name
op_star
op_star
id|p
op_assign
id|name_array
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
r_struct
id|commit_name
op_star
id|n
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;commit
op_eq
id|cmit
)paren
r_return
id|n
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
r_const
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
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|allocs
)paren
(brace
id|allocs
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
op_assign
id|xrealloc
c_func
(paren
id|name_array
comma
id|allocs
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
id|idx
)braket
op_assign
id|name
suffix:semicolon
id|names
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
id|TYPE_TAG
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
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|name_array
comma
id|names
comma
r_sizeof
(paren
op_star
id|name_array
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
id|list
op_assign
l_int|NULL
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
id|pop_most_recent_commit
c_func
(paren
op_amp
id|list
comma
id|SEEN
)paren
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
id|printf
c_func
(paren
l_string|&quot;%s-g%s&bslash;n&quot;
comma
id|n-&gt;path
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
id|SEEN
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
)brace
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
op_le
id|abbrev
)paren
id|abbrev
op_assign
id|DEFAULT_ABBREV
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
r_if
c_cond
(paren
id|i
op_eq
id|argc
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
