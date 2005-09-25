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
DECL|macro|MAXDEPTH
mdefine_line|#define MAXDEPTH 5
DECL|function|resolve_ref
r_const
r_char
op_star
id|resolve_ref
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
id|sha1
)paren
(brace
r_int
id|depth
op_assign
id|MAXDEPTH
comma
id|len
suffix:semicolon
r_char
id|buffer
(braket
l_int|256
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|depth
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Special case: non-existing file */
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sha1
comma
l_int|0
comma
l_int|20
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
multiline_comment|/* Follow &quot;normalized&quot; - ie &quot;refs/..&quot; symlinks by hand */
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|len
op_assign
id|readlink
c_func
(paren
id|path
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|5
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;refs/&quot;
comma
id|buffer
comma
l_int|5
)paren
)paren
(brace
id|path
op_assign
id|git_path
c_func
(paren
l_string|&quot;%.*s&quot;
comma
id|len
comma
id|buffer
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Anything else, just open it and try to use it as&n;&t;&t; * a ref&n;&t;&t; */
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|len
op_assign
id|read
c_func
(paren
id|fd
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
l_int|40
op_logical_or
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|path
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
comma
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
l_string|&quot;Ref %s changed to %s&quot;
comma
id|refname
comma
id|sha1_to_hex
c_func
(paren
id|currsha1
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
multiline_comment|/*&n;&t; * FIXME!&n;&t; *&n;&t; * We should re-read the old ref here, and re-verify that it&n;&t; * matches &quot;oldsha1&quot;. Otherwise there&squot;s a small race.&n;&t; */
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
