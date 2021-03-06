multiline_comment|/*&n; * Builtin &quot;git verify-tag&quot;&n; *&n; * Copyright (c) 2007 Carlos Rica &lt;jasampler@gmail.com&gt;&n; *&n; * Based on git-verify-tag.sh&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;gpg-interface.h&quot;
DECL|variable|verify_tag_usage
r_static
r_const
r_char
op_star
r_const
id|verify_tag_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git verify-tag [-v | --verbose] &lt;tag&gt;...&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|run_gpg_verify
r_static
r_int
id|run_gpg_verify
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
r_int
id|flags
)paren
(brace
r_struct
id|signature_check
id|sigc
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sigc
comma
l_int|0
comma
r_sizeof
(paren
id|sigc
)paren
)paren
suffix:semicolon
id|len
op_assign
id|parse_signature
c_func
(paren
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
id|len
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|GPG_VERIFY_VERBOSE
)paren
id|write_in_full
c_func
(paren
l_int|1
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;no signature found&quot;
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|check_signature
c_func
(paren
id|buf
comma
id|len
comma
id|buf
op_plus
id|len
comma
id|size
id|len
comma
op_amp
id|sigc
)paren
suffix:semicolon
id|print_signature_buffer
c_func
(paren
op_amp
id|sigc
comma
id|flags
)paren
suffix:semicolon
id|signature_check_clear
c_func
(paren
op_amp
id|sigc
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|verify_tag
r_static
r_int
id|verify_tag
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|flags
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;tag &squot;%s&squot; not found.&quot;
comma
id|name
)paren
suffix:semicolon
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_TAG
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot verify a non-tag object of type %s.&quot;
comma
id|name
comma
r_typename
(paren
id|type
)paren
)paren
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: unable to read file.&quot;
comma
id|name
)paren
suffix:semicolon
id|ret
op_assign
id|run_gpg_verify
c_func
(paren
id|buf
comma
id|size
comma
id|flags
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|git_verify_tag_config
r_static
r_int
id|git_verify_tag_config
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
r_int
id|status
op_assign
id|git_gpg_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
r_return
id|status
suffix:semicolon
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
DECL|function|cmd_verify_tag
r_int
id|cmd_verify_tag
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
id|i
op_assign
l_int|1
comma
id|verbose
op_assign
l_int|0
comma
id|had_error
op_assign
l_int|0
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_const
r_struct
id|option
id|verify_tag_options
(braket
)braket
op_assign
(brace
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
comma
id|N_
c_func
(paren
l_string|&quot;print tag contents&quot;
)paren
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;raw&quot;
comma
op_amp
id|flags
comma
id|N_
c_func
(paren
l_string|&quot;print raw gpg status output&quot;
)paren
comma
id|GPG_VERIFY_RAW
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
id|git_verify_tag_config
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
id|verify_tag_options
comma
id|verify_tag_usage
comma
id|PARSE_OPT_KEEP_ARGV0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_le
id|i
)paren
id|usage_with_options
c_func
(paren
id|verify_tag_usage
comma
id|verify_tag_options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|flags
op_or_assign
id|GPG_VERIFY_VERBOSE
suffix:semicolon
multiline_comment|/* sometimes the program was terminated because this signal&n;&t; * was received in the process of writing the gpg input: */
id|signal
c_func
(paren
id|SIGPIPE
comma
id|SIG_IGN
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|argc
)paren
r_if
c_cond
(paren
id|verify_tag
c_func
(paren
id|argv
(braket
id|i
op_increment
)braket
comma
id|flags
)paren
)paren
id|had_error
op_assign
l_int|1
suffix:semicolon
r_return
id|had_error
suffix:semicolon
)brace
eof
