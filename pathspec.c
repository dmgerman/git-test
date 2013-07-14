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
multiline_comment|/*&n; * Magic pathspec&n; *&n; * Possible future magic semantics include stuff like:&n; *&n; *&t;{ PATHSPEC_NOGLOB, &squot;!&squot;, &quot;noglob&quot; },&n; *&t;{ PATHSPEC_ICASE, &squot;&bslash;0&squot;, &quot;icase&quot; },&n; *&t;{ PATHSPEC_RECURSIVE, &squot;*&squot;, &quot;recursive&quot; },&n; *&t;{ PATHSPEC_REGEXP, &squot;&bslash;0&squot;, &quot;regexp&quot; },&n; *&n; */
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
multiline_comment|/*&n; * Take an element of a pathspec and check for magic signatures.&n; * Append the result to the prefix. Return the magic bitmap.&n; *&n; * For now, we only parse the syntax and throw out anything other than&n; * &quot;top&quot; magic.&n; *&n; * NEEDSWORK: This needs to be rewritten when we start migrating&n; * get_pathspec() users to use the &quot;struct pathspec&quot; interface.  For&n; * example, a pathspec element may be marked as case-insensitive, but&n; * the prefix part must always match literally, and a single stupid&n; * string cannot express such a case.&n; */
DECL|function|prefix_pathspec
r_static
r_int
id|prefix_pathspec
c_func
(paren
r_struct
id|pathspec_item
op_star
id|item
comma
r_int
op_star
id|p_short_magic
comma
r_const
r_char
op_star
op_star
id|raw
comma
r_int
id|flags
comma
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
comma
id|short_magic
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
r_char
op_star
id|match
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
id|short_magic
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
id|magic
op_or_assign
id|short_magic
suffix:semicolon
op_star
id|p_short_magic
op_assign
id|short_magic
suffix:semicolon
r_if
c_cond
(paren
id|magic
op_amp
id|PATHSPEC_FROMTOP
)paren
id|match
op_assign
id|xstrdup
c_func
(paren
id|copyfrom
)paren
suffix:semicolon
r_else
id|match
op_assign
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
op_star
id|raw
op_assign
id|item-&gt;match
op_assign
id|match
suffix:semicolon
multiline_comment|/*&n;&t; * Prefix the pathspec (keep all magic) and assign to&n;&t; * original. Useful for passing to another command.&n;&t; */
r_if
c_cond
(paren
id|flags
op_amp
id|PATHSPEC_PREFIX_ORIGIN
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|sb
comma
id|elt
comma
id|copyfrom
id|elt
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|match
)paren
suffix:semicolon
id|item-&gt;original
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|sb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|item-&gt;original
op_assign
id|elt
suffix:semicolon
id|item-&gt;len
op_assign
id|strlen
c_func
(paren
id|item-&gt;match
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP
)paren
op_logical_and
(paren
id|item-&gt;len
op_ge
l_int|1
op_logical_and
id|item-&gt;match
(braket
id|item-&gt;len
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
op_logical_and
(paren
id|i
op_assign
id|cache_name_pos
c_func
(paren
id|item-&gt;match
comma
id|item-&gt;len
l_int|1
)paren
)paren
op_ge
l_int|0
op_logical_and
id|S_ISGITLINK
c_func
(paren
id|active_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|ce_mode
)paren
)paren
(brace
id|item-&gt;len
op_decrement
suffix:semicolon
id|match
(braket
id|item-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE
)paren
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
op_logical_neg
id|S_ISGITLINK
c_func
(paren
id|ce-&gt;ce_mode
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;len
op_le
id|ce_len
op_logical_or
id|match
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
id|match
comma
id|ce_len
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;len
op_eq
id|ce_len
op_plus
l_int|1
)paren
(brace
multiline_comment|/* strip trailing slash */
id|item-&gt;len
op_decrement
suffix:semicolon
id|match
(braket
id|item-&gt;len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
id|die
(paren
id|_
c_func
(paren
l_string|&quot;Pathspec &squot;%s&squot; is in submodule &squot;%.*s&squot;&quot;
)paren
comma
id|elt
comma
id|ce_len
comma
id|ce-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|limit_pathspec_to_literal
c_func
(paren
)paren
)paren
id|item-&gt;nowildcard_len
op_assign
id|item-&gt;len
suffix:semicolon
r_else
id|item-&gt;nowildcard_len
op_assign
id|simple_length
c_func
(paren
id|item-&gt;match
)paren
suffix:semicolon
id|item-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;nowildcard_len
OL
id|item-&gt;len
op_logical_and
id|item-&gt;match
(braket
id|item-&gt;nowildcard_len
)braket
op_eq
l_char|&squot;*&squot;
op_logical_and
id|no_wildcard
c_func
(paren
id|item-&gt;match
op_plus
id|item-&gt;nowildcard_len
op_plus
l_int|1
)paren
)paren
id|item-&gt;flags
op_or_assign
id|PATHSPEC_ONESTAR
suffix:semicolon
r_return
id|magic
suffix:semicolon
)brace
DECL|function|pathspec_item_cmp
r_static
r_int
id|pathspec_item_cmp
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|pathspec_item
op_star
id|a
comma
op_star
id|b
suffix:semicolon
id|a
op_assign
(paren
r_struct
id|pathspec_item
op_star
)paren
id|a_
suffix:semicolon
id|b
op_assign
(paren
r_struct
id|pathspec_item
op_star
)paren
id|b_
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|a-&gt;match
comma
id|b-&gt;match
)paren
suffix:semicolon
)brace
DECL|function|unsupported_magic
r_static
r_void
id|NORETURN
id|unsupported_magic
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_int
id|magic
comma
r_int
id|short_magic
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
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
(brace
r_const
r_struct
id|pathspec_magic
op_star
id|m
op_assign
id|pathspec_magic
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|magic
op_amp
id|m-&gt;bit
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sb.len
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|short_magic
op_amp
id|m-&gt;bit
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;&squot;%c&squot;&quot;
comma
id|m-&gt;mnemonic
)paren
suffix:semicolon
r_else
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;&squot;%s&squot;&quot;
comma
id|m-&gt;name
)paren
suffix:semicolon
id|n
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We may want to substitute &quot;this command&quot; with a command&n;&t; * name. E.g. when add--interactive dies when running&n;&t; * &quot;checkout -p&quot;&n;&t; */
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;%s: pathspec magic not supported by this command: %s&quot;
)paren
comma
id|pattern
comma
id|sb.buf
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given command line arguments and a prefix, convert the input to&n; * pathspec. die() if any magic in magic_mask is used.&n; */
DECL|function|parse_pathspec
r_void
id|parse_pathspec
c_func
(paren
r_struct
id|pathspec
op_star
id|pathspec
comma
r_int
id|magic_mask
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|pathspec_item
op_star
id|item
suffix:semicolon
r_const
r_char
op_star
id|entry
op_assign
id|argv
ques
c_cond
op_star
id|argv
suffix:colon
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|n
comma
id|prefixlen
suffix:semicolon
id|memset
c_func
(paren
id|pathspec
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|pathspec
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PATHSPEC_MAXDEPTH_VALID
)paren
id|pathspec-&gt;magic
op_or_assign
id|PATHSPEC_MAXDEPTH
suffix:semicolon
multiline_comment|/* No arguments, no prefix -&gt; no pathspec */
r_if
c_cond
(paren
op_logical_neg
id|entry
op_logical_and
op_logical_neg
id|prefix
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|PATHSPEC_PREFER_CWD
)paren
op_logical_and
(paren
id|flags
op_amp
id|PATHSPEC_PREFER_FULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;BUG: PATHSPEC_PREFER_CWD and PATHSPEC_PREFER_FULL are incompatible&quot;
)paren
suffix:semicolon
multiline_comment|/* No arguments with prefix -&gt; prefix pathspec */
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
id|raw
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PATHSPEC_PREFER_FULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|PATHSPEC_PREFER_CWD
)paren
)paren
id|die
c_func
(paren
l_string|&quot;BUG: PATHSPEC_PREFER_CWD requires arguments&quot;
)paren
suffix:semicolon
id|pathspec-&gt;items
op_assign
id|item
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|item
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|item
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|item
)paren
)paren
suffix:semicolon
id|item-&gt;match
op_assign
id|prefix
suffix:semicolon
id|item-&gt;original
op_assign
id|prefix
suffix:semicolon
id|item-&gt;nowildcard_len
op_assign
id|item-&gt;len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|raw
(braket
l_int|0
)braket
op_assign
id|prefix
suffix:semicolon
id|raw
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|pathspec-&gt;nr
op_assign
l_int|1
suffix:semicolon
id|pathspec-&gt;raw
op_assign
id|raw
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|argv
(braket
id|n
)braket
)paren
id|n
op_increment
suffix:semicolon
id|pathspec-&gt;nr
op_assign
id|n
suffix:semicolon
id|pathspec-&gt;items
op_assign
id|item
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|item
)paren
op_star
id|n
)paren
suffix:semicolon
id|pathspec-&gt;raw
op_assign
id|argv
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|short_magic
suffix:semicolon
id|entry
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
id|item
(braket
id|i
)braket
dot
id|magic
op_assign
id|prefix_pathspec
c_func
(paren
id|item
op_plus
id|i
comma
op_amp
id|short_magic
comma
id|argv
op_plus
id|i
comma
id|flags
comma
id|prefix
comma
id|prefixlen
comma
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item
(braket
id|i
)braket
dot
id|magic
op_amp
id|magic_mask
)paren
id|unsupported_magic
c_func
(paren
id|entry
comma
id|item
(braket
id|i
)braket
dot
id|magic
op_amp
id|magic_mask
comma
id|short_magic
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|PATHSPEC_SYMLINK_LEADING_PATH
)paren
op_logical_and
id|has_symlink_leading_path
c_func
(paren
id|item
(braket
id|i
)braket
dot
id|match
comma
id|item
(braket
id|i
)braket
dot
id|len
)paren
)paren
(brace
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;pathspec &squot;%s&squot; is beyond a symbolic link&quot;
)paren
comma
id|entry
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|item
(braket
id|i
)braket
dot
id|nowildcard_len
OL
id|item
(braket
id|i
)braket
dot
id|len
)paren
id|pathspec-&gt;has_wildcard
op_assign
l_int|1
suffix:semicolon
id|pathspec-&gt;magic
op_or_assign
id|item
(braket
id|i
)braket
dot
id|magic
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pathspec-&gt;magic
op_amp
id|PATHSPEC_MAXDEPTH
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|PATHSPEC_KEEP_ORDER
)paren
id|die
c_func
(paren
l_string|&quot;BUG: PATHSPEC_MAXDEPTH_VALID and PATHSPEC_KEEP_ORDER are incompatible&quot;
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|pathspec-&gt;items
comma
id|pathspec-&gt;nr
comma
r_sizeof
(paren
r_struct
id|pathspec_item
)paren
comma
id|pathspec_item_cmp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * N.B. get_pathspec() is deprecated in favor of the &quot;struct pathspec&quot;&n; * based interface - see pathspec.c:parse_pathspec().&n; *&n; * Arguments:&n; *  - prefix - a path relative to the root of the working tree&n; *  - pathspec - a list of paths underneath the prefix path&n; *&n; * Iterates over pathspec, prepending each path with prefix,&n; * and return the resulting list.&n; *&n; * If pathspec is empty, return a singleton list containing prefix.&n; *&n; * If pathspec and prefix are both empty, return an empty list.&n; *&n; * This is typically used by built-in commands such as add.c, in order&n; * to normalize argv arguments provided to the built-in into a list of&n; * paths to process, all relative to the root of the working tree.&n; */
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
r_struct
id|pathspec
id|ps
suffix:semicolon
id|parse_pathspec
c_func
(paren
op_amp
id|ps
comma
id|PATHSPEC_ALL_MAGIC
op_amp
op_complement
id|PATHSPEC_FROMTOP
comma
id|PATHSPEC_PREFER_CWD
comma
id|prefix
comma
id|pathspec
)paren
suffix:semicolon
r_return
id|ps.raw
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
DECL|function|free_pathspec
r_void
id|free_pathspec
c_func
(paren
r_struct
id|pathspec
op_star
id|pathspec
)paren
(brace
id|free
c_func
(paren
id|pathspec-&gt;items
)paren
suffix:semicolon
id|pathspec-&gt;items
op_assign
l_int|NULL
suffix:semicolon
)brace
eof
