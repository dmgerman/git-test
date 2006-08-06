macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;delta.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;csum-file.h&quot;
DECL|variable|max_depth
r_static
r_int
id|max_depth
op_assign
l_int|10
suffix:semicolon
DECL|variable|object_count
r_static
r_int
r_int
id|object_count
suffix:semicolon
DECL|variable|duplicate_count
r_static
r_int
r_int
id|duplicate_count
suffix:semicolon
DECL|variable|packoff
r_static
r_int
r_int
id|packoff
suffix:semicolon
DECL|variable|overflow_count
r_static
r_int
r_int
id|overflow_count
suffix:semicolon
DECL|variable|packfd
r_static
r_int
id|packfd
suffix:semicolon
DECL|variable|current_depth
r_static
r_int
id|current_depth
suffix:semicolon
DECL|variable|lastdat
r_static
r_void
op_star
id|lastdat
suffix:semicolon
DECL|variable|lastdatlen
r_static
r_int
r_int
id|lastdatlen
suffix:semicolon
DECL|variable|lastsha1
r_static
r_int
r_char
id|lastsha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|packsha1
r_static
r_int
r_char
id|packsha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|struct|object_entry
r_struct
id|object_entry
(brace
DECL|member|next
r_struct
id|object_entry
op_star
id|next
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|overflow_object_entry
r_struct
id|overflow_object_entry
(brace
DECL|member|next
r_struct
id|overflow_object_entry
op_star
id|next
suffix:semicolon
DECL|member|oe
r_struct
id|object_entry
id|oe
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|pool_start
r_struct
id|object_entry
op_star
id|pool_start
suffix:semicolon
DECL|variable|pool_next
r_struct
id|object_entry
op_star
id|pool_next
suffix:semicolon
DECL|variable|pool_end
r_struct
id|object_entry
op_star
id|pool_end
suffix:semicolon
DECL|variable|overflow
r_struct
id|overflow_object_entry
op_star
id|overflow
suffix:semicolon
DECL|variable|table
r_struct
id|object_entry
op_star
id|table
(braket
l_int|1
op_lshift
l_int|16
)braket
suffix:semicolon
DECL|function|new_object
r_static
r_struct
id|object_entry
op_star
id|new_object
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|pool_next
op_ne
id|pool_end
)paren
(brace
r_struct
id|object_entry
op_star
id|e
op_assign
id|pool_next
op_increment
suffix:semicolon
id|memcpy
c_func
(paren
id|e-&gt;sha1
comma
id|sha1
comma
r_sizeof
(paren
id|e-&gt;sha1
)paren
)paren
suffix:semicolon
r_return
id|e
suffix:semicolon
)brace
r_else
(brace
r_struct
id|overflow_object_entry
op_star
id|e
suffix:semicolon
id|e
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|overflow_object_entry
)paren
)paren
suffix:semicolon
id|e-&gt;next
op_assign
id|overflow
suffix:semicolon
id|memcpy
c_func
(paren
id|e-&gt;oe.sha1
comma
id|sha1
comma
r_sizeof
(paren
id|e-&gt;oe.sha1
)paren
)paren
suffix:semicolon
id|overflow
op_assign
id|e
suffix:semicolon
id|overflow_count
op_increment
suffix:semicolon
r_return
op_amp
id|e-&gt;oe
suffix:semicolon
)brace
)brace
DECL|function|insert_object
r_static
r_struct
id|object_entry
op_star
id|insert_object
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
id|h
op_assign
id|sha1
(braket
l_int|0
)braket
op_lshift
l_int|8
op_or
id|sha1
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|object_entry
op_star
id|e
op_assign
id|table
(braket
id|h
)braket
suffix:semicolon
r_struct
id|object_entry
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|e
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|sha1
comma
id|e-&gt;sha1
comma
r_sizeof
(paren
id|e-&gt;sha1
)paren
)paren
)paren
r_return
id|e
suffix:semicolon
id|p
op_assign
id|e
suffix:semicolon
id|e
op_assign
id|e-&gt;next
suffix:semicolon
)brace
id|e
op_assign
id|new_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|e-&gt;next
op_assign
l_int|0
suffix:semicolon
id|e-&gt;offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|p-&gt;next
op_assign
id|e
suffix:semicolon
r_else
id|table
(braket
id|h
)braket
op_assign
id|e
suffix:semicolon
r_return
id|e
suffix:semicolon
)brace
DECL|function|yread
r_static
id|ssize_t
id|yread
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ret
OL
id|length
)paren
(brace
id|ssize_t
id|size
op_assign
id|xread
c_func
(paren
id|fd
comma
(paren
r_char
op_star
)paren
id|buffer
op_plus
id|ret
comma
id|length
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
r_return
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_add_assign
id|size
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ywrite
r_static
id|ssize_t
id|ywrite
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ret
OL
id|length
)paren
(brace
id|ssize_t
id|size
op_assign
id|xwrite
c_func
(paren
id|fd
comma
(paren
r_char
op_star
)paren
id|buffer
op_plus
id|ret
comma
id|length
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
(brace
r_return
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_add_assign
id|size
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|encode_header
r_static
r_int
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
DECL|function|write_blob
r_static
r_void
id|write_blob
c_func
(paren
r_void
op_star
id|dat
comma
r_int
r_int
id|datlen
)paren
(brace
id|z_stream
id|s
suffix:semicolon
r_void
op_star
id|out
comma
op_star
id|delta
suffix:semicolon
r_int
r_char
id|hdr
(braket
l_int|64
)braket
suffix:semicolon
r_int
r_int
id|hdrlen
comma
id|deltalen
suffix:semicolon
r_if
c_cond
(paren
id|lastdat
op_logical_and
id|current_depth
OL
id|max_depth
)paren
(brace
id|delta
op_assign
id|diff_delta
c_func
(paren
id|lastdat
comma
id|lastdatlen
comma
id|dat
comma
id|datlen
comma
op_amp
id|deltalen
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|delta
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|s
comma
l_int|0
comma
r_sizeof
(paren
id|s
)paren
)paren
suffix:semicolon
id|deflateInit
c_func
(paren
op_amp
id|s
comma
id|zlib_compression_level
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
)paren
(brace
id|current_depth
op_increment
suffix:semicolon
id|s.next_in
op_assign
id|delta
suffix:semicolon
id|s.avail_in
op_assign
id|deltalen
suffix:semicolon
id|hdrlen
op_assign
id|encode_header
c_func
(paren
id|OBJ_DELTA
comma
id|deltalen
comma
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
id|hdr
comma
id|hdrlen
)paren
op_ne
id|hdrlen
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t write object header: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
id|lastsha1
comma
r_sizeof
(paren
id|lastsha1
)paren
)paren
op_ne
r_sizeof
(paren
id|lastsha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t write object base: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|packoff
op_add_assign
id|hdrlen
op_plus
r_sizeof
(paren
id|lastsha1
)paren
suffix:semicolon
)brace
r_else
(brace
id|current_depth
op_assign
l_int|0
suffix:semicolon
id|s.next_in
op_assign
id|dat
suffix:semicolon
id|s.avail_in
op_assign
id|datlen
suffix:semicolon
id|hdrlen
op_assign
id|encode_header
c_func
(paren
id|OBJ_BLOB
comma
id|datlen
comma
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
id|hdr
comma
id|hdrlen
)paren
op_ne
id|hdrlen
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t write object header: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|packoff
op_add_assign
id|hdrlen
suffix:semicolon
)brace
id|s.avail_out
op_assign
id|deflateBound
c_func
(paren
op_amp
id|s
comma
id|s.avail_in
)paren
suffix:semicolon
id|s.next_out
op_assign
id|out
op_assign
id|xmalloc
c_func
(paren
id|s.avail_out
)paren
suffix:semicolon
r_while
c_loop
(paren
id|deflate
c_func
(paren
op_amp
id|s
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
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
id|out
comma
id|s.total_out
)paren
op_ne
id|s.total_out
)paren
id|die
c_func
(paren
l_string|&quot;Failed writing compressed data %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|packoff
op_add_assign
id|s.total_out
suffix:semicolon
id|free
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
)paren
id|free
c_func
(paren
id|delta
)paren
suffix:semicolon
)brace
DECL|function|init_pack_header
r_static
r_void
id|init_pack_header
c_func
(paren
)paren
(brace
r_const
r_char
op_star
id|magic
op_assign
l_string|&quot;PACK&quot;
suffix:semicolon
r_int
r_int
id|version
op_assign
l_int|2
suffix:semicolon
r_int
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
id|version
op_assign
id|htonl
c_func
(paren
id|version
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
(paren
r_char
op_star
)paren
id|magic
comma
l_int|4
)paren
op_ne
l_int|4
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t write pack magic: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
op_amp
id|version
comma
l_int|4
)paren
op_ne
l_int|4
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t write pack version: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
op_amp
id|zero
comma
l_int|4
)paren
op_ne
l_int|4
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t write 0 object count: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|packoff
op_assign
l_int|4
op_star
l_int|3
suffix:semicolon
)brace
DECL|function|fixup_header_footer
r_static
r_void
id|fixup_header_footer
c_func
(paren
)paren
(brace
id|SHA_CTX
id|c
suffix:semicolon
r_char
id|hdr
(braket
l_int|8
)braket
suffix:semicolon
r_int
r_int
id|cnt
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|packfd
comma
l_int|0
comma
id|SEEK_SET
)paren
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Failed seeking to start: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|SHA1_Init
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|yread
c_func
(paren
id|packfd
comma
id|hdr
comma
l_int|8
)paren
op_ne
l_int|8
)paren
id|die
c_func
(paren
l_string|&quot;Failed reading header: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|hdr
comma
l_int|8
)paren
suffix:semicolon
id|cnt
op_assign
id|htonl
c_func
(paren
id|object_count
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
op_amp
id|cnt
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
op_amp
id|cnt
comma
l_int|4
)paren
op_ne
l_int|4
)paren
id|die
c_func
(paren
l_string|&quot;Failed writing object count: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|buf
op_assign
id|xmalloc
c_func
(paren
l_int|128
op_star
l_int|1024
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|n
op_assign
id|xread
c_func
(paren
id|packfd
comma
id|buf
comma
l_int|128
op_star
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|buf
comma
id|n
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
id|SHA1_Final
c_func
(paren
id|packsha1
comma
op_amp
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ywrite
c_func
(paren
id|packfd
comma
id|packsha1
comma
r_sizeof
(paren
id|packsha1
)paren
)paren
op_ne
r_sizeof
(paren
id|packsha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Failed writing pack checksum: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|oecmp
r_static
r_int
id|oecmp
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
(paren
r_struct
id|object_entry
op_star
op_star
)paren
id|_a
)paren
suffix:semicolon
r_struct
id|object_entry
op_star
id|b
op_assign
op_star
(paren
(paren
r_struct
id|object_entry
op_star
op_star
)paren
id|_b
)paren
suffix:semicolon
r_return
id|memcmp
c_func
(paren
id|a-&gt;sha1
comma
id|b-&gt;sha1
comma
r_sizeof
(paren
id|a-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|write_index
r_static
r_void
id|write_index
c_func
(paren
r_const
r_char
op_star
id|idx_name
)paren
(brace
r_struct
id|sha1file
op_star
id|f
suffix:semicolon
r_struct
id|object_entry
op_star
op_star
id|idx
comma
op_star
op_star
id|c
comma
op_star
op_star
id|last
suffix:semicolon
r_struct
id|object_entry
op_star
id|e
suffix:semicolon
r_struct
id|overflow_object_entry
op_star
id|o
suffix:semicolon
r_int
r_int
id|array
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Build the sorted table of object IDs. */
id|idx
op_assign
id|xmalloc
c_func
(paren
id|object_count
op_star
r_sizeof
(paren
r_struct
id|object_entry
op_star
)paren
)paren
suffix:semicolon
id|c
op_assign
id|idx
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|pool_start
suffix:semicolon
id|e
op_ne
id|pool_next
suffix:semicolon
id|e
op_increment
)paren
op_star
id|c
op_increment
op_assign
id|e
suffix:semicolon
r_for
c_loop
(paren
id|o
op_assign
id|overflow
suffix:semicolon
id|o
suffix:semicolon
id|o
op_assign
id|o-&gt;next
)paren
op_star
id|c
op_increment
op_assign
op_amp
id|o-&gt;oe
suffix:semicolon
id|last
op_assign
id|idx
op_plus
id|object_count
suffix:semicolon
id|qsort
c_func
(paren
id|idx
comma
id|object_count
comma
r_sizeof
(paren
r_struct
id|object_entry
op_star
)paren
comma
id|oecmp
)paren
suffix:semicolon
multiline_comment|/* Generate the fan-out array. */
id|c
op_assign
id|idx
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
r_struct
id|object_entry
op_star
op_star
id|next
op_assign
id|c
suffix:semicolon
suffix:semicolon
r_while
c_loop
(paren
id|next
OL
id|last
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|next
)paren
op_member_access_from_pointer
id|sha1
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
id|idx
)paren
suffix:semicolon
id|c
op_assign
id|next
suffix:semicolon
)brace
id|f
op_assign
id|sha1create
c_func
(paren
l_string|&quot;%s&quot;
comma
id|idx_name
)paren
suffix:semicolon
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
r_for
c_loop
(paren
id|c
op_assign
id|idx
suffix:semicolon
id|c
op_ne
id|last
suffix:semicolon
id|c
op_increment
)paren
(brace
r_int
r_int
id|offset
op_assign
id|htonl
c_func
(paren
(paren
op_star
id|c
)paren
op_member_access_from_pointer
id|offset
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
(paren
op_star
id|c
)paren
op_member_access_from_pointer
id|sha1
comma
r_sizeof
(paren
(paren
op_star
id|c
)paren
op_member_access_from_pointer
id|sha1
)paren
)paren
suffix:semicolon
)brace
id|sha1write
c_func
(paren
id|f
comma
id|packsha1
comma
r_sizeof
(paren
id|packsha1
)paren
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
id|free
c_func
(paren
id|idx
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
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
)paren
(brace
r_const
r_char
op_star
id|base_name
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|est_obj_cnt
op_assign
id|atoi
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_char
op_star
id|pack_name
suffix:semicolon
r_char
op_star
id|idx_name
suffix:semicolon
id|pack_name
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base_name
)paren
op_plus
l_int|6
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|pack_name
comma
l_string|&quot;%s.pack&quot;
comma
id|base_name
)paren
suffix:semicolon
id|idx_name
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base_name
)paren
op_plus
l_int|5
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|idx_name
comma
l_string|&quot;%s.idx&quot;
comma
id|base_name
)paren
suffix:semicolon
id|packfd
op_assign
id|open
c_func
(paren
id|pack_name
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_TRUNC
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|packfd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t create pack file %s: %s&quot;
comma
id|pack_name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|pool_start
op_assign
id|xmalloc
c_func
(paren
id|est_obj_cnt
op_star
r_sizeof
(paren
r_struct
id|object_entry
)paren
)paren
suffix:semicolon
id|pool_next
op_assign
id|pool_start
suffix:semicolon
id|pool_end
op_assign
id|pool_start
op_plus
id|est_obj_cnt
suffix:semicolon
id|init_pack_header
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|datlen
suffix:semicolon
r_int
id|hdrlen
suffix:semicolon
r_void
op_star
id|dat
suffix:semicolon
r_char
id|hdr
(braket
l_int|128
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|SHA_CTX
id|c
suffix:semicolon
r_struct
id|object_entry
op_star
id|e
suffix:semicolon
r_if
c_cond
(paren
id|yread
c_func
(paren
l_int|0
comma
op_amp
id|datlen
comma
l_int|4
)paren
op_ne
l_int|4
)paren
r_break
suffix:semicolon
id|dat
op_assign
id|xmalloc
c_func
(paren
id|datlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|yread
c_func
(paren
l_int|0
comma
id|dat
comma
id|datlen
)paren
op_ne
id|datlen
)paren
r_break
suffix:semicolon
id|hdrlen
op_assign
id|sprintf
c_func
(paren
id|hdr
comma
l_string|&quot;blob %lu&quot;
comma
id|datlen
)paren
op_plus
l_int|1
suffix:semicolon
id|SHA1_Init
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|hdr
comma
id|hdrlen
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|dat
comma
id|datlen
)paren
suffix:semicolon
id|SHA1_Final
c_func
(paren
id|sha1
comma
op_amp
id|c
)paren
suffix:semicolon
id|e
op_assign
id|insert_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;offset
)paren
(brace
id|e-&gt;offset
op_assign
id|packoff
suffix:semicolon
id|write_blob
c_func
(paren
id|dat
comma
id|datlen
)paren
suffix:semicolon
id|object_count
op_increment
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lastdat
)paren
id|free
c_func
(paren
id|lastdat
)paren
suffix:semicolon
id|lastdat
op_assign
id|dat
suffix:semicolon
id|lastdatlen
op_assign
id|datlen
suffix:semicolon
id|memcpy
c_func
(paren
id|lastsha1
comma
id|sha1
comma
r_sizeof
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|duplicate_count
op_increment
suffix:semicolon
id|free
c_func
(paren
id|dat
)paren
suffix:semicolon
)brace
)brace
id|fixup_header_footer
c_func
(paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|packfd
)paren
suffix:semicolon
id|write_index
c_func
(paren
id|idx_name
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%lu objects, %lu duplicates, %lu pool overflow&bslash;n&quot;
comma
id|object_count
comma
id|duplicate_count
comma
id|overflow_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
