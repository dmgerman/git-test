macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;delta.h&quot;
DECL|variable|pack_usage
r_static
r_const
r_char
id|pack_usage
(braket
)braket
op_assign
l_string|&quot;git-pack-objects [--window=N] base-name &lt; object-list&quot;
suffix:semicolon
DECL|enum|object_type
r_enum
id|object_type
(brace
DECL|enumerator|OBJ_NONE
id|OBJ_NONE
comma
DECL|enumerator|OBJ_COMMIT
id|OBJ_COMMIT
comma
DECL|enumerator|OBJ_TREE
id|OBJ_TREE
comma
DECL|enumerator|OBJ_BLOB
id|OBJ_BLOB
comma
DECL|enumerator|OBJ_DELTA
id|OBJ_DELTA
singleline_comment|// NOTE! This is _not_ the same as a &quot;delta&quot; object in the filesystem
)brace
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
DECL|member|flags
r_int
r_int
id|flags
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
DECL|variable|delta_window
r_static
r_int
id|delta_window
op_assign
l_int|10
suffix:semicolon
DECL|variable|base_name
r_static
r_const
r_char
op_star
id|base_name
suffix:semicolon
DECL|struct|myfile
r_struct
id|myfile
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|chars
r_int
r_int
id|chars
suffix:semicolon
DECL|member|buffer
r_int
r_char
id|buffer
(braket
l_int|8192
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|create_file
r_static
id|FILE
op_star
id|create_file
c_func
(paren
r_const
r_char
op_star
id|suffix
)paren
(brace
r_static
r_char
id|filename
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|snprintf
c_func
(paren
id|filename
comma
id|PATH_MAX
comma
l_string|&quot;%s.%s&quot;
comma
id|base_name
comma
id|suffix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|PATH_MAX
)paren
id|die
c_func
(paren
l_string|&quot;you wascally wabbit, you&quot;
)paren
suffix:semicolon
r_return
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
)brace
DECL|function|fwrite_compressed
r_static
r_int
r_int
id|fwrite_compressed
c_func
(paren
r_void
op_star
id|in
comma
r_int
r_int
id|size
comma
id|FILE
op_star
id|f
)paren
(brace
id|z_stream
id|stream
suffix:semicolon
r_int
r_int
id|maxsize
suffix:semicolon
r_void
op_star
id|out
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|stream
comma
l_int|0
comma
r_sizeof
(paren
id|stream
)paren
)paren
suffix:semicolon
id|deflateInit
c_func
(paren
op_amp
id|stream
comma
id|Z_DEFAULT_COMPRESSION
)paren
suffix:semicolon
id|maxsize
op_assign
id|deflateBound
c_func
(paren
op_amp
id|stream
comma
id|size
)paren
suffix:semicolon
id|out
op_assign
id|xmalloc
c_func
(paren
id|maxsize
)paren
suffix:semicolon
multiline_comment|/* Compress it */
id|stream.next_in
op_assign
id|in
suffix:semicolon
id|stream.avail_in
op_assign
id|size
suffix:semicolon
id|stream.next_out
op_assign
id|out
suffix:semicolon
id|stream.avail_out
op_assign
id|maxsize
suffix:semicolon
r_while
c_loop
(paren
id|deflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
op_eq
id|Z_OK
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|deflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|size
op_assign
id|stream.total_out
suffix:semicolon
id|fwrite
c_func
(paren
id|out
comma
id|size
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
id|free
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
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
id|buf
comma
id|size
comma
id|otherbuf
comma
id|othersize
comma
op_amp
id|delta_size
)paren
suffix:semicolon
r_if
c_cond
(paren
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
DECL|function|write_object
r_static
r_int
r_int
id|write_object
c_func
(paren
id|FILE
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
r_char
id|header
(braket
l_int|21
)braket
suffix:semicolon
r_int
id|hdrlen
comma
id|datalen
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
multiline_comment|/*&n;&t; * The object header is a byte of &squot;type&squot; followed by four bytes of&n;&t; * length, except for deltas that has the 20 bytes of delta sha&n;&t; * instead.&n;&t; */
id|header
(braket
l_int|0
)braket
op_assign
l_string|&quot;.CTB&quot;
(braket
id|entry-&gt;type
)braket
suffix:semicolon
id|datalen
op_assign
id|htonl
c_func
(paren
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header
op_plus
l_int|1
comma
op_amp
id|datalen
comma
l_int|4
)paren
suffix:semicolon
id|hdrlen
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;delta
)paren
(brace
id|header
(braket
l_int|0
)braket
op_assign
l_char|&squot;D&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|header
op_plus
l_int|1
comma
id|entry-&gt;delta
comma
l_int|20
)paren
suffix:semicolon
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
id|hdrlen
op_assign
l_int|21
suffix:semicolon
)brace
id|fwrite
c_func
(paren
id|header
comma
id|hdrlen
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
id|datalen
op_assign
id|fwrite_compressed
c_func
(paren
id|buf
comma
id|size
comma
id|f
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
id|FILE
op_star
id|f
op_assign
id|create_file
c_func
(paren
l_string|&quot;pack&quot;
)paren
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|mb
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
id|objects
op_plus
id|i
suffix:semicolon
id|entry-&gt;offset
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
id|entry
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
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
id|FILE
op_star
id|f
op_assign
id|create_file
c_func
(paren
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
multiline_comment|/*&n;&t; * Write the first-level table (the list is sorted,&n;&t; * but we use a 256-entry lookup to be able to avoid&n;&t; * having to do eight extra binary search iterations)&n;&t; */
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
id|fwrite
c_func
(paren
id|array
comma
l_int|256
comma
r_sizeof
(paren
r_int
)paren
comma
id|f
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
id|fwrite
c_func
(paren
op_amp
id|offset
comma
l_int|4
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|entry-&gt;sha1
comma
l_int|20
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
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
id|buffer
(braket
l_int|128
)braket
suffix:semicolon
r_char
id|type
(braket
l_int|10
)braket
suffix:semicolon
r_int
r_int
id|mapsize
suffix:semicolon
id|z_stream
id|stream
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
id|map
op_assign
id|map_sha1_file
c_func
(paren
id|entry-&gt;sha1
comma
op_amp
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
id|die
c_func
(paren
l_string|&quot;unable to map %s&quot;
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
id|unpack_sha1_header
c_func
(paren
op_amp
id|stream
comma
id|map
comma
id|mapsize
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to unpack %s header&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
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
id|parse_sha1_header
c_func
(paren
id|buffer
comma
id|type
comma
op_amp
id|entry-&gt;size
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to parse %s header&quot;
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
multiline_comment|/*&n; * We search for deltas in a list sorted by type and by size, and&n; * walk the &quot;old&quot; chain backwards in the list, so if the type&n; * has changed or the size difference is too big, there&squot;s no point&n; * in even continuing the walk, since the other old objects are&n; * going to be even smaller or of a different type. So return -1&n; * once we determine that there&squot;s no point even trying.&n; */
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
multiline_comment|/* Size is guaranteed to be larger than or equal to oldsize */
id|size
op_assign
id|cur_entry-&gt;size
suffix:semicolon
id|oldsize
op_assign
id|old_entry-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|size
id|oldsize
OG
id|oldsize
op_div
l_int|4
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE!&n;&t; *&n;&t; * We always delta from the bigger to the smaller, since that&squot;s&n;&t; * more space-efficient (deletes don&squot;t have to say _what_ they&n;&t; * delete).&n;&t; */
id|delta_buf
op_assign
id|diff_delta
c_func
(paren
id|cur-&gt;data
comma
id|size
comma
id|old-&gt;data
comma
id|oldsize
comma
op_amp
id|delta_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|delta_buf
)paren
id|die
c_func
(paren
l_string|&quot;unable to create delta&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta_size
op_plus
l_int|20
OL
id|size
op_div
l_int|2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cur_entry-&gt;delta
op_logical_or
id|cur_entry-&gt;delta_size
OG
id|delta_size
)paren
(brace
id|cur_entry-&gt;delta
op_assign
id|old_entry
suffix:semicolon
id|cur_entry-&gt;delta_size
op_assign
id|delta_size
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|delta_buf
)paren
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
)paren
(brace
r_int
r_int
id|i
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
r_int
r_int
id|idx
op_assign
id|i
op_mod
id|window
suffix:semicolon
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
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|window
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
r_int
id|other_idx
op_assign
id|idx
l_int|1
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
OL
l_int|0
)paren
id|other_idx
op_add_assign
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
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
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
l_int|128
)braket
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
id|delta_window
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
id|add_object_entry
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
id|get_object_details
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
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
id|delta_window
)paren
id|find_deltas
c_func
(paren
id|sorted_by_type
comma
id|delta_window
)paren
suffix:semicolon
id|write_pack_file
c_func
(paren
)paren
suffix:semicolon
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
