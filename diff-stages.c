multiline_comment|/*&n; * Copyright (c) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|variable|diff_output_format
r_static
r_int
id|diff_output_format
op_assign
id|DIFF_FORMAT_HUMAN
suffix:semicolon
DECL|variable|detect_rename
r_static
r_int
id|detect_rename
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_setup_opt
r_static
r_int
id|diff_setup_opt
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_score_opt
r_static
r_int
id|diff_score_opt
op_assign
l_int|0
suffix:semicolon
DECL|variable|pickaxe
r_static
r_const
r_char
op_star
id|pickaxe
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pickaxe_opts
r_static
r_int
id|pickaxe_opts
op_assign
l_int|0
suffix:semicolon
DECL|variable|diff_break_opt
r_static
r_int
id|diff_break_opt
op_assign
l_int|1
suffix:semicolon
DECL|variable|orderfile
r_static
r_const
r_char
op_star
id|orderfile
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|diff_filter
r_static
r_const
r_char
op_star
id|diff_filter
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|diff_stages_usage
r_static
r_char
op_star
id|diff_stages_usage
op_assign
l_string|&quot;git-diff-stages [-p] [-r] [-z] [-M] [-C] [-R] [-S&lt;string&gt;] [-O&lt;orderfile&gt;] &lt;stage1&gt; &lt;stage2&gt; [&lt;path&gt;...]&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
)paren
(brace
r_int
id|stage1
comma
id|stage2
comma
id|i
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|ac
op_logical_and
id|av
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
r_const
r_char
op_star
id|arg
op_assign
id|av
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-r&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* as usual */
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-p&quot;
)paren
)paren
id|diff_output_format
op_assign
id|DIFF_FORMAT_PATCH
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-B&quot;
comma
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|diff_break_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
)paren
op_eq
l_int|1
)paren
id|usage
c_func
(paren
id|diff_stages_usage
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-M&quot;
comma
l_int|2
)paren
)paren
(brace
id|detect_rename
op_assign
id|DIFF_DETECT_RENAME
suffix:semicolon
r_if
c_cond
(paren
(paren
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
)paren
op_eq
l_int|1
)paren
id|usage
c_func
(paren
id|diff_stages_usage
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-C&quot;
comma
l_int|2
)paren
)paren
(brace
id|detect_rename
op_assign
id|DIFF_DETECT_COPY
suffix:semicolon
r_if
c_cond
(paren
(paren
id|diff_score_opt
op_assign
id|diff_scoreopt_parse
c_func
(paren
id|arg
)paren
)paren
op_eq
l_int|1
)paren
id|usage
c_func
(paren
id|diff_stages_usage
)paren
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
id|arg
comma
l_string|&quot;-z&quot;
)paren
)paren
id|diff_output_format
op_assign
id|DIFF_FORMAT_MACHINE
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-R&quot;
)paren
)paren
id|diff_setup_opt
op_or_assign
id|DIFF_SETUP_REVERSE
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-S&quot;
comma
l_int|2
)paren
)paren
id|pickaxe
op_assign
id|arg
op_plus
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;-O&quot;
comma
l_int|2
)paren
)paren
id|orderfile
op_assign
id|arg
op_plus
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--diff-filter=&quot;
comma
l_int|14
)paren
)paren
id|diff_filter
op_assign
id|arg
op_plus
l_int|14
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--pickaxe-all&quot;
)paren
)paren
id|pickaxe_opts
op_assign
id|DIFF_PICKAXE_ALL
suffix:semicolon
r_else
id|usage
c_func
(paren
id|diff_stages_usage
)paren
suffix:semicolon
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ac
OL
l_int|3
op_logical_or
id|sscanf
c_func
(paren
id|av
(braket
l_int|1
)braket
comma
l_string|&quot;%d&quot;
comma
op_amp
id|stage1
)paren
op_ne
l_int|1
op_logical_or
op_logical_neg
(paren
l_int|0
op_le
id|stage1
op_logical_and
id|stage1
op_le
l_int|3
)paren
op_logical_or
id|sscanf
c_func
(paren
id|av
(braket
l_int|2
)braket
comma
l_string|&quot;%d&quot;
comma
op_amp
id|stage2
)paren
op_ne
l_int|1
op_logical_or
op_logical_neg
(paren
l_int|0
op_le
id|stage2
op_logical_and
id|stage2
op_le
l_int|3
)paren
)paren
id|usage
c_func
(paren
id|diff_stages_usage
)paren
suffix:semicolon
id|av
op_add_assign
l_int|3
suffix:semicolon
multiline_comment|/* The rest from av[0] are for paths restriction. */
id|diff_setup
c_func
(paren
id|diff_setup_opt
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|active_nr
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
comma
op_star
id|stages
(braket
l_int|4
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
r_struct
id|cache_entry
op_star
id|one
comma
op_star
id|two
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|len
suffix:semicolon
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
id|len
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
id|name
op_assign
id|ce-&gt;name
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|stage
op_assign
id|ce_stage
c_func
(paren
id|ce
)paren
suffix:semicolon
id|stages
(braket
id|stage
)braket
op_assign
id|ce
suffix:semicolon
r_if
c_cond
(paren
id|active_nr
op_le
op_increment
id|i
)paren
r_break
suffix:semicolon
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
id|ce_namelen
c_func
(paren
id|ce
)paren
op_ne
id|len
op_logical_or
id|memcmp
c_func
(paren
id|name
comma
id|ce-&gt;name
comma
id|len
)paren
)paren
r_break
suffix:semicolon
)brace
id|one
op_assign
id|stages
(braket
id|stage1
)braket
suffix:semicolon
id|two
op_assign
id|stages
(braket
id|stage2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one
op_logical_and
op_logical_neg
id|two
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one
)paren
id|diff_addremove
c_func
(paren
l_char|&squot;+&squot;
comma
id|ntohl
c_func
(paren
id|two-&gt;ce_mode
)paren
comma
id|two-&gt;sha1
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|two
)paren
id|diff_addremove
c_func
(paren
l_char|&squot;-&squot;
comma
id|ntohl
c_func
(paren
id|one-&gt;ce_mode
)paren
comma
id|one-&gt;sha1
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|one-&gt;sha1
comma
id|two-&gt;sha1
comma
l_int|20
)paren
op_logical_or
(paren
id|one-&gt;ce_mode
op_ne
id|two-&gt;ce_mode
)paren
)paren
id|diff_change
c_func
(paren
id|ntohl
c_func
(paren
id|one-&gt;ce_mode
)paren
comma
id|ntohl
c_func
(paren
id|two-&gt;ce_mode
)paren
comma
id|one-&gt;sha1
comma
id|two-&gt;sha1
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|diffcore_std
c_func
(paren
id|av
comma
id|detect_rename
comma
id|diff_score_opt
comma
id|pickaxe
comma
id|pickaxe_opts
comma
id|diff_break_opt
comma
id|orderfile
comma
id|diff_filter
)paren
suffix:semicolon
id|diff_flush
c_func
(paren
id|diff_output_format
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
