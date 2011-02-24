multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) 2000-2002 Michael R. Elkins &lt;me@mutt.org&gt;&n; * Copyright (C) 2002-2004 Oswald Buddenhagen &lt;ossi@users.sf.net&gt;&n; * Copyright (C) 2004 Theodore Y. Ts&squot;o &lt;tytso@mit.edu&gt;&n; * Copyright (C) 2006 Mike McCormack&n; * Copyright (C) 2006 Christian Couder&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
multiline_comment|/* Get a trace file descriptor from GIT_TRACE env variable. */
DECL|function|get_trace_fd
r_static
r_int
id|get_trace_fd
c_func
(paren
r_int
op_star
id|need_close
)paren
(brace
r_char
op_star
id|trace
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_TRACE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trace
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|trace
comma
l_string|&quot;&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|trace
comma
l_string|&quot;0&quot;
)paren
op_logical_or
op_logical_neg
id|strcasecmp
c_func
(paren
id|trace
comma
l_string|&quot;false&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|trace
comma
l_string|&quot;1&quot;
)paren
op_logical_or
op_logical_neg
id|strcasecmp
c_func
(paren
id|trace
comma
l_string|&quot;true&quot;
)paren
)paren
r_return
id|STDERR_FILENO
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|trace
)paren
op_eq
l_int|1
op_logical_and
id|isdigit
c_func
(paren
op_star
id|trace
)paren
)paren
r_return
id|atoi
c_func
(paren
id|trace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_absolute_path
c_func
(paren
id|trace
)paren
)paren
(brace
r_int
id|fd
op_assign
id|open
c_func
(paren
id|trace
comma
id|O_WRONLY
op_or
id|O_APPEND
op_or
id|O_CREAT
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
l_int|1
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Could not open &squot;%s&squot; for tracing: %s&bslash;n&quot;
l_string|&quot;Defaulting to tracing on stderr...&bslash;n&quot;
comma
id|trace
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_return
id|STDERR_FILENO
suffix:semicolon
)brace
op_star
id|need_close
op_assign
l_int|1
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;What does &squot;%s&squot; for GIT_TRACE mean?&bslash;n&quot;
comma
id|trace
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;If you want to trace into a file, &quot;
l_string|&quot;then please set GIT_TRACE to an absolute pathname &quot;
l_string|&quot;(starting with /).&bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Defaulting to tracing on stderr...&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|STDERR_FILENO
suffix:semicolon
)brace
DECL|variable|err_msg
r_static
r_const
r_char
id|err_msg
(braket
)braket
op_assign
l_string|&quot;Could not trace into fd given by &quot;
l_string|&quot;GIT_TRACE environment variable&quot;
suffix:semicolon
DECL|function|trace_vprintf
r_void
id|trace_vprintf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|ap
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|fd
comma
id|need_close
op_assign
l_int|0
suffix:semicolon
id|fd
op_assign
id|get_trace_fd
c_func
(paren
op_amp
id|need_close
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fd
)paren
r_return
suffix:semicolon
id|set_try_to_free_routine
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* is never reset */
id|strbuf_vaddf
c_func
(paren
op_amp
id|buf
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|write_or_whine_pipe
c_func
(paren
id|fd
comma
id|buf.buf
comma
id|buf.len
comma
id|err_msg
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_close
)paren
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|trace_printf
r_void
id|trace_printf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|trace_vprintf
c_func
(paren
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|trace_argv_printf
r_void
id|trace_argv_printf
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
r_int
id|fd
comma
id|need_close
op_assign
l_int|0
suffix:semicolon
id|fd
op_assign
id|get_trace_fd
c_func
(paren
op_amp
id|need_close
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fd
)paren
r_return
suffix:semicolon
id|set_try_to_free_routine
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* is never reset */
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|buf
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|sq_quote_argv
c_func
(paren
op_amp
id|buf
comma
id|argv
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|write_or_whine_pipe
c_func
(paren
id|fd
comma
id|buf.buf
comma
id|buf.len
comma
id|err_msg
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_close
)paren
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|quote_crnl
r_static
r_const
r_char
op_star
id|quote_crnl
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_static
r_char
id|new_path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|p2
op_assign
id|path
suffix:semicolon
r_char
op_star
id|p1
op_assign
id|new_path
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
r_return
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p2
)paren
(brace
r_switch
c_cond
(paren
op_star
id|p2
)paren
(brace
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
op_star
id|p1
op_increment
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
op_star
id|p1
op_increment
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
op_star
id|p1
op_increment
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
op_star
id|p1
op_increment
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;r&squot;
suffix:colon
op_star
id|p1
op_increment
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
op_star
id|p1
op_increment
op_assign
l_char|&squot;r&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|p1
op_increment
op_assign
op_star
id|p2
suffix:semicolon
)brace
id|p2
op_increment
suffix:semicolon
)brace
op_star
id|p1
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|new_path
suffix:semicolon
)brace
multiline_comment|/* FIXME: move prefix to startup_info struct and get rid of this arg */
DECL|function|trace_repo_setup
r_void
id|trace_repo_setup
c_func
(paren
r_const
r_char
op_star
id|prefix
)paren
(brace
r_const
r_char
op_star
id|git_work_tree
suffix:semicolon
r_char
id|cwd
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
op_star
id|trace
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_TRACE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trace
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|trace
comma
l_string|&quot;&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|trace
comma
l_string|&quot;0&quot;
)paren
op_logical_or
op_logical_neg
id|strcasecmp
c_func
(paren
id|trace
comma
l_string|&quot;false&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|getcwd
c_func
(paren
id|cwd
comma
id|PATH_MAX
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to get current working directory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|git_work_tree
op_assign
id|get_git_work_tree
c_func
(paren
)paren
)paren
)paren
id|git_work_tree
op_assign
l_string|&quot;(null)&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefix
)paren
id|prefix
op_assign
l_string|&quot;(null)&quot;
suffix:semicolon
id|trace_printf
c_func
(paren
l_string|&quot;setup: git_dir: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|get_git_dir
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|trace_printf
c_func
(paren
l_string|&quot;setup: worktree: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|git_work_tree
)paren
)paren
suffix:semicolon
id|trace_printf
c_func
(paren
l_string|&quot;setup: cwd: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|cwd
)paren
)paren
suffix:semicolon
id|trace_printf
c_func
(paren
l_string|&quot;setup: prefix: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|prefix
)paren
)paren
suffix:semicolon
)brace
eof
