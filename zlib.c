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
multiline_comment|/*&n; * avail_in and avail_out in zlib are counted in uInt, which typically&n; * limits the size of the buffer we can use to 4GB when interacting&n; * with zlib in a single call to inflate/deflate.&n; */
multiline_comment|/* #define ZLIB_BUF_MAX ((uInt)-1) */
DECL|macro|ZLIB_BUF_MAX
mdefine_line|#define ZLIB_BUF_MAX ((uInt) 1024 * 1024 * 1024) /* 1GB */
DECL|function|zlib_buf_cap
r_static
r_inline
id|uInt
id|zlib_buf_cap
c_func
(paren
r_int
r_int
id|len
)paren
(brace
r_return
(paren
id|ZLIB_BUF_MAX
OL
id|len
)paren
ques
c_cond
id|ZLIB_BUF_MAX
suffix:colon
id|len
suffix:semicolon
)brace
DECL|function|zlib_pre_call
r_static
r_void
id|zlib_pre_call
c_func
(paren
id|git_zstream
op_star
id|s
)paren
(brace
id|s-&gt;z.next_in
op_assign
id|s-&gt;next_in
suffix:semicolon
id|s-&gt;z.next_out
op_assign
id|s-&gt;next_out
suffix:semicolon
id|s-&gt;z.total_in
op_assign
id|s-&gt;total_in
suffix:semicolon
id|s-&gt;z.total_out
op_assign
id|s-&gt;total_out
suffix:semicolon
id|s-&gt;z.avail_in
op_assign
id|zlib_buf_cap
c_func
(paren
id|s-&gt;avail_in
)paren
suffix:semicolon
id|s-&gt;z.avail_out
op_assign
id|zlib_buf_cap
c_func
(paren
id|s-&gt;avail_out
)paren
suffix:semicolon
)brace
DECL|function|zlib_post_call
r_static
r_void
id|zlib_post_call
c_func
(paren
id|git_zstream
op_star
id|s
)paren
(brace
r_int
r_int
id|bytes_consumed
suffix:semicolon
r_int
r_int
id|bytes_produced
suffix:semicolon
id|bytes_consumed
op_assign
id|s-&gt;z.next_in
id|s-&gt;next_in
suffix:semicolon
id|bytes_produced
op_assign
id|s-&gt;z.next_out
id|s-&gt;next_out
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;z.total_out
op_ne
id|s-&gt;total_out
op_plus
id|bytes_produced
)paren
id|die
c_func
(paren
l_string|&quot;BUG: total_out mismatch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;z.total_in
op_ne
id|s-&gt;total_in
op_plus
id|bytes_consumed
)paren
id|die
c_func
(paren
l_string|&quot;BUG: total_in mismatch&quot;
)paren
suffix:semicolon
id|s-&gt;total_out
op_assign
id|s-&gt;z.total_out
suffix:semicolon
id|s-&gt;total_in
op_assign
id|s-&gt;z.total_in
suffix:semicolon
id|s-&gt;next_in
op_assign
id|s-&gt;z.next_in
suffix:semicolon
id|s-&gt;next_out
op_assign
id|s-&gt;z.next_out
suffix:semicolon
id|s-&gt;avail_in
op_sub_assign
id|bytes_consumed
suffix:semicolon
id|s-&gt;avail_out
op_sub_assign
id|bytes_produced
suffix:semicolon
)brace
DECL|function|git_inflate_init
r_void
id|git_inflate_init
c_func
(paren
id|git_zstream
op_star
id|strm
)paren
(brace
r_int
id|status
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|inflateInit
c_func
(paren
op_amp
id|strm-&gt;z
)paren
suffix:semicolon
id|zlib_post_call
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
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
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
id|git_zstream
op_star
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
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|inflateInit2
c_func
(paren
op_amp
id|strm-&gt;z
comma
id|windowBits
)paren
suffix:semicolon
id|zlib_post_call
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
l_string|&quot;inflateInit2: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
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
id|git_zstream
op_star
id|strm
)paren
(brace
r_int
id|status
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|inflateEnd
c_func
(paren
op_amp
id|strm-&gt;z
)paren
suffix:semicolon
id|zlib_post_call
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
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
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
id|git_zstream
op_star
id|strm
comma
r_int
id|flush
)paren
(brace
r_int
id|status
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
multiline_comment|/* Never say Z_FINISH unless we are feeding everything */
id|status
op_assign
id|inflate
c_func
(paren
op_amp
id|strm-&gt;z
comma
(paren
id|strm-&gt;z.avail_in
op_ne
id|strm-&gt;avail_in
)paren
ques
c_cond
l_int|0
suffix:colon
id|flush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_MEM_ERROR
)paren
id|die
c_func
(paren
l_string|&quot;inflate: out of memory&quot;
)paren
suffix:semicolon
id|zlib_post_call
c_func
(paren
id|strm
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Let zlib work another round, while we can still&n;&t;&t; * make progress.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|strm-&gt;avail_out
op_logical_and
op_logical_neg
id|strm-&gt;z.avail_out
)paren
op_logical_and
(paren
id|status
op_eq
id|Z_OK
op_logical_or
id|status
op_eq
id|Z_BUF_ERROR
)paren
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
macro_line|#if defined(NO_DEFLATE_BOUND) || ZLIB_VERNUM &lt; 0x1200
DECL|macro|deflateBound
mdefine_line|#define deflateBound(c,s)  ((s) + (((s) + 7) &gt;&gt; 3) + (((s) + 63) &gt;&gt; 6) + 11)
macro_line|#endif
DECL|function|git_deflate_bound
r_int
r_int
id|git_deflate_bound
c_func
(paren
id|git_zstream
op_star
id|strm
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|deflateBound
c_func
(paren
op_amp
id|strm-&gt;z
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|git_deflate_init
r_void
id|git_deflate_init
c_func
(paren
id|git_zstream
op_star
id|strm
comma
r_int
id|level
)paren
(brace
r_int
id|status
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|deflateInit
c_func
(paren
op_amp
id|strm-&gt;z
comma
id|level
)paren
suffix:semicolon
id|zlib_post_call
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
l_string|&quot;deflateInit: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
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
id|git_zstream
op_star
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
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|deflateInit2
c_func
(paren
op_amp
id|strm-&gt;z
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
id|zlib_post_call
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
l_string|&quot;deflateInit2: %s (%s)&quot;
comma
id|zerr_to_string
c_func
(paren
id|status
)paren
comma
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
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
id|git_zstream
op_star
id|strm
)paren
(brace
r_int
id|status
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|deflateEnd
c_func
(paren
op_amp
id|strm-&gt;z
)paren
suffix:semicolon
id|zlib_post_call
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
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
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
id|git_zstream
op_star
id|strm
)paren
(brace
r_int
id|status
suffix:semicolon
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
id|status
op_assign
id|deflateEnd
c_func
(paren
op_amp
id|strm-&gt;z
)paren
suffix:semicolon
id|zlib_post_call
c_func
(paren
id|strm
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|git_deflate
r_int
id|git_deflate
c_func
(paren
id|git_zstream
op_star
id|strm
comma
r_int
id|flush
)paren
(brace
r_int
id|status
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|zlib_pre_call
c_func
(paren
id|strm
)paren
suffix:semicolon
multiline_comment|/* Never say Z_FINISH unless we are feeding everything */
id|status
op_assign
id|deflate
c_func
(paren
op_amp
id|strm-&gt;z
comma
(paren
id|strm-&gt;z.avail_in
op_ne
id|strm-&gt;avail_in
)paren
ques
c_cond
l_int|0
suffix:colon
id|flush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|Z_MEM_ERROR
)paren
id|die
c_func
(paren
l_string|&quot;deflate: out of memory&quot;
)paren
suffix:semicolon
id|zlib_post_call
c_func
(paren
id|strm
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Let zlib work another round, while we can still&n;&t;&t; * make progress.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|strm-&gt;avail_out
op_logical_and
op_logical_neg
id|strm-&gt;z.avail_out
)paren
op_logical_and
(paren
id|status
op_eq
id|Z_OK
op_logical_or
id|status
op_eq
id|Z_BUF_ERROR
)paren
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|strm-&gt;z.msg
ques
c_cond
id|strm-&gt;z.msg
suffix:colon
l_string|&quot;no message&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
eof
