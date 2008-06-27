multiline_comment|/*&n; * I&squot;m tired of doing &quot;vsnprintf()&quot; etc just to open a&n; * file, so here&squot;s a &quot;return static buffer with printf&quot;&n; * interface for paths.&n; *&n; * It&squot;s obviously not thread-safe. Sue me. But it&squot;s quite&n; * useful for doing things like&n; *&n; *   f = open(mkpath(&quot;%s/%s.git&quot;, base, name), O_RDONLY);&n; *&n; * which is what it&squot;s designed for.&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|bad_path
r_static
r_char
id|bad_path
(braket
)braket
op_assign
l_string|&quot;/bad-path/&quot;
suffix:semicolon
DECL|function|get_pathname
r_static
r_char
op_star
id|get_pathname
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|pathname_array
(braket
l_int|4
)braket
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_static
r_int
id|index
suffix:semicolon
r_return
id|pathname_array
(braket
l_int|3
op_amp
op_increment
id|index
)braket
suffix:semicolon
)brace
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
r_char
op_star
id|pathname
op_assign
id|get_pathname
c_func
(paren
)paren
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
r_char
op_star
id|pathname
op_assign
id|get_pathname
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
r_const
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|n
suffix:semicolon
id|tmp
op_assign
id|getenv
c_func
(paren
l_string|&quot;TMPDIR&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
id|tmp
op_assign
l_string|&quot;/tmp&quot;
suffix:semicolon
id|n
op_assign
id|snprintf
c_func
(paren
id|path
comma
id|len
comma
l_string|&quot;%s/%s&quot;
comma
id|tmp
comma
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|n
)paren
(brace
id|errno
op_assign
id|ENAMETOOLONG
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|mkstemp
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
DECL|function|validate_headref
r_int
id|validate_headref
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|ssize_t
id|len
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
id|read_in_full
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
l_string|&quot;ref:&quot;
comma
id|buffer
comma
l_int|4
)paren
)paren
(brace
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
)brace
multiline_comment|/*&n;&t; * Is this a detached HEAD?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|user_path
r_static
r_char
op_star
id|user_path
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|path
comma
r_int
id|sz
)paren
(brace
r_struct
id|passwd
op_star
id|pw
suffix:semicolon
r_char
op_star
id|slash
suffix:semicolon
r_int
id|len
comma
id|baselen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
id|path
(braket
l_int|0
)braket
op_ne
l_char|&squot;~&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
id|path
op_increment
suffix:semicolon
id|slash
op_assign
id|strchr
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
op_logical_neg
id|path
(braket
l_int|0
)braket
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
l_int|0
suffix:semicolon
id|pw
op_assign
id|getpwnam
c_func
(paren
id|path
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
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pw
op_logical_or
op_logical_neg
id|pw-&gt;pw_dir
op_logical_or
id|sz
op_le
id|strlen
c_func
(paren
id|pw-&gt;pw_dir
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|baselen
op_assign
id|strlen
c_func
(paren
id|pw-&gt;pw_dir
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|pw-&gt;pw_dir
comma
id|baselen
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
l_int|1
OL
id|baselen
)paren
op_logical_and
(paren
id|buf
(braket
id|baselen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
(brace
id|buf
(braket
id|baselen
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|baselen
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slash
op_logical_and
id|slash
(braket
l_int|1
)braket
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|slash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
op_le
id|baselen
op_plus
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|baselen
comma
id|slash
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; * First, one directory to try is determined by the following algorithm.&n; *&n; * (0) If &quot;strict&quot; is given, the path is used as given and no DWIM is&n; *     done. Otherwise:&n; * (1) &quot;~/path&quot; to mean path under the running user&squot;s home directory;&n; * (2) &quot;~user/path&quot; to mean path under named user&squot;s home directory;&n; * (3) &quot;relative/path&quot; to mean cwd relative directory; or&n; * (4) &quot;/absolute/path&quot; to mean absolute directory.&n; *&n; * Unless &quot;strict&quot; is given, we try access() for existence of &quot;%s.git/.git&quot;,&n; * &quot;%s/.git&quot;, &quot;%s.git&quot;, &quot;%s&quot; in this order.  The first one that exists is&n; * what we try.&n; *&n; * Second, we try chdir() to that.  Upon failure, we return NULL.&n; *&n; * Then, we try if the current directory is a valid git repository.&n; * Upon failure, we return NULL.&n; *&n; * If all goes well, we return the directory we used to chdir() (but&n; * before ~user is expanded), avoiding getcwd() resolving symbolic&n; * links.  User relative paths are also returned as they are given,&n; * except DWIM suffixing.&n; */
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
r_static
r_char
id|used_path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_static
r_char
id|validated_path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strict
)paren
(brace
r_static
r_const
r_char
op_star
id|suffix
(braket
)braket
op_assign
(brace
l_string|&quot;.git/.git&quot;
comma
l_string|&quot;/.git&quot;
comma
l_string|&quot;.git&quot;
comma
l_string|&quot;&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
(paren
l_int|1
OL
id|len
)paren
op_logical_and
(paren
id|path
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
(brace
id|path
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PATH_MAX
op_le
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|path
(braket
l_int|0
)braket
op_eq
l_char|&squot;~&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|user_path
c_func
(paren
id|used_path
comma
id|path
comma
id|PATH_MAX
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|strcpy
c_func
(paren
id|validated_path
comma
id|path
)paren
suffix:semicolon
id|path
op_assign
id|used_path
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PATH_MAX
l_int|10
OL
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
(brace
id|path
op_assign
id|strcpy
c_func
(paren
id|used_path
comma
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|validated_path
comma
id|path
)paren
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|suffix
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
id|suffix
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|path
comma
id|F_OK
)paren
)paren
(brace
id|strcat
c_func
(paren
id|validated_path
comma
id|suffix
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|suffix
(braket
id|i
)braket
op_logical_or
id|chdir
c_func
(paren
id|path
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|path
op_assign
id|validated_path
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|path
)paren
)paren
r_return
l_int|NULL
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
id|validate_headref
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
l_string|&quot;.&quot;
comma
l_int|1
)paren
suffix:semicolon
id|check_repository_format
c_func
(paren
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|adjust_shared_perm
r_int
id|adjust_shared_perm
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
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared_repository
)paren
r_return
l_int|0
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
id|mode
op_assign
id|st.st_mode
suffix:semicolon
r_if
c_cond
(paren
id|shared_repository
)paren
(brace
r_int
id|tweak
op_assign
id|shared_repository
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|S_IWUSR
)paren
)paren
id|tweak
op_and_assign
op_complement
l_int|0222
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_amp
op_complement
l_int|0777
)paren
op_or
id|tweak
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Preserve old PERM_UMASK behaviour */
r_if
c_cond
(paren
id|mode
op_amp
id|S_IWUSR
)paren
id|mode
op_or_assign
id|S_IWGRP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
id|mode
op_or_assign
id|FORCE_DIR_SET_GID
suffix:semicolon
multiline_comment|/* Copy read bits to execute bits */
id|mode
op_or_assign
(paren
id|shared_repository
op_amp
l_int|0444
)paren
op_rshift
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|mode
op_amp
id|st.st_mode
)paren
op_ne
id|mode
op_logical_and
id|chmod
c_func
(paren
id|path
comma
id|mode
)paren
OL
l_int|0
)paren
r_return
l_int|2
suffix:semicolon
r_return
l_int|0
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
DECL|function|make_nonrelative_path
r_const
r_char
op_star
id|make_nonrelative_path
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
id|die
c_func
(paren
l_string|&quot;Cannot determine the current working directory&quot;
)paren
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
l_string|&quot;%s/%s&quot;
comma
id|cwd
comma
id|path
)paren
op_ge
id|PATH_MAX
)paren
id|die
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
DECL|function|make_relative_path
r_const
r_char
op_star
id|make_relative_path
c_func
(paren
r_const
r_char
op_star
id|abs
comma
r_const
r_char
op_star
id|base
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
r_int
id|baselen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
r_return
id|abs
suffix:semicolon
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|abs
comma
id|base
)paren
)paren
r_return
id|abs
suffix:semicolon
r_if
c_cond
(paren
id|abs
(braket
id|baselen
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|baselen
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base
(braket
id|baselen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_return
id|abs
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
comma
id|abs
op_plus
id|baselen
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
eof
