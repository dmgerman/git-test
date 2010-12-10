multiline_comment|/*&n; * Licensed under a two-clause BSD-style license.&n; * See LICENSE for details.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;fast_export.h&quot;
macro_line|#include &quot;line_buffer.h&quot;
macro_line|#include &quot;repo_tree.h&quot;
macro_line|#include &quot;string_pool.h&quot;
macro_line|#include &quot;strbuf.h&quot;
DECL|macro|MAX_GITSVN_LINE_LEN
mdefine_line|#define MAX_GITSVN_LINE_LEN 4096
DECL|variable|first_commit_done
r_static
r_uint32
id|first_commit_done
suffix:semicolon
DECL|variable|report_buffer
r_static
r_struct
id|line_buffer
id|report_buffer
op_assign
id|LINE_BUFFER_INIT
suffix:semicolon
DECL|function|fast_export_init
r_void
id|fast_export_init
c_func
(paren
r_int
id|fd
)paren
(brace
r_if
c_cond
(paren
id|buffer_fdinit
c_func
(paren
op_amp
id|report_buffer
comma
id|fd
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot read from file descriptor %d&quot;
comma
id|fd
)paren
suffix:semicolon
)brace
DECL|function|fast_export_deinit
r_void
id|fast_export_deinit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|buffer_deinit
c_func
(paren
op_amp
id|report_buffer
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;error closing fast-import feedback stream&quot;
)paren
suffix:semicolon
)brace
DECL|function|fast_export_reset
r_void
id|fast_export_reset
c_func
(paren
r_void
)paren
(brace
id|buffer_reset
c_func
(paren
op_amp
id|report_buffer
)paren
suffix:semicolon
)brace
DECL|function|fast_export_delete
r_void
id|fast_export_delete
c_func
(paren
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
)paren
(brace
id|putchar
c_func
(paren
l_char|&squot;D&squot;
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|pool_print_seq
c_func
(paren
id|depth
comma
id|path
comma
l_char|&squot;/&squot;
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|fast_export_truncate
r_static
r_void
id|fast_export_truncate
c_func
(paren
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
comma
r_uint32
id|mode
)paren
(brace
id|fast_export_modify
c_func
(paren
id|depth
comma
id|path
comma
id|mode
comma
l_string|&quot;inline&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;data 0&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|fast_export_modify
r_void
id|fast_export_modify
c_func
(paren
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
comma
r_uint32
id|mode
comma
r_const
r_char
op_star
id|dataref
)paren
(brace
multiline_comment|/* Mode must be 100644, 100755, 120000, or 160000. */
r_if
c_cond
(paren
op_logical_neg
id|dataref
)paren
(brace
id|fast_export_truncate
c_func
(paren
id|depth
comma
id|path
comma
id|mode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;M %06&quot;
id|PRIo32
l_string|&quot; %s &quot;
comma
id|mode
comma
id|dataref
)paren
suffix:semicolon
id|pool_print_seq
c_func
(paren
id|depth
comma
id|path
comma
l_char|&squot;/&squot;
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|variable|gitsvnline
r_static
r_char
id|gitsvnline
(braket
id|MAX_GITSVN_LINE_LEN
)braket
suffix:semicolon
DECL|function|fast_export_begin_commit
r_void
id|fast_export_begin_commit
c_func
(paren
r_uint32
id|revision
comma
r_uint32
id|author
comma
r_char
op_star
id|log
comma
r_uint32
id|uuid
comma
r_uint32
id|url
comma
r_int
r_int
id|timestamp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|log
)paren
id|log
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|uuid
op_logical_and
op_complement
id|url
)paren
(brace
id|snprintf
c_func
(paren
id|gitsvnline
comma
id|MAX_GITSVN_LINE_LEN
comma
l_string|&quot;&bslash;n&bslash;ngit-svn-id: %s@%&quot;
id|PRIu32
l_string|&quot; %s&bslash;n&quot;
comma
id|pool_fetch
c_func
(paren
id|url
)paren
comma
id|revision
comma
id|pool_fetch
c_func
(paren
id|uuid
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|gitsvnline
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;commit refs/heads/master&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;mark :%&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|revision
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;committer %s &lt;%s@%s&gt; %ld +0000&bslash;n&quot;
comma
op_complement
id|author
ques
c_cond
id|pool_fetch
c_func
(paren
id|author
)paren
suffix:colon
l_string|&quot;nobody&quot;
comma
op_complement
id|author
ques
c_cond
id|pool_fetch
c_func
(paren
id|author
)paren
suffix:colon
l_string|&quot;nobody&quot;
comma
op_complement
id|uuid
ques
c_cond
id|pool_fetch
c_func
(paren
id|uuid
)paren
suffix:colon
l_string|&quot;local&quot;
comma
id|timestamp
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;data %&quot;
id|PRIu32
l_string|&quot;&bslash;n%s%s&bslash;n&quot;
comma
(paren
r_uint32
)paren
(paren
id|strlen
c_func
(paren
id|log
)paren
op_plus
id|strlen
c_func
(paren
id|gitsvnline
)paren
)paren
comma
id|log
comma
id|gitsvnline
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first_commit_done
)paren
(brace
r_if
c_cond
(paren
id|revision
OG
l_int|1
)paren
id|printf
c_func
(paren
l_string|&quot;from refs/heads/master^0&bslash;n&quot;
)paren
suffix:semicolon
id|first_commit_done
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|fast_export_end_commit
r_void
id|fast_export_end_commit
c_func
(paren
r_uint32
id|revision
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;progress Imported commit %&quot;
id|PRIu32
l_string|&quot;.&bslash;n&bslash;n&quot;
comma
id|revision
)paren
suffix:semicolon
)brace
DECL|function|ls_from_rev
r_static
r_void
id|ls_from_rev
c_func
(paren
r_uint32
id|rev
comma
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
)paren
(brace
multiline_comment|/* ls :5 path/to/old/file */
id|printf
c_func
(paren
l_string|&quot;ls :%&quot;
id|PRIu32
l_string|&quot; &quot;
comma
id|rev
)paren
suffix:semicolon
id|pool_print_seq
c_func
(paren
id|depth
comma
id|path
comma
l_char|&squot;/&squot;
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
DECL|function|ls_from_active_commit
r_static
r_void
id|ls_from_active_commit
c_func
(paren
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
)paren
(brace
multiline_comment|/* ls &quot;path/to/file&quot; */
id|printf
c_func
(paren
l_string|&quot;ls &bslash;&quot;&quot;
)paren
suffix:semicolon
id|pool_print_seq
c_func
(paren
id|depth
comma
id|path
comma
l_char|&squot;/&squot;
comma
id|stdout
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
DECL|function|get_response_line
r_static
r_const
r_char
op_star
id|get_response_line
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|line
op_assign
id|buffer_read_line
c_func
(paren
op_amp
id|report_buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
)paren
r_return
id|line
suffix:semicolon
r_if
c_cond
(paren
id|buffer_ferror
c_func
(paren
op_amp
id|report_buffer
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;error reading from fast-import&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unexpected end of fast-import feedback&quot;
)paren
suffix:semicolon
)brace
DECL|function|fast_export_data
r_void
id|fast_export_data
c_func
(paren
r_uint32
id|mode
comma
r_uint32
id|len
comma
r_struct
id|line_buffer
op_star
id|input
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|REPO_MODE_LNK
)paren
(brace
multiline_comment|/* svn symlink blobs start with &quot;link &quot; */
id|buffer_skip_bytes
c_func
(paren
id|input
comma
l_int|5
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|5
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;data %&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
id|buffer_copy_bytes
c_func
(paren
id|input
comma
id|len
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stdout
)paren
suffix:semicolon
)brace
DECL|function|parse_ls_response
r_static
r_int
id|parse_ls_response
c_func
(paren
r_const
r_char
op_star
id|response
comma
r_uint32
op_star
id|mode
comma
r_struct
id|strbuf
op_star
id|dataref
)paren
(brace
r_const
r_char
op_star
id|tab
suffix:semicolon
r_const
r_char
op_star
id|response_end
suffix:semicolon
m_assert
(paren
id|response
)paren
suffix:semicolon
id|response_end
op_assign
id|response
op_plus
id|strlen
c_func
(paren
id|response
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|response
op_eq
l_char|&squot;m&squot;
)paren
(brace
multiline_comment|/* Missing. */
id|errno
op_assign
id|ENOENT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Mode. */
r_if
c_cond
(paren
id|response_end
id|response
OL
id|strlen
c_func
(paren
l_string|&quot;100644&quot;
)paren
op_logical_or
id|response
(braket
id|strlen
c_func
(paren
l_string|&quot;100644&quot;
)paren
)braket
op_ne
l_char|&squot; &squot;
)paren
id|die
c_func
(paren
l_string|&quot;invalid ls response: missing mode: %s&quot;
comma
id|response
)paren
suffix:semicolon
op_star
id|mode
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|response
op_ne
l_char|&squot; &squot;
suffix:semicolon
id|response
op_increment
)paren
(brace
r_char
id|ch
op_assign
op_star
id|response
suffix:semicolon
r_if
c_cond
(paren
id|ch
template_param
l_char|&squot;7&squot;
)paren
id|die
c_func
(paren
l_string|&quot;invalid ls response: mode is not octal: %s&quot;
comma
id|response
)paren
suffix:semicolon
op_star
id|mode
op_mul_assign
l_int|8
suffix:semicolon
op_star
id|mode
op_add_assign
id|ch
l_char|&squot;0&squot;
suffix:semicolon
)brace
multiline_comment|/* &squot; blob &squot; or &squot; tree &squot; */
r_if
c_cond
(paren
id|response_end
id|response
OL
id|strlen
c_func
(paren
l_string|&quot; blob &quot;
)paren
op_logical_or
(paren
id|response
(braket
l_int|1
)braket
op_ne
l_char|&squot;b&squot;
op_logical_and
id|response
(braket
l_int|1
)braket
op_ne
l_char|&squot;t&squot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unexpected ls response: not a tree or blob: %s&quot;
comma
id|response
)paren
suffix:semicolon
id|response
op_add_assign
id|strlen
c_func
(paren
l_string|&quot; blob &quot;
)paren
suffix:semicolon
multiline_comment|/* Dataref. */
id|tab
op_assign
id|memchr
c_func
(paren
id|response
comma
l_char|&squot;&bslash;t&squot;
comma
id|response_end
id|response
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tab
)paren
id|die
c_func
(paren
l_string|&quot;invalid ls response: missing tab: %s&quot;
comma
id|response
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|dataref
comma
id|response
comma
id|tab
id|response
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fast_export_ls_rev
r_int
id|fast_export_ls_rev
c_func
(paren
r_uint32
id|rev
comma
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
comma
r_uint32
op_star
id|mode
comma
r_struct
id|strbuf
op_star
id|dataref
)paren
(brace
id|ls_from_rev
c_func
(paren
id|rev
comma
id|depth
comma
id|path
)paren
suffix:semicolon
r_return
id|parse_ls_response
c_func
(paren
id|get_response_line
c_func
(paren
)paren
comma
id|mode
comma
id|dataref
)paren
suffix:semicolon
)brace
DECL|function|fast_export_ls
r_int
id|fast_export_ls
c_func
(paren
r_uint32
id|depth
comma
r_const
r_uint32
op_star
id|path
comma
r_uint32
op_star
id|mode
comma
r_struct
id|strbuf
op_star
id|dataref
)paren
(brace
id|ls_from_active_commit
c_func
(paren
id|depth
comma
id|path
)paren
suffix:semicolon
r_return
id|parse_ls_response
c_func
(paren
id|get_response_line
c_func
(paren
)paren
comma
id|mode
comma
id|dataref
)paren
suffix:semicolon
)brace
eof
