macro_line|#include &quot;cache.h&quot;
DECL|macro|MTIME_CHANGED
mdefine_line|#define MTIME_CHANGED&t;0x0001
DECL|macro|CTIME_CHANGED
mdefine_line|#define CTIME_CHANGED&t;0x0002
DECL|macro|OWNER_CHANGED
mdefine_line|#define OWNER_CHANGED&t;0x0004
DECL|macro|MODE_CHANGED
mdefine_line|#define MODE_CHANGED    0x0008
DECL|macro|INODE_CHANGED
mdefine_line|#define INODE_CHANGED   0x0010
DECL|macro|DATA_CHANGED
mdefine_line|#define DATA_CHANGED    0x0020
DECL|function|match_stat
r_static
r_int
id|match_stat
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_struct
id|stat
op_star
id|st
)paren
(brace
r_int
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;mtime.sec
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_mtim.tv_sec
op_logical_or
id|ce-&gt;mtime.nsec
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_mtim.tv_nsec
)paren
id|changed
op_or_assign
id|MTIME_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ctime.sec
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_ctim.tv_sec
op_logical_or
id|ce-&gt;ctime.nsec
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_ctim.tv_nsec
)paren
id|changed
op_or_assign
id|CTIME_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;st_uid
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_uid
op_logical_or
id|ce-&gt;st_gid
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_gid
)paren
id|changed
op_or_assign
id|OWNER_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;st_mode
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_mode
)paren
id|changed
op_or_assign
id|MODE_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;st_dev
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_dev
op_logical_or
id|ce-&gt;st_ino
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_ino
)paren
id|changed
op_or_assign
id|INODE_CHANGED
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;st_size
op_ne
(paren
r_int
r_int
)paren
id|st-&gt;st_size
)paren
id|changed
op_or_assign
id|DATA_CHANGED
suffix:semicolon
r_return
id|changed
suffix:semicolon
)brace
DECL|function|show_differences
r_static
r_void
id|show_differences
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_struct
id|stat
op_star
id|cur
comma
r_void
op_star
id|old_contents
comma
r_int
r_int
r_int
id|old_size
)paren
(brace
r_static
r_char
id|cmd
(braket
l_int|1000
)braket
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
id|snprintf
c_func
(paren
id|cmd
comma
r_sizeof
(paren
id|cmd
)paren
comma
l_string|&quot;diff -u - %s&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|f
op_assign
id|popen
c_func
(paren
id|cmd
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
id|fwrite
c_func
(paren
id|old_contents
comma
id|old_size
comma
l_int|1
comma
id|f
)paren
suffix:semicolon
id|pclose
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;read_cache&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|entries
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_int
id|n
comma
id|changed
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
r_new
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|ce-&gt;name
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|changed
op_assign
id|match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s: ok&bslash;n&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%.*s:  &quot;
comma
id|ce-&gt;namelen
comma
id|ce-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|20
suffix:semicolon
id|n
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%02x&quot;
comma
id|ce-&gt;sha1
(braket
id|n
)braket
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_new
op_assign
id|read_sha1_file
c_func
(paren
id|ce-&gt;sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
id|show_differences
c_func
(paren
id|ce
comma
op_amp
id|st
comma
r_new
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
