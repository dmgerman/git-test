macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;reachable.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;progress.h&quot;
macro_line|#include &quot;dir.h&quot;
DECL|variable|prune_usage
r_static
r_const
r_char
op_star
r_const
id|prune_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git prune [-n] [-v] [--expire &lt;time&gt;] [--] [&lt;head&gt;...]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|show_only
r_static
r_int
id|show_only
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|variable|expire
r_static
r_int
r_int
id|expire
suffix:semicolon
DECL|variable|show_progress
r_static
r_int
id|show_progress
op_assign
l_int|1
suffix:semicolon
DECL|function|prune_tmp_file
r_static
r_int
id|prune_tmp_file
c_func
(paren
r_const
r_char
op_star
id|fullpath
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|fullpath
comma
op_amp
id|st
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not stat &squot;%s&squot;&quot;
comma
id|fullpath
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st.st_mtime
OG
id|expire
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|show_only
op_logical_or
id|verbose
)paren
id|printf
c_func
(paren
l_string|&quot;Removing stale temporary file %s&bslash;n&quot;
comma
id|fullpath
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
)paren
id|unlink_or_warn
c_func
(paren
id|fullpath
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_object
r_static
r_int
id|prune_object
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
id|fullpath
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
multiline_comment|/*&n;&t; * Do we know about this object?&n;&t; * It must have been reachable&n;&t; */
r_if
c_cond
(paren
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|fullpath
comma
op_amp
id|st
)paren
)paren
(brace
multiline_comment|/* report errors, but do not stop pruning */
id|error
c_func
(paren
l_string|&quot;Could not stat &squot;%s&squot;&quot;
comma
id|fullpath
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st.st_mtime
OG
id|expire
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|show_only
op_logical_or
id|verbose
)paren
(brace
r_enum
id|object_type
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
(paren
id|type
OG
l_int|0
)paren
ques
c_cond
r_typename
(paren
id|type
)paren
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|show_only
)paren
id|unlink_or_warn
c_func
(paren
id|fullpath
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_cruft
r_static
r_int
id|prune_cruft
c_func
(paren
r_const
r_char
op_star
id|basename
comma
r_const
r_char
op_star
id|path
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|basename
comma
l_string|&quot;tmp_obj_&quot;
)paren
)paren
id|prune_tmp_file
c_func
(paren
id|path
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;bad sha1 file: %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_subdir
r_static
r_int
id|prune_subdir
c_func
(paren
r_int
id|nr
comma
r_const
r_char
op_star
id|path
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
id|show_only
)paren
id|rmdir
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write errors (particularly out of space) can result in&n; * failed temporary packs (and more rarely indexes and other&n; * files beginning with &quot;tmp_&quot;) accumulating in the object&n; * and the pack directories.&n; */
DECL|function|remove_temporary_files
r_static
r_void
id|remove_temporary_files
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
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
op_logical_neg
id|dir
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unable to open directory %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_return
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
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|de-&gt;d_name
comma
l_string|&quot;tmp_&quot;
)paren
)paren
id|prune_tmp_file
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
id|path
comma
id|de-&gt;d_name
)paren
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
DECL|function|cmd_prune
r_int
id|cmd_prune
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
r_struct
id|rev_info
id|revs
suffix:semicolon
r_struct
id|progress
op_star
id|progress
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__DRY_RUN
c_func
(paren
op_amp
id|show_only
comma
id|N_
c_func
(paren
l_string|&quot;do not remove, show only&quot;
)paren
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
comma
id|N_
c_func
(paren
l_string|&quot;report pruned objects&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;progress&quot;
comma
op_amp
id|show_progress
comma
id|N_
c_func
(paren
l_string|&quot;show progress&quot;
)paren
)paren
comma
id|OPT_EXPIRY_DATE
c_func
(paren
l_int|0
comma
l_string|&quot;expire&quot;
comma
op_amp
id|expire
comma
id|N_
c_func
(paren
l_string|&quot;expire objects older than &lt;time&gt;&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
id|expire
op_assign
id|ULONG_MAX
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
id|check_replace_refs
op_assign
l_int|0
suffix:semicolon
id|ref_paranoia
op_assign
l_int|1
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
id|prefix
)paren
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
id|options
comma
id|prune_usage
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argc
op_decrement
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
id|name
op_assign
op_star
id|argv
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
(brace
r_struct
id|object
op_star
id|object
op_assign
id|parse_object_or_die
c_func
(paren
id|sha1
comma
id|name
)paren
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|object
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_progress
op_eq
l_int|1
)paren
id|show_progress
op_assign
id|isatty
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_progress
)paren
id|progress
op_assign
id|start_progress_delay
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Checking connectivity&quot;
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
id|mark_reachable_objects
c_func
(paren
op_amp
id|revs
comma
l_int|1
comma
id|expire
comma
id|progress
)paren
suffix:semicolon
id|stop_progress
c_func
(paren
op_amp
id|progress
)paren
suffix:semicolon
id|for_each_loose_file_in_objdir
c_func
(paren
id|get_object_directory
c_func
(paren
)paren
comma
id|prune_object
comma
id|prune_cruft
comma
id|prune_subdir
comma
l_int|NULL
)paren
suffix:semicolon
id|prune_packed_objects
c_func
(paren
id|show_only
ques
c_cond
id|PRUNE_PACKED_DRY_RUN
suffix:colon
l_int|0
)paren
suffix:semicolon
id|remove_temporary_files
c_func
(paren
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|s
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/pack&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|remove_temporary_files
c_func
(paren
id|s
)paren
suffix:semicolon
id|free
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_repository_shallow
c_func
(paren
)paren
)paren
id|prune_shallow
c_func
(paren
id|show_only
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
