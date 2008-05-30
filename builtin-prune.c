macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;reachable.h&quot;
macro_line|#include &quot;parse-options.h&quot;
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
l_string|&quot;git-prune [-n] [--expire &lt;time&gt;] [--] [&lt;head&gt;...]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|show_only
r_static
r_int
id|show_only
suffix:semicolon
DECL|variable|expire
r_static
r_int
r_int
id|expire
suffix:semicolon
DECL|function|prune_object
r_static
r_int
id|prune_object
c_func
(paren
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|filename
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_const
r_char
op_star
id|fullpath
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
id|path
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|expire
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
)brace
r_if
c_cond
(paren
id|show_only
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
r_else
id|unlink
c_func
(paren
id|fullpath
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prune_dir
r_static
r_int
id|prune_dir
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
l_int|0
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
multiline_comment|/*&n;&t;&t;&t; * Do we know about this object?&n;&t;&t;&t; * It must have been reachable&n;&t;&t;&t; */
r_if
c_cond
(paren
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
r_continue
suffix:semicolon
id|prune_object
c_func
(paren
id|path
comma
id|de-&gt;d_name
comma
id|sha1
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
DECL|function|prune_object_dir
r_static
r_void
id|prune_object_dir
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
id|prune_dir
c_func
(paren
id|i
comma
id|dir
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write errors (particularly out of space) can result in&n; * failed temporary packs (and more rarely indexes and other&n; * files begining with &quot;tmp_&quot;) accumulating in the&n; * object directory.&n; */
DECL|function|remove_temporary_files
r_static
r_void
id|remove_temporary_files
c_func
(paren
r_void
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
r_char
op_star
id|dirname
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|dirname
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
l_string|&quot;Unable to open object directory %s&bslash;n&quot;
comma
id|dirname
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|de-&gt;d_name
comma
l_string|&quot;tmp_&quot;
)paren
)paren
(brace
r_char
id|name
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|c
op_assign
id|snprintf
c_func
(paren
id|name
comma
id|PATH_MAX
comma
l_string|&quot;%s/%s&quot;
comma
id|dirname
comma
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
OL
l_int|0
op_logical_or
id|c
op_ge
id|PATH_MAX
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|expire
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|name
comma
op_amp
id|st
)paren
op_ne
l_int|0
op_logical_or
id|st.st_mtime
op_ge
id|expire
)paren
r_continue
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;Removing stale temporary file %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_only
)paren
id|unlink
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
)brace
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
r_const
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;n&squot;
comma
l_int|NULL
comma
op_amp
id|show_only
comma
l_string|&quot;do not remove, show only&quot;
)paren
comma
id|OPT_DATE
c_func
(paren
l_int|0
comma
l_string|&quot;expire&quot;
comma
op_amp
id|expire
comma
l_string|&quot;expire objects older than &lt;time&gt;&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
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
id|object
)paren
id|die
c_func
(paren
l_string|&quot;bad object: %s&quot;
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
id|mark_reachable_objects
c_func
(paren
op_amp
id|revs
comma
l_int|1
)paren
suffix:semicolon
id|prune_object_dir
c_func
(paren
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|prune_packed_objects
c_func
(paren
id|show_only
)paren
suffix:semicolon
id|remove_temporary_files
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
