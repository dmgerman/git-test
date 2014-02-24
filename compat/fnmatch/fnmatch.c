multiline_comment|/* Copyright (C) 1991, 92, 93, 96, 97, 98, 99 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;&n;   This library is free software; you can redistribute it and/or&n;   modify it under the terms of the GNU Library General Public License as&n;   published by the Free Software Foundation; either version 2 of the&n;   License, or (at your option) any later version.&n;&n;   This library is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   Library General Public License for more details.&n;&n;   You should have received a copy of the GNU Library General Public&n;   License along with this library; see the file COPYING.LIB.  If not,&n;   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,&n;   Boston, MA 02111-1307, USA.  */
macro_line|#if HAVE_CONFIG_H
macro_line|# include &lt;config.h&gt;
macro_line|#endif
multiline_comment|/* Enable GNU extensions in fnmatch.h.  */
macro_line|#ifndef _GNU_SOURCE
DECL|macro|_GNU_SOURCE
macro_line|# define _GNU_SOURCE&t;1
macro_line|#endif
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fnmatch.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#if HAVE_STRING_H || defined _LIBC
macro_line|# include &lt;string.h&gt;
macro_line|#else
macro_line|# include &lt;strings.h&gt;
macro_line|#endif
macro_line|#if defined STDC_HEADERS || defined _LIBC
macro_line|# include &lt;stdlib.h&gt;
macro_line|#endif
multiline_comment|/* For platforms which support the ISO C amendment 1 functionality we&n;   support user defined character classes.  */
macro_line|#if defined _LIBC || (defined HAVE_WCTYPE_H &amp;&amp; defined HAVE_WCHAR_H)
multiline_comment|/* Solaris 2.5 has a bug: &lt;wchar.h&gt; must be included before &lt;wctype.h&gt;.  */
macro_line|# include &lt;wchar.h&gt;
macro_line|# include &lt;wctype.h&gt;
macro_line|#endif
multiline_comment|/* Comment out all this code if we are using the GNU C Library, and are not&n;   actually compiling the library itself.  This code is part of the GNU C&n;   Library, but also included in many other GNU distributions.  Compiling&n;   and linking in this code is a waste when using the GNU C library&n;   (especially if it is a shared library).  Rather than having every GNU&n;   program understand `configure --with-gnu-libc&squot; and omit the object files,&n;   it is simpler to just do this in the source for each such file.  */
macro_line|#if defined NO_FNMATCH || defined NO_FNMATCH_CASEFOLD || &bslash;&n;    defined _LIBC || !defined __GNU_LIBRARY__
macro_line|# if defined STDC_HEADERS || !defined isascii
DECL|macro|ISASCII
macro_line|#  define ISASCII(c) 1
macro_line|# else
DECL|macro|ISASCII
macro_line|#  define ISASCII(c) isascii(c)
macro_line|# endif
macro_line|# ifdef isblank
DECL|macro|ISBLANK
macro_line|#  define ISBLANK(c) (ISASCII (c) &amp;&amp; isblank (c))
macro_line|# else
DECL|macro|ISBLANK
macro_line|#  define ISBLANK(c) ((c) == &squot; &squot; || (c) == &squot;&bslash;t&squot;)
macro_line|# endif
macro_line|# ifdef isgraph
DECL|macro|ISGRAPH
macro_line|#  define ISGRAPH(c) (ISASCII (c) &amp;&amp; isgraph (c))
macro_line|# else
DECL|macro|ISGRAPH
macro_line|#  define ISGRAPH(c) (ISASCII (c) &amp;&amp; isprint (c) &amp;&amp; !isspace (c))
macro_line|# endif
DECL|macro|ISPRINT
macro_line|# define ISPRINT(c) (ISASCII (c) &amp;&amp; isprint (c))
DECL|macro|ISDIGIT
macro_line|# define ISDIGIT(c) (ISASCII (c) &amp;&amp; isdigit (c))
DECL|macro|ISALNUM
macro_line|# define ISALNUM(c) (ISASCII (c) &amp;&amp; isalnum (c))
DECL|macro|ISALPHA
macro_line|# define ISALPHA(c) (ISASCII (c) &amp;&amp; isalpha (c))
DECL|macro|ISCNTRL
macro_line|# define ISCNTRL(c) (ISASCII (c) &amp;&amp; iscntrl (c))
DECL|macro|ISLOWER
macro_line|# define ISLOWER(c) (ISASCII (c) &amp;&amp; islower (c))
DECL|macro|ISPUNCT
macro_line|# define ISPUNCT(c) (ISASCII (c) &amp;&amp; ispunct (c))
DECL|macro|ISSPACE
macro_line|# define ISSPACE(c) (ISASCII (c) &amp;&amp; isspace (c))
DECL|macro|ISUPPER
macro_line|# define ISUPPER(c) (ISASCII (c) &amp;&amp; isupper (c))
DECL|macro|ISXDIGIT
macro_line|# define ISXDIGIT(c) (ISASCII (c) &amp;&amp; isxdigit (c))
DECL|macro|STREQ
macro_line|# define STREQ(s1, s2) ((strcmp (s1, s2) == 0))
macro_line|# if defined _LIBC || (defined HAVE_WCTYPE_H &amp;&amp; defined HAVE_WCHAR_H)
multiline_comment|/* The GNU C library provides support for user-defined character classes&n;   and the functions from ISO C amendment 1.  */
macro_line|#  ifdef CHARCLASS_NAME_MAX
DECL|macro|CHAR_CLASS_MAX_LENGTH
macro_line|#   define CHAR_CLASS_MAX_LENGTH CHARCLASS_NAME_MAX
macro_line|#  else
multiline_comment|/* This shouldn&squot;t happen but some implementation might still have this&n;   problem.  Use a reasonable default value.  */
DECL|macro|CHAR_CLASS_MAX_LENGTH
macro_line|#   define CHAR_CLASS_MAX_LENGTH 256
macro_line|#  endif
macro_line|#  ifdef _LIBC
DECL|macro|IS_CHAR_CLASS
macro_line|#   define IS_CHAR_CLASS(string) __wctype (string)
macro_line|#  else
DECL|macro|IS_CHAR_CLASS
macro_line|#   define IS_CHAR_CLASS(string) wctype (string)
macro_line|#  endif
macro_line|# else
DECL|macro|CHAR_CLASS_MAX_LENGTH
macro_line|#  define CHAR_CLASS_MAX_LENGTH  6 /* Namely, `xdigit&squot;.  */
DECL|macro|IS_CHAR_CLASS
macro_line|#  define IS_CHAR_CLASS(string)&t;&t;&t;&t;&t;&t;      &bslash;&n;   (STREQ (string, &quot;alpha&quot;) || STREQ (string, &quot;upper&quot;)&t;&t;&t;      &bslash;&n;    || STREQ (string, &quot;lower&quot;) || STREQ (string, &quot;digit&quot;)&t;&t;      &bslash;&n;    || STREQ (string, &quot;alnum&quot;) || STREQ (string, &quot;xdigit&quot;)&t;&t;      &bslash;&n;    || STREQ (string, &quot;space&quot;) || STREQ (string, &quot;print&quot;)&t;&t;      &bslash;&n;    || STREQ (string, &quot;punct&quot;) || STREQ (string, &quot;graph&quot;)&t;&t;      &bslash;&n;    || STREQ (string, &quot;cntrl&quot;) || STREQ (string, &quot;blank&quot;))
macro_line|# endif
multiline_comment|/* Avoid depending on library functions or files&n;   whose names are inconsistent.  */
macro_line|# if !defined _LIBC &amp;&amp; !defined getenv
r_extern
r_char
op_star
id|getenv
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|# endif
macro_line|# ifndef errno
r_extern
r_int
id|errno
suffix:semicolon
macro_line|# endif
macro_line|# ifndef NULL
DECL|macro|NULL
macro_line|#  define NULL 0
macro_line|# endif
multiline_comment|/* This function doesn&squot;t exist on most systems.  */
macro_line|# if !defined HAVE___STRCHRNUL &amp;&amp; !defined _LIBC
r_static
r_char
op_star
DECL|function|__strchrnul
id|__strchrnul
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|c
)paren
(brace
r_char
op_star
id|result
op_assign
id|strchr
(paren
id|s
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|NULL
)paren
id|result
op_assign
id|strchr
(paren
id|s
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|# endif
macro_line|# ifndef internal_function
multiline_comment|/* Inside GNU libc we mark some function in a special way.  In other&n;   environments simply ignore the marking.  */
DECL|macro|internal_function
macro_line|#  define internal_function
macro_line|# endif
multiline_comment|/* Match STRING against the filename pattern PATTERN, returning zero if&n;   it matches, nonzero if not.  */
r_static
r_int
id|internal_fnmatch
id|__P
(paren
(paren
r_const
r_char
op_star
id|pattern
comma
r_const
r_char
op_star
id|string
comma
r_int
id|no_leading_period
comma
r_int
id|flags
)paren
)paren
id|internal_function
suffix:semicolon
r_static
r_int
id|internal_function
DECL|function|internal_fnmatch
id|internal_fnmatch
(paren
r_const
r_char
op_star
id|pattern
comma
r_const
r_char
op_star
id|string
comma
r_int
id|no_leading_period
comma
r_int
id|flags
)paren
(brace
r_register
r_const
r_char
op_star
id|p
op_assign
id|pattern
comma
op_star
id|n
op_assign
id|string
suffix:semicolon
r_register
r_int
r_char
id|c
suffix:semicolon
multiline_comment|/* Note that this evaluates C many times.  */
macro_line|# ifdef _LIBC
DECL|macro|FOLD
macro_line|#  define FOLD(c) ((flags &amp; FNM_CASEFOLD) ? tolower (c) : (c))
macro_line|# else
macro_line|#  define FOLD(c) ((flags &amp; FNM_CASEFOLD) &amp;&amp; ISUPPER (c) ? tolower (c) : (c))
macro_line|# endif
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|c
op_assign
id|FOLD
(paren
id|c
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;?&squot;
suffix:colon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;.&squot;
op_logical_and
id|no_leading_period
op_logical_and
(paren
id|n
op_eq
id|string
op_logical_or
(paren
id|n
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
)paren
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|FNM_NOESCAPE
)paren
)paren
(brace
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* Trailing &bslash; loses.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
id|c
op_assign
id|FOLD
(paren
id|c
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|FOLD
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
op_ne
id|c
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;*&squot;
suffix:colon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;.&squot;
op_logical_and
id|no_leading_period
op_logical_and
(paren
id|n
op_eq
id|string
op_logical_or
(paren
id|n
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
)paren
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|c
op_eq
l_char|&squot;?&squot;
op_logical_or
id|c
op_eq
l_char|&squot;*&squot;
suffix:semicolon
id|c
op_assign
op_star
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
multiline_comment|/* A slash does not match a wildcard under FNM_FILE_NAME.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;?&squot;
)paren
(brace
multiline_comment|/* A ? needs to match one character.  */
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* There isn&squot;t another character; no match.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
r_else
multiline_comment|/* One character of the string is consumed in matching&n;&t;&t;       this ? wildcard, so *??? won&squot;t match if there are&n;&t;&t;       less than three characters.  */
op_increment
id|n
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* The wildcard(s) is/are the last element of the pattern.&n;&t;       If the name is a file name and contains another slash&n;&t;       this does mean it cannot match.  */
r_return
(paren
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
op_logical_and
id|strchr
(paren
id|n
comma
l_char|&squot;/&squot;
)paren
op_ne
l_int|NULL
ques
c_cond
id|FNM_NOMATCH
suffix:colon
l_int|0
)paren
suffix:semicolon
r_else
(brace
r_const
r_char
op_star
id|endp
suffix:semicolon
id|endp
op_assign
id|__strchrnul
(paren
id|n
comma
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
ques
c_cond
l_char|&squot;/&squot;
suffix:colon
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;[&squot;
)paren
(brace
r_int
id|flags2
op_assign
(paren
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
ques
c_cond
id|flags
suffix:colon
(paren
id|flags
op_amp
op_complement
id|FNM_PERIOD
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
op_decrement
id|p
suffix:semicolon
id|n
OL
id|endp
suffix:semicolon
op_increment
id|n
)paren
r_if
c_cond
(paren
id|internal_fnmatch
(paren
id|p
comma
id|n
comma
(paren
id|no_leading_period
op_logical_and
(paren
id|n
op_eq
id|string
op_logical_or
(paren
id|n
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
)paren
)paren
comma
id|flags2
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
(brace
r_while
c_loop
(paren
op_star
id|n
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
op_star
id|n
op_ne
l_char|&squot;/&squot;
)paren
op_increment
id|n
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|internal_fnmatch
(paren
id|p
comma
id|n
op_plus
l_int|1
comma
id|flags
op_amp
id|FNM_PERIOD
comma
id|flags
)paren
op_eq
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
id|flags2
op_assign
(paren
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
ques
c_cond
id|flags
suffix:colon
(paren
id|flags
op_amp
op_complement
id|FNM_PERIOD
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
op_logical_neg
(paren
id|flags
op_amp
id|FNM_NOESCAPE
)paren
)paren
id|c
op_assign
op_star
id|p
suffix:semicolon
id|c
op_assign
id|FOLD
(paren
id|c
)paren
suffix:semicolon
r_for
c_loop
(paren
op_decrement
id|p
suffix:semicolon
id|n
OL
id|endp
suffix:semicolon
op_increment
id|n
)paren
r_if
c_cond
(paren
id|FOLD
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
op_eq
id|c
op_logical_and
(paren
id|internal_fnmatch
(paren
id|p
comma
id|n
comma
(paren
id|no_leading_period
op_logical_and
(paren
id|n
op_eq
id|string
op_logical_or
(paren
id|n
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
)paren
)paren
comma
id|flags2
)paren
op_eq
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* If we come here no match is possible with the wildcard.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
r_case
l_char|&squot;[&squot;
suffix:colon
(brace
multiline_comment|/* Nonzero if the sense of the character class is inverted.  */
r_static
r_int
id|posixly_correct
suffix:semicolon
r_register
r_int
op_logical_neg
suffix:semicolon
r_char
id|cold
suffix:semicolon
r_if
c_cond
(paren
id|posixly_correct
op_eq
l_int|0
)paren
id|posixly_correct
op_assign
id|getenv
(paren
l_string|&quot;POSIXLY_CORRECT&quot;
)paren
op_ne
l_int|NULL
ques
c_cond
l_int|1
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;.&squot;
op_logical_and
id|no_leading_period
op_logical_and
(paren
id|n
op_eq
id|string
op_logical_or
(paren
id|n
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
)paren
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;/&squot;
op_logical_and
(paren
id|flags
op_amp
id|FNM_FILE_NAME
)paren
)paren
multiline_comment|/* `/&squot; cannot be matched.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
op_logical_neg
op_assign
(paren
op_star
id|p
op_eq
l_char|&squot;!&squot;
op_logical_or
(paren
id|posixly_correct
OL
l_int|0
op_logical_and
op_star
id|p
op_eq
l_char|&squot;^&squot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
)paren
op_increment
id|p
suffix:semicolon
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
id|fn
op_assign
id|FOLD
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|FNM_NOESCAPE
)paren
op_logical_and
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
id|c
op_assign
id|FOLD
(paren
(paren
r_int
r_char
)paren
op_star
id|p
)paren
suffix:semicolon
op_increment
id|p
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|fn
)paren
r_goto
id|matched
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;[&squot;
op_logical_and
op_star
id|p
op_eq
l_char|&squot;:&squot;
)paren
(brace
multiline_comment|/* Leave room for the null.  */
r_char
id|str
(braket
id|CHAR_CLASS_MAX_LENGTH
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|c1
op_assign
l_int|0
suffix:semicolon
macro_line|# if defined _LIBC || (defined HAVE_WCTYPE_H &amp;&amp; defined HAVE_WCHAR_H)
id|wctype_t
id|wt
suffix:semicolon
macro_line|# endif
r_const
r_char
op_star
id|startp
op_assign
id|p
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|c1
OG
id|CHAR_CLASS_MAX_LENGTH
)paren
multiline_comment|/* The name is too long and therefore the pattern&n;&t;&t;&t;     is ill-formed.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
id|c
op_assign
op_star
op_increment
id|p
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;:&squot;
op_logical_and
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;]&squot;
)paren
(brace
id|p
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
OL
l_char|&squot;a&squot;
op_logical_or
id|c
op_ge
l_char|&squot;z&squot;
)paren
(brace
multiline_comment|/* This cannot possibly be a character class name.&n;&t;&t;&t;       Match it as a normal range.  */
id|p
op_assign
id|startp
suffix:semicolon
id|c
op_assign
l_char|&squot;[&squot;
suffix:semicolon
r_goto
id|normal_bracket
suffix:semicolon
)brace
id|str
(braket
id|c1
op_increment
)braket
op_assign
id|c
suffix:semicolon
)brace
id|str
(braket
id|c1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
macro_line|# if defined _LIBC || (defined HAVE_WCTYPE_H &amp;&amp; defined HAVE_WCHAR_H)
id|wt
op_assign
id|IS_CHAR_CLASS
(paren
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wt
op_eq
l_int|0
)paren
multiline_comment|/* Invalid character class name.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|__iswctype
(paren
id|__btowc
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
comma
id|wt
)paren
)paren
r_goto
id|matched
suffix:semicolon
macro_line|# else
r_if
c_cond
(paren
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;alnum&quot;
)paren
op_logical_and
id|ISALNUM
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;alpha&quot;
)paren
op_logical_and
id|ISALPHA
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;blank&quot;
)paren
op_logical_and
id|ISBLANK
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;cntrl&quot;
)paren
op_logical_and
id|ISCNTRL
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;digit&quot;
)paren
op_logical_and
id|ISDIGIT
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;graph&quot;
)paren
op_logical_and
id|ISGRAPH
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;lower&quot;
)paren
op_logical_and
id|ISLOWER
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;print&quot;
)paren
op_logical_and
id|ISPRINT
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;punct&quot;
)paren
op_logical_and
id|ISPUNCT
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;space&quot;
)paren
op_logical_and
id|ISSPACE
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;upper&quot;
)paren
op_logical_and
id|ISUPPER
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
op_logical_or
(paren
id|STREQ
(paren
id|str
comma
l_string|&quot;xdigit&quot;
)paren
op_logical_and
id|ISXDIGIT
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
)paren
r_goto
id|matched
suffix:semicolon
macro_line|# endif
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* [ (unterminated) loses.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
r_else
(brace
id|normal_bracket
suffix:colon
r_if
c_cond
(paren
id|FOLD
(paren
id|c
)paren
op_eq
id|fn
)paren
r_goto
id|matched
suffix:semicolon
id|cold
op_assign
id|c
suffix:semicolon
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;-&squot;
op_logical_and
op_star
id|p
op_ne
l_char|&squot;]&squot;
)paren
(brace
multiline_comment|/* It is a range.  */
r_int
r_char
id|cend
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|FNM_NOESCAPE
)paren
op_logical_and
id|cend
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
id|cend
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cend
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_if
c_cond
(paren
id|cold
op_le
id|fn
op_logical_and
id|fn
op_le
id|FOLD
(paren
id|cend
)paren
)paren
r_goto
id|matched
suffix:semicolon
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;]&squot;
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_logical_neg
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_break
suffix:semicolon
id|matched
suffix:colon
multiline_comment|/* Skip the rest of the [...] that already matched.  */
r_while
c_loop
(paren
id|c
op_ne
l_char|&squot;]&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;0&squot;
)paren
multiline_comment|/* [... (unterminated) loses.  */
r_return
id|FNM_NOMATCH
suffix:semicolon
id|c
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|FNM_NOESCAPE
)paren
op_logical_and
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
multiline_comment|/* XXX 1003.2d11 is unclear if this is right.  */
op_increment
id|p
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;[&squot;
op_logical_and
op_star
id|p
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_do
r_if
c_cond
(paren
op_star
op_increment
id|p
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
op_ne
l_char|&squot;:&squot;
op_logical_or
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;]&squot;
)paren
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
id|c
op_assign
op_star
id|p
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|c
op_ne
id|FOLD
(paren
(paren
r_int
r_char
)paren
op_star
id|n
)paren
)paren
r_return
id|FNM_NOMATCH
suffix:semicolon
)brace
op_increment
id|n
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|n
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|FNM_LEADING_DIR
)paren
op_logical_and
op_star
id|n
op_eq
l_char|&squot;/&squot;
)paren
multiline_comment|/* The FNM_LEADING_DIR flag says that &quot;foo*&quot; matches &quot;foobar/frobozz&quot;.  */
r_return
l_int|0
suffix:semicolon
r_return
id|FNM_NOMATCH
suffix:semicolon
DECL|macro|FOLD
macro_line|# undef FOLD
)brace
r_int
DECL|function|fnmatch
id|fnmatch
(paren
r_const
r_char
op_star
id|pattern
comma
r_const
r_char
op_star
id|string
comma
r_int
id|flags
)paren
(brace
r_return
id|internal_fnmatch
(paren
id|pattern
comma
id|string
comma
id|flags
op_amp
id|FNM_PERIOD
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* _LIBC or not __GNU_LIBRARY__.  */
eof