multiline_comment|/* Extended regular expression matching and search library.&n;   Copyright (C) 2002, 2003, 2005 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;   Contributed by Isamu Hasegawa &lt;isamu@yamato.ibm.com&gt;.&n;&n;   The GNU C Library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Lesser General Public&n;   License as published by the Free Software Foundation; either&n;   version 2.1 of the License, or (at your option) any later version.&n;&n;   The GNU C Library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Lesser General Public License for more details.&n;&n;   You should have received a copy of the GNU Lesser General Public&n;   License along with the GNU C Library; if not, write to the Free&n;   Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA&n;   02110-1301 USA.  */
macro_line|#ifdef HAVE_CONFIG_H
macro_line|#include &quot;config.h&quot;
macro_line|#endif
multiline_comment|/* Make sure noone compiles this code with a C++ compiler.  */
macro_line|#ifdef __cplusplus
macro_line|# error &quot;This is C code, use a C compiler&quot;
macro_line|#endif
macro_line|#ifdef _LIBC
multiline_comment|/* We have to keep the namespace clean.  */
DECL|macro|regfree
macro_line|# define regfree(preg) __regfree (preg)
DECL|macro|regexec
macro_line|# define regexec(pr, st, nm, pm, ef) __regexec (pr, st, nm, pm, ef)
DECL|macro|regcomp
macro_line|# define regcomp(preg, pattern, cflags) __regcomp (preg, pattern, cflags)
DECL|macro|regerror
macro_line|# define regerror(errcode, preg, errbuf, errbuf_size) &bslash;&n;&t;__regerror(errcode, preg, errbuf, errbuf_size)
DECL|macro|re_set_registers
macro_line|# define re_set_registers(bu, re, nu, st, en) &bslash;&n;&t;__re_set_registers (bu, re, nu, st, en)
DECL|macro|re_match_2
macro_line|# define re_match_2(bufp, string1, size1, string2, size2, pos, regs, stop) &bslash;&n;&t;__re_match_2 (bufp, string1, size1, string2, size2, pos, regs, stop)
DECL|macro|re_match
macro_line|# define re_match(bufp, string, size, pos, regs) &bslash;&n;&t;__re_match (bufp, string, size, pos, regs)
DECL|macro|re_search
macro_line|# define re_search(bufp, string, size, startpos, range, regs) &bslash;&n;&t;__re_search (bufp, string, size, startpos, range, regs)
DECL|macro|re_compile_pattern
macro_line|# define re_compile_pattern(pattern, length, bufp) &bslash;&n;&t;__re_compile_pattern (pattern, length, bufp)
DECL|macro|re_set_syntax
macro_line|# define re_set_syntax(syntax) __re_set_syntax (syntax)
DECL|macro|re_search_2
macro_line|# define re_search_2(bufp, st1, s1, st2, s2, startpos, range, regs, stop) &bslash;&n;&t;__re_search_2 (bufp, st1, s1, st2, s2, startpos, range, regs, stop)
DECL|macro|re_compile_fastmap
macro_line|# define re_compile_fastmap(bufp) __re_compile_fastmap (bufp)
macro_line|# include &quot;../locale/localeinfo.h&quot;
macro_line|#endif
macro_line|#if defined (_MSC_VER)
macro_line|#include &lt;stdio.h&gt; /* for size_t */
macro_line|#endif
multiline_comment|/* On some systems, limits.h sets RE_DUP_MAX to a lower value than&n;   GNU regex allows.  Include it before &lt;regex.h&gt;, which correctly&n;   #undefs RE_DUP_MAX and sets it to the right value.  */
macro_line|#include &lt;limits.h&gt;
macro_line|#ifdef GAWK
DECL|macro|alloca
macro_line|#undef alloca
DECL|macro|alloca
mdefine_line|#define alloca alloca_is_bad_you_should_never_use_it
macro_line|#endif
macro_line|#include &lt;regex.h&gt;
macro_line|#include &quot;regex_internal.h&quot;
macro_line|#include &quot;regex_internal.c&quot;
macro_line|#ifdef GAWK
DECL|macro|bool
mdefine_line|#define bool int
DECL|macro|true
mdefine_line|#define true (1)
DECL|macro|false
mdefine_line|#define false (0)
macro_line|#endif
macro_line|#include &quot;regcomp.c&quot;
macro_line|#include &quot;regexec.c&quot;
multiline_comment|/* Binary backward compatibility.  */
macro_line|#if _LIBC
macro_line|# include &lt;shlib-compat.h&gt;
macro_line|# if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_3)
id|link_warning
(paren
id|re_max_failures
comma
l_string|&quot;the &squot;re_max_failures&squot; variable is obsolete and will go away.&quot;
)paren
DECL|variable|re_max_failures
r_int
id|re_max_failures
op_assign
l_int|2000
suffix:semicolon
macro_line|# endif
macro_line|#endif
eof
