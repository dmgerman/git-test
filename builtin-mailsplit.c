multiline_comment|/*&n; * Totally braindamaged mbox splitter program.&n; *&n; * It just splits a mbox into a list of files: &quot;0001&quot; &quot;0002&quot; ..&n; * so you can process them further from there.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;string-list.h&quot;
DECL|variable|git_mailsplit_usage
r_static
r_const
r_char
id|git_mailsplit_usage
(braket
)braket
op_assign
l_string|&quot;git mailsplit [-d&lt;prec&gt;] [-f&lt;n&gt;] [-b] -o&lt;directory&gt; [&lt;mbox&gt;|&lt;Maildir&gt;...]&quot;
suffix:semicolon
DECL|function|is_from_line
r_static
r_int
id|is_from_line
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_const
r_char
op_star
id|colon
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|20
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;From &quot;
comma
id|line
comma
l_int|5
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|colon
op_assign
id|line
op_plus
id|len
l_int|2
suffix:semicolon
id|line
op_add_assign
l_int|5
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|colon
OL
id|line
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
op_decrement
id|colon
op_eq
l_char|&squot;:&squot;
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isdigit
c_func
(paren
id|colon
(braket
l_int|4
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
id|colon
(braket
l_int|2
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
id|colon
(braket
l_int|1
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
id|colon
(braket
l_int|1
)braket
)paren
op_logical_or
op_logical_neg
id|isdigit
c_func
(paren
id|colon
(braket
l_int|2
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* year */
r_if
c_cond
(paren
id|strtol
c_func
(paren
id|colon
op_plus
l_int|3
comma
l_int|NULL
comma
l_int|10
)paren
op_le
l_int|90
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Ok, close enough */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Could be as small as 64, enough to hold a Unix &quot;From &quot; line. */
DECL|variable|buf
r_static
r_char
id|buf
(braket
l_int|4096
)braket
suffix:semicolon
multiline_comment|/* We cannot use fgets() because our lines can contain NULs */
DECL|function|read_line_with_nul
r_int
id|read_line_with_nul
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
comma
id|FILE
op_star
id|in
)paren
(brace
r_int
id|len
op_assign
l_int|0
comma
id|c
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
id|getc
c_func
(paren
id|in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
r_break
suffix:semicolon
id|buf
(braket
id|len
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_or
id|len
op_plus
l_int|1
op_ge
id|size
)paren
r_break
suffix:semicolon
)brace
id|buf
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* Called with the first line (potentially partial)&n; * already in buf[] -- normally that should begin with&n; * the Unix &quot;From &quot; line.  Write it into the specified&n; * file.&n; */
DECL|function|split_one
r_static
r_int
id|split_one
c_func
(paren
id|FILE
op_star
id|mbox
comma
r_const
r_char
op_star
id|name
comma
r_int
id|allow_bare
)paren
(brace
id|FILE
op_star
id|output
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
id|is_bare
op_assign
op_logical_neg
id|is_from_line
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_bare
op_logical_and
op_logical_neg
id|allow_bare
)paren
r_goto
id|corrupt
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|name
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot open output file &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
id|output
op_assign
id|fdopen
c_func
(paren
id|fd
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
multiline_comment|/* Copy it out, while searching for a line that begins with&n;&t; * &quot;From &quot; and having something that looks like a date format.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|is_partial
op_assign
id|len
op_logical_and
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|buf
comma
l_int|1
comma
id|len
comma
id|output
)paren
op_ne
id|len
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot write output&quot;
)paren
suffix:semicolon
id|len
op_assign
id|read_line_with_nul
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|mbox
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|feof
c_func
(paren
id|mbox
)paren
)paren
(brace
id|status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|die_errno
c_func
(paren
l_string|&quot;cannot read mbox&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|is_partial
op_logical_and
op_logical_neg
id|is_bare
op_logical_and
id|is_from_line
c_func
(paren
id|buf
comma
id|len
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* done with one message */
)brace
id|fclose
c_func
(paren
id|output
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
id|corrupt
suffix:colon
r_if
c_cond
(paren
id|output
)paren
id|fclose
c_func
(paren
id|output
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|name
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;corrupt mailbox&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|populate_maildir_list
r_static
r_int
id|populate_maildir_list
c_func
(paren
r_struct
id|string_list
op_star
id|list
comma
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
id|dent
suffix:semicolon
r_char
id|name
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
op_star
id|subs
(braket
)braket
op_assign
(brace
l_string|&quot;cur&quot;
comma
l_string|&quot;new&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
op_star
id|sub
suffix:semicolon
r_for
c_loop
(paren
id|sub
op_assign
id|subs
suffix:semicolon
op_star
id|sub
suffix:semicolon
op_increment
id|sub
)paren
(brace
id|snprintf
c_func
(paren
id|name
comma
r_sizeof
(paren
id|name
)paren
comma
l_string|&quot;%s/%s&quot;
comma
id|path
comma
op_star
id|sub
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dir
op_assign
id|opendir
c_func
(paren
id|name
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;cannot opendir %s (%s)&quot;
comma
id|name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|dent
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
id|dent-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_continue
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
r_sizeof
(paren
id|name
)paren
comma
l_string|&quot;%s/%s&quot;
comma
op_star
id|sub
comma
id|dent-&gt;d_name
)paren
suffix:semicolon
id|string_list_insert
c_func
(paren
id|name
comma
id|list
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
l_int|0
suffix:semicolon
)brace
DECL|function|split_maildir
r_static
r_int
id|split_maildir
c_func
(paren
r_const
r_char
op_star
id|maildir
comma
r_const
r_char
op_star
id|dir
comma
r_int
id|nr_prec
comma
r_int
id|skip
)paren
(brace
r_char
id|file
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
id|name
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|string_list
id|list
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_if
c_cond
(paren
id|populate_maildir_list
c_func
(paren
op_amp
id|list
comma
id|maildir
)paren
OL
l_int|0
)paren
r_goto
id|out
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
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|FILE
op_star
id|f
suffix:semicolon
id|snprintf
c_func
(paren
id|file
comma
r_sizeof
(paren
id|file
)paren
comma
l_string|&quot;%s/%s&quot;
comma
id|maildir
comma
id|list.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
id|f
op_assign
id|fopen
c_func
(paren
id|file
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot open mail %s (%s)&quot;
comma
id|file
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|f
)paren
op_eq
l_int|NULL
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot read mail %s (%s)&quot;
comma
id|file
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s/%0*d&quot;
comma
id|dir
comma
id|nr_prec
comma
op_increment
id|skip
)paren
suffix:semicolon
id|split_one
c_func
(paren
id|f
comma
id|name
comma
l_int|1
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|skip
suffix:semicolon
id|out
suffix:colon
id|string_list_clear
c_func
(paren
op_amp
id|list
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|split_mbox
r_static
r_int
id|split_mbox
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|dir
comma
r_int
id|allow_bare
comma
r_int
id|nr_prec
comma
r_int
id|skip
)paren
(brace
r_char
id|name
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_int
id|peek
suffix:semicolon
id|FILE
op_star
id|f
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|file
comma
l_string|&quot;-&quot;
)paren
ques
c_cond
id|stdin
suffix:colon
id|fopen
c_func
(paren
id|file
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_int
id|file_done
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot open mbox %s&quot;
comma
id|file
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_do
(brace
id|peek
op_assign
id|fgetc
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|peek
)paren
)paren
suffix:semicolon
id|ungetc
c_func
(paren
id|peek
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|f
)paren
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* empty stdin is OK */
r_if
c_cond
(paren
id|f
op_ne
id|stdin
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot read mbox %s&quot;
comma
id|file
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|file_done
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|file_done
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s/%0*d&quot;
comma
id|dir
comma
id|nr_prec
comma
op_increment
id|skip
)paren
suffix:semicolon
id|file_done
op_assign
id|split_one
c_func
(paren
id|f
comma
id|name
comma
id|allow_bare
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|f
op_ne
id|stdin
)paren
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
id|ret
op_assign
id|skip
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cmd_mailsplit
r_int
id|cmd_mailsplit
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
id|nr
op_assign
l_int|0
comma
id|nr_prec
op_assign
l_int|4
comma
id|num
op_assign
l_int|0
suffix:semicolon
r_int
id|allow_bare
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|dir
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
op_star
id|argp
suffix:semicolon
r_static
r_const
r_char
op_star
id|stdin_only
(braket
)braket
op_assign
(brace
l_string|&quot;-&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_for
c_loop
(paren
id|argp
op_assign
id|argv
op_plus
l_int|1
suffix:semicolon
op_star
id|argp
suffix:semicolon
id|argp
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
op_star
id|argp
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
multiline_comment|/* do flags here */
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;d&squot;
)paren
(brace
id|nr_prec
op_assign
id|strtol
c_func
(paren
id|arg
op_plus
l_int|2
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_prec
OL
l_int|3
op_logical_or
l_int|10
op_le
id|nr_prec
)paren
id|usage
c_func
(paren
id|git_mailsplit_usage
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;f&squot;
)paren
(brace
id|nr
op_assign
id|strtol
c_func
(paren
id|arg
op_plus
l_int|2
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;b&squot;
op_logical_and
op_logical_neg
id|arg
(braket
l_int|2
)braket
)paren
(brace
id|allow_bare
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;o&squot;
op_logical_and
id|arg
(braket
l_int|2
)braket
)paren
(brace
id|dir
op_assign
id|arg
op_plus
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;-&squot;
op_logical_and
op_logical_neg
id|arg
(braket
l_int|2
)braket
)paren
(brace
id|argp
op_increment
suffix:semicolon
multiline_comment|/* -- marks end of options */
r_break
suffix:semicolon
)brace
r_else
(brace
id|die
c_func
(paren
l_string|&quot;unknown option: %s&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
(brace
multiline_comment|/* Backwards compatibility: if no -o specified, accept&n;&t;&t;   &lt;mbox&gt; &lt;dir&gt; or just &lt;dir&gt; */
r_switch
c_cond
(paren
id|argc
(paren
id|argp
op_minus
id|argv
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|dir
op_assign
id|argp
(braket
l_int|0
)braket
suffix:semicolon
id|argp
op_assign
id|stdin_only
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|stdin_only
(braket
l_int|0
)braket
op_assign
id|argp
(braket
l_int|0
)braket
suffix:semicolon
id|dir
op_assign
id|argp
(braket
l_int|1
)braket
suffix:semicolon
id|argp
op_assign
id|stdin_only
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage
c_func
(paren
id|git_mailsplit_usage
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* New usage: if no more argument, parse stdin */
r_if
c_cond
(paren
op_logical_neg
op_star
id|argp
)paren
id|argp
op_assign
id|stdin_only
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|argp
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
op_star
id|argp
op_increment
suffix:semicolon
r_struct
id|stat
id|argstat
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
op_logical_and
id|arg
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
id|split_mbox
c_func
(paren
id|arg
comma
id|dir
comma
id|allow_bare
comma
id|nr_prec
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot split patches from stdin&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|num
op_add_assign
(paren
id|ret
id|nr
)paren
suffix:semicolon
id|nr
op_assign
id|ret
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
c_func
(paren
id|arg
comma
op_amp
id|argstat
)paren
op_eq
l_int|1
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot stat %s (%s)&quot;
comma
id|arg
comma
id|strerror
c_func
(paren
id|errno
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
id|S_ISDIR
c_func
(paren
id|argstat.st_mode
)paren
)paren
id|ret
op_assign
id|split_maildir
c_func
(paren
id|arg
comma
id|dir
comma
id|nr_prec
comma
id|nr
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|split_mbox
c_func
(paren
id|arg
comma
id|dir
comma
id|allow_bare
comma
id|nr_prec
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|error
c_func
(paren
l_string|&quot;cannot split patches from %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|num
op_add_assign
(paren
id|ret
id|nr
)paren
suffix:semicolon
id|nr
op_assign
id|ret
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
