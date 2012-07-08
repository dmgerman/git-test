multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;parse-options.h&quot;
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
DECL|variable|init_is_bare_repository
r_static
r_int
id|init_is_bare_repository
op_assign
l_int|0
suffix:semicolon
DECL|variable|init_shared_repository
r_static
r_int
id|init_shared_repository
op_assign
l_int|1
suffix:semicolon
DECL|variable|init_db_template_dir
r_static
r_const
r_char
op_star
id|init_db_template_dir
suffix:semicolon
DECL|variable|git_link
r_static
r_const
r_char
op_star
id|git_link
suffix:semicolon
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
id|_
c_func
(paren
l_string|&quot;Could not make %s writable by group&quot;
)paren
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
multiline_comment|/* Note: if &quot;.git/hooks&quot; file exists in the repository being&n;&t; * re-initialized, /etc/core-git/templates/hooks/update would&n;&t; * cause &quot;git init&quot; to fail here.  I think this is sane but&n;&t; * it means that the set of templates we ship by default, along&n;&t; * with the way the namespace under .git/ is organized, should&n;&t; * be really carefully chosen.&n;&t; */
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
id|_
c_func
(paren
l_string|&quot;insanely long template name %s&quot;
)paren
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot stat &squot;%s&squot;&quot;
)paren
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot stat template &squot;%s&squot;&quot;
)paren
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot opendir &squot;%s&squot;&quot;
)paren
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot readlink &squot;%s&squot;&quot;
)paren
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
id|_
c_func
(paren
l_string|&quot;insanely long symlink %s&quot;
)paren
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot symlink &squot;%s&squot; &squot;%s&squot;&quot;
)paren
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot copy &squot;%s&squot; to &squot;%s&squot;&quot;
)paren
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
id|_
c_func
(paren
l_string|&quot;ignoring template %s&quot;
)paren
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
id|init_db_template_dir
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
r_if
c_cond
(paren
op_logical_neg
id|template_dir
(braket
l_int|0
)braket
)paren
r_return
suffix:semicolon
id|template_len
op_assign
id|strlen
c_func
(paren
id|template_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PATH_MAX
op_le
(paren
id|template_len
op_plus
id|strlen
c_func
(paren
l_string|&quot;/config&quot;
)paren
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;insanely long template path %s&quot;
)paren
comma
id|template_dir
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
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;templates not found %s&quot;
)paren
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
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;not copying templates of &quot;
l_string|&quot;a wrong format version %d from &squot;%s&squot;&quot;
)paren
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
DECL|function|git_init_db_config
r_static
r_int
id|git_init_db_config
c_func
(paren
r_const
r_char
op_star
id|k
comma
r_const
r_char
op_star
id|v
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|k
comma
l_string|&quot;init.templatedir&quot;
)paren
)paren
r_return
id|git_config_pathname
c_func
(paren
op_amp
id|init_db_template_dir
comma
id|k
comma
id|v
)paren
suffix:semicolon
r_return
l_int|0
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
id|_
c_func
(paren
l_string|&quot;insane git directory %s&quot;
)paren
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
multiline_comment|/* Just look for `init.templatedir` */
id|git_config
c_func
(paren
id|git_init_db_config
comma
l_int|NULL
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
id|is_bare_repository_cfg
op_assign
id|init_is_bare_repository
suffix:semicolon
multiline_comment|/* reading existing config may have overwrote it */
r_if
c_cond
(paren
id|init_shared_repository
op_ne
l_int|1
)paren
id|shared_repository
op_assign
id|init_shared_repository
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
id|probe_utf8_pathname_composition
c_func
(paren
id|path
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|reinit
suffix:semicolon
)brace
DECL|function|create_object_directory
r_static
r_void
id|create_object_directory
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|object_directory
op_assign
id|get_object_directory
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
id|object_directory
)paren
suffix:semicolon
r_char
op_star
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
id|object_directory
comma
id|len
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|object_directory
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
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
DECL|function|set_git_dir_init
r_int
id|set_git_dir_init
c_func
(paren
r_const
r_char
op_star
id|git_dir
comma
r_const
r_char
op_star
id|real_git_dir
comma
r_int
id|exist_ok
)paren
(brace
r_if
c_cond
(paren
id|real_git_dir
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exist_ok
op_logical_and
op_logical_neg
id|stat
c_func
(paren
id|git_dir
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s already exists&quot;
)paren
comma
id|git_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exist_ok
op_logical_and
op_logical_neg
id|stat
c_func
(paren
id|real_git_dir
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s already exists&quot;
)paren
comma
id|real_git_dir
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * make sure symlinks are resolved because we&squot;ll be&n;&t;&t; * moving the target repo later on in separate_git_dir()&n;&t;&t; */
id|git_link
op_assign
id|xstrdup
c_func
(paren
id|real_path
c_func
(paren
id|git_dir
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|real_git_dir
op_assign
id|real_path
c_func
(paren
id|git_dir
)paren
suffix:semicolon
id|git_link
op_assign
l_int|NULL
suffix:semicolon
)brace
id|set_git_dir
c_func
(paren
id|real_path
c_func
(paren
id|real_git_dir
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|separate_git_dir
r_static
r_void
id|separate_git_dir
c_func
(paren
r_const
r_char
op_star
id|git_dir
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
id|FILE
op_star
id|fp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|git_link
comma
op_amp
id|st
)paren
)paren
(brace
r_const
r_char
op_star
id|src
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
id|src
op_assign
id|read_gitfile
c_func
(paren
id|git_link
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
id|src
op_assign
id|git_link
suffix:semicolon
r_else
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to handle file type %d&quot;
)paren
comma
(paren
r_int
)paren
id|st.st_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|src
comma
id|git_dir
)paren
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unable to move %s to %s&quot;
)paren
comma
id|src
comma
id|git_dir
)paren
suffix:semicolon
)brace
id|fp
op_assign
id|fopen
c_func
(paren
id|git_link
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Could not create git link %s&quot;
)paren
comma
id|git_link
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;gitdir: %s&bslash;n&quot;
comma
id|git_dir
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
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
r_int
id|reinit
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
r_if
c_cond
(paren
id|git_link
)paren
id|separate_git_dir
c_func
(paren
id|git_dir
)paren
suffix:semicolon
id|safe_create_dir
c_func
(paren
id|git_dir
comma
l_int|0
)paren
suffix:semicolon
id|init_is_bare_repository
op_assign
id|is_bare_repository
c_func
(paren
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
id|create_object_directory
c_func
(paren
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
OL
l_int|0
)paren
multiline_comment|/* force to the mode value */
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
r_else
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
id|die
c_func
(paren
l_string|&quot;oops&quot;
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
multiline_comment|/*&n;&t;&t; * TRANSLATORS: The first &squot;%s&squot; is either &quot;Reinitialized&n;&t;&t; * existing&quot; or &quot;Initialized empty&quot;, the second &quot; shared&quot; or&n;&t;&t; * &quot;&quot;, and the last &squot;%s%s&squot; is the verbatim directory name.&n;&t;&t; */
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s%s Git repository in %s%s&bslash;n&quot;
)paren
comma
id|reinit
ques
c_cond
id|_
c_func
(paren
l_string|&quot;Reinitialized existing&quot;
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;Initialized empty&quot;
)paren
comma
id|shared_repository
ques
c_cond
id|_
c_func
(paren
l_string|&quot; shared&quot;
)paren
suffix:colon
l_string|&quot;&quot;
comma
id|git_dir
comma
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
ques
c_cond
l_string|&quot;/&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot tell cwd&quot;
)paren
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
DECL|function|shared_callback
r_static
r_int
id|shared_callback
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
op_star
(paren
(paren
r_int
op_star
)paren
id|opt-&gt;value
)paren
op_assign
(paren
id|arg
)paren
ques
c_cond
id|git_config_perm
c_func
(paren
l_string|&quot;arg&quot;
comma
id|arg
)paren
suffix:colon
id|PERM_GROUP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_db_usage
r_static
r_const
r_char
op_star
r_const
id|init_db_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git init [-q | --quiet] [--bare] [--template=&lt;template-directory&gt;] [--shared[=&lt;permissions&gt;]] [directory]&quot;
comma
l_int|NULL
)brace
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
id|real_git_dir
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|work_tree
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
r_const
r_struct
id|option
id|init_db_options
(braket
)braket
op_assign
(brace
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;template&quot;
comma
op_amp
id|template_dir
comma
l_string|&quot;template-directory&quot;
comma
l_string|&quot;directory from which templates will be used&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;bare&quot;
comma
op_amp
id|is_bare_repository_cfg
comma
l_string|&quot;create a bare repository&quot;
comma
l_int|1
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;shared&quot;
comma
op_amp
id|init_shared_repository
comma
l_string|&quot;permissions&quot;
comma
l_string|&quot;specify that the git repository is to be shared amongst several users&quot;
comma
id|PARSE_OPT_OPTARG
op_or
id|PARSE_OPT_NONEG
comma
id|shared_callback
comma
l_int|0
)brace
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;q&squot;
comma
l_string|&quot;quiet&quot;
comma
op_amp
id|flags
comma
l_string|&quot;be quiet&quot;
comma
id|INIT_DB_QUIET
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;separate-git-dir&quot;
comma
op_amp
id|real_git_dir
comma
l_string|&quot;gitdir&quot;
comma
l_string|&quot;separate git dir from working tree&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|init_db_options
comma
id|init_db_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|real_git_dir
op_logical_and
op_logical_neg
id|is_absolute_path
c_func
(paren
id|real_git_dir
)paren
)paren
id|real_git_dir
op_assign
id|xstrdup
c_func
(paren
id|real_path
c_func
(paren
id|real_git_dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
(brace
r_int
id|mkdir_tried
op_assign
l_int|0
suffix:semicolon
id|retry
suffix:colon
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mkdir_tried
)paren
(brace
r_int
id|saved
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * At this point we haven&squot;t read any configuration,&n;&t;&t;&t;&t; * and we know shared_repository should always be 0;&n;&t;&t;&t;&t; * but just in case we play safe.&n;&t;&t;&t;&t; */
id|saved
op_assign
id|shared_repository
suffix:semicolon
id|shared_repository
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|safe_create_leading_directories_const
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
)paren
(brace
r_case
l_int|3
suffix:colon
id|errno
op_assign
id|EEXIST
suffix:semicolon
multiline_comment|/* fallthru */
r_case
l_int|1
suffix:colon
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot mkdir %s&quot;
)paren
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|shared_repository
op_assign
id|saved
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_int|0777
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot mkdir %s&quot;
)paren
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|mkdir_tried
op_assign
l_int|1
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cannot chdir to %s&quot;
)paren
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
l_int|0
OL
id|argc
)paren
(brace
id|usage
c_func
(paren
id|init_db_usage
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_bare_repository_cfg
op_eq
l_int|1
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
id|argc
OG
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|init_shared_repository
op_ne
l_int|1
)paren
id|shared_repository
op_assign
id|init_shared_repository
suffix:semicolon
multiline_comment|/*&n;&t; * GIT_WORK_TREE makes sense only in conjunction with GIT_DIR&n;&t; * without --bare.  Catch the error early.&n;&t; */
id|git_dir
op_assign
id|getenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
id|work_tree
op_assign
id|getenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
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
id|work_tree
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s (or --work-tree=&lt;directory&gt;) not allowed without &quot;
l_string|&quot;specifying %s (or --git-dir=&lt;directory&gt;)&quot;
)paren
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
id|real_path
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
id|die_errno
(paren
id|_
c_func
(paren
l_string|&quot;Cannot access current working directory&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|work_tree
)paren
id|set_git_work_tree
c_func
(paren
id|real_path
c_func
(paren
id|work_tree
)paren
)paren
suffix:semicolon
r_else
id|set_git_work_tree
c_func
(paren
id|git_work_tree_cfg
)paren
suffix:semicolon
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
id|die_errno
(paren
id|_
c_func
(paren
l_string|&quot;Cannot access work tree &squot;%s&squot;&quot;
)paren
comma
id|get_git_work_tree
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
id|work_tree
)paren
id|set_git_work_tree
c_func
(paren
id|real_path
c_func
(paren
id|work_tree
)paren
)paren
suffix:semicolon
)brace
id|set_git_dir_init
c_func
(paren
id|git_dir
comma
id|real_git_dir
comma
l_int|1
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
