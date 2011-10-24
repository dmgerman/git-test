multiline_comment|/*&n; * Copyright (c) 2006 Franck Bui-Huu&n; * Copyright (c) 2006 Rene Scharfe&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;archive.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
DECL|function|create_output_file
r_static
r_void
id|create_output_file
c_func
(paren
r_const
r_char
op_star
id|output_file
)paren
(brace
r_int
id|output_fd
op_assign
id|open
c_func
(paren
id|output_file
comma
id|O_CREAT
op_or
id|O_WRONLY
op_or
id|O_TRUNC
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output_fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not create archive file &squot;%s&squot;&quot;
)paren
comma
id|output_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output_fd
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|dup2
c_func
(paren
id|output_fd
comma
l_int|1
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not redirect output&quot;
)paren
)paren
suffix:semicolon
r_else
id|close
c_func
(paren
id|output_fd
)paren
suffix:semicolon
)brace
)brace
DECL|function|run_remote_archiver
r_static
r_int
id|run_remote_archiver
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
id|remote
comma
r_const
r_char
op_star
id|exec
comma
r_const
r_char
op_star
id|name_hint
)paren
(brace
r_char
id|buf
(braket
id|LARGE_PACKET_MAX
)braket
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
comma
id|i
comma
id|len
comma
id|rv
suffix:semicolon
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_struct
id|remote
op_star
id|_remote
suffix:semicolon
id|_remote
op_assign
id|remote_get
c_func
(paren
id|remote
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_remote-&gt;url
(braket
l_int|0
)braket
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;git archive: Remote with no URL&quot;
)paren
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|_remote
comma
id|_remote-&gt;url
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|transport_connect
c_func
(paren
id|transport
comma
l_string|&quot;git-upload-archive&quot;
comma
id|exec
comma
id|fd
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Inject a fake --format field at the beginning of the&n;&t; * arguments, with the format inferred from our output&n;&t; * filename. This way explicit --format options can override&n;&t; * it.&n;&t; */
r_if
c_cond
(paren
id|name_hint
)paren
(brace
r_const
r_char
op_star
id|format
op_assign
id|archive_format_from_filename
c_func
(paren
id|name_hint
)paren
suffix:semicolon
r_if
c_cond
(paren
id|format
)paren
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;argument --format=%s&bslash;n&quot;
comma
id|format
)paren
suffix:semicolon
)brace
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
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;argument %s&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
(braket
l_int|0
)braket
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
op_logical_neg
id|len
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;git archive: expected ACK/NAK, got EOF&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;ACK&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
OG
l_int|5
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;NACK &quot;
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;git archive: NACK %s&quot;
)paren
comma
id|buf
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|4
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;ERR &quot;
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;remote error: %s&quot;
)paren
comma
id|buf
op_plus
l_int|4
)paren
suffix:semicolon
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;git archive: protocol error&quot;
)paren
)paren
suffix:semicolon
)brace
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
(braket
l_int|0
)braket
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
id|len
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;git archive: expected a flush&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Now, start reading from fd[0] and spit it out to stdout */
id|rv
op_assign
id|recv_sideband
c_func
(paren
l_string|&quot;archive&quot;
comma
id|fd
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
id|rv
op_or_assign
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|rv
suffix:semicolon
)brace
DECL|macro|PARSE_OPT_KEEP_ALL
mdefine_line|#define PARSE_OPT_KEEP_ALL ( PARSE_OPT_KEEP_DASHDASH | &t;&bslash;&n;&t;&t;&t;     PARSE_OPT_KEEP_ARGV0 | &t;&bslash;&n;&t;&t;&t;     PARSE_OPT_KEEP_UNKNOWN |&t;&bslash;&n;&t;&t;&t;     PARSE_OPT_NO_INTERNAL_HELP&t;)
DECL|function|cmd_archive
r_int
id|cmd_archive
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
id|exec
op_assign
l_string|&quot;git-upload-archive&quot;
suffix:semicolon
r_const
r_char
op_star
id|output
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|remote
op_assign
l_int|NULL
suffix:semicolon
r_int
id|is_remote
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|local_opts
(braket
)braket
op_assign
(brace
id|OPT_STRING
c_func
(paren
l_char|&squot;o&squot;
comma
l_string|&quot;output&quot;
comma
op_amp
id|output
comma
l_string|&quot;file&quot;
comma
l_string|&quot;write the archive to this file&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;remote&quot;
comma
op_amp
id|remote
comma
l_string|&quot;repo&quot;
comma
l_string|&quot;retrieve the archive from remote repository &lt;repo&gt;&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;exec&quot;
comma
op_amp
id|exec
comma
l_string|&quot;cmd&quot;
comma
l_string|&quot;path to the remote git-upload-archive command&quot;
)paren
comma
(brace
id|OPTION_BOOLEAN
comma
l_int|0
comma
l_string|&quot;remote-request&quot;
comma
op_amp
id|is_remote
comma
l_int|NULL
comma
l_string|&quot;indicate we are serving a remote request&quot;
comma
id|PARSE_OPT_NOARG
op_or
id|PARSE_OPT_HIDDEN
)brace
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|local_opts
comma
l_int|NULL
comma
id|PARSE_OPT_KEEP_ALL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output
)paren
id|create_output_file
c_func
(paren
id|output
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
)paren
r_return
id|run_remote_archiver
c_func
(paren
id|argc
comma
id|argv
comma
id|remote
comma
id|exec
comma
id|output
)paren
suffix:semicolon
id|setvbuf
c_func
(paren
id|stderr
comma
l_int|NULL
comma
id|_IOLBF
comma
id|BUFSIZ
)paren
suffix:semicolon
r_return
id|write_archive
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
l_int|1
comma
id|output
comma
id|is_remote
)paren
suffix:semicolon
)brace
eof
