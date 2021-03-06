macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
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
id|get_merge_bases_many_dirty
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
id|oid_to_hex
c_func
(paren
op_amp
id|result-&gt;item-&gt;object.oid
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
l_string|&quot;git merge-base [-a | --all] &lt;commit&gt; &lt;commit&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git merge-base [-a | --all] --octopus &lt;commit&gt;...&quot;
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
id|N_
c_func
(paren
l_string|&quot;git merge-base --fork-point &lt;ref&gt; [&lt;commit&gt;]&quot;
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
id|oid_to_hex
c_func
(paren
op_amp
id|result-&gt;item-&gt;object.oid
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
id|oid_to_hex
c_func
(paren
op_amp
id|result-&gt;item-&gt;object.oid
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
DECL|struct|rev_collect
r_struct
id|rev_collect
(brace
DECL|member|commit
r_struct
id|commit
op_star
op_star
id|commit
suffix:semicolon
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|initial
r_int
r_int
id|initial
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|function|add_one_commit
r_static
r_void
id|add_one_commit
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_struct
id|rev_collect
op_star
id|revs
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|sha1
)paren
)paren
r_return
suffix:semicolon
id|commit
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
op_logical_neg
id|commit
op_logical_or
(paren
id|commit-&gt;object.flags
op_amp
id|TMP_MARK
)paren
op_logical_or
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
r_return
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|revs-&gt;commit
comma
id|revs-&gt;nr
op_plus
l_int|1
comma
id|revs-&gt;alloc
)paren
suffix:semicolon
id|revs-&gt;commit
(braket
id|revs-&gt;nr
op_increment
)braket
op_assign
id|commit
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|TMP_MARK
suffix:semicolon
)brace
DECL|function|collect_one_reflog_ent
r_static
r_int
id|collect_one_reflog_ent
c_func
(paren
r_int
r_char
op_star
id|osha1
comma
r_int
r_char
op_star
id|nsha1
comma
r_const
r_char
op_star
id|ident
comma
r_int
r_int
id|timestamp
comma
r_int
id|tz
comma
r_const
r_char
op_star
id|message
comma
r_void
op_star
id|cbdata
)paren
(brace
r_struct
id|rev_collect
op_star
id|revs
op_assign
id|cbdata
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;initial
)paren
(brace
id|revs-&gt;initial
op_assign
l_int|0
suffix:semicolon
id|add_one_commit
c_func
(paren
id|osha1
comma
id|revs
)paren
suffix:semicolon
)brace
id|add_one_commit
c_func
(paren
id|nsha1
comma
id|revs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_fork_point
r_static
r_int
id|handle_fork_point
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
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|refname
suffix:semicolon
r_const
r_char
op_star
id|commitname
suffix:semicolon
r_struct
id|rev_collect
id|revs
suffix:semicolon
r_struct
id|commit
op_star
id|derived
suffix:semicolon
r_struct
id|commit_list
op_star
id|bases
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dwim_ref
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|strlen
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
comma
id|sha1
comma
op_amp
id|refname
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|die
c_func
(paren
l_string|&quot;No such ref: &squot;%s&squot;&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
r_break
suffix:semicolon
multiline_comment|/* good */
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;Ambiguous refname: &squot;%s&squot;&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|commitname
op_assign
(paren
id|argc
op_eq
l_int|2
)paren
ques
c_cond
id|argv
(braket
l_int|1
)braket
suffix:colon
l_string|&quot;HEAD&quot;
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|commitname
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;&quot;
comma
id|commitname
)paren
suffix:semicolon
id|derived
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|revs
comma
l_int|0
comma
r_sizeof
(paren
id|revs
)paren
)paren
suffix:semicolon
id|revs.initial
op_assign
l_int|1
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|refname
comma
id|collect_one_reflog_ent
comma
op_amp
id|revs
)paren
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
id|revs.nr
suffix:semicolon
id|i
op_increment
)paren
id|revs.commit
(braket
id|i
)braket
op_member_access_from_pointer
id|object.flags
op_and_assign
op_complement
id|TMP_MARK
suffix:semicolon
id|bases
op_assign
id|get_merge_bases_many_dirty
c_func
(paren
id|derived
comma
id|revs.nr
comma
id|revs.commit
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There should be one and only one merge base, when we found&n;&t; * a common ancestor among reflog entries.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|bases
op_logical_or
id|bases-&gt;next
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|cleanup_return
suffix:semicolon
)brace
multiline_comment|/* And the found one must be one of the reflog entries */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|revs.nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_amp
id|bases-&gt;item-&gt;object
op_eq
op_amp
id|revs.commit
(braket
id|i
)braket
op_member_access_from_pointer
id|object
)paren
r_break
suffix:semicolon
multiline_comment|/* found */
r_if
c_cond
(paren
id|revs.nr
op_le
id|i
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* not found */
r_goto
id|cleanup_return
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|oid_to_hex
c_func
(paren
op_amp
id|bases-&gt;item-&gt;object.oid
)paren
)paren
suffix:semicolon
id|cleanup_return
suffix:colon
id|free_commit_list
c_func
(paren
id|bases
)paren
suffix:semicolon
r_return
id|ret
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
id|cmdmode
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
id|OPT_CMDMODE
c_func
(paren
l_int|0
comma
l_string|&quot;octopus&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;find ancestors for a single n-way merge&quot;
)paren
comma
l_char|&squot;o&squot;
)paren
comma
id|OPT_CMDMODE
c_func
(paren
l_int|0
comma
l_string|&quot;independent&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;list revs not reachable from others&quot;
)paren
comma
l_char|&squot;r&squot;
)paren
comma
id|OPT_CMDMODE
c_func
(paren
l_int|0
comma
l_string|&quot;is-ancestor&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;is the first one ancestor of the other?&quot;
)paren
comma
l_char|&squot;a&squot;
)paren
comma
id|OPT_CMDMODE
c_func
(paren
l_int|0
comma
l_string|&quot;fork-point&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;find where &lt;commit&gt; forked from reflog of &lt;ref&gt;&quot;
)paren
comma
l_char|&squot;f&squot;
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
id|cmdmode
op_eq
l_char|&squot;a&squot;
)paren
(brace
r_if
c_cond
(paren
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
id|show_all
)paren
id|die
c_func
(paren
l_string|&quot;--is-ancestor cannot be used with --all&quot;
)paren
suffix:semicolon
r_return
id|handle_is_ancestor
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmdmode
op_eq
l_char|&squot;r&squot;
op_logical_and
id|show_all
)paren
id|die
c_func
(paren
l_string|&quot;--independent cannot be used with --all&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmdmode
op_eq
l_char|&squot;o&squot;
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
r_if
c_cond
(paren
id|cmdmode
op_eq
l_char|&squot;r&squot;
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
r_if
c_cond
(paren
id|cmdmode
op_eq
l_char|&squot;f&squot;
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|1
op_logical_or
l_int|2
OL
id|argc
)paren
id|usage_with_options
c_func
(paren
id|merge_base_usage
comma
id|options
)paren
suffix:semicolon
r_return
id|handle_fork_point
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
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
