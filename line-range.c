macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;line-range.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;userdiff.h&quot;
multiline_comment|/*&n; * Parse one item in the -L option&n; */
DECL|function|parse_loc
r_static
r_const
r_char
op_star
id|parse_loc
c_func
(paren
r_const
r_char
op_star
id|spec
comma
id|nth_line_fn_t
id|nth_line
comma
r_void
op_star
id|data
comma
r_int
id|lines
comma
r_int
id|begin
comma
r_int
op_star
id|ret
)paren
(brace
r_char
op_star
id|term
suffix:semicolon
r_const
r_char
op_star
id|line
suffix:semicolon
r_int
id|num
suffix:semicolon
r_int
id|reg_error
suffix:semicolon
id|regex_t
id|regexp
suffix:semicolon
id|regmatch_t
id|match
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Allow &quot;-L &lt;something&gt;,+20&quot; to mean starting at &lt;something&gt;&n;&t; * for 20 lines, or &quot;-L &lt;something&gt;,-5&quot; for 5 lines ending at&n;&t; * &lt;something&gt;.&n;&t; */
r_if
c_cond
(paren
l_int|1
OL
id|begin
op_logical_and
(paren
id|spec
(braket
l_int|0
)braket
op_eq
l_char|&squot;+&squot;
op_logical_or
id|spec
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
)paren
(brace
id|num
op_assign
id|strtol
c_func
(paren
id|spec
op_plus
l_int|1
comma
op_amp
id|term
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|term
op_ne
id|spec
op_plus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
id|term
suffix:semicolon
r_if
c_cond
(paren
id|spec
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|num
op_assign
l_int|0
id|num
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OL
id|num
)paren
op_star
id|ret
op_assign
id|begin
op_plus
id|num
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|num
)paren
op_star
id|ret
op_assign
id|begin
suffix:semicolon
r_else
op_star
id|ret
op_assign
id|begin
op_plus
id|num
suffix:semicolon
r_return
id|term
suffix:semicolon
)brace
r_return
id|spec
suffix:semicolon
)brace
id|num
op_assign
id|strtol
c_func
(paren
id|spec
comma
op_amp
id|term
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|term
op_ne
id|spec
)paren
(brace
r_if
c_cond
(paren
id|ret
)paren
op_star
id|ret
op_assign
id|num
suffix:semicolon
r_return
id|term
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spec
(braket
l_int|0
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_return
id|spec
suffix:semicolon
multiline_comment|/* it could be a regexp of form /.../ */
r_for
c_loop
(paren
id|term
op_assign
(paren
r_char
op_star
)paren
id|spec
op_plus
l_int|1
suffix:semicolon
op_star
id|term
op_logical_and
op_star
id|term
op_ne
l_char|&squot;/&squot;
suffix:semicolon
id|term
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|term
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
id|term
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|term
op_ne
l_char|&squot;/&squot;
)paren
r_return
id|spec
suffix:semicolon
multiline_comment|/* in the scan-only case we are not interested in the regex */
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
id|term
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* try [spec+1 .. term-1] as regexp */
op_star
id|term
op_assign
l_int|0
suffix:semicolon
id|begin
op_decrement
suffix:semicolon
multiline_comment|/* input is in human terms */
id|line
op_assign
id|nth_line
c_func
(paren
id|data
comma
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg_error
op_assign
id|regcomp
c_func
(paren
op_amp
id|regexp
comma
id|spec
op_plus
l_int|1
comma
id|REG_NEWLINE
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|reg_error
op_assign
id|regexec
c_func
(paren
op_amp
id|regexp
comma
id|line
comma
l_int|1
comma
id|match
comma
l_int|0
)paren
)paren
)paren
(brace
r_const
r_char
op_star
id|cp
op_assign
id|line
op_plus
id|match
(braket
l_int|0
)braket
dot
id|rm_so
suffix:semicolon
r_const
r_char
op_star
id|nline
suffix:semicolon
r_while
c_loop
(paren
id|begin
op_increment
OL
id|lines
)paren
(brace
id|nline
op_assign
id|nth_line
c_func
(paren
id|data
comma
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
op_le
id|cp
op_logical_and
id|cp
OL
id|nline
)paren
r_break
suffix:semicolon
id|line
op_assign
id|nline
suffix:semicolon
)brace
op_star
id|ret
op_assign
id|begin
suffix:semicolon
id|regfree
c_func
(paren
op_amp
id|regexp
)paren
suffix:semicolon
op_star
id|term
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_return
id|term
suffix:semicolon
)brace
r_else
(brace
r_char
id|errbuf
(braket
l_int|1024
)braket
suffix:semicolon
id|regerror
c_func
(paren
id|reg_error
comma
op_amp
id|regexp
comma
id|errbuf
comma
l_int|1024
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;-L parameter &squot;%s&squot;: %s&quot;
comma
id|spec
op_plus
l_int|1
comma
id|errbuf
)paren
suffix:semicolon
)brace
)brace
DECL|function|match_funcname
r_static
r_int
id|match_funcname
c_func
(paren
id|xdemitconf_t
op_star
id|xecfg
comma
r_const
r_char
op_star
id|bol
comma
r_const
r_char
op_star
id|eol
)paren
(brace
r_if
c_cond
(paren
id|xecfg
)paren
(brace
r_char
id|buf
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|xecfg
op_member_access_from_pointer
id|find_func
c_func
(paren
id|bol
comma
id|eol
id|bol
comma
id|buf
comma
l_int|1
comma
id|xecfg-&gt;find_func_priv
)paren
op_ge
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bol
op_eq
id|eol
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|isalpha
c_func
(paren
op_star
id|bol
)paren
op_logical_or
op_star
id|bol
op_eq
l_char|&squot;_&squot;
op_logical_or
op_star
id|bol
op_eq
l_char|&squot;$&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|find_funcname_matching_regexp
r_static
r_const
r_char
op_star
id|find_funcname_matching_regexp
c_func
(paren
id|xdemitconf_t
op_star
id|xecfg
comma
r_const
r_char
op_star
id|start
comma
id|regex_t
op_star
id|regexp
)paren
(brace
r_int
id|reg_error
suffix:semicolon
id|regmatch_t
id|match
(braket
l_int|1
)braket
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_const
r_char
op_star
id|bol
comma
op_star
id|eol
suffix:semicolon
id|reg_error
op_assign
id|regexec
c_func
(paren
id|regexp
comma
id|start
comma
l_int|1
comma
id|match
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg_error
op_eq
id|REG_NOMATCH
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|reg_error
)paren
(brace
r_char
id|errbuf
(braket
l_int|1024
)braket
suffix:semicolon
id|regerror
c_func
(paren
id|reg_error
comma
id|regexp
comma
id|errbuf
comma
l_int|1024
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;-L parameter: regexec() failed: %s&quot;
comma
id|errbuf
)paren
suffix:semicolon
)brace
multiline_comment|/* determine extent of line matched */
id|bol
op_assign
id|start
op_plus
id|match
(braket
l_int|0
)braket
dot
id|rm_so
suffix:semicolon
id|eol
op_assign
id|start
op_plus
id|match
(braket
l_int|0
)braket
dot
id|rm_eo
suffix:semicolon
r_while
c_loop
(paren
id|bol
OG
id|start
op_logical_and
op_star
id|bol
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|bol
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bol
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|bol
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_star
id|eol
op_logical_and
op_star
id|eol
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|eol
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|eol
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|eol
op_increment
suffix:semicolon
multiline_comment|/* is it a funcname line? */
r_if
c_cond
(paren
id|match_funcname
c_func
(paren
id|xecfg
comma
(paren
r_char
op_star
)paren
id|bol
comma
(paren
r_char
op_star
)paren
id|eol
)paren
)paren
r_return
id|bol
suffix:semicolon
id|start
op_assign
id|eol
suffix:semicolon
)brace
)brace
DECL|function|parse_range_funcname
r_static
r_const
r_char
op_star
id|parse_range_funcname
c_func
(paren
r_const
r_char
op_star
id|arg
comma
id|nth_line_fn_t
id|nth_line_cb
comma
r_void
op_star
id|cb_data
comma
r_int
id|lines
comma
r_int
op_star
id|begin
comma
r_int
op_star
id|end
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_char
op_star
id|pattern
suffix:semicolon
r_const
r_char
op_star
id|term
suffix:semicolon
r_struct
id|userdiff_driver
op_star
id|drv
suffix:semicolon
id|xdemitconf_t
op_star
id|xecfg
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|start
suffix:semicolon
r_const
r_char
op_star
id|p
suffix:semicolon
r_int
id|reg_error
suffix:semicolon
id|regex_t
id|regexp
suffix:semicolon
m_assert
(paren
op_star
id|arg
op_eq
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|term
op_assign
id|arg
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_star
id|term
op_logical_and
op_star
id|term
op_ne
l_char|&squot;:&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|term
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
op_star
(paren
id|term
op_plus
l_int|1
)paren
)paren
id|term
op_increment
suffix:semicolon
id|term
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|term
op_eq
id|arg
op_plus
l_int|1
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|begin
)paren
multiline_comment|/* skip_range_arg case */
r_return
id|term
suffix:semicolon
id|pattern
op_assign
id|xstrndup
c_func
(paren
id|arg
op_plus
l_int|1
comma
id|term
op_minus
(paren
id|arg
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|start
op_assign
id|nth_line_cb
c_func
(paren
id|cb_data
comma
l_int|0
)paren
suffix:semicolon
id|drv
op_assign
id|userdiff_find_by_path
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv
op_logical_and
id|drv-&gt;funcname.pattern
)paren
(brace
r_const
r_struct
id|userdiff_funcname
op_star
id|pe
op_assign
op_amp
id|drv-&gt;funcname
suffix:semicolon
id|xecfg
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|xecfg
)paren
)paren
suffix:semicolon
id|xdiff_set_find_func
c_func
(paren
id|xecfg
comma
id|pe-&gt;pattern
comma
id|pe-&gt;cflags
)paren
suffix:semicolon
)brace
id|reg_error
op_assign
id|regcomp
c_func
(paren
op_amp
id|regexp
comma
id|pattern
comma
id|REG_NEWLINE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg_error
)paren
(brace
r_char
id|errbuf
(braket
l_int|1024
)braket
suffix:semicolon
id|regerror
c_func
(paren
id|reg_error
comma
op_amp
id|regexp
comma
id|errbuf
comma
l_int|1024
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;-L parameter &squot;%s&squot;: %s&quot;
comma
id|pattern
comma
id|errbuf
)paren
suffix:semicolon
)brace
id|p
op_assign
id|find_funcname_matching_regexp
c_func
(paren
id|xecfg
comma
(paren
r_char
op_star
)paren
id|start
comma
op_amp
id|regexp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|die
c_func
(paren
l_string|&quot;-L parameter &squot;%s&squot;: no match&quot;
comma
id|pattern
)paren
suffix:semicolon
op_star
id|begin
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
OG
id|nth_line_cb
c_func
(paren
id|cb_data
comma
op_star
id|begin
)paren
)paren
(paren
op_star
id|begin
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|begin
op_ge
id|lines
)paren
id|die
c_func
(paren
l_string|&quot;-L parameter &squot;%s&squot; matches at EOF&quot;
comma
id|pattern
)paren
suffix:semicolon
op_star
id|end
op_assign
op_star
id|begin
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_star
id|end
OL
id|lines
)paren
(brace
r_const
r_char
op_star
id|bol
op_assign
id|nth_line_cb
c_func
(paren
id|cb_data
comma
op_star
id|end
)paren
suffix:semicolon
r_const
r_char
op_star
id|eol
op_assign
id|nth_line_cb
c_func
(paren
id|cb_data
comma
op_star
id|end
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_funcname
c_func
(paren
id|xecfg
comma
id|bol
comma
id|eol
)paren
)paren
r_break
suffix:semicolon
(paren
op_star
id|end
)paren
op_increment
suffix:semicolon
)brace
id|regfree
c_func
(paren
op_amp
id|regexp
)paren
suffix:semicolon
id|free
c_func
(paren
id|xecfg
)paren
suffix:semicolon
id|free
c_func
(paren
id|pattern
)paren
suffix:semicolon
multiline_comment|/* compensate for 1-based numbering */
(paren
op_star
id|begin
)paren
op_increment
suffix:semicolon
r_return
id|term
suffix:semicolon
)brace
DECL|function|parse_range_arg
r_int
id|parse_range_arg
c_func
(paren
r_const
r_char
op_star
id|arg
comma
id|nth_line_fn_t
id|nth_line_cb
comma
r_void
op_star
id|cb_data
comma
r_int
id|lines
comma
r_int
op_star
id|begin
comma
r_int
op_star
id|end
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|arg
op_assign
id|parse_range_funcname
c_func
(paren
id|arg
comma
id|nth_line_cb
comma
id|cb_data
comma
id|lines
comma
id|begin
comma
id|end
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
op_logical_or
op_star
id|arg
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|arg
op_assign
id|parse_loc
c_func
(paren
id|arg
comma
id|nth_line_cb
comma
id|cb_data
comma
id|lines
comma
l_int|1
comma
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;,&squot;
)paren
id|arg
op_assign
id|parse_loc
c_func
(paren
id|arg
op_plus
l_int|1
comma
id|nth_line_cb
comma
id|cb_data
comma
id|lines
comma
op_star
id|begin
op_plus
l_int|1
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|skip_range_arg
r_const
r_char
op_star
id|skip_range_arg
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;:&squot;
)paren
r_return
id|parse_range_funcname
c_func
(paren
id|arg
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|arg
op_assign
id|parse_loc
c_func
(paren
id|arg
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;,&squot;
)paren
id|arg
op_assign
id|parse_loc
c_func
(paren
id|arg
op_plus
l_int|1
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|arg
suffix:semicolon
)brace
eof
