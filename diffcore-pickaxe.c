multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; * Copyright (C) 2010 Google Inc.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;xdiff-interface.h&quot;
macro_line|#include &quot;kwset.h&quot;
DECL|typedef|pickaxe_fn
r_typedef
r_int
(paren
op_star
id|pickaxe_fn
)paren
(paren
id|mmfile_t
op_star
id|one
comma
id|mmfile_t
op_star
id|two
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
)paren
suffix:semicolon
r_static
r_int
id|pickaxe_match
c_func
(paren
r_struct
id|diff_filepair
op_star
id|p
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
comma
id|pickaxe_fn
id|fn
)paren
suffix:semicolon
DECL|function|pickaxe
r_static
r_void
id|pickaxe
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
comma
id|pickaxe_fn
id|fn
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|diff_queue_struct
id|outq
suffix:semicolon
id|DIFF_QUEUE_CLEAR
c_func
(paren
op_amp
id|outq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;pickaxe_opts
op_amp
id|DIFF_PICKAXE_ALL
)paren
(brace
multiline_comment|/* Showing the whole changeset if needle exists */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pickaxe_match
c_func
(paren
id|p
comma
id|o
comma
id|regexp
comma
id|kws
comma
id|fn
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* do not munge the queue */
)brace
multiline_comment|/*&n;&t;&t; * Otherwise we will clear the whole queue by copying&n;&t;&t; * the empty outq at the end of this function, but&n;&t;&t; * first clear the current entries in the queue.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|diff_free_filepair
c_func
(paren
id|q-&gt;queue
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Showing only the filepairs that has the needle */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filepair
op_star
id|p
op_assign
id|q-&gt;queue
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pickaxe_match
c_func
(paren
id|p
comma
id|o
comma
id|regexp
comma
id|kws
comma
id|fn
)paren
)paren
id|diff_q
c_func
(paren
op_amp
id|outq
comma
id|p
)paren
suffix:semicolon
r_else
id|diff_free_filepair
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|q-&gt;queue
)paren
suffix:semicolon
op_star
id|q
op_assign
id|outq
suffix:semicolon
)brace
DECL|struct|diffgrep_cb
r_struct
id|diffgrep_cb
(brace
DECL|member|regexp
id|regex_t
op_star
id|regexp
suffix:semicolon
DECL|member|hit
r_int
id|hit
suffix:semicolon
)brace
suffix:semicolon
DECL|function|diffgrep_consume
r_static
r_void
id|diffgrep_consume
c_func
(paren
r_void
op_star
id|priv
comma
r_char
op_star
id|line
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|diffgrep_cb
op_star
id|data
op_assign
id|priv
suffix:semicolon
id|regmatch_t
id|regmatch
suffix:semicolon
r_int
id|hold
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_ne
l_char|&squot;+&squot;
op_logical_and
id|line
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;hit
)paren
multiline_comment|/*&n;&t;&t; * NEEDSWORK: we should have a way to terminate the&n;&t;&t; * caller early.&n;&t;&t; */
r_return
suffix:semicolon
multiline_comment|/* Yuck -- line ought to be &quot;const char *&quot;! */
id|hold
op_assign
id|line
(braket
id|len
)braket
suffix:semicolon
id|line
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|data-&gt;hit
op_assign
op_logical_neg
id|regexec
c_func
(paren
id|data-&gt;regexp
comma
id|line
op_plus
l_int|1
comma
l_int|1
comma
op_amp
id|regmatch
comma
l_int|0
)paren
suffix:semicolon
id|line
(braket
id|len
)braket
op_assign
id|hold
suffix:semicolon
)brace
DECL|function|diff_grep
r_static
r_int
id|diff_grep
c_func
(paren
id|mmfile_t
op_star
id|one
comma
id|mmfile_t
op_star
id|two
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
)paren
(brace
id|regmatch_t
id|regmatch
suffix:semicolon
r_struct
id|diffgrep_cb
id|ecbdata
suffix:semicolon
id|xpparam_t
id|xpp
suffix:semicolon
id|xdemitconf_t
id|xecfg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one
)paren
r_return
op_logical_neg
id|regexec
c_func
(paren
id|regexp
comma
id|two-&gt;ptr
comma
l_int|1
comma
op_amp
id|regmatch
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|two
)paren
r_return
op_logical_neg
id|regexec
c_func
(paren
id|regexp
comma
id|one-&gt;ptr
comma
l_int|1
comma
op_amp
id|regmatch
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We have both sides; need to run textual diff and see if&n;&t; * the pattern appears on added/deleted lines.&n;&t; */
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
id|memset
c_func
(paren
op_amp
id|xecfg
comma
l_int|0
comma
r_sizeof
(paren
id|xecfg
)paren
)paren
suffix:semicolon
id|ecbdata.regexp
op_assign
id|regexp
suffix:semicolon
id|ecbdata.hit
op_assign
l_int|0
suffix:semicolon
id|xecfg.ctxlen
op_assign
id|o-&gt;context
suffix:semicolon
id|xecfg.interhunkctxlen
op_assign
id|o-&gt;interhunkcontext
suffix:semicolon
id|xdi_diff_outf
c_func
(paren
id|one
comma
id|two
comma
id|diffgrep_consume
comma
op_amp
id|ecbdata
comma
op_amp
id|xpp
comma
op_amp
id|xecfg
)paren
suffix:semicolon
r_return
id|ecbdata.hit
suffix:semicolon
)brace
DECL|function|diffcore_pickaxe_grep
r_static
r_void
id|diffcore_pickaxe_grep
c_func
(paren
r_struct
id|diff_options
op_star
id|o
)paren
(brace
r_int
id|err
suffix:semicolon
id|regex_t
id|regex
suffix:semicolon
r_int
id|cflags
op_assign
id|REG_EXTENDED
op_or
id|REG_NEWLINE
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|o
comma
id|PICKAXE_IGNORE_CASE
)paren
)paren
id|cflags
op_or_assign
id|REG_ICASE
suffix:semicolon
id|err
op_assign
id|regcomp
c_func
(paren
op_amp
id|regex
comma
id|o-&gt;pickaxe
comma
id|cflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_char
id|errbuf
(braket
l_int|1024
)braket
suffix:semicolon
id|regerror
c_func
(paren
id|err
comma
op_amp
id|regex
comma
id|errbuf
comma
l_int|1024
)paren
suffix:semicolon
id|regfree
c_func
(paren
op_amp
id|regex
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid log-grep regex: %s&quot;
comma
id|errbuf
)paren
suffix:semicolon
)brace
id|pickaxe
c_func
(paren
op_amp
id|diff_queued_diff
comma
id|o
comma
op_amp
id|regex
comma
l_int|NULL
comma
id|diff_grep
)paren
suffix:semicolon
id|regfree
c_func
(paren
op_amp
id|regex
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|contains
r_static
r_int
r_int
id|contains
c_func
(paren
id|mmfile_t
op_star
id|mf
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
)paren
(brace
r_int
r_int
id|cnt
suffix:semicolon
r_int
r_int
id|sz
suffix:semicolon
r_const
r_char
op_star
id|data
suffix:semicolon
id|sz
op_assign
id|mf-&gt;size
suffix:semicolon
id|data
op_assign
id|mf-&gt;ptr
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|regexp
)paren
(brace
id|regmatch_t
id|regmatch
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
m_assert
(paren
id|data
(braket
id|sz
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|data
op_logical_and
op_logical_neg
id|regexec
c_func
(paren
id|regexp
comma
id|data
comma
l_int|1
comma
op_amp
id|regmatch
comma
id|flags
)paren
)paren
(brace
id|flags
op_or_assign
id|REG_NOTBOL
suffix:semicolon
id|data
op_add_assign
id|regmatch.rm_eo
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
op_logical_and
id|regmatch.rm_so
op_eq
id|regmatch.rm_eo
)paren
id|data
op_increment
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Classic exact string match */
r_while
c_loop
(paren
id|sz
)paren
(brace
r_struct
id|kwsmatch
id|kwsm
suffix:semicolon
r_int
id|offset
op_assign
id|kwsexec
c_func
(paren
id|kws
comma
id|data
comma
id|sz
comma
op_amp
id|kwsm
)paren
suffix:semicolon
r_const
r_char
op_star
id|found
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
l_int|1
)paren
r_break
suffix:semicolon
r_else
id|found
op_assign
id|data
op_plus
id|offset
suffix:semicolon
id|sz
op_sub_assign
id|found
id|data
op_plus
id|kwsm.size
(braket
l_int|0
)braket
suffix:semicolon
id|data
op_assign
id|found
op_plus
id|kwsm.size
(braket
l_int|0
)braket
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
DECL|function|has_changes
r_static
r_int
id|has_changes
c_func
(paren
id|mmfile_t
op_star
id|one
comma
id|mmfile_t
op_star
id|two
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|one
)paren
r_return
id|contains
c_func
(paren
id|two
comma
id|o
comma
id|regexp
comma
id|kws
)paren
op_ne
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|two
)paren
r_return
id|contains
c_func
(paren
id|one
comma
id|o
comma
id|regexp
comma
id|kws
)paren
op_ne
l_int|0
suffix:semicolon
r_return
id|contains
c_func
(paren
id|one
comma
id|o
comma
id|regexp
comma
id|kws
)paren
op_ne
id|contains
c_func
(paren
id|two
comma
id|o
comma
id|regexp
comma
id|kws
)paren
suffix:semicolon
)brace
DECL|function|pickaxe_match
r_static
r_int
id|pickaxe_match
c_func
(paren
r_struct
id|diff_filepair
op_star
id|p
comma
r_struct
id|diff_options
op_star
id|o
comma
id|regex_t
op_star
id|regexp
comma
id|kwset_t
id|kws
comma
id|pickaxe_fn
id|fn
)paren
(brace
r_struct
id|userdiff_driver
op_star
id|textconv_one
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|userdiff_driver
op_star
id|textconv_two
op_assign
l_int|NULL
suffix:semicolon
id|mmfile_t
id|mf1
comma
id|mf2
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o-&gt;pickaxe
(braket
l_int|0
)braket
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ignore unmerged */
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
op_logical_and
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DIFF_OPT_TST
c_func
(paren
id|o
comma
id|ALLOW_TEXTCONV
)paren
)paren
(brace
id|textconv_one
op_assign
id|get_textconv
c_func
(paren
id|p-&gt;one
)paren
suffix:semicolon
id|textconv_two
op_assign
id|get_textconv
c_func
(paren
id|p-&gt;two
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we have an unmodified pair, we know that the count will be the&n;&t; * same and don&squot;t even have to load the blobs. Unless textconv is in&n;&t; * play, _and_ we are using two different textconv filters (e.g.,&n;&t; * because a pair is an exact rename with different textconv attributes&n;&t; * for each side, which might generate different content).&n;&t; */
r_if
c_cond
(paren
id|textconv_one
op_eq
id|textconv_two
op_logical_and
id|diff_unmodified_pair
c_func
(paren
id|p
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|mf1.size
op_assign
id|fill_textconv
c_func
(paren
id|textconv_one
comma
id|p-&gt;one
comma
op_amp
id|mf1.ptr
)paren
suffix:semicolon
id|mf2.size
op_assign
id|fill_textconv
c_func
(paren
id|textconv_two
comma
id|p-&gt;two
comma
op_amp
id|mf2.ptr
)paren
suffix:semicolon
id|ret
op_assign
id|fn
c_func
(paren
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
ques
c_cond
op_amp
id|mf1
suffix:colon
l_int|NULL
comma
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
ques
c_cond
op_amp
id|mf2
suffix:colon
l_int|NULL
comma
id|o
comma
id|regexp
comma
id|kws
)paren
suffix:semicolon
r_if
c_cond
(paren
id|textconv_one
)paren
id|free
c_func
(paren
id|mf1.ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|textconv_two
)paren
id|free
c_func
(paren
id|mf2.ptr
)paren
suffix:semicolon
id|diff_free_filespec_data
c_func
(paren
id|p-&gt;one
)paren
suffix:semicolon
id|diff_free_filespec_data
c_func
(paren
id|p-&gt;two
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|diffcore_pickaxe_count
r_static
r_void
id|diffcore_pickaxe_count
c_func
(paren
r_struct
id|diff_options
op_star
id|o
)paren
(brace
r_const
r_char
op_star
id|needle
op_assign
id|o-&gt;pickaxe
suffix:semicolon
r_int
id|opts
op_assign
id|o-&gt;pickaxe_opts
suffix:semicolon
r_int
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|needle
)paren
suffix:semicolon
id|regex_t
id|regex
comma
op_star
id|regexp
op_assign
l_int|NULL
suffix:semicolon
id|kwset_t
id|kws
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|opts
op_amp
id|DIFF_PICKAXE_REGEX
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|regcomp
c_func
(paren
op_amp
id|regex
comma
id|needle
comma
id|REG_EXTENDED
op_or
id|REG_NEWLINE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
multiline_comment|/* The POSIX.2 people are surely sick */
r_char
id|errbuf
(braket
l_int|1024
)braket
suffix:semicolon
id|regerror
c_func
(paren
id|err
comma
op_amp
id|regex
comma
id|errbuf
comma
l_int|1024
)paren
suffix:semicolon
id|regfree
c_func
(paren
op_amp
id|regex
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;invalid pickaxe regex: %s&quot;
comma
id|errbuf
)paren
suffix:semicolon
)brace
id|regexp
op_assign
op_amp
id|regex
suffix:semicolon
)brace
r_else
(brace
id|kws
op_assign
id|kwsalloc
c_func
(paren
id|DIFF_OPT_TST
c_func
(paren
id|o
comma
id|PICKAXE_IGNORE_CASE
)paren
ques
c_cond
id|tolower_trans_tbl
suffix:colon
l_int|NULL
)paren
suffix:semicolon
id|kwsincr
c_func
(paren
id|kws
comma
id|needle
comma
id|len
)paren
suffix:semicolon
id|kwsprep
c_func
(paren
id|kws
)paren
suffix:semicolon
)brace
id|pickaxe
c_func
(paren
op_amp
id|diff_queued_diff
comma
id|o
comma
id|regexp
comma
id|kws
comma
id|has_changes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts
op_amp
id|DIFF_PICKAXE_REGEX
)paren
id|regfree
c_func
(paren
op_amp
id|regex
)paren
suffix:semicolon
r_else
id|kwsfree
c_func
(paren
id|kws
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|diffcore_pickaxe
r_void
id|diffcore_pickaxe
c_func
(paren
r_struct
id|diff_options
op_star
id|o
)paren
(brace
multiline_comment|/* Might want to warn when both S and G are on; I don&squot;t care... */
r_if
c_cond
(paren
id|o-&gt;pickaxe_opts
op_amp
id|DIFF_PICKAXE_KIND_G
)paren
id|diffcore_pickaxe_grep
c_func
(paren
id|o
)paren
suffix:semicolon
r_else
id|diffcore_pickaxe_count
c_func
(paren
id|o
)paren
suffix:semicolon
)brace
eof
