multiline_comment|/*&n; * Builtin &quot;git grep&quot;&n; *&n; * Copyright (c) 2006 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &lt;regex.h&gt;
macro_line|#include &lt;fnmatch.h&gt;
multiline_comment|/*&n; * git grep pathspecs are somewhat different from diff-tree pathspecs;&n; * pathname wildcards are allowed.&n; */
DECL|function|pathspec_matches
r_static
r_int
id|pathspec_matches
c_func
(paren
r_const
r_char
op_star
op_star
id|paths
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|namelen
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|paths
op_logical_or
op_logical_neg
op_star
id|paths
)paren
r_return
l_int|1
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|paths
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|match
op_assign
id|paths
(braket
id|i
)braket
suffix:semicolon
r_int
id|matchlen
op_assign
id|strlen
c_func
(paren
id|match
)paren
suffix:semicolon
r_const
r_char
op_star
id|cp
comma
op_star
id|meta
suffix:semicolon
r_if
c_cond
(paren
(paren
id|matchlen
op_le
id|namelen
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
id|match
comma
id|matchlen
)paren
op_logical_and
(paren
id|match
(braket
id|matchlen
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
id|name
(braket
id|matchlen
)braket
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|name
(braket
id|matchlen
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|match
comma
id|name
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
id|namelen
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
multiline_comment|/* We are being asked if the directory (&quot;name&quot;) is worth&n;&t;&t; * descending into.&n;&t;&t; *&n;&t;&t; * Find the longest leading directory name that does&n;&t;&t; * not have metacharacter in the pathspec; the name&n;&t;&t; * we are looking at must overlap with that directory.&n;&t;&t; */
r_for
c_loop
(paren
id|cp
op_assign
id|match
comma
id|meta
op_assign
l_int|NULL
suffix:semicolon
id|cp
id|match
OL
id|matchlen
suffix:semicolon
id|cp
op_increment
)paren
(brace
r_char
id|ch
op_assign
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;*&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;[&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|meta
op_assign
id|cp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|meta
)paren
id|meta
op_assign
id|cp
suffix:semicolon
multiline_comment|/* fully literal */
r_if
c_cond
(paren
id|namelen
op_le
id|meta
id|match
)paren
(brace
multiline_comment|/* Looking at &quot;Documentation/&quot; and&n;&t;&t;&t; * the pattern says &quot;Documentation/howto/&quot;, or&n;&t;&t;&t; * &quot;Documentation/diff*.txt&quot;.  The name we&n;&t;&t;&t; * have should match prefix.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|match
comma
id|name
comma
id|namelen
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|meta
id|match
OL
id|namelen
)paren
(brace
multiline_comment|/* Looking at &quot;Documentation/howto/&quot; and&n;&t;&t;&t; * the pattern says &quot;Documentation/h*&quot;;&n;&t;&t;&t; * match up to &quot;Do.../h&quot;; this avoids descending&n;&t;&t;&t; * into &quot;Documentation/technical/&quot;.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|match
comma
id|name
comma
id|meta
id|match
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|grep_pat
r_struct
id|grep_pat
(brace
DECL|member|next
r_struct
id|grep_pat
op_star
id|next
suffix:semicolon
DECL|member|pattern
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|regexp
id|regex_t
id|regexp
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|grep_opt
r_struct
id|grep_opt
(brace
DECL|member|pattern_list
r_struct
id|grep_pat
op_star
id|pattern_list
suffix:semicolon
DECL|member|pattern_tail
r_struct
id|grep_pat
op_star
op_star
id|pattern_tail
suffix:semicolon
DECL|member|regexp
id|regex_t
id|regexp
suffix:semicolon
DECL|member|linenum
r_int
id|linenum
suffix:colon
l_int|1
suffix:semicolon
DECL|member|invert
r_int
id|invert
suffix:colon
l_int|1
suffix:semicolon
DECL|member|name_only
r_int
id|name_only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unmatch_name_only
r_int
id|unmatch_name_only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:colon
l_int|1
suffix:semicolon
DECL|member|word_regexp
r_int
id|word_regexp
suffix:colon
l_int|1
suffix:semicolon
DECL|macro|GREP_BINARY_DEFAULT
mdefine_line|#define GREP_BINARY_DEFAULT&t;0
DECL|macro|GREP_BINARY_NOMATCH
mdefine_line|#define GREP_BINARY_NOMATCH&t;1
DECL|macro|GREP_BINARY_TEXT
mdefine_line|#define GREP_BINARY_TEXT&t;2
DECL|member|binary
r_int
id|binary
suffix:colon
l_int|2
suffix:semicolon
DECL|member|regflags
r_int
id|regflags
suffix:semicolon
DECL|member|pre_context
r_int
id|pre_context
suffix:semicolon
DECL|member|post_context
r_int
id|post_context
suffix:semicolon
)brace
suffix:semicolon
DECL|function|add_pattern
r_static
r_void
id|add_pattern
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
id|pat
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|p-&gt;pattern
op_assign
id|pat
suffix:semicolon
op_star
id|opt-&gt;pattern_tail
op_assign
id|p
suffix:semicolon
id|opt-&gt;pattern_tail
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|compile_patterns
r_static
r_void
id|compile_patterns
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|opt-&gt;pattern_list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|err
op_assign
id|regcomp
c_func
(paren
op_amp
id|p-&gt;regexp
comma
id|p-&gt;pattern
comma
id|opt-&gt;regflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_char
id|errbuf
(braket
l_int|1024
)braket
suffix:semicolon
id|regerror
c_func
(paren
id|err
comma
op_amp
id|p-&gt;regexp
comma
id|errbuf
comma
l_int|1024
)paren
suffix:semicolon
id|regfree
c_func
(paren
op_amp
id|p-&gt;regexp
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: %s&quot;
comma
id|p-&gt;pattern
comma
id|errbuf
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|end_of_line
r_static
r_char
op_star
id|end_of_line
c_func
(paren
r_char
op_star
id|cp
comma
r_int
r_int
op_star
id|left
)paren
(brace
r_int
r_int
id|l
op_assign
op_star
id|left
suffix:semicolon
r_while
c_loop
(paren
id|l
op_logical_and
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|l
op_decrement
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
op_star
id|left
op_assign
id|l
suffix:semicolon
r_return
id|cp
suffix:semicolon
)brace
DECL|function|word_char
r_static
r_int
id|word_char
c_func
(paren
r_char
id|ch
)paren
(brace
r_return
id|isalnum
c_func
(paren
id|ch
)paren
op_logical_or
id|ch
op_eq
l_char|&squot;_&squot;
suffix:semicolon
)brace
DECL|function|show_line
r_static
r_void
id|show_line
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
id|bol
comma
r_const
r_char
op_star
id|eol
comma
r_const
r_char
op_star
id|name
comma
r_int
id|lno
comma
r_char
id|sign
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|name
comma
id|sign
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;linenum
)paren
id|printf
c_func
(paren
l_string|&quot;%d%c&quot;
comma
id|lno
comma
id|sign
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%.*s&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|eol
op_minus
id|bol
)paren
comma
id|bol
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NEEDSWORK: share code with diff.c&n; */
DECL|macro|FIRST_FEW_BYTES
mdefine_line|#define FIRST_FEW_BYTES 8000
DECL|function|buffer_is_binary
r_static
r_int
id|buffer_is_binary
c_func
(paren
r_const
r_char
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|FIRST_FEW_BYTES
OL
id|size
)paren
id|size
op_assign
id|FIRST_FEW_BYTES
suffix:semicolon
r_if
c_cond
(paren
id|memchr
c_func
(paren
id|ptr
comma
l_int|0
comma
id|size
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|grep_buffer
r_static
r_int
id|grep_buffer
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
id|name
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|size
)paren
(brace
r_char
op_star
id|bol
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|left
op_assign
id|size
suffix:semicolon
r_int
id|lno
op_assign
l_int|1
suffix:semicolon
r_struct
id|pre_context_line
(brace
r_char
op_star
id|bol
suffix:semicolon
r_char
op_star
id|eol
suffix:semicolon
)brace
op_star
id|prev
op_assign
l_int|NULL
comma
op_star
id|pcl
suffix:semicolon
r_int
id|last_hit
op_assign
l_int|0
suffix:semicolon
r_int
id|last_shown
op_assign
l_int|0
suffix:semicolon
r_int
id|binary_match_only
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|hunk_mark
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer_is_binary
c_func
(paren
id|buf
comma
id|size
)paren
)paren
(brace
r_switch
c_cond
(paren
id|opt-&gt;binary
)paren
(brace
r_case
id|GREP_BINARY_DEFAULT
suffix:colon
id|binary_match_only
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GREP_BINARY_NOMATCH
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Assume unmatch */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|opt-&gt;pre_context
)paren
id|prev
op_assign
id|xcalloc
c_func
(paren
id|opt-&gt;pre_context
comma
r_sizeof
(paren
op_star
id|prev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;pre_context
op_logical_or
id|opt-&gt;post_context
)paren
id|hunk_mark
op_assign
l_string|&quot;--&bslash;n&quot;
suffix:semicolon
r_while
c_loop
(paren
id|left
)paren
(brace
id|regmatch_t
id|pmatch
(braket
l_int|10
)braket
suffix:semicolon
r_char
op_star
id|eol
comma
id|ch
suffix:semicolon
r_int
id|hit
op_assign
l_int|0
suffix:semicolon
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
id|eol
op_assign
id|end_of_line
c_func
(paren
id|bol
comma
op_amp
id|left
)paren
suffix:semicolon
id|ch
op_assign
op_star
id|eol
suffix:semicolon
op_star
id|eol
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|opt-&gt;pattern_list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
id|regex_t
op_star
id|exp
op_assign
op_amp
id|p-&gt;regexp
suffix:semicolon
id|hit
op_assign
op_logical_neg
id|regexec
c_func
(paren
id|exp
comma
id|bol
comma
id|ARRAY_SIZE
c_func
(paren
id|pmatch
)paren
comma
id|pmatch
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hit
op_logical_and
id|opt-&gt;word_regexp
)paren
(brace
multiline_comment|/* Match beginning must be either&n;&t;&t;&t;&t; * beginning of the line, or at word&n;&t;&t;&t;&t; * boundary (i.e. the last char must&n;&t;&t;&t;&t; * not be alnum or underscore).&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
OL
l_int|0
)paren
op_logical_or
(paren
id|eol
id|bol
)paren
op_le
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
op_logical_or
(paren
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_eo
OL
l_int|0
)paren
op_logical_or
(paren
id|eol
id|bol
)paren
OL
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_eo
)paren
id|die
c_func
(paren
l_string|&quot;regexp returned nonsense&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
op_ne
l_int|0
op_logical_and
id|word_char
c_func
(paren
id|bol
(braket
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
op_minus
l_int|1
)braket
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* not a word boundary */
r_if
c_cond
(paren
(paren
id|eol
op_minus
id|bol
)paren
OL
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_eo
op_logical_and
id|word_char
c_func
(paren
id|bol
(braket
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_eo
)braket
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* not a word boundary */
)brace
r_if
c_cond
(paren
id|hit
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* &quot;grep -v -e foo -e bla&quot; should list lines&n;&t;&t; * that do not have either, so inversion should&n;&t;&t; * be done outside.&n;&t;&t; */
r_if
c_cond
(paren
id|opt-&gt;invert
)paren
id|hit
op_assign
op_logical_neg
id|hit
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;unmatch_name_only
)paren
(brace
r_if
c_cond
(paren
id|hit
)paren
r_return
l_int|0
suffix:semicolon
r_goto
id|next_line
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hit
)paren
(brace
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|binary_match_only
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Binary file %s matches&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;name_only
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Hit at this line.  If we haven&squot;t shown the&n;&t;&t;&t; * pre-context lines, we would need to show them.&n;&t;&t;&t; * When asked to do &quot;count&quot;, this still show&n;&t;&t;&t; * the context which is nonsense, but the user&n;&t;&t;&t; * deserves to get that ;-).&n;&t;&t;&t; */
r_if
c_cond
(paren
id|opt-&gt;pre_context
)paren
(brace
r_int
id|from
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;pre_context
OL
id|lno
)paren
id|from
op_assign
id|lno
id|opt-&gt;pre_context
suffix:semicolon
r_else
id|from
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|from
op_le
id|last_shown
)paren
id|from
op_assign
id|last_shown
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|last_shown
op_logical_and
id|from
op_ne
id|last_shown
op_plus
l_int|1
)paren
id|printf
c_func
(paren
id|hunk_mark
)paren
suffix:semicolon
r_while
c_loop
(paren
id|from
OL
id|lno
)paren
(brace
id|pcl
op_assign
op_amp
id|prev
(braket
id|lno
op_minus
id|from
op_minus
l_int|1
)braket
suffix:semicolon
id|show_line
c_func
(paren
id|opt
comma
id|pcl-&gt;bol
comma
id|pcl-&gt;eol
comma
id|name
comma
id|from
comma
l_char|&squot;-&squot;
)paren
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
id|last_shown
op_assign
id|lno
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_shown
op_logical_and
id|lno
op_ne
id|last_shown
op_plus
l_int|1
)paren
id|printf
c_func
(paren
id|hunk_mark
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;count
)paren
id|show_line
c_func
(paren
id|opt
comma
id|bol
comma
id|eol
comma
id|name
comma
id|lno
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|last_shown
op_assign
id|last_hit
op_assign
id|lno
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|last_hit
op_logical_and
id|lno
op_le
id|last_hit
op_plus
id|opt-&gt;post_context
)paren
(brace
multiline_comment|/* If the last hit is within the post context,&n;&t;&t;&t; * we need to show this line.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|last_shown
op_logical_and
id|lno
op_ne
id|last_shown
op_plus
l_int|1
)paren
id|printf
c_func
(paren
id|hunk_mark
)paren
suffix:semicolon
id|show_line
c_func
(paren
id|opt
comma
id|bol
comma
id|eol
comma
id|name
comma
id|lno
comma
l_char|&squot;-&squot;
)paren
suffix:semicolon
id|last_shown
op_assign
id|lno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;pre_context
)paren
(brace
id|memmove
c_func
(paren
id|prev
op_plus
l_int|1
comma
id|prev
comma
(paren
id|opt-&gt;pre_context
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|prev
)paren
)paren
suffix:semicolon
id|prev-&gt;bol
op_assign
id|bol
suffix:semicolon
id|prev-&gt;eol
op_assign
id|eol
suffix:semicolon
)brace
id|next_line
suffix:colon
op_star
id|eol
op_assign
id|ch
suffix:semicolon
id|bol
op_assign
id|eol
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
r_break
suffix:semicolon
id|left
op_decrement
suffix:semicolon
id|lno
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;unmatch_name_only
)paren
(brace
multiline_comment|/* We did not see any hit, so we want to show this */
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* NEEDSWORK:&n;&t; * The real &quot;grep -c foo *.c&quot; gives many &quot;bar.c:0&quot; lines,&n;&t; * which feels mostly useless but sometimes useful.  Maybe&n;&t; * make it another option?  For now suppress them.&n;&t; */
r_if
c_cond
(paren
id|opt-&gt;count
op_logical_and
id|count
)paren
id|printf
c_func
(paren
l_string|&quot;%s:%u&bslash;n&quot;
comma
id|name
comma
id|count
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|last_hit
suffix:semicolon
)brace
DECL|function|grep_sha1
r_static
r_int
id|grep_sha1
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|hit
suffix:semicolon
id|data
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot;: unable to read %s&quot;
comma
id|name
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|hit
op_assign
id|grep_buffer
c_func
(paren
id|opt
comma
id|name
comma
id|data
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|hit
suffix:semicolon
)brace
DECL|function|grep_file
r_static
r_int
id|grep_file
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|filename
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
id|err_ret
suffix:colon
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot;: %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|st.st_size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* empty file -- no grep hit */
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_goto
id|err_ret
suffix:semicolon
id|data
op_assign
id|xmalloc
c_func
(paren
id|st.st_size
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st.st_size
op_ne
id|xread
c_func
(paren
id|i
comma
id|data
comma
id|st.st_size
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot;: short read %s&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|close
c_func
(paren
id|i
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|close
c_func
(paren
id|i
)paren
suffix:semicolon
id|i
op_assign
id|grep_buffer
c_func
(paren
id|opt
comma
id|filename
comma
id|data
comma
id|st.st_size
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|grep_cache
r_static
r_int
id|grep_cache
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
op_star
id|paths
comma
r_int
id|cached
)paren
(brace
r_int
id|hit
op_assign
l_int|0
suffix:semicolon
r_int
id|nr
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
id|nr
OL
id|active_nr
suffix:semicolon
id|nr
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|nr
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathspec_matches
c_func
(paren
id|paths
comma
id|ce-&gt;name
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cached
)paren
id|hit
op_or_assign
id|grep_sha1
c_func
(paren
id|opt
comma
id|ce-&gt;sha1
comma
id|ce-&gt;name
)paren
suffix:semicolon
r_else
id|hit
op_or_assign
id|grep_file
c_func
(paren
id|opt
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|hit
suffix:semicolon
)brace
DECL|function|grep_tree
r_static
r_int
id|grep_tree
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
op_star
id|paths
comma
r_struct
id|tree_desc
op_star
id|tree
comma
r_const
r_char
op_star
id|tree_name
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_int
id|mode
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|hit
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|path
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_char
op_star
id|down
suffix:semicolon
r_char
op_star
id|path_buf
op_assign
id|xmalloc
c_func
(paren
id|PATH_MAX
op_plus
id|strlen
c_func
(paren
id|tree_name
)paren
op_plus
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tree_name
(braket
l_int|0
)braket
)paren
(brace
r_int
id|offset
op_assign
id|sprintf
c_func
(paren
id|path_buf
comma
l_string|&quot;%s:&quot;
comma
id|tree_name
)paren
suffix:semicolon
id|down
op_assign
id|path_buf
op_plus
id|offset
suffix:semicolon
id|strcat
c_func
(paren
id|down
comma
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
id|down
op_assign
id|path_buf
suffix:semicolon
id|strcpy
c_func
(paren
id|down
comma
id|base
)paren
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|path_buf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tree-&gt;size
)paren
(brace
r_int
id|pathlen
suffix:semicolon
id|sha1
op_assign
id|tree_entry_extract
c_func
(paren
id|tree
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path_buf
op_plus
id|len
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
multiline_comment|/* Match &quot;abc/&quot; against pathspec to&n;&t;&t;&t; * decide if we want to descend into &quot;abc&quot;&n;&t;&t;&t; * directory.&n;&t;&t;&t; */
id|strcpy
c_func
(paren
id|path_buf
op_plus
id|len
op_plus
id|pathlen
comma
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathspec_matches
c_func
(paren
id|paths
comma
id|down
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
id|hit
op_or_assign
id|grep_sha1
c_func
(paren
id|opt
comma
id|sha1
comma
id|path_buf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|tree_desc
id|sub
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
id|data
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|sub.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|sub.buf
op_assign
id|data
suffix:semicolon
id|hit
op_or_assign
id|grep_tree
c_func
(paren
id|opt
comma
id|paths
comma
op_amp
id|sub
comma
id|tree_name
comma
id|down
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
id|update_tree_entry
c_func
(paren
id|tree
)paren
suffix:semicolon
)brace
r_return
id|hit
suffix:semicolon
)brace
DECL|function|grep_object
r_static
r_int
id|grep_object
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_const
r_char
op_star
op_star
id|paths
comma
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|obj-&gt;type
comma
id|blob_type
)paren
)paren
r_return
id|grep_sha1
c_func
(paren
id|opt
comma
id|obj-&gt;sha1
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|obj-&gt;type
comma
id|commit_type
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|obj-&gt;type
comma
id|tree_type
)paren
)paren
(brace
r_struct
id|tree_desc
id|tree
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_int
id|hit
suffix:semicolon
id|data
op_assign
id|read_object_with_reference
c_func
(paren
id|obj-&gt;sha1
comma
id|tree_type
comma
op_amp
id|tree.size
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree (%s)&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|tree.buf
op_assign
id|data
suffix:semicolon
id|hit
op_assign
id|grep_tree
c_func
(paren
id|opt
comma
id|paths
comma
op_amp
id|tree
comma
id|name
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|hit
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;unable to grep from object of type %s&quot;
comma
id|obj-&gt;type
)paren
suffix:semicolon
)brace
DECL|variable|builtin_grep_usage
r_static
r_const
r_char
id|builtin_grep_usage
(braket
)braket
op_assign
l_string|&quot;git-grep &lt;option&gt;* &lt;rev&gt;* [-e] &lt;pattern&gt; [&lt;path&gt;...]&quot;
suffix:semicolon
DECL|function|cmd_grep
r_int
id|cmd_grep
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_int
id|hit
op_assign
l_int|0
suffix:semicolon
r_int
id|no_more_flags
op_assign
l_int|0
suffix:semicolon
r_int
id|seen_noncommit
op_assign
l_int|0
suffix:semicolon
r_int
id|cached
op_assign
l_int|0
suffix:semicolon
r_struct
id|grep_opt
id|opt
suffix:semicolon
r_struct
id|object_list
op_star
id|list
comma
op_star
op_star
id|tail
comma
op_star
id|object_list
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_const
r_char
op_star
op_star
id|paths
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opt
comma
l_int|0
comma
r_sizeof
(paren
id|opt
)paren
)paren
suffix:semicolon
id|opt.pattern_tail
op_assign
op_amp
id|opt.pattern_list
suffix:semicolon
id|opt.regflags
op_assign
id|REG_NEWLINE
suffix:semicolon
multiline_comment|/*&n;&t; * No point using rev_info, really.&n;&t; */
r_while
c_loop
(paren
l_int|1
OL
id|argc
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--cached&quot;
comma
id|arg
)paren
)paren
(brace
id|cached
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-a&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--text&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.binary
op_assign
id|GREP_BINARY_TEXT
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-i&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--ignore-case&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.regflags
op_or_assign
id|REG_ICASE
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-I&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.binary
op_assign
id|GREP_BINARY_NOMATCH
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-v&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--invert-match&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.invert
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-E&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--extended-regexp&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.regflags
op_or_assign
id|REG_EXTENDED
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-G&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--basic-regexp&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.regflags
op_and_assign
op_complement
id|REG_EXTENDED
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-n&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.linenum
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-H&quot;
comma
id|arg
)paren
)paren
(brace
multiline_comment|/* We always show the pathname, so this&n;&t;&t;&t; * is a noop.&n;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-l&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--files-with-matches&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.name_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-L&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--files-without-match&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.unmatch_name_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-c&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--count&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.count
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-w&quot;
comma
id|arg
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--word-regexp&quot;
comma
id|arg
)paren
)paren
(brace
id|opt.word_regexp
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;-A&quot;
comma
id|arg
comma
l_int|2
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;-B&quot;
comma
id|arg
comma
l_int|2
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;-C&quot;
comma
id|arg
comma
l_int|2
)paren
op_logical_or
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
op_logical_and
l_char|&squot;1&squot;
op_le
id|arg
(braket
l_int|1
)braket
op_logical_and
id|arg
(braket
l_int|1
)braket
op_le
l_char|&squot;9&squot;
)paren
)paren
(brace
r_int
id|num
suffix:semicolon
r_const
r_char
op_star
id|scan
suffix:semicolon
r_switch
c_cond
(paren
id|arg
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;A&squot;
suffix:colon
r_case
l_char|&squot;B&squot;
suffix:colon
r_case
l_char|&squot;C&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|arg
(braket
l_int|2
)braket
)paren
(brace
r_if
c_cond
(paren
id|argc
op_le
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_grep_usage
)paren
suffix:semicolon
id|scan
op_assign
op_star
op_increment
id|argv
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
r_else
id|scan
op_assign
id|arg
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|scan
op_assign
id|arg
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|scan
comma
l_string|&quot;%u&quot;
comma
op_amp
id|num
)paren
op_ne
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_grep_usage
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|arg
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;A&squot;
suffix:colon
id|opt.post_context
op_assign
id|num
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_case
l_char|&squot;C&squot;
suffix:colon
id|opt.post_context
op_assign
id|num
suffix:semicolon
r_case
l_char|&squot;B&squot;
suffix:colon
id|opt.pre_context
op_assign
id|num
suffix:semicolon
r_break
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-e&quot;
comma
id|arg
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|1
OL
id|argc
)paren
(brace
id|add_pattern
c_func
(paren
op_amp
id|opt
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|builtin_grep_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--&quot;
comma
id|arg
)paren
)paren
(brace
id|no_more_flags
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Either unrecognized option or a single pattern */
r_if
c_cond
(paren
op_logical_neg
id|no_more_flags
op_logical_and
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|builtin_grep_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt.pattern_list
)paren
(brace
id|add_pattern
c_func
(paren
op_amp
id|opt
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We are looking at the first path or rev;&n;&t;&t;&t; * it is found at argv[0] after leaving the&n;&t;&t;&t; * loop.&n;&t;&t;&t; */
id|argc
op_increment
suffix:semicolon
id|argv
op_decrement
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|opt.pattern_list
)paren
id|die
c_func
(paren
l_string|&quot;no pattern given.&quot;
)paren
suffix:semicolon
id|compile_patterns
c_func
(paren
op_amp
id|opt
)paren
suffix:semicolon
id|tail
op_assign
op_amp
id|object_list
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
)paren
(brace
r_struct
id|object
op_star
id|object
suffix:semicolon
r_struct
id|object_list
op_star
id|elem
suffix:semicolon
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
id|die
c_func
(paren
l_string|&quot;bad object %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|elem
op_assign
id|object_list_insert
c_func
(paren
id|object
comma
id|tail
)paren
suffix:semicolon
id|elem-&gt;name
op_assign
id|arg
suffix:semicolon
id|tail
op_assign
op_amp
id|elem-&gt;next
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|1
OL
id|argc
)paren
id|paths
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
op_plus
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|prefix
)paren
(brace
id|paths
op_assign
id|xcalloc
c_func
(paren
l_int|2
comma
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
id|paths
(braket
l_int|0
)braket
op_assign
id|prefix
suffix:semicolon
id|paths
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|object_list
)paren
r_return
op_logical_neg
id|grep_cache
c_func
(paren
op_amp
id|opt
comma
id|paths
comma
id|cached
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do not walk &quot;grep -e foo master next pu -- Documentation/&quot;&n;&t; * but do walk &quot;grep -e foo master..next -- Documentation/&quot;.&n;&t; * Ranged request mixed with a blob or tree object, like&n;&t; * &quot;grep -e foo v1.0.0:Documentation/ master..next&quot;&n;&t; * so detect that and complain.&n;&t; */
r_for
c_loop
(paren
id|list
op_assign
id|object_list
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_struct
id|object
op_star
id|real_obj
suffix:semicolon
id|real_obj
op_assign
id|deref_tag
c_func
(paren
id|list-&gt;item
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|real_obj-&gt;type
comma
id|commit_type
)paren
)paren
id|seen_noncommit
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cached
)paren
id|die
c_func
(paren
l_string|&quot;both --cached and revisions given.&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|object_list
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_struct
id|object
op_star
id|real_obj
suffix:semicolon
id|real_obj
op_assign
id|deref_tag
c_func
(paren
id|list-&gt;item
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|grep_object
c_func
(paren
op_amp
id|opt
comma
id|paths
comma
id|real_obj
comma
id|list-&gt;name
)paren
)paren
id|hit
op_assign
l_int|1
suffix:semicolon
)brace
r_return
op_logical_neg
id|hit
suffix:semicolon
)brace
eof
