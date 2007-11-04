multiline_comment|/*&n; * Builtin &quot;git tag&quot;&n; *&n; * Copyright (c) 2007 Kristian H&oslash;gsberg &lt;krh@redhat.com&gt;,&n; *                    Carlos Rica &lt;jasampler@gmail.com&gt;&n; * Based on git-tag.sh and mktag.c by Linus Torvalds.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;run-command.h&quot;
DECL|variable|builtin_tag_usage
r_static
r_const
r_char
id|builtin_tag_usage
(braket
)braket
op_assign
l_string|&quot;git-tag [-n [&lt;num&gt;]] -l [&lt;pattern&gt;] | [-a | -s | -u &lt;key-id&gt;] [-f | -d | -v] [-m &lt;msg&gt; | -F &lt;file&gt;] &lt;tagname&gt; [&lt;head&gt;]&quot;
suffix:semicolon
DECL|variable|signingkey
r_static
r_char
id|signingkey
(braket
l_int|1000
)braket
suffix:semicolon
DECL|function|launch_editor
r_static
r_void
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
)paren
(brace
r_const
r_char
op_star
id|editor
comma
op_star
id|terminal
suffix:semicolon
r_struct
id|child_process
id|child
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
l_int|3
)braket
suffix:semicolon
id|editor
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_EDITOR&quot;
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
id|terminal
op_assign
id|getenv
c_func
(paren
l_string|&quot;TERM&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|editor
op_logical_and
(paren
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
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Terminal is dumb but no VISUAL nor EDITOR defined.&bslash;n&quot;
l_string|&quot;Please supply the message using either -m or -F option.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
id|child.argv
op_assign
id|args
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
id|editor
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
id|path
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|run_command
c_func
(paren
op_amp
id|child
)paren
)paren
id|die
c_func
(paren
l_string|&quot;There was a problem with the editor %s.&quot;
comma
id|editor
)paren
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
id|die
c_func
(paren
l_string|&quot;could not read message file &squot;%s&squot;: %s&quot;
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
)brace
DECL|struct|tag_filter
r_struct
id|tag_filter
(brace
DECL|member|pattern
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|lines
r_int
id|lines
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PGP_SIGNATURE
mdefine_line|#define PGP_SIGNATURE &quot;-----BEGIN PGP SIGNATURE-----&quot;
DECL|function|show_reference
r_static
r_int
id|show_reference
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|tag_filter
op_star
id|filter
op_assign
id|cb_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|filter-&gt;pattern
comma
id|refname
comma
l_int|0
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|sp
comma
op_star
id|eol
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filter-&gt;lines
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%-15s &quot;
comma
id|refname
)paren
suffix:semicolon
id|sp
op_assign
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* skip header */
r_while
c_loop
(paren
id|sp
op_plus
l_int|1
OL
id|buf
op_plus
id|size
op_logical_and
op_logical_neg
(paren
id|sp
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|sp
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
id|sp
op_increment
suffix:semicolon
multiline_comment|/* only take up to &quot;lines&quot; lines, and strip the signature */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|sp
op_add_assign
l_int|2
suffix:semicolon
id|i
OL
id|filter-&gt;lines
op_logical_and
id|sp
OL
id|buf
op_plus
id|size
op_logical_and
id|prefixcmp
c_func
(paren
id|sp
comma
id|PGP_SIGNATURE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
id|printf
c_func
(paren
l_string|&quot;&bslash;n    &quot;
)paren
suffix:semicolon
id|eol
op_assign
id|memchr
c_func
(paren
id|sp
comma
l_char|&squot;&bslash;n&squot;
comma
id|size
(paren
id|sp
id|buf
)paren
)paren
suffix:semicolon
id|len
op_assign
id|eol
ques
c_cond
id|eol
id|sp
suffix:colon
id|size
(paren
id|sp
id|buf
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|sp
comma
id|len
comma
l_int|1
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eol
)paren
r_break
suffix:semicolon
id|sp
op_assign
id|eol
op_plus
l_int|1
suffix:semicolon
)brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|list_tags
r_static
r_int
id|list_tags
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_int
id|lines
)paren
(brace
r_struct
id|tag_filter
id|filter
suffix:semicolon
r_if
c_cond
(paren
id|pattern
op_eq
l_int|NULL
)paren
id|pattern
op_assign
l_string|&quot;*&quot;
suffix:semicolon
id|filter.pattern
op_assign
id|pattern
suffix:semicolon
id|filter.lines
op_assign
id|lines
suffix:semicolon
id|for_each_tag_ref
c_func
(paren
id|show_reference
comma
(paren
r_void
op_star
)paren
op_amp
id|filter
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|typedef|each_tag_name_fn
r_typedef
r_int
(paren
op_star
id|each_tag_name_fn
)paren
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
suffix:semicolon
DECL|function|for_each_tag_name
r_static
r_int
id|for_each_tag_name
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
comma
id|each_tag_name_fn
id|fn
)paren
(brace
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
r_char
id|ref
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|had_error
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|argv
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|ref
comma
r_sizeof
(paren
id|ref
)paren
comma
l_string|&quot;refs/tags/%s&quot;
comma
op_star
id|p
)paren
op_ge
r_sizeof
(paren
id|ref
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;tag name too long: %.*s...&quot;
comma
l_int|50
comma
op_star
id|p
)paren
suffix:semicolon
id|had_error
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;tag &squot;%s&squot; not found.&quot;
comma
op_star
id|p
)paren
suffix:semicolon
id|had_error
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fn
c_func
(paren
op_star
id|p
comma
id|ref
comma
id|sha1
)paren
)paren
id|had_error
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|had_error
suffix:semicolon
)brace
DECL|function|delete_tag
r_static
r_int
id|delete_tag
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|ref
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Deleted tag &squot;%s&squot;&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
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
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_const
r_char
op_star
id|argv_verify_tag
(braket
)braket
op_assign
(brace
l_string|&quot;git-verify-tag&quot;
comma
l_string|&quot;-v&quot;
comma
l_string|&quot;SHA1_HEX&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|argv_verify_tag
(braket
l_int|2
)braket
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|argv_verify_tag
comma
l_int|0
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not verify the tag &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_sign
r_static
r_int
id|do_sign
c_func
(paren
r_struct
id|strbuf
op_star
id|buffer
)paren
(brace
r_struct
id|child_process
id|gpg
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
l_int|4
)braket
suffix:semicolon
r_char
op_star
id|bracket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|signingkey
)paren
(brace
r_if
c_cond
(paren
id|strlcpy
c_func
(paren
id|signingkey
comma
id|git_committer_info
c_func
(paren
l_int|1
)paren
comma
r_sizeof
(paren
id|signingkey
)paren
)paren
OG
r_sizeof
(paren
id|signingkey
)paren
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;committer info too long.&quot;
)paren
suffix:semicolon
id|bracket
op_assign
id|strchr
c_func
(paren
id|signingkey
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bracket
)paren
id|bracket
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/* When the username signingkey is bad, program could be terminated&n;&t; * because gpg exits without reading and then write gets SIGPIPE. */
id|signal
c_func
(paren
id|SIGPIPE
comma
id|SIG_IGN
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|gpg
comma
l_int|0
comma
r_sizeof
(paren
id|gpg
)paren
)paren
suffix:semicolon
id|gpg.argv
op_assign
id|args
suffix:semicolon
id|gpg.in
op_assign
l_int|1
suffix:semicolon
id|gpg.out
op_assign
l_int|1
suffix:semicolon
id|args
(braket
l_int|0
)braket
op_assign
l_string|&quot;gpg&quot;
suffix:semicolon
id|args
(braket
l_int|1
)braket
op_assign
l_string|&quot;-bsau&quot;
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
id|signingkey
suffix:semicolon
id|args
(braket
l_int|3
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|gpg
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not run gpg.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|gpg.in
comma
id|buffer-&gt;buf
comma
id|buffer-&gt;len
)paren
op_ne
id|buffer-&gt;len
)paren
(brace
id|close
c_func
(paren
id|gpg.in
)paren
suffix:semicolon
id|finish_command
c_func
(paren
op_amp
id|gpg
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;gpg did not accept the tag data&quot;
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|gpg.in
)paren
suffix:semicolon
id|gpg.close_in
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|strbuf_read
c_func
(paren
id|buffer
comma
id|gpg.out
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|gpg
)paren
op_logical_or
op_logical_neg
id|len
op_logical_or
id|len
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;gpg failed to sign the tag&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not read the entire signature from gpg.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tag_template
r_static
r_const
r_char
id|tag_template
(braket
)braket
op_assign
l_string|&quot;&bslash;n&quot;
l_string|&quot;#&bslash;n&quot;
l_string|&quot;# Write a tag message&bslash;n&quot;
l_string|&quot;#&bslash;n&quot;
suffix:semicolon
DECL|function|git_tag_config
r_static
r_int
id|git_tag_config
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;user.signingkey&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
id|die
c_func
(paren
l_string|&quot;user.signingkey without value&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlcpy
c_func
(paren
id|signingkey
comma
id|value
comma
r_sizeof
(paren
id|signingkey
)paren
)paren
op_ge
r_sizeof
(paren
id|signingkey
)paren
)paren
id|die
c_func
(paren
l_string|&quot;user.signingkey value too long&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|write_tag_body
r_static
r_void
id|write_tag_body
c_func
(paren
r_int
id|fd
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|sp
comma
op_star
id|eob
suffix:semicolon
r_int
id|len
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
suffix:semicolon
multiline_comment|/* skip header */
id|sp
op_assign
id|strstr
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sp
op_logical_or
op_logical_neg
id|size
op_logical_or
id|type
op_ne
id|OBJ_TAG
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sp
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* skip the 2 LFs */
id|eob
op_assign
id|strstr
c_func
(paren
id|sp
comma
l_string|&quot;&bslash;n&quot;
id|PGP_SIGNATURE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eob
)paren
id|len
op_assign
id|eob
id|sp
suffix:semicolon
r_else
id|len
op_assign
id|buf
op_plus
id|size
id|sp
suffix:semicolon
id|write_or_die
c_func
(paren
id|fd
comma
id|sp
comma
id|len
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|create_tag
r_static
r_void
id|create_tag
c_func
(paren
r_const
r_int
r_char
op_star
id|object
comma
r_const
r_char
op_star
id|tag
comma
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|message
comma
r_int
id|sign
comma
r_int
r_char
op_star
id|prev
comma
r_int
r_char
op_star
id|result
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_char
id|header_buf
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|header_len
suffix:semicolon
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|object
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_le
id|OBJ_NONE
)paren
id|die
c_func
(paren
l_string|&quot;bad object type.&quot;
)paren
suffix:semicolon
id|header_len
op_assign
id|snprintf
c_func
(paren
id|header_buf
comma
r_sizeof
(paren
id|header_buf
)paren
comma
l_string|&quot;object %s&bslash;n&quot;
l_string|&quot;type %s&bslash;n&quot;
l_string|&quot;tag %s&bslash;n&quot;
l_string|&quot;tagger %s&bslash;n&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|object
)paren
comma
r_typename
(paren
id|type
)paren
comma
id|tag
comma
id|git_committer_info
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|header_len
OG
r_sizeof
(paren
id|header_buf
)paren
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;tag header too big.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|message
)paren
(brace
r_char
op_star
id|path
suffix:semicolon
r_int
id|fd
suffix:semicolon
multiline_comment|/* write the template message before editing: */
id|path
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;TAG_EDITMSG&quot;
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_CREAT
op_or
id|O_TRUNC
op_or
id|O_WRONLY
comma
l_int|0600
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;could not create file &squot;%s&squot;: %s&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|prev
)paren
)paren
id|write_tag_body
c_func
(paren
id|fd
comma
id|prev
)paren
suffix:semicolon
r_else
id|write_or_die
c_func
(paren
id|fd
comma
id|tag_template
comma
id|strlen
c_func
(paren
id|tag_template
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|launch_editor
c_func
(paren
id|path
comma
id|buf
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|path
)paren
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
id|stripspace
c_func
(paren
id|buf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|message
op_logical_and
op_logical_neg
id|buf-&gt;len
)paren
id|die
c_func
(paren
l_string|&quot;no tag message?&quot;
)paren
suffix:semicolon
id|strbuf_insert
c_func
(paren
id|buf
comma
l_int|0
comma
id|header_buf
comma
id|header_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sign
op_logical_and
id|do_sign
c_func
(paren
id|buf
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to sign the tag&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|buf-&gt;buf
comma
id|buf-&gt;len
comma
id|tag_type
comma
id|result
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to write tag file&quot;
)paren
suffix:semicolon
)brace
DECL|function|cmd_tag
r_int
id|cmd_tag
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
r_struct
id|strbuf
id|buf
suffix:semicolon
r_int
r_char
id|object
(braket
l_int|20
)braket
comma
id|prev
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|annotate
op_assign
l_int|0
comma
id|sign
op_assign
l_int|0
comma
id|force
op_assign
l_int|0
comma
id|lines
op_assign
l_int|0
comma
id|message
op_assign
l_int|0
suffix:semicolon
r_char
id|ref
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|object_ref
comma
op_star
id|tag
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
id|git_config
c_func
(paren
id|git_tag_config
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-a&quot;
)paren
)paren
(brace
id|annotate
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-s&quot;
)paren
)paren
(brace
id|annotate
op_assign
l_int|1
suffix:semicolon
id|sign
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|force
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_plus
l_int|1
op_eq
id|argc
op_logical_or
op_star
id|argv
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_char|&squot;-&squot;
)paren
multiline_comment|/* no argument */
id|lines
op_assign
l_int|1
suffix:semicolon
r_else
id|lines
op_assign
id|isdigit
c_func
(paren
op_star
id|argv
(braket
op_increment
id|i
)braket
)paren
ques
c_cond
id|atoi
c_func
(paren
id|argv
(braket
id|i
)braket
)paren
suffix:colon
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-m&quot;
)paren
)paren
(brace
id|annotate
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;option -m needs an argument.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
id|die
c_func
(paren
l_string|&quot;only one -F or -m option is allowed.&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|message
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-F&quot;
)paren
)paren
(brace
id|annotate
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;option -F needs an argument.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
id|die
c_func
(paren
l_string|&quot;only one -F or -m option is allowed.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|buf
comma
l_int|0
comma
l_int|1024
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;cannot read %s&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|strbuf_read_file
c_func
(paren
op_amp
id|buf
comma
id|argv
(braket
id|i
)braket
comma
l_int|1024
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;could not open or read &squot;%s&squot;: %s&quot;
comma
id|argv
(braket
id|i
)braket
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|message
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-u&quot;
)paren
)paren
(brace
id|annotate
op_assign
l_int|1
suffix:semicolon
id|sign
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;option -u needs an argument.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlcpy
c_func
(paren
id|signingkey
comma
id|argv
(braket
id|i
)braket
comma
r_sizeof
(paren
id|signingkey
)paren
)paren
op_ge
r_sizeof
(paren
id|signingkey
)paren
)paren
id|die
c_func
(paren
l_string|&quot;argument to option -u too long&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-l&quot;
)paren
)paren
r_return
id|list_tags
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
comma
id|lines
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-d&quot;
)paren
)paren
r_return
id|for_each_tag_name
c_func
(paren
id|argv
op_plus
id|i
op_plus
l_int|1
comma
id|delete_tag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-v&quot;
)paren
)paren
r_return
id|for_each_tag_name
c_func
(paren
id|argv
op_plus
id|i
op_plus
l_int|1
comma
id|verify_tag
)paren
suffix:semicolon
id|usage
c_func
(paren
id|builtin_tag_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
(brace
r_if
c_cond
(paren
id|annotate
)paren
id|usage
c_func
(paren
id|builtin_tag_usage
)paren
suffix:semicolon
r_return
id|list_tags
c_func
(paren
l_int|NULL
comma
id|lines
)paren
suffix:semicolon
)brace
id|tag
op_assign
id|argv
(braket
id|i
op_increment
)braket
suffix:semicolon
id|object_ref
op_assign
id|i
OL
id|argc
ques
c_cond
id|argv
(braket
id|i
)braket
suffix:colon
l_string|&quot;HEAD&quot;
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
l_int|1
OL
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;too many params&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|object_ref
comma
id|object
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Failed to resolve &squot;%s&squot; as a valid ref.&quot;
comma
id|object_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|ref
comma
r_sizeof
(paren
id|ref
)paren
comma
l_string|&quot;refs/tags/%s&quot;
comma
id|tag
)paren
OG
r_sizeof
(paren
id|ref
)paren
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;tag name too long: %.*s...&quot;
comma
l_int|50
comma
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|ref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid tag name.&quot;
comma
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|ref
comma
id|prev
comma
l_int|1
comma
l_int|NULL
)paren
)paren
id|hashclr
c_func
(paren
id|prev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
id|die
c_func
(paren
l_string|&quot;tag &squot;%s&squot; already exists&quot;
comma
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|annotate
)paren
id|create_tag
c_func
(paren
id|object
comma
id|tag
comma
op_amp
id|buf
comma
id|message
comma
id|sign
comma
id|prev
comma
id|object
)paren
suffix:semicolon
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref
comma
id|prev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
id|die
c_func
(paren
l_string|&quot;%s: cannot lock the ref&quot;
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|object
comma
l_int|NULL
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: cannot update the ref&quot;
comma
id|ref
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
