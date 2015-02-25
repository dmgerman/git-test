multiline_comment|/*&n; * Builtin &quot;git interpret-trailers&quot;&n; *&n; * Copyright (c) 2013, 2014 Christian Couder &lt;chriscool@tuxfamily.org&gt;&n; *&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;trailer.h&quot;
DECL|variable|git_interpret_trailers_usage
r_static
r_const
r_char
op_star
r_const
id|git_interpret_trailers_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git interpret-trailers [--trim-empty] [(--trailer &lt;token&gt;[(=|:)&lt;value&gt;])...] [&lt;file&gt;...]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_interpret_trailers
r_int
id|cmd_interpret_trailers
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
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|trim_empty
op_assign
l_int|0
suffix:semicolon
r_struct
id|string_list
id|trailers
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;trim-empty&quot;
comma
op_amp
id|trim_empty
comma
id|N_
c_func
(paren
l_string|&quot;trim empty trailers&quot;
)paren
)paren
comma
id|OPT_STRING_LIST
c_func
(paren
l_int|0
comma
l_string|&quot;trailer&quot;
comma
op_amp
id|trailers
comma
id|N_
c_func
(paren
l_string|&quot;trailer&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;trailer(s) to add&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|options
comma
id|git_interpret_trailers_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
)paren
(brace
r_int
id|i
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
id|process_trailers
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|trim_empty
comma
op_amp
id|trailers
)paren
suffix:semicolon
)brace
r_else
id|process_trailers
c_func
(paren
l_int|NULL
comma
id|trim_empty
comma
op_amp
id|trailers
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|trailers
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof