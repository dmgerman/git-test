multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;utf8.h&quot;
DECL|macro|BLOCKING
mdefine_line|#define BLOCKING (1ul &lt;&lt; 14)
multiline_comment|/*&n; * FIXME! Share the code with &quot;write-tree.c&quot;&n; */
DECL|function|init_buffer
r_static
r_void
id|init_buffer
c_func
(paren
r_char
op_star
op_star
id|bufp
comma
r_int
r_int
op_star
id|sizep
)paren
(brace
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|BLOCKING
)paren
suffix:semicolon
op_star
id|sizep
op_assign
l_int|0
suffix:semicolon
op_star
id|bufp
op_assign
id|buf
suffix:semicolon
)brace
DECL|function|add_buffer
r_static
r_void
id|add_buffer
c_func
(paren
r_char
op_star
op_star
id|bufp
comma
r_int
r_int
op_star
id|sizep
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
id|one_line
(braket
l_int|2048
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
r_int
id|alloc
comma
id|size
comma
id|newsize
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|one_line
comma
r_sizeof
(paren
id|one_line
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|size
op_assign
op_star
id|sizep
suffix:semicolon
id|newsize
op_assign
id|size
op_plus
id|len
op_plus
l_int|1
suffix:semicolon
id|alloc
op_assign
(paren
id|size
op_plus
l_int|32767
)paren
op_amp
op_complement
l_int|32767
suffix:semicolon
id|buf
op_assign
op_star
id|bufp
suffix:semicolon
r_if
c_cond
(paren
id|newsize
OG
id|alloc
)paren
(brace
id|alloc
op_assign
(paren
id|newsize
op_plus
l_int|32767
)paren
op_amp
op_complement
l_int|32767
suffix:semicolon
id|buf
op_assign
id|xrealloc
c_func
(paren
id|buf
comma
id|alloc
)paren
suffix:semicolon
op_star
id|bufp
op_assign
id|buf
suffix:semicolon
)brace
op_star
id|sizep
op_assign
id|newsize
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|size
comma
id|one_line
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|check_valid
r_static
r_void
id|check_valid
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|expect
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sha1_object_info
c_func
(paren
id|sha1
comma
id|type
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a valid object&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expect
op_logical_and
id|strcmp
c_func
(paren
id|type
comma
id|expect
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s is not a valid &squot;%s&squot; object&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|expect
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Having more than two parents is not strange at all, and this is&n; * how multi-way merges are represented.&n; */
DECL|macro|MAXPARENT
mdefine_line|#define MAXPARENT (16)
DECL|variable|parent_sha1
r_static
r_int
r_char
id|parent_sha1
(braket
id|MAXPARENT
)braket
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|commit_tree_usage
r_static
r_const
r_char
id|commit_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-commit-tree &lt;sha1&gt; [-p &lt;sha1&gt;]* &lt; changelog&quot;
suffix:semicolon
DECL|function|new_parent
r_static
r_int
id|new_parent
c_func
(paren
r_int
id|idx
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|sha1
op_assign
id|parent_sha1
(braket
id|idx
)braket
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
id|idx
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|parent_sha1
(braket
id|i
)braket
comma
id|sha1
)paren
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
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|commit_utf8_warn
r_static
r_const
r_char
id|commit_utf8_warn
(braket
)braket
op_assign
l_string|&quot;Warning: commit message does not conform to UTF-8.&bslash;n&quot;
l_string|&quot;You may want to amend it after fixing the message, or set the config&bslash;n&quot;
l_string|&quot;variable i18n.commitencoding to the encoding your project uses.&bslash;n&quot;
suffix:semicolon
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
suffix:semicolon
r_int
id|parents
op_assign
l_int|0
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
r_char
id|comment
(braket
l_int|1000
)braket
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
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
l_int|1
)braket
comma
id|tree_sha1
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
id|check_valid
c_func
(paren
id|tree_sha1
comma
id|tree_type
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
r_const
r_char
op_star
id|a
comma
op_star
id|b
suffix:semicolon
id|a
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
id|b
op_assign
id|argv
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
op_logical_or
id|strcmp
c_func
(paren
id|a
comma
l_string|&quot;-p&quot;
)paren
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
id|parents
op_ge
id|MAXPARENT
)paren
id|die
c_func
(paren
l_string|&quot;Too many parents (%d max)&quot;
comma
id|MAXPARENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|b
comma
id|parent_sha1
(braket
id|parents
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|b
)paren
suffix:semicolon
id|check_valid
c_func
(paren
id|parent_sha1
(braket
id|parents
)braket
comma
id|commit_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_parent
c_func
(paren
id|parents
)paren
)paren
id|parents
op_increment
suffix:semicolon
)brace
id|init_buffer
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
)paren
suffix:semicolon
id|add_buffer
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
comma
l_string|&quot;tree %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tree_sha1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE! This ordering means that the same exact tree merged with a&n;&t; * different order of parents will be a _different_ changeset even&n;&t; * if everything else stays the same.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|parents
suffix:semicolon
id|i
op_increment
)paren
id|add_buffer
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
comma
l_string|&quot;parent %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|parent_sha1
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* Person/date information */
id|add_buffer
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
comma
l_string|&quot;author %s&bslash;n&quot;
comma
id|git_author_info
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|add_buffer
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
comma
l_string|&quot;committer %s&bslash;n&bslash;n&quot;
comma
id|git_committer_info
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* And add the comment */
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|comment
comma
r_sizeof
(paren
id|comment
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
id|add_buffer
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|size
comma
l_string|&quot;%s&quot;
comma
id|comment
)paren
suffix:semicolon
multiline_comment|/* And check the encoding */
id|buffer
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|git_commit_encoding
comma
l_string|&quot;utf-8&quot;
)paren
op_logical_and
op_logical_neg
id|is_utf8
c_func
(paren
id|buffer
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
id|commit_utf8_warn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_sha1_file
c_func
(paren
id|buffer
comma
id|size
comma
id|commit_type
comma
id|commit_sha1
)paren
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
id|commit_sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
eof
