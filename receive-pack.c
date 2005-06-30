macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|receive_pack_usage
r_static
r_const
r_char
id|receive_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-receive-pack [--unpack=executable] &lt;git-dir&gt; [heads]&quot;
suffix:semicolon
DECL|variable|unpacker
r_static
r_const
r_char
op_star
id|unpacker
op_assign
l_string|&quot;git-unpack-objects&quot;
suffix:semicolon
DECL|function|path_match
r_static
r_int
id|path_match
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|nr
comma
r_char
op_star
op_star
id|match
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|pathlen
op_assign
id|strlen
c_func
(paren
id|path
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|s
op_assign
id|match
(braket
id|i
)braket
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
id|len
OG
id|pathlen
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|path
op_plus
id|pathlen
id|len
comma
id|s
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pathlen
OG
id|len
op_logical_and
id|path
(braket
id|pathlen
id|len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
op_star
id|s
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_ref
r_static
r_void
id|show_ref
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
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
)brace
DECL|function|read_ref
r_static
r_int
id|read_ref
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_int
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
op_ge
l_int|0
)paren
(brace
r_char
id|buffer
(braket
l_int|60
)braket
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
op_ge
l_int|40
)paren
id|ret
op_assign
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|write_head_info
r_static
r_void
id|write_head_info
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_int
id|nr
comma
r_char
op_star
op_star
id|match
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_int
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_char
op_star
id|path
op_assign
id|xmalloc
c_func
(paren
id|baselen
op_plus
l_int|257
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|base
comma
id|baselen
)paren
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
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
r_continue
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namelen
OG
l_int|255
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|path
op_plus
id|baselen
comma
id|de-&gt;d_name
comma
id|namelen
op_plus
l_int|1
)paren
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
r_continue
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
(brace
id|path
(braket
id|baselen
op_plus
id|namelen
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|path
(braket
id|baselen
op_plus
id|namelen
op_plus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|write_head_info
c_func
(paren
id|path
comma
id|nr
comma
id|match
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_ref
c_func
(paren
id|path
comma
id|sha1
)paren
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_logical_and
op_logical_neg
id|path_match
c_func
(paren
id|path
comma
id|nr
comma
id|match
)paren
)paren
r_continue
suffix:semicolon
id|show_ref
c_func
(paren
id|path
comma
id|sha1
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
)brace
DECL|struct|command
r_struct
id|command
(brace
DECL|member|next
r_struct
id|command
op_star
id|next
suffix:semicolon
DECL|member|old_sha1
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|new_sha1
r_int
r_char
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|ref_name
r_char
id|ref_name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|commands
r_struct
id|command
op_star
id|commands
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * This gets called after(if) we&squot;ve successfully&n; * unpacked the data payload.&n; */
DECL|function|execute_commands
r_static
r_void
id|execute_commands
c_func
(paren
r_void
)paren
(brace
r_struct
id|command
op_star
id|cmd
op_assign
id|commands
suffix:semicolon
r_while
c_loop
(paren
id|cmd
)paren
(brace
r_char
id|old_hex
(braket
l_int|60
)braket
comma
op_star
id|new_hex
suffix:semicolon
id|strcpy
c_func
(paren
id|old_hex
comma
id|sha1_to_hex
c_func
(paren
id|cmd-&gt;old_sha1
)paren
)paren
suffix:semicolon
id|new_hex
op_assign
id|sha1_to_hex
c_func
(paren
id|cmd-&gt;new_sha1
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: %s -&gt; %s&bslash;n&quot;
comma
id|cmd-&gt;ref_name
comma
id|old_hex
comma
id|new_hex
)paren
suffix:semicolon
id|cmd
op_assign
id|cmd-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|read_head_info
r_static
r_void
id|read_head_info
c_func
(paren
r_void
)paren
(brace
r_struct
id|command
op_star
op_star
id|p
op_assign
op_amp
id|commands
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
comma
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|command
op_star
id|cmd
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|83
op_logical_or
id|line
(braket
l_int|40
)braket
op_ne
l_char|&squot; &squot;
op_logical_or
id|line
(braket
l_int|81
)braket
op_ne
l_char|&squot; &squot;
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
comma
id|old_sha1
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|41
comma
id|new_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: expected old/new/ref, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
id|cmd
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|command
)paren
op_plus
id|len
l_int|80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd-&gt;old_sha1
comma
id|old_sha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd-&gt;new_sha1
comma
id|new_sha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd-&gt;ref_name
comma
id|line
op_plus
l_int|82
comma
id|len
l_int|81
)paren
suffix:semicolon
id|cmd-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|p
op_assign
id|cmd
suffix:semicolon
id|p
op_assign
op_amp
id|cmd-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|unpack
r_static
r_void
id|unpack
c_func
(paren
r_void
)paren
(brace
id|pid_t
id|pid
op_assign
id|fork
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unpack fork failed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|setenv
c_func
(paren
l_string|&quot;GIT_DIR&quot;
comma
l_string|&quot;.&quot;
comma
l_int|1
)paren
suffix:semicolon
id|execlp
c_func
(paren
id|unpacker
comma
id|unpacker
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unpack execute failed&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|status
comma
id|code
suffix:semicolon
r_int
id|retval
op_assign
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
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EINTR
)paren
r_continue
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;waitpid failed (%s)&quot;
comma
id|strerror
c_func
(paren
id|retval
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ne
id|pid
)paren
id|die
c_func
(paren
l_string|&quot;waitpid is confused&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s died of signal %d&quot;
comma
id|unpacker
comma
id|WTERMSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s died out of really strange complications&quot;
comma
id|unpacker
)paren
suffix:semicolon
id|code
op_assign
id|WEXITSTATUS
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|code
)paren
id|die
c_func
(paren
l_string|&quot;%s exited with error code %d&quot;
comma
id|unpacker
comma
id|code
)paren
suffix:semicolon
r_return
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
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
comma
id|nr_heads
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|dir
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
op_star
id|heads
op_assign
l_int|NULL
suffix:semicolon
id|argv
op_increment
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
id|arg
op_assign
op_star
id|argv
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|arg
comma
l_string|&quot;--unpack=&quot;
comma
l_int|9
)paren
)paren
(brace
id|unpacker
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Do flag handling here */
id|usage
c_func
(paren
id|receive_pack_usage
)paren
suffix:semicolon
)brace
id|dir
op_assign
id|arg
suffix:semicolon
id|heads
op_assign
id|argv
suffix:semicolon
id|nr_heads
op_assign
id|argc
id|i
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
id|usage
c_func
(paren
id|receive_pack_usage
)paren
suffix:semicolon
multiline_comment|/* chdir to the directory. If that fails, try appending &quot;.git&quot; */
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|dir
)paren
OL
l_int|0
)paren
(brace
r_static
r_char
id|path
(braket
id|PATH_MAX
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
l_string|&quot;%s.git&quot;
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chdir
c_func
(paren
id|path
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to cd to %s&quot;
comma
id|dir
)paren
suffix:semicolon
)brace
multiline_comment|/* If we have a &quot;.git&quot; directory, chdir to it */
id|chdir
c_func
(paren
l_string|&quot;.git&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
l_string|&quot;objects&quot;
comma
id|X_OK
)paren
OL
l_int|0
op_logical_or
id|access
c_func
(paren
l_string|&quot;refs/heads&quot;
comma
id|X_OK
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s doesn&squot;t appear to be a git directory&quot;
comma
id|dir
)paren
suffix:semicolon
id|write_head_info
c_func
(paren
l_string|&quot;refs/&quot;
comma
id|nr_heads
comma
id|heads
)paren
suffix:semicolon
multiline_comment|/* EOF */
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|read_head_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commands
)paren
(brace
id|unpack
c_func
(paren
)paren
suffix:semicolon
id|execute_commands
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
