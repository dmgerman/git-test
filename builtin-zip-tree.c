multiline_comment|/*&n; * Copyright (c) 2006 Rene Scharfe&n; */
macro_line|#include &lt;time.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;archive.h&quot;
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|variable|zip_date
r_static
r_int
id|zip_date
suffix:semicolon
DECL|variable|zip_time
r_static
r_int
id|zip_time
suffix:semicolon
DECL|variable|zip_dir
r_static
r_int
r_char
op_star
id|zip_dir
suffix:semicolon
DECL|variable|zip_dir_size
r_static
r_int
r_int
id|zip_dir_size
suffix:semicolon
DECL|variable|zip_offset
r_static
r_int
r_int
id|zip_offset
suffix:semicolon
DECL|variable|zip_dir_offset
r_static
r_int
r_int
id|zip_dir_offset
suffix:semicolon
DECL|variable|zip_dir_entries
r_static
r_int
r_int
id|zip_dir_entries
suffix:semicolon
DECL|macro|ZIP_DIRECTORY_MIN_SIZE
mdefine_line|#define ZIP_DIRECTORY_MIN_SIZE&t;(1024 * 1024)
DECL|struct|zip_local_header
r_struct
id|zip_local_header
(brace
DECL|member|magic
r_int
r_char
id|magic
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|version
r_int
r_char
id|version
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|compression_method
r_int
r_char
id|compression_method
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mtime
r_int
r_char
id|mtime
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mdate
r_int
r_char
id|mdate
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|crc32
r_int
r_char
id|crc32
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|compressed_size
r_int
r_char
id|compressed_size
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|size
r_int
r_char
id|size
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|filename_length
r_int
r_char
id|filename_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|extra_length
r_int
r_char
id|extra_length
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zip_dir_header
r_struct
id|zip_dir_header
(brace
DECL|member|magic
r_int
r_char
id|magic
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|creator_version
r_int
r_char
id|creator_version
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|version
r_int
r_char
id|version
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|compression_method
r_int
r_char
id|compression_method
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mtime
r_int
r_char
id|mtime
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mdate
r_int
r_char
id|mdate
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|crc32
r_int
r_char
id|crc32
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|compressed_size
r_int
r_char
id|compressed_size
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|size
r_int
r_char
id|size
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|filename_length
r_int
r_char
id|filename_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|extra_length
r_int
r_char
id|extra_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|comment_length
r_int
r_char
id|comment_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|disk
r_int
r_char
id|disk
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|attr1
r_int
r_char
id|attr1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|attr2
r_int
r_char
id|attr2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|offset
r_int
r_char
id|offset
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zip_dir_trailer
r_struct
id|zip_dir_trailer
(brace
DECL|member|magic
r_int
r_char
id|magic
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|disk
r_int
r_char
id|disk
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|directory_start_disk
r_int
r_char
id|directory_start_disk
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|entries_on_this_disk
r_int
r_char
id|entries_on_this_disk
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|entries
r_int
r_char
id|entries
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|size
r_int
r_char
id|size
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|offset
r_int
r_char
id|offset
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|comment_length
r_int
r_char
id|comment_length
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|copy_le16
r_static
r_void
id|copy_le16
c_func
(paren
r_int
r_char
op_star
id|dest
comma
r_int
r_int
id|n
)paren
(brace
id|dest
(braket
l_int|0
)braket
op_assign
l_int|0xff
op_amp
id|n
suffix:semicolon
id|dest
(braket
l_int|1
)braket
op_assign
l_int|0xff
op_amp
(paren
id|n
op_rshift
l_int|010
)paren
suffix:semicolon
)brace
DECL|function|copy_le32
r_static
r_void
id|copy_le32
c_func
(paren
r_int
r_char
op_star
id|dest
comma
r_int
r_int
id|n
)paren
(brace
id|dest
(braket
l_int|0
)braket
op_assign
l_int|0xff
op_amp
id|n
suffix:semicolon
id|dest
(braket
l_int|1
)braket
op_assign
l_int|0xff
op_amp
(paren
id|n
op_rshift
l_int|010
)paren
suffix:semicolon
id|dest
(braket
l_int|2
)braket
op_assign
l_int|0xff
op_amp
(paren
id|n
op_rshift
l_int|020
)paren
suffix:semicolon
id|dest
(braket
l_int|3
)braket
op_assign
l_int|0xff
op_amp
(paren
id|n
op_rshift
l_int|030
)paren
suffix:semicolon
)brace
DECL|function|zlib_deflate
r_static
r_void
op_star
id|zlib_deflate
c_func
(paren
r_void
op_star
id|data
comma
r_int
r_int
id|size
comma
r_int
r_int
op_star
id|compressed_size
)paren
(brace
id|z_stream
id|stream
suffix:semicolon
r_int
r_int
id|maxsize
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|stream
comma
l_int|0
comma
r_sizeof
(paren
id|stream
)paren
)paren
suffix:semicolon
id|deflateInit
c_func
(paren
op_amp
id|stream
comma
id|zlib_compression_level
)paren
suffix:semicolon
id|maxsize
op_assign
id|deflateBound
c_func
(paren
op_amp
id|stream
comma
id|size
)paren
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|maxsize
)paren
suffix:semicolon
id|stream.next_in
op_assign
id|data
suffix:semicolon
id|stream.avail_in
op_assign
id|size
suffix:semicolon
id|stream.next_out
op_assign
id|buffer
suffix:semicolon
id|stream.avail_out
op_assign
id|maxsize
suffix:semicolon
r_do
(brace
id|result
op_assign
id|deflate
c_func
(paren
op_amp
id|stream
comma
id|Z_FINISH
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|result
op_eq
id|Z_OK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|Z_STREAM_END
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|deflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
op_star
id|compressed_size
op_assign
id|stream.total_out
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|construct_path
r_static
r_char
op_star
id|construct_path
c_func
(paren
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
id|filename
comma
r_int
id|isdir
comma
r_int
op_star
id|pathlen
)paren
(brace
r_int
id|filenamelen
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
r_int
id|len
op_assign
id|baselen
op_plus
id|filenamelen
suffix:semicolon
r_char
op_star
id|path
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|isdir
)paren
id|len
op_increment
suffix:semicolon
id|p
op_assign
id|path
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|p
op_add_assign
id|baselen
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|filename
comma
id|filenamelen
)paren
suffix:semicolon
id|p
op_add_assign
id|filenamelen
suffix:semicolon
r_if
c_cond
(paren
id|isdir
)paren
op_star
id|p
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|pathlen
op_assign
id|len
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
DECL|function|write_zip_entry
r_static
r_int
id|write_zip_entry
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
id|base
comma
r_int
id|baselen
comma
r_const
r_char
op_star
id|filename
comma
r_int
id|mode
comma
r_int
id|stage
)paren
(brace
r_struct
id|zip_local_header
id|header
suffix:semicolon
r_struct
id|zip_dir_header
id|dirent
suffix:semicolon
r_int
r_int
id|compressed_size
suffix:semicolon
r_int
r_int
id|uncompressed_size
suffix:semicolon
r_int
r_int
id|crc
suffix:semicolon
r_int
r_int
id|direntsize
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|method
suffix:semicolon
r_int
id|result
op_assign
l_int|1
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_int
r_char
op_star
id|out
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
r_void
op_star
id|deflated
op_assign
l_int|NULL
suffix:semicolon
id|crc
op_assign
id|crc32
c_func
(paren
l_int|0
comma
id|Z_NULL
comma
l_int|0
)paren
suffix:semicolon
id|path
op_assign
id|construct_path
c_func
(paren
id|base
comma
id|baselen
comma
id|filename
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
comma
op_amp
id|pathlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OG
l_int|0xffff
)paren
(brace
id|error
c_func
(paren
l_string|&quot;path too long (%d chars, SHA1: %s): %s&quot;
comma
id|pathlen
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|path
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
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
(brace
id|method
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|READ_TREE_RECURSIVE
suffix:semicolon
id|out
op_assign
l_int|NULL
suffix:semicolon
id|uncompressed_size
op_assign
l_int|0
suffix:semicolon
id|compressed_size
op_assign
l_int|0
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
id|method
op_assign
id|zlib_compression_level
op_eq
l_int|0
ques
c_cond
l_int|0
suffix:colon
l_int|8
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|buffer
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
id|buffer
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
id|crc
op_assign
id|crc32
c_func
(paren
id|crc
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|out
op_assign
id|buffer
suffix:semicolon
id|uncompressed_size
op_assign
id|size
suffix:semicolon
id|compressed_size
op_assign
id|size
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
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|method
op_eq
l_int|8
)paren
(brace
id|deflated
op_assign
id|zlib_deflate
c_func
(paren
id|buffer
comma
id|size
comma
op_amp
id|compressed_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deflated
op_logical_and
id|compressed_size
l_int|6
OL
id|size
)paren
(brace
multiline_comment|/* ZLIB --&gt; raw compressed data (see RFC 1950) */
multiline_comment|/* CMF and FLG ... */
id|out
op_assign
(paren
r_int
r_char
op_star
)paren
id|deflated
op_plus
l_int|2
suffix:semicolon
id|compressed_size
op_sub_assign
l_int|6
suffix:semicolon
multiline_comment|/* ... and ADLER32 */
)brace
r_else
(brace
id|method
op_assign
l_int|0
suffix:semicolon
id|compressed_size
op_assign
id|size
suffix:semicolon
)brace
)brace
multiline_comment|/* make sure we have enough free space in the dictionary */
id|direntsize
op_assign
r_sizeof
(paren
r_struct
id|zip_dir_header
)paren
op_plus
id|pathlen
suffix:semicolon
r_while
c_loop
(paren
id|zip_dir_size
OL
id|zip_dir_offset
op_plus
id|direntsize
)paren
(brace
id|zip_dir_size
op_add_assign
id|ZIP_DIRECTORY_MIN_SIZE
suffix:semicolon
id|zip_dir
op_assign
id|xrealloc
c_func
(paren
id|zip_dir
comma
id|zip_dir_size
)paren
suffix:semicolon
)brace
id|copy_le32
c_func
(paren
id|dirent.magic
comma
l_int|0x02014b50
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.creator_version
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.version
comma
l_int|20
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.flags
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.compression_method
comma
id|method
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.mtime
comma
id|zip_time
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.mdate
comma
id|zip_date
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|dirent.crc32
comma
id|crc
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|dirent.compressed_size
comma
id|compressed_size
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|dirent.size
comma
id|uncompressed_size
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.filename_length
comma
id|pathlen
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.extra_length
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.comment_length
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.disk
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|dirent.attr1
comma
l_int|0
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|dirent.attr2
comma
l_int|0
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|dirent.offset
comma
id|zip_offset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|zip_dir
op_plus
id|zip_dir_offset
comma
op_amp
id|dirent
comma
r_sizeof
(paren
r_struct
id|zip_dir_header
)paren
)paren
suffix:semicolon
id|zip_dir_offset
op_add_assign
r_sizeof
(paren
r_struct
id|zip_dir_header
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|zip_dir
op_plus
id|zip_dir_offset
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|zip_dir_offset
op_add_assign
id|pathlen
suffix:semicolon
id|zip_dir_entries
op_increment
suffix:semicolon
id|copy_le32
c_func
(paren
id|header.magic
comma
l_int|0x04034b50
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.version
comma
l_int|20
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.flags
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.compression_method
comma
id|method
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.mtime
comma
id|zip_time
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.mdate
comma
id|zip_date
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|header.crc32
comma
id|crc
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|header.compressed_size
comma
id|compressed_size
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|header.size
comma
id|uncompressed_size
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.filename_length
comma
id|pathlen
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|header.extra_length
comma
l_int|0
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
op_amp
id|header
comma
r_sizeof
(paren
r_struct
id|zip_local_header
)paren
)paren
suffix:semicolon
id|zip_offset
op_add_assign
r_sizeof
(paren
r_struct
id|zip_local_header
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|zip_offset
op_add_assign
id|pathlen
suffix:semicolon
r_if
c_cond
(paren
id|compressed_size
OG
l_int|0
)paren
(brace
id|write_or_die
c_func
(paren
l_int|1
comma
id|out
comma
id|compressed_size
)paren
suffix:semicolon
id|zip_offset
op_add_assign
id|compressed_size
suffix:semicolon
)brace
id|out
suffix:colon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|free
c_func
(paren
id|deflated
)paren
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|write_zip_trailer
r_static
r_void
id|write_zip_trailer
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
id|zip_dir_trailer
id|trailer
suffix:semicolon
id|copy_le32
c_func
(paren
id|trailer.magic
comma
l_int|0x06054b50
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|trailer.disk
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|trailer.directory_start_disk
comma
l_int|0
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|trailer.entries_on_this_disk
comma
id|zip_dir_entries
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|trailer.entries
comma
id|zip_dir_entries
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|trailer.size
comma
id|zip_dir_offset
)paren
suffix:semicolon
id|copy_le32
c_func
(paren
id|trailer.offset
comma
id|zip_offset
)paren
suffix:semicolon
id|copy_le16
c_func
(paren
id|trailer.comment_length
comma
id|sha1
ques
c_cond
l_int|40
suffix:colon
l_int|0
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|zip_dir
comma
id|zip_dir_offset
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
op_amp
id|trailer
comma
r_sizeof
(paren
r_struct
id|zip_dir_trailer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sha1
)paren
id|write_or_die
c_func
(paren
l_int|1
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
)brace
DECL|function|dos_time
r_static
r_void
id|dos_time
c_func
(paren
id|time_t
op_star
id|time
comma
r_int
op_star
id|dos_date
comma
r_int
op_star
id|dos_time
)paren
(brace
r_struct
id|tm
op_star
id|t
op_assign
id|localtime
c_func
(paren
id|time
)paren
suffix:semicolon
op_star
id|dos_date
op_assign
id|t-&gt;tm_mday
op_plus
(paren
id|t-&gt;tm_mon
op_plus
l_int|1
)paren
op_star
l_int|32
op_plus
(paren
id|t-&gt;tm_year
op_plus
l_int|1900
l_int|1980
)paren
op_star
l_int|512
suffix:semicolon
op_star
id|dos_time
op_assign
id|t-&gt;tm_sec
op_div
l_int|2
op_plus
id|t-&gt;tm_min
op_star
l_int|32
op_plus
id|t-&gt;tm_hour
op_star
l_int|2048
suffix:semicolon
)brace
DECL|function|write_zip_archive
r_int
id|write_zip_archive
c_func
(paren
r_struct
id|archiver_args
op_star
id|args
)paren
(brace
r_int
id|plen
op_assign
id|strlen
c_func
(paren
id|args-&gt;base
)paren
suffix:semicolon
id|dos_time
c_func
(paren
op_amp
id|args-&gt;time
comma
op_amp
id|zip_date
comma
op_amp
id|zip_time
)paren
suffix:semicolon
id|zip_dir
op_assign
id|xmalloc
c_func
(paren
id|ZIP_DIRECTORY_MIN_SIZE
)paren
suffix:semicolon
id|zip_dir_size
op_assign
id|ZIP_DIRECTORY_MIN_SIZE
suffix:semicolon
id|verbose
op_assign
id|args-&gt;verbose
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;base
op_logical_and
id|plen
OG
l_int|0
op_logical_and
id|args-&gt;base
(braket
id|plen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_char
op_star
id|base
op_assign
id|xstrdup
c_func
(paren
id|args-&gt;base
)paren
suffix:semicolon
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_while
c_loop
(paren
id|baselen
OG
l_int|0
op_logical_and
id|base
(braket
id|baselen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|base
(braket
op_decrement
id|baselen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|write_zip_entry
c_func
(paren
id|args-&gt;tree-&gt;object.sha1
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|base
comma
l_int|040777
comma
l_int|0
)paren
suffix:semicolon
id|free
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
id|read_tree_recursive
c_func
(paren
id|args-&gt;tree
comma
id|args-&gt;base
comma
id|plen
comma
l_int|0
comma
id|args-&gt;pathspec
comma
id|write_zip_entry
)paren
suffix:semicolon
id|write_zip_trailer
c_func
(paren
id|args-&gt;commit_sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|zip_dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_extra_zip_args
r_void
op_star
id|parse_extra_zip_args
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
r_for
c_loop
(paren
suffix:semicolon
id|argc
OG
l_int|0
suffix:semicolon
id|argc
op_decrement
comma
id|argv
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
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
op_logical_and
id|isdigit
c_func
(paren
id|arg
(braket
l_int|1
)braket
)paren
op_logical_and
id|arg
(braket
l_int|2
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|zlib_compression_level
op_assign
id|arg
(braket
l_int|1
)braket
l_char|&squot;0&squot;
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;Unknown argument for zip format: %s&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
eof
