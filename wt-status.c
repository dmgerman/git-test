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
op_star
id|use_add_msg
op_assign
l_string|&quot;use &bslash;&quot;git add &lt;file&gt;...&bslash;&quot; to incrementally add content to commit&quot;
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
id|s-&gt;amend
op_assign
l_int|0
suffix:semicolon
id|s-&gt;verbose
op_assign
l_int|0
suffix:semicolon
id|s-&gt;commitable
op_assign
l_int|0
suffix:semicolon
id|s-&gt;untracked
op_assign
l_int|0
suffix:semicolon
id|s-&gt;workdir_clean
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|wt_status_print_header
r_static
r_void
id|wt_status_print_header
c_func
(paren
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
id|color_printf_ln
c_func
(paren
id|c
comma
l_string|&quot;# %s:&quot;
comma
id|main
)paren
suffix:semicolon
id|color_printf_ln
c_func
(paren
id|c
comma
l_string|&quot;#   (%s)&quot;
comma
id|sub
)paren
suffix:semicolon
id|color_printf_ln
c_func
(paren
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
r_void
)paren
(brace
id|color_printf_ln
c_func
(paren
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
DECL|function|quote_crlf
r_static
r_const
r_char
op_star
id|quote_crlf
c_func
(paren
r_const
r_char
op_star
id|in
comma
r_char
op_star
id|buf
comma
r_int
id|sz
)paren
(brace
r_const
r_char
op_star
id|scan
suffix:semicolon
r_char
op_star
id|out
suffix:semicolon
r_const
r_char
op_star
id|ret
op_assign
id|in
suffix:semicolon
r_for
c_loop
(paren
id|scan
op_assign
id|in
comma
id|out
op_assign
id|buf
suffix:semicolon
op_star
id|scan
suffix:semicolon
id|scan
op_increment
)paren
(brace
r_int
id|ch
op_assign
op_star
id|scan
suffix:semicolon
r_int
id|quoted
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
id|quoted
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;r&squot;
suffix:colon
id|quoted
op_assign
l_char|&squot;r&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|out
op_increment
op_assign
id|ch
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|out
op_increment
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|quoted
suffix:semicolon
id|ret
op_assign
id|buf
suffix:semicolon
)brace
op_star
id|out
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|wt_status_print_filepair
r_static
r_void
id|wt_status_print_filepair
c_func
(paren
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
r_char
id|onebuf
(braket
id|PATH_MAX
)braket
comma
id|twobuf
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|one
op_assign
id|quote_crlf
c_func
(paren
id|p-&gt;one-&gt;path
comma
id|onebuf
comma
r_sizeof
(paren
id|onebuf
)paren
)paren
suffix:semicolon
id|two
op_assign
id|quote_crlf
c_func
(paren
id|p-&gt;two-&gt;path
comma
id|twobuf
comma
r_sizeof
(paren
id|twobuf
)paren
)paren
suffix:semicolon
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|color_printf
c_func
(paren
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
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
id|wt_status_print_header
c_func
(paren
l_string|&quot;Added but not yet committed&quot;
comma
l_string|&quot;will commit&quot;
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
id|s-&gt;workdir_clean
op_assign
l_int|0
suffix:semicolon
id|wt_status_print_header
c_func
(paren
l_string|&quot;Changed but not added&quot;
comma
id|use_add_msg
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
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_initial
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
r_char
id|buf
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|read_cache
c_func
(paren
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
id|wt_status_print_header
c_func
(paren
l_string|&quot;Added but not yet committed&quot;
comma
l_string|&quot;will commit&quot;
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
id|color_printf
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
id|color_printf_ln
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_UPDATED
)paren
comma
l_string|&quot;new file: %s&quot;
comma
id|quote_crlf
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
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
r_const
r_char
op_star
id|x
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|shown_header
op_assign
l_int|0
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
id|dir.exclude_per_dir
op_assign
l_string|&quot;.gitignore&quot;
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
id|x
op_assign
id|git_path
c_func
(paren
l_string|&quot;info/exclude&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file_exists
c_func
(paren
id|x
)paren
)paren
id|add_excludes_from_file
c_func
(paren
op_amp
id|dir
comma
id|x
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
id|s-&gt;workdir_clean
op_assign
l_int|0
suffix:semicolon
id|wt_status_print_header
c_func
(paren
l_string|&quot;Untracked files&quot;
comma
id|use_add_msg
)paren
suffix:semicolon
id|shown_header
op_assign
l_int|1
suffix:semicolon
)brace
id|color_printf
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
id|color_printf_ln
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_UNTRACKED
)paren
comma
l_string|&quot;%.*s&quot;
comma
id|ent-&gt;len
comma
id|ent-&gt;name
)paren
suffix:semicolon
)brace
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
id|color_printf_ln
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;# On branch %s&quot;
comma
id|s-&gt;branch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;is_initial
)paren
(brace
id|color_printf_ln
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
id|color_printf_ln
c_func
(paren
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
comma
l_string|&quot;# Initial commit&quot;
)paren
suffix:semicolon
id|color_printf_ln
c_func
(paren
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
id|discard_cache
c_func
(paren
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
id|printf
c_func
(paren
l_string|&quot;# No changes&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;workdir_clean
)paren
id|printf
c_func
(paren
id|s-&gt;is_initial
ques
c_cond
l_string|&quot;nothing to commit&bslash;n&quot;
suffix:colon
l_string|&quot;nothing to commit (working directory matches HEAD)&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;no changes added to commit (use &bslash;&quot;git add&bslash;&quot; and/or &bslash;&quot;git commit [-a|-i|-o]&bslash;&quot;)&bslash;n&quot;
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
id|strncmp
c_func
(paren
id|k
comma
l_string|&quot;status.color.&quot;
comma
l_int|13
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|k
comma
l_string|&quot;color.status&quot;
comma
l_int|13
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
