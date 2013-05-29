multiline_comment|/*&n; * Copyright (C) 2009 Andrzej K. Haczewski &lt;ahaczewski@gmail.com&gt;&n; *&n; * DISCLAIMER: The implementation is Git-specific, it is subset of original&n; * Pthreads API, without lots of other features that Git doesn&squot;t use.&n; * Git also makes sure that the passed arguments are valid, so there&squot;s&n; * no need for double-checking.&n; */
macro_line|#include &quot;../../git-compat-util.h&quot;
macro_line|#include &quot;pthread.h&quot;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;limits.h&gt;
DECL|function|win32_start_routine
r_static
r_int
id|__stdcall
id|win32_start_routine
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|pthread_t
op_star
id|thread
op_assign
id|arg
suffix:semicolon
id|thread-&gt;tid
op_assign
id|GetCurrentThreadId
c_func
(paren
)paren
suffix:semicolon
id|thread-&gt;arg
op_assign
id|thread
op_member_access_from_pointer
id|start_routine
c_func
(paren
id|thread-&gt;arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pthread_create
r_int
id|pthread_create
c_func
(paren
id|pthread_t
op_star
id|thread
comma
r_const
r_void
op_star
id|unused
comma
r_void
op_star
(paren
op_star
id|start_routine
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
)paren
(brace
id|thread-&gt;arg
op_assign
id|arg
suffix:semicolon
id|thread-&gt;start_routine
op_assign
id|start_routine
suffix:semicolon
id|thread-&gt;handle
op_assign
(paren
id|HANDLE
)paren
id|_beginthreadex
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|win32_start_routine
comma
id|thread
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|thread-&gt;handle
)paren
r_return
id|errno
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|win32_pthread_join
r_int
id|win32_pthread_join
c_func
(paren
id|pthread_t
op_star
id|thread
comma
r_void
op_star
op_star
id|value_ptr
)paren
(brace
id|DWORD
id|result
op_assign
id|WaitForSingleObject
c_func
(paren
id|thread-&gt;handle
comma
id|INFINITE
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|result
)paren
(brace
r_case
id|WAIT_OBJECT_0
suffix:colon
r_if
c_cond
(paren
id|value_ptr
)paren
op_star
id|value_ptr
op_assign
id|thread-&gt;arg
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|WAIT_ABANDONED
suffix:colon
r_return
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
id|err_win_to_posix
c_func
(paren
id|GetLastError
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|pthread_self
id|pthread_t
id|pthread_self
c_func
(paren
r_void
)paren
(brace
id|pthread_t
id|t
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
id|t.tid
op_assign
id|GetCurrentThreadId
c_func
(paren
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|function|pthread_cond_init
r_int
id|pthread_cond_init
c_func
(paren
id|pthread_cond_t
op_star
id|cond
comma
r_const
r_void
op_star
id|unused
)paren
(brace
id|cond-&gt;waiters
op_assign
l_int|0
suffix:semicolon
id|cond-&gt;was_broadcast
op_assign
l_int|0
suffix:semicolon
id|InitializeCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
id|cond-&gt;sema
op_assign
id|CreateSemaphore
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|LONG_MAX
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cond-&gt;sema
)paren
id|die
c_func
(paren
l_string|&quot;CreateSemaphore() failed&quot;
)paren
suffix:semicolon
id|cond-&gt;continue_broadcast
op_assign
id|CreateEvent
c_func
(paren
l_int|NULL
comma
multiline_comment|/* security */
id|FALSE
comma
multiline_comment|/* auto-reset */
id|FALSE
comma
multiline_comment|/* not signaled */
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* name */
r_if
c_cond
(paren
op_logical_neg
id|cond-&gt;continue_broadcast
)paren
id|die
c_func
(paren
l_string|&quot;CreateEvent() failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pthread_cond_destroy
r_int
id|pthread_cond_destroy
c_func
(paren
id|pthread_cond_t
op_star
id|cond
)paren
(brace
id|CloseHandle
c_func
(paren
id|cond-&gt;sema
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|cond-&gt;continue_broadcast
)paren
suffix:semicolon
id|DeleteCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pthread_cond_wait
r_int
id|pthread_cond_wait
c_func
(paren
id|pthread_cond_t
op_star
id|cond
comma
id|CRITICAL_SECTION
op_star
id|mutex
)paren
(brace
r_int
id|last_waiter
suffix:semicolon
id|EnterCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
id|cond-&gt;waiters
op_increment
suffix:semicolon
id|LeaveCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unlock external mutex and wait for signal.&n;&t; * NOTE: we&squot;ve held mutex locked long enough to increment&n;&t; * waiters count above, so there&squot;s no problem with&n;&t; * leaving mutex unlocked before we wait on semaphore.&n;&t; */
id|LeaveCriticalSection
c_func
(paren
id|mutex
)paren
suffix:semicolon
multiline_comment|/* let&squot;s wait - ignore return value */
id|WaitForSingleObject
c_func
(paren
id|cond-&gt;sema
comma
id|INFINITE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Decrease waiters count. If we are the last waiter, then we must&n;&t; * notify the broadcasting thread that it can continue.&n;&t; * But if we continued due to cond_signal, we do not have to do that&n;&t; * because the signaling thread knows that only one waiter continued.&n;&t; */
id|EnterCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
id|cond-&gt;waiters
op_decrement
suffix:semicolon
id|last_waiter
op_assign
id|cond-&gt;was_broadcast
op_logical_and
id|cond-&gt;waiters
op_eq
l_int|0
suffix:semicolon
id|LeaveCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_waiter
)paren
(brace
multiline_comment|/*&n;&t;&t; * cond_broadcast was issued while mutex was held. This means&n;&t;&t; * that all other waiters have continued, but are contending&n;&t;&t; * for the mutex at the end of this function because the&n;&t;&t; * broadcasting thread did not leave cond_broadcast, yet.&n;&t;&t; * (This is so that it can be sure that each waiter has&n;&t;&t; * consumed exactly one slice of the semaphor.)&n;&t;&t; * The last waiter must tell the broadcasting thread that it&n;&t;&t; * can go on.&n;&t;&t; */
id|SetEvent
c_func
(paren
id|cond-&gt;continue_broadcast
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now we go on to contend with all other waiters for&n;&t;&t; * the mutex. Auf in den Kampf!&n;&t;&t; */
)brace
multiline_comment|/* lock external mutex again */
id|EnterCriticalSection
c_func
(paren
id|mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * IMPORTANT: This implementation requires that pthread_cond_signal&n; * is called while the mutex is held that is used in the corresponding&n; * pthread_cond_wait calls!&n; */
DECL|function|pthread_cond_signal
r_int
id|pthread_cond_signal
c_func
(paren
id|pthread_cond_t
op_star
id|cond
)paren
(brace
r_int
id|have_waiters
suffix:semicolon
id|EnterCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
id|have_waiters
op_assign
id|cond-&gt;waiters
OG
l_int|0
suffix:semicolon
id|LeaveCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Signal only when there are waiters&n;&t; */
r_if
c_cond
(paren
id|have_waiters
)paren
r_return
id|ReleaseSemaphore
c_func
(paren
id|cond-&gt;sema
comma
l_int|1
comma
l_int|NULL
)paren
ques
c_cond
l_int|0
suffix:colon
id|err_win_to_posix
c_func
(paren
id|GetLastError
c_func
(paren
)paren
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * DOUBLY IMPORTANT: This implementation requires that pthread_cond_broadcast&n; * is called while the mutex is held that is used in the corresponding&n; * pthread_cond_wait calls!&n; */
DECL|function|pthread_cond_broadcast
r_int
id|pthread_cond_broadcast
c_func
(paren
id|pthread_cond_t
op_star
id|cond
)paren
(brace
id|EnterCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cond-&gt;was_broadcast
op_assign
id|cond-&gt;waiters
OG
l_int|0
)paren
)paren
(brace
multiline_comment|/* wake up all waiters */
id|ReleaseSemaphore
c_func
(paren
id|cond-&gt;sema
comma
id|cond-&gt;waiters
comma
l_int|NULL
)paren
suffix:semicolon
id|LeaveCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * At this point all waiters continue. Each one takes its&n;&t;&t; * slice of the semaphor. Now it&squot;s our turn to wait: Since&n;&t;&t; * the external mutex is held, no thread can leave cond_wait,&n;&t;&t; * yet. For this reason, we can be sure that no thread gets&n;&t;&t; * a chance to eat *more* than one slice. OTOH, it means&n;&t;&t; * that the last waiter must send us a wake-up.&n;&t;&t; */
id|WaitForSingleObject
c_func
(paren
id|cond-&gt;continue_broadcast
comma
id|INFINITE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Since the external mutex is held, no thread can enter&n;&t;&t; * cond_wait, and, hence, it is safe to reset this flag&n;&t;&t; * without cond-&gt;waiters_lock held.&n;&t;&t; */
id|cond-&gt;was_broadcast
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|LeaveCriticalSection
c_func
(paren
op_amp
id|cond-&gt;waiters_lock
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
