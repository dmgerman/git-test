macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|variable|prune_usage
r_static
r_const
r_char
id|prune_usage
(braket
)braket
op_assign
l_string|&quot;git prune [-n]&quot;
suffix:semicolon
DECL|variable|show_only
r_static
r_int
id|show_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|revs
r_static
r_struct
id|rev_info
id|revs
suffix:semicolon
DECL|function|prune_object
r_static
r_int
id|prune_object
c_func
(paren
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|filename
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|show_only
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;would prune %s/%s&bslash;n&quot;
comma
id|path
comma
id|filename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|unlink
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
id|path
comma
id|filename
)paren
)paren
suffix:semicolon
id|rmdir
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_dir
r_static
r_int
id|prune_dir
c_func
(paren
r_int
id|i
comma
r_char
op_star
id|path
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
id|name
(braket
l_int|100
)braket
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
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_int|38
suffix:colon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|i
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|name
op_plus
l_int|2
comma
id|de-&gt;d_name
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|name
comma
id|sha1
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Do we know about this object?&n;&t;&t;&t; * It must have been reachable&n;&t;&t;&t; */
r_if
c_cond
(paren
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
r_continue
suffix:semicolon
id|prune_object
c_func
(paren
id|path
comma
id|de-&gt;d_name
comma
id|sha1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;bad sha1 file: %s/%s&bslash;n&quot;
comma
id|path
comma
id|de-&gt;d_name
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_object_dir
r_static
r_void
id|prune_object_dir
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|i
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_static
r_char
id|dir
(braket
l_int|4096
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|dir
comma
l_string|&quot;%s/%02x&quot;
comma
id|path
comma
id|i
)paren
suffix:semicolon
id|prune_dir
c_func
(paren
id|i
comma
id|dir
)paren
suffix:semicolon
)brace
)brace
DECL|function|process_blob
r_static
r_void
id|process_blob
c_func
(paren
r_struct
id|blob
op_star
id|blob
comma
r_struct
id|object_array
op_star
id|p
comma
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
op_amp
id|blob-&gt;object
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
multiline_comment|/* Nothing to do, really .. The blob lookup was the important part */
)brace
DECL|function|process_tree
r_static
r_void
id|process_tree
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_struct
id|object_array
op_star
id|p
comma
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
op_amp
id|tree-&gt;object
suffix:semicolon
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_struct
id|name_path
id|me
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
r_if
c_cond
(paren
id|parse_tree
c_func
(paren
id|tree
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad tree object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|name
op_assign
id|strdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|add_object
c_func
(paren
id|obj
comma
id|p
comma
id|path
comma
id|name
)paren
suffix:semicolon
id|me.up
op_assign
id|path
suffix:semicolon
id|me.elem
op_assign
id|name
suffix:semicolon
id|me.elem_len
op_assign
id|strlen
c_func
(paren
id|name
)paren
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
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|process_tree
c_func
(paren
id|lookup_tree
c_func
(paren
id|entry.sha1
)paren
comma
id|p
comma
op_amp
id|me
comma
id|entry.path
)paren
suffix:semicolon
r_else
id|process_blob
c_func
(paren
id|lookup_blob
c_func
(paren
id|entry.sha1
)paren
comma
id|p
comma
op_amp
id|me
comma
id|entry.path
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|tree-&gt;buffer
)paren
suffix:semicolon
id|tree-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|process_tag
r_static
r_void
id|process_tag
c_func
(paren
r_struct
id|tag
op_star
id|tag
comma
r_struct
id|object_array
op_star
id|p
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
op_amp
id|tag-&gt;object
suffix:semicolon
r_struct
id|name_path
id|me
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
suffix:semicolon
id|me.up
op_assign
l_int|NULL
suffix:semicolon
id|me.elem
op_assign
l_string|&quot;tag:/&quot;
suffix:semicolon
id|me.elem_len
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|parse_tag
c_func
(paren
id|tag
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad tag object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|add_object
c_func
(paren
id|tag-&gt;tagged
comma
id|p
comma
l_int|NULL
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|walk_commit_list
r_static
r_void
id|walk_commit_list
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|object_array
id|objects
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* Walk all commits, process their trees */
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|revs
)paren
)paren
op_ne
l_int|NULL
)paren
id|process_tree
c_func
(paren
id|commit-&gt;tree
comma
op_amp
id|objects
comma
l_int|NULL
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* Then walk all the pending objects, recursively processing them too */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|revs-&gt;pending.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object_array_entry
op_star
id|pending
op_assign
id|revs-&gt;pending.objects
op_plus
id|i
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
id|pending-&gt;item
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|pending-&gt;name
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|process_tag
c_func
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
comma
op_amp
id|objects
comma
id|name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
(brace
id|process_tree
c_func
(paren
(paren
r_struct
id|tree
op_star
)paren
id|obj
comma
op_amp
id|objects
comma
l_int|NULL
comma
id|name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_BLOB
)paren
(brace
id|process_blob
c_func
(paren
(paren
r_struct
id|blob
op_star
)paren
id|obj
comma
op_amp
id|objects
comma
l_int|NULL
comma
id|name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;unknown pending object %s (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
id|name
)paren
suffix:semicolon
)brace
)brace
DECL|function|add_one_ref
r_static
r_int
id|add_one_ref
c_func
(paren
r_const
r_char
op_star
id|path
comma
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
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
id|die
c_func
(paren
l_string|&quot;bad object ref: %s:%s&quot;
comma
id|path
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|object
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_one_tree
r_static
r_void
id|add_one_tree
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
id|tree
op_star
id|tree
op_assign
id|lookup_tree
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
op_amp
id|tree-&gt;object
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|function|add_cache_tree
r_static
r_void
id|add_cache_tree
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|it-&gt;entry_count
op_ge
l_int|0
)paren
id|add_one_tree
c_func
(paren
id|it-&gt;sha1
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
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
id|add_cache_tree
c_func
(paren
id|it-&gt;down
(braket
id|i
)braket
op_member_access_from_pointer
id|cache_tree
)paren
suffix:semicolon
)brace
DECL|function|add_cache_refs
r_static
r_void
id|add_cache_refs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|read_cache
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lookup_blob
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|sha1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We could add the blobs to the pending list, but quite&n;&t;&t; * frankly, we don&squot;t care. Once we&squot;ve looked them up, and&n;&t;&t; * added them as objects, we&squot;ve really done everything&n;&t;&t; * there is to do for a blob&n;&t;&t; */
)brace
r_if
c_cond
(paren
id|active_cache_tree
)paren
id|add_cache_tree
c_func
(paren
id|active_cache_tree
)paren
suffix:semicolon
)brace
DECL|function|cmd_prune
r_int
id|cmd_prune
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
id|i
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
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
(brace
id|show_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|prune_usage
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set up revision parsing, and mark us as being interested&n;&t; * in all object types, not just commits.&n;&t; */
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
id|setup_git_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|revs.tag_objects
op_assign
l_int|1
suffix:semicolon
id|revs.blob_objects
op_assign
l_int|1
suffix:semicolon
id|revs.tree_objects
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Add all external refs */
id|for_each_ref
c_func
(paren
id|add_one_ref
)paren
suffix:semicolon
multiline_comment|/* Add all refs from the index file */
id|add_cache_refs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the revision walk - this will move all commits&n;&t; * from the pending list to the commit walking list.&n;&t; */
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
id|walk_commit_list
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
id|prune_object_dir
c_func
(paren
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
