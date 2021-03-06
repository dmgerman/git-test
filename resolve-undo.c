macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;resolve-undo.h&quot;
macro_line|#include &quot;string-list.h&quot;
multiline_comment|/* The only error case is to run out of memory in string-list */
DECL|function|record_resolve_undo
r_void
id|record_resolve_undo
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
r_struct
id|string_list_item
op_star
id|lost
suffix:semicolon
r_struct
id|resolve_undo_info
op_star
id|ui
suffix:semicolon
r_struct
id|string_list
op_star
id|resolve_undo
suffix:semicolon
r_int
id|stage
op_assign
id|ce_stage
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stage
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|istate-&gt;resolve_undo
)paren
(brace
id|resolve_undo
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|resolve_undo
)paren
)paren
suffix:semicolon
id|resolve_undo-&gt;strdup_strings
op_assign
l_int|1
suffix:semicolon
id|istate-&gt;resolve_undo
op_assign
id|resolve_undo
suffix:semicolon
)brace
id|resolve_undo
op_assign
id|istate-&gt;resolve_undo
suffix:semicolon
id|lost
op_assign
id|string_list_insert
c_func
(paren
id|resolve_undo
comma
id|ce-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lost-&gt;util
)paren
id|lost-&gt;util
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ui
)paren
)paren
suffix:semicolon
id|ui
op_assign
id|lost-&gt;util
suffix:semicolon
id|hashcpy
c_func
(paren
id|ui-&gt;sha1
(braket
id|stage
l_int|1
)braket
comma
id|ce-&gt;sha1
)paren
suffix:semicolon
id|ui-&gt;mode
(braket
id|stage
l_int|1
)braket
op_assign
id|ce-&gt;ce_mode
suffix:semicolon
)brace
DECL|function|resolve_undo_write
r_void
id|resolve_undo_write
c_func
(paren
r_struct
id|strbuf
op_star
id|sb
comma
r_struct
id|string_list
op_star
id|resolve_undo
)paren
(brace
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
id|for_each_string_list_item
c_func
(paren
id|item
comma
id|resolve_undo
)paren
(brace
r_struct
id|resolve_undo_info
op_star
id|ui
op_assign
id|item-&gt;util
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ui
)paren
r_continue
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
id|item-&gt;string
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|sb
comma
l_int|0
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|strbuf_addf
c_func
(paren
id|sb
comma
l_string|&quot;%o%c&quot;
comma
id|ui-&gt;mode
(braket
id|i
)braket
comma
l_int|0
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ui-&gt;mode
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|ui-&gt;sha1
(braket
id|i
)braket
comma
l_int|20
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|resolve_undo_read
r_struct
id|string_list
op_star
id|resolve_undo_read
c_func
(paren
r_const
r_char
op_star
id|data
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|string_list
op_star
id|resolve_undo
suffix:semicolon
r_int
id|len
suffix:semicolon
r_char
op_star
id|endptr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|resolve_undo
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|resolve_undo
)paren
)paren
suffix:semicolon
id|resolve_undo-&gt;strdup_strings
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_struct
id|string_list_item
op_star
id|lost
suffix:semicolon
r_struct
id|resolve_undo_info
op_star
id|ui
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|data
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|len
)paren
r_goto
id|error
suffix:semicolon
id|lost
op_assign
id|string_list_insert
c_func
(paren
id|resolve_undo
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lost-&gt;util
)paren
id|lost-&gt;util
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ui
)paren
)paren
suffix:semicolon
id|ui
op_assign
id|lost-&gt;util
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|data
op_add_assign
id|len
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ui-&gt;mode
(braket
id|i
)braket
op_assign
id|strtoul
c_func
(paren
id|data
comma
op_amp
id|endptr
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|endptr
op_logical_or
id|endptr
op_eq
id|data
op_logical_or
op_star
id|endptr
)paren
r_goto
id|error
suffix:semicolon
id|len
op_assign
(paren
id|endptr
op_plus
l_int|1
)paren
(paren
r_char
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|len
)paren
r_goto
id|error
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|data
op_add_assign
id|len
suffix:semicolon
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ui-&gt;mode
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|20
)paren
r_goto
id|error
suffix:semicolon
id|hashcpy
c_func
(paren
id|ui-&gt;sha1
(braket
id|i
)braket
comma
(paren
r_const
r_int
r_char
op_star
)paren
id|data
)paren
suffix:semicolon
id|size
op_sub_assign
l_int|20
suffix:semicolon
id|data
op_add_assign
l_int|20
suffix:semicolon
)brace
)brace
r_return
id|resolve_undo
suffix:semicolon
id|error
suffix:colon
id|string_list_clear
c_func
(paren
id|resolve_undo
comma
l_int|1
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;Index records invalid resolve-undo information&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|resolve_undo_clear_index
r_void
id|resolve_undo_clear_index
c_func
(paren
r_struct
id|index_state
op_star
id|istate
)paren
(brace
r_struct
id|string_list
op_star
id|resolve_undo
op_assign
id|istate-&gt;resolve_undo
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_undo
)paren
r_return
suffix:semicolon
id|string_list_clear
c_func
(paren
id|resolve_undo
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|resolve_undo
)paren
suffix:semicolon
id|istate-&gt;resolve_undo
op_assign
l_int|NULL
suffix:semicolon
id|istate-&gt;cache_changed
op_or_assign
id|RESOLVE_UNDO_CHANGED
suffix:semicolon
)brace
DECL|function|unmerge_index_entry_at
r_int
id|unmerge_index_entry_at
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_int
id|pos
)paren
(brace
r_const
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_struct
id|resolve_undo_info
op_star
id|ru
suffix:semicolon
r_int
id|i
comma
id|err
op_assign
l_int|0
comma
id|matched
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|istate-&gt;resolve_undo
)paren
r_return
id|pos
suffix:semicolon
id|ce
op_assign
id|istate-&gt;cache
(braket
id|pos
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
(brace
multiline_comment|/* already unmerged */
r_while
c_loop
(paren
(paren
id|pos
OL
id|istate-&gt;cache_nr
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|istate-&gt;cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|ce-&gt;name
)paren
)paren
id|pos
op_increment
suffix:semicolon
r_return
id|pos
l_int|1
suffix:semicolon
multiline_comment|/* return the last entry processed */
)brace
id|item
op_assign
id|string_list_lookup
c_func
(paren
id|istate-&gt;resolve_undo
comma
id|ce-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|item
)paren
r_return
id|pos
suffix:semicolon
id|ru
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ru
)paren
r_return
id|pos
suffix:semicolon
id|matched
op_assign
id|ce-&gt;ce_flags
op_amp
id|CE_MATCHED
suffix:semicolon
id|name
op_assign
id|xstrdup
c_func
(paren
id|ce-&gt;name
)paren
suffix:semicolon
id|remove_index_entry_at
c_func
(paren
id|istate
comma
id|pos
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|nce
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ru-&gt;mode
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|nce
op_assign
id|make_cache_entry
c_func
(paren
id|ru-&gt;mode
(braket
id|i
)braket
comma
id|ru-&gt;sha1
(braket
id|i
)braket
comma
id|name
comma
id|i
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|matched
)paren
id|nce-&gt;ce_flags
op_or_assign
id|CE_MATCHED
suffix:semicolon
r_if
c_cond
(paren
id|add_index_entry
c_func
(paren
id|istate
comma
id|nce
comma
id|ADD_CACHE_OK_TO_ADD
)paren
)paren
(brace
id|err
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;cannot unmerge &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|pos
suffix:semicolon
id|free
c_func
(paren
id|ru
)paren
suffix:semicolon
id|item-&gt;util
op_assign
l_int|NULL
suffix:semicolon
r_return
id|unmerge_index_entry_at
c_func
(paren
id|istate
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|unmerge_marked_index
r_void
id|unmerge_marked_index
c_func
(paren
r_struct
id|index_state
op_star
id|istate
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|istate-&gt;resolve_undo
)paren
r_return
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
id|istate-&gt;cache_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|istate-&gt;cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|CE_MATCHED
)paren
id|i
op_assign
id|unmerge_index_entry_at
c_func
(paren
id|istate
comma
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|unmerge_index
r_void
id|unmerge_index
c_func
(paren
r_struct
id|index_state
op_star
id|istate
comma
r_const
r_struct
id|pathspec
op_star
id|pathspec
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|istate-&gt;resolve_undo
)paren
r_return
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
id|istate-&gt;cache_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|istate-&gt;cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_path_match
c_func
(paren
id|ce
comma
id|pathspec
comma
l_int|NULL
)paren
)paren
r_continue
suffix:semicolon
id|i
op_assign
id|unmerge_index_entry_at
c_func
(paren
id|istate
comma
id|i
)paren
suffix:semicolon
)brace
)brace
eof
