multiline_comment|/*&n; * Copyright 2008 Peter Harris &lt;git@peter.is-a-geek.org&gt;&n; */
DECL|macro|NOGDI
macro_line|#undef NOGDI
macro_line|#include &quot;../git-compat-util.h&quot;
macro_line|#include &lt;wingdi.h&gt;
macro_line|#include &lt;winreg.h&gt;
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
DECL|variable|non_ascii_used
r_static
r_int
id|non_ascii_used
op_assign
l_int|0
suffix:semicolon
DECL|variable|hthread
DECL|variable|hread
DECL|variable|hwrite
r_static
id|HANDLE
id|hthread
comma
id|hread
comma
id|hwrite
suffix:semicolon
DECL|variable|hconsole1
DECL|variable|hconsole2
r_static
id|HANDLE
id|hconsole1
comma
id|hconsole2
suffix:semicolon
macro_line|#ifdef __MINGW32__
DECL|struct|_CONSOLE_FONT_INFOEX
r_typedef
r_struct
id|_CONSOLE_FONT_INFOEX
(brace
DECL|member|cbSize
id|ULONG
id|cbSize
suffix:semicolon
DECL|member|nFont
id|DWORD
id|nFont
suffix:semicolon
DECL|member|dwFontSize
id|COORD
id|dwFontSize
suffix:semicolon
DECL|member|FontFamily
id|UINT
id|FontFamily
suffix:semicolon
DECL|member|FontWeight
id|UINT
id|FontWeight
suffix:semicolon
DECL|member|FaceName
id|WCHAR
id|FaceName
(braket
id|LF_FACESIZE
)braket
suffix:semicolon
DECL|typedef|CONSOLE_FONT_INFOEX
DECL|typedef|PCONSOLE_FONT_INFOEX
)brace
id|CONSOLE_FONT_INFOEX
comma
op_star
id|PCONSOLE_FONT_INFOEX
suffix:semicolon
macro_line|#endif
DECL|typedef|PGETCURRENTCONSOLEFONTEX
r_typedef
id|BOOL
(paren
id|WINAPI
op_star
id|PGETCURRENTCONSOLEFONTEX
)paren
(paren
id|HANDLE
comma
id|BOOL
comma
id|PCONSOLE_FONT_INFOEX
)paren
suffix:semicolon
DECL|function|warn_if_raster_font
r_static
r_void
id|warn_if_raster_font
c_func
(paren
r_void
)paren
(brace
id|DWORD
id|fontFamily
op_assign
l_int|0
suffix:semicolon
id|PGETCURRENTCONSOLEFONTEX
id|pGetCurrentConsoleFontEx
suffix:semicolon
multiline_comment|/* don&squot;t bother if output was ascii only */
r_if
c_cond
(paren
op_logical_neg
id|non_ascii_used
)paren
r_return
suffix:semicolon
multiline_comment|/* GetCurrentConsoleFontEx is available since Vista */
id|pGetCurrentConsoleFontEx
op_assign
(paren
id|PGETCURRENTCONSOLEFONTEX
)paren
id|GetProcAddress
c_func
(paren
id|GetModuleHandle
c_func
(paren
l_string|&quot;kernel32.dll&quot;
)paren
comma
l_string|&quot;GetCurrentConsoleFontEx&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pGetCurrentConsoleFontEx
)paren
(brace
id|CONSOLE_FONT_INFOEX
id|cfi
suffix:semicolon
id|cfi.cbSize
op_assign
r_sizeof
(paren
id|cfi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pGetCurrentConsoleFontEx
c_func
(paren
id|console
comma
l_int|0
comma
op_amp
id|cfi
)paren
)paren
id|fontFamily
op_assign
id|cfi.FontFamily
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* pre-Vista: check default console font in registry */
id|HKEY
id|hkey
suffix:semicolon
r_if
c_cond
(paren
id|ERROR_SUCCESS
op_eq
id|RegOpenKeyExA
c_func
(paren
id|HKEY_CURRENT_USER
comma
l_string|&quot;Console&quot;
comma
l_int|0
comma
id|KEY_READ
comma
op_amp
id|hkey
)paren
)paren
(brace
id|DWORD
id|size
op_assign
r_sizeof
(paren
id|fontFamily
)paren
suffix:semicolon
id|RegQueryValueExA
c_func
(paren
id|hkey
comma
l_string|&quot;FontFamily&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
(paren
id|LPVOID
)paren
op_amp
id|fontFamily
comma
op_amp
id|size
)paren
suffix:semicolon
id|RegCloseKey
c_func
(paren
id|hkey
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|fontFamily
op_amp
id|TMPF_TRUETYPE
)paren
)paren
(brace
r_const
m_wchar_t
op_star
id|msg
op_assign
id|L
l_string|&quot;&bslash;nWarning: Your console font probably &quot;
id|L
l_string|&quot;doesn&bslash;&squot;t support Unicode. If you experience strange &quot;
id|L
l_string|&quot;characters in the output, consider switching to a &quot;
id|L
l_string|&quot;TrueType font such as Consolas!&bslash;n&quot;
suffix:semicolon
id|DWORD
id|dummy
suffix:semicolon
id|WriteConsoleW
c_func
(paren
id|console
comma
id|msg
comma
id|wcslen
c_func
(paren
id|msg
)paren
comma
op_amp
id|dummy
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
DECL|function|is_console
r_static
r_int
id|is_console
c_func
(paren
r_int
id|fd
)paren
(brace
id|CONSOLE_SCREEN_BUFFER_INFO
id|sbi
suffix:semicolon
id|HANDLE
id|hcon
suffix:semicolon
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* get OS handle of the file descriptor */
id|hcon
op_assign
(paren
id|HANDLE
)paren
id|_get_osfhandle
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hcon
op_eq
id|INVALID_HANDLE_VALUE
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check if its a device (i.e. console, printer, serial port) */
r_if
c_cond
(paren
id|GetFileType
c_func
(paren
id|hcon
)paren
op_ne
id|FILE_TYPE_CHAR
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check if its a handle to a console output screen buffer */
r_if
c_cond
(paren
op_logical_neg
id|GetConsoleScreenBufferInfo
c_func
(paren
id|hcon
comma
op_amp
id|sbi
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* initialize attributes */
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
id|console
op_assign
id|hcon
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
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE 4096
DECL|macro|MAX_PARAMS
mdefine_line|#define MAX_PARAMS 16
DECL|function|write_console
r_static
r_void
id|write_console
c_func
(paren
r_int
r_char
op_star
id|str
comma
r_int
id|len
)paren
(brace
multiline_comment|/* only called from console_thread, so a static buffer will do */
r_static
m_wchar_t
id|wbuf
(braket
l_int|2
op_star
id|BUFFER_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
id|DWORD
id|dummy
suffix:semicolon
multiline_comment|/* convert utf-8 to utf-16 */
r_int
id|wlen
op_assign
id|xutftowcsn
c_func
(paren
id|wbuf
comma
(paren
r_char
op_star
)paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|wbuf
)paren
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* write directly to console */
id|WriteConsoleW
c_func
(paren
id|console
comma
id|wbuf
comma
id|wlen
comma
op_amp
id|dummy
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* remember if non-ascii characters are printed */
r_if
c_cond
(paren
id|wlen
op_ne
id|len
)paren
id|non_ascii_used
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
r_void
id|set_attr
c_func
(paren
r_char
id|func
comma
r_const
r_int
op_star
id|params
comma
r_int
id|paramlen
)paren
(brace
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
l_char|&squot;m&squot;
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|paramlen
suffix:semicolon
id|i
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|params
(braket
id|i
)braket
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
)brace
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
)brace
r_enum
(brace
DECL|enumerator|TEXT
DECL|enumerator|ESCAPE
DECL|enumerator|BRACKET
id|TEXT
op_assign
l_int|0
comma
id|ESCAPE
op_assign
l_int|033
comma
id|BRACKET
op_assign
l_char|&squot;[&squot;
)brace
suffix:semicolon
DECL|function|console_thread
r_static
id|DWORD
id|WINAPI
id|console_thread
c_func
(paren
id|LPVOID
id|unused
)paren
(brace
r_int
r_char
id|buffer
(braket
id|BUFFER_SIZE
)braket
suffix:semicolon
id|DWORD
id|bytes
suffix:semicolon
r_int
id|start
comma
id|end
op_assign
l_int|0
comma
id|c
comma
id|parampos
op_assign
l_int|0
comma
id|state
op_assign
id|TEXT
suffix:semicolon
r_int
id|params
(braket
id|MAX_PARAMS
)braket
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* read next chunk of bytes from the pipe */
r_if
c_cond
(paren
op_logical_neg
id|ReadFile
c_func
(paren
id|hread
comma
id|buffer
op_plus
id|end
comma
id|BUFFER_SIZE
id|end
comma
op_amp
id|bytes
comma
l_int|NULL
)paren
)paren
(brace
multiline_comment|/* exit if pipe has been closed or disconnected */
r_if
c_cond
(paren
id|GetLastError
c_func
(paren
)paren
op_eq
id|ERROR_PIPE_NOT_CONNECTED
op_logical_or
id|GetLastError
c_func
(paren
)paren
op_eq
id|ERROR_BROKEN_PIPE
)paren
r_break
suffix:semicolon
multiline_comment|/* ignore other errors */
r_continue
suffix:semicolon
)brace
multiline_comment|/* scan the bytes and handle ANSI control codes */
id|bytes
op_add_assign
id|end
suffix:semicolon
id|start
op_assign
id|end
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|end
OL
id|bytes
)paren
(brace
id|c
op_assign
id|buffer
(braket
id|end
op_increment
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|TEXT
suffix:colon
r_if
c_cond
(paren
id|c
op_eq
id|ESCAPE
)paren
(brace
multiline_comment|/* print text seen so far */
r_if
c_cond
(paren
id|end
l_int|1
OG
id|start
)paren
id|write_console
c_func
(paren
id|buffer
op_plus
id|start
comma
id|end
l_int|1
id|start
)paren
suffix:semicolon
multiline_comment|/* then start parsing escape sequence */
id|start
op_assign
id|end
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|params
comma
l_int|0
comma
r_sizeof
(paren
id|params
)paren
)paren
suffix:semicolon
id|parampos
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
id|ESCAPE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ESCAPE
suffix:colon
multiline_comment|/* continue if &quot;&bslash;033[&quot;, otherwise bail out */
id|state
op_assign
(paren
id|c
op_eq
id|BRACKET
)paren
ques
c_cond
id|BRACKET
suffix:colon
id|TEXT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BRACKET
suffix:colon
multiline_comment|/* parse [0-9;]* into array of parameters */
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
(brace
id|params
(braket
id|parampos
)braket
op_mul_assign
l_int|10
suffix:semicolon
id|params
(braket
id|parampos
)braket
op_add_assign
id|c
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;;&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * next parameter, bail out if out of&n;&t;&t;&t;&t;&t; * bounds&n;&t;&t;&t;&t;&t; */
id|parampos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|parampos
op_ge
id|MAX_PARAMS
)paren
id|state
op_assign
id|TEXT
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * end of escape sequence, change&n;&t;&t;&t;&t;&t; * console attributes&n;&t;&t;&t;&t;&t; */
id|set_attr
c_func
(paren
id|c
comma
id|params
comma
id|parampos
op_plus
l_int|1
)paren
suffix:semicolon
id|start
op_assign
id|end
suffix:semicolon
id|state
op_assign
id|TEXT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* print remaining text unless parsing an escape sequence */
r_if
c_cond
(paren
id|state
op_eq
id|TEXT
op_logical_and
id|end
OG
id|start
)paren
(brace
multiline_comment|/* check for incomplete UTF-8 sequences and fix end */
r_if
c_cond
(paren
id|buffer
(braket
id|end
l_int|1
)braket
op_ge
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
id|end
l_int|1
)braket
op_ge
l_int|0xc0
)paren
id|end
op_decrement
suffix:semicolon
r_else
r_if
c_cond
(paren
id|end
l_int|1
OG
id|start
op_logical_and
id|buffer
(braket
id|end
l_int|2
)braket
op_ge
l_int|0xe0
)paren
id|end
op_sub_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|end
l_int|2
OG
id|start
op_logical_and
id|buffer
(braket
id|end
l_int|3
)braket
op_ge
l_int|0xf0
)paren
id|end
op_sub_assign
l_int|3
suffix:semicolon
)brace
multiline_comment|/* print remaining complete UTF-8 sequences */
r_if
c_cond
(paren
id|end
OG
id|start
)paren
id|write_console
c_func
(paren
id|buffer
op_plus
id|start
comma
id|end
id|start
)paren
suffix:semicolon
multiline_comment|/* move remaining bytes to the front */
r_if
c_cond
(paren
id|end
OL
id|bytes
)paren
id|memmove
c_func
(paren
id|buffer
comma
id|buffer
op_plus
id|end
comma
id|bytes
id|end
)paren
suffix:semicolon
id|end
op_assign
id|bytes
id|end
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* all data has been consumed, mark buffer empty */
id|end
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* check if the console font supports unicode */
id|warn_if_raster_font
c_func
(paren
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|hread
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|winansi_exit
r_static
r_void
id|winansi_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* flush all streams */
id|_flushall
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* signal console thread to exit */
id|FlushFileBuffers
c_func
(paren
id|hwrite
)paren
suffix:semicolon
id|DisconnectNamedPipe
c_func
(paren
id|hwrite
)paren
suffix:semicolon
multiline_comment|/* wait for console thread to copy remaining data */
id|WaitForSingleObject
c_func
(paren
id|hthread
comma
id|INFINITE
)paren
suffix:semicolon
multiline_comment|/* cleanup handles... */
id|CloseHandle
c_func
(paren
id|hwrite
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|hthread
)paren
suffix:semicolon
)brace
DECL|function|die_lasterr
r_static
r_void
id|die_lasterr
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|fmt
)paren
suffix:semicolon
id|errno
op_assign
id|err_win_to_posix
c_func
(paren
id|GetLastError
c_func
(paren
)paren
)paren
suffix:semicolon
id|die_errno
c_func
(paren
id|fmt
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
)brace
DECL|function|duplicate_handle
r_static
id|HANDLE
id|duplicate_handle
c_func
(paren
id|HANDLE
id|hnd
)paren
(brace
id|HANDLE
id|hresult
comma
id|hproc
op_assign
id|GetCurrentProcess
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DuplicateHandle
c_func
(paren
id|hproc
comma
id|hnd
comma
id|hproc
comma
op_amp
id|hresult
comma
l_int|0
comma
id|TRUE
comma
id|DUPLICATE_SAME_ACCESS
)paren
)paren
id|die_lasterr
c_func
(paren
l_string|&quot;DuplicateHandle(%li) failed&quot;
comma
(paren
r_int
)paren
id|hnd
)paren
suffix:semicolon
r_return
id|hresult
suffix:semicolon
)brace
multiline_comment|/*&n; * Make MSVCRT&squot;s internal file descriptor control structure accessible&n; * so that we can tweak OS handles and flags directly (we need MSVCRT&n; * to treat our pipe handle as if it were a console).&n; *&n; * We assume that the ioinfo structure (exposed by MSVCRT.dll via&n; * __pioinfo) starts with the OS handle and the flags. The exact size&n; * varies between MSVCRT versions, so we try different sizes until&n; * toggling the FDEV bit of _pioinfo(1)-&gt;osflags is reflected in&n; * isatty(1).&n; */
r_typedef
r_struct
(brace
DECL|member|osfhnd
id|HANDLE
id|osfhnd
suffix:semicolon
DECL|member|osflags
r_char
id|osflags
suffix:semicolon
DECL|typedef|ioinfo
)brace
id|ioinfo
suffix:semicolon
r_extern
id|__declspec
c_func
(paren
id|dllimport
)paren
id|ioinfo
op_star
id|__pioinfo
(braket
)braket
suffix:semicolon
DECL|variable|sizeof_ioinfo
r_static
r_int
id|sizeof_ioinfo
op_assign
l_int|0
suffix:semicolon
DECL|macro|IOINFO_L2E
mdefine_line|#define IOINFO_L2E 5
DECL|macro|IOINFO_ARRAY_ELTS
mdefine_line|#define IOINFO_ARRAY_ELTS (1 &lt;&lt; IOINFO_L2E)
DECL|macro|FDEV
mdefine_line|#define FDEV  0x40
DECL|function|_pioinfo
r_static
r_inline
id|ioinfo
op_star
id|_pioinfo
c_func
(paren
r_int
id|fd
)paren
(brace
r_return
(paren
id|ioinfo
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|__pioinfo
(braket
id|fd
op_rshift
id|IOINFO_L2E
)braket
op_plus
(paren
id|fd
op_amp
(paren
id|IOINFO_ARRAY_ELTS
l_int|1
)paren
)paren
op_star
id|sizeof_ioinfo
)paren
suffix:semicolon
)brace
DECL|function|init_sizeof_ioinfo
r_static
r_int
id|init_sizeof_ioinfo
c_func
(paren
)paren
(brace
r_int
id|istty
comma
id|wastty
suffix:semicolon
multiline_comment|/* don&squot;t init twice */
r_if
c_cond
(paren
id|sizeof_ioinfo
)paren
r_return
id|sizeof_ioinfo
op_ge
l_int|256
suffix:semicolon
id|sizeof_ioinfo
op_assign
r_sizeof
(paren
id|ioinfo
)paren
suffix:semicolon
id|wastty
op_assign
id|isatty
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sizeof_ioinfo
OL
l_int|256
)paren
(brace
multiline_comment|/* toggle FDEV flag, check isatty, then toggle back */
id|_pioinfo
c_func
(paren
l_int|1
)paren
op_member_access_from_pointer
id|osflags
op_xor_assign
id|FDEV
suffix:semicolon
id|istty
op_assign
id|isatty
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|_pioinfo
c_func
(paren
l_int|1
)paren
op_member_access_from_pointer
id|osflags
op_xor_assign
id|FDEV
suffix:semicolon
multiline_comment|/* return if we found the correct size */
r_if
c_cond
(paren
id|istty
op_ne
id|wastty
)paren
r_return
l_int|0
suffix:semicolon
id|sizeof_ioinfo
op_add_assign
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
)brace
id|error
c_func
(paren
l_string|&quot;Tweaking file descriptors doesn&squot;t work with this MSVCRT.dll&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|swap_osfhnd
r_static
id|HANDLE
id|swap_osfhnd
c_func
(paren
r_int
id|fd
comma
id|HANDLE
id|new_handle
)paren
(brace
id|ioinfo
op_star
id|pioinfo
suffix:semicolon
id|HANDLE
id|old_handle
suffix:semicolon
multiline_comment|/* init ioinfo size if we haven&squot;t done so */
r_if
c_cond
(paren
id|init_sizeof_ioinfo
c_func
(paren
)paren
)paren
r_return
id|INVALID_HANDLE_VALUE
suffix:semicolon
multiline_comment|/* get ioinfo pointer and change the handles */
id|pioinfo
op_assign
id|_pioinfo
c_func
(paren
id|fd
)paren
suffix:semicolon
id|old_handle
op_assign
id|pioinfo-&gt;osfhnd
suffix:semicolon
id|pioinfo-&gt;osfhnd
op_assign
id|new_handle
suffix:semicolon
r_return
id|old_handle
suffix:semicolon
)brace
DECL|function|winansi_init
r_void
id|winansi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|con1
comma
id|con2
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* check if either stdout or stderr is a console output screen buffer */
id|con1
op_assign
id|is_console
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|con2
op_assign
id|is_console
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|con1
op_logical_and
op_logical_neg
id|con2
)paren
r_return
suffix:semicolon
multiline_comment|/* create a named pipe to communicate with the console thread */
id|xsnprintf
c_func
(paren
id|name
comma
r_sizeof
(paren
id|name
)paren
comma
l_string|&quot;&bslash;&bslash;&bslash;&bslash;.&bslash;&bslash;pipe&bslash;&bslash;winansi%lu&quot;
comma
id|GetCurrentProcessId
c_func
(paren
)paren
)paren
suffix:semicolon
id|hwrite
op_assign
id|CreateNamedPipe
c_func
(paren
id|name
comma
id|PIPE_ACCESS_OUTBOUND
comma
id|PIPE_TYPE_BYTE
op_or
id|PIPE_WAIT
comma
l_int|1
comma
id|BUFFER_SIZE
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwrite
op_eq
id|INVALID_HANDLE_VALUE
)paren
id|die_lasterr
c_func
(paren
l_string|&quot;CreateNamedPipe failed&quot;
)paren
suffix:semicolon
id|hread
op_assign
id|CreateFile
c_func
(paren
id|name
comma
id|GENERIC_READ
comma
l_int|0
comma
l_int|NULL
comma
id|OPEN_EXISTING
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hread
op_eq
id|INVALID_HANDLE_VALUE
)paren
id|die_lasterr
c_func
(paren
l_string|&quot;CreateFile for named pipe failed&quot;
)paren
suffix:semicolon
multiline_comment|/* start console spool thread on the pipe&squot;s read end */
id|hthread
op_assign
id|CreateThread
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|console_thread
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hthread
op_eq
id|INVALID_HANDLE_VALUE
)paren
id|die_lasterr
c_func
(paren
l_string|&quot;CreateThread(console_thread) failed&quot;
)paren
suffix:semicolon
multiline_comment|/* schedule cleanup routine */
r_if
c_cond
(paren
id|atexit
c_func
(paren
id|winansi_exit
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;atexit(winansi_exit) failed&quot;
)paren
suffix:semicolon
multiline_comment|/* redirect stdout / stderr to the pipe */
r_if
c_cond
(paren
id|con1
)paren
id|hconsole1
op_assign
id|swap_osfhnd
c_func
(paren
l_int|1
comma
id|duplicate_handle
c_func
(paren
id|hwrite
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|con2
)paren
id|hconsole2
op_assign
id|swap_osfhnd
c_func
(paren
l_int|2
comma
id|duplicate_handle
c_func
(paren
id|hwrite
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns the real console handle if stdout / stderr is a pipe redirecting&n; * to the console. Allows spawn / exec to pass the console to the next process.&n; */
DECL|function|winansi_get_osfhandle
id|HANDLE
id|winansi_get_osfhandle
c_func
(paren
r_int
id|fd
)paren
(brace
id|HANDLE
id|hnd
op_assign
(paren
id|HANDLE
)paren
id|_get_osfhandle
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fd
op_eq
l_int|1
op_logical_or
id|fd
op_eq
l_int|2
)paren
op_logical_and
id|isatty
c_func
(paren
id|fd
)paren
op_logical_and
id|GetFileType
c_func
(paren
id|hnd
)paren
op_eq
id|FILE_TYPE_PIPE
)paren
r_return
(paren
id|fd
op_eq
l_int|1
)paren
ques
c_cond
id|hconsole1
suffix:colon
id|hconsole2
suffix:semicolon
r_return
id|hnd
suffix:semicolon
)brace
eof
