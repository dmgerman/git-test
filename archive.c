macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;archive.h&quot;
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
id|strbuf_init
c_func
(paren
op_amp
id|fmt
comma
l_int|0
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
DECL|function|convert_to_archive
r_static
r_int
id|convert_to_archive
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_void
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
comma
r_const
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_static
r_struct
id|git_attr
op_star
id|attr_export_subst
suffix:semicolon
r_struct
id|git_attr_check
id|check
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_export_subst
)paren
id|attr_export_subst
op_assign
id|git_attr
c_func
(paren
l_string|&quot;export-subst&quot;
comma
l_int|12
)paren
suffix:semicolon
id|check
(braket
l_int|0
)braket
dot
id|attr
op_assign
id|attr_export_subst
suffix:semicolon
r_if
c_cond
(paren
id|git_checkattr
c_func
(paren
id|path
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
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
id|format_subst
c_func
(paren
id|commit
comma
id|src
comma
id|len
comma
id|buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sha1_file_to_archive
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
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
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
id|convert_to_archive
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
comma
id|commit
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
DECL|function|is_archive_path_ignored
r_int
id|is_archive_path_ignored
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_static
r_struct
id|git_attr
op_star
id|attr_export_ignore
suffix:semicolon
r_struct
id|git_attr_check
id|check
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_export_ignore
)paren
id|attr_export_ignore
op_assign
id|git_attr
c_func
(paren
l_string|&quot;export-ignore&quot;
comma
l_int|13
)paren
suffix:semicolon
id|check
(braket
l_int|0
)braket
dot
id|attr
op_assign
id|attr_export_ignore
suffix:semicolon
r_if
c_cond
(paren
id|git_checkattr
c_func
(paren
id|path
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
r_return
l_int|0
suffix:semicolon
r_return
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
r_if
c_cond
(paren
id|is_archive_path_ignored
c_func
(paren
id|path.buf
op_plus
id|args-&gt;baselen
)paren
)paren
r_return
l_int|0
suffix:semicolon
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
id|READ_TREE_RECURSIVE
suffix:semicolon
)brace
id|buffer
op_assign
id|sha1_file_to_archive
c_func
(paren
id|path.buf
op_plus
id|args-&gt;baselen
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
id|args-&gt;commit
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
id|err
op_assign
id|read_tree_recursive
c_func
(paren
id|args-&gt;tree
comma
id|args-&gt;base
comma
id|args-&gt;baselen
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
eof
