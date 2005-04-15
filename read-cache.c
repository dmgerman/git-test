multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|variable|sha1_file_directory
r_const
r_char
op_star
id|sha1_file_directory
op_assign
l_int|NULL
suffix:semicolon
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
DECL|function|usage
r_void
id|usage
c_func
(paren
r_const
r_char
op_star
id|err
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|report
r_static
r_void
id|report
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|err
comma
id|va_list
id|params
)paren
(brace
id|fputs
c_func
(paren
id|prefix
comma
id|stderr
)paren
suffix:semicolon
id|vfprintf
c_func
(paren
id|stderr
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&bslash;n&quot;
comma
id|stderr
)paren
suffix:semicolon
)brace
DECL|function|die
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;fatal: &quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|error
r_int
id|error
c_func
(paren
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;error: &quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hexval
r_static
r_int
id|hexval
c_func
(paren
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
r_return
id|c
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;f&squot;
)paren
r_return
id|c
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;F&squot;
)paren
r_return
id|c
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
r_return
op_complement
l_int|0
suffix:semicolon
)brace
DECL|function|get_sha1_hex
r_int
id|get_sha1_hex
c_func
(paren
r_const
r_char
op_star
id|hex
comma
r_int
r_char
op_star
id|sha1
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|val
op_assign
(paren
id|hexval
c_func
(paren
id|hex
(braket
l_int|0
)braket
)paren
op_lshift
l_int|4
)paren
op_or
id|hexval
c_func
(paren
id|hex
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
op_complement
l_int|0xff
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|sha1
op_increment
op_assign
id|val
suffix:semicolon
id|hex
op_add_assign
l_int|2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sha1_to_hex
r_char
op_star
id|sha1_to_hex
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|50
)braket
suffix:semicolon
r_static
r_const
r_char
id|hex
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|val
op_assign
op_star
id|sha1
op_increment
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|hex
(braket
id|val
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|hex
(braket
id|val
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE! This returns a statically allocated buffer, so you have to be&n; * careful about using it. Do a &quot;strdup()&quot; if you need to save the&n; * filename.&n; */
DECL|function|sha1_file_name
r_char
op_star
id|sha1_file_name
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
id|i
suffix:semicolon
r_static
r_char
op_star
id|name
comma
op_star
id|base
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
r_char
op_star
id|sha1_file_directory
op_assign
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
ques
c_cond
suffix:colon
id|DEFAULT_DB_ENVIRONMENT
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|sha1_file_directory
)paren
suffix:semicolon
id|base
op_assign
id|malloc
c_func
(paren
id|len
op_plus
l_int|60
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|base
comma
id|sha1_file_directory
comma
id|len
)paren
suffix:semicolon
id|memset
c_func
(paren
id|base
op_plus
id|len
comma
l_int|0
comma
l_int|60
)paren
suffix:semicolon
id|base
(braket
id|len
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|base
(braket
id|len
op_plus
l_int|3
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|name
op_assign
id|base
op_plus
id|len
op_plus
l_int|1
suffix:semicolon
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_static
r_char
id|hex
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
r_int
r_int
id|val
op_assign
id|sha1
(braket
id|i
)braket
suffix:semicolon
r_char
op_star
id|pos
op_assign
id|name
op_plus
id|i
op_star
l_int|2
op_plus
(paren
id|i
OG
l_int|0
)paren
suffix:semicolon
op_star
id|pos
op_increment
op_assign
id|hex
(braket
id|val
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|pos
op_assign
id|hex
(braket
id|val
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
r_return
id|base
suffix:semicolon
)brace
DECL|function|check_sha1_signature
r_int
id|check_sha1_signature
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_void
op_star
id|map
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_char
id|real_sha1
(braket
l_int|20
)braket
suffix:semicolon
id|SHA_CTX
id|c
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
id|map
comma
id|size
)paren
suffix:semicolon
id|SHA1_Final
c_func
(paren
id|real_sha1
comma
op_amp
id|c
)paren
suffix:semicolon
r_return
id|memcmp
c_func
(paren
id|sha1
comma
id|real_sha1
comma
l_int|20
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|map_sha1_file
r_void
op_star
id|map_sha1_file
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_char
op_star
id|filename
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
l_int|NULL
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
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|NULL
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
l_int|NULL
suffix:semicolon
op_star
id|size
op_assign
id|st.st_size
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
DECL|function|unpack_sha1_file
r_void
op_star
id|unpack_sha1_file
c_func
(paren
r_void
op_star
id|map
comma
r_int
r_int
id|mapsize
comma
r_char
op_star
id|type
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_int
id|ret
comma
id|bytes
suffix:semicolon
id|z_stream
id|stream
suffix:semicolon
r_char
id|buffer
(braket
l_int|8192
)braket
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* Get the data stream */
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
id|map
suffix:semicolon
id|stream.avail_in
op_assign
id|mapsize
suffix:semicolon
id|stream.next_out
op_assign
id|buffer
suffix:semicolon
id|stream.avail_out
op_assign
r_sizeof
(paren
id|buffer
)paren
suffix:semicolon
id|inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buffer
comma
l_string|&quot;%10s %lu&quot;
comma
id|type
comma
id|size
)paren
op_ne
l_int|2
)paren
r_return
l_int|NULL
suffix:semicolon
id|bytes
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
op_plus
l_int|1
suffix:semicolon
id|buf
op_assign
id|malloc
c_func
(paren
op_star
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
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|buffer
op_plus
id|bytes
comma
id|stream.total_out
id|bytes
)paren
suffix:semicolon
id|bytes
op_assign
id|stream.total_out
id|bytes
suffix:semicolon
r_if
c_cond
(paren
id|bytes
OL
op_star
id|size
op_logical_and
id|ret
op_eq
id|Z_OK
)paren
(brace
id|stream.next_out
op_assign
id|buf
op_plus
id|bytes
suffix:semicolon
id|stream.avail_out
op_assign
op_star
id|size
id|bytes
suffix:semicolon
r_while
c_loop
(paren
id|inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
op_eq
id|Z_OK
)paren
multiline_comment|/* nothing */
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
DECL|function|read_sha1_file
r_void
op_star
id|read_sha1_file
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_char
op_star
id|type
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_int
r_int
id|mapsize
suffix:semicolon
r_void
op_star
id|map
comma
op_star
id|buf
suffix:semicolon
id|map
op_assign
id|map_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
)paren
(brace
id|buf
op_assign
id|unpack_sha1_file
c_func
(paren
id|map
comma
id|mapsize
comma
id|type
comma
id|size
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|mapsize
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|write_sha1_file
r_int
id|write_sha1_file
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
r_char
op_star
id|returnsha1
)paren
(brace
r_int
id|size
suffix:semicolon
r_char
op_star
id|compressed
suffix:semicolon
id|z_stream
id|stream
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|SHA_CTX
id|c
suffix:semicolon
multiline_comment|/* Set it up */
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
id|deflateInit
c_func
(paren
op_amp
id|stream
comma
id|Z_BEST_COMPRESSION
)paren
suffix:semicolon
id|size
op_assign
id|deflateBound
c_func
(paren
op_amp
id|stream
comma
id|len
)paren
suffix:semicolon
id|compressed
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/* Compress it */
id|stream.next_in
op_assign
id|buf
suffix:semicolon
id|stream.avail_in
op_assign
id|len
suffix:semicolon
id|stream.next_out
op_assign
id|compressed
suffix:semicolon
id|stream.avail_out
op_assign
id|size
suffix:semicolon
r_while
c_loop
(paren
id|deflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
op_eq
id|Z_OK
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|deflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|size
op_assign
id|stream.total_out
suffix:semicolon
multiline_comment|/* Sha1.. */
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
id|compressed
comma
id|size
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
id|write_sha1_buffer
c_func
(paren
id|sha1
comma
id|compressed
comma
id|size
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|returnsha1
)paren
id|memcpy
c_func
(paren
id|returnsha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|collision_check
r_static
r_inline
r_int
id|collision_check
c_func
(paren
r_char
op_star
id|filename
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
macro_line|#ifdef COLLISION_CHECK
r_void
op_star
id|map
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|cmp
suffix:semicolon
multiline_comment|/* Unreadable object, or object went away? Strange. */
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
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
OL
l_int|0
op_logical_or
id|size
op_ne
id|st.st_size
)paren
r_return
l_int|1
suffix:semicolon
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
id|cmp
op_assign
id|memcmp
c_func
(paren
id|buf
comma
id|map
comma
id|size
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_sha1_buffer
r_int
id|write_sha1_buffer
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
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
r_char
op_star
id|filename
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0666
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
id|errno
op_ne
id|EEXIST
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|collision_check
c_func
(paren
id|filename
comma
id|buf
comma
id|size
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;SHA1 collision detected!&quot;
l_string|&quot; This is bad, bad, BAD!&bslash;a&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|write
c_func
(paren
id|fd
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|ce-&gt;ce_mode
op_ne
id|htonl
c_func
(paren
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
id|len1
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|len2
)paren
(brace
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
id|ce_namelen
c_func
(paren
id|ce
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
op_ge
l_int|0
)paren
(brace
id|active_nr
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|active_nr
)paren
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
)brace
r_return
l_int|0
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
id|ce_namelen
c_func
(paren
id|ce
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
l_int|1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad version&quot;
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
m_offsetof
(paren
r_struct
id|cache_header
comma
id|sha1
)paren
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|hdr
op_plus
l_int|1
comma
id|size
r_sizeof
(paren
op_star
id|hdr
)paren
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
id|hdr-&gt;sha1
comma
l_int|20
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;bad header sha1&quot;
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
l_int|1
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
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
op_amp
id|hdr
comma
m_offsetof
(paren
r_struct
id|cache_header
comma
id|sha1
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
r_int
id|size
op_assign
id|ce_size
c_func
(paren
id|ce
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|ce
comma
id|size
)paren
suffix:semicolon
)brace
id|SHA1_Final
c_func
(paren
id|hdr.sha1
comma
op_amp
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
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
op_ne
r_sizeof
(paren
id|hdr
)paren
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
r_int
id|size
op_assign
id|ce_size
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|newfd
comma
id|ce
comma
id|size
)paren
op_ne
id|size
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
