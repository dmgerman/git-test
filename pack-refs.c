macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;pack-refs.h&quot;
DECL|struct|ref_to_prune
r_struct
id|ref_to_prune
(brace
DECL|member|next
r_struct
id|ref_to_prune
op_star
id|next
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pack_refs_cb_data
r_struct
id|pack_refs_cb_data
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ref_to_prune
r_struct
id|ref_to_prune
op_star
id|ref_to_prune
suffix:semicolon
DECL|member|refs_file
id|FILE
op_star
id|refs_file
suffix:semicolon
)brace
suffix:semicolon
DECL|function|do_not_prune
r_static
r_int
id|do_not_prune
c_func
(paren
r_int
id|flags
)paren
(brace
multiline_comment|/* If it is already packed or if it is a symref,&n;&t; * do not prune it.&n;&t; */
r_return
(paren
id|flags
op_amp
(paren
id|REF_ISSYMREF
op_or
id|REF_ISPACKED
)paren
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
r_struct
id|pack_refs_cb_data
op_star
id|cb
op_assign
id|cb_data
suffix:semicolon
r_int
id|is_tag_ref
suffix:semicolon
multiline_comment|/* Do not pack the symbolic refs */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|REF_ISSYMREF
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|is_tag_ref
op_assign
op_logical_neg
id|prefixcmp
c_func
(paren
id|path
comma
l_string|&quot;refs/tags/&quot;
)paren
suffix:semicolon
multiline_comment|/* ALWAYS pack refs that were already packed or are tags */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cb-&gt;flags
op_amp
id|PACK_REFS_ALL
)paren
op_logical_and
op_logical_neg
id|is_tag_ref
op_logical_and
op_logical_neg
(paren
id|flags
op_amp
id|REF_ISPACKED
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|cb-&gt;refs_file
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
r_if
c_cond
(paren
id|is_tag_ref
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
id|fprintf
c_func
(paren
id|cb-&gt;refs_file
comma
l_string|&quot;^%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|cb-&gt;flags
op_amp
id|PACK_REFS_PRUNE
)paren
op_logical_and
op_logical_neg
id|do_not_prune
c_func
(paren
id|flags
)paren
)paren
(brace
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|path
)paren
op_plus
l_int|1
suffix:semicolon
r_struct
id|ref_to_prune
op_star
id|n
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|n
)paren
op_plus
id|namelen
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|n-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|n-&gt;name
comma
id|path
)paren
suffix:semicolon
id|n-&gt;next
op_assign
id|cb-&gt;ref_to_prune
suffix:semicolon
id|cb-&gt;ref_to_prune
op_assign
id|n
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove empty parents, but spare refs/ and immediate subdirs.&n; * Note: munges *name.&n; */
DECL|function|try_remove_empty_parents
r_static
r_void
id|try_remove_empty_parents
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
id|i
suffix:semicolon
id|p
op_assign
id|name
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* refs/{heads,tags,...}/ */
r_while
c_loop
(paren
op_star
id|p
op_logical_and
op_star
id|p
op_ne
l_char|&squot;/&squot;
)paren
id|p
op_increment
suffix:semicolon
multiline_comment|/* tolerate duplicate slashes; see check_refname_format() */
r_while
c_loop
(paren
op_star
id|p
op_eq
l_char|&squot;/&squot;
)paren
id|p
op_increment
suffix:semicolon
)brace
r_for
c_loop
(paren
id|q
op_assign
id|p
suffix:semicolon
op_star
id|q
suffix:semicolon
id|q
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
id|q
OG
id|p
op_logical_and
op_star
id|q
op_ne
l_char|&squot;/&squot;
)paren
id|q
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|q
OG
id|p
op_logical_and
op_star
(paren
id|q
op_minus
l_int|1
)paren
op_eq
l_char|&squot;/&squot;
)paren
id|q
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|q
op_eq
id|p
)paren
r_break
suffix:semicolon
op_star
id|q
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|rmdir
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|name
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* make sure nobody touched the ref, and unlink */
DECL|function|prune_ref
r_static
r_void
id|prune_ref
c_func
(paren
r_struct
id|ref_to_prune
op_star
id|r
)paren
(brace
r_struct
id|ref_lock
op_star
id|lock
op_assign
id|lock_ref_sha1
c_func
(paren
id|r-&gt;name
op_plus
l_int|5
comma
id|r-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock
)paren
(brace
id|unlink_or_warn
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|r-&gt;name
)paren
)paren
suffix:semicolon
id|unlock_ref
c_func
(paren
id|lock
)paren
suffix:semicolon
id|try_remove_empty_parents
c_func
(paren
id|r-&gt;name
)paren
suffix:semicolon
)brace
)brace
DECL|function|prune_refs
r_static
r_void
id|prune_refs
c_func
(paren
r_struct
id|ref_to_prune
op_star
id|r
)paren
(brace
r_while
c_loop
(paren
id|r
)paren
(brace
id|prune_ref
c_func
(paren
id|r
)paren
suffix:semicolon
id|r
op_assign
id|r-&gt;next
suffix:semicolon
)brace
)brace
DECL|variable|packed
r_static
r_struct
id|lock_file
id|packed
suffix:semicolon
DECL|function|pack_refs
r_int
id|pack_refs
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_int
id|fd
suffix:semicolon
r_struct
id|pack_refs_cb_data
id|cbdata
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cbdata
comma
l_int|0
comma
r_sizeof
(paren
id|cbdata
)paren
)paren
suffix:semicolon
id|cbdata.flags
op_assign
id|flags
suffix:semicolon
id|fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|packed
comma
id|git_path
c_func
(paren
l_string|&quot;packed-refs&quot;
)paren
comma
id|LOCK_DIE_ON_ERROR
)paren
suffix:semicolon
id|cbdata.refs_file
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
id|cbdata.refs_file
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to create ref-pack file structure&quot;
)paren
suffix:semicolon
multiline_comment|/* perhaps other traits later as well */
id|fprintf
c_func
(paren
id|cbdata.refs_file
comma
l_string|&quot;# pack-refs with: peeled &bslash;n&quot;
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|handle_one_ref
comma
op_amp
id|cbdata
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|cbdata.refs_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;failed to write ref-pack file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fflush
c_func
(paren
id|cbdata.refs_file
)paren
op_logical_or
id|fsync
c_func
(paren
id|fd
)paren
op_logical_or
id|fclose
c_func
(paren
id|cbdata.refs_file
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to write ref-pack file&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Since the lock file was fdopen()&squot;ed and then fclose()&squot;ed above,&n;&t; * assign -1 to the lock file descriptor so that commit_lock_file()&n;&t; * won&squot;t try to close() it.&n;&t; */
id|packed.fd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|commit_lock_file
c_func
(paren
op_amp
id|packed
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to overwrite old ref-pack file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cbdata.flags
op_amp
id|PACK_REFS_PRUNE
)paren
id|prune_refs
c_func
(paren
id|cbdata.ref_to_prune
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
