macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
DECL|variable|is_shallow
r_static
r_int
id|is_shallow
op_assign
l_int|1
suffix:semicolon
DECL|variable|shallow_stat
r_static
r_struct
id|stat
id|shallow_stat
suffix:semicolon
DECL|variable|alternate_shallow_file
r_static
r_char
op_star
id|alternate_shallow_file
suffix:semicolon
DECL|function|set_alternate_shallow_file
r_void
id|set_alternate_shallow_file
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_if
c_cond
(paren
id|is_shallow
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;BUG: is_repository_shallow must not be called before set_alternate_shallow_file&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|alternate_shallow_file
)paren
suffix:semicolon
id|alternate_shallow_file
op_assign
id|path
ques
c_cond
id|xstrdup
c_func
(paren
id|path
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|register_shallow
r_int
id|register_shallow
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|commit_graft
op_star
id|graft
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_graft
)paren
)paren
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|lookup_commit
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|graft-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|graft-&gt;nr_parent
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|commit
op_logical_and
id|commit-&gt;object.parsed
)paren
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
r_return
id|register_commit_graft
c_func
(paren
id|graft
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|is_repository_shallow
r_int
id|is_repository_shallow
c_func
(paren
r_void
)paren
(brace
id|FILE
op_star
id|fp
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_const
r_char
op_star
id|path
op_assign
id|alternate_shallow_file
suffix:semicolon
r_if
c_cond
(paren
id|is_shallow
op_ge
l_int|0
)paren
r_return
id|is_shallow
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|path
op_assign
id|git_path
c_func
(paren
l_string|&quot;shallow&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * fetch-pack sets &squot;--shallow-file &quot;&quot;&squot; as an indicator that no&n;&t; * shallow file should be used. We could just open it and it&n;&t; * will likely fail. But let&squot;s do an explicit check instead.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
op_star
id|path
op_logical_or
id|stat
c_func
(paren
id|path
comma
op_amp
id|shallow_stat
)paren
op_logical_or
(paren
id|fp
op_assign
id|fopen
c_func
(paren
id|path
comma
l_string|&quot;r&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|is_shallow
op_assign
l_int|0
suffix:semicolon
r_return
id|is_shallow
suffix:semicolon
)brace
id|is_shallow
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
id|fp
)paren
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buf
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;bad shallow line: %s&quot;
comma
id|buf
)paren
suffix:semicolon
id|register_shallow
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
id|is_shallow
suffix:semicolon
)brace
DECL|function|get_shallow_commits
r_struct
id|commit_list
op_star
id|get_shallow_commits
c_func
(paren
r_struct
id|object_array
op_star
id|heads
comma
r_int
id|depth
comma
r_int
id|shallow_flag
comma
r_int
id|not_shallow_flag
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|cur_depth
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|object_array
id|stack
op_assign
id|OBJECT_ARRAY_INIT
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|commit
op_logical_or
id|i
OL
id|heads-&gt;nr
op_logical_or
id|stack.nr
)paren
(brace
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
(brace
r_if
c_cond
(paren
id|i
OL
id|heads-&gt;nr
)paren
(brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|deref_tag
c_func
(paren
id|heads-&gt;objects
(braket
id|i
op_increment
)braket
dot
id|item
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
op_logical_or
id|commit-&gt;object.type
op_ne
id|OBJ_COMMIT
)paren
(brace
id|commit
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;util
)paren
id|commit-&gt;util
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|commit-&gt;util
op_assign
l_int|0
suffix:semicolon
id|cur_depth
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|stack.objects
(braket
op_decrement
id|stack.nr
)braket
dot
id|item
suffix:semicolon
id|cur_depth
op_assign
op_star
(paren
r_int
op_star
)paren
id|commit-&gt;util
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
id|die
c_func
(paren
l_string|&quot;invalid commit&quot;
)paren
suffix:semicolon
id|cur_depth
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cur_depth
op_ge
id|depth
)paren
(brace
id|commit_list_insert
c_func
(paren
id|commit
comma
op_amp
id|result
)paren
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|shallow_flag
suffix:semicolon
id|commit
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|commit-&gt;object.flags
op_or_assign
id|not_shallow_flag
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|commit-&gt;parents
comma
id|commit
op_assign
l_int|NULL
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;item-&gt;util
)paren
(brace
r_int
op_star
id|pointer
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|p-&gt;item-&gt;util
op_assign
id|pointer
suffix:semicolon
op_star
id|pointer
op_assign
id|cur_depth
suffix:semicolon
)brace
r_else
(brace
r_int
op_star
id|pointer
op_assign
id|p-&gt;item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|cur_depth
op_ge
op_star
id|pointer
)paren
r_continue
suffix:semicolon
op_star
id|pointer
op_assign
id|cur_depth
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;next
)paren
id|add_object_array
c_func
(paren
op_amp
id|p-&gt;item-&gt;object
comma
l_int|NULL
comma
op_amp
id|stack
)paren
suffix:semicolon
r_else
(brace
id|commit
op_assign
id|p-&gt;item
suffix:semicolon
id|cur_depth
op_assign
op_star
(paren
r_int
op_star
)paren
id|commit-&gt;util
suffix:semicolon
)brace
)brace
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|check_shallow_file_for_update
r_void
id|check_shallow_file_for_update
c_func
(paren
r_void
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
id|is_shallow
)paren
r_return
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_shallow
op_eq
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;BUG: shallow must be initialized by now&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;shallow&quot;
)paren
comma
op_amp
id|st
)paren
)paren
id|die
c_func
(paren
l_string|&quot;shallow file was removed during fetch&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|st.st_mtime
op_ne
id|shallow_stat.st_mtime
macro_line|#ifdef USE_NSEC
op_logical_or
id|ST_MTIME_NSEC
c_func
(paren
id|st
)paren
op_ne
id|ST_MTIME_NSEC
c_func
(paren
id|shallow_stat
)paren
macro_line|#endif
)paren
id|die
c_func
(paren
l_string|&quot;shallow file was changed during fetch&quot;
)paren
suffix:semicolon
)brace
DECL|struct|write_shallow_data
r_struct
id|write_shallow_data
(brace
DECL|member|out
r_struct
id|strbuf
op_star
id|out
suffix:semicolon
DECL|member|use_pack_protocol
r_int
id|use_pack_protocol
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|write_one_shallow
r_static
r_int
id|write_one_shallow
c_func
(paren
r_const
r_struct
id|commit_graft
op_star
id|graft
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|write_shallow_data
op_star
id|data
op_assign
id|cb_data
suffix:semicolon
r_const
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|graft-&gt;sha1
)paren
suffix:semicolon
id|data-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;use_pack_protocol
)paren
id|packet_buf_write
c_func
(paren
id|data-&gt;out
comma
l_string|&quot;shallow %s&quot;
comma
id|hex
)paren
suffix:semicolon
r_else
(brace
id|strbuf_addstr
c_func
(paren
id|data-&gt;out
comma
id|hex
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|data-&gt;out
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_shallow_commits
r_int
id|write_shallow_commits
c_func
(paren
r_struct
id|strbuf
op_star
id|out
comma
r_int
id|use_pack_protocol
)paren
(brace
r_struct
id|write_shallow_data
id|data
suffix:semicolon
id|data.out
op_assign
id|out
suffix:semicolon
id|data.use_pack_protocol
op_assign
id|use_pack_protocol
suffix:semicolon
id|data.count
op_assign
l_int|0
suffix:semicolon
id|for_each_commit_graft
c_func
(paren
id|write_one_shallow
comma
op_amp
id|data
)paren
suffix:semicolon
r_return
id|data.count
suffix:semicolon
)brace
DECL|function|setup_alternate_shallow
r_void
id|setup_alternate_shallow
c_func
(paren
r_struct
id|lock_file
op_star
id|shallow_lock
comma
r_const
r_char
op_star
op_star
id|alternate_shallow_file
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|check_shallow_file_for_update
c_func
(paren
)paren
suffix:semicolon
id|fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
id|shallow_lock
comma
id|git_path
c_func
(paren
l_string|&quot;shallow&quot;
)paren
comma
id|LOCK_DIE_ON_ERROR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_shallow_commits
c_func
(paren
op_amp
id|sb
comma
l_int|0
)paren
)paren
(brace
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|fd
comma
id|sb.buf
comma
id|sb.len
)paren
op_ne
id|sb.len
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to write to %s&quot;
comma
id|shallow_lock-&gt;filename
)paren
suffix:semicolon
op_star
id|alternate_shallow_file
op_assign
id|shallow_lock-&gt;filename
suffix:semicolon
)brace
r_else
multiline_comment|/*&n;&t;&t; * is_repository_shallow() sees empty string as &quot;no&n;&t;&t; * shallow file&quot;.&n;&t;&t; */
op_star
id|alternate_shallow_file
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
eof
