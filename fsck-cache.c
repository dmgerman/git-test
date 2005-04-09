macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;dirent.h&gt;
multiline_comment|/*&n; * These two functions should build up a graph in memory about&n; * what objects we&squot;ve referenced, and found, and types..&n; *&n; * Right now we don&squot;t do that kind of reachability checking. Yet.&n; */
DECL|function|mark_needs_sha1
r_static
r_void
id|mark_needs_sha1
c_func
(paren
r_int
r_char
op_star
id|parent
comma
r_const
r_char
op_star
id|type
comma
r_int
r_char
op_star
id|child
)paren
(brace
)brace
DECL|function|mark_sha1_seen
r_static
r_int
id|mark_sha1_seen
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_char
op_star
id|tag
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_tree
r_static
r_int
id|fsck_tree
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_while
c_loop
(paren
id|size
)paren
(brace
r_int
id|len
op_assign
l_int|1
op_plus
id|strlen
c_func
(paren
id|data
)paren
suffix:semicolon
r_int
r_char
op_star
id|file_sha1
op_assign
id|data
op_plus
id|len
suffix:semicolon
r_char
op_star
id|path
op_assign
id|strchr
c_func
(paren
id|data
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|len
op_plus
l_int|20
op_logical_or
op_logical_neg
id|path
)paren
r_return
l_int|1
suffix:semicolon
id|data
op_add_assign
id|len
op_plus
l_int|20
suffix:semicolon
id|size
op_sub_assign
id|len
op_plus
l_int|20
suffix:semicolon
id|mark_needs_sha1
c_func
(paren
id|sha1
comma
l_string|&quot;blob&quot;
comma
id|file_sha1
)paren
suffix:semicolon
)brace
)brace
DECL|function|fsck_commit
r_static
r_int
id|fsck_commit
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_char
id|parent_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;tree &quot;
comma
l_int|5
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|data
op_plus
l_int|5
comma
id|tree_sha1
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|mark_needs_sha1
c_func
(paren
id|sha1
comma
l_string|&quot;tree&quot;
comma
id|tree_sha1
)paren
suffix:semicolon
id|data
op_add_assign
l_int|5
op_plus
l_int|40
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* &quot;tree &quot; + &lt;hex sha1&gt; + &squot;&bslash;n&squot; */
r_while
c_loop
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|data
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
id|get_sha1_hex
c_func
(paren
id|data
op_plus
l_int|7
comma
id|parent_sha1
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|mark_needs_sha1
c_func
(paren
id|sha1
comma
l_string|&quot;commit&quot;
comma
id|parent_sha1
)paren
suffix:semicolon
id|data
op_add_assign
l_int|7
op_plus
l_int|40
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* &quot;parent &quot; + &lt;hex sha1&gt; + &squot;&bslash;n&squot; */
)brace
)brace
DECL|function|fsck_entry
r_static
r_int
id|fsck_entry
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_char
op_star
id|tag
comma
r_void
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|tag
comma
l_string|&quot;blob&quot;
)paren
)paren
(brace
multiline_comment|/* Nothing to check */
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|tag
comma
l_string|&quot;tree&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|fsck_tree
c_func
(paren
id|sha1
comma
id|data
comma
id|size
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|tag
comma
l_string|&quot;commit&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|fsck_commit
c_func
(paren
id|sha1
comma
id|data
comma
id|size
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
r_return
id|mark_sha1_seen
c_func
(paren
id|sha1
comma
id|tag
)paren
suffix:semicolon
)brace
DECL|function|fsck_name
r_static
r_int
id|fsck_name
c_func
(paren
r_char
op_star
id|hex
)paren
(brace
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
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
(brace
r_int
r_int
id|mapsize
suffix:semicolon
r_void
op_star
id|map
op_assign
id|map_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
)paren
(brace
r_char
id|type
(braket
l_int|100
)braket
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_void
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_sha1_signature
c_func
(paren
id|sha1
comma
id|map
comma
id|mapsize
)paren
)paren
id|buffer
op_assign
id|unpack_sha1_file
c_func
(paren
id|map
comma
id|mapsize
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_logical_and
op_logical_neg
id|fsck_entry
c_func
(paren
id|sha1
comma
id|type
comma
id|buffer
comma
id|size
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|fsck_dir
r_static
r_int
id|fsck_dir
c_func
(paren
r_int
id|i
comma
r_char
op_star
id|path
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;missing sha1 directory &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
id|name
(braket
l_int|100
)braket
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_int|38
suffix:colon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|i
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|name
op_plus
l_int|2
comma
id|de-&gt;d_name
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fsck_name
c_func
(paren
id|name
)paren
)paren
r_continue
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;bad sha1 file: %s/%s&bslash;n&quot;
comma
id|path
comma
id|de-&gt;d_name
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
id|i
suffix:semicolon
r_char
op_star
id|sha1_dir
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage
c_func
(paren
l_string|&quot;fsck-cache&quot;
)paren
suffix:semicolon
id|sha1_dir
op_assign
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
ques
c_cond
suffix:colon
id|DEFAULT_DB_ENVIRONMENT
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
r_static
r_char
id|dir
(braket
l_int|4096
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|dir
comma
l_string|&quot;%s/%02x&quot;
comma
id|sha1_dir
comma
id|i
)paren
suffix:semicolon
id|fsck_dir
c_func
(paren
id|i
comma
id|dir
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
