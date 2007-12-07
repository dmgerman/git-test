macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;wt-status.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;diffcore.h&quot;
DECL|variable|wt_status_use_color
r_int
id|wt_status_use_color
op_assign
l_int|0
suffix:semicolon
DECL|variable|wt_status_colors
r_static
r_char
id|wt_status_colors
(braket
)braket
(braket
id|COLOR_MAXLEN
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
multiline_comment|/* WT_STATUS_HEADER: normal */
l_string|&quot;&bslash;033[32m&quot;
comma
multiline_comment|/* WT_STATUS_UPDATED: green */
l_string|&quot;&bslash;033[31m&quot;
comma
multiline_comment|/* WT_STATUS_CHANGED: red */
l_string|&quot;&bslash;033[31m&quot;
comma
multiline_comment|/* WT_STATUS_UNTRACKED: red */
)brace
suffix:semicolon
DECL|variable|use_add_msg
r_static
r_const
r_char
id|use_add_msg
(braket
)braket
op_assign
l_string|&quot;use &bslash;&quot;git add &lt;file&gt;...&bslash;&quot; to update what will be committed&quot;
suffix:semicolon
DECL|variable|use_add_rm_msg
r_static
r_const
r_char
id|use_add_rm_msg
(braket
)braket
op_assign
l_string|&quot;use &bslash;&quot;git add/rm &lt;file&gt;...&bslash;&quot; to update what will be committed&quot;
suffix:semicolon
DECL|variable|use_add_to_include_msg
r_static
r_const
r_char
id|use_add_to_include_msg
(braket
)braket
op_assign
l_string|&quot;use &bslash;&quot;git add &lt;file&gt;...&bslash;&quot; to include in what will be committed&quot;
suffix:semicolon
DECL|function|parse_status_slot
r_static
r_int
id|parse_status_slot
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|offset
comma
l_string|&quot;header&quot;
)paren
)paren
r_return
id|WT_STATUS_HEADER
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|offset
comma
l_string|&quot;updated&quot;
)paren
op_logical_or
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|offset
comma
l_string|&quot;added&quot;
)paren
)paren
r_return
id|WT_STATUS_UPDATED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|offset
comma
l_string|&quot;changed&quot;
)paren
)paren
r_return
id|WT_STATUS_CHANGED
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|offset
comma
l_string|&quot;untracked&quot;
)paren
)paren
r_return
id|WT_STATUS_UNTRACKED
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;bad config variable &squot;%s&squot;&quot;
comma
id|var
)paren
suffix:semicolon
)brace
DECL|function|color
r_static
r_const
r_char
op_star
id|color
c_func
(paren
r_int
id|slot
)paren
(brace
r_return
id|wt_status_use_color
ques
c_cond
id|wt_status_colors
(braket
id|slot
)braket
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
)brace
DECL|function|wt_status_prepare
r_void
id|wt_status_prepare
c_func
(paren
r_struct
id|wt_status
op_star
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
r_const
r_char
op_star
id|head
suffix:semicolon
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|s
)paren
)paren
suffix:semicolon
id|head
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|s-&gt;branch
op_assign
id|head
ques
c_cond
id|xstrdup
c_func
(paren
id|head
)paren
suffix:colon
l_int|NULL
suffix:semicolon
id|s-&gt;reference
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
id|s-&gt;fp
op_assign
id|stdout
suffix:semicolon
id|s-&gt;index_file
op_assign
id|get_index_file
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_cached_header
r_static
r_void
id|wt_status_print_cached_header
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_const
r_char
op_star
id|c
op_assign
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;# Changes to be committed:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;reference
)paren
(brace
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git reset %s &lt;file&gt;...&bslash;&quot; to unstage)&quot;
comma
id|s-&gt;reference
)paren
suffix:semicolon
)brace
r_else
(brace
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git rm --cached &lt;file&gt;...&bslash;&quot; to unstage)&quot;
)paren
suffix:semicolon
)brace
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_header
r_static
r_void
id|wt_status_print_header
c_func
(paren
r_struct
id|wt_status
op_star
id|s
comma
r_const
r_char
op_star
id|main
comma
r_const
r_char
op_star
id|sub
)paren
(brace
r_const
r_char
op_star
id|c
op_assign
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;# %s:&quot;
comma
id|main
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (%s)&quot;
comma
id|sub
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_trailer
r_static
r_void
id|wt_status_print_trailer
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
)brace
DECL|function|quote_path
r_static
r_char
op_star
id|quote_path
c_func
(paren
r_const
r_char
op_star
id|in
comma
r_int
id|len
comma
r_struct
id|strbuf
op_star
id|out
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
id|len
OL
l_int|0
)paren
id|len
op_assign
id|strlen
c_func
(paren
id|in
)paren
suffix:semicolon
id|strbuf_grow
c_func
(paren
id|out
comma
id|len
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|out
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_int
id|off
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|prefix
(braket
id|off
)braket
op_logical_and
id|off
OL
id|len
op_logical_and
id|prefix
(braket
id|off
)braket
op_eq
id|in
(braket
id|off
)braket
)paren
r_if
c_cond
(paren
id|prefix
(braket
id|off
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|prefix
op_add_assign
id|off
op_plus
l_int|1
suffix:semicolon
id|in
op_add_assign
id|off
op_plus
l_int|1
suffix:semicolon
id|len
op_sub_assign
id|off
op_plus
l_int|1
suffix:semicolon
id|off
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|off
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|prefix
suffix:semicolon
id|prefix
op_increment
)paren
r_if
c_cond
(paren
op_star
id|prefix
op_eq
l_char|&squot;/&squot;
)paren
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;../&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|in
op_increment
comma
id|len
op_decrement
)paren
(brace
r_int
id|ch
op_assign
op_star
id|in
suffix:semicolon
r_switch
c_cond
(paren
id|ch
)paren
(brace
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;&bslash;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;r&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;&bslash;&bslash;r&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|strbuf_addch
c_func
(paren
id|out
comma
id|ch
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|out-&gt;len
)paren
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;./&quot;
)paren
suffix:semicolon
r_return
id|out-&gt;buf
suffix:semicolon
)brace
DECL|function|wt_status_print_filepair
r_static
r_void
id|wt_status_print_filepair
c_func
(paren
r_struct
id|wt_status
op_star
id|s
comma
r_int
id|t
comma
r_struct
id|diff_filepair
op_star
id|p
)paren
(brace
r_const
r_char
op_star
id|c
op_assign
id|color
c_func
(paren
id|t
)paren
suffix:semicolon
r_const
r_char
op_star
id|one
comma
op_star
id|two
suffix:semicolon
r_struct
id|strbuf
id|onebuf
comma
id|twobuf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|onebuf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|twobuf
comma
l_int|0
)paren
suffix:semicolon
id|one
op_assign
id|quote_path
c_func
(paren
id|p-&gt;one-&gt;path
comma
l_int|1
comma
op_amp
id|onebuf
comma
id|s-&gt;prefix
)paren
suffix:semicolon
id|two
op_assign
id|quote_path
c_func
(paren
id|p-&gt;two-&gt;path
comma
l_int|1
comma
op_amp
id|twobuf
comma
id|s-&gt;prefix
)paren
suffix:semicolon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;status
)paren
(brace
r_case
id|DIFF_STATUS_ADDED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;new file:   %s&quot;
comma
id|one
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_COPIED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;copied:     %s -&gt; %s&quot;
comma
id|one
comma
id|two
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_DELETED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;deleted:    %s&quot;
comma
id|one
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_MODIFIED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;modified:   %s&quot;
comma
id|one
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_RENAMED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;renamed:    %s -&gt; %s&quot;
comma
id|one
comma
id|two
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_TYPE_CHANGED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;typechange: %s&quot;
comma
id|one
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_UNKNOWN
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;unknown:    %s&quot;
comma
id|one
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_UNMERGED
suffix:colon
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;unmerged:   %s&quot;
comma
id|one
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;bug: unhandled diff status %c&quot;
comma
id|p-&gt;status
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|s-&gt;fp
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|onebuf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|twobuf
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_updated_cb
r_static
r_void
id|wt_status_print_updated_cb
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_options
op_star
id|options
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|wt_status
op_star
id|s
op_assign
id|data
suffix:semicolon
r_int
id|shown_header
op_assign
l_int|0
suffix:semicolon
r_int
id|i
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|status
op_eq
l_char|&squot;U&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shown_header
)paren
(brace
id|wt_status_print_cached_header
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;commitable
op_assign
l_int|1
suffix:semicolon
id|shown_header
op_assign
l_int|1
suffix:semicolon
)brace
id|wt_status_print_filepair
c_func
(paren
id|s
comma
id|WT_STATUS_UPDATED
comma
id|q-&gt;queue
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shown_header
)paren
id|wt_status_print_trailer
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_changed_cb
r_static
r_void
id|wt_status_print_changed_cb
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_options
op_star
id|options
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|wt_status
op_star
id|s
op_assign
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;nr
)paren
(brace
r_const
r_char
op_star
id|msg
op_assign
id|use_add_msg
suffix:semicolon
id|s-&gt;workdir_dirty
op_assign
l_int|1
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|status
op_eq
id|DIFF_STATUS_DELETED
)paren
(brace
id|msg
op_assign
id|use_add_rm_msg
suffix:semicolon
r_break
suffix:semicolon
)brace
id|wt_status_print_header
c_func
(paren
id|s
comma
l_string|&quot;Changed but not updated&quot;
comma
id|msg
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|wt_status_print_filepair
c_func
(paren
id|s
comma
id|WT_STATUS_CHANGED
comma
id|q-&gt;queue
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;nr
)paren
id|wt_status_print_trailer
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
DECL|function|wt_read_cache
r_static
r_void
id|wt_read_cache
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
id|discard_cache
c_func
(paren
)paren
suffix:semicolon
id|read_cache_from
c_func
(paren
id|s-&gt;index_file
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_initial
r_static
r_void
id|wt_status_print_initial
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|wt_read_cache
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_nr
)paren
(brace
id|s-&gt;commitable
op_assign
l_int|1
suffix:semicolon
id|wt_status_print_cached_header
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_UPDATED
)paren
comma
l_string|&quot;new file: %s&quot;
comma
id|quote_path
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
l_int|1
comma
op_amp
id|buf
comma
id|s-&gt;prefix
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|active_nr
)paren
id|wt_status_print_trailer
c_func
(paren
id|s
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
DECL|function|wt_status_print_updated
r_static
r_void
id|wt_status_print_updated
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
op_amp
id|rev
comma
id|s-&gt;reference
)paren
suffix:semicolon
id|rev.diffopt.output_format
op_or_assign
id|DIFF_FORMAT_CALLBACK
suffix:semicolon
id|rev.diffopt.format_callback
op_assign
id|wt_status_print_updated_cb
suffix:semicolon
id|rev.diffopt.format_callback_data
op_assign
id|s
suffix:semicolon
id|rev.diffopt.detect_rename
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.rename_limit
op_assign
l_int|100
suffix:semicolon
id|rev.diffopt.break_opt
op_assign
l_int|0
suffix:semicolon
id|wt_read_cache
c_func
(paren
id|s
)paren
suffix:semicolon
id|run_diff_index
c_func
(paren
op_amp
id|rev
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_changed
r_static
r_void
id|wt_status_print_changed
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|rev.diffopt.output_format
op_or_assign
id|DIFF_FORMAT_CALLBACK
suffix:semicolon
id|rev.diffopt.format_callback
op_assign
id|wt_status_print_changed_cb
suffix:semicolon
id|rev.diffopt.format_callback_data
op_assign
id|s
suffix:semicolon
id|wt_read_cache
c_func
(paren
id|s
)paren
suffix:semicolon
id|run_diff_files
c_func
(paren
op_amp
id|rev
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_untracked
r_static
r_void
id|wt_status_print_untracked
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_struct
id|dir_struct
id|dir
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|shown_header
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dir
comma
l_int|0
comma
r_sizeof
(paren
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;untracked
)paren
(brace
id|dir.show_other_directories
op_assign
l_int|1
suffix:semicolon
id|dir.hide_empty_directories
op_assign
l_int|1
suffix:semicolon
)brace
id|setup_standard_excludes
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|read_directory
c_func
(paren
op_amp
id|dir
comma
l_string|&quot;.&quot;
comma
l_string|&quot;&quot;
comma
l_int|0
comma
l_int|NULL
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
id|dir.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* check for matching entry, which is unmerged; lifted from&n;&t;&t; * builtin-ls-files:show_other_files */
r_struct
id|dir_entry
op_star
id|ent
op_assign
id|dir.entries
(braket
id|i
)braket
suffix:semicolon
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
id|die
c_func
(paren
l_string|&quot;bug in wt_status_print_untracked&quot;
)paren
suffix:semicolon
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|active_nr
)paren
(brace
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_namelen
c_func
(paren
id|ce
)paren
op_eq
id|ent-&gt;len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|shown_header
)paren
(brace
id|s-&gt;workdir_untracked
op_assign
l_int|1
suffix:semicolon
id|wt_status_print_header
c_func
(paren
id|s
comma
l_string|&quot;Untracked files&quot;
comma
id|use_add_to_include_msg
)paren
suffix:semicolon
id|shown_header
op_assign
l_int|1
suffix:semicolon
)brace
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_UNTRACKED
)paren
comma
l_string|&quot;%s&quot;
comma
id|quote_path
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
comma
op_amp
id|buf
comma
id|s-&gt;prefix
)paren
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
DECL|function|wt_status_print_verbose
r_static
r_void
id|wt_status_print_verbose
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
r_int
id|saved_stdout
suffix:semicolon
id|fflush
c_func
(paren
id|s-&gt;fp
)paren
suffix:semicolon
multiline_comment|/* Sigh, the entire diff machinery is hardcoded to output to&n;&t; * stdout.  Do the dup-dance...*/
id|saved_stdout
op_assign
id|dup
c_func
(paren
id|STDOUT_FILENO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved_stdout
OL
l_int|0
op_logical_or
id|dup2
c_func
(paren
id|fileno
c_func
(paren
id|s-&gt;fp
)paren
comma
id|STDOUT_FILENO
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;couldn&squot;t redirect stdout&bslash;n&quot;
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
op_amp
id|rev
comma
id|s-&gt;reference
)paren
suffix:semicolon
id|rev.diffopt.output_format
op_or_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
id|rev.diffopt.detect_rename
op_assign
l_int|1
suffix:semicolon
id|wt_read_cache
c_func
(paren
id|s
)paren
suffix:semicolon
id|run_diff_index
c_func
(paren
op_amp
id|rev
comma
l_int|1
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dup2
c_func
(paren
id|saved_stdout
comma
id|STDOUT_FILENO
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;couldn&squot;t restore stdout&bslash;n&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|saved_stdout
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print
r_void
id|wt_status_print
c_func
(paren
r_struct
id|wt_status
op_star
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
id|s-&gt;is_initial
op_assign
id|get_sha1
c_func
(paren
id|s-&gt;reference
comma
id|sha1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;branch
)paren
(brace
r_const
r_char
op_star
id|on_what
op_assign
l_string|&quot;On branch &quot;
suffix:semicolon
r_const
r_char
op_star
id|branch_name
op_assign
id|s-&gt;branch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|branch_name
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
id|branch_name
op_add_assign
l_int|11
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|branch_name
comma
l_string|&quot;HEAD&quot;
)paren
)paren
(brace
id|branch_name
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|on_what
op_assign
l_string|&quot;Not currently on any branch.&quot;
suffix:semicolon
)brace
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;# %s%s&quot;
comma
id|on_what
comma
id|branch_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|s-&gt;is_initial
)paren
(brace
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;# Initial commit&quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
id|wt_status_print_initial
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_else
(brace
id|wt_status_print_updated
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
id|wt_status_print_changed
c_func
(paren
id|s
)paren
suffix:semicolon
id|wt_status_print_untracked
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;verbose
op_logical_and
op_logical_neg
id|s-&gt;is_initial
)paren
id|wt_status_print_verbose
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;commitable
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;amend
)paren
id|fprintf
c_func
(paren
id|s-&gt;fp
comma
l_string|&quot;# No changes&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;workdir_dirty
)paren
id|printf
c_func
(paren
l_string|&quot;no changes added to commit (use &bslash;&quot;git add&bslash;&quot; and/or &bslash;&quot;git commit -a&bslash;&quot;)&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;workdir_untracked
)paren
id|printf
c_func
(paren
l_string|&quot;nothing added to commit but untracked files present (use &bslash;&quot;git add&bslash;&quot; to track)&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;is_initial
)paren
id|printf
c_func
(paren
l_string|&quot;nothing to commit (create/copy files and use &bslash;&quot;git add&bslash;&quot; to track)&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;nothing to commit (working directory clean)&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|git_status_config
r_int
id|git_status_config
c_func
(paren
r_const
r_char
op_star
id|k
comma
r_const
r_char
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|k
comma
l_string|&quot;status.color&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|k
comma
l_string|&quot;color.status&quot;
)paren
)paren
(brace
id|wt_status_use_color
op_assign
id|git_config_colorbool
c_func
(paren
id|k
comma
id|v
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|k
comma
l_string|&quot;status.color.&quot;
)paren
op_logical_or
op_logical_neg
id|prefixcmp
c_func
(paren
id|k
comma
l_string|&quot;color.status.&quot;
)paren
)paren
(brace
r_int
id|slot
op_assign
id|parse_status_slot
c_func
(paren
id|k
comma
l_int|13
)paren
suffix:semicolon
id|color_parse
c_func
(paren
id|v
comma
id|k
comma
id|wt_status_colors
(braket
id|slot
)braket
)paren
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|k
comma
id|v
)paren
suffix:semicolon
)brace
eof
