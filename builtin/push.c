multiline_comment|/*&n; * &quot;git push&quot;&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;submodule.h&quot;
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
l_string|&quot;git push [&lt;options&gt;] [&lt;repository&gt; [&lt;refspec&gt;...]]&quot;
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
DECL|variable|deleterefs
r_static
r_int
id|deleterefs
suffix:semicolon
DECL|variable|receivepack
r_static
r_const
r_char
op_star
id|receivepack
suffix:semicolon
DECL|variable|verbosity
r_static
r_int
id|verbosity
suffix:semicolon
DECL|variable|progress
r_static
r_int
id|progress
op_assign
l_int|1
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
DECL|variable|refspec_alloc
r_static
r_int
id|refspec_alloc
suffix:semicolon
DECL|variable|default_matching_used
r_static
r_int
id|default_matching_used
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
id|refspec_nr
op_increment
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|refspec
comma
id|refspec_nr
comma
id|refspec_alloc
)paren
suffix:semicolon
id|refspec
(braket
id|refspec_nr
op_minus
l_int|1
)braket
op_assign
id|ref
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
id|_
c_func
(paren
l_string|&quot;tag shorthand without &lt;tag&gt;&quot;
)paren
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
r_if
c_cond
(paren
id|deleterefs
)paren
(brace
id|tag
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tag
comma
l_string|&quot;:refs/tags/&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
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
)brace
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
r_else
r_if
c_cond
(paren
id|deleterefs
op_logical_and
op_logical_neg
id|strchr
c_func
(paren
id|ref
comma
l_char|&squot;:&squot;
)paren
)paren
(brace
r_char
op_star
id|delref
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|ref
)paren
op_plus
l_int|1
suffix:semicolon
id|delref
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|delref
comma
l_string|&quot;:&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|delref
comma
id|ref
)paren
suffix:semicolon
id|ref
op_assign
id|delref
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|deleterefs
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--delete only accepts plain target ref names&quot;
)paren
)paren
suffix:semicolon
id|add_refspec
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
)brace
DECL|function|push_url_of_remote
r_static
r_int
id|push_url_of_remote
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_const
r_char
op_star
op_star
op_star
id|url_p
)paren
(brace
r_if
c_cond
(paren
id|remote-&gt;pushurl_nr
)paren
(brace
op_star
id|url_p
op_assign
id|remote-&gt;pushurl
suffix:semicolon
r_return
id|remote-&gt;pushurl_nr
suffix:semicolon
)brace
op_star
id|url_p
op_assign
id|remote-&gt;url
suffix:semicolon
r_return
id|remote-&gt;url_nr
suffix:semicolon
)brace
DECL|function|die_push_simple
r_static
id|NORETURN
r_int
id|die_push_simple
c_func
(paren
r_struct
id|branch
op_star
id|branch
comma
r_struct
id|remote
op_star
id|remote
)paren
(brace
multiline_comment|/*&n;&t; * There&squot;s no point in using shorten_unambiguous_ref here,&n;&t; * as the ambiguity would be on the remote side, not what&n;&t; * we have locally. Plus, this is supposed to be the simple&n;&t; * mode. If the user is doing something crazy like setting&n;&t; * upstream to a non-branch, we should probably be showing&n;&t; * them the big ugly fully qualified ref.&n;&t; */
r_const
r_char
op_star
id|advice_maybe
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_const
r_char
op_star
id|short_upstream
op_assign
id|skip_prefix
c_func
(paren
id|branch-&gt;merge
(braket
l_int|0
)braket
op_member_access_from_pointer
id|src
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|short_upstream
)paren
id|short_upstream
op_assign
id|branch-&gt;merge
(braket
l_int|0
)braket
op_member_access_from_pointer
id|src
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t show advice for people who explicitely set&n;&t; * push.default.&n;&t; */
r_if
c_cond
(paren
id|push_default
op_eq
id|PUSH_DEFAULT_UNSPECIFIED
)paren
id|advice_maybe
op_assign
id|_
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;To choose either option permanently, &quot;
l_string|&quot;see push.default in &squot;git help config&squot;.&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;The upstream branch of your current branch does not match&bslash;n&quot;
l_string|&quot;the name of your current branch.  To push to the upstream branch&bslash;n&quot;
l_string|&quot;on the remote, use&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;    git push %s HEAD:%s&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;To push to the branch of the same name on the remote, use&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;    git push %s %s&bslash;n&quot;
l_string|&quot;%s&quot;
)paren
comma
id|remote-&gt;name
comma
id|short_upstream
comma
id|remote-&gt;name
comma
id|branch-&gt;name
comma
id|advice_maybe
)paren
suffix:semicolon
)brace
DECL|function|setup_push_upstream
r_static
r_void
id|setup_push_upstream
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_int
id|simple
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
id|_
c_func
(paren
l_string|&quot;You are not currently on a branch.&bslash;n&quot;
l_string|&quot;To push the history leading to the current (detached HEAD)&bslash;n&quot;
l_string|&quot;state now, use&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;    git push %s HEAD:&lt;name-of-remote-branch&gt;&bslash;n&quot;
)paren
comma
id|remote-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|branch-&gt;merge_nr
op_logical_or
op_logical_neg
id|branch-&gt;merge
op_logical_or
op_logical_neg
id|branch-&gt;remote_name
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;The current branch %s has no upstream branch.&bslash;n&quot;
l_string|&quot;To push the current branch and set the remote as upstream, use&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;    git push --set-upstream %s %s&bslash;n&quot;
)paren
comma
id|branch-&gt;name
comma
id|remote-&gt;name
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
id|_
c_func
(paren
l_string|&quot;The current branch %s has multiple upstream branches, &quot;
l_string|&quot;refusing to push.&quot;
)paren
comma
id|branch-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|branch-&gt;remote_name
comma
id|remote-&gt;name
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;You are pushing to remote &squot;%s&squot;, which is not the upstream of&bslash;n&quot;
l_string|&quot;your current branch &squot;%s&squot;, without telling me what to push&bslash;n&quot;
l_string|&quot;to update which remote branch.&quot;
)paren
comma
id|remote-&gt;name
comma
id|branch-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|simple
op_logical_and
id|strcmp
c_func
(paren
id|branch-&gt;refname
comma
id|branch-&gt;merge
(braket
l_int|0
)braket
op_member_access_from_pointer
id|src
)paren
)paren
id|die_push_simple
c_func
(paren
id|branch
comma
id|remote
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
r_struct
id|remote
op_star
id|remote
)paren
(brace
r_switch
c_cond
(paren
id|push_default
)paren
(brace
r_default
suffix:colon
r_case
id|PUSH_DEFAULT_UNSPECIFIED
suffix:colon
id|default_matching_used
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fallthru */
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
id|PUSH_DEFAULT_SIMPLE
suffix:colon
id|setup_push_upstream
c_func
(paren
id|remote
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PUSH_DEFAULT_UPSTREAM
suffix:colon
id|setup_push_upstream
c_func
(paren
id|remote
comma
l_int|0
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
id|_
c_func
(paren
l_string|&quot;You didn&squot;t specify any refspecs to push, and &quot;
l_string|&quot;push.default is &bslash;&quot;nothing&bslash;&quot;.&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|message_advice_pull_before_push
r_static
r_const
r_char
id|message_advice_pull_before_push
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;Updates were rejected because the tip of your current branch is behind&bslash;n&quot;
l_string|&quot;its remote counterpart. Merge the remote changes (e.g. &squot;git pull&squot;)&bslash;n&quot;
l_string|&quot;before pushing again.&bslash;n&quot;
l_string|&quot;See the &squot;Note about fast-forwards&squot; in &squot;git push --help&squot; for details.&quot;
)paren
suffix:semicolon
DECL|variable|message_advice_use_upstream
r_static
r_const
r_char
id|message_advice_use_upstream
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;Updates were rejected because a pushed branch tip is behind its remote&bslash;n&quot;
l_string|&quot;counterpart. If you did not intend to push that branch, you may want to&bslash;n&quot;
l_string|&quot;specify branches to push or set the &squot;push.default&squot; configuration&bslash;n&quot;
l_string|&quot;variable to &squot;current&squot; or &squot;upstream&squot; to push only the current branch.&quot;
)paren
suffix:semicolon
DECL|variable|message_advice_checkout_pull_push
r_static
r_const
r_char
id|message_advice_checkout_pull_push
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;Updates were rejected because a pushed branch tip is behind its remote&bslash;n&quot;
l_string|&quot;counterpart. Check out this branch and merge the remote changes&bslash;n&quot;
l_string|&quot;(e.g. &squot;git pull&squot;) before pushing again.&bslash;n&quot;
l_string|&quot;See the &squot;Note about fast-forwards&squot; in &squot;git push --help&squot; for details.&quot;
)paren
suffix:semicolon
DECL|function|advise_pull_before_push
r_static
r_void
id|advise_pull_before_push
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|advice_push_non_ff_current
op_logical_or
op_logical_neg
id|advice_push_nonfastforward
)paren
r_return
suffix:semicolon
id|advise
c_func
(paren
id|_
c_func
(paren
id|message_advice_pull_before_push
)paren
)paren
suffix:semicolon
)brace
DECL|function|advise_use_upstream
r_static
r_void
id|advise_use_upstream
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|advice_push_non_ff_default
op_logical_or
op_logical_neg
id|advice_push_nonfastforward
)paren
r_return
suffix:semicolon
id|advise
c_func
(paren
id|_
c_func
(paren
id|message_advice_use_upstream
)paren
)paren
suffix:semicolon
)brace
DECL|function|advise_checkout_pull_push
r_static
r_void
id|advise_checkout_pull_push
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|advice_push_non_ff_matching
op_logical_or
op_logical_neg
id|advice_push_nonfastforward
)paren
r_return
suffix:semicolon
id|advise
c_func
(paren
id|_
c_func
(paren
id|message_advice_checkout_pull_push
)paren
)paren
suffix:semicolon
)brace
DECL|function|push_with_options
r_static
r_int
id|push_with_options
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_int
id|flags
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|nonfastforward
suffix:semicolon
id|transport_set_verbosity
c_func
(paren
id|transport
comma
id|verbosity
comma
id|progress
)paren
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
id|verbosity
OG
l_int|0
)paren
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;Pushing to %s&bslash;n&quot;
)paren
comma
id|transport-&gt;url
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
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;failed to push some refs to &squot;%s&squot;&quot;
)paren
comma
id|transport-&gt;url
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
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|nonfastforward
)paren
(brace
r_default
suffix:colon
r_break
suffix:semicolon
r_case
id|NON_FF_HEAD
suffix:colon
id|advise_pull_before_push
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NON_FF_OTHER
suffix:colon
r_if
c_cond
(paren
id|default_matching_used
)paren
id|advise_use_upstream
c_func
(paren
)paren
suffix:semicolon
r_else
id|advise_checkout_pull_push
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
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
id|_
c_func
(paren
l_string|&quot;bad repository &squot;%s&squot;&quot;
)paren
comma
id|repo
)paren
suffix:semicolon
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;No configured push destination.&bslash;n&quot;
l_string|&quot;Either specify the URL from the command-line or configure a remote repository using&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;    git remote add &lt;name&gt; &lt;url&gt;&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;and then push using the remote name&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;    git push &lt;name&gt;&bslash;n&quot;
)paren
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
id|_
c_func
(paren
l_string|&quot;--all and --tags are incompatible&quot;
)paren
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--all can&squot;t be combined with refspecs&quot;
)paren
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
id|_
c_func
(paren
l_string|&quot;--mirror and --tags are incompatible&quot;
)paren
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--mirror can&squot;t be combined with refspecs&quot;
)paren
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
id|_
c_func
(paren
l_string|&quot;--all and --mirror are incompatible&quot;
)paren
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
id|remote
)paren
suffix:semicolon
)brace
id|errs
op_assign
l_int|0
suffix:semicolon
id|url_nr
op_assign
id|push_url_of_remote
c_func
(paren
id|remote
comma
op_amp
id|url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|url_nr
)paren
(brace
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
r_if
c_cond
(paren
id|push_with_options
c_func
(paren
id|transport
comma
id|flags
)paren
)paren
id|errs
op_increment
suffix:semicolon
)brace
)brace
r_else
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
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|push_with_options
c_func
(paren
id|transport
comma
id|flags
)paren
)paren
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
DECL|function|option_parse_recurse_submodules
r_static
r_int
id|option_parse_recurse_submodules
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
r_int
op_star
id|flags
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
op_star
id|flags
op_amp
(paren
id|TRANSPORT_RECURSE_SUBMODULES_CHECK
op_or
id|TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s can only be used once.&quot;
comma
id|opt-&gt;long_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;check&quot;
)paren
)paren
op_star
id|flags
op_or_assign
id|TRANSPORT_RECURSE_SUBMODULES_CHECK
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;on-demand&quot;
)paren
)paren
op_star
id|flags
op_or_assign
id|TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;bad %s argument: %s&quot;
comma
id|opt-&gt;long_name
comma
id|arg
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;option %s needs an argument (check|on-demand)&quot;
comma
id|opt-&gt;long_name
)paren
suffix:semicolon
r_return
l_int|0
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
id|OPT__VERBOSITY
c_func
(paren
op_amp
id|verbosity
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
l_string|&quot;delete&quot;
comma
op_amp
id|deleterefs
comma
l_string|&quot;delete refs&quot;
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
l_string|&quot;push tags (can&squot;t be used with --all or --mirror)&quot;
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;n&squot;
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
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;recurse-submodules&quot;
comma
op_amp
id|flags
comma
l_string|&quot;check&quot;
comma
l_string|&quot;controls recursive pushing of submodules&quot;
comma
id|PARSE_OPT_OPTARG
comma
id|option_parse_recurse_submodules
)brace
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
id|OPT_BIT
c_func
(paren
l_char|&squot;u&squot;
comma
l_string|&quot;set-upstream&quot;
comma
op_amp
id|flags
comma
l_string|&quot;set upstream for git pull/status&quot;
comma
id|TRANSPORT_PUSH_SET_UPSTREAM
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;progress&quot;
comma
op_amp
id|progress
comma
l_string|&quot;force progress reporting&quot;
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;prune&quot;
comma
op_amp
id|flags
comma
l_string|&quot;prune locally removed refs&quot;
comma
id|TRANSPORT_PUSH_PRUNE
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|packet_trace_identity
c_func
(paren
l_string|&quot;push&quot;
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
id|deleterefs
op_logical_and
(paren
id|tags
op_logical_or
(paren
id|flags
op_amp
(paren
id|TRANSPORT_PUSH_ALL
op_or
id|TRANSPORT_PUSH_MIRROR
)paren
)paren
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--delete is incompatible with --all, --mirror and --tags&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deleterefs
op_logical_and
id|argc
OL
l_int|2
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;--delete doesn&squot;t make sense without any refs&quot;
)paren
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
