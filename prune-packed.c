macro_line|#include &quot;cache.h&quot;
DECL|variable|prune_packed_usage
r_static
r_const
r_char
id|prune_packed_usage
(braket
)braket
op_assign
l_string|&quot;git-prune-packed (no arguments)&quot;
suffix:semicolon
DECL|function|prune_dir
r_static
r_void
id|prune_dir
c_func
(paren
r_int
id|i
comma
id|DIR
op_star
id|dir
comma
r_char
op_star
id|pathname
comma
r_int
id|len
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_char
id|hex
(braket
l_int|40
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|hex
comma
l_string|&quot;%02x&quot;
comma
id|i
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
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
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
op_ne
l_int|38
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|hex
op_plus
l_int|2
comma
id|de-&gt;d_name
comma
l_int|38
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_pack
c_func
(paren
id|sha1
)paren
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|pathname
op_plus
id|len
comma
id|de-&gt;d_name
comma
l_int|38
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|pathname
)paren
OL
l_int|0
)paren
id|error
c_func
(paren
l_string|&quot;unable to unlink %s&quot;
comma
id|pathname
)paren
suffix:semicolon
)brace
)brace
DECL|function|prune_packed_objects
r_static
r_void
id|prune_packed_objects
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_char
id|pathname
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|dir
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|PATH_MAX
l_int|42
)paren
id|die
c_func
(paren
l_string|&quot;impossible object directory&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pathname
comma
id|dir
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|pathname
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|pathname
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DIR
op_star
id|d
suffix:semicolon
id|sprintf
c_func
(paren
id|pathname
op_plus
id|len
comma
l_string|&quot;%02x/&quot;
comma
id|i
)paren
suffix:semicolon
id|d
op_assign
id|opendir
c_func
(paren
id|pathname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
id|die
c_func
(paren
l_string|&quot;unable to open %s&quot;
comma
id|pathname
)paren
suffix:semicolon
id|prune_dir
c_func
(paren
id|i
comma
id|d
comma
id|pathname
comma
id|len
op_plus
l_int|3
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
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
multiline_comment|/* Handle flags here .. */
id|usage
c_func
(paren
id|prune_packed_usage
)paren
suffix:semicolon
)brace
multiline_comment|/* Handle arguments here .. */
id|usage
c_func
(paren
id|prune_packed_usage
)paren
suffix:semicolon
)brace
id|prune_packed_objects
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
