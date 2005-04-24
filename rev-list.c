macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit_list
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
op_logical_or
id|get_sha1_hex
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|sha1
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;rev-list &lt;commit-id&gt;&quot;
)paren
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
id|parse_commit
c_func
(paren
id|commit
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad commit object&quot;
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|commit
comma
op_amp
id|list
)paren
suffix:semicolon
r_do
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|pop_most_recent_commit
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
