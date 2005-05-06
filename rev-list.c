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
r_char
op_star
id|commit_arg
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|max_age
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|min_age
op_assign
l_int|1
suffix:semicolon
r_int
id|max_count
op_assign
l_int|1
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--max-count=&quot;
comma
l_int|12
)paren
)paren
(brace
id|max_count
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|12
)paren
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
l_string|&quot;--max-age=&quot;
comma
l_int|10
)paren
)paren
(brace
id|max_age
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
)paren
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
l_string|&quot;--min-age=&quot;
comma
l_int|10
)paren
)paren
(brace
id|min_age
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
)paren
suffix:semicolon
)brace
r_else
(brace
id|commit_arg
op_assign
id|arg
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|commit_arg
op_logical_or
id|get_sha1
c_func
(paren
id|commit_arg
comma
id|sha1
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;usage: rev-list [OPTION] commit-id&bslash;n&quot;
l_string|&quot;  --max-count=nr&bslash;n&quot;
l_string|&quot;  --max-age=epoch&bslash;n&quot;
l_string|&quot;  --min-age=epoch&bslash;n&quot;
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
comma
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|min_age
op_ne
l_int|1
op_logical_and
(paren
id|commit-&gt;date
OG
id|min_age
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|max_age
op_ne
l_int|1
op_logical_and
(paren
id|commit-&gt;date
OL
id|max_age
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|max_count
op_ne
l_int|1
op_logical_and
op_logical_neg
id|max_count
op_decrement
)paren
r_break
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
