macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;string-list.h&quot;
multiline_comment|/* if there is no exact match, point to the index where the entry could be&n; * inserted */
DECL|function|get_entry_index
r_static
r_int
id|get_entry_index
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
comma
r_int
op_star
id|exact_match
)paren
(brace
r_int
id|left
op_assign
l_int|1
comma
id|right
op_assign
id|list-&gt;nr
suffix:semicolon
r_while
c_loop
(paren
id|left
op_plus
l_int|1
OL
id|right
)paren
(brace
r_int
id|middle
op_assign
(paren
id|left
op_plus
id|right
)paren
op_div
l_int|2
suffix:semicolon
r_int
id|compare
op_assign
id|strcmp
c_func
(paren
id|string
comma
id|list-&gt;items
(braket
id|middle
)braket
dot
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compare
OL
l_int|0
)paren
id|right
op_assign
id|middle
suffix:semicolon
r_else
r_if
c_cond
(paren
id|compare
OG
l_int|0
)paren
id|left
op_assign
id|middle
suffix:semicolon
r_else
(brace
op_star
id|exact_match
op_assign
l_int|1
suffix:semicolon
r_return
id|middle
suffix:semicolon
)brace
)brace
op_star
id|exact_match
op_assign
l_int|0
suffix:semicolon
r_return
id|right
suffix:semicolon
)brace
multiline_comment|/* returns -1-index if already exists */
DECL|function|add_entry
r_static
r_int
id|add_entry
c_func
(paren
r_int
id|insert_at
comma
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|exact_match
op_assign
l_int|0
suffix:semicolon
r_int
id|index
op_assign
id|insert_at
op_ne
l_int|1
ques
c_cond
id|insert_at
suffix:colon
id|get_entry_index
c_func
(paren
id|list
comma
id|string
comma
op_amp
id|exact_match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exact_match
)paren
r_return
l_int|1
id|index
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;nr
op_plus
l_int|1
op_ge
id|list-&gt;alloc
)paren
(brace
id|list-&gt;alloc
op_add_assign
l_int|32
suffix:semicolon
id|list-&gt;items
op_assign
id|xrealloc
c_func
(paren
id|list-&gt;items
comma
id|list-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|string_list_item
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index
OL
id|list-&gt;nr
)paren
id|memmove
c_func
(paren
id|list-&gt;items
op_plus
id|index
op_plus
l_int|1
comma
id|list-&gt;items
op_plus
id|index
comma
(paren
id|list-&gt;nr
id|index
)paren
op_star
r_sizeof
(paren
r_struct
id|string_list_item
)paren
)paren
suffix:semicolon
id|list-&gt;items
(braket
id|index
)braket
dot
id|string
op_assign
id|list-&gt;strdup_strings
ques
c_cond
id|xstrdup
c_func
(paren
id|string
)paren
suffix:colon
(paren
r_char
op_star
)paren
id|string
suffix:semicolon
id|list-&gt;items
(braket
id|index
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
id|list-&gt;nr
op_increment
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
DECL|function|string_list_insert
r_struct
id|string_list_item
op_star
id|string_list_insert
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_return
id|string_list_insert_at_index
c_func
(paren
id|list
comma
l_int|1
comma
id|string
)paren
suffix:semicolon
)brace
DECL|function|string_list_insert_at_index
r_struct
id|string_list_item
op_star
id|string_list_insert_at_index
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_int
id|insert_at
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|index
op_assign
id|add_entry
c_func
(paren
id|insert_at
comma
id|list
comma
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
)paren
id|index
op_assign
l_int|1
id|index
suffix:semicolon
r_return
id|list-&gt;items
op_plus
id|index
suffix:semicolon
)brace
DECL|function|string_list_has_string
r_int
id|string_list_has_string
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|exact_match
suffix:semicolon
id|get_entry_index
c_func
(paren
id|list
comma
id|string
comma
op_amp
id|exact_match
)paren
suffix:semicolon
r_return
id|exact_match
suffix:semicolon
)brace
DECL|function|string_list_find_insert_index
r_int
id|string_list_find_insert_index
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
comma
r_int
id|negative_existing_index
)paren
(brace
r_int
id|exact_match
suffix:semicolon
r_int
id|index
op_assign
id|get_entry_index
c_func
(paren
id|list
comma
id|string
comma
op_amp
id|exact_match
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exact_match
)paren
id|index
op_assign
l_int|1
(paren
id|negative_existing_index
ques
c_cond
id|index
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
DECL|function|string_list_lookup
r_struct
id|string_list_item
op_star
id|string_list_lookup
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|exact_match
comma
id|i
op_assign
id|get_entry_index
c_func
(paren
id|list
comma
id|string
comma
op_amp
id|exact_match
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exact_match
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|list-&gt;items
op_plus
id|i
suffix:semicolon
)brace
DECL|function|for_each_string_list
r_int
id|for_each_string_list
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
id|string_list_each_func_t
id|fn
comma
r_void
op_star
id|cb_data
)paren
(brace
r_int
id|i
comma
id|ret
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
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|fn
c_func
(paren
op_amp
id|list-&gt;items
(braket
id|i
)braket
comma
id|cb_data
)paren
)paren
)paren
r_break
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|string_list_clear
r_void
id|string_list_clear
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_int
id|free_util
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;items
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;strdup_strings
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|free_util
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|list-&gt;items
(braket
id|i
)braket
dot
id|util
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|list-&gt;items
)paren
suffix:semicolon
)brace
id|list-&gt;items
op_assign
l_int|NULL
suffix:semicolon
id|list-&gt;nr
op_assign
id|list-&gt;alloc
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|string_list_clear_func
r_void
id|string_list_clear_func
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
id|string_list_clear_func_t
id|clearfunc
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;items
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|clearfunc
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|clearfunc
c_func
(paren
id|list-&gt;items
(braket
id|i
)braket
dot
id|util
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list-&gt;strdup_strings
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|list-&gt;items
)paren
suffix:semicolon
)brace
id|list-&gt;items
op_assign
l_int|NULL
suffix:semicolon
id|list-&gt;nr
op_assign
id|list-&gt;alloc
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|print_string_list
r_void
id|print_string_list
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|p
comma
r_const
r_char
op_star
id|text
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|text
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|text
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
id|p-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s:%p&bslash;n&quot;
comma
id|p-&gt;items
(braket
id|i
)braket
dot
id|string
comma
id|p-&gt;items
(braket
id|i
)braket
dot
id|util
)paren
suffix:semicolon
)brace
DECL|function|string_list_append
r_struct
id|string_list_item
op_star
id|string_list_append
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|list-&gt;items
comma
id|list-&gt;nr
op_plus
l_int|1
comma
id|list-&gt;alloc
)paren
suffix:semicolon
id|list-&gt;items
(braket
id|list-&gt;nr
)braket
dot
id|string
op_assign
id|list-&gt;strdup_strings
ques
c_cond
id|xstrdup
c_func
(paren
id|string
)paren
suffix:colon
(paren
r_char
op_star
)paren
id|string
suffix:semicolon
r_return
id|list-&gt;items
op_plus
id|list-&gt;nr
op_increment
suffix:semicolon
)brace
DECL|function|cmp_items
r_static
r_int
id|cmp_items
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
id|string_list_item
op_star
id|one
op_assign
id|a
suffix:semicolon
r_const
r_struct
id|string_list_item
op_star
id|two
op_assign
id|b
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|one-&gt;string
comma
id|two-&gt;string
)paren
suffix:semicolon
)brace
DECL|function|sort_string_list
r_void
id|sort_string_list
c_func
(paren
r_struct
id|string_list
op_star
id|list
)paren
(brace
id|qsort
c_func
(paren
id|list-&gt;items
comma
id|list-&gt;nr
comma
r_sizeof
(paren
op_star
id|list-&gt;items
)paren
comma
id|cmp_items
)paren
suffix:semicolon
)brace
DECL|function|unsorted_string_list_lookup
r_struct
id|string_list_item
op_star
id|unsorted_string_list_lookup
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
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
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|string
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
)paren
r_return
id|list-&gt;items
op_plus
id|i
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|unsorted_string_list_has_string
r_int
id|unsorted_string_list_has_string
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_return
id|unsorted_string_list_lookup
c_func
(paren
id|list
comma
id|string
)paren
op_ne
l_int|NULL
suffix:semicolon
)brace
eof
