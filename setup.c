macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
DECL|variable|inside_git_dir
r_static
r_int
id|inside_git_dir
op_assign
l_int|1
suffix:semicolon
DECL|variable|inside_work_tree
r_static
r_int
id|inside_work_tree
op_assign
l_int|1
suffix:semicolon
DECL|function|prefix_path
r_const
r_char
op_star
id|prefix_path
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_int
id|len
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_const
r_char
op_star
id|orig
op_assign
id|path
suffix:semicolon
r_char
op_star
id|sanitized
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|orig
)paren
)paren
id|strcpy
c_func
(paren
id|sanitized
comma
id|path
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|len
)paren
id|memcpy
c_func
(paren
id|sanitized
comma
id|prefix
comma
id|len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sanitized
op_plus
id|len
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|normalize_path_copy
c_func
(paren
id|sanitized
comma
id|sanitized
)paren
)paren
r_goto
id|error_out
suffix:semicolon
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|orig
)paren
)paren
(brace
r_const
r_char
op_star
id|work_tree
op_assign
id|get_git_work_tree
c_func
(paren
)paren
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|work_tree
)paren
suffix:semicolon
r_int
id|total
op_assign
id|strlen
c_func
(paren
id|sanitized
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|sanitized
comma
id|work_tree
comma
id|len
)paren
op_logical_or
(paren
id|sanitized
(braket
id|len
)braket
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
id|sanitized
(braket
id|len
)braket
op_ne
l_char|&squot;/&squot;
)paren
)paren
(brace
id|error_out
suffix:colon
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is outside repository&quot;
comma
id|orig
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sanitized
(braket
id|len
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len
op_increment
suffix:semicolon
id|memmove
c_func
(paren
id|sanitized
comma
id|sanitized
op_plus
id|len
comma
id|total
id|len
)paren
suffix:semicolon
)brace
r_return
id|sanitized
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
macro_line|#ifndef __MINGW32__
r_if
c_cond
(paren
op_logical_neg
id|pfx
op_logical_or
op_logical_neg
op_star
id|pfx
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
multiline_comment|/*&n; * Verify a filename that we got as an argument for a pathspec&n; * entry. Note that a filename that begins with &quot;-&quot; never verifies&n; * as true, because even if such a filename were to exist, we want&n; * it to be preceded by the &quot;--&quot; marker (or we want the user to&n; * use a format like &quot;./-filename&quot;)&n; */
DECL|function|verify_filename
r_void
id|verify_filename
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|arg
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
id|die
c_func
(paren
l_string|&quot;bad flag &squot;%s&squot; used after filename&quot;
comma
id|arg
)paren
suffix:semicolon
id|name
op_assign
id|prefix
ques
c_cond
id|prefix_filename
c_func
(paren
id|prefix
comma
id|strlen
c_func
(paren
id|prefix
)paren
comma
id|arg
)paren
suffix:colon
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|name
comma
op_amp
id|st
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
id|die
c_func
(paren
l_string|&quot;ambiguous argument &squot;%s&squot;: unknown revision or path not in the working tree.&bslash;n&quot;
l_string|&quot;Use &squot;--&squot; to separate paths from revisions&quot;
comma
id|arg
)paren
suffix:semicolon
id|die_errno
c_func
(paren
l_string|&quot;failed to stat &squot;%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Opposite of the above: the command line did not have -- marker&n; * and we parsed the arg as a refname.  It should not be interpretable&n; * as a filename.&n; */
DECL|function|verify_non_filename
r_void
id|verify_non_filename
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|arg
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_inside_work_tree
c_func
(paren
)paren
op_logical_or
id|is_inside_git_dir
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
r_return
suffix:semicolon
multiline_comment|/* flag */
id|name
op_assign
id|prefix
ques
c_cond
id|prefix_filename
c_func
(paren
id|prefix
comma
id|strlen
c_func
(paren
id|prefix
)paren
comma
id|arg
)paren
suffix:colon
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|name
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
l_string|&quot;ambiguous argument &squot;%s&squot;: both revision and filename&bslash;n&quot;
l_string|&quot;Use &squot;--&squot; to separate filenames from revisions&quot;
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
op_logical_and
id|errno
op_ne
id|ENOTDIR
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to stat &squot;%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|get_pathspec
r_const
r_char
op_star
op_star
id|get_pathspec
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_const
r_char
op_star
id|entry
op_assign
op_star
id|pathspec
suffix:semicolon
r_const
r_char
op_star
op_star
id|src
comma
op_star
op_star
id|dst
suffix:semicolon
r_int
id|prefixlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefix
op_logical_and
op_logical_neg
id|entry
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
r_static
r_const
r_char
op_star
id|spec
(braket
l_int|2
)braket
suffix:semicolon
id|spec
(braket
l_int|0
)braket
op_assign
id|prefix
suffix:semicolon
id|spec
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|spec
suffix:semicolon
)brace
multiline_comment|/* Otherwise we have to re-write the entries.. */
id|src
op_assign
id|pathspec
suffix:semicolon
id|dst
op_assign
id|pathspec
suffix:semicolon
id|prefixlen
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|src
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefixlen
comma
op_star
id|src
)paren
suffix:semicolon
op_star
(paren
id|dst
op_increment
)paren
op_assign
id|p
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
op_star
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|pathspec
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|pathspec
suffix:semicolon
)brace
multiline_comment|/*&n; * Test if it looks like we&squot;re at a git directory.&n; * We want to see:&n; *&n; *  - either an objects/ directory _or_ the proper&n; *    GIT_OBJECT_DIRECTORY environment variable&n; *  - a refs/ directory&n; *  - either a HEAD symlink or a HEAD file that is formatted as&n; *    a proper &quot;ref:&quot;, or a regular file HEAD that has a properly&n; *    formatted sha1 object name.&n; */
DECL|function|is_git_directory
r_static
r_int
id|is_git_directory
c_func
(paren
r_const
r_char
op_star
id|suspect
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|suspect
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
id|suspect
)paren
suffix:semicolon
r_if
c_cond
(paren
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
)paren
(brace
r_if
c_cond
(paren
id|access
c_func
(paren
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
comma
id|X_OK
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/objects&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|path
comma
id|X_OK
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/refs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|path
comma
id|X_OK
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|validate_headref
c_func
(paren
id|path
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|is_inside_git_dir
r_int
id|is_inside_git_dir
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inside_git_dir
OL
l_int|0
)paren
id|inside_git_dir
op_assign
id|is_inside_dir
c_func
(paren
id|get_git_dir
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|inside_git_dir
suffix:semicolon
)brace
DECL|function|is_inside_work_tree
r_int
id|is_inside_work_tree
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inside_work_tree
OL
l_int|0
)paren
id|inside_work_tree
op_assign
id|is_inside_dir
c_func
(paren
id|get_git_work_tree
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|inside_work_tree
suffix:semicolon
)brace
multiline_comment|/*&n; * set_work_tree() is only ever called if you set GIT_DIR explicitely.&n; * The old behaviour (which we retain here) is to set the work tree root&n; * to the cwd, unless overridden by the config, the command line, or&n; * GIT_WORK_TREE.&n; */
DECL|function|set_work_tree
r_static
r_const
r_char
op_star
id|set_work_tree
c_func
(paren
r_const
r_char
op_star
id|dir
)paren
(brace
r_char
id|buffer
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
id|getcwd
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
)paren
id|die
(paren
l_string|&quot;Could not get the current working directory&quot;
)paren
suffix:semicolon
id|git_work_tree_cfg
op_assign
id|xstrdup
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|inside_work_tree
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|setup_work_tree
r_void
id|setup_work_tree
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|work_tree
comma
op_star
id|git_dir
suffix:semicolon
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|initialized
)paren
r_return
suffix:semicolon
id|work_tree
op_assign
id|get_git_work_tree
c_func
(paren
)paren
suffix:semicolon
id|git_dir
op_assign
id|get_git_dir
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_absolute_path
c_func
(paren
id|git_dir
)paren
)paren
id|git_dir
op_assign
id|make_absolute_path
c_func
(paren
id|git_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|work_tree
op_logical_or
id|chdir
c_func
(paren
id|work_tree
)paren
)paren
id|die
c_func
(paren
l_string|&quot;This operation must be run in a work tree&quot;
)paren
suffix:semicolon
id|set_git_dir
c_func
(paren
id|make_relative_path
c_func
(paren
id|git_dir
comma
id|work_tree
)paren
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|check_repository_format_gently
r_static
r_int
id|check_repository_format_gently
c_func
(paren
r_int
op_star
id|nongit_ok
)paren
(brace
id|git_config
c_func
(paren
id|check_repository_format_version
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|GIT_REPO_VERSION
OL
id|repository_format_version
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nongit_ok
)paren
id|die
(paren
l_string|&quot;Expected git repo version &lt;= %d, found %d&quot;
comma
id|GIT_REPO_VERSION
comma
id|repository_format_version
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;Expected git repo version &lt;= %d, found %d&quot;
comma
id|GIT_REPO_VERSION
comma
id|repository_format_version
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;Please upgrade Git&quot;
)paren
suffix:semicolon
op_star
id|nongit_ok
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to read the location of the git directory from the .git file,&n; * return path to git directory if found.&n; */
DECL|function|read_gitfile_gently
r_const
r_char
op_star
id|read_gitfile_gently
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
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
id|die_errno
c_func
(paren
l_string|&quot;Error opening &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|buf
op_assign
id|xmalloc
c_func
(paren
id|st.st_size
op_plus
l_int|1
)paren
suffix:semicolon
id|len
op_assign
id|read_in_full
c_func
(paren
id|fd
comma
id|buf
comma
id|st.st_size
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
id|len
op_ne
id|st.st_size
)paren
id|die
c_func
(paren
l_string|&quot;Error reading %s&quot;
comma
id|path
)paren
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;gitdir: &quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Invalid gitfile format: %s&quot;
comma
id|path
)paren
suffix:semicolon
r_while
c_loop
(paren
id|buf
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|buf
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;r&squot;
)paren
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|9
)paren
id|die
c_func
(paren
l_string|&quot;No path in gitfile: %s&quot;
comma
id|path
)paren
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_git_directory
c_func
(paren
id|buf
op_plus
l_int|8
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a git repository: %s&quot;
comma
id|buf
op_plus
l_int|8
)paren
suffix:semicolon
id|path
op_assign
id|make_absolute_path
c_func
(paren
id|buf
op_plus
l_int|8
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
multiline_comment|/*&n; * We cannot decide in this function whether we are in the work tree or&n; * not, since the config can only be read _after_ this function was called.&n; */
DECL|function|setup_git_directory_gently
r_const
r_char
op_star
id|setup_git_directory_gently
c_func
(paren
r_int
op_star
id|nongit_ok
)paren
(brace
r_const
r_char
op_star
id|work_tree_env
op_assign
id|getenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
)paren
suffix:semicolon
r_const
r_char
op_star
id|env_ceiling_dirs
op_assign
id|getenv
c_func
(paren
id|CEILING_DIRECTORIES_ENVIRONMENT
)paren
suffix:semicolon
r_static
r_char
id|cwd
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_const
r_char
op_star
id|gitdirenv
suffix:semicolon
r_const
r_char
op_star
id|gitfile_dir
suffix:semicolon
r_int
id|len
comma
id|offset
comma
id|ceil_offset
suffix:semicolon
multiline_comment|/*&n;&t; * Let&squot;s assume that we are in a git repository.&n;&t; * If it turns out later that we are somewhere else, the value will be&n;&t; * updated accordingly.&n;&t; */
r_if
c_cond
(paren
id|nongit_ok
)paren
op_star
id|nongit_ok
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If GIT_DIR is set explicitly, we&squot;re not going&n;&t; * to do any discovery, but we still do repository&n;&t; * validation.&n;&t; */
id|gitdirenv
op_assign
id|getenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gitdirenv
)paren
(brace
r_if
c_cond
(paren
id|PATH_MAX
l_int|40
OL
id|strlen
c_func
(paren
id|gitdirenv
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;$%s&squot; too big&quot;
comma
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_git_directory
c_func
(paren
id|gitdirenv
)paren
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|1024
op_plus
l_int|1
)braket
suffix:semicolon
r_const
r_char
op_star
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|work_tree_env
)paren
(brace
id|retval
op_assign
id|set_work_tree
c_func
(paren
id|gitdirenv
)paren
suffix:semicolon
multiline_comment|/* config may override worktree */
r_if
c_cond
(paren
id|check_repository_format_gently
c_func
(paren
id|nongit_ok
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_repository_format_gently
c_func
(paren
id|nongit_ok
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|retval
op_assign
id|get_relative_cwd
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
l_int|1
comma
id|get_git_work_tree
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_or
op_logical_neg
op_star
id|retval
)paren
r_return
l_int|NULL
suffix:semicolon
id|set_git_dir
c_func
(paren
id|make_absolute_path
c_func
(paren
id|gitdirenv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|work_tree_env
)paren
OL
l_int|0
)paren
id|die_errno
(paren
l_string|&quot;Could not chdir to &squot;%s&squot;&quot;
comma
id|work_tree_env
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buffer
comma
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nongit_ok
)paren
(brace
op_star
id|nongit_ok
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;Not a git repository: &squot;%s&squot;&quot;
comma
id|gitdirenv
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
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
op_minus
l_int|1
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;Unable to read current working directory&quot;
)paren
suffix:semicolon
id|ceil_offset
op_assign
id|longest_ancestor_length
c_func
(paren
id|cwd
comma
id|env_ceiling_dirs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ceil_offset
OL
l_int|0
op_logical_and
id|has_dos_drive_prefix
c_func
(paren
id|cwd
)paren
)paren
id|ceil_offset
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Test in the following order (relative to the cwd):&n;&t; * - .git (file containing &quot;gitdir: &lt;path&gt;&quot;)&n;&t; * - .git/&n;&t; * - ./ (bare)&n;&t; * - ../.git&n;&t; * - ../.git/&n;&t; * - ../ (bare)&n;&t; * - ../../.git/&n;&t; *   etc.&n;&t; */
id|offset
op_assign
id|len
op_assign
id|strlen
c_func
(paren
id|cwd
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|gitfile_dir
op_assign
id|read_gitfile_gently
c_func
(paren
id|DEFAULT_GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gitfile_dir
)paren
(brace
r_if
c_cond
(paren
id|set_git_dir
c_func
(paren
id|gitfile_dir
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Repository setup failed&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_git_directory
c_func
(paren
id|DEFAULT_GIT_DIR_ENVIRONMENT
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|is_git_directory
c_func
(paren
l_string|&quot;.&quot;
)paren
)paren
(brace
id|inside_git_dir
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|work_tree_env
)paren
id|inside_work_tree
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ne
id|len
)paren
(brace
id|cwd
(braket
id|offset
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
id|cwd
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
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
id|check_repository_format_gently
c_func
(paren
id|nongit_ok
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|offset
OG
id|ceil_offset
op_logical_and
id|cwd
(braket
id|offset
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_le
id|ceil_offset
)paren
(brace
r_if
c_cond
(paren
id|nongit_ok
)paren
(brace
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|cwd
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot come back to cwd&quot;
)paren
suffix:semicolon
op_star
id|nongit_ok
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;Not a git repository (or any of the parent directories): %s&quot;
comma
id|DEFAULT_GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chdir
c_func
(paren
l_string|&quot;..&quot;
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot change to &squot;%s/..&squot;&quot;
comma
id|cwd
)paren
suffix:semicolon
)brace
id|inside_git_dir
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|work_tree_env
)paren
id|inside_work_tree
op_assign
l_int|1
suffix:semicolon
id|git_work_tree_cfg
op_assign
id|xstrndup
c_func
(paren
id|cwd
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_repository_format_gently
c_func
(paren
id|nongit_ok
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Make &quot;offset&quot; point to past the &squot;/&squot;, and add a &squot;/&squot; at the end */
id|offset
op_increment
suffix:semicolon
id|cwd
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|cwd
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|cwd
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|git_config_perm
r_int
id|git_config_perm
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|endptr
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|NULL
)paren
r_return
id|PERM_GROUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;umask&quot;
)paren
)paren
r_return
id|PERM_UMASK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;group&quot;
)paren
)paren
r_return
id|PERM_GROUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;all&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;world&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;everybody&quot;
)paren
)paren
r_return
id|PERM_EVERYBODY
suffix:semicolon
multiline_comment|/* Parse octal numbers */
id|i
op_assign
id|strtol
c_func
(paren
id|value
comma
op_amp
id|endptr
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* If not an octal number, maybe true/false? */
r_if
c_cond
(paren
op_star
id|endptr
op_ne
l_int|0
)paren
r_return
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
ques
c_cond
id|PERM_GROUP
suffix:colon
id|PERM_UMASK
suffix:semicolon
multiline_comment|/*&n;&t; * Treat values 0, 1 and 2 as compatibility cases, otherwise it is&n;&t; * a chmod value to restrict to.&n;&t; */
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
id|PERM_UMASK
suffix:colon
multiline_comment|/* 0 */
r_return
id|PERM_UMASK
suffix:semicolon
r_case
id|OLD_PERM_GROUP
suffix:colon
multiline_comment|/* 1 */
r_return
id|PERM_GROUP
suffix:semicolon
r_case
id|OLD_PERM_EVERYBODY
suffix:colon
multiline_comment|/* 2 */
r_return
id|PERM_EVERYBODY
suffix:semicolon
)brace
multiline_comment|/* A filemode value was given: 0xxx */
r_if
c_cond
(paren
(paren
id|i
op_amp
l_int|0600
)paren
op_ne
l_int|0600
)paren
id|die
c_func
(paren
l_string|&quot;Problem with core.sharedRepository filemode value &quot;
l_string|&quot;(0%.3o).&bslash;nThe owner of files must always have &quot;
l_string|&quot;read and write permissions.&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Mask filemode value. Others can not get write permission.&n;&t; * x flags for directories are handled separately.&n;&t; */
r_return
(paren
id|i
op_amp
l_int|0666
)paren
suffix:semicolon
)brace
DECL|function|check_repository_format_version
r_int
id|check_repository_format_version
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.repositoryformatversion&quot;
)paren
op_eq
l_int|0
)paren
id|repository_format_version
op_assign
id|git_config_int
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.sharedrepository&quot;
)paren
op_eq
l_int|0
)paren
id|shared_repository
op_assign
id|git_config_perm
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.bare&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|is_bare_repository_cfg
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bare_repository_cfg
op_eq
l_int|1
)paren
id|inside_work_tree
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.worktree&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|free
c_func
(paren
id|git_work_tree_cfg
)paren
suffix:semicolon
id|git_work_tree_cfg
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
id|inside_work_tree
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_repository_format
r_int
id|check_repository_format
c_func
(paren
r_void
)paren
(brace
r_return
id|check_repository_format_gently
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|setup_git_directory
r_const
r_char
op_star
id|setup_git_directory
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|retval
op_assign
id|setup_git_directory_gently
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* If the work tree is not the default one, recompute prefix */
r_if
c_cond
(paren
id|inside_work_tree
OL
l_int|0
)paren
(brace
r_static
r_char
id|buffer
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_char
op_star
id|rel
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_logical_and
id|chdir
c_func
(paren
id|retval
)paren
)paren
id|die_errno
(paren
l_string|&quot;Could not jump back into original cwd&quot;
)paren
suffix:semicolon
id|rel
op_assign
id|get_relative_cwd
c_func
(paren
id|buffer
comma
id|PATH_MAX
comma
id|get_git_work_tree
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rel
op_logical_and
op_star
id|rel
op_logical_and
id|chdir
c_func
(paren
id|get_git_work_tree
c_func
(paren
)paren
)paren
)paren
id|die_errno
(paren
l_string|&quot;Could not jump to working directory&quot;
)paren
suffix:semicolon
r_return
id|rel
op_logical_and
op_star
id|rel
ques
c_cond
id|strcat
c_func
(paren
id|rel
comma
l_string|&quot;/&quot;
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
