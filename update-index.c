multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;quote.h&quot;
multiline_comment|/*&n; * Default to not allowing changes to the list of files. The&n; * tool doesn&squot;t actually care, but this makes it harder to add&n; * files to the revision control by mistake by doing something&n; * like &quot;git-update-index *&quot; and suddenly having all the object&n; * files be revision controlled.&n; */
DECL|variable|allow_add
r_static
r_int
id|allow_add
suffix:semicolon
DECL|variable|allow_remove
r_static
r_int
id|allow_remove
suffix:semicolon
DECL|variable|allow_replace
r_static
r_int
id|allow_replace
suffix:semicolon
DECL|variable|allow_unmerged
r_static
r_int
id|allow_unmerged
suffix:semicolon
multiline_comment|/* --refresh needing merge is not error */
DECL|variable|not_new
r_static
r_int
id|not_new
suffix:semicolon
multiline_comment|/* --refresh not having working tree files is not error */
DECL|variable|quiet
r_static
r_int
id|quiet
suffix:semicolon
multiline_comment|/* --refresh needing update is not error */
DECL|variable|info_only
r_static
r_int
id|info_only
suffix:semicolon
DECL|variable|force_remove
r_static
r_int
id|force_remove
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
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
DECL|function|report
r_static
r_void
id|report
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
id|vp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose
)paren
r_return
suffix:semicolon
id|va_start
c_func
(paren
id|vp
comma
id|fmt
)paren
suffix:semicolon
id|vprintf
c_func
(paren
id|fmt
comma
id|vp
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
DECL|function|add_file_to_cache
r_static
r_int
id|add_file_to_cache
c_func
(paren
r_const
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
comma
id|status
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
id|status
op_assign
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
op_logical_or
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
multiline_comment|/* When we used to have &quot;path&quot; and now we want to add&n;&t;&t; * &quot;path/file&quot;, we need a way to remove &quot;path&quot; before&n;&t;&t; * being able to add &quot;path/file&quot;.  However,&n;&t;&t; * &quot;git-update-index --remove path&quot; would not work.&n;&t;&t; * --force-remove can be used but this is more user&n;&t;&t; * friendly, especially since we can do the opposite&n;&t;&t; * case just fine without --force-remove.&n;&t;&t; */
r_if
c_cond
(paren
id|status
op_eq
l_int|0
op_logical_or
(paren
id|errno
op_eq
id|ENOENT
op_logical_or
id|errno
op_eq
id|ENOTDIR
)paren
)paren
(brace
r_if
c_cond
(paren
id|allow_remove
)paren
(brace
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|path
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot remove from the index&quot;
comma
id|path
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
(brace
r_return
id|error
c_func
(paren
l_string|&quot;%s: does not exist and --remove not passed&quot;
comma
id|path
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|status
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: is a directory - add files inside instead&quot;
comma
id|path
)paren
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;lstat(&bslash;&quot;%s&bslash;&quot;): %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|trust_executable_bit
)paren
(brace
multiline_comment|/* If there is an existing entry, pick the mode bits&n;&t;&t; * from it.&n;&t;&t; */
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
id|ce-&gt;ce_mode
op_assign
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|ce_mode
suffix:semicolon
)brace
id|ce-&gt;ce_flags
op_assign
id|htons
c_func
(paren
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index_path
c_func
(paren
id|ce-&gt;sha1
comma
id|path
comma
op_amp
id|st
comma
op_logical_neg
id|info_only
)paren
)paren
r_return
l_int|1
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
r_if
c_cond
(paren
id|add_cache_entry
c_func
(paren
id|ce
comma
id|option
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot add to the index - missing --add option?&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * &quot;refresh&quot; does not calculate a new sha1 file or bring the&n; * cache up-to-date for mode/content changes. But what it&n; * _does_ do is to &quot;re-match&quot; the stat information of a file&n; * with the cache, so that you can refresh the cache for a&n; * file that hasn&squot;t been changed but where the stat entry is&n; * out of date.&n; *&n; * For example, you&squot;d want to do this after doing a &quot;git-read-tree&quot;,&n; * to link up the stat cache details with the proper files.&n; */
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
id|ce_match_stat
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
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ce_modified
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
id|EINVAL
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|allow_unmerged
)paren
r_continue
suffix:semicolon
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
op_logical_neg
r_new
)paren
r_continue
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
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|quiet
)paren
r_continue
suffix:semicolon
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
r_continue
suffix:semicolon
)brace
id|active_cache_changed
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* You can NOT just free active_cache[i] here, since it&n;&t;&t; * might not be necessarily malloc()ed but can also come&n;&t;&t; * from mmap(). */
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
multiline_comment|/*&n; * We fundamentally don&squot;t like some paths: we don&squot;t want&n; * dot or dot-dot anywhere, and for obvious reasons don&squot;t&n; * want to recurse into &quot;.git&quot; either.&n; *&n; * Also, we don&squot;t want double slashes or slashes at the&n; * end that can make pathnames ambiguous.&n; */
DECL|function|verify_dotfile
r_static
r_int
id|verify_dotfile
c_func
(paren
r_const
r_char
op_star
id|rest
)paren
(brace
multiline_comment|/*&n;&t; * The first character was &squot;.&squot;, but that&n;&t; * has already been discarded, we now test&n;&t; * the rest.&n;&t; */
r_switch
c_cond
(paren
op_star
id|rest
)paren
(brace
multiline_comment|/* &quot;.&quot; is not allowed */
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
r_case
l_char|&squot;/&squot;
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;.git&quot; followed by  NUL or slash is bad. This&n;&t; * shares the path end test with the &quot;..&quot; case.&n;&t; */
r_case
l_char|&squot;g&squot;
suffix:colon
r_if
c_cond
(paren
id|rest
(braket
l_int|1
)braket
op_ne
l_char|&squot;i&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|rest
(braket
l_int|2
)braket
op_ne
l_char|&squot;t&squot;
)paren
r_break
suffix:semicolon
id|rest
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
l_char|&squot;.&squot;
suffix:colon
r_if
c_cond
(paren
id|rest
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|rest
(braket
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|verify_path
r_static
r_int
id|verify_path
c_func
(paren
r_const
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
r_switch
c_cond
(paren
id|c
)paren
(brace
r_default
suffix:colon
r_continue
suffix:semicolon
r_case
l_char|&squot;/&squot;
suffix:colon
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
r_break
suffix:semicolon
r_case
l_char|&squot;.&squot;
suffix:colon
r_if
c_cond
(paren
id|verify_dotfile
c_func
(paren
id|path
)paren
)paren
r_continue
suffix:semicolon
)brace
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
r_const
r_char
op_star
id|arg1
comma
r_const
r_char
op_star
id|arg2
comma
r_const
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
r_if
c_cond
(paren
id|add_cache_entry
c_func
(paren
id|ce
comma
id|option
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot add to the index - missing --add option?&quot;
comma
id|arg3
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;add &squot;%s&squot;&quot;
comma
id|arg3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chmod_path
r_static
r_int
id|chmod_path
c_func
(paren
r_int
id|flip
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|pos
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
id|mode
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|flip
)paren
(brace
r_case
l_char|&squot;+&squot;
suffix:colon
id|ce-&gt;ce_mode
op_or_assign
id|htonl
c_func
(paren
l_int|0111
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
id|ce-&gt;ce_mode
op_and_assign
id|htonl
c_func
(paren
op_complement
l_int|0111
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
id|active_cache_changed
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cache_file
r_static
r_struct
id|cache_file
id|cache_file
suffix:semicolon
DECL|function|update_one
r_static
r_void
id|update_one
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|prefix
comma
r_int
id|prefix_length
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|p
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
id|path
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|force_remove
)paren
(brace
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|p
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: unable to remove %s&quot;
comma
id|path
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;remove &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|add_file_to_cache
c_func
(paren
id|p
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to process file %s&quot;
comma
id|path
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;add &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|read_index_info
r_static
r_void
id|read_index_info
c_func
(paren
r_int
id|line_termination
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
r_char
op_star
id|path_name
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
id|read_line
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.eof
)paren
r_break
suffix:semicolon
id|mode
op_assign
id|strtoul
c_func
(paren
id|buf.buf
comma
op_amp
id|ptr
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
id|buf.buf
op_logical_or
op_star
id|ptr
op_ne
l_char|&squot; &squot;
op_logical_or
id|get_sha1_hex
c_func
(paren
id|ptr
op_plus
l_int|1
comma
id|sha1
)paren
op_logical_or
id|ptr
(braket
l_int|41
)braket
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_goto
id|bad_line
suffix:semicolon
id|ptr
op_add_assign
l_int|42
suffix:semicolon
r_if
c_cond
(paren
id|line_termination
op_logical_and
id|ptr
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
id|path_name
op_assign
id|unquote_c_style
c_func
(paren
id|ptr
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|path_name
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|path_name
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
id|path_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path_name
op_ne
id|ptr
)paren
id|free
c_func
(paren
id|path_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mode
)paren
(brace
multiline_comment|/* mode == 0 means there is no such path -- remove */
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|path_name
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: unable to remove %s&quot;
comma
id|ptr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* mode &squot; &squot; sha1 &squot;&bslash;t&squot; name&n;&t;&t;&t; * ptr[-1] points at tab,&n;&t;&t;&t; * ptr[-41] is at the beginning of sha1&n;&t;&t;&t; */
id|ptr
(braket
l_int|42
)braket
op_assign
id|ptr
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|add_cacheinfo
c_func
(paren
id|buf.buf
comma
id|ptr
op_minus
l_int|41
comma
id|path_name
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: unable to update %s&quot;
comma
id|path_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path_name
op_ne
id|ptr
)paren
id|free
c_func
(paren
id|path_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
id|bad_line
suffix:colon
id|die
c_func
(paren
l_string|&quot;malformed index info %s&quot;
comma
id|buf.buf
)paren
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_const
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
comma
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_int
id|allow_options
op_assign
l_int|1
suffix:semicolon
r_int
id|read_from_stdin
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|prefix_length
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_index_file_for_update
c_func
(paren
op_amp
id|cache_file
comma
id|get_index_file
c_func
(paren
)paren
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
r_const
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
l_string|&quot;-q&quot;
)paren
)paren
(brace
id|quiet
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
l_string|&quot;--unmerged&quot;
)paren
)paren
(brace
id|allow_unmerged
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
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: --cacheinfo &lt;mode&gt; &lt;sha1&gt; &lt;path&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
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
l_string|&quot;git-update-index: --cacheinfo cannot add %s&quot;
comma
id|argv
(braket
id|i
op_plus
l_int|3
)braket
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
l_string|&quot;--chmod=-x&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--chmod=+x&quot;
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
l_string|&quot;git-update-index: %s &lt;path&gt;&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chmod_path
c_func
(paren
id|path
(braket
l_int|8
)braket
comma
id|argv
(braket
op_increment
id|i
)braket
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: %s cannot chmod %s&quot;
comma
id|path
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
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--info-only&quot;
)paren
)paren
(brace
id|info_only
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
l_string|&quot;--force-remove&quot;
)paren
)paren
(brace
id|force_remove
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
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_termination
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
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|argc
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;--stdin must be at the end&quot;
)paren
suffix:semicolon
id|read_from_stdin
op_assign
l_int|1
suffix:semicolon
r_break
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
l_string|&quot;--index-info&quot;
)paren
)paren
(brace
id|allow_add
op_assign
id|allow_replace
op_assign
id|allow_remove
op_assign
l_int|1
suffix:semicolon
id|read_index_info
c_func
(paren
id|line_termination
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--verbose&quot;
)paren
)paren
(brace
id|verbose
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
id|update_one
c_func
(paren
id|path
comma
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_from_stdin
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|read_line
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.eof
)paren
r_break
suffix:semicolon
id|update_one
c_func
(paren
id|buf.buf
comma
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|active_cache_changed
)paren
(brace
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
id|commit_index_file
c_func
(paren
op_amp
id|cache_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new cachefile&quot;
)paren
suffix:semicolon
)brace
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
