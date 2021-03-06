macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;mergesort.h&quot;
DECL|struct|mergesort_sublist
r_struct
id|mergesort_sublist
(brace
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_nth_next
r_static
r_void
op_star
id|get_nth_next
c_func
(paren
r_void
op_star
id|list
comma
r_int
r_int
id|n
comma
r_void
op_star
(paren
op_star
id|get_next_fn
)paren
(paren
r_const
r_void
op_star
)paren
)paren
(brace
r_while
c_loop
(paren
id|n
op_decrement
op_logical_and
id|list
)paren
id|list
op_assign
id|get_next_fn
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
DECL|function|pop_item
r_static
r_void
op_star
id|pop_item
c_func
(paren
r_struct
id|mergesort_sublist
op_star
id|l
comma
r_void
op_star
(paren
op_star
id|get_next_fn
)paren
(paren
r_const
r_void
op_star
)paren
)paren
(brace
r_void
op_star
id|p
op_assign
id|l-&gt;ptr
suffix:semicolon
id|l-&gt;ptr
op_assign
id|get_next_fn
c_func
(paren
id|l-&gt;ptr
)paren
suffix:semicolon
id|l-&gt;len
op_assign
id|l-&gt;ptr
ques
c_cond
(paren
id|l-&gt;len
l_int|1
)paren
suffix:colon
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|llist_mergesort
r_void
op_star
id|llist_mergesort
c_func
(paren
r_void
op_star
id|list
comma
r_void
op_star
(paren
op_star
id|get_next_fn
)paren
(paren
r_const
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|set_next_fn
)paren
(paren
r_void
op_star
comma
r_void
op_star
)paren
comma
r_int
(paren
op_star
id|compare_fn
)paren
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
)paren
)paren
(brace
r_int
r_int
id|l
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|1
suffix:semicolon
suffix:semicolon
id|l
op_mul_assign
l_int|2
)paren
(brace
r_void
op_star
id|curr
suffix:semicolon
r_struct
id|mergesort_sublist
id|p
comma
id|q
suffix:semicolon
id|p.ptr
op_assign
id|list
suffix:semicolon
id|q.ptr
op_assign
id|get_nth_next
c_func
(paren
id|p.ptr
comma
id|l
comma
id|get_next_fn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q.ptr
)paren
r_break
suffix:semicolon
id|p.len
op_assign
id|q.len
op_assign
id|l
suffix:semicolon
r_if
c_cond
(paren
id|compare_fn
c_func
(paren
id|p.ptr
comma
id|q.ptr
)paren
OG
l_int|0
)paren
id|list
op_assign
id|curr
op_assign
id|pop_item
c_func
(paren
op_amp
id|q
comma
id|get_next_fn
)paren
suffix:semicolon
r_else
id|list
op_assign
id|curr
op_assign
id|pop_item
c_func
(paren
op_amp
id|p
comma
id|get_next_fn
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p.ptr
)paren
(brace
r_while
c_loop
(paren
id|p.len
op_logical_or
id|q.len
)paren
(brace
r_void
op_star
id|prev
op_assign
id|curr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p.len
)paren
id|curr
op_assign
id|pop_item
c_func
(paren
op_amp
id|q
comma
id|get_next_fn
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|q.len
)paren
id|curr
op_assign
id|pop_item
c_func
(paren
op_amp
id|p
comma
id|get_next_fn
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|compare_fn
c_func
(paren
id|p.ptr
comma
id|q.ptr
)paren
OG
l_int|0
)paren
id|curr
op_assign
id|pop_item
c_func
(paren
op_amp
id|q
comma
id|get_next_fn
)paren
suffix:semicolon
r_else
id|curr
op_assign
id|pop_item
c_func
(paren
op_amp
id|p
comma
id|get_next_fn
)paren
suffix:semicolon
id|set_next_fn
c_func
(paren
id|prev
comma
id|curr
)paren
suffix:semicolon
)brace
id|p.ptr
op_assign
id|q.ptr
suffix:semicolon
id|p.len
op_assign
id|l
suffix:semicolon
id|q.ptr
op_assign
id|get_nth_next
c_func
(paren
id|p.ptr
comma
id|l
comma
id|get_next_fn
)paren
suffix:semicolon
id|q.len
op_assign
id|q.ptr
ques
c_cond
id|l
suffix:colon
l_int|0
suffix:semicolon
)brace
id|set_next_fn
c_func
(paren
id|curr
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|list
suffix:semicolon
)brace
eof
