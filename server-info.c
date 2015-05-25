macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
multiline_comment|/*&n; * Create the file &quot;path&quot; by writing to a temporary file and renaming&n; * it into place. The contents of the file come from &quot;generate&quot;, which&n; * should return non-zero if it encounters an error.&n; */
DECL|function|update_info_file
r_static
r_int
id|update_info_file
c_func
(paren
r_char
op_star
id|path
comma
r_int
(paren
op_star
id|generate
)paren
(paren
id|FILE
op_star
)paren
)paren
(brace
r_char
op_star
id|tmp
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s_XXXXXX&quot;
comma
id|path
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_int
id|fd
op_assign
l_int|1
suffix:semicolon
id|FILE
op_star
id|fp
op_assign
l_int|NULL
suffix:semicolon
id|safe_create_leading_directories
c_func
(paren
id|path
)paren
suffix:semicolon
id|fd
op_assign
id|git_mkstemp_mode
c_func
(paren
id|tmp
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
r_goto
id|out
suffix:semicolon
id|fp
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
id|fp
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|generate
c_func
(paren
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|fclose
c_func
(paren
id|fp
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|adjust_shared_perm
c_func
(paren
id|tmp
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|tmp
comma
id|path
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|error
c_func
(paren
l_string|&quot;unable to update %s: %s&quot;
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
r_if
c_cond
(paren
id|fp
)paren
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|add_info_ref
r_static
r_int
id|add_info_ref
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
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
id|FILE
op_star
id|fp
op_assign
id|cb_data
suffix:semicolon
r_struct
id|object
op_star
id|o
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&t;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|path
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|o
op_assign
id|deref_tag
c_func
(paren
id|o
comma
id|path
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o
)paren
r_if
c_cond
(paren
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s&t;%s^{}&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
comma
id|path
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
DECL|function|generate_info_refs
r_static
r_int
id|generate_info_refs
c_func
(paren
id|FILE
op_star
id|fp
)paren
(brace
r_struct
id|each_ref_fn_sha1_adapter
id|wrapped_add_info_ref
op_assign
(brace
id|add_info_ref
comma
id|fp
)brace
suffix:semicolon
r_return
id|for_each_ref
c_func
(paren
id|each_ref_fn_adapter
comma
op_amp
id|wrapped_add_info_ref
)paren
suffix:semicolon
)brace
DECL|function|update_info_refs
r_static
r_int
id|update_info_refs
c_func
(paren
r_int
id|force
)paren
(brace
r_char
op_star
id|path
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;info/refs&quot;
)paren
suffix:semicolon
r_int
id|ret
op_assign
id|update_info_file
c_func
(paren
id|path
comma
id|generate_info_refs
)paren
suffix:semicolon
id|free
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* packs */
DECL|struct|pack_info
r_static
r_struct
id|pack_info
(brace
DECL|member|p
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
DECL|member|old_num
r_int
id|old_num
suffix:semicolon
DECL|member|new_num
r_int
id|new_num
suffix:semicolon
DECL|member|nr_alloc
r_int
id|nr_alloc
suffix:semicolon
DECL|member|nr_heads
r_int
id|nr_heads
suffix:semicolon
DECL|member|head
r_int
r_char
(paren
op_star
id|head
)paren
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|info
)brace
op_star
op_star
id|info
suffix:semicolon
DECL|variable|num_pack
r_static
r_int
id|num_pack
suffix:semicolon
DECL|variable|objdir
r_static
r_const
r_char
op_star
id|objdir
suffix:semicolon
DECL|variable|objdirlen
r_static
r_int
id|objdirlen
suffix:semicolon
DECL|function|find_pack_by_name
r_static
r_struct
id|pack_info
op_star
id|find_pack_by_name
c_func
(paren
r_const
r_char
op_star
id|name
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
id|num_pack
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|packed_git
op_star
id|p
op_assign
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|p
suffix:semicolon
multiline_comment|/* skip &quot;/pack/&quot; after &quot;.git/objects&quot; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p-&gt;pack_name
op_plus
id|objdirlen
op_plus
l_int|6
comma
id|name
)paren
)paren
r_return
id|info
(braket
id|i
)braket
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Returns non-zero when we detect that the info in the&n; * old file is useless.&n; */
DECL|function|parse_pack_def
r_static
r_int
id|parse_pack_def
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|old_cnt
)paren
(brace
r_struct
id|pack_info
op_star
id|i
op_assign
id|find_pack_by_name
c_func
(paren
id|line
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|i-&gt;old_num
op_assign
id|old_cnt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The file describes a pack that is no longer here */
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Returns non-zero when we detect that the info in the&n; * old file is useless.&n; */
DECL|function|read_pack_info_file
r_static
r_int
id|read_pack_info_file
c_func
(paren
r_const
r_char
op_star
id|infofile
)paren
(brace
id|FILE
op_star
id|fp
suffix:semicolon
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|old_cnt
op_assign
l_int|0
suffix:semicolon
id|fp
op_assign
id|fopen
c_func
(paren
id|infofile
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* nonexistent is not an error. */
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|fp
)paren
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
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
op_logical_neg
id|len
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|line
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;P&squot;
suffix:colon
multiline_comment|/* P name */
r_if
c_cond
(paren
id|parse_pack_def
c_func
(paren
id|line
comma
id|old_cnt
op_increment
)paren
)paren
r_goto
id|out_stale
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;D&squot;
suffix:colon
multiline_comment|/* we used to emit D but that was misguided. */
r_case
l_char|&squot;T&squot;
suffix:colon
multiline_comment|/* we used to emit T but nobody uses it. */
r_goto
id|out_stale
suffix:semicolon
r_default
suffix:colon
id|error
c_func
(paren
l_string|&quot;unrecognized: %s&quot;
comma
id|line
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_stale
suffix:colon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|compare_info
r_static
r_int
id|compare_info
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|pack_info
op_star
r_const
op_star
id|a
op_assign
id|a_
suffix:semicolon
r_struct
id|pack_info
op_star
r_const
op_star
id|b
op_assign
id|b_
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
(paren
op_star
id|a
)paren
op_member_access_from_pointer
id|old_num
op_logical_and
l_int|0
op_le
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|old_num
)paren
multiline_comment|/* Keep the order in the original */
r_return
(paren
op_star
id|a
)paren
op_member_access_from_pointer
id|old_num
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|old_num
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0
op_le
(paren
op_star
id|a
)paren
op_member_access_from_pointer
id|old_num
)paren
multiline_comment|/* Only A existed in the original so B is obviously newer */
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0
op_le
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|old_num
)paren
multiline_comment|/* The other way around. */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* then it does not matter but at least keep the comparison stable */
r_if
c_cond
(paren
(paren
op_star
id|a
)paren
op_member_access_from_pointer
id|p
op_eq
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
op_star
id|a
)paren
op_member_access_from_pointer
id|p
OL
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|p
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|init_pack_info
r_static
r_void
id|init_pack_info
c_func
(paren
r_const
r_char
op_star
id|infofile
comma
r_int
id|force
)paren
(brace
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
r_int
id|stale
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|objdir
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
id|objdirlen
op_assign
id|strlen
c_func
(paren
id|objdir
)paren
suffix:semicolon
id|prepare_packed_git
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|packed_git
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
multiline_comment|/* we ignore things on alternate path since they are&n;&t;&t; * not available to the pullers in general.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;pack_local
)paren
r_continue
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|num_pack
op_assign
id|i
suffix:semicolon
id|info
op_assign
id|xcalloc
c_func
(paren
id|num_pack
comma
r_sizeof
(paren
r_struct
id|pack_info
op_star
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
id|packed_git
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
id|p-&gt;pack_local
)paren
r_continue
suffix:semicolon
id|info
(braket
id|i
)braket
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|pack_info
)paren
)paren
suffix:semicolon
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|p
op_assign
id|p
suffix:semicolon
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|old_num
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|infofile
op_logical_and
op_logical_neg
id|force
)paren
id|stale
op_assign
id|read_pack_info_file
c_func
(paren
id|infofile
)paren
suffix:semicolon
r_else
id|stale
op_assign
l_int|1
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
id|num_pack
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|stale
)paren
(brace
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|old_num
op_assign
l_int|1
suffix:semicolon
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|nr_heads
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* renumber them */
id|qsort
c_func
(paren
id|info
comma
id|num_pack
comma
r_sizeof
(paren
id|info
(braket
l_int|0
)braket
)paren
comma
id|compare_info
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
id|num_pack
suffix:semicolon
id|i
op_increment
)paren
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|new_num
op_assign
id|i
suffix:semicolon
)brace
DECL|function|free_pack_info
r_static
r_void
id|free_pack_info
c_func
(paren
r_void
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
id|num_pack
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|info
(braket
id|i
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
DECL|function|write_pack_info_file
r_static
r_int
id|write_pack_info_file
c_func
(paren
id|FILE
op_star
id|fp
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
id|num_pack
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;P %s&bslash;n&quot;
comma
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|p-&gt;pack_name
op_plus
id|objdirlen
op_plus
l_int|6
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|fp
)paren
op_eq
id|EOF
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|update_info_packs
r_static
r_int
id|update_info_packs
c_func
(paren
r_int
id|force
)paren
(brace
r_char
op_star
id|infofile
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/info/packs&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|init_pack_info
c_func
(paren
id|infofile
comma
id|force
)paren
suffix:semicolon
id|ret
op_assign
id|update_info_file
c_func
(paren
id|infofile
comma
id|write_pack_info_file
)paren
suffix:semicolon
id|free_pack_info
c_func
(paren
)paren
suffix:semicolon
id|free
c_func
(paren
id|infofile
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* public */
DECL|function|update_server_info
r_int
id|update_server_info
c_func
(paren
r_int
id|force
)paren
(brace
multiline_comment|/* We would add more dumb-server support files later,&n;&t; * including index of available pack files and their&n;&t; * intended audiences.&n;&t; */
r_int
id|errs
op_assign
l_int|0
suffix:semicolon
id|errs
op_assign
id|errs
op_or
id|update_info_refs
c_func
(paren
id|force
)paren
suffix:semicolon
id|errs
op_assign
id|errs
op_or
id|update_info_packs
c_func
(paren
id|force
)paren
suffix:semicolon
multiline_comment|/* remove leftover rev-cache file if there is any */
id|unlink_or_warn
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;info/rev-cache&quot;
)paren
)paren
suffix:semicolon
r_return
id|errs
suffix:semicolon
)brace
eof
