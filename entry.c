macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;streaming.h&quot;
DECL|function|create_directories
r_static
r_void
id|create_directories
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|path_len
comma
r_const
r_struct
id|checkout
op_star
id|state
)paren
(brace
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|path_len
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
id|path_len
)paren
(brace
r_do
(brace
id|buf
(braket
id|len
)braket
op_assign
id|path
(braket
id|len
)braket
suffix:semicolon
id|len
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OL
id|path_len
op_logical_and
id|path
(braket
id|len
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|path_len
)paren
r_break
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * For &squot;checkout-index --prefix=&lt;dir&gt;&squot;, &lt;dir&gt; is&n;&t;&t; * allowed to be a symlink to an existing directory,&n;&t;&t; * and we set &squot;state-&gt;base_dir_len&squot; below, such that&n;&t;&t; * we test the path components of the prefix with the&n;&t;&t; * stat() function instead of the lstat() function.&n;&t;&t; */
r_if
c_cond
(paren
id|has_dirs_only_path
c_func
(paren
id|buf
comma
id|len
comma
id|state-&gt;base_dir_len
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* ok, it is already a directory. */
multiline_comment|/*&n;&t;&t; * If this mkdir() would fail, it could be that there&n;&t;&t; * is already a symlink or something else exists&n;&t;&t; * there, therefore we then try to unlink it and try&n;&t;&t; * one more time to create the directory.&n;&t;&t; */
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|buf
comma
l_int|0777
)paren
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EEXIST
op_logical_and
id|state-&gt;force
op_logical_and
op_logical_neg
id|unlink_or_warn
c_func
(paren
id|buf
)paren
op_logical_and
op_logical_neg
id|mkdir
c_func
(paren
id|buf
comma
l_int|0777
)paren
)paren
r_continue
suffix:semicolon
id|die_errno
c_func
(paren
l_string|&quot;cannot create directory at &squot;%s&squot;&quot;
comma
id|buf
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|remove_subtree
r_static
r_void
id|remove_subtree
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_char
id|pathbuf
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot opendir &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|pathbuf
comma
id|path
)paren
suffix:semicolon
id|name
op_assign
id|pathbuf
op_plus
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
op_star
id|name
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|is_dot_or_dotdot
c_func
(paren
id|de-&gt;d_name
)paren
)paren
r_continue
suffix:semicolon
id|strcpy
c_func
(paren
id|name
comma
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lstat
c_func
(paren
id|pathbuf
comma
op_amp
id|st
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot lstat &squot;%s&squot;&quot;
comma
id|pathbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
id|remove_subtree
c_func
(paren
id|pathbuf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|pathbuf
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot unlink &squot;%s&squot;&quot;
comma
id|pathbuf
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rmdir
c_func
(paren
id|path
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;cannot rmdir &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|create_file
r_static
r_int
id|create_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|mode
)paren
(brace
id|mode
op_assign
(paren
id|mode
op_amp
l_int|0100
)paren
ques
c_cond
l_int|0777
suffix:colon
l_int|0666
suffix:semicolon
r_return
id|open
c_func
(paren
id|path
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|read_blob_entry
r_static
r_void
op_star
id|read_blob_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_enum
id|object_type
id|type
suffix:semicolon
r_void
op_star
r_new
op_assign
id|read_sha1_file
c_func
(paren
id|ce-&gt;sha1
comma
op_amp
id|type
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|OBJ_BLOB
)paren
r_return
r_new
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|open_output_fd
r_static
r_int
id|open_output_fd
c_func
(paren
r_char
op_star
id|path
comma
r_struct
id|cache_entry
op_star
id|ce
comma
r_int
id|to_tempfile
)paren
(brace
r_int
id|symlink
op_assign
(paren
id|ce-&gt;ce_mode
op_amp
id|S_IFMT
)paren
op_ne
id|S_IFREG
suffix:semicolon
r_if
c_cond
(paren
id|to_tempfile
)paren
(brace
id|strcpy
c_func
(paren
id|path
comma
id|symlink
ques
c_cond
l_string|&quot;.merge_link_XXXXXX&quot;
suffix:colon
l_string|&quot;.merge_file_XXXXXX&quot;
)paren
suffix:semicolon
r_return
id|mkstemp
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|create_file
c_func
(paren
id|path
comma
op_logical_neg
id|symlink
ques
c_cond
id|ce-&gt;ce_mode
suffix:colon
l_int|0666
)paren
suffix:semicolon
)brace
)brace
DECL|function|fstat_output
r_static
r_int
id|fstat_output
c_func
(paren
r_int
id|fd
comma
r_const
r_struct
id|checkout
op_star
id|state
comma
r_struct
id|stat
op_star
id|st
)paren
(brace
multiline_comment|/* use fstat() only when path == ce-&gt;name */
r_if
c_cond
(paren
id|fstat_is_reliable
c_func
(paren
)paren
op_logical_and
id|state-&gt;refresh_cache
op_logical_and
op_logical_neg
id|state-&gt;base_dir_len
)paren
(brace
id|fstat
c_func
(paren
id|fd
comma
id|st
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|streaming_write_entry
r_static
r_int
id|streaming_write_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_char
op_star
id|path
comma
r_struct
id|stream_filter
op_star
id|filter
comma
r_const
r_struct
id|checkout
op_star
id|state
comma
r_int
id|to_tempfile
comma
r_int
op_star
id|fstat_done
comma
r_struct
id|stat
op_star
id|statbuf
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|open_output_fd
c_func
(paren
id|path
comma
id|ce
comma
id|to_tempfile
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
id|result
op_or_assign
id|stream_blob_to_fd
c_func
(paren
id|fd
comma
id|ce-&gt;sha1
comma
id|filter
comma
l_int|1
)paren
suffix:semicolon
op_star
id|fstat_done
op_assign
id|fstat_output
c_func
(paren
id|fd
comma
id|state
comma
id|statbuf
)paren
suffix:semicolon
id|result
op_or_assign
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|unlink
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|write_entry
r_static
r_int
id|write_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_char
op_star
id|path
comma
r_const
r_struct
id|checkout
op_star
id|state
comma
r_int
id|to_tempfile
)paren
(brace
r_int
r_int
id|ce_mode_s_ifmt
op_assign
id|ce-&gt;ce_mode
op_amp
id|S_IFMT
suffix:semicolon
r_int
id|fd
comma
id|ret
comma
id|fstat_done
op_assign
l_int|0
suffix:semicolon
r_char
op_star
r_new
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|wrote
comma
id|newsize
op_assign
l_int|0
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|ce_mode_s_ifmt
op_eq
id|S_IFREG
)paren
(brace
r_struct
id|stream_filter
op_star
id|filter
op_assign
id|get_stream_filter
c_func
(paren
id|ce-&gt;name
comma
id|ce-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filter
op_logical_and
op_logical_neg
id|streaming_write_entry
c_func
(paren
id|ce
comma
id|path
comma
id|filter
comma
id|state
comma
id|to_tempfile
comma
op_amp
id|fstat_done
comma
op_amp
id|st
)paren
)paren
r_goto
id|finish
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ce_mode_s_ifmt
)paren
(brace
r_case
id|S_IFREG
suffix:colon
r_case
id|S_IFLNK
suffix:colon
r_new
op_assign
id|read_blob_entry
c_func
(paren
id|ce
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to read sha1 file of %s (%s)&quot;
comma
id|path
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ce_mode_s_ifmt
op_eq
id|S_IFLNK
op_logical_and
id|has_symlinks
op_logical_and
op_logical_neg
id|to_tempfile
)paren
(brace
id|ret
op_assign
id|symlink
c_func
(paren
r_new
comma
id|path
)paren
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to create symlink %s (%s)&quot;
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
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Convert from git internal format to working tree format&n;&t;&t; */
r_if
c_cond
(paren
id|ce_mode_s_ifmt
op_eq
id|S_IFREG
op_logical_and
id|convert_to_working_tree
c_func
(paren
id|ce-&gt;name
comma
r_new
comma
id|size
comma
op_amp
id|buf
)paren
)paren
(brace
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_new
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
op_amp
id|newsize
)paren
suffix:semicolon
id|size
op_assign
id|newsize
suffix:semicolon
)brace
id|fd
op_assign
id|open_output_fd
c_func
(paren
id|path
comma
id|ce
comma
id|to_tempfile
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
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;unable to create file %s (%s)&quot;
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
id|wrote
op_assign
id|write_in_full
c_func
(paren
id|fd
comma
r_new
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|to_tempfile
)paren
id|fstat_done
op_assign
id|fstat_output
c_func
(paren
id|fd
comma
id|state
comma
op_amp
id|st
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wrote
op_ne
id|size
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to write file %s&quot;
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFGITLINK
suffix:colon
r_if
c_cond
(paren
id|to_tempfile
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot create temporary subproject %s&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|path
comma
l_int|0777
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;cannot create subproject directory %s&quot;
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|error
c_func
(paren
l_string|&quot;unknown file mode for %s in index&quot;
comma
id|path
)paren
suffix:semicolon
)brace
id|finish
suffix:colon
r_if
c_cond
(paren
id|state-&gt;refresh_cache
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fstat_done
)paren
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is like &squot;lstat()&squot;, except it refuses to follow symlinks&n; * in the path, after skipping &quot;skiplen&quot;.&n; */
DECL|function|check_path
r_static
r_int
id|check_path
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|len
comma
r_struct
id|stat
op_star
id|st
comma
r_int
id|skiplen
)paren
(brace
r_const
r_char
op_star
id|slash
op_assign
id|path
op_plus
id|len
suffix:semicolon
r_while
c_loop
(paren
id|path
OL
id|slash
op_logical_and
op_star
id|slash
op_ne
l_char|&squot;/&squot;
)paren
id|slash
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_dirs_only_path
c_func
(paren
id|path
comma
id|slash
id|path
comma
id|skiplen
)paren
)paren
(brace
id|errno
op_assign
id|ENOENT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|lstat
c_func
(paren
id|path
comma
id|st
)paren
suffix:semicolon
)brace
DECL|function|checkout_entry
r_int
id|checkout_entry
c_func
(paren
r_struct
id|cache_entry
op_star
id|ce
comma
r_const
r_struct
id|checkout
op_star
id|state
comma
r_char
op_star
id|topath
)paren
(brace
r_static
r_char
id|path
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|len
op_assign
id|state-&gt;base_dir_len
suffix:semicolon
r_if
c_cond
(paren
id|topath
)paren
r_return
id|write_entry
c_func
(paren
id|ce
comma
id|topath
comma
id|state
comma
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|state-&gt;base_dir
comma
id|len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path
op_plus
id|len
comma
id|ce-&gt;name
)paren
suffix:semicolon
id|len
op_add_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_path
c_func
(paren
id|path
comma
id|len
comma
op_amp
id|st
comma
id|state-&gt;base_dir_len
)paren
)paren
(brace
r_int
id|changed
op_assign
id|ce_match_stat
c_func
(paren
id|ce
comma
op_amp
id|st
comma
id|CE_MATCH_IGNORE_VALID
op_or
id|CE_MATCH_IGNORE_SKIP_WORKTREE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;force
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;quiet
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s already exists, no checkout&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We unlink the old file, to get the new one with the&n;&t;&t; * right permissions (including umask, which is nasty&n;&t;&t; * to emulate by hand - much easier to let the system&n;&t;&t; * just do the right thing)&n;&t;&t; */
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
multiline_comment|/* If it is a gitlink, leave it alone! */
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;force
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s is a directory&quot;
comma
id|path
)paren
suffix:semicolon
id|remove_subtree
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|path
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to unlink old &squot;%s&squot; (%s)&quot;
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
r_else
r_if
c_cond
(paren
id|state-&gt;not_new
)paren
r_return
l_int|0
suffix:semicolon
id|create_directories
c_func
(paren
id|path
comma
id|len
comma
id|state
)paren
suffix:semicolon
r_return
id|write_entry
c_func
(paren
id|ce
comma
id|path
comma
id|state
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
