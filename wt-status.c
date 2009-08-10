macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;wt-status.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|variable|default_wt_status_colors
r_static
r_char
id|default_wt_status_colors
(braket
)braket
(braket
id|COLOR_MAXLEN
)braket
op_assign
(brace
id|GIT_COLOR_NORMAL
comma
multiline_comment|/* WT_STATUS_HEADER */
id|GIT_COLOR_GREEN
comma
multiline_comment|/* WT_STATUS_UPDATED */
id|GIT_COLOR_RED
comma
multiline_comment|/* WT_STATUS_CHANGED */
id|GIT_COLOR_RED
comma
multiline_comment|/* WT_STATUS_UNTRACKED */
id|GIT_COLOR_RED
comma
multiline_comment|/* WT_STATUS_NOBRANCH */
id|GIT_COLOR_RED
comma
multiline_comment|/* WT_STATUS_UNMERGED */
)brace
suffix:semicolon
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
comma
r_struct
id|wt_status
op_star
id|s
)paren
(brace
r_return
id|s-&gt;use_color
OG
l_int|0
ques
c_cond
id|s-&gt;color_palette
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
id|memcpy
c_func
(paren
id|s-&gt;color_palette
comma
id|default_wt_status_colors
comma
r_sizeof
(paren
id|default_wt_status_colors
)paren
)paren
suffix:semicolon
id|s-&gt;show_untracked_files
op_assign
id|SHOW_NORMAL_UNTRACKED_FILES
suffix:semicolon
id|s-&gt;use_color
op_assign
l_int|1
suffix:semicolon
id|s-&gt;relative_paths
op_assign
l_int|1
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
id|s-&gt;change.strdup_strings
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|wt_status_print_unmerged_header
r_static
r_void
id|wt_status_print_unmerged_header
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
comma
id|s
)paren
suffix:semicolon
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;# Unmerged paths:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;is_initial
)paren
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
r_else
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
id|color_fprintf_ln
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;#   (use &bslash;&quot;git add &lt;file&gt;...&bslash;&quot; to mark resolution)&quot;
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
comma
id|s
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
comma
id|s
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
comma
id|s
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
comma
id|s
)paren
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
)brace
DECL|macro|quote_path
mdefine_line|#define quote_path quote_path_relative
DECL|function|wt_status_print_unmerged_data
r_static
r_void
id|wt_status_print_unmerged_data
c_func
(paren
r_struct
id|wt_status
op_star
id|s
comma
r_struct
id|string_list_item
op_star
id|it
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
id|WT_STATUS_UNMERGED
comma
id|s
)paren
suffix:semicolon
r_struct
id|wt_status_change_data
op_star
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_struct
id|strbuf
id|onebuf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|one
comma
op_star
id|how
op_assign
l_string|&quot;bug&quot;
suffix:semicolon
id|one
op_assign
id|quote_path
c_func
(paren
id|it-&gt;string
comma
l_int|1
comma
op_amp
id|onebuf
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
comma
id|s
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|d-&gt;stagemask
)paren
(brace
r_case
l_int|1
suffix:colon
id|how
op_assign
l_string|&quot;both deleted:&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|how
op_assign
l_string|&quot;added by us:&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|how
op_assign
l_string|&quot;deleted by them:&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|how
op_assign
l_string|&quot;added by them:&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|how
op_assign
l_string|&quot;deleted by us:&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|how
op_assign
l_string|&quot;both added:&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|how
op_assign
l_string|&quot;both modified:&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|color_fprintf
c_func
(paren
id|s-&gt;fp
comma
id|c
comma
l_string|&quot;%-20s%s&bslash;n&quot;
comma
id|how
comma
id|one
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|onebuf
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_change_data
r_static
r_void
id|wt_status_print_change_data
c_func
(paren
r_struct
id|wt_status
op_star
id|s
comma
r_int
id|change_type
comma
r_struct
id|string_list_item
op_star
id|it
)paren
(brace
r_struct
id|wt_status_change_data
op_star
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_const
r_char
op_star
id|c
op_assign
id|color
c_func
(paren
id|change_type
comma
id|s
)paren
suffix:semicolon
r_int
id|status
op_assign
id|status
suffix:semicolon
r_char
op_star
id|one_name
suffix:semicolon
r_char
op_star
id|two_name
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
id|one_name
op_assign
id|two_name
op_assign
id|it-&gt;string
suffix:semicolon
r_switch
c_cond
(paren
id|change_type
)paren
(brace
r_case
id|WT_STATUS_UPDATED
suffix:colon
id|status
op_assign
id|d-&gt;index_status
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;head_path
)paren
id|one_name
op_assign
id|d-&gt;head_path
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WT_STATUS_CHANGED
suffix:colon
id|status
op_assign
id|d-&gt;worktree_status
suffix:semicolon
r_break
suffix:semicolon
)brace
id|one
op_assign
id|quote_path
c_func
(paren
id|one_name
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
id|two_name
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
comma
id|s
)paren
comma
l_string|&quot;#&bslash;t&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
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
id|status
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
DECL|function|wt_status_collect_changed_cb
r_static
r_void
id|wt_status_collect_changed_cb
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
op_logical_neg
id|q-&gt;nr
)paren
r_return
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
(brace
r_struct
id|diff_filepair
op_star
id|p
suffix:semicolon
r_struct
id|string_list_item
op_star
id|it
suffix:semicolon
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
id|it
op_assign
id|string_list_insert
c_func
(paren
id|p-&gt;one-&gt;path
comma
op_amp
id|s-&gt;change
)paren
suffix:semicolon
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
(brace
id|d
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|d
)paren
)paren
suffix:semicolon
id|it-&gt;util
op_assign
id|d
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;worktree_status
)paren
id|d-&gt;worktree_status
op_assign
id|p-&gt;status
suffix:semicolon
)brace
)brace
DECL|function|unmerged_mask
r_static
r_int
id|unmerged_mask
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|pos
comma
id|mask
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
r_return
l_int|0
suffix:semicolon
id|mask
op_assign
l_int|0
suffix:semicolon
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
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
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|path
)paren
op_logical_or
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_break
suffix:semicolon
id|mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_return
id|mask
suffix:semicolon
)brace
DECL|function|wt_status_collect_updated_cb
r_static
r_void
id|wt_status_collect_updated_cb
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
r_struct
id|diff_filepair
op_star
id|p
suffix:semicolon
r_struct
id|string_list_item
op_star
id|it
suffix:semicolon
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
id|it
op_assign
id|string_list_insert
c_func
(paren
id|p-&gt;two-&gt;path
comma
op_amp
id|s-&gt;change
)paren
suffix:semicolon
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
(brace
id|d
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|d
)paren
)paren
suffix:semicolon
id|it-&gt;util
op_assign
id|d
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;index_status
)paren
id|d-&gt;index_status
op_assign
id|p-&gt;status
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;status
)paren
(brace
r_case
id|DIFF_STATUS_COPIED
suffix:colon
r_case
id|DIFF_STATUS_RENAMED
suffix:colon
id|d-&gt;head_path
op_assign
id|xstrdup
c_func
(paren
id|p-&gt;one-&gt;path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_UNMERGED
suffix:colon
id|d-&gt;stagemask
op_assign
id|unmerged_mask
c_func
(paren
id|p-&gt;two-&gt;path
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|wt_status_collect_changes_worktree
r_static
r_void
id|wt_status_collect_changes_worktree
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
l_int|NULL
)paren
suffix:semicolon
id|rev.diffopt.output_format
op_or_assign
id|DIFF_FORMAT_CALLBACK
suffix:semicolon
id|rev.diffopt.format_callback
op_assign
id|wt_status_collect_changed_cb
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
DECL|function|wt_status_collect_changes_index
r_static
r_void
id|wt_status_collect_changes_index
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
id|wt_status_collect_updated_cb
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
DECL|function|wt_status_collect_changes_initial
r_static
r_void
id|wt_status_collect_changes_initial
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
r_struct
id|string_list_item
op_star
id|it
suffix:semicolon
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
id|it
op_assign
id|string_list_insert
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|s-&gt;change
)paren
suffix:semicolon
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
(brace
id|d
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|d
)paren
)paren
suffix:semicolon
id|it-&gt;util
op_assign
id|d
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|d-&gt;index_status
op_assign
id|DIFF_STATUS_UNMERGED
suffix:semicolon
id|d-&gt;stagemask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_else
id|d-&gt;index_status
op_assign
id|DIFF_STATUS_ADDED
suffix:semicolon
)brace
)brace
DECL|function|wt_status_collect_changes
r_void
id|wt_status_collect_changes
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
id|wt_status_collect_changes_worktree
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;is_initial
)paren
id|wt_status_collect_changes_initial
c_func
(paren
id|s
)paren
suffix:semicolon
r_else
id|wt_status_collect_changes_index
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
DECL|function|wt_status_print_unmerged
r_static
r_void
id|wt_status_print_unmerged
c_func
(paren
r_struct
id|wt_status
op_star
id|s
)paren
(brace
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
id|s-&gt;change.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
r_struct
id|string_list_item
op_star
id|it
suffix:semicolon
id|it
op_assign
op_amp
(paren
id|s-&gt;change.items
(braket
id|i
)braket
)paren
suffix:semicolon
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;stagemask
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
id|wt_status_print_unmerged_header
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
id|wt_status_print_unmerged_data
c_func
(paren
id|s
comma
id|it
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
id|s-&gt;change.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
r_struct
id|string_list_item
op_star
id|it
suffix:semicolon
id|it
op_assign
op_amp
(paren
id|s-&gt;change.items
(braket
id|i
)braket
)paren
suffix:semicolon
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;index_status
op_logical_or
id|d-&gt;index_status
op_eq
id|DIFF_STATUS_UNMERGED
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
id|wt_status_print_change_data
c_func
(paren
id|s
comma
id|WT_STATUS_UPDATED
comma
id|it
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
multiline_comment|/*&n; * -1 : has delete&n; *  0 : no change&n; *  1 : some change but no delete&n; */
DECL|function|wt_status_check_worktree_changes
r_static
r_int
id|wt_status_check_worktree_changes
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
r_int
id|changes
op_assign
l_int|0
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
id|s-&gt;change.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
id|d
op_assign
id|s-&gt;change.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;worktree_status
op_logical_or
id|d-&gt;worktree_status
op_eq
id|DIFF_STATUS_UNMERGED
)paren
r_continue
suffix:semicolon
id|changes
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;worktree_status
op_eq
id|DIFF_STATUS_DELETED
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|changes
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
r_int
id|i
suffix:semicolon
r_int
id|worktree_changes
op_assign
id|wt_status_check_worktree_changes
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|worktree_changes
)paren
r_return
suffix:semicolon
id|wt_status_print_dirty_header
c_func
(paren
id|s
comma
id|worktree_changes
OL
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
id|s-&gt;change.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|wt_status_change_data
op_star
id|d
suffix:semicolon
r_struct
id|string_list_item
op_star
id|it
suffix:semicolon
id|it
op_assign
op_amp
(paren
id|s-&gt;change.items
(braket
id|i
)braket
)paren
suffix:semicolon
id|d
op_assign
id|it-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d-&gt;worktree_status
op_logical_or
id|d-&gt;worktree_status
op_eq
id|DIFF_STATUS_UNMERGED
)paren
r_continue
suffix:semicolon
id|wt_status_print_change_data
c_func
(paren
id|s
comma
id|WT_STATUS_CHANGED
comma
id|it
)paren
suffix:semicolon
)brace
id|wt_status_print_trailer
c_func
(paren
id|s
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
id|s-&gt;submodule_summary
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
id|s-&gt;show_untracked_files
op_ne
id|SHOW_ALL_UNTRACKED_FILES
)paren
id|dir.flags
op_or_assign
id|DIR_SHOW_OTHER_DIRECTORIES
op_or
id|DIR_HIDE_EMPTY_DIRECTORIES
suffix:semicolon
id|setup_standard_excludes
c_func
(paren
op_amp
id|dir
)paren
suffix:semicolon
id|fill_directory
c_func
(paren
op_amp
id|dir
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
comma
id|s
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
comma
id|s
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
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|ALLOW_TEXTCONV
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
multiline_comment|/*&n;&t; * If we&squot;re not going to stdout, then we definitely don&squot;t&n;&t; * want color, since we are going to the commit message&n;&t; * file (and even the &quot;auto&quot; setting won&squot;t work, since it&n;&t; * will have checked isatty on stdout).&n;&t; */
r_if
c_cond
(paren
id|s-&gt;fp
op_ne
id|stdout
)paren
id|DIFF_OPT_CLR
c_func
(paren
op_amp
id|rev.diffopt
comma
id|COLOR_DIFF
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
comma
id|s
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
comma
id|s
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
comma
id|s
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
comma
id|s
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
comma
id|s
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
id|wt_status_collect_changes
c_func
(paren
id|s
)paren
suffix:semicolon
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
comma
id|s
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
comma
id|s
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
comma
id|s
)paren
comma
l_string|&quot;#&quot;
)paren
suffix:semicolon
)brace
id|wt_status_print_unmerged
c_func
(paren
id|s
)paren
suffix:semicolon
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
id|s-&gt;submodule_summary
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
id|s-&gt;show_untracked_files
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
id|s-&gt;show_untracked_files
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
eof
