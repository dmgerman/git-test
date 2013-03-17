multiline_comment|/*&n; * name-hash.c&n; *&n; * Hashing names in the index state&n; *&n; * Copyright (C) 2008 Linus Torvalds&n; */
DECL|macro|NO_THE_INDEX_COMPATIBILITY_MACROS
mdefine_line|#define NO_THE_INDEX_COMPATIBILITY_MACROS
macro_line|#include &quot;cache.h&quot;
multiline_comment|/*&n; * This removes bit 5 if bit 6 is set.&n; *&n; * That will make US-ASCII characters hash to their upper-case&n; * equivalent. We could easily do this one whole word at a time,&n; * but that&squot;s for future worries.&n; */
DECL|function|icase_hash
r_static
r_inline
r_int
r_char
id|icase_hash
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_return
id|c
op_amp
op_complement
(paren
(paren
id|c
op_amp
l_int|0x40
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|hash_name
r_static
r_int
r_int
id|hash_name
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
(brace
r_int
r_int
id|hash
op_assign
l_int|0x123
suffix:semicolon
r_do
(brace
r_int
r_char
id|c
op_assign
op_star
id|name
op_increment
suffix:semicolon
id|c
op_assign
id|icase_hash
c_func
(paren
id|c
)paren
suffix:semicolon
id|hash
op_assign
id|hash
op_star
l_int|101
op_plus
id|c
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|namelen
)paren
suffix:semicolon
r_return
id|hash
suffix:semicolon
)brace
DECL|function|hash_index_entry_directories
r_static
r_void
id|hash_index_entry_directories
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
multiline_comment|/*&n;&t; * Throw each directory component in the hash for quick lookup&n;&t; * during a git status. Directory components are stored with their&n;&t; * closing slash.  Despite submodules being a directory, they never&n;&t; * reach this point, because they are stored without a closing slash&n;&t; * in the cache.&n;&t; *&n;&t; * Note that the cache_entry stored with the directory does not&n;&t; * represent the directory itself.  It is a pointer to an existing&n;&t; * filename, and its only purpose is to represent existence of the&n;&t; * directory in the cache.  It is very possible multiple directory&n;&t; * hash entries may point to the same cache_entry.&n;&t; */
r_int
r_int
id|hash
suffix:semicolon
r_void
op_star
op_star
id|pos
suffix:semicolon
r_const
r_char
op_star
id|ptr
op_assign
id|ce-&gt;name
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ptr
)paren
(brace
r_while
c_loop
(paren
op_star
id|ptr
op_logical_and
op_star
id|ptr
op_ne
l_char|&squot;/&squot;
)paren
op_increment
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ptr
op_eq
l_char|&squot;/&squot;
)paren
(brace
op_increment
id|ptr
suffix:semicolon
id|hash
op_assign
id|hash_name
c_func
(paren
id|ce-&gt;name
comma
id|ptr
id|ce-&gt;name
)paren
suffix:semicolon
id|pos
op_assign
id|insert_hash
c_func
(paren
id|hash
comma
id|ce
comma
op_amp
id|istate-&gt;name_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
)paren
(brace
id|ce-&gt;dir_next
op_assign
op_star
id|pos
suffix:semicolon
op_star
id|pos
op_assign
id|ce
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|hash_index_entry
r_static
r_void
id|hash_index_entry
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_void
op_star
op_star
id|pos
suffix:semicolon
r_int
r_int
id|hash
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_HASHED
)paren
r_return
suffix:semicolon
id|ce-&gt;ce_flags
op_or_assign
id|CE_HASHED
suffix:semicolon
id|ce-&gt;next
op_assign
id|ce-&gt;dir_next
op_assign
l_int|NULL
suffix:semicolon
id|hash
op_assign
id|hash_name
c_func
(paren
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
)paren
suffix:semicolon
id|pos
op_assign
id|insert_hash
c_func
(paren
id|hash
comma
id|ce
comma
op_amp
id|istate-&gt;name_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
)paren
(brace
id|ce-&gt;next
op_assign
op_star
id|pos
suffix:semicolon
op_star
id|pos
op_assign
id|ce
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ignore_case
)paren
id|hash_index_entry_directories
c_func
(paren
id|istate
comma
id|ce
)paren
suffix:semicolon
)brace
DECL|function|lazy_init_name_hash
r_static
r_void
id|lazy_init_name_hash
c_func
(paren
r_struct
id|index_state
op_star
id|istate
)paren
(brace
r_int
id|nr
suffix:semicolon
r_if
c_cond
(paren
id|istate-&gt;name_hash_initialized
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|istate-&gt;cache_nr
)paren
id|preallocate_hash
c_func
(paren
op_amp
id|istate-&gt;name_hash
comma
id|istate-&gt;cache_nr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
id|nr
OL
id|istate-&gt;cache_nr
suffix:semicolon
id|nr
op_increment
)paren
id|hash_index_entry
c_func
(paren
id|istate
comma
id|istate-&gt;cache
(braket
id|nr
)braket
)paren
suffix:semicolon
id|istate-&gt;name_hash_initialized
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|add_name_hash
r_void
id|add_name_hash
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
id|ce-&gt;ce_flags
op_and_assign
op_complement
id|CE_UNHASHED
suffix:semicolon
r_if
c_cond
(paren
id|istate-&gt;name_hash_initialized
)paren
id|hash_index_entry
c_func
(paren
id|istate
comma
id|ce
)paren
suffix:semicolon
)brace
DECL|function|slow_same_name
r_static
r_int
id|slow_same_name
c_func
(paren
r_const
r_char
op_star
id|name1
comma
r_int
id|len1
comma
r_const
r_char
op_star
id|name2
comma
r_int
id|len2
)paren
(brace
r_if
c_cond
(paren
id|len1
op_ne
id|len2
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len1
)paren
(brace
r_int
r_char
id|c1
op_assign
op_star
id|name1
op_increment
suffix:semicolon
r_int
r_char
id|c2
op_assign
op_star
id|name2
op_increment
suffix:semicolon
id|len1
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
(brace
id|c1
op_assign
id|toupper
c_func
(paren
id|c1
)paren
suffix:semicolon
id|c2
op_assign
id|toupper
c_func
(paren
id|c2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|same_name
r_static
r_int
id|same_name
c_func
(paren
r_const
r_struct
id|cache_entry
op_star
id|ce
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_int
id|icase
)paren
(brace
r_int
id|len
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Always do exact compare, even if we want a case-ignoring comparison;&n;&t; * we do the quick exact one first, because it will be the common case.&n;&t; */
r_if
c_cond
(paren
id|len
op_eq
id|namelen
op_logical_and
op_logical_neg
id|cache_name_compare
c_func
(paren
id|name
comma
id|namelen
comma
id|ce-&gt;name
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|icase
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If the entry we&squot;re comparing is a filename (no trailing slash), then compare&n;&t; * the lengths exactly.&n;&t; */
r_if
c_cond
(paren
id|name
(braket
id|namelen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_return
id|slow_same_name
c_func
(paren
id|name
comma
id|namelen
comma
id|ce-&gt;name
comma
id|len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For a directory, we point to an arbitrary cache_entry filename.  Just&n;&t; * make sure the directory portion matches.&n;&t; */
r_return
id|slow_same_name
c_func
(paren
id|name
comma
id|namelen
comma
id|ce-&gt;name
comma
id|namelen
OL
id|len
ques
c_cond
id|namelen
suffix:colon
id|len
)paren
suffix:semicolon
)brace
DECL|function|index_name_exists
r_struct
id|cache_entry
op_star
id|index_name_exists
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_int
id|icase
)paren
(brace
r_int
r_int
id|hash
op_assign
id|hash_name
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
id|lazy_init_name_hash
c_func
(paren
id|istate
)paren
suffix:semicolon
id|ce
op_assign
id|lookup_hash
c_func
(paren
id|hash
comma
op_amp
id|istate-&gt;name_hash
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ce
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_UNHASHED
)paren
)paren
(brace
r_if
c_cond
(paren
id|same_name
c_func
(paren
id|ce
comma
id|name
comma
id|namelen
comma
id|icase
)paren
)paren
r_return
id|ce
suffix:semicolon
)brace
r_if
c_cond
(paren
id|icase
op_logical_and
id|name
(braket
id|namelen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|ce
op_assign
id|ce-&gt;dir_next
suffix:semicolon
r_else
id|ce
op_assign
id|ce-&gt;next
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Might be a submodule.  Despite submodules being directories,&n;&t; * they are stored in the name hash without a closing slash.&n;&t; * When ignore_case is 1, directories are stored in the name hash&n;&t; * with their closing slash.&n;&t; *&n;&t; * The side effect of this storage technique is we have need to&n;&t; * remove the slash from name and perform the lookup again without&n;&t; * the slash.  If a match is made, S_ISGITLINK(ce-&gt;mode) will be&n;&t; * true.&n;&t; */
r_if
c_cond
(paren
id|icase
op_logical_and
id|name
(braket
id|namelen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|ce
op_assign
id|index_name_exists
c_func
(paren
id|istate
comma
id|name
comma
id|namelen
l_int|1
comma
id|icase
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ce
op_logical_and
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
r_return
id|ce
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
eof
