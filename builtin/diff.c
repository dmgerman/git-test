multiline_comment|/*&n; * Builtin &quot;git diff&quot;&n; *&n; * Copyright (c) 2006 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;submodule.h&quot;
macro_line|#include &quot;sha1-array.h&quot;
DECL|macro|DIFF_NO_INDEX_EXPLICIT
mdefine_line|#define DIFF_NO_INDEX_EXPLICIT 1
DECL|macro|DIFF_NO_INDEX_IMPLICIT
mdefine_line|#define DIFF_NO_INDEX_IMPLICIT 2
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
l_string|&quot;git diff [&lt;options&gt;] [&lt;commit&gt; [&lt;commit&gt;]] [--] [&lt;path&gt;...]&quot;
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
r_int
id|old_sha1_valid
comma
r_int
id|new_sha1_valid
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
id|old_sha1_valid
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
id|new_sha1_valid
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
id|die_errno
c_func
(paren
id|_
c_func
(paren
l_string|&quot;failed to stat &squot;%s&squot;&quot;
)paren
comma
id|path
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
id|_
c_func
(paren
l_string|&quot;&squot;%s&squot;: not a regular file or symlink&quot;
)paren
comma
id|path
)paren
suffix:semicolon
id|diff_set_mnemonic_prefix
c_func
(paren
op_amp
id|revs-&gt;diffopt
comma
l_string|&quot;o/&quot;
comma
l_string|&quot;w/&quot;
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
l_int|1
comma
l_int|0
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
l_int|1
comma
l_int|1
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
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--staged&quot;
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
op_logical_neg
id|cached
)paren
(brace
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache_preload
c_func
(paren
op_amp
id|revs-&gt;diffopt.pathspec
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache_preload&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_else
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
id|ent0
comma
r_struct
id|object_array_entry
op_star
id|ent1
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
multiline_comment|/*&n;&t; * We saw two trees, ent0 and ent1.  If ent1 is uninteresting,&n;&t; * swap them.&n;&t; */
r_if
c_cond
(paren
id|ent1-&gt;item-&gt;flags
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
id|ent0-&gt;item-&gt;sha1
suffix:semicolon
id|sha1
(braket
l_int|1
id|swap
)braket
op_assign
id|ent1-&gt;item-&gt;sha1
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
r_struct
id|sha1_array
id|parents
op_assign
id|SHA1_ARRAY_INIT
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
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ents
suffix:semicolon
id|i
op_increment
)paren
id|sha1_array_append
c_func
(paren
op_amp
id|parents
comma
id|ent
(braket
id|i
)braket
dot
id|item-&gt;sha1
)paren
suffix:semicolon
id|diff_tree_combined
c_func
(paren
id|ent
(braket
l_int|0
)braket
dot
id|item-&gt;sha1
comma
op_amp
id|parents
comma
id|revs-&gt;dense_combined_merges
comma
id|revs
)paren
suffix:semicolon
id|sha1_array_clear
c_func
(paren
op_amp
id|parents
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
id|update_index_if_able
c_func
(paren
op_amp
id|the_index
comma
id|lock_file
)paren
suffix:semicolon
)brace
DECL|function|builtin_diff_files
r_static
r_int
id|builtin_diff_files
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
r_int
id|options
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|argc
op_logical_and
id|argv
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--base&quot;
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--ours&quot;
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--theirs&quot;
)paren
)paren
id|revs-&gt;max_count
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-q&quot;
)paren
)paren
id|options
op_or_assign
id|DIFF_SILENT_ON_REMOVED
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage
c_func
(paren
id|builtin_diff_usage
)paren
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;invalid option: %s&quot;
)paren
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * &quot;diff --base&quot; should not combine merges because it was not&n;&t; * asked to.  &quot;diff -c&quot; should not densify (if the user wants&n;&t; * dense one, --cc can be explicitly asked for, or just rely&n;&t; * on the default).&n;&t; */
r_if
c_cond
(paren
id|revs-&gt;max_count
op_eq
l_int|1
op_logical_and
op_logical_neg
id|revs-&gt;combine_merges
op_logical_and
(paren
id|revs-&gt;diffopt.output_format
op_amp
id|DIFF_FORMAT_PATCH
)paren
)paren
id|revs-&gt;combine_merges
op_assign
id|revs-&gt;dense_combined_merges
op_assign
l_int|1
suffix:semicolon
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_cache_preload
c_func
(paren
op_amp
id|revs-&gt;diffopt.pathspec
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache_preload&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|run_diff_files
c_func
(paren
id|revs
comma
id|options
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
id|object_array
id|ent
op_assign
id|OBJECT_ARRAY_INIT
suffix:semicolon
r_int
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
comma
id|no_index
op_assign
l_int|0
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We could get N tree-ish in the rev.pending_objects list.&n;&t; * Also there could be M blobs there, and P pathspecs.&n;&t; *&n;&t; * N=0, M=0:&n;&t; *&t;cache vs files (diff-files)&n;&t; * N=0, M=2:&n;&t; *      compare two random blobs.  P must be zero.&n;&t; * N=0, M=1, P=1:&n;&t; *&t;compare a blob with a working tree file.&n;&t; *&n;&t; * N=1, M=0:&n;&t; *      tree vs cache (diff-index --cached)&n;&t; *&n;&t; * N=2, M=0:&n;&t; *      tree vs tree (diff-tree)&n;&t; *&n;&t; * N=0, M=0, P=2:&n;&t; *      compare two filesystem entities (aka --no-index).&n;&t; *&n;&t; * Other cases are errors.&n;&t; */
multiline_comment|/* Were we asked to do --no-index explicitly? */
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--no-index&quot;
)paren
)paren
id|no_index
op_assign
id|DIFF_NO_INDEX_EXPLICIT
suffix:semicolon
r_if
c_cond
(paren
id|argv
(braket
id|i
)braket
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|no_index
)paren
id|prefix
op_assign
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Treat git diff with at least one path outside of the&n;&t; * repo the same as if the command would have been executed&n;&t; * outside of a git repository.  In this case it behaves&n;&t; * the same way as &quot;git diff --no-index &lt;a&gt; &lt;b&gt;&quot;, which acts&n;&t; * as a colourful &quot;diff&quot; replacement.&n;&t; */
r_if
c_cond
(paren
id|nongit
op_logical_or
(paren
(paren
id|argc
op_eq
id|i
op_plus
l_int|2
)paren
op_logical_and
(paren
op_logical_neg
id|path_inside_repo
c_func
(paren
id|prefix
comma
id|argv
(braket
id|i
)braket
)paren
op_logical_or
op_logical_neg
id|path_inside_repo
c_func
(paren
id|prefix
comma
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
)paren
)paren
id|no_index
op_assign
id|DIFF_NO_INDEX_IMPLICIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_index
)paren
id|gitmodules_config
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_diff_ui_config
comma
l_int|NULL
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
r_if
c_cond
(paren
id|no_index
op_logical_and
id|argc
op_ne
id|i
op_plus
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|no_index
op_eq
id|DIFF_NO_INDEX_IMPLICIT
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * There was no --no-index and there were not two&n;&t;&t;&t; * paths. It is possible that the user intended&n;&t;&t;&t; * to do an inside-repository operation.&n;&t;&t;&t; */
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Not a git repository&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;To compare two paths outside a working tree:&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Give the usage message for non-repository usage and exit. */
id|usagef
c_func
(paren
l_string|&quot;git diff %s &lt;path&gt; &lt;path&gt;&quot;
comma
id|no_index
op_eq
id|DIFF_NO_INDEX_EXPLICIT
ques
c_cond
l_string|&quot;--no-index&quot;
suffix:colon
l_string|&quot;[--no-index]&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no_index
)paren
multiline_comment|/* If this is a no-index diff, just run it and exit there. */
id|diff_no_index
c_func
(paren
op_amp
id|rev
comma
id|argc
comma
id|argv
comma
id|prefix
)paren
suffix:semicolon
multiline_comment|/* Otherwise, we are doing the usual &quot;git&quot; diff */
id|rev.diffopt.skip_stat_unmatch
op_assign
op_logical_neg
op_logical_neg
id|diff_auto_refresh_index
suffix:semicolon
multiline_comment|/* Scale to real terminal size and respect statGraphWidth config */
id|rev.diffopt.stat_width
op_assign
l_int|1
suffix:semicolon
id|rev.diffopt.stat_graph_width
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Default to let external and textconv be used */
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
id|ALLOW_TEXTCONV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nongit
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not a git repository&quot;
)paren
)paren
suffix:semicolon
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
id|diff_setup_done
c_func
(paren
op_amp
id|rev.diffopt
)paren
suffix:semicolon
)brace
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|rev.diffopt
comma
id|RECURSIVE
)paren
suffix:semicolon
id|setup_diff_pager
c_func
(paren
op_amp
id|rev.diffopt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do we have --cached and not have a pending object, then&n;&t; * default to HEAD by hand.  Eek.&n;&t; */
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
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--staged&quot;
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
(brace
r_struct
id|tree
op_star
id|tree
suffix:semicolon
id|tree
op_assign
id|lookup_tree
c_func
(paren
id|EMPTY_TREE_SHA1_BIN
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|rev
comma
op_amp
id|tree-&gt;object
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
)brace
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
id|entry
op_assign
op_amp
id|rev.pending.objects
(braket
id|i
)braket
suffix:semicolon
r_struct
id|object
op_star
id|obj
op_assign
id|entry-&gt;item
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|entry-&gt;name
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
id|_
c_func
(paren
l_string|&quot;invalid object &squot;%s&squot; given.&quot;
)paren
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
id|obj-&gt;flags
op_or_assign
id|flags
suffix:semicolon
id|add_object_array
c_func
(paren
id|obj
comma
id|name
comma
op_amp
id|ent
)paren
suffix:semicolon
)brace
r_else
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
id|_
c_func
(paren
l_string|&quot;more than two blobs given: &squot;%s&squot;&quot;
)paren
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
id|entry-&gt;mode
suffix:semicolon
id|blobs
op_increment
suffix:semicolon
)brace
r_else
(brace
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;unhandled object &squot;%s&squot; given.&quot;
)paren
comma
id|name
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rev.prune_data.nr
)paren
(brace
multiline_comment|/* builtin_diff_b_f() */
id|GUARD_PATHSPEC
c_func
(paren
op_amp
id|rev.prune_data
comma
id|PATHSPEC_FROMTOP
op_or
id|PATHSPEC_LITERAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|path
op_assign
id|rev.prune_data.items
(braket
l_int|0
)braket
dot
id|match
suffix:semicolon
id|paths
op_add_assign
id|rev.prune_data.nr
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now, do the arguments look reasonable?&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ent.nr
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
id|builtin_diff_files
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
id|ent.nr
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
id|ent.nr
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
op_amp
id|ent.objects
(braket
l_int|0
)braket
comma
op_amp
id|ent.objects
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ent.objects
(braket
l_int|0
)braket
dot
id|item-&gt;flags
op_amp
id|UNINTERESTING
)paren
(brace
multiline_comment|/*&n;&t;&t; * diff A...B where there is at least one merge base&n;&t;&t; * between A and B.  We have ent.objects[0] ==&n;&t;&t; * merge-base, ent.objects[ents-2] == A, and&n;&t;&t; * ent.objects[ents-1] == B.  Show diff between the&n;&t;&t; * base and B.  Note that we pick one merge base at&n;&t;&t; * random if there are more than one.&n;&t;&t; */
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
op_amp
id|ent.objects
(braket
l_int|0
)braket
comma
op_amp
id|ent.objects
(braket
id|ent.nr
op_minus
l_int|1
)braket
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
id|ent.objects
comma
id|ent.nr
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
