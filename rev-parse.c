multiline_comment|/*&n; * rev-parse.c&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|def
r_static
r_char
op_star
id|def
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|no_revs
r_static
r_int
id|no_revs
op_assign
l_int|0
suffix:semicolon
DECL|variable|single_rev
r_static
r_int
id|single_rev
op_assign
l_int|0
suffix:semicolon
DECL|variable|revs_only
r_static
r_int
id|revs_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|do_rev_argument
r_static
r_int
id|do_rev_argument
op_assign
l_int|1
suffix:semicolon
DECL|variable|output_revs
r_static
r_int
id|output_revs
op_assign
l_int|0
suffix:semicolon
DECL|variable|flags_only
r_static
r_int
id|flags_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|no_flags
r_static
r_int
id|no_flags
op_assign
l_int|0
suffix:semicolon
DECL|variable|output_sq
r_static
r_int
id|output_sq
op_assign
l_int|0
suffix:semicolon
DECL|variable|symbolic
r_static
r_int
id|symbolic
op_assign
l_int|0
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
l_string|&quot;--max-count=&quot;
comma
l_string|&quot;--max-age=&quot;
comma
l_string|&quot;--min-age=&quot;
comma
l_string|&quot;--merge-order&quot;
comma
l_string|&quot;--topo-order&quot;
comma
l_string|&quot;--bisect&quot;
comma
l_string|&quot;--no-merges&quot;
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
r_return
l_int|1
suffix:semicolon
)brace
)brace
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
id|no_revs
)paren
r_return
suffix:semicolon
id|output_revs
op_increment
suffix:semicolon
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
r_if
c_cond
(paren
id|symbolic
op_logical_and
id|name
)paren
id|show
c_func
(paren
id|name
)paren
suffix:semicolon
r_else
id|show
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|show_rev_arg
r_static
r_void
id|show_rev_arg
c_func
(paren
r_char
op_star
id|rev
)paren
(brace
r_if
c_cond
(paren
id|no_revs
)paren
r_return
suffix:semicolon
id|show
c_func
(paren
id|rev
)paren
suffix:semicolon
)brace
DECL|function|show_norev
r_static
r_void
id|show_norev
c_func
(paren
r_char
op_star
id|norev
)paren
(brace
r_if
c_cond
(paren
id|flags_only
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|revs_only
)paren
r_return
suffix:semicolon
id|show
c_func
(paren
id|norev
)paren
suffix:semicolon
)brace
DECL|function|show_arg
r_static
r_void
id|show_arg
c_func
(paren
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|no_flags
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|do_rev_argument
op_logical_and
id|is_rev_argument
c_func
(paren
id|arg
)paren
)paren
id|show_rev_arg
c_func
(paren
id|arg
)paren
suffix:semicolon
r_else
id|show
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|show_default
r_static
r_void
id|show_default
c_func
(paren
r_void
)paren
(brace
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
suffix:semicolon
)brace
id|show_norev
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
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
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
comma
id|as_is
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
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
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
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_char
op_star
id|dotdot
suffix:semicolon
r_if
c_cond
(paren
id|as_is
)paren
(brace
id|show_norev
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
id|show_default
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs_only
op_logical_or
id|flags_only
)paren
r_break
suffix:semicolon
id|as_is
op_assign
l_int|1
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
id|revs_only
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
l_string|&quot;--no-revs&quot;
)paren
)paren
(brace
id|no_revs
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
l_string|&quot;--flags&quot;
)paren
)paren
(brace
id|flags_only
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
l_string|&quot;--no-flags&quot;
)paren
)paren
(brace
id|no_flags
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
l_string|&quot;--verify&quot;
)paren
)paren
(brace
id|revs_only
op_assign
l_int|1
suffix:semicolon
id|do_rev_argument
op_assign
l_int|0
suffix:semicolon
id|single_rev
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
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|for_each_ref
c_func
(paren
id|show_reference
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
id|puts
c_func
(paren
id|prefix
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|show_arg
c_func
(paren
id|arg
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dotdot
op_assign
id|strstr
c_func
(paren
id|arg
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dotdot
)paren
(brace
r_int
r_char
id|end
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|n
op_assign
id|dotdot
op_plus
l_int|2
suffix:semicolon
op_star
id|dotdot
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|n
)paren
id|n
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
id|n
comma
id|end
)paren
)paren
(brace
r_if
c_cond
(paren
id|no_revs
)paren
r_continue
suffix:semicolon
id|def
op_assign
l_int|NULL
suffix:semicolon
id|show_rev
c_func
(paren
id|NORMAL
comma
id|end
comma
id|n
)paren
suffix:semicolon
id|show_rev
c_func
(paren
id|REVERSED
comma
id|sha1
comma
id|arg
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
op_star
id|dotdot
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|no_revs
)paren
r_continue
suffix:semicolon
id|def
op_assign
l_int|NULL
suffix:semicolon
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
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;^&squot;
op_logical_and
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
op_plus
l_int|1
comma
id|sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|no_revs
)paren
r_continue
suffix:semicolon
id|def
op_assign
l_int|NULL
suffix:semicolon
id|show_rev
c_func
(paren
id|REVERSED
comma
id|sha1
comma
id|arg
op_plus
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|show_default
c_func
(paren
)paren
suffix:semicolon
id|show_norev
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
id|show_default
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|single_rev
op_logical_and
id|output_revs
op_ne
l_int|1
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Needed a single revision&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
