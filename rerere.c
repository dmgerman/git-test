macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;rerere.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;resolve-undo.h&quot;
macro_line|#include &quot;ll-merge.h&quot;
macro_line|#include &quot;attr.h&quot;
multiline_comment|/* if rerere_enabled == -1, fall back to detection of .git/rr-cache */
DECL|variable|rerere_enabled
r_static
r_int
id|rerere_enabled
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* automatically update cleanly resolved paths to the index */
DECL|variable|rerere_autoupdate
r_static
r_int
id|rerere_autoupdate
suffix:semicolon
DECL|variable|merge_rr_path
r_static
r_char
op_star
id|merge_rr_path
suffix:semicolon
DECL|function|rerere_path
r_const
r_char
op_star
id|rerere_path
c_func
(paren
r_const
r_char
op_star
id|hex
comma
r_const
r_char
op_star
id|file
)paren
(brace
r_return
id|git_path
c_func
(paren
l_string|&quot;rr-cache/%s/%s&quot;
comma
id|hex
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|has_rerere_resolution
r_int
id|has_rerere_resolution
c_func
(paren
r_const
r_char
op_star
id|hex
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_return
op_logical_neg
id|stat
c_func
(paren
id|rerere_path
c_func
(paren
id|hex
comma
l_string|&quot;postimage&quot;
)paren
comma
op_amp
id|st
)paren
suffix:semicolon
)brace
DECL|function|read_rr
r_static
r_void
id|read_rr
c_func
(paren
r_struct
id|string_list
op_star
id|rr
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|buf
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|FILE
op_star
id|in
op_assign
id|fopen
c_func
(paren
id|merge_rr_path
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|fread
c_func
(paren
id|buf
comma
l_int|40
comma
l_int|1
comma
id|in
)paren
op_eq
l_int|1
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buf
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt MERGE_RR&quot;
)paren
suffix:semicolon
id|buf
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|name
op_assign
id|xstrdup
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fgetc
c_func
(paren
id|in
)paren
op_ne
l_char|&squot;&bslash;t&squot;
)paren
id|die
c_func
(paren
l_string|&quot;corrupt MERGE_RR&quot;
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
r_sizeof
(paren
id|buf
)paren
op_logical_and
(paren
id|buf
(braket
id|i
)braket
op_assign
id|fgetc
c_func
(paren
id|in
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
multiline_comment|/* do nothing */
r_if
c_cond
(paren
id|i
op_eq
r_sizeof
(paren
id|buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;filename too long&quot;
)paren
suffix:semicolon
id|string_list_insert
c_func
(paren
id|rr
comma
id|buf
)paren
op_member_access_from_pointer
id|util
op_assign
id|name
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|in
)paren
suffix:semicolon
)brace
DECL|variable|write_lock
r_static
r_struct
id|lock_file
id|write_lock
suffix:semicolon
DECL|function|write_rr
r_static
r_int
id|write_rr
c_func
(paren
r_struct
id|string_list
op_star
id|rr
comma
r_int
id|out_fd
)paren
(brace
r_int
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
id|rr-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
id|length
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rr-&gt;items
(braket
id|i
)braket
dot
id|util
)paren
r_continue
suffix:semicolon
id|path
op_assign
id|rr-&gt;items
(braket
id|i
)braket
dot
id|string
suffix:semicolon
id|length
op_assign
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|out_fd
comma
id|rr-&gt;items
(braket
id|i
)braket
dot
id|util
comma
l_int|40
)paren
op_ne
l_int|40
op_logical_or
id|write_str_in_full
c_func
(paren
id|out_fd
comma
l_string|&quot;&bslash;t&quot;
)paren
op_ne
l_int|1
op_logical_or
id|write_in_full
c_func
(paren
id|out_fd
comma
id|path
comma
id|length
)paren
op_ne
id|length
)paren
id|die
c_func
(paren
l_string|&quot;unable to write rerere record&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|commit_lock_file
c_func
(paren
op_amp
id|write_lock
)paren
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to write rerere record&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ferr_write
r_static
r_void
id|ferr_write
c_func
(paren
r_const
r_void
op_star
id|p
comma
r_int
id|count
comma
id|FILE
op_star
id|fp
comma
r_int
op_star
id|err
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|count
op_logical_or
op_star
id|err
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|p
comma
id|count
comma
l_int|1
comma
id|fp
)paren
op_ne
l_int|1
)paren
op_star
id|err
op_assign
id|errno
suffix:semicolon
)brace
DECL|function|ferr_puts
r_static
r_inline
r_void
id|ferr_puts
c_func
(paren
r_const
r_char
op_star
id|s
comma
id|FILE
op_star
id|fp
comma
r_int
op_star
id|err
)paren
(brace
id|ferr_write
c_func
(paren
id|s
comma
id|strlen
c_func
(paren
id|s
)paren
comma
id|fp
comma
id|err
)paren
suffix:semicolon
)brace
DECL|struct|rerere_io
r_struct
id|rerere_io
(brace
DECL|member|getline
r_int
(paren
op_star
id|getline
)paren
(paren
r_struct
id|strbuf
op_star
comma
r_struct
id|rerere_io
op_star
)paren
suffix:semicolon
DECL|member|output
id|FILE
op_star
id|output
suffix:semicolon
DECL|member|wrerror
r_int
id|wrerror
suffix:semicolon
multiline_comment|/* some more stuff */
)brace
suffix:semicolon
DECL|function|rerere_io_putstr
r_static
r_void
id|rerere_io_putstr
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|rerere_io
op_star
id|io
)paren
(brace
r_if
c_cond
(paren
id|io-&gt;output
)paren
id|ferr_puts
c_func
(paren
id|str
comma
id|io-&gt;output
comma
op_amp
id|io-&gt;wrerror
)paren
suffix:semicolon
)brace
DECL|function|rerere_io_putconflict
r_static
r_void
id|rerere_io_putconflict
c_func
(paren
r_int
id|ch
comma
r_int
id|size
comma
r_struct
id|rerere_io
op_star
id|io
)paren
(brace
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
OL
r_sizeof
(paren
id|buf
)paren
l_int|2
)paren
(brace
id|memset
c_func
(paren
id|buf
comma
id|ch
comma
id|size
)paren
suffix:semicolon
id|buf
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|size
op_plus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|size
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
id|sz
op_assign
r_sizeof
(paren
id|buf
)paren
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|sz
)paren
id|sz
op_sub_assign
(paren
id|sz
id|size
)paren
op_plus
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
id|ch
comma
id|sz
)paren
suffix:semicolon
id|buf
(braket
id|sz
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|size
op_sub_assign
id|sz
suffix:semicolon
)brace
id|rerere_io_putstr
c_func
(paren
id|buf
comma
id|io
)paren
suffix:semicolon
)brace
)brace
DECL|function|rerere_io_putmem
r_static
r_void
id|rerere_io_putmem
c_func
(paren
r_const
r_char
op_star
id|mem
comma
r_int
id|sz
comma
r_struct
id|rerere_io
op_star
id|io
)paren
(brace
r_if
c_cond
(paren
id|io-&gt;output
)paren
id|ferr_write
c_func
(paren
id|mem
comma
id|sz
comma
id|io-&gt;output
comma
op_amp
id|io-&gt;wrerror
)paren
suffix:semicolon
)brace
DECL|struct|rerere_io_file
r_struct
id|rerere_io_file
(brace
DECL|member|io
r_struct
id|rerere_io
id|io
suffix:semicolon
DECL|member|input
id|FILE
op_star
id|input
suffix:semicolon
)brace
suffix:semicolon
DECL|function|rerere_file_getline
r_static
r_int
id|rerere_file_getline
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_struct
id|rerere_io
op_star
id|io_
)paren
(brace
r_struct
id|rerere_io_file
op_star
id|io
op_assign
(paren
r_struct
id|rerere_io_file
op_star
)paren
id|io_
suffix:semicolon
r_return
id|strbuf_getwholeline
c_func
(paren
id|sb
comma
id|io-&gt;input
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|is_cmarker
r_static
r_int
id|is_cmarker
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|marker_char
comma
r_int
id|marker_size
comma
r_int
id|want_sp
)paren
(brace
r_while
c_loop
(paren
id|marker_size
op_decrement
)paren
r_if
c_cond
(paren
op_star
id|buf
op_increment
op_ne
id|marker_char
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|want_sp
op_logical_and
op_star
id|buf
op_ne
l_char|&squot; &squot;
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|isspace
c_func
(paren
op_star
id|buf
)paren
suffix:semicolon
)brace
DECL|function|handle_path
r_static
r_int
id|handle_path
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_struct
id|rerere_io
op_star
id|io
comma
r_int
id|marker_size
)paren
(brace
id|git_SHA_CTX
id|ctx
suffix:semicolon
r_int
id|hunk_no
op_assign
l_int|0
suffix:semicolon
r_enum
(brace
id|RR_CONTEXT
op_assign
l_int|0
comma
id|RR_SIDE_1
comma
id|RR_SIDE_2
comma
id|RR_ORIGINAL
)brace
id|hunk
op_assign
id|RR_CONTEXT
suffix:semicolon
r_struct
id|strbuf
id|one
op_assign
id|STRBUF_INIT
comma
id|two
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|sha1
)paren
id|git_SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|io
op_member_access_from_pointer
id|getline
c_func
(paren
op_amp
id|buf
comma
id|io
)paren
)paren
(brace
r_if
c_cond
(paren
id|is_cmarker
c_func
(paren
id|buf.buf
comma
l_char|&squot;&lt;&squot;
comma
id|marker_size
comma
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|hunk
op_ne
id|RR_CONTEXT
)paren
r_goto
id|bad
suffix:semicolon
id|hunk
op_assign
id|RR_SIDE_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_cmarker
c_func
(paren
id|buf.buf
comma
l_char|&squot;|&squot;
comma
id|marker_size
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|hunk
op_ne
id|RR_SIDE_1
)paren
r_goto
id|bad
suffix:semicolon
id|hunk
op_assign
id|RR_ORIGINAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_cmarker
c_func
(paren
id|buf.buf
comma
l_char|&squot;=&squot;
comma
id|marker_size
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|hunk
op_ne
id|RR_SIDE_1
op_logical_and
id|hunk
op_ne
id|RR_ORIGINAL
)paren
r_goto
id|bad
suffix:semicolon
id|hunk
op_assign
id|RR_SIDE_2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_cmarker
c_func
(paren
id|buf.buf
comma
l_char|&squot;&gt;&squot;
comma
id|marker_size
comma
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|hunk
op_ne
id|RR_SIDE_2
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_cmp
c_func
(paren
op_amp
id|one
comma
op_amp
id|two
)paren
OG
l_int|0
)paren
id|strbuf_swap
c_func
(paren
op_amp
id|one
comma
op_amp
id|two
)paren
suffix:semicolon
id|hunk_no
op_increment
suffix:semicolon
id|hunk
op_assign
id|RR_CONTEXT
suffix:semicolon
id|rerere_io_putconflict
c_func
(paren
l_char|&squot;&lt;&squot;
comma
id|marker_size
comma
id|io
)paren
suffix:semicolon
id|rerere_io_putmem
c_func
(paren
id|one.buf
comma
id|one.len
comma
id|io
)paren
suffix:semicolon
id|rerere_io_putconflict
c_func
(paren
l_char|&squot;=&squot;
comma
id|marker_size
comma
id|io
)paren
suffix:semicolon
id|rerere_io_putmem
c_func
(paren
id|two.buf
comma
id|two.len
comma
id|io
)paren
suffix:semicolon
id|rerere_io_putconflict
c_func
(paren
l_char|&squot;&gt;&squot;
comma
id|marker_size
comma
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sha1
)paren
(brace
id|git_SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|one.buf
ques
c_cond
id|one.buf
suffix:colon
l_string|&quot;&quot;
comma
id|one.len
op_plus
l_int|1
)paren
suffix:semicolon
id|git_SHA1_Update
c_func
(paren
op_amp
id|ctx
comma
id|two.buf
ques
c_cond
id|two.buf
suffix:colon
l_string|&quot;&quot;
comma
id|two.len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|one
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|two
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hunk
op_eq
id|RR_SIDE_1
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|one
comma
id|buf.buf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|hunk
op_eq
id|RR_ORIGINAL
)paren
suffix:semicolon
multiline_comment|/* discard */
r_else
r_if
c_cond
(paren
id|hunk
op_eq
id|RR_SIDE_2
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|two
comma
id|buf.buf
)paren
suffix:semicolon
r_else
id|rerere_io_putstr
c_func
(paren
id|buf.buf
comma
id|io
)paren
suffix:semicolon
r_continue
suffix:semicolon
id|bad
suffix:colon
id|hunk
op_assign
l_int|99
suffix:semicolon
multiline_comment|/* force error exit */
r_break
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|one
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|two
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sha1
)paren
id|git_SHA1_Final
c_func
(paren
id|sha1
comma
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hunk
op_ne
id|RR_CONTEXT
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|hunk_no
suffix:semicolon
)brace
DECL|function|handle_file
r_static
r_int
id|handle_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|output
)paren
(brace
r_int
id|hunk_no
op_assign
l_int|0
suffix:semicolon
r_struct
id|rerere_io_file
id|io
suffix:semicolon
r_int
id|marker_size
op_assign
id|ll_merge_marker_size
c_func
(paren
id|path
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|io
comma
l_int|0
comma
r_sizeof
(paren
id|io
)paren
)paren
suffix:semicolon
id|io.io.getline
op_assign
id|rerere_file_getline
suffix:semicolon
id|io.input
op_assign
id|fopen
c_func
(paren
id|path
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|io.io.wrerror
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io.input
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open %s&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output
)paren
(brace
id|io.io.output
op_assign
id|fopen
c_func
(paren
id|output
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io.io.output
)paren
(brace
id|fclose
c_func
(paren
id|io.input
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Could not write %s&quot;
comma
id|output
)paren
suffix:semicolon
)brace
)brace
id|hunk_no
op_assign
id|handle_path
c_func
(paren
id|sha1
comma
(paren
r_struct
id|rerere_io
op_star
)paren
op_amp
id|io
comma
id|marker_size
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|io.input
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io.io.wrerror
)paren
id|error
c_func
(paren
l_string|&quot;There were errors while writing %s (%s)&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|io.io.wrerror
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io.io.output
op_logical_and
id|fclose
c_func
(paren
id|io.io.output
)paren
)paren
id|io.io.wrerror
op_assign
id|error
c_func
(paren
l_string|&quot;Failed to flush %s: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hunk_no
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|output
)paren
id|unlink_or_warn
c_func
(paren
id|output
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Could not parse conflict hunks in %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|io.io.wrerror
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|hunk_no
suffix:semicolon
)brace
DECL|struct|rerere_io_mem
r_struct
id|rerere_io_mem
(brace
DECL|member|io
r_struct
id|rerere_io
id|io
suffix:semicolon
DECL|member|input
r_struct
id|strbuf
id|input
suffix:semicolon
)brace
suffix:semicolon
DECL|function|rerere_mem_getline
r_static
r_int
id|rerere_mem_getline
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_struct
id|rerere_io
op_star
id|io_
)paren
(brace
r_struct
id|rerere_io_mem
op_star
id|io
op_assign
(paren
r_struct
id|rerere_io_mem
op_star
)paren
id|io_
suffix:semicolon
r_char
op_star
id|ep
suffix:semicolon
r_int
id|len
suffix:semicolon
id|strbuf_release
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io-&gt;input.len
)paren
r_return
l_int|1
suffix:semicolon
id|ep
op_assign
id|strchrnul
c_func
(paren
id|io-&gt;input.buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ep
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|ep
op_increment
suffix:semicolon
id|len
op_assign
id|ep
id|io-&gt;input.buf
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|io-&gt;input.buf
comma
id|len
)paren
suffix:semicolon
id|strbuf_remove
c_func
(paren
op_amp
id|io-&gt;input
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|handle_cache
r_static
r_int
id|handle_cache
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|output
)paren
(brace
id|mmfile_t
id|mmfile
(braket
l_int|3
)braket
suffix:semicolon
id|mmbuffer_t
id|result
op_assign
(brace
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_int
id|pos
comma
id|len
comma
id|i
comma
id|hunk_no
suffix:semicolon
r_struct
id|rerere_io_mem
id|io
suffix:semicolon
r_int
id|marker_size
op_assign
id|ll_merge_marker_size
c_func
(paren
id|path
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reproduce the conflicted merge in-core&n;&t; */
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
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
r_return
l_int|1
suffix:semicolon
id|pos
op_assign
id|pos
l_int|1
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|mmfile
(braket
id|i
)braket
dot
id|size
op_assign
l_int|0
suffix:semicolon
id|mmfile
(braket
id|i
)braket
dot
id|ptr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|active_nr
op_le
id|pos
)paren
r_break
suffix:semicolon
id|ce
op_assign
id|active_cache
(braket
id|pos
op_increment
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
op_ne
id|len
op_logical_or
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|len
)paren
op_logical_or
id|ce_stage
c_func
(paren
id|ce
)paren
op_ne
id|i
op_plus
l_int|1
)paren
r_break
suffix:semicolon
id|mmfile
(braket
id|i
)braket
dot
id|ptr
op_assign
id|read_sha1_file
c_func
(paren
id|ce-&gt;sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
id|mmfile
(braket
id|i
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mmfile
(braket
id|i
)braket
dot
id|ptr
op_logical_and
op_logical_neg
id|mmfile
(braket
id|i
)braket
dot
id|size
)paren
id|mmfile
(braket
id|i
)braket
dot
id|ptr
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * NEEDSWORK: handle conflicts from merges with&n;&t; * merge.renormalize set, too&n;&t; */
id|ll_merge
c_func
(paren
op_amp
id|result
comma
id|path
comma
op_amp
id|mmfile
(braket
l_int|0
)braket
comma
l_int|NULL
comma
op_amp
id|mmfile
(braket
l_int|1
)braket
comma
l_string|&quot;ours&quot;
comma
op_amp
id|mmfile
(braket
l_int|2
)braket
comma
l_string|&quot;theirs&quot;
comma
l_int|0
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|mmfile
(braket
id|i
)braket
dot
id|ptr
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|io
comma
l_int|0
comma
r_sizeof
(paren
id|io
)paren
)paren
suffix:semicolon
id|io.io.getline
op_assign
id|rerere_mem_getline
suffix:semicolon
r_if
c_cond
(paren
id|output
)paren
id|io.io.output
op_assign
id|fopen
c_func
(paren
id|output
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_else
id|io.io.output
op_assign
l_int|NULL
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|io.input
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_attach
c_func
(paren
op_amp
id|io.input
comma
id|result.ptr
comma
id|result.size
comma
id|result.size
)paren
suffix:semicolon
id|hunk_no
op_assign
id|handle_path
c_func
(paren
id|sha1
comma
(paren
r_struct
id|rerere_io
op_star
)paren
op_amp
id|io
comma
id|marker_size
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|io.input
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io.io.output
)paren
id|fclose
c_func
(paren
id|io.io.output
)paren
suffix:semicolon
r_return
id|hunk_no
suffix:semicolon
)brace
DECL|function|find_conflict
r_static
r_int
id|find_conflict
c_func
(paren
r_struct
id|string_list
op_star
id|conflict
)paren
(brace
r_int
id|i
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
r_return
id|error
c_func
(paren
l_string|&quot;Could not read index&quot;
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
op_plus
l_int|1
OL
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|e2
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|e3
op_assign
id|active_cache
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|e2
)paren
op_eq
l_int|2
op_logical_and
id|ce_stage
c_func
(paren
id|e3
)paren
op_eq
l_int|3
op_logical_and
id|ce_same_name
c_func
(paren
id|e2
comma
id|e3
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|e2-&gt;ce_mode
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|e3-&gt;ce_mode
)paren
)paren
(brace
id|string_list_insert
c_func
(paren
id|conflict
comma
(paren
r_const
r_char
op_star
)paren
id|e2-&gt;name
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
multiline_comment|/* skip over both #2 and #3 */
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|merge
r_static
r_int
id|merge
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|ret
suffix:semicolon
id|mmfile_t
id|cur
op_assign
(brace
l_int|NULL
comma
l_int|0
)brace
comma
id|base
op_assign
(brace
l_int|NULL
comma
l_int|0
)brace
comma
id|other
op_assign
(brace
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
id|mmbuffer_t
id|result
op_assign
(brace
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
id|handle_file
c_func
(paren
id|path
comma
l_int|NULL
comma
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;thisimage&quot;
)paren
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|read_mmfile
c_func
(paren
op_amp
id|cur
comma
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;thisimage&quot;
)paren
)paren
op_logical_or
id|read_mmfile
c_func
(paren
op_amp
id|base
comma
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;preimage&quot;
)paren
)paren
op_logical_or
id|read_mmfile
c_func
(paren
op_amp
id|other
comma
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
)paren
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|ll_merge
c_func
(paren
op_amp
id|result
comma
id|path
comma
op_amp
id|base
comma
l_int|NULL
comma
op_amp
id|cur
comma
l_string|&quot;&quot;
comma
op_amp
id|other
comma
l_string|&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|FILE
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
id|utime
c_func
(paren
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
comma
l_int|NULL
)paren
OL
l_int|0
)paren
id|warning
c_func
(paren
l_string|&quot;failed utime() on %s: %s&quot;
comma
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|f
op_assign
id|fopen
c_func
(paren
id|path
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open %s: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|result.ptr
comma
id|result.size
comma
l_int|1
comma
id|f
)paren
op_ne
l_int|1
)paren
id|error
c_func
(paren
l_string|&quot;Could not write %s: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|f
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Writing %s failed: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|free
c_func
(paren
id|cur.ptr
)paren
suffix:semicolon
id|free
c_func
(paren
id|base.ptr
)paren
suffix:semicolon
id|free
c_func
(paren
id|other.ptr
)paren
suffix:semicolon
id|free
c_func
(paren
id|result.ptr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|index_lock
r_static
r_struct
id|lock_file
id|index_lock
suffix:semicolon
DECL|function|update_paths
r_static
r_int
id|update_paths
c_func
(paren
r_struct
id|string_list
op_star
id|update
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|fd
op_assign
id|hold_locked_index
c_func
(paren
op_amp
id|index_lock
comma
l_int|0
)paren
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|1
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
id|update-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|string_list_item
op_star
id|item
op_assign
op_amp
id|update-&gt;items
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|add_file_to_cache
c_func
(paren
id|item-&gt;string
comma
id|ADD_CACHE_IGNORE_ERRORS
)paren
)paren
id|status
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|status
op_logical_and
id|active_cache_changed
)paren
(brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|fd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
op_amp
id|index_lock
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
id|rollback_lock_file
c_func
(paren
op_amp
id|index_lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|do_plain_rerere
r_static
r_int
id|do_plain_rerere
c_func
(paren
r_struct
id|string_list
op_star
id|rr
comma
r_int
id|fd
)paren
(brace
r_struct
id|string_list
id|conflict
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|string_list
id|update
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_int
id|i
suffix:semicolon
id|find_conflict
c_func
(paren
op_amp
id|conflict
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * MERGE_RR records paths with conflicts immediately after merge&n;&t; * failed.  Some of the conflicted paths might have been hand resolved&n;&t; * in the working tree since then, but the initial run would catch all&n;&t; * and register their preimages.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|conflict.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
id|conflict.items
(braket
id|i
)braket
dot
id|string
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|string_list_has_string
c_func
(paren
id|rr
comma
id|path
)paren
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|hex
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|handle_file
c_func
(paren
id|path
comma
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|1
)paren
r_continue
suffix:semicolon
id|hex
op_assign
id|xstrdup
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|string_list_insert
c_func
(paren
id|rr
comma
id|path
)paren
op_member_access_from_pointer
id|util
op_assign
id|hex
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;rr-cache/%s&quot;
comma
id|hex
)paren
comma
l_int|0755
)paren
)paren
r_continue
suffix:semicolon
id|handle_file
c_func
(paren
id|path
comma
l_int|NULL
comma
id|rerere_path
c_func
(paren
id|hex
comma
l_string|&quot;preimage&quot;
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Recorded preimage for &squot;%s&squot;&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Now some of the paths that had conflicts earlier might have been&n;&t; * hand resolved.  Others may be similar to a conflict already that&n;&t; * was resolved before.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|rr-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|ret
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
id|rr-&gt;items
(braket
id|i
)braket
dot
id|string
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
(paren
r_const
r_char
op_star
)paren
id|rr-&gt;items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_if
c_cond
(paren
id|has_rerere_resolution
c_func
(paren
id|name
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|merge
c_func
(paren
id|name
comma
id|path
)paren
)paren
(brace
r_if
c_cond
(paren
id|rerere_autoupdate
)paren
id|string_list_insert
c_func
(paren
op_amp
id|update
comma
id|path
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s &squot;%s&squot; using previous resolution.&bslash;n&quot;
comma
id|rerere_autoupdate
ques
c_cond
l_string|&quot;Staged&quot;
suffix:colon
l_string|&quot;Resolved&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|mark_resolved
suffix:semicolon
)brace
)brace
multiline_comment|/* Let&squot;s see if we have resolved it. */
id|ret
op_assign
id|handle_file
c_func
(paren
id|path
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_continue
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Recorded resolution for &squot;%s&squot;.&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
id|copy_file
c_func
(paren
id|rerere_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
comma
id|path
comma
l_int|0666
)paren
suffix:semicolon
id|mark_resolved
suffix:colon
id|rr-&gt;items
(braket
id|i
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|update.nr
)paren
id|update_paths
c_func
(paren
op_amp
id|update
)paren
suffix:semicolon
r_return
id|write_rr
c_func
(paren
id|rr
comma
id|fd
)paren
suffix:semicolon
)brace
DECL|function|git_rerere_config
r_static
r_int
id|git_rerere_config
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
l_string|&quot;rerere.enabled&quot;
)paren
)paren
id|rerere_enabled
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;rerere.autoupdate&quot;
)paren
)paren
id|rerere_autoupdate
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_else
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|is_rerere_enabled
r_static
r_int
id|is_rerere_enabled
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|rr_cache
suffix:semicolon
r_int
id|rr_cache_exists
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rerere_enabled
)paren
r_return
l_int|0
suffix:semicolon
id|rr_cache
op_assign
id|git_path
c_func
(paren
l_string|&quot;rr-cache&quot;
)paren
suffix:semicolon
id|rr_cache_exists
op_assign
id|is_directory
c_func
(paren
id|rr_cache
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rerere_enabled
OL
l_int|0
)paren
r_return
id|rr_cache_exists
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rr_cache_exists
op_logical_and
(paren
id|mkdir
c_func
(paren
id|rr_cache
comma
l_int|0777
)paren
op_logical_or
id|adjust_shared_perm
c_func
(paren
id|rr_cache
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not create directory %s&quot;
comma
id|rr_cache
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setup_rerere
r_int
id|setup_rerere
c_func
(paren
r_struct
id|string_list
op_star
id|merge_rr
comma
r_int
id|flags
)paren
(brace
r_int
id|fd
suffix:semicolon
id|git_config
c_func
(paren
id|git_rerere_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_rerere_enabled
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|RERERE_AUTOUPDATE
op_or
id|RERERE_NOAUTOUPDATE
)paren
)paren
id|rerere_autoupdate
op_assign
op_logical_neg
op_logical_neg
(paren
id|flags
op_amp
id|RERERE_AUTOUPDATE
)paren
suffix:semicolon
id|merge_rr_path
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;MERGE_RR&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|write_lock
comma
id|merge_rr_path
comma
id|LOCK_DIE_ON_ERROR
)paren
suffix:semicolon
id|read_rr
c_func
(paren
id|merge_rr
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|rerere
r_int
id|rerere
c_func
(paren
r_int
id|flags
)paren
(brace
r_struct
id|string_list
id|merge_rr
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|setup_rerere
c_func
(paren
op_amp
id|merge_rr
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|do_plain_rerere
c_func
(paren
op_amp
id|merge_rr
comma
id|fd
)paren
suffix:semicolon
)brace
DECL|function|rerere_forget_one_path
r_static
r_int
id|rerere_forget_one_path
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|string_list
op_star
id|rr
)paren
(brace
r_const
r_char
op_star
id|filename
suffix:semicolon
r_char
op_star
id|hex
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|handle_cache
c_func
(paren
id|path
comma
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not parse conflict hunks in &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|hex
op_assign
id|xstrdup
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|filename
op_assign
id|rerere_path
c_func
(paren
id|hex
comma
l_string|&quot;postimage&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|filename
)paren
)paren
r_return
(paren
id|errno
op_eq
id|ENOENT
ques
c_cond
id|error
c_func
(paren
l_string|&quot;no remembered resolution for %s&quot;
comma
id|path
)paren
suffix:colon
id|error
c_func
(paren
l_string|&quot;cannot unlink %s: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
)paren
suffix:semicolon
id|handle_cache
c_func
(paren
id|path
comma
id|sha1
comma
id|rerere_path
c_func
(paren
id|hex
comma
l_string|&quot;preimage&quot;
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Updated preimage for &squot;%s&squot;&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
id|string_list_insert
c_func
(paren
id|rr
comma
id|path
)paren
op_member_access_from_pointer
id|util
op_assign
id|hex
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Forgot resolution for %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rerere_forget
r_int
id|rerere_forget
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_int
id|i
comma
id|fd
suffix:semicolon
r_struct
id|string_list
id|conflict
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|string_list
id|merge_rr
op_assign
id|STRING_LIST_INIT_DUP
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
r_return
id|error
c_func
(paren
l_string|&quot;Could not read index&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|setup_rerere
c_func
(paren
op_amp
id|merge_rr
comma
id|RERERE_NOAUTOUPDATE
)paren
suffix:semicolon
id|unmerge_cache
c_func
(paren
id|pathspec
)paren
suffix:semicolon
id|find_conflict
c_func
(paren
op_amp
id|conflict
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
id|conflict.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|string_list_item
op_star
id|it
op_assign
op_amp
id|conflict.items
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match_pathspec
c_func
(paren
id|pathspec
comma
id|it-&gt;string
comma
id|strlen
c_func
(paren
id|it-&gt;string
)paren
comma
l_int|0
comma
l_int|NULL
)paren
)paren
r_continue
suffix:semicolon
id|rerere_forget_one_path
c_func
(paren
id|it-&gt;string
comma
op_amp
id|merge_rr
)paren
suffix:semicolon
)brace
r_return
id|write_rr
c_func
(paren
op_amp
id|merge_rr
comma
id|fd
)paren
suffix:semicolon
)brace
eof
