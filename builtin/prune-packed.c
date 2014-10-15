macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;progress.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|prune_packed_usage
r_static
r_const
r_char
op_star
r_const
id|prune_packed_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git prune-packed [-n|--dry-run] [-q|--quiet]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|progress
r_static
r_struct
id|progress
op_star
id|progress
suffix:semicolon
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
r_int
op_star
id|opts
op_assign
id|data
suffix:semicolon
id|display_progress
c_func
(paren
id|progress
comma
id|nr
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|opts
op_amp
id|PRUNE_PACKED_DRY_RUN
)paren
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
id|path
comma
r_void
op_star
id|data
)paren
(brace
r_int
op_star
id|opts
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_pack
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
op_star
id|opts
op_amp
id|PRUNE_PACKED_DRY_RUN
)paren
id|printf
c_func
(paren
l_string|&quot;rm -f %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_else
id|unlink_or_warn
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_packed_objects
r_void
id|prune_packed_objects
c_func
(paren
r_int
id|opts
)paren
(brace
r_if
c_cond
(paren
id|opts
op_amp
id|PRUNE_PACKED_VERBOSE
)paren
id|progress
op_assign
id|start_progress_delay
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Removing duplicate objects&quot;
)paren
comma
l_int|256
comma
l_int|95
comma
l_int|2
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
l_int|NULL
comma
id|prune_subdir
comma
op_amp
id|opts
)paren
suffix:semicolon
multiline_comment|/* Ensure we show 100% before finishing progress */
id|display_progress
c_func
(paren
id|progress
comma
l_int|256
)paren
suffix:semicolon
id|stop_progress
c_func
(paren
op_amp
id|progress
)paren
suffix:semicolon
)brace
DECL|function|cmd_prune_packed
r_int
id|cmd_prune_packed
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
id|opts
op_assign
id|isatty
c_func
(paren
l_int|2
)paren
ques
c_cond
id|PRUNE_PACKED_VERBOSE
suffix:colon
l_int|0
suffix:semicolon
r_const
r_struct
id|option
id|prune_packed_options
(braket
)braket
op_assign
(brace
id|OPT_BIT
c_func
(paren
l_char|&squot;n&squot;
comma
l_string|&quot;dry-run&quot;
comma
op_amp
id|opts
comma
id|N_
c_func
(paren
l_string|&quot;dry run&quot;
)paren
comma
id|PRUNE_PACKED_DRY_RUN
)paren
comma
id|OPT_NEGBIT
c_func
(paren
l_char|&squot;q&squot;
comma
l_string|&quot;quiet&quot;
comma
op_amp
id|opts
comma
id|N_
c_func
(paren
l_string|&quot;be quiet&quot;
)paren
comma
id|PRUNE_PACKED_VERBOSE
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
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
id|prune_packed_options
comma
id|prune_packed_usage
comma
l_int|0
)paren
suffix:semicolon
id|prune_packed_objects
c_func
(paren
id|opts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
