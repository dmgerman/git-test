multiline_comment|/*&n; * test-delta.c: test code to exercise diff-delta.c and patch-delta.c&n; *&n; * (C) 2005 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &quot;delta.h&quot;
DECL|variable|usage
r_static
r_const
r_char
id|usage
(braket
)braket
op_assign
l_string|&quot;test-delta (-d|-p) &lt;from_file&gt; &lt;data_file&gt; &lt;out_file&gt;&quot;
suffix:semicolon
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
id|fd
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_void
op_star
id|from_buf
comma
op_star
id|data_buf
comma
op_star
id|out_buf
suffix:semicolon
r_int
r_int
id|from_size
comma
id|data_size
comma
id|out_size
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|5
op_logical_or
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-d&quot;
)paren
op_logical_and
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-p&quot;
)paren
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Usage: %s&bslash;n&quot;
comma
id|usage
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fd
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|from_size
op_assign
id|st.st_size
suffix:semicolon
id|from_buf
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|from_size
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_buf
op_eq
id|MAP_FAILED
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|3
)braket
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|data_size
op_assign
id|st.st_size
suffix:semicolon
id|data_buf
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|data_size
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data_buf
op_eq
id|MAP_FAILED
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;d&squot;
)paren
id|out_buf
op_assign
id|diff_delta
c_func
(paren
id|from_buf
comma
id|from_size
comma
id|data_buf
comma
id|data_size
comma
op_amp
id|out_size
comma
l_int|0
)paren
suffix:semicolon
r_else
id|out_buf
op_assign
id|patch_delta
c_func
(paren
id|from_buf
comma
id|from_size
comma
id|data_buf
comma
id|data_size
comma
op_amp
id|out_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out_buf
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;delta operation failed (returned NULL)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fd
op_assign
id|open
(paren
id|argv
(braket
l_int|4
)braket
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_TRUNC
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|write
c_func
(paren
id|fd
comma
id|out_buf
comma
id|out_size
)paren
op_ne
id|out_size
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
