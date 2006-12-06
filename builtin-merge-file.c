macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;xdiff/xdiff.h&quot;
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
DECL|function|read_file
r_static
r_int
id|read_file
c_func
(paren
id|mmfile_t
op_star
id|ptr
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|filename
comma
op_amp
id|st
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not stat %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|f
op_assign
id|fopen
c_func
(paren
id|filename
comma
l_string|&quot;rb&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open %s&quot;
comma
id|filename
)paren
suffix:semicolon
id|ptr-&gt;ptr
op_assign
id|xmalloc
c_func
(paren
id|st.st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
id|ptr-&gt;ptr
comma
id|st.st_size
comma
l_int|1
comma
id|f
)paren
op_ne
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not read %s&quot;
comma
id|filename
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
id|ptr-&gt;size
op_assign
id|st.st_size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_merge_file
r_int
id|cmd_merge_file
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
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
r_if
c_cond
(paren
id|read_file
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
