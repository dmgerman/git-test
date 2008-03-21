multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|variable|nr_trees
r_static
r_int
id|nr_trees
suffix:semicolon
DECL|variable|trees
r_static
r_struct
id|tree
op_star
id|trees
(braket
id|MAX_UNPACK_TREES
)braket
suffix:semicolon
DECL|function|list_tree
r_static
r_int
id|list_tree
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_if
c_cond
(paren
id|nr_trees
op_ge
id|MAX_UNPACK_TREES
)paren
id|die
c_func
(paren
l_string|&quot;I cannot read more than %d trees&quot;
comma
id|MAX_UNPACK_TREES
)paren
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
r_return
l_int|1
suffix:semicolon
id|trees
(braket
id|nr_trees
op_increment
)braket
op_assign
id|tree
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_cache_unmerged
r_static
r_int
id|read_cache_unmerged
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|dst
suffix:semicolon
r_struct
id|cache_entry
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
id|dst
op_assign
id|active_cache
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|remove_name_hash
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|last-&gt;name
)paren
)paren
r_continue
suffix:semicolon
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|last
op_assign
id|ce
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|dst
op_increment
op_assign
id|ce
suffix:semicolon
)brace
id|active_nr
op_assign
id|dst
id|active_cache
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|last
suffix:semicolon
)brace
DECL|function|prime_cache_tree_rec
r_static
r_void
id|prime_cache_tree_rec
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_struct
id|tree
op_star
id|tree
)paren
(brace
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_int
id|cnt
suffix:semicolon
id|hashcpy
c_func
(paren
id|it-&gt;sha1
comma
id|tree-&gt;object.sha1
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|desc
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|tree_entry
c_func
(paren
op_amp
id|desc
comma
op_amp
id|entry
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|cnt
op_increment
suffix:semicolon
r_else
(brace
r_struct
id|cache_tree_sub
op_star
id|sub
suffix:semicolon
r_struct
id|tree
op_star
id|subtree
op_assign
id|lookup_tree
c_func
(paren
id|entry.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subtree-&gt;object.parsed
)paren
id|parse_tree
c_func
(paren
id|subtree
)paren
suffix:semicolon
id|sub
op_assign
id|cache_tree_sub
c_func
(paren
id|it
comma
id|entry.path
)paren
suffix:semicolon
id|sub-&gt;cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|prime_cache_tree_rec
c_func
(paren
id|sub-&gt;cache_tree
comma
id|subtree
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sub-&gt;cache_tree-&gt;entry_count
suffix:semicolon
)brace
)brace
id|it-&gt;entry_count
op_assign
id|cnt
suffix:semicolon
)brace
DECL|function|prime_cache_tree
r_static
r_void
id|prime_cache_tree
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nr_trees
)paren
r_return
suffix:semicolon
id|active_cache_tree
op_assign
id|cache_tree
c_func
(paren
)paren
suffix:semicolon
id|prime_cache_tree_rec
c_func
(paren
id|active_cache_tree
comma
id|trees
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|variable|read_tree_usage
r_static
r_const
r_char
id|read_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-read-tree (&lt;sha&gt; | [[-m [--trivial] [--aggressive] | --reset | --prefix=&lt;prefix&gt;] [-u | -i]] [--exclude-per-directory=&lt;gitignore&gt;] [--index-output=&lt;file&gt;] &lt;sha1&gt; [&lt;sha2&gt; [&lt;sha3&gt;]])&quot;
suffix:semicolon
DECL|variable|lock_file
r_static
r_struct
id|lock_file
id|lock_file
suffix:semicolon
DECL|function|cmd_read_tree
r_int
id|cmd_read_tree
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
id|unused_prefix
)paren
(brace
r_int
id|i
comma
id|newfd
comma
id|stage
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|tree_desc
id|t
(braket
id|MAX_UNPACK_TREES
)braket
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
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
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
op_amp
id|lock_file
comma
l_int|1
)paren
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
multiline_comment|/* &quot;-u&quot; means &quot;update&quot;, meaning that a merge will update&n;&t;&t; * the working tree.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-u&quot;
)paren
)paren
(brace
id|opts.update
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
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|opts.verbose_update
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* &quot;-i&quot; means &quot;index only&quot;, meaning that a merge will&n;&t;&t; * not even look at the working tree.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-i&quot;
)paren
)paren
(brace
id|opts.index_only
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--index-output=&quot;
)paren
)paren
(brace
id|set_alternate_index_output
c_func
(paren
id|arg
op_plus
l_int|15
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* &quot;--prefix=&lt;subdirectory&gt;/&quot; means keep the current index&n;&t;&t; *  entries and put the entries from the tree under the&n;&t;&t; * given subdirectory.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--prefix=&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|stage
op_logical_or
id|opts.merge
op_logical_or
id|opts.prefix
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
id|opts.prefix
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|stage
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|read_cache_unmerged
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you need to resolve your current index first&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* This differs from &quot;-m&quot; in that we&squot;ll silently ignore&n;&t;&t; * unmerged entries and overwrite working tree files that&n;&t;&t; * correspond to them.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--reset&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|stage
op_logical_or
id|opts.merge
op_logical_or
id|opts.prefix
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
id|opts.reset
op_assign
l_int|1
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|stage
op_assign
l_int|1
suffix:semicolon
id|read_cache_unmerged
c_func
(paren
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
l_string|&quot;--trivial&quot;
)paren
)paren
(brace
id|opts.trivial_merges_only
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
l_string|&quot;--aggressive&quot;
)paren
)paren
(brace
id|opts.aggressive
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* &quot;-m&quot; stands for &quot;merge&quot;, meaning we start in stage 1 */
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
id|stage
op_logical_or
id|opts.merge
op_logical_or
id|opts.prefix
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache_unmerged
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;you need to resolve your current index first&quot;
)paren
suffix:semicolon
id|stage
op_assign
l_int|1
suffix:semicolon
id|opts.merge
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exclude-per-directory=&quot;
)paren
)paren
(brace
r_struct
id|dir_struct
op_star
id|dir
suffix:semicolon
r_if
c_cond
(paren
id|opts.dir
)paren
id|die
c_func
(paren
l_string|&quot;more than one --exclude-per-directory are given.&quot;
)paren
suffix:semicolon
id|dir
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|opts.dir
)paren
)paren
suffix:semicolon
id|dir-&gt;show_ignored
op_assign
l_int|1
suffix:semicolon
id|dir-&gt;exclude_per_dir
op_assign
id|arg
op_plus
l_int|24
suffix:semicolon
id|opts.dir
op_assign
id|dir
suffix:semicolon
multiline_comment|/* We do not need to nor want to do read-directory&n;&t;&t;&t; * here; we are merely interested in reusing the&n;&t;&t;&t; * per directory ignore stack mechanism.&n;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
multiline_comment|/* using -u and -i at the same time makes no sense */
r_if
c_cond
(paren
l_int|1
OL
id|opts.index_only
op_plus
id|opts.update
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
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
id|list_tree
c_func
(paren
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;failed to unpack tree object %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|stage
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|opts.update
op_logical_or
id|opts.index_only
)paren
op_logical_and
op_logical_neg
id|opts.merge
)paren
id|usage
c_func
(paren
id|read_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|opts.dir
op_logical_and
op_logical_neg
id|opts.update
)paren
)paren
id|die
c_func
(paren
l_string|&quot;--exclude-per-directory is meaningless unless -u&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts.merge
)paren
(brace
r_if
c_cond
(paren
id|stage
OL
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;just how do you expect me to merge %d trees?&quot;
comma
id|stage
op_minus
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|stage
l_int|1
)paren
(brace
r_case
l_int|1
suffix:colon
id|opts.fn
op_assign
id|opts.prefix
ques
c_cond
id|bind_merge
suffix:colon
id|oneway_merge
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|opts.fn
op_assign
id|twoway_merge
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_default
suffix:colon
id|opts.fn
op_assign
id|threeway_merge
suffix:semicolon
id|cache_tree_free
c_func
(paren
op_amp
id|active_cache_tree
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stage
l_int|1
op_ge
l_int|3
)paren
id|opts.head_idx
op_assign
id|stage
l_int|2
suffix:semicolon
r_else
id|opts.head_idx
op_assign
l_int|1
suffix:semicolon
)brace
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
r_struct
id|tree
op_star
id|tree
op_assign
id|trees
(braket
id|i
)braket
suffix:semicolon
id|parse_tree
c_func
(paren
id|tree
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
id|t
op_plus
id|i
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
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
l_int|128
suffix:semicolon
multiline_comment|/*&n;&t; * When reading only one tree (either the most basic form,&n;&t; * &quot;-m ent&quot; or &quot;--reset ent&quot; form), we can obtain a fully&n;&t; * valid cache-tree because the index must match exactly&n;&t; * what came from the tree.&n;&t; */
r_if
c_cond
(paren
id|nr_trees
op_logical_and
op_logical_neg
id|opts.prefix
op_logical_and
(paren
op_logical_neg
id|opts.merge
op_logical_or
(paren
id|stage
op_eq
l_int|2
)paren
)paren
)paren
(brace
id|cache_tree_free
c_func
(paren
op_amp
id|active_cache_tree
)paren
suffix:semicolon
id|prime_cache_tree
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
op_amp
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
