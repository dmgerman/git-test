multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|diff_cmd
r_static
r_char
op_star
id|diff_cmd
op_assign
l_string|&quot;diff -L &squot;%s&squot; -u -N  - &squot;%s&squot;&quot;
suffix:semicolon
multiline_comment|/* Help to copy the thing properly quoted for the shell safety.&n; * any single quote is replaced with &squot;&bslash;&squot;&squot;, and the caller is&n; * expected to enclose the result within a single quote pair.&n; *&n; * E.g.&n; *  original     sq_expand     result&n; *  name     ==&gt; name      ==&gt; &squot;name&squot;&n; *  a b      ==&gt; a b       ==&gt; &squot;a b&squot;&n; *  a&squot;b      ==&gt; a&squot;&bslash;&squot;&squot;b    ==&gt; &squot;a&squot;&bslash;&squot;&squot;b&squot;&n; *&n; * NOTE! The returned memory belongs to this function so&n; * do not free it.&n; */
DECL|function|sq_expand
r_static
r_char
op_star
id|sq_expand
c_func
(paren
r_char
op_star
id|src
)paren
(brace
r_static
r_char
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|buf_size
op_assign
l_int|1
suffix:semicolon
r_int
id|cnt
comma
id|c
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
multiline_comment|/* count single quote characters */
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
comma
id|cp
op_assign
id|src
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cnt
op_increment
comma
id|cp
op_increment
)paren
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;&bslash;&squot;&squot;
)paren
id|cnt
op_add_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|buf_size
OL
id|cnt
)paren
(brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf_size
op_assign
id|cnt
suffix:semicolon
id|buf
op_assign
id|malloc
c_func
(paren
id|cnt
)paren
suffix:semicolon
)brace
id|cp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
op_increment
)paren
)paren
(brace
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;&squot;&squot;
)paren
op_star
id|cp
op_increment
op_assign
id|c
suffix:semicolon
r_else
(brace
id|cp
op_assign
id|strcpy
c_func
(paren
id|cp
comma
l_string|&quot;&squot;&bslash;&bslash;&squot;&squot;&quot;
)paren
suffix:semicolon
id|cp
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|function|show_differences
r_static
r_void
id|show_differences
c_func
(paren
r_char
op_star
id|name
comma
r_void
op_star
id|old_contents
comma
r_int
r_int
r_int
id|old_size
)paren
(brace
id|FILE
op_star
id|f
suffix:semicolon
r_static
r_char
op_star
id|cmd
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|cmd_size
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|name_sq
op_assign
id|sq_expand
c_func
(paren
id|name
)paren
suffix:semicolon
r_int
id|cmd_required_length
op_assign
id|strlen
c_func
(paren
id|name_sq
)paren
op_star
l_int|2
op_plus
id|strlen
c_func
(paren
id|diff_cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd_size
OL
id|cmd_required_length
)paren
(brace
id|free
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|cmd_size
op_assign
id|cmd_required_length
suffix:semicolon
id|cmd
op_assign
id|malloc
c_func
(paren
id|cmd_required_length
)paren
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|cmd
comma
id|cmd_size
comma
id|diff_cmd
comma
id|name_sq
comma
id|name_sq
)paren
suffix:semicolon
id|f
op_assign
id|popen
c_func
(paren
id|cmd
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_size
)paren
id|fwrite
c_func
(paren
id|old_contents
comma
id|old_size
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
id|pclose
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
DECL|function|show_diff_empty
r_static
r_void
id|show_diff_empty
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_char
op_star
id|old
suffix:semicolon
r_int
r_int
r_int
id|size
suffix:semicolon
r_int
id|lines
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|type
(braket
l_int|20
)braket
comma
op_star
id|p
comma
op_star
id|end
suffix:semicolon
id|old
op_assign
id|read_sha1_file
c_func
(paren
id|ce-&gt;sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
id|startline
op_assign
l_int|1
suffix:semicolon
r_int
id|c
op_assign
l_int|0
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;--- %s&bslash;n&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;+++ /dev/null&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_assign
id|old
suffix:semicolon
id|end
op_assign
id|old
op_plus
id|size
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
)paren
r_if
c_cond
(paren
op_star
id|p
op_increment
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|lines
op_increment
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;@@ -1,%d +0,0 @@&bslash;n&quot;
comma
id|lines
)paren
suffix:semicolon
id|p
op_assign
id|old
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|startline
)paren
(brace
id|putchar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
id|startline
op_assign
l_int|0
suffix:semicolon
)brace
id|putchar
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|startline
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
)brace
DECL|variable|show_diff_usage
r_static
r_const
r_char
op_star
id|show_diff_usage
op_assign
l_string|&quot;show-diff [-q] [-s] [-z] [paths...]&quot;
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
id|silent
op_assign
l_int|0
suffix:semicolon
r_int
id|silent_on_nonexisting_files
op_assign
l_int|0
suffix:semicolon
r_int
id|machine_readable
op_assign
l_int|0
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
l_string|&quot;-s&quot;
)paren
)paren
id|silent_on_nonexisting_files
op_assign
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
l_string|&quot;-q&quot;
)paren
)paren
id|silent_on_nonexisting_files
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
l_string|&quot;-z&quot;
)paren
)paren
id|machine_readable
op_assign
l_int|1
suffix:semicolon
r_else
id|usage
c_func
(paren
id|show_diff_usage
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
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|old
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
r_if
c_cond
(paren
id|machine_readable
)paren
id|printf
c_func
(paren
l_string|&quot;U %s%c&quot;
comma
id|ce-&gt;name
comma
l_int|0
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s: Unmerged&bslash;n&quot;
comma
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
op_eq
id|ENOENT
op_logical_and
id|silent_on_nonexisting_files
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|machine_readable
)paren
id|printf
c_func
(paren
l_string|&quot;X %s%c&quot;
comma
id|ce-&gt;name
comma
l_int|0
)paren
suffix:semicolon
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|ce-&gt;name
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
id|errno
op_eq
id|ENOENT
)paren
id|show_diff_empty
c_func
(paren
id|ce
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|machine_readable
)paren
id|printf
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|ce-&gt;name
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
)paren
suffix:semicolon
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%s %s%c&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
comma
id|ce-&gt;name
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|silent
)paren
r_continue
suffix:semicolon
id|old
op_assign
id|read_sha1_file
c_func
(paren
id|ce-&gt;sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
id|show_differences
c_func
(paren
id|ce-&gt;name
comma
id|old
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
