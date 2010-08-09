multiline_comment|/*&n; * test-obj-pool.c: code to exercise the svn importer&squot;s object pool&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;vcs-svn/obj_pool.h&quot;
DECL|enum|pool
DECL|enumerator|POOL_ONE
DECL|enumerator|POOL_TWO
r_enum
id|pool
(brace
id|POOL_ONE
comma
id|POOL_TWO
)brace
suffix:semicolon
id|obj_pool_gen
c_func
(paren
id|one
comma
r_int
comma
l_int|1
)paren
id|obj_pool_gen
c_func
(paren
id|two
comma
r_int
comma
l_int|4096
)paren
DECL|function|strtouint32
r_static
r_uint32
id|strtouint32
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_uintmax
id|n
op_assign
id|strtoumax
c_func
(paren
id|s
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
(paren
op_star
id|end
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
op_star
id|end
op_ne
l_char|&squot;&bslash;0&squot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;invalid offset: %s&quot;
comma
id|s
)paren
suffix:semicolon
r_return
(paren
r_uint32
)paren
id|n
suffix:semicolon
)brace
DECL|function|handle_command
r_static
r_void
id|handle_command
c_func
(paren
r_const
r_char
op_star
id|command
comma
r_enum
id|pool
id|pool
comma
r_const
r_char
op_star
id|arg
)paren
(brace
r_switch
c_cond
(paren
op_star
id|command
)paren
(brace
r_case
l_char|&squot;a&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;alloc &quot;
)paren
)paren
(brace
r_uint32
id|n
op_assign
id|strtouint32
c_func
(paren
id|arg
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_alloc
c_func
(paren
id|n
)paren
suffix:colon
id|two_alloc
c_func
(paren
id|n
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;commit &quot;
)paren
)paren
(brace
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_commit
c_func
(paren
)paren
suffix:colon
id|two_commit
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;committed &quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_pool.committed
suffix:colon
id|two_pool.committed
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;f&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;free &quot;
)paren
)paren
(brace
r_uint32
id|n
op_assign
id|strtouint32
c_func
(paren
id|arg
)paren
suffix:semicolon
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_free
c_func
(paren
id|n
)paren
suffix:colon
id|two_free
c_func
(paren
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;n&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;null &quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_offset
c_func
(paren
l_int|NULL
)paren
suffix:colon
id|two_offset
c_func
(paren
l_int|NULL
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;o&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;offset &quot;
)paren
)paren
(brace
r_uint32
id|n
op_assign
id|strtouint32
c_func
(paren
id|arg
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%&quot;
id|PRIu32
l_string|&quot;&bslash;n&quot;
comma
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_offset
c_func
(paren
id|one_pointer
c_func
(paren
id|n
)paren
)paren
suffix:colon
id|two_offset
c_func
(paren
id|two_pointer
c_func
(paren
id|n
)paren
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;r&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;reset &quot;
)paren
)paren
(brace
id|pool
op_eq
id|POOL_ONE
ques
c_cond
id|one_reset
c_func
(paren
)paren
suffix:colon
id|two_reset
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;s&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;set &quot;
)paren
)paren
(brace
r_uint32
id|n
op_assign
id|strtouint32
c_func
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool
op_eq
id|POOL_ONE
)paren
op_star
id|one_pointer
c_func
(paren
id|n
)paren
op_assign
l_int|1
suffix:semicolon
r_else
op_star
id|two_pointer
c_func
(paren
id|n
)paren
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
l_char|&squot;t&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|command
comma
l_string|&quot;test &quot;
)paren
)paren
(brace
r_uint32
id|n
op_assign
id|strtouint32
c_func
(paren
id|arg
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|pool
op_eq
id|POOL_ONE
ques
c_cond
op_star
id|one_pointer
c_func
(paren
id|n
)paren
suffix:colon
op_star
id|two_pointer
c_func
(paren
id|n
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;unrecognized command: %s&quot;
comma
id|command
)paren
suffix:semicolon
)brace
)brace
DECL|function|handle_line
r_static
r_void
id|handle_line
c_func
(paren
r_const
r_char
op_star
id|line
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_enum
id|pool
id|pool
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
op_plus
l_int|1
comma
l_string|&quot;one&quot;
)paren
)paren
id|pool
op_assign
id|POOL_ONE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|arg
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
op_plus
l_int|1
comma
l_string|&quot;two&quot;
)paren
)paren
id|pool
op_assign
id|POOL_TWO
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;no pool specified: %s&quot;
comma
id|line
)paren
suffix:semicolon
id|handle_command
c_func
(paren
id|line
comma
id|pool
comma
id|arg
op_plus
id|strlen
c_func
(paren
l_string|&quot;one &quot;
)paren
)paren
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
id|argv
(braket
)braket
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage
c_func
(paren
l_string|&quot;test-obj-str &lt; script&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
id|handle_line
c_func
(paren
id|sb.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
