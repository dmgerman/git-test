macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;rerere.h&quot;
macro_line|#include &quot;xdiff/xdiff.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
DECL|variable|git_rerere_usage
r_static
r_const
r_char
id|git_rerere_usage
(braket
)braket
op_assign
l_string|&quot;git rerere [clear | status | diff | gc]&quot;
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
DECL|function|rerere_created_at
r_static
id|time_t
id|rerere_created_at
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
id|stat
c_func
(paren
id|rerere_path
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
ques
c_cond
(paren
id|time_t
)paren
l_int|0
suffix:colon
id|st.st_mtime
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
id|rerere_path
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
id|rerere_path
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
id|rerere_path
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
DECL|function|git_rerere_gc_config
r_static
r_int
id|git_rerere_gc_config
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
DECL|function|garbage_collect
r_static
r_void
id|garbage_collect
c_func
(paren
r_struct
id|string_list
op_star
id|rr
)paren
(brace
r_struct
id|string_list
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
id|git_config
c_func
(paren
id|git_rerere_gc_config
comma
l_int|NULL
)paren
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;rr-cache&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to open rr-cache directory&quot;
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
id|then
op_assign
id|rerere_created_at
c_func
(paren
id|e-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|then
)paren
r_continue
suffix:semicolon
id|cutoff
op_assign
(paren
id|has_rerere_resolution
c_func
(paren
id|e-&gt;d_name
)paren
ques
c_cond
id|cutoff_resolve
suffix:colon
id|cutoff_noresolve
)paren
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
id|string_list_append
c_func
(paren
id|e-&gt;d_name
comma
op_amp
id|to_remove
)paren
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
id|string
)paren
suffix:semicolon
id|string_list_clear
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
id|memset
c_func
(paren
op_amp
id|xpp
comma
l_int|0
comma
r_sizeof
(paren
id|xpp
)paren
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
id|xdi_diff
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
id|i
comma
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
r_return
id|rerere
c_func
(paren
)paren
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
id|has_rerere_resolution
c_func
(paren
id|name
)paren
)paren
id|unlink_rr_item
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
id|unlink_or_warn
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;rr-cache/MERGE_RR&quot;
)paren
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
id|string
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
id|rerere_path
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
id|string_list_clear
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
