macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;rerere.h&quot;
macro_line|#include &quot;xdiff/xdiff.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;pathspec.h&quot;
DECL|variable|rerere_usage
r_static
r_const
r_char
op_star
r_const
id|rerere_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git rerere [clear | forget &lt;path&gt;... | status | remaining | diff | gc]&quot;
)paren
comma
l_int|NULL
comma
)brace
suffix:semicolon
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
l_int|0
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
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_int
id|i
comma
id|autoupdate
op_assign
l_int|1
comma
id|flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;rerere-autoupdate&quot;
comma
op_amp
id|autoupdate
comma
id|N_
c_func
(paren
l_string|&quot;register clean resolutions in index&quot;
)paren
comma
l_int|1
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
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
id|prefix
comma
id|options
comma
id|rerere_usage
comma
l_int|0
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_xmerge_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|autoupdate
op_eq
l_int|1
)paren
id|flags
op_assign
id|RERERE_AUTOUPDATE
suffix:semicolon
r_if
c_cond
(paren
id|autoupdate
op_eq
l_int|0
)paren
id|flags
op_assign
id|RERERE_NOAUTOUPDATE
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
r_return
id|rerere
c_func
(paren
id|flags
)paren
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
l_int|0
)braket
comma
l_string|&quot;forget&quot;
)paren
)paren
(brace
r_struct
id|pathspec
id|pathspec
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
id|warning
c_func
(paren
l_string|&quot;&squot;git rerere forget&squot; without paths is deprecated&quot;
)paren
suffix:semicolon
id|parse_pathspec
c_func
(paren
op_amp
id|pathspec
comma
l_int|0
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
r_return
id|rerere_forget
c_func
(paren
op_amp
id|pathspec
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
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;clear&quot;
)paren
)paren
(brace
id|rerere_clear
c_func
(paren
op_amp
id|merge_rr
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
l_int|0
)braket
comma
l_string|&quot;gc&quot;
)paren
)paren
id|rerere_gc
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
l_int|0
)braket
comma
l_string|&quot;status&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|setup_rerere
c_func
(paren
op_amp
id|merge_rr
comma
id|flags
op_or
id|RERERE_READONLY
)paren
OL
l_int|0
)paren
r_return
l_int|0
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
l_int|0
)braket
comma
l_string|&quot;remaining&quot;
)paren
)paren
(brace
id|rerere_remaining
c_func
(paren
op_amp
id|merge_rr
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
id|merge_rr.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|merge_rr.items
(braket
id|i
)braket
dot
id|util
op_ne
id|RERERE_RESOLVED
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
multiline_comment|/* prepare for later call to&n;&t;&t;&t;&t; * string_list_clear() */
id|merge_rr.items
(braket
id|i
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
)brace
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
l_int|0
)braket
comma
l_string|&quot;diff&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|setup_rerere
c_func
(paren
op_amp
id|merge_rr
comma
id|flags
op_or
id|RERERE_READONLY
)paren
OL
l_int|0
)paren
r_return
l_int|0
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
r_struct
id|rerere_id
op_star
id|id
op_assign
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
id|id
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
)brace
r_else
id|usage_with_options
c_func
(paren
id|rerere_usage
comma
id|options
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
