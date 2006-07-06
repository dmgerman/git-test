macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/poll.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
DECL|variable|upload_pack_usage
r_static
r_const
r_char
id|upload_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-upload-pack [--strict] [--timeout=nn] &lt;dir&gt;&quot;
suffix:semicolon
DECL|macro|THEY_HAVE
mdefine_line|#define THEY_HAVE (1U &lt;&lt; 0)
DECL|macro|OUR_REF
mdefine_line|#define OUR_REF (1U &lt;&lt; 1)
DECL|macro|WANTED
mdefine_line|#define WANTED (1U &lt;&lt; 2)
DECL|variable|multi_ack
DECL|variable|nr_our_refs
r_static
r_int
id|multi_ack
op_assign
l_int|0
comma
id|nr_our_refs
op_assign
l_int|0
suffix:semicolon
DECL|variable|use_thin_pack
r_static
r_int
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
DECL|variable|have_obj
r_static
r_struct
id|object_array
id|have_obj
suffix:semicolon
DECL|variable|want_obj
r_static
r_struct
id|object_array
id|want_obj
suffix:semicolon
DECL|variable|timeout
r_static
r_int
r_int
id|timeout
op_assign
l_int|0
suffix:semicolon
DECL|variable|use_sideband
r_static
r_int
id|use_sideband
op_assign
l_int|0
suffix:semicolon
DECL|function|reset_timeout
r_static
r_void
id|reset_timeout
c_func
(paren
r_void
)paren
(brace
id|alarm
c_func
(paren
id|timeout
)paren
suffix:semicolon
)brace
DECL|function|strip
r_static
r_int
id|strip
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_logical_and
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|macro|PACKET_MAX
mdefine_line|#define PACKET_MAX 1000
DECL|function|send_client_data
r_static
id|ssize_t
id|send_client_data
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|data
comma
id|ssize_t
id|sz
)paren
(brace
id|ssize_t
id|ssz
suffix:semicolon
r_const
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|use_sideband
)paren
r_return
l_int|0
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|use_sideband
)paren
(brace
r_if
c_cond
(paren
id|fd
op_eq
l_int|3
)paren
multiline_comment|/* emergency quit */
id|fd
op_assign
l_int|2
suffix:semicolon
r_return
id|safe_write
c_func
(paren
id|fd
comma
id|data
comma
id|sz
)paren
suffix:semicolon
)brace
id|p
op_assign
id|data
suffix:semicolon
id|ssz
op_assign
id|sz
suffix:semicolon
r_while
c_loop
(paren
id|sz
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|hdr
(braket
l_int|5
)braket
suffix:semicolon
id|n
op_assign
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|PACKET_MAX
l_int|5
OL
id|n
)paren
id|n
op_assign
id|PACKET_MAX
l_int|5
suffix:semicolon
id|sprintf
c_func
(paren
id|hdr
comma
l_string|&quot;%04x&quot;
comma
id|n
op_plus
l_int|5
)paren
suffix:semicolon
id|hdr
(braket
l_int|4
)braket
op_assign
id|fd
suffix:semicolon
id|safe_write
c_func
(paren
l_int|1
comma
id|hdr
comma
l_int|5
)paren
suffix:semicolon
id|safe_write
c_func
(paren
l_int|1
comma
id|p
comma
id|n
)paren
suffix:semicolon
id|p
op_add_assign
id|n
suffix:semicolon
id|sz
op_sub_assign
id|n
suffix:semicolon
)brace
r_return
id|ssz
suffix:semicolon
)brace
DECL|function|create_pack_file
r_static
r_void
id|create_pack_file
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Pipes between rev-list to pack-objects, pack-objects to us&n;&t; * and pack-objects error stream for progress bar.&n;&t; */
r_int
id|lp_pipe
(braket
l_int|2
)braket
comma
id|pu_pipe
(braket
l_int|2
)braket
comma
id|pe_pipe
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid_rev_list
comma
id|pid_pack_objects
suffix:semicolon
r_int
id|create_full_pack
op_assign
(paren
id|nr_our_refs
op_eq
id|want_obj.nr
op_logical_and
op_logical_neg
id|have_obj.nr
)paren
suffix:semicolon
r_char
id|data
(braket
l_int|8193
)braket
comma
id|progress
(braket
l_int|128
)braket
suffix:semicolon
r_char
id|abort_msg
(braket
)braket
op_assign
l_string|&quot;aborting due to possible repository &quot;
l_string|&quot;corruption on the remote side.&quot;
suffix:semicolon
r_int
id|buffered
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|lp_pipe
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to create pipe&quot;
)paren
suffix:semicolon
id|pid_rev_list
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid_rev_list
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to fork git-rev-list&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid_rev_list
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|args
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|create_full_pack
)paren
(brace
id|args
op_assign
l_int|10
suffix:semicolon
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no point doing it */
)brace
r_else
id|args
op_assign
id|have_obj.nr
op_plus
id|want_obj.nr
op_plus
l_int|5
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
id|args
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|argv
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
id|p
suffix:semicolon
id|buf
op_assign
id|xmalloc
c_func
(paren
id|args
op_star
l_int|45
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|lp_pipe
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
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|lp_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|lp_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_string|&quot;rev-list&quot;
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|use_thin_pack
ques
c_cond
l_string|&quot;--objects-edge&quot;
suffix:colon
l_string|&quot;--objects&quot;
suffix:semicolon
r_if
c_cond
(paren
id|create_full_pack
)paren
op_star
id|p
op_increment
op_assign
l_string|&quot;--all&quot;
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|want_obj.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|want_obj.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|buf
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
comma
l_int|41
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|41
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_full_pack
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|have_obj.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|have_obj.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|buf
suffix:semicolon
op_star
id|buf
op_increment
op_assign
l_char|&squot;^&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
comma
l_int|41
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|41
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
l_int|NULL
suffix:semicolon
id|execv_git_cmd
c_func
(paren
id|argv
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to exec git-rev-list&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pu_pipe
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to create pipe&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pe_pipe
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to create pipe&quot;
)paren
suffix:semicolon
id|pid_pack_objects
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid_pack_objects
OL
l_int|0
)paren
(brace
multiline_comment|/* daemon sets things up to ignore TERM */
id|kill
c_func
(paren
id|pid_rev_list
comma
id|SIGKILL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to fork git-pack-objects&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pid_pack_objects
)paren
(brace
id|dup2
c_func
(paren
id|lp_pipe
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|pu_pipe
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|pe_pipe
(braket
l_int|1
)braket
comma
l_int|2
)paren
suffix:semicolon
id|close
c_func
(paren
id|lp_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|lp_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pu_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pu_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pe_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pe_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|execl_git_cmd
c_func
(paren
l_string|&quot;pack-objects&quot;
comma
l_string|&quot;--stdout&quot;
comma
l_string|&quot;--progress&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|kill
c_func
(paren
id|pid_rev_list
comma
id|SIGKILL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to exec git-pack-objects&quot;
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|lp_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|lp_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* We read from pe_pipe[0] to capture stderr output for&n;&t; * progress bar, and pu_pipe[0] to capture the pack data.&n;&t; */
id|close
c_func
(paren
id|pe_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pu_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_const
r_char
op_star
id|who
suffix:semicolon
r_struct
id|pollfd
id|pfd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_int
id|status
suffix:semicolon
id|ssize_t
id|sz
suffix:semicolon
r_int
id|pe
comma
id|pu
comma
id|pollsize
suffix:semicolon
id|pollsize
op_assign
l_int|0
suffix:semicolon
id|pe
op_assign
id|pu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pu_pipe
(braket
l_int|0
)braket
)paren
(brace
id|pfd
(braket
id|pollsize
)braket
dot
id|fd
op_assign
id|pu_pipe
(braket
l_int|0
)braket
suffix:semicolon
id|pfd
(braket
id|pollsize
)braket
dot
id|events
op_assign
id|POLLIN
suffix:semicolon
id|pu
op_assign
id|pollsize
suffix:semicolon
id|pollsize
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|pe_pipe
(braket
l_int|0
)braket
)paren
(brace
id|pfd
(braket
id|pollsize
)braket
dot
id|fd
op_assign
id|pe_pipe
(braket
l_int|0
)braket
suffix:semicolon
id|pfd
(braket
id|pollsize
)braket
dot
id|events
op_assign
id|POLLIN
suffix:semicolon
id|pe
op_assign
id|pollsize
suffix:semicolon
id|pollsize
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pollsize
)paren
(brace
r_if
c_cond
(paren
id|poll
c_func
(paren
id|pfd
comma
id|pollsize
comma
l_int|1
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
(brace
id|error
c_func
(paren
l_string|&quot;poll failed, resuming: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|sleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|pu
op_logical_and
(paren
id|pfd
(braket
id|pu
)braket
dot
id|revents
op_amp
(paren
id|POLLIN
op_or
id|POLLHUP
)paren
)paren
)paren
(brace
multiline_comment|/* Data ready; we keep the last byte&n;&t;&t;&t;&t; * to ourselves in case we detect&n;&t;&t;&t;&t; * broken rev-list, so that we can&n;&t;&t;&t;&t; * leave the stream corrupted.  This&n;&t;&t;&t;&t; * is unfortunate -- unpack-objects&n;&t;&t;&t;&t; * would happily accept a valid pack&n;&t;&t;&t;&t; * data with trailing garbage, so&n;&t;&t;&t;&t; * appending garbage after we pass all&n;&t;&t;&t;&t; * the pack data is not good enough to&n;&t;&t;&t;&t; * signal breakage to downstream.&n;&t;&t;&t;&t; */
r_char
op_star
id|cp
op_assign
id|data
suffix:semicolon
id|ssize_t
id|outsz
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|buffered
)paren
(brace
op_star
id|cp
op_increment
op_assign
id|buffered
suffix:semicolon
id|outsz
op_increment
suffix:semicolon
)brace
id|sz
op_assign
id|read
c_func
(paren
id|pu_pipe
(braket
l_int|0
)braket
comma
id|cp
comma
r_sizeof
(paren
id|data
)paren
id|outsz
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OL
id|sz
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sz
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|pu_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pu_pipe
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|fail
suffix:semicolon
id|sz
op_add_assign
id|outsz
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|sz
)paren
(brace
id|buffered
op_assign
id|data
(braket
id|sz
op_minus
l_int|1
)braket
op_amp
l_int|0xFF
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
)brace
r_else
id|buffered
op_assign
l_int|1
suffix:semicolon
id|sz
op_assign
id|send_client_data
c_func
(paren
l_int|1
comma
id|data
comma
id|sz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|pe
op_logical_and
(paren
id|pfd
(braket
id|pe
)braket
dot
id|revents
op_amp
(paren
id|POLLIN
op_or
id|POLLHUP
)paren
)paren
)paren
(brace
multiline_comment|/* Status ready; we ship that in the side-band&n;&t;&t;&t;&t; * or dump to the standard error.&n;&t;&t;&t;&t; */
id|sz
op_assign
id|read
c_func
(paren
id|pe_pipe
(braket
l_int|0
)braket
comma
id|progress
comma
r_sizeof
(paren
id|progress
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OL
id|sz
)paren
id|send_client_data
c_func
(paren
l_int|2
comma
id|progress
comma
id|sz
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sz
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|pe_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pe_pipe
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|fail
suffix:semicolon
)brace
)brace
multiline_comment|/* See if the children are still there */
r_if
c_cond
(paren
id|pid_rev_list
op_logical_or
id|pid_pack_objects
)paren
(brace
id|pid
op_assign
id|waitpid
c_func
(paren
l_int|1
comma
op_amp
id|status
comma
id|WNOHANG
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
r_continue
suffix:semicolon
id|who
op_assign
(paren
(paren
id|pid
op_eq
id|pid_rev_list
)paren
ques
c_cond
l_string|&quot;git-rev-list&quot;
suffix:colon
(paren
id|pid
op_eq
id|pid_pack_objects
)paren
ques
c_cond
l_string|&quot;git-pack-objects&quot;
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|who
)paren
(brace
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;git-upload-pack: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|error
c_func
(paren
l_string|&quot;git-upload-pack: we weren&squot;t &quot;
l_string|&quot;waiting for %d&quot;
comma
id|pid
)paren
suffix:semicolon
r_continue
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
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
OG
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;git-upload-pack: %s died with error.&quot;
comma
id|who
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pid
op_eq
id|pid_rev_list
)paren
id|pid_rev_list
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
id|pid_pack_objects
)paren
id|pid_pack_objects
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pid_rev_list
op_logical_or
id|pid_pack_objects
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/* both died happily */
r_if
c_cond
(paren
id|pollsize
)paren
r_continue
suffix:semicolon
multiline_comment|/* flush the data */
r_if
c_cond
(paren
l_int|0
op_le
id|buffered
)paren
(brace
id|data
(braket
l_int|0
)braket
op_assign
id|buffered
suffix:semicolon
id|sz
op_assign
id|send_client_data
c_func
(paren
l_int|1
comma
id|data
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;flushed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|send_client_data
c_func
(paren
l_int|1
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fail
suffix:colon
r_if
c_cond
(paren
id|pid_pack_objects
)paren
id|kill
c_func
(paren
id|pid_pack_objects
comma
id|SIGKILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid_rev_list
)paren
id|kill
c_func
(paren
id|pid_rev_list
comma
id|SIGKILL
)paren
suffix:semicolon
id|send_client_data
c_func
(paren
l_int|3
comma
id|abort_msg
comma
r_sizeof
(paren
id|abort_msg
)paren
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: %s&quot;
comma
id|abort_msg
)paren
suffix:semicolon
)brace
DECL|function|got_sha1
r_static
r_int
id|got_sha1
c_func
(paren
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
r_struct
id|object
op_star
id|o
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: expected SHA1 object, got &squot;%s&squot;&quot;
comma
id|hex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o
op_logical_and
id|o-&gt;parsed
)paren
)paren
id|o
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
)paren
id|die
c_func
(paren
l_string|&quot;oops (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|TYPE_COMMIT
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;flags
op_amp
id|THEY_HAVE
)paren
r_return
l_int|0
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|THEY_HAVE
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o
)paren
op_member_access_from_pointer
id|parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
id|parents-&gt;item-&gt;object.flags
op_or_assign
id|THEY_HAVE
suffix:semicolon
)brace
id|add_object_array
c_func
(paren
id|o
comma
l_int|NULL
comma
op_amp
id|have_obj
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_common_commits
r_static
r_int
id|get_common_commits
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|last_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|track_object_refs
op_assign
l_int|0
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
r_if
c_cond
(paren
id|have_obj.nr
op_eq
l_int|0
op_logical_or
id|multi_ack
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NAK&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|len
op_assign
id|strip
c_func
(paren
id|line
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;have &quot;
comma
l_int|5
)paren
)paren
(brace
r_if
c_cond
(paren
id|got_sha1
c_func
(paren
id|line
op_plus
l_int|5
comma
id|sha1
)paren
op_logical_and
(paren
id|multi_ack
op_logical_or
id|have_obj.nr
op_eq
l_int|1
)paren
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK %s%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|multi_ack
ques
c_cond
l_string|&quot; continue&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|multi_ack
)paren
id|memcpy
c_func
(paren
id|last_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;done&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|have_obj.nr
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|multi_ack
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|last_sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NAK&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;git-upload-pack: expected SHA1 list, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
)brace
)brace
DECL|function|receive_needs
r_static
r_void
id|receive_needs
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|object
op_star
id|o
suffix:semicolon
r_int
r_char
id|sha1_buf
(braket
l_int|20
)braket
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;want &quot;
comma
id|line
comma
l_int|5
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|5
comma
id|sha1_buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: protocol error, &quot;
l_string|&quot;expected to get sha, not &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;multi_ack&quot;
)paren
)paren
id|multi_ack
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;thin-pack&quot;
)paren
)paren
id|use_thin_pack
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;side-band&quot;
)paren
)paren
id|use_sideband
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We have sent all our refs already, and the other end&n;&t;&t; * should have chosen out of them; otherwise they are&n;&t;&t; * asking for nonsense.&n;&t;&t; *&n;&t;&t; * Hmph.  We may later want to allow &quot;want&quot; line that&n;&t;&t; * asks for something like &quot;master~10&quot; (symbolic)...&n;&t;&t; * would it make sense?  I don&squot;t know.&n;&t;&t; */
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1_buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_or
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|OUR_REF
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: not our ref %s&quot;
comma
id|line
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|WANTED
)paren
)paren
(brace
id|o-&gt;flags
op_or_assign
id|WANTED
suffix:semicolon
id|add_object_array
c_func
(paren
id|o
comma
l_int|NULL
comma
op_amp
id|want_obj
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|send_ref
r_static
r_int
id|send_ref
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_const
r_char
op_star
id|capabilities
op_assign
l_string|&quot;multi_ack thin-pack side-band&quot;
suffix:semicolon
r_struct
id|object
op_star
id|o
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: cannot find object %s:&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|capabilities
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s%c%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|refname
comma
l_int|0
comma
id|capabilities
)paren
suffix:semicolon
r_else
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|refname
)paren
suffix:semicolon
id|capabilities
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|OUR_REF
)paren
)paren
(brace
id|o-&gt;flags
op_or_assign
id|OUR_REF
suffix:semicolon
id|nr_our_refs
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|TYPE_TAG
)paren
(brace
id|o
op_assign
id|deref_tag
c_func
(paren
id|o
comma
id|refname
comma
l_int|0
)paren
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s^{}&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
comma
id|refname
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|upload_pack
r_static
r_int
id|upload_pack
c_func
(paren
r_void
)paren
(brace
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
id|head_ref
c_func
(paren
id|send_ref
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|send_ref
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|receive_needs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|want_obj.nr
)paren
r_return
l_int|0
suffix:semicolon
id|get_common_commits
c_func
(paren
)paren
suffix:semicolon
id|create_pack_file
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
op_star
id|dir
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|strict
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--strict&quot;
)paren
)paren
(brace
id|strict
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--timeout=&quot;
comma
l_int|10
)paren
)paren
(brace
id|timeout
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_ne
id|argc
op_minus
l_int|1
)paren
id|usage
c_func
(paren
id|upload_pack_usage
)paren
suffix:semicolon
id|dir
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enter_repo
c_func
(paren
id|dir
comma
id|strict
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: unable to chdir or not a git archive&quot;
comma
id|dir
)paren
suffix:semicolon
id|upload_pack
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
