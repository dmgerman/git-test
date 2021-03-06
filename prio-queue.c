macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;prio-queue.h&quot;
DECL|function|compare
r_static
r_inline
r_int
id|compare
c_func
(paren
r_struct
id|prio_queue
op_star
id|queue
comma
r_int
id|i
comma
r_int
id|j
)paren
(brace
r_int
id|cmp
op_assign
id|queue
op_member_access_from_pointer
id|compare
c_func
(paren
id|queue-&gt;array
(braket
id|i
)braket
dot
id|data
comma
id|queue-&gt;array
(braket
id|j
)braket
dot
id|data
comma
id|queue-&gt;cb_data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
id|cmp
op_assign
id|queue-&gt;array
(braket
id|i
)braket
dot
id|ctr
id|queue-&gt;array
(braket
id|j
)braket
dot
id|ctr
suffix:semicolon
r_return
id|cmp
suffix:semicolon
)brace
DECL|function|swap
r_static
r_inline
r_void
id|swap
c_func
(paren
r_struct
id|prio_queue
op_star
id|queue
comma
r_int
id|i
comma
r_int
id|j
)paren
(brace
r_struct
id|prio_queue_entry
id|tmp
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
id|tmp
suffix:semicolon
)brace
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
id|swap
c_func
(paren
id|queue
comma
id|i
comma
id|j
)paren
suffix:semicolon
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
id|queue-&gt;insertion_ctr
op_assign
l_int|0
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
)braket
dot
id|ctr
op_assign
id|queue-&gt;insertion_ctr
op_increment
suffix:semicolon
id|queue-&gt;array
(braket
id|queue-&gt;nr
)braket
dot
id|data
op_assign
id|thing
suffix:semicolon
id|queue-&gt;nr
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue-&gt;compare
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
id|queue
comma
id|parent
comma
id|ix
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|swap
c_func
(paren
id|queue
comma
id|parent
comma
id|ix
)paren
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
suffix:semicolon
r_int
id|ix
comma
id|child
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
id|queue-&gt;compare
)paren
r_return
id|queue-&gt;array
(braket
op_decrement
id|queue-&gt;nr
)braket
dot
id|data
suffix:semicolon
multiline_comment|/* LIFO */
id|result
op_assign
id|queue-&gt;array
(braket
l_int|0
)braket
dot
id|data
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
id|child
op_plus
l_int|1
OL
id|queue-&gt;nr
op_logical_and
id|compare
c_func
(paren
id|queue
comma
id|child
comma
id|child
op_plus
l_int|1
)paren
op_ge
l_int|0
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
id|queue
comma
id|ix
comma
id|child
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|swap
c_func
(paren
id|queue
comma
id|child
comma
id|ix
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
eof
