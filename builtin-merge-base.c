macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|function|show_merge_base
r_static
r_int
id|show_merge_base
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
comma
r_int
id|show_all
)paren
(brace
r_struct
id|commit_list
op_star
id|result
op_assign
id|get_merge_bases
c_func
(paren
id|rev1
comma
id|rev2
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
id|merge_base_usage
(braket
)braket
op_assign
l_string|&quot;git merge-base [--all] &lt;commit-id&gt; &lt;commit-id&gt;&quot;
suffix:semicolon
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
r_int
id|show_all
op_assign
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
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
r_const
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
)paren
id|usage
c_func
(paren
id|merge_base_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
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
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|2
)braket
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
id|show_merge_base
c_func
(paren
id|rev1
comma
id|rev2
comma
id|show_all
)paren
suffix:semicolon
)brace
eof
