macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|git_update_ref_usage
r_static
r_const
r_char
id|git_update_ref_usage
(braket
)braket
op_assign
l_string|&quot;git-update-ref &lt;refname&gt; &lt;value&gt; [&lt;oldval&gt;]&quot;
suffix:semicolon
DECL|function|re_verify
r_static
r_int
id|re_verify
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_char
op_star
id|oldsha1
comma
r_int
r_char
op_star
id|currsha1
)paren
(brace
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDONLY
)paren
comma
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|nr
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
l_int|40
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
id|nr
op_ne
l_int|40
op_logical_or
id|get_sha1_hex
c_func
(paren
id|buf
comma
id|currsha1
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|memcmp
c_func
(paren
id|oldsha1
comma
id|currsha1
comma
l_int|20
)paren
ques
c_cond
l_int|1
suffix:colon
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
r_char
op_star
id|hex
suffix:semicolon
r_const
r_char
op_star
id|refname
comma
op_star
id|value
comma
op_star
id|oldval
comma
op_star
id|path
suffix:semicolon
r_char
op_star
id|lockpath
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|oldsha1
(braket
l_int|20
)braket
comma
id|currsha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|fd
comma
id|written
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|4
)paren
id|usage
c_func
(paren
id|git_update_ref_usage
)paren
suffix:semicolon
id|refname
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|value
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
id|oldval
op_assign
id|argv
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|value
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: not a valid SHA1&quot;
comma
id|value
)paren
suffix:semicolon
id|memset
c_func
(paren
id|oldsha1
comma
l_int|0
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldval
op_logical_and
id|get_sha1
c_func
(paren
id|oldval
comma
id|oldsha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: not a valid old SHA1&quot;
comma
id|oldval
)paren
suffix:semicolon
id|path
op_assign
id|resolve_ref
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|refname
)paren
comma
id|currsha1
comma
op_logical_neg
op_logical_neg
id|oldval
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|die
c_func
(paren
l_string|&quot;No such ref: %s&quot;
comma
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldval
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|currsha1
comma
id|oldsha1
comma
l_int|20
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Ref %s is at %s but expected %s&quot;
comma
id|refname
comma
id|sha1_to_hex
c_func
(paren
id|currsha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|oldsha1
)paren
)paren
suffix:semicolon
multiline_comment|/* Nothing to do? */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|oldsha1
comma
id|sha1
comma
l_int|20
)paren
)paren
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|path
op_assign
id|strdup
c_func
(paren
id|path
)paren
suffix:semicolon
id|lockpath
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s.lock&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories
c_func
(paren
id|lockpath
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unable to create all of %s&quot;
comma
id|lockpath
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|lockpath
comma
id|O_CREAT
op_or
id|O_EXCL
op_or
id|O_WRONLY
comma
l_int|0666
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
l_string|&quot;Unable to create %s&quot;
comma
id|lockpath
)paren
suffix:semicolon
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|hex
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|written
op_assign
id|write
c_func
(paren
id|fd
comma
id|hex
comma
l_int|41
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
id|written
op_ne
l_int|41
)paren
(brace
id|unlink
c_func
(paren
id|lockpath
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Unable to write to %s&quot;
comma
id|lockpath
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Re-read the ref after getting the lock to verify&n;&t; */
r_if
c_cond
(paren
id|oldval
op_logical_and
id|re_verify
c_func
(paren
id|path
comma
id|oldsha1
comma
id|currsha1
)paren
OL
l_int|0
)paren
(brace
id|unlink
c_func
(paren
id|lockpath
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Ref lock failed&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Finally, replace the old ref with the new one&n;&t; */
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lockpath
comma
id|path
)paren
OL
l_int|0
)paren
(brace
id|unlink
c_func
(paren
id|lockpath
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Unable to create %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
