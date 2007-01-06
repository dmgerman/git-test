multiline_comment|/*&n; * Copyright (c) 2005, Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|lock_file_list
r_static
r_struct
id|lock_file
op_star
id|lock_file_list
suffix:semicolon
DECL|function|remove_lock_file
r_static
r_void
id|remove_lock_file
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|lock_file_list
)paren
(brace
r_if
c_cond
(paren
id|lock_file_list-&gt;filename
(braket
l_int|0
)braket
)paren
id|unlink
c_func
(paren
id|lock_file_list-&gt;filename
)paren
suffix:semicolon
id|lock_file_list
op_assign
id|lock_file_list-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|remove_lock_file_on_signal
r_static
r_void
id|remove_lock_file_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_lock_file
c_func
(paren
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGINT
comma
id|SIG_DFL
)paren
suffix:semicolon
id|raise
c_func
(paren
id|signo
)paren
suffix:semicolon
)brace
DECL|function|lock_file
r_static
r_int
id|lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|fd
suffix:semicolon
id|sprintf
c_func
(paren
id|lk-&gt;filename
comma
l_string|&quot;%s.lock&quot;
comma
id|path
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|lk-&gt;filename
comma
id|O_RDWR
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
l_int|0
op_le
id|fd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lk-&gt;on_list
)paren
(brace
id|lk-&gt;next
op_assign
id|lock_file_list
suffix:semicolon
id|lock_file_list
op_assign
id|lk
suffix:semicolon
id|lk-&gt;on_list
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lock_file_list
)paren
(brace
id|signal
c_func
(paren
id|SIGINT
comma
id|remove_lock_file_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_lock_file
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|lk-&gt;filename
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot fix permission bits on %s&quot;
comma
id|lk-&gt;filename
)paren
suffix:semicolon
)brace
r_else
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|hold_lock_file_for_update
r_int
id|hold_lock_file_for_update
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
comma
r_const
r_char
op_star
id|path
comma
r_int
id|die_on_error
)paren
(brace
r_int
id|fd
op_assign
id|lock_file
c_func
(paren
id|lk
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_and
id|die_on_error
)paren
id|die
c_func
(paren
l_string|&quot;unable to create &squot;%s.lock&squot;: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|commit_lock_file
r_int
id|commit_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_char
id|result_file
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|strcpy
c_func
(paren
id|result_file
comma
id|lk-&gt;filename
)paren
suffix:semicolon
id|i
op_assign
id|strlen
c_func
(paren
id|result_file
)paren
l_int|5
suffix:semicolon
multiline_comment|/* .lock */
id|result_file
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
id|rename
c_func
(paren
id|lk-&gt;filename
comma
id|result_file
)paren
suffix:semicolon
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|rollback_lock_file
r_void
id|rollback_lock_file
c_func
(paren
r_struct
id|lock_file
op_star
id|lk
)paren
(brace
r_if
c_cond
(paren
id|lk-&gt;filename
(braket
l_int|0
)braket
)paren
id|unlink
c_func
(paren
id|lk-&gt;filename
)paren
suffix:semicolon
id|lk-&gt;filename
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
eof
