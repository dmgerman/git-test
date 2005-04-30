multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|diff_files_usage
r_static
r_const
r_char
op_star
id|diff_files_usage
op_assign
l_string|&quot;diff-files [-p] [-q] [-r] [-z] [paths...]&quot;
suffix:semicolon
DECL|variable|generate_patch
r_static
r_int
id|generate_patch
op_assign
l_int|0
suffix:semicolon
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|silent
r_static
r_int
id|silent
op_assign
l_int|0
suffix:semicolon
DECL|function|matches_pathspec
r_static
r_int
id|matches_pathspec
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_char
op_star
op_star
id|spec
comma
r_int
id|cnt
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|namelen
op_assign
id|ce_namelen
c_func
(paren
id|ce
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|speclen
op_assign
id|strlen
c_func
(paren
id|spec
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|spec
(braket
id|i
)braket
comma
id|ce-&gt;name
comma
id|speclen
)paren
op_logical_and
id|speclen
op_le
id|namelen
op_logical_and
(paren
id|ce-&gt;name
(braket
id|speclen
)braket
op_eq
l_int|0
op_logical_or
id|ce-&gt;name
(braket
id|speclen
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_unmerge
r_static
r_void
id|show_unmerge
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|generate_patch
)paren
id|diff_unmerge
c_func
(paren
id|path
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;U %s%c&quot;
comma
id|path
comma
id|line_termination
)paren
suffix:semicolon
)brace
DECL|function|show_file
r_static
r_void
id|show_file
c_func
(paren
r_int
id|pfx
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_if
c_cond
(paren
id|generate_patch
)paren
id|diff_addremove
c_func
(paren
id|pfx
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|ce-&gt;sha1
comma
id|ce-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%c%06o&bslash;t%s&bslash;t%s&bslash;t%s%c&quot;
comma
id|pfx
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
l_string|&quot;blob&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
comma
id|ce-&gt;name
comma
id|line_termination
)paren
suffix:semicolon
)brace
DECL|function|show_modified
r_static
r_void
id|show_modified
c_func
(paren
r_int
id|oldmode
comma
r_int
id|mode
comma
r_const
r_char
op_star
id|old_sha1
comma
r_const
r_char
op_star
id|sha1
comma
r_char
op_star
id|path
)paren
(brace
r_char
id|old_sha1_hex
(braket
l_int|41
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|old_sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|generate_patch
)paren
id|diff_change
c_func
(paren
id|oldmode
comma
id|mode
comma
id|old_sha1
comma
id|sha1
comma
id|path
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;*%06o-&gt;%06o&bslash;tblob&bslash;t%s-&gt;%s&bslash;t%s%c&quot;
comma
id|oldmode
comma
id|mode
comma
id|old_sha1_hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|path
comma
id|line_termination
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
r_static
r_const
r_char
id|null_sha1
(braket
l_int|20
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
r_int
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_int
id|i
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
l_string|&quot;-p&quot;
)paren
)paren
id|generate_patch
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
l_string|&quot;-q&quot;
)paren
)paren
id|silent
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
l_string|&quot;-r&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* no-op */
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
l_string|&quot;-s&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* no-op */
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
l_string|&quot;-z&quot;
)paren
)paren
id|line_termination
op_assign
l_int|0
suffix:semicolon
r_else
id|usage
c_func
(paren
id|diff_files_usage
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
multiline_comment|/* At this point, if argc == 1, then we are doing everything.&n;&t; * Otherwise argv[1] .. argv[argc-1] have the explicit paths.&n;&t; */
r_if
c_cond
(paren
id|entries
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
m_exit
(paren
l_int|1
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
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
r_int
id|oldmode
comma
id|mode
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_int
id|changed
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|argc
op_logical_and
op_logical_neg
id|matches_pathspec
c_func
(paren
id|ce
comma
id|argv
op_plus
l_int|1
comma
id|argc
op_minus
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|show_unmerge
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|entries
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
id|i
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
multiline_comment|/* compensate for loop control increments */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ENOENT
)paren
(brace
id|perror
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|silent
)paren
r_continue
suffix:semicolon
id|show_file
c_func
(paren
l_char|&squot;-&squot;
comma
id|ce
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|changed
op_assign
id|cache_match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
r_continue
suffix:semicolon
id|oldmode
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
id|mode
op_assign
id|S_IFREG
op_or
id|ce_permissions
c_func
(paren
id|st.st_mode
)paren
suffix:semicolon
id|show_modified
c_func
(paren
id|oldmode
comma
id|mode
comma
id|ce-&gt;sha1
comma
id|null_sha1
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
