macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;tag.h&quot;
DECL|variable|show_ref_usage
r_static
r_const
r_char
id|show_ref_usage
(braket
)braket
op_assign
l_string|&quot;git show-ref [-q|--quiet] [--verify] [-h|--head] [-d|--dereference] [-s|--hash[=&lt;length&gt;]] [--abbrev[=&lt;length&gt;]] [--tags] [--heads] [--] [pattern*]&quot;
suffix:semicolon
DECL|variable|deref_tags
DECL|variable|show_head
DECL|variable|tags_only
DECL|variable|heads_only
r_static
r_int
id|deref_tags
op_assign
l_int|0
comma
id|show_head
op_assign
l_int|0
comma
id|tags_only
op_assign
l_int|0
comma
id|heads_only
op_assign
l_int|0
comma
DECL|variable|found_match
DECL|variable|verify
DECL|variable|quiet
DECL|variable|hash_only
DECL|variable|abbrev
id|found_match
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
id|hash_only
op_assign
l_int|0
comma
id|abbrev
op_assign
l_int|0
suffix:semicolon
DECL|variable|pattern
r_static
r_const
r_char
op_star
op_star
id|pattern
suffix:semicolon
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
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_const
r_char
op_star
id|hex
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
id|strncmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads/&quot;
comma
l_int|11
)paren
suffix:semicolon
id|match
op_or_assign
id|tags_only
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
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
id|obj
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
id|obj
)paren
(brace
r_if
c_cond
(paren
id|quiet
)paren
r_return
l_int|0
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-show-ref: bad ref %s (%s)&quot;
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
)brace
r_if
c_cond
(paren
id|quiet
)paren
r_return
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
id|deref_tags
op_logical_and
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|obj
op_assign
id|deref_tag
c_func
(paren
id|obj
comma
id|refname
comma
l_int|0
)paren
suffix:semicolon
id|hex
op_assign
id|find_unique_abbrev
c_func
(paren
id|obj-&gt;sha1
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
r_int
id|i
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
op_star
id|arg
op_ne
l_char|&squot;-&squot;
)paren
(brace
id|pattern
op_assign
id|argv
op_plus
id|i
suffix:semicolon
r_break
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
l_string|&quot;--&quot;
)paren
)paren
(brace
id|pattern
op_assign
id|argv
op_plus
id|i
op_plus
l_int|1
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
r_break
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
l_string|&quot;-q&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--quiet&quot;
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
l_string|&quot;-h&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--head&quot;
)paren
)paren
(brace
id|show_head
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
l_string|&quot;-d&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--dereference&quot;
)paren
)paren
(brace
id|deref_tags
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
l_string|&quot;-s&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--hash&quot;
)paren
)paren
(brace
id|hash_only
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
id|arg
comma
l_string|&quot;--hash=&quot;
comma
l_int|7
)paren
op_logical_or
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--abbrev&quot;
comma
l_int|8
)paren
op_logical_and
(paren
id|arg
(braket
l_int|8
)braket
op_eq
l_char|&squot;=&squot;
op_logical_or
id|arg
(braket
l_int|8
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|arg
(braket
l_int|3
)braket
op_ne
l_char|&squot;h&squot;
op_logical_and
op_logical_neg
id|arg
(braket
l_int|8
)braket
)paren
multiline_comment|/* --abbrev only */
id|abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
r_else
(brace
multiline_comment|/* --hash= or --abbrev= */
r_char
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|3
)braket
op_eq
l_char|&squot;h&squot;
)paren
(brace
id|hash_only
op_assign
l_int|1
suffix:semicolon
id|arg
op_add_assign
l_int|7
suffix:semicolon
)brace
r_else
id|arg
op_add_assign
l_int|9
suffix:semicolon
id|abbrev
op_assign
id|strtoul
c_func
(paren
id|arg
comma
op_amp
id|end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
op_logical_or
id|abbrev
OG
l_int|40
)paren
id|usage
c_func
(paren
id|show_ref_usage
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
l_string|&quot;--verify&quot;
)paren
)paren
(brace
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
l_string|&quot;--tags&quot;
)paren
)paren
(brace
id|tags_only
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
l_string|&quot;--heads&quot;
)paren
)paren
(brace
id|heads_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|show_ref_usage
)paren
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
