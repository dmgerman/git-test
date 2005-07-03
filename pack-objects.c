macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;delta.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;csum-file.h&quot;
DECL|variable|pack_usage
r_static
r_const
r_char
id|pack_usage
(braket
)braket
op_assign
l_string|&quot;git-pack-objects [--incremental] [--window=N] [--depth=N] {--stdout | base-name} &lt; object-list&quot;
suffix:semicolon
DECL|struct|object_entry
r_struct
id|object_entry
(brace
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
DECL|member|hash
r_int
r_int
id|hash
suffix:semicolon
DECL|member|type
r_enum
id|object_type
id|type
suffix:semicolon
DECL|member|delta_size
r_int
r_int
id|delta_size
suffix:semicolon
DECL|member|delta
r_struct
id|object_entry
op_star
id|delta
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|non_empty
r_static
r_int
id|non_empty
op_assign
l_int|0
suffix:semicolon
DECL|variable|incremental
r_static
r_int
id|incremental
op_assign
l_int|0
suffix:semicolon
DECL|variable|sorted_by_sha
DECL|variable|sorted_by_type
r_static
r_struct
id|object_entry
op_star
op_star
id|sorted_by_sha
comma
op_star
op_star
id|sorted_by_type
suffix:semicolon
DECL|variable|objects
r_static
r_struct
id|object_entry
op_star
id|objects
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|nr_objects
DECL|variable|nr_alloc
r_static
r_int
id|nr_objects
op_assign
l_int|0
comma
id|nr_alloc
op_assign
l_int|0
suffix:semicolon
DECL|variable|base_name
r_static
r_const
r_char
op_star
id|base_name
suffix:semicolon
DECL|variable|pack_file_sha1
r_static
r_int
r_char
id|pack_file_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|delta_against
r_static
r_void
op_star
id|delta_against
c_func
(paren
r_void
op_star
id|buf
comma
r_int
r_int
id|size
comma
r_struct
id|object_entry
op_star
id|entry
)paren
(brace
r_int
r_int
id|othersize
comma
id|delta_size
suffix:semicolon
r_char
id|type
(braket
l_int|10
)braket
suffix:semicolon
r_void
op_star
id|otherbuf
op_assign
id|read_sha1_file
c_func
(paren
id|entry-&gt;delta-&gt;sha1
comma
id|type
comma
op_amp
id|othersize
)paren
suffix:semicolon
r_void
op_star
id|delta_buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|otherbuf
)paren
id|die
c_func
(paren
l_string|&quot;unable to read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;delta-&gt;sha1
)paren
)paren
suffix:semicolon
id|delta_buf
op_assign
id|diff_delta
c_func
(paren
id|otherbuf
comma
id|othersize
comma
id|buf
comma
id|size
comma
op_amp
id|delta_size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|delta_buf
op_logical_or
id|delta_size
op_ne
id|entry-&gt;delta_size
)paren
id|die
c_func
(paren
l_string|&quot;delta size changed&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
id|free
c_func
(paren
id|otherbuf
)paren
suffix:semicolon
r_return
id|delta_buf
suffix:semicolon
)brace
multiline_comment|/*&n; * The per-object header is a pretty dense thing, which is&n; *  - first byte: low four bits are &quot;size&quot;, then three bits of &quot;type&quot;,&n; *    and the high bit is &quot;size continues&quot;.&n; *  - each byte afterwards: low seven bits are size continuation,&n; *    with the high bit being &quot;size continues&quot;&n; */
DECL|function|encode_header
r_static
r_int
id|encode_header
c_func
(paren
r_enum
id|object_type
id|type
comma
r_int
r_int
id|size
comma
r_int
r_char
op_star
id|hdr
)paren
(brace
r_int
id|n
op_assign
l_int|1
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|type
template_param
id|OBJ_DELTA
)paren
id|die
c_func
(paren
l_string|&quot;bad type %d&quot;
comma
id|type
)paren
suffix:semicolon
id|c
op_assign
(paren
id|type
op_lshift
l_int|4
)paren
op_or
(paren
id|size
op_amp
l_int|15
)paren
suffix:semicolon
id|size
op_rshift_assign
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
op_star
id|hdr
op_increment
op_assign
id|c
op_or
l_int|0x80
suffix:semicolon
id|c
op_assign
id|size
op_amp
l_int|0x7f
suffix:semicolon
id|size
op_rshift_assign
l_int|7
suffix:semicolon
id|n
op_increment
suffix:semicolon
)brace
op_star
id|hdr
op_assign
id|c
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|write_object
r_static
r_int
r_int
id|write_object
c_func
(paren
r_struct
id|sha1file
op_star
id|f
comma
r_struct
id|object_entry
op_star
id|entry
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|10
)braket
suffix:semicolon
r_void
op_star
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|entry-&gt;sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_int
r_char
id|header
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|hdrlen
comma
id|datalen
suffix:semicolon
r_enum
id|object_type
id|obj_type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;unable to read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
id|entry-&gt;size
)paren
id|die
c_func
(paren
l_string|&quot;object %s size inconsistency (%lu vs %lu)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
comma
id|size
comma
id|entry-&gt;size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The object header is a byte of &squot;type&squot; followed by zero or&n;&t; * more bytes of length.  For deltas, the 20 bytes of delta sha1&n;&t; * follows that.&n;&t; */
id|obj_type
op_assign
id|entry-&gt;type
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;delta
)paren
(brace
id|buf
op_assign
id|delta_against
c_func
(paren
id|buf
comma
id|size
comma
id|entry
)paren
suffix:semicolon
id|size
op_assign
id|entry-&gt;delta_size
suffix:semicolon
id|obj_type
op_assign
id|OBJ_DELTA
suffix:semicolon
)brace
id|hdrlen
op_assign
id|encode_header
c_func
(paren
id|obj_type
comma
id|size
comma
id|header
)paren
suffix:semicolon
id|sha1write
c_func
(paren
id|f
comma
id|header
comma
id|hdrlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;delta
)paren
(brace
id|sha1write
c_func
(paren
id|f
comma
id|entry-&gt;delta
comma
l_int|20
)paren
suffix:semicolon
id|hdrlen
op_add_assign
l_int|20
suffix:semicolon
)brace
id|datalen
op_assign
id|sha1write_compressed
c_func
(paren
id|f
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|hdrlen
op_plus
id|datalen
suffix:semicolon
)brace
DECL|function|write_one
r_static
r_int
r_int
id|write_one
c_func
(paren
r_struct
id|sha1file
op_star
id|f
comma
r_struct
id|object_entry
op_star
id|e
comma
r_int
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|e-&gt;offset
)paren
multiline_comment|/* offset starts from header size and cannot be zero&n;&t;&t; * if it is written already.&n;&t;&t; */
r_return
id|offset
suffix:semicolon
id|e-&gt;offset
op_assign
id|offset
suffix:semicolon
id|offset
op_add_assign
id|write_object
c_func
(paren
id|f
comma
id|e
)paren
suffix:semicolon
multiline_comment|/* if we are delitified, write out its base object. */
r_if
c_cond
(paren
id|e-&gt;delta
)paren
id|offset
op_assign
id|write_one
c_func
(paren
id|f
comma
id|e-&gt;delta
comma
id|offset
)paren
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
DECL|function|write_pack_file
r_static
r_void
id|write_pack_file
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sha1file
op_star
id|f
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|mb
suffix:semicolon
r_struct
id|pack_header
id|hdr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base_name
)paren
id|f
op_assign
id|sha1fd
c_func
(paren
l_int|1
comma
l_string|&quot;&lt;stdout&gt;&quot;
)paren
suffix:semicolon
r_else
id|f
op_assign
id|sha1create
c_func
(paren
l_string|&quot;%s.%s&quot;
comma
id|base_name
comma
l_string|&quot;pack&quot;
)paren
suffix:semicolon
id|hdr.hdr_signature
op_assign
id|htonl
c_func
(paren
id|PACK_SIGNATURE
)paren
suffix:semicolon
id|hdr.hdr_version
op_assign
id|htonl
c_func
(paren
id|PACK_VERSION
)paren
suffix:semicolon
id|hdr.hdr_entries
op_assign
id|htonl
c_func
(paren
id|nr_objects
)paren
suffix:semicolon
id|sha1write
c_func
(paren
id|f
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
suffix:semicolon
id|offset
op_assign
r_sizeof
(paren
id|hdr
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
id|nr_objects
suffix:semicolon
id|i
op_increment
)paren
id|offset
op_assign
id|write_one
c_func
(paren
id|f
comma
id|objects
op_plus
id|i
comma
id|offset
)paren
suffix:semicolon
id|sha1close
c_func
(paren
id|f
comma
id|pack_file_sha1
comma
l_int|1
)paren
suffix:semicolon
id|mb
op_assign
id|offset
op_rshift
l_int|20
suffix:semicolon
id|offset
op_and_assign
l_int|0xfffff
suffix:semicolon
)brace
DECL|function|write_index_file
r_static
r_void
id|write_index_file
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sha1file
op_star
id|f
op_assign
id|sha1create
c_func
(paren
l_string|&quot;%s.%s&quot;
comma
id|base_name
comma
l_string|&quot;idx&quot;
)paren
suffix:semicolon
r_struct
id|object_entry
op_star
op_star
id|list
op_assign
id|sorted_by_sha
suffix:semicolon
r_struct
id|object_entry
op_star
op_star
id|last
op_assign
id|list
op_plus
id|nr_objects
suffix:semicolon
r_int
r_int
id|array
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Write the first-level table (the list is sorted,&n;&t; * but we use a 256-entry lookup to be able to avoid&n;&t; * having to do eight extra binary search iterations).&n;&t; */
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
r_struct
id|object_entry
op_star
op_star
id|next
op_assign
id|list
suffix:semicolon
r_while
c_loop
(paren
id|next
OL
id|last
)paren
(brace
r_struct
id|object_entry
op_star
id|entry
op_assign
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;sha1
(braket
l_int|0
)braket
op_ne
id|i
)paren
r_break
suffix:semicolon
id|next
op_increment
suffix:semicolon
)brace
id|array
(braket
id|i
)braket
op_assign
id|htonl
c_func
(paren
id|next
id|sorted_by_sha
)paren
suffix:semicolon
id|list
op_assign
id|next
suffix:semicolon
)brace
id|sha1write
c_func
(paren
id|f
comma
id|array
comma
l_int|256
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Write the actual SHA1 entries..&n;&t; */
id|list
op_assign
id|sorted_by_sha
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
id|nr_objects
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object_entry
op_star
id|entry
op_assign
op_star
id|list
op_increment
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|htonl
c_func
(paren
id|entry-&gt;offset
)paren
suffix:semicolon
id|sha1write
c_func
(paren
id|f
comma
op_amp
id|offset
comma
l_int|4
)paren
suffix:semicolon
id|sha1write
c_func
(paren
id|f
comma
id|entry-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
id|sha1write
c_func
(paren
id|f
comma
id|pack_file_sha1
comma
l_int|20
)paren
suffix:semicolon
id|sha1close
c_func
(paren
id|f
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|add_object_entry
r_static
r_void
id|add_object_entry
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|hash
)paren
(brace
r_int
r_int
id|idx
op_assign
id|nr_objects
suffix:semicolon
r_struct
id|object_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|incremental
op_logical_and
id|has_sha1_pack
c_func
(paren
id|sha1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|nr_alloc
)paren
(brace
r_int
r_int
id|needed
op_assign
(paren
id|idx
op_plus
l_int|1024
)paren
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
id|objects
op_assign
id|xrealloc
c_func
(paren
id|objects
comma
id|needed
op_star
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
id|nr_alloc
op_assign
id|needed
suffix:semicolon
)brace
id|entry
op_assign
id|objects
op_plus
id|idx
suffix:semicolon
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|entry-&gt;sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|entry-&gt;hash
op_assign
id|hash
suffix:semicolon
id|nr_objects
op_assign
id|idx
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|check_object
r_static
r_void
id|check_object
c_func
(paren
r_struct
id|object_entry
op_star
id|entry
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sha1_object_info
c_func
(paren
id|entry-&gt;sha1
comma
id|type
comma
op_amp
id|entry-&gt;size
)paren
)paren
(brace
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
id|entry-&gt;type
op_assign
id|OBJ_COMMIT
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
id|entry-&gt;type
op_assign
id|OBJ_TREE
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
id|entry-&gt;type
op_assign
id|OBJ_BLOB
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
id|entry-&gt;type
op_assign
id|OBJ_TAG
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;unable to pack object %s of type %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
comma
id|type
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;unable to get type of object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_object_details
r_static
r_void
id|get_object_details
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|object_entry
op_star
id|entry
op_assign
id|objects
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
id|nr_objects
suffix:semicolon
id|i
op_increment
)paren
id|check_object
c_func
(paren
id|entry
op_increment
)paren
suffix:semicolon
)brace
DECL|typedef|entry_sort_t
r_typedef
r_int
(paren
op_star
id|entry_sort_t
)paren
(paren
r_const
r_struct
id|object_entry
op_star
comma
r_const
r_struct
id|object_entry
op_star
)paren
suffix:semicolon
DECL|variable|current_sort
r_static
id|entry_sort_t
id|current_sort
suffix:semicolon
DECL|function|sort_comparator
r_static
r_int
id|sort_comparator
c_func
(paren
r_const
r_void
op_star
id|_a
comma
r_const
r_void
op_star
id|_b
)paren
(brace
r_struct
id|object_entry
op_star
id|a
op_assign
op_star
(paren
r_struct
id|object_entry
op_star
op_star
)paren
id|_a
suffix:semicolon
r_struct
id|object_entry
op_star
id|b
op_assign
op_star
(paren
r_struct
id|object_entry
op_star
op_star
)paren
id|_b
suffix:semicolon
r_return
id|current_sort
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
)brace
DECL|function|create_sorted_list
r_static
r_struct
id|object_entry
op_star
op_star
id|create_sorted_list
c_func
(paren
id|entry_sort_t
id|sort
)paren
(brace
r_struct
id|object_entry
op_star
op_star
id|list
op_assign
id|xmalloc
c_func
(paren
id|nr_objects
op_star
r_sizeof
(paren
r_struct
id|object_entry
op_star
)paren
)paren
suffix:semicolon
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
id|nr_objects
suffix:semicolon
id|i
op_increment
)paren
id|list
(braket
id|i
)braket
op_assign
id|objects
op_plus
id|i
suffix:semicolon
id|current_sort
op_assign
id|sort
suffix:semicolon
id|qsort
c_func
(paren
id|list
comma
id|nr_objects
comma
r_sizeof
(paren
r_struct
id|object_entry
op_star
)paren
comma
id|sort_comparator
)paren
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
DECL|function|sha1_sort
r_static
r_int
id|sha1_sort
c_func
(paren
r_const
r_struct
id|object_entry
op_star
id|a
comma
r_const
r_struct
id|object_entry
op_star
id|b
)paren
(brace
r_return
id|memcmp
c_func
(paren
id|a-&gt;sha1
comma
id|b-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
DECL|function|type_size_sort
r_static
r_int
id|type_size_sort
c_func
(paren
r_const
r_struct
id|object_entry
op_star
id|a
comma
r_const
r_struct
id|object_entry
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|a-&gt;type
OL
id|b-&gt;type
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;type
OG
id|b-&gt;type
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;hash
OL
id|b-&gt;hash
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;hash
OG
id|b-&gt;hash
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;size
OL
id|b-&gt;size
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;size
OG
id|b-&gt;size
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|a
OL
id|b
ques
c_cond
l_int|1
suffix:colon
(paren
id|a
OG
id|b
)paren
suffix:semicolon
)brace
DECL|struct|unpacked
r_struct
id|unpacked
(brace
DECL|member|entry
r_struct
id|object_entry
op_star
id|entry
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * We search for deltas _backwards_ in a list sorted by type and&n; * by size, so that we see progressively smaller and smaller files.&n; * That&squot;s because we prefer deltas to be from the bigger file&n; * to the smaller - deletes are potentially cheaper, but perhaps&n; * more importantly, the bigger file is likely the more recent&n; * one.&n; */
DECL|function|try_delta
r_static
r_int
id|try_delta
c_func
(paren
r_struct
id|unpacked
op_star
id|cur
comma
r_struct
id|unpacked
op_star
id|old
comma
r_int
id|max_depth
)paren
(brace
r_struct
id|object_entry
op_star
id|cur_entry
op_assign
id|cur-&gt;entry
suffix:semicolon
r_struct
id|object_entry
op_star
id|old_entry
op_assign
id|old-&gt;entry
suffix:semicolon
r_int
r_int
id|size
comma
id|oldsize
comma
id|delta_size
comma
id|sizediff
suffix:semicolon
r_int
id|max_size
suffix:semicolon
r_void
op_star
id|delta_buf
suffix:semicolon
multiline_comment|/* Don&squot;t bother doing diffs between different types */
r_if
c_cond
(paren
id|cur_entry-&gt;type
op_ne
id|old_entry-&gt;type
)paren
r_return
l_int|1
suffix:semicolon
id|size
op_assign
id|cur_entry-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|50
)paren
r_return
l_int|1
suffix:semicolon
id|oldsize
op_assign
id|old_entry-&gt;size
suffix:semicolon
id|sizediff
op_assign
id|oldsize
OG
id|size
ques
c_cond
id|oldsize
id|size
suffix:colon
id|size
id|oldsize
suffix:semicolon
r_if
c_cond
(paren
id|sizediff
OG
id|size
op_div
l_int|8
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|old_entry-&gt;depth
op_ge
id|max_depth
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE!&n;&t; *&n;&t; * We always delta from the bigger to the smaller, since that&squot;s&n;&t; * more space-efficient (deletes don&squot;t have to say _what_ they&n;&t; * delete).&n;&t; */
id|max_size
op_assign
id|size
op_div
l_int|2
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|cur_entry-&gt;delta
)paren
id|max_size
op_assign
id|cur_entry-&gt;delta_size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sizediff
op_ge
id|max_size
)paren
r_return
l_int|1
suffix:semicolon
id|delta_buf
op_assign
id|diff_delta
c_func
(paren
id|old-&gt;data
comma
id|oldsize
comma
id|cur-&gt;data
comma
id|size
comma
op_amp
id|delta_size
comma
id|max_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|delta_buf
)paren
r_return
l_int|0
suffix:semicolon
id|cur_entry-&gt;delta
op_assign
id|old_entry
suffix:semicolon
id|cur_entry-&gt;delta_size
op_assign
id|delta_size
suffix:semicolon
id|cur_entry-&gt;depth
op_assign
id|old_entry-&gt;depth
op_plus
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|delta_buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|find_deltas
r_static
r_void
id|find_deltas
c_func
(paren
r_struct
id|object_entry
op_star
op_star
id|list
comma
r_int
id|window
comma
r_int
id|depth
)paren
(brace
r_int
id|i
comma
id|idx
suffix:semicolon
r_int
r_int
id|array_size
op_assign
id|window
op_star
r_sizeof
(paren
r_struct
id|unpacked
)paren
suffix:semicolon
r_struct
id|unpacked
op_star
id|array
op_assign
id|xmalloc
c_func
(paren
id|array_size
)paren
suffix:semicolon
id|memset
c_func
(paren
id|array
comma
l_int|0
comma
id|array_size
)paren
suffix:semicolon
id|i
op_assign
id|nr_objects
suffix:semicolon
id|idx
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
(brace
r_struct
id|object_entry
op_star
id|entry
op_assign
id|list
(braket
id|i
)braket
suffix:semicolon
r_struct
id|unpacked
op_star
id|n
op_assign
id|array
op_plus
id|idx
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|j
suffix:semicolon
id|free
c_func
(paren
id|n-&gt;data
)paren
suffix:semicolon
id|n-&gt;entry
op_assign
id|entry
suffix:semicolon
id|n-&gt;data
op_assign
id|read_sha1_file
c_func
(paren
id|entry-&gt;sha1
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
id|size
op_ne
id|entry-&gt;size
)paren
id|die
c_func
(paren
l_string|&quot;object %s inconsistent object length (%lu vs %lu)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
comma
id|size
comma
id|entry-&gt;size
)paren
suffix:semicolon
id|j
op_assign
id|window
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|j
OG
l_int|0
)paren
(brace
r_int
r_int
id|other_idx
op_assign
id|idx
op_plus
id|j
suffix:semicolon
r_struct
id|unpacked
op_star
id|m
suffix:semicolon
r_if
c_cond
(paren
id|other_idx
op_ge
id|window
)paren
id|other_idx
op_sub_assign
id|window
suffix:semicolon
id|m
op_assign
id|array
op_plus
id|other_idx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;entry
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|try_delta
c_func
(paren
id|n
comma
id|m
comma
id|depth
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|idx
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|window
)paren
id|idx
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
id|line
(braket
id|PATH_MAX
op_plus
l_int|20
)braket
suffix:semicolon
r_int
id|window
op_assign
l_int|10
comma
id|depth
op_assign
l_int|10
comma
id|pack_to_stdout
op_assign
l_int|0
suffix:semicolon
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
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--non-empty&quot;
comma
id|arg
)paren
)paren
(brace
id|non_empty
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
l_string|&quot;--incremental&quot;
comma
id|arg
)paren
)paren
(brace
id|incremental
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
id|strncmp
c_func
(paren
l_string|&quot;--window=&quot;
comma
id|arg
comma
l_int|9
)paren
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
id|window
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|9
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
(braket
l_int|9
)braket
op_logical_or
op_star
id|end
)paren
id|usage
c_func
(paren
id|pack_usage
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;--depth=&quot;
comma
id|arg
comma
l_int|8
)paren
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
id|depth
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|8
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
(braket
l_int|8
)braket
op_logical_or
op_star
id|end
)paren
id|usage
c_func
(paren
id|pack_usage
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
l_string|&quot;--stdout&quot;
comma
id|arg
)paren
)paren
(brace
id|pack_to_stdout
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|pack_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base_name
)paren
id|usage
c_func
(paren
id|pack_usage
)paren
suffix:semicolon
id|base_name
op_assign
id|arg
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pack_to_stdout
op_ne
op_logical_neg
id|base_name
)paren
id|usage
c_func
(paren
id|pack_usage
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
id|hash
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|line
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;expected sha1, got garbage&quot;
)paren
suffix:semicolon
id|hash
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|line
op_plus
l_int|40
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|c
)paren
)paren
r_continue
suffix:semicolon
id|hash
op_assign
id|hash
op_star
l_int|11
op_plus
id|c
suffix:semicolon
)brace
id|add_object_entry
c_func
(paren
id|sha1
comma
id|hash
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|non_empty
op_logical_and
op_logical_neg
id|nr_objects
)paren
r_return
l_int|0
suffix:semicolon
id|get_object_details
c_func
(paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Packing %d objects&bslash;n&quot;
comma
id|nr_objects
)paren
suffix:semicolon
id|sorted_by_sha
op_assign
id|create_sorted_list
c_func
(paren
id|sha1_sort
)paren
suffix:semicolon
id|sorted_by_type
op_assign
id|create_sorted_list
c_func
(paren
id|type_size_sort
)paren
suffix:semicolon
r_if
c_cond
(paren
id|window
op_logical_and
id|depth
)paren
id|find_deltas
c_func
(paren
id|sorted_by_type
comma
id|window
op_plus
l_int|1
comma
id|depth
)paren
suffix:semicolon
id|write_pack_file
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pack_to_stdout
)paren
id|write_index_file
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
