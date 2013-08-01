macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;prio-queue.h&quot;
DECL|function|prio_queue_reverse
r_void
id|prio_queue_reverse
c_func
(paren
r_struct
id|prio_queue
op_star
id|queue
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;compare
op_ne
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;BUG: prio_queue_reverse() on non-LIFO queue&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
(paren
id|j
op_assign
(paren
id|queue-&gt;nr
l_int|1
)paren
id|i
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|commit
op_star
id|swap
op_assign
id|queue-&gt;array
(braket
id|i
)braket
suffix:semicolon
id|queue-&gt;array
(braket
id|i
)braket
op_assign
id|queue-&gt;array
(braket
id|j
)braket
suffix:semicolon
id|queue-&gt;array
(braket
id|j
)braket
op_assign
id|swap
suffix:semicolon
)brace
)brace
DECL|function|clear_prio_queue
r_void
id|clear_prio_queue
c_func
(paren
r_struct
id|prio_queue
op_star
id|queue
)paren
(brace
id|free
c_func
(paren
id|queue-&gt;array
)paren
suffix:semicolon
id|queue-&gt;nr
op_assign
l_int|0
suffix:semicolon
id|queue-&gt;alloc
op_assign
l_int|0
suffix:semicolon
id|queue-&gt;array
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|prio_queue_put
r_void
id|prio_queue_put
c_func
(paren
r_struct
id|prio_queue
op_star
id|queue
comma
r_void
op_star
id|thing
)paren
(brace
id|prio_queue_compare_fn
id|compare
op_assign
id|queue-&gt;compare
suffix:semicolon
r_int
id|ix
comma
id|parent
suffix:semicolon
multiline_comment|/* Append at the end */
id|ALLOC_GROW
c_func
(paren
id|queue-&gt;array
comma
id|queue-&gt;nr
op_plus
l_int|1
comma
id|queue-&gt;alloc
)paren
suffix:semicolon
id|queue-&gt;array
(braket
id|queue-&gt;nr
op_increment
)braket
op_assign
id|thing
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|compare
)paren
r_return
suffix:semicolon
multiline_comment|/* LIFO */
multiline_comment|/* Bubble up the new one */
r_for
c_loop
(paren
id|ix
op_assign
id|queue-&gt;nr
l_int|1
suffix:semicolon
id|ix
suffix:semicolon
id|ix
op_assign
id|parent
)paren
(brace
id|parent
op_assign
(paren
id|ix
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|compare
c_func
(paren
id|queue-&gt;array
(braket
id|parent
)braket
comma
id|queue-&gt;array
(braket
id|ix
)braket
comma
id|queue-&gt;cb_data
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|thing
op_assign
id|queue-&gt;array
(braket
id|parent
)braket
suffix:semicolon
id|queue-&gt;array
(braket
id|parent
)braket
op_assign
id|queue-&gt;array
(braket
id|ix
)braket
suffix:semicolon
id|queue-&gt;array
(braket
id|ix
)braket
op_assign
id|thing
suffix:semicolon
)brace
)brace
DECL|function|prio_queue_get
r_void
op_star
id|prio_queue_get
c_func
(paren
r_struct
id|prio_queue
op_star
id|queue
)paren
(brace
r_void
op_star
id|result
comma
op_star
id|swap
suffix:semicolon
r_int
id|ix
comma
id|child
suffix:semicolon
id|prio_queue_compare_fn
id|compare
op_assign
id|queue-&gt;compare
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue-&gt;nr
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|compare
)paren
r_return
id|queue-&gt;array
(braket
op_decrement
id|queue-&gt;nr
)braket
suffix:semicolon
multiline_comment|/* LIFO */
id|result
op_assign
id|queue-&gt;array
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|queue-&gt;nr
)paren
r_return
id|result
suffix:semicolon
id|queue-&gt;array
(braket
l_int|0
)braket
op_assign
id|queue-&gt;array
(braket
id|queue-&gt;nr
)braket
suffix:semicolon
multiline_comment|/* Push down the one at the root */
r_for
c_loop
(paren
id|ix
op_assign
l_int|0
suffix:semicolon
id|ix
op_star
l_int|2
op_plus
l_int|1
OL
id|queue-&gt;nr
suffix:semicolon
id|ix
op_assign
id|child
)paren
(brace
id|child
op_assign
id|ix
op_star
l_int|2
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* left */
r_if
c_cond
(paren
(paren
id|child
op_plus
l_int|1
OL
id|queue-&gt;nr
)paren
op_logical_and
(paren
id|compare
c_func
(paren
id|queue-&gt;array
(braket
id|child
)braket
comma
id|queue-&gt;array
(braket
id|child
op_plus
l_int|1
)braket
comma
id|queue-&gt;cb_data
)paren
op_ge
l_int|0
)paren
)paren
id|child
op_increment
suffix:semicolon
multiline_comment|/* use right child */
r_if
c_cond
(paren
id|compare
c_func
(paren
id|queue-&gt;array
(braket
id|ix
)braket
comma
id|queue-&gt;array
(braket
id|child
)braket
comma
id|queue-&gt;cb_data
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|swap
op_assign
id|queue-&gt;array
(braket
id|child
)braket
suffix:semicolon
id|queue-&gt;array
(braket
id|child
)braket
op_assign
id|queue-&gt;array
(braket
id|ix
)braket
suffix:semicolon
id|queue-&gt;array
(braket
id|ix
)braket
op_assign
id|swap
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
eof