multiline_comment|/*&n; * test-revision-walking.c: test revision walking API.&n; *&n; * (C) 2012 Heiko Voigt &lt;hvoigt@hvoigt.net&gt;&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
DECL|function|print_commit
r_static
r_void
id|print_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|pretty_print_context
id|ctx
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|ctx.date_mode.type
op_assign
id|DATE_NORMAL
suffix:semicolon
id|format_commit_message
c_func
(paren
id|commit
comma
l_string|&quot; %m %s&quot;
comma
op_amp
id|sb
comma
op_amp
id|ctx
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sb.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
DECL|function|run_revision_walk
r_static
r_int
id|run_revision_walk
c_func
(paren
r_void
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;--all&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|argc
op_assign
id|ARRAY_SIZE
c_func
(paren
id|argv
)paren
l_int|1
suffix:semicolon
r_int
id|got_revision
op_assign
l_int|0
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
op_amp
id|rev
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
op_amp
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|print_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
id|got_revision
op_assign
l_int|1
suffix:semicolon
)brace
id|reset_revision_walk
c_func
(paren
)paren
suffix:semicolon
r_return
id|got_revision
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
r_char
op_star
op_star
id|argv
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
r_return
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
l_string|&quot;run-twice&quot;
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;1st&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|run_revision_walk
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;2nd&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|run_revision_walk
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;check usage&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
