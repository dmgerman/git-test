multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;builtin.h&quot;
multiline_comment|/*&n; * Default to not allowing changes to the list of files. The&n; * tool doesn&squot;t actually care, but this makes it harder to add&n; * files to the revision control by mistake by doing something&n; * like &quot;git-update-index *&quot; and suddenly having all the object&n; * files be revision controlled.&n; */
DECL|variable|allow_add
r_static
r_int
id|allow_add
suffix:semicolon
DECL|variable|allow_remove
r_static
r_int
id|allow_remove
suffix:semicolon
DECL|variable|allow_replace
r_static
r_int
id|allow_replace
suffix:semicolon
DECL|variable|info_only
r_static
r_int
id|info_only
suffix:semicolon
DECL|variable|force_remove
r_static
r_int
id|force_remove
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
suffix:semicolon
DECL|variable|mark_valid_only
r_static
r_int
id|mark_valid_only
suffix:semicolon
DECL|macro|MARK_VALID
mdefine_line|#define MARK_VALID 1
DECL|macro|UNMARK_VALID
mdefine_line|#define UNMARK_VALID 2
DECL|function|report
r_static
r_void
id|report
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|vp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verbose
)paren
r_return
suffix:semicolon
id|va_start
c_func
(paren
id|vp
comma
id|fmt
)paren
suffix:semicolon
id|vprintf
c_func
(paren
id|fmt
comma
id|vp
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|vp
)paren
suffix:semicolon
)brace
DECL|function|mark_valid
r_static
r_int
id|mark_valid
c_func
(paren
r_const
r_char
op_star
id|path
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
suffix:semicolon
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
(brace
r_switch
c_cond
(paren
id|mark_valid_only
)paren
(brace
r_case
id|MARK_VALID
suffix:colon
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_VALID
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UNMARK_VALID
suffix:colon
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|ce_flags
op_and_assign
op_complement
id|htons
c_func
(paren
id|CE_VALID
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path
)paren
suffix:semicolon
id|active_cache_changed
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|add_file_to_cache
r_static
r_int
id|add_file_to_cache
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|size
comma
id|namelen
comma
id|option
comma
id|status
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|status
op_assign
id|lstat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
suffix:semicolon
multiline_comment|/* We probably want to do this in remove_file_from_cache() and&n;&t; * add_cache_entry() instead...&n;&t; */
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
op_logical_or
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
multiline_comment|/* When we used to have &quot;path&quot; and now we want to add&n;&t;&t; * &quot;path/file&quot;, we need a way to remove &quot;path&quot; before&n;&t;&t; * being able to add &quot;path/file&quot;.  However,&n;&t;&t; * &quot;git-update-index --remove path&quot; would not work.&n;&t;&t; * --force-remove can be used but this is more user&n;&t;&t; * friendly, especially since we can do the opposite&n;&t;&t; * case just fine without --force-remove.&n;&t;&t; */
r_if
c_cond
(paren
id|status
op_eq
l_int|0
op_logical_or
(paren
id|errno
op_eq
id|ENOENT
op_logical_or
id|errno
op_eq
id|ENOTDIR
)paren
)paren
(brace
r_if
c_cond
(paren
id|allow_remove
)paren
(brace
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|path
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot remove from the index&quot;
comma
id|path
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
(brace
r_return
id|error
c_func
(paren
l_string|&quot;%s: does not exist and --remove not passed&quot;
comma
id|path
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|status
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: is a directory - add files inside instead&quot;
comma
id|path
)paren
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;lstat(&bslash;&quot;%s&bslash;&quot;): %s&quot;
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
)brace
id|namelen
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|namelen
)paren
suffix:semicolon
id|ce
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|namelen
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|htons
c_func
(paren
id|namelen
)paren
suffix:semicolon
id|fill_stat_cache_info
c_func
(paren
id|ce
comma
op_amp
id|st
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|st.st_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trust_executable_bit
)paren
(brace
multiline_comment|/* If there is an existing entry, pick the mode bits&n;&t;&t; * from it, otherwise force to 644.&n;&t;&t; */
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
id|ce-&gt;ce_mode
op_assign
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|ce_mode
suffix:semicolon
r_else
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|S_IFREG
op_or
l_int|0644
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index_path
c_func
(paren
id|ce-&gt;sha1
comma
id|path
comma
op_amp
id|st
comma
op_logical_neg
id|info_only
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|option
op_assign
id|allow_add
ques
c_cond
id|ADD_CACHE_OK_TO_ADD
suffix:colon
l_int|0
suffix:semicolon
id|option
op_or_assign
id|allow_replace
ques
c_cond
id|ADD_CACHE_OK_TO_REPLACE
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|add_cache_entry
c_func
(paren
id|ce
comma
id|option
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot add to the index - missing --add option?&quot;
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_cacheinfo
r_static
r_int
id|add_cacheinfo
c_func
(paren
r_int
r_int
id|mode
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|path
comma
r_int
id|stage
)paren
(brace
r_int
id|size
comma
id|len
comma
id|option
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|path
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|len
)paren
suffix:semicolon
id|ce
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|size
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|len
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|create_ce_flags
c_func
(paren
id|len
comma
id|stage
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|assume_unchanged
)paren
id|ce-&gt;ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_VALID
)paren
suffix:semicolon
id|option
op_assign
id|allow_add
ques
c_cond
id|ADD_CACHE_OK_TO_ADD
suffix:colon
l_int|0
suffix:semicolon
id|option
op_or_assign
id|allow_replace
ques
c_cond
id|ADD_CACHE_OK_TO_REPLACE
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|add_cache_entry
c_func
(paren
id|ce
comma
id|option
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;%s: cannot add to the index - missing --add option?&quot;
comma
id|path
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;add &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chmod_path
r_static
r_void
id|chmod_path
c_func
(paren
r_int
id|flip
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|pos
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
id|mode
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_switch
c_cond
(paren
id|flip
)paren
(brace
r_case
l_char|&squot;+&squot;
suffix:colon
id|ce-&gt;ce_mode
op_or_assign
id|htonl
c_func
(paren
l_int|0111
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
id|ce-&gt;ce_mode
op_and_assign
id|htonl
c_func
(paren
op_complement
l_int|0111
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|fail
suffix:semicolon
)brace
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path
)paren
suffix:semicolon
id|active_cache_changed
op_assign
l_int|1
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;chmod %cx &squot;%s&squot;&quot;
comma
id|flip
comma
id|path
)paren
suffix:semicolon
r_return
suffix:semicolon
id|fail
suffix:colon
id|die
c_func
(paren
l_string|&quot;git-update-index: cannot chmod %cx &squot;%s&squot;&quot;
comma
id|flip
comma
id|path
)paren
suffix:semicolon
)brace
DECL|function|update_one
r_static
r_void
id|update_one
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|prefix
comma
r_int
id|prefix_length
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|p
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Ignoring path %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mark_valid_only
)paren
(brace
r_if
c_cond
(paren
id|mark_valid
c_func
(paren
id|p
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to mark file %s&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|force_remove
)paren
(brace
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|p
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: unable to remove %s&quot;
comma
id|path
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;remove &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|add_file_to_cache
c_func
(paren
id|p
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to process file %s&quot;
comma
id|path
)paren
suffix:semicolon
id|report
c_func
(paren
l_string|&quot;add &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|free_return
suffix:colon
r_if
c_cond
(paren
id|p
template_param
id|path
op_plus
id|strlen
c_func
(paren
id|path
)paren
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|read_index_info
r_static
r_void
id|read_index_info
c_func
(paren
r_int
id|line_termination
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|ptr
comma
op_star
id|tab
suffix:semicolon
r_char
op_star
id|path_name
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_int
id|stage
suffix:semicolon
multiline_comment|/* This reads lines formatted in one of three formats:&n;&t;&t; *&n;&t;&t; * (1) mode         SP sha1          TAB path&n;&t;&t; * The first format is what &quot;git-apply --index-info&quot;&n;&t;&t; * reports, and used to reconstruct a partial tree&n;&t;&t; * that is used for phony merge base tree when falling&n;&t;&t; * back on 3-way merge.&n;&t;&t; *&n;&t;&t; * (2) mode SP type SP sha1          TAB path&n;&t;&t; * The second format is to stuff git-ls-tree output&n;&t;&t; * into the index file.&n;&t;&t; *&n;&t;&t; * (3) mode         SP sha1 SP stage TAB path&n;&t;&t; * This format is to put higher order stages into the&n;&t;&t; * index file and matches git-ls-files --stage output.&n;&t;&t; */
id|read_line
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.eof
)paren
r_break
suffix:semicolon
id|mode
op_assign
id|strtoul
c_func
(paren
id|buf.buf
comma
op_amp
id|ptr
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
id|buf.buf
op_logical_or
op_star
id|ptr
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|bad_line
suffix:semicolon
id|tab
op_assign
id|strchr
c_func
(paren
id|ptr
comma
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tab
op_logical_or
id|tab
id|ptr
OL
l_int|41
)paren
r_goto
id|bad_line
suffix:semicolon
r_if
c_cond
(paren
id|tab
(braket
l_int|2
)braket
op_eq
l_char|&squot; &squot;
op_logical_and
l_char|&squot;0&squot;
op_le
id|tab
(braket
l_int|1
)braket
op_logical_and
id|tab
(braket
l_int|1
)braket
op_le
l_char|&squot;3&squot;
)paren
(brace
id|stage
op_assign
id|tab
(braket
l_int|1
)braket
l_char|&squot;0&squot;
suffix:semicolon
id|ptr
op_assign
id|tab
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* point at the head of path */
id|tab
op_assign
id|tab
l_int|2
suffix:semicolon
multiline_comment|/* point at tail of sha1 */
)brace
r_else
(brace
id|stage
op_assign
l_int|0
suffix:semicolon
id|ptr
op_assign
id|tab
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* point at the head of path */
)brace
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|tab
l_int|40
comma
id|sha1
)paren
op_logical_or
id|tab
(braket
l_int|41
)braket
op_ne
l_char|&squot; &squot;
)paren
r_goto
id|bad_line
suffix:semicolon
r_if
c_cond
(paren
id|line_termination
op_logical_and
id|ptr
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
id|path_name
op_assign
id|unquote_c_style
c_func
(paren
id|ptr
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|path_name
op_assign
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|verify_path
c_func
(paren
id|path_name
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Ignoring path %s&bslash;n&quot;
comma
id|path_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path_name
op_ne
id|ptr
)paren
id|free
c_func
(paren
id|path_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mode
)paren
(brace
multiline_comment|/* mode == 0 means there is no such path -- remove */
r_if
c_cond
(paren
id|remove_file_from_cache
c_func
(paren
id|path_name
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: unable to remove %s&quot;
comma
id|ptr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* mode &squot; &squot; sha1 &squot;&bslash;t&squot; name&n;&t;&t;&t; * ptr[-1] points at tab,&n;&t;&t;&t; * ptr[-41] is at the beginning of sha1&n;&t;&t;&t; */
id|ptr
(braket
l_int|42
)braket
op_assign
id|ptr
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|add_cacheinfo
c_func
(paren
id|mode
comma
id|sha1
comma
id|path_name
comma
id|stage
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: unable to update %s&quot;
comma
id|path_name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|path_name
op_ne
id|ptr
)paren
id|free
c_func
(paren
id|path_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
id|bad_line
suffix:colon
id|die
c_func
(paren
l_string|&quot;malformed index info %s&quot;
comma
id|buf.buf
)paren
suffix:semicolon
)brace
)brace
DECL|variable|update_index_usage
r_static
r_const
r_char
id|update_index_usage
(braket
)braket
op_assign
l_string|&quot;git-update-index [-q] [--add] [--replace] [--remove] [--unmerged] [--refresh] [--really-refresh] [--cacheinfo] [--chmod=(+|-)x] [--assume-unchanged] [--info-only] [--force-remove] [--stdin] [--index-info] [--unresolve] [--again | -g] [--ignore-missing] [-z] [--verbose] [--] &lt;file&gt;...&quot;
suffix:semicolon
DECL|variable|head_sha1
r_static
r_int
r_char
id|head_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|merge_head_sha1
r_static
r_int
r_char
id|merge_head_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|function|read_one_ent
r_static
r_struct
id|cache_entry
op_star
id|read_one_ent
c_func
(paren
r_const
r_char
op_star
id|which
comma
r_int
r_char
op_star
id|ent
comma
r_const
r_char
op_star
id|path
comma
r_int
id|namelen
comma
r_int
id|stage
)paren
(brace
r_int
id|mode
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
r_if
c_cond
(paren
id|get_tree_entry
c_func
(paren
id|ent
comma
id|path
comma
id|sha1
comma
op_amp
id|mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|which
)paren
id|error
c_func
(paren
l_string|&quot;%s: not in %s branch.&quot;
comma
id|path
comma
id|which
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mode
op_eq
id|S_IFDIR
)paren
(brace
r_if
c_cond
(paren
id|which
)paren
id|error
c_func
(paren
l_string|&quot;%s: not a blob in %s branch.&quot;
comma
id|path
comma
id|which
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|size
op_assign
id|cache_entry_size
c_func
(paren
id|namelen
)paren
suffix:semicolon
id|ce
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|size
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ce-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|namelen
)paren
suffix:semicolon
id|ce-&gt;ce_flags
op_assign
id|create_ce_flags
c_func
(paren
id|namelen
comma
id|stage
)paren
suffix:semicolon
id|ce-&gt;ce_mode
op_assign
id|create_ce_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
r_return
id|ce
suffix:semicolon
)brace
DECL|function|unresolve_one
r_static
r_int
id|unresolve_one
c_func
(paren
r_const
r_char
op_star
id|path
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
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce_2
op_assign
l_int|NULL
comma
op_star
id|ce_3
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* See if there is such entry in the index. */
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|path
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
(brace
multiline_comment|/* If there isn&squot;t, either it is unmerged, or&n;&t;&t; * resolved as &quot;removed&quot; by mistake.  We do not&n;&t;&t; * want to do anything in the former case.&n;&t;&t; */
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|active_nr
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_namelen
c_func
(paren
id|ce
)paren
op_eq
id|namelen
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|namelen
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: skipping still unmerged path.&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Grab blobs from given path from HEAD and MERGE_HEAD,&n;&t; * stuff HEAD version in stage #2,&n;&t; * stuff MERGE_HEAD version in stage #3.&n;&t; */
id|ce_2
op_assign
id|read_one_ent
c_func
(paren
l_string|&quot;our&quot;
comma
id|head_sha1
comma
id|path
comma
id|namelen
comma
l_int|2
)paren
suffix:semicolon
id|ce_3
op_assign
id|read_one_ent
c_func
(paren
l_string|&quot;their&quot;
comma
id|merge_head_sha1
comma
id|path
comma
id|namelen
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_2
op_logical_or
op_logical_neg
id|ce_3
)paren
(brace
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|ce_2-&gt;sha1
comma
id|ce_3-&gt;sha1
)paren
op_logical_and
id|ce_2-&gt;ce_mode
op_eq
id|ce_3-&gt;ce_mode
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: identical in both, skipping.&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
id|cache_tree_invalidate_path
c_func
(paren
id|active_cache_tree
comma
id|path
)paren
suffix:semicolon
id|remove_file_from_cache
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add_cache_entry
c_func
(paren
id|ce_2
comma
id|ADD_CACHE_OK_TO_ADD
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;%s: cannot add our version to the index.&quot;
comma
id|path
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|free_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|add_cache_entry
c_func
(paren
id|ce_3
comma
id|ADD_CACHE_OK_TO_ADD
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s: cannot add their version to the index.&quot;
comma
id|path
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
id|free_return
suffix:colon
id|free
c_func
(paren
id|ce_2
)paren
suffix:semicolon
id|free
c_func
(paren
id|ce_3
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|read_head_pointers
r_static
r_void
id|read_head_pointers
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|read_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;No HEAD -- no initial commit yet?&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_ref
c_func
(paren
l_string|&quot;MERGE_HEAD&quot;
comma
id|merge_head_sha1
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Not in the middle of a merge.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_unresolve
r_static
r_int
id|do_unresolve
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
comma
r_const
r_char
op_star
id|prefix
comma
r_int
id|prefix_length
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Read HEAD and MERGE_HEAD; if MERGE_HEAD does not exist, we&n;&t; * are not doing a merge, so exit with success status.&n;&t; */
id|read_head_pointers
c_func
(paren
)paren
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
id|ac
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
id|av
(braket
id|i
)braket
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|arg
)paren
suffix:semicolon
id|err
op_or_assign
id|unresolve_one
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
template_param
id|arg
op_plus
id|strlen
c_func
(paren
id|arg
)paren
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|do_reupdate
r_static
r_int
id|do_reupdate
c_func
(paren
r_int
id|ac
comma
r_const
r_char
op_star
op_star
id|av
comma
r_const
r_char
op_star
id|prefix
comma
r_int
id|prefix_length
)paren
(brace
multiline_comment|/* Read HEAD and run update-index on paths that are&n;&t; * merged and already different between index and HEAD.&n;&t; */
r_int
id|pos
suffix:semicolon
r_int
id|has_head
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
op_star
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|av
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
)paren
)paren
multiline_comment|/* If there is no HEAD, that means it is an initial&n;&t;&t; * commit.  Update everything in the index.&n;&t;&t; */
id|has_head
op_assign
l_int|0
suffix:semicolon
id|redo
suffix:colon
r_for
c_loop
(paren
id|pos
op_assign
l_int|0
suffix:semicolon
id|pos
OL
id|active_nr
suffix:semicolon
id|pos
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_struct
id|cache_entry
op_star
id|old
op_assign
l_int|NULL
suffix:semicolon
r_int
id|save_nr
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
op_logical_or
op_logical_neg
id|ce_path_match
c_func
(paren
id|ce
comma
id|pathspec
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|has_head
)paren
id|old
op_assign
id|read_one_ent
c_func
(paren
l_int|NULL
comma
id|head_sha1
comma
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_logical_and
id|ce-&gt;ce_mode
op_eq
id|old-&gt;ce_mode
op_logical_and
op_logical_neg
id|hashcmp
c_func
(paren
id|ce-&gt;sha1
comma
id|old-&gt;sha1
)paren
)paren
(brace
id|free
c_func
(paren
id|old
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* unchanged */
)brace
multiline_comment|/* Be careful.  The working tree may not have the&n;&t;&t; * path anymore, in which case, under &squot;allow_remove&squot;,&n;&t;&t; * or worse yet &squot;allow_replace&squot;, active_nr may decrease.&n;&t;&t; */
id|save_nr
op_assign
id|active_nr
suffix:semicolon
id|update_one
c_func
(paren
id|ce-&gt;name
op_plus
id|prefix_length
comma
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_nr
op_ne
id|active_nr
)paren
r_goto
id|redo
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_update_index
r_int
id|cmd_update_index
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
id|newfd
comma
id|entries
comma
id|has_errors
op_assign
l_int|0
comma
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_int
id|allow_options
op_assign
l_int|1
suffix:semicolon
r_int
id|read_from_stdin
op_assign
l_int|0
suffix:semicolon
r_int
id|prefix_length
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
r_char
id|set_executable_bit
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|refresh_flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|lock_file
op_star
id|lock_file
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
multiline_comment|/* We can&squot;t free this memory, it becomes part of a linked list parsed atexit() */
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
id|newfd
op_assign
id|hold_lock_file_for_update
c_func
(paren
id|lock_file
comma
id|get_index_file
c_func
(paren
)paren
comma
l_int|1
)paren
suffix:semicolon
id|entries
op_assign
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entries
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;cache corrupted&quot;
)paren
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
id|path
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|allow_options
op_logical_and
op_star
id|path
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
id|path
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|allow_options
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-q&quot;
)paren
)paren
(brace
id|refresh_flags
op_or_assign
id|REFRESH_QUIET
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--add&quot;
)paren
)paren
(brace
id|allow_add
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
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--replace&quot;
)paren
)paren
(brace
id|allow_replace
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
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--remove&quot;
)paren
)paren
(brace
id|allow_remove
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
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--unmerged&quot;
)paren
)paren
(brace
id|refresh_flags
op_or_assign
id|REFRESH_UNMERGED
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--refresh&quot;
)paren
)paren
(brace
id|has_errors
op_or_assign
id|refresh_cache
c_func
(paren
id|refresh_flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--really-refresh&quot;
)paren
)paren
(brace
id|has_errors
op_or_assign
id|refresh_cache
c_func
(paren
id|REFRESH_REALLY
op_or
id|refresh_flags
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--cacheinfo&quot;
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
r_int
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
l_int|3
op_ge
id|argc
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: --cacheinfo &lt;mode&gt; &lt;sha1&gt; &lt;path&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sscanf
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|1
)braket
comma
l_string|&quot;%o&quot;
comma
op_amp
id|mode
)paren
op_ne
l_int|1
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|argv
(braket
id|i
op_plus
l_int|2
)braket
comma
id|sha1
)paren
op_logical_or
id|add_cacheinfo
c_func
(paren
id|mode
comma
id|sha1
comma
id|argv
(braket
id|i
op_plus
l_int|3
)braket
comma
l_int|0
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: --cacheinfo&quot;
l_string|&quot; cannot add %s&quot;
comma
id|argv
(braket
id|i
op_plus
l_int|3
)braket
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--chmod=-x&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--chmod=+x&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
op_le
id|i
op_plus
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;git-update-index: %s &lt;path&gt;&quot;
comma
id|path
)paren
suffix:semicolon
id|set_executable_bit
op_assign
id|path
(braket
l_int|8
)braket
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--assume-unchanged&quot;
)paren
)paren
(brace
id|mark_valid_only
op_assign
id|MARK_VALID
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--no-assume-unchanged&quot;
)paren
)paren
(brace
id|mark_valid_only
op_assign
id|UNMARK_VALID
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--info-only&quot;
)paren
)paren
(brace
id|info_only
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
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--force-remove&quot;
)paren
)paren
(brace
id|force_remove
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
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_termination
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|argc
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;--stdin must be at the end&quot;
)paren
suffix:semicolon
id|read_from_stdin
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--index-info&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|argc
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;--index-info must be at the end&quot;
)paren
suffix:semicolon
id|allow_add
op_assign
id|allow_replace
op_assign
id|allow_remove
op_assign
l_int|1
suffix:semicolon
id|read_index_info
c_func
(paren
id|line_termination
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--unresolve&quot;
)paren
)paren
(brace
id|has_errors
op_assign
id|do_unresolve
c_func
(paren
id|argc
id|i
comma
id|argv
op_plus
id|i
comma
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_errors
)paren
id|active_cache_changed
op_assign
l_int|0
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--again&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-g&quot;
)paren
)paren
(brace
id|has_errors
op_assign
id|do_reupdate
c_func
(paren
id|argc
id|i
comma
id|argv
op_plus
id|i
comma
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_errors
)paren
id|active_cache_changed
op_assign
l_int|0
suffix:semicolon
r_goto
id|finish
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--ignore-missing&quot;
)paren
)paren
(brace
id|refresh_flags
op_or_assign
id|REFRESH_IGNORE_MISSING
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--verbose&quot;
)paren
)paren
(brace
id|verbose
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
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-h&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;--help&quot;
)paren
)paren
id|usage
c_func
(paren
id|update_index_usage
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unknown option %s&quot;
comma
id|path
)paren
suffix:semicolon
)brace
id|update_one
c_func
(paren
id|path
comma
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set_executable_bit
)paren
id|chmod_path
c_func
(paren
id|set_executable_bit
comma
id|path
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_from_stdin
)paren
(brace
r_struct
id|strbuf
id|buf
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_char
op_star
id|path_name
suffix:semicolon
r_const
r_char
op_star
id|p
suffix:semicolon
id|read_line
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.eof
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|line_termination
op_logical_and
id|buf.buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
id|path_name
op_assign
id|unquote_c_style
c_func
(paren
id|buf.buf
comma
l_int|NULL
)paren
suffix:semicolon
r_else
id|path_name
op_assign
id|buf.buf
suffix:semicolon
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|path_name
)paren
suffix:semicolon
id|update_one
c_func
(paren
id|p
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set_executable_bit
)paren
id|chmod_path
c_func
(paren
id|set_executable_bit
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
template_param
id|path_name
op_plus
id|strlen
c_func
(paren
id|path_name
)paren
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path_name
op_ne
id|buf.buf
)paren
id|free
c_func
(paren
id|path_name
)paren
suffix:semicolon
)brace
)brace
id|finish
suffix:colon
r_if
c_cond
(paren
id|active_cache_changed
)paren
(brace
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|close
c_func
(paren
id|newfd
)paren
op_logical_or
id|commit_lock_file
c_func
(paren
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
suffix:semicolon
)brace
id|rollback_lock_file
c_func
(paren
id|lock_file
)paren
suffix:semicolon
r_return
id|has_errors
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
