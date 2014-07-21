multiline_comment|/*&n; * sh-i18n--envsubst.c - a stripped-down version of gettext&squot;s envsubst(1)&n; *&n; * Copyright (C) 2010 &AElig;var Arnfj&ouml;r&eth; Bjarmason&n; *&n; * This is a modified version of&n; * 67d0871a8c:gettext-runtime/src/envsubst.c from the gettext.git&n; * repository. It has been stripped down to only implement the&n; * envsubst(1) features that we need in the git-sh-i18n fallbacks.&n; *&n; * The &quot;Close standard error&quot; part in main() is from&n; * 8dac033df0:gnulib-local/lib/closeout.c. The copyright notices for&n; * both files are reproduced immediately below.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
multiline_comment|/* Substitution of environment variables in shell format strings.&n;   Copyright (C) 2003-2007 Free Software Foundation, Inc.&n;   Written by Bruno Haible &lt;bruno@clisp.org&gt;, 2003.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software Foundation,&n;   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */
multiline_comment|/* closeout.c - close standard output and standard error&n;   Copyright (C) 1998-2007 Free Software Foundation, Inc.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software Foundation,&n;   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
multiline_comment|/* If true, substitution shall be performed on all variables.  */
DECL|variable|all_variables
r_static
r_int
r_int
r_int
id|all_variables
suffix:semicolon
multiline_comment|/* Forward declaration of local functions.  */
r_static
r_void
id|print_variables
(paren
r_const
r_char
op_star
id|string
)paren
suffix:semicolon
r_static
r_void
id|note_variables
(paren
r_const
r_char
op_star
id|string
)paren
suffix:semicolon
r_static
r_void
id|subst_from_stdin
(paren
r_void
)paren
suffix:semicolon
r_int
DECL|function|main
id|main
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
multiline_comment|/* Default values for command line options.  */
multiline_comment|/* unsigned short int show_variables = 0; */
r_switch
c_cond
(paren
id|argc
)paren
(brace
r_case
l_int|1
suffix:colon
id|error
(paren
l_string|&quot;we won&squot;t substitute all variables on stdin for you&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;  all_variables = 1;&n;      subst_from_stdin ();&n;&t;  */
r_case
l_int|2
suffix:colon
multiline_comment|/* echo &squot;$foo and $bar&squot; | git sh-i18n--envsubst --variables &squot;$foo and $bar&squot; */
id|all_variables
op_assign
l_int|0
suffix:semicolon
id|note_variables
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|subst_from_stdin
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* git sh-i18n--envsubst --variables &squot;$foo and $bar&squot; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--variables&quot;
)paren
)paren
id|error
(paren
l_string|&quot;first argument must be --variables when two are given&quot;
)paren
suffix:semicolon
multiline_comment|/* show_variables = 1; */
id|print_variables
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|error
(paren
l_string|&quot;too many arguments&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Close standard error.  This is simpler than fwriteerror_no_ebadf, because&n;     upon failure we don&squot;t need an errno - all we can do at this point is to&n;     set an exit status.  */
id|errno
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ferror
(paren
id|stderr
)paren
op_logical_or
id|fflush
(paren
id|stderr
)paren
)paren
(brace
id|fclose
(paren
id|stderr
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fclose
(paren
id|stderr
)paren
op_logical_and
id|errno
op_ne
id|EBADF
)paren
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_SUCCESS
)paren
suffix:semicolon
)brace
multiline_comment|/* Parse the string and invoke the callback each time a $VARIABLE or&n;   ${VARIABLE} construct is seen, where VARIABLE is a nonempty sequence&n;   of ASCII alphanumeric/underscore characters, starting with an ASCII&n;   alphabetic/underscore character.&n;   We allow only ASCII characters, to avoid dependencies w.r.t. the current&n;   encoding: While &quot;${&bslash;xe0}&quot; looks like a variable access in ISO-8859-1&n;   encoding, it doesn&squot;t look like one in the BIG5, BIG5-HKSCS, GBK, GB18030,&n;   SHIFT_JIS, JOHAB encodings, because &bslash;xe0&bslash;x7d is a single character in these&n;   encodings.  */
r_static
r_void
DECL|function|find_variables
id|find_variables
(paren
r_const
r_char
op_star
id|string
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_const
r_char
op_star
id|var_ptr
comma
r_int
id|var_len
)paren
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
op_star
id|string
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)paren
r_if
c_cond
(paren
op_star
id|string
op_increment
op_eq
l_char|&squot;$&squot;
)paren
(brace
r_const
r_char
op_star
id|variable_start
suffix:semicolon
r_const
r_char
op_star
id|variable_end
suffix:semicolon
r_int
r_int
r_int
id|valid
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_star
id|string
op_eq
l_char|&squot;{&squot;
)paren
id|string
op_increment
suffix:semicolon
id|variable_start
op_assign
id|string
suffix:semicolon
id|c
op_assign
op_star
id|string
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
id|c
op_eq
l_char|&squot;_&squot;
)paren
(brace
r_do
id|c
op_assign
op_star
op_increment
id|string
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
op_logical_or
id|c
op_eq
l_char|&squot;_&squot;
)paren
suffix:semicolon
id|variable_end
op_assign
id|string
suffix:semicolon
r_if
c_cond
(paren
id|variable_start
(braket
l_int|1
)braket
op_eq
l_char|&squot;{&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|string
op_eq
l_char|&squot;}&squot;
)paren
(brace
id|string
op_increment
suffix:semicolon
id|valid
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|valid
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|valid
)paren
id|callback
(paren
id|variable_start
comma
id|variable_end
id|variable_start
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Print a variable to stdout, followed by a newline.  */
r_static
r_void
DECL|function|print_variable
id|print_variable
(paren
r_const
r_char
op_star
id|var_ptr
comma
r_int
id|var_len
)paren
(brace
id|fwrite
(paren
id|var_ptr
comma
id|var_len
comma
l_int|1
comma
id|stdout
)paren
suffix:semicolon
id|putchar
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Print the variables contained in STRING to stdout, each one followed by a&n;   newline.  */
r_static
r_void
DECL|function|print_variables
id|print_variables
(paren
r_const
r_char
op_star
id|string
)paren
(brace
id|find_variables
(paren
id|string
comma
op_amp
id|print_variable
)paren
suffix:semicolon
)brace
multiline_comment|/* Type describing list of immutable strings,&n;   implemented using a dynamic array.  */
DECL|typedef|string_list_ty
r_typedef
r_struct
id|string_list_ty
id|string_list_ty
suffix:semicolon
DECL|struct|string_list_ty
r_struct
id|string_list_ty
(brace
DECL|member|item
r_const
r_char
op_star
op_star
id|item
suffix:semicolon
DECL|member|nitems
r_int
id|nitems
suffix:semicolon
DECL|member|nitems_max
r_int
id|nitems_max
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Initialize an empty list of strings.  */
r_static
r_inline
r_void
DECL|function|string_list_init
id|string_list_init
(paren
id|string_list_ty
op_star
id|slp
)paren
(brace
id|slp-&gt;item
op_assign
l_int|NULL
suffix:semicolon
id|slp-&gt;nitems
op_assign
l_int|0
suffix:semicolon
id|slp-&gt;nitems_max
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Append a single string to the end of a list of strings.  */
r_static
r_inline
r_void
DECL|function|string_list_append
id|string_list_append
(paren
id|string_list_ty
op_star
id|slp
comma
r_const
r_char
op_star
id|s
)paren
(brace
multiline_comment|/* Grow the list.  */
r_if
c_cond
(paren
id|slp-&gt;nitems
op_ge
id|slp-&gt;nitems_max
)paren
(brace
r_int
id|nbytes
suffix:semicolon
id|slp-&gt;nitems_max
op_assign
id|slp-&gt;nitems_max
op_star
l_int|2
op_plus
l_int|4
suffix:semicolon
id|nbytes
op_assign
id|slp-&gt;nitems_max
op_star
r_sizeof
(paren
id|slp-&gt;item
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|slp-&gt;item
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
id|xrealloc
(paren
id|slp-&gt;item
comma
id|nbytes
)paren
suffix:semicolon
)brace
multiline_comment|/* Add the string to the end of the list.  */
id|slp-&gt;item
(braket
id|slp-&gt;nitems
op_increment
)braket
op_assign
id|s
suffix:semicolon
)brace
multiline_comment|/* Compare two strings given by reference.  */
r_static
r_int
DECL|function|cmp_string
id|cmp_string
(paren
r_const
r_void
op_star
id|pstr1
comma
r_const
r_void
op_star
id|pstr2
)paren
(brace
r_const
r_char
op_star
id|str1
op_assign
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|pstr1
suffix:semicolon
r_const
r_char
op_star
id|str2
op_assign
op_star
(paren
r_const
r_char
op_star
op_star
)paren
id|pstr2
suffix:semicolon
r_return
id|strcmp
(paren
id|str1
comma
id|str2
)paren
suffix:semicolon
)brace
multiline_comment|/* Sort a list of strings.  */
r_static
r_inline
r_void
DECL|function|string_list_sort
id|string_list_sort
(paren
id|string_list_ty
op_star
id|slp
)paren
(brace
r_if
c_cond
(paren
id|slp-&gt;nitems
OG
l_int|0
)paren
id|qsort
(paren
id|slp-&gt;item
comma
id|slp-&gt;nitems
comma
r_sizeof
(paren
id|slp-&gt;item
(braket
l_int|0
)braket
)paren
comma
id|cmp_string
)paren
suffix:semicolon
)brace
multiline_comment|/* Test whether a sorted string list contains a given string.  */
r_static
r_int
DECL|function|sorted_string_list_member
id|sorted_string_list_member
(paren
r_const
id|string_list_ty
op_star
id|slp
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|j1
comma
id|j2
suffix:semicolon
id|j1
op_assign
l_int|0
suffix:semicolon
id|j2
op_assign
id|slp-&gt;nitems
suffix:semicolon
r_if
c_cond
(paren
id|j2
OG
l_int|0
)paren
(brace
multiline_comment|/* Binary search.  */
r_while
c_loop
(paren
id|j2
id|j1
OG
l_int|1
)paren
(brace
multiline_comment|/* Here we know that if s is in the list, it is at an index j&n;&t;     with j1 &lt;= j &lt; j2.  */
r_int
id|j
op_assign
(paren
id|j1
op_plus
id|j2
)paren
op_rshift
l_int|1
suffix:semicolon
r_int
id|result
op_assign
id|strcmp
(paren
id|slp-&gt;item
(braket
id|j
)braket
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
id|j2
op_assign
id|j
suffix:semicolon
r_else
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_else
id|j1
op_assign
id|j
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j2
OG
id|j1
)paren
r_if
c_cond
(paren
id|strcmp
(paren
id|slp-&gt;item
(braket
id|j1
)braket
comma
id|s
)paren
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set of variables on which to perform substitution.&n;   Used only if !all_variables.  */
DECL|variable|variables_set
r_static
id|string_list_ty
id|variables_set
suffix:semicolon
multiline_comment|/* Adds a variable to variables_set.  */
r_static
r_void
DECL|function|note_variable
id|note_variable
(paren
r_const
r_char
op_star
id|var_ptr
comma
r_int
id|var_len
)paren
(brace
r_char
op_star
id|string
op_assign
id|xmemdupz
(paren
id|var_ptr
comma
id|var_len
)paren
suffix:semicolon
id|string_list_append
(paren
op_amp
id|variables_set
comma
id|string
)paren
suffix:semicolon
)brace
multiline_comment|/* Stores the variables occurring in the string in variables_set.  */
r_static
r_void
DECL|function|note_variables
id|note_variables
(paren
r_const
r_char
op_star
id|string
)paren
(brace
id|string_list_init
(paren
op_amp
id|variables_set
)paren
suffix:semicolon
id|find_variables
(paren
id|string
comma
op_amp
id|note_variable
)paren
suffix:semicolon
id|string_list_sort
(paren
op_amp
id|variables_set
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_getc
id|do_getc
(paren
r_void
)paren
(brace
r_int
id|c
op_assign
id|getc
(paren
id|stdin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
(brace
r_if
c_cond
(paren
id|ferror
(paren
id|stdin
)paren
)paren
id|error
(paren
l_string|&quot;error while reading standard input&quot;
)paren
suffix:semicolon
)brace
r_return
id|c
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|do_ungetc
id|do_ungetc
(paren
r_int
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
op_ne
id|EOF
)paren
id|ungetc
(paren
id|c
comma
id|stdin
)paren
suffix:semicolon
)brace
multiline_comment|/* Copies stdin to stdout, performing substitutions.  */
r_static
r_void
DECL|function|subst_from_stdin
id|subst_from_stdin
(paren
r_void
)paren
(brace
r_static
r_char
op_star
id|buffer
suffix:semicolon
r_static
r_int
id|bufmax
suffix:semicolon
r_static
r_int
id|buflen
suffix:semicolon
r_int
id|c
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|c
op_assign
id|do_getc
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|EOF
)paren
r_break
suffix:semicolon
multiline_comment|/* Look for $VARIABLE or ${VARIABLE}.  */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;$&squot;
)paren
(brace
r_int
r_int
r_int
id|opening_brace
op_assign
l_int|0
suffix:semicolon
r_int
r_int
r_int
id|closing_brace
op_assign
l_int|0
suffix:semicolon
id|c
op_assign
id|do_getc
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;{&squot;
)paren
(brace
id|opening_brace
op_assign
l_int|1
suffix:semicolon
id|c
op_assign
id|do_getc
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
id|c
op_eq
l_char|&squot;_&squot;
)paren
(brace
r_int
r_int
r_int
id|valid
suffix:semicolon
multiline_comment|/* Accumulate the VARIABLE in buffer.  */
id|buflen
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|buflen
op_ge
id|bufmax
)paren
(brace
id|bufmax
op_assign
l_int|2
op_star
id|bufmax
op_plus
l_int|10
suffix:semicolon
id|buffer
op_assign
id|xrealloc
(paren
id|buffer
comma
id|bufmax
)paren
suffix:semicolon
)brace
id|buffer
(braket
id|buflen
op_increment
)braket
op_assign
id|c
suffix:semicolon
id|c
op_assign
id|do_getc
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;Z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;z&squot;
)paren
op_logical_or
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
op_logical_or
id|c
op_eq
l_char|&squot;_&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opening_brace
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;}&squot;
)paren
(brace
id|closing_brace
op_assign
l_int|1
suffix:semicolon
id|valid
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|valid
op_assign
l_int|0
suffix:semicolon
id|do_ungetc
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|valid
op_assign
l_int|1
suffix:semicolon
id|do_ungetc
(paren
id|c
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|valid
)paren
(brace
multiline_comment|/* Terminate the variable in the buffer.  */
r_if
c_cond
(paren
id|buflen
op_ge
id|bufmax
)paren
(brace
id|bufmax
op_assign
l_int|2
op_star
id|bufmax
op_plus
l_int|10
suffix:semicolon
id|buffer
op_assign
id|xrealloc
(paren
id|buffer
comma
id|bufmax
)paren
suffix:semicolon
)brace
id|buffer
(braket
id|buflen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Test whether the variable shall be substituted.  */
r_if
c_cond
(paren
op_logical_neg
id|all_variables
op_logical_and
op_logical_neg
id|sorted_string_list_member
(paren
op_amp
id|variables_set
comma
id|buffer
)paren
)paren
id|valid
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|valid
)paren
(brace
multiline_comment|/* Substitute the variable&squot;s value from the environment.  */
r_const
r_char
op_star
id|env_value
op_assign
id|getenv
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|env_value
op_ne
l_int|NULL
)paren
id|fputs
(paren
id|env_value
comma
id|stdout
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Perform no substitution at all.  Since the buffered input&n;&t;&t;     contains no other &squot;$&squot; than at the start, we can just&n;&t;&t;     output all the buffered contents.  */
id|putchar
(paren
l_char|&squot;$&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opening_brace
)paren
id|putchar
(paren
l_char|&squot;{&squot;
)paren
suffix:semicolon
id|fwrite
(paren
id|buffer
comma
id|buflen
comma
l_int|1
comma
id|stdout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|closing_brace
)paren
id|putchar
(paren
l_char|&squot;}&squot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|do_ungetc
(paren
id|c
)paren
suffix:semicolon
id|putchar
(paren
l_char|&squot;$&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opening_brace
)paren
id|putchar
(paren
l_char|&squot;{&squot;
)paren
suffix:semicolon
)brace
)brace
r_else
id|putchar
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
eof
