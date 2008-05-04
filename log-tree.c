macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;reflog-walk.h&quot;
DECL|variable|name_decoration
r_struct
id|decoration
id|name_decoration
op_assign
(brace
l_string|&quot;object names&quot;
)brace
suffix:semicolon
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
id|diff_unique_abbrev
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
l_string|&quot;%s%s&quot;
comma
id|prefix
comma
id|decoration-&gt;name
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
id|ch
comma
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
(paren
id|ch
op_assign
op_star
id|cp
)paren
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
DECL|function|has_non_ascii
r_static
r_int
id|has_non_ascii
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|ch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|non_ascii
c_func
(paren
id|ch
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
r_const
r_char
op_star
id|name
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
r_if
c_cond
(paren
id|opt-&gt;message_id
)paren
id|printf
c_func
(paren
l_string|&quot;Message-Id: &lt;%s&gt;&bslash;n&quot;
comma
id|opt-&gt;message_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;ref_message_id
)paren
id|printf
c_func
(paren
l_string|&quot;In-Reply-To: &lt;%s&gt;&bslash;nReferences: &lt;%s&gt;&bslash;n&quot;
comma
id|opt-&gt;ref_message_id
comma
id|opt-&gt;ref_message_id
)paren
suffix:semicolon
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
l_string|&quot;--%s%s&bslash;n&quot;
l_string|&quot;Content-Type: text/x-patch;&quot;
l_string|&quot; name=&bslash;&quot;%s.diff&bslash;&quot;&bslash;n&quot;
l_string|&quot;Content-Transfer-Encoding: 8bit&bslash;n&quot;
l_string|&quot;Content-Disposition: %s;&quot;
l_string|&quot; filename=&bslash;&quot;%s.diff&bslash;&quot;&bslash;n&bslash;n&quot;
comma
id|mime_boundary_leader
comma
id|opt-&gt;mime_boundary
comma
id|name
comma
id|opt-&gt;no_inline
ques
c_cond
l_string|&quot;attachment&quot;
suffix:colon
l_string|&quot;inline&quot;
comma
id|name
)paren
suffix:semicolon
id|opt-&gt;diffopt.stat_sep
op_assign
id|buffer
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
id|abbrev
op_assign
id|opt-&gt;diffopt.abbrev
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
id|subject
op_assign
l_int|NULL
comma
op_star
id|extra_headers
op_assign
id|opt-&gt;extra_headers
suffix:semicolon
r_int
id|need_8bit_cte
op_assign
l_int|0
suffix:semicolon
id|opt-&gt;loginfo
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt-&gt;verbose_header
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
id|fputs
c_func
(paren
id|diff_unique_abbrev
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
id|commit
)paren
suffix:semicolon
id|putchar
c_func
(paren
id|opt-&gt;diffopt.line_termination
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If use_terminator is set, add a newline at the end of the entry.&n;&t; * Otherwise, add a diffopt.line_termination character before all&n;&t; * entries but the first.  (IOW, as a separator between entries)&n;&t; */
r_if
c_cond
(paren
id|opt-&gt;shown_one
op_logical_and
op_logical_neg
id|opt-&gt;use_terminator
)paren
id|putchar
c_func
(paren
id|opt-&gt;diffopt.line_termination
)paren
suffix:semicolon
id|opt-&gt;shown_one
op_assign
l_int|1
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
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
op_amp
id|subject
comma
op_amp
id|extra_headers
comma
op_amp
id|need_8bit_cte
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
id|fputs
c_func
(paren
id|diff_unique_abbrev
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
id|diff_unique_abbrev
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
id|putchar
c_func
(paren
id|opt-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;reflog_info
)paren
(brace
id|show_reflog_message
c_func
(paren
id|opt-&gt;reflog_info
comma
id|opt-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
comma
id|opt-&gt;date_mode
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
id|strbuf_init
c_func
(paren
op_amp
id|msgbuf
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_8bit_cte
op_ge
l_int|0
)paren
id|need_8bit_cte
op_assign
id|has_non_ascii
c_func
(paren
id|opt-&gt;add_signoff
)paren
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
id|abbrev
comma
id|subject
comma
id|extra_headers
comma
id|opt-&gt;date_mode
comma
id|need_8bit_cte
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
r_if
c_cond
(paren
id|msgbuf.len
)paren
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
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
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
