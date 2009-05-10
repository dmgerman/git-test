multiline_comment|/*&n; * GIT - the stupid content tracker&n; *&n; * Copyright (c) Junio C Hamano, 2006, 2009&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|struct|treeent
r_static
r_struct
id|treeent
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
DECL|variable|entries
)brace
op_star
op_star
id|entries
suffix:semicolon
DECL|variable|alloc
DECL|variable|used
r_static
r_int
id|alloc
comma
id|used
suffix:semicolon
DECL|function|append_to_tree
r_static
r_void
id|append_to_tree
c_func
(paren
r_int
id|mode
comma
r_int
r_char
op_star
id|sha1
comma
r_char
op_star
id|path
)paren
(brace
r_struct
id|treeent
op_star
id|ent
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;path %s contains slash&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alloc
op_le
id|used
)paren
(brace
id|alloc
op_assign
id|alloc_nr
c_func
(paren
id|used
)paren
suffix:semicolon
id|entries
op_assign
id|xrealloc
c_func
(paren
id|entries
comma
r_sizeof
(paren
op_star
id|entries
)paren
op_star
id|alloc
)paren
suffix:semicolon
)brace
id|ent
op_assign
id|entries
(braket
id|used
op_increment
)braket
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
op_star
id|entries
)paren
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|ent-&gt;mode
op_assign
id|mode
suffix:semicolon
id|ent-&gt;len
op_assign
id|len
suffix:semicolon
id|hashcpy
c_func
(paren
id|ent-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|path
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ent_compare
r_static
r_int
id|ent_compare
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|treeent
op_star
id|a
op_assign
op_star
(paren
r_struct
id|treeent
op_star
op_star
)paren
id|a_
suffix:semicolon
r_struct
id|treeent
op_star
id|b
op_assign
op_star
(paren
r_struct
id|treeent
op_star
op_star
)paren
id|b_
suffix:semicolon
r_return
id|base_name_compare
c_func
(paren
id|a-&gt;name
comma
id|a-&gt;len
comma
id|a-&gt;mode
comma
id|b-&gt;name
comma
id|b-&gt;len
comma
id|b-&gt;mode
)paren
suffix:semicolon
)brace
DECL|function|write_tree
r_static
r_void
id|write_tree
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|i
suffix:semicolon
id|qsort
c_func
(paren
id|entries
comma
id|used
comma
r_sizeof
(paren
op_star
id|entries
)paren
comma
id|ent_compare
)paren
suffix:semicolon
r_for
c_loop
(paren
id|size
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|used
suffix:semicolon
id|i
op_increment
)paren
id|size
op_add_assign
l_int|32
op_plus
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|len
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
id|size
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
id|used
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|treeent
op_star
id|ent
op_assign
id|entries
(braket
id|i
)braket
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%o %s%c&quot;
comma
id|ent-&gt;mode
comma
id|ent-&gt;name
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|buf
comma
id|ent-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
id|write_sha1_file
c_func
(paren
id|buf.buf
comma
id|buf.len
comma
id|tree_type
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|variable|mktree_usage
r_static
r_const
r_char
op_star
id|mktree_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git mktree [-z]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|mktree_line
r_static
r_void
id|mktree_line
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|line_termination
comma
r_int
id|allow_missing
)paren
(brace
r_char
op_star
id|ptr
comma
op_star
id|ntr
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|ptr
op_assign
id|buf
suffix:semicolon
multiline_comment|/*&n;&t; * Read non-recursive ls-tree output format:&n;&t; *     mode SP type SP sha1 TAB name&n;&t; */
id|mode
op_assign
id|strtoul
c_func
(paren
id|ptr
comma
op_amp
id|ntr
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
id|ntr
op_logical_or
op_logical_neg
id|ntr
op_logical_or
op_star
id|ntr
op_ne
l_char|&squot; &squot;
)paren
id|die
c_func
(paren
l_string|&quot;input format error: %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|ptr
op_assign
id|ntr
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* type */
id|ntr
op_assign
id|strchr
c_func
(paren
id|ptr
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ntr
op_logical_or
id|buf
op_plus
id|len
op_le
id|ntr
op_plus
l_int|40
op_logical_or
id|ntr
(braket
l_int|41
)braket
op_ne
l_char|&squot;&bslash;t&squot;
op_logical_or
id|get_sha1_hex
c_func
(paren
id|ntr
op_plus
l_int|1
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;input format error: %s&quot;
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* It is perfectly normal if we do not have a commit from a submodule */
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|mode
)paren
)paren
id|allow_missing
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allow_missing
)paren
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|type
op_assign
id|object_type
c_func
(paren
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;object %s unavailable&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
op_star
id|ntr
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* now at the beginning of SHA1 */
r_if
c_cond
(paren
id|type
op_ne
id|type_from_string
c_func
(paren
id|ptr
)paren
)paren
id|die
c_func
(paren
l_string|&quot;object type %s mismatch (%s)&quot;
comma
id|ptr
comma
r_typename
(paren
id|type
)paren
)paren
suffix:semicolon
id|path
op_assign
id|ntr
op_plus
l_int|41
suffix:semicolon
multiline_comment|/* at the beginning of name */
r_if
c_cond
(paren
id|line_termination
op_logical_and
id|path
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
r_struct
id|strbuf
id|p_uq
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|unquote_c_style
c_func
(paren
op_amp
id|p_uq
comma
id|path
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;invalid quoting&quot;
)paren
suffix:semicolon
id|path
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|p_uq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|append_to_tree
c_func
(paren
id|mode
comma
id|sha1
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|cmd_mktree
r_int
id|cmd_mktree
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_int
id|allow_missing
op_assign
l_int|0
suffix:semicolon
r_const
r_struct
id|option
id|option
(braket
)braket
op_assign
(brace
id|OPT_SET_INT
c_func
(paren
l_char|&squot;z&squot;
comma
l_int|NULL
comma
op_amp
id|line_termination
comma
l_string|&quot;input is NUL terminated&quot;
comma
l_char|&squot;&bslash;0&squot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;missing&quot;
comma
op_amp
id|allow_missing
comma
l_string|&quot;allow missing objects&quot;
comma
l_int|1
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|ac
op_assign
id|parse_options
c_func
(paren
id|ac
comma
id|av
comma
id|option
comma
id|mktree_usage
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
id|line_termination
)paren
op_ne
id|EOF
)paren
id|mktree_line
c_func
(paren
id|sb.buf
comma
id|sb.len
comma
id|line_termination
comma
id|allow_missing
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|write_tree
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|puts
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
