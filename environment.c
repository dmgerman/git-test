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
DECL|variable|only_use_symrefs
r_int
id|only_use_symrefs
op_assign
l_int|0
suffix:semicolon
DECL|variable|repository_format_version
r_int
id|repository_format_version
op_assign
l_int|0
suffix:semicolon
DECL|variable|git_commit_encoding
r_char
id|git_commit_encoding
(braket
id|MAX_ENCODING_LENGTH
)braket
op_assign
l_string|&quot;utf-8&quot;
suffix:semicolon
DECL|variable|shared_repository
r_int
id|shared_repository
op_assign
l_int|0
suffix:semicolon
DECL|variable|git_dir
DECL|variable|git_object_dir
DECL|variable|git_index_file
DECL|variable|git_refs_dir
r_static
r_char
op_star
id|git_dir
comma
op_star
id|git_object_dir
comma
op_star
id|git_index_file
comma
op_star
id|git_refs_dir
comma
DECL|variable|git_graft_file
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
id|strdup
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
DECL|function|get_git_dir
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
