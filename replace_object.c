macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;sha1-lookup.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
multiline_comment|/*&n; * An array of replacements.  The array is kept sorted by the original&n; * sha1.&n; */
DECL|struct|replace_object
r_static
r_struct
id|replace_object
(brace
DECL|member|original
r_int
r_char
id|original
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|replacement
r_int
r_char
id|replacement
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|replace_object
)brace
op_star
op_star
id|replace_object
suffix:semicolon
DECL|variable|replace_object_alloc
DECL|variable|replace_object_nr
r_static
r_int
id|replace_object_alloc
comma
id|replace_object_nr
suffix:semicolon
DECL|function|replace_sha1_access
r_static
r_const
r_int
r_char
op_star
id|replace_sha1_access
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
r_struct
id|replace_object
op_star
op_star
id|replace
op_assign
id|table
suffix:semicolon
r_return
id|replace
(braket
id|index
)braket
op_member_access_from_pointer
id|original
suffix:semicolon
)brace
DECL|function|replace_object_pos
r_static
r_int
id|replace_object_pos
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_return
id|sha1_pos
c_func
(paren
id|sha1
comma
id|replace_object
comma
id|replace_object_nr
comma
id|replace_sha1_access
)paren
suffix:semicolon
)brace
DECL|function|register_replace_object
r_static
r_int
id|register_replace_object
c_func
(paren
r_struct
id|replace_object
op_star
id|replace
comma
r_int
id|ignore_dups
)paren
(brace
r_int
id|pos
op_assign
id|replace_object_pos
c_func
(paren
id|replace-&gt;original
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
(brace
r_if
c_cond
(paren
id|ignore_dups
)paren
id|free
c_func
(paren
id|replace
)paren
suffix:semicolon
r_else
(brace
id|free
c_func
(paren
id|replace_object
(braket
id|pos
)braket
)paren
suffix:semicolon
id|replace_object
(braket
id|pos
)braket
op_assign
id|replace
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|replace_object
comma
id|replace_object_nr
op_plus
l_int|1
comma
id|replace_object_alloc
)paren
suffix:semicolon
id|replace_object_nr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|replace_object_nr
)paren
id|memmove
c_func
(paren
id|replace_object
op_plus
id|pos
op_plus
l_int|1
comma
id|replace_object
op_plus
id|pos
comma
(paren
id|replace_object_nr
id|pos
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|replace_object
)paren
)paren
suffix:semicolon
id|replace_object
(braket
id|pos
)braket
op_assign
id|replace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|register_replace_ref
r_static
r_int
id|register_replace_ref
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
multiline_comment|/* Get sha1 from refname */
r_const
r_char
op_star
id|slash
op_assign
id|strrchr
c_func
(paren
id|refname
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|hash
op_assign
id|slash
ques
c_cond
id|slash
op_plus
l_int|1
suffix:colon
id|refname
suffix:semicolon
r_struct
id|replace_object
op_star
id|repl_obj
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|repl_obj
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|hash
)paren
op_ne
l_int|40
op_logical_or
id|get_sha1_hex
c_func
(paren
id|hash
comma
id|repl_obj-&gt;original
)paren
)paren
(brace
id|free
c_func
(paren
id|repl_obj
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;bad replace ref name: %s&quot;
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Copy sha1 from the read ref */
id|hashcpy
c_func
(paren
id|repl_obj-&gt;replacement
comma
id|sha1
)paren
suffix:semicolon
multiline_comment|/* Register new object */
r_if
c_cond
(paren
id|register_replace_object
c_func
(paren
id|repl_obj
comma
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;duplicate replace ref: %s&quot;
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prepare_replace_object
r_static
r_void
id|prepare_replace_object
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|replace_object_prepared
suffix:semicolon
r_if
c_cond
(paren
id|replace_object_prepared
)paren
r_return
suffix:semicolon
id|for_each_replace_ref
c_func
(paren
id|register_replace_ref
comma
l_int|NULL
)paren
suffix:semicolon
id|replace_object_prepared
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|replace_object_nr
)paren
id|check_replace_refs
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We allow &quot;recursive&quot; replacement. Only within reason, though */
DECL|macro|MAXREPLACEDEPTH
mdefine_line|#define MAXREPLACEDEPTH 5
multiline_comment|/*&n; * If a replacement for object sha1 has been set up, return the&n; * replacement object&squot;s name (replaced recursively, if necessary).&n; * The return value is either sha1 or a pointer to a&n; * permanently-allocated value.  This function always respects replace&n; * references, regardless of the value of check_replace_refs.&n; */
DECL|function|do_lookup_replace_object
r_const
r_int
r_char
op_star
id|do_lookup_replace_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|pos
comma
id|depth
op_assign
id|MAXREPLACEDEPTH
suffix:semicolon
r_const
r_int
r_char
op_star
id|cur
op_assign
id|sha1
suffix:semicolon
id|prepare_replace_object
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Try to recursively replace the object */
r_do
(brace
r_if
c_cond
(paren
op_decrement
id|depth
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;replace depth too high for object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|pos
op_assign
id|replace_object_pos
c_func
(paren
id|cur
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
id|cur
op_assign
id|replace_object
(braket
id|pos
)braket
op_member_access_from_pointer
id|replacement
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
op_le
id|pos
)paren
suffix:semicolon
r_return
id|cur
suffix:semicolon
)brace
eof
