multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|function|safe_create_dir
r_static
r_void
id|safe_create_dir
c_func
(paren
r_const
r_char
op_star
id|dir
)paren
(brace
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|dir
comma
l_int|0777
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
(brace
id|perror
c_func
(paren
id|dir
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|create_default_files
r_static
r_void
id|create_default_files
c_func
(paren
r_const
r_char
op_star
id|git_dir
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|git_dir
)paren
suffix:semicolon
r_static
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
r_sizeof
(paren
id|path
)paren
op_minus
l_int|50
)paren
id|die
c_func
(paren
l_string|&quot;insane git directory %s&quot;
comma
id|git_dir
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
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
id|path
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|path
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
multiline_comment|/*&n;&t; * Create .git/refs/{heads,tags}&n;&t; */
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;refs&quot;
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;refs/heads&quot;
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;refs/tags&quot;
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the default symlink from &quot;.git/HEAD&quot; to the &quot;master&quot;&n;&t; * branch&n;&t; */
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symlink
c_func
(paren
l_string|&quot;refs/heads/master&quot;
comma
id|path
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
(brace
id|perror
c_func
(paren
id|path
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * If you want to, you can share the DB area with any number of branches.&n; * That has advantages: you can save space by sharing all the SHA1 objects.&n; * On the other hand, it might just make lookup slower and messier. You&n; * be the judge.  The default case is to have one DB per managed directory.&n; */
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_const
r_char
op_star
id|git_dir
suffix:semicolon
r_const
r_char
op_star
id|sha1_dir
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the default .git directory contents&n;&t; */
id|git_dir
op_assign
id|gitenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_dir
)paren
(brace
id|git_dir
op_assign
id|DEFAULT_GIT_DIR_ENVIRONMENT
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;defaulting to local storage area&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|safe_create_dir
c_func
(paren
id|git_dir
)paren
suffix:semicolon
id|create_default_files
c_func
(paren
id|git_dir
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * And set up the object store.&n;&t; */
id|sha1_dir
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|sha1_dir
)paren
suffix:semicolon
id|path
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|40
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|sha1_dir
comma
id|len
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|sha1_dir
)paren
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/%02x&quot;
comma
id|i
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/pack&quot;
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
