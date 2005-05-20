macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|function|process_list
r_static
r_struct
id|commit
op_star
id|process_list
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list_p
comma
r_int
id|this_mark
comma
r_int
id|other_mark
)paren
(brace
r_struct
id|commit
op_star
id|item
op_assign
(paren
op_star
id|list_p
)paren
op_member_access_from_pointer
id|item
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.flags
op_amp
id|other_mark
)paren
(brace
r_return
id|item
suffix:semicolon
)brace
r_else
(brace
id|pop_most_recent_commit
c_func
(paren
id|list_p
comma
id|this_mark
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|common_ancestor
r_static
r_struct
id|commit
op_star
id|common_ancestor
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
)paren
(brace
r_struct
id|commit_list
op_star
id|rev1list
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|rev2list
op_assign
l_int|NULL
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|rev1
comma
op_amp
id|rev1list
)paren
suffix:semicolon
id|rev1-&gt;object.flags
op_or_assign
l_int|0x1
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|rev2
comma
op_amp
id|rev2list
)paren
suffix:semicolon
id|rev2-&gt;object.flags
op_or_assign
l_int|0x2
suffix:semicolon
id|parse_commit
c_func
(paren
id|rev1
)paren
suffix:semicolon
id|parse_commit
c_func
(paren
id|rev2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|rev1list
op_logical_or
id|rev2list
)paren
(brace
r_struct
id|commit
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev1list
)paren
(brace
singleline_comment|// process 2
id|ret
op_assign
id|process_list
c_func
(paren
op_amp
id|rev2list
comma
l_int|0x2
comma
l_int|0x1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|rev2list
)paren
(brace
singleline_comment|// process 1
id|ret
op_assign
id|process_list
c_func
(paren
op_amp
id|rev1list
comma
l_int|0x1
comma
l_int|0x2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rev1list-&gt;item-&gt;date
OL
id|rev2list-&gt;item-&gt;date
)paren
(brace
singleline_comment|// process 2
id|ret
op_assign
id|process_list
c_func
(paren
op_amp
id|rev2list
comma
l_int|0x2
comma
l_int|0x1
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// process 1
id|ret
op_assign
id|process_list
c_func
(paren
op_amp
id|rev1list
comma
l_int|0x1
comma
l_int|0x2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
id|free_commit_list
c_func
(paren
id|rev1list
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|rev2list
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
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
r_struct
id|commit
op_star
id|rev1
comma
op_star
id|rev2
comma
op_star
id|ret
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
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
op_logical_or
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
op_logical_or
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
(brace
id|usage
c_func
(paren
l_string|&quot;git-merge-base &lt;commit-id&gt; &lt;commit-id&gt;&quot;
)paren
suffix:semicolon
)brace
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
id|ret
op_assign
id|common_ancestor
c_func
(paren
id|rev1
comma
id|rev2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ret-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
