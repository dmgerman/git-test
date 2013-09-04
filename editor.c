macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#ifndef DEFAULT_EDITOR
DECL|macro|DEFAULT_EDITOR
mdefine_line|#define DEFAULT_EDITOR &quot;vi&quot;
macro_line|#endif
DECL|function|git_editor
r_const
r_char
op_star
id|git_editor
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|editor
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_EDITOR&quot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|terminal
op_assign
id|getenv
c_func
(paren
l_string|&quot;TERM&quot;
)paren
suffix:semicolon
r_int
id|terminal_is_dumb
op_assign
op_logical_neg
id|terminal
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|terminal
comma
l_string|&quot;dumb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
op_logical_and
id|editor_program
)paren
id|editor
op_assign
id|editor_program
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
op_logical_and
op_logical_neg
id|terminal_is_dumb
)paren
id|editor
op_assign
id|getenv
c_func
(paren
l_string|&quot;VISUAL&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
)paren
id|editor
op_assign
id|getenv
c_func
(paren
l_string|&quot;EDITOR&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
op_logical_and
id|terminal_is_dumb
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
)paren
id|editor
op_assign
id|DEFAULT_EDITOR
suffix:semicolon
r_return
id|editor
suffix:semicolon
)brace
DECL|function|launch_editor
r_int
id|launch_editor
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|strbuf
op_star
id|buffer
comma
r_const
r_char
op_star
r_const
op_star
id|env
)paren
(brace
r_const
r_char
op_star
id|editor
op_assign
id|git_editor
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Terminal is dumb, but EDITOR unset&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|editor
comma
l_string|&quot;:&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|args
(braket
)braket
op_assign
(brace
id|editor
comma
id|real_path
c_func
(paren
id|path
)paren
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|child_process
id|p
suffix:semicolon
r_int
id|ret
comma
id|sig
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|p
comma
l_int|0
comma
r_sizeof
(paren
id|p
)paren
)paren
suffix:semicolon
id|p.argv
op_assign
id|args
suffix:semicolon
id|p.env
op_assign
id|env
suffix:semicolon
id|p.use_shell
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
id|p
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to start editor &squot;%s&squot;&quot;
comma
id|editor
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGINT
comma
id|SIG_IGN
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGQUIT
comma
id|SIG_IGN
)paren
suffix:semicolon
id|ret
op_assign
id|finish_command
c_func
(paren
op_amp
id|p
)paren
suffix:semicolon
id|sig
op_assign
id|ret
l_int|128
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|SIGINT
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|SIGQUIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGINT
op_logical_or
id|sig
op_eq
id|SIGQUIT
)paren
id|raise
c_func
(paren
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|error
c_func
(paren
l_string|&quot;There was a problem with the editor &squot;%s&squot;.&quot;
comma
id|editor
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_read_file
c_func
(paren
id|buffer
comma
id|path
comma
l_int|0
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not read file &squot;%s&squot;: %s&quot;
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
r_return
l_int|0
suffix:semicolon
)brace
eof
