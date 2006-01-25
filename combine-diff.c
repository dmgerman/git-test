macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;quote.h&quot;
DECL|struct|path_list
r_struct
id|path_list
(brace
DECL|member|next
r_struct
id|path_list
op_star
id|next
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|parent_sha1
r_int
r_char
id|parent_sha1
(braket
id|FLEX_ARRAY
)braket
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|uninteresting
r_static
r_int
id|uninteresting
c_func
(paren
r_struct
id|diff_filepair
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|diff_unmodified_pair
c_func
(paren
id|p
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|p-&gt;one-&gt;mode
)paren
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|p-&gt;two-&gt;mode
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|intersect_paths
r_static
r_struct
id|path_list
op_star
id|intersect_paths
c_func
(paren
r_struct
id|path_list
op_star
id|curr
comma
r_int
id|n
comma
r_int
id|num_parent
)paren
(brace
r_struct
id|diff_queue_struct
op_star
id|q
op_assign
op_amp
id|diff_queued_diff
suffix:semicolon
r_struct
id|path_list
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
(brace
r_struct
id|path_list
op_star
id|list
op_assign
l_int|NULL
comma
op_star
op_star
id|tail
op_assign
op_amp
id|list
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|path
suffix:semicolon
r_if
c_cond
(paren
id|uninteresting
c_func
(paren
id|q-&gt;queue
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|path
op_assign
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|two-&gt;path
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|p
)paren
op_plus
id|len
op_plus
l_int|1
op_plus
id|num_parent
op_star
l_int|20
)paren
suffix:semicolon
id|p-&gt;path
op_assign
(paren
r_char
op_star
)paren
op_amp
(paren
id|p-&gt;parent_sha1
(braket
id|num_parent
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;path
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|p-&gt;path
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|p-&gt;len
op_assign
id|len
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;sha1
comma
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|two-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;parent_sha1
(braket
id|n
)braket
comma
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|one-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
op_star
id|tail
op_assign
id|p
suffix:semicolon
id|tail
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
)brace
r_return
id|list
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|curr
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;len
)paren
r_continue
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|uninteresting
c_func
(paren
id|q-&gt;queue
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|path
op_assign
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|two-&gt;path
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|p-&gt;len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|path
comma
id|p-&gt;path
comma
id|len
)paren
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;parent_sha1
(braket
id|n
)braket
comma
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|one-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|p-&gt;len
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|curr
suffix:semicolon
)brace
DECL|struct|lline
r_struct
id|lline
(brace
DECL|member|next
r_struct
id|lline
op_star
id|next
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|parent_map
r_int
r_int
id|parent_map
suffix:semicolon
DECL|member|line
r_char
id|line
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sline
r_struct
id|sline
(brace
DECL|member|lost_head
DECL|member|lost_tail
r_struct
id|lline
op_star
id|lost_head
comma
op_star
op_star
id|lost_tail
suffix:semicolon
DECL|member|bol
r_char
op_star
id|bol
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
)brace
suffix:semicolon
DECL|function|grab_blob
r_static
r_char
op_star
id|grab_blob
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_char
op_star
id|blob
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|sha1
comma
id|null_sha1
comma
l_int|20
)paren
)paren
(brace
multiline_comment|/* deleted blob */
op_star
id|size
op_assign
l_int|0
suffix:semicolon
r_return
id|xcalloc
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
id|blob
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
id|size
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
l_string|&quot;blob&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;object &squot;%s&squot; is not a blob!&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
id|blob
suffix:semicolon
)brace
DECL|macro|TMPPATHLEN
mdefine_line|#define TMPPATHLEN 50
DECL|macro|MAXLINELEN
mdefine_line|#define MAXLINELEN 10240
DECL|function|write_to_temp_file
r_static
r_void
id|write_to_temp_file
c_func
(paren
r_char
op_star
id|tmpfile
comma
r_void
op_star
id|blob
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|fd
op_assign
id|git_mkstemp
c_func
(paren
id|tmpfile
comma
id|TMPPATHLEN
comma
l_string|&quot;.diff_XXXXXX&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to create temp-file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|blob
comma
id|size
)paren
op_ne
id|size
)paren
id|die
c_func
(paren
l_string|&quot;unable to write temp-file&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|write_temp_blob
r_static
r_void
id|write_temp_blob
c_func
(paren
r_char
op_star
id|tmpfile
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|blob
suffix:semicolon
id|blob
op_assign
id|grab_blob
c_func
(paren
id|sha1
comma
op_amp
id|size
)paren
suffix:semicolon
id|write_to_temp_file
c_func
(paren
id|tmpfile
comma
id|blob
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|blob
)paren
suffix:semicolon
)brace
DECL|function|parse_num
r_static
r_int
id|parse_num
c_func
(paren
r_char
op_star
op_star
id|cp_p
comma
r_int
r_int
op_star
id|num_p
)paren
(brace
r_char
op_star
id|cp
op_assign
op_star
id|cp_p
suffix:semicolon
r_int
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_int
id|read_some
suffix:semicolon
r_while
c_loop
(paren
l_char|&squot;0&squot;
op_le
op_star
id|cp
op_logical_and
op_star
id|cp
op_le
l_char|&squot;9&squot;
)paren
id|num
op_assign
id|num
op_star
l_int|10
op_plus
op_star
id|cp
op_increment
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|read_some
op_assign
id|cp
op_star
id|cp_p
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|cp_p
op_assign
id|cp
suffix:semicolon
op_star
id|num_p
op_assign
id|num
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_hunk_header
r_static
r_int
id|parse_hunk_header
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
r_int
op_star
id|ob
comma
r_int
r_int
op_star
id|on
comma
r_int
r_int
op_star
id|nb
comma
r_int
r_int
op_star
id|nn
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
id|cp
op_assign
id|line
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|ob
)paren
)paren
(brace
id|bad_line
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;malformed diff output: %s&quot;
comma
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;,&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|on
)paren
)paren
r_goto
id|bad_line
suffix:semicolon
)brace
r_else
op_star
id|on
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot; &squot;
op_logical_or
op_star
id|cp
op_increment
op_ne
l_char|&squot;+&squot;
)paren
r_goto
id|bad_line
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|nb
)paren
)paren
r_goto
id|bad_line
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;,&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|parse_num
c_func
(paren
op_amp
id|cp
comma
id|nn
)paren
)paren
r_goto
id|bad_line
suffix:semicolon
)brace
r_else
op_star
id|nn
op_assign
l_int|1
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|memcmp
c_func
(paren
id|cp
comma
l_string|&quot; @@&quot;
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|append_lost
r_static
r_void
id|append_lost
c_func
(paren
r_struct
id|sline
op_star
id|sline
comma
r_int
id|n
comma
r_const
r_char
op_star
id|line
)paren
(brace
r_struct
id|lline
op_star
id|lline
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_int
r_int
id|this_mask
op_assign
(paren
l_int|1UL
op_lshift
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|len
op_decrement
suffix:semicolon
multiline_comment|/* Check to see if we can squash things */
r_if
c_cond
(paren
id|sline-&gt;lost_head
)paren
(brace
r_struct
id|lline
op_star
id|last_one
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We cannot squash it with earlier one */
r_for
c_loop
(paren
id|lline
op_assign
id|sline-&gt;lost_head
suffix:semicolon
id|lline
suffix:semicolon
id|lline
op_assign
id|lline-&gt;next
)paren
r_if
c_cond
(paren
id|lline-&gt;parent_map
op_amp
id|this_mask
)paren
id|last_one
op_assign
id|lline
suffix:semicolon
id|lline
op_assign
id|last_one
ques
c_cond
id|last_one-&gt;next
suffix:colon
id|sline-&gt;lost_head
suffix:semicolon
r_while
c_loop
(paren
id|lline
)paren
(brace
r_if
c_cond
(paren
id|lline-&gt;len
op_eq
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|lline-&gt;line
comma
id|line
comma
id|len
)paren
)paren
(brace
id|lline-&gt;parent_map
op_or_assign
id|this_mask
suffix:semicolon
r_return
suffix:semicolon
)brace
id|lline
op_assign
id|lline-&gt;next
suffix:semicolon
)brace
)brace
id|lline
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|lline
)paren
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|lline-&gt;len
op_assign
id|len
suffix:semicolon
id|lline-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|lline-&gt;parent_map
op_assign
id|this_mask
suffix:semicolon
id|memcpy
c_func
(paren
id|lline-&gt;line
comma
id|line
comma
id|len
)paren
suffix:semicolon
id|lline-&gt;line
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|sline-&gt;lost_tail
op_assign
id|lline
suffix:semicolon
id|sline-&gt;lost_tail
op_assign
op_amp
id|lline-&gt;next
suffix:semicolon
)brace
DECL|function|combine_diff
r_static
r_void
id|combine_diff
c_func
(paren
r_const
r_int
r_char
op_star
id|parent
comma
r_const
r_char
op_star
id|ourtmp
comma
r_struct
id|sline
op_star
id|sline
comma
r_int
id|cnt
comma
r_int
id|n
)paren
(brace
id|FILE
op_star
id|in
suffix:semicolon
r_char
id|parent_tmp
(braket
id|TMPPATHLEN
)braket
suffix:semicolon
r_char
id|cmd
(braket
id|TMPPATHLEN
op_star
l_int|2
op_plus
l_int|1024
)braket
suffix:semicolon
r_char
id|line
(braket
id|MAXLINELEN
)braket
suffix:semicolon
r_int
r_int
id|lno
comma
id|ob
comma
id|on
comma
id|nb
comma
id|nn
suffix:semicolon
r_int
r_int
id|pmask
op_assign
op_complement
(paren
l_int|1UL
op_lshift
id|n
)paren
suffix:semicolon
r_struct
id|sline
op_star
id|lost_bucket
op_assign
l_int|NULL
suffix:semicolon
id|write_temp_blob
c_func
(paren
id|parent_tmp
comma
id|parent
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|cmd
comma
l_string|&quot;diff --unified=0 -La/x -Lb/x &squot;%s&squot; &squot;%s&squot;&quot;
comma
id|parent_tmp
comma
id|ourtmp
)paren
suffix:semicolon
id|in
op_assign
id|popen
c_func
(paren
id|cmd
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
r_return
suffix:semicolon
id|lno
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|in
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|5
OL
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;@@ -&quot;
comma
id|line
comma
l_int|4
)paren
)paren
(brace
r_if
c_cond
(paren
id|parse_hunk_header
c_func
(paren
id|line
comma
id|len
comma
op_amp
id|ob
comma
op_amp
id|on
comma
op_amp
id|nb
comma
op_amp
id|nn
)paren
)paren
r_break
suffix:semicolon
id|lno
op_assign
id|nb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nb
)paren
(brace
multiline_comment|/* @@ -1,2 +0,0 @@ to remove the&n;&t;&t;&t;&t; * first two lines...&n;&t;&t;&t;&t; */
id|nb
op_assign
l_int|1
suffix:semicolon
)brace
id|lost_bucket
op_assign
op_amp
id|sline
(braket
id|nb
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* sline is 0 based */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|lost_bucket
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|line
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;-&squot;
suffix:colon
id|append_lost
c_func
(paren
id|lost_bucket
comma
id|n
comma
id|line
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|sline
(braket
id|lno
op_minus
l_int|1
)braket
dot
id|flag
op_and_assign
id|pmask
suffix:semicolon
id|lno
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fclose
c_func
(paren
id|in
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|parent_tmp
)paren
suffix:semicolon
)brace
DECL|variable|context
r_static
r_int
r_int
id|context
op_assign
l_int|3
suffix:semicolon
DECL|variable|combine_marker
r_static
r_char
id|combine_marker
op_assign
l_char|&squot;@&squot;
suffix:semicolon
DECL|function|interesting
r_static
r_int
id|interesting
c_func
(paren
r_struct
id|sline
op_star
id|sline
comma
r_int
r_int
id|all_mask
)paren
(brace
r_return
(paren
(paren
id|sline-&gt;flag
op_amp
id|all_mask
)paren
op_ne
id|all_mask
op_logical_or
id|sline-&gt;lost_head
)paren
suffix:semicolon
)brace
DECL|function|line_diff_parents
r_static
r_int
r_int
id|line_diff_parents
c_func
(paren
r_struct
id|sline
op_star
id|sline
comma
r_int
r_int
id|all_mask
)paren
(brace
multiline_comment|/*&n;&t; * Look at the line and see from which parents we have difference.&n;&t; * Lower bits of sline-&gt;flag records if the parent had this line,&n;&t; * so XOR with all_mask gives us on-bits for parents we have&n;&t; * differences with.&n;&t; */
r_int
r_int
id|parents
op_assign
(paren
id|sline-&gt;flag
op_xor
id|all_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sline-&gt;lost_head
)paren
(brace
r_struct
id|lline
op_star
id|ll
suffix:semicolon
r_for
c_loop
(paren
id|ll
op_assign
id|sline-&gt;lost_head
suffix:semicolon
id|ll
suffix:semicolon
id|ll
op_assign
id|ll-&gt;next
)paren
id|parents
op_or_assign
id|ll-&gt;parent_map
suffix:semicolon
)brace
r_return
id|parents
op_amp
id|all_mask
suffix:semicolon
)brace
DECL|function|make_hunks
r_static
r_void
id|make_hunks
c_func
(paren
r_struct
id|sline
op_star
id|sline
comma
r_int
r_int
id|cnt
comma
r_int
id|num_parent
comma
r_int
id|dense
)paren
(brace
r_int
r_int
id|all_mask
op_assign
(paren
l_int|1UL
op_lshift
id|num_parent
)paren
l_int|1
suffix:semicolon
r_int
r_int
id|mark
op_assign
(paren
l_int|1UL
op_lshift
id|num_parent
)paren
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|cnt
)paren
(brace
r_if
c_cond
(paren
id|interesting
c_func
(paren
op_amp
id|sline
(braket
id|i
)braket
comma
id|all_mask
)paren
)paren
(brace
r_int
r_int
id|j
op_assign
(paren
id|context
OL
id|i
)paren
ques
c_cond
id|i
id|context
suffix:colon
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|j
op_le
id|i
)paren
id|sline
(braket
id|j
op_increment
)braket
dot
id|flag
op_or_assign
id|mark
suffix:semicolon
r_while
c_loop
(paren
op_increment
id|i
OL
id|cnt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|interesting
c_func
(paren
op_amp
id|sline
(braket
id|i
)braket
comma
id|all_mask
)paren
)paren
r_break
suffix:semicolon
id|sline
(braket
id|i
)braket
dot
id|flag
op_or_assign
id|mark
suffix:semicolon
)brace
id|j
op_assign
(paren
id|i
op_plus
id|context
OL
id|cnt
)paren
ques
c_cond
id|i
op_plus
id|context
suffix:colon
id|cnt
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|j
)paren
id|sline
(braket
id|i
op_increment
)braket
dot
id|flag
op_or_assign
id|mark
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dense
)paren
r_return
suffix:semicolon
multiline_comment|/* Look at each hunk, and if it contains changes from only&n;&t; * one parent, mark that uninteresting.&n;&t; */
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|cnt
)paren
(brace
r_int
id|j
comma
id|hunk_end
comma
id|diffs
suffix:semicolon
r_int
r_int
id|parents
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|cnt
op_logical_and
op_logical_neg
(paren
id|sline
(braket
id|i
)braket
dot
id|flag
op_amp
id|mark
)paren
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_le
id|i
)paren
r_break
suffix:semicolon
multiline_comment|/* No more interesting hunks */
r_for
c_loop
(paren
id|hunk_end
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|hunk_end
OL
id|cnt
suffix:semicolon
id|hunk_end
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|sline
(braket
id|hunk_end
)braket
dot
id|flag
op_amp
id|mark
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* [i..hunk_end) are interesting.  Now is it from&n;&t;&t; * only one parent?&n;&t;&t; * If lost lines are only from one parent and&n;&t;&t; * remaining lines existed in parents other than&n;&t;&t; * that parent, then the hunk is not that interesting.&n;&t;&t; */
id|parents
op_assign
l_int|0
suffix:semicolon
id|diffs
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OL
id|hunk_end
suffix:semicolon
id|j
op_increment
)paren
id|parents
op_or_assign
id|line_diff_parents
c_func
(paren
id|sline
op_plus
id|j
comma
id|all_mask
)paren
suffix:semicolon
multiline_comment|/* Now, how many bits from [0..num_parent) are on? */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_parent
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|parents
op_amp
(paren
l_int|1UL
op_lshift
id|j
)paren
)paren
id|diffs
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|diffs
OL
l_int|2
)paren
(brace
multiline_comment|/* This hunk is not that interesting after all */
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OL
id|hunk_end
suffix:semicolon
id|j
op_increment
)paren
id|sline
(braket
id|j
)braket
dot
id|flag
op_and_assign
op_complement
id|mark
suffix:semicolon
)brace
id|i
op_assign
id|hunk_end
suffix:semicolon
)brace
)brace
DECL|function|dump_sline
r_static
r_void
id|dump_sline
c_func
(paren
r_struct
id|sline
op_star
id|sline
comma
r_int
id|cnt
comma
r_int
id|num_parent
)paren
(brace
r_int
r_int
id|mark
op_assign
(paren
l_int|1UL
op_lshift
id|num_parent
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|lno
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|sline
op_star
id|sl
op_assign
op_amp
id|sline
(braket
id|lno
)braket
suffix:semicolon
r_int
id|hunk_end
suffix:semicolon
r_while
c_loop
(paren
id|lno
OL
id|cnt
op_logical_and
op_logical_neg
(paren
id|sline
(braket
id|lno
)braket
dot
id|flag
op_amp
id|mark
)paren
)paren
id|lno
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_le
id|lno
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|hunk_end
op_assign
id|lno
op_plus
l_int|1
suffix:semicolon
id|hunk_end
OL
id|cnt
suffix:semicolon
id|hunk_end
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|sline
(braket
id|hunk_end
)braket
dot
id|flag
op_amp
id|mark
)paren
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|num_parent
suffix:semicolon
id|i
op_increment
)paren
id|putchar
c_func
(paren
id|combine_marker
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; +%d,%d &quot;
comma
id|lno
op_plus
l_int|1
comma
id|hunk_end
op_minus
id|lno
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
op_le
id|num_parent
suffix:semicolon
id|i
op_increment
)paren
id|putchar
c_func
(paren
id|combine_marker
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lno
OL
id|hunk_end
)paren
(brace
r_struct
id|lline
op_star
id|ll
suffix:semicolon
r_int
id|j
suffix:semicolon
id|sl
op_assign
op_amp
id|sline
(braket
id|lno
op_increment
)braket
suffix:semicolon
id|ll
op_assign
id|sl-&gt;lost_head
suffix:semicolon
r_while
c_loop
(paren
id|ll
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_parent
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ll-&gt;parent_map
op_amp
(paren
l_int|1UL
op_lshift
id|j
)paren
)paren
id|putchar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
id|puts
c_func
(paren
id|ll-&gt;line
)paren
suffix:semicolon
id|ll
op_assign
id|ll-&gt;next
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_parent
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|1UL
op_lshift
id|j
)paren
op_amp
id|sl-&gt;flag
)paren
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;+&squot;
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot; %.*s&bslash;n&quot;
comma
id|sl-&gt;len
comma
id|sl-&gt;bol
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|show_combined_diff
r_static
r_void
id|show_combined_diff
c_func
(paren
r_struct
id|path_list
op_star
id|elem
comma
r_int
id|num_parent
comma
r_int
id|dense
)paren
(brace
r_int
r_int
id|size
comma
id|cnt
comma
id|lno
suffix:semicolon
r_char
op_star
id|result
comma
op_star
id|cp
comma
op_star
id|ep
suffix:semicolon
r_struct
id|sline
op_star
id|sline
suffix:semicolon
multiline_comment|/* survived lines */
r_int
id|i
suffix:semicolon
r_char
id|ourtmp
(braket
id|TMPPATHLEN
)braket
suffix:semicolon
multiline_comment|/* Read the result of merge first */
id|result
op_assign
id|grab_blob
c_func
(paren
id|elem-&gt;sha1
comma
op_amp
id|size
)paren
suffix:semicolon
id|write_to_temp_file
c_func
(paren
id|ourtmp
comma
id|result
comma
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
comma
id|cp
op_assign
id|result
suffix:semicolon
id|cp
id|result
OL
id|size
suffix:semicolon
id|cp
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|cnt
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
(braket
id|size
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|cnt
op_increment
suffix:semicolon
multiline_comment|/* incomplete line */
id|sline
op_assign
id|xcalloc
c_func
(paren
id|cnt
comma
r_sizeof
(paren
op_star
id|sline
)paren
)paren
suffix:semicolon
id|ep
op_assign
id|result
suffix:semicolon
id|sline
(braket
l_int|0
)braket
dot
id|bol
op_assign
id|result
suffix:semicolon
r_for
c_loop
(paren
id|lno
op_assign
l_int|0
comma
id|cp
op_assign
id|result
suffix:semicolon
id|cp
id|result
OL
id|size
suffix:semicolon
id|cp
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|sline
(braket
id|lno
)braket
dot
id|lost_tail
op_assign
op_amp
id|sline
(braket
id|lno
)braket
dot
id|lost_head
suffix:semicolon
id|sline
(braket
id|lno
)braket
dot
id|len
op_assign
id|cp
id|sline
(braket
id|lno
)braket
dot
id|bol
suffix:semicolon
id|sline
(braket
id|lno
)braket
dot
id|flag
op_assign
(paren
l_int|1UL
op_lshift
id|num_parent
)paren
l_int|1
suffix:semicolon
id|lno
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|lno
OL
id|cnt
)paren
id|sline
(braket
id|lno
)braket
dot
id|bol
op_assign
id|cp
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
(braket
id|size
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|sline
(braket
id|cnt
op_minus
l_int|1
)braket
dot
id|lost_tail
op_assign
op_amp
id|sline
(braket
id|cnt
op_minus
l_int|1
)braket
dot
id|lost_head
suffix:semicolon
id|sline
(braket
id|cnt
op_minus
l_int|1
)braket
dot
id|len
op_assign
id|size
(paren
id|sline
(braket
id|cnt
op_minus
l_int|1
)braket
dot
id|bol
id|result
)paren
suffix:semicolon
id|sline
(braket
id|cnt
op_minus
l_int|1
)braket
dot
id|flag
op_assign
(paren
l_int|1UL
op_lshift
id|num_parent
)paren
l_int|1
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
id|num_parent
suffix:semicolon
id|i
op_increment
)paren
id|combine_diff
c_func
(paren
id|elem-&gt;parent_sha1
(braket
id|i
)braket
comma
id|ourtmp
comma
id|sline
comma
id|cnt
comma
id|i
)paren
suffix:semicolon
id|make_hunks
c_func
(paren
id|sline
comma
id|cnt
comma
id|num_parent
comma
id|dense
)paren
suffix:semicolon
id|dump_sline
c_func
(paren
id|sline
comma
id|cnt
comma
id|num_parent
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|ourtmp
)paren
suffix:semicolon
id|free
c_func
(paren
id|result
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sline
(braket
id|i
)braket
dot
id|lost_head
)paren
(brace
r_struct
id|lline
op_star
id|ll
op_assign
id|sline
(braket
id|i
)braket
dot
id|lost_head
suffix:semicolon
r_while
c_loop
(paren
id|ll
)paren
(brace
r_struct
id|lline
op_star
id|tmp
op_assign
id|ll
suffix:semicolon
id|ll
op_assign
id|ll-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
)brace
)brace
id|free
c_func
(paren
id|sline
)paren
suffix:semicolon
)brace
DECL|function|diff_tree_combined_merge
r_int
id|diff_tree_combined_merge
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|header
comma
r_int
id|show_empty_merge
comma
r_int
id|dense
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|lookup_commit
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_struct
id|diff_options
id|diffopts
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_struct
id|path_list
op_star
id|p
comma
op_star
id|paths
op_assign
l_int|NULL
suffix:semicolon
r_int
id|num_parent
comma
id|i
comma
id|num_paths
suffix:semicolon
id|diff_setup
c_func
(paren
op_amp
id|diffopts
)paren
suffix:semicolon
id|diffopts.output_format
op_assign
id|DIFF_FORMAT_NO_OUTPUT
suffix:semicolon
id|diffopts.recursive
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* count parents */
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
comma
id|num_parent
op_assign
l_int|0
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
comma
id|num_parent
op_increment
)paren
suffix:semicolon
multiline_comment|/* nothing */
multiline_comment|/* find set of paths that everybody touches */
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
comma
id|i
op_increment
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|parent-&gt;object.sha1
comma
id|commit-&gt;object.sha1
comma
l_string|&quot;&quot;
comma
op_amp
id|diffopts
)paren
suffix:semicolon
id|paths
op_assign
id|intersect_paths
c_func
(paren
id|paths
comma
id|i
comma
id|num_parent
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|diffopts
)paren
suffix:semicolon
)brace
multiline_comment|/* find out surviving paths */
r_for
c_loop
(paren
id|num_paths
op_assign
l_int|0
comma
id|p
op_assign
id|paths
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;len
)paren
id|num_paths
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num_paths
op_logical_or
id|show_empty_merge
)paren
(brace
id|puts
c_func
(paren
id|header
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|paths
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;len
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;diff --combined &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|quote_c_style
c_func
(paren
id|p-&gt;path
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)paren
)paren
id|quote_c_style
c_func
(paren
id|p-&gt;path
comma
l_int|NULL
comma
id|stdout
comma
l_int|0
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|p-&gt;path
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|show_combined_diff
c_func
(paren
id|p
comma
id|num_parent
comma
id|dense
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Clean things up */
r_while
c_loop
(paren
id|paths
)paren
(brace
r_struct
id|path_list
op_star
id|tmp
op_assign
id|paths
suffix:semicolon
id|paths
op_assign
id|paths-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
