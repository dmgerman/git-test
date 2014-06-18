macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;levenshtein.h&quot;
macro_line|#include &quot;help.h&quot;
macro_line|#include &quot;common-cmds.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;column.h&quot;
macro_line|#include &quot;version.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|function|add_cmdname
r_void
id|add_cmdname
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_struct
id|cmdname
op_star
id|ent
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ent
)paren
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|ent-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|ent-&gt;name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|cmds-&gt;names
comma
id|cmds-&gt;cnt
op_plus
l_int|1
comma
id|cmds-&gt;alloc
)paren
suffix:semicolon
id|cmds-&gt;names
(braket
id|cmds-&gt;cnt
op_increment
)braket
op_assign
id|ent
suffix:semicolon
)brace
DECL|function|clean_cmdnames
r_static
r_void
id|clean_cmdnames
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
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
id|cmds-&gt;cnt
suffix:semicolon
op_increment
id|i
)paren
id|free
c_func
(paren
id|cmds-&gt;names
(braket
id|i
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|cmds-&gt;names
)paren
suffix:semicolon
id|cmds-&gt;cnt
op_assign
l_int|0
suffix:semicolon
id|cmds-&gt;alloc
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|cmdname_compare
r_static
r_int
id|cmdname_compare
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|cmdname
op_star
id|a
op_assign
op_star
(paren
r_struct
id|cmdname
op_star
op_star
)paren
id|a_
suffix:semicolon
r_struct
id|cmdname
op_star
id|b
op_assign
op_star
(paren
r_struct
id|cmdname
op_star
op_star
)paren
id|b_
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|uniq
r_static
r_void
id|uniq
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmds-&gt;cnt
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|cmds-&gt;cnt
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
id|cmds-&gt;names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|cmds-&gt;names
(braket
id|j
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|name
)paren
)paren
id|free
c_func
(paren
id|cmds-&gt;names
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|cmds-&gt;names
(braket
id|j
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|i
)braket
suffix:semicolon
)brace
id|cmds-&gt;cnt
op_assign
id|j
suffix:semicolon
)brace
DECL|function|exclude_cmds
r_void
id|exclude_cmds
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_struct
id|cmdnames
op_star
id|excludes
)paren
(brace
r_int
id|ci
comma
id|cj
comma
id|ei
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|ci
op_assign
id|cj
op_assign
id|ei
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ci
OL
id|cmds-&gt;cnt
op_logical_and
id|ei
OL
id|excludes-&gt;cnt
)paren
(brace
id|cmp
op_assign
id|strcmp
c_func
(paren
id|cmds-&gt;names
(braket
id|ci
)braket
op_member_access_from_pointer
id|name
comma
id|excludes-&gt;names
(braket
id|ei
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
id|cmds-&gt;names
(braket
id|cj
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmp
op_eq
l_int|0
)paren
(brace
id|ei
op_increment
suffix:semicolon
id|free
c_func
(paren
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
id|ei
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ci
OL
id|cmds-&gt;cnt
)paren
id|cmds-&gt;names
(braket
id|cj
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
suffix:semicolon
id|cmds-&gt;cnt
op_assign
id|cj
suffix:semicolon
)brace
DECL|function|pretty_print_cmdnames
r_static
r_void
id|pretty_print_cmdnames
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_int
r_int
id|colopts
)paren
(brace
r_struct
id|string_list
id|list
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|column_options
id|copts
suffix:semicolon
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
id|cmds-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
id|string_list_append
c_func
(paren
op_amp
id|list
comma
id|cmds-&gt;names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * always enable column display, we only consult column.*&n;&t; * about layout strategy and stuff&n;&t; */
id|colopts
op_assign
(paren
id|colopts
op_amp
op_complement
id|COL_ENABLE_MASK
)paren
op_or
id|COL_ENABLED
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|copts
comma
l_int|0
comma
r_sizeof
(paren
id|copts
)paren
)paren
suffix:semicolon
id|copts.indent
op_assign
l_string|&quot;  &quot;
suffix:semicolon
id|copts.padding
op_assign
l_int|2
suffix:semicolon
id|print_columns
c_func
(paren
op_amp
id|list
comma
id|colopts
comma
op_amp
id|copts
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|list
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|is_executable
r_static
r_int
id|is_executable
c_func
(paren
r_const
r_char
op_star
id|name
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
op_logical_or
multiline_comment|/* stat, not lstat */
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#if defined(GIT_WINDOWS_NATIVE)
(brace
multiline_comment|/* cannot trust the executable bit, peek into the file instead */
r_char
id|buf
(braket
l_int|3
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
id|n
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|name
comma
id|O_RDONLY
)paren
suffix:semicolon
id|st.st_mode
op_and_assign
op_complement
id|S_IXUSR
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
id|n
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|2
)paren
multiline_comment|/* DOS executables start with &quot;MZ&quot; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;#!&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|buf
comma
l_string|&quot;MZ&quot;
)paren
)paren
id|st.st_mode
op_or_assign
id|S_IXUSR
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
id|st.st_mode
op_amp
id|S_IXUSR
suffix:semicolon
)brace
DECL|function|list_commands_in_dir
r_static
r_void
id|list_commands_in_dir
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|prefix
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
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|len
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
op_logical_neg
id|prefix
)paren
id|prefix
op_assign
l_string|&quot;git-&quot;
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%s/&quot;
comma
id|path
)paren
suffix:semicolon
id|len
op_assign
id|buf.len
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
r_const
r_char
op_star
id|ent
suffix:semicolon
r_int
id|entlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skip_prefix
c_func
(paren
id|de-&gt;d_name
comma
id|prefix
comma
op_amp
id|ent
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|buf
comma
id|len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_executable
c_func
(paren
id|buf.buf
)paren
)paren
r_continue
suffix:semicolon
id|entlen
op_assign
id|strlen
c_func
(paren
id|ent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_extension
c_func
(paren
id|ent
comma
l_string|&quot;.exe&quot;
)paren
)paren
id|entlen
op_sub_assign
l_int|4
suffix:semicolon
id|add_cmdname
c_func
(paren
id|cmds
comma
id|ent
comma
id|entlen
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|load_command_list
r_void
id|load_command_list
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_struct
id|cmdnames
op_star
id|main_cmds
comma
r_struct
id|cmdnames
op_star
id|other_cmds
)paren
(brace
r_const
r_char
op_star
id|env_path
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|exec_path
op_assign
id|git_exec_path
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exec_path
)paren
(brace
id|list_commands_in_dir
c_func
(paren
id|main_cmds
comma
id|exec_path
comma
id|prefix
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|main_cmds-&gt;names
comma
id|main_cmds-&gt;cnt
comma
r_sizeof
(paren
op_star
id|main_cmds-&gt;names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
id|main_cmds
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|env_path
)paren
(brace
r_char
op_star
id|paths
comma
op_star
id|path
comma
op_star
id|colon
suffix:semicolon
id|path
op_assign
id|paths
op_assign
id|xstrdup
c_func
(paren
id|env_path
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|colon
op_assign
id|strchr
c_func
(paren
id|path
comma
id|PATH_SEP
)paren
)paren
)paren
op_star
id|colon
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exec_path
op_logical_or
id|strcmp
c_func
(paren
id|path
comma
id|exec_path
)paren
)paren
id|list_commands_in_dir
c_func
(paren
id|other_cmds
comma
id|path
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|colon
)paren
r_break
suffix:semicolon
id|path
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
)brace
id|free
c_func
(paren
id|paths
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|other_cmds-&gt;names
comma
id|other_cmds-&gt;cnt
comma
r_sizeof
(paren
op_star
id|other_cmds-&gt;names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
id|other_cmds
)paren
suffix:semicolon
)brace
id|exclude_cmds
c_func
(paren
id|other_cmds
comma
id|main_cmds
)paren
suffix:semicolon
)brace
DECL|function|list_commands
r_void
id|list_commands
c_func
(paren
r_int
r_int
id|colopts
comma
r_struct
id|cmdnames
op_star
id|main_cmds
comma
r_struct
id|cmdnames
op_star
id|other_cmds
)paren
(brace
r_if
c_cond
(paren
id|main_cmds-&gt;cnt
)paren
(brace
r_const
r_char
op_star
id|exec_path
op_assign
id|git_exec_path
c_func
(paren
)paren
suffix:semicolon
id|printf_ln
c_func
(paren
id|_
c_func
(paren
l_string|&quot;available git commands in &squot;%s&squot;&quot;
)paren
comma
id|exec_path
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pretty_print_cmdnames
c_func
(paren
id|main_cmds
comma
id|colopts
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|other_cmds-&gt;cnt
)paren
(brace
id|printf_ln
c_func
(paren
id|_
c_func
(paren
l_string|&quot;git commands available from elsewhere on your $PATH&quot;
)paren
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pretty_print_cmdnames
c_func
(paren
id|other_cmds
comma
id|colopts
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|list_common_cmds_help
r_void
id|list_common_cmds_help
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|longest
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
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|longest
OL
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
)paren
id|longest
op_assign
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
id|_
c_func
(paren
l_string|&quot;The most commonly used git commands are:&quot;
)paren
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
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;   %s   &quot;
comma
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|mput_char
c_func
(paren
l_char|&squot; &squot;
comma
id|longest
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
id|_
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|help
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|is_in_cmdlist
r_int
id|is_in_cmdlist
c_func
(paren
r_struct
id|cmdnames
op_star
id|c
comma
r_const
r_char
op_star
id|s
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
id|c-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
id|c-&gt;names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|autocorrect
r_static
r_int
id|autocorrect
suffix:semicolon
DECL|variable|aliases
r_static
r_struct
id|cmdnames
id|aliases
suffix:semicolon
DECL|function|git_unknown_cmd_config
r_static
r_int
id|git_unknown_cmd_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_const
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;help.autocorrect&quot;
)paren
)paren
id|autocorrect
op_assign
id|git_config_int
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
multiline_comment|/* Also use aliases for command lookup */
r_if
c_cond
(paren
id|skip_prefix
c_func
(paren
id|var
comma
l_string|&quot;alias.&quot;
comma
op_amp
id|p
)paren
)paren
id|add_cmdname
c_func
(paren
op_amp
id|aliases
comma
id|p
comma
id|strlen
c_func
(paren
id|p
)paren
)paren
suffix:semicolon
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
DECL|function|levenshtein_compare
r_static
r_int
id|levenshtein_compare
c_func
(paren
r_const
r_void
op_star
id|p1
comma
r_const
r_void
op_star
id|p2
)paren
(brace
r_const
r_struct
id|cmdname
op_star
r_const
op_star
id|c1
op_assign
id|p1
comma
op_star
r_const
op_star
id|c2
op_assign
id|p2
suffix:semicolon
r_const
r_char
op_star
id|s1
op_assign
(paren
op_star
id|c1
)paren
op_member_access_from_pointer
id|name
comma
op_star
id|s2
op_assign
(paren
op_star
id|c2
)paren
op_member_access_from_pointer
id|name
suffix:semicolon
r_int
id|l1
op_assign
(paren
op_star
id|c1
)paren
op_member_access_from_pointer
id|len
suffix:semicolon
r_int
id|l2
op_assign
(paren
op_star
id|c2
)paren
op_member_access_from_pointer
id|len
suffix:semicolon
r_return
id|l1
op_ne
id|l2
ques
c_cond
id|l1
id|l2
suffix:colon
id|strcmp
c_func
(paren
id|s1
comma
id|s2
)paren
suffix:semicolon
)brace
DECL|function|add_cmd_list
r_static
r_void
id|add_cmd_list
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_struct
id|cmdnames
op_star
id|old
)paren
(brace
r_int
id|i
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|cmds-&gt;names
comma
id|cmds-&gt;cnt
op_plus
id|old-&gt;cnt
comma
id|cmds-&gt;alloc
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
id|old-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
id|cmds-&gt;names
(braket
id|cmds-&gt;cnt
op_increment
)braket
op_assign
id|old-&gt;names
(braket
id|i
)braket
suffix:semicolon
id|free
c_func
(paren
id|old-&gt;names
)paren
suffix:semicolon
id|old-&gt;cnt
op_assign
l_int|0
suffix:semicolon
id|old-&gt;names
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* An empirically derived magic number */
DECL|macro|SIMILARITY_FLOOR
mdefine_line|#define SIMILARITY_FLOOR 7
DECL|macro|SIMILAR_ENOUGH
mdefine_line|#define SIMILAR_ENOUGH(x) ((x) &lt; SIMILARITY_FLOOR)
DECL|variable|bad_interpreter_advice
r_static
r_const
r_char
id|bad_interpreter_advice
(braket
)braket
op_assign
id|N_
c_func
(paren
l_string|&quot;&squot;%s&squot; appears to be a git command, but we were not&bslash;n&quot;
l_string|&quot;able to execute it. Maybe git-%s is broken?&quot;
)paren
suffix:semicolon
DECL|function|help_unknown_cmd
r_const
r_char
op_star
id|help_unknown_cmd
c_func
(paren
r_const
r_char
op_star
id|cmd
)paren
(brace
r_int
id|i
comma
id|n
comma
id|best_similarity
op_assign
l_int|0
suffix:semicolon
r_struct
id|cmdnames
id|main_cmds
comma
id|other_cmds
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|main_cmds
comma
l_int|0
comma
r_sizeof
(paren
id|main_cmds
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|other_cmds
comma
l_int|0
comma
r_sizeof
(paren
id|other_cmds
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|aliases
comma
l_int|0
comma
r_sizeof
(paren
id|aliases
)paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_unknown_cmd_config
comma
l_int|NULL
)paren
suffix:semicolon
id|load_command_list
c_func
(paren
l_string|&quot;git-&quot;
comma
op_amp
id|main_cmds
comma
op_amp
id|other_cmds
)paren
suffix:semicolon
id|add_cmd_list
c_func
(paren
op_amp
id|main_cmds
comma
op_amp
id|aliases
)paren
suffix:semicolon
id|add_cmd_list
c_func
(paren
op_amp
id|main_cmds
comma
op_amp
id|other_cmds
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|main_cmds.names
comma
id|main_cmds.cnt
comma
r_sizeof
(paren
id|main_cmds.names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
op_amp
id|main_cmds
)paren
suffix:semicolon
multiline_comment|/* This abuses cmdname-&gt;len for levenshtein distance */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|main_cmds.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|cmp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* avoid compiler stupidity */
r_const
r_char
op_star
id|candidate
op_assign
id|main_cmds.names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
multiline_comment|/*&n;&t;&t; * An exact match means we have the command, but&n;&t;&t; * for some reason exec&squot;ing it gave us ENOENT; probably&n;&t;&t; * it&squot;s a bad interpreter in the #! line.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|candidate
comma
id|cmd
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
id|bad_interpreter_advice
)paren
comma
id|cmd
comma
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Does the candidate appear in common_cmds list? */
r_while
c_loop
(paren
id|n
OL
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
op_logical_and
(paren
id|cmp
op_assign
id|strcmp
c_func
(paren
id|common_cmds
(braket
id|n
)braket
dot
id|name
comma
id|candidate
)paren
)paren
OL
l_int|0
)paren
id|n
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
OL
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
)paren
op_logical_and
op_logical_neg
id|cmp
)paren
(brace
multiline_comment|/* Yes, this is one of the common commands */
id|n
op_increment
suffix:semicolon
multiline_comment|/* use the entry from common_cmds[] */
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|candidate
comma
id|cmd
)paren
)paren
(brace
multiline_comment|/* Give prefix match a very good score */
id|main_cmds.names
(braket
id|i
)braket
op_member_access_from_pointer
id|len
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|main_cmds.names
(braket
id|i
)braket
op_member_access_from_pointer
id|len
op_assign
id|levenshtein
c_func
(paren
id|cmd
comma
id|candidate
comma
l_int|0
comma
l_int|2
comma
l_int|1
comma
l_int|3
)paren
op_plus
l_int|1
suffix:semicolon
)brace
id|qsort
c_func
(paren
id|main_cmds.names
comma
id|main_cmds.cnt
comma
r_sizeof
(paren
op_star
id|main_cmds.names
)paren
comma
id|levenshtein_compare
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|main_cmds.cnt
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Uh oh. Your system reports no Git commands at all.&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* skip and count prefix matches */
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|main_cmds.cnt
op_logical_and
op_logical_neg
id|main_cmds.names
(braket
id|n
)braket
op_member_access_from_pointer
id|len
suffix:semicolon
id|n
op_increment
)paren
suffix:semicolon
multiline_comment|/* still counting */
r_if
c_cond
(paren
id|main_cmds.cnt
op_le
id|n
)paren
(brace
multiline_comment|/* prefix matches with everything? that is too ambiguous */
id|best_similarity
op_assign
id|SIMILARITY_FLOOR
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* count all the most similar ones */
r_for
c_loop
(paren
id|best_similarity
op_assign
id|main_cmds.names
(braket
id|n
op_increment
)braket
op_member_access_from_pointer
id|len
suffix:semicolon
(paren
id|n
OL
id|main_cmds.cnt
op_logical_and
id|best_similarity
op_eq
id|main_cmds.names
(braket
id|n
)braket
op_member_access_from_pointer
id|len
)paren
suffix:semicolon
id|n
op_increment
)paren
suffix:semicolon
multiline_comment|/* still counting */
)brace
r_if
c_cond
(paren
id|autocorrect
op_logical_and
id|n
op_eq
l_int|1
op_logical_and
id|SIMILAR_ENOUGH
c_func
(paren
id|best_similarity
)paren
)paren
(brace
r_const
r_char
op_star
id|assumed
op_assign
id|main_cmds.names
(braket
l_int|0
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
id|main_cmds.names
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|clean_cmdnames
c_func
(paren
op_amp
id|main_cmds
)paren
suffix:semicolon
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;WARNING: You called a Git command named &squot;%s&squot;, &quot;
l_string|&quot;which does not exist.&bslash;n&quot;
l_string|&quot;Continuing under the assumption that you meant &squot;%s&squot;&quot;
)paren
comma
id|cmd
comma
id|assumed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|autocorrect
OG
l_int|0
)paren
(brace
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;in %0.1f seconds automatically...&quot;
)paren
comma
(paren
r_float
)paren
id|autocorrect
op_div
l_float|10.0
)paren
suffix:semicolon
id|poll
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|autocorrect
op_star
l_int|100
)paren
suffix:semicolon
)brace
r_return
id|assumed
suffix:semicolon
)brace
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;git: &squot;%s&squot; is not a git command. See &squot;git --help&squot;.&quot;
)paren
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SIMILAR_ENOUGH
c_func
(paren
id|best_similarity
)paren
)paren
(brace
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|Q_
c_func
(paren
l_string|&quot;&bslash;nDid you mean this?&quot;
comma
l_string|&quot;&bslash;nDid you mean one of these?&quot;
comma
id|n
)paren
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
id|n
suffix:semicolon
id|i
op_increment
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;t%s&bslash;n&quot;
comma
id|main_cmds.names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cmd_version
r_int
id|cmd_version
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
multiline_comment|/*&n;&t; * The format of this string should be kept stable for compatibility&n;&t; * with external projects that rely on the output of &quot;git version&quot;.&n;&t; */
id|printf
c_func
(paren
l_string|&quot;git version %s&bslash;n&quot;
comma
id|git_version_string
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|similar_ref_cb
r_struct
id|similar_ref_cb
(brace
DECL|member|base_ref
r_const
r_char
op_star
id|base_ref
suffix:semicolon
DECL|member|similar_refs
r_struct
id|string_list
op_star
id|similar_refs
suffix:semicolon
)brace
suffix:semicolon
DECL|function|append_similar_ref
r_static
r_int
id|append_similar_ref
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
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|similar_ref_cb
op_star
id|cb
op_assign
(paren
r_struct
id|similar_ref_cb
op_star
)paren
(paren
id|cb_data
)paren
suffix:semicolon
r_char
op_star
id|branch
op_assign
id|strrchr
c_func
(paren
id|refname
comma
l_char|&squot;/&squot;
)paren
op_plus
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|remote
suffix:semicolon
multiline_comment|/* A remote branch of the same name is deemed similar */
r_if
c_cond
(paren
id|skip_prefix
c_func
(paren
id|refname
comma
l_string|&quot;refs/remotes/&quot;
comma
op_amp
id|remote
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|branch
comma
id|cb-&gt;base_ref
)paren
)paren
id|string_list_append
c_func
(paren
id|cb-&gt;similar_refs
comma
id|remote
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|guess_refs
r_static
r_struct
id|string_list
id|guess_refs
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_struct
id|similar_ref_cb
id|ref_cb
suffix:semicolon
r_struct
id|string_list
id|similar_refs
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
id|ref_cb.base_ref
op_assign
id|ref
suffix:semicolon
id|ref_cb.similar_refs
op_assign
op_amp
id|similar_refs
suffix:semicolon
id|for_each_ref
c_func
(paren
id|append_similar_ref
comma
op_amp
id|ref_cb
)paren
suffix:semicolon
r_return
id|similar_refs
suffix:semicolon
)brace
DECL|function|help_unknown_ref
r_void
id|help_unknown_ref
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_char
op_star
id|cmd
comma
r_const
r_char
op_star
id|error
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|string_list
id|suggested_refs
op_assign
id|guess_refs
c_func
(paren
id|ref
)paren
suffix:semicolon
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;%s: %s - %s&quot;
)paren
comma
id|cmd
comma
id|ref
comma
id|error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|suggested_refs.nr
OG
l_int|0
)paren
(brace
id|fprintf_ln
c_func
(paren
id|stderr
comma
id|Q_
c_func
(paren
l_string|&quot;&bslash;nDid you mean this?&quot;
comma
l_string|&quot;&bslash;nDid you mean one of these?&quot;
comma
id|suggested_refs.nr
)paren
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
id|suggested_refs.nr
suffix:semicolon
id|i
op_increment
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;&bslash;t%s&bslash;n&quot;
comma
id|suggested_refs.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
)brace
id|string_list_clear
c_func
(paren
op_amp
id|suggested_refs
comma
l_int|0
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
