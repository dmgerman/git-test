DECL|macro|WIN32_LEAN_AND_MEAN
mdefine_line|#define WIN32_LEAN_AND_MEAN
macro_line|#ifdef CYGWIN_V15_WIN32API
macro_line|#include &quot;../git-compat-util.h&quot;
macro_line|#include &quot;win32.h&quot;
macro_line|#else
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/errno.h&gt;
macro_line|#include &quot;win32.h&quot;
macro_line|#include &quot;../git-compat-util.h&quot;
macro_line|#endif
macro_line|#include &quot;../cache.h&quot; /* to read configuration */
DECL|function|filetime_to_timespec
r_static
r_inline
r_void
id|filetime_to_timespec
c_func
(paren
r_const
id|FILETIME
op_star
id|ft
comma
r_struct
id|timespec
op_star
id|ts
)paren
(brace
r_int
r_int
id|winTime
op_assign
(paren
(paren
r_int
r_int
)paren
id|ft-&gt;dwHighDateTime
op_lshift
l_int|32
)paren
op_plus
id|ft-&gt;dwLowDateTime
suffix:semicolon
id|winTime
op_sub_assign
l_int|116444736000000000LL
suffix:semicolon
multiline_comment|/* Windows to Unix Epoch conversion */
multiline_comment|/* convert 100-nsecond interval to seconds and nanoseconds */
id|ts-&gt;tv_sec
op_assign
(paren
id|time_t
)paren
(paren
id|winTime
op_div
l_int|10000000
)paren
suffix:semicolon
id|ts-&gt;tv_nsec
op_assign
(paren
r_int
)paren
(paren
id|winTime
id|ts-&gt;tv_sec
op_star
l_int|10000000LL
)paren
op_star
l_int|100
suffix:semicolon
)brace
DECL|macro|size_to_blocks
mdefine_line|#define size_to_blocks(s) (((s)+511)/512)
multiline_comment|/* do_stat is a common implementation for cygwin_lstat and cygwin_stat.&n; *&n; * To simplify its logic, in the case of cygwin symlinks, this implementation&n; * falls back to the cygwin version of stat/lstat, which is provided as the&n; * last argument.&n; */
DECL|function|do_stat
r_static
r_int
id|do_stat
c_func
(paren
r_const
r_char
op_star
id|file_name
comma
r_struct
id|stat
op_star
id|buf
comma
id|stat_fn_t
id|cygstat
)paren
(brace
id|WIN32_FILE_ATTRIBUTE_DATA
id|fdata
suffix:semicolon
r_if
c_cond
(paren
id|file_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
id|cygstat
(paren
id|file_name
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|errno
op_assign
id|get_file_attr
c_func
(paren
id|file_name
comma
op_amp
id|fdata
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the system attribute is set and it is not a directory then&n;&t;&t; * it could be a symbol link created in the nowinsymlinks mode.&n;&t;&t; * Normally, Cygwin works in the winsymlinks mode, so this situation&n;&t;&t; * is very unlikely. For the sake of simplicity of our code, let&squot;s&n;&t;&t; * Cygwin to handle it.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|fdata.dwFileAttributes
op_amp
id|FILE_ATTRIBUTE_SYSTEM
)paren
op_logical_and
op_logical_neg
(paren
id|fdata.dwFileAttributes
op_amp
id|FILE_ATTRIBUTE_DIRECTORY
)paren
)paren
r_return
id|cygstat
c_func
(paren
id|file_name
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* fill out the stat structure */
id|buf-&gt;st_dev
op_assign
id|buf-&gt;st_rdev
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* not used by Git */
id|buf-&gt;st_ino
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;st_mode
op_assign
id|file_attr_to_st_mode
c_func
(paren
id|fdata.dwFileAttributes
)paren
suffix:semicolon
id|buf-&gt;st_nlink
op_assign
l_int|1
suffix:semicolon
id|buf-&gt;st_uid
op_assign
id|buf-&gt;st_gid
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __CYGWIN_USE_BIG_TYPES__
id|buf-&gt;st_size
op_assign
(paren
(paren
id|_off64_t
)paren
id|fdata.nFileSizeHigh
op_lshift
l_int|32
)paren
op_plus
id|fdata.nFileSizeLow
suffix:semicolon
macro_line|#else
id|buf-&gt;st_size
op_assign
(paren
id|off_t
)paren
id|fdata.nFileSizeLow
suffix:semicolon
macro_line|#endif
id|buf-&gt;st_blocks
op_assign
id|size_to_blocks
c_func
(paren
id|buf-&gt;st_size
)paren
suffix:semicolon
id|filetime_to_timespec
c_func
(paren
op_amp
id|fdata.ftLastAccessTime
comma
op_amp
id|buf-&gt;st_atim
)paren
suffix:semicolon
id|filetime_to_timespec
c_func
(paren
op_amp
id|fdata.ftLastWriteTime
comma
op_amp
id|buf-&gt;st_mtim
)paren
suffix:semicolon
id|filetime_to_timespec
c_func
(paren
op_amp
id|fdata.ftCreationTime
comma
op_amp
id|buf-&gt;st_ctim
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
(brace
multiline_comment|/*&n;&t;&t; * In the winsymlinks mode (which is the default), Cygwin&n;&t;&t; * emulates symbol links using Windows shortcut files. These&n;&t;&t; * files are formed by adding .lnk extension. So, if we have&n;&t;&t; * not found the specified file name, it could be that it is&n;&t;&t; * a symbol link. Let&squot;s Cygwin to deal with that.&n;&t;&t; */
r_return
id|cygstat
c_func
(paren
id|file_name
comma
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* We provide our own lstat/stat functions, since the provided Cygwin versions&n; * of these functions are too slow. These stat functions are tailored for Git&squot;s&n; * usage, and therefore they are not meant to be complete and correct emulation&n; * of lstat/stat functionality.&n; */
DECL|function|cygwin_lstat
r_static
r_int
id|cygwin_lstat
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|stat
op_star
id|buf
)paren
(brace
r_return
id|do_stat
c_func
(paren
id|path
comma
id|buf
comma
id|lstat
)paren
suffix:semicolon
)brace
DECL|function|cygwin_stat
r_static
r_int
id|cygwin_stat
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|stat
op_star
id|buf
)paren
(brace
r_return
id|do_stat
c_func
(paren
id|path
comma
id|buf
comma
id|stat
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * At start up, we are trying to determine whether Win32 API or cygwin stat&n; * functions should be used. The choice is determined by core.ignorecygwinfstricks.&n; * Reading this option is not always possible immediately as git_dir may&n; * not be set yet. So until it is set, use cygwin lstat/stat functions.&n; * However, if core.filemode is set, we must use the Cygwin posix&n; * stat/lstat as the Windows stat functions do not determine posix filemode.&n; *&n; * Note that git_cygwin_config() does NOT call git_default_config() and this&n; * is deliberate.  Many commands read from config to establish initial&n; * values in variables and later tweak them from elsewhere (e.g. command line).&n; * init_stat() is called lazily on demand, typically much late in the program,&n; * and calling git_default_config() from here would break such variables.&n; */
DECL|variable|native_stat
r_static
r_int
id|native_stat
op_assign
l_int|1
suffix:semicolon
DECL|variable|core_filemode
r_static
r_int
id|core_filemode
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* matches trust_executable_bit default */
DECL|function|git_cygwin_config
r_static
r_int
id|git_cygwin_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.ignorecygwinfstricks&quot;
)paren
)paren
id|native_stat
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;core.filemode&quot;
)paren
)paren
id|core_filemode
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_stat
r_static
r_int
id|init_stat
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|have_git_dir
c_func
(paren
)paren
op_logical_and
id|git_config
c_func
(paren
id|git_cygwin_config
comma
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|core_filemode
op_logical_and
id|native_stat
)paren
(brace
id|cygwin_stat_fn
op_assign
id|cygwin_stat
suffix:semicolon
id|cygwin_lstat_fn
op_assign
id|cygwin_lstat
suffix:semicolon
)brace
r_else
(brace
id|cygwin_stat_fn
op_assign
id|stat
suffix:semicolon
id|cygwin_lstat_fn
op_assign
id|lstat
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cygwin_stat_stub
r_static
r_int
id|cygwin_stat_stub
c_func
(paren
r_const
r_char
op_star
id|file_name
comma
r_struct
id|stat
op_star
id|buf
)paren
(brace
r_return
(paren
id|init_stat
c_func
(paren
)paren
ques
c_cond
id|stat
suffix:colon
op_star
id|cygwin_stat_fn
)paren
(paren
id|file_name
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|cygwin_lstat_stub
r_static
r_int
id|cygwin_lstat_stub
c_func
(paren
r_const
r_char
op_star
id|file_name
comma
r_struct
id|stat
op_star
id|buf
)paren
(brace
r_return
(paren
id|init_stat
c_func
(paren
)paren
ques
c_cond
id|lstat
suffix:colon
op_star
id|cygwin_lstat_fn
)paren
(paren
id|file_name
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|variable|cygwin_stat_fn
id|stat_fn_t
id|cygwin_stat_fn
op_assign
id|cygwin_stat_stub
suffix:semicolon
DECL|variable|cygwin_lstat_fn
id|stat_fn_t
id|cygwin_lstat_fn
op_assign
id|cygwin_lstat_stub
suffix:semicolon
eof
