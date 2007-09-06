multiline_comment|/*&n; * Copyright (c) 2006 Franck Bui-Huu&n; * Copyright (c) 2006 Rene Scharfe&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;archive.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &quot;attr.h&quot;
DECL|variable|archive_usage
r_static
r_const
r_char
id|archive_usage
(braket
)braket
op_assign
"&bslash;"
l_string|&quot;git-archive --format=&lt;fmt&gt; [--prefix=&lt;prefix&gt;/] [--verbose] [&lt;extra&gt;] &lt;tree-ish&gt; [path...]&quot;
suffix:semicolon
DECL|struct|archiver_desc
r_static
r_struct
id|archiver_desc
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
DECL|member|parse_extra
id|parse_extra_args_fn_t
id|parse_extra
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
comma
l_int|NULL
)brace
comma
(brace
l_string|&quot;zip&quot;
comma
id|write_zip_archive
comma
id|parse_extra_zip_args
)brace
comma
)brace
suffix:semicolon
DECL|function|run_remote_archiver
r_static
r_int
id|run_remote_archiver
c_func
(paren
r_const
r_char
op_star
id|remote
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
op_star
id|url
comma
id|buf
(braket
id|LARGE_PACKET_MAX
)braket
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
comma
id|i
comma
id|len
comma
id|rv
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_const
r_char
op_star
id|exec
op_assign
l_string|&quot;git-upload-archive&quot;
suffix:semicolon
r_int
id|exec_at
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exec=&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|exec_at
)paren
id|die
c_func
(paren
l_string|&quot;multiple --exec specified&quot;
)paren
suffix:semicolon
id|exec
op_assign
id|arg
op_plus
l_int|7
suffix:semicolon
id|exec_at
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|url
op_assign
id|xstrdup
c_func
(paren
id|remote
)paren
suffix:semicolon
id|pid
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|url
comma
id|exec
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
id|pid
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|exec_at
)paren
r_continue
suffix:semicolon
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;argument %s&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|die
c_func
(paren
l_string|&quot;git-archive: expected ACK/NAK, got EOF&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;ACK&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
OG
l_int|5
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;NACK &quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-archive: NACK %s&quot;
comma
id|buf
op_plus
l_int|5
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-archive: protocol error&quot;
)paren
suffix:semicolon
)brace
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
id|die
c_func
(paren
l_string|&quot;git-archive: expected a flush&quot;
)paren
suffix:semicolon
multiline_comment|/* Now, start reading from fd[0] and spit it out to stdout */
id|rv
op_assign
id|recv_sideband
c_func
(paren
l_string|&quot;archive&quot;
comma
id|fd
(braket
l_int|0
)braket
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|rv
op_or_assign
id|finish_connect
c_func
(paren
id|pid
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|rv
suffix:semicolon
)brace
DECL|function|format_subst
r_static
r_void
op_star
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
id|format
comma
r_int
r_int
op_star
id|sizep
)paren
(brace
r_int
r_int
id|len
op_assign
op_star
id|sizep
comma
id|result_len
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|a
op_assign
id|format
suffix:semicolon
r_char
op_star
id|result
op_assign
l_int|NULL
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
r_char
op_star
id|fmt
comma
op_star
id|formatted
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|a_len
comma
id|fmt_len
comma
id|formatted_len
comma
id|allocated
op_assign
l_int|0
suffix:semicolon
id|b
op_assign
id|memmem
c_func
(paren
id|a
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
op_logical_or
id|a
op_plus
id|len
OL
id|b
op_plus
l_int|9
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
id|len
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
id|a_len
op_assign
id|b
id|a
suffix:semicolon
id|fmt_len
op_assign
id|c
id|b
l_int|8
suffix:semicolon
id|fmt
op_assign
id|xmalloc
c_func
(paren
id|fmt_len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fmt
comma
id|b
op_plus
l_int|8
comma
id|fmt_len
)paren
suffix:semicolon
id|fmt
(braket
id|fmt_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|formatted_len
op_assign
id|format_commit_message
c_func
(paren
id|commit
comma
id|fmt
comma
op_amp
id|formatted
comma
op_amp
id|allocated
)paren
suffix:semicolon
id|result
op_assign
id|xrealloc
c_func
(paren
id|result
comma
id|result_len
op_plus
id|a_len
op_plus
id|formatted_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
op_plus
id|result_len
comma
id|a
comma
id|a_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
op_plus
id|result_len
op_plus
id|a_len
comma
id|formatted
comma
id|formatted_len
)paren
suffix:semicolon
id|result_len
op_add_assign
id|a_len
op_plus
id|formatted_len
suffix:semicolon
id|len
op_sub_assign
id|c
op_plus
l_int|1
id|a
suffix:semicolon
id|a
op_assign
id|c
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
op_logical_and
id|len
)paren
(brace
id|result
op_assign
id|xrealloc
c_func
(paren
id|result
comma
id|result_len
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
op_plus
id|result_len
comma
id|a
comma
id|len
)paren
suffix:semicolon
id|result_len
op_add_assign
id|len
suffix:semicolon
)brace
op_star
id|sizep
op_assign
id|result_len
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|convert_to_archive
r_static
r_void
op_star
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
l_int|NULL
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
l_int|NULL
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
l_int|NULL
suffix:semicolon
r_return
id|format_subst
c_func
(paren
id|commit
comma
id|src
comma
id|sizep
)paren
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
id|size
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
comma
op_star
id|converted
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
id|size
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
id|converted
op_assign
id|convert_to_working_tree
c_func
(paren
id|path
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|converted
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|converted
suffix:semicolon
)brace
id|converted
op_assign
id|convert_to_archive
c_func
(paren
id|path
comma
id|buffer
comma
id|size
comma
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|converted
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|converted
suffix:semicolon
)brace
)brace
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|init_archiver
r_static
r_int
id|init_archiver
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|archiver
op_star
id|ar
)paren
(brace
r_int
id|rv
op_assign
l_int|1
comma
id|i
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
(brace
id|memset
c_func
(paren
id|ar
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ar
)paren
)paren
suffix:semicolon
id|ar-&gt;name
op_assign
id|archivers
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|ar-&gt;write_archive
op_assign
id|archivers
(braket
id|i
)braket
dot
id|write_archive
suffix:semicolon
id|ar-&gt;parse_extra
op_assign
id|archivers
(braket
id|i
)braket
dot
id|parse_extra
suffix:semicolon
id|rv
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|rv
suffix:semicolon
)brace
DECL|function|parse_pathspec_arg
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
id|get_pathspec
c_func
(paren
id|ar_args-&gt;base
comma
id|pathspec
)paren
suffix:semicolon
)brace
DECL|function|parse_treeish_arg
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
DECL|function|parse_archive_args
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
r_struct
id|archiver
op_star
id|ar
)paren
(brace
r_const
r_char
op_star
id|extra_argv
(braket
id|MAX_EXTRA_ARGS
)braket
suffix:semicolon
r_int
id|extra_argc
op_assign
l_int|0
suffix:semicolon
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
l_string|&quot;&quot;
suffix:semicolon
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--list&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-l&quot;
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--verbose&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|verbose
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--format=&quot;
)paren
)paren
(brace
id|format
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--prefix=&quot;
)paren
)paren
(brace
id|base
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|extra_argc
OG
id|MAX_EXTRA_ARGS
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Too many extra options&quot;
)paren
suffix:semicolon
id|extra_argv
(braket
id|extra_argc
op_increment
)braket
op_assign
id|arg
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* We need at least one parameter -- tree-ish */
r_if
c_cond
(paren
id|argc
l_int|1
OL
id|i
)paren
id|usage
c_func
(paren
id|archive_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|init_archiver
c_func
(paren
id|format
comma
id|ar
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unknown archive format &squot;%s&squot;&quot;
comma
id|format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|extra_argc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ar-&gt;parse_extra
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; format does not handle %s&quot;
comma
id|ar-&gt;name
comma
id|extra_argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ar-&gt;args.extra
op_assign
id|ar
op_member_access_from_pointer
id|parse_extra
c_func
(paren
id|extra_argc
comma
id|extra_argv
)paren
suffix:semicolon
)brace
id|ar-&gt;args.verbose
op_assign
id|verbose
suffix:semicolon
id|ar-&gt;args.base
op_assign
id|base
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|extract_remote_arg
r_static
r_const
r_char
op_star
id|extract_remote_arg
c_func
(paren
r_int
op_star
id|ac
comma
r_const
r_char
op_star
op_star
id|av
)paren
(brace
r_int
id|ix
comma
id|iy
comma
id|cnt
op_assign
op_star
id|ac
suffix:semicolon
r_int
id|no_more_options
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|remote
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|ix
op_assign
id|iy
op_assign
l_int|1
suffix:semicolon
id|ix
OL
id|cnt
suffix:semicolon
id|ix
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|av
(braket
id|ix
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
id|no_more_options
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_more_options
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--remote=&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|remote
)paren
id|die
c_func
(paren
l_string|&quot;Multiple --remote specified&quot;
)paren
suffix:semicolon
id|remote
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
id|no_more_options
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ix
op_ne
id|iy
)paren
id|av
(braket
id|iy
)braket
op_assign
id|arg
suffix:semicolon
id|iy
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|remote
)paren
(brace
id|av
(braket
op_decrement
id|cnt
)braket
op_assign
l_int|NULL
suffix:semicolon
op_star
id|ac
op_assign
id|cnt
suffix:semicolon
)brace
r_return
id|remote
suffix:semicolon
)brace
DECL|function|cmd_archive
r_int
id|cmd_archive
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
r_struct
id|archiver
id|ar
suffix:semicolon
r_int
id|tree_idx
suffix:semicolon
r_const
r_char
op_star
id|remote
op_assign
l_int|NULL
suffix:semicolon
id|remote
op_assign
id|extract_remote_arg
c_func
(paren
op_amp
id|argc
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
)paren
r_return
id|run_remote_archiver
c_func
(paren
id|remote
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
id|setvbuf
c_func
(paren
id|stderr
comma
l_int|NULL
comma
id|_IOLBF
comma
id|BUFSIZ
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ar
comma
l_int|0
comma
r_sizeof
(paren
id|ar
)paren
)paren
suffix:semicolon
id|tree_idx
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
)paren
suffix:semicolon
r_if
c_cond
(paren
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
id|argv
op_add_assign
id|tree_idx
suffix:semicolon
id|parse_treeish_arg
c_func
(paren
id|argv
comma
op_amp
id|ar.args
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
id|ar.args
)paren
suffix:semicolon
r_return
id|ar
dot
id|write_archive
c_func
(paren
op_amp
id|ar.args
)paren
suffix:semicolon
)brace
eof
