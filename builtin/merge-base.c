macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|function|show_merge_base
r_static
r_int
id|show_merge_base
c_func
(paren
r_struct
id|commit
op_star
op_star
id|rev
comma
r_int
id|rev_nr
comma
r_int
id|show_all
)paren
(brace
r_struct
id|commit_list
op_star
id|result
suffix:semicolon
id|result
op_assign
id|get_merge_bases_many
c_func
(paren
id|rev
(braket
l_int|0
)braket
comma
id|rev_nr
l_int|1
comma
id|rev
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
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
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|result-&gt;item-&gt;object.sha1
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
id|result
op_assign
id|result-&gt;next
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
op_star
r_const
id|merge_base_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git merge-base [-a|--all] &lt;commit&gt; &lt;commit&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git merge-base [-a|--all] --octopus &lt;commit&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git merge-base --independent &lt;commit&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git merge-base --is-ancestor &lt;commit&gt; &lt;commit&gt;&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|get_commit_reference
r_static
r_struct
id|commit
op_star
id|get_commit_reference
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_int
r_char
id|revkey
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|r
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|revkey
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
id|r
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
id|r
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid commit name %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|handle_independent
r_static
r_int
id|handle_independent
c_func
(paren
r_int
id|count
comma
r_const
r_char
op_star
op_star
id|args
)paren
(brace
r_struct
id|commit_list
op_star
id|revs
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|count
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|commit_list_insert
c_func
(paren
id|get_commit_reference
c_func
(paren
id|args
(braket
id|i
)braket
)paren
comma
op_amp
id|revs
)paren
suffix:semicolon
id|result
op_assign
id|reduce_heads
c_func
(paren
id|revs
)paren
suffix:semicolon
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
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|result-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|result
op_assign
id|result-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_octopus
r_static
r_int
id|handle_octopus
c_func
(paren
r_int
id|count
comma
r_const
r_char
op_star
op_star
id|args
comma
r_int
id|show_all
)paren
(brace
r_struct
id|commit_list
op_star
id|revs
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|count
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|commit_list_insert
c_func
(paren
id|get_commit_reference
c_func
(paren
id|args
(braket
id|i
)braket
)paren
comma
op_amp
id|revs
)paren
suffix:semicolon
id|result
op_assign
id|reduce_heads
c_func
(paren
id|get_octopus_merge_bases
c_func
(paren
id|revs
)paren
)paren
suffix:semicolon
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
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|result-&gt;item-&gt;object.sha1
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
id|result
op_assign
id|result-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_is_ancestor
r_static
r_int
id|handle_is_ancestor
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
)paren
(brace
r_struct
id|commit
op_star
id|one
comma
op_star
id|two
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;--is-ancestor takes exactly two commits&quot;
)paren
suffix:semicolon
id|one
op_assign
id|get_commit_reference
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|two
op_assign
id|get_commit_reference
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_merge_bases
c_func
(paren
id|one
comma
id|two
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cmd_merge_base
r_int
id|cmd_merge_base
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
id|commit
op_star
op_star
id|rev
suffix:semicolon
r_int
id|rev_nr
op_assign
l_int|0
suffix:semicolon
r_int
id|show_all
op_assign
l_int|0
suffix:semicolon
r_int
id|octopus
op_assign
l_int|0
suffix:semicolon
r_int
id|reduce
op_assign
l_int|0
suffix:semicolon
r_int
id|is_ancestor
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
id|OPT_BOOL
c_func
(paren
l_char|&squot;a&squot;
comma
l_string|&quot;all&quot;
comma
op_amp
id|show_all
comma
id|N_
c_func
(paren
l_string|&quot;output all common ancestors&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;octopus&quot;
comma
op_amp
id|octopus
comma
id|N_
c_func
(paren
l_string|&quot;find ancestors for a single n-way merge&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;independent&quot;
comma
op_amp
id|reduce
comma
id|N_
c_func
(paren
l_string|&quot;list revs not reachable from others&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;is-ancestor&quot;
comma
op_amp
id|is_ancestor
comma
id|N_
c_func
(paren
l_string|&quot;is the first one ancestor of the other?&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
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
id|merge_base_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|octopus
op_logical_and
op_logical_neg
id|reduce
op_logical_and
id|argc
OL
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|merge_base_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_ancestor
op_logical_and
(paren
id|show_all
op_logical_or
id|octopus
op_logical_or
id|reduce
)paren
)paren
id|die
c_func
(paren
l_string|&quot;--is-ancestor cannot be used with other options&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_ancestor
)paren
r_return
id|handle_is_ancestor
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reduce
op_logical_and
(paren
id|show_all
op_logical_or
id|octopus
)paren
)paren
id|die
c_func
(paren
l_string|&quot;--independent cannot be used with other options&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|octopus
)paren
r_return
id|handle_octopus
c_func
(paren
id|argc
comma
id|argv
comma
id|show_all
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|reduce
)paren
r_return
id|handle_independent
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
id|rev
op_assign
id|xmalloc
c_func
(paren
id|argc
op_star
r_sizeof
(paren
op_star
id|rev
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argc
op_decrement
OG
l_int|0
)paren
id|rev
(braket
id|rev_nr
op_increment
)braket
op_assign
id|get_commit_reference
c_func
(paren
op_star
id|argv
op_increment
)paren
suffix:semicolon
r_return
id|show_merge_base
c_func
(paren
id|rev
comma
id|rev_nr
comma
id|show_all
)paren
suffix:semicolon
)brace
eof
