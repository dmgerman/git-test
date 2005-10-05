macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &lt;sys/wait.h&gt;
DECL|variable|quiet
r_static
r_int
id|quiet
suffix:semicolon
DECL|variable|clone_pack_usage
r_static
r_const
r_char
id|clone_pack_usage
(braket
)braket
op_assign
l_string|&quot;git-clone-pack [-q] [--exec=&lt;git-upload-pack&gt;] [&lt;host&gt;:]&lt;directory&gt; [&lt;heads&gt;]*&quot;
suffix:semicolon
DECL|variable|exec
r_static
r_const
r_char
op_star
id|exec
op_assign
l_string|&quot;git-upload-pack&quot;
suffix:semicolon
DECL|function|clone_handshake
r_static
r_void
id|clone_handshake
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_while
c_loop
(paren
id|ref
)paren
(brace
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;want %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
)paren
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
suffix:semicolon
)brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t have nuttin&squot; */
id|packet_write
c_func
(paren
id|fd
(braket
l_int|1
)braket
comma
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_ack
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
id|sha1
)paren
)paren
id|error
c_func
(paren
l_string|&quot;Huh! git-clone-pack got positive ack for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|is_master
r_static
r_int
id|is_master
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/heads/master&quot;
)paren
suffix:semicolon
)brace
DECL|function|write_one_ref
r_static
r_void
id|write_one_ref
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_char
op_star
id|path
op_assign
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|ref-&gt;name
)paren
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_char
op_star
id|hex
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories
c_func
(paren
id|path
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to create leading directory for %s&quot;
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
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
l_string|&quot;unable to create ref %s&quot;
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|ref-&gt;old_sha1
)paren
suffix:semicolon
id|hex
(braket
l_int|40
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
id|hex
comma
l_int|41
)paren
op_ne
l_int|41
)paren
id|die
c_func
(paren
l_string|&quot;unable to write ref %s&quot;
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|write_refs
r_static
r_void
id|write_refs
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_struct
id|ref
op_star
id|head
op_assign
l_int|NULL
comma
op_star
id|head_ptr
comma
op_star
id|master_ref
suffix:semicolon
r_char
op_star
id|head_path
suffix:semicolon
multiline_comment|/* Upload-pack must report HEAD first */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;HEAD&quot;
)paren
)paren
(brace
id|head
op_assign
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
suffix:semicolon
)brace
id|head_ptr
op_assign
l_int|NULL
suffix:semicolon
id|master_ref
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|ref
)paren
(brace
r_if
c_cond
(paren
id|is_master
c_func
(paren
id|ref
)paren
)paren
id|master_ref
op_assign
id|ref
suffix:semicolon
r_if
c_cond
(paren
id|head
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ref-&gt;old_sha1
comma
id|head-&gt;old_sha1
comma
l_int|20
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;refs/heads/&quot;
comma
l_int|11
)paren
op_logical_and
(paren
op_logical_neg
id|head_ptr
op_logical_or
id|ref
op_eq
id|master_ref
)paren
)paren
id|head_ptr
op_assign
id|ref
suffix:semicolon
id|write_one_ref
c_func
(paren
id|ref
)paren
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;No HEAD in remote.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|head_path
op_assign
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;HEAD&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head_ptr
)paren
(brace
multiline_comment|/*&n;&t;&t; * If we had a master ref, and it wasn&squot;t HEAD, we need to undo the&n;&t;&t; * symlink, and write a standalone HEAD. Give a warning, because that&squot;s&n;&t;&t; * really really wrong.&n;&t;&t; */
r_if
c_cond
(paren
id|master_ref
)paren
(brace
id|error
c_func
(paren
l_string|&quot;HEAD doesn&squot;t point to any refs! Making standalone HEAD&quot;
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|head_path
)paren
suffix:semicolon
)brace
id|write_one_ref
c_func
(paren
id|head
)paren
suffix:semicolon
id|free
c_func
(paren
id|head_path
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We reset to the master branch if it&squot;s available */
r_if
c_cond
(paren
id|master_ref
)paren
r_return
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Setting HEAD to %s&bslash;n&quot;
comma
id|head_ptr-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Uhhuh. Other end didn&squot;t have master. We start HEAD off with&n;&t; * the first branch with the same value.&n;&t; */
r_if
c_cond
(paren
id|create_symref
c_func
(paren
id|head_path
comma
id|head_ptr-&gt;name
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to link HEAD to %s&quot;
comma
id|head_ptr-&gt;name
)paren
suffix:semicolon
id|free
c_func
(paren
id|head_path
)paren
suffix:semicolon
)brace
DECL|function|clone_pack
r_static
r_int
id|clone_pack
c_func
(paren
r_int
id|fd
(braket
l_int|2
)braket
comma
r_int
id|nr_match
comma
r_char
op_star
op_star
id|match
)paren
(brace
r_struct
id|ref
op_star
id|refs
suffix:semicolon
r_int
id|status
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|get_remote_heads
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
op_amp
id|refs
comma
id|nr_match
comma
id|match
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|refs
)paren
(brace
id|packet_flush
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;no matching remote head&quot;
)paren
suffix:semicolon
)brace
id|clone_handshake
c_func
(paren
id|fd
comma
id|refs
)paren
suffix:semicolon
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
l_string|&quot;git-clone-pack: unable to fork off git-unpack-objects&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|dup2
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;git-unpack-objects&quot;
comma
l_string|&quot;git-unpack-objects&quot;
comma
id|quiet
ques
c_cond
l_string|&quot;-q&quot;
suffix:colon
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects exec failed&quot;
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_while
c_loop
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
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
id|die
c_func
(paren
l_string|&quot;waiting for git-unpack-objects: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
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
l_string|&quot;git-unpack-objects died with error code %d&quot;
comma
id|code
)paren
suffix:semicolon
id|write_refs
c_func
(paren
id|refs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
r_int
id|sig
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-unpack-objects died of signal %d&quot;
comma
id|sig
)paren
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;Sherlock Holmes! git-unpack-objects died of unnatural causes %d!&quot;
comma
id|status
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
id|ret
comma
id|nr_heads
suffix:semicolon
r_char
op_star
id|dest
op_assign
l_int|NULL
comma
op_star
op_star
id|heads
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
id|nr_heads
op_assign
l_int|0
suffix:semicolon
id|heads
op_assign
l_int|NULL
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
id|strcmp
c_func
(paren
l_string|&quot;-q&quot;
comma
id|arg
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
id|strncmp
c_func
(paren
l_string|&quot;--exec=&quot;
comma
id|arg
comma
l_int|7
)paren
)paren
(brace
id|exec
op_assign
id|arg
op_plus
l_int|7
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|clone_pack_usage
)paren
suffix:semicolon
)brace
id|dest
op_assign
id|arg
suffix:semicolon
id|heads
op_assign
id|argv
op_plus
id|i
op_plus
l_int|1
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
id|dest
)paren
id|usage
c_func
(paren
id|clone_pack_usage
)paren
suffix:semicolon
id|pid
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|dest
comma
id|exec
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
l_int|1
suffix:semicolon
id|ret
op_assign
id|clone_pack
c_func
(paren
id|fd
comma
id|nr_heads
comma
id|heads
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|finish_connect
c_func
(paren
id|pid
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
