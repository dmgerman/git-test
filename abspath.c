macro_line|#include &quot;cache.h&quot;
multiline_comment|/*&n; * Do not use this for inspecting *tracked* content.  When path is a&n; * symlink to a directory, we do not want to say it is a directory when&n; * dealing with tracked content in the working tree.&n; */
DECL|function|is_directory
r_int
id|is_directory
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
r_return
(paren
op_logical_neg
id|stat
c_func
(paren
id|path
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
suffix:semicolon
)brace
multiline_comment|/* We allow &quot;recursive&quot; symbolic links. Only within reason, though. */
DECL|macro|MAXDEPTH
mdefine_line|#define MAXDEPTH 5
multiline_comment|/*&n; * Return the real path (i.e., absolute path, with symlinks resolved&n; * and extra slashes removed) equivalent to the specified path.  (If&n; * you want an absolute path but don&squot;t mind links, use&n; * absolute_path().)  The return value is a pointer to a static&n; * buffer.&n; *&n; * The input and all intermediate paths must be shorter than MAX_PATH.&n; * The directory part of path (i.e., everything up to the last&n; * dir_sep) must denote a valid, existing directory, but the last&n; * component need not exist.  If die_on_error is set, then die with an&n; * informative error message if there is a problem.  Otherwise, return&n; * NULL on errors (without generating any output).&n; *&n; * If path is our buffer, then return path, as it&squot;s already what the&n; * user wants.&n; */
DECL|function|real_path_internal
r_static
r_const
r_char
op_star
id|real_path_internal
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|die_on_error
)paren
(brace
r_static
r_char
id|bufs
(braket
l_int|2
)braket
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
comma
op_star
id|buf
op_assign
id|bufs
(braket
l_int|0
)braket
comma
op_star
id|next_buf
op_assign
id|bufs
(braket
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * If we have to temporarily chdir(), store the original CWD&n;&t; * here so that we can chdir() back to it at the end of the&n;&t; * function:&n;&t; */
r_char
id|cwd
(braket
l_int|1024
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
id|buf_index
op_assign
l_int|1
suffix:semicolon
r_int
id|depth
op_assign
id|MAXDEPTH
suffix:semicolon
r_char
op_star
id|last_elem
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
multiline_comment|/* We&squot;ve already done it */
r_if
c_cond
(paren
id|path
op_eq
id|buf
op_logical_or
id|path
op_eq
id|next_buf
)paren
r_return
id|path
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die
c_func
(paren
l_string|&quot;The empty string is not a valid path&quot;
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlcpy
c_func
(paren
id|buf
comma
id|path
comma
id|PATH_MAX
)paren
op_ge
id|PATH_MAX
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die
c_func
(paren
l_string|&quot;Too long path: %.*s&quot;
comma
l_int|60
comma
id|path
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
r_while
c_loop
(paren
id|depth
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_directory
c_func
(paren
id|buf
)paren
)paren
(brace
r_char
op_star
id|last_slash
op_assign
id|find_last_dir_sep
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_slash
)paren
(brace
id|last_elem
op_assign
id|xstrdup
c_func
(paren
id|last_slash
op_plus
l_int|1
)paren
suffix:semicolon
id|last_slash
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
(brace
id|last_elem
op_assign
id|xstrdup
c_func
(paren
id|buf
)paren
suffix:semicolon
op_star
id|buf
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|cwd
op_logical_and
op_logical_neg
id|getcwd
c_func
(paren
id|cwd
comma
r_sizeof
(paren
id|cwd
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die_errno
c_func
(paren
l_string|&quot;Could not get current working directory&quot;
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|buf
)paren
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die_errno
c_func
(paren
l_string|&quot;Could not switch to &squot;%s&squot;&quot;
comma
id|buf
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|getcwd
c_func
(paren
id|buf
comma
id|PATH_MAX
)paren
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die_errno
c_func
(paren
l_string|&quot;Could not get current working directory&quot;
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_elem
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|strlen
c_func
(paren
id|last_elem
)paren
op_plus
l_int|2
OG
id|PATH_MAX
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die
c_func
(paren
l_string|&quot;Too long path name: &squot;%s/%s&squot;&quot;
comma
id|buf
comma
id|last_elem
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_logical_and
op_logical_neg
id|is_dir_sep
c_func
(paren
id|buf
(braket
id|len
l_int|1
)braket
)paren
)paren
id|buf
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
op_plus
id|len
comma
id|last_elem
)paren
suffix:semicolon
id|free
c_func
(paren
id|last_elem
)paren
suffix:semicolon
id|last_elem
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|buf
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISLNK
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|ssize_t
id|len
op_assign
id|readlink
c_func
(paren
id|buf
comma
id|next_buf
comma
id|PATH_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die_errno
c_func
(paren
l_string|&quot;Invalid symlink &squot;%s&squot;&quot;
comma
id|buf
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PATH_MAX
op_le
id|len
)paren
(brace
r_if
c_cond
(paren
id|die_on_error
)paren
id|die
c_func
(paren
l_string|&quot;symbolic link too long: %s&quot;
comma
id|buf
)paren
suffix:semicolon
r_else
r_goto
id|error_out
suffix:semicolon
)brace
id|next_buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|buf
op_assign
id|next_buf
suffix:semicolon
id|buf_index
op_assign
l_int|1
id|buf_index
suffix:semicolon
id|next_buf
op_assign
id|bufs
(braket
id|buf_index
)braket
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|retval
op_assign
id|buf
suffix:semicolon
id|error_out
suffix:colon
id|free
c_func
(paren
id|last_elem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cwd
op_logical_and
id|chdir
c_func
(paren
id|cwd
)paren
)paren
id|die_errno
(paren
l_string|&quot;Could not change back to &squot;%s&squot;&quot;
comma
id|cwd
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|real_path
r_const
r_char
op_star
id|real_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_return
id|real_path_internal
c_func
(paren
id|path
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|real_path_if_valid
r_const
r_char
op_star
id|real_path_if_valid
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_return
id|real_path_internal
c_func
(paren
id|path
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|get_pwd_cwd
r_static
r_const
r_char
op_star
id|get_pwd_cwd
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|cwd
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|pwd
suffix:semicolon
r_struct
id|stat
id|cwd_stat
comma
id|pwd_stat
suffix:semicolon
r_if
c_cond
(paren
id|getcwd
c_func
(paren
id|cwd
comma
id|PATH_MAX
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|pwd
op_assign
id|getenv
c_func
(paren
l_string|&quot;PWD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pwd
op_logical_and
id|strcmp
c_func
(paren
id|pwd
comma
id|cwd
)paren
)paren
(brace
id|stat
c_func
(paren
id|cwd
comma
op_amp
id|cwd_stat
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cwd_stat.st_dev
op_logical_or
id|cwd_stat.st_ino
)paren
op_logical_and
op_logical_neg
id|stat
c_func
(paren
id|pwd
comma
op_amp
id|pwd_stat
)paren
op_logical_and
id|pwd_stat.st_dev
op_eq
id|cwd_stat.st_dev
op_logical_and
id|pwd_stat.st_ino
op_eq
id|cwd_stat.st_ino
)paren
(brace
id|strlcpy
c_func
(paren
id|cwd
comma
id|pwd
comma
id|PATH_MAX
)paren
suffix:semicolon
)brace
)brace
r_return
id|cwd
suffix:semicolon
)brace
multiline_comment|/*&n; * Use this to get an absolute path from a relative one. If you want&n; * to resolve links, you should use real_path.&n; *&n; * If the path is already absolute, then return path. As the user is&n; * never meant to free the return value, we&squot;re safe.&n; */
DECL|function|absolute_path
r_const
r_char
op_star
id|absolute_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_static
r_char
id|buf
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|path
)paren
(brace
id|die
c_func
(paren
l_string|&quot;The empty string is not a valid path&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|path
)paren
)paren
(brace
r_if
c_cond
(paren
id|strlcpy
c_func
(paren
id|buf
comma
id|path
comma
id|PATH_MAX
)paren
op_ge
id|PATH_MAX
)paren
id|die
c_func
(paren
l_string|&quot;Too long path: %.*s&quot;
comma
l_int|60
comma
id|path
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|fmt
suffix:semicolon
r_const
r_char
op_star
id|cwd
op_assign
id|get_pwd_cwd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cwd
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot determine the current working directory&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|cwd
)paren
suffix:semicolon
id|fmt
op_assign
(paren
id|len
OG
l_int|0
op_logical_and
id|is_dir_sep
c_func
(paren
id|cwd
(braket
id|len
l_int|1
)braket
)paren
)paren
ques
c_cond
l_string|&quot;%s%s&quot;
suffix:colon
l_string|&quot;%s/%s&quot;
suffix:semicolon
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|buf
comma
id|PATH_MAX
comma
id|fmt
comma
id|cwd
comma
id|path
)paren
op_ge
id|PATH_MAX
)paren
id|die
c_func
(paren
l_string|&quot;Too long path: %.*s&quot;
comma
l_int|60
comma
id|path
)paren
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; * Unlike prefix_path, this should be used if the named file does&n; * not have to interact with index entry; i.e. name of a random file&n; * on the filesystem.&n; */
DECL|function|prefix_filename
r_const
r_char
op_star
id|prefix_filename
c_func
(paren
r_const
r_char
op_star
id|pfx
comma
r_int
id|pfx_len
comma
r_const
r_char
op_star
id|arg
)paren
(brace
r_static
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
macro_line|#ifndef GIT_WINDOWS_NATIVE
r_if
c_cond
(paren
op_logical_neg
id|pfx_len
op_logical_or
id|is_absolute_path
c_func
(paren
id|arg
)paren
)paren
r_return
id|arg
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|pfx
comma
id|pfx_len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|pfx_len
comma
id|arg
)paren
suffix:semicolon
macro_line|#else
r_char
op_star
id|p
suffix:semicolon
multiline_comment|/* don&squot;t add prefix to absolute paths, but still replace &squot;&bslash;&squot; by &squot;/&squot; */
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|arg
)paren
)paren
id|pfx_len
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pfx_len
)paren
id|memcpy
c_func
(paren
id|path
comma
id|pfx
comma
id|pfx_len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|pfx_len
comma
id|arg
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|path
op_plus
id|pfx_len
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
op_star
id|p
op_assign
l_char|&squot;/&squot;
suffix:semicolon
macro_line|#endif
r_return
id|path
suffix:semicolon
)brace
eof
