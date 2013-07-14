macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;pathspec.h&quot;
multiline_comment|/*&n; * Finds which of the given pathspecs match items in the index.&n; *&n; * For each pathspec, sets the corresponding entry in the seen[] array&n; * (which should be specs items long, i.e. the same size as pathspec)&n; * to the nature of the &quot;closest&quot; (i.e. most specific) match found for&n; * that pathspec in the index, if it was a closer type of match than&n; * the existing entry.  As an optimization, matching is skipped&n; * altogether if seen[] already only contains non-zero entries.&n; *&n; * If seen[] has not already been written to, it may make sense&n; * to use find_pathspecs_matching_against_index() instead.&n; */
DECL|function|add_pathspec_matches_against_index
r_void
id|add_pathspec_matches_against_index
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
comma
r_char
op_star
id|seen
comma
r_int
id|specs
)paren
(brace
r_int
id|num_unmatched
op_assign
l_int|0
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Since we are walking the index as if we were walking the directory,&n;&t; * we have to mark the matched pathspec as seen; otherwise we will&n;&t; * mistakenly think that the user gave a pathspec that did not match&n;&t; * anything.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|specs
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|seen
(braket
id|i
)braket
)paren
id|num_unmatched
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_unmatched
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
id|match_pathspec
c_func
(paren
id|pathspec
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
comma
id|seen
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Finds which of the given pathspecs match items in the index.&n; *&n; * This is a one-shot wrapper around add_pathspec_matches_against_index()&n; * which allocates, populates, and returns a seen[] array indicating the&n; * nature of the &quot;closest&quot; (i.e. most specific) matches which each of the&n; * given pathspecs achieves against all items in the index.&n; */
DECL|function|find_pathspecs_matching_against_index
r_char
op_star
id|find_pathspecs_matching_against_index
c_func
(paren
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_char
op_star
id|seen
suffix:semicolon
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
id|pathspec
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
multiline_comment|/* just counting */
id|seen
op_assign
id|xcalloc
c_func
(paren
id|i
comma
l_int|1
)paren
suffix:semicolon
id|add_pathspec_matches_against_index
c_func
(paren
id|pathspec
comma
id|seen
comma
id|i
)paren
suffix:semicolon
r_return
id|seen
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the index to see whether path refers to a submodule, or&n; * something inside a submodule.  If the former, returns the path with&n; * any trailing slash stripped.  If the latter, dies with an error&n; * message.&n; */
DECL|function|check_path_for_gitlink
r_const
r_char
op_star
id|check_path_for_gitlink
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_int
id|i
comma
id|path_len
op_assign
id|strlen
c_func
(paren
id|path
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
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
(brace
r_int
id|ce_len
op_assign
id|ce_namelen
c_func
(paren
id|ce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path_len
op_le
id|ce_len
op_logical_or
id|path
(braket
id|ce_len
)braket
op_ne
l_char|&squot;/&squot;
op_logical_or
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|path
comma
id|ce_len
)paren
)paren
multiline_comment|/* path does not refer to this&n;&t;&t;&t;&t; * submodule or anything inside it */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|path_len
op_eq
id|ce_len
op_plus
l_int|1
)paren
(brace
multiline_comment|/* path refers to submodule;&n;&t;&t;&t;&t; * strip trailing slash */
r_return
id|xstrndup
c_func
(paren
id|ce-&gt;name
comma
id|ce_len
)paren
suffix:semicolon
)brace
r_else
(brace
id|die
(paren
id|_
c_func
(paren
l_string|&quot;Path &squot;%s&squot; is in submodule &squot;%.*s&squot;&quot;
)paren
comma
id|path
comma
id|ce_len
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|path
suffix:semicolon
)brace
multiline_comment|/*&n; * Dies if the given path refers to a file inside a symlinked&n; * directory in the index.&n; */
DECL|function|die_if_path_beyond_symlink
r_void
id|die_if_path_beyond_symlink
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
)paren
(brace
r_if
c_cond
(paren
id|has_symlink_leading_path
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
)paren
(brace
r_int
id|len
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
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;&squot;%s&squot; is beyond a symbolic link&quot;
)paren
comma
id|path
op_plus
id|len
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Magic pathspec&n; *&n; * NEEDSWORK: These need to be moved to dir.h or even to a new&n; * pathspec.h when we restructure get_pathspec() users to use the&n; * &quot;struct pathspec&quot; interface.&n; *&n; * Possible future magic semantics include stuff like:&n; *&n; *&t;{ PATHSPEC_NOGLOB, &squot;!&squot;, &quot;noglob&quot; },&n; *&t;{ PATHSPEC_ICASE, &squot;&bslash;0&squot;, &quot;icase&quot; },&n; *&t;{ PATHSPEC_RECURSIVE, &squot;*&squot;, &quot;recursive&quot; },&n; *&t;{ PATHSPEC_REGEXP, &squot;&bslash;0&squot;, &quot;regexp&quot; },&n; *&n; */
DECL|macro|PATHSPEC_FROMTOP
mdefine_line|#define PATHSPEC_FROMTOP    (1&lt;&lt;0)
DECL|struct|pathspec_magic
r_static
r_struct
id|pathspec_magic
(brace
DECL|member|bit
r_int
id|bit
suffix:semicolon
DECL|member|mnemonic
r_char
id|mnemonic
suffix:semicolon
multiline_comment|/* this cannot be &squot;:&squot;! */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|variable|pathspec_magic
)brace
id|pathspec_magic
(braket
)braket
op_assign
(brace
(brace
id|PATHSPEC_FROMTOP
comma
l_char|&squot;/&squot;
comma
l_string|&quot;top&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Take an element of a pathspec and check for magic signatures.&n; * Append the result to the prefix.&n; *&n; * For now, we only parse the syntax and throw out anything other than&n; * &quot;top&quot; magic.&n; *&n; * NEEDSWORK: This needs to be rewritten when we start migrating&n; * get_pathspec() users to use the &quot;struct pathspec&quot; interface.  For&n; * example, a pathspec element may be marked as case-insensitive, but&n; * the prefix part must always match literally, and a single stupid&n; * string cannot express such a case.&n; */
DECL|function|prefix_pathspec
r_static
r_const
r_char
op_star
id|prefix_pathspec
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_int
id|prefixlen
comma
r_const
r_char
op_star
id|elt
)paren
(brace
r_int
id|magic
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|copyfrom
op_assign
id|elt
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|elt
(braket
l_int|0
)braket
op_ne
l_char|&squot;:&squot;
)paren
(brace
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
r_else
r_if
c_cond
(paren
id|elt
(braket
l_int|1
)braket
op_eq
l_char|&squot;(&squot;
)paren
(brace
multiline_comment|/* longhand */
r_const
r_char
op_star
id|nextat
suffix:semicolon
r_for
c_loop
(paren
id|copyfrom
op_assign
id|elt
op_plus
l_int|2
suffix:semicolon
op_star
id|copyfrom
op_logical_and
op_star
id|copyfrom
op_ne
l_char|&squot;)&squot;
suffix:semicolon
id|copyfrom
op_assign
id|nextat
)paren
(brace
r_int
id|len
op_assign
id|strcspn
c_func
(paren
id|copyfrom
comma
l_string|&quot;,)&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copyfrom
(braket
id|len
)braket
op_eq
l_char|&squot;,&squot;
)paren
id|nextat
op_assign
id|copyfrom
op_plus
id|len
op_plus
l_int|1
suffix:semicolon
r_else
multiline_comment|/* handle &squot;)&squot; and &squot;&bslash;0&squot; */
id|nextat
op_assign
id|copyfrom
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_continue
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
id|ARRAY_SIZE
c_func
(paren
id|pathspec_magic
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|pathspec_magic
(braket
id|i
)braket
dot
id|name
)paren
op_eq
id|len
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|pathspec_magic
(braket
id|i
)braket
dot
id|name
comma
id|copyfrom
comma
id|len
)paren
)paren
(brace
id|magic
op_or_assign
id|pathspec_magic
(braket
id|i
)braket
dot
id|bit
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ARRAY_SIZE
c_func
(paren
id|pathspec_magic
)paren
op_le
id|i
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Invalid pathspec magic &squot;%.*s&squot; in &squot;%s&squot;&quot;
)paren
comma
(paren
r_int
)paren
id|len
comma
id|copyfrom
comma
id|elt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|copyfrom
op_ne
l_char|&squot;)&squot;
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Missing &squot;)&squot; at the end of pathspec magic in &squot;%s&squot;&quot;
)paren
comma
id|elt
)paren
suffix:semicolon
id|copyfrom
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* shorthand */
r_for
c_loop
(paren
id|copyfrom
op_assign
id|elt
op_plus
l_int|1
suffix:semicolon
op_star
id|copyfrom
op_logical_and
op_star
id|copyfrom
op_ne
l_char|&squot;:&squot;
suffix:semicolon
id|copyfrom
op_increment
)paren
(brace
r_char
id|ch
op_assign
op_star
id|copyfrom
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_pathspec_magic
c_func
(paren
id|ch
)paren
)paren
r_break
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
id|ARRAY_SIZE
c_func
(paren
id|pathspec_magic
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pathspec_magic
(braket
id|i
)braket
dot
id|mnemonic
op_eq
id|ch
)paren
(brace
id|magic
op_or_assign
id|pathspec_magic
(braket
id|i
)braket
dot
id|bit
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ARRAY_SIZE
c_func
(paren
id|pathspec_magic
)paren
op_le
id|i
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Unimplemented pathspec magic &squot;%c&squot; in &squot;%s&squot;&quot;
)paren
comma
id|ch
comma
id|elt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|copyfrom
op_eq
l_char|&squot;:&squot;
)paren
id|copyfrom
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|magic
op_amp
id|PATHSPEC_FROMTOP
)paren
r_return
id|xstrdup
c_func
(paren
id|copyfrom
)paren
suffix:semicolon
r_else
r_return
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefixlen
comma
id|copyfrom
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * N.B. get_pathspec() is deprecated in favor of the &quot;struct pathspec&quot;&n; * based interface - see pathspec_magic above.&n; *&n; * Arguments:&n; *  - prefix - a path relative to the root of the working tree&n; *  - pathspec - a list of paths underneath the prefix path&n; *&n; * Iterates over pathspec, prepending each path with prefix,&n; * and return the resulting list.&n; *&n; * If pathspec is empty, return a singleton list containing prefix.&n; *&n; * If pathspec and prefix are both empty, return an empty list.&n; *&n; * This is typically used by built-in commands such as add.c, in order&n; * to normalize argv arguments provided to the built-in into a list of&n; * paths to process, all relative to the root of the working tree.&n; */
DECL|function|get_pathspec
r_const
r_char
op_star
op_star
id|get_pathspec
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
op_star
id|pathspec
)paren
(brace
r_const
r_char
op_star
id|entry
op_assign
op_star
id|pathspec
suffix:semicolon
r_const
r_char
op_star
op_star
id|src
comma
op_star
op_star
id|dst
suffix:semicolon
r_int
id|prefixlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefix
op_logical_and
op_logical_neg
id|entry
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
r_static
r_const
r_char
op_star
id|spec
(braket
l_int|2
)braket
suffix:semicolon
id|spec
(braket
l_int|0
)braket
op_assign
id|prefix
suffix:semicolon
id|spec
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
id|spec
suffix:semicolon
)brace
multiline_comment|/* Otherwise we have to re-write the entries.. */
id|src
op_assign
id|pathspec
suffix:semicolon
id|dst
op_assign
id|pathspec
suffix:semicolon
id|prefixlen
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
r_while
c_loop
(paren
op_star
id|src
)paren
(brace
op_star
(paren
id|dst
op_increment
)paren
op_assign
id|prefix_pathspec
c_func
(paren
id|prefix
comma
id|prefixlen
comma
op_star
id|src
)paren
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
op_star
id|dst
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|pathspec
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|pathspec
suffix:semicolon
)brace
DECL|function|copy_pathspec
r_void
id|copy_pathspec
c_func
(paren
r_struct
id|pathspec
op_star
id|dst
comma
r_const
r_struct
id|pathspec
op_star
id|src
)paren
(brace
op_star
id|dst
op_assign
op_star
id|src
suffix:semicolon
id|dst-&gt;items
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pathspec_item
)paren
op_star
id|dst-&gt;nr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst-&gt;items
comma
id|src-&gt;items
comma
r_sizeof
(paren
r_struct
id|pathspec_item
)paren
op_star
id|dst-&gt;nr
)paren
suffix:semicolon
)brace
eof
