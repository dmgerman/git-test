multiline_comment|/*&n; * This merges the file listing in the directory cache index&n; * with the actual working directory list, and shows different&n; * combinations of the two.&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;tree.h&quot;
DECL|variable|abbrev
r_static
r_int
id|abbrev
suffix:semicolon
DECL|variable|show_deleted
r_static
r_int
id|show_deleted
suffix:semicolon
DECL|variable|show_cached
r_static
r_int
id|show_cached
suffix:semicolon
DECL|variable|show_others
r_static
r_int
id|show_others
suffix:semicolon
DECL|variable|show_stage
r_static
r_int
id|show_stage
suffix:semicolon
DECL|variable|show_unmerged
r_static
r_int
id|show_unmerged
suffix:semicolon
DECL|variable|show_modified
r_static
r_int
id|show_modified
suffix:semicolon
DECL|variable|show_killed
r_static
r_int
id|show_killed
suffix:semicolon
DECL|variable|show_valid_bit
r_static
r_int
id|show_valid_bit
suffix:semicolon
DECL|variable|line_terminator
r_static
r_int
id|line_terminator
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|prefix_len
r_static
r_int
id|prefix_len
suffix:semicolon
DECL|variable|prefix_offset
r_static
r_int
id|prefix_offset
suffix:semicolon
DECL|variable|pathspec
r_static
r_const
r_char
op_star
op_star
id|pathspec
suffix:semicolon
DECL|variable|error_unmatch
r_static
r_int
id|error_unmatch
suffix:semicolon
DECL|variable|ps_matched
r_static
r_char
op_star
id|ps_matched
suffix:semicolon
DECL|variable|with_tree
r_static
r_const
r_char
op_star
id|with_tree
suffix:semicolon
DECL|variable|tag_cached
r_static
r_const
r_char
op_star
id|tag_cached
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_unmerged
r_static
r_const
r_char
op_star
id|tag_unmerged
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_removed
r_static
r_const
r_char
op_star
id|tag_removed
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_other
r_static
r_const
r_char
op_star
id|tag_other
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_killed
r_static
r_const
r_char
op_star
id|tag_killed
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|tag_modified
r_static
r_const
r_char
op_star
id|tag_modified
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/*&n; * Match a pathspec against a filename. The first &quot;skiplen&quot; characters&n; * are the common prefix&n; */
DECL|function|pathspec_match
r_int
id|pathspec_match
c_func
(paren
r_const
r_char
op_star
op_star
id|spec
comma
r_char
op_star
id|ps_matched
comma
r_const
r_char
op_star
id|filename
comma
r_int
id|skiplen
)paren
(brace
r_const
r_char
op_star
id|m
suffix:semicolon
r_while
c_loop
(paren
(paren
id|m
op_assign
op_star
id|spec
op_increment
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|matchlen
op_assign
id|strlen
c_func
(paren
id|m
op_plus
id|skiplen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|matchlen
)paren
r_goto
id|matched
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|m
op_plus
id|skiplen
comma
id|filename
op_plus
id|skiplen
comma
id|matchlen
)paren
)paren
(brace
r_if
c_cond
(paren
id|m
(braket
id|skiplen
op_plus
id|matchlen
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
r_goto
id|matched
suffix:semicolon
r_switch
c_cond
(paren
id|filename
(braket
id|skiplen
op_plus
id|matchlen
)braket
)paren
(brace
r_case
l_char|&squot;/&squot;
suffix:colon
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
r_goto
id|matched
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|m
op_plus
id|skiplen
comma
id|filename
op_plus
id|skiplen
comma
l_int|0
)paren
)paren
r_goto
id|matched
suffix:semicolon
r_if
c_cond
(paren
id|ps_matched
)paren
id|ps_matched
op_increment
suffix:semicolon
r_continue
suffix:semicolon
id|matched
suffix:colon
r_if
c_cond
(paren
id|ps_matched
)paren
op_star
id|ps_matched
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|show_dir_entry
r_static
r_void
id|show_dir_entry
c_func
(paren
r_const
r_char
op_star
id|tag
comma
r_struct
id|dir_entry
op_star
id|ent
)paren
(brace
r_int
id|len
op_assign
id|prefix_len
suffix:semicolon
r_int
id|offset
op_assign
id|prefix_offset
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|ent-&gt;len
)paren
id|die
c_func
(paren
l_string|&quot;git-ls-files: internal error - directory entry not superset of prefix&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
op_logical_and
op_logical_neg
id|pathspec_match
c_func
(paren
id|pathspec
comma
id|ps_matched
comma
id|ent-&gt;name
comma
id|len
)paren
)paren
r_return
suffix:semicolon
id|fputs
c_func
(paren
id|tag
comma
id|stdout
)paren
suffix:semicolon
id|write_name_quoted
c_func
(paren
id|ent-&gt;name
op_plus
id|offset
comma
id|stdout
comma
id|line_terminator
)paren
suffix:semicolon
)brace
DECL|function|show_other_files
r_static
r_void
id|show_other_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Skip matching and unmerged entries for the paths,&n;&t; * since we want just &quot;others&quot;.&n;&t; *&n;&t; * (Matching entries are normally pruned during&n;&t; * the directory tree walk, but will show up for&n;&t; * gitlinks because we don&squot;t necessarily have&n;&t; * dir-&gt;show_other_directories set to suppress&n;&t; * them).&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dir-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dir_entry
op_star
id|ent
op_assign
id|dir-&gt;entries
(braket
id|i
)braket
suffix:semicolon
r_int
id|len
comma
id|pos
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Remove the &squot;/&squot; at the end that directory&n;&t;&t; * walking adds for directory entries.&n;&t;&t; */
id|len
op_assign
id|ent-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|ent-&gt;name
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|len
op_decrement
suffix:semicolon
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
r_continue
suffix:semicolon
multiline_comment|/* exact match */
id|pos
op_assign
id|pos
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
id|len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|ent-&gt;name
comma
id|len
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Yup, this one exists unmerged */
)brace
id|show_dir_entry
c_func
(paren
id|tag_other
comma
id|ent
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_killed_files
r_static
r_void
id|show_killed_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
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
id|dir-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dir_entry
op_star
id|ent
op_assign
id|dir-&gt;entries
(braket
id|i
)braket
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|sp
suffix:semicolon
r_int
id|pos
comma
id|len
comma
id|killed
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|ent-&gt;name
suffix:semicolon
id|cp
id|ent-&gt;name
OL
id|ent-&gt;len
suffix:semicolon
id|cp
op_assign
id|sp
op_plus
l_int|1
)paren
(brace
id|sp
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sp
)paren
(brace
multiline_comment|/* If ent-&gt;name is prefix of an entry in the&n;&t;&t;&t;&t; * cache, it will be killed.&n;&t;&t;&t;&t; */
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pos
)paren
id|die
c_func
(paren
l_string|&quot;bug in show-killed-files&quot;
)paren
suffix:semicolon
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|active_nr
op_logical_and
id|ce_stage
c_func
(paren
id|active_cache
(braket
id|pos
)braket
)paren
)paren
id|pos
op_increment
suffix:semicolon
multiline_comment|/* skip unmerged */
r_if
c_cond
(paren
id|active_nr
op_le
id|pos
)paren
r_break
suffix:semicolon
multiline_comment|/* pos points at a name immediately after&n;&t;&t;&t;&t; * ent-&gt;name in the cache.  Does it expect&n;&t;&t;&t;&t; * ent-&gt;name to be a directory?&n;&t;&t;&t;&t; */
id|len
op_assign
id|ce_namelen
c_func
(paren
id|active_cache
(braket
id|pos
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ent-&gt;len
OL
id|len
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
comma
id|ent-&gt;name
comma
id|ent-&gt;len
)paren
op_logical_and
id|active_cache
(braket
id|pos
)braket
op_member_access_from_pointer
id|name
(braket
id|ent-&gt;len
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|killed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|cache_name_pos
c_func
(paren
id|ent-&gt;name
comma
id|sp
id|ent-&gt;name
)paren
)paren
(brace
multiline_comment|/* If any of the leading directories in&n;&t;&t;&t;&t; * ent-&gt;name is registered in the cache,&n;&t;&t;&t;&t; * ent-&gt;name will be killed.&n;&t;&t;&t;&t; */
id|killed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|killed
)paren
id|show_dir_entry
c_func
(paren
id|tag_killed
comma
id|dir-&gt;entries
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_ce_entry
r_static
r_void
id|show_ce_entry
c_func
(paren
r_const
r_char
op_star
id|tag
comma
r_struct
id|cache_entry
op_star
id|ce
)paren
(brace
r_int
id|len
op_assign
id|prefix_len
suffix:semicolon
r_int
id|offset
op_assign
id|prefix_offset
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|ce_namelen
c_func
(paren
id|ce
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-ls-files: internal error - cache entry not superset of prefix&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathspec
op_logical_and
op_logical_neg
id|pathspec_match
c_func
(paren
id|pathspec
comma
id|ps_matched
comma
id|ce-&gt;name
comma
id|len
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_logical_and
op_star
id|tag
op_logical_and
id|show_valid_bit
op_logical_and
(paren
id|ce-&gt;ce_flags
op_amp
id|htons
c_func
(paren
id|CE_VALID
)paren
)paren
)paren
(brace
r_static
r_char
id|alttag
(braket
l_int|4
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|alttag
comma
id|tag
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isalpha
c_func
(paren
id|tag
(braket
l_int|0
)braket
)paren
)paren
id|alttag
(braket
l_int|0
)braket
op_assign
id|tolower
c_func
(paren
id|tag
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tag
(braket
l_int|0
)braket
op_eq
l_char|&squot;?&squot;
)paren
id|alttag
(braket
l_int|0
)braket
op_assign
l_char|&squot;!&squot;
suffix:semicolon
r_else
(brace
id|alttag
(braket
l_int|0
)braket
op_assign
l_char|&squot;v&squot;
suffix:semicolon
id|alttag
(braket
l_int|1
)braket
op_assign
id|tag
(braket
l_int|0
)braket
suffix:semicolon
id|alttag
(braket
l_int|2
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|alttag
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|tag
op_assign
id|alttag
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|show_stage
)paren
(brace
id|fputs
c_func
(paren
id|tag
comma
id|stdout
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%s%06o %s %d&bslash;t&quot;
comma
id|tag
comma
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
comma
id|abbrev
ques
c_cond
id|find_unique_abbrev
c_func
(paren
id|ce-&gt;sha1
comma
id|abbrev
)paren
suffix:colon
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
comma
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
suffix:semicolon
)brace
id|write_name_quoted
c_func
(paren
id|ce-&gt;name
op_plus
id|offset
comma
id|stdout
comma
id|line_terminator
)paren
suffix:semicolon
)brace
DECL|function|show_files
r_static
r_void
id|show_files
c_func
(paren
r_struct
id|dir_struct
op_star
id|dir
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* For cached/deleted files we don&squot;t need to even do the readdir */
r_if
c_cond
(paren
id|show_others
op_logical_or
id|show_killed
)paren
(brace
r_const
r_char
op_star
id|path
op_assign
l_string|&quot;.&quot;
comma
op_star
id|base
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
id|baselen
op_assign
id|prefix_len
suffix:semicolon
r_if
c_cond
(paren
id|baselen
)paren
id|path
op_assign
id|base
op_assign
id|prefix
suffix:semicolon
id|read_directory
c_func
(paren
id|dir
comma
id|path
comma
id|base
comma
id|baselen
comma
id|pathspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_others
)paren
id|show_other_files
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_killed
)paren
id|show_killed_files
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|show_cached
op_or
id|show_stage
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|active_nr
suffix:semicolon
id|i
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
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|excluded
c_func
(paren
id|dir
comma
id|ce-&gt;name
)paren
op_ne
id|dir-&gt;show_ignored
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|show_unmerged
op_logical_and
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ce-&gt;ce_flags
op_amp
id|htons
c_func
(paren
id|CE_UPDATE
)paren
)paren
r_continue
suffix:semicolon
id|show_ce_entry
c_func
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
ques
c_cond
id|tag_unmerged
suffix:colon
id|tag_cached
comma
id|ce
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|show_deleted
op_or
id|show_modified
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|active_nr
suffix:semicolon
id|i
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
id|i
)braket
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|excluded
c_func
(paren
id|dir
comma
id|ce-&gt;name
)paren
op_ne
id|dir-&gt;show_ignored
)paren
r_continue
suffix:semicolon
id|err
op_assign
id|lstat
c_func
(paren
id|ce-&gt;name
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_deleted
op_logical_and
id|err
)paren
id|show_ce_entry
c_func
(paren
id|tag_removed
comma
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|show_modified
op_logical_and
id|ce_modified
c_func
(paren
id|ce
comma
op_amp
id|st
comma
l_int|0
)paren
)paren
id|show_ce_entry
c_func
(paren
id|tag_modified
comma
id|ce
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Prune the index to only contain stuff starting with &quot;prefix&quot;&n; */
DECL|function|prune_cache
r_static
r_void
id|prune_cache
c_func
(paren
r_const
r_char
op_star
id|prefix
)paren
(brace
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|prefix
comma
id|prefix_len
)paren
suffix:semicolon
r_int
r_int
id|first
comma
id|last
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
id|pos
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
id|memmove
c_func
(paren
id|active_cache
comma
id|active_cache
op_plus
id|pos
comma
(paren
id|active_nr
id|pos
)paren
op_star
r_sizeof
(paren
r_struct
id|cache_entry
op_star
)paren
)paren
suffix:semicolon
id|active_nr
op_sub_assign
id|pos
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
id|last
op_assign
id|active_nr
suffix:semicolon
r_while
c_loop
(paren
id|last
OG
id|first
)paren
(brace
r_int
id|next
op_assign
(paren
id|last
op_plus
id|first
)paren
op_rshift
l_int|1
suffix:semicolon
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|next
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|ce-&gt;name
comma
id|prefix
comma
id|prefix_len
)paren
)paren
(brace
id|first
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|last
op_assign
id|next
suffix:semicolon
)brace
id|active_nr
op_assign
id|last
suffix:semicolon
)brace
DECL|function|verify_pathspec
r_static
r_const
r_char
op_star
id|verify_pathspec
c_func
(paren
r_const
r_char
op_star
id|prefix
)paren
(brace
r_const
r_char
op_star
op_star
id|p
comma
op_star
id|n
comma
op_star
id|prev
suffix:semicolon
r_int
r_int
id|max
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|max
op_assign
id|PATH_MAX
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|pathspec
suffix:semicolon
(paren
id|n
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_increment
)paren
(brace
r_int
id|i
comma
id|len
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c
op_assign
id|n
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_logical_and
id|prev
(braket
id|i
)braket
op_ne
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
op_logical_or
id|c
op_eq
l_char|&squot;*&squot;
op_logical_or
id|c
op_eq
l_char|&squot;?&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;/&squot;
)paren
id|len
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
)brace
id|prev
op_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|max
)paren
(brace
id|max
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|max
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|prefix_offset
OG
id|max
op_logical_or
id|memcmp
c_func
(paren
id|prev
comma
id|prefix
comma
id|prefix_offset
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git-ls-files: cannot generate relative filenames containing &squot;..&squot;&quot;
)paren
suffix:semicolon
id|prefix_len
op_assign
id|max
suffix:semicolon
r_return
id|max
ques
c_cond
id|xmemdupz
c_func
(paren
id|prev
comma
id|max
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the tree specified with --with-tree option&n; * (typically, HEAD) into stage #1 and then&n; * squash them down to stage #0.  This is used for&n; * --error-unmatch to list and check the path patterns&n; * that were given from the command line.  We are not&n; * going to write this index out.&n; */
DECL|function|overlay_tree_on_cache
r_void
id|overlay_tree_on_cache
c_func
(paren
r_const
r_char
op_star
id|tree_name
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|tree
op_star
id|tree
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
op_star
id|match
suffix:semicolon
r_struct
id|cache_entry
op_star
id|last_stage0
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|tree_name
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;tree-ish %s not found.&quot;
comma
id|tree_name
)paren
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tree
)paren
id|die
c_func
(paren
l_string|&quot;bad tree-ish %s&quot;
comma
id|tree_name
)paren
suffix:semicolon
multiline_comment|/* Hoist the unmerged entries up to stage #3 to make room */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|active_nr
suffix:semicolon
id|i
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
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
r_continue
suffix:semicolon
id|ce-&gt;ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_STAGEMASK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prefix
)paren
(brace
r_static
r_const
r_char
op_star
(paren
id|matchbuf
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|matchbuf
(braket
l_int|0
)braket
op_assign
id|prefix
suffix:semicolon
id|matchbuf
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|match
op_assign
id|matchbuf
suffix:semicolon
)brace
r_else
id|match
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|read_tree
c_func
(paren
id|tree
comma
l_int|1
comma
id|match
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to read tree entries %s&quot;
comma
id|tree_name
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
id|active_nr
suffix:semicolon
id|i
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
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|last_stage0
op_assign
id|ce
suffix:semicolon
multiline_comment|/* fallthru */
r_default
suffix:colon
r_continue
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * If there is stage #0 entry for this, we do not&n;&t;&t;&t; * need to show it.  We use CE_UPDATE bit to mark&n;&t;&t;&t; * such an entry.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|last_stage0
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|last_stage0-&gt;name
comma
id|ce-&gt;name
)paren
)paren
id|ce-&gt;ce_flags
op_or_assign
id|htons
c_func
(paren
id|CE_UPDATE
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|report_path_error
r_int
id|report_path_error
c_func
(paren
r_const
r_char
op_star
id|ps_matched
comma
r_const
r_char
op_star
op_star
id|pathspec
comma
r_int
id|prefix_offset
)paren
(brace
multiline_comment|/*&n;&t; * Make sure all pathspec matched; otherwise it is an error.&n;&t; */
r_int
id|num
comma
id|errors
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|num
)braket
suffix:semicolon
id|num
op_increment
)paren
(brace
r_int
id|other
comma
id|found_dup
suffix:semicolon
r_if
c_cond
(paren
id|ps_matched
(braket
id|num
)braket
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The caller might have fed identical pathspec&n;&t;&t; * twice.  Do not barf on such a mistake.&n;&t;&t; */
r_for
c_loop
(paren
id|found_dup
op_assign
id|other
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|found_dup
op_logical_and
id|pathspec
(braket
id|other
)braket
suffix:semicolon
id|other
op_increment
)paren
(brace
r_if
c_cond
(paren
id|other
op_eq
id|num
op_logical_or
op_logical_neg
id|ps_matched
(braket
id|other
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|pathspec
(braket
id|other
)braket
comma
id|pathspec
(braket
id|num
)braket
)paren
)paren
multiline_comment|/*&n;&t;&t;&t;&t; * Ok, we have a match already.&n;&t;&t;&t;&t; */
id|found_dup
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found_dup
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; did not match any file(s) known to git.&quot;
comma
id|pathspec
(braket
id|num
)braket
op_plus
id|prefix_offset
)paren
suffix:semicolon
id|errors
op_increment
suffix:semicolon
)brace
r_return
id|errors
suffix:semicolon
)brace
DECL|variable|ls_files_usage
r_static
r_const
r_char
id|ls_files_usage
(braket
)braket
op_assign
l_string|&quot;git-ls-files [-z] [-t] [-v] (--[cached|deleted|others|stage|unmerged|killed|modified])* &quot;
l_string|&quot;[ --ignored ] [--exclude=&lt;pattern&gt;] [--exclude-from=&lt;file&gt;] &quot;
l_string|&quot;[ --exclude-per-directory=&lt;filename&gt; ] [--exclude-standard] &quot;
l_string|&quot;[--full-name] [--abbrev] [--] [&lt;file&gt;]*&quot;
suffix:semicolon
DECL|function|cmd_ls_files
r_int
id|cmd_ls_files
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
suffix:semicolon
r_int
id|exc_given
op_assign
l_int|0
comma
id|require_work_tree
op_assign
l_int|0
suffix:semicolon
r_struct
id|dir_struct
id|dir
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dir
comma
l_int|0
comma
r_sizeof
(paren
id|dir
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
id|prefix_offset
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
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
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
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
id|arg
comma
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_terminator
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
id|arg
comma
l_string|&quot;-t&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|tag_cached
op_assign
l_string|&quot;H &quot;
suffix:semicolon
id|tag_unmerged
op_assign
l_string|&quot;M &quot;
suffix:semicolon
id|tag_removed
op_assign
l_string|&quot;R &quot;
suffix:semicolon
id|tag_modified
op_assign
l_string|&quot;C &quot;
suffix:semicolon
id|tag_other
op_assign
l_string|&quot;? &quot;
suffix:semicolon
id|tag_killed
op_assign
l_string|&quot;K &quot;
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|1
)braket
op_eq
l_char|&squot;v&squot;
)paren
id|show_valid_bit
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
id|arg
comma
l_string|&quot;-c&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--cached&quot;
)paren
)paren
(brace
id|show_cached
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
id|arg
comma
l_string|&quot;-d&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--deleted&quot;
)paren
)paren
(brace
id|show_deleted
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
id|arg
comma
l_string|&quot;-m&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--modified&quot;
)paren
)paren
(brace
id|show_modified
op_assign
l_int|1
suffix:semicolon
id|require_work_tree
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
id|arg
comma
l_string|&quot;-o&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--others&quot;
)paren
)paren
(brace
id|show_others
op_assign
l_int|1
suffix:semicolon
id|require_work_tree
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
id|arg
comma
l_string|&quot;-i&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--ignored&quot;
)paren
)paren
(brace
id|dir.show_ignored
op_assign
l_int|1
suffix:semicolon
id|require_work_tree
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
id|arg
comma
l_string|&quot;-s&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stage&quot;
)paren
)paren
(brace
id|show_stage
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
id|arg
comma
l_string|&quot;-k&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--killed&quot;
)paren
)paren
(brace
id|show_killed
op_assign
l_int|1
suffix:semicolon
id|require_work_tree
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
id|arg
comma
l_string|&quot;--directory&quot;
)paren
)paren
(brace
id|dir.show_other_directories
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
id|arg
comma
l_string|&quot;--no-empty-directory&quot;
)paren
)paren
(brace
id|dir.hide_empty_directories
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
id|arg
comma
l_string|&quot;-u&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--unmerged&quot;
)paren
)paren
(brace
multiline_comment|/* There&squot;s no point in showing unmerged unless&n;&t;&t;&t; * you also show the stage information.&n;&t;&t;&t; */
id|show_stage
op_assign
l_int|1
suffix:semicolon
id|show_unmerged
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
id|arg
comma
l_string|&quot;-x&quot;
)paren
op_logical_and
id|i
op_plus
l_int|1
OL
id|argc
)paren
(brace
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|add_exclude
c_func
(paren
id|argv
(braket
op_increment
id|i
)braket
comma
l_string|&quot;&quot;
comma
l_int|0
comma
op_amp
id|dir.exclude_list
(braket
id|EXC_CMDL
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exclude=&quot;
)paren
)paren
(brace
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|add_exclude
c_func
(paren
id|arg
op_plus
l_int|10
comma
l_string|&quot;&quot;
comma
l_int|0
comma
op_amp
id|dir.exclude_list
(braket
id|EXC_CMDL
)braket
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
id|arg
comma
l_string|&quot;-X&quot;
)paren
op_logical_and
id|i
op_plus
l_int|1
OL
id|argc
)paren
(brace
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|add_excludes_from_file
c_func
(paren
op_amp
id|dir
comma
id|argv
(braket
op_increment
id|i
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exclude-from=&quot;
)paren
)paren
(brace
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|add_excludes_from_file
c_func
(paren
op_amp
id|dir
comma
id|arg
op_plus
l_int|15
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exclude-per-directory=&quot;
)paren
)paren
(brace
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|dir.exclude_per_dir
op_assign
id|arg
op_plus
l_int|24
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
id|arg
comma
l_string|&quot;--exclude-standard&quot;
)paren
)paren
(brace
id|exc_given
op_assign
l_int|1
suffix:semicolon
id|setup_standard_excludes
c_func
(paren
op_amp
id|dir
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
id|arg
comma
l_string|&quot;--full-name&quot;
)paren
)paren
(brace
id|prefix_offset
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
id|arg
comma
l_string|&quot;--error-unmatch&quot;
)paren
)paren
(brace
id|error_unmatch
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--with-tree=&quot;
)paren
)paren
(brace
id|with_tree
op_assign
id|arg
op_plus
l_int|12
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--abbrev=&quot;
)paren
)paren
(brace
id|abbrev
op_assign
id|strtoul
c_func
(paren
id|arg
op_plus
l_int|9
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|abbrev
op_logical_and
id|abbrev
OL
id|MINIMUM_ABBREV
)paren
id|abbrev
op_assign
id|MINIMUM_ABBREV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|abbrev
OG
l_int|40
)paren
id|abbrev
op_assign
l_int|40
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
id|arg
comma
l_string|&quot;--abbrev&quot;
)paren
)paren
(brace
id|abbrev
op_assign
id|DEFAULT_ABBREV
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|ls_files_usage
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|require_work_tree
op_logical_and
op_logical_neg
id|is_inside_work_tree
c_func
(paren
)paren
)paren
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
id|pathspec
op_assign
id|get_pathspec
c_func
(paren
id|prefix
comma
id|argv
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Verify that the pathspec matches the prefix */
r_if
c_cond
(paren
id|pathspec
)paren
id|prefix
op_assign
id|verify_pathspec
c_func
(paren
id|prefix
)paren
suffix:semicolon
multiline_comment|/* Treat unmatching pathspec elements as errors */
r_if
c_cond
(paren
id|pathspec
op_logical_and
id|error_unmatch
)paren
(brace
r_int
id|num
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|pathspec
(braket
id|num
)braket
suffix:semicolon
id|num
op_increment
)paren
suffix:semicolon
id|ps_matched
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
id|num
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir.show_ignored
op_logical_and
op_logical_neg
id|exc_given
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: --ignored needs some exclude pattern&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* With no flags, we default to showing the cached files */
r_if
c_cond
(paren
op_logical_neg
(paren
id|show_stage
op_or
id|show_deleted
op_or
id|show_others
op_or
id|show_unmerged
op_or
id|show_killed
op_or
id|show_modified
)paren
)paren
id|show_cached
op_assign
l_int|1
suffix:semicolon
id|read_cache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
)paren
id|prune_cache
c_func
(paren
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|with_tree
)paren
(brace
multiline_comment|/*&n;&t;&t; * Basic sanity check; show-stages and show-unmerged&n;&t;&t; * would not make any sense with this option.&n;&t;&t; */
r_if
c_cond
(paren
id|show_stage
op_logical_or
id|show_unmerged
)paren
id|die
c_func
(paren
l_string|&quot;ls-files --with-tree is incompatible with -s or -u&quot;
)paren
suffix:semicolon
id|overlay_tree_on_cache
c_func
(paren
id|with_tree
comma
id|prefix
)paren
suffix:semicolon
)brace
id|show_files
c_func
(paren
op_amp
id|dir
comma
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ps_matched
)paren
(brace
r_int
id|bad
suffix:semicolon
id|bad
op_assign
id|report_path_error
c_func
(paren
id|ps_matched
comma
id|pathspec
comma
id|prefix_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bad
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Did you forget to &squot;git add&squot;?&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|bad
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
