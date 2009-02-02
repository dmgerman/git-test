multiline_comment|/*&n; * Builtin &quot;git replace&quot;&n; *&n; * Copyright (c) 2008 Christian Couder &lt;chriscool@tuxfamily.org&gt;&n; *&n; * Based on builtin-tag.c by Kristian H&oslash;gsberg &lt;krh@redhat.com&gt;&n; * and Carlos Rica &lt;jasampler@gmail.com&gt; that was itself based on&n; * git-tag.sh and mktag.c by Linus Torvalds.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|git_replace_usage
r_static
r_const
r_char
op_star
r_const
id|git_replace_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git replace [-f] &lt;object&gt; &lt;replacement&gt;&quot;
comma
l_string|&quot;git replace -d &lt;object&gt;...&quot;
comma
l_string|&quot;git replace -l [&lt;pattern&gt;]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|show_reference
r_static
r_int
id|show_reference
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
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
r_const
r_char
op_star
id|pattern
op_assign
id|cb_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fnmatch
c_func
(paren
id|pattern
comma
id|refname
comma
l_int|0
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|refname
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|list_replace_refs
r_static
r_int
id|list_replace_refs
c_func
(paren
r_const
r_char
op_star
id|pattern
)paren
(brace
r_if
c_cond
(paren
id|pattern
op_eq
l_int|NULL
)paren
id|pattern
op_assign
l_string|&quot;*&quot;
suffix:semicolon
id|for_each_replace_ref
c_func
(paren
id|show_reference
comma
(paren
r_void
op_star
)paren
id|pattern
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|typedef|each_replace_name_fn
r_typedef
r_int
(paren
op_star
id|each_replace_name_fn
)paren
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
suffix:semicolon
DECL|function|for_each_replace_name
r_static
r_int
id|for_each_replace_name
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
comma
id|each_replace_name_fn
id|fn
)paren
(brace
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
r_char
id|ref
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|had_error
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|argv
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|ref
comma
r_sizeof
(paren
id|ref
)paren
comma
l_string|&quot;refs/replace/%s&quot;
comma
op_star
id|p
)paren
op_ge
r_sizeof
(paren
id|ref
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;replace ref name too long: %.*s...&quot;
comma
l_int|50
comma
op_star
id|p
)paren
suffix:semicolon
id|had_error
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
id|resolve_ref
c_func
(paren
id|ref
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
l_string|&quot;replace ref &squot;%s&squot; not found.&quot;
comma
op_star
id|p
)paren
suffix:semicolon
id|had_error
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fn
c_func
(paren
op_star
id|p
comma
id|ref
comma
id|sha1
)paren
)paren
id|had_error
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|had_error
suffix:semicolon
)brace
DECL|function|delete_replace_ref
r_static
r_int
id|delete_replace_ref
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
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_if
c_cond
(paren
id|delete_ref
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Deleted replace ref &squot;%s&squot;&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|replace_object
r_static
r_int
id|replace_object
c_func
(paren
r_const
r_char
op_star
id|object_ref
comma
r_const
r_char
op_star
id|replace_ref
comma
r_int
id|force
)paren
(brace
r_int
r_char
id|object
(braket
l_int|20
)braket
comma
id|prev
(braket
l_int|20
)braket
comma
id|repl
(braket
l_int|20
)braket
suffix:semicolon
r_char
id|ref
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|ref_lock
op_star
id|lock
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|object_ref
comma
id|object
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Failed to resolve &squot;%s&squot; as a valid ref.&quot;
comma
id|object_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|replace_ref
comma
id|repl
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Failed to resolve &squot;%s&squot; as a valid ref.&quot;
comma
id|replace_ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|ref
comma
r_sizeof
(paren
id|ref
)paren
comma
l_string|&quot;refs/replace/%s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|object
)paren
)paren
OG
r_sizeof
(paren
id|ref
)paren
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;replace ref name too long: %.*s...&quot;
comma
l_int|50
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_ref_format
c_func
(paren
id|ref
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not a valid ref name.&quot;
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|ref
comma
id|prev
comma
l_int|1
comma
l_int|NULL
)paren
)paren
id|hashclr
c_func
(paren
id|prev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
id|die
c_func
(paren
l_string|&quot;replace ref &squot;%s&squot; already exists&quot;
comma
id|ref
)paren
suffix:semicolon
id|lock
op_assign
id|lock_any_ref_for_update
c_func
(paren
id|ref
comma
id|prev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock
)paren
id|die
c_func
(paren
l_string|&quot;%s: cannot lock the ref&quot;
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_ref_sha1
c_func
(paren
id|lock
comma
id|repl
comma
l_int|NULL
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;%s: cannot update the ref&quot;
comma
id|ref
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmd_replace
r_int
id|cmd_replace
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
id|list
op_assign
l_int|0
comma
r_delete
op_assign
l_int|0
comma
id|force
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;l&squot;
comma
l_int|NULL
comma
op_amp
id|list
comma
l_string|&quot;list replace refs&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
r_delete
comma
l_string|&quot;delete replace refs&quot;
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
id|force
comma
l_string|&quot;replace the ref if it exists&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
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
id|options
comma
id|git_replace_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list
op_logical_and
r_delete
)paren
id|usage_with_options
c_func
(paren
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|force
op_logical_and
(paren
id|list
op_logical_or
r_delete
)paren
)paren
id|usage_with_options
c_func
(paren
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
multiline_comment|/* Delete refs */
r_if
c_cond
(paren
r_delete
)paren
(brace
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_return
id|for_each_replace_name
c_func
(paren
id|argv
comma
id|delete_replace_ref
)paren
suffix:semicolon
)brace
multiline_comment|/* Replace object */
r_if
c_cond
(paren
op_logical_neg
id|list
op_logical_and
id|argc
)paren
(brace
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage_with_options
c_func
(paren
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_return
id|replace_object
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
id|force
)paren
suffix:semicolon
)brace
multiline_comment|/* List refs, even if &quot;list&quot; is not set */
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage_with_options
c_func
(paren
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
id|usage_with_options
c_func
(paren
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_return
id|list_replace_refs
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
eof
