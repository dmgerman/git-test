macro_line|#include &quot;cache.h&quot;
DECL|variable|cached_only
r_static
r_int
id|cached_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
multiline_comment|/* A file entry went away or appeared */
DECL|function|show_file
r_static
r_void
id|show_file
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s%o&bslash;t%s&bslash;t%s&bslash;t%s%c&quot;
comma
id|prefix
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
l_string|&quot;blob&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
comma
id|ce-&gt;name
comma
id|line_termination
)paren
suffix:semicolon
)brace
DECL|function|show_modified
r_static
r_int
id|show_modified
c_func
(paren
r_struct
id|cache_entry
op_star
id|old
comma
r_struct
id|cache_entry
op_star
r_new
)paren
(brace
r_int
r_int
id|mode
op_assign
id|ntohl
c_func
(paren
r_new
op_member_access_from_pointer
id|ce_mode
)paren
comma
id|oldmode
suffix:semicolon
r_int
r_char
op_star
id|sha1
op_assign
r_new
op_member_access_from_pointer
id|sha1
suffix:semicolon
r_int
r_char
id|old_sha1_hex
(braket
l_int|60
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cached_only
)paren
(brace
r_static
r_int
r_char
id|no_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|changed
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
r_new
op_member_access_from_pointer
id|name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|old
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|changed
op_assign
id|cache_match_stat
c_func
(paren
r_new
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mode
op_assign
id|st.st_mode
suffix:semicolon
id|sha1
op_assign
id|no_sha1
suffix:semicolon
)brace
)brace
id|oldmode
op_assign
id|ntohl
c_func
(paren
id|old-&gt;ce_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|oldmode
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|sha1
comma
id|old-&gt;sha1
comma
l_int|20
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|old-&gt;sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;*%o-&gt;%o&bslash;t%s&bslash;t%s-&gt;%s&bslash;t%s%c&quot;
comma
id|oldmode
comma
id|mode
comma
l_string|&quot;blob&quot;
comma
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|old-&gt;name
comma
id|line_termination
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|diff_cache
r_static
r_int
id|diff_cache
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|ac
comma
r_int
id|entries
)paren
(brace
r_while
c_loop
(paren
id|entries
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
op_star
id|ac
suffix:semicolon
multiline_comment|/* No matching 0-stage (current) entry? Show it as deleted */
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|ce
)paren
suffix:semicolon
id|ac
op_increment
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* No matching 1-stage (tree) entry? Show the current one as added */
r_if
c_cond
(paren
id|entries
op_eq
l_int|1
op_logical_or
op_logical_neg
id|same_name
c_func
(paren
id|ce
comma
id|ac
(braket
l_int|1
)braket
)paren
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|ce
)paren
suffix:semicolon
id|ac
op_increment
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|show_modified
c_func
(paren
id|ac
(braket
l_int|1
)braket
comma
id|ce
)paren
suffix:semicolon
id|ac
op_add_assign
l_int|2
suffix:semicolon
id|entries
op_sub_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remove_merge_entries
r_static
r_void
id|remove_merge_entries
c_func
(paren
r_void
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;U %s%c&quot;
comma
id|ce-&gt;name
comma
id|line_termination
)paren
suffix:semicolon
r_while
c_loop
(paren
id|remove_entry_at
c_func
(paren
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|active_cache
(braket
id|i
)braket
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|variable|diff_cache_usage
r_static
r_char
op_star
id|diff_cache_usage
op_assign
l_string|&quot;diff-cache [-r] [-z] [--cached] &lt;tree sha1&gt;&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|tree
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argc
OG
l_int|2
)paren
(brace
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
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
l_string|&quot;-r&quot;
)paren
)paren
(brace
multiline_comment|/* We accept the -r flag just to look like diff-tree */
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
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_termination
op_assign
l_char|&squot;&bslash;0&squot;
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
l_string|&quot;--cached&quot;
)paren
)paren
(brace
id|cached_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|diff_cache_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
op_logical_or
id|get_sha1_hex
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|tree_sha1
)paren
)paren
id|usage
c_func
(paren
id|diff_cache_usage
)paren
suffix:semicolon
id|remove_merge_entries
c_func
(paren
)paren
suffix:semicolon
id|tree
op_assign
id|read_tree_with_tree_or_commit_sha1
c_func
(paren
id|tree_sha1
comma
op_amp
id|size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
id|die
c_func
(paren
l_string|&quot;bad tree object %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_tree
c_func
(paren
id|tree
comma
id|size
comma
l_int|1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree object %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|diff_cache
c_func
(paren
id|active_cache
comma
id|active_nr
)paren
suffix:semicolon
)brace
eof
