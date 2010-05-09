DECL|macro|NO_THE_INDEX_COMPATIBILITY_MACROS
mdefine_line|#define NO_THE_INDEX_COMPATIBILITY_MACROS
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
DECL|variable|git_attr__true
r_const
r_char
id|git_attr__true
(braket
)braket
op_assign
l_string|&quot;(builtin)true&quot;
suffix:semicolon
DECL|variable|git_attr__false
r_const
r_char
id|git_attr__false
(braket
)braket
op_assign
l_string|&quot;&bslash;0(builtin)false&quot;
suffix:semicolon
DECL|variable|git_attr__unknown
r_static
r_const
r_char
id|git_attr__unknown
(braket
)braket
op_assign
l_string|&quot;(builtin)unknown&quot;
suffix:semicolon
DECL|macro|ATTR__TRUE
mdefine_line|#define ATTR__TRUE git_attr__true
DECL|macro|ATTR__FALSE
mdefine_line|#define ATTR__FALSE git_attr__false
DECL|macro|ATTR__UNSET
mdefine_line|#define ATTR__UNSET NULL
DECL|macro|ATTR__UNKNOWN
mdefine_line|#define ATTR__UNKNOWN git_attr__unknown
multiline_comment|/*&n; * The basic design decision here is that we are not going to have&n; * insanely large number of attributes.&n; *&n; * This is a randomly chosen prime.&n; */
DECL|macro|HASHSIZE
mdefine_line|#define HASHSIZE 257
macro_line|#ifndef DEBUG_ATTR
DECL|macro|DEBUG_ATTR
mdefine_line|#define DEBUG_ATTR 0
macro_line|#endif
DECL|struct|git_attr
r_struct
id|git_attr
(brace
DECL|member|next
r_struct
id|git_attr
op_star
id|next
suffix:semicolon
DECL|member|h
r_int
id|h
suffix:semicolon
DECL|member|attr_nr
r_int
id|attr_nr
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|attr_nr
r_static
r_int
id|attr_nr
suffix:semicolon
DECL|variable|check_all_attr
r_static
r_struct
id|git_attr_check
op_star
id|check_all_attr
suffix:semicolon
DECL|variable|git_attr_hash
r_static
r_struct
id|git_attr
op_star
(paren
id|git_attr_hash
(braket
id|HASHSIZE
)braket
)paren
suffix:semicolon
DECL|function|hash_name
r_static
r_int
id|hash_name
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
r_int
id|val
op_assign
l_int|0
comma
id|c
suffix:semicolon
r_while
c_loop
(paren
id|namelen
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
id|val
op_assign
(paren
(paren
id|val
op_lshift
l_int|7
)paren
op_or
(paren
id|val
op_rshift
l_int|22
)paren
)paren
op_xor
id|c
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|invalid_attr_name
r_static
r_int
id|invalid_attr_name
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
multiline_comment|/*&n;&t; * Attribute name cannot begin with &squot;-&squot; and from&n;&t; * [-A-Za-z0-9_.].  We&squot;d specifically exclude &squot;=&squot; for now,&n;&t; * as we might later want to allow non-binary value for&n;&t; * attributes, e.g. &quot;*.svg&t;merge=special-merge-program-for-svg&quot;&n;&t; */
r_if
c_cond
(paren
op_star
id|name
op_eq
l_char|&squot;-&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|namelen
op_decrement
)paren
(brace
r_char
id|ch
op_assign
op_star
id|name
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch
op_eq
l_char|&squot;-&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;.&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;_&squot;
op_logical_or
(paren
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;9&squot;
)paren
op_logical_or
(paren
l_char|&squot;a&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
(paren
l_char|&squot;A&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;Z&squot;
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_attr_internal
r_static
r_struct
id|git_attr
op_star
id|git_attr_internal
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|hval
op_assign
id|hash_name
c_func
(paren
id|name
comma
id|len
)paren
suffix:semicolon
r_int
id|pos
op_assign
id|hval
op_mod
id|HASHSIZE
suffix:semicolon
r_struct
id|git_attr
op_star
id|a
suffix:semicolon
r_for
c_loop
(paren
id|a
op_assign
id|git_attr_hash
(braket
id|pos
)braket
suffix:semicolon
id|a
suffix:semicolon
id|a
op_assign
id|a-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|a-&gt;h
op_eq
id|hval
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|a-&gt;name
comma
id|name
comma
id|len
)paren
op_logical_and
op_logical_neg
id|a-&gt;name
(braket
id|len
)braket
)paren
r_return
id|a
suffix:semicolon
)brace
r_if
c_cond
(paren
id|invalid_attr_name
c_func
(paren
id|name
comma
id|len
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|a
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|a
)paren
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|a-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|a-&gt;name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|a-&gt;h
op_assign
id|hval
suffix:semicolon
id|a-&gt;next
op_assign
id|git_attr_hash
(braket
id|pos
)braket
suffix:semicolon
id|a-&gt;attr_nr
op_assign
id|attr_nr
op_increment
suffix:semicolon
id|git_attr_hash
(braket
id|pos
)braket
op_assign
id|a
suffix:semicolon
id|check_all_attr
op_assign
id|xrealloc
c_func
(paren
id|check_all_attr
comma
r_sizeof
(paren
op_star
id|check_all_attr
)paren
op_star
id|attr_nr
)paren
suffix:semicolon
id|check_all_attr
(braket
id|a-&gt;attr_nr
)braket
dot
id|attr
op_assign
id|a
suffix:semicolon
id|check_all_attr
(braket
id|a-&gt;attr_nr
)braket
dot
id|value
op_assign
id|ATTR__UNKNOWN
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
DECL|function|git_attr
r_struct
id|git_attr
op_star
id|git_attr
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_return
id|git_attr_internal
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * .gitattributes file is one line per record, each of which is&n; *&n; * (1) glob pattern.&n; * (2) whitespace&n; * (3) whitespace separated list of attribute names, each of which&n; *     could be prefixed with &squot;-&squot; to mean &quot;set to false&quot;, &squot;!&squot; to mean&n; *     &quot;unset&quot;.&n; */
multiline_comment|/* What does a matched pattern decide? */
DECL|struct|attr_state
r_struct
id|attr_state
(brace
DECL|member|attr
r_struct
id|git_attr
op_star
id|attr
suffix:semicolon
DECL|member|setto
r_const
r_char
op_star
id|setto
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|match_attr
r_struct
id|match_attr
(brace
r_union
(brace
DECL|member|pattern
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|attr
r_struct
id|git_attr
op_star
id|attr
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|is_macro
r_char
id|is_macro
suffix:semicolon
DECL|member|num_attr
r_int
id|num_attr
suffix:semicolon
DECL|member|state
r_struct
id|attr_state
id|state
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|blank
r_static
r_const
r_char
id|blank
(braket
)braket
op_assign
l_string|&quot; &bslash;t&bslash;r&bslash;n&quot;
suffix:semicolon
DECL|function|parse_attr
r_static
r_const
r_char
op_star
id|parse_attr
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_int
id|lineno
comma
r_const
r_char
op_star
id|cp
comma
r_int
op_star
id|num_attr
comma
r_struct
id|match_attr
op_star
id|res
)paren
(brace
r_const
r_char
op_star
id|ep
comma
op_star
id|equals
suffix:semicolon
r_int
id|len
suffix:semicolon
id|ep
op_assign
id|cp
op_plus
id|strcspn
c_func
(paren
id|cp
comma
id|blank
)paren
suffix:semicolon
id|equals
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|equals
op_logical_and
id|ep
OL
id|equals
)paren
id|equals
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|equals
)paren
id|len
op_assign
id|equals
id|cp
suffix:semicolon
r_else
id|len
op_assign
id|ep
id|cp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|invalid_attr_name
c_func
(paren
id|cp
comma
id|len
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s is not a valid attribute name: %s:%d&bslash;n&quot;
comma
id|len
comma
id|cp
comma
id|src
comma
id|lineno
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|attr_state
op_star
id|e
suffix:semicolon
id|e
op_assign
op_amp
(paren
id|res-&gt;state
(braket
op_star
id|num_attr
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|e-&gt;setto
op_assign
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
)paren
ques
c_cond
id|ATTR__FALSE
suffix:colon
id|ATTR__UNSET
suffix:semicolon
id|cp
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|equals
)paren
id|e-&gt;setto
op_assign
id|ATTR__TRUE
suffix:semicolon
r_else
(brace
id|e-&gt;setto
op_assign
id|xmemdupz
c_func
(paren
id|equals
op_plus
l_int|1
comma
id|ep
id|equals
l_int|1
)paren
suffix:semicolon
)brace
id|e-&gt;attr
op_assign
id|git_attr_internal
c_func
(paren
id|cp
comma
id|len
)paren
suffix:semicolon
)brace
(paren
op_star
id|num_attr
)paren
op_increment
suffix:semicolon
r_return
id|ep
op_plus
id|strspn
c_func
(paren
id|ep
comma
id|blank
)paren
suffix:semicolon
)brace
DECL|function|parse_attr_line
r_static
r_struct
id|match_attr
op_star
id|parse_attr_line
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_const
r_char
op_star
id|src
comma
r_int
id|lineno
comma
r_int
id|macro_ok
)paren
(brace
r_int
id|namelen
suffix:semicolon
r_int
id|num_attr
suffix:semicolon
r_const
r_char
op_star
id|cp
comma
op_star
id|name
suffix:semicolon
r_struct
id|match_attr
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
r_int
id|pass
suffix:semicolon
r_int
id|is_macro
suffix:semicolon
id|cp
op_assign
id|line
op_plus
id|strspn
c_func
(paren
id|line
comma
id|blank
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|cp
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;#&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
id|name
op_assign
id|cp
suffix:semicolon
id|namelen
op_assign
id|strcspn
c_func
(paren
id|name
comma
id|blank
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|ATTRIBUTE_MACRO_PREFIX
)paren
OL
id|namelen
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
id|ATTRIBUTE_MACRO_PREFIX
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|macro_ok
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s not allowed: %s:%d&bslash;n&quot;
comma
id|name
comma
id|src
comma
id|lineno
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|is_macro
op_assign
l_int|1
suffix:semicolon
id|name
op_add_assign
id|strlen
c_func
(paren
id|ATTRIBUTE_MACRO_PREFIX
)paren
suffix:semicolon
id|name
op_add_assign
id|strspn
c_func
(paren
id|name
comma
id|blank
)paren
suffix:semicolon
id|namelen
op_assign
id|strcspn
c_func
(paren
id|name
comma
id|blank
)paren
suffix:semicolon
r_if
c_cond
(paren
id|invalid_attr_name
c_func
(paren
id|name
comma
id|namelen
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%.*s is not a valid attribute name: %s:%d&bslash;n&quot;
comma
id|namelen
comma
id|name
comma
id|src
comma
id|lineno
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
id|is_macro
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|pass
op_assign
l_int|0
suffix:semicolon
id|pass
OL
l_int|2
suffix:semicolon
id|pass
op_increment
)paren
(brace
multiline_comment|/* pass 0 counts and allocates, pass 1 fills */
id|num_attr
op_assign
l_int|0
suffix:semicolon
id|cp
op_assign
id|name
op_plus
id|namelen
suffix:semicolon
id|cp
op_assign
id|cp
op_plus
id|strspn
c_func
(paren
id|cp
comma
id|blank
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
)paren
(brace
id|cp
op_assign
id|parse_attr
c_func
(paren
id|src
comma
id|lineno
comma
id|cp
comma
op_amp
id|num_attr
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pass
)paren
r_break
suffix:semicolon
id|res
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|res
)paren
op_plus
r_sizeof
(paren
r_struct
id|attr_state
)paren
op_star
id|num_attr
op_plus
(paren
id|is_macro
ques
c_cond
l_int|0
suffix:colon
id|namelen
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_macro
)paren
id|res-&gt;u.attr
op_assign
id|git_attr_internal
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
r_else
(brace
id|res-&gt;u.pattern
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|res-&gt;state
(braket
id|num_attr
)braket
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|res-&gt;u.pattern
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|res-&gt;u.pattern
(braket
id|namelen
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|res-&gt;is_macro
op_assign
id|is_macro
suffix:semicolon
id|res-&gt;num_attr
op_assign
id|num_attr
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Like info/exclude and .gitignore, the attribute information can&n; * come from many places.&n; *&n; * (1) .gitattribute file of the same directory;&n; * (2) .gitattribute file of the parent directory if (1) does not have&n; *      any match; this goes recursively upwards, just like .gitignore.&n; * (3) $GIT_DIR/info/attributes, which overrides both of the above.&n; *&n; * In the same file, later entries override the earlier match, so in the&n; * global list, we would have entries from info/attributes the earliest&n; * (reading the file from top to bottom), .gitattribute of the root&n; * directory (again, reading the file from top to bottom) down to the&n; * current directory, and then scan the list backwards to find the first match.&n; * This is exactly the same as what excluded() does in dir.c to deal with&n; * .gitignore&n; */
DECL|struct|attr_stack
r_static
r_struct
id|attr_stack
(brace
DECL|member|prev
r_struct
id|attr_stack
op_star
id|prev
suffix:semicolon
DECL|member|origin
r_char
op_star
id|origin
suffix:semicolon
DECL|member|num_matches
r_int
id|num_matches
suffix:semicolon
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|attrs
r_struct
id|match_attr
op_star
op_star
id|attrs
suffix:semicolon
DECL|variable|attr_stack
)brace
op_star
id|attr_stack
suffix:semicolon
DECL|function|free_attr_elem
r_static
r_void
id|free_attr_elem
c_func
(paren
r_struct
id|attr_stack
op_star
id|e
)paren
(brace
r_int
id|i
suffix:semicolon
id|free
c_func
(paren
id|e-&gt;origin
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
id|e-&gt;num_matches
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|match_attr
op_star
id|a
op_assign
id|e-&gt;attrs
(braket
id|i
)braket
suffix:semicolon
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|a-&gt;num_attr
suffix:semicolon
id|j
op_increment
)paren
(brace
r_const
r_char
op_star
id|setto
op_assign
id|a-&gt;state
(braket
id|j
)braket
dot
id|setto
suffix:semicolon
r_if
c_cond
(paren
id|setto
op_eq
id|ATTR__TRUE
op_logical_or
id|setto
op_eq
id|ATTR__FALSE
op_logical_or
id|setto
op_eq
id|ATTR__UNSET
op_logical_or
id|setto
op_eq
id|ATTR__UNKNOWN
)paren
suffix:semicolon
r_else
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|setto
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|a
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|e
)paren
suffix:semicolon
)brace
DECL|variable|builtin_attr
r_static
r_const
r_char
op_star
id|builtin_attr
(braket
)braket
op_assign
(brace
l_string|&quot;[attr]binary -diff -crlf&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|handle_attr_line
r_static
r_void
id|handle_attr_line
c_func
(paren
r_struct
id|attr_stack
op_star
id|res
comma
r_const
r_char
op_star
id|line
comma
r_const
r_char
op_star
id|src
comma
r_int
id|lineno
comma
r_int
id|macro_ok
)paren
(brace
r_struct
id|match_attr
op_star
id|a
suffix:semicolon
id|a
op_assign
id|parse_attr_line
c_func
(paren
id|line
comma
id|src
comma
id|lineno
comma
id|macro_ok
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;alloc
op_le
id|res-&gt;num_matches
)paren
(brace
id|res-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|res-&gt;num_matches
)paren
suffix:semicolon
id|res-&gt;attrs
op_assign
id|xrealloc
c_func
(paren
id|res-&gt;attrs
comma
r_sizeof
(paren
r_struct
id|match_attr
op_star
)paren
op_star
id|res-&gt;alloc
)paren
suffix:semicolon
)brace
id|res-&gt;attrs
(braket
id|res-&gt;num_matches
op_increment
)braket
op_assign
id|a
suffix:semicolon
)brace
DECL|function|read_attr_from_array
r_static
r_struct
id|attr_stack
op_star
id|read_attr_from_array
c_func
(paren
r_const
r_char
op_star
op_star
id|list
)paren
(brace
r_struct
id|attr_stack
op_star
id|res
suffix:semicolon
r_const
r_char
op_star
id|line
suffix:semicolon
r_int
id|lineno
op_assign
l_int|0
suffix:semicolon
id|res
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|line
op_assign
op_star
(paren
id|list
op_increment
)paren
)paren
op_ne
l_int|NULL
)paren
id|handle_attr_line
c_func
(paren
id|res
comma
id|line
comma
l_string|&quot;[builtin]&quot;
comma
op_increment
id|lineno
comma
l_int|1
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|direction
r_static
r_enum
id|git_attr_direction
id|direction
suffix:semicolon
DECL|variable|use_index
r_static
r_struct
id|index_state
op_star
id|use_index
suffix:semicolon
DECL|function|read_attr_from_file
r_static
r_struct
id|attr_stack
op_star
id|read_attr_from_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|macro_ok
)paren
(brace
id|FILE
op_star
id|fp
op_assign
id|fopen
c_func
(paren
id|path
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_struct
id|attr_stack
op_star
id|res
suffix:semicolon
r_char
id|buf
(braket
l_int|2048
)braket
suffix:semicolon
r_int
id|lineno
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
r_return
l_int|NULL
suffix:semicolon
id|res
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|fp
)paren
)paren
id|handle_attr_line
c_func
(paren
id|res
comma
id|buf
comma
id|path
comma
op_increment
id|lineno
comma
id|macro_ok
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|read_index_data
r_static
r_void
op_star
id|read_index_data
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|pos
comma
id|len
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_struct
id|index_state
op_star
id|istate
op_assign
id|use_index
ques
c_cond
id|use_index
suffix:colon
op_amp
id|the_index
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|pos
op_assign
id|index_name_pos
c_func
(paren
id|istate
comma
id|path
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * We might be in the middle of a merge, in which&n;&t;&t; * case we would read stage #2 (ours).&n;&t;&t; */
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pos
l_int|1
suffix:semicolon
(paren
id|pos
OL
l_int|0
op_logical_and
id|i
OL
id|istate-&gt;cache_nr
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|istate-&gt;cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|path
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|istate-&gt;cache
(braket
id|i
)braket
)paren
op_eq
l_int|2
)paren
id|pos
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|data
op_assign
id|read_sha1_file
c_func
(paren
id|istate-&gt;cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|sha1
comma
op_amp
id|type
comma
op_amp
id|sz
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
op_logical_or
id|type
op_ne
id|OBJ_BLOB
)paren
(brace
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|data
suffix:semicolon
)brace
DECL|function|read_attr_from_index
r_static
r_struct
id|attr_stack
op_star
id|read_attr_from_index
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|macro_ok
)paren
(brace
r_struct
id|attr_stack
op_star
id|res
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|sp
suffix:semicolon
r_int
id|lineno
op_assign
l_int|0
suffix:semicolon
id|buf
op_assign
id|read_index_data
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
l_int|NULL
suffix:semicolon
id|res
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sp
op_assign
id|buf
suffix:semicolon
op_star
id|sp
suffix:semicolon
)paren
(brace
r_char
op_star
id|ep
suffix:semicolon
r_int
id|more
suffix:semicolon
r_for
c_loop
(paren
id|ep
op_assign
id|sp
suffix:semicolon
op_star
id|ep
op_logical_and
op_star
id|ep
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|ep
op_increment
)paren
suffix:semicolon
id|more
op_assign
(paren
op_star
id|ep
op_eq
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
op_star
id|ep
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|handle_attr_line
c_func
(paren
id|res
comma
id|sp
comma
id|path
comma
op_increment
id|lineno
comma
id|macro_ok
)paren
suffix:semicolon
id|sp
op_assign
id|ep
op_plus
id|more
suffix:semicolon
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|read_attr
r_static
r_struct
id|attr_stack
op_star
id|read_attr
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|macro_ok
)paren
(brace
r_struct
id|attr_stack
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|GIT_ATTR_CHECKOUT
)paren
(brace
id|res
op_assign
id|read_attr_from_index
c_func
(paren
id|path
comma
id|macro_ok
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|res
op_assign
id|read_attr_from_file
c_func
(paren
id|path
comma
id|macro_ok
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|direction
op_eq
id|GIT_ATTR_CHECKIN
)paren
(brace
id|res
op_assign
id|read_attr_from_file
c_func
(paren
id|path
comma
id|macro_ok
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
multiline_comment|/*&n;&t;&t;&t; * There is no checked out .gitattributes file there, but&n;&t;&t;&t; * we might have it in the index.  We allow operation in a&n;&t;&t;&t; * sparsely checked out work tree, so read from it.&n;&t;&t;&t; */
id|res
op_assign
id|read_attr_from_index
c_func
(paren
id|path
comma
id|macro_ok
)paren
suffix:semicolon
)brace
r_else
id|res
op_assign
id|read_attr_from_index
c_func
(paren
id|path
comma
id|macro_ok
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|res
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
macro_line|#if DEBUG_ATTR
DECL|function|debug_info
r_static
r_void
id|debug_info
c_func
(paren
r_const
r_char
op_star
id|what
comma
r_struct
id|attr_stack
op_star
id|elem
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|what
comma
id|elem-&gt;origin
ques
c_cond
id|elem-&gt;origin
suffix:colon
l_string|&quot;()&quot;
)paren
suffix:semicolon
)brace
DECL|function|debug_set
r_static
r_void
id|debug_set
c_func
(paren
r_const
r_char
op_star
id|what
comma
r_const
r_char
op_star
id|match
comma
r_struct
id|git_attr
op_star
id|attr
comma
r_const
r_void
op_star
id|v
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|v
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;set&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_FALSE
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;unset&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_UNSET
c_func
(paren
id|value
)paren
)paren
id|value
op_assign
l_string|&quot;unspecified&quot;
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %s =&gt; %s (%s)&bslash;n&quot;
comma
id|what
comma
id|attr-&gt;name
comma
(paren
r_char
op_star
)paren
id|value
comma
id|match
)paren
suffix:semicolon
)brace
DECL|macro|debug_push
mdefine_line|#define debug_push(a) debug_info(&quot;push&quot;, (a))
DECL|macro|debug_pop
mdefine_line|#define debug_pop(a) debug_info(&quot;pop&quot;, (a))
macro_line|#else
DECL|macro|debug_push
mdefine_line|#define debug_push(a) do { ; } while (0)
DECL|macro|debug_pop
mdefine_line|#define debug_pop(a) do { ; } while (0)
DECL|macro|debug_set
mdefine_line|#define debug_set(a,b,c,d) do { ; } while (0)
macro_line|#endif
DECL|function|drop_attr_stack
r_static
r_void
id|drop_attr_stack
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|attr_stack
)paren
(brace
r_struct
id|attr_stack
op_star
id|elem
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|elem-&gt;prev
suffix:semicolon
id|free_attr_elem
c_func
(paren
id|elem
)paren
suffix:semicolon
)brace
)brace
DECL|function|bootstrap_attr_stack
r_static
r_void
id|bootstrap_attr_stack
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|attr_stack
)paren
(brace
r_struct
id|attr_stack
op_star
id|elem
suffix:semicolon
id|elem
op_assign
id|read_attr_from_array
c_func
(paren
id|builtin_attr
)paren
suffix:semicolon
id|elem-&gt;origin
op_assign
l_int|NULL
suffix:semicolon
id|elem-&gt;prev
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|elem
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_bare_repository
c_func
(paren
)paren
op_logical_or
id|direction
op_eq
id|GIT_ATTR_INDEX
)paren
(brace
id|elem
op_assign
id|read_attr
c_func
(paren
id|GITATTRIBUTES_FILE
comma
l_int|1
)paren
suffix:semicolon
id|elem-&gt;origin
op_assign
id|strdup
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|elem-&gt;prev
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|elem
suffix:semicolon
id|debug_push
c_func
(paren
id|elem
)paren
suffix:semicolon
)brace
id|elem
op_assign
id|read_attr_from_file
c_func
(paren
id|git_path
c_func
(paren
id|INFOATTRIBUTES_FILE
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elem
)paren
id|elem
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|elem
)paren
)paren
suffix:semicolon
id|elem-&gt;origin
op_assign
l_int|NULL
suffix:semicolon
id|elem-&gt;prev
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|elem
suffix:semicolon
)brace
)brace
DECL|function|prepare_attr_stack
r_static
r_void
id|prepare_attr_stack
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|dirlen
)paren
(brace
r_struct
id|attr_stack
op_star
id|elem
comma
op_star
id|info
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|strbuf
id|pathbuf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|pathbuf
comma
id|dirlen
op_plus
l_int|2
op_plus
id|strlen
c_func
(paren
id|GITATTRIBUTES_FILE
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * At the bottom of the attribute stack is the built-in&n;&t; * set of attribute definitions.  Then, contents from&n;&t; * .gitattribute files from directories closer to the&n;&t; * root to the ones in deeper directories are pushed&n;&t; * to the stack.  Finally, at the very top of the stack&n;&t; * we always keep the contents of $GIT_DIR/info/attributes.&n;&t; *&n;&t; * When checking, we use entries from near the top of the&n;&t; * stack, preferring $GIT_DIR/info/attributes, then&n;&t; * .gitattributes in deeper directories to shallower ones,&n;&t; * and finally use the built-in set as the default.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|attr_stack
)paren
id|bootstrap_attr_stack
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Pop the &quot;info&quot; one that is always at the top of the stack.&n;&t; */
id|info
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|info-&gt;prev
suffix:semicolon
multiline_comment|/*&n;&t; * Pop the ones from directories that are not the prefix of&n;&t; * the path we are checking.&n;&t; */
r_while
c_loop
(paren
id|attr_stack
op_logical_and
id|attr_stack-&gt;origin
)paren
(brace
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|attr_stack-&gt;origin
)paren
suffix:semicolon
id|elem
op_assign
id|attr_stack
suffix:semicolon
r_if
c_cond
(paren
id|namelen
op_le
id|dirlen
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|elem-&gt;origin
comma
id|path
comma
id|namelen
)paren
)paren
r_break
suffix:semicolon
id|debug_pop
c_func
(paren
id|elem
)paren
suffix:semicolon
id|attr_stack
op_assign
id|elem-&gt;prev
suffix:semicolon
id|free_attr_elem
c_func
(paren
id|elem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Read from parent directories and push them down&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|is_bare_repository
c_func
(paren
)paren
op_logical_or
id|direction
op_eq
id|GIT_ATTR_INDEX
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|attr_stack-&gt;origin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dirlen
op_le
id|len
)paren
r_break
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|pathbuf
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|pathbuf
comma
id|path
comma
id|dirlen
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|pathbuf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|cp
op_assign
id|strchr
c_func
(paren
id|pathbuf.buf
op_plus
id|len
op_plus
l_int|1
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|cp
op_plus
l_int|1
comma
id|GITATTRIBUTES_FILE
)paren
suffix:semicolon
id|elem
op_assign
id|read_attr
c_func
(paren
id|pathbuf.buf
comma
l_int|0
)paren
suffix:semicolon
op_star
id|cp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|elem-&gt;origin
op_assign
id|strdup
c_func
(paren
id|pathbuf.buf
)paren
suffix:semicolon
id|elem-&gt;prev
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|elem
suffix:semicolon
id|debug_push
c_func
(paren
id|elem
)paren
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|pathbuf
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Finally push the &quot;info&quot; one at the top of the stack.&n;&t; */
id|info-&gt;prev
op_assign
id|attr_stack
suffix:semicolon
id|attr_stack
op_assign
id|info
suffix:semicolon
)brace
DECL|function|path_matches
r_static
r_int
id|path_matches
c_func
(paren
r_const
r_char
op_star
id|pathname
comma
r_int
id|pathlen
comma
r_const
r_char
op_star
id|pattern
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
id|pattern
comma
l_char|&squot;/&squot;
)paren
)paren
(brace
multiline_comment|/* match basename */
r_const
r_char
op_star
id|basename
op_assign
id|strrchr
c_func
(paren
id|pathname
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|basename
op_assign
id|basename
ques
c_cond
id|basename
op_plus
l_int|1
suffix:colon
id|pathname
suffix:semicolon
r_return
(paren
id|fnmatch
c_func
(paren
id|pattern
comma
id|basename
comma
l_int|0
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * match with FNM_PATHNAME; the pattern has base implicitly&n;&t; * in front of it.&n;&t; */
r_if
c_cond
(paren
op_star
id|pattern
op_eq
l_char|&squot;/&squot;
)paren
id|pattern
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OL
id|baselen
op_logical_or
(paren
id|baselen
op_logical_and
id|pathname
(braket
id|baselen
)braket
op_ne
l_char|&squot;/&squot;
)paren
op_logical_or
id|strncmp
c_func
(paren
id|pathname
comma
id|base
comma
id|baselen
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|baselen
op_ne
l_int|0
)paren
id|baselen
op_increment
suffix:semicolon
r_return
id|fnmatch
c_func
(paren
id|pattern
comma
id|pathname
op_plus
id|baselen
comma
id|FNM_PATHNAME
)paren
op_eq
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|macroexpand_one
c_func
(paren
r_int
id|attr_nr
comma
r_int
id|rem
)paren
suffix:semicolon
DECL|function|fill_one
r_static
r_int
id|fill_one
c_func
(paren
r_const
r_char
op_star
id|what
comma
r_struct
id|match_attr
op_star
id|a
comma
r_int
id|rem
)paren
(brace
r_struct
id|git_attr_check
op_star
id|check
op_assign
id|check_all_attr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|a-&gt;num_attr
l_int|1
suffix:semicolon
l_int|0
OL
id|rem
op_logical_and
l_int|0
op_le
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_struct
id|git_attr
op_star
id|attr
op_assign
id|a-&gt;state
(braket
id|i
)braket
dot
id|attr
suffix:semicolon
r_const
r_char
op_star
op_star
id|n
op_assign
op_amp
(paren
id|check
(braket
id|attr-&gt;attr_nr
)braket
dot
id|value
)paren
suffix:semicolon
r_const
r_char
op_star
id|v
op_assign
id|a-&gt;state
(braket
id|i
)braket
dot
id|setto
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_eq
id|ATTR__UNKNOWN
)paren
(brace
id|debug_set
c_func
(paren
id|what
comma
id|a-&gt;is_macro
ques
c_cond
id|a-&gt;u.attr-&gt;name
suffix:colon
id|a-&gt;u.pattern
comma
id|attr
comma
id|v
)paren
suffix:semicolon
op_star
id|n
op_assign
id|v
suffix:semicolon
id|rem
op_decrement
suffix:semicolon
id|rem
op_assign
id|macroexpand_one
c_func
(paren
id|attr-&gt;attr_nr
comma
id|rem
)paren
suffix:semicolon
)brace
)brace
r_return
id|rem
suffix:semicolon
)brace
DECL|function|fill
r_static
r_int
id|fill
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|pathlen
comma
r_struct
id|attr_stack
op_star
id|stk
comma
r_int
id|rem
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_char
op_star
id|base
op_assign
id|stk-&gt;origin
ques
c_cond
id|stk-&gt;origin
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|stk-&gt;num_matches
l_int|1
suffix:semicolon
l_int|0
OL
id|rem
op_logical_and
l_int|0
op_le
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_struct
id|match_attr
op_star
id|a
op_assign
id|stk-&gt;attrs
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;is_macro
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|path_matches
c_func
(paren
id|path
comma
id|pathlen
comma
id|a-&gt;u.pattern
comma
id|base
comma
id|strlen
c_func
(paren
id|base
)paren
)paren
)paren
id|rem
op_assign
id|fill_one
c_func
(paren
l_string|&quot;fill&quot;
comma
id|a
comma
id|rem
)paren
suffix:semicolon
)brace
r_return
id|rem
suffix:semicolon
)brace
DECL|function|macroexpand_one
r_static
r_int
id|macroexpand_one
c_func
(paren
r_int
id|attr_nr
comma
r_int
id|rem
)paren
(brace
r_struct
id|attr_stack
op_star
id|stk
suffix:semicolon
r_struct
id|match_attr
op_star
id|a
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|check_all_attr
(braket
id|attr_nr
)braket
dot
id|value
op_ne
id|ATTR__TRUE
)paren
r_return
id|rem
suffix:semicolon
r_for
c_loop
(paren
id|stk
op_assign
id|attr_stack
suffix:semicolon
op_logical_neg
id|a
op_logical_and
id|stk
suffix:semicolon
id|stk
op_assign
id|stk-&gt;prev
)paren
r_for
c_loop
(paren
id|i
op_assign
id|stk-&gt;num_matches
l_int|1
suffix:semicolon
op_logical_neg
id|a
op_logical_and
l_int|0
op_le
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_struct
id|match_attr
op_star
id|ma
op_assign
id|stk-&gt;attrs
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ma-&gt;is_macro
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ma-&gt;u.attr-&gt;attr_nr
op_eq
id|attr_nr
)paren
id|a
op_assign
id|ma
suffix:semicolon
)brace
r_if
c_cond
(paren
id|a
)paren
id|rem
op_assign
id|fill_one
c_func
(paren
l_string|&quot;expand&quot;
comma
id|a
comma
id|rem
)paren
suffix:semicolon
r_return
id|rem
suffix:semicolon
)brace
DECL|function|git_checkattr
r_int
id|git_checkattr
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|num
comma
r_struct
id|git_attr_check
op_star
id|check
)paren
(brace
r_struct
id|attr_stack
op_star
id|stk
suffix:semicolon
r_const
r_char
op_star
id|cp
suffix:semicolon
r_int
id|dirlen
comma
id|pathlen
comma
id|i
comma
id|rem
suffix:semicolon
id|bootstrap_attr_stack
c_func
(paren
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
id|attr_nr
suffix:semicolon
id|i
op_increment
)paren
id|check_all_attr
(braket
id|i
)braket
dot
id|value
op_assign
id|ATTR__UNKNOWN
suffix:semicolon
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|cp
op_assign
id|strrchr
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
id|dirlen
op_assign
l_int|0
suffix:semicolon
r_else
id|dirlen
op_assign
id|cp
id|path
suffix:semicolon
id|prepare_attr_stack
c_func
(paren
id|path
comma
id|dirlen
)paren
suffix:semicolon
id|rem
op_assign
id|attr_nr
suffix:semicolon
r_for
c_loop
(paren
id|stk
op_assign
id|attr_stack
suffix:semicolon
l_int|0
OL
id|rem
op_logical_and
id|stk
suffix:semicolon
id|stk
op_assign
id|stk-&gt;prev
)paren
id|rem
op_assign
id|fill
c_func
(paren
id|path
comma
id|pathlen
comma
id|stk
comma
id|rem
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|check_all_attr
(braket
id|check
(braket
id|i
)braket
dot
id|attr-&gt;attr_nr
)braket
dot
id|value
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
id|ATTR__UNKNOWN
)paren
id|value
op_assign
id|ATTR__UNSET
suffix:semicolon
id|check
(braket
id|i
)braket
dot
id|value
op_assign
id|value
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_attr_set_direction
r_void
id|git_attr_set_direction
c_func
(paren
r_enum
id|git_attr_direction
r_new
comma
r_struct
id|index_state
op_star
id|istate
)paren
(brace
r_enum
id|git_attr_direction
id|old
op_assign
id|direction
suffix:semicolon
r_if
c_cond
(paren
id|is_bare_repository
c_func
(paren
)paren
op_logical_and
r_new
op_ne
id|GIT_ATTR_INDEX
)paren
id|die
c_func
(paren
l_string|&quot;BUG: non-INDEX attr direction in a bare repo&quot;
)paren
suffix:semicolon
id|direction
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ne
id|old
)paren
id|drop_attr_stack
c_func
(paren
)paren
suffix:semicolon
id|use_index
op_assign
id|istate
suffix:semicolon
)brace
eof
