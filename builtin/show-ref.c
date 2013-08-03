macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|show_ref_usage
r_static
r_const
r_char
op_star
r_const
id|show_ref_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git show-ref [-q|--quiet] [--verify] [--head] [-d|--dereference] [-s|--hash[=&lt;n&gt;]] [--abbrev[=&lt;n&gt;]] [--tags] [--heads] [--] [pattern*] &quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git show-ref --exclude-existing[=pattern] &lt; ref-list&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|deref_tags
DECL|variable|show_head
DECL|variable|tags_only
DECL|variable|heads_only
DECL|variable|found_match
DECL|variable|verify
r_static
r_int
id|deref_tags
comma
id|show_head
comma
id|tags_only
comma
id|heads_only
comma
id|found_match
comma
id|verify
comma
DECL|variable|quiet
DECL|variable|hash_only
DECL|variable|abbrev
DECL|variable|exclude_arg
id|quiet
comma
id|hash_only
comma
id|abbrev
comma
id|exclude_arg
suffix:semicolon
DECL|variable|pattern
r_static
r_const
r_char
op_star
op_star
id|pattern
suffix:semicolon
DECL|variable|exclude_existing_arg
r_static
r_const
r_char
op_star
id|exclude_existing_arg
suffix:semicolon
DECL|function|show_one
r_static
r_void
id|show_one
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
r_const
r_char
op_star
id|hex
op_assign
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|abbrev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hash_only
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|hex
comma
id|refname
)paren
suffix:semicolon
)brace
DECL|function|show_ref
r_static
r_int
id|show_ref
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
id|cbdata
)paren
(brace
r_const
r_char
op_star
id|hex
suffix:semicolon
r_int
r_char
id|peeled
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|show_head
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|refname
comma
l_string|&quot;HEAD&quot;
)paren
)paren
r_goto
id|match
suffix:semicolon
r_if
c_cond
(paren
id|tags_only
op_logical_or
id|heads_only
)paren
(brace
r_int
id|match
suffix:semicolon
id|match
op_assign
id|heads_only
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
id|match
op_or_assign
id|tags_only
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/tags/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|match
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pattern
)paren
(brace
r_int
id|reflen
op_assign
id|strlen
c_func
(paren
id|refname
)paren
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
op_assign
id|pattern
comma
op_star
id|m
suffix:semicolon
r_while
c_loop
(paren
(paren
id|m
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|reflen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|m
comma
id|refname
op_plus
id|reflen
id|len
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|reflen
)paren
r_goto
id|match
suffix:semicolon
multiline_comment|/* &quot;--verify&quot; requires an exact match */
r_if
c_cond
(paren
id|verify
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|refname
(braket
id|reflen
id|len
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_goto
id|match
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|match
suffix:colon
id|found_match
op_increment
suffix:semicolon
multiline_comment|/* This changes the semantics slightly that even under quiet we&n;&t; * detect and return error if the repository is corrupt and&n;&t; * ref points at a nonexistent object.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git show-ref: bad ref %s (%s)&quot;
comma
id|refname
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|quiet
)paren
r_return
l_int|0
suffix:semicolon
id|show_one
c_func
(paren
id|refname
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|deref_tags
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|peel_ref
c_func
(paren
id|refname
comma
id|peeled
)paren
)paren
(brace
id|hex
op_assign
id|find_unique_abbrev
c_func
(paren
id|peeled
comma
id|abbrev
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s^{}&bslash;n&quot;
comma
id|hex
comma
id|refname
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_existing
r_static
r_int
id|add_existing
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
id|cbdata
)paren
(brace
r_struct
id|string_list
op_star
id|list
op_assign
(paren
r_struct
id|string_list
op_star
)paren
id|cbdata
suffix:semicolon
id|string_list_insert
c_func
(paren
id|list
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * read &quot;^(?:&lt;anything&gt;&bslash;s)?&lt;refname&gt;(?:&bslash;^&bslash;{&bslash;})?$&quot; from the standard input,&n; * and&n; * (1) strip &quot;^{}&quot; at the end of line if any;&n; * (2) ignore if match is provided and does not head-match refname;&n; * (3) warn if refname is not a well-formed refname and skip;&n; * (4) ignore if refname is a ref that exists in the local repository;&n; * (5) otherwise output the line.&n; */
DECL|function|exclude_existing
r_static
r_int
id|exclude_existing
c_func
(paren
r_const
r_char
op_star
id|match
)paren
(brace
r_static
r_struct
id|string_list
id|existing_refs
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|matchlen
op_assign
id|match
ques
c_cond
id|strlen
c_func
(paren
id|match
)paren
suffix:colon
l_int|0
suffix:semicolon
id|for_each_ref
c_func
(paren
id|add_existing
comma
op_amp
id|existing_refs
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
id|stdin
)paren
)paren
(brace
r_char
op_star
id|ref
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
op_logical_and
id|buf
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
l_int|3
op_le
id|len
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|buf
op_plus
id|len
l_int|3
comma
l_string|&quot;^{}&quot;
)paren
)paren
(brace
id|len
op_sub_assign
l_int|3
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_for
c_loop
(paren
id|ref
op_assign
id|buf
op_plus
id|len
suffix:semicolon
id|buf
OL
id|ref
suffix:semicolon
id|ref
op_decrement
)paren
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|ref
(braket
l_int|1
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|match
)paren
(brace
r_int
id|reflen
op_assign
id|buf
op_plus
id|len
id|ref
suffix:semicolon
r_if
c_cond
(paren
id|reflen
OL
id|matchlen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ref
comma
id|match
comma
id|matchlen
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_refname_format
c_func
(paren
id|ref
comma
l_int|0
)paren
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;ref &squot;%s&squot; ignored&quot;
comma
id|ref
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|string_list_has_string
c_func
(paren
op_amp
id|existing_refs
comma
id|ref
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hash_callback
r_static
r_int
id|hash_callback
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
id|hash_only
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Use full length SHA1 if no argument */
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|parse_opt_abbrev_cb
c_func
(paren
id|opt
comma
id|arg
comma
id|unset
)paren
suffix:semicolon
)brace
DECL|function|exclude_existing_callback
r_static
r_int
id|exclude_existing_callback
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
id|exclude_arg
op_assign
l_int|1
suffix:semicolon
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|opt-&gt;value
op_assign
id|arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|help_callback
r_static
r_int
id|help_callback
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
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|show_ref_options
r_static
r_const
r_struct
id|option
id|show_ref_options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;tags&quot;
comma
op_amp
id|tags_only
comma
id|N_
c_func
(paren
l_string|&quot;only show tags (can be combined with heads)&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;heads&quot;
comma
op_amp
id|heads_only
comma
id|N_
c_func
(paren
l_string|&quot;only show heads (can be combined with tags)&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;verify&quot;
comma
op_amp
id|verify
comma
id|N_
c_func
(paren
l_string|&quot;stricter reference checking, &quot;
l_string|&quot;requires exact ref path&quot;
)paren
)paren
comma
id|OPT_HIDDEN_BOOL
c_func
(paren
l_char|&squot;h&squot;
comma
l_int|NULL
comma
op_amp
id|show_head
comma
id|N_
c_func
(paren
l_string|&quot;show the HEAD reference, even if it would be filtered out&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;head&quot;
comma
op_amp
id|show_head
comma
id|N_
c_func
(paren
l_string|&quot;show the HEAD reference, even if it would be filtered out&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;d&squot;
comma
l_string|&quot;dereference&quot;
comma
op_amp
id|deref_tags
comma
id|N_
c_func
(paren
l_string|&quot;dereference tags into object IDs&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_char|&squot;s&squot;
comma
l_string|&quot;hash&quot;
comma
op_amp
id|abbrev
comma
id|N_
c_func
(paren
l_string|&quot;n&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;only show SHA1 hash using &lt;n&gt; digits&quot;
)paren
comma
id|PARSE_OPT_OPTARG
comma
op_amp
id|hash_callback
)brace
comma
id|OPT__ABBREV
c_func
(paren
op_amp
id|abbrev
)paren
comma
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
id|N_
c_func
(paren
l_string|&quot;do not print results to stdout (useful with --verify)&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;exclude-existing&quot;
comma
op_amp
id|exclude_existing_arg
comma
id|N_
c_func
(paren
l_string|&quot;pattern&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;show refs from stdin that aren&squot;t in local repository&quot;
)paren
comma
id|PARSE_OPT_OPTARG
op_or
id|PARSE_OPT_NONEG
comma
id|exclude_existing_callback
)brace
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;help-all&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|N_
c_func
(paren
l_string|&quot;show usage&quot;
)paren
comma
id|PARSE_OPT_HIDDEN
op_or
id|PARSE_OPT_NOARG
comma
id|help_callback
)brace
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
DECL|function|cmd_show_ref
r_int
id|cmd_show_ref
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
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
op_logical_and
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
)paren
id|usage_with_options
c_func
(paren
id|show_ref_usage
comma
id|show_ref_options
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
id|show_ref_options
comma
id|show_ref_usage
comma
id|PARSE_OPT_NO_INTERNAL_HELP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exclude_arg
)paren
r_return
id|exclude_existing
c_func
(paren
id|exclude_existing_arg
)paren
suffix:semicolon
id|pattern
op_assign
id|argv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|pattern
)paren
id|pattern
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|verify
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pattern
)paren
id|die
c_func
(paren
l_string|&quot;--verify requires a reference&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pattern
)paren
(brace
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
op_logical_neg
id|prefixcmp
c_func
(paren
op_star
id|pattern
comma
l_string|&quot;refs/&quot;
)paren
op_logical_and
op_logical_neg
id|read_ref
c_func
(paren
op_star
id|pattern
comma
id|sha1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|show_one
c_func
(paren
op_star
id|pattern
comma
id|sha1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; - not a valid ref&quot;
comma
op_star
id|pattern
)paren
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
id|pattern
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_head
)paren
id|head_ref
c_func
(paren
id|show_ref
comma
l_int|NULL
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|show_ref
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found_match
)paren
(brace
r_if
c_cond
(paren
id|verify
op_logical_and
op_logical_neg
id|quiet
)paren
id|die
c_func
(paren
l_string|&quot;No match&quot;
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
eof
