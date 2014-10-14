multiline_comment|/*&n; * Copyright (c) 2005, Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;lockfile.h&quot;
macro_line|#include &quot;sigchain.h&quot;
DECL|variable|lock_file_list
r_static
r_struct
id|lock_file
op_star
r_volatile
id|lock_file_list
suffix:semicolon
DECL|function|remove_lock_files
r_static
r_void
id|remove_lock_files
c_func
(paren
r_int
id|skip_fclose
)paren
(brace
id|pid_t
id|me
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lock_file_list
)paren
(brace
r_if
c_cond
(paren
id|lock_file_list-&gt;owner
op_eq
id|me
)paren
(brace
multiline_comment|/* fclose() is not safe to call in a signal handler */
r_if
c_cond
(paren
id|skip_fclose
)paren
id|lock_file_list-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lock_file_list
)paren
suffix:semicolon
)brace
id|lock_file_list
op_assign
id|lock_file_list-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|remove_lock_files_on_exit
r_static
r_void
id|remove_lock_files_on_exit
c_func
(paren
r_void
)paren
(brace
id|remove_lock_files
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|remove_lock_files_on_signal
r_static
r_void
id|remove_lock_files_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_lock_files
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|signo
)paren
suffix:semicolon
id|raise
c_func
(paren
id|signo
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * path = absolute or relative path name&n; *&n; * Remove the last path name element from path (leaving the preceding&n; * &quot;/&quot;, if any).  If path is empty or the root directory (&quot;/&quot;), set&n; * path to the empty string.&n; */
DECL|function|trim_last_path_component
r_static
r_void
id|trim_last_path_component
c_func
(paren
r_struct
id|strbuf
op_star
id|path
)paren
(brace
r_int
id|i
op_assign
id|path-&gt;len
suffix:semicolon
multiline_comment|/* back up past trailing slashes, if any */
r_while
c_loop
(paren
id|i
op_logical_and
id|path-&gt;buf
(braket
id|i
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|i
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * then go backwards until a slash, or the beginning of the&n;&t; * string&n;&t; */
r_while
c_loop
(paren
id|i
op_logical_and
id|path-&gt;buf
(braket
id|i
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|i
op_decrement
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|path
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* We allow &quot;recursive&quot; symbolic links. Only within reason, though */
DECL|macro|MAXDEPTH
mdefine_line|#define MAXDEPTH 5
multiline_comment|/*&n; * path contains a path that might be a symlink.&n; *&n; * If path is a symlink, attempt to overwrite it with a path to the&n; * real file or directory (which may or may not exist), following a&n; * chain of symlinks if necessary.  Otherwise, leave path unmodified.&n; *&n; * This is a best-effort routine.  If an error occurs, path will&n; * either be left unmodified or will name a different symlink in a&n; * symlink chain that started with the original path.&n; */
DECL|function|resolve_symlink
r_static
r_void
id|resolve_symlink
c_func
(paren
r_struct
id|strbuf
op_star
id|path
)paren
(brace
r_int
id|depth
op_assign
id|MAXDEPTH
suffix:semicolon
r_static
r_struct
id|strbuf
id|link
op_assign
id|STRBUF_INIT
suffix:semicolon
r_while
c_loop
(paren
id|depth
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|strbuf_readlink
c_func
(paren
op_amp
id|link
comma
id|path-&gt;buf
comma
id|path-&gt;len
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|link.buf
)paren
)paren
multiline_comment|/* absolute path simply replaces p */
id|strbuf_reset
c_func
(paren
id|path
)paren
suffix:semicolon
r_else
multiline_comment|/*&n;&t;&t;&t; * link is a relative path, so replace the&n;&t;&t;&t; * last element of p with it.&n;&t;&t;&t; */
id|trim_last_path_component
c_func
(paren
id|path
)paren
suffix:semicolon
id|strbuf_addbuf
c_func
(paren
id|path
comma
op_amp
id|link
)paren
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* Make sure errno contains a meaningful value on error */
DECL|function|lock_file
r_static
r_int
id|lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
)paren
(brace
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock_file_list
)paren
(brace
multiline_comment|/* One-time initialization */
id|sigchain_push_common
c_func
(paren
id|remove_lock_files_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_lock_files_on_exit
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lk-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: cannot lock_file(&bslash;&quot;%s&bslash;&quot;) using active struct lock_file&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;on_list
)paren
(brace
multiline_comment|/* Initialize *lk and add it to lock_file_list: */
id|lk-&gt;fd
op_assign
l_int|1
suffix:semicolon
id|lk-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
id|lk-&gt;active
op_assign
l_int|0
suffix:semicolon
id|lk-&gt;owner
op_assign
l_int|0
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|lk-&gt;filename
comma
id|pathlen
op_plus
id|LOCK_SUFFIX_LEN
)paren
suffix:semicolon
id|lk-&gt;next
op_assign
id|lock_file_list
suffix:semicolon
id|lock_file_list
op_assign
id|lk
suffix:semicolon
id|lk-&gt;on_list
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lk-&gt;filename.len
)paren
(brace
multiline_comment|/* This shouldn&squot;t happen, but better safe than sorry. */
id|die
c_func
(paren
l_string|&quot;BUG: lock_file(&bslash;&quot;%s&bslash;&quot;) called with improperly-reset lock_file object&quot;
comma
id|path
)paren
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
op_amp
id|lk-&gt;filename
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LOCK_NO_DEREF
)paren
)paren
id|resolve_symlink
c_func
(paren
op_amp
id|lk-&gt;filename
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|lk-&gt;filename
comma
id|LOCK_SUFFIX
)paren
suffix:semicolon
id|lk-&gt;fd
op_assign
id|open
c_func
(paren
id|lk-&gt;filename.buf
comma
id|O_RDWR
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
id|lk-&gt;fd
OL
l_int|0
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|lk-&gt;filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|lk-&gt;owner
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
id|lk-&gt;active
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|lk-&gt;filename.buf
)paren
)paren
(brace
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;cannot fix permission bits on %s&quot;
comma
id|lk-&gt;filename.buf
)paren
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lk
)paren
suffix:semicolon
id|errno
op_assign
id|save_errno
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|lk-&gt;fd
suffix:semicolon
)brace
DECL|function|unable_to_lock_message
r_void
id|unable_to_lock_message
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|err
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|err
op_eq
id|EEXIST
)paren
(brace
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;Unable to create &squot;%s.lock&squot;: %s.&bslash;n&bslash;n&quot;
l_string|&quot;If no other git process is currently running, this probably means a&bslash;n&quot;
l_string|&quot;git process crashed in this repository earlier. Make sure no other git&bslash;n&quot;
l_string|&quot;process is running and remove the file manually to continue.&quot;
comma
id|absolute_path
c_func
(paren
id|path
)paren
comma
id|strerror
c_func
(paren
id|err
)paren
)paren
suffix:semicolon
)brace
r_else
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;Unable to create &squot;%s.lock&squot;: %s&quot;
comma
id|absolute_path
c_func
(paren
id|path
)paren
comma
id|strerror
c_func
(paren
id|err
)paren
)paren
suffix:semicolon
)brace
DECL|function|unable_to_lock_error
r_int
id|unable_to_lock_error
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|err
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|unable_to_lock_message
c_func
(paren
id|path
comma
id|err
comma
op_amp
id|buf
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buf.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|unable_to_lock_die
id|NORETURN
r_void
id|unable_to_lock_die
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|err
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|unable_to_lock_message
c_func
(paren
id|path
comma
id|err
comma
op_amp
id|buf
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buf.buf
)paren
suffix:semicolon
)brace
multiline_comment|/* This should return a meaningful errno on failure */
DECL|function|hold_lock_file_for_update
r_int
id|hold_lock_file_for_update
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
)paren
(brace
r_int
id|fd
op_assign
id|lock_file
c_func
(paren
id|lk
comma
id|path
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_and
(paren
id|flags
op_amp
id|LOCK_DIE_ON_ERROR
)paren
)paren
id|unable_to_lock_die
c_func
(paren
id|path
comma
id|errno
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|hold_lock_file_for_append
r_int
id|hold_lock_file_for_append
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
)paren
(brace
r_int
id|fd
comma
id|orig_fd
suffix:semicolon
id|fd
op_assign
id|lock_file
c_func
(paren
id|lk
comma
id|path
comma
id|flags
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
id|flags
op_amp
id|LOCK_DIE_ON_ERROR
)paren
id|unable_to_lock_die
c_func
(paren
id|path
comma
id|errno
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
id|orig_fd
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
id|orig_fd
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
(brace
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|LOCK_DIE_ON_ERROR
)paren
id|die
c_func
(paren
l_string|&quot;cannot open &squot;%s&squot; for copying&quot;
comma
id|path
)paren
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lk
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;cannot open &squot;%s&squot; for copying&quot;
comma
id|path
)paren
suffix:semicolon
id|errno
op_assign
id|save_errno
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|copy_fd
c_func
(paren
id|orig_fd
comma
id|fd
)paren
)paren
(brace
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|LOCK_DIE_ON_ERROR
)paren
m_exit
(paren
l_int|128
)paren
suffix:semicolon
id|close
c_func
(paren
id|orig_fd
)paren
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lk
)paren
suffix:semicolon
id|errno
op_assign
id|save_errno
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|close
c_func
(paren
id|orig_fd
)paren
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|fdopen_lock_file
id|FILE
op_star
id|fdopen_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|mode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: fdopen_lock_file() called for unlocked object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lk-&gt;fp
)paren
id|die
c_func
(paren
l_string|&quot;BUG: fdopen_lock_file() called twice for file &squot;%s&squot;&quot;
comma
id|lk-&gt;filename.buf
)paren
suffix:semicolon
id|lk-&gt;fp
op_assign
id|fdopen
c_func
(paren
id|lk-&gt;fd
comma
id|mode
)paren
suffix:semicolon
r_return
id|lk-&gt;fp
suffix:semicolon
)brace
DECL|function|get_locked_file_path
r_char
op_star
id|get_locked_file_path
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: get_locked_file_path() called for unlocked object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lk-&gt;filename.len
op_le
id|LOCK_SUFFIX_LEN
)paren
id|die
c_func
(paren
l_string|&quot;BUG: get_locked_file_path() called for malformed lock object&quot;
)paren
suffix:semicolon
r_return
id|xmemdupz
c_func
(paren
id|lk-&gt;filename.buf
comma
id|lk-&gt;filename.len
id|LOCK_SUFFIX_LEN
)paren
suffix:semicolon
)brace
DECL|function|close_lock_file
r_int
id|close_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_int
id|fd
op_assign
id|lk-&gt;fd
suffix:semicolon
id|FILE
op_star
id|fp
op_assign
id|lk-&gt;fp
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|lk-&gt;fd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fp
)paren
(brace
id|lk-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note: no short-circuiting here; we want to fclose()&n;&t;&t; * in any case!&n;&t;&t; */
id|err
op_assign
id|ferror
c_func
(paren
id|fp
)paren
op_or
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lk
)paren
suffix:semicolon
id|errno
op_assign
id|save_errno
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|reopen_lock_file
r_int
id|reopen_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_le
id|lk-&gt;fd
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;BUG: reopen a lockfile that is still open&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;active
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;BUG: reopen a lockfile that has been committed&quot;
)paren
)paren
suffix:semicolon
id|lk-&gt;fd
op_assign
id|open
c_func
(paren
id|lk-&gt;filename.buf
comma
id|O_WRONLY
)paren
suffix:semicolon
r_return
id|lk-&gt;fd
suffix:semicolon
)brace
DECL|function|commit_lock_file_to
r_int
id|commit_lock_file_to
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: attempt to commit unlocked object to &bslash;&quot;%s&bslash;&quot;&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close_lock_file
c_func
(paren
id|lk
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lk-&gt;filename.buf
comma
id|path
)paren
)paren
(brace
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lk
)paren
suffix:semicolon
id|errno
op_assign
id|save_errno
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|lk-&gt;active
op_assign
l_int|0
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|lk-&gt;filename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|commit_lock_file
r_int
id|commit_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_static
r_struct
id|strbuf
id|result_file
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: attempt to commit unlocked object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lk-&gt;filename.len
op_le
id|LOCK_SUFFIX_LEN
op_logical_or
id|strcmp
c_func
(paren
id|lk-&gt;filename.buf
op_plus
id|lk-&gt;filename.len
id|LOCK_SUFFIX_LEN
comma
id|LOCK_SUFFIX
)paren
)paren
id|die
c_func
(paren
l_string|&quot;BUG: lockfile filename corrupt&quot;
)paren
suffix:semicolon
multiline_comment|/* remove &quot;.lock&quot;: */
id|strbuf_add
c_func
(paren
op_amp
id|result_file
comma
id|lk-&gt;filename.buf
comma
id|lk-&gt;filename.len
id|LOCK_SUFFIX_LEN
)paren
suffix:semicolon
id|err
op_assign
id|commit_lock_file_to
c_func
(paren
id|lk
comma
id|result_file.buf
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|result_file
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|rollback_lock_file
r_void
id|rollback_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;active
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|close_lock_file
c_func
(paren
id|lk
)paren
)paren
(brace
id|unlink_or_warn
c_func
(paren
id|lk-&gt;filename.buf
)paren
suffix:semicolon
id|lk-&gt;active
op_assign
l_int|0
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|lk-&gt;filename
)paren
suffix:semicolon
)brace
)brace
eof
