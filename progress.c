multiline_comment|/*&n; * Simple text-based progress display module for GIT&n; *&n; * Copyright (c) 2007 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;progress.h&quot;
DECL|macro|TP_IDX_MAX
mdefine_line|#define TP_IDX_MAX      8
DECL|struct|throughput
r_struct
id|throughput
(brace
DECL|member|prev_tv
r_struct
id|timeval
id|prev_tv
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|avg_bytes
r_int
r_int
id|avg_bytes
suffix:semicolon
DECL|member|last_bytes
r_int
r_int
id|last_bytes
(braket
id|TP_IDX_MAX
)braket
suffix:semicolon
DECL|member|avg_misecs
r_int
r_int
id|avg_misecs
suffix:semicolon
DECL|member|last_misecs
r_int
r_int
id|last_misecs
(braket
id|TP_IDX_MAX
)braket
suffix:semicolon
DECL|member|idx
r_int
r_int
id|idx
suffix:semicolon
DECL|member|display
r_char
id|display
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|progress
r_struct
id|progress
(brace
DECL|member|title
r_const
r_char
op_star
id|title
suffix:semicolon
DECL|member|last_value
r_int
id|last_value
suffix:semicolon
DECL|member|total
r_int
id|total
suffix:semicolon
DECL|member|last_percent
r_int
id|last_percent
suffix:semicolon
DECL|member|delay
r_int
id|delay
suffix:semicolon
DECL|member|delayed_percent_treshold
r_int
id|delayed_percent_treshold
suffix:semicolon
DECL|member|throughput
r_struct
id|throughput
op_star
id|throughput
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|progress_update
r_static
r_volatile
id|sig_atomic_t
id|progress_update
suffix:semicolon
DECL|function|progress_interval
r_static
r_void
id|progress_interval
c_func
(paren
r_int
id|signum
)paren
(brace
id|progress_update
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|set_progress_signal
r_static
r_void
id|set_progress_signal
c_func
(paren
r_void
)paren
(brace
r_struct
id|sigaction
id|sa
suffix:semicolon
r_struct
id|itimerval
id|v
suffix:semicolon
id|progress_update
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sa
comma
l_int|0
comma
r_sizeof
(paren
id|sa
)paren
)paren
suffix:semicolon
id|sa.sa_handler
op_assign
id|progress_interval
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|sa.sa_mask
)paren
suffix:semicolon
id|sa.sa_flags
op_assign
id|SA_RESTART
suffix:semicolon
id|sigaction
c_func
(paren
id|SIGALRM
comma
op_amp
id|sa
comma
l_int|NULL
)paren
suffix:semicolon
id|v.it_interval.tv_sec
op_assign
l_int|1
suffix:semicolon
id|v.it_interval.tv_usec
op_assign
l_int|0
suffix:semicolon
id|v.it_value
op_assign
id|v.it_interval
suffix:semicolon
id|setitimer
c_func
(paren
id|ITIMER_REAL
comma
op_amp
id|v
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|clear_progress_signal
r_static
r_void
id|clear_progress_signal
c_func
(paren
r_void
)paren
(brace
r_struct
id|itimerval
id|v
op_assign
(brace
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|setitimer
c_func
(paren
id|ITIMER_REAL
comma
op_amp
id|v
comma
l_int|NULL
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGALRM
comma
id|SIG_IGN
)paren
suffix:semicolon
id|progress_update
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|display
r_static
r_int
id|display
c_func
(paren
r_struct
id|progress
op_star
id|progress
comma
r_int
id|n
comma
r_int
id|done
)paren
(brace
r_char
op_star
id|eol
comma
op_star
id|tp
suffix:semicolon
r_if
c_cond
(paren
id|progress-&gt;delay
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|progress_update
op_logical_or
op_decrement
id|progress-&gt;delay
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|progress-&gt;total
)paren
(brace
r_int
id|percent
op_assign
id|n
op_star
l_int|100
op_div
id|progress-&gt;total
suffix:semicolon
r_if
c_cond
(paren
id|percent
OG
id|progress-&gt;delayed_percent_treshold
)paren
(brace
multiline_comment|/* inhibit this progress report entirely */
id|clear_progress_signal
c_func
(paren
)paren
suffix:semicolon
id|progress-&gt;delay
op_assign
l_int|1
suffix:semicolon
id|progress-&gt;total
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|progress-&gt;last_value
op_assign
id|n
suffix:semicolon
id|tp
op_assign
(paren
id|progress-&gt;throughput
)paren
ques
c_cond
id|progress-&gt;throughput-&gt;display
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
id|eol
op_assign
id|done
ques
c_cond
l_string|&quot;, done.   &bslash;n&quot;
suffix:colon
l_string|&quot;   &bslash;r&quot;
suffix:semicolon
r_if
c_cond
(paren
id|progress-&gt;total
)paren
(brace
r_int
id|percent
op_assign
id|n
op_star
l_int|100
op_div
id|progress-&gt;total
suffix:semicolon
r_if
c_cond
(paren
id|percent
op_ne
id|progress-&gt;last_percent
op_logical_or
id|progress_update
)paren
(brace
id|progress-&gt;last_percent
op_assign
id|percent
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %3u%% (%u/%u)%s%s&quot;
comma
id|progress-&gt;title
comma
id|percent
comma
id|n
comma
id|progress-&gt;total
comma
id|tp
comma
id|eol
)paren
suffix:semicolon
id|progress_update
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|progress_update
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %u%s%s&quot;
comma
id|progress-&gt;title
comma
id|n
comma
id|tp
comma
id|eol
)paren
suffix:semicolon
id|progress_update
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|display_throughput
r_void
id|display_throughput
c_func
(paren
r_struct
id|progress
op_star
id|progress
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|throughput
op_star
id|tp
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_int
r_int
id|misecs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|progress
)paren
r_return
suffix:semicolon
id|tp
op_assign
id|progress-&gt;throughput
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
r_if
c_cond
(paren
op_logical_neg
id|tp
)paren
(brace
id|progress-&gt;throughput
op_assign
id|tp
op_assign
id|calloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|tp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp
)paren
id|tp-&gt;prev_tv
op_assign
id|tv
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tp-&gt;count
op_add_assign
id|n
suffix:semicolon
multiline_comment|/*&n;&t; * We have x = bytes and y = microsecs.  We want z = KiB/s:&n;&t; *&n;&t; *&t;z = (x / 1024) / (y / 1000000)&n;&t; *&t;z = x / y * 1000000 / 1024&n;&t; *&t;z = x / (y * 1024 / 1000000)&n;&t; *&t;z = x / y&squot;&n;&t; *&n;&t; * To simplify things we&squot;ll keep track of misecs, or 1024th of a sec&n;&t; * obtained with:&n;&t; *&n;&t; *&t;y&squot; = y * 1024 / 1000000&n;&t; *&t;y&squot; = y / (1000000 / 1024)&n;&t; *&t;y&squot; = y / 977&n;&t; */
id|misecs
op_assign
(paren
id|tv.tv_sec
id|tp-&gt;prev_tv.tv_sec
)paren
op_star
l_int|1024
suffix:semicolon
id|misecs
op_add_assign
(paren
r_int
)paren
(paren
id|tv.tv_usec
id|tp-&gt;prev_tv.tv_usec
)paren
op_div
l_int|977
suffix:semicolon
r_if
c_cond
(paren
id|misecs
OG
l_int|512
)paren
(brace
id|tp-&gt;prev_tv
op_assign
id|tv
suffix:semicolon
id|tp-&gt;avg_bytes
op_add_assign
id|tp-&gt;count
suffix:semicolon
id|tp-&gt;avg_misecs
op_add_assign
id|misecs
suffix:semicolon
id|snprintf
c_func
(paren
id|tp-&gt;display
comma
r_sizeof
(paren
id|tp-&gt;display
)paren
comma
l_string|&quot;, %lu KiB/s&quot;
comma
id|tp-&gt;avg_bytes
op_div
id|tp-&gt;avg_misecs
)paren
suffix:semicolon
id|tp-&gt;avg_bytes
op_sub_assign
id|tp-&gt;last_bytes
(braket
id|tp-&gt;idx
)braket
suffix:semicolon
id|tp-&gt;avg_misecs
op_sub_assign
id|tp-&gt;last_misecs
(braket
id|tp-&gt;idx
)braket
suffix:semicolon
id|tp-&gt;last_bytes
(braket
id|tp-&gt;idx
)braket
op_assign
id|tp-&gt;count
suffix:semicolon
id|tp-&gt;last_misecs
(braket
id|tp-&gt;idx
)braket
op_assign
id|misecs
suffix:semicolon
id|tp-&gt;idx
op_assign
(paren
id|tp-&gt;idx
op_plus
l_int|1
)paren
op_mod
id|TP_IDX_MAX
suffix:semicolon
id|tp-&gt;count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|progress-&gt;last_value
op_ne
l_int|1
op_logical_and
id|progress_update
)paren
id|display
c_func
(paren
id|progress
comma
id|progress-&gt;last_value
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|display_progress
r_int
id|display_progress
c_func
(paren
r_struct
id|progress
op_star
id|progress
comma
r_int
id|n
)paren
(brace
r_return
id|progress
ques
c_cond
id|display
c_func
(paren
id|progress
comma
id|n
comma
l_int|0
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|start_progress_delay
r_struct
id|progress
op_star
id|start_progress_delay
c_func
(paren
r_const
r_char
op_star
id|title
comma
r_int
id|total
comma
r_int
id|percent_treshold
comma
r_int
id|delay
)paren
(brace
r_struct
id|progress
op_star
id|progress
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|progress
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|progress
)paren
(brace
multiline_comment|/* unlikely, but here&squot;s a good fallback */
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s...&bslash;n&quot;
comma
id|title
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|progress-&gt;title
op_assign
id|title
suffix:semicolon
id|progress-&gt;total
op_assign
id|total
suffix:semicolon
id|progress-&gt;last_value
op_assign
l_int|1
suffix:semicolon
id|progress-&gt;last_percent
op_assign
l_int|1
suffix:semicolon
id|progress-&gt;delayed_percent_treshold
op_assign
id|percent_treshold
suffix:semicolon
id|progress-&gt;delay
op_assign
id|delay
suffix:semicolon
id|progress-&gt;throughput
op_assign
l_int|NULL
suffix:semicolon
id|set_progress_signal
c_func
(paren
)paren
suffix:semicolon
r_return
id|progress
suffix:semicolon
)brace
DECL|function|start_progress
r_struct
id|progress
op_star
id|start_progress
c_func
(paren
r_const
r_char
op_star
id|title
comma
r_int
id|total
)paren
(brace
r_return
id|start_progress_delay
c_func
(paren
id|title
comma
id|total
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|stop_progress
r_void
id|stop_progress
c_func
(paren
r_struct
id|progress
op_star
op_star
id|p_progress
)paren
(brace
r_struct
id|progress
op_star
id|progress
op_assign
op_star
id|p_progress
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|progress
)paren
r_return
suffix:semicolon
op_star
id|p_progress
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|progress-&gt;last_value
op_ne
l_int|1
)paren
(brace
multiline_comment|/* Force the last update */
id|progress_update
op_assign
l_int|1
suffix:semicolon
id|display
c_func
(paren
id|progress
comma
id|progress-&gt;last_value
comma
l_int|1
)paren
suffix:semicolon
)brace
id|clear_progress_signal
c_func
(paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|progress-&gt;throughput
)paren
suffix:semicolon
id|free
c_func
(paren
id|progress
)paren
suffix:semicolon
)brace
eof
