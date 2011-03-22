macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;transport.h&quot;
multiline_comment|/*&n; * URL syntax:&n; *&t;&squot;fd::&lt;inoutfd&gt;[/&lt;anything&gt;]&squot;&t;&t;Read/write socket pair&n; *&t;&t;&t;&t;&t;&t;&lt;inoutfd&gt;.&n; *&t;&squot;fd::&lt;infd&gt;,&lt;outfd&gt;[/&lt;anything&gt;]&squot;&t;Read pipe &lt;infd&gt; and write&n; *&t;&t;&t;&t;&t;&t;pipe &lt;outfd&gt;.&n; *&t;[foo] indicates &squot;foo&squot; is optional. &lt;anything&gt; is any string.&n; *&n; * The data output to &lt;outfd&gt;/&lt;inoutfd&gt; should be passed unmolested to&n; * git-receive-pack/git-upload-pack/git-upload-archive and output of&n; * git-receive-pack/git-upload-pack/git-upload-archive should be passed&n; * unmolested to &lt;infd&gt;/&lt;inoutfd&gt;.&n; *&n; */
DECL|macro|MAXCOMMAND
mdefine_line|#define MAXCOMMAND 4096
DECL|function|command_loop
r_static
r_void
id|command_loop
c_func
(paren
r_int
id|input_fd
comma
r_int
id|output_fd
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
l_string|&quot;Input error&quot;
)paren
suffix:semicolon
r_return
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
r_if
c_cond
(paren
id|bidirectional_transfer_loop
c_func
(paren
id|input_fd
comma
id|output_fd
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Copying data between file descriptors failed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|die
c_func
(paren
l_string|&quot;Bad command: %s&quot;
comma
id|buffer
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|cmd_remote_fd
r_int
id|cmd_remote_fd
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
r_int
id|input_fd
op_assign
l_int|1
suffix:semicolon
r_int
id|output_fd
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
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
id|input_fd
op_assign
(paren
r_int
)paren
id|strtoul
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|end
op_eq
id|argv
(braket
l_int|2
)braket
)paren
op_logical_or
(paren
op_star
id|end
op_ne
l_char|&squot;,&squot;
op_logical_and
op_star
id|end
op_ne
l_char|&squot;/&squot;
op_logical_and
op_star
id|end
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Bad URL syntax&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
op_eq
l_char|&squot;/&squot;
op_logical_or
op_logical_neg
op_star
id|end
)paren
(brace
id|output_fd
op_assign
id|input_fd
suffix:semicolon
)brace
r_else
(brace
r_char
op_star
id|end2
suffix:semicolon
id|output_fd
op_assign
(paren
r_int
)paren
id|strtoul
c_func
(paren
id|end
op_plus
l_int|1
comma
op_amp
id|end2
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|end2
op_eq
id|end
op_plus
l_int|1
)paren
op_logical_or
(paren
op_star
id|end2
op_ne
l_char|&squot;/&squot;
op_logical_and
op_star
id|end2
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Bad URL syntax&quot;
)paren
suffix:semicolon
)brace
id|command_loop
c_func
(paren
id|input_fd
comma
id|output_fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
