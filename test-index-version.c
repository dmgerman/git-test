macro_line|#include &quot;cache.h&quot;
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
r_struct
id|cache_header
id|hdr
suffix:semicolon
r_int
id|version
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hdr
comma
l_int|0
comma
r_sizeof
(paren
id|hdr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
l_int|0
comma
op_amp
id|hdr
comma
r_sizeof
(paren
id|hdr
)paren
)paren
op_ne
r_sizeof
(paren
id|hdr
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|version
op_assign
id|ntohl
c_func
(paren
id|hdr.hdr_version
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
