multiline_comment|/*&n; * Totally braindamaged mbox splitter program.&n; *&n; * It just splits a mbox into a list of files: &quot;0001&quot; &quot;0002&quot; ..&n; * so you can process them further from there.&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;assert.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|variable|git_mailsplit_usage
r_static
r_const
r_char
id|git_mailsplit_usage
(braket
)braket
op_assign
l_string|&quot;git-mailsplit [-d&lt;prec&gt;] [&lt;mbox&gt;] &lt;directory&gt;&quot;
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
r_if
c_cond
(paren
op_logical_neg
id|is_from_line
c_func
(paren
id|buf
comma
id|len
)paren
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
id|die
c_func
(paren
l_string|&quot;cannot open output file %s&quot;
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
(paren
id|buf
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fputs
c_func
(paren
id|buf
comma
id|output
)paren
op_eq
id|EOF
)paren
id|die
c_func
(paren
l_string|&quot;cannot write output&quot;
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
id|mbox
)paren
op_eq
l_int|NULL
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
id|die
c_func
(paren
l_string|&quot;cannot read mbox&quot;
)paren
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_partial
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
DECL|function|main
r_int
id|main
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
)paren
(brace
r_int
id|i
comma
id|nr
comma
id|nr_prec
op_assign
l_int|4
suffix:semicolon
id|FILE
op_star
id|mbox
op_assign
l_int|NULL
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
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-d&quot;
comma
l_int|2
)paren
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
)brace
multiline_comment|/* Either one remaining arg (dir), or two (mbox and dir) */
r_switch
c_cond
(paren
id|argc
id|i
)paren
(brace
r_case
l_int|1
suffix:colon
id|mbox
op_assign
id|stdin
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
(paren
id|mbox
op_assign
id|fopen
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;r&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;cannot open mbox %s for reading&quot;
comma
id|argv
(braket
id|i
)braket
)paren
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
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|argv
(braket
id|argc
l_int|1
)braket
)paren
OL
l_int|0
)paren
id|usage
c_func
(paren
id|git_mailsplit_usage
)paren
suffix:semicolon
id|nr
op_assign
l_int|0
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
id|mbox
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;cannot read mbox&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%0*d&quot;
comma
id|nr_prec
comma
op_increment
id|nr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|split_one
c_func
(paren
id|mbox
comma
id|name
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|printf
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
eof
