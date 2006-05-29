macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &lt;stdlib.h&gt;
DECL|variable|tree_type
r_const
r_char
op_star
id|tree_type
op_assign
l_string|&quot;tree&quot;
suffix:semicolon
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
id|baselen
op_plus
id|len
comma
id|stage
)paren
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
id|memcpy
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
id|add_cache_entry
c_func
(paren
id|ce
comma
id|ADD_CACHE_OK_TO_ADD
op_or
id|ADD_CACHE_SKIP_DFCHECK
)paren
suffix:semicolon
)brace
DECL|function|match_tree_entry
r_static
r_int
id|match_tree_entry
c_func
(paren
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
id|path
comma
r_int
r_int
id|mode
comma
r_const
r_char
op_star
op_star
id|paths
)paren
(brace
r_const
r_char
op_star
id|match
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|paths
)paren
r_return
l_int|1
suffix:semicolon
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|match
op_assign
op_star
id|paths
op_increment
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|matchlen
op_assign
id|strlen
c_func
(paren
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baselen
op_ge
id|matchlen
)paren
(brace
multiline_comment|/* If it doesn&squot;t match, move along... */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|base
comma
id|match
comma
id|matchlen
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* The base is a subdirectory of a path which was specified. */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Does the base match? */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|base
comma
id|match
comma
id|baselen
)paren
)paren
r_continue
suffix:semicolon
id|match
op_add_assign
id|baselen
suffix:semicolon
id|matchlen
op_sub_assign
id|baselen
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OG
id|matchlen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|matchlen
OG
id|pathlen
)paren
(brace
r_if
c_cond
(paren
id|match
(braket
id|pathlen
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|path
comma
id|match
comma
id|pathlen
)paren
)paren
r_continue
suffix:semicolon
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
r_char
op_star
op_star
id|match
comma
id|read_tree_fn_t
id|fn
)paren
(brace
r_struct
id|tree_desc
id|desc
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
id|desc.buf
op_assign
id|tree-&gt;buffer
suffix:semicolon
id|desc.size
op_assign
id|tree-&gt;size
suffix:semicolon
r_while
c_loop
(paren
id|desc.size
)paren
(brace
r_int
id|mode
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|desc
comma
op_amp
id|name
comma
op_amp
id|mode
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|desc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match_tree_entry
c_func
(paren
id|base
comma
id|baselen
comma
id|name
comma
id|mode
comma
id|match
)paren
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|fn
c_func
(paren
id|sha1
comma
id|base
comma
id|baselen
comma
id|name
comma
id|mode
comma
id|stage
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
id|mode
)paren
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_char
op_star
id|newbase
suffix:semicolon
id|newbase
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
l_int|1
op_plus
id|pathlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
comma
id|name
comma
id|pathlen
)paren
suffix:semicolon
id|newbase
(braket
id|baselen
op_plus
id|pathlen
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|retval
op_assign
id|read_tree_recursive
c_func
(paren
id|lookup_tree
c_func
(paren
id|sha1
)paren
comma
id|newbase
comma
id|baselen
op_plus
id|pathlen
op_plus
l_int|1
comma
id|stage
comma
id|match
comma
id|fn
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
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
r_continue
suffix:semicolon
)brace
)brace
r_return
l_int|0
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
r_const
r_char
op_star
op_star
id|match
)paren
(brace
r_return
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
id|read_one_entry
)paren
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
(brace
r_struct
id|tree
op_star
id|ret
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|tree
)paren
)paren
suffix:semicolon
id|created_object
c_func
(paren
id|sha1
comma
op_amp
id|ret-&gt;object
)paren
suffix:semicolon
id|ret-&gt;object.type
op_assign
id|tree_type
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;type
)paren
id|obj-&gt;type
op_assign
id|tree_type
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|tree_type
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
id|obj-&gt;type
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
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|tree_entry_list
op_star
op_star
id|list_p
suffix:semicolon
r_int
id|n_refs
op_assign
l_int|0
suffix:semicolon
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
id|desc.buf
op_assign
id|buffer
suffix:semicolon
id|desc.size
op_assign
id|size
suffix:semicolon
id|list_p
op_assign
op_amp
id|item-&gt;entries
suffix:semicolon
r_while
c_loop
(paren
id|desc.size
)paren
(brace
r_int
id|mode
suffix:semicolon
r_const
r_char
op_star
id|path
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_struct
id|tree_entry_list
op_star
id|entry
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|desc
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|entry
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tree_entry_list
)paren
)paren
suffix:semicolon
id|entry-&gt;name
op_assign
id|path
suffix:semicolon
id|entry-&gt;sha1
op_assign
id|sha1
suffix:semicolon
id|entry-&gt;mode
op_assign
id|mode
suffix:semicolon
id|entry-&gt;directory
op_assign
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_ne
l_int|0
suffix:semicolon
id|entry-&gt;executable
op_assign
(paren
id|mode
op_amp
id|S_IXUSR
)paren
op_ne
l_int|0
suffix:semicolon
id|entry-&gt;symlink
op_assign
id|S_ISLNK
c_func
(paren
id|mode
)paren
op_ne
l_int|0
suffix:semicolon
id|entry-&gt;zeropad
op_assign
op_star
(paren
r_const
r_char
op_star
)paren
(paren
id|desc.buf
)paren
op_eq
l_char|&squot;0&squot;
suffix:semicolon
id|entry-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|desc
)paren
suffix:semicolon
id|n_refs
op_increment
suffix:semicolon
op_star
id|list_p
op_assign
id|entry
suffix:semicolon
id|list_p
op_assign
op_amp
id|entry-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|track_object_refs
)paren
(brace
r_struct
id|tree_entry_list
op_star
id|entry
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|object_refs
op_star
id|refs
op_assign
id|alloc_object_refs
c_func
(paren
id|n_refs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|item-&gt;entries
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;directory
)paren
id|obj
op_assign
op_amp
id|lookup_tree
c_func
(paren
id|entry-&gt;sha1
)paren
op_member_access_from_pointer
id|object
suffix:semicolon
r_else
id|obj
op_assign
op_amp
id|lookup_blob
c_func
(paren
id|entry-&gt;sha1
)paren
op_member_access_from_pointer
id|object
suffix:semicolon
id|refs-&gt;ref
(braket
id|i
op_increment
)braket
op_assign
id|obj
suffix:semicolon
)brace
id|set_object_refs
c_func
(paren
op_amp
id|item-&gt;object
comma
id|refs
)paren
suffix:semicolon
)brace
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
r_char
id|type
(braket
l_int|20
)braket
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
id|strcmp
c_func
(paren
id|type
comma
id|tree_type
)paren
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
id|tree_type
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
id|commit_type
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
id|tag_type
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
