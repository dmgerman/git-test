macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;run-command.h&quot;
multiline_comment|/*&n; * URL syntax:&n; *&t;&squot;command [arg1 [arg2 [...]]]&squot;&t;Invoke command with given arguments.&n; *&t;Special characters:&n; *&t;&squot;% &squot;: Literal space in argument.&n; *&t;&squot;%%&squot;: Literal percent sign.&n; *&t;&squot;%S&squot;: Name of service (git-upload-pack/git-upload-archive/&n; *&t;&t;git-receive-pack.&n; *&t;&squot;%s&squot;: Same as &bslash;s, but with possible git- prefix stripped.&n; *&t;&squot;%G&squot;: Only allowed as first &squot;character&squot; of argument. Do not pass this&n; *&t;&t;Argument to command, instead send this as name of repository&n; *&t;&t;in in-line git://-style request (also activates sending this&n; *&t;&t;style of request).&n; *&t;&squot;%V&squot;: Only allowed as first &squot;character&squot; of argument. Used in&n; *&t;&t;conjunction with &squot;%G&squot;: Do not pass this argument to command,&n; *&t;&t;instead send this as vhost in git://-style request (note: does&n; *&t;&t;not activate sending git:// style request).&n; */
DECL|variable|git_req
r_static
r_char
op_star
id|git_req
suffix:semicolon
DECL|variable|git_req_vhost
r_static
r_char
op_star
id|git_req_vhost
suffix:semicolon
DECL|function|strip_escapes
r_static
r_char
op_star
id|strip_escapes
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_const
r_char
op_star
id|service
comma
r_const
r_char
op_star
op_star
id|next
)paren
(brace
r_int
id|rpos
op_assign
l_int|0
suffix:semicolon
r_int
id|escape
op_assign
l_int|0
suffix:semicolon
r_char
id|special
op_assign
l_int|0
suffix:semicolon
r_int
id|pslen
op_assign
l_int|0
suffix:semicolon
r_int
id|pSlen
op_assign
l_int|0
suffix:semicolon
r_int
id|psoff
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
id|ret
op_assign
id|STRBUF_INIT
suffix:semicolon
multiline_comment|/* Calculate prefix length for &bslash;s and lengths for &bslash;s and &bslash;S */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|service
comma
l_string|&quot;git-&quot;
comma
l_int|4
)paren
)paren
id|psoff
op_assign
l_int|4
suffix:semicolon
id|pSlen
op_assign
id|strlen
c_func
(paren
id|service
)paren
suffix:semicolon
id|pslen
op_assign
id|pSlen
id|psoff
suffix:semicolon
multiline_comment|/* Pass the service to command. */
id|setenv
c_func
(paren
l_string|&quot;GIT_EXT_SERVICE&quot;
comma
id|service
comma
l_int|1
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;GIT_EXT_SERVICE_NOPREFIX&quot;
comma
id|service
op_plus
id|psoff
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Scan the length of argument. */
r_while
c_loop
(paren
id|str
(braket
id|rpos
)braket
op_logical_and
(paren
id|escape
op_logical_or
id|str
(braket
id|rpos
)braket
op_ne
l_char|&squot; &squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|escape
)paren
(brace
r_switch
c_cond
(paren
id|str
(braket
id|rpos
)braket
)paren
(brace
r_case
l_char|&squot; &squot;
suffix:colon
r_case
l_char|&squot;%&squot;
suffix:colon
r_case
l_char|&squot;s&squot;
suffix:colon
r_case
l_char|&squot;S&squot;
suffix:colon
r_break
suffix:semicolon
r_case
l_char|&squot;G&squot;
suffix:colon
r_case
l_char|&squot;V&squot;
suffix:colon
id|special
op_assign
id|str
(braket
id|rpos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|rpos
op_eq
l_int|1
)paren
r_break
suffix:semicolon
multiline_comment|/* Fall-through to error. */
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;Bad remote-ext placeholder &squot;%%%c&squot;.&quot;
comma
id|str
(braket
id|rpos
)braket
)paren
suffix:semicolon
)brace
id|escape
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|escape
op_assign
(paren
id|str
(braket
id|rpos
)braket
op_eq
l_char|&squot;%&squot;
)paren
suffix:semicolon
id|rpos
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|escape
op_logical_and
op_logical_neg
id|str
(braket
id|rpos
)braket
)paren
id|die
c_func
(paren
l_string|&quot;remote-ext command has incomplete placeholder&quot;
)paren
suffix:semicolon
op_star
id|next
op_assign
id|str
op_plus
id|rpos
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|next
op_eq
l_char|&squot; &squot;
)paren
op_increment
op_star
id|next
suffix:semicolon
multiline_comment|/* Skip over space */
multiline_comment|/*&n;&t; * Do the actual placeholder substitution. The string will be short&n;&t; * enough not to overflow integers.&n;&t; */
id|rpos
op_assign
id|special
ques
c_cond
l_int|2
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Skip first 2 bytes in specials. */
id|escape
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|str
(braket
id|rpos
)braket
op_logical_and
(paren
id|escape
op_logical_or
id|str
(braket
id|rpos
)braket
op_ne
l_char|&squot; &squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|escape
)paren
(brace
r_switch
c_cond
(paren
id|str
(braket
id|rpos
)braket
)paren
(brace
r_case
l_char|&squot; &squot;
suffix:colon
r_case
l_char|&squot;%&squot;
suffix:colon
id|strbuf_addch
c_func
(paren
op_amp
id|ret
comma
id|str
(braket
id|rpos
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
op_amp
id|ret
comma
id|service
op_plus
id|psoff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;S&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
op_amp
id|ret
comma
id|service
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|escape
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|str
(braket
id|rpos
)braket
)paren
(brace
r_case
l_char|&squot;%&squot;
suffix:colon
id|escape
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|strbuf_addch
c_func
(paren
op_amp
id|ret
comma
id|str
(braket
id|rpos
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rpos
op_increment
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|special
)paren
(brace
r_case
l_char|&squot;G&squot;
suffix:colon
id|git_req
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|ret
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
r_case
l_char|&squot;V&squot;
suffix:colon
id|git_req_vhost
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|ret
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
r_default
suffix:colon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|ret
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Should be enough... */
DECL|macro|MAXARGUMENTS
mdefine_line|#define MAXARGUMENTS 256
DECL|function|parse_argv
r_static
r_const
r_char
op_star
op_star
id|parse_argv
c_func
(paren
r_const
r_char
op_star
id|arg
comma
r_const
r_char
op_star
id|service
)paren
(brace
r_int
id|arguments
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
op_star
id|ret
suffix:semicolon
r_char
op_star
id|temparray
(braket
id|MAXARGUMENTS
op_plus
l_int|1
)braket
suffix:semicolon
r_while
c_loop
(paren
op_star
id|arg
)paren
(brace
r_char
op_star
id|expanded
suffix:semicolon
r_if
c_cond
(paren
id|arguments
op_eq
id|MAXARGUMENTS
)paren
id|die
c_func
(paren
l_string|&quot;remote-ext command has too many arguments&quot;
)paren
suffix:semicolon
id|expanded
op_assign
id|strip_escapes
c_func
(paren
id|arg
comma
id|service
comma
op_amp
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expanded
)paren
id|temparray
(braket
id|arguments
op_increment
)braket
op_assign
id|expanded
suffix:semicolon
)brace
id|ret
op_assign
id|xmalloc
c_func
(paren
(paren
id|arguments
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|arguments
suffix:semicolon
id|i
op_increment
)paren
id|ret
(braket
id|i
)braket
op_assign
id|temparray
(braket
id|i
)braket
suffix:semicolon
id|ret
(braket
id|arguments
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|send_git_request
r_static
r_void
id|send_git_request
c_func
(paren
r_int
id|stdin_fd
comma
r_const
r_char
op_star
id|serv
comma
r_const
r_char
op_star
id|repo
comma
r_const
r_char
op_star
id|vhost
)paren
(brace
r_int
id|bufferspace
suffix:semicolon
r_int
id|wpos
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t; * Request needs 12 bytes extra if there is vhost (xxxx &bslash;0host=&bslash;0) and&n;&t; * 6 bytes extra (xxxx &bslash;0) if there is no vhost.&n;&t; */
r_if
c_cond
(paren
id|vhost
)paren
id|bufferspace
op_assign
id|strlen
c_func
(paren
id|serv
)paren
op_plus
id|strlen
c_func
(paren
id|repo
)paren
op_plus
id|strlen
c_func
(paren
id|vhost
)paren
op_plus
l_int|12
suffix:semicolon
r_else
id|bufferspace
op_assign
id|strlen
c_func
(paren
id|serv
)paren
op_plus
id|strlen
c_func
(paren
id|repo
)paren
op_plus
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|bufferspace
OG
l_int|0xFFFF
)paren
id|die
c_func
(paren
l_string|&quot;Request too large to send&quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|bufferspace
)paren
suffix:semicolon
multiline_comment|/* Make the packet. */
id|wpos
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%04x%s %s%c&quot;
comma
(paren
r_int
)paren
id|bufferspace
comma
id|serv
comma
id|repo
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Add vhost if any. */
r_if
c_cond
(paren
id|vhost
)paren
id|sprintf
c_func
(paren
id|buffer
op_plus
id|wpos
comma
l_string|&quot;host=%s%c&quot;
comma
id|vhost
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Send the request */
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|stdin_fd
comma
id|buffer
comma
id|bufferspace
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Failed to send request&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|run_child
r_static
r_int
id|run_child
c_func
(paren
r_const
r_char
op_star
id|arg
comma
r_const
r_char
op_star
id|service
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|child_process
id|child
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|child
comma
l_int|0
comma
r_sizeof
(paren
id|child
)paren
)paren
suffix:semicolon
id|child.in
op_assign
l_int|1
suffix:semicolon
id|child.out
op_assign
l_int|1
suffix:semicolon
id|child.err
op_assign
l_int|0
suffix:semicolon
id|child.argv
op_assign
id|parse_argv
c_func
(paren
id|arg
comma
id|service
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|child
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Can&squot;t run specified command&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_req
)paren
id|send_git_request
c_func
(paren
id|child.in
comma
id|service
comma
id|git_req
comma
id|git_req_vhost
)paren
suffix:semicolon
id|r
op_assign
id|bidirectional_transfer_loop
c_func
(paren
id|child.out
comma
id|child.in
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
id|r
op_assign
id|finish_command
c_func
(paren
op_amp
id|child
)paren
suffix:semicolon
r_else
id|finish_command
c_func
(paren
op_amp
id|child
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|macro|MAXCOMMAND
mdefine_line|#define MAXCOMMAND 4096
DECL|function|command_loop
r_static
r_int
id|command_loop
c_func
(paren
r_const
r_char
op_star
id|child
)paren
(brace
r_char
id|buffer
(braket
id|MAXCOMMAND
)braket
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fgets
c_func
(paren
id|buffer
comma
id|MAXCOMMAND
l_int|1
comma
id|stdin
)paren
)paren
(brace
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|stdin
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Comammand input error&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Strip end of line characters. */
id|i
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|buffer
(braket
id|i
l_int|1
)braket
)paren
)paren
id|buffer
(braket
op_decrement
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buffer
comma
l_string|&quot;capabilities&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;*connect&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;connect &quot;
comma
l_int|8
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_return
id|run_child
c_func
(paren
id|child
comma
id|buffer
op_plus
l_int|8
)paren
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Bad command&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|function|cmd_remote_ext
r_int
id|cmd_remote_ext
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
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
)paren
id|die
c_func
(paren
l_string|&quot;Expected two arguments&quot;
)paren
suffix:semicolon
r_return
id|command_loop
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
eof
