macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pack.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;fsck.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;dir.h&quot;
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
DECL|variable|include_reflogs
r_static
r_int
id|include_reflogs
op_assign
l_int|1
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
DECL|variable|head_points_at
r_static
r_const
r_char
op_star
id|head_points_at
suffix:semicolon
DECL|variable|errors_found
r_static
r_int
id|errors_found
suffix:semicolon
DECL|variable|write_lost_and_found
r_static
r_int
id|write_lost_and_found
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|macro|ERROR_OBJECT
mdefine_line|#define ERROR_OBJECT 01
DECL|macro|ERROR_REACHABLE
mdefine_line|#define ERROR_REACHABLE 02
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
id|errors_found
op_or_assign
id|ERROR_OBJECT
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
DECL|function|fsck_error_func
r_static
r_int
id|fsck_error_func
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
(paren
id|type
op_eq
id|FSCK_WARN
)paren
ques
c_cond
l_string|&quot;warning&quot;
suffix:colon
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
(paren
id|type
op_eq
id|FSCK_WARN
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|variable|pending
r_static
r_struct
id|object_array
id|pending
suffix:semicolon
DECL|function|mark_object
r_static
r_int
id|mark_object
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
r_void
op_star
id|data
)paren
(brace
r_struct
id|object
op_star
id|parent
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;broken link from %7s %s&bslash;n&quot;
comma
r_typename
(paren
id|parent-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|parent-&gt;sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;broken link from %7s %s&bslash;n&quot;
comma
(paren
id|type
op_eq
id|OBJ_ANY
ques
c_cond
l_string|&quot;unknown&quot;
suffix:colon
r_typename
(paren
id|type
)paren
)paren
comma
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
id|errors_found
op_or_assign
id|ERROR_REACHABLE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_ne
id|OBJ_ANY
op_logical_and
id|obj-&gt;type
op_ne
id|type
)paren
id|objerror
c_func
(paren
id|parent
comma
l_string|&quot;wrong object type in link&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|REACHABLE
)paren
r_return
l_int|0
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|REACHABLE
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
id|parent
op_logical_and
op_logical_neg
id|has_sha1_file
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;broken link from %7s %s&bslash;n&quot;
comma
r_typename
(paren
id|parent-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|parent-&gt;sha1
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
id|errors_found
op_or_assign
id|ERROR_REACHABLE
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|add_object_array
c_func
(paren
id|obj
comma
(paren
r_void
op_star
)paren
id|parent
comma
op_amp
id|pending
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mark_object_reachable
r_static
r_void
id|mark_object_reachable
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
id|mark_object
c_func
(paren
id|obj
comma
id|OBJ_ANY
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|traverse_one_object
r_static
r_int
id|traverse_one_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_struct
id|object
op_star
id|parent
)paren
(brace
r_int
id|result
suffix:semicolon
r_struct
id|tree
op_star
id|tree
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
(brace
id|obj-&gt;parsed
op_assign
l_int|0
suffix:semicolon
id|tree
op_assign
(paren
r_struct
id|tree
op_star
)paren
id|obj
suffix:semicolon
r_if
c_cond
(paren
id|parse_tree
c_func
(paren
id|tree
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* error already displayed */
)brace
id|result
op_assign
id|fsck_walk
c_func
(paren
id|obj
comma
id|mark_object
comma
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tree
)paren
(brace
id|free
c_func
(paren
id|tree-&gt;buffer
)paren
suffix:semicolon
id|tree-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|traverse_reachable
r_static
r_int
id|traverse_reachable
c_func
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|pending.nr
)paren
(brace
r_struct
id|object_array_entry
op_star
id|entry
suffix:semicolon
r_struct
id|object
op_star
id|obj
comma
op_star
id|parent
suffix:semicolon
id|entry
op_assign
id|pending.objects
op_plus
op_decrement
id|pending.nr
suffix:semicolon
id|obj
op_assign
id|entry-&gt;item
suffix:semicolon
id|parent
op_assign
(paren
r_struct
id|object
op_star
)paren
id|entry-&gt;name
suffix:semicolon
id|result
op_or_assign
id|traverse_one_object
c_func
(paren
id|obj
comma
id|parent
)paren
suffix:semicolon
)brace
r_return
op_logical_neg
op_logical_neg
id|result
suffix:semicolon
)brace
DECL|function|mark_used
r_static
r_int
id|mark_used
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
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check a single reachable object&n; */
DECL|function|check_reachable_object
r_static
r_void
id|check_reachable_object
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
multiline_comment|/*&n;&t; * We obviously want the object to be parsed,&n;&t; * except if it was in a pack-file and we didn&squot;t&n;&t; * do a full fsck&n;&t; */
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
id|has_sha1_pack
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* it is in pack - forget about it */
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
id|errors_found
op_or_assign
id|ERROR_REACHABLE
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check a single unreachable object&n; */
DECL|function|check_unreachable_object
r_static
r_void
id|check_unreachable_object
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
multiline_comment|/*&n;&t; * Missing unreachable object? Ignore it. It&squot;s not like&n;&t; * we miss it (since it can&squot;t be reached), nor do we want&n;&t; * to complain about it being unreachable (since it does&n;&t; * not exist).&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;parsed
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Unreachable object that exists? Show it if asked to,&n;&t; * since this is something that is prunable.&n;&t; */
r_if
c_cond
(paren
id|show_unreachable
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
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * &quot;!used&quot; means that nothing at all points to it, including&n;&t; * other unreachable objects. In other words, it&squot;s the &quot;tip&quot;&n;&t; * of some set of unreachable objects, usually a commit that&n;&t; * got dropped.&n;&t; *&n;&t; * Such starting points are more interesting than some random&n;&t; * set of unreachable objects, so we show them even if the user&n;&t; * hasn&squot;t asked for _all_ unreachable objects. If you have&n;&t; * deleted a branch by mistake, this is a prime candidate to&n;&t; * start looking at, for example.&n;&t; */
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
r_if
c_cond
(paren
id|write_lost_and_found
)paren
(brace
r_char
op_star
id|filename
op_assign
id|git_path
c_func
(paren
l_string|&quot;lost-found/%s/%s&quot;
comma
id|obj-&gt;type
op_eq
id|OBJ_COMMIT
ques
c_cond
l_string|&quot;commit&quot;
suffix:colon
l_string|&quot;other&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories
c_func
(paren
id|filename
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Could not create lost-found&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|f
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;w&quot;
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Could not open %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_BLOB
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|obj-&gt;sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|buf
comma
id|size
comma
l_int|1
comma
id|f
)paren
op_ne
l_int|1
)paren
id|die_errno
c_func
(paren
l_string|&quot;Could not write &squot;%s&squot;&quot;
comma
id|filename
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_else
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|f
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;Could not finish &squot;%s&squot;&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Otherwise? It&squot;s there, it&squot;s unreachable, and some other unreachable&n;&t; * object points to it. Ignore it - it&squot;s not interesting, and we showed&n;&t; * all the interesting cases above.&n;&t; */
)brace
DECL|function|check_object
r_static
r_void
id|check_object
c_func
(paren
r_struct
id|object
op_star
id|obj
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;flags
op_amp
id|REACHABLE
)paren
id|check_reachable_object
c_func
(paren
id|obj
)paren
suffix:semicolon
r_else
id|check_unreachable_object
c_func
(paren
id|obj
)paren
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
multiline_comment|/* Traverse the pending reachable objects */
id|traverse_reachable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Look up all the requirements, warn about missing objects.. */
id|max
op_assign
id|get_max_object_index
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking connectivity (%d objects)&bslash;n&quot;
comma
id|max
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
id|obj
)paren
id|check_object
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
)brace
DECL|function|fsck_sha1
r_static
r_int
id|fsck_sha1
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
(brace
id|errors_found
op_or_assign
id|ERROR_OBJECT
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;%s: object corrupt or missing&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
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
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking %s %s&bslash;n&quot;
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
r_if
c_cond
(paren
id|fsck_walk
c_func
(paren
id|obj
comma
id|mark_used
comma
l_int|0
)paren
)paren
id|objerror
c_func
(paren
id|obj
comma
l_string|&quot;broken links&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fsck_object
c_func
(paren
id|obj
comma
id|check_strict
comma
id|fsck_error_func
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
(brace
r_struct
id|tree
op_star
id|item
op_assign
(paren
r_struct
id|tree
op_star
)paren
id|obj
suffix:semicolon
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
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_COMMIT
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|obj
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
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
r_struct
id|tag
op_star
id|tag
op_assign
(paren
r_struct
id|tag
op_star
)paren
id|obj
suffix:semicolon
r_if
c_cond
(paren
id|show_tags
op_logical_and
id|tag-&gt;tagged
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;tagged %s %s&quot;
comma
r_typename
(paren
id|tag-&gt;tagged-&gt;type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;tagged-&gt;sha1
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
)brace
)brace
r_return
l_int|0
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
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking directory %s&bslash;n&quot;
comma
id|path
)paren
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
r_if
c_cond
(paren
id|is_dot_or_dotdot
c_func
(paren
id|de-&gt;d_name
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
op_eq
l_int|38
)paren
(brace
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
l_int|39
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
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|de-&gt;d_name
comma
l_string|&quot;tmp_obj_&quot;
)paren
)paren
r_continue
suffix:semicolon
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
DECL|function|fsck_handle_reflog_ent
r_static
r_int
id|fsck_handle_reflog_ent
c_func
(paren
r_int
r_char
op_star
id|osha1
comma
r_int
r_char
op_star
id|nsha1
comma
r_const
r_char
op_star
id|email
comma
r_int
r_int
id|timestamp
comma
r_int
id|tz
comma
r_const
r_char
op_star
id|message
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
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking reflog %s-&gt;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|osha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|nsha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|osha1
)paren
)paren
(brace
id|obj
op_assign
id|lookup_object
c_func
(paren
id|osha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj
)paren
(brace
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
id|mark_object_reachable
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
)brace
id|obj
op_assign
id|lookup_object
c_func
(paren
id|nsha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj
)paren
(brace
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
id|mark_object_reachable
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fsck_handle_reflog
r_static
r_int
id|fsck_handle_reflog
c_func
(paren
r_const
r_char
op_star
id|logname
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
id|for_each_reflog_ent
c_func
(paren
id|logname
comma
id|fsck_handle_reflog_ent
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|is_branch
r_static
r_int
id|is_branch
c_func
(paren
r_const
r_char
op_star
id|refname
)paren
(brace
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|refname
comma
l_string|&quot;HEAD&quot;
)paren
op_logical_or
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
)brace
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
r_int
id|flag
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
(brace
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
r_if
c_cond
(paren
id|obj-&gt;type
op_ne
id|OBJ_COMMIT
op_logical_and
id|is_branch
c_func
(paren
id|refname
)paren
)paren
id|error
c_func
(paren
l_string|&quot;%s: not a commit&quot;
comma
id|refname
)paren
suffix:semicolon
id|default_refs
op_increment
suffix:semicolon
id|obj-&gt;used
op_assign
l_int|1
suffix:semicolon
id|mark_object_reachable
c_func
(paren
id|obj
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
r_if
c_cond
(paren
id|head_points_at
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|head_sha1
)paren
)paren
id|fsck_handle_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|fsck_handle_ref
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|include_reflogs
)paren
id|for_each_reflog
c_func
(paren
id|fsck_handle_reflog
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;notice: No default references&bslash;n&quot;
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
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking object directory&bslash;n&quot;
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
id|flag
suffix:semicolon
r_int
id|null_is_error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking HEAD link&bslash;n&quot;
)paren
suffix:semicolon
id|head_points_at
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
comma
l_int|0
comma
op_amp
id|flag
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
l_string|&quot;Invalid HEAD&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|head_points_at
comma
l_string|&quot;HEAD&quot;
)paren
)paren
multiline_comment|/* detached HEAD */
id|null_is_error
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|head_points_at
comma
l_string|&quot;refs/heads/&quot;
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
id|head_sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|null_is_error
)paren
r_return
id|error
c_func
(paren
l_string|&quot;HEAD: detached HEAD points at nothing&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;notice: HEAD points to an unborn branch (%s)&bslash;n&quot;
comma
id|head_points_at
op_plus
l_int|11
)paren
suffix:semicolon
)brace
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
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Checking cache tree&bslash;n&quot;
)paren
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
id|mark_object_reachable
c_func
(paren
id|obj
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
DECL|variable|fsck_usage
r_static
r_char
r_const
op_star
r_const
id|fsck_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git fsck [options] [&lt;object&gt;...]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|fsck_opts
r_static
r_struct
id|option
id|fsck_opts
(braket
)braket
op_assign
(brace
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;unreachable&quot;
comma
op_amp
id|show_unreachable
comma
l_string|&quot;show unreachable objects&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;tags&quot;
comma
op_amp
id|show_tags
comma
l_string|&quot;report tags&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;root&quot;
comma
op_amp
id|show_root
comma
l_string|&quot;report root nodes&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;cache&quot;
comma
op_amp
id|keep_cache_objects
comma
l_string|&quot;make index objects head nodes&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;reflogs&quot;
comma
op_amp
id|include_reflogs
comma
l_string|&quot;make reflogs head nodes (default)&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;full&quot;
comma
op_amp
id|check_full
comma
l_string|&quot;also consider alternate objects&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;strict&quot;
comma
op_amp
id|check_strict
comma
l_string|&quot;enable more strict checking&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;lost-found&quot;
comma
op_amp
id|write_lost_and_found
comma
l_string|&quot;write dangling objects in .git/lost-found&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
DECL|function|cmd_fsck
r_int
id|cmd_fsck
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
id|i
comma
id|heads
suffix:semicolon
r_struct
id|alternate_object_database
op_star
id|alt
suffix:semicolon
id|errors_found
op_assign
l_int|0
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
id|fsck_opts
comma
id|fsck_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_lost_and_found
)paren
(brace
id|check_full
op_assign
l_int|1
suffix:semicolon
id|include_reflogs
op_assign
l_int|0
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
r_if
c_cond
(paren
id|check_full
)paren
(brace
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
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
r_uint32
id|j
comma
id|num
suffix:semicolon
r_if
c_cond
(paren
id|open_pack_index
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
id|num
op_assign
id|p-&gt;num_objects
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
id|num
suffix:semicolon
id|j
op_increment
)paren
id|fsck_sha1
c_func
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|j
)paren
)paren
suffix:semicolon
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
l_int|0
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
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
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
id|sha1
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
id|mark_object_reachable
c_func
(paren
id|obj
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
r_int
r_int
id|mode
suffix:semicolon
r_struct
id|blob
op_star
id|blob
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
id|mode
op_assign
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|ce_mode
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|mode
)paren
)paren
r_continue
suffix:semicolon
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
id|mark_object_reachable
c_func
(paren
id|obj
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
id|errors_found
suffix:semicolon
)brace
eof
