macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;pack-revindex.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|macro|MAX_CHAIN
mdefine_line|#define MAX_CHAIN 50
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
r_uint32
id|nr_objects
comma
id|i
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_int
r_int
id|chain_histogram
(braket
id|MAX_CHAIN
op_plus
l_int|1
)braket
comma
id|baseobjects
suffix:semicolon
id|nr_objects
op_assign
id|p-&gt;num_objects
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
id|baseobjects
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
id|nr_objects
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
r_char
id|base_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|store_size
suffix:semicolon
id|off_t
id|offset
suffix:semicolon
r_int
r_int
id|delta_chain_length
suffix:semicolon
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
id|sha1
)paren
id|die
c_func
(paren
l_string|&quot;internal error pack-check nth-packed-object&quot;
)paren
suffix:semicolon
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
id|type
op_assign
id|packed_object_info_detail
c_func
(paren
id|p
comma
id|offset
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
(brace
id|printf
c_func
(paren
l_string|&quot;%-6s %lu %lu %&quot;
id|PRIuMAX
l_string|&quot;&bslash;n&quot;
comma
id|type
comma
id|size
comma
id|store_size
comma
(paren
r_uintmax
)paren
id|offset
)paren
suffix:semicolon
id|baseobjects
op_increment
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%-6s %lu %lu %&quot;
id|PRIuMAX
l_string|&quot; %u %s&bslash;n&quot;
comma
id|type
comma
id|size
comma
id|store_size
comma
(paren
r_uintmax
)paren
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
op_le
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
r_if
c_cond
(paren
id|baseobjects
)paren
id|printf
c_func
(paren
l_string|&quot;non delta: %lu object%s&bslash;n&quot;
comma
id|baseobjects
comma
id|baseobjects
OG
l_int|1
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|1
suffix:semicolon
id|cnt
op_le
id|MAX_CHAIN
suffix:semicolon
id|cnt
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|chain_histogram
(braket
id|cnt
)braket
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;chain length = %d: %lu object%s&bslash;n&quot;
comma
id|cnt
comma
id|chain_histogram
(braket
id|cnt
)braket
comma
id|chain_histogram
(braket
id|cnt
)braket
OG
l_int|1
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chain_histogram
(braket
l_int|0
)braket
)paren
id|printf
c_func
(paren
l_string|&quot;chain length &gt; %d: %lu object%s&bslash;n&quot;
comma
id|MAX_CHAIN
comma
id|chain_histogram
(braket
l_int|0
)braket
comma
id|chain_histogram
(braket
l_int|0
)braket
OG
l_int|1
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|function|verify_one_pack
r_static
r_int
id|verify_one_pack
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|verbose
)paren
(brace
r_char
id|arg
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|packed_git
op_star
id|pack
suffix:semicolon
r_int
id|err
suffix:semicolon
id|len
op_assign
id|strlcpy
c_func
(paren
id|arg
comma
id|path
comma
id|PATH_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|PATH_MAX
)paren
r_return
id|error
c_func
(paren
l_string|&quot;name too long: %s&quot;
comma
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * In addition to &quot;foo.idx&quot; we accept &quot;foo.pack&quot; and &quot;foo&quot;;&n;&t; * normalize these forms to &quot;foo.idx&quot; for add_packed_git().&n;&t; */
r_if
c_cond
(paren
id|has_extension
c_func
(paren
id|arg
comma
l_string|&quot;.pack&quot;
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|arg
op_plus
id|len
l_int|5
comma
l_string|&quot;.idx&quot;
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|has_extension
c_func
(paren
id|arg
comma
l_string|&quot;.idx&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
op_plus
l_int|4
op_ge
id|PATH_MAX
)paren
r_return
id|error
c_func
(paren
l_string|&quot;name too long: %s.idx&quot;
comma
id|arg
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|arg
op_plus
id|len
comma
l_string|&quot;.idx&quot;
)paren
suffix:semicolon
id|len
op_add_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * add_packed_git() uses our buffer (containing &quot;foo.idx&quot;) to&n;&t; * build the pack filename (&quot;foo.pack&quot;).  Make sure it fits.&n;&t; */
r_if
c_cond
(paren
id|len
op_plus
l_int|1
op_ge
id|PATH_MAX
)paren
(brace
id|arg
(braket
id|len
l_int|4
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;name too long: %s.pack&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
id|pack
op_assign
id|add_packed_git
c_func
(paren
id|arg
comma
id|len
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pack
)paren
r_return
id|error
c_func
(paren
l_string|&quot;packfile %s not found.&quot;
comma
id|arg
)paren
suffix:semicolon
id|install_packed_git
c_func
(paren
id|pack
)paren
suffix:semicolon
id|err
op_assign
id|verify_pack
c_func
(paren
id|pack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_if
c_cond
(paren
id|err
)paren
id|printf
c_func
(paren
l_string|&quot;%s: bad&bslash;n&quot;
comma
id|pack-&gt;pack_name
)paren
suffix:semicolon
r_else
(brace
id|show_pack_info
c_func
(paren
id|pack
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s: ok&bslash;n&quot;
comma
id|pack-&gt;pack_name
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|verify_pack_usage
r_static
r_const
r_char
op_star
r_const
id|verify_pack_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git verify-pack [-v|--verbose] &lt;pack&gt;...&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_verify_pack
r_int
id|cmd_verify_pack
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
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_const
r_struct
id|option
id|verify_pack_options
(braket
)braket
op_assign
(brace
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|verify_pack_options
comma
id|verify_pack_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|verify_pack_usage
comma
id|verify_pack_options
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|verify_one_pack
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|verbose
)paren
)paren
id|err
op_assign
l_int|1
suffix:semicolon
id|discard_revindex
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
eof
