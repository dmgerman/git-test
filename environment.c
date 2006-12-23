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
DECL|variable|use_legacy_headers
r_int
id|use_legacy_headers
op_assign
l_int|1
suffix:semicolon
DECL|variable|trust_executable_bit
r_int
id|trust_executable_bit
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
DECL|variable|log_all_ref_updates
r_int
id|log_all_ref_updates
suffix:semicolon
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
r_char
op_star
id|git_commit_encoding
suffix:semicolon
DECL|variable|git_log_output_encoding
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
id|Z_DEFAULT_COMPRESSION
suffix:semicolon
DECL|variable|packed_git_limit
r_int
id|packed_git_limit
op_assign
l_int|256
op_star
l_int|1024
op_star
l_int|1024
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
id|log_all_ref_updates
op_assign
op_logical_neg
id|is_bare_git_dir
c_func
(paren
id|git_dir
)paren
suffix:semicolon
)brace
DECL|function|is_bare_git_dir
r_int
id|is_bare_git_dir
(paren
r_const
r_char
op_star
id|dir
)paren
(brace
r_const
r_char
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|dir
comma
id|DEFAULT_GIT_DIR_ENVIRONMENT
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|s
op_assign
id|strrchr
c_func
(paren
id|dir
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_return
op_logical_neg
id|s
op_logical_or
id|strcmp
c_func
(paren
id|s
op_plus
l_int|1
comma
id|DEFAULT_GIT_DIR_ENVIRONMENT
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
eof
