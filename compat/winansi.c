multiline_comment|/*&n; * Copyright 2008 Peter Harris &lt;git@peter.is-a-geek.org&gt;&n; */
macro_line|#include &lt;windows.h&gt;
macro_line|#include &quot;../git-compat-util.h&quot;
multiline_comment|/*&n; Functions to be wrapped:&n;*/
DECL|macro|printf
macro_line|#undef printf
DECL|macro|fprintf
macro_line|#undef fprintf
DECL|macro|fputs
macro_line|#undef fputs
multiline_comment|/* TODO: write */
multiline_comment|/*&n; ANSI codes used by git: m, K&n;&n; This file is git-specific. Therefore, this file does not attempt&n; to implement any codes that are not used by git.&n;*/
DECL|variable|console
r_static
id|HANDLE
id|console
suffix:semicolon
DECL|variable|plain_attr
r_static
id|WORD
id|plain_attr
suffix:semicolon
DECL|variable|attr
r_static
id|WORD
id|attr
suffix:semicolon
DECL|variable|negative
r_static
r_int
id|negative
suffix:semicolon
DECL|function|init
r_static
r_void
id|init
c_func
(paren
r_void
)paren
(brace
id|CONSOLE_SCREEN_BUFFER_INFO
id|sbi
suffix:semicolon
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|initialized
)paren
r_return
suffix:semicolon
id|console
op_assign
id|GetStdHandle
c_func
(paren
id|STD_OUTPUT_HANDLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|console
op_eq
id|INVALID_HANDLE_VALUE
)paren
id|console
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|console
)paren
r_return
suffix:semicolon
id|GetConsoleScreenBufferInfo
c_func
(paren
id|console
comma
op_amp
id|sbi
)paren
suffix:semicolon
id|attr
op_assign
id|plain_attr
op_assign
id|sbi.wAttributes
suffix:semicolon
id|negative
op_assign
l_int|0
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
DECL|macro|FOREGROUND_ALL
mdefine_line|#define FOREGROUND_ALL (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
DECL|macro|BACKGROUND_ALL
mdefine_line|#define BACKGROUND_ALL (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
DECL|function|set_console_attr
r_static
r_void
id|set_console_attr
c_func
(paren
r_void
)paren
(brace
id|WORD
id|attributes
op_assign
id|attr
suffix:semicolon
r_if
c_cond
(paren
id|negative
)paren
(brace
id|attributes
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attributes
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
multiline_comment|/* This could probably use a bitmask&n;&t;&t;   instead of a series of ifs */
r_if
c_cond
(paren
id|attr
op_amp
id|FOREGROUND_RED
)paren
id|attributes
op_or_assign
id|BACKGROUND_RED
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|FOREGROUND_GREEN
)paren
id|attributes
op_or_assign
id|BACKGROUND_GREEN
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|FOREGROUND_BLUE
)paren
id|attributes
op_or_assign
id|BACKGROUND_BLUE
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|BACKGROUND_RED
)paren
id|attributes
op_or_assign
id|FOREGROUND_RED
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|BACKGROUND_GREEN
)paren
id|attributes
op_or_assign
id|FOREGROUND_GREEN
suffix:semicolon
r_if
c_cond
(paren
id|attr
op_amp
id|BACKGROUND_BLUE
)paren
id|attributes
op_or_assign
id|FOREGROUND_BLUE
suffix:semicolon
)brace
id|SetConsoleTextAttribute
c_func
(paren
id|console
comma
id|attributes
)paren
suffix:semicolon
)brace
DECL|function|erase_in_line
r_static
r_void
id|erase_in_line
c_func
(paren
r_void
)paren
(brace
id|CONSOLE_SCREEN_BUFFER_INFO
id|sbi
suffix:semicolon
id|DWORD
id|dummy
suffix:semicolon
multiline_comment|/* Needed for Windows 7 (or Vista) regression */
r_if
c_cond
(paren
op_logical_neg
id|console
)paren
r_return
suffix:semicolon
id|GetConsoleScreenBufferInfo
c_func
(paren
id|console
comma
op_amp
id|sbi
)paren
suffix:semicolon
id|FillConsoleOutputCharacterA
c_func
(paren
id|console
comma
l_char|&squot; &squot;
comma
id|sbi.dwSize.X
id|sbi.dwCursorPosition.X
comma
id|sbi.dwCursorPosition
comma
op_amp
id|dummy
)paren
suffix:semicolon
)brace
DECL|function|set_attr
r_static
r_const
r_char
op_star
id|set_attr
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_const
r_char
op_star
id|func
suffix:semicolon
r_int
id|len
op_assign
id|strspn
c_func
(paren
id|str
comma
l_string|&quot;0123456789;&quot;
)paren
suffix:semicolon
id|func
op_assign
id|str
op_plus
id|len
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|func
)paren
(brace
r_case
l_char|&squot;m&squot;
suffix:colon
r_do
(brace
r_int
id|val
op_assign
id|strtol
c_func
(paren
id|str
comma
(paren
r_char
op_star
op_star
)paren
op_amp
id|str
comma
l_int|10
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|val
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* reset */
id|attr
op_assign
id|plain_attr
suffix:semicolon
id|negative
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* bold */
id|attr
op_or_assign
id|FOREGROUND_INTENSITY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* faint */
r_case
l_int|22
suffix:colon
multiline_comment|/* normal */
id|attr
op_and_assign
op_complement
id|FOREGROUND_INTENSITY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* italic */
multiline_comment|/* Unsupported */
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* underline */
r_case
l_int|21
suffix:colon
multiline_comment|/* double underline */
multiline_comment|/* Wikipedia says this flag does nothing */
multiline_comment|/* Furthermore, mingw doesn&squot;t define this flag&n;&t;&t;&t;&t;attr |= COMMON_LVB_UNDERSCORE; */
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
multiline_comment|/* no underline */
multiline_comment|/* attr &amp;= ~COMMON_LVB_UNDERSCORE; */
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* slow blink */
r_case
l_int|6
suffix:colon
multiline_comment|/* fast blink */
multiline_comment|/* We don&squot;t have blink, but we do have&n;&t;&t;&t;&t;   background intensity */
id|attr
op_or_assign
id|BACKGROUND_INTENSITY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
multiline_comment|/* no blink */
id|attr
op_and_assign
op_complement
id|BACKGROUND_INTENSITY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* negative */
id|negative
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|27
suffix:colon
multiline_comment|/* positive */
id|negative
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/* conceal */
r_case
l_int|28
suffix:colon
multiline_comment|/* reveal */
multiline_comment|/* Unsupported */
r_break
suffix:semicolon
r_case
l_int|30
suffix:colon
multiline_comment|/* Black */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|31
suffix:colon
multiline_comment|/* Red */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|FOREGROUND_RED
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
multiline_comment|/* Green */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|FOREGROUND_GREEN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|33
suffix:colon
multiline_comment|/* Yellow */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|FOREGROUND_RED
op_or
id|FOREGROUND_GREEN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|34
suffix:colon
multiline_comment|/* Blue */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|FOREGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|35
suffix:colon
multiline_comment|/* Magenta */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|FOREGROUND_RED
op_or
id|FOREGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|36
suffix:colon
multiline_comment|/* Cyan */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|FOREGROUND_GREEN
op_or
id|FOREGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|37
suffix:colon
multiline_comment|/* White */
id|attr
op_or_assign
id|FOREGROUND_RED
op_or
id|FOREGROUND_GREEN
op_or
id|FOREGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38
suffix:colon
multiline_comment|/* Unknown */
r_break
suffix:semicolon
r_case
l_int|39
suffix:colon
multiline_comment|/* reset */
id|attr
op_and_assign
op_complement
id|FOREGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
(paren
id|plain_attr
op_amp
id|FOREGROUND_ALL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|40
suffix:colon
multiline_comment|/* Black */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|41
suffix:colon
multiline_comment|/* Red */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|BACKGROUND_RED
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|42
suffix:colon
multiline_comment|/* Green */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|BACKGROUND_GREEN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|43
suffix:colon
multiline_comment|/* Yellow */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|BACKGROUND_RED
op_or
id|BACKGROUND_GREEN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|44
suffix:colon
multiline_comment|/* Blue */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|BACKGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|45
suffix:colon
multiline_comment|/* Magenta */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|BACKGROUND_RED
op_or
id|BACKGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|46
suffix:colon
multiline_comment|/* Cyan */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
id|BACKGROUND_GREEN
op_or
id|BACKGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|47
suffix:colon
multiline_comment|/* White */
id|attr
op_or_assign
id|BACKGROUND_RED
op_or
id|BACKGROUND_GREEN
op_or
id|BACKGROUND_BLUE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48
suffix:colon
multiline_comment|/* Unknown */
r_break
suffix:semicolon
r_case
l_int|49
suffix:colon
multiline_comment|/* reset */
id|attr
op_and_assign
op_complement
id|BACKGROUND_ALL
suffix:semicolon
id|attr
op_or_assign
(paren
id|plain_attr
op_amp
id|BACKGROUND_ALL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unsupported code */
r_break
suffix:semicolon
)brace
id|str
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
(paren
id|str
op_minus
l_int|1
)paren
op_eq
l_char|&squot;;&squot;
)paren
suffix:semicolon
id|set_console_attr
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;K&squot;
suffix:colon
id|erase_in_line
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unsupported code */
r_break
suffix:semicolon
)brace
r_return
id|func
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|ansi_emulate
r_static
r_int
id|ansi_emulate
c_func
(paren
r_const
r_char
op_star
id|str
comma
id|FILE
op_star
id|stream
)paren
(brace
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|pos
op_assign
id|str
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pos
)paren
(brace
id|pos
op_assign
id|strstr
c_func
(paren
id|str
comma
l_string|&quot;&bslash;033[&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
)paren
(brace
r_int
id|len
op_assign
id|pos
id|str
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_int
id|out_len
op_assign
id|fwrite
c_func
(paren
id|str
comma
l_int|1
comma
id|len
comma
id|stream
)paren
suffix:semicolon
id|rv
op_add_assign
id|out_len
suffix:semicolon
r_if
c_cond
(paren
id|out_len
OL
id|len
)paren
r_return
id|rv
suffix:semicolon
)brace
id|str
op_assign
id|pos
op_plus
l_int|2
suffix:semicolon
id|rv
op_add_assign
l_int|2
suffix:semicolon
id|fflush
c_func
(paren
id|stream
)paren
suffix:semicolon
id|pos
op_assign
id|set_attr
c_func
(paren
id|str
)paren
suffix:semicolon
id|rv
op_add_assign
id|pos
id|str
suffix:semicolon
id|str
op_assign
id|pos
suffix:semicolon
)brace
r_else
(brace
id|rv
op_add_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
id|fputs
c_func
(paren
id|str
comma
id|stream
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
)brace
r_return
id|rv
suffix:semicolon
)brace
DECL|function|winansi_fputs
r_int
id|winansi_fputs
c_func
(paren
r_const
r_char
op_star
id|str
comma
id|FILE
op_star
id|stream
)paren
(brace
r_int
id|rv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isatty
c_func
(paren
id|fileno
c_func
(paren
id|stream
)paren
)paren
)paren
r_return
id|fputs
c_func
(paren
id|str
comma
id|stream
)paren
suffix:semicolon
id|init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|console
)paren
r_return
id|fputs
c_func
(paren
id|str
comma
id|stream
)paren
suffix:semicolon
id|rv
op_assign
id|ansi_emulate
c_func
(paren
id|str
comma
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ge
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
id|EOF
suffix:semicolon
)brace
DECL|function|winansi_vfprintf
r_static
r_int
id|winansi_vfprintf
c_func
(paren
id|FILE
op_star
id|stream
comma
r_const
r_char
op_star
id|format
comma
id|va_list
id|list
)paren
(brace
r_int
id|len
comma
id|rv
suffix:semicolon
r_char
id|small_buf
(braket
l_int|256
)braket
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|small_buf
suffix:semicolon
id|va_list
id|cp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isatty
c_func
(paren
id|fileno
c_func
(paren
id|stream
)paren
)paren
)paren
r_goto
m_abort
suffix:semicolon
id|init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|console
)paren
r_goto
m_abort
suffix:semicolon
id|va_copy
c_func
(paren
id|cp
comma
id|list
)paren
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|small_buf
comma
r_sizeof
(paren
id|small_buf
)paren
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
id|len
OG
r_sizeof
(paren
id|small_buf
)paren
l_int|1
)paren
(brace
id|buf
op_assign
id|malloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_goto
m_abort
suffix:semicolon
id|len
op_assign
id|vsnprintf
c_func
(paren
id|buf
comma
id|len
op_plus
l_int|1
comma
id|format
comma
id|list
)paren
suffix:semicolon
)brace
id|rv
op_assign
id|ansi_emulate
c_func
(paren
id|buf
comma
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_ne
id|small_buf
)paren
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
m_abort
suffix:colon
id|rv
op_assign
id|vfprintf
c_func
(paren
id|stream
comma
id|format
comma
id|list
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|winansi_fprintf
r_int
id|winansi_fprintf
c_func
(paren
id|FILE
op_star
id|stream
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
id|list
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|format
)paren
suffix:semicolon
id|rv
op_assign
id|winansi_vfprintf
c_func
(paren
id|stream
comma
id|format
comma
id|list
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|winansi_printf
r_int
id|winansi_printf
c_func
(paren
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
id|list
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|format
)paren
suffix:semicolon
id|rv
op_assign
id|winansi_vfprintf
c_func
(paren
id|stdout
comma
id|format
comma
id|list
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
eof
