macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|macro|CUTOFF_DATE_SLOP
mdefine_line|#define CUTOFF_DATE_SLOP 86400 /* one day */
DECL|struct|rev_name
r_typedef
r_struct
id|rev_name
(brace
DECL|member|tip_name
r_const
r_char
op_star
id|tip_name
suffix:semicolon
DECL|member|generation
r_int
id|generation
suffix:semicolon
DECL|member|distance
r_int
id|distance
suffix:semicolon
DECL|typedef|rev_name
)brace
id|rev_name
suffix:semicolon
DECL|variable|cutoff
r_static
r_int
id|cutoff
op_assign
id|LONG_MAX
suffix:semicolon
multiline_comment|/* How many generations are maximally preferred over _one_ merge traversal? */
DECL|macro|MERGE_TRAVERSAL_WEIGHT
mdefine_line|#define MERGE_TRAVERSAL_WEIGHT 65535
DECL|function|name_rev
r_static
r_void
id|name_rev
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
id|tip_name
comma
r_int
id|generation
comma
r_int
id|distance
comma
r_int
id|deref
)paren
(brace
r_struct
id|rev_name
op_star
id|name
op_assign
(paren
r_struct
id|rev_name
op_star
)paren
id|commit-&gt;util
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_int
id|parent_number
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;object.parsed
)paren
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;date
OL
id|cutoff
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|deref
)paren
(brace
r_char
op_star
id|new_name
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|tip_name
)paren
op_plus
l_int|3
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|new_name
comma
id|tip_name
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|new_name
comma
l_string|&quot;^0&quot;
)paren
suffix:semicolon
id|tip_name
op_assign
id|new_name
suffix:semicolon
r_if
c_cond
(paren
id|generation
)paren
id|die
c_func
(paren
l_string|&quot;generation: %d, but deref?&quot;
comma
id|generation
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
(brace
id|name
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
id|rev_name
)paren
)paren
suffix:semicolon
id|commit-&gt;util
op_assign
id|name
suffix:semicolon
r_goto
id|copy_data
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|name-&gt;distance
OG
id|distance
)paren
(brace
id|copy_data
suffix:colon
id|name-&gt;tip_name
op_assign
id|tip_name
suffix:semicolon
id|name-&gt;generation
op_assign
id|generation
suffix:semicolon
id|name-&gt;distance
op_assign
id|distance
suffix:semicolon
)brace
r_else
r_return
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
comma
id|parent_number
op_increment
)paren
(brace
r_if
c_cond
(paren
id|parent_number
OG
l_int|1
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|tip_name
)paren
suffix:semicolon
r_char
op_star
id|new_name
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
op_plus
id|decimal_length
c_func
(paren
id|generation
)paren
op_plus
multiline_comment|/* ~&lt;n&gt; */
l_int|1
op_plus
l_int|2
op_plus
multiline_comment|/* ^NN */
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|tip_name
op_plus
id|len
l_int|2
comma
l_string|&quot;^0&quot;
)paren
)paren
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|generation
OG
l_int|0
)paren
id|sprintf
c_func
(paren
id|new_name
comma
l_string|&quot;%.*s~%d^%d&quot;
comma
id|len
comma
id|tip_name
comma
id|generation
comma
id|parent_number
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|new_name
comma
l_string|&quot;%.*s^%d&quot;
comma
id|len
comma
id|tip_name
comma
id|parent_number
)paren
suffix:semicolon
id|name_rev
c_func
(paren
id|parents-&gt;item
comma
id|new_name
comma
l_int|0
comma
id|distance
op_plus
id|MERGE_TRAVERSAL_WEIGHT
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|name_rev
c_func
(paren
id|parents-&gt;item
comma
id|tip_name
comma
id|generation
op_plus
l_int|1
comma
id|distance
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|subpath_matches
r_static
r_int
id|subpath_matches
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
id|filter
)paren
(brace
r_const
r_char
op_star
id|subpath
op_assign
id|path
suffix:semicolon
r_while
c_loop
(paren
id|subpath
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|filter
comma
id|subpath
comma
l_int|0
)paren
)paren
r_return
id|subpath
id|path
suffix:semicolon
id|subpath
op_assign
id|strchr
c_func
(paren
id|subpath
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subpath
)paren
id|subpath
op_increment
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|struct|name_ref_data
r_struct
id|name_ref_data
(brace
DECL|member|tags_only
r_int
id|tags_only
suffix:semicolon
DECL|member|name_only
r_int
id|name_only
suffix:semicolon
DECL|member|ref_filter
r_const
r_char
op_star
id|ref_filter
suffix:semicolon
)brace
suffix:semicolon
DECL|function|name_ref
r_static
r_int
id|name_ref
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
r_struct
id|name_ref_data
op_star
id|data
op_assign
id|cb_data
suffix:semicolon
r_int
id|can_abbreviate_output
op_assign
id|data-&gt;tags_only
op_logical_and
id|data-&gt;name_only
suffix:semicolon
r_int
id|deref
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;tags_only
op_logical_and
id|prefixcmp
c_func
(paren
id|path
comma
l_string|&quot;refs/tags/&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;ref_filter
)paren
(brace
r_switch
c_cond
(paren
id|subpath_matches
c_func
(paren
id|path
comma
id|data-&gt;ref_filter
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* did not match */
r_return
l_int|0
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* matched fully */
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* matched subpath */
id|can_abbreviate_output
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|o
op_logical_and
id|o-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
r_struct
id|tag
op_star
id|t
op_assign
(paren
r_struct
id|tag
op_star
)paren
id|o
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t-&gt;tagged
)paren
r_break
suffix:semicolon
multiline_comment|/* broken repository */
id|o
op_assign
id|parse_object
c_func
(paren
id|t-&gt;tagged-&gt;sha1
)paren
suffix:semicolon
id|deref
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o
op_logical_and
id|o-&gt;type
op_eq
id|OBJ_COMMIT
)paren
(brace
r_struct
id|commit
op_star
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|o
suffix:semicolon
r_if
c_cond
(paren
id|can_abbreviate_output
)paren
id|path
op_assign
id|shorten_unambiguous_ref
c_func
(paren
id|path
comma
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|path
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
id|path
op_assign
id|path
op_plus
l_int|11
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|path
comma
l_string|&quot;refs/&quot;
)paren
)paren
id|path
op_assign
id|path
op_plus
l_int|5
suffix:semicolon
id|name_rev
c_func
(paren
id|commit
comma
id|xstrdup
c_func
(paren
id|path
)paren
comma
l_int|0
comma
l_int|0
comma
id|deref
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* returns a static buffer */
DECL|function|get_rev_name
r_static
r_const
r_char
op_star
id|get_rev_name
c_func
(paren
r_const
r_struct
id|object
op_star
id|o
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|rev_name
op_star
id|n
suffix:semicolon
r_struct
id|commit
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
id|o-&gt;type
op_ne
id|OBJ_COMMIT
)paren
r_return
l_int|NULL
suffix:semicolon
id|c
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|o
suffix:semicolon
id|n
op_assign
id|c-&gt;util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n-&gt;generation
)paren
r_return
id|n-&gt;tip_name
suffix:semicolon
r_else
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|n-&gt;tip_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|n-&gt;tip_name
op_plus
id|len
l_int|2
comma
l_string|&quot;^0&quot;
)paren
)paren
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|snprintf
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
l_string|&quot;%.*s~%d&quot;
comma
id|len
comma
id|n-&gt;tip_name
comma
id|n-&gt;generation
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
)brace
DECL|function|show_name
r_static
r_void
id|show_name
c_func
(paren
r_const
r_struct
id|object
op_star
id|obj
comma
r_const
r_char
op_star
id|caller_name
comma
r_int
id|always
comma
r_int
id|allow_undefined
comma
r_int
id|name_only
)paren
(brace
r_const
r_char
op_star
id|name
suffix:semicolon
r_const
r_int
r_char
op_star
id|sha1
op_assign
id|obj-&gt;sha1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_only
)paren
id|printf
c_func
(paren
l_string|&quot;%s &quot;
comma
id|caller_name
ques
c_cond
id|caller_name
suffix:colon
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|name
op_assign
id|get_rev_name
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|allow_undefined
)paren
id|printf
c_func
(paren
l_string|&quot;undefined&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|always
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|find_unique_abbrev
c_func
(paren
id|sha1
comma
id|DEFAULT_ABBREV
)paren
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;cannot describe &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
DECL|variable|name_rev_usage
r_static
r_char
r_const
op_star
r_const
id|name_rev_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git name-rev [options] &lt;commit&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git name-rev [options] --all&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git name-rev [options] --stdin&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|name_rev_line
r_static
r_void
id|name_rev_line
c_func
(paren
r_char
op_star
id|p
comma
r_struct
id|name_ref_data
op_star
id|data
)paren
(brace
r_int
id|forty
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|p_start
suffix:semicolon
r_for
c_loop
(paren
id|p_start
op_assign
id|p
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
DECL|macro|ishex
mdefine_line|#define ishex(x) (isdigit((x)) || ((x) &gt;= &squot;a&squot; &amp;&amp; (x) &lt;= &squot;f&squot;))
r_if
c_cond
(paren
op_logical_neg
id|ishex
c_func
(paren
op_star
id|p
)paren
)paren
id|forty
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_increment
id|forty
op_eq
l_int|40
op_logical_and
op_logical_neg
id|ishex
c_func
(paren
op_star
(paren
id|p
op_plus
l_int|1
)paren
)paren
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|40
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
r_char
id|c
op_assign
op_star
(paren
id|p
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|p_len
op_assign
id|p
id|p_start
op_plus
l_int|1
suffix:semicolon
id|forty
op_assign
l_int|0
suffix:semicolon
op_star
(paren
id|p
op_plus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|p
l_int|39
comma
id|sha1
)paren
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o
)paren
id|name
op_assign
id|get_rev_name
c_func
(paren
id|o
)paren
suffix:semicolon
)brace
op_star
(paren
id|p
op_plus
l_int|1
)paren
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;name_only
)paren
id|printf
c_func
(paren
l_string|&quot;%.*s%s&quot;
comma
id|p_len
l_int|40
comma
id|p_start
comma
id|name
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%.*s (%s)&quot;
comma
id|p_len
comma
id|p_start
comma
id|name
)paren
suffix:semicolon
id|p_start
op_assign
id|p
op_plus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* flush */
r_if
c_cond
(paren
id|p_start
op_ne
id|p
)paren
id|fwrite
c_func
(paren
id|p_start
comma
id|p
id|p_start
comma
l_int|1
comma
id|stdout
)paren
suffix:semicolon
)brace
DECL|function|cmd_name_rev
r_int
id|cmd_name_rev
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
r_struct
id|object_array
id|revs
op_assign
id|OBJECT_ARRAY_INIT
suffix:semicolon
r_int
id|all
op_assign
l_int|0
comma
id|transform_stdin
op_assign
l_int|0
comma
id|allow_undefined
op_assign
l_int|1
comma
id|always
op_assign
l_int|0
suffix:semicolon
r_struct
id|name_ref_data
id|data
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|option
id|opts
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;name-only&quot;
comma
op_amp
id|data.name_only
comma
id|N_
c_func
(paren
l_string|&quot;print only names (no SHA-1)&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;tags&quot;
comma
op_amp
id|data.tags_only
comma
id|N_
c_func
(paren
l_string|&quot;only use tags to name the commits&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;refs&quot;
comma
op_amp
id|data.ref_filter
comma
id|N_
c_func
(paren
l_string|&quot;pattern&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;only use refs matching &lt;pattern&gt;&quot;
)paren
)paren
comma
id|OPT_GROUP
c_func
(paren
l_string|&quot;&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;all&quot;
comma
op_amp
id|all
comma
id|N_
c_func
(paren
l_string|&quot;list all commits reachable from all refs&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|transform_stdin
comma
id|N_
c_func
(paren
l_string|&quot;read from stdin&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;undefined&quot;
comma
op_amp
id|allow_undefined
comma
id|N_
c_func
(paren
l_string|&quot;allow to print `undefined` names&quot;
)paren
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;always&quot;
comma
op_amp
id|always
comma
id|N_
c_func
(paren
l_string|&quot;show abbreviated commit object as fallback&quot;
)paren
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
id|git_default_config
comma
l_int|NULL
)paren
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
id|prefix
comma
id|opts
comma
id|name_rev_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_logical_neg
id|all
op_plus
op_logical_neg
op_logical_neg
id|transform_stdin
op_plus
op_logical_neg
op_logical_neg
id|argc
OG
l_int|1
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Specify either a list, or --all, not both!&quot;
)paren
suffix:semicolon
id|usage_with_options
c_func
(paren
id|name_rev_usage
comma
id|opts
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|all
op_logical_or
id|transform_stdin
)paren
id|cutoff
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|argc
suffix:semicolon
id|argc
op_decrement
comma
id|argv
op_increment
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
id|object
op_star
id|o
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
op_star
id|argv
comma
id|sha1
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Could not get sha1 for %s. Skipping.&bslash;n&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|o
op_assign
id|deref_tag
c_func
(paren
id|parse_object
c_func
(paren
id|sha1
)paren
comma
op_star
id|argv
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_or
id|o-&gt;type
op_ne
id|OBJ_COMMIT
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Could not get commit for %s. Skipping.&bslash;n&quot;
comma
op_star
id|argv
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|o
suffix:semicolon
r_if
c_cond
(paren
id|cutoff
OG
id|commit-&gt;date
)paren
id|cutoff
op_assign
id|commit-&gt;date
suffix:semicolon
id|add_object_array
c_func
(paren
(paren
r_struct
id|object
op_star
)paren
id|commit
comma
op_star
id|argv
comma
op_amp
id|revs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cutoff
)paren
id|cutoff
op_assign
id|cutoff
id|CUTOFF_DATE_SLOP
suffix:semicolon
id|for_each_ref
c_func
(paren
id|name_ref
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transform_stdin
)paren
(brace
r_char
id|buffer
(braket
l_int|2048
)braket
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|feof
c_func
(paren
id|stdin
)paren
)paren
(brace
r_char
op_star
id|p
op_assign
id|fgets
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|stdin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_break
suffix:semicolon
id|name_rev_line
c_func
(paren
id|p
comma
op_amp
id|data
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|all
)paren
(brace
r_int
id|i
comma
id|max
suffix:semicolon
id|max
op_assign
id|get_max_object_index
c_func
(paren
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|get_indexed_object
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj
op_logical_or
id|obj-&gt;type
op_ne
id|OBJ_COMMIT
)paren
r_continue
suffix:semicolon
id|show_name
c_func
(paren
id|obj
comma
l_int|NULL
comma
id|always
comma
id|allow_undefined
comma
id|data.name_only
)paren
suffix:semicolon
)brace
)brace
r_else
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
id|revs.nr
suffix:semicolon
id|i
op_increment
)paren
id|show_name
c_func
(paren
id|revs.objects
(braket
id|i
)braket
dot
id|item
comma
id|revs.objects
(braket
id|i
)braket
dot
id|name
comma
id|always
comma
id|allow_undefined
comma
id|data.name_only
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
