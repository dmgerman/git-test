macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;merge-recursive.h&quot;
DECL|function|better_branch_name
r_static
r_const
r_char
op_star
id|better_branch_name
c_func
(paren
r_const
r_char
op_star
id|branch
)paren
(brace
r_static
r_char
id|githead_env
(braket
l_int|8
op_plus
l_int|40
op_plus
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|branch
)paren
op_ne
l_int|40
)paren
r_return
id|branch
suffix:semicolon
id|sprintf
c_func
(paren
id|githead_env
comma
l_string|&quot;GITHEAD_%s&quot;
comma
id|branch
)paren
suffix:semicolon
id|name
op_assign
id|getenv
c_func
(paren
id|githead_env
)paren
suffix:semicolon
r_return
id|name
ques
c_cond
id|name
suffix:colon
id|branch
suffix:semicolon
)brace
DECL|function|cmd_merge_recursive
r_int
id|cmd_merge_recursive
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
r_const
r_int
r_char
op_star
id|bases
(braket
l_int|21
)braket
suffix:semicolon
r_int
id|bases_count
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|failed
suffix:semicolon
r_int
r_char
id|h1
(braket
l_int|20
)braket
comma
id|h2
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|merge_options
id|o
suffix:semicolon
r_struct
id|commit
op_star
id|result
suffix:semicolon
id|init_merge_options
c_func
(paren
op_amp
id|o
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|suffixcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;-subtree&quot;
)paren
)paren
id|o.subtree_shift
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|4
)paren
id|usagef
c_func
(paren
l_string|&quot;%s &lt;base&gt;... -- &lt;head&gt; &lt;remote&gt; ...&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
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
op_increment
id|i
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|arg
(braket
l_int|2
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|parse_merge_opt
c_func
(paren
op_amp
id|o
comma
id|arg
op_plus
l_int|2
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unknown option %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bases_count
OL
id|ARRAY_SIZE
c_func
(paren
id|bases
)paren
op_minus
l_int|1
)paren
(brace
r_int
r_char
op_star
id|sha
op_assign
id|xmalloc
c_func
(paren
l_int|20
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
id|i
)braket
comma
id|sha
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not parse object &squot;%s&squot;&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|bases
(braket
id|bases_count
op_increment
)braket
op_assign
id|sha
suffix:semicolon
)brace
r_else
id|warning
c_func
(paren
l_string|&quot;Cannot handle more than %d bases. &quot;
l_string|&quot;Ignoring %s.&quot;
comma
(paren
r_int
)paren
id|ARRAY_SIZE
c_func
(paren
id|bases
)paren
op_minus
l_int|1
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
id|i
op_ne
l_int|3
)paren
multiline_comment|/* &quot;--&quot; &quot;&lt;head&gt;&quot; &quot;&lt;remote&gt;&quot; */
id|die
c_func
(paren
l_string|&quot;Not handling anything other than two heads merge.&quot;
)paren
suffix:semicolon
id|o.branch1
op_assign
id|argv
(braket
op_increment
id|i
)braket
suffix:semicolon
id|o.branch2
op_assign
id|argv
(braket
op_increment
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|o.branch1
comma
id|h1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not resolve ref &squot;%s&squot;&quot;
comma
id|o.branch1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|o.branch2
comma
id|h2
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not resolve ref &squot;%s&squot;&quot;
comma
id|o.branch2
)paren
suffix:semicolon
id|o.branch1
op_assign
id|better_branch_name
c_func
(paren
id|o.branch1
)paren
suffix:semicolon
id|o.branch2
op_assign
id|better_branch_name
c_func
(paren
id|o.branch2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o.verbosity
op_ge
l_int|3
)paren
id|printf
c_func
(paren
l_string|&quot;Merging %s with %s&bslash;n&quot;
comma
id|o.branch1
comma
id|o.branch2
)paren
suffix:semicolon
id|failed
op_assign
id|merge_recursive_generic
c_func
(paren
op_amp
id|o
comma
id|h1
comma
id|h2
comma
id|bases_count
comma
id|bases
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|failed
OL
l_int|0
)paren
r_return
l_int|128
suffix:semicolon
multiline_comment|/* die() error code */
r_return
id|failed
suffix:semicolon
)brace
eof
