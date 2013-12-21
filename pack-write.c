macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;csum-file.h&quot;
DECL|function|reset_pack_idx_option
r_void
id|reset_pack_idx_option
c_func
(paren
r_struct
id|pack_idx_option
op_star
id|opts
)paren
(brace
id|memset
c_func
(paren
id|opts
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|opts
)paren
)paren
suffix:semicolon
id|opts-&gt;version
op_assign
l_int|2
suffix:semicolon
id|opts-&gt;off32_limit
op_assign
l_int|0x7fffffff
suffix:semicolon
)brace
DECL|function|sha1_compare
r_static
r_int
id|sha1_compare
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
id|pack_idx_entry
op_star
id|a
op_assign
op_star
(paren
r_struct
id|pack_idx_entry
op_star
op_star
)paren
id|_a
suffix:semicolon
r_struct
id|pack_idx_entry
op_star
id|b
op_assign
op_star
(paren
r_struct
id|pack_idx_entry
op_star
op_star
)paren
id|_b
suffix:semicolon
r_return
id|hashcmp
c_func
(paren
id|a-&gt;sha1
comma
id|b-&gt;sha1
)paren
suffix:semicolon
)brace
DECL|function|cmp_uint32
r_static
r_int
id|cmp_uint32
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_uint32
id|a
op_assign
op_star
(paren
(paren
r_uint32
op_star
)paren
id|a_
)paren
suffix:semicolon
r_uint32
id|b
op_assign
op_star
(paren
(paren
r_uint32
op_star
)paren
id|b_
)paren
suffix:semicolon
r_return
(paren
id|a
OL
id|b
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
id|a
op_ne
id|b
)paren
suffix:semicolon
)brace
DECL|function|need_large_offset
r_static
r_int
id|need_large_offset
c_func
(paren
id|off_t
id|offset
comma
r_const
r_struct
id|pack_idx_option
op_star
id|opts
)paren
(brace
r_uint32
id|ofsval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|offset
op_rshift
l_int|31
)paren
op_logical_or
(paren
id|opts-&gt;off32_limit
OL
id|offset
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts-&gt;anomaly_nr
)paren
r_return
l_int|0
suffix:semicolon
id|ofsval
op_assign
id|offset
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|bsearch
c_func
(paren
op_amp
id|ofsval
comma
id|opts-&gt;anomaly
comma
id|opts-&gt;anomaly_nr
comma
r_sizeof
(paren
id|ofsval
)paren
comma
id|cmp_uint32
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * On entry *sha1 contains the pack content SHA1 hash, on exit it is&n; * the SHA1 hash of sorted object names. The objects array passed in&n; * will be sorted by SHA1 on exit.&n; */
DECL|function|write_idx_file
r_const
r_char
op_star
id|write_idx_file
c_func
(paren
r_const
r_char
op_star
id|index_name
comma
r_struct
id|pack_idx_entry
op_star
op_star
id|objects
comma
r_int
id|nr_objects
comma
r_const
r_struct
id|pack_idx_option
op_star
id|opts
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|sha1file
op_star
id|f
suffix:semicolon
r_struct
id|pack_idx_entry
op_star
op_star
id|sorted_by_sha
comma
op_star
op_star
id|list
comma
op_star
op_star
id|last
suffix:semicolon
id|off_t
id|last_obj_offset
op_assign
l_int|0
suffix:semicolon
r_uint32
id|array
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|i
comma
id|fd
suffix:semicolon
id|git_SHA_CTX
id|ctx
suffix:semicolon
r_uint32
id|index_version
suffix:semicolon
r_if
c_cond
(paren
id|nr_objects
)paren
(brace
id|sorted_by_sha
op_assign
id|objects
suffix:semicolon
id|list
op_assign
id|sorted_by_sha
suffix:semicolon
id|last
op_assign
id|sorted_by_sha
op_plus
id|nr_objects
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
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|objects
(braket
id|i
)braket
op_member_access_from_pointer
id|offset
OG
id|last_obj_offset
)paren
id|last_obj_offset
op_assign
id|objects
(braket
id|i
)braket
op_member_access_from_pointer
id|offset
suffix:semicolon
)brace
id|qsort
c_func
(paren
id|sorted_by_sha
comma
id|nr_objects
comma
r_sizeof
(paren
id|sorted_by_sha
(braket
l_int|0
)braket
)paren
comma
id|sha1_compare
)paren
suffix:semicolon
)brace
r_else
id|sorted_by_sha
op_assign
id|list
op_assign
id|last
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;flags
op_amp
id|WRITE_IDX_VERIFY
)paren
(brace
m_assert
(paren
id|index_name
)paren
suffix:semicolon
id|f
op_assign
id|sha1fd_check
c_func
(paren
id|index_name
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|index_name
)paren
(brace
r_static
r_char
id|tmp_file
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|fd
op_assign
id|odb_mkstemp
c_func
(paren
id|tmp_file
comma
r_sizeof
(paren
id|tmp_file
)paren
comma
l_string|&quot;pack/tmp_idx_XXXXXX&quot;
)paren
suffix:semicolon
id|index_name
op_assign
id|xstrdup
c_func
(paren
id|tmp_file
)paren
suffix:semicolon
)brace
r_else
(brace
id|unlink
c_func
(paren
id|index_name
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|index_name
comma
id|O_CREAT
op_or
id|O_EXCL
op_or
id|O_WRONLY
comma
l_int|0600
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to create &squot;%s&squot;&quot;
comma
id|index_name
)paren
suffix:semicolon
id|f
op_assign
id|sha1fd
c_func
(paren
id|fd
comma
id|index_name
)paren
suffix:semicolon
)brace
multiline_comment|/* if last object&squot;s offset is &gt;= 2^31 we should use index V2 */
id|index_version
op_assign
id|need_large_offset
c_func
(paren
id|last_obj_offset
comma
id|opts
)paren
ques
c_cond
l_int|2
suffix:colon
id|opts-&gt;version
suffix:semicolon
multiline_comment|/* index versions 2 and above need a header */
r_if
c_cond
(paren
id|index_version
op_ge
l_int|2
)paren
(brace
r_struct
id|pack_idx_header
id|hdr
suffix:semicolon
id|hdr.idx_signature
op_assign
id|htonl
c_func
(paren
id|PACK_IDX_SIGNATURE
)paren
suffix:semicolon
id|hdr.idx_version
op_assign
id|htonl
c_func
(paren
id|index_version
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
)brace
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
id|pack_idx_entry
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
id|pack_idx_entry
op_star
id|obj
op_assign
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;sha1
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
l_int|4
)paren
suffix:semicolon
multiline_comment|/* compute the SHA1 hash of sorted object names. */
id|git_SHA1_Init
c_func
(paren
op_amp
id|ctx
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
id|pack_idx_entry
op_star
id|obj
op_assign
op_star
id|list
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|index_version
OL
l_int|2
)paren
(brace
r_uint32
id|offset
op_assign
id|htonl
c_func
(paren
id|obj-&gt;offset
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
)brace
id|sha1write
c_func
(paren
id|f
comma
id|obj-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|obj-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|opts-&gt;flags
op_amp
id|WRITE_IDX_STRICT
)paren
op_logical_and
(paren
id|i
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|list
(braket
l_int|2
)braket
op_member_access_from_pointer
id|sha1
comma
id|obj-&gt;sha1
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;The same object %s appears twice in the pack&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index_version
op_ge
l_int|2
)paren
(brace
r_int
r_int
id|nr_large_offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* write the crc32 table */
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
id|pack_idx_entry
op_star
id|obj
op_assign
op_star
id|list
op_increment
suffix:semicolon
r_uint32
id|crc32_val
op_assign
id|htonl
c_func
(paren
id|obj-&gt;crc32
)paren
suffix:semicolon
id|sha1write
c_func
(paren
id|f
comma
op_amp
id|crc32_val
comma
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* write the 32-bit offset table */
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
id|pack_idx_entry
op_star
id|obj
op_assign
op_star
id|list
op_increment
suffix:semicolon
r_uint32
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|need_large_offset
c_func
(paren
id|obj-&gt;offset
comma
id|opts
)paren
ques
c_cond
(paren
l_int|0x80000000
op_or
id|nr_large_offset
op_increment
)paren
suffix:colon
id|obj-&gt;offset
)paren
suffix:semicolon
id|offset
op_assign
id|htonl
c_func
(paren
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
)brace
multiline_comment|/* write the large offset table */
id|list
op_assign
id|sorted_by_sha
suffix:semicolon
r_while
c_loop
(paren
id|nr_large_offset
)paren
(brace
r_struct
id|pack_idx_entry
op_star
id|obj
op_assign
op_star
id|list
op_increment
suffix:semicolon
r_uint64
id|offset
op_assign
id|obj-&gt;offset
suffix:semicolon
r_uint32
id|split
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_large_offset
c_func
(paren
id|offset
comma
id|opts
)paren
)paren
r_continue
suffix:semicolon
id|split
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
id|offset
op_rshift
l_int|32
)paren
suffix:semicolon
id|split
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
id|offset
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|sha1write
c_func
(paren
id|f
comma
id|split
comma
l_int|8
)paren
suffix:semicolon
id|nr_large_offset
op_decrement
suffix:semicolon
)brace
)brace
id|sha1write
c_func
(paren
id|f
comma
id|sha1
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
(paren
(paren
id|opts-&gt;flags
op_amp
id|WRITE_IDX_VERIFY
)paren
ques
c_cond
id|CSUM_CLOSE
suffix:colon
id|CSUM_FSYNC
)paren
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
r_return
id|index_name
suffix:semicolon
)brace
DECL|function|write_pack_header
id|off_t
id|write_pack_header
c_func
(paren
r_struct
id|sha1file
op_star
id|f
comma
r_uint32
id|nr_entries
)paren
(brace
r_struct
id|pack_header
id|hdr
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
id|nr_entries
)paren
suffix:semicolon
r_if
c_cond
(paren
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
)paren
r_return
l_int|0
suffix:semicolon
r_return
r_sizeof
(paren
id|hdr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Update pack header with object_count and compute new SHA1 for pack data&n; * associated to pack_fd, and write that SHA1 at the end.  That new SHA1&n; * is also returned in new_pack_sha1.&n; *&n; * If partial_pack_sha1 is non null, then the SHA1 of the existing pack&n; * (without the header update) is computed and validated against the&n; * one provided in partial_pack_sha1.  The validation is performed at&n; * partial_pack_offset bytes in the pack file.  The SHA1 of the remaining&n; * data (i.e. from partial_pack_offset to the end) is then computed and&n; * returned in partial_pack_sha1.&n; *&n; * Note that new_pack_sha1 is updated last, so both new_pack_sha1 and&n; * partial_pack_sha1 can refer to the same buffer if the caller is not&n; * interested in the resulting SHA1 of pack data above partial_pack_offset.&n; */
DECL|function|fixup_pack_header_footer
r_void
id|fixup_pack_header_footer
c_func
(paren
r_int
id|pack_fd
comma
r_int
r_char
op_star
id|new_pack_sha1
comma
r_const
r_char
op_star
id|pack_name
comma
r_uint32
id|object_count
comma
r_int
r_char
op_star
id|partial_pack_sha1
comma
id|off_t
id|partial_pack_offset
)paren
(brace
r_int
id|aligned_sz
comma
id|buf_sz
op_assign
l_int|8
op_star
l_int|1024
suffix:semicolon
id|git_SHA_CTX
id|old_sha1_ctx
comma
id|new_sha1_ctx
suffix:semicolon
r_struct
id|pack_header
id|hdr
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
id|git_SHA1_Init
c_func
(paren
op_amp
id|old_sha1_ctx
)paren
suffix:semicolon
id|git_SHA1_Init
c_func
(paren
op_amp
id|new_sha1_ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|pack_fd
comma
l_int|0
comma
id|SEEK_SET
)paren
op_ne
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Failed seeking to start of &squot;%s&squot;&quot;
comma
id|pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_in_full
c_func
(paren
id|pack_fd
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
op_ne
r_sizeof
(paren
id|hdr
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;Unable to reread header of &squot;%s&squot;&quot;
comma
id|pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|pack_fd
comma
l_int|0
comma
id|SEEK_SET
)paren
op_ne
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Failed seeking to start of &squot;%s&squot;&quot;
comma
id|pack_name
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|old_sha1_ctx
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
id|hdr.hdr_entries
op_assign
id|htonl
c_func
(paren
id|object_count
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|new_sha1_ctx
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
id|write_or_die
c_func
(paren
id|pack_fd
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
id|partial_pack_offset
op_sub_assign
r_sizeof
(paren
id|hdr
)paren
suffix:semicolon
id|buf
op_assign
id|xmalloc
c_func
(paren
id|buf_sz
)paren
suffix:semicolon
id|aligned_sz
op_assign
id|buf_sz
r_sizeof
(paren
id|hdr
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|ssize_t
id|m
comma
id|n
suffix:semicolon
id|m
op_assign
(paren
id|partial_pack_sha1
op_logical_and
id|partial_pack_offset
OL
id|aligned_sz
)paren
ques
c_cond
id|partial_pack_offset
suffix:colon
id|aligned_sz
suffix:semicolon
id|n
op_assign
id|xread
c_func
(paren
id|pack_fd
comma
id|buf
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Failed to checksum &squot;%s&squot;&quot;
comma
id|pack_name
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|new_sha1_ctx
comma
id|buf
comma
id|n
)paren
suffix:semicolon
id|aligned_sz
op_sub_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aligned_sz
)paren
id|aligned_sz
op_assign
id|buf_sz
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|partial_pack_sha1
)paren
r_continue
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|old_sha1_ctx
comma
id|buf
comma
id|n
)paren
suffix:semicolon
id|partial_pack_offset
op_sub_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|partial_pack_offset
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|git_SHA1_Final
c_func
(paren
id|sha1
comma
op_amp
id|old_sha1_ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|partial_pack_sha1
)paren
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unexpected checksum for %s &quot;
l_string|&quot;(disk corruption?)&quot;
comma
id|pack_name
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Now let&squot;s compute the SHA1 of the remainder of the&n;&t;&t;&t; * pack, which also means making partial_pack_offset&n;&t;&t;&t; * big enough not to matter anymore.&n;&t;&t;&t; */
id|git_SHA1_Init
c_func
(paren
op_amp
id|old_sha1_ctx
)paren
suffix:semicolon
id|partial_pack_offset
op_assign
op_complement
id|partial_pack_offset
suffix:semicolon
id|partial_pack_offset
op_sub_assign
id|MSB
c_func
(paren
id|partial_pack_offset
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|partial_pack_sha1
)paren
id|git_SHA1_Final
c_func
(paren
id|partial_pack_sha1
comma
op_amp
id|old_sha1_ctx
)paren
suffix:semicolon
id|git_SHA1_Final
c_func
(paren
id|new_pack_sha1
comma
op_amp
id|new_sha1_ctx
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|pack_fd
comma
id|new_pack_sha1
comma
l_int|20
)paren
suffix:semicolon
id|fsync_or_die
c_func
(paren
id|pack_fd
comma
id|pack_name
)paren
suffix:semicolon
)brace
DECL|function|index_pack_lockfile
r_char
op_star
id|index_pack_lockfile
c_func
(paren
r_int
id|ip_out
)paren
(brace
r_char
id|packname
(braket
l_int|46
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * The first thing we expect from index-pack&squot;s output&n;&t; * is &quot;pack&bslash;t%40s&bslash;n&quot; or &quot;keep&bslash;t%40s&bslash;n&quot; (46 bytes) where&n;&t; * %40s is the newly created pack SHA1 name.  In the &quot;keep&quot;&n;&t; * case, we need it to remove the corresponding .keep file&n;&t; * later on.  If we don&squot;t get that then tough luck with it.&n;&t; */
r_if
c_cond
(paren
id|read_in_full
c_func
(paren
id|ip_out
comma
id|packname
comma
l_int|46
)paren
op_eq
l_int|46
op_logical_and
id|packname
(braket
l_int|45
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|memcmp
c_func
(paren
id|packname
comma
l_string|&quot;keep&bslash;t&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|packname
(braket
l_int|45
)braket
op_assign
l_int|0
suffix:semicolon
id|snprintf
c_func
(paren
id|path
comma
r_sizeof
(paren
id|path
)paren
comma
l_string|&quot;%s/pack/pack-%s.keep&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|packname
op_plus
l_int|5
)paren
suffix:semicolon
r_return
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * The per-object header is a pretty dense thing, which is&n; *  - first byte: low four bits are &quot;size&quot;, then three bits of &quot;type&quot;,&n; *    and the high bit is &quot;size continues&quot;.&n; *  - each byte afterwards: low seven bits are size continuation,&n; *    with the high bit being &quot;size continues&quot;&n; */
DECL|function|encode_in_pack_object_header
r_int
id|encode_in_pack_object_header
c_func
(paren
r_enum
id|object_type
id|type
comma
r_uintmax
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
id|OBJ_REF_DELTA
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
DECL|function|create_tmp_packfile
r_struct
id|sha1file
op_star
id|create_tmp_packfile
c_func
(paren
r_char
op_star
op_star
id|pack_tmp_name
)paren
(brace
r_char
id|tmpname
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|odb_mkstemp
c_func
(paren
id|tmpname
comma
r_sizeof
(paren
id|tmpname
)paren
comma
l_string|&quot;pack/tmp_pack_XXXXXX&quot;
)paren
suffix:semicolon
op_star
id|pack_tmp_name
op_assign
id|xstrdup
c_func
(paren
id|tmpname
)paren
suffix:semicolon
r_return
id|sha1fd
c_func
(paren
id|fd
comma
op_star
id|pack_tmp_name
)paren
suffix:semicolon
)brace
DECL|function|finish_tmp_packfile
r_void
id|finish_tmp_packfile
c_func
(paren
r_char
op_star
id|name_buffer
comma
r_const
r_char
op_star
id|pack_tmp_name
comma
r_struct
id|pack_idx_entry
op_star
op_star
id|written_list
comma
r_uint32
id|nr_written
comma
r_struct
id|pack_idx_option
op_star
id|pack_idx_opts
comma
r_int
r_char
id|sha1
(braket
)braket
)paren
(brace
r_const
r_char
op_star
id|idx_tmp_name
suffix:semicolon
r_char
op_star
id|end_of_name_prefix
op_assign
id|strrchr
c_func
(paren
id|name_buffer
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|pack_tmp_name
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to make temporary pack file readable&quot;
)paren
suffix:semicolon
id|idx_tmp_name
op_assign
id|write_idx_file
c_func
(paren
l_int|NULL
comma
id|written_list
comma
id|nr_written
comma
id|pack_idx_opts
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|idx_tmp_name
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to make temporary index file readable&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|end_of_name_prefix
comma
l_string|&quot;%s.pack&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|free_pack_by_name
c_func
(paren
id|name_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|pack_tmp_name
comma
id|name_buffer
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to rename temporary pack file&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|end_of_name_prefix
comma
l_string|&quot;%s.idx&quot;
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
id|rename
c_func
(paren
id|idx_tmp_name
comma
id|name_buffer
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to rename temporary index file&quot;
)paren
suffix:semicolon
op_star
id|end_of_name_prefix
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|idx_tmp_name
)paren
suffix:semicolon
)brace
eof
