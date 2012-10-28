multiline_comment|/*&n; * I&squot;m tired of doing &quot;vsnprintf()&quot; etc just to open a&n; * file, so here&squot;s a &quot;return static buffer with printf&quot;&n; * interface for paths.&n; *&n; * It&squot;s obviously not thread-safe. Sue me. But it&squot;s quite&n; * useful for doing things like&n; *&n; *   f = open(mkpath(&quot;%s/%s.git&quot;, base, name), O_RDONLY);&n; *&n; * which is what it&squot;s designed for.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;string-list.h&quot;
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
DECL|function|mksnpath
r_char
op_star
id|mksnpath
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|n
comma
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
id|buf
comma
id|n
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
id|n
)paren
(brace
id|strlcpy
c_func
(paren
id|buf
comma
id|bad_path
comma
id|n
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_return
id|cleanup_path
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|vsnpath
r_static
r_char
op_star
id|vsnpath
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|n
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
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
id|n
OL
id|len
op_plus
l_int|1
)paren
r_goto
id|bad
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
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
op_logical_neg
id|is_dir_sep
c_func
(paren
id|git_dir
(braket
id|len
op_minus
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
id|len
op_add_assign
id|vsnprintf
c_func
(paren
id|buf
op_plus
id|len
comma
id|n
id|len
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|n
)paren
r_goto
id|bad
suffix:semicolon
r_return
id|cleanup_path
c_func
(paren
id|buf
)paren
suffix:semicolon
id|bad
suffix:colon
id|strlcpy
c_func
(paren
id|buf
comma
id|bad_path
comma
id|n
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|function|git_snpath
r_char
op_star
id|git_snpath
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|n
comma
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
r_char
op_star
id|ret
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|vsnpath
c_func
(paren
id|buf
comma
id|n
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
r_return
id|ret
suffix:semicolon
)brace
DECL|function|git_pathdup
r_char
op_star
id|git_pathdup
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
r_char
id|path
(braket
id|PATH_MAX
)braket
comma
op_star
id|ret
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|vsnpath
c_func
(paren
id|path
comma
r_sizeof
(paren
id|path
)paren
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
r_return
id|xstrdup
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|mkpathdup
r_char
op_star
id|mkpathdup
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
r_char
op_star
id|path
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|sb
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
id|path
op_assign
id|xstrdup
c_func
(paren
id|cleanup_path
c_func
(paren
id|sb.buf
)paren
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
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
r_char
op_star
id|ret
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|vsnpath
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
r_return
id|ret
suffix:semicolon
)brace
DECL|function|home_config_paths
r_void
id|home_config_paths
c_func
(paren
r_char
op_star
op_star
id|global
comma
r_char
op_star
op_star
id|xdg
comma
r_char
op_star
id|file
)paren
(brace
r_char
op_star
id|xdg_home
op_assign
id|getenv
c_func
(paren
l_string|&quot;XDG_CONFIG_HOME&quot;
)paren
suffix:semicolon
r_char
op_star
id|home
op_assign
id|getenv
c_func
(paren
l_string|&quot;HOME&quot;
)paren
suffix:semicolon
r_char
op_star
id|to_free
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|home
)paren
(brace
r_if
c_cond
(paren
id|global
)paren
op_star
id|global
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|xdg_home
)paren
(brace
id|to_free
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/.config&quot;
comma
id|home
)paren
suffix:semicolon
id|xdg_home
op_assign
id|to_free
suffix:semicolon
)brace
r_if
c_cond
(paren
id|global
)paren
op_star
id|global
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/.gitconfig&quot;
comma
id|home
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|xdg_home
)paren
op_star
id|xdg
op_assign
l_int|NULL
suffix:semicolon
r_else
op_star
id|xdg
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/git/%s&quot;
comma
id|xdg_home
comma
id|file
)paren
suffix:semicolon
id|free
c_func
(paren
id|to_free
)paren
suffix:semicolon
)brace
DECL|function|git_path_submodule
r_char
op_star
id|git_path_submodule
c_func
(paren
r_const
r_char
op_star
id|path
comma
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
r_char
op_star
id|pathname
op_assign
id|get_pathname
c_func
(paren
)paren
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|git_dir
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
id|path
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
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|path
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;.git&quot;
)paren
suffix:semicolon
id|git_dir
op_assign
id|read_gitfile
c_func
(paren
id|buf.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_dir
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|git_dir
)paren
suffix:semicolon
)brace
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.len
op_ge
id|PATH_MAX
)paren
r_return
id|bad_path
suffix:semicolon
id|memcpy
c_func
(paren
id|pathname
comma
id|buf.buf
comma
id|buf.len
op_plus
l_int|1
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|pathname
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
DECL|function|getpw_str
r_static
r_struct
id|passwd
op_star
id|getpw_str
c_func
(paren
r_const
r_char
op_star
id|username
comma
r_int
id|len
)paren
(brace
r_struct
id|passwd
op_star
id|pw
suffix:semicolon
r_char
op_star
id|username_z
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|username_z
comma
id|username
comma
id|len
)paren
suffix:semicolon
id|username_z
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|pw
op_assign
id|getpwnam
c_func
(paren
id|username_z
)paren
suffix:semicolon
id|free
c_func
(paren
id|username_z
)paren
suffix:semicolon
r_return
id|pw
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a string with ~ and ~user expanded via getpw*.  If buf != NULL,&n; * then it is a newly allocated string. Returns NULL on getpw failure or&n; * if path is NULL.&n; */
DECL|function|expand_user_path
r_char
op_star
id|expand_user_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|strbuf
id|user_path
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|first_slash
op_assign
id|strchrnul
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|to_copy
op_assign
id|path
suffix:semicolon
r_if
c_cond
(paren
id|path
op_eq
l_int|NULL
)paren
r_goto
id|return_null
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
r_const
r_char
op_star
id|username
op_assign
id|path
op_plus
l_int|1
suffix:semicolon
r_int
id|username_len
op_assign
id|first_slash
id|username
suffix:semicolon
r_if
c_cond
(paren
id|username_len
op_eq
l_int|0
)paren
(brace
r_const
r_char
op_star
id|home
op_assign
id|getenv
c_func
(paren
l_string|&quot;HOME&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|home
)paren
r_goto
id|return_null
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|user_path
comma
id|home
comma
id|strlen
c_func
(paren
id|home
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|passwd
op_star
id|pw
op_assign
id|getpw_str
c_func
(paren
id|username
comma
id|username_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pw
)paren
r_goto
id|return_null
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|user_path
comma
id|pw-&gt;pw_dir
comma
id|strlen
c_func
(paren
id|pw-&gt;pw_dir
)paren
)paren
suffix:semicolon
)brace
id|to_copy
op_assign
id|first_slash
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
op_amp
id|user_path
comma
id|to_copy
comma
id|strlen
c_func
(paren
id|to_copy
)paren
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|user_path
comma
l_int|NULL
)paren
suffix:semicolon
id|return_null
suffix:colon
id|strbuf_release
c_func
(paren
op_amp
id|user_path
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * First, one directory to try is determined by the following algorithm.&n; *&n; * (0) If &quot;strict&quot; is given, the path is used as given and no DWIM is&n; *     done. Otherwise:&n; * (1) &quot;~/path&quot; to mean path under the running user&squot;s home directory;&n; * (2) &quot;~user/path&quot; to mean path under named user&squot;s home directory;&n; * (3) &quot;relative/path&quot; to mean cwd relative directory; or&n; * (4) &quot;/absolute/path&quot; to mean absolute directory.&n; *&n; * Unless &quot;strict&quot; is given, we try access() for existence of &quot;%s.git/.git&quot;,&n; * &quot;%s/.git&quot;, &quot;%s.git&quot;, &quot;%s&quot; in this order.  The first one that exists is&n; * what we try.&n; *&n; * Second, we try chdir() to that.  Upon failure, we return NULL.&n; *&n; * Then, we try if the current directory is a valid git repository.&n; * Upon failure, we return NULL.&n; *&n; * If all goes well, we return the directory we used to chdir() (but&n; * before ~user is expanded), avoiding getcwd() resolving symbolic&n; * links.  User relative paths are also returned as they are given,&n; * except DWIM suffixing.&n; */
DECL|function|enter_repo
r_const
r_char
op_star
id|enter_repo
c_func
(paren
r_const
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
l_string|&quot;/.git&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;.git/.git&quot;
comma
l_string|&quot;.git&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_const
r_char
op_star
id|gitfile
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
id|len
op_decrement
suffix:semicolon
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
id|strncpy
c_func
(paren
id|used_path
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|used_path
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|validated_path
comma
id|used_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|used_path
(braket
l_int|0
)braket
op_eq
l_char|&squot;~&squot;
)paren
(brace
r_char
op_star
id|newpath
op_assign
id|expand_user_path
c_func
(paren
id|used_path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newpath
op_logical_or
(paren
id|PATH_MAX
l_int|10
OL
id|strlen
c_func
(paren
id|newpath
)paren
)paren
)paren
(brace
id|free
c_func
(paren
id|newpath
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Copy back into the static buffer. A pity&n;&t;&t;&t; * since newpath was not bounded, but other&n;&t;&t;&t; * branches of the if are limited by PATH_MAX&n;&t;&t;&t; * anyway.&n;&t;&t;&t; */
id|strcpy
c_func
(paren
id|used_path
comma
id|newpath
)paren
suffix:semicolon
id|free
c_func
(paren
id|newpath
)paren
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
id|len
op_assign
id|strlen
c_func
(paren
id|used_path
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
r_struct
id|stat
id|st
suffix:semicolon
id|strcpy
c_func
(paren
id|used_path
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
id|stat
c_func
(paren
id|used_path
comma
op_amp
id|st
)paren
op_logical_and
(paren
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
op_logical_and
id|is_git_directory
c_func
(paren
id|used_path
)paren
)paren
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
)paren
r_return
l_int|NULL
suffix:semicolon
id|gitfile
op_assign
id|read_gitfile
c_func
(paren
id|used_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gitfile
)paren
id|strcpy
c_func
(paren
id|used_path
comma
id|gitfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|used_path
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
id|set_git_dir
c_func
(paren
l_string|&quot;.&quot;
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
DECL|function|set_shared_perm
r_int
id|set_shared_perm
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|mode
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|tweak
comma
id|shared
comma
id|orig_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared_repository
)paren
(brace
r_if
c_cond
(paren
id|mode
)paren
r_return
id|chmod
c_func
(paren
id|path
comma
id|mode
op_amp
op_complement
id|S_IFMT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mode
)paren
(brace
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
id|orig_mode
op_assign
id|mode
suffix:semicolon
)brace
r_else
id|orig_mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|shared_repository
OL
l_int|0
)paren
id|shared
op_assign
id|shared_repository
suffix:semicolon
r_else
id|shared
op_assign
id|shared_repository
suffix:semicolon
id|tweak
op_assign
id|shared
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
r_if
c_cond
(paren
id|mode
op_amp
id|S_IXUSR
)paren
multiline_comment|/* Copy read bits to execute bits */
id|tweak
op_or_assign
(paren
id|tweak
op_amp
l_int|0444
)paren
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|shared_repository
OL
l_int|0
)paren
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
r_else
id|mode
op_or_assign
id|tweak
suffix:semicolon
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
multiline_comment|/* Copy read bits to execute bits */
id|mode
op_or_assign
(paren
id|shared
op_amp
l_int|0444
)paren
op_rshift
l_int|2
suffix:semicolon
id|mode
op_or_assign
id|FORCE_DIR_SET_GID
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|shared_repository
OL
l_int|0
ques
c_cond
(paren
id|orig_mode
op_amp
(paren
id|FORCE_DIR_SET_GID
op_or
l_int|0777
)paren
)paren
suffix:colon
(paren
id|orig_mode
op_amp
id|mode
)paren
)paren
op_ne
id|mode
)paren
op_logical_and
id|chmod
c_func
(paren
id|path
comma
(paren
id|mode
op_amp
op_complement
id|S_IFMT
)paren
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
DECL|function|relative_path
r_const
r_char
op_star
id|relative_path
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
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
op_logical_or
op_logical_neg
id|base
(braket
l_int|0
)braket
)paren
r_return
id|abs
suffix:semicolon
r_while
c_loop
(paren
id|base
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
id|base
(braket
id|i
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_dir_sep
c_func
(paren
id|abs
(braket
id|j
)braket
)paren
)paren
r_return
id|abs
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
id|base
(braket
id|i
)braket
)paren
)paren
id|i
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
id|abs
(braket
id|j
)braket
)paren
)paren
id|j
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|abs
(braket
id|j
)braket
op_ne
id|base
(braket
id|i
)braket
)paren
(brace
r_return
id|abs
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
multiline_comment|/* &quot;/foo&quot; is a prefix of &quot;/foo&quot; */
id|abs
(braket
id|j
)braket
op_logical_and
multiline_comment|/* &quot;/foo&quot; is not a prefix of &quot;/foobar&quot; */
op_logical_neg
id|is_dir_sep
c_func
(paren
id|base
(braket
id|i
op_minus
l_int|1
)braket
)paren
op_logical_and
op_logical_neg
id|is_dir_sep
c_func
(paren
id|abs
(braket
id|j
)braket
)paren
)paren
r_return
id|abs
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
id|abs
(braket
id|j
)braket
)paren
)paren
id|j
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|abs
(braket
id|j
)braket
)paren
id|strcpy
c_func
(paren
id|buf
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|buf
comma
id|abs
op_plus
id|j
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; * It is okay if dst == src, but they should not overlap otherwise.&n; *&n; * Performs the following normalizations on src, storing the result in dst:&n; * - Ensures that components are separated by &squot;/&squot; (Windows only)&n; * - Squashes sequences of &squot;/&squot;.&n; * - Removes &quot;.&quot; components.&n; * - Removes &quot;..&quot; components, and the components the precede them.&n; * Returns failure (non-zero) if a &quot;..&quot; component appears as first path&n; * component anytime during the normalization. Otherwise, returns success (0).&n; *&n; * Note that this function is purely textual.  It does not follow symlinks,&n; * verify the existence of the path, or make any system calls.&n; */
DECL|function|normalize_path_copy
r_int
id|normalize_path_copy
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|dst0
suffix:semicolon
r_if
c_cond
(paren
id|has_dos_drive_prefix
c_func
(paren
id|src
)paren
)paren
(brace
op_star
id|dst
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
op_star
id|dst
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
)brace
id|dst0
op_assign
id|dst
suffix:semicolon
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
op_star
id|src
)paren
)paren
(brace
op_star
id|dst
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
op_star
id|src
)paren
)paren
id|src
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
id|c
op_assign
op_star
id|src
suffix:semicolon
multiline_comment|/*&n;&t;&t; * A path component that begins with . could be&n;&t;&t; * special:&n;&t;&t; * (1) &quot;.&quot; and ends   -- ignore and terminate.&n;&t;&t; * (2) &quot;./&quot;           -- ignore them, eat slash and continue.&n;&t;&t; * (3) &quot;..&quot; and ends  -- strip one and terminate.&n;&t;&t; * (4) &quot;../&quot;          -- strip one, eat slash and continue.&n;&t;&t; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|src
(braket
l_int|1
)braket
)paren
(brace
multiline_comment|/* (1) */
id|src
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
id|src
(braket
l_int|1
)braket
)paren
)paren
(brace
multiline_comment|/* (2) */
id|src
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
op_star
id|src
)paren
)paren
id|src
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|src
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|src
(braket
l_int|2
)braket
)paren
(brace
multiline_comment|/* (3) */
id|src
op_add_assign
l_int|2
suffix:semicolon
r_goto
id|up_one
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
id|src
(braket
l_int|2
)braket
)paren
)paren
(brace
multiline_comment|/* (4) */
id|src
op_add_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
op_star
id|src
)paren
)paren
id|src
op_increment
suffix:semicolon
r_goto
id|up_one
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* copy up to the next &squot;/&squot;, and eat all &squot;/&squot; */
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
op_logical_neg
id|is_dir_sep
c_func
(paren
id|c
)paren
)paren
op_star
id|dst
op_increment
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
id|c
)paren
)paren
(brace
op_star
id|dst
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_while
c_loop
(paren
id|is_dir_sep
c_func
(paren
id|c
)paren
)paren
id|c
op_assign
op_star
id|src
op_increment
suffix:semicolon
id|src
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
id|up_one
suffix:colon
multiline_comment|/*&n;&t;&t; * dst0..dst is prefix portion, and dst[-1] is &squot;/&squot;;&n;&t;&t; * go up one level.&n;&t;&t; */
id|dst
op_decrement
suffix:semicolon
multiline_comment|/* go to trailing &squot;/&squot; */
r_if
c_cond
(paren
id|dst
op_le
id|dst0
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Windows: dst[-1] cannot be backslash anymore */
r_while
c_loop
(paren
id|dst0
OL
id|dst
op_logical_and
id|dst
(braket
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|dst
op_decrement
suffix:semicolon
)brace
op_star
id|dst
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * path = Canonical absolute path&n; * prefixes = string_list containing normalized, absolute paths without&n; * trailing slashes (except for the root directory, which is denoted by &quot;/&quot;).&n; *&n; * Determines, for each path in prefixes, whether the &quot;prefix&quot;&n; * is an ancestor directory of path.  Returns the length of the longest&n; * ancestor directory, excluding any trailing slashes, or -1 if no prefix&n; * is an ancestor.  (Note that this means 0 is returned if prefixes is&n; * [&quot;/&quot;].) &quot;/foo&quot; is not considered an ancestor of &quot;/foobar&quot;.  Directories&n; * are not considered to be their own ancestors.  path must be in a&n; * canonical form: empty components, or &quot;.&quot; or &quot;..&quot; components are not&n; * allowed.&n; */
DECL|function|longest_ancestor_length
r_int
id|longest_ancestor_length
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|string_list
op_star
id|prefixes
)paren
(brace
r_int
id|i
comma
id|max_len
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;/&quot;
)paren
)paren
r_return
l_int|1
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
id|prefixes-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|ceil
op_assign
id|prefixes-&gt;items
(braket
id|i
)braket
dot
id|string
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|ceil
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|1
op_logical_and
id|ceil
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* root matches anything, with length 0 */
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|path
comma
id|ceil
comma
id|len
)paren
op_logical_and
id|path
(braket
id|len
)braket
op_eq
l_char|&squot;/&squot;
)paren
suffix:semicolon
multiline_comment|/* match of length len */
r_else
r_continue
suffix:semicolon
multiline_comment|/* no match */
r_if
c_cond
(paren
id|len
OG
id|max_len
)paren
id|max_len
op_assign
id|len
suffix:semicolon
)brace
r_return
id|max_len
suffix:semicolon
)brace
multiline_comment|/* strip arbitrary amount of directory separators at end of path */
DECL|function|chomp_trailing_dir_sep
r_static
r_inline
r_int
id|chomp_trailing_dir_sep
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
op_logical_and
id|is_dir_sep
c_func
(paren
id|path
(braket
id|len
l_int|1
)braket
)paren
)paren
id|len
op_decrement
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * If path ends with suffix (complete path components), returns the&n; * part before suffix (sans trailing directory separators).&n; * Otherwise returns NULL.&n; */
DECL|function|strip_path_suffix
r_char
op_star
id|strip_path_suffix
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|suffix
)paren
(brace
r_int
id|path_len
op_assign
id|strlen
c_func
(paren
id|path
)paren
comma
id|suffix_len
op_assign
id|strlen
c_func
(paren
id|suffix
)paren
suffix:semicolon
r_while
c_loop
(paren
id|suffix_len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|path_len
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|is_dir_sep
c_func
(paren
id|path
(braket
id|path_len
l_int|1
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_dir_sep
c_func
(paren
id|suffix
(braket
id|suffix_len
l_int|1
)braket
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|path_len
op_assign
id|chomp_trailing_dir_sep
c_func
(paren
id|path
comma
id|path_len
)paren
suffix:semicolon
id|suffix_len
op_assign
id|chomp_trailing_dir_sep
c_func
(paren
id|suffix
comma
id|suffix_len
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|path
(braket
op_decrement
id|path_len
)braket
op_ne
id|suffix
(braket
op_decrement
id|suffix_len
)braket
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path_len
op_logical_and
op_logical_neg
id|is_dir_sep
c_func
(paren
id|path
(braket
id|path_len
l_int|1
)braket
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|xstrndup
c_func
(paren
id|path
comma
id|chomp_trailing_dir_sep
c_func
(paren
id|path
comma
id|path_len
)paren
)paren
suffix:semicolon
)brace
DECL|function|daemon_avoid_alias
r_int
id|daemon_avoid_alias
c_func
(paren
r_const
r_char
op_star
id|p
)paren
(brace
r_int
id|sl
comma
id|ndot
suffix:semicolon
multiline_comment|/*&n;&t; * This resurrects the belts and suspenders paranoia check by HPA&n;&t; * done in &lt;435560F7.4080006@zytor.com&gt; thread, now enter_repo()&n;&t; * does not do getcwd() based path canonicalization.&n;&t; *&n;&t; * sl becomes true immediately after seeing &squot;/&squot; and continues to&n;&t; * be true as long as dots continue after that without intervening&n;&t; * non-dot character.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
(paren
op_star
id|p
op_ne
l_char|&squot;/&squot;
op_logical_and
op_star
id|p
op_ne
l_char|&squot;~&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|sl
op_assign
l_int|1
suffix:semicolon
id|ndot
op_assign
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
id|ch
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sl
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;.&squot;
)paren
id|ndot
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
id|ndot
OL
l_int|3
)paren
multiline_comment|/* reject //, /./ and /../ */
r_return
l_int|1
suffix:semicolon
id|ndot
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
l_int|0
OL
id|ndot
op_logical_and
id|ndot
OL
l_int|3
)paren
multiline_comment|/* reject /.$ and /..$ */
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|sl
op_assign
id|ndot
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|sl
op_assign
l_int|1
suffix:semicolon
id|ndot
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|offset_1st_component
r_int
id|offset_1st_component
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|has_dos_drive_prefix
c_func
(paren
id|path
)paren
)paren
r_return
l_int|2
op_plus
id|is_dir_sep
c_func
(paren
id|path
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_return
id|is_dir_sep
c_func
(paren
id|path
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
eof
