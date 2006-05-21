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
DECL|function|cmd_log_wc
r_static
r_int
id|cmd_log_wc
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
r_struct
id|commit
op_star
id|commit
suffix:semicolon
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
id|rev-&gt;always_show_header
)paren
(brace
r_if
c_cond
(paren
id|rev-&gt;diffopt.pickaxe
op_logical_or
id|rev-&gt;diffopt.filter
)paren
(brace
id|rev-&gt;always_show_header
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rev-&gt;diffopt.output_format
op_eq
id|DIFF_FORMAT_RAW
)paren
id|rev-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
)brace
)brace
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
r_return
id|cmd_log_wc
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
r_return
id|cmd_log_wc
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
id|rev.diffopt.recursive
op_assign
l_int|1
suffix:semicolon
r_return
id|cmd_log_wc
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
id|strncpy
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
id|keep_subject
op_assign
l_int|0
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
id|rev.diffopt.with_raw
op_assign
l_int|0
suffix:semicolon
id|rev.diffopt.with_stat
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
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_PATCH
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
l_string|&quot;-o&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
id|die
(paren
l_string|&quot;Which directory?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
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
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|output_directory
op_assign
id|strdup
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
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
id|numbered
op_logical_and
id|keep_subject
OL
l_int|0
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
id|rev.pending_objects
op_logical_and
id|rev.pending_objects-&gt;next
op_eq
l_int|NULL
)paren
(brace
id|rev.pending_objects-&gt;item-&gt;flags
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
r_if
c_cond
(paren
id|shown
)paren
id|printf
c_func
(paren
l_string|&quot;-- &bslash;n%s&bslash;n&bslash;n&quot;
comma
id|git_version_string
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|output_directory
)paren
id|free
c_func
(paren
id|output_directory
)paren
suffix:semicolon
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
