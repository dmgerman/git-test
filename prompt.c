macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;prompt.h&quot;
macro_line|#include &quot;compat/terminal.h&quot;
DECL|function|do_askpass
r_static
r_char
op_star
id|do_askpass
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_const
r_char
op_star
id|prompt
)paren
(brace
r_struct
id|child_process
id|pass
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
l_int|3
)braket
suffix:semicolon
r_static
r_struct
id|strbuf
id|buffer
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
id|cmd
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
id|prompt
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pass
comma
l_int|0
comma
r_sizeof
(paren
id|pass
)paren
)paren
suffix:semicolon
id|pass.argv
op_assign
id|args
suffix:semicolon
id|pass.out
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|pass
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|buffer
comma
id|pass.out
comma
l_int|20
)paren
OL
l_int|0
)paren
id|err
op_assign
l_int|1
suffix:semicolon
id|close
c_func
(paren
id|pass.out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|pass
)paren
)paren
id|err
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|error
c_func
(paren
l_string|&quot;unable to read askpass response from &squot;%s&squot;&quot;
comma
id|cmd
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
op_amp
id|buffer
comma
id|strcspn
c_func
(paren
id|buffer.buf
comma
l_string|&quot;&bslash;r&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|buffer
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|git_prompt
r_char
op_star
id|git_prompt
c_func
(paren
r_const
r_char
op_star
id|prompt
comma
r_int
id|flags
)paren
(brace
r_char
op_star
id|r
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PROMPT_ASKPASS
)paren
(brace
r_const
r_char
op_star
id|askpass
suffix:semicolon
id|askpass
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_ASKPASS&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|askpass
)paren
id|askpass
op_assign
id|askpass_program
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|askpass
)paren
id|askpass
op_assign
id|getenv
c_func
(paren
l_string|&quot;SSH_ASKPASS&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|askpass
op_logical_and
op_star
id|askpass
)paren
id|r
op_assign
id|do_askpass
c_func
(paren
id|askpass
comma
id|prompt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
id|r
op_assign
id|git_terminal_prompt
c_func
(paren
id|prompt
comma
id|flags
op_amp
id|PROMPT_ECHO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
(brace
multiline_comment|/* prompts already contain &quot;: &quot; at the end */
id|die
c_func
(paren
l_string|&quot;could not read %s%s&quot;
comma
id|prompt
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|git_getpass
r_char
op_star
id|git_getpass
c_func
(paren
r_const
r_char
op_star
id|prompt
)paren
(brace
r_return
id|git_prompt
c_func
(paren
id|prompt
comma
id|PROMPT_ASKPASS
)paren
suffix:semicolon
)brace
eof
