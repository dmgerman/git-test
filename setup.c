macro_line|#include &quot;cache.h&quot;
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_star
id|path
op_ne
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
id|c
op_assign
id|path
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* &quot;.&quot; */
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
(brace
id|path
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* &quot;./&quot; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|path
op_add_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
id|c
op_assign
id|path
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
id|path
op_add_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
id|path
op_add_assign
l_int|3
suffix:semicolon
r_else
r_break
suffix:semicolon
multiline_comment|/* &quot;..&quot; and &quot;../&quot; */
multiline_comment|/* Remove last component of the prefix */
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is outside repository&quot;
comma
id|orig
)paren
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
op_logical_and
id|prefix
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
)paren
(brace
r_int
id|speclen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_char
op_star
id|n
op_assign
id|xmalloc
c_func
(paren
id|speclen
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|n
comma
id|prefix
comma
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|n
op_plus
id|len
comma
id|path
comma
id|speclen
op_plus
l_int|1
)paren
suffix:semicolon
id|path
op_assign
id|n
suffix:semicolon
)brace
r_return
id|path
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
id|p
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
id|p
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
r_do
(brace
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
id|entry
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|entry
op_assign
op_star
op_increment
id|p
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
r_const
r_char
op_star
op_star
)paren
id|pathspec
suffix:semicolon
)brace
multiline_comment|/*&n; * Test if it looks like we&squot;re at the top level git directory.&n; * We want to see:&n; *&n; *  - either a .git/objects/ directory _or_ the proper&n; *    GIT_OBJECT_DIRECTORY environment variable&n; *  - a refs/ directory under &quot;.git&quot;&n; *  - either a HEAD symlink or a HEAD file that is formatted as&n; *    a proper &quot;ref:&quot;.&n; */
DECL|function|is_toplevel_directory
r_static
r_int
id|is_toplevel_directory
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|access
c_func
(paren
l_string|&quot;.git/refs/&quot;
comma
id|X_OK
)paren
op_logical_or
id|access
c_func
(paren
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
ques
c_cond
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
suffix:colon
l_string|&quot;.git/objects/&quot;
comma
id|X_OK
)paren
op_logical_or
id|validate_symref
c_func
(paren
l_string|&quot;.git/HEAD&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setup_git_directory_1
r_static
r_const
r_char
op_star
id|setup_git_directory_1
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
r_int
id|len
comma
id|offset
suffix:semicolon
multiline_comment|/*&n;&t; * If GIT_DIR is set explicitly, we&squot;re not going&n;&t; * to do any discovery, but we still do repository&n;&t; * validation.&n;&t; */
r_if
c_cond
(paren
id|getenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
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
id|getenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|path
)paren
l_int|40
OL
id|len
)paren
id|die
c_func
(paren
l_string|&quot;&squot;$%s&squot; too big&quot;
comma
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|getenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
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
r_goto
id|bad_dir_environ
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
id|validate_symref
c_func
(paren
id|path
)paren
)paren
r_goto
id|bad_dir_environ
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
id|DB_ENVIRONMENT
comma
id|X_OK
)paren
)paren
r_goto
id|bad_dir_environ
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
r_goto
id|bad_dir_environ
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
id|bad_dir_environ
suffix:colon
id|path
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Not a git repository: &squot;%s&squot;&quot;
comma
id|path
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
)paren
op_logical_or
id|cwd
(braket
l_int|0
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|die
c_func
(paren
l_string|&quot;Unable to read current working directory&quot;
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|is_toplevel_directory
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
id|chdir
c_func
(paren
l_string|&quot;..&quot;
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|offset
)paren
id|die
c_func
(paren
l_string|&quot;Not a git repository&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cwd
(braket
op_decrement
id|offset
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
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
id|setup_git_directory_1
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
