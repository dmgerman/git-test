multiline_comment|/*&n; * Copyright (c) 2005, Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;sigchain.h&quot;
DECL|variable|lock_file_list
r_static
r_struct
id|lock_file
op_star
id|lock_file_list
suffix:semicolon
DECL|variable|alternate_index_output
r_static
r_const
r_char
op_star
id|alternate_index_output
suffix:semicolon
DECL|function|remove_lock_file
r_static
r_void
id|remove_lock_file
c_func
(paren
r_void
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
op_logical_and
id|lock_file_list-&gt;filename
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|lock_file_list-&gt;fd
op_ge
l_int|0
)paren
id|close
c_func
(paren
id|lock_file_list-&gt;fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_file_list-&gt;filename
)paren
suffix:semicolon
)brace
id|lock_file_list
op_assign
id|lock_file_list-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|remove_lock_file_on_signal
r_static
r_void
id|remove_lock_file_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_lock_file
c_func
(paren
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
multiline_comment|/*&n; * p = absolute or relative path name&n; *&n; * Return a pointer into p showing the beginning of the last path name&n; * element.  If p is empty or the root directory (&quot;/&quot;), just return p.&n; */
DECL|function|last_path_elm
r_static
r_char
op_star
id|last_path_elm
c_func
(paren
r_char
op_star
id|p
)paren
(brace
multiline_comment|/* r starts pointing to null at the end of the string */
r_char
op_star
id|r
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
id|p
)paren
r_return
id|p
suffix:semicolon
multiline_comment|/* just return empty string */
id|r
op_decrement
suffix:semicolon
multiline_comment|/* back up to last non-null character */
multiline_comment|/* back up past trailing slashes, if any */
r_while
c_loop
(paren
id|r
OG
id|p
op_logical_and
op_star
id|r
op_eq
l_char|&squot;/&squot;
)paren
id|r
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * then go backwards until I hit a slash, or the beginning of&n;&t; * the string&n;&t; */
r_while
c_loop
(paren
id|r
OG
id|p
op_logical_and
op_star
(paren
id|r
op_minus
l_int|1
)paren
op_ne
l_char|&squot;/&squot;
)paren
id|r
op_decrement
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/* We allow &quot;recursive&quot; symbolic links. Only within reason, though */
DECL|macro|MAXDEPTH
mdefine_line|#define MAXDEPTH 5
multiline_comment|/*&n; * p = path that may be a symlink&n; * s = full size of p&n; *&n; * If p is a symlink, attempt to overwrite p with a path to the real&n; * file or directory (which may or may not exist), following a chain of&n; * symlinks if necessary.  Otherwise, leave p unmodified.&n; *&n; * This is a best-effort routine.  If an error occurs, p will either be&n; * left unmodified or will name a different symlink in a symlink chain&n; * that started with p&squot;s initial contents.&n; *&n; * Always returns p.&n; */
DECL|function|resolve_symlink
r_static
r_char
op_star
id|resolve_symlink
c_func
(paren
r_char
op_star
id|p
comma
r_int
id|s
)paren
(brace
r_int
id|depth
op_assign
id|MAXDEPTH
suffix:semicolon
r_while
c_loop
(paren
id|depth
op_decrement
)paren
(brace
r_char
id|link
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|link_len
op_assign
id|readlink
c_func
(paren
id|p
comma
id|link
comma
r_sizeof
(paren
id|link
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link_len
OL
l_int|0
)paren
(brace
multiline_comment|/* not a symlink anymore */
r_return
id|p
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|link_len
OL
r_sizeof
(paren
id|link
)paren
)paren
multiline_comment|/* readlink() never null-terminates */
id|link
(braket
id|link_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
(brace
id|warning
c_func
(paren
l_string|&quot;%s: symlink too long&quot;
comma
id|p
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|link
)paren
)paren
(brace
multiline_comment|/* absolute path simply replaces p */
r_if
c_cond
(paren
id|link_len
OL
id|s
)paren
id|strcpy
c_func
(paren
id|p
comma
id|link
)paren
suffix:semicolon
r_else
(brace
id|warning
c_func
(paren
l_string|&quot;%s: symlink too long&quot;
comma
id|p
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * link is a relative path, so I must replace the&n;&t;&t;&t; * last element of p with it.&n;&t;&t;&t; */
r_char
op_star
id|r
op_assign
(paren
r_char
op_star
)paren
id|last_path_elm
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
id|p
op_plus
id|link_len
OL
id|s
)paren
id|strcpy
c_func
(paren
id|r
comma
id|link
)paren
suffix:semicolon
r_else
(brace
id|warning
c_func
(paren
l_string|&quot;%s: symlink too long&quot;
comma
id|p
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
)brace
)brace
r_return
id|p
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|path
)paren
op_ge
r_sizeof
(paren
id|lk-&gt;filename
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|lk-&gt;filename
comma
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * subtract 5 from size to make sure there&squot;s room for adding&n;&t; * &quot;.lock&quot; for the lock file name&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|LOCK_NODEREF
)paren
)paren
id|resolve_symlink
c_func
(paren
id|lk-&gt;filename
comma
r_sizeof
(paren
id|lk-&gt;filename
)paren
op_minus
l_int|5
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|lk-&gt;filename
comma
l_string|&quot;.lock&quot;
)paren
suffix:semicolon
id|lk-&gt;fd
op_assign
id|open
c_func
(paren
id|lk-&gt;filename
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
l_int|0
op_le
id|lk-&gt;fd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lock_file_list
)paren
(brace
id|sigchain_push_common
c_func
(paren
id|remove_lock_file_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_lock_file
)paren
suffix:semicolon
)brace
id|lk-&gt;owner
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;on_list
)paren
(brace
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
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|lk-&gt;filename
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot fix permission bits on %s&quot;
comma
id|lk-&gt;filename
)paren
suffix:semicolon
)brace
r_else
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|lk-&gt;fd
suffix:semicolon
)brace
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
id|die
c_func
(paren
l_string|&quot;unable to create &squot;%s.lock&squot;: %s&quot;
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
id|die
c_func
(paren
l_string|&quot;unable to create &squot;%s.lock&squot;: %s&quot;
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;cannot open &squot;%s&squot; for copying&quot;
comma
id|path
)paren
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
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|fd
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
id|lk-&gt;fd
op_assign
l_int|1
suffix:semicolon
r_return
id|close
c_func
(paren
id|fd
)paren
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
r_char
id|result_file
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|lk-&gt;fd
op_ge
l_int|0
op_logical_and
id|close_lock_file
c_func
(paren
id|lk
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|result_file
comma
id|lk-&gt;filename
)paren
suffix:semicolon
id|i
op_assign
id|strlen
c_func
(paren
id|result_file
)paren
l_int|5
suffix:semicolon
multiline_comment|/* .lock */
id|result_file
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lk-&gt;filename
comma
id|result_file
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hold_locked_index
r_int
id|hold_locked_index
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_int
id|die_on_error
)paren
(brace
r_return
id|hold_lock_file_for_update
c_func
(paren
id|lk
comma
id|get_index_file
c_func
(paren
)paren
comma
id|die_on_error
ques
c_cond
id|LOCK_DIE_ON_ERROR
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|set_alternate_index_output
r_void
id|set_alternate_index_output
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|alternate_index_output
op_assign
id|name
suffix:semicolon
)brace
DECL|function|commit_locked_index
r_int
id|commit_locked_index
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
id|alternate_index_output
)paren
(brace
r_if
c_cond
(paren
id|lk-&gt;fd
op_ge
l_int|0
op_logical_and
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
id|lk-&gt;filename
comma
id|alternate_index_output
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
id|commit_lock_file
c_func
(paren
id|lk
)paren
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
id|lk-&gt;filename
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|lk-&gt;fd
op_ge
l_int|0
)paren
id|close
c_func
(paren
id|lk-&gt;fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lk-&gt;filename
)paren
suffix:semicolon
)brace
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
eof
