multiline_comment|/*&n; * Builtin &quot;git diff&quot;&n; *&n; * Copyright (c) 2006 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
DECL|struct|blobinfo
r_struct
id|blobinfo
(brace
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|builtin_diff_usage
r_static
r_const
r_char
id|builtin_diff_usage
(braket
)braket
op_assign
l_string|&quot;git-diff &lt;options&gt; &lt;rev&gt;{0,2} -- &lt;path&gt;*&quot;
suffix:semicolon
DECL|function|stuff_change
r_static
r_void
id|stuff_change
c_func
(paren
r_struct
id|diff_options
op_star
id|opt
comma
r_int
id|old_mode
comma
r_int
id|new_mode
comma
r_const
r_int
r_char
op_star
id|old_sha1
comma
r_const
r_int
r_char
op_star
id|new_sha1
comma
r_const
r_char
op_star
id|old_name
comma
r_const
r_char
op_star
id|new_name
)paren
(brace
r_struct
id|diff_filespec
op_star
id|one
comma
op_star
id|two
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|old_sha1
)paren
op_logical_and
op_logical_neg
id|is_null_sha1
c_func
(paren
id|new_sha1
)paren
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|old_sha1
comma
id|new_sha1
)paren
op_logical_and
(paren
id|old_mode
op_eq
id|new_mode
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|opt
comma
id|REVERSE_DIFF
)paren
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_const
r_int
r_char
op_star
id|tmp_u
suffix:semicolon
r_const
r_char
op_star
id|tmp_c
suffix:semicolon
id|tmp
op_assign
id|old_mode
suffix:semicolon
id|old_mode
op_assign
id|new_mode
suffix:semicolon
id|new_mode
op_assign
id|tmp
suffix:semicolon
id|tmp_u
op_assign
id|old_sha1
suffix:semicolon
id|old_sha1
op_assign
id|new_sha1
suffix:semicolon
id|new_sha1
op_assign
id|tmp_u
suffix:semicolon
id|tmp_c
op_assign
id|old_name
suffix:semicolon
id|old_name
op_assign
id|new_name
suffix:semicolon
id|new_name
op_assign
id|tmp_c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opt-&gt;prefix
op_logical_and
(paren
id|strncmp
c_func
(paren
id|old_name
comma
id|opt-&gt;prefix
comma
id|opt-&gt;prefix_length
)paren
op_logical_or
id|strncmp
c_func
(paren
id|new_name
comma
id|opt-&gt;prefix
comma
id|opt-&gt;prefix_length
)paren
)paren
)paren
r_return
suffix:semicolon
id|one
op_assign
id|alloc_filespec
c_func
(paren
id|old_name
)paren
suffix:semicolon
id|two
op_assign
id|alloc_filespec
c_func
(paren
id|new_name
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|one
comma
id|old_sha1
comma
id|old_mode
)paren
suffix:semicolon
id|fill_filespec
c_func
(paren
id|two
comma
id|new_sha1
comma
id|new_mode
)paren
suffix:semicolon
id|diff_queue
c_func
(paren
op_amp
id|diff_queued_diff
comma
id|one
comma
id|two
)paren
suffix:semicolon
)brace
DECL|function|builtin_diff_b_f
r_static
r_int
id|builtin_diff_b_f
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_struct
id|blobinfo
op_star
id|blob
comma
r_const
r_char
op_star
id|path
)paren
(brace
multiline_comment|/* Blob vs file in the working tree*/
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
op_logical_or
id|S_ISLNK
c_func
(paren
id|st.st_mode
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: not a regular file or symlink&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blob
(braket
l_int|0
)braket
dot
id|mode
op_eq
id|S_IFINVALID
)paren
id|blob
(braket
l_int|0
)braket
dot
id|mode
op_assign
id|canon_mode
c_func
(paren
id|st.st_mode
)paren
suffix:semicolon
id|stuff_change
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|blob
(braket
l_int|0
)braket
dot
id|mode
comma
id|canon_mode
c_func
(paren
id|st.st_mode
)paren
comma
id|blob
(braket
l_int|0
)braket
dot
id|sha1
comma
id|null_sha1
comma
id|path
comma
id|path
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|builtin_diff_blobs
r_static
r_int
id|builtin_diff_blobs
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_struct
id|blobinfo
op_star
id|blob
)paren
(brace
r_int
id|mode
op_assign
id|canon_mode
c_func
(paren
id|S_IFREG
op_or
l_int|0644
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blob
(braket
l_int|0
)braket
dot
id|mode
op_eq
id|S_IFINVALID
)paren
id|blob
(braket
l_int|0
)braket
dot
id|mode
op_assign
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|blob
(braket
l_int|1
)braket
dot
id|mode
op_eq
id|S_IFINVALID
)paren
id|blob
(braket
l_int|1
)braket
dot
id|mode
op_assign
id|mode
suffix:semicolon
id|stuff_change
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
id|blob
(braket
l_int|0
)braket
dot
id|mode
comma
id|blob
(braket
l_int|1
)braket
dot
id|mode
comma
id|blob
(braket
l_int|0
)braket
dot
id|sha1
comma
id|blob
(braket
l_int|1
)braket
dot
id|sha1
comma
id|blob
(braket
l_int|0
)braket
dot
id|name
comma
id|blob
(braket
l_int|1
)braket
dot
id|name
)paren
suffix:semicolon
id|diffcore_std
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|builtin_diff_index
r_static
r_int
id|builtin_diff_index
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|cached
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
l_int|1
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
l_string|&quot;--cached&quot;
)paren
)paren
id|cached
op_assign
l_int|1
suffix:semicolon
r_else
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure there is one revision (i.e. pending object),&n;&t; * and there is no revision filtering parameters.&n;&t; */
r_if
c_cond
(paren
id|revs-&gt;pending.nr
op_ne
l_int|1
op_logical_or
id|revs-&gt;max_count
op_ne
l_int|1
op_logical_or
id|revs-&gt;min_age
op_ne
l_int|1
op_logical_or
id|revs-&gt;max_age
op_ne
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|run_diff_index
c_func
(paren
id|revs
comma
id|cached
)paren
suffix:semicolon
)brace
DECL|function|builtin_diff_tree
r_static
r_int
id|builtin_diff_tree
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_struct
id|object_array_entry
op_star
id|ent
)paren
(brace
r_const
r_int
r_char
op_star
(paren
id|sha1
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_int
id|swap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
multiline_comment|/* We saw two trees, ent[0] and ent[1].&n;&t; * if ent[1] is uninteresting, they are swapped&n;&t; */
r_if
c_cond
(paren
id|ent
(braket
l_int|1
)braket
dot
id|item-&gt;flags
op_amp
id|UNINTERESTING
)paren
id|swap
op_assign
l_int|1
suffix:semicolon
id|sha1
(braket
id|swap
)braket
op_assign
id|ent
(braket
l_int|0
)braket
dot
id|item-&gt;sha1
suffix:semicolon
id|sha1
(braket
l_int|1
op_minus
id|swap
)braket
op_assign
id|ent
(braket
l_int|1
)braket
dot
id|item-&gt;sha1
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|sha1
(braket
l_int|0
)braket
comma
id|sha1
(braket
l_int|1
)braket
comma
l_string|&quot;&quot;
comma
op_amp
id|revs-&gt;diffopt
)paren
suffix:semicolon
id|log_tree_diff_flush
c_func
(paren
id|revs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|builtin_diff_combined
r_static
r_int
id|builtin_diff_combined
c_func
(paren
r_struct
id|rev_info
op_star
id|revs
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_struct
id|object_array_entry
op_star
id|ent
comma
r_int
id|ents
)paren
(brace
r_const
r_int
r_char
(paren
op_star
id|parent
)paren
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|revs-&gt;dense_combined_merges
op_logical_and
op_logical_neg
id|revs-&gt;combine_merges
)paren
id|revs-&gt;dense_combined_merges
op_assign
id|revs-&gt;combine_merges
op_assign
l_int|1
suffix:semicolon
id|parent
op_assign
id|xmalloc
c_func
(paren
id|ents
op_star
r_sizeof
(paren
op_star
id|parent
)paren
)paren
suffix:semicolon
multiline_comment|/* Again, the revs are all reverse */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ents
suffix:semicolon
id|i
op_increment
)paren
id|hashcpy
c_func
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|parent
op_plus
id|i
)paren
comma
id|ent
(braket
id|ents
l_int|1
id|i
)braket
dot
id|item-&gt;sha1
)paren
suffix:semicolon
id|diff_tree_combined
c_func
(paren
id|parent
(braket
l_int|0
)braket
comma
id|parent
op_plus
l_int|1
comma
id|ents
l_int|1
comma
id|revs-&gt;dense_combined_merges
comma
id|revs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|refresh_index_quietly
r_static
r_void
id|refresh_index_quietly
c_func
(paren
r_void
)paren
(brace
r_struct
id|lock_file
op_star
id|lock_file
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|hold_locked_index
c_func
(paren
id|lock_file
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
suffix:semicolon
id|discard_cache
c_func
(paren
)paren
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
id|refresh_cache
c_func
(paren
id|REFRESH_QUIET
op_or
id|REFRESH_UNMERGED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active_cache_changed
op_logical_and
op_logical_neg
id|write_cache
c_func
(paren
id|fd
comma
id|active_cache
comma
id|active_nr
)paren
)paren
id|commit_locked_index
c_func
(paren
id|lock_file
)paren
suffix:semicolon
id|rollback_lock_file
c_func
(paren
id|lock_file
)paren
suffix:semicolon
)brace
DECL|function|cmd_diff
r_int
id|cmd_diff
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
suffix:semicolon
r_struct
id|rev_info
id|rev
suffix:semicolon
r_struct
id|object_array_entry
id|ent
(braket
l_int|100
)braket
suffix:semicolon
r_int
id|ents
op_assign
l_int|0
comma
id|blobs
op_assign
l_int|0
comma
id|paths
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|blobinfo
id|blob
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|nongit
op_assign
l_int|0
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We could get N tree-ish in the rev.pending_objects list.&n;&t; * Also there could be M blobs there, and P pathspecs.&n;&t; *&n;&t; * N=0, M=0:&n;&t; *&t;cache vs files (diff-files)&n;&t; * N=0, M=2:&n;&t; *      compare two random blobs.  P must be zero.&n;&t; * N=0, M=1, P=1:&n;&t; *&t;compare a blob with a working tree file.&n;&t; *&n;&t; * N=1, M=0:&n;&t; *      tree vs cache (diff-index --cached)&n;&t; *&n;&t; * N=2, M=0:&n;&t; *      tree vs tree (diff-tree)&n;&t; *&n;&t; * Other cases are errors.&n;&t; */
id|prefix
op_assign
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_diff_ui_config
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
id|prefix
)paren
suffix:semicolon
id|rev.diffopt.skip_stat_unmatch
op_assign
op_logical_neg
op_logical_neg
id|diff_auto_refresh_index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|setup_diff_no_index
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|nongit
comma
id|prefix
)paren
)paren
id|argc
op_assign
l_int|0
suffix:semicolon
r_else
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev.diffopt.output_format
)paren
(brace
id|rev.diffopt.output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
r_if
c_cond
(paren
id|diff_setup_done
c_func
(paren
op_amp
id|rev.diffopt
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;diff_setup_done failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rev.diffopt.prefix
op_logical_and
id|nongit
)paren
(brace
id|rev.diffopt.prefix
op_assign
l_int|NULL
suffix:semicolon
id|rev.diffopt.prefix_length
op_assign
l_int|0
suffix:semicolon
)brace
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|ALLOW_EXTERNAL
)paren
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|RECURSIVE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the user asked for our exit code then don&squot;t start a&n;&t; * pager or we would end up reporting its exit code instead.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|DIFF_OPT_TST
c_func
(paren
op_amp
id|rev.diffopt
comma
id|EXIT_WITH_STATUS
)paren
)paren
id|setup_pager
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do we have --cached and not have a pending object, then&n;&t; * default to HEAD by hand.  Eek.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rev.pending.nr
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
l_string|&quot;--&quot;
)paren
)paren
r_break
suffix:semicolon
r_else
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
id|add_head_to_pending
c_func
(paren
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev.pending.nr
)paren
id|die
c_func
(paren
l_string|&quot;No HEAD commit to compare with (yet)&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
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
id|rev.pending.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object_array_entry
op_star
id|list
op_assign
id|rev.pending.objects
op_plus
id|i
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
id|list-&gt;item
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|list-&gt;name
suffix:semicolon
r_int
id|flags
op_assign
(paren
id|obj-&gt;flags
op_amp
id|UNINTERESTING
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj-&gt;parsed
)paren
id|obj
op_assign
id|parse_object
c_func
(paren
id|obj-&gt;sha1
)paren
suffix:semicolon
id|obj
op_assign
id|deref_tag
c_func
(paren
id|obj
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
)paren
id|die
c_func
(paren
l_string|&quot;invalid object &squot;%s&squot; given.&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_COMMIT
)paren
id|obj
op_assign
op_amp
(paren
(paren
r_struct
id|commit
op_star
)paren
id|obj
)paren
op_member_access_from_pointer
id|tree-&gt;object
suffix:semicolon
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_TREE
)paren
(brace
r_if
c_cond
(paren
id|ARRAY_SIZE
c_func
(paren
id|ent
)paren
op_le
id|ents
)paren
id|die
c_func
(paren
l_string|&quot;more than %d trees given: &squot;%s&squot;&quot;
comma
(paren
r_int
)paren
id|ARRAY_SIZE
c_func
(paren
id|ent
)paren
comma
id|name
)paren
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|flags
suffix:semicolon
id|ent
(braket
id|ents
)braket
dot
id|item
op_assign
id|obj
suffix:semicolon
id|ent
(braket
id|ents
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|ents
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj-&gt;type
op_eq
id|OBJ_BLOB
)paren
(brace
r_if
c_cond
(paren
l_int|2
op_le
id|blobs
)paren
id|die
c_func
(paren
l_string|&quot;more than two blobs given: &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|blob
(braket
id|blobs
)braket
dot
id|sha1
comma
id|obj-&gt;sha1
)paren
suffix:semicolon
id|blob
(braket
id|blobs
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|blob
(braket
id|blobs
)braket
dot
id|mode
op_assign
id|list-&gt;mode
suffix:semicolon
id|blobs
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;unhandled object &squot;%s&squot; given.&quot;
comma
id|name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rev.prune_data
)paren
(brace
r_const
r_char
op_star
op_star
id|pathspec
op_assign
id|rev.prune_data
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pathspec
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|path
op_assign
op_star
id|pathspec
suffix:semicolon
id|paths
op_increment
suffix:semicolon
id|pathspec
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Now, do the arguments look reasonable?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ents
)paren
(brace
r_switch
c_cond
(paren
id|blobs
)paren
(brace
r_case
l_int|0
suffix:colon
id|result
op_assign
id|run_diff_files_cmd
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|paths
op_ne
l_int|1
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
id|result
op_assign
id|builtin_diff_b_f
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|blob
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|paths
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
id|result
op_assign
id|builtin_diff_blobs
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|blob
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|blobs
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ents
op_eq
l_int|1
)paren
id|result
op_assign
id|builtin_diff_index
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ents
op_eq
l_int|2
)paren
id|result
op_assign
id|builtin_diff_tree
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|ent
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|ents
op_eq
l_int|3
)paren
op_logical_and
(paren
id|ent
(braket
l_int|0
)braket
dot
id|item-&gt;flags
op_amp
id|UNINTERESTING
)paren
)paren
(brace
multiline_comment|/* diff A...B where there is one sane merge base between&n;&t;&t; * A and B.  We have ent[0] == merge-base, ent[1] == A,&n;&t;&t; * and ent[2] == B.  Show diff between the base and B.&n;&t;&t; */
id|ent
(braket
l_int|1
)braket
op_assign
id|ent
(braket
l_int|2
)braket
suffix:semicolon
id|result
op_assign
id|builtin_diff_tree
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|ent
)paren
suffix:semicolon
)brace
r_else
id|result
op_assign
id|builtin_diff_combined
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|ent
comma
id|ents
)paren
suffix:semicolon
id|result
op_assign
id|diff_result_code
c_func
(paren
op_amp
id|rev.diffopt
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|rev.diffopt.skip_stat_unmatch
)paren
id|refresh_index_quietly
c_func
(paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
