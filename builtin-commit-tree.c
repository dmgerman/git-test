multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;utf8.h&quot;
DECL|macro|BLOCKING
mdefine_line|#define BLOCKING (1ul &lt;&lt; 14)
multiline_comment|/*&n; * FIXME! Share the code with &quot;write-tree.c&quot;&n; */
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
r_enum
id|object_type
id|expect
)paren
(brace
r_enum
id|object_type
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
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
id|type
op_ne
id|expect
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
r_typename
(paren
id|expect
)paren
)paren
suffix:semicolon
)brace
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
suffix:semicolon
r_int
id|encoding_is_utf8
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
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
id|OBJ_TREE
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
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
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
id|get_sha1
c_func
(paren
id|b
comma
id|sha1
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
)brace
multiline_comment|/* Not having i18n.commitencoding is the same as having utf-8 */
id|encoding_is_utf8
op_assign
id|is_encoding_utf8
c_func
(paren
id|git_commit_encoding
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buffer
comma
l_int|8192
)paren
suffix:semicolon
multiline_comment|/* should avoid reallocs for the headers */
id|strbuf_addf
c_func
(paren
op_amp
id|buffer
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
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit_list
op_star
id|next
op_assign
id|parents-&gt;next
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buffer
comma
l_string|&quot;parent %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|parents-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|parents
)paren
suffix:semicolon
id|parents
op_assign
id|next
suffix:semicolon
)brace
multiline_comment|/* Person/date information */
id|strbuf_addf
c_func
(paren
op_amp
id|buffer
comma
l_string|&quot;author %s&bslash;n&quot;
comma
id|git_author_info
c_func
(paren
id|IDENT_ERROR_ON_NO_NAME
)paren
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buffer
comma
l_string|&quot;committer %s&bslash;n&quot;
comma
id|git_committer_info
c_func
(paren
id|IDENT_ERROR_ON_NO_NAME
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|encoding_is_utf8
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|buffer
comma
l_string|&quot;encoding %s&bslash;n&quot;
comma
id|git_commit_encoding
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buffer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
multiline_comment|/* And add the comment */
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
id|die
c_func
(paren
l_string|&quot;git-commit-tree: read returned %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
multiline_comment|/* And check the encoding */
r_if
c_cond
(paren
id|encoding_is_utf8
op_logical_and
op_logical_neg
id|is_utf8
c_func
(paren
id|buffer.buf
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
id|buffer.buf
comma
id|buffer.len
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
