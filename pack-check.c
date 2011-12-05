macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;pack-revindex.h&quot;
macro_line|#include &quot;progress.h&quot;
DECL|struct|idx_entry
r_struct
id|idx_entry
(brace
DECL|member|offset
id|off_t
id|offset
suffix:semicolon
DECL|member|sha1
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|compare_entries
r_static
r_int
id|compare_entries
c_func
(paren
r_const
r_void
op_star
id|e1
comma
r_const
r_void
op_star
id|e2
)paren
(brace
r_const
r_struct
id|idx_entry
op_star
id|entry1
op_assign
id|e1
suffix:semicolon
r_const
r_struct
id|idx_entry
op_star
id|entry2
op_assign
id|e2
suffix:semicolon
r_if
c_cond
(paren
id|entry1-&gt;offset
OL
id|entry2-&gt;offset
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|entry1-&gt;offset
OG
id|entry2-&gt;offset
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_pack_crc
r_int
id|check_pack_crc
c_func
(paren
r_struct
id|packed_git
op_star
id|p
comma
r_struct
id|pack_window
op_star
op_star
id|w_curs
comma
id|off_t
id|offset
comma
id|off_t
id|len
comma
r_int
r_int
id|nr
)paren
(brace
r_const
r_uint32
op_star
id|index_crc
suffix:semicolon
r_uint32
id|data_crc
op_assign
id|crc32
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_do
(brace
r_int
r_int
id|avail
suffix:semicolon
r_void
op_star
id|data
op_assign
id|use_pack
c_func
(paren
id|p
comma
id|w_curs
comma
id|offset
comma
op_amp
id|avail
)paren
suffix:semicolon
r_if
c_cond
(paren
id|avail
OG
id|len
)paren
id|avail
op_assign
id|len
suffix:semicolon
id|data_crc
op_assign
id|crc32
c_func
(paren
id|data_crc
comma
id|data
comma
id|avail
)paren
suffix:semicolon
id|offset
op_add_assign
id|avail
suffix:semicolon
id|len
op_sub_assign
id|avail
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
)paren
suffix:semicolon
id|index_crc
op_assign
id|p-&gt;index_data
suffix:semicolon
id|index_crc
op_add_assign
l_int|2
op_plus
l_int|256
op_plus
id|p-&gt;num_objects
op_star
(paren
l_int|20
op_div
l_int|4
)paren
op_plus
id|nr
suffix:semicolon
r_return
id|data_crc
op_ne
id|ntohl
c_func
(paren
op_star
id|index_crc
)paren
suffix:semicolon
)brace
DECL|function|verify_packfile
r_static
r_int
id|verify_packfile
c_func
(paren
r_struct
id|packed_git
op_star
id|p
comma
r_struct
id|pack_window
op_star
op_star
id|w_curs
comma
id|verify_fn
id|fn
comma
r_struct
id|progress
op_star
id|progress
comma
r_uint32
id|base_count
)paren
(brace
id|off_t
id|index_size
op_assign
id|p-&gt;index_size
suffix:semicolon
r_const
r_int
r_char
op_star
id|index_base
op_assign
id|p-&gt;index_data
suffix:semicolon
id|git_SHA_CTX
id|ctx
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
op_star
id|pack_sig
suffix:semicolon
id|off_t
id|offset
op_assign
l_int|0
comma
id|pack_sig_ofs
op_assign
l_int|0
suffix:semicolon
r_uint32
id|nr_objects
comma
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|idx_entry
op_star
id|entries
suffix:semicolon
multiline_comment|/* Note that the pack header checks are actually performed by&n;&t; * use_pack when it first opens the pack file.  If anything&n;&t; * goes wrong during those checks then the call will die out&n;&t; * immediately.&n;&t; */
id|git_SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
r_do
(brace
r_int
r_int
id|remaining
suffix:semicolon
r_int
r_char
op_star
id|in
op_assign
id|use_pack
c_func
(paren
id|p
comma
id|w_curs
comma
id|offset
comma
op_amp
id|remaining
)paren
suffix:semicolon
id|offset
op_add_assign
id|remaining
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pack_sig_ofs
)paren
id|pack_sig_ofs
op_assign
id|p-&gt;pack_size
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|pack_sig_ofs
)paren
id|remaining
op_sub_assign
(paren
r_int
r_int
)paren
(paren
id|offset
id|pack_sig_ofs
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|in
comma
id|remaining
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|offset
OL
id|pack_sig_ofs
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
id|pack_sig
op_assign
id|use_pack
c_func
(paren
id|p
comma
id|w_curs
comma
id|pack_sig_ofs
comma
l_int|NULL
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
id|pack_sig
)paren
)paren
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;%s SHA1 checksum mismatch&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|index_base
op_plus
id|index_size
l_int|40
comma
id|pack_sig
)paren
)paren
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;%s SHA1 does not match its index&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
id|unuse_pack
c_func
(paren
id|w_curs
)paren
suffix:semicolon
multiline_comment|/* Make sure everything reachable from idx is valid.  Since we&n;&t; * have verified that nr_objects matches between idx and pack,&n;&t; * we do not do scan-streaming check on the pack file.&n;&t; */
id|nr_objects
op_assign
id|p-&gt;num_objects
suffix:semicolon
id|entries
op_assign
id|xmalloc
c_func
(paren
(paren
id|nr_objects
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|entries
)paren
)paren
suffix:semicolon
id|entries
(braket
id|nr_objects
)braket
dot
id|offset
op_assign
id|pack_sig_ofs
suffix:semicolon
multiline_comment|/* first sort entries by pack offset, since unpacking them is more efficient that way */
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
id|entries
(braket
id|i
)braket
dot
id|sha1
op_assign
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entries
(braket
id|i
)braket
dot
id|sha1
)paren
id|die
c_func
(paren
l_string|&quot;internal error pack-check nth-packed-object&quot;
)paren
suffix:semicolon
id|entries
(braket
id|i
)braket
dot
id|offset
op_assign
id|nth_packed_object_offset
c_func
(paren
id|p
comma
id|i
)paren
suffix:semicolon
id|entries
(braket
id|i
)braket
dot
id|nr
op_assign
id|i
suffix:semicolon
)brace
id|qsort
c_func
(paren
id|entries
comma
id|nr_objects
comma
r_sizeof
(paren
op_star
id|entries
)paren
comma
id|compare_entries
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
r_void
op_star
id|data
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;index_version
OG
l_int|1
)paren
(brace
id|off_t
id|offset
op_assign
id|entries
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
id|off_t
id|len
op_assign
id|entries
(braket
id|i
op_plus
l_int|1
)braket
dot
id|offset
id|offset
suffix:semicolon
r_int
r_int
id|nr
op_assign
id|entries
(braket
id|i
)braket
dot
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|check_pack_crc
c_func
(paren
id|p
comma
id|w_curs
comma
id|offset
comma
id|len
comma
id|nr
)paren
)paren
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;index CRC mismatch for object %s &quot;
l_string|&quot;from %s at offset %&quot;
id|PRIuMAX
l_string|&quot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entries
(braket
id|i
)braket
dot
id|sha1
)paren
comma
id|p-&gt;pack_name
comma
(paren
r_uintmax
)paren
id|offset
)paren
suffix:semicolon
)brace
id|data
op_assign
id|unpack_entry
c_func
(paren
id|p
comma
id|entries
(braket
id|i
)braket
dot
id|offset
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
id|data
)paren
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;cannot unpack %s from %s at offset %&quot;
id|PRIuMAX
l_string|&quot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entries
(braket
id|i
)braket
dot
id|sha1
)paren
comma
id|p-&gt;pack_name
comma
(paren
r_uintmax
)paren
id|entries
(braket
id|i
)braket
dot
id|offset
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|check_sha1_signature
c_func
(paren
id|entries
(braket
id|i
)braket
dot
id|sha1
comma
id|data
comma
id|size
comma
r_typename
(paren
id|type
)paren
)paren
)paren
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;packed %s from %s is corrupt&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entries
(braket
id|i
)braket
dot
id|sha1
)paren
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fn
)paren
(brace
r_int
id|eaten
op_assign
l_int|0
suffix:semicolon
id|fn
c_func
(paren
id|entries
(braket
id|i
)braket
dot
id|sha1
comma
id|type
comma
id|size
comma
id|data
comma
op_amp
id|eaten
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eaten
)paren
id|data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|base_count
op_plus
id|i
)paren
op_amp
l_int|1023
)paren
op_eq
l_int|0
)paren
id|display_progress
c_func
(paren
id|progress
comma
id|base_count
op_plus
id|i
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
id|display_progress
c_func
(paren
id|progress
comma
id|base_count
op_plus
id|i
)paren
suffix:semicolon
id|free
c_func
(paren
id|entries
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|verify_pack_index
r_int
id|verify_pack_index
c_func
(paren
r_struct
id|packed_git
op_star
id|p
)paren
(brace
id|off_t
id|index_size
suffix:semicolon
r_const
r_int
r_char
op_star
id|index_base
suffix:semicolon
id|git_SHA_CTX
id|ctx
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|open_pack_index
c_func
(paren
id|p
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;packfile %s index not opened&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
id|index_size
op_assign
id|p-&gt;index_size
suffix:semicolon
id|index_base
op_assign
id|p-&gt;index_data
suffix:semicolon
multiline_comment|/* Verify SHA1 sum of the index file */
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
id|index_base
comma
(paren
r_int
r_int
)paren
(paren
id|index_size
l_int|20
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
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|index_base
op_plus
id|index_size
l_int|20
)paren
)paren
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;Packfile index for %s SHA1 mismatch&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|verify_pack
r_int
id|verify_pack
c_func
(paren
r_struct
id|packed_git
op_star
id|p
comma
id|verify_fn
id|fn
comma
r_struct
id|progress
op_star
id|progress
comma
r_uint32
id|base_count
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|pack_window
op_star
id|w_curs
op_assign
l_int|NULL
suffix:semicolon
id|err
op_or_assign
id|verify_pack_index
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;index_data
)paren
r_return
l_int|1
suffix:semicolon
id|err
op_or_assign
id|verify_packfile
c_func
(paren
id|p
comma
op_amp
id|w_curs
comma
id|fn
comma
id|progress
comma
id|base_count
)paren
suffix:semicolon
id|unuse_pack
c_func
(paren
op_amp
id|w_curs
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
