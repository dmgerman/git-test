multiline_comment|/*&n; * Copyright (c) 2006 Franck Bui-Huu&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;archive.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &quot;run-command.h&quot;
DECL|variable|upload_archive_usage
r_static
r_const
r_char
id|upload_archive_usage
(braket
)braket
op_assign
l_string|&quot;git upload-archive &lt;repo&gt;&quot;
suffix:semicolon
DECL|variable|deadchild
r_static
r_const
r_char
id|deadchild
(braket
)braket
op_assign
l_string|&quot;git upload-archive: archiver died with error&quot;
suffix:semicolon
DECL|variable|lostchild
r_static
r_const
r_char
id|lostchild
(braket
)braket
op_assign
l_string|&quot;git upload-archive: archiver process was lost&quot;
suffix:semicolon
DECL|macro|MAX_ARGS
mdefine_line|#define MAX_ARGS (64)
DECL|function|prepare_argv
r_static
r_void
id|prepare_argv
c_func
(paren
r_const
r_char
op_star
op_star
id|sent_argv
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_const
r_char
op_star
id|arg_cmd
op_assign
l_string|&quot;argument &quot;
suffix:semicolon
r_char
op_star
id|p
comma
id|buf
(braket
l_int|4096
)braket
suffix:semicolon
r_int
id|sent_argc
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* put received options in sent_argv[] */
id|sent_argc
op_assign
l_int|2
suffix:semicolon
id|sent_argv
(braket
l_int|0
)braket
op_assign
l_string|&quot;archive&quot;
suffix:semicolon
id|sent_argv
(braket
l_int|1
)braket
op_assign
l_string|&quot;--remote-request&quot;
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|buf
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* This will die if not enough free space in buf */
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|p
comma
(paren
id|buf
op_plus
r_sizeof
id|buf
)paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* got a flush */
r_if
c_cond
(paren
id|sent_argc
OG
id|MAX_ARGS
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;Too many options (&gt;%d)&quot;
comma
id|MAX_ARGS
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|p
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
id|strlen
c_func
(paren
id|arg_cmd
)paren
op_logical_or
id|strncmp
c_func
(paren
id|arg_cmd
comma
id|p
comma
id|strlen
c_func
(paren
id|arg_cmd
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;argument&squot; token or flush expected&quot;
)paren
suffix:semicolon
id|len
op_sub_assign
id|strlen
c_func
(paren
id|arg_cmd
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|p
comma
id|p
op_plus
id|strlen
c_func
(paren
id|arg_cmd
)paren
comma
id|len
)paren
suffix:semicolon
id|sent_argv
(braket
id|sent_argc
op_increment
)braket
op_assign
id|p
suffix:semicolon
id|p
op_add_assign
id|len
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
id|sent_argv
(braket
id|sent_argc
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
DECL|function|error_clnt
r_static
r_void
id|error_clnt
c_func
(paren
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
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
id|va_list
id|params
suffix:semicolon
r_int
id|len
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|fmt
)paren
suffix:semicolon
id|len
op_assign
id|vsprintf
c_func
(paren
id|buf
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
id|send_sideband
c_func
(paren
l_int|1
comma
l_int|3
comma
id|buf
comma
id|len
comma
id|LARGE_PACKET_MAX
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;sent error to the client: %s&quot;
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|process_input
r_static
id|ssize_t
id|process_input
c_func
(paren
r_int
id|child_fd
comma
r_int
id|band
)paren
(brace
r_char
id|buf
(braket
l_int|16384
)braket
suffix:semicolon
id|ssize_t
id|sz
op_assign
id|read
c_func
(paren
id|child_fd
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
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EAGAIN
op_logical_and
id|errno
op_ne
id|EINTR
)paren
id|error_clnt
c_func
(paren
l_string|&quot;read error: %s&bslash;n&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|sz
suffix:semicolon
)brace
id|send_sideband
c_func
(paren
l_int|1
comma
id|band
comma
id|buf
comma
id|sz
comma
id|LARGE_PACKET_MAX
)paren
suffix:semicolon
r_return
id|sz
suffix:semicolon
)brace
DECL|function|cmd_upload_archive
r_int
id|cmd_upload_archive
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_const
r_char
op_star
id|sent_argv
(braket
id|MAX_ARGS
)braket
suffix:semicolon
r_struct
id|child_process
id|cld
op_assign
(brace
id|sent_argv
)brace
suffix:semicolon
id|cld.out
op_assign
id|cld.err
op_assign
l_int|1
suffix:semicolon
id|cld.git_cmd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage
c_func
(paren
id|upload_archive_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enter_repo
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; does not appear to be a git repository&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|prepare_argv
c_func
(paren
id|sent_argv
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|cld
)paren
)paren
(brace
r_int
id|err
op_assign
id|errno
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NACK fork failed on the remote side&bslash;n&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;upload-archive: %s&quot;
comma
id|strerror
c_func
(paren
id|err
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* parent - read from child, multiplex and send out to fd#1 */
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK&bslash;n&quot;
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|pollfd
id|pfd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pfd
(braket
l_int|0
)braket
dot
id|fd
op_assign
id|cld.out
suffix:semicolon
id|pfd
(braket
l_int|0
)braket
dot
id|events
op_assign
id|POLLIN
suffix:semicolon
id|pfd
(braket
l_int|1
)braket
dot
id|fd
op_assign
id|cld.err
suffix:semicolon
id|pfd
(braket
l_int|1
)braket
dot
id|events
op_assign
id|POLLIN
suffix:semicolon
r_if
c_cond
(paren
id|poll
c_func
(paren
id|pfd
comma
l_int|2
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
l_string|&quot;poll failed resuming: %s&quot;
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
id|pfd
(braket
l_int|1
)braket
dot
id|revents
op_amp
id|POLLIN
)paren
multiline_comment|/* Status stream ready */
r_if
c_cond
(paren
id|process_input
c_func
(paren
id|pfd
(braket
l_int|1
)braket
dot
id|fd
comma
l_int|2
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
l_int|0
)braket
dot
id|revents
op_amp
id|POLLIN
)paren
multiline_comment|/* Data stream ready */
r_if
c_cond
(paren
id|process_input
c_func
(paren
id|pfd
(braket
l_int|0
)braket
dot
id|fd
comma
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|waitpid
c_func
(paren
id|cld.pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
id|error_clnt
c_func
(paren
l_string|&quot;%s&quot;
comma
id|lostchild
)paren
suffix:semicolon
r_else
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
id|error_clnt
c_func
(paren
l_string|&quot;%s&quot;
comma
id|deadchild
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
