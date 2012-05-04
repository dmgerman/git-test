macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;list-objects.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;graph.h&quot;
macro_line|#include &quot;bisect.h&quot;
DECL|variable|rev_list_usage
r_static
r_const
r_char
id|rev_list_usage
(braket
)braket
op_assign
l_string|&quot;git rev-list [OPTION] &lt;commit-id&gt;... [ -- paths... ]&bslash;n&quot;
l_string|&quot;  limiting output:&bslash;n&quot;
l_string|&quot;    --max-count=&lt;n&gt;&bslash;n&quot;
l_string|&quot;    --max-age=&lt;epoch&gt;&bslash;n&quot;
l_string|&quot;    --min-age=&lt;epoch&gt;&bslash;n&quot;
l_string|&quot;    --sparse&bslash;n&quot;
l_string|&quot;    --no-merges&bslash;n&quot;
l_string|&quot;    --min-parents=&lt;n&gt;&bslash;n&quot;
l_string|&quot;    --no-min-parents&bslash;n&quot;
l_string|&quot;    --max-parents=&lt;n&gt;&bslash;n&quot;
l_string|&quot;    --no-max-parents&bslash;n&quot;
l_string|&quot;    --remove-empty&bslash;n&quot;
l_string|&quot;    --all&bslash;n&quot;
l_string|&quot;    --branches&bslash;n&quot;
l_string|&quot;    --tags&bslash;n&quot;
l_string|&quot;    --remotes&bslash;n&quot;
l_string|&quot;    --stdin&bslash;n&quot;
l_string|&quot;    --quiet&bslash;n&quot;
l_string|&quot;  ordering output:&bslash;n&quot;
l_string|&quot;    --topo-order&bslash;n&quot;
l_string|&quot;    --date-order&bslash;n&quot;
l_string|&quot;    --reverse&bslash;n&quot;
l_string|&quot;  formatting output:&bslash;n&quot;
l_string|&quot;    --parents&bslash;n&quot;
l_string|&quot;    --children&bslash;n&quot;
l_string|&quot;    --objects | --objects-edge&bslash;n&quot;
l_string|&quot;    --unpacked&bslash;n&quot;
l_string|&quot;    --header | --pretty&bslash;n&quot;
l_string|&quot;    --abbrev=&lt;n&gt; | --no-abbrev&bslash;n&quot;
l_string|&quot;    --abbrev-commit&bslash;n&quot;
l_string|&quot;    --left-right&bslash;n&quot;
l_string|&quot;  special purpose:&bslash;n&quot;
l_string|&quot;    --bisect&bslash;n&quot;
l_string|&quot;    --bisect-vars&bslash;n&quot;
l_string|&quot;    --bisect-all&quot;
suffix:semicolon
r_static
r_void
id|finish_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|function|show_commit
r_static
r_void
id|show_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|rev_list_info
op_star
id|info
op_assign
id|data
suffix:semicolon
r_struct
id|rev_info
op_star
id|revs
op_assign
id|info-&gt;revs
suffix:semicolon
id|graph_show_commit
c_func
(paren
id|revs-&gt;graph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;count
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|PATCHSAME
)paren
id|revs-&gt;count_same
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|SYMMETRIC_LEFT
)paren
id|revs-&gt;count_left
op_increment
suffix:semicolon
r_else
id|revs-&gt;count_right
op_increment
suffix:semicolon
id|finish_commit
c_func
(paren
id|commit
comma
id|data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;show_timestamp
)paren
id|printf
c_func
(paren
l_string|&quot;%lu &quot;
comma
id|commit-&gt;date
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;header_prefix
)paren
id|fputs
c_func
(paren
id|info-&gt;header_prefix
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;graph
)paren
id|fputs
c_func
(paren
id|get_revision_mark
c_func
(paren
id|revs
comma
id|commit
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;abbrev_commit
op_logical_and
id|revs-&gt;abbrev
)paren
id|fputs
c_func
(paren
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|revs-&gt;abbrev
)paren
comma
id|stdout
)paren
suffix:semicolon
r_else
id|fputs
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;print_parents
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|parents-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|revs-&gt;children.name
)paren
(brace
r_struct
id|commit_list
op_star
id|children
suffix:semicolon
id|children
op_assign
id|lookup_decoration
c_func
(paren
op_amp
id|revs-&gt;children
comma
op_amp
id|commit-&gt;object
)paren
suffix:semicolon
r_while
c_loop
(paren
id|children
)paren
(brace
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|children-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|children
op_assign
id|children-&gt;next
suffix:semicolon
)brace
)brace
id|show_decorations
c_func
(paren
id|revs
comma
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;verbose_header
op_logical_and
id|commit-&gt;buffer
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|ctx.abbrev
op_assign
id|revs-&gt;abbrev
suffix:semicolon
id|ctx.date_mode
op_assign
id|revs-&gt;date_mode
suffix:semicolon
id|ctx.date_mode_explicit
op_assign
id|revs-&gt;date_mode_explicit
suffix:semicolon
id|ctx.fmt
op_assign
id|revs-&gt;commit_format
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
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;graph
)paren
(brace
r_if
c_cond
(paren
id|buf.len
)paren
(brace
r_if
c_cond
(paren
id|revs-&gt;commit_format
op_ne
id|CMIT_FMT_ONELINE
)paren
id|graph_show_oneline
c_func
(paren
id|revs-&gt;graph
)paren
suffix:semicolon
id|graph_show_commit_msg
c_func
(paren
id|revs-&gt;graph
comma
op_amp
id|buf
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Add a newline after the commit message.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * Usually, this newline produces a blank&n;&t;&t;&t;&t; * padding line between entries, in which case&n;&t;&t;&t;&t; * we need to add graph padding on this line.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * However, the commit message may not end in a&n;&t;&t;&t;&t; * newline.  In this case the newline simply&n;&t;&t;&t;&t; * ends the last line of the commit message,&n;&t;&t;&t;&t; * and we don&squot;t need any graph output.  (This&n;&t;&t;&t;&t; * always happens with CMIT_FMT_ONELINE, and it&n;&t;&t;&t;&t; * happens with CMIT_FMT_USERFORMAT when the&n;&t;&t;&t;&t; * format doesn&squot;t explicitly end in a newline.)&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|buf.len
op_logical_and
id|buf.buf
(braket
id|buf.len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|graph_show_padding
c_func
(paren
id|revs-&gt;graph
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * If the message buffer is empty, just show&n;&t;&t;&t;&t; * the rest of the graph output for this&n;&t;&t;&t;&t; * commit.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|graph_show_remainder
c_func
(paren
id|revs-&gt;graph
)paren
)paren
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|revs-&gt;commit_format
op_ne
id|CMIT_FMT_USERFORMAT
op_logical_or
id|buf.len
)paren
(brace
id|fwrite
c_func
(paren
id|buf.buf
comma
l_int|1
comma
id|buf.len
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
id|info-&gt;hdr_termination
)paren
suffix:semicolon
)brace
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|graph_show_remainder
c_func
(paren
id|revs-&gt;graph
)paren
)paren
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
id|maybe_flush_or_die
c_func
(paren
id|stdout
comma
l_string|&quot;stdout&quot;
)paren
suffix:semicolon
id|finish_commit
c_func
(paren
id|commit
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|finish_commit
r_static
r_void
id|finish_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;parents
)paren
(brace
id|free_commit_list
c_func
(paren
id|commit-&gt;parents
)paren
suffix:semicolon
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free
c_func
(paren
id|commit-&gt;buffer
)paren
suffix:semicolon
id|commit-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|finish_object
r_static
r_void
id|finish_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_struct
id|name_path
op_star
id|path
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
id|obj-&gt;type
op_eq
id|OBJ_BLOB
op_logical_and
op_logical_neg
id|has_sha1_file
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;missing blob object &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|show_object
r_static
r_void
id|show_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|component
)paren
(brace
r_char
op_star
id|name
op_assign
id|path_name
c_func
(paren
id|path
comma
id|component
)paren
suffix:semicolon
multiline_comment|/* An object with name &quot;foo&bslash;n0000000...&quot; can be used to&n;&t; * confuse downstream &quot;git pack-objects&quot; very badly.&n;&t; */
r_const
r_char
op_star
id|ep
op_assign
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|finish_object
c_func
(paren
id|obj
comma
id|path
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s %.*s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
(paren
r_int
)paren
(paren
id|ep
id|name
)paren
comma
id|name
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
id|name
)paren
suffix:semicolon
id|free
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
DECL|function|show_edge
r_static
r_void
id|show_edge
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;-%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|log2i
r_static
r_inline
r_int
id|log2i
c_func
(paren
r_int
id|n
)paren
(brace
r_int
id|log2
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
OG
l_int|1
suffix:semicolon
id|n
op_rshift_assign
l_int|1
)paren
id|log2
op_increment
suffix:semicolon
r_return
id|log2
suffix:semicolon
)brace
DECL|function|exp2i
r_static
r_inline
r_int
id|exp2i
c_func
(paren
r_int
id|n
)paren
(brace
r_return
l_int|1
op_lshift
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Estimate the number of bisect steps left (after the current step)&n; *&n; * For any x between 0 included and 2^n excluded, the probability for&n; * n - 1 steps left looks like:&n; *&n; * P(2^n + x) == (2^n - x) / (2^n + x)&n; *&n; * and P(2^n + x) &lt; 0.5 means 2^n &lt; 3x&n; */
DECL|function|estimate_bisect_steps
r_int
id|estimate_bisect_steps
c_func
(paren
r_int
id|all
)paren
(brace
r_int
id|n
comma
id|x
comma
id|e
suffix:semicolon
r_if
c_cond
(paren
id|all
OL
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
id|n
op_assign
id|log2i
c_func
(paren
id|all
)paren
suffix:semicolon
id|e
op_assign
id|exp2i
c_func
(paren
id|n
)paren
suffix:semicolon
id|x
op_assign
id|all
id|e
suffix:semicolon
r_return
(paren
id|e
OL
l_int|3
op_star
id|x
)paren
ques
c_cond
id|n
suffix:colon
id|n
l_int|1
suffix:semicolon
)brace
DECL|function|print_commit_list
r_void
id|print_commit_list
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_const
r_char
op_star
id|format_cur
comma
r_const
r_char
op_star
id|format_last
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_const
r_char
op_star
id|format
op_assign
id|list-&gt;next
ques
c_cond
id|format_cur
suffix:colon
id|format_last
suffix:semicolon
id|printf
c_func
(paren
id|format
comma
id|sha1_to_hex
c_func
(paren
id|list-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_tried_revs
r_static
r_void
id|show_tried_revs
c_func
(paren
r_struct
id|commit_list
op_star
id|tried
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;bisect_tried=&squot;&quot;
)paren
suffix:semicolon
id|print_commit_list
c_func
(paren
id|tried
comma
l_string|&quot;%s|&quot;
comma
l_string|&quot;%s&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&squot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|print_var_str
r_static
r_void
id|print_var_str
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|val
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s=&squot;%s&squot;&bslash;n&quot;
comma
id|var
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|print_var_int
r_static
r_void
id|print_var_int
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_int
id|val
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s=%d&bslash;n&quot;
comma
id|var
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|show_bisect_vars
r_static
r_int
id|show_bisect_vars
c_func
(paren
r_struct
id|rev_list_info
op_star
id|info
comma
r_int
id|reaches
comma
r_int
id|all
)paren
(brace
r_int
id|cnt
comma
id|flags
op_assign
id|info-&gt;bisect_show_flags
suffix:semicolon
r_char
id|hex
(braket
l_int|41
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_struct
id|commit_list
op_star
id|tried
suffix:semicolon
r_struct
id|rev_info
op_star
id|revs
op_assign
id|info-&gt;revs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;commits
op_logical_and
op_logical_neg
(paren
id|flags
op_amp
id|BISECT_SHOW_TRIED
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|revs-&gt;commits
op_assign
id|filter_skipped
c_func
(paren
id|revs-&gt;commits
comma
op_amp
id|tried
comma
id|flags
op_amp
id|BISECT_SHOW_ALL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * revs-&gt;commits can reach &quot;reaches&quot; commits among&n;&t; * &quot;all&quot; commits.  If it is good, then there are&n;&t; * (all-reaches) commits left to be bisected.&n;&t; * On the other hand, if it is bad, then the set&n;&t; * to bisect is &quot;reaches&quot;.&n;&t; * A bisect set of size N has (N-1) commits further&n;&t; * to test, as we already know one bad one.&n;&t; */
id|cnt
op_assign
id|all
id|reaches
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
id|reaches
)paren
id|cnt
op_assign
id|reaches
suffix:semicolon
r_if
c_cond
(paren
id|revs-&gt;commits
)paren
id|strcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|revs-&gt;commits-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|BISECT_SHOW_ALL
)paren
(brace
id|traverse_commit_list
c_func
(paren
id|revs
comma
id|show_commit
comma
id|show_object
comma
id|info
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;------&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|BISECT_SHOW_TRIED
)paren
id|show_tried_revs
c_func
(paren
id|tried
)paren
suffix:semicolon
id|print_var_str
c_func
(paren
l_string|&quot;bisect_rev&quot;
comma
id|hex
)paren
suffix:semicolon
id|print_var_int
c_func
(paren
l_string|&quot;bisect_nr&quot;
comma
id|cnt
l_int|1
)paren
suffix:semicolon
id|print_var_int
c_func
(paren
l_string|&quot;bisect_good&quot;
comma
id|all
id|reaches
l_int|1
)paren
suffix:semicolon
id|print_var_int
c_func
(paren
l_string|&quot;bisect_bad&quot;
comma
id|reaches
l_int|1
)paren
suffix:semicolon
id|print_var_int
c_func
(paren
l_string|&quot;bisect_all&quot;
comma
id|all
)paren
suffix:semicolon
id|print_var_int
c_func
(paren
l_string|&quot;bisect_steps&quot;
comma
id|estimate_bisect_steps
c_func
(paren
id|all
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_rev_list
r_int
id|cmd_rev_list
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
id|revs
suffix:semicolon
r_struct
id|rev_list_info
id|info
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|bisect_list
op_assign
l_int|0
suffix:semicolon
r_int
id|bisect_show_vars
op_assign
l_int|0
suffix:semicolon
r_int
id|bisect_find_all
op_assign
l_int|0
suffix:semicolon
r_int
id|quiet
op_assign
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
id|prefix
)paren
suffix:semicolon
id|revs.abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
id|revs.commit_format
op_assign
id|CMIT_FMT_UNSPECIFIED
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
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.revs
op_assign
op_amp
id|revs
suffix:semicolon
r_if
c_cond
(paren
id|revs.bisect
)paren
id|bisect_list
op_assign
l_int|1
suffix:semicolon
id|quiet
op_assign
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs.diffopt
comma
id|QUICK
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
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--header&quot;
)paren
)paren
(brace
id|revs.verbose_header
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
l_string|&quot;--timestamp&quot;
)paren
)paren
(brace
id|info.show_timestamp
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
l_string|&quot;--bisect&quot;
)paren
)paren
(brace
id|bisect_list
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
l_string|&quot;--bisect-all&quot;
)paren
)paren
(brace
id|bisect_list
op_assign
l_int|1
suffix:semicolon
id|bisect_find_all
op_assign
l_int|1
suffix:semicolon
id|info.bisect_show_flags
op_assign
id|BISECT_SHOW_ALL
suffix:semicolon
id|revs.show_decorations
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
l_string|&quot;--bisect-vars&quot;
)paren
)paren
(brace
id|bisect_list
op_assign
l_int|1
suffix:semicolon
id|bisect_show_vars
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|rev_list_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs.commit_format
op_ne
id|CMIT_FMT_UNSPECIFIED
)paren
(brace
multiline_comment|/* The command line has a --pretty  */
id|info.hdr_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|revs.commit_format
op_eq
id|CMIT_FMT_ONELINE
)paren
id|info.header_prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_else
id|info.header_prefix
op_assign
l_string|&quot;commit &quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|revs.verbose_header
)paren
multiline_comment|/* Only --header was specified */
id|revs.commit_format
op_assign
id|CMIT_FMT_RAW
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|revs.commits
op_logical_and
(paren
op_logical_neg
(paren
id|revs.tag_objects
op_logical_or
id|revs.tree_objects
op_logical_or
id|revs.blob_objects
)paren
op_logical_and
op_logical_neg
id|revs.pending.nr
)paren
)paren
op_logical_or
id|revs.diff
)paren
id|usage
c_func
(paren
id|rev_list_usage
)paren
suffix:semicolon
id|save_commit_buffer
op_assign
(paren
id|revs.verbose_header
op_logical_or
id|revs.grep_filter.pattern_list
op_logical_or
id|revs.grep_filter.header_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bisect_list
)paren
id|revs.limited
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.tree_objects
)paren
id|mark_edges_uninteresting
c_func
(paren
id|revs.commits
comma
op_amp
id|revs
comma
id|show_edge
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bisect_list
)paren
(brace
r_int
id|reaches
op_assign
id|reaches
comma
id|all
op_assign
id|all
suffix:semicolon
id|revs.commits
op_assign
id|find_bisection
c_func
(paren
id|revs.commits
comma
op_amp
id|reaches
comma
op_amp
id|all
comma
id|bisect_find_all
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bisect_show_vars
)paren
r_return
id|show_bisect_vars
c_func
(paren
op_amp
id|info
comma
id|reaches
comma
id|all
)paren
suffix:semicolon
)brace
id|traverse_commit_list
c_func
(paren
op_amp
id|revs
comma
id|quiet
ques
c_cond
id|finish_commit
suffix:colon
id|show_commit
comma
id|quiet
ques
c_cond
id|finish_object
suffix:colon
id|show_object
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.count
)paren
(brace
r_if
c_cond
(paren
id|revs.left_right
op_logical_and
id|revs.cherry_mark
)paren
id|printf
c_func
(paren
l_string|&quot;%d&bslash;t%d&bslash;t%d&bslash;n&quot;
comma
id|revs.count_left
comma
id|revs.count_right
comma
id|revs.count_same
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|revs.left_right
)paren
id|printf
c_func
(paren
l_string|&quot;%d&bslash;t%d&bslash;n&quot;
comma
id|revs.count_left
comma
id|revs.count_right
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|revs.cherry_mark
)paren
id|printf
c_func
(paren
l_string|&quot;%d&bslash;t%d&bslash;n&quot;
comma
id|revs.count_left
op_plus
id|revs.count_right
comma
id|revs.count_same
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|revs.count_left
op_plus
id|revs.count_right
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
