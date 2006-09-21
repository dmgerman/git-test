multiline_comment|/*&n; * rev-parse.c&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;builtin.h&quot;
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
DECL|variable|output_sq
r_static
r_int
id|output_sq
suffix:semicolon
DECL|variable|revs_count
r_static
r_int
id|revs_count
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
id|revs_count
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
r_if
c_cond
(paren
id|abbrev
)paren
id|show
c_func
(paren
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
r_void
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
suffix:semicolon
)brace
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
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
comma
l_int|2
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
l_string|&quot;--short&quot;
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--short=&quot;
comma
l_int|8
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
id|die
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--since=&quot;
comma
l_int|8
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--after=&quot;
comma
l_int|8
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--before=&quot;
comma
l_int|9
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
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--until=&quot;
comma
l_int|8
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
id|die
c_func
(paren
l_string|&quot;Needed a single revision&quot;
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
r_if
c_cond
(paren
id|verify
)paren
id|die
c_func
(paren
l_string|&quot;Needed a single revision&quot;
)paren
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
id|show_default
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify
op_logical_and
id|revs_count
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Needed a single revision&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
