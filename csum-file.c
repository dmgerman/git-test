multiline_comment|/*&n; * csum-file.c&n; *&n; * Copyright (C) 2005 Linus Torvalds&n; *&n; * Simple file write infrastructure for writing SHA1-summed&n; * files. Useful when you write a file that you want to be&n; * able to verify hasn&squot;t been messed with afterwards.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;progress.h&quot;
macro_line|#include &quot;csum-file.h&quot;
DECL|function|flush
r_static
r_void
id|flush
c_func
(paren
r_struct
id|sha1file
op_star
id|f
comma
r_int
r_int
id|count
)paren
(brace
r_void
op_star
id|buf
op_assign
id|f-&gt;buffer
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|ret
op_assign
id|xwrite
c_func
(paren
id|f-&gt;fd
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|f-&gt;total
op_add_assign
id|ret
suffix:semicolon
id|display_throughput
c_func
(paren
id|f-&gt;tp
comma
id|f-&gt;total
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_char
op_star
)paren
id|buf
op_plus
id|ret
suffix:semicolon
id|count
op_sub_assign
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
r_continue
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|die
c_func
(paren
l_string|&quot;sha1 file &squot;%s&squot; write error. Out of diskspace&quot;
comma
id|f-&gt;name
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;sha1 file &squot;%s&squot; write error (%s)&quot;
comma
id|f-&gt;name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|sha1flush
r_void
id|sha1flush
c_func
(paren
r_struct
id|sha1file
op_star
id|f
)paren
(brace
r_int
id|offset
op_assign
id|f-&gt;offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|SHA1_Update
c_func
(paren
op_amp
id|f-&gt;ctx
comma
id|f-&gt;buffer
comma
id|offset
)paren
suffix:semicolon
id|flush
c_func
(paren
id|f
comma
id|offset
)paren
suffix:semicolon
id|f-&gt;offset
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|sha1close
r_int
id|sha1close
c_func
(paren
r_struct
id|sha1file
op_star
id|f
comma
r_int
r_char
op_star
id|result
comma
r_int
r_int
id|flags
)paren
(brace
r_int
id|fd
suffix:semicolon
id|sha1flush
c_func
(paren
id|f
)paren
suffix:semicolon
id|SHA1_Final
c_func
(paren
id|f-&gt;buffer
comma
op_amp
id|f-&gt;ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|hashcpy
c_func
(paren
id|result
comma
id|f-&gt;buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|CSUM_CLOSE
op_or
id|CSUM_FSYNC
)paren
)paren
(brace
multiline_comment|/* write checksum and close fd */
id|flush
c_func
(paren
id|f
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CSUM_FSYNC
)paren
id|fsync_or_die
c_func
(paren
id|f-&gt;fd
comma
id|f-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close
c_func
(paren
id|f-&gt;fd
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s: sha1 file error on close (%s)&quot;
comma
id|f-&gt;name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|fd
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|fd
op_assign
id|f-&gt;fd
suffix:semicolon
id|free
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|sha1write
r_int
id|sha1write
c_func
(paren
r_struct
id|sha1file
op_star
id|f
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;do_crc
)paren
id|f-&gt;crc32
op_assign
id|crc32
c_func
(paren
id|f-&gt;crc32
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_int
id|offset
op_assign
id|f-&gt;offset
suffix:semicolon
r_int
id|left
op_assign
r_sizeof
(paren
id|f-&gt;buffer
)paren
id|offset
suffix:semicolon
r_int
id|nr
op_assign
id|count
OG
id|left
ques
c_cond
id|left
suffix:colon
id|count
suffix:semicolon
id|memcpy
c_func
(paren
id|f-&gt;buffer
op_plus
id|offset
comma
id|buf
comma
id|nr
)paren
suffix:semicolon
id|count
op_sub_assign
id|nr
suffix:semicolon
id|offset
op_add_assign
id|nr
suffix:semicolon
id|buf
op_assign
(paren
r_char
op_star
)paren
id|buf
op_plus
id|nr
suffix:semicolon
id|left
op_sub_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
(brace
id|SHA1_Update
c_func
(paren
op_amp
id|f-&gt;ctx
comma
id|f-&gt;buffer
comma
id|offset
)paren
suffix:semicolon
id|flush
c_func
(paren
id|f
comma
id|offset
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
id|f-&gt;offset
op_assign
id|offset
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sha1fd
r_struct
id|sha1file
op_star
id|sha1fd
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|sha1fd_throughput
c_func
(paren
id|fd
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|sha1fd_throughput
r_struct
id|sha1file
op_star
id|sha1fd_throughput
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|progress
op_star
id|tp
)paren
(brace
r_struct
id|sha1file
op_star
id|f
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|f-&gt;fd
op_assign
id|fd
suffix:semicolon
id|f-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|f-&gt;total
op_assign
l_int|0
suffix:semicolon
id|f-&gt;tp
op_assign
id|tp
suffix:semicolon
id|f-&gt;name
op_assign
id|name
suffix:semicolon
id|f-&gt;do_crc
op_assign
l_int|0
suffix:semicolon
id|SHA1_Init
c_func
(paren
op_amp
id|f-&gt;ctx
)paren
suffix:semicolon
r_return
id|f
suffix:semicolon
)brace
DECL|function|crc32_begin
r_void
id|crc32_begin
c_func
(paren
r_struct
id|sha1file
op_star
id|f
)paren
(brace
id|f-&gt;crc32
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
id|f-&gt;do_crc
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|crc32_end
r_uint32
id|crc32_end
c_func
(paren
r_struct
id|sha1file
op_star
id|f
)paren
(brace
id|f-&gt;do_crc
op_assign
l_int|0
suffix:semicolon
r_return
id|f-&gt;crc32
suffix:semicolon
)brace
eof
