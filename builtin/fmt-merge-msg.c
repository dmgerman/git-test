macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;gpg-interface.h&quot;
DECL|variable|fmt_merge_msg_usage
r_static
r_const
r_char
op_star
r_const
id|fmt_merge_msg_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git fmt-merge-msg [-m &lt;message&gt;] [--log[=&lt;n&gt;]|--no-log] [--file &lt;file&gt;]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|shortlog_len
r_static
r_int
id|shortlog_len
suffix:semicolon
DECL|function|fmt_merge_msg_config
r_static
r_int
id|fmt_merge_msg_config
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
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;merge.log&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;merge.summary&quot;
)paren
)paren
(brace
r_int
id|is_bool
suffix:semicolon
id|shortlog_len
op_assign
id|git_config_bool_or_int
c_func
(paren
id|key
comma
id|value
comma
op_amp
id|is_bool
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_bool
op_logical_and
id|shortlog_len
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: negative length %s&quot;
comma
id|key
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bool
op_logical_and
id|shortlog_len
)paren
id|shortlog_len
op_assign
id|DEFAULT_MERGE_LOG_LEN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* merge data per repository where the merged tips came from */
DECL|struct|src_data
r_struct
id|src_data
(brace
DECL|member|branch
DECL|member|tag
DECL|member|r_branch
DECL|member|generic
r_struct
id|string_list
id|branch
comma
id|tag
comma
id|r_branch
comma
id|generic
suffix:semicolon
DECL|member|head_status
r_int
id|head_status
suffix:semicolon
)brace
suffix:semicolon
DECL|function|init_src_data
r_static
r_void
id|init_src_data
c_func
(paren
r_struct
id|src_data
op_star
id|data
)paren
(brace
id|data-&gt;branch.strdup_strings
op_assign
l_int|1
suffix:semicolon
id|data-&gt;tag.strdup_strings
op_assign
l_int|1
suffix:semicolon
id|data-&gt;r_branch.strdup_strings
op_assign
l_int|1
suffix:semicolon
id|data-&gt;generic.strdup_strings
op_assign
l_int|1
suffix:semicolon
)brace
DECL|variable|srcs
r_static
r_struct
id|string_list
id|srcs
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
DECL|variable|origins
r_static
r_struct
id|string_list
id|origins
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
DECL|function|handle_line
r_static
r_int
id|handle_line
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|i
comma
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_char
op_star
id|src
comma
op_star
id|origin
suffix:semicolon
r_struct
id|src_data
op_star
id|src_data
suffix:semicolon
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_int
id|pulling_head
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|43
op_logical_or
id|line
(braket
l_int|40
)braket
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|line
op_plus
l_int|41
comma
l_string|&quot;not-for-merge&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|41
)braket
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_return
l_int|2
suffix:semicolon
id|line
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
id|sha1
op_assign
id|xmalloc
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|i
op_assign
id|get_sha1
c_func
(paren
id|line
comma
id|sha1
)paren
suffix:semicolon
id|line
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
id|len
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|line
op_add_assign
l_int|42
suffix:semicolon
multiline_comment|/*&n;&t; * At this point, line points at the beginning of comment e.g.&n;&t; * &quot;branch &squot;frotz&squot; of git://that/repository.git&quot;.&n;&t; * Find the repository name and point it with src.&n;&t; */
id|src
op_assign
id|strstr
c_func
(paren
id|line
comma
l_string|&quot; of &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src
)paren
(brace
op_star
id|src
op_assign
l_int|0
suffix:semicolon
id|src
op_add_assign
l_int|4
suffix:semicolon
id|pulling_head
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|src
op_assign
id|line
suffix:semicolon
id|pulling_head
op_assign
l_int|1
suffix:semicolon
)brace
id|item
op_assign
id|unsorted_string_list_lookup
c_func
(paren
op_amp
id|srcs
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|item
)paren
(brace
id|item
op_assign
id|string_list_append
c_func
(paren
op_amp
id|srcs
comma
id|src
)paren
suffix:semicolon
id|item-&gt;util
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|src_data
)paren
)paren
suffix:semicolon
id|init_src_data
c_func
(paren
id|item-&gt;util
)paren
suffix:semicolon
)brace
id|src_data
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|pulling_head
)paren
(brace
id|origin
op_assign
id|src
suffix:semicolon
id|src_data-&gt;head_status
op_or_assign
l_int|1
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
id|line
comma
l_string|&quot;branch &quot;
)paren
)paren
(brace
id|origin
op_assign
id|line
op_plus
l_int|7
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|src_data-&gt;branch
comma
id|origin
)paren
suffix:semicolon
id|src_data-&gt;head_status
op_or_assign
l_int|2
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
id|line
comma
l_string|&quot;tag &quot;
)paren
)paren
(brace
id|origin
op_assign
id|line
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|src_data-&gt;tag
comma
id|origin
op_plus
l_int|4
)paren
suffix:semicolon
id|src_data-&gt;head_status
op_or_assign
l_int|2
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
id|line
comma
l_string|&quot;remote-tracking branch &quot;
)paren
)paren
(brace
id|origin
op_assign
id|line
op_plus
id|strlen
c_func
(paren
l_string|&quot;remote-tracking branch &quot;
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|src_data-&gt;r_branch
comma
id|origin
)paren
suffix:semicolon
id|src_data-&gt;head_status
op_or_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|origin
op_assign
id|src
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|src_data-&gt;generic
comma
id|line
)paren
suffix:semicolon
id|src_data-&gt;head_status
op_or_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;.&quot;
comma
id|src
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|src
comma
id|origin
)paren
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|origin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|origin
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;&squot;&squot;
op_logical_and
id|origin
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;&squot;&squot;
)paren
id|origin
op_assign
id|xmemdupz
c_func
(paren
id|origin
op_plus
l_int|1
comma
id|len
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
r_char
op_star
id|new_origin
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|origin
)paren
op_plus
id|strlen
c_func
(paren
id|src
)paren
op_plus
l_int|5
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|new_origin
comma
l_string|&quot;%s of %s&quot;
comma
id|origin
comma
id|src
)paren
suffix:semicolon
id|origin
op_assign
id|new_origin
suffix:semicolon
)brace
id|string_list_append
c_func
(paren
op_amp
id|origins
comma
id|origin
)paren
op_member_access_from_pointer
id|util
op_assign
id|sha1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|print_joined
r_static
r_void
id|print_joined
c_func
(paren
r_const
r_char
op_star
id|singular
comma
r_const
r_char
op_star
id|plural
comma
r_struct
id|string_list
op_star
id|list
comma
r_struct
id|strbuf
op_star
id|out
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;nr
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;nr
op_eq
l_int|1
)paren
(brace
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot;%s%s&quot;
comma
id|singular
comma
id|list-&gt;items
(braket
l_int|0
)braket
dot
id|string
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|out
comma
id|plural
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
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot;%s%s&quot;
comma
id|i
OG
l_int|0
ques
c_cond
l_string|&quot;, &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot; and %s&quot;
comma
id|list-&gt;items
(braket
id|list-&gt;nr
l_int|1
)braket
dot
id|string
)paren
suffix:semicolon
)brace
)brace
DECL|function|shortlog
r_static
r_void
id|shortlog
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_char
op_star
id|sha1
comma
r_struct
id|commit
op_star
id|head
comma
r_struct
id|rev_info
op_star
id|rev
comma
r_int
id|limit
comma
r_struct
id|strbuf
op_star
id|out
)paren
(brace
r_int
id|i
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|object
op_star
id|branch
suffix:semicolon
r_struct
id|string_list
id|subjects
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_int
id|flags
op_assign
id|UNINTERESTING
op_or
id|TREESAME
op_or
id|SEEN
op_or
id|SHOWN
op_or
id|ADDED
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
id|branch
op_assign
id|deref_tag
c_func
(paren
id|parse_object
c_func
(paren
id|sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|branch
op_logical_or
id|branch-&gt;type
op_ne
id|OBJ_COMMIT
)paren
r_return
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|rev-&gt;ignore_merges
op_assign
l_int|1
suffix:semicolon
id|add_pending_object
c_func
(paren
id|rev
comma
id|branch
comma
id|name
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
id|rev
comma
op_amp
id|head-&gt;object
comma
l_string|&quot;^HEAD&quot;
)paren
suffix:semicolon
id|head-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
id|rev
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* ignore merges */
r_if
c_cond
(paren
id|commit-&gt;parents
op_logical_and
id|commit-&gt;parents-&gt;next
)paren
r_continue
suffix:semicolon
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|subjects.nr
OG
id|limit
)paren
r_continue
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
l_string|&quot;%s&quot;
comma
op_amp
id|sb
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|strbuf_ltrim
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb.len
)paren
id|string_list_append
c_func
(paren
op_amp
id|subjects
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_else
id|string_list_append
c_func
(paren
op_amp
id|subjects
comma
id|strbuf_detach
c_func
(paren
op_amp
id|sb
comma
l_int|NULL
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|limit
)paren
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n* %s: (%d commits)&bslash;n&quot;
comma
id|name
comma
id|count
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot;&bslash;n* %s:&bslash;n&quot;
comma
id|name
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
id|subjects.nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|i
op_ge
id|limit
)paren
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot;  ...&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot;  %s&bslash;n&quot;
comma
id|subjects.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|branch
comma
id|flags
)paren
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|head
comma
id|flags
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|rev-&gt;commits
)paren
suffix:semicolon
id|rev-&gt;commits
op_assign
l_int|NULL
suffix:semicolon
id|rev-&gt;pending.nr
op_assign
l_int|0
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|subjects
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|fmt_merge_msg_title
r_static
r_void
id|fmt_merge_msg_title
c_func
(paren
r_struct
id|strbuf
op_star
id|out
comma
r_const
r_char
op_star
id|current_branch
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|sep
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;Merge &quot;
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
id|srcs.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|src_data
op_star
id|src_data
op_assign
id|srcs.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_const
r_char
op_star
id|subsep
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|out
comma
id|sep
)paren
suffix:semicolon
id|sep
op_assign
l_string|&quot;; &quot;
suffix:semicolon
r_if
c_cond
(paren
id|src_data-&gt;head_status
op_eq
l_int|1
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|out
comma
id|srcs.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|src_data-&gt;head_status
op_eq
l_int|3
)paren
(brace
id|subsep
op_assign
l_string|&quot;, &quot;
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|out
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|src_data-&gt;branch.nr
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|out
comma
id|subsep
)paren
suffix:semicolon
id|subsep
op_assign
l_string|&quot;, &quot;
suffix:semicolon
id|print_joined
c_func
(paren
l_string|&quot;branch &quot;
comma
l_string|&quot;branches &quot;
comma
op_amp
id|src_data-&gt;branch
comma
id|out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|src_data-&gt;r_branch.nr
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|out
comma
id|subsep
)paren
suffix:semicolon
id|subsep
op_assign
l_string|&quot;, &quot;
suffix:semicolon
id|print_joined
c_func
(paren
l_string|&quot;remote-tracking branch &quot;
comma
l_string|&quot;remote-tracking branches &quot;
comma
op_amp
id|src_data-&gt;r_branch
comma
id|out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|src_data-&gt;tag.nr
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|out
comma
id|subsep
)paren
suffix:semicolon
id|subsep
op_assign
l_string|&quot;, &quot;
suffix:semicolon
id|print_joined
c_func
(paren
l_string|&quot;tag &quot;
comma
l_string|&quot;tags &quot;
comma
op_amp
id|src_data-&gt;tag
comma
id|out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|src_data-&gt;generic.nr
)paren
(brace
id|strbuf_addstr
c_func
(paren
id|out
comma
id|subsep
)paren
suffix:semicolon
id|print_joined
c_func
(paren
l_string|&quot;commit &quot;
comma
l_string|&quot;commits &quot;
comma
op_amp
id|src_data-&gt;generic
comma
id|out
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
l_string|&quot;.&quot;
comma
id|srcs.items
(braket
id|i
)braket
dot
id|string
)paren
)paren
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot; of %s&quot;
comma
id|srcs.items
(braket
id|i
)braket
dot
id|string
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
l_string|&quot;master&quot;
comma
id|current_branch
)paren
)paren
id|strbuf_addch
c_func
(paren
id|out
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
id|out
comma
l_string|&quot; into %s&bslash;n&quot;
comma
id|current_branch
)paren
suffix:semicolon
)brace
DECL|function|fmt_tag_signature
r_static
r_void
id|fmt_tag_signature
c_func
(paren
r_struct
id|strbuf
op_star
id|tagbuf
comma
r_struct
id|strbuf
op_star
id|sig
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|len
)paren
(brace
r_const
r_char
op_star
id|tag_body
op_assign
id|strstr
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tag_body
)paren
(brace
id|tag_body
op_add_assign
l_int|2
suffix:semicolon
id|strbuf_add
c_func
(paren
id|tagbuf
comma
id|tag_body
comma
id|buf
op_plus
id|len
id|tag_body
)paren
suffix:semicolon
)brace
id|strbuf_complete_line
c_func
(paren
id|tagbuf
)paren
suffix:semicolon
id|strbuf_add_lines
c_func
(paren
id|tagbuf
comma
l_string|&quot;# &quot;
comma
id|sig-&gt;buf
comma
id|sig-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|fmt_merge_msg_sigs
r_static
r_void
id|fmt_merge_msg_sigs
c_func
(paren
r_struct
id|strbuf
op_star
id|out
)paren
(brace
r_int
id|i
comma
id|tag_number
op_assign
l_int|0
comma
id|first_tag
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
id|tagbuf
op_assign
id|STRBUF_INIT
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
id|origins.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
op_star
id|sha1
op_assign
id|origins.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
comma
id|len
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_struct
id|strbuf
id|sig
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|type
op_ne
id|OBJ_TAG
)paren
r_goto
id|next
suffix:semicolon
id|len
op_assign
id|parse_signature
c_func
(paren
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
id|len
)paren
suffix:semicolon
multiline_comment|/* merely annotated */
r_else
r_if
c_cond
(paren
id|verify_signed_buffer
c_func
(paren
id|buf
comma
id|len
comma
id|buf
op_plus
id|len
comma
id|size
id|len
comma
op_amp
id|sig
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sig.len
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|sig
comma
l_string|&quot;gpg verification failed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tag_number
op_increment
)paren
(brace
id|fmt_tag_signature
c_func
(paren
op_amp
id|tagbuf
comma
op_amp
id|sig
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|first_tag
op_assign
id|i
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tag_number
op_eq
l_int|2
)paren
(brace
r_struct
id|strbuf
id|tagline
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|tagline
comma
l_string|&quot;&bslash;n# %s&bslash;n&quot;
comma
id|origins.items
(braket
id|first_tag
)braket
dot
id|string
)paren
suffix:semicolon
id|strbuf_insert
c_func
(paren
op_amp
id|tagbuf
comma
l_int|0
comma
id|tagline.buf
comma
id|tagline.len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|tagline
)paren
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|tagbuf
comma
l_string|&quot;&bslash;n# %s&bslash;n&quot;
comma
id|origins.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
id|fmt_tag_signature
c_func
(paren
op_amp
id|tagbuf
comma
op_amp
id|sig
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|sig
)paren
suffix:semicolon
id|next
suffix:colon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tagbuf.len
)paren
(brace
id|strbuf_addch
c_func
(paren
id|out
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|strbuf_addbuf
c_func
(paren
id|out
comma
op_amp
id|tagbuf
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|tagbuf
)paren
suffix:semicolon
)brace
DECL|function|fmt_merge_msg
r_int
id|fmt_merge_msg
c_func
(paren
r_struct
id|strbuf
op_star
id|in
comma
r_struct
id|strbuf
op_star
id|out
comma
r_struct
id|fmt_merge_msg_opts
op_star
id|opts
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|pos
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|head_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|current_branch
suffix:semicolon
multiline_comment|/* get current branch */
id|current_branch
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current_branch
)paren
id|die
c_func
(paren
l_string|&quot;No current branch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|current_branch
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
id|current_branch
op_add_assign
l_int|11
suffix:semicolon
multiline_comment|/* get a line */
r_while
c_loop
(paren
id|pos
OL
id|in-&gt;len
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|newline
comma
op_star
id|p
op_assign
id|in-&gt;buf
op_plus
id|pos
suffix:semicolon
id|newline
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|len
op_assign
id|newline
ques
c_cond
id|newline
id|p
suffix:colon
id|strlen
c_func
(paren
id|p
)paren
suffix:semicolon
id|pos
op_add_assign
id|len
op_plus
op_logical_neg
op_logical_neg
id|newline
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|p
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|handle_line
c_func
(paren
id|p
)paren
)paren
id|die
(paren
l_string|&quot;Error in line %d: %.*s&quot;
comma
id|i
comma
id|len
comma
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opts-&gt;add_title
op_logical_and
id|srcs.nr
)paren
id|fmt_merge_msg_title
c_func
(paren
id|out
comma
id|current_branch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|origins.nr
)paren
id|fmt_merge_msg_sigs
c_func
(paren
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;shortlog_len
)paren
(brace
r_struct
id|commit
op_star
id|head
suffix:semicolon
r_struct
id|rev_info
id|rev
suffix:semicolon
id|head
op_assign
id|lookup_commit_or_die
c_func
(paren
id|head_sha1
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|rev.commit_format
op_assign
id|CMIT_FMT_ONELINE
suffix:semicolon
id|rev.ignore_merges
op_assign
l_int|1
suffix:semicolon
id|rev.limited
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|suffixcmp
c_func
(paren
id|out-&gt;buf
comma
l_string|&quot;&bslash;n&quot;
)paren
)paren
id|strbuf_addch
c_func
(paren
id|out
comma
l_char|&squot;&bslash;n&squot;
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
id|origins.nr
suffix:semicolon
id|i
op_increment
)paren
id|shortlog
c_func
(paren
id|origins.items
(braket
id|i
)braket
dot
id|string
comma
id|origins.items
(braket
id|i
)braket
dot
id|util
comma
id|head
comma
op_amp
id|rev
comma
id|opts-&gt;shortlog_len
comma
id|out
)paren
suffix:semicolon
)brace
id|strbuf_complete_line
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_fmt_merge_msg
r_int
id|cmd_fmt_merge_msg
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
r_const
r_char
op_star
id|inpath
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|message
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
(brace
id|OPTION_INTEGER
comma
l_int|0
comma
l_string|&quot;log&quot;
comma
op_amp
id|shortlog_len
comma
l_string|&quot;n&quot;
comma
l_string|&quot;populate log with at most &lt;n&gt; entries from shortlog&quot;
comma
id|PARSE_OPT_OPTARG
comma
l_int|NULL
comma
id|DEFAULT_MERGE_LOG_LEN
)brace
comma
(brace
id|OPTION_INTEGER
comma
l_int|0
comma
l_string|&quot;summary&quot;
comma
op_amp
id|shortlog_len
comma
l_string|&quot;n&quot;
comma
l_string|&quot;alias for --log (deprecated)&quot;
comma
id|PARSE_OPT_OPTARG
op_or
id|PARSE_OPT_HIDDEN
comma
l_int|NULL
comma
id|DEFAULT_MERGE_LOG_LEN
)brace
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;m&squot;
comma
l_string|&quot;message&quot;
comma
op_amp
id|message
comma
l_string|&quot;text&quot;
comma
l_string|&quot;use &lt;text&gt; as start of message&quot;
)paren
comma
id|OPT_FILENAME
c_func
(paren
l_char|&squot;F&squot;
comma
l_string|&quot;file&quot;
comma
op_amp
id|inpath
comma
l_string|&quot;file to read from&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|FILE
op_star
id|in
op_assign
id|stdin
suffix:semicolon
r_struct
id|strbuf
id|input
op_assign
id|STRBUF_INIT
comma
id|output
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|fmt_merge_msg_opts
id|opts
suffix:semicolon
id|git_config
c_func
(paren
id|fmt_merge_msg_config
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
id|fmt_merge_msg_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
id|usage_with_options
c_func
(paren
id|fmt_merge_msg_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shortlog_len
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Negative --log=%d&quot;
comma
id|shortlog_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inpath
op_logical_and
id|strcmp
c_func
(paren
id|inpath
comma
l_string|&quot;-&quot;
)paren
)paren
(brace
id|in
op_assign
id|fopen
c_func
(paren
id|inpath
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot open &squot;%s&squot;&quot;
comma
id|inpath
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|input
comma
id|fileno
c_func
(paren
id|in
)paren
comma
l_int|0
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;could not read input file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|output
comma
id|message
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
(paren
id|opts
)paren
)paren
suffix:semicolon
id|opts.add_title
op_assign
op_logical_neg
id|message
suffix:semicolon
id|opts.shortlog_len
op_assign
id|shortlog_len
suffix:semicolon
id|ret
op_assign
id|fmt_merge_msg
c_func
(paren
op_amp
id|input
comma
op_amp
id|output
comma
op_amp
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|write_in_full
c_func
(paren
id|STDOUT_FILENO
comma
id|output.buf
comma
id|output.len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
