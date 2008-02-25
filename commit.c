macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
DECL|variable|save_commit_buffer
r_int
id|save_commit_buffer
op_assign
l_int|1
suffix:semicolon
DECL|variable|commit_type
r_const
r_char
op_star
id|commit_type
op_assign
l_string|&quot;commit&quot;
suffix:semicolon
DECL|function|check_commit
r_static
r_struct
id|commit
op_star
id|check_commit
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|quiet
)paren
(brace
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|OBJ_COMMIT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|error
c_func
(paren
l_string|&quot;Object %s is a %s, not a commit&quot;
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
id|commit
op_star
)paren
id|obj
suffix:semicolon
)brace
DECL|function|lookup_commit_reference_gently
r_struct
id|commit
op_star
id|lookup_commit_reference_gently
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|quiet
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|deref_tag
c_func
(paren
id|parse_object
c_func
(paren
id|sha1
)paren
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|check_commit
c_func
(paren
id|obj
comma
id|sha1
comma
id|quiet
)paren
suffix:semicolon
)brace
DECL|function|lookup_commit_reference
r_struct
id|commit
op_star
id|lookup_commit_reference
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_return
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|lookup_commit
r_struct
id|commit
op_star
id|lookup_commit
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
id|OBJ_COMMIT
comma
id|alloc_commit_node
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
id|OBJ_COMMIT
suffix:semicolon
r_return
id|check_commit
c_func
(paren
id|obj
comma
id|sha1
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|parse_commit_date
r_static
r_int
r_int
id|parse_commit_date
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|tail
)paren
(brace
r_int
r_int
id|date
suffix:semicolon
r_const
r_char
op_star
id|dateptr
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_plus
l_int|6
op_ge
id|tail
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buf
comma
l_string|&quot;author&quot;
comma
l_int|6
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|buf
OL
id|tail
op_logical_and
op_star
id|buf
op_increment
op_ne
l_char|&squot;&bslash;n&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_plus
l_int|9
op_ge
id|tail
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buf
comma
l_string|&quot;committer&quot;
comma
l_int|9
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|buf
OL
id|tail
op_logical_and
op_star
id|buf
op_increment
op_ne
l_char|&squot;&gt;&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_ge
id|tail
)paren
r_return
l_int|0
suffix:semicolon
id|dateptr
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|buf
OL
id|tail
op_logical_and
op_star
id|buf
op_increment
op_ne
l_char|&squot;&bslash;n&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_ge
id|tail
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* dateptr &lt; buf &amp;&amp; buf[-1] == &squot;&bslash;n&squot;, so strtoul will stop at buf-1 */
id|date
op_assign
id|strtoul
c_func
(paren
id|dateptr
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|date
op_eq
id|ULONG_MAX
)paren
id|date
op_assign
l_int|0
suffix:semicolon
r_return
id|date
suffix:semicolon
)brace
DECL|variable|commit_graft
r_static
r_struct
id|commit_graft
op_star
op_star
id|commit_graft
suffix:semicolon
DECL|variable|commit_graft_alloc
DECL|variable|commit_graft_nr
r_static
r_int
id|commit_graft_alloc
comma
id|commit_graft_nr
suffix:semicolon
DECL|function|commit_graft_pos
r_static
r_int
id|commit_graft_pos
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
id|lo
comma
id|hi
suffix:semicolon
id|lo
op_assign
l_int|0
suffix:semicolon
id|hi
op_assign
id|commit_graft_nr
suffix:semicolon
r_while
c_loop
(paren
id|lo
OL
id|hi
)paren
(brace
r_int
id|mi
op_assign
(paren
id|lo
op_plus
id|hi
)paren
op_div
l_int|2
suffix:semicolon
r_struct
id|commit_graft
op_star
id|graft
op_assign
id|commit_graft
(braket
id|mi
)braket
suffix:semicolon
r_int
id|cmp
op_assign
id|hashcmp
c_func
(paren
id|sha1
comma
id|graft-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|mi
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
id|hi
op_assign
id|mi
suffix:semicolon
r_else
id|lo
op_assign
id|mi
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|lo
l_int|1
suffix:semicolon
)brace
DECL|function|register_commit_graft
r_int
id|register_commit_graft
c_func
(paren
r_struct
id|commit_graft
op_star
id|graft
comma
r_int
id|ignore_dups
)paren
(brace
r_int
id|pos
op_assign
id|commit_graft_pos
c_func
(paren
id|graft-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
(brace
r_if
c_cond
(paren
id|ignore_dups
)paren
id|free
c_func
(paren
id|graft
)paren
suffix:semicolon
r_else
(brace
id|free
c_func
(paren
id|commit_graft
(braket
id|pos
)braket
)paren
suffix:semicolon
id|commit_graft
(braket
id|pos
)braket
op_assign
id|graft
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|commit_graft_alloc
op_le
op_increment
id|commit_graft_nr
)paren
(brace
id|commit_graft_alloc
op_assign
id|alloc_nr
c_func
(paren
id|commit_graft_alloc
)paren
suffix:semicolon
id|commit_graft
op_assign
id|xrealloc
c_func
(paren
id|commit_graft
comma
r_sizeof
(paren
op_star
id|commit_graft
)paren
op_star
id|commit_graft_alloc
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OL
id|commit_graft_nr
)paren
id|memmove
c_func
(paren
id|commit_graft
op_plus
id|pos
op_plus
l_int|1
comma
id|commit_graft
op_plus
id|pos
comma
(paren
id|commit_graft_nr
id|pos
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|commit_graft
)paren
)paren
suffix:semicolon
id|commit_graft
(braket
id|pos
)braket
op_assign
id|graft
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_graft_line
r_struct
id|commit_graft
op_star
id|read_graft_line
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
multiline_comment|/* The format is just &quot;Commit Parent1 Parent2 ...&bslash;n&quot; */
r_int
id|i
suffix:semicolon
r_struct
id|commit_graft
op_star
id|graft
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;#&squot;
op_logical_or
id|buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_plus
l_int|1
)paren
op_mod
l_int|41
)paren
(brace
id|bad_graft_data
suffix:colon
id|error
c_func
(paren
l_string|&quot;bad graft data: %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|free
c_func
(paren
id|graft
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|i
op_assign
(paren
id|len
op_plus
l_int|1
)paren
op_div
l_int|41
l_int|1
suffix:semicolon
id|graft
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|graft
)paren
op_plus
l_int|20
op_star
id|i
)paren
suffix:semicolon
id|graft-&gt;nr_parent
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buf
comma
id|graft-&gt;sha1
)paren
)paren
r_goto
id|bad_graft_data
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|40
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_add_assign
l_int|41
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|bad_graft_data
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buf
op_plus
id|i
op_plus
l_int|1
comma
id|graft-&gt;parent
(braket
id|i
op_div
l_int|41
)braket
)paren
)paren
r_goto
id|bad_graft_data
suffix:semicolon
)brace
r_return
id|graft
suffix:semicolon
)brace
DECL|function|read_graft_file
r_int
id|read_graft_file
c_func
(paren
r_const
r_char
op_star
id|graft_file
)paren
(brace
id|FILE
op_star
id|fp
op_assign
id|fopen
c_func
(paren
id|graft_file
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|fp
)paren
)paren
(brace
multiline_comment|/* The format is just &quot;Commit Parent1 Parent2 ...&bslash;n&quot; */
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_struct
id|commit_graft
op_star
id|graft
op_assign
id|read_graft_line
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|graft
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|register_commit_graft
c_func
(paren
id|graft
comma
l_int|1
)paren
)paren
id|error
c_func
(paren
l_string|&quot;duplicate graft data: %s&quot;
comma
id|buf
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prepare_commit_graft
r_static
r_void
id|prepare_commit_graft
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|commit_graft_prepared
suffix:semicolon
r_char
op_star
id|graft_file
suffix:semicolon
r_if
c_cond
(paren
id|commit_graft_prepared
)paren
r_return
suffix:semicolon
id|graft_file
op_assign
id|get_graft_file
c_func
(paren
)paren
suffix:semicolon
id|read_graft_file
c_func
(paren
id|graft_file
)paren
suffix:semicolon
multiline_comment|/* make sure shallows are read */
id|is_repository_shallow
c_func
(paren
)paren
suffix:semicolon
id|commit_graft_prepared
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|lookup_commit_graft
r_struct
id|commit_graft
op_star
id|lookup_commit_graft
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
suffix:semicolon
id|prepare_commit_graft
c_func
(paren
)paren
suffix:semicolon
id|pos
op_assign
id|commit_graft_pos
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|commit_graft
(braket
id|pos
)braket
suffix:semicolon
)brace
DECL|function|write_shallow_commits
r_int
id|write_shallow_commits
c_func
(paren
r_int
id|fd
comma
r_int
id|use_pack_protocol
)paren
(brace
r_int
id|i
comma
id|count
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
id|commit_graft_nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|commit_graft
(braket
id|i
)braket
op_member_access_from_pointer
id|nr_parent
OL
l_int|0
)paren
(brace
r_const
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|commit_graft
(braket
id|i
)braket
op_member_access_from_pointer
id|sha1
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|use_pack_protocol
)paren
id|packet_write
c_func
(paren
id|fd
comma
l_string|&quot;shallow %s&quot;
comma
id|hex
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
id|hex
comma
l_int|40
)paren
op_ne
l_int|40
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_break
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|unregister_shallow
r_int
id|unregister_shallow
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
id|commit_graft_pos
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
l_int|1
OL
id|commit_graft_nr
)paren
id|memcpy
c_func
(paren
id|commit_graft
op_plus
id|pos
comma
id|commit_graft
op_plus
id|pos
op_plus
l_int|1
comma
r_sizeof
(paren
r_struct
id|commit_graft
op_star
)paren
op_star
(paren
id|commit_graft_nr
id|pos
l_int|1
)paren
)paren
suffix:semicolon
id|commit_graft_nr
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_commit_buffer
r_int
id|parse_commit_buffer
c_func
(paren
r_struct
id|commit
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
r_char
op_star
id|tail
op_assign
id|buffer
suffix:semicolon
r_char
op_star
id|bufptr
op_assign
id|buffer
suffix:semicolon
r_int
r_char
id|parent
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit_list
op_star
op_star
id|pptr
suffix:semicolon
r_struct
id|commit_graft
op_star
id|graft
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
id|tail
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|tail
op_le
id|bufptr
op_plus
l_int|46
op_logical_or
id|memcmp
c_func
(paren
id|bufptr
comma
l_string|&quot;tree &quot;
comma
l_int|5
)paren
op_logical_or
id|bufptr
(braket
l_int|45
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bogus commit object %s&quot;
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
id|get_sha1_hex
c_func
(paren
id|bufptr
op_plus
l_int|5
comma
id|parent
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad tree pointer in commit %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|item-&gt;tree
op_assign
id|lookup_tree
c_func
(paren
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;tree
)paren
id|n_refs
op_increment
suffix:semicolon
id|bufptr
op_add_assign
l_int|46
suffix:semicolon
multiline_comment|/* &quot;tree &quot; + &quot;hex sha1&quot; + &quot;&bslash;n&quot; */
id|pptr
op_assign
op_amp
id|item-&gt;parents
suffix:semicolon
id|graft
op_assign
id|lookup_commit_graft
c_func
(paren
id|item-&gt;object.sha1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bufptr
op_plus
l_int|48
OL
id|tail
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|bufptr
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
(brace
r_struct
id|commit
op_star
id|new_parent
suffix:semicolon
r_if
c_cond
(paren
id|tail
op_le
id|bufptr
op_plus
l_int|48
op_logical_or
id|get_sha1_hex
c_func
(paren
id|bufptr
op_plus
l_int|7
comma
id|parent
)paren
op_logical_or
id|bufptr
(braket
l_int|47
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad parents in commit %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|bufptr
op_add_assign
l_int|48
suffix:semicolon
r_if
c_cond
(paren
id|graft
)paren
r_continue
suffix:semicolon
id|new_parent
op_assign
id|lookup_commit
c_func
(paren
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_parent
)paren
(brace
id|pptr
op_assign
op_amp
id|commit_list_insert
c_func
(paren
id|new_parent
comma
id|pptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|n_refs
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|graft
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|commit
op_star
id|new_parent
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
id|graft-&gt;nr_parent
suffix:semicolon
id|i
op_increment
)paren
(brace
id|new_parent
op_assign
id|lookup_commit
c_func
(paren
id|graft-&gt;parent
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_parent
)paren
r_continue
suffix:semicolon
id|pptr
op_assign
op_amp
id|commit_list_insert
c_func
(paren
id|new_parent
comma
id|pptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|n_refs
op_increment
suffix:semicolon
)brace
)brace
id|item-&gt;date
op_assign
id|parse_commit_date
c_func
(paren
id|bufptr
comma
id|tail
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_commit
r_int
id|parse_commit
c_func
(paren
r_struct
id|commit
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
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|item
)paren
r_return
l_int|1
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
id|OBJ_COMMIT
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
l_string|&quot;Object %s not a commit&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|parse_commit_buffer
c_func
(paren
id|item
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_commit_buffer
op_logical_and
op_logical_neg
id|ret
)paren
(brace
id|item-&gt;buffer
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|commit_list_insert
r_struct
id|commit_list
op_star
id|commit_list_insert
c_func
(paren
r_struct
id|commit
op_star
id|item
comma
r_struct
id|commit_list
op_star
op_star
id|list_p
)paren
(brace
r_struct
id|commit_list
op_star
id|new_list
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_list
)paren
)paren
suffix:semicolon
id|new_list-&gt;item
op_assign
id|item
suffix:semicolon
id|new_list-&gt;next
op_assign
op_star
id|list_p
suffix:semicolon
op_star
id|list_p
op_assign
id|new_list
suffix:semicolon
r_return
id|new_list
suffix:semicolon
)brace
DECL|function|free_commit_list
r_void
id|free_commit_list
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|temp
op_assign
id|list
suffix:semicolon
id|list
op_assign
id|temp-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|temp
)paren
suffix:semicolon
)brace
)brace
DECL|function|insert_by_date
r_struct
id|commit_list
op_star
id|insert_by_date
c_func
(paren
r_struct
id|commit
op_star
id|item
comma
r_struct
id|commit_list
op_star
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
op_star
id|pp
op_assign
id|list
suffix:semicolon
r_struct
id|commit_list
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
id|p-&gt;item-&gt;date
OL
id|item-&gt;date
)paren
(brace
r_break
suffix:semicolon
)brace
id|pp
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
)brace
r_return
id|commit_list_insert
c_func
(paren
id|item
comma
id|pp
)paren
suffix:semicolon
)brace
DECL|function|sort_by_date
r_void
id|sort_by_date
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|list
)paren
(brace
id|insert_by_date
c_func
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|item
comma
op_amp
id|ret
)paren
suffix:semicolon
op_star
id|list
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
op_star
id|list
op_assign
id|ret
suffix:semicolon
)brace
DECL|function|pop_most_recent_commit
r_struct
id|commit
op_star
id|pop_most_recent_commit
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
comma
r_int
r_int
id|mark
)paren
(brace
r_struct
id|commit
op_star
id|ret
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|item
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
id|ret-&gt;parents
suffix:semicolon
r_struct
id|commit_list
op_star
id|old
op_assign
op_star
id|list
suffix:semicolon
op_star
id|list
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|free
c_func
(paren
id|old
)paren
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|parents-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_commit
c_func
(paren
id|commit
)paren
op_logical_and
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|mark
)paren
)paren
(brace
id|commit-&gt;object.flags
op_or_assign
id|mark
suffix:semicolon
id|insert_by_date
c_func
(paren
id|commit
comma
id|list
)paren
suffix:semicolon
)brace
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|clear_commit_marks
r_void
id|clear_commit_marks
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
r_int
id|mark
)paren
(brace
r_while
c_loop
(paren
id|commit
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mark
op_amp
id|commit-&gt;object.flags
)paren
)paren
r_return
suffix:semicolon
id|commit-&gt;object.flags
op_and_assign
op_complement
id|mark
suffix:semicolon
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parents
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|parents
op_assign
id|parents-&gt;next
)paren
)paren
id|clear_commit_marks
c_func
(paren
id|parents-&gt;item
comma
id|mark
)paren
suffix:semicolon
id|commit
op_assign
id|commit-&gt;parents-&gt;item
suffix:semicolon
)brace
)brace
DECL|function|pop_commit
r_struct
id|commit
op_star
id|pop_commit
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|stack
)paren
(brace
r_struct
id|commit_list
op_star
id|top
op_assign
op_star
id|stack
suffix:semicolon
r_struct
id|commit
op_star
id|item
op_assign
id|top
ques
c_cond
id|top-&gt;item
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|top
)paren
(brace
op_star
id|stack
op_assign
id|top-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|top
)paren
suffix:semicolon
)brace
r_return
id|item
suffix:semicolon
)brace
multiline_comment|/*&n; * Performs an in-place topological sort on the list supplied.&n; */
DECL|function|sort_in_topological_order
r_void
id|sort_in_topological_order
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
comma
r_int
id|lifo
)paren
(brace
r_struct
id|commit_list
op_star
id|next
comma
op_star
id|orig
op_assign
op_star
id|list
suffix:semicolon
r_struct
id|commit_list
op_star
id|work
comma
op_star
op_star
id|insert
suffix:semicolon
r_struct
id|commit_list
op_star
op_star
id|pptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|orig
)paren
r_return
suffix:semicolon
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Mark them and clear the indegree */
r_for
c_loop
(paren
id|next
op_assign
id|orig
suffix:semicolon
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|next-&gt;item
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|TOPOSORT
suffix:semicolon
id|commit-&gt;indegree
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* update the indegree */
r_for
c_loop
(paren
id|next
op_assign
id|orig
suffix:semicolon
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
op_assign
id|next-&gt;item-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_if
c_cond
(paren
id|parent-&gt;object.flags
op_amp
id|TOPOSORT
)paren
id|parent-&gt;indegree
op_increment
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * find the tips&n;&t; *&n;&t; * tips are nodes not reachable from any other node in the list&n;&t; *&n;&t; * the tips serve as a starting set for the work queue.&n;&t; */
id|work
op_assign
l_int|NULL
suffix:semicolon
id|insert
op_assign
op_amp
id|work
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|orig
suffix:semicolon
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|next-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;indegree
)paren
id|insert
op_assign
op_amp
id|commit_list_insert
c_func
(paren
id|commit
comma
id|insert
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
multiline_comment|/* process the list in topological order */
r_if
c_cond
(paren
op_logical_neg
id|lifo
)paren
id|sort_by_date
c_func
(paren
op_amp
id|work
)paren
suffix:semicolon
id|pptr
op_assign
id|list
suffix:semicolon
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|work
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
comma
op_star
id|work_item
suffix:semicolon
id|work_item
op_assign
id|work
suffix:semicolon
id|work
op_assign
id|work_item-&gt;next
suffix:semicolon
id|work_item-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|commit
op_assign
id|work_item-&gt;item
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|parent-&gt;object.flags
op_amp
id|TOPOSORT
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * parents are only enqueued for emission&n;&t;&t;&t; * when all their children have been emitted thereby&n;&t;&t;&t; * guaranteeing topological order.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|parent-&gt;indegree
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lifo
)paren
id|insert_by_date
c_func
(paren
id|parent
comma
op_amp
id|work
)paren
suffix:semicolon
r_else
id|commit_list_insert
c_func
(paren
id|parent
comma
op_amp
id|work
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * work_item is a commit all of whose children&n;&t;&t; * have already been emitted. we can emit it now.&n;&t;&t; */
id|commit-&gt;object.flags
op_and_assign
op_complement
id|TOPOSORT
suffix:semicolon
op_star
id|pptr
op_assign
id|work_item
suffix:semicolon
id|pptr
op_assign
op_amp
id|work_item-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/* merge-base stuff */
multiline_comment|/* bits #0..15 in revision.h */
DECL|macro|PARENT1
mdefine_line|#define PARENT1&t;&t;(1u&lt;&lt;16)
DECL|macro|PARENT2
mdefine_line|#define PARENT2&t;&t;(1u&lt;&lt;17)
DECL|macro|STALE
mdefine_line|#define STALE&t;&t;(1u&lt;&lt;18)
DECL|macro|RESULT
mdefine_line|#define RESULT&t;&t;(1u&lt;&lt;19)
DECL|variable|all_flags
r_static
r_const
r_int
id|all_flags
op_assign
(paren
id|PARENT1
op_or
id|PARENT2
op_or
id|STALE
op_or
id|RESULT
)paren
suffix:semicolon
DECL|function|interesting
r_static
r_struct
id|commit
op_star
id|interesting
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|STALE
)paren
r_continue
suffix:semicolon
r_return
id|commit
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|merge_bases
r_static
r_struct
id|commit_list
op_star
id|merge_bases
c_func
(paren
r_struct
id|commit
op_star
id|one
comma
r_struct
id|commit
op_star
id|two
)paren
(brace
r_struct
id|commit_list
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|one
op_eq
id|two
)paren
multiline_comment|/* We do not mark this even with RESULT so we do not&n;&t;&t; * have to clean it up.&n;&t;&t; */
r_return
id|commit_list_insert
c_func
(paren
id|one
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|one
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|two
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|one-&gt;object.flags
op_or_assign
id|PARENT1
suffix:semicolon
id|two-&gt;object.flags
op_or_assign
id|PARENT2
suffix:semicolon
id|insert_by_date
c_func
(paren
id|one
comma
op_amp
id|list
)paren
suffix:semicolon
id|insert_by_date
c_func
(paren
id|two
comma
op_amp
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|interesting
c_func
(paren
id|list
)paren
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_struct
id|commit_list
op_star
id|n
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
id|n
op_assign
id|list-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|list
)paren
suffix:semicolon
id|list
op_assign
id|n
suffix:semicolon
id|flags
op_assign
id|commit-&gt;object.flags
op_amp
(paren
id|PARENT1
op_or
id|PARENT2
op_or
id|STALE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_eq
(paren
id|PARENT1
op_or
id|PARENT2
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|RESULT
)paren
)paren
(brace
id|commit-&gt;object.flags
op_or_assign
id|RESULT
suffix:semicolon
id|insert_by_date
c_func
(paren
id|commit
comma
op_amp
id|result
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark parents of a found merge stale */
id|flags
op_or_assign
id|STALE
suffix:semicolon
)brace
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|p
op_assign
id|parents-&gt;item
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;object.flags
op_amp
id|flags
)paren
op_eq
id|flags
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|p
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|p-&gt;object.flags
op_or_assign
id|flags
suffix:semicolon
id|insert_by_date
c_func
(paren
id|p
comma
op_amp
id|list
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Clean up the result to remove stale ones */
id|free_commit_list
c_func
(paren
id|list
)paren
suffix:semicolon
id|list
op_assign
id|result
suffix:semicolon
id|result
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|n
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|list-&gt;item-&gt;object.flags
op_amp
id|STALE
)paren
)paren
id|insert_by_date
c_func
(paren
id|list-&gt;item
comma
op_amp
id|result
)paren
suffix:semicolon
id|free
c_func
(paren
id|list
)paren
suffix:semicolon
id|list
op_assign
id|n
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|get_merge_bases
r_struct
id|commit_list
op_star
id|get_merge_bases
c_func
(paren
r_struct
id|commit
op_star
id|one
comma
r_struct
id|commit
op_star
id|two
comma
r_int
id|cleanup
)paren
(brace
r_struct
id|commit_list
op_star
id|list
suffix:semicolon
r_struct
id|commit
op_star
op_star
id|rslt
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
suffix:semicolon
r_int
id|cnt
comma
id|i
comma
id|j
suffix:semicolon
id|result
op_assign
id|merge_bases
c_func
(paren
id|one
comma
id|two
)paren
suffix:semicolon
r_if
c_cond
(paren
id|one
op_eq
id|two
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
op_logical_or
op_logical_neg
id|result-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|cleanup
)paren
(brace
id|clear_commit_marks
c_func
(paren
id|one
comma
id|all_flags
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|two
comma
id|all_flags
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* There are more than one */
id|cnt
op_assign
l_int|0
suffix:semicolon
id|list
op_assign
id|result
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
id|list
op_assign
id|list-&gt;next
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
id|rslt
op_assign
id|xcalloc
c_func
(paren
id|cnt
comma
r_sizeof
(paren
op_star
id|rslt
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|result
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
id|rslt
(braket
id|i
op_increment
)braket
op_assign
id|list-&gt;item
suffix:semicolon
id|free_commit_list
c_func
(paren
id|result
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|one
comma
id|all_flags
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|two
comma
id|all_flags
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
id|cnt
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rslt
(braket
id|i
)braket
op_logical_or
op_logical_neg
id|rslt
(braket
id|j
)braket
)paren
r_continue
suffix:semicolon
id|result
op_assign
id|merge_bases
c_func
(paren
id|rslt
(braket
id|i
)braket
comma
id|rslt
(braket
id|j
)braket
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|rslt
(braket
id|i
)braket
comma
id|all_flags
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|rslt
(braket
id|j
)braket
comma
id|all_flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|result
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|rslt
(braket
id|i
)braket
op_eq
id|list-&gt;item
)paren
id|rslt
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|rslt
(braket
id|j
)braket
op_eq
id|list-&gt;item
)paren
id|rslt
(braket
id|j
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Surviving ones in rslt[] are the independent results */
id|result
op_assign
l_int|NULL
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rslt
(braket
id|i
)braket
)paren
id|insert_by_date
c_func
(paren
id|rslt
(braket
id|i
)braket
comma
op_amp
id|result
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|rslt
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|in_merge_bases
r_int
id|in_merge_bases
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit
op_star
op_star
id|reference
comma
r_int
id|num
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
r_if
c_cond
(paren
id|num
op_eq
l_int|1
)paren
id|bases
op_assign
id|get_merge_bases
c_func
(paren
id|commit
comma
op_star
id|reference
comma
l_int|1
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;not yet&quot;
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
id|commit-&gt;object.sha1
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
eof
