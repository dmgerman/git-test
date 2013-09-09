multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;pathspec.h&quot;
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|macro|LS_RECURSIVE
mdefine_line|#define LS_RECURSIVE 1
DECL|macro|LS_TREE_ONLY
mdefine_line|#define LS_TREE_ONLY 2
DECL|macro|LS_SHOW_TREES
mdefine_line|#define LS_SHOW_TREES 4
DECL|macro|LS_NAME_ONLY
mdefine_line|#define LS_NAME_ONLY 8
DECL|macro|LS_SHOW_SIZE
mdefine_line|#define LS_SHOW_SIZE 16
DECL|variable|abbrev
r_static
r_int
id|abbrev
suffix:semicolon
DECL|variable|ls_options
r_static
r_int
id|ls_options
suffix:semicolon
DECL|variable|pathspec
r_static
r_struct
id|pathspec
id|pathspec
suffix:semicolon
DECL|variable|chomp_prefix
r_static
r_int
id|chomp_prefix
suffix:semicolon
DECL|variable|ls_tree_prefix
r_static
r_const
r_char
op_star
id|ls_tree_prefix
suffix:semicolon
DECL|variable|ls_tree_usage
r_static
r_const
r_char
op_star
r_const
id|ls_tree_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git ls-tree [&lt;options&gt;] &lt;tree-ish&gt; [&lt;path&gt;...]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|show_recursive
r_static
r_int
id|show_recursive
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_const
r_char
op_star
id|pathname
)paren
(brace
r_const
r_char
op_star
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|ls_options
op_amp
id|LS_RECURSIVE
)paren
r_return
l_int|1
suffix:semicolon
id|s
op_assign
id|pathspec._raw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|spec
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_int
id|len
comma
id|speclen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spec
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|base
comma
id|spec
comma
id|baselen
)paren
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|spec
op_add_assign
id|baselen
suffix:semicolon
id|speclen
op_assign
id|strlen
c_func
(paren
id|spec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speclen
op_le
id|len
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|spec
(braket
id|len
)braket
op_logical_and
id|spec
(braket
id|len
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|pathname
comma
id|spec
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|show_tree
r_static
r_int
id|show_tree
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
id|base
comma
r_int
id|baselen
comma
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
comma
r_int
id|stage
comma
r_void
op_star
id|context
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|type
op_assign
id|blob_type
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|mode
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Maybe we want to have some recursive version here?&n;&t;&t; *&n;&t;&t; * Something similar to this incomplete example:&n;&t;&t; *&n;&t;&t;if (show_subprojects(base, baselen, pathname))&n;&t;&t;&t;retval = READ_TREE_RECURSIVE;&n;&t;&t; *&n;&t;&t; */
id|type
op_assign
id|commit_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|show_recursive
c_func
(paren
id|base
comma
id|baselen
comma
id|pathname
)paren
)paren
(brace
id|retval
op_assign
id|READ_TREE_RECURSIVE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ls_options
op_amp
id|LS_SHOW_TREES
)paren
)paren
r_return
id|retval
suffix:semicolon
)brace
id|type
op_assign
id|tree_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ls_options
op_amp
id|LS_TREE_ONLY
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|chomp_prefix
op_logical_and
(paren
id|baselen
OL
id|chomp_prefix
op_logical_or
id|memcmp
c_func
(paren
id|ls_tree_prefix
comma
id|base
comma
id|chomp_prefix
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ls_options
op_amp
id|LS_NAME_ONLY
)paren
)paren
(brace
r_if
c_cond
(paren
id|ls_options
op_amp
id|LS_SHOW_SIZE
)paren
(brace
r_char
id|size_text
(braket
l_int|24
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|blob_type
)paren
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|sha1_object_info
c_func
(paren
id|sha1
comma
op_amp
id|size
)paren
op_eq
id|OBJ_BAD
)paren
id|strcpy
c_func
(paren
id|size_text
comma
l_string|&quot;BAD&quot;
)paren
suffix:semicolon
r_else
id|snprintf
c_func
(paren
id|size_text
comma
r_sizeof
(paren
id|size_text
)paren
comma
l_string|&quot;%lu&quot;
comma
id|size
)paren
suffix:semicolon
)brace
r_else
id|strcpy
c_func
(paren
id|size_text
comma
l_string|&quot;-&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%06o %s %s %7s&bslash;t&quot;
comma
id|mode
comma
id|type
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|abbrev
)paren
comma
id|size_text
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%06o %s %s&bslash;t&quot;
comma
id|mode
comma
id|type
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|abbrev
)paren
)paren
suffix:semicolon
)brace
id|write_name_quotedpfx
c_func
(paren
id|base
op_plus
id|chomp_prefix
comma
id|baselen
id|chomp_prefix
comma
id|pathname
comma
id|stdout
comma
id|line_termination
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|cmd_ls_tree
r_int
id|cmd_ls_tree
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_int
id|i
comma
id|full_tree
op_assign
l_int|0
suffix:semicolon
r_const
r_struct
id|option
id|ls_tree_options
(braket
)braket
op_assign
(brace
id|OPT_BIT
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
id|ls_options
comma
id|N_
c_func
(paren
l_string|&quot;only show trees&quot;
)paren
comma
id|LS_TREE_ONLY
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|NULL
comma
op_amp
id|ls_options
comma
id|N_
c_func
(paren
l_string|&quot;recurse into subtrees&quot;
)paren
comma
id|LS_RECURSIVE
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|NULL
comma
op_amp
id|ls_options
comma
id|N_
c_func
(paren
l_string|&quot;show trees when recursing&quot;
)paren
comma
id|LS_SHOW_TREES
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;z&squot;
comma
l_int|NULL
comma
op_amp
id|line_termination
comma
id|N_
c_func
(paren
l_string|&quot;terminate entries with NUL byte&quot;
)paren
comma
l_int|0
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;l&squot;
comma
l_string|&quot;long&quot;
comma
op_amp
id|ls_options
comma
id|N_
c_func
(paren
l_string|&quot;include object size&quot;
)paren
comma
id|LS_SHOW_SIZE
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;name-only&quot;
comma
op_amp
id|ls_options
comma
id|N_
c_func
(paren
l_string|&quot;list only filenames&quot;
)paren
comma
id|LS_NAME_ONLY
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;name-status&quot;
comma
op_amp
id|ls_options
comma
id|N_
c_func
(paren
l_string|&quot;list only filenames&quot;
)paren
comma
id|LS_NAME_ONLY
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;full-name&quot;
comma
op_amp
id|chomp_prefix
comma
id|N_
c_func
(paren
l_string|&quot;use full path names&quot;
)paren
comma
l_int|0
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;full-tree&quot;
comma
op_amp
id|full_tree
comma
id|N_
c_func
(paren
l_string|&quot;list entire tree; not just current directory &quot;
l_string|&quot;(implies --full-name)&quot;
)paren
)paren
comma
id|OPT__ABBREV
c_func
(paren
op_amp
id|abbrev
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
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|ls_tree_prefix
op_assign
id|prefix
suffix:semicolon
r_if
c_cond
(paren
id|prefix
op_logical_and
op_star
id|prefix
)paren
id|chomp_prefix
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
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
id|ls_tree_options
comma
id|ls_tree_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|full_tree
)paren
(brace
id|ls_tree_prefix
op_assign
id|prefix
op_assign
l_int|NULL
suffix:semicolon
id|chomp_prefix
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* -d -r should imply -t, but -d by itself should not have to. */
r_if
c_cond
(paren
(paren
id|LS_TREE_ONLY
op_or
id|LS_RECURSIVE
)paren
op_eq
(paren
(paren
id|LS_TREE_ONLY
op_or
id|LS_RECURSIVE
)paren
op_amp
id|ls_options
)paren
)paren
id|ls_options
op_or_assign
id|LS_SHOW_TREES
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|ls_tree_usage
comma
id|ls_tree_options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * show_recursive() rolls its own matching code and is&n;&t; * generally ignorant of &squot;struct pathspec&squot;. The magic mask&n;&t; * cannot be lifted until it is converted to use&n;&t; * match_pathspec_depth() or tree_entry_interesting()&n;&t; */
id|parse_pathspec
c_func
(paren
op_amp
id|pathspec
comma
id|PATHSPEC_GLOB
op_or
id|PATHSPEC_ICASE
comma
id|PATHSPEC_PREFER_CWD
comma
id|prefix
comma
id|argv
op_plus
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
id|pathspec.nr
suffix:semicolon
id|i
op_increment
)paren
id|pathspec.items
(braket
id|i
)braket
dot
id|nowildcard_len
op_assign
id|pathspec.items
(braket
id|i
)braket
dot
id|len
suffix:semicolon
id|pathspec.has_wildcard
op_assign
l_int|0
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
id|die
c_func
(paren
l_string|&quot;not a tree object&quot;
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|read_tree_recursive
c_func
(paren
id|tree
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
comma
op_amp
id|pathspec
comma
id|show_tree
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
