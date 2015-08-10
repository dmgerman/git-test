multiline_comment|/*&n; * State diagram and cleanup&n; * -------------------------&n; *&n; * If the program exits while a temporary file is active, we want to&n; * make sure that we remove it. This is done by remembering the active&n; * temporary files in a linked list, `tempfile_list`. An `atexit(3)`&n; * handler and a signal handler are registered, to clean up any active&n; * temporary files.&n; *&n; * Because the signal handler can run at any time, `tempfile_list` and&n; * the `tempfile` objects that comprise it must be kept in&n; * self-consistent states at all times.&n; *&n; * The possible states of a `tempfile` object are as follows:&n; *&n; * - Uninitialized. In this state the object&squot;s `on_list` field must be&n; *   zero but the rest of its contents need not be initialized. As&n; *   soon as the object is used in any way, it is irrevocably&n; *   registered in `tempfile_list`, and `on_list` is set.&n; *&n; * - Active, file open (after `create_tempfile()` or&n; *   `reopen_tempfile()`). In this state:&n; *&n; *   - the temporary file exists&n; *   - `active` is set&n; *   - `filename` holds the filename of the temporary file&n; *   - `fd` holds a file descriptor open for writing to it&n; *   - `fp` holds a pointer to an open `FILE` object if and only if&n; *     `fdopen_tempfile()` has been called on the object&n; *   - `owner` holds the PID of the process that created the file&n; *&n; * - Active, file closed (after successful `close_tempfile()`). Same&n; *   as the previous state, except that the temporary file is closed,&n; *   `fd` is -1, and `fp` is `NULL`.&n; *&n; * - Inactive (after `delete_tempfile()`, `rename_tempfile()`, a&n; *   failed attempt to create a temporary file, or a failed&n; *   `close_tempfile()`). In this state:&n; *&n; *   - `active` is unset&n; *   - `filename` is empty (usually, though there are transitory&n; *     states in which this condition doesn&squot;t hold). Client code should&n; *     *not* rely on the filename being empty in this state.&n; *   - `fd` is -1 and `fp` is `NULL`&n; *   - the object is left registered in the `tempfile_list`, and&n; *     `on_list` is set.&n; *&n; * A temporary file is owned by the process that created it. The&n; * `tempfile` has an `owner` field that records the owner&squot;s PID. This&n; * field is used to prevent a forked process from deleting a temporary&n; * file created by its parent.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tempfile.h&quot;
macro_line|#include &quot;sigchain.h&quot;
DECL|variable|tempfile_list
r_static
r_struct
id|tempfile
op_star
r_volatile
id|tempfile_list
suffix:semicolon
DECL|function|remove_tempfiles
r_static
r_void
id|remove_tempfiles
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
id|tempfile_list
)paren
(brace
r_if
c_cond
(paren
id|tempfile_list-&gt;owner
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
id|tempfile_list-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
id|delete_tempfile
c_func
(paren
id|tempfile_list
)paren
suffix:semicolon
)brace
id|tempfile_list
op_assign
id|tempfile_list-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|remove_tempfiles_on_exit
r_static
r_void
id|remove_tempfiles_on_exit
c_func
(paren
r_void
)paren
(brace
id|remove_tempfiles
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|remove_tempfiles_on_signal
r_static
r_void
id|remove_tempfiles_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_tempfiles
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
multiline_comment|/*&n; * Initialize *tempfile if necessary and add it to tempfile_list.&n; */
DECL|function|prepare_tempfile_object
r_static
r_void
id|prepare_tempfile_object
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tempfile_list
)paren
(brace
multiline_comment|/* One-time initialization */
id|sigchain_push_common
c_func
(paren
id|remove_tempfiles_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_tempfiles_on_exit
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: prepare_tempfile_object called for active object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tempfile-&gt;on_list
)paren
(brace
multiline_comment|/* Initialize *tempfile and add it to tempfile_list: */
id|tempfile-&gt;fd
op_assign
l_int|1
suffix:semicolon
id|tempfile-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
id|tempfile-&gt;active
op_assign
l_int|0
suffix:semicolon
id|tempfile-&gt;owner
op_assign
l_int|0
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|tempfile-&gt;filename
comma
l_int|0
)paren
suffix:semicolon
id|tempfile-&gt;next
op_assign
id|tempfile_list
suffix:semicolon
id|tempfile_list
op_assign
id|tempfile
suffix:semicolon
id|tempfile-&gt;on_list
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tempfile-&gt;filename.len
)paren
(brace
multiline_comment|/* This shouldn&squot;t happen, but better safe than sorry. */
id|die
c_func
(paren
l_string|&quot;BUG: prepare_tempfile_object called for improperly-reset object&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Make sure errno contains a meaningful value on error */
DECL|function|create_tempfile
r_int
id|create_tempfile
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
comma
r_const
r_char
op_star
id|path
)paren
(brace
id|prepare_tempfile_object
c_func
(paren
id|tempfile
)paren
suffix:semicolon
id|strbuf_add_absolute_path
c_func
(paren
op_amp
id|tempfile-&gt;filename
comma
id|path
)paren
suffix:semicolon
id|tempfile-&gt;fd
op_assign
id|open
c_func
(paren
id|tempfile-&gt;filename.buf
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
id|tempfile-&gt;fd
OL
l_int|0
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|tempfile-&gt;filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|tempfile-&gt;owner
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
id|tempfile-&gt;active
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|tempfile-&gt;filename.buf
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
id|tempfile-&gt;filename.buf
)paren
suffix:semicolon
id|delete_tempfile
c_func
(paren
id|tempfile
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
id|tempfile-&gt;fd
suffix:semicolon
)brace
DECL|function|mks_tempfile_sm
r_int
id|mks_tempfile_sm
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
comma
r_const
r_char
op_star
r_template
comma
r_int
id|suffixlen
comma
r_int
id|mode
)paren
(brace
id|prepare_tempfile_object
c_func
(paren
id|tempfile
)paren
suffix:semicolon
id|strbuf_add_absolute_path
c_func
(paren
op_amp
id|tempfile-&gt;filename
comma
r_template
)paren
suffix:semicolon
id|tempfile-&gt;fd
op_assign
id|git_mkstemps_mode
c_func
(paren
id|tempfile-&gt;filename.buf
comma
id|suffixlen
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tempfile-&gt;fd
OL
l_int|0
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|tempfile-&gt;filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|tempfile-&gt;owner
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
id|tempfile-&gt;active
op_assign
l_int|1
suffix:semicolon
r_return
id|tempfile-&gt;fd
suffix:semicolon
)brace
DECL|function|mks_tempfile_tsm
r_int
id|mks_tempfile_tsm
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
comma
r_const
r_char
op_star
r_template
comma
r_int
id|suffixlen
comma
r_int
id|mode
)paren
(brace
r_const
r_char
op_star
id|tmpdir
suffix:semicolon
id|prepare_tempfile_object
c_func
(paren
id|tempfile
)paren
suffix:semicolon
id|tmpdir
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
id|tmpdir
)paren
id|tmpdir
op_assign
l_string|&quot;/tmp&quot;
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|tempfile-&gt;filename
comma
l_string|&quot;%s/%s&quot;
comma
id|tmpdir
comma
r_template
)paren
suffix:semicolon
id|tempfile-&gt;fd
op_assign
id|git_mkstemps_mode
c_func
(paren
id|tempfile-&gt;filename.buf
comma
id|suffixlen
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tempfile-&gt;fd
OL
l_int|0
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|tempfile-&gt;filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|tempfile-&gt;owner
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
id|tempfile-&gt;active
op_assign
l_int|1
suffix:semicolon
r_return
id|tempfile-&gt;fd
suffix:semicolon
)brace
DECL|function|xmks_tempfile_m
r_int
id|xmks_tempfile_m
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
comma
r_const
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
r_struct
id|strbuf
id|full_template
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_add_absolute_path
c_func
(paren
op_amp
id|full_template
comma
r_template
)paren
suffix:semicolon
id|fd
op_assign
id|mks_tempfile_m
c_func
(paren
id|tempfile
comma
id|full_template.buf
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
id|die_errno
c_func
(paren
l_string|&quot;Unable to create temporary file &squot;%s&squot;&quot;
comma
id|full_template.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|full_template
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|fdopen_tempfile
id|FILE
op_star
id|fdopen_tempfile
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
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
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: fdopen_tempfile() called for inactive object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tempfile-&gt;fp
)paren
id|die
c_func
(paren
l_string|&quot;BUG: fdopen_tempfile() called for open object&quot;
)paren
suffix:semicolon
id|tempfile-&gt;fp
op_assign
id|fdopen
c_func
(paren
id|tempfile-&gt;fd
comma
id|mode
)paren
suffix:semicolon
r_return
id|tempfile-&gt;fp
suffix:semicolon
)brace
DECL|function|get_tempfile_path
r_const
r_char
op_star
id|get_tempfile_path
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: get_tempfile_path() called for inactive object&quot;
)paren
suffix:semicolon
r_return
id|tempfile-&gt;filename.buf
suffix:semicolon
)brace
DECL|function|get_tempfile_fd
r_int
id|get_tempfile_fd
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: get_tempfile_fd() called for inactive object&quot;
)paren
suffix:semicolon
r_return
id|tempfile-&gt;fd
suffix:semicolon
)brace
DECL|function|get_tempfile_fp
id|FILE
op_star
id|get_tempfile_fp
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: get_tempfile_fp() called for inactive object&quot;
)paren
suffix:semicolon
r_return
id|tempfile-&gt;fp
suffix:semicolon
)brace
DECL|function|close_tempfile
r_int
id|close_tempfile
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_int
id|fd
op_assign
id|tempfile-&gt;fd
suffix:semicolon
id|FILE
op_star
id|fp
op_assign
id|tempfile-&gt;fp
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
id|tempfile-&gt;fd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fp
)paren
(brace
id|tempfile-&gt;fp
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
id|delete_tempfile
c_func
(paren
id|tempfile
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
DECL|function|reopen_tempfile
r_int
id|reopen_tempfile
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_le
id|tempfile-&gt;fd
)paren
id|die
c_func
(paren
l_string|&quot;BUG: reopen_tempfile called for an open object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: reopen_tempfile called for an inactive object&quot;
)paren
suffix:semicolon
id|tempfile-&gt;fd
op_assign
id|open
c_func
(paren
id|tempfile-&gt;filename.buf
comma
id|O_WRONLY
)paren
suffix:semicolon
r_return
id|tempfile-&gt;fd
suffix:semicolon
)brace
DECL|function|rename_tempfile
r_int
id|rename_tempfile
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
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
id|tempfile-&gt;active
)paren
id|die
c_func
(paren
l_string|&quot;BUG: rename_tempfile called for inactive object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close_tempfile
c_func
(paren
id|tempfile
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
id|tempfile-&gt;filename.buf
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
id|delete_tempfile
c_func
(paren
id|tempfile
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
id|tempfile-&gt;active
op_assign
l_int|0
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|tempfile-&gt;filename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|delete_tempfile
r_void
id|delete_tempfile
c_func
(paren
r_struct
id|tempfile
op_star
id|tempfile
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tempfile-&gt;active
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|close_tempfile
c_func
(paren
id|tempfile
)paren
)paren
(brace
id|unlink_or_warn
c_func
(paren
id|tempfile-&gt;filename.buf
)paren
suffix:semicolon
id|tempfile-&gt;active
op_assign
l_int|0
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|tempfile-&gt;filename
)paren
suffix:semicolon
)brace
)brace
eof
