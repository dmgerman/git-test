macro_line|#include &quot;../git-compat-util.h&quot;
DECL|variable|_CRT_fmode
r_int
r_int
id|_CRT_fmode
op_assign
id|_O_BINARY
suffix:semicolon
DECL|macro|open
macro_line|#undef open
DECL|function|mingw_open
r_int
id|mingw_open
(paren
r_const
r_char
op_star
id|filename
comma
r_int
id|oflags
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|mode
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|oflags
)paren
suffix:semicolon
id|mode
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|filename
comma
l_string|&quot;/dev/null&quot;
)paren
)paren
id|filename
op_assign
l_string|&quot;nul&quot;
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|oflags
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_and
(paren
id|oflags
op_amp
id|O_CREAT
)paren
op_logical_and
id|errno
op_eq
id|EACCES
)paren
(brace
id|DWORD
id|attrs
op_assign
id|GetFileAttributes
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrs
op_ne
id|INVALID_FILE_ATTRIBUTES
op_logical_and
(paren
id|attrs
op_amp
id|FILE_ATTRIBUTE_DIRECTORY
)paren
)paren
id|errno
op_assign
id|EISDIR
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|sleep
r_int
r_int
id|sleep
(paren
r_int
r_int
id|seconds
)paren
(brace
id|Sleep
c_func
(paren
id|seconds
op_star
l_int|1000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mkstemp
r_int
id|mkstemp
c_func
(paren
r_char
op_star
r_template
)paren
(brace
r_char
op_star
id|filename
op_assign
id|mktemp
c_func
(paren
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filename
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|open
c_func
(paren
id|filename
comma
id|O_RDWR
op_or
id|O_CREAT
comma
l_int|0600
)paren
suffix:semicolon
)brace
DECL|function|gettimeofday
r_int
id|gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_void
op_star
id|tz
)paren
(brace
id|SYSTEMTIME
id|st
suffix:semicolon
r_struct
id|tm
id|tm
suffix:semicolon
id|GetSystemTime
c_func
(paren
op_amp
id|st
)paren
suffix:semicolon
id|tm.tm_year
op_assign
id|st.wYear
op_minus
l_int|1900
suffix:semicolon
id|tm.tm_mon
op_assign
id|st.wMonth
op_minus
l_int|1
suffix:semicolon
id|tm.tm_mday
op_assign
id|st.wDay
suffix:semicolon
id|tm.tm_hour
op_assign
id|st.wHour
suffix:semicolon
id|tm.tm_min
op_assign
id|st.wMinute
suffix:semicolon
id|tm.tm_sec
op_assign
id|st.wSecond
suffix:semicolon
id|tv-&gt;tv_sec
op_assign
id|tm_to_time_t
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tv-&gt;tv_sec
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|st.wMilliseconds
op_star
l_int|1000
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pipe
r_int
id|pipe
c_func
(paren
r_int
id|filedes
(braket
l_int|2
)braket
)paren
(brace
r_int
id|fd
suffix:semicolon
id|HANDLE
id|h
(braket
l_int|2
)braket
comma
id|parent
suffix:semicolon
r_if
c_cond
(paren
id|_pipe
c_func
(paren
id|filedes
comma
l_int|8192
comma
l_int|0
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|parent
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
(paren
id|parent
comma
(paren
id|HANDLE
)paren
id|_get_osfhandle
c_func
(paren
id|filedes
(braket
l_int|0
)braket
)paren
comma
id|parent
comma
op_amp
id|h
(braket
l_int|0
)braket
comma
l_int|0
comma
id|FALSE
comma
id|DUPLICATE_SAME_ACCESS
)paren
)paren
(brace
id|close
c_func
(paren
id|filedes
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|filedes
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|DuplicateHandle
(paren
id|parent
comma
(paren
id|HANDLE
)paren
id|_get_osfhandle
c_func
(paren
id|filedes
(braket
l_int|1
)braket
)paren
comma
id|parent
comma
op_amp
id|h
(braket
l_int|1
)braket
comma
l_int|0
comma
id|FALSE
comma
id|DUPLICATE_SAME_ACCESS
)paren
)paren
(brace
id|close
c_func
(paren
id|filedes
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|filedes
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|h
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|fd
op_assign
id|_open_osfhandle
c_func
(paren
(paren
r_int
)paren
id|h
(braket
l_int|0
)braket
comma
id|O_NOINHERIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|filedes
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|filedes
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|h
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|h
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|filedes
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|filedes
(braket
l_int|0
)braket
op_assign
id|fd
suffix:semicolon
id|fd
op_assign
id|_open_osfhandle
c_func
(paren
(paren
r_int
)paren
id|h
(braket
l_int|1
)braket
comma
id|O_NOINHERIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|filedes
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|filedes
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|h
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|filedes
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|filedes
(braket
l_int|1
)braket
op_assign
id|fd
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|poll
r_int
id|poll
c_func
(paren
r_struct
id|pollfd
op_star
id|ufds
comma
r_int
r_int
id|nfds
comma
r_int
id|timeout
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|gmtime_r
r_struct
id|tm
op_star
id|gmtime_r
c_func
(paren
r_const
id|time_t
op_star
id|timep
comma
r_struct
id|tm
op_star
id|result
)paren
(brace
multiline_comment|/* gmtime() in MSVCRT.DLL is thread-safe, but not reentrant */
id|memcpy
c_func
(paren
id|result
comma
id|gmtime
c_func
(paren
id|timep
)paren
comma
r_sizeof
(paren
r_struct
id|tm
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|localtime_r
r_struct
id|tm
op_star
id|localtime_r
c_func
(paren
r_const
id|time_t
op_star
id|timep
comma
r_struct
id|tm
op_star
id|result
)paren
(brace
multiline_comment|/* localtime() in MSVCRT.DLL is thread-safe, but not reentrant */
id|memcpy
c_func
(paren
id|result
comma
id|localtime
c_func
(paren
id|timep
)paren
comma
r_sizeof
(paren
r_struct
id|tm
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|getcwd
macro_line|#undef getcwd
DECL|function|mingw_getcwd
r_char
op_star
id|mingw_getcwd
c_func
(paren
r_char
op_star
id|pointer
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|ret
op_assign
id|getcwd
c_func
(paren
id|pointer
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|pointer
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pointer
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
id|pointer
(braket
id|i
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|parse_interpreter
r_static
r_const
r_char
op_star
id|parse_interpreter
c_func
(paren
r_const
r_char
op_star
id|cmd
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|100
)braket
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|opt
suffix:semicolon
r_int
id|n
comma
id|fd
suffix:semicolon
multiline_comment|/* don&squot;t even try a .exe */
id|n
op_assign
id|strlen
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
l_int|4
op_logical_and
op_logical_neg
id|strcasecmp
c_func
(paren
id|cmd
op_plus
id|n
op_minus
l_int|4
comma
l_string|&quot;.exe&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|cmd
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|n
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|4
)paren
multiline_comment|/* at least &squot;#!/x&squot; and not error */
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;#&squot;
op_logical_or
id|buf
(braket
l_int|1
)braket
op_ne
l_char|&squot;!&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
id|buf
(braket
id|n
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|strrchr
c_func
(paren
id|buf
op_plus
l_int|2
comma
l_char|&squot;/&squot;
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|p
op_assign
id|strrchr
c_func
(paren
id|buf
op_plus
l_int|2
comma
l_char|&squot;&bslash;&bslash;&squot;
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* strip options */
r_if
c_cond
(paren
(paren
id|opt
op_assign
id|strchr
c_func
(paren
id|p
op_plus
l_int|1
comma
l_char|&squot; &squot;
)paren
)paren
)paren
op_star
id|opt
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|p
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Splits the PATH into parts.&n; */
DECL|function|get_path_split
r_static
r_char
op_star
op_star
id|get_path_split
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|p
comma
op_star
op_star
id|path
comma
op_star
id|envpath
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
suffix:semicolon
r_int
id|i
comma
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|envpath
op_logical_or
op_logical_neg
op_star
id|envpath
)paren
r_return
l_int|NULL
suffix:semicolon
id|envpath
op_assign
id|xstrdup
c_func
(paren
id|envpath
)paren
suffix:semicolon
id|p
op_assign
id|envpath
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_char
op_star
id|dir
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|dir
)paren
(brace
multiline_comment|/* not earlier, catches series of ; */
op_increment
id|n
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
l_int|NULL
suffix:semicolon
id|path
op_assign
id|xmalloc
c_func
(paren
(paren
id|n
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|p
op_assign
id|envpath
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_star
id|p
)paren
id|path
(braket
id|i
op_increment
)braket
op_assign
id|xstrdup
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|p
op_plus
id|strlen
c_func
(paren
id|p
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|n
)paren
suffix:semicolon
id|path
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|free
c_func
(paren
id|envpath
)paren
suffix:semicolon
r_return
id|path
suffix:semicolon
)brace
DECL|function|free_path_split
r_static
r_void
id|free_path_split
c_func
(paren
r_char
op_star
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
r_return
suffix:semicolon
r_char
op_star
op_star
id|p
op_assign
id|path
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
id|free
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * exe_only means that we only want to detect .exe files, but not scripts&n; * (which do not have an extension)&n; */
DECL|function|lookup_prog
r_static
r_char
op_star
id|lookup_prog
c_func
(paren
r_const
r_char
op_star
id|dir
comma
r_const
r_char
op_star
id|cmd
comma
r_int
id|isexe
comma
r_int
id|exe_only
)paren
(brace
r_char
id|path
(braket
id|MAX_PATH
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|path
comma
r_sizeof
(paren
id|path
)paren
comma
l_string|&quot;%s/%s.exe&quot;
comma
id|dir
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isexe
op_logical_and
id|access
c_func
(paren
id|path
comma
id|F_OK
)paren
op_eq
l_int|0
)paren
r_return
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
id|path
(braket
id|strlen
c_func
(paren
id|path
)paren
op_minus
l_int|4
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|exe_only
op_logical_or
id|isexe
)paren
op_logical_and
id|access
c_func
(paren
id|path
comma
id|F_OK
)paren
op_eq
l_int|0
)paren
r_return
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Determines the absolute path of cmd using the the split path in path.&n; * If cmd contains a slash or backslash, no lookup is performed.&n; */
DECL|function|path_lookup
r_static
r_char
op_star
id|path_lookup
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_char
op_star
op_star
id|path
comma
r_int
id|exe_only
)paren
(brace
r_char
op_star
id|prog
op_assign
l_int|NULL
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_int
id|isexe
op_assign
id|len
op_ge
l_int|4
op_logical_and
op_logical_neg
id|strcasecmp
c_func
(paren
id|cmd
op_plus
id|len
op_minus
l_int|4
comma
l_string|&quot;.exe&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|cmd
comma
l_char|&squot;/&squot;
)paren
op_logical_or
id|strchr
c_func
(paren
id|cmd
comma
l_char|&squot;&bslash;&bslash;&squot;
)paren
)paren
id|prog
op_assign
id|xstrdup
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|prog
op_logical_and
op_star
id|path
)paren
id|prog
op_assign
id|lookup_prog
c_func
(paren
op_star
id|path
op_increment
comma
id|cmd
comma
id|isexe
comma
id|exe_only
)paren
suffix:semicolon
r_return
id|prog
suffix:semicolon
)brace
DECL|function|try_shell_exec
r_static
r_int
id|try_shell_exec
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_char
op_star
r_const
op_star
id|argv
comma
r_char
op_star
op_star
id|env
)paren
(brace
r_const
r_char
op_star
id|interpr
op_assign
id|parse_interpreter
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_char
op_star
op_star
id|path
suffix:semicolon
r_char
op_star
id|prog
suffix:semicolon
r_int
id|pid
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interpr
)paren
r_return
l_int|0
suffix:semicolon
id|path
op_assign
id|get_path_split
c_func
(paren
)paren
suffix:semicolon
id|prog
op_assign
id|path_lookup
c_func
(paren
id|interpr
comma
id|path
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prog
)paren
(brace
r_int
id|argc
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv2
suffix:semicolon
r_while
c_loop
(paren
id|argv
(braket
id|argc
)braket
)paren
id|argc
op_increment
suffix:semicolon
id|argv2
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|argv
)paren
op_star
(paren
id|argc
op_plus
l_int|2
)paren
)paren
suffix:semicolon
id|argv2
(braket
l_int|0
)braket
op_assign
(paren
r_char
op_star
)paren
id|interpr
suffix:semicolon
id|argv2
(braket
l_int|1
)braket
op_assign
(paren
r_char
op_star
)paren
id|cmd
suffix:semicolon
multiline_comment|/* full path to the script file */
id|memcpy
c_func
(paren
op_amp
id|argv2
(braket
l_int|2
)braket
comma
op_amp
id|argv
(braket
l_int|1
)braket
comma
r_sizeof
(paren
op_star
id|argv
)paren
op_star
id|argc
)paren
suffix:semicolon
id|pid
op_assign
id|spawnve
c_func
(paren
id|_P_NOWAIT
comma
id|prog
comma
id|argv2
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|env
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ge
l_int|0
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
id|status
op_assign
l_int|255
suffix:semicolon
m_exit
(paren
id|status
)paren
suffix:semicolon
)brace
id|pid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* indicate that we tried but failed */
id|free
c_func
(paren
id|prog
)paren
suffix:semicolon
id|free
c_func
(paren
id|argv2
)paren
suffix:semicolon
)brace
id|free_path_split
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
DECL|function|mingw_execve
r_static
r_void
id|mingw_execve
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_char
op_star
r_const
op_star
id|argv
comma
r_char
op_star
r_const
op_star
id|env
)paren
(brace
multiline_comment|/* check if git_command is a shell script */
r_if
c_cond
(paren
op_logical_neg
id|try_shell_exec
c_func
(paren
id|cmd
comma
id|argv
comma
(paren
r_char
op_star
op_star
)paren
id|env
)paren
)paren
(brace
r_int
id|pid
comma
id|status
suffix:semicolon
id|pid
op_assign
id|spawnve
c_func
(paren
id|_P_NOWAIT
comma
id|cmd
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|argv
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|env
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
id|status
op_assign
l_int|255
suffix:semicolon
m_exit
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
DECL|function|mingw_execvp
r_void
id|mingw_execvp
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_char
op_star
r_const
op_star
id|argv
)paren
(brace
r_char
op_star
op_star
id|path
op_assign
id|get_path_split
c_func
(paren
)paren
suffix:semicolon
r_char
op_star
id|prog
op_assign
id|path_lookup
c_func
(paren
id|cmd
comma
id|path
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prog
)paren
(brace
id|mingw_execve
c_func
(paren
id|prog
comma
id|argv
comma
id|environ
)paren
suffix:semicolon
id|free
c_func
(paren
id|prog
)paren
suffix:semicolon
)brace
r_else
id|errno
op_assign
id|ENOENT
suffix:semicolon
id|free_path_split
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
DECL|function|copy_environ
r_char
op_star
op_star
id|copy_environ
c_func
(paren
)paren
(brace
r_char
op_star
op_star
id|env
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|environ
(braket
id|i
)braket
)paren
id|i
op_increment
suffix:semicolon
id|env
op_assign
id|xmalloc
c_func
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|env
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|environ
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|env
(braket
id|i
)braket
op_assign
id|xstrdup
c_func
(paren
id|environ
(braket
id|i
)braket
)paren
suffix:semicolon
id|env
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|env
suffix:semicolon
)brace
DECL|function|free_environ
r_void
id|free_environ
c_func
(paren
r_char
op_star
op_star
id|env
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|env
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|env
(braket
id|i
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|env
)paren
suffix:semicolon
)brace
DECL|function|lookup_env
r_static
r_int
id|lookup_env
c_func
(paren
r_char
op_star
op_star
id|env
comma
r_const
r_char
op_star
id|name
comma
r_int
id|nmln
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|env
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
id|strncmp
c_func
(paren
id|env
(braket
id|i
)braket
comma
id|name
comma
id|nmln
)paren
op_logical_and
l_char|&squot;=&squot;
op_eq
id|env
(braket
id|i
)braket
(braket
id|nmln
)braket
)paren
multiline_comment|/* matches */
r_return
id|i
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * If name contains &squot;=&squot;, then sets the variable, otherwise it unsets it&n; */
DECL|function|env_setenv
r_char
op_star
op_star
id|env_setenv
c_func
(paren
r_char
op_star
op_star
id|env
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_char
op_star
id|eq
op_assign
id|strchrnul
c_func
(paren
id|name
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_int
id|i
op_assign
id|lookup_env
c_func
(paren
id|env
comma
id|name
comma
id|eq
op_minus
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|eq
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|env
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|env
op_assign
id|xrealloc
c_func
(paren
id|env
comma
(paren
id|i
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
op_star
id|env
)paren
)paren
suffix:semicolon
id|env
(braket
id|i
)braket
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|env
(braket
id|i
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
id|free
c_func
(paren
id|env
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|eq
)paren
id|env
(braket
id|i
)braket
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
suffix:semicolon
id|env
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
id|env
(braket
id|i
)braket
op_assign
id|env
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
r_return
id|env
suffix:semicolon
)brace
DECL|macro|rename
macro_line|#undef rename
DECL|function|mingw_rename
r_int
id|mingw_rename
c_func
(paren
r_const
r_char
op_star
id|pold
comma
r_const
r_char
op_star
id|pnew
)paren
(brace
multiline_comment|/*&n;&t; * Try native rename() first to get errno right.&n;&t; * It is based on MoveFile(), which cannot overwrite existing files.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rename
c_func
(paren
id|pold
comma
id|pnew
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|MoveFileEx
c_func
(paren
id|pold
comma
id|pnew
comma
id|MOVEFILE_REPLACE_EXISTING
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* TODO: translate more errors */
r_if
c_cond
(paren
id|GetLastError
c_func
(paren
)paren
op_eq
id|ERROR_ACCESS_DENIED
)paren
(brace
id|DWORD
id|attrs
op_assign
id|GetFileAttributes
c_func
(paren
id|pnew
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attrs
op_ne
id|INVALID_FILE_ATTRIBUTES
op_logical_and
(paren
id|attrs
op_amp
id|FILE_ATTRIBUTE_DIRECTORY
)paren
)paren
(brace
id|errno
op_assign
id|EISDIR
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|errno
op_assign
id|EACCES
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|getpwuid
r_struct
id|passwd
op_star
id|getpwuid
c_func
(paren
r_int
id|uid
)paren
(brace
r_static
r_char
id|user_name
(braket
l_int|100
)braket
suffix:semicolon
r_static
r_struct
id|passwd
id|p
suffix:semicolon
id|DWORD
id|len
op_assign
r_sizeof
(paren
id|user_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|GetUserName
c_func
(paren
id|user_name
comma
op_amp
id|len
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|p.pw_name
op_assign
id|user_name
suffix:semicolon
id|p.pw_gecos
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
id|p.pw_dir
op_assign
l_int|NULL
suffix:semicolon
r_return
op_amp
id|p
suffix:semicolon
)brace
DECL|variable|timer_event
r_static
id|HANDLE
id|timer_event
suffix:semicolon
DECL|variable|timer_thread
r_static
id|HANDLE
id|timer_thread
suffix:semicolon
DECL|variable|timer_interval
r_static
r_int
id|timer_interval
suffix:semicolon
DECL|variable|one_shot
r_static
r_int
id|one_shot
suffix:semicolon
DECL|variable|timer_fn
r_static
id|sig_handler_t
id|timer_fn
op_assign
id|SIG_DFL
suffix:semicolon
multiline_comment|/* The timer works like this:&n; * The thread, ticktack(), is a trivial routine that most of the time&n; * only waits to receive the signal to terminate. The main thread tells&n; * the thread to terminate by setting the timer_event to the signalled&n; * state.&n; * But ticktack() interrupts the wait state after the timer&squot;s interval&n; * length to call the signal handler.&n; */
DECL|function|ticktack
r_static
id|__stdcall
r_int
id|ticktack
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_while
c_loop
(paren
id|WaitForSingleObject
c_func
(paren
id|timer_event
comma
id|timer_interval
)paren
op_eq
id|WAIT_TIMEOUT
)paren
(brace
r_if
c_cond
(paren
id|timer_fn
op_eq
id|SIG_DFL
)paren
id|die
c_func
(paren
l_string|&quot;Alarm&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_fn
op_ne
id|SIG_IGN
)paren
id|timer_fn
c_func
(paren
id|SIGALRM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|one_shot
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|start_timer_thread
r_static
r_int
id|start_timer_thread
c_func
(paren
r_void
)paren
(brace
id|timer_event
op_assign
id|CreateEvent
c_func
(paren
l_int|NULL
comma
id|FALSE
comma
id|FALSE
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_event
)paren
(brace
id|timer_thread
op_assign
(paren
id|HANDLE
)paren
id|_beginthreadex
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|ticktack
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
op_logical_neg
id|timer_thread
)paren
r_return
id|errno
op_assign
id|ENOMEM
comma
id|error
c_func
(paren
l_string|&quot;cannot start timer thread&quot;
)paren
suffix:semicolon
)brace
r_else
r_return
id|errno
op_assign
id|ENOMEM
comma
id|error
c_func
(paren
l_string|&quot;cannot allocate resources for timer&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|stop_timer_thread
r_static
r_void
id|stop_timer_thread
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|timer_event
)paren
id|SetEvent
c_func
(paren
id|timer_event
)paren
suffix:semicolon
multiline_comment|/* tell thread to terminate */
r_if
c_cond
(paren
id|timer_thread
)paren
(brace
r_int
id|rc
op_assign
id|WaitForSingleObject
c_func
(paren
id|timer_thread
comma
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|WAIT_TIMEOUT
)paren
id|error
c_func
(paren
l_string|&quot;timer thread did not terminate timely&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rc
op_ne
id|WAIT_OBJECT_0
)paren
id|error
c_func
(paren
l_string|&quot;waiting for timer thread failed: %lu&quot;
comma
id|GetLastError
c_func
(paren
)paren
)paren
suffix:semicolon
id|CloseHandle
c_func
(paren
id|timer_thread
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timer_event
)paren
id|CloseHandle
c_func
(paren
id|timer_event
)paren
suffix:semicolon
id|timer_event
op_assign
l_int|NULL
suffix:semicolon
id|timer_thread
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|is_timeval_eq
r_static
r_inline
r_int
id|is_timeval_eq
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|i1
comma
r_const
r_struct
id|timeval
op_star
id|i2
)paren
(brace
r_return
id|i1-&gt;tv_sec
op_eq
id|i2-&gt;tv_sec
op_logical_and
id|i1-&gt;tv_usec
op_eq
id|i2-&gt;tv_usec
suffix:semicolon
)brace
DECL|function|setitimer
r_int
id|setitimer
c_func
(paren
r_int
id|type
comma
r_struct
id|itimerval
op_star
id|in
comma
r_struct
id|itimerval
op_star
id|out
)paren
(brace
r_static
r_const
r_struct
id|timeval
id|zero
suffix:semicolon
r_static
r_int
id|atexit_done
suffix:semicolon
r_if
c_cond
(paren
id|out
op_ne
l_int|NULL
)paren
r_return
id|errno
op_assign
id|EINVAL
comma
id|error
c_func
(paren
l_string|&quot;setitimer param 3 != NULL not implemented&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_timeval_eq
c_func
(paren
op_amp
id|in-&gt;it_interval
comma
op_amp
id|zero
)paren
op_logical_and
op_logical_neg
id|is_timeval_eq
c_func
(paren
op_amp
id|in-&gt;it_interval
comma
op_amp
id|in-&gt;it_value
)paren
)paren
r_return
id|errno
op_assign
id|EINVAL
comma
id|error
c_func
(paren
l_string|&quot;setitimer: it_interval must be zero or eq it_value&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timer_thread
)paren
id|stop_timer_thread
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_timeval_eq
c_func
(paren
op_amp
id|in-&gt;it_value
comma
op_amp
id|zero
)paren
op_logical_and
id|is_timeval_eq
c_func
(paren
op_amp
id|in-&gt;it_interval
comma
op_amp
id|zero
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|timer_interval
op_assign
id|in-&gt;it_value.tv_sec
op_star
l_int|1000
op_plus
id|in-&gt;it_value.tv_usec
op_div
l_int|1000
suffix:semicolon
id|one_shot
op_assign
id|is_timeval_eq
c_func
(paren
op_amp
id|in-&gt;it_interval
comma
op_amp
id|zero
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atexit_done
)paren
(brace
id|atexit
c_func
(paren
id|stop_timer_thread
)paren
suffix:semicolon
id|atexit_done
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|start_timer_thread
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sigaction
r_int
id|sigaction
c_func
(paren
r_int
id|sig
comma
r_struct
id|sigaction
op_star
id|in
comma
r_struct
id|sigaction
op_star
id|out
)paren
(brace
r_if
c_cond
(paren
id|sig
op_ne
id|SIGALRM
)paren
r_return
id|errno
op_assign
id|EINVAL
comma
id|error
c_func
(paren
l_string|&quot;sigaction only implemented for SIGALRM&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out
op_ne
l_int|NULL
)paren
r_return
id|errno
op_assign
id|EINVAL
comma
id|error
c_func
(paren
l_string|&quot;sigaction: param 3 != NULL not implemented&quot;
)paren
suffix:semicolon
id|timer_fn
op_assign
id|in-&gt;sa_handler
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|signal
macro_line|#undef signal
DECL|function|mingw_signal
id|sig_handler_t
id|mingw_signal
c_func
(paren
r_int
id|sig
comma
id|sig_handler_t
id|handler
)paren
(brace
r_if
c_cond
(paren
id|sig
op_ne
id|SIGALRM
)paren
r_return
id|signal
c_func
(paren
id|sig
comma
id|handler
)paren
suffix:semicolon
id|sig_handler_t
id|old
op_assign
id|timer_fn
suffix:semicolon
id|timer_fn
op_assign
id|handler
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
eof
