multiline_comment|/*&n; * Various trivial helper wrappers around standard functions&n; */
macro_line|#include &quot;cache.h&quot;
DECL|function|do_nothing
r_static
r_void
id|do_nothing
c_func
(paren
r_int
id|size
)paren
(brace
)brace
DECL|variable|try_to_free_routine
r_static
r_void
(paren
op_star
id|try_to_free_routine
)paren
(paren
r_int
id|size
)paren
op_assign
id|do_nothing
suffix:semicolon
DECL|function|memory_limit_check
r_static
r_int
id|memory_limit_check
c_func
(paren
r_int
id|size
comma
r_int
id|gentle
)paren
(brace
r_static
r_int
id|limit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|limit
)paren
(brace
id|limit
op_assign
id|git_env_ulong
c_func
(paren
l_string|&quot;GIT_ALLOC_LIMIT&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|limit
)paren
id|limit
op_assign
id|SIZE_MAX
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OG
id|limit
)paren
(brace
r_if
c_cond
(paren
id|gentle
)paren
(brace
id|error
c_func
(paren
l_string|&quot;attempting to allocate %&quot;
id|PRIuMAX
l_string|&quot; over limit %&quot;
id|PRIuMAX
comma
(paren
r_uintmax
)paren
id|size
comma
(paren
r_uintmax
)paren
id|limit
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;attempting to allocate %&quot;
id|PRIuMAX
l_string|&quot; over limit %&quot;
id|PRIuMAX
comma
(paren
r_uintmax
)paren
id|size
comma
(paren
r_uintmax
)paren
id|limit
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_try_to_free_routine
id|try_to_free_t
id|set_try_to_free_routine
c_func
(paren
id|try_to_free_t
id|routine
)paren
(brace
id|try_to_free_t
id|old
op_assign
id|try_to_free_routine
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|routine
)paren
id|routine
op_assign
id|do_nothing
suffix:semicolon
id|try_to_free_routine
op_assign
id|routine
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
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
id|try_to_free_routine
c_func
(paren
id|strlen
c_func
(paren
id|str
)paren
op_plus
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
DECL|function|do_xmalloc
r_static
r_void
op_star
id|do_xmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|gentle
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|memory_limit_check
c_func
(paren
id|size
comma
id|gentle
)paren
)paren
r_return
l_int|NULL
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
(brace
id|try_to_free_routine
c_func
(paren
id|size
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|gentle
)paren
id|die
c_func
(paren
l_string|&quot;Out of memory, malloc failed (tried to allocate %lu bytes)&quot;
comma
(paren
r_int
r_int
)paren
id|size
)paren
suffix:semicolon
r_else
(brace
id|error
c_func
(paren
l_string|&quot;Out of memory, malloc failed (tried to allocate %lu bytes)&quot;
comma
(paren
r_int
r_int
)paren
id|size
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
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
r_return
id|do_xmalloc
c_func
(paren
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|do_xmallocz
r_static
r_void
op_star
id|do_xmallocz
c_func
(paren
r_int
id|size
comma
r_int
id|gentle
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|unsigned_add_overflows
c_func
(paren
id|size
comma
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|gentle
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Data too large to fit into virtual memory space.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;Data too large to fit into virtual memory space.&quot;
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|do_xmalloc
c_func
(paren
id|size
op_plus
l_int|1
comma
id|gentle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(paren
(paren
r_char
op_star
)paren
id|ret
)paren
(braket
id|size
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xmallocz
r_void
op_star
id|xmallocz
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|do_xmallocz
c_func
(paren
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xmallocz_gently
r_void
op_star
id|xmallocz_gently
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|do_xmallocz
c_func
(paren
id|size
comma
l_int|1
)paren
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
r_return
id|memcpy
c_func
(paren
id|xmallocz
c_func
(paren
id|len
)paren
comma
id|data
comma
id|len
)paren
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
suffix:semicolon
id|memory_limit_check
c_func
(paren
id|size
comma
l_int|0
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
(brace
id|try_to_free_routine
c_func
(paren
id|size
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
suffix:semicolon
id|memory_limit_check
c_func
(paren
id|size
op_star
id|nmemb
comma
l_int|0
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
(brace
id|try_to_free_routine
c_func
(paren
id|nmemb
op_star
id|size
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
multiline_comment|/*&n; * Limit size of IO chunks, because huge chunks only cause pain.  OS X&n; * 64-bit is buggy, returning EINVAL if len &gt;= INT_MAX; and even in&n; * the absence of bugs, large chunks can result in bad latencies when&n; * you decide to kill the process.&n; *&n; * We pick 8 MiB as our default, but if the platform defines SSIZE_MAX&n; * that is smaller than that, clip it to SSIZE_MAX, as a call to&n; * read(2) or write(2) larger than that is allowed to fail.  As the last&n; * resort, we allow a port to pass via CFLAGS e.g. &quot;-DMAX_IO_SIZE=value&quot;&n; * to override this, if the definition of SSIZE_MAX given by the platform&n; * is broken.&n; */
macro_line|#ifndef MAX_IO_SIZE
DECL|macro|MAX_IO_SIZE_DEFAULT
macro_line|# define MAX_IO_SIZE_DEFAULT (8*1024*1024)
macro_line|# if defined(SSIZE_MAX) &amp;&amp; (SSIZE_MAX &lt; MAX_IO_SIZE_DEFAULT)
DECL|macro|MAX_IO_SIZE
macro_line|#  define MAX_IO_SIZE SSIZE_MAX
macro_line|# else
DECL|macro|MAX_IO_SIZE
macro_line|#  define MAX_IO_SIZE MAX_IO_SIZE_DEFAULT
macro_line|# endif
macro_line|#endif
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
r_if
c_cond
(paren
id|len
OG
id|MAX_IO_SIZE
)paren
id|len
op_assign
id|MAX_IO_SIZE
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
r_if
c_cond
(paren
id|len
OG
id|MAX_IO_SIZE
)paren
id|len
op_assign
id|MAX_IO_SIZE
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
multiline_comment|/*&n; * xpread() is the same as pread(), but it automatically restarts pread()&n; * operations with a recoverable error (EAGAIN and EINTR). xpread() DOES&n; * NOT GUARANTEE that &quot;len&quot; bytes is read even if the data is available.&n; */
DECL|function|xpread
id|ssize_t
id|xpread
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
comma
id|off_t
id|offset
)paren
(brace
id|ssize_t
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|MAX_IO_SIZE
)paren
id|len
op_assign
id|MAX_IO_SIZE
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|nr
op_assign
id|pread
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
id|offset
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
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|loaded
op_eq
l_int|0
)paren
r_return
id|total
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
DECL|function|pread_in_full
id|ssize_t
id|pread_in_full
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
comma
id|off_t
id|offset
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
id|xpread
c_func
(paren
id|fd
comma
id|p
comma
id|count
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loaded
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|loaded
op_eq
l_int|0
)paren
r_return
id|total
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
id|offset
op_add_assign
id|loaded
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
id|die_errno
c_func
(paren
l_string|&quot;dup failed&quot;
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
id|die_errno
c_func
(paren
l_string|&quot;Out of memory? fdopen failed&quot;
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
r_char
id|origtemplate
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|strlcpy
c_func
(paren
id|origtemplate
comma
r_template
comma
r_sizeof
(paren
id|origtemplate
)paren
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
id|fd
OL
l_int|0
)paren
(brace
r_int
id|saved_errno
op_assign
id|errno
suffix:semicolon
r_const
r_char
op_star
id|nonrelative_template
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
r_template
)paren
op_ne
id|strlen
c_func
(paren
id|origtemplate
)paren
)paren
r_template
op_assign
id|origtemplate
suffix:semicolon
id|nonrelative_template
op_assign
id|absolute_path
c_func
(paren
r_template
)paren
suffix:semicolon
id|errno
op_assign
id|saved_errno
suffix:semicolon
id|die_errno
c_func
(paren
l_string|&quot;Unable to create temporary file &squot;%s&squot;&quot;
comma
id|nonrelative_template
)paren
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
multiline_comment|/* git_mkstemp() - create tmp file honoring TMPDIR variable */
DECL|function|git_mkstemp
r_int
id|git_mkstemp
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|len
comma
r_const
r_char
op_star
r_template
)paren
(brace
r_const
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|n
suffix:semicolon
id|tmp
op_assign
id|getenv
c_func
(paren
l_string|&quot;TMPDIR&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
id|tmp
op_assign
l_string|&quot;/tmp&quot;
suffix:semicolon
id|n
op_assign
id|snprintf
c_func
(paren
id|path
comma
id|len
comma
l_string|&quot;%s/%s&quot;
comma
id|tmp
comma
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|n
)paren
(brace
id|errno
op_assign
id|ENAMETOOLONG
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|mkstemp
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
multiline_comment|/* git_mkstemps() - create tmp file with suffix honoring TMPDIR variable. */
DECL|function|git_mkstemps
r_int
id|git_mkstemps
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|len
comma
r_const
r_char
op_star
r_template
comma
r_int
id|suffix_len
)paren
(brace
r_const
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|n
suffix:semicolon
id|tmp
op_assign
id|getenv
c_func
(paren
l_string|&quot;TMPDIR&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
id|tmp
op_assign
l_string|&quot;/tmp&quot;
suffix:semicolon
id|n
op_assign
id|snprintf
c_func
(paren
id|path
comma
id|len
comma
l_string|&quot;%s/%s&quot;
comma
id|tmp
comma
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|n
)paren
(brace
id|errno
op_assign
id|ENAMETOOLONG
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|mkstemps
c_func
(paren
id|path
comma
id|suffix_len
)paren
suffix:semicolon
)brace
multiline_comment|/* Adapted from libiberty&squot;s mkstemp.c. */
DECL|macro|TMP_MAX
macro_line|#undef TMP_MAX
DECL|macro|TMP_MAX
mdefine_line|#define TMP_MAX 16384
DECL|function|git_mkstemps_mode
r_int
id|git_mkstemps_mode
c_func
(paren
r_char
op_star
id|pattern
comma
r_int
id|suffix_len
comma
r_int
id|mode
)paren
(brace
r_static
r_const
r_char
id|letters
(braket
)braket
op_assign
l_string|&quot;abcdefghijklmnopqrstuvwxyz&quot;
l_string|&quot;ABCDEFGHIJKLMNOPQRSTUVWXYZ&quot;
l_string|&quot;0123456789&quot;
suffix:semicolon
r_static
r_const
r_int
id|num_letters
op_assign
l_int|62
suffix:semicolon
r_uint64
id|value
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_char
op_star
r_template
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|fd
comma
id|count
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|pattern
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|6
op_plus
id|suffix_len
)paren
(brace
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
op_amp
id|pattern
(braket
id|len
l_int|6
id|suffix_len
)braket
comma
l_string|&quot;XXXXXX&quot;
comma
l_int|6
)paren
)paren
(brace
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Replace pattern&squot;s XXXXXX characters with randomness.&n;&t; * Try TMP_MAX different filenames.&n;&t; */
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
id|value
op_assign
(paren
(paren
r_int
)paren
(paren
id|tv.tv_usec
op_lshift
l_int|16
)paren
)paren
op_xor
id|tv.tv_sec
op_xor
id|getpid
c_func
(paren
)paren
suffix:semicolon
r_template
op_assign
op_amp
id|pattern
(braket
id|len
l_int|6
id|suffix_len
)braket
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|TMP_MAX
suffix:semicolon
op_increment
id|count
)paren
(brace
r_uint64
id|v
op_assign
id|value
suffix:semicolon
multiline_comment|/* Fill in the random bits. */
r_template
(braket
l_int|0
)braket
op_assign
id|letters
(braket
id|v
op_mod
id|num_letters
)braket
suffix:semicolon
id|v
op_div_assign
id|num_letters
suffix:semicolon
r_template
(braket
l_int|1
)braket
op_assign
id|letters
(braket
id|v
op_mod
id|num_letters
)braket
suffix:semicolon
id|v
op_div_assign
id|num_letters
suffix:semicolon
r_template
(braket
l_int|2
)braket
op_assign
id|letters
(braket
id|v
op_mod
id|num_letters
)braket
suffix:semicolon
id|v
op_div_assign
id|num_letters
suffix:semicolon
r_template
(braket
l_int|3
)braket
op_assign
id|letters
(braket
id|v
op_mod
id|num_letters
)braket
suffix:semicolon
id|v
op_div_assign
id|num_letters
suffix:semicolon
r_template
(braket
l_int|4
)braket
op_assign
id|letters
(braket
id|v
op_mod
id|num_letters
)braket
suffix:semicolon
id|v
op_div_assign
id|num_letters
suffix:semicolon
r_template
(braket
l_int|5
)braket
op_assign
id|letters
(braket
id|v
op_mod
id|num_letters
)braket
suffix:semicolon
id|v
op_div_assign
id|num_letters
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|pattern
comma
id|O_CREAT
op_or
id|O_EXCL
op_or
id|O_RDWR
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
r_return
id|fd
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Fatal error (EPERM, ENOSPC etc).&n;&t;&t; * It doesn&squot;t make sense to loop.&n;&t;&t; */
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This is a random value.  It is only necessary that&n;&t;&t; * the next TMP_MAX values generated by adding 7777 to&n;&t;&t; * VALUE are different with (module 2^32).&n;&t;&t; */
id|value
op_add_assign
l_int|7777
suffix:semicolon
)brace
multiline_comment|/* We return the null string if we can&squot;t find a unique file name.  */
id|pattern
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|git_mkstemp_mode
r_int
id|git_mkstemp_mode
c_func
(paren
r_char
op_star
id|pattern
comma
r_int
id|mode
)paren
(brace
multiline_comment|/* mkstemp is just mkstemps with no suffix */
r_return
id|git_mkstemps_mode
c_func
(paren
id|pattern
comma
l_int|0
comma
id|mode
)paren
suffix:semicolon
)brace
macro_line|#ifdef NO_MKSTEMPS
DECL|function|gitmkstemps
r_int
id|gitmkstemps
c_func
(paren
r_char
op_star
id|pattern
comma
r_int
id|suffix_len
)paren
(brace
r_return
id|git_mkstemps_mode
c_func
(paren
id|pattern
comma
id|suffix_len
comma
l_int|0600
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|xmkstemp_mode
r_int
id|xmkstemp_mode
c_func
(paren
r_char
op_star
r_template
comma
r_int
id|mode
)paren
(brace
r_int
id|fd
suffix:semicolon
r_char
id|origtemplate
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|strlcpy
c_func
(paren
id|origtemplate
comma
r_template
comma
r_sizeof
(paren
id|origtemplate
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|git_mkstemp_mode
c_func
(paren
r_template
comma
id|mode
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
r_int
id|saved_errno
op_assign
id|errno
suffix:semicolon
r_const
r_char
op_star
id|nonrelative_template
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_template
(braket
l_int|0
)braket
)paren
r_template
op_assign
id|origtemplate
suffix:semicolon
id|nonrelative_template
op_assign
id|absolute_path
c_func
(paren
r_template
)paren
suffix:semicolon
id|errno
op_assign
id|saved_errno
suffix:semicolon
id|die_errno
c_func
(paren
l_string|&quot;Unable to create temporary file &squot;%s&squot;&quot;
comma
id|nonrelative_template
)paren
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|warn_if_unremovable
r_static
r_int
id|warn_if_unremovable
c_func
(paren
r_const
r_char
op_star
id|op
comma
r_const
r_char
op_star
id|file
comma
r_int
id|rc
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_or
id|errno
op_eq
id|ENOENT
)paren
r_return
l_int|0
suffix:semicolon
id|err
op_assign
id|errno
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;unable to %s %s: %s&quot;
comma
id|op
comma
id|file
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|errno
op_assign
id|err
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|unlink_or_msg
r_int
id|unlink_or_msg
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_struct
id|strbuf
op_star
id|err
)paren
(brace
r_int
id|rc
op_assign
id|unlink
c_func
(paren
id|file
)paren
suffix:semicolon
m_assert
(paren
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_or
id|errno
op_eq
id|ENOENT
)paren
r_return
l_int|0
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|err
comma
l_string|&quot;unable to unlink %s: %s&quot;
comma
id|file
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
DECL|function|unlink_or_warn
r_int
id|unlink_or_warn
c_func
(paren
r_const
r_char
op_star
id|file
)paren
(brace
r_return
id|warn_if_unremovable
c_func
(paren
l_string|&quot;unlink&quot;
comma
id|file
comma
id|unlink
c_func
(paren
id|file
)paren
)paren
suffix:semicolon
)brace
DECL|function|rmdir_or_warn
r_int
id|rmdir_or_warn
c_func
(paren
r_const
r_char
op_star
id|file
)paren
(brace
r_return
id|warn_if_unremovable
c_func
(paren
l_string|&quot;rmdir&quot;
comma
id|file
comma
id|rmdir
c_func
(paren
id|file
)paren
)paren
suffix:semicolon
)brace
DECL|function|remove_or_warn
r_int
id|remove_or_warn
c_func
(paren
r_int
r_int
id|mode
comma
r_const
r_char
op_star
id|file
)paren
(brace
r_return
id|S_ISGITLINK
c_func
(paren
id|mode
)paren
ques
c_cond
id|rmdir_or_warn
c_func
(paren
id|file
)paren
suffix:colon
id|unlink_or_warn
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
DECL|function|warn_on_inaccessible
r_void
id|warn_on_inaccessible
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to access &squot;%s&squot;: %s&quot;
)paren
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|access_error_is_ok
r_static
r_int
id|access_error_is_ok
c_func
(paren
r_int
id|err
comma
r_int
id|flag
)paren
(brace
r_return
id|err
op_eq
id|ENOENT
op_logical_or
id|err
op_eq
id|ENOTDIR
op_logical_or
(paren
(paren
id|flag
op_amp
id|ACCESS_EACCES_OK
)paren
op_logical_and
id|err
op_eq
id|EACCES
)paren
suffix:semicolon
)brace
DECL|function|access_or_warn
r_int
id|access_or_warn
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|mode
comma
r_int
id|flag
)paren
(brace
r_int
id|ret
op_assign
id|access
c_func
(paren
id|path
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
op_logical_neg
id|access_error_is_ok
c_func
(paren
id|errno
comma
id|flag
)paren
)paren
id|warn_on_inaccessible
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|access_or_die
r_int
id|access_or_die
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|mode
comma
r_int
id|flag
)paren
(brace
r_int
id|ret
op_assign
id|access
c_func
(paren
id|path
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
op_logical_neg
id|access_error_is_ok
c_func
(paren
id|errno
comma
id|flag
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to access &squot;%s&squot;&quot;
)paren
comma
id|path
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|xgetpwuid_self
r_struct
id|passwd
op_star
id|xgetpwuid_self
c_func
(paren
r_void
)paren
(brace
r_struct
id|passwd
op_star
id|pw
suffix:semicolon
id|errno
op_assign
l_int|0
suffix:semicolon
id|pw
op_assign
id|getpwuid
c_func
(paren
id|getuid
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pw
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to look up current user in the passwd file: %s&quot;
)paren
comma
id|errno
ques
c_cond
id|strerror
c_func
(paren
id|errno
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;no such user&quot;
)paren
)paren
suffix:semicolon
r_return
id|pw
suffix:semicolon
)brace
DECL|function|xgetcwd
r_char
op_star
id|xgetcwd
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_getcwd
c_func
(paren
op_amp
id|sb
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to get current working directory&quot;
)paren
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|sb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|write_file
r_int
id|write_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|fatal
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
id|va_list
id|params
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_TRUNC
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
id|fatal
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not open %s for writing&quot;
)paren
comma
id|path
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|va_start
c_func
(paren
id|params
comma
id|fmt
)paren
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|sb
comma
id|fmt
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
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
id|sb.buf
comma
id|sb.len
)paren
op_ne
id|sb.len
)paren
(brace
r_int
id|err
op_assign
id|errno
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|errno
op_assign
id|err
suffix:semicolon
r_if
c_cond
(paren
id|fatal
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not write to %s&quot;
)paren
comma
id|path
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close
c_func
(paren
id|fd
)paren
)paren
(brace
r_if
c_cond
(paren
id|fatal
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not close %s&quot;
)paren
comma
id|path
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
