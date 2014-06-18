macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;fsck.h&quot;
DECL|function|fsck_walk_tree
r_static
r_int
id|fsck_walk_tree
c_func
(paren
r_struct
id|tree
op_star
id|tree
comma
id|fsck_walk_func
id|walk
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|parse_tree
c_func
(paren
id|tree
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|desc
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tree_entry
c_func
(paren
op_amp
id|desc
comma
op_amp
id|entry
)paren
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|entry.mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|entry.mode
)paren
)paren
id|result
op_assign
id|walk
c_func
(paren
op_amp
id|lookup_tree
c_func
(paren
id|entry.sha1
)paren
op_member_access_from_pointer
id|object
comma
id|OBJ_TREE
comma
id|data
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|entry.mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|entry.mode
)paren
)paren
id|result
op_assign
id|walk
c_func
(paren
op_amp
id|lookup_blob
c_func
(paren
id|entry.sha1
)paren
op_member_access_from_pointer
id|object
comma
id|OBJ_BLOB
comma
id|data
)paren
suffix:semicolon
r_else
(brace
id|result
op_assign
id|error
c_func
(paren
l_string|&quot;in tree %s: entry %s has bad mode %.6o&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tree-&gt;object.sha1
)paren
comma
id|entry.path
comma
id|entry.mode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|res
op_assign
id|result
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|fsck_walk_commit
r_static
r_int
id|fsck_walk_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
id|fsck_walk_func
id|walk
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|result
op_assign
id|walk
c_func
(paren
(paren
r_struct
id|object
op_star
)paren
id|commit-&gt;tree
comma
id|OBJ_TREE
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|res
op_assign
id|result
suffix:semicolon
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
id|result
op_assign
id|walk
c_func
(paren
(paren
r_struct
id|object
op_star
)paren
id|parents-&gt;item
comma
id|OBJ_COMMIT
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|res
op_assign
id|result
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|fsck_walk_tag
r_static
r_int
id|fsck_walk_tag
c_func
(paren
r_struct
id|tag
op_star
id|tag
comma
id|fsck_walk_func
id|walk
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|parse_tag
c_func
(paren
id|tag
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|walk
c_func
(paren
id|tag-&gt;tagged
comma
id|OBJ_ANY
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|fsck_walk
r_int
id|fsck_walk
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
id|fsck_walk_func
id|walk
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|obj-&gt;type
)paren
(brace
r_case
id|OBJ_BLOB
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|OBJ_TREE
suffix:colon
r_return
id|fsck_walk_tree
c_func
(paren
(paren
r_struct
id|tree
op_star
)paren
id|obj
comma
id|walk
comma
id|data
)paren
suffix:semicolon
r_case
id|OBJ_COMMIT
suffix:colon
r_return
id|fsck_walk_commit
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
comma
id|walk
comma
id|data
)paren
suffix:semicolon
r_case
id|OBJ_TAG
suffix:colon
r_return
id|fsck_walk_tag
c_func
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
comma
id|walk
comma
id|data
)paren
suffix:semicolon
r_default
suffix:colon
id|error
c_func
(paren
l_string|&quot;Unknown object type for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The entries in a tree are ordered in the _path_ order,&n; * which means that a directory entry is ordered by adding&n; * a slash to the end of it.&n; *&n; * So a directory called &quot;a&quot; is ordered _after_ a file&n; * called &quot;a.c&quot;, because &quot;a/&quot; sorts after &quot;a.c&quot;.&n; */
DECL|macro|TREE_UNORDERED
mdefine_line|#define TREE_UNORDERED (-1)
DECL|macro|TREE_HAS_DUPS
mdefine_line|#define TREE_HAS_DUPS  (-2)
DECL|function|verify_ordered
r_static
r_int
id|verify_ordered
c_func
(paren
r_int
id|mode1
comma
r_const
r_char
op_star
id|name1
comma
r_int
id|mode2
comma
r_const
r_char
op_star
id|name2
)paren
(brace
r_int
id|len1
op_assign
id|strlen
c_func
(paren
id|name1
)paren
suffix:semicolon
r_int
id|len2
op_assign
id|strlen
c_func
(paren
id|name2
)paren
suffix:semicolon
r_int
id|len
op_assign
id|len1
OL
id|len2
ques
c_cond
id|len1
suffix:colon
id|len2
suffix:semicolon
r_int
r_char
id|c1
comma
id|c2
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|cmp
op_assign
id|memcmp
c_func
(paren
id|name1
comma
id|name2
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
r_return
id|TREE_UNORDERED
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, the first &lt;len&gt; characters are the same.&n;&t; * Now we need to order the next one, but turn&n;&t; * a &squot;&bslash;0&squot; into a &squot;/&squot; for a directory entry.&n;&t; */
id|c1
op_assign
id|name1
(braket
id|len
)braket
suffix:semicolon
id|c2
op_assign
id|name2
(braket
id|len
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c1
op_logical_and
op_logical_neg
id|c2
)paren
multiline_comment|/*&n;&t;&t; * git-write-tree used to write out a nonsense tree that has&n;&t;&t; * entries with the same name, one blob and one tree.  Make&n;&t;&t; * sure we do not have duplicate entries.&n;&t;&t; */
r_return
id|TREE_HAS_DUPS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c1
op_logical_and
id|S_ISDIR
c_func
(paren
id|mode1
)paren
)paren
id|c1
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c2
op_logical_and
id|S_ISDIR
c_func
(paren
id|mode2
)paren
)paren
id|c2
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_return
id|c1
OL
id|c2
ques
c_cond
l_int|0
suffix:colon
id|TREE_UNORDERED
suffix:semicolon
)brace
DECL|function|fsck_tree
r_static
r_int
id|fsck_tree
c_func
(paren
r_struct
id|tree
op_star
id|item
comma
r_int
id|strict
comma
id|fsck_error
id|error_func
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
id|has_null_sha1
op_assign
l_int|0
suffix:semicolon
r_int
id|has_full_path
op_assign
l_int|0
suffix:semicolon
r_int
id|has_empty_name
op_assign
l_int|0
suffix:semicolon
r_int
id|has_dot
op_assign
l_int|0
suffix:semicolon
r_int
id|has_dotdot
op_assign
l_int|0
suffix:semicolon
r_int
id|has_dotgit
op_assign
l_int|0
suffix:semicolon
r_int
id|has_zero_pad
op_assign
l_int|0
suffix:semicolon
r_int
id|has_bad_modes
op_assign
l_int|0
suffix:semicolon
r_int
id|has_dup_entries
op_assign
l_int|0
suffix:semicolon
r_int
id|not_properly_sorted
op_assign
l_int|0
suffix:semicolon
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_int
id|o_mode
suffix:semicolon
r_const
r_char
op_star
id|o_name
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|desc
comma
id|item-&gt;buffer
comma
id|item-&gt;size
)paren
suffix:semicolon
id|o_mode
op_assign
l_int|0
suffix:semicolon
id|o_name
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|desc.size
)paren
(brace
r_int
id|mode
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
suffix:semicolon
id|sha1
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
id|has_null_sha1
op_or_assign
id|is_null_sha1
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|has_full_path
op_or_assign
op_logical_neg
op_logical_neg
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|has_empty_name
op_or_assign
op_logical_neg
op_star
id|name
suffix:semicolon
id|has_dot
op_or_assign
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|has_dotdot
op_or_assign
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|has_dotgit
op_or_assign
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;.git&quot;
)paren
suffix:semicolon
id|has_zero_pad
op_or_assign
op_star
(paren
r_char
op_star
)paren
id|desc.buffer
op_eq
l_char|&squot;0&squot;
suffix:semicolon
id|update_tree_entry
c_func
(paren
op_amp
id|desc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
multiline_comment|/*&n;&t;&t; * Standard modes..&n;&t;&t; */
r_case
id|S_IFREG
op_or
l_int|0755
suffix:colon
r_case
id|S_IFREG
op_or
l_int|0644
suffix:colon
r_case
id|S_IFLNK
suffix:colon
r_case
id|S_IFDIR
suffix:colon
r_case
id|S_IFGITLINK
suffix:colon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This is nonstandard, but we had a few of these&n;&t;&t; * early on when we honored the full set of mode&n;&t;&t; * bits..&n;&t;&t; */
r_case
id|S_IFREG
op_or
l_int|0664
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strict
)paren
r_break
suffix:semicolon
r_default
suffix:colon
id|has_bad_modes
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o_name
)paren
(brace
r_switch
c_cond
(paren
id|verify_ordered
c_func
(paren
id|o_mode
comma
id|o_name
comma
id|mode
comma
id|name
)paren
)paren
(brace
r_case
id|TREE_UNORDERED
suffix:colon
id|not_properly_sorted
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TREE_HAS_DUPS
suffix:colon
id|has_dup_entries
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|o_mode
op_assign
id|mode
suffix:semicolon
id|o_name
op_assign
id|name
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|has_null_sha1
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains entries pointing to null sha1&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_full_path
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains full pathnames&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_empty_name
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains empty pathname&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_dot
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains &squot;.&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_dotdot
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains &squot;..&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_dotgit
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains &squot;.git&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_zero_pad
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains zero-padded file modes&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_bad_modes
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_WARN
comma
l_string|&quot;contains bad file modes&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_dup_entries
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;contains duplicate file entries&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|not_properly_sorted
)paren
id|retval
op_add_assign
id|error_func
c_func
(paren
op_amp
id|item-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;not properly sorted&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fsck_ident
r_static
r_int
id|fsck_ident
c_func
(paren
r_const
r_char
op_star
op_star
id|ident
comma
r_struct
id|object
op_star
id|obj
comma
id|fsck_error
id|error_func
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|ident
op_eq
l_char|&squot;&lt;&squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - missing space before email&quot;
)paren
suffix:semicolon
op_star
id|ident
op_add_assign
id|strcspn
c_func
(paren
op_star
id|ident
comma
l_string|&quot;&lt;&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|ident
op_eq
l_char|&squot;&gt;&squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - bad name&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|ident
op_ne
l_char|&squot;&lt;&squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - missing email&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|ident
)paren
(braket
l_int|1
)braket
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - missing space before email&quot;
)paren
suffix:semicolon
(paren
op_star
id|ident
)paren
op_increment
suffix:semicolon
op_star
id|ident
op_add_assign
id|strcspn
c_func
(paren
op_star
id|ident
comma
l_string|&quot;&lt;&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|ident
op_ne
l_char|&squot;&gt;&squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - bad email&quot;
)paren
suffix:semicolon
(paren
op_star
id|ident
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|ident
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - missing space before date&quot;
)paren
suffix:semicolon
(paren
op_star
id|ident
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
op_star
id|ident
op_eq
l_char|&squot;0&squot;
op_logical_and
(paren
op_star
id|ident
)paren
(braket
l_int|1
)braket
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - zero-padded date&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|date_overflows
c_func
(paren
id|strtoul
c_func
(paren
op_star
id|ident
comma
op_amp
id|end
comma
l_int|10
)paren
)paren
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - date causes integer overflow&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
op_star
id|ident
op_logical_or
op_star
id|end
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - bad date&quot;
)paren
suffix:semicolon
op_star
id|ident
op_assign
id|end
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
op_star
id|ident
op_ne
l_char|&squot;+&squot;
op_logical_and
op_star
op_star
id|ident
op_ne
l_char|&squot;-&squot;
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
(paren
op_star
id|ident
)paren
(braket
l_int|1
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
(paren
op_star
id|ident
)paren
(braket
l_int|2
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
(paren
op_star
id|ident
)paren
(braket
l_int|3
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
(paren
op_star
id|ident
)paren
(braket
l_int|4
)braket
)paren
op_logical_or
(paren
(paren
op_star
id|ident
)paren
(braket
l_int|5
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid author/committer line - bad time zone&quot;
)paren
suffix:semicolon
(paren
op_star
id|ident
)paren
op_add_assign
l_int|6
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_commit
r_static
r_int
id|fsck_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
id|fsck_error
id|error_func
)paren
(brace
r_const
r_char
op_star
id|buffer
op_assign
id|commit-&gt;buffer
suffix:semicolon
r_int
r_char
id|tree_sha1
(braket
l_int|20
)braket
comma
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|commit_graft
op_star
id|graft
suffix:semicolon
r_int
id|parents
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skip_prefix
c_func
(paren
id|buffer
comma
l_string|&quot;tree &quot;
comma
op_amp
id|buffer
)paren
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid format - expected &squot;tree&squot; line&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|tree_sha1
)paren
op_logical_or
id|buffer
(braket
l_int|40
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid &squot;tree&squot; line format - bad sha1&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|41
suffix:semicolon
r_while
c_loop
(paren
id|skip_prefix
c_func
(paren
id|buffer
comma
l_string|&quot;parent &quot;
comma
op_amp
id|buffer
)paren
)paren
(brace
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
op_logical_or
id|buffer
(braket
l_int|40
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid &squot;parent&squot; line format - bad sha1&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|41
suffix:semicolon
id|parents
op_increment
suffix:semicolon
)brace
id|graft
op_assign
id|lookup_commit_graft
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|graft
)paren
(brace
r_struct
id|commit_list
op_star
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|parents
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|graft-&gt;nr_parent
op_eq
l_int|1
op_logical_and
op_logical_neg
id|parents
)paren
suffix:semicolon
multiline_comment|/* shallow commit */
r_else
r_if
c_cond
(paren
id|graft-&gt;nr_parent
op_ne
id|parents
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;graft objects missing&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|commit_list
op_star
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|p
op_logical_and
id|parents
)paren
(brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
id|parents
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
op_logical_or
id|parents
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;parent objects missing&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|skip_prefix
c_func
(paren
id|buffer
comma
l_string|&quot;author &quot;
comma
op_amp
id|buffer
)paren
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid format - expected &squot;author&squot; line&quot;
)paren
suffix:semicolon
id|err
op_assign
id|fsck_ident
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|commit-&gt;object
comma
id|error_func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skip_prefix
c_func
(paren
id|buffer
comma
l_string|&quot;committer &quot;
comma
op_amp
id|buffer
)paren
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;invalid format - expected &squot;committer&squot; line&quot;
)paren
suffix:semicolon
id|err
op_assign
id|fsck_ident
c_func
(paren
op_amp
id|buffer
comma
op_amp
id|commit-&gt;object
comma
id|error_func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;tree
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|commit-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;could not load commit&squot;s tree %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tree_sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_tag
r_static
r_int
id|fsck_tag
c_func
(paren
r_struct
id|tag
op_star
id|tag
comma
id|fsck_error
id|error_func
)paren
(brace
r_struct
id|object
op_star
id|tagged
op_assign
id|tag-&gt;tagged
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tagged
)paren
r_return
id|error_func
c_func
(paren
op_amp
id|tag-&gt;object
comma
id|FSCK_ERROR
comma
l_string|&quot;could not load tagged object&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_object
r_int
id|fsck_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_int
id|strict
comma
id|fsck_error
id|error_func
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;no valid object to fsck&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_BLOB
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
r_return
id|fsck_tree
c_func
(paren
(paren
r_struct
id|tree
op_star
)paren
id|obj
comma
id|strict
comma
id|error_func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_COMMIT
)paren
r_return
id|fsck_commit
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
comma
id|error_func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
r_return
id|fsck_tag
c_func
(paren
(paren
r_struct
id|tag
op_star
)paren
id|obj
comma
id|error_func
)paren
suffix:semicolon
r_return
id|error_func
c_func
(paren
id|obj
comma
id|FSCK_ERROR
comma
l_string|&quot;unknown type &squot;%d&squot; (internal fsck error)&quot;
comma
id|obj-&gt;type
)paren
suffix:semicolon
)brace
DECL|function|fsck_error_function
r_int
id|fsck_error_function
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_int
id|type
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;object %s:&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|sb
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s&quot;
comma
id|sb.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
