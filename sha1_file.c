multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; *&n; * This handles basic git sha1 object files - packing, unpacking,&n; * creation etc.&n; */
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
eof
