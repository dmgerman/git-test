macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|git_update_ref_usage
r_static
r_const
r_char
id|git_update_ref_usage
(braket
)braket
op_assign
l_string|&quot;git-update-ref [-m &lt;reason&gt;] (-d &lt;refname&gt; &lt;value&gt; | [--no-deref] &lt;refname&gt; &lt;value&gt; [&lt;oldval&gt;])&quot;
suffix:semicolon
DECL|function|cmd_update_ref
r_int
id|cmd_update_ref
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
r_char
op_star
id|refname
op_assign
l_int|NULL
comma
op_star
id|value
op_assign
l_int|NULL
comma
op_star
id|oldval
op_assign
l_int|NULL
comma
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|oldsha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|i
comma
r_delete
comma
id|ref_flags
suffix:semicolon
r_delete
op_assign
l_int|0
suffix:semicolon
id|ref_flags
op_assign
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-m&quot;
comma
id|argv
(braket
id|i
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_plus
l_int|1
op_ge
id|argc
)paren
id|usage
c_func
(paren
id|git_update_ref_usage
)paren
suffix:semicolon
id|msg
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
op_logical_neg
op_star
id|msg
)paren
id|die
c_func
(paren
l_string|&quot;Refusing to perform update with empty message.&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-d&quot;
comma
id|argv
(braket
id|i
)braket
)paren
)paren
(brace
r_delete
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--no-deref&quot;
comma
id|argv
(braket
id|i
)braket
)paren
)paren
(brace
id|ref_flags
op_or_assign
id|REF_NODEREF
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|refname
)paren
(brace
id|refname
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|value
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|oldval
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|refname
op_logical_or
op_logical_neg
id|value
)paren
id|usage
c_func
(paren
id|git_update_ref_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|value
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s: not a valid SHA1&quot;
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
r_delete
)paren
(brace
r_if
c_cond
(paren
id|oldval
)paren
id|usage
c_func
(paren
id|git_update_ref_usage
)paren
suffix:semicolon
r_return
id|delete_ref
c_func
(paren
id|refname
comma
id|sha1
)paren
suffix:semicolon
)brace
id|hashclr
c_func
(paren
id|oldsha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldval
op_logical_and
op_star
id|oldval
op_logical_and
id|get_sha1
c_func
(paren
id|oldval
comma
id|oldsha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s: not a valid old SHA1&quot;
comma
id|oldval
)paren
suffix:semicolon
r_return
id|update_ref
c_func
(paren
id|msg
comma
id|refname
comma
id|sha1
comma
id|oldval
ques
c_cond
id|oldsha1
suffix:colon
l_int|NULL
comma
id|ref_flags
comma
id|DIE_ON_ERR
)paren
suffix:semicolon
)brace
eof
