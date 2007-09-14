multiline_comment|/*&n; * &quot;git fetch&quot;&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;transport.h&quot;
DECL|variable|fetch_usage
r_static
r_const
r_char
id|fetch_usage
(braket
)braket
op_assign
l_string|&quot;git-fetch [-a | --append] [--upload-pack &lt;upload-pack&gt;] [-f | --force] [--no-tags] [-t | --tags] [-k | --keep] [-u | --update-head-ok] [--depth &lt;depth&gt;] [-v | --verbose] [&lt;repository&gt; &lt;refspec&gt;...]&quot;
suffix:semicolon
DECL|variable|append
DECL|variable|force
DECL|variable|tags
DECL|variable|no_tags
DECL|variable|update_head_ok
DECL|variable|verbose
DECL|variable|quiet
r_static
r_int
id|append
comma
id|force
comma
id|tags
comma
id|no_tags
comma
id|update_head_ok
comma
id|verbose
comma
id|quiet
suffix:semicolon
DECL|variable|unpacklimit
r_static
r_int
id|unpacklimit
suffix:semicolon
DECL|variable|default_rla
r_static
r_char
op_star
id|default_rla
op_assign
l_int|NULL
suffix:semicolon
DECL|function|find_merge_config
r_static
r_void
id|find_merge_config
c_func
(paren
r_struct
id|ref
op_star
id|ref_map
comma
r_struct
id|remote
op_star
id|remote
)paren
(brace
r_struct
id|ref
op_star
id|rm
op_assign
id|ref_map
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
op_logical_neg
id|branch_has_merge_config
c_func
(paren
id|branch
)paren
)paren
(brace
r_if
c_cond
(paren
id|remote
op_logical_and
id|remote-&gt;fetch
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|remote-&gt;fetch
(braket
l_int|0
)braket
dot
id|src
comma
id|rm-&gt;name
)paren
)paren
id|rm-&gt;merge
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|branch_merges
c_func
(paren
id|branch
comma
id|rm-&gt;name
)paren
)paren
id|rm-&gt;merge
op_assign
l_int|1
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|remote-&gt;fetch_refspec_nr
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
)brace
id|find_merge_config
c_func
(paren
id|ref_map
comma
id|remote
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
id|ref_map-&gt;merge
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|ref_map
suffix:semicolon
)brace
DECL|function|show_new
r_static
r_void
id|show_new
c_func
(paren
r_enum
id|object_type
id|type
comma
r_int
r_char
op_star
id|sha1_new
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;  %s: %s&bslash;n&quot;
comma
r_typename
(paren
id|type
)paren
comma
id|find_unique_abbrev
c_func
(paren
id|sha1_new
comma
id|DEFAULT_ABBREV
)paren
)paren
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
id|default_rla
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
id|note
comma
r_int
id|verbose
)paren
(brace
r_char
id|oldh
(braket
l_int|41
)braket
comma
id|newh
(braket
l_int|41
)braket
suffix:semicolon
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
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* fetched %s&bslash;n&quot;
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|ref-&gt;new_sha1
)paren
suffix:semicolon
)brace
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
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: same as %s&bslash;n&quot;
comma
id|ref-&gt;name
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|ref-&gt;new_sha1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; * %s: Cannot fetch into the current branch.&bslash;n&quot;
comma
id|ref-&gt;name
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: updating with %s&bslash;n&quot;
comma
id|ref-&gt;name
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|ref-&gt;new_sha1
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
id|lookup_commit_reference
c_func
(paren
id|ref-&gt;old_sha1
)paren
suffix:semicolon
id|updated
op_assign
id|lookup_commit_reference
c_func
(paren
id|ref-&gt;new_sha1
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
r_char
op_star
id|msg
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
id|msg
op_assign
l_string|&quot;storing tag&quot;
suffix:semicolon
r_else
id|msg
op_assign
l_string|&quot;storing head&quot;
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: storing %s&bslash;n&quot;
comma
id|ref-&gt;name
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|ref-&gt;new_sha1
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
id|strcpy
c_func
(paren
id|oldh
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
id|strcpy
c_func
(paren
id|newh
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: fast forward to %s&bslash;n&quot;
comma
id|ref-&gt;name
comma
id|note
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;  old..new: %s..%s&bslash;n&quot;
comma
id|oldh
comma
id|newh
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
r_if
c_cond
(paren
op_logical_neg
id|force
op_logical_and
op_logical_neg
id|ref-&gt;force
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: not updating to non-fast forward %s&bslash;n&quot;
comma
id|ref-&gt;name
comma
id|note
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;  old...new: %s...%s&bslash;n&quot;
comma
id|oldh
comma
id|newh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: forcing update to non-fast forward %s&bslash;n&quot;
comma
id|ref-&gt;name
comma
id|note
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;  old...new: %s...%s&bslash;n&quot;
comma
id|oldh
comma
id|newh
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
DECL|function|store_updated_refs
r_static
r_void
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
id|fp
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;FETCH_HEAD&quot;
)paren
comma
l_string|&quot;a&quot;
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
id|lookup_commit_reference
c_func
(paren
id|rm-&gt;old_sha1
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
id|update_local_ref
c_func
(paren
id|ref
comma
id|note
comma
id|verbose
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|fp
)paren
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
id|store_updated_refs
c_func
(paren
id|transport-&gt;url
comma
id|ref_map
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
comma
r_struct
id|ref
op_star
id|fetch_map
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
r_int
r_char
op_star
id|ref_sha1
suffix:semicolon
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
id|lookup_object
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Auto-following %s&bslash;n&quot;
comma
id|ref_name
)paren
suffix:semicolon
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
comma
op_star
id|fetch_map
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
op_logical_neg
id|no_tags
)paren
id|tags
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|transport-&gt;remote-&gt;fetch_tags
op_eq
l_int|1
)paren
id|no_tags
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transport-&gt;ops
op_logical_or
op_logical_neg
id|transport-&gt;ops-&gt;get_refs_list
op_logical_or
op_logical_neg
(paren
id|transport-&gt;ops-&gt;fetch_refs
op_logical_or
id|transport-&gt;ops-&gt;fetch_objs
)paren
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
id|fclose
c_func
(paren
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;FETCH_HEAD&quot;
)paren
comma
l_string|&quot;w&quot;
)paren
)paren
suffix:semicolon
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
id|printf
c_func
(paren
l_string|&quot;%s : %s&bslash;n&quot;
comma
id|rm-&gt;name
comma
id|rm-&gt;peer_ref
ques
c_cond
id|rm-&gt;peer_ref-&gt;name
suffix:colon
l_int|NULL
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  &lt; %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|rm-&gt;old_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rm-&gt;peer_ref
)paren
id|printf
c_func
(paren
l_string|&quot;  &gt; %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|rm-&gt;peer_ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rm-&gt;peer_ref
op_logical_or
id|hashcmp
c_func
(paren
id|rm-&gt;old_sha1
comma
id|rm-&gt;peer_ref-&gt;old_sha1
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s needs update.&bslash;n&quot;
comma
id|rm-&gt;name
)paren
suffix:semicolon
)brace
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
id|fetch_map
op_assign
id|ref_map
suffix:semicolon
multiline_comment|/* if neither --no-tags nor --tags was specified, do automated tag&n;&t; * following ... */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tags
op_logical_or
id|no_tags
)paren
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
comma
id|fetch_map
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
id|free_refs
c_func
(paren
id|fetch_map
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_config
r_static
r_int
id|fetch_config
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
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;fetch.unpacklimit&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|unpacklimit
op_assign
id|git_config_int
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;transfer.unpacklimit&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|unpacklimit
op_assign
id|git_config_int
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
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
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|rla_offset
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
r_int
id|cmd_len
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|depth
op_assign
l_int|NULL
comma
op_star
id|upload_pack
op_assign
l_int|NULL
suffix:semicolon
r_int
id|keep
op_assign
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|fetch_config
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
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
id|cmd_len
op_add_assign
id|strlen
c_func
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--append&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-a&quot;
)paren
)paren
(brace
id|append
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--upload-pack=&quot;
)paren
)paren
(brace
id|upload_pack
op_assign
id|arg
op_plus
l_int|14
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--upload-pack&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|usage
c_func
(paren
id|fetch_usage
)paren
suffix:semicolon
id|upload_pack
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--force&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|force
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--no-tags&quot;
)paren
)paren
(brace
id|no_tags
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--tags&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-t&quot;
)paren
)paren
(brace
id|tags
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--keep&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-k&quot;
)paren
)paren
(brace
id|keep
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--update-head-ok&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-u&quot;
)paren
)paren
(brace
id|update_head_ok
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--depth=&quot;
)paren
)paren
(brace
id|depth
op_assign
id|arg
op_plus
l_int|8
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--depth&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|argc
)paren
id|usage
c_func
(paren
id|fetch_usage
)paren
suffix:semicolon
id|depth
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--quiet&quot;
)paren
)paren
(brace
id|quiet
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--verbose&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|verbose
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|fetch_usage
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OL
id|argc
suffix:semicolon
id|j
op_increment
)paren
id|cmd_len
op_add_assign
id|strlen
c_func
(paren
id|argv
(braket
id|j
)braket
)paren
suffix:semicolon
id|default_rla
op_assign
id|xmalloc
c_func
(paren
id|cmd_len
op_plus
l_int|5
op_plus
id|argc
op_plus
l_int|1
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|default_rla
comma
l_string|&quot;fetch&quot;
)paren
suffix:semicolon
id|rla_offset
op_assign
id|strlen
c_func
(paren
id|default_rla
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|argc
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|default_rla
op_plus
id|rla_offset
comma
l_string|&quot; %s&quot;
comma
id|argv
(braket
id|j
)braket
)paren
suffix:semicolon
id|rla_offset
op_add_assign
id|strlen
c_func
(paren
id|argv
(braket
id|j
)braket
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|argc
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
id|i
op_increment
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
id|remote-&gt;uri
(braket
l_int|0
)braket
comma
l_int|1
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|upload_pack
)paren
id|transport_set_option
c_func
(paren
id|transport
comma
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
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_KEEP
comma
l_string|&quot;yes&quot;
)paren
suffix:semicolon
id|transport_set_option
c_func
(paren
id|transport
comma
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
id|i
OL
id|argc
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
id|i
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
r_while
c_loop
(paren
id|i
OL
id|argc
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
id|i
op_increment
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
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|refs
(braket
id|j
)braket
suffix:semicolon
id|j
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;ref: %s&bslash;n&quot;
comma
id|refs
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
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
