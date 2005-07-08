macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
DECL|variable|upload_pack_usage
r_static
r_const
r_char
id|upload_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-upload-pack &lt;dir&gt;&quot;
suffix:semicolon
DECL|macro|MAX_HAS
mdefine_line|#define MAX_HAS (16)
DECL|macro|MAX_NEEDS
mdefine_line|#define MAX_NEEDS (256)
DECL|variable|nr_has
DECL|variable|nr_needs
r_static
r_int
id|nr_has
op_assign
l_int|0
comma
id|nr_needs
op_assign
l_int|0
suffix:semicolon
DECL|variable|has_sha1
r_static
r_int
r_char
id|has_sha1
(braket
id|MAX_HAS
)braket
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|needs_sha1
r_static
r_int
r_char
id|needs_sha1
(braket
id|MAX_NEEDS
)braket
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|strip
r_static
r_int
id|strip
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_logical_and
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|create_pack_file
r_static
r_void
id|create_pack_file
c_func
(paren
r_void
)paren
(brace
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fd
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to create pipe&quot;
)paren
suffix:semicolon
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to fork git-rev-list&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|args
op_assign
id|nr_has
op_plus
id|nr_needs
op_plus
l_int|5
suffix:semicolon
r_char
op_star
op_star
id|argv
op_assign
id|xmalloc
c_func
(paren
id|args
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|args
op_star
l_int|45
)paren
suffix:semicolon
r_char
op_star
op_star
id|p
op_assign
id|argv
suffix:semicolon
id|dup2
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_string|&quot;git-rev-list&quot;
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_string|&quot;--objects&quot;
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
id|nr_needs
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|p
op_increment
op_assign
id|buf
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|sha1_to_hex
c_func
(paren
id|needs_sha1
(braket
id|i
)braket
)paren
comma
l_int|41
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|41
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_has
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|p
op_increment
op_assign
id|buf
suffix:semicolon
op_star
id|buf
op_increment
op_assign
l_char|&squot;^&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|sha1_to_hex
c_func
(paren
id|has_sha1
(braket
id|i
)braket
)paren
comma
l_int|41
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|41
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
l_int|NULL
suffix:semicolon
id|execvp
c_func
(paren
l_string|&quot;git-rev-list&quot;
comma
id|argv
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to exec git-rev-list&quot;
)paren
suffix:semicolon
)brace
id|dup2
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;git-pack-objects&quot;
comma
l_string|&quot;git-pack-objects&quot;
comma
l_string|&quot;--stdout&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: unable to exec git-pack-objects&quot;
)paren
suffix:semicolon
)brace
DECL|function|got_sha1
r_static
r_int
id|got_sha1
c_func
(paren
r_char
op_star
id|hex
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: expected SHA1 object, got &squot;%s&squot;&quot;
comma
id|hex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|nr
op_assign
id|nr_has
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
id|MAX_HAS
)paren
(brace
id|memcpy
c_func
(paren
id|has_sha1
(braket
id|nr
)braket
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|nr_has
op_assign
id|nr
op_plus
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_common_commits
r_static
r_int
id|get_common_commits
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NAK&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|len
op_assign
id|strip
c_func
(paren
id|line
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;have &quot;
comma
l_int|5
)paren
)paren
(brace
r_if
c_cond
(paren
id|got_sha1
c_func
(paren
id|line
op_plus
l_int|5
comma
id|sha1
)paren
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|line
comma
l_string|&quot;done&quot;
)paren
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NAK&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;git-upload-pack: expected SHA1 list, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|strip
c_func
(paren
id|line
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;have &quot;
comma
l_int|5
)paren
)paren
(brace
id|got_sha1
c_func
(paren
id|line
op_plus
l_int|5
comma
id|sha1
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
id|line
comma
l_string|&quot;done&quot;
)paren
)paren
r_break
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-upload-pack: expected SHA1 list, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|receive_needs
r_static
r_int
id|receive_needs
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|len
comma
id|needs
suffix:semicolon
id|needs
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
id|needs
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This is purely theoretical right now: git-fetch-pack only&n;&t;&t; * ever asks for a single HEAD&n;&t;&t; */
r_if
c_cond
(paren
id|needs
op_ge
id|MAX_NEEDS
)paren
id|die
c_func
(paren
l_string|&quot;I&squot;m only doing a max of %d requests&quot;
comma
id|MAX_NEEDS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;want &quot;
comma
id|line
comma
l_int|5
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|5
comma
id|needs_sha1
(braket
id|needs
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: protocol error, expected to get sha, not &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
id|needs
op_increment
suffix:semicolon
)brace
)brace
DECL|function|send_ref
r_static
r_int
id|send_ref
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
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|upload_pack
r_static
r_int
id|upload_pack
c_func
(paren
r_void
)paren
(brace
id|head_ref
c_func
(paren
id|send_ref
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|send_ref
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|nr_needs
op_assign
id|receive_needs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_needs
)paren
r_return
l_int|0
suffix:semicolon
id|get_common_commits
c_func
(paren
)paren
suffix:semicolon
id|create_pack_file
c_func
(paren
)paren
suffix:semicolon
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
r_const
r_char
op_star
id|dir
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage
c_func
(paren
id|upload_pack_usage
)paren
suffix:semicolon
id|dir
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* chdir to the directory. If that fails, try appending &quot;.git&quot; */
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|dir
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s.git&quot;
comma
id|dir
)paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack unable to chdir to %s&quot;
comma
id|dir
)paren
suffix:semicolon
)brace
id|chdir
c_func
(paren
l_string|&quot;.git&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
l_string|&quot;objects&quot;
comma
id|X_OK
)paren
op_logical_or
id|access
c_func
(paren
l_string|&quot;refs&quot;
comma
id|X_OK
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-upload-pack: %s doesn&squot;t seem to be a git archive&quot;
comma
id|dir
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;GIT_DIR&quot;
comma
l_string|&quot;.&quot;
comma
l_int|1
)paren
suffix:semicolon
id|upload_pack
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
