multiline_comment|/*&n; * We put all the git config variables in this same object&n; * file, so that programs can link against the config parser&n; * without having to link against all the rest of git.&n; *&n; * In particular, no need to bring in libz etc unless needed,&n; * even if you might want to know where the git directory etc&n; * are.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;fmt-merge-msg.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|variable|trust_executable_bit
r_int
id|trust_executable_bit
op_assign
l_int|1
suffix:semicolon
DECL|variable|trust_ctime
r_int
id|trust_ctime
op_assign
l_int|1
suffix:semicolon
DECL|variable|check_stat
r_int
id|check_stat
op_assign
l_int|1
suffix:semicolon
DECL|variable|has_symlinks
r_int
id|has_symlinks
op_assign
l_int|1
suffix:semicolon
DECL|variable|minimum_abbrev
DECL|variable|default_abbrev
r_int
id|minimum_abbrev
op_assign
l_int|4
comma
id|default_abbrev
op_assign
l_int|7
suffix:semicolon
DECL|variable|ignore_case
r_int
id|ignore_case
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
DECL|variable|warn_on_object_refname_ambiguity
r_int
id|warn_on_object_refname_ambiguity
op_assign
l_int|1
suffix:semicolon
DECL|variable|ref_paranoia
r_int
id|ref_paranoia
op_assign
l_int|1
suffix:semicolon
DECL|variable|repository_format_version
r_int
id|repository_format_version
suffix:semicolon
DECL|variable|repository_format_precious_objects
r_int
id|repository_format_precious_objects
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
DECL|variable|apply_default_ignorewhitespace
r_const
r_char
op_star
id|apply_default_ignorewhitespace
suffix:semicolon
DECL|variable|git_attributes_file
r_const
r_char
op_star
id|git_attributes_file
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
DECL|variable|fsync_object_files
r_int
id|fsync_object_files
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
l_int|96
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
DECL|variable|big_file_threshold
r_int
r_int
id|big_file_threshold
op_assign
l_int|512
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
DECL|variable|pager_program
r_const
r_char
op_star
id|pager_program
suffix:semicolon
DECL|variable|pager_use_color
r_int
id|pager_use_color
op_assign
l_int|1
suffix:semicolon
DECL|variable|editor_program
r_const
r_char
op_star
id|editor_program
suffix:semicolon
DECL|variable|askpass_program
r_const
r_char
op_star
id|askpass_program
suffix:semicolon
DECL|variable|excludes_file
r_const
r_char
op_star
id|excludes_file
suffix:semicolon
DECL|variable|auto_crlf
r_enum
id|auto_crlf
id|auto_crlf
op_assign
id|AUTO_CRLF_FALSE
suffix:semicolon
DECL|variable|check_replace_refs
r_int
id|check_replace_refs
op_assign
l_int|1
suffix:semicolon
DECL|variable|git_replace_ref_base
r_char
op_star
id|git_replace_ref_base
suffix:semicolon
DECL|variable|core_eol
r_enum
id|eol
id|core_eol
op_assign
id|EOL_UNSET
suffix:semicolon
DECL|variable|safe_crlf
r_enum
id|safe_crlf
id|safe_crlf
op_assign
id|SAFE_CRLF_WARN
suffix:semicolon
DECL|variable|whitespace_rule_cfg
r_int
id|whitespace_rule_cfg
op_assign
id|WS_DEFAULT_RULE
suffix:semicolon
DECL|variable|git_branch_track
r_enum
id|branch_track
id|git_branch_track
op_assign
id|BRANCH_TRACK_REMOTE
suffix:semicolon
DECL|variable|autorebase
r_enum
id|rebase_setup_type
id|autorebase
op_assign
id|AUTOREBASE_NEVER
suffix:semicolon
DECL|variable|push_default
r_enum
id|push_default_type
id|push_default
op_assign
id|PUSH_DEFAULT_UNSPECIFIED
suffix:semicolon
macro_line|#ifndef OBJECT_CREATION_MODE
DECL|macro|OBJECT_CREATION_MODE
mdefine_line|#define OBJECT_CREATION_MODE OBJECT_CREATION_USES_HARDLINKS
macro_line|#endif
DECL|variable|object_creation_mode
r_enum
id|object_creation_mode
id|object_creation_mode
op_assign
id|OBJECT_CREATION_MODE
suffix:semicolon
DECL|variable|notes_ref_name
r_char
op_star
id|notes_ref_name
suffix:semicolon
DECL|variable|grafts_replace_parents
r_int
id|grafts_replace_parents
op_assign
l_int|1
suffix:semicolon
DECL|variable|core_apply_sparse_checkout
r_int
id|core_apply_sparse_checkout
suffix:semicolon
DECL|variable|merge_log_config
r_int
id|merge_log_config
op_assign
l_int|1
suffix:semicolon
DECL|variable|precomposed_unicode
r_int
id|precomposed_unicode
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* see probe_utf8_pathname_composition() */
DECL|variable|startup_info
r_struct
id|startup_info
op_star
id|startup_info
suffix:semicolon
DECL|variable|pack_size_limit_cfg
r_int
r_int
id|pack_size_limit_cfg
suffix:semicolon
macro_line|#ifndef PROTECT_HFS_DEFAULT
DECL|macro|PROTECT_HFS_DEFAULT
mdefine_line|#define PROTECT_HFS_DEFAULT 0
macro_line|#endif
DECL|variable|protect_hfs
r_int
id|protect_hfs
op_assign
id|PROTECT_HFS_DEFAULT
suffix:semicolon
macro_line|#ifndef PROTECT_NTFS_DEFAULT
DECL|macro|PROTECT_NTFS_DEFAULT
mdefine_line|#define PROTECT_NTFS_DEFAULT 0
macro_line|#endif
DECL|variable|protect_ntfs
r_int
id|protect_ntfs
op_assign
id|PROTECT_NTFS_DEFAULT
suffix:semicolon
multiline_comment|/*&n; * The character that begins a commented line in user-editable file&n; * that is subject to stripspace.&n; */
DECL|variable|comment_line_char
r_char
id|comment_line_char
op_assign
l_char|&squot;#&squot;
suffix:semicolon
DECL|variable|auto_comment_line_char
r_int
id|auto_comment_line_char
suffix:semicolon
multiline_comment|/* Parallel index stat data preload? */
DECL|variable|core_preload_index
r_int
id|core_preload_index
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* This is set by setup_git_dir_gently() and/or git_default_config() */
DECL|variable|git_work_tree_cfg
r_char
op_star
id|git_work_tree_cfg
suffix:semicolon
DECL|variable|work_tree
r_static
r_char
op_star
id|work_tree
suffix:semicolon
DECL|variable|namespace
r_static
r_const
r_char
op_star
r_namespace
suffix:semicolon
DECL|variable|namespace_len
r_static
r_int
id|namespace_len
suffix:semicolon
DECL|variable|git_dir
DECL|variable|git_common_dir
r_static
r_const
r_char
op_star
id|git_dir
comma
op_star
id|git_common_dir
suffix:semicolon
DECL|variable|git_object_dir
DECL|variable|git_index_file
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
id|git_graft_file
suffix:semicolon
DECL|variable|git_db_env
DECL|variable|git_index_env
DECL|variable|git_graft_env
DECL|variable|git_common_dir_env
r_int
id|git_db_env
comma
id|git_index_env
comma
id|git_graft_env
comma
id|git_common_dir_env
suffix:semicolon
multiline_comment|/*&n; * Repository-local GIT_* environment variables; see cache.h for details.&n; */
DECL|variable|local_repo_env
r_const
r_char
op_star
r_const
id|local_repo_env
(braket
)braket
op_assign
(brace
id|ALTERNATE_DB_ENVIRONMENT
comma
id|CONFIG_ENVIRONMENT
comma
id|CONFIG_DATA_ENVIRONMENT
comma
id|DB_ENVIRONMENT
comma
id|GIT_DIR_ENVIRONMENT
comma
id|GIT_WORK_TREE_ENVIRONMENT
comma
id|GIT_IMPLICIT_WORK_TREE_ENVIRONMENT
comma
id|GRAFT_ENVIRONMENT
comma
id|INDEX_ENVIRONMENT
comma
id|NO_REPLACE_OBJECTS_ENVIRONMENT
comma
id|GIT_REPLACE_REF_BASE_ENVIRONMENT
comma
id|GIT_PREFIX_ENVIRONMENT
comma
id|GIT_SHALLOW_FILE_ENVIRONMENT
comma
id|GIT_COMMON_DIR_ENVIRONMENT
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|expand_namespace
r_static
r_char
op_star
id|expand_namespace
c_func
(paren
r_const
r_char
op_star
id|raw_namespace
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
op_star
op_star
id|components
comma
op_star
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_namespace
op_logical_or
op_logical_neg
op_star
id|raw_namespace
)paren
r_return
id|xstrdup
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|raw_namespace
)paren
suffix:semicolon
id|components
op_assign
id|strbuf_split
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
id|components
suffix:semicolon
op_star
id|c
suffix:semicolon
id|c
op_increment
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
(paren
op_star
id|c
)paren
op_member_access_from_pointer
id|buf
comma
l_string|&quot;/&quot;
)paren
op_ne
l_int|0
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;refs/namespaces/%s&quot;
comma
(paren
op_star
id|c
)paren
op_member_access_from_pointer
id|buf
)paren
suffix:semicolon
id|strbuf_list_free
c_func
(paren
id|components
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_refname_format
c_func
(paren
id|buf.buf
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
l_string|&quot;bad git namespace path &bslash;&quot;%s&bslash;&quot;&quot;
comma
id|raw_namespace
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|git_path_from_env
r_static
r_char
op_star
id|git_path_from_env
c_func
(paren
r_const
r_char
op_star
id|envvar
comma
r_const
r_char
op_star
id|git_dir
comma
r_const
r_char
op_star
id|path
comma
r_int
op_star
id|fromenv
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|getenv
c_func
(paren
id|envvar
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|xstrfmt
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
id|git_dir
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fromenv
)paren
op_star
id|fromenv
op_assign
l_int|1
suffix:semicolon
r_return
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
DECL|function|setup_git_env
r_static
r_void
id|setup_git_env
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|gitfile
suffix:semicolon
r_const
r_char
op_star
id|shallow_file
suffix:semicolon
r_const
r_char
op_star
id|replace_ref_base
suffix:semicolon
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
id|gitfile
op_assign
id|read_gitfile
c_func
(paren
id|git_dir
)paren
suffix:semicolon
id|git_dir
op_assign
id|xstrdup
c_func
(paren
id|gitfile
ques
c_cond
id|gitfile
suffix:colon
id|git_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_common_dir
c_func
(paren
op_amp
id|sb
comma
id|git_dir
)paren
)paren
id|git_common_dir_env
op_assign
l_int|1
suffix:semicolon
id|git_common_dir
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|sb
comma
l_int|NULL
)paren
suffix:semicolon
id|git_object_dir
op_assign
id|git_path_from_env
c_func
(paren
id|DB_ENVIRONMENT
comma
id|git_common_dir
comma
l_string|&quot;objects&quot;
comma
op_amp
id|git_db_env
)paren
suffix:semicolon
id|git_index_file
op_assign
id|git_path_from_env
c_func
(paren
id|INDEX_ENVIRONMENT
comma
id|git_dir
comma
l_string|&quot;index&quot;
comma
op_amp
id|git_index_env
)paren
suffix:semicolon
id|git_graft_file
op_assign
id|git_path_from_env
c_func
(paren
id|GRAFT_ENVIRONMENT
comma
id|git_common_dir
comma
l_string|&quot;info/grafts&quot;
comma
op_amp
id|git_graft_env
)paren
suffix:semicolon
r_if
c_cond
(paren
id|getenv
c_func
(paren
id|NO_REPLACE_OBJECTS_ENVIRONMENT
)paren
)paren
id|check_replace_refs
op_assign
l_int|0
suffix:semicolon
id|replace_ref_base
op_assign
id|getenv
c_func
(paren
id|GIT_REPLACE_REF_BASE_ENVIRONMENT
)paren
suffix:semicolon
id|git_replace_ref_base
op_assign
id|xstrdup
c_func
(paren
id|replace_ref_base
ques
c_cond
id|replace_ref_base
suffix:colon
l_string|&quot;refs/replace/&quot;
)paren
suffix:semicolon
r_namespace
op_assign
id|expand_namespace
c_func
(paren
id|getenv
c_func
(paren
id|GIT_NAMESPACE_ENVIRONMENT
)paren
)paren
suffix:semicolon
id|namespace_len
op_assign
id|strlen
c_func
(paren
r_namespace
)paren
suffix:semicolon
id|shallow_file
op_assign
id|getenv
c_func
(paren
id|GIT_SHALLOW_FILE_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shallow_file
)paren
id|set_alternate_shallow_file
c_func
(paren
id|shallow_file
comma
l_int|0
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
DECL|function|get_git_common_dir
r_const
r_char
op_star
id|get_git_common_dir
c_func
(paren
r_void
)paren
(brace
r_return
id|git_common_dir
suffix:semicolon
)brace
DECL|function|get_git_namespace
r_const
r_char
op_star
id|get_git_namespace
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
r_namespace
)paren
id|setup_git_env
c_func
(paren
)paren
suffix:semicolon
r_return
r_namespace
suffix:semicolon
)brace
DECL|function|strip_namespace
r_const
r_char
op_star
id|strip_namespace
c_func
(paren
r_const
r_char
op_star
id|namespaced_ref
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|starts_with
c_func
(paren
id|namespaced_ref
comma
id|get_git_namespace
c_func
(paren
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|namespaced_ref
op_plus
id|namespace_len
suffix:semicolon
)brace
DECL|variable|git_work_tree_initialized
r_static
r_int
id|git_work_tree_initialized
suffix:semicolon
multiline_comment|/*&n; * Note.  This works only before you used a work tree.  This was added&n; * primarily to support git-clone to work in a new repository it just&n; * created, and is not meant to flip between different work trees.&n; */
DECL|function|set_git_work_tree
r_void
id|set_git_work_tree
c_func
(paren
r_const
r_char
op_star
id|new_work_tree
)paren
(brace
r_if
c_cond
(paren
id|git_work_tree_initialized
)paren
(brace
id|new_work_tree
op_assign
id|real_path
c_func
(paren
id|new_work_tree
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|new_work_tree
comma
id|work_tree
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error: work tree has already been set&bslash;n&quot;
l_string|&quot;Current worktree: %s&bslash;nNew worktree: %s&quot;
comma
id|work_tree
comma
id|new_work_tree
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|git_work_tree_initialized
op_assign
l_int|1
suffix:semicolon
id|work_tree
op_assign
id|xstrdup
c_func
(paren
id|real_path
c_func
(paren
id|new_work_tree
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setenv
c_func
(paren
id|GIT_WORK_TREE_ENVIRONMENT
comma
id|work_tree
comma
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;could not set GIT_WORK_TREE to &squot;%s&squot;&quot;
comma
id|work_tree
)paren
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
DECL|function|odb_mkstemp
r_int
id|odb_mkstemp
c_func
(paren
r_char
op_star
r_template
comma
r_int
id|limit
comma
r_const
r_char
op_star
id|pattern
)paren
(brace
r_int
id|fd
suffix:semicolon
multiline_comment|/*&n;&t; * we let the umask do its job, don&squot;t try to be more&n;&t; * restrictive except to remove write permission.&n;&t; */
r_int
id|mode
op_assign
l_int|0444
suffix:semicolon
id|snprintf
c_func
(paren
r_template
comma
id|limit
comma
l_string|&quot;%s/%s&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|pattern
)paren
suffix:semicolon
id|fd
op_assign
id|git_mkstemp_mode
c_func
(paren
r_template
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|fd
)paren
r_return
id|fd
suffix:semicolon
multiline_comment|/* slow path */
multiline_comment|/* some mkstemp implementations erase template on failure */
id|snprintf
c_func
(paren
r_template
comma
id|limit
comma
l_string|&quot;%s/%s&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|pattern
)paren
suffix:semicolon
id|safe_create_leading_directories
c_func
(paren
r_template
)paren
suffix:semicolon
r_return
id|xmkstemp_mode
c_func
(paren
r_template
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|odb_pack_keep
r_int
id|odb_pack_keep
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|namesz
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|fd
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|namesz
comma
l_string|&quot;%s/pack/pack-%s.keep&quot;
comma
id|get_object_directory
c_func
(paren
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|name
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0600
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|fd
)paren
r_return
id|fd
suffix:semicolon
multiline_comment|/* slow path */
id|safe_create_leading_directories
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|open
c_func
(paren
id|name
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0600
)paren
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
DECL|function|get_log_output_encoding
r_const
r_char
op_star
id|get_log_output_encoding
c_func
(paren
r_void
)paren
(brace
r_return
id|git_log_output_encoding
ques
c_cond
id|git_log_output_encoding
suffix:colon
id|get_commit_output_encoding
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_commit_output_encoding
r_const
r_char
op_star
id|get_commit_output_encoding
c_func
(paren
r_void
)paren
(brace
r_return
id|git_commit_encoding
ques
c_cond
id|git_commit_encoding
suffix:colon
l_string|&quot;UTF-8&quot;
suffix:semicolon
)brace
eof
