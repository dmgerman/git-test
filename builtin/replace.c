multiline_comment|/*&n; * Builtin &quot;git replace&quot;&n; *&n; * Copyright (c) 2008 Christian Couder &lt;chriscool@tuxfamily.org&gt;&n; *&n; * Based on builtin/tag.c by Kristian H&oslash;gsberg &lt;krh@redhat.com&gt;&n; * and Carlos Rica &lt;jasampler@gmail.com&gt; that was itself based on&n; * git-tag.sh and mktag.c by Linus Torvalds.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;tag.h&quot;
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
id|N_
c_func
(paren
l_string|&quot;git replace [-f] &lt;object&gt; &lt;replacement&gt;&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git replace [-f] --edit &lt;object&gt;&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git replace [-f] --graft &lt;commit&gt; [&lt;parent&gt;...]&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git replace -d &lt;object&gt;...&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;git replace [--format=&lt;format&gt;] [-l [&lt;pattern&gt;]]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|enum|replace_format
r_enum
id|replace_format
(brace
DECL|enumerator|REPLACE_FORMAT_SHORT
id|REPLACE_FORMAT_SHORT
comma
DECL|enumerator|REPLACE_FORMAT_MEDIUM
id|REPLACE_FORMAT_MEDIUM
comma
DECL|enumerator|REPLACE_FORMAT_LONG
id|REPLACE_FORMAT_LONG
)brace
suffix:semicolon
DECL|struct|show_data
r_struct
id|show_data
(brace
DECL|member|pattern
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|format
r_enum
id|replace_format
id|format
suffix:semicolon
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
r_struct
id|show_data
op_star
id|data
op_assign
id|cb_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wildmatch
c_func
(paren
id|data-&gt;pattern
comma
id|refname
comma
l_int|0
comma
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|data-&gt;format
op_eq
id|REPLACE_FORMAT_SHORT
)paren
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|refname
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|data-&gt;format
op_eq
id|REPLACE_FORMAT_MEDIUM
)paren
id|printf
c_func
(paren
l_string|&quot;%s -&gt; %s&bslash;n&quot;
comma
id|refname
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* data-&gt;format == REPLACE_FORMAT_LONG */
r_int
r_char
id|object
(braket
l_int|20
)braket
suffix:semicolon
r_enum
id|object_type
id|obj_type
comma
id|repl_type
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|refname
comma
id|object
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Failed to resolve &squot;%s&squot; as a valid ref.&quot;
comma
id|refname
)paren
suffix:semicolon
id|obj_type
op_assign
id|sha1_object_info
c_func
(paren
id|object
comma
l_int|NULL
)paren
suffix:semicolon
id|repl_type
op_assign
id|sha1_object_info
c_func
(paren
id|sha1
comma
l_int|NULL
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s (%s) -&gt; %s (%s)&bslash;n&quot;
comma
id|refname
comma
r_typename
(paren
id|obj_type
)paren
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
r_typename
(paren
id|repl_type
)paren
)paren
suffix:semicolon
)brace
)brace
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
comma
r_const
r_char
op_star
id|format
)paren
(brace
r_struct
id|show_data
id|data
suffix:semicolon
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
id|data.pattern
op_assign
id|pattern
suffix:semicolon
r_if
c_cond
(paren
id|format
op_eq
l_int|NULL
op_logical_or
op_star
id|format
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;short&quot;
)paren
)paren
id|data.format
op_assign
id|REPLACE_FORMAT_SHORT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;medium&quot;
)paren
)paren
id|data.format
op_assign
id|REPLACE_FORMAT_MEDIUM
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;long&quot;
)paren
)paren
id|data.format
op_assign
id|REPLACE_FORMAT_LONG
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;invalid replace format &squot;%s&squot;&bslash;n&quot;
l_string|&quot;valid formats are &squot;short&squot;, &squot;medium&squot; and &squot;long&squot;&bslash;n&quot;
comma
id|format
)paren
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
op_amp
id|data
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
comma
op_star
id|full_hex
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
id|get_sha1
c_func
(paren
op_star
id|p
comma
id|sha1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Failed to resolve &squot;%s&squot; as a valid ref.&quot;
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
id|full_hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
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
id|full_hex
)paren
suffix:semicolon
multiline_comment|/* read_ref() may reuse the buffer */
id|full_hex
op_assign
id|ref
op_plus
id|strlen
c_func
(paren
l_string|&quot;refs/replace/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_ref
c_func
(paren
id|ref
comma
id|sha1
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;replace ref &squot;%s&squot; not found.&quot;
comma
id|full_hex
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
id|full_hex
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
DECL|function|check_ref_valid
r_static
r_void
id|check_ref_valid
c_func
(paren
r_int
r_char
id|object
(braket
l_int|20
)braket
comma
r_int
r_char
id|prev
(braket
l_int|20
)braket
comma
r_char
op_star
id|ref
comma
r_int
id|ref_size
comma
r_int
id|force
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
id|ref_size
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
id|ref_size
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
id|check_refname_format
c_func
(paren
id|ref
comma
l_int|0
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
id|read_ref
c_func
(paren
id|ref
comma
id|prev
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
)brace
DECL|function|replace_object_sha1
r_static
r_int
id|replace_object_sha1
c_func
(paren
r_const
r_char
op_star
id|object_ref
comma
r_int
r_char
id|object
(braket
l_int|20
)braket
comma
r_const
r_char
op_star
id|replace_ref
comma
r_int
r_char
id|repl
(braket
l_int|20
)braket
comma
r_int
id|force
)paren
(brace
r_int
r_char
id|prev
(braket
l_int|20
)braket
suffix:semicolon
r_enum
id|object_type
id|obj_type
comma
id|repl_type
suffix:semicolon
r_char
id|ref
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|ref_transaction
op_star
id|transaction
suffix:semicolon
r_struct
id|strbuf
id|err
op_assign
id|STRBUF_INIT
suffix:semicolon
id|obj_type
op_assign
id|sha1_object_info
c_func
(paren
id|object
comma
l_int|NULL
)paren
suffix:semicolon
id|repl_type
op_assign
id|sha1_object_info
c_func
(paren
id|repl
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|force
op_logical_and
id|obj_type
op_ne
id|repl_type
)paren
id|die
c_func
(paren
l_string|&quot;Objects must be of the same type.&bslash;n&quot;
l_string|&quot;&squot;%s&squot; points to a replaced object of type &squot;%s&squot;&bslash;n&quot;
l_string|&quot;while &squot;%s&squot; points to a replacement object of type &squot;%s&squot;.&quot;
comma
id|object_ref
comma
r_typename
(paren
id|obj_type
)paren
comma
id|replace_ref
comma
r_typename
(paren
id|repl_type
)paren
)paren
suffix:semicolon
id|check_ref_valid
c_func
(paren
id|object
comma
id|prev
comma
id|ref
comma
r_sizeof
(paren
id|ref
)paren
comma
id|force
)paren
suffix:semicolon
id|transaction
op_assign
id|ref_transaction_begin
c_func
(paren
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transaction
op_logical_or
id|ref_transaction_update
c_func
(paren
id|transaction
comma
id|ref
comma
id|repl
comma
id|prev
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|err
)paren
op_logical_or
id|ref_transaction_commit
c_func
(paren
id|transaction
comma
op_amp
id|err
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s&quot;
comma
id|err.buf
)paren
suffix:semicolon
id|ref_transaction_free
c_func
(paren
id|transaction
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
id|repl
(braket
l_int|20
)braket
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
r_return
id|replace_object_sha1
c_func
(paren
id|object_ref
comma
id|object
comma
id|replace_ref
comma
id|repl
comma
id|force
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write the contents of the object named by &quot;sha1&quot; to the file &quot;filename&quot;.&n; * If &quot;raw&quot; is true, then the object&squot;s raw contents are printed according to&n; * &quot;type&quot;. Otherwise, we pretty-print the contents for human editing.&n; */
DECL|function|export_object
r_static
r_void
id|export_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_enum
id|object_type
id|type
comma
r_int
id|raw
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_struct
id|child_process
id|cmd
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_TRUNC
comma
l_int|0666
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to open %s for writing&quot;
comma
id|filename
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd.args
comma
l_string|&quot;--no-replace-objects&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd.args
comma
l_string|&quot;cat-file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raw
)paren
id|argv_array_push
c_func
(paren
op_amp
id|cmd.args
comma
r_typename
(paren
id|type
)paren
)paren
suffix:semicolon
r_else
id|argv_array_push
c_func
(paren
op_amp
id|cmd.args
comma
l_string|&quot;-p&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd.args
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|cmd.git_cmd
op_assign
l_int|1
suffix:semicolon
id|cmd.out
op_assign
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|run_command
c_func
(paren
op_amp
id|cmd
)paren
)paren
id|die
c_func
(paren
l_string|&quot;cat-file reported failure&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a previously-exported (and possibly edited) object back from &quot;filename&quot;,&n; * interpreting it as &quot;type&quot;, and writing the result to the object database.&n; * The sha1 of the written object is returned via sha1.&n; */
DECL|function|import_object
r_static
r_void
id|import_object
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_enum
id|object_type
id|type
comma
r_int
id|raw
comma
r_const
r_char
op_star
id|filename
)paren
(brace
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to open %s for reading&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw
op_logical_and
id|type
op_eq
id|OBJ_TREE
)paren
(brace
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;mktree&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|child_process
id|cmd
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
r_struct
id|strbuf
id|result
op_assign
id|STRBUF_INIT
suffix:semicolon
id|cmd.argv
op_assign
id|argv
suffix:semicolon
id|cmd.git_cmd
op_assign
l_int|1
suffix:semicolon
id|cmd.in
op_assign
id|fd
suffix:semicolon
id|cmd.out
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|cmd
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to spawn mktree&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strbuf_read
c_func
(paren
op_amp
id|result
comma
id|cmd.out
comma
l_int|41
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to read from mktree&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|cmd.out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|cmd
)paren
)paren
id|die
c_func
(paren
l_string|&quot;mktree reported failure&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|result.buf
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;mktree did not return an object name&quot;
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|result
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|flags
op_assign
id|HASH_FORMAT_CHECK
op_or
id|HASH_WRITE_OBJECT
suffix:semicolon
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;unable to fstat %s&quot;
comma
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index_fd
c_func
(paren
id|sha1
comma
id|fd
comma
op_amp
id|st
comma
id|type
comma
l_int|NULL
comma
id|flags
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to write object to database&quot;
)paren
suffix:semicolon
multiline_comment|/* index_fd close()s fd for us */
)brace
multiline_comment|/*&n;&t; * No need to close(fd) here; both run-command and index-fd&n;&t; * will have done it for us.&n;&t; */
)brace
DECL|function|edit_and_replace
r_static
r_int
id|edit_and_replace
c_func
(paren
r_const
r_char
op_star
id|object_ref
comma
r_int
id|force
comma
r_int
id|raw
)paren
(brace
r_char
op_star
id|tmpfile
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;REPLACE_EDITOBJ&quot;
)paren
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_int
r_char
id|old
(braket
l_int|20
)braket
comma
r_new
(braket
l_int|20
)braket
comma
id|prev
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
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|object_ref
comma
id|old
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;&quot;
comma
id|object_ref
)paren
suffix:semicolon
id|type
op_assign
id|sha1_object_info
c_func
(paren
id|old
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to get object type for %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|old
)paren
)paren
suffix:semicolon
id|check_ref_valid
c_func
(paren
id|old
comma
id|prev
comma
id|ref
comma
r_sizeof
(paren
id|ref
)paren
comma
id|force
)paren
suffix:semicolon
id|export_object
c_func
(paren
id|old
comma
id|type
comma
id|raw
comma
id|tmpfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|launch_editor
c_func
(paren
id|tmpfile
comma
l_int|NULL
comma
l_int|NULL
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;editing object file failed&quot;
)paren
suffix:semicolon
id|import_object
c_func
(paren
r_new
comma
id|type
comma
id|raw
comma
id|tmpfile
)paren
suffix:semicolon
id|free
c_func
(paren
id|tmpfile
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|old
comma
r_new
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;new object is the same as the old one: &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|old
)paren
)paren
suffix:semicolon
r_return
id|replace_object_sha1
c_func
(paren
id|object_ref
comma
id|old
comma
l_string|&quot;replacement&quot;
comma
r_new
comma
id|force
)paren
suffix:semicolon
)brace
DECL|function|replace_parents
r_static
r_void
id|replace_parents
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|strbuf
id|new_parents
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|parent_start
comma
op_star
id|parent_end
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* find existing parents */
id|parent_start
op_assign
id|buf-&gt;buf
suffix:semicolon
id|parent_start
op_add_assign
l_int|46
suffix:semicolon
multiline_comment|/* &quot;tree &quot; + &quot;hex sha1&quot; + &quot;&bslash;n&quot; */
id|parent_end
op_assign
id|parent_start
suffix:semicolon
r_while
c_loop
(paren
id|starts_with
c_func
(paren
id|parent_end
comma
l_string|&quot;parent &quot;
)paren
)paren
id|parent_end
op_add_assign
l_int|48
suffix:semicolon
multiline_comment|/* &quot;parent &quot; + &quot;hex sha1&quot; + &quot;&bslash;n&quot; */
multiline_comment|/* prepare new parents */
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
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
id|i
)braket
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;&quot;
)paren
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|lookup_commit_or_die
c_func
(paren
id|sha1
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|new_parents
comma
l_string|&quot;parent %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* replace existing parents with new ones */
id|strbuf_splice
c_func
(paren
id|buf
comma
id|parent_start
id|buf-&gt;buf
comma
id|parent_end
id|parent_start
comma
id|new_parents.buf
comma
id|new_parents.len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|new_parents
)paren
suffix:semicolon
)brace
DECL|struct|check_mergetag_data
r_struct
id|check_mergetag_data
(brace
DECL|member|argc
r_int
id|argc
suffix:semicolon
DECL|member|argv
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
)brace
suffix:semicolon
DECL|function|check_one_mergetag
r_static
r_void
id|check_one_mergetag
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit_extra_header
op_star
id|extra
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|check_mergetag_data
op_star
id|mergetag_data
op_assign
(paren
r_struct
id|check_mergetag_data
op_star
)paren
id|data
suffix:semicolon
r_const
r_char
op_star
id|ref
op_assign
id|mergetag_data-&gt;argv
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_char
id|tag_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|tag
op_star
id|tag
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hash_sha1_file
c_func
(paren
id|extra-&gt;value
comma
id|extra-&gt;len
comma
r_typename
(paren
id|OBJ_TAG
)paren
comma
id|tag_sha1
)paren
suffix:semicolon
id|tag
op_assign
id|lookup_tag
c_func
(paren
id|tag_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tag
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;bad mergetag in commit &squot;%s&squot;&quot;
)paren
comma
id|ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_tag_buffer
c_func
(paren
id|tag
comma
id|extra-&gt;value
comma
id|extra-&gt;len
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;malformed mergetag in commit &squot;%s&squot;&quot;
)paren
comma
id|ref
)paren
suffix:semicolon
multiline_comment|/* iterate over new parents */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|mergetag_data-&gt;argc
suffix:semicolon
id|i
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
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|mergetag_data-&gt;argv
(braket
id|i
)braket
comma
id|sha1
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;&quot;
)paren
comma
id|mergetag_data-&gt;argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|tag-&gt;tagged-&gt;sha1
comma
id|sha1
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* found */
)brace
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;original commit &squot;%s&squot; contains mergetag &squot;%s&squot; that is discarded; &quot;
l_string|&quot;use --edit instead of --graft&quot;
)paren
comma
id|ref
comma
id|sha1_to_hex
c_func
(paren
id|tag_sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|check_mergetags
r_static
r_void
id|check_mergetags
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
)paren
(brace
r_struct
id|check_mergetag_data
id|mergetag_data
suffix:semicolon
id|mergetag_data.argc
op_assign
id|argc
suffix:semicolon
id|mergetag_data.argv
op_assign
id|argv
suffix:semicolon
id|for_each_mergetag
c_func
(paren
id|check_one_mergetag
comma
id|commit
comma
op_amp
id|mergetag_data
)paren
suffix:semicolon
)brace
DECL|function|create_graft
r_static
r_int
id|create_graft
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
)paren
(brace
r_int
r_char
id|old
(braket
l_int|20
)braket
comma
r_new
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|old_ref
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|old_ref
comma
id|old
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Not a valid object name: &squot;%s&squot;&quot;
)paren
comma
id|old_ref
)paren
suffix:semicolon
id|commit
op_assign
id|lookup_commit_or_die
c_func
(paren
id|old
comma
id|old_ref
)paren
suffix:semicolon
id|buffer
op_assign
id|get_commit_buffer
c_func
(paren
id|commit
comma
op_amp
id|size
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|buf
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|unuse_commit_buffer
c_func
(paren
id|commit
comma
id|buffer
)paren
suffix:semicolon
id|replace_parents
c_func
(paren
op_amp
id|buf
comma
id|argc
l_int|1
comma
op_amp
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remove_signature
c_func
(paren
op_amp
id|buf
)paren
)paren
(brace
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;the original commit &squot;%s&squot; has a gpg signature.&quot;
)paren
comma
id|old_ref
)paren
suffix:semicolon
id|warning
c_func
(paren
id|_
c_func
(paren
l_string|&quot;the signature will be removed in the replacement commit!&quot;
)paren
)paren
suffix:semicolon
)brace
id|check_mergetags
c_func
(paren
id|commit
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_sha1_file
c_func
(paren
id|buf.buf
comma
id|buf.len
comma
id|commit_type
comma
r_new
)paren
)paren
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;could not write replacement commit for: &squot;%s&squot;&quot;
)paren
comma
id|old_ref
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|old
comma
r_new
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;new commit is the same as the old one: &squot;%s&squot;&quot;
comma
id|sha1_to_hex
c_func
(paren
id|old
)paren
)paren
suffix:semicolon
r_return
id|replace_object_sha1
c_func
(paren
id|old_ref
comma
id|old
comma
l_string|&quot;replacement&quot;
comma
r_new
comma
id|force
)paren
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
id|force
op_assign
l_int|0
suffix:semicolon
r_int
id|raw
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|format
op_assign
l_int|NULL
suffix:semicolon
r_enum
(brace
id|MODE_UNSPECIFIED
op_assign
l_int|0
comma
id|MODE_LIST
comma
id|MODE_DELETE
comma
id|MODE_EDIT
comma
id|MODE_GRAFT
comma
id|MODE_REPLACE
)brace
id|cmdmode
op_assign
id|MODE_UNSPECIFIED
suffix:semicolon
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT_CMDMODE
c_func
(paren
l_char|&squot;l&squot;
comma
l_string|&quot;list&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;list replace refs&quot;
)paren
comma
id|MODE_LIST
)paren
comma
id|OPT_CMDMODE
c_func
(paren
l_char|&squot;d&squot;
comma
l_string|&quot;delete&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;delete replace refs&quot;
)paren
comma
id|MODE_DELETE
)paren
comma
id|OPT_CMDMODE
c_func
(paren
l_char|&squot;e&squot;
comma
l_string|&quot;edit&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;edit existing object&quot;
)paren
comma
id|MODE_EDIT
)paren
comma
id|OPT_CMDMODE
c_func
(paren
l_char|&squot;g&squot;
comma
l_string|&quot;graft&quot;
comma
op_amp
id|cmdmode
comma
id|N_
c_func
(paren
l_string|&quot;change a commit&squot;s parents&quot;
)paren
comma
id|MODE_GRAFT
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;f&squot;
comma
l_string|&quot;force&quot;
comma
op_amp
id|force
comma
id|N_
c_func
(paren
l_string|&quot;replace the ref if it exists&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;raw&quot;
comma
op_amp
id|raw
comma
id|N_
c_func
(paren
l_string|&quot;do not pretty-print contents for --edit&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;format&quot;
comma
op_amp
id|format
comma
id|N_
c_func
(paren
l_string|&quot;format&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;use this format&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|check_replace_refs
op_assign
l_int|0
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
op_logical_neg
id|cmdmode
)paren
id|cmdmode
op_assign
id|argc
ques
c_cond
id|MODE_REPLACE
suffix:colon
id|MODE_LIST
suffix:semicolon
r_if
c_cond
(paren
id|format
op_logical_and
id|cmdmode
op_ne
id|MODE_LIST
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;--format cannot be used when not listing&quot;
comma
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
id|cmdmode
op_ne
id|MODE_REPLACE
op_logical_and
id|cmdmode
op_ne
id|MODE_EDIT
op_logical_and
id|cmdmode
op_ne
id|MODE_GRAFT
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;-f only makes sense when writing a replacement&quot;
comma
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|raw
op_logical_and
id|cmdmode
op_ne
id|MODE_EDIT
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;--raw only makes sense with --edit&quot;
comma
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmdmode
)paren
(brace
r_case
id|MODE_DELETE
suffix:colon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;-d needs at least one argument&quot;
comma
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
r_case
id|MODE_REPLACE
suffix:colon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;bad number of arguments&quot;
comma
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
r_case
id|MODE_EDIT
suffix:colon
r_if
c_cond
(paren
id|argc
op_ne
l_int|1
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;-e needs exactly one argument&quot;
comma
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_return
id|edit_and_replace
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|force
comma
id|raw
)paren
suffix:semicolon
r_case
id|MODE_GRAFT
suffix:colon
r_if
c_cond
(paren
id|argc
OL
l_int|1
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;-g needs at least one argument&quot;
comma
id|git_replace_usage
comma
id|options
)paren
suffix:semicolon
r_return
id|create_graft
c_func
(paren
id|argc
comma
id|argv
comma
id|force
)paren
suffix:semicolon
r_case
id|MODE_LIST
suffix:colon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage_msg_opt
c_func
(paren
l_string|&quot;only one pattern can be given with -l&quot;
comma
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
comma
id|format
)paren
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;BUG: invalid cmdmode %d&quot;
comma
(paren
r_int
)paren
id|cmdmode
)paren
suffix:semicolon
)brace
)brace
eof
