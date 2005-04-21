macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
multiline_comment|/*&n; * Show one commit&n; */
DECL|function|show_commit
r_void
id|show_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_char
id|cmdline
(braket
l_int|400
)braket
suffix:semicolon
r_char
id|hex
(braket
l_int|100
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Id: %s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|cmdline
comma
l_string|&quot;cat-file commit %s&quot;
comma
id|hex
)paren
suffix:semicolon
id|system
c_func
(paren
id|cmdline
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;parents
)paren
(brace
r_char
op_star
id|against
op_assign
id|sha1_to_hex
c_func
(paren
id|commit-&gt;parents-&gt;item-&gt;object.sha1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&bslash;n======== diff against %s ========&bslash;n&quot;
comma
id|against
)paren
suffix:semicolon
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|cmdline
comma
l_string|&quot;git diff -r %s:%s&quot;
comma
id|against
comma
id|hex
)paren
suffix:semicolon
id|system
c_func
(paren
id|cmdline
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;======== end ========&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Show all unseen commits, depth-first&n; */
DECL|function|show_unseen
r_void
id|show_unseen
c_func
(paren
r_struct
id|commit
op_star
id|top
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
id|top-&gt;object.flags
op_amp
l_int|2
)paren
r_return
suffix:semicolon
id|top-&gt;object.flags
op_or_assign
l_int|2
suffix:semicolon
id|parents
op_assign
id|top-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
id|show_unseen
c_func
(paren
id|parents-&gt;item
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
id|show_commit
c_func
(paren
id|top
)paren
suffix:semicolon
)brace
DECL|function|export
r_void
id|export
c_func
(paren
r_struct
id|commit
op_star
id|top
comma
r_struct
id|commit
op_star
id|base
)paren
(brace
id|mark_reachable
c_func
(paren
op_amp
id|top-&gt;object
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
id|mark_reachable
c_func
(paren
op_amp
id|base-&gt;object
comma
l_int|2
)paren
suffix:semicolon
id|show_unseen
c_func
(paren
id|top
)paren
suffix:semicolon
)brace
DECL|function|get_commit
r_struct
id|commit
op_star
id|get_commit
c_func
(paren
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
id|commit-&gt;object.parsed
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
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
l_string|&quot;unable to parse commit %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
id|get_commit
c_func
(paren
id|parents-&gt;item-&gt;object.sha1
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
r_return
id|commit
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
r_char
id|base_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|top_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|4
op_logical_or
id|get_sha1_hex
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|top_sha1
)paren
op_logical_or
(paren
id|argc
op_eq
l_int|3
op_logical_and
id|get_sha1_hex
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|base_sha1
)paren
)paren
)paren
id|usage
c_func
(paren
l_string|&quot;git-export top [base]&quot;
)paren
suffix:semicolon
id|export
c_func
(paren
id|get_commit
c_func
(paren
id|top_sha1
)paren
comma
id|argc
op_eq
l_int|3
ques
c_cond
id|get_commit
c_func
(paren
id|base_sha1
)paren
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
