multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &lt;signal.h&gt;
macro_line|#include &quot;cache.h&quot;
multiline_comment|/*&n; * Default to not allowing changes to the list of files. The&n; * tool doesn&squot;t actually care, but this makes it harder to add&n; * files to the revision control by mistake by doing something&n; * like &quot;update-cache *&quot; and suddenly having all the object&n; * files be revision controlled.&n; */
DECL|variable|allow_add
DECL|variable|allow_remove
DECL|variable|allow_replace
DECL|variable|not_new
r_static
r_int
id|allow_add
op_assign
l_int|0
comma
id|allow_remove
op_assign
l_int|0
comma
id|allow_replace
op_assign
l_int|0
comma
id|not_new
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Three functions to allow overloaded pointer return; see linux/err.h */
DECL|function|ERR_PTR
r_static
r_inline
r_void
op_star
id|ERR_PTR
c_func
(paren
r_int
id|error
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|error
suffix:semicolon
)brace
DECL|function|PTR_ERR
r_static
r_inline
r_int
id|PTR_ERR
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
r_int
)paren
id|ptr
suffix:semicolon
)brace
DECL|function|IS_ERR
r_static
r_inline
r_int
id|IS_ERR
c_func
(paren
r_const
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|ptr
OG
(paren
r_int
r_int
)paren
op_minus
l_int|1000L
suffix:semicolon
)brace
multiline_comment|/*&n; * This only updates the &quot;non-critical&quot; parts of the directory&n; * cache, ie the parts that aren&squot;t tracked by GIT, and only used&n; * to validate the cache.&n; */
DECL|function|fill_stat_cache_info
r_static
r_void
id|fill_stat_cache_info
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
id|ce-&gt;ce_ctime.sec
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_ctime
)paren
suffix:semicolon
id|ce-&gt;ce_mtime.sec
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_mtime
)paren
suffix:semicolon
macro_line|#ifdef NSEC
id|ce-&gt;ce_ctime.nsec
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_ctim.tv_nsec
)paren
suffix:semicolon
id|ce-&gt;ce_mtime.nsec
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_mtim.tv_nsec
)paren
suffix:semicolon
macro_line|#endif
id|ce-&gt;ce_dev
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_dev
)paren
suffix:semicolon
id|ce-&gt;ce_ino
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_ino
)paren
suffix:semicolon
id|ce-&gt;ce_uid
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_uid
)paren
suffix:semicolon
id|ce-&gt;ce_gid
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_gid
)paren
suffix:semicolon
id|ce-&gt;ce_size
op_assign
id|htonl
c_func
(paren
id|st-&gt;st_size
)paren
suffix:semicolon
)brace
DECL|function|add_file_to_cache
r_static
r_int
id|add_file_to_cache
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_int
id|size
comma
id|namelen
comma
id|option
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_char
op_star
id|target
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
op_logical_or
id|errno
op_eq
id|ENOTDIR
)paren
(brace
r_if
c_cond
(paren
id|allow_remove
)paren
r_return
id|remove_file_from_cache
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|namelen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|namelen
)paren
suffix:semicolon
id|ce
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ce
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|namelen
)paren
suffix:semicolon
id|fill_stat_cache_info
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|st.st_mode
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|htons
c_func
(paren
id|namelen
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|st.st_mode
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFREG
suffix:colon
id|fd
op_assign
id|open
c_func
(paren
id|path
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
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|index_fd
c_func
(paren
id|ce-&gt;sha1
comma
id|fd
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|target
op_assign
id|xmalloc
c_func
(paren
id|st.st_size
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|readlink
c_func
(paren
id|path
comma
id|target
comma
id|st.st_size
op_plus
l_int|1
)paren
op_ne
id|st.st_size
)paren
(brace
id|free
c_func
(paren
id|target
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|target
comma
id|st.st_size
comma
l_string|&quot;blob&quot;
comma
id|ce-&gt;sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|target
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
id|option
op_assign
id|allow_add
ques
c_cond
id|ADD_CACHE_OK_TO_ADD
suffix:colon
l_int|0
suffix:semicolon
id|option
op_or_assign
id|allow_replace
ques
c_cond
id|ADD_CACHE_OK_TO_REPLACE
suffix:colon
l_int|0
suffix:semicolon
r_return
id|add_cache_entry
c_func
(paren
id|ce
comma
id|option
)paren
suffix:semicolon
)brace
DECL|function|match_data
r_static
r_int
id|match_data
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_while
c_loop
(paren
id|size
)paren
(brace
r_char
id|compare
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|ret
op_assign
id|read
c_func
(paren
id|fd
comma
id|compare
comma
r_sizeof
(paren
id|compare
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_le
l_int|0
op_logical_or
id|ret
OG
id|size
op_logical_or
id|memcmp
c_func
(paren
id|buffer
comma
id|compare
comma
id|ret
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|size
op_sub_assign
id|ret
suffix:semicolon
id|buffer
op_add_assign
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compare_data
r_static
r_int
id|compare_data
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_int
id|expected_size
)paren
(brace
r_int
id|match
op_assign
l_int|1
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|ce-&gt;name
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|10
)braket
suffix:semicolon
id|buffer
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
r_if
c_cond
(paren
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
id|expected_size
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;blob&quot;
)paren
)paren
id|match
op_assign
id|match_data
c_func
(paren
id|fd
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
r_return
id|match
suffix:semicolon
)brace
DECL|function|compare_link
r_static
r_int
id|compare_link
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_int
id|expected_size
)paren
(brace
r_int
id|match
op_assign
l_int|1
suffix:semicolon
r_char
op_star
id|target
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_char
id|type
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|target
op_assign
id|xmalloc
c_func
(paren
id|expected_size
)paren
suffix:semicolon
id|len
op_assign
id|readlink
c_func
(paren
id|ce-&gt;name
comma
id|target
comma
id|expected_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
id|expected_size
)paren
(brace
id|free
c_func
(paren
id|target
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|buffer
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
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|free
c_func
(paren
id|target
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_eq
id|expected_size
)paren
id|match
op_assign
id|memcmp
c_func
(paren
id|buffer
comma
id|target
comma
id|size
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|free
c_func
(paren
id|target
)paren
suffix:semicolon
r_return
id|match
suffix:semicolon
)brace
multiline_comment|/*&n; * &quot;refresh&quot; does not calculate a new sha1 file or bring the&n; * cache up-to-date for mode/content changes. But what it&n; * _does_ do is to &quot;re-match&quot; the stat information of a file&n; * with the cache, so that you can refresh the cache for a&n; * file that hasn&squot;t been changed but where the stat entry is&n; * out of date.&n; *&n; * For example, you&squot;d want to do this after doing a &quot;read-tree&quot;,&n; * to link up the stat cache details with the proper files.&n; */
DECL|function|refresh_entry
r_static
r_struct
id|cache_entry
op_star
id|refresh_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_struct
id|cache_entry
op_star
id|updated
suffix:semicolon
r_int
id|changed
comma
id|size
suffix:semicolon
r_if
c_cond
(paren
id|lstat
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
r_return
id|ERR_PTR
c_func
(paren
id|errno
)paren
suffix:semicolon
id|changed
op_assign
id|cache_match_stat
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
r_return
id|ce
suffix:semicolon
multiline_comment|/*&n;&t; * If the mode or type has changed, there&squot;s no point in trying&n;&t; * to refresh the entry - it&squot;s not going to match&n;&t; */
r_if
c_cond
(paren
id|changed
op_amp
(paren
id|MODE_CHANGED
op_or
id|TYPE_CHANGED
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|st.st_mode
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFREG
suffix:colon
r_if
c_cond
(paren
id|compare_data
c_func
(paren
id|ce
comma
id|st.st_size
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
r_if
c_cond
(paren
id|compare_link
c_func
(paren
id|ce
comma
id|st.st_size
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
id|size
op_assign
id|ce_size
c_func
(paren
id|ce
)paren
suffix:semicolon
id|updated
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|updated
comma
id|ce
comma
id|size
)paren
suffix:semicolon
id|fill_stat_cache_info
c_func
(paren
id|updated
comma
op_amp
id|st
)paren
suffix:semicolon
r_return
id|updated
suffix:semicolon
)brace
DECL|function|refresh_cache
r_static
r_int
id|refresh_cache
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|has_errors
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
comma
op_star
r_new
suffix:semicolon
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s: needs merge&bslash;n&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|has_errors
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
OL
id|active_nr
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|ce-&gt;name
)paren
)paren
id|i
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_new
op_assign
id|refresh_entry
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
r_new
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|not_new
op_logical_and
id|PTR_ERR
c_func
(paren
r_new
)paren
op_eq
id|ENOENT
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s: needs update&bslash;n&quot;
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|has_errors
op_assign
l_int|1
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|active_cache_changed
op_assign
l_int|1
suffix:semicolon
id|active_cache
(braket
id|i
)braket
op_assign
r_new
suffix:semicolon
)brace
r_return
id|has_errors
suffix:semicolon
)brace
multiline_comment|/*&n; * We fundamentally don&squot;t like some paths: we don&squot;t want&n; * dot or dot-dot anywhere, and in fact, we don&squot;t even want&n; * any other dot-files (.git or anything else). They&n; * are hidden, for chist sake.&n; *&n; * Also, we don&squot;t want double slashes or slashes at the&n; * end that can make pathnames ambiguous.&n; */
DECL|function|verify_path
r_static
r_int
id|verify_path
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_char
id|c
suffix:semicolon
r_goto
id|inside
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
op_logical_neg
id|c
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|inside
suffix:colon
id|c
op_assign
op_star
id|path
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;/&squot;
op_logical_and
id|c
op_ne
l_char|&squot;.&squot;
op_logical_and
id|c
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|c
op_assign
op_star
id|path
op_increment
suffix:semicolon
)brace
)brace
DECL|function|add_cacheinfo
r_static
r_int
id|add_cacheinfo
c_func
(paren
r_char
op_star
id|arg1
comma
r_char
op_star
id|arg2
comma
r_char
op_star
id|arg3
)paren
(brace
r_int
id|size
comma
id|len
comma
id|option
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|arg1
comma
l_string|&quot;%o&quot;
comma
op_amp
id|mode
)paren
op_ne
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|arg2
comma
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|arg3
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|arg3
)paren
suffix:semicolon
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|len
)paren
suffix:semicolon
id|ce
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ce
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|arg3
comma
id|len
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|htons
c_func
(paren
id|len
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|option
op_assign
id|allow_add
ques
c_cond
id|ADD_CACHE_OK_TO_ADD
suffix:colon
l_int|0
suffix:semicolon
id|option
op_or_assign
id|allow_replace
ques
c_cond
id|ADD_CACHE_OK_TO_REPLACE
suffix:colon
l_int|0
suffix:semicolon
r_return
id|add_cache_entry
c_func
(paren
id|ce
comma
id|option
)paren
suffix:semicolon
)brace
DECL|variable|lockfile_name
r_static
r_const
r_char
op_star
id|lockfile_name
op_assign
l_int|NULL
suffix:semicolon
DECL|function|remove_lock_file
r_static
r_void
id|remove_lock_file
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|lockfile_name
)paren
id|unlink
c_func
(paren
id|lockfile_name
)paren
suffix:semicolon
)brace
DECL|function|remove_lock_file_on_signal
r_static
r_void
id|remove_lock_file_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_lock_file
c_func
(paren
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
id|i
comma
id|newfd
comma
id|entries
comma
id|has_errors
op_assign
l_int|0
suffix:semicolon
r_int
id|allow_options
op_assign
l_int|1
suffix:semicolon
r_static
r_char
id|lockfile
(braket
id|MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
r_const
r_char
op_star
id|indexfile
op_assign
id|get_index_file
c_func
(paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|lockfile
comma
r_sizeof
(paren
id|lockfile
)paren
comma
l_string|&quot;%s.lock&quot;
comma
id|indexfile
)paren
suffix:semicolon
id|newfd
op_assign
id|open
c_func
(paren
id|lockfile
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0600
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newfd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to create new cachefile&quot;
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGINT
comma
id|remove_lock_file_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_lock_file
)paren
suffix:semicolon
id|lockfile_name
op_assign
id|lockfile
suffix:semicolon
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;cache corrupted&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|path
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|allow_options
op_logical_and
op_star
id|path
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|allow_options
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--add&quot;
)paren
)paren
(brace
id|allow_add
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--replace&quot;
)paren
)paren
(brace
id|allow_replace
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--remove&quot;
)paren
)paren
(brace
id|allow_remove
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--refresh&quot;
)paren
)paren
(brace
id|has_errors
op_or_assign
id|refresh_cache
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--cacheinfo&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_plus
l_int|3
op_ge
id|argc
op_logical_or
id|add_cacheinfo
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
comma
id|argv
(braket
id|i
op_plus
l_int|2
)braket
comma
id|argv
(braket
id|i
op_plus
l_int|3
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;update-cache: --cacheinfo &lt;mode&gt; &lt;sha1&gt; &lt;path&gt;&quot;
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--force-remove&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
op_le
id|i
op_plus
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;update-cache: --force-remove &lt;path&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;update-cache: --force-remove cannot remove %s&quot;
comma
id|argv
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--ignore-missing&quot;
)paren
)paren
(brace
id|not_new
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;unknown option %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|path
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Ignoring path %s&bslash;n&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|add_file_to_cache
c_func
(paren
id|path
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to add %s to database&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|rename
c_func
(paren
id|lockfile
comma
id|indexfile
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new cachefile&quot;
)paren
suffix:semicolon
id|lockfile_name
op_assign
l_int|NULL
suffix:semicolon
r_return
id|has_errors
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
