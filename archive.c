macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;attr.h&quot;
DECL|function|format_subst
r_static
r_void
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
id|src
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
r_char
op_star
id|to_free
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|strbuf
id|fmt
suffix:semicolon
r_if
c_cond
(paren
id|src
op_eq
id|buf-&gt;buf
)paren
id|to_free
op_assign
id|strbuf_detach
c_func
(paren
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|fmt
comma
l_int|0
)paren
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
id|b
op_assign
id|memmem
c_func
(paren
id|src
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
id|src
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
id|strbuf_reset
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|fmt
comma
id|b
op_plus
l_int|8
comma
id|c
id|b
l_int|8
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|b
id|src
)paren
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
id|fmt.buf
comma
id|buf
)paren
suffix:semicolon
id|len
op_sub_assign
id|c
op_plus
l_int|1
id|src
suffix:semicolon
id|src
op_assign
id|c
op_plus
l_int|1
suffix:semicolon
)brace
id|strbuf_add
c_func
(paren
id|buf
comma
id|src
comma
id|len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|fmt
)paren
suffix:semicolon
id|free
c_func
(paren
id|to_free
)paren
suffix:semicolon
)brace
DECL|function|convert_to_archive
r_static
r_int
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
id|len
comma
r_struct
id|strbuf
op_star
id|buf
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
l_int|0
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
l_int|0
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
l_int|0
suffix:semicolon
id|format_subst
c_func
(paren
id|commit
comma
id|src
comma
id|len
comma
id|buf
)paren
suffix:semicolon
r_return
l_int|1
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
id|sizep
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
id|sizep
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
r_struct
id|strbuf
id|buf
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_attach
c_func
(paren
op_amp
id|buf
comma
id|buffer
comma
op_star
id|sizep
comma
op_star
id|sizep
op_plus
l_int|1
)paren
suffix:semicolon
id|convert_to_working_tree
c_func
(paren
id|path
comma
id|buf.buf
comma
id|buf.len
comma
op_amp
id|buf
)paren
suffix:semicolon
id|convert_to_archive
c_func
(paren
id|path
comma
id|buf.buf
comma
id|buf.len
comma
op_amp
id|buf
comma
id|commit
)paren
suffix:semicolon
id|buffer
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
op_amp
id|size
)paren
suffix:semicolon
op_star
id|sizep
op_assign
id|size
suffix:semicolon
)brace
r_return
id|buffer
suffix:semicolon
)brace
eof
