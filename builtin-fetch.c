multiline_comment|/*&n; * &quot;git fetch&quot;&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|builtin_fetch_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_fetch_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git-fetch [options] [&lt;repository&gt; &lt;refspec&gt;...]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TAGS_UNSET
id|TAGS_UNSET
op_assign
l_int|0
comma
DECL|enumerator|TAGS_DEFAULT
id|TAGS_DEFAULT
op_assign
l_int|1
comma
DECL|enumerator|TAGS_SET
id|TAGS_SET
op_assign
l_int|2
)brace
suffix:semicolon
DECL|variable|append
DECL|variable|force
DECL|variable|keep
DECL|variable|update_head_ok
DECL|variable|verbose
DECL|variable|quiet
r_static
r_int
id|append
comma
id|force
comma
id|keep
comma
id|update_head_ok
comma
id|verbose
comma
id|quiet
suffix:semicolon
DECL|variable|tags
r_static
r_int
id|tags
op_assign
id|TAGS_DEFAULT
suffix:semicolon
DECL|variable|depth
r_static
r_const
r_char
op_star
id|depth
suffix:semicolon
DECL|variable|upload_pack
r_static
r_const
r_char
op_star
id|upload_pack
suffix:semicolon
DECL|variable|default_rla
r_static
r_struct
id|strbuf
id|default_rla
op_assign
id|STRBUF_INIT
suffix:semicolon
DECL|variable|transport
r_static
r_struct
id|transport
op_star
id|transport
suffix:semicolon
DECL|variable|builtin_fetch_options
r_static
r_struct
id|option
id|builtin_fetch_options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;a&squot;
comma
l_string|&quot;append&quot;
comma
op_amp
id|append
comma
l_string|&quot;append to .git/FETCH_HEAD instead of overwriting&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;upload-pack&quot;
comma
op_amp
id|upload_pack
comma
l_string|&quot;PATH&quot;
comma
l_string|&quot;path to upload pack on remote end&quot;
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
l_string|&quot;force overwrite of local branch&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;t&squot;
comma
l_string|&quot;tags&quot;
comma
op_amp
id|tags
comma
l_string|&quot;fetch all tags and associated objects&quot;
comma
id|TAGS_SET
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;k&squot;
comma
l_string|&quot;keep&quot;
comma
op_amp
id|keep
comma
l_string|&quot;keep downloaded pack&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;u&squot;
comma
l_string|&quot;update-head-ok&quot;
comma
op_amp
id|update_head_ok
comma
l_string|&quot;allow updating of HEAD ref&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;depth&quot;
comma
op_amp
id|depth
comma
l_string|&quot;DEPTH&quot;
comma
l_string|&quot;deepen history of shallow clone&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
DECL|function|unlock_pack
r_static
r_void
id|unlock_pack
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|transport
)paren
id|transport_unlock_pack
c_func
(paren
id|transport
)paren
suffix:semicolon
)brace
DECL|function|unlock_pack_on_signal
r_static
r_void
id|unlock_pack_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|unlock_pack
c_func
(paren
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGINT
comma
id|SIG_DFL
)paren
suffix:semicolon
id|raise
c_func
(paren
id|signo
)paren
suffix:semicolon
)brace
DECL|function|add_merge_config
r_static
r_void
id|add_merge_config
c_func
(paren
r_struct
id|ref
op_star
op_star
id|head
comma
r_const
r_struct
id|ref
op_star
id|remote_refs
comma
r_struct
id|branch
op_star
id|branch
comma
r_struct
id|ref
op_star
op_star
op_star
id|tail
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
id|branch-&gt;merge_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ref
op_star
id|rm
comma
op_star
op_star
id|old_tail
op_assign
op_star
id|tail
suffix:semicolon
r_struct
id|refspec
id|refspec
suffix:semicolon
r_for
c_loop
(paren
id|rm
op_assign
op_star
id|head
suffix:semicolon
id|rm
suffix:semicolon
id|rm
op_assign
id|rm-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|branch_merge_matches
c_func
(paren
id|branch
comma
id|i
comma
id|rm-&gt;name
)paren
)paren
(brace
id|rm-&gt;merge
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rm
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Not fetched to a tracking branch?  We need to fetch&n;&t;&t; * it anyway to allow this branch&squot;s &quot;branch.$name.merge&quot;&n;&t;&t; * to be honored by git-pull, but we do not have to&n;&t;&t; * fail if branch.$name.merge is misconfigured to point&n;&t;&t; * at a nonexisting branch.  If we were indeed called by&n;&t;&t; * git-pull, it will notice the misconfiguration because&n;&t;&t; * there is no entry in the resulting FETCH_HEAD marked&n;&t;&t; * for merging.&n;&t;&t; */
id|refspec.src
op_assign
id|branch-&gt;merge
(braket
id|i
)braket
op_member_access_from_pointer
id|src
suffix:semicolon
id|refspec.dst
op_assign
l_int|NULL
suffix:semicolon
id|refspec.pattern
op_assign
l_int|0
suffix:semicolon
id|refspec.force
op_assign
l_int|0
suffix:semicolon
id|get_fetch_map
c_func
(paren
id|remote_refs
comma
op_amp
id|refspec
comma
id|tail
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rm
op_assign
op_star
id|old_tail
suffix:semicolon
id|rm
suffix:semicolon
id|rm
op_assign
id|rm-&gt;next
)paren
id|rm-&gt;merge
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|get_ref_map
r_static
r_struct
id|ref
op_star
id|get_ref_map
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_struct
id|refspec
op_star
id|refs
comma
r_int
id|ref_count
comma
r_int
id|tags
comma
r_int
op_star
id|autotags
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ref
op_star
id|rm
suffix:semicolon
r_struct
id|ref
op_star
id|ref_map
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
op_star
id|tail
op_assign
op_amp
id|ref_map
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|remote_refs
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_count
op_logical_or
id|tags
op_eq
id|TAGS_SET
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
id|ref_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|get_fetch_map
c_func
(paren
id|remote_refs
comma
op_amp
id|refs
(braket
id|i
)braket
comma
op_amp
id|tail
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|refs
(braket
id|i
)braket
dot
id|dst
op_logical_and
id|refs
(braket
id|i
)braket
dot
id|dst
(braket
l_int|0
)braket
)paren
op_star
id|autotags
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Merge everything on the command line, but not --tags */
r_for
c_loop
(paren
id|rm
op_assign
id|ref_map
suffix:semicolon
id|rm
suffix:semicolon
id|rm
op_assign
id|rm-&gt;next
)paren
id|rm-&gt;merge
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tags
op_eq
id|TAGS_SET
)paren
(brace
r_struct
id|refspec
id|refspec
suffix:semicolon
id|refspec.src
op_assign
l_string|&quot;refs/tags/&quot;
suffix:semicolon
id|refspec.dst
op_assign
l_string|&quot;refs/tags/&quot;
suffix:semicolon
id|refspec.pattern
op_assign
l_int|1
suffix:semicolon
id|refspec.force
op_assign
l_int|0
suffix:semicolon
id|get_fetch_map
c_func
(paren
id|remote_refs
comma
op_amp
id|refspec
comma
op_amp
id|tail
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Use the defaults */
r_struct
id|remote
op_star
id|remote
op_assign
id|transport-&gt;remote
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
r_int
id|has_merge
op_assign
id|branch_has_merge_config
c_func
(paren
id|branch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
op_logical_and
(paren
id|remote-&gt;fetch_refspec_nr
op_logical_or
id|has_merge
)paren
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
id|remote-&gt;fetch_refspec_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|get_fetch_map
c_func
(paren
id|remote_refs
comma
op_amp
id|remote-&gt;fetch
(braket
id|i
)braket
comma
op_amp
id|tail
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote-&gt;fetch
(braket
id|i
)braket
dot
id|dst
op_logical_and
id|remote-&gt;fetch
(braket
id|i
)braket
dot
id|dst
(braket
l_int|0
)braket
)paren
op_star
id|autotags
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_and
op_logical_neg
id|has_merge
op_logical_and
id|ref_map
op_logical_and
op_logical_neg
id|remote-&gt;fetch
(braket
l_int|0
)braket
dot
id|pattern
)paren
id|ref_map-&gt;merge
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * if the remote we&squot;re fetching from is the same&n;&t;&t;&t; * as given in branch.&lt;name&gt;.remote, we add the&n;&t;&t;&t; * ref given in branch.&lt;name&gt;.merge, too.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|has_merge
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|branch-&gt;remote_name
comma
id|remote-&gt;name
)paren
)paren
id|add_merge_config
c_func
(paren
op_amp
id|ref_map
comma
id|remote_refs
comma
id|branch
comma
op_amp
id|tail
)paren
suffix:semicolon
)brace
r_else
(brace
id|ref_map
op_assign
id|get_remote_ref
c_func
(paren
id|remote_refs
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref_map
)paren
id|die
c_func
(paren
l_string|&quot;Couldn&squot;t find remote ref HEAD&quot;
)paren
suffix:semicolon
id|ref_map-&gt;merge
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|ref_remove_duplicates
c_func
(paren
id|ref_map
)paren
suffix:semicolon
r_return
id|ref_map
suffix:semicolon
)brace
DECL|function|s_update_ref
r_static
r_int
id|s_update_ref
c_func
(paren
r_const
r_char
op_star
id|action
comma
r_struct
id|ref
op_star
id|ref
comma
r_int
id|check_old
)paren
(brace
r_char
id|msg
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|rla
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_REFLOG_ACTION&quot;
)paren
suffix:semicolon
r_static
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rla
)paren
id|rla
op_assign
id|default_rla.buf
suffix:semicolon
id|snprintf
c_func
(paren
id|msg
comma
r_sizeof
(paren
id|msg
)paren
comma
l_string|&quot;%s: %s&quot;
comma
id|rla
comma
id|action
)paren
suffix:semicolon
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref-&gt;name
comma
id|check_old
ques
c_cond
id|ref-&gt;old_sha1
suffix:colon
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
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|ref-&gt;new_sha1
comma
id|msg
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|SUMMARY_WIDTH
mdefine_line|#define SUMMARY_WIDTH (2 * DEFAULT_ABBREV + 3)
DECL|macro|REFCOL_WIDTH
mdefine_line|#define REFCOL_WIDTH  10
DECL|function|update_local_ref
r_static
r_int
id|update_local_ref
c_func
(paren
r_struct
id|ref
op_star
id|ref
comma
r_const
r_char
op_star
id|remote
comma
r_int
id|verbose
comma
r_char
op_star
id|display
)paren
(brace
r_struct
id|commit
op_star
id|current
op_assign
l_int|NULL
comma
op_star
id|updated
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_struct
id|branch
op_star
id|current_branch
op_assign
id|branch_get
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_const
r_char
op_star
id|pretty_ref
op_assign
id|ref-&gt;name
op_plus
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/heads/&quot;
)paren
ques
c_cond
l_int|11
suffix:colon
op_logical_neg
id|prefixcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/tags/&quot;
)paren
ques
c_cond
l_int|10
suffix:colon
op_logical_neg
id|prefixcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/remotes/&quot;
)paren
ques
c_cond
l_int|13
suffix:colon
l_int|0
)paren
suffix:semicolon
op_star
id|display
op_assign
l_int|0
suffix:semicolon
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|ref-&gt;new_sha1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;object %s not found&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;new_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|ref-&gt;name
)paren
(brace
multiline_comment|/* Not storing */
r_if
c_cond
(paren
id|verbose
)paren
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;* branch %s -&gt; FETCH_HEAD&quot;
comma
id|remote
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|ref-&gt;old_sha1
comma
id|ref-&gt;new_sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;= %-*s %-*s -&gt; %s&quot;
comma
id|SUMMARY_WIDTH
comma
l_string|&quot;[up to date]&quot;
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current_branch
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ref-&gt;name
comma
id|current_branch-&gt;name
)paren
op_logical_and
op_logical_neg
(paren
id|update_head_ok
op_logical_or
id|is_bare_repository
c_func
(paren
)paren
)paren
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * If this is the head, and it&squot;s not okay to update&n;&t;&t; * the head, and the old value of the head isn&squot;t empty...&n;&t;&t; */
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;! %-*s %-*s -&gt; %s  (can&squot;t fetch in current branch)&quot;
comma
id|SUMMARY_WIDTH
comma
l_string|&quot;[rejected]&quot;
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|ref-&gt;old_sha1
)paren
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/tags/&quot;
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;- %-*s %-*s -&gt; %s&quot;
comma
id|SUMMARY_WIDTH
comma
l_string|&quot;[tag update]&quot;
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
id|s_update_ref
c_func
(paren
l_string|&quot;updating tag&quot;
comma
id|ref
comma
l_int|0
)paren
suffix:semicolon
)brace
id|current
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|ref-&gt;old_sha1
comma
l_int|1
)paren
suffix:semicolon
id|updated
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|ref-&gt;new_sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current
op_logical_or
op_logical_neg
id|updated
)paren
(brace
r_const
r_char
op_star
id|msg
suffix:semicolon
r_const
r_char
op_star
id|what
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
)paren
)paren
(brace
id|msg
op_assign
l_string|&quot;storing tag&quot;
suffix:semicolon
id|what
op_assign
l_string|&quot;[new tag]&quot;
suffix:semicolon
)brace
r_else
(brace
id|msg
op_assign
l_string|&quot;storing head&quot;
suffix:semicolon
id|what
op_assign
l_string|&quot;[new branch]&quot;
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;* %-*s %-*s -&gt; %s&quot;
comma
id|SUMMARY_WIDTH
comma
id|what
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
id|s_update_ref
c_func
(paren
id|msg
comma
id|ref
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|in_merge_bases
c_func
(paren
id|current
comma
op_amp
id|updated
comma
l_int|1
)paren
)paren
(brace
r_char
id|quickref
(braket
l_int|83
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|quickref
comma
id|find_unique_abbrev
c_func
(paren
id|current-&gt;object.sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|quickref
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|quickref
comma
id|find_unique_abbrev
c_func
(paren
id|ref-&gt;new_sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;  %-*s %-*s -&gt; %s&quot;
comma
id|SUMMARY_WIDTH
comma
id|quickref
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
id|s_update_ref
c_func
(paren
l_string|&quot;fast forward&quot;
comma
id|ref
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|force
op_logical_or
id|ref-&gt;force
)paren
(brace
r_char
id|quickref
(braket
l_int|84
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|quickref
comma
id|find_unique_abbrev
c_func
(paren
id|current-&gt;object.sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|quickref
comma
l_string|&quot;...&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|quickref
comma
id|find_unique_abbrev
c_func
(paren
id|ref-&gt;new_sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;+ %-*s %-*s -&gt; %s  (forced update)&quot;
comma
id|SUMMARY_WIDTH
comma
id|quickref
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
id|s_update_ref
c_func
(paren
l_string|&quot;forced-update&quot;
comma
id|ref
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
c_func
(paren
id|display
comma
l_string|&quot;! %-*s %-*s -&gt; %s  (non fast forward)&quot;
comma
id|SUMMARY_WIDTH
comma
l_string|&quot;[rejected]&quot;
comma
id|REFCOL_WIDTH
comma
id|remote
comma
id|pretty_ref
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|store_updated_refs
r_static
r_int
id|store_updated_refs
c_func
(paren
r_const
r_char
op_star
id|url
comma
r_struct
id|ref
op_star
id|ref_map
)paren
(brace
id|FILE
op_star
id|fp
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
id|url_len
comma
id|i
comma
id|note_len
comma
id|shown_url
op_assign
l_int|0
suffix:semicolon
r_char
id|note
(braket
l_int|1024
)braket
suffix:semicolon
r_const
r_char
op_star
id|what
comma
op_star
id|kind
suffix:semicolon
r_struct
id|ref
op_star
id|rm
suffix:semicolon
r_char
op_star
id|filename
op_assign
id|git_path
c_func
(paren
l_string|&quot;FETCH_HEAD&quot;
)paren
suffix:semicolon
id|fp
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;a&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot open %s: %s&bslash;n&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rm
op_assign
id|ref_map
suffix:semicolon
id|rm
suffix:semicolon
id|rm
op_assign
id|rm-&gt;next
)paren
(brace
r_struct
id|ref
op_star
id|ref
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|rm-&gt;peer_ref
)paren
(brace
id|ref
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ref
)paren
op_plus
id|strlen
c_func
(paren
id|rm-&gt;peer_ref-&gt;name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ref-&gt;name
comma
id|rm-&gt;peer_ref-&gt;name
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ref-&gt;old_sha1
comma
id|rm-&gt;peer_ref-&gt;old_sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|rm-&gt;old_sha1
)paren
suffix:semicolon
id|ref-&gt;force
op_assign
id|rm-&gt;peer_ref-&gt;force
suffix:semicolon
)brace
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|rm-&gt;old_sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
id|rm-&gt;merge
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rm-&gt;name
comma
l_string|&quot;HEAD&quot;
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|what
op_assign
l_string|&quot;&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|rm-&gt;name
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;branch&quot;
suffix:semicolon
id|what
op_assign
id|rm-&gt;name
op_plus
l_int|11
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|rm-&gt;name
comma
l_string|&quot;refs/tags/&quot;
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;tag&quot;
suffix:semicolon
id|what
op_assign
id|rm-&gt;name
op_plus
l_int|10
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|rm-&gt;name
comma
l_string|&quot;refs/remotes/&quot;
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;remote branch&quot;
suffix:semicolon
id|what
op_assign
id|rm-&gt;name
op_plus
l_int|13
suffix:semicolon
)brace
r_else
(brace
id|kind
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|what
op_assign
id|rm-&gt;name
suffix:semicolon
)brace
id|url_len
op_assign
id|strlen
c_func
(paren
id|url
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|url_len
l_int|1
suffix:semicolon
id|url
(braket
id|i
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
l_int|0
op_le
id|i
suffix:semicolon
id|i
op_decrement
)paren
suffix:semicolon
id|url_len
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|4
OL
id|i
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;.git&quot;
comma
id|url
op_plus
id|i
l_int|3
comma
l_int|4
)paren
)paren
id|url_len
op_assign
id|i
l_int|3
suffix:semicolon
id|note_len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|what
)paren
(brace
r_if
c_cond
(paren
op_star
id|kind
)paren
id|note_len
op_add_assign
id|sprintf
c_func
(paren
id|note
op_plus
id|note_len
comma
l_string|&quot;%s &quot;
comma
id|kind
)paren
suffix:semicolon
id|note_len
op_add_assign
id|sprintf
c_func
(paren
id|note
op_plus
id|note_len
comma
l_string|&quot;&squot;%s&squot; of &quot;
comma
id|what
)paren
suffix:semicolon
)brace
id|note_len
op_add_assign
id|sprintf
c_func
(paren
id|note
op_plus
id|note_len
comma
l_string|&quot;%.*s&quot;
comma
id|url_len
comma
id|url
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&bslash;t%s&bslash;t%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit
ques
c_cond
id|commit-&gt;object.sha1
suffix:colon
id|rm-&gt;old_sha1
)paren
comma
id|rm-&gt;merge
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not-for-merge&quot;
comma
id|note
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref
)paren
(brace
id|update_local_ref
c_func
(paren
id|ref
comma
id|what
comma
id|verbose
comma
id|note
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|note
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|shown_url
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;From %.*s&bslash;n&quot;
comma
id|url_len
comma
id|url
)paren
suffix:semicolon
id|shown_url
op_assign
l_int|1
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; %s&bslash;n&quot;
comma
id|note
)paren
suffix:semicolon
)brace
)brace
)brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We would want to bypass the object transfer altogether if&n; * everything we are going to fetch already exists and connected&n; * locally.&n; *&n; * The refs we are going to fetch are in to_fetch (nr_heads in&n; * total).  If running&n; *&n; *  $ git-rev-list --objects to_fetch[0] to_fetch[1] ... --not --all&n; *&n; * does not error out, that means everything reachable from the&n; * refs we are going to fetch exists and is connected to some of&n; * our existing refs.&n; */
DECL|function|quickfetch
r_static
r_int
id|quickfetch
c_func
(paren
r_struct
id|ref
op_star
id|ref_map
)paren
(brace
r_struct
id|child_process
id|revlist
suffix:semicolon
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_char
op_star
op_star
id|argv
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * If we are deepening a shallow clone we already have these&n;&t; * objects reachable.  Running rev-list here will return with&n;&t; * a good (0) exit status and we&squot;ll bypass the fetch that we&n;&t; * really need to perform.  Claiming failure now will ensure&n;&t; * we perform the network exchange to deepen our history.&n;&t; */
r_if
c_cond
(paren
id|depth
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|ref
op_assign
id|ref_map
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
l_int|0
suffix:semicolon
id|argv
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|argv
)paren
op_star
(paren
id|i
op_plus
l_int|6
)paren
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;rev-list&quot;
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;--quiet&quot;
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;--objects&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|ref_map
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;--not&quot;
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;--all&quot;
)paren
suffix:semicolon
id|argv
(braket
id|i
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|revlist
comma
l_int|0
comma
r_sizeof
(paren
id|revlist
)paren
)paren
suffix:semicolon
id|revlist.argv
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
id|argv
suffix:semicolon
id|revlist.git_cmd
op_assign
l_int|1
suffix:semicolon
id|revlist.no_stdin
op_assign
l_int|1
suffix:semicolon
id|revlist.no_stdout
op_assign
l_int|1
suffix:semicolon
id|revlist.no_stderr
op_assign
l_int|1
suffix:semicolon
id|err
op_assign
id|run_command
c_func
(paren
op_amp
id|revlist
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|argv
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|argv
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|fetch_refs
r_static
r_int
id|fetch_refs
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_struct
id|ref
op_star
id|ref_map
)paren
(brace
r_int
id|ret
op_assign
id|quickfetch
c_func
(paren
id|ref_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|ret
op_assign
id|transport_fetch_refs
c_func
(paren
id|transport
comma
id|ref_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_or_assign
id|store_updated_refs
c_func
(paren
id|transport-&gt;url
comma
id|ref_map
)paren
suffix:semicolon
id|transport_unlock_pack
c_func
(paren
id|transport
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|add_existing
r_static
r_int
id|add_existing
c_func
(paren
r_const
r_char
op_star
id|refname
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cbdata
)paren
(brace
r_struct
id|path_list
op_star
id|list
op_assign
(paren
r_struct
id|path_list
op_star
)paren
id|cbdata
suffix:semicolon
id|path_list_insert
c_func
(paren
id|refname
comma
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|find_non_local_tags
r_static
r_struct
id|ref
op_star
id|find_non_local_tags
c_func
(paren
r_struct
id|transport
op_star
id|transport
)paren
(brace
r_static
r_struct
id|path_list
id|existing_refs
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|path_list
id|new_refs
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_char
op_star
id|ref_name
suffix:semicolon
r_int
id|ref_name_len
suffix:semicolon
r_const
r_int
r_char
op_star
id|ref_sha1
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|tag_ref
suffix:semicolon
r_struct
id|ref
op_star
id|rm
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
id|ref_map
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
op_star
id|tail
op_assign
op_amp
id|ref_map
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|ref
suffix:semicolon
id|for_each_ref
c_func
(paren
id|add_existing
comma
op_amp
id|existing_refs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/tags&quot;
)paren
)paren
r_continue
suffix:semicolon
id|ref_name
op_assign
id|xstrdup
c_func
(paren
id|ref-&gt;name
)paren
suffix:semicolon
id|ref_name_len
op_assign
id|strlen
c_func
(paren
id|ref_name
)paren
suffix:semicolon
id|ref_sha1
op_assign
id|ref-&gt;old_sha1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ref_name
op_plus
id|ref_name_len
l_int|3
comma
l_string|&quot;^{}&quot;
)paren
)paren
(brace
id|ref_name
(braket
id|ref_name_len
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|tag_ref
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tag_ref
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|tag_ref-&gt;name
comma
id|ref_name
)paren
)paren
(brace
id|ref_sha1
op_assign
id|tag_ref-&gt;old_sha1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tag_ref
op_assign
id|tag_ref-&gt;next
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|path_list_has_path
c_func
(paren
op_amp
id|existing_refs
comma
id|ref_name
)paren
op_logical_and
op_logical_neg
id|path_list_has_path
c_func
(paren
op_amp
id|new_refs
comma
id|ref_name
)paren
op_logical_and
id|has_sha1_file
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
(brace
id|path_list_insert
c_func
(paren
id|ref_name
comma
op_amp
id|new_refs
)paren
suffix:semicolon
id|rm
op_assign
id|alloc_ref
c_func
(paren
id|strlen
c_func
(paren
id|ref_name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|rm-&gt;name
comma
id|ref_name
)paren
suffix:semicolon
id|rm-&gt;peer_ref
op_assign
id|alloc_ref
c_func
(paren
id|strlen
c_func
(paren
id|ref_name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|rm-&gt;peer_ref-&gt;name
comma
id|ref_name
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|rm-&gt;old_sha1
comma
id|ref_sha1
)paren
suffix:semicolon
op_star
id|tail
op_assign
id|rm
suffix:semicolon
id|tail
op_assign
op_amp
id|rm-&gt;next
suffix:semicolon
)brace
id|free
c_func
(paren
id|ref_name
)paren
suffix:semicolon
)brace
r_return
id|ref_map
suffix:semicolon
)brace
DECL|function|do_fetch
r_static
r_int
id|do_fetch
c_func
(paren
r_struct
id|transport
op_star
id|transport
comma
r_struct
id|refspec
op_star
id|refs
comma
r_int
id|ref_count
)paren
(brace
r_struct
id|ref
op_star
id|ref_map
suffix:semicolon
r_struct
id|ref
op_star
id|rm
suffix:semicolon
r_int
id|autotags
op_assign
(paren
id|transport-&gt;remote-&gt;fetch_tags
op_eq
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transport-&gt;remote-&gt;fetch_tags
op_eq
l_int|2
op_logical_and
id|tags
op_ne
id|TAGS_UNSET
)paren
id|tags
op_assign
id|TAGS_SET
suffix:semicolon
r_if
c_cond
(paren
id|transport-&gt;remote-&gt;fetch_tags
op_eq
l_int|1
)paren
id|tags
op_assign
id|TAGS_UNSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transport-&gt;get_refs_list
op_logical_or
op_logical_neg
id|transport-&gt;fetch
)paren
id|die
c_func
(paren
l_string|&quot;Don&squot;t know how to fetch from %s&quot;
comma
id|transport-&gt;url
)paren
suffix:semicolon
multiline_comment|/* if not appending, truncate FETCH_HEAD */
r_if
c_cond
(paren
op_logical_neg
id|append
)paren
(brace
r_char
op_star
id|filename
op_assign
id|git_path
c_func
(paren
l_string|&quot;FETCH_HEAD&quot;
)paren
suffix:semicolon
id|FILE
op_star
id|fp
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot open %s: %s&bslash;n&quot;
comma
id|filename
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
)brace
id|ref_map
op_assign
id|get_ref_map
c_func
(paren
id|transport
comma
id|refs
comma
id|ref_count
comma
id|tags
comma
op_amp
id|autotags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rm
op_assign
id|ref_map
suffix:semicolon
id|rm
suffix:semicolon
id|rm
op_assign
id|rm-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|rm-&gt;peer_ref
)paren
id|read_ref
c_func
(paren
id|rm-&gt;peer_ref-&gt;name
comma
id|rm-&gt;peer_ref-&gt;old_sha1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fetch_refs
c_func
(paren
id|transport
comma
id|ref_map
)paren
)paren
(brace
id|free_refs
c_func
(paren
id|ref_map
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|free_refs
c_func
(paren
id|ref_map
)paren
suffix:semicolon
multiline_comment|/* if neither --no-tags nor --tags was specified, do automated tag&n;&t; * following ... */
r_if
c_cond
(paren
id|tags
op_eq
id|TAGS_DEFAULT
op_logical_and
id|autotags
)paren
(brace
id|ref_map
op_assign
id|find_non_local_tags
c_func
(paren
id|transport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref_map
)paren
(brace
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_DEPTH
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|fetch_refs
c_func
(paren
id|transport
comma
id|ref_map
)paren
suffix:semicolon
)brace
id|free_refs
c_func
(paren
id|ref_map
)paren
suffix:semicolon
)brace
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_option
r_static
r_void
id|set_option
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_int
id|r
op_assign
id|transport_set_option
c_func
(paren
id|transport
comma
id|name
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Option &bslash;&quot;%s&bslash;&quot; value &bslash;&quot;%s&bslash;&quot; is not valid for %s&bslash;n&quot;
comma
id|name
comma
id|value
comma
id|transport-&gt;url
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OG
l_int|0
)paren
id|warning
c_func
(paren
l_string|&quot;Option &bslash;&quot;%s&bslash;&quot; is ignored for %s&bslash;n&quot;
comma
id|name
comma
id|transport-&gt;url
)paren
suffix:semicolon
)brace
DECL|function|cmd_fetch
r_int
id|cmd_fetch
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
id|remote
op_star
id|remote
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
r_const
r_char
op_star
op_star
id|refs
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ref_nr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Record the command line for the reflog */
id|strbuf_addstr
c_func
(paren
op_amp
id|default_rla
comma
l_string|&quot;fetch&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
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
id|strbuf_addf
c_func
(paren
op_amp
id|default_rla
comma
l_string|&quot; %s&quot;
comma
id|argv
(braket
id|i
)braket
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
id|builtin_fetch_options
comma
id|builtin_fetch_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
)paren
id|remote
op_assign
id|remote_get
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_else
id|remote
op_assign
id|remote_get
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|remote-&gt;url
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
op_ge
l_int|2
)paren
id|transport-&gt;verbose
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|quiet
)paren
id|transport-&gt;verbose
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|upload_pack
)paren
id|set_option
c_func
(paren
id|TRANS_OPT_UPLOADPACK
comma
id|upload_pack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|keep
)paren
id|set_option
c_func
(paren
id|TRANS_OPT_KEEP
comma
l_string|&quot;yes&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
)paren
id|set_option
c_func
(paren
id|TRANS_OPT_DEPTH
comma
id|depth
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transport-&gt;url
)paren
id|die
c_func
(paren
l_string|&quot;Where do you want to fetch from today?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
(brace
r_int
id|j
op_assign
l_int|0
suffix:semicolon
id|refs
op_assign
id|xcalloc
c_func
(paren
id|argc
op_plus
l_int|1
comma
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
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
l_string|&quot;tag&quot;
)paren
)paren
(brace
r_char
op_star
id|ref
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|ref
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|argv
(braket
id|i
)braket
)paren
op_star
l_int|2
op_plus
l_int|22
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ref
comma
l_string|&quot;refs/tags/&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|ref
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|ref
comma
l_string|&quot;:refs/tags/&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|ref
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|refs
(braket
id|j
op_increment
)braket
op_assign
id|ref
suffix:semicolon
)brace
r_else
id|refs
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
id|refs
(braket
id|j
)braket
op_assign
l_int|NULL
suffix:semicolon
id|ref_nr
op_assign
id|j
suffix:semicolon
)brace
id|signal
c_func
(paren
id|SIGINT
comma
id|unlock_pack_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|unlock_pack
)paren
suffix:semicolon
r_return
id|do_fetch
c_func
(paren
id|transport
comma
id|parse_ref_spec
c_func
(paren
id|ref_nr
comma
id|refs
)paren
comma
id|ref_nr
)paren
suffix:semicolon
)brace
eof
