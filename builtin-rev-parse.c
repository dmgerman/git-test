multiline_comment|/*&n; * rev-parse.c&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|macro|DO_REVS
mdefine_line|#define DO_REVS&t;&t;1
DECL|macro|DO_NOREV
mdefine_line|#define DO_NOREV&t;2
DECL|macro|DO_FLAGS
mdefine_line|#define DO_FLAGS&t;4
DECL|macro|DO_NONFLAGS
mdefine_line|#define DO_NONFLAGS&t;8
DECL|variable|filter
r_static
r_int
id|filter
op_assign
op_complement
l_int|0
suffix:semicolon
DECL|variable|def
r_static
r_const
r_char
op_star
id|def
suffix:semicolon
DECL|macro|NORMAL
mdefine_line|#define NORMAL 0
DECL|macro|REVERSED
mdefine_line|#define REVERSED 1
DECL|variable|show_type
r_static
r_int
id|show_type
op_assign
id|NORMAL
suffix:semicolon
DECL|macro|SHOW_SYMBOLIC_ASIS
mdefine_line|#define SHOW_SYMBOLIC_ASIS 1
DECL|macro|SHOW_SYMBOLIC_FULL
mdefine_line|#define SHOW_SYMBOLIC_FULL 2
DECL|variable|symbolic
r_static
r_int
id|symbolic
suffix:semicolon
DECL|variable|abbrev
r_static
r_int
id|abbrev
suffix:semicolon
DECL|variable|abbrev_ref
r_static
r_int
id|abbrev_ref
suffix:semicolon
DECL|variable|abbrev_ref_strict
r_static
r_int
id|abbrev_ref_strict
suffix:semicolon
DECL|variable|output_sq
r_static
r_int
id|output_sq
suffix:semicolon
multiline_comment|/*&n; * Some arguments are relevant &quot;revision&quot; arguments,&n; * others are about output format or other details.&n; * This sorts it all out.&n; */
DECL|function|is_rev_argument
r_static
r_int
id|is_rev_argument
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_static
r_const
r_char
op_star
id|rev_args
(braket
)braket
op_assign
(brace
l_string|&quot;--all&quot;
comma
l_string|&quot;--bisect&quot;
comma
l_string|&quot;--dense&quot;
comma
l_string|&quot;--branches&quot;
comma
l_string|&quot;--header&quot;
comma
l_string|&quot;--max-age=&quot;
comma
l_string|&quot;--max-count=&quot;
comma
l_string|&quot;--min-age=&quot;
comma
l_string|&quot;--no-merges&quot;
comma
l_string|&quot;--objects&quot;
comma
l_string|&quot;--objects-edge&quot;
comma
l_string|&quot;--parents&quot;
comma
l_string|&quot;--pretty&quot;
comma
l_string|&quot;--remotes&quot;
comma
l_string|&quot;--sparse&quot;
comma
l_string|&quot;--tags&quot;
comma
l_string|&quot;--topo-order&quot;
comma
l_string|&quot;--date-order&quot;
comma
l_string|&quot;--unpacked&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
op_assign
id|rev_args
suffix:semicolon
multiline_comment|/* accept -&lt;digit&gt;, like traditional &quot;head&quot; */
r_if
c_cond
(paren
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
op_logical_and
id|isdigit
c_func
(paren
id|arg
(braket
l_int|1
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|str
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
id|str
)paren
op_logical_or
(paren
id|str
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;=&squot;
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
id|str
comma
id|len
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Output argument as a string, either SQ or normal */
DECL|function|show
r_static
r_void
id|show
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|output_sq
)paren
(brace
r_int
id|sq
op_assign
l_char|&squot;&bslash;&squot;&squot;
comma
id|ch
suffix:semicolon
id|putchar
c_func
(paren
id|sq
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|arg
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
id|sq
)paren
id|fputs
c_func
(paren
l_string|&quot;&squot;&bslash;&bslash;&squot;&quot;
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
id|ch
)paren
suffix:semicolon
)brace
id|putchar
c_func
(paren
id|sq
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
r_else
id|puts
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/* Like show(), but with a negation prefix according to type */
DECL|function|show_with_type
r_static
r_void
id|show_with_type
c_func
(paren
r_int
id|type
comma
r_const
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|type
op_ne
id|show_type
)paren
id|putchar
c_func
(paren
l_char|&squot;^&squot;
)paren
suffix:semicolon
id|show
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/* Output a revision, only if filter allows it */
DECL|function|show_rev
r_static
r_void
id|show_rev
c_func
(paren
r_int
id|type
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|filter
op_amp
id|DO_REVS
)paren
)paren
r_return
suffix:semicolon
id|def
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|symbolic
op_logical_or
id|abbrev_ref
)paren
op_logical_and
id|name
)paren
(brace
r_if
c_cond
(paren
id|symbolic
op_eq
id|SHOW_SYMBOLIC_FULL
op_logical_or
id|abbrev_ref
)paren
(brace
r_int
r_char
id|discard
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|full
suffix:semicolon
r_switch
c_cond
(paren
id|dwim_ref
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
comma
id|discard
comma
op_amp
id|full
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t;&t;&t; * Not found -- not a ref.  We could&n;&t;&t;&t;&t; * emit &quot;name&quot; here, but symbolic-full&n;&t;&t;&t;&t; * users are interested in finding the&n;&t;&t;&t;&t; * refs spelled in full, and they would&n;&t;&t;&t;&t; * need to filter non-refs if we did so.&n;&t;&t;&t;&t; */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* happy */
r_if
c_cond
(paren
id|abbrev_ref
)paren
id|full
op_assign
id|shorten_unambiguous_ref
c_func
(paren
id|full
comma
id|abbrev_ref_strict
)paren
suffix:semicolon
id|show_with_type
c_func
(paren
id|type
comma
id|full
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* ambiguous */
id|error
c_func
(paren
l_string|&quot;refname &squot;%s&squot; is ambiguous&quot;
comma
id|name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|show_with_type
c_func
(paren
id|type
comma
id|name
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|abbrev
)paren
id|show_with_type
c_func
(paren
id|type
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|abbrev
)paren
)paren
suffix:semicolon
r_else
id|show_with_type
c_func
(paren
id|type
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Output a flag, only if filter allows it. */
DECL|function|show_flag
r_static
r_int
id|show_flag
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|filter
op_amp
id|DO_FLAGS
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filter
op_amp
(paren
id|is_rev_argument
c_func
(paren
id|arg
)paren
ques
c_cond
id|DO_REVS
suffix:colon
id|DO_NOREV
)paren
)paren
(brace
id|show
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_default
r_static
r_int
id|show_default
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|s
op_assign
id|def
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|def
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|s
comma
id|sha1
)paren
)paren
(brace
id|show_rev
c_func
(paren
id|NORMAL
comma
id|sha1
comma
id|s
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_reference
r_static
r_int
id|show_reference
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
id|show_rev
c_func
(paren
id|NORMAL
comma
id|sha1
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|anti_reference
r_static
r_int
id|anti_reference
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
id|show_rev
c_func
(paren
id|REVERSED
comma
id|sha1
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_datestring
r_static
r_void
id|show_datestring
c_func
(paren
r_const
r_char
op_star
id|flag
comma
r_const
r_char
op_star
id|datestr
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|100
)braket
suffix:semicolon
multiline_comment|/* date handling requires both flags and revs */
r_if
c_cond
(paren
(paren
id|filter
op_amp
(paren
id|DO_FLAGS
op_or
id|DO_REVS
)paren
)paren
op_ne
(paren
id|DO_FLAGS
op_or
id|DO_REVS
)paren
)paren
r_return
suffix:semicolon
id|snprintf
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
l_string|&quot;%s%lu&quot;
comma
id|flag
comma
id|approxidate
c_func
(paren
id|datestr
)paren
)paren
suffix:semicolon
id|show
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|show_file
r_static
r_int
id|show_file
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
id|show_default
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|filter
op_amp
(paren
id|DO_NONFLAGS
op_or
id|DO_NOREV
)paren
)paren
op_eq
(paren
id|DO_NONFLAGS
op_or
id|DO_NOREV
)paren
)paren
(brace
id|show
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|try_difference
r_static
r_int
id|try_difference
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_char
op_star
id|dotdot
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|end
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|next
suffix:semicolon
r_const
r_char
op_star
id|this
suffix:semicolon
r_int
id|symmetric
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dotdot
op_assign
id|strstr
c_func
(paren
id|arg
comma
l_string|&quot;..&quot;
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|next
op_assign
id|dotdot
op_plus
l_int|2
suffix:semicolon
id|this
op_assign
id|arg
suffix:semicolon
id|symmetric
op_assign
(paren
op_star
id|next
op_eq
l_char|&squot;.&squot;
)paren
suffix:semicolon
op_star
id|dotdot
op_assign
l_int|0
suffix:semicolon
id|next
op_add_assign
id|symmetric
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|next
)paren
id|next
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
r_if
c_cond
(paren
id|dotdot
op_eq
id|arg
)paren
id|this
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|this
comma
id|sha1
)paren
op_logical_and
op_logical_neg
id|get_sha1
c_func
(paren
id|next
comma
id|end
)paren
)paren
(brace
id|show_rev
c_func
(paren
id|NORMAL
comma
id|end
comma
id|next
)paren
suffix:semicolon
id|show_rev
c_func
(paren
id|symmetric
ques
c_cond
id|NORMAL
suffix:colon
id|REVERSED
comma
id|sha1
comma
id|this
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symmetric
)paren
(brace
r_struct
id|commit_list
op_star
id|exclude
suffix:semicolon
r_struct
id|commit
op_star
id|a
comma
op_star
id|b
suffix:semicolon
id|a
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|b
op_assign
id|lookup_commit_reference
c_func
(paren
id|end
)paren
suffix:semicolon
id|exclude
op_assign
id|get_merge_bases
c_func
(paren
id|a
comma
id|b
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|exclude
)paren
(brace
r_struct
id|commit_list
op_star
id|n
op_assign
id|exclude-&gt;next
suffix:semicolon
id|show_rev
c_func
(paren
id|REVERSED
comma
id|exclude-&gt;item-&gt;object.sha1
comma
l_int|NULL
)paren
suffix:semicolon
id|free
c_func
(paren
id|exclude
)paren
suffix:semicolon
id|exclude
op_assign
id|n
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
op_star
id|dotdot
op_assign
l_char|&squot;.&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|try_parent_shorthands
r_static
r_int
id|try_parent_shorthands
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_char
op_star
id|dotdot
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
id|parents_only
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dotdot
op_assign
id|strstr
c_func
(paren
id|arg
comma
l_string|&quot;^!&quot;
)paren
)paren
)paren
id|parents_only
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|dotdot
op_assign
id|strstr
c_func
(paren
id|arg
comma
l_string|&quot;^@&quot;
)paren
)paren
)paren
id|parents_only
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dotdot
op_logical_or
id|dotdot
(braket
l_int|2
)braket
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|dotdot
op_assign
l_int|0
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
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parents_only
)paren
id|show_rev
c_func
(paren
id|NORMAL
comma
id|sha1
comma
id|arg
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
id|show_rev
c_func
(paren
id|parents_only
ques
c_cond
id|NORMAL
suffix:colon
id|REVERSED
comma
id|parents-&gt;item-&gt;object.sha1
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parseopt_dump
r_static
r_int
id|parseopt_dump
c_func
(paren
r_const
r_struct
id|option
op_star
id|o
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|strbuf
op_star
id|parsed
op_assign
id|o-&gt;value
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
id|strbuf_addf
c_func
(paren
id|parsed
comma
l_string|&quot; --no-%s&quot;
comma
id|o-&gt;long_name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|o-&gt;short_name
)paren
id|strbuf_addf
c_func
(paren
id|parsed
comma
l_string|&quot; -%c&quot;
comma
id|o-&gt;short_name
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|parsed
comma
l_string|&quot; --%s&quot;
comma
id|o-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
id|strbuf_addch
c_func
(paren
id|parsed
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|sq_quote_buf
c_func
(paren
id|parsed
comma
id|arg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|skipspaces
r_static
r_const
r_char
op_star
id|skipspaces
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
id|isspace
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
id|s
suffix:semicolon
)brace
DECL|function|cmd_parseopt
r_static
r_int
id|cmd_parseopt
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
r_const
r_char
op_star
id|prefix
)paren
(brace
r_static
r_int
id|keep_dashdash
op_assign
l_int|0
comma
id|stop_at_non_option
op_assign
l_int|0
suffix:semicolon
r_static
r_char
r_const
op_star
r_const
id|parseopt_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git rev-parse --parseopt [options] -- [&lt;args&gt;...]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_static
r_struct
id|option
id|parseopt_opts
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;keep-dashdash&quot;
comma
op_amp
id|keep_dashdash
comma
l_string|&quot;keep the `--` passed as an arg&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;stop-at-non-option&quot;
comma
op_amp
id|stop_at_non_option
comma
l_string|&quot;stop parsing after the &quot;
l_string|&quot;first non-option argument&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
comma
id|parsed
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
op_star
id|usage
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
op_star
id|opts
op_assign
l_int|NULL
suffix:semicolon
r_int
id|onb
op_assign
l_int|0
comma
id|osz
op_assign
l_int|0
comma
id|unb
op_assign
l_int|0
comma
id|usz
op_assign
l_int|0
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|parsed
comma
l_string|&quot;set --&quot;
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|parseopt_opts
comma
id|parseopt_usage
comma
id|PARSE_OPT_KEEP_DASHDASH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
op_logical_or
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
id|usage_with_options
c_func
(paren
id|parseopt_usage
comma
id|parseopt_opts
)paren
suffix:semicolon
multiline_comment|/* get the usage up to the first line with a -- on it */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_eq
id|EOF
)paren
id|die
c_func
(paren
l_string|&quot;premature end of input&quot;
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|usage
comma
id|unb
op_plus
l_int|1
comma
id|usz
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--&quot;
comma
id|sb.buf
)paren
)paren
(brace
r_if
c_cond
(paren
id|unb
OL
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;no usage string given before the `--&squot; separator&quot;
)paren
suffix:semicolon
id|usage
(braket
id|unb
)braket
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage
(braket
id|unb
op_increment
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|sb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* parse: (&lt;short&gt;|&lt;short&gt;,&lt;long&gt;|&lt;long&gt;)[=?]? SP+ &lt;help&gt; */
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
r_const
r_char
op_star
id|s
suffix:semicolon
r_struct
id|option
op_star
id|o
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb.len
)paren
r_continue
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|opts
comma
id|onb
op_plus
l_int|1
comma
id|osz
)paren
suffix:semicolon
id|memset
c_func
(paren
id|opts
op_plus
id|onb
comma
l_int|0
comma
r_sizeof
(paren
id|opts
(braket
id|onb
)braket
)paren
)paren
suffix:semicolon
id|o
op_assign
op_amp
id|opts
(braket
id|onb
op_increment
)braket
suffix:semicolon
id|s
op_assign
id|strchr
c_func
(paren
id|sb.buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
op_logical_or
op_star
id|sb.buf
op_eq
l_char|&squot; &squot;
)paren
(brace
id|o-&gt;type
op_assign
id|OPTION_GROUP
suffix:semicolon
id|o-&gt;help
op_assign
id|xstrdup
c_func
(paren
id|skipspaces
c_func
(paren
id|sb.buf
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|o-&gt;type
op_assign
id|OPTION_CALLBACK
suffix:semicolon
id|o-&gt;help
op_assign
id|xstrdup
c_func
(paren
id|skipspaces
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
id|o-&gt;value
op_assign
op_amp
id|parsed
suffix:semicolon
id|o-&gt;flags
op_assign
id|PARSE_OPT_NOARG
suffix:semicolon
id|o-&gt;callback
op_assign
op_amp
id|parseopt_dump
suffix:semicolon
r_while
c_loop
(paren
id|s
OG
id|sb.buf
op_logical_and
id|strchr
c_func
(paren
l_string|&quot;*=?!&quot;
comma
id|s
(braket
l_int|1
)braket
)paren
)paren
(brace
r_switch
c_cond
(paren
op_star
op_decrement
id|s
)paren
(brace
r_case
l_char|&squot;=&squot;
suffix:colon
id|o-&gt;flags
op_and_assign
op_complement
id|PARSE_OPT_NOARG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;?&squot;
suffix:colon
id|o-&gt;flags
op_and_assign
op_complement
id|PARSE_OPT_NOARG
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|PARSE_OPT_OPTARG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;!&squot;
suffix:colon
id|o-&gt;flags
op_or_assign
id|PARSE_OPT_NONEG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;*&squot;
suffix:colon
id|o-&gt;flags
op_or_assign
id|PARSE_OPT_HIDDEN
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|s
id|sb.buf
op_eq
l_int|1
)paren
multiline_comment|/* short option only */
id|o-&gt;short_name
op_assign
op_star
id|sb.buf
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sb.buf
(braket
l_int|1
)braket
op_ne
l_char|&squot;,&squot;
)paren
multiline_comment|/* long option only */
id|o-&gt;long_name
op_assign
id|xmemdupz
c_func
(paren
id|sb.buf
comma
id|s
id|sb.buf
)paren
suffix:semicolon
r_else
(brace
id|o-&gt;short_name
op_assign
op_star
id|sb.buf
suffix:semicolon
id|o-&gt;long_name
op_assign
id|xmemdupz
c_func
(paren
id|sb.buf
op_plus
l_int|2
comma
id|s
id|sb.buf
l_int|2
)paren
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
multiline_comment|/* put an OPT_END() */
id|ALLOC_GROW
c_func
(paren
id|opts
comma
id|onb
op_plus
l_int|1
comma
id|osz
)paren
suffix:semicolon
id|memset
c_func
(paren
id|opts
op_plus
id|onb
comma
l_int|0
comma
r_sizeof
(paren
id|opts
(braket
id|onb
)braket
)paren
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|opts
comma
id|usage
comma
id|keep_dashdash
ques
c_cond
id|PARSE_OPT_KEEP_DASHDASH
suffix:colon
l_int|0
op_or
id|stop_at_non_option
ques
c_cond
id|PARSE_OPT_STOP_AT_NON_OPTION
suffix:colon
l_int|0
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|parsed
comma
l_string|&quot; --&quot;
)paren
suffix:semicolon
id|sq_quote_argv
c_func
(paren
op_amp
id|parsed
comma
id|argv
comma
l_int|0
)paren
suffix:semicolon
id|puts
c_func
(paren
id|parsed.buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_sq_quote
r_static
r_int
id|cmd_sq_quote
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
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|argc
)paren
id|sq_quote_argv
c_func
(paren
op_amp
id|buf
comma
id|argv
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|buf.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|die_no_single_rev
r_static
r_void
id|die_no_single_rev
c_func
(paren
r_int
id|quiet
)paren
(brace
r_if
c_cond
(paren
id|quiet
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;Needed a single revision&quot;
)paren
suffix:semicolon
)brace
DECL|function|cmd_rev_parse
r_int
id|cmd_rev_parse
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
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|i
comma
id|as_is
op_assign
l_int|0
comma
id|verify
op_assign
l_int|0
comma
id|quiet
op_assign
l_int|0
comma
id|revs_count
op_assign
l_int|0
comma
id|type
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--parseopt&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
r_return
id|cmd_parseopt
c_func
(paren
id|argc
l_int|1
comma
id|argv
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;--sq-quote&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
r_return
id|cmd_sq_quote
c_func
(paren
id|argc
l_int|2
comma
id|argv
op_plus
l_int|2
)paren
suffix:semicolon
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|as_is
)paren
(brace
r_if
c_cond
(paren
id|show_file
c_func
(paren
id|arg
)paren
op_logical_and
id|as_is
OL
l_int|2
)paren
id|verify_filename
c_func
(paren
id|prefix
comma
id|arg
)paren
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
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_increment
id|i
op_ge
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;-n requires an argument&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|filter
op_amp
id|DO_FLAGS
)paren
op_logical_and
(paren
id|filter
op_amp
id|DO_REVS
)paren
)paren
(brace
id|show
c_func
(paren
id|arg
)paren
suffix:semicolon
id|show
c_func
(paren
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|filter
op_amp
id|DO_FLAGS
)paren
op_logical_and
(paren
id|filter
op_amp
id|DO_REVS
)paren
)paren
id|show
c_func
(paren
id|arg
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|as_is
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Pass on the &quot;--&quot; if we show anything but files.. */
r_if
c_cond
(paren
id|filter
op_amp
(paren
id|DO_FLAGS
op_or
id|DO_REVS
)paren
)paren
id|show_file
c_func
(paren
id|arg
)paren
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
id|arg
comma
l_string|&quot;--default&quot;
)paren
)paren
(brace
id|def
op_assign
id|argv
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|i
op_increment
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
id|arg
comma
l_string|&quot;--revs-only&quot;
)paren
)paren
(brace
id|filter
op_and_assign
op_complement
id|DO_NOREV
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
id|arg
comma
l_string|&quot;--no-revs&quot;
)paren
)paren
(brace
id|filter
op_and_assign
op_complement
id|DO_REVS
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
id|arg
comma
l_string|&quot;--flags&quot;
)paren
)paren
(brace
id|filter
op_and_assign
op_complement
id|DO_NONFLAGS
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
id|arg
comma
l_string|&quot;--no-flags&quot;
)paren
)paren
(brace
id|filter
op_and_assign
op_complement
id|DO_FLAGS
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
id|arg
comma
l_string|&quot;--verify&quot;
)paren
)paren
(brace
id|filter
op_and_assign
op_complement
(paren
id|DO_FLAGS
op_or
id|DO_NOREV
)paren
suffix:semicolon
id|verify
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
id|arg
comma
l_string|&quot;--quiet&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-q&quot;
)paren
)paren
(brace
id|quiet
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
id|arg
comma
l_string|&quot;--short&quot;
)paren
op_logical_or
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--short=&quot;
)paren
)paren
(brace
id|filter
op_and_assign
op_complement
(paren
id|DO_FLAGS
op_or
id|DO_NOREV
)paren
suffix:semicolon
id|verify
op_assign
l_int|1
suffix:semicolon
id|abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|7
)braket
op_eq
l_char|&squot;=&squot;
)paren
id|abbrev
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|8
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|abbrev
OL
id|MINIMUM_ABBREV
)paren
id|abbrev
op_assign
id|MINIMUM_ABBREV
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|40
op_le
id|abbrev
)paren
id|abbrev
op_assign
l_int|40
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
id|arg
comma
l_string|&quot;--sq&quot;
)paren
)paren
(brace
id|output_sq
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
id|arg
comma
l_string|&quot;--not&quot;
)paren
)paren
(brace
id|show_type
op_xor_assign
id|REVERSED
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
id|arg
comma
l_string|&quot;--symbolic&quot;
)paren
)paren
(brace
id|symbolic
op_assign
id|SHOW_SYMBOLIC_ASIS
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
id|arg
comma
l_string|&quot;--symbolic-full-name&quot;
)paren
)paren
(brace
id|symbolic
op_assign
id|SHOW_SYMBOLIC_FULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--abbrev-ref&quot;
)paren
op_logical_and
(paren
op_logical_neg
id|arg
(braket
l_int|12
)braket
op_logical_or
id|arg
(braket
l_int|12
)braket
op_eq
l_char|&squot;=&squot;
)paren
)paren
(brace
id|abbrev_ref
op_assign
l_int|1
suffix:semicolon
id|abbrev_ref_strict
op_assign
id|warn_ambiguous_refs
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|12
)braket
op_eq
l_char|&squot;=&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
op_plus
l_int|13
comma
l_string|&quot;strict&quot;
)paren
)paren
id|abbrev_ref_strict
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
op_plus
l_int|13
comma
l_string|&quot;loose&quot;
)paren
)paren
id|abbrev_ref_strict
op_assign
l_int|0
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;unknown mode for %s&quot;
comma
id|arg
)paren
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
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|for_each_ref
c_func
(paren
id|show_reference
comma
l_int|NULL
)paren
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
id|arg
comma
l_string|&quot;--bisect&quot;
)paren
)paren
(brace
id|for_each_ref_in
c_func
(paren
l_string|&quot;refs/bisect/bad&quot;
comma
id|show_reference
comma
l_int|NULL
)paren
suffix:semicolon
id|for_each_ref_in
c_func
(paren
l_string|&quot;refs/bisect/good&quot;
comma
id|anti_reference
comma
l_int|NULL
)paren
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
id|arg
comma
l_string|&quot;--branches&quot;
)paren
)paren
(brace
id|for_each_branch_ref
c_func
(paren
id|show_reference
comma
l_int|NULL
)paren
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
id|arg
comma
l_string|&quot;--tags&quot;
)paren
)paren
(brace
id|for_each_tag_ref
c_func
(paren
id|show_reference
comma
l_int|NULL
)paren
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
id|arg
comma
l_string|&quot;--remotes&quot;
)paren
)paren
(brace
id|for_each_remote_ref
c_func
(paren
id|show_reference
comma
l_int|NULL
)paren
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
id|arg
comma
l_string|&quot;--show-prefix&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|prefix
)paren
id|puts
c_func
(paren
id|prefix
)paren
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
id|arg
comma
l_string|&quot;--show-cdup&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|pfx
op_assign
id|prefix
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_inside_work_tree
c_func
(paren
)paren
)paren
(brace
r_const
r_char
op_star
id|work_tree
op_assign
id|get_git_work_tree
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|work_tree
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|work_tree
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pfx
)paren
(brace
id|pfx
op_assign
id|strchr
c_func
(paren
id|pfx
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfx
)paren
(brace
id|pfx
op_increment
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;../&quot;
)paren
suffix:semicolon
)brace
)brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
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
id|arg
comma
l_string|&quot;--git-dir&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|gitdir
op_assign
id|getenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
suffix:semicolon
r_static
r_char
id|cwd
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
id|gitdir
)paren
(brace
id|puts
c_func
(paren
id|gitdir
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefix
)paren
(brace
id|puts
c_func
(paren
l_string|&quot;.git&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|getcwd
c_func
(paren
id|cwd
comma
id|PATH_MAX
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to get current working directory&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s/.git&bslash;n&quot;
comma
id|cwd
)paren
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
id|arg
comma
l_string|&quot;--is-inside-git-dir&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|is_inside_git_dir
c_func
(paren
)paren
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
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
id|arg
comma
l_string|&quot;--is-inside-work-tree&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|is_inside_work_tree
c_func
(paren
)paren
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
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
id|arg
comma
l_string|&quot;--is-bare-repository&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|is_bare_repository
c_func
(paren
)paren
ques
c_cond
l_string|&quot;true&quot;
suffix:colon
l_string|&quot;false&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--since=&quot;
)paren
)paren
(brace
id|show_datestring
c_func
(paren
l_string|&quot;--max-age=&quot;
comma
id|arg
op_plus
l_int|8
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--after=&quot;
)paren
)paren
(brace
id|show_datestring
c_func
(paren
l_string|&quot;--max-age=&quot;
comma
id|arg
op_plus
l_int|8
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--before=&quot;
)paren
)paren
(brace
id|show_datestring
c_func
(paren
l_string|&quot;--min-age=&quot;
comma
id|arg
op_plus
l_int|9
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--until=&quot;
)paren
)paren
(brace
id|show_datestring
c_func
(paren
l_string|&quot;--min-age=&quot;
comma
id|arg
op_plus
l_int|8
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_flag
c_func
(paren
id|arg
)paren
op_logical_and
id|verify
)paren
id|die_no_single_rev
c_func
(paren
id|quiet
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Not a flag argument */
r_if
c_cond
(paren
id|try_difference
c_func
(paren
id|arg
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|try_parent_shorthands
c_func
(paren
id|arg
)paren
)paren
r_continue
suffix:semicolon
id|name
op_assign
id|arg
suffix:semicolon
id|type
op_assign
id|NORMAL
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;^&squot;
)paren
(brace
id|name
op_increment
suffix:semicolon
id|type
op_assign
id|REVERSED
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|verify
)paren
id|revs_count
op_increment
suffix:semicolon
r_else
id|show_rev
c_func
(paren
id|type
comma
id|sha1
comma
id|name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verify
)paren
id|die_no_single_rev
c_func
(paren
id|quiet
)paren
suffix:semicolon
id|as_is
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_file
c_func
(paren
id|arg
)paren
)paren
r_continue
suffix:semicolon
id|verify_filename
c_func
(paren
id|prefix
comma
id|arg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verify
)paren
(brace
r_if
c_cond
(paren
id|revs_count
op_eq
l_int|1
)paren
(brace
id|show_rev
c_func
(paren
id|type
comma
id|sha1
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|revs_count
op_eq
l_int|0
op_logical_and
id|show_default
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|die_no_single_rev
c_func
(paren
id|quiet
)paren
suffix:semicolon
)brace
r_else
id|show_default
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
