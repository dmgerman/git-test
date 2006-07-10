macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|name_rev_usage
r_static
r_const
r_char
id|name_rev_usage
(braket
)braket
op_assign
l_string|&quot;git-name-rev [--tags] ( --all | --stdin | committish [committish...] )&bslash;n&quot;
suffix:semicolon
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
DECL|member|merge_traversals
r_int
id|merge_traversals
suffix:semicolon
DECL|member|generation
r_int
id|generation
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
id|merge_traversals
comma
r_int
id|generation
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
id|name-&gt;merge_traversals
OG
id|merge_traversals
op_logical_or
(paren
id|name-&gt;merge_traversals
op_eq
id|merge_traversals
op_logical_and
id|name-&gt;generation
OG
id|generation
)paren
)paren
(brace
id|copy_data
suffix:colon
id|name-&gt;tip_name
op_assign
id|tip_name
suffix:semicolon
id|name-&gt;merge_traversals
op_assign
id|merge_traversals
suffix:semicolon
id|name-&gt;generation
op_assign
id|generation
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
l_int|8
)paren
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
l_string|&quot;%s~%d^%d&quot;
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
l_string|&quot;%s^%d&quot;
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
id|merge_traversals
op_plus
l_int|1
comma
l_int|0
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
id|merge_traversals
comma
id|generation
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|tags_only
r_static
r_int
id|tags_only
op_assign
l_int|0
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
r_int
id|deref
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tags_only
op_logical_and
id|strncmp
c_func
(paren
id|path
comma
l_string|&quot;refs/tags/&quot;
comma
l_int|10
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|o
op_logical_and
id|o-&gt;type
op_eq
id|TYPE_TAG
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
id|TYPE_COMMIT
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
op_logical_neg
id|strncmp
c_func
(paren
id|path
comma
l_string|&quot;refs/heads/&quot;
comma
l_int|11
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
id|strncmp
c_func
(paren
id|path
comma
l_string|&quot;refs/&quot;
comma
l_int|5
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
id|strdup
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
id|TYPE_COMMIT
)paren
r_return
l_string|&quot;undefined&quot;
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
l_string|&quot;undefined&quot;
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
l_string|&quot;%s~%d&quot;
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
r_struct
id|object_array
id|revs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|as_is
op_assign
l_int|0
comma
id|all
op_assign
l_int|0
comma
id|transform_stdin
op_assign
l_int|0
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
id|usage
c_func
(paren
id|name_rev_usage
)paren
suffix:semicolon
r_for
c_loop
(paren
op_decrement
id|argc
comma
op_increment
id|argv
suffix:semicolon
id|argc
suffix:semicolon
op_decrement
id|argc
comma
op_increment
id|argv
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
op_logical_neg
id|as_is
op_logical_and
(paren
op_star
id|argv
)paren
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
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|as_is
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;--tags&quot;
)paren
)paren
(brace
id|tags_only
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;--all&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Specify either a list, or --all, not both!&quot;
)paren
suffix:semicolon
id|all
op_assign
l_int|1
suffix:semicolon
id|cutoff
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|argv
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Specify either a list, or --stdin, not both!&quot;
)paren
suffix:semicolon
id|transform_stdin
op_assign
l_int|1
suffix:semicolon
id|cutoff
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|name_rev_usage
)paren
suffix:semicolon
)brace
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
id|TYPE_COMMIT
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
id|for_each_ref
c_func
(paren
id|name_ref
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
r_char
op_star
id|p
comma
op_star
id|p_start
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
r_int
id|forty
op_assign
l_int|0
suffix:semicolon
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
l_string|&quot;undefined&quot;
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
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;undefined&quot;
)paren
)paren
r_continue
suffix:semicolon
id|fwrite
c_func
(paren
id|p_start
comma
id|p
id|p_start
op_plus
l_int|1
comma
l_int|1
comma
id|stdout
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; (%s)&quot;
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
)paren
r_continue
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
id|get_rev_name
c_func
(paren
id|obj
)paren
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
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|revs.objects
(braket
id|i
)braket
dot
id|name
comma
id|get_rev_name
c_func
(paren
id|revs.objects
(braket
id|i
)braket
dot
id|item
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
