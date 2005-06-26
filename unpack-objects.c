macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;delta.h&quot;
DECL|variable|dry_run
r_static
r_int
id|dry_run
suffix:semicolon
DECL|variable|nr_entries
r_static
r_int
id|nr_entries
suffix:semicolon
DECL|variable|base_name
r_static
r_const
r_char
op_star
id|base_name
suffix:semicolon
DECL|variable|unpack_usage
r_static
r_const
r_char
id|unpack_usage
(braket
)braket
op_assign
l_string|&quot;git-unpack-objects basename&quot;
suffix:semicolon
DECL|struct|pack_entry
r_struct
id|pack_entry
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* network byte order */
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
DECL|variable|pack_base
r_static
r_void
op_star
id|pack_base
suffix:semicolon
DECL|variable|pack_size
r_static
r_int
r_int
id|pack_size
suffix:semicolon
DECL|variable|index_base
r_static
r_void
op_star
id|index_base
suffix:semicolon
DECL|variable|index_size
r_static
r_int
r_int
id|index_size
suffix:semicolon
DECL|variable|pack_list
r_static
r_struct
id|pack_entry
op_star
op_star
id|pack_list
suffix:semicolon
DECL|function|map_file
r_static
r_void
op_star
id|map_file
c_func
(paren
r_const
r_char
op_star
id|suffix
comma
r_int
r_int
op_star
id|sizep
)paren
(brace
r_static
r_char
id|pathname
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
id|len
op_assign
id|snprintf
c_func
(paren
id|pathname
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
l_string|&quot;bad pack base-name&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|pathname
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to open &squot;%s&squot;&quot;
comma
id|pathname
)paren
suffix:semicolon
id|len
op_assign
id|st.st_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|die
c_func
(paren
l_string|&quot;bad pack file &squot;%s&squot;&quot;
comma
id|pathname
)paren
suffix:semicolon
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|len
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_eq
(paren
r_int
)paren
(paren
r_int
)paren
id|map
)paren
id|die
c_func
(paren
l_string|&quot;unable to mmap &squot;%s&squot;&quot;
comma
id|pathname
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
op_star
id|sizep
op_assign
id|len
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
DECL|function|sort_by_offset
r_static
r_int
id|sort_by_offset
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
id|pack_entry
op_star
id|a
op_assign
op_star
(paren
r_struct
id|pack_entry
op_star
op_star
)paren
id|_a
suffix:semicolon
r_struct
id|pack_entry
op_star
id|b
op_assign
op_star
(paren
r_struct
id|pack_entry
op_star
op_star
)paren
id|_b
suffix:semicolon
r_int
r_int
id|o1
comma
id|o2
suffix:semicolon
id|o1
op_assign
id|ntohl
c_func
(paren
id|a-&gt;offset
)paren
suffix:semicolon
id|o2
op_assign
id|ntohl
c_func
(paren
id|b-&gt;offset
)paren
suffix:semicolon
r_return
id|o1
OL
id|o2
ques
c_cond
l_int|1
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|check_index
r_static
r_int
id|check_index
c_func
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|array
op_assign
id|index_base
suffix:semicolon
r_int
r_int
id|nr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|index_size
OL
l_int|4
op_star
l_int|256
)paren
r_return
id|error
c_func
(paren
l_string|&quot;index file too small&quot;
)paren
suffix:semicolon
id|nr
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|n
op_assign
id|ntohl
c_func
(paren
id|array
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|nr
)paren
r_return
id|error
c_func
(paren
l_string|&quot;non-monotonic index&quot;
)paren
suffix:semicolon
id|nr
op_assign
id|n
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index_size
op_ne
l_int|4
op_star
l_int|256
op_plus
id|nr
op_star
l_int|24
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;index_size=%lu, expected %u (%u)&bslash;n&quot;
comma
id|index_size
comma
l_int|4
op_star
l_int|256
op_plus
id|nr
op_star
l_int|24
comma
id|nr
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;wrong index file size&quot;
)paren
suffix:semicolon
)brace
id|nr_entries
op_assign
id|nr
suffix:semicolon
id|pack_list
op_assign
id|xmalloc
c_func
(paren
id|nr
op_star
r_sizeof
(paren
r_struct
id|pack_entry
op_star
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
id|pack_list
(braket
id|i
)braket
op_assign
id|index_base
op_plus
l_int|4
op_star
l_int|256
op_plus
id|i
op_star
l_int|24
suffix:semicolon
id|qsort
c_func
(paren
id|pack_list
comma
id|nr
comma
r_sizeof
(paren
op_star
id|pack_list
)paren
comma
id|sort_by_offset
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d entries&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unpack_non_delta_entry
r_static
r_int
id|unpack_non_delta_entry
c_func
(paren
r_struct
id|pack_entry
op_star
id|entry
comma
r_int
id|kind
comma
r_int
r_char
op_star
id|data
comma
r_int
r_int
id|size
comma
r_int
r_int
id|left
)paren
(brace
r_int
id|st
suffix:semicolon
id|z_stream
id|stream
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|type_s
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %c %lu&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
comma
id|kind
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dry_run
)paren
r_return
l_int|0
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|size
op_plus
l_int|1
)paren
suffix:semicolon
id|buffer
(braket
id|size
)braket
op_assign
l_int|0
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
id|stream.next_in
op_assign
id|data
suffix:semicolon
id|stream.avail_in
op_assign
id|left
suffix:semicolon
id|stream.next_out
op_assign
id|buffer
suffix:semicolon
id|stream.avail_out
op_assign
id|size
suffix:semicolon
id|inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|st
op_assign
id|inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|st
op_ne
id|Z_STREAM_END
)paren
op_logical_or
id|stream.total_out
op_ne
id|size
)paren
r_goto
id|err_finish
suffix:semicolon
r_switch
c_cond
(paren
id|kind
)paren
(brace
r_case
l_char|&squot;C&squot;
suffix:colon
id|type_s
op_assign
l_string|&quot;commit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;T&squot;
suffix:colon
id|type_s
op_assign
l_string|&quot;tree&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;B&squot;
suffix:colon
id|type_s
op_assign
l_string|&quot;blob&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|err_finish
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|buffer
comma
id|size
comma
id|type_s
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;failed to write %s (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
comma
id|type_s
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|type_s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sha1
comma
id|entry-&gt;sha1
comma
l_int|20
)paren
)paren
id|die
c_func
(paren
l_string|&quot;resulting %s have wrong SHA1&quot;
comma
id|type_s
)paren
suffix:semicolon
id|finish
suffix:colon
id|st
op_assign
l_int|0
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|st
suffix:semicolon
id|err_finish
suffix:colon
id|st
op_assign
l_int|1
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
DECL|function|find_pack_entry
r_static
r_int
id|find_pack_entry
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_struct
id|pack_entry
op_star
op_star
id|ent
)paren
(brace
r_int
op_star
id|level1_ofs
op_assign
id|index_base
suffix:semicolon
r_int
id|hi
op_assign
id|ntohl
c_func
(paren
id|level1_ofs
(braket
op_star
id|sha1
)braket
)paren
suffix:semicolon
r_int
id|lo
op_assign
(paren
(paren
op_star
id|sha1
op_eq
l_int|0x0
)paren
ques
c_cond
l_int|0
suffix:colon
id|ntohl
c_func
(paren
id|level1_ofs
(braket
op_star
id|sha1
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_void
op_star
id|index
op_assign
id|index_base
op_plus
l_int|4
op_star
l_int|256
suffix:semicolon
r_do
(brace
r_int
id|mi
op_assign
(paren
id|lo
op_plus
id|hi
)paren
op_div
l_int|2
suffix:semicolon
r_int
id|cmp
op_assign
id|memcmp
c_func
(paren
id|index
op_plus
l_int|24
op_star
id|mi
op_plus
l_int|4
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;lo=%d mi=%d hi=%d cmp=%d&bslash;n&quot;
comma
id|lo
comma
id|mi
comma
id|hi
comma
id|cmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
(brace
op_star
id|ent
op_assign
id|index
op_plus
l_int|24
op_star
id|mi
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
id|hi
op_assign
id|mi
suffix:semicolon
r_else
id|lo
op_assign
id|mi
op_plus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|lo
OL
id|hi
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* forward declaration for a mutually recursive function */
r_static
r_void
id|unpack_entry
c_func
(paren
r_struct
id|pack_entry
op_star
)paren
suffix:semicolon
DECL|function|unpack_delta_entry
r_static
r_int
id|unpack_delta_entry
c_func
(paren
r_struct
id|pack_entry
op_star
id|entry
comma
r_int
r_char
op_star
id|base_sha1
comma
r_int
r_int
id|delta_size
comma
r_int
r_int
id|left
)paren
(brace
r_void
op_star
id|data
comma
op_star
id|delta_data
comma
op_star
id|result
comma
op_star
id|base
suffix:semicolon
r_int
r_int
id|data_size
comma
id|result_size
comma
id|base_size
suffix:semicolon
id|z_stream
id|stream
suffix:semicolon
r_int
id|st
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
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
id|left
OL
l_int|20
)paren
id|die
c_func
(paren
l_string|&quot;truncated pack file&quot;
)paren
suffix:semicolon
id|data
op_assign
id|base_sha1
op_plus
l_int|20
suffix:semicolon
id|data_size
op_assign
id|left
l_int|20
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s D %lu&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;sha1
)paren
comma
id|delta_size
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %s&bslash;n&quot;
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
id|dry_run
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* pack+5 is the base sha1, unless we have it, we need to&n;&t; * unpack it first.&n;&t; */
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
r_struct
id|pack_entry
op_star
id|base
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|find_pack_entry
c_func
(paren
id|base_sha1
comma
op_amp
id|base
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot find delta-pack base object&quot;
)paren
suffix:semicolon
id|unpack_entry
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
id|delta_data
op_assign
id|xmalloc
c_func
(paren
id|delta_size
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
id|stream.next_in
op_assign
id|data
suffix:semicolon
id|stream.avail_in
op_assign
id|data_size
suffix:semicolon
id|stream.next_out
op_assign
id|delta_data
suffix:semicolon
id|stream.avail_out
op_assign
id|delta_size
suffix:semicolon
id|inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|st
op_assign
id|inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|st
op_ne
id|Z_STREAM_END
)paren
op_logical_or
id|stream.total_out
op_ne
id|delta_size
)paren
id|die
c_func
(paren
l_string|&quot;delta data unpack failed&quot;
)paren
suffix:semicolon
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
id|patch_delta
c_func
(paren
id|base
comma
id|base_size
comma
id|delta_data
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
id|delta_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|result
comma
id|result_size
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
l_string|&quot;failed to write %s (%s)&quot;
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
id|free
c_func
(paren
id|result
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sha1
comma
id|entry-&gt;sha1
comma
l_int|20
)paren
)paren
id|die
c_func
(paren
l_string|&quot;resulting %s have wrong SHA1&quot;
comma
id|type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unpack_entry
r_static
r_void
id|unpack_entry
c_func
(paren
r_struct
id|pack_entry
op_star
id|entry
)paren
(brace
r_int
r_int
id|offset
comma
id|size
comma
id|left
suffix:semicolon
r_int
r_char
op_star
id|pack
suffix:semicolon
multiline_comment|/* Have we done this one already due to deltas based on it? */
r_if
c_cond
(paren
id|lookup_object
c_func
(paren
id|entry-&gt;sha1
)paren
)paren
r_return
suffix:semicolon
id|offset
op_assign
id|ntohl
c_func
(paren
id|entry-&gt;offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|pack_size
l_int|5
)paren
id|die
c_func
(paren
l_string|&quot;object offset outside of pack file&quot;
)paren
suffix:semicolon
id|pack
op_assign
id|pack_base
op_plus
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|pack
(braket
l_int|1
)braket
op_lshift
l_int|24
)paren
op_plus
(paren
id|pack
(braket
l_int|2
)braket
op_lshift
l_int|16
)paren
op_plus
(paren
id|pack
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
op_plus
id|pack
(braket
l_int|4
)braket
suffix:semicolon
id|left
op_assign
id|pack_size
id|offset
l_int|5
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|pack
)paren
(brace
r_case
l_char|&squot;C&squot;
suffix:colon
r_case
l_char|&squot;T&squot;
suffix:colon
r_case
l_char|&squot;B&squot;
suffix:colon
id|unpack_non_delta_entry
c_func
(paren
id|entry
comma
op_star
id|pack
comma
id|pack
op_plus
l_int|5
comma
id|size
comma
id|left
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
id|unpack_delta_entry
c_func
(paren
id|entry
comma
id|pack
op_plus
l_int|5
comma
id|size
comma
id|left
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;corrupted pack file&quot;
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
op_assign
id|nr_entries
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
id|pack_entry
op_star
id|entry
op_assign
id|pack_list
(braket
id|i
)braket
suffix:semicolon
id|unpack_entry
c_func
(paren
id|entry
)paren
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
id|usage
c_func
(paren
id|unpack_usage
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
id|unpack_usage
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
id|unpack_usage
)paren
suffix:semicolon
id|index_base
op_assign
id|map_file
c_func
(paren
l_string|&quot;idx&quot;
comma
op_amp
id|index_size
)paren
suffix:semicolon
id|pack_base
op_assign
id|map_file
c_func
(paren
l_string|&quot;pack&quot;
comma
op_amp
id|pack_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_index
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;bad index file&quot;
)paren
suffix:semicolon
id|unpack_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
