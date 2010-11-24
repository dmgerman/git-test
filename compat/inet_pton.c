multiline_comment|/*&n; * Copyright (C) 1996-2001  Internet Software Consortium.&n; *&n; * Permission to use, copy, modify, and distribute this software for any&n; * purpose with or without fee is hereby granted, provided that the above&n; * copyright notice and this permission notice appear in all copies.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot; AND INTERNET SOFTWARE CONSORTIUM&n; * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL&n; * INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,&n; * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING&n; * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,&n; * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION&n; * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &quot;../git-compat-util.h&quot;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#ifndef NS_INT16SZ
DECL|macro|NS_INT16SZ
mdefine_line|#define NS_INT16SZ       2
macro_line|#endif
macro_line|#ifndef NS_INADDRSZ
DECL|macro|NS_INADDRSZ
mdefine_line|#define NS_INADDRSZ      4
macro_line|#endif
macro_line|#ifndef NS_IN6ADDRSZ
DECL|macro|NS_IN6ADDRSZ
mdefine_line|#define NS_IN6ADDRSZ    16
macro_line|#endif
multiline_comment|/*&n; * WARNING: Don&squot;t even consider trying to compile this on a system where&n; * sizeof(int) &lt; 4.  sizeof(int) &gt; 4 is fine; all the world&squot;s not a VAX.&n; */
r_static
r_int
id|inet_pton4
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_int
r_char
op_star
id|dst
)paren
suffix:semicolon
macro_line|#ifndef NO_IPV6
r_static
r_int
id|inet_pton6
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_int
r_char
op_star
id|dst
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* int&n; * inet_pton4(src, dst)&n; *      like inet_aton() but without all the hexadecimal and shorthand.&n; * return:&n; *      1 if `src&squot; is a valid dotted quad, else 0.&n; * notice:&n; *      does not touch `dst&squot; unless it&squot;s returning 1.&n; * author:&n; *      Paul Vixie, 1996.&n; */
r_static
r_int
DECL|function|inet_pton4
id|inet_pton4
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_int
r_char
op_star
id|dst
)paren
(brace
r_static
r_const
r_char
id|digits
(braket
)braket
op_assign
l_string|&quot;0123456789&quot;
suffix:semicolon
r_int
id|saw_digit
comma
id|octets
comma
id|ch
suffix:semicolon
r_int
r_char
id|tmp
(braket
id|NS_INADDRSZ
)braket
comma
op_star
id|tp
suffix:semicolon
id|saw_digit
op_assign
l_int|0
suffix:semicolon
id|octets
op_assign
l_int|0
suffix:semicolon
op_star
(paren
id|tp
op_assign
id|tmp
)paren
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_const
r_char
op_star
id|pch
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pch
op_assign
id|strchr
c_func
(paren
id|digits
comma
id|ch
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
r_int
r_new
op_assign
op_star
id|tp
op_star
l_int|10
op_plus
(paren
id|pch
id|digits
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
OG
l_int|255
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
op_star
id|tp
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saw_digit
)paren
(brace
r_if
c_cond
(paren
op_increment
id|octets
OG
l_int|4
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|saw_digit
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;.&squot;
op_logical_and
id|saw_digit
)paren
(brace
r_if
c_cond
(paren
id|octets
op_eq
l_int|4
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
op_star
op_increment
id|tp
op_assign
l_int|0
suffix:semicolon
id|saw_digit
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|octets
OL
l_int|4
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|tmp
comma
id|NS_INADDRSZ
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* int&n; * inet_pton6(src, dst)&n; *      convert presentation level address to network order binary form.&n; * return:&n; *      1 if `src&squot; is a valid [RFC1884 2.2] address, else 0.&n; * notice:&n; *      (1) does not touch `dst&squot; unless it&squot;s returning 1.&n; *      (2) :: in a full address is silently ignored.&n; * credit:&n; *      inspired by Mark Andrews.&n; * author:&n; *      Paul Vixie, 1996.&n; */
macro_line|#ifndef NO_IPV6
r_static
r_int
DECL|function|inet_pton6
id|inet_pton6
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_int
r_char
op_star
id|dst
)paren
(brace
r_static
r_const
r_char
id|xdigits_l
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
comma
id|xdigits_u
(braket
)braket
op_assign
l_string|&quot;0123456789ABCDEF&quot;
suffix:semicolon
r_int
r_char
id|tmp
(braket
id|NS_IN6ADDRSZ
)braket
comma
op_star
id|tp
comma
op_star
id|endp
comma
op_star
id|colonp
suffix:semicolon
r_const
r_char
op_star
id|xdigits
comma
op_star
id|curtok
suffix:semicolon
r_int
id|ch
comma
id|saw_xdigit
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|memset
c_func
(paren
(paren
id|tp
op_assign
id|tmp
)paren
comma
l_char|&squot;&bslash;0&squot;
comma
id|NS_IN6ADDRSZ
)paren
suffix:semicolon
id|endp
op_assign
id|tp
op_plus
id|NS_IN6ADDRSZ
suffix:semicolon
id|colonp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Leading :: requires some special handling. */
r_if
c_cond
(paren
op_star
id|src
op_eq
l_char|&squot;:&squot;
)paren
r_if
c_cond
(paren
op_star
op_increment
id|src
op_ne
l_char|&squot;:&squot;
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|curtok
op_assign
id|src
suffix:semicolon
id|saw_xdigit
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|src
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_const
r_char
op_star
id|pch
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pch
op_assign
id|strchr
c_func
(paren
(paren
id|xdigits
op_assign
id|xdigits_l
)paren
comma
id|ch
)paren
)paren
op_eq
l_int|NULL
)paren
id|pch
op_assign
id|strchr
c_func
(paren
(paren
id|xdigits
op_assign
id|xdigits_u
)paren
comma
id|ch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pch
op_ne
l_int|NULL
)paren
(brace
id|val
op_lshift_assign
l_int|4
suffix:semicolon
id|val
op_or_assign
(paren
id|pch
id|xdigits
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
l_int|0xffff
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|saw_xdigit
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|curtok
op_assign
id|src
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saw_xdigit
)paren
(brace
r_if
c_cond
(paren
id|colonp
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|colonp
op_assign
id|tp
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp
op_plus
id|NS_INT16SZ
OG
id|endp
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
op_star
id|tp
op_increment
op_assign
(paren
r_int
r_char
)paren
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
op_star
id|tp
op_increment
op_assign
(paren
r_int
r_char
)paren
id|val
op_amp
l_int|0xff
suffix:semicolon
id|saw_xdigit
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;.&squot;
op_logical_and
(paren
(paren
id|tp
op_plus
id|NS_INADDRSZ
)paren
op_le
id|endp
)paren
op_logical_and
id|inet_pton4
c_func
(paren
id|curtok
comma
id|tp
)paren
OG
l_int|0
)paren
(brace
id|tp
op_add_assign
id|NS_INADDRSZ
suffix:semicolon
id|saw_xdigit
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* &squot;&bslash;0&squot; was seen by inet_pton4(). */
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|saw_xdigit
)paren
(brace
r_if
c_cond
(paren
id|tp
op_plus
id|NS_INT16SZ
OG
id|endp
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
op_star
id|tp
op_increment
op_assign
(paren
r_int
r_char
)paren
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
op_star
id|tp
op_increment
op_assign
(paren
r_int
r_char
)paren
id|val
op_amp
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|colonp
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;                 * Since some memmove()&squot;s erroneously fail to handle&n;                 * overlapping regions, we&squot;ll do the shift by hand.&n;                 */
r_const
r_int
id|n
op_assign
id|tp
id|colonp
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|endp
(braket
id|i
)braket
op_assign
id|colonp
(braket
id|n
id|i
)braket
suffix:semicolon
id|colonp
(braket
id|n
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|tp
op_assign
id|endp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp
op_ne
id|endp
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|tmp
comma
id|NS_IN6ADDRSZ
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* int&n; * isc_net_pton(af, src, dst)&n; *      convert from presentation format (which usually means ASCII printable)&n; *      to network format (which is usually some kind of binary format).&n; * return:&n; *      1 if the address was valid for the specified address family&n; *      0 if the address wasn&squot;t valid (`dst&squot; is untouched in this case)&n; *      -1 if some other error occurred (`dst&squot; is untouched in this case, too)&n; * author:&n; *      Paul Vixie, 1996.&n; */
r_int
DECL|function|inet_pton
id|inet_pton
c_func
(paren
r_int
id|af
comma
r_const
r_char
op_star
id|src
comma
r_void
op_star
id|dst
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
id|inet_pton4
c_func
(paren
id|src
comma
id|dst
)paren
)paren
suffix:semicolon
macro_line|#ifndef NO_IPV6
r_case
id|AF_INET6
suffix:colon
r_return
(paren
id|inet_pton6
c_func
(paren
id|src
comma
id|dst
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
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* NOTREACHED */
)brace
eof
