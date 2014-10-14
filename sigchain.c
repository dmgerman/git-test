macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;sigchain.h&quot;
DECL|macro|SIGCHAIN_MAX_SIGNALS
mdefine_line|#define SIGCHAIN_MAX_SIGNALS 32
DECL|struct|sigchain_signal
r_struct
id|sigchain_signal
(brace
DECL|member|old
id|sigchain_fun
op_star
id|old
suffix:semicolon
DECL|member|n
r_int
id|n
suffix:semicolon
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|signals
r_static
r_struct
id|sigchain_signal
id|signals
(braket
id|SIGCHAIN_MAX_SIGNALS
)braket
suffix:semicolon
DECL|function|check_signum
r_static
r_void
id|check_signum
c_func
(paren
r_int
id|sig
)paren
(brace
r_if
c_cond
(paren
id|sig
OL
l_int|1
op_logical_or
id|sig
op_ge
id|SIGCHAIN_MAX_SIGNALS
)paren
id|die
c_func
(paren
l_string|&quot;BUG: signal out of range: %d&quot;
comma
id|sig
)paren
suffix:semicolon
)brace
DECL|function|sigchain_push
r_int
id|sigchain_push
c_func
(paren
r_int
id|sig
comma
id|sigchain_fun
id|f
)paren
(brace
r_struct
id|sigchain_signal
op_star
id|s
op_assign
id|signals
op_plus
id|sig
suffix:semicolon
id|check_signum
c_func
(paren
id|sig
)paren
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|s-&gt;old
comma
id|s-&gt;n
op_plus
l_int|1
comma
id|s-&gt;alloc
)paren
suffix:semicolon
id|s-&gt;old
(braket
id|s-&gt;n
)braket
op_assign
id|signal
c_func
(paren
id|sig
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;old
(braket
id|s-&gt;n
)braket
op_eq
id|SIG_ERR
)paren
r_return
l_int|1
suffix:semicolon
id|s-&gt;n
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sigchain_pop
r_int
id|sigchain_pop
c_func
(paren
r_int
id|sig
)paren
(brace
r_struct
id|sigchain_signal
op_star
id|s
op_assign
id|signals
op_plus
id|sig
suffix:semicolon
id|check_signum
c_func
(paren
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;n
OL
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|signal
c_func
(paren
id|sig
comma
id|s-&gt;old
(braket
id|s-&gt;n
l_int|1
)braket
)paren
op_eq
id|SIG_ERR
)paren
r_return
l_int|1
suffix:semicolon
id|s-&gt;n
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sigchain_push_common
r_void
id|sigchain_push_common
c_func
(paren
id|sigchain_fun
id|f
)paren
(brace
id|sigchain_push
c_func
(paren
id|SIGINT
comma
id|f
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGHUP
comma
id|f
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGTERM
comma
id|f
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGQUIT
comma
id|f
)paren
suffix:semicolon
id|sigchain_push
c_func
(paren
id|SIGPIPE
comma
id|f
)paren
suffix:semicolon
)brace
eof
