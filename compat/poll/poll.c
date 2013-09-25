multiline_comment|/* Emulation for poll(2)&n;   Contributed by Paolo Bonzini.&n;&n;   Copyright 2001-2003, 2006-2011 Free Software Foundation, Inc.&n;&n;   This file is part of gnulib.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License along&n;   with this program; if not, write to the Free Software Foundation,&n;   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */
multiline_comment|/* Tell gcc not to warn about the (nfd &lt; 0) tests, below.  */
macro_line|#if (__GNUC__ == 4 &amp;&amp; 3 &lt;= __GNUC_MINOR__) || 4 &lt; __GNUC__
macro_line|# pragma GCC diagnostic ignored &quot;-Wtype-limits&quot;
macro_line|#endif
macro_line|#if defined(WIN32)
macro_line|# include &lt;malloc.h&gt;
macro_line|#endif
macro_line|#include &lt;sys/types.h&gt;
multiline_comment|/* Specification.  */
macro_line|#include &lt;poll.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &lt;assert.h&gt;
macro_line|#if (defined _WIN32 || defined __WIN32__) &amp;&amp; ! defined __CYGWIN__
DECL|macro|WIN32_NATIVE
macro_line|# define WIN32_NATIVE
macro_line|# if defined (_MSC_VER) &amp;&amp; !defined(_WIN32_WINNT)
DECL|macro|_WIN32_WINNT
macro_line|#  define _WIN32_WINNT 0x0502
macro_line|# endif
macro_line|# include &lt;winsock2.h&gt;
macro_line|# include &lt;windows.h&gt;
macro_line|# include &lt;io.h&gt;
macro_line|# include &lt;stdio.h&gt;
macro_line|# include &lt;conio.h&gt;
macro_line|#else
macro_line|# include &lt;sys/time.h&gt;
macro_line|# include &lt;sys/socket.h&gt;
macro_line|# ifndef NO_SYS_SELECT_H
macro_line|#  include &lt;sys/select.h&gt;
macro_line|# endif
macro_line|# include &lt;unistd.h&gt;
macro_line|#endif
macro_line|#ifdef HAVE_SYS_IOCTL_H
macro_line|# include &lt;sys/ioctl.h&gt;
macro_line|#endif
macro_line|#ifdef HAVE_SYS_FILIO_H
macro_line|# include &lt;sys/filio.h&gt;
macro_line|#endif
macro_line|#include &lt;time.h&gt;
macro_line|#ifndef INFTIM
DECL|macro|INFTIM
macro_line|# define INFTIM (-1)
macro_line|#endif
multiline_comment|/* BeOS does not have MSG_PEEK.  */
macro_line|#ifndef MSG_PEEK
DECL|macro|MSG_PEEK
macro_line|# define MSG_PEEK 0
macro_line|#endif
macro_line|#ifdef WIN32_NATIVE
DECL|macro|IsConsoleHandle
mdefine_line|#define IsConsoleHandle(h) (((long) (h) &amp; 3) == 3)
r_static
id|BOOL
DECL|function|IsSocketHandle
id|IsSocketHandle
(paren
id|HANDLE
id|h
)paren
(brace
id|WSANETWORKEVENTS
id|ev
suffix:semicolon
r_if
c_cond
(paren
id|IsConsoleHandle
(paren
id|h
)paren
)paren
r_return
id|FALSE
suffix:semicolon
multiline_comment|/* Under Wine, it seems that getsockopt returns 0 for pipes too.&n;     WSAEnumNetworkEvents instead distinguishes the two correctly.  */
id|ev.lNetworkEvents
op_assign
l_int|0xDEADBEEF
suffix:semicolon
id|WSAEnumNetworkEvents
(paren
(paren
id|SOCKET
)paren
id|h
comma
l_int|NULL
comma
op_amp
id|ev
)paren
suffix:semicolon
r_return
id|ev.lNetworkEvents
op_ne
l_int|0xDEADBEEF
suffix:semicolon
)brace
multiline_comment|/* Declare data structures for ntdll functions.  */
DECL|struct|_FILE_PIPE_LOCAL_INFORMATION
r_typedef
r_struct
id|_FILE_PIPE_LOCAL_INFORMATION
(brace
DECL|member|NamedPipeType
id|ULONG
id|NamedPipeType
suffix:semicolon
DECL|member|NamedPipeConfiguration
id|ULONG
id|NamedPipeConfiguration
suffix:semicolon
DECL|member|MaximumInstances
id|ULONG
id|MaximumInstances
suffix:semicolon
DECL|member|CurrentInstances
id|ULONG
id|CurrentInstances
suffix:semicolon
DECL|member|InboundQuota
id|ULONG
id|InboundQuota
suffix:semicolon
DECL|member|ReadDataAvailable
id|ULONG
id|ReadDataAvailable
suffix:semicolon
DECL|member|OutboundQuota
id|ULONG
id|OutboundQuota
suffix:semicolon
DECL|member|WriteQuotaAvailable
id|ULONG
id|WriteQuotaAvailable
suffix:semicolon
DECL|member|NamedPipeState
id|ULONG
id|NamedPipeState
suffix:semicolon
DECL|member|NamedPipeEnd
id|ULONG
id|NamedPipeEnd
suffix:semicolon
DECL|typedef|FILE_PIPE_LOCAL_INFORMATION
DECL|typedef|PFILE_PIPE_LOCAL_INFORMATION
)brace
id|FILE_PIPE_LOCAL_INFORMATION
comma
op_star
id|PFILE_PIPE_LOCAL_INFORMATION
suffix:semicolon
DECL|struct|_IO_STATUS_BLOCK
r_typedef
r_struct
id|_IO_STATUS_BLOCK
(brace
r_union
(brace
DECL|member|Status
id|DWORD
id|Status
suffix:semicolon
DECL|member|Pointer
id|PVOID
id|Pointer
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|Information
id|ULONG_PTR
id|Information
suffix:semicolon
DECL|typedef|IO_STATUS_BLOCK
DECL|typedef|PIO_STATUS_BLOCK
)brace
id|IO_STATUS_BLOCK
comma
op_star
id|PIO_STATUS_BLOCK
suffix:semicolon
DECL|enum|_FILE_INFORMATION_CLASS
r_typedef
r_enum
id|_FILE_INFORMATION_CLASS
(brace
DECL|enumerator|FilePipeLocalInformation
id|FilePipeLocalInformation
op_assign
l_int|24
DECL|typedef|FILE_INFORMATION_CLASS
DECL|typedef|PFILE_INFORMATION_CLASS
)brace
id|FILE_INFORMATION_CLASS
comma
op_star
id|PFILE_INFORMATION_CLASS
suffix:semicolon
DECL|typedef|PNtQueryInformationFile
r_typedef
id|DWORD
(paren
id|WINAPI
op_star
id|PNtQueryInformationFile
)paren
(paren
id|HANDLE
comma
id|IO_STATUS_BLOCK
op_star
comma
id|VOID
op_star
comma
id|ULONG
comma
id|FILE_INFORMATION_CLASS
)paren
suffix:semicolon
macro_line|# ifndef PIPE_BUF
DECL|macro|PIPE_BUF
macro_line|#  define PIPE_BUF      512
macro_line|# endif
multiline_comment|/* Compute revents values for file handle H.  If some events cannot happen&n;   for the handle, eliminate them from *P_SOUGHT.  */
r_static
r_int
DECL|function|win32_compute_revents
id|win32_compute_revents
(paren
id|HANDLE
id|h
comma
r_int
op_star
id|p_sought
)paren
(brace
r_int
id|i
comma
id|ret
comma
id|happened
suffix:semicolon
id|INPUT_RECORD
op_star
id|irbuffer
suffix:semicolon
id|DWORD
id|avail
comma
id|nbuffer
suffix:semicolon
id|BOOL
id|bRet
suffix:semicolon
id|IO_STATUS_BLOCK
id|iosb
suffix:semicolon
id|FILE_PIPE_LOCAL_INFORMATION
id|fpli
suffix:semicolon
r_static
id|PNtQueryInformationFile
id|NtQueryInformationFile
suffix:semicolon
r_static
id|BOOL
id|once_only
suffix:semicolon
r_switch
c_cond
(paren
id|GetFileType
(paren
id|h
)paren
)paren
(brace
r_case
id|FILE_TYPE_PIPE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|once_only
)paren
(brace
id|NtQueryInformationFile
op_assign
(paren
id|PNtQueryInformationFile
)paren
id|GetProcAddress
(paren
id|GetModuleHandle
(paren
l_string|&quot;ntdll.dll&quot;
)paren
comma
l_string|&quot;NtQueryInformationFile&quot;
)paren
suffix:semicolon
id|once_only
op_assign
id|TRUE
suffix:semicolon
)brace
id|happened
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|PeekNamedPipe
(paren
id|h
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|avail
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|avail
)paren
id|happened
op_or_assign
op_star
id|p_sought
op_amp
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|GetLastError
(paren
)paren
op_eq
id|ERROR_BROKEN_PIPE
)paren
id|happened
op_or_assign
id|POLLHUP
suffix:semicolon
r_else
(brace
multiline_comment|/* It was the write-end of the pipe.  Check if it is writable.&n;&t;     If NtQueryInformationFile fails, optimistically assume the pipe is&n;&t;     writable.  This could happen on Win9x, where NtQueryInformationFile&n;&t;     is not available, or if we inherit a pipe that doesn&squot;t permit&n;&t;     FILE_READ_ATTRIBUTES access on the write end (I think this should&n;&t;     not happen since WinXP SP2; WINE seems fine too).  Otherwise,&n;&t;     ensure that enough space is available for atomic writes.  */
id|memset
(paren
op_amp
id|iosb
comma
l_int|0
comma
r_sizeof
(paren
id|iosb
)paren
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|fpli
comma
l_int|0
comma
r_sizeof
(paren
id|fpli
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NtQueryInformationFile
op_logical_or
id|NtQueryInformationFile
(paren
id|h
comma
op_amp
id|iosb
comma
op_amp
id|fpli
comma
r_sizeof
(paren
id|fpli
)paren
comma
id|FilePipeLocalInformation
)paren
op_logical_or
id|fpli.WriteQuotaAvailable
op_ge
id|PIPE_BUF
op_logical_or
(paren
id|fpli.OutboundQuota
OL
id|PIPE_BUF
op_logical_and
id|fpli.WriteQuotaAvailable
op_eq
id|fpli.OutboundQuota
)paren
)paren
id|happened
op_or_assign
op_star
id|p_sought
op_amp
(paren
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
suffix:semicolon
)brace
r_return
id|happened
suffix:semicolon
r_case
id|FILE_TYPE_CHAR
suffix:colon
id|ret
op_assign
id|WaitForSingleObject
(paren
id|h
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IsConsoleHandle
(paren
id|h
)paren
)paren
r_return
id|ret
op_eq
id|WAIT_OBJECT_0
ques
c_cond
op_star
id|p_sought
op_amp
op_complement
(paren
id|POLLPRI
op_or
id|POLLRDBAND
)paren
suffix:colon
l_int|0
suffix:semicolon
id|nbuffer
op_assign
id|avail
op_assign
l_int|0
suffix:semicolon
id|bRet
op_assign
id|GetNumberOfConsoleInputEvents
(paren
id|h
comma
op_amp
id|nbuffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRet
)paren
(brace
multiline_comment|/* Input buffer.  */
op_star
id|p_sought
op_and_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_if
c_cond
(paren
id|nbuffer
op_eq
l_int|0
)paren
r_return
id|POLLHUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p_sought
)paren
r_return
l_int|0
suffix:semicolon
id|irbuffer
op_assign
(paren
id|INPUT_RECORD
op_star
)paren
id|alloca
(paren
id|nbuffer
op_star
r_sizeof
(paren
id|INPUT_RECORD
)paren
)paren
suffix:semicolon
id|bRet
op_assign
id|PeekConsoleInput
(paren
id|h
comma
id|irbuffer
comma
id|nbuffer
comma
op_amp
id|avail
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bRet
op_logical_or
id|avail
op_eq
l_int|0
)paren
r_return
id|POLLHUP
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
id|avail
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|irbuffer
(braket
id|i
)braket
dot
id|EventType
op_eq
id|KEY_EVENT
)paren
r_return
op_star
id|p_sought
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Screen buffer.  */
op_star
id|p_sought
op_and_assign
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
suffix:semicolon
r_return
op_star
id|p_sought
suffix:semicolon
)brace
r_default
suffix:colon
id|ret
op_assign
id|WaitForSingleObject
(paren
id|h
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|WAIT_OBJECT_0
)paren
r_return
op_star
id|p_sought
op_amp
op_complement
(paren
id|POLLPRI
op_or
id|POLLRDBAND
)paren
suffix:semicolon
r_return
op_star
id|p_sought
op_amp
(paren
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Convert fd_sets returned by select into revents values.  */
r_static
r_int
DECL|function|win32_compute_revents_socket
id|win32_compute_revents_socket
(paren
id|SOCKET
id|h
comma
r_int
id|sought
comma
r_int
id|lNetworkEvents
)paren
(brace
r_int
id|happened
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lNetworkEvents
op_amp
(paren
id|FD_READ
op_or
id|FD_ACCEPT
op_or
id|FD_CLOSE
)paren
)paren
op_eq
id|FD_ACCEPT
)paren
id|happened
op_or_assign
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
op_amp
id|sought
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lNetworkEvents
op_amp
(paren
id|FD_READ
op_or
id|FD_ACCEPT
op_or
id|FD_CLOSE
)paren
)paren
(brace
r_int
id|r
comma
id|error
suffix:semicolon
r_char
id|data
(braket
l_int|64
)braket
suffix:semicolon
id|WSASetLastError
(paren
l_int|0
)paren
suffix:semicolon
id|r
op_assign
id|recv
(paren
id|h
comma
id|data
comma
r_sizeof
(paren
id|data
)paren
comma
id|MSG_PEEK
)paren
suffix:semicolon
id|error
op_assign
id|WSAGetLastError
(paren
)paren
suffix:semicolon
id|WSASetLastError
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OG
l_int|0
op_logical_or
id|error
op_eq
id|WSAENOTCONN
)paren
id|happened
op_or_assign
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
op_amp
id|sought
suffix:semicolon
multiline_comment|/* Distinguish hung-up sockets from other errors.  */
r_else
r_if
c_cond
(paren
id|r
op_eq
l_int|0
op_logical_or
id|error
op_eq
id|WSAESHUTDOWN
op_logical_or
id|error
op_eq
id|WSAECONNRESET
op_logical_or
id|error
op_eq
id|WSAECONNABORTED
op_logical_or
id|error
op_eq
id|WSAENETRESET
)paren
id|happened
op_or_assign
id|POLLHUP
suffix:semicolon
r_else
id|happened
op_or_assign
id|POLLERR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lNetworkEvents
op_amp
(paren
id|FD_WRITE
op_or
id|FD_CONNECT
)paren
)paren
id|happened
op_or_assign
(paren
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
op_amp
id|sought
suffix:semicolon
r_if
c_cond
(paren
id|lNetworkEvents
op_amp
id|FD_OOB
)paren
id|happened
op_or_assign
(paren
id|POLLPRI
op_or
id|POLLRDBAND
)paren
op_amp
id|sought
suffix:semicolon
r_return
id|happened
suffix:semicolon
)brace
macro_line|#else /* !MinGW */
multiline_comment|/* Convert select(2) returned fd_sets into poll(2) revents values.  */
r_static
r_int
DECL|function|compute_revents
id|compute_revents
(paren
r_int
id|fd
comma
r_int
id|sought
comma
id|fd_set
op_star
id|rfds
comma
id|fd_set
op_star
id|wfds
comma
id|fd_set
op_star
id|efds
)paren
(brace
r_int
id|happened
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|FD_ISSET
(paren
id|fd
comma
id|rfds
)paren
)paren
(brace
r_int
id|r
suffix:semicolon
r_int
id|socket_errno
suffix:semicolon
macro_line|# if defined __MACH__ &amp;&amp; defined __APPLE__
multiline_comment|/* There is a bug in Mac OS X that causes it to ignore MSG_PEEK&n;&t; for some kinds of descriptors.  Detect if this descriptor is a&n;&t; connected socket, a server socket, or something else using a&n;&t; 0-byte recv, and use ioctl(2) to detect POLLHUP.  */
id|r
op_assign
id|recv
(paren
id|fd
comma
l_int|NULL
comma
l_int|0
comma
id|MSG_PEEK
)paren
suffix:semicolon
id|socket_errno
op_assign
(paren
id|r
OL
l_int|0
)paren
ques
c_cond
id|errno
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|0
op_logical_or
id|socket_errno
op_eq
id|ENOTSOCK
)paren
id|ioctl
(paren
id|fd
comma
id|FIONREAD
comma
op_amp
id|r
)paren
suffix:semicolon
macro_line|# else
r_char
id|data
(braket
l_int|64
)braket
suffix:semicolon
id|r
op_assign
id|recv
(paren
id|fd
comma
id|data
comma
r_sizeof
(paren
id|data
)paren
comma
id|MSG_PEEK
)paren
suffix:semicolon
id|socket_errno
op_assign
(paren
id|r
OL
l_int|0
)paren
ques
c_cond
id|errno
suffix:colon
l_int|0
suffix:semicolon
macro_line|# endif
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|happened
op_or_assign
id|POLLHUP
suffix:semicolon
multiline_comment|/* If the event happened on an unconnected server socket,&n;&t; that&squot;s fine. */
r_else
r_if
c_cond
(paren
id|r
OG
l_int|0
op_logical_or
(paren
multiline_comment|/* (r == -1) &amp;&amp; */
id|socket_errno
op_eq
id|ENOTCONN
)paren
)paren
id|happened
op_or_assign
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
op_amp
id|sought
suffix:semicolon
multiline_comment|/* Distinguish hung-up sockets from other errors.  */
r_else
r_if
c_cond
(paren
id|socket_errno
op_eq
id|ESHUTDOWN
op_logical_or
id|socket_errno
op_eq
id|ECONNRESET
op_logical_or
id|socket_errno
op_eq
id|ECONNABORTED
op_logical_or
id|socket_errno
op_eq
id|ENETRESET
)paren
id|happened
op_or_assign
id|POLLHUP
suffix:semicolon
multiline_comment|/* some systems can&squot;t use recv() on non-socket, including HP NonStop */
r_else
r_if
c_cond
(paren
multiline_comment|/* (r == -1) &amp;&amp; */
id|socket_errno
op_eq
id|ENOTSOCK
)paren
id|happened
op_or_assign
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
op_amp
id|sought
suffix:semicolon
r_else
id|happened
op_or_assign
id|POLLERR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|FD_ISSET
(paren
id|fd
comma
id|wfds
)paren
)paren
id|happened
op_or_assign
(paren
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
op_amp
id|sought
suffix:semicolon
r_if
c_cond
(paren
id|FD_ISSET
(paren
id|fd
comma
id|efds
)paren
)paren
id|happened
op_or_assign
(paren
id|POLLPRI
op_or
id|POLLRDBAND
)paren
op_amp
id|sought
suffix:semicolon
r_return
id|happened
suffix:semicolon
)brace
macro_line|#endif /* !MinGW */
r_int
DECL|function|poll
id|poll
(paren
r_struct
id|pollfd
op_star
id|pfd
comma
id|nfds_t
id|nfd
comma
r_int
id|timeout
)paren
(brace
macro_line|#ifndef WIN32_NATIVE
id|fd_set
id|rfds
comma
id|wfds
comma
id|efds
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_struct
id|timeval
op_star
id|ptv
suffix:semicolon
r_int
id|maxfd
comma
id|rc
suffix:semicolon
id|nfds_t
id|i
suffix:semicolon
macro_line|# ifdef _SC_OPEN_MAX
r_static
r_int
id|sc_open_max
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nfd
OL
l_int|0
op_logical_or
(paren
id|nfd
OG
id|sc_open_max
op_logical_and
(paren
id|sc_open_max
op_ne
l_int|1
op_logical_or
id|nfd
OG
(paren
id|sc_open_max
op_assign
id|sysconf
(paren
id|_SC_OPEN_MAX
)paren
)paren
)paren
)paren
)paren
(brace
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|# else /* !_SC_OPEN_MAX */
macro_line|#  ifdef OPEN_MAX
r_if
c_cond
(paren
id|nfd
template_param
id|OPEN_MAX
)paren
(brace
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#  endif /* OPEN_MAX -- else, no check is needed */
macro_line|# endif /* !_SC_OPEN_MAX */
multiline_comment|/* EFAULT is not necessary to implement, but let&squot;s do it in the&n;     simplest case. */
r_if
c_cond
(paren
op_logical_neg
id|pfd
op_logical_and
id|nfd
)paren
(brace
id|errno
op_assign
id|EFAULT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* convert timeout number into a timeval structure */
r_if
c_cond
(paren
id|timeout
op_eq
l_int|0
)paren
(brace
id|ptv
op_assign
op_amp
id|tv
suffix:semicolon
id|ptv-&gt;tv_sec
op_assign
l_int|0
suffix:semicolon
id|ptv-&gt;tv_usec
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|timeout
OG
l_int|0
)paren
(brace
id|ptv
op_assign
op_amp
id|tv
suffix:semicolon
id|ptv-&gt;tv_sec
op_assign
id|timeout
op_div
l_int|1000
suffix:semicolon
id|ptv-&gt;tv_usec
op_assign
(paren
id|timeout
op_mod
l_int|1000
)paren
op_star
l_int|1000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|timeout
op_eq
id|INFTIM
)paren
multiline_comment|/* wait forever */
id|ptv
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* create fd sets and determine max fd */
id|maxfd
op_assign
l_int|1
suffix:semicolon
id|FD_ZERO
(paren
op_amp
id|rfds
)paren
suffix:semicolon
id|FD_ZERO
(paren
op_amp
id|wfds
)paren
suffix:semicolon
id|FD_ZERO
(paren
op_amp
id|efds
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
id|nfd
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|events
op_amp
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
)paren
id|FD_SET
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
comma
op_amp
id|rfds
)paren
suffix:semicolon
multiline_comment|/* see select(2): &quot;the only exceptional condition detectable&n;&t; is out-of-band data received on a socket&quot;, hence we push&n;&t; POLLWRBAND events onto wfds instead of efds. */
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|events
op_amp
(paren
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
)paren
id|FD_SET
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
comma
op_amp
id|wfds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|events
op_amp
(paren
id|POLLPRI
op_or
id|POLLRDBAND
)paren
)paren
id|FD_SET
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
comma
op_amp
id|efds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
op_ge
id|maxfd
op_logical_and
(paren
id|pfd
(braket
id|i
)braket
dot
id|events
op_amp
(paren
id|POLLIN
op_or
id|POLLOUT
op_or
id|POLLPRI
op_or
id|POLLRDNORM
op_or
id|POLLRDBAND
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
)paren
)paren
(brace
id|maxfd
op_assign
id|pfd
(braket
id|i
)braket
dot
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|maxfd
OG
id|FD_SETSIZE
)paren
(brace
id|errno
op_assign
id|EOVERFLOW
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* examine fd sets */
id|rc
op_assign
id|select
(paren
id|maxfd
op_plus
l_int|1
comma
op_amp
id|rfds
comma
op_amp
id|wfds
comma
op_amp
id|efds
comma
id|ptv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
multiline_comment|/* establish results */
id|rc
op_assign
l_int|0
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
id|nfd
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
OL
l_int|0
)paren
id|pfd
(braket
id|i
)braket
dot
id|revents
op_assign
l_int|0
suffix:semicolon
r_else
(brace
r_int
id|happened
op_assign
id|compute_revents
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
comma
id|pfd
(braket
id|i
)braket
dot
id|events
comma
op_amp
id|rfds
comma
op_amp
id|wfds
comma
op_amp
id|efds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|happened
)paren
(brace
id|pfd
(braket
id|i
)braket
dot
id|revents
op_assign
id|happened
suffix:semicolon
id|rc
op_increment
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
macro_line|#else
r_static
r_struct
id|timeval
id|tv0
suffix:semicolon
r_static
id|HANDLE
id|hEvent
suffix:semicolon
id|WSANETWORKEVENTS
id|ev
suffix:semicolon
id|HANDLE
id|h
comma
id|handle_array
(braket
id|FD_SETSIZE
op_plus
l_int|2
)braket
suffix:semicolon
id|DWORD
id|ret
comma
id|wait_timeout
comma
id|nhandles
suffix:semicolon
id|fd_set
id|rfds
comma
id|wfds
comma
id|xfds
suffix:semicolon
id|BOOL
id|poll_again
suffix:semicolon
id|MSG
id|msg
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|nfds_t
id|i
suffix:semicolon
r_if
c_cond
(paren
id|nfd
OL
l_int|0
op_logical_or
id|timeout
OL
l_int|1
)paren
(brace
id|errno
op_assign
id|EINVAL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hEvent
)paren
id|hEvent
op_assign
id|CreateEvent
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
id|restart
suffix:colon
id|handle_array
(braket
l_int|0
)braket
op_assign
id|hEvent
suffix:semicolon
id|nhandles
op_assign
l_int|1
suffix:semicolon
id|FD_ZERO
(paren
op_amp
id|rfds
)paren
suffix:semicolon
id|FD_ZERO
(paren
op_amp
id|wfds
)paren
suffix:semicolon
id|FD_ZERO
(paren
op_amp
id|xfds
)paren
suffix:semicolon
multiline_comment|/* Classify socket handles and create fd sets. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nfd
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|sought
op_assign
id|pfd
(braket
id|i
)braket
dot
id|events
suffix:semicolon
id|pfd
(braket
id|i
)braket
dot
id|revents
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sought
op_amp
(paren
id|POLLIN
op_or
id|POLLRDNORM
op_or
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
op_or
id|POLLPRI
op_or
id|POLLRDBAND
)paren
)paren
)paren
r_continue
suffix:semicolon
id|h
op_assign
(paren
id|HANDLE
)paren
id|_get_osfhandle
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
)paren
suffix:semicolon
m_assert
(paren
id|h
op_ne
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IsSocketHandle
(paren
id|h
)paren
)paren
(brace
r_int
id|requested
op_assign
id|FD_CLOSE
suffix:semicolon
multiline_comment|/* see above; socket handles are mapped onto select.  */
r_if
c_cond
(paren
id|sought
op_amp
(paren
id|POLLIN
op_or
id|POLLRDNORM
)paren
)paren
(brace
id|requested
op_or_assign
id|FD_READ
op_or
id|FD_ACCEPT
suffix:semicolon
id|FD_SET
(paren
(paren
id|SOCKET
)paren
id|h
comma
op_amp
id|rfds
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sought
op_amp
(paren
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
)paren
(brace
id|requested
op_or_assign
id|FD_WRITE
op_or
id|FD_CONNECT
suffix:semicolon
id|FD_SET
(paren
(paren
id|SOCKET
)paren
id|h
comma
op_amp
id|wfds
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sought
op_amp
(paren
id|POLLPRI
op_or
id|POLLRDBAND
)paren
)paren
(brace
id|requested
op_or_assign
id|FD_OOB
suffix:semicolon
id|FD_SET
(paren
(paren
id|SOCKET
)paren
id|h
comma
op_amp
id|xfds
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|requested
)paren
id|WSAEventSelect
(paren
(paren
id|SOCKET
)paren
id|h
comma
id|hEvent
comma
id|requested
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Poll now.  If we get an event, do not poll again.  Also,&n;&t;     screen buffer handles are waitable, and they&squot;ll block until&n;&t;     a character is available.  win32_compute_revents eliminates&n;&t;     bits for the &quot;wrong&quot; direction. */
id|pfd
(braket
id|i
)braket
dot
id|revents
op_assign
id|win32_compute_revents
(paren
id|h
comma
op_amp
id|sought
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sought
)paren
id|handle_array
(braket
id|nhandles
op_increment
)braket
op_assign
id|h
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|revents
)paren
id|timeout
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|select
(paren
l_int|0
comma
op_amp
id|rfds
comma
op_amp
id|wfds
comma
op_amp
id|xfds
comma
op_amp
id|tv0
)paren
OG
l_int|0
)paren
(brace
multiline_comment|/* Do MsgWaitForMultipleObjects anyway to dispatch messages, but&n;&t; no need to call select again.  */
id|poll_again
op_assign
id|FALSE
suffix:semicolon
id|wait_timeout
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|poll_again
op_assign
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
id|timeout
op_eq
id|INFTIM
)paren
id|wait_timeout
op_assign
id|INFINITE
suffix:semicolon
r_else
id|wait_timeout
op_assign
id|timeout
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|ret
op_assign
id|MsgWaitForMultipleObjects
(paren
id|nhandles
comma
id|handle_array
comma
id|FALSE
comma
id|wait_timeout
comma
id|QS_ALLINPUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|WAIT_OBJECT_0
op_plus
id|nhandles
)paren
(brace
multiline_comment|/* new input of some other kind */
id|BOOL
id|bRet
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bRet
op_assign
id|PeekMessage
(paren
op_amp
id|msg
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|PM_REMOVE
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|TranslateMessage
(paren
op_amp
id|msg
)paren
suffix:semicolon
id|DispatchMessage
(paren
op_amp
id|msg
)paren
suffix:semicolon
)brace
)brace
r_else
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|poll_again
)paren
id|select
(paren
l_int|0
comma
op_amp
id|rfds
comma
op_amp
id|wfds
comma
op_amp
id|xfds
comma
op_amp
id|tv0
)paren
suffix:semicolon
multiline_comment|/* Place a sentinel at the end of the array.  */
id|handle_array
(braket
id|nhandles
)braket
op_assign
l_int|NULL
suffix:semicolon
id|nhandles
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
id|nfd
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|happened
suffix:semicolon
r_if
c_cond
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pfd
(braket
id|i
)braket
dot
id|events
op_amp
(paren
id|POLLIN
op_or
id|POLLRDNORM
op_or
id|POLLOUT
op_or
id|POLLWRNORM
op_or
id|POLLWRBAND
)paren
)paren
)paren
r_continue
suffix:semicolon
id|h
op_assign
(paren
id|HANDLE
)paren
id|_get_osfhandle
(paren
id|pfd
(braket
id|i
)braket
dot
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h
op_ne
id|handle_array
(braket
id|nhandles
)braket
)paren
(brace
multiline_comment|/* It&squot;s a socket.  */
id|WSAEnumNetworkEvents
(paren
(paren
id|SOCKET
)paren
id|h
comma
l_int|NULL
comma
op_amp
id|ev
)paren
suffix:semicolon
id|WSAEventSelect
(paren
(paren
id|SOCKET
)paren
id|h
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* If we&squot;re lucky, WSAEnumNetworkEvents already provided a way&n;&t;     to distinguish FD_READ and FD_ACCEPT; this saves a recv later.  */
r_if
c_cond
(paren
id|FD_ISSET
(paren
(paren
id|SOCKET
)paren
id|h
comma
op_amp
id|rfds
)paren
op_logical_and
op_logical_neg
(paren
id|ev.lNetworkEvents
op_amp
(paren
id|FD_READ
op_or
id|FD_ACCEPT
)paren
)paren
)paren
id|ev.lNetworkEvents
op_or_assign
id|FD_READ
op_or
id|FD_ACCEPT
suffix:semicolon
r_if
c_cond
(paren
id|FD_ISSET
(paren
(paren
id|SOCKET
)paren
id|h
comma
op_amp
id|wfds
)paren
)paren
id|ev.lNetworkEvents
op_or_assign
id|FD_WRITE
op_or
id|FD_CONNECT
suffix:semicolon
r_if
c_cond
(paren
id|FD_ISSET
(paren
(paren
id|SOCKET
)paren
id|h
comma
op_amp
id|xfds
)paren
)paren
id|ev.lNetworkEvents
op_or_assign
id|FD_OOB
suffix:semicolon
id|happened
op_assign
id|win32_compute_revents_socket
(paren
(paren
id|SOCKET
)paren
id|h
comma
id|pfd
(braket
id|i
)braket
dot
id|events
comma
id|ev.lNetworkEvents
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Not a socket.  */
r_int
id|sought
op_assign
id|pfd
(braket
id|i
)braket
dot
id|events
suffix:semicolon
id|happened
op_assign
id|win32_compute_revents
(paren
id|h
comma
op_amp
id|sought
)paren
suffix:semicolon
id|nhandles
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pfd
(braket
id|i
)braket
dot
id|revents
op_or_assign
id|happened
)paren
op_ne
l_int|0
)paren
id|rc
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_and
id|timeout
op_eq
id|INFTIM
)paren
(brace
id|SwitchToThread
c_func
(paren
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
macro_line|#endif
)brace
eof
