multiline_comment|/*&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;string_pool.h&quot;
macro_line|#include &quot;repo_tree.h&quot;
macro_line|#include &quot;obj_pool.h&quot;
macro_line|#include &quot;fast_export.h&quot;
macro_line|#include &quot;trp.h&quot;
DECL|struct|repo_dirent
r_struct
id|repo_dirent
(brace
DECL|member|name_offset
r_uint32
id|name_offset
suffix:semicolon
DECL|member|children
r_struct
id|trp_node
id|children
suffix:semicolon
DECL|member|mode
r_uint32
id|mode
suffix:semicolon
DECL|member|content_offset
r_uint32
id|content_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|repo_dir
r_struct
id|repo_dir
(brace
DECL|member|entries
r_struct
id|trp_root
id|entries
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|repo_commit
r_struct
id|repo_commit
(brace
DECL|member|root_dir_offset
r_uint32
id|root_dir_offset
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Memory pools for commit, dir and dirent */
id|obj_pool_gen
c_func
(paren
id|commit
comma
r_struct
id|repo_commit
comma
l_int|4096
)paren
id|obj_pool_gen
c_func
(paren
id|dir
comma
r_struct
id|repo_dir
comma
l_int|4096
)paren
id|obj_pool_gen
c_func
(paren
id|dent
comma
r_struct
id|repo_dirent
comma
l_int|4096
)paren
DECL|variable|active_commit
r_static
r_uint32
id|active_commit
suffix:semicolon
DECL|variable|mark
r_static
r_uint32
id|mark
suffix:semicolon
r_static
r_int
id|repo_dirent_name_cmp
c_func
(paren
r_const
r_void
op_star
id|a
comma
r_const
r_void
op_star
id|b
)paren
suffix:semicolon
multiline_comment|/* Treap for directory entries */
id|trp_gen
c_func
(paren
r_static
comma
id|dent_
comma
r_struct
id|repo_dirent
comma
id|children
comma
id|dent
comma
id|repo_dirent_name_cmp
)paren
suffix:semicolon
DECL|function|next_blob_mark
r_uint32
id|next_blob_mark
c_func
(paren
r_void
)paren
(brace
r_return
id|mark
op_increment
suffix:semicolon
)brace
DECL|function|repo_commit_root_dir
r_static
r_struct
id|repo_dir
op_star
id|repo_commit_root_dir
c_func
(paren
r_struct
id|repo_commit
op_star
id|commit
)paren
(brace
r_return
id|dir_pointer
c_func
(paren
id|commit-&gt;root_dir_offset
)paren
suffix:semicolon
)brace
DECL|function|repo_first_dirent
r_static
r_struct
id|repo_dirent
op_star
id|repo_first_dirent
c_func
(paren
r_struct
id|repo_dir
op_star
id|dir
)paren
(brace
r_return
id|dent_first
c_func
(paren
op_amp
id|dir-&gt;entries
)paren
suffix:semicolon
)brace
DECL|function|repo_dirent_name_cmp
r_static
r_int
id|repo_dirent_name_cmp
c_func
(paren
r_const
r_void
op_star
id|a
comma
r_const
r_void
op_star
id|b
)paren
(brace
r_const
r_struct
id|repo_dirent
op_star
id|dent1
op_assign
id|a
comma
op_star
id|dent2
op_assign
id|b
suffix:semicolon
r_uint32
id|a_offset
op_assign
id|dent1-&gt;name_offset
suffix:semicolon
r_uint32
id|b_offset
op_assign
id|dent2-&gt;name_offset
suffix:semicolon
r_return
(paren
id|a_offset
OG
id|b_offset
)paren
(paren
id|a_offset
OL
id|b_offset
)paren
suffix:semicolon
)brace
DECL|function|repo_dirent_is_dir
r_static
r_int
id|repo_dirent_is_dir
c_func
(paren
r_struct
id|repo_dirent
op_star
id|dent
)paren
(brace
r_return
id|dent
op_ne
l_int|NULL
op_logical_and
id|dent-&gt;mode
op_eq
id|REPO_MODE_DIR
suffix:semicolon
)brace
DECL|function|repo_dir_from_dirent
r_static
r_struct
id|repo_dir
op_star
id|repo_dir_from_dirent
c_func
(paren
r_struct
id|repo_dirent
op_star
id|dent
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|repo_dirent_is_dir
c_func
(paren
id|dent
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|dir_pointer
c_func
(paren
id|dent-&gt;content_offset
)paren
suffix:semicolon
)brace
DECL|function|repo_clone_dir
r_static
r_struct
id|repo_dir
op_star
id|repo_clone_dir
c_func
(paren
r_struct
id|repo_dir
op_star
id|orig_dir
)paren
(brace
r_uint32
id|orig_o
comma
id|new_o
suffix:semicolon
id|orig_o
op_assign
id|dir_offset
c_func
(paren
id|orig_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|orig_o
op_ge
id|dir_pool.committed
)paren
r_return
id|orig_dir
suffix:semicolon
id|new_o
op_assign
id|dir_alloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|orig_dir
op_assign
id|dir_pointer
c_func
(paren
id|orig_o
)paren
suffix:semicolon
op_star
id|dir_pointer
c_func
(paren
id|new_o
)paren
op_assign
op_star
id|orig_dir
suffix:semicolon
r_return
id|dir_pointer
c_func
(paren
id|new_o
)paren
suffix:semicolon
)brace
DECL|function|repo_read_dirent
r_static
r_struct
id|repo_dirent
op_star
id|repo_read_dirent
c_func
(paren
r_uint32
id|revision
comma
r_uint32
op_star
id|path
)paren
(brace
r_uint32
id|name
op_assign
l_int|0
suffix:semicolon
r_struct
id|repo_dirent
op_star
id|key
op_assign
id|dent_pointer
c_func
(paren
id|dent_alloc
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
r_struct
id|repo_dir
op_star
id|dir
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|repo_dirent
op_star
id|dent
op_assign
l_int|NULL
suffix:semicolon
id|dir
op_assign
id|repo_commit_root_dir
c_func
(paren
id|commit_pointer
c_func
(paren
id|revision
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_complement
(paren
id|name
op_assign
op_star
id|path
op_increment
)paren
)paren
(brace
id|key-&gt;name_offset
op_assign
id|name
suffix:semicolon
id|dent
op_assign
id|dent_search
c_func
(paren
op_amp
id|dir-&gt;entries
comma
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dent
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|repo_dirent_is_dir
c_func
(paren
id|dent
)paren
)paren
r_break
suffix:semicolon
id|dir
op_assign
id|repo_dir_from_dirent
c_func
(paren
id|dent
)paren
suffix:semicolon
)brace
id|dent_free
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|dent
suffix:semicolon
)brace
DECL|function|repo_write_dirent
r_static
r_void
id|repo_write_dirent
c_func
(paren
r_uint32
op_star
id|path
comma
r_uint32
id|mode
comma
r_uint32
id|content_offset
comma
r_uint32
id|del
)paren
(brace
r_uint32
id|name
comma
id|revision
comma
id|dir_o
op_assign
op_complement
l_int|0
comma
id|parent_dir_o
op_assign
op_complement
l_int|0
suffix:semicolon
r_struct
id|repo_dir
op_star
id|dir
suffix:semicolon
r_struct
id|repo_dirent
op_star
id|key
suffix:semicolon
r_struct
id|repo_dirent
op_star
id|dent
op_assign
l_int|NULL
suffix:semicolon
id|revision
op_assign
id|active_commit
suffix:semicolon
id|dir
op_assign
id|repo_commit_root_dir
c_func
(paren
id|commit_pointer
c_func
(paren
id|revision
)paren
)paren
suffix:semicolon
id|dir
op_assign
id|repo_clone_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|commit_pointer
c_func
(paren
id|revision
)paren
op_member_access_from_pointer
id|root_dir_offset
op_assign
id|dir_offset
c_func
(paren
id|dir
)paren
suffix:semicolon
r_while
c_loop
(paren
op_complement
(paren
id|name
op_assign
op_star
id|path
op_increment
)paren
)paren
(brace
id|parent_dir_o
op_assign
id|dir_offset
c_func
(paren
id|dir
)paren
suffix:semicolon
id|key
op_assign
id|dent_pointer
c_func
(paren
id|dent_alloc
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|key-&gt;name_offset
op_assign
id|name
suffix:semicolon
id|dent
op_assign
id|dent_search
c_func
(paren
op_amp
id|dir-&gt;entries
comma
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dent
op_eq
l_int|NULL
)paren
id|dent
op_assign
id|key
suffix:semicolon
r_else
id|dent_free
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dent
op_eq
id|key
)paren
(brace
id|dent-&gt;mode
op_assign
id|REPO_MODE_DIR
suffix:semicolon
id|dent-&gt;content_offset
op_assign
l_int|0
suffix:semicolon
id|dent_insert
c_func
(paren
op_amp
id|dir-&gt;entries
comma
id|dent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dent_offset
c_func
(paren
id|dent
)paren
OL
id|dent_pool.committed
)paren
(brace
id|dir_o
op_assign
id|repo_dirent_is_dir
c_func
(paren
id|dent
)paren
ques
c_cond
id|dent-&gt;content_offset
suffix:colon
op_complement
l_int|0
suffix:semicolon
id|dent_remove
c_func
(paren
op_amp
id|dir-&gt;entries
comma
id|dent
)paren
suffix:semicolon
id|dent
op_assign
id|dent_pointer
c_func
(paren
id|dent_alloc
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|dent-&gt;name_offset
op_assign
id|name
suffix:semicolon
id|dent-&gt;mode
op_assign
id|REPO_MODE_DIR
suffix:semicolon
id|dent-&gt;content_offset
op_assign
id|dir_o
suffix:semicolon
id|dent_insert
c_func
(paren
op_amp
id|dir-&gt;entries
comma
id|dent
)paren
suffix:semicolon
)brace
id|dir
op_assign
id|repo_dir_from_dirent
c_func
(paren
id|dent
)paren
suffix:semicolon
id|dir
op_assign
id|repo_clone_dir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|dent-&gt;content_offset
op_assign
id|dir_offset
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dent
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|dent-&gt;mode
op_assign
id|mode
suffix:semicolon
id|dent-&gt;content_offset
op_assign
id|content_offset
suffix:semicolon
r_if
c_cond
(paren
id|del
op_logical_and
op_complement
id|parent_dir_o
)paren
id|dent_remove
c_func
(paren
op_amp
id|dir_pointer
c_func
(paren
id|parent_dir_o
)paren
op_member_access_from_pointer
id|entries
comma
id|dent
)paren
suffix:semicolon
)brace
DECL|function|repo_copy
r_uint32
id|repo_copy
c_func
(paren
r_uint32
id|revision
comma
r_uint32
op_star
id|src
comma
r_uint32
op_star
id|dst
)paren
(brace
r_uint32
id|mode
op_assign
l_int|0
comma
id|content_offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|repo_dirent
op_star
id|src_dent
suffix:semicolon
id|src_dent
op_assign
id|repo_read_dirent
c_func
(paren
id|revision
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src_dent
op_ne
l_int|NULL
)paren
(brace
id|mode
op_assign
id|src_dent-&gt;mode
suffix:semicolon
id|content_offset
op_assign
id|src_dent-&gt;content_offset
suffix:semicolon
id|repo_write_dirent
c_func
(paren
id|dst
comma
id|mode
comma
id|content_offset
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|mode
suffix:semicolon
)brace
DECL|function|repo_add
r_void
id|repo_add
c_func
(paren
r_uint32
op_star
id|path
comma
r_uint32
id|mode
comma
r_uint32
id|blob_mark
)paren
(brace
id|repo_write_dirent
c_func
(paren
id|path
comma
id|mode
comma
id|blob_mark
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|repo_modify_path
r_uint32
id|repo_modify_path
c_func
(paren
r_uint32
op_star
id|path
comma
r_uint32
id|mode
comma
r_uint32
id|blob_mark
)paren
(brace
r_struct
id|repo_dirent
op_star
id|src_dent
suffix:semicolon
id|src_dent
op_assign
id|repo_read_dirent
c_func
(paren
id|active_commit
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|src_dent
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blob_mark
)paren
id|blob_mark
op_assign
id|src_dent-&gt;content_offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mode
)paren
id|mode
op_assign
id|src_dent-&gt;mode
suffix:semicolon
id|repo_write_dirent
c_func
(paren
id|path
comma
id|mode
comma
id|blob_mark
comma
l_int|0
)paren
suffix:semicolon
r_return
id|mode
suffix:semicolon
)brace
DECL|function|repo_delete
r_void
id|repo_delete
c_func
(paren
r_uint32
op_star
id|path
)paren
(brace
id|repo_write_dirent
c_func
(paren
id|path
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
id|repo_git_add_r
c_func
(paren
r_uint32
id|depth
comma
r_uint32
op_star
id|path
comma
r_struct
id|repo_dir
op_star
id|dir
)paren
suffix:semicolon
DECL|function|repo_git_add
r_static
r_void
id|repo_git_add
c_func
(paren
r_uint32
id|depth
comma
r_uint32
op_star
id|path
comma
r_struct
id|repo_dirent
op_star
id|dent
)paren
(brace
r_if
c_cond
(paren
id|repo_dirent_is_dir
c_func
(paren
id|dent
)paren
)paren
id|repo_git_add_r
c_func
(paren
id|depth
comma
id|path
comma
id|repo_dir_from_dirent
c_func
(paren
id|dent
)paren
)paren
suffix:semicolon
r_else
id|fast_export_modify
c_func
(paren
id|depth
comma
id|path
comma
id|dent-&gt;mode
comma
id|dent-&gt;content_offset
)paren
suffix:semicolon
)brace
DECL|function|repo_git_add_r
r_static
r_void
id|repo_git_add_r
c_func
(paren
r_uint32
id|depth
comma
r_uint32
op_star
id|path
comma
r_struct
id|repo_dir
op_star
id|dir
)paren
(brace
r_struct
id|repo_dirent
op_star
id|de
op_assign
id|repo_first_dirent
c_func
(paren
id|dir
)paren
suffix:semicolon
r_while
c_loop
(paren
id|de
)paren
(brace
id|path
(braket
id|depth
)braket
op_assign
id|de-&gt;name_offset
suffix:semicolon
id|repo_git_add
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
comma
id|de
)paren
suffix:semicolon
id|de
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir-&gt;entries
comma
id|de
)paren
suffix:semicolon
)brace
)brace
DECL|function|repo_diff_r
r_static
r_void
id|repo_diff_r
c_func
(paren
r_uint32
id|depth
comma
r_uint32
op_star
id|path
comma
r_struct
id|repo_dir
op_star
id|dir1
comma
r_struct
id|repo_dir
op_star
id|dir2
)paren
(brace
r_struct
id|repo_dirent
op_star
id|de1
comma
op_star
id|de2
suffix:semicolon
id|de1
op_assign
id|repo_first_dirent
c_func
(paren
id|dir1
)paren
suffix:semicolon
id|de2
op_assign
id|repo_first_dirent
c_func
(paren
id|dir2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|de1
op_logical_and
id|de2
)paren
(brace
r_if
c_cond
(paren
id|de1-&gt;name_offset
OL
id|de2-&gt;name_offset
)paren
(brace
id|path
(braket
id|depth
)braket
op_assign
id|de1-&gt;name_offset
suffix:semicolon
id|fast_export_delete
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
)paren
suffix:semicolon
id|de1
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir1-&gt;entries
comma
id|de1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de1-&gt;name_offset
OG
id|de2-&gt;name_offset
)paren
(brace
id|path
(braket
id|depth
)braket
op_assign
id|de2-&gt;name_offset
suffix:semicolon
id|repo_git_add
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
comma
id|de2
)paren
suffix:semicolon
id|de2
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir2-&gt;entries
comma
id|de2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|path
(braket
id|depth
)braket
op_assign
id|de1-&gt;name_offset
suffix:semicolon
r_if
c_cond
(paren
id|de1-&gt;mode
op_eq
id|de2-&gt;mode
op_logical_and
id|de1-&gt;content_offset
op_eq
id|de2-&gt;content_offset
)paren
(brace
suffix:semicolon
multiline_comment|/* No change. */
)brace
r_else
r_if
c_cond
(paren
id|repo_dirent_is_dir
c_func
(paren
id|de1
)paren
op_logical_and
id|repo_dirent_is_dir
c_func
(paren
id|de2
)paren
)paren
(brace
id|repo_diff_r
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
comma
id|repo_dir_from_dirent
c_func
(paren
id|de1
)paren
comma
id|repo_dir_from_dirent
c_func
(paren
id|de2
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|repo_dirent_is_dir
c_func
(paren
id|de1
)paren
op_logical_and
op_logical_neg
id|repo_dirent_is_dir
c_func
(paren
id|de2
)paren
)paren
(brace
id|repo_git_add
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
comma
id|de2
)paren
suffix:semicolon
)brace
r_else
(brace
id|fast_export_delete
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
)paren
suffix:semicolon
id|repo_git_add
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
comma
id|de2
)paren
suffix:semicolon
)brace
id|de1
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir1-&gt;entries
comma
id|de1
)paren
suffix:semicolon
id|de2
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir2-&gt;entries
comma
id|de2
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|de1
)paren
(brace
id|path
(braket
id|depth
)braket
op_assign
id|de1-&gt;name_offset
suffix:semicolon
id|fast_export_delete
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
)paren
suffix:semicolon
id|de1
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir1-&gt;entries
comma
id|de1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|de2
)paren
(brace
id|path
(braket
id|depth
)braket
op_assign
id|de2-&gt;name_offset
suffix:semicolon
id|repo_git_add
c_func
(paren
id|depth
op_plus
l_int|1
comma
id|path
comma
id|de2
)paren
suffix:semicolon
id|de2
op_assign
id|dent_next
c_func
(paren
op_amp
id|dir2-&gt;entries
comma
id|de2
)paren
suffix:semicolon
)brace
)brace
DECL|variable|path_stack
r_static
r_uint32
id|path_stack
(braket
id|REPO_MAX_PATH_DEPTH
)braket
suffix:semicolon
DECL|function|repo_diff
r_void
id|repo_diff
c_func
(paren
r_uint32
id|r1
comma
r_uint32
id|r2
)paren
(brace
id|repo_diff_r
c_func
(paren
l_int|0
comma
id|path_stack
comma
id|repo_commit_root_dir
c_func
(paren
id|commit_pointer
c_func
(paren
id|r1
)paren
)paren
comma
id|repo_commit_root_dir
c_func
(paren
id|commit_pointer
c_func
(paren
id|r2
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|repo_commit
r_void
id|repo_commit
c_func
(paren
r_uint32
id|revision
comma
r_uint32
id|author
comma
r_char
op_star
id|log
comma
r_uint32
id|uuid
comma
r_uint32
id|url
comma
r_int
r_int
id|timestamp
)paren
(brace
id|fast_export_commit
c_func
(paren
id|revision
comma
id|author
comma
id|log
comma
id|uuid
comma
id|url
comma
id|timestamp
)paren
suffix:semicolon
id|dent_commit
c_func
(paren
)paren
suffix:semicolon
id|dir_commit
c_func
(paren
)paren
suffix:semicolon
id|active_commit
op_assign
id|commit_alloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|commit_pointer
c_func
(paren
id|active_commit
)paren
op_member_access_from_pointer
id|root_dir_offset
op_assign
id|commit_pointer
c_func
(paren
id|active_commit
l_int|1
)paren
op_member_access_from_pointer
id|root_dir_offset
suffix:semicolon
)brace
DECL|function|mark_init
r_static
r_void
id|mark_init
c_func
(paren
r_void
)paren
(brace
r_uint32
id|i
suffix:semicolon
id|mark
op_assign
l_int|0
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
id|dent_pool.size
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|repo_dirent_is_dir
c_func
(paren
id|dent_pointer
c_func
(paren
id|i
)paren
)paren
op_logical_and
id|dent_pointer
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|content_offset
OG
id|mark
)paren
id|mark
op_assign
id|dent_pointer
c_func
(paren
id|i
)paren
op_member_access_from_pointer
id|content_offset
suffix:semicolon
id|mark
op_increment
suffix:semicolon
)brace
DECL|function|repo_init
r_void
id|repo_init
c_func
(paren
r_void
)paren
(brace
id|mark_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_pool.size
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Create empty tree for commit 0. */
id|commit_alloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|commit_pointer
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|root_dir_offset
op_assign
id|dir_alloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|dir_pointer
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|entries.trp_root
op_assign
op_complement
l_int|0
suffix:semicolon
id|dir_commit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Preallocate next commit, ready for changes. */
id|active_commit
op_assign
id|commit_alloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|commit_pointer
c_func
(paren
id|active_commit
)paren
op_member_access_from_pointer
id|root_dir_offset
op_assign
id|commit_pointer
c_func
(paren
id|active_commit
l_int|1
)paren
op_member_access_from_pointer
id|root_dir_offset
suffix:semicolon
)brace
DECL|function|repo_reset
r_void
id|repo_reset
c_func
(paren
r_void
)paren
(brace
id|pool_reset
c_func
(paren
)paren
suffix:semicolon
id|commit_reset
c_func
(paren
)paren
suffix:semicolon
id|dir_reset
c_func
(paren
)paren
suffix:semicolon
id|dent_reset
c_func
(paren
)paren
suffix:semicolon
)brace
eof
