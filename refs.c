macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;ctype.h&gt;
multiline_comment|/* We allow &quot;recursive&quot; symbolic refs. Only within reason, though */
DECL|macro|MAXDEPTH
mdefine_line|#define MAXDEPTH 5
macro_line|#ifndef USE_SYMLINK_HEAD
DECL|macro|USE_SYMLINK_HEAD
mdefine_line|#define USE_SYMLINK_HEAD 1
macro_line|#endif
DECL|function|validate_symref
r_int
id|validate_symref
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_char
op_star
id|buf
comma
id|buffer
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|len
comma
id|fd
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
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Make sure it is a &quot;refs/..&quot; symlink */
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
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Anything else, just open it and try to see if it is a symbolic ref.&n;&t; */
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
l_int|1
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
multiline_comment|/*&n;&t; * Is it a symbolic ref?&n;&t; */
r_if
c_cond
(paren
id|len
OL
l_int|4
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;ref:&quot;
comma
id|buffer
comma
l_int|4
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|buf
op_assign
id|buffer
op_plus
l_int|4
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
id|buf
op_increment
comma
id|len
op_decrement
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
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
comma
r_int
id|reading
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
r_char
op_star
id|buf
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
multiline_comment|/* Special case: non-existing file.&n;&t;&t; * Not having the refs/heads/new-branch is OK&n;&t;&t; * if we are writing into it, so is .git/HEAD&n;&t;&t; * that points at refs/heads/master still to be&n;&t;&t; * born.  It is NOT OK if we are resolving for&n;&t;&t; * reading.&n;&t;&t; */
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
id|reading
op_logical_or
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
multiline_comment|/*&n;&t;&t; * Is it a symbolic ref?&n;&t;&t; */
r_if
c_cond
(paren
id|len
OL
l_int|4
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;ref:&quot;
comma
id|buffer
comma
l_int|4
)paren
)paren
r_break
suffix:semicolon
id|buf
op_assign
id|buffer
op_plus
l_int|4
suffix:semicolon
id|len
op_sub_assign
l_int|4
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
id|buf
op_increment
comma
id|len
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|isspace
c_func
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
)paren
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|path
op_assign
id|git_path
c_func
(paren
l_string|&quot;%.*s&quot;
comma
id|len
comma
id|buf
)paren
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
DECL|function|create_symref
r_int
id|create_symref
c_func
(paren
r_const
r_char
op_star
id|git_HEAD
comma
r_const
r_char
op_star
id|refs_heads_master
)paren
(brace
macro_line|#if USE_SYMLINK_HEAD
id|unlink
c_func
(paren
id|git_HEAD
)paren
suffix:semicolon
r_return
id|symlink
c_func
(paren
id|refs_heads_master
comma
id|git_HEAD
)paren
suffix:semicolon
macro_line|#else
r_const
r_char
op_star
id|lockpath
suffix:semicolon
r_char
id|ref
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|fd
comma
id|len
comma
id|written
suffix:semicolon
id|len
op_assign
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
l_string|&quot;ref: %s&bslash;n&quot;
comma
id|refs_heads_master
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|ref
)paren
op_le
id|len
)paren
(brace
id|error
c_func
(paren
l_string|&quot;refname too long: %s&quot;
comma
id|refs_heads_master
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|lockpath
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s.lock&quot;
comma
id|git_HEAD
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
id|written
op_assign
id|write
c_func
(paren
id|fd
comma
id|ref
comma
id|len
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
id|len
)paren
(brace
id|unlink
c_func
(paren
id|lockpath
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;Unable to write to %s&quot;
comma
id|lockpath
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lockpath
comma
id|git_HEAD
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
id|error
c_func
(paren
l_string|&quot;Unable to create %s&quot;
comma
id|git_HEAD
)paren
suffix:semicolon
r_return
l_int|3
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|read_ref
r_int
id|read_ref
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
r_if
c_cond
(paren
id|resolve_ref
c_func
(paren
id|filename
comma
id|sha1
comma
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
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
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|base
)paren
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
id|stat
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|path
)paren
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
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|path
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|read_ref
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
comma
id|sha1
)paren
)paren
r_return
id|fn
c_func
(paren
l_string|&quot;HEAD&quot;
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
l_string|&quot;refs&quot;
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
r_const
r_char
op_star
id|filename
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
id|git_path
c_func
(paren
l_string|&quot;refs/%s&quot;
comma
id|ref
)paren
suffix:semicolon
r_return
id|read_ref
c_func
(paren
id|filename
comma
id|sha1
)paren
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
id|read_ref
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
