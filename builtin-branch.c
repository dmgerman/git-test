multiline_comment|/*&n; * Builtin &quot;git branch&quot;&n; *&n; * Copyright (c) 2006 Kristian H&#xfffd;gsberg &lt;krh@redhat.com&gt;&n; * Based on git-branch.sh by Junio C Hamano.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|builtin_branch_usage
r_static
r_const
r_char
id|builtin_branch_usage
(braket
)braket
op_assign
l_string|&quot;git-branch (-d | -D) &lt;branchname&gt; | [-l] [-f] &lt;branchname&gt; [&lt;start-point&gt;] | [-r]&quot;
suffix:semicolon
DECL|variable|head
r_static
r_const
r_char
op_star
id|head
suffix:semicolon
DECL|variable|head_sha1
r_static
r_int
r_char
id|head_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|in_merge_bases
r_static
r_int
id|in_merge_bases
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|commit
op_star
id|rev1
comma
r_struct
id|commit
op_star
id|rev2
)paren
(brace
r_struct
id|commit_list
op_star
id|bases
comma
op_star
id|b
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|bases
op_assign
id|get_merge_bases
c_func
(paren
id|rev1
comma
id|rev2
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|b
op_assign
id|bases
suffix:semicolon
id|b
suffix:semicolon
id|b
op_assign
id|b-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|b-&gt;item-&gt;object.sha1
)paren
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|free_commit_list
c_func
(paren
id|bases
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|delete_branches
r_static
r_void
id|delete_branches
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
r_int
id|force
)paren
(brace
r_struct
id|commit
op_star
id|rev
comma
op_star
id|head_rev
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
id|name
suffix:semicolon
r_int
id|i
suffix:semicolon
id|head_rev
op_assign
id|lookup_commit_reference
c_func
(paren
id|head_sha1
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
id|argv
(braket
id|i
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Cannot delete the branch you are currently on.&quot;
)paren
suffix:semicolon
id|name
op_assign
id|xstrdup
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;refs/heads/%s&quot;
comma
id|argv
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|name
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Branch &squot;%s&squot; not found.&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|rev
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev
op_logical_or
op_logical_neg
id|head_rev
)paren
id|die
c_func
(paren
l_string|&quot;Couldn&squot;t look up commit objects.&quot;
)paren
suffix:semicolon
multiline_comment|/* This checks whether the merge bases of branch and&n;&t;&t; * HEAD contains branch -- which means that the HEAD&n;&t;&t; * contains everything in both.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|force
op_logical_and
op_logical_neg
id|in_merge_bases
c_func
(paren
id|sha1
comma
id|rev
comma
id|head_rev
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;The branch &squot;%s&squot; is not a strict subset of your current HEAD.&bslash;n&quot;
l_string|&quot;If you are sure you want to delete it, run &squot;git branch -D %s&squot;.&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;Error deleting branch &squot;%s&squot;&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;Deleted branch %s.&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
)brace
DECL|variable|ref_index
DECL|variable|ref_alloc
r_static
r_int
id|ref_index
comma
id|ref_alloc
suffix:semicolon
DECL|variable|ref_list
r_static
r_char
op_star
op_star
id|ref_list
suffix:semicolon
DECL|function|append_ref
r_static
r_int
id|append_ref
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
r_if
c_cond
(paren
id|ref_index
op_ge
id|ref_alloc
)paren
(brace
id|ref_alloc
op_assign
id|alloc_nr
c_func
(paren
id|ref_alloc
)paren
suffix:semicolon
id|ref_list
op_assign
id|xrealloc
c_func
(paren
id|ref_list
comma
id|ref_alloc
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
)brace
id|ref_list
(braket
id|ref_index
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ref_cmp
r_static
r_int
id|ref_cmp
c_func
(paren
r_const
r_void
op_star
id|r1
comma
r_const
r_void
op_star
id|r2
)paren
(brace
r_return
id|strcmp
c_func
(paren
op_star
(paren
r_char
op_star
op_star
)paren
id|r1
comma
op_star
(paren
r_char
op_star
op_star
)paren
id|r2
)paren
suffix:semicolon
)brace
DECL|function|print_ref_list
r_static
r_void
id|print_ref_list
c_func
(paren
r_int
id|remote_only
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|remote_only
)paren
id|for_each_remote_ref
c_func
(paren
id|append_ref
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|for_each_branch_ref
c_func
(paren
id|append_ref
comma
l_int|NULL
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|ref_list
comma
id|ref_index
comma
r_sizeof
(paren
r_char
op_star
)paren
comma
id|ref_cmp
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
id|ref_index
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ref_list
(braket
id|i
)braket
comma
id|head
)paren
)paren
id|c
op_assign
l_char|&squot;*&squot;
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%c %s&bslash;n&quot;
comma
id|c
comma
id|ref_list
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|create_branch
r_static
r_void
id|create_branch
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|start
comma
r_int
id|force
comma
r_int
id|reflog
)paren
(brace
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|ref
(braket
id|PATH_MAX
)braket
comma
id|msg
(braket
id|PATH_MAX
op_plus
l_int|20
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|ref
comma
r_sizeof
id|ref
comma
l_string|&quot;refs/heads/%s&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|ref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid branch name.&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resolve_ref
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
id|die
c_func
(paren
l_string|&quot;A branch named &squot;%s&squot; already exists.&quot;
comma
id|name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
id|name
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Cannot force update the current branch.&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|start
comma
id|sha1
)paren
op_logical_or
(paren
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid branch point: &squot;%s&squot;.&quot;
comma
id|start
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|sha1
comma
id|commit-&gt;object.sha1
)paren
suffix:semicolon
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
id|die
c_func
(paren
l_string|&quot;Failed to lock ref for update: %s.&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reflog
)paren
(brace
id|log_all_ref_updates
op_assign
l_int|1
suffix:semicolon
id|snprintf
c_func
(paren
id|msg
comma
r_sizeof
id|msg
comma
l_string|&quot;branch: Created from %s&quot;
comma
id|start
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|sha1
comma
id|msg
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Failed to write ref: %s.&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|cmd_branch
r_int
id|cmd_branch
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
r_delete
op_assign
l_int|0
comma
id|force_delete
op_assign
l_int|0
comma
id|force_create
op_assign
l_int|0
comma
id|remote_only
op_assign
l_int|0
suffix:semicolon
r_int
id|reflog
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
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
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
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
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
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
l_string|&quot;-d&quot;
)paren
)paren
(brace
r_delete
op_assign
l_int|1
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
l_string|&quot;-D&quot;
)paren
)paren
(brace
r_delete
op_assign
l_int|1
suffix:semicolon
id|force_delete
op_assign
l_int|1
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
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|force_create
op_assign
l_int|1
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
l_string|&quot;-r&quot;
)paren
)paren
(brace
id|remote_only
op_assign
l_int|1
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
l_string|&quot;-l&quot;
)paren
)paren
(brace
id|reflog
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|builtin_branch_usage
)paren
suffix:semicolon
)brace
id|head
op_assign
id|xstrdup
c_func
(paren
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
comma
l_int|0
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
id|die
c_func
(paren
l_string|&quot;Failed to resolve HEAD as a valid ref.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|head
comma
l_string|&quot;refs/heads/&quot;
comma
l_int|11
)paren
)paren
id|die
c_func
(paren
l_string|&quot;HEAD not found below refs/heads!&quot;
)paren
suffix:semicolon
id|head
op_add_assign
l_int|11
suffix:semicolon
r_if
c_cond
(paren
r_delete
)paren
id|delete_branches
c_func
(paren
id|argc
id|i
comma
id|argv
op_plus
id|i
comma
id|force_delete
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|print_ref_list
c_func
(paren
id|remote_only
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
id|argc
l_int|1
)paren
id|create_branch
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|head
comma
id|force_create
comma
id|reflog
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
op_eq
id|argc
l_int|2
)paren
id|create_branch
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|argv
(braket
id|i
op_plus
l_int|1
)braket
comma
id|force_create
comma
id|reflog
)paren
suffix:semicolon
r_else
id|usage
c_func
(paren
id|builtin_branch_usage
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
