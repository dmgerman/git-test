multiline_comment|/*&n; * Copyright (C) 2006, Fredrik Kuivinen &lt;freku045@student.liu.se&gt;&n; */
macro_line|#include &lt;assert.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
DECL|variable|blame_lines
r_struct
id|commit
op_star
op_star
id|blame_lines
suffix:semicolon
DECL|variable|num_blame_lines
r_int
id|num_blame_lines
suffix:semicolon
DECL|struct|util_info
r_struct
id|util_info
(brace
DECL|member|line_map
r_int
op_star
id|line_map
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* blob sha, not commit! */
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|num_lines
r_int
id|num_lines
suffix:semicolon
singleline_comment|//    const char* path;
)brace
suffix:semicolon
DECL|struct|chunk
r_struct
id|chunk
(brace
DECL|member|off1
DECL|member|len1
r_int
id|off1
comma
id|len1
suffix:semicolon
singleline_comment|// ---
DECL|member|off2
DECL|member|len2
r_int
id|off2
comma
id|len2
suffix:semicolon
singleline_comment|// +++
)brace
suffix:semicolon
DECL|struct|patch
r_struct
id|patch
(brace
DECL|member|chunks
r_struct
id|chunk
op_star
id|chunks
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
id|get_blob
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
suffix:semicolon
multiline_comment|/* Only used for statistics */
DECL|variable|num_get_patch
r_static
r_int
id|num_get_patch
op_assign
l_int|0
suffix:semicolon
DECL|variable|num_commits
r_static
r_int
id|num_commits
op_assign
l_int|0
suffix:semicolon
DECL|variable|patch_time
r_static
r_int
id|patch_time
op_assign
l_int|0
suffix:semicolon
DECL|macro|TEMPFILE_PATH_LEN
mdefine_line|#define TEMPFILE_PATH_LEN 60
DECL|function|get_patch
r_static
r_struct
id|patch
op_star
id|get_patch
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit
op_star
id|other
)paren
(brace
r_struct
id|patch
op_star
id|ret
suffix:semicolon
r_struct
id|util_info
op_star
id|info_c
op_assign
(paren
r_struct
id|util_info
op_star
)paren
id|commit-&gt;object.util
suffix:semicolon
r_struct
id|util_info
op_star
id|info_o
op_assign
(paren
r_struct
id|util_info
op_star
)paren
id|other-&gt;object.util
suffix:semicolon
r_char
id|tmp_path1
(braket
id|TEMPFILE_PATH_LEN
)braket
comma
id|tmp_path2
(braket
id|TEMPFILE_PATH_LEN
)braket
suffix:semicolon
r_char
id|diff_cmd
(braket
id|TEMPFILE_PATH_LEN
op_star
l_int|2
op_plus
l_int|20
)braket
suffix:semicolon
r_struct
id|timeval
id|tv_start
comma
id|tv_end
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|FILE
op_star
id|fin
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
id|ret
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|patch
)paren
)paren
suffix:semicolon
id|ret-&gt;chunks
op_assign
l_int|NULL
suffix:semicolon
id|ret-&gt;num
op_assign
l_int|0
suffix:semicolon
id|get_blob
c_func
(paren
id|commit
)paren
suffix:semicolon
id|get_blob
c_func
(paren
id|other
)paren
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|tv_start
comma
l_int|NULL
)paren
suffix:semicolon
id|fd
op_assign
id|git_mkstemp
c_func
(paren
id|tmp_path1
comma
id|TEMPFILE_PATH_LEN
comma
l_string|&quot;git-blame-XXXXXX&quot;
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
l_string|&quot;unable to create temp-file: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xwrite
c_func
(paren
id|fd
comma
id|info_c-&gt;buf
comma
id|info_c-&gt;size
)paren
op_ne
id|info_c-&gt;size
)paren
id|die
c_func
(paren
l_string|&quot;write failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
id|git_mkstemp
c_func
(paren
id|tmp_path2
comma
id|TEMPFILE_PATH_LEN
comma
l_string|&quot;git-blame-XXXXXX&quot;
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
l_string|&quot;unable to create temp-file: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xwrite
c_func
(paren
id|fd
comma
id|info_o-&gt;buf
comma
id|info_o-&gt;size
)paren
op_ne
id|info_o-&gt;size
)paren
id|die
c_func
(paren
l_string|&quot;write failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|diff_cmd
comma
l_string|&quot;diff -u0 %s %s&quot;
comma
id|tmp_path1
comma
id|tmp_path2
)paren
suffix:semicolon
id|fin
op_assign
id|popen
c_func
(paren
id|diff_cmd
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fin
)paren
id|die
c_func
(paren
l_string|&quot;popen failed: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|fin
)paren
)paren
(brace
r_struct
id|chunk
op_star
id|chunk
suffix:semicolon
r_char
op_star
id|start
comma
op_star
id|sp
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;@&squot;
op_logical_or
id|buf
(braket
l_int|1
)braket
op_ne
l_char|&squot;@&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;chunk line: %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|ret-&gt;num
op_increment
suffix:semicolon
id|ret-&gt;chunks
op_assign
id|xrealloc
c_func
(paren
id|ret-&gt;chunks
comma
r_sizeof
(paren
r_struct
id|chunk
)paren
op_star
id|ret-&gt;num
)paren
suffix:semicolon
id|chunk
op_assign
op_amp
id|ret-&gt;chunks
(braket
id|ret-&gt;num
l_int|1
)braket
suffix:semicolon
m_assert
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;@@ -&quot;
comma
l_int|4
)paren
)paren
suffix:semicolon
id|start
op_assign
id|buf
op_plus
l_int|4
suffix:semicolon
id|sp
op_assign
id|index
c_func
(paren
id|start
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
op_star
id|sp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|index
c_func
(paren
id|start
comma
l_char|&squot;,&squot;
)paren
)paren
(brace
r_int
id|ret
op_assign
id|sscanf
c_func
(paren
id|start
comma
l_string|&quot;%d,%d&quot;
comma
op_amp
id|chunk-&gt;off1
comma
op_amp
id|chunk-&gt;len1
)paren
suffix:semicolon
m_assert
(paren
id|ret
op_eq
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|ret
op_assign
id|sscanf
c_func
(paren
id|start
comma
l_string|&quot;%d&quot;
comma
op_amp
id|chunk-&gt;off1
)paren
suffix:semicolon
m_assert
(paren
id|ret
op_eq
l_int|1
)paren
suffix:semicolon
id|chunk-&gt;len1
op_assign
l_int|1
suffix:semicolon
)brace
op_star
id|sp
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|start
op_assign
id|sp
op_plus
l_int|1
suffix:semicolon
id|sp
op_assign
id|index
c_func
(paren
id|start
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
op_star
id|sp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|index
c_func
(paren
id|start
comma
l_char|&squot;,&squot;
)paren
)paren
(brace
r_int
id|ret
op_assign
id|sscanf
c_func
(paren
id|start
comma
l_string|&quot;%d,%d&quot;
comma
op_amp
id|chunk-&gt;off2
comma
op_amp
id|chunk-&gt;len2
)paren
suffix:semicolon
m_assert
(paren
id|ret
op_eq
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|ret
op_assign
id|sscanf
c_func
(paren
id|start
comma
l_string|&quot;%d&quot;
comma
op_amp
id|chunk-&gt;off2
)paren
suffix:semicolon
m_assert
(paren
id|ret
op_eq
l_int|1
)paren
suffix:semicolon
id|chunk-&gt;len2
op_assign
l_int|1
suffix:semicolon
)brace
op_star
id|sp
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;len1
op_eq
l_int|0
)paren
id|chunk-&gt;off1
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;len2
op_eq
l_int|0
)paren
id|chunk-&gt;off2
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;off1
OG
l_int|0
)paren
id|chunk-&gt;off1
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;off2
OG
l_int|0
)paren
id|chunk-&gt;off2
op_decrement
suffix:semicolon
m_assert
(paren
id|chunk-&gt;off1
op_ge
l_int|0
)paren
suffix:semicolon
m_assert
(paren
id|chunk-&gt;off2
op_ge
l_int|0
)paren
suffix:semicolon
)brace
id|pclose
c_func
(paren
id|fin
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|tmp_path1
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|tmp_path2
)paren
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|tv_end
comma
l_int|NULL
)paren
suffix:semicolon
id|patch_time
op_add_assign
l_int|1000000
op_star
(paren
id|tv_end.tv_sec
id|tv_start.tv_sec
)paren
op_plus
id|tv_end.tv_usec
id|tv_start.tv_usec
suffix:semicolon
id|num_get_patch
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|free_patch
r_static
r_void
id|free_patch
c_func
(paren
r_struct
id|patch
op_star
id|p
)paren
(brace
id|free
c_func
(paren
id|p-&gt;chunks
)paren
suffix:semicolon
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_static
r_int
id|get_blob_sha1_internal
c_func
(paren
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
r_int
id|baselen
comma
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
comma
r_int
id|stage
)paren
suffix:semicolon
DECL|variable|blob_sha1
r_static
r_int
r_char
id|blob_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|get_blob_sha1
r_static
r_int
id|get_blob_sha1
c_func
(paren
r_struct
id|tree
op_star
id|t
comma
r_const
r_char
op_star
id|pathname
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
id|pathspec
(braket
l_int|2
)braket
suffix:semicolon
id|pathspec
(braket
l_int|0
)braket
op_assign
id|pathname
suffix:semicolon
id|pathspec
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|blob_sha1
comma
l_int|0
comma
r_sizeof
(paren
id|blob_sha1
)paren
)paren
suffix:semicolon
id|read_tree_recursive
c_func
(paren
id|t
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|0
comma
id|pathspec
comma
id|get_blob_sha1_internal
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|blob_sha1
(braket
id|i
)braket
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|20
)paren
r_return
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|sha1
comma
id|blob_sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_blob_sha1_internal
r_static
r_int
id|get_blob_sha1_internal
c_func
(paren
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
r_int
id|baselen
comma
r_const
r_char
op_star
id|pathname
comma
r_int
id|mode
comma
r_int
id|stage
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
r_return
id|READ_TREE_RECURSIVE
suffix:semicolon
id|memcpy
c_func
(paren
id|blob_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_blob
r_static
r_void
id|get_blob
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|util_info
op_star
id|info
op_assign
id|commit-&gt;object.util
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;buf
)paren
r_return
suffix:semicolon
id|info-&gt;buf
op_assign
id|read_sha1_file
c_func
(paren
id|info-&gt;sha1
comma
id|type
comma
op_amp
id|info-&gt;size
)paren
suffix:semicolon
m_assert
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;blob&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* For debugging only */
DECL|function|print_patch
r_static
r_void
id|print_patch
c_func
(paren
r_struct
id|patch
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Num chunks: %d&bslash;n&quot;
comma
id|p-&gt;num
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
id|p-&gt;num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%d,%d %d,%d&bslash;n&quot;
comma
id|p-&gt;chunks
(braket
id|i
)braket
dot
id|off1
comma
id|p-&gt;chunks
(braket
id|i
)braket
dot
id|len1
comma
id|p-&gt;chunks
(braket
id|i
)braket
dot
id|off2
comma
id|p-&gt;chunks
(braket
id|i
)braket
dot
id|len2
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* For debugging only */
DECL|function|print_map
r_static
r_void
id|print_map
c_func
(paren
r_struct
id|commit
op_star
id|cmit
comma
r_struct
id|commit
op_star
id|other
)paren
(brace
r_struct
id|util_info
op_star
id|util
op_assign
id|cmit-&gt;object.util
suffix:semicolon
r_struct
id|util_info
op_star
id|util2
op_assign
id|other-&gt;object.util
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|max
op_assign
id|util-&gt;num_lines
OG
id|util2-&gt;num_lines
ques
c_cond
id|util-&gt;num_lines
suffix:colon
id|util2-&gt;num_lines
suffix:semicolon
r_int
id|num
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;i: %d &quot;
comma
id|i
)paren
suffix:semicolon
id|num
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|util-&gt;num_lines
)paren
(brace
id|num
op_assign
id|util-&gt;line_map
(braket
id|i
)braket
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;t&quot;
comma
id|num
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|util2-&gt;num_lines
)paren
(brace
r_int
id|num2
op_assign
id|util2-&gt;line_map
(braket
id|i
)braket
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;t&quot;
comma
id|num2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
op_ne
l_int|1
op_logical_and
id|num2
op_ne
id|num
)paren
id|printf
c_func
(paren
l_string|&quot;---&quot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// p is a patch from commit to other.
DECL|function|fill_line_map
r_static
r_void
id|fill_line_map
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit
op_star
id|other
comma
r_struct
id|patch
op_star
id|p
)paren
(brace
r_struct
id|util_info
op_star
id|util
op_assign
id|commit-&gt;object.util
suffix:semicolon
r_struct
id|util_info
op_star
id|util2
op_assign
id|other-&gt;object.util
suffix:semicolon
r_int
op_star
id|map
op_assign
id|util-&gt;line_map
suffix:semicolon
r_int
op_star
id|map2
op_assign
id|util2-&gt;line_map
suffix:semicolon
r_int
id|cur_chunk
op_assign
l_int|0
suffix:semicolon
r_int
id|i1
comma
id|i2
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;num
op_logical_and
id|DEBUG
)paren
id|print_patch
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;num lines 1: %d num lines 2: %d&bslash;n&quot;
comma
id|util-&gt;num_lines
comma
id|util2-&gt;num_lines
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i1
op_assign
l_int|0
comma
id|i2
op_assign
l_int|0
suffix:semicolon
id|i1
OL
id|util-&gt;num_lines
suffix:semicolon
id|i1
op_increment
comma
id|i2
op_increment
)paren
(brace
r_struct
id|chunk
op_star
id|chunk
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cur_chunk
OL
id|p-&gt;num
)paren
id|chunk
op_assign
op_amp
id|p-&gt;chunks
(braket
id|cur_chunk
)braket
suffix:semicolon
r_if
c_cond
(paren
id|chunk
op_logical_and
id|chunk-&gt;off1
op_eq
id|i1
)paren
(brace
r_if
c_cond
(paren
id|DEBUG
op_logical_and
id|i2
op_ne
id|chunk-&gt;off2
)paren
id|printf
c_func
(paren
l_string|&quot;i2: %d off2: %d&bslash;n&quot;
comma
id|i2
comma
id|chunk-&gt;off2
)paren
suffix:semicolon
m_assert
(paren
id|i2
op_eq
id|chunk-&gt;off2
)paren
suffix:semicolon
id|i1
op_decrement
suffix:semicolon
id|i2
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;len1
OG
l_int|0
)paren
id|i1
op_add_assign
id|chunk-&gt;len1
suffix:semicolon
r_if
c_cond
(paren
id|chunk-&gt;len2
OG
l_int|0
)paren
id|i2
op_add_assign
id|chunk-&gt;len2
suffix:semicolon
id|cur_chunk
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|i2
op_ge
id|util2-&gt;num_lines
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|map
(braket
id|i1
)braket
op_ne
id|map2
(braket
id|i2
)braket
op_logical_and
id|map
(braket
id|i1
)braket
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;map: i1: %d %d %p i2: %d %d %p&bslash;n&quot;
comma
id|i1
comma
id|map
(braket
id|i1
)braket
comma
id|i1
op_ne
l_int|1
ques
c_cond
id|blame_lines
(braket
id|map
(braket
id|i1
)braket
)braket
suffix:colon
l_int|NULL
comma
id|i2
comma
id|map2
(braket
id|i2
)braket
comma
id|i2
op_ne
l_int|1
ques
c_cond
id|blame_lines
(braket
id|map2
(braket
id|i2
)braket
)braket
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map2
(braket
id|i2
)braket
op_ne
l_int|1
op_logical_and
id|blame_lines
(braket
id|map
(braket
id|i1
)braket
)braket
op_logical_and
op_logical_neg
id|blame_lines
(braket
id|map2
(braket
id|i2
)braket
)braket
)paren
id|map
(braket
id|i1
)braket
op_assign
id|map2
(braket
id|i2
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map
(braket
id|i1
)braket
op_eq
l_int|1
op_logical_and
id|map2
(braket
id|i2
)braket
op_ne
l_int|1
)paren
id|map
(braket
id|i1
)braket
op_assign
id|map2
(braket
id|i2
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DEBUG
OG
l_int|1
)paren
id|printf
c_func
(paren
l_string|&quot;l1: %d l2: %d i1: %d i2: %d&bslash;n&quot;
comma
id|map
(braket
id|i1
)braket
comma
id|map2
(braket
id|i2
)braket
comma
id|i1
comma
id|i2
)paren
suffix:semicolon
)brace
)brace
DECL|function|map_line
r_static
r_int
id|map_line
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
id|line
)paren
(brace
r_struct
id|util_info
op_star
id|info
op_assign
id|commit-&gt;object.util
suffix:semicolon
m_assert
(paren
id|line
op_ge
l_int|0
op_logical_and
id|line
OL
id|info-&gt;num_lines
)paren
suffix:semicolon
r_return
id|info-&gt;line_map
(braket
id|line
)braket
suffix:semicolon
)brace
DECL|function|fill_util_info
r_static
r_int
id|fill_util_info
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|util_info
op_star
id|util
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.util
)paren
r_return
l_int|0
suffix:semicolon
id|util
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|util_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_blob_sha1
c_func
(paren
id|commit-&gt;tree
comma
id|path
comma
id|util-&gt;sha1
)paren
)paren
(brace
id|free
c_func
(paren
id|util
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|util-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|util-&gt;size
op_assign
l_int|0
suffix:semicolon
id|util-&gt;line_map
op_assign
l_int|NULL
suffix:semicolon
id|util-&gt;num_lines
op_assign
l_int|1
suffix:semicolon
id|commit-&gt;object.util
op_assign
id|util
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|alloc_line_map
r_static
r_void
id|alloc_line_map
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|util_info
op_star
id|util
op_assign
id|commit-&gt;object.util
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|util-&gt;line_map
)paren
r_return
suffix:semicolon
id|get_blob
c_func
(paren
id|commit
)paren
suffix:semicolon
id|util-&gt;num_lines
op_assign
l_int|0
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
id|util-&gt;size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|util-&gt;buf
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|util-&gt;num_lines
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|util-&gt;buf
(braket
id|util-&gt;size
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|util-&gt;num_lines
op_increment
suffix:semicolon
)brace
id|util-&gt;line_map
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
id|util-&gt;num_lines
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
id|util-&gt;num_lines
suffix:semicolon
id|i
op_increment
)paren
id|util-&gt;line_map
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|init_first_commit
r_static
r_void
id|init_first_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|util_info
op_star
id|util
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|fill_util_info
c_func
(paren
id|commit
comma
id|filename
)paren
)paren
id|die
c_func
(paren
l_string|&quot;fill_util_info failed&quot;
)paren
suffix:semicolon
id|alloc_line_map
c_func
(paren
id|commit
)paren
suffix:semicolon
id|util
op_assign
id|commit-&gt;object.util
suffix:semicolon
id|num_blame_lines
op_assign
id|util-&gt;num_lines
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
id|num_blame_lines
suffix:semicolon
id|i
op_increment
)paren
id|util-&gt;line_map
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
)brace
DECL|function|process_commits
r_static
r_void
id|process_commits
c_func
(paren
r_struct
id|rev_info
op_star
id|rev
comma
r_const
r_char
op_star
id|path
comma
r_struct
id|commit
op_star
op_star
id|initial
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|util_info
op_star
id|util
suffix:semicolon
r_int
id|lines_left
suffix:semicolon
r_int
op_star
id|blame_p
suffix:semicolon
r_int
op_star
id|new_lines
suffix:semicolon
r_int
id|new_lines_len
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
suffix:semicolon
m_assert
(paren
id|commit
)paren
suffix:semicolon
id|init_first_commit
c_func
(paren
id|commit
comma
id|path
)paren
suffix:semicolon
id|util
op_assign
id|commit-&gt;object.util
suffix:semicolon
id|num_blame_lines
op_assign
id|util-&gt;num_lines
suffix:semicolon
id|blame_lines
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit
op_star
)paren
op_star
id|num_blame_lines
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
id|num_blame_lines
suffix:semicolon
id|i
op_increment
)paren
id|blame_lines
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|lines_left
op_assign
id|num_blame_lines
suffix:semicolon
id|blame_p
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
id|num_blame_lines
)paren
suffix:semicolon
id|new_lines
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
id|num_blame_lines
)paren
suffix:semicolon
r_do
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
id|num_parents
suffix:semicolon
r_struct
id|util_info
op_star
id|util
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;&bslash;nProcessing commit: %d %s&bslash;n&quot;
comma
id|num_commits
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lines_left
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|num_commits
op_increment
suffix:semicolon
id|memset
c_func
(paren
id|blame_p
comma
l_int|0
comma
r_sizeof
(paren
r_int
)paren
op_star
id|num_blame_lines
)paren
suffix:semicolon
id|new_lines_len
op_assign
l_int|0
suffix:semicolon
id|num_parents
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
op_ne
l_int|NULL
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
id|num_parents
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|num_parents
op_eq
l_int|0
)paren
(brace
op_star
id|initial
op_assign
id|commit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fill_util_info
c_func
(paren
id|commit
comma
id|path
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
id|alloc_line_map
c_func
(paren
id|commit
)paren
suffix:semicolon
id|util
op_assign
id|commit-&gt;object.util
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
op_ne
l_int|NULL
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_struct
id|patch
op_star
id|patch
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|parent
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;parse_commit error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;parent: %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|parent-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fill_util_info
c_func
(paren
id|parent
comma
id|path
)paren
)paren
(brace
id|num_parents
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|patch
op_assign
id|get_patch
c_func
(paren
id|parent
comma
id|commit
)paren
suffix:semicolon
id|alloc_line_map
c_func
(paren
id|parent
)paren
suffix:semicolon
id|fill_line_map
c_func
(paren
id|parent
comma
id|commit
comma
id|patch
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
id|patch-&gt;num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|l
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|0
suffix:semicolon
id|l
OL
id|patch-&gt;chunks
(braket
id|i
)braket
dot
id|len2
suffix:semicolon
id|l
op_increment
)paren
(brace
r_int
id|mapped_line
op_assign
id|map_line
c_func
(paren
id|commit
comma
id|patch-&gt;chunks
(braket
id|i
)braket
dot
id|off2
op_plus
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mapped_line
op_ne
l_int|1
)paren
(brace
id|blame_p
(braket
id|mapped_line
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|blame_p
(braket
id|mapped_line
)braket
op_eq
id|num_parents
)paren
id|new_lines
(braket
id|new_lines_len
op_increment
)braket
op_assign
id|mapped_line
suffix:semicolon
)brace
)brace
)brace
id|free_patch
c_func
(paren
id|patch
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;parents: %d&bslash;n&quot;
comma
id|num_parents
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
id|new_lines_len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|mapped_line
op_assign
id|new_lines
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|blame_lines
(braket
id|mapped_line
)braket
op_eq
l_int|NULL
)paren
(brace
id|blame_lines
(braket
id|mapped_line
)braket
op_assign
id|commit
suffix:semicolon
id|lines_left
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG
)paren
id|printf
c_func
(paren
l_string|&quot;blame: mapped: %d i: %d&bslash;n&quot;
comma
id|mapped_line
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
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
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|commit
op_star
id|initial
op_assign
l_int|NULL
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|filename
suffix:semicolon
r_int
id|num_args
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
l_int|10
)braket
suffix:semicolon
r_struct
id|rev_info
id|rev
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
)paren
id|die
c_func
(paren
l_string|&quot;Usage: blame commit-ish file&quot;
)paren
suffix:semicolon
id|filename
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;get_sha1 failed&quot;
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fill_util_info
c_func
(paren
id|commit
comma
id|filename
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s not found in %s&bslash;n&quot;
comma
id|filename
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|num_args
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|num_args
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|args
(braket
id|num_args
op_increment
)braket
op_assign
l_string|&quot;--topo-order&quot;
suffix:semicolon
id|args
(braket
id|num_args
op_increment
)braket
op_assign
l_string|&quot;--remove-empty&quot;
suffix:semicolon
id|args
(braket
id|num_args
op_increment
)braket
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|args
(braket
id|num_args
op_increment
)braket
op_assign
l_string|&quot;--&quot;
suffix:semicolon
id|args
(braket
id|num_args
op_increment
)braket
op_assign
id|filename
suffix:semicolon
id|args
(braket
id|num_args
)braket
op_assign
l_int|NULL
suffix:semicolon
id|setup_revisions
c_func
(paren
id|num_args
comma
id|args
comma
op_amp
id|rev
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
id|process_commits
c_func
(paren
op_amp
id|rev
comma
id|filename
comma
op_amp
id|initial
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
id|num_blame_lines
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|commit
op_star
id|c
op_assign
id|blame_lines
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
id|c
op_assign
id|initial
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d %.8s&bslash;n&quot;
comma
id|i
comma
id|sha1_to_hex
c_func
(paren
id|c-&gt;object.sha1
)paren
)paren
suffix:semicolon
singleline_comment|// printf(&quot;%d %s&bslash;n&quot;, i, find_unique_abbrev(blame_lines[i]-&gt;object.sha1, 6));
)brace
r_if
c_cond
(paren
id|DEBUG
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;num get patch: %d&bslash;n&quot;
comma
id|num_get_patch
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;num commits: %d&bslash;n&quot;
comma
id|num_commits
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;patch time: %f&bslash;n&quot;
comma
id|patch_time
op_div
l_float|1000000.0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;initial: %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|initial-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
