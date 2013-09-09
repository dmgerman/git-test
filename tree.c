macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
DECL|variable|tree_type
r_const
r_char
op_star
id|tree_type
op_assign
l_string|&quot;tree&quot;
suffix:semicolon
DECL|function|read_one_entry_opt
r_static
r_int
id|read_one_entry_opt
c_func
(paren
r_const
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
comma
r_int
id|opt
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
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
r_return
id|READ_TREE_RECURSIVE
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|baselen
op_plus
id|len
)paren
suffix:semicolon
id|ce
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|size
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|create_ce_flags
c_func
(paren
id|stage
)paren
suffix:semicolon
id|ce-&gt;ce_namelen
op_assign
id|baselen
op_plus
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
op_plus
id|baselen
comma
id|pathname
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
r_return
id|add_cache_entry
c_func
(paren
id|ce
comma
id|opt
)paren
suffix:semicolon
)brace
DECL|function|read_one_entry
r_static
r_int
id|read_one_entry
c_func
(paren
r_const
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
comma
r_void
op_star
id|context
)paren
(brace
r_return
id|read_one_entry_opt
c_func
(paren
id|sha1
comma
id|base
comma
id|baselen
comma
id|pathname
comma
id|mode
comma
id|stage
comma
id|ADD_CACHE_OK_TO_ADD
op_or
id|ADD_CACHE_SKIP_DFCHECK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is used when the caller knows there is no existing entries at&n; * the stage that will conflict with the entry being added.&n; */
DECL|function|read_one_entry_quick
r_static
r_int
id|read_one_entry_quick
c_func
(paren
r_const
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
comma
r_void
op_star
id|context
)paren
(brace
r_return
id|read_one_entry_opt
c_func
(paren
id|sha1
comma
id|base
comma
id|baselen
comma
id|pathname
comma
id|mode
comma
id|stage
comma
id|ADD_CACHE_JUST_APPEND
)paren
suffix:semicolon
)brace
DECL|function|read_tree_1
r_static
r_int
id|read_tree_1
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_struct
id|strbuf
op_star
id|base
comma
r_int
id|stage
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
comma
id|read_tree_fn_t
id|fn
comma
r_void
op_star
id|context
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|len
comma
id|oldlen
op_assign
id|base-&gt;len
suffix:semicolon
r_enum
id|interesting
id|retval
op_assign
id|entry_not_interesting
suffix:semicolon
r_if
c_cond
(paren
id|parse_tree
c_func
(paren
id|tree
)paren
)paren
r_return
l_int|1
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
id|retval
op_ne
id|all_entries_interesting
)paren
(brace
id|retval
op_assign
id|tree_entry_interesting
c_func
(paren
op_amp
id|entry
comma
id|base
comma
l_int|0
comma
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
id|all_entries_not_interesting
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
id|entry_not_interesting
)paren
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|fn
c_func
(paren
id|entry.sha1
comma
id|base-&gt;buf
comma
id|base-&gt;len
comma
id|entry.path
comma
id|entry.mode
comma
id|stage
comma
id|context
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_continue
suffix:semicolon
r_case
id|READ_TREE_RECURSIVE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|hashcpy
c_func
(paren
id|sha1
comma
id|entry.sha1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|entry.mode
)paren
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
id|commit
op_assign
id|lookup_commit
c_func
(paren
id|entry.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
id|die
c_func
(paren
l_string|&quot;Commit %s in submodule path %s%s not found&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry.sha1
)paren
comma
id|base-&gt;buf
comma
id|entry.path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Invalid commit %s in submodule path %s%s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry.sha1
)paren
comma
id|base-&gt;buf
comma
id|entry.path
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|sha1
comma
id|commit-&gt;tree-&gt;object.sha1
)paren
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
id|len
op_assign
id|tree_entry_len
c_func
(paren
op_amp
id|entry
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|base
comma
id|entry.path
comma
id|len
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|base
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|retval
op_assign
id|read_tree_1
c_func
(paren
id|lookup_tree
c_func
(paren
id|sha1
)paren
comma
id|base
comma
id|stage
comma
id|pathspec
comma
id|fn
comma
id|context
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|base
comma
id|oldlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_tree_recursive
r_int
id|read_tree_recursive
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_int
id|stage
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
comma
id|read_tree_fn_t
id|fn
comma
r_void
op_star
id|context
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|sb
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|ret
op_assign
id|read_tree_1
c_func
(paren
id|tree
comma
op_amp
id|sb
comma
id|stage
comma
id|pathspec
comma
id|fn
comma
id|context
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cmp_cache_name_compare
r_static
r_int
id|cmp_cache_name_compare
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_const
r_struct
id|cache_entry
op_star
id|ce1
comma
op_star
id|ce2
suffix:semicolon
id|ce1
op_assign
op_star
(paren
(paren
r_const
r_struct
id|cache_entry
op_star
op_star
)paren
id|a_
)paren
suffix:semicolon
id|ce2
op_assign
op_star
(paren
(paren
r_const
r_struct
id|cache_entry
op_star
op_star
)paren
id|b_
)paren
suffix:semicolon
r_return
id|cache_name_stage_compare
c_func
(paren
id|ce1-&gt;name
comma
id|ce1-&gt;ce_namelen
comma
id|ce_stage
c_func
(paren
id|ce1
)paren
comma
id|ce2-&gt;name
comma
id|ce2-&gt;ce_namelen
comma
id|ce_stage
c_func
(paren
id|ce2
)paren
)paren
suffix:semicolon
)brace
DECL|function|read_tree
r_int
id|read_tree
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_int
id|stage
comma
r_struct
id|pathspec
op_star
id|match
)paren
(brace
id|read_tree_fn_t
id|fn
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * Currently the only existing callers of this function all&n;&t; * call it with stage=1 and after making sure there is nothing&n;&t; * at that stage; we could always use read_one_entry_quick().&n;&t; *&n;&t; * But when we decide to straighten out git-read-tree not to&n;&t; * use unpack_trees() in some cases, this will probably start&n;&t; * to matter.&n;&t; */
multiline_comment|/*&n;&t; * See if we have cache entry at the stage.  If so,&n;&t; * do it the original slow way, otherwise, append and then&n;&t; * sort at the end.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|fn
op_logical_and
id|i
OL
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
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
op_eq
id|stage
)paren
id|fn
op_assign
id|read_one_entry
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
id|fn
op_assign
id|read_one_entry_quick
suffix:semicolon
id|err
op_assign
id|read_tree_recursive
c_func
(paren
id|tree
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|stage
comma
id|match
comma
id|fn
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn
op_eq
id|read_one_entry
op_logical_or
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * Sort the cache entry -- we need to nuke the cache tree, though.&n;&t; */
id|cache_tree_free
c_func
(paren
op_amp
id|active_cache_tree
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|active_cache
comma
id|active_nr
comma
r_sizeof
(paren
id|active_cache
(braket
l_int|0
)braket
)paren
comma
id|cmp_cache_name_compare
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lookup_tree
r_struct
id|tree
op_star
id|lookup_tree
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
id|object
op_star
id|obj
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
id|create_object
c_func
(paren
id|sha1
comma
id|OBJ_TREE
comma
id|alloc_tree_node
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;type
)paren
id|obj-&gt;type
op_assign
id|OBJ_TREE
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|OBJ_TREE
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Object %s is a %s, not a tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_typename
(paren
id|obj-&gt;type
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_struct
id|tree
op_star
)paren
id|obj
suffix:semicolon
)brace
DECL|function|parse_tree_buffer
r_int
id|parse_tree_buffer
c_func
(paren
r_struct
id|tree
op_star
id|item
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|item-&gt;object.parsed
)paren
r_return
l_int|0
suffix:semicolon
id|item-&gt;object.parsed
op_assign
l_int|1
suffix:semicolon
id|item-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|item-&gt;size
op_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_tree
r_int
id|parse_tree
c_func
(paren
r_struct
id|tree
op_star
id|item
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.parsed
)paren
r_return
l_int|0
suffix:semicolon
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|item-&gt;object.sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_TREE
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Object %s not a tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
r_return
id|parse_tree_buffer
c_func
(paren
id|item
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|parse_tree_indirect
r_struct
id|tree
op_star
id|parse_tree_indirect
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
id|object
op_star
id|obj
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
r_return
(paren
r_struct
id|tree
op_star
)paren
id|obj
suffix:semicolon
r_else
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_COMMIT
)paren
id|obj
op_assign
op_amp
(paren
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
)paren
op_member_access_from_pointer
id|tree-&gt;object
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
id|obj
op_assign
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
)paren
op_member_access_from_pointer
id|tagged
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;parsed
)paren
id|parse_object
c_func
(paren
id|obj-&gt;sha1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
