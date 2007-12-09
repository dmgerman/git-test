macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|variable|ls_remote_usage
r_static
r_const
r_char
id|ls_remote_usage
(braket
)braket
op_assign
l_string|&quot;git-ls-remote [--upload-pack=&lt;git-upload-pack&gt;] [&lt;host&gt;:]&lt;directory&gt;&quot;
suffix:semicolon
multiline_comment|/*&n; * Is there one among the list of patterns that match the tail part&n; * of the path?&n; */
DECL|function|tail_match
r_static
r_int
id|tail_match
c_func
(paren
r_const
r_char
op_star
op_star
id|pattern
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
id|p
suffix:semicolon
r_char
id|pathbuf
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pattern
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* no restriction */
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|pathbuf
comma
r_sizeof
(paren
id|pathbuf
)paren
comma
l_string|&quot;/%s&quot;
comma
id|path
)paren
OG
r_sizeof
(paren
id|pathbuf
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;insanely long ref %.*s...&quot;
comma
l_int|20
comma
id|path
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
op_star
(paren
id|pattern
op_increment
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|p
comma
id|pathbuf
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_ls_remote
r_int
id|cmd_ls_remote
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
id|i
suffix:semicolon
r_const
r_char
op_star
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_int
id|nongit
op_assign
l_int|0
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|uploadpack
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
op_star
id|pattern
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|ref
suffix:semicolon
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
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
op_star
id|arg
op_eq
l_char|&squot;-&squot;
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
l_string|&quot;--upload-pack=&quot;
)paren
)paren
(brace
id|uploadpack
op_assign
id|arg
op_plus
l_int|14
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
l_string|&quot;--exec=&quot;
)paren
)paren
(brace
id|uploadpack
op_assign
id|arg
op_plus
l_int|7
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
l_string|&quot;--tags&quot;
comma
id|arg
)paren
)paren
(brace
id|flags
op_or_assign
id|REF_TAGS
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
l_string|&quot;--heads&quot;
comma
id|arg
)paren
)paren
(brace
id|flags
op_or_assign
id|REF_HEADS
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
l_string|&quot;--refs&quot;
comma
id|arg
)paren
)paren
(brace
id|flags
op_or_assign
id|REF_NORMAL
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|ls_remote_usage
)paren
suffix:semicolon
)brace
id|dest
op_assign
id|arg
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
id|usage
c_func
(paren
id|ls_remote_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
id|i
)braket
)paren
(brace
r_int
id|j
suffix:semicolon
id|pattern
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_const
r_char
op_star
)paren
comma
id|argc
id|i
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OL
id|argc
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|argv
(braket
id|j
)braket
)paren
suffix:semicolon
r_char
op_star
id|p
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|3
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;*/%s&quot;
comma
id|argv
(braket
id|j
)braket
)paren
suffix:semicolon
id|pattern
(braket
id|j
id|i
)braket
op_assign
id|p
suffix:semicolon
)brace
)brace
id|remote
op_assign
id|nongit
ques
c_cond
l_int|NULL
suffix:colon
id|remote_get
c_func
(paren
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
op_logical_and
op_logical_neg
id|remote-&gt;url_nr
)paren
id|die
c_func
(paren
l_string|&quot;remote %s has no configured URL&quot;
comma
id|dest
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|remote
ques
c_cond
id|remote-&gt;url
(braket
l_int|0
)braket
suffix:colon
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uploadpack
op_ne
l_int|NULL
)paren
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_UPLOADPACK
comma
id|uploadpack
)paren
suffix:semicolon
id|ref
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|check_ref_type
c_func
(paren
id|ref
comma
id|flags
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tail_match
c_func
(paren
id|pattern
comma
id|ref-&gt;name
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&t;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
comma
id|ref-&gt;name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
