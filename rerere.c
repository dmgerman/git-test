macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;rerere.h&quot;
macro_line|#include &quot;xdiff/xdiff.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
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
DECL|function|rr_path
r_static
r_const
r_char
op_star
id|rr_path
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
id|file
)paren
(brace
r_return
id|git_path
c_func
(paren
l_string|&quot;rr-cache/%s/%s&quot;
comma
id|name
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|has_resolution
r_static
r_int
id|has_resolution
c_func
(paren
r_const
r_char
op_star
id|name
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
id|rr_path
c_func
(paren
id|name
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
id|buf
comma
id|rr
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
id|write_in_full
c_func
(paren
id|out_fd
comma
l_string|&quot;&bslash;t&quot;
comma
l_int|1
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
id|git_SHA_CTX
id|ctx
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
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
comma
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
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|path
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|FILE
op_star
id|out
op_assign
l_int|NULL
suffix:semicolon
r_int
id|wrerror
op_assign
l_int|0
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
id|out
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
id|out
)paren
(brace
id|fclose
c_func
(paren
id|f
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
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|f
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;&lt;&lt;&lt;&lt;&lt;&lt;&lt; &quot;
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;|||||||&quot;
)paren
op_logical_and
id|isspace
c_func
(paren
id|buf
(braket
l_int|7
)braket
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;=======&quot;
)paren
op_logical_and
id|isspace
c_func
(paren
id|buf
(braket
l_int|7
)braket
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|buf
comma
l_string|&quot;&gt;&gt;&gt;&gt;&gt;&gt;&gt; &quot;
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
r_if
c_cond
(paren
id|out
)paren
(brace
id|ferr_puts
c_func
(paren
l_string|&quot;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&bslash;n&quot;
comma
id|out
comma
op_amp
id|wrerror
)paren
suffix:semicolon
id|ferr_write
c_func
(paren
id|one.buf
comma
id|one.len
comma
id|out
comma
op_amp
id|wrerror
)paren
suffix:semicolon
id|ferr_puts
c_func
(paren
l_string|&quot;=======&bslash;n&quot;
comma
id|out
comma
op_amp
id|wrerror
)paren
suffix:semicolon
id|ferr_write
c_func
(paren
id|two.buf
comma
id|two.len
comma
id|out
comma
op_amp
id|wrerror
)paren
suffix:semicolon
id|ferr_puts
c_func
(paren
l_string|&quot;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&bslash;n&quot;
comma
id|out
comma
op_amp
id|wrerror
)paren
suffix:semicolon
)brace
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
id|buf
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
id|buf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|out
)paren
id|ferr_puts
c_func
(paren
id|buf
comma
id|out
comma
op_amp
id|wrerror
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
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wrerror
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
id|wrerror
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out
op_logical_and
id|fclose
c_func
(paren
id|out
)paren
)paren
id|wrerror
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
(brace
r_if
c_cond
(paren
id|output
)paren
id|unlink
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
id|wrerror
)paren
r_return
l_int|1
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
(paren
r_const
r_char
op_star
)paren
id|e2-&gt;name
comma
id|conflict
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
comma
id|base
comma
id|other
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
id|xpparam_t
id|xpp
op_assign
(brace
id|XDF_NEED_MINIMAL
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
id|rr_path
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
id|rr_path
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
id|rr_path
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
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
id|xdl_merge
c_func
(paren
op_amp
id|base
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
op_amp
id|xpp
comma
id|XDL_MERGE_ZEALOUS
comma
op_amp
id|result
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
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_struct
id|string_list
id|update
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
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
id|path
comma
id|rr
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
suffix:semicolon
id|handle_file
c_func
(paren
id|path
comma
l_int|NULL
comma
id|rr_path
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
id|has_resolution
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
id|path
comma
op_amp
id|update
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
id|rr_path
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
r_void
)paren
(brace
r_struct
id|string_list
id|merge_rr
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
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
eof
