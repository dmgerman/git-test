macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;mailmap.h&quot;
macro_line|#include &quot;shortlog.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|shortlog_usage
r_static
r_char
r_const
op_star
r_const
id|shortlog_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git shortlog [-n] [-s] [-e] [-w] [rev-opts] [--] [&lt;commit-id&gt;... ]&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;[rev-opts] are documented in git-rev-list(1)&quot;
comma
l_int|NULL
)brace
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
id|string_list_item
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
id|string_list
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
r_const
r_char
op_star
id|format_subject
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|msg
comma
r_const
r_char
op_star
id|line_separator
)paren
suffix:semicolon
DECL|function|insert_one_record
r_static
r_void
id|insert_one_record
c_func
(paren
r_struct
id|shortlog
op_star
id|log
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
id|log-&gt;common_repo_prefix
suffix:semicolon
r_char
op_star
id|buffer
comma
op_star
id|p
suffix:semicolon
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_char
id|namebuf
(braket
l_int|1024
)braket
suffix:semicolon
r_char
id|emailbuf
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
r_struct
id|strbuf
id|subject
op_assign
id|STRBUF_INIT
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
multiline_comment|/* copy author name to namebuf, to support matching on both name and email */
id|memcpy
c_func
(paren
id|namebuf
comma
id|author
comma
id|boemail
id|author
)paren
suffix:semicolon
id|len
op_assign
id|boemail
id|author
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
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
l_int|0
suffix:semicolon
multiline_comment|/* copy email name to emailbuf, to allow email replacement as well */
id|memcpy
c_func
(paren
id|emailbuf
comma
id|boemail
op_plus
l_int|1
comma
id|eoemail
id|boemail
)paren
suffix:semicolon
id|emailbuf
(braket
id|eoemail
id|boemail
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map_user
c_func
(paren
op_amp
id|log-&gt;mailmap
comma
id|emailbuf
comma
r_sizeof
(paren
id|emailbuf
)paren
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
id|log-&gt;email
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
id|strlen
c_func
(paren
id|emailbuf
)paren
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
l_string|&quot; &lt;%.*s&gt;&quot;
comma
id|maillen
comma
id|emailbuf
)paren
suffix:semicolon
)brace
id|item
op_assign
id|string_list_insert
c_func
(paren
op_amp
id|log-&gt;list
comma
id|namebuf
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
id|string_list
)paren
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
id|format_subject
c_func
(paren
op_amp
id|subject
comma
id|oneline
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|subject
comma
l_int|NULL
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
id|string_list_append
c_func
(paren
id|item-&gt;util
comma
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|read_from_stdin
r_static
r_void
id|read_from_stdin
c_func
(paren
r_struct
id|shortlog
op_star
id|log
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
id|log
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
DECL|function|shortlog_add_commit
r_void
id|shortlog_add_commit
c_func
(paren
r_struct
id|shortlog
op_star
id|log
comma
r_struct
id|commit
op_star
id|commit
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
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|ufbuf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|pp_commit_easy
c_func
(paren
id|CMIT_FMT_RAW
comma
id|commit
comma
op_amp
id|buf
)paren
suffix:semicolon
id|buffer
op_assign
id|buf.buf
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
id|log-&gt;user_format
)paren
(brace
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|ctx.fmt
op_assign
id|CMIT_FMT_USERFORMAT
suffix:semicolon
id|ctx.abbrev
op_assign
id|log-&gt;abbrev
suffix:semicolon
id|ctx.subject
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|ctx.after_subject
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|ctx.date_mode
op_assign
id|DATE_NORMAL
suffix:semicolon
id|pretty_print_commit
c_func
(paren
op_amp
id|ctx
comma
id|commit
comma
op_amp
id|ufbuf
)paren
suffix:semicolon
id|buffer
op_assign
id|ufbuf.buf
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|buffer
)paren
(brace
id|buffer
op_increment
suffix:semicolon
)brace
id|insert_one_record
c_func
(paren
id|log
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
id|strbuf_release
c_func
(paren
op_amp
id|ufbuf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
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
id|shortlog
op_star
id|log
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
id|rev
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
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
id|shortlog_add_commit
c_func
(paren
id|log
comma
id|commit
)paren
suffix:semicolon
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
comma
r_int
id|defval
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
r_if
c_cond
(paren
id|ul
OG
id|INT_MAX
)paren
r_return
l_int|1
suffix:semicolon
id|ret
op_assign
op_star
id|arg
op_eq
id|endp
ques
c_cond
id|defval
suffix:colon
(paren
r_int
)paren
id|ul
suffix:semicolon
op_star
id|arg
op_assign
op_star
id|endp
ques
c_cond
id|endp
op_plus
l_int|1
suffix:colon
id|endp
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
r_int
id|parse_wrap_args
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
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
id|shortlog
op_star
id|log
op_assign
id|opt-&gt;value
suffix:semicolon
id|log-&gt;wrap_lines
op_assign
op_logical_neg
id|unset
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|log-&gt;wrap
op_assign
id|DEFAULT_WRAPLEN
suffix:semicolon
id|log-&gt;in1
op_assign
id|DEFAULT_INDENT1
suffix:semicolon
id|log-&gt;in2
op_assign
id|DEFAULT_INDENT2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|log-&gt;wrap
op_assign
id|parse_uint
c_func
(paren
op_amp
id|arg
comma
l_char|&squot;,&squot;
comma
id|DEFAULT_WRAPLEN
)paren
suffix:semicolon
id|log-&gt;in1
op_assign
id|parse_uint
c_func
(paren
op_amp
id|arg
comma
l_char|&squot;,&squot;
comma
id|DEFAULT_INDENT1
)paren
suffix:semicolon
id|log-&gt;in2
op_assign
id|parse_uint
c_func
(paren
op_amp
id|arg
comma
l_char|&squot;&bslash;0&squot;
comma
id|DEFAULT_INDENT2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log-&gt;wrap
OL
l_int|0
op_logical_or
id|log-&gt;in1
OL
l_int|0
op_logical_or
id|log-&gt;in2
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
id|wrap_arg_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log-&gt;wrap
op_logical_and
(paren
(paren
id|log-&gt;in1
op_logical_and
id|log-&gt;wrap
op_le
id|log-&gt;in1
)paren
op_logical_or
(paren
id|log-&gt;in2
op_logical_and
id|log-&gt;wrap
op_le
id|log-&gt;in2
)paren
)paren
)paren
r_return
id|error
c_func
(paren
id|wrap_arg_usage
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shortlog_init
r_void
id|shortlog_init
c_func
(paren
r_struct
id|shortlog
op_star
id|log
)paren
(brace
id|memset
c_func
(paren
id|log
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|log
)paren
)paren
suffix:semicolon
id|read_mailmap
c_func
(paren
op_amp
id|log-&gt;mailmap
comma
op_amp
id|log-&gt;common_repo_prefix
)paren
suffix:semicolon
id|log-&gt;list.strdup_strings
op_assign
l_int|1
suffix:semicolon
id|log-&gt;wrap
op_assign
id|DEFAULT_WRAPLEN
suffix:semicolon
id|log-&gt;in1
op_assign
id|DEFAULT_INDENT1
suffix:semicolon
id|log-&gt;in2
op_assign
id|DEFAULT_INDENT2
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
r_static
r_struct
id|shortlog
id|log
suffix:semicolon
r_static
r_struct
id|rev_info
id|rev
suffix:semicolon
r_int
id|nongit
op_assign
op_logical_neg
id|startup_info-&gt;have_repository
suffix:semicolon
r_static
r_const
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;n&squot;
comma
l_string|&quot;numbered&quot;
comma
op_amp
id|log.sort_by_number
comma
l_string|&quot;sort output according to the number of commits per author&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;s&squot;
comma
l_string|&quot;summary&quot;
comma
op_amp
id|log.summary
comma
l_string|&quot;Suppress commit descriptions, only provides commit count&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;e&squot;
comma
l_string|&quot;email&quot;
comma
op_amp
id|log.email
comma
l_string|&quot;Show the email address of each author&quot;
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_char|&squot;w&squot;
comma
l_int|NULL
comma
op_amp
id|log
comma
l_string|&quot;w[,i1[,i2]]&quot;
comma
l_string|&quot;Linewrap output&quot;
comma
id|PARSE_OPT_OPTARG
comma
op_amp
id|parse_wrap_args
)brace
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_struct
id|parse_opt_ctx_t
id|ctx
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|shortlog_init
c_func
(paren
op_amp
id|log
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
id|prefix
)paren
suffix:semicolon
id|parse_options_start
c_func
(paren
op_amp
id|ctx
comma
id|argc
comma
id|argv
comma
id|prefix
comma
id|options
comma
id|PARSE_OPT_KEEP_DASHDASH
op_or
id|PARSE_OPT_KEEP_ARGV0
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
id|parse_options_step
c_func
(paren
op_amp
id|ctx
comma
id|options
comma
id|shortlog_usage
)paren
)paren
(brace
r_case
id|PARSE_OPT_HELP
suffix:colon
m_exit
(paren
l_int|129
)paren
suffix:semicolon
r_case
id|PARSE_OPT_DONE
suffix:colon
r_goto
id|parse_done
suffix:semicolon
)brace
id|parse_revision_opt
c_func
(paren
op_amp
id|rev
comma
op_amp
id|ctx
comma
id|options
comma
id|shortlog_usage
)paren
suffix:semicolon
)brace
id|parse_done
suffix:colon
id|argc
op_assign
id|parse_options_end
c_func
(paren
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
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
op_ne
l_int|1
)paren
(brace
id|error
c_func
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|shortlog_usage
comma
id|options
)paren
suffix:semicolon
)brace
id|log.user_format
op_assign
id|rev.commit_format
op_eq
id|CMIT_FMT_USERFORMAT
suffix:semicolon
id|log.abbrev
op_assign
id|rev.abbrev
suffix:semicolon
multiline_comment|/* assume HEAD if from a tty */
r_if
c_cond
(paren
op_logical_neg
id|nongit
op_logical_and
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
r_if
c_cond
(paren
id|isatty
c_func
(paren
l_int|0
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;(reading log message from standard input)&bslash;n&quot;
)paren
suffix:semicolon
id|read_from_stdin
c_func
(paren
op_amp
id|log
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
id|log
)paren
suffix:semicolon
id|shortlog_output
c_func
(paren
op_amp
id|log
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_wrapped_shortlog_msg
r_static
r_void
id|add_wrapped_shortlog_msg
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|s
comma
r_const
r_struct
id|shortlog
op_star
id|log
)paren
(brace
r_int
id|col
op_assign
id|strbuf_add_wrapped_text
c_func
(paren
id|sb
comma
id|s
comma
id|log-&gt;in1
comma
id|log-&gt;in2
comma
id|log-&gt;wrap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|col
op_ne
id|log-&gt;wrap
)paren
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|shortlog_output
r_void
id|shortlog_output
c_func
(paren
r_struct
id|shortlog
op_star
id|log
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|log-&gt;sort_by_number
)paren
id|qsort
c_func
(paren
id|log-&gt;list.items
comma
id|log-&gt;list.nr
comma
r_sizeof
(paren
r_struct
id|string_list_item
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
id|log-&gt;list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|string_list
op_star
id|onelines
op_assign
id|log-&gt;list.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_if
c_cond
(paren
id|log-&gt;summary
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%6d&bslash;t%s&bslash;n&quot;
comma
id|onelines-&gt;nr
comma
id|log-&gt;list.items
(braket
id|i
)braket
dot
id|string
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
id|log-&gt;list.items
(braket
id|i
)braket
dot
id|string
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
id|string
suffix:semicolon
r_if
c_cond
(paren
id|log-&gt;wrap_lines
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|add_wrapped_shortlog_msg
c_func
(paren
op_amp
id|sb
comma
id|msg
comma
id|log
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|sb.buf
comma
id|sb.len
comma
l_int|1
comma
id|stdout
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
id|onelines-&gt;strdup_strings
op_assign
l_int|1
suffix:semicolon
id|string_list_clear
c_func
(paren
id|onelines
comma
l_int|0
)paren
suffix:semicolon
id|free
c_func
(paren
id|onelines
)paren
suffix:semicolon
id|log-&gt;list.items
(braket
id|i
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|log-&gt;list.strdup_strings
op_assign
l_int|1
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|log-&gt;list
comma
l_int|1
)paren
suffix:semicolon
id|clear_mailmap
c_func
(paren
op_amp
id|log-&gt;mailmap
)paren
suffix:semicolon
)brace
eof
