macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;rev-cache.h&quot;
DECL|variable|rev_cache
r_struct
id|rev_cache
op_star
op_star
id|rev_cache
suffix:semicolon
DECL|variable|nr_revs
DECL|variable|alloc_revs
r_int
id|nr_revs
comma
id|alloc_revs
suffix:semicolon
DECL|variable|rle_free
r_static
r_struct
id|rev_list_elem
op_star
id|rle_free
suffix:semicolon
DECL|macro|BATCH_SIZE
mdefine_line|#define BATCH_SIZE 512
DECL|function|find_rev_cache
r_int
id|find_rev_cache
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|lo
op_assign
l_int|0
comma
id|hi
op_assign
id|nr_revs
suffix:semicolon
r_while
c_loop
(paren
id|lo
OL
id|hi
)paren
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
r_struct
id|rev_cache
op_star
id|ri
op_assign
id|rev_cache
(braket
id|mi
)braket
suffix:semicolon
r_int
id|cmp
op_assign
id|memcmp
c_func
(paren
id|sha1
comma
id|ri-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|mi
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
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
r_return
id|lo
l_int|1
suffix:semicolon
)brace
DECL|function|alloc_list_elem
r_static
r_struct
id|rev_list_elem
op_star
id|alloc_list_elem
c_func
(paren
r_void
)paren
(brace
r_struct
id|rev_list_elem
op_star
id|rle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rle_free
)paren
(brace
r_int
id|i
suffix:semicolon
id|rle
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rle
)paren
op_star
id|BATCH_SIZE
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
id|BATCH_SIZE
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rle
(braket
id|i
)braket
dot
id|ri
op_assign
l_int|NULL
suffix:semicolon
id|rle
(braket
id|i
)braket
dot
id|next
op_assign
op_amp
id|rle
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|rle
(braket
id|BATCH_SIZE
l_int|1
)braket
dot
id|ri
op_assign
l_int|NULL
suffix:semicolon
id|rle
(braket
id|BATCH_SIZE
l_int|1
)braket
dot
id|next
op_assign
l_int|NULL
suffix:semicolon
id|rle_free
op_assign
id|rle
suffix:semicolon
)brace
id|rle
op_assign
id|rle_free
suffix:semicolon
id|rle_free
op_assign
id|rle-&gt;next
suffix:semicolon
r_return
id|rle
suffix:semicolon
)brace
DECL|function|create_rev_cache
r_static
r_struct
id|rev_cache
op_star
id|create_rev_cache
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|rev_cache
op_star
id|ri
suffix:semicolon
r_int
id|pos
op_assign
id|find_rev_cache
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
r_return
id|rev_cache
(braket
id|pos
)braket
suffix:semicolon
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|alloc_revs
op_le
op_increment
id|nr_revs
)paren
(brace
id|alloc_revs
op_assign
id|alloc_nr
c_func
(paren
id|alloc_revs
)paren
suffix:semicolon
id|rev_cache
op_assign
id|xrealloc
c_func
(paren
id|rev_cache
comma
r_sizeof
(paren
id|ri
)paren
op_star
id|alloc_revs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OL
id|nr_revs
)paren
id|memmove
c_func
(paren
id|rev_cache
op_plus
id|pos
op_plus
l_int|1
comma
id|rev_cache
op_plus
id|pos
comma
(paren
id|nr_revs
id|pos
l_int|1
)paren
op_star
r_sizeof
(paren
id|ri
)paren
)paren
suffix:semicolon
id|ri
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ri
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ri-&gt;sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|rev_cache
(braket
id|pos
)braket
op_assign
id|ri
suffix:semicolon
r_return
id|ri
suffix:semicolon
)brace
DECL|variable|last_sha1
r_static
r_int
r_char
id|last_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|write_one_rev_cache
r_static
r_void
id|write_one_rev_cache
c_func
(paren
id|FILE
op_star
id|rev_cache_file
comma
r_struct
id|rev_cache
op_star
id|ri
)paren
(brace
r_int
r_char
id|flag
suffix:semicolon
r_struct
id|rev_list_elem
op_star
id|rle
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;written
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;parsed
)paren
(brace
multiline_comment|/* We use last_sha1 compression only for the first parent;&n;&t;&t; * otherwise the resulting rev-cache would lose the parent&n;&t;&t; * order information.&n;&t;&t; */
r_if
c_cond
(paren
id|ri-&gt;parents
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ri-&gt;parents-&gt;ri-&gt;sha1
comma
id|last_sha1
comma
l_int|20
)paren
)paren
id|flag
op_assign
(paren
id|ri-&gt;num_parents
l_int|1
)paren
op_or
l_int|0x80
suffix:semicolon
r_else
id|flag
op_assign
id|ri-&gt;num_parents
suffix:semicolon
id|fwrite
c_func
(paren
id|ri-&gt;sha1
comma
l_int|20
comma
l_int|1
comma
id|rev_cache_file
)paren
suffix:semicolon
id|fwrite
c_func
(paren
op_amp
id|flag
comma
l_int|1
comma
l_int|1
comma
id|rev_cache_file
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rle
op_assign
id|ri-&gt;parents
suffix:semicolon
id|rle
suffix:semicolon
id|rle
op_assign
id|rle-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|flag
op_amp
l_int|0x80
op_logical_and
id|rle
op_eq
id|ri-&gt;parents
)paren
r_continue
suffix:semicolon
id|fwrite
c_func
(paren
id|rle-&gt;ri-&gt;sha1
comma
l_int|20
comma
l_int|1
comma
id|rev_cache_file
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|last_sha1
comma
id|ri-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
id|ri-&gt;written
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* recursively write children depth first */
r_for
c_loop
(paren
id|rle
op_assign
id|ri-&gt;children
suffix:semicolon
id|rle
suffix:semicolon
id|rle
op_assign
id|rle-&gt;next
)paren
id|write_one_rev_cache
c_func
(paren
id|rev_cache_file
comma
id|rle-&gt;ri
)paren
suffix:semicolon
)brace
DECL|function|write_rev_cache
r_void
id|write_rev_cache
c_func
(paren
r_const
r_char
op_star
id|newpath
comma
r_const
r_char
op_star
id|oldpath
)paren
(brace
multiline_comment|/* write the following commit ancestry information in&n;&t; * $GIT_DIR/info/rev-cache.&n;&t; *&n;&t; * The format is:&n;&t; * 20-byte SHA1 (commit ID)&n;&t; * 1-byte flag:&n;&t; * - bit 0-6 records &quot;number of parent commit SHA1s to&n;&t; *   follow&quot; (i.e. up to 127 children can be listed).&n;&t; * - when the bit 7 is on, then &quot;the entry immediately&n;&t; *   before this entry is one of the parents of this&n;         *   commit&quot;.&n;&t; * N x 20-byte SHA1 (parent commit IDs)&n;&t; */
id|FILE
op_star
id|rev_cache_file
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|rev_cache
op_star
id|ri
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|newpath
comma
id|oldpath
)paren
)paren
(brace
multiline_comment|/* If we are doing it in place */
id|rev_cache_file
op_assign
id|fopen
c_func
(paren
id|newpath
comma
l_string|&quot;a&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_char
id|buf
(braket
l_int|8096
)braket
suffix:semicolon
r_int
id|sz
suffix:semicolon
id|FILE
op_star
id|oldfp
op_assign
id|fopen
c_func
(paren
id|oldpath
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|rev_cache_file
op_assign
id|fopen
c_func
(paren
id|newpath
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldfp
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|sz
op_assign
id|fread
c_func
(paren
id|buf
comma
l_int|1
comma
r_sizeof
(paren
id|buf
)paren
comma
id|oldfp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|fwrite
c_func
(paren
id|buf
comma
l_int|1
comma
id|sz
comma
id|rev_cache_file
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|oldfp
)paren
suffix:semicolon
)brace
)brace
id|memset
c_func
(paren
id|last_sha1
comma
l_int|0
comma
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Go through available rev_cache structures, starting from&n;&t; * parentless ones first, so that we would get most out of&n;&t; * last_sha1 optimization by the depth first behaviour of&n;&t; * write_one_rev_cache().&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_revs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ri
op_assign
id|rev_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;num_parents
)paren
r_continue
suffix:semicolon
id|write_one_rev_cache
c_func
(paren
id|rev_cache_file
comma
id|ri
)paren
suffix:semicolon
)brace
multiline_comment|/* Then the rest */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_revs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ri
op_assign
id|rev_cache
(braket
id|i
)braket
suffix:semicolon
id|write_one_rev_cache
c_func
(paren
id|rev_cache_file
comma
id|ri
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|rev_cache_file
)paren
suffix:semicolon
)brace
DECL|function|add_parent
r_static
r_void
id|add_parent
c_func
(paren
r_struct
id|rev_cache
op_star
id|child
comma
r_const
r_int
r_char
op_star
id|parent_sha1
)paren
(brace
r_struct
id|rev_cache
op_star
id|parent
op_assign
id|create_rev_cache
c_func
(paren
id|parent_sha1
)paren
suffix:semicolon
r_struct
id|rev_list_elem
op_star
id|e
op_assign
id|alloc_list_elem
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Keep the parent list ordered in the same way the commit&n;&t; * object records them.&n;&t; */
id|e-&gt;ri
op_assign
id|parent
suffix:semicolon
id|e-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child-&gt;parents_tail
)paren
id|child-&gt;parents
op_assign
id|e
suffix:semicolon
r_else
id|child-&gt;parents_tail-&gt;next
op_assign
id|e
suffix:semicolon
id|child-&gt;parents_tail
op_assign
id|e
suffix:semicolon
id|child-&gt;num_parents
op_increment
suffix:semicolon
multiline_comment|/* There is no inherent order of the children so we just&n;&t; * LIFO them together.&n;&t; */
id|e
op_assign
id|alloc_list_elem
c_func
(paren
)paren
suffix:semicolon
id|e-&gt;next
op_assign
id|parent-&gt;children
suffix:semicolon
id|parent-&gt;children
op_assign
id|e
suffix:semicolon
id|e-&gt;ri
op_assign
id|child
suffix:semicolon
id|parent-&gt;num_children
op_increment
suffix:semicolon
)brace
DECL|function|read_rev_cache
r_int
id|read_rev_cache
c_func
(paren
r_const
r_char
op_star
id|path
comma
id|FILE
op_star
id|dumpfile
comma
r_int
id|dry_run
)paren
(brace
r_int
r_char
op_star
id|map
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
r_int
id|ofs
comma
id|len
suffix:semicolon
r_struct
id|rev_cache
op_star
id|ri
op_assign
l_int|NULL
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
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
)paren
(brace
r_if
c_cond
(paren
id|dry_run
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot open %s&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|st.st_size
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_eq
id|MAP_FAILED
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|last_sha1
comma
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|ofs
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|st.st_size
suffix:semicolon
r_while
c_loop
(paren
id|ofs
OL
id|len
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|flag
comma
id|cnt
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|ofs
op_plus
l_int|21
)paren
id|die
c_func
(paren
l_string|&quot;rev-cache too short&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sha1
comma
id|map
op_plus
id|ofs
comma
l_int|20
)paren
suffix:semicolon
id|flag
op_assign
id|map
(braket
id|ofs
op_plus
l_int|20
)braket
suffix:semicolon
id|ofs
op_add_assign
l_int|21
suffix:semicolon
id|cnt
op_assign
(paren
id|flag
op_amp
l_int|0x7f
)paren
op_plus
(paren
(paren
id|flag
op_amp
l_int|0x80
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|ofs
op_plus
(paren
id|flag
op_amp
l_int|0x7f
)paren
op_star
l_int|20
)paren
id|die
c_func
(paren
l_string|&quot;rev-cache too short to have %d more parents&quot;
comma
(paren
id|flag
op_amp
l_int|0x7f
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dumpfile
)paren
id|fprintf
c_func
(paren
id|dumpfile
comma
l_string|&quot;%s&quot;
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
id|dry_run
)paren
(brace
id|ri
op_assign
id|create_rev_cache
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ri
)paren
id|die
c_func
(paren
l_string|&quot;cannot create rev-cache for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|ri-&gt;written
op_assign
id|ri-&gt;parsed
op_assign
l_int|1
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dry_run
)paren
id|add_parent
c_func
(paren
id|ri
comma
id|last_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dumpfile
)paren
id|fprintf
c_func
(paren
id|dumpfile
comma
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|last_sha1
)paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_increment
OL
id|cnt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dry_run
)paren
id|add_parent
c_func
(paren
id|ri
comma
id|map
op_plus
id|ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dumpfile
)paren
id|fprintf
c_func
(paren
id|dumpfile
comma
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|last_sha1
)paren
)paren
suffix:semicolon
id|ofs
op_add_assign
l_int|20
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dumpfile
)paren
id|fprintf
c_func
(paren
id|dumpfile
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|last_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ofs
op_ne
id|len
)paren
id|die
c_func
(paren
l_string|&quot;rev-cache truncated?&quot;
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|record_rev_cache
r_int
id|record_rev_cache
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
id|FILE
op_star
id|dumpfile
)paren
(brace
r_int
r_char
id|parent
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
comma
id|ofs
suffix:semicolon
r_int
r_int
id|cnt
comma
id|i
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_struct
id|rev_cache
op_star
id|ri
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
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
id|buf
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: not found&quot;
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
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;commit&quot;
)paren
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;%s: not a commit but a %s&quot;
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
)brace
id|ri
op_assign
id|create_rev_cache
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ri-&gt;parsed
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dumpfile
)paren
id|fprintf
c_func
(paren
id|dumpfile
comma
l_string|&quot;commit %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
id|ofs
op_assign
l_int|46
suffix:semicolon
multiline_comment|/* &quot;tree &quot; + hex-sha1 + &quot;&bslash;n&quot; */
r_while
c_loop
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buf
op_plus
id|ofs
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
op_logical_and
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|buf
op_plus
id|ofs
op_plus
l_int|7
comma
id|parent
)paren
)paren
(brace
id|ofs
op_add_assign
l_int|48
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
op_star
l_int|48
op_plus
l_int|46
op_ne
id|ofs
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;internal error in record_rev_cache&quot;
)paren
suffix:semicolon
)brace
id|ri
op_assign
id|create_rev_cache
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|ri-&gt;parsed
op_assign
l_int|1
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|parent_sha1
(braket
l_int|20
)braket
suffix:semicolon
id|ofs
op_assign
l_int|46
op_plus
id|i
op_star
l_int|48
op_plus
l_int|7
suffix:semicolon
id|get_sha1_hex
c_func
(paren
id|buf
op_plus
id|ofs
comma
id|parent_sha1
)paren
suffix:semicolon
id|add_parent
c_func
(paren
id|ri
comma
id|parent_sha1
)paren
suffix:semicolon
id|record_rev_cache
c_func
(paren
id|parent_sha1
comma
id|dumpfile
)paren
suffix:semicolon
)brace
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
eof
