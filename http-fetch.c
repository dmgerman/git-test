macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;fetch.h&quot;
macro_line|#include &lt;curl/curl.h&gt;
macro_line|#include &lt;curl/easy.h&gt;
macro_line|#if LIBCURL_VERSION_NUM &lt; 0x070704
DECL|macro|curl_global_cleanup
mdefine_line|#define curl_global_cleanup() do { /* nothing */ } while(0)
macro_line|#endif
macro_line|#if LIBCURL_VERSION_NUM &lt; 0x070800
DECL|macro|curl_global_init
mdefine_line|#define curl_global_init(a) do { /* nothing */ } while(0)
macro_line|#endif
DECL|variable|curl
r_static
id|CURL
op_star
id|curl
suffix:semicolon
DECL|variable|no_pragma_header
r_static
r_struct
id|curl_slist
op_star
id|no_pragma_header
suffix:semicolon
DECL|variable|initial_base
r_static
r_char
op_star
id|initial_base
suffix:semicolon
DECL|struct|alt_base
r_struct
id|alt_base
(brace
DECL|member|base
r_char
op_star
id|base
suffix:semicolon
DECL|member|got_indices
r_int
id|got_indices
suffix:semicolon
DECL|member|packs
r_struct
id|packed_git
op_star
id|packs
suffix:semicolon
DECL|member|next
r_struct
id|alt_base
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|alt
r_struct
id|alt_base
op_star
id|alt
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|c
r_static
id|SHA_CTX
id|c
suffix:semicolon
DECL|variable|stream
r_static
id|z_stream
id|stream
suffix:semicolon
DECL|variable|local
r_static
r_int
id|local
suffix:semicolon
DECL|variable|zret
r_static
r_int
id|zret
suffix:semicolon
DECL|variable|curl_ssl_verify
r_static
r_int
id|curl_ssl_verify
suffix:semicolon
DECL|struct|buffer
r_struct
id|buffer
(brace
DECL|member|posn
r_int
id|posn
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|function|fwrite_buffer
r_static
r_int
id|fwrite_buffer
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|eltsize
comma
r_int
id|nmemb
comma
r_struct
id|buffer
op_star
id|buffer
)paren
(brace
r_int
id|size
op_assign
id|eltsize
op_star
id|nmemb
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|buffer-&gt;size
id|buffer-&gt;posn
)paren
id|size
op_assign
id|buffer-&gt;size
id|buffer-&gt;posn
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer-&gt;buffer
op_plus
id|buffer-&gt;posn
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
id|buffer-&gt;posn
op_add_assign
id|size
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|fwrite_sha1_file
r_static
r_int
id|fwrite_sha1_file
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|eltsize
comma
r_int
id|nmemb
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_char
id|expn
(braket
l_int|4096
)braket
suffix:semicolon
r_int
id|size
op_assign
id|eltsize
op_star
id|nmemb
suffix:semicolon
r_int
id|posn
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ssize_t
id|retval
op_assign
id|write
c_func
(paren
id|local
comma
id|ptr
op_plus
id|posn
comma
id|size
id|posn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|posn
suffix:semicolon
id|posn
op_add_assign
id|retval
suffix:semicolon
)brace
r_while
c_loop
(paren
id|posn
OL
id|size
)paren
suffix:semicolon
id|stream.avail_in
op_assign
id|size
suffix:semicolon
id|stream.next_in
op_assign
id|ptr
suffix:semicolon
r_do
(brace
id|stream.next_out
op_assign
id|expn
suffix:semicolon
id|stream.avail_out
op_assign
r_sizeof
(paren
id|expn
)paren
suffix:semicolon
id|zret
op_assign
id|inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_SYNC_FLUSH
)paren
suffix:semicolon
id|SHA1_Update
c_func
(paren
op_amp
id|c
comma
id|expn
comma
r_sizeof
(paren
id|expn
)paren
id|stream.avail_out
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|stream.avail_in
op_logical_and
id|zret
op_eq
id|Z_OK
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|prefetch
r_void
id|prefetch
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
)brace
DECL|variable|got_alternates
r_static
r_int
id|got_alternates
op_assign
l_int|0
suffix:semicolon
DECL|function|fetch_index
r_static
r_int
id|fetch_index
c_func
(paren
r_struct
id|alt_base
op_star
id|repo
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|filename
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
id|FILE
op_star
id|indexfile
suffix:semicolon
r_if
c_cond
(paren
id|has_pack_index
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting index for pack %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|repo-&gt;base
)paren
op_plus
l_int|64
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|url
comma
l_string|&quot;%s/objects/pack/pack-%s.idx&quot;
comma
id|repo-&gt;base
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|filename
op_assign
id|sha1_pack_index_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|indexfile
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|indexfile
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Unable to open local file %s for pack index&quot;
comma
id|filename
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
id|indexfile
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_HTTPHEADER
comma
id|no_pragma_header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
)paren
(brace
id|fclose
c_func
(paren
id|indexfile
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Unable to get pack index %s&quot;
comma
id|url
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|indexfile
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_index
r_static
r_int
id|setup_index
c_func
(paren
r_struct
id|alt_base
op_star
id|repo
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|packed_git
op_star
id|new_pack
suffix:semicolon
r_if
c_cond
(paren
id|has_pack_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
singleline_comment|// don&squot;t list this as something we can get
r_if
c_cond
(paren
id|fetch_index
c_func
(paren
id|repo
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|new_pack
op_assign
id|parse_pack_index
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|new_pack-&gt;next
op_assign
id|repo-&gt;packs
suffix:semicolon
id|repo-&gt;packs
op_assign
id|new_pack
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_alternates
r_static
r_int
id|fetch_alternates
c_func
(paren
r_char
op_star
id|base
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|buffer
id|buffer
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|http_specific
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|got_alternates
)paren
r_return
l_int|0
suffix:semicolon
id|data
op_assign
id|xmalloc
c_func
(paren
l_int|4096
)paren
suffix:semicolon
id|buffer.size
op_assign
l_int|4095
suffix:semicolon
id|buffer.posn
op_assign
l_int|0
suffix:semicolon
id|buffer.buffer
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting alternates list&bslash;n&quot;
)paren
suffix:semicolon
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base
)paren
op_plus
l_int|31
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|url
comma
l_string|&quot;%s/objects/info/http-alternates&quot;
comma
id|base
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite_buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
op_logical_or
op_logical_neg
id|buffer.posn
)paren
(brace
id|http_specific
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|url
comma
l_string|&quot;%s/objects/info/alternates&quot;
comma
id|base
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite_buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|data
(braket
id|buffer.posn
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|buffer.posn
)paren
(brace
r_int
id|posn
op_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
id|posn
OL
id|buffer.posn
op_logical_and
id|data
(braket
id|posn
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|posn
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
id|posn
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_int
id|okay
op_assign
l_int|0
suffix:semicolon
r_int
id|serverlen
op_assign
l_int|0
suffix:semicolon
r_struct
id|alt_base
op_star
id|newalt
suffix:semicolon
r_char
op_star
id|target
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
id|i
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|serverlen
op_assign
id|strchr
c_func
(paren
id|base
op_plus
l_int|8
comma
l_char|&squot;/&squot;
)paren
id|base
suffix:semicolon
id|okay
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|data
op_plus
id|i
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
)paren
(brace
id|i
op_add_assign
l_int|3
suffix:semicolon
id|serverlen
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
id|i
op_plus
l_int|2
OL
id|posn
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|data
op_plus
id|i
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
)paren
(brace
r_do
(brace
id|serverlen
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|serverlen
op_logical_and
id|base
(braket
id|serverlen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
suffix:semicolon
)brace
singleline_comment|// If the server got removed, give up.
id|okay
op_assign
id|strchr
c_func
(paren
id|base
comma
l_char|&squot;:&squot;
)paren
id|base
op_plus
l_int|3
OL
id|serverlen
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|http_specific
)paren
(brace
r_char
op_star
id|colon
op_assign
id|strchr
c_func
(paren
id|data
op_plus
id|i
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
id|data
op_plus
id|i
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|colon
op_logical_and
id|slash
op_logical_and
id|colon
OL
id|data
op_plus
id|posn
op_logical_and
id|slash
OL
id|data
op_plus
id|posn
op_logical_and
id|colon
OL
id|slash
)paren
(brace
id|okay
op_assign
l_int|1
suffix:semicolon
)brace
)brace
singleline_comment|// skip &squot;objects&squot; at end
r_if
c_cond
(paren
id|okay
)paren
(brace
id|target
op_assign
id|xmalloc
c_func
(paren
id|serverlen
op_plus
id|posn
id|i
l_int|6
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|target
comma
id|base
comma
id|serverlen
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|target
op_plus
id|serverlen
comma
id|data
op_plus
id|i
comma
id|posn
id|i
l_int|7
)paren
suffix:semicolon
id|target
(braket
id|serverlen
op_plus
id|posn
id|i
l_int|7
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Also look at %s&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
id|newalt
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|newalt
)paren
)paren
suffix:semicolon
id|newalt-&gt;next
op_assign
id|alt
suffix:semicolon
id|newalt-&gt;base
op_assign
id|target
suffix:semicolon
id|newalt-&gt;got_indices
op_assign
l_int|0
suffix:semicolon
id|newalt-&gt;packs
op_assign
l_int|NULL
suffix:semicolon
id|alt
op_assign
id|newalt
suffix:semicolon
id|ret
op_increment
suffix:semicolon
)brace
)brace
id|i
op_assign
id|posn
op_plus
l_int|1
suffix:semicolon
)brace
id|got_alternates
op_assign
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fetch_indices
r_static
r_int
id|fetch_indices
c_func
(paren
r_struct
id|alt_base
op_star
id|repo
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_struct
id|buffer
id|buffer
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|repo-&gt;got_indices
)paren
r_return
l_int|0
suffix:semicolon
id|data
op_assign
id|xmalloc
c_func
(paren
l_int|4096
)paren
suffix:semicolon
id|buffer.size
op_assign
l_int|4096
suffix:semicolon
id|buffer.posn
op_assign
l_int|0
suffix:semicolon
id|buffer.buffer
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting pack list&bslash;n&quot;
)paren
suffix:semicolon
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|repo-&gt;base
)paren
op_plus
l_int|21
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|url
comma
l_string|&quot;%s/objects/info/packs&quot;
comma
id|repo-&gt;base
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite_buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_HTTPHEADER
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|buffer.posn
)paren
(brace
r_switch
c_cond
(paren
id|data
(braket
id|i
)braket
)paren
(brace
r_case
l_char|&squot;P&squot;
suffix:colon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
l_int|52
OL
id|buffer.posn
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|data
op_plus
id|i
comma
l_string|&quot; pack-&quot;
comma
l_int|6
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|data
op_plus
id|i
op_plus
l_int|46
comma
l_string|&quot;.pack&bslash;n&quot;
comma
l_int|6
)paren
)paren
(brace
id|get_sha1_hex
c_func
(paren
id|data
op_plus
id|i
op_plus
l_int|6
comma
id|sha1
)paren
suffix:semicolon
id|setup_index
c_func
(paren
id|repo
comma
id|sha1
)paren
suffix:semicolon
id|i
op_add_assign
l_int|51
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
(brace
)brace
r_while
c_loop
(paren
id|data
(braket
id|i
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|i
op_increment
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
id|repo-&gt;got_indices
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_pack
r_static
r_int
id|fetch_pack
c_func
(paren
r_struct
id|alt_base
op_star
id|repo
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|url
suffix:semicolon
r_struct
id|packed_git
op_star
id|target
suffix:semicolon
r_struct
id|packed_git
op_star
op_star
id|lst
suffix:semicolon
id|FILE
op_star
id|packfile
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
r_if
c_cond
(paren
id|fetch_indices
c_func
(paren
id|repo
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|target
op_assign
id|find_sha1_pack
c_func
(paren
id|sha1
comma
id|repo-&gt;packs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_verbosely
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting pack %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; which contains %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|repo-&gt;base
)paren
op_plus
l_int|65
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|url
comma
l_string|&quot;%s/objects/pack/pack-%s.pack&quot;
comma
id|repo-&gt;base
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|filename
op_assign
id|sha1_pack_name
c_func
(paren
id|target-&gt;sha1
)paren
suffix:semicolon
id|packfile
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packfile
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Unable to open local file %s for pack&quot;
comma
id|filename
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
id|packfile
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_HTTPHEADER
comma
id|no_pragma_header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
)paren
(brace
id|fclose
c_func
(paren
id|packfile
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Unable to get pack file %s&quot;
comma
id|url
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|packfile
)paren
suffix:semicolon
id|lst
op_assign
op_amp
id|repo-&gt;packs
suffix:semicolon
r_while
c_loop
(paren
op_star
id|lst
op_ne
id|target
)paren
id|lst
op_assign
op_amp
(paren
(paren
op_star
id|lst
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|lst
op_assign
(paren
op_star
id|lst
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|install_packed_git
c_func
(paren
id|target
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_object
r_int
id|fetch_object
c_func
(paren
r_struct
id|alt_base
op_star
id|repo
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_char
op_star
id|filename
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_int
r_char
id|real_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|tmpfile
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_char
op_star
id|posn
suffix:semicolon
id|snprintf
c_func
(paren
id|tmpfile
comma
r_sizeof
(paren
id|tmpfile
)paren
comma
l_string|&quot;%s/obj_XXXXXX&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|local
op_assign
id|mkstemp
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t create temporary file %s for %s: %s&bslash;n&quot;
comma
id|tmpfile
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
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
id|inflateInit
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|SHA1_Init
c_func
(paren
op_amp
id|c
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FAILONERROR
comma
l_int|1
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
l_int|NULL
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite_sha1_file
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_HTTPHEADER
comma
id|no_pragma_header
)paren
suffix:semicolon
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|repo-&gt;base
)paren
op_plus
l_int|50
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|url
comma
id|repo-&gt;base
)paren
suffix:semicolon
id|posn
op_assign
id|url
op_plus
id|strlen
c_func
(paren
id|repo-&gt;base
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|posn
comma
l_string|&quot;objects/&quot;
)paren
suffix:semicolon
id|posn
op_add_assign
l_int|8
suffix:semicolon
id|memcpy
c_func
(paren
id|posn
comma
id|hex
comma
l_int|2
)paren
suffix:semicolon
id|posn
op_add_assign
l_int|2
suffix:semicolon
op_star
(paren
id|posn
op_increment
)paren
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|strcpy
c_func
(paren
id|posn
comma
id|hex
op_plus
l_int|2
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
)paren
(brace
id|unlink
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fchmod
c_func
(paren
id|local
comma
l_int|0444
)paren
suffix:semicolon
id|close
c_func
(paren
id|local
)paren
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|SHA1_Final
c_func
(paren
id|real_sha1
comma
op_amp
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zret
op_ne
id|Z_STREAM_END
)paren
(brace
id|unlink
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;File %s (%s) corrupt&bslash;n&quot;
comma
id|hex
comma
id|url
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|sha1
comma
id|real_sha1
comma
l_int|20
)paren
)paren
(brace
id|unlink
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;File %s has bad hash&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|link
c_func
(paren
id|tmpfile
comma
id|filename
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
multiline_comment|/* Same Coda hack as in write_sha1_file(sha1_file.c) */
id|ret
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|EXDEV
op_logical_and
op_logical_neg
id|rename
c_func
(paren
id|tmpfile
comma
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
id|unlink
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_if
c_cond
(paren
id|ret
op_ne
id|EEXIST
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to write sha1 filename %s: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|ret
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|pull_say
c_func
(paren
l_string|&quot;got %s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch
r_int
id|fetch
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|alt_base
op_star
id|altbase
op_assign
id|alt
suffix:semicolon
r_while
c_loop
(paren
id|altbase
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fetch_object
c_func
(paren
id|altbase
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fetch_pack
c_func
(paren
id|altbase
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fetch_alternates
c_func
(paren
id|altbase-&gt;base
)paren
OG
l_int|0
)paren
(brace
id|altbase
op_assign
id|alt
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|altbase
op_assign
id|altbase-&gt;next
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;Unable to find %s under %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|initial_base
)paren
suffix:semicolon
)brace
DECL|function|fetch_ref
r_int
id|fetch_ref
c_func
(paren
r_char
op_star
id|ref
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|url
comma
op_star
id|posn
suffix:semicolon
r_char
id|hex
(braket
l_int|42
)braket
suffix:semicolon
r_struct
id|buffer
id|buffer
suffix:semicolon
r_char
op_star
id|base
op_assign
id|initial_base
suffix:semicolon
id|buffer.size
op_assign
l_int|41
suffix:semicolon
id|buffer.posn
op_assign
l_int|0
suffix:semicolon
id|buffer.buffer
op_assign
id|hex
suffix:semicolon
id|hex
(braket
l_int|41
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_FILE
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite_buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_HTTPHEADER
comma
l_int|NULL
)paren
suffix:semicolon
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base
)paren
op_plus
l_int|6
op_plus
id|strlen
c_func
(paren
id|ref
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|url
comma
id|base
)paren
suffix:semicolon
id|posn
op_assign
id|url
op_plus
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|posn
comma
l_string|&quot;refs/&quot;
)paren
suffix:semicolon
id|posn
op_add_assign
l_int|5
suffix:semicolon
id|strcpy
c_func
(paren
id|posn
comma
id|ref
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_easy_perform
c_func
(paren
id|curl
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t get %s for %s&bslash;n&quot;
comma
id|url
comma
id|ref
)paren
suffix:semicolon
id|hex
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
suffix:semicolon
r_return
l_int|0
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
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
op_star
id|commit_id
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_int
id|arg
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|arg
OL
id|argc
op_logical_and
id|argv
(braket
id|arg
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;t&squot;
)paren
(brace
id|get_tree
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;c&squot;
)paren
(brace
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;a&squot;
)paren
(brace
id|get_all
op_assign
l_int|1
suffix:semicolon
id|get_tree
op_assign
l_int|1
suffix:semicolon
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;v&squot;
)paren
(brace
id|get_verbosely
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;w&squot;
)paren
(brace
id|write_ref
op_assign
id|argv
(braket
id|arg
op_plus
l_int|1
)braket
suffix:semicolon
id|arg
op_increment
suffix:semicolon
)brace
id|arg
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
id|arg
op_plus
l_int|2
)paren
(brace
id|usage
c_func
(paren
l_string|&quot;git-http-fetch [-c] [-t] [-a] [-d] [-v] [--recover] [-w ref] commit-id url&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|commit_id
op_assign
id|argv
(braket
id|arg
)braket
suffix:semicolon
id|url
op_assign
id|argv
(braket
id|arg
op_plus
l_int|1
)braket
suffix:semicolon
id|curl_global_init
c_func
(paren
id|CURL_GLOBAL_ALL
)paren
suffix:semicolon
id|curl
op_assign
id|curl_easy_init
c_func
(paren
)paren
suffix:semicolon
id|no_pragma_header
op_assign
id|curl_slist_append
c_func
(paren
id|no_pragma_header
comma
l_string|&quot;Pragma:&quot;
)paren
suffix:semicolon
id|curl_ssl_verify
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSL_NO_VERIFY&quot;
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_SSL_VERIFYPEER
comma
id|curl_ssl_verify
)paren
suffix:semicolon
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070907
id|curl_easy_setopt
c_func
(paren
id|curl
comma
id|CURLOPT_NETRC
comma
id|CURL_NETRC_OPTIONAL
)paren
suffix:semicolon
macro_line|#endif
id|alt
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|alt
)paren
)paren
suffix:semicolon
id|alt-&gt;base
op_assign
id|url
suffix:semicolon
id|alt-&gt;got_indices
op_assign
l_int|0
suffix:semicolon
id|alt-&gt;packs
op_assign
l_int|NULL
suffix:semicolon
id|alt-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|initial_base
op_assign
id|url
suffix:semicolon
r_if
c_cond
(paren
id|pull
c_func
(paren
id|commit_id
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|curl_slist_free_all
c_func
(paren
id|no_pragma_header
)paren
suffix:semicolon
id|curl_global_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
