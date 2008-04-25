macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|builtin_remote_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_remote_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git remote&quot;
comma
l_string|&quot;git remote add &lt;name&gt; &lt;url&gt;&quot;
comma
l_string|&quot;git remote rm &lt;name&gt;&quot;
comma
l_string|&quot;git remote show &lt;name&gt;&quot;
comma
l_string|&quot;git remote prune &lt;name&gt;&quot;
comma
l_string|&quot;git remote update [group]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
r_static
r_int
id|show_all
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|postfixcmp
r_static
r_inline
r_int
id|postfixcmp
c_func
(paren
r_const
r_char
op_star
id|string
comma
r_const
r_char
op_star
id|postfix
)paren
(brace
r_int
id|len1
op_assign
id|strlen
c_func
(paren
id|string
)paren
comma
id|len2
op_assign
id|strlen
c_func
(paren
id|postfix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len1
OL
id|len2
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|string
op_plus
id|len1
id|len2
comma
id|postfix
)paren
suffix:semicolon
)brace
DECL|function|skip_prefix
r_static
r_inline
r_const
r_char
op_star
id|skip_prefix
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
id|prefix
)paren
(brace
r_return
op_logical_neg
id|name
ques
c_cond
l_string|&quot;&quot;
suffix:colon
id|prefixcmp
c_func
(paren
id|name
comma
id|prefix
)paren
ques
c_cond
id|name
suffix:colon
id|name
op_plus
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
)brace
DECL|function|opt_parse_track
r_static
r_int
id|opt_parse_track
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
op_logical_neg
)paren
(brace
r_struct
id|path_list
op_star
id|list
op_assign
id|opt-&gt;value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
)paren
id|path_list_clear
c_func
(paren
id|list
comma
l_int|0
)paren
suffix:semicolon
r_else
id|path_list_append
c_func
(paren
id|arg
comma
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_remote
r_static
r_int
id|fetch_remote
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;fetch&quot;
comma
id|name
comma
l_int|NULL
)brace
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Updating %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|argv
comma
id|RUN_GIT_CMD
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not fetch %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add
r_static
r_int
id|add
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
id|fetch
op_assign
l_int|0
comma
id|mirror
op_assign
l_int|0
suffix:semicolon
r_struct
id|path_list
id|track
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_const
r_char
op_star
id|master
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|strbuf
id|buf
comma
id|buf2
suffix:semicolon
r_const
r_char
op_star
id|name
comma
op_star
id|url
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_GROUP
c_func
(paren
l_string|&quot;add specific options&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;fetch&quot;
comma
op_amp
id|fetch
comma
l_string|&quot;fetch the remote branches&quot;
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_char|&squot;t&squot;
comma
l_string|&quot;track&quot;
comma
op_amp
id|track
comma
l_string|&quot;branch&quot;
comma
l_string|&quot;branch(es) to track&quot;
comma
id|opt_parse_track
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;m&squot;
comma
l_string|&quot;master&quot;
comma
op_amp
id|master
comma
l_string|&quot;branch&quot;
comma
l_string|&quot;master branch&quot;
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
l_string|&quot;no separate remotes&quot;
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
id|builtin_remote_usage
comma
l_int|0
)paren
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
id|builtin_remote_usage
comma
id|options
)paren
suffix:semicolon
id|name
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|url
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|remote
op_assign
id|remote_get
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote
op_logical_and
(paren
id|remote-&gt;url_nr
OG
l_int|1
op_logical_or
id|strcmp
c_func
(paren
id|name
comma
id|remote-&gt;url
(braket
l_int|0
)braket
)paren
op_logical_or
id|remote-&gt;fetch_refspec_nr
)paren
)paren
id|die
c_func
(paren
l_string|&quot;remote %s already exists.&quot;
comma
id|name
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf2
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf2
comma
l_string|&quot;refs/heads/test:refs/remotes/%s/test&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|valid_fetch_refspec
c_func
(paren
id|buf2.buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid remote name&quot;
comma
id|name
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;remote.%s.url&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_set
c_func
(paren
id|buf.buf
comma
id|url
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;remote.%s.fetch&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|track.nr
op_eq
l_int|0
)paren
id|path_list_append
c_func
(paren
l_string|&quot;*&quot;
comma
op_amp
id|track
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
id|track.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list_item
op_star
id|item
op_assign
id|track.items
op_plus
id|i
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf2
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf2
comma
l_char|&squot;+&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mirror
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|buf2
comma
l_string|&quot;refs/%s:refs/%s&quot;
comma
id|item-&gt;path
comma
id|item-&gt;path
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
op_amp
id|buf2
comma
l_string|&quot;refs/heads/%s:refs/remotes/%s/%s&quot;
comma
id|item-&gt;path
comma
id|name
comma
id|item-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_set_multivar
c_func
(paren
id|buf.buf
comma
id|buf2.buf
comma
l_string|&quot;^$&quot;
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fetch
op_logical_and
id|fetch_remote
c_func
(paren
id|name
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|master
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;refs/remotes/%s/HEAD&quot;
comma
id|name
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|buf2
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf2
comma
l_string|&quot;refs/remotes/%s/%s&quot;
comma
id|name
comma
id|master
)paren
suffix:semicolon
r_if
c_cond
(paren
id|create_symref
c_func
(paren
id|buf.buf
comma
id|buf2.buf
comma
l_string|&quot;remote add&quot;
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not setup master &squot;%s&squot;&quot;
comma
id|master
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf2
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|track
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|branch_info
r_struct
id|branch_info
(brace
DECL|member|remote
r_char
op_star
id|remote
suffix:semicolon
DECL|member|merge
r_struct
id|path_list
id|merge
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|branch_list
r_static
r_struct
id|path_list
id|branch_list
suffix:semicolon
DECL|function|config_read_branches
r_static
r_int
id|config_read_branches
c_func
(paren
r_const
r_char
op_star
id|key
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|key
comma
l_string|&quot;branch.&quot;
)paren
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
r_struct
id|branch_info
op_star
id|info
suffix:semicolon
r_enum
(brace
id|REMOTE
comma
id|MERGE
)brace
id|type
suffix:semicolon
id|key
op_add_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|postfixcmp
c_func
(paren
id|key
comma
l_string|&quot;.remote&quot;
)paren
)paren
(brace
id|name
op_assign
id|xstrndup
c_func
(paren
id|key
comma
id|strlen
c_func
(paren
id|key
)paren
l_int|7
)paren
suffix:semicolon
id|type
op_assign
id|REMOTE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|postfixcmp
c_func
(paren
id|key
comma
l_string|&quot;.merge&quot;
)paren
)paren
(brace
id|name
op_assign
id|xstrndup
c_func
(paren
id|key
comma
id|strlen
c_func
(paren
id|key
)paren
l_int|6
)paren
suffix:semicolon
id|type
op_assign
id|MERGE
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
id|item
op_assign
id|path_list_insert
c_func
(paren
id|name
comma
op_amp
id|branch_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|item-&gt;util
)paren
id|item-&gt;util
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|branch_info
)paren
comma
l_int|1
)paren
suffix:semicolon
id|info
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|REMOTE
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;remote
)paren
id|warning
c_func
(paren
l_string|&quot;more than one branch.%s&quot;
comma
id|key
)paren
suffix:semicolon
id|info-&gt;remote
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_else
(brace
r_char
op_star
id|space
op_assign
id|strchr
c_func
(paren
id|value
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|value
op_assign
id|skip_prefix
c_func
(paren
id|value
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|space
)paren
(brace
r_char
op_star
id|merge
suffix:semicolon
id|merge
op_assign
id|xstrndup
c_func
(paren
id|value
comma
id|space
id|value
)paren
suffix:semicolon
id|path_list_append
c_func
(paren
id|merge
comma
op_amp
id|info-&gt;merge
)paren
suffix:semicolon
id|value
op_assign
id|skip_prefix
c_func
(paren
id|space
op_plus
l_int|1
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
id|space
op_assign
id|strchr
c_func
(paren
id|value
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|path_list_append
c_func
(paren
id|xstrdup
c_func
(paren
id|value
)paren
comma
op_amp
id|info-&gt;merge
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_branches
r_static
r_void
id|read_branches
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|branch_list.nr
)paren
r_return
suffix:semicolon
id|git_config
c_func
(paren
id|config_read_branches
)paren
suffix:semicolon
id|sort_path_list
c_func
(paren
op_amp
id|branch_list
)paren
suffix:semicolon
)brace
DECL|struct|ref_states
r_struct
id|ref_states
(brace
DECL|member|remote
r_struct
id|remote
op_star
id|remote
suffix:semicolon
DECL|member|remote_prefix
r_struct
id|strbuf
id|remote_prefix
suffix:semicolon
DECL|member|new
DECL|member|stale
DECL|member|tracked
r_struct
id|path_list
r_new
comma
id|stale
comma
id|tracked
suffix:semicolon
)brace
suffix:semicolon
DECL|function|handle_one_branch
r_static
r_int
id|handle_one_branch
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
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|ref_states
op_star
id|states
op_assign
id|cb_data
suffix:semicolon
r_struct
id|refspec
id|refspec
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|refspec
comma
l_int|0
comma
r_sizeof
(paren
id|refspec
)paren
)paren
suffix:semicolon
id|refspec.dst
op_assign
(paren
r_char
op_star
)paren
id|refname
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote_find_tracking
c_func
(paren
id|states-&gt;remote
comma
op_amp
id|refspec
)paren
)paren
(brace
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|skip_prefix
c_func
(paren
id|refspec.src
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
multiline_comment|/* symbolic refs pointing nowhere were handled already */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|REF_ISSYMREF
)paren
op_logical_or
id|unsorted_path_list_has_path
c_func
(paren
op_amp
id|states-&gt;tracked
comma
id|name
)paren
op_logical_or
id|unsorted_path_list_has_path
c_func
(paren
op_amp
id|states
op_member_access_from_pointer
r_new
comma
id|name
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|item
op_assign
id|path_list_append
c_func
(paren
id|name
comma
op_amp
id|states-&gt;stale
)paren
suffix:semicolon
id|item-&gt;util
op_assign
id|xstrdup
c_func
(paren
id|refname
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_ref_states
r_static
r_int
id|get_ref_states
c_func
(paren
r_const
r_struct
id|ref
op_star
id|ref
comma
r_struct
id|ref_states
op_star
id|states
)paren
(brace
r_struct
id|ref
op_star
id|fetch_map
op_assign
l_int|NULL
comma
op_star
op_star
id|tail
op_assign
op_amp
id|fetch_map
suffix:semicolon
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
id|states-&gt;remote-&gt;fetch_refspec_nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|get_fetch_map
c_func
(paren
id|ref
comma
id|states-&gt;remote-&gt;fetch
op_plus
id|i
comma
op_amp
id|tail
comma
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not get fetch map for refspec %s&quot;
comma
id|states-&gt;remote-&gt;fetch_refspec
(braket
id|i
)braket
)paren
suffix:semicolon
id|states
op_member_access_from_pointer
r_new
dot
id|strdup_paths
op_assign
id|states-&gt;tracked.strdup_paths
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|fetch_map
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_struct
id|path_list
op_star
id|target
op_assign
op_amp
id|states-&gt;tracked
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|util
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref-&gt;peer_ref
op_logical_or
id|read_ref
c_func
(paren
id|ref-&gt;peer_ref-&gt;name
comma
id|sha1
)paren
)paren
id|target
op_assign
op_amp
id|states
op_member_access_from_pointer
r_new
suffix:semicolon
r_else
(brace
id|target
op_assign
op_amp
id|states-&gt;tracked
suffix:semicolon
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|ref-&gt;new_sha1
)paren
)paren
id|util
op_assign
op_amp
id|states
suffix:semicolon
)brace
id|path_list_append
c_func
(paren
id|skip_prefix
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/heads/&quot;
)paren
comma
id|target
)paren
op_member_access_from_pointer
id|util
op_assign
id|util
suffix:semicolon
)brace
id|free_refs
c_func
(paren
id|fetch_map
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|states-&gt;remote_prefix
comma
l_string|&quot;refs/remotes/%s/&quot;
comma
id|states-&gt;remote-&gt;name
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|handle_one_branch
comma
id|states
)paren
suffix:semicolon
id|sort_path_list
c_func
(paren
op_amp
id|states-&gt;stale
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|branches_for_remote
r_struct
id|branches_for_remote
(brace
DECL|member|prefix
r_const
r_char
op_star
id|prefix
suffix:semicolon
DECL|member|branches
r_struct
id|path_list
op_star
id|branches
suffix:semicolon
)brace
suffix:semicolon
DECL|function|add_branch_for_removal
r_static
r_int
id|add_branch_for_removal
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
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|branches_for_remote
op_star
id|branches
op_assign
id|cb_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
id|branches-&gt;prefix
)paren
)paren
(brace
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
multiline_comment|/* make sure that symrefs are deleted */
r_if
c_cond
(paren
id|flags
op_amp
id|REF_ISSYMREF
)paren
r_return
id|unlink
c_func
(paren
id|git_path
c_func
(paren
id|refname
)paren
)paren
suffix:semicolon
id|item
op_assign
id|path_list_append
c_func
(paren
id|refname
comma
id|branches-&gt;branches
)paren
suffix:semicolon
id|item-&gt;util
op_assign
id|xmalloc
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|item-&gt;util
comma
id|sha1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remove_branches
r_static
r_int
id|remove_branches
c_func
(paren
r_struct
id|path_list
op_star
id|branches
)paren
(brace
r_int
id|i
comma
id|result
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
id|branches-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list_item
op_star
id|item
op_assign
id|branches-&gt;items
op_plus
id|i
suffix:semicolon
r_const
r_char
op_star
id|refname
op_assign
id|item-&gt;path
suffix:semicolon
r_int
r_char
op_star
id|sha1
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|refname
comma
id|sha1
)paren
)paren
id|result
op_or_assign
id|error
c_func
(paren
l_string|&quot;Could not remove branch %s&quot;
comma
id|refname
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|rm
r_static
r_int
id|rm
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
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|strbuf
id|buf
suffix:semicolon
r_struct
id|path_list
id|branches
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
r_struct
id|branches_for_remote
id|cb_data
op_assign
(brace
l_int|NULL
comma
op_amp
id|branches
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|builtin_remote_usage
comma
id|options
)paren
suffix:semicolon
id|remote
op_assign
id|remote_get
c_func
(paren
id|argv
(braket
l_int|1
)braket
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
l_string|&quot;No such remote: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;remote.%s&quot;
comma
id|remote-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_rename_section
c_func
(paren
id|buf.buf
comma
l_int|NULL
)paren
OL
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not remove config section &squot;%s&squot;&quot;
comma
id|buf.buf
)paren
suffix:semicolon
id|read_branches
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
id|branch_list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list_item
op_star
id|item
op_assign
id|branch_list.items
op_plus
id|i
suffix:semicolon
r_struct
id|branch_info
op_star
id|info
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;remote
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|info-&gt;remote
comma
id|remote-&gt;name
)paren
)paren
(brace
r_const
r_char
op_star
id|keys
(braket
)braket
op_assign
(brace
l_string|&quot;remote&quot;
comma
l_string|&quot;merge&quot;
comma
l_int|NULL
)brace
comma
op_star
op_star
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|keys
suffix:semicolon
op_star
id|k
suffix:semicolon
id|k
op_increment
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;branch.%s.%s&quot;
comma
id|item-&gt;path
comma
op_star
id|k
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_set
c_func
(paren
id|buf.buf
comma
l_int|NULL
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n;&t; * We cannot just pass a function to for_each_ref() which deletes&n;&t; * the branches one by one, since for_each_ref() relies on cached&n;&t; * refs, which are invalidated when deleting a branch.&n;&t; */
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;refs/remotes/%s/&quot;
comma
id|remote-&gt;name
)paren
suffix:semicolon
id|cb_data.prefix
op_assign
id|buf.buf
suffix:semicolon
id|i
op_assign
id|for_each_ref
c_func
(paren
id|add_branch_for_removal
comma
op_amp
id|cb_data
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
id|i
op_assign
id|remove_branches
c_func
(paren
op_amp
id|branches
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|branches
comma
l_int|1
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|show_list
r_static
r_void
id|show_list
c_func
(paren
r_const
r_char
op_star
id|title
comma
r_struct
id|path_list
op_star
id|list
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;nr
)paren
r_return
suffix:semicolon
id|printf
c_func
(paren
id|title
comma
id|list-&gt;nr
OG
l_int|1
ques
c_cond
l_string|&quot;es&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n    &quot;
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
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|i
ques
c_cond
l_string|&quot; &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_or_prune
r_static
r_int
id|show_or_prune
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
r_int
id|prune
)paren
(brace
r_int
id|dry_run
op_assign
l_int|0
comma
id|result
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
id|OPT_GROUP
c_func
(paren
l_string|&quot;show specific options&quot;
)paren
comma
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|dry_run
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_struct
id|ref_states
id|states
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
id|builtin_remote_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prune
)paren
r_return
id|show_all
c_func
(paren
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_remote_usage
comma
id|options
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|states
comma
l_int|0
comma
r_sizeof
(paren
id|states
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|argc
suffix:semicolon
id|argc
op_decrement
comma
id|argv
op_increment
)paren
(brace
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_struct
id|strbuf
id|buf
suffix:semicolon
r_int
id|i
comma
id|got_states
suffix:semicolon
id|states.remote
op_assign
id|remote_get
c_func
(paren
op_star
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|states.remote
)paren
r_return
id|error
c_func
(paren
l_string|&quot;No such remote: %s&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
l_int|NULL
comma
id|states.remote-&gt;url_nr
OG
l_int|0
ques
c_cond
id|states.remote-&gt;url
(braket
l_int|0
)braket
suffix:colon
l_int|NULL
)paren
suffix:semicolon
id|ref
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
id|read_branches
c_func
(paren
)paren
suffix:semicolon
id|got_states
op_assign
id|get_ref_states
c_func
(paren
id|ref
comma
op_amp
id|states
)paren
suffix:semicolon
r_if
c_cond
(paren
id|got_states
)paren
id|result
op_assign
id|error
c_func
(paren
l_string|&quot;Error getting local info for &squot;%s&squot;&quot;
comma
id|states.remote-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prune
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
r_int
id|prefix_len
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|states.remote-&gt;fetch_refspec_nr
op_eq
l_int|1
op_logical_and
id|states.remote-&gt;fetch-&gt;pattern
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|states.remote-&gt;fetch-&gt;src
comma
id|states.remote-&gt;fetch-&gt;dst
)paren
)paren
multiline_comment|/* handle --mirror remote */
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;refs/remotes/%s/&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
id|prefix_len
op_assign
id|buf.len
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
id|states.stale.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strbuf_setlen
c_func
(paren
op_amp
id|buf
comma
id|prefix_len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|states.stale.items
(braket
id|i
)braket
dot
id|path
)paren
suffix:semicolon
id|result
op_or_assign
id|delete_ref
c_func
(paren
id|buf.buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_goto
id|cleanup_states
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;* remote %s&bslash;n  URL: %s&bslash;n&quot;
comma
op_star
id|argv
comma
id|states.remote-&gt;url_nr
OG
l_int|0
ques
c_cond
id|states.remote-&gt;url
(braket
l_int|0
)braket
suffix:colon
l_string|&quot;(no URL)&quot;
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
id|branch_list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list_item
op_star
id|branch
op_assign
id|branch_list.items
op_plus
id|i
suffix:semicolon
r_struct
id|branch_info
op_star
id|info
op_assign
id|branch-&gt;util
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;merge.nr
op_logical_or
id|strcmp
c_func
(paren
op_star
id|argv
comma
id|info-&gt;remote
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;  Remote branch%s merged with &squot;git pull&squot; &quot;
l_string|&quot;while on branch %s&bslash;n   &quot;
comma
id|info-&gt;merge.nr
OG
l_int|1
ques
c_cond
l_string|&quot;es&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|branch-&gt;path
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|info-&gt;merge.nr
suffix:semicolon
id|j
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|info-&gt;merge.items
(braket
id|j
)braket
dot
id|path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|got_states
)paren
r_continue
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;  New remote branch%%s (next fetch will &quot;
l_string|&quot;store in remotes/%s)&quot;
comma
id|states.remote-&gt;name
)paren
suffix:semicolon
id|show_list
c_func
(paren
id|buf.buf
comma
op_amp
id|states
dot
r_new
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;  Stale tracking branch%s (use &squot;git remote prune&squot;)&quot;
comma
op_amp
id|states.stale
)paren
suffix:semicolon
id|show_list
c_func
(paren
l_string|&quot;  Tracked remote branch%s&quot;
comma
op_amp
id|states.tracked
)paren
suffix:semicolon
r_if
c_cond
(paren
id|states.remote-&gt;push_refspec_nr
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;  Local branch%s pushed with &squot;git push&squot;&bslash;n   &quot;
comma
id|states.remote-&gt;push_refspec_nr
OG
l_int|1
ques
c_cond
l_string|&quot;es&quot;
suffix:colon
l_string|&quot;&quot;
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
id|states.remote-&gt;push_refspec_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|refspec
op_star
id|spec
op_assign
id|states.remote-&gt;push
op_plus
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; %s%s%s%s&quot;
comma
id|spec-&gt;force
ques
c_cond
l_string|&quot;+&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|skip_prefix
c_func
(paren
id|spec-&gt;src
comma
l_string|&quot;refs/heads/&quot;
)paren
comma
id|spec-&gt;dst
ques
c_cond
l_string|&quot;:&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|skip_prefix
c_func
(paren
id|spec-&gt;dst
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|cleanup_states
suffix:colon
multiline_comment|/* NEEDSWORK: free remote */
id|path_list_clear
c_func
(paren
op_amp
id|states
dot
r_new
comma
l_int|0
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|states.stale
comma
l_int|0
)paren
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|states.tracked
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|get_one_remote_for_update
r_static
r_int
id|get_one_remote_for_update
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
id|path_list
op_star
id|list
op_assign
id|priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote-&gt;skip_default_update
)paren
id|path_list_append
c_func
(paren
id|xstrdup
c_func
(paren
id|remote-&gt;name
)paren
comma
id|list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|remote_group
r_struct
id|remote_group
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|list
r_struct
id|path_list
op_star
id|list
suffix:semicolon
DECL|variable|remote_group
)brace
id|remote_group
suffix:semicolon
DECL|function|get_remote_group
r_static
r_int
id|get_remote_group
c_func
(paren
r_const
r_char
op_star
id|key
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
op_logical_neg
id|prefixcmp
c_func
(paren
id|key
comma
l_string|&quot;remotes.&quot;
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|key
op_plus
l_int|8
comma
id|remote_group.name
)paren
)paren
(brace
multiline_comment|/* split list by white space */
r_int
id|space
op_assign
id|strcspn
c_func
(paren
id|value
comma
l_string|&quot; &bslash;t&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
id|space
OG
l_int|1
)paren
id|path_list_append
c_func
(paren
id|xstrndup
c_func
(paren
id|value
comma
id|space
)paren
comma
id|remote_group.list
)paren
suffix:semicolon
id|value
op_add_assign
id|space
op_plus
(paren
id|value
(braket
id|space
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|space
op_assign
id|strcspn
c_func
(paren
id|value
comma
l_string|&quot; &bslash;t&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|update
r_static
r_int
id|update
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
id|i
comma
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|path_list
id|list
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
r_static
r_const
r_char
op_star
id|default_argv
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;default&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
id|argc
op_assign
l_int|2
suffix:semicolon
id|argv
op_assign
id|default_argv
suffix:semicolon
)brace
id|remote_group.list
op_assign
op_amp
id|list
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
id|remote_group.name
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
id|result
op_assign
id|git_config
c_func
(paren
id|get_remote_group
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|result
op_logical_and
op_logical_neg
id|list.nr
op_logical_and
id|argc
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;default&quot;
)paren
)paren
id|result
op_assign
id|for_each_remote
c_func
(paren
id|get_one_remote_for_update
comma
op_amp
id|list
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
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
id|result
op_or_assign
id|fetch_remote
c_func
(paren
id|list.items
(braket
id|i
)braket
dot
id|path
)paren
suffix:semicolon
multiline_comment|/* all names were strdup()ed or strndup()ed */
id|list.strdup_paths
op_assign
l_int|1
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|list
comma
l_int|0
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|get_one_entry
r_static
r_int
id|get_one_entry
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
id|path_list
op_star
id|list
op_assign
id|priv
suffix:semicolon
id|path_list_append
c_func
(paren
id|remote-&gt;name
comma
id|list
)paren
op_member_access_from_pointer
id|util
op_assign
id|remote-&gt;url_nr
ques
c_cond
(paren
r_void
op_star
)paren
id|remote-&gt;url
(braket
l_int|0
)braket
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|remote-&gt;url_nr
OG
l_int|1
)paren
id|warning
c_func
(paren
l_string|&quot;Remote %s has more than one URL&quot;
comma
id|remote-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_all
r_static
r_int
id|show_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|path_list
id|list
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|result
op_assign
id|for_each_remote
c_func
(paren
id|get_one_entry
comma
op_amp
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
r_int
id|i
suffix:semicolon
id|sort_path_list
c_func
(paren
op_amp
id|list
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
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list_item
op_star
id|item
op_assign
id|list.items
op_plus
id|i
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s%s%s&bslash;n&quot;
comma
id|item-&gt;path
comma
id|verbose
ques
c_cond
l_string|&quot;&bslash;t&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|verbose
op_logical_and
id|item-&gt;util
ques
c_cond
(paren
r_const
r_char
op_star
)paren
id|item-&gt;util
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|cmd_remote
r_int
id|cmd_remote
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
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_int
id|result
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
id|builtin_remote_usage
comma
id|PARSE_OPT_STOP_AT_NON_OPTION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|result
op_assign
id|show_all
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;add&quot;
)paren
)paren
id|result
op_assign
id|add
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;rm&quot;
)paren
)paren
id|result
op_assign
id|rm
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;show&quot;
)paren
)paren
id|result
op_assign
id|show_or_prune
c_func
(paren
id|argc
comma
id|argv
comma
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;prune&quot;
)paren
)paren
id|result
op_assign
id|show_or_prune
c_func
(paren
id|argc
comma
id|argv
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
l_string|&quot;update&quot;
)paren
)paren
id|result
op_assign
id|update
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
r_else
(brace
id|error
c_func
(paren
l_string|&quot;Unknown subcommand: %s&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|builtin_remote_usage
comma
id|options
)paren
suffix:semicolon
)brace
r_return
id|result
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
