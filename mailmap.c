macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;mailmap.h&quot;
DECL|macro|DEBUG_MAILMAP
mdefine_line|#define DEBUG_MAILMAP 0
macro_line|#if DEBUG_MAILMAP
DECL|macro|debug_mm
mdefine_line|#define debug_mm(...) fprintf(stderr, __VA_ARGS__)
macro_line|#else
DECL|function|debug_mm
r_static
r_inline
r_void
id|debug_mm
c_func
(paren
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
)brace
macro_line|#endif
DECL|variable|git_mailmap_file
r_const
r_char
op_star
id|git_mailmap_file
suffix:semicolon
DECL|struct|mailmap_info
r_struct
id|mailmap_info
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|email
r_char
op_star
id|email
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mailmap_entry
r_struct
id|mailmap_entry
(brace
multiline_comment|/* name and email for the simple mail-only case */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|email
r_char
op_star
id|email
suffix:semicolon
multiline_comment|/* name and email for the complex mail and name matching case */
DECL|member|namemap
r_struct
id|string_list
id|namemap
suffix:semicolon
)brace
suffix:semicolon
DECL|function|free_mailmap_info
r_static
r_void
id|free_mailmap_info
c_func
(paren
r_void
op_star
id|p
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_struct
id|mailmap_info
op_star
id|mi
op_assign
(paren
r_struct
id|mailmap_info
op_star
)paren
id|p
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: -- complex: &squot;%s&squot; -&gt; &squot;%s&squot; &lt;%s&gt;&bslash;n&quot;
comma
id|s
comma
id|mi-&gt;name
comma
id|mi-&gt;email
)paren
suffix:semicolon
id|free
c_func
(paren
id|mi-&gt;name
)paren
suffix:semicolon
id|free
c_func
(paren
id|mi-&gt;email
)paren
suffix:semicolon
)brace
DECL|function|free_mailmap_entry
r_static
r_void
id|free_mailmap_entry
c_func
(paren
r_void
op_star
id|p
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_struct
id|mailmap_entry
op_star
id|me
op_assign
(paren
r_struct
id|mailmap_entry
op_star
)paren
id|p
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: removing entries for &lt;%s&gt;, with %d sub-entries&bslash;n&quot;
comma
id|s
comma
id|me-&gt;namemap.nr
)paren
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: - simple: &squot;%s&squot; &lt;%s&gt;&bslash;n&quot;
comma
id|me-&gt;name
comma
id|me-&gt;email
)paren
suffix:semicolon
id|free
c_func
(paren
id|me-&gt;name
)paren
suffix:semicolon
id|free
c_func
(paren
id|me-&gt;email
)paren
suffix:semicolon
id|me-&gt;namemap.strdup_strings
op_assign
l_int|1
suffix:semicolon
id|string_list_clear_func
c_func
(paren
op_amp
id|me-&gt;namemap
comma
id|free_mailmap_info
)paren
suffix:semicolon
)brace
DECL|function|add_mapping
r_static
r_void
id|add_mapping
c_func
(paren
r_struct
id|string_list
op_star
id|map
comma
r_char
op_star
id|new_name
comma
r_char
op_star
id|new_email
comma
r_char
op_star
id|old_name
comma
r_char
op_star
id|old_email
)paren
(brace
r_struct
id|mailmap_entry
op_star
id|me
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
id|old_email
op_eq
l_int|NULL
)paren
(brace
id|old_email
op_assign
id|new_email
suffix:semicolon
id|new_email
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|index
op_assign
id|string_list_find_insert_index
c_func
(paren
id|map
comma
id|old_email
comma
l_int|1
)paren
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* mailmap entry exists, invert index value */
id|index
op_assign
l_int|1
id|index
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* create mailmap entry */
r_struct
id|string_list_item
op_star
id|item
op_assign
id|string_list_insert_at_index
c_func
(paren
id|index
comma
id|old_email
comma
id|map
)paren
suffix:semicolon
id|item-&gt;util
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mailmap_entry
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|item-&gt;util
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mailmap_entry
)paren
)paren
suffix:semicolon
(paren
(paren
r_struct
id|mailmap_entry
op_star
)paren
id|item-&gt;util
)paren
op_member_access_from_pointer
id|namemap.strdup_strings
op_assign
l_int|1
suffix:semicolon
)brace
id|me
op_assign
(paren
r_struct
id|mailmap_entry
op_star
)paren
id|map-&gt;items
(braket
id|index
)braket
dot
id|util
suffix:semicolon
r_if
c_cond
(paren
id|old_name
op_eq
l_int|NULL
)paren
(brace
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: adding (simple) entry for %s at index %d&bslash;n&quot;
comma
id|old_email
comma
id|index
)paren
suffix:semicolon
multiline_comment|/* Replace current name and new email for simple entry */
id|free
c_func
(paren
id|me-&gt;name
)paren
suffix:semicolon
id|free
c_func
(paren
id|me-&gt;email
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_name
)paren
id|me-&gt;name
op_assign
id|xstrdup
c_func
(paren
id|new_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_email
)paren
id|me-&gt;email
op_assign
id|xstrdup
c_func
(paren
id|new_email
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|mailmap_info
op_star
id|mi
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mailmap_info
)paren
)paren
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: adding (complex) entry for %s at index %d&bslash;n&quot;
comma
id|old_email
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_name
)paren
id|mi-&gt;name
op_assign
id|xstrdup
c_func
(paren
id|new_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_email
)paren
id|mi-&gt;email
op_assign
id|xstrdup
c_func
(paren
id|new_email
)paren
suffix:semicolon
id|string_list_insert
c_func
(paren
id|old_name
comma
op_amp
id|me-&gt;namemap
)paren
op_member_access_from_pointer
id|util
op_assign
id|mi
suffix:semicolon
)brace
id|debug_mm
c_func
(paren
l_string|&quot;mailmap:  &squot;%s&squot; &lt;%s&gt; -&gt; &squot;%s&squot; &lt;%s&gt;&bslash;n&quot;
comma
id|old_name
comma
id|old_email
comma
id|new_name
comma
id|new_email
)paren
suffix:semicolon
)brace
DECL|function|parse_name_and_email
r_static
r_char
op_star
id|parse_name_and_email
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|name
comma
r_char
op_star
op_star
id|email
comma
r_int
id|allow_empty_email
)paren
(brace
r_char
op_star
id|left
comma
op_star
id|right
comma
op_star
id|nstart
comma
op_star
id|nend
suffix:semicolon
op_star
id|name
op_assign
op_star
id|email
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|left
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot;&lt;&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|right
op_assign
id|strchr
c_func
(paren
id|left
op_plus
l_int|1
comma
l_char|&squot;&gt;&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allow_empty_email
op_logical_and
(paren
id|left
op_plus
l_int|1
op_eq
id|right
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* remove whitespace from beginning and end of name */
id|nstart
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|nstart
)paren
op_logical_and
id|nstart
OL
id|left
)paren
op_increment
id|nstart
suffix:semicolon
id|nend
op_assign
id|left
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|nend
)paren
op_logical_and
id|nend
OG
id|nstart
)paren
op_decrement
id|nend
suffix:semicolon
op_star
id|name
op_assign
(paren
id|nstart
OL
id|nend
ques
c_cond
id|nstart
suffix:colon
l_int|NULL
)paren
suffix:semicolon
op_star
id|email
op_assign
id|left
op_plus
l_int|1
suffix:semicolon
op_star
(paren
id|nend
op_plus
l_int|1
)paren
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|right
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
(paren
op_star
id|right
op_eq
l_char|&squot;&bslash;0&squot;
ques
c_cond
l_int|NULL
suffix:colon
id|right
)paren
suffix:semicolon
)brace
DECL|function|read_single_mailmap
r_static
r_int
id|read_single_mailmap
c_func
(paren
r_struct
id|string_list
op_star
id|map
comma
r_const
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|repo_abbrev
)paren
(brace
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
id|FILE
op_star
id|f
op_assign
(paren
id|filename
op_eq
l_int|NULL
ques
c_cond
l_int|NULL
suffix:colon
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;r&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|f
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|name1
op_assign
l_int|0
comma
op_star
id|email1
op_assign
l_int|0
comma
op_star
id|name2
op_assign
l_int|0
comma
op_star
id|email2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;#&squot;
)paren
(brace
r_static
r_const
r_char
id|abbrev
(braket
)braket
op_assign
l_string|&quot;# repo-abbrev:&quot;
suffix:semicolon
r_int
id|abblen
op_assign
r_sizeof
(paren
id|abbrev
)paren
l_int|1
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|repo_abbrev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|buffer
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buffer
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
id|abbrev
comma
id|abblen
)paren
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|repo_abbrev
)paren
id|free
c_func
(paren
op_star
id|repo_abbrev
)paren
suffix:semicolon
op_star
id|repo_abbrev
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|buffer
op_plus
id|abblen
suffix:semicolon
id|isspace
c_func
(paren
op_star
id|cp
)paren
suffix:semicolon
id|cp
op_increment
)paren
suffix:semicolon
multiline_comment|/* nothing */
id|strcpy
c_func
(paren
op_star
id|repo_abbrev
comma
id|cp
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|name2
op_assign
id|parse_name_and_email
c_func
(paren
id|buffer
comma
op_amp
id|name1
comma
op_amp
id|email1
comma
l_int|0
)paren
)paren
op_ne
l_int|NULL
)paren
id|parse_name_and_email
c_func
(paren
id|name2
comma
op_amp
id|name2
comma
op_amp
id|email2
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|email1
)paren
id|add_mapping
c_func
(paren
id|map
comma
id|name1
comma
id|email1
comma
id|name2
comma
id|email2
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_mailmap
r_int
id|read_mailmap
c_func
(paren
r_struct
id|string_list
op_star
id|map
comma
r_char
op_star
op_star
id|repo_abbrev
)paren
(brace
id|map-&gt;strdup_strings
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* each failure returns 1, so &gt;1 means both calls failed */
r_return
id|read_single_mailmap
c_func
(paren
id|map
comma
l_string|&quot;.mailmap&quot;
comma
id|repo_abbrev
)paren
op_plus
id|read_single_mailmap
c_func
(paren
id|map
comma
id|git_mailmap_file
comma
id|repo_abbrev
)paren
OG
l_int|1
suffix:semicolon
)brace
DECL|function|clear_mailmap
r_void
id|clear_mailmap
c_func
(paren
r_struct
id|string_list
op_star
id|map
)paren
(brace
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: clearing %d entries...&bslash;n&quot;
comma
id|map-&gt;nr
)paren
suffix:semicolon
id|map-&gt;strdup_strings
op_assign
l_int|1
suffix:semicolon
id|string_list_clear_func
c_func
(paren
id|map
comma
id|free_mailmap_entry
)paren
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;mailmap: cleared&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|map_user
r_int
id|map_user
c_func
(paren
r_struct
id|string_list
op_star
id|map
comma
r_char
op_star
id|email
comma
r_int
id|maxlen_email
comma
r_char
op_star
id|name
comma
r_int
id|maxlen_name
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_struct
id|mailmap_entry
op_star
id|me
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
comma
op_star
id|mailbuf
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* figure out space requirement for email */
id|p
op_assign
id|strchr
c_func
(paren
id|email
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
multiline_comment|/* email passed in might not be wrapped in &lt;&gt;, but end with a &bslash;0 */
id|p
op_assign
id|memchr
c_func
(paren
id|email
comma
l_char|&squot;&bslash;0&squot;
comma
id|maxlen_email
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
id|email
op_plus
l_int|1
OL
r_sizeof
(paren
id|buf
)paren
)paren
id|mailbuf
op_assign
id|buf
suffix:semicolon
r_else
id|mailbuf
op_assign
id|xmalloc
c_func
(paren
id|p
id|email
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* downcase the email address */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|p
id|email
suffix:semicolon
id|i
op_increment
)paren
id|mailbuf
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|email
(braket
id|i
)braket
)paren
suffix:semicolon
id|mailbuf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;map_user: map &squot;%s&squot; &lt;%s&gt;&bslash;n&quot;
comma
id|name
comma
id|mailbuf
)paren
suffix:semicolon
id|item
op_assign
id|string_list_lookup
c_func
(paren
id|mailbuf
comma
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item
op_ne
l_int|NULL
)paren
(brace
id|me
op_assign
(paren
r_struct
id|mailmap_entry
op_star
)paren
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|me-&gt;namemap.nr
)paren
(brace
multiline_comment|/* The item has multiple items, so we&squot;ll look up on name too */
multiline_comment|/* If the name is not found, we choose the simple entry      */
r_struct
id|string_list_item
op_star
id|subitem
op_assign
id|string_list_lookup
c_func
(paren
id|name
comma
op_amp
id|me-&gt;namemap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subitem
)paren
id|item
op_assign
id|subitem
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mailbuf
op_ne
id|buf
)paren
id|free
c_func
(paren
id|mailbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item
op_ne
l_int|NULL
)paren
(brace
r_struct
id|mailmap_info
op_star
id|mi
op_assign
(paren
r_struct
id|mailmap_info
op_star
)paren
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;name
op_eq
l_int|NULL
op_logical_and
(paren
id|mi-&gt;email
op_eq
l_int|NULL
op_logical_or
id|maxlen_email
op_eq
l_int|0
)paren
)paren
(brace
id|debug_mm
c_func
(paren
l_string|&quot;map_user:  -- (no simple mapping)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|maxlen_email
op_logical_and
id|mi-&gt;email
)paren
id|strlcpy
c_func
(paren
id|email
comma
id|mi-&gt;email
comma
id|maxlen_email
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxlen_name
op_logical_and
id|mi-&gt;name
)paren
id|strlcpy
c_func
(paren
id|name
comma
id|mi-&gt;name
comma
id|maxlen_name
)paren
suffix:semicolon
id|debug_mm
c_func
(paren
l_string|&quot;map_user:  to &squot;%s&squot; &lt;%s&gt;&bslash;n&quot;
comma
id|name
comma
id|mi-&gt;email
ques
c_cond
id|mi-&gt;email
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|debug_mm
c_func
(paren
l_string|&quot;map_user:  --&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_email
r_int
id|map_email
c_func
(paren
r_struct
id|string_list
op_star
id|map
comma
r_const
r_char
op_star
id|email
comma
r_char
op_star
id|name
comma
r_int
id|maxlen
)paren
(brace
r_return
id|map_user
c_func
(paren
id|map
comma
(paren
r_char
op_star
)paren
id|email
comma
l_int|0
comma
id|name
comma
id|maxlen
)paren
suffix:semicolon
)brace
eof
