macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;reachable.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;progress.h&quot;
macro_line|#include &quot;list-objects.h&quot;
DECL|struct|connectivity_progress
r_struct
id|connectivity_progress
(brace
DECL|member|progress
r_struct
id|progress
op_star
id|progress
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|update_progress
r_static
r_void
id|update_progress
c_func
(paren
r_struct
id|connectivity_progress
op_star
id|cp
)paren
(brace
id|cp-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cp-&gt;count
op_amp
l_int|1023
)paren
op_eq
l_int|0
)paren
id|display_progress
c_func
(paren
id|cp-&gt;progress
comma
id|cp-&gt;count
)paren
suffix:semicolon
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
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|object
op_star
id|object
op_assign
id|parse_object_or_die
c_func
(paren
id|sha1
comma
id|path
)paren
suffix:semicolon
r_struct
id|rev_info
op_star
id|revs
op_assign
(paren
r_struct
id|rev_info
op_star
)paren
id|cb_data
suffix:semicolon
id|add_pending_object
c_func
(paren
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
multiline_comment|/*&n; * The traversal will have already marked us as SEEN, so we&n; * only need to handle any progress reporting here.&n; */
DECL|function|mark_object
r_static
r_void
id|mark_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|data
)paren
(brace
id|update_progress
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|function|mark_commit
r_static
r_void
id|mark_commit
c_func
(paren
r_struct
id|commit
op_star
id|c
comma
r_void
op_star
id|data
)paren
(brace
id|mark_object
c_func
(paren
op_amp
id|c-&gt;object
comma
l_int|NULL
comma
l_int|NULL
comma
id|data
)paren
suffix:semicolon
)brace
DECL|struct|recent_data
r_struct
id|recent_data
(brace
DECL|member|revs
r_struct
id|rev_info
op_star
id|revs
suffix:semicolon
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
)brace
suffix:semicolon
DECL|function|add_recent_object
r_static
r_void
id|add_recent_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|mtime
comma
r_struct
id|recent_data
op_star
id|data
)paren
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_if
c_cond
(paren
id|mtime
op_le
id|data-&gt;timestamp
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * We do not want to call parse_object here, because&n;&t; * inflating blobs and trees could be very expensive.&n;&t; * However, we do need to know the correct type for&n;&t; * later processing, and the revision machinery expects&n;&t; * commits and tags to have been parsed.&n;&t; */
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to get object info for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|OBJ_TAG
suffix:colon
r_case
id|OBJ_COMMIT
suffix:colon
id|obj
op_assign
id|parse_object_or_die
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_TREE
suffix:colon
id|obj
op_assign
(paren
r_struct
id|object
op_star
)paren
id|lookup_tree
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_BLOB
suffix:colon
id|obj
op_assign
(paren
r_struct
id|object
op_star
)paren
id|lookup_blob
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;unknown object type for %s: %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_typename
(paren
id|type
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
id|die
c_func
(paren
l_string|&quot;unable to lookup %s&quot;
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
id|data-&gt;revs
comma
id|obj
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|function|add_recent_loose
r_static
r_int
id|add_recent_loose
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
id|path
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
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
id|obj
op_logical_and
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * It&squot;s OK if an object went away during our iteration; this&n;&t;&t; * could be due to a simultaneous repack. But anything else&n;&t;&t; * we should abort, since we might then fail to mark objects&n;&t;&t; * which should not be pruned.&n;&t;&t; */
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unable to stat %s: %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|add_recent_object
c_func
(paren
id|sha1
comma
id|st.st_mtime
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_recent_packed
r_static
r_int
id|add_recent_packed
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|packed_git
op_star
id|p
comma
r_uint32
id|pos
comma
r_void
op_star
id|data
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
id|obj
op_logical_and
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
l_int|0
suffix:semicolon
id|add_recent_object
c_func
(paren
id|sha1
comma
id|p-&gt;mtime
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_unseen_recent_objects_to_traversal
r_int
id|add_unseen_recent_objects_to_traversal
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
r_int
id|timestamp
)paren
(brace
r_struct
id|recent_data
id|data
suffix:semicolon
r_int
id|r
suffix:semicolon
id|data.revs
op_assign
id|revs
suffix:semicolon
id|data.timestamp
op_assign
id|timestamp
suffix:semicolon
id|r
op_assign
id|for_each_loose_object
c_func
(paren
id|add_recent_loose
comma
op_amp
id|data
comma
id|FOR_EACH_OBJECT_LOCAL_ONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
r_return
id|for_each_packed_object
c_func
(paren
id|add_recent_packed
comma
op_amp
id|data
comma
id|FOR_EACH_OBJECT_LOCAL_ONLY
)paren
suffix:semicolon
)brace
DECL|function|mark_reachable_objects
r_void
id|mark_reachable_objects
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|mark_reflog
comma
r_int
r_int
id|mark_recent
comma
r_struct
id|progress
op_star
id|progress
)paren
(brace
r_struct
id|connectivity_progress
id|cp
suffix:semicolon
multiline_comment|/*&n;&t; * Set up revision parsing, and mark us as being interested&n;&t; * in all object types, not just commits.&n;&t; */
id|revs-&gt;tag_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;blob_objects
op_assign
l_int|1
suffix:semicolon
id|revs-&gt;tree_objects
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Add all refs from the index file */
id|add_index_objects_to_pending
c_func
(paren
id|revs
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Add all external refs */
id|for_each_ref
c_func
(paren
id|add_one_ref
comma
id|revs
)paren
suffix:semicolon
multiline_comment|/* detached HEAD is not included in the list above */
id|head_ref
c_func
(paren
id|add_one_ref
comma
id|revs
)paren
suffix:semicolon
multiline_comment|/* Add all reflog info */
r_if
c_cond
(paren
id|mark_reflog
)paren
id|add_reflogs_to_pending
c_func
(paren
id|revs
comma
l_int|0
)paren
suffix:semicolon
id|cp.progress
op_assign
id|progress
suffix:semicolon
id|cp.count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the revision walk - this will move all commits&n;&t; * from the pending list to the commit walking list.&n;&t; */
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
id|revs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
id|traverse_commit_list
c_func
(paren
id|revs
comma
id|mark_commit
comma
id|mark_object
comma
op_amp
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mark_recent
)paren
(brace
id|revs-&gt;ignore_missing_links
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|add_unseen_recent_objects_to_traversal
c_func
(paren
id|revs
comma
id|mark_recent
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to mark recent objects&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
id|revs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
id|traverse_commit_list
c_func
(paren
id|revs
comma
id|mark_commit
comma
id|mark_object
comma
op_amp
id|cp
)paren
suffix:semicolon
)brace
id|display_progress
c_func
(paren
id|cp.progress
comma
id|cp.count
)paren
suffix:semicolon
)brace
eof
