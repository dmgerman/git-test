macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;blob.h&quot;
DECL|function|find_short_object_filename
r_static
r_int
id|find_short_object_filename
c_func
(paren
r_int
id|len
comma
r_const
r_char
op_star
id|name
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|alternate_object_database
op_star
id|alt
suffix:semicolon
r_char
id|hex
(braket
l_int|40
)braket
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_static
r_struct
id|alternate_object_database
op_star
id|fakeent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fakeent
)paren
(brace
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
id|objdir_len
op_assign
id|strlen
c_func
(paren
id|objdir
)paren
suffix:semicolon
r_int
id|entlen
op_assign
id|objdir_len
op_plus
l_int|43
suffix:semicolon
id|fakeent
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fakeent
)paren
op_plus
id|entlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fakeent-&gt;base
comma
id|objdir
comma
id|objdir_len
)paren
suffix:semicolon
id|fakeent-&gt;name
op_assign
id|fakeent-&gt;base
op_plus
id|objdir_len
op_plus
l_int|1
suffix:semicolon
id|fakeent-&gt;name
(braket
l_int|1
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
id|fakeent-&gt;next
op_assign
id|alt_odb_list
suffix:semicolon
id|sprintf
c_func
(paren
id|hex
comma
l_string|&quot;%.2s&quot;
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|alt
op_assign
id|fakeent
suffix:semicolon
id|alt
op_logical_and
id|found
OL
l_int|2
suffix:semicolon
id|alt
op_assign
id|alt-&gt;next
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
id|DIR
op_star
id|dir
suffix:semicolon
id|sprintf
c_func
(paren
id|alt-&gt;name
comma
l_string|&quot;%.2s/&quot;
comma
id|name
)paren
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|alt-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_continue
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
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
op_ne
l_int|38
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|de-&gt;d_name
comma
id|name
op_plus
l_int|2
comma
id|len
l_int|2
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|memcpy
c_func
(paren
id|hex
op_plus
l_int|2
comma
id|de-&gt;d_name
comma
l_int|38
)paren
suffix:semicolon
id|found
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|hex
op_plus
l_int|2
comma
id|de-&gt;d_name
comma
l_int|38
)paren
)paren
(brace
id|found
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|1
)paren
r_return
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
op_eq
l_int|0
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|function|match_sha
r_static
r_int
id|match_sha
c_func
(paren
r_int
id|len
comma
r_const
r_int
r_char
op_star
id|a
comma
r_const
r_int
r_char
op_star
id|b
)paren
(brace
r_do
(brace
r_if
c_cond
(paren
op_star
id|a
op_ne
op_star
id|b
)paren
r_return
l_int|0
suffix:semicolon
id|a
op_increment
suffix:semicolon
id|b
op_increment
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
r_if
c_cond
(paren
(paren
op_star
id|a
op_xor
op_star
id|b
)paren
op_amp
l_int|0xf0
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|find_short_packed_object
r_static
r_int
id|find_short_packed_object
c_func
(paren
r_int
id|len
comma
r_const
r_int
r_char
op_star
id|match
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
r_int
r_char
id|found_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|found
op_assign
l_int|0
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
op_logical_and
id|found
OL
l_int|2
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
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
id|first
op_assign
l_int|0
comma
id|last
op_assign
id|num
suffix:semicolon
r_while
c_loop
(paren
id|first
OL
id|last
)paren
(brace
r_int
id|mid
op_assign
(paren
id|first
op_plus
id|last
)paren
op_div
l_int|2
suffix:semicolon
r_int
r_char
id|now
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|mid
comma
id|now
)paren
suffix:semicolon
id|cmp
op_assign
id|memcmp
c_func
(paren
id|match
comma
id|now
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
(brace
id|first
op_assign
id|mid
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
(brace
id|first
op_assign
id|mid
op_plus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|last
op_assign
id|mid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|first
OL
id|num
)paren
(brace
r_int
r_char
id|now
(braket
l_int|20
)braket
comma
id|next
(braket
l_int|20
)braket
suffix:semicolon
id|nth_packed_object_sha1
c_func
(paren
id|p
comma
id|first
comma
id|now
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_sha
c_func
(paren
id|len
comma
id|match
comma
id|now
)paren
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
id|first
op_plus
l_int|1
comma
id|next
)paren
op_logical_or
op_logical_neg
id|match_sha
c_func
(paren
id|len
comma
id|match
comma
id|next
)paren
)paren
(brace
multiline_comment|/* unique within this pack */
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|memcpy
c_func
(paren
id|found_sha1
comma
id|now
comma
l_int|20
)paren
suffix:semicolon
id|found
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|found_sha1
comma
id|now
comma
l_int|20
)paren
)paren
(brace
id|found
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* not even unique within this pack */
id|found
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|1
)paren
id|memcpy
c_func
(paren
id|sha1
comma
id|found_sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
id|found
suffix:semicolon
)brace
DECL|macro|SHORT_NAME_NOT_FOUND
mdefine_line|#define SHORT_NAME_NOT_FOUND (-1)
DECL|macro|SHORT_NAME_AMBIGUOUS
mdefine_line|#define SHORT_NAME_AMBIGUOUS (-2)
DECL|function|find_unique_short_object
r_static
r_int
id|find_unique_short_object
c_func
(paren
r_int
id|len
comma
r_char
op_star
id|canonical
comma
r_int
r_char
op_star
id|res
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|has_unpacked
comma
id|has_packed
suffix:semicolon
r_int
r_char
id|unpacked_sha1
(braket
l_int|20
)braket
comma
id|packed_sha1
(braket
l_int|20
)braket
suffix:semicolon
id|has_unpacked
op_assign
id|find_short_object_filename
c_func
(paren
id|len
comma
id|canonical
comma
id|unpacked_sha1
)paren
suffix:semicolon
id|has_packed
op_assign
id|find_short_packed_object
c_func
(paren
id|len
comma
id|res
comma
id|packed_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_unpacked
op_logical_and
op_logical_neg
id|has_packed
)paren
r_return
id|SHORT_NAME_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|has_unpacked
op_logical_or
l_int|1
OL
id|has_packed
)paren
r_return
id|SHORT_NAME_AMBIGUOUS
suffix:semicolon
r_if
c_cond
(paren
id|has_unpacked
op_ne
id|has_packed
)paren
(brace
id|memcpy
c_func
(paren
id|sha1
comma
(paren
id|has_packed
ques
c_cond
id|packed_sha1
suffix:colon
id|unpacked_sha1
)paren
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Both have unique ones -- do they match? */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|packed_sha1
comma
id|unpacked_sha1
comma
l_int|20
)paren
)paren
r_return
id|SHORT_NAME_AMBIGUOUS
suffix:semicolon
id|memcpy
c_func
(paren
id|sha1
comma
id|packed_sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_short_sha1
r_static
r_int
id|get_short_sha1
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|sha1
comma
r_int
id|quietly
)paren
(brace
r_int
id|i
comma
id|status
suffix:semicolon
r_char
id|canonical
(braket
l_int|40
)braket
suffix:semicolon
r_int
r_char
id|res
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|MINIMUM_ABBREV
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|memset
c_func
(paren
id|canonical
comma
l_char|&squot;x&squot;
comma
l_int|40
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|c
op_assign
id|name
(braket
id|i
)braket
suffix:semicolon
r_int
r_char
id|val
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
id|val
op_assign
id|c
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;f&squot;
)paren
id|val
op_assign
id|c
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;F&squot;
)paren
(brace
id|val
op_assign
id|c
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
id|c
op_sub_assign
l_char|&squot;A&squot;
l_char|&squot;a&squot;
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
id|canonical
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_amp
l_int|1
)paren
)paren
id|val
op_lshift_assign
l_int|4
suffix:semicolon
id|res
(braket
id|i
op_rshift
l_int|1
)braket
op_or_assign
id|val
suffix:semicolon
)brace
id|status
op_assign
id|find_unique_short_object
c_func
(paren
id|i
comma
id|canonical
comma
id|res
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quietly
op_logical_and
(paren
id|status
op_eq
id|SHORT_NAME_AMBIGUOUS
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;short SHA1 %.*s is ambiguous.&quot;
comma
id|len
comma
id|canonical
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|find_unique_abbrev
r_const
r_char
op_star
id|find_unique_abbrev
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|len
)paren
(brace
r_int
id|status
suffix:semicolon
r_static
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|40
)paren
r_return
id|hex
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
l_int|40
)paren
(brace
r_int
r_char
id|sha1_ret
(braket
l_int|20
)braket
suffix:semicolon
id|status
op_assign
id|get_short_sha1
c_func
(paren
id|hex
comma
id|len
comma
id|sha1_ret
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
(brace
id|hex
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|hex
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ne
id|SHORT_NAME_AMBIGUOUS
)paren
r_return
l_int|NULL
suffix:semicolon
id|len
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ambiguous_path
r_static
r_int
id|ambiguous_path
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
id|len
)paren
(brace
r_int
id|slash
op_assign
l_int|1
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|len
suffix:semicolon
id|cnt
op_increment
)paren
(brace
r_switch
c_cond
(paren
op_star
id|path
op_increment
)paren
(brace
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
r_break
suffix:semicolon
r_case
l_char|&squot;/&squot;
suffix:colon
r_if
c_cond
(paren
id|slash
)paren
r_break
suffix:semicolon
id|slash
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
r_case
l_char|&squot;.&squot;
suffix:colon
r_continue
suffix:semicolon
r_default
suffix:colon
id|slash
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|slash
suffix:semicolon
)brace
DECL|function|get_sha1_basic
r_static
r_int
id|get_sha1_basic
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
id|len
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_const
r_char
op_star
id|prefix
(braket
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;refs&quot;
comma
l_string|&quot;refs/tags&quot;
comma
l_string|&quot;refs/heads&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|40
op_logical_and
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|str
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Accept only unambiguous ref paths. */
r_if
c_cond
(paren
id|ambiguous_path
c_func
(paren
id|str
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|prefix
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
r_char
op_star
id|pathname
op_assign
id|git_path
c_func
(paren
l_string|&quot;%s/%.*s&quot;
comma
op_star
id|p
comma
id|len
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|read_ref
c_func
(paren
id|pathname
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
id|get_sha1_1
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|sha1
)paren
suffix:semicolon
DECL|function|get_parent
r_static
r_int
id|get_parent
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|result
comma
r_int
id|idx
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
id|ret
op_assign
id|get_sha1_1
c_func
(paren
id|name
comma
id|len
comma
id|sha1
)paren
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idx
)paren
(brace
id|memcpy
c_func
(paren
id|result
comma
id|commit-&gt;object.sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|idx
)paren
(brace
id|memcpy
c_func
(paren
id|result
comma
id|p-&gt;item-&gt;object.sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_nth_ancestor
r_static
r_int
id|get_nth_ancestor
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|result
comma
r_int
id|generation
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
id|ret
op_assign
id|get_sha1_1
c_func
(paren
id|name
comma
id|len
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_while
c_loop
(paren
id|generation
op_decrement
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
op_logical_or
id|parse_commit
c_func
(paren
id|commit
)paren
op_logical_or
op_logical_neg
id|commit-&gt;parents
)paren
r_return
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|sha1
comma
id|commit-&gt;parents-&gt;item-&gt;object.sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|result
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
DECL|function|peel_onion
r_static
r_int
id|peel_onion
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_char
id|outer
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|sp
suffix:semicolon
r_const
r_char
op_star
id|type_string
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|object
op_star
id|o
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;ref^{type}&quot; dereferences ref repeatedly until you cannot&n;&t; * dereference anymore, or you get an object of given type,&n;&t; * whichever comes first.  &quot;ref^{}&quot; means just dereference&n;&t; * tags until you get a non-tag.  &quot;ref^0&quot; is a shorthand for&n;&t; * &quot;ref^{commit}&quot;.  &quot;commit^{tree}&quot; could be used to find the&n;&t; * top-level tree of the given commit.&n;&t; */
r_if
c_cond
(paren
id|len
OL
l_int|4
op_logical_or
id|name
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;}&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|sp
op_assign
id|name
op_plus
id|len
l_int|1
suffix:semicolon
id|name
op_le
id|sp
suffix:semicolon
id|sp
op_decrement
)paren
(brace
r_int
id|ch
op_assign
op_star
id|sp
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;{&squot;
op_logical_and
id|name
OL
id|sp
op_logical_and
id|sp
(braket
l_int|1
)braket
op_eq
l_char|&squot;^&squot;
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sp
op_le
id|name
)paren
r_return
l_int|1
suffix:semicolon
id|sp
op_increment
suffix:semicolon
multiline_comment|/* beginning of type name, or closing brace for empty */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commit_type
comma
id|sp
comma
l_int|6
)paren
op_logical_and
id|sp
(braket
l_int|6
)braket
op_eq
l_char|&squot;}&squot;
)paren
id|type_string
op_assign
id|commit_type
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|tree_type
comma
id|sp
comma
l_int|4
)paren
op_logical_and
id|sp
(braket
l_int|4
)braket
op_eq
l_char|&squot;}&squot;
)paren
id|type_string
op_assign
id|tree_type
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|blob_type
comma
id|sp
comma
l_int|4
)paren
op_logical_and
id|sp
(braket
l_int|4
)braket
op_eq
l_char|&squot;}&squot;
)paren
id|type_string
op_assign
id|blob_type
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sp
(braket
l_int|0
)braket
op_eq
l_char|&squot;}&squot;
)paren
id|type_string
op_assign
l_int|NULL
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_1
c_func
(paren
id|name
comma
id|sp
id|name
l_int|2
comma
id|outer
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|o
op_assign
id|parse_object
c_func
(paren
id|outer
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
op_logical_neg
id|type_string
)paren
(brace
id|o
op_assign
id|deref_tag
c_func
(paren
id|o
comma
id|name
comma
id|sp
id|name
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_or
(paren
op_logical_neg
id|o-&gt;parsed
op_logical_and
op_logical_neg
id|parse_object
c_func
(paren
id|o-&gt;sha1
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|sha1
comma
id|o-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* At this point, the syntax look correct, so&n;&t;&t; * if we do not get the needed object, we should&n;&t;&t; * barf.&n;&t;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_or
(paren
op_logical_neg
id|o-&gt;parsed
op_logical_and
op_logical_neg
id|parse_object
c_func
(paren
id|o-&gt;sha1
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|type_string
)paren
(brace
id|memcpy
c_func
(paren
id|sha1
comma
id|o-&gt;sha1
comma
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|tag_type
)paren
id|o
op_assign
(paren
(paren
r_struct
id|tag
op_star
)paren
id|o
)paren
op_member_access_from_pointer
id|tagged
suffix:semicolon
r_else
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|commit_type
)paren
id|o
op_assign
op_amp
(paren
(paren
(paren
r_struct
id|commit
op_star
)paren
id|o
)paren
op_member_access_from_pointer
id|tree-&gt;object
)paren
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;%.*s: expected %s type, but the object dereferences to %s type&quot;
comma
id|len
comma
id|name
comma
id|type_string
comma
id|o-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o-&gt;parsed
)paren
id|parse_object
c_func
(paren
id|o-&gt;sha1
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_sha1_1
r_static
r_int
id|get_sha1_1
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|ret
comma
id|has_suffix
suffix:semicolon
r_const
r_char
op_star
id|cp
suffix:semicolon
multiline_comment|/* &quot;name~3&quot; is &quot;name^^^&quot;,&n;&t; * &quot;name~&quot; and &quot;name~0&quot; are name -- not &quot;name^0&quot;!&n;&t; * &quot;name^&quot; is not &quot;name^0&quot;; it is &quot;name^1&quot;.&n;&t; */
id|has_suffix
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|name
op_plus
id|len
l_int|1
suffix:semicolon
id|name
op_le
id|cp
suffix:semicolon
id|cp
op_decrement
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
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;9&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;~&squot;
op_logical_or
id|ch
op_eq
l_char|&squot;^&squot;
)paren
id|has_suffix
op_assign
id|ch
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|has_suffix
)paren
(brace
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_int
id|len1
op_assign
id|cp
id|name
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|cp
OL
id|name
op_plus
id|len
)paren
id|num
op_assign
id|num
op_star
l_int|10
op_plus
op_star
id|cp
op_increment
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|has_suffix
op_eq
l_char|&squot;^&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|num
op_logical_and
id|len1
op_eq
id|len
l_int|1
)paren
id|num
op_assign
l_int|1
suffix:semicolon
r_return
id|get_parent
c_func
(paren
id|name
comma
id|len1
comma
id|sha1
comma
id|num
)paren
suffix:semicolon
)brace
multiline_comment|/* else if (has_suffix == &squot;~&squot;) -- goes without saying */
r_return
id|get_nth_ancestor
c_func
(paren
id|name
comma
id|len1
comma
id|sha1
comma
id|num
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|peel_onion
c_func
(paren
id|name
comma
id|len
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
l_int|0
suffix:semicolon
id|ret
op_assign
id|get_sha1_basic
c_func
(paren
id|name
comma
id|len
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|get_short_sha1
c_func
(paren
id|name
comma
id|len
comma
id|sha1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is like &quot;get_sha1_basic()&quot;, except it allows &quot;sha1 expressions&quot;,&n; * notably &quot;xyz^&quot; for &quot;parent of xyz&quot;&n; */
DECL|function|get_sha1
r_int
id|get_sha1
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
id|prepare_alt_odb
c_func
(paren
)paren
suffix:semicolon
r_return
id|get_sha1_1
c_func
(paren
id|name
comma
id|strlen
c_func
(paren
id|name
)paren
comma
id|sha1
)paren
suffix:semicolon
)brace
eof
