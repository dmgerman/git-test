multiline_comment|/*&n; * Builtin &quot;git tag&quot;&n; *&n; * Copyright (c) 2007 Kristian H&oslash;gsberg &lt;krh@redhat.com&gt;,&n; *                    Carlos Rica &lt;jasampler@gmail.com&gt;&n; * Based on git-tag.sh and mktag.c by Linus Torvalds.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|git_tag_usage
r_static
r_const
r_char
op_star
r_const
id|git_tag_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git tag [-a|-s|-u &lt;key-id&gt;] [-f] [-m &lt;msg&gt;|-F &lt;file&gt;] &lt;tagname&gt; [&lt;head&gt;]&quot;
comma
l_string|&quot;git tag -d &lt;tagname&gt;...&quot;
comma
l_string|&quot;git tag -l [-n[&lt;num&gt;]] [&lt;pattern&gt;]&quot;
comma
l_string|&quot;git tag -v &lt;tagname&gt;...&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|signingkey
r_static
r_char
id|signingkey
(braket
l_int|1000
)braket
suffix:semicolon
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
op_logical_or
op_logical_neg
id|size
)paren
r_return
l_int|0
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
comma
l_int|0
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
r_int
id|i
comma
id|j
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
id|IDENT_ERROR_ON_NO_NAME
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
id|close
c_func
(paren
id|gpg.out
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
id|close
c_func
(paren
id|gpg.out
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
multiline_comment|/* Strip CR from the line endings, in case we are on Windows. */
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|buffer-&gt;len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|buffer-&gt;buf
(braket
id|i
)braket
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|j
)paren
id|buffer-&gt;buf
(braket
id|j
)braket
op_assign
id|buffer-&gt;buf
(braket
id|i
)braket
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
id|strbuf_setlen
c_func
(paren
id|buffer
comma
id|j
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
DECL|function|set_signingkey
r_static
r_void
id|set_signingkey
c_func
(paren
r_const
r_char
op_star
id|value
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
l_string|&quot;signing key value too long (%.10s...)&quot;
comma
id|value
)paren
suffix:semicolon
)brace
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
comma
r_void
op_star
id|cb
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
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|set_signingkey
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
DECL|function|build_tag_object
r_static
r_int
id|build_tag_object
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|sign
comma
r_int
r_char
op_star
id|result
)paren
(brace
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
r_return
id|error
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
r_return
id|error
c_func
(paren
l_string|&quot;unable to write tag file&quot;
)paren
suffix:semicolon
r_return
l_int|0
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
r_char
op_star
id|path
op_assign
l_int|NULL
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
id|IDENT_ERROR_ON_NO_NAME
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
r_int
id|fd
suffix:semicolon
multiline_comment|/* write the template message before editing: */
id|path
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;TAG_EDITMSG&quot;
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
r_if
c_cond
(paren
id|launch_editor
c_func
(paren
id|path
comma
id|buf
comma
l_int|NULL
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Please supply the message using either -m or -F option.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
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
id|build_tag_object
c_func
(paren
id|buf
comma
id|sign
comma
id|result
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|path
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;The tag message has been left in %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
m_exit
(paren
l_int|128
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path
)paren
(brace
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
)brace
DECL|struct|msg_arg
r_struct
id|msg_arg
(brace
DECL|member|given
r_int
id|given
suffix:semicolon
DECL|member|buf
r_struct
id|strbuf
id|buf
suffix:semicolon
)brace
suffix:semicolon
DECL|function|parse_msg_arg
r_static
r_int
id|parse_msg_arg
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|msg_arg
op_star
id|msg
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;buf.len
)paren
id|strbuf_addstr
c_func
(paren
op_amp
(paren
id|msg-&gt;buf
)paren
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
(paren
id|msg-&gt;buf
)paren
comma
id|arg
)paren
suffix:semicolon
id|msg-&gt;given
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
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
r_struct
id|ref_lock
op_star
id|lock
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
l_int|1
comma
id|list
op_assign
l_int|0
comma
r_delete
op_assign
l_int|0
comma
id|verify
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|msgfile
op_assign
l_int|NULL
comma
op_star
id|keyid
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|msg_arg
id|msg
op_assign
(brace
l_int|0
comma
id|STRBUF_INIT
)brace
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;l&squot;
comma
l_int|NULL
comma
op_amp
id|list
comma
l_string|&quot;list tag names&quot;
)paren
comma
(brace
id|OPTION_INTEGER
comma
l_char|&squot;n&squot;
comma
l_int|NULL
comma
op_amp
id|lines
comma
l_int|NULL
comma
l_string|&quot;print n lines of each tag message&quot;
comma
id|PARSE_OPT_OPTARG
comma
l_int|NULL
comma
l_int|1
)brace
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
r_delete
comma
l_string|&quot;delete tags&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;v&squot;
comma
l_int|NULL
comma
op_amp
id|verify
comma
l_string|&quot;verify tags&quot;
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Tag creation options&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;a&squot;
comma
l_int|NULL
comma
op_amp
id|annotate
comma
l_string|&quot;annotated tag, needs a message&quot;
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_char|&squot;m&squot;
comma
l_int|NULL
comma
op_amp
id|msg
comma
l_string|&quot;msg&quot;
comma
l_string|&quot;message for the tag&quot;
comma
id|parse_msg_arg
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;F&squot;
comma
l_int|NULL
comma
op_amp
id|msgfile
comma
l_string|&quot;file&quot;
comma
l_string|&quot;message in a file&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;s&squot;
comma
l_int|NULL
comma
op_amp
id|sign
comma
l_string|&quot;annotated and GPG-signed tag&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;u&squot;
comma
l_int|NULL
comma
op_amp
id|keyid
comma
l_string|&quot;key-id&quot;
comma
l_string|&quot;use another key to sign the tag&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_int|NULL
comma
op_amp
id|force
comma
l_string|&quot;replace the tag if exists&quot;
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
id|git_tag_config
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
id|options
comma
id|git_tag_usage
comma
l_int|0
)paren
suffix:semicolon
id|msgfile
op_assign
id|parse_options_fix_filename
c_func
(paren
id|prefix
comma
id|msgfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|keyid
)paren
(brace
id|sign
op_assign
l_int|1
suffix:semicolon
id|set_signingkey
c_func
(paren
id|keyid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sign
)paren
id|annotate
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
op_logical_and
op_logical_neg
(paren
r_delete
op_logical_or
id|verify
)paren
)paren
id|list
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|annotate
op_logical_or
id|msg.given
op_logical_or
id|msgfile
op_logical_or
id|force
)paren
op_logical_and
(paren
id|list
op_logical_or
r_delete
op_logical_or
id|verify
)paren
)paren
id|usage_with_options
c_func
(paren
id|git_tag_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list
op_plus
r_delete
op_plus
id|verify
OG
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|git_tag_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list
)paren
r_return
id|list_tags
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|lines
op_eq
l_int|1
ques
c_cond
l_int|0
suffix:colon
id|lines
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lines
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;-n option is only allowed with -l.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
r_delete
)paren
r_return
id|for_each_tag_name
c_func
(paren
id|argv
comma
id|delete_tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify
)paren
r_return
id|for_each_tag_name
c_func
(paren
id|argv
comma
id|verify_tag
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
r_if
c_cond
(paren
id|msg.given
op_logical_or
id|msgfile
)paren
(brace
r_if
c_cond
(paren
id|msg.given
op_logical_and
id|msgfile
)paren
id|die
c_func
(paren
l_string|&quot;only one -F or -m option is allowed.&quot;
)paren
suffix:semicolon
id|annotate
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|msg.given
)paren
id|strbuf_addbuf
c_func
(paren
op_amp
id|buf
comma
op_amp
(paren
id|msg.buf
)paren
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|msgfile
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
id|msgfile
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
id|msgfile
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
id|msgfile
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
id|tag
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|object_ref
op_assign
id|argc
op_eq
l_int|2
ques
c_cond
id|argv
(braket
l_int|1
)braket
suffix:colon
l_string|&quot;HEAD&quot;
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|2
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
id|msg.given
op_logical_or
id|msgfile
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
