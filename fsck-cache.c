macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tag.h&quot;
DECL|macro|REACHABLE
mdefine_line|#define REACHABLE 0x0001
DECL|variable|show_root
r_static
r_int
id|show_root
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_tags
r_static
r_int
id|show_tags
op_assign
l_int|0
suffix:semicolon
DECL|variable|show_unreachable
r_static
r_int
id|show_unreachable
op_assign
l_int|0
suffix:semicolon
DECL|variable|standalone
r_static
r_int
id|standalone
op_assign
l_int|0
suffix:semicolon
DECL|variable|check_full
r_static
r_int
id|check_full
op_assign
l_int|0
suffix:semicolon
DECL|variable|keep_cache_objects
r_static
r_int
id|keep_cache_objects
op_assign
l_int|0
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
suffix:semicolon
multiline_comment|/* Look up all the requirements, warn about missing objects.. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_objs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|objs
(braket
id|i
)braket
suffix:semicolon
r_struct
id|object_list
op_star
id|refs
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
op_logical_neg
id|standalone
op_logical_and
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
id|obj-&gt;type
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
r_for
c_loop
(paren
id|refs
op_assign
id|obj-&gt;refs
suffix:semicolon
id|refs
suffix:semicolon
id|refs
op_assign
id|refs-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|refs-&gt;item-&gt;parsed
op_logical_or
(paren
op_logical_neg
id|standalone
op_logical_and
id|has_sha1_file
c_func
(paren
id|refs-&gt;item-&gt;sha1
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
id|obj-&gt;type
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
id|refs-&gt;item-&gt;type
comma
id|sha1_to_hex
c_func
(paren
id|refs-&gt;item-&gt;sha1
)paren
)paren
suffix:semicolon
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
id|obj-&gt;type
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
id|obj-&gt;type
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
r_struct
id|tree_entry_list
op_star
id|a
comma
r_struct
id|tree_entry_list
op_star
id|b
)paren
(brace
r_int
id|len1
op_assign
id|strlen
c_func
(paren
id|a-&gt;name
)paren
suffix:semicolon
r_int
id|len2
op_assign
id|strlen
c_func
(paren
id|b-&gt;name
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
id|a-&gt;name
comma
id|b-&gt;name
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
id|a-&gt;name
(braket
id|len
)braket
suffix:semicolon
id|c2
op_assign
id|b-&gt;name
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
id|a-&gt;directory
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
id|b-&gt;directory
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
id|has_full_path
op_assign
l_int|0
suffix:semicolon
r_struct
id|tree_entry_list
op_star
id|entry
comma
op_star
id|last
suffix:semicolon
id|last
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|item-&gt;entries
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|entry-&gt;name
comma
l_char|&squot;/&squot;
)paren
)paren
id|has_full_path
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|entry-&gt;mode
)paren
(brace
multiline_comment|/*&n;&t;&t; * Standard modes.. &n;&t;&t; */
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
r_break
suffix:semicolon
r_default
suffix:colon
id|printf
c_func
(paren
l_string|&quot;tree %s has entry %o %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
comma
id|entry-&gt;mode
comma
id|entry-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last
)paren
(brace
r_switch
c_cond
(paren
id|verify_ordered
c_func
(paren
id|last
comma
id|entry
)paren
)paren
(brace
r_case
id|TREE_UNORDERED
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;tree %s not ordered&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
id|TREE_HAS_DUPS
suffix:colon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;tree %s has duplicate entries for &squot;%s&squot;&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
comma
id|entry-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|last
op_assign
id|entry
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_full_path
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: git-fsck-cache: tree %s &quot;
l_string|&quot;has full pathnames in it&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
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
)paren
(brace
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
l_int|1
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
id|printf
c_func
(paren
l_string|&quot;bad object in tag %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
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
id|tagged-&gt;type
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
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|blob_type
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|tree_type
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
id|commit_type
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
id|tag_type
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
r_return
l_int|1
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
r_if
c_cond
(paren
id|fsck_sha1
c_func
(paren
id|sha1
)paren
OL
l_int|0
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;bad sha1 entry &squot;%s&squot;&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
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
id|memcpy
c_func
(paren
id|entry-&gt;sha1
comma
id|sha1
comma
l_int|20
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
r_return
id|error
c_func
(paren
l_string|&quot;missing sha1 directory &squot;%s&squot;&quot;
comma
id|path
)paren
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
id|de-&gt;d_ino
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_sha1_reference
r_static
r_int
id|read_sha1_reference
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_char
id|hexname
(braket
l_int|60
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
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_RDONLY
)paren
comma
id|len
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|read
c_func
(paren
id|fd
comma
id|hexname
comma
r_sizeof
(paren
id|hexname
)paren
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
id|len
OL
l_int|40
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
id|hexname
comma
id|sha1
)paren
OL
l_int|0
)paren
r_return
l_int|1
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
op_logical_neg
id|standalone
op_logical_and
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* it is in pack */
r_return
id|error
c_func
(paren
l_string|&quot;%s: invalid sha1 pointer %.40s&quot;
comma
id|path
comma
id|hexname
)paren
suffix:semicolon
)brace
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
DECL|function|find_file_objects
r_static
r_int
id|find_file_objects
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
id|name
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
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_char
op_star
id|path
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
id|namelen
op_plus
l_int|2
)paren
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|path
(braket
id|baselen
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|path
op_plus
id|baselen
op_plus
l_int|1
comma
id|name
comma
id|namelen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Recurse into directories&n;&t; */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
id|dir
)paren
(brace
r_struct
id|dirent
op_star
id|de
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
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_continue
suffix:semicolon
id|count
op_add_assign
id|find_file_objects
c_func
(paren
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
r_return
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
r_return
id|read_sha1_reference
c_func
(paren
id|path
)paren
op_eq
l_int|0
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
r_char
op_star
id|git_dir
op_assign
id|gitenv
c_func
(paren
id|GIT_DIR_ENVIRONMENT
)paren
ques
c_cond
suffix:colon
id|DEFAULT_GIT_DIR_ENVIRONMENT
suffix:semicolon
r_int
id|count
op_assign
id|find_file_objects
c_func
(paren
id|git_dir
comma
l_string|&quot;refs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
id|die
c_func
(paren
l_string|&quot;No default references&quot;
)paren
suffix:semicolon
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
l_string|&quot;--standalone&quot;
)paren
)paren
(brace
id|standalone
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
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
l_string|&quot;git-fsck-cache [--tags] [[--unreachable] [--cache] [--standalone | --full] &lt;head-sha1&gt;*]&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|standalone
op_logical_and
id|check_full
)paren
id|die
c_func
(paren
l_string|&quot;Only one of --standalone or --full can be used.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|standalone
)paren
id|unsetenv
c_func
(paren
l_string|&quot;GIT_ALTERNATE_OBJECT_DIRECTORIES&quot;
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
r_int
id|j
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
id|j
op_assign
l_int|0
suffix:semicolon
id|alt_odb
(braket
id|j
)braket
dot
id|base
suffix:semicolon
id|j
op_increment
)paren
(brace
id|alt_odb
(braket
id|j
)braket
dot
id|name
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* was slash */
id|fsck_object_dir
c_func
(paren
id|alt_odb
(braket
id|j
)braket
dot
id|base
)paren
suffix:semicolon
id|alt_odb
(braket
id|j
)braket
dot
id|name
(braket
l_int|1
)braket
op_assign
l_char|&squot;/&squot;
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
r_if
c_cond
(paren
id|fsck_sha1
c_func
(paren
id|sha1
)paren
OL
l_int|0
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;bad sha1 entry &squot;%s&squot;&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
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
l_string|&quot;expected sha1, got %s&quot;
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
