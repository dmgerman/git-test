multiline_comment|/*&n; * Simple random data generator used to create reproducible test files.&n; * This is inspired from POSIX.1-2001 implementation example for rand().&n; * Copyright (C) 2007 by Nicolas Pitre, licensed under the GPL version 2.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
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
r_int
r_int
id|count
comma
id|next
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
id|argc
template_param
l_int|3
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Usage: %s &lt;seed_string&gt; [&lt;size&gt;]&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|c
op_assign
(paren
r_int
r_char
op_star
)paren
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_do
(brace
id|next
op_assign
id|next
op_star
l_int|11
op_plus
op_star
id|c
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|c
op_increment
)paren
suffix:semicolon
id|count
op_assign
(paren
id|argc
op_eq
l_int|3
)paren
ques
c_cond
id|strtoul
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_int|NULL
comma
l_int|0
)paren
suffix:colon
l_int|1L
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|next
op_assign
id|next
op_star
l_int|1103515245
op_plus
l_int|12345
suffix:semicolon
r_if
c_cond
(paren
id|putchar
c_func
(paren
(paren
id|next
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
op_eq
id|EOF
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
