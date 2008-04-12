macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;mailmap.h&quot;
DECL|variable|shortlog_usage
r_static
r_const
r_char
id|shortlog_usage
(braket
)braket
op_assign
l_string|&quot;git-shortlog [-n] [-s] [-e] [-w] [&lt;commit-id&gt;... ]&quot;
suffix:semicolon
DECL|variable|common_repo_prefix
r_static
r_char
op_star
id|common_repo_prefix
suffix:semicolon
DECL|variable|email
r_static
r_int
id|email
suffix:semicolon
DECL|function|compare_by_number
r_static
r_int
id|compare_by_number
c_func
(paren
r_const
r_void
op_star
id|a1
comma
r_const
r_void
op_star
id|a2
)paren
(brace
r_const
r_struct
id|path_list_item
op_star
id|i1
op_assign
id|a1
comma
op_star
id|i2
op_assign
id|a2
suffix:semicolon
r_const
r_struct
id|path_list
op_star
id|l1
op_assign
id|i1-&gt;util
comma
op_star
id|l2
op_assign
id|i2-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|l1-&gt;nr
OL
id|l2-&gt;nr
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|l1-&gt;nr
op_eq
id|l2-&gt;nr
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|mailmap
r_static
r_struct
id|path_list
id|mailmap
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|insert_one_record
r_static
r_void
id|insert_one_record
c_func
(paren
r_struct
id|path_list
op_star
id|list
comma
r_const
r_char
op_star
id|author
comma
r_const
r_char
op_star
id|oneline
)paren
(brace
r_const
r_char
op_star
id|dot3
op_assign
id|common_repo_prefix
suffix:semicolon
r_char
op_star
id|buffer
comma
op_star
id|p
suffix:semicolon
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
r_struct
id|path_list
op_star
id|onelines
suffix:semicolon
r_char
id|namebuf
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|eol
suffix:semicolon
r_const
r_char
op_star
id|boemail
comma
op_star
id|eoemail
suffix:semicolon
id|boemail
op_assign
id|strchr
c_func
(paren
id|author
comma
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boemail
)paren
r_return
suffix:semicolon
id|eoemail
op_assign
id|strchr
c_func
(paren
id|boemail
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eoemail
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_email
c_func
(paren
op_amp
id|mailmap
comma
id|boemail
op_plus
l_int|1
comma
id|namebuf
comma
r_sizeof
(paren
id|namebuf
)paren
)paren
)paren
(brace
r_while
c_loop
(paren
id|author
OL
id|boemail
op_logical_and
id|isspace
c_func
(paren
op_star
id|author
)paren
)paren
id|author
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|len
op_assign
l_int|0
suffix:semicolon
id|len
OL
r_sizeof
(paren
id|namebuf
)paren
l_int|1
op_logical_and
id|author
op_plus
id|len
OL
id|boemail
suffix:semicolon
id|len
op_increment
)paren
id|namebuf
(braket
id|len
)braket
op_assign
id|author
(braket
id|len
)braket
suffix:semicolon
r_while
c_loop
(paren
l_int|0
OL
id|len
op_logical_and
id|isspace
c_func
(paren
id|namebuf
(braket
id|len
op_minus
l_int|1
)braket
)paren
)paren
id|len
op_decrement
suffix:semicolon
id|namebuf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
id|len
op_assign
id|strlen
c_func
(paren
id|namebuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|email
)paren
(brace
r_int
id|room
op_assign
r_sizeof
(paren
id|namebuf
)paren
id|len
l_int|1
suffix:semicolon
r_int
id|maillen
op_assign
id|eoemail
id|boemail
op_plus
l_int|1
suffix:semicolon
id|snprintf
c_func
(paren
id|namebuf
op_plus
id|len
comma
id|room
comma
l_string|&quot; %.*s&quot;
comma
id|maillen
comma
id|boemail
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|xstrdup
c_func
(paren
id|namebuf
)paren
suffix:semicolon
id|item
op_assign
id|path_list_insert
c_func
(paren
id|buffer
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;util
op_eq
l_int|NULL
)paren
id|item-&gt;util
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|path_list
)paren
)paren
suffix:semicolon
r_else
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Skip any leading whitespace, including any blank lines. */
r_while
c_loop
(paren
op_star
id|oneline
op_logical_and
id|isspace
c_func
(paren
op_star
id|oneline
)paren
)paren
id|oneline
op_increment
suffix:semicolon
id|eol
op_assign
id|strchr
c_func
(paren
id|oneline
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eol
)paren
id|eol
op_assign
id|oneline
op_plus
id|strlen
c_func
(paren
id|oneline
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|oneline
comma
l_string|&quot;[PATCH&quot;
)paren
)paren
(brace
r_char
op_star
id|eob
op_assign
id|strchr
c_func
(paren
id|oneline
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eob
op_logical_and
(paren
op_logical_neg
id|eol
op_logical_or
id|eob
OL
id|eol
)paren
)paren
id|oneline
op_assign
id|eob
op_plus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|oneline
op_logical_and
id|isspace
c_func
(paren
op_star
id|oneline
)paren
op_logical_and
op_star
id|oneline
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|oneline
op_increment
suffix:semicolon
id|len
op_assign
id|eol
id|oneline
suffix:semicolon
r_while
c_loop
(paren
id|len
op_logical_and
id|isspace
c_func
(paren
id|oneline
(braket
id|len
op_minus
l_int|1
)braket
)paren
)paren
id|len
op_decrement
suffix:semicolon
id|buffer
op_assign
id|xmemdupz
c_func
(paren
id|oneline
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dot3
)paren
(brace
r_int
id|dot3len
op_assign
id|strlen
c_func
(paren
id|dot3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dot3len
OG
l_int|5
)paren
(brace
r_while
c_loop
(paren
(paren
id|p
op_assign
id|strstr
c_func
(paren
id|buffer
comma
id|dot3
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|taillen
op_assign
id|strlen
c_func
(paren
id|p
)paren
id|dot3len
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
l_string|&quot;/.../&quot;
comma
l_int|5
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|p
op_plus
l_int|5
comma
id|p
op_plus
id|dot3len
comma
id|taillen
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
id|onelines
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|onelines-&gt;nr
op_ge
id|onelines-&gt;alloc
)paren
(brace
id|onelines-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|onelines-&gt;nr
)paren
suffix:semicolon
id|onelines-&gt;items
op_assign
id|xrealloc
c_func
(paren
id|onelines-&gt;items
comma
id|onelines-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|path_list_item
)paren
)paren
suffix:semicolon
)brace
id|onelines-&gt;items
(braket
id|onelines-&gt;nr
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
id|onelines-&gt;items
(braket
id|onelines-&gt;nr
op_increment
)braket
dot
id|path
op_assign
id|buffer
suffix:semicolon
)brace
DECL|function|read_from_stdin
r_static
r_void
id|read_from_stdin
c_func
(paren
r_struct
id|path_list
op_star
id|list
)paren
(brace
r_char
id|author
(braket
l_int|1024
)braket
comma
id|oneline
(braket
l_int|1024
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|author
comma
r_sizeof
(paren
id|author
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|author
(braket
l_int|0
)braket
op_eq
l_char|&squot;A&squot;
op_logical_or
id|author
(braket
l_int|0
)braket
op_eq
l_char|&squot;a&squot;
)paren
op_logical_or
id|prefixcmp
c_func
(paren
id|author
op_plus
l_int|1
comma
l_string|&quot;uthor: &quot;
)paren
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|oneline
comma
r_sizeof
(paren
id|oneline
)paren
comma
id|stdin
)paren
op_logical_and
id|oneline
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
multiline_comment|/* discard headers */
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|oneline
comma
r_sizeof
(paren
id|oneline
)paren
comma
id|stdin
)paren
op_logical_and
id|oneline
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
multiline_comment|/* discard blanks */
id|insert_one_record
c_func
(paren
id|list
comma
id|author
op_plus
l_int|8
comma
id|oneline
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_from_rev
r_static
r_void
id|get_from_rev
c_func
(paren
r_struct
id|rev_info
op_star
id|rev
comma
r_struct
id|path_list
op_star
id|list
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
id|rev
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_const
r_char
op_star
id|author
op_assign
l_int|NULL
comma
op_star
id|buffer
suffix:semicolon
id|buffer
op_assign
id|commit-&gt;buffer
suffix:semicolon
r_while
c_loop
(paren
op_star
id|buffer
op_logical_and
op_star
id|buffer
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_const
r_char
op_star
id|eol
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eol
op_eq
l_int|NULL
)paren
id|eol
op_assign
id|buffer
op_plus
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_else
id|eol
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buffer
comma
l_string|&quot;author &quot;
)paren
)paren
id|author
op_assign
id|buffer
op_plus
l_int|7
suffix:semicolon
id|buffer
op_assign
id|eol
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|author
)paren
id|die
c_func
(paren
l_string|&quot;Missing author: %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buffer
)paren
id|buffer
op_increment
suffix:semicolon
id|insert_one_record
c_func
(paren
id|list
comma
id|author
comma
op_logical_neg
op_star
id|buffer
ques
c_cond
l_string|&quot;&lt;none&gt;&quot;
suffix:colon
id|buffer
)paren
suffix:semicolon
)brace
)brace
DECL|function|parse_uint
r_static
r_int
id|parse_uint
c_func
(paren
r_char
r_const
op_star
op_star
id|arg
comma
r_int
id|comma
)paren
(brace
r_int
r_int
id|ul
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_char
op_star
id|endp
suffix:semicolon
id|ul
op_assign
id|strtoul
c_func
(paren
op_star
id|arg
comma
op_amp
id|endp
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endp
op_ne
op_star
id|arg
op_logical_and
op_star
id|endp
op_logical_and
op_star
id|endp
op_ne
id|comma
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
(paren
r_int
)paren
id|ul
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|ul
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|arg
op_assign
id|endp
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|arg
)paren
(paren
op_star
id|arg
)paren
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|wrap_arg_usage
r_static
r_const
r_char
id|wrap_arg_usage
(braket
)braket
op_assign
l_string|&quot;-w[&lt;width&gt;[,&lt;indent1&gt;[,&lt;indent2&gt;]]]&quot;
suffix:semicolon
DECL|macro|DEFAULT_WRAPLEN
mdefine_line|#define DEFAULT_WRAPLEN 76
DECL|macro|DEFAULT_INDENT1
mdefine_line|#define DEFAULT_INDENT1 6
DECL|macro|DEFAULT_INDENT2
mdefine_line|#define DEFAULT_INDENT2 9
DECL|function|parse_wrap_args
r_static
r_void
id|parse_wrap_args
c_func
(paren
r_const
r_char
op_star
id|arg
comma
r_int
op_star
id|in1
comma
r_int
op_star
id|in2
comma
r_int
op_star
id|wrap
)paren
(brace
id|arg
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* skip -w */
op_star
id|wrap
op_assign
id|parse_uint
c_func
(paren
op_amp
id|arg
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|wrap
OL
l_int|0
)paren
id|die
c_func
(paren
id|wrap_arg_usage
)paren
suffix:semicolon
op_star
id|in1
op_assign
id|parse_uint
c_func
(paren
op_amp
id|arg
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|in1
OL
l_int|0
)paren
id|die
c_func
(paren
id|wrap_arg_usage
)paren
suffix:semicolon
op_star
id|in2
op_assign
id|parse_uint
c_func
(paren
op_amp
id|arg
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|in2
OL
l_int|0
)paren
id|die
c_func
(paren
id|wrap_arg_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|wrap
)paren
op_star
id|wrap
op_assign
id|DEFAULT_WRAPLEN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|in1
)paren
op_star
id|in1
op_assign
id|DEFAULT_INDENT1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|in2
)paren
op_star
id|in2
op_assign
id|DEFAULT_INDENT2
suffix:semicolon
r_if
c_cond
(paren
op_star
id|wrap
op_logical_and
(paren
(paren
op_star
id|in1
op_logical_and
op_star
id|wrap
op_le
op_star
id|in1
)paren
op_logical_or
(paren
op_star
id|in2
op_logical_and
op_star
id|wrap
op_le
op_star
id|in2
)paren
)paren
)paren
id|die
c_func
(paren
id|wrap_arg_usage
)paren
suffix:semicolon
)brace
DECL|function|cmd_shortlog
r_int
id|cmd_shortlog
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
r_struct
id|rev_info
id|rev
suffix:semicolon
r_struct
id|path_list
id|list
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|sort_by_number
op_assign
l_int|0
comma
id|summary
op_assign
l_int|0
suffix:semicolon
r_int
id|wrap_lines
op_assign
l_int|0
suffix:semicolon
r_int
id|wrap
op_assign
id|DEFAULT_WRAPLEN
suffix:semicolon
r_int
id|in1
op_assign
id|DEFAULT_INDENT1
suffix:semicolon
r_int
id|in2
op_assign
id|DEFAULT_INDENT2
suffix:semicolon
multiline_comment|/* since -n is a shadowed rev argument, parse our args first */
r_while
c_loop
(paren
id|argc
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-n&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--numbered&quot;
)paren
)paren
id|sort_by_number
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
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-s&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--summary&quot;
)paren
)paren
id|summary
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
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-e&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--email&quot;
)paren
)paren
id|email
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-w&quot;
)paren
)paren
(brace
id|wrap_lines
op_assign
l_int|1
suffix:semicolon
id|parse_wrap_args
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
op_amp
id|in1
comma
op_amp
id|in2
comma
op_amp
id|wrap
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--help&quot;
)paren
)paren
id|usage
c_func
(paren
id|shortlog_usage
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
id|prefix
)paren
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|die
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|read_mailmap
c_func
(paren
op_amp
id|mailmap
comma
l_string|&quot;.mailmap&quot;
comma
op_amp
id|common_repo_prefix
)paren
suffix:semicolon
multiline_comment|/* assume HEAD if from a tty */
r_if
c_cond
(paren
op_logical_neg
id|rev.pending.nr
op_logical_and
id|isatty
c_func
(paren
l_int|0
)paren
)paren
id|add_head_to_pending
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev.pending.nr
op_eq
l_int|0
)paren
(brace
id|read_from_stdin
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
)brace
r_else
id|get_from_rev
c_func
(paren
op_amp
id|rev
comma
op_amp
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sort_by_number
)paren
id|qsort
c_func
(paren
id|list.items
comma
id|list.nr
comma
r_sizeof
(paren
r_struct
id|path_list_item
)paren
comma
id|compare_by_number
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
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list
op_star
id|onelines
op_assign
id|list.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_if
c_cond
(paren
id|summary
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%6d&bslash;t%s&bslash;n&quot;
comma
id|onelines-&gt;nr
comma
id|list.items
(braket
id|i
)braket
dot
id|path
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%s (%d):&bslash;n&quot;
comma
id|list.items
(braket
id|i
)braket
dot
id|path
comma
id|onelines-&gt;nr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|onelines-&gt;nr
l_int|1
suffix:semicolon
id|j
op_ge
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
r_const
r_char
op_star
id|msg
op_assign
id|onelines-&gt;items
(braket
id|j
)braket
dot
id|path
suffix:semicolon
r_if
c_cond
(paren
id|wrap_lines
)paren
(brace
r_int
id|col
op_assign
id|print_wrapped_text
c_func
(paren
id|msg
comma
id|in1
comma
id|in2
comma
id|wrap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|col
op_ne
id|wrap
)paren
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;      %s&bslash;n&quot;
comma
id|msg
)paren
suffix:semicolon
)brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
id|onelines-&gt;strdup_paths
op_assign
l_int|1
suffix:semicolon
id|path_list_clear
c_func
(paren
id|onelines
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|onelines
)paren
suffix:semicolon
id|list.items
(braket
id|i
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
)brace
id|list.strdup_paths
op_assign
l_int|1
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|list
comma
l_int|1
)paren
suffix:semicolon
id|mailmap.strdup_paths
op_assign
l_int|1
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|mailmap
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
