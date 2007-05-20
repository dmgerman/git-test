macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
DECL|macro|CHUNK_SIZE
mdefine_line|#define CHUNK_SIZE 1024
DECL|function|get_stdin
r_static
r_char
op_star
id|get_stdin
c_func
(paren
r_void
)paren
(brace
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|data
op_assign
id|xmalloc
c_func
(paren
id|CHUNK_SIZE
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|ssize_t
id|cnt
op_assign
id|xread
c_func
(paren
l_int|0
comma
id|data
op_plus
id|offset
comma
id|CHUNK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;error reading standard input: %s&quot;
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
id|cnt
op_eq
l_int|0
)paren
(brace
id|data
(braket
id|offset
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|offset
op_add_assign
id|cnt
suffix:semicolon
id|data
op_assign
id|xrealloc
c_func
(paren
id|data
comma
id|offset
op_plus
id|CHUNK_SIZE
)paren
suffix:semicolon
)brace
r_return
id|data
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
DECL|function|update_ref
r_static
r_int
id|update_ref
c_func
(paren
r_const
r_char
op_star
id|action
comma
r_const
r_char
op_star
id|refname
comma
r_int
r_char
op_star
id|sha1
comma
r_int
r_char
op_star
id|oldval
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
l_string|&quot;(reflog update)&quot;
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
id|refname
comma
id|oldval
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
id|sha1
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
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|new_head
comma
r_const
r_char
op_star
id|note
comma
r_int
id|verbose
comma
r_int
id|force
)paren
(brace
r_int
r_char
id|sha1_old
(braket
l_int|20
)braket
comma
id|sha1_new
(braket
l_int|20
)braket
suffix:semicolon
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
comma
op_star
id|updated
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|new_head
comma
id|sha1_new
)paren
)paren
id|die
c_func
(paren
l_string|&quot;malformed object name %s&quot;
comma
id|new_head
)paren
suffix:semicolon
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1_new
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
id|new_head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|name
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
id|sha1_new
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
id|get_sha1
c_func
(paren
id|name
comma
id|sha1_old
)paren
)paren
(brace
r_char
op_star
id|msg
suffix:semicolon
id|just_store
suffix:colon
multiline_comment|/* new ref */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
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
id|name
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|sha1_new
)paren
suffix:semicolon
r_return
id|update_ref
c_func
(paren
id|msg
comma
id|name
comma
id|sha1_new
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1_old
comma
id|sha1_new
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
id|name
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|sha1_new
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
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
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
id|name
comma
id|note
)paren
suffix:semicolon
id|show_new
c_func
(paren
id|type
comma
id|sha1_new
)paren
suffix:semicolon
r_return
id|update_ref
c_func
(paren
l_string|&quot;updating tag&quot;
comma
id|name
comma
id|sha1_new
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|current
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1_old
)paren
suffix:semicolon
id|updated
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1_new
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
r_goto
id|just_store
suffix:semicolon
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
id|sha1_new
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
id|name
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
id|update_ref
c_func
(paren
l_string|&quot;fast forward&quot;
comma
id|name
comma
id|sha1_new
comma
id|sha1_old
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;* %s: not updating to non-fast forward %s&bslash;n&quot;
comma
id|name
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
id|name
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
id|update_ref
c_func
(paren
l_string|&quot;forced-update&quot;
comma
id|name
comma
id|sha1_new
comma
id|sha1_old
)paren
suffix:semicolon
)brace
DECL|function|append_fetch_head
r_static
r_int
id|append_fetch_head
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|head
comma
r_const
r_char
op_star
id|remote
comma
r_const
r_char
op_star
id|remote_name
comma
r_const
r_char
op_star
id|remote_nick
comma
r_const
r_char
op_star
id|local_name
comma
r_int
id|not_for_merge
comma
r_int
id|verbose
comma
r_int
id|force
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
id|remote_len
comma
id|i
comma
id|note_len
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
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
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|head
comma
id|sha1
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Not a valid object name: %s&quot;
comma
id|head
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
id|not_for_merge
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|remote_name
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
id|strncmp
c_func
(paren
id|remote_name
comma
l_string|&quot;refs/heads/&quot;
comma
l_int|11
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;branch&quot;
suffix:semicolon
id|what
op_assign
id|remote_name
op_plus
l_int|11
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|remote_name
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;tag&quot;
suffix:semicolon
id|what
op_assign
id|remote_name
op_plus
l_int|10
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|remote_name
comma
l_string|&quot;refs/remotes/&quot;
comma
l_int|13
)paren
)paren
(brace
id|kind
op_assign
l_string|&quot;remote branch&quot;
suffix:semicolon
id|what
op_assign
id|remote_name
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
id|remote_name
suffix:semicolon
)brace
id|remote_len
op_assign
id|strlen
c_func
(paren
id|remote
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|remote_len
l_int|1
suffix:semicolon
id|remote
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
id|remote_len
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
id|remote
op_plus
id|i
l_int|3
comma
l_int|4
)paren
)paren
id|remote_len
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
id|remote_len
comma
id|remote
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
id|sha1
)paren
comma
id|not_for_merge
ques
c_cond
l_string|&quot;not-for-merge&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|note
)paren
suffix:semicolon
r_return
id|update_local_ref
c_func
(paren
id|local_name
comma
id|head
comma
id|note
comma
id|verbose
comma
id|force
)paren
suffix:semicolon
)brace
DECL|variable|keep
r_static
r_char
op_star
id|keep
suffix:semicolon
DECL|function|remove_keep
r_static
r_void
id|remove_keep
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|keep
op_logical_and
op_star
id|keep
)paren
id|unlink
c_func
(paren
id|keep
)paren
suffix:semicolon
)brace
DECL|function|remove_keep_on_signal
r_static
r_void
id|remove_keep_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_keep
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
DECL|function|find_local_name
r_static
r_char
op_star
id|find_local_name
c_func
(paren
r_const
r_char
op_star
id|remote_name
comma
r_const
r_char
op_star
id|refs
comma
r_int
op_star
id|force_p
comma
r_int
op_star
id|not_for_merge_p
)paren
(brace
r_const
r_char
op_star
id|ref
op_assign
id|refs
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|remote_name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ref
)paren
(brace
r_const
r_char
op_star
id|next
suffix:semicolon
r_int
id|single_force
comma
id|not_for_merge
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ref
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|ref
)paren
r_break
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|ref
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|single_force
op_assign
id|not_for_merge
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ref
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|single_force
op_assign
l_int|1
suffix:semicolon
id|ref
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|ref
op_eq
l_char|&squot;.&squot;
)paren
(brace
id|not_for_merge
op_assign
l_int|1
suffix:semicolon
id|ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ref
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|single_force
op_assign
l_int|1
suffix:semicolon
id|ref
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|remote_name
comma
id|ref
comma
id|len
)paren
op_logical_and
id|ref
(braket
id|len
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_const
r_char
op_star
id|local_part
op_assign
id|ref
op_plus
id|len
op_plus
l_int|1
suffix:semicolon
r_char
op_star
id|ret
suffix:semicolon
r_int
id|retlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
id|retlen
op_assign
id|strlen
c_func
(paren
id|local_part
)paren
suffix:semicolon
r_else
id|retlen
op_assign
id|next
id|local_part
suffix:semicolon
id|ret
op_assign
id|xmalloc
c_func
(paren
id|retlen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ret
comma
id|local_part
comma
id|retlen
)paren
suffix:semicolon
id|ret
(braket
id|retlen
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|force_p
op_assign
id|single_force
suffix:semicolon
op_star
id|not_for_merge_p
op_assign
id|not_for_merge
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ref
op_assign
id|next
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|fetch_native_store
r_static
r_int
id|fetch_native_store
c_func
(paren
id|FILE
op_star
id|fp
comma
r_const
r_char
op_star
id|remote
comma
r_const
r_char
op_star
id|remote_nick
comma
r_const
r_char
op_star
id|refs
comma
r_int
id|verbose
comma
r_int
id|force
)paren
(brace
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|signal
c_func
(paren
id|SIGINT
comma
id|remove_keep_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_keep
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|stdin
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
r_char
op_star
id|local_name
suffix:semicolon
r_int
id|single_force
comma
id|not_for_merge
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|buffer
suffix:semicolon
op_star
id|cp
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|cp
)paren
suffix:semicolon
id|cp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
)paren
op_star
id|cp
op_increment
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|cp
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|cp
(braket
op_decrement
id|len
)braket
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
id|buffer
comma
l_string|&quot;failed&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Fetch failure: %s&quot;
comma
id|remote
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buffer
comma
l_string|&quot;pack&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buffer
comma
l_string|&quot;keep&quot;
)paren
)paren
(brace
r_char
op_star
id|od
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|od
)paren
op_plus
id|strlen
c_func
(paren
id|cp
)paren
op_plus
l_int|50
suffix:semicolon
id|keep
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|keep
comma
l_string|&quot;%s/pack/pack-%s.keep&quot;
comma
id|od
comma
id|cp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|local_name
op_assign
id|find_local_name
c_func
(paren
id|cp
comma
id|refs
comma
op_amp
id|single_force
comma
op_amp
id|not_for_merge
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local_name
)paren
r_continue
suffix:semicolon
id|err
op_or_assign
id|append_fetch_head
c_func
(paren
id|fp
comma
id|buffer
comma
id|remote
comma
id|cp
comma
id|remote_nick
comma
id|local_name
comma
id|not_for_merge
comma
id|verbose
comma
id|force
op_logical_or
id|single_force
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|parse_reflist
r_static
r_int
id|parse_reflist
c_func
(paren
r_const
r_char
op_star
id|reflist
)paren
(brace
r_const
r_char
op_star
id|ref
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;refs=&squot;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|reflist
suffix:semicolon
id|ref
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|next
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ref
op_logical_and
id|isspace
c_func
(paren
op_star
id|ref
)paren
)paren
id|ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|ref
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|ref
suffix:semicolon
op_star
id|next
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|next
)paren
suffix:semicolon
id|next
op_increment
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n%.*s&quot;
comma
(paren
r_int
)paren
(paren
id|next
id|ref
)paren
comma
id|ref
)paren
suffix:semicolon
id|ref
op_assign
id|next
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&squot;&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;rref=&squot;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|reflist
suffix:semicolon
id|ref
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|next
comma
op_star
id|colon
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ref
op_logical_and
id|isspace
c_func
(paren
op_star
id|ref
)paren
)paren
id|ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|ref
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|ref
suffix:semicolon
op_star
id|next
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|next
)paren
suffix:semicolon
id|next
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ref
op_eq
l_char|&squot;.&squot;
)paren
id|ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ref
op_eq
l_char|&squot;+&squot;
)paren
id|ref
op_increment
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|ref
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%.*s&quot;
comma
(paren
r_int
)paren
(paren
(paren
id|colon
ques
c_cond
id|colon
suffix:colon
id|next
)paren
id|ref
)paren
comma
id|ref
)paren
suffix:semicolon
id|ref
op_assign
id|next
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&squot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|expand_refs_wildcard
r_static
r_int
id|expand_refs_wildcard
c_func
(paren
r_const
r_char
op_star
id|ls_remote_result
comma
r_int
id|numrefs
comma
r_const
r_char
op_star
op_star
id|refs
)paren
(brace
r_int
id|i
comma
id|matchlen
comma
id|replacelen
suffix:semicolon
r_int
id|found_one
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|remote
op_assign
op_star
id|refs
op_increment
suffix:semicolon
id|numrefs
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|numrefs
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Nothing specified for fetching with remote.%s.fetch&bslash;n&quot;
comma
id|remote
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;empty&bslash;n&quot;
)paren
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
id|numrefs
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
r_const
r_char
op_star
id|lref
op_assign
id|ref
suffix:semicolon
r_const
r_char
op_star
id|colon
suffix:semicolon
r_const
r_char
op_star
id|tail
suffix:semicolon
r_const
r_char
op_star
id|ls
suffix:semicolon
r_const
r_char
op_star
id|next
suffix:semicolon
r_if
c_cond
(paren
op_star
id|lref
op_eq
l_char|&squot;+&squot;
)paren
id|lref
op_increment
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|lref
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|tail
op_assign
id|lref
op_plus
id|strlen
c_func
(paren
id|lref
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|colon
op_logical_and
l_int|2
OL
id|colon
id|lref
op_logical_and
id|colon
(braket
l_int|1
)braket
op_eq
l_char|&squot;*&squot;
op_logical_and
id|colon
(braket
l_int|2
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
l_int|2
OL
id|tail
(paren
id|colon
op_plus
l_int|1
)paren
op_logical_and
id|tail
(braket
l_int|1
)braket
op_eq
l_char|&squot;*&squot;
op_logical_and
id|tail
(braket
l_int|2
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
(brace
multiline_comment|/* not a glob */
r_if
c_cond
(paren
op_logical_neg
id|found_one
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;explicit&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|ref
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* glob */
r_if
c_cond
(paren
op_logical_neg
id|found_one
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;glob&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* lref to colon-2 is remote hierarchy name;&n;&t;&t; * colon+1 to tail-2 is local.&n;&t;&t; */
id|matchlen
op_assign
(paren
id|colon
op_minus
l_int|1
)paren
id|lref
suffix:semicolon
id|replacelen
op_assign
(paren
id|tail
op_minus
l_int|1
)paren
(paren
id|colon
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ls
op_assign
id|ls_remote_result
suffix:semicolon
id|ls
suffix:semicolon
id|ls
op_assign
id|next
)paren
(brace
r_const
r_char
op_star
id|eol
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ls
op_logical_and
id|isspace
c_func
(paren
op_star
id|ls
)paren
)paren
id|ls
op_increment
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|ls
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|eol
op_assign
op_logical_neg
id|next
ques
c_cond
(paren
id|ls
op_plus
id|strlen
c_func
(paren
id|ls
)paren
)paren
suffix:colon
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;^{}&quot;
comma
id|eol
op_minus
l_int|3
comma
l_int|3
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|eol
id|ls
OL
l_int|40
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|ls
comma
id|sha1
)paren
)paren
r_continue
suffix:semicolon
id|ls
op_add_assign
l_int|40
suffix:semicolon
r_while
c_loop
(paren
id|ls
OL
id|eol
op_logical_and
id|isspace
c_func
(paren
op_star
id|ls
)paren
)paren
id|ls
op_increment
suffix:semicolon
multiline_comment|/* ls to next (or eol) is the name.&n;&t;&t;&t; * is it identical to lref to colon-2?&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|eol
id|ls
)paren
op_le
id|matchlen
op_logical_or
id|strncmp
c_func
(paren
id|ls
comma
id|lref
comma
id|matchlen
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Yes, it is a match */
id|namelen
op_assign
id|eol
id|ls
suffix:semicolon
r_if
c_cond
(paren
id|lref
op_ne
id|ref
)paren
id|putchar
c_func
(paren
l_char|&squot;+&squot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%.*s:%.*s%.*s&bslash;n&quot;
comma
id|namelen
comma
id|ls
comma
id|replacelen
comma
id|colon
op_plus
l_int|1
comma
id|namelen
id|matchlen
comma
id|ls
op_plus
id|matchlen
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pick_rref
r_static
r_int
id|pick_rref
c_func
(paren
r_int
id|sha1_only
comma
r_const
r_char
op_star
id|rref
comma
r_const
r_char
op_star
id|ls_remote_result
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|lrr_count
op_assign
id|lrr_count
comma
id|i
comma
id|pass
suffix:semicolon
r_const
r_char
op_star
id|cp
suffix:semicolon
r_struct
id|lrr
(brace
r_const
r_char
op_star
id|line
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_int
id|shown
suffix:semicolon
)brace
op_star
id|lrr_list
op_assign
id|lrr_list
suffix:semicolon
r_for
c_loop
(paren
id|pass
op_assign
l_int|0
suffix:semicolon
id|pass
OL
l_int|2
suffix:semicolon
id|pass
op_increment
)paren
(brace
multiline_comment|/* pass 0 counts and allocates, pass 1 fills... */
id|cp
op_assign
id|ls_remote_result
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_const
r_char
op_star
id|np
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
op_logical_and
id|isspace
c_func
(paren
op_star
id|cp
)paren
)paren
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|cp
)paren
r_break
suffix:semicolon
id|np
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|np
)paren
id|np
op_assign
id|cp
op_plus
id|strlen
c_func
(paren
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pass
)paren
(brace
id|lrr_list
(braket
id|i
)braket
dot
id|line
op_assign
id|cp
suffix:semicolon
id|lrr_list
(braket
id|i
)braket
dot
id|name
op_assign
id|cp
op_plus
l_int|41
suffix:semicolon
id|lrr_list
(braket
id|i
)braket
dot
id|namelen
op_assign
id|np
(paren
id|cp
op_plus
l_int|41
)paren
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
id|cp
op_assign
id|np
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pass
)paren
(brace
id|lrr_count
op_assign
id|i
suffix:semicolon
id|lrr_list
op_assign
id|xcalloc
c_func
(paren
id|lrr_count
comma
r_sizeof
(paren
op_star
id|lrr_list
)paren
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_const
r_char
op_star
id|next
suffix:semicolon
r_int
id|rreflen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
op_star
id|rref
op_logical_and
id|isspace
c_func
(paren
op_star
id|rref
)paren
)paren
id|rref
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|rref
)paren
r_break
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|rref
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
id|next
op_assign
id|rref
op_plus
id|strlen
c_func
(paren
id|rref
)paren
suffix:semicolon
id|rreflen
op_assign
id|next
id|rref
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
id|lrr_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|lrr
op_star
id|lrr
op_assign
op_amp
(paren
id|lrr_list
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rreflen
op_eq
id|lrr-&gt;namelen
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|lrr-&gt;name
comma
id|rref
comma
id|rreflen
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lrr-&gt;shown
)paren
id|printf
c_func
(paren
l_string|&quot;%.*s&bslash;n&quot;
comma
id|sha1_only
ques
c_cond
l_int|40
suffix:colon
id|lrr-&gt;namelen
op_plus
l_int|41
comma
id|lrr-&gt;line
)paren
suffix:semicolon
id|lrr-&gt;shown
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
id|lrr_count
op_le
id|i
)paren
(brace
id|error
c_func
(paren
l_string|&quot;pick-rref: %.*s not found&quot;
comma
id|rreflen
comma
id|rref
)paren
suffix:semicolon
id|err
op_assign
l_int|1
suffix:semicolon
)brace
id|rref
op_assign
id|next
suffix:semicolon
)brace
id|free
c_func
(paren
id|lrr_list
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cmd_fetch__tool
r_int
id|cmd_fetch__tool
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
id|verbose
op_assign
l_int|0
suffix:semicolon
r_int
id|force
op_assign
l_int|0
suffix:semicolon
r_int
id|sopt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;-v&quot;
comma
id|arg
)paren
)paren
id|verbose
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
l_string|&quot;-f&quot;
comma
id|arg
)paren
)paren
id|force
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
l_string|&quot;-s&quot;
comma
id|arg
)paren
)paren
id|sopt
op_assign
l_int|1
suffix:semicolon
r_else
r_break
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_le
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Missing subcommand&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;append-fetch-head&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
(brace
r_int
id|result
suffix:semicolon
id|FILE
op_star
id|fp
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|8
)paren
r_return
id|error
c_func
(paren
l_string|&quot;append-fetch-head takes 6 args&quot;
)paren
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
id|result
op_assign
id|append_fetch_head
c_func
(paren
id|fp
comma
id|argv
(braket
l_int|2
)braket
comma
id|argv
(braket
l_int|3
)braket
comma
id|argv
(braket
l_int|4
)braket
comma
id|argv
(braket
l_int|5
)braket
comma
id|argv
(braket
l_int|6
)braket
comma
op_logical_neg
op_logical_neg
id|argv
(braket
l_int|7
)braket
(braket
l_int|0
)braket
comma
id|verbose
comma
id|force
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;native-store&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
(brace
r_int
id|result
suffix:semicolon
id|FILE
op_star
id|fp
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|5
)paren
r_return
id|error
c_func
(paren
l_string|&quot;fetch-native-store takes 3 args&quot;
)paren
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
id|result
op_assign
id|fetch_native_store
c_func
(paren
id|fp
comma
id|argv
(braket
l_int|2
)braket
comma
id|argv
(braket
l_int|3
)braket
comma
id|argv
(braket
l_int|4
)braket
comma
id|verbose
comma
id|force
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;parse-reflist&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
(brace
r_const
r_char
op_star
id|reflist
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|3
)paren
r_return
id|error
c_func
(paren
l_string|&quot;parse-reflist takes 1 arg&quot;
)paren
suffix:semicolon
id|reflist
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|reflist
comma
l_string|&quot;-&quot;
)paren
)paren
id|reflist
op_assign
id|get_stdin
c_func
(paren
)paren
suffix:semicolon
r_return
id|parse_reflist
c_func
(paren
id|reflist
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;pick-rref&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
(brace
r_const
r_char
op_star
id|ls_remote_result
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|4
)paren
r_return
id|error
c_func
(paren
l_string|&quot;pick-rref takes 2 args&quot;
)paren
suffix:semicolon
id|ls_remote_result
op_assign
id|argv
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ls_remote_result
comma
l_string|&quot;-&quot;
)paren
)paren
id|ls_remote_result
op_assign
id|get_stdin
c_func
(paren
)paren
suffix:semicolon
r_return
id|pick_rref
c_func
(paren
id|sopt
comma
id|argv
(braket
l_int|2
)braket
comma
id|ls_remote_result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;expand-refs-wildcard&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
)paren
(brace
r_const
r_char
op_star
id|reflist
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|4
)paren
r_return
id|error
c_func
(paren
l_string|&quot;expand-refs-wildcard takes at least 2 args&quot;
)paren
suffix:semicolon
id|reflist
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|reflist
comma
l_string|&quot;-&quot;
)paren
)paren
id|reflist
op_assign
id|get_stdin
c_func
(paren
)paren
suffix:semicolon
r_return
id|expand_refs_wildcard
c_func
(paren
id|reflist
comma
id|argc
l_int|3
comma
id|argv
op_plus
l_int|3
)paren
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;Unknown subcommand: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
eof
