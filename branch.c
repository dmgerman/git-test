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
)paren
(brace
r_char
id|key
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|tracking
id|tracking
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
l_string|&quot;Tracking not set up: name too long: %s&quot;
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
op_logical_or
op_logical_neg
id|tracking.matches
)paren
r_return
l_int|1
suffix:semicolon
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
l_string|&quot;Not tracking: ambiguous information for ref %s&quot;
comma
id|orig_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tracking.matches
op_eq
l_int|1
)paren
(brace
id|sprintf
c_func
(paren
id|key
comma
l_string|&quot;branch.%s.remote&quot;
comma
id|new_ref
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key
comma
id|tracking.remote
ques
c_cond
id|tracking.remote
suffix:colon
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|key
comma
l_string|&quot;branch.%s.merge&quot;
comma
id|new_ref
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key
comma
id|tracking.src
)paren
suffix:semicolon
id|free
c_func
(paren
id|tracking.src
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Branch %s set up to track remote branch %s.&bslash;n&quot;
comma
id|new_ref
comma
id|orig_ref
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|track
)paren
(brace
r_struct
id|ref_lock
op_star
id|lock
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
id|ref
(braket
id|PATH_MAX
)braket
comma
id|msg
(braket
id|PATH_MAX
op_plus
l_int|20
)braket
suffix:semicolon
r_int
id|forcing
op_assign
l_int|0
suffix:semicolon
id|snprintf
c_func
(paren
id|ref
comma
r_sizeof
id|ref
comma
l_string|&quot;refs/heads/%s&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|ref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid branch name.&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resolve_ref
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
id|die
c_func
(paren
l_string|&quot;A branch named &squot;%s&squot; already exists.&quot;
comma
id|name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|is_bare_repository
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
id|name
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Cannot force update the current branch.&quot;
)paren
suffix:semicolon
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
id|die
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;.&quot;
comma
id|start_name
)paren
suffix:semicolon
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
id|real_ref
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Unique completion -- good */
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;Ambiguous object name: &squot;%s&squot;.&quot;
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
l_string|&quot;Not a valid branch point: &squot;%s&squot;.&quot;
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
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
id|die
c_func
(paren
l_string|&quot;Failed to lock ref for update: %s.&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
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
l_string|&quot;branch: Reset from %s&quot;
comma
id|start_name
)paren
suffix:semicolon
r_else
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
multiline_comment|/* When branching off a remote branch, set up so that git-pull&n;&t;   automatically merges from there.  So far, this is only done for&n;&t;   remotes registered via .git/config.  */
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
id|name
comma
id|real_ref
)paren
suffix:semicolon
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
id|die
c_func
(paren
l_string|&quot;Failed to write ref: %s.&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|real_ref
)paren
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
l_string|&quot;rr-cache/MERGE_RR&quot;
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
l_string|&quot;SQUASH_MSG&quot;
)paren
)paren
suffix:semicolon
)brace
eof
