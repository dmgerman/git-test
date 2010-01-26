multiline_comment|/*&n; * &quot;git clean&quot; builtin command&n; *&n; * Copyright (C) 2007 Shawn Bohrer&n; *&n; * Based on git-clean.sh by Pavel Roskin&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|variable|force
r_static
r_int
id|force
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* unset */
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
l_string|&quot;git clean [-d] [-f] [-n] [-q] [-x | -X] [--] &lt;paths&gt;...&quot;
comma
l_int|NULL
)brace
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
suffix:semicolon
r_int
id|show_only
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
id|baselen
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
suffix:semicolon
r_int
id|rm_flags
op_assign
id|REMOVE_DIR_KEEP_NESTED_GIT
suffix:semicolon
r_struct
id|strbuf
id|directory
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
)paren
comma
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|show_only
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
comma
op_amp
id|force
comma
l_string|&quot;force&quot;
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
l_string|&quot;remove whole directories&quot;
)paren
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
l_string|&quot;remove ignored files, too&quot;
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
l_string|&quot;remove only ignored files&quot;
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
l_string|&quot;-x and -X cannot be used together&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
op_logical_and
op_logical_neg
id|force
)paren
id|die
c_func
(paren
l_string|&quot;clean.requireForce%s set and -n or -f not given; &quot;
l_string|&quot;refusing to clean&quot;
comma
id|config_set
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; not&quot;
)paren
suffix:semicolon
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
l_string|&quot;index file corrupt&quot;
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
multiline_comment|/*&n;&t;&t; * we might have removed this as part of earlier&n;&t;&t; * recursive directory removal, so lstat() here could&n;&t;&t; * fail with ENOENT.&n;&t;&t; */
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
r_continue
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
id|baselen
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
id|strbuf_addstr
c_func
(paren
op_amp
id|directory
comma
id|ent-&gt;name
)paren
suffix:semicolon
id|qname
op_assign
id|quote_path_relative
c_func
(paren
id|directory.buf
comma
id|directory.len
comma
op_amp
id|buf
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_only
op_logical_and
(paren
id|remove_directories
op_logical_or
(paren
id|matches
op_eq
id|MATCHED_EXACTLY
)paren
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Would remove %s&bslash;n&quot;
comma
id|qname
)paren
suffix:semicolon
)brace
r_else
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
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|printf
c_func
(paren
l_string|&quot;Removing %s&bslash;n&quot;
comma
id|qname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remove_dir_recursively
c_func
(paren
op_amp
id|directory
comma
id|rm_flags
)paren
op_ne
l_int|0
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;failed to remove &squot;%s&squot;&quot;
comma
id|qname
)paren
suffix:semicolon
id|errors
op_increment
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|show_only
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Would not remove %s&bslash;n&quot;
comma
id|qname
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;Not removing %s&bslash;n&quot;
comma
id|qname
)paren
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|directory
)paren
suffix:semicolon
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
id|qname
op_assign
id|quote_path_relative
c_func
(paren
id|ent-&gt;name
comma
l_int|1
comma
op_amp
id|buf
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_only
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Would remove %s&bslash;n&quot;
comma
id|qname
)paren
suffix:semicolon
r_continue
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
id|printf
c_func
(paren
l_string|&quot;Removing %s&bslash;n&quot;
comma
id|qname
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|ent-&gt;name
)paren
op_ne
l_int|0
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;failed to remove &squot;%s&squot;&quot;
comma
id|qname
)paren
suffix:semicolon
id|errors
op_increment
suffix:semicolon
)brace
)brace
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
id|directory
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
