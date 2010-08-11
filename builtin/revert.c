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
macro_line|#include &quot;rerere.h&quot;
macro_line|#include &quot;merge-recursive.h&quot;
macro_line|#include &quot;refs.h&quot;
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
DECL|variable|allow_ff
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
comma
id|allow_ff
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
DECL|variable|commit_argc
r_static
r_int
id|commit_argc
suffix:semicolon
DECL|variable|commit_argv
r_static
r_const
r_char
op_star
op_star
id|commit_argv
suffix:semicolon
DECL|variable|allow_rerere_auto
r_static
r_int
id|allow_rerere_auto
suffix:semicolon
DECL|variable|me
r_static
r_const
r_char
op_star
id|me
suffix:semicolon
DECL|variable|strategy
r_static
r_const
r_char
op_star
id|strategy
suffix:semicolon
DECL|macro|GIT_REFLOG_ACTION
mdefine_line|#define GIT_REFLOG_ACTION &quot;GIT_REFLOG_ACTION&quot;
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
suffix:semicolon
DECL|function|revert_or_cherry_pick_usage
r_static
r_const
r_char
op_star
r_const
op_star
id|revert_or_cherry_pick_usage
c_func
(paren
r_void
)paren
(brace
r_return
id|action
op_eq
id|REVERT
ques
c_cond
id|revert_usage
suffix:colon
id|cherry_pick_usage
suffix:semicolon
)brace
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
id|revert_or_cherry_pick_usage
c_func
(paren
)paren
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
id|OPT_RERERE_AUTOUPDATE
c_func
(paren
op_amp
id|allow_rerere_auto
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;strategy&quot;
comma
op_amp
id|strategy
comma
l_string|&quot;strategy&quot;
comma
l_string|&quot;merge strategy&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
id|OPT_END
c_func
(paren
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
id|action
op_eq
id|CHERRY_PICK
)paren
(brace
r_struct
id|option
id|cp_extra
(braket
)braket
op_assign
(brace
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
l_string|&quot;append commit name&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;ff&quot;
comma
op_amp
id|allow_ff
comma
l_string|&quot;allow fast-forward&quot;
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
id|parse_options_concat
c_func
(paren
id|options
comma
id|ARRAY_SIZE
c_func
(paren
id|options
)paren
comma
id|cp_extra
)paren
)paren
id|die
c_func
(paren
l_string|&quot;program error&quot;
)paren
suffix:semicolon
)brace
id|commit_argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
l_int|NULL
comma
id|options
comma
id|usage_str
comma
id|PARSE_OPT_KEEP_ARGV0
op_or
id|PARSE_OPT_KEEP_UNKNOWN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_argc
OL
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|usage_str
comma
id|options
)paren
suffix:semicolon
id|commit_argv
op_assign
id|argv
suffix:semicolon
)brace
DECL|struct|commit_message
r_struct
id|commit_message
(brace
DECL|member|parent_label
r_char
op_star
id|parent_label
suffix:semicolon
DECL|member|label
r_const
r_char
op_star
id|label
suffix:semicolon
DECL|member|subject
r_const
r_char
op_star
id|subject
suffix:semicolon
DECL|member|reencoded_message
r_char
op_star
id|reencoded_message
suffix:semicolon
DECL|member|message
r_const
r_char
op_star
id|message
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_message
r_static
r_int
id|get_message
c_func
(paren
r_const
r_char
op_star
id|raw_message
comma
r_struct
id|commit_message
op_star
id|out
)paren
(brace
r_const
r_char
op_star
id|encoding
suffix:semicolon
r_const
r_char
op_star
id|p
comma
op_star
id|abbrev
comma
op_star
id|eol
suffix:semicolon
r_char
op_star
id|q
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
id|raw_message
)paren
r_return
l_int|1
suffix:semicolon
id|encoding
op_assign
id|get_encoding
c_func
(paren
id|raw_message
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
l_string|&quot;UTF-8&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_commit_encoding
)paren
id|git_commit_encoding
op_assign
l_string|&quot;UTF-8&quot;
suffix:semicolon
id|out-&gt;reencoded_message
op_assign
l_int|NULL
suffix:semicolon
id|out-&gt;message
op_assign
id|raw_message
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|encoding
comma
id|git_commit_encoding
)paren
)paren
id|out-&gt;reencoded_message
op_assign
id|reencode_string
c_func
(paren
id|raw_message
comma
id|git_commit_encoding
comma
id|encoding
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out-&gt;reencoded_message
)paren
id|out-&gt;message
op_assign
id|out-&gt;reencoded_message
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
multiline_comment|/* Find beginning and end of commit subject. */
id|p
op_assign
id|out-&gt;message
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
id|oneline_len
op_assign
id|eol
id|p
suffix:semicolon
id|out-&gt;parent_label
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
l_string|&quot;parent of &quot;
)paren
op_plus
id|abbrev_len
op_plus
id|strlen
c_func
(paren
l_string|&quot;... &quot;
)paren
op_plus
id|oneline_len
op_plus
l_int|1
)paren
suffix:semicolon
id|q
op_assign
id|out-&gt;parent_label
suffix:semicolon
id|q
op_assign
id|mempcpy
c_func
(paren
id|q
comma
l_string|&quot;parent of &quot;
comma
id|strlen
c_func
(paren
l_string|&quot;parent of &quot;
)paren
)paren
suffix:semicolon
id|out-&gt;label
op_assign
id|q
suffix:semicolon
id|q
op_assign
id|mempcpy
c_func
(paren
id|q
comma
id|abbrev
comma
id|abbrev_len
)paren
suffix:semicolon
id|q
op_assign
id|mempcpy
c_func
(paren
id|q
comma
l_string|&quot;... &quot;
comma
id|strlen
c_func
(paren
l_string|&quot;... &quot;
)paren
)paren
suffix:semicolon
id|out-&gt;subject
op_assign
id|q
suffix:semicolon
id|q
op_assign
id|mempcpy
c_func
(paren
id|q
comma
id|p
comma
id|oneline_len
)paren
suffix:semicolon
op_star
id|q
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_message
r_static
r_void
id|free_message
c_func
(paren
r_struct
id|commit_message
op_star
id|msg
)paren
(brace
id|free
c_func
(paren
id|msg-&gt;parent_label
)paren
suffix:semicolon
id|free
c_func
(paren
id|msg-&gt;reencoded_message
)paren
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
DECL|function|add_message_to_msg
r_static
r_void
id|add_message_to_msg
c_func
(paren
r_struct
id|strbuf
op_star
id|msgbuf
comma
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
id|strbuf_addstr
c_func
(paren
id|msgbuf
comma
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
id|strbuf_addstr
c_func
(paren
id|msgbuf
comma
id|p
)paren
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
DECL|function|advise
r_static
r_void
id|advise
c_func
(paren
r_const
r_char
op_star
id|advice
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|advice
)paren
suffix:semicolon
id|vreportf
c_func
(paren
l_string|&quot;hint: &quot;
comma
id|advice
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
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
r_void
)paren
(brace
r_struct
id|strbuf
id|helpbuf
op_assign
id|STRBUF_INIT
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
id|strbuf_addstr
c_func
(paren
op_amp
id|helpbuf
comma
l_string|&quot;  After resolving the conflicts,&bslash;n&quot;
l_string|&quot;mark the corrected paths with &squot;git add &lt;paths&gt;&squot; or &squot;git rm &lt;paths&gt;&squot;&bslash;n&quot;
l_string|&quot;and commit the result&quot;
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
id|strbuf_addf
c_func
(paren
op_amp
id|helpbuf
comma
l_string|&quot; with: &bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;        git commit -c %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
r_else
id|strbuf_addch
c_func
(paren
op_amp
id|helpbuf
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|helpbuf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|write_message
r_static
r_void
id|write_message
c_func
(paren
r_struct
id|strbuf
op_star
id|msgbuf
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_static
r_struct
id|lock_file
id|msg_file
suffix:semicolon
r_int
id|msg_fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|msg_file
comma
id|filename
comma
id|LOCK_DIE_ON_ERROR
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
id|msgbuf-&gt;buf
comma
id|msgbuf-&gt;len
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Could not write to %s.&quot;
comma
id|filename
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
id|msgbuf
)paren
suffix:semicolon
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
c_func
(paren
l_string|&quot;Error wrapping up %s&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
DECL|function|empty_tree
r_static
r_struct
id|tree
op_star
id|empty_tree
c_func
(paren
r_void
)paren
(brace
r_struct
id|tree
op_star
id|tree
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|tree
)paren
)paren
suffix:semicolon
id|tree-&gt;object.parsed
op_assign
l_int|1
suffix:semicolon
id|tree-&gt;object.type
op_assign
id|OBJ_TREE
suffix:semicolon
id|pretend_sha1_file
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|OBJ_TREE
comma
id|tree-&gt;object.sha1
)paren
suffix:semicolon
r_return
id|tree
suffix:semicolon
)brace
DECL|function|die_dirty_index
r_static
id|NORETURN
r_void
id|die_dirty_index
c_func
(paren
r_const
r_char
op_star
id|me
)paren
(brace
r_if
c_cond
(paren
id|read_cache_unmerged
c_func
(paren
)paren
)paren
(brace
id|die_resolve_conflict
c_func
(paren
id|me
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|advice_commit_before_merge
)paren
id|die
c_func
(paren
l_string|&quot;Your local changes would be overwritten by %s.&bslash;n&quot;
l_string|&quot;Please, commit your changes or stash them to proceed.&quot;
comma
id|me
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;Your local changes would be overwritten by %s.&bslash;n&quot;
comma
id|me
)paren
suffix:semicolon
)brace
)brace
DECL|function|fast_forward_to
r_static
r_int
id|fast_forward_to
c_func
(paren
r_const
r_int
r_char
op_star
id|to
comma
r_const
r_int
r_char
op_star
id|from
)paren
(brace
r_struct
id|ref_lock
op_star
id|ref_lock
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|checkout_fast_forward
c_func
(paren
id|from
comma
id|to
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* the callee should have complained already */
id|ref_lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|from
comma
l_int|0
)paren
suffix:semicolon
r_return
id|write_ref_sha1
c_func
(paren
id|ref_lock
comma
id|to
comma
l_string|&quot;cherry-pick&quot;
)paren
suffix:semicolon
)brace
DECL|function|do_recursive_merge
r_static
r_int
id|do_recursive_merge
c_func
(paren
r_struct
id|commit
op_star
id|base
comma
r_struct
id|commit
op_star
id|next
comma
r_const
r_char
op_star
id|base_label
comma
r_const
r_char
op_star
id|next_label
comma
r_int
r_char
op_star
id|head
comma
r_struct
id|strbuf
op_star
id|msgbuf
)paren
(brace
r_struct
id|merge_options
id|o
suffix:semicolon
r_struct
id|tree
op_star
id|result
comma
op_star
id|next_tree
comma
op_star
id|base_tree
comma
op_star
id|head_tree
suffix:semicolon
r_int
id|clean
comma
id|index_fd
suffix:semicolon
r_static
r_struct
id|lock_file
id|index_lock
suffix:semicolon
id|index_fd
op_assign
id|hold_locked_index
c_func
(paren
op_amp
id|index_lock
comma
l_int|1
)paren
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
id|init_merge_options
c_func
(paren
op_amp
id|o
)paren
suffix:semicolon
id|o.ancestor
op_assign
id|base
ques
c_cond
id|base_label
suffix:colon
l_string|&quot;(empty tree)&quot;
suffix:semicolon
id|o.branch1
op_assign
l_string|&quot;HEAD&quot;
suffix:semicolon
id|o.branch2
op_assign
id|next
ques
c_cond
id|next_label
suffix:colon
l_string|&quot;(empty tree)&quot;
suffix:semicolon
id|head_tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|head
)paren
suffix:semicolon
id|next_tree
op_assign
id|next
ques
c_cond
id|next-&gt;tree
suffix:colon
id|empty_tree
c_func
(paren
)paren
suffix:semicolon
id|base_tree
op_assign
id|base
ques
c_cond
id|base-&gt;tree
suffix:colon
id|empty_tree
c_func
(paren
)paren
suffix:semicolon
id|clean
op_assign
id|merge_trees
c_func
(paren
op_amp
id|o
comma
id|head_tree
comma
id|next_tree
comma
id|base_tree
comma
op_amp
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_cache_changed
op_logical_and
(paren
id|write_cache
c_func
(paren
id|index_fd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
op_amp
id|index_lock
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s: Unable to write new index file&quot;
comma
id|me
)paren
suffix:semicolon
id|rollback_lock_file
c_func
(paren
op_amp
id|index_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clean
)paren
(brace
r_int
id|i
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|msgbuf
comma
l_string|&quot;&bslash;nConflicts:&bslash;n&bslash;n&quot;
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
id|strbuf_addch
c_func
(paren
id|msgbuf
comma
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|msgbuf
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|msgbuf
comma
l_char|&squot;&bslash;n&squot;
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
)brace
r_return
op_logical_neg
id|clean
suffix:semicolon
)brace
multiline_comment|/*&n; * If we are cherry-pick, and if the merge did not result in&n; * hand-editing, we will hit this commit and inherit the original&n; * author date and name.&n; * If we are revert, or if our cherry-pick results in a hand merge,&n; * we had better say that the current user is responsible for that.&n; */
DECL|function|run_git_commit
r_static
r_int
id|run_git_commit
c_func
(paren
r_const
r_char
op_star
id|defmsg
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
id|run_command_v_opt
c_func
(paren
id|args
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
)brace
DECL|function|do_pick_commit
r_static
r_int
id|do_pick_commit
c_func
(paren
r_void
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
r_const
r_char
op_star
id|base_label
comma
op_star
id|next_label
suffix:semicolon
r_struct
id|commit_message
id|msg
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
id|defmsg
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|strbuf
id|msgbuf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|mebuf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|res
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
id|index_differs_from
c_func
(paren
l_string|&quot;HEAD&quot;
comma
l_int|0
)paren
)paren
id|die_dirty_index
c_func
(paren
id|me
)paren
suffix:semicolon
)brace
id|discard_cache
c_func
(paren
)paren
suffix:semicolon
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
id|allow_ff
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|parent-&gt;object.sha1
comma
id|head
)paren
)paren
r_return
id|fast_forward_to
c_func
(paren
id|commit-&gt;object.sha1
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
op_logical_and
id|parse_commit
c_func
(paren
id|parent
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: cannot parse parent commit %s&quot;
comma
id|me
comma
id|sha1_to_hex
c_func
(paren
id|parent-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_message
c_func
(paren
id|commit-&gt;buffer
comma
op_amp
id|msg
)paren
op_ne
l_int|0
)paren
id|die
c_func
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
id|defmsg
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;MERGE_MSG&quot;
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
id|base
op_assign
id|commit
suffix:semicolon
id|base_label
op_assign
id|msg.label
suffix:semicolon
id|next
op_assign
id|parent
suffix:semicolon
id|next_label
op_assign
id|msg.parent_label
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
l_string|&quot;Revert &bslash;&quot;&quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
id|msg.subject
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
l_string|&quot;&bslash;&quot;&bslash;n&bslash;nThis reverts commit &quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
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
id|commit-&gt;parents-&gt;next
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
l_string|&quot;, reversing&bslash;nchanges made to &quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
id|sha1_to_hex
c_func
(paren
id|parent-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
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
id|base_label
op_assign
id|msg.parent_label
suffix:semicolon
id|next
op_assign
id|commit
suffix:semicolon
id|next_label
op_assign
id|msg.label
suffix:semicolon
id|set_author_ident_env
c_func
(paren
id|msg.message
)paren
suffix:semicolon
id|add_message_to_msg
c_func
(paren
op_amp
id|msgbuf
comma
id|msg.message
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_replay
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
l_string|&quot;(cherry picked from commit &quot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|msgbuf
comma
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|mebuf
comma
l_string|&quot;%s of commit %s&quot;
comma
id|me
comma
id|find_unique_abbrev
c_func
(paren
id|commit-&gt;object.sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strategy
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|strategy
comma
l_string|&quot;recursive&quot;
)paren
op_logical_or
id|action
op_eq
id|REVERT
)paren
(brace
id|res
op_assign
id|do_recursive_merge
c_func
(paren
id|base
comma
id|next
comma
id|base_label
comma
id|next_label
comma
id|head
comma
op_amp
id|msgbuf
)paren
suffix:semicolon
id|write_message
c_func
(paren
op_amp
id|msgbuf
comma
id|defmsg
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|commit_list
op_star
id|common
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|remotes
op_assign
l_int|NULL
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|mebuf
comma
l_string|&quot; with strategy %s&quot;
comma
id|strategy
)paren
suffix:semicolon
id|write_message
c_func
(paren
op_amp
id|msgbuf
comma
id|defmsg
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|base
comma
op_amp
id|common
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|next
comma
op_amp
id|remotes
)paren
suffix:semicolon
id|res
op_assign
id|try_merge_command
c_func
(paren
id|strategy
comma
id|common
comma
id|sha1_to_hex
c_func
(paren
id|head
)paren
comma
id|remotes
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|common
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|remotes
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Automatic %s failed.%s&bslash;n&quot;
comma
id|mebuf.buf
comma
id|help_msg
c_func
(paren
)paren
)paren
suffix:semicolon
id|rerere
c_func
(paren
id|allow_rerere_auto
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|no_commit
)paren
id|res
op_assign
id|run_git_commit
c_func
(paren
id|defmsg
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|mebuf
)paren
suffix:semicolon
id|free_message
c_func
(paren
op_amp
id|msg
)paren
suffix:semicolon
id|free
c_func
(paren
id|defmsg
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|prepare_revs
r_static
r_void
id|prepare_revs
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
)paren
(brace
r_int
id|argc
suffix:semicolon
id|init_revisions
c_func
(paren
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|revs-&gt;no_walk
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|action
op_ne
id|REVERT
)paren
id|revs-&gt;reverse
op_assign
l_int|1
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|commit_argc
comma
id|commit_argv
comma
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage
c_func
(paren
op_star
id|revert_or_cherry_pick_usage
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
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
op_logical_neg
id|revs-&gt;commits
)paren
id|die
c_func
(paren
l_string|&quot;empty commit set passed&quot;
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
r_struct
id|rev_info
id|revs
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
r_if
c_cond
(paren
id|allow_ff
)paren
(brace
r_if
c_cond
(paren
id|signoff
)paren
id|die
c_func
(paren
l_string|&quot;cherry-pick --ff cannot be used with --signoff&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_commit
)paren
id|die
c_func
(paren
l_string|&quot;cherry-pick --ff cannot be used with --no-commit&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_replay
)paren
id|die
c_func
(paren
l_string|&quot;cherry-pick --ff cannot be used with -x&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|edit
)paren
id|die
c_func
(paren
l_string|&quot;cherry-pick --ff cannot be used with --edit&quot;
)paren
suffix:semicolon
)brace
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
l_string|&quot;git %s: failed to read the index&quot;
comma
id|me
)paren
suffix:semicolon
id|prepare_revs
c_func
(paren
op_amp
id|revs
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
id|revs
)paren
)paren
)paren
(brace
r_int
id|res
op_assign
id|do_pick_commit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_return
id|res
suffix:semicolon
)brace
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
