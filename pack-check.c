macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
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
)paren
(brace
r_int
r_int
id|index_size
op_assign
id|p-&gt;index_size
suffix:semicolon
r_void
op_star
id|index_base
op_assign
id|p-&gt;index_base
suffix:semicolon
id|SHA_CTX
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
r_int
id|pack_size
op_assign
id|p-&gt;pack_size
suffix:semicolon
r_void
op_star
id|pack_base
suffix:semicolon
r_struct
id|pack_header
op_star
id|hdr
suffix:semicolon
r_int
id|nr_objects
comma
id|err
comma
id|i
suffix:semicolon
multiline_comment|/* Header consistency check */
id|hdr
op_assign
id|p-&gt;pack_base
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;hdr_signature
op_ne
id|htonl
c_func
(paren
id|PACK_SIGNATURE
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Packfile %s signature mismatch&quot;
comma
id|p-&gt;pack_name
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
r_return
id|error
c_func
(paren
l_string|&quot;Packfile version %d unsupported&quot;
comma
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_version
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
id|num_packed_objects
c_func
(paren
id|p
)paren
op_ne
id|nr_objects
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Packfile claims to have %d objects, &quot;
l_string|&quot;while idx size expects %d&quot;
comma
id|nr_objects
comma
id|num_packed_objects
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
id|pack_base
op_assign
id|p-&gt;pack_base
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|pack_base
comma
id|pack_size
l_int|20
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
id|hashcmp
c_func
(paren
id|sha1
comma
(paren
r_int
r_char
op_star
)paren
id|pack_base
op_plus
id|pack_size
l_int|20
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Packfile %s SHA1 mismatch with itself&quot;
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
id|sha1
comma
(paren
r_int
r_char
op_star
)paren
id|index_base
op_plus
id|index_size
l_int|40
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Packfile %s SHA1 mismatch with idx&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
multiline_comment|/* Make sure everything reachable from idx is valid.  Since we&n;&t; * have verified that nr_objects matches between idx and pack,&n;&t; * we do not do scan-streaming check on the pack file.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|err
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
comma
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error pack-check nth-packed-object&quot;
)paren
suffix:semicolon
id|offset
op_assign
id|find_pack_entry_one
c_func
(paren
id|sha1
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
id|die
c_func
(paren
l_string|&quot;internal error pack-check find-pack-entry-one&quot;
)paren
suffix:semicolon
id|data
op_assign
id|unpack_entry
c_func
(paren
id|p
comma
id|offset
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
op_logical_neg
id|data
)paren
(brace
id|err
op_assign
id|error
c_func
(paren
l_string|&quot;cannot unpack %s from %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_sha1_signature
c_func
(paren
id|sha1
comma
id|data
comma
id|size
comma
id|type
)paren
)paren
(brace
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
id|sha1
)paren
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|macro|MAX_CHAIN
mdefine_line|#define MAX_CHAIN 40
DECL|function|show_pack_info
r_static
r_void
id|show_pack_info
c_func
(paren
r_struct
id|packed_git
op_star
id|p
)paren
(brace
r_struct
id|pack_header
op_star
id|hdr
suffix:semicolon
r_int
id|nr_objects
comma
id|i
suffix:semicolon
r_int
r_int
id|chain_histogram
(braket
id|MAX_CHAIN
)braket
suffix:semicolon
id|hdr
op_assign
id|p-&gt;pack_base
suffix:semicolon
id|nr_objects
op_assign
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_entries
)paren
suffix:semicolon
id|memset
c_func
(paren
id|chain_histogram
comma
l_int|0
comma
r_sizeof
(paren
id|chain_histogram
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
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|base_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|store_size
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|delta_chain_length
suffix:semicolon
r_if
c_cond
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error pack-check nth-packed-object&quot;
)paren
suffix:semicolon
id|offset
op_assign
id|find_pack_entry_one
c_func
(paren
id|sha1
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
id|die
c_func
(paren
l_string|&quot;internal error pack-check find-pack-entry-one&quot;
)paren
suffix:semicolon
id|packed_object_info_detail
c_func
(paren
id|p
comma
id|offset
comma
id|type
comma
op_amp
id|size
comma
op_amp
id|store_size
comma
op_amp
id|delta_chain_length
comma
id|base_sha1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s &quot;
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
op_logical_neg
id|delta_chain_length
)paren
id|printf
c_func
(paren
l_string|&quot;%-6s %lu %lu&bslash;n&quot;
comma
id|type
comma
id|size
comma
id|offset
)paren
suffix:semicolon
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%-6s %lu %lu %u %s&bslash;n&quot;
comma
id|type
comma
id|size
comma
id|offset
comma
id|delta_chain_length
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
id|delta_chain_length
OL
id|MAX_CHAIN
)paren
id|chain_histogram
(braket
id|delta_chain_length
)braket
op_increment
suffix:semicolon
r_else
id|chain_histogram
(braket
l_int|0
)braket
op_increment
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CHAIN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|chain_histogram
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;chain length %s %d: %d object%s&bslash;n&quot;
comma
id|i
ques
c_cond
l_string|&quot;=&quot;
suffix:colon
l_string|&quot;&gt;=&quot;
comma
id|i
ques
c_cond
id|i
suffix:colon
id|MAX_CHAIN
comma
id|chain_histogram
(braket
id|i
)braket
comma
l_int|1
OL
id|chain_histogram
(braket
id|i
)braket
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
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
r_int
id|verbose
)paren
(brace
r_int
r_int
id|index_size
op_assign
id|p-&gt;index_size
suffix:semicolon
r_void
op_star
id|index_base
op_assign
id|p-&gt;index_base
suffix:semicolon
id|SHA_CTX
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
id|ret
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Verify SHA1 sum of the index file */
id|SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|index_base
comma
id|index_size
l_int|20
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
id|hashcmp
c_func
(paren
id|sha1
comma
(paren
r_int
r_char
op_star
)paren
id|index_base
op_plus
id|index_size
l_int|20
)paren
)paren
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Packfile index for %s SHA1 mismatch&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
multiline_comment|/* Verify pack file */
id|use_packed_git
c_func
(paren
id|p
)paren
suffix:semicolon
id|ret
op_assign
id|verify_packfile
c_func
(paren
id|p
)paren
suffix:semicolon
id|unuse_packed_git
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_if
c_cond
(paren
id|ret
)paren
id|printf
c_func
(paren
l_string|&quot;%s: bad&bslash;n&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_else
(brace
id|use_packed_git
c_func
(paren
id|p
)paren
suffix:semicolon
id|show_pack_info
c_func
(paren
id|p
)paren
suffix:semicolon
id|unuse_packed_git
c_func
(paren
id|p
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s: ok&bslash;n&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
