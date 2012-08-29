macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;rerere.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;sequencer.h&quot;
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
l_string|&quot;git revert &lt;subcommand&gt;&quot;
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
l_string|&quot;git cherry-pick &lt;subcommand&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|action_name
r_static
r_const
r_char
op_star
id|action_name
c_func
(paren
r_const
r_struct
id|replay_opts
op_star
id|opts
)paren
(brace
r_return
id|opts-&gt;action
op_eq
id|REPLAY_REVERT
ques
c_cond
l_string|&quot;revert&quot;
suffix:colon
l_string|&quot;cherry-pick&quot;
suffix:semicolon
)brace
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
r_struct
id|replay_opts
op_star
id|opts
)paren
(brace
r_return
id|opts-&gt;action
op_eq
id|REPLAY_REVERT
ques
c_cond
id|revert_usage
suffix:colon
id|cherry_pick_usage
suffix:semicolon
)brace
DECL|function|option_parse_x
r_static
r_int
id|option_parse_x
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_struct
id|replay_opts
op_star
op_star
id|opts_ptr
op_assign
id|opt-&gt;value
suffix:semicolon
r_struct
id|replay_opts
op_star
id|opts
op_assign
op_star
id|opts_ptr
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
r_return
l_int|0
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|opts-&gt;xopts
comma
id|opts-&gt;xopts_nr
op_plus
l_int|1
comma
id|opts-&gt;xopts_alloc
)paren
suffix:semicolon
id|opts-&gt;xopts
(braket
id|opts-&gt;xopts_nr
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|verify_opt_compatible
r_static
r_void
id|verify_opt_compatible
c_func
(paren
r_const
r_char
op_star
id|me
comma
r_const
r_char
op_star
id|base_opt
comma
dot
dot
dot
)paren
(brace
r_const
r_char
op_star
id|this_opt
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|base_opt
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_opt
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_const
r_char
op_star
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|va_arg
c_func
(paren
id|ap
comma
r_int
)paren
)paren
r_break
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this_opt
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s: %s cannot be used with %s&quot;
)paren
comma
id|me
comma
id|this_opt
comma
id|base_opt
)paren
suffix:semicolon
)brace
DECL|function|verify_opt_mutually_compatible
r_static
r_void
id|verify_opt_mutually_compatible
c_func
(paren
r_const
r_char
op_star
id|me
comma
dot
dot
dot
)paren
(brace
r_const
r_char
op_star
id|opt1
comma
op_star
id|opt2
op_assign
l_int|NULL
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|me
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|opt1
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_const
r_char
op_star
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|va_arg
c_func
(paren
id|ap
comma
r_int
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt1
)paren
(brace
r_while
c_loop
(paren
(paren
id|opt2
op_assign
id|va_arg
c_func
(paren
id|ap
comma
r_const
r_char
op_star
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|va_arg
c_func
(paren
id|ap
comma
r_int
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt1
op_logical_and
id|opt2
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s: %s cannot be used with %s&quot;
)paren
comma
id|me
comma
id|opt1
comma
id|opt2
)paren
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
comma
r_struct
id|replay_opts
op_star
id|opts
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
id|opts
)paren
suffix:semicolon
r_const
r_char
op_star
id|me
op_assign
id|action_name
c_func
(paren
id|opts
)paren
suffix:semicolon
r_int
id|remove_state
op_assign
l_int|0
suffix:semicolon
r_int
id|contin
op_assign
l_int|0
suffix:semicolon
r_int
id|rollback
op_assign
l_int|0
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
l_int|0
comma
l_string|&quot;quit&quot;
comma
op_amp
id|remove_state
comma
l_string|&quot;end revert or cherry-pick sequence&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;continue&quot;
comma
op_amp
id|contin
comma
l_string|&quot;resume revert or cherry-pick sequence&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;abort&quot;
comma
op_amp
id|rollback
comma
l_string|&quot;cancel revert or cherry-pick sequence&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;n&squot;
comma
l_string|&quot;no-commit&quot;
comma
op_amp
id|opts-&gt;no_commit
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
id|opts-&gt;edit
comma
l_string|&quot;edit the commit message&quot;
)paren
comma
id|OPT_NOOP_NOARG
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|NULL
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
id|opts-&gt;signoff
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
id|opts-&gt;mainline
comma
l_string|&quot;parent number&quot;
)paren
comma
id|OPT_RERERE_AUTOUPDATE
c_func
(paren
op_amp
id|opts-&gt;allow_rerere_auto
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
id|opts-&gt;strategy
comma
l_string|&quot;strategy&quot;
comma
l_string|&quot;merge strategy&quot;
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_char|&squot;X&squot;
comma
l_string|&quot;strategy-option&quot;
comma
op_amp
id|opts
comma
l_string|&quot;option&quot;
comma
l_string|&quot;option for merge strategy&quot;
comma
id|option_parse_x
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
id|opts-&gt;action
op_eq
id|REPLAY_PICK
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
id|opts-&gt;record_origin
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
id|opts-&gt;allow_ff
comma
l_string|&quot;allow fast-forward&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;allow-empty&quot;
comma
op_amp
id|opts-&gt;allow_empty
comma
l_string|&quot;preserve initially empty commits&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;keep-redundant-commits&quot;
comma
op_amp
id|opts-&gt;keep_redundant_commits
comma
l_string|&quot;keep redundant, empty commits&quot;
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
id|_
c_func
(paren
l_string|&quot;program error&quot;
)paren
)paren
suffix:semicolon
)brace
id|argc
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
multiline_comment|/* Check for incompatible subcommands */
id|verify_opt_mutually_compatible
c_func
(paren
id|me
comma
l_string|&quot;--quit&quot;
comma
id|remove_state
comma
l_string|&quot;--continue&quot;
comma
id|contin
comma
l_string|&quot;--abort&quot;
comma
id|rollback
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* implies allow_empty */
r_if
c_cond
(paren
id|opts-&gt;keep_redundant_commits
)paren
id|opts-&gt;allow_empty
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Set the subcommand */
r_if
c_cond
(paren
id|remove_state
)paren
id|opts-&gt;subcommand
op_assign
id|REPLAY_REMOVE_STATE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|contin
)paren
id|opts-&gt;subcommand
op_assign
id|REPLAY_CONTINUE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rollback
)paren
id|opts-&gt;subcommand
op_assign
id|REPLAY_ROLLBACK
suffix:semicolon
r_else
id|opts-&gt;subcommand
op_assign
id|REPLAY_NONE
suffix:semicolon
multiline_comment|/* Check for incompatible command line arguments */
r_if
c_cond
(paren
id|opts-&gt;subcommand
op_ne
id|REPLAY_NONE
)paren
(brace
r_char
op_star
id|this_operation
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;subcommand
op_eq
id|REPLAY_REMOVE_STATE
)paren
id|this_operation
op_assign
l_string|&quot;--quit&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|opts-&gt;subcommand
op_eq
id|REPLAY_CONTINUE
)paren
id|this_operation
op_assign
l_string|&quot;--continue&quot;
suffix:semicolon
r_else
(brace
m_assert
(paren
id|opts-&gt;subcommand
op_eq
id|REPLAY_ROLLBACK
)paren
suffix:semicolon
id|this_operation
op_assign
l_string|&quot;--abort&quot;
suffix:semicolon
)brace
id|verify_opt_compatible
c_func
(paren
id|me
comma
id|this_operation
comma
l_string|&quot;--no-commit&quot;
comma
id|opts-&gt;no_commit
comma
l_string|&quot;--signoff&quot;
comma
id|opts-&gt;signoff
comma
l_string|&quot;--mainline&quot;
comma
id|opts-&gt;mainline
comma
l_string|&quot;--strategy&quot;
comma
id|opts-&gt;strategy
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
l_string|&quot;--strategy-option&quot;
comma
id|opts-&gt;xopts
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
l_string|&quot;-x&quot;
comma
id|opts-&gt;record_origin
comma
l_string|&quot;--ff&quot;
comma
id|opts-&gt;allow_ff
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opts-&gt;allow_ff
)paren
id|verify_opt_compatible
c_func
(paren
id|me
comma
l_string|&quot;--ff&quot;
comma
l_string|&quot;--signoff&quot;
comma
id|opts-&gt;signoff
comma
l_string|&quot;--no-commit&quot;
comma
id|opts-&gt;no_commit
comma
l_string|&quot;-x&quot;
comma
id|opts-&gt;record_origin
comma
l_string|&quot;--edit&quot;
comma
id|opts-&gt;edit
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;subcommand
op_ne
id|REPLAY_NONE
)paren
(brace
id|opts-&gt;revs
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_struct
id|setup_revision_opt
id|s_r_opt
suffix:semicolon
id|opts-&gt;revs
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|opts-&gt;revs
)paren
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
id|opts-&gt;revs
comma
l_int|NULL
)paren
suffix:semicolon
id|opts-&gt;revs-&gt;no_walk
op_assign
id|REVISION_WALK_NO_WALK_UNSORTED
suffix:semicolon
r_if
c_cond
(paren
id|argc
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
id|memset
c_func
(paren
op_amp
id|s_r_opt
comma
l_int|0
comma
r_sizeof
(paren
id|s_r_opt
)paren
)paren
suffix:semicolon
id|s_r_opt.assume_dashdash
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
id|opts-&gt;revs
comma
op_amp
id|s_r_opt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OG
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
r_struct
id|replay_opts
id|opts
suffix:semicolon
r_int
id|res
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isatty
c_func
(paren
l_int|0
)paren
)paren
id|opts.edit
op_assign
l_int|1
suffix:semicolon
id|opts.action
op_assign
id|REPLAY_REVERT
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|parse_args
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|opts
)paren
suffix:semicolon
id|res
op_assign
id|sequencer_pick_revisions
c_func
(paren
op_amp
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;revert failed&quot;
)paren
)paren
suffix:semicolon
r_return
id|res
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
r_struct
id|replay_opts
id|opts
suffix:semicolon
r_int
id|res
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|opts.action
op_assign
id|REPLAY_PICK
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|parse_args
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|opts
)paren
suffix:semicolon
id|res
op_assign
id|sequencer_pick_revisions
c_func
(paren
op_amp
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;cherry-pick failed&quot;
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
eof
