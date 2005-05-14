multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|diff_opts
r_static
r_const
r_char
op_star
id|diff_opts
op_assign
l_string|&quot;-pu&quot;
suffix:semicolon
DECL|function|external_diff
r_static
r_const
r_char
op_star
id|external_diff
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_char
op_star
id|external_diff_cmd
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|done_preparing
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|done_preparing
)paren
r_return
id|external_diff_cmd
suffix:semicolon
multiline_comment|/*&n;&t; * Default values above are meant to match the&n;&t; * Linux kernel development style.  Examples of&n;&t; * alternative styles you can specify via environment&n;&t; * variables are:&n;&t; *&n;&t; * GIT_DIFF_OPTS=&quot;-c&quot;;&n;&t; */
r_if
c_cond
(paren
id|gitenv
c_func
(paren
l_string|&quot;GIT_EXTERNAL_DIFF&quot;
)paren
)paren
id|external_diff_cmd
op_assign
id|gitenv
c_func
(paren
l_string|&quot;GIT_EXTERNAL_DIFF&quot;
)paren
suffix:semicolon
multiline_comment|/* In case external diff fails... */
id|diff_opts
op_assign
id|gitenv
c_func
(paren
l_string|&quot;GIT_DIFF_OPTS&quot;
)paren
ques
c_cond
suffix:colon
id|diff_opts
suffix:semicolon
id|done_preparing
op_assign
l_int|1
suffix:semicolon
r_return
id|external_diff_cmd
suffix:semicolon
)brace
multiline_comment|/* Help to copy the thing properly quoted for the shell safety.&n; * any single quote is replaced with &squot;&bslash;&squot;&squot;, and the caller is&n; * expected to enclose the result within a single quote pair.&n; *&n; * E.g.&n; *  original     sq_expand     result&n; *  name     ==&gt; name      ==&gt; &squot;name&squot;&n; *  a b      ==&gt; a b       ==&gt; &squot;a b&squot;&n; *  a&squot;b      ==&gt; a&squot;&bslash;&squot;&squot;b    ==&gt; &squot;a&squot;&bslash;&squot;&squot;b&squot;&n; */
DECL|function|sq_expand
r_static
r_char
op_star
id|sq_expand
c_func
(paren
r_const
r_char
op_star
id|src
)paren
(brace
r_static
r_char
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_int
id|cnt
comma
id|c
suffix:semicolon
r_const
r_char
op_star
id|cp
suffix:semicolon
r_char
op_star
id|bp
suffix:semicolon
multiline_comment|/* count bytes needed to store the quoted string. */
r_for
c_loop
(paren
id|cnt
op_assign
l_int|1
comma
id|cp
op_assign
id|src
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cnt
op_increment
comma
id|cp
op_increment
)paren
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;&bslash;&squot;&squot;
)paren
id|cnt
op_add_assign
l_int|3
suffix:semicolon
id|buf
op_assign
id|xmalloc
c_func
(paren
id|cnt
)paren
suffix:semicolon
id|bp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;&squot;&squot;
)paren
op_star
id|bp
op_increment
op_assign
id|c
suffix:semicolon
r_else
(brace
id|bp
op_assign
id|strcpy
c_func
(paren
id|bp
comma
l_string|&quot;&squot;&bslash;&bslash;&squot;&squot;&quot;
)paren
suffix:semicolon
id|bp
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
op_star
id|bp
op_assign
l_int|0
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|struct|diff_tempfile
r_static
r_struct
id|diff_tempfile
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|hex
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
DECL|member|mode
r_char
id|mode
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|tmp_path
r_char
id|tmp_path
(braket
l_int|50
)braket
suffix:semicolon
DECL|variable|diff_temp
)brace
id|diff_temp
(braket
l_int|2
)braket
suffix:semicolon
DECL|function|builtin_diff
r_static
r_void
id|builtin_diff
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|diff_tempfile
op_star
id|temp
)paren
(brace
r_int
id|i
comma
id|next_at
suffix:semicolon
r_const
r_char
op_star
id|git_prefix
op_assign
l_string|&quot;# mode: &quot;
suffix:semicolon
r_const
r_char
op_star
id|diff_cmd
op_assign
l_string|&quot;diff -L&squot;%s%s&squot; -L&squot;%s%s&squot;&quot;
suffix:semicolon
r_const
r_char
op_star
id|diff_arg
op_assign
l_string|&quot;&squot;%s&squot; &squot;%s&squot;||:&quot;
suffix:semicolon
multiline_comment|/* &quot;||:&quot; is to return 0 */
r_const
r_char
op_star
id|input_name_sq
(braket
l_int|2
)braket
suffix:semicolon
r_const
r_char
op_star
id|path0
(braket
l_int|2
)braket
suffix:semicolon
r_const
r_char
op_star
id|path1
(braket
l_int|2
)braket
suffix:semicolon
r_const
r_char
op_star
id|name_sq
op_assign
id|sq_expand
c_func
(paren
id|name
)paren
suffix:semicolon
r_char
op_star
id|cmd
suffix:semicolon
multiline_comment|/* diff_cmd and diff_arg have 6 %s in total which makes&n;&t; * the sum of these strings 12 bytes larger than required.&n;&t; * we use 2 spaces around diff-opts, and we need to count&n;&t; * terminating NUL, so we subtract 9 here.&n;&t; */
r_int
id|cmd_size
op_assign
(paren
id|strlen
c_func
(paren
id|diff_cmd
)paren
op_plus
id|strlen
c_func
(paren
id|diff_opts
)paren
op_plus
id|strlen
c_func
(paren
id|diff_arg
)paren
l_int|9
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|input_name_sq
(braket
id|i
)braket
op_assign
id|sq_expand
c_func
(paren
id|temp
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|temp
(braket
id|i
)braket
dot
id|name
comma
l_string|&quot;/dev/null&quot;
)paren
)paren
(brace
id|path0
(braket
id|i
)braket
op_assign
l_string|&quot;/dev/null&quot;
suffix:semicolon
id|path1
(braket
id|i
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
)brace
r_else
(brace
id|path0
(braket
id|i
)braket
op_assign
id|i
ques
c_cond
l_string|&quot;b/&quot;
suffix:colon
l_string|&quot;a/&quot;
suffix:semicolon
id|path1
(braket
id|i
)braket
op_assign
id|name_sq
suffix:semicolon
)brace
id|cmd_size
op_add_assign
(paren
id|strlen
c_func
(paren
id|path0
(braket
id|i
)braket
)paren
op_plus
id|strlen
c_func
(paren
id|path1
(braket
id|i
)braket
)paren
op_plus
id|strlen
c_func
(paren
id|input_name_sq
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
id|cmd
op_assign
id|xmalloc
c_func
(paren
id|cmd_size
)paren
suffix:semicolon
id|next_at
op_assign
l_int|0
suffix:semicolon
id|next_at
op_add_assign
id|snprintf
c_func
(paren
id|cmd
op_plus
id|next_at
comma
id|cmd_size
op_minus
id|next_at
comma
id|diff_cmd
comma
id|path0
(braket
l_int|0
)braket
comma
id|path1
(braket
l_int|0
)braket
comma
id|path0
(braket
l_int|1
)braket
comma
id|path1
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|next_at
op_add_assign
id|snprintf
c_func
(paren
id|cmd
op_plus
id|next_at
comma
id|cmd_size
op_minus
id|next_at
comma
l_string|&quot; %s &quot;
comma
id|diff_opts
)paren
suffix:semicolon
id|next_at
op_add_assign
id|snprintf
c_func
(paren
id|cmd
op_plus
id|next_at
comma
id|cmd_size
op_minus
id|next_at
comma
id|diff_arg
comma
id|input_name_sq
(braket
l_int|0
)braket
comma
id|input_name_sq
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path1
(braket
l_int|0
)braket
(braket
l_int|0
)braket
)paren
id|printf
c_func
(paren
l_string|&quot;%s. %s %s&bslash;n&quot;
comma
id|git_prefix
comma
id|temp
(braket
l_int|1
)braket
dot
id|mode
comma
id|name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|path1
(braket
l_int|1
)braket
(braket
l_int|0
)braket
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s . %s&bslash;n&quot;
comma
id|git_prefix
comma
id|temp
(braket
l_int|0
)braket
dot
id|mode
comma
id|name
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|temp
(braket
l_int|0
)braket
dot
id|mode
comma
id|temp
(braket
l_int|1
)braket
dot
id|mode
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s %s %s&bslash;n&quot;
comma
id|git_prefix
comma
id|temp
(braket
l_int|0
)braket
dot
id|mode
comma
id|temp
(braket
l_int|1
)braket
dot
id|mode
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|temp
(braket
l_int|0
)braket
dot
id|mode
comma
id|temp
(braket
l_int|1
)braket
dot
id|mode
comma
l_int|3
)paren
)paren
multiline_comment|/* we do not run diff between different kind&n;&t;&t;&t; * of objects.&n;&t;&t;&t; */
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;/bin/sh&quot;
comma
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
id|cmd
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a name and sha1 pair, if the dircache tells us the file in&n; * the work tree has that object contents, return true, so that&n; * prepare_temp_file() does not have to inflate and extract.&n; */
DECL|function|work_tree_matches
r_static
r_int
id|work_tree_matches
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|pos
comma
id|len
suffix:semicolon
multiline_comment|/* We do not read the cache ourselves here, because the&n;&t; * benchmark with my previous version that always reads cache&n;&t; * shows that it makes things worse for diff-tree comparing&n;&t; * two linux-2.6 kernel trees in an already checked out work&n;&t; * tree.  This is because most diff-tree comparison deals with&n;&t; * only a small number of files, while reading the cache is&n;&t; * expensive for a large project, and its cost outweighs the&n;&t; * savings we get by not inflating the object to a temporary&n;&t; * file.  Practically, this code only helps when we are used&n;&t; * by diff-cache --cached, which does read the cache before&n;&t; * calling us.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|active_cache
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lstat
c_func
(paren
id|name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
op_logical_or
id|cache_match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
op_logical_or
id|memcmp
c_func
(paren
id|sha1
comma
id|ce-&gt;sha1
comma
l_int|20
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|prep_temp_blob
r_static
r_void
id|prep_temp_blob
c_func
(paren
r_struct
id|diff_tempfile
op_star
id|temp
comma
r_void
op_star
id|blob
comma
r_int
r_int
id|size
comma
r_int
r_char
op_star
id|sha1
comma
r_int
id|mode
)paren
(brace
r_int
id|fd
suffix:semicolon
id|strcpy
c_func
(paren
id|temp-&gt;tmp_path
comma
l_string|&quot;.diff_XXXXXX&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|mkstemp
c_func
(paren
id|temp-&gt;tmp_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to create temp-file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|blob
comma
id|size
)paren
op_ne
id|size
)paren
id|die
c_func
(paren
l_string|&quot;unable to write temp-file&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|temp-&gt;name
op_assign
id|temp-&gt;tmp_path
suffix:semicolon
id|strcpy
c_func
(paren
id|temp-&gt;hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|temp-&gt;hex
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|temp-&gt;mode
comma
l_string|&quot;%06o&quot;
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|prepare_temp_file
r_static
r_void
id|prepare_temp_file
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|diff_tempfile
op_star
id|temp
comma
r_struct
id|diff_spec
op_star
id|one
)paren
(brace
r_static
r_int
r_char
id|null_sha1
(braket
l_int|20
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
r_int
id|use_work_tree
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one-&gt;file_valid
)paren
(brace
id|not_a_valid_file
suffix:colon
multiline_comment|/* A &squot;-&squot; entry produces this for file-2, and&n;&t;&t; * a &squot;+&squot; entry produces this for file-1.&n;&t;&t; */
id|temp-&gt;name
op_assign
l_string|&quot;/dev/null&quot;
suffix:semicolon
id|strcpy
c_func
(paren
id|temp-&gt;hex
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|temp-&gt;mode
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|one-&gt;sha1_valid
op_logical_and
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|one-&gt;blob_sha1
comma
id|null_sha1
comma
r_sizeof
(paren
id|null_sha1
)paren
)paren
op_logical_or
id|work_tree_matches
c_func
(paren
id|name
comma
id|one-&gt;blob_sha1
)paren
)paren
)paren
id|use_work_tree
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one-&gt;sha1_valid
op_logical_or
id|use_work_tree
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
id|temp-&gt;name
op_assign
id|name
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|temp-&gt;name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
r_goto
id|not_a_valid_file
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;stat(%s): %s&quot;
comma
id|temp-&gt;name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
r_int
id|ret
suffix:semicolon
r_char
op_star
id|buf
comma
id|buf_
(braket
l_int|1024
)braket
suffix:semicolon
id|buf
op_assign
(paren
(paren
r_sizeof
(paren
id|buf_
)paren
OL
id|st.st_size
)paren
ques
c_cond
id|xmalloc
c_func
(paren
id|st.st_size
)paren
suffix:colon
id|buf_
)paren
suffix:semicolon
id|ret
op_assign
id|readlink
c_func
(paren
id|name
comma
id|buf
comma
id|st.st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;readlink(%s)&quot;
comma
id|name
)paren
suffix:semicolon
id|prep_temp_blob
c_func
(paren
id|temp
comma
id|buf
comma
id|st.st_size
comma
(paren
id|one-&gt;sha1_valid
ques
c_cond
id|one-&gt;blob_sha1
suffix:colon
id|null_sha1
)paren
comma
(paren
id|one-&gt;sha1_valid
ques
c_cond
id|one-&gt;mode
suffix:colon
id|S_IFLNK
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|one-&gt;sha1_valid
)paren
id|strcpy
c_func
(paren
id|temp-&gt;hex
comma
id|sha1_to_hex
c_func
(paren
id|null_sha1
)paren
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|temp-&gt;hex
comma
id|sha1_to_hex
c_func
(paren
id|one-&gt;blob_sha1
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|temp-&gt;mode
comma
l_string|&quot;%06o&quot;
comma
id|S_IFREG
op_or
id|ce_permissions
c_func
(paren
id|st.st_mode
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_else
(brace
r_void
op_star
id|blob
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|blob
op_assign
id|read_sha1_file
c_func
(paren
id|one-&gt;blob_sha1
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
id|blob
op_logical_or
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;blob&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to read blob object for %s (%s)&quot;
comma
id|name
comma
id|sha1_to_hex
c_func
(paren
id|one-&gt;blob_sha1
)paren
)paren
suffix:semicolon
id|prep_temp_blob
c_func
(paren
id|temp
comma
id|blob
comma
id|size
comma
id|one-&gt;blob_sha1
comma
id|one-&gt;mode
)paren
suffix:semicolon
id|free
c_func
(paren
id|blob
)paren
suffix:semicolon
)brace
)brace
DECL|function|remove_tempfile
r_static
r_void
id|remove_tempfile
c_func
(paren
r_void
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|diff_temp
(braket
id|i
)braket
dot
id|name
op_eq
id|diff_temp
(braket
id|i
)braket
dot
id|tmp_path
)paren
(brace
id|unlink
c_func
(paren
id|diff_temp
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|diff_temp
(braket
id|i
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|remove_tempfile_on_signal
r_static
r_void
id|remove_tempfile_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_tempfile
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* An external diff command takes:&n; *&n; * diff-cmd name infile1 infile1-sha1 infile1-mode &bslash;&n; *               infile2 infile2-sha1 infile2-mode.&n; *&n; */
DECL|function|run_external_diff
r_void
id|run_external_diff
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|diff_spec
op_star
id|one
comma
r_struct
id|diff_spec
op_star
id|two
)paren
(brace
r_struct
id|diff_tempfile
op_star
id|temp
op_assign
id|diff_temp
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_int
id|status
suffix:semicolon
r_static
r_int
id|atexit_asked
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|one
op_logical_and
id|two
)paren
(brace
id|prepare_temp_file
c_func
(paren
id|name
comma
op_amp
id|temp
(braket
l_int|0
)braket
comma
id|one
)paren
suffix:semicolon
id|prepare_temp_file
c_func
(paren
id|name
comma
op_amp
id|temp
(braket
l_int|1
)braket
comma
id|two
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atexit_asked
op_logical_and
(paren
id|temp
(braket
l_int|0
)braket
dot
id|name
op_eq
id|temp
(braket
l_int|0
)braket
dot
id|tmp_path
op_logical_or
id|temp
(braket
l_int|1
)braket
dot
id|name
op_eq
id|temp
(braket
l_int|1
)braket
dot
id|tmp_path
)paren
)paren
(brace
id|atexit_asked
op_assign
l_int|1
suffix:semicolon
id|atexit
c_func
(paren
id|remove_tempfile
)paren
suffix:semicolon
)brace
id|signal
c_func
(paren
id|SIGINT
comma
id|remove_tempfile_on_signal
)paren
suffix:semicolon
)brace
id|fflush
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to fork&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_const
r_char
op_star
id|pgm
op_assign
id|external_diff
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgm
)paren
(brace
r_if
c_cond
(paren
id|one
op_logical_and
id|two
)paren
id|execlp
c_func
(paren
id|pgm
comma
id|pgm
comma
id|name
comma
id|temp
(braket
l_int|0
)braket
dot
id|name
comma
id|temp
(braket
l_int|0
)braket
dot
id|hex
comma
id|temp
(braket
l_int|0
)braket
dot
id|mode
comma
id|temp
(braket
l_int|1
)braket
dot
id|name
comma
id|temp
(braket
l_int|1
)braket
dot
id|hex
comma
id|temp
(braket
l_int|1
)braket
dot
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|execlp
c_func
(paren
id|pgm
comma
id|pgm
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * otherwise we use the built-in one.&n;&t;&t; */
r_if
c_cond
(paren
id|one
op_logical_and
id|two
)paren
id|builtin_diff
c_func
(paren
id|name
comma
id|temp
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;* Unmerged path %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
op_logical_or
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Earlier we did not check the exit status because&n;&t;&t; * diff exits non-zero if files are different, and&n;&t;&t; * we are not interested in knowing that.  It was a&n;&t;&t; * mistake which made it harder to quit a diff-*&n;&t;&t; * session that uses the git-apply-patch-script as&n;&t;&t; * the GIT_EXTERNAL_DIFF.  A custom GIT_EXTERNAL_DIFF&n;&t;&t; * should also exit non-zero only when it wants to&n;&t;&t; * abort the entire diff-* session.&n;&t;&t; */
id|remove_tempfile
c_func
(paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;external diff died, stopping at %s.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|remove_tempfile
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|diff_addremove
r_void
id|diff_addremove
c_func
(paren
r_int
id|addremove
comma
r_int
id|mode
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|base
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_char
id|concatpath
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|diff_spec
id|spec
(braket
l_int|2
)braket
comma
op_star
id|one
comma
op_star
id|two
suffix:semicolon
id|memcpy
c_func
(paren
id|spec
(braket
l_int|0
)braket
dot
id|blob_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|spec
(braket
l_int|0
)braket
dot
id|mode
op_assign
id|mode
suffix:semicolon
id|spec
(braket
l_int|0
)braket
dot
id|sha1_valid
op_assign
id|spec
(braket
l_int|0
)braket
dot
id|file_valid
op_assign
l_int|1
suffix:semicolon
id|spec
(braket
l_int|1
)braket
dot
id|file_valid
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addremove
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|one
op_assign
id|spec
op_plus
l_int|1
suffix:semicolon
id|two
op_assign
id|spec
suffix:semicolon
)brace
r_else
(brace
id|one
op_assign
id|spec
suffix:semicolon
id|two
op_assign
id|one
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path
)paren
(brace
id|strcpy
c_func
(paren
id|concatpath
comma
id|base
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|concatpath
comma
id|path
)paren
suffix:semicolon
)brace
id|run_external_diff
c_func
(paren
id|path
ques
c_cond
id|concatpath
suffix:colon
id|base
comma
id|one
comma
id|two
)paren
suffix:semicolon
)brace
DECL|function|diff_change
r_void
id|diff_change
c_func
(paren
r_int
id|old_mode
comma
r_int
id|new_mode
comma
r_const
r_int
r_char
op_star
id|old_sha1
comma
r_const
r_int
r_char
op_star
id|new_sha1
comma
r_const
r_char
op_star
id|base
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_char
id|concatpath
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|diff_spec
id|spec
(braket
l_int|2
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|spec
(braket
l_int|0
)braket
dot
id|blob_sha1
comma
id|old_sha1
comma
l_int|20
)paren
suffix:semicolon
id|spec
(braket
l_int|0
)braket
dot
id|mode
op_assign
id|old_mode
suffix:semicolon
id|memcpy
c_func
(paren
id|spec
(braket
l_int|1
)braket
dot
id|blob_sha1
comma
id|new_sha1
comma
l_int|20
)paren
suffix:semicolon
id|spec
(braket
l_int|1
)braket
dot
id|mode
op_assign
id|new_mode
suffix:semicolon
id|spec
(braket
l_int|0
)braket
dot
id|sha1_valid
op_assign
id|spec
(braket
l_int|0
)braket
dot
id|file_valid
op_assign
l_int|1
suffix:semicolon
id|spec
(braket
l_int|1
)braket
dot
id|sha1_valid
op_assign
id|spec
(braket
l_int|1
)braket
dot
id|file_valid
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|path
)paren
(brace
id|strcpy
c_func
(paren
id|concatpath
comma
id|base
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|concatpath
comma
id|path
)paren
suffix:semicolon
)brace
id|run_external_diff
c_func
(paren
id|path
ques
c_cond
id|concatpath
suffix:colon
id|base
comma
op_amp
id|spec
(braket
l_int|0
)braket
comma
op_amp
id|spec
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|diff_unmerge
r_void
id|diff_unmerge
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|run_external_diff
c_func
(paren
id|path
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
