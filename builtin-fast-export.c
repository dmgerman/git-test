multiline_comment|/*&n; * &quot;git fast-export&quot; builtin command&n; *&n; * Copyright (C) 2007 Johannes E. Schindelin&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
macro_line|#include &quot;log-tree.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;decorate.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;parse-options.h&quot;
DECL|variable|fast_export_usage
r_static
r_const
r_char
op_star
id|fast_export_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git fast-export [rev-list-opts]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|progress
r_static
r_int
id|progress
suffix:semicolon
DECL|enumerator|ABORT
DECL|enumerator|VERBATIM
DECL|enumerator|WARN
DECL|enumerator|STRIP
DECL|variable|signed_tag_mode
r_static
r_enum
(brace
id|ABORT
comma
id|VERBATIM
comma
id|WARN
comma
id|STRIP
)brace
id|signed_tag_mode
op_assign
id|ABORT
suffix:semicolon
DECL|enumerator|ERROR
DECL|enumerator|DROP
DECL|enumerator|REWRITE
DECL|variable|tag_of_filtered_mode
r_static
r_enum
(brace
id|ERROR
comma
id|DROP
comma
id|REWRITE
)brace
id|tag_of_filtered_mode
op_assign
id|ABORT
suffix:semicolon
DECL|variable|fake_missing_tagger
r_static
r_int
id|fake_missing_tagger
suffix:semicolon
DECL|function|parse_opt_signed_tag_mode
r_static
r_int
id|parse_opt_signed_tag_mode
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
r_if
c_cond
(paren
id|unset
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;abort&quot;
)paren
)paren
id|signed_tag_mode
op_assign
id|ABORT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;verbatim&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;ignore&quot;
)paren
)paren
id|signed_tag_mode
op_assign
id|VERBATIM
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;warn&quot;
)paren
)paren
id|signed_tag_mode
op_assign
id|WARN
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;strip&quot;
)paren
)paren
id|signed_tag_mode
op_assign
id|STRIP
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;Unknown signed-tag mode: %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_opt_tag_of_filtered_mode
r_static
r_int
id|parse_opt_tag_of_filtered_mode
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
r_if
c_cond
(paren
id|unset
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;abort&quot;
)paren
)paren
id|tag_of_filtered_mode
op_assign
id|ABORT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;drop&quot;
)paren
)paren
id|tag_of_filtered_mode
op_assign
id|DROP
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;rewrite&quot;
)paren
)paren
id|tag_of_filtered_mode
op_assign
id|REWRITE
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;Unknown tag-of-filtered mode: %s&quot;
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|idnums
r_static
r_struct
id|decoration
id|idnums
suffix:semicolon
DECL|variable|last_idnum
r_static
r_uint32
id|last_idnum
suffix:semicolon
DECL|function|has_unshown_parent
r_static
r_int
id|has_unshown_parent
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|commit_list
op_star
id|parent
suffix:semicolon
r_for
c_loop
(paren
id|parent
op_assign
id|commit-&gt;parents
suffix:semicolon
id|parent
suffix:semicolon
id|parent
op_assign
id|parent-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|parent-&gt;item-&gt;object.flags
op_amp
id|SHOWN
)paren
op_logical_and
op_logical_neg
(paren
id|parent-&gt;item-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Since intptr_t is C99, we do not use it here */
DECL|function|mark_to_ptr
r_static
r_inline
r_uint32
op_star
id|mark_to_ptr
c_func
(paren
r_uint32
id|mark
)paren
(brace
r_return
(paren
(paren
r_uint32
op_star
)paren
l_int|NULL
)paren
op_plus
id|mark
suffix:semicolon
)brace
DECL|function|ptr_to_mark
r_static
r_inline
r_uint32
id|ptr_to_mark
c_func
(paren
r_void
op_star
id|mark
)paren
(brace
r_return
(paren
r_uint32
op_star
)paren
id|mark
(paren
r_uint32
op_star
)paren
l_int|NULL
suffix:semicolon
)brace
DECL|function|mark_object
r_static
r_inline
r_void
id|mark_object
c_func
(paren
r_struct
id|object
op_star
id|object
comma
r_uint32
id|mark
)paren
(brace
id|add_decoration
c_func
(paren
op_amp
id|idnums
comma
id|object
comma
id|mark_to_ptr
c_func
(paren
id|mark
)paren
)paren
suffix:semicolon
)brace
DECL|function|mark_next_object
r_static
r_inline
r_void
id|mark_next_object
c_func
(paren
r_struct
id|object
op_star
id|object
)paren
(brace
id|mark_object
c_func
(paren
id|object
comma
op_increment
id|last_idnum
)paren
suffix:semicolon
)brace
DECL|function|get_object_mark
r_static
r_int
id|get_object_mark
c_func
(paren
r_struct
id|object
op_star
id|object
)paren
(brace
r_void
op_star
id|decoration
op_assign
id|lookup_decoration
c_func
(paren
op_amp
id|idnums
comma
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|decoration
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ptr_to_mark
c_func
(paren
id|decoration
)paren
suffix:semicolon
)brace
DECL|function|show_progress
r_static
r_void
id|show_progress
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|counter
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|progress
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
op_increment
id|counter
op_mod
id|progress
)paren
op_eq
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;progress %d objects&bslash;n&quot;
comma
id|counter
)paren
suffix:semicolon
)brace
DECL|function|handle_object
r_static
r_void
id|handle_object
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_struct
id|object
op_star
id|object
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|sha1
)paren
)paren
r_return
suffix:semicolon
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
id|die
(paren
l_string|&quot;Could not read blob %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|object-&gt;flags
op_amp
id|SHOWN
)paren
r_return
suffix:semicolon
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
(paren
l_string|&quot;Could not read blob %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|mark_next_object
c_func
(paren
id|object
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;blob&bslash;nmark :%&quot;
id|PRIu32
l_string|&quot;&bslash;ndata %lu&bslash;n&quot;
comma
id|last_idnum
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_logical_and
id|fwrite
c_func
(paren
id|buf
comma
id|size
comma
l_int|1
comma
id|stdout
)paren
op_ne
l_int|1
)paren
id|die
(paren
l_string|&quot;Could not write blob %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|show_progress
c_func
(paren
)paren
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|SHOWN
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|show_filemodify
r_static
r_void
id|show_filemodify
c_func
(paren
r_struct
id|diff_queue_struct
op_star
id|q
comma
r_struct
id|diff_options
op_star
id|options
comma
r_void
op_star
id|data
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
id|q-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|diff_filespec
op_star
id|ospec
op_assign
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|one
suffix:semicolon
r_struct
id|diff_filespec
op_star
id|spec
op_assign
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|two
suffix:semicolon
r_switch
c_cond
(paren
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|status
)paren
(brace
r_case
id|DIFF_STATUS_DELETED
suffix:colon
id|printf
c_func
(paren
l_string|&quot;D %s&bslash;n&quot;
comma
id|spec-&gt;path
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIFF_STATUS_COPIED
suffix:colon
r_case
id|DIFF_STATUS_RENAMED
suffix:colon
id|printf
c_func
(paren
l_string|&quot;%c &bslash;&quot;%s&bslash;&quot; &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|status
comma
id|ospec-&gt;path
comma
id|spec-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|ospec-&gt;sha1
comma
id|spec-&gt;sha1
)paren
op_logical_and
id|ospec-&gt;mode
op_eq
id|spec-&gt;mode
)paren
r_break
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
id|DIFF_STATUS_TYPE_CHANGED
suffix:colon
r_case
id|DIFF_STATUS_MODIFIED
suffix:colon
r_case
id|DIFF_STATUS_ADDED
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Links refer to objects in another repositories;&n;&t;&t;&t; * output the SHA-1 verbatim.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|S_ISGITLINK
c_func
(paren
id|spec-&gt;mode
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;M %06o %s %s&bslash;n&quot;
comma
id|spec-&gt;mode
comma
id|sha1_to_hex
c_func
(paren
id|spec-&gt;sha1
)paren
comma
id|spec-&gt;path
)paren
suffix:semicolon
r_else
(brace
r_struct
id|object
op_star
id|object
op_assign
id|lookup_object
c_func
(paren
id|spec-&gt;sha1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;M %06o :%d %s&bslash;n&quot;
comma
id|spec-&gt;mode
comma
id|get_object_mark
c_func
(paren
id|object
)paren
comma
id|spec-&gt;path
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;Unexpected comparison status &squot;%c&squot; for %s, %s&quot;
comma
id|q-&gt;queue
(braket
id|i
)braket
op_member_access_from_pointer
id|status
comma
id|ospec-&gt;path
ques
c_cond
id|ospec-&gt;path
suffix:colon
l_string|&quot;none&quot;
comma
id|spec-&gt;path
ques
c_cond
id|spec-&gt;path
suffix:colon
l_string|&quot;none&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|find_encoding
r_static
r_const
r_char
op_star
id|find_encoding
c_func
(paren
r_const
r_char
op_star
id|begin
comma
r_const
r_char
op_star
id|end
)paren
(brace
r_const
r_char
op_star
id|needle
op_assign
l_string|&quot;&bslash;nencoding &quot;
suffix:semicolon
r_char
op_star
id|bol
comma
op_star
id|eol
suffix:semicolon
id|bol
op_assign
id|memmem
c_func
(paren
id|begin
comma
id|end
ques
c_cond
id|end
id|begin
suffix:colon
id|strlen
c_func
(paren
id|begin
)paren
comma
id|needle
comma
id|strlen
c_func
(paren
id|needle
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bol
)paren
r_return
id|git_commit_encoding
suffix:semicolon
id|bol
op_add_assign
id|strlen
c_func
(paren
id|needle
)paren
suffix:semicolon
id|eol
op_assign
id|strchrnul
c_func
(paren
id|bol
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
op_star
id|eol
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|bol
suffix:semicolon
)brace
DECL|function|handle_commit
r_static
r_void
id|handle_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|rev_info
op_star
id|rev
)paren
(brace
r_int
id|saved_output_format
op_assign
id|rev-&gt;diffopt.output_format
suffix:semicolon
r_const
r_char
op_star
id|author
comma
op_star
id|author_end
comma
op_star
id|committer
comma
op_star
id|committer_end
suffix:semicolon
r_const
r_char
op_star
id|encoding
comma
op_star
id|message
suffix:semicolon
r_char
op_star
id|reencoded
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|rev-&gt;diffopt.output_format
op_assign
id|DIFF_FORMAT_CALLBACK
suffix:semicolon
id|parse_commit
c_func
(paren
id|commit
)paren
suffix:semicolon
id|author
op_assign
id|strstr
c_func
(paren
id|commit-&gt;buffer
comma
l_string|&quot;&bslash;nauthor &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|author
)paren
id|die
(paren
l_string|&quot;Could not find author in commit %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|author
op_increment
suffix:semicolon
id|author_end
op_assign
id|strchrnul
c_func
(paren
id|author
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|committer
op_assign
id|strstr
c_func
(paren
id|author_end
comma
l_string|&quot;&bslash;ncommitter &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|committer
)paren
id|die
(paren
l_string|&quot;Could not find committer in commit %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|committer
op_increment
suffix:semicolon
id|committer_end
op_assign
id|strchrnul
c_func
(paren
id|committer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|message
op_assign
id|strstr
c_func
(paren
id|committer_end
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|encoding
op_assign
id|find_encoding
c_func
(paren
id|committer_end
comma
id|message
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
id|message
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;parents
op_logical_and
id|get_object_mark
c_func
(paren
op_amp
id|commit-&gt;parents-&gt;item-&gt;object
)paren
op_ne
l_int|0
)paren
(brace
id|parse_commit
c_func
(paren
id|commit-&gt;parents-&gt;item
)paren
suffix:semicolon
id|diff_tree_sha1
c_func
(paren
id|commit-&gt;parents-&gt;item-&gt;tree-&gt;object.sha1
comma
id|commit-&gt;tree-&gt;object.sha1
comma
l_string|&quot;&quot;
comma
op_amp
id|rev-&gt;diffopt
)paren
suffix:semicolon
)brace
r_else
id|diff_root_tree_sha1
c_func
(paren
id|commit-&gt;tree-&gt;object.sha1
comma
l_string|&quot;&quot;
comma
op_amp
id|rev-&gt;diffopt
)paren
suffix:semicolon
multiline_comment|/* Export the referenced blobs, and remember the marks. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|diff_queued_diff.nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|S_ISGITLINK
c_func
(paren
id|diff_queued_diff.queue
(braket
id|i
)braket
op_member_access_from_pointer
id|two-&gt;mode
)paren
)paren
id|handle_object
c_func
(paren
id|diff_queued_diff.queue
(braket
id|i
)braket
op_member_access_from_pointer
id|two-&gt;sha1
)paren
suffix:semicolon
id|mark_next_object
c_func
(paren
op_amp
id|commit-&gt;object
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_encoding_utf8
c_func
(paren
id|encoding
)paren
)paren
id|reencoded
op_assign
id|reencode_string
c_func
(paren
id|message
comma
l_string|&quot;UTF-8&quot;
comma
id|encoding
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;parents
)paren
id|printf
c_func
(paren
l_string|&quot;reset %s&bslash;n&quot;
comma
(paren
r_const
r_char
op_star
)paren
id|commit-&gt;util
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;commit %s&bslash;nmark :%&quot;
id|PRIu32
l_string|&quot;&bslash;n%.*s&bslash;n%.*s&bslash;ndata %u&bslash;n%s&quot;
comma
(paren
r_const
r_char
op_star
)paren
id|commit-&gt;util
comma
id|last_idnum
comma
(paren
r_int
)paren
(paren
id|author_end
id|author
)paren
comma
id|author
comma
(paren
r_int
)paren
(paren
id|committer_end
id|committer
)paren
comma
id|committer
comma
(paren
r_int
)paren
(paren
id|reencoded
ques
c_cond
id|strlen
c_func
(paren
id|reencoded
)paren
suffix:colon
id|message
ques
c_cond
id|strlen
c_func
(paren
id|message
)paren
suffix:colon
l_int|0
)paren
comma
id|reencoded
ques
c_cond
id|reencoded
suffix:colon
id|message
ques
c_cond
id|message
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|reencoded
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
id|commit-&gt;parents
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_int
id|mark
op_assign
id|get_object_mark
c_func
(paren
op_amp
id|p-&gt;item-&gt;object
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mark
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;from :%d&bslash;n&quot;
comma
id|mark
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;merge :%d&bslash;n&quot;
comma
id|mark
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|log_tree_diff_flush
c_func
(paren
id|rev
)paren
suffix:semicolon
id|rev-&gt;diffopt.output_format
op_assign
id|saved_output_format
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|show_progress
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|handle_tail
r_static
r_void
id|handle_tail
c_func
(paren
r_struct
id|object_array
op_star
id|commits
comma
r_struct
id|rev_info
op_star
id|revs
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_while
c_loop
(paren
id|commits-&gt;nr
)paren
(brace
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|commits-&gt;objects
(braket
id|commits-&gt;nr
l_int|1
)braket
dot
id|item
suffix:semicolon
r_if
c_cond
(paren
id|has_unshown_parent
c_func
(paren
id|commit
)paren
)paren
r_return
suffix:semicolon
id|handle_commit
c_func
(paren
id|commit
comma
id|revs
)paren
suffix:semicolon
id|commits-&gt;nr
op_decrement
suffix:semicolon
)brace
)brace
DECL|function|handle_tag
r_static
r_void
id|handle_tag
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|tag
op_star
id|tag
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_const
r_char
op_star
id|tagger
comma
op_star
id|tagger_end
comma
op_star
id|message
suffix:semicolon
r_int
id|message_size
op_assign
l_int|0
suffix:semicolon
r_struct
id|object
op_star
id|tagged
suffix:semicolon
r_int
id|tagged_mark
suffix:semicolon
r_struct
id|commit
op_star
id|p
suffix:semicolon
multiline_comment|/* Trees have no identifer in fast-export output, thus we have no way&n;&t; * to output tags of trees, tags of tags of trees, etc.  Simply omit&n;&t; * such tags.&n;&t; */
id|tagged
op_assign
id|tag-&gt;tagged
suffix:semicolon
r_while
c_loop
(paren
id|tagged-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|tagged
op_assign
(paren
(paren
r_struct
id|tag
op_star
)paren
id|tagged
)paren
op_member_access_from_pointer
id|tagged
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tagged-&gt;type
op_eq
id|OBJ_TREE
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;Omitting tag %s,&bslash;nsince tags of trees (or tags of tags of trees, etc.) are not supported.&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|buf
op_assign
id|read_sha1_file
c_func
(paren
id|tag-&gt;object.sha1
comma
op_amp
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
(paren
l_string|&quot;Could not read tag %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|message
op_assign
id|memmem
c_func
(paren
id|buf
comma
id|size
comma
l_string|&quot;&bslash;n&bslash;n&quot;
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|message
)paren
(brace
id|message
op_add_assign
l_int|2
suffix:semicolon
id|message_size
op_assign
id|strlen
c_func
(paren
id|message
)paren
suffix:semicolon
)brace
id|tagger
op_assign
id|memmem
c_func
(paren
id|buf
comma
id|message
ques
c_cond
id|message
id|buf
suffix:colon
id|size
comma
l_string|&quot;&bslash;ntagger &quot;
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tagger
)paren
(brace
r_if
c_cond
(paren
id|fake_missing_tagger
)paren
id|tagger
op_assign
l_string|&quot;tagger Unspecified Tagger &quot;
l_string|&quot;&lt;unspecified-tagger&gt; 0 +0000&quot;
suffix:semicolon
r_else
id|tagger
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|tagger_end
op_assign
id|tagger
op_plus
id|strlen
c_func
(paren
id|tagger
)paren
suffix:semicolon
)brace
r_else
(brace
id|tagger
op_increment
suffix:semicolon
id|tagger_end
op_assign
id|strchrnul
c_func
(paren
id|tagger
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/* handle signed tags */
r_if
c_cond
(paren
id|message
)paren
(brace
r_const
r_char
op_star
id|signature
op_assign
id|strstr
c_func
(paren
id|message
comma
l_string|&quot;&bslash;n-----BEGIN PGP SIGNATURE-----&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signature
)paren
r_switch
c_cond
(paren
id|signed_tag_mode
)paren
(brace
r_case
id|ABORT
suffix:colon
id|die
(paren
l_string|&quot;Encountered signed tag %s; use &quot;
l_string|&quot;--signed-tag=&lt;mode&gt; to handle it.&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_case
id|WARN
suffix:colon
id|warning
(paren
l_string|&quot;Exporting signed tag %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
multiline_comment|/* fallthru */
r_case
id|VERBATIM
suffix:colon
r_break
suffix:semicolon
r_case
id|STRIP
suffix:colon
id|message_size
op_assign
id|signature
op_plus
l_int|1
id|message
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* handle tag-&gt;tagged having been filtered out due to paths specified */
id|tagged
op_assign
id|tag-&gt;tagged
suffix:semicolon
id|tagged_mark
op_assign
id|get_object_mark
c_func
(paren
id|tagged
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tagged_mark
)paren
(brace
r_switch
c_cond
(paren
id|tag_of_filtered_mode
)paren
(brace
r_case
id|ABORT
suffix:colon
id|die
(paren
l_string|&quot;Tag %s tags unexported object; use &quot;
l_string|&quot;--tag-of-filtered-object=&lt;mode&gt; to handle it.&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_case
id|DROP
suffix:colon
multiline_comment|/* Ignore this tag altogether */
r_return
suffix:semicolon
r_case
id|REWRITE
suffix:colon
r_if
c_cond
(paren
id|tagged-&gt;type
op_ne
id|OBJ_COMMIT
)paren
(brace
id|die
(paren
l_string|&quot;Tag %s tags unexported %s!&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
comma
r_typename
(paren
id|tagged-&gt;type
)paren
)paren
suffix:semicolon
)brace
id|p
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|tagged
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;parents
op_logical_and
id|p-&gt;parents-&gt;next
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;object.flags
op_amp
id|TREESAME
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;parents
)paren
id|die
(paren
l_string|&quot;Can&squot;t find replacement commit for tag %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|tag-&gt;object.sha1
)paren
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;parents-&gt;item
suffix:semicolon
)brace
id|tagged_mark
op_assign
id|get_object_mark
c_func
(paren
op_amp
id|p-&gt;object
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/tags/&quot;
)paren
)paren
id|name
op_add_assign
l_int|10
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;tag %s&bslash;nfrom :%d&bslash;n%.*s%sdata %d&bslash;n%.*s&bslash;n&quot;
comma
id|name
comma
id|tagged_mark
comma
(paren
r_int
)paren
(paren
id|tagger_end
id|tagger
)paren
comma
id|tagger
comma
id|tagger
op_eq
id|tagger_end
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;&bslash;n&quot;
comma
(paren
r_int
)paren
id|message_size
comma
(paren
r_int
)paren
id|message_size
comma
id|message
ques
c_cond
id|message
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|function|get_tags_and_duplicates
r_static
r_void
id|get_tags_and_duplicates
c_func
(paren
r_struct
id|object_array
op_star
id|pending
comma
r_struct
id|string_list
op_star
id|extra_refs
)paren
(brace
r_struct
id|tag
op_star
id|tag
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
id|i
OL
id|pending-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object_array_entry
op_star
id|e
op_assign
id|pending-&gt;objects
op_plus
id|i
suffix:semicolon
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
op_assign
id|commit
suffix:semicolon
r_char
op_star
id|full_name
suffix:semicolon
r_if
c_cond
(paren
id|dwim_ref
c_func
(paren
id|e-&gt;name
comma
id|strlen
c_func
(paren
id|e-&gt;name
)paren
comma
id|sha1
comma
op_amp
id|full_name
)paren
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|e-&gt;item-&gt;type
)paren
(brace
r_case
id|OBJ_COMMIT
suffix:colon
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|e-&gt;item
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_TAG
suffix:colon
id|tag
op_assign
(paren
r_struct
id|tag
op_star
)paren
id|e-&gt;item
suffix:semicolon
multiline_comment|/* handle nested tags */
r_while
c_loop
(paren
id|tag
op_logical_and
id|tag-&gt;object.type
op_eq
id|OBJ_TAG
)paren
(brace
id|parse_object
c_func
(paren
id|tag-&gt;object.sha1
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
id|full_name
comma
id|extra_refs
)paren
op_member_access_from_pointer
id|util
op_assign
id|tag
suffix:semicolon
id|tag
op_assign
(paren
r_struct
id|tag
op_star
)paren
id|tag-&gt;tagged
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tag
)paren
id|die
(paren
l_string|&quot;Tag %s points nowhere?&quot;
comma
id|e-&gt;name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tag-&gt;object.type
)paren
(brace
r_case
id|OBJ_COMMIT
suffix:colon
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|tag
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_BLOB
suffix:colon
id|handle_object
c_func
(paren
id|tag-&gt;object.sha1
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* OBJ_TAG (nested tags) is already handled */
id|warning
c_func
(paren
l_string|&quot;Tag points to object of unexpected type %s, skipping.&quot;
comma
r_typename
(paren
id|tag-&gt;object.type
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|warning
c_func
(paren
l_string|&quot;%s: Unexpected object of type %s, skipping.&quot;
comma
id|e-&gt;name
comma
r_typename
(paren
id|e-&gt;item-&gt;type
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|commit-&gt;util
)paren
multiline_comment|/* more than one name for the same object */
id|string_list_append
c_func
(paren
id|full_name
comma
id|extra_refs
)paren
op_member_access_from_pointer
id|util
op_assign
id|commit
suffix:semicolon
r_else
id|commit-&gt;util
op_assign
id|full_name
suffix:semicolon
)brace
)brace
DECL|function|handle_tags_and_duplicates
r_static
r_void
id|handle_tags_and_duplicates
c_func
(paren
r_struct
id|string_list
op_star
id|extra_refs
)paren
(brace
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|extra_refs-&gt;nr
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|extra_refs-&gt;items
(braket
id|i
)braket
dot
id|string
suffix:semicolon
r_struct
id|object
op_star
id|object
op_assign
id|extra_refs-&gt;items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
r_switch
c_cond
(paren
id|object-&gt;type
)paren
(brace
r_case
id|OBJ_TAG
suffix:colon
id|handle_tag
c_func
(paren
id|name
comma
(paren
r_struct
id|tag
op_star
)paren
id|object
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OBJ_COMMIT
suffix:colon
multiline_comment|/* create refs pointing to already seen commits */
id|commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|object
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;reset %s&bslash;nfrom :%d&bslash;n&bslash;n&quot;
comma
id|name
comma
id|get_object_mark
c_func
(paren
op_amp
id|commit-&gt;object
)paren
)paren
suffix:semicolon
id|show_progress
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|export_marks
r_static
r_void
id|export_marks
c_func
(paren
r_char
op_star
id|file
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_uint32
id|mark
suffix:semicolon
r_struct
id|object_decoration
op_star
id|deco
op_assign
id|idnums.hash
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
id|f
op_assign
id|fopen
c_func
(paren
id|file
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
id|error
c_func
(paren
l_string|&quot;Unable to open marks file %s for writing&quot;
comma
id|file
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
id|idnums.size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|deco-&gt;base
op_logical_and
id|deco-&gt;base-&gt;type
op_eq
l_int|1
)paren
(brace
id|mark
op_assign
id|ptr_to_mark
c_func
(paren
id|deco-&gt;decoration
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|f
comma
l_string|&quot;:%&quot;
id|PRIu32
l_string|&quot; %s&bslash;n&quot;
comma
id|mark
comma
id|sha1_to_hex
c_func
(paren
id|deco-&gt;base-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
id|deco
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ferror
c_func
(paren
id|f
)paren
op_logical_or
id|fclose
c_func
(paren
id|f
)paren
)paren
id|error
c_func
(paren
l_string|&quot;Unable to write marks file %s.&quot;
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|import_marks
r_static
r_void
id|import_marks
c_func
(paren
r_char
op_star
id|input_file
)paren
(brace
r_char
id|line
(braket
l_int|512
)braket
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|input_file
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
id|die
c_func
(paren
l_string|&quot;cannot read %s: %s&quot;
comma
id|input_file
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|f
)paren
)paren
(brace
r_uint32
id|mark
suffix:semicolon
r_char
op_star
id|line_end
comma
op_star
id|mark_end
suffix:semicolon
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
id|object
suffix:semicolon
id|line_end
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_ne
l_char|&squot;:&squot;
op_logical_or
op_logical_neg
id|line_end
)paren
id|die
c_func
(paren
l_string|&quot;corrupt mark line: %s&quot;
comma
id|line
)paren
suffix:semicolon
op_star
id|line_end
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|mark
op_assign
id|strtoumax
c_func
(paren
id|line
op_plus
l_int|1
comma
op_amp
id|mark_end
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mark
op_logical_or
id|mark_end
op_eq
id|line
op_plus
l_int|1
op_logical_or
op_star
id|mark_end
op_ne
l_char|&squot; &squot;
op_logical_or
id|get_sha1
c_func
(paren
id|mark_end
op_plus
l_int|1
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;corrupt mark line: %s&quot;
comma
id|line
)paren
suffix:semicolon
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
id|die
(paren
l_string|&quot;Could not read blob %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|object-&gt;flags
op_amp
id|SHOWN
)paren
id|error
c_func
(paren
l_string|&quot;Object %s already has a mark&quot;
comma
id|sha1
)paren
suffix:semicolon
id|mark_object
c_func
(paren
id|object
comma
id|mark
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_idnum
OL
id|mark
)paren
id|last_idnum
op_assign
id|mark
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|SHOWN
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
DECL|function|cmd_fast_export
r_int
id|cmd_fast_export
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
id|rev_info
id|revs
suffix:semicolon
r_struct
id|object_array
id|commits
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
id|string_list
id|extra_refs
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_char
op_star
id|export_filename
op_assign
l_int|NULL
comma
op_star
id|import_filename
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
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;progress&quot;
comma
op_amp
id|progress
comma
l_string|&quot;show progress after &lt;n&gt; objects&quot;
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_int|0
comma
l_string|&quot;signed-tags&quot;
comma
op_amp
id|signed_tag_mode
comma
l_string|&quot;mode&quot;
comma
l_string|&quot;select handling of signed tags&quot;
comma
id|parse_opt_signed_tag_mode
)paren
comma
id|OPT_CALLBACK
c_func
(paren
l_int|0
comma
l_string|&quot;tag-of-filtered-object&quot;
comma
op_amp
id|tag_of_filtered_mode
comma
l_string|&quot;mode&quot;
comma
l_string|&quot;select handling of tags that tag filtered objects&quot;
comma
id|parse_opt_tag_of_filtered_mode
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;export-marks&quot;
comma
op_amp
id|export_filename
comma
l_string|&quot;FILE&quot;
comma
l_string|&quot;Dump marks to this file&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;import-marks&quot;
comma
op_amp
id|import_filename
comma
l_string|&quot;FILE&quot;
comma
l_string|&quot;Import marks from this file&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;fake-missing-tagger&quot;
comma
op_amp
id|fake_missing_tagger
comma
l_string|&quot;Fake a tagger when tags lack one&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|1
)paren
id|usage_with_options
(paren
id|fast_export_usage
comma
id|options
)paren
suffix:semicolon
multiline_comment|/* we handle encodings */
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
id|prefix
)paren
suffix:semicolon
id|revs.topo_order
op_assign
l_int|1
suffix:semicolon
id|revs.show_source
op_assign
l_int|1
suffix:semicolon
id|revs.rewrite_parents
op_assign
l_int|1
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|revs
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
id|options
comma
id|fast_export_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
id|usage_with_options
(paren
id|fast_export_usage
comma
id|options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|import_filename
)paren
id|import_marks
c_func
(paren
id|import_filename
)paren
suffix:semicolon
id|get_tags_and_duplicates
c_func
(paren
op_amp
id|revs.pending
comma
op_amp
id|extra_refs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
)paren
)paren
id|die
c_func
(paren
l_string|&quot;revision walk setup failed&quot;
)paren
suffix:semicolon
id|revs.diffopt.format_callback
op_assign
id|show_filemodify
suffix:semicolon
id|DIFF_OPT_SET
c_func
(paren
op_amp
id|revs.diffopt
comma
id|RECURSIVE
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
op_amp
id|revs
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|has_unshown_parent
c_func
(paren
id|commit
)paren
)paren
(brace
id|add_object_array
c_func
(paren
op_amp
id|commit-&gt;object
comma
l_int|NULL
comma
op_amp
id|commits
)paren
suffix:semicolon
)brace
r_else
(brace
id|handle_commit
c_func
(paren
id|commit
comma
op_amp
id|revs
)paren
suffix:semicolon
id|handle_tail
c_func
(paren
op_amp
id|commits
comma
op_amp
id|revs
)paren
suffix:semicolon
)brace
)brace
id|handle_tags_and_duplicates
c_func
(paren
op_amp
id|extra_refs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|export_filename
)paren
id|export_marks
c_func
(paren
id|export_filename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
