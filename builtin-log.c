multiline_comment|/*&n; * Builtin &quot;git log&quot; and related commands (show, whatchanged)&n; *&n; * (C) Copyright 2006 Linus Torvalds&n; *&t;&t; 2006 Junio Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
multiline_comment|/* this is in builtin-diff.c */
r_void
id|add_head
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
)paren
suffix:semicolon
DECL|function|cmd_log_init
r_static
r_void
id|cmd_log_init
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
r_char
op_star
op_star
id|envp
comma
r_struct
id|rev_info
op_star
id|rev
)paren
(brace
id|rev-&gt;abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
id|rev-&gt;commit_format
op_assign
id|CMIT_FMT_DEFAULT
suffix:semicolon
id|rev-&gt;verbose_header
op_assign
l_int|1
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
id|rev
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev-&gt;diffopt.pickaxe
op_logical_or
id|rev-&gt;diffopt.filter
)paren
id|rev-&gt;always_show_header
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|cmd_log_walk
r_static
r_int
id|cmd_log_walk
c_func
(paren
r_struct
id|rev_info
op_star
id|rev
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
id|rev
)paren
suffix:semicolon
id|setup_pager
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|log_tree_commit
c_func
(paren
id|rev
comma
id|commit
)paren
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_whatchanged
r_int
id|cmd_whatchanged
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
r_char
op_star
op_star
id|envp
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
)paren
suffix:semicolon
id|rev.diff
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.recursive
op_assign
l_int|1
suffix:semicolon
id|rev.simplify_history
op_assign
l_int|0
suffix:semicolon
id|cmd_log_init
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev.diffopt.output_format
)paren
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_RAW
suffix:semicolon
r_return
id|cmd_log_walk
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
)brace
DECL|function|cmd_show
r_int
id|cmd_show
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
r_char
op_star
op_star
id|envp
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
)paren
suffix:semicolon
id|rev.diff
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.recursive
op_assign
l_int|1
suffix:semicolon
id|rev.combine_merges
op_assign
l_int|1
suffix:semicolon
id|rev.dense_combined_merges
op_assign
l_int|1
suffix:semicolon
id|rev.always_show_header
op_assign
l_int|1
suffix:semicolon
id|rev.ignore_merges
op_assign
l_int|0
suffix:semicolon
id|rev.no_walk
op_assign
l_int|1
suffix:semicolon
id|cmd_log_init
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
op_amp
id|rev
)paren
suffix:semicolon
r_return
id|cmd_log_walk
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
)brace
DECL|function|cmd_log
r_int
id|cmd_log
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
r_char
op_star
op_star
id|envp
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
)paren
suffix:semicolon
id|rev.always_show_header
op_assign
l_int|1
suffix:semicolon
id|cmd_log_init
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
op_amp
id|rev
)paren
suffix:semicolon
r_return
id|cmd_log_walk
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
)brace
DECL|function|istitlechar
r_static
r_int
id|istitlechar
c_func
(paren
r_char
id|c
)paren
(brace
r_return
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
op_logical_or
id|c
op_eq
l_char|&squot;.&squot;
op_logical_or
id|c
op_eq
l_char|&squot;_&squot;
suffix:semicolon
)brace
DECL|variable|extra_headers
r_static
r_char
op_star
id|extra_headers
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|extra_headers_size
r_static
r_int
id|extra_headers_size
op_assign
l_int|0
suffix:semicolon
DECL|function|git_format_config
r_static
r_int
id|git_format_config
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
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;format.headers&quot;
)paren
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|value
)paren
suffix:semicolon
id|extra_headers_size
op_add_assign
id|len
op_plus
l_int|1
suffix:semicolon
id|extra_headers
op_assign
id|realloc
c_func
(paren
id|extra_headers
comma
id|extra_headers_size
)paren
suffix:semicolon
id|extra_headers
(braket
id|extra_headers_size
id|len
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|strcat
c_func
(paren
id|extra_headers
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|realstdout
r_static
id|FILE
op_star
id|realstdout
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|output_directory
r_static
r_const
r_char
op_star
id|output_directory
op_assign
l_int|NULL
suffix:semicolon
DECL|function|reopen_stdout
r_static
r_void
id|reopen_stdout
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
r_int
id|keep_subject
)paren
(brace
r_char
id|filename
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|sol
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|output_directory
)paren
(brace
id|strlcpy
c_func
(paren
id|filename
comma
id|output_directory
comma
l_int|1010
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filename
(braket
id|len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|filename
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|filename
op_plus
id|len
comma
l_string|&quot;%04d&quot;
comma
id|nr
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
id|sol
op_assign
id|strstr
c_func
(paren
id|commit-&gt;buffer
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sol
)paren
(brace
r_int
id|j
comma
id|space
op_assign
l_int|1
suffix:semicolon
id|sol
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* strip [PATCH] or [PATCH blabla] */
r_if
c_cond
(paren
op_logical_neg
id|keep_subject
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|sol
comma
l_string|&quot;[PATCH&quot;
comma
l_int|6
)paren
)paren
(brace
r_char
op_star
id|eos
op_assign
id|strchr
c_func
(paren
id|sol
op_plus
l_int|6
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eos
)paren
(brace
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|eos
)paren
)paren
id|eos
op_increment
suffix:semicolon
id|sol
op_assign
id|eos
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|len
OL
l_int|1024
l_int|6
op_logical_and
id|sol
(braket
id|j
)braket
op_logical_and
id|sol
(braket
id|j
)braket
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|istitlechar
c_func
(paren
id|sol
(braket
id|j
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|space
)paren
(brace
id|filename
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;-&squot;
suffix:semicolon
id|space
op_assign
l_int|0
suffix:semicolon
)brace
id|filename
(braket
id|len
op_increment
)braket
op_assign
id|sol
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sol
(braket
id|j
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_while
c_loop
(paren
id|sol
(braket
id|j
op_plus
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
id|j
op_increment
suffix:semicolon
)brace
r_else
id|space
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|filename
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
op_logical_or
id|filename
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|len
op_decrement
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|filename
op_plus
id|len
comma
l_string|&quot;.txt&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|realstdout
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
id|freopen
c_func
(paren
id|filename
comma
l_string|&quot;w&quot;
comma
id|stdout
)paren
suffix:semicolon
)brace
DECL|function|get_patch_id
r_static
r_int
id|get_patch_id
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|diff_options
op_star
id|options
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
id|diff_tree_sha1
c_func
(paren
id|commit-&gt;parents-&gt;item-&gt;object.sha1
comma
id|commit-&gt;object.sha1
comma
l_string|&quot;&quot;
comma
id|options
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
id|options
)paren
suffix:semicolon
r_return
id|diff_flush_patch_id
c_func
(paren
id|options
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|get_patch_ids
r_static
r_void
id|get_patch_ids
c_func
(paren
r_struct
id|rev_info
op_star
id|rev
comma
r_struct
id|diff_options
op_star
id|options
)paren
(brace
r_struct
id|rev_info
id|check_rev
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|object
op_star
id|o1
comma
op_star
id|o2
suffix:semicolon
r_int
id|flags1
comma
id|flags2
suffix:semicolon
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
id|rev-&gt;pending.nr
op_ne
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;Need exactly one range.&quot;
)paren
suffix:semicolon
id|o1
op_assign
id|rev-&gt;pending.objects
(braket
l_int|0
)braket
dot
id|item
suffix:semicolon
id|flags1
op_assign
id|o1-&gt;flags
suffix:semicolon
id|o2
op_assign
id|rev-&gt;pending.objects
(braket
l_int|1
)braket
dot
id|item
suffix:semicolon
id|flags2
op_assign
id|o2-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags1
op_amp
id|UNINTERESTING
)paren
op_eq
(paren
id|flags2
op_amp
id|UNINTERESTING
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a range.&quot;
)paren
suffix:semicolon
id|diff_setup
c_func
(paren
id|options
)paren
suffix:semicolon
id|options-&gt;recursive
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|diff_setup_done
c_func
(paren
id|options
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;diff_setup_done failed&quot;
)paren
suffix:semicolon
multiline_comment|/* given a range a..b get all patch ids for b..a */
id|init_revisions
c_func
(paren
op_amp
id|check_rev
)paren
suffix:semicolon
id|o1-&gt;flags
op_xor_assign
id|UNINTERESTING
suffix:semicolon
id|o2-&gt;flags
op_xor_assign
id|UNINTERESTING
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|check_rev
comma
id|o1
comma
l_string|&quot;o1&quot;
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|check_rev
comma
id|o2
comma
l_string|&quot;o2&quot;
)paren
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
op_amp
id|check_rev
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
op_amp
id|check_rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* ignore merges */
r_if
c_cond
(paren
id|commit-&gt;parents
op_logical_and
id|commit-&gt;parents-&gt;next
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_patch_id
c_func
(paren
id|commit
comma
id|options
comma
id|sha1
)paren
)paren
id|created_object
c_func
(paren
id|sha1
comma
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|object
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* reset for next revision walk */
id|clear_commit_marks
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o1
comma
id|SEEN
op_or
id|UNINTERESTING
op_or
id|SHOWN
op_or
id|ADDED
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o2
comma
id|SEEN
op_or
id|UNINTERESTING
op_or
id|SHOWN
op_or
id|ADDED
)paren
suffix:semicolon
id|o1-&gt;flags
op_assign
id|flags1
suffix:semicolon
id|o2-&gt;flags
op_assign
id|flags2
suffix:semicolon
)brace
DECL|function|cmd_format_patch
r_int
id|cmd_format_patch
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
r_char
op_star
op_star
id|envp
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit
op_star
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|rev_info
id|rev
suffix:semicolon
r_int
id|nr
op_assign
l_int|0
comma
id|total
comma
id|i
comma
id|j
suffix:semicolon
r_int
id|use_stdout
op_assign
l_int|0
suffix:semicolon
r_int
id|numbered
op_assign
l_int|0
suffix:semicolon
r_int
id|start_number
op_assign
l_int|1
suffix:semicolon
r_int
id|keep_subject
op_assign
l_int|0
suffix:semicolon
r_int
id|ignore_if_in_upstream
op_assign
l_int|0
suffix:semicolon
r_struct
id|diff_options
id|patch_id_opts
suffix:semicolon
r_char
op_star
id|add_signoff
op_assign
l_int|NULL
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
id|rev.commit_format
op_assign
id|CMIT_FMT_EMAIL
suffix:semicolon
id|rev.verbose_header
op_assign
l_int|1
suffix:semicolon
id|rev.diff
op_assign
l_int|1
suffix:semicolon
id|rev.combine_merges
op_assign
l_int|0
suffix:semicolon
id|rev.ignore_merges
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.msg_sep
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|rev.diffopt.recursive
op_assign
l_int|1
suffix:semicolon
id|git_config
c_func
(paren
id|git_format_config
)paren
suffix:semicolon
id|rev.extra_headers
op_assign
id|extra_headers
suffix:semicolon
multiline_comment|/*&n;&t; * Parse the arguments before setup_revisions(), or something&n;&t; * like &quot;git fmt-patch -o a123 HEAD^..&quot; may fail; a123 is&n;&t; * possibly a valid SHA1.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
comma
id|j
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--stdout&quot;
)paren
)paren
id|use_stdout
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-n&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--numbered&quot;
)paren
)paren
id|numbered
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--start-number=&quot;
comma
l_int|15
)paren
)paren
id|start_number
op_assign
id|strtol
c_func
(paren
id|argv
(braket
id|i
)braket
op_plus
l_int|15
comma
l_int|NULL
comma
l_int|10
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
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--start-number&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;Need a number for --start-number&quot;
)paren
suffix:semicolon
id|start_number
op_assign
id|strtol
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-k&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--keep-subject&quot;
)paren
)paren
(brace
id|keep_subject
op_assign
l_int|1
suffix:semicolon
id|rev.total
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--output-directory&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-o&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_le
id|i
)paren
id|die
c_func
(paren
l_string|&quot;Which directory?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|output_directory
)paren
id|die
c_func
(paren
l_string|&quot;Two output directories?&quot;
)paren
suffix:semicolon
id|output_directory
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--signoff&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;-s&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|committer
suffix:semicolon
r_const
r_char
op_star
id|endpos
suffix:semicolon
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
id|committer
op_assign
id|git_committer_info
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|endpos
op_assign
id|strchr
c_func
(paren
id|committer
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|endpos
)paren
id|die
c_func
(paren
l_string|&quot;bogos committer info %s&bslash;n&quot;
comma
id|committer
)paren
suffix:semicolon
id|add_signoff
op_assign
id|xmalloc
c_func
(paren
id|endpos
id|committer
op_plus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|add_signoff
comma
id|committer
comma
id|endpos
id|committer
op_plus
l_int|1
)paren
suffix:semicolon
id|add_signoff
(braket
id|endpos
id|committer
op_plus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--attach&quot;
)paren
)paren
id|rev.mime_boundary
op_assign
id|git_version_string
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--attach=&quot;
comma
l_int|9
)paren
)paren
id|rev.mime_boundary
op_assign
id|argv
(braket
id|i
)braket
op_plus
l_int|9
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--ignore-if-in-upstream&quot;
)paren
)paren
id|ignore_if_in_upstream
op_assign
l_int|1
suffix:semicolon
r_else
id|argv
(braket
id|j
op_increment
)braket
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
)brace
id|argc
op_assign
id|j
suffix:semicolon
r_if
c_cond
(paren
id|start_number
OL
l_int|0
)paren
id|start_number
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|numbered
op_logical_and
id|keep_subject
)paren
id|die
(paren
l_string|&quot;-n and -k are mutually exclusive.&quot;
)paren
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
id|rev
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|die
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev.diffopt.output_format
)paren
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_DIFFSTAT
op_or
id|DIFF_FORMAT_PATCH
suffix:semicolon
r_if
c_cond
(paren
id|output_directory
)paren
(brace
r_if
c_cond
(paren
id|use_stdout
)paren
id|die
c_func
(paren
l_string|&quot;standard output, or directory, which one?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|output_directory
comma
l_int|0777
)paren
OL
l_int|0
op_logical_and
id|errno
op_ne
id|EEXIST
)paren
id|die
c_func
(paren
l_string|&quot;Could not create directory %s&quot;
comma
id|output_directory
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rev.pending.nr
op_eq
l_int|1
)paren
(brace
id|rev.pending.objects
(braket
l_int|0
)braket
dot
id|item-&gt;flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
id|add_head
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ignore_if_in_upstream
)paren
id|get_patch_ids
c_func
(paren
op_amp
id|rev
comma
op_amp
id|patch_id_opts
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_stdout
)paren
id|realstdout
op_assign
id|fdopen
c_func
(paren
id|dup
c_func
(paren
l_int|1
)paren
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
op_amp
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* ignore merges */
r_if
c_cond
(paren
id|commit-&gt;parents
op_logical_and
id|commit-&gt;parents-&gt;next
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ignore_if_in_upstream
op_logical_and
op_logical_neg
id|get_patch_id
c_func
(paren
id|commit
comma
op_amp
id|patch_id_opts
comma
id|sha1
)paren
op_logical_and
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
r_continue
suffix:semicolon
id|nr
op_increment
suffix:semicolon
id|list
op_assign
id|realloc
c_func
(paren
id|list
comma
id|nr
op_star
r_sizeof
(paren
id|list
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|list
(braket
id|nr
l_int|1
)braket
op_assign
id|commit
suffix:semicolon
)brace
id|total
op_assign
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|numbered
)paren
id|rev.total
op_assign
id|total
op_plus
id|start_number
l_int|1
suffix:semicolon
id|rev.add_signoff
op_assign
id|add_signoff
suffix:semicolon
r_while
c_loop
(paren
l_int|0
op_le
op_decrement
id|nr
)paren
(brace
r_int
id|shown
suffix:semicolon
id|commit
op_assign
id|list
(braket
id|nr
)braket
suffix:semicolon
id|rev.nr
op_assign
id|total
id|nr
op_plus
(paren
id|start_number
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_stdout
)paren
id|reopen_stdout
c_func
(paren
id|commit
comma
id|rev.nr
comma
id|keep_subject
)paren
suffix:semicolon
id|shown
op_assign
id|log_tree_commit
c_func
(paren
op_amp
id|rev
comma
id|commit
)paren
suffix:semicolon
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
multiline_comment|/* We put one extra blank line between formatted&n;&t;&t; * patches and this flag is used by log-tree code&n;&t;&t; * to see if it needs to emit a LF before showing&n;&t;&t; * the log; when using one file per patch, we do&n;&t;&t; * not want the extra blank line.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|use_stdout
)paren
id|rev.shown_one
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|shown
)paren
(brace
r_if
c_cond
(paren
id|rev.mime_boundary
)paren
id|printf
c_func
(paren
l_string|&quot;&bslash;n--%s%s--&bslash;n&bslash;n&bslash;n&quot;
comma
id|mime_boundary_leader
comma
id|rev.mime_boundary
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;-- &bslash;n%s&bslash;n&bslash;n&quot;
comma
id|git_version_string
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|use_stdout
)paren
id|fclose
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
