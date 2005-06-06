macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;pull.h&quot;
macro_line|#include &lt;curl/curl.h&gt;
macro_line|#include &lt;curl/easy.h&gt;
DECL|variable|curl
r_static
id|CURL
op_star
id|curl
suffix:semicolon
DECL|variable|base
r_static
r_char
op_star
id|base
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
op_star
id|url
suffix:semicolon
r_char
op_star
id|posn
suffix:semicolon
id|local
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0666
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
l_string|&quot;Couldn&squot;t open %s&bslash;n&quot;
comma
id|filename
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
l_int|50
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
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t get %s for %s&bslash;n&quot;
comma
id|url
comma
id|hex
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
id|filename
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
id|filename
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
r_return
l_int|1
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
l_char|&squot;d&squot;
)paren
(brace
id|get_delta
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|arg
)braket
comma
l_string|&quot;--recover&quot;
)paren
)paren
(brace
id|get_delta
op_assign
l_int|2
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
l_string|&quot;git-http-pull [-c] [-t] [-a] [-d] [-v] [--recover] commit-id url&quot;
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
id|base
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
