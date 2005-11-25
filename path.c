multiline_comment|/*&n; * I&squot;m tired of doing &quot;vsnprintf()&quot; etc just to open a&n; * file, so here&squot;s a &quot;return static buffer with printf&quot;&n; * interface for paths.&n; *&n; * It&squot;s obviously not thread-safe. Sue me. But it&squot;s quite&n; * useful for doing things like&n; *&n; *   f = open(mkpath(&quot;%s/%s.git&quot;, base, name), O_RDONLY);&n; *&n; * which is what it&squot;s designed for.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;pwd.h&gt;
DECL|variable|pathname
r_static
r_char
id|pathname
(braket
id|PATH_MAX
)braket
suffix:semicolon
DECL|variable|bad_path
r_static
r_char
id|bad_path
(braket
)braket
op_assign
l_string|&quot;/bad-path/&quot;
suffix:semicolon
DECL|function|cleanup_path
r_static
r_char
op_star
id|cleanup_path
c_func
(paren
r_char
op_star
id|path
)paren
(brace
multiline_comment|/* Clean it up */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|path
comma
l_string|&quot;./&quot;
comma
l_int|2
)paren
)paren
(brace
id|path
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
op_star
id|path
op_eq
l_char|&squot;/&squot;
)paren
id|path
op_increment
suffix:semicolon
)brace
r_return
id|path
suffix:semicolon
)brace
DECL|function|mkpath
r_char
op_star
id|mkpath
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|len
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|pathname
comma
id|PATH_MAX
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|PATH_MAX
)paren
r_return
id|bad_path
suffix:semicolon
r_return
id|cleanup_path
c_func
(paren
id|pathname
)paren
suffix:semicolon
)brace
DECL|function|git_path
r_char
op_star
id|git_path
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_const
r_char
op_star
id|git_dir
op_assign
id|get_git_dir
c_func
(paren
)paren
suffix:semicolon
id|va_list
id|args
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|git_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|PATH_MAX
op_minus
l_int|100
)paren
r_return
id|bad_path
suffix:semicolon
id|memcpy
c_func
(paren
id|pathname
comma
id|git_dir
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|git_dir
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|pathname
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|len
op_add_assign
id|vsnprintf
c_func
(paren
id|pathname
op_plus
id|len
comma
id|PATH_MAX
id|len
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|PATH_MAX
)paren
r_return
id|bad_path
suffix:semicolon
r_return
id|cleanup_path
c_func
(paren
id|pathname
)paren
suffix:semicolon
)brace
multiline_comment|/* git_mkstemp() - create tmp file honoring TMPDIR variable */
DECL|function|git_mkstemp
r_int
id|git_mkstemp
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|len
comma
r_const
r_char
op_star
r_template
)paren
(brace
r_char
op_star
id|env
comma
op_star
id|pch
op_assign
id|path
suffix:semicolon
r_if
c_cond
(paren
(paren
id|env
op_assign
id|getenv
c_func
(paren
l_string|&quot;TMPDIR&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|strcpy
c_func
(paren
id|pch
comma
l_string|&quot;/tmp/&quot;
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|5
suffix:semicolon
id|pch
op_add_assign
l_int|5
suffix:semicolon
)brace
r_else
(brace
r_int
id|n
op_assign
id|snprintf
c_func
(paren
id|pch
comma
id|len
comma
l_string|&quot;%s/&quot;
comma
id|env
)paren
suffix:semicolon
id|len
op_sub_assign
id|n
suffix:semicolon
id|pch
op_add_assign
id|n
suffix:semicolon
)brace
id|safe_strncpy
c_func
(paren
id|pch
comma
r_template
comma
id|len
)paren
suffix:semicolon
r_return
id|mkstemp
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
DECL|function|safe_strncpy
r_char
op_star
id|safe_strncpy
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
comma
r_int
id|n
)paren
(brace
id|strncpy
c_func
(paren
id|dest
comma
id|src
comma
id|n
)paren
suffix:semicolon
id|dest
(braket
id|n
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
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
id|buf
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
DECL|function|current_dir
r_static
r_char
op_star
id|current_dir
c_func
(paren
r_void
)paren
(brace
r_return
id|getcwd
c_func
(paren
id|pathname
comma
r_sizeof
(paren
id|pathname
)paren
)paren
suffix:semicolon
)brace
DECL|function|user_chdir
r_static
r_int
id|user_chdir
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_char
op_star
id|dir
op_assign
id|path
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dir
op_eq
l_char|&squot;~&squot;
)paren
(brace
multiline_comment|/* user-relative path */
r_struct
id|passwd
op_star
id|pw
suffix:semicolon
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
id|dir
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|dir
op_increment
suffix:semicolon
multiline_comment|/* &squot;~/&squot; and &squot;~&squot; (no slash) means users own home-dir */
r_if
c_cond
(paren
op_logical_neg
op_star
id|dir
op_logical_or
op_star
id|dir
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|pw
op_assign
id|getpwuid
c_func
(paren
id|getuid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|slash
)paren
(brace
op_star
id|slash
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|pw
op_assign
id|getpwnam
c_func
(paren
id|dir
)paren
suffix:semicolon
op_star
id|slash
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_else
id|pw
op_assign
id|getpwnam
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
multiline_comment|/* make sure we got something back that we can chdir() to */
r_if
c_cond
(paren
op_logical_neg
id|pw
op_logical_or
id|chdir
c_func
(paren
id|pw-&gt;pw_dir
)paren
OL
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|slash
op_logical_or
op_logical_neg
id|slash
(braket
l_int|1
)braket
)paren
(brace
multiline_comment|/* no path following username */
r_return
l_int|0
suffix:semicolon
)brace
id|dir
op_assign
id|slash
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ~foo/path/to/repo is now path/to/repo and we&squot;re in foo&squot;s homedir */
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
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|enter_repo
r_char
op_star
id|enter_repo
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|strict
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strict
)paren
(brace
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|path
)paren
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|path
)paren
suffix:semicolon
multiline_comment|/* happy -- no chdir */
r_else
r_if
c_cond
(paren
op_logical_neg
id|user_chdir
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
multiline_comment|/* happy -- as given */
r_else
r_if
c_cond
(paren
op_logical_neg
id|user_chdir
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s.git&quot;
comma
id|path
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* happy -- uemacs --&gt; uemacs.git */
r_else
r_return
l_int|NULL
suffix:semicolon
(paren
r_void
)paren
id|chdir
c_func
(paren
l_string|&quot;.git&quot;
)paren
suffix:semicolon
)brace
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
op_eq
l_int|0
op_logical_and
id|access
c_func
(paren
l_string|&quot;refs&quot;
comma
id|X_OK
)paren
op_eq
l_int|0
op_logical_and
id|validate_symref
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|putenv
c_func
(paren
l_string|&quot;GIT_DIR=.&quot;
)paren
suffix:semicolon
id|check_repository_format
c_func
(paren
)paren
suffix:semicolon
r_return
id|current_dir
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
eof
