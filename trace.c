multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) 2000-2002 Michael R. Elkins &lt;me@mutt.org&gt;&n; * Copyright (C) 2002-2004 Oswald Buddenhagen &lt;ossi@users.sf.net&gt;&n; * Copyright (C) 2004 Theodore Y. Ts&squot;o &lt;tytso@mit.edu&gt;&n; * Copyright (C) 2006 Mike McCormack&n; * Copyright (C) 2006 Christian Couder&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
multiline_comment|/* Get a trace file descriptor from &quot;key&quot; env variable. */
DECL|function|get_trace_fd
r_static
r_int
id|get_trace_fd
c_func
(paren
r_struct
id|trace_key
op_star
id|key
)paren
(brace
r_static
r_struct
id|trace_key
id|trace_default
op_assign
(brace
l_string|&quot;GIT_TRACE&quot;
)brace
suffix:semicolon
r_const
r_char
op_star
id|trace
suffix:semicolon
multiline_comment|/* use default &quot;GIT_TRACE&quot; if NULL */
r_if
c_cond
(paren
op_logical_neg
id|key
)paren
id|key
op_assign
op_amp
id|trace_default
suffix:semicolon
multiline_comment|/* don&squot;t open twice */
r_if
c_cond
(paren
id|key-&gt;initialized
)paren
r_return
id|key-&gt;fd
suffix:semicolon
id|trace
op_assign
id|getenv
c_func
(paren
id|key-&gt;key
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
id|key-&gt;fd
op_assign
l_int|0
suffix:semicolon
r_else
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
id|key-&gt;fd
op_assign
id|STDERR_FILENO
suffix:semicolon
r_else
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
id|key-&gt;fd
op_assign
id|atoi
c_func
(paren
id|trace
)paren
suffix:semicolon
r_else
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
id|key-&gt;fd
op_assign
id|STDERR_FILENO
suffix:semicolon
)brace
r_else
(brace
id|key-&gt;fd
op_assign
id|fd
suffix:semicolon
id|key-&gt;need_close
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;What does &squot;%s&squot; for %s mean?&bslash;n&quot;
l_string|&quot;If you want to trace into a file, then please set &quot;
l_string|&quot;%s to an absolute pathname (starting with /).&bslash;n&quot;
l_string|&quot;Defaulting to tracing on stderr...&bslash;n&quot;
comma
id|trace
comma
id|key-&gt;key
comma
id|key-&gt;key
)paren
suffix:semicolon
id|key-&gt;fd
op_assign
id|STDERR_FILENO
suffix:semicolon
)brace
id|key-&gt;initialized
op_assign
l_int|1
suffix:semicolon
r_return
id|key-&gt;fd
suffix:semicolon
)brace
DECL|function|trace_disable
r_void
id|trace_disable
c_func
(paren
r_struct
id|trace_key
op_star
id|key
)paren
(brace
r_if
c_cond
(paren
id|key-&gt;need_close
)paren
id|close
c_func
(paren
id|key-&gt;fd
)paren
suffix:semicolon
id|key-&gt;fd
op_assign
l_int|0
suffix:semicolon
id|key-&gt;initialized
op_assign
l_int|1
suffix:semicolon
id|key-&gt;need_close
op_assign
l_int|0
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
DECL|function|prepare_trace_line
r_static
r_int
id|prepare_trace_line
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_struct
id|trace_key
op_star
id|key
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
r_static
r_struct
id|trace_key
id|trace_bare
op_assign
id|TRACE_KEY_INIT
c_func
(paren
id|BARE
)paren
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_struct
id|tm
id|tm
suffix:semicolon
id|time_t
id|secs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trace_want
c_func
(paren
id|key
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|set_try_to_free_routine
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* is never reset */
multiline_comment|/* unit tests may want to disable additional trace output */
r_if
c_cond
(paren
id|trace_want
c_func
(paren
op_amp
id|trace_bare
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* print current timestamp */
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
id|secs
op_assign
id|tv.tv_sec
suffix:semicolon
id|localtime_r
c_func
(paren
op_amp
id|secs
comma
op_amp
id|tm
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;%02d:%02d:%02d.%06ld &quot;
comma
id|tm.tm_hour
comma
id|tm.tm_min
comma
id|tm.tm_sec
comma
(paren
r_int
)paren
id|tv.tv_usec
)paren
suffix:semicolon
macro_line|#ifdef HAVE_VARIADIC_MACROS
multiline_comment|/* print file:line */
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;%s:%d &quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
multiline_comment|/* align trace output (column 40 catches most files names in git) */
r_while
c_loop
(paren
id|buf-&gt;len
OL
l_int|40
)paren
id|strbuf_addch
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|trace_verbatim
r_void
id|trace_verbatim
c_func
(paren
r_struct
id|trace_key
op_star
id|key
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|trace_want
c_func
(paren
id|key
)paren
)paren
r_return
suffix:semicolon
id|write_or_whine_pipe
c_func
(paren
id|get_trace_fd
c_func
(paren
id|key
)paren
comma
id|buf
comma
id|len
comma
id|err_msg
)paren
suffix:semicolon
)brace
DECL|function|print_trace_line
r_static
r_void
id|print_trace_line
c_func
(paren
r_struct
id|trace_key
op_star
id|key
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
id|strbuf_complete_line
c_func
(paren
id|buf
)paren
suffix:semicolon
id|write_or_whine_pipe
c_func
(paren
id|get_trace_fd
c_func
(paren
id|key
)paren
comma
id|buf-&gt;buf
comma
id|buf-&gt;len
comma
id|err_msg
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|trace_vprintf_fl
r_static
r_void
id|trace_vprintf_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_struct
id|trace_key
op_star
id|key
comma
r_const
r_char
op_star
id|format
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
r_if
c_cond
(paren
op_logical_neg
id|prepare_trace_line
c_func
(paren
id|file
comma
id|line
comma
id|key
comma
op_amp
id|buf
)paren
)paren
r_return
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|buf
comma
id|format
comma
id|ap
)paren
suffix:semicolon
id|print_trace_line
c_func
(paren
id|key
comma
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|trace_argv_vprintf_fl
r_static
r_void
id|trace_argv_vprintf_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
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
id|format
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
r_if
c_cond
(paren
op_logical_neg
id|prepare_trace_line
c_func
(paren
id|file
comma
id|line
comma
l_int|NULL
comma
op_amp
id|buf
)paren
)paren
r_return
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|buf
comma
id|format
comma
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
id|print_trace_line
c_func
(paren
l_int|NULL
comma
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|trace_strbuf_fl
r_void
id|trace_strbuf_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_struct
id|trace_key
op_star
id|key
comma
r_const
r_struct
id|strbuf
op_star
id|data
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prepare_trace_line
c_func
(paren
id|file
comma
id|line
comma
id|key
comma
op_amp
id|buf
)paren
)paren
r_return
suffix:semicolon
id|strbuf_addbuf
c_func
(paren
op_amp
id|buf
comma
id|data
)paren
suffix:semicolon
id|print_trace_line
c_func
(paren
id|key
comma
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|variable|trace_perf_key
r_static
r_struct
id|trace_key
id|trace_perf_key
op_assign
id|TRACE_KEY_INIT
c_func
(paren
id|PERFORMANCE
)paren
suffix:semicolon
DECL|function|trace_performance_vprintf_fl
r_static
r_void
id|trace_performance_vprintf_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_uint64
id|nanos
comma
r_const
r_char
op_star
id|format
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
r_if
c_cond
(paren
op_logical_neg
id|prepare_trace_line
c_func
(paren
id|file
comma
id|line
comma
op_amp
id|trace_perf_key
comma
op_amp
id|buf
)paren
)paren
r_return
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;performance: %.9f s&quot;
comma
(paren
r_float
)paren
id|nanos
op_div
l_int|1000000000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|format
op_logical_and
op_star
id|format
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;: &quot;
)paren
suffix:semicolon
id|strbuf_vaddf
c_func
(paren
op_amp
id|buf
comma
id|format
comma
id|ap
)paren
suffix:semicolon
)brace
id|print_trace_line
c_func
(paren
op_amp
id|trace_perf_key
comma
op_amp
id|buf
)paren
suffix:semicolon
)brace
macro_line|#ifndef HAVE_VARIADIC_MACROS
DECL|function|trace_printf
r_void
id|trace_printf
c_func
(paren
r_const
r_char
op_star
id|format
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
id|format
)paren
suffix:semicolon
id|trace_vprintf_fl
c_func
(paren
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
id|format
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
DECL|function|trace_printf_key
r_void
id|trace_printf_key
c_func
(paren
r_struct
id|trace_key
op_star
id|key
comma
r_const
r_char
op_star
id|format
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
id|format
)paren
suffix:semicolon
id|trace_vprintf_fl
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|key
comma
id|format
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
id|format
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
id|format
)paren
suffix:semicolon
id|trace_argv_vprintf_fl
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|argv
comma
id|format
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
DECL|function|trace_strbuf
r_void
id|trace_strbuf
c_func
(paren
r_struct
id|trace_key
op_star
id|key
comma
r_const
r_struct
id|strbuf
op_star
id|data
)paren
(brace
id|trace_strbuf_fl
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|key
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|trace_performance
r_void
id|trace_performance
c_func
(paren
r_uint64
id|nanos
comma
r_const
r_char
op_star
id|format
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
id|format
)paren
suffix:semicolon
id|trace_performance_vprintf_fl
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|nanos
comma
id|format
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
DECL|function|trace_performance_since
r_void
id|trace_performance_since
c_func
(paren
r_uint64
id|start
comma
r_const
r_char
op_star
id|format
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
id|format
)paren
suffix:semicolon
id|trace_performance_vprintf_fl
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|getnanotime
c_func
(paren
)paren
id|start
comma
id|format
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
macro_line|#else
DECL|function|trace_printf_key_fl
r_void
id|trace_printf_key_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_struct
id|trace_key
op_star
id|key
comma
r_const
r_char
op_star
id|format
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
id|format
)paren
suffix:semicolon
id|trace_vprintf_fl
c_func
(paren
id|file
comma
id|line
comma
id|key
comma
id|format
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
DECL|function|trace_argv_printf_fl
r_void
id|trace_argv_printf_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
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
id|format
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
id|format
)paren
suffix:semicolon
id|trace_argv_vprintf_fl
c_func
(paren
id|file
comma
id|line
comma
id|argv
comma
id|format
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
DECL|function|trace_performance_fl
r_void
id|trace_performance_fl
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_uint64
id|nanos
comma
r_const
r_char
op_star
id|format
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
id|format
)paren
suffix:semicolon
id|trace_performance_vprintf_fl
c_func
(paren
id|file
comma
id|line
comma
id|nanos
comma
id|format
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
macro_line|#endif /* HAVE_VARIADIC_MACROS */
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
r_struct
id|strbuf
id|new_path
op_assign
id|STRBUF_INIT
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
id|strbuf_reset
c_func
(paren
op_amp
id|new_path
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|path
)paren
(brace
r_switch
c_cond
(paren
op_star
id|path
)paren
(brace
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
l_string|&quot;&bslash;&bslash;&bslash;&bslash;&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;n&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
l_string|&quot;&bslash;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;r&squot;
suffix:colon
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
l_string|&quot;&bslash;&bslash;r&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|strbuf_addch
c_func
(paren
op_amp
id|new_path
comma
op_star
id|path
)paren
suffix:semicolon
)brace
id|path
op_increment
suffix:semicolon
)brace
r_return
id|new_path.buf
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
r_static
r_struct
id|trace_key
id|key
op_assign
id|TRACE_KEY_INIT
c_func
(paren
id|SETUP
)paren
suffix:semicolon
r_const
r_char
op_star
id|git_work_tree
suffix:semicolon
r_char
op_star
id|cwd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trace_want
c_func
(paren
op_amp
id|key
)paren
)paren
r_return
suffix:semicolon
id|cwd
op_assign
id|xgetcwd
c_func
(paren
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
id|trace_printf_key
c_func
(paren
op_amp
id|key
comma
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
id|trace_printf_key
c_func
(paren
op_amp
id|key
comma
l_string|&quot;setup: git_common_dir: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|get_git_common_dir
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|trace_printf_key
c_func
(paren
op_amp
id|key
comma
l_string|&quot;setup: worktree: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|git_work_tree
)paren
)paren
suffix:semicolon
id|trace_printf_key
c_func
(paren
op_amp
id|key
comma
l_string|&quot;setup: cwd: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|cwd
)paren
)paren
suffix:semicolon
id|trace_printf_key
c_func
(paren
op_amp
id|key
comma
l_string|&quot;setup: prefix: %s&bslash;n&quot;
comma
id|quote_crnl
c_func
(paren
id|prefix
)paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|cwd
)paren
suffix:semicolon
)brace
DECL|function|trace_want
r_int
id|trace_want
c_func
(paren
r_struct
id|trace_key
op_star
id|key
)paren
(brace
r_return
op_logical_neg
op_logical_neg
id|get_trace_fd
c_func
(paren
id|key
)paren
suffix:semicolon
)brace
macro_line|#if defined(HAVE_CLOCK_GETTIME) &amp;&amp; defined(HAVE_CLOCK_MONOTONIC)
DECL|function|highres_nanos
r_static
r_inline
r_uint64
id|highres_nanos
c_func
(paren
r_void
)paren
(brace
r_struct
id|timespec
id|ts
suffix:semicolon
r_if
c_cond
(paren
id|clock_gettime
c_func
(paren
id|CLOCK_MONOTONIC
comma
op_amp
id|ts
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
r_uint64
)paren
id|ts.tv_sec
op_star
l_int|1000000000
op_plus
id|ts.tv_nsec
suffix:semicolon
)brace
macro_line|#elif defined (GIT_WINDOWS_NATIVE)
DECL|function|highres_nanos
r_static
r_inline
r_uint64
id|highres_nanos
c_func
(paren
r_void
)paren
(brace
r_static
r_uint64
id|high_ns
comma
id|scaled_low_ns
suffix:semicolon
r_static
r_int
id|scale
suffix:semicolon
id|LARGE_INTEGER
id|cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scale
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|QueryPerformanceFrequency
c_func
(paren
op_amp
id|cnt
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* high_ns = number of ns per cnt.HighPart */
id|high_ns
op_assign
(paren
l_int|1000000000LL
op_lshift
l_int|32
)paren
op_div
(paren
r_uint64
)paren
id|cnt.QuadPart
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Number of ns per cnt.LowPart is 10^9 / frequency (or&n;&t;&t; * high_ns &gt;&gt; 32). For maximum precision, we scale this factor&n;&t;&t; * so that it just fits within 32 bit (i.e. won&squot;t overflow if&n;&t;&t; * multiplied with cnt.LowPart).&n;&t;&t; */
id|scaled_low_ns
op_assign
id|high_ns
suffix:semicolon
id|scale
op_assign
l_int|32
suffix:semicolon
r_while
c_loop
(paren
id|scaled_low_ns
op_ge
l_int|0x100000000LL
)paren
(brace
id|scaled_low_ns
op_rshift_assign
l_int|1
suffix:semicolon
id|scale
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/* if QPF worked on initialization, we expect QPC to work as well */
id|QueryPerformanceCounter
c_func
(paren
op_amp
id|cnt
)paren
suffix:semicolon
r_return
(paren
id|high_ns
op_star
id|cnt.HighPart
)paren
op_plus
(paren
(paren
id|scaled_low_ns
op_star
id|cnt.LowPart
)paren
op_rshift
id|scale
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|highres_nanos
macro_line|# define highres_nanos() 0
macro_line|#endif
DECL|function|gettimeofday_nanos
r_static
r_inline
r_uint64
id|gettimeofday_nanos
c_func
(paren
r_void
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
r_return
(paren
r_uint64
)paren
id|tv.tv_sec
op_star
l_int|1000000000
op_plus
id|tv.tv_usec
op_star
l_int|1000
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns nanoseconds since the epoch (01/01/1970), for performance tracing&n; * (i.e. favoring high precision over wall clock time accuracy).&n; */
DECL|function|getnanotime
r_uint64
id|getnanotime
c_func
(paren
r_void
)paren
(brace
r_static
r_uint64
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
l_int|1
)paren
(brace
multiline_comment|/* initialization succeeded, return offset + high res time */
r_return
id|offset
op_plus
id|highres_nanos
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|offset
op_eq
l_int|1
)paren
(brace
multiline_comment|/* initialization failed, fall back to gettimeofday */
r_return
id|gettimeofday_nanos
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* initialize offset if high resolution timer works */
r_uint64
id|now
op_assign
id|gettimeofday_nanos
c_func
(paren
)paren
suffix:semicolon
r_uint64
id|highres
op_assign
id|highres_nanos
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|highres
)paren
id|offset
op_assign
id|now
id|highres
suffix:semicolon
r_else
id|offset
op_assign
l_int|1
suffix:semicolon
r_return
id|now
suffix:semicolon
)brace
)brace
DECL|variable|command_start_time
r_static
r_uint64
id|command_start_time
suffix:semicolon
DECL|variable|command_line
r_static
r_struct
id|strbuf
id|command_line
op_assign
id|STRBUF_INIT
suffix:semicolon
DECL|function|print_command_performance_atexit
r_static
r_void
id|print_command_performance_atexit
c_func
(paren
r_void
)paren
(brace
id|trace_performance_since
c_func
(paren
id|command_start_time
comma
l_string|&quot;git command:%s&quot;
comma
id|command_line.buf
)paren
suffix:semicolon
)brace
DECL|function|trace_command_performance
r_void
id|trace_command_performance
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|trace_want
c_func
(paren
op_amp
id|trace_perf_key
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|command_start_time
)paren
id|atexit
c_func
(paren
id|print_command_performance_atexit
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|command_line
)paren
suffix:semicolon
id|sq_quote_argv
c_func
(paren
op_amp
id|command_line
comma
id|argv
comma
l_int|0
)paren
suffix:semicolon
id|command_start_time
op_assign
id|getnanotime
c_func
(paren
)paren
suffix:semicolon
)brace
eof
