multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &lt;limits.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;diff.h&quot;
DECL|function|matches_pathspec
r_static
r_int
id|matches_pathspec
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
op_star
id|spec
comma
r_int
id|cnt
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
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
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|speclen
op_assign
id|strlen
c_func
(paren
id|spec
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|spec
(braket
id|i
)braket
comma
id|name
comma
id|speclen
)paren
op_logical_and
id|speclen
op_le
id|namelen
op_logical_and
(paren
id|name
(braket
id|speclen
)braket
op_eq
l_int|0
op_logical_or
id|name
(braket
id|speclen
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|detect_rename
r_static
r_int
id|detect_rename
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * We do not detect circular renames.  Just hold created and deleted&n; * entries and later attempt to match them up.  If they do not match,&n; * then spit them out as deletes or creates as original.&n; */
DECL|struct|diff_spec_hold
r_static
r_struct
id|diff_spec_hold
(brace
DECL|member|next
r_struct
id|diff_spec_hold
op_star
id|next
suffix:semicolon
DECL|member|matched
r_struct
id|diff_spec_hold
op_star
id|matched
suffix:semicolon
DECL|member|old
DECL|member|new
r_struct
id|diff_spec
id|old
comma
r_new
suffix:semicolon
DECL|member|path
r_char
id|path
(braket
l_int|1
)braket
suffix:semicolon
DECL|variable|createdfile
DECL|variable|deletedfile
)brace
op_star
id|createdfile
comma
op_star
id|deletedfile
suffix:semicolon
DECL|function|hold_spec
r_static
r_void
id|hold_spec
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|diff_spec
op_star
id|old
comma
r_struct
id|diff_spec
op_star
r_new
)paren
(brace
r_struct
id|diff_spec_hold
op_star
op_star
id|list
comma
op_star
id|elem
suffix:semicolon
id|list
op_assign
(paren
op_logical_neg
id|old-&gt;file_valid
)paren
ques
c_cond
op_amp
id|createdfile
suffix:colon
op_amp
id|deletedfile
suffix:semicolon
id|elem
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|elem
)paren
op_plus
id|strlen
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|elem-&gt;path
comma
id|path
)paren
suffix:semicolon
id|elem-&gt;next
op_assign
op_star
id|list
suffix:semicolon
op_star
id|list
op_assign
id|elem
suffix:semicolon
id|elem-&gt;old
op_assign
op_star
id|old
suffix:semicolon
id|elem
op_member_access_from_pointer
r_new
op_assign
op_star
r_new
suffix:semicolon
id|elem-&gt;matched
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|MINIMUM_SCORE
mdefine_line|#define MINIMUM_SCORE 7000
DECL|function|estimate_similarity
r_int
id|estimate_similarity
c_func
(paren
r_struct
id|diff_spec
op_star
id|one
comma
r_struct
id|diff_spec
op_star
id|two
)paren
(brace
multiline_comment|/* Return how similar they are, representing the score as an&n;&t; * integer between 0 and 10000.&n;&t; *&n;&t; * This version is very dumb and detects exact matches only.&n;&t; * Wnen Nico&squot;s delta stuff gets in, I&squot;ll use the delta&n;&t; * algorithm to estimate the similarity score in core.&n;&t; */
r_if
c_cond
(paren
id|one-&gt;sha1_valid
op_logical_and
id|two-&gt;sha1_valid
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|one-&gt;blob_sha1
comma
id|two-&gt;blob_sha1
comma
l_int|20
)paren
)paren
r_return
l_int|10000
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flush_renames
r_static
r_void
id|flush_renames
c_func
(paren
r_const
r_char
op_star
op_star
id|spec
comma
r_int
id|cnt
comma
r_int
id|reverse
)paren
(brace
r_struct
id|diff_spec_hold
op_star
id|rename_src
comma
op_star
id|rename_dst
comma
op_star
id|elem
suffix:semicolon
r_struct
id|diff_spec_hold
op_star
id|leftover
op_assign
l_int|NULL
suffix:semicolon
r_int
id|score
comma
id|best_score
suffix:semicolon
r_while
c_loop
(paren
id|createdfile
)paren
(brace
id|rename_dst
op_assign
id|createdfile
suffix:semicolon
id|createdfile
op_assign
id|rename_dst-&gt;next
suffix:semicolon
id|best_score
op_assign
id|MINIMUM_SCORE
suffix:semicolon
id|rename_src
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|elem
op_assign
id|deletedfile
suffix:semicolon
id|elem
suffix:semicolon
id|elem
op_assign
id|elem-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|elem-&gt;matched
)paren
r_continue
suffix:semicolon
id|score
op_assign
id|estimate_similarity
c_func
(paren
op_amp
id|elem-&gt;old
comma
op_amp
id|rename_dst
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|best_score
OL
id|score
)paren
(brace
id|rename_src
op_assign
id|elem
suffix:semicolon
id|best_score
op_assign
id|score
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rename_src
)paren
(brace
id|rename_src-&gt;matched
op_assign
id|rename_dst
suffix:semicolon
id|rename_dst-&gt;matched
op_assign
id|rename_src
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cnt
op_logical_or
id|matches_pathspec
c_func
(paren
id|rename_src-&gt;path
comma
id|spec
comma
id|cnt
)paren
op_logical_or
id|matches_pathspec
c_func
(paren
id|rename_dst-&gt;path
comma
id|spec
comma
id|cnt
)paren
)paren
(brace
r_if
c_cond
(paren
id|reverse
)paren
id|run_external_diff
c_func
(paren
id|rename_dst-&gt;path
comma
id|rename_src-&gt;path
comma
op_amp
id|rename_dst
op_member_access_from_pointer
r_new
comma
op_amp
id|rename_src-&gt;old
)paren
suffix:semicolon
r_else
id|run_external_diff
c_func
(paren
id|rename_src-&gt;path
comma
id|rename_dst-&gt;path
comma
op_amp
id|rename_src-&gt;old
comma
op_amp
id|rename_dst
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|rename_dst-&gt;next
op_assign
id|leftover
suffix:semicolon
id|leftover
op_assign
id|rename_dst
suffix:semicolon
)brace
)brace
multiline_comment|/* unmatched deletes */
r_for
c_loop
(paren
id|elem
op_assign
id|deletedfile
suffix:semicolon
id|elem
suffix:semicolon
id|elem
op_assign
id|elem-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|elem-&gt;matched
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cnt
op_logical_or
id|matches_pathspec
c_func
(paren
id|elem-&gt;path
comma
id|spec
comma
id|cnt
)paren
)paren
(brace
r_if
c_cond
(paren
id|reverse
)paren
id|run_external_diff
c_func
(paren
id|elem-&gt;path
comma
l_int|NULL
comma
op_amp
id|elem
op_member_access_from_pointer
r_new
comma
op_amp
id|elem-&gt;old
)paren
suffix:semicolon
r_else
id|run_external_diff
c_func
(paren
id|elem-&gt;path
comma
l_int|NULL
comma
op_amp
id|elem-&gt;old
comma
op_amp
id|elem
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* unmatched creates */
r_for
c_loop
(paren
id|elem
op_assign
id|leftover
suffix:semicolon
id|elem
suffix:semicolon
id|elem
op_assign
id|elem-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cnt
op_logical_or
id|matches_pathspec
c_func
(paren
id|elem-&gt;path
comma
id|spec
comma
id|cnt
)paren
)paren
(brace
r_if
c_cond
(paren
id|reverse
)paren
id|run_external_diff
c_func
(paren
id|elem-&gt;path
comma
l_int|NULL
comma
op_amp
id|elem
op_member_access_from_pointer
r_new
comma
op_amp
id|elem-&gt;old
)paren
suffix:semicolon
r_else
id|run_external_diff
c_func
(paren
id|elem-&gt;path
comma
l_int|NULL
comma
op_amp
id|elem-&gt;old
comma
op_amp
id|elem
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|parse_oneside_change
r_static
r_int
id|parse_oneside_change
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_struct
id|diff_spec
op_star
id|one
comma
r_char
op_star
id|path
)paren
(brace
r_int
id|ch
suffix:semicolon
id|one-&gt;file_valid
op_assign
id|one-&gt;sha1_valid
op_assign
l_int|1
suffix:semicolon
id|one-&gt;mode
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_logical_and
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;7&squot;
)paren
(brace
id|one-&gt;mode
op_assign
(paren
id|one-&gt;mode
op_lshift
l_int|3
)paren
op_or
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;&bslash;tblob&bslash;t&quot;
comma
l_int|6
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|cp
comma
id|one-&gt;blob_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_diff_raw_output
r_static
r_int
id|parse_diff_raw_output
c_func
(paren
r_const
r_char
op_star
id|buf
comma
r_const
r_char
op_star
op_star
id|spec
comma
r_int
id|cnt
comma
r_int
id|reverse
)paren
(brace
r_struct
id|diff_spec
id|old
comma
r_new
suffix:semicolon
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|cp
op_assign
id|buf
suffix:semicolon
r_int
id|ch
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|cp
op_increment
)paren
(brace
r_case
l_char|&squot;U&squot;
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|cnt
op_logical_or
id|matches_pathspec
c_func
(paren
id|cp
op_plus
l_int|1
comma
id|spec
comma
id|cnt
)paren
)paren
id|diff_unmerge
c_func
(paren
id|cp
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|old.file_valid
op_assign
l_int|0
suffix:semicolon
id|parse_oneside_change
c_func
(paren
id|cp
comma
op_amp
r_new
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
r_new
dot
id|file_valid
op_assign
l_int|0
suffix:semicolon
id|parse_oneside_change
c_func
(paren
id|cp
comma
op_amp
id|old
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;*&squot;
suffix:colon
id|old.file_valid
op_assign
id|old.sha1_valid
op_assign
r_new
dot
id|file_valid
op_assign
r_new
dot
id|sha1_valid
op_assign
l_int|1
suffix:semicolon
id|old.mode
op_assign
r_new
dot
id|mode
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_logical_and
(paren
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;7&squot;
)paren
)paren
(brace
id|old.mode
op_assign
(paren
id|old.mode
op_lshift
l_int|3
)paren
op_or
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;-&gt;&quot;
comma
l_int|2
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_logical_and
(paren
l_char|&squot;0&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;7&squot;
)paren
)paren
(brace
r_new
dot
id|mode
op_assign
(paren
r_new
dot
id|mode
op_lshift
l_int|3
)paren
op_or
(paren
id|ch
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;&bslash;tblob&bslash;t&quot;
comma
l_int|6
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|cp
comma
id|old.blob_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|cp
comma
l_string|&quot;-&gt;&quot;
comma
l_int|2
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|cp
comma
r_new
dot
id|blob_sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|cp
op_add_assign
l_int|40
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot;&bslash;t&squot;
)paren
r_return
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|path
comma
id|cp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|detect_rename
op_logical_and
id|old.file_valid
op_ne
r_new
dot
id|file_valid
)paren
(brace
multiline_comment|/* hold these */
id|hold_spec
c_func
(paren
id|path
comma
op_amp
id|old
comma
op_amp
r_new
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cnt
op_logical_or
id|matches_pathspec
c_func
(paren
id|path
comma
id|spec
comma
id|cnt
)paren
)paren
(brace
r_if
c_cond
(paren
id|reverse
)paren
id|run_external_diff
c_func
(paren
id|path
comma
l_int|NULL
comma
op_amp
r_new
comma
op_amp
id|old
)paren
suffix:semicolon
r_else
id|run_external_diff
c_func
(paren
id|path
comma
l_int|NULL
comma
op_amp
id|old
comma
op_amp
r_new
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|diff_helper_usage
r_static
r_const
r_char
op_star
id|diff_helper_usage
op_assign
l_string|&quot;git-diff-helper [-r] [-R] [-z] paths...&quot;
suffix:semicolon
DECL|function|main
r_int
id|main
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
)paren
(brace
r_struct
id|strbuf
id|sb
suffix:semicolon
r_int
id|reverse
op_assign
l_int|0
suffix:semicolon
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
OL
id|ac
op_logical_and
id|av
(braket
l_int|1
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|av
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;R&squot;
)paren
id|reverse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|av
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;z&squot;
)paren
id|line_termination
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|av
(braket
l_int|1
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;r&squot;
)paren
id|detect_rename
op_assign
l_int|1
suffix:semicolon
r_else
id|usage
c_func
(paren
id|diff_helper_usage
)paren
suffix:semicolon
id|ac
op_decrement
suffix:semicolon
id|av
op_increment
suffix:semicolon
)brace
multiline_comment|/* the remaining parameters are paths patterns */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|status
suffix:semicolon
id|read_line
c_func
(paren
op_amp
id|sb
comma
id|stdin
comma
id|line_termination
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb.eof
)paren
r_break
suffix:semicolon
id|status
op_assign
id|parse_diff_raw_output
c_func
(paren
id|sb.buf
comma
id|av
op_plus
l_int|1
comma
id|ac
op_minus
l_int|1
comma
id|reverse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot parse %s&bslash;n&quot;
comma
id|sb.buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|detect_rename
)paren
id|flush_renames
c_func
(paren
id|av
op_plus
l_int|1
comma
id|ac
op_minus
l_int|1
comma
id|reverse
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
