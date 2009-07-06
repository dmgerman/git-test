multiline_comment|/*&n; * Low level 3-way in-core file merge.&n; *&n; * Copyright (c) 2007 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;ll-merge.h&quot;
r_struct
id|ll_merge_driver
suffix:semicolon
DECL|typedef|ll_merge_fn
r_typedef
r_int
(paren
op_star
id|ll_merge_fn
)paren
(paren
r_const
r_struct
id|ll_merge_driver
op_star
comma
id|mmbuffer_t
op_star
id|result
comma
r_const
r_char
op_star
id|path
comma
id|mmfile_t
op_star
id|orig
comma
id|mmfile_t
op_star
id|src1
comma
r_const
r_char
op_star
id|name1
comma
id|mmfile_t
op_star
id|src2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|virtual_ancestor
)paren
suffix:semicolon
DECL|struct|ll_merge_driver
r_struct
id|ll_merge_driver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
DECL|member|fn
id|ll_merge_fn
id|fn
suffix:semicolon
DECL|member|recursive
r_const
r_char
op_star
id|recursive
suffix:semicolon
DECL|member|next
r_struct
id|ll_merge_driver
op_star
id|next
suffix:semicolon
DECL|member|cmdline
r_char
op_star
id|cmdline
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Built-in low-levels&n; */
DECL|function|ll_binary_merge
r_static
r_int
id|ll_binary_merge
c_func
(paren
r_const
r_struct
id|ll_merge_driver
op_star
id|drv_unused
comma
id|mmbuffer_t
op_star
id|result
comma
r_const
r_char
op_star
id|path_unused
comma
id|mmfile_t
op_star
id|orig
comma
id|mmfile_t
op_star
id|src1
comma
r_const
r_char
op_star
id|name1
comma
id|mmfile_t
op_star
id|src2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|virtual_ancestor
)paren
(brace
multiline_comment|/*&n;&t; * The tentative merge result is &quot;ours&quot; for the final round,&n;&t; * or common ancestor for an internal merge.  Still return&n;&t; * &quot;conflicted merge&quot; status.&n;&t; */
id|mmfile_t
op_star
id|stolen
op_assign
id|virtual_ancestor
ques
c_cond
id|orig
suffix:colon
id|src1
suffix:semicolon
id|result-&gt;ptr
op_assign
id|stolen-&gt;ptr
suffix:semicolon
id|result-&gt;size
op_assign
id|stolen-&gt;size
suffix:semicolon
id|stolen-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ll_xdl_merge
r_static
r_int
id|ll_xdl_merge
c_func
(paren
r_const
r_struct
id|ll_merge_driver
op_star
id|drv_unused
comma
id|mmbuffer_t
op_star
id|result
comma
r_const
r_char
op_star
id|path
comma
id|mmfile_t
op_star
id|orig
comma
id|mmfile_t
op_star
id|src1
comma
r_const
r_char
op_star
id|name1
comma
id|mmfile_t
op_star
id|src2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|virtual_ancestor
)paren
(brace
id|xpparam_t
id|xpp
suffix:semicolon
r_int
id|style
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buffer_is_binary
c_func
(paren
id|orig-&gt;ptr
comma
id|orig-&gt;size
)paren
op_logical_or
id|buffer_is_binary
c_func
(paren
id|src1-&gt;ptr
comma
id|src1-&gt;size
)paren
op_logical_or
id|buffer_is_binary
c_func
(paren
id|src2-&gt;ptr
comma
id|src2-&gt;size
)paren
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;Cannot merge binary files: %s (%s vs. %s)&bslash;n&quot;
comma
id|path
comma
id|name1
comma
id|name2
)paren
suffix:semicolon
r_return
id|ll_binary_merge
c_func
(paren
id|drv_unused
comma
id|result
comma
id|path
comma
id|orig
comma
id|src1
comma
id|name1
comma
id|src2
comma
id|name2
comma
id|virtual_ancestor
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|xpp
comma
l_int|0
comma
r_sizeof
(paren
id|xpp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_xmerge_style
op_ge
l_int|0
)paren
id|style
op_assign
id|git_xmerge_style
suffix:semicolon
r_return
id|xdl_merge
c_func
(paren
id|orig
comma
id|src1
comma
id|name1
comma
id|src2
comma
id|name2
comma
op_amp
id|xpp
comma
id|XDL_MERGE_ZEALOUS
op_or
id|style
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|ll_union_merge
r_static
r_int
id|ll_union_merge
c_func
(paren
r_const
r_struct
id|ll_merge_driver
op_star
id|drv_unused
comma
id|mmbuffer_t
op_star
id|result
comma
r_const
r_char
op_star
id|path_unused
comma
id|mmfile_t
op_star
id|orig
comma
id|mmfile_t
op_star
id|src1
comma
r_const
r_char
op_star
id|name1
comma
id|mmfile_t
op_star
id|src2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|virtual_ancestor
)paren
(brace
r_char
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_int
id|size
suffix:semicolon
r_const
r_int
id|marker_size
op_assign
l_int|7
suffix:semicolon
r_int
id|status
comma
id|saved_style
suffix:semicolon
multiline_comment|/* We have to force the RCS &quot;merge&quot; style */
id|saved_style
op_assign
id|git_xmerge_style
suffix:semicolon
id|git_xmerge_style
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|ll_xdl_merge
c_func
(paren
id|drv_unused
comma
id|result
comma
id|path_unused
comma
id|orig
comma
id|src1
comma
l_int|NULL
comma
id|src2
comma
l_int|NULL
comma
id|virtual_ancestor
)paren
suffix:semicolon
id|git_xmerge_style
op_assign
id|saved_style
suffix:semicolon
r_if
c_cond
(paren
id|status
op_le
l_int|0
)paren
r_return
id|status
suffix:semicolon
id|size
op_assign
id|result-&gt;size
suffix:semicolon
id|src
op_assign
id|dst
op_assign
id|result-&gt;ptr
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_char
id|ch
suffix:semicolon
r_if
c_cond
(paren
(paren
id|marker_size
OL
id|size
)paren
op_logical_and
(paren
op_star
id|src
op_eq
l_char|&squot;&lt;&squot;
op_logical_or
op_star
id|src
op_eq
l_char|&squot;=&squot;
op_logical_or
op_star
id|src
op_eq
l_char|&squot;&gt;&squot;
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
id|ch
op_assign
op_star
id|src
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
id|marker_size
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|src
(braket
id|i
)braket
op_ne
id|ch
)paren
r_goto
id|not_a_marker
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
id|marker_size
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_goto
id|not_a_marker
suffix:semicolon
id|src
op_add_assign
id|marker_size
op_plus
l_int|1
suffix:semicolon
id|size
op_sub_assign
id|marker_size
op_plus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|not_a_marker
suffix:colon
r_do
(brace
id|ch
op_assign
op_star
id|src
op_increment
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|ch
suffix:semicolon
id|size
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ch
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
id|size
)paren
suffix:semicolon
)brace
id|result-&gt;size
op_assign
id|dst
id|result-&gt;ptr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|LL_BINARY_MERGE
mdefine_line|#define LL_BINARY_MERGE 0
DECL|macro|LL_TEXT_MERGE
mdefine_line|#define LL_TEXT_MERGE 1
DECL|macro|LL_UNION_MERGE
mdefine_line|#define LL_UNION_MERGE 2
DECL|variable|ll_merge_drv
r_static
r_struct
id|ll_merge_driver
id|ll_merge_drv
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;binary&quot;
comma
l_string|&quot;built-in binary merge&quot;
comma
id|ll_binary_merge
)brace
comma
(brace
l_string|&quot;text&quot;
comma
l_string|&quot;built-in 3-way text merge&quot;
comma
id|ll_xdl_merge
)brace
comma
(brace
l_string|&quot;union&quot;
comma
l_string|&quot;built-in union merge&quot;
comma
id|ll_union_merge
)brace
comma
)brace
suffix:semicolon
DECL|function|create_temp
r_static
r_void
id|create_temp
c_func
(paren
id|mmfile_t
op_star
id|src
comma
r_char
op_star
id|path
)paren
(brace
r_int
id|fd
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
l_string|&quot;.merge_file_XXXXXX&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|xmkstemp
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
id|src-&gt;ptr
comma
id|src-&gt;size
)paren
op_ne
id|src-&gt;size
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to write temp-file&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * User defined low-level merge driver support.&n; */
DECL|function|ll_ext_merge
r_static
r_int
id|ll_ext_merge
c_func
(paren
r_const
r_struct
id|ll_merge_driver
op_star
id|fn
comma
id|mmbuffer_t
op_star
id|result
comma
r_const
r_char
op_star
id|path
comma
id|mmfile_t
op_star
id|orig
comma
id|mmfile_t
op_star
id|src1
comma
r_const
r_char
op_star
id|name1
comma
id|mmfile_t
op_star
id|src2
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|virtual_ancestor
)paren
(brace
r_char
id|temp
(braket
l_int|3
)braket
(braket
l_int|50
)braket
suffix:semicolon
r_struct
id|strbuf
id|cmd
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf_expand_dict_entry
id|dict
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;O&quot;
comma
id|temp
(braket
l_int|0
)braket
)brace
comma
(brace
l_string|&quot;A&quot;
comma
id|temp
(braket
l_int|1
)braket
)brace
comma
(brace
l_string|&quot;B&quot;
comma
id|temp
(braket
l_int|2
)braket
)brace
comma
(brace
l_int|NULL
)brace
)brace
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
)braket
op_assign
(brace
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|status
comma
id|fd
comma
id|i
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;cmdline
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;custom merge driver %s lacks command line.&quot;
comma
id|fn-&gt;name
)paren
suffix:semicolon
id|result-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
id|result-&gt;size
op_assign
l_int|0
suffix:semicolon
id|create_temp
c_func
(paren
id|orig
comma
id|temp
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|create_temp
c_func
(paren
id|src1
comma
id|temp
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|create_temp
c_func
(paren
id|src2
comma
id|temp
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|strbuf_expand
c_func
(paren
op_amp
id|cmd
comma
id|fn-&gt;cmdline
comma
id|strbuf_expand_dict_cb
comma
op_amp
id|dict
)paren
suffix:semicolon
id|args
(braket
l_int|2
)braket
op_assign
id|cmd.buf
suffix:semicolon
id|status
op_assign
id|run_command_v_opt
c_func
(paren
id|args
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
id|ERR_RUN_COMMAND_FORK
)paren
suffix:semicolon
multiline_comment|/* failure in run-command */
r_else
id|status
op_assign
id|status
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|temp
(braket
l_int|1
)braket
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
)paren
r_goto
id|close_bad
suffix:semicolon
id|result-&gt;size
op_assign
id|st.st_size
suffix:semicolon
id|result-&gt;ptr
op_assign
id|xmalloc
c_func
(paren
id|result-&gt;size
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_in_full
c_func
(paren
id|fd
comma
id|result-&gt;ptr
comma
id|result-&gt;size
)paren
op_ne
id|result-&gt;size
)paren
(brace
id|free
c_func
(paren
id|result-&gt;ptr
)paren
suffix:semicolon
id|result-&gt;ptr
op_assign
l_int|NULL
suffix:semicolon
id|result-&gt;size
op_assign
l_int|0
suffix:semicolon
)brace
id|close_bad
suffix:colon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|bad
suffix:colon
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
id|unlink_or_warn
c_func
(paren
id|temp
(braket
id|i
)braket
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * merge.default and merge.driver configuration items&n; */
DECL|variable|ll_user_merge
DECL|variable|ll_user_merge_tail
r_static
r_struct
id|ll_merge_driver
op_star
id|ll_user_merge
comma
op_star
op_star
id|ll_user_merge_tail
suffix:semicolon
DECL|variable|default_ll_merge
r_static
r_const
r_char
op_star
id|default_ll_merge
suffix:semicolon
DECL|function|read_merge_config
r_static
r_int
id|read_merge_config
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
r_struct
id|ll_merge_driver
op_star
id|fn
suffix:semicolon
r_const
r_char
op_star
id|ep
comma
op_star
id|name
suffix:semicolon
r_int
id|namelen
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
l_string|&quot;merge.default&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
)paren
id|default_ll_merge
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We are not interested in anything but &quot;merge.&lt;name&gt;.variable&quot;;&n;&t; * especially, we do not want to look at variables such as&n;&t; * &quot;merge.summary&quot;, &quot;merge.tool&quot;, and &quot;merge.verbosity&quot;.&n;&t; */
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;merge.&quot;
)paren
op_logical_or
(paren
id|ep
op_assign
id|strrchr
c_func
(paren
id|var
comma
l_char|&squot;.&squot;
)paren
)paren
op_eq
id|var
op_plus
l_int|5
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Find existing one as we might be processing merge.&lt;name&gt;.var2&n;&t; * after seeing merge.&lt;name&gt;.var1.&n;&t; */
id|name
op_assign
id|var
op_plus
l_int|6
suffix:semicolon
id|namelen
op_assign
id|ep
id|name
suffix:semicolon
r_for
c_loop
(paren
id|fn
op_assign
id|ll_user_merge
suffix:semicolon
id|fn
suffix:semicolon
id|fn
op_assign
id|fn-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|fn-&gt;name
comma
id|name
comma
id|namelen
)paren
op_logical_and
op_logical_neg
id|fn-&gt;name
(braket
id|namelen
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
(brace
id|fn
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|ll_merge_driver
)paren
)paren
suffix:semicolon
id|fn-&gt;name
op_assign
id|xmemdupz
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
id|fn-&gt;fn
op_assign
id|ll_ext_merge
suffix:semicolon
op_star
id|ll_user_merge_tail
op_assign
id|fn
suffix:semicolon
id|ll_user_merge_tail
op_assign
op_amp
(paren
id|fn-&gt;next
)paren
suffix:semicolon
)brace
id|ep
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;name&quot;
comma
id|ep
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: lacks value&quot;
comma
id|var
)paren
suffix:semicolon
id|fn-&gt;description
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;driver&quot;
comma
id|ep
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: lacks value&quot;
comma
id|var
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * merge.&lt;name&gt;.driver specifies the command line:&n;&t;&t; *&n;&t;&t; *&t;command-line&n;&t;&t; *&n;&t;&t; * The command-line will be interpolated with the following&n;&t;&t; * tokens and is given to the shell:&n;&t;&t; *&n;&t;&t; *    %O - temporary file name for the merge base.&n;&t;&t; *    %A - temporary file name for our version.&n;&t;&t; *    %B - temporary file name for the other branches&squot; version.&n;&t;&t; *&n;&t;&t; * The external merge driver should write the results in the&n;&t;&t; * file named by %A, and signal that it has done with zero exit&n;&t;&t; * status.&n;&t;&t; */
id|fn-&gt;cmdline
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;recursive&quot;
comma
id|ep
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: lacks value&quot;
comma
id|var
)paren
suffix:semicolon
id|fn-&gt;recursive
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|initialize_ll_merge
r_static
r_void
id|initialize_ll_merge
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ll_user_merge_tail
)paren
r_return
suffix:semicolon
id|ll_user_merge_tail
op_assign
op_amp
id|ll_user_merge
suffix:semicolon
id|git_config
c_func
(paren
id|read_merge_config
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|find_ll_merge_driver
r_static
r_const
r_struct
id|ll_merge_driver
op_star
id|find_ll_merge_driver
c_func
(paren
r_const
r_char
op_star
id|merge_attr
)paren
(brace
r_struct
id|ll_merge_driver
op_star
id|fn
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|i
suffix:semicolon
id|initialize_ll_merge
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|merge_attr
)paren
)paren
r_return
op_amp
id|ll_merge_drv
(braket
id|LL_TEXT_MERGE
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_FALSE
c_func
(paren
id|merge_attr
)paren
)paren
r_return
op_amp
id|ll_merge_drv
(braket
id|LL_BINARY_MERGE
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ATTR_UNSET
c_func
(paren
id|merge_attr
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|default_ll_merge
)paren
r_return
op_amp
id|ll_merge_drv
(braket
id|LL_TEXT_MERGE
)braket
suffix:semicolon
r_else
id|name
op_assign
id|default_ll_merge
suffix:semicolon
)brace
r_else
id|name
op_assign
id|merge_attr
suffix:semicolon
r_for
c_loop
(paren
id|fn
op_assign
id|ll_user_merge
suffix:semicolon
id|fn
suffix:semicolon
id|fn
op_assign
id|fn-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|fn-&gt;name
comma
id|name
)paren
)paren
r_return
id|fn
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
id|ll_merge_drv
)paren
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
id|ll_merge_drv
(braket
id|i
)braket
dot
id|name
comma
id|name
)paren
)paren
r_return
op_amp
id|ll_merge_drv
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* default to the 3-way */
r_return
op_amp
id|ll_merge_drv
(braket
id|LL_TEXT_MERGE
)braket
suffix:semicolon
)brace
DECL|function|git_path_check_merge
r_static
r_const
r_char
op_star
id|git_path_check_merge
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_static
r_struct
id|git_attr_check
id|attr_merge_check
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_merge_check.attr
)paren
id|attr_merge_check.attr
op_assign
id|git_attr
c_func
(paren
l_string|&quot;merge&quot;
comma
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_checkattr
c_func
(paren
id|path
comma
l_int|1
comma
op_amp
id|attr_merge_check
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|attr_merge_check.value
suffix:semicolon
)brace
DECL|function|ll_merge
r_int
id|ll_merge
c_func
(paren
id|mmbuffer_t
op_star
id|result_buf
comma
r_const
r_char
op_star
id|path
comma
id|mmfile_t
op_star
id|ancestor
comma
id|mmfile_t
op_star
id|ours
comma
r_const
r_char
op_star
id|our_label
comma
id|mmfile_t
op_star
id|theirs
comma
r_const
r_char
op_star
id|their_label
comma
r_int
id|virtual_ancestor
)paren
(brace
r_const
r_char
op_star
id|ll_driver_name
suffix:semicolon
r_const
r_struct
id|ll_merge_driver
op_star
id|driver
suffix:semicolon
id|ll_driver_name
op_assign
id|git_path_check_merge
c_func
(paren
id|path
)paren
suffix:semicolon
id|driver
op_assign
id|find_ll_merge_driver
c_func
(paren
id|ll_driver_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virtual_ancestor
op_logical_and
id|driver-&gt;recursive
)paren
id|driver
op_assign
id|find_ll_merge_driver
c_func
(paren
id|driver-&gt;recursive
)paren
suffix:semicolon
r_return
id|driver
op_member_access_from_pointer
id|fn
c_func
(paren
id|driver
comma
id|result_buf
comma
id|path
comma
id|ancestor
comma
id|ours
comma
id|our_label
comma
id|theirs
comma
id|their_label
comma
id|virtual_ancestor
)paren
suffix:semicolon
)brace
eof
