multiline_comment|/*&n; * Copyright (c) 2005, 2006 Rene Scharfe&n; */
macro_line|#include &lt;time.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;tar.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
DECL|macro|RECORDSIZE
mdefine_line|#define RECORDSIZE&t;(512)
DECL|macro|BLOCKSIZE
mdefine_line|#define BLOCKSIZE&t;(RECORDSIZE * 20)
DECL|variable|tar_tree_usage
r_static
r_const
r_char
id|tar_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-tar-tree [--remote=&lt;repo&gt;] &lt;ent&gt; [basedir]&quot;
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
DECL|variable|archive_time
r_static
id|time_t
id|archive_time
suffix:semicolon
DECL|variable|tar_umask
r_static
r_int
id|tar_umask
suffix:semicolon
multiline_comment|/* tries hard to write, either succeeds or dies in the attempt */
DECL|function|reliable_write
r_static
r_void
id|reliable_write
c_func
(paren
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_const
r_char
op_star
id|buf
op_assign
id|data
suffix:semicolon
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
multiline_comment|/*&n; * queues up writes, so that all our write(2) calls write exactly one&n; * full block; pads writes to RECORDSIZE&n; */
DECL|function|write_blocked
r_static
r_void
id|write_blocked
c_func
(paren
r_const
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_const
r_char
op_star
id|buf
op_assign
id|data
suffix:semicolon
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
multiline_comment|/*&n; * The end of tar archives is marked by 2*512 nul bytes and after that&n; * follows the rest of the block (if any).&n; */
DECL|function|write_trailer
r_static
r_void
id|write_trailer
c_func
(paren
r_void
)paren
(brace
r_int
id|tail
op_assign
id|BLOCKSIZE
id|offset
suffix:semicolon
id|memset
c_func
(paren
id|block
op_plus
id|offset
comma
l_int|0
comma
id|tail
)paren
suffix:semicolon
id|reliable_write
c_func
(paren
id|block
comma
id|BLOCKSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tail
OL
l_int|2
op_star
id|RECORDSIZE
)paren
(brace
id|memset
c_func
(paren
id|block
comma
l_int|0
comma
id|offset
)paren
suffix:semicolon
id|reliable_write
c_func
(paren
id|block
comma
id|BLOCKSIZE
)paren
suffix:semicolon
)brace
)brace
DECL|function|strbuf_append_string
r_static
r_void
id|strbuf_append_string
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
id|s
)paren
(brace
r_int
id|slen
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|total
op_assign
id|sb-&gt;len
op_plus
id|slen
suffix:semicolon
r_if
c_cond
(paren
id|total
OG
id|sb-&gt;alloc
)paren
(brace
id|sb-&gt;buf
op_assign
id|xrealloc
c_func
(paren
id|sb-&gt;buf
comma
id|total
)paren
suffix:semicolon
id|sb-&gt;alloc
op_assign
id|total
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|sb-&gt;buf
op_plus
id|sb-&gt;len
comma
id|s
comma
id|slen
)paren
suffix:semicolon
id|sb-&gt;len
op_assign
id|total
suffix:semicolon
)brace
multiline_comment|/*&n; * pax extended header records have the format &quot;%u %s=%s&bslash;n&quot;.  %u contains&n; * the size of the whole string (including the %u), the first %s is the&n; * keyword, the second one is the value.  This function constructs such a&n; * string and appends it to a struct strbuf.&n; */
DECL|function|strbuf_append_ext_header
r_static
r_void
id|strbuf_append_ext_header
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
id|keyword
comma
r_const
r_char
op_star
id|value
comma
r_int
r_int
id|valuelen
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
id|len
comma
id|total
comma
id|tmp
suffix:semicolon
multiline_comment|/* &quot;%u %s=%s&bslash;n&quot; */
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
r_for
c_loop
(paren
id|tmp
op_assign
id|len
suffix:semicolon
id|tmp
OG
l_int|9
suffix:semicolon
id|tmp
op_div_assign
l_int|10
)paren
id|len
op_increment
suffix:semicolon
id|total
op_assign
id|sb-&gt;len
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|total
OG
id|sb-&gt;alloc
)paren
(brace
id|sb-&gt;buf
op_assign
id|xrealloc
c_func
(paren
id|sb-&gt;buf
comma
id|total
)paren
suffix:semicolon
id|sb-&gt;alloc
op_assign
id|total
suffix:semicolon
)brace
id|p
op_assign
id|sb-&gt;buf
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%u %s=&quot;
comma
id|len
comma
id|keyword
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|value
comma
id|valuelen
)paren
suffix:semicolon
id|p
op_add_assign
id|valuelen
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|sb-&gt;len
op_assign
id|total
suffix:semicolon
)brace
DECL|function|ustar_header_chksum
r_static
r_int
r_int
id|ustar_header_chksum
c_func
(paren
r_const
r_struct
id|ustar_header
op_star
id|header
)paren
(brace
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|header
suffix:semicolon
r_int
r_int
id|chksum
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|header-&gt;chksum
)paren
id|chksum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
id|chksum
op_add_assign
r_sizeof
(paren
id|header-&gt;chksum
)paren
op_star
l_char|&squot; &squot;
suffix:semicolon
id|p
op_add_assign
r_sizeof
(paren
id|header-&gt;chksum
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
(paren
r_char
op_star
)paren
id|header
op_plus
r_sizeof
(paren
r_struct
id|ustar_header
)paren
)paren
id|chksum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
r_return
id|chksum
suffix:semicolon
)brace
DECL|function|get_path_prefix
r_static
r_int
id|get_path_prefix
c_func
(paren
r_const
r_struct
id|strbuf
op_star
id|path
comma
r_int
id|maxlen
)paren
(brace
r_int
id|i
op_assign
id|path-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|maxlen
)paren
id|i
op_assign
id|maxlen
suffix:semicolon
r_do
(brace
id|i
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OG
l_int|0
op_logical_and
id|path-&gt;buf
(braket
id|i
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|write_entry
r_static
r_void
id|write_entry
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|strbuf
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
r_struct
id|ustar_header
id|header
suffix:semicolon
r_struct
id|strbuf
id|ext_header
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|header
comma
l_int|0
comma
r_sizeof
(paren
id|header
)paren
)paren
suffix:semicolon
id|ext_header.buf
op_assign
l_int|NULL
suffix:semicolon
id|ext_header.len
op_assign
id|ext_header.alloc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sha1
)paren
(brace
op_star
id|header.typeflag
op_assign
id|TYPEFLAG_GLOBAL_HEADER
suffix:semicolon
id|mode
op_assign
l_int|0100666
suffix:semicolon
id|strcpy
c_func
(paren
id|header.name
comma
l_string|&quot;pax_global_header&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
(brace
op_star
id|header.typeflag
op_assign
id|TYPEFLAG_EXT_HEADER
suffix:semicolon
id|mode
op_assign
l_int|0100666
suffix:semicolon
id|sprintf
c_func
(paren
id|header.name
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
)brace
r_else
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
(brace
op_star
id|header.typeflag
op_assign
id|TYPEFLAG_DIR
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_or
l_int|0777
)paren
op_amp
op_complement
id|tar_umask
suffix:semicolon
)brace
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
(brace
op_star
id|header.typeflag
op_assign
id|TYPEFLAG_LNK
suffix:semicolon
id|mode
op_or_assign
l_int|0777
suffix:semicolon
)brace
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
(brace
op_star
id|header.typeflag
op_assign
id|TYPEFLAG_REG
suffix:semicolon
id|mode
op_assign
(paren
id|mode
op_or
(paren
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
)paren
)paren
op_amp
op_complement
id|tar_umask
suffix:semicolon
)brace
r_else
(brace
id|error
c_func
(paren
l_string|&quot;unsupported file mode: 0%o (SHA1: %s)&quot;
comma
id|mode
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path-&gt;len
OG
r_sizeof
(paren
id|header.name
)paren
)paren
(brace
r_int
id|plen
op_assign
id|get_path_prefix
c_func
(paren
id|path
comma
r_sizeof
(paren
id|header.prefix
)paren
)paren
suffix:semicolon
r_int
id|rest
op_assign
id|path-&gt;len
id|plen
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|plen
OG
l_int|0
op_logical_and
id|rest
op_le
r_sizeof
(paren
id|header.name
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|header.prefix
comma
id|path-&gt;buf
comma
id|plen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header.name
comma
id|path-&gt;buf
op_plus
id|plen
op_plus
l_int|1
comma
id|rest
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
c_func
(paren
id|header.name
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
id|strbuf_append_ext_header
c_func
(paren
op_amp
id|ext_header
comma
l_string|&quot;path&quot;
comma
id|path-&gt;buf
comma
id|path-&gt;len
)paren
suffix:semicolon
)brace
)brace
r_else
id|memcpy
c_func
(paren
id|header.name
comma
id|path-&gt;buf
comma
id|path-&gt;len
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|mode
)paren
op_logical_and
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|size
OG
r_sizeof
(paren
id|header.linkname
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|header.linkname
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
id|strbuf_append_ext_header
c_func
(paren
op_amp
id|ext_header
comma
l_string|&quot;linkpath&quot;
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|header.linkname
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|header.mode
comma
l_string|&quot;%07o&quot;
comma
id|mode
op_amp
l_int|07777
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header.size
comma
l_string|&quot;%011lo&quot;
comma
id|S_ISREG
c_func
(paren
id|mode
)paren
ques
c_cond
id|size
suffix:colon
l_int|0
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header.mtime
comma
l_string|&quot;%011lo&quot;
comma
id|archive_time
)paren
suffix:semicolon
multiline_comment|/* XXX: should we provide more meaningful info here? */
id|sprintf
c_func
(paren
id|header.uid
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header.gid
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|header.uname
comma
l_string|&quot;git&quot;
comma
r_sizeof
(paren
id|header.uname
)paren
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|header.gname
comma
l_string|&quot;git&quot;
comma
r_sizeof
(paren
id|header.gname
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header.devmajor
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header.devminor
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header.magic
comma
l_string|&quot;ustar&quot;
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header.version
comma
l_string|&quot;00&quot;
comma
l_int|2
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header.chksum
comma
l_string|&quot;%07o&quot;
comma
id|ustar_header_chksum
c_func
(paren
op_amp
id|header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ext_header.len
OG
l_int|0
)paren
(brace
id|write_entry
c_func
(paren
id|sha1
comma
l_int|NULL
comma
l_int|0
comma
id|ext_header.buf
comma
id|ext_header.len
)paren
suffix:semicolon
id|free
c_func
(paren
id|ext_header.buf
)paren
suffix:semicolon
)brace
id|write_blocked
c_func
(paren
op_amp
id|header
comma
r_sizeof
(paren
id|header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
op_logical_and
id|buffer
op_logical_and
id|size
OG
l_int|0
)paren
id|write_blocked
c_func
(paren
id|buffer
comma
id|size
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
r_struct
id|strbuf
id|ext_header
suffix:semicolon
id|ext_header.buf
op_assign
l_int|NULL
suffix:semicolon
id|ext_header.len
op_assign
id|ext_header.alloc
op_assign
l_int|0
suffix:semicolon
id|strbuf_append_ext_header
c_func
(paren
op_amp
id|ext_header
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
id|write_entry
c_func
(paren
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
id|ext_header.buf
comma
id|ext_header.len
)paren
suffix:semicolon
id|free
c_func
(paren
id|ext_header.buf
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
id|strbuf
op_star
id|path
)paren
(brace
r_int
id|pathlen
op_assign
id|path-&gt;len
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_while
c_loop
(paren
id|tree_entry
c_func
(paren
id|tree
comma
op_amp
id|entry
)paren
)paren
(brace
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
id|eltbuf
op_assign
id|read_sha1_file
c_func
(paren
id|entry.sha1
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
id|entry.sha1
)paren
)paren
suffix:semicolon
id|path-&gt;len
op_assign
id|pathlen
suffix:semicolon
id|strbuf_append_string
c_func
(paren
id|path
comma
id|entry.path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|strbuf_append_string
c_func
(paren
id|path
comma
l_string|&quot;/&quot;
)paren
suffix:semicolon
id|write_entry
c_func
(paren
id|entry.sha1
comma
id|path
comma
id|entry.mode
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
id|entry.mode
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
id|traverse_tree
c_func
(paren
op_amp
id|subtree
comma
id|path
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
DECL|function|git_tar_config
r_int
id|git_tar_config
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;tar.umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;user&quot;
)paren
)paren
(brace
id|tar_umask
op_assign
id|umask
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|umask
c_func
(paren
id|tar_umask
)paren
suffix:semicolon
)brace
r_else
(brace
id|tar_umask
op_assign
id|git_config_int
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|generate_tar
r_static
r_int
id|generate_tar
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
r_char
op_star
op_star
id|envp
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|tree_sha1
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
r_struct
id|strbuf
id|current_path
suffix:semicolon
id|current_path.buf
op_assign
id|xmalloc
c_func
(paren
id|PATH_MAX
)paren
suffix:semicolon
id|current_path.alloc
op_assign
id|PATH_MAX
suffix:semicolon
id|current_path.len
op_assign
id|current_path.eof
op_assign
l_int|0
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_tar_config
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
id|strbuf_append_string
c_func
(paren
op_amp
id|current_path
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|strbuf_append_string
c_func
(paren
op_amp
id|current_path
comma
l_string|&quot;/&quot;
)paren
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
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|1
)braket
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
r_else
id|archive_time
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|tree.buf
op_assign
id|read_object_with_reference
c_func
(paren
id|sha1
comma
id|tree_type
comma
op_amp
id|tree.size
comma
id|tree_sha1
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
id|current_path.len
OG
l_int|0
)paren
id|write_entry
c_func
(paren
id|tree_sha1
comma
op_amp
id|current_path
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
op_amp
id|current_path
)paren
suffix:semicolon
id|write_trailer
c_func
(paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|current_path.buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|exec
r_static
r_const
r_char
op_star
id|exec
op_assign
l_string|&quot;git-upload-tar&quot;
suffix:semicolon
DECL|function|remote_tar
r_static
r_int
id|remote_tar
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
id|fd
(braket
l_int|2
)braket
comma
id|ret
comma
id|len
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|3
op_logical_or
l_int|4
OL
id|argc
)paren
id|usage
c_func
(paren
id|tar_tree_usage
)paren
suffix:semicolon
multiline_comment|/* --remote=&lt;repo&gt; */
id|url
op_assign
id|strdup
c_func
(paren
id|argv
(braket
l_int|1
)braket
op_plus
l_int|9
)paren
suffix:semicolon
id|pid
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|url
comma
id|exec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;want %s&bslash;n&quot;
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
id|argv
(braket
l_int|3
)braket
)paren
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;base %s&bslash;n&quot;
comma
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|die
c_func
(paren
l_string|&quot;git-tar-tree: expected ACK/NAK, got EOF&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;ACK&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|5
OL
id|len
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;NACK &quot;
comma
l_int|5
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-tar-tree: NACK %s&quot;
comma
id|buf
op_plus
l_int|5
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-tar-tree: protocol error&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* expect a flush */
id|len
op_assign
id|packet_read_line
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
id|die
c_func
(paren
l_string|&quot;git-tar-tree: expected a flush&quot;
)paren
suffix:semicolon
multiline_comment|/* Now, start reading from fd[0] and spit it out to stdout */
id|ret
op_assign
id|copy_fd
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ret
op_or_assign
id|finish_connect
c_func
(paren
id|pid
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|ret
suffix:semicolon
)brace
DECL|function|cmd_tar_tree
r_int
id|cmd_tar_tree
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
r_char
op_star
op_star
id|envp
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
id|usage
c_func
(paren
id|tar_tree_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;--remote=&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
l_int|9
)paren
)paren
r_return
id|remote_tar
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_return
id|generate_tar
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
)brace
multiline_comment|/* ustar header + extended global header content */
DECL|macro|HEADERSIZE
mdefine_line|#define HEADERSIZE (2 * RECORDSIZE)
DECL|function|cmd_get_tar_commit_id
r_int
id|cmd_get_tar_commit_id
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
r_char
op_star
op_star
id|envp
)paren
(brace
r_char
id|buffer
(braket
id|HEADERSIZE
)braket
suffix:semicolon
r_struct
id|ustar_header
op_star
id|header
op_assign
(paren
r_struct
id|ustar_header
op_star
)paren
id|buffer
suffix:semicolon
r_char
op_star
id|content
op_assign
id|buffer
op_plus
id|RECORDSIZE
suffix:semicolon
id|ssize_t
id|n
suffix:semicolon
id|n
op_assign
id|xread
c_func
(paren
l_int|0
comma
id|buffer
comma
id|HEADERSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|HEADERSIZE
)paren
id|die
c_func
(paren
l_string|&quot;git-get-tar-commit-id: read error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|header-&gt;typeflag
(braket
l_int|0
)braket
op_ne
l_char|&squot;g&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|content
comma
l_string|&quot;52 comment=&quot;
comma
l_int|11
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|n
op_assign
id|xwrite
c_func
(paren
l_int|1
comma
id|content
op_plus
l_int|11
comma
l_int|41
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|41
)paren
id|die
c_func
(paren
l_string|&quot;git-get-tar-commit-id: write error&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
