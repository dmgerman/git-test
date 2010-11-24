macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;archive.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
DECL|variable|archive_usage
r_static
r_char
r_const
op_star
r_const
id|archive_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git archive [options] &lt;tree-ish&gt; [&lt;path&gt;...]&quot;
comma
l_string|&quot;git archive --list&quot;
comma
l_string|&quot;git archive --remote &lt;repo&gt; [--exec &lt;cmd&gt;] [options] &lt;tree-ish&gt; [&lt;path&gt;...]&quot;
comma
l_string|&quot;git archive --remote &lt;repo&gt; [--exec &lt;cmd&gt;] --list&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|macro|USES_ZLIB_COMPRESSION
mdefine_line|#define USES_ZLIB_COMPRESSION 1
DECL|struct|archiver
r_static
r_const
r_struct
id|archiver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|write_archive
id|write_archive_fn_t
id|write_archive
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|variable|archivers
)brace
id|archivers
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;tar&quot;
comma
id|write_tar_archive
)brace
comma
(brace
l_string|&quot;zip&quot;
comma
id|write_zip_archive
comma
id|USES_ZLIB_COMPRESSION
)brace
comma
)brace
suffix:semicolon
DECL|function|format_subst
r_static
r_void
id|format_subst
c_func
(paren
r_const
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
r_char
op_star
id|to_free
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|strbuf
id|fmt
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|ctx.date_mode
op_assign
id|DATE_NORMAL
suffix:semicolon
id|ctx.abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
r_if
c_cond
(paren
id|src
op_eq
id|buf-&gt;buf
)paren
id|to_free
op_assign
id|strbuf_detach
c_func
(paren
id|buf
comma
l_int|NULL
)paren
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
id|b
comma
op_star
id|c
suffix:semicolon
id|b
op_assign
id|memmem
c_func
(paren
id|src
comma
id|len
comma
l_string|&quot;$Format:&quot;
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
r_break
suffix:semicolon
id|c
op_assign
id|memchr
c_func
(paren
id|b
op_plus
l_int|8
comma
l_char|&squot;$&squot;
comma
(paren
id|src
op_plus
id|len
)paren
id|b
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|fmt
comma
id|b
op_plus
l_int|8
comma
id|c
id|b
l_int|8
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|b
id|src
)paren
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
id|fmt.buf
comma
id|buf
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|len
op_sub_assign
id|c
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|c
op_plus
l_int|1
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
id|free
c_func
(paren
id|to_free
)paren
suffix:semicolon
)brace
DECL|function|sha1_file_to_archive
r_static
r_void
op_star
id|sha1_file_to_archive
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|mode
comma
r_enum
id|object_type
op_star
id|type
comma
r_int
r_int
op_star
id|sizep
comma
r_const
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_void
op_star
id|buffer
suffix:semicolon
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
id|sizep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_logical_and
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
id|strbuf_attach
c_func
(paren
op_amp
id|buf
comma
id|buffer
comma
op_star
id|sizep
comma
op_star
id|sizep
op_plus
l_int|1
)paren
suffix:semicolon
id|convert_to_working_tree
c_func
(paren
id|path
comma
id|buf.buf
comma
id|buf.len
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit
)paren
id|format_subst
c_func
(paren
id|commit
comma
id|buf.buf
comma
id|buf.len
comma
op_amp
id|buf
)paren
suffix:semicolon
id|buffer
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
op_amp
id|size
)paren
suffix:semicolon
op_star
id|sizep
op_assign
id|size
suffix:semicolon
)brace
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|setup_archive_check
r_static
r_void
id|setup_archive_check
c_func
(paren
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_static
r_struct
id|git_attr
op_star
id|attr_export_ignore
suffix:semicolon
r_static
r_struct
id|git_attr
op_star
id|attr_export_subst
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_export_ignore
)paren
(brace
id|attr_export_ignore
op_assign
id|git_attr
c_func
(paren
l_string|&quot;export-ignore&quot;
)paren
suffix:semicolon
id|attr_export_subst
op_assign
id|git_attr
c_func
(paren
l_string|&quot;export-subst&quot;
)paren
suffix:semicolon
)brace
id|check
(braket
l_int|0
)braket
dot
id|attr
op_assign
id|attr_export_ignore
suffix:semicolon
id|check
(braket
l_int|1
)braket
dot
id|attr
op_assign
id|attr_export_subst
suffix:semicolon
)brace
DECL|struct|archiver_context
r_struct
id|archiver_context
(brace
DECL|member|args
r_struct
id|archiver_args
op_star
id|args
suffix:semicolon
DECL|member|write_entry
id|write_archive_entry_fn_t
id|write_entry
suffix:semicolon
)brace
suffix:semicolon
DECL|function|write_archive_entry
r_static
r_int
id|write_archive_entry
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
id|filename
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
r_static
r_struct
id|strbuf
id|path
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|archiver_context
op_star
id|c
op_assign
id|context
suffix:semicolon
r_struct
id|archiver_args
op_star
id|args
op_assign
id|c-&gt;args
suffix:semicolon
id|write_archive_entry_fn_t
id|write_entry
op_assign
id|c-&gt;write_entry
suffix:semicolon
r_struct
id|git_attr_check
id|check
(braket
l_int|2
)braket
suffix:semicolon
r_const
r_char
op_star
id|path_without_prefix
suffix:semicolon
r_int
id|convert
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|path
)paren
suffix:semicolon
id|strbuf_grow
c_func
(paren
op_amp
id|path
comma
id|PATH_MAX
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|path
comma
id|args-&gt;base
comma
id|args-&gt;baselen
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|path
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|path
comma
id|filename
)paren
suffix:semicolon
id|path_without_prefix
op_assign
id|path.buf
op_plus
id|args-&gt;baselen
suffix:semicolon
id|setup_archive_check
c_func
(paren
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_checkattr
c_func
(paren
id|path_without_prefix
comma
id|ARRAY_SIZE
c_func
(paren
id|check
)paren
comma
id|check
)paren
)paren
(brace
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|check
(braket
l_int|0
)braket
dot
id|value
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|convert
op_assign
id|ATTR_TRUE
c_func
(paren
id|check
(braket
l_int|1
)braket
dot
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISGITLINK
c_func
(paren
id|mode
)paren
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s&bslash;n&quot;
comma
(paren
r_int
)paren
id|path.len
comma
id|path.buf
)paren
suffix:semicolon
id|err
op_assign
id|write_entry
c_func
(paren
id|args
comma
id|sha1
comma
id|path.buf
comma
id|path.len
comma
id|mode
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_return
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
ques
c_cond
id|READ_TREE_RECURSIVE
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|sha1_file_to_archive
c_func
(paren
id|path_without_prefix
comma
id|sha1
comma
id|mode
comma
op_amp
id|type
comma
op_amp
id|size
comma
id|convert
ques
c_cond
id|args-&gt;commit
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s&bslash;n&quot;
comma
(paren
r_int
)paren
id|path.len
comma
id|path.buf
)paren
suffix:semicolon
id|err
op_assign
id|write_entry
c_func
(paren
id|args
comma
id|sha1
comma
id|path.buf
comma
id|path.len
comma
id|mode
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|write_archive_entries
r_int
id|write_archive_entries
c_func
(paren
r_struct
id|archiver_args
op_star
id|args
comma
id|write_archive_entry_fn_t
id|write_entry
)paren
(brace
r_struct
id|archiver_context
id|context
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
suffix:semicolon
r_struct
id|tree_desc
id|t
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;baselen
OG
l_int|0
op_logical_and
id|args-&gt;base
(braket
id|args-&gt;baselen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_int
id|len
op_assign
id|args-&gt;baselen
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
op_logical_and
id|args-&gt;base
(braket
id|len
l_int|2
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s&bslash;n&quot;
comma
(paren
r_int
)paren
id|len
comma
id|args-&gt;base
)paren
suffix:semicolon
id|err
op_assign
id|write_entry
c_func
(paren
id|args
comma
id|args-&gt;tree-&gt;object.sha1
comma
id|args-&gt;base
comma
id|len
comma
l_int|040777
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
id|context.args
op_assign
id|args
suffix:semicolon
id|context.write_entry
op_assign
id|write_entry
suffix:semicolon
multiline_comment|/*&n;&t; * Setup index and instruct attr to read index only&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|args-&gt;worktree_attributes
)paren
(brace
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|opts.index_only
op_assign
l_int|1
suffix:semicolon
id|opts.head_idx
op_assign
l_int|1
suffix:semicolon
id|opts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.dst_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.fn
op_assign
id|oneway_merge
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t
comma
id|args-&gt;tree-&gt;buffer
comma
id|args-&gt;tree-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unpack_trees
c_func
(paren
l_int|1
comma
op_amp
id|t
comma
op_amp
id|opts
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|git_attr_set_direction
c_func
(paren
id|GIT_ATTR_INDEX
comma
op_amp
id|the_index
)paren
suffix:semicolon
)brace
id|err
op_assign
id|read_tree_recursive
c_func
(paren
id|args-&gt;tree
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
comma
id|args-&gt;pathspec
comma
id|write_archive_entry
comma
op_amp
id|context
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
id|READ_TREE_RECURSIVE
)paren
id|err
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|lookup_archiver
r_static
r_const
r_struct
id|archiver
op_star
id|lookup_archiver
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
l_int|NULL
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
id|ARRAY_SIZE
c_func
(paren
id|archivers
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|archivers
(braket
id|i
)braket
dot
id|name
)paren
)paren
r_return
op_amp
id|archivers
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|reject_entry
r_static
r_int
id|reject_entry
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
id|filename
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
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|path_exists
r_static
r_int
id|path_exists
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_const
r_char
op_star
id|pathspec
(braket
)braket
op_assign
(brace
id|path
comma
l_int|NULL
)brace
suffix:semicolon
r_if
c_cond
(paren
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
id|pathspec
comma
id|reject_entry
comma
l_int|NULL
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_pathspec_arg
r_static
r_void
id|parse_pathspec_arg
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
comma
r_struct
id|archiver_args
op_star
id|ar_args
)paren
(brace
id|ar_args-&gt;pathspec
op_assign
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
l_string|&quot;&quot;
comma
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
)paren
(brace
r_while
c_loop
(paren
op_star
id|pathspec
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|path_exists
c_func
(paren
id|ar_args-&gt;tree
comma
op_star
id|pathspec
)paren
)paren
id|die
c_func
(paren
l_string|&quot;path not found: %s&quot;
comma
op_star
id|pathspec
)paren
suffix:semicolon
id|pathspec
op_increment
suffix:semicolon
)brace
)brace
)brace
DECL|function|parse_treeish_arg
r_static
r_void
id|parse_treeish_arg
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
comma
r_struct
id|archiver_args
op_star
id|ar_args
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
id|name
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_const
r_int
r_char
op_star
id|commit_sha1
suffix:semicolon
id|time_t
id|archive_time
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_const
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name&quot;
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit
)paren
(brace
id|commit_sha1
op_assign
id|commit-&gt;object.sha1
suffix:semicolon
id|archive_time
op_assign
id|commit-&gt;date
suffix:semicolon
)brace
r_else
(brace
id|commit_sha1
op_assign
l_int|NULL
suffix:semicolon
id|archive_time
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
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
id|tree
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;not a tree object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|get_tree_entry
c_func
(paren
id|tree-&gt;object.sha1
comma
id|prefix
comma
id|tree_sha1
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|die
c_func
(paren
l_string|&quot;current working directory is untracked&quot;
)paren
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|tree_sha1
)paren
suffix:semicolon
)brace
id|ar_args-&gt;tree
op_assign
id|tree
suffix:semicolon
id|ar_args-&gt;commit_sha1
op_assign
id|commit_sha1
suffix:semicolon
id|ar_args-&gt;commit
op_assign
id|commit
suffix:semicolon
id|ar_args-&gt;time
op_assign
id|archive_time
suffix:semicolon
)brace
DECL|macro|OPT__COMPR
mdefine_line|#define OPT__COMPR(s, v, h, p) &bslash;&n;&t;{ OPTION_SET_INT, (s), NULL, (v), NULL, (h), &bslash;&n;&t;  PARSE_OPT_NOARG | PARSE_OPT_NONEG, NULL, (p) }
DECL|macro|OPT__COMPR_HIDDEN
mdefine_line|#define OPT__COMPR_HIDDEN(s, v, p) &bslash;&n;&t;{ OPTION_SET_INT, (s), NULL, (v), NULL, &quot;&quot;, &bslash;&n;&t;  PARSE_OPT_NOARG | PARSE_OPT_NONEG | PARSE_OPT_HIDDEN, NULL, (p) }
DECL|function|parse_archive_args
r_static
r_int
id|parse_archive_args
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
r_struct
id|archiver
op_star
op_star
id|ar
comma
r_struct
id|archiver_args
op_star
id|args
)paren
(brace
r_const
r_char
op_star
id|format
op_assign
l_string|&quot;tar&quot;
suffix:semicolon
r_const
r_char
op_star
id|base
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|remote
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|exec
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|output
op_assign
l_int|NULL
suffix:semicolon
r_int
id|compression_level
op_assign
l_int|1
suffix:semicolon
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|list
op_assign
l_int|0
suffix:semicolon
r_int
id|worktree_attributes
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|opts
(braket
)braket
op_assign
(brace
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;format&quot;
comma
op_amp
id|format
comma
l_string|&quot;fmt&quot;
comma
l_string|&quot;archive format&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;prefix&quot;
comma
op_amp
id|base
comma
l_string|&quot;prefix&quot;
comma
l_string|&quot;prepend prefix to each pathname in the archive&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;o&squot;
comma
l_string|&quot;output&quot;
comma
op_amp
id|output
comma
l_string|&quot;file&quot;
comma
l_string|&quot;write the archive to this file&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;worktree-attributes&quot;
comma
op_amp
id|worktree_attributes
comma
l_string|&quot;read .gitattributes in working directory&quot;
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
comma
l_string|&quot;report archived files on stderr&quot;
)paren
comma
id|OPT__COMPR
c_func
(paren
l_char|&squot;0&squot;
comma
op_amp
id|compression_level
comma
l_string|&quot;store only&quot;
comma
l_int|0
)paren
comma
id|OPT__COMPR
c_func
(paren
l_char|&squot;1&squot;
comma
op_amp
id|compression_level
comma
l_string|&quot;compress faster&quot;
comma
l_int|1
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;2&squot;
comma
op_amp
id|compression_level
comma
l_int|2
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;3&squot;
comma
op_amp
id|compression_level
comma
l_int|3
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;4&squot;
comma
op_amp
id|compression_level
comma
l_int|4
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;5&squot;
comma
op_amp
id|compression_level
comma
l_int|5
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;6&squot;
comma
op_amp
id|compression_level
comma
l_int|6
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;7&squot;
comma
op_amp
id|compression_level
comma
l_int|7
)paren
comma
id|OPT__COMPR_HIDDEN
c_func
(paren
l_char|&squot;8&squot;
comma
op_amp
id|compression_level
comma
l_int|8
)paren
comma
id|OPT__COMPR
c_func
(paren
l_char|&squot;9&squot;
comma
op_amp
id|compression_level
comma
l_string|&quot;compress better&quot;
comma
l_int|9
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;l&squot;
comma
l_string|&quot;list&quot;
comma
op_amp
id|list
comma
l_string|&quot;list supported archive formats&quot;
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;remote&quot;
comma
op_amp
id|remote
comma
l_string|&quot;repo&quot;
comma
l_string|&quot;retrieve the archive from remote repository &lt;repo&gt;&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;exec&quot;
comma
op_amp
id|exec
comma
l_string|&quot;cmd&quot;
comma
l_string|&quot;path to the remote git-upload-archive command&quot;
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
l_int|NULL
comma
id|opts
comma
id|archive_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
)paren
id|die
c_func
(paren
l_string|&quot;Unexpected option --remote&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exec
)paren
id|die
c_func
(paren
l_string|&quot;Option --exec can only be used together with --remote&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output
)paren
id|die
c_func
(paren
l_string|&quot;Unexpected option --output&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
id|base
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|list
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
id|ARRAY_SIZE
c_func
(paren
id|archivers
)paren
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|archivers
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* We need at least one parameter -- tree-ish */
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
id|archive_usage
comma
id|opts
)paren
suffix:semicolon
op_star
id|ar
op_assign
id|lookup_archiver
c_func
(paren
id|format
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|ar
)paren
id|die
c_func
(paren
l_string|&quot;Unknown archive format &squot;%s&squot;&quot;
comma
id|format
)paren
suffix:semicolon
id|args-&gt;compression_level
op_assign
id|Z_DEFAULT_COMPRESSION
suffix:semicolon
r_if
c_cond
(paren
id|compression_level
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|ar
)paren
op_member_access_from_pointer
id|flags
op_amp
id|USES_ZLIB_COMPRESSION
)paren
id|args-&gt;compression_level
op_assign
id|compression_level
suffix:semicolon
r_else
(brace
id|die
c_func
(paren
l_string|&quot;Argument not supported for format &squot;%s&squot;: -%d&quot;
comma
id|format
comma
id|compression_level
)paren
suffix:semicolon
)brace
)brace
id|args-&gt;verbose
op_assign
id|verbose
suffix:semicolon
id|args-&gt;base
op_assign
id|base
suffix:semicolon
id|args-&gt;baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
id|args-&gt;worktree_attributes
op_assign
id|worktree_attributes
suffix:semicolon
r_return
id|argc
suffix:semicolon
)brace
DECL|function|write_archive
r_int
id|write_archive
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
comma
r_int
id|setup_prefix
)paren
(brace
r_const
r_struct
id|archiver
op_star
id|ar
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|archiver_args
id|args
suffix:semicolon
id|argc
op_assign
id|parse_archive_args
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|ar
comma
op_amp
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setup_prefix
op_logical_and
id|prefix
op_eq
l_int|NULL
)paren
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|parse_treeish_arg
c_func
(paren
id|argv
comma
op_amp
id|args
comma
id|prefix
)paren
suffix:semicolon
id|parse_pathspec_arg
c_func
(paren
id|argv
op_plus
l_int|1
comma
op_amp
id|args
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
r_return
id|ar
op_member_access_from_pointer
id|write_archive
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
)brace
eof
