multiline_comment|/*&n; * &quot;git push&quot;&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|push_usage
r_static
r_const
r_char
op_star
r_const
id|push_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git-push [--all | --mirror] [--dry-run] [--tags] [--receive-pack=&lt;git-receive-pack&gt;] [--repo=all] [-f | --force] [-v] [&lt;repository&gt; &lt;refspec&gt;...]&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|thin
DECL|variable|verbose
r_static
r_int
id|thin
comma
id|verbose
suffix:semicolon
DECL|variable|receivepack
r_static
r_const
r_char
op_star
id|receivepack
suffix:semicolon
DECL|variable|refspec
r_static
r_const
r_char
op_star
op_star
id|refspec
suffix:semicolon
DECL|variable|refspec_nr
r_static
r_int
id|refspec_nr
suffix:semicolon
DECL|function|add_refspec
r_static
r_void
id|add_refspec
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
id|nr
op_assign
id|refspec_nr
op_plus
l_int|1
suffix:semicolon
id|refspec
op_assign
id|xrealloc
c_func
(paren
id|refspec
comma
id|nr
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|refspec
(braket
id|nr
op_minus
l_int|1
)braket
op_assign
id|ref
suffix:semicolon
id|refspec_nr
op_assign
id|nr
suffix:semicolon
)brace
DECL|function|set_refspecs
r_static
r_void
id|set_refspecs
c_func
(paren
r_const
r_char
op_star
op_star
id|refs
comma
r_int
id|nr
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|ref
op_assign
id|refs
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
l_string|&quot;tag&quot;
comma
id|ref
)paren
)paren
(brace
r_char
op_star
id|tag
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_le
op_increment
id|i
)paren
id|die
c_func
(paren
l_string|&quot;tag shorthand without &lt;tag&gt;&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|refs
(braket
id|i
)braket
)paren
op_plus
l_int|11
suffix:semicolon
id|tag
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tag
comma
l_string|&quot;refs/tags/&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|tag
comma
id|refs
(braket
id|i
)braket
)paren
suffix:semicolon
id|ref
op_assign
id|tag
suffix:semicolon
)brace
id|add_refspec
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_push
r_static
r_int
id|do_push
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_int
id|flags
)paren
(brace
r_int
id|i
comma
id|errs
suffix:semicolon
r_struct
id|remote
op_star
id|remote
op_assign
id|remote_get
c_func
(paren
id|repo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote
)paren
id|die
c_func
(paren
l_string|&quot;bad repository &squot;%s&squot;&quot;
comma
id|repo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refspec
op_logical_and
op_logical_neg
(paren
id|flags
op_amp
id|TRANSPORT_PUSH_ALL
)paren
op_logical_and
id|remote-&gt;push_refspec_nr
)paren
(brace
id|refspec
op_assign
id|remote-&gt;push_refspec
suffix:semicolon
id|refspec_nr
op_assign
id|remote-&gt;push_refspec_nr
suffix:semicolon
)brace
id|errs
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
id|remote-&gt;url_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|transport
op_star
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|remote-&gt;url
(braket
id|i
)braket
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|receivepack
)paren
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_RECEIVEPACK
comma
id|receivepack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thin
)paren
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_THIN
comma
l_string|&quot;yes&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Pushing to %s&bslash;n&quot;
comma
id|remote-&gt;url
(braket
id|i
)braket
)paren
suffix:semicolon
id|err
op_assign
id|transport_push
c_func
(paren
id|transport
comma
id|refspec_nr
comma
id|refspec
comma
id|flags
)paren
suffix:semicolon
id|err
op_or_assign
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;failed to push to &squot;%s&squot;&quot;
comma
id|remote-&gt;url
(braket
id|i
)braket
)paren
suffix:semicolon
id|errs
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
op_logical_neg
id|errs
suffix:semicolon
)brace
DECL|function|cmd_push
r_int
id|cmd_push
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
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|all
op_assign
l_int|0
suffix:semicolon
r_int
id|mirror
op_assign
l_int|0
suffix:semicolon
r_int
id|dry_run
op_assign
l_int|0
suffix:semicolon
r_int
id|force
op_assign
l_int|0
suffix:semicolon
r_int
id|tags
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|repo
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* default repository */
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;repo&quot;
comma
op_amp
id|repo
comma
l_string|&quot;repository&quot;
comma
l_string|&quot;repository&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;all&quot;
comma
op_amp
id|all
comma
l_string|&quot;push all refs&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;mirror&quot;
comma
op_amp
id|mirror
comma
l_string|&quot;mirror all refs&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;tags&quot;
comma
op_amp
id|tags
comma
l_string|&quot;push tags&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;dry-run&quot;
comma
op_amp
id|dry_run
comma
l_string|&quot;dry run&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
comma
op_amp
id|force
comma
l_string|&quot;force updates&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;thin&quot;
comma
op_amp
id|thin
comma
l_string|&quot;use thin pack&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;receive-pack&quot;
comma
op_amp
id|receivepack
comma
l_string|&quot;receive-pack&quot;
comma
l_string|&quot;receive pack program&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;exec&quot;
comma
op_amp
id|receivepack
comma
l_string|&quot;receive-pack&quot;
comma
l_string|&quot;receive pack program&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|options
comma
id|push_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
id|flags
op_or_assign
id|TRANSPORT_PUSH_FORCE
suffix:semicolon
r_if
c_cond
(paren
id|dry_run
)paren
id|flags
op_or_assign
id|TRANSPORT_PUSH_DRY_RUN
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|flags
op_or_assign
id|TRANSPORT_PUSH_VERBOSE
suffix:semicolon
r_if
c_cond
(paren
id|tags
)paren
id|add_refspec
c_func
(paren
l_string|&quot;refs/tags/*&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|all
)paren
id|flags
op_or_assign
id|TRANSPORT_PUSH_ALL
suffix:semicolon
r_if
c_cond
(paren
id|mirror
)paren
id|flags
op_or_assign
(paren
id|TRANSPORT_PUSH_MIRROR
op_or
id|TRANSPORT_PUSH_FORCE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
(brace
id|repo
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|set_refspecs
c_func
(paren
id|argv
op_plus
l_int|1
comma
id|argc
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|TRANSPORT_PUSH_ALL
op_or
id|TRANSPORT_PUSH_MIRROR
)paren
)paren
op_logical_and
id|refspec
)paren
id|usage_with_options
c_func
(paren
id|push_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|TRANSPORT_PUSH_ALL
op_or
id|TRANSPORT_PUSH_MIRROR
)paren
)paren
op_eq
(paren
id|TRANSPORT_PUSH_ALL
op_or
id|TRANSPORT_PUSH_MIRROR
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;--all and --mirror are incompatible&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|push_usage
comma
id|options
)paren
suffix:semicolon
)brace
r_return
id|do_push
c_func
(paren
id|repo
comma
id|flags
)paren
suffix:semicolon
)brace
eof
