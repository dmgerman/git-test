macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;xdiff/xdiff.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &lt;time.h&gt;
DECL|variable|git_rerere_usage
r_static
r_const
r_char
id|git_rerere_usage
(braket
)braket
op_assign
l_string|&quot;git-rerere [clear | status | diff | gc]&quot;
suffix:semicolon
multiline_comment|/* these values are days */
DECL|variable|cutoff_noresolve
r_static
r_int
id|cutoff_noresolve
op_assign
l_int|15
suffix:semicolon
DECL|variable|cutoff_resolve
r_static
r_int
id|cutoff_resolve
op_assign
l_int|60
suffix:semicolon
multiline_comment|/* if rerere_enabled == -1, fall back to detection of .git/rr-cache */
DECL|variable|rerere_enabled
r_static
r_int
id|rerere_enabled
op_assign
l_int|1
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
DECL|function|read_rr
r_static
r_void
id|read_rr
c_func
(paren
r_struct
id|path_list
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
id|path_list_insert
c_func
(paren
id|buf
comma
id|rr
)paren
op_member_access_from_pointer
id|util
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
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
id|path_list
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
op_assign
id|rr-&gt;items
(braket
id|i
)braket
dot
id|path
suffix:semicolon
r_int
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
id|close
c_func
(paren
id|out_fd
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
id|commit_lock_file
c_func
(paren
op_amp
id|write_lock
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
id|SHA_CTX
id|ctx
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|hunk
op_assign
l_int|0
comma
id|hunk_no
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
id|one
comma
id|two
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
id|SHA1_Init
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|one
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|two
comma
l_int|0
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
id|hunk
op_assign
l_int|1
suffix:semicolon
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
)paren
id|hunk
op_assign
l_int|2
suffix:semicolon
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
r_int
id|cmp
op_assign
id|strbuf_cmp
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
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
)brace
r_if
c_cond
(paren
id|out
)paren
(brace
id|fputs
c_func
(paren
l_string|&quot;&lt;&lt;&lt;&lt;&lt;&lt;&lt;&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|one.buf
comma
id|one.len
comma
l_int|1
comma
id|out
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;=======&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|two.buf
comma
id|two.len
comma
l_int|1
comma
id|out
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&bslash;n&quot;
comma
id|out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sha1
)paren
(brace
id|SHA1_Update
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
id|SHA1_Update
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
l_int|1
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
l_int|2
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
id|fputs
c_func
(paren
id|buf
comma
id|out
)paren
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
id|out
)paren
id|fclose
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sha1
)paren
id|SHA1_Final
c_func
(paren
id|sha1
comma
op_amp
id|ctx
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
id|path_list
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
id|ntohl
c_func
(paren
id|e2-&gt;ce_mode
)paren
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|ntohl
c_func
(paren
id|e3-&gt;ce_mode
)paren
)paren
)paren
(brace
id|path_list_insert
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
l_string|&quot;Could not write to %s&quot;
comma
id|path
)paren
suffix:semicolon
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
suffix:semicolon
id|fclose
c_func
(paren
id|f
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
DECL|function|unlink_rr_item
r_static
r_void
id|unlink_rr_item
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|unlink
c_func
(paren
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;thisimage&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;preimage&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
)paren
suffix:semicolon
id|rmdir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;rr-cache/%s&quot;
comma
id|name
)paren
)paren
suffix:semicolon
)brace
DECL|function|garbage_collect
r_static
r_void
id|garbage_collect
c_func
(paren
r_struct
id|path_list
op_star
id|rr
)paren
(brace
r_struct
id|path_list
id|to_remove
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
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|e
suffix:semicolon
r_int
id|len
comma
id|i
comma
id|cutoff
suffix:semicolon
id|time_t
id|now
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
comma
id|then
suffix:semicolon
id|strlcpy
c_func
(paren
id|buf
comma
id|git_path
c_func
(paren
l_string|&quot;rr-cache&quot;
)paren
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|buf
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
op_plus
id|len
op_increment
comma
l_string|&quot;/&quot;
)paren
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
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|e-&gt;d_name
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
id|name
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
(paren
id|name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
op_logical_and
id|name
(braket
l_int|2
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
)paren
r_continue
suffix:semicolon
id|i
op_assign
id|snprintf
c_func
(paren
id|buf
op_plus
id|len
comma
r_sizeof
(paren
id|buf
)paren
id|len
comma
l_string|&quot;%s&quot;
comma
id|name
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|buf
op_plus
id|len
op_plus
id|i
comma
l_string|&quot;/preimage&quot;
comma
r_sizeof
(paren
id|buf
)paren
id|len
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|buf
comma
op_amp
id|st
)paren
)paren
r_continue
suffix:semicolon
id|then
op_assign
id|st.st_mtime
suffix:semicolon
id|strlcpy
c_func
(paren
id|buf
op_plus
id|len
op_plus
id|i
comma
l_string|&quot;/postimage&quot;
comma
r_sizeof
(paren
id|buf
)paren
id|len
id|i
)paren
suffix:semicolon
id|cutoff
op_assign
id|stat
c_func
(paren
id|buf
comma
op_amp
id|st
)paren
ques
c_cond
id|cutoff_noresolve
suffix:colon
id|cutoff_resolve
suffix:semicolon
r_if
c_cond
(paren
id|then
OL
id|now
id|cutoff
op_star
l_int|86400
)paren
(brace
id|buf
(braket
id|len
op_plus
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|path_list_insert
c_func
(paren
id|xstrdup
c_func
(paren
id|name
)paren
comma
op_amp
id|to_remove
)paren
suffix:semicolon
)brace
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
id|to_remove.nr
suffix:semicolon
id|i
op_increment
)paren
id|unlink_rr_item
c_func
(paren
id|to_remove.items
(braket
id|i
)braket
dot
id|path
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|to_remove
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|outf
r_static
r_int
id|outf
c_func
(paren
r_void
op_star
id|dummy
comma
id|mmbuffer_t
op_star
id|ptr
comma
r_int
id|nbuf
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
id|nbuf
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
l_int|1
comma
id|ptr
(braket
id|i
)braket
dot
id|ptr
comma
id|ptr
(braket
id|i
)braket
dot
id|size
)paren
op_ne
id|ptr
(braket
id|i
)braket
dot
id|size
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_two
r_static
r_int
id|diff_two
c_func
(paren
r_const
r_char
op_star
id|file1
comma
r_const
r_char
op_star
id|label1
comma
r_const
r_char
op_star
id|file2
comma
r_const
r_char
op_star
id|label2
)paren
(brace
id|xpparam_t
id|xpp
suffix:semicolon
id|xdemitconf_t
id|xecfg
suffix:semicolon
id|xdemitcb_t
id|ecb
suffix:semicolon
id|mmfile_t
id|minus
comma
id|plus
suffix:semicolon
r_if
c_cond
(paren
id|read_mmfile
c_func
(paren
op_amp
id|minus
comma
id|file1
)paren
op_logical_or
id|read_mmfile
c_func
(paren
op_amp
id|plus
comma
id|file2
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;--- a/%s&bslash;n+++ b/%s&bslash;n&quot;
comma
id|label1
comma
id|label2
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|xpp.flags
op_assign
id|XDF_NEED_MINIMAL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|xecfg
comma
l_int|0
comma
r_sizeof
(paren
id|xecfg
)paren
)paren
suffix:semicolon
id|xecfg.ctxlen
op_assign
l_int|3
suffix:semicolon
id|ecb.outf
op_assign
id|outf
suffix:semicolon
id|xdl_diff
c_func
(paren
op_amp
id|minus
comma
op_amp
id|plus
comma
op_amp
id|xpp
comma
op_amp
id|xecfg
comma
op_amp
id|ecb
)paren
suffix:semicolon
id|free
c_func
(paren
id|minus.ptr
)paren
suffix:semicolon
id|free
c_func
(paren
id|plus.ptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_file
r_static
r_int
id|copy_file
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_const
r_char
op_star
id|dest
)paren
(brace
id|FILE
op_star
id|in
comma
op_star
id|out
suffix:semicolon
r_char
id|buffer
(braket
l_int|32768
)braket
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|in
op_assign
id|fopen
c_func
(paren
id|src
comma
l_string|&quot;r&quot;
)paren
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open %s&quot;
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|out
op_assign
id|fopen
c_func
(paren
id|dest
comma
l_string|&quot;w&quot;
)paren
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open %s&quot;
comma
id|dest
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|count
op_assign
id|fread
c_func
(paren
id|buffer
comma
l_int|1
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|in
)paren
)paren
)paren
id|fwrite
c_func
(paren
id|buffer
comma
l_int|1
comma
id|count
comma
id|out
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|in
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_plain_rerere
r_static
r_int
id|do_plain_rerere
c_func
(paren
r_struct
id|path_list
op_star
id|rr
comma
r_int
id|fd
)paren
(brace
r_struct
id|path_list
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
id|path
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path_list_has_path
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
id|path_list_insert
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
r_struct
id|stat
id|st
suffix:semicolon
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
id|path
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
op_logical_neg
id|stat
c_func
(paren
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;preimage&quot;
)paren
comma
op_amp
id|st
)paren
op_logical_and
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Resolved &squot;%s&squot; using &quot;
l_string|&quot;previous resolution.&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|tail_optimization
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
id|path
comma
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;postimage&quot;
)paren
)paren
suffix:semicolon
id|tail_optimization
suffix:colon
r_if
c_cond
(paren
id|i
OL
id|rr-&gt;nr
l_int|1
)paren
id|memmove
c_func
(paren
id|rr-&gt;items
op_plus
id|i
comma
id|rr-&gt;items
op_plus
id|i
op_plus
l_int|1
comma
r_sizeof
(paren
id|rr-&gt;items
(braket
l_int|0
)braket
)paren
op_star
(paren
id|rr-&gt;nr
id|i
l_int|1
)paren
)paren
suffix:semicolon
id|rr-&gt;nr
op_decrement
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
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
l_string|&quot;gc.rerereresolved&quot;
)paren
)paren
id|cutoff_resolve
op_assign
id|git_config_int
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
l_string|&quot;gc.rerereunresolved&quot;
)paren
)paren
id|cutoff_noresolve
op_assign
id|git_config_int
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
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
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
r_struct
id|stat
id|st
suffix:semicolon
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
op_logical_neg
id|stat
c_func
(paren
id|rr_cache
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISDIR
c_func
(paren
id|st.st_mode
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
DECL|function|cmd_rerere
r_int
id|cmd_rerere
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
id|path_list
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
id|i
comma
id|fd
op_assign
l_int|1
suffix:semicolon
id|git_config
c_func
(paren
id|git_rerere_config
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
l_int|0
suffix:semicolon
id|merge_rr_path
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;rr-cache/MERGE_RR&quot;
)paren
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
l_int|1
)paren
suffix:semicolon
id|read_rr
c_func
(paren
op_amp
id|merge_rr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
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
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;clear&quot;
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
id|merge_rr.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|stat
id|st
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
id|merge_rr.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;rr-cache/%s&quot;
comma
id|name
)paren
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
op_logical_and
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
)paren
id|unlink_rr_item
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
id|unlink
c_func
(paren
id|merge_rr_path
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
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;gc&quot;
)paren
)paren
id|garbage_collect
c_func
(paren
op_amp
id|merge_rr
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
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;status&quot;
)paren
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|merge_rr.nr
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|merge_rr.items
(braket
id|i
)braket
dot
id|path
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
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;diff&quot;
)paren
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|merge_rr.nr
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
id|merge_rr.items
(braket
id|i
)braket
dot
id|path
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
id|merge_rr.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
id|diff_two
c_func
(paren
id|rr_path
c_func
(paren
id|name
comma
l_string|&quot;preimage&quot;
)paren
comma
id|path
comma
id|path
comma
id|path
)paren
suffix:semicolon
)brace
r_else
id|usage
c_func
(paren
id|git_rerere_usage
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|merge_rr
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
