multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|variable|active_cache
r_struct
id|cache_entry
op_star
op_star
id|active_cache
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|active_nr
DECL|variable|active_alloc
r_int
r_int
id|active_nr
op_assign
l_int|0
comma
id|active_alloc
op_assign
l_int|0
suffix:semicolon
DECL|function|cache_match_stat
r_int
id|cache_match_stat
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_struct
id|stat
op_star
id|st
)paren
(brace
r_int
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_mtime.sec
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_mtime
)paren
)paren
id|changed
op_or_assign
id|MTIME_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_ctime.sec
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_ctime
)paren
)paren
id|changed
op_or_assign
id|CTIME_CHANGED
suffix:semicolon
macro_line|#ifdef NSEC
multiline_comment|/*&n;&t; * nsec seems unreliable - not all filesystems support it, so&n;&t; * as long as it is in the inode cache you get right nsec&n;&t; * but after it gets flushed, you get zero nsec.&n;&t; */
r_if
c_cond
(paren
id|ce-&gt;ce_mtime.nsec
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_mtim.tv_nsec
)paren
id|changed
op_or_assign
id|MTIME_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_ctime.nsec
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_ctim.tv_nsec
)paren
id|changed
op_or_assign
id|CTIME_CHANGED
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
id|ce-&gt;ce_uid
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_uid
)paren
op_logical_or
id|ce-&gt;ce_gid
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_gid
)paren
)paren
id|changed
op_or_assign
id|OWNER_CHANGED
suffix:semicolon
multiline_comment|/* We consider only the owner x bit to be relevant for &quot;mode changes&quot; */
r_if
c_cond
(paren
l_int|0100
op_amp
(paren
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_xor
id|st-&gt;st_mode
)paren
)paren
id|changed
op_or_assign
id|MODE_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_dev
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_dev
)paren
op_logical_or
id|ce-&gt;ce_ino
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_ino
)paren
)paren
id|changed
op_or_assign
id|INODE_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_size
op_ne
id|htonl
c_func
(paren
id|st-&gt;st_size
)paren
)paren
id|changed
op_or_assign
id|DATA_CHANGED
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|function|cache_name_compare
r_int
id|cache_name_compare
c_func
(paren
r_const
r_char
op_star
id|name1
comma
r_int
id|flags1
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|flags2
)paren
(brace
r_int
id|len1
op_assign
id|flags1
op_amp
id|CE_NAMEMASK
suffix:semicolon
r_int
id|len2
op_assign
id|flags2
op_amp
id|CE_NAMEMASK
suffix:semicolon
r_int
id|len
op_assign
id|len1
OL
id|len2
ques
c_cond
id|len1
suffix:colon
id|len2
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|cmp
op_assign
id|memcmp
c_func
(paren
id|name1
comma
id|name2
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
)paren
r_return
id|cmp
suffix:semicolon
r_if
c_cond
(paren
id|len1
OL
id|len2
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len1
OG
id|len2
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flags1
OL
id|flags2
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flags1
OG
id|flags2
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cache_name_pos
r_int
id|cache_name_pos
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
r_int
id|first
comma
id|last
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|last
op_assign
id|active_nr
suffix:semicolon
r_while
c_loop
(paren
id|last
OG
id|first
)paren
(brace
r_int
id|next
op_assign
(paren
id|last
op_plus
id|first
)paren
op_rshift
l_int|1
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|next
)braket
suffix:semicolon
r_int
id|cmp
op_assign
id|cache_name_compare
c_func
(paren
id|name
comma
id|namelen
comma
id|ce-&gt;name
comma
id|htons
c_func
(paren
id|ce-&gt;ce_flags
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|next
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|last
op_assign
id|next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|first
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|first
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Remove entry, return true if there are more entries to go.. */
DECL|function|remove_entry_at
r_static
r_int
id|remove_entry_at
c_func
(paren
r_int
id|pos
)paren
(brace
id|active_nr
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|active_nr
)paren
r_return
l_int|0
suffix:semicolon
id|memmove
c_func
(paren
id|active_cache
op_plus
id|pos
comma
id|active_cache
op_plus
id|pos
op_plus
l_int|1
comma
(paren
id|active_nr
id|pos
)paren
op_star
r_sizeof
(paren
r_struct
id|cache_entry
op_star
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|remove_file_from_cache
r_int
id|remove_file_from_cache
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|active_nr
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|path
)paren
)paren
id|remove_entry_at
c_func
(paren
id|pos
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|same_name
r_static
r_int
id|same_name
c_func
(paren
r_struct
id|cache_entry
op_star
id|a
comma
r_struct
id|cache_entry
op_star
id|b
)paren
(brace
r_int
id|len
op_assign
id|ce_namelen
c_func
(paren
id|a
)paren
suffix:semicolon
r_return
id|ce_namelen
c_func
(paren
id|b
)paren
op_eq
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|add_cache_entry
r_int
id|add_cache_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
id|ok_to_add
)paren
(brace
r_int
id|pos
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|ce-&gt;name
comma
id|htons
c_func
(paren
id|ce-&gt;ce_flags
)paren
)paren
suffix:semicolon
multiline_comment|/* existing match? Just replace it */
r_if
c_cond
(paren
id|pos
op_ge
l_int|0
)paren
(brace
id|active_cache
(braket
id|pos
)braket
op_assign
id|ce
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Inserting a merged entry (&quot;stage 0&quot;) into the index&n;&t; * will always replace all non-merged entries..&n;&t; */
r_if
c_cond
(paren
id|pos
OL
id|active_nr
op_logical_and
id|ce_stage
c_func
(paren
id|ce
)paren
op_eq
l_int|0
)paren
(brace
r_while
c_loop
(paren
id|same_name
c_func
(paren
id|active_cache
(braket
id|pos
)braket
comma
id|ce
)paren
)paren
(brace
id|ok_to_add
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remove_entry_at
c_func
(paren
id|pos
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ok_to_add
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Make sure the array is big enough .. */
r_if
c_cond
(paren
id|active_nr
op_eq
id|active_alloc
)paren
(brace
id|active_alloc
op_assign
id|alloc_nr
c_func
(paren
id|active_alloc
)paren
suffix:semicolon
id|active_cache
op_assign
id|realloc
c_func
(paren
id|active_cache
comma
id|active_alloc
op_star
r_sizeof
(paren
r_struct
id|cache_entry
op_star
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Add it in.. */
id|active_nr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|active_nr
OG
id|pos
)paren
id|memmove
c_func
(paren
id|active_cache
op_plus
id|pos
op_plus
l_int|1
comma
id|active_cache
op_plus
id|pos
comma
(paren
id|active_nr
id|pos
l_int|1
)paren
op_star
r_sizeof
(paren
id|ce
)paren
)paren
suffix:semicolon
id|active_cache
(braket
id|pos
)braket
op_assign
id|ce
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|verify_hdr
r_static
r_int
id|verify_hdr
c_func
(paren
r_struct
id|cache_header
op_star
id|hdr
comma
r_int
r_int
id|size
)paren
(brace
id|SHA_CTX
id|c
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
id|hdr-&gt;hdr_signature
op_ne
id|htonl
c_func
(paren
id|CACHE_SIGNATURE
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad signature&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;hdr_version
op_ne
id|htonl
c_func
(paren
l_int|2
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad index version&quot;
)paren
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
id|size
l_int|20
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
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sha1
comma
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|size
l_int|20
comma
l_int|20
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad index file sha1 signature&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_cache
r_int
id|read_cache
c_func
(paren
r_void
)paren
(brace
r_int
id|fd
comma
id|i
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
r_int
id|size
comma
id|offset
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
r_struct
id|cache_header
op_star
id|hdr
suffix:semicolon
id|errno
op_assign
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|active_cache
)paren
r_return
id|error
c_func
(paren
l_string|&quot;more than one cachefile&quot;
)paren
suffix:semicolon
id|errno
op_assign
id|ENOENT
suffix:semicolon
id|sha1_file_directory
op_assign
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sha1_file_directory
)paren
id|sha1_file_directory
op_assign
id|DEFAULT_DB_ENVIRONMENT
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|sha1_file_directory
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;no access to SHA1 file directory&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
l_string|&quot;.git/index&quot;
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
r_return
(paren
id|errno
op_eq
id|ENOENT
)paren
ques
c_cond
l_int|0
suffix:colon
id|error
c_func
(paren
l_string|&quot;open failed&quot;
)paren
suffix:semicolon
id|size
op_assign
l_int|0
suffix:semicolon
singleline_comment|// avoid gcc warning
id|map
op_assign
(paren
r_void
op_star
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
id|size
op_assign
id|st.st_size
suffix:semicolon
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
r_sizeof
(paren
r_struct
id|cache_header
)paren
op_plus
l_int|20
)paren
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|size
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
)brace
id|close
c_func
(paren
id|fd
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
r_return
id|error
c_func
(paren
l_string|&quot;mmap failed&quot;
)paren
suffix:semicolon
id|hdr
op_assign
id|map
suffix:semicolon
r_if
c_cond
(paren
id|verify_hdr
c_func
(paren
id|hdr
comma
id|size
)paren
OL
l_int|0
)paren
r_goto
id|unmap
suffix:semicolon
id|active_nr
op_assign
id|ntohl
c_func
(paren
id|hdr-&gt;hdr_entries
)paren
suffix:semicolon
id|active_alloc
op_assign
id|alloc_nr
c_func
(paren
id|active_nr
)paren
suffix:semicolon
id|active_cache
op_assign
id|calloc
c_func
(paren
id|active_alloc
comma
r_sizeof
(paren
r_struct
id|cache_entry
op_star
)paren
)paren
suffix:semicolon
id|offset
op_assign
r_sizeof
(paren
op_star
id|hdr
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|map
op_plus
id|offset
suffix:semicolon
id|offset
op_assign
id|offset
op_plus
id|ce_size
c_func
(paren
id|ce
)paren
suffix:semicolon
id|active_cache
(braket
id|i
)braket
op_assign
id|ce
suffix:semicolon
)brace
r_return
id|active_nr
suffix:semicolon
id|unmap
suffix:colon
id|munmap
c_func
(paren
id|map
comma
id|size
)paren
suffix:semicolon
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;verify header failed&quot;
)paren
suffix:semicolon
)brace
DECL|macro|WRITE_BUFFER_SIZE
mdefine_line|#define WRITE_BUFFER_SIZE 8192
DECL|variable|write_buffer
r_static
r_char
id|write_buffer
(braket
id|WRITE_BUFFER_SIZE
)braket
suffix:semicolon
DECL|variable|write_buffer_len
r_static
r_int
r_int
id|write_buffer_len
suffix:semicolon
DECL|function|ce_write
r_static
r_int
id|ce_write
c_func
(paren
id|SHA_CTX
op_star
id|context
comma
r_int
id|fd
comma
r_void
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
r_int
id|buffered
op_assign
id|write_buffer_len
suffix:semicolon
r_int
r_int
id|partial
op_assign
id|WRITE_BUFFER_SIZE
id|buffered
suffix:semicolon
r_if
c_cond
(paren
id|partial
OG
id|len
)paren
id|partial
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|write_buffer
op_plus
id|buffered
comma
id|data
comma
id|partial
)paren
suffix:semicolon
id|buffered
op_add_assign
id|partial
suffix:semicolon
r_if
c_cond
(paren
id|buffered
op_eq
id|WRITE_BUFFER_SIZE
)paren
(brace
id|SHA1_Update
c_func
(paren
id|context
comma
id|write_buffer
comma
id|WRITE_BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|write_buffer
comma
id|WRITE_BUFFER_SIZE
)paren
op_ne
id|WRITE_BUFFER_SIZE
)paren
r_return
l_int|1
suffix:semicolon
id|buffered
op_assign
l_int|0
suffix:semicolon
)brace
id|write_buffer_len
op_assign
id|buffered
suffix:semicolon
id|len
op_sub_assign
id|partial
suffix:semicolon
id|data
op_add_assign
id|partial
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ce_flush
r_static
r_int
id|ce_flush
c_func
(paren
id|SHA_CTX
op_star
id|context
comma
r_int
id|fd
)paren
(brace
r_int
r_int
id|left
op_assign
id|write_buffer_len
suffix:semicolon
r_if
c_cond
(paren
id|left
)paren
(brace
id|write_buffer_len
op_assign
l_int|0
suffix:semicolon
id|SHA1_Update
c_func
(paren
id|context
comma
id|write_buffer
comma
id|left
)paren
suffix:semicolon
)brace
multiline_comment|/* Append the SHA1 signature at the end */
id|SHA1_Final
c_func
(paren
id|write_buffer
op_plus
id|left
comma
id|context
)paren
suffix:semicolon
id|left
op_add_assign
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|write_buffer
comma
id|left
)paren
op_ne
id|left
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_cache
r_int
id|write_cache
c_func
(paren
r_int
id|newfd
comma
r_struct
id|cache_entry
op_star
op_star
id|cache
comma
r_int
id|entries
)paren
(brace
id|SHA_CTX
id|c
suffix:semicolon
r_struct
id|cache_header
id|hdr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hdr.hdr_signature
op_assign
id|htonl
c_func
(paren
id|CACHE_SIGNATURE
)paren
suffix:semicolon
id|hdr.hdr_version
op_assign
id|htonl
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|hdr.hdr_entries
op_assign
id|htonl
c_func
(paren
id|entries
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
id|ce_write
c_func
(paren
op_amp
id|c
comma
id|newfd
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
OL
l_int|0
)paren
r_return
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_write
c_func
(paren
op_amp
id|c
comma
id|newfd
comma
id|ce
comma
id|ce_size
c_func
(paren
id|ce
)paren
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|ce_flush
c_func
(paren
op_amp
id|c
comma
id|newfd
)paren
suffix:semicolon
)brace
eof
