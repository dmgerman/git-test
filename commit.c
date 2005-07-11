macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;cache.h&quot;
DECL|struct|sort_node
r_struct
id|sort_node
(brace
multiline_comment|/*&n;         * the number of children of the associated commit&n;         * that also occur in the list being sorted.&n;         */
DECL|member|indegree
r_int
r_int
id|indegree
suffix:semicolon
multiline_comment|/*&n;         * reference to original list item that we will re-use&n;         * on output.&n;         */
DECL|member|list_item
r_struct
id|commit_list
op_star
id|list_item
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|commit_type
r_const
r_char
op_star
id|commit_type
op_assign
l_string|&quot;commit&quot;
suffix:semicolon
DECL|function|get_commit_format
r_enum
id|cmit_fmt
id|get_commit_format
c_func
(paren
r_const
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|arg
)paren
r_return
id|CMIT_FMT_DEFAULT
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
l_string|&quot;=raw&quot;
)paren
)paren
r_return
id|CMIT_FMT_RAW
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
l_string|&quot;=medium&quot;
)paren
)paren
r_return
id|CMIT_FMT_MEDIUM
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
l_string|&quot;=short&quot;
)paren
)paren
r_return
id|CMIT_FMT_SHORT
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
l_string|&quot;=full&quot;
)paren
)paren
r_return
id|CMIT_FMT_FULL
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid --pretty format&quot;
)paren
suffix:semicolon
)brace
DECL|function|check_commit
r_static
r_struct
id|commit
op_star
id|check_commit
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|commit_type
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Object %s is a %s, not a commit&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|obj-&gt;type
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_struct
id|commit
op_star
)paren
id|obj
suffix:semicolon
)brace
DECL|function|lookup_commit_reference
r_struct
id|commit
op_star
id|lookup_commit_reference
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
id|object
op_star
id|obj
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|obj-&gt;type
op_eq
id|tag_type
)paren
id|obj
op_assign
id|parse_object
c_func
(paren
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
)paren
op_member_access_from_pointer
id|tagged-&gt;sha1
)paren
suffix:semicolon
r_return
id|check_commit
c_func
(paren
id|obj
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|lookup_commit
r_struct
id|commit
op_star
id|lookup_commit
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
id|object
op_star
id|obj
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
(brace
r_struct
id|commit
op_star
id|ret
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|commit
)paren
)paren
suffix:semicolon
id|created_object
c_func
(paren
id|sha1
comma
op_amp
id|ret-&gt;object
)paren
suffix:semicolon
id|ret-&gt;object.type
op_assign
id|commit_type
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;type
)paren
id|obj-&gt;type
op_assign
id|commit_type
suffix:semicolon
r_return
id|check_commit
c_func
(paren
id|obj
comma
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|parse_commit_date
r_static
r_int
r_int
id|parse_commit_date
c_func
(paren
r_const
r_char
op_star
id|buf
)paren
(brace
r_int
r_int
id|date
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buf
comma
l_string|&quot;author&quot;
comma
l_int|6
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|buf
op_increment
op_ne
l_char|&squot;&bslash;n&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buf
comma
l_string|&quot;committer&quot;
comma
l_int|9
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|buf
op_increment
op_ne
l_char|&squot;&gt;&squot;
)paren
multiline_comment|/* nada */
suffix:semicolon
id|date
op_assign
id|strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|date
op_eq
id|ULONG_MAX
)paren
id|date
op_assign
l_int|0
suffix:semicolon
r_return
id|date
suffix:semicolon
)brace
DECL|function|parse_commit_buffer
r_int
id|parse_commit_buffer
c_func
(paren
r_struct
id|commit
op_star
id|item
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|bufptr
op_assign
id|buffer
suffix:semicolon
r_int
r_char
id|parent
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit_list
op_star
op_star
id|pptr
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.parsed
)paren
r_return
l_int|0
suffix:semicolon
id|item-&gt;object.parsed
op_assign
l_int|1
suffix:semicolon
id|get_sha1_hex
c_func
(paren
id|bufptr
op_plus
l_int|5
comma
id|parent
)paren
suffix:semicolon
id|item-&gt;tree
op_assign
id|lookup_tree
c_func
(paren
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;tree
)paren
id|add_ref
c_func
(paren
op_amp
id|item-&gt;object
comma
op_amp
id|item-&gt;tree-&gt;object
)paren
suffix:semicolon
id|bufptr
op_add_assign
l_int|46
suffix:semicolon
multiline_comment|/* &quot;tree &quot; + &quot;hex sha1&quot; + &quot;&bslash;n&quot; */
id|pptr
op_assign
op_amp
id|item-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|bufptr
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
op_logical_and
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|bufptr
op_plus
l_int|7
comma
id|parent
)paren
)paren
(brace
r_struct
id|commit
op_star
id|new_parent
op_assign
id|lookup_commit
c_func
(paren
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_parent
)paren
(brace
id|pptr
op_assign
op_amp
id|commit_list_insert
c_func
(paren
id|new_parent
comma
id|pptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|add_ref
c_func
(paren
op_amp
id|item-&gt;object
comma
op_amp
id|new_parent-&gt;object
)paren
suffix:semicolon
)brace
id|bufptr
op_add_assign
l_int|48
suffix:semicolon
)brace
id|item-&gt;date
op_assign
id|parse_commit_date
c_func
(paren
id|bufptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_commit
r_int
id|parse_commit
c_func
(paren
r_struct
id|commit
op_star
id|item
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.parsed
)paren
r_return
l_int|0
suffix:semicolon
id|buffer
op_assign
id|read_sha1_file
c_func
(paren
id|item-&gt;object.sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not read %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|type
comma
id|commit_type
)paren
)paren
(brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Object %s not a commit&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|parse_commit_buffer
c_func
(paren
id|item
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|item-&gt;buffer
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|commit_list_insert
r_struct
id|commit_list
op_star
id|commit_list_insert
c_func
(paren
r_struct
id|commit
op_star
id|item
comma
r_struct
id|commit_list
op_star
op_star
id|list_p
)paren
(brace
r_struct
id|commit_list
op_star
id|new_list
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_list
)paren
)paren
suffix:semicolon
id|new_list-&gt;item
op_assign
id|item
suffix:semicolon
id|new_list-&gt;next
op_assign
op_star
id|list_p
suffix:semicolon
op_star
id|list_p
op_assign
id|new_list
suffix:semicolon
r_return
id|new_list
suffix:semicolon
)brace
DECL|function|free_commit_list
r_void
id|free_commit_list
c_func
(paren
r_struct
id|commit_list
op_star
id|list
)paren
(brace
r_while
c_loop
(paren
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|temp
op_assign
id|list
suffix:semicolon
id|list
op_assign
id|temp-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|temp
)paren
suffix:semicolon
)brace
)brace
DECL|function|insert_by_date
r_struct
id|commit_list
op_star
id|insert_by_date
c_func
(paren
r_struct
id|commit
op_star
id|item
comma
r_struct
id|commit_list
op_star
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
op_star
id|pp
op_assign
id|list
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
op_star
id|pp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;item-&gt;date
OL
id|item-&gt;date
)paren
(brace
r_break
suffix:semicolon
)brace
id|pp
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
)brace
r_return
id|commit_list_insert
c_func
(paren
id|item
comma
id|pp
)paren
suffix:semicolon
)brace
DECL|function|sort_by_date
r_void
id|sort_by_date
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|list
)paren
(brace
id|insert_by_date
c_func
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|item
comma
op_amp
id|ret
)paren
suffix:semicolon
op_star
id|list
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
op_star
id|list
op_assign
id|ret
suffix:semicolon
)brace
DECL|function|pop_most_recent_commit
r_struct
id|commit
op_star
id|pop_most_recent_commit
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
comma
r_int
r_int
id|mark
)paren
(brace
r_struct
id|commit
op_star
id|ret
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|item
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
id|ret-&gt;parents
suffix:semicolon
r_struct
id|commit_list
op_star
id|old
op_assign
op_star
id|list
suffix:semicolon
op_star
id|list
op_assign
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|free
c_func
(paren
id|old
)paren
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|parents-&gt;item
suffix:semicolon
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|commit-&gt;object.flags
op_amp
id|mark
)paren
)paren
(brace
id|commit-&gt;object.flags
op_or_assign
id|mark
suffix:semicolon
id|insert_by_date
c_func
(paren
id|commit
comma
id|list
)paren
suffix:semicolon
)brace
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic support for pretty-printing the header&n; */
DECL|function|get_one_line
r_static
r_int
id|get_one_line
c_func
(paren
r_const
r_char
op_star
id|msg
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_char
id|c
op_assign
op_star
id|msg
op_increment
suffix:semicolon
id|ret
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|add_user_info
r_static
r_int
id|add_user_info
c_func
(paren
r_const
r_char
op_star
id|what
comma
r_enum
id|cmit_fmt
id|fmt
comma
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|line
)paren
(brace
r_char
op_star
id|date
suffix:semicolon
r_int
r_int
id|namelen
suffix:semicolon
r_int
r_int
id|time
suffix:semicolon
r_int
id|tz
comma
id|ret
suffix:semicolon
id|date
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|date
)paren
r_return
l_int|0
suffix:semicolon
id|namelen
op_assign
op_increment
id|date
id|line
suffix:semicolon
id|time
op_assign
id|strtoul
c_func
(paren
id|date
comma
op_amp
id|date
comma
l_int|10
)paren
suffix:semicolon
id|tz
op_assign
id|strtol
c_func
(paren
id|date
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|ret
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s: %.*s&bslash;n&quot;
comma
id|what
comma
id|namelen
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fmt
op_eq
id|CMIT_FMT_MEDIUM
)paren
id|ret
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|ret
comma
l_string|&quot;Date:   %s&bslash;n&quot;
comma
id|show_date
c_func
(paren
id|time
comma
id|tz
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|is_empty_line
r_static
r_int
id|is_empty_line
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
op_logical_and
id|isspace
c_func
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
)paren
)paren
id|len
op_decrement
suffix:semicolon
r_return
op_logical_neg
id|len
suffix:semicolon
)brace
DECL|function|add_parent_info
r_static
r_int
id|add_parent_info
c_func
(paren
r_enum
id|cmit_fmt
id|fmt
comma
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|line
comma
r_int
id|parents
)paren
(brace
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|parents
)paren
(brace
r_case
l_int|1
suffix:colon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Go back to the previous line: 40 characters of previous parent, and one &squot;&bslash;n&squot; */
id|offset
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Merge: %.40s&bslash;n&quot;
comma
id|line
op_minus
l_int|41
)paren
suffix:semicolon
multiline_comment|/* Fallthrough */
r_default
suffix:colon
multiline_comment|/* Replace the previous &squot;&bslash;n&squot; with a space */
id|buf
(braket
id|offset
op_minus
l_int|1
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;%.40s&bslash;n&quot;
comma
id|line
op_plus
l_int|7
)paren
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|pretty_print_commit
r_int
r_int
id|pretty_print_commit
c_func
(paren
r_enum
id|cmit_fmt
id|fmt
comma
r_const
r_char
op_star
id|msg
comma
r_int
r_int
id|len
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|space
)paren
(brace
r_int
id|hdr
op_assign
l_int|1
comma
id|body
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
id|parents
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|line
op_assign
id|msg
suffix:semicolon
r_int
id|linelen
op_assign
id|get_one_line
c_func
(paren
id|msg
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|linelen
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We want some slop for indentation and a possible&n;&t;&t; * final &quot;...&quot;. Thus the &quot;+ 20&quot;.&n;&t;&t; */
r_if
c_cond
(paren
id|offset
op_plus
id|linelen
op_plus
l_int|20
OG
id|space
)paren
(brace
id|memcpy
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;    ...&bslash;n&quot;
comma
l_int|8
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|msg
op_add_assign
id|linelen
suffix:semicolon
id|len
op_sub_assign
id|linelen
suffix:semicolon
r_if
c_cond
(paren
id|hdr
)paren
(brace
r_if
c_cond
(paren
id|linelen
op_eq
l_int|1
)paren
(brace
id|hdr
op_assign
l_int|0
suffix:semicolon
id|buf
(braket
id|offset
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fmt
op_eq
id|CMIT_FMT_RAW
)paren
(brace
id|memcpy
c_func
(paren
id|buf
op_plus
id|offset
comma
id|line
comma
id|linelen
)paren
suffix:semicolon
id|offset
op_add_assign
id|linelen
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
id|linelen
op_ne
l_int|48
)paren
id|die
c_func
(paren
l_string|&quot;bad parent line in commit&quot;
)paren
suffix:semicolon
id|offset
op_add_assign
id|add_parent_info
c_func
(paren
id|fmt
comma
id|buf
op_plus
id|offset
comma
id|line
comma
op_increment
id|parents
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;author &quot;
comma
l_int|7
)paren
)paren
id|offset
op_add_assign
id|add_user_info
c_func
(paren
l_string|&quot;Author&quot;
comma
id|fmt
comma
id|buf
op_plus
id|offset
comma
id|line
op_plus
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fmt
op_eq
id|CMIT_FMT_FULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;committer &quot;
comma
l_int|10
)paren
)paren
id|offset
op_add_assign
id|add_user_info
c_func
(paren
l_string|&quot;Commit&quot;
comma
id|fmt
comma
id|buf
op_plus
id|offset
comma
id|line
op_plus
l_int|10
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_empty_line
c_func
(paren
id|line
comma
id|linelen
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|body
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|fmt
op_eq
id|CMIT_FMT_SHORT
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
id|body
op_assign
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|buf
op_plus
id|offset
comma
l_char|&squot; &squot;
comma
l_int|4
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
op_plus
id|offset
op_plus
l_int|4
comma
id|line
comma
id|linelen
)paren
suffix:semicolon
id|offset
op_add_assign
id|linelen
op_plus
l_int|4
suffix:semicolon
)brace
multiline_comment|/* Make sure there is an EOLN */
r_if
c_cond
(paren
id|buf
(braket
id|offset
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
id|offset
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buf
(braket
id|offset
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
DECL|function|pop_commit
r_struct
id|commit
op_star
id|pop_commit
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|stack
)paren
(brace
r_struct
id|commit_list
op_star
id|top
op_assign
op_star
id|stack
suffix:semicolon
r_struct
id|commit
op_star
id|item
op_assign
id|top
ques
c_cond
id|top-&gt;item
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|top
)paren
(brace
op_star
id|stack
op_assign
id|top-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|top
)paren
suffix:semicolon
)brace
r_return
id|item
suffix:semicolon
)brace
DECL|function|count_parents
r_int
id|count_parents
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
comma
id|count
op_increment
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Performs an in-place topological sort on the list supplied.&n; */
DECL|function|sort_in_topological_order
r_void
id|sort_in_topological_order
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|list
)paren
(brace
r_struct
id|commit_list
op_star
id|next
op_assign
op_star
id|list
suffix:semicolon
r_struct
id|commit_list
op_star
id|work
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
op_star
id|pptr
op_assign
id|list
suffix:semicolon
r_struct
id|sort_node
op_star
id|nodes
suffix:semicolon
r_struct
id|sort_node
op_star
id|next_nodes
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* determine the size of the list */
r_while
c_loop
(paren
id|next
)paren
(brace
id|next
op_assign
id|next-&gt;next
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
multiline_comment|/* allocate an array to help sort the list */
id|nodes
op_assign
id|xcalloc
c_func
(paren
id|count
comma
r_sizeof
(paren
op_star
id|nodes
)paren
)paren
suffix:semicolon
multiline_comment|/* link the list to the array */
id|next_nodes
op_assign
id|nodes
suffix:semicolon
id|next
op_assign
op_star
id|list
suffix:semicolon
r_while
c_loop
(paren
id|next
)paren
(brace
id|next_nodes-&gt;list_item
op_assign
id|next
suffix:semicolon
id|next-&gt;item-&gt;object.util
op_assign
id|next_nodes
suffix:semicolon
id|next_nodes
op_increment
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
multiline_comment|/* update the indegree */
id|next
op_assign
op_star
id|list
suffix:semicolon
r_while
c_loop
(paren
id|next
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
op_assign
id|next-&gt;item-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_struct
id|sort_node
op_star
id|pn
op_assign
(paren
r_struct
id|sort_node
op_star
)paren
id|parent-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
id|pn
)paren
id|pn-&gt;indegree
op_increment
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
multiline_comment|/* &n;         * find the tips&n;         *&n;         * tips are nodes not reachable from any other node in the list &n;         * &n;         * the tips serve as a starting set for the work queue.&n;         */
id|next
op_assign
op_star
id|list
suffix:semicolon
r_while
c_loop
(paren
id|next
)paren
(brace
r_struct
id|sort_node
op_star
id|node
op_assign
(paren
r_struct
id|sort_node
op_star
)paren
id|next-&gt;item-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;indegree
op_eq
l_int|0
)paren
(brace
id|commit_list_insert
c_func
(paren
id|next-&gt;item
comma
op_amp
id|work
)paren
suffix:semicolon
)brace
id|next
op_assign
id|next-&gt;next
suffix:semicolon
)brace
multiline_comment|/* process the list in topological order */
r_while
c_loop
(paren
id|work
)paren
(brace
r_struct
id|commit
op_star
id|work_item
op_assign
id|pop_commit
c_func
(paren
op_amp
id|work
)paren
suffix:semicolon
r_struct
id|sort_node
op_star
id|work_node
op_assign
(paren
r_struct
id|sort_node
op_star
)paren
id|work_item-&gt;object.util
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
op_assign
id|work_item-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_struct
id|sort_node
op_star
id|pn
op_assign
(paren
r_struct
id|sort_node
op_star
)paren
id|parent-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
id|pn
)paren
(brace
multiline_comment|/* &n;&t;&t;&t;&t; * parents are only enqueued for emission &n;                                 * when all their children have been emitted thereby&n;                                 * guaranteeing topological order.&n;                                 */
id|pn-&gt;indegree
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pn-&gt;indegree
)paren
id|commit_list_insert
c_func
(paren
id|parent
comma
op_amp
id|work
)paren
suffix:semicolon
)brace
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
multiline_comment|/*&n;                 * work_item is a commit all of whose children&n;                 * have already been emitted. we can emit it now.&n;                 */
op_star
id|pptr
op_assign
id|work_node-&gt;list_item
suffix:semicolon
id|pptr
op_assign
op_amp
(paren
op_star
id|pptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
op_star
id|pptr
op_assign
l_int|NULL
suffix:semicolon
id|work_item-&gt;object.util
op_assign
l_int|NULL
suffix:semicolon
)brace
id|free
c_func
(paren
id|nodes
)paren
suffix:semicolon
)brace
eof
