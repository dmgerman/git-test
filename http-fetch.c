macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;http.h&quot;
macro_line|#include &quot;walker.h&quot;
DECL|variable|http_fetch_usage
r_static
r_const
r_char
id|http_fetch_usage
(braket
)braket
op_assign
l_string|&quot;git http-fetch &quot;
l_string|&quot;[-c] [-t] [-a] [-v] [--recover] [-w ref] [--stdin] commit-id url&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
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
id|walker
op_star
id|walker
suffix:semicolon
r_int
id|commits_on_stdin
op_assign
l_int|0
suffix:semicolon
r_int
id|commits
suffix:semicolon
r_const
r_char
op_star
op_star
id|write_ref
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
op_star
id|commit_id
suffix:semicolon
r_char
op_star
id|url
op_assign
l_int|NULL
suffix:semicolon
r_int
id|arg
op_assign
l_int|1
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|get_tree
op_assign
l_int|0
suffix:semicolon
r_int
id|get_history
op_assign
l_int|0
suffix:semicolon
r_int
id|get_all
op_assign
l_int|0
suffix:semicolon
r_int
id|get_verbosely
op_assign
l_int|0
suffix:semicolon
r_int
id|get_recover
op_assign
l_int|0
suffix:semicolon
id|git_extract_argv0_path
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|arg
OL
id|argc
op_logical_and
id|argv
(braket
id|arg
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;t&squot;
)paren
(brace
id|get_tree
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;c&squot;
)paren
(brace
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;a&squot;
)paren
(brace
id|get_all
op_assign
l_int|1
suffix:semicolon
id|get_tree
op_assign
l_int|1
suffix:semicolon
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;v&squot;
)paren
(brace
id|get_verbosely
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;w&squot;
)paren
(brace
id|write_ref
op_assign
op_amp
id|argv
(braket
id|arg
op_plus
l_int|1
)braket
suffix:semicolon
id|arg
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;h&squot;
)paren
(brace
id|usage
c_func
(paren
id|http_fetch_usage
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|arg
)braket
comma
l_string|&quot;--recover&quot;
)paren
)paren
(brace
id|get_recover
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|arg
)braket
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
id|commits_on_stdin
op_assign
l_int|1
suffix:semicolon
)brace
id|arg
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
id|arg
op_plus
l_int|2
id|commits_on_stdin
)paren
id|usage
c_func
(paren
id|http_fetch_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commits_on_stdin
)paren
(brace
id|commits
op_assign
id|walker_targets_stdin
c_func
(paren
op_amp
id|commit_id
comma
op_amp
id|write_ref
)paren
suffix:semicolon
)brace
r_else
(brace
id|commit_id
op_assign
(paren
r_char
op_star
op_star
)paren
op_amp
id|argv
(braket
id|arg
op_increment
)braket
suffix:semicolon
id|commits
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_all
op_eq
l_int|0
)paren
id|warning
c_func
(paren
l_string|&quot;http-fetch: use without -a is deprecated.&bslash;n&quot;
l_string|&quot;In a future release, -a will become the default.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
)paren
id|str_end_url_with_slash
c_func
(paren
id|argv
(braket
id|arg
)braket
comma
op_amp
id|url
)paren
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|http_init
c_func
(paren
l_int|NULL
comma
id|url
)paren
suffix:semicolon
id|walker
op_assign
id|get_http_walker
c_func
(paren
id|url
)paren
suffix:semicolon
id|walker-&gt;get_tree
op_assign
id|get_tree
suffix:semicolon
id|walker-&gt;get_history
op_assign
id|get_history
suffix:semicolon
id|walker-&gt;get_all
op_assign
id|get_all
suffix:semicolon
id|walker-&gt;get_verbosely
op_assign
id|get_verbosely
suffix:semicolon
id|walker-&gt;get_recover
op_assign
id|get_recover
suffix:semicolon
id|rc
op_assign
id|walker_fetch
c_func
(paren
id|walker
comma
id|commits
comma
id|commit_id
comma
id|write_ref
comma
id|url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commits_on_stdin
)paren
id|walker_targets_free
c_func
(paren
id|commits
comma
id|commit_id
comma
id|write_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;corrupt_object_found
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Some loose object were found to be corrupt, but they might be just&bslash;n&quot;
l_string|&quot;a false &squot;404 Not Found&squot; error message sent with incorrect HTTP&bslash;n&quot;
l_string|&quot;status code.  Suggest running &squot;git fsck&squot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|walker_free
c_func
(paren
id|walker
)paren
suffix:semicolon
id|http_cleanup
c_func
(paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|url
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
