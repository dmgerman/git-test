macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;delta.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;progress.h&quot;
macro_line|#include &quot;decorate.h&quot;
macro_line|#include &quot;fsck.h&quot;
DECL|variable|dry_run
DECL|variable|quiet
DECL|variable|recover
DECL|variable|has_errors
DECL|variable|strict
r_static
r_int
id|dry_run
comma
id|quiet
comma
id|recover
comma
id|has_errors
comma
id|strict
suffix:semicolon
DECL|variable|unpack_usage
r_static
r_const
r_char
id|unpack_usage
(braket
)braket
op_assign
l_string|&quot;git unpack-objects [-n] [-q] [-r] [--strict] &lt; pack-file&quot;
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
r_static
r_int
r_int
id|offset
comma
id|len
suffix:semicolon
DECL|variable|consumed_bytes
r_static
id|off_t
id|consumed_bytes
suffix:semicolon
DECL|variable|ctx
r_static
id|git_SHA_CTX
id|ctx
suffix:semicolon
multiline_comment|/*&n; * When running under --strict mode, objects whose reachability are&n; * suspect are kept in core without getting written in the object&n; * store.&n; */
DECL|struct|obj_buffer
r_struct
id|obj_buffer
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|obj_decorate
r_static
r_struct
id|decoration
id|obj_decorate
suffix:semicolon
DECL|function|lookup_object_buffer
r_static
r_struct
id|obj_buffer
op_star
id|lookup_object_buffer
c_func
(paren
r_struct
id|object
op_star
id|base
)paren
(brace
r_return
id|lookup_decoration
c_func
(paren
op_amp
id|obj_decorate
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|add_object_buffer
r_static
r_void
id|add_object_buffer
c_func
(paren
r_struct
id|object
op_star
id|object
comma
r_char
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|obj_buffer
op_star
id|obj
suffix:semicolon
id|obj
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|obj_buffer
)paren
)paren
suffix:semicolon
id|obj-&gt;buffer
op_assign
id|buffer
suffix:semicolon
id|obj-&gt;size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|add_decoration
c_func
(paren
op_amp
id|obj_decorate
comma
id|object
comma
id|obj
)paren
)paren
id|die
c_func
(paren
l_string|&quot;object %s tried to add buffer twice!&quot;
comma
id|sha1_to_hex
c_func
(paren
id|object-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
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
id|git_SHA1_Update
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
id|memmove
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
id|ssize_t
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
id|die_errno
c_func
(paren
l_string|&quot;read error on input&quot;
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
multiline_comment|/* make sure off_t is sufficiently large not to wrap */
r_if
c_cond
(paren
id|signed_add_overflows
c_func
(paren
id|consumed_bytes
comma
id|bytes
)paren
)paren
id|die
c_func
(paren
l_string|&quot;pack too large for current definition of off_t&quot;
)paren
suffix:semicolon
id|consumed_bytes
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
id|git_zstream
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
id|git_inflate_init
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
id|git_inflate
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
(brace
id|error
c_func
(paren
l_string|&quot;inflate returned %d&quot;
comma
id|ret
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|recover
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
id|has_errors
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|git_inflate_end
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
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|base_offset
id|off_t
id|base_offset
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
id|nr
comma
r_int
r_const
r_char
op_star
id|base_sha1
comma
id|off_t
id|base_offset
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
id|hashcpy
c_func
(paren
id|info-&gt;base_sha1
comma
id|base_sha1
)paren
suffix:semicolon
id|info-&gt;base_offset
op_assign
id|base_offset
suffix:semicolon
id|info-&gt;size
op_assign
id|size
suffix:semicolon
id|info-&gt;delta
op_assign
id|delta
suffix:semicolon
id|info-&gt;nr
op_assign
id|nr
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
DECL|struct|obj_info
r_struct
id|obj_info
(brace
DECL|member|offset
id|off_t
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
DECL|member|obj
r_struct
id|object
op_star
id|obj
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FLAG_OPEN
mdefine_line|#define FLAG_OPEN (1u&lt;&lt;20)
DECL|macro|FLAG_WRITTEN
mdefine_line|#define FLAG_WRITTEN (1u&lt;&lt;21)
DECL|variable|obj_list
r_static
r_struct
id|obj_info
op_star
id|obj_list
suffix:semicolon
DECL|variable|nr_objects
r_static
r_int
id|nr_objects
suffix:semicolon
multiline_comment|/*&n; * Called only from check_object() after it verified this object&n; * is Ok.&n; */
DECL|function|write_cached_object
r_static
r_void
id|write_cached_object
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|obj_buffer
op_star
id|obj_buf
op_assign
id|lookup_object_buffer
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|obj_buf-&gt;buffer
comma
id|obj_buf-&gt;size
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;failed to write object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|FLAG_WRITTEN
suffix:semicolon
)brace
multiline_comment|/*&n; * At the very end of the processing, write_rest() scans the objects&n; * that have reachability requirements and calls this function.&n; * Verify its reachability and validity recursively and write it out.&n; */
DECL|function|check_object
r_static
r_int
id|check_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_int
id|type
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|FLAG_WRITTEN
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_ANY
op_logical_and
id|obj-&gt;type
op_ne
id|type
)paren
id|die
c_func
(paren
l_string|&quot;object type mismatch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|obj-&gt;flags
op_amp
id|FLAG_OPEN
)paren
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_int
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|obj-&gt;sha1
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|obj-&gt;type
op_logical_or
id|type
op_le
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;object of unexpected type&quot;
)paren
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|FLAG_WRITTEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fsck_object
c_func
(paren
id|obj
comma
l_int|1
comma
id|fsck_error_function
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Error in object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fsck_walk
c_func
(paren
id|obj
comma
id|check_object
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Error on reachable objects of %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|write_cached_object
c_func
(paren
id|obj
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_rest
r_static
r_void
id|write_rest
c_func
(paren
r_void
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
id|nr_objects
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|obj_list
(braket
id|i
)braket
dot
id|obj
)paren
id|check_object
c_func
(paren
id|obj_list
(braket
id|i
)braket
dot
id|obj
comma
id|OBJ_ANY
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|added_object
c_func
(paren
r_int
id|nr
comma
r_enum
id|object_type
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
multiline_comment|/*&n; * Write out nr-th object from the list, now we know the contents&n; * of it.  Under --strict, this buffers structured objects in-core,&n; * to be checked at the end.&n; */
DECL|function|write_object
r_static
r_void
id|write_object
c_func
(paren
r_int
id|nr
comma
r_enum
id|object_type
id|type
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strict
)paren
(brace
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
r_typename
(paren
id|type
)paren
comma
id|obj_list
(braket
id|nr
)braket
dot
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
id|nr
comma
id|type
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
id|obj_list
(braket
id|nr
)braket
dot
id|obj
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_BLOB
)paren
(brace
r_struct
id|blob
op_star
id|blob
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
r_typename
(paren
id|type
)paren
comma
id|obj_list
(braket
id|nr
)braket
dot
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
id|nr
comma
id|type
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
id|blob
op_assign
id|lookup_blob
c_func
(paren
id|obj_list
(braket
id|nr
)braket
dot
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blob
)paren
id|blob-&gt;object.flags
op_or_assign
id|FLAG_WRITTEN
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;invalid blob object&quot;
)paren
suffix:semicolon
id|obj_list
(braket
id|nr
)braket
dot
id|obj
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_int
id|eaten
suffix:semicolon
id|hash_sha1_file
c_func
(paren
id|buf
comma
id|size
comma
r_typename
(paren
id|type
)paren
comma
id|obj_list
(braket
id|nr
)braket
dot
id|sha1
)paren
suffix:semicolon
id|added_object
c_func
(paren
id|nr
comma
id|type
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|obj
op_assign
id|parse_object_buffer
c_func
(paren
id|obj_list
(braket
id|nr
)braket
dot
id|sha1
comma
id|type
comma
id|size
comma
id|buf
comma
op_amp
id|eaten
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
id|die
c_func
(paren
l_string|&quot;invalid %s&quot;
comma
r_typename
(paren
id|type
)paren
)paren
suffix:semicolon
id|add_object_buffer
c_func
(paren
id|obj
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|FLAG_OPEN
suffix:semicolon
id|obj_list
(braket
id|nr
)braket
dot
id|obj
op_assign
id|obj
suffix:semicolon
)brace
)brace
DECL|function|resolve_delta
r_static
r_void
id|resolve_delta
c_func
(paren
r_int
id|nr
comma
r_enum
id|object_type
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
id|nr
comma
id|type
comma
id|result
comma
id|result_size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We now know the contents of an object (which is nr-th in the pack);&n; * resolve all the deltified objects that are based on it.&n; */
DECL|function|added_object
r_static
r_void
id|added_object
c_func
(paren
r_int
id|nr
comma
r_enum
id|object_type
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
id|hashcmp
c_func
(paren
id|info-&gt;base_sha1
comma
id|obj_list
(braket
id|nr
)braket
dot
id|sha1
)paren
op_logical_or
id|info-&gt;base_offset
op_eq
id|obj_list
(braket
id|nr
)braket
dot
id|offset
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
id|info-&gt;nr
comma
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
r_void
id|unpack_non_delta_entry
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
id|nr
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
r_if
c_cond
(paren
op_logical_neg
id|dry_run
op_logical_and
id|buf
)paren
id|write_object
c_func
(paren
id|nr
comma
id|type
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_else
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|resolve_against_held
r_static
r_int
id|resolve_against_held
c_func
(paren
r_int
id|nr
comma
r_const
r_int
r_char
op_star
id|base
comma
r_void
op_star
id|delta_data
comma
r_int
r_int
id|delta_size
)paren
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_struct
id|obj_buffer
op_star
id|obj_buffer
suffix:semicolon
id|obj
op_assign
id|lookup_object
c_func
(paren
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|0
suffix:semicolon
id|obj_buffer
op_assign
id|lookup_object_buffer
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_buffer
)paren
r_return
l_int|0
suffix:semicolon
id|resolve_delta
c_func
(paren
id|nr
comma
id|obj-&gt;type
comma
id|obj_buffer-&gt;buffer
comma
id|obj_buffer-&gt;size
comma
id|delta_data
comma
id|delta_size
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|unpack_delta_entry
r_static
r_void
id|unpack_delta_entry
c_func
(paren
r_enum
id|object_type
id|type
comma
r_int
r_int
id|delta_size
comma
r_int
id|nr
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
r_int
r_char
id|base_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_REF_DELTA
)paren
(brace
id|hashcpy
c_func
(paren
id|base_sha1
comma
id|fill
c_func
(paren
l_int|20
)paren
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
op_logical_or
op_logical_neg
id|delta_data
)paren
(brace
id|free
c_func
(paren
id|delta_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|base_sha1
)paren
)paren
suffix:semicolon
multiline_comment|/* Ok we have this one */
r_else
r_if
c_cond
(paren
id|resolve_against_held
c_func
(paren
id|nr
comma
id|base_sha1
comma
id|delta_data
comma
id|delta_size
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* we are done */
r_else
(brace
multiline_comment|/* cannot resolve yet --- queue it */
id|hashcpy
c_func
(paren
id|obj_list
(braket
id|nr
)braket
dot
id|sha1
comma
id|null_sha1
)paren
suffix:semicolon
id|add_delta_to_list
c_func
(paren
id|nr
comma
id|base_sha1
comma
l_int|0
comma
id|delta_data
comma
id|delta_size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
id|base_found
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|pack
comma
id|c
suffix:semicolon
id|off_t
id|base_offset
suffix:semicolon
r_int
id|lo
comma
id|mid
comma
id|hi
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
id|base_offset
op_assign
id|c
op_amp
l_int|127
suffix:semicolon
r_while
c_loop
(paren
id|c
op_amp
l_int|128
)paren
(brace
id|base_offset
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base_offset
op_logical_or
id|MSB
c_func
(paren
id|base_offset
comma
l_int|7
)paren
)paren
id|die
c_func
(paren
l_string|&quot;offset value overflow for delta base object&quot;
)paren
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
id|base_offset
op_assign
(paren
id|base_offset
op_lshift
l_int|7
)paren
op_plus
(paren
id|c
op_amp
l_int|127
)paren
suffix:semicolon
)brace
id|base_offset
op_assign
id|obj_list
(braket
id|nr
)braket
dot
id|offset
id|base_offset
suffix:semicolon
r_if
c_cond
(paren
id|base_offset
op_le
l_int|0
op_logical_or
id|base_offset
op_ge
id|obj_list
(braket
id|nr
)braket
dot
id|offset
)paren
id|die
c_func
(paren
l_string|&quot;offset value out of bound for delta base object&quot;
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
op_logical_or
op_logical_neg
id|delta_data
)paren
(brace
id|free
c_func
(paren
id|delta_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|lo
op_assign
l_int|0
suffix:semicolon
id|hi
op_assign
id|nr
suffix:semicolon
r_while
c_loop
(paren
id|lo
OL
id|hi
)paren
(brace
id|mid
op_assign
(paren
id|lo
op_plus
id|hi
)paren
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|base_offset
OL
id|obj_list
(braket
id|mid
)braket
dot
id|offset
)paren
(brace
id|hi
op_assign
id|mid
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|base_offset
OG
id|obj_list
(braket
id|mid
)braket
dot
id|offset
)paren
(brace
id|lo
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|hashcpy
c_func
(paren
id|base_sha1
comma
id|obj_list
(braket
id|mid
)braket
dot
id|sha1
)paren
suffix:semicolon
id|base_found
op_assign
op_logical_neg
id|is_null_sha1
c_func
(paren
id|base_sha1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|base_found
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The delta base object is itself a delta that&n;&t;&t;&t; * has not been resolved yet.&n;&t;&t;&t; */
id|hashcpy
c_func
(paren
id|obj_list
(braket
id|nr
)braket
dot
id|sha1
comma
id|null_sha1
)paren
suffix:semicolon
id|add_delta_to_list
c_func
(paren
id|nr
comma
id|null_sha1
comma
id|base_offset
comma
id|delta_data
comma
id|delta_size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|resolve_against_held
c_func
(paren
id|nr
comma
id|base_sha1
comma
id|delta_data
comma
id|delta_size
)paren
)paren
r_return
suffix:semicolon
id|base
op_assign
id|read_sha1_file
c_func
(paren
id|base_sha1
comma
op_amp
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
(brace
id|error
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
r_if
c_cond
(paren
op_logical_neg
id|recover
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
id|has_errors
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|resolve_delta
c_func
(paren
id|nr
comma
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
)brace
DECL|function|unpack_one
r_static
r_void
id|unpack_one
c_func
(paren
r_int
id|nr
)paren
(brace
r_int
id|shift
suffix:semicolon
r_int
r_char
op_star
id|pack
suffix:semicolon
r_int
r_int
id|size
comma
id|c
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
id|obj_list
(braket
id|nr
)braket
dot
id|offset
op_assign
id|consumed_bytes
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
comma
id|nr
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|OBJ_REF_DELTA
suffix:colon
r_case
id|OBJ_OFS_DELTA
suffix:colon
id|unpack_delta_entry
c_func
(paren
id|type
comma
id|size
comma
id|nr
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|error
c_func
(paren
l_string|&quot;bad object type %d&quot;
comma
id|type
)paren
suffix:semicolon
id|has_errors
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|recover
)paren
r_return
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
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
id|progress
op_star
id|progress
op_assign
l_int|NULL
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
l_string|&quot;unknown pack file version %&quot;
id|PRIu32
comma
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_version
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|progress
op_assign
id|start_progress
c_func
(paren
l_string|&quot;Unpacking objects&quot;
comma
id|nr_objects
)paren
suffix:semicolon
id|obj_list
op_assign
id|xcalloc
c_func
(paren
id|nr_objects
comma
r_sizeof
(paren
op_star
id|obj_list
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
(brace
id|unpack_one
c_func
(paren
id|i
)paren
suffix:semicolon
id|display_progress
c_func
(paren
id|progress
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|stop_progress
c_func
(paren
op_amp
id|progress
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
DECL|function|cmd_unpack_objects
r_int
id|cmd_unpack_objects
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
r_const
r_char
op_star
id|prefix
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
id|read_replace_refs
op_assign
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-r&quot;
)paren
)paren
(brace
id|recover
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
l_string|&quot;--strict&quot;
)paren
)paren
(brace
id|strict
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|arg
comma
l_string|&quot;--pack_header=&quot;
)paren
)paren
(brace
r_struct
id|pack_header
op_star
id|hdr
suffix:semicolon
r_char
op_star
id|c
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|pack_header
op_star
)paren
id|buffer
suffix:semicolon
id|hdr-&gt;hdr_signature
op_assign
id|htonl
c_func
(paren
id|PACK_SIGNATURE
)paren
suffix:semicolon
id|hdr-&gt;hdr_version
op_assign
id|htonl
c_func
(paren
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|14
comma
op_amp
id|c
comma
l_int|10
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|c
op_ne
l_char|&squot;,&squot;
)paren
id|die
c_func
(paren
l_string|&quot;bad %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|hdr-&gt;hdr_entries
op_assign
id|htonl
c_func
(paren
id|strtoul
c_func
(paren
id|c
op_plus
l_int|1
comma
op_amp
id|c
comma
l_int|10
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|c
)paren
id|die
c_func
(paren
l_string|&quot;bad %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
op_star
id|hdr
)paren
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
id|git_SHA1_Init
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
id|git_SHA1_Update
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
id|git_SHA1_Final
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
id|strict
)paren
id|write_rest
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|fill
c_func
(paren
l_int|20
)paren
comma
id|sha1
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
r_return
id|has_errors
suffix:semicolon
)brace
eof
