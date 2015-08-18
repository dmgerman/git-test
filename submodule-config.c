macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;submodule-config.h&quot;
macro_line|#include &quot;submodule.h&quot;
macro_line|#include &quot;strbuf.h&quot;
multiline_comment|/*&n; * submodule cache lookup structure&n; * There is one shared set of &squot;struct submodule&squot; entries which can be&n; * looked up by their sha1 blob id of the .gitmodule file and either&n; * using path or name as key.&n; * for_path stores submodule entries with path as key&n; * for_name stores submodule entries with name as key&n; */
DECL|struct|submodule_cache
r_struct
id|submodule_cache
(brace
DECL|member|for_path
r_struct
id|hashmap
id|for_path
suffix:semicolon
DECL|member|for_name
r_struct
id|hashmap
id|for_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * thin wrapper struct needed to insert &squot;struct submodule&squot; entries to&n; * the hashmap&n; */
DECL|struct|submodule_entry
r_struct
id|submodule_entry
(brace
DECL|member|ent
r_struct
id|hashmap_entry
id|ent
suffix:semicolon
DECL|member|config
r_struct
id|submodule
op_star
id|config
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|lookup_type
r_enum
id|lookup_type
(brace
DECL|enumerator|lookup_name
id|lookup_name
comma
DECL|enumerator|lookup_path
id|lookup_path
)brace
suffix:semicolon
DECL|variable|cache
r_static
r_struct
id|submodule_cache
id|cache
suffix:semicolon
DECL|variable|is_cache_init
r_static
r_int
id|is_cache_init
suffix:semicolon
DECL|function|config_path_cmp
r_static
r_int
id|config_path_cmp
c_func
(paren
r_const
r_struct
id|submodule_entry
op_star
id|a
comma
r_const
r_struct
id|submodule_entry
op_star
id|b
comma
r_const
r_void
op_star
id|unused
)paren
(brace
r_return
id|strcmp
c_func
(paren
id|a-&gt;config-&gt;path
comma
id|b-&gt;config-&gt;path
)paren
op_logical_or
id|hashcmp
c_func
(paren
id|a-&gt;config-&gt;gitmodules_sha1
comma
id|b-&gt;config-&gt;gitmodules_sha1
)paren
suffix:semicolon
)brace
DECL|function|config_name_cmp
r_static
r_int
id|config_name_cmp
c_func
(paren
r_const
r_struct
id|submodule_entry
op_star
id|a
comma
r_const
r_struct
id|submodule_entry
op_star
id|b
comma
r_const
r_void
op_star
id|unused
)paren
(brace
r_return
id|strcmp
c_func
(paren
id|a-&gt;config-&gt;name
comma
id|b-&gt;config-&gt;name
)paren
op_logical_or
id|hashcmp
c_func
(paren
id|a-&gt;config-&gt;gitmodules_sha1
comma
id|b-&gt;config-&gt;gitmodules_sha1
)paren
suffix:semicolon
)brace
DECL|function|cache_init
r_static
r_void
id|cache_init
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
)paren
(brace
id|hashmap_init
c_func
(paren
op_amp
id|cache-&gt;for_path
comma
(paren
id|hashmap_cmp_fn
)paren
id|config_path_cmp
comma
l_int|0
)paren
suffix:semicolon
id|hashmap_init
c_func
(paren
op_amp
id|cache-&gt;for_name
comma
(paren
id|hashmap_cmp_fn
)paren
id|config_name_cmp
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|free_one_config
r_static
r_void
id|free_one_config
c_func
(paren
r_struct
id|submodule_entry
op_star
id|entry
)paren
(brace
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|entry-&gt;config-&gt;path
)paren
suffix:semicolon
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|entry-&gt;config-&gt;name
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry-&gt;config
)paren
suffix:semicolon
)brace
DECL|function|cache_free
r_static
r_void
id|cache_free
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
)paren
(brace
r_struct
id|hashmap_iter
id|iter
suffix:semicolon
r_struct
id|submodule_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/*&n;&t; * We iterate over the name hash here to be symmetric with the&n;&t; * allocation of struct submodule entries. Each is allocated by&n;&t; * their .gitmodule blob sha1 and submodule name.&n;&t; */
id|hashmap_iter_init
c_func
(paren
op_amp
id|cache-&gt;for_name
comma
op_amp
id|iter
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|hashmap_iter_next
c_func
(paren
op_amp
id|iter
)paren
)paren
)paren
id|free_one_config
c_func
(paren
id|entry
)paren
suffix:semicolon
id|hashmap_free
c_func
(paren
op_amp
id|cache-&gt;for_path
comma
l_int|1
)paren
suffix:semicolon
id|hashmap_free
c_func
(paren
op_amp
id|cache-&gt;for_name
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|hash_sha1_string
r_static
r_int
r_int
id|hash_sha1_string
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_return
id|memhash
c_func
(paren
id|sha1
comma
l_int|20
)paren
op_plus
id|strhash
c_func
(paren
id|string
)paren
suffix:semicolon
)brace
DECL|function|cache_put_path
r_static
r_void
id|cache_put_path
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_struct
id|submodule
op_star
id|submodule
)paren
(brace
r_int
r_int
id|hash
op_assign
id|hash_sha1_string
c_func
(paren
id|submodule-&gt;gitmodules_sha1
comma
id|submodule-&gt;path
)paren
suffix:semicolon
r_struct
id|submodule_entry
op_star
id|e
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|e
)paren
)paren
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
id|e
comma
id|hash
)paren
suffix:semicolon
id|e-&gt;config
op_assign
id|submodule
suffix:semicolon
id|hashmap_put
c_func
(paren
op_amp
id|cache-&gt;for_path
comma
id|e
)paren
suffix:semicolon
)brace
DECL|function|cache_remove_path
r_static
r_void
id|cache_remove_path
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_struct
id|submodule
op_star
id|submodule
)paren
(brace
r_int
r_int
id|hash
op_assign
id|hash_sha1_string
c_func
(paren
id|submodule-&gt;gitmodules_sha1
comma
id|submodule-&gt;path
)paren
suffix:semicolon
r_struct
id|submodule_entry
id|e
suffix:semicolon
r_struct
id|submodule_entry
op_star
id|removed
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
op_amp
id|e
comma
id|hash
)paren
suffix:semicolon
id|e.config
op_assign
id|submodule
suffix:semicolon
id|removed
op_assign
id|hashmap_remove
c_func
(paren
op_amp
id|cache-&gt;for_path
comma
op_amp
id|e
comma
l_int|NULL
)paren
suffix:semicolon
id|free
c_func
(paren
id|removed
)paren
suffix:semicolon
)brace
DECL|function|cache_add
r_static
r_void
id|cache_add
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_struct
id|submodule
op_star
id|submodule
)paren
(brace
r_int
r_int
id|hash
op_assign
id|hash_sha1_string
c_func
(paren
id|submodule-&gt;gitmodules_sha1
comma
id|submodule-&gt;name
)paren
suffix:semicolon
r_struct
id|submodule_entry
op_star
id|e
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|e
)paren
)paren
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
id|e
comma
id|hash
)paren
suffix:semicolon
id|e-&gt;config
op_assign
id|submodule
suffix:semicolon
id|hashmap_add
c_func
(paren
op_amp
id|cache-&gt;for_name
comma
id|e
)paren
suffix:semicolon
)brace
DECL|function|cache_lookup_path
r_static
r_const
r_struct
id|submodule
op_star
id|cache_lookup_path
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_const
r_int
r_char
op_star
id|gitmodules_sha1
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|submodule_entry
op_star
id|entry
suffix:semicolon
r_int
r_int
id|hash
op_assign
id|hash_sha1_string
c_func
(paren
id|gitmodules_sha1
comma
id|path
)paren
suffix:semicolon
r_struct
id|submodule_entry
id|key
suffix:semicolon
r_struct
id|submodule
id|key_config
suffix:semicolon
id|hashcpy
c_func
(paren
id|key_config.gitmodules_sha1
comma
id|gitmodules_sha1
)paren
suffix:semicolon
id|key_config.path
op_assign
id|path
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
op_amp
id|key
comma
id|hash
)paren
suffix:semicolon
id|key.config
op_assign
op_amp
id|key_config
suffix:semicolon
id|entry
op_assign
id|hashmap_get
c_func
(paren
op_amp
id|cache-&gt;for_path
comma
op_amp
id|key
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
r_return
id|entry-&gt;config
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|cache_lookup_name
r_static
r_struct
id|submodule
op_star
id|cache_lookup_name
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_const
r_int
r_char
op_star
id|gitmodules_sha1
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|submodule_entry
op_star
id|entry
suffix:semicolon
r_int
r_int
id|hash
op_assign
id|hash_sha1_string
c_func
(paren
id|gitmodules_sha1
comma
id|name
)paren
suffix:semicolon
r_struct
id|submodule_entry
id|key
suffix:semicolon
r_struct
id|submodule
id|key_config
suffix:semicolon
id|hashcpy
c_func
(paren
id|key_config.gitmodules_sha1
comma
id|gitmodules_sha1
)paren
suffix:semicolon
id|key_config.name
op_assign
id|name
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
op_amp
id|key
comma
id|hash
)paren
suffix:semicolon
id|key.config
op_assign
op_amp
id|key_config
suffix:semicolon
id|entry
op_assign
id|hashmap_get
c_func
(paren
op_amp
id|cache-&gt;for_name
comma
op_amp
id|key
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
r_return
id|entry-&gt;config
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|name_and_item_from_var
r_static
r_int
id|name_and_item_from_var
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_struct
id|strbuf
op_star
id|name
comma
r_struct
id|strbuf
op_star
id|item
)paren
(brace
r_const
r_char
op_star
id|subsection
comma
op_star
id|key
suffix:semicolon
r_int
id|subsection_len
comma
id|parse
suffix:semicolon
id|parse
op_assign
id|parse_config_key
c_func
(paren
id|var
comma
l_string|&quot;submodule&quot;
comma
op_amp
id|subsection
comma
op_amp
id|subsection_len
comma
op_amp
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse
OL
l_int|0
op_logical_or
op_logical_neg
id|subsection
)paren
r_return
l_int|0
suffix:semicolon
id|strbuf_add
c_func
(paren
id|name
comma
id|subsection
comma
id|subsection_len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|item
comma
id|key
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|lookup_or_create_by_name
r_static
r_struct
id|submodule
op_star
id|lookup_or_create_by_name
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_const
r_int
r_char
op_star
id|gitmodules_sha1
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|submodule
op_star
id|submodule
suffix:semicolon
r_struct
id|strbuf
id|name_buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|submodule
op_assign
id|cache_lookup_name
c_func
(paren
id|cache
comma
id|gitmodules_sha1
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|submodule
)paren
r_return
id|submodule
suffix:semicolon
id|submodule
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|submodule
)paren
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|name_buf
comma
id|name
)paren
suffix:semicolon
id|submodule-&gt;name
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|name_buf
comma
l_int|NULL
)paren
suffix:semicolon
id|submodule-&gt;path
op_assign
l_int|NULL
suffix:semicolon
id|submodule-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|submodule-&gt;fetch_recurse
op_assign
id|RECURSE_SUBMODULES_NONE
suffix:semicolon
id|submodule-&gt;ignore
op_assign
l_int|NULL
suffix:semicolon
id|hashcpy
c_func
(paren
id|submodule-&gt;gitmodules_sha1
comma
id|gitmodules_sha1
)paren
suffix:semicolon
id|cache_add
c_func
(paren
id|cache
comma
id|submodule
)paren
suffix:semicolon
r_return
id|submodule
suffix:semicolon
)brace
DECL|function|warn_multiple_config
r_static
r_void
id|warn_multiple_config
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|option
)paren
(brace
r_const
r_char
op_star
id|commit_string
op_assign
l_string|&quot;WORKTREE&quot;
suffix:semicolon
r_if
c_cond
(paren
id|commit_sha1
)paren
id|commit_string
op_assign
id|sha1_to_hex
c_func
(paren
id|commit_sha1
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;%s:.gitmodules, multiple configurations found for &quot;
l_string|&quot;&squot;submodule.%s.%s&squot;. Skipping second one!&quot;
comma
id|commit_string
comma
id|name
comma
id|option
)paren
suffix:semicolon
)brace
DECL|struct|parse_config_parameter
r_struct
id|parse_config_parameter
(brace
DECL|member|cache
r_struct
id|submodule_cache
op_star
id|cache
suffix:semicolon
DECL|member|commit_sha1
r_const
r_int
r_char
op_star
id|commit_sha1
suffix:semicolon
DECL|member|gitmodules_sha1
r_const
r_int
r_char
op_star
id|gitmodules_sha1
suffix:semicolon
DECL|member|overwrite
r_int
id|overwrite
suffix:semicolon
)brace
suffix:semicolon
DECL|function|parse_config
r_static
r_int
id|parse_config
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
id|data
)paren
(brace
r_struct
id|parse_config_parameter
op_star
id|me
op_assign
id|data
suffix:semicolon
r_struct
id|submodule
op_star
id|submodule
suffix:semicolon
r_struct
id|strbuf
id|name
op_assign
id|STRBUF_INIT
comma
id|item
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this also ensures that we only parse submodule entries */
r_if
c_cond
(paren
op_logical_neg
id|name_and_item_from_var
c_func
(paren
id|var
comma
op_amp
id|name
comma
op_amp
id|item
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|submodule
op_assign
id|lookup_or_create_by_name
c_func
(paren
id|me-&gt;cache
comma
id|me-&gt;gitmodules_sha1
comma
id|name.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|item.buf
comma
l_string|&quot;path&quot;
)paren
)paren
(brace
r_struct
id|strbuf
id|path
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|ret
op_assign
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;overwrite
op_logical_and
id|submodule-&gt;path
op_ne
l_int|NULL
)paren
(brace
id|warn_multiple_config
c_func
(paren
id|me-&gt;commit_sha1
comma
id|submodule-&gt;name
comma
l_string|&quot;path&quot;
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|submodule-&gt;path
)paren
id|cache_remove_path
c_func
(paren
id|me-&gt;cache
comma
id|submodule
)paren
suffix:semicolon
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|submodule-&gt;path
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|path
comma
id|value
)paren
suffix:semicolon
id|submodule-&gt;path
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|path
comma
l_int|NULL
)paren
suffix:semicolon
id|cache_put_path
c_func
(paren
id|me-&gt;cache
comma
id|submodule
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
id|item.buf
comma
l_string|&quot;fetchrecursesubmodules&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;overwrite
op_logical_and
id|submodule-&gt;fetch_recurse
op_ne
id|RECURSE_SUBMODULES_NONE
)paren
(brace
id|warn_multiple_config
c_func
(paren
id|me-&gt;commit_sha1
comma
id|submodule-&gt;name
comma
l_string|&quot;fetchrecursesubmodules&quot;
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
id|submodule-&gt;fetch_recurse
op_assign
id|parse_fetch_recurse_submodules_arg
c_func
(paren
id|var
comma
id|value
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
id|item.buf
comma
l_string|&quot;ignore&quot;
)paren
)paren
(brace
r_struct
id|strbuf
id|ignore
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;overwrite
op_logical_and
id|submodule-&gt;ignore
op_ne
l_int|NULL
)paren
(brace
id|warn_multiple_config
c_func
(paren
id|me-&gt;commit_sha1
comma
id|submodule-&gt;name
comma
l_string|&quot;ignore&quot;
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|ret
op_assign
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;untracked&quot;
)paren
op_logical_and
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;dirty&quot;
)paren
op_logical_and
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;all&quot;
)paren
op_logical_and
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;none&quot;
)paren
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;Invalid parameter &squot;%s&squot; for config option &quot;
l_string|&quot;&squot;submodule.%s.ignore&squot;&quot;
comma
id|value
comma
id|var
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|submodule-&gt;ignore
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|ignore
comma
id|value
)paren
suffix:semicolon
id|submodule-&gt;ignore
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|ignore
comma
l_int|NULL
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
id|item.buf
comma
l_string|&quot;url&quot;
)paren
)paren
(brace
r_struct
id|strbuf
id|url
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|ret
op_assign
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;overwrite
op_logical_and
id|submodule-&gt;url
op_ne
l_int|NULL
)paren
(brace
id|warn_multiple_config
c_func
(paren
id|me-&gt;commit_sha1
comma
id|submodule-&gt;name
comma
l_string|&quot;url&quot;
)paren
suffix:semicolon
r_goto
id|release_return
suffix:semicolon
)brace
id|free
c_func
(paren
(paren
r_void
op_star
)paren
id|submodule-&gt;url
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|url
comma
id|value
)paren
suffix:semicolon
id|submodule-&gt;url
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|url
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|release_return
suffix:colon
id|strbuf_release
c_func
(paren
op_amp
id|name
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|item
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|gitmodule_sha1_from_commit
r_static
r_int
id|gitmodule_sha1_from_commit
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_int
r_char
op_star
id|gitmodules_sha1
)paren
(brace
r_struct
id|strbuf
id|rev
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|commit_sha1
)paren
)paren
(brace
id|hashcpy
c_func
(paren
id|gitmodules_sha1
comma
id|null_sha1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|rev
comma
l_string|&quot;%s:.gitmodules&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|rev.buf
comma
id|gitmodules_sha1
)paren
op_ge
l_int|0
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* This does a lookup of a submodule configuration by name or by path&n; * (key) with on-demand reading of the appropriate .gitmodules from&n; * revisions.&n; */
DECL|function|config_from
r_static
r_const
r_struct
id|submodule
op_star
id|config_from
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_char
op_star
id|key
comma
r_enum
id|lookup_type
id|lookup_type
)paren
(brace
r_struct
id|strbuf
id|rev
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
r_int
id|config_size
suffix:semicolon
r_char
op_star
id|config
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_const
r_struct
id|submodule
op_star
id|submodule
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|parse_config_parameter
id|parameter
suffix:semicolon
multiline_comment|/*&n;&t; * If any parameter except the cache is a NULL pointer just&n;&t; * return the first submodule. Can be used to check whether&n;&t; * there are any submodules parsed.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|commit_sha1
op_logical_or
op_logical_neg
id|key
)paren
(brace
r_struct
id|hashmap_iter
id|iter
suffix:semicolon
r_struct
id|submodule_entry
op_star
id|entry
suffix:semicolon
id|hashmap_iter_init
c_func
(paren
op_amp
id|cache-&gt;for_name
comma
op_amp
id|iter
)paren
suffix:semicolon
id|entry
op_assign
id|hashmap_iter_next
c_func
(paren
op_amp
id|iter
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|entry-&gt;config
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|gitmodule_sha1_from_commit
c_func
(paren
id|commit_sha1
comma
id|sha1
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|lookup_type
)paren
(brace
r_case
id|lookup_name
suffix:colon
id|submodule
op_assign
id|cache_lookup_name
c_func
(paren
id|cache
comma
id|sha1
comma
id|key
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|lookup_path
suffix:colon
id|submodule
op_assign
id|cache_lookup_path
c_func
(paren
id|cache
comma
id|sha1
comma
id|key
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|submodule
)paren
r_return
id|submodule
suffix:semicolon
id|config
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|config_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|config
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|config
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* fill the submodule config into the cache */
id|parameter.cache
op_assign
id|cache
suffix:semicolon
id|parameter.commit_sha1
op_assign
id|commit_sha1
suffix:semicolon
id|parameter.gitmodules_sha1
op_assign
id|sha1
suffix:semicolon
id|parameter.overwrite
op_assign
l_int|0
suffix:semicolon
id|git_config_from_buf
c_func
(paren
id|parse_config
comma
id|rev.buf
comma
id|config
comma
id|config_size
comma
op_amp
id|parameter
)paren
suffix:semicolon
id|free
c_func
(paren
id|config
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|lookup_type
)paren
(brace
r_case
id|lookup_name
suffix:colon
r_return
id|cache_lookup_name
c_func
(paren
id|cache
comma
id|sha1
comma
id|key
)paren
suffix:semicolon
r_case
id|lookup_path
suffix:colon
r_return
id|cache_lookup_path
c_func
(paren
id|cache
comma
id|sha1
comma
id|key
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|config_from_path
r_static
r_const
r_struct
id|submodule
op_star
id|config_from_path
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_return
id|config_from
c_func
(paren
id|cache
comma
id|commit_sha1
comma
id|path
comma
id|lookup_path
)paren
suffix:semicolon
)brace
DECL|function|config_from_name
r_static
r_const
r_struct
id|submodule
op_star
id|config_from_name
c_func
(paren
r_struct
id|submodule_cache
op_star
id|cache
comma
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|config_from
c_func
(paren
id|cache
comma
id|commit_sha1
comma
id|name
comma
id|lookup_name
)paren
suffix:semicolon
)brace
DECL|function|ensure_cache_init
r_static
r_void
id|ensure_cache_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|is_cache_init
)paren
r_return
suffix:semicolon
id|cache_init
c_func
(paren
op_amp
id|cache
)paren
suffix:semicolon
id|is_cache_init
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|submodule_from_name
r_const
r_struct
id|submodule
op_star
id|submodule_from_name
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|ensure_cache_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|config_from_name
c_func
(paren
op_amp
id|cache
comma
id|commit_sha1
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|submodule_from_path
r_const
r_struct
id|submodule
op_star
id|submodule_from_path
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_char
op_star
id|path
)paren
(brace
id|ensure_cache_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|config_from_path
c_func
(paren
op_amp
id|cache
comma
id|commit_sha1
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|submodule_free
r_void
id|submodule_free
c_func
(paren
r_void
)paren
(brace
id|cache_free
c_func
(paren
op_amp
id|cache
)paren
suffix:semicolon
id|is_cache_init
op_assign
l_int|0
suffix:semicolon
)brace
eof
