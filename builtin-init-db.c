multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#ifndef DEFAULT_GIT_TEMPLATE_DIR
DECL|macro|DEFAULT_GIT_TEMPLATE_DIR
mdefine_line|#define DEFAULT_GIT_TEMPLATE_DIR &quot;/usr/share/git-core/templates&quot;
macro_line|#endif
macro_line|#ifdef NO_TRUSTABLE_FILEMODE
DECL|macro|TEST_FILEMODE
mdefine_line|#define TEST_FILEMODE 0
macro_line|#else
DECL|macro|TEST_FILEMODE
mdefine_line|#define TEST_FILEMODE 1
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
comma
r_int
id|share
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
r_else
r_if
c_cond
(paren
id|share
op_logical_and
id|adjust_shared_perm
c_func
(paren
id|dir
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not make %s writable by group&bslash;n&quot;
comma
id|dir
)paren
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
multiline_comment|/* Note: if &quot;.git/hooks&quot; file exists in the repository being&n;&t; * re-initialized, /etc/core-git/templates/hooks/update would&n;&t; * cause git-init to fail here.  I think this is sane but&n;&t; * it means that the set of templates we ship by default, along&n;&t; * with the way the namespace under .git/ is organized, should&n;&t; * be really carefully chosen.&n;&t; */
id|safe_create_dir
c_func
(paren
id|path
comma
l_int|1
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
op_logical_neg
id|template_dir
)paren
id|template_dir
op_assign
id|getenv
c_func
(paren
id|TEMPLATE_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|template_dir
)paren
id|template_dir
op_assign
id|system_path
c_func
(paren
id|DEFAULT_GIT_TEMPLATE_DIR
)paren
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
multiline_comment|/* Make sure that template is from the correct vintage */
id|strcpy
c_func
(paren
id|template_path
op_plus
id|template_len
comma
l_string|&quot;config&quot;
)paren
suffix:semicolon
id|repository_format_version
op_assign
l_int|0
suffix:semicolon
id|git_config_from_file
c_func
(paren
id|check_repository_format_version
comma
id|template_path
comma
l_int|NULL
)paren
suffix:semicolon
id|template_path
(braket
id|template_len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|repository_format_version
op_logical_and
id|repository_format_version
op_ne
id|GIT_REPO_VERSION
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: not copying templates of &quot;
l_string|&quot;a wrong format version %d from &squot;%s&squot;&bslash;n&quot;
comma
id|repository_format_version
comma
id|template_dir
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|dir
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
r_if
c_cond
(paren
id|len
op_logical_and
id|path
(braket
id|len
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
id|path
(braket
id|len
)braket
op_assign
l_int|0
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
r_int
id|create_default_files
c_func
(paren
r_const
r_char
op_star
id|template_path
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
r_struct
id|stat
id|st1
suffix:semicolon
r_char
id|repo_version_string
(braket
l_int|10
)braket
suffix:semicolon
r_char
id|junk
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|reinit
suffix:semicolon
r_int
id|filemode
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
id|safe_create_dir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs&quot;
)paren
comma
l_int|1
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs/heads&quot;
)paren
comma
l_int|1
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs/tags&quot;
)paren
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* First copy the templates -- we might have the default&n;&t; * config file there, in which case we would want to read&n;&t; * from it after installing.&n;&t; */
id|copy_templates
c_func
(paren
id|template_path
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We would have created the above under user&squot;s umask -- under&n;&t; * shared-repository settings, we would need to fix them up.&n;&t; */
r_if
c_cond
(paren
id|shared_repository
)paren
(brace
id|adjust_shared_perm
c_func
(paren
id|get_git_dir
c_func
(paren
)paren
)paren
suffix:semicolon
id|adjust_shared_perm
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs&quot;
)paren
)paren
suffix:semicolon
id|adjust_shared_perm
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs/heads&quot;
)paren
)paren
suffix:semicolon
id|adjust_shared_perm
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;refs/tags&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create the default symlink from &quot;.git/HEAD&quot; to the &quot;master&quot;&n;&t; * branch, if it does not exist yet.&n;&t; */
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
id|reinit
op_assign
(paren
op_logical_neg
id|access
c_func
(paren
id|path
comma
id|R_OK
)paren
op_logical_or
id|readlink
c_func
(paren
id|path
comma
id|junk
comma
r_sizeof
(paren
id|junk
)paren
op_minus
l_int|1
)paren
op_ne
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reinit
)paren
(brace
r_if
c_cond
(paren
id|create_symref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
l_string|&quot;refs/heads/master&quot;
comma
l_int|NULL
)paren
OL
l_int|0
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* This forces creation of new config file */
id|sprintf
c_func
(paren
id|repo_version_string
comma
l_string|&quot;%d&quot;
comma
id|GIT_REPO_VERSION
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
l_string|&quot;core.repositoryformatversion&quot;
comma
id|repo_version_string
)paren
suffix:semicolon
id|path
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;config&quot;
)paren
suffix:semicolon
multiline_comment|/* Check filemode trustability */
id|filemode
op_assign
id|TEST_FILEMODE
suffix:semicolon
r_if
c_cond
(paren
id|TEST_FILEMODE
op_logical_and
op_logical_neg
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st1
)paren
)paren
(brace
r_struct
id|stat
id|st2
suffix:semicolon
id|filemode
op_assign
(paren
op_logical_neg
id|chmod
c_func
(paren
id|path
comma
id|st1.st_mode
op_xor
id|S_IXUSR
)paren
op_logical_and
op_logical_neg
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st2
)paren
op_logical_and
id|st1.st_mode
op_ne
id|st2.st_mode
)paren
suffix:semicolon
)brace
id|git_config_set
c_func
(paren
l_string|&quot;core.filemode&quot;
comma
id|filemode
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bare_repository
c_func
(paren
)paren
)paren
id|git_config_set
c_func
(paren
l_string|&quot;core.bare&quot;
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
r_else
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
id|git_config_set
c_func
(paren
l_string|&quot;core.bare&quot;
comma
l_string|&quot;false&quot;
)paren
suffix:semicolon
multiline_comment|/* allow template config file to override the default */
r_if
c_cond
(paren
id|log_all_ref_updates
op_eq
l_int|1
)paren
id|git_config_set
c_func
(paren
l_string|&quot;core.logallrefupdates&quot;
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|git_dir
comma
id|work_tree
)paren
op_logical_or
id|strcmp
c_func
(paren
id|git_dir
op_plus
id|strlen
c_func
(paren
id|work_tree
)paren
comma
l_string|&quot;/.git&quot;
)paren
)paren
(brace
id|git_config_set
c_func
(paren
l_string|&quot;core.worktree&quot;
comma
id|work_tree
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|reinit
)paren
(brace
multiline_comment|/* Check if symlink is supported in the work tree */
id|path
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;tXXXXXX&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|close
c_func
(paren
id|xmkstemp
c_func
(paren
id|path
)paren
)paren
op_logical_and
op_logical_neg
id|unlink
c_func
(paren
id|path
)paren
op_logical_and
op_logical_neg
id|symlink
c_func
(paren
l_string|&quot;testing&quot;
comma
id|path
)paren
op_logical_and
op_logical_neg
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st1
)paren
op_logical_and
id|S_ISLNK
c_func
(paren
id|st1.st_mode
)paren
)paren
id|unlink
c_func
(paren
id|path
)paren
suffix:semicolon
multiline_comment|/* good */
r_else
id|git_config_set
c_func
(paren
l_string|&quot;core.symlinks&quot;
comma
l_string|&quot;false&quot;
)paren
suffix:semicolon
multiline_comment|/* Check if the filesystem is case-insensitive */
id|path
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;CoNfIg&quot;
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
id|git_config_set
c_func
(paren
l_string|&quot;core.ignorecase&quot;
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
)brace
r_return
id|reinit
suffix:semicolon
)brace
DECL|function|init_db
r_int
id|init_db
c_func
(paren
r_const
r_char
op_star
id|template_dir
comma
r_int
r_int
id|flags
)paren
(brace
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
id|reinit
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|get_git_dir
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Check to see if the repository version is right.&n;&t; * Note that a newly created repository does not have&n;&t; * config file, so this will not fail.  What we are catching&n;&t; * is an attempt to reinitialize new repository with an old tool.&n;&t; */
id|check_repository_format
c_func
(paren
)paren
suffix:semicolon
id|reinit
op_assign
id|create_default_files
c_func
(paren
id|template_dir
)paren
suffix:semicolon
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
comma
l_int|1
)paren
suffix:semicolon
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
comma
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/info&quot;
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|path
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shared_repository
)paren
(brace
r_char
id|buf
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* We do not spell &quot;group&quot; and such, so that&n;&t;&t; * the configuration can be read by older version&n;&t;&t; * of git. Note, we use octal numbers for new share modes,&n;&t;&t; * and compatibility values for PERM_GROUP and&n;&t;&t; * PERM_EVERYBODY.&n;&t;&t; */
r_if
c_cond
(paren
id|shared_repository
op_eq
id|PERM_GROUP
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&quot;
comma
id|OLD_PERM_GROUP
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|shared_repository
op_eq
id|PERM_EVERYBODY
)paren
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&quot;
comma
id|OLD_PERM_EVERYBODY
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;0%o&quot;
comma
id|shared_repository
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
l_string|&quot;core.sharedrepository&quot;
comma
id|buf
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
l_string|&quot;receive.denyNonFastforwards&quot;
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|INIT_DB_QUIET
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s Git repository in %s/&bslash;n&quot;
comma
id|reinit
ques
c_cond
l_string|&quot;Reinitialized existing&quot;
suffix:colon
l_string|&quot;Initialized empty&quot;
comma
id|shared_repository
ques
c_cond
l_string|&quot; shared&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|get_git_dir
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|guess_repository_type
r_static
r_int
id|guess_repository_type
c_func
(paren
r_const
r_char
op_star
id|git_dir
)paren
(brace
r_char
id|cwd
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|slash
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;GIT_DIR=. git init&quot; is always bare.&n;&t; * &quot;GIT_DIR=`pwd` git init&quot; too.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;.&quot;
comma
id|git_dir
)paren
)paren
r_return
l_int|1
suffix:semicolon
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
)paren
id|die
c_func
(paren
l_string|&quot;cannot tell cwd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|git_dir
comma
id|cwd
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;GIT_DIR=.git or GIT_DIR=something/.git is usually not.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|git_dir
comma
l_string|&quot;.git&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|slash
op_assign
id|strrchr
c_func
(paren
id|git_dir
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slash
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|slash
comma
l_string|&quot;/.git&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Otherwise it is often bare.  At this point&n;&t; * we are just guessing.&n;&t; */
r_return
l_int|1
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
l_string|&quot;git init [-q | --quiet] [--bare] [--template=&lt;template-directory&gt;] [--shared[=&lt;permissions&gt;]]&quot;
suffix:semicolon
multiline_comment|/*&n; * If you want to, you can share the DB area with any number of branches.&n; * That has advantages: you can save space by sharing all the SHA1 objects.&n; * On the other hand, it might just make lookup slower and messier. You&n; * be the judge.  The default case is to have one DB per managed directory.&n; */
DECL|function|cmd_init_db
r_int
id|cmd_init_db
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|prefix
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
id|template_dir
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
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
r_const
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--template=&quot;
)paren
)paren
id|template_dir
op_assign
id|arg
op_plus
l_int|11
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--bare&quot;
)paren
)paren
(brace
r_static
r_char
id|git_dir
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
id|is_bare_repository_cfg
op_assign
l_int|1
suffix:semicolon
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
id|getcwd
c_func
(paren
id|git_dir
comma
r_sizeof
(paren
id|git_dir
)paren
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--shared&quot;
)paren
)paren
id|shared_repository
op_assign
id|PERM_GROUP
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--shared=&quot;
)paren
)paren
id|shared_repository
op_assign
id|git_config_perm
c_func
(paren
l_string|&quot;arg&quot;
comma
id|arg
op_plus
l_int|9
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-q&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--quiet&quot;
)paren
)paren
id|flags
op_or_assign
id|INIT_DB_QUIET
suffix:semicolon
r_else
id|usage
c_func
(paren
id|init_db_usage
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * GIT_WORK_TREE makes sense only in conjunction with GIT_DIR&n;&t; * without --bare.  Catch the error early.&n;&t; */
id|git_dir
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
(paren
op_logical_neg
id|git_dir
op_logical_or
id|is_bare_repository_cfg
op_eq
l_int|1
)paren
op_logical_and
id|getenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s (or --work-tree=&lt;directory&gt;) not allowed without &quot;
l_string|&quot;specifying %s (or --git-dir=&lt;directory&gt;)&quot;
comma
id|GIT_WORK_TREE_ENVIRONMENT
comma
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the default .git directory contents&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|git_dir
)paren
id|git_dir
op_assign
id|DEFAULT_GIT_DIR_ENVIRONMENT
suffix:semicolon
r_if
c_cond
(paren
id|is_bare_repository_cfg
OL
l_int|0
)paren
id|is_bare_repository_cfg
op_assign
id|guess_repository_type
c_func
(paren
id|git_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_bare_repository_cfg
)paren
(brace
r_if
c_cond
(paren
id|git_dir
)paren
(brace
r_const
r_char
op_star
id|git_dir_parent
op_assign
id|strrchr
c_func
(paren
id|git_dir
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_dir_parent
)paren
(brace
r_char
op_star
id|rel
op_assign
id|xstrndup
c_func
(paren
id|git_dir
comma
id|git_dir_parent
id|git_dir
)paren
suffix:semicolon
id|git_work_tree_cfg
op_assign
id|xstrdup
c_func
(paren
id|make_absolute_path
c_func
(paren
id|rel
)paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|rel
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|git_work_tree_cfg
)paren
(brace
id|git_work_tree_cfg
op_assign
id|xcalloc
c_func
(paren
id|PATH_MAX
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|getcwd
c_func
(paren
id|git_work_tree_cfg
comma
id|PATH_MAX
)paren
)paren
id|die
(paren
l_string|&quot;Cannot access current working directory.&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|access
c_func
(paren
id|get_git_work_tree
c_func
(paren
)paren
comma
id|X_OK
)paren
)paren
id|die
(paren
l_string|&quot;Cannot access work tree &squot;%s&squot;&quot;
comma
id|get_git_work_tree
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|set_git_dir
c_func
(paren
id|make_absolute_path
c_func
(paren
id|git_dir
)paren
)paren
suffix:semicolon
r_return
id|init_db
c_func
(paren
id|template_dir
comma
id|flags
)paren
suffix:semicolon
)brace
eof
