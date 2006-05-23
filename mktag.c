macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
multiline_comment|/*&n; * A signature file has a very simple fixed format: three lines&n; * of &quot;object &lt;sha1&gt;&quot; + &quot;type &lt;typename&gt;&quot; + &quot;tag &lt;tagname&gt;&quot;,&n; * followed by some free-form signature that git itself doesn&squot;t&n; * care about, but that can be verified with gpg or similar.&n; *&n; * The first three lines are guaranteed to be at least 63 bytes:&n; * &quot;object &lt;sha1&gt;&bslash;n&quot; is 48 bytes, &quot;type tag&bslash;n&quot; at 9 bytes is the&n; * shortest possible type-line, and &quot;tag .&bslash;n&quot; at 6 bytes is the&n; * shortest single-character-tag line. &n; *&n; * We also artificially limit the size of the full object to 8kB.&n; * Just because I&squot;m a lazy bastard, and if you can&squot;t fit a signature&n; * in that size, you&squot;re doing something wrong.&n; */
singleline_comment|// Some random size
DECL|macro|MAXSIZE
mdefine_line|#define MAXSIZE (8192)
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
r_char
id|type
(braket
l_int|100
)braket
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
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
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
id|type
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
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|64
)paren
r_return
l_int|1
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
l_int|1
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
l_int|1
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
l_int|1
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
l_int|1
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
l_int|1
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
l_int|1
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
l_int|1
suffix:semicolon
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
l_int|1
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
l_int|1
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
l_string|&quot;tagger&quot;
comma
l_int|6
)paren
op_logical_or
(paren
id|tagger_line
(braket
l_int|6
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* The actual stuff afterwards we don&squot;t care about.. */
r_return
l_int|0
suffix:semicolon
)brace
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
r_int
r_int
id|size
op_assign
l_int|4096
suffix:semicolon
r_char
op_star
id|buffer
op_assign
id|malloc
c_func
(paren
id|size
)paren
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
l_string|&quot;cat &lt;signaturefile&gt; | git-mktag&quot;
)paren
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_pipe
c_func
(paren
l_int|0
comma
op_amp
id|buffer
comma
op_amp
id|size
)paren
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;could not read from stdin&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// Verify it for some basic sanity: it needs to start with &quot;object &lt;sha1&gt;&bslash;ntype&bslash;ntagger &quot;
r_if
c_cond
(paren
id|verify_tag
c_func
(paren
id|buffer
comma
id|size
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
id|buffer
comma
id|size
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
id|free
c_func
(paren
id|buffer
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
