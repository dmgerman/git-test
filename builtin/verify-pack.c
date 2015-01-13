macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|macro|VERIFY_PACK_VERBOSE
mdefine_line|#define VERIFY_PACK_VERBOSE 01
DECL|macro|VERIFY_PACK_STAT_ONLY
mdefine_line|#define VERIFY_PACK_STAT_ONLY 02
DECL|function|verify_one_pack
r_static
r_int
id|verify_one_pack
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|child_process
id|index_pack
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;index-pack&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|strbuf
id|arg
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|verbose
op_assign
id|flags
op_amp
id|VERIFY_PACK_VERBOSE
suffix:semicolon
r_int
id|stat_only
op_assign
id|flags
op_amp
id|VERIFY_PACK_STAT_ONLY
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|stat_only
)paren
id|argv
(braket
l_int|1
)braket
op_assign
l_string|&quot;--verify-stat-only&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|verbose
)paren
id|argv
(braket
l_int|1
)braket
op_assign
l_string|&quot;--verify-stat&quot;
suffix:semicolon
r_else
id|argv
(braket
l_int|1
)braket
op_assign
l_string|&quot;--verify&quot;
suffix:semicolon
multiline_comment|/*&n;&t; * In addition to &quot;foo.pack&quot; we accept &quot;foo.idx&quot; and &quot;foo&quot;;&n;&t; * normalize these forms to &quot;foo.pack&quot; for &quot;index-pack --verify&quot;.&n;&t; */
id|strbuf_addstr
c_func
(paren
op_amp
id|arg
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_strip_suffix
c_func
(paren
op_amp
id|arg
comma
l_string|&quot;.idx&quot;
)paren
op_logical_or
op_logical_neg
id|ends_with
c_func
(paren
id|arg.buf
comma
l_string|&quot;.pack&quot;
)paren
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|arg
comma
l_string|&quot;.pack&quot;
)paren
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
id|arg.buf
suffix:semicolon
id|index_pack.argv
op_assign
id|argv
suffix:semicolon
id|index_pack.git_cmd
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|run_command
c_func
(paren
op_amp
id|index_pack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
op_logical_or
id|stat_only
)paren
(brace
r_if
c_cond
(paren
id|err
)paren
id|printf
c_func
(paren
l_string|&quot;%s: bad&bslash;n&quot;
comma
id|arg.buf
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|stat_only
)paren
id|printf
c_func
(paren
l_string|&quot;%s: ok&bslash;n&quot;
comma
id|arg.buf
)paren
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|arg
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|verify_pack_usage
r_static
r_const
r_char
op_star
r_const
id|verify_pack_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git verify-pack [-v | --verbose] [-s | --stat-only] &lt;pack&gt;...&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_verify_pack
r_int
id|cmd_verify_pack
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
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_const
r_struct
id|option
id|verify_pack_options
(braket
)braket
op_assign
(brace
id|OPT_BIT
c_func
(paren
l_char|&squot;v&squot;
comma
l_string|&quot;verbose&quot;
comma
op_amp
id|flags
comma
id|N_
c_func
(paren
l_string|&quot;verbose&quot;
)paren
comma
id|VERIFY_PACK_VERBOSE
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;s&squot;
comma
l_string|&quot;stat-only&quot;
comma
op_amp
id|flags
comma
id|N_
c_func
(paren
l_string|&quot;show statistics only&quot;
)paren
comma
id|VERIFY_PACK_STAT_ONLY
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
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
id|verify_pack_options
comma
id|verify_pack_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|verify_pack_usage
comma
id|verify_pack_options
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|verify_one_pack
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|flags
)paren
)paren
id|err
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
eof
