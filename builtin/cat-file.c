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
DECL|struct|expand_data
r_struct
id|expand_data
(brace
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|type
r_enum
id|object_type
id|type
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|disk_size
r_int
r_int
id|disk_size
suffix:semicolon
DECL|member|rest
r_const
r_char
op_star
id|rest
suffix:semicolon
multiline_comment|/*&n;&t; * If mark_query is true, we do not expand anything, but rather&n;&t; * just mark the object_info with items we wish to query.&n;&t; */
DECL|member|mark_query
r_int
id|mark_query
suffix:semicolon
multiline_comment|/*&n;&t; * After a mark_query run, this object_info is set up to be&n;&t; * passed to sha1_object_info_extended. It will point to the data&n;&t; * elements above, so you can retrieve the response from there.&n;&t; */
DECL|member|info
r_struct
id|object_info
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|function|is_atom
r_static
r_int
id|is_atom
c_func
(paren
r_const
r_char
op_star
id|atom
comma
r_const
r_char
op_star
id|s
comma
r_int
id|slen
)paren
(brace
r_int
id|alen
op_assign
id|strlen
c_func
(paren
id|atom
)paren
suffix:semicolon
r_return
id|alen
op_eq
id|slen
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|atom
comma
id|s
comma
id|alen
)paren
suffix:semicolon
)brace
DECL|function|expand_atom
r_static
r_void
id|expand_atom
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|atom
comma
r_int
id|len
comma
r_void
op_star
id|vdata
)paren
(brace
r_struct
id|expand_data
op_star
id|data
op_assign
id|vdata
suffix:semicolon
r_if
c_cond
(paren
id|is_atom
c_func
(paren
l_string|&quot;objectname&quot;
comma
id|atom
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;mark_query
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|sha1_to_hex
c_func
(paren
id|data-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_atom
c_func
(paren
l_string|&quot;objecttype&quot;
comma
id|atom
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;mark_query
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
r_typename
(paren
id|data-&gt;type
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_atom
c_func
(paren
l_string|&quot;objectsize&quot;
comma
id|atom
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
id|data-&gt;mark_query
)paren
id|data-&gt;info.sizep
op_assign
op_amp
id|data-&gt;size
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;%lu&quot;
comma
id|data-&gt;size
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_atom
c_func
(paren
l_string|&quot;objectsize:disk&quot;
comma
id|atom
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
id|data-&gt;mark_query
)paren
id|data-&gt;info.disk_sizep
op_assign
op_amp
id|data-&gt;disk_size
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;%lu&quot;
comma
id|data-&gt;disk_size
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_atom
c_func
(paren
l_string|&quot;rest&quot;
comma
id|atom
comma
id|len
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;mark_query
op_logical_and
id|data-&gt;rest
)paren
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|data-&gt;rest
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;unknown format element: %.*s&quot;
comma
id|len
comma
id|atom
)paren
suffix:semicolon
)brace
DECL|function|expand_format
r_static
r_int
id|expand_format
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|start
comma
r_void
op_star
id|data
)paren
(brace
r_const
r_char
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
op_star
id|start
op_ne
l_char|&squot;(&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|end
op_assign
id|strchr
c_func
(paren
id|start
op_plus
l_int|1
comma
l_char|&squot;)&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|end
)paren
id|die
c_func
(paren
l_string|&quot;format element &squot;%s&squot; does not end in &squot;)&squot;&quot;
comma
id|start
)paren
suffix:semicolon
id|expand_atom
c_func
(paren
id|sb
comma
id|start
op_plus
l_int|1
comma
id|end
id|start
l_int|1
comma
id|data
)paren
suffix:semicolon
r_return
id|end
id|start
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|print_object_or_die
r_static
r_void
id|print_object_or_die
c_func
(paren
r_int
id|fd
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_enum
id|object_type
id|type
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_BLOB
)paren
(brace
r_if
c_cond
(paren
id|stream_blob_to_fd
c_func
(paren
id|fd
comma
id|sha1
comma
l_int|NULL
comma
l_int|0
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to stream %s to stdout&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_enum
id|object_type
id|rtype
suffix:semicolon
r_int
r_int
id|rsize
suffix:semicolon
r_void
op_star
id|contents
suffix:semicolon
id|contents
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|rtype
comma
op_amp
id|rsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|contents
)paren
id|die
c_func
(paren
l_string|&quot;object %s disappeared&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtype
op_ne
id|type
)paren
id|die
c_func
(paren
l_string|&quot;object %s changed type!?&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsize
op_ne
id|size
)paren
id|die
c_func
(paren
l_string|&quot;object %s change size!?&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|fd
comma
id|contents
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|contents
)paren
suffix:semicolon
)brace
)brace
DECL|struct|batch_options
r_struct
id|batch_options
(brace
DECL|member|enabled
r_int
id|enabled
suffix:semicolon
DECL|member|print_contents
r_int
id|print_contents
suffix:semicolon
DECL|member|format
r_const
r_char
op_star
id|format
suffix:semicolon
)brace
suffix:semicolon
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
r_struct
id|batch_options
op_star
id|opt
comma
r_struct
id|expand_data
op_star
id|data
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
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
id|data-&gt;sha1
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
id|data-&gt;type
op_assign
id|sha1_object_info_extended
c_func
(paren
id|data-&gt;sha1
comma
op_amp
id|data-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;type
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
r_return
l_int|0
suffix:semicolon
)brace
id|strbuf_expand
c_func
(paren
op_amp
id|buf
comma
id|opt-&gt;format
comma
id|expand_format
comma
id|data
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|buf.buf
comma
id|buf.len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;print_contents
)paren
(brace
id|print_object_or_die
c_func
(paren
l_int|1
comma
id|data-&gt;sha1
comma
id|data-&gt;type
comma
id|data-&gt;size
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
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
r_struct
id|batch_options
op_star
id|opt
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|expand_data
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;format
)paren
id|opt-&gt;format
op_assign
l_string|&quot;%(objectname) %(objecttype) %(objectsize)&quot;
suffix:semicolon
multiline_comment|/*&n;&t; * Expand once with our special mark_query flag, which will prime the&n;&t; * object_info to be handed to sha1_object_info_extended for each&n;&t; * object.&n;&t; */
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|data.mark_query
op_assign
l_int|1
suffix:semicolon
id|strbuf_expand
c_func
(paren
op_amp
id|buf
comma
id|opt-&gt;format
comma
id|expand_format
comma
op_amp
id|data
)paren
suffix:semicolon
id|data.mark_query
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We are going to call get_sha1 on a potentially very large number of&n;&t; * objects. In most large cases, these will be actual object sha1s. The&n;&t; * cost to double-check that each one is not also a ref (just so we can&n;&t; * warn) ends up dwarfing the actual cost of the object lookups&n;&t; * themselves. We can work around it by just turning off the warning.&n;&t; */
id|warn_on_object_refname_ambiguity
op_assign
l_int|0
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
r_char
op_star
id|p
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Split at first whitespace, tying off the beginning of the&n;&t;&t; * string and saving the remainder (or NULL) in data.rest.&n;&t;&t; */
id|p
op_assign
id|strpbrk
c_func
(paren
id|buf.buf
comma
l_string|&quot; &bslash;t&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_while
c_loop
(paren
op_star
id|p
op_logical_and
id|strchr
c_func
(paren
l_string|&quot; &bslash;t&quot;
comma
op_star
id|p
)paren
)paren
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
id|data.rest
op_assign
id|p
suffix:semicolon
id|error
op_assign
id|batch_one_object
c_func
(paren
id|buf.buf
comma
id|opt
comma
op_amp
id|data
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
DECL|function|batch_option_callback
r_static
r_int
id|batch_option_callback
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|batch_options
op_star
id|bo
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
(brace
id|memset
c_func
(paren
id|bo
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|bo
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|bo-&gt;enabled
op_assign
l_int|1
suffix:semicolon
id|bo-&gt;print_contents
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|opt-&gt;long_name
comma
l_string|&quot;batch&quot;
)paren
suffix:semicolon
id|bo-&gt;format
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
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
r_struct
id|batch_options
id|batch
op_assign
(brace
l_int|0
)brace
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
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;batch&quot;
comma
op_amp
id|batch
comma
l_string|&quot;format&quot;
comma
id|N_
c_func
(paren
l_string|&quot;show info and content of objects fed from the standard input&quot;
)paren
comma
id|PARSE_OPT_OPTARG
comma
id|batch_option_callback
)brace
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;batch-check&quot;
comma
op_amp
id|batch
comma
l_string|&quot;format&quot;
comma
id|N_
c_func
(paren
l_string|&quot;show info about objects fed from the standard input&quot;
)paren
comma
id|PARSE_OPT_OPTARG
comma
id|batch_option_callback
)brace
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
id|batch.enabled
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
id|batch.enabled
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
id|batch.enabled
)paren
r_return
id|batch_objects
c_func
(paren
op_amp
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
