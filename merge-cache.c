macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|variable|pgm
r_static
r_const
r_char
op_star
id|pgm
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|arguments
r_static
r_const
r_char
op_star
id|arguments
(braket
l_int|8
)braket
suffix:semicolon
DECL|variable|one_shot
r_static
r_int
id|one_shot
suffix:semicolon
DECL|variable|err
r_static
r_int
id|err
suffix:semicolon
DECL|function|run_program
r_static
r_void
id|run_program
c_func
(paren
r_void
)paren
(brace
r_int
id|pid
op_assign
id|fork
c_func
(paren
)paren
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to fork&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|execlp
c_func
(paren
id|pgm
comma
id|arguments
(braket
l_int|0
)braket
comma
id|arguments
(braket
l_int|1
)braket
comma
id|arguments
(braket
l_int|2
)braket
comma
id|arguments
(braket
l_int|3
)braket
comma
id|arguments
(braket
l_int|4
)braket
comma
id|arguments
(braket
l_int|5
)braket
comma
id|arguments
(braket
l_int|6
)braket
comma
id|arguments
(braket
l_int|7
)braket
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unable to execute &squot;%s&squot;&quot;
comma
id|pgm
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
op_logical_or
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
(brace
r_if
c_cond
(paren
id|one_shot
)paren
id|err
op_increment
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;merge program failed&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|merge_entry
r_static
r_int
id|merge_entry
c_func
(paren
r_int
id|pos
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|found
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|active_nr
)paren
id|die
c_func
(paren
l_string|&quot;merge-cache: %s not in the cache&quot;
comma
id|path
)paren
suffix:semicolon
id|arguments
(braket
l_int|0
)braket
op_assign
id|pgm
suffix:semicolon
id|arguments
(braket
l_int|1
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|arguments
(braket
l_int|2
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|arguments
(braket
l_int|3
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|arguments
(braket
l_int|4
)braket
op_assign
id|path
suffix:semicolon
id|arguments
(braket
l_int|5
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|arguments
(braket
l_int|6
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|arguments
(braket
l_int|7
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_static
r_char
id|hexbuf
(braket
l_int|4
)braket
(braket
l_int|60
)braket
suffix:semicolon
r_static
r_char
id|ownbuf
(braket
l_int|4
)braket
(braket
l_int|60
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_int
id|stage
op_assign
id|ce_stage
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|ce-&gt;name
comma
id|path
)paren
)paren
r_break
suffix:semicolon
id|found
op_increment
suffix:semicolon
id|strcpy
c_func
(paren
id|hexbuf
(braket
id|stage
)braket
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|ownbuf
(braket
id|stage
)braket
comma
l_string|&quot;%o&quot;
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_amp
(paren
op_complement
id|S_IFMT
)paren
)paren
suffix:semicolon
id|arguments
(braket
id|stage
)braket
op_assign
id|hexbuf
(braket
id|stage
)braket
suffix:semicolon
id|arguments
(braket
id|stage
op_plus
l_int|4
)braket
op_assign
id|ownbuf
(braket
id|stage
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
op_increment
id|pos
OL
id|active_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|die
c_func
(paren
l_string|&quot;merge-cache: %s not in the cache&quot;
comma
id|path
)paren
suffix:semicolon
id|run_program
c_func
(paren
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|function|merge_file
r_static
r_void
id|merge_file
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If it already exists in the cache as stage0, it&squot;s&n;&t; * already merged and there is nothing to do.&n;&t; */
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
id|merge_entry
c_func
(paren
id|pos
op_minus
l_int|1
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|merge_all
r_static
r_void
id|merge_all
c_func
(paren
r_void
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
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
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|i
op_add_assign
id|merge_entry
c_func
(paren
id|i
comma
id|ce-&gt;name
)paren
op_minus
l_int|1
suffix:semicolon
)brace
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
id|i
comma
id|force_file
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
id|usage
c_func
(paren
l_string|&quot;merge-cache [-o] &lt;merge-program&gt; (-a | &lt;filename&gt;*)&quot;
)paren
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
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
l_string|&quot;-o&quot;
)paren
)paren
(brace
id|one_shot
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|pgm
op_assign
id|argv
(braket
id|i
op_increment
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
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
id|force_file
op_logical_and
op_star
id|arg
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
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|force_file
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-a&quot;
)paren
)paren
(brace
id|merge_all
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;merge-cache: unknown option %s&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
id|merge_file
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
id|die
c_func
(paren
l_string|&quot;merge program failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
