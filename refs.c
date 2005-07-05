macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;errno.h&gt;
DECL|function|read_ref
r_static
r_int
id|read_ref
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
id|ret
op_assign
l_int|1
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
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
r_char
id|buffer
(braket
l_int|60
)braket
suffix:semicolon
r_if
c_cond
(paren
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
)paren
op_ge
l_int|40
)paren
id|ret
op_assign
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_for_each_ref
r_static
r_int
id|do_for_each_ref
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_char
op_star
id|path
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
l_int|257
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|base
comma
l_string|&quot;./&quot;
comma
l_int|2
)paren
)paren
(brace
id|base
op_add_assign
l_int|2
suffix:semicolon
id|baselen
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|path
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baselen
op_logical_and
id|base
(braket
id|baselen
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|path
(braket
id|baselen
op_increment
)braket
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
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_continue
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
l_int|255
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|path
op_plus
id|baselen
comma
id|de-&gt;d_name
comma
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
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
r_continue
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
(brace
id|retval
op_assign
id|do_for_each_ref
c_func
(paren
id|path
comma
id|fn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_ref
c_func
(paren
id|path
comma
id|sha1
)paren
OL
l_int|0
)paren
r_continue
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
r_continue
suffix:semicolon
id|retval
op_assign
id|fn
c_func
(paren
id|path
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_break
suffix:semicolon
)brace
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|head_ref
r_int
id|head_ref
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
)paren
(brace
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
id|headpath
op_assign
id|git_path
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|read_ref
c_func
(paren
id|headpath
comma
id|sha1
)paren
)paren
r_return
id|fn
c_func
(paren
id|headpath
comma
id|sha1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|for_each_ref
r_int
id|for_each_ref
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
)paren
(brace
r_return
id|do_for_each_ref
c_func
(paren
id|get_refs_directory
c_func
(paren
)paren
comma
id|fn
)paren
suffix:semicolon
)brace
DECL|function|ref_file_name
r_static
r_char
op_star
id|ref_file_name
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_char
op_star
id|base
op_assign
id|get_refs_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_int
id|reflen
op_assign
id|strlen
c_func
(paren
id|ref
)paren
suffix:semicolon
r_char
op_star
id|ret
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
l_int|2
op_plus
id|reflen
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|ret
comma
l_string|&quot;%s/%s&quot;
comma
id|base
comma
id|ref
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ref_lock_file_name
r_static
r_char
op_star
id|ref_lock_file_name
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_char
op_star
id|base
op_assign
id|get_refs_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_int
id|reflen
op_assign
id|strlen
c_func
(paren
id|ref
)paren
suffix:semicolon
r_char
op_star
id|ret
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
l_int|7
op_plus
id|reflen
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|ret
comma
l_string|&quot;%s/%s.lock&quot;
comma
id|base
comma
id|ref
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|read_ref_file
r_static
r_int
id|read_ref_file
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t open %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|read
c_func
(paren
id|fd
comma
id|hex
comma
l_int|41
)paren
OL
l_int|41
)paren
op_logical_or
(paren
id|hex
(braket
l_int|40
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t read a hash from %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_ref_sha1
r_int
id|get_ref_sha1
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|filename
suffix:semicolon
r_int
id|retval
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
r_return
l_int|1
suffix:semicolon
id|filename
op_assign
id|ref_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|retval
op_assign
id|read_ref_file
c_func
(paren
id|filename
comma
id|sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|lock_ref_file
r_static
r_int
id|lock_ref_file
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_const
r_char
op_star
id|lock_filename
comma
r_const
r_int
r_char
op_star
id|old_sha1
)paren
(brace
r_int
id|fd
op_assign
id|open
c_func
(paren
id|lock_filename
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0666
)paren
suffix:semicolon
r_int
r_char
id|current_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t open lock file for %s: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|retval
op_assign
id|read_ref_file
c_func
(paren
id|filename
comma
id|current_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_sha1
)paren
(brace
r_if
c_cond
(paren
id|retval
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_filename
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Could not read the current value of %s&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|current_sha1
comma
id|old_sha1
comma
l_int|20
)paren
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_filename
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;The current value of %s is %s&quot;
comma
id|filename
comma
id|sha1_to_hex
c_func
(paren
id|current_sha1
)paren
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Expected %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|old_sha1
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock_filename
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Unexpectedly found a value of %s for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|current_sha1
)paren
comma
id|filename
)paren
suffix:semicolon
)brace
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|lock_ref_sha1
r_int
id|lock_ref_sha1
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|old_sha1
)paren
(brace
r_char
op_star
id|filename
suffix:semicolon
r_char
op_star
id|lock_filename
suffix:semicolon
r_int
id|retval
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
r_return
l_int|1
suffix:semicolon
id|filename
op_assign
id|ref_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|lock_filename
op_assign
id|ref_lock_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|retval
op_assign
id|lock_ref_file
c_func
(paren
id|filename
comma
id|lock_filename
comma
id|old_sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|filename
)paren
suffix:semicolon
id|free
c_func
(paren
id|lock_filename
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|write_ref_file
r_static
r_int
id|write_ref_file
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_const
r_char
op_star
id|lock_filename
comma
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
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_char
id|term
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|hex
comma
l_int|40
)paren
OL
l_int|40
op_logical_or
id|write
c_func
(paren
id|fd
comma
op_amp
id|term
comma
l_int|1
)paren
OL
l_int|1
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t write %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|rename
c_func
(paren
id|lock_filename
comma
id|filename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_ref_sha1
r_int
id|write_ref_sha1
c_func
(paren
r_const
r_char
op_star
id|ref
comma
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
r_char
op_star
id|filename
suffix:semicolon
r_char
op_star
id|lock_filename
suffix:semicolon
r_int
id|retval
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
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|ref
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|filename
op_assign
id|ref_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|lock_filename
op_assign
id|ref_lock_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|retval
op_assign
id|write_ref_file
c_func
(paren
id|filename
comma
id|lock_filename
comma
id|fd
comma
id|sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|filename
)paren
suffix:semicolon
id|free
c_func
(paren
id|lock_filename
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|check_ref_format
r_int
id|check_ref_format
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_char
op_star
id|middle
suffix:semicolon
r_if
c_cond
(paren
id|ref
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_or
id|ref
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|middle
op_assign
id|strchr
c_func
(paren
id|ref
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|middle
op_logical_or
op_logical_neg
id|middle
(braket
l_int|1
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|middle
op_plus
l_int|1
comma
l_char|&squot;/&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_ref_sha1_unlocked
r_int
id|write_ref_sha1_unlocked
c_func
(paren
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
r_char
op_star
id|filename
suffix:semicolon
r_char
op_star
id|lock_filename
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
id|retval
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
r_return
l_int|1
suffix:semicolon
id|filename
op_assign
id|ref_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|lock_filename
op_assign
id|ref_lock_file_name
c_func
(paren
id|ref
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|lock_filename
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
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
(brace
id|error
c_func
(paren
l_string|&quot;Writing %s&quot;
comma
id|lock_filename
)paren
suffix:semicolon
id|perror
c_func
(paren
l_string|&quot;Open&quot;
)paren
suffix:semicolon
)brace
id|retval
op_assign
id|write_ref_file
c_func
(paren
id|filename
comma
id|lock_filename
comma
id|fd
comma
id|sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|filename
)paren
suffix:semicolon
id|free
c_func
(paren
id|lock_filename
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
