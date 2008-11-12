macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;wt-status.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|variable|wt_status_relative_paths
r_int
id|wt_status_relative_paths
op_assign
l_int|1
suffix:semicolon
DECL|variable|wt_status_use_color
r_int
id|wt_status_use_color
op_assign
l_int|1
suffix:semicolon
DECL|variable|wt_status_submodule_summary
r_int
id|wt_status_submodule_summary
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
l_string|&quot;&bslash;033[31m&quot;
comma
multiline_comment|/* WT_STATUS_NOBRANCH: red */
)brace
suffix:semicolon
DECL|variable|show_untracked_files
r_enum
id|untracked_status_type
id|show_untracked_files
op_assign
id|SHOW_NORMAL_UNTRACKED_FILES
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
l_string|&quot;nobranch&quot;
)paren
)paren
r_return
id|WT_STATUS_NOBRANCH
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
OG
l_int|0
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
op_logical_neg
id|s-&gt;is_initial
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
DECL|function|wt_status_print_dirty_header
r_static
r_void
id|wt_status_print_dirty_header
c_func
(paren
r_struct
id|wt_status
op_star
id|s
comma
r_int
id|has_deleted
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
l_string|&quot;# Changed but not updated:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_deleted
)paren
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git add &lt;file&gt;...&bslash;&quot; to update what will be committed)&quot;
)paren
suffix:semicolon
r_else
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git add/rm &lt;file&gt;...&bslash;&quot; to update what will be committed)&quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git checkout -- &lt;file&gt;...&bslash;&quot; to discard changes in working directory)&quot;
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
DECL|function|wt_status_print_untracked_header
r_static
r_void
id|wt_status_print_untracked_header
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
l_string|&quot;# Untracked files:&quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git add &lt;file&gt;...&bslash;&quot; to include in what will be committed)&quot;
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
DECL|macro|quote_path
mdefine_line|#define quote_path quote_path_relative
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
op_assign
id|STRBUF_INIT
comma
id|twobuf
op_assign
id|STRBUF_INIT
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
r_int
id|has_deleted
op_assign
l_int|0
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
id|has_deleted
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|wt_status_print_dirty_header
c_func
(paren
id|s
comma
id|has_deleted
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
id|s-&gt;is_initial
ques
c_cond
id|EMPTY_TREE_SHA1_HEX
suffix:colon
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
l_int|200
suffix:semicolon
id|rev.diffopt.break_opt
op_assign
l_int|0
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
DECL|function|wt_status_print_submodule_summary
r_static
r_void
id|wt_status_print_submodule_summary
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_struct
id|child_process
id|sm_summary
suffix:semicolon
r_char
id|summary_limit
(braket
l_int|64
)braket
suffix:semicolon
r_char
id|index
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|env
(braket
)braket
op_assign
(brace
id|index
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;submodule&quot;
comma
l_string|&quot;summary&quot;
comma
l_string|&quot;--cached&quot;
comma
l_string|&quot;--for-status&quot;
comma
l_string|&quot;--summary-limit&quot;
comma
id|summary_limit
comma
id|s-&gt;amend
ques
c_cond
l_string|&quot;HEAD^&quot;
suffix:colon
l_string|&quot;HEAD&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|sprintf
c_func
(paren
id|summary_limit
comma
l_string|&quot;%d&quot;
comma
id|wt_status_submodule_summary
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|index
comma
r_sizeof
(paren
id|index
)paren
comma
l_string|&quot;GIT_INDEX_FILE=%s&quot;
comma
id|s-&gt;index_file
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sm_summary
comma
l_int|0
comma
r_sizeof
(paren
id|sm_summary
)paren
)paren
suffix:semicolon
id|sm_summary.argv
op_assign
id|argv
suffix:semicolon
id|sm_summary.env
op_assign
id|env
suffix:semicolon
id|sm_summary.git_cmd
op_assign
l_int|1
suffix:semicolon
id|sm_summary.no_stdin
op_assign
l_int|1
suffix:semicolon
id|fflush
c_func
(paren
id|s-&gt;fp
)paren
suffix:semicolon
id|sm_summary.out
op_assign
id|dup
c_func
(paren
id|fileno
c_func
(paren
id|s-&gt;fp
)paren
)paren
suffix:semicolon
multiline_comment|/* run_command closes it */
id|run_command
c_func
(paren
op_amp
id|sm_summary
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
op_assign
id|STRBUF_INIT
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
r_if
c_cond
(paren
op_logical_neg
id|cache_name_is_other
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
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
id|s-&gt;workdir_untracked
op_assign
l_int|1
suffix:semicolon
id|wt_status_print_untracked_header
c_func
(paren
id|s
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
id|s-&gt;is_initial
ques
c_cond
id|EMPTY_TREE_SHA1_HEX
suffix:colon
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
id|rev.diffopt.file
op_assign
id|s-&gt;fp
suffix:semicolon
id|rev.diffopt.close_file
op_assign
l_int|0
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
DECL|function|wt_status_print_tracking
r_static
r_void
id|wt_status_print_tracking
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|cp
comma
op_star
id|ep
suffix:semicolon
r_struct
id|branch
op_star
id|branch
suffix:semicolon
m_assert
(paren
id|s-&gt;branch
op_logical_and
op_logical_neg
id|s-&gt;is_initial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|s-&gt;branch
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
r_return
suffix:semicolon
id|branch
op_assign
id|branch_get
c_func
(paren
id|s-&gt;branch
op_plus
l_int|11
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|format_tracking_info
c_func
(paren
id|branch
comma
op_amp
id|sb
)paren
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|sb.buf
suffix:semicolon
(paren
id|ep
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
op_ne
l_int|NULL
suffix:semicolon
id|cp
op_assign
id|ep
op_plus
l_int|1
)paren
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
l_string|&quot;# %.*s&quot;
comma
(paren
r_int
)paren
(paren
id|ep
id|cp
)paren
comma
id|cp
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
r_const
r_char
op_star
id|branch_color
op_assign
id|color
c_func
(paren
id|WT_STATUS_HEADER
)paren
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
id|branch_color
op_assign
id|color
c_func
(paren
id|WT_STATUS_NOBRANCH
)paren
suffix:semicolon
id|on_what
op_assign
l_string|&quot;Not currently on any branch.&quot;
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
l_string|&quot;# &quot;
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|branch_color
comma
l_string|&quot;%s%s&quot;
comma
id|on_what
comma
id|branch_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;is_initial
)paren
id|wt_status_print_tracking
c_func
(paren
id|s
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
)brace
id|wt_status_print_updated
c_func
(paren
id|s
)paren
suffix:semicolon
id|wt_status_print_changed
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wt_status_submodule_summary
)paren
id|wt_status_print_submodule_summary
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_untracked_files
)paren
id|wt_status_print_untracked
c_func
(paren
id|s
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|s-&gt;commitable
)paren
id|fprintf
c_func
(paren
id|s-&gt;fp
comma
l_string|&quot;# Untracked files not listed (use -u option to show untracked files)&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;verbose
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
id|s-&gt;nowarn
)paren
suffix:semicolon
multiline_comment|/* nothing */
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
r_if
c_cond
(paren
op_logical_neg
id|show_untracked_files
)paren
id|printf
c_func
(paren
l_string|&quot;nothing to commit (use -u to show untracked files)&bslash;n&quot;
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
comma
r_void
op_star
id|cb
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
l_string|&quot;status.submodulesummary&quot;
)paren
)paren
(brace
r_int
id|is_bool
suffix:semicolon
id|wt_status_submodule_summary
op_assign
id|git_config_bool_or_int
c_func
(paren
id|k
comma
id|v
comma
op_amp
id|is_bool
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bool
op_logical_and
id|wt_status_submodule_summary
)paren
id|wt_status_submodule_summary
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|v
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|k
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
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|k
comma
l_string|&quot;status.relativepaths&quot;
)paren
)paren
(brace
id|wt_status_relative_paths
op_assign
id|git_config_bool
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
id|strcmp
c_func
(paren
id|k
comma
l_string|&quot;status.showuntrackedfiles&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|v
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|k
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|v
comma
l_string|&quot;no&quot;
)paren
)paren
id|show_untracked_files
op_assign
id|SHOW_NO_UNTRACKED_FILES
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|v
comma
l_string|&quot;normal&quot;
)paren
)paren
id|show_untracked_files
op_assign
id|SHOW_NORMAL_UNTRACKED_FILES
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|v
comma
l_string|&quot;all&quot;
)paren
)paren
id|show_untracked_files
op_assign
id|SHOW_ALL_UNTRACKED_FILES
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;Invalid untracked files mode &squot;%s&squot;&quot;
comma
id|v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_color_default_config
c_func
(paren
id|k
comma
id|v
comma
id|cb
)paren
suffix:semicolon
)brace
eof
