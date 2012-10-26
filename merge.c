macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;resolve-undo.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;dir.h&quot;
DECL|function|merge_argument
r_static
r_const
r_char
op_star
id|merge_argument
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_if
c_cond
(paren
id|commit
)paren
r_return
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_else
r_return
id|EMPTY_TREE_SHA1_HEX
suffix:semicolon
)brace
DECL|function|try_merge_command
r_int
id|try_merge_command
c_func
(paren
r_const
r_char
op_star
id|strategy
comma
r_int
id|xopts_nr
comma
r_const
r_char
op_star
op_star
id|xopts
comma
r_struct
id|commit_list
op_star
id|common
comma
r_const
r_char
op_star
id|head_arg
comma
r_struct
id|commit_list
op_star
id|remotes
)paren
(brace
r_const
r_char
op_star
op_star
id|args
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|x
op_assign
l_int|0
comma
id|ret
suffix:semicolon
r_struct
id|commit_list
op_star
id|j
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|args
op_assign
id|xmalloc
c_func
(paren
(paren
l_int|4
op_plus
id|xopts_nr
op_plus
id|commit_list_count
c_func
(paren
id|common
)paren
op_plus
id|commit_list_count
c_func
(paren
id|remotes
)paren
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;merge-%s&quot;
comma
id|strategy
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|buf.buf
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|xopts_nr
suffix:semicolon
id|x
op_increment
)paren
(brace
r_char
op_star
id|s
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|xopts
(braket
id|x
)braket
)paren
op_plus
l_int|2
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|s
comma
l_string|&quot;--&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|s
op_plus
l_int|2
comma
id|xopts
(braket
id|x
)braket
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|s
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
id|common
suffix:semicolon
id|j
suffix:semicolon
id|j
op_assign
id|j-&gt;next
)paren
id|args
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|merge_argument
c_func
(paren
id|j-&gt;item
)paren
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|head_arg
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|remotes
suffix:semicolon
id|j
suffix:semicolon
id|j
op_assign
id|j-&gt;next
)paren
id|args
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|merge_argument
c_func
(paren
id|j-&gt;item
)paren
)paren
suffix:semicolon
id|args
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
id|run_command_v_opt
c_func
(paren
id|args
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|xopts_nr
suffix:semicolon
id|x
op_increment
)paren
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|args
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|common
suffix:semicolon
id|j
suffix:semicolon
id|j
op_assign
id|j-&gt;next
)paren
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|args
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
id|i
op_add_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|remotes
suffix:semicolon
id|j
suffix:semicolon
id|j
op_assign
id|j-&gt;next
)paren
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|args
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|args
)paren
suffix:semicolon
id|discard_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;failed to read the cache&quot;
)paren
)paren
suffix:semicolon
id|resolve_undo_clear
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|checkout_fast_forward
r_int
id|checkout_fast_forward
c_func
(paren
r_const
r_int
r_char
op_star
id|head
comma
r_const
r_int
r_char
op_star
id|remote
comma
r_int
id|overwrite_ignore
)paren
(brace
r_struct
id|tree
op_star
id|trees
(braket
id|MAX_UNPACK_TREES
)braket
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
suffix:semicolon
r_struct
id|tree_desc
id|t
(braket
id|MAX_UNPACK_TREES
)braket
suffix:semicolon
r_int
id|i
comma
id|fd
comma
id|nr_trees
op_assign
l_int|0
suffix:semicolon
r_struct
id|dir_struct
id|dir
suffix:semicolon
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
id|refresh_cache
c_func
(paren
id|REFRESH_QUIET
)paren
suffix:semicolon
id|fd
op_assign
id|hold_locked_index
c_func
(paren
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|trees
comma
l_int|0
comma
r_sizeof
(paren
id|trees
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|t
comma
l_int|0
comma
r_sizeof
(paren
id|t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|overwrite_ignore
)paren
(brace
id|memset
c_func
(paren
op_amp
id|dir
comma
l_int|0
comma
r_sizeof
(paren
id|dir
)paren
)paren
suffix:semicolon
id|dir.flags
op_or_assign
id|DIR_SHOW_IGNORED
suffix:semicolon
id|setup_standard_excludes
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|opts.dir
op_assign
op_amp
id|dir
suffix:semicolon
)brace
id|opts.head_idx
op_assign
l_int|1
suffix:semicolon
id|opts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.dst_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.update
op_assign
l_int|1
suffix:semicolon
id|opts.verbose_update
op_assign
l_int|1
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|opts.fn
op_assign
id|twoway_merge
suffix:semicolon
id|setup_unpack_trees_porcelain
c_func
(paren
op_amp
id|opts
comma
l_string|&quot;merge&quot;
)paren
suffix:semicolon
id|trees
(braket
id|nr_trees
)braket
op_assign
id|parse_tree_indirect
c_func
(paren
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trees
(braket
id|nr_trees
op_increment
)braket
)paren
r_return
l_int|1
suffix:semicolon
id|trees
(braket
id|nr_trees
)braket
op_assign
id|parse_tree_indirect
c_func
(paren
id|remote
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trees
(braket
id|nr_trees
op_increment
)braket
)paren
r_return
l_int|1
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
id|nr_trees
suffix:semicolon
id|i
op_increment
)paren
(brace
id|parse_tree
c_func
(paren
id|trees
(braket
id|i
)braket
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
id|t
op_plus
id|i
comma
id|trees
(braket
id|i
)braket
op_member_access_from_pointer
id|buffer
comma
id|trees
(braket
id|i
)braket
op_member_access_from_pointer
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unpack_trees
c_func
(paren
id|nr_trees
comma
id|t
comma
op_amp
id|opts
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|fd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
id|lock_file
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
