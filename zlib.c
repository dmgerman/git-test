multiline_comment|/*&n; * zlib wrappers to make sure we don&squot;t silently miss errors&n; * at init time.&n; */
macro_line|#include &quot;cache.h&quot;
DECL|function|zerr_to_string
r_static
r_const
r_char
op_star
id|zerr_to_string
c_func
(paren
r_int
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|Z_MEM_ERROR
suffix:colon
r_return
l_string|&quot;out of memory&quot;
suffix:semicolon
r_case
id|Z_VERSION_ERROR
suffix:colon
r_return
l_string|&quot;wrong version&quot;
suffix:semicolon
r_case
id|Z_NEED_DICT
suffix:colon
r_return
l_string|&quot;needs dictionary&quot;
suffix:semicolon
r_case
id|Z_DATA_ERROR
suffix:colon
r_return
l_string|&quot;data stream error&quot;
suffix:semicolon
r_case
id|Z_STREAM_ERROR
suffix:colon
r_return
l_string|&quot;stream consistency error&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown error&quot;
suffix:semicolon
)brace
)brace
DECL|function|git_inflate_init
r_void
id|git_inflate_init
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
r_int
id|status
op_assign
id|inflateInit
c_func
(paren
id|strm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_OK
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;inflateInit: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_inflate_init_gzip_only
r_void
id|git_inflate_init_gzip_only
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
multiline_comment|/*&n;&t; * Use default 15 bits, +16 is to accept only gzip and to&n;&t; * yield Z_DATA_ERROR when fed zlib format.&n;&t; */
r_const
r_int
id|windowBits
op_assign
l_int|15
op_plus
l_int|16
suffix:semicolon
r_int
id|status
op_assign
id|inflateInit2
c_func
(paren
id|strm
comma
id|windowBits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_OK
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;inflateInit2: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_inflate_end
r_void
id|git_inflate_end
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
r_int
id|status
op_assign
id|inflateEnd
c_func
(paren
id|strm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_OK
)paren
r_return
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;inflateEnd: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_inflate
r_int
id|git_inflate
c_func
(paren
id|z_streamp
id|strm
comma
r_int
id|flush
)paren
(brace
r_int
id|status
op_assign
id|inflate
c_func
(paren
id|strm
comma
id|flush
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* Z_BUF_ERROR: normal, needs more space in the output buffer */
r_case
id|Z_BUF_ERROR
suffix:colon
r_case
id|Z_OK
suffix:colon
r_case
id|Z_STREAM_END
suffix:colon
r_return
id|status
suffix:semicolon
r_case
id|Z_MEM_ERROR
suffix:colon
id|die
c_func
(paren
l_string|&quot;inflate: out of memory&quot;
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|error
c_func
(paren
l_string|&quot;inflate: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|git_deflate_init
r_void
id|git_deflate_init
c_func
(paren
id|z_streamp
id|strm
comma
r_int
id|level
)paren
(brace
r_int
id|status
op_assign
id|deflateInit
c_func
(paren
id|strm
comma
id|level
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_OK
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;deflateInit: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_deflate_init_gzip
r_void
id|git_deflate_init_gzip
c_func
(paren
id|z_streamp
id|strm
comma
r_int
id|level
)paren
(brace
multiline_comment|/*&n;&t; * Use default 15 bits, +16 is to generate gzip header/trailer&n;&t; * instead of the zlib wrapper.&n;&t; */
r_const
r_int
id|windowBits
op_assign
l_int|15
op_plus
l_int|16
suffix:semicolon
r_int
id|status
op_assign
id|deflateInit2
c_func
(paren
id|strm
comma
id|level
comma
id|Z_DEFLATED
comma
id|windowBits
comma
l_int|8
comma
id|Z_DEFAULT_STRATEGY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_OK
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;deflateInit2: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_deflate_end
r_void
id|git_deflate_end
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
r_int
id|status
op_assign
id|deflateEnd
c_func
(paren
id|strm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_OK
)paren
r_return
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;deflateEnd: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
)brace
DECL|function|git_deflate_end_gently
r_int
id|git_deflate_end_gently
c_func
(paren
id|z_streamp
id|strm
)paren
(brace
r_return
id|deflateEnd
c_func
(paren
id|strm
)paren
suffix:semicolon
)brace
DECL|function|git_deflate
r_int
id|git_deflate
c_func
(paren
id|z_streamp
id|strm
comma
r_int
id|flush
)paren
(brace
r_int
id|status
op_assign
id|deflate
c_func
(paren
id|strm
comma
id|flush
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
multiline_comment|/* Z_BUF_ERROR: normal, needs more space in the output buffer */
r_case
id|Z_BUF_ERROR
suffix:colon
r_case
id|Z_OK
suffix:colon
r_case
id|Z_STREAM_END
suffix:colon
r_return
id|status
suffix:semicolon
r_case
id|Z_MEM_ERROR
suffix:colon
id|die
c_func
(paren
l_string|&quot;deflate: out of memory&quot;
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|error
c_func
(paren
l_string|&quot;deflate: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;msg
ques
c_cond
id|strm-&gt;msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
eof
