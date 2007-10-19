macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;run-command.h&quot;
multiline_comment|/*&n; * convert.c - convert a file when checking it out and checking it in.&n; *&n; * This should use the pathname to decide on whether it wants to do some&n; * more interesting conversions (automatic gzip/unzip, general format&n; * conversions etc etc), but by default it just does automatic CRLF&lt;-&gt;LF&n; * translation when the &quot;auto_crlf&quot; option is set.&n; */
DECL|macro|CRLF_GUESS
mdefine_line|#define CRLF_GUESS&t;(-1)
DECL|macro|CRLF_BINARY
mdefine_line|#define CRLF_BINARY&t;0
DECL|macro|CRLF_TEXT
mdefine_line|#define CRLF_TEXT&t;1
DECL|macro|CRLF_INPUT
mdefine_line|#define CRLF_INPUT&t;2
DECL|struct|text_stat
r_struct
id|text_stat
(brace
multiline_comment|/* CR, LF and CRLF counts */
DECL|member|cr
DECL|member|lf
DECL|member|crlf
r_int
id|cr
comma
id|lf
comma
id|crlf
suffix:semicolon
multiline_comment|/* These are just approximations! */
DECL|member|printable
DECL|member|nonprintable
r_int
id|printable
comma
id|nonprintable
suffix:semicolon
)brace
suffix:semicolon
DECL|function|gather_stats
r_static
r_void
id|gather_stats
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|size
comma
r_struct
id|text_stat
op_star
id|stats
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|stats
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|stats
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
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|c
op_assign
id|buf
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|stats-&gt;cr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
l_int|1
OL
id|size
op_logical_and
id|buf
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|stats-&gt;crlf
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|stats-&gt;lf
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_int|127
)paren
multiline_comment|/* DEL */
id|stats-&gt;nonprintable
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
OL
l_int|32
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
multiline_comment|/* BS, HT, ESC and FF */
r_case
l_char|&squot;&bslash;b&squot;
suffix:colon
r_case
l_char|&squot;&bslash;t&squot;
suffix:colon
r_case
l_char|&squot;&bslash;033&squot;
suffix:colon
r_case
l_char|&squot;&bslash;014&squot;
suffix:colon
id|stats-&gt;printable
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|stats-&gt;nonprintable
op_increment
suffix:semicolon
)brace
)brace
r_else
id|stats-&gt;printable
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The same heuristics as diff.c::mmfile_is_binary()&n; */
DECL|function|is_binary
r_static
r_int
id|is_binary
c_func
(paren
r_int
r_int
id|size
comma
r_struct
id|text_stat
op_star
id|stats
)paren
(brace
r_if
c_cond
(paren
(paren
id|stats-&gt;printable
op_rshift
l_int|7
)paren
OL
id|stats-&gt;nonprintable
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Other heuristics? Average line length might be relevant,&n;&t; * as might LF vs CR vs CRLF counts..&n;&t; *&n;&t; * NOTE! It might be normal to have a low ratio of CRLF to LF&n;&t; * (somebody starts with a LF-only file and edits it with an editor&n;&t; * that adds CRLF only to lines that are added..). But do  we&n;&t; * want to support CR-only? Probably not.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|crlf_to_git
r_static
r_int
id|crlf_to_git
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|action
)paren
(brace
r_struct
id|text_stat
id|stats
suffix:semicolon
r_char
op_star
id|dst
suffix:semicolon
r_if
c_cond
(paren
(paren
id|action
op_eq
id|CRLF_BINARY
)paren
op_logical_or
op_logical_neg
id|auto_crlf
op_logical_or
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
id|gather_stats
c_func
(paren
id|src
comma
id|len
comma
op_amp
id|stats
)paren
suffix:semicolon
multiline_comment|/* No CR? Nothing to convert, regardless. */
r_if
c_cond
(paren
op_logical_neg
id|stats.cr
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|CRLF_GUESS
)paren
(brace
multiline_comment|/*&n;&t;&t; * We&squot;re currently not going to even try to convert stuff&n;&t;&t; * that has bare CR characters. Does anybody do that crazy&n;&t;&t; * stuff?&n;&t;&t; */
r_if
c_cond
(paren
id|stats.cr
op_ne
id|stats.crlf
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * And add some heuristics for binary vs text, of course...&n;&t;&t; */
r_if
c_cond
(paren
id|is_binary
c_func
(paren
id|len
comma
op_amp
id|stats
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* only grow if not in place */
r_if
c_cond
(paren
id|strbuf_avail
c_func
(paren
id|buf
)paren
op_plus
id|buf-&gt;len
OL
id|len
)paren
id|strbuf_grow
c_func
(paren
id|buf
comma
id|len
id|buf-&gt;len
)paren
suffix:semicolon
id|dst
op_assign
id|buf-&gt;buf
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|CRLF_GUESS
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we guessed, we already know we rejected a file with&n;&t;&t; * lone CR, and we can strip a CR without looking at what&n;&t;&t; * follow it.&n;&t;&t; */
r_do
(brace
r_int
r_char
id|c
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;r&squot;
)paren
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
r_do
(brace
r_int
r_char
id|c
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|c
op_eq
l_char|&squot;&bslash;r&squot;
op_logical_and
(paren
l_int|1
OL
id|len
op_logical_and
op_star
id|src
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
)paren
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|len
)paren
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|buf
comma
id|dst
id|buf-&gt;buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|crlf_to_worktree
r_static
r_int
id|crlf_to_worktree
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|action
)paren
(brace
r_char
op_star
id|to_free
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|text_stat
id|stats
suffix:semicolon
r_if
c_cond
(paren
(paren
id|action
op_eq
id|CRLF_BINARY
)paren
op_logical_or
(paren
id|action
op_eq
id|CRLF_INPUT
)paren
op_logical_or
id|auto_crlf
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|0
suffix:semicolon
id|gather_stats
c_func
(paren
id|src
comma
id|len
comma
op_amp
id|stats
)paren
suffix:semicolon
multiline_comment|/* No LF? Nothing to convert, regardless. */
r_if
c_cond
(paren
op_logical_neg
id|stats.lf
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Was it already in CRLF format? */
r_if
c_cond
(paren
id|stats.lf
op_eq
id|stats.crlf
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|CRLF_GUESS
)paren
(brace
multiline_comment|/* If we have any bare CR characters, we&squot;re not going to touch it */
r_if
c_cond
(paren
id|stats.cr
op_ne
id|stats.crlf
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_binary
c_func
(paren
id|len
comma
op_amp
id|stats
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* are we &quot;faking&quot; in place editing ? */
r_if
c_cond
(paren
id|src
op_eq
id|buf-&gt;buf
)paren
id|to_free
op_assign
id|strbuf_detach
c_func
(paren
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|buf
comma
id|len
op_plus
id|stats.lf
id|stats.crlf
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|nl
op_assign
id|memchr
c_func
(paren
id|src
comma
l_char|&squot;&bslash;n&squot;
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nl
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|nl
OG
id|src
op_logical_and
id|nl
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|nl
op_plus
l_int|1
id|src
)paren
suffix:semicolon
)brace
r_else
(brace
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|nl
id|src
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|len
op_sub_assign
id|nl
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|nl
op_plus
l_int|1
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|free
c_func
(paren
id|to_free
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|filter_buffer
r_static
r_int
id|filter_buffer
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|src
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|cmd
)paren
(brace
multiline_comment|/*&n;&t; * Spawn cmd and feed the buffer contents through its stdin.&n;&t; */
r_struct
id|child_process
id|child_process
suffix:semicolon
r_int
id|write_err
comma
id|status
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
id|cmd
comma
l_int|NULL
)brace
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|child_process
comma
l_int|0
comma
r_sizeof
(paren
id|child_process
)paren
)paren
suffix:semicolon
id|child_process.argv
op_assign
id|argv
suffix:semicolon
id|child_process.in
op_assign
l_int|1
suffix:semicolon
id|child_process.out
op_assign
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|child_process
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot fork to run external filter %s&quot;
comma
id|cmd
)paren
suffix:semicolon
id|write_err
op_assign
(paren
id|write_in_full
c_func
(paren
id|child_process.in
comma
id|src
comma
id|size
)paren
OL
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close
c_func
(paren
id|child_process.in
)paren
)paren
id|write_err
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_err
)paren
id|error
c_func
(paren
l_string|&quot;cannot feed the input to external filter %s&quot;
comma
id|cmd
)paren
suffix:semicolon
id|status
op_assign
id|finish_command
c_func
(paren
op_amp
id|child_process
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|error
c_func
(paren
l_string|&quot;external filter %s failed %d&quot;
comma
id|cmd
comma
id|status
)paren
suffix:semicolon
r_return
(paren
id|write_err
op_logical_or
id|status
)paren
suffix:semicolon
)brace
DECL|function|apply_filter
r_static
r_int
id|apply_filter
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|dst
comma
r_const
r_char
op_star
id|cmd
)paren
(brace
multiline_comment|/*&n;&t; * Create a pipeline to have the command filter the buffer&squot;s&n;&t; * contents.&n;&t; *&n;&t; * (child --&gt; cmd) --&gt; us&n;&t; */
r_int
id|pipe_feed
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|status
comma
id|ret
op_assign
l_int|1
suffix:semicolon
r_struct
id|child_process
id|child_process
suffix:semicolon
r_struct
id|strbuf
id|nbuf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmd
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|child_process
comma
l_int|0
comma
r_sizeof
(paren
id|child_process
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|pipe_feed
)paren
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot create pipe to run external filter %s&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|child_process.pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child_process.pid
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot fork to run external filter %s&quot;
comma
id|cmd
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_feed
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|pipe_feed
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|child_process.pid
)paren
(brace
id|close
c_func
(paren
id|pipe_feed
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
id|filter_buffer
c_func
(paren
id|pipe_feed
(braket
l_int|1
)braket
comma
id|src
comma
id|len
comma
id|cmd
)paren
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|pipe_feed
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|nbuf
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|nbuf
comma
id|pipe_feed
(braket
l_int|0
)braket
comma
id|len
)paren
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;read from external filter %s failed&quot;
comma
id|cmd
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|close
c_func
(paren
id|pipe_feed
(braket
l_int|0
)braket
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;read from external filter %s failed&quot;
comma
id|cmd
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|status
op_assign
id|finish_command
c_func
(paren
op_amp
id|child_process
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|error
c_func
(paren
l_string|&quot;external filter %s failed %d&quot;
comma
id|cmd
comma
id|status
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
id|strbuf_swap
c_func
(paren
id|dst
comma
op_amp
id|nbuf
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|struct|convert_driver
r_static
r_struct
id|convert_driver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|next
r_struct
id|convert_driver
op_star
id|next
suffix:semicolon
DECL|member|smudge
r_char
op_star
id|smudge
suffix:semicolon
DECL|member|clean
r_char
op_star
id|clean
suffix:semicolon
DECL|variable|user_convert
DECL|variable|user_convert_tail
)brace
op_star
id|user_convert
comma
op_star
op_star
id|user_convert_tail
suffix:semicolon
DECL|function|read_convert_config
r_static
r_int
id|read_convert_config
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
)paren
(brace
r_const
r_char
op_star
id|ep
comma
op_star
id|name
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_struct
id|convert_driver
op_star
id|drv
suffix:semicolon
multiline_comment|/*&n;&t; * External conversion drivers are configured using&n;&t; * &quot;filter.&lt;name&gt;.variable&quot;.&n;&t; */
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;filter.&quot;
)paren
op_logical_or
(paren
id|ep
op_assign
id|strrchr
c_func
(paren
id|var
comma
l_char|&squot;.&squot;
)paren
)paren
op_eq
id|var
op_plus
l_int|6
)paren
r_return
l_int|0
suffix:semicolon
id|name
op_assign
id|var
op_plus
l_int|7
suffix:semicolon
id|namelen
op_assign
id|ep
id|name
suffix:semicolon
r_for
c_loop
(paren
id|drv
op_assign
id|user_convert
suffix:semicolon
id|drv
suffix:semicolon
id|drv
op_assign
id|drv-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|drv-&gt;name
comma
id|name
comma
id|namelen
)paren
op_logical_and
op_logical_neg
id|drv-&gt;name
(braket
id|namelen
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
)paren
(brace
id|drv
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|convert_driver
)paren
)paren
suffix:semicolon
id|drv-&gt;name
op_assign
id|xmemdupz
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
op_star
id|user_convert_tail
op_assign
id|drv
suffix:semicolon
id|user_convert_tail
op_assign
op_amp
(paren
id|drv-&gt;next
)paren
suffix:semicolon
)brace
id|ep
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * filter.&lt;name&gt;.smudge and filter.&lt;name&gt;.clean specifies&n;&t; * the command line:&n;&t; *&n;&t; *&t;command-line&n;&t; *&n;&t; * The command-line will not be interpolated in any way.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;smudge&quot;
comma
id|ep
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
id|error
c_func
(paren
l_string|&quot;%s: lacks value&quot;
comma
id|var
)paren
suffix:semicolon
id|drv-&gt;smudge
op_assign
id|strdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;clean&quot;
comma
id|ep
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
id|error
c_func
(paren
l_string|&quot;%s: lacks value&quot;
comma
id|var
)paren
suffix:semicolon
id|drv-&gt;clean
op_assign
id|strdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_convert_check
r_static
r_void
id|setup_convert_check
c_func
(paren
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_static
r_struct
id|git_attr
op_star
id|attr_crlf
suffix:semicolon
r_static
r_struct
id|git_attr
op_star
id|attr_ident
suffix:semicolon
r_static
r_struct
id|git_attr
op_star
id|attr_filter
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_crlf
)paren
(brace
id|attr_crlf
op_assign
id|git_attr
c_func
(paren
l_string|&quot;crlf&quot;
comma
l_int|4
)paren
suffix:semicolon
id|attr_ident
op_assign
id|git_attr
c_func
(paren
l_string|&quot;ident&quot;
comma
l_int|5
)paren
suffix:semicolon
id|attr_filter
op_assign
id|git_attr
c_func
(paren
l_string|&quot;filter&quot;
comma
l_int|6
)paren
suffix:semicolon
id|user_convert_tail
op_assign
op_amp
id|user_convert
suffix:semicolon
id|git_config
c_func
(paren
id|read_convert_config
)paren
suffix:semicolon
)brace
id|check
(braket
l_int|0
)braket
dot
id|attr
op_assign
id|attr_crlf
suffix:semicolon
id|check
(braket
l_int|1
)braket
dot
id|attr
op_assign
id|attr_ident
suffix:semicolon
id|check
(braket
l_int|2
)braket
dot
id|attr
op_assign
id|attr_filter
suffix:semicolon
)brace
DECL|function|count_ident
r_static
r_int
id|count_ident
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_int
r_int
id|size
)paren
(brace
multiline_comment|/*&n;&t; * &quot;$Id: 0000000000000000000000000000000000000000 $&quot; &lt;=&gt; &quot;$Id$&quot;&n;&t; */
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_char
id|ch
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
id|ch
op_assign
op_star
id|cp
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ne
l_char|&squot;$&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|3
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
l_string|&quot;Id&quot;
comma
id|cp
comma
l_int|2
)paren
)paren
r_continue
suffix:semicolon
id|ch
op_assign
id|cp
(braket
l_int|2
)braket
suffix:semicolon
id|cp
op_add_assign
l_int|3
suffix:semicolon
id|size
op_sub_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;$&squot;
)paren
id|cnt
op_increment
suffix:semicolon
multiline_comment|/* $Id$ */
r_if
c_cond
(paren
id|ch
op_ne
l_char|&squot;:&squot;
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * &quot;$Id: ... &quot;; scan up to the closing dollar sign and discard.&n;&t;&t; */
r_while
c_loop
(paren
id|size
)paren
(brace
id|ch
op_assign
op_star
id|cp
op_increment
suffix:semicolon
id|size
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;$&squot;
)paren
(brace
id|cnt
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
DECL|function|ident_to_git
r_static
r_int
id|ident_to_git
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|ident
)paren
(brace
r_char
op_star
id|dst
comma
op_star
id|dollar
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ident
op_logical_or
op_logical_neg
id|count_ident
c_func
(paren
id|src
comma
id|len
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* only grow if not in place */
r_if
c_cond
(paren
id|strbuf_avail
c_func
(paren
id|buf
)paren
op_plus
id|buf-&gt;len
OL
id|len
)paren
id|strbuf_grow
c_func
(paren
id|buf
comma
id|len
id|buf-&gt;len
)paren
suffix:semicolon
id|dst
op_assign
id|buf-&gt;buf
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|dollar
op_assign
id|memchr
c_func
(paren
id|src
comma
l_char|&squot;$&squot;
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dollar
)paren
r_break
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|dollar
op_plus
l_int|1
id|src
)paren
suffix:semicolon
id|dst
op_add_assign
id|dollar
op_plus
l_int|1
id|src
suffix:semicolon
id|len
op_sub_assign
id|dollar
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|dollar
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|3
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|src
comma
l_string|&quot;Id:&quot;
comma
l_int|3
)paren
)paren
(brace
id|dollar
op_assign
id|memchr
c_func
(paren
id|src
op_plus
l_int|3
comma
l_char|&squot;$&squot;
comma
id|len
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dollar
)paren
r_break
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
l_string|&quot;Id$&quot;
comma
l_int|3
)paren
suffix:semicolon
id|dst
op_add_assign
l_int|3
suffix:semicolon
id|len
op_sub_assign
id|dollar
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|dollar
op_plus
l_int|1
suffix:semicolon
)brace
)brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|buf
comma
id|dst
op_plus
id|len
id|buf-&gt;buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ident_to_worktree
r_static
r_int
id|ident_to_worktree
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|ident
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|to_free
op_assign
l_int|NULL
comma
op_star
id|dollar
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ident
)paren
r_return
l_int|0
suffix:semicolon
id|cnt
op_assign
id|count_ident
c_func
(paren
id|src
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cnt
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* are we &quot;faking&quot; in place editing ? */
r_if
c_cond
(paren
id|src
op_eq
id|buf-&gt;buf
)paren
id|to_free
op_assign
id|strbuf_detach
c_func
(paren
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|hash_sha1_file
c_func
(paren
id|src
comma
id|len
comma
l_string|&quot;blob&quot;
comma
id|sha1
)paren
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|buf
comma
id|len
op_plus
id|cnt
op_star
l_int|43
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* step 1: run to the next &squot;$&squot; */
id|dollar
op_assign
id|memchr
c_func
(paren
id|src
comma
l_char|&squot;$&squot;
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dollar
)paren
r_break
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|dollar
op_plus
l_int|1
id|src
)paren
suffix:semicolon
id|len
op_sub_assign
id|dollar
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|dollar
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* step 2: does it looks like a bit like Id:xxx$ or Id$ ? */
r_if
c_cond
(paren
id|len
OL
l_int|3
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;Id&quot;
comma
id|src
comma
l_int|2
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* step 3: skip over Id$ or Id:xxxxx$ */
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_eq
l_char|&squot;$&squot;
)paren
(brace
id|src
op_add_assign
l_int|3
suffix:semicolon
id|len
op_sub_assign
l_int|3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * It&squot;s possible that an expanded Id has crept its way into the&n;&t;&t;&t; * repository, we cope with that by stripping the expansion out&n;&t;&t;&t; */
id|dollar
op_assign
id|memchr
c_func
(paren
id|src
op_plus
l_int|3
comma
l_char|&squot;$&squot;
comma
id|len
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dollar
)paren
(brace
multiline_comment|/* incomplete keyword, no more &squot;$&squot;, so just quit the loop */
r_break
suffix:semicolon
)brace
id|len
op_sub_assign
id|dollar
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|dollar
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* it wasn&squot;t a &quot;Id$&quot; or &quot;Id:xxxx$&quot; */
r_continue
suffix:semicolon
)brace
multiline_comment|/* step 4: substitute */
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot;Id: &quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|buf
comma
l_string|&quot; $&quot;
)paren
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|free
c_func
(paren
id|to_free
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|git_path_check_crlf
r_static
r_int
id|git_path_check_crlf
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|check-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|value
)paren
)paren
r_return
id|CRLF_TEXT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_FALSE
c_func
(paren
id|value
)paren
)paren
r_return
id|CRLF_BINARY
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_UNSET
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;input&quot;
)paren
)paren
r_return
id|CRLF_INPUT
suffix:semicolon
r_return
id|CRLF_GUESS
suffix:semicolon
)brace
DECL|function|git_path_check_convert
r_static
r_struct
id|convert_driver
op_star
id|git_path_check_convert
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|check-&gt;value
suffix:semicolon
r_struct
id|convert_driver
op_star
id|drv
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|value
)paren
op_logical_or
id|ATTR_FALSE
c_func
(paren
id|value
)paren
op_logical_or
id|ATTR_UNSET
c_func
(paren
id|value
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|drv
op_assign
id|user_convert
suffix:semicolon
id|drv
suffix:semicolon
id|drv
op_assign
id|drv-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
id|drv-&gt;name
)paren
)paren
r_return
id|drv
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|git_path_check_ident
r_static
r_int
id|git_path_check_ident
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|check-&gt;value
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|ATTR_TRUE
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
DECL|function|convert_to_git
r_int
id|convert_to_git
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|dst
)paren
(brace
r_struct
id|git_attr_check
id|check
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|crlf
op_assign
id|CRLF_GUESS
suffix:semicolon
r_int
id|ident
op_assign
l_int|0
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|filter
op_assign
l_int|NULL
suffix:semicolon
id|setup_convert_check
c_func
(paren
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_checkattr
c_func
(paren
id|path
comma
id|ARRAY_SIZE
c_func
(paren
id|check
)paren
comma
id|check
)paren
)paren
(brace
r_struct
id|convert_driver
op_star
id|drv
suffix:semicolon
id|crlf
op_assign
id|git_path_check_crlf
c_func
(paren
id|path
comma
id|check
op_plus
l_int|0
)paren
suffix:semicolon
id|ident
op_assign
id|git_path_check_ident
c_func
(paren
id|path
comma
id|check
op_plus
l_int|1
)paren
suffix:semicolon
id|drv
op_assign
id|git_path_check_convert
c_func
(paren
id|path
comma
id|check
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
op_logical_and
id|drv-&gt;clean
)paren
id|filter
op_assign
id|drv-&gt;clean
suffix:semicolon
)brace
id|ret
op_or_assign
id|apply_filter
c_func
(paren
id|path
comma
id|src
comma
id|len
comma
id|dst
comma
id|filter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|src
op_assign
id|dst-&gt;buf
suffix:semicolon
id|len
op_assign
id|dst-&gt;len
suffix:semicolon
)brace
id|ret
op_or_assign
id|crlf_to_git
c_func
(paren
id|path
comma
id|src
comma
id|len
comma
id|dst
comma
id|crlf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|src
op_assign
id|dst-&gt;buf
suffix:semicolon
id|len
op_assign
id|dst-&gt;len
suffix:semicolon
)brace
r_return
id|ret
op_or
id|ident_to_git
c_func
(paren
id|path
comma
id|src
comma
id|len
comma
id|dst
comma
id|ident
)paren
suffix:semicolon
)brace
DECL|function|convert_to_working_tree
r_int
id|convert_to_working_tree
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|dst
)paren
(brace
r_struct
id|git_attr_check
id|check
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|crlf
op_assign
id|CRLF_GUESS
suffix:semicolon
r_int
id|ident
op_assign
l_int|0
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|filter
op_assign
l_int|NULL
suffix:semicolon
id|setup_convert_check
c_func
(paren
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_checkattr
c_func
(paren
id|path
comma
id|ARRAY_SIZE
c_func
(paren
id|check
)paren
comma
id|check
)paren
)paren
(brace
r_struct
id|convert_driver
op_star
id|drv
suffix:semicolon
id|crlf
op_assign
id|git_path_check_crlf
c_func
(paren
id|path
comma
id|check
op_plus
l_int|0
)paren
suffix:semicolon
id|ident
op_assign
id|git_path_check_ident
c_func
(paren
id|path
comma
id|check
op_plus
l_int|1
)paren
suffix:semicolon
id|drv
op_assign
id|git_path_check_convert
c_func
(paren
id|path
comma
id|check
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
op_logical_and
id|drv-&gt;smudge
)paren
id|filter
op_assign
id|drv-&gt;smudge
suffix:semicolon
)brace
id|ret
op_or_assign
id|ident_to_worktree
c_func
(paren
id|path
comma
id|src
comma
id|len
comma
id|dst
comma
id|ident
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|src
op_assign
id|dst-&gt;buf
suffix:semicolon
id|len
op_assign
id|dst-&gt;len
suffix:semicolon
)brace
id|ret
op_or_assign
id|crlf_to_worktree
c_func
(paren
id|path
comma
id|src
comma
id|len
comma
id|dst
comma
id|crlf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|src
op_assign
id|dst-&gt;buf
suffix:semicolon
id|len
op_assign
id|dst-&gt;len
suffix:semicolon
)brace
r_return
id|ret
op_or
id|apply_filter
c_func
(paren
id|path
comma
id|src
comma
id|len
comma
id|dst
comma
id|filter
)paren
suffix:semicolon
)brace
eof
