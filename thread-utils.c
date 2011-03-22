macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;thread-utils.h&quot;
macro_line|#if defined(hpux) || defined(__hpux) || defined(_hpux)
macro_line|#  include &lt;sys/pstat.h&gt;
macro_line|#endif
multiline_comment|/*&n; * By doing this in two steps we can at least get&n; * the function to be somewhat coherent, even&n; * with this disgusting nest of #ifdefs.&n; */
macro_line|#ifndef _SC_NPROCESSORS_ONLN
macro_line|#  ifdef _SC_NPROC_ONLN
DECL|macro|_SC_NPROCESSORS_ONLN
macro_line|#    define _SC_NPROCESSORS_ONLN _SC_NPROC_ONLN
macro_line|#  elif defined _SC_CRAY_NCPU
DECL|macro|_SC_NPROCESSORS_ONLN
macro_line|#    define _SC_NPROCESSORS_ONLN _SC_CRAY_NCPU
macro_line|#  endif
macro_line|#endif
DECL|function|online_cpus
r_int
id|online_cpus
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef _SC_NPROCESSORS_ONLN
r_int
id|ncpus
suffix:semicolon
macro_line|#endif
macro_line|#ifdef _WIN32
id|SYSTEM_INFO
id|info
suffix:semicolon
id|GetSystemInfo
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|info.dwNumberOfProcessors
OG
l_int|0
)paren
r_return
(paren
r_int
)paren
id|info.dwNumberOfProcessors
suffix:semicolon
macro_line|#elif defined(hpux) || defined(__hpux) || defined(_hpux)
r_struct
id|pst_dynamic
id|psd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pstat_getdynamic
c_func
(paren
op_amp
id|psd
comma
r_sizeof
(paren
id|psd
)paren
comma
(paren
r_int
)paren
l_int|1
comma
l_int|0
)paren
)paren
r_return
(paren
r_int
)paren
id|psd.psd_proc_cnt
suffix:semicolon
macro_line|#endif
macro_line|#ifdef _SC_NPROCESSORS_ONLN
r_if
c_cond
(paren
(paren
id|ncpus
op_assign
(paren
r_int
)paren
id|sysconf
c_func
(paren
id|_SC_NPROCESSORS_ONLN
)paren
)paren
OG
l_int|0
)paren
r_return
(paren
r_int
)paren
id|ncpus
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|init_recursive_mutex
r_int
id|init_recursive_mutex
c_func
(paren
id|pthread_mutex_t
op_star
id|m
)paren
(brace
id|pthread_mutexattr_t
id|a
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|pthread_mutexattr_init
c_func
(paren
op_amp
id|a
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|pthread_mutexattr_settype
c_func
(paren
op_amp
id|a
comma
id|PTHREAD_MUTEX_RECURSIVE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|pthread_mutex_init
c_func
(paren
id|m
comma
op_amp
id|a
)paren
suffix:semicolon
id|pthread_mutexattr_destroy
c_func
(paren
op_amp
id|a
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
