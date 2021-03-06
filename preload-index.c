multiline_comment|/*&n; * Copyright (C) 2008 Linus Torvalds&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pathspec.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#ifdef NO_PTHREADS
DECL|function|preload_index
r_static
r_void
id|preload_index
c_func
(paren
r_struct
id|index_state
op_star
id|index
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
)paren
(brace
suffix:semicolon
multiline_comment|/* nothing */
)brace
macro_line|#else
macro_line|#include &lt;pthread.h&gt;
multiline_comment|/*&n; * Mostly randomly chosen maximum thread counts: we&n; * cap the parallelism to 20 threads, and we want&n; * to have at least 500 lstat&squot;s per thread for it to&n; * be worth starting a thread.&n; */
DECL|macro|MAX_PARALLEL
mdefine_line|#define MAX_PARALLEL (20)
DECL|macro|THREAD_COST
mdefine_line|#define THREAD_COST (500)
DECL|struct|thread_data
r_struct
id|thread_data
(brace
DECL|member|pthread
id|pthread_t
id|pthread
suffix:semicolon
DECL|member|index
r_struct
id|index_state
op_star
id|index
suffix:semicolon
DECL|member|pathspec
r_struct
id|pathspec
id|pathspec
suffix:semicolon
DECL|member|offset
DECL|member|nr
r_int
id|offset
comma
id|nr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|preload_thread
r_static
r_void
op_star
id|preload_thread
c_func
(paren
r_void
op_star
id|_data
)paren
(brace
r_int
id|nr
suffix:semicolon
r_struct
id|thread_data
op_star
id|p
op_assign
id|_data
suffix:semicolon
r_struct
id|index_state
op_star
id|index
op_assign
id|p-&gt;index
suffix:semicolon
r_struct
id|cache_entry
op_star
op_star
id|cep
op_assign
id|index-&gt;cache
op_plus
id|p-&gt;offset
suffix:semicolon
r_struct
id|cache_def
id|cache
op_assign
id|CACHE_DEF_INIT
suffix:semicolon
id|nr
op_assign
id|p-&gt;nr
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_plus
id|p-&gt;offset
OG
id|index-&gt;cache_nr
)paren
id|nr
op_assign
id|index-&gt;cache_nr
id|p-&gt;offset
suffix:semicolon
r_do
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
op_star
id|cep
op_increment
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce_uptodate
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_path_match
c_func
(paren
id|ce
comma
op_amp
id|p-&gt;pathspec
comma
l_int|NULL
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|threaded_has_symlink_leading_path
c_func
(paren
op_amp
id|cache
comma
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ie_match_stat
c_func
(paren
id|index
comma
id|ce
comma
op_amp
id|st
comma
id|CE_MATCH_RACY_IS_DIRTY
)paren
)paren
r_continue
suffix:semicolon
id|ce_mark_uptodate
c_func
(paren
id|ce
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|nr
OG
l_int|0
)paren
suffix:semicolon
id|cache_def_clear
c_func
(paren
op_amp
id|cache
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|preload_index
r_static
r_void
id|preload_index
c_func
(paren
r_struct
id|index_state
op_star
id|index
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
)paren
(brace
r_int
id|threads
comma
id|i
comma
id|work
comma
id|offset
suffix:semicolon
r_struct
id|thread_data
id|data
(braket
id|MAX_PARALLEL
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|core_preload_index
)paren
r_return
suffix:semicolon
id|threads
op_assign
id|index-&gt;cache_nr
op_div
id|THREAD_COST
suffix:semicolon
r_if
c_cond
(paren
id|threads
OL
l_int|2
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|threads
OG
id|MAX_PARALLEL
)paren
id|threads
op_assign
id|MAX_PARALLEL
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|work
op_assign
id|DIV_ROUND_UP
c_func
(paren
id|index-&gt;cache_nr
comma
id|threads
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
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
id|threads
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|thread_data
op_star
id|p
op_assign
id|data
op_plus
id|i
suffix:semicolon
id|p-&gt;index
op_assign
id|index
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
)paren
id|copy_pathspec
c_func
(paren
op_amp
id|p-&gt;pathspec
comma
id|pathspec
)paren
suffix:semicolon
id|p-&gt;offset
op_assign
id|offset
suffix:semicolon
id|p-&gt;nr
op_assign
id|work
suffix:semicolon
id|offset
op_add_assign
id|work
suffix:semicolon
r_if
c_cond
(paren
id|pthread_create
c_func
(paren
op_amp
id|p-&gt;pthread
comma
l_int|NULL
comma
id|preload_thread
comma
id|p
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to create threaded lstat&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|threads
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|thread_data
op_star
id|p
op_assign
id|data
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|pthread_join
c_func
(paren
id|p-&gt;pthread
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to join threaded lstat&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|read_index_preload
r_int
id|read_index_preload
c_func
(paren
r_struct
id|index_state
op_star
id|index
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
)paren
(brace
r_int
id|retval
op_assign
id|read_index
c_func
(paren
id|index
)paren
suffix:semicolon
id|preload_index
c_func
(paren
id|index
comma
id|pathspec
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
