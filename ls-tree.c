multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|macro|LS_RECURSIVE
mdefine_line|#define LS_RECURSIVE 1
DECL|macro|LS_TREE_ONLY
mdefine_line|#define LS_TREE_ONLY 2
DECL|variable|ls_options
r_static
r_int
id|ls_options
op_assign
l_int|0
suffix:semicolon
DECL|variable|pathspec
r_const
r_char
op_star
op_star
id|pathspec
suffix:semicolon
DECL|variable|ls_tree_usage
r_static
r_const
r_char
id|ls_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-ls-tree [-d] [-r] [-z] &lt;tree-ish&gt; [path...]&quot;
suffix:semicolon
DECL|function|show_tree
r_static
r_int
id|show_tree
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
id|base
comma
r_int
id|baselen
comma
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
comma
r_int
id|stage
)paren
(brace
r_const
r_char
op_star
id|type
op_assign
l_string|&quot;blob&quot;
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_const
r_char
op_star
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|ls_options
op_amp
id|LS_RECURSIVE
)paren
r_return
id|READ_TREE_RECURSIVE
suffix:semicolon
id|s
op_assign
id|pathspec
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|spec
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_int
id|len
comma
id|speclen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spec
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|base
comma
id|spec
comma
id|baselen
)paren
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|spec
op_add_assign
id|baselen
suffix:semicolon
id|speclen
op_assign
id|strlen
c_func
(paren
id|spec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speclen
op_le
id|len
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|pathname
comma
id|spec
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_return
id|READ_TREE_RECURSIVE
suffix:semicolon
)brace
)brace
id|type
op_assign
l_string|&quot;tree&quot;
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%06o %s %s&bslash;t%.*s%s%c&quot;
comma
id|mode
comma
id|type
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|baselen
comma
id|base
comma
id|pathname
comma
id|line_termination
)paren
suffix:semicolon
r_return
l_int|0
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
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_const
r_char
op_star
id|prefix
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
op_logical_and
id|argv
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_switch
c_cond
(paren
id|argv
(braket
l_int|1
)braket
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;z&squot;
suffix:colon
id|line_termination
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;r&squot;
suffix:colon
id|ls_options
op_or_assign
id|LS_RECURSIVE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
id|ls_options
op_or_assign
id|LS_TREE_ONLY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
id|ls_tree_usage
)paren
suffix:semicolon
)brace
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
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
id|ls_tree_usage
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
id|sha1
)paren
OL
l_int|0
)paren
id|usage
c_func
(paren
id|ls_tree_usage
)paren
suffix:semicolon
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
op_plus
l_int|2
)paren
suffix:semicolon
id|buf
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
l_string|&quot;tree&quot;
comma
op_amp
id|size
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;not a tree object&quot;
)paren
suffix:semicolon
id|read_tree_recursive
c_func
(paren
id|buf
comma
id|size
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
comma
id|pathspec
comma
id|show_tree
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
