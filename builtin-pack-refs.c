macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|result_path
DECL|variable|lock_path
r_static
r_const
r_char
op_star
id|result_path
comma
op_star
id|lock_path
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
id|lock_path
)paren
id|unlink
c_func
(paren
id|lock_path
)paren
suffix:semicolon
)brace
DECL|function|handle_one_ref
r_static
r_int
id|handle_one_ref
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flags
comma
r_void
op_star
id|cb_data
)paren
(brace
id|FILE
op_star
id|refs_file
op_assign
id|cb_data
suffix:semicolon
multiline_comment|/* Do not pack the symbolic refs */
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|REF_ISSYMREF
)paren
)paren
id|fprintf
c_func
(paren
id|refs_file
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_pack_refs
r_int
id|cmd_pack_refs
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
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|fd
suffix:semicolon
id|FILE
op_star
id|refs_file
suffix:semicolon
id|result_path
op_assign
id|xstrdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;packed-refs&quot;
)paren
)paren
suffix:semicolon
id|lock_path
op_assign
id|xstrdup
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s.lock&quot;
comma
id|result_path
)paren
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|lock_path
comma
id|O_CREAT
op_or
id|O_EXCL
op_or
id|O_WRONLY
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to create new ref-pack file (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_lock_file
)paren
suffix:semicolon
id|refs_file
op_assign
id|fdopen
c_func
(paren
id|fd
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refs_file
)paren
id|die
c_func
(paren
l_string|&quot;unable to create ref-pack file structure (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|handle_one_ref
comma
id|refs_file
)paren
suffix:semicolon
id|fsync
c_func
(paren
id|fd
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|refs_file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|lock_path
comma
id|result_path
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to overwrite old ref-pack file (%s)&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|lock_path
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
