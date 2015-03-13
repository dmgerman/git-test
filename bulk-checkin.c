multiline_comment|/*&n; * Copyright (c) 2011, Google Inc.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;bulk-checkin.h&quot;
macro_line|#include &quot;csum-file.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|variable|pack_compression_level
r_static
r_int
id|pack_compression_level
op_assign
id|Z_DEFAULT_COMPRESSION
suffix:semicolon
DECL|struct|bulk_checkin_state
r_static
r_struct
id|bulk_checkin_state
(brace
DECL|member|plugged
r_int
id|plugged
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pack_tmp_name
r_char
op_star
id|pack_tmp_name
suffix:semicolon
DECL|member|f
r_struct
id|sha1file
op_star
id|f
suffix:semicolon
DECL|member|offset
id|off_t
id|offset
suffix:semicolon
DECL|member|pack_idx_opts
r_struct
id|pack_idx_option
id|pack_idx_opts
suffix:semicolon
DECL|member|written
r_struct
id|pack_idx_entry
op_star
op_star
id|written
suffix:semicolon
DECL|member|alloc_written
r_uint32
id|alloc_written
suffix:semicolon
DECL|member|nr_written
r_uint32
id|nr_written
suffix:semicolon
DECL|variable|state
)brace
id|state
suffix:semicolon
DECL|function|finish_bulk_checkin
r_static
r_void
id|finish_bulk_checkin
c_func
(paren
r_struct
id|bulk_checkin_state
op_star
id|state
)paren
(brace
r_struct
id|object_id
id|oid
suffix:semicolon
r_struct
id|strbuf
id|packname
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;f
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;nr_written
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|state-&gt;f-&gt;fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|state-&gt;pack_tmp_name
)paren
suffix:semicolon
r_goto
id|clear_exit
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state-&gt;nr_written
op_eq
l_int|1
)paren
(brace
id|sha1close
c_func
(paren
id|state-&gt;f
comma
id|oid.hash
comma
id|CSUM_FSYNC
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|fd
op_assign
id|sha1close
c_func
(paren
id|state-&gt;f
comma
id|oid.hash
comma
l_int|0
)paren
suffix:semicolon
id|fixup_pack_header_footer
c_func
(paren
id|fd
comma
id|oid.hash
comma
id|state-&gt;pack_tmp_name
comma
id|state-&gt;nr_written
comma
id|oid.hash
comma
id|state-&gt;offset
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|packname
comma
l_string|&quot;%s/pack/pack-&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|finish_tmp_packfile
c_func
(paren
op_amp
id|packname
comma
id|state-&gt;pack_tmp_name
comma
id|state-&gt;written
comma
id|state-&gt;nr_written
comma
op_amp
id|state-&gt;pack_idx_opts
comma
id|oid.hash
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
id|state-&gt;nr_written
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|state-&gt;written
(braket
id|i
)braket
)paren
suffix:semicolon
id|clear_exit
suffix:colon
id|free
c_func
(paren
id|state-&gt;written
)paren
suffix:semicolon
id|memset
c_func
(paren
id|state
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|state
)paren
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|packname
)paren
suffix:semicolon
multiline_comment|/* Make objects we just wrote available to ourselves */
id|reprepare_packed_git
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|already_written
r_static
r_int
id|already_written
c_func
(paren
r_struct
id|bulk_checkin_state
op_star
id|state
comma
r_int
r_char
id|sha1
(braket
)braket
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* The object may already exist in the repository */
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Might want to keep the list sorted */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|state-&gt;nr_written
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|state-&gt;written
(braket
id|i
)braket
op_member_access_from_pointer
id|sha1
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* This is a new object we need to keep */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the contents from fd for size bytes, streaming it to the&n; * packfile in state while updating the hash in ctx. Signal a failure&n; * by returning a negative value when the resulting pack would exceed&n; * the pack size limit and this is not the first object in the pack,&n; * so that the caller can discard what we wrote from the current pack&n; * by truncating it and opening a new one. The caller will then call&n; * us again after rewinding the input fd.&n; *&n; * The already_hashed_to pointer is kept untouched by the caller to&n; * make sure we do not hash the same byte when we are called&n; * again. This way, the caller does not have to checkpoint its hash&n; * status before calling us just in case we ask it to call us again&n; * with a new pack.&n; */
DECL|function|stream_to_pack
r_static
r_int
id|stream_to_pack
c_func
(paren
r_struct
id|bulk_checkin_state
op_star
id|state
comma
id|git_SHA_CTX
op_star
id|ctx
comma
id|off_t
op_star
id|already_hashed_to
comma
r_int
id|fd
comma
r_int
id|size
comma
r_enum
id|object_type
id|type
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
)paren
(brace
id|git_zstream
id|s
suffix:semicolon
r_int
r_char
id|obuf
(braket
l_int|16384
)braket
suffix:semicolon
r_int
id|hdrlen
suffix:semicolon
r_int
id|status
op_assign
id|Z_OK
suffix:semicolon
r_int
id|write_object
op_assign
(paren
id|flags
op_amp
id|HASH_WRITE_OBJECT
)paren
suffix:semicolon
id|off_t
id|offset
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
id|git_deflate_init
c_func
(paren
op_amp
id|s
comma
id|pack_compression_level
)paren
suffix:semicolon
id|hdrlen
op_assign
id|encode_in_pack_object_header
c_func
(paren
id|type
comma
id|size
comma
id|obuf
)paren
suffix:semicolon
id|s.next_out
op_assign
id|obuf
op_plus
id|hdrlen
suffix:semicolon
id|s.avail_out
op_assign
r_sizeof
(paren
id|obuf
)paren
id|hdrlen
suffix:semicolon
r_while
c_loop
(paren
id|status
op_ne
id|Z_STREAM_END
)paren
(brace
r_int
r_char
id|ibuf
(braket
l_int|16384
)braket
suffix:semicolon
r_if
c_cond
(paren
id|size
op_logical_and
op_logical_neg
id|s.avail_in
)paren
(brace
id|ssize_t
id|rsize
op_assign
id|size
OL
r_sizeof
(paren
id|ibuf
)paren
ques
c_cond
id|size
suffix:colon
r_sizeof
(paren
id|ibuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_in_full
c_func
(paren
id|fd
comma
id|ibuf
comma
id|rsize
)paren
op_ne
id|rsize
)paren
id|die
c_func
(paren
l_string|&quot;failed to read %d bytes from &squot;%s&squot;&quot;
comma
(paren
r_int
)paren
id|rsize
comma
id|path
)paren
suffix:semicolon
id|offset
op_add_assign
id|rsize
suffix:semicolon
r_if
c_cond
(paren
op_star
id|already_hashed_to
OL
id|offset
)paren
(brace
r_int
id|hsize
op_assign
id|offset
op_star
id|already_hashed_to
suffix:semicolon
r_if
c_cond
(paren
id|rsize
OL
id|hsize
)paren
id|hsize
op_assign
id|rsize
suffix:semicolon
r_if
c_cond
(paren
id|hsize
)paren
id|git_SHA1_Update
c_func
(paren
id|ctx
comma
id|ibuf
comma
id|hsize
)paren
suffix:semicolon
op_star
id|already_hashed_to
op_assign
id|offset
suffix:semicolon
)brace
id|s.next_in
op_assign
id|ibuf
suffix:semicolon
id|s.avail_in
op_assign
id|rsize
suffix:semicolon
id|size
op_sub_assign
id|rsize
suffix:semicolon
)brace
id|status
op_assign
id|git_deflate
c_func
(paren
op_amp
id|s
comma
id|size
ques
c_cond
l_int|0
suffix:colon
id|Z_FINISH
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s.avail_out
op_logical_or
id|status
op_eq
id|Z_STREAM_END
)paren
(brace
r_if
c_cond
(paren
id|write_object
)paren
(brace
r_int
id|written
op_assign
id|s.next_out
id|obuf
suffix:semicolon
multiline_comment|/* would we bust the size limit? */
r_if
c_cond
(paren
id|state-&gt;nr_written
op_logical_and
id|pack_size_limit_cfg
op_logical_and
id|pack_size_limit_cfg
OL
id|state-&gt;offset
op_plus
id|written
)paren
(brace
id|git_deflate_abort
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|sha1write
c_func
(paren
id|state-&gt;f
comma
id|obuf
comma
id|written
)paren
suffix:semicolon
id|state-&gt;offset
op_add_assign
id|written
suffix:semicolon
)brace
id|s.next_out
op_assign
id|obuf
suffix:semicolon
id|s.avail_out
op_assign
r_sizeof
(paren
id|obuf
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|Z_OK
suffix:colon
r_case
id|Z_BUF_ERROR
suffix:colon
r_case
id|Z_STREAM_END
suffix:colon
r_continue
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;unexpected deflate failure: %d&quot;
comma
id|status
)paren
suffix:semicolon
)brace
)brace
id|git_deflate_end
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Lazily create backing packfile for the state */
DECL|function|prepare_to_stream
r_static
r_void
id|prepare_to_stream
c_func
(paren
r_struct
id|bulk_checkin_state
op_star
id|state
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|HASH_WRITE_OBJECT
)paren
op_logical_or
id|state-&gt;f
)paren
r_return
suffix:semicolon
id|state-&gt;f
op_assign
id|create_tmp_packfile
c_func
(paren
op_amp
id|state-&gt;pack_tmp_name
)paren
suffix:semicolon
id|reset_pack_idx_option
c_func
(paren
op_amp
id|state-&gt;pack_idx_opts
)paren
suffix:semicolon
multiline_comment|/* Pretend we are going to write only one object */
id|state-&gt;offset
op_assign
id|write_pack_header
c_func
(paren
id|state-&gt;f
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;offset
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to write pack header&quot;
)paren
suffix:semicolon
)brace
DECL|function|deflate_to_pack
r_static
r_int
id|deflate_to_pack
c_func
(paren
r_struct
id|bulk_checkin_state
op_star
id|state
comma
r_int
r_char
id|result_sha1
(braket
)braket
comma
r_int
id|fd
comma
r_int
id|size
comma
r_enum
id|object_type
id|type
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
)paren
(brace
id|off_t
id|seekback
comma
id|already_hashed_to
suffix:semicolon
id|git_SHA_CTX
id|ctx
suffix:semicolon
r_int
r_char
id|obuf
(braket
l_int|16384
)braket
suffix:semicolon
r_int
id|header_len
suffix:semicolon
r_struct
id|sha1file_checkpoint
id|checkpoint
suffix:semicolon
r_struct
id|pack_idx_entry
op_star
id|idx
op_assign
l_int|NULL
suffix:semicolon
id|seekback
op_assign
id|lseek
c_func
(paren
id|fd
comma
l_int|0
comma
id|SEEK_CUR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seekback
op_eq
(paren
id|off_t
)paren
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot find the current offset&quot;
)paren
suffix:semicolon
id|header_len
op_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|obuf
comma
l_string|&quot;%s %&quot;
id|PRIuMAX
comma
r_typename
(paren
id|type
)paren
comma
(paren
r_uintmax
)paren
id|size
)paren
op_plus
l_int|1
suffix:semicolon
id|git_SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|obuf
comma
id|header_len
)paren
suffix:semicolon
multiline_comment|/* Note: idx is non-NULL when we are writing */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|HASH_WRITE_OBJECT
)paren
op_ne
l_int|0
)paren
id|idx
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|idx
)paren
)paren
suffix:semicolon
id|already_hashed_to
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|prepare_to_stream
c_func
(paren
id|state
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
)paren
(brace
id|sha1file_checkpoint
c_func
(paren
id|state-&gt;f
comma
op_amp
id|checkpoint
)paren
suffix:semicolon
id|idx-&gt;offset
op_assign
id|state-&gt;offset
suffix:semicolon
id|crc32_begin
c_func
(paren
id|state-&gt;f
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|stream_to_pack
c_func
(paren
id|state
comma
op_amp
id|ctx
comma
op_amp
id|already_hashed_to
comma
id|fd
comma
id|size
comma
id|type
comma
id|path
comma
id|flags
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Writing this object to the current pack will make&n;&t;&t; * it too big; we need to truncate it, start a new&n;&t;&t; * pack, and write into it.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|idx
)paren
id|die
c_func
(paren
l_string|&quot;BUG: should not happen&quot;
)paren
suffix:semicolon
id|sha1file_truncate
c_func
(paren
id|state-&gt;f
comma
op_amp
id|checkpoint
)paren
suffix:semicolon
id|state-&gt;offset
op_assign
id|checkpoint.offset
suffix:semicolon
id|finish_bulk_checkin
c_func
(paren
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|fd
comma
id|seekback
comma
id|SEEK_SET
)paren
op_eq
(paren
id|off_t
)paren
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot seek back&quot;
)paren
suffix:semicolon
)brace
id|git_SHA1_Final
c_func
(paren
id|result_sha1
comma
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idx
)paren
r_return
l_int|0
suffix:semicolon
id|idx-&gt;crc32
op_assign
id|crc32_end
c_func
(paren
id|state-&gt;f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|already_written
c_func
(paren
id|state
comma
id|result_sha1
)paren
)paren
(brace
id|sha1file_truncate
c_func
(paren
id|state-&gt;f
comma
op_amp
id|checkpoint
)paren
suffix:semicolon
id|state-&gt;offset
op_assign
id|checkpoint.offset
suffix:semicolon
id|free
c_func
(paren
id|idx
)paren
suffix:semicolon
)brace
r_else
(brace
id|hashcpy
c_func
(paren
id|idx-&gt;sha1
comma
id|result_sha1
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|state-&gt;written
comma
id|state-&gt;nr_written
op_plus
l_int|1
comma
id|state-&gt;alloc_written
)paren
suffix:semicolon
id|state-&gt;written
(braket
id|state-&gt;nr_written
op_increment
)braket
op_assign
id|idx
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|index_bulk_checkin
r_int
id|index_bulk_checkin
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
id|fd
comma
r_int
id|size
comma
r_enum
id|object_type
id|type
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
)paren
(brace
r_int
id|status
op_assign
id|deflate_to_pack
c_func
(paren
op_amp
id|state
comma
id|sha1
comma
id|fd
comma
id|size
comma
id|type
comma
id|path
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state.plugged
)paren
id|finish_bulk_checkin
c_func
(paren
op_amp
id|state
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|plug_bulk_checkin
r_void
id|plug_bulk_checkin
c_func
(paren
r_void
)paren
(brace
id|state.plugged
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|unplug_bulk_checkin
r_void
id|unplug_bulk_checkin
c_func
(paren
r_void
)paren
(brace
id|state.plugged
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|state.f
)paren
id|finish_bulk_checkin
c_func
(paren
op_amp
id|state
)paren
suffix:semicolon
)brace
eof
