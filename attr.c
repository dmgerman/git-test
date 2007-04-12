macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
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
DECL|member|name
r_char
id|name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
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
suffix:semicolon
r_int
r_char
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
id|git_attr_hash
(braket
id|pos
)braket
op_assign
id|a
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
multiline_comment|/*&n; * .gitattributes file is one line per record, each of which is&n; *&n; * (1) glob pattern.&n; * (2) whitespace&n; * (3) whitespace separated list of attribute names, each of which&n; *     could be prefixed with &squot;!&squot; to mean &quot;not set&quot;.&n; */
DECL|struct|attr_state
r_struct
id|attr_state
(brace
DECL|member|unset
r_int
id|unset
suffix:semicolon
DECL|member|attr
r_struct
id|git_attr
op_star
id|attr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|match_attr
r_struct
id|match_attr
(brace
DECL|member|pattern
r_char
op_star
id|pattern
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
id|res
suffix:semicolon
r_int
id|pass
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
r_const
r_char
op_star
id|ep
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
r_if
c_cond
(paren
id|pass
)paren
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
l_char|&squot;!&squot;
)paren
(brace
id|e-&gt;unset
op_assign
l_int|1
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
id|e-&gt;attr
op_assign
id|git_attr
c_func
(paren
id|cp
comma
id|ep
id|cp
)paren
suffix:semicolon
)brace
id|num_attr
op_increment
suffix:semicolon
id|cp
op_assign
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
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|res-&gt;pattern
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
id|res-&gt;pattern
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|res-&gt;pattern
(braket
id|namelen
)braket
op_assign
l_int|0
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
multiline_comment|/*&n; * Like info/exclude and .gitignore, the attribute information can&n; * come from many places.&n; *&n; * (1) .gitattribute file of the same directory;&n; * (2) .gitattribute file of the parent directory if (1) does not have any match;&n; *     this goes recursively upwards, just like .gitignore&n; * (3) perhaps $GIT_DIR/info/attributes, as the final fallback.&n; *&n; * In the same file, later entries override the earlier match, so in the&n; * global list, we would have entries from info/attributes the earliest&n; * (reading the file from top to bottom), .gitattribute of the root&n; * directory (again, reading the file from top to bottom) down to the&n; * current directory, and then scan the list backwards to find the first match.&n; * This is exactly the same as what excluded() does in dir.c to deal with&n; * .gitignore&n; */
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
id|free
c_func
(paren
id|e-&gt;attrs
(braket
id|i
)braket
)paren
suffix:semicolon
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
l_int|NULL
comma
)brace
suffix:semicolon
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
(brace
r_struct
id|match_attr
op_star
id|a
op_assign
id|parse_attr_line
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_continue
suffix:semicolon
id|res-&gt;attrs
op_assign
id|xrealloc
c_func
(paren
id|res-&gt;attrs
comma
id|res-&gt;num_matches
op_plus
l_int|1
)paren
suffix:semicolon
id|res-&gt;attrs
(braket
id|res-&gt;num_matches
op_increment
)braket
op_assign
id|a
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
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
)paren
(brace
id|FILE
op_star
id|fp
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
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
r_return
id|res
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
(brace
r_struct
id|match_attr
op_star
id|a
op_assign
id|parse_attr_line
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
r_continue
suffix:semicolon
id|res-&gt;attrs
op_assign
id|xrealloc
c_func
(paren
id|res-&gt;attrs
comma
id|res-&gt;num_matches
op_plus
l_int|1
)paren
suffix:semicolon
id|res-&gt;attrs
(braket
id|res-&gt;num_matches
op_increment
)braket
op_assign
id|a
suffix:semicolon
)brace
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
DECL|macro|debug_push
mdefine_line|#define debug_push(a) debug_info(&quot;push&quot;, (a))
DECL|macro|debug_pop
mdefine_line|#define debug_pop(a) debug_info(&quot;pop&quot;, (a))
macro_line|#else
DECL|macro|debug_push
mdefine_line|#define debug_push(a) do { ; } while (0)
DECL|macro|debug_pop
mdefine_line|#define debug_pop(a) do { ; } while (0)
macro_line|#endif
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
r_char
id|pathbuf
(braket
id|PATH_MAX
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * At the bottom of the attribute stack is the built-in&n;&t; * set of attribute definitions.  Then, contents from&n;&t; * .gitattribute files from directories closer to the&n;&t; * root to the ones in deeper directories are pushed&n;&t; * to the stack.  Finally, at the very top of the stack&n;&t; * we always keep the contents of $GIT_DIR/info/attributes.&n;&t; *&n;&t; * When checking, we use entries from near the top of the&n;&t; * stack, preferring $GIT_DIR/info/attributes, then&n;&t; * .gitattributes in deeper directories to shallower ones,&n;&t; * and finally use the built-in set as the default.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|attr_stack
)paren
(brace
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
id|elem
op_assign
id|read_attr_from_file
c_func
(paren
id|GITATTRIBUTES_FILE
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
id|memcpy
c_func
(paren
id|pathbuf
comma
id|path
comma
id|dirlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pathbuf
op_plus
id|dirlen
comma
l_string|&quot;/&quot;
comma
l_int|2
)paren
suffix:semicolon
id|cp
op_assign
id|strchr
c_func
(paren
id|pathbuf
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
id|read_attr_from_file
c_func
(paren
id|pathbuf
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
id|pathbuf
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
l_int|1
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
multiline_comment|/*&n; * I do not like this at all.  Only because we allow individual&n; * attribute to be set or unset incrementally by individual&n; * lines in .gitattribute files, we need to do this triple&n; * loop which looks quite wasteful.&n; */
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
r_struct
id|git_attr_check
op_star
id|check
comma
r_int
id|num
comma
r_int
id|rem
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
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
id|path_matches
c_func
(paren
id|path
comma
id|pathlen
comma
id|a-&gt;pattern
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
(brace
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
r_struct
id|git_attr
op_star
id|attr
op_assign
id|a-&gt;state
(braket
id|j
)braket
dot
id|attr
suffix:semicolon
r_int
id|set
op_assign
op_logical_neg
id|a-&gt;state
(braket
id|j
)braket
dot
id|unset
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|num
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_le
id|check
(braket
id|k
)braket
dot
id|isset
op_logical_or
id|check
(braket
id|k
)braket
dot
id|attr
op_ne
id|attr
)paren
r_continue
suffix:semicolon
id|check
(braket
id|k
)braket
dot
id|isset
op_assign
id|set
suffix:semicolon
id|rem
op_decrement
suffix:semicolon
)brace
)brace
)brace
)brace
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
id|check
(braket
id|i
)braket
dot
id|isset
op_assign
l_int|1
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
id|num
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
id|check
comma
id|num
comma
id|rem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
