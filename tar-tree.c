multiline_comment|/*&n; * Copyright (c) 2005 Rene Scharfe&n; */
macro_line|#include &lt;time.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|macro|RECORDSIZE
mdefine_line|#define RECORDSIZE&t;(512)
DECL|macro|BLOCKSIZE
mdefine_line|#define BLOCKSIZE&t;(RECORDSIZE * 20)
DECL|macro|TYPEFLAG_AUTO
mdefine_line|#define TYPEFLAG_AUTO&t;&t;&squot;&bslash;0&squot;
DECL|macro|TYPEFLAG_REG
mdefine_line|#define TYPEFLAG_REG&t;&t;&squot;0&squot;
DECL|macro|TYPEFLAG_LNK
mdefine_line|#define TYPEFLAG_LNK&t;&t;&squot;2&squot;
DECL|macro|TYPEFLAG_DIR
mdefine_line|#define TYPEFLAG_DIR&t;&t;&squot;5&squot;
DECL|macro|TYPEFLAG_GLOBAL_HEADER
mdefine_line|#define TYPEFLAG_GLOBAL_HEADER&t;&squot;g&squot;
DECL|macro|TYPEFLAG_EXT_HEADER
mdefine_line|#define TYPEFLAG_EXT_HEADER&t;&squot;x&squot;
DECL|macro|EXT_HEADER_PATH
mdefine_line|#define EXT_HEADER_PATH&t;&t;1
DECL|macro|EXT_HEADER_LINKPATH
mdefine_line|#define EXT_HEADER_LINKPATH&t;2
DECL|variable|tar_tree_usage
r_static
r_const
r_char
id|tar_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-tar-tree &lt;key&gt; [basedir]&quot;
suffix:semicolon
DECL|variable|block
r_static
r_char
id|block
(braket
id|BLOCKSIZE
)braket
suffix:semicolon
DECL|variable|offset
r_static
r_int
r_int
id|offset
suffix:semicolon
DECL|variable|basedir
r_static
r_const
r_char
op_star
id|basedir
suffix:semicolon
DECL|variable|archive_time
r_static
id|time_t
id|archive_time
suffix:semicolon
DECL|struct|path_prefix
r_struct
id|path_prefix
(brace
DECL|member|prev
r_struct
id|path_prefix
op_star
id|prev
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* tries hard to write, either succeeds or dies in the attempt */
DECL|function|reliable_write
r_static
r_void
id|reliable_write
c_func
(paren
r_void
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
id|ret
op_assign
id|xwrite
c_func
(paren
l_int|1
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EPIPE
)paren
m_exit
(paren
l_int|0
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-tar-tree: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|die
c_func
(paren
l_string|&quot;git-tar-tree: disk full?&quot;
)paren
suffix:semicolon
)brace
id|size
op_sub_assign
id|ret
suffix:semicolon
id|buf
op_add_assign
id|ret
suffix:semicolon
)brace
)brace
multiline_comment|/* writes out the whole block, but only if it is full */
DECL|function|write_if_needed
r_static
r_void
id|write_if_needed
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|offset
op_eq
id|BLOCKSIZE
)paren
(brace
id|reliable_write
c_func
(paren
id|block
comma
id|BLOCKSIZE
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* acquire the next record from the buffer; user must call write_if_needed() */
DECL|function|get_record
r_static
r_char
op_star
id|get_record
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|p
op_assign
id|block
op_plus
id|offset
suffix:semicolon
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|RECORDSIZE
)paren
suffix:semicolon
id|offset
op_add_assign
id|RECORDSIZE
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * The end of tar archives is marked by 1024 nul bytes and after that&n; * follows the rest of the block (if any).&n; */
DECL|function|write_trailer
r_static
r_void
id|write_trailer
c_func
(paren
r_void
)paren
(brace
id|get_record
c_func
(paren
)paren
suffix:semicolon
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
id|get_record
c_func
(paren
)paren
suffix:semicolon
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|offset
)paren
(brace
id|get_record
c_func
(paren
)paren
suffix:semicolon
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * queues up writes, so that all our write(2) calls write exactly one&n; * full block; pads writes to RECORDSIZE&n; */
DECL|function|write_blocked
r_static
r_void
id|write_blocked
c_func
(paren
r_void
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|tail
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
r_int
r_int
id|chunk
op_assign
id|BLOCKSIZE
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|chunk
)paren
id|chunk
op_assign
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|block
op_plus
id|offset
comma
id|buf
comma
id|chunk
)paren
suffix:semicolon
id|size
op_sub_assign
id|chunk
suffix:semicolon
id|offset
op_add_assign
id|chunk
suffix:semicolon
id|buf
op_add_assign
id|chunk
suffix:semicolon
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
id|BLOCKSIZE
)paren
(brace
id|reliable_write
c_func
(paren
id|buf
comma
id|BLOCKSIZE
)paren
suffix:semicolon
id|size
op_sub_assign
id|BLOCKSIZE
suffix:semicolon
id|buf
op_add_assign
id|BLOCKSIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
)paren
(brace
id|memcpy
c_func
(paren
id|block
op_plus
id|offset
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|buf
op_add_assign
id|size
suffix:semicolon
id|offset
op_add_assign
id|size
suffix:semicolon
)brace
id|tail
op_assign
id|offset
op_mod
id|RECORDSIZE
suffix:semicolon
r_if
c_cond
(paren
id|tail
)paren
(brace
id|memset
c_func
(paren
id|block
op_plus
id|offset
comma
l_int|0
comma
id|RECORDSIZE
id|tail
)paren
suffix:semicolon
id|offset
op_add_assign
id|RECORDSIZE
id|tail
suffix:semicolon
)brace
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|append_string
r_static
r_void
id|append_string
c_func
(paren
r_char
op_star
op_star
id|p
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_star
id|p
comma
id|s
comma
id|len
)paren
suffix:semicolon
op_star
id|p
op_add_assign
id|len
suffix:semicolon
)brace
DECL|function|append_char
r_static
r_void
id|append_char
c_func
(paren
r_char
op_star
op_star
id|p
comma
r_char
id|c
)paren
(brace
op_star
op_star
id|p
op_assign
id|c
suffix:semicolon
op_star
id|p
op_add_assign
l_int|1
suffix:semicolon
)brace
DECL|function|append_path_prefix
r_static
r_void
id|append_path_prefix
c_func
(paren
r_char
op_star
op_star
id|buffer
comma
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix
)paren
r_return
suffix:semicolon
id|append_path_prefix
c_func
(paren
id|buffer
comma
id|prefix-&gt;prev
)paren
suffix:semicolon
id|append_string
c_func
(paren
id|buffer
comma
id|prefix-&gt;name
)paren
suffix:semicolon
id|append_char
c_func
(paren
id|buffer
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
DECL|function|path_prefix_len
r_static
r_int
r_int
id|path_prefix_len
c_func
(paren
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|path_prefix_len
c_func
(paren
id|prefix-&gt;prev
)paren
op_plus
id|strlen
c_func
(paren
id|prefix-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|append_path
r_static
r_void
id|append_path
c_func
(paren
r_char
op_star
op_star
id|p
comma
r_int
id|is_dir
comma
r_const
r_char
op_star
id|basepath
comma
r_struct
id|path_prefix
op_star
id|prefix
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|basepath
)paren
(brace
id|append_string
c_func
(paren
id|p
comma
id|basepath
)paren
suffix:semicolon
id|append_char
c_func
(paren
id|p
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
id|append_path_prefix
c_func
(paren
id|p
comma
id|prefix
)paren
suffix:semicolon
id|append_string
c_func
(paren
id|p
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_dir
)paren
id|append_char
c_func
(paren
id|p
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
DECL|function|path_len
r_static
r_int
r_int
id|path_len
c_func
(paren
r_int
id|is_dir
comma
r_const
r_char
op_star
id|basepath
comma
r_struct
id|path_prefix
op_star
id|prefix
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|basepath
)paren
id|len
op_add_assign
id|strlen
c_func
(paren
id|basepath
)paren
op_plus
l_int|1
suffix:semicolon
id|len
op_add_assign
id|path_prefix_len
c_func
(paren
id|prefix
)paren
op_plus
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_dir
)paren
id|len
op_increment
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|append_extended_header_prefix
r_static
r_void
id|append_extended_header_prefix
c_func
(paren
r_char
op_star
op_star
id|p
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|keyword
)paren
(brace
r_int
id|len
op_assign
id|sprintf
c_func
(paren
op_star
id|p
comma
l_string|&quot;%u %s=&quot;
comma
id|size
comma
id|keyword
)paren
suffix:semicolon
op_star
id|p
op_add_assign
id|len
suffix:semicolon
)brace
DECL|function|extended_header_len
r_static
r_int
r_int
id|extended_header_len
c_func
(paren
r_const
r_char
op_star
id|keyword
comma
r_int
r_int
id|valuelen
)paren
(brace
multiline_comment|/* &quot;%u %s=%s&bslash;n&quot; */
r_int
r_int
id|len
op_assign
l_int|1
op_plus
l_int|1
op_plus
id|strlen
c_func
(paren
id|keyword
)paren
op_plus
l_int|1
op_plus
id|valuelen
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|9
)paren
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|99
)paren
id|len
op_increment
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|append_extended_header
r_static
r_void
id|append_extended_header
c_func
(paren
r_char
op_star
op_star
id|p
comma
r_const
r_char
op_star
id|keyword
comma
r_const
r_char
op_star
id|value
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|size
op_assign
id|extended_header_len
c_func
(paren
id|keyword
comma
id|len
)paren
suffix:semicolon
id|append_extended_header_prefix
c_func
(paren
id|p
comma
id|size
comma
id|keyword
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_star
id|p
comma
id|value
comma
id|len
)paren
suffix:semicolon
op_star
id|p
op_add_assign
id|len
suffix:semicolon
id|append_char
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_static
r_void
id|write_header
c_func
(paren
r_const
r_int
r_char
op_star
comma
r_char
comma
r_const
r_char
op_star
comma
r_struct
id|path_prefix
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* stores a pax extended header directly in the block buffer */
DECL|function|write_extended_header
r_static
r_void
id|write_extended_header
c_func
(paren
r_const
r_char
op_star
id|headerfilename
comma
r_int
id|is_dir
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|basepath
comma
r_struct
id|path_prefix
op_star
id|prefix
comma
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|namelen
comma
r_void
op_star
id|content
comma
r_int
r_int
id|contentsize
)paren
(brace
r_char
op_star
id|buffer
comma
op_star
id|p
suffix:semicolon
r_int
r_int
id|pathlen
comma
id|size
comma
id|linkpathlen
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
id|pathlen
op_assign
id|extended_header_len
c_func
(paren
l_string|&quot;path&quot;
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT_HEADER_LINKPATH
)paren
(brace
id|linkpathlen
op_assign
id|extended_header_len
c_func
(paren
l_string|&quot;linkpath&quot;
comma
id|contentsize
)paren
suffix:semicolon
id|size
op_add_assign
id|linkpathlen
suffix:semicolon
)brace
id|write_header
c_func
(paren
l_int|NULL
comma
id|TYPEFLAG_EXT_HEADER
comma
l_int|NULL
comma
l_int|NULL
comma
id|headerfilename
comma
l_int|0100600
comma
l_int|NULL
comma
id|size
)paren
suffix:semicolon
id|buffer
op_assign
id|p
op_assign
id|malloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
id|die
c_func
(paren
l_string|&quot;git-tar-tree: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|append_extended_header_prefix
c_func
(paren
op_amp
id|p
comma
id|pathlen
comma
l_string|&quot;path&quot;
)paren
suffix:semicolon
id|append_path
c_func
(paren
op_amp
id|p
comma
id|is_dir
comma
id|basepath
comma
id|prefix
comma
id|path
)paren
suffix:semicolon
id|append_char
c_func
(paren
op_amp
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|EXT_HEADER_LINKPATH
)paren
id|append_extended_header
c_func
(paren
op_amp
id|p
comma
l_string|&quot;linkpath&quot;
comma
id|content
comma
id|contentsize
)paren
suffix:semicolon
id|write_blocked
c_func
(paren
id|buffer
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|write_global_extended_header
r_static
r_void
id|write_global_extended_header
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
id|extended_header_len
c_func
(paren
l_string|&quot;comment&quot;
comma
l_int|40
)paren
suffix:semicolon
id|write_header
c_func
(paren
l_int|NULL
comma
id|TYPEFLAG_GLOBAL_HEADER
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;pax_global_header&quot;
comma
l_int|0100600
comma
l_int|NULL
comma
id|size
)paren
suffix:semicolon
id|p
op_assign
id|get_record
c_func
(paren
)paren
suffix:semicolon
id|append_extended_header
c_func
(paren
op_amp
id|p
comma
l_string|&quot;comment&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* stores a ustar header directly in the block buffer */
DECL|function|write_header
r_static
r_void
id|write_header
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_char
id|typeflag
comma
r_const
r_char
op_star
id|basepath
comma
r_struct
id|path_prefix
op_star
id|prefix
comma
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|mode
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|namelen
suffix:semicolon
r_char
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|checksum
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|ext_header
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|typeflag
op_eq
id|TYPEFLAG_AUTO
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
id|typeflag
op_assign
id|TYPEFLAG_DIR
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|typeflag
op_assign
id|TYPEFLAG_LNK
suffix:semicolon
r_else
id|typeflag
op_assign
id|TYPEFLAG_REG
suffix:semicolon
)brace
id|namelen
op_assign
id|path_len
c_func
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
comma
id|basepath
comma
id|prefix
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
l_int|100
)paren
id|ext_header
op_or_assign
id|EXT_HEADER_PATH
suffix:semicolon
r_if
c_cond
(paren
id|typeflag
op_eq
id|TYPEFLAG_LNK
op_logical_and
id|size
OG
l_int|100
)paren
id|ext_header
op_or_assign
id|EXT_HEADER_LINKPATH
suffix:semicolon
multiline_comment|/* the extended header must be written before the normal one */
r_if
c_cond
(paren
id|ext_header
)paren
(brace
r_char
id|headerfilename
(braket
l_int|51
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|headerfilename
comma
l_string|&quot;%s.paxheader&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|write_extended_header
c_func
(paren
id|headerfilename
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
comma
id|ext_header
comma
id|basepath
comma
id|prefix
comma
id|path
comma
id|namelen
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
id|header
op_assign
id|get_record
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ext_header
)paren
(brace
id|sprintf
c_func
(paren
id|header
comma
l_string|&quot;%s.data&quot;
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
r_char
op_star
id|p
op_assign
id|header
suffix:semicolon
id|append_path
c_func
(paren
op_amp
id|p
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
comma
id|basepath
comma
id|prefix
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|typeflag
op_eq
id|TYPEFLAG_LNK
)paren
(brace
r_if
c_cond
(paren
id|ext_header
op_amp
id|EXT_HEADER_LINKPATH
)paren
(brace
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|157
)braket
comma
l_string|&quot;see %s.paxheader&quot;
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
r_if
c_cond
(paren
id|buffer
)paren
id|strncpy
c_func
(paren
op_amp
id|header
(braket
l_int|157
)braket
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
l_int|0777
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
(paren
id|mode
op_amp
l_int|0100
)paren
ques
c_cond
l_int|0777
suffix:colon
l_int|0666
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
l_int|0777
suffix:semicolon
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|100
)braket
comma
l_string|&quot;%07o&quot;
comma
id|mode
op_amp
l_int|07777
)paren
suffix:semicolon
multiline_comment|/* XXX: should we provide more meaningful info here? */
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|108
)braket
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* uid */
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|116
)braket
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* gid */
id|strncpy
c_func
(paren
op_amp
id|header
(braket
l_int|265
)braket
comma
l_string|&quot;git&quot;
comma
l_int|31
)paren
suffix:semicolon
multiline_comment|/* uname */
id|strncpy
c_func
(paren
op_amp
id|header
(braket
l_int|297
)braket
comma
l_string|&quot;git&quot;
comma
l_int|31
)paren
suffix:semicolon
multiline_comment|/* gname */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
id|size
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|124
)braket
comma
l_string|&quot;%011lo&quot;
comma
id|size
)paren
suffix:semicolon
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|136
)braket
comma
l_string|&quot;%011lo&quot;
comma
id|archive_time
)paren
suffix:semicolon
id|header
(braket
l_int|156
)braket
op_assign
id|typeflag
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|header
(braket
l_int|257
)braket
comma
l_string|&quot;ustar&quot;
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|header
(braket
l_int|263
)braket
comma
l_string|&quot;00&quot;
comma
l_int|2
)paren
suffix:semicolon
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|329
)braket
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* devmajor */
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|337
)braket
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* devminor */
id|memset
c_func
(paren
op_amp
id|header
(braket
l_int|148
)braket
comma
l_char|&squot; &squot;
comma
l_int|8
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
id|RECORDSIZE
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
id|header
(braket
id|i
)braket
suffix:semicolon
id|sprintf
c_func
(paren
op_amp
id|header
(braket
l_int|148
)braket
comma
l_string|&quot;%07o&quot;
comma
id|checksum
op_amp
l_int|0x1fffff
)paren
suffix:semicolon
id|write_if_needed
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|traverse_tree
r_static
r_void
id|traverse_tree
c_func
(paren
r_struct
id|tree_desc
op_star
id|tree
comma
r_struct
id|path_prefix
op_star
id|prefix
)paren
(brace
r_struct
id|path_prefix
id|this_prefix
suffix:semicolon
id|this_prefix.prev
op_assign
id|prefix
suffix:semicolon
r_while
c_loop
(paren
id|tree-&gt;size
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_void
op_star
id|eltbuf
suffix:semicolon
r_char
id|elttype
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|eltsize
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
id|tree
comma
op_amp
id|name
comma
op_amp
id|mode
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
id|tree
)paren
suffix:semicolon
id|eltbuf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|elttype
comma
op_amp
id|eltsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eltbuf
)paren
id|die
c_func
(paren
l_string|&quot;cannot read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|write_header
c_func
(paren
id|sha1
comma
id|TYPEFLAG_AUTO
comma
id|basedir
comma
id|prefix
comma
id|name
comma
id|mode
comma
id|eltbuf
comma
id|eltsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_struct
id|tree_desc
id|subtree
suffix:semicolon
id|subtree.buf
op_assign
id|eltbuf
suffix:semicolon
id|subtree.size
op_assign
id|eltsize
suffix:semicolon
id|this_prefix.name
op_assign
id|name
suffix:semicolon
id|traverse_tree
c_func
(paren
op_amp
id|subtree
comma
op_amp
id|this_prefix
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|S_ISLNK
c_func
(paren
id|mode
)paren
)paren
(brace
id|write_blocked
c_func
(paren
id|eltbuf
comma
id|eltsize
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|eltbuf
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|tree_desc
id|tree
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_case
l_int|3
suffix:colon
id|basedir
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* FALLTHROUGH */
r_case
l_int|2
suffix:colon
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
OL
l_int|0
)paren
id|usage
c_func
(paren
id|tar_tree_usage
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
id|tar_tree_usage
)paren
suffix:semicolon
)brace
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit
)paren
(brace
id|write_global_extended_header
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
id|archive_time
op_assign
id|commit-&gt;date
suffix:semicolon
)brace
id|tree.buf
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
l_string|&quot;tree&quot;
comma
op_amp
id|tree.size
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree.buf
)paren
id|die
c_func
(paren
l_string|&quot;not a reference to a tag, commit or tree object: %s&quot;
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
op_logical_neg
id|archive_time
)paren
id|archive_time
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|basedir
)paren
id|write_header
c_func
(paren
(paren
r_int
r_char
op_star
)paren
l_string|&quot;0&quot;
comma
id|TYPEFLAG_DIR
comma
l_int|NULL
comma
l_int|NULL
comma
id|basedir
comma
l_int|040777
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|traverse_tree
c_func
(paren
op_amp
id|tree
comma
l_int|NULL
)paren
suffix:semicolon
id|write_trailer
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
