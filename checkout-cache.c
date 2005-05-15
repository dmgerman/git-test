multiline_comment|/*&n; * Check-out files from the &quot;current cache directory&quot;&n; *&n; * Copyright (C) 2005 Linus Torvalds&n; *&n; * Careful: order of argument flags does matter. For example,&n; *&n; *&t;checkout-cache -a -f file.c&n; *&n; * Will first check out all files listed in the cache (but not&n; * overwrite any old ones), and then force-checkout &quot;file.c&quot; a&n; * second time (ie that one _will_ overwrite any old contents&n; * with the same filename).&n; *&n; * Also, just doing &quot;checkout-cache&quot; does nothing. You probably&n; * meant &quot;checkout-cache -a&quot;. And if you want to force it, you&n; * want &quot;checkout-cache -f -a&quot;.&n; *&n; * Intuitiveness is not the goal here. Repeatability is. The&n; * reason for the &quot;no arguments means no work&quot; thing is that&n; * from scripts you are supposed to be able to do things like&n; *&n; *&t;find . -name &squot;*.h&squot; -print0 | xargs -0 checkout-cache -f --&n; *&n; * which will force all existing *.h files to be replaced with&n; * their cached copies. If an empty command line implied &quot;all&quot;,&n; * then this would force-refresh everything in the cache, which&n; * was not the point.&n; *&n; * Oh, and the &quot;--&quot; is just a good idea when you know the rest&n; * will be filenames. Just so that you wouldn&squot;t have a filename&n; * of &quot;-a&quot; causing problems (not possible in the above example,&n; * but get used to it in scripting!).&n; */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &quot;cache.h&quot;
DECL|variable|force
DECL|variable|quiet
DECL|variable|not_new
DECL|variable|refresh_cache
r_static
r_int
id|force
op_assign
l_int|0
comma
id|quiet
op_assign
l_int|0
comma
id|not_new
op_assign
l_int|0
comma
id|refresh_cache
op_assign
l_int|0
suffix:semicolon
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
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_const
r_char
op_star
id|slash
op_assign
id|path
suffix:semicolon
r_while
c_loop
(paren
(paren
id|slash
op_assign
id|strchr
c_func
(paren
id|slash
op_plus
l_int|1
comma
l_char|&squot;/&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|len
op_assign
id|slash
id|path
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|buf
comma
l_int|0755
)paren
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EEXIST
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|buf
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* ok */
r_if
c_cond
(paren
id|force
op_logical_and
op_logical_neg
id|unlink
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
l_int|0755
)paren
)paren
r_continue
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;cannot create directory at %s&quot;
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
id|die
c_func
(paren
l_string|&quot;cannot opendir %s&quot;
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
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
id|de-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
id|de-&gt;d_name
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
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
id|die
c_func
(paren
l_string|&quot;cannot lstat %s&quot;
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
id|die
c_func
(paren
l_string|&quot;cannot unlink %s&quot;
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
id|die
c_func
(paren
l_string|&quot;cannot rmdir %s&quot;
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
r_int
id|fd
suffix:semicolon
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
id|create_directories
c_func
(paren
id|path
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_WRONLY
op_or
id|O_TRUNC
op_or
id|O_CREAT
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
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EISDIR
op_logical_and
id|force
)paren
(brace
id|remove_subtree
c_func
(paren
id|path
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
comma
id|O_WRONLY
op_or
id|O_TRUNC
op_or
id|O_CREAT
comma
id|mode
)paren
suffix:semicolon
)brace
)brace
r_return
id|fd
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
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|fd
suffix:semicolon
r_void
op_star
r_new
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|wrote
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|target
(braket
l_int|1024
)braket
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
r_if
c_cond
(paren
op_logical_neg
r_new
op_logical_or
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;blob&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
r_new
)paren
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
l_string|&quot;checkout-cache: unable to read sha1 file of %s (%s)&quot;
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
)brace
r_switch
c_cond
(paren
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFREG
suffix:colon
id|fd
op_assign
id|create_file
c_func
(paren
id|path
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
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
l_string|&quot;checkout-cache: unable to create file %s (%s)&quot;
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
id|write
c_func
(paren
id|fd
comma
r_new
comma
id|size
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
l_string|&quot;checkout-cache: unable to write file %s&quot;
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|memcpy
c_func
(paren
id|target
comma
r_new
comma
id|size
)paren
suffix:semicolon
id|target
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|create_directories
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symlink
c_func
(paren
id|target
comma
id|path
)paren
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
l_string|&quot;checkout-cache: unable to create symlink %s (%s)&quot;
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
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
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
l_string|&quot;checkout-cache: unknown file mode for %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|refresh_cache
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
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
DECL|function|checkout_entry
r_static
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
r_char
op_star
id|base_dir
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_static
r_char
id|path
(braket
id|MAXPATHLEN
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|base_dir
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|base_dir
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
r_if
c_cond
(paren
op_logical_neg
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
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
id|force
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;checkout-cache: %s already exists&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We unlink the old file, to get the new one with the&n;&t;&t; * right permissions (including umask, which is nasty&n;&t;&t; * to emulate by hand - much easier to let the system&n;&t;&t; * just do the right thing)&n;&t;&t; */
id|unlink
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
id|not_new
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|write_entry
c_func
(paren
id|ce
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|checkout_file
r_static
r_int
id|checkout_file
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|base_dir
)paren
(brace
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
(brace
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;checkout-cache: %s is %s.&bslash;n&quot;
comma
id|name
comma
(paren
id|pos
OL
id|active_nr
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|name
)paren
)paren
ques
c_cond
l_string|&quot;unmerged&quot;
suffix:colon
l_string|&quot;not in the cache&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|checkout_entry
c_func
(paren
id|active_cache
(braket
id|pos
)braket
comma
id|base_dir
)paren
suffix:semicolon
)brace
DECL|function|checkout_all
r_static
r_int
id|checkout_all
c_func
(paren
r_const
r_char
op_star
id|base_dir
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
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|checkout_entry
c_func
(paren
id|ce
comma
id|base_dir
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
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
id|force_filename
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|base_dir
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_struct
id|cache_file
id|cache_file
suffix:semicolon
r_int
id|newfd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|die
c_func
(paren
l_string|&quot;invalid cache&quot;
)paren
suffix:semicolon
)brace
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
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|force_filename
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-a&quot;
)paren
)paren
(brace
id|checkout_all
c_func
(paren
id|base_dir
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
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|force_filename
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
id|arg
comma
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|force
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
id|arg
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
id|arg
comma
l_string|&quot;-n&quot;
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
id|arg
comma
l_string|&quot;-u&quot;
)paren
)paren
(brace
id|refresh_cache
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|newfd
OL
l_int|0
)paren
id|newfd
op_assign
id|hold_index_file_for_update
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
l_string|&quot;cannot open index.lock file.&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|arg
comma
l_string|&quot;--prefix=&quot;
comma
l_int|9
)paren
)paren
(brace
id|base_dir
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|base_dir
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* when --prefix is specified we do not&n;&t;&t;&t; * want to update cache.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|refresh_cache
)paren
(brace
id|close
c_func
(paren
id|newfd
)paren
suffix:semicolon
id|newfd
op_assign
l_int|1
suffix:semicolon
id|rollback_index_file
c_func
(paren
op_amp
id|cache_file
)paren
suffix:semicolon
)brace
id|refresh_cache
op_assign
l_int|0
suffix:semicolon
)brace
id|checkout_file
c_func
(paren
id|arg
comma
id|base_dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|newfd
op_logical_and
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
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new cachefile&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
