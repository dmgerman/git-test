multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
DECL|function|contains
r_static
r_int
r_int
id|contains
c_func
(paren
r_struct
id|diff_filespec
op_star
id|one
comma
r_const
r_char
op_star
id|needle
comma
r_int
r_int
id|len
comma
id|regex_t
op_star
id|regexp
)paren
(brace
r_int
r_int
id|cnt
suffix:semicolon
r_int
r_int
id|offset
comma
id|sz
suffix:semicolon
r_const
r_char
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
id|diff_populate_filespec
c_func
(paren
id|one
comma
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|sz
op_assign
id|one-&gt;size
suffix:semicolon
id|data
op_assign
id|one-&gt;data
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
id|regmatch.rm_so
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data
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
multiline_comment|/* Yes, I&squot;ve heard of strstr(), but the thing is *data may&n;&t;&t; * not be NUL terminated.  Sue me.&n;&t;&t; */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
op_plus
id|len
op_le
id|sz
suffix:semicolon
id|offset
op_increment
)paren
(brace
multiline_comment|/* we count non-overlapping occurrences of needle */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|needle
comma
id|data
op_plus
id|offset
comma
id|len
)paren
)paren
(brace
id|offset
op_add_assign
id|len
l_int|1
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
DECL|function|diffcore_pickaxe
r_void
id|diffcore_pickaxe
c_func
(paren
r_const
r_char
op_star
id|needle
comma
r_int
id|opts
)paren
(brace
r_struct
id|diff_queue_struct
op_star
id|q
op_assign
op_amp
id|diff_queued_diff
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
r_int
id|i
comma
id|has_changes
suffix:semicolon
id|regex_t
id|regex
comma
op_star
id|regexp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|diff_queue_struct
id|outq
suffix:semicolon
id|outq.queue
op_assign
l_int|NULL
suffix:semicolon
id|outq.nr
op_assign
id|outq.alloc
op_assign
l_int|0
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
r_if
c_cond
(paren
id|opts
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
id|has_changes
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|has_changes
op_logical_and
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
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* ignore unmerged */
multiline_comment|/* created */
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;two
comma
id|needle
comma
id|len
comma
id|regexp
)paren
)paren
id|has_changes
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
(brace
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;one
comma
id|needle
comma
id|len
comma
id|regexp
)paren
)paren
id|has_changes
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|diff_unmodified_pair
c_func
(paren
id|p
)paren
op_logical_and
id|contains
c_func
(paren
id|p-&gt;one
comma
id|needle
comma
id|len
comma
id|regexp
)paren
op_ne
id|contains
c_func
(paren
id|p-&gt;two
comma
id|needle
comma
id|len
comma
id|regexp
)paren
)paren
id|has_changes
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_changes
)paren
r_return
suffix:semicolon
multiline_comment|/* not munge the queue */
multiline_comment|/* otherwise we will clear the whole queue&n;&t;&t; * by copying the empty outq at the end of this&n;&t;&t; * function, but first clear the current entries&n;&t;&t; * in the queue.&n;&t;&t; */
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
id|has_changes
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;one
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
suffix:semicolon
multiline_comment|/* ignore unmerged */
multiline_comment|/* created */
r_else
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;two
comma
id|needle
comma
id|len
comma
id|regexp
)paren
)paren
id|has_changes
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|DIFF_FILE_VALID
c_func
(paren
id|p-&gt;two
)paren
)paren
(brace
r_if
c_cond
(paren
id|contains
c_func
(paren
id|p-&gt;one
comma
id|needle
comma
id|len
comma
id|regexp
)paren
)paren
id|has_changes
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|diff_unmodified_pair
c_func
(paren
id|p
)paren
op_logical_and
id|contains
c_func
(paren
id|p-&gt;one
comma
id|needle
comma
id|len
comma
id|regexp
)paren
op_ne
id|contains
c_func
(paren
id|p-&gt;two
comma
id|needle
comma
id|len
comma
id|regexp
)paren
)paren
id|has_changes
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|has_changes
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
r_if
c_cond
(paren
id|opts
op_amp
id|DIFF_PICKAXE_REGEX
)paren
(brace
id|regfree
c_func
(paren
op_amp
id|regex
)paren
suffix:semicolon
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
r_return
suffix:semicolon
)brace
eof
