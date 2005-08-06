multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#ifndef DEFAULT_GIT_TEMPLATE_DIR
DECL|macro|DEFAULT_GIT_TEMPLATE_DIR
mdefine_line|#define DEFAULT_GIT_TEMPLATE_DIR &quot;/usr/share/git-core/templates/&quot;
macro_line|#endif
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
DECL|function|copy_file
r_static
r_int
id|copy_file
c_func
(paren
r_const
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|mode
)paren
(brace
r_int
id|fdi
comma
id|fdo
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_amp
l_int|0111
)paren
ques
c_cond
l_int|0777
suffix:colon
l_int|0666
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fdi
op_assign
id|open
c_func
(paren
id|src
comma
id|O_RDONLY
)paren
)paren
OL
l_int|0
)paren
r_return
id|fdi
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fdo
op_assign
id|open
c_func
(paren
id|dst
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
id|mode
)paren
)paren
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|fdi
)paren
suffix:semicolon
r_return
id|fdo
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
id|buf
(braket
id|BUFSIZ
)braket
suffix:semicolon
id|ssize_t
id|leni
comma
id|leno
comma
id|ofs
suffix:semicolon
id|leni
op_assign
id|read
c_func
(paren
id|fdi
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|leni
OL
l_int|0
)paren
(brace
id|error_return
suffix:colon
id|close
c_func
(paren
id|fdo
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdi
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|leni
)paren
r_break
suffix:semicolon
id|ofs
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|leno
op_assign
id|write
c_func
(paren
id|fdo
comma
id|buf
op_plus
id|ofs
comma
id|leni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|leno
OL
l_int|0
)paren
r_goto
id|error_return
suffix:semicolon
id|leni
op_sub_assign
id|leno
suffix:semicolon
id|ofs
op_add_assign
id|leno
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
OL
id|leni
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fdo
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdi
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_templates_1
r_static
r_void
id|copy_templates_1
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|baselen
comma
r_char
op_star
r_template
comma
r_int
id|template_baselen
comma
id|DIR
op_star
id|dir
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
multiline_comment|/* Note: if &quot;.git/hooks&quot; file exists in the repository being&n;&t; * re-initialized, /etc/core-git/templates/hooks/update would&n;&t; * cause git-init-db to fail here.  I think this is sane but&n;&t; * it means that the set of templates we ship by default, along&n;&t; * with the way the namespace under .git/ is organized, should&n;&t; * be really carefully chosen.&n;&t; */
id|safe_create_dir
c_func
(paren
id|path
)paren
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
r_struct
id|stat
id|st_git
comma
id|st_template
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_int
id|exists
op_assign
l_int|0
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
(paren
id|PATH_MAX
op_le
id|baselen
op_plus
id|namelen
)paren
op_logical_or
(paren
id|PATH_MAX
op_le
id|template_baselen
op_plus
id|namelen
)paren
)paren
id|die
c_func
(paren
l_string|&quot;insanely long template name %s&quot;
comma
id|de-&gt;d_name
)paren
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
id|memcpy
c_func
(paren
r_template
op_plus
id|template_baselen
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
id|st_git
)paren
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
id|die
c_func
(paren
l_string|&quot;cannot stat %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_else
id|exists
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
r_template
comma
op_amp
id|st_template
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot stat template %s&quot;
comma
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st_template.st_mode
)paren
)paren
(brace
id|DIR
op_star
id|subdir
op_assign
id|opendir
c_func
(paren
r_template
)paren
suffix:semicolon
r_int
id|baselen_sub
op_assign
id|baselen
op_plus
id|namelen
suffix:semicolon
r_int
id|template_baselen_sub
op_assign
id|template_baselen
op_plus
id|namelen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subdir
)paren
id|die
c_func
(paren
l_string|&quot;cannot opendir %s&quot;
comma
r_template
)paren
suffix:semicolon
id|path
(braket
id|baselen_sub
op_increment
)braket
op_assign
r_template
(braket
id|template_baselen_sub
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|path
(braket
id|baselen_sub
)braket
op_assign
r_template
(braket
id|template_baselen_sub
)braket
op_assign
l_int|0
suffix:semicolon
id|copy_templates_1
c_func
(paren
id|path
comma
id|baselen_sub
comma
r_template
comma
id|template_baselen_sub
comma
id|subdir
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|subdir
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|exists
)paren
r_continue
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|st_template.st_mode
)paren
)paren
(brace
r_char
id|lnk
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|readlink
c_func
(paren
r_template
comma
id|lnk
comma
r_sizeof
(paren
id|lnk
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;cannot readlink %s&quot;
comma
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|lnk
)paren
op_le
id|len
)paren
id|die
c_func
(paren
l_string|&quot;insanely long symlink %s&quot;
comma
r_template
)paren
suffix:semicolon
id|lnk
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|symlink
c_func
(paren
id|lnk
comma
id|path
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot symlink %s %s&quot;
comma
id|lnk
comma
id|path
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|st_template.st_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_file
c_func
(paren
id|path
comma
r_template
comma
id|st_template.st_mode
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cannot copy %s to %s&quot;
comma
r_template
comma
id|path
)paren
suffix:semicolon
)brace
r_else
id|error
c_func
(paren
l_string|&quot;ignoring template %s&quot;
comma
r_template
)paren
suffix:semicolon
)brace
)brace
DECL|function|copy_templates
r_static
r_void
id|copy_templates
c_func
(paren
r_const
r_char
op_star
id|git_dir
comma
r_int
id|len
comma
r_char
op_star
id|template_dir
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
id|template_path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|template_len
suffix:semicolon
id|DIR
op_star
id|dir
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|template_dir
)paren
id|template_dir
op_assign
id|DEFAULT_GIT_TEMPLATE_DIR
suffix:semicolon
id|strcpy
c_func
(paren
id|template_path
comma
id|template_dir
)paren
suffix:semicolon
id|template_len
op_assign
id|strlen
c_func
(paren
id|template_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|template_path
(braket
id|template_len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
(brace
id|template_path
(braket
id|template_len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|template_path
(braket
id|template_len
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|dir
op_assign
id|opendir
c_func
(paren
id|template_path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: templates not found %s&bslash;n&quot;
comma
id|template_dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|copy_templates_1
c_func
(paren
id|path
comma
id|len
comma
id|template_path
comma
id|template_len
comma
id|dir
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
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
comma
r_char
op_star
id|template_path
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
id|copy_templates
c_func
(paren
id|path
comma
id|len
comma
id|template_path
)paren
suffix:semicolon
)brace
DECL|variable|init_db_usage
r_static
r_const
r_char
id|init_db_usage
(braket
)braket
op_assign
l_string|&quot;git-init-db [--template=&lt;template-directory&gt;]&quot;
suffix:semicolon
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
comma
op_star
id|template_dir
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
comma
id|argv
op_increment
)paren
(brace
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--template=&quot;
comma
l_int|11
)paren
)paren
id|template_dir
op_assign
id|arg
op_plus
l_int|11
suffix:semicolon
r_else
id|die
c_func
(paren
id|init_db_usage
)paren
suffix:semicolon
)brace
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
comma
id|template_dir
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
