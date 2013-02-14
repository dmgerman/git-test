macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;gpg-interface.h&quot;
macro_line|#include &quot;sigchain.h&quot;
DECL|variable|configured_signing_key
r_static
r_char
op_star
id|configured_signing_key
suffix:semicolon
DECL|variable|gpg_program
r_static
r_const
r_char
op_star
id|gpg_program
op_assign
l_string|&quot;gpg&quot;
suffix:semicolon
DECL|function|set_signing_key
r_void
id|set_signing_key
c_func
(paren
r_const
r_char
op_star
id|key
)paren
(brace
id|free
c_func
(paren
id|configured_signing_key
)paren
suffix:semicolon
id|configured_signing_key
op_assign
id|xstrdup
c_func
(paren
id|key
)paren
suffix:semicolon
)brace
DECL|function|git_gpg_config
r_int
id|git_gpg_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;user.signingkey&quot;
)paren
)paren
(brace
id|set_signing_key
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gpg.program&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|gpg_program
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_signing_key
r_const
r_char
op_star
id|get_signing_key
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|configured_signing_key
)paren
r_return
id|configured_signing_key
suffix:semicolon
r_return
id|git_committer_info
c_func
(paren
id|IDENT_STRICT
op_or
id|IDENT_NO_DATE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a detached signature for the contents of &quot;buffer&quot; and append&n; * it after &quot;signature&quot;; &quot;buffer&quot; and &quot;signature&quot; can be the same&n; * strbuf instance, which would cause the detached signature appended&n; * at the end.&n; */
DECL|function|sign_buffer
r_int
id|sign_buffer
c_func
(paren
r_struct
id|strbuf
op_star
id|buffer
comma
r_struct
id|strbuf
op_star
id|signature
comma
r_const
r_char
op_star
id|signing_key
)paren
(brace
r_struct
id|child_process
id|gpg
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
l_int|4
)braket
suffix:semicolon
id|ssize_t
id|len
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|bottom
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|gpg
comma
l_int|0
comma
r_sizeof
(paren
id|gpg
)paren
)paren
suffix:semicolon
id|gpg.argv
op_assign
id|args
suffix:semicolon
id|gpg.in
op_assign
l_int|1
suffix:semicolon
id|gpg.out
op_assign
l_int|1
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
id|gpg_program
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
l_string|&quot;-bsau&quot;
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
id|signing_key
suffix:semicolon
id|args
(braket
l_int|3
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|gpg
)paren
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not run gpg.&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * When the username signingkey is bad, program could be terminated&n;&t; * because gpg exits without reading and then write gets SIGPIPE.&n;&t; */
id|sigchain_push
c_func
(paren
id|SIGPIPE
comma
id|SIG_IGN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|gpg.in
comma
id|buffer-&gt;buf
comma
id|buffer-&gt;len
)paren
op_ne
id|buffer-&gt;len
)paren
(brace
id|close
c_func
(paren
id|gpg.in
)paren
suffix:semicolon
id|close
c_func
(paren
id|gpg.out
)paren
suffix:semicolon
id|finish_command
c_func
(paren
op_amp
id|gpg
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;gpg did not accept the data&quot;
)paren
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|gpg.in
)paren
suffix:semicolon
id|bottom
op_assign
id|signature-&gt;len
suffix:semicolon
id|len
op_assign
id|strbuf_read
c_func
(paren
id|signature
comma
id|gpg.out
comma
l_int|1024
)paren
suffix:semicolon
id|close
c_func
(paren
id|gpg.out
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|SIGPIPE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|gpg
)paren
op_logical_or
op_logical_neg
id|len
op_logical_or
id|len
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;gpg failed to sign the data&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Strip CR from the line endings, in case we are on Windows. */
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
id|bottom
suffix:semicolon
id|i
OL
id|signature-&gt;len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|signature-&gt;buf
(braket
id|i
)braket
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|j
)paren
id|signature-&gt;buf
(braket
id|j
)braket
op_assign
id|signature-&gt;buf
(braket
id|i
)braket
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|signature
comma
id|j
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Run &quot;gpg&quot; to see if the payload matches the detached signature.&n; * gpg_output, when set, receives the diagnostic output from GPG.&n; * gpg_status, when set, receives the status output from GPG.&n; */
DECL|function|verify_signed_buffer
r_int
id|verify_signed_buffer
c_func
(paren
r_const
r_char
op_star
id|payload
comma
r_int
id|payload_size
comma
r_const
r_char
op_star
id|signature
comma
r_int
id|signature_size
comma
r_struct
id|strbuf
op_star
id|gpg_output
)paren
(brace
r_struct
id|child_process
id|gpg
suffix:semicolon
r_const
r_char
op_star
id|args_gpg
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;--status-fd=1&quot;
comma
l_string|&quot;--verify&quot;
comma
l_string|&quot;FILE&quot;
comma
l_string|&quot;-&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|fd
comma
id|ret
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|args_gpg
(braket
l_int|0
)braket
op_assign
id|gpg_program
suffix:semicolon
id|fd
op_assign
id|git_mkstemp
c_func
(paren
id|path
comma
id|PATH_MAX
comma
l_string|&quot;.git_vtag_tmpXXXXXX&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not create temporary file &squot;%s&squot;: %s&quot;
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
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
id|signature
comma
id|signature_size
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;failed writing detached signature to &squot;%s&squot;: %s&quot;
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|gpg
comma
l_int|0
comma
r_sizeof
(paren
id|gpg
)paren
)paren
suffix:semicolon
id|gpg.argv
op_assign
id|args_gpg
suffix:semicolon
id|gpg.in
op_assign
l_int|1
suffix:semicolon
id|gpg.out
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|gpg_output
)paren
id|gpg.err
op_assign
l_int|1
suffix:semicolon
id|args_gpg
(braket
l_int|3
)braket
op_assign
id|path
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|gpg
)paren
)paren
(brace
id|unlink
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;could not run gpg.&quot;
)paren
suffix:semicolon
)brace
id|write_in_full
c_func
(paren
id|gpg.in
comma
id|payload
comma
id|payload_size
)paren
suffix:semicolon
id|close
c_func
(paren
id|gpg.in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpg_output
)paren
(brace
id|strbuf_read
c_func
(paren
id|gpg_output
comma
id|gpg.err
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|gpg.err
)paren
suffix:semicolon
)brace
id|strbuf_read
c_func
(paren
op_amp
id|buf
comma
id|gpg.out
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|gpg.out
)paren
suffix:semicolon
id|ret
op_assign
id|finish_command
c_func
(paren
op_amp
id|gpg
)paren
suffix:semicolon
id|unlink_or_warn
c_func
(paren
id|path
)paren
suffix:semicolon
id|ret
op_or_assign
op_logical_neg
id|strstr
c_func
(paren
id|buf.buf
comma
l_string|&quot;&bslash;n[GNUPG:] GOODSIG &quot;
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
id|ret
suffix:semicolon
)brace
eof
