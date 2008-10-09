macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;list-objects.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;graph.h&quot;
multiline_comment|/* bits #0-15 in revision.h */
DECL|macro|COUNTED
mdefine_line|#define COUNTED&t;&t;(1u&lt;&lt;16)
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
l_string|&quot;    --max-count=nr&bslash;n&quot;
l_string|&quot;    --max-age=epoch&bslash;n&quot;
l_string|&quot;    --min-age=epoch&bslash;n&quot;
l_string|&quot;    --sparse&bslash;n&quot;
l_string|&quot;    --no-merges&bslash;n&quot;
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
l_string|&quot;    --abbrev=nr | --no-abbrev&bslash;n&quot;
l_string|&quot;    --abbrev-commit&bslash;n&quot;
l_string|&quot;    --left-right&bslash;n&quot;
l_string|&quot;  special purpose:&bslash;n&quot;
l_string|&quot;    --bisect&bslash;n&quot;
l_string|&quot;    --bisect-vars&bslash;n&quot;
l_string|&quot;    --bisect-all&quot;
suffix:semicolon
DECL|variable|revs
r_static
r_struct
id|rev_info
id|revs
suffix:semicolon
DECL|variable|bisect_list
r_static
r_int
id|bisect_list
suffix:semicolon
DECL|variable|show_timestamp
r_static
r_int
id|show_timestamp
suffix:semicolon
DECL|variable|hdr_termination
r_static
r_int
id|hdr_termination
suffix:semicolon
DECL|variable|header_prefix
r_static
r_const
r_char
op_star
id|header_prefix
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
)paren
(brace
id|graph_show_commit
c_func
(paren
id|revs.graph
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_timestamp
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
id|header_prefix
)paren
id|fputs
c_func
(paren
id|header_prefix
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs.graph
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
id|revs.left_right
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
r_if
c_cond
(paren
id|revs.abbrev_commit
op_logical_and
id|revs.abbrev
)paren
id|fputs
c_func
(paren
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|revs.abbrev
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
id|revs.print_parents
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
id|revs.children.name
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
id|revs.children
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
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.commit_format
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
id|revs.verbose_header
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
id|pretty_print_commit
c_func
(paren
id|revs.commit_format
comma
id|commit
comma
op_amp
id|buf
comma
id|revs.abbrev
comma
l_int|NULL
comma
l_int|NULL
comma
id|revs.date_mode
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revs.graph
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
id|revs.commit_format
op_ne
id|CMIT_FMT_ONELINE
)paren
id|graph_show_oneline
c_func
(paren
id|revs.graph
)paren
suffix:semicolon
id|graph_show_commit_msg
c_func
(paren
id|revs.graph
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
id|revs.graph
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
id|revs.graph
)paren
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
id|buf.len
)paren
id|printf
c_func
(paren
l_string|&quot;%s%c&quot;
comma
id|buf.buf
comma
id|hdr_termination
)paren
suffix:semicolon
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
id|revs.graph
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
id|object_array_entry
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;item-&gt;type
op_eq
id|OBJ_BLOB
op_logical_and
op_logical_neg
id|has_sha1_file
c_func
(paren
id|p-&gt;item-&gt;sha1
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
id|p-&gt;item-&gt;sha1
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
id|object_array_entry
op_star
id|p
)paren
(brace
multiline_comment|/* An object with name &quot;foo&bslash;n0000000...&quot; can be used to&n;&t; * confuse downstream &quot;git pack-objects&quot; very badly.&n;&t; */
r_const
r_char
op_star
id|ep
op_assign
id|strchr
c_func
(paren
id|p-&gt;name
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|finish_object
c_func
(paren
id|p
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
id|p-&gt;item-&gt;sha1
)paren
comma
(paren
r_int
)paren
(paren
id|ep
id|p-&gt;name
)paren
comma
id|p-&gt;name
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
id|p-&gt;item-&gt;sha1
)paren
comma
id|p-&gt;name
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
multiline_comment|/*&n; * This is a truly stupid algorithm, but it&squot;s only&n; * used for bisection, and we just don&squot;t care enough.&n; *&n; * We care just barely enough to avoid recursing for&n; * non-merge entries.&n; */
DECL|function|count_distance
r_static
r_int
id|count_distance
c_func
(paren
r_struct
id|commit_list
op_star
id|entry
)paren
(brace
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|entry-&gt;item
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
(paren
id|UNINTERESTING
op_or
id|COUNTED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|TREESAME
)paren
)paren
id|nr
op_increment
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|COUNTED
suffix:semicolon
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|entry
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|nr
op_add_assign
id|count_distance
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
)brace
r_return
id|nr
suffix:semicolon
)brace
DECL|function|clear_distance
r_static
r_void
id|clear_distance
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|list-&gt;item
suffix:semicolon
id|commit-&gt;object.flags
op_and_assign
op_complement
id|COUNTED
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
)brace
DECL|macro|DEBUG_BISECT
mdefine_line|#define DEBUG_BISECT 0
DECL|function|weight
r_static
r_inline
r_int
id|weight
c_func
(paren
r_struct
id|commit_list
op_star
id|elem
)paren
(brace
r_return
op_star
(paren
(paren
r_int
op_star
)paren
(paren
id|elem-&gt;item-&gt;util
)paren
)paren
suffix:semicolon
)brace
DECL|function|weight_set
r_static
r_inline
r_void
id|weight_set
c_func
(paren
r_struct
id|commit_list
op_star
id|elem
comma
r_int
id|weight
)paren
(brace
op_star
(paren
(paren
r_int
op_star
)paren
(paren
id|elem-&gt;item-&gt;util
)paren
)paren
op_assign
id|weight
suffix:semicolon
)brace
DECL|function|count_interesting_parents
r_static
r_int
id|count_interesting_parents
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_int
id|count
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
comma
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
r_if
c_cond
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|halfway
r_static
r_inline
r_int
id|halfway
c_func
(paren
r_struct
id|commit_list
op_star
id|p
comma
r_int
id|nr
)paren
(brace
multiline_comment|/*&n;&t; * Don&squot;t short-cut something we are not going to return!&n;&t; */
r_if
c_cond
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|TREESAME
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_BISECT
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * 2 and 3 are halfway of 5.&n;&t; * 3 is halfway of 6 but 2 and 4 are not.&n;&t; */
r_switch
c_cond
(paren
l_int|2
op_star
id|weight
c_func
(paren
id|p
)paren
id|nr
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#if !DEBUG_BISECT
DECL|macro|show_list
mdefine_line|#define show_list(a,b,c,d) do { ; } while (0)
macro_line|#else
DECL|function|show_list
r_static
r_void
id|show_list
c_func
(paren
r_const
r_char
op_star
id|debug
comma
r_int
id|counted
comma
r_int
id|nr
comma
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s (%d/%d)&bslash;n&quot;
comma
id|debug
comma
id|counted
comma
id|nr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|commit_list
op_star
id|pp
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|commit-&gt;object.sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_char
op_star
id|ep
comma
op_star
id|sp
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%c%c%c &quot;
comma
(paren
id|flags
op_amp
id|TREESAME
)paren
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;T&squot;
comma
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
ques
c_cond
l_char|&squot;U&squot;
suffix:colon
l_char|&squot; &squot;
comma
(paren
id|flags
op_amp
id|COUNTED
)paren
ques
c_cond
l_char|&squot;C&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;util
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%3d&quot;
comma
id|weight
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;---&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %.*s&quot;
comma
l_int|8
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
id|commit-&gt;parents
suffix:semicolon
id|pp
suffix:semicolon
id|pp
op_assign
id|pp-&gt;next
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %.*s&quot;
comma
l_int|8
comma
id|sha1_to_hex
c_func
(paren
id|pp-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|sp
op_assign
id|strstr
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp
)paren
(brace
id|sp
op_add_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|ep
op_assign
id|sp
suffix:semicolon
op_star
id|ep
op_logical_and
op_star
id|ep
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|ep
op_increment
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %.*s&quot;
comma
(paren
r_int
)paren
(paren
id|ep
id|sp
)paren
comma
id|sp
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* DEBUG_BISECT */
DECL|function|best_bisection
r_static
r_struct
id|commit_list
op_star
id|best_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
id|nr
)paren
(brace
r_struct
id|commit_list
op_star
id|p
comma
op_star
id|best
suffix:semicolon
r_int
id|best_distance
op_assign
l_int|1
suffix:semicolon
id|best
op_assign
id|list
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|distance
suffix:semicolon
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|TREESAME
)paren
r_continue
suffix:semicolon
id|distance
op_assign
id|weight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
id|distance
OL
id|distance
)paren
id|distance
op_assign
id|nr
id|distance
suffix:semicolon
r_if
c_cond
(paren
id|distance
OG
id|best_distance
)paren
(brace
id|best
op_assign
id|p
suffix:semicolon
id|best_distance
op_assign
id|distance
suffix:semicolon
)brace
)brace
r_return
id|best
suffix:semicolon
)brace
DECL|struct|commit_dist
r_struct
id|commit_dist
(brace
DECL|member|commit
r_struct
id|commit
op_star
id|commit
suffix:semicolon
DECL|member|distance
r_int
id|distance
suffix:semicolon
)brace
suffix:semicolon
DECL|function|compare_commit_dist
r_static
r_int
id|compare_commit_dist
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|commit_dist
op_star
id|a
comma
op_star
id|b
suffix:semicolon
id|a
op_assign
(paren
r_struct
id|commit_dist
op_star
)paren
id|a_
suffix:semicolon
id|b
op_assign
(paren
r_struct
id|commit_dist
op_star
)paren
id|b_
suffix:semicolon
r_if
c_cond
(paren
id|a-&gt;distance
op_ne
id|b-&gt;distance
)paren
r_return
id|b-&gt;distance
id|a-&gt;distance
suffix:semicolon
multiline_comment|/* desc sort */
r_return
id|hashcmp
c_func
(paren
id|a-&gt;commit-&gt;object.sha1
comma
id|b-&gt;commit-&gt;object.sha1
)paren
suffix:semicolon
)brace
DECL|function|best_bisection_sorted
r_static
r_struct
id|commit_list
op_star
id|best_bisection_sorted
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
id|nr
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_struct
id|commit_dist
op_star
id|array
op_assign
id|xcalloc
c_func
(paren
id|nr
comma
r_sizeof
(paren
op_star
id|array
)paren
)paren
suffix:semicolon
r_int
id|cnt
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
comma
id|cnt
op_assign
l_int|0
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|distance
suffix:semicolon
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|TREESAME
)paren
r_continue
suffix:semicolon
id|distance
op_assign
id|weight
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
id|distance
OL
id|distance
)paren
id|distance
op_assign
id|nr
id|distance
suffix:semicolon
id|array
(braket
id|cnt
)braket
dot
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
id|array
(braket
id|cnt
)braket
dot
id|distance
op_assign
id|distance
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
id|qsort
c_func
(paren
id|array
comma
id|cnt
comma
r_sizeof
(paren
op_star
id|array
)paren
comma
id|compare_commit_dist
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|list
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|name_decoration
op_star
id|r
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|r
)paren
op_plus
l_int|100
)paren
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
op_amp
(paren
id|array
(braket
id|i
)braket
dot
id|commit-&gt;object
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|r-&gt;name
comma
l_string|&quot;dist=%d&quot;
comma
id|array
(braket
id|i
)braket
dot
id|distance
)paren
suffix:semicolon
id|r-&gt;next
op_assign
id|add_decoration
c_func
(paren
op_amp
id|name_decoration
comma
id|obj
comma
id|r
)paren
suffix:semicolon
id|p-&gt;item
op_assign
id|array
(braket
id|i
)braket
dot
id|commit
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
)paren
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|free
c_func
(paren
id|array
)paren
suffix:semicolon
r_return
id|list
suffix:semicolon
)brace
multiline_comment|/*&n; * zero or positive weight is the number of interesting commits it can&n; * reach, including itself.  Especially, weight = 0 means it does not&n; * reach any tree-changing commits (e.g. just above uninteresting one&n; * but traversal is with pathspec).&n; *&n; * weight = -1 means it has one parent and its distance is yet to&n; * be computed.&n; *&n; * weight = -2 means it has more than one parent and its distance is&n; * unknown.  After running count_distance() first, they will get zero&n; * or positive distance.&n; */
DECL|function|do_find_bisection
r_static
r_struct
id|commit_list
op_star
id|do_find_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
id|nr
comma
r_int
op_star
id|weights
comma
r_int
id|find_all
)paren
(brace
r_int
id|n
comma
id|counted
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
id|counted
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|p
op_assign
id|list
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
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
r_int
id|flags
op_assign
id|commit-&gt;object.flags
suffix:semicolon
id|p-&gt;item-&gt;util
op_assign
op_amp
id|weights
(braket
id|n
op_increment
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|count_interesting_parents
c_func
(paren
id|commit
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TREESAME
)paren
)paren
(brace
id|weight_set
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
id|counted
op_increment
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 count one&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * otherwise, it is known not to reach any&n;&t;&t;&t; * tree-changing commit and gets weight 0.&n;&t;&t;&t; */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|weight_set
c_func
(paren
id|p
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|weight_set
c_func
(paren
id|p
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|show_list
c_func
(paren
l_string|&quot;bisection 2 initialize&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If you have only one parent in the resulting set&n;&t; * then you can reach one commit more than that parent&n;&t; * can reach.  So we do not have to run the expensive&n;&t; * count_distance() for single strand of pearls.&n;&t; *&n;&t; * However, if you have more than one parents, you cannot&n;&t; * just add their distance and one for yourself, since&n;&t; * they usually reach the same ancestor and you would&n;&t; * end up counting them twice that way.&n;&t; *&n;&t; * So we will first count distance of merges the usual&n;&t; * way, and then fill the blanks using cheaper algorithm.&n;&t; */
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|weight
c_func
(paren
id|p
)paren
op_ne
l_int|2
)paren
r_continue
suffix:semicolon
id|weight_set
c_func
(paren
id|p
comma
id|count_distance
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
id|clear_distance
c_func
(paren
id|list
)paren
suffix:semicolon
multiline_comment|/* Does it happen to be at exactly half-way? */
r_if
c_cond
(paren
op_logical_neg
id|find_all
op_logical_and
id|halfway
c_func
(paren
id|p
comma
id|nr
)paren
)paren
r_return
id|p
suffix:semicolon
id|counted
op_increment
suffix:semicolon
)brace
id|show_list
c_func
(paren
l_string|&quot;bisection 2 count_distance&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|counted
OL
id|nr
)paren
(brace
r_for
c_loop
(paren
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_struct
id|commit_list
op_star
id|q
suffix:semicolon
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|weight
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|p-&gt;item-&gt;parents
suffix:semicolon
id|q
suffix:semicolon
id|q
op_assign
id|q-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|weight
c_func
(paren
id|q
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * weight for p is unknown but q is known.&n;&t;&t;&t; * add one for p itself if p is to be counted,&n;&t;&t;&t; * otherwise inherit it from q directly.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TREESAME
)paren
)paren
(brace
id|weight_set
c_func
(paren
id|p
comma
id|weight
c_func
(paren
id|q
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|counted
op_increment
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 count one&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
)brace
r_else
id|weight_set
c_func
(paren
id|p
comma
id|weight
c_func
(paren
id|q
)paren
)paren
suffix:semicolon
multiline_comment|/* Does it happen to be at exactly half-way? */
r_if
c_cond
(paren
op_logical_neg
id|find_all
op_logical_and
id|halfway
c_func
(paren
id|p
comma
id|nr
)paren
)paren
r_return
id|p
suffix:semicolon
)brace
)brace
id|show_list
c_func
(paren
l_string|&quot;bisection 2 counted all&quot;
comma
id|counted
comma
id|nr
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|find_all
)paren
r_return
id|best_bisection
c_func
(paren
id|list
comma
id|nr
)paren
suffix:semicolon
r_else
r_return
id|best_bisection_sorted
c_func
(paren
id|list
comma
id|nr
)paren
suffix:semicolon
)brace
DECL|function|find_bisection
r_static
r_struct
id|commit_list
op_star
id|find_bisection
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_int
op_star
id|reaches
comma
r_int
op_star
id|all
comma
r_int
id|find_all
)paren
(brace
r_int
id|nr
comma
id|on_list
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
comma
op_star
id|best
comma
op_star
id|next
comma
op_star
id|last
suffix:semicolon
r_int
op_star
id|weights
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 entry&quot;
comma
l_int|0
comma
l_int|0
comma
id|list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Count the number of total and tree-changing items on the&n;&t; * list, while reversing the list.&n;&t; */
r_for
c_loop
(paren
id|nr
op_assign
id|on_list
op_assign
l_int|0
comma
id|last
op_assign
l_int|NULL
comma
id|p
op_assign
id|list
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|next
)paren
(brace
r_int
id|flags
op_assign
id|p-&gt;item-&gt;object.flags
suffix:semicolon
id|next
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|UNINTERESTING
)paren
r_continue
suffix:semicolon
id|p-&gt;next
op_assign
id|last
suffix:semicolon
id|last
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TREESAME
)paren
)paren
id|nr
op_increment
suffix:semicolon
id|on_list
op_increment
suffix:semicolon
)brace
id|list
op_assign
id|last
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;bisection 2 sorted&quot;
comma
l_int|0
comma
id|nr
comma
id|list
)paren
suffix:semicolon
op_star
id|all
op_assign
id|nr
suffix:semicolon
id|weights
op_assign
id|xcalloc
c_func
(paren
id|on_list
comma
r_sizeof
(paren
op_star
id|weights
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the real work of finding bisection commit. */
id|best
op_assign
id|do_find_bisection
c_func
(paren
id|list
comma
id|nr
comma
id|weights
comma
id|find_all
)paren
suffix:semicolon
r_if
c_cond
(paren
id|best
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|find_all
)paren
id|best-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|reaches
op_assign
id|weight
c_func
(paren
id|best
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|weights
)paren
suffix:semicolon
r_return
id|best
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
id|commit_list
op_star
id|list
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|read_from_stdin
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
l_int|0
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
id|quiet
op_assign
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|revs.diffopt
comma
id|QUIET
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
id|show_timestamp
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|read_from_stdin
op_increment
)paren
id|die
c_func
(paren
l_string|&quot;--stdin given twice?&quot;
)paren
suffix:semicolon
id|read_revisions_from_stdin
c_func
(paren
op_amp
id|revs
)paren
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
id|hdr_termination
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
id|header_prefix
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_else
id|header_prefix
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
id|list
op_assign
id|revs.commits
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|list
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
id|revs.verbose_header
op_logical_or
id|revs.grep_filter.pattern_list
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
(brace
r_int
id|cnt
suffix:semicolon
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs.commits
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * revs.commits can reach &quot;reaches&quot; commits among&n;&t;&t;&t; * &quot;all&quot; commits.  If it is good, then there are&n;&t;&t;&t; * (all-reaches) commits left to be bisected.&n;&t;&t;&t; * On the other hand, if it is bad, then the set&n;&t;&t;&t; * to bisect is &quot;reaches&quot;.&n;&t;&t;&t; * A bisect set of size N has (N-1) commits further&n;&t;&t;&t; * to test, as we already know one bad one.&n;&t;&t;&t; */
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
id|strcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|revs.commits-&gt;item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bisect_find_all
)paren
(brace
id|traverse_commit_list
c_func
(paren
op_amp
id|revs
comma
id|show_commit
comma
id|show_object
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;------&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;bisect_rev=%s&bslash;n&quot;
l_string|&quot;bisect_nr=%d&bslash;n&quot;
l_string|&quot;bisect_good=%d&bslash;n&quot;
l_string|&quot;bisect_bad=%d&bslash;n&quot;
l_string|&quot;bisect_all=%d&bslash;n&quot;
comma
id|hex
comma
id|cnt
l_int|1
comma
id|all
id|reaches
l_int|1
comma
id|reaches
l_int|1
comma
id|all
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
