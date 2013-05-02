macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;compat/terminal.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#if defined(HAVE_DEV_TTY) || defined(GIT_WINDOWS_NATIVE)
r_static
r_void
id|restore_term
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|restore_term_on_signal
r_static
r_void
id|restore_term_on_signal
c_func
(paren
r_int
id|sig
)paren
(brace
id|restore_term
c_func
(paren
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|sig
)paren
suffix:semicolon
id|raise
c_func
(paren
id|sig
)paren
suffix:semicolon
)brace
macro_line|#ifdef HAVE_DEV_TTY
DECL|macro|INPUT_PATH
mdefine_line|#define INPUT_PATH &quot;/dev/tty&quot;
DECL|macro|OUTPUT_PATH
mdefine_line|#define OUTPUT_PATH &quot;/dev/tty&quot;
DECL|variable|term_fd
r_static
r_int
id|term_fd
op_assign
l_int|1
suffix:semicolon
DECL|variable|old_term
r_static
r_struct
id|termios
id|old_term
suffix:semicolon
DECL|function|restore_term
r_static
r_void
id|restore_term
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|term_fd
OL
l_int|0
)paren
r_return
suffix:semicolon
id|tcsetattr
c_func
(paren
id|term_fd
comma
id|TCSAFLUSH
comma
op_amp
id|old_term
)paren
suffix:semicolon
id|close
c_func
(paren
id|term_fd
)paren
suffix:semicolon
id|term_fd
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|disable_echo
r_static
r_int
id|disable_echo
c_func
(paren
r_void
)paren
(brace
r_struct
id|termios
id|t
suffix:semicolon
id|term_fd
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/tty&quot;
comma
id|O_RDWR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcgetattr
c_func
(paren
id|term_fd
comma
op_amp
id|t
)paren
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|old_term
op_assign
id|t
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|restore_term_on_signal
)paren
suffix:semicolon
id|t.c_lflag
op_and_assign
op_complement
id|ECHO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tcsetattr
c_func
(paren
id|term_fd
comma
id|TCSAFLUSH
comma
op_amp
id|t
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|close
c_func
(paren
id|term_fd
)paren
suffix:semicolon
id|term_fd
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#elif defined(GIT_WINDOWS_NATIVE)
DECL|macro|INPUT_PATH
mdefine_line|#define INPUT_PATH &quot;CONIN$&quot;
DECL|macro|OUTPUT_PATH
mdefine_line|#define OUTPUT_PATH &quot;CONOUT$&quot;
DECL|macro|FORCE_TEXT
mdefine_line|#define FORCE_TEXT &quot;t&quot;
DECL|variable|hconin
r_static
id|HANDLE
id|hconin
op_assign
id|INVALID_HANDLE_VALUE
suffix:semicolon
DECL|variable|cmode
r_static
id|DWORD
id|cmode
suffix:semicolon
DECL|function|restore_term
r_static
r_void
id|restore_term
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|hconin
op_eq
id|INVALID_HANDLE_VALUE
)paren
r_return
suffix:semicolon
id|SetConsoleMode
c_func
(paren
id|hconin
comma
id|cmode
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|hconin
)paren
suffix:semicolon
id|hconin
op_assign
id|INVALID_HANDLE_VALUE
suffix:semicolon
)brace
DECL|function|disable_echo
r_static
r_int
id|disable_echo
c_func
(paren
r_void
)paren
(brace
id|hconin
op_assign
id|CreateFile
c_func
(paren
l_string|&quot;CONIN$&quot;
comma
id|GENERIC_READ
op_or
id|GENERIC_WRITE
comma
id|FILE_SHARE_READ
comma
l_int|NULL
comma
id|OPEN_EXISTING
comma
id|FILE_ATTRIBUTE_NORMAL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hconin
op_eq
id|INVALID_HANDLE_VALUE
)paren
r_return
l_int|1
suffix:semicolon
id|GetConsoleMode
c_func
(paren
id|hconin
comma
op_amp
id|cmode
)paren
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|restore_term_on_signal
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SetConsoleMode
c_func
(paren
id|hconin
comma
id|cmode
op_amp
(paren
op_complement
id|ENABLE_ECHO_INPUT
)paren
)paren
)paren
(brace
id|CloseHandle
c_func
(paren
id|hconin
)paren
suffix:semicolon
id|hconin
op_assign
id|INVALID_HANDLE_VALUE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef FORCE_TEXT
DECL|macro|FORCE_TEXT
mdefine_line|#define FORCE_TEXT
macro_line|#endif
DECL|function|git_terminal_prompt
r_char
op_star
id|git_terminal_prompt
c_func
(paren
r_const
r_char
op_star
id|prompt
comma
r_int
id|echo
)paren
(brace
r_static
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|r
suffix:semicolon
id|FILE
op_star
id|input_fh
comma
op_star
id|output_fh
suffix:semicolon
id|input_fh
op_assign
id|fopen
c_func
(paren
id|INPUT_PATH
comma
l_string|&quot;r&quot;
id|FORCE_TEXT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|input_fh
)paren
r_return
l_int|NULL
suffix:semicolon
id|output_fh
op_assign
id|fopen
c_func
(paren
id|OUTPUT_PATH
comma
l_string|&quot;w&quot;
id|FORCE_TEXT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|output_fh
)paren
(brace
id|fclose
c_func
(paren
id|input_fh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|echo
op_logical_and
id|disable_echo
c_func
(paren
)paren
)paren
(brace
id|fclose
c_func
(paren
id|input_fh
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|output_fh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|fputs
c_func
(paren
id|prompt
comma
id|output_fh
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|output_fh
)paren
suffix:semicolon
id|r
op_assign
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|input_fh
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|echo
)paren
(brace
id|putc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|output_fh
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|output_fh
)paren
suffix:semicolon
)brace
id|restore_term
c_func
(paren
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|input_fh
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|output_fh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
id|EOF
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|buf.buf
suffix:semicolon
)brace
macro_line|#else
DECL|function|git_terminal_prompt
r_char
op_star
id|git_terminal_prompt
c_func
(paren
r_const
r_char
op_star
id|prompt
comma
r_int
id|echo
)paren
(brace
r_return
id|getpass
c_func
(paren
id|prompt
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
