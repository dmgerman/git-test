multiline_comment|/*&n; * Low level 3-way in-core file merge.&n; *&n; * Copyright (c) 2007 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;ll-merge.h&quot;
macro_line|#include &quot;quote.h&quot;
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
r_const
r_char
op_star
id|orig_name
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
r_const
r_struct
id|ll_merge_options
op_star
id|opts
comma
r_int
id|marker_size
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
id|path
comma
id|mmfile_t
op_star
id|orig
comma
r_const
r_char
op_star
id|orig_name
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
r_const
r_struct
id|ll_merge_options
op_star
id|opts
comma
r_int
id|marker_size
)paren
(brace
id|mmfile_t
op_star
id|stolen
suffix:semicolon
m_assert
(paren
id|opts
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The tentative merge result is the or common ancestor for an internal merge.&n;&t; */
r_if
c_cond
(paren
id|opts-&gt;virtual_ancestor
)paren
(brace
id|stolen
op_assign
id|orig
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|opts-&gt;variant
)paren
(brace
r_default
suffix:colon
id|warning
c_func
(paren
l_string|&quot;Cannot merge binary files: %s (%s vs. %s)&quot;
comma
id|path
comma
id|name1
comma
id|name2
)paren
suffix:semicolon
multiline_comment|/* fallthru */
r_case
id|XDL_MERGE_FAVOR_OURS
suffix:colon
id|stolen
op_assign
id|src1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XDL_MERGE_FAVOR_THEIRS
suffix:colon
id|stolen
op_assign
id|src2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n;&t; * With -Xtheirs or -Xours, we have cleanly merged;&n;&t; * otherwise we got a conflict.&n;&t; */
r_return
(paren
id|opts-&gt;variant
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
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
r_const
r_char
op_star
id|orig_name
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
r_const
r_struct
id|ll_merge_options
op_star
id|opts
comma
r_int
id|marker_size
)paren
(brace
id|xmparam_t
id|xmp
suffix:semicolon
m_assert
(paren
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|orig-&gt;size
OG
id|MAX_XDIFF_SIZE
op_logical_or
id|src1-&gt;size
OG
id|MAX_XDIFF_SIZE
op_logical_or
id|src2-&gt;size
OG
id|MAX_XDIFF_SIZE
op_logical_or
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
id|orig_name
comma
id|src1
comma
id|name1
comma
id|src2
comma
id|name2
comma
id|opts
comma
id|marker_size
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|xmp
comma
l_int|0
comma
r_sizeof
(paren
id|xmp
)paren
)paren
suffix:semicolon
id|xmp.level
op_assign
id|XDL_MERGE_ZEALOUS
suffix:semicolon
id|xmp.favor
op_assign
id|opts-&gt;variant
suffix:semicolon
id|xmp.xpp.flags
op_assign
id|opts-&gt;xdl_opts
suffix:semicolon
r_if
c_cond
(paren
id|git_xmerge_style
op_ge
l_int|0
)paren
id|xmp.style
op_assign
id|git_xmerge_style
suffix:semicolon
r_if
c_cond
(paren
id|marker_size
OG
l_int|0
)paren
id|xmp.marker_size
op_assign
id|marker_size
suffix:semicolon
id|xmp.ancestor
op_assign
id|orig_name
suffix:semicolon
id|xmp.file1
op_assign
id|name1
suffix:semicolon
id|xmp.file2
op_assign
id|name2
suffix:semicolon
r_return
id|xdl_merge
c_func
(paren
id|orig
comma
id|src1
comma
id|src2
comma
op_amp
id|xmp
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
r_const
r_char
op_star
id|orig_name
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
r_const
r_struct
id|ll_merge_options
op_star
id|opts
comma
r_int
id|marker_size
)paren
(brace
multiline_comment|/* Use union favor */
r_struct
id|ll_merge_options
id|o
suffix:semicolon
m_assert
(paren
id|opts
)paren
suffix:semicolon
id|o
op_assign
op_star
id|opts
suffix:semicolon
id|o.variant
op_assign
id|XDL_MERGE_FAVOR_UNION
suffix:semicolon
r_return
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
l_int|NULL
comma
id|src1
comma
l_int|NULL
comma
id|src2
comma
l_int|NULL
comma
op_amp
id|o
comma
id|marker_size
)paren
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
comma
r_int
id|len
)paren
(brace
r_int
id|fd
suffix:semicolon
id|xsnprintf
c_func
(paren
id|path
comma
id|len
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
r_const
r_char
op_star
id|orig_name
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
r_const
r_struct
id|ll_merge_options
op_star
id|opts
comma
r_int
id|marker_size
)paren
(brace
r_char
id|temp
(braket
l_int|4
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
l_int|6
)braket
suffix:semicolon
r_struct
id|strbuf
id|path_sq
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|args
(braket
)braket
op_assign
(brace
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
m_assert
(paren
id|opts
)paren
suffix:semicolon
id|sq_quote_buf
c_func
(paren
op_amp
id|path_sq
comma
id|path
)paren
suffix:semicolon
id|dict
(braket
l_int|0
)braket
dot
id|placeholder
op_assign
l_string|&quot;O&quot;
suffix:semicolon
id|dict
(braket
l_int|0
)braket
dot
id|value
op_assign
id|temp
(braket
l_int|0
)braket
suffix:semicolon
id|dict
(braket
l_int|1
)braket
dot
id|placeholder
op_assign
l_string|&quot;A&quot;
suffix:semicolon
id|dict
(braket
l_int|1
)braket
dot
id|value
op_assign
id|temp
(braket
l_int|1
)braket
suffix:semicolon
id|dict
(braket
l_int|2
)braket
dot
id|placeholder
op_assign
l_string|&quot;B&quot;
suffix:semicolon
id|dict
(braket
l_int|2
)braket
dot
id|value
op_assign
id|temp
(braket
l_int|2
)braket
suffix:semicolon
id|dict
(braket
l_int|3
)braket
dot
id|placeholder
op_assign
l_string|&quot;L&quot;
suffix:semicolon
id|dict
(braket
l_int|3
)braket
dot
id|value
op_assign
id|temp
(braket
l_int|3
)braket
suffix:semicolon
id|dict
(braket
l_int|4
)braket
dot
id|placeholder
op_assign
l_string|&quot;P&quot;
suffix:semicolon
id|dict
(braket
l_int|4
)braket
dot
id|value
op_assign
id|path_sq.buf
suffix:semicolon
id|dict
(braket
l_int|5
)braket
dot
id|placeholder
op_assign
l_int|NULL
suffix:semicolon
id|dict
(braket
l_int|5
)braket
dot
id|value
op_assign
l_int|NULL
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
comma
r_sizeof
(paren
id|temp
(braket
l_int|0
)braket
)paren
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
comma
r_sizeof
(paren
id|temp
(braket
l_int|1
)braket
)paren
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
comma
r_sizeof
(paren
id|temp
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|xsnprintf
c_func
(paren
id|temp
(braket
l_int|3
)braket
comma
r_sizeof
(paren
id|temp
(braket
l_int|3
)braket
)paren
comma
l_string|&quot;%d&quot;
comma
id|marker_size
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
l_int|0
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
id|RUN_USING_SHELL
)paren
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
id|strbuf_release
c_func
(paren
op_amp
id|path_sq
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
id|key
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
r_return
id|git_config_string
c_func
(paren
op_amp
id|default_ll_merge
comma
id|var
comma
id|value
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We are not interested in anything but &quot;merge.&lt;name&gt;.variable&quot;;&n;&t; * especially, we do not want to look at variables such as&n;&t; * &quot;merge.summary&quot;, &quot;merge.tool&quot;, and &quot;merge.verbosity&quot;.&n;&t; */
r_if
c_cond
(paren
id|parse_config_key
c_func
(paren
id|var
comma
l_string|&quot;merge&quot;
comma
op_amp
id|name
comma
op_amp
id|namelen
comma
op_amp
id|key
)paren
OL
l_int|0
op_logical_or
op_logical_neg
id|name
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Find existing one as we might be processing merge.&lt;name&gt;.var2&n;&t; * after seeing merge.&lt;name&gt;.var1.&n;&t; */
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;name&quot;
comma
id|key
)paren
)paren
r_return
id|git_config_string
c_func
(paren
op_amp
id|fn-&gt;description
comma
id|var
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;driver&quot;
comma
id|key
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
multiline_comment|/*&n;&t;&t; * merge.&lt;name&gt;.driver specifies the command line:&n;&t;&t; *&n;&t;&t; *&t;command-line&n;&t;&t; *&n;&t;&t; * The command-line will be interpolated with the following&n;&t;&t; * tokens and is given to the shell:&n;&t;&t; *&n;&t;&t; *    %O - temporary file name for the merge base.&n;&t;&t; *    %A - temporary file name for our version.&n;&t;&t; *    %B - temporary file name for the other branches&squot; version.&n;&t;&t; *    %L - conflict marker length&n;&t;&t; *    %P - the original path (safely quoted for the shell)&n;&t;&t; *&n;&t;&t; * The external merge driver should write the results in the&n;&t;&t; * file named by %A, and signal that it has done with zero exit&n;&t;&t; * status.&n;&t;&t; */
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
id|key
)paren
)paren
r_return
id|git_config_string
c_func
(paren
op_amp
id|fn-&gt;recursive
comma
id|var
comma
id|value
)paren
suffix:semicolon
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
r_int
id|git_path_check_merge
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|git_attr_check
id|check
(braket
l_int|2
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|check
(braket
l_int|0
)braket
dot
id|attr
)paren
(brace
id|check
(braket
l_int|0
)braket
dot
id|attr
op_assign
id|git_attr
c_func
(paren
l_string|&quot;merge&quot;
)paren
suffix:semicolon
id|check
(braket
l_int|1
)braket
dot
id|attr
op_assign
id|git_attr
c_func
(paren
l_string|&quot;conflict-marker-size&quot;
)paren
suffix:semicolon
)brace
r_return
id|git_check_attr
c_func
(paren
id|path
comma
l_int|2
comma
id|check
)paren
suffix:semicolon
)brace
DECL|function|normalize_file
r_static
r_void
id|normalize_file
c_func
(paren
id|mmfile_t
op_star
id|mm
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|strbuf
id|strbuf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|renormalize_buffer
c_func
(paren
id|path
comma
id|mm-&gt;ptr
comma
id|mm-&gt;size
comma
op_amp
id|strbuf
)paren
)paren
(brace
id|free
c_func
(paren
id|mm-&gt;ptr
)paren
suffix:semicolon
id|mm-&gt;size
op_assign
id|strbuf.len
suffix:semicolon
id|mm-&gt;ptr
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|strbuf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
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
r_const
r_char
op_star
id|ancestor_label
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
r_const
r_struct
id|ll_merge_options
op_star
id|opts
)paren
(brace
r_static
r_struct
id|git_attr_check
id|check
(braket
l_int|2
)braket
suffix:semicolon
r_static
r_const
r_struct
id|ll_merge_options
id|default_opts
suffix:semicolon
r_const
r_char
op_star
id|ll_driver_name
op_assign
l_int|NULL
suffix:semicolon
r_int
id|marker_size
op_assign
id|DEFAULT_CONFLICT_MARKER_SIZE
suffix:semicolon
r_const
r_struct
id|ll_merge_driver
op_star
id|driver
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts
)paren
id|opts
op_assign
op_amp
id|default_opts
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;renormalize
)paren
(brace
id|normalize_file
c_func
(paren
id|ancestor
comma
id|path
)paren
suffix:semicolon
id|normalize_file
c_func
(paren
id|ours
comma
id|path
)paren
suffix:semicolon
id|normalize_file
c_func
(paren
id|theirs
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|git_path_check_merge
c_func
(paren
id|path
comma
id|check
)paren
)paren
(brace
id|ll_driver_name
op_assign
id|check
(braket
l_int|0
)braket
dot
id|value
suffix:semicolon
r_if
c_cond
(paren
id|check
(braket
l_int|1
)braket
dot
id|value
)paren
(brace
id|marker_size
op_assign
id|atoi
c_func
(paren
id|check
(braket
l_int|1
)braket
dot
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|marker_size
op_le
l_int|0
)paren
id|marker_size
op_assign
id|DEFAULT_CONFLICT_MARKER_SIZE
suffix:semicolon
)brace
)brace
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
id|opts-&gt;virtual_ancestor
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
id|ancestor_label
comma
id|ours
comma
id|our_label
comma
id|theirs
comma
id|their_label
comma
id|opts
comma
id|marker_size
)paren
suffix:semicolon
)brace
DECL|function|ll_merge_marker_size
r_int
id|ll_merge_marker_size
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
id|check
suffix:semicolon
r_int
id|marker_size
op_assign
id|DEFAULT_CONFLICT_MARKER_SIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check.attr
)paren
id|check.attr
op_assign
id|git_attr
c_func
(paren
l_string|&quot;conflict-marker-size&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_check_attr
c_func
(paren
id|path
comma
l_int|1
comma
op_amp
id|check
)paren
op_logical_and
id|check.value
)paren
(brace
id|marker_size
op_assign
id|atoi
c_func
(paren
id|check.value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|marker_size
op_le
l_int|0
)paren
id|marker_size
op_assign
id|DEFAULT_CONFLICT_MARKER_SIZE
suffix:semicolon
)brace
r_return
id|marker_size
suffix:semicolon
)brace
eof
