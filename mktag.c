macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
multiline_comment|/*&n; * A signature file has a very simple fixed format: four lines&n; * of &quot;object &lt;sha1&gt;&quot; + &quot;type &lt;typename&gt;&quot; + &quot;tag &lt;tagname&gt;&quot; +&n; * &quot;tagger &lt;committer&gt;&quot;, followed by a blank line, a free-form tag&n; * message and a signature block that git itself doesn&squot;t care about,&n; * but that can be verified with gpg or similar.&n; *&n; * The first four lines are guaranteed to be at least 83 bytes:&n; * &quot;object &lt;sha1&gt;&bslash;n&quot; is 48 bytes, &quot;type tag&bslash;n&quot; at 9 bytes is the&n; * shortest possible type-line, &quot;tag .&bslash;n&quot; at 6 bytes is the shortest&n; * single-character-tag line, and &quot;tagger . &lt;&gt; 0 +0000&bslash;n&quot; at 20 bytes is&n; * the shortest possible tagger-line.&n; */
multiline_comment|/*&n; * We refuse to tag something we can&squot;t verify. Just because.&n; */
DECL|function|verify_object
r_static
r_int
id|verify_object
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|expected_type
)paren
(brace
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|buffer
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
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|type_from_string
c_func
(paren
id|expected_type
)paren
)paren
id|ret
op_assign
id|check_sha1_signature
c_func
(paren
id|sha1
comma
id|buffer
comma
id|size
comma
id|expected_type
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef NO_C99_FORMAT
DECL|macro|PD_FMT
mdefine_line|#define PD_FMT &quot;%d&quot;
macro_line|#else
DECL|macro|PD_FMT
mdefine_line|#define PD_FMT &quot;%td&quot;
macro_line|#endif
DECL|function|verify_tag
r_static
r_int
id|verify_tag
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|typelen
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|object
comma
op_star
id|type_line
comma
op_star
id|tag_line
comma
op_star
id|tagger_line
comma
op_star
id|lb
comma
op_star
id|rb
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|84
)paren
r_return
id|error
c_func
(paren
l_string|&quot;wanna fool me ? you obviously got the size wrong !&quot;
)paren
suffix:semicolon
id|buffer
(braket
id|size
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Verify object line */
id|object
op_assign
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|object
comma
l_string|&quot;object &quot;
comma
l_int|7
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char%d: does not start with &bslash;&quot;object &bslash;&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|object
op_plus
l_int|7
comma
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char%d: could not get SHA1 hash&quot;
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* Verify type line */
id|type_line
op_assign
id|object
op_plus
l_int|48
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|type_line
l_int|1
comma
l_string|&quot;&bslash;ntype &quot;
comma
l_int|6
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char%d: could not find &bslash;&quot;&bslash;&bslash;ntype &bslash;&quot;&quot;
comma
l_int|47
)paren
suffix:semicolon
multiline_comment|/* Verify tag-line */
id|tag_line
op_assign
id|strchr
c_func
(paren
id|type_line
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tag_line
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: could not find next &bslash;&quot;&bslash;&bslash;n&bslash;&quot;&quot;
comma
id|type_line
id|buffer
)paren
suffix:semicolon
id|tag_line
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|tag_line
comma
l_string|&quot;tag &quot;
comma
l_int|4
)paren
op_logical_or
id|tag_line
(braket
l_int|4
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: no &bslash;&quot;tag &bslash;&quot; found&quot;
comma
id|tag_line
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Get the actual type */
id|typelen
op_assign
id|tag_line
id|type_line
id|strlen
c_func
(paren
l_string|&quot;type &bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|typelen
op_ge
r_sizeof
(paren
id|type
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: type too long&quot;
comma
id|type_line
op_plus
l_int|5
id|buffer
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|type
comma
id|type_line
op_plus
l_int|5
comma
id|typelen
)paren
suffix:semicolon
id|type
(braket
id|typelen
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Verify that the object matches */
r_if
c_cond
(paren
id|verify_object
c_func
(paren
id|sha1
comma
id|type
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char%d: could not verify object %s&quot;
comma
l_int|7
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
multiline_comment|/* Verify the tag-name: we don&squot;t allow control characters or spaces in it */
id|tag_line
op_add_assign
l_int|4
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|tag_line
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: could not verify tag name&quot;
comma
id|tag_line
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* Verify the tagger line */
id|tagger_line
op_assign
id|tag_line
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|tagger_line
comma
l_string|&quot;tagger &quot;
comma
l_int|7
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: could not find &bslash;&quot;tagger &bslash;&quot;&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check for correct form for name and email&n;&t; * i.e. &quot; &lt;&quot; followed by &quot;&gt; &quot; on _this_ line&n;&t; * No angle brackets within the name or email address fields.&n;&t; * No spaces within the email address field.&n;&t; */
id|tagger_line
op_add_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|lb
op_assign
id|strstr
c_func
(paren
id|tagger_line
comma
l_string|&quot; &lt;&quot;
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|rb
op_assign
id|strstr
c_func
(paren
id|lb
op_plus
l_int|2
comma
l_string|&quot;&gt; &quot;
)paren
)paren
op_logical_or
id|strpbrk
c_func
(paren
id|tagger_line
comma
l_string|&quot;&lt;&gt;&bslash;n&quot;
)paren
op_ne
id|lb
op_plus
l_int|1
op_logical_or
id|strpbrk
c_func
(paren
id|lb
op_plus
l_int|2
comma
l_string|&quot;&gt;&lt;&bslash;n &quot;
)paren
op_ne
id|rb
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: malformed tagger field&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Check for author name, at least one character, space is acceptable */
r_if
c_cond
(paren
id|lb
op_eq
id|tagger_line
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: missing tagger name&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
multiline_comment|/* timestamp, 1 or more digits followed by space */
id|tagger_line
op_assign
id|rb
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|len
op_assign
id|strspn
c_func
(paren
id|tagger_line
comma
l_string|&quot;0123456789&quot;
)paren
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: missing tag timestamp&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
id|tagger_line
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_star
id|tagger_line
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: malformed tag timestamp&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
id|tagger_line
op_increment
suffix:semicolon
multiline_comment|/* timezone, 5 digits [+-]hhmm, max. 1400 */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|tagger_line
(braket
l_int|0
)braket
op_eq
l_char|&squot;+&squot;
op_logical_or
id|tagger_line
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
op_logical_and
id|strspn
c_func
(paren
id|tagger_line
op_plus
l_int|1
comma
l_string|&quot;0123456789&quot;
)paren
op_eq
l_int|4
op_logical_and
id|tagger_line
(braket
l_int|5
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|atoi
c_func
(paren
id|tagger_line
op_plus
l_int|1
)paren
op_le
l_int|1400
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: malformed tag timezone&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
id|tagger_line
op_add_assign
l_int|6
suffix:semicolon
multiline_comment|/* Verify the blank line separating the header from the body */
r_if
c_cond
(paren
op_star
id|tagger_line
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;char&quot;
id|PD_FMT
l_string|&quot;: trailing garbage in tag header&quot;
comma
id|tagger_line
id|buffer
)paren
suffix:semicolon
multiline_comment|/* The actual stuff afterwards we don&squot;t care about.. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PD_FMT
macro_line|#undef PD_FMT
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
r_int
r_char
id|result_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage
c_func
(paren
l_string|&quot;git-mktag &lt; signaturefile&quot;
)paren
suffix:semicolon
id|setup_git_directory
c_func
(paren
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
id|strbuf_read
c_func
(paren
op_amp
id|buf
comma
l_int|0
comma
l_int|4096
)paren
OL
l_int|0
)paren
(brace
id|die
c_func
(paren
l_string|&quot;could not read from stdin&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Verify it for some basic sanity: it needs to start with&n;&t;   &quot;object &lt;sha1&gt;&bslash;ntype&bslash;ntagger &quot; */
r_if
c_cond
(paren
id|verify_tag
c_func
(paren
id|buf.buf
comma
id|buf.len
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;invalid tag signature file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|buf.buf
comma
id|buf.len
comma
id|tag_type
comma
id|result_sha1
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
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|result_sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
