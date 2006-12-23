macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
DECL|struct|expire_reflog_cb
r_struct
id|expire_reflog_cb
(brace
DECL|member|newlog
id|FILE
op_star
id|newlog
suffix:semicolon
DECL|member|ref
r_const
r_char
op_star
id|ref
suffix:semicolon
DECL|member|ref_commit
r_struct
id|commit
op_star
id|ref_commit
suffix:semicolon
DECL|member|expire_total
r_int
r_int
id|expire_total
suffix:semicolon
DECL|member|expire_unreachable
r_int
r_int
id|expire_unreachable
suffix:semicolon
)brace
suffix:semicolon
DECL|function|tree_is_complete
r_static
r_int
id|tree_is_complete
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|desc.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
l_int|0
suffix:semicolon
id|desc.buf
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|desc.size
)paren
(brace
r_const
r_int
r_char
op_star
id|elem
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|mode
suffix:semicolon
id|elem
op_assign
id|tree_entry_extract
c_func
(paren
op_amp
id|desc
comma
op_amp
id|name
comma
op_amp
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|elem
)paren
op_logical_or
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
op_logical_and
op_logical_neg
id|tree_is_complete
c_func
(paren
id|elem
)paren
)paren
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|update_tree_entry
c_func
(paren
op_amp
id|desc
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|keep_entry
r_static
r_int
id|keep_entry
c_func
(paren
r_struct
id|commit
op_star
op_star
id|it
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
op_star
id|it
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Make sure everything in this commit exists. */
id|parse_object
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree_is_complete
c_func
(paren
id|commit-&gt;tree-&gt;object.sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|it
op_assign
id|commit
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|expire_reflog_ent
r_static
r_int
id|expire_reflog_ent
c_func
(paren
r_int
r_char
op_star
id|osha1
comma
r_int
r_char
op_star
id|nsha1
comma
r_char
op_star
id|data
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|expire_reflog_cb
op_star
id|cb
op_assign
id|cb_data
suffix:semicolon
r_int
r_int
id|timestamp
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|ep
suffix:semicolon
r_struct
id|commit
op_star
id|old
comma
op_star
r_new
suffix:semicolon
id|cp
op_assign
id|strchr
c_func
(paren
id|data
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cp
op_logical_or
op_star
op_increment
id|cp
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|prune
suffix:semicolon
id|timestamp
op_assign
id|strtoul
c_func
(paren
id|cp
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ep
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
id|timestamp
OL
id|cb-&gt;expire_total
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|keep_entry
c_func
(paren
op_amp
id|old
comma
id|osha1
)paren
op_logical_or
op_logical_neg
id|keep_entry
c_func
(paren
op_amp
r_new
comma
id|nsha1
)paren
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
(paren
id|timestamp
OL
id|cb-&gt;expire_unreachable
)paren
op_logical_and
(paren
op_logical_neg
id|cb-&gt;ref_commit
op_logical_or
(paren
id|old
op_logical_and
op_logical_neg
id|in_merge_bases
c_func
(paren
id|old
comma
id|cb-&gt;ref_commit
)paren
)paren
op_logical_or
(paren
r_new
op_logical_and
op_logical_neg
id|in_merge_bases
c_func
(paren
r_new
comma
id|cb-&gt;ref_commit
)paren
)paren
)paren
)paren
r_goto
id|prune
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;newlog
)paren
id|fprintf
c_func
(paren
id|cb-&gt;newlog
comma
l_string|&quot;%s %s %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|osha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|nsha1
)paren
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|prune
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|cb-&gt;newlog
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;would prune %s&quot;
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|cmd_reflog_expire_cb
r_struct
id|cmd_reflog_expire_cb
(brace
DECL|member|dry_run
r_int
id|dry_run
suffix:semicolon
DECL|member|expire_total
r_int
r_int
id|expire_total
suffix:semicolon
DECL|member|expire_unreachable
r_int
r_int
id|expire_unreachable
suffix:semicolon
)brace
suffix:semicolon
DECL|function|expire_reflog
r_static
r_int
id|expire_reflog
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|unused
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|cmd_reflog_expire_cb
op_star
id|cmd
op_assign
id|cb_data
suffix:semicolon
r_struct
id|expire_reflog_cb
id|cb
suffix:semicolon
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
r_char
op_star
id|newlog_path
op_assign
l_int|NULL
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ref
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;not a ref &squot;%s&squot;&quot;
comma
id|ref
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
)paren
suffix:semicolon
multiline_comment|/* we take the lock for the ref itself to prevent it from&n;&t; * getting updated.&n;&t; */
id|lock
op_assign
id|lock_ref_sha1
c_func
(paren
id|ref
op_plus
l_int|5
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot lock ref &squot;%s&squot;&quot;
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|lock-&gt;log_file
)paren
)paren
r_goto
id|finish
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmd-&gt;dry_run
)paren
(brace
id|newlog_path
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;logs/%s.lock&quot;
comma
id|ref
)paren
)paren
suffix:semicolon
id|cb.newlog
op_assign
id|fopen
c_func
(paren
id|newlog_path
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
)brace
id|cb.ref_commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cb.ref_commit
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: ref &squot;%s&squot; does not point at a commit&bslash;n&quot;
comma
id|ref
)paren
suffix:semicolon
id|cb.ref
op_assign
id|ref
suffix:semicolon
id|cb.expire_total
op_assign
id|cmd-&gt;expire_total
suffix:semicolon
id|cb.expire_unreachable
op_assign
id|cmd-&gt;expire_unreachable
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|ref
comma
id|expire_reflog_ent
comma
op_amp
id|cb
)paren
suffix:semicolon
id|finish
suffix:colon
r_if
c_cond
(paren
id|cb.newlog
)paren
(brace
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|cb.newlog
)paren
)paren
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;%s: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
comma
id|newlog_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|newlog_path
comma
id|lock-&gt;log_file
)paren
)paren
(brace
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;cannot rename %s to %s&quot;
comma
id|newlog_path
comma
id|lock-&gt;log_file
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|newlog_path
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|newlog_path
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|variable|reflog_expire_usage
r_static
r_const
r_char
id|reflog_expire_usage
(braket
)braket
op_assign
l_string|&quot;git-reflog expire [--dry-run] [--expire=&lt;time&gt;] [--expire-unreachable=&lt;time&gt;] [--all] &lt;refs&gt;...&quot;
suffix:semicolon
DECL|function|cmd_reflog_expire
r_static
r_int
id|cmd_reflog_expire
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
id|cmd_reflog_expire_cb
id|cb
suffix:semicolon
r_int
r_int
id|now
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_int
id|i
comma
id|status
comma
id|do_all
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
id|do_all
op_assign
id|status
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
)paren
suffix:semicolon
id|cb.expire_total
op_assign
id|now
l_int|90
op_star
l_int|24
op_star
l_int|3600
suffix:semicolon
id|cb.expire_unreachable
op_assign
id|now
l_int|30
op_star
l_int|24
op_star
l_int|3600
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--dry-run&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-n&quot;
)paren
)paren
id|cb.dry_run
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--expire=&quot;
comma
l_int|9
)paren
)paren
id|cb.expire_total
op_assign
id|approxidate
c_func
(paren
id|arg
op_plus
l_int|9
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--expire-unreachable=&quot;
comma
l_int|21
)paren
)paren
id|cb.expire_unreachable
op_assign
id|approxidate
c_func
(paren
id|arg
op_plus
l_int|21
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
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
id|do_all
op_assign
l_int|1
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
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|reflog_expire_usage
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_all
)paren
id|status
op_or_assign
id|for_each_ref
c_func
(paren
id|expire_reflog
comma
op_amp
id|cb
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
r_const
r_char
op_star
id|ref
op_assign
id|argv
(braket
id|i
op_increment
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
id|status
op_or_assign
id|error
c_func
(paren
l_string|&quot;%s points nowhere!&quot;
comma
id|ref
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|status
op_or_assign
id|expire_reflog
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|0
comma
op_amp
id|cb
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|variable|reflog_usage
r_static
r_const
r_char
id|reflog_usage
(braket
)braket
op_assign
l_string|&quot;git-reflog (expire | ...)&quot;
suffix:semicolon
DECL|function|cmd_reflog
r_int
id|cmd_reflog
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
id|argc
OL
l_int|2
)paren
id|usage
c_func
(paren
id|reflog_usage
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
l_int|1
)braket
comma
l_string|&quot;expire&quot;
)paren
)paren
r_return
id|cmd_reflog_expire
c_func
(paren
id|argc
l_int|1
comma
id|argv
op_plus
l_int|1
comma
id|prefix
)paren
suffix:semicolon
r_else
id|usage
c_func
(paren
id|reflog_usage
)paren
suffix:semicolon
)brace
eof
