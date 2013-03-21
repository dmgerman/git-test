multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;userdiff.h&quot;
macro_line|#include &quot;streaming.h&quot;
DECL|macro|BATCH
mdefine_line|#define BATCH 1
DECL|macro|BATCH_CHECK
mdefine_line|#define BATCH_CHECK 2
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
DECL|function|cat_one_file
r_static
r_int
id|cat_one_file
c_func
(paren
r_int
id|opt
comma
r_const
r_char
op_star
id|exp_type
comma
r_const
r_char
op_star
id|obj_name
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|object_context
id|obj_context
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_with_context
c_func
(paren
id|obj_name
comma
l_int|0
comma
id|sha1
comma
op_amp
id|obj_context
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|obj_name
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|type
OG
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
r_typename
(paren
id|type
)paren
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
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OG
l_int|0
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
l_string|&quot;Not a valid object name %s&quot;
comma
id|obj_name
)paren
suffix:semicolon
multiline_comment|/* custom pretty-print here */
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_TREE
)paren
(brace
r_const
r_char
op_star
id|ls_args
(braket
l_int|3
)braket
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
id|ls_args
(braket
l_int|0
)braket
op_assign
l_string|&quot;ls-tree&quot;
suffix:semicolon
id|ls_args
(braket
l_int|1
)braket
op_assign
id|obj_name
suffix:semicolon
r_return
id|cmd_ls_tree
c_func
(paren
l_int|2
comma
id|ls_args
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_BLOB
)paren
r_return
id|stream_blob_to_fd
c_func
(paren
l_int|1
comma
id|sha1
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
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
id|obj_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_TAG
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
l_char|&squot;c&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|obj_context.path
(braket
l_int|0
)braket
)paren
id|die
c_func
(paren
l_string|&quot;git cat-file --textconv %s: &lt;object&gt; must be &lt;sha1:path&gt;&quot;
comma
id|obj_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|textconv_object
c_func
(paren
id|obj_context.path
comma
id|obj_context.mode
comma
id|sha1
comma
l_int|1
comma
op_amp
id|buf
comma
op_amp
id|size
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git cat-file --textconv: unable to run textconv on %s&quot;
comma
id|obj_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|type_from_string
c_func
(paren
id|exp_type
)paren
op_eq
id|OBJ_BLOB
)paren
(brace
r_int
r_char
id|blob_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
op_eq
id|OBJ_TAG
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
l_string|&quot;object &quot;
comma
l_int|7
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|buffer
op_plus
l_int|7
comma
id|blob_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s not a valid tag&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_else
id|hashcpy
c_func
(paren
id|blob_sha1
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sha1_object_info
c_func
(paren
id|blob_sha1
comma
l_int|NULL
)paren
op_eq
id|OBJ_BLOB
)paren
r_return
id|stream_blob_to_fd
c_func
(paren
l_int|1
comma
id|blob_sha1
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * we attempted to dereference a tag to a blob&n;&t;&t;&t; * and failed; there may be new dereference&n;&t;&t;&t; * mechanisms this code is not aware of.&n;&t;&t;&t; * fall-back to the usual case.&n;&t;&t;&t; */
)brace
id|buf
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
id|exp_type
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
l_string|&quot;git cat-file: unknown option: %s&quot;
comma
id|exp_type
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
l_string|&quot;git cat-file %s: bad file&quot;
comma
id|obj_name
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
DECL|function|batch_one_object
r_static
r_int
id|batch_one_object
c_func
(paren
r_const
r_char
op_star
id|obj_name
comma
r_int
id|print_contents
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_enum
id|object_type
id|type
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|contents
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_name
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|obj_name
comma
id|sha1
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s missing&bslash;n&quot;
comma
id|obj_name
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|print_contents
op_eq
id|BATCH
)paren
id|contents
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_else
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_le
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s missing&bslash;n&quot;
comma
id|obj_name
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|print_contents
op_eq
id|BATCH
)paren
id|free
c_func
(paren
id|contents
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s %s %lu&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_typename
(paren
id|type
)paren
comma
id|size
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|print_contents
op_eq
id|BATCH
)paren
(brace
id|write_or_die
c_func
(paren
l_int|1
comma
id|contents
comma
id|size
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|free
c_func
(paren
id|contents
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|batch_objects
r_static
r_int
id|batch_objects
c_func
(paren
r_int
id|print_contents
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
r_int
id|error
op_assign
id|batch_one_object
c_func
(paren
id|buf.buf
comma
id|print_contents
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cat_file_usage
r_static
r_const
r_char
op_star
r_const
id|cat_file_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git cat-file (-t|-s|-e|-p|&lt;type&gt;|--textconv) &lt;object&gt;&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git cat-file (--batch|--batch-check) &lt; &lt;list_of_objects&gt;&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|git_cat_file_config
r_static
r_int
id|git_cat_file_config
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
id|userdiff_config
c_func
(paren
id|var
comma
id|value
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
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
id|opt
op_assign
l_int|0
comma
id|batch
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|exp_type
op_assign
l_int|NULL
comma
op_star
id|obj_name
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_GROUP
c_func
(paren
id|N_
c_func
(paren
l_string|&quot;&lt;type&gt; can be one of: blob, tree, commit, tag&quot;
)paren
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|NULL
comma
op_amp
id|opt
comma
id|N_
c_func
(paren
l_string|&quot;show object type&quot;
)paren
comma
l_char|&squot;t&squot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;s&squot;
comma
l_int|NULL
comma
op_amp
id|opt
comma
id|N_
c_func
(paren
l_string|&quot;show object size&quot;
)paren
comma
l_char|&squot;s&squot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;e&squot;
comma
l_int|NULL
comma
op_amp
id|opt
comma
id|N_
c_func
(paren
l_string|&quot;exit with zero when there&squot;s no error&quot;
)paren
comma
l_char|&squot;e&squot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;p&squot;
comma
l_int|NULL
comma
op_amp
id|opt
comma
id|N_
c_func
(paren
l_string|&quot;pretty-print object&squot;s content&quot;
)paren
comma
l_char|&squot;p&squot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;textconv&quot;
comma
op_amp
id|opt
comma
id|N_
c_func
(paren
l_string|&quot;for blob objects, run textconv on object&squot;s content&quot;
)paren
comma
l_char|&squot;c&squot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;batch&quot;
comma
op_amp
id|batch
comma
id|N_
c_func
(paren
l_string|&quot;show info and content of objects fed from the standard input&quot;
)paren
comma
id|BATCH
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;batch-check&quot;
comma
op_amp
id|batch
comma
id|N_
c_func
(paren
l_string|&quot;show info about objects fed from the standard input&quot;
)paren
comma
id|BATCH_CHECK
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_cat_file_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
op_logical_and
id|argc
op_ne
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|cat_file_usage
comma
id|options
)paren
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
id|cat_file_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt
)paren
(brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
id|obj_name
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_else
id|usage_with_options
c_func
(paren
id|cat_file_usage
comma
id|options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|opt
op_logical_and
op_logical_neg
id|batch
)paren
(brace
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
)paren
(brace
id|exp_type
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|obj_name
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_else
id|usage_with_options
c_func
(paren
id|cat_file_usage
comma
id|options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|batch
op_logical_and
(paren
id|opt
op_logical_or
id|argc
)paren
)paren
(brace
id|usage_with_options
c_func
(paren
id|cat_file_usage
comma
id|options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|batch
)paren
r_return
id|batch_objects
c_func
(paren
id|batch
)paren
suffix:semicolon
r_return
id|cat_one_file
c_func
(paren
id|opt
comma
id|exp_type
comma
id|obj_name
)paren
suffix:semicolon
)brace
eof
