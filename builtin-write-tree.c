multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|variable|write_tree_usage
r_static
r_const
r_char
id|write_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-write-tree [--missing-ok] [--prefix=&lt;prefix&gt;/]&quot;
suffix:semicolon
DECL|function|write_tree
r_int
id|write_tree
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
id|missing_ok
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|entries
comma
id|was_valid
comma
id|newfd
suffix:semicolon
multiline_comment|/* We can&squot;t free this memory, it becomes part of a linked list parsed atexit() */
r_struct
id|lock_file
op_star
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_lock_file_for_update
c_func
(paren
id|lock_file
comma
id|get_index_file
c_func
(paren
)paren
)paren
suffix:semicolon
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-write-tree: error reading cache&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|active_cache_tree
)paren
id|active_cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|was_valid
op_assign
id|cache_tree_fully_valid
c_func
(paren
id|active_cache_tree
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|was_valid
)paren
(brace
r_if
c_cond
(paren
id|cache_tree_update
c_func
(paren
id|active_cache_tree
comma
id|active_cache
comma
id|active_nr
comma
id|missing_ok
comma
l_int|0
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-write-tree: error building trees&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|newfd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_and
op_logical_neg
id|close
c_func
(paren
id|newfd
)paren
)paren
id|commit_lock_file
c_func
(paren
id|lock_file
)paren
suffix:semicolon
)brace
multiline_comment|/* Not being able to write is fine -- we are only interested&n;&t;&t; * in updating the cache-tree part, and if the next caller&n;&t;&t; * ends up using the old index with unupdated cache-tree part&n;&t;&t; * it misses the work we did here, but that is just a&n;&t;&t; * performance penalty and not a big deal.&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_struct
id|cache_tree
op_star
id|subtree
op_assign
id|cache_tree_find
c_func
(paren
id|active_cache_tree
comma
id|prefix
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sha1
comma
id|subtree-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|sha1
comma
id|active_cache_tree-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lock_file
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_write_tree
r_int
id|cmd_write_tree
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
r_char
op_star
op_star
id|envp
)paren
(brace
r_int
id|missing_ok
op_assign
l_int|0
comma
id|ret
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
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
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
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
l_string|&quot;--missing-ok&quot;
)paren
)paren
id|missing_ok
op_assign
l_int|1
suffix:semicolon
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
l_string|&quot;--prefix=&quot;
comma
l_int|9
)paren
)paren
id|prefix
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
r_else
id|die
c_func
(paren
id|write_tree_usage
)paren
suffix:semicolon
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
OG
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;too many options&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|write_tree
c_func
(paren
id|sha1
comma
id|missing_ok
comma
id|prefix
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
id|sha1
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
