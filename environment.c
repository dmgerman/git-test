multiline_comment|/*&n; * We put all the git config variables in this same object&n; * file, so that programs can link against the config parser&n; * without having to link against all the rest of git.&n; *&n; * In particular, no need to bring in libz etc unless needed,&n; * even if you might want to know where the git directory etc&n; * are.&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|git_default_email
r_char
id|git_default_email
(braket
id|MAX_GITNAME
)braket
suffix:semicolon
DECL|variable|git_default_name
r_char
id|git_default_name
(braket
id|MAX_GITNAME
)braket
suffix:semicolon
DECL|variable|trust_executable_bit
r_int
id|trust_executable_bit
op_assign
l_int|1
suffix:semicolon
DECL|variable|quote_path_fully
r_int
id|quote_path_fully
op_assign
l_int|1
suffix:semicolon
DECL|variable|has_symlinks
r_int
id|has_symlinks
op_assign
l_int|1
suffix:semicolon
DECL|variable|assume_unchanged
r_int
id|assume_unchanged
suffix:semicolon
DECL|variable|prefer_symlink_refs
r_int
id|prefer_symlink_refs
suffix:semicolon
DECL|variable|is_bare_repository_cfg
r_int
id|is_bare_repository_cfg
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* unspecified */
DECL|variable|log_all_ref_updates
r_int
id|log_all_ref_updates
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* unspecified */
DECL|variable|warn_ambiguous_refs
r_int
id|warn_ambiguous_refs
op_assign
l_int|1
suffix:semicolon
DECL|variable|repository_format_version
r_int
id|repository_format_version
suffix:semicolon
DECL|variable|git_commit_encoding
r_const
r_char
op_star
id|git_commit_encoding
suffix:semicolon
DECL|variable|git_log_output_encoding
r_const
r_char
op_star
id|git_log_output_encoding
suffix:semicolon
DECL|variable|shared_repository
r_int
id|shared_repository
op_assign
id|PERM_UMASK
suffix:semicolon
DECL|variable|apply_default_whitespace
r_const
r_char
op_star
id|apply_default_whitespace
suffix:semicolon
DECL|variable|zlib_compression_level
r_int
id|zlib_compression_level
op_assign
id|Z_BEST_SPEED
suffix:semicolon
DECL|variable|core_compression_level
r_int
id|core_compression_level
suffix:semicolon
DECL|variable|core_compression_seen
r_int
id|core_compression_seen
suffix:semicolon
DECL|variable|packed_git_window_size
r_int
id|packed_git_window_size
op_assign
id|DEFAULT_PACKED_GIT_WINDOW_SIZE
suffix:semicolon
DECL|variable|packed_git_limit
r_int
id|packed_git_limit
op_assign
id|DEFAULT_PACKED_GIT_LIMIT
suffix:semicolon
DECL|variable|delta_base_cache_limit
r_int
id|delta_base_cache_limit
op_assign
l_int|16
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
DECL|variable|pager_program
r_char
op_star
id|pager_program
suffix:semicolon
DECL|variable|pager_in_use
r_int
id|pager_in_use
suffix:semicolon
DECL|variable|pager_use_color
r_int
id|pager_use_color
op_assign
l_int|1
suffix:semicolon
DECL|variable|editor_program
r_char
op_star
id|editor_program
suffix:semicolon
DECL|variable|auto_crlf
r_int
id|auto_crlf
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 1: both ways, -1: only when adding git objects */
DECL|variable|whitespace_rule_cfg
r_int
id|whitespace_rule_cfg
op_assign
id|WS_DEFAULT_RULE
suffix:semicolon
multiline_comment|/* This is set by setup_git_dir_gently() and/or git_default_config() */
DECL|variable|git_work_tree_cfg
r_char
op_star
id|git_work_tree_cfg
suffix:semicolon
DECL|variable|work_tree
r_static
r_const
r_char
op_star
id|work_tree
suffix:semicolon
DECL|variable|git_dir
r_static
r_const
r_char
op_star
id|git_dir
suffix:semicolon
DECL|variable|git_object_dir
DECL|variable|git_index_file
DECL|variable|git_refs_dir
DECL|variable|git_graft_file
r_static
r_char
op_star
id|git_object_dir
comma
op_star
id|git_index_file
comma
op_star
id|git_refs_dir
comma
op_star
id|git_graft_file
suffix:semicolon
DECL|function|setup_git_env
r_static
r_void
id|setup_git_env
c_func
(paren
r_void
)paren
(brace
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
op_logical_neg
id|git_dir
)paren
id|git_dir
op_assign
id|DEFAULT_GIT_DIR_ENVIRONMENT
suffix:semicolon
id|git_object_dir
op_assign
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_object_dir
)paren
(brace
id|git_object_dir
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|git_dir
)paren
op_plus
l_int|9
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|git_object_dir
comma
l_string|&quot;%s/objects&quot;
comma
id|git_dir
)paren
suffix:semicolon
)brace
id|git_refs_dir
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|git_dir
)paren
op_plus
l_int|6
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|git_refs_dir
comma
l_string|&quot;%s/refs&quot;
comma
id|git_dir
)paren
suffix:semicolon
id|git_index_file
op_assign
id|getenv
c_func
(paren
id|INDEX_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_index_file
)paren
(brace
id|git_index_file
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|git_dir
)paren
op_plus
l_int|7
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|git_index_file
comma
l_string|&quot;%s/index&quot;
comma
id|git_dir
)paren
suffix:semicolon
)brace
id|git_graft_file
op_assign
id|getenv
c_func
(paren
id|GRAFT_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_graft_file
)paren
id|git_graft_file
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;info/grafts&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|is_bare_repository
r_int
id|is_bare_repository
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* if core.bare is not &squot;false&squot;, let&squot;s see if there is a work tree */
r_return
id|is_bare_repository_cfg
op_logical_and
op_logical_neg
id|get_git_work_tree
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_git_dir
r_const
r_char
op_star
id|get_git_dir
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_dir
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_dir
suffix:semicolon
)brace
DECL|function|get_git_work_tree
r_const
r_char
op_star
id|get_git_work_tree
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
id|work_tree
op_assign
id|getenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
)paren
suffix:semicolon
multiline_comment|/* core.bare = true overrides implicit and config work tree */
r_if
c_cond
(paren
op_logical_neg
id|work_tree
op_logical_and
id|is_bare_repository_cfg
OL
l_int|1
)paren
(brace
id|work_tree
op_assign
id|git_work_tree_cfg
suffix:semicolon
multiline_comment|/* make_absolute_path also normalizes the path */
r_if
c_cond
(paren
id|work_tree
op_logical_and
op_logical_neg
id|is_absolute_path
c_func
(paren
id|work_tree
)paren
)paren
id|work_tree
op_assign
id|xstrdup
c_func
(paren
id|make_absolute_path
c_func
(paren
id|git_path
c_func
(paren
id|work_tree
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|work_tree
)paren
id|work_tree
op_assign
id|xstrdup
c_func
(paren
id|make_absolute_path
c_func
(paren
id|work_tree
)paren
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|work_tree
)paren
id|is_bare_repository_cfg
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|work_tree
suffix:semicolon
)brace
DECL|function|get_object_directory
r_char
op_star
id|get_object_directory
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_object_dir
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_object_dir
suffix:semicolon
)brace
DECL|function|get_refs_directory
r_char
op_star
id|get_refs_directory
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_refs_dir
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_refs_dir
suffix:semicolon
)brace
DECL|function|get_index_file
r_char
op_star
id|get_index_file
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_index_file
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_index_file
suffix:semicolon
)brace
DECL|function|get_graft_file
r_char
op_star
id|get_graft_file
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_graft_file
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
id|git_graft_file
suffix:semicolon
)brace
DECL|function|set_git_dir
r_int
id|set_git_dir
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
id|setenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
comma
id|path
comma
l_int|1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not set GIT_DIR to &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
