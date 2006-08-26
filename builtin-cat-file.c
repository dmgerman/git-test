multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|function|pprint_tag
r_static
r_void
id|pprint_tag
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
multiline_comment|/* the parser in tag.c is useless here. */
r_const
r_char
op_star
id|endp
op_assign
id|buf
op_plus
id|size
suffix:semicolon
r_const
r_char
op_star
id|cp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|cp
OL
id|endp
)paren
(brace
r_char
id|c
op_assign
op_star
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
l_int|7
op_le
id|endp
id|cp
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;tagger &quot;
comma
id|cp
comma
l_int|7
)paren
)paren
(brace
r_const
r_char
op_star
id|tagger
op_assign
id|cp
suffix:semicolon
multiline_comment|/* Found the tagger line.  Copy out the contents&n;&t;&t;&t; * of the buffer so far.&n;&t;&t;&t; */
id|write_or_die
c_func
(paren
l_int|1
comma
id|buf
comma
id|cp
id|buf
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Do something intelligent, like pretty-printing&n;&t;&t;&t; * the date.&n;&t;&t;&t; */
r_while
c_loop
(paren
id|cp
OL
id|endp
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* tagger to cp is a line&n;&t;&t;&t;&t;&t; * that has ident and time.&n;&t;&t;&t;&t;&t; */
r_const
r_char
op_star
id|sp
op_assign
id|tagger
suffix:semicolon
r_char
op_star
id|ep
suffix:semicolon
r_int
r_int
id|date
suffix:semicolon
r_int
id|tz
suffix:semicolon
r_while
c_loop
(paren
id|sp
OL
id|cp
op_logical_and
op_star
id|sp
op_ne
l_char|&squot;&gt;&squot;
)paren
id|sp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_eq
id|cp
)paren
(brace
multiline_comment|/* give up */
id|write_or_die
c_func
(paren
l_int|1
comma
id|tagger
comma
id|cp
id|tagger
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sp
OL
id|cp
op_logical_and
op_logical_neg
(paren
l_char|&squot;0&squot;
op_le
op_star
id|sp
op_logical_and
op_star
id|sp
op_le
l_char|&squot;9&squot;
)paren
)paren
id|sp
op_increment
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|tagger
comma
id|sp
id|tagger
)paren
suffix:semicolon
id|date
op_assign
id|strtoul
c_func
(paren
id|sp
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
id|tz
op_assign
id|strtol
c_func
(paren
id|ep
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|sp
op_assign
id|show_date
c_func
(paren
id|date
comma
id|tz
comma
l_int|0
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|sp
comma
id|strlen
c_func
(paren
id|sp
)paren
)paren
suffix:semicolon
id|xwrite
c_func
(paren
l_int|1
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cp
OL
id|endp
op_logical_and
op_star
id|cp
op_eq
l_char|&squot;&bslash;n&squot;
)paren
multiline_comment|/* end of header */
r_break
suffix:semicolon
)brace
multiline_comment|/* At this point, we have copied out the header up to the end of&n;&t; * the tagger line and cp points at one past &bslash;n.  It could be the&n;&t; * next header line after the tagger line, or it could be another&n;&t; * &bslash;n that marks the end of the headers.  We need to copy out the&n;&t; * remainder as is.&n;&t; */
r_if
c_cond
(paren
id|cp
OL
id|endp
)paren
id|write_or_die
c_func
(paren
l_int|1
comma
id|cp
comma
id|endp
id|cp
)paren
suffix:semicolon
)brace
DECL|function|cmd_cat_file
r_int
id|cmd_cat_file
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|opt
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
)paren
id|usage
c_func
(paren
l_string|&quot;git-cat-file [-t|-s|-e|-p|&lt;type&gt;] &lt;sha1&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|opt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|opt
op_assign
id|argv
(braket
l_int|1
)braket
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
op_logical_or
id|argv
(braket
l_int|1
)braket
(braket
l_int|2
)braket
)paren
id|opt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Not a single character option */
)brace
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|opt
)paren
(brace
r_case
l_char|&squot;t&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sha1_object_info
c_func
(paren
id|sha1
comma
id|type
comma
l_int|NULL
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sha1_object_info
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%lu&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;e&squot;
suffix:colon
r_return
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
r_if
c_cond
(paren
id|sha1_object_info
c_func
(paren
id|sha1
comma
id|type
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* custom pretty-print here */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|tree_type
)paren
)paren
r_return
id|cmd_ls_tree
c_func
(paren
l_int|2
comma
id|argv
op_plus
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;Cannot read object %s&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|tag_type
)paren
)paren
(brace
id|pprint_tag
c_func
(paren
id|sha1
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* otherwise just spit out the data */
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|buf
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
id|argv
(braket
l_int|1
)braket
comma
op_amp
id|size
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;git-cat-file: unknown option: %s&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;git-cat-file %s: bad file&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
