macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;branch.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|struct|tracking
r_struct
id|tracking
(brace
DECL|member|spec
r_struct
id|refspec
id|spec
suffix:semicolon
DECL|member|src
r_char
op_star
id|src
suffix:semicolon
DECL|member|remote
r_const
r_char
op_star
id|remote
suffix:semicolon
DECL|member|matches
r_int
id|matches
suffix:semicolon
)brace
suffix:semicolon
DECL|function|find_tracked_branch
r_static
r_int
id|find_tracked_branch
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_void
op_star
id|priv
)paren
(brace
r_struct
id|tracking
op_star
id|tracking
op_assign
id|priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote_find_tracking
c_func
(paren
id|remote
comma
op_amp
id|tracking-&gt;spec
)paren
)paren
(brace
r_if
c_cond
(paren
op_increment
id|tracking-&gt;matches
op_eq
l_int|1
)paren
(brace
id|tracking-&gt;src
op_assign
id|tracking-&gt;spec.src
suffix:semicolon
id|tracking-&gt;remote
op_assign
id|remote-&gt;name
suffix:semicolon
)brace
r_else
(brace
id|free
c_func
(paren
id|tracking-&gt;spec.src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tracking-&gt;src
)paren
(brace
id|free
c_func
(paren
id|tracking-&gt;src
)paren
suffix:semicolon
id|tracking-&gt;src
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|tracking-&gt;spec.src
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|should_setup_rebase
r_static
r_int
id|should_setup_rebase
c_func
(paren
r_const
r_char
op_star
id|origin
)paren
(brace
r_switch
c_cond
(paren
id|autorebase
)paren
(brace
r_case
id|AUTOREBASE_NEVER
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|AUTOREBASE_LOCAL
suffix:colon
r_return
id|origin
op_eq
l_int|NULL
suffix:semicolon
r_case
id|AUTOREBASE_REMOTE
suffix:colon
r_return
id|origin
op_ne
l_int|NULL
suffix:semicolon
r_case
id|AUTOREBASE_ALWAYS
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|install_branch_config
r_void
id|install_branch_config
c_func
(paren
r_int
id|flag
comma
r_const
r_char
op_star
id|local
comma
r_const
r_char
op_star
id|origin
comma
r_const
r_char
op_star
id|remote
)paren
(brace
r_const
r_char
op_star
id|shortname
op_assign
id|remote
op_plus
l_int|11
suffix:semicolon
r_int
id|remote_is_branch
op_assign
id|starts_with
c_func
(paren
id|remote
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
r_struct
id|strbuf
id|key
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|rebasing
op_assign
id|should_setup_rebase
c_func
(paren
id|origin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote_is_branch
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|local
comma
id|shortname
)paren
op_logical_and
op_logical_neg
id|origin
)paren
(brace
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not setting branch %s as its own upstream.&quot;
)paren
comma
id|local
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|key
comma
l_string|&quot;branch.%s.remote&quot;
comma
id|local
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key.buf
comma
id|origin
ques
c_cond
id|origin
suffix:colon
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|key
comma
l_string|&quot;branch.%s.merge&quot;
comma
id|local
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key.buf
comma
id|remote
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rebasing
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|key
comma
l_string|&quot;branch.%s.rebase&quot;
comma
id|local
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key.buf
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|BRANCH_CONFIG_VERBOSE
)paren
(brace
r_if
c_cond
(paren
id|remote_is_branch
op_logical_and
id|origin
)paren
id|printf_ln
c_func
(paren
id|rebasing
ques
c_cond
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track remote branch %s from %s by rebasing.&quot;
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track remote branch %s from %s.&quot;
)paren
comma
id|local
comma
id|shortname
comma
id|origin
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|remote_is_branch
op_logical_and
op_logical_neg
id|origin
)paren
id|printf_ln
c_func
(paren
id|rebasing
ques
c_cond
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track local branch %s by rebasing.&quot;
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track local branch %s.&quot;
)paren
comma
id|local
comma
id|shortname
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|remote_is_branch
op_logical_and
id|origin
)paren
id|printf_ln
c_func
(paren
id|rebasing
ques
c_cond
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track remote ref %s by rebasing.&quot;
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track remote ref %s.&quot;
)paren
comma
id|local
comma
id|remote
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|remote_is_branch
op_logical_and
op_logical_neg
id|origin
)paren
id|printf_ln
c_func
(paren
id|rebasing
ques
c_cond
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track local ref %s by rebasing.&quot;
)paren
suffix:colon
id|_
c_func
(paren
l_string|&quot;Branch %s set up to track local ref %s.&quot;
)paren
comma
id|local
comma
id|remote
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;BUG: impossible combination of %d and %p&quot;
comma
id|remote_is_branch
comma
id|origin
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is called when new_ref is branched off of orig_ref, and tries&n; * to infer the settings for branch.&lt;new_ref&gt;.{remote,merge} from the&n; * config.&n; */
DECL|function|setup_tracking
r_static
r_int
id|setup_tracking
c_func
(paren
r_const
r_char
op_star
id|new_ref
comma
r_const
r_char
op_star
id|orig_ref
comma
r_enum
id|branch_track
id|track
comma
r_int
id|quiet
)paren
(brace
r_struct
id|tracking
id|tracking
suffix:semicolon
r_int
id|config_flags
op_assign
id|quiet
ques
c_cond
l_int|0
suffix:colon
id|BRANCH_CONFIG_VERBOSE
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|new_ref
)paren
OG
l_int|1024
l_int|7
l_int|7
l_int|1
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Tracking not set up: name too long: %s&quot;
)paren
comma
id|new_ref
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tracking
comma
l_int|0
comma
r_sizeof
(paren
id|tracking
)paren
)paren
suffix:semicolon
id|tracking.spec.dst
op_assign
(paren
r_char
op_star
)paren
id|orig_ref
suffix:semicolon
r_if
c_cond
(paren
id|for_each_remote
c_func
(paren
id|find_tracked_branch
comma
op_amp
id|tracking
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tracking.matches
)paren
r_switch
c_cond
(paren
id|track
)paren
(brace
r_case
id|BRANCH_TRACK_ALWAYS
suffix:colon
r_case
id|BRANCH_TRACK_EXPLICIT
suffix:colon
r_case
id|BRANCH_TRACK_OVERRIDE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tracking.matches
OG
l_int|1
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not tracking: ambiguous information for ref %s&quot;
)paren
comma
id|orig_ref
)paren
suffix:semicolon
id|install_branch_config
c_func
(paren
id|config_flags
comma
id|new_ref
comma
id|tracking.remote
comma
id|tracking.src
ques
c_cond
id|tracking.src
suffix:colon
id|orig_ref
)paren
suffix:semicolon
id|free
c_func
(paren
id|tracking.src
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|branch_desc_cb
r_struct
id|branch_desc_cb
(brace
DECL|member|config_name
r_const
r_char
op_star
id|config_name
suffix:semicolon
DECL|member|value
r_const
r_char
op_star
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|function|read_branch_desc_cb
r_static
r_int
id|read_branch_desc_cb
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
comma
r_void
op_star
id|cb
)paren
(brace
r_struct
id|branch_desc_cb
op_star
id|desc
op_assign
id|cb
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|desc-&gt;config_name
comma
id|var
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|desc-&gt;value
)paren
suffix:semicolon
r_return
id|git_config_string
c_func
(paren
op_amp
id|desc-&gt;value
comma
id|var
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|read_branch_desc
r_int
id|read_branch_desc
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_const
r_char
op_star
id|branch_name
)paren
(brace
r_struct
id|branch_desc_cb
id|cb
suffix:semicolon
r_struct
id|strbuf
id|name
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|name
comma
l_string|&quot;branch.%s.description&quot;
comma
id|branch_name
)paren
suffix:semicolon
id|cb.config_name
op_assign
id|name.buf
suffix:semicolon
id|cb.value
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|git_config
c_func
(paren
id|read_branch_desc_cb
comma
op_amp
id|cb
)paren
OL
l_int|0
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cb.value
)paren
id|strbuf_addstr
c_func
(paren
id|buf
comma
id|cb.value
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|validate_new_branchname
r_int
id|validate_new_branchname
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|strbuf
op_star
id|ref
comma
r_int
id|force
comma
r_int
id|attr_only
)paren
(brace
r_if
c_cond
(paren
id|strbuf_check_branch_ref
c_func
(paren
id|ref
comma
id|name
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid branch name.&quot;
)paren
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref_exists
c_func
(paren
id|ref-&gt;buf
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|force
op_logical_and
op_logical_neg
id|attr_only
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;A branch named &squot;%s&squot; already exists.&quot;
)paren
comma
id|ref-&gt;buf
op_plus
id|strlen
c_func
(paren
l_string|&quot;refs/heads/&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_only
)paren
(brace
r_const
r_char
op_star
id|head
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|head
op_assign
id|resolve_ref_unsafe
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
r_if
c_cond
(paren
op_logical_neg
id|is_bare_repository
c_func
(paren
)paren
op_logical_and
id|head
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
id|ref-&gt;buf
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Cannot force update the current branch.&quot;
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|check_tracking_branch
r_static
r_int
id|check_tracking_branch
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_void
op_star
id|cb_data
)paren
(brace
r_char
op_star
id|tracking_branch
op_assign
id|cb_data
suffix:semicolon
r_struct
id|refspec
id|query
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|query
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|refspec
)paren
)paren
suffix:semicolon
id|query.dst
op_assign
id|tracking_branch
suffix:semicolon
r_return
op_logical_neg
id|remote_find_tracking
c_func
(paren
id|remote
comma
op_amp
id|query
)paren
suffix:semicolon
)brace
DECL|function|validate_remote_tracking_branch
r_static
r_int
id|validate_remote_tracking_branch
c_func
(paren
r_char
op_star
id|ref
)paren
(brace
r_return
op_logical_neg
id|for_each_remote
c_func
(paren
id|check_tracking_branch
comma
id|ref
)paren
suffix:semicolon
)brace
DECL|variable|upstream_not_branch
r_static
r_const
r_char
id|upstream_not_branch
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;Cannot setup tracking information; starting point &squot;%s&squot; is not a branch.&quot;
)paren
suffix:semicolon
DECL|variable|upstream_missing
r_static
r_const
r_char
id|upstream_missing
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;the requested upstream branch &squot;%s&squot; does not exist&quot;
)paren
suffix:semicolon
DECL|variable|upstream_advice
r_static
r_const
r_char
id|upstream_advice
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;&bslash;n&quot;
l_string|&quot;If you are planning on basing your work on an upstream&bslash;n&quot;
l_string|&quot;branch that already exists at the remote, you may need to&bslash;n&quot;
l_string|&quot;run &bslash;&quot;git fetch&bslash;&quot; to retrieve it.&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;If you are planning to push out a new local branch that&bslash;n&quot;
l_string|&quot;will track its remote counterpart, you may want to use&bslash;n&quot;
l_string|&quot;&bslash;&quot;git push -u&bslash;&quot; to set the upstream config as you push.&quot;
)paren
suffix:semicolon
DECL|function|create_branch
r_void
id|create_branch
c_func
(paren
r_const
r_char
op_star
id|head
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|start_name
comma
r_int
id|force
comma
r_int
id|reflog
comma
r_int
id|clobber_head
comma
r_int
id|quiet
comma
r_enum
id|branch_track
id|track
)paren
(brace
r_struct
id|ref_lock
op_star
id|lock
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|real_ref
comma
id|msg
(braket
id|PATH_MAX
op_plus
l_int|20
)braket
suffix:semicolon
r_struct
id|strbuf
id|ref
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|forcing
op_assign
l_int|0
suffix:semicolon
r_int
id|dont_change_ref
op_assign
l_int|0
suffix:semicolon
r_int
id|explicit_tracking
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|track
op_eq
id|BRANCH_TRACK_EXPLICIT
op_logical_or
id|track
op_eq
id|BRANCH_TRACK_OVERRIDE
)paren
id|explicit_tracking
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|validate_new_branchname
c_func
(paren
id|name
comma
op_amp
id|ref
comma
id|force
comma
id|track
op_eq
id|BRANCH_TRACK_OVERRIDE
op_logical_or
id|clobber_head
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
id|dont_change_ref
op_assign
l_int|1
suffix:semicolon
r_else
id|forcing
op_assign
l_int|1
suffix:semicolon
)brace
id|real_ref
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|start_name
comma
id|sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|explicit_tracking
)paren
(brace
r_if
c_cond
(paren
id|advice_set_upstream_failure
)paren
(brace
id|error
c_func
(paren
id|_
c_func
(paren
id|upstream_missing
)paren
comma
id|start_name
)paren
suffix:semicolon
id|advise
c_func
(paren
id|_
c_func
(paren
id|upstream_advice
)paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
id|_
c_func
(paren
id|upstream_missing
)paren
comma
id|start_name
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;.&quot;
)paren
comma
id|start_name
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dwim_ref
c_func
(paren
id|start_name
comma
id|strlen
c_func
(paren
id|start_name
)paren
comma
id|sha1
comma
op_amp
id|real_ref
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Not branching from any existing branch */
r_if
c_cond
(paren
id|explicit_tracking
)paren
id|die
c_func
(paren
id|_
c_func
(paren
id|upstream_not_branch
)paren
comma
id|start_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Unique completion -- good, only if it is a real branch */
r_if
c_cond
(paren
op_logical_neg
id|starts_with
c_func
(paren
id|real_ref
comma
l_string|&quot;refs/heads/&quot;
)paren
op_logical_and
id|validate_remote_tracking_branch
c_func
(paren
id|real_ref
)paren
)paren
(brace
r_if
c_cond
(paren
id|explicit_tracking
)paren
id|die
c_func
(paren
id|_
c_func
(paren
id|upstream_not_branch
)paren
comma
id|start_name
)paren
suffix:semicolon
r_else
id|real_ref
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Ambiguous object name: &squot;%s&squot;.&quot;
)paren
comma
id|start_name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not a valid branch point: &squot;%s&squot;.&quot;
)paren
comma
id|start_name
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|sha1
comma
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dont_change_ref
)paren
(brace
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref.buf
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Failed to lock ref for update&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reflog
)paren
id|log_all_ref_updates
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|forcing
)paren
id|snprintf
c_func
(paren
id|msg
comma
r_sizeof
id|msg
comma
l_string|&quot;branch: Reset to %s&quot;
comma
id|start_name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|dont_change_ref
)paren
id|snprintf
c_func
(paren
id|msg
comma
r_sizeof
id|msg
comma
l_string|&quot;branch: Created from %s&quot;
comma
id|start_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|real_ref
op_logical_and
id|track
)paren
id|setup_tracking
c_func
(paren
id|ref.buf
op_plus
l_int|11
comma
id|real_ref
comma
id|track
comma
id|quiet
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dont_change_ref
)paren
r_if
c_cond
(paren
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|sha1
comma
id|msg
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Failed to write ref&quot;
)paren
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|ref
)paren
suffix:semicolon
id|free
c_func
(paren
id|real_ref
)paren
suffix:semicolon
)brace
DECL|function|remove_branch_state
r_void
id|remove_branch_state
c_func
(paren
r_void
)paren
(brace
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;CHERRY_PICK_HEAD&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;REVERT_HEAD&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;MERGE_HEAD&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;MERGE_RR&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;MERGE_MSG&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;MERGE_MODE&quot;
)paren
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;SQUASH_MSG&quot;
)paren
)paren
suffix:semicolon
)brace
eof
