multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; *&n; * This handles basic git sha1 object files - packing, unpacking,&n; * creation etc.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;delta.h&quot;
macro_line|#ifndef O_NOATIME
macro_line|#if defined(__linux__) &amp;&amp; (defined(__i386__) || defined(__PPC__))
DECL|macro|O_NOATIME
mdefine_line|#define O_NOATIME 01000000
macro_line|#else
DECL|macro|O_NOATIME
mdefine_line|#define O_NOATIME 0
macro_line|#endif
macro_line|#endif
DECL|variable|sha1_file_open_flag
r_static
r_int
r_int
id|sha1_file_open_flag
op_assign
id|O_NOATIME
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
DECL|function|get_sha1_file
r_static
r_int
id|get_sha1_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_char
op_star
id|result
)paren
(brace
r_char
id|buffer
(braket
l_int|60
)braket
suffix:semicolon
r_int
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
r_int
id|len
suffix:semicolon
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
id|len
op_assign
id|read
c_func
(paren
id|fd
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
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
id|len
OL
l_int|40
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|result
)paren
suffix:semicolon
)brace
DECL|variable|git_dir
DECL|variable|git_object_dir
DECL|variable|git_index_file
r_static
r_char
op_star
id|git_dir
comma
op_star
id|git_object_dir
comma
op_star
id|git_index_file
suffix:semicolon
DECL|function|setup_git_env
r_static
r_void
id|setup_git_env
c_func
(paren
r_void
)paren
(brace
id|git_dir
op_assign
id|gitenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_dir
)paren
id|git_dir
op_assign
id|DEFAULT_GIT_DIR_ENVIRONMENT
suffix:semicolon
id|git_object_dir
op_assign
id|gitenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_object_dir
)paren
(brace
id|git_object_dir
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|git_dir
)paren
op_plus
l_int|9
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|git_object_dir
comma
l_string|&quot;%s/objects&quot;
comma
id|git_dir
)paren
suffix:semicolon
)brace
id|git_index_file
op_assign
id|gitenv
c_func
(paren
id|INDEX_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_index_file
)paren
(brace
id|git_index_file
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|git_dir
)paren
op_plus
l_int|7
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|git_index_file
comma
l_string|&quot;%s/index&quot;
comma
id|git_dir
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_object_directory
r_char
op_star
id|get_object_directory
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_object_dir
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_object_dir
suffix:semicolon
)brace
DECL|function|get_index_file
r_char
op_star
id|get_index_file
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_index_file
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_index_file
suffix:semicolon
)brace
DECL|function|get_sha1
r_int
id|get_sha1
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_char
id|pathname
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_static
r_const
r_char
op_star
id|prefix
(braket
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;refs&quot;
comma
l_string|&quot;refs/tags&quot;
comma
l_string|&quot;refs/heads&quot;
comma
l_string|&quot;refs/snap&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|str
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_dir
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|prefix
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
id|snprintf
c_func
(paren
id|pathname
comma
r_sizeof
(paren
id|pathname
)paren
comma
l_string|&quot;%s/%s/%s&quot;
comma
id|git_dir
comma
op_star
id|p
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_file
c_func
(paren
id|pathname
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
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
DECL|function|fill_sha1_path
r_static
r_void
id|fill_sha1_path
c_func
(paren
r_char
op_star
id|pathbuf
comma
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
id|pathbuf
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
)brace
multiline_comment|/*&n; * NOTE! This returns a statically allocated buffer, so you have to be&n; * careful about using it. Do a &quot;strdup()&quot; if you need to save the&n; * filename.&n; *&n; * Also note that this returns the location for creating.  Reading&n; * SHA1 file can happen from any alternate directory listed in the&n; * DB_ENVIRONMENT environment variable if it is not found in&n; * the primary object database.&n; */
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
r_const
r_char
op_star
id|sha1_file_directory
op_assign
id|get_object_directory
c_func
(paren
)paren
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
id|xmalloc
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
id|fill_sha1_path
c_func
(paren
id|name
comma
id|sha1
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
DECL|struct|alternate_object_database
r_static
r_struct
id|alternate_object_database
(brace
DECL|member|base
r_char
op_star
id|base
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|alt_odb
)brace
op_star
id|alt_odb
suffix:semicolon
multiline_comment|/*&n; * Prepare alternate object database registry.&n; * alt_odb points at an array of struct alternate_object_database.&n; * This array is terminated with an element that has both its base&n; * and name set to NULL.  alt_odb[n] comes from n&squot;th non-empty&n; * element from colon separated ALTERNATE_DB_ENVIRONMENT environment&n; * variable, and its base points at a statically allocated buffer&n; * that contains &quot;/the/directory/corresponding/to/.git/objects/...&quot;,&n; * while its name points just after the slash at the end of&n; * &quot;.git/objects/&quot; in the example above, and has enough space to hold&n; * 40-byte hex SHA1, an extra slash for the first level indirection,&n; * and the terminating NUL.&n; * This function allocates the alt_odb array and all the strings&n; * pointed by base fields of the array elements with one xmalloc();&n; * the string pool immediately follows the array.&n; */
DECL|function|prepare_alt_odb
r_static
r_void
id|prepare_alt_odb
c_func
(paren
r_void
)paren
(brace
r_int
id|pass
comma
id|totlen
comma
id|i
suffix:semicolon
r_const
r_char
op_star
id|cp
comma
op_star
id|last
suffix:semicolon
r_char
op_star
id|op
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|alt
op_assign
id|gitenv
c_func
(paren
id|ALTERNATE_DB_ENVIRONMENT
)paren
ques
c_cond
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* The first pass counts how large an area to allocate to&n;&t; * hold the entire alt_odb structure, including array of&n;&t; * structs and path buffers for them.  The second pass fills&n;&t; * the structure and prepares the path buffers for use by&n;&t; * fill_sha1_path().&n;&t; */
r_for
c_loop
(paren
id|totlen
op_assign
id|pass
op_assign
l_int|0
suffix:semicolon
id|pass
OL
l_int|2
suffix:semicolon
id|pass
op_increment
)paren
(brace
id|last
op_assign
id|alt
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|cp
op_assign
id|strchr
c_func
(paren
id|last
comma
l_char|&squot;:&squot;
)paren
ques
c_cond
suffix:colon
id|last
op_plus
id|strlen
c_func
(paren
id|last
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last
op_ne
id|cp
)paren
(brace
multiline_comment|/* 43 = 40-byte + 2 &squot;/&squot; + terminating NUL */
r_int
id|pfxlen
op_assign
id|cp
id|last
suffix:semicolon
r_int
id|entlen
op_assign
id|pfxlen
op_plus
l_int|43
suffix:semicolon
r_if
c_cond
(paren
id|pass
op_eq
l_int|0
)paren
id|totlen
op_add_assign
id|entlen
suffix:semicolon
r_else
(brace
id|alt_odb
(braket
id|i
)braket
dot
id|base
op_assign
id|op
suffix:semicolon
id|alt_odb
(braket
id|i
)braket
dot
id|name
op_assign
id|op
op_plus
id|pfxlen
op_plus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|op
comma
id|last
comma
id|pfxlen
)paren
suffix:semicolon
id|op
(braket
id|pfxlen
)braket
op_assign
id|op
(braket
id|pfxlen
op_plus
l_int|3
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|op
(braket
id|entlen
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|op
op_add_assign
id|entlen
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|cp
op_logical_and
op_star
id|cp
op_eq
l_char|&squot;:&squot;
)paren
id|cp
op_increment
suffix:semicolon
id|last
op_assign
id|cp
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pass
)paren
r_break
suffix:semicolon
id|alt_odb
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|alt_odb
)paren
op_star
(paren
id|i
op_plus
l_int|1
)paren
op_plus
id|totlen
)paren
suffix:semicolon
id|alt_odb
(braket
id|i
)braket
dot
id|base
op_assign
id|alt_odb
(braket
id|i
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|op
op_assign
(paren
r_char
op_star
)paren
(paren
op_amp
id|alt_odb
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|find_sha1_file
r_static
r_char
op_star
id|find_sha1_file
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|stat
op_star
id|st
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|name
comma
id|st
)paren
)paren
r_return
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alt_odb
)paren
id|prepare_alt_odb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|name
op_assign
id|alt_odb
(braket
id|i
)braket
dot
id|name
)paren
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fill_sha1_path
c_func
(paren
id|name
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|alt_odb
(braket
id|i
)braket
dot
id|base
comma
id|st
)paren
)paren
r_return
id|alt_odb
(braket
id|i
)braket
dot
id|base
suffix:semicolon
)brace
r_return
l_int|NULL
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
comma
r_const
r_char
op_star
id|type
)paren
(brace
r_char
id|header
(braket
l_int|100
)braket
suffix:semicolon
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
id|header
comma
l_int|1
op_plus
id|sprintf
c_func
(paren
id|header
comma
l_string|&quot;%s %lu&quot;
comma
id|type
comma
id|size
)paren
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
r_struct
id|stat
id|st
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_char
op_star
id|filename
op_assign
id|find_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filename
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot map sha1 file %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
op_or
id|sha1_file_open_flag
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
multiline_comment|/* See if it works without O_NOATIME */
r_switch
c_cond
(paren
id|sha1_file_open_flag
)paren
(brace
r_default
suffix:colon
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
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* Fallthrough */
r_case
l_int|0
suffix:colon
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
multiline_comment|/* If it failed once, it will probably fail again. Stop using O_NOATIME */
id|sha1_file_open_flag
op_assign
l_int|0
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
r_int
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
(paren
r_int
r_char
op_star
)paren
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
id|ret
OL
id|Z_OK
)paren
r_return
l_int|NULL
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
id|xmalloc
c_func
(paren
l_int|1
op_plus
op_star
id|size
)paren
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
id|buf
(braket
op_star
id|size
)braket
op_assign
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
id|buf
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;delta&quot;
)paren
)paren
(brace
r_void
op_star
id|ref
op_assign
l_int|NULL
comma
op_star
id|delta
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|ref_size
comma
id|delta_size
op_assign
op_star
id|size
suffix:semicolon
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|delta_size
OG
l_int|20
)paren
id|ref
op_assign
id|read_sha1_file
c_func
(paren
id|delta
comma
id|type
comma
op_amp
id|ref_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref
)paren
id|buf
op_assign
id|patch_delta
c_func
(paren
id|ref
comma
id|ref_size
comma
id|delta
op_plus
l_int|20
comma
id|delta_size
op_minus
l_int|20
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|delta
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|read_object_with_reference
r_void
op_star
id|read_object_with_reference
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|required_type
comma
r_int
r_int
op_star
id|size
comma
r_int
r_char
op_star
id|actual_sha1_return
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|isize
suffix:semicolon
r_int
r_char
id|actual_sha1
(braket
l_int|20
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|actual_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|ref_length
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|ref_type
op_assign
l_int|NULL
suffix:semicolon
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|actual_sha1
comma
id|type
comma
op_amp
id|isize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|required_type
)paren
)paren
(brace
op_star
id|size
op_assign
id|isize
suffix:semicolon
r_if
c_cond
(paren
id|actual_sha1_return
)paren
id|memcpy
c_func
(paren
id|actual_sha1_return
comma
id|actual_sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/* Handle references */
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;commit&quot;
)paren
)paren
id|ref_type
op_assign
l_string|&quot;tree &quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;tag&quot;
)paren
)paren
id|ref_type
op_assign
l_string|&quot;object &quot;
suffix:semicolon
r_else
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ref_length
op_assign
id|strlen
c_func
(paren
id|ref_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
id|ref_type
comma
id|ref_length
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|buffer
op_plus
id|ref_length
comma
id|actual_sha1
)paren
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Now we have the ID of the referred-to object in&n;&t;&t; * actual_sha1.  Check again. */
)brace
)brace
DECL|function|write_sha1_file
r_int
id|write_sha1_file
c_func
(paren
r_void
op_star
id|buf
comma
r_int
r_int
id|len
comma
r_const
r_char
op_star
id|type
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
r_int
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
r_char
op_star
id|filename
suffix:semicolon
r_static
r_char
id|tmpfile
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
r_char
id|hdr
(braket
l_int|50
)braket
suffix:semicolon
r_int
id|fd
comma
id|hdrlen
comma
id|ret
suffix:semicolon
multiline_comment|/* Generate the header */
id|hdrlen
op_assign
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|hdr
comma
l_string|&quot;%s %lu&quot;
comma
id|type
comma
id|len
)paren
op_plus
l_int|1
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
id|hdr
comma
id|hdrlen
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|buf
comma
id|len
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
id|filename
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * FIXME!!! We might do collision checking here, but we&squot;d&n;&t;&t; * need to uncompress the old file and check it. Later.&n;&t;&t; */
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
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;sha1 file %s: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|tmpfile
comma
r_sizeof
(paren
id|tmpfile
)paren
comma
l_string|&quot;%s/obj_XXXXXX&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|mkstemp
c_func
(paren
id|tmpfile
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;unable to create temporary sha1 filename %s: %s&quot;
comma
id|tmpfile
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
op_plus
id|hdrlen
)paren
suffix:semicolon
id|compressed
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/* Compress it */
id|stream.next_out
op_assign
id|compressed
suffix:semicolon
id|stream.avail_out
op_assign
id|size
suffix:semicolon
multiline_comment|/* First header.. */
id|stream.next_in
op_assign
id|hdr
suffix:semicolon
id|stream.avail_in
op_assign
id|hdrlen
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
l_int|0
)paren
op_eq
id|Z_OK
)paren
multiline_comment|/* nothing */
suffix:semicolon
multiline_comment|/* Then the data itself.. */
id|stream.next_in
op_assign
id|buf
suffix:semicolon
id|stream.avail_in
op_assign
id|len
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
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|compressed
comma
id|size
)paren
op_ne
id|size
)paren
id|die
c_func
(paren
l_string|&quot;unable to write file&quot;
)paren
suffix:semicolon
id|fchmod
c_func
(paren
id|fd
comma
l_int|0444
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|free
c_func
(paren
id|compressed
)paren
suffix:semicolon
id|ret
op_assign
id|link
c_func
(paren
id|tmpfile
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|errno
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Coda hack - coda doesn&squot;t like cross-directory links,&n;&t;&t; * so we fall back to a rename, which will mean that it&n;&t;&t; * won&squot;t be able to check collisions, but that&squot;s not a&n;&t;&t; * big deal.&n;&t;&t; *&n;&t;&t; * When this succeeds, we just return 0. We have nothing&n;&t;&t; * left to unlink.&n;&t;&t; */
r_if
c_cond
(paren
id|ret
op_eq
id|EXDEV
op_logical_and
op_logical_neg
id|rename
c_func
(paren
id|tmpfile
comma
id|filename
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|unlink
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_if
c_cond
(paren
id|ret
op_ne
id|EEXIST
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;unable to write sha1 filename %s: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|ret
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* FIXME!!! Collision check here ? */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_sha1_from_fd
r_int
id|write_sha1_from_fd
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|fd
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
id|local
suffix:semicolon
id|z_stream
id|stream
suffix:semicolon
r_int
r_char
id|real_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|4096
)braket
suffix:semicolon
r_int
r_char
id|discard
(braket
l_int|4096
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|SHA_CTX
id|c
suffix:semicolon
id|local
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
id|local
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t open %s&bslash;n&quot;
comma
id|filename
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
id|inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|SHA1_Init
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
r_do
(brace
id|ssize_t
id|size
suffix:semicolon
id|size
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
l_int|0
)paren
(brace
id|close
c_func
(paren
id|local
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Connection closed?&quot;
)paren
suffix:semicolon
id|perror
c_func
(paren
l_string|&quot;Reading from connection&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|write
c_func
(paren
id|local
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|stream.avail_in
op_assign
id|size
suffix:semicolon
id|stream.next_in
op_assign
id|buf
suffix:semicolon
r_do
(brace
id|stream.next_out
op_assign
id|discard
suffix:semicolon
id|stream.avail_out
op_assign
r_sizeof
(paren
id|discard
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
id|Z_SYNC_FLUSH
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|discard
comma
r_sizeof
(paren
id|discard
)paren
id|stream.avail_out
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|stream.avail_in
op_logical_and
id|ret
op_eq
id|Z_OK
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ret
op_eq
id|Z_OK
)paren
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|close
c_func
(paren
id|local
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
r_if
c_cond
(paren
id|ret
op_ne
id|Z_STREAM_END
)paren
(brace
id|unlink
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;File %s corrupted&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sha1
comma
id|real_sha1
comma
l_int|20
)paren
)paren
(brace
id|unlink
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;File %s has bad hash&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|has_sha1_file
r_int
id|has_sha1_file
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
id|stat
id|st
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|find_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|st
)paren
suffix:semicolon
)brace
DECL|function|index_fd
r_int
id|index_fd
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
r_struct
id|stat
op_star
id|st
)paren
(brace
r_int
r_int
id|size
op_assign
id|st-&gt;st_size
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|buf
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|buf
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
(paren
r_int
)paren
(paren
r_int
)paren
id|buf
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
id|write_sha1_file
c_func
(paren
id|buf
comma
id|size
comma
l_string|&quot;blob&quot;
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|munmap
c_func
(paren
id|buf
comma
id|size
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
