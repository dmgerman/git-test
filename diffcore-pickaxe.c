multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;delta.h&quot;
DECL|function|contains
r_static
r_int
id|contains
c_func
(paren
r_struct
id|diff_filespec
op_star
id|one
comma
r_const
r_char
op_star
id|needle
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|offset
comma
id|sz
suffix:semicolon
r_const
r_char
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|one
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|sz
op_assign
id|one-&gt;size
suffix:semicolon
id|data
op_assign
id|one-&gt;data
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
op_plus
id|len
op_le
id|sz
suffix:semicolon
id|offset
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|needle
comma
id|data
op_plus
id|offset
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diffcore_pickaxe
r_void
id|diffcore_pickaxe
c_func
(paren
r_const
r_char
op_star
id|needle
)paren
(brace
r_struct
id|diff_queue_struct
op_star
id|q
op_assign
op_amp
id|diff_queued_diff
suffix:semicolon
r_int
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|needle
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|diff_queue_struct
id|outq
suffix:semicolon
id|outq.queue
op_assign
l_int|NULL
suffix:semicolon
id|outq.nr
op_assign
id|outq.alloc
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
r_int
id|onum
op_assign
id|outq.nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* ignore nonsense */
multiline_comment|/* created */
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;two
comma
id|needle
comma
id|len
)paren
)paren
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
(brace
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;one
comma
id|needle
comma
id|len
)paren
)paren
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;one
comma
id|needle
comma
id|len
)paren
op_ne
id|contains
c_func
(paren
id|p-&gt;two
comma
id|needle
comma
id|len
)paren
)paren
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|onum
op_eq
id|outq.nr
)paren
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|q-&gt;queue
)paren
suffix:semicolon
op_star
id|q
op_assign
id|outq
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
