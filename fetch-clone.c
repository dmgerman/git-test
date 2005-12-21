macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|function|finish_pack
r_static
r_int
id|finish_pack
c_func
(paren
r_const
r_char
op_star
id|pack_tmp_name
comma
r_const
r_char
op_star
id|me
)paren
(brace
r_int
id|pipe_fd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_char
id|idx
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
id|final
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
id|hash
(braket
l_int|41
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pipe_fd
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: unable to set up pipe&quot;
comma
id|me
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|idx
comma
id|pack_tmp_name
)paren
suffix:semicolon
multiline_comment|/* &quot;.git/objects/pack-XXXXXX&quot; */
id|cp
op_assign
id|strrchr
c_func
(paren
id|idx
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cp
comma
l_string|&quot;/pidx&quot;
comma
l_int|5
)paren
suffix:semicolon
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-clone-pack: unable to fork off git-index-pack&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|close
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|pipe_fd
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;git-index-pack&quot;
comma
l_string|&quot;git-index-pack&quot;
comma
l_string|&quot;-o&quot;
comma
id|idx
comma
id|pack_tmp_name
comma
l_int|NULL
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;cannot exec git-index-pack &lt;%s&gt; &lt;%s&gt;&quot;
comma
id|idx
comma
id|pack_tmp_name
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|pipe_fd
(braket
l_int|0
)braket
comma
id|hash
comma
l_int|40
)paren
op_ne
l_int|40
)paren
(brace
id|error
c_func
(paren
l_string|&quot;%s: unable to read from git-index-pack&quot;
comma
id|me
)paren
suffix:semicolon
id|err
op_assign
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|pipe_fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|status
comma
id|code
suffix:semicolon
r_int
id|retval
op_assign
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EINTR
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;waitpid failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|retval
)paren
)paren
suffix:semicolon
r_goto
id|error_die
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|sig
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;git-index-pack died of signal %d&quot;
comma
id|sig
)paren
suffix:semicolon
r_goto
id|error_die
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;git-index-pack died of unnatural causes %d&quot;
comma
id|status
)paren
suffix:semicolon
r_goto
id|error_die
suffix:semicolon
)brace
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
(brace
id|error
c_func
(paren
l_string|&quot;git-index-pack died with error code %d&quot;
comma
id|code
)paren
suffix:semicolon
r_goto
id|error_die
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error_die
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hash
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|hash
comma
id|sha1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;git-index-pack reported nonsense &squot;%s&squot;&quot;
comma
id|hash
)paren
suffix:semicolon
r_goto
id|error_die
suffix:semicolon
)brace
multiline_comment|/* Now we have pack in pack_tmp_name[], and&n;&t; * idx in idx[]; rename them to their final names.&n;&t; */
id|snprintf
c_func
(paren
id|final
comma
r_sizeof
(paren
id|final
)paren
comma
l_string|&quot;%s/pack/pack-%s.pack&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|hash
)paren
suffix:semicolon
id|move_temp_to_file
c_func
(paren
id|pack_tmp_name
comma
id|final
)paren
suffix:semicolon
id|chmod
c_func
(paren
id|final
comma
l_int|0444
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|final
comma
r_sizeof
(paren
id|final
)paren
comma
l_string|&quot;%s/pack/pack-%s.idx&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|hash
)paren
suffix:semicolon
id|move_temp_to_file
c_func
(paren
id|idx
comma
id|final
)paren
suffix:semicolon
id|chmod
c_func
(paren
id|final
comma
l_int|0444
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_die
suffix:colon
id|unlink
c_func
(paren
id|idx
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|pack_tmp_name
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|receive_unpack_pack
r_int
id|receive_unpack_pack
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_const
r_char
op_star
id|me
comma
r_int
id|quiet
)paren
(brace
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: unable to fork off git-unpack-objects&quot;
comma
id|me
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|dup2
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;git-unpack-objects&quot;
comma
l_string|&quot;git-unpack-objects&quot;
comma
id|quiet
ques
c_cond
l_string|&quot;-q&quot;
suffix:colon
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects exec failed&quot;
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
id|die
c_func
(paren
l_string|&quot;waiting for git-unpack-objects: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died with error code %d&quot;
comma
id|code
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|sig
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died of signal %d&quot;
comma
id|sig
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died of unnatural causes %d&quot;
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|receive_keep_pack
r_int
id|receive_keep_pack
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_const
r_char
op_star
id|me
)paren
(brace
r_char
id|tmpfile
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|ofd
comma
id|ifd
suffix:semicolon
id|ifd
op_assign
id|fd
(braket
l_int|0
)braket
suffix:semicolon
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
l_string|&quot;%s/pack/tmp-XXXXXX&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|ofd
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
id|ofd
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to create temporary file %s&quot;
comma
id|tmpfile
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
id|buf
(braket
l_int|8192
)braket
suffix:semicolon
id|ssize_t
id|sz
comma
id|wsz
comma
id|pos
suffix:semicolon
id|sz
op_assign
id|read
c_func
(paren
id|ifd
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
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
r_if
c_cond
(paren
id|sz
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;error reading pack (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|ofd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|pos
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|sz
)paren
(brace
id|wsz
op_assign
id|write
c_func
(paren
id|ofd
comma
id|buf
op_plus
id|pos
comma
id|sz
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wsz
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;error writing pack (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|ofd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|pos
op_add_assign
id|wsz
suffix:semicolon
)brace
)brace
id|close
c_func
(paren
id|ofd
)paren
suffix:semicolon
r_return
id|finish_pack
c_func
(paren
id|tmpfile
comma
id|me
)paren
suffix:semicolon
)brace
eof
