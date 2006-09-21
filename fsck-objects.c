macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
DECL|macro|REACHABLE
mdefine_line|#define REACHABLE 0x0001
DECL|macro|SEEN
mdefine_line|#define SEEN      0x0002
DECL|variable|show_root
r_static
r_int
id|show_root
suffix:semicolon
DECL|variable|show_tags
r_static
r_int
id|show_tags
suffix:semicolon
DECL|variable|show_unreachable
r_static
r_int
id|show_unreachable
suffix:semicolon
DECL|variable|check_full
r_static
r_int
id|check_full
suffix:semicolon
DECL|variable|check_strict
r_static
r_int
id|check_strict
suffix:semicolon
DECL|variable|keep_cache_objects
r_static
r_int
id|keep_cache_objects
suffix:semicolon
DECL|variable|head_sha1
r_static
r_int
r_char
id|head_sha1
(braket
l_int|20
)braket
suffix:semicolon
macro_line|#ifdef NO_D_INO_IN_DIRENT
DECL|macro|SORT_DIRENT
mdefine_line|#define SORT_DIRENT 0
DECL|macro|DIRENT_SORT_HINT
mdefine_line|#define DIRENT_SORT_HINT(de) 0
macro_line|#else
DECL|macro|SORT_DIRENT
mdefine_line|#define SORT_DIRENT 1
DECL|macro|DIRENT_SORT_HINT
mdefine_line|#define DIRENT_SORT_HINT(de) ((de)-&gt;d_ino)
macro_line|#endif
DECL|function|objreport
r_static
r_void
id|objreport
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|severity
comma
r_const
r_char
op_star
id|err
comma
id|va_list
id|params
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s in %s %s: &quot;
comma
id|severity
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|vfprintf
c_func
(paren
id|stderr
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;&bslash;n&quot;
comma
id|stderr
)paren
suffix:semicolon
)brace
DECL|function|objerror
r_static
r_int
id|objerror
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
id|objreport
c_func
(paren
id|obj
comma
l_string|&quot;error&quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|objwarning
r_static
r_int
id|objwarning
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
id|objreport
c_func
(paren
id|obj
comma
l_string|&quot;warning&quot;
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|check_connectivity
r_static
r_void
id|check_connectivity
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|max
suffix:semicolon
multiline_comment|/* Look up all the requirements, warn about missing objects.. */
id|max
op_assign
id|get_max_object_index
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_struct
id|object_refs
op_star
id|refs
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
id|get_indexed_object
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;parsed
)paren
(brace
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
multiline_comment|/* it is in pack */
r_else
id|printf
c_func
(paren
l_string|&quot;missing %s %s&bslash;n&quot;
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|refs
op_assign
id|lookup_object_refs
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|refs
)paren
(brace
r_int
id|j
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
id|refs-&gt;count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|object
op_star
id|ref
op_assign
id|refs-&gt;ref
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;parsed
op_logical_or
(paren
id|has_sha1_file
c_func
(paren
id|ref-&gt;sha1
)paren
)paren
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;broken link from %7s %s&bslash;n&quot;
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;              to %7s %s&bslash;n&quot;
comma
r_typename
(paren
id|ref-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|show_unreachable
op_logical_and
op_logical_neg
(paren
id|obj-&gt;flags
op_amp
id|REACHABLE
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;unreachable %s %s&bslash;n&quot;
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;used
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;dangling %s %s&bslash;n&quot;
comma
r_typename
(paren
id|obj-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
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
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
id|has_full_path
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
r_const
r_int
r_char
op_star
id|o_sha1
suffix:semicolon
id|desc.buf
op_assign
id|item-&gt;buffer
suffix:semicolon
id|desc.size
op_assign
id|item-&gt;size
suffix:semicolon
id|o_mode
op_assign
l_int|0
suffix:semicolon
id|o_name
op_assign
l_int|NULL
suffix:semicolon
id|o_sha1
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
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;/&squot;
)paren
)paren
id|has_full_path
op_assign
l_int|1
suffix:semicolon
id|has_zero_pad
op_or_assign
op_star
(paren
r_char
op_star
)paren
id|desc.buf
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
id|check_strict
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
id|o_sha1
op_assign
id|sha1
suffix:semicolon
)brace
id|free
c_func
(paren
id|item-&gt;buffer
)paren
suffix:semicolon
id|item-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|has_full_path
)paren
(brace
id|objwarning
c_func
(paren
op_amp
id|item-&gt;object
comma
l_string|&quot;contains full pathnames&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_zero_pad
)paren
(brace
id|objwarning
c_func
(paren
op_amp
id|item-&gt;object
comma
l_string|&quot;contains zero-padded file modes&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_bad_modes
)paren
(brace
id|objwarning
c_func
(paren
op_amp
id|item-&gt;object
comma
l_string|&quot;contains bad file modes&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_dup_entries
)paren
(brace
id|retval
op_assign
id|objerror
c_func
(paren
op_amp
id|item-&gt;object
comma
l_string|&quot;contains duplicate file entries&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|not_properly_sorted
)paren
(brace
id|retval
op_assign
id|objerror
c_func
(paren
op_amp
id|item-&gt;object
comma
l_string|&quot;not properly sorted&quot;
)paren
suffix:semicolon
)brace
r_return
id|retval
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
)paren
(brace
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
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
l_string|&quot;tree &quot;
comma
l_int|5
)paren
)paren
r_return
id|objerror
c_func
(paren
op_amp
id|commit-&gt;object
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
op_plus
l_int|5
comma
id|tree_sha1
)paren
op_logical_or
id|buffer
(braket
l_int|45
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|objerror
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_string|&quot;invalid &squot;tree&squot; line format - bad sha1&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|46
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buffer
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
id|buffer
op_plus
l_int|7
comma
id|sha1
)paren
op_logical_or
id|buffer
(braket
l_int|47
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
id|objerror
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_string|&quot;invalid &squot;parent&squot; line format - bad sha1&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|48
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
l_string|&quot;author &quot;
comma
l_int|7
)paren
)paren
r_return
id|objerror
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_string|&quot;invalid format - expected &squot;author&squot; line&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|commit-&gt;buffer
)paren
suffix:semicolon
id|commit-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;tree
)paren
r_return
id|objerror
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_string|&quot;could not load commit&squot;s tree %s&quot;
comma
id|tree_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;parents
op_logical_and
id|show_root
)paren
id|printf
c_func
(paren
l_string|&quot;root %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;date
)paren
id|printf
c_func
(paren
l_string|&quot;bad commit date in %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
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
(brace
r_return
id|objerror
c_func
(paren
op_amp
id|tag-&gt;object
comma
l_string|&quot;could not load tagged object&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|show_tags
)paren
r_return
l_int|0
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;tagged %s %s&quot;
comma
r_typename
(paren
id|tagged-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|tagged-&gt;sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; (%s) in %s&bslash;n&quot;
comma
id|tag-&gt;tag
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_sha1
r_static
r_int
id|fsck_sha1
c_func
(paren
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
id|error
c_func
(paren
l_string|&quot;%s: object not found&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|SEEN
)paren
r_return
l_int|0
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SEEN
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
)paren
suffix:semicolon
multiline_comment|/* By now, parse_object() would&squot;ve returned NULL instead. */
r_return
id|objerror
c_func
(paren
id|obj
comma
l_string|&quot;unknown type &squot;%d&squot; (internal fsck error)&quot;
comma
id|obj-&gt;type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the sorting chunk size: make it reasonably&n; * big so that we can sort well..&n; */
DECL|macro|MAX_SHA1_ENTRIES
mdefine_line|#define MAX_SHA1_ENTRIES (1024)
DECL|struct|sha1_entry
r_struct
id|sha1_entry
(brace
DECL|member|ino
r_int
r_int
id|ino
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|entry
r_struct
id|sha1_entry
op_star
id|entry
(braket
id|MAX_SHA1_ENTRIES
)braket
suffix:semicolon
DECL|variable|sha1_list
)brace
id|sha1_list
suffix:semicolon
DECL|function|ino_compare
r_static
r_int
id|ino_compare
c_func
(paren
r_const
r_void
op_star
id|_a
comma
r_const
r_void
op_star
id|_b
)paren
(brace
r_const
r_struct
id|sha1_entry
op_star
id|a
op_assign
id|_a
comma
op_star
id|b
op_assign
id|_b
suffix:semicolon
r_int
r_int
id|ino1
op_assign
id|a-&gt;ino
comma
id|ino2
op_assign
id|b-&gt;ino
suffix:semicolon
r_return
id|ino1
template_param
id|ino2
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_sha1_list
r_static
r_void
id|fsck_sha1_list
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|nr
op_assign
id|sha1_list.nr
suffix:semicolon
r_if
c_cond
(paren
id|SORT_DIRENT
)paren
id|qsort
c_func
(paren
id|sha1_list.entry
comma
id|nr
comma
r_sizeof
(paren
r_struct
id|sha1_entry
op_star
)paren
comma
id|ino_compare
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sha1_entry
op_star
id|entry
op_assign
id|sha1_list.entry
(braket
id|i
)braket
suffix:semicolon
r_int
r_char
op_star
id|sha1
op_assign
id|entry-&gt;sha1
suffix:semicolon
id|sha1_list.entry
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|fsck_sha1
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
id|sha1_list.nr
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|add_sha1_list
r_static
r_void
id|add_sha1_list
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
r_int
id|ino
)paren
(brace
r_struct
id|sha1_entry
op_star
id|entry
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
r_int
id|nr
suffix:semicolon
id|entry-&gt;ino
op_assign
id|ino
suffix:semicolon
id|hashcpy
c_func
(paren
id|entry-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|nr
op_assign
id|sha1_list.nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_eq
id|MAX_SHA1_ENTRIES
)paren
(brace
id|fsck_sha1_list
c_func
(paren
)paren
suffix:semicolon
id|nr
op_assign
l_int|0
suffix:semicolon
)brace
id|sha1_list.entry
(braket
id|nr
)braket
op_assign
id|entry
suffix:semicolon
id|sha1_list.nr
op_assign
op_increment
id|nr
suffix:semicolon
)brace
DECL|function|fsck_dir
r_static
r_void
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
r_return
suffix:semicolon
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
r_char
id|sha1
(braket
l_int|20
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
id|get_sha1_hex
c_func
(paren
id|name
comma
id|sha1
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|add_sha1_list
c_func
(paren
id|sha1
comma
id|DIRENT_SORT_HINT
c_func
(paren
id|de
)paren
)paren
suffix:semicolon
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
)brace
DECL|variable|default_refs
r_static
r_int
id|default_refs
suffix:semicolon
DECL|function|fsck_handle_ref
r_static
r_int
id|fsck_handle_ref
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
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|object
op_star
id|obj
suffix:semicolon
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
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
(brace
id|default_refs
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* it is in a pack */
)brace
id|error
c_func
(paren
l_string|&quot;%s: invalid sha1 pointer %s&quot;
comma
id|refname
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll continue with the rest despite the error.. */
r_return
l_int|0
suffix:semicolon
)brace
id|default_refs
op_increment
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
id|mark_reachable
c_func
(paren
id|obj
comma
id|REACHABLE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_default_heads
r_static
r_void
id|get_default_heads
c_func
(paren
r_void
)paren
(brace
id|for_each_ref
c_func
(paren
id|fsck_handle_ref
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Not having any default heads isn&squot;t really fatal, but&n;&t; * it does mean that &quot;--unreachable&quot; no longer makes any&n;&t; * sense (since in this case everything will obviously&n;&t; * be unreachable by definition.&n;&t; *&n;&t; * Showing dangling objects is valid, though (as those&n;&t; * dangling objects are likely lost heads).&n;&t; *&n;&t; * So we just print a warning about it, and clear the&n;&t; * &quot;show_unreachable&quot; flag.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|default_refs
)paren
(brace
id|error
c_func
(paren
l_string|&quot;No default references&quot;
)paren
suffix:semicolon
id|show_unreachable
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|fsck_object_dir
r_static
r_void
id|fsck_object_dir
c_func
(paren
r_const
r_char
op_star
id|path
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
id|path
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
id|fsck_sha1_list
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fsck_head_link
r_static
r_int
id|fsck_head_link
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|head_points_at
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head_points_at
)paren
r_return
id|error
c_func
(paren
l_string|&quot;HEAD is not a symbolic ref&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|head_points_at
comma
l_string|&quot;refs/heads/&quot;
comma
l_int|11
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;HEAD points to something strange (%s)&quot;
comma
id|head_points_at
)paren
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
id|error
c_func
(paren
l_string|&quot;HEAD: not a valid git pointer&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_cache_tree
r_static
r_int
id|fsck_cache_tree
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|it-&gt;entry_count
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
id|it-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
(brace
id|error
c_func
(paren
l_string|&quot;%s: invalid sha1 pointer in cache-tree&quot;
comma
id|sha1_to_hex
c_func
(paren
id|it-&gt;sha1
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|mark_reachable
c_func
(paren
id|obj
comma
id|REACHABLE
)paren
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|OBJ_TREE
)paren
id|err
op_or_assign
id|objerror
c_func
(paren
id|obj
comma
l_string|&quot;non-tree in cache-tree&quot;
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
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
id|err
op_or_assign
id|fsck_cache_tree
c_func
(paren
id|it-&gt;down
(braket
id|i
)braket
op_member_access_from_pointer
id|cache_tree
)paren
suffix:semicolon
r_return
id|err
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
comma
id|heads
suffix:semicolon
id|track_object_refs
op_assign
l_int|1
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
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
l_string|&quot;--unreachable&quot;
)paren
)paren
(brace
id|show_unreachable
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
l_string|&quot;--tags&quot;
)paren
)paren
(brace
id|show_tags
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
l_string|&quot;--root&quot;
)paren
)paren
(brace
id|show_root
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
l_string|&quot;--cache&quot;
)paren
)paren
(brace
id|keep_cache_objects
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
l_string|&quot;--full&quot;
)paren
)paren
(brace
id|check_full
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
l_string|&quot;--strict&quot;
)paren
)paren
(brace
id|check_strict
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
l_string|&quot;git-fsck-objects [--tags] [--root] [[--unreachable] [--cache] [--full] [--strict] &lt;head-sha1&gt;*]&quot;
)paren
suffix:semicolon
)brace
id|fsck_head_link
c_func
(paren
)paren
suffix:semicolon
id|fsck_object_dir
c_func
(paren
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_full
)paren
(brace
r_struct
id|alternate_object_database
op_star
id|alt
suffix:semicolon
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
id|prepare_alt_odb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|alt
op_assign
id|alt_odb_list
suffix:semicolon
id|alt
suffix:semicolon
id|alt
op_assign
id|alt-&gt;next
)paren
(brace
r_char
id|namebuf
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|namelen
op_assign
id|alt-&gt;name
id|alt-&gt;base
suffix:semicolon
id|memcpy
c_func
(paren
id|namebuf
comma
id|alt-&gt;base
comma
id|namelen
)paren
suffix:semicolon
id|namebuf
(braket
id|namelen
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|fsck_object_dir
c_func
(paren
id|namebuf
)paren
suffix:semicolon
)brace
id|prepare_packed_git
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|packed_git
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
multiline_comment|/* verify gives error messages itself */
id|verify_pack
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|packed_git
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|num
op_assign
id|num_packed_objects
c_func
(paren
id|p
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
suffix:semicolon
id|fsck_sha1
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
)brace
)brace
id|heads
op_assign
l_int|0
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
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|arg
comma
id|head_sha1
)paren
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
id|head_sha1
)paren
suffix:semicolon
multiline_comment|/* Error is printed by lookup_object(). */
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
r_continue
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
id|mark_reachable
c_func
(paren
id|obj
comma
id|REACHABLE
)paren
suffix:semicolon
id|heads
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|error
c_func
(paren
l_string|&quot;invalid parameter: expected sha1, got &squot;%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we&squot;ve not been given any explicit head information, do the&n;&t; * default ones from .git/refs. We also consider the index file&n;&t; * in this case (ie this implies --cache).&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|heads
)paren
(brace
id|get_default_heads
c_func
(paren
)paren
suffix:semicolon
id|keep_cache_objects
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|keep_cache_objects
)paren
(brace
r_int
id|i
suffix:semicolon
id|read_cache
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|blob
op_star
id|blob
op_assign
id|lookup_blob
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|sha1
)paren
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blob
)paren
r_continue
suffix:semicolon
id|obj
op_assign
op_amp
id|blob-&gt;object
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
id|mark_reachable
c_func
(paren
id|obj
comma
id|REACHABLE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|active_cache_tree
)paren
id|fsck_cache_tree
c_func
(paren
id|active_cache_tree
)paren
suffix:semicolon
)brace
id|check_connectivity
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
