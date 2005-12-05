macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
multiline_comment|/* refs */
DECL|variable|info_ref_fp
r_static
id|FILE
op_star
id|info_ref_fp
suffix:semicolon
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
)paren
(brace
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
id|fprintf
c_func
(paren
id|info_ref_fp
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
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|tag_type
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
id|fprintf
c_func
(paren
id|info_ref_fp
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
suffix:semicolon
)brace
r_return
l_int|0
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
id|path0
op_assign
id|strdup
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;info/refs&quot;
)paren
)paren
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|path0
)paren
suffix:semicolon
r_char
op_star
id|path1
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|2
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path1
comma
id|path0
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|path1
op_plus
id|len
comma
l_string|&quot;+&quot;
)paren
suffix:semicolon
id|safe_create_leading_directories
c_func
(paren
id|path0
)paren
suffix:semicolon
id|info_ref_fp
op_assign
id|fopen
c_func
(paren
id|path1
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info_ref_fp
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unable to update %s&quot;
comma
id|path0
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|add_info_ref
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|info_ref_fp
)paren
suffix:semicolon
id|rename
c_func
(paren
id|path1
comma
id|path0
)paren
suffix:semicolon
id|free
c_func
(paren
id|path0
)paren
suffix:semicolon
id|free
c_func
(paren
id|path1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* packs */
DECL|struct|pack_info
r_static
r_struct
id|pack_info
(brace
DECL|member|latest
r_int
r_int
id|latest
suffix:semicolon
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
DECL|function|parse_object_cheap
r_static
r_struct
id|object
op_star
id|parse_object_cheap
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
id|object
op_star
id|o
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|commit_type
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|o
suffix:semicolon
id|free
c_func
(paren
id|commit-&gt;buffer
)paren
suffix:semicolon
id|commit-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|tree_type
)paren
(brace
r_struct
id|tree
op_star
id|tree
op_assign
(paren
r_struct
id|tree
op_star
)paren
id|o
suffix:semicolon
r_struct
id|tree_entry_list
op_star
id|e
comma
op_star
id|n
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
id|tree-&gt;entries
suffix:semicolon
id|e
suffix:semicolon
id|e
op_assign
id|n
)paren
(brace
id|free
c_func
(paren
id|e-&gt;name
)paren
suffix:semicolon
id|e-&gt;name
op_assign
l_int|NULL
suffix:semicolon
id|n
op_assign
id|e-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|e
)paren
suffix:semicolon
)brace
id|tree-&gt;entries
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|o
suffix:semicolon
)brace
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
DECL|function|find_pack_by_old_num
r_static
r_struct
id|pack_info
op_star
id|find_pack_by_old_num
c_func
(paren
r_int
id|old_num
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
r_if
c_cond
(paren
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|old_num
op_eq
id|old_num
)paren
r_return
id|info
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|add_head_def
r_static
r_int
id|add_head_def
c_func
(paren
r_struct
id|pack_info
op_star
id|this
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|this-&gt;nr_alloc
op_le
id|this-&gt;nr_heads
)paren
(brace
id|this-&gt;nr_alloc
op_assign
id|alloc_nr
c_func
(paren
id|this-&gt;nr_alloc
)paren
suffix:semicolon
id|this-&gt;head
op_assign
id|xrealloc
c_func
(paren
id|this-&gt;head
comma
id|this-&gt;nr_alloc
op_star
l_int|20
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|this-&gt;head
(braket
id|this-&gt;nr_heads
op_increment
)braket
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
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
multiline_comment|/* Returns non-zero when we detect that the info in the old file is useless.&n; */
DECL|function|parse_head_def
r_static
r_int
id|parse_head_def
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|num
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|ep
suffix:semicolon
r_struct
id|pack_info
op_star
id|this
suffix:semicolon
r_struct
id|object
op_star
id|o
suffix:semicolon
id|cp
op_assign
id|line
op_plus
l_int|2
suffix:semicolon
id|num
op_assign
id|strtoul
c_func
(paren
id|cp
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
op_eq
id|cp
op_logical_or
op_star
id|ep
op_increment
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;invalid input ix %s&quot;
comma
id|line
)paren
suffix:semicolon
id|this
op_assign
id|find_pack_by_old_num
c_func
(paren
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* You know the drill. */
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|ep
comma
id|sha1
)paren
op_logical_or
id|ep
(braket
l_int|40
)braket
op_ne
l_char|&squot; &squot;
)paren
r_return
id|error
c_func
(paren
l_string|&quot;invalid input sha1 %s (%s)&quot;
comma
id|line
comma
id|ep
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o
op_assign
id|parse_object_cheap
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|error
c_func
(paren
l_string|&quot;no such object: %s&quot;
comma
id|line
)paren
suffix:semicolon
r_return
id|add_head_def
c_func
(paren
id|this
comma
id|sha1
)paren
suffix:semicolon
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
multiline_comment|/* nonexisting is not an error. */
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
id|len
op_minus
l_int|1
)braket
op_assign
l_int|0
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
r_goto
id|out_stale
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;T&squot;
suffix:colon
multiline_comment|/* T ix sha1 type */
r_if
c_cond
(paren
id|parse_head_def
c_func
(paren
id|line
)paren
)paren
r_goto
id|out_stale
suffix:semicolon
r_break
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
multiline_comment|/* We sort the packs according to the date of the latest commit.  That&n; * in turn indicates how young the pack is, and in general we would&n; * want to depend on younger packs.&n; */
DECL|function|get_latest_commit_date
r_static
r_int
r_int
id|get_latest_commit_date
c_func
(paren
r_struct
id|packed_git
op_star
id|p
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|object
op_star
id|o
suffix:semicolon
r_int
id|num
op_assign
id|num_packed_objects
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|latest
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt pack file %s?&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o
op_assign
id|parse_object_cheap
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;cannot parse %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|commit_type
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|o
suffix:semicolon
r_if
c_cond
(paren
id|latest
OL
id|commit-&gt;date
)paren
id|latest
op_assign
id|commit-&gt;date
suffix:semicolon
)brace
)brace
r_return
id|latest
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
r_if
c_cond
(paren
(paren
op_star
id|a
)paren
op_member_access_from_pointer
id|latest
OL
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|latest
)paren
r_return
l_int|1
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
id|latest
op_eq
(paren
op_star
id|b
)paren
op_member_access_from_pointer
id|latest
)paren
r_return
l_int|0
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
id|strncmp
c_func
(paren
id|p-&gt;pack_name
comma
id|objdir
comma
id|objdirlen
)paren
op_logical_or
id|strncmp
c_func
(paren
id|p-&gt;pack_name
op_plus
id|objdirlen
comma
l_string|&quot;/pack/&quot;
comma
l_int|6
)paren
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
id|strncmp
c_func
(paren
id|p-&gt;pack_name
comma
id|objdir
comma
id|objdirlen
)paren
op_logical_or
id|p-&gt;pack_name
(braket
id|objdirlen
)braket
op_ne
l_char|&squot;/&squot;
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
r_if
c_cond
(paren
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|old_num
OL
l_int|0
)paren
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|latest
op_assign
id|get_latest_commit_date
c_func
(paren
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|p
)paren
suffix:semicolon
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
DECL|function|write_pack_info_file
r_static
r_void
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
comma
id|j
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
id|pack_info
op_star
id|this
op_assign
id|info
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|this-&gt;nr_heads
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|lookup_object
c_func
(paren
id|this-&gt;head
(braket
id|j
)braket
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;T %1d %s %s&bslash;n&quot;
comma
id|i
comma
id|sha1_to_hex
c_func
(paren
id|this-&gt;head
(braket
id|j
)braket
)paren
comma
id|o-&gt;type
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|macro|REFERENCED
mdefine_line|#define REFERENCED 01
DECL|macro|EMITTED
mdefine_line|#define EMITTED   04
DECL|function|show
r_static
r_void
id|show
c_func
(paren
r_struct
id|object
op_star
id|o
comma
r_int
id|pack_ix
)paren
(brace
multiline_comment|/*&n;&t; * We are interested in objects that are not referenced,&n;&t; */
r_if
c_cond
(paren
id|o-&gt;flags
op_amp
id|EMITTED
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|REFERENCED
)paren
)paren
id|add_head_def
c_func
(paren
id|info
(braket
id|pack_ix
)braket
comma
id|o-&gt;sha1
)paren
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|EMITTED
suffix:semicolon
)brace
DECL|function|find_pack_info_one
r_static
r_void
id|find_pack_info_one
c_func
(paren
r_int
id|pack_ix
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|object
op_star
id|o
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|packed_git
op_star
id|p
op_assign
id|info
(braket
id|pack_ix
)braket
op_member_access_from_pointer
id|p
suffix:semicolon
r_int
id|num
op_assign
id|num_packed_objects
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* Scan objects, clear flags from all the edge ones and&n;&t; * internal ones, possibly marked in the previous round.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt pack file %s?&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;cannot parse %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;refs
)paren
(brace
r_struct
id|object_refs
op_star
id|refs
op_assign
id|o-&gt;refs
suffix:semicolon
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|refs-&gt;count
suffix:semicolon
id|j
op_increment
)paren
id|refs-&gt;ref
(braket
id|j
)braket
op_member_access_from_pointer
id|flags
op_assign
l_int|0
suffix:semicolon
)brace
id|o-&gt;flags
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Mark all the referenced ones */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt pack file %s?&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;cannot find %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;refs
)paren
(brace
r_struct
id|object_refs
op_star
id|refs
op_assign
id|o-&gt;refs
suffix:semicolon
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|refs-&gt;count
suffix:semicolon
id|j
op_increment
)paren
id|refs-&gt;ref
(braket
id|j
)braket
op_member_access_from_pointer
id|flags
op_or_assign
id|REFERENCED
suffix:semicolon
)brace
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|i
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt pack file %s?&quot;
comma
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
)paren
op_eq
l_int|NULL
)paren
id|die
c_func
(paren
l_string|&quot;cannot find %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|show
c_func
(paren
id|o
comma
id|pack_ix
)paren
suffix:semicolon
)brace
)brace
DECL|function|find_pack_info
r_static
r_void
id|find_pack_info
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
(brace
multiline_comment|/* The packed objects are cast in stone, and a head&n;&t;&t; * in a pack will stay as head, so is the set of missing&n;&t;&t; * objects.  If the repo has been reorganized and we&n;&t;&t; * are missing some packs available back then, we have&n;&t;&t; * already discarded the info read from the file, so&n;&t;&t; * we will find (old_num &lt; 0) in that case.&n;&t;&t; */
r_if
c_cond
(paren
l_int|0
op_le
id|info
(braket
id|i
)braket
op_member_access_from_pointer
id|old_num
)paren
r_continue
suffix:semicolon
id|find_pack_info_one
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
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
id|infofile
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
id|name
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|namelen
suffix:semicolon
id|FILE
op_star
id|fp
suffix:semicolon
id|namelen
op_assign
id|sprintf
c_func
(paren
id|infofile
comma
l_string|&quot;%s/info/packs&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|name
comma
id|infofile
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|name
op_plus
id|namelen
comma
l_string|&quot;+&quot;
)paren
suffix:semicolon
id|init_pack_info
c_func
(paren
id|infofile
comma
id|force
)paren
suffix:semicolon
id|find_pack_info
c_func
(paren
)paren
suffix:semicolon
id|safe_create_leading_directories
c_func
(paren
id|name
)paren
suffix:semicolon
id|fp
op_assign
id|fopen
c_func
(paren
id|name
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
r_return
id|error
c_func
(paren
l_string|&quot;cannot open %s&quot;
comma
id|name
)paren
suffix:semicolon
id|write_pack_info_file
c_func
(paren
id|fp
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
id|rename
c_func
(paren
id|name
comma
id|infofile
)paren
suffix:semicolon
r_return
l_int|0
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
id|unlink
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
