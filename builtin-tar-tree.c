multiline_comment|/*&n; * Copyright (c) 2005, 2006 Rene Scharfe&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tar.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|tar_tree_usage
r_static
r_const
r_char
id|tar_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-tar-tree [--remote=&lt;repo&gt;] &lt;tree-ish&gt; [basedir]&bslash;n&quot;
l_string|&quot;*** Note that this command is now deprecated; use git-archive instead.&quot;
suffix:semicolon
DECL|function|cmd_tar_tree
r_int
id|cmd_tar_tree
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
multiline_comment|/*&n;&t; * git-tar-tree is now a wrapper around git-archive --format=tar&n;&t; *&n;&t; * $0 --remote=&lt;repo&gt; arg... ==&gt;&n;&t; *&t;git-archive --format=tar --remote=&lt;repo&gt; arg...&n;&t; * $0 tree-ish ==&gt;&n;&t; *&t;git-archive --format=tar tree-ish&n;&t; * $0 tree-ish basedir ==&gt;&n;&t; * &t;git-archive --format-tar --prefix=basedir tree-ish&n;&t; */
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
op_star
id|nargv
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|nargv
)paren
comma
id|argc
op_plus
l_int|2
)paren
suffix:semicolon
r_char
op_star
id|basedir_arg
suffix:semicolon
r_int
id|nargc
op_assign
l_int|0
suffix:semicolon
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
l_string|&quot;git-archive&quot;
suffix:semicolon
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
l_string|&quot;--format=tar&quot;
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_le
id|argc
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;--remote=&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
l_int|9
)paren
)paren
(brace
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_default
suffix:colon
id|usage
c_func
(paren
id|tar_tree_usage
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* base-path */
id|basedir_arg
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
op_plus
l_int|11
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|basedir_arg
comma
l_string|&quot;--prefix=%s/&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
id|basedir_arg
suffix:semicolon
multiline_comment|/* fallthru */
r_case
l_int|2
suffix:colon
multiline_comment|/* tree-ish */
id|nargv
(braket
id|nargc
op_increment
)braket
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|nargv
(braket
id|nargc
)braket
op_assign
l_int|NULL
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;*** git-tar-tree is now deprecated.&bslash;n&quot;
l_string|&quot;*** Running git-archive instead.&bslash;n***&quot;
)paren
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
id|nargc
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fputc
c_func
(paren
l_char|&squot; &squot;
comma
id|stderr
)paren
suffix:semicolon
id|sq_quote_print
c_func
(paren
id|stderr
comma
id|nargv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
r_return
id|cmd_archive
c_func
(paren
id|nargc
comma
id|nargv
comma
id|prefix
)paren
suffix:semicolon
)brace
multiline_comment|/* ustar header + extended global header content */
DECL|macro|RECORDSIZE
mdefine_line|#define RECORDSIZE&t;(512)
DECL|macro|HEADERSIZE
mdefine_line|#define HEADERSIZE (2 * RECORDSIZE)
DECL|function|cmd_get_tar_commit_id
r_int
id|cmd_get_tar_commit_id
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
r_char
id|buffer
(braket
id|HEADERSIZE
)braket
suffix:semicolon
r_struct
id|ustar_header
op_star
id|header
op_assign
(paren
r_struct
id|ustar_header
op_star
)paren
id|buffer
suffix:semicolon
r_char
op_star
id|content
op_assign
id|buffer
op_plus
id|RECORDSIZE
suffix:semicolon
id|ssize_t
id|n
suffix:semicolon
id|n
op_assign
id|read_in_full
c_func
(paren
l_int|0
comma
id|buffer
comma
id|HEADERSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|HEADERSIZE
)paren
id|die
c_func
(paren
l_string|&quot;git-get-tar-commit-id: read error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|header-&gt;typeflag
(braket
l_int|0
)braket
op_ne
l_char|&squot;g&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|content
comma
l_string|&quot;52 comment=&quot;
comma
l_int|11
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|n
op_assign
id|write_in_full
c_func
(paren
l_int|1
comma
id|content
op_plus
l_int|11
comma
l_int|41
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|41
)paren
id|die
c_func
(paren
l_string|&quot;git-get-tar-commit-id: write error&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
