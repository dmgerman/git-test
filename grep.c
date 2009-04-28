macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;grep.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
DECL|function|append_header_grep_pattern
r_void
id|append_header_grep_pattern
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_enum
id|grep_header_field
id|field
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
id|p-&gt;origin
op_assign
l_string|&quot;header&quot;
suffix:semicolon
id|p-&gt;no
op_assign
l_int|0
suffix:semicolon
id|p-&gt;token
op_assign
id|GREP_PATTERN_HEAD
suffix:semicolon
id|p-&gt;field
op_assign
id|field
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
DECL|function|append_grep_pattern
r_void
id|append_grep_pattern
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
comma
r_const
r_char
op_star
id|origin
comma
r_int
id|no
comma
r_enum
id|grep_pat_token
id|t
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
id|p-&gt;origin
op_assign
id|origin
suffix:semicolon
id|p-&gt;no
op_assign
id|no
suffix:semicolon
id|p-&gt;token
op_assign
id|t
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
DECL|function|is_fixed
r_static
r_int
id|is_fixed
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_while
c_loop
(paren
op_star
id|s
op_logical_and
op_logical_neg
id|is_regex_special
c_func
(paren
op_star
id|s
)paren
)paren
id|s
op_increment
suffix:semicolon
r_return
op_logical_neg
op_star
id|s
suffix:semicolon
)brace
DECL|function|compile_regexp
r_static
r_void
id|compile_regexp
c_func
(paren
r_struct
id|grep_pat
op_star
id|p
comma
r_struct
id|grep_opt
op_star
id|opt
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;fixed
op_logical_or
id|is_fixed
c_func
(paren
id|p-&gt;pattern
)paren
)paren
id|p-&gt;fixed
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;regflags
op_amp
id|REG_ICASE
)paren
id|p-&gt;fixed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;fixed
)paren
r_return
suffix:semicolon
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
r_char
id|where
(braket
l_int|1024
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;no
)paren
id|sprintf
c_func
(paren
id|where
comma
l_string|&quot;In &squot;%s&squot; at %d, &quot;
comma
id|p-&gt;origin
comma
id|p-&gt;no
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;origin
)paren
id|sprintf
c_func
(paren
id|where
comma
l_string|&quot;%s, &quot;
comma
id|p-&gt;origin
)paren
suffix:semicolon
r_else
id|where
(braket
l_int|0
)braket
op_assign
l_int|0
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
l_string|&quot;%s&squot;%s&squot;: %s&quot;
comma
id|where
comma
id|p-&gt;pattern
comma
id|errbuf
)paren
suffix:semicolon
)brace
)brace
r_static
r_struct
id|grep_expr
op_star
id|compile_pattern_or
c_func
(paren
r_struct
id|grep_pat
op_star
op_star
)paren
suffix:semicolon
DECL|function|compile_pattern_atom
r_static
r_struct
id|grep_expr
op_star
id|compile_pattern_atom
c_func
(paren
r_struct
id|grep_pat
op_star
op_star
id|list
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
r_struct
id|grep_expr
op_star
id|x
suffix:semicolon
id|p
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;token
)paren
(brace
r_case
id|GREP_PATTERN
suffix:colon
multiline_comment|/* atom */
r_case
id|GREP_PATTERN_HEAD
suffix:colon
r_case
id|GREP_PATTERN_BODY
suffix:colon
id|x
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|grep_expr
)paren
)paren
suffix:semicolon
id|x-&gt;node
op_assign
id|GREP_NODE_ATOM
suffix:semicolon
id|x-&gt;u.atom
op_assign
id|p
suffix:semicolon
op_star
id|list
op_assign
id|p-&gt;next
suffix:semicolon
r_return
id|x
suffix:semicolon
r_case
id|GREP_OPEN_PAREN
suffix:colon
op_star
id|list
op_assign
id|p-&gt;next
suffix:semicolon
id|x
op_assign
id|compile_pattern_or
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|list
op_logical_or
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|token
op_ne
id|GREP_CLOSE_PAREN
)paren
id|die
c_func
(paren
l_string|&quot;unmatched parenthesis&quot;
)paren
suffix:semicolon
op_star
id|list
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_return
id|x
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|compile_pattern_not
r_static
r_struct
id|grep_expr
op_star
id|compile_pattern_not
c_func
(paren
r_struct
id|grep_pat
op_star
op_star
id|list
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
r_struct
id|grep_expr
op_star
id|x
suffix:semicolon
id|p
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;token
)paren
(brace
r_case
id|GREP_NOT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;next
)paren
id|die
c_func
(paren
l_string|&quot;--not not followed by pattern expression&quot;
)paren
suffix:semicolon
op_star
id|list
op_assign
id|p-&gt;next
suffix:semicolon
id|x
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|grep_expr
)paren
)paren
suffix:semicolon
id|x-&gt;node
op_assign
id|GREP_NODE_NOT
suffix:semicolon
id|x-&gt;u.unary
op_assign
id|compile_pattern_not
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;u.unary
)paren
id|die
c_func
(paren
l_string|&quot;--not followed by non pattern expression&quot;
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
r_default
suffix:colon
r_return
id|compile_pattern_atom
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
)brace
DECL|function|compile_pattern_and
r_static
r_struct
id|grep_expr
op_star
id|compile_pattern_and
c_func
(paren
r_struct
id|grep_pat
op_star
op_star
id|list
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
r_struct
id|grep_expr
op_star
id|x
comma
op_star
id|y
comma
op_star
id|z
suffix:semicolon
id|x
op_assign
id|compile_pattern_not
c_func
(paren
id|list
)paren
suffix:semicolon
id|p
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
id|p-&gt;token
op_eq
id|GREP_AND
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;next
)paren
id|die
c_func
(paren
l_string|&quot;--and not followed by pattern expression&quot;
)paren
suffix:semicolon
op_star
id|list
op_assign
id|p-&gt;next
suffix:semicolon
id|y
op_assign
id|compile_pattern_and
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|y
)paren
id|die
c_func
(paren
l_string|&quot;--and not followed by pattern expression&quot;
)paren
suffix:semicolon
id|z
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|grep_expr
)paren
)paren
suffix:semicolon
id|z-&gt;node
op_assign
id|GREP_NODE_AND
suffix:semicolon
id|z-&gt;u.binary.left
op_assign
id|x
suffix:semicolon
id|z-&gt;u.binary.right
op_assign
id|y
suffix:semicolon
r_return
id|z
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
DECL|function|compile_pattern_or
r_static
r_struct
id|grep_expr
op_star
id|compile_pattern_or
c_func
(paren
r_struct
id|grep_pat
op_star
op_star
id|list
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
r_struct
id|grep_expr
op_star
id|x
comma
op_star
id|y
comma
op_star
id|z
suffix:semicolon
id|x
op_assign
id|compile_pattern_and
c_func
(paren
id|list
)paren
suffix:semicolon
id|p
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|x
op_logical_and
id|p
op_logical_and
id|p-&gt;token
op_ne
id|GREP_CLOSE_PAREN
)paren
(brace
id|y
op_assign
id|compile_pattern_or
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|y
)paren
id|die
c_func
(paren
l_string|&quot;not a pattern expression %s&quot;
comma
id|p-&gt;pattern
)paren
suffix:semicolon
id|z
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|grep_expr
)paren
)paren
suffix:semicolon
id|z-&gt;node
op_assign
id|GREP_NODE_OR
suffix:semicolon
id|z-&gt;u.binary.left
op_assign
id|x
suffix:semicolon
id|z-&gt;u.binary.right
op_assign
id|y
suffix:semicolon
r_return
id|z
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
DECL|function|compile_pattern_expr
r_static
r_struct
id|grep_expr
op_star
id|compile_pattern_expr
c_func
(paren
r_struct
id|grep_pat
op_star
op_star
id|list
)paren
(brace
r_return
id|compile_pattern_or
c_func
(paren
id|list
)paren
suffix:semicolon
)brace
DECL|function|compile_grep_patterns
r_void
id|compile_grep_patterns
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
r_if
c_cond
(paren
id|opt-&gt;all_match
)paren
id|opt-&gt;extended
op_assign
l_int|1
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
r_switch
c_cond
(paren
id|p-&gt;token
)paren
(brace
r_case
id|GREP_PATTERN
suffix:colon
multiline_comment|/* atom */
r_case
id|GREP_PATTERN_HEAD
suffix:colon
r_case
id|GREP_PATTERN_BODY
suffix:colon
id|compile_regexp
c_func
(paren
id|p
comma
id|opt
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|opt-&gt;extended
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;extended
)paren
r_return
suffix:semicolon
multiline_comment|/* Then bundle them up in an expression.&n;&t; * A classic recursive descent parser would do.&n;&t; */
id|p
op_assign
id|opt-&gt;pattern_list
suffix:semicolon
id|opt-&gt;pattern_expression
op_assign
id|compile_pattern_expr
c_func
(paren
op_amp
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|die
c_func
(paren
l_string|&quot;incomplete pattern expression: %s&quot;
comma
id|p-&gt;pattern
)paren
suffix:semicolon
)brace
DECL|function|free_pattern_expr
r_static
r_void
id|free_pattern_expr
c_func
(paren
r_struct
id|grep_expr
op_star
id|x
)paren
(brace
r_switch
c_cond
(paren
id|x-&gt;node
)paren
(brace
r_case
id|GREP_NODE_ATOM
suffix:colon
r_break
suffix:semicolon
r_case
id|GREP_NODE_NOT
suffix:colon
id|free_pattern_expr
c_func
(paren
id|x-&gt;u.unary
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GREP_NODE_AND
suffix:colon
r_case
id|GREP_NODE_OR
suffix:colon
id|free_pattern_expr
c_func
(paren
id|x-&gt;u.binary.left
)paren
suffix:semicolon
id|free_pattern_expr
c_func
(paren
id|x-&gt;u.binary.right
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|free
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|free_grep_patterns
r_void
id|free_grep_patterns
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
comma
op_star
id|n
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
id|n
)paren
(brace
id|n
op_assign
id|p-&gt;next
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;token
)paren
(brace
r_case
id|GREP_PATTERN
suffix:colon
multiline_comment|/* atom */
r_case
id|GREP_PATTERN_HEAD
suffix:colon
r_case
id|GREP_PATTERN_BODY
suffix:colon
id|regfree
c_func
(paren
op_amp
id|p-&gt;regexp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|free
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;extended
)paren
r_return
suffix:semicolon
id|free_pattern_expr
c_func
(paren
id|opt-&gt;pattern_expression
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|opt-&gt;null_following_name
)paren
id|sign
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;pathname
)paren
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
DECL|function|show_name
r_static
r_void
id|show_name
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
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|name
comma
id|opt-&gt;null_following_name
ques
c_cond
l_char|&squot;&bslash;0&squot;
suffix:colon
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|fixmatch
r_static
r_int
id|fixmatch
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_char
op_star
id|line
comma
id|regmatch_t
op_star
id|match
)paren
(brace
r_char
op_star
id|hit
op_assign
id|strstr
c_func
(paren
id|line
comma
id|pattern
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hit
)paren
(brace
id|match-&gt;rm_so
op_assign
id|match-&gt;rm_eo
op_assign
l_int|1
suffix:semicolon
r_return
id|REG_NOMATCH
suffix:semicolon
)brace
r_else
(brace
id|match-&gt;rm_so
op_assign
id|hit
id|line
suffix:semicolon
id|match-&gt;rm_eo
op_assign
id|match-&gt;rm_so
op_plus
id|strlen
c_func
(paren
id|pattern
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|strip_timestamp
r_static
r_int
id|strip_timestamp
c_func
(paren
r_char
op_star
id|bol
comma
r_char
op_star
op_star
id|eol_p
)paren
(brace
r_char
op_star
id|eol
op_assign
op_star
id|eol_p
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_while
c_loop
(paren
id|bol
OL
op_decrement
id|eol
)paren
(brace
r_if
c_cond
(paren
op_star
id|eol
op_ne
l_char|&squot;&gt;&squot;
)paren
r_continue
suffix:semicolon
op_star
id|eol_p
op_assign
op_increment
id|eol
suffix:semicolon
id|ch
op_assign
op_star
id|eol
suffix:semicolon
op_star
id|eol
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|ch
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|field
r_const
r_char
op_star
id|field
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|variable|header_field
)brace
id|header_field
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;author &quot;
comma
l_int|7
)brace
comma
(brace
l_string|&quot;committer &quot;
comma
l_int|10
)brace
comma
)brace
suffix:semicolon
DECL|function|match_one_pattern
r_static
r_int
id|match_one_pattern
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_struct
id|grep_pat
op_star
id|p
comma
r_char
op_star
id|bol
comma
r_char
op_star
id|eol
comma
r_enum
id|grep_context
id|ctx
)paren
(brace
r_int
id|hit
op_assign
l_int|0
suffix:semicolon
r_int
id|saved_ch
op_assign
l_int|0
suffix:semicolon
id|regmatch_t
id|pmatch
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;token
op_ne
id|GREP_PATTERN
)paren
op_logical_and
(paren
(paren
id|p-&gt;token
op_eq
id|GREP_PATTERN_HEAD
)paren
op_ne
(paren
id|ctx
op_eq
id|GREP_CONTEXT_HEAD
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;token
op_eq
id|GREP_PATTERN_HEAD
)paren
(brace
r_const
r_char
op_star
id|field
suffix:semicolon
r_int
id|len
suffix:semicolon
m_assert
(paren
id|p-&gt;field
OL
id|ARRAY_SIZE
c_func
(paren
id|header_field
)paren
)paren
suffix:semicolon
id|field
op_assign
id|header_field
(braket
id|p-&gt;field
)braket
dot
id|field
suffix:semicolon
id|len
op_assign
id|header_field
(braket
id|p-&gt;field
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|bol
comma
id|field
comma
id|len
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|bol
op_add_assign
id|len
suffix:semicolon
id|saved_ch
op_assign
id|strip_timestamp
c_func
(paren
id|bol
comma
op_amp
id|eol
)paren
suffix:semicolon
)brace
id|again
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;fixed
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
)brace
r_else
(brace
id|hit
op_assign
op_logical_neg
id|fixmatch
c_func
(paren
id|p-&gt;pattern
comma
id|bol
comma
id|pmatch
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hit
op_logical_and
id|opt-&gt;word_regexp
)paren
(brace
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
multiline_comment|/* Match beginning must be either beginning of the&n;&t;&t; * line, or at word boundary (i.e. the last char must&n;&t;&t; * not be a word char).  Similarly, match end must be&n;&t;&t; * either end of the line, or at word boundary&n;&t;&t; * (i.e. the next char must not be a word char).&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
op_eq
l_int|0
)paren
op_logical_or
op_logical_neg
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
op_logical_and
(paren
(paren
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_eo
op_eq
(paren
id|eol
op_minus
id|bol
)paren
)paren
op_logical_or
op_logical_neg
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
)paren
suffix:semicolon
r_else
id|hit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hit
op_logical_and
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
op_plus
id|bol
op_plus
l_int|1
OL
id|eol
)paren
(brace
multiline_comment|/* There could be more than one match on the&n;&t;&t;&t; * line, and the first match might not be&n;&t;&t;&t; * strict word match.  But later ones could be!&n;&t;&t;&t; * Forward to the next possible start, i.e. the&n;&t;&t;&t; * next position following a non-word char.&n;&t;&t;&t; */
id|bol
op_assign
id|pmatch
(braket
l_int|0
)braket
dot
id|rm_so
op_plus
id|bol
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|word_char
c_func
(paren
id|bol
(braket
l_int|1
)braket
)paren
op_logical_and
id|bol
OL
id|eol
)paren
id|bol
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bol
OL
id|eol
)paren
r_goto
id|again
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|p-&gt;token
op_eq
id|GREP_PATTERN_HEAD
op_logical_and
id|saved_ch
)paren
op_star
id|eol
op_assign
id|saved_ch
suffix:semicolon
r_return
id|hit
suffix:semicolon
)brace
DECL|function|match_expr_eval
r_static
r_int
id|match_expr_eval
c_func
(paren
r_struct
id|grep_opt
op_star
id|o
comma
r_struct
id|grep_expr
op_star
id|x
comma
r_char
op_star
id|bol
comma
r_char
op_star
id|eol
comma
r_enum
id|grep_context
id|ctx
comma
r_int
id|collect_hits
)paren
(brace
r_int
id|h
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid grep expression&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|x-&gt;node
)paren
(brace
r_case
id|GREP_NODE_ATOM
suffix:colon
id|h
op_assign
id|match_one_pattern
c_func
(paren
id|o
comma
id|x-&gt;u.atom
comma
id|bol
comma
id|eol
comma
id|ctx
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GREP_NODE_NOT
suffix:colon
id|h
op_assign
op_logical_neg
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.unary
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GREP_NODE_AND
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|collect_hits
)paren
r_return
(paren
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.left
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
op_logical_and
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.right
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
)paren
suffix:semicolon
id|h
op_assign
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.left
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
suffix:semicolon
id|h
op_and_assign
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.right
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GREP_NODE_OR
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|collect_hits
)paren
r_return
(paren
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.left
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
op_logical_or
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.right
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
)paren
suffix:semicolon
id|h
op_assign
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.left
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|0
)paren
suffix:semicolon
id|x-&gt;u.binary.left-&gt;hit
op_or_assign
id|h
suffix:semicolon
id|h
op_or_assign
id|match_expr_eval
c_func
(paren
id|o
comma
id|x-&gt;u.binary.right
comma
id|bol
comma
id|eol
comma
id|ctx
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;Unexpected node type (internal error) %d&quot;
comma
id|x-&gt;node
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|collect_hits
)paren
id|x-&gt;hit
op_or_assign
id|h
suffix:semicolon
r_return
id|h
suffix:semicolon
)brace
DECL|function|match_expr
r_static
r_int
id|match_expr
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_char
op_star
id|bol
comma
r_char
op_star
id|eol
comma
r_enum
id|grep_context
id|ctx
comma
r_int
id|collect_hits
)paren
(brace
r_struct
id|grep_expr
op_star
id|x
op_assign
id|opt-&gt;pattern_expression
suffix:semicolon
r_return
id|match_expr_eval
c_func
(paren
id|opt
comma
id|x
comma
id|bol
comma
id|eol
comma
id|ctx
comma
id|collect_hits
)paren
suffix:semicolon
)brace
DECL|function|match_line
r_static
r_int
id|match_line
c_func
(paren
r_struct
id|grep_opt
op_star
id|opt
comma
r_char
op_star
id|bol
comma
r_char
op_star
id|eol
comma
r_enum
id|grep_context
id|ctx
comma
r_int
id|collect_hits
)paren
(brace
r_struct
id|grep_pat
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;extended
)paren
r_return
id|match_expr
c_func
(paren
id|opt
comma
id|bol
comma
id|eol
comma
id|ctx
comma
id|collect_hits
)paren
suffix:semicolon
multiline_comment|/* we do not call with collect_hits without being extended */
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
r_if
c_cond
(paren
id|match_one_pattern
c_func
(paren
id|opt
comma
id|p
comma
id|bol
comma
id|eol
comma
id|ctx
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
DECL|function|grep_buffer_1
r_static
r_int
id|grep_buffer_1
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
comma
r_int
id|collect_hits
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
r_enum
id|grep_context
id|ctx
op_assign
id|GREP_CONTEXT_HEAD
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
r_char
op_star
id|eol
comma
id|ch
suffix:semicolon
r_int
id|hit
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
r_if
c_cond
(paren
(paren
id|ctx
op_eq
id|GREP_CONTEXT_HEAD
)paren
op_logical_and
(paren
id|eol
op_eq
id|bol
)paren
)paren
id|ctx
op_assign
id|GREP_CONTEXT_BODY
suffix:semicolon
id|hit
op_assign
id|match_line
c_func
(paren
id|opt
comma
id|bol
comma
id|eol
comma
id|ctx
comma
id|collect_hits
)paren
suffix:semicolon
op_star
id|eol
op_assign
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|collect_hits
)paren
r_goto
id|next_line
suffix:semicolon
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
id|opt-&gt;status_only
)paren
r_return
l_int|1
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
id|show_name
c_func
(paren
id|opt
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
id|fputs
c_func
(paren
id|hunk_mark
comma
id|stdout
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
id|fputs
c_func
(paren
id|hunk_mark
comma
id|stdout
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
id|fputs
c_func
(paren
id|hunk_mark
comma
id|stdout
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
id|free
c_func
(paren
id|prev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|collect_hits
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;status_only
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;unmatch_name_only
)paren
(brace
multiline_comment|/* We did not see any hit, so we want to show this */
id|show_name
c_func
(paren
id|opt
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
l_string|&quot;%s%c%u&bslash;n&quot;
comma
id|name
comma
id|opt-&gt;null_following_name
ques
c_cond
l_char|&squot;&bslash;0&squot;
suffix:colon
l_char|&squot;:&squot;
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
DECL|function|clr_hit_marker
r_static
r_void
id|clr_hit_marker
c_func
(paren
r_struct
id|grep_expr
op_star
id|x
)paren
(brace
multiline_comment|/* All-hit markers are meaningful only at the very top level&n;&t; * OR node.&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|x-&gt;hit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;node
op_ne
id|GREP_NODE_OR
)paren
r_return
suffix:semicolon
id|x-&gt;u.binary.left-&gt;hit
op_assign
l_int|0
suffix:semicolon
id|x
op_assign
id|x-&gt;u.binary.right
suffix:semicolon
)brace
)brace
DECL|function|chk_hit_marker
r_static
r_int
id|chk_hit_marker
c_func
(paren
r_struct
id|grep_expr
op_star
id|x
)paren
(brace
multiline_comment|/* Top level nodes have hit markers.  See if they all are hits */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;node
op_ne
id|GREP_NODE_OR
)paren
r_return
id|x-&gt;hit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;u.binary.left-&gt;hit
)paren
r_return
l_int|0
suffix:semicolon
id|x
op_assign
id|x-&gt;u.binary.right
suffix:semicolon
)brace
)brace
DECL|function|grep_buffer
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
multiline_comment|/*&n;&t; * we do not have to do the two-pass grep when we do not check&n;&t; * buffer-wide &quot;all-match&quot;.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;all_match
)paren
r_return
id|grep_buffer_1
c_func
(paren
id|opt
comma
id|name
comma
id|buf
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Otherwise the toplevel &quot;or&quot; terms hit a bit differently.&n;&t; * We first clear hit markers from them.&n;&t; */
id|clr_hit_marker
c_func
(paren
id|opt-&gt;pattern_expression
)paren
suffix:semicolon
id|grep_buffer_1
c_func
(paren
id|opt
comma
id|name
comma
id|buf
comma
id|size
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chk_hit_marker
c_func
(paren
id|opt-&gt;pattern_expression
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|grep_buffer_1
c_func
(paren
id|opt
comma
id|name
comma
id|buf
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
