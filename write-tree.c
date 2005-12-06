multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
DECL|variable|missing_ok
r_static
r_int
id|missing_ok
op_assign
l_int|0
suffix:semicolon
DECL|function|check_valid_sha1
r_static
r_int
id|check_valid_sha1
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* If we were anal, we&squot;d check that the sha1 of the contents actually matches */
id|ret
op_assign
id|has_sha1_file
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|perror
c_func
(paren
id|sha1_file_name
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
id|ret
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|write_tree
r_static
r_int
id|write_tree
c_func
(paren
r_struct
id|cache_entry
op_star
op_star
id|cachep
comma
r_int
id|maxentries
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_int
r_char
op_star
id|returnsha1
)paren
(brace
r_int
r_char
id|subdir_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
r_int
id|size
comma
id|offset
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|nr
suffix:semicolon
multiline_comment|/* Guess at some random initial size */
id|size
op_assign
l_int|8192
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|nr
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|nr
OL
id|maxentries
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|cachep
(braket
id|nr
)braket
suffix:semicolon
r_const
r_char
op_star
id|pathname
op_assign
id|ce-&gt;name
comma
op_star
id|filename
comma
op_star
id|dirname
suffix:semicolon
r_int
id|pathlen
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
comma
id|entrylen
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* Did we hit the end of the directory? Return how many we wrote */
r_if
c_cond
(paren
id|baselen
op_ge
id|pathlen
op_logical_or
id|memcmp
c_func
(paren
id|base
comma
id|pathname
comma
id|baselen
)paren
)paren
r_break
suffix:semicolon
id|sha1
op_assign
id|ce-&gt;sha1
suffix:semicolon
id|mode
op_assign
id|ntohl
c_func
(paren
id|ce-&gt;ce_mode
)paren
suffix:semicolon
multiline_comment|/* Do we have _further_ subdirectories? */
id|filename
op_assign
id|pathname
op_plus
id|baselen
suffix:semicolon
id|dirname
op_assign
id|strchr
c_func
(paren
id|filename
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dirname
)paren
(brace
r_int
id|subdir_written
suffix:semicolon
id|subdir_written
op_assign
id|write_tree
c_func
(paren
id|cachep
op_plus
id|nr
comma
id|maxentries
id|nr
comma
id|pathname
comma
id|dirname
op_minus
id|pathname
op_plus
l_int|1
comma
id|subdir_sha1
)paren
suffix:semicolon
id|nr
op_add_assign
id|subdir_written
suffix:semicolon
multiline_comment|/* Now we need to write out the directory entry into this tree.. */
id|mode
op_assign
id|S_IFDIR
suffix:semicolon
id|pathlen
op_assign
id|dirname
id|pathname
suffix:semicolon
multiline_comment|/* ..but the directory entry doesn&squot;t count towards the total count */
id|nr
op_decrement
suffix:semicolon
id|sha1
op_assign
id|subdir_sha1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|missing_ok
op_logical_and
id|check_valid_sha1
c_func
(paren
id|sha1
)paren
OL
l_int|0
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
id|entrylen
op_assign
id|pathlen
id|baselen
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_plus
id|entrylen
op_plus
l_int|100
OG
id|size
)paren
(brace
id|size
op_assign
id|alloc_nr
c_func
(paren
id|offset
op_plus
id|entrylen
op_plus
l_int|100
)paren
suffix:semicolon
id|buffer
op_assign
id|xrealloc
c_func
(paren
id|buffer
comma
id|size
)paren
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|offset
comma
l_string|&quot;%o %.*s&quot;
comma
id|mode
comma
id|entrylen
comma
id|filename
)paren
suffix:semicolon
id|buffer
(braket
id|offset
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
op_plus
id|offset
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|20
suffix:semicolon
id|nr
op_increment
suffix:semicolon
)brace
id|write_sha1_file
c_func
(paren
id|buffer
comma
id|offset
comma
l_string|&quot;tree&quot;
comma
id|returnsha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
DECL|variable|write_tree_usage
r_static
r_const
r_char
id|write_tree_usage
(braket
)braket
op_assign
l_string|&quot;git-write-tree [--missing-ok]&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
comma
id|funny
suffix:semicolon
r_int
id|entries
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|setup_git_directory
c_func
(paren
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
id|argc
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--missing-ok&quot;
)paren
)paren
id|missing_ok
op_assign
l_int|1
suffix:semicolon
r_else
id|die
c_func
(paren
id|write_tree_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OG
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;too many options&quot;
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
l_string|&quot;git-write-tree: error reading cache&quot;
)paren
suffix:semicolon
multiline_comment|/* Verify that the tree is merged */
id|funny
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
id|entries
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
id|ntohs
c_func
(paren
id|ce-&gt;ce_flags
)paren
op_amp
op_complement
id|CE_NAMEMASK
)paren
(brace
r_if
c_cond
(paren
l_int|10
OL
op_increment
id|funny
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: unmerged (%s)&bslash;n&quot;
comma
id|ce-&gt;name
comma
id|sha1_to_hex
c_func
(paren
id|ce-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|funny
)paren
id|die
c_func
(paren
l_string|&quot;git-write-tree: not able to write tree&quot;
)paren
suffix:semicolon
multiline_comment|/* Also verify that the cache does not have path and path/file&n;&t; * at the same time.  At this point we know the cache has only&n;&t; * stage 0 entries.&n;&t; */
id|funny
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
id|entries
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* path/file always comes after path because of the way&n;&t;&t; * the cache is sorted.  Also path can appear only once,&n;&t;&t; * which means conflicting one would immediately follow.&n;&t;&t; */
r_const
r_char
op_star
id|this_name
op_assign
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
r_const
r_char
op_star
id|next_name
op_assign
id|active_cache
(braket
id|i
op_plus
l_int|1
)braket
op_member_access_from_pointer
id|name
suffix:semicolon
r_int
id|this_len
op_assign
id|strlen
c_func
(paren
id|this_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|this_len
OL
id|strlen
c_func
(paren
id|next_name
)paren
op_logical_and
id|strncmp
c_func
(paren
id|this_name
comma
id|next_name
comma
id|this_len
)paren
op_eq
l_int|0
op_logical_and
id|next_name
(braket
id|this_len
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
l_int|10
OL
op_increment
id|funny
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;You have both %s and %s&bslash;n&quot;
comma
id|this_name
comma
id|next_name
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|funny
)paren
id|die
c_func
(paren
l_string|&quot;git-write-tree: not able to write tree&quot;
)paren
suffix:semicolon
multiline_comment|/* Ok, write it out */
r_if
c_cond
(paren
id|write_tree
c_func
(paren
id|active_cache
comma
id|entries
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|sha1
)paren
op_ne
id|entries
)paren
id|die
c_func
(paren
l_string|&quot;git-write-tree: internal error&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
