multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;resolve-undo.h&quot;
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
DECL|variable|read_tree_usage
r_static
r_const
r_char
op_star
r_const
id|read_tree_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git read-tree [[-m [--trivial] [--aggressive] | --reset | --prefix=&lt;prefix&gt;] [-u [--exclude-per-directory=&lt;gitignore&gt;] | -i]]  [--index-output=&lt;file&gt;] &lt;tree-ish1&gt; [&lt;tree-ish2&gt; [&lt;tree-ish3&gt;]]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|index_output_cb
r_static
r_int
id|index_output_cb
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
id|set_alternate_index_output
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exclude_per_directory_cb
r_static
r_int
id|exclude_per_directory_cb
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|dir_struct
op_star
id|dir
suffix:semicolon
r_struct
id|unpack_trees_options
op_star
id|opts
suffix:semicolon
id|opts
op_assign
(paren
r_struct
id|unpack_trees_options
op_star
)paren
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;dir
)paren
id|die
c_func
(paren
l_string|&quot;more than one --exclude-per-directory given.&quot;
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
id|opts-&gt;dir
)paren
)paren
suffix:semicolon
id|dir-&gt;flags
op_or_assign
id|DIR_SHOW_IGNORED
suffix:semicolon
id|dir-&gt;exclude_per_dir
op_assign
id|arg
suffix:semicolon
id|opts-&gt;dir
op_assign
id|dir
suffix:semicolon
multiline_comment|/* We do not need to nor want to do read-directory&n;&t; * here; we are merely interested in reusing the&n;&t; * per directory ignore stack mechanism.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
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
r_int
id|prefix_set
op_assign
l_int|0
suffix:semicolon
r_const
r_struct
id|option
id|read_tree_options
(braket
)braket
op_assign
(brace
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;index-output&quot;
comma
l_int|NULL
comma
l_string|&quot;FILE&quot;
comma
l_string|&quot;write resulting index to &lt;FILE&gt;&quot;
comma
id|PARSE_OPT_NONEG
comma
id|index_output_cb
)brace
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|opts.verbose_update
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Merging&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;m&squot;
comma
l_int|NULL
comma
op_amp
id|opts.merge
comma
l_string|&quot;perform a merge in addition to a read&quot;
comma
l_int|1
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;trivial&quot;
comma
op_amp
id|opts.trivial_merges_only
comma
l_string|&quot;3-way merge if no file level merging required&quot;
comma
l_int|1
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;aggressive&quot;
comma
op_amp
id|opts.aggressive
comma
l_string|&quot;3-way merge in presence of adds and removes&quot;
comma
l_int|1
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;reset&quot;
comma
op_amp
id|opts.reset
comma
l_string|&quot;same as -m, but discard unmerged entries&quot;
comma
l_int|1
)paren
comma
(brace
id|OPTION_STRING
comma
l_int|0
comma
l_string|&quot;prefix&quot;
comma
op_amp
id|opts.prefix
comma
l_string|&quot;&lt;subdirectory&gt;/&quot;
comma
l_string|&quot;read the tree into the index under &lt;subdirectory&gt;/&quot;
comma
id|PARSE_OPT_NONEG
op_or
id|PARSE_OPT_LITERAL_ARGHELP
)brace
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;u&squot;
comma
l_int|NULL
comma
op_amp
id|opts.update
comma
l_string|&quot;update working tree with merge result&quot;
comma
l_int|1
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;exclude-per-directory&quot;
comma
op_amp
id|opts
comma
l_string|&quot;gitignore&quot;
comma
l_string|&quot;allow explicitly ignored files to be overwritten&quot;
comma
id|PARSE_OPT_NONEG
comma
id|exclude_per_directory_cb
)brace
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;i&squot;
comma
l_int|NULL
comma
op_amp
id|opts.index_only
comma
l_string|&quot;don&squot;t check the working tree after merging&quot;
comma
l_int|1
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
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
comma
l_int|NULL
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|unused_prefix
comma
id|read_tree_options
comma
id|read_tree_usage
comma
l_int|0
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
id|prefix_set
op_assign
id|opts.prefix
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|opts.merge
op_plus
id|opts.reset
op_plus
id|prefix_set
)paren
id|die
c_func
(paren
l_string|&quot;Which one? -m, --reset, or --prefix?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts.reset
op_logical_or
id|opts.merge
op_logical_or
id|opts.prefix
)paren
(brace
r_if
c_cond
(paren
id|read_cache_unmerged
c_func
(paren
)paren
op_logical_and
(paren
id|opts.prefix
op_logical_or
id|opts.merge
)paren
)paren
id|die
c_func
(paren
l_string|&quot;You need to resolve your current index first&quot;
)paren
suffix:semicolon
id|stage
op_assign
id|opts.merge
op_assign
l_int|1
suffix:semicolon
)brace
id|resolve_undo_clear
c_func
(paren
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
l_int|1
OL
id|opts.index_only
op_plus
id|opts.update
)paren
id|die
c_func
(paren
l_string|&quot;-u and -i at the same time makes no sense&quot;
)paren
suffix:semicolon
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
id|die
c_func
(paren
l_string|&quot;%s is meaningless without -m, --reset, or --prefix&quot;
comma
id|opts.update
ques
c_cond
l_string|&quot;-u&quot;
suffix:colon
l_string|&quot;-i&quot;
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
op_logical_and
op_logical_neg
id|opts.index_only
)paren
id|setup_work_tree
c_func
(paren
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
id|opts.initial_checkout
op_assign
id|is_cache_unborn
c_func
(paren
)paren
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
id|cache_tree_free
c_func
(paren
op_amp
id|active_cache_tree
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
multiline_comment|/*&n;&t; * When reading only one tree (either the most basic form,&n;&t; * &quot;-m ent&quot; or &quot;--reset ent&quot; form), we can obtain a fully&n;&t; * valid cache-tree because the index must match exactly&n;&t; * what came from the tree.&n;&t; *&n;&t; * The same holds true if we are switching between two trees&n;&t; * using read-tree -m A B.  The index must match B after that.&n;&t; */
r_if
c_cond
(paren
id|nr_trees
op_eq
l_int|1
op_logical_and
op_logical_neg
id|opts.prefix
)paren
id|prime_cache_tree
c_func
(paren
op_amp
id|active_cache_tree
comma
id|trees
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|nr_trees
op_eq
l_int|2
op_logical_and
id|opts.merge
)paren
id|prime_cache_tree
c_func
(paren
op_amp
id|active_cache_tree
comma
id|trees
(braket
l_int|1
)braket
)paren
suffix:semicolon
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
