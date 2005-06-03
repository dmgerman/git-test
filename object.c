macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;delta.h&quot;
DECL|variable|objs
r_struct
id|object
op_star
op_star
id|objs
suffix:semicolon
DECL|variable|nr_objs
r_int
id|nr_objs
suffix:semicolon
DECL|variable|obj_allocs
r_static
r_int
id|obj_allocs
suffix:semicolon
DECL|function|find_object
r_static
r_int
id|find_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|first
op_assign
l_int|0
comma
id|last
op_assign
id|nr_objs
suffix:semicolon
r_while
c_loop
(paren
id|first
OL
id|last
)paren
(brace
r_int
id|next
op_assign
(paren
id|first
op_plus
id|last
)paren
op_div
l_int|2
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
id|objs
(braket
id|next
)braket
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|cmp
op_assign
id|memcmp
c_func
(paren
id|sha1
comma
id|obj-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|next
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|last
op_assign
id|next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|first
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|first
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|lookup_object
r_struct
id|object
op_star
id|lookup_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|pos
op_assign
id|find_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
l_int|0
)paren
r_return
id|objs
(braket
id|pos
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|created_object
r_void
id|created_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|object
op_star
id|obj
)paren
(brace
r_int
id|pos
op_assign
id|find_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|obj-&gt;parsed
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|obj-&gt;sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|obj-&gt;type
op_assign
l_int|NULL
suffix:semicolon
id|obj-&gt;refs
op_assign
l_int|NULL
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Inserting %s twice&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|obj_allocs
op_eq
id|nr_objs
)paren
(brace
id|obj_allocs
op_assign
id|alloc_nr
c_func
(paren
id|obj_allocs
)paren
suffix:semicolon
id|objs
op_assign
id|xrealloc
c_func
(paren
id|objs
comma
id|obj_allocs
op_star
r_sizeof
(paren
r_struct
id|object
op_star
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Insert it into the right place */
id|memmove
c_func
(paren
id|objs
op_plus
id|pos
op_plus
l_int|1
comma
id|objs
op_plus
id|pos
comma
(paren
id|nr_objs
id|pos
)paren
op_star
r_sizeof
(paren
r_struct
id|object
op_star
)paren
)paren
suffix:semicolon
id|objs
(braket
id|pos
)braket
op_assign
id|obj
suffix:semicolon
id|nr_objs
op_increment
suffix:semicolon
)brace
DECL|function|add_ref
r_void
id|add_ref
c_func
(paren
r_struct
id|object
op_star
id|refer
comma
r_struct
id|object
op_star
id|target
)paren
(brace
r_struct
id|object_list
op_star
op_star
id|pp
op_assign
op_amp
id|refer-&gt;refs
suffix:semicolon
r_struct
id|object_list
op_star
id|p
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
op_star
id|pp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;item
op_eq
id|target
)paren
r_return
suffix:semicolon
id|pp
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
)brace
id|target-&gt;used
op_assign
l_int|1
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|p-&gt;item
op_assign
id|target
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|pp
op_assign
id|p
suffix:semicolon
)brace
DECL|function|mark_reachable
r_void
id|mark_reachable
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_int
r_int
id|mask
)paren
(brace
r_struct
id|object_list
op_star
id|p
op_assign
id|obj-&gt;refs
suffix:semicolon
multiline_comment|/* If we&squot;ve been here already, don&squot;t bother */
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|mask
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|mask
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|mark_reachable
c_func
(paren
id|p-&gt;item
comma
id|mask
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|parse_object
r_struct
id|object
op_star
id|parse_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|mapsize
suffix:semicolon
r_void
op_star
id|map
op_assign
id|map_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
)paren
(brace
r_int
id|is_delta
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_char
id|type
(braket
l_int|100
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|buffer
op_assign
id|unpack_sha1_file
c_func
(paren
id|map
comma
id|mapsize
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
l_int|NULL
suffix:semicolon
id|is_delta
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;delta&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_delta
op_logical_and
id|check_sha1_signature
c_func
(paren
id|sha1
comma
id|buffer
comma
id|size
comma
id|type
)paren
OL
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;sha1 mismatch %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_delta
)paren
(brace
r_struct
id|delta
op_star
id|delta
op_assign
id|lookup_delta
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|parse_delta_buffer
c_func
(paren
id|delta
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
(paren
r_struct
id|object
op_star
)paren
id|delta
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;blob&quot;
)paren
)paren
(brace
r_struct
id|blob
op_star
id|blob
op_assign
id|lookup_blob
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|parse_blob_buffer
c_func
(paren
id|blob
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
op_amp
id|blob-&gt;object
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;tree&quot;
)paren
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
id|parse_tree_buffer
c_func
(paren
id|tree
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
op_amp
id|tree-&gt;object
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;commit&quot;
)paren
)paren
(brace
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
id|parse_commit_buffer
c_func
(paren
id|commit
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;buffer
)paren
(brace
id|commit-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
id|obj
op_assign
op_amp
id|commit-&gt;object
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;tag&quot;
)paren
)paren
(brace
r_struct
id|tag
op_star
id|tag
op_assign
id|lookup_tag
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|parse_tag_buffer
c_func
(paren
id|tag
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
op_amp
id|tag-&gt;object
suffix:semicolon
)brace
r_else
(brace
id|obj
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
eof
