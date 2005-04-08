multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|function|check_valid_sha1
r_static
r_int
id|check_valid_sha1
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|filename
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* If we were anal, we&squot;d check that the sha1 of the contents actually matches */
id|ret
op_assign
id|access
c_func
(paren
id|filename
comma
id|R_OK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|perror
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|prepend_integer
r_static
r_int
id|prepend_integer
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|val
comma
r_int
id|i
)paren
(brace
id|buffer
(braket
op_decrement
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_do
(brace
id|buffer
(braket
op_decrement
id|i
)braket
op_assign
l_char|&squot;0&squot;
op_plus
(paren
id|val
op_mod
l_int|10
)paren
suffix:semicolon
id|val
op_div_assign
l_int|10
suffix:semicolon
)brace
r_while
c_loop
(paren
id|val
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|macro|ORIG_OFFSET
mdefine_line|#define ORIG_OFFSET (40)&t;/* Enough space to add the header of &quot;tree &lt;size&gt;&bslash;0&quot; */
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
r_int
id|size
comma
id|offset
suffix:semicolon
r_int
id|i
comma
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|entries
op_le
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No file-cache to create a tree of&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Guess at an initial size */
id|size
op_assign
id|entries
op_star
l_int|40
op_plus
l_int|400
suffix:semicolon
id|buffer
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|offset
op_assign
id|ORIG_OFFSET
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|check_valid_sha1
c_func
(paren
id|ce-&gt;sha1
)paren
OL
l_int|0
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_plus
id|ce-&gt;namelen
op_plus
l_int|60
OG
id|size
)paren
(brace
id|size
op_assign
id|alloc_nr
c_func
(paren
id|offset
op_plus
id|ce-&gt;namelen
op_plus
l_int|60
)paren
suffix:semicolon
id|buffer
op_assign
id|realloc
c_func
(paren
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|offset
comma
l_string|&quot;%o %s&quot;
comma
id|ce-&gt;st_mode
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|buffer
(braket
id|offset
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
op_plus
id|offset
comma
id|ce-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|20
suffix:semicolon
)brace
id|i
op_assign
id|prepend_integer
c_func
(paren
id|buffer
comma
id|offset
id|ORIG_OFFSET
comma
id|ORIG_OFFSET
)paren
suffix:semicolon
id|i
op_sub_assign
l_int|5
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
op_plus
id|i
comma
l_string|&quot;tree &quot;
comma
l_int|5
)paren
suffix:semicolon
id|buffer
op_add_assign
id|i
suffix:semicolon
id|offset
op_sub_assign
id|i
suffix:semicolon
id|write_sha1_file
c_func
(paren
id|buffer
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
