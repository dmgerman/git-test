macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;run-command.h&quot;
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
id|error
c_func
(paren
l_string|&quot;terminal is dumb, but EDITOR unset&quot;
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
l_string|&quot;vi&quot;
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
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|editor
)paren
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|failed
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
l_int|6
)braket
suffix:semicolon
r_struct
id|strbuf
id|arg0
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|strcspn
c_func
(paren
id|editor
comma
l_string|&quot;|&amp;;&lt;&gt;()$`&bslash;&bslash;&bslash;&quot;&squot; &bslash;t&bslash;n*?[#~=%&quot;
)paren
op_ne
id|len
)paren
(brace
multiline_comment|/* there are specials */
id|strbuf_addf
c_func
(paren
op_amp
id|arg0
comma
l_string|&quot;%s &bslash;&quot;$@&bslash;&quot;&quot;
comma
id|editor
)paren
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;sh&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;-c&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|arg0.buf
suffix:semicolon
)brace
id|args
(braket
id|i
op_increment
)braket
op_assign
id|editor
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|path
suffix:semicolon
id|args
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|failed
op_assign
id|run_command_v_opt_cd_env
c_func
(paren
id|args
comma
l_int|0
comma
l_int|NULL
comma
id|env
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|arg0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|failed
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
