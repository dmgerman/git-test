macro_line|#include &quot;../git-compat-util.h&quot;
multiline_comment|/*&n; * The size parameter specifies the available space, i.e. includes&n; * the trailing NUL byte; but Windows&squot;s vsnprintf uses the entire&n; * buffer and avoids the trailing NUL, should the buffer be exactly&n; * big enough for the result. Defining SNPRINTF_SIZE_CORR to 1 will&n; * therefore remove 1 byte from the reported buffer size, so we&n; * always have room for a trailing NUL byte.&n; */
macro_line|#ifndef SNPRINTF_SIZE_CORR
macro_line|#if defined(WIN32) &amp;&amp; (!defined(__GNUC__) || __GNUC__ &lt; 4)
DECL|macro|SNPRINTF_SIZE_CORR
mdefine_line|#define SNPRINTF_SIZE_CORR 1
macro_line|#else
DECL|macro|SNPRINTF_SIZE_CORR
mdefine_line|#define SNPRINTF_SIZE_CORR 0
macro_line|#endif
macro_line|#endif
DECL|macro|vsnprintf
macro_line|#undef vsnprintf
DECL|function|git_vsnprintf
r_int
id|git_vsnprintf
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|maxsize
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
id|va_list
id|cp
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|maxsize
OG
l_int|0
)paren
(brace
id|va_copy
c_func
(paren
id|cp
comma
id|ap
)paren
suffix:semicolon
id|ret
op_assign
id|vsnprintf
c_func
(paren
id|str
comma
id|maxsize
op_minus
id|SNPRINTF_SIZE_CORR
comma
id|format
comma
id|cp
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|maxsize
op_minus
l_int|1
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Windows does not NUL-terminate if result fills buffer */
id|str
(braket
id|maxsize
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
r_return
id|ret
suffix:semicolon
id|s
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|maxsize
OL
l_int|128
)paren
id|maxsize
op_assign
l_int|128
suffix:semicolon
r_while
c_loop
(paren
id|ret
op_eq
l_int|1
)paren
(brace
id|maxsize
op_mul_assign
l_int|4
suffix:semicolon
id|str
op_assign
id|realloc
c_func
(paren
id|s
comma
id|maxsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
)paren
r_break
suffix:semicolon
id|s
op_assign
id|str
suffix:semicolon
id|va_copy
c_func
(paren
id|cp
comma
id|ap
)paren
suffix:semicolon
id|ret
op_assign
id|vsnprintf
c_func
(paren
id|str
comma
id|maxsize
op_minus
id|SNPRINTF_SIZE_CORR
comma
id|format
comma
id|cp
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|maxsize
op_minus
l_int|1
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|free
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|git_snprintf
r_int
id|git_snprintf
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|maxsize
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
r_int
id|ret
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|format
)paren
suffix:semicolon
id|ret
op_assign
id|git_vsnprintf
c_func
(paren
id|str
comma
id|maxsize
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
r_return
id|ret
suffix:semicolon
)brace
eof
