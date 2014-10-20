multiline_comment|/*&n; * Copyright (c) 2005, 2006 Rene Scharfe&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tar.h&quot;
macro_line|#include &quot;archive.h&quot;
macro_line|#include &quot;streaming.h&quot;
macro_line|#include &quot;run-command.h&quot;
DECL|macro|RECORDSIZE
mdefine_line|#define RECORDSIZE&t;(512)
DECL|macro|BLOCKSIZE
mdefine_line|#define BLOCKSIZE&t;(RECORDSIZE * 20)
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
DECL|variable|tar_umask
r_static
r_int
id|tar_umask
op_assign
l_int|002
suffix:semicolon
r_static
r_int
id|write_tar_filter_archive
c_func
(paren
r_const
r_struct
id|archiver
op_star
id|ar
comma
r_struct
id|archiver_args
op_star
id|args
)paren
suffix:semicolon
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
id|write_or_die
c_func
(paren
l_int|1
comma
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
DECL|function|do_write_blocked
r_static
r_void
id|do_write_blocked
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
id|write_or_die
c_func
(paren
l_int|1
comma
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
)brace
DECL|function|finish_record
r_static
r_void
id|finish_record
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tail
suffix:semicolon
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
id|do_write_blocked
c_func
(paren
id|data
comma
id|size
)paren
suffix:semicolon
id|finish_record
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
id|write_or_die
c_func
(paren
l_int|1
comma
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
id|write_or_die
c_func
(paren
l_int|1
comma
id|block
comma
id|BLOCKSIZE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * queues up writes, so that all our write(2) calls write exactly one&n; * full block; pads writes to RECORDSIZE&n; */
DECL|function|stream_blocked
r_static
r_int
id|stream_blocked
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
id|git_istream
op_star
id|st
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
r_char
id|buf
(braket
id|BLOCKSIZE
)braket
suffix:semicolon
id|ssize_t
id|readlen
suffix:semicolon
id|st
op_assign
id|open_istream
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|sz
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|st
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot stream blob %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|readlen
op_assign
id|read_istream
c_func
(paren
id|st
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
id|readlen
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|do_write_blocked
c_func
(paren
id|buf
comma
id|readlen
)paren
suffix:semicolon
)brace
id|close_istream
c_func
(paren
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|readlen
)paren
id|finish_record
c_func
(paren
)paren
suffix:semicolon
r_return
id|readlen
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
r_int
id|len
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
id|strbuf_grow
c_func
(paren
id|sb
comma
id|len
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;%u %s=&quot;
comma
id|len
comma
id|keyword
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|value
comma
id|valuelen
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
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
r_const
r_int
r_char
op_star
id|p
op_assign
(paren
r_const
r_int
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
(paren
r_const
r_int
r_char
op_star
)paren
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
r_const
r_int
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
r_char
op_star
id|path
comma
r_int
id|pathlen
comma
r_int
id|maxlen
)paren
(brace
r_int
id|i
op_assign
id|pathlen
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|1
op_logical_and
id|path
(braket
id|i
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|i
op_decrement
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
id|path
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
DECL|function|prepare_header
r_static
r_void
id|prepare_header
c_func
(paren
r_struct
id|archiver_args
op_star
id|args
comma
r_struct
id|ustar_header
op_star
id|header
comma
r_int
r_int
id|mode
comma
r_int
r_int
id|size
)paren
(brace
id|sprintf
c_func
(paren
id|header-&gt;mode
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
id|header-&gt;size
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
id|header-&gt;mtime
comma
l_string|&quot;%011lo&quot;
comma
(paren
r_int
r_int
)paren
id|args-&gt;time
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header-&gt;uid
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header-&gt;gid
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|header-&gt;uname
comma
l_string|&quot;root&quot;
comma
r_sizeof
(paren
id|header-&gt;uname
)paren
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|header-&gt;gname
comma
l_string|&quot;root&quot;
comma
r_sizeof
(paren
id|header-&gt;gname
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header-&gt;devmajor
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header-&gt;devminor
comma
l_string|&quot;%07o&quot;
comma
l_int|0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header-&gt;magic
comma
l_string|&quot;ustar&quot;
comma
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header-&gt;version
comma
l_string|&quot;00&quot;
comma
l_int|2
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|header-&gt;chksum
comma
l_string|&quot;%07o&quot;
comma
id|ustar_header_chksum
c_func
(paren
id|header
)paren
)paren
suffix:semicolon
)brace
DECL|function|write_extended_header
r_static
r_int
id|write_extended_header
c_func
(paren
r_struct
id|archiver_args
op_star
id|args
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
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
r_int
r_int
id|mode
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
id|prepare_header
c_func
(paren
id|args
comma
op_amp
id|header
comma
id|mode
comma
id|size
)paren
suffix:semicolon
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
id|write_blocked
c_func
(paren
id|buffer
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_tar_entry
r_static
r_int
id|write_tar_entry
c_func
(paren
r_struct
id|archiver_args
op_star
id|args
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
id|path
comma
r_int
id|pathlen
comma
r_int
r_int
id|mode
)paren
(brace
r_struct
id|ustar_header
id|header
suffix:semicolon
r_struct
id|strbuf
id|ext_header
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
r_int
id|old_mode
op_assign
id|mode
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
id|err
op_assign
l_int|0
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
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_logical_or
id|S_ISGITLINK
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
r_return
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
)brace
r_if
c_cond
(paren
id|pathlen
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
id|pathlen
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
id|pathlen
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
id|path
comma
id|plen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|header.name
comma
id|path
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
id|path
comma
id|pathlen
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
id|path
comma
id|pathlen
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
op_logical_neg
id|args-&gt;convert
op_logical_and
id|sha1_object_info
c_func
(paren
id|sha1
comma
op_amp
id|size
)paren
op_eq
id|OBJ_BLOB
op_logical_and
id|size
OG
id|big_file_threshold
)paren
id|buffer
op_assign
l_int|NULL
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
op_logical_or
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
id|buffer
op_assign
id|sha1_file_to_archive
c_func
(paren
id|args
comma
id|path
comma
id|sha1
comma
id|old_mode
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
id|buffer
)paren
r_return
id|error
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
)brace
r_else
(brace
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|size
op_assign
l_int|0
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
id|prepare_header
c_func
(paren
id|args
comma
op_amp
id|header
comma
id|mode
comma
id|size
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
id|err
op_assign
id|write_extended_header
c_func
(paren
id|args
comma
id|sha1
comma
id|ext_header.buf
comma
id|ext_header.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|ext_header
)paren
suffix:semicolon
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
id|size
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buffer
)paren
id|write_blocked
c_func
(paren
id|buffer
comma
id|size
)paren
suffix:semicolon
r_else
id|err
op_assign
id|stream_blocked
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|write_global_extended_header
r_static
r_int
id|write_global_extended_header
c_func
(paren
r_struct
id|archiver_args
op_star
id|args
)paren
(brace
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|args-&gt;commit_sha1
suffix:semicolon
r_struct
id|strbuf
id|ext_header
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|ustar_header
id|header
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_int
id|err
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
id|prepare_header
c_func
(paren
id|args
comma
op_amp
id|header
comma
id|mode
comma
id|ext_header.len
)paren
suffix:semicolon
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
id|write_blocked
c_func
(paren
id|ext_header.buf
comma
id|ext_header.len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|ext_header
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|tar_filters
r_static
r_struct
id|archiver
op_star
op_star
id|tar_filters
suffix:semicolon
DECL|variable|nr_tar_filters
r_static
r_int
id|nr_tar_filters
suffix:semicolon
DECL|variable|alloc_tar_filters
r_static
r_int
id|alloc_tar_filters
suffix:semicolon
DECL|function|find_tar_filter
r_static
r_struct
id|archiver
op_star
id|find_tar_filter
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
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
id|nr_tar_filters
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|archiver
op_star
id|ar
op_assign
id|tar_filters
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|ar-&gt;name
comma
id|name
comma
id|len
)paren
op_logical_and
op_logical_neg
id|ar-&gt;name
(braket
id|len
)braket
)paren
r_return
id|ar
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|tar_filter_config
r_static
r_int
id|tar_filter_config
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
id|data
)paren
(brace
r_struct
id|archiver
op_star
id|ar
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_const
r_char
op_star
id|type
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_if
c_cond
(paren
id|parse_config_key
c_func
(paren
id|var
comma
l_string|&quot;tar&quot;
comma
op_amp
id|name
comma
op_amp
id|namelen
comma
op_amp
id|type
)paren
OL
l_int|0
op_logical_or
op_logical_neg
id|name
)paren
r_return
l_int|0
suffix:semicolon
id|ar
op_assign
id|find_tar_filter
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ar
)paren
(brace
id|ar
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ar
)paren
)paren
suffix:semicolon
id|ar-&gt;name
op_assign
id|xmemdupz
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
id|ar-&gt;write_archive
op_assign
id|write_tar_filter_archive
suffix:semicolon
id|ar-&gt;flags
op_assign
id|ARCHIVER_WANT_COMPRESSION_LEVELS
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|tar_filters
comma
id|nr_tar_filters
op_plus
l_int|1
comma
id|alloc_tar_filters
)paren
suffix:semicolon
id|tar_filters
(braket
id|nr_tar_filters
op_increment
)braket
op_assign
id|ar
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;command&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|free
c_func
(paren
id|ar-&gt;data
)paren
suffix:semicolon
id|ar-&gt;data
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;remote&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
)paren
id|ar-&gt;flags
op_or_assign
id|ARCHIVER_REMOTE
suffix:semicolon
r_else
id|ar-&gt;flags
op_and_assign
op_complement
id|ARCHIVER_REMOTE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_tar_config
r_static
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
comma
r_void
op_star
id|cb
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
id|value
op_logical_and
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
id|tar_filter_config
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
DECL|function|write_tar_archive
r_static
r_int
id|write_tar_archive
c_func
(paren
r_const
r_struct
id|archiver
op_star
id|ar
comma
r_struct
id|archiver_args
op_star
id|args
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;commit_sha1
)paren
id|err
op_assign
id|write_global_extended_header
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|write_archive_entries
c_func
(paren
id|args
comma
id|write_tar_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|write_trailer
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|write_tar_filter_archive
r_static
r_int
id|write_tar_filter_archive
c_func
(paren
r_const
r_struct
id|archiver
op_star
id|ar
comma
r_struct
id|archiver_args
op_star
id|args
)paren
(brace
r_struct
id|strbuf
id|cmd
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|child_process
id|filter
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ar-&gt;data
)paren
id|die
c_func
(paren
l_string|&quot;BUG: tar-filter archiver called with no filter defined&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|cmd
comma
id|ar-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;compression_level
op_ge
l_int|0
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|cmd
comma
l_string|&quot; -%d&quot;
comma
id|args-&gt;compression_level
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|cmd.buf
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|filter.argv
op_assign
id|argv
suffix:semicolon
id|filter.use_shell
op_assign
l_int|1
suffix:semicolon
id|filter.in
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|filter
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to start &squot;%s&squot; filter&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dup2
c_func
(paren
id|filter.in
comma
l_int|1
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to redirect descriptor&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|filter.in
)paren
suffix:semicolon
id|r
op_assign
id|write_tar_archive
c_func
(paren
id|ar
comma
id|args
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|filter
)paren
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; filter reported error&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|variable|tar_archiver
r_static
r_struct
id|archiver
id|tar_archiver
op_assign
(brace
l_string|&quot;tar&quot;
comma
id|write_tar_archive
comma
id|ARCHIVER_REMOTE
)brace
suffix:semicolon
DECL|function|init_tar_archiver
r_void
id|init_tar_archiver
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|register_archiver
c_func
(paren
op_amp
id|tar_archiver
)paren
suffix:semicolon
id|tar_filter_config
c_func
(paren
l_string|&quot;tar.tgz.command&quot;
comma
l_string|&quot;gzip -cn&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|tar_filter_config
c_func
(paren
l_string|&quot;tar.tgz.remote&quot;
comma
l_string|&quot;true&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|tar_filter_config
c_func
(paren
l_string|&quot;tar.tar.gz.command&quot;
comma
l_string|&quot;gzip -cn&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|tar_filter_config
c_func
(paren
l_string|&quot;tar.tar.gz.remote&quot;
comma
l_string|&quot;true&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_tar_config
comma
l_int|NULL
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
id|nr_tar_filters
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* omit any filters that never had a command configured */
r_if
c_cond
(paren
id|tar_filters
(braket
id|i
)braket
op_member_access_from_pointer
id|data
)paren
id|register_archiver
c_func
(paren
id|tar_filters
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
eof
