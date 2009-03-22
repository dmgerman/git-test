multiline_comment|/*&n; * Various trivial helper wrappers around standard functions&n; */
macro_line|#include &quot;cache.h&quot;
DECL|function|xstrdup
r_char
op_star
id|xstrdup
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|ret
op_assign
id|strdup
c_func
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|release_pack_memory
c_func
(paren
id|strlen
c_func
(paren
id|str
)paren
op_plus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|strdup
c_func
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory, strdup failed&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xmalloc
r_void
op_star
id|xmalloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
op_logical_neg
id|size
)paren
id|ret
op_assign
id|malloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|release_pack_memory
c_func
(paren
id|size
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
op_logical_neg
id|size
)paren
id|ret
op_assign
id|malloc
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory, malloc failed&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef XMALLOC_POISON
id|memset
c_func
(paren
id|ret
comma
l_int|0xA5
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * xmemdupz() allocates (len + 1) bytes of memory, duplicates &quot;len&quot; bytes of&n; * &quot;data&quot; to the allocated memory, zero terminates the allocated memory,&n; * and returns a pointer to the allocated memory. If the allocation fails,&n; * the program dies.&n; */
DECL|function|xmemdupz
r_void
op_star
id|xmemdupz
c_func
(paren
r_const
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|p
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|data
comma
id|len
)paren
suffix:semicolon
id|p
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|xstrndup
r_char
op_star
id|xstrndup
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|p
op_assign
id|memchr
c_func
(paren
id|str
comma
l_char|&squot;&bslash;0&squot;
comma
id|len
)paren
suffix:semicolon
r_return
id|xmemdupz
c_func
(paren
id|str
comma
id|p
ques
c_cond
id|p
id|str
suffix:colon
id|len
)paren
suffix:semicolon
)brace
DECL|function|xrealloc
r_void
op_star
id|xrealloc
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
op_assign
id|realloc
c_func
(paren
id|ptr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
op_logical_neg
id|size
)paren
id|ret
op_assign
id|realloc
c_func
(paren
id|ptr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|release_pack_memory
c_func
(paren
id|size
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|realloc
c_func
(paren
id|ptr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
op_logical_neg
id|size
)paren
id|ret
op_assign
id|realloc
c_func
(paren
id|ptr
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory, realloc failed&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xcalloc
r_void
op_star
id|xcalloc
c_func
(paren
r_int
id|nmemb
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
op_assign
id|calloc
c_func
(paren
id|nmemb
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
(paren
op_logical_neg
id|nmemb
op_logical_or
op_logical_neg
id|size
)paren
)paren
id|ret
op_assign
id|calloc
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|release_pack_memory
c_func
(paren
id|nmemb
op_star
id|size
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|calloc
c_func
(paren
id|nmemb
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
(paren
op_logical_neg
id|nmemb
op_logical_or
op_logical_neg
id|size
)paren
)paren
id|ret
op_assign
id|calloc
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory, calloc failed&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xmmap
r_void
op_star
id|xmmap
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|length
comma
r_int
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
id|off_t
id|offset
)paren
(brace
r_void
op_star
id|ret
op_assign
id|mmap
c_func
(paren
id|start
comma
id|length
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|MAP_FAILED
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|length
)paren
r_return
l_int|NULL
suffix:semicolon
id|release_pack_memory
c_func
(paren
id|length
comma
id|fd
)paren
suffix:semicolon
id|ret
op_assign
id|mmap
c_func
(paren
id|start
comma
id|length
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|MAP_FAILED
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory? mmap failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * xread() is the same a read(), but it automatically restarts read()&n; * operations with a recoverable error (EAGAIN and EINTR). xread()&n; * DOES NOT GUARANTEE that &quot;len&quot; bytes is read even if the data is available.&n; */
DECL|function|xread
id|ssize_t
id|xread
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|ssize_t
id|nr
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|nr
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EAGAIN
op_logical_or
id|errno
op_eq
id|EINTR
)paren
)paren
r_continue
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * xwrite() is the same a write(), but it automatically restarts write()&n; * operations with a recoverable error (EAGAIN and EINTR). xwrite() DOES NOT&n; * GUARANTEE that &quot;len&quot; bytes is written even if the operation is successful.&n; */
DECL|function|xwrite
id|ssize_t
id|xwrite
c_func
(paren
r_int
id|fd
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|ssize_t
id|nr
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|nr
op_assign
id|write
c_func
(paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nr
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EAGAIN
op_logical_or
id|errno
op_eq
id|EINTR
)paren
)paren
r_continue
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
)brace
DECL|function|read_in_full
id|ssize_t
id|read_in_full
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
id|ssize_t
id|total
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|ssize_t
id|loaded
op_assign
id|xread
c_func
(paren
id|fd
comma
id|p
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loaded
op_le
l_int|0
)paren
r_return
id|total
ques
c_cond
id|total
suffix:colon
id|loaded
suffix:semicolon
id|count
op_sub_assign
id|loaded
suffix:semicolon
id|p
op_add_assign
id|loaded
suffix:semicolon
id|total
op_add_assign
id|loaded
suffix:semicolon
)brace
r_return
id|total
suffix:semicolon
)brace
DECL|function|write_in_full
id|ssize_t
id|write_in_full
c_func
(paren
r_int
id|fd
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
id|ssize_t
id|total
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|ssize_t
id|written
op_assign
id|xwrite
c_func
(paren
id|fd
comma
id|p
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|written
)paren
(brace
id|errno
op_assign
id|ENOSPC
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|count
op_sub_assign
id|written
suffix:semicolon
id|p
op_add_assign
id|written
suffix:semicolon
id|total
op_add_assign
id|written
suffix:semicolon
)brace
r_return
id|total
suffix:semicolon
)brace
DECL|function|xdup
r_int
id|xdup
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
id|ret
op_assign
id|dup
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;dup failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xfdopen
id|FILE
op_star
id|xfdopen
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|mode
)paren
(brace
id|FILE
op_star
id|stream
op_assign
id|fdopen
c_func
(paren
id|fd
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stream
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory? fdopen failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|stream
suffix:semicolon
)brace
DECL|function|xmkstemp
r_int
id|xmkstemp
c_func
(paren
r_char
op_star
r_template
)paren
(brace
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|mkstemp
c_func
(paren
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unable to create temporary file: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
multiline_comment|/*&n; * zlib wrappers to make sure we don&squot;t silently miss errors&n; * at init time.&n; */
DECL|function|git_inflate_init
r_void
id|git_inflate_init
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
r_const
r_char
op_star
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|inflateInit
c_func
(paren
id|strm
)paren
)paren
(brace
r_case
id|Z_OK
suffix:colon
r_return
suffix:semicolon
r_case
id|Z_MEM_ERROR
suffix:colon
id|err
op_assign
l_string|&quot;out of memory&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Z_VERSION_ERROR
suffix:colon
id|err
op_assign
l_string|&quot;wrong version&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
l_string|&quot;error&quot;
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;inflateInit: %s (%s)&quot;
comma
id|err
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_inflate_end
r_void
id|git_inflate_end
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
r_if
c_cond
(paren
id|inflateEnd
c_func
(paren
id|strm
)paren
op_ne
id|Z_OK
)paren
id|error
c_func
(paren
l_string|&quot;inflateEnd: %s&quot;
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;failed&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_inflate
r_int
id|git_inflate
c_func
(paren
id|z_streamp
id|strm
comma
r_int
id|flush
)paren
(brace
r_int
id|ret
op_assign
id|inflate
c_func
(paren
id|strm
comma
id|flush
)paren
suffix:semicolon
r_const
r_char
op_star
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* Out of memory is fatal. */
r_case
id|Z_MEM_ERROR
suffix:colon
id|die
c_func
(paren
l_string|&quot;inflate: out of memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Data corruption errors: we may want to recover from them (fsck) */
r_case
id|Z_NEED_DICT
suffix:colon
id|err
op_assign
l_string|&quot;needs dictionary&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Z_DATA_ERROR
suffix:colon
id|err
op_assign
l_string|&quot;data stream error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Z_STREAM_ERROR
suffix:colon
id|err
op_assign
l_string|&quot;stream consistency error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
l_string|&quot;unknown error&quot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Z_BUF_ERROR: normal, needs more space in the output buffer */
r_case
id|Z_BUF_ERROR
suffix:colon
r_case
id|Z_OK
suffix:colon
r_case
id|Z_STREAM_END
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
id|error
c_func
(paren
l_string|&quot;inflate: %s (%s)&quot;
comma
id|err
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|odb_mkstemp
r_int
id|odb_mkstemp
c_func
(paren
r_char
op_star
r_template
comma
r_int
id|limit
comma
r_const
r_char
op_star
id|pattern
)paren
(brace
r_int
id|fd
suffix:semicolon
id|snprintf
c_func
(paren
r_template
comma
id|limit
comma
l_string|&quot;%s/%s&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|pattern
)paren
suffix:semicolon
id|fd
op_assign
id|mkstemp
c_func
(paren
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|fd
)paren
r_return
id|fd
suffix:semicolon
multiline_comment|/* slow path */
multiline_comment|/* some mkstemp implementations erase template on failure */
id|snprintf
c_func
(paren
r_template
comma
id|limit
comma
l_string|&quot;%s/%s&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|pattern
)paren
suffix:semicolon
id|safe_create_leading_directories
c_func
(paren
r_template
)paren
suffix:semicolon
r_return
id|xmkstemp
c_func
(paren
r_template
)paren
suffix:semicolon
)brace
DECL|function|odb_pack_keep
r_int
id|odb_pack_keep
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|namesz
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|fd
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|namesz
comma
l_string|&quot;%s/pack/pack-%s.keep&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|name
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0600
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|fd
)paren
r_return
id|fd
suffix:semicolon
multiline_comment|/* slow path */
id|safe_create_leading_directories
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|open
c_func
(paren
id|name
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0600
)paren
suffix:semicolon
)brace
eof
