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
l_string|&quot;git push [--all | --mirror] [--dry-run] [--porcelain] [--tags] [--receive-pack=&lt;git-receive-pack&gt;] [--repo=&lt;repository&gt;] [-f | --force] [-v] [&lt;repository&gt; &lt;refspec&gt;...]&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|thin
r_static
r_int
id|thin
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
DECL|function|setup_push_tracking
r_static
r_void
id|setup_push_tracking
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|refspec
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|branch
op_star
id|branch
op_assign
id|branch_get
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|branch
)paren
id|die
c_func
(paren
l_string|&quot;You are not currently on a branch.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|branch-&gt;merge_nr
)paren
id|die
c_func
(paren
l_string|&quot;The current branch %s is not tracking anything.&quot;
comma
id|branch-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|branch-&gt;merge_nr
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;The current branch %s is tracking multiple branches, &quot;
l_string|&quot;refusing to push.&quot;
comma
id|branch-&gt;name
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|refspec
comma
l_string|&quot;%s:%s&quot;
comma
id|branch-&gt;name
comma
id|branch-&gt;merge
(braket
l_int|0
)braket
op_member_access_from_pointer
id|src
)paren
suffix:semicolon
id|add_refspec
c_func
(paren
id|refspec.buf
)paren
suffix:semicolon
)brace
DECL|function|setup_default_push_refspecs
r_static
r_void
id|setup_default_push_refspecs
c_func
(paren
r_void
)paren
(brace
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|push_default
)paren
(brace
r_default
suffix:colon
r_case
id|PUSH_DEFAULT_MATCHING
suffix:colon
id|add_refspec
c_func
(paren
l_string|&quot;:&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PUSH_DEFAULT_TRACKING
suffix:colon
id|setup_push_tracking
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PUSH_DEFAULT_CURRENT
suffix:colon
id|add_refspec
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PUSH_DEFAULT_NOTHING
suffix:colon
id|die
c_func
(paren
l_string|&quot;You didn&squot;t specify any refspecs to push, and &quot;
l_string|&quot;push.default is &bslash;&quot;nothing&bslash;&quot;.&quot;
)paren
suffix:semicolon
r_break
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
r_const
r_char
op_star
op_star
id|url
suffix:semicolon
r_int
id|url_nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote
)paren
(brace
r_if
c_cond
(paren
id|repo
)paren
id|die
c_func
(paren
l_string|&quot;bad repository &squot;%s&squot;&quot;
comma
id|repo
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;No destination configured to push to.&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|remote-&gt;mirror
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
(paren
id|flags
op_amp
id|TRANSPORT_PUSH_ALL
)paren
op_logical_and
id|refspec
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|refspec
comma
l_string|&quot;refs/tags/*&quot;
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;--all and --tags are incompatible&quot;
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;--all can&squot;t be combined with refspecs&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|TRANSPORT_PUSH_MIRROR
)paren
op_logical_and
id|refspec
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|refspec
comma
l_string|&quot;refs/tags/*&quot;
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;--mirror and --tags are incompatible&quot;
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;--mirror can&squot;t be combined with refspecs&quot;
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
op_eq
(paren
id|TRANSPORT_PUSH_ALL
op_or
id|TRANSPORT_PUSH_MIRROR
)paren
)paren
(brace
r_return
id|error
c_func
(paren
l_string|&quot;--all and --mirror are incompatible&quot;
)paren
suffix:semicolon
)brace
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
)paren
(brace
r_if
c_cond
(paren
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
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|TRANSPORT_PUSH_MIRROR
)paren
)paren
id|setup_default_push_refspecs
c_func
(paren
)paren
suffix:semicolon
)brace
id|errs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|remote-&gt;pushurl_nr
)paren
(brace
id|url
op_assign
id|remote-&gt;pushurl
suffix:semicolon
id|url_nr
op_assign
id|remote-&gt;pushurl_nr
suffix:semicolon
)brace
r_else
(brace
id|url
op_assign
id|remote-&gt;url
suffix:semicolon
id|url_nr
op_assign
id|remote-&gt;url_nr
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
id|url_nr
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
id|url
(braket
id|i
)braket
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|nonfastforward
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
id|flags
op_amp
id|TRANSPORT_PUSH_VERBOSE
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Pushing to %s&bslash;n&quot;
comma
id|url
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
comma
op_amp
id|nonfastforward
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
l_string|&quot;failed to push some refs to &squot;%s&squot;&quot;
comma
id|url
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nonfastforward
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;To prevent you from losing history, non-fast-forward updates were rejected&bslash;n&quot;
l_string|&quot;Merge the remote changes before pushing again.  See the &squot;non-fast forward&squot;&bslash;n&quot;
l_string|&quot;section of &squot;git push --help&squot; for details.&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
id|tags
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
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
id|OPT_BIT
c_func
(paren
l_char|&squot;v&squot;
comma
l_string|&quot;verbose&quot;
comma
op_amp
id|flags
comma
l_string|&quot;be verbose&quot;
comma
id|TRANSPORT_PUSH_VERBOSE
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
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;all&quot;
comma
op_amp
id|flags
comma
l_string|&quot;push all refs&quot;
comma
id|TRANSPORT_PUSH_ALL
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;mirror&quot;
comma
op_amp
id|flags
comma
l_string|&quot;mirror all refs&quot;
comma
(paren
id|TRANSPORT_PUSH_MIRROR
op_or
id|TRANSPORT_PUSH_FORCE
)paren
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
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;dry-run&quot;
comma
op_amp
id|flags
comma
l_string|&quot;dry run&quot;
comma
id|TRANSPORT_PUSH_DRY_RUN
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;porcelain&quot;
comma
op_amp
id|flags
comma
l_string|&quot;machine-readable output&quot;
comma
id|TRANSPORT_PUSH_PORCELAIN
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
comma
op_amp
id|flags
comma
l_string|&quot;force updates&quot;
comma
id|TRANSPORT_PUSH_FORCE
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
id|prefix
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
id|rc
op_assign
id|do_push
c_func
(paren
id|repo
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|push_usage
comma
id|options
)paren
suffix:semicolon
r_else
r_return
id|rc
suffix:semicolon
)brace
eof
