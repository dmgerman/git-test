macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;decorate.h&quot;
DECL|variable|track_object_refs
r_int
id|track_object_refs
op_assign
l_int|0
suffix:semicolon
DECL|variable|ref_decorate
r_static
r_struct
id|decoration
id|ref_decorate
suffix:semicolon
DECL|function|lookup_object_refs
r_struct
id|object_refs
op_star
id|lookup_object_refs
c_func
(paren
r_struct
id|object
op_star
id|base
)paren
(brace
r_return
id|lookup_decoration
c_func
(paren
op_amp
id|ref_decorate
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|add_object_refs
r_static
r_void
id|add_object_refs
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_struct
id|object_refs
op_star
id|refs
)paren
(brace
r_if
c_cond
(paren
id|add_decoration
c_func
(paren
op_amp
id|ref_decorate
comma
id|obj
comma
id|refs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;object %s tried to add refs twice!&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|alloc_object_refs
r_struct
id|object_refs
op_star
id|alloc_object_refs
c_func
(paren
r_int
id|count
)paren
(brace
r_struct
id|object_refs
op_star
id|refs
suffix:semicolon
r_int
id|size
op_assign
r_sizeof
(paren
op_star
id|refs
)paren
op_plus
id|count
op_star
r_sizeof
(paren
r_struct
id|object
op_star
)paren
suffix:semicolon
id|refs
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|size
)paren
suffix:semicolon
id|refs-&gt;count
op_assign
id|count
suffix:semicolon
r_return
id|refs
suffix:semicolon
)brace
DECL|function|compare_object_pointers
r_static
r_int
id|compare_object_pointers
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
r_const
r_struct
id|object
op_star
r_const
op_star
id|pa
op_assign
id|a
suffix:semicolon
r_const
r_struct
id|object
op_star
r_const
op_star
id|pb
op_assign
id|b
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pa
op_eq
op_star
id|pb
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|pa
OL
op_star
id|pb
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|set_object_refs
r_void
id|set_object_refs
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_struct
id|object_refs
op_star
id|refs
)paren
(brace
r_int
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* Do not install empty list of references */
r_if
c_cond
(paren
id|refs-&gt;count
OL
l_int|1
)paren
(brace
id|free
c_func
(paren
id|refs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Sort the list and filter out duplicates */
id|qsort
c_func
(paren
id|refs-&gt;ref
comma
id|refs-&gt;count
comma
r_sizeof
(paren
id|refs-&gt;ref
(braket
l_int|0
)braket
)paren
comma
id|compare_object_pointers
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|refs-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|refs-&gt;ref
(braket
id|i
)braket
op_ne
id|refs-&gt;ref
(braket
id|i
l_int|1
)braket
)paren
id|refs-&gt;ref
(braket
id|j
op_increment
)braket
op_assign
id|refs-&gt;ref
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
OL
id|refs-&gt;count
)paren
(brace
multiline_comment|/* Duplicates were found - reallocate list */
r_int
id|size
op_assign
r_sizeof
(paren
op_star
id|refs
)paren
op_plus
id|j
op_star
r_sizeof
(paren
r_struct
id|object
op_star
)paren
suffix:semicolon
id|refs-&gt;count
op_assign
id|j
suffix:semicolon
id|refs
op_assign
id|xrealloc
c_func
(paren
id|refs
comma
id|size
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|refs-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|refs-&gt;ref
(braket
id|i
)braket
op_member_access_from_pointer
id|used
op_assign
l_int|1
suffix:semicolon
id|add_object_refs
c_func
(paren
id|obj
comma
id|refs
)paren
suffix:semicolon
)brace
DECL|function|mark_reachable
r_void
id|mark_reachable
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_int
r_int
id|mask
)paren
(brace
r_const
r_struct
id|object_refs
op_star
id|refs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|track_object_refs
)paren
id|die
c_func
(paren
l_string|&quot;cannot do reachability with object refs turned off&quot;
)paren
suffix:semicolon
multiline_comment|/* If we&squot;ve been here already, don&squot;t bother */
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|mask
)paren
r_return
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|mask
suffix:semicolon
id|refs
op_assign
id|lookup_object_refs
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|refs
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
id|refs-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|mark_reachable
c_func
(paren
id|refs-&gt;ref
(braket
id|i
)braket
comma
id|mask
)paren
suffix:semicolon
)brace
)brace
eof
