macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;graph.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;reflog-walk.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;color.h&quot;
DECL|variable|name_decoration
r_struct
id|decoration
id|name_decoration
op_assign
(brace
l_string|&quot;object names&quot;
)brace
suffix:semicolon
DECL|enum|decoration_type
r_enum
id|decoration_type
(brace
DECL|enumerator|DECORATION_NONE
id|DECORATION_NONE
op_assign
l_int|0
comma
DECL|enumerator|DECORATION_REF_LOCAL
id|DECORATION_REF_LOCAL
comma
DECL|enumerator|DECORATION_REF_REMOTE
id|DECORATION_REF_REMOTE
comma
DECL|enumerator|DECORATION_REF_TAG
id|DECORATION_REF_TAG
comma
DECL|enumerator|DECORATION_REF_STASH
id|DECORATION_REF_STASH
comma
DECL|enumerator|DECORATION_REF_HEAD
id|DECORATION_REF_HEAD
comma
)brace
suffix:semicolon
DECL|variable|decoration_colors
r_static
r_char
id|decoration_colors
(braket
)braket
(braket
id|COLOR_MAXLEN
)braket
op_assign
(brace
id|GIT_COLOR_RESET
comma
id|GIT_COLOR_BOLD_GREEN
comma
multiline_comment|/* REF_LOCAL */
id|GIT_COLOR_BOLD_RED
comma
multiline_comment|/* REF_REMOTE */
id|GIT_COLOR_BOLD_YELLOW
comma
multiline_comment|/* REF_TAG */
id|GIT_COLOR_BOLD_MAGENTA
comma
multiline_comment|/* REF_STASH */
id|GIT_COLOR_BOLD_CYAN
comma
multiline_comment|/* REF_HEAD */
)brace
suffix:semicolon
DECL|function|decorate_get_color
r_static
r_const
r_char
op_star
id|decorate_get_color
c_func
(paren
r_int
id|decorate_use_color
comma
r_enum
id|decoration_type
id|ix
)paren
(brace
r_if
c_cond
(paren
id|decorate_use_color
)paren
r_return
id|decoration_colors
(braket
id|ix
)braket
suffix:semicolon
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
DECL|function|parse_decorate_color_slot
r_static
r_int
id|parse_decorate_color_slot
c_func
(paren
r_const
r_char
op_star
id|slot
)paren
(brace
multiline_comment|/*&n;&t; * We&squot;re comparing with &squot;ignore-case&squot; on&n;&t; * (because config.c sets them all tolower),&n;&t; * but let&squot;s match the letters in the literal&n;&t; * string values here with how they are&n;&t; * documented in Documentation/config.txt, for&n;&t; * consistency.&n;&t; *&n;&t; * We love being consistent, don&squot;t we?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|slot
comma
l_string|&quot;branch&quot;
)paren
)paren
r_return
id|DECORATION_REF_LOCAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|slot
comma
l_string|&quot;remoteBranch&quot;
)paren
)paren
r_return
id|DECORATION_REF_REMOTE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|slot
comma
l_string|&quot;tag&quot;
)paren
)paren
r_return
id|DECORATION_REF_TAG
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|slot
comma
l_string|&quot;stash&quot;
)paren
)paren
r_return
id|DECORATION_REF_STASH
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|slot
comma
l_string|&quot;HEAD&quot;
)paren
)paren
r_return
id|DECORATION_REF_HEAD
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parse_decorate_color_config
r_int
id|parse_decorate_color_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_int
id|ofs
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_int
id|slot
op_assign
id|parse_decorate_color_slot
c_func
(paren
id|var
op_plus
id|ofs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|color_parse
c_func
(paren
id|value
comma
id|var
comma
id|decoration_colors
(braket
id|slot
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * log-tree.c uses DIFF_OPT_TST for determining whether to use color&n; * for showing the commit sha1, use the same check for --decorate&n; */
DECL|macro|decorate_get_color_opt
mdefine_line|#define decorate_get_color_opt(o, ix) &bslash;&n;&t;decorate_get_color(DIFF_OPT_TST((o), COLOR_DIFF), ix)
DECL|function|add_name_decoration
r_static
r_void
id|add_name_decoration
c_func
(paren
r_enum
id|decoration_type
id|type
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|object
op_star
id|obj
)paren
(brace
r_int
id|nlen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_struct
id|name_decoration
op_star
id|res
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|name_decoration
)paren
op_plus
id|nlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|res-&gt;name
comma
id|name
comma
id|nlen
op_plus
l_int|1
)paren
suffix:semicolon
id|res-&gt;type
op_assign
id|type
suffix:semicolon
id|res-&gt;next
op_assign
id|add_decoration
c_func
(paren
op_amp
id|name_decoration
comma
id|obj
comma
id|res
)paren
suffix:semicolon
)brace
DECL|function|add_ref_decoration
r_static
r_int
id|add_ref_decoration
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
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_enum
id|decoration_type
id|type
op_assign
id|DECORATION_NONE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads&quot;
)paren
)paren
id|type
op_assign
id|DECORATION_REF_LOCAL
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/remotes&quot;
)paren
)paren
id|type
op_assign
id|DECORATION_REF_REMOTE
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/tags&quot;
)paren
)paren
id|type
op_assign
id|DECORATION_REF_TAG
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/stash&quot;
)paren
)paren
id|type
op_assign
id|DECORATION_REF_STASH
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;HEAD&quot;
)paren
)paren
id|type
op_assign
id|DECORATION_REF_HEAD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cb_data
op_logical_or
op_star
(paren
r_int
op_star
)paren
id|cb_data
op_eq
id|DECORATE_SHORT_REFS
)paren
id|refname
op_assign
id|prettify_refname
c_func
(paren
id|refname
)paren
suffix:semicolon
id|add_name_decoration
c_func
(paren
id|type
comma
id|refname
comma
id|obj
)paren
suffix:semicolon
r_while
c_loop
(paren
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|obj
op_assign
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
)paren
op_member_access_from_pointer
id|tagged
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_break
suffix:semicolon
id|add_name_decoration
c_func
(paren
id|DECORATION_REF_TAG
comma
id|refname
comma
id|obj
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|load_ref_decorations
r_void
id|load_ref_decorations
c_func
(paren
r_int
id|flags
)paren
(brace
r_static
r_int
id|loaded
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|loaded
)paren
(brace
id|loaded
op_assign
l_int|1
suffix:semicolon
id|for_each_ref
c_func
(paren
id|add_ref_decoration
comma
op_amp
id|flags
)paren
suffix:semicolon
id|head_ref
c_func
(paren
id|add_ref_decoration
comma
op_amp
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_parents
r_static
r_void
id|show_parents
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
id|abbrev
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|p-&gt;item
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|find_unique_abbrev
c_func
(paren
id|parent-&gt;object.sha1
comma
id|abbrev
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_decorations
r_void
id|show_decorations
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
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
id|prefix
suffix:semicolon
r_struct
id|name_decoration
op_star
id|decoration
suffix:semicolon
r_const
r_char
op_star
id|color_commit
op_assign
id|diff_get_color_opt
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|DIFF_COMMIT
)paren
suffix:semicolon
r_const
r_char
op_star
id|color_reset
op_assign
id|decorate_get_color_opt
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|DECORATION_NONE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;show_source
op_logical_and
id|commit-&gt;util
)paren
id|printf
c_func
(paren
l_string|&quot;&bslash;t%s&quot;
comma
(paren
r_char
op_star
)paren
id|commit-&gt;util
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;show_decorations
)paren
r_return
suffix:semicolon
id|decoration
op_assign
id|lookup_decoration
c_func
(paren
op_amp
id|name_decoration
comma
op_amp
id|commit-&gt;object
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|decoration
)paren
r_return
suffix:semicolon
id|prefix
op_assign
l_string|&quot; (&quot;
suffix:semicolon
r_while
c_loop
(paren
id|decoration
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|prefix
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|decorate_get_color_opt
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|decoration-&gt;type
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|decoration-&gt;type
op_eq
id|DECORATION_REF_TAG
)paren
id|fputs
c_func
(paren
l_string|&quot;tag: &quot;
comma
id|stdout
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|decoration-&gt;name
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|color_reset
comma
id|stdout
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|color_commit
comma
id|stdout
)paren
suffix:semicolon
id|prefix
op_assign
l_string|&quot;, &quot;
suffix:semicolon
id|decoration
op_assign
id|decoration-&gt;next
suffix:semicolon
)brace
id|putchar
c_func
(paren
l_char|&squot;)&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Search for &quot;^[-A-Za-z]+: [^@]+@&quot; pattern. It usually matches&n; * Signed-off-by: and Acked-by: lines.&n; */
DECL|function|detect_any_signoff
r_static
r_int
id|detect_any_signoff
c_func
(paren
r_char
op_star
id|letter
comma
r_int
id|size
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
r_int
id|seen_colon
op_assign
l_int|0
suffix:semicolon
r_int
id|seen_at
op_assign
l_int|0
suffix:semicolon
r_int
id|seen_name
op_assign
l_int|0
suffix:semicolon
r_int
id|seen_head
op_assign
l_int|0
suffix:semicolon
id|cp
op_assign
id|letter
op_plus
id|size
suffix:semicolon
r_while
c_loop
(paren
id|letter
op_le
op_decrement
id|cp
op_logical_and
op_star
id|cp
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|letter
op_le
id|cp
)paren
(brace
r_char
id|ch
op_assign
op_star
id|cp
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|seen_at
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;@&squot;
)paren
id|seen_at
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
id|seen_colon
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;@&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;:&squot;
)paren
id|seen_colon
op_assign
l_int|1
suffix:semicolon
r_else
id|seen_name
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
l_char|&squot;A&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;Z&squot;
)paren
op_logical_or
(paren
l_char|&squot;a&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
id|ch
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|seen_head
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* no empty last line doesn&squot;t match */
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|seen_head
op_logical_and
id|seen_name
suffix:semicolon
)brace
DECL|function|append_signoff
r_static
r_void
id|append_signoff
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
id|signoff
)paren
(brace
r_static
r_const
r_char
id|signed_off_by
(braket
)braket
op_assign
l_string|&quot;Signed-off-by: &quot;
suffix:semicolon
r_int
id|signoff_len
op_assign
id|strlen
c_func
(paren
id|signoff
)paren
suffix:semicolon
r_int
id|has_signoff
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
id|cp
op_assign
id|sb-&gt;buf
suffix:semicolon
multiline_comment|/* First see if we already have the sign-off by the signer */
r_while
c_loop
(paren
(paren
id|cp
op_assign
id|strstr
c_func
(paren
id|cp
comma
id|signed_off_by
)paren
)paren
)paren
(brace
id|has_signoff
op_assign
l_int|1
suffix:semicolon
id|cp
op_add_assign
id|strlen
c_func
(paren
id|signed_off_by
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_plus
id|signoff_len
op_ge
id|sb-&gt;buf
op_plus
id|sb-&gt;len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
id|signoff
comma
id|signoff_len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|cp
(braket
id|signoff_len
)braket
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* we already have him */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|has_signoff
)paren
id|has_signoff
op_assign
id|detect_any_signoff
c_func
(paren
id|sb-&gt;buf
comma
id|sb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_signoff
)paren
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|signed_off_by
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|signoff
comma
id|signoff_len
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|sb
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|digits_in_number
r_static
r_int
r_int
id|digits_in_number
c_func
(paren
r_int
r_int
id|number
)paren
(brace
r_int
r_int
id|i
op_assign
l_int|10
comma
id|result
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|i
op_le
id|number
)paren
(brace
id|i
op_mul_assign
l_int|10
suffix:semicolon
id|result
op_increment
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|get_patch_filename
r_void
id|get_patch_filename
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
id|nr
comma
r_const
r_char
op_star
id|suffix
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
r_int
id|suffix_len
op_assign
id|strlen
c_func
(paren
id|suffix
)paren
op_plus
l_int|1
suffix:semicolon
r_int
id|start_len
op_assign
id|buf-&gt;len
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|buf
comma
id|commit
ques
c_cond
l_string|&quot;%04d-&quot;
suffix:colon
l_string|&quot;%d&quot;
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit
)paren
(brace
r_int
id|max_len
op_assign
id|start_len
op_plus
id|FORMAT_PATCH_NAME_MAX
id|suffix_len
suffix:semicolon
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|ctx.date_mode
op_assign
id|DATE_NORMAL
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
l_string|&quot;%f&quot;
comma
id|buf
comma
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_len
OL
id|buf-&gt;len
)paren
id|strbuf_setlen
c_func
(paren
id|buf
comma
id|max_len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|buf
comma
id|suffix
)paren
suffix:semicolon
)brace
)brace
DECL|function|log_write_email_headers
r_void
id|log_write_email_headers
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
comma
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
op_star
id|subject_p
comma
r_const
r_char
op_star
op_star
id|extra_headers_p
comma
r_int
op_star
id|need_8bit_cte_p
)paren
(brace
r_const
r_char
op_star
id|subject
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|extra_headers
op_assign
id|opt-&gt;extra_headers
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
op_star
id|need_8bit_cte_p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* unknown */
r_if
c_cond
(paren
id|opt-&gt;total
OG
l_int|0
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|64
)braket
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
l_string|&quot;Subject: [%s %0*d/%d] &quot;
comma
id|opt-&gt;subject_prefix
comma
id|digits_in_number
c_func
(paren
id|opt-&gt;total
)paren
comma
id|opt-&gt;nr
comma
id|opt-&gt;total
)paren
suffix:semicolon
id|subject
op_assign
id|buffer
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|opt-&gt;total
op_eq
l_int|0
op_logical_and
id|opt-&gt;subject_prefix
op_logical_and
op_star
id|opt-&gt;subject_prefix
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|256
)braket
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
l_string|&quot;Subject: [%s] &quot;
comma
id|opt-&gt;subject_prefix
)paren
suffix:semicolon
id|subject
op_assign
id|buffer
suffix:semicolon
)brace
r_else
(brace
id|subject
op_assign
l_string|&quot;Subject: &quot;
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;From %s Mon Sep 17 00:00:00 2001&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|graph_show_oneline
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;message_id
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Message-Id: &lt;%s&gt;&bslash;n&quot;
comma
id|opt-&gt;message_id
)paren
suffix:semicolon
id|graph_show_oneline
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;ref_message_ids
op_logical_and
id|opt-&gt;ref_message_ids-&gt;nr
OG
l_int|0
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
id|n
op_assign
id|opt-&gt;ref_message_ids-&gt;nr
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;In-Reply-To: &lt;%s&gt;&bslash;n&quot;
comma
id|opt-&gt;ref_message_ids-&gt;items
(braket
id|n
op_minus
l_int|1
)braket
dot
id|string
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
id|n
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s&lt;%s&gt;&bslash;n&quot;
comma
(paren
id|i
OG
l_int|0
ques
c_cond
l_string|&quot;&bslash;t&quot;
suffix:colon
l_string|&quot;References: &quot;
)paren
comma
id|opt-&gt;ref_message_ids-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
id|graph_show_oneline
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;mime_boundary
)paren
(brace
r_static
r_char
id|subject_buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_static
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|strbuf
id|filename
op_assign
id|STRBUF_INIT
suffix:semicolon
op_star
id|need_8bit_cte_p
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* NEVER */
id|snprintf
c_func
(paren
id|subject_buffer
comma
r_sizeof
(paren
id|subject_buffer
)paren
l_int|1
comma
l_string|&quot;%s&quot;
l_string|&quot;MIME-Version: 1.0&bslash;n&quot;
l_string|&quot;Content-Type: multipart/mixed;&quot;
l_string|&quot; boundary=&bslash;&quot;%s%s&bslash;&quot;&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;This is a multi-part message in MIME &quot;
l_string|&quot;format.&bslash;n&quot;
l_string|&quot;--%s%s&bslash;n&quot;
l_string|&quot;Content-Type: text/plain; &quot;
l_string|&quot;charset=UTF-8; format=fixed&bslash;n&quot;
l_string|&quot;Content-Transfer-Encoding: 8bit&bslash;n&bslash;n&quot;
comma
id|extra_headers
ques
c_cond
id|extra_headers
suffix:colon
l_string|&quot;&quot;
comma
id|mime_boundary_leader
comma
id|opt-&gt;mime_boundary
comma
id|mime_boundary_leader
comma
id|opt-&gt;mime_boundary
)paren
suffix:semicolon
id|extra_headers
op_assign
id|subject_buffer
suffix:semicolon
id|get_patch_filename
c_func
(paren
id|opt-&gt;numbered_files
ques
c_cond
l_int|NULL
suffix:colon
id|commit
comma
id|opt-&gt;nr
comma
id|opt-&gt;patch_suffix
comma
op_amp
id|filename
)paren
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
l_int|1
comma
l_string|&quot;&bslash;n--%s%s&bslash;n&quot;
l_string|&quot;Content-Type: text/x-patch;&quot;
l_string|&quot; name=&bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
l_string|&quot;Content-Transfer-Encoding: 8bit&bslash;n&quot;
l_string|&quot;Content-Disposition: %s;&quot;
l_string|&quot; filename=&bslash;&quot;%s&bslash;&quot;&bslash;n&bslash;n&quot;
comma
id|mime_boundary_leader
comma
id|opt-&gt;mime_boundary
comma
id|filename.buf
comma
id|opt-&gt;no_inline
ques
c_cond
l_string|&quot;attachment&quot;
suffix:colon
l_string|&quot;inline&quot;
comma
id|filename.buf
)paren
suffix:semicolon
id|opt-&gt;diffopt.stat_sep
op_assign
id|buffer
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|filename
)paren
suffix:semicolon
)brace
op_star
id|subject_p
op_assign
id|subject
suffix:semicolon
op_star
id|extra_headers_p
op_assign
id|extra_headers
suffix:semicolon
)brace
DECL|function|show_log
r_void
id|show_log
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
)paren
(brace
r_struct
id|strbuf
id|msgbuf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|log_info
op_star
id|log
op_assign
id|opt-&gt;loginfo
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|log-&gt;commit
comma
op_star
id|parent
op_assign
id|log-&gt;parent
suffix:semicolon
r_int
id|abbrev_commit
op_assign
id|opt-&gt;abbrev_commit
ques
c_cond
id|opt-&gt;abbrev
suffix:colon
l_int|40
suffix:semicolon
r_const
r_char
op_star
id|extra_headers
op_assign
id|opt-&gt;extra_headers
suffix:semicolon
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|opt-&gt;loginfo
op_assign
l_int|NULL
suffix:semicolon
id|ctx.show_notes
op_assign
id|opt-&gt;show_notes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;verbose_header
)paren
(brace
id|graph_show_commit
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;graph
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|BOUNDARY
)paren
id|putchar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
id|putchar
c_func
(paren
l_char|&squot;^&squot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt-&gt;left_right
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|SYMMETRIC_LEFT
)paren
id|putchar
c_func
(paren
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
)brace
id|fputs
c_func
(paren
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|abbrev_commit
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;print_parents
)paren
id|show_parents
c_func
(paren
id|commit
comma
id|abbrev_commit
)paren
suffix:semicolon
id|show_decorations
c_func
(paren
id|opt
comma
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;graph
op_logical_and
op_logical_neg
id|graph_is_commit_finished
c_func
(paren
id|opt-&gt;graph
)paren
)paren
(brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|graph_show_remainder
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
)brace
id|putchar
c_func
(paren
id|opt-&gt;diffopt.line_termination
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If use_terminator is set, we already handled any record termination&n;&t; * at the end of the last record.&n;&t; * Otherwise, add a diffopt.line_termination character before all&n;&t; * entries but the first.  (IOW, as a separator between entries)&n;&t; */
r_if
c_cond
(paren
id|opt-&gt;shown_one
op_logical_and
op_logical_neg
id|opt-&gt;use_terminator
)paren
(brace
multiline_comment|/*&n;&t;&t; * If entries are separated by a newline, the output&n;&t;&t; * should look human-readable.  If the last entry ended&n;&t;&t; * with a newline, print the graph output before this&n;&t;&t; * newline.  Otherwise it will end up as a completely blank&n;&t;&t; * line and will look like a gap in the graph.&n;&t;&t; *&n;&t;&t; * If the entry separator is not a newline, the output is&n;&t;&t; * primarily intended for programmatic consumption, and we&n;&t;&t; * never want the extra graph output before the entry&n;&t;&t; * separator.&n;&t;&t; */
r_if
c_cond
(paren
id|opt-&gt;diffopt.line_termination
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|opt-&gt;missing_newline
)paren
id|graph_show_padding
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
id|putchar
c_func
(paren
id|opt-&gt;diffopt.line_termination
)paren
suffix:semicolon
)brace
id|opt-&gt;shown_one
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * If the history graph was requested,&n;&t; * print the graph, up to this commit&squot;s line&n;&t; */
id|graph_show_commit
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Print header line of header..&n;&t; */
r_if
c_cond
(paren
id|opt-&gt;commit_format
op_eq
id|CMIT_FMT_EMAIL
)paren
(brace
id|log_write_email_headers
c_func
(paren
id|opt
comma
id|commit
comma
op_amp
id|ctx.subject
comma
op_amp
id|extra_headers
comma
op_amp
id|ctx.need_8bit_cte
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|opt-&gt;commit_format
op_ne
id|CMIT_FMT_USERFORMAT
)paren
(brace
id|fputs
c_func
(paren
id|diff_get_color_opt
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|DIFF_COMMIT
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;commit_format
op_ne
id|CMIT_FMT_ONELINE
)paren
id|fputs
c_func
(paren
l_string|&quot;commit &quot;
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;graph
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|BOUNDARY
)paren
id|putchar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
id|putchar
c_func
(paren
l_char|&squot;^&squot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt-&gt;left_right
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|SYMMETRIC_LEFT
)paren
id|putchar
c_func
(paren
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
)brace
id|fputs
c_func
(paren
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|abbrev_commit
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;print_parents
)paren
id|show_parents
c_func
(paren
id|commit
comma
id|abbrev_commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|printf
c_func
(paren
l_string|&quot; (from %s)&quot;
comma
id|find_unique_abbrev
c_func
(paren
id|parent-&gt;object.sha1
comma
id|abbrev_commit
)paren
)paren
suffix:semicolon
id|show_decorations
c_func
(paren
id|opt
comma
id|commit
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|diff_get_color_opt
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|DIFF_RESET
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
(brace
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|graph_show_oneline
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;reflog_info
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * setup_revisions() ensures that opt-&gt;reflog_info&n;&t;&t;&t; * and opt-&gt;graph cannot both be set,&n;&t;&t;&t; * so we don&squot;t need to worry about printing the&n;&t;&t;&t; * graph info here.&n;&t;&t;&t; */
id|show_reflog_message
c_func
(paren
id|opt-&gt;reflog_info
comma
id|opt-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
comma
id|opt-&gt;date_mode_explicit
ques
c_cond
id|opt-&gt;date_mode
suffix:colon
id|DATE_NORMAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;buffer
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * And then the pretty-printed message itself&n;&t; */
r_if
c_cond
(paren
id|ctx.need_8bit_cte
op_ge
l_int|0
)paren
id|ctx.need_8bit_cte
op_assign
id|has_non_ascii
c_func
(paren
id|opt-&gt;add_signoff
)paren
suffix:semicolon
id|ctx.date_mode
op_assign
id|opt-&gt;date_mode
suffix:semicolon
id|ctx.abbrev
op_assign
id|opt-&gt;diffopt.abbrev
suffix:semicolon
id|ctx.after_subject
op_assign
id|extra_headers
suffix:semicolon
id|ctx.reflog_info
op_assign
id|opt-&gt;reflog_info
suffix:semicolon
id|pretty_print_commit
c_func
(paren
id|opt-&gt;commit_format
comma
id|commit
comma
op_amp
id|msgbuf
comma
op_amp
id|ctx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;add_signoff
)paren
id|append_signoff
c_func
(paren
op_amp
id|msgbuf
comma
id|opt-&gt;add_signoff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;show_log_size
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;log size %i&bslash;n&quot;
comma
(paren
r_int
)paren
id|msgbuf.len
)paren
suffix:semicolon
id|graph_show_oneline
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set opt-&gt;missing_newline if msgbuf doesn&squot;t&n;&t; * end in a newline (including if it is empty)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|msgbuf.len
op_logical_or
id|msgbuf.buf
(braket
id|msgbuf.len
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|opt-&gt;missing_newline
op_assign
l_int|1
suffix:semicolon
r_else
id|opt-&gt;missing_newline
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;graph
)paren
id|graph_show_commit_msg
c_func
(paren
id|opt-&gt;graph
comma
op_amp
id|msgbuf
)paren
suffix:semicolon
r_else
id|fwrite
c_func
(paren
id|msgbuf.buf
comma
r_sizeof
(paren
r_char
)paren
comma
id|msgbuf.len
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;use_terminator
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;missing_newline
)paren
id|graph_show_padding
c_func
(paren
id|opt-&gt;graph
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|msgbuf
)paren
suffix:semicolon
)brace
DECL|function|log_tree_diff_flush
r_int
id|log_tree_diff_flush
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
)paren
(brace
id|diffcore_std
c_func
(paren
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff_queue_is_empty
c_func
(paren
)paren
)paren
(brace
r_int
id|saved_fmt
op_assign
id|opt-&gt;diffopt.output_format
suffix:semicolon
id|opt-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|opt-&gt;diffopt.output_format
op_assign
id|saved_fmt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;loginfo
op_logical_and
op_logical_neg
id|opt-&gt;no_commit_id
)paren
(brace
multiline_comment|/* When showing a verbose header (i.e. log message),&n;&t;&t; * and not in --pretty=oneline format, we would want&n;&t;&t; * an extra newline between the end of log and the&n;&t;&t; * output for readability.&n;&t;&t; */
id|show_log
c_func
(paren
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|opt-&gt;diffopt.output_format
op_amp
op_complement
id|DIFF_FORMAT_NO_OUTPUT
)paren
op_logical_and
id|opt-&gt;verbose_header
op_logical_and
id|opt-&gt;commit_format
op_ne
id|CMIT_FMT_ONELINE
)paren
(brace
r_int
id|pch
op_assign
id|DIFF_FORMAT_DIFFSTAT
op_or
id|DIFF_FORMAT_PATCH
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pch
op_amp
id|opt-&gt;diffopt.output_format
)paren
op_eq
id|pch
)paren
id|printf
c_func
(paren
l_string|&quot;---&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;diffopt.output_prefix
)paren
(brace
r_struct
id|strbuf
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
id|msg
op_assign
id|opt-&gt;diffopt
dot
id|output_prefix
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|opt-&gt;diffopt.output_prefix_data
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|msg-&gt;buf
comma
id|msg-&gt;len
comma
l_int|1
comma
id|stdout
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
)brace
id|diff_flush
c_func
(paren
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|do_diff_combined
r_static
r_int
id|do_diff_combined
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
comma
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_int
r_const
r_char
op_star
id|sha1
op_assign
id|commit-&gt;object.sha1
suffix:semicolon
id|diff_tree_combined_merge
c_func
(paren
id|sha1
comma
id|opt-&gt;dense_combined_merges
comma
id|opt
)paren
suffix:semicolon
r_return
op_logical_neg
id|opt-&gt;loginfo
suffix:semicolon
)brace
multiline_comment|/*&n; * Show the diff of a commit.&n; *&n; * Return true if we printed any log info messages&n; */
DECL|function|log_tree_diff
r_static
r_int
id|log_tree_diff
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
comma
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|log_info
op_star
id|log
)paren
(brace
r_int
id|showed_log
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
r_const
r_char
op_star
id|sha1
op_assign
id|commit-&gt;object.sha1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;diff
op_logical_and
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|opt-&gt;diffopt
comma
id|EXIT_WITH_STATUS
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Root commit? */
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parents
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;show_root_diff
)paren
(brace
id|diff_root_tree_sha1
c_func
(paren
id|sha1
comma
l_string|&quot;&quot;
comma
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
id|opt
)paren
suffix:semicolon
)brace
r_return
op_logical_neg
id|opt-&gt;loginfo
suffix:semicolon
)brace
multiline_comment|/* More than one parent? */
r_if
c_cond
(paren
id|parents
op_logical_and
id|parents-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|opt-&gt;ignore_merges
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt-&gt;combine_merges
)paren
r_return
id|do_diff_combined
c_func
(paren
id|opt
comma
id|commit
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opt-&gt;first_parent_only
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Generate merge log entry only for the first&n;&t;&t;&t; * parent, showing summary diff of the others&n;&t;&t;&t; * we merged _in_.&n;&t;&t;&t; */
id|diff_tree_sha1
c_func
(paren
id|parents-&gt;item-&gt;object.sha1
comma
id|sha1
comma
l_string|&quot;&quot;
comma
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
id|opt
)paren
suffix:semicolon
r_return
op_logical_neg
id|opt-&gt;loginfo
suffix:semicolon
)brace
multiline_comment|/* If we show individual diffs, show the parent info */
id|log-&gt;parent
op_assign
id|parents-&gt;item
suffix:semicolon
)brace
id|showed_log
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|parent-&gt;object.sha1
comma
id|sha1
comma
l_string|&quot;&quot;
comma
op_amp
id|opt-&gt;diffopt
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
id|opt
)paren
suffix:semicolon
id|showed_log
op_or_assign
op_logical_neg
id|opt-&gt;loginfo
suffix:semicolon
multiline_comment|/* Set up the log info for the next parent, if any.. */
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parents
)paren
r_break
suffix:semicolon
id|log-&gt;parent
op_assign
id|parents-&gt;item
suffix:semicolon
id|opt-&gt;loginfo
op_assign
id|log
suffix:semicolon
)brace
r_return
id|showed_log
suffix:semicolon
)brace
DECL|function|log_tree_commit
r_int
id|log_tree_commit
c_func
(paren
r_struct
id|rev_info
op_star
id|opt
comma
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|log_info
id|log
suffix:semicolon
r_int
id|shown
suffix:semicolon
id|log.commit
op_assign
id|commit
suffix:semicolon
id|log.parent
op_assign
l_int|NULL
suffix:semicolon
id|opt-&gt;loginfo
op_assign
op_amp
id|log
suffix:semicolon
id|shown
op_assign
id|log_tree_diff
c_func
(paren
id|opt
comma
id|commit
comma
op_amp
id|log
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shown
op_logical_and
id|opt-&gt;loginfo
op_logical_and
id|opt-&gt;always_show_header
)paren
(brace
id|log.parent
op_assign
l_int|NULL
suffix:semicolon
id|show_log
c_func
(paren
id|opt
)paren
suffix:semicolon
id|shown
op_assign
l_int|1
suffix:semicolon
)brace
id|opt-&gt;loginfo
op_assign
l_int|NULL
suffix:semicolon
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;stdout&quot;
)paren
suffix:semicolon
r_return
id|shown
suffix:semicolon
)brace
eof
