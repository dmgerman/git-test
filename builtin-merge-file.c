macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;xdiff/xdiff.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
DECL|variable|merge_file_usage
r_static
r_const
r_char
id|merge_file_usage
(braket
)braket
op_assign
l_string|&quot;git merge-file [-p | --stdout] [-q | --quiet] [-L name1 [-L orig [-L name2]]] file1 orig_file file2&quot;
suffix:semicolon
DECL|function|cmd_merge_file
r_int
id|cmd_merge_file
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
r_const
r_char
op_star
id|names
(braket
l_int|3
)braket
suffix:semicolon
id|mmfile_t
id|mmfs
(braket
l_int|3
)braket
suffix:semicolon
id|mmbuffer_t
id|result
op_assign
(brace
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
id|xpparam_t
id|xpp
op_assign
(brace
id|XDF_NEED_MINIMAL
)brace
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
comma
id|to_stdout
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|argc
OG
l_int|4
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
l_string|&quot;-L&quot;
)paren
op_logical_and
id|i
OL
l_int|3
)paren
(brace
id|names
(braket
id|i
op_increment
)braket
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
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
l_string|&quot;-p&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--stdout&quot;
)paren
)paren
id|to_stdout
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
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--quiet&quot;
)paren
)paren
id|freopen
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
l_string|&quot;w&quot;
comma
id|stderr
)paren
suffix:semicolon
r_else
id|usage
c_func
(paren
id|merge_file_usage
)paren
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
id|argv
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|4
)paren
id|usage
c_func
(paren
id|merge_file_usage
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|names
(braket
id|i
)braket
op_assign
id|argv
(braket
id|i
op_plus
l_int|1
)braket
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|read_mmfile
c_func
(paren
id|mmfs
op_plus
id|i
comma
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|buffer_is_binary
c_func
(paren
id|mmfs
(braket
id|i
)braket
dot
id|ptr
comma
id|mmfs
(braket
id|i
)braket
dot
id|size
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Cannot merge binary files: %s&bslash;n&quot;
comma
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|xdl_merge
c_func
(paren
id|mmfs
op_plus
l_int|1
comma
id|mmfs
op_plus
l_int|0
comma
id|names
(braket
l_int|0
)braket
comma
id|mmfs
op_plus
l_int|2
comma
id|names
(braket
l_int|2
)braket
comma
op_amp
id|xpp
comma
id|XDL_MERGE_ZEALOUS
comma
op_amp
id|result
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|mmfs
(braket
id|i
)braket
dot
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
(brace
r_const
r_char
op_star
id|filename
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|to_stdout
ques
c_cond
id|stdout
suffix:colon
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;wb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Could not open %s for writing&quot;
comma
id|filename
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|result.ptr
comma
id|result.size
comma
l_int|1
comma
id|f
)paren
op_ne
l_int|1
)paren
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Could not write to %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|f
)paren
)paren
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Could not close %s&quot;
comma
id|filename
)paren
suffix:semicolon
id|free
c_func
(paren
id|result.ptr
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
