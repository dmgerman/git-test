multiline_comment|/*&n; * Builtin &quot;git branch&quot;&n; *&n; * Copyright (c) 2006 Kristian H&oslash;gsberg &lt;krh@redhat.com&gt;&n; * Based on git-branch.sh by Junio C Hamano.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;color.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;branch.h&quot;
DECL|variable|builtin_branch_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_branch_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git branch [options] [-r | -a] [--merged | --no-merged]&quot;
comma
l_string|&quot;git branch [options] [-l] [-f] &lt;branchname&gt; [&lt;start-point&gt;]&quot;
comma
l_string|&quot;git branch [options] [-r] (-d | -D) &lt;branchname&gt;&quot;
comma
l_string|&quot;git branch [options] (-m | -M) [&lt;oldbranch&gt;] &lt;newbranch&gt;&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|macro|REF_UNKNOWN_TYPE
mdefine_line|#define REF_UNKNOWN_TYPE    0x00
DECL|macro|REF_LOCAL_BRANCH
mdefine_line|#define REF_LOCAL_BRANCH    0x01
DECL|macro|REF_REMOTE_BRANCH
mdefine_line|#define REF_REMOTE_BRANCH   0x02
DECL|macro|REF_TAG
mdefine_line|#define REF_TAG             0x04
DECL|variable|head
r_static
r_const
r_char
op_star
id|head
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
DECL|variable|branch_use_color
r_static
r_int
id|branch_use_color
op_assign
l_int|1
suffix:semicolon
DECL|variable|branch_colors
r_static
r_char
id|branch_colors
(braket
)braket
(braket
id|COLOR_MAXLEN
)braket
op_assign
(brace
l_string|&quot;&bslash;033[m&quot;
comma
multiline_comment|/* reset */
l_string|&quot;&quot;
comma
multiline_comment|/* PLAIN (normal) */
l_string|&quot;&bslash;033[31m&quot;
comma
multiline_comment|/* REMOTE (red) */
l_string|&quot;&quot;
comma
multiline_comment|/* LOCAL (normal) */
l_string|&quot;&bslash;033[32m&quot;
comma
multiline_comment|/* CURRENT (green) */
)brace
suffix:semicolon
DECL|enum|color_branch
r_enum
id|color_branch
(brace
DECL|enumerator|COLOR_BRANCH_RESET
id|COLOR_BRANCH_RESET
op_assign
l_int|0
comma
DECL|enumerator|COLOR_BRANCH_PLAIN
id|COLOR_BRANCH_PLAIN
op_assign
l_int|1
comma
DECL|enumerator|COLOR_BRANCH_REMOTE
id|COLOR_BRANCH_REMOTE
op_assign
l_int|2
comma
DECL|enumerator|COLOR_BRANCH_LOCAL
id|COLOR_BRANCH_LOCAL
op_assign
l_int|3
comma
DECL|enumerator|COLOR_BRANCH_CURRENT
id|COLOR_BRANCH_CURRENT
op_assign
l_int|4
comma
)brace
suffix:semicolon
DECL|variable|mergefilter
r_static
r_int
id|mergefilter
op_assign
l_int|1
suffix:semicolon
DECL|function|parse_branch_color_slot
r_static
r_int
id|parse_branch_color_slot
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_int
id|ofs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|ofs
comma
l_string|&quot;plain&quot;
)paren
)paren
r_return
id|COLOR_BRANCH_PLAIN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|ofs
comma
l_string|&quot;reset&quot;
)paren
)paren
r_return
id|COLOR_BRANCH_RESET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|ofs
comma
l_string|&quot;remote&quot;
)paren
)paren
r_return
id|COLOR_BRANCH_REMOTE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|ofs
comma
l_string|&quot;local&quot;
)paren
)paren
r_return
id|COLOR_BRANCH_LOCAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|var
op_plus
id|ofs
comma
l_string|&quot;current&quot;
)paren
)paren
r_return
id|COLOR_BRANCH_CURRENT
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;bad config variable &squot;%s&squot;&quot;
comma
id|var
)paren
suffix:semicolon
)brace
DECL|function|git_branch_config
r_static
r_int
id|git_branch_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_void
op_star
id|cb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;color.branch&quot;
)paren
)paren
(brace
id|branch_use_color
op_assign
id|git_config_colorbool
c_func
(paren
id|var
comma
id|value
comma
l_int|1
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
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;color.branch.&quot;
)paren
)paren
(brace
r_int
id|slot
op_assign
id|parse_branch_color_slot
c_func
(paren
id|var
comma
l_int|13
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|color_parse
c_func
(paren
id|value
comma
id|var
comma
id|branch_colors
(braket
id|slot
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|git_color_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
DECL|function|branch_get_color
r_static
r_const
r_char
op_star
id|branch_get_color
c_func
(paren
r_enum
id|color_branch
id|ix
)paren
(brace
r_if
c_cond
(paren
id|branch_use_color
OG
l_int|0
)paren
r_return
id|branch_colors
(braket
id|ix
)braket
suffix:semicolon
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
DECL|function|delete_branches
r_static
r_int
id|delete_branches
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
r_int
id|force
comma
r_int
id|kinds
)paren
(brace
r_struct
id|commit
op_star
id|rev
comma
op_star
id|head_rev
op_assign
id|head_rev
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|fmt
comma
op_star
id|remote
suffix:semicolon
r_char
id|section
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|kinds
)paren
(brace
r_case
id|REF_REMOTE_BRANCH
suffix:colon
id|fmt
op_assign
l_string|&quot;refs/remotes/%s&quot;
suffix:semicolon
id|remote
op_assign
l_string|&quot;remote &quot;
suffix:semicolon
id|force
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_LOCAL_BRANCH
suffix:colon
id|fmt
op_assign
l_string|&quot;refs/heads/%s&quot;
suffix:semicolon
id|remote
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;cannot use -a with -d&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
(brace
id|head_rev
op_assign
id|lookup_commit_reference
c_func
(paren
id|head_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head_rev
)paren
id|die
c_func
(paren
l_string|&quot;Couldn&squot;t look up commit object for HEAD&quot;
)paren
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kinds
op_eq
id|REF_LOCAL_BRANCH
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
id|argv
(braket
id|i
)braket
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Cannot delete the branch &squot;%s&squot; &quot;
l_string|&quot;which you are currently on.&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|free
c_func
(paren
id|name
)paren
suffix:semicolon
id|name
op_assign
id|xstrdup
c_func
(paren
id|mkpath
c_func
(paren
id|fmt
comma
id|argv
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|name
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;%sbranch &squot;%s&squot; not found.&quot;
comma
id|remote
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|rev
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
id|rev
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t look up commit object for &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* This checks whether the merge bases of branch and&n;&t;&t; * HEAD contains branch -- which means that the HEAD&n;&t;&t; * contains everything in both.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|force
op_logical_and
op_logical_neg
id|in_merge_bases
c_func
(paren
id|rev
comma
op_amp
id|head_rev
comma
l_int|1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;The branch &squot;%s&squot; is not an ancestor of &quot;
l_string|&quot;your current HEAD.&bslash;n&quot;
l_string|&quot;If you are sure you want to delete it, &quot;
l_string|&quot;run &squot;git branch -D %s&squot;.&quot;
comma
id|argv
(braket
id|i
)braket
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Error deleting %sbranch &squot;%s&squot;&quot;
comma
id|remote
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;Deleted %sbranch %s.&bslash;n&quot;
comma
id|remote
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|section
comma
r_sizeof
(paren
id|section
)paren
comma
l_string|&quot;branch.%s&quot;
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_rename_section
c_func
(paren
id|section
comma
l_int|NULL
)paren
OL
l_int|0
)paren
id|warning
c_func
(paren
l_string|&quot;Update of config-file failed&quot;
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
r_return
id|ret
suffix:semicolon
)brace
DECL|struct|ref_item
r_struct
id|ref_item
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|kind
r_int
r_int
id|kind
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ref_list
r_struct
id|ref_list
(brace
DECL|member|index
DECL|member|alloc
DECL|member|maxwidth
r_int
id|index
comma
id|alloc
comma
id|maxwidth
suffix:semicolon
DECL|member|list
r_struct
id|ref_item
op_star
id|list
suffix:semicolon
DECL|member|with_commit
r_struct
id|commit_list
op_star
id|with_commit
suffix:semicolon
DECL|member|kinds
r_int
id|kinds
suffix:semicolon
)brace
suffix:semicolon
DECL|function|has_commit
r_static
r_int
id|has_commit
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_struct
id|commit_list
op_star
id|with_commit
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|with_commit
)paren
r_return
l_int|1
suffix:semicolon
id|commit
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|with_commit
)paren
(brace
r_struct
id|commit
op_star
id|other
suffix:semicolon
id|other
op_assign
id|with_commit-&gt;item
suffix:semicolon
id|with_commit
op_assign
id|with_commit-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|in_merge_bases
c_func
(paren
id|other
comma
op_amp
id|commit
comma
l_int|1
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
DECL|function|append_ref
r_static
r_int
id|append_ref
c_func
(paren
r_const
r_char
op_star
id|refname
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
id|ref_list
op_star
id|ref_list
op_assign
(paren
r_struct
id|ref_list
op_star
)paren
(paren
id|cb_data
)paren
suffix:semicolon
r_struct
id|ref_item
op_star
id|newitem
suffix:semicolon
r_int
id|kind
op_assign
id|REF_UNKNOWN_TYPE
suffix:semicolon
r_int
id|len
suffix:semicolon
r_static
r_struct
id|commit_list
id|branch
suffix:semicolon
multiline_comment|/* Detect kind */
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
(brace
id|kind
op_assign
id|REF_LOCAL_BRANCH
suffix:semicolon
id|refname
op_add_assign
l_int|11
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/remotes/&quot;
)paren
)paren
(brace
id|kind
op_assign
id|REF_REMOTE_BRANCH
suffix:semicolon
id|refname
op_add_assign
l_int|13
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refname
comma
l_string|&quot;refs/tags/&quot;
)paren
)paren
(brace
id|kind
op_assign
id|REF_TAG
suffix:semicolon
id|refname
op_add_assign
l_int|10
suffix:semicolon
)brace
multiline_comment|/* Filter with with_commit if specified */
r_if
c_cond
(paren
op_logical_neg
id|has_commit
c_func
(paren
id|sha1
comma
id|ref_list-&gt;with_commit
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t add types the caller doesn&squot;t want */
r_if
c_cond
(paren
(paren
id|kind
op_amp
id|ref_list-&gt;kinds
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mergefilter
OG
l_int|1
)paren
(brace
id|branch.item
op_assign
id|lookup_commit_reference_gently
c_func
(paren
id|sha1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|branch.item
)paren
id|die
c_func
(paren
l_string|&quot;Unable to lookup tip of branch %s&quot;
comma
id|refname
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mergefilter
op_eq
l_int|0
op_logical_and
id|has_commit
c_func
(paren
id|head_sha1
comma
op_amp
id|branch
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mergefilter
op_eq
l_int|1
op_logical_and
op_logical_neg
id|has_commit
c_func
(paren
id|head_sha1
comma
op_amp
id|branch
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Resize buffer */
r_if
c_cond
(paren
id|ref_list-&gt;index
op_ge
id|ref_list-&gt;alloc
)paren
(brace
id|ref_list-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|ref_list-&gt;alloc
)paren
suffix:semicolon
id|ref_list-&gt;list
op_assign
id|xrealloc
c_func
(paren
id|ref_list-&gt;list
comma
id|ref_list-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|ref_item
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Record the new item */
id|newitem
op_assign
op_amp
(paren
id|ref_list-&gt;list
(braket
id|ref_list-&gt;index
op_increment
)braket
)paren
suffix:semicolon
id|newitem-&gt;name
op_assign
id|xstrdup
c_func
(paren
id|refname
)paren
suffix:semicolon
id|newitem-&gt;kind
op_assign
id|kind
suffix:semicolon
id|hashcpy
c_func
(paren
id|newitem-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|newitem-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|ref_list-&gt;maxwidth
)paren
id|ref_list-&gt;maxwidth
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_ref_list
r_static
r_void
id|free_ref_list
c_func
(paren
r_struct
id|ref_list
op_star
id|ref_list
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
id|ref_list-&gt;index
suffix:semicolon
id|i
op_increment
)paren
id|free
c_func
(paren
id|ref_list-&gt;list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref_list-&gt;list
)paren
suffix:semicolon
)brace
DECL|function|ref_cmp
r_static
r_int
id|ref_cmp
c_func
(paren
r_const
r_void
op_star
id|r1
comma
r_const
r_void
op_star
id|r2
)paren
(brace
r_struct
id|ref_item
op_star
id|c1
op_assign
(paren
r_struct
id|ref_item
op_star
)paren
(paren
id|r1
)paren
suffix:semicolon
r_struct
id|ref_item
op_star
id|c2
op_assign
(paren
r_struct
id|ref_item
op_star
)paren
(paren
id|r2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c1-&gt;kind
op_ne
id|c2-&gt;kind
)paren
r_return
id|c1-&gt;kind
id|c2-&gt;kind
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|c1-&gt;name
comma
id|c2-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|print_ref_item
r_static
r_void
id|print_ref_item
c_func
(paren
r_struct
id|ref_item
op_star
id|item
comma
r_int
id|maxwidth
comma
r_int
id|verbose
comma
r_int
id|abbrev
comma
r_int
id|current
)paren
(brace
r_char
id|c
suffix:semicolon
r_int
id|color
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_switch
c_cond
(paren
id|item-&gt;kind
)paren
(brace
r_case
id|REF_LOCAL_BRANCH
suffix:colon
id|color
op_assign
id|COLOR_BRANCH_LOCAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_REMOTE_BRANCH
suffix:colon
id|color
op_assign
id|COLOR_BRANCH_REMOTE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|color
op_assign
id|COLOR_BRANCH_PLAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
id|current
)paren
(brace
id|c
op_assign
l_char|&squot;*&squot;
suffix:semicolon
id|color
op_assign
id|COLOR_BRANCH_CURRENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_struct
id|strbuf
id|subject
suffix:semicolon
r_const
r_char
op_star
id|sub
op_assign
l_string|&quot; **** invalid ref ****&quot;
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|subject
comma
l_int|0
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit
c_func
(paren
id|item-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit
op_logical_and
op_logical_neg
id|parse_commit
c_func
(paren
id|commit
)paren
)paren
(brace
id|pretty_print_commit
c_func
(paren
id|CMIT_FMT_ONELINE
comma
id|commit
comma
op_amp
id|subject
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|sub
op_assign
id|subject.buf
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%c %s%-*s%s %s %s&bslash;n&quot;
comma
id|c
comma
id|branch_get_color
c_func
(paren
id|color
)paren
comma
id|maxwidth
comma
id|item-&gt;name
comma
id|branch_get_color
c_func
(paren
id|COLOR_BRANCH_RESET
)paren
comma
id|find_unique_abbrev
c_func
(paren
id|item-&gt;sha1
comma
id|abbrev
)paren
comma
id|sub
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|subject
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;%c %s%s%s&bslash;n&quot;
comma
id|c
comma
id|branch_get_color
c_func
(paren
id|color
)paren
comma
id|item-&gt;name
comma
id|branch_get_color
c_func
(paren
id|COLOR_BRANCH_RESET
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|print_ref_list
r_static
r_void
id|print_ref_list
c_func
(paren
r_int
id|kinds
comma
r_int
id|detached
comma
r_int
id|verbose
comma
r_int
id|abbrev
comma
r_struct
id|commit_list
op_star
id|with_commit
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ref_list
id|ref_list
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ref_list
comma
l_int|0
comma
r_sizeof
(paren
id|ref_list
)paren
)paren
suffix:semicolon
id|ref_list.kinds
op_assign
id|kinds
suffix:semicolon
id|ref_list.with_commit
op_assign
id|with_commit
suffix:semicolon
id|for_each_ref
c_func
(paren
id|append_ref
comma
op_amp
id|ref_list
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|ref_list.list
comma
id|ref_list.index
comma
r_sizeof
(paren
r_struct
id|ref_item
)paren
comma
id|ref_cmp
)paren
suffix:semicolon
id|detached
op_assign
(paren
id|detached
op_logical_and
(paren
id|kinds
op_amp
id|REF_LOCAL_BRANCH
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|detached
op_logical_and
id|has_commit
c_func
(paren
id|head_sha1
comma
id|with_commit
)paren
)paren
(brace
r_struct
id|ref_item
id|item
suffix:semicolon
id|item.name
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;(no branch)&quot;
)paren
suffix:semicolon
id|item.kind
op_assign
id|REF_LOCAL_BRANCH
suffix:semicolon
id|hashcpy
c_func
(paren
id|item.sha1
comma
id|head_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|item.name
)paren
OG
id|ref_list.maxwidth
)paren
id|ref_list.maxwidth
op_assign
id|strlen
c_func
(paren
id|item.name
)paren
suffix:semicolon
id|print_ref_item
c_func
(paren
op_amp
id|item
comma
id|ref_list.maxwidth
comma
id|verbose
comma
id|abbrev
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|item.name
)paren
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
id|ref_list.index
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|current
op_assign
op_logical_neg
id|detached
op_logical_and
(paren
id|ref_list.list
(braket
id|i
)braket
dot
id|kind
op_eq
id|REF_LOCAL_BRANCH
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|ref_list.list
(braket
id|i
)braket
dot
id|name
comma
id|head
)paren
suffix:semicolon
id|print_ref_item
c_func
(paren
op_amp
id|ref_list.list
(braket
id|i
)braket
comma
id|ref_list.maxwidth
comma
id|verbose
comma
id|abbrev
comma
id|current
)paren
suffix:semicolon
)brace
id|free_ref_list
c_func
(paren
op_amp
id|ref_list
)paren
suffix:semicolon
)brace
DECL|function|rename_branch
r_static
r_void
id|rename_branch
c_func
(paren
r_const
r_char
op_star
id|oldname
comma
r_const
r_char
op_star
id|newname
comma
r_int
id|force
)paren
(brace
r_char
id|oldref
(braket
id|PATH_MAX
)braket
comma
id|newref
(braket
id|PATH_MAX
)braket
comma
id|logmsg
(braket
id|PATH_MAX
op_star
l_int|2
op_plus
l_int|100
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|oldsection
(braket
id|PATH_MAX
)braket
comma
id|newsection
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldname
)paren
id|die
c_func
(paren
l_string|&quot;cannot rename the current branch while not on any.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|oldref
comma
r_sizeof
(paren
id|oldref
)paren
comma
l_string|&quot;refs/heads/%s&quot;
comma
id|oldname
)paren
OG
r_sizeof
(paren
id|oldref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Old branchname too long&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|oldref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Invalid branch name: %s&quot;
comma
id|oldref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|newref
comma
r_sizeof
(paren
id|newref
)paren
comma
l_string|&quot;refs/heads/%s&quot;
comma
id|newname
)paren
OG
r_sizeof
(paren
id|newref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;New branchname too long&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|newref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Invalid branch name: %s&quot;
comma
id|newref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resolve_ref
c_func
(paren
id|newref
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
op_logical_and
op_logical_neg
id|force
)paren
id|die
c_func
(paren
l_string|&quot;A branch named &squot;%s&squot; already exists.&quot;
comma
id|newname
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|logmsg
comma
r_sizeof
(paren
id|logmsg
)paren
comma
l_string|&quot;Branch: renamed %s to %s&quot;
comma
id|oldref
comma
id|newref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename_ref
c_func
(paren
id|oldref
comma
id|newref
comma
id|logmsg
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Branch rename failed&quot;
)paren
suffix:semicolon
multiline_comment|/* no need to pass logmsg here as HEAD didn&squot;t really move */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|oldname
comma
id|head
)paren
op_logical_and
id|create_symref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|newref
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Branch renamed to %s, but HEAD is not updated!&quot;
comma
id|newname
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|oldsection
comma
r_sizeof
(paren
id|oldsection
)paren
comma
l_string|&quot;branch.%s&quot;
comma
id|oldref
op_plus
l_int|11
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|newsection
comma
r_sizeof
(paren
id|newsection
)paren
comma
l_string|&quot;branch.%s&quot;
comma
id|newref
op_plus
l_int|11
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_config_rename_section
c_func
(paren
id|oldsection
comma
id|newsection
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Branch is renamed, but update of config-file failed&quot;
)paren
suffix:semicolon
)brace
DECL|function|opt_parse_with_commit
r_static
r_int
id|opt_parse_with_commit
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
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
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|arg
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;malformed object name %s&quot;
comma
id|arg
)paren
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
id|die
c_func
(paren
l_string|&quot;no such commit %s&quot;
comma
id|arg
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|commit
comma
id|opt-&gt;value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_branch
r_int
id|cmd_branch
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
r_delete
op_assign
l_int|0
comma
id|rename
op_assign
l_int|0
comma
id|force_create
op_assign
l_int|0
suffix:semicolon
r_int
id|verbose
op_assign
l_int|0
comma
id|abbrev
op_assign
id|DEFAULT_ABBREV
comma
id|detached
op_assign
l_int|0
suffix:semicolon
r_int
id|reflog
op_assign
l_int|0
suffix:semicolon
r_enum
id|branch_track
id|track
suffix:semicolon
r_int
id|kinds
op_assign
id|REF_LOCAL_BRANCH
suffix:semicolon
r_struct
id|commit_list
op_star
id|with_commit
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_GROUP
c_func
(paren
l_string|&quot;Generic options&quot;
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;track&quot;
comma
op_amp
id|track
comma
l_string|&quot;set up tracking mode (see git-pull(1))&quot;
comma
id|BRANCH_TRACK_EXPLICIT
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;color&quot;
comma
op_amp
id|branch_use_color
comma
l_string|&quot;use colored output&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;r&squot;
comma
l_int|NULL
comma
op_amp
id|kinds
comma
l_string|&quot;act on remote-tracking branches&quot;
comma
id|REF_REMOTE_BRANCH
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_int|0
comma
l_string|&quot;contains&quot;
comma
op_amp
id|with_commit
comma
l_string|&quot;commit&quot;
comma
l_string|&quot;print only branches that contain the commit&quot;
comma
id|opt_parse_with_commit
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;with&quot;
comma
op_amp
id|with_commit
comma
l_string|&quot;commit&quot;
comma
l_string|&quot;print only branches that contain the commit&quot;
comma
id|PARSE_OPT_HIDDEN
comma
id|opt_parse_with_commit
comma
)brace
comma
id|OPT__ABBREV
c_func
(paren
op_amp
id|abbrev
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;Specific git-branch actions:&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;a&squot;
comma
l_int|NULL
comma
op_amp
id|kinds
comma
l_string|&quot;list both remote-tracking and local branches&quot;
comma
id|REF_REMOTE_BRANCH
op_or
id|REF_LOCAL_BRANCH
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
r_delete
comma
l_string|&quot;delete fully merged branch&quot;
comma
l_int|1
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;D&squot;
comma
l_int|NULL
comma
op_amp
r_delete
comma
l_string|&quot;delete branch (even if not merged)&quot;
comma
l_int|2
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;m&squot;
comma
l_int|NULL
comma
op_amp
id|rename
comma
l_string|&quot;move/rename a branch and its reflog&quot;
comma
l_int|1
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;M&squot;
comma
l_int|NULL
comma
op_amp
id|rename
comma
l_string|&quot;move/rename a branch, even if target exists&quot;
comma
l_int|2
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;l&squot;
comma
l_int|NULL
comma
op_amp
id|reflog
comma
l_string|&quot;create the branch&squot;s reflog&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;f&squot;
comma
l_int|NULL
comma
op_amp
id|force_create
comma
l_string|&quot;force creation (when already exists)&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_int|0
comma
l_string|&quot;merged&quot;
comma
op_amp
id|mergefilter
comma
l_string|&quot;list only merged branches&quot;
comma
l_int|1
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|git_branch_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|branch_use_color
op_eq
l_int|1
)paren
id|branch_use_color
op_assign
id|git_use_color_default
suffix:semicolon
id|track
op_assign
id|git_branch_track
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
id|options
comma
id|builtin_branch_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_logical_neg
r_delete
op_plus
op_logical_neg
op_logical_neg
id|rename
op_plus
op_logical_neg
op_logical_neg
id|force_create
OG
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|builtin_branch_usage
comma
id|options
)paren
suffix:semicolon
id|head
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|head_sha1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
id|die
c_func
(paren
l_string|&quot;Failed to resolve HEAD as a valid ref.&quot;
)paren
suffix:semicolon
id|head
op_assign
id|xstrdup
c_func
(paren
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|head
comma
l_string|&quot;HEAD&quot;
)paren
)paren
(brace
id|detached
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|head
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
id|die
c_func
(paren
l_string|&quot;HEAD not found below refs/heads!&quot;
)paren
suffix:semicolon
id|head
op_add_assign
l_int|11
suffix:semicolon
)brace
r_if
c_cond
(paren
r_delete
)paren
r_return
id|delete_branches
c_func
(paren
id|argc
comma
id|argv
comma
r_delete
OG
l_int|1
comma
id|kinds
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
)paren
id|print_ref_list
c_func
(paren
id|kinds
comma
id|detached
comma
id|verbose
comma
id|abbrev
comma
id|with_commit
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rename
op_logical_and
(paren
id|argc
op_eq
l_int|1
)paren
)paren
id|rename_branch
c_func
(paren
id|head
comma
id|argv
(braket
l_int|0
)braket
comma
id|rename
OG
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rename
op_logical_and
(paren
id|argc
op_eq
l_int|2
)paren
)paren
id|rename_branch
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
comma
id|rename
OG
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argc
op_le
l_int|2
)paren
id|create_branch
c_func
(paren
id|head
comma
id|argv
(braket
l_int|0
)braket
comma
(paren
id|argc
op_eq
l_int|2
)paren
ques
c_cond
id|argv
(braket
l_int|1
)braket
suffix:colon
id|head
comma
id|force_create
comma
id|reflog
comma
id|track
)paren
suffix:semicolon
r_else
id|usage_with_options
c_func
(paren
id|builtin_branch_usage
comma
id|options
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
