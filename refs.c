macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;errno.h&gt;
multiline_comment|/* We allow &quot;recursive&quot; symbolic refs. Only within reason, though */
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
macro_line|#ifndef NO_SYMLINK_HEAD
r_if
c_cond
(paren
id|prefer_symlink_refs
)paren
(brace
id|unlink
c_func
(paren
id|git_HEAD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|symlink
c_func
(paren
id|refs_heads_master
comma
id|git_HEAD
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;no symlink - falling back to symbolic ref&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
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
comma
r_int
id|trim
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
comma
id|trim
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
(brace
id|error
c_func
(paren
l_string|&quot;%s points nowhere!&quot;
comma
id|path
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
(brace
id|error
c_func
(paren
l_string|&quot;%s does not point to a valid &quot;
l_string|&quot;commit object!&quot;
comma
id|path
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|retval
op_assign
id|fn
c_func
(paren
id|path
op_plus
id|trim
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
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|for_each_tag_ref
r_int
id|for_each_tag_ref
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
l_string|&quot;refs/tags&quot;
comma
id|fn
comma
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|for_each_branch_ref
r_int
id|for_each_branch_ref
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
l_string|&quot;refs/heads&quot;
comma
id|fn
comma
l_int|11
)paren
suffix:semicolon
)brace
DECL|function|for_each_remote_ref
r_int
id|for_each_remote_ref
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
l_string|&quot;refs/remotes&quot;
comma
id|fn
comma
l_int|13
)paren
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
r_return
id|read_ref
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs/%s&quot;
comma
id|ref
)paren
comma
id|sha1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make sure &quot;ref&quot; is something reasonable to have under &quot;.git/refs/&quot;;&n; * We do not like it if:&n; *&n; * - any path component of it begins with &quot;.&quot;, or&n; * - it has double dots &quot;..&quot;, or&n; * - it has ASCII control character, &quot;~&quot;, &quot;^&quot;, &quot;:&quot; or SP, anywhere, or&n; * - it ends with a &quot;/&quot;.&n; */
DECL|function|bad_ref_char
r_static
r_inline
r_int
id|bad_ref_char
c_func
(paren
r_int
id|ch
)paren
(brace
r_return
(paren
(paren
(paren
r_int
)paren
id|ch
)paren
op_le
l_char|&squot; &squot;
op_logical_or
id|ch
op_eq
l_char|&squot;~&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;^&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;:&squot;
op_logical_or
multiline_comment|/* 2.13 Pattern Matching Notation */
id|ch
op_eq
l_char|&squot;?&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;*&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;[&squot;
)paren
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
r_int
id|ch
comma
id|level
suffix:semicolon
r_const
r_char
op_star
id|cp
op_assign
id|ref
suffix:semicolon
id|level
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
op_increment
)paren
op_eq
l_char|&squot;/&squot;
)paren
suffix:semicolon
multiline_comment|/* tolerate duplicated slashes */
r_if
c_cond
(paren
op_logical_neg
id|ch
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* should not end with slashes */
multiline_comment|/* we are at the beginning of the path component */
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;.&squot;
op_logical_or
id|bad_ref_char
c_func
(paren
id|ch
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* scan the rest of the path component */
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|bad_ref_char
c_func
(paren
id|ch
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;/&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;.&squot;
op_logical_and
op_star
id|cp
op_eq
l_char|&squot;.&squot;
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|level
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch
)paren
(brace
r_if
c_cond
(paren
id|level
OL
l_int|2
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* at least of form &quot;heads/blah&quot; */
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|verify_lock
r_static
r_struct
id|ref_lock
op_star
id|verify_lock
c_func
(paren
r_struct
id|ref_lock
op_star
id|lock
comma
r_const
r_int
r_char
op_star
id|old_sha1
comma
r_int
id|mustexist
)paren
(brace
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
r_int
id|nr
comma
id|fd
op_assign
id|open
c_func
(paren
id|lock-&gt;ref_file
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
op_logical_and
(paren
id|mustexist
op_logical_or
id|errno
op_ne
id|ENOENT
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Can&squot;t verify ref %s&quot;
comma
id|lock-&gt;ref_file
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
id|lock-&gt;old_sha1
)paren
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Can&squot;t verify ref %s&quot;
comma
id|lock-&gt;ref_file
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|lock-&gt;old_sha1
comma
id|old_sha1
comma
l_int|20
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Ref %s is at %s but expected %s&quot;
comma
id|lock-&gt;ref_file
comma
id|sha1_to_hex
c_func
(paren
id|lock-&gt;old_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|old_sha1
)paren
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|lock
suffix:semicolon
)brace
DECL|function|lock_ref_sha1_basic
r_static
r_struct
id|ref_lock
op_star
id|lock_ref_sha1_basic
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|plen
comma
r_const
r_int
r_char
op_star
id|old_sha1
comma
r_int
id|mustexist
)paren
(brace
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
id|lock
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|ref_lock
)paren
)paren
suffix:semicolon
id|lock-&gt;lock_fd
op_assign
l_int|1
suffix:semicolon
id|plen
op_assign
id|strlen
c_func
(paren
id|path
)paren
id|plen
suffix:semicolon
id|path
op_assign
id|resolve_ref
c_func
(paren
id|path
comma
id|lock-&gt;old_sha1
comma
id|mustexist
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Can&squot;t read ref %s&quot;
comma
id|path
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|lock-&gt;ref_file
op_assign
id|strdup
c_func
(paren
id|path
)paren
suffix:semicolon
id|lock-&gt;lock_file
op_assign
id|strdup
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s.lock&quot;
comma
id|lock-&gt;ref_file
)paren
)paren
suffix:semicolon
id|lock-&gt;log_file
op_assign
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;logs/%s&quot;
comma
id|lock-&gt;ref_file
op_plus
id|plen
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories
c_func
(paren
id|lock-&gt;lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to create directory for %s&quot;
comma
id|lock-&gt;lock_file
)paren
suffix:semicolon
id|lock-&gt;lock_fd
op_assign
id|open
c_func
(paren
id|lock-&gt;lock_file
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
id|lock-&gt;lock_fd
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t open lock file %s: %s&quot;
comma
id|lock-&gt;lock_file
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|old_sha1
ques
c_cond
id|verify_lock
c_func
(paren
id|lock
comma
id|old_sha1
comma
id|mustexist
)paren
suffix:colon
id|lock
suffix:semicolon
)brace
DECL|function|lock_ref_sha1
r_struct
id|ref_lock
op_star
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
comma
r_int
id|mustexist
)paren
(brace
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
l_int|NULL
suffix:semicolon
r_return
id|lock_ref_sha1_basic
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs/%s&quot;
comma
id|ref
)paren
comma
id|strlen
c_func
(paren
id|ref
)paren
comma
id|old_sha1
comma
id|mustexist
)paren
suffix:semicolon
)brace
DECL|function|lock_any_ref_for_update
r_struct
id|ref_lock
op_star
id|lock_any_ref_for_update
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
comma
r_int
id|mustexist
)paren
(brace
r_return
id|lock_ref_sha1_basic
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|ref
)paren
comma
id|strlen
c_func
(paren
id|ref
)paren
comma
id|old_sha1
comma
id|mustexist
)paren
suffix:semicolon
)brace
DECL|function|unlock_ref
r_void
id|unlock_ref
(paren
r_struct
id|ref_lock
op_star
id|lock
)paren
(brace
r_if
c_cond
(paren
id|lock-&gt;lock_fd
op_ge
l_int|0
)paren
(brace
id|close
c_func
(paren
id|lock-&gt;lock_fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|lock-&gt;lock_file
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lock-&gt;ref_file
)paren
id|free
c_func
(paren
id|lock-&gt;ref_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock-&gt;lock_file
)paren
id|free
c_func
(paren
id|lock-&gt;lock_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock-&gt;log_file
)paren
id|free
c_func
(paren
id|lock-&gt;log_file
)paren
suffix:semicolon
id|free
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|function|log_ref_write
r_static
r_int
id|log_ref_write
c_func
(paren
r_struct
id|ref_lock
op_star
id|lock
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|msg
)paren
(brace
r_int
id|logfd
comma
id|written
comma
id|oflags
op_assign
id|O_APPEND
op_or
id|O_WRONLY
suffix:semicolon
r_int
id|maxlen
comma
id|len
suffix:semicolon
r_char
op_star
id|logrec
suffix:semicolon
r_const
r_char
op_star
id|comitter
suffix:semicolon
r_if
c_cond
(paren
id|log_all_ref_updates
)paren
(brace
r_if
c_cond
(paren
id|safe_create_leading_directories
c_func
(paren
id|lock-&gt;log_file
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to create directory for %s&quot;
comma
id|lock-&gt;log_file
)paren
suffix:semicolon
id|oflags
op_or_assign
id|O_CREAT
suffix:semicolon
)brace
id|logfd
op_assign
id|open
c_func
(paren
id|lock-&gt;log_file
comma
id|oflags
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|logfd
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|log_all_ref_updates
op_logical_and
id|errno
op_eq
id|ENOENT
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Unable to append to %s: %s&quot;
comma
id|lock-&gt;log_file
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
id|comitter
op_assign
id|git_committer_info
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
(brace
id|maxlen
op_assign
id|strlen
c_func
(paren
id|comitter
)paren
op_plus
id|strlen
c_func
(paren
id|msg
)paren
op_plus
l_int|2
op_star
l_int|40
op_plus
l_int|5
suffix:semicolon
id|logrec
op_assign
id|xmalloc
c_func
(paren
id|maxlen
)paren
suffix:semicolon
id|len
op_assign
id|snprintf
c_func
(paren
id|logrec
comma
id|maxlen
comma
l_string|&quot;%s %s %s&bslash;t%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|lock-&gt;old_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|comitter
comma
id|msg
)paren
suffix:semicolon
)brace
r_else
(brace
id|maxlen
op_assign
id|strlen
c_func
(paren
id|comitter
)paren
op_plus
l_int|2
op_star
l_int|40
op_plus
l_int|4
suffix:semicolon
id|logrec
op_assign
id|xmalloc
c_func
(paren
id|maxlen
)paren
suffix:semicolon
id|len
op_assign
id|snprintf
c_func
(paren
id|logrec
comma
id|maxlen
comma
l_string|&quot;%s %s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|lock-&gt;old_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|comitter
)paren
suffix:semicolon
)brace
id|written
op_assign
id|len
op_le
id|maxlen
ques
c_cond
id|write
c_func
(paren
id|logfd
comma
id|logrec
comma
id|len
)paren
suffix:colon
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|logrec
)paren
suffix:semicolon
id|close
c_func
(paren
id|logfd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
op_ne
id|len
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Unable to append to %s&quot;
comma
id|lock-&gt;log_file
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
r_struct
id|ref_lock
op_star
id|lock
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|logmsg
)paren
(brace
r_static
r_char
id|term
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|lock-&gt;old_sha1
comma
id|sha1
comma
l_int|20
)paren
)paren
(brace
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
c_func
(paren
id|lock-&gt;lock_fd
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
op_ne
l_int|40
op_logical_or
id|write
c_func
(paren
id|lock-&gt;lock_fd
comma
op_amp
id|term
comma
l_int|1
)paren
op_ne
l_int|1
op_logical_or
id|close
c_func
(paren
id|lock-&gt;lock_fd
)paren
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t write %s&quot;
comma
id|lock-&gt;lock_file
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|log_ref_write
c_func
(paren
id|lock
comma
id|sha1
comma
id|logmsg
)paren
OL
l_int|0
)paren
(brace
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lock-&gt;lock_file
comma
id|lock-&gt;ref_file
)paren
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t set %s&quot;
comma
id|lock-&gt;ref_file
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|lock-&gt;lock_fd
op_assign
l_int|1
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
