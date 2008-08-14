macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
DECL|function|parse_num
r_static
r_int
id|parse_num
c_func
(paren
r_char
op_star
op_star
id|cp_p
comma
r_int
op_star
id|num_p
)paren
(brace
r_char
op_star
id|cp
op_assign
op_star
id|cp_p
suffix:semicolon
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_int
id|read_some
suffix:semicolon
r_while
c_loop
(paren
l_char|&squot;0&squot;
op_le
op_star
id|cp
op_logical_and
op_star
id|cp
op_le
l_char|&squot;9&squot;
)paren
id|num
op_assign
id|num
op_star
l_int|10
op_plus
op_star
id|cp
op_increment
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|read_some
op_assign
id|cp
op_star
id|cp_p
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|cp_p
op_assign
id|cp
suffix:semicolon
op_star
id|num_p
op_assign
id|num
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_hunk_header
r_int
id|parse_hunk_header
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
op_star
id|ob
comma
r_int
op_star
id|on
comma
r_int
op_star
id|nb
comma
r_int
op_star
id|nn
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
id|cp
op_assign
id|line
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|ob
)paren
)paren
(brace
id|bad_line
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;malformed diff output: %s&quot;
comma
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;,&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|on
)paren
)paren
r_goto
id|bad_line
suffix:semicolon
)brace
r_else
op_star
id|on
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot; &squot;
op_logical_or
op_star
id|cp
op_increment
op_ne
l_char|&squot;+&squot;
)paren
r_goto
id|bad_line
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|nb
)paren
)paren
r_goto
id|bad_line
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;,&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|nn
)paren
)paren
r_goto
id|bad_line
suffix:semicolon
)brace
r_else
op_star
id|nn
op_assign
l_int|1
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|memcmp
c_func
(paren
id|cp
comma
l_string|&quot; @@&quot;
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|consume_one
r_static
r_void
id|consume_one
c_func
(paren
r_void
op_star
id|priv_
comma
r_char
op_star
id|s
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|xdiff_emit_state
op_star
id|priv
op_assign
id|priv_
suffix:semicolon
r_char
op_star
id|ep
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_int
r_int
id|this_size
suffix:semicolon
id|ep
op_assign
id|memchr
c_func
(paren
id|s
comma
l_char|&squot;&bslash;n&squot;
comma
id|size
)paren
suffix:semicolon
id|this_size
op_assign
(paren
id|ep
op_eq
l_int|NULL
)paren
ques
c_cond
id|size
suffix:colon
(paren
id|ep
id|s
op_plus
l_int|1
)paren
suffix:semicolon
id|priv
op_member_access_from_pointer
id|consume
c_func
(paren
id|priv
comma
id|s
comma
id|this_size
)paren
suffix:semicolon
id|size
op_sub_assign
id|this_size
suffix:semicolon
id|s
op_add_assign
id|this_size
suffix:semicolon
)brace
)brace
DECL|function|xdiff_outf
r_static
r_int
id|xdiff_outf
c_func
(paren
r_void
op_star
id|priv_
comma
id|mmbuffer_t
op_star
id|mb
comma
r_int
id|nbuf
)paren
(brace
r_struct
id|xdiff_emit_state
op_star
id|priv
op_assign
id|priv_
suffix:semicolon
r_int
id|i
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
id|nbuf
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mb
(braket
id|i
)braket
dot
id|ptr
(braket
id|mb
(braket
id|i
)braket
dot
id|size
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* Incomplete line */
id|strbuf_add
c_func
(paren
op_amp
id|priv-&gt;remainder
comma
id|mb
(braket
id|i
)braket
dot
id|ptr
comma
id|mb
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* we have a complete line */
r_if
c_cond
(paren
op_logical_neg
id|priv-&gt;remainder.len
)paren
(brace
id|consume_one
c_func
(paren
id|priv
comma
id|mb
(braket
id|i
)braket
dot
id|ptr
comma
id|mb
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
op_amp
id|priv-&gt;remainder
comma
id|mb
(braket
id|i
)braket
dot
id|ptr
comma
id|mb
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|consume_one
c_func
(paren
id|priv
comma
id|priv-&gt;remainder.buf
comma
id|priv-&gt;remainder.len
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|priv-&gt;remainder
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;remainder.len
)paren
(brace
id|consume_one
c_func
(paren
id|priv
comma
id|priv-&gt;remainder.buf
comma
id|priv-&gt;remainder.len
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|priv-&gt;remainder
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Trim down common substring at the end of the buffers,&n; * but leave at least ctx lines at the end.&n; */
DECL|function|trim_common_tail
r_static
r_void
id|trim_common_tail
c_func
(paren
id|mmfile_t
op_star
id|a
comma
id|mmfile_t
op_star
id|b
comma
r_int
id|ctx
)paren
(brace
r_const
r_int
id|blk
op_assign
l_int|1024
suffix:semicolon
r_int
id|trimmed
op_assign
l_int|0
comma
id|recovered
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|ap
op_assign
id|a-&gt;ptr
op_plus
id|a-&gt;size
suffix:semicolon
r_char
op_star
id|bp
op_assign
id|b-&gt;ptr
op_plus
id|b-&gt;size
suffix:semicolon
r_int
id|smaller
op_assign
(paren
id|a-&gt;size
OL
id|b-&gt;size
)paren
ques
c_cond
id|a-&gt;size
suffix:colon
id|b-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|ctx
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|blk
op_plus
id|trimmed
op_le
id|smaller
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ap
id|blk
comma
id|bp
id|blk
comma
id|blk
)paren
)paren
(brace
id|trimmed
op_add_assign
id|blk
suffix:semicolon
id|ap
op_sub_assign
id|blk
suffix:semicolon
id|bp
op_sub_assign
id|blk
suffix:semicolon
)brace
r_while
c_loop
(paren
id|recovered
OL
id|trimmed
)paren
r_if
c_cond
(paren
id|ap
(braket
id|recovered
op_increment
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
id|a-&gt;size
op_sub_assign
id|trimmed
id|recovered
suffix:semicolon
id|b-&gt;size
op_sub_assign
id|trimmed
id|recovered
suffix:semicolon
)brace
DECL|function|xdi_diff
r_int
id|xdi_diff
c_func
(paren
id|mmfile_t
op_star
id|mf1
comma
id|mmfile_t
op_star
id|mf2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdemitconf_t
r_const
op_star
id|xecfg
comma
id|xdemitcb_t
op_star
id|xecb
)paren
(brace
id|mmfile_t
id|a
op_assign
op_star
id|mf1
suffix:semicolon
id|mmfile_t
id|b
op_assign
op_star
id|mf2
suffix:semicolon
id|trim_common_tail
c_func
(paren
op_amp
id|a
comma
op_amp
id|b
comma
id|xecfg-&gt;ctxlen
)paren
suffix:semicolon
r_return
id|xdl_diff
c_func
(paren
op_amp
id|a
comma
op_amp
id|b
comma
id|xpp
comma
id|xecfg
comma
id|xecb
)paren
suffix:semicolon
)brace
DECL|function|xdi_diff_outf
r_int
id|xdi_diff_outf
c_func
(paren
id|mmfile_t
op_star
id|mf1
comma
id|mmfile_t
op_star
id|mf2
comma
r_struct
id|xdiff_emit_state
op_star
id|state
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdemitconf_t
r_const
op_star
id|xecfg
comma
id|xdemitcb_t
op_star
id|xecb
)paren
(brace
r_int
id|ret
suffix:semicolon
id|xecb-&gt;outf
op_assign
id|xdiff_outf
suffix:semicolon
id|xecb-&gt;priv
op_assign
id|state
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|state-&gt;remainder
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|xdi_diff
c_func
(paren
id|mf1
comma
id|mf2
comma
id|xpp
comma
id|xecfg
comma
id|xecb
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|state-&gt;remainder
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|read_mmfile
r_int
id|read_mmfile
c_func
(paren
id|mmfile_t
op_star
id|ptr
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
r_int
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|filename
comma
op_amp
id|st
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not stat %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|f
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;rb&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open %s&quot;
comma
id|filename
)paren
suffix:semicolon
id|sz
op_assign
id|xsize_t
c_func
(paren
id|st.st_size
)paren
suffix:semicolon
id|ptr-&gt;ptr
op_assign
id|xmalloc
c_func
(paren
id|sz
ques
c_cond
id|sz
suffix:colon
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
op_logical_and
id|fread
c_func
(paren
id|ptr-&gt;ptr
comma
id|sz
comma
l_int|1
comma
id|f
)paren
op_ne
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not read %s&quot;
comma
id|filename
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
id|ptr-&gt;size
op_assign
id|sz
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|FIRST_FEW_BYTES
mdefine_line|#define FIRST_FEW_BYTES 8000
DECL|function|buffer_is_binary
r_int
id|buffer_is_binary
c_func
(paren
r_const
r_char
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|FIRST_FEW_BYTES
OL
id|size
)paren
id|size
op_assign
id|FIRST_FEW_BYTES
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|memchr
c_func
(paren
id|ptr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
DECL|struct|ff_regs
r_struct
id|ff_regs
(brace
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|struct|ff_reg
r_struct
id|ff_reg
(brace
DECL|member|re
id|regex_t
id|re
suffix:semicolon
DECL|member|negate
r_int
id|negate
suffix:semicolon
DECL|member|array
)brace
op_star
id|array
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ff_regexp
r_static
r_int
id|ff_regexp
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
comma
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
comma
r_void
op_star
id|priv
)paren
(brace
r_char
op_star
id|line_buffer
op_assign
id|xstrndup
c_func
(paren
id|line
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* make NUL terminated */
r_struct
id|ff_regs
op_star
id|regs
op_assign
id|priv
suffix:semicolon
id|regmatch_t
id|pmatch
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|result
op_assign
l_int|0
comma
id|i
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
id|regs-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ff_reg
op_star
id|reg
op_assign
id|regs-&gt;array
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;negate
op_xor
op_logical_neg
op_logical_neg
id|regexec
c_func
(paren
op_amp
id|reg-&gt;re
comma
id|line_buffer
comma
l_int|2
comma
id|pmatch
comma
l_int|0
)paren
)paren
(brace
id|free
c_func
(paren
id|line_buffer
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|i
op_assign
id|pmatch
(braket
l_int|1
)braket
dot
id|rm_so
op_ge
l_int|0
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|line
op_add_assign
id|pmatch
(braket
id|i
)braket
dot
id|rm_so
suffix:semicolon
id|result
op_assign
id|pmatch
(braket
id|i
)braket
dot
id|rm_eo
id|pmatch
(braket
id|i
)braket
dot
id|rm_so
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
id|buffer_size
)paren
id|result
op_assign
id|buffer_size
suffix:semicolon
r_else
r_while
c_loop
(paren
id|result
OG
l_int|0
op_logical_and
(paren
id|isspace
c_func
(paren
id|line
(braket
id|result
l_int|1
)braket
)paren
op_logical_or
id|line
(braket
id|result
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
id|result
op_decrement
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|line
comma
id|result
)paren
suffix:semicolon
id|free
c_func
(paren
id|line_buffer
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|xdiff_set_find_func
r_void
id|xdiff_set_find_func
c_func
(paren
id|xdemitconf_t
op_star
id|xecfg
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ff_regs
op_star
id|regs
suffix:semicolon
id|xecfg-&gt;find_func
op_assign
id|ff_regexp
suffix:semicolon
id|regs
op_assign
id|xecfg-&gt;find_func_priv
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ff_regs
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|regs-&gt;nr
op_assign
l_int|1
suffix:semicolon
id|value
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|value
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|regs-&gt;nr
op_increment
suffix:semicolon
id|regs-&gt;array
op_assign
id|xmalloc
c_func
(paren
id|regs-&gt;nr
op_star
r_sizeof
(paren
r_struct
id|ff_reg
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
id|regs-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ff_reg
op_star
id|reg
op_assign
id|regs-&gt;array
op_plus
id|i
suffix:semicolon
r_const
r_char
op_star
id|ep
op_assign
id|strchr
c_func
(paren
id|value
comma
l_char|&squot;&bslash;n&squot;
)paren
comma
op_star
id|expression
suffix:semicolon
r_char
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|reg-&gt;negate
op_assign
(paren
op_star
id|value
op_eq
l_char|&squot;!&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;negate
op_logical_and
id|i
op_eq
id|regs-&gt;nr
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Last expression must not be negated: %s&quot;
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
op_eq
l_char|&squot;!&squot;
)paren
id|value
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
id|expression
op_assign
id|buffer
op_assign
id|xstrndup
c_func
(paren
id|value
comma
id|ep
id|value
)paren
suffix:semicolon
r_else
id|expression
op_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|regcomp
c_func
(paren
op_amp
id|reg-&gt;re
comma
id|expression
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Invalid regexp to look for hunk header: %s&quot;
comma
id|expression
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|value
op_assign
id|ep
op_plus
l_int|1
suffix:semicolon
)brace
)brace
eof
