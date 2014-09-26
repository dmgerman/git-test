multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; * Copyright (C) Junio C Hamano, 2005&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
multiline_comment|/*&n; * This is to create corrupt objects for debugging and as such it&n; * needs to bypass the data conversion performed by, and the type&n; * limitation imposed by, index_fd() and its callees.&n; */
DECL|function|hash_literally
r_static
r_int
id|hash_literally
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
id|fd
comma
r_const
r_char
op_star
id|type
comma
r_int
id|flags
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|buf
comma
id|fd
comma
l_int|4096
)paren
OL
l_int|0
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|flags
op_amp
id|HASH_WRITE_OBJECT
)paren
id|ret
op_assign
id|write_sha1_file
c_func
(paren
id|buf.buf
comma
id|buf.len
comma
id|type
comma
id|sha1
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|hash_sha1_file
c_func
(paren
id|buf.buf
comma
id|buf.len
comma
id|type
comma
id|sha1
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hash_fd
r_static
r_void
id|hash_fd
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|type
comma
r_const
r_char
op_star
id|path
comma
r_int
id|flags
comma
r_int
id|literally
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
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
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
OL
l_int|0
op_logical_or
(paren
id|literally
ques
c_cond
id|hash_literally
c_func
(paren
id|sha1
comma
id|fd
comma
id|type
comma
id|flags
)paren
suffix:colon
id|index_fd
c_func
(paren
id|sha1
comma
id|fd
comma
op_amp
id|st
comma
id|type_from_string
c_func
(paren
id|type
)paren
comma
id|path
comma
id|flags
)paren
)paren
)paren
id|die
c_func
(paren
(paren
id|flags
op_amp
id|HASH_WRITE_OBJECT
)paren
ques
c_cond
l_string|&quot;Unable to add %s to database&quot;
suffix:colon
l_string|&quot;Unable to hash %s&quot;
comma
id|path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;hash to stdout&quot;
)paren
suffix:semicolon
)brace
DECL|function|hash_object
r_static
r_void
id|hash_object
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|type
comma
r_const
r_char
op_star
id|vpath
comma
r_int
id|flags
comma
r_int
id|literally
)paren
(brace
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot open &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|hash_fd
c_func
(paren
id|fd
comma
id|type
comma
id|vpath
comma
id|flags
comma
id|literally
)paren
suffix:semicolon
)brace
DECL|function|hash_stdin_paths
r_static
r_void
id|hash_stdin_paths
c_func
(paren
r_const
r_char
op_star
id|type
comma
r_int
id|no_filters
comma
r_int
id|flags
comma
r_int
id|literally
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
comma
id|nbuf
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
r_if
c_cond
(paren
id|buf.buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unquote_c_style
c_func
(paren
op_amp
id|nbuf
comma
id|buf.buf
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;line is badly quoted&quot;
)paren
suffix:semicolon
id|strbuf_swap
c_func
(paren
op_amp
id|buf
comma
op_amp
id|nbuf
)paren
suffix:semicolon
)brace
id|hash_object
c_func
(paren
id|buf.buf
comma
id|type
comma
id|no_filters
ques
c_cond
l_int|NULL
suffix:colon
id|buf.buf
comma
id|flags
comma
id|literally
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
)brace
DECL|function|cmd_hash_object
r_int
id|cmd_hash_object
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
r_static
r_const
r_char
op_star
r_const
id|hash_object_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git hash-object [-t &lt;type&gt;] [-w] [--path=&lt;file&gt;|--no-filters] [--stdin] [--] &lt;file&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git hash-object  --stdin-paths &lt; &lt;list-of-paths&gt;&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
id|type
op_assign
id|blob_type
suffix:semicolon
r_int
id|hashstdin
op_assign
l_int|0
suffix:semicolon
r_int
id|stdin_paths
op_assign
l_int|0
suffix:semicolon
r_int
id|no_filters
op_assign
l_int|0
suffix:semicolon
r_int
id|literally
op_assign
l_int|0
suffix:semicolon
r_int
id|flags
op_assign
id|HASH_FORMAT_CHECK
suffix:semicolon
r_const
r_char
op_star
id|vpath
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|option
id|hash_object_options
(braket
)braket
op_assign
(brace
id|OPT_STRING
c_func
(paren
l_char|&squot;t&squot;
comma
l_int|NULL
comma
op_amp
id|type
comma
id|N_
c_func
(paren
l_string|&quot;type&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;object type&quot;
)paren
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;w&squot;
comma
l_int|NULL
comma
op_amp
id|flags
comma
id|N_
c_func
(paren
l_string|&quot;write the object into the object database&quot;
)paren
comma
id|HASH_WRITE_OBJECT
)paren
comma
id|OPT_COUNTUP
c_func
(paren
l_int|0
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|hashstdin
comma
id|N_
c_func
(paren
l_string|&quot;read the object from stdin&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;stdin-paths&quot;
comma
op_amp
id|stdin_paths
comma
id|N_
c_func
(paren
l_string|&quot;read file names from stdin&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;no-filters&quot;
comma
op_amp
id|no_filters
comma
id|N_
c_func
(paren
l_string|&quot;store file as is without filters&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;literally&quot;
comma
op_amp
id|literally
comma
id|N_
c_func
(paren
l_string|&quot;just hash any random garbage to create corrupt objects for debugging Git&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;path&quot;
comma
op_amp
id|vpath
comma
id|N_
c_func
(paren
l_string|&quot;file&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;process file as it were from this path&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|prefix_length
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|errstr
op_assign
l_int|NULL
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
l_int|NULL
comma
id|hash_object_options
comma
id|hash_object_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|HASH_WRITE_OBJECT
)paren
(brace
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|prefix_length
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vpath
op_logical_and
id|prefix
)paren
id|vpath
op_assign
id|prefix_filename
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|vpath
)paren
suffix:semicolon
)brace
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stdin_paths
)paren
(brace
r_if
c_cond
(paren
id|hashstdin
)paren
id|errstr
op_assign
l_string|&quot;Can&squot;t use --stdin-paths with --stdin&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argc
)paren
id|errstr
op_assign
l_string|&quot;Can&squot;t specify files with --stdin-paths&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vpath
)paren
id|errstr
op_assign
l_string|&quot;Can&squot;t use --stdin-paths with --path&quot;
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hashstdin
OG
l_int|1
)paren
id|errstr
op_assign
l_string|&quot;Multiple --stdin arguments are not supported&quot;
suffix:semicolon
r_if
c_cond
(paren
id|vpath
op_logical_and
id|no_filters
)paren
id|errstr
op_assign
l_string|&quot;Can&squot;t use --path with --no-filters&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errstr
)paren
(brace
id|error
c_func
(paren
l_string|&quot;%s&quot;
comma
id|errstr
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|hash_object_usage
comma
id|hash_object_options
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hashstdin
)paren
id|hash_fd
c_func
(paren
l_int|0
comma
id|type
comma
id|vpath
comma
id|flags
comma
id|literally
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
l_int|0
op_le
id|prefix_length
)paren
id|arg
op_assign
id|prefix_filename
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|arg
)paren
suffix:semicolon
id|hash_object
c_func
(paren
id|arg
comma
id|type
comma
id|no_filters
ques
c_cond
l_int|NULL
suffix:colon
id|vpath
ques
c_cond
id|vpath
suffix:colon
id|arg
comma
id|flags
comma
id|literally
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stdin_paths
)paren
id|hash_stdin_paths
c_func
(paren
id|type
comma
id|no_filters
comma
id|flags
comma
id|literally
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
