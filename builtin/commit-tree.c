multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;gpg-interface.h&quot;
DECL|variable|commit_tree_usage
r_static
r_const
r_char
id|commit_tree_usage
(braket
)braket
op_assign
l_string|&quot;git commit-tree [(-p &lt;sha1&gt;)...] [-S&lt;signer&gt;] [-m &lt;message&gt;] [-F &lt;file&gt;] &lt;sha1&gt; &lt;changelog&quot;
suffix:semicolon
DECL|function|new_parent
r_static
r_void
id|new_parent
c_func
(paren
r_struct
id|commit
op_star
id|parent
comma
r_struct
id|commit_list
op_star
op_star
id|parents_p
)paren
(brace
r_int
r_char
op_star
id|sha1
op_assign
id|parent-&gt;object.sha1
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
op_star
id|parents_p
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|parents-&gt;item
op_eq
id|parent
)paren
(brace
id|error
c_func
(paren
l_string|&quot;duplicate parent %s ignored&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|parents_p
op_assign
op_amp
id|parents-&gt;next
suffix:semicolon
)brace
id|commit_list_insert
c_func
(paren
id|parent
comma
id|parents_p
)paren
suffix:semicolon
)brace
DECL|function|commit_tree_config
r_static
r_int
id|commit_tree_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_int
id|status
op_assign
id|git_gpg_config
c_func
(paren
id|var
comma
id|value
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
DECL|function|cmd_commit_tree
r_int
id|cmd_commit_tree
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
r_int
id|i
comma
id|got_tree
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|strbuf
id|buffer
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|sign_commit
op_assign
l_int|NULL
suffix:semicolon
id|git_config
c_func
(paren
id|commit_tree_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage
c_func
(paren
id|commit_tree_usage
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-p&quot;
)paren
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_le
op_increment
id|i
)paren
id|usage
c_func
(paren
id|commit_tree_usage
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
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|assert_sha1_type
c_func
(paren
id|sha1
comma
id|OBJ_COMMIT
)paren
suffix:semicolon
id|new_parent
c_func
(paren
id|lookup_commit
c_func
(paren
id|sha1
)paren
comma
op_amp
id|parents
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|arg
comma
l_string|&quot;-S&quot;
comma
l_int|2
)paren
)paren
(brace
id|sign_commit
op_assign
id|arg
op_plus
l_int|2
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
id|arg
comma
l_string|&quot;-m&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
op_le
op_increment
id|i
)paren
id|usage
c_func
(paren
id|commit_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer.len
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|buffer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buffer
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|strbuf_complete_line
c_func
(paren
op_amp
id|buffer
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
id|arg
comma
l_string|&quot;-F&quot;
)paren
)paren
(brace
r_int
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_le
op_increment
id|i
)paren
id|usage
c_func
(paren
id|commit_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer.len
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|buffer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-&quot;
)paren
)paren
id|fd
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|fd
op_assign
id|open
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;git commit-tree: failed to open &squot;%s&squot;&quot;
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
id|strbuf_read
c_func
(paren
op_amp
id|buffer
comma
id|fd
comma
l_int|0
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;git commit-tree: failed to read &squot;%s&squot;&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_logical_and
id|close
c_func
(paren
id|fd
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;git commit-tree: failed to close &squot;%s&squot;&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|strbuf_complete_line
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|tree_sha1
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
r_if
c_cond
(paren
id|got_tree
)paren
id|die
c_func
(paren
l_string|&quot;Cannot give more than one trees&quot;
)paren
suffix:semicolon
id|got_tree
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer.len
)paren
(brace
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|buffer
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;git commit-tree: failed to read&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|commit_tree
c_func
(paren
op_amp
id|buffer
comma
id|tree_sha1
comma
id|parents
comma
id|commit_sha1
comma
l_int|NULL
comma
id|sign_commit
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit_sha1
)paren
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
