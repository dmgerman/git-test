multiline_comment|/*&n; * Copyright (c) 1996-1999 by Internet Software Consortium.&n; *&n; * Permission to use, copy, modify, and distribute this software for any&n; * purpose with or without fee is hereby granted, provided that the above&n; * copyright notice and this permission notice appear in all copies.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot; AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS&n; * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES&n; * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE&n; * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL&n; * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR&n; * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS&n; * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS&n; * SOFTWARE.&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &quot;../git-compat-util.h&quot;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#ifndef NS_INADDRSZ
DECL|macro|NS_INADDRSZ
mdefine_line|#define NS_INADDRSZ&t;4
macro_line|#endif
macro_line|#ifndef NS_IN6ADDRSZ
DECL|macro|NS_IN6ADDRSZ
mdefine_line|#define NS_IN6ADDRSZ&t;16
macro_line|#endif
macro_line|#ifndef NS_INT16SZ
DECL|macro|NS_INT16SZ
mdefine_line|#define NS_INT16SZ&t;2
macro_line|#endif
multiline_comment|/*&n; * WARNING: Don&squot;t even consider trying to compile this on a system where&n; * sizeof(int) &lt; 4.  sizeof(int) &gt; 4 is fine; all the world&squot;s not a VAX.&n; */
multiline_comment|/* const char *&n; * inet_ntop4(src, dst, size)&n; *&t;format an IPv4 address&n; * return:&n; *&t;`dst&squot; (as a const)&n; * notes:&n; *&t;(1) uses no statics&n; *&t;(2) takes a u_char* not an in_addr as input&n; * author:&n; *&t;Paul Vixie, 1996.&n; */
r_static
r_const
r_char
op_star
DECL|function|inet_ntop4
id|inet_ntop4
c_func
(paren
r_const
id|u_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|size
)paren
(brace
r_static
r_const
r_char
id|fmt
(braket
)braket
op_assign
l_string|&quot;%u.%u.%u.%u&quot;
suffix:semicolon
r_char
id|tmp
(braket
r_sizeof
l_string|&quot;255.255.255.255&quot;
)braket
suffix:semicolon
r_int
id|nprinted
suffix:semicolon
id|nprinted
op_assign
id|snprintf
c_func
(paren
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
id|fmt
comma
id|src
(braket
l_int|0
)braket
comma
id|src
(braket
l_int|1
)braket
comma
id|src
(braket
l_int|2
)braket
comma
id|src
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nprinted
OL
l_int|0
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* we assume &quot;errno&quot; was set by &quot;snprintf()&quot; */
r_if
c_cond
(paren
(paren
r_int
)paren
id|nprinted
OG
id|size
)paren
(brace
id|errno
op_assign
id|ENOSPC
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|dst
comma
id|tmp
)paren
suffix:semicolon
r_return
(paren
id|dst
)paren
suffix:semicolon
)brace
macro_line|#ifndef NO_IPV6
multiline_comment|/* const char *&n; * inet_ntop6(src, dst, size)&n; *&t;convert IPv6 binary address into presentation (printable) format&n; * author:&n; *&t;Paul Vixie, 1996.&n; */
r_static
r_const
r_char
op_star
DECL|function|inet_ntop6
id|inet_ntop6
c_func
(paren
r_const
id|u_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|size
)paren
(brace
multiline_comment|/*&n;&t; * Note that int32_t and int16_t need only be &quot;at least&quot; large enough&n;&t; * to contain a value of the specified size.  On some systems, like&n;&t; * Crays, there is no such thing as an integer variable with 16 bits.&n;&t; * Keep this in mind if you think this function should have been coded&n;&t; * to use pointer overlays.  All the world&squot;s not a VAX.&n;&t; */
r_char
id|tmp
(braket
r_sizeof
l_string|&quot;ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255&quot;
)braket
comma
op_star
id|tp
suffix:semicolon
r_struct
(brace
r_int
id|base
comma
id|len
suffix:semicolon
)brace
id|best
comma
id|cur
suffix:semicolon
r_int
r_int
id|words
(braket
id|NS_IN6ADDRSZ
op_div
id|NS_INT16SZ
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Preprocess:&n;&t; *&t;Copy the input (bytewise) array into a wordwise array.&n;&t; *&t;Find the longest run of 0x00&squot;s in src[] for :: shorthanding.&n;&t; */
id|memset
c_func
(paren
id|words
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
id|words
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
id|NS_IN6ADDRSZ
suffix:semicolon
id|i
op_increment
)paren
id|words
(braket
id|i
op_div
l_int|2
)braket
op_or_assign
(paren
id|src
(braket
id|i
)braket
op_lshift
(paren
(paren
l_int|1
(paren
id|i
op_mod
l_int|2
)paren
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
id|best.base
op_assign
l_int|1
suffix:semicolon
id|cur.base
op_assign
l_int|1
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
(paren
id|NS_IN6ADDRSZ
op_div
id|NS_INT16SZ
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|words
(braket
id|i
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|cur.base
op_eq
l_int|1
)paren
id|cur.base
op_assign
id|i
comma
id|cur.len
op_assign
l_int|1
suffix:semicolon
r_else
id|cur.len
op_increment
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cur.base
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|best.base
op_eq
l_int|1
op_logical_or
id|cur.len
OG
id|best.len
)paren
id|best
op_assign
id|cur
suffix:semicolon
id|cur.base
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|cur.base
op_ne
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|best.base
op_eq
l_int|1
op_logical_or
id|cur.len
OG
id|best.len
)paren
id|best
op_assign
id|cur
suffix:semicolon
)brace
r_if
c_cond
(paren
id|best.base
op_ne
l_int|1
op_logical_and
id|best.len
OL
l_int|2
)paren
id|best.base
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Format the result.&n;&t; */
id|tp
op_assign
id|tmp
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
(paren
id|NS_IN6ADDRSZ
op_div
id|NS_INT16SZ
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Are we inside the best run of 0x00&squot;s? */
r_if
c_cond
(paren
id|best.base
op_ne
l_int|1
op_logical_and
id|i
op_ge
id|best.base
op_logical_and
id|i
OL
(paren
id|best.base
op_plus
id|best.len
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|best.base
)paren
op_star
id|tp
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Are we following an initial run of 0x00s or any real hex? */
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
op_star
id|tp
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
multiline_comment|/* Is this address an encapsulated IPv4? */
r_if
c_cond
(paren
id|i
op_eq
l_int|6
op_logical_and
id|best.base
op_eq
l_int|0
op_logical_and
(paren
id|best.len
op_eq
l_int|6
op_logical_or
(paren
id|best.len
op_eq
l_int|5
op_logical_and
id|words
(braket
l_int|5
)braket
op_eq
l_int|0xffff
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inet_ntop4
c_func
(paren
id|src
op_plus
l_int|12
comma
id|tp
comma
r_sizeof
id|tmp
(paren
id|tp
id|tmp
)paren
)paren
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
id|tp
op_add_assign
id|strlen
c_func
(paren
id|tp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tp
op_add_assign
id|snprintf
c_func
(paren
id|tp
comma
r_sizeof
id|tmp
(paren
id|tp
id|tmp
)paren
comma
l_string|&quot;%x&quot;
comma
id|words
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Was it a trailing run of 0x00&squot;s? */
r_if
c_cond
(paren
id|best.base
op_ne
l_int|1
op_logical_and
(paren
id|best.base
op_plus
id|best.len
)paren
op_eq
(paren
id|NS_IN6ADDRSZ
op_div
id|NS_INT16SZ
)paren
)paren
op_star
id|tp
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
op_star
id|tp
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/*&n;&t; * Check for overflow, copy, and we&squot;re done.&n;&t; */
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|tp
id|tmp
)paren
OG
id|size
)paren
(brace
id|errno
op_assign
id|ENOSPC
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|dst
comma
id|tmp
)paren
suffix:semicolon
r_return
(paren
id|dst
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* char *&n; * inet_ntop(af, src, dst, size)&n; *&t;convert a network format address to presentation format.&n; * return:&n; *&t;pointer to presentation format address (`dst&squot;), or NULL (see errno).&n; * author:&n; *&t;Paul Vixie, 1996.&n; */
r_const
r_char
op_star
DECL|function|inet_ntop
id|inet_ntop
c_func
(paren
r_int
id|af
comma
r_const
r_void
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|af
)paren
(brace
r_case
id|AF_INET
suffix:colon
r_return
(paren
id|inet_ntop4
c_func
(paren
id|src
comma
id|dst
comma
id|size
)paren
)paren
suffix:semicolon
macro_line|#ifndef NO_IPV6
r_case
id|AF_INET6
suffix:colon
r_return
(paren
id|inet_ntop6
c_func
(paren
id|src
comma
id|dst
comma
id|size
)paren
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|errno
op_assign
id|EAFNOSUPPORT
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* NOTREACHED */
)brace
eof
