multiline_comment|/*&n; * Builtin &quot;git count-objects&quot;.&n; *&n; * Copyright (c) 2006 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|function|count_objects
r_static
r_void
id|count_objects
c_func
(paren
id|DIR
op_star
id|d
comma
r_char
op_star
id|path
comma
r_int
id|len
comma
r_int
id|verbose
comma
r_int
r_int
op_star
id|loose
comma
r_int
r_int
op_star
id|loose_size
comma
r_int
r_int
op_star
id|packed_loose
comma
r_int
r_int
op_star
id|garbage
)paren
(brace
r_struct
id|dirent
op_star
id|ent
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ent
op_assign
id|readdir
c_func
(paren
id|d
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|cp
suffix:semicolon
r_int
id|bad
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ent-&gt;d_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|ent-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_int|0
op_logical_or
(paren
(paren
id|ent-&gt;d_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;.&squot;
)paren
op_logical_and
(paren
id|ent-&gt;d_name
(braket
l_int|2
)braket
op_eq
l_int|0
)paren
)paren
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|ent-&gt;d_name
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cp
op_increment
)paren
(brace
r_int
id|ch
op_assign
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
(paren
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;9&squot;
)paren
op_logical_or
(paren
l_char|&squot;a&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;f&squot;
)paren
)paren
r_continue
suffix:semicolon
id|bad
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cp
id|ent-&gt;d_name
op_ne
l_int|38
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_else
(brace
r_struct
id|stat
id|st
suffix:semicolon
id|memcpy
c_func
(paren
id|path
op_plus
id|len
op_plus
l_int|3
comma
id|ent-&gt;d_name
comma
l_int|38
)paren
suffix:semicolon
id|path
(braket
id|len
op_plus
l_int|2
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|path
(braket
id|len
op_plus
l_int|41
)braket
op_assign
l_int|0
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
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_else
(paren
op_star
id|loose_size
)paren
op_add_assign
id|xsize_t
c_func
(paren
id|on_disk_bytes
c_func
(paren
id|st
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bad
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|error
c_func
(paren
l_string|&quot;garbage found: %.*s/%s&quot;
comma
id|len
op_plus
l_int|2
comma
id|path
comma
id|ent-&gt;d_name
)paren
suffix:semicolon
(paren
op_star
id|garbage
)paren
op_increment
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
(paren
op_star
id|loose
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|hex
comma
id|path
op_plus
id|len
comma
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hex
op_plus
l_int|2
comma
id|ent-&gt;d_name
comma
l_int|38
)paren
suffix:semicolon
id|hex
(braket
l_int|40
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;internal error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_sha1_pack
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
)paren
(paren
op_star
id|packed_loose
)paren
op_increment
suffix:semicolon
)brace
)brace
DECL|variable|count_objects_usage
r_static
r_char
r_const
op_star
r_const
id|count_objects_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git count-objects [-v]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_count_objects
r_int
id|cmd_count_objects
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
id|i
comma
id|verbose
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|objdir
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|objdir
)paren
suffix:semicolon
r_char
op_star
id|path
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|50
)paren
suffix:semicolon
r_int
r_int
id|loose
op_assign
l_int|0
comma
id|packed
op_assign
l_int|0
comma
id|packed_loose
op_assign
l_int|0
comma
id|garbage
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|loose_size
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|opts
(braket
)braket
op_assign
(brace
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|opts
comma
id|count_objects_usage
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* we do not take arguments other than flags for now */
r_if
c_cond
(paren
id|argc
)paren
id|usage_with_options
c_func
(paren
id|count_objects_usage
comma
id|opts
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|objdir
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|objdir
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|path
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DIR
op_star
id|d
suffix:semicolon
id|sprintf
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;%02x&quot;
comma
id|i
)paren
suffix:semicolon
id|d
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_continue
suffix:semicolon
id|count_objects
c_func
(paren
id|d
comma
id|path
comma
id|len
comma
id|verbose
comma
op_amp
id|loose
comma
op_amp
id|loose_size
comma
op_amp
id|packed_loose
comma
op_amp
id|garbage
)paren
suffix:semicolon
id|closedir
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
r_int
r_int
id|num_pack
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|size_pack
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packed_git
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;pack_local
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|open_pack_index
c_func
(paren
id|p
)paren
)paren
r_continue
suffix:semicolon
id|packed
op_add_assign
id|p-&gt;num_objects
suffix:semicolon
id|size_pack
op_add_assign
id|p-&gt;pack_size
op_plus
id|p-&gt;index_size
suffix:semicolon
id|num_pack
op_increment
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;count: %lu&bslash;n&quot;
comma
id|loose
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;size: %lu&bslash;n&quot;
comma
id|loose_size
op_div
l_int|1024
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;in-pack: %lu&bslash;n&quot;
comma
id|packed
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;packs: %lu&bslash;n&quot;
comma
id|num_pack
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;size-pack: %lu&bslash;n&quot;
comma
id|size_pack
op_div
l_int|1024
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;prune-packable: %lu&bslash;n&quot;
comma
id|packed_loose
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;garbage: %lu&bslash;n&quot;
comma
id|garbage
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;%lu objects, %lu kilobytes&bslash;n&quot;
comma
id|loose
comma
id|loose_size
op_div
l_int|1024
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
