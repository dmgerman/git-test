macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;delta.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &lt;sys/time.h&gt;
DECL|variable|dry_run
DECL|variable|quiet
r_static
r_int
id|dry_run
comma
id|quiet
suffix:semicolon
DECL|variable|unpack_usage
r_static
r_const
r_char
id|unpack_usage
(braket
)braket
op_assign
l_string|&quot;git-unpack-objects [-n] [-q] &lt; pack-file&quot;
suffix:semicolon
multiline_comment|/* We always read in 4kB chunks. */
DECL|variable|buffer
r_static
r_int
r_char
id|buffer
(braket
l_int|4096
)braket
suffix:semicolon
DECL|variable|offset
DECL|variable|len
DECL|variable|eof
r_static
r_int
r_int
id|offset
comma
id|len
comma
id|eof
suffix:semicolon
DECL|variable|ctx
r_static
id|SHA_CTX
id|ctx
suffix:semicolon
multiline_comment|/*&n; * Make sure at least &quot;min&quot; bytes are available in the buffer, and&n; * return the pointer to the buffer.&n; */
DECL|function|fill
r_static
r_void
op_star
id|fill
c_func
(paren
r_int
id|min
)paren
(brace
r_if
c_cond
(paren
id|min
op_le
id|len
)paren
r_return
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|eof
)paren
id|die
c_func
(paren
l_string|&quot;unable to fill input&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|min
OG
r_sizeof
(paren
id|buffer
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot fill %d bytes&quot;
comma
id|min
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|buffer
comma
id|offset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|buffer
op_plus
id|offset
comma
id|len
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
r_do
(brace
r_int
id|ret
op_assign
id|xread
c_func
(paren
l_int|0
comma
id|buffer
op_plus
id|len
comma
r_sizeof
(paren
id|buffer
)paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;early EOF&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;read error on input: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|ret
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OL
id|min
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|use
r_static
r_void
id|use
c_func
(paren
r_int
id|bytes
)paren
(brace
r_if
c_cond
(paren
id|bytes
OG
id|len
)paren
id|die
c_func
(paren
l_string|&quot;used more bytes than were available&quot;
)paren
suffix:semicolon
id|len
op_sub_assign
id|bytes
suffix:semicolon
id|offset
op_add_assign
id|bytes
suffix:semicolon
)brace
DECL|function|get_data
r_static
r_void
op_star
id|get_data
c_func
(paren
r_int
r_int
id|size
)paren
(brace
id|z_stream
id|stream
suffix:semicolon
r_void
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
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
id|stream.next_out
op_assign
id|buf
suffix:semicolon
id|stream.avail_out
op_assign
id|size
suffix:semicolon
id|stream.next_in
op_assign
id|fill
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|stream.avail_in
op_assign
id|len
suffix:semicolon
id|inflateInit
c_func
(paren
op_amp
id|stream
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
id|ret
op_assign
id|inflate
c_func
(paren
op_amp
id|stream
comma
l_int|0
)paren
suffix:semicolon
id|use
c_func
(paren
id|len
id|stream.avail_in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stream.total_out
op_eq
id|size
op_logical_and
id|ret
op_eq
id|Z_STREAM_END
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|Z_OK
)paren
id|die
c_func
(paren
l_string|&quot;inflate returned %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|stream.next_in
op_assign
id|fill
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|stream.avail_in
op_assign
id|len
suffix:semicolon
)brace
id|inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|struct|delta_info
r_struct
id|delta_info
(brace
DECL|member|base_sha1
r_int
r_char
id|base_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|delta
r_void
op_star
id|delta
suffix:semicolon
DECL|member|next
r_struct
id|delta_info
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|delta_list
r_static
r_struct
id|delta_info
op_star
id|delta_list
suffix:semicolon
DECL|function|add_delta_to_list
r_static
r_void
id|add_delta_to_list
c_func
(paren
r_int
r_char
op_star
id|base_sha1
comma
r_void
op_star
id|delta
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|delta_info
op_star
id|info
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|info-&gt;base_sha1
comma
id|base_sha1
comma
l_int|20
)paren
suffix:semicolon
id|info-&gt;size
op_assign
id|size
suffix:semicolon
id|info-&gt;delta
op_assign
id|delta
suffix:semicolon
id|info-&gt;next
op_assign
id|delta_list
suffix:semicolon
id|delta_list
op_assign
id|info
suffix:semicolon
)brace
r_static
r_void
id|added_object
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|type
comma
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|function|write_object
r_static
r_void
id|write_object
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
r_const
r_char
op_star
id|type
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
id|write_sha1_file
c_func
(paren
id|buf
comma
id|size
comma
id|type
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;failed to write object&quot;
)paren
suffix:semicolon
id|added_object
c_func
(paren
id|sha1
comma
id|type
comma
id|buf
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|resolve_delta
r_static
r_int
id|resolve_delta
c_func
(paren
r_const
r_char
op_star
id|type
comma
r_void
op_star
id|base
comma
r_int
r_int
id|base_size
comma
r_void
op_star
id|delta
comma
r_int
r_int
id|delta_size
)paren
(brace
r_void
op_star
id|result
suffix:semicolon
r_int
r_int
id|result_size
suffix:semicolon
id|result
op_assign
id|patch_delta
c_func
(paren
id|base
comma
id|base_size
comma
id|delta
comma
id|delta_size
comma
op_amp
id|result_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
id|die
c_func
(paren
l_string|&quot;failed to apply delta&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|delta
)paren
suffix:semicolon
id|write_object
c_func
(paren
id|result
comma
id|result_size
comma
id|type
)paren
suffix:semicolon
id|free
c_func
(paren
id|result
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|added_object
r_static
r_void
id|added_object
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|type
comma
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|delta_info
op_star
op_star
id|p
op_assign
op_amp
id|delta_list
suffix:semicolon
r_struct
id|delta_info
op_star
id|info
suffix:semicolon
r_while
c_loop
(paren
(paren
id|info
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|info-&gt;base_sha1
comma
id|sha1
comma
l_int|20
)paren
)paren
(brace
op_star
id|p
op_assign
id|info-&gt;next
suffix:semicolon
id|p
op_assign
op_amp
id|delta_list
suffix:semicolon
id|resolve_delta
c_func
(paren
id|type
comma
id|data
comma
id|size
comma
id|info-&gt;delta
comma
id|info-&gt;size
)paren
suffix:semicolon
id|free
c_func
(paren
id|info
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|info-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|unpack_non_delta_entry
r_static
r_int
id|unpack_non_delta_entry
c_func
(paren
r_enum
id|object_type
id|kind
comma
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|buf
op_assign
id|get_data
c_func
(paren
id|size
)paren
suffix:semicolon
r_const
r_char
op_star
id|type
suffix:semicolon
r_switch
c_cond
(paren
id|kind
)paren
(brace
r_case
id|OBJ_COMMIT
suffix:colon
id|type
op_assign
l_string|&quot;commit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_TREE
suffix:colon
id|type
op_assign
l_string|&quot;tree&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_BLOB
suffix:colon
id|type
op_assign
l_string|&quot;blob&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_TAG
suffix:colon
id|type
op_assign
l_string|&quot;tag&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;bad type %d&quot;
comma
id|kind
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dry_run
)paren
id|write_object
c_func
(paren
id|buf
comma
id|size
comma
id|type
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unpack_delta_entry
r_static
r_int
id|unpack_delta_entry
c_func
(paren
r_int
r_int
id|delta_size
)paren
(brace
r_void
op_star
id|delta_data
comma
op_star
id|base
suffix:semicolon
r_int
r_int
id|base_size
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|base_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memcpy
c_func
(paren
id|base_sha1
comma
id|fill
c_func
(paren
l_int|20
)paren
comma
l_int|20
)paren
suffix:semicolon
id|use
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|delta_data
op_assign
id|get_data
c_func
(paren
id|delta_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dry_run
)paren
(brace
id|free
c_func
(paren
id|delta_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|base_sha1
)paren
)paren
(brace
id|add_delta_to_list
c_func
(paren
id|base_sha1
comma
id|delta_data
comma
id|delta_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|base
op_assign
id|read_sha1_file
c_func
(paren
id|base_sha1
comma
id|type
comma
op_amp
id|base_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
id|die
c_func
(paren
l_string|&quot;failed to read delta-pack base object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|base_sha1
)paren
)paren
suffix:semicolon
id|result
op_assign
id|resolve_delta
c_func
(paren
id|type
comma
id|base
comma
id|base_size
comma
id|delta_data
comma
id|delta_size
)paren
suffix:semicolon
id|free
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|unpack_one
r_static
r_void
id|unpack_one
c_func
(paren
r_int
id|nr
comma
r_int
id|total
)paren
(brace
r_int
id|shift
suffix:semicolon
r_int
r_char
op_star
id|pack
comma
id|c
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
id|pack
op_assign
id|fill
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|c
op_assign
op_star
id|pack
suffix:semicolon
id|use
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|type
op_assign
(paren
id|c
op_rshift
l_int|4
)paren
op_amp
l_int|7
suffix:semicolon
id|size
op_assign
(paren
id|c
op_amp
l_int|15
)paren
suffix:semicolon
id|shift
op_assign
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|c
op_amp
l_int|0x80
)paren
(brace
id|pack
op_assign
id|fill
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|c
op_assign
op_star
id|pack
op_increment
suffix:semicolon
id|use
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|size
op_add_assign
(paren
id|c
op_amp
l_int|0x7f
)paren
op_lshift
id|shift
suffix:semicolon
id|shift
op_add_assign
l_int|7
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
(brace
r_static
r_int
r_int
id|last_sec
suffix:semicolon
r_static
r_int
id|last_percent
suffix:semicolon
r_struct
id|timeval
id|now
suffix:semicolon
r_int
id|percentage
op_assign
(paren
id|nr
op_star
l_int|100
)paren
op_div
id|total
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|now
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|percentage
op_ne
id|last_percent
op_logical_or
id|now.tv_sec
op_ne
id|last_sec
)paren
(brace
id|last_sec
op_assign
id|now.tv_sec
suffix:semicolon
id|last_percent
op_assign
id|percentage
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%4u%% (%u/%u) done&bslash;r&quot;
comma
id|percentage
comma
id|nr
comma
id|total
)paren
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|OBJ_COMMIT
suffix:colon
r_case
id|OBJ_TREE
suffix:colon
r_case
id|OBJ_BLOB
suffix:colon
r_case
id|OBJ_TAG
suffix:colon
id|unpack_non_delta_entry
c_func
(paren
id|type
comma
id|size
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|OBJ_DELTA
suffix:colon
id|unpack_delta_entry
c_func
(paren
id|size
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;bad object type %d&quot;
comma
id|type
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We unpack from the end, older files first. Now, usually&n; * there are deltas etc, so we&squot;ll not actually write the&n; * objects in that order, but we might as well try..&n; */
DECL|function|unpack_all
r_static
r_void
id|unpack_all
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pack_header
op_star
id|hdr
op_assign
id|fill
c_func
(paren
r_sizeof
(paren
r_struct
id|pack_header
)paren
)paren
suffix:semicolon
r_int
id|nr_objects
op_assign
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_entries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_signature
)paren
op_ne
id|PACK_SIGNATURE
)paren
id|die
c_func
(paren
l_string|&quot;bad pack file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pack_version_ok
c_func
(paren
id|hdr-&gt;hdr_version
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unknown pack file version %d&quot;
comma
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_version
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unpacking %d objects&bslash;n&quot;
comma
id|nr_objects
)paren
suffix:semicolon
id|use
c_func
(paren
r_sizeof
(paren
r_struct
id|pack_header
)paren
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
id|unpack_one
c_func
(paren
id|i
op_plus
l_int|1
comma
id|nr_objects
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta_list
)paren
id|die
c_func
(paren
l_string|&quot;unresolved deltas left after unpacking&quot;
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
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|quiet
op_assign
op_logical_neg
id|isatty
c_func
(paren
l_int|2
)paren
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
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
(brace
id|dry_run
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
id|arg
comma
l_string|&quot;-q&quot;
)paren
)paren
(brace
id|quiet
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|unpack_usage
)paren
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t take any non-flag arguments now.. Maybe some day */
id|usage
c_func
(paren
id|unpack_usage
)paren
suffix:semicolon
)brace
id|SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
id|unpack_all
c_func
(paren
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|buffer
comma
id|offset
)paren
suffix:semicolon
id|SHA1_Final
c_func
(paren
id|sha1
comma
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|fill
c_func
(paren
l_int|20
)paren
comma
id|sha1
comma
l_int|20
)paren
)paren
id|die
c_func
(paren
l_string|&quot;final sha1 did not match&quot;
)paren
suffix:semicolon
id|use
c_func
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Write the last part of the buffer to stdout */
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
id|ret
op_assign
id|xwrite
c_func
(paren
l_int|1
comma
id|buffer
op_plus
id|offset
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|len
op_sub_assign
id|ret
suffix:semicolon
id|offset
op_add_assign
id|ret
suffix:semicolon
)brace
multiline_comment|/* All done */
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
