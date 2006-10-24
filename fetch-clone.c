macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/time.h&gt;
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
l_string|&quot;%s: unable to fork off git-index-pack&quot;
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
id|execl_git_cmd
c_func
(paren
l_string|&quot;index-pack&quot;
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
r_if
c_cond
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
id|errno
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
DECL|function|setup_sideband
r_static
id|pid_t
id|setup_sideband
c_func
(paren
r_int
id|sideband
comma
r_const
r_char
op_star
id|me
comma
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
id|xd
(braket
l_int|2
)braket
)paren
(brace
id|pid_t
id|side_pid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sideband
)paren
(brace
id|fd
(braket
l_int|0
)braket
op_assign
id|xd
(braket
l_int|0
)braket
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
id|xd
(braket
l_int|1
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* xd[] is talking with upload-pack; subprocess reads from&n;&t; * xd[0], spits out band#2 to stderr, and feeds us band#1&n;&t; * through our fd[0].&n;&t; */
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fd
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
id|side_pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|side_pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: unable to fork off sideband demultiplexer&quot;
comma
id|me
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|side_pid
)paren
(brace
multiline_comment|/* subprocess */
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xd
(braket
l_int|0
)braket
op_ne
id|xd
(braket
l_int|1
)braket
)paren
id|close
c_func
(paren
id|xd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recv_sideband
c_func
(paren
id|me
comma
id|xd
(braket
l_int|0
)braket
comma
id|fd
(braket
l_int|1
)braket
comma
l_int|2
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|xd
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
id|fd
(braket
l_int|1
)braket
op_assign
id|xd
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|side_pid
suffix:semicolon
)brace
DECL|function|receive_unpack_pack
r_int
id|receive_unpack_pack
c_func
(paren
r_int
id|xd
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
comma
r_int
id|sideband
)paren
(brace
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
comma
id|side_pid
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
id|side_pid
op_assign
id|setup_sideband
c_func
(paren
id|sideband
comma
id|me
comma
id|fd
comma
id|xd
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
id|execl_git_cmd
c_func
(paren
l_string|&quot;unpack-objects&quot;
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
multiline_comment|/*&n; * We average out the download speed over this many &quot;events&quot;, where&n; * an event is a minimum of about half a second. That way, we get&n; * a reasonably stable number.&n; */
DECL|macro|NR_AVERAGE
mdefine_line|#define NR_AVERAGE (4)
multiline_comment|/*&n; * A &quot;binary msec&quot; is a power-of-two-msec, aka 1/1024th of a second.&n; * Keeping the time in that format means that &quot;bytes / msecs&quot; means&n; * the same as kB/s (modulo rounding).&n; *&n; * 1000512 is a magic number (usecs in a second, rounded up by half&n; * of 1024, to make &quot;rounding&quot; come out right ;)&n; */
DECL|macro|usec_to_binarymsec
mdefine_line|#define usec_to_binarymsec(x) ((int)(x) / (1000512 &gt;&gt; 10))
DECL|function|receive_keep_pack
r_int
id|receive_keep_pack
c_func
(paren
r_int
id|xd
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
comma
r_int
id|sideband
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
comma
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|total
suffix:semicolon
r_static
r_struct
id|timeval
id|prev_tv
suffix:semicolon
r_struct
id|average
(brace
r_int
r_int
id|bytes
suffix:semicolon
r_int
r_int
id|time
suffix:semicolon
)brace
id|download
(braket
id|NR_AVERAGE
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
r_int
r_int
id|avg_bytes
comma
id|avg_time
suffix:semicolon
r_int
id|idx
op_assign
l_int|0
suffix:semicolon
id|setup_sideband
c_func
(paren
id|sideband
comma
id|me
comma
id|fd
comma
id|xd
)paren
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
id|gettimeofday
c_func
(paren
op_amp
id|prev_tv
comma
l_int|NULL
)paren
suffix:semicolon
id|total
op_assign
l_int|0
suffix:semicolon
id|avg_bytes
op_assign
l_int|0
suffix:semicolon
id|avg_time
op_assign
l_int|0
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
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
op_logical_and
id|errno
op_ne
id|EAGAIN
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
id|sz
op_assign
l_int|0
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
id|total
op_add_assign
id|sz
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
(brace
r_static
r_int
r_int
id|last
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_int
r_int
id|diff
op_assign
id|total
id|last
suffix:semicolon
multiline_comment|/* not really &quot;msecs&quot;, but a power-of-two millisec (1/1024th of a sec) */
r_int
r_int
id|msecs
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
id|msecs
op_assign
id|tv.tv_sec
id|prev_tv.tv_sec
suffix:semicolon
id|msecs
op_lshift_assign
l_int|10
suffix:semicolon
id|msecs
op_add_assign
id|usec_to_binarymsec
c_func
(paren
id|tv.tv_usec
id|prev_tv.tv_usec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msecs
OG
l_int|500
)paren
(brace
id|prev_tv
op_assign
id|tv
suffix:semicolon
id|last
op_assign
id|total
suffix:semicolon
multiline_comment|/* Update averages ..*/
id|avg_bytes
op_add_assign
id|diff
suffix:semicolon
id|avg_time
op_add_assign
id|msecs
suffix:semicolon
id|avg_bytes
op_sub_assign
id|download
(braket
id|idx
)braket
dot
id|bytes
suffix:semicolon
id|avg_time
op_sub_assign
id|download
(braket
id|idx
)braket
dot
id|time
suffix:semicolon
id|download
(braket
id|idx
)braket
dot
id|bytes
op_assign
id|diff
suffix:semicolon
id|download
(braket
id|idx
)braket
dot
id|time
op_assign
id|msecs
suffix:semicolon
id|idx
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|NR_AVERAGE
)paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%4lu.%03luMB  (%lu kB/s)      &bslash;r&quot;
comma
id|total
op_rshift
l_int|20
comma
l_int|1000
op_star
(paren
(paren
id|total
op_rshift
l_int|10
)paren
op_amp
l_int|1023
)paren
op_rshift
l_int|10
comma
id|avg_bytes
op_div
id|avg_time
)paren
suffix:semicolon
)brace
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
