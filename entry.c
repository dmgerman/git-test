macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|function|create_directories
r_static
r_void
id|create_directories
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|checkout
op_star
id|state
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_const
r_char
op_star
id|slash
op_assign
id|path
suffix:semicolon
r_while
c_loop
(paren
(paren
id|slash
op_assign
id|strchr
c_func
(paren
id|slash
op_plus
l_int|1
comma
l_char|&squot;/&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|len
op_assign
id|slash
id|path
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|buf
comma
l_int|0777
)paren
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EEXIST
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|state-&gt;base_dir_len
op_logical_and
id|state-&gt;force
op_logical_and
op_logical_neg
id|unlink
c_func
(paren
id|buf
)paren
op_logical_and
op_logical_neg
id|mkdir
c_func
(paren
id|buf
comma
l_int|0777
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|buf
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* ok */
)brace
id|die
c_func
(paren
l_string|&quot;cannot create directory at %s&quot;
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|remove_subtree
r_static
r_void
id|remove_subtree
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_char
id|pathbuf
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
id|die
c_func
(paren
l_string|&quot;cannot opendir %s&quot;
comma
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|pathbuf
comma
id|path
)paren
suffix:semicolon
id|name
op_assign
id|pathbuf
op_plus
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
op_star
id|name
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
id|de-&gt;d_name
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
)paren
)paren
r_continue
suffix:semicolon
id|strcpy
c_func
(paren
id|name
comma
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|pathbuf
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot lstat %s&quot;
comma
id|pathbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
id|remove_subtree
c_func
(paren
id|pathbuf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|pathbuf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot unlink %s&quot;
comma
id|pathbuf
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rmdir
c_func
(paren
id|path
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot rmdir %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|create_file
r_static
r_int
id|create_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|mode
comma
r_int
id|force
)paren
(brace
r_int
id|fd
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_amp
l_int|0100
)paren
ques
c_cond
l_int|0777
suffix:colon
l_int|0666
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_WRONLY
op_or
id|O_TRUNC
op_or
id|O_CREAT
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EISDIR
op_logical_and
id|force
)paren
(brace
id|remove_subtree
c_func
(paren
id|path
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_WRONLY
op_or
id|O_TRUNC
op_or
id|O_CREAT
comma
id|mode
)paren
suffix:semicolon
)brace
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|write_entry
r_static
r_int
id|write_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_const
r_char
op_star
id|path
comma
r_struct
id|checkout
op_star
id|state
)paren
(brace
r_int
id|fd
suffix:semicolon
r_void
op_star
r_new
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|wrote
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|target
(braket
l_int|1024
)braket
suffix:semicolon
r_new
op_assign
id|read_sha1_file
c_func
(paren
id|ce-&gt;sha1
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
op_logical_neg
r_new
op_logical_or
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;blob&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
r_new
)paren
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;git-checkout-cache: unable to read sha1 file of %s (%s)&quot;
comma
id|path
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFREG
suffix:colon
id|fd
op_assign
id|create_file
c_func
(paren
id|path
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|state-&gt;force
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;git-checkout-cache: unable to create file %s (%s)&quot;
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
id|wrote
op_assign
id|write
c_func
(paren
id|fd
comma
r_new
comma
id|size
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wrote
op_ne
id|size
)paren
r_return
id|error
c_func
(paren
l_string|&quot;git-checkout-cache: unable to write file %s&quot;
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|memcpy
c_func
(paren
id|target
comma
r_new
comma
id|size
)paren
suffix:semicolon
id|target
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|symlink
c_func
(paren
id|target
comma
id|path
)paren
)paren
(brace
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;git-checkout-cache: unable to create symlink %s (%s)&quot;
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
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;git-checkout-cache: unknown file mode for %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;refresh_cache
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
suffix:semicolon
id|fill_stat_cache_info
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|checkout_entry
r_int
id|checkout_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_struct
id|checkout
op_star
id|state
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_static
r_char
id|path
(braket
id|MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|len
op_assign
id|state-&gt;base_dir_len
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|state-&gt;base_dir
comma
id|len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
id|ce-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
)paren
(brace
r_int
id|changed
op_assign
id|ce_match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;force
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;quiet
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git-checkout-cache: %s already exists&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We unlink the old file, to get the new one with the&n;&t;&t; * right permissions (including umask, which is nasty&n;&t;&t; * to emulate by hand - much easier to let the system&n;&t;&t; * just do the right thing)&n;&t;&t; */
id|unlink
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|state-&gt;not_new
)paren
r_return
l_int|0
suffix:semicolon
id|create_directories
c_func
(paren
id|path
comma
id|state
)paren
suffix:semicolon
r_return
id|write_entry
c_func
(paren
id|ce
comma
id|path
comma
id|state
)paren
suffix:semicolon
)brace
eof
