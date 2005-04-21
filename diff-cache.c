macro_line|#include &quot;cache.h&quot;
DECL|variable|cached_only
r_static
r_int
id|cached_only
op_assign
l_int|0
suffix:semicolon
DECL|variable|recursive
r_static
r_int
id|recursive
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
r_static
r_int
id|diff_cache
c_func
(paren
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_struct
id|cache_entry
op_star
op_star
id|ac
comma
r_int
id|entries
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
DECL|function|update_tree_entry
r_static
r_void
id|update_tree_entry
c_func
(paren
r_void
op_star
op_star
id|bufp
comma
r_int
r_int
op_star
id|sizep
)paren
(brace
r_void
op_star
id|buf
op_assign
op_star
id|bufp
suffix:semicolon
r_int
r_int
id|size
op_assign
op_star
id|sizep
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
op_plus
l_int|1
op_plus
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|len
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file 1 (%s)&quot;
comma
id|size
)paren
suffix:semicolon
op_star
id|bufp
op_assign
id|buf
op_plus
id|len
suffix:semicolon
op_star
id|sizep
op_assign
id|size
id|len
suffix:semicolon
)brace
DECL|function|extract
r_static
r_const
r_int
r_char
op_star
id|extract
c_func
(paren
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
op_star
id|pathp
comma
r_int
r_int
op_star
id|modep
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|tree
)paren
op_plus
l_int|1
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|tree
op_plus
id|len
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
id|strchr
c_func
(paren
id|tree
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
id|size
OL
id|len
op_plus
l_int|20
op_logical_or
id|sscanf
c_func
(paren
id|tree
comma
l_string|&quot;%o&quot;
comma
id|modep
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree file 2 (%d)&quot;
comma
id|size
)paren
suffix:semicolon
op_star
id|pathp
op_assign
id|path
op_plus
l_int|1
suffix:semicolon
r_return
id|sha1
suffix:semicolon
)brace
DECL|function|malloc_base
r_static
r_char
op_star
id|malloc_base
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_const
r_char
op_star
id|path
comma
r_int
id|pathlen
)paren
(brace
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_char
op_star
id|newbase
op_assign
id|malloc
c_func
(paren
id|baselen
op_plus
id|pathlen
op_plus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
comma
id|path
comma
id|pathlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
op_plus
id|pathlen
comma
l_string|&quot;/&quot;
comma
l_int|2
)paren
suffix:semicolon
r_return
id|newbase
suffix:semicolon
)brace
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
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|mode
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
multiline_comment|/* A whole sub-tree went away or appeared */
DECL|function|show_tree
r_static
r_void
id|show_tree
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_while
c_loop
(paren
id|size
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|extract
c_func
(paren
id|tree
comma
id|size
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|show_file
c_func
(paren
id|prefix
comma
id|path
comma
id|mode
comma
id|sha1
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|tree
comma
op_amp
id|size
)paren
suffix:semicolon
)brace
)brace
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
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|mode
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_if
c_cond
(paren
id|recursive
op_logical_and
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|newbase
op_assign
id|malloc_base
c_func
(paren
id|base
comma
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
r_void
op_star
id|tree
suffix:semicolon
id|tree
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
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
id|tree
op_logical_or
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;tree&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree sha %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|show_tree
c_func
(paren
id|prefix
comma
id|tree
comma
id|size
comma
id|newbase
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s%o&bslash;t%s&bslash;t%s&bslash;t%s%s%c&quot;
comma
id|prefix
comma
id|mode
comma
id|S_ISDIR
c_func
(paren
id|mode
)paren
ques
c_cond
l_string|&quot;tree&quot;
suffix:colon
l_string|&quot;blob&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|base
comma
id|path
comma
id|line_termination
)paren
suffix:semicolon
)brace
DECL|function|compare_tree_entry
r_static
r_int
id|compare_tree_entry
c_func
(paren
r_const
r_char
op_star
id|path1
comma
r_int
r_int
id|mode1
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|cache_entry
op_star
op_star
id|ac
comma
r_int
op_star
id|entries
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
op_star
id|ac
suffix:semicolon
r_const
r_char
op_star
id|path2
op_assign
id|ce-&gt;name
op_plus
id|baselen
suffix:semicolon
r_int
r_int
id|mode2
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha2
op_assign
id|ce-&gt;sha1
suffix:semicolon
r_int
id|cmp
comma
id|pathlen1
comma
id|pathlen2
suffix:semicolon
r_char
id|old_sha1_hex
(braket
l_int|50
)braket
suffix:semicolon
id|pathlen1
op_assign
id|strlen
c_func
(paren
id|path1
)paren
suffix:semicolon
id|pathlen2
op_assign
id|strlen
c_func
(paren
id|path2
)paren
suffix:semicolon
id|cmp
op_assign
id|cache_name_compare
c_func
(paren
id|path1
comma
id|pathlen1
comma
id|path2
comma
id|pathlen2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
)paren
(brace
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|tree
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_char
op_star
id|newbase
op_assign
id|malloc
c_func
(paren
id|baselen
op_plus
l_int|2
op_plus
id|pathlen1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
comma
id|path1
comma
id|pathlen1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newbase
op_plus
id|baselen
op_plus
id|pathlen1
comma
l_string|&quot;/&quot;
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
op_logical_or
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;tree&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
op_star
id|entries
op_assign
id|diff_cache
c_func
(paren
id|tree
comma
id|size
comma
id|ac
comma
op_star
id|entries
comma
id|newbase
)paren
suffix:semicolon
id|free
c_func
(paren
id|newbase
)paren
suffix:semicolon
id|free
c_func
(paren
id|tree
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|path1
comma
id|mode1
comma
id|sha1
comma
id|base
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
id|fd
comma
id|changed
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|ce-&gt;name
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|fstat
c_func
(paren
id|fd
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
id|path1
comma
id|mode1
comma
id|sha1
comma
id|base
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
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|changed
)paren
(brace
id|mode2
op_assign
id|st.st_mode
suffix:semicolon
id|sha2
op_assign
id|no_sha1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|path2
comma
id|mode2
comma
id|sha2
comma
id|base
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
id|memcmp
c_func
(paren
id|sha1
comma
id|sha2
comma
l_int|20
)paren
op_logical_and
id|mode1
op_eq
id|mode2
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If the filemode has changed to/from a directory from/to a regular&n;&t; * file, we need to consider it a remove and an add.&n;&t; */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode1
)paren
op_logical_or
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|path1
comma
id|mode1
comma
id|sha1
comma
id|base
)paren
suffix:semicolon
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|path2
comma
id|mode2
comma
id|sha2
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;*%o-&gt;%o&bslash;t%s&bslash;t%s-&gt;%s&bslash;t%s%s%c&quot;
comma
id|mode1
comma
id|mode2
comma
id|S_ISDIR
c_func
(paren
id|mode1
)paren
ques
c_cond
l_string|&quot;tree&quot;
suffix:colon
l_string|&quot;blob&quot;
comma
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|sha2
)paren
comma
id|base
comma
id|path1
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
r_void
op_star
id|tree
comma
r_int
r_int
id|size
comma
r_struct
id|cache_entry
op_star
op_star
id|ac
comma
r_int
id|entries
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_const
r_char
op_star
id|path
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|left
suffix:semicolon
multiline_comment|/*&n;&t;&t; * No entries in the cache (with this base)?&n;&t;&t; * Output the tree contents.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|entries
op_logical_or
id|ce_namelen
c_func
(paren
id|ce
op_assign
op_star
id|ac
)paren
OL
id|baselen
op_logical_or
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|base
comma
id|baselen
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
id|entries
suffix:semicolon
id|sha1
op_assign
id|extract
c_func
(paren
id|tree
comma
id|size
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|show_file
c_func
(paren
l_string|&quot;-&quot;
comma
id|path
comma
id|mode
comma
id|sha1
comma
id|base
)paren
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|tree
comma
op_amp
id|size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * No entries in the tree? Output the cache contents&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|show_file
c_func
(paren
l_string|&quot;+&quot;
comma
id|ce-&gt;name
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|ce-&gt;sha1
comma
l_string|&quot;&quot;
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
id|sha1
op_assign
id|extract
c_func
(paren
id|tree
comma
id|size
comma
op_amp
id|path
comma
op_amp
id|mode
)paren
suffix:semicolon
id|left
op_assign
id|entries
suffix:semicolon
r_switch
c_cond
(paren
id|compare_tree_entry
c_func
(paren
id|path
comma
id|mode
comma
id|sha1
comma
id|ac
comma
op_amp
id|left
comma
id|base
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|tree
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|left
OL
id|entries
)paren
(brace
id|ac
op_add_assign
(paren
id|entries
id|left
)paren
suffix:semicolon
id|entries
op_assign
id|left
suffix:semicolon
)brace
r_continue
suffix:semicolon
r_case
l_int|0
suffix:colon
id|update_tree_entry
c_func
(paren
op_amp
id|tree
comma
op_amp
id|size
)paren
suffix:semicolon
multiline_comment|/* Fallthrough */
r_case
l_int|1
suffix:colon
id|ac
op_increment
suffix:semicolon
id|entries
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;diff-cache: internal error&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
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
id|recursive
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
r_return
id|diff_cache
c_func
(paren
id|tree
comma
id|size
comma
id|active_cache
comma
id|active_nr
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
eof
