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
r_int
id|i
suffix:semicolon
r_int
id|nr
suffix:semicolon
r_int
r_int
id|entry
(braket
l_int|6
)braket
suffix:semicolon
r_static
r_int
r_int
id|top_index
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
id|top_index
comma
r_sizeof
(paren
id|top_index
)paren
comma
l_int|1
comma
id|stdin
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;unable to read idex&quot;
)paren
suffix:semicolon
id|nr
op_assign
l_int|0
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|n
op_assign
id|ntohl
c_func
(paren
id|top_index
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|nr
)paren
id|die
c_func
(paren
l_string|&quot;corrupt index file&quot;
)paren
suffix:semicolon
id|nr
op_assign
id|n
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
id|entry
comma
l_int|24
comma
l_int|1
comma
id|stdin
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;unable to read entry %u/%u&quot;
comma
id|i
comma
id|nr
)paren
suffix:semicolon
id|offset
op_assign
id|ntohl
c_func
(paren
id|entry
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%u %s&bslash;n&quot;
comma
id|offset
comma
id|sha1_to_hex
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|entry
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
