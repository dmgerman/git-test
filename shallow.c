macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
DECL|variable|is_shallow
r_static
r_int
id|is_shallow
op_assign
l_int|1
suffix:semicolon
DECL|function|register_shallow
r_int
id|register_shallow
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit_graft
op_star
id|graft
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_graft
)paren
)paren
suffix:semicolon
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
id|hashcpy
c_func
(paren
id|graft-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|graft-&gt;nr_parent
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|commit
op_logical_and
id|commit-&gt;object.parsed
)paren
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
r_return
id|register_commit_graft
c_func
(paren
id|graft
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|is_repository_shallow
r_int
id|is_repository_shallow
c_func
(paren
r_void
)paren
(brace
id|FILE
op_star
id|fp
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_if
c_cond
(paren
id|is_shallow
op_ge
l_int|0
)paren
r_return
id|is_shallow
suffix:semicolon
id|fp
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;shallow&quot;
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
(brace
id|is_shallow
op_assign
l_int|0
suffix:semicolon
r_return
id|is_shallow
suffix:semicolon
)brace
id|is_shallow
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|fp
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
id|get_sha1_hex
c_func
(paren
id|buf
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;bad shallow line: %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|register_shallow
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
id|is_shallow
suffix:semicolon
)brace
DECL|function|get_shallow_commits
r_struct
id|commit_list
op_star
id|get_shallow_commits
c_func
(paren
r_struct
id|object_array
op_star
id|heads
comma
r_int
id|depth
comma
r_int
id|shallow_flag
comma
r_int
id|not_shallow_flag
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|cur_depth
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|object_array
id|stack
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|commit
op_logical_or
id|i
OL
id|heads-&gt;nr
op_logical_or
id|stack.nr
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|heads-&gt;nr
)paren
(brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|deref_tag
c_func
(paren
id|heads-&gt;objects
(braket
id|i
op_increment
)braket
dot
id|item
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.type
op_ne
id|OBJ_COMMIT
)paren
(brace
id|commit
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;util
)paren
id|commit-&gt;util
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|commit-&gt;util
op_assign
l_int|0
suffix:semicolon
id|cur_depth
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|stack.objects
(braket
op_decrement
id|stack.nr
)braket
dot
id|item
suffix:semicolon
id|cur_depth
op_assign
op_star
(paren
r_int
op_star
)paren
id|commit-&gt;util
suffix:semicolon
)brace
)brace
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|not_shallow_flag
suffix:semicolon
id|cur_depth
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|commit-&gt;parents
comma
id|commit
op_assign
l_int|NULL
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;item-&gt;util
)paren
(brace
r_int
op_star
id|pointer
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|p-&gt;item-&gt;util
op_assign
id|pointer
suffix:semicolon
op_star
id|pointer
op_assign
id|cur_depth
suffix:semicolon
)brace
r_else
(brace
r_int
op_star
id|pointer
op_assign
id|p-&gt;item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|cur_depth
op_ge
op_star
id|pointer
)paren
r_continue
suffix:semicolon
op_star
id|pointer
op_assign
id|cur_depth
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cur_depth
OL
id|depth
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;next
)paren
id|add_object_array
c_func
(paren
op_amp
id|p-&gt;item-&gt;object
comma
l_int|NULL
comma
op_amp
id|stack
)paren
suffix:semicolon
r_else
(brace
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
id|cur_depth
op_assign
op_star
(paren
r_int
op_star
)paren
id|commit-&gt;util
suffix:semicolon
)brace
)brace
r_else
(brace
id|commit_list_insert
c_func
(paren
id|p-&gt;item
comma
op_amp
id|result
)paren
suffix:semicolon
id|p-&gt;item-&gt;object.flags
op_or_assign
id|shallow_flag
suffix:semicolon
)brace
)brace
)brace
r_return
id|result
suffix:semicolon
)brace
eof
