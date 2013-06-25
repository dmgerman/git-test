multiline_comment|/*&n; * &quot;git clean&quot; builtin command&n; *&n; * Copyright (C) 2007 Shawn Bohrer&n; *&n; * Based on git-clean.sh by Pavel Roskin&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|force
r_static
r_int
id|force
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* unset */
DECL|variable|del_list
r_static
r_struct
id|string_list
id|del_list
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
DECL|variable|builtin_clean_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_clean_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git clean [-d] [-f] [-n] [-q] [-e &lt;pattern&gt;] [-x | -X] [--] &lt;paths&gt;...&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|msg_remove
r_static
r_const
r_char
op_star
id|msg_remove
op_assign
id|N_
c_func
(paren
l_string|&quot;Removing %s&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|msg_would_remove
r_static
r_const
r_char
op_star
id|msg_would_remove
op_assign
id|N_
c_func
(paren
l_string|&quot;Would remove %s&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|msg_skip_git_dir
r_static
r_const
r_char
op_star
id|msg_skip_git_dir
op_assign
id|N_
c_func
(paren
l_string|&quot;Skipping repository %s&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|msg_would_skip_git_dir
r_static
r_const
r_char
op_star
id|msg_would_skip_git_dir
op_assign
id|N_
c_func
(paren
l_string|&quot;Would skip repository %s&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|msg_warn_remove_failed
r_static
r_const
r_char
op_star
id|msg_warn_remove_failed
op_assign
id|N_
c_func
(paren
l_string|&quot;failed to remove %s&quot;
)paren
suffix:semicolon
DECL|function|git_clean_config
r_static
r_int
id|git_clean_config
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
id|var
comma
l_string|&quot;clean.requireforce&quot;
)paren
)paren
id|force
op_assign
op_logical_neg
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
DECL|function|exclude_cb
r_static
r_int
id|exclude_cb
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
r_struct
id|string_list
op_star
id|exclude_list
op_assign
id|opt-&gt;value
suffix:semicolon
id|string_list_append
c_func
(paren
id|exclude_list
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remove_dirs
r_static
r_int
id|remove_dirs
c_func
(paren
r_struct
id|strbuf
op_star
id|path
comma
r_const
r_char
op_star
id|prefix
comma
r_int
id|force_flag
comma
r_int
id|dry_run
comma
r_int
id|quiet
comma
r_int
op_star
id|dir_gone
)paren
(brace
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|strbuf
id|quoted
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|dirent
op_star
id|e
suffix:semicolon
r_int
id|res
op_assign
l_int|0
comma
id|ret
op_assign
l_int|0
comma
id|gone
op_assign
l_int|1
comma
id|original_len
op_assign
id|path-&gt;len
comma
id|len
comma
id|i
suffix:semicolon
r_int
r_char
id|submodule_head
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|string_list
id|dels
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
op_star
id|dir_gone
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|force_flag
op_amp
id|REMOVE_DIR_KEEP_NESTED_GIT
)paren
op_logical_and
op_logical_neg
id|resolve_gitlink_ref
c_func
(paren
id|path-&gt;buf
comma
l_string|&quot;HEAD&quot;
comma
id|submodule_head
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
(brace
id|quote_path_relative
c_func
(paren
id|path-&gt;buf
comma
id|prefix
comma
op_amp
id|quoted
)paren
suffix:semicolon
id|printf
c_func
(paren
id|dry_run
ques
c_cond
id|_
c_func
(paren
id|msg_would_skip_git_dir
)paren
suffix:colon
id|_
c_func
(paren
id|msg_skip_git_dir
)paren
comma
id|quoted.buf
)paren
suffix:semicolon
)brace
op_star
id|dir_gone
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dir
op_assign
id|opendir
c_func
(paren
id|path-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
multiline_comment|/* an empty dir could be removed even if it is unreadble */
id|res
op_assign
id|dry_run
ques
c_cond
l_int|0
suffix:colon
id|rmdir
c_func
(paren
id|path-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|quote_path_relative
c_func
(paren
id|path-&gt;buf
comma
id|prefix
comma
op_amp
id|quoted
)paren
suffix:semicolon
id|warning
c_func
(paren
id|_
c_func
(paren
id|msg_warn_remove_failed
)paren
comma
id|quoted.buf
)paren
suffix:semicolon
op_star
id|dir_gone
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path-&gt;buf
(braket
id|original_len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|strbuf_addch
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|len
op_assign
id|path-&gt;len
suffix:semicolon
r_while
c_loop
(paren
(paren
id|e
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
id|st
suffix:semicolon
r_if
c_cond
(paren
id|is_dot_or_dotdot
c_func
(paren
id|e-&gt;d_name
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|path
comma
id|len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|path
comma
id|e-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|path-&gt;buf
comma
op_amp
id|st
)paren
)paren
suffix:semicolon
multiline_comment|/* fall thru */
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
(brace
r_if
c_cond
(paren
id|remove_dirs
c_func
(paren
id|path
comma
id|prefix
comma
id|force_flag
comma
id|dry_run
comma
id|quiet
comma
op_amp
id|gone
)paren
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|gone
)paren
(brace
id|quote_path_relative
c_func
(paren
id|path-&gt;buf
comma
id|prefix
comma
op_amp
id|quoted
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|dels
comma
id|quoted.buf
)paren
suffix:semicolon
)brace
r_else
op_star
id|dir_gone
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
id|res
op_assign
id|dry_run
ques
c_cond
l_int|0
suffix:colon
id|unlink
c_func
(paren
id|path-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|quote_path_relative
c_func
(paren
id|path-&gt;buf
comma
id|prefix
comma
op_amp
id|quoted
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|dels
comma
id|quoted.buf
)paren
suffix:semicolon
)brace
r_else
(brace
id|quote_path_relative
c_func
(paren
id|path-&gt;buf
comma
id|prefix
comma
op_amp
id|quoted
)paren
suffix:semicolon
id|warning
c_func
(paren
id|_
c_func
(paren
id|msg_warn_remove_failed
)paren
comma
id|quoted.buf
)paren
suffix:semicolon
op_star
id|dir_gone
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
multiline_comment|/* path too long, stat fails, or non-directory still exists */
op_star
id|dir_gone
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|path
comma
id|original_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dir_gone
)paren
(brace
id|res
op_assign
id|dry_run
ques
c_cond
l_int|0
suffix:colon
id|rmdir
c_func
(paren
id|path-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
op_star
id|dir_gone
op_assign
l_int|1
suffix:semicolon
r_else
(brace
id|quote_path_relative
c_func
(paren
id|path-&gt;buf
comma
id|prefix
comma
op_amp
id|quoted
)paren
suffix:semicolon
id|warning
c_func
(paren
id|_
c_func
(paren
id|msg_warn_remove_failed
)paren
comma
id|quoted.buf
)paren
suffix:semicolon
op_star
id|dir_gone
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|dir_gone
op_logical_and
op_logical_neg
id|quiet
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dels.nr
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
id|dry_run
ques
c_cond
id|_
c_func
(paren
id|msg_would_remove
)paren
suffix:colon
id|_
c_func
(paren
id|msg_remove
)paren
comma
id|dels.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
)brace
id|string_list_clear
c_func
(paren
op_amp
id|dels
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cmd_clean
r_int
id|cmd_clean
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
r_int
id|i
comma
id|res
suffix:semicolon
r_int
id|dry_run
op_assign
l_int|0
comma
id|remove_directories
op_assign
l_int|0
comma
id|quiet
op_assign
l_int|0
comma
id|ignored
op_assign
l_int|0
suffix:semicolon
r_int
id|ignored_only
op_assign
l_int|0
comma
id|config_set
op_assign
l_int|0
comma
id|errors
op_assign
l_int|0
comma
id|gone
op_assign
l_int|1
suffix:semicolon
r_int
id|rm_flags
op_assign
id|REMOVE_DIR_KEEP_NESTED_GIT
suffix:semicolon
r_struct
id|strbuf
id|abs_path
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|dir_struct
id|dir
suffix:semicolon
r_static
r_const
r_char
op_star
op_star
id|pathspec
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|string_list
id|exclude_list
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|exclude_list
op_star
id|el
suffix:semicolon
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_const
r_char
op_star
id|qname
suffix:semicolon
r_char
op_star
id|seen
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
id|N_
c_func
(paren
l_string|&quot;do not print names of files removed&quot;
)paren
)paren
comma
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|dry_run
comma
id|N_
c_func
(paren
l_string|&quot;dry run&quot;
)paren
)paren
comma
id|OPT__FORCE
c_func
(paren
op_amp
id|force
comma
id|N_
c_func
(paren
l_string|&quot;force&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
id|remove_directories
comma
id|N_
c_func
(paren
l_string|&quot;remove whole directories&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_char|&squot;e&squot;
comma
l_string|&quot;exclude&quot;
comma
op_amp
id|exclude_list
comma
id|N_
c_func
(paren
l_string|&quot;pattern&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;add &lt;pattern&gt; to ignore rules&quot;
)paren
comma
id|PARSE_OPT_NONEG
comma
id|exclude_cb
)brace
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;x&squot;
comma
l_int|NULL
comma
op_amp
id|ignored
comma
id|N_
c_func
(paren
l_string|&quot;remove ignored files, too&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;X&squot;
comma
l_int|NULL
comma
op_amp
id|ignored_only
comma
id|N_
c_func
(paren
l_string|&quot;remove only ignored files&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_clean_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|force
OL
l_int|0
)paren
id|force
op_assign
l_int|0
suffix:semicolon
r_else
id|config_set
op_assign
l_int|1
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
id|options
comma
id|builtin_clean_usage
comma
l_int|0
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dir
comma
l_int|0
comma
r_sizeof
(paren
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ignored_only
)paren
id|dir.flags
op_or_assign
id|DIR_SHOW_IGNORED
suffix:semicolon
r_if
c_cond
(paren
id|ignored
op_logical_and
id|ignored_only
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;-x and -X cannot be used together&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dry_run
op_logical_and
op_logical_neg
id|force
)paren
(brace
r_if
c_cond
(paren
id|config_set
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;clean.requireForce set to true and neither -n nor -f given; &quot;
l_string|&quot;refusing to clean&quot;
)paren
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;clean.requireForce defaults to true and neither -n nor -f given; &quot;
l_string|&quot;refusing to clean&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|force
OG
l_int|1
)paren
id|rm_flags
op_assign
l_int|0
suffix:semicolon
id|dir.flags
op_or_assign
id|DIR_SHOW_OTHER_DIRECTORIES
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;index file corrupt&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ignored
)paren
id|setup_standard_excludes
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|el
op_assign
id|add_exclude_list
c_func
(paren
op_amp
id|dir
comma
id|EXC_CMDL
comma
l_string|&quot;--exclude option&quot;
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
id|exclude_list.nr
suffix:semicolon
id|i
op_increment
)paren
id|add_exclude
c_func
(paren
id|exclude_list.items
(braket
id|i
)braket
dot
id|string
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|el
comma
(paren
id|i
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
)paren
suffix:semicolon
id|fill_directory
c_func
(paren
op_amp
id|dir
comma
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
)paren
id|seen
op_assign
id|xmalloc
c_func
(paren
id|argc
OG
l_int|0
ques
c_cond
id|argc
suffix:colon
l_int|1
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
id|dir.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dir_entry
op_star
id|ent
op_assign
id|dir.entries
(braket
id|i
)braket
suffix:semicolon
r_int
id|len
comma
id|pos
suffix:semicolon
r_int
id|matches
op_assign
l_int|0
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_const
r_char
op_star
id|rel
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Remove the &squot;/&squot; at the end that directory&n;&t;&t; * walking adds for directory entries.&n;&t;&t; */
id|len
op_assign
id|ent-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|ent-&gt;name
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len
op_decrement
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
r_continue
suffix:semicolon
multiline_comment|/* exact match */
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|active_nr
)paren
(brace
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_namelen
c_func
(paren
id|ce
)paren
op_eq
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|ent-&gt;name
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Yup, this one exists unmerged */
)brace
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|ent-&gt;name
comma
op_amp
id|st
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot lstat &squot;%s&squot;&quot;
comma
id|ent-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
)paren
(brace
id|memset
c_func
(paren
id|seen
comma
l_int|0
comma
id|argc
OG
l_int|0
ques
c_cond
id|argc
suffix:colon
l_int|1
)paren
suffix:semicolon
id|matches
op_assign
id|match_pathspec
c_func
(paren
id|pathspec
comma
id|ent-&gt;name
comma
id|len
comma
l_int|0
comma
id|seen
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|remove_directories
op_logical_or
(paren
id|matches
op_eq
id|MATCHED_EXACTLY
)paren
)paren
(brace
id|rel
op_assign
id|relative_path
c_func
(paren
id|ent-&gt;name
comma
id|prefix
comma
op_amp
id|buf
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|del_list
comma
id|rel
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|pathspec
op_logical_and
op_logical_neg
id|matches
)paren
r_continue
suffix:semicolon
id|rel
op_assign
id|relative_path
c_func
(paren
id|ent-&gt;name
comma
id|prefix
comma
op_amp
id|buf
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|del_list
comma
id|rel
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* TODO: do interactive git-clean here, which will modify del_list */
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|del_list
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|abs_path
comma
id|prefix
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|abs_path
comma
id|item-&gt;string
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we might have removed this as part of earlier&n;&t;&t; * recursive directory removal, so lstat() here could&n;&t;&t; * fail with ENOENT.&n;&t;&t; */
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|abs_path.buf
comma
op_amp
id|st
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|remove_dirs
c_func
(paren
op_amp
id|abs_path
comma
id|prefix
comma
id|rm_flags
comma
id|dry_run
comma
id|quiet
comma
op_amp
id|gone
)paren
)paren
id|errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|gone
op_logical_and
op_logical_neg
id|quiet
)paren
(brace
id|qname
op_assign
id|quote_path_relative
c_func
(paren
id|item-&gt;string
comma
l_int|NULL
comma
op_amp
id|buf
)paren
suffix:semicolon
id|printf
c_func
(paren
id|dry_run
ques
c_cond
id|_
c_func
(paren
id|msg_would_remove
)paren
suffix:colon
id|_
c_func
(paren
id|msg_remove
)paren
comma
id|qname
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|res
op_assign
id|dry_run
ques
c_cond
l_int|0
suffix:colon
id|unlink
c_func
(paren
id|abs_path.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|qname
op_assign
id|quote_path_relative
c_func
(paren
id|item-&gt;string
comma
l_int|NULL
comma
op_amp
id|buf
)paren
suffix:semicolon
id|warning
c_func
(paren
id|_
c_func
(paren
id|msg_warn_remove_failed
)paren
comma
id|qname
)paren
suffix:semicolon
id|errors
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
(brace
id|qname
op_assign
id|quote_path_relative
c_func
(paren
id|item-&gt;string
comma
l_int|NULL
comma
op_amp
id|buf
)paren
suffix:semicolon
id|printf
c_func
(paren
id|dry_run
ques
c_cond
id|_
c_func
(paren
id|msg_would_remove
)paren
suffix:colon
id|_
c_func
(paren
id|msg_remove
)paren
comma
id|qname
)paren
suffix:semicolon
)brace
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|abs_path
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|seen
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|abs_path
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|del_list
comma
l_int|0
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|exclude_list
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|errors
op_ne
l_int|0
)paren
suffix:semicolon
)brace
eof
