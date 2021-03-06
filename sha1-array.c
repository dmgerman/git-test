macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;sha1-array.h&quot;
macro_line|#include &quot;sha1-lookup.h&quot;
DECL|function|sha1_array_append
r_void
id|sha1_array_append
c_func
(paren
r_struct
id|sha1_array
op_star
id|array
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|array-&gt;sha1
comma
id|array-&gt;nr
op_plus
l_int|1
comma
id|array-&gt;alloc
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|array-&gt;sha1
(braket
id|array-&gt;nr
op_increment
)braket
comma
id|sha1
)paren
suffix:semicolon
id|array-&gt;sorted
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|void_hashcmp
r_static
r_int
id|void_hashcmp
c_func
(paren
r_const
r_void
op_star
id|a
comma
r_const
r_void
op_star
id|b
)paren
(brace
r_return
id|hashcmp
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
)brace
DECL|function|sha1_array_sort
r_static
r_void
id|sha1_array_sort
c_func
(paren
r_struct
id|sha1_array
op_star
id|array
)paren
(brace
id|qsort
c_func
(paren
id|array-&gt;sha1
comma
id|array-&gt;nr
comma
r_sizeof
(paren
op_star
id|array-&gt;sha1
)paren
comma
id|void_hashcmp
)paren
suffix:semicolon
id|array-&gt;sorted
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|sha1_access
r_static
r_const
r_int
r_char
op_star
id|sha1_access
c_func
(paren
r_int
id|index
comma
r_void
op_star
id|table
)paren
(brace
r_int
r_char
(paren
op_star
id|array
)paren
(braket
l_int|20
)braket
op_assign
id|table
suffix:semicolon
r_return
id|array
(braket
id|index
)braket
suffix:semicolon
)brace
DECL|function|sha1_array_lookup
r_int
id|sha1_array_lookup
c_func
(paren
r_struct
id|sha1_array
op_star
id|array
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|array-&gt;sorted
)paren
id|sha1_array_sort
c_func
(paren
id|array
)paren
suffix:semicolon
r_return
id|sha1_pos
c_func
(paren
id|sha1
comma
id|array-&gt;sha1
comma
id|array-&gt;nr
comma
id|sha1_access
)paren
suffix:semicolon
)brace
DECL|function|sha1_array_clear
r_void
id|sha1_array_clear
c_func
(paren
r_struct
id|sha1_array
op_star
id|array
)paren
(brace
id|free
c_func
(paren
id|array-&gt;sha1
)paren
suffix:semicolon
id|array-&gt;sha1
op_assign
l_int|NULL
suffix:semicolon
id|array-&gt;nr
op_assign
l_int|0
suffix:semicolon
id|array-&gt;alloc
op_assign
l_int|0
suffix:semicolon
id|array-&gt;sorted
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|sha1_array_for_each_unique
r_void
id|sha1_array_for_each_unique
c_func
(paren
r_struct
id|sha1_array
op_star
id|array
comma
id|for_each_sha1_fn
id|fn
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|array-&gt;sorted
)paren
id|sha1_array_sort
c_func
(paren
id|array
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
OL
id|array-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OG
l_int|0
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|array-&gt;sha1
(braket
id|i
)braket
comma
id|array-&gt;sha1
(braket
id|i
op_minus
l_int|1
)braket
)paren
)paren
r_continue
suffix:semicolon
id|fn
c_func
(paren
id|array-&gt;sha1
(braket
id|i
)braket
comma
id|data
)paren
suffix:semicolon
)brace
)brace
eof
