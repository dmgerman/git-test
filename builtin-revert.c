macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;wt-status.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
multiline_comment|/*&n; * This implements the builtins revert and cherry-pick.&n; *&n; * Copyright (c) 2007 Johannes E. Schindelin&n; *&n; * Based on git-revert.sh, which is&n; *&n; * Copyright (c) 2005 Linus Torvalds&n; * Copyright (c) 2005 Junio C Hamano&n; */
DECL|variable|revert_usage
r_static
r_const
r_char
op_star
r_const
id|revert_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git revert [options] &lt;commit-ish&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|cherry_pick_usage
r_static
r_const
r_char
op_star
r_const
id|cherry_pick_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git cherry-pick [options] &lt;commit-ish&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|edit
DECL|variable|no_replay
DECL|variable|no_commit
DECL|variable|mainline
DECL|variable|signoff
r_static
r_int
id|edit
comma
id|no_replay
comma
id|no_commit
comma
id|mainline
comma
id|signoff
suffix:semicolon
DECL|enumerator|REVERT
DECL|enumerator|CHERRY_PICK
DECL|variable|action
r_static
r_enum
(brace
id|REVERT
comma
id|CHERRY_PICK
)brace
id|action
suffix:semicolon
DECL|variable|commit
r_static
r_struct
id|commit
op_star
id|commit
suffix:semicolon
DECL|variable|me
r_static
r_const
r_char
op_star
id|me
suffix:semicolon
DECL|macro|GIT_REFLOG_ACTION
mdefine_line|#define GIT_REFLOG_ACTION &quot;GIT_REFLOG_ACTION&quot;
DECL|function|parse_args
r_static
r_void
id|parse_args
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
)paren
(brace
r_const
r_char
op_star
r_const
op_star
id|usage_str
op_assign
id|action
op_eq
id|REVERT
ques
c_cond
id|revert_usage
suffix:colon
id|cherry_pick_usage
suffix:semicolon
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
id|arg
suffix:semicolon
r_int
id|noop
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;n&squot;
comma
l_string|&quot;no-commit&quot;
comma
op_amp
id|no_commit
comma
l_string|&quot;don&squot;t automatically commit&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;e&squot;
comma
l_string|&quot;edit&quot;
comma
op_amp
id|edit
comma
l_string|&quot;edit the commit message&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;x&squot;
comma
l_int|NULL
comma
op_amp
id|no_replay
comma
l_string|&quot;append commit name when cherry-picking&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|NULL
comma
op_amp
id|noop
comma
l_string|&quot;no-op (backward compatibility)&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;s&squot;
comma
l_string|&quot;signoff&quot;
comma
op_amp
id|signoff
comma
l_string|&quot;add Signed-off-by:&quot;
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_char|&squot;m&squot;
comma
l_string|&quot;mainline&quot;
comma
op_amp
id|mainline
comma
l_string|&quot;parent number&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|options
comma
id|usage_str
comma
l_int|0
)paren
op_ne
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|usage_str
comma
id|options
)paren
suffix:semicolon
id|arg
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
)paren
id|die
(paren
l_string|&quot;Cannot find &squot;%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
id|die
(paren
l_string|&quot;Could not find %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.type
op_eq
id|OBJ_TAG
)paren
(brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|deref_tag
c_func
(paren
(paren
r_struct
id|object
op_star
)paren
id|commit
comma
id|arg
comma
id|strlen
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|commit-&gt;object.type
op_ne
id|OBJ_COMMIT
)paren
id|die
(paren
l_string|&quot;&squot;%s&squot; does not point to a commit&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|get_oneline
r_static
r_char
op_star
id|get_oneline
c_func
(paren
r_const
r_char
op_star
id|message
)paren
(brace
r_char
op_star
id|result
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
id|message
comma
op_star
id|abbrev
comma
op_star
id|eol
suffix:semicolon
r_int
id|abbrev_len
comma
id|oneline_len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|die
(paren
l_string|&quot;Could not read commit message of %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_or
id|p
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
)paren
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|p
op_add_assign
l_int|2
suffix:semicolon
r_for
c_loop
(paren
id|eol
op_assign
id|p
op_plus
l_int|1
suffix:semicolon
op_star
id|eol
op_logical_and
op_star
id|eol
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|eol
op_increment
)paren
suffix:semicolon
multiline_comment|/* do nothing */
)brace
r_else
id|eol
op_assign
id|p
suffix:semicolon
id|abbrev
op_assign
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|DEFAULT_ABBREV
)paren
suffix:semicolon
id|abbrev_len
op_assign
id|strlen
c_func
(paren
id|abbrev
)paren
suffix:semicolon
id|oneline_len
op_assign
id|eol
id|p
suffix:semicolon
id|result
op_assign
id|xmalloc
c_func
(paren
id|abbrev_len
op_plus
l_int|5
op_plus
id|oneline_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
comma
id|abbrev
comma
id|abbrev_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
op_plus
id|abbrev_len
comma
l_string|&quot;... &quot;
comma
l_int|4
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|result
op_plus
id|abbrev_len
op_plus
l_int|4
comma
id|p
comma
id|oneline_len
)paren
suffix:semicolon
id|result
(braket
id|abbrev_len
op_plus
l_int|4
op_plus
id|oneline_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|get_encoding
r_static
r_char
op_star
id|get_encoding
c_func
(paren
r_const
r_char
op_star
id|message
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|message
comma
op_star
id|eol
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|die
(paren
l_string|&quot;Could not read commit message of %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_logical_and
op_star
id|p
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_for
c_loop
(paren
id|eol
op_assign
id|p
op_plus
l_int|1
suffix:semicolon
op_star
id|eol
op_logical_and
op_star
id|eol
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|eol
op_increment
)paren
suffix:semicolon
multiline_comment|/* do nothing */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|p
comma
l_string|&quot;encoding &quot;
)paren
)paren
(brace
r_char
op_star
id|result
op_assign
id|xmalloc
c_func
(paren
id|eol
l_int|8
id|p
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|result
comma
id|p
op_plus
l_int|9
comma
id|eol
l_int|8
id|p
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|p
op_assign
id|eol
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|p
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|msg_file
r_static
r_struct
id|lock_file
id|msg_file
suffix:semicolon
DECL|variable|msg_fd
r_static
r_int
id|msg_fd
suffix:semicolon
DECL|function|add_to_msg
r_static
r_void
id|add_to_msg
c_func
(paren
r_const
r_char
op_star
id|string
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|msg_fd
comma
id|string
comma
id|len
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;Could not write to MERGE_MSG&quot;
)paren
suffix:semicolon
)brace
DECL|function|add_message_to_msg
r_static
r_void
id|add_message_to_msg
c_func
(paren
r_const
r_char
op_star
id|message
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|message
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_or
id|p
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
)paren
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
id|add_to_msg
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
id|add_to_msg
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|set_author_ident_env
r_static
r_void
id|set_author_ident_env
c_func
(paren
r_const
r_char
op_star
id|message
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|message
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|die
(paren
l_string|&quot;Could not read commit message of %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_logical_and
op_star
id|p
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_const
r_char
op_star
id|eol
suffix:semicolon
r_for
c_loop
(paren
id|eol
op_assign
id|p
suffix:semicolon
op_star
id|eol
op_logical_and
op_star
id|eol
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|eol
op_increment
)paren
suffix:semicolon
multiline_comment|/* do nothing */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|p
comma
l_string|&quot;author &quot;
)paren
)paren
(brace
r_char
op_star
id|line
comma
op_star
id|pend
comma
op_star
id|email
comma
op_star
id|timestamp
suffix:semicolon
id|p
op_add_assign
l_int|7
suffix:semicolon
id|line
op_assign
id|xmemdupz
c_func
(paren
id|p
comma
id|eol
id|p
)paren
suffix:semicolon
id|email
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|email
)paren
id|die
(paren
l_string|&quot;Could not extract author email from %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|email
op_eq
id|line
)paren
id|pend
op_assign
id|line
suffix:semicolon
r_else
r_for
c_loop
(paren
id|pend
op_assign
id|email
suffix:semicolon
id|pend
op_ne
id|line
op_plus
l_int|1
op_logical_and
id|isspace
c_func
(paren
id|pend
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pend
op_decrement
)paren
suffix:semicolon
suffix:semicolon
multiline_comment|/* do nothing */
op_star
id|pend
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|email
op_increment
suffix:semicolon
id|timestamp
op_assign
id|strchr
c_func
(paren
id|email
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timestamp
)paren
id|die
(paren
l_string|&quot;Could not extract author time from %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
op_star
id|timestamp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|timestamp
op_increment
suffix:semicolon
op_star
id|timestamp
op_logical_and
id|isspace
c_func
(paren
op_star
id|timestamp
)paren
suffix:semicolon
id|timestamp
op_increment
)paren
suffix:semicolon
multiline_comment|/* do nothing */
id|setenv
c_func
(paren
l_string|&quot;GIT_AUTHOR_NAME&quot;
comma
id|line
comma
l_int|1
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;GIT_AUTHOR_EMAIL&quot;
comma
id|email
comma
l_int|1
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;GIT_AUTHOR_DATE&quot;
comma
id|timestamp
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|line
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
id|eol
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|p
op_increment
suffix:semicolon
)brace
id|die
(paren
l_string|&quot;No author information found in %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|merge_recursive
r_static
r_int
id|merge_recursive
c_func
(paren
r_const
r_char
op_star
id|base_sha1
comma
r_const
r_char
op_star
id|head_sha1
comma
r_const
r_char
op_star
id|head_name
comma
r_const
r_char
op_star
id|next_sha1
comma
r_const
r_char
op_star
id|next_name
)paren
(brace
r_char
id|buffer
(braket
l_int|256
)braket
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;GITHEAD_%s&quot;
comma
id|head_sha1
)paren
suffix:semicolon
id|setenv
c_func
(paren
id|buffer
comma
id|head_name
comma
l_int|1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;GITHEAD_%s&quot;
comma
id|next_sha1
)paren
suffix:semicolon
id|setenv
c_func
(paren
id|buffer
comma
id|next_name
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This three way merge is an interesting one.  We are at&n;&t; * $head, and would want to apply the change between $commit&n;&t; * and $prev on top of us (when reverting), or the change between&n;&t; * $prev and $commit on top of us (when cherry-picking or replaying).&n;&t; */
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;merge-recursive&quot;
suffix:semicolon
r_if
c_cond
(paren
id|base_sha1
)paren
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|base_sha1
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;--&quot;
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|head_sha1
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|next_sha1
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|run_command_v_opt
c_func
(paren
id|argv
comma
id|RUN_COMMAND_NO_STDIN
op_or
id|RUN_GIT_CMD
)paren
suffix:semicolon
)brace
DECL|function|help_msg
r_static
r_char
op_star
id|help_msg
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_char
id|helpbuf
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|msg
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_CHERRY_PICK_HELP&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
r_return
id|msg
suffix:semicolon
id|strcpy
c_func
(paren
id|helpbuf
comma
l_string|&quot;  After resolving the conflicts,&bslash;n&quot;
l_string|&quot;mark the corrected paths with &squot;git add &lt;paths&gt;&squot; &quot;
l_string|&quot;or &squot;git rm &lt;paths&gt;&squot; and commit the result.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|CHERRY_PICK
)paren
(brace
id|sprintf
c_func
(paren
id|helpbuf
op_plus
id|strlen
c_func
(paren
id|helpbuf
)paren
comma
l_string|&quot;&bslash;nWhen commiting, use the option &quot;
l_string|&quot;&squot;-c %s&squot; to retain authorship and message.&quot;
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
)brace
r_return
id|helpbuf
suffix:semicolon
)brace
DECL|function|index_is_dirty
r_static
r_int
id|index_is_dirty
c_func
(paren
r_void
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
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|QUIET
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|EXIT_WITH_STATUS
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
r_return
op_logical_neg
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|rev.diffopt
comma
id|HAS_CHANGES
)paren
suffix:semicolon
)brace
DECL|function|revert_or_cherry_pick
r_static
r_int
id|revert_or_cherry_pick
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
)paren
(brace
r_int
r_char
id|head
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|base
comma
op_star
id|next
comma
op_star
id|parent
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|oneline
comma
op_star
id|reencoded_message
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|message
comma
op_star
id|encoding
suffix:semicolon
r_char
op_star
id|defmsg
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;MERGE_MSG&quot;
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|me
op_assign
id|action
op_eq
id|REVERT
ques
c_cond
l_string|&quot;revert&quot;
suffix:colon
l_string|&quot;cherry-pick&quot;
suffix:semicolon
id|setenv
c_func
(paren
id|GIT_REFLOG_ACTION
comma
id|me
comma
l_int|0
)paren
suffix:semicolon
id|parse_args
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
multiline_comment|/* this is copied from the shell script, but it&squot;s never triggered... */
r_if
c_cond
(paren
id|action
op_eq
id|REVERT
op_logical_and
op_logical_neg
id|no_replay
)paren
id|die
c_func
(paren
l_string|&quot;revert is incompatible with replay&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_commit
)paren
(brace
multiline_comment|/*&n;&t;&t; * We do not intend to commit immediately.  We just want to&n;&t;&t; * merge the differences in, so let&squot;s compute the tree&n;&t;&t; * that represents the &quot;current&quot; state for merge-recursive&n;&t;&t; * to work on.&n;&t;&t; */
r_if
c_cond
(paren
id|write_cache_as_tree
c_func
(paren
id|head
comma
l_int|0
comma
l_int|NULL
)paren
)paren
id|die
(paren
l_string|&quot;Your index file is unmerged.&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head
)paren
)paren
id|die
(paren
l_string|&quot;You do not have a valid HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;could not read the index&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index_is_dirty
c_func
(paren
)paren
)paren
id|die
(paren
l_string|&quot;Dirty index: cannot %s&quot;
comma
id|me
)paren
suffix:semicolon
id|discard_cache
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;parents
)paren
(brace
r_if
c_cond
(paren
id|action
op_eq
id|REVERT
)paren
id|die
(paren
l_string|&quot;Cannot revert a root commit&quot;
)paren
suffix:semicolon
id|parent
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|commit-&gt;parents-&gt;next
)paren
(brace
multiline_comment|/* Reverting or cherry-picking a merge commit */
r_int
id|cnt
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mainline
)paren
id|die
c_func
(paren
l_string|&quot;Commit %s is a merge but no -m option was given.&quot;
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
id|cnt
op_assign
l_int|1
comma
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|cnt
op_ne
id|mainline
op_logical_and
id|p
suffix:semicolon
id|cnt
op_increment
)paren
id|p
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_ne
id|mainline
op_logical_or
op_logical_neg
id|p
)paren
id|die
c_func
(paren
l_string|&quot;Commit %s does not have parent %d&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
id|mainline
)paren
suffix:semicolon
id|parent
op_assign
id|p-&gt;item
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
l_int|0
OL
id|mainline
)paren
id|die
c_func
(paren
l_string|&quot;Mainline was specified but commit %s is not a merge.&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_else
id|parent
op_assign
id|commit-&gt;parents-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|message
op_assign
id|commit-&gt;buffer
)paren
)paren
id|die
(paren
l_string|&quot;Cannot get commit message for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;commit&quot; is an existing commit.  We would want to apply&n;&t; * the difference it introduces since its first parent &quot;prev&quot;&n;&t; * on top of the current HEAD if we are cherry-pick.  Or the&n;&t; * reverse of it if we are revert.&n;&t; */
id|msg_fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|msg_file
comma
id|defmsg
comma
id|LOCK_DIE_ON_ERROR
)paren
suffix:semicolon
id|encoding
op_assign
id|get_encoding
c_func
(paren
id|message
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|encoding
)paren
id|encoding
op_assign
l_string|&quot;utf-8&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_commit_encoding
)paren
id|git_commit_encoding
op_assign
l_string|&quot;utf-8&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reencoded_message
op_assign
id|reencode_string
c_func
(paren
id|message
comma
id|git_commit_encoding
comma
id|encoding
)paren
)paren
)paren
id|message
op_assign
id|reencoded_message
suffix:semicolon
id|oneline
op_assign
id|get_oneline
c_func
(paren
id|message
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|REVERT
)paren
(brace
r_char
op_star
id|oneline_body
op_assign
id|strchr
c_func
(paren
id|oneline
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|base
op_assign
id|commit
suffix:semicolon
id|next
op_assign
id|parent
suffix:semicolon
id|add_to_msg
c_func
(paren
l_string|&quot;Revert &bslash;&quot;&quot;
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
id|oneline_body
op_plus
l_int|1
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
l_string|&quot;&bslash;&quot;&bslash;n&bslash;nThis reverts commit &quot;
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|base
op_assign
id|parent
suffix:semicolon
id|next
op_assign
id|commit
suffix:semicolon
id|set_author_ident_env
c_func
(paren
id|message
)paren
suffix:semicolon
id|add_message_to_msg
c_func
(paren
id|message
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_replay
)paren
(brace
id|add_to_msg
c_func
(paren
l_string|&quot;(cherry picked from commit &quot;
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|merge_recursive
c_func
(paren
id|base
op_eq
l_int|NULL
ques
c_cond
l_int|NULL
suffix:colon
id|sha1_to_hex
c_func
(paren
id|base-&gt;object.sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|head
)paren
comma
l_string|&quot;HEAD&quot;
comma
id|sha1_to_hex
c_func
(paren
id|next-&gt;object.sha1
)paren
comma
id|oneline
)paren
op_logical_or
id|write_cache_as_tree
c_func
(paren
id|head
comma
l_int|0
comma
l_int|NULL
)paren
)paren
(brace
id|add_to_msg
c_func
(paren
l_string|&quot;&bslash;nConflicts:&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|read_cache
c_func
(paren
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
id|active_nr
suffix:semicolon
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
op_increment
)braket
suffix:semicolon
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
id|add_to_msg
c_func
(paren
l_string|&quot;&bslash;t&quot;
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
id|add_to_msg
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|active_nr
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
id|i
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|commit_lock_file
c_func
(paren
op_amp
id|msg_file
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;Error wrapping up %s&quot;
comma
id|defmsg
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Automatic %s failed.%s&bslash;n&quot;
comma
id|me
comma
id|help_msg
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|commit_lock_file
c_func
(paren
op_amp
id|msg_file
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;Error wrapping up %s&quot;
comma
id|defmsg
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Finished one %s.&bslash;n&quot;
comma
id|me
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&n;&t; * If we are cherry-pick, and if the merge did not result in&n;&t; * hand-editing, we will hit this commit and inherit the original&n;&t; * author date and name.&n;&t; * If we are revert, or if our cherry-pick results in a hand merge,&n;&t; * we had better say that the current user is responsible for that.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|no_commit
)paren
(brace
multiline_comment|/* 6 is max possible length of our args array including NULL */
r_const
r_char
op_star
id|args
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;commit&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;-n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|signoff
)paren
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;-s&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|edit
)paren
(brace
id|args
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;-F&quot;
suffix:semicolon
id|args
(braket
id|i
op_increment
)braket
op_assign
id|defmsg
suffix:semicolon
)brace
id|args
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|execv_git_cmd
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|reencoded_message
)paren
suffix:semicolon
id|free
c_func
(paren
id|defmsg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_revert
r_int
id|cmd_revert
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
r_if
c_cond
(paren
id|isatty
c_func
(paren
l_int|0
)paren
)paren
id|edit
op_assign
l_int|1
suffix:semicolon
id|no_replay
op_assign
l_int|1
suffix:semicolon
id|action
op_assign
id|REVERT
suffix:semicolon
r_return
id|revert_or_cherry_pick
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
DECL|function|cmd_cherry_pick
r_int
id|cmd_cherry_pick
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
id|no_replay
op_assign
l_int|0
suffix:semicolon
id|action
op_assign
id|CHERRY_PICK
suffix:semicolon
r_return
id|revert_or_cherry_pick
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
eof
