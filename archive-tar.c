multiline_comment|/*&n; * Copyright (c) 2005, 2006 Rene Scharfe&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tar.h&quot;
macro_line|#include &quot;archive.h&quot;
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
op_assign
id|STRBUF_INIT
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
l_string|&quot;root&quot;
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
l_string|&quot;root&quot;
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
id|err
op_assign
id|write_tar_entry
c_func
(paren
id|args
comma
id|sha1
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
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
r_return
id|err
suffix:semicolon
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
r_int
id|err
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
id|err
op_assign
id|write_tar_entry
c_func
(paren
id|args
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
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
l_int|0
suffix:semicolon
)brace
DECL|function|write_tar_archive
r_static
r_int
id|write_tar_archive
c_func
(paren
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
l_int|0
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
id|register_archiver
c_func
(paren
op_amp
id|tar_archiver
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
)brace
eof
