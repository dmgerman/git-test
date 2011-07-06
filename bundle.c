macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;bundle.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;list-objects.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|bundle_signature
r_static
r_const
r_char
id|bundle_signature
(braket
)braket
op_assign
l_string|&quot;# v2 git bundle&bslash;n&quot;
suffix:semicolon
DECL|function|add_to_ref_list
r_static
r_void
id|add_to_ref_list
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|ref_list
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;nr
op_plus
l_int|1
op_ge
id|list-&gt;alloc
)paren
(brace
id|list-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|list-&gt;nr
op_plus
l_int|1
)paren
suffix:semicolon
id|list-&gt;list
op_assign
id|xrealloc
c_func
(paren
id|list-&gt;list
comma
id|list-&gt;alloc
op_star
r_sizeof
(paren
id|list-&gt;list
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|list-&gt;list
(braket
id|list-&gt;nr
)braket
dot
id|sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|list-&gt;list
(braket
id|list-&gt;nr
)braket
dot
id|name
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
id|list-&gt;nr
op_increment
suffix:semicolon
)brace
multiline_comment|/* returns an fd */
DECL|function|read_bundle_header
r_int
id|read_bundle_header
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_struct
id|bundle_header
op_star
id|header
)paren
(brace
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_int
id|fpos
suffix:semicolon
id|FILE
op_star
id|ffd
op_assign
id|fopen
c_func
(paren
id|path
comma
l_string|&quot;rb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ffd
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not open &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
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
id|ffd
)paren
op_logical_or
id|strcmp
c_func
(paren
id|buffer
comma
id|bundle_signature
)paren
)paren
(brace
id|fclose
c_func
(paren
id|ffd
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot; does not look like a v2 bundle file&quot;
comma
id|path
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
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
id|ffd
)paren
op_logical_and
id|buffer
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_int
id|is_prereq
op_assign
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
suffix:semicolon
r_int
id|offset
op_assign
id|is_prereq
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|ref_list
op_star
id|list
op_assign
id|is_prereq
ques
c_cond
op_amp
id|header-&gt;prerequisites
suffix:colon
op_amp
id|header-&gt;references
suffix:semicolon
r_char
id|delim
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|buffer
(braket
id|len
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buffer
(braket
id|len
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buffer
op_plus
id|offset
comma
id|sha1
)paren
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;unrecognized header: %s&quot;
comma
id|buffer
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|delim
op_assign
id|buffer
(braket
l_int|40
op_plus
id|offset
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|delim
)paren
op_logical_and
(paren
id|delim
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_or
op_logical_neg
id|is_prereq
)paren
)paren
id|die
(paren
l_string|&quot;invalid header: %s&quot;
comma
id|buffer
)paren
suffix:semicolon
id|add_to_ref_list
c_func
(paren
id|sha1
comma
id|isspace
c_func
(paren
id|delim
)paren
ques
c_cond
id|buffer
op_plus
l_int|41
op_plus
id|offset
suffix:colon
l_string|&quot;&quot;
comma
id|list
)paren
suffix:semicolon
)brace
id|fpos
op_assign
id|ftell
c_func
(paren
id|ffd
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|ffd
)paren
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|path
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
r_return
id|error
c_func
(paren
l_string|&quot;could not open &squot;%s&squot;&quot;
comma
id|path
)paren
suffix:semicolon
id|lseek
c_func
(paren
id|fd
comma
id|fpos
comma
id|SEEK_SET
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|list_refs
r_static
r_int
id|list_refs
c_func
(paren
r_struct
id|ref_list
op_star
id|r
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
id|r-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|argc
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|r-&gt;list
(braket
id|i
)braket
dot
id|name
comma
id|argv
(braket
id|j
)braket
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|argc
)paren
r_continue
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|r-&gt;list
(braket
id|i
)braket
dot
id|sha1
)paren
comma
id|r-&gt;list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PREREQ_MARK
mdefine_line|#define PREREQ_MARK (1u&lt;&lt;16)
DECL|function|verify_bundle
r_int
id|verify_bundle
c_func
(paren
r_struct
id|bundle_header
op_star
id|header
comma
r_int
id|verbose
)paren
(brace
multiline_comment|/*&n;&t; * Do fast check, then if any prereqs are missing then go line by line&n;&t; * to be verbose about the errors&n;&t; */
r_struct
id|ref_list
op_star
id|p
op_assign
op_amp
id|header-&gt;prerequisites
suffix:semicolon
r_struct
id|rev_info
id|revs
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;--all&quot;
)brace
suffix:semicolon
r_struct
id|object_array
id|refs
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
l_int|0
comma
id|req_nr
suffix:semicolon
r_const
r_char
op_star
id|message
op_assign
l_string|&quot;Repository lacks these prerequisite commits:&quot;
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
l_int|NULL
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
id|p-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ref_list_entry
op_star
id|e
op_assign
id|p-&gt;list
op_plus
id|i
suffix:semicolon
r_struct
id|object
op_star
id|o
op_assign
id|parse_object
c_func
(paren
id|e-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o
)paren
(brace
id|o-&gt;flags
op_or_assign
id|PREREQ_MARK
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|o
comma
id|e-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|ret
op_eq
l_int|1
)paren
id|error
c_func
(paren
id|message
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|e-&gt;sha1
)paren
comma
id|e-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|revs.pending.nr
op_ne
id|p-&gt;nr
)paren
r_return
id|ret
suffix:semicolon
id|req_nr
op_assign
id|revs.pending.nr
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|2
comma
id|argv
comma
op_amp
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|refs
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|object_array
)paren
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
id|revs.pending.nr
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
id|revs.pending.objects
op_plus
id|i
suffix:semicolon
id|add_object_array
c_func
(paren
id|e-&gt;item
comma
id|e-&gt;name
comma
op_amp
id|refs
)paren
suffix:semicolon
)brace
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
id|i
op_assign
id|req_nr
suffix:semicolon
r_while
c_loop
(paren
id|i
op_logical_and
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
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|PREREQ_MARK
)paren
id|i
op_decrement
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
id|req_nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|refs.objects
(braket
id|i
)braket
dot
id|item-&gt;flags
op_amp
id|SHOWN
)paren
)paren
(brace
r_if
c_cond
(paren
op_increment
id|ret
op_eq
l_int|1
)paren
id|error
c_func
(paren
id|message
)paren
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|refs.objects
(braket
id|i
)braket
dot
id|item-&gt;sha1
)paren
comma
id|refs.objects
(braket
id|i
)braket
dot
id|name
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
id|refs.nr
suffix:semicolon
id|i
op_increment
)paren
id|clear_commit_marks
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|refs.objects
(braket
id|i
)braket
dot
id|item
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
r_struct
id|ref_list
op_star
id|r
suffix:semicolon
id|r
op_assign
op_amp
id|header-&gt;references
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;The bundle contains %d ref%s&bslash;n&quot;
comma
id|r-&gt;nr
comma
(paren
l_int|1
OL
id|r-&gt;nr
)paren
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|list_refs
c_func
(paren
id|r
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|r
op_assign
op_amp
id|header-&gt;prerequisites
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;The bundle requires these %d ref%s&bslash;n&quot;
comma
id|r-&gt;nr
comma
(paren
l_int|1
OL
id|r-&gt;nr
)paren
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|list_refs
c_func
(paren
id|r
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|list_bundle_refs
r_int
id|list_bundle_refs
c_func
(paren
r_struct
id|bundle_header
op_star
id|header
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
r_return
id|list_refs
c_func
(paren
op_amp
id|header-&gt;references
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
DECL|function|create_bundle
r_int
id|create_bundle
c_func
(paren
r_struct
id|bundle_header
op_star
id|header
comma
r_const
r_char
op_star
id|path
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
r_static
r_struct
id|lock_file
id|lock
suffix:semicolon
r_int
id|bundle_fd
op_assign
l_int|1
suffix:semicolon
r_int
id|bundle_to_stdout
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv_boundary
op_assign
id|xmalloc
c_func
(paren
(paren
id|argc
op_plus
l_int|4
)paren
op_star
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv_pack
op_assign
id|xmalloc
c_func
(paren
l_int|5
op_star
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
r_int
id|i
comma
id|ref_count
op_assign
l_int|0
suffix:semicolon
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|rev_info
id|revs
suffix:semicolon
r_int
id|read_from_stdin
op_assign
l_int|0
suffix:semicolon
r_struct
id|child_process
id|rls
suffix:semicolon
id|FILE
op_star
id|rls_fout
suffix:semicolon
id|bundle_to_stdout
op_assign
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bundle_to_stdout
)paren
id|bundle_fd
op_assign
l_int|1
suffix:semicolon
r_else
id|bundle_fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|lock
comma
id|path
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* write signature */
id|write_or_die
c_func
(paren
id|bundle_fd
comma
id|bundle_signature
comma
id|strlen
c_func
(paren
id|bundle_signature
)paren
)paren
suffix:semicolon
multiline_comment|/* init revs to list objects for pack-objects later */
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* write prerequisites */
id|memcpy
c_func
(paren
id|argv_boundary
op_plus
l_int|3
comma
id|argv
op_plus
l_int|1
comma
id|argc
op_star
r_sizeof
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
id|argv_boundary
(braket
l_int|0
)braket
op_assign
l_string|&quot;rev-list&quot;
suffix:semicolon
id|argv_boundary
(braket
l_int|1
)braket
op_assign
l_string|&quot;--boundary&quot;
suffix:semicolon
id|argv_boundary
(braket
l_int|2
)braket
op_assign
l_string|&quot;--pretty=oneline&quot;
suffix:semicolon
id|argv_boundary
(braket
id|argc
op_plus
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rls
comma
l_int|0
comma
r_sizeof
(paren
id|rls
)paren
)paren
suffix:semicolon
id|rls.argv
op_assign
id|argv_boundary
suffix:semicolon
id|rls.out
op_assign
l_int|1
suffix:semicolon
id|rls.git_cmd
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
id|rls
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|rls_fout
op_assign
id|fdopen
c_func
(paren
id|rls.out
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
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
id|rls_fout
)paren
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
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|write_or_die
c_func
(paren
id|bundle_fd
comma
id|buffer
comma
id|strlen
c_func
(paren
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|buffer
op_plus
l_int|1
comma
id|sha1
)paren
)paren
(brace
r_struct
id|object
op_star
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|object
comma
id|buffer
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
)paren
(brace
r_struct
id|object
op_star
id|object
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|SHOWN
suffix:semicolon
)brace
)brace
id|fclose
c_func
(paren
id|rls_fout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|rls
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;rev-list died&quot;
)paren
suffix:semicolon
multiline_comment|/* write references */
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
r_for
c_loop
(paren
id|i
op_assign
l_int|1
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
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|read_from_stdin
op_increment
)paren
id|die
c_func
(paren
l_string|&quot;--stdin given twice?&quot;
)paren
suffix:semicolon
id|read_revisions_from_stdin
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;unrecognized argument: %s&squot;&quot;
comma
id|argv
(braket
id|i
)braket
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
id|revs.pending.nr
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
id|revs.pending.objects
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
r_char
op_star
id|ref
suffix:semicolon
r_const
r_char
op_star
id|display_ref
suffix:semicolon
r_int
id|flag
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;item-&gt;flags
op_amp
id|UNINTERESTING
)paren
r_continue
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
id|ref
)paren
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolve_ref
c_func
(paren
id|e-&gt;name
comma
id|sha1
comma
l_int|1
comma
op_amp
id|flag
)paren
)paren
id|flag
op_assign
l_int|0
suffix:semicolon
id|display_ref
op_assign
(paren
id|flag
op_amp
id|REF_ISSYMREF
)paren
ques
c_cond
id|e-&gt;name
suffix:colon
id|ref
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Make sure the refs we wrote out is correct; --max-count and&n;&t;&t; * other limiting options could have prevented all the tips&n;&t;&t; * from getting output.&n;&t;&t; *&n;&t;&t; * Non commit objects such as tags and blobs do not have&n;&t;&t; * this issue as they are not affected by those extra&n;&t;&t; * constraints.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|e-&gt;item-&gt;flags
op_amp
id|SHOWN
)paren
op_logical_and
id|e-&gt;item-&gt;type
op_eq
id|OBJ_COMMIT
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;ref &squot;%s&squot; is excluded by the rev-list options&quot;
comma
id|e-&gt;name
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If you run &quot;git bundle create bndl v1.0..v2.0&quot;, the&n;&t;&t; * name of the positive ref is &quot;v2.0&quot; but that is the&n;&t;&t; * commit that is referenced by the tag, and not the tag&n;&t;&t; * itself.&n;&t;&t; */
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|sha1
comma
id|e-&gt;item-&gt;sha1
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Is this the positive end of a range expressed&n;&t;&t;&t; * in terms of a tag (e.g. v2.0 from the range&n;&t;&t;&t; * &quot;v1.0..v2.0&quot;)?&n;&t;&t;&t; */
r_struct
id|commit
op_star
id|one
op_assign
id|lookup_commit_reference
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_struct
id|object
op_star
id|obj
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;item
op_eq
op_amp
(paren
id|one-&gt;object
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Need to include e-&gt;name as an&n;&t;&t;&t;&t; * independent ref to the pack-objects&n;&t;&t;&t;&t; * input, so that the tag is included&n;&t;&t;&t;&t; * in the output; otherwise we would&n;&t;&t;&t;&t; * end up triggering &quot;empty bundle&quot;&n;&t;&t;&t;&t; * error.&n;&t;&t;&t;&t; */
id|obj
op_assign
id|parse_object
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|obj-&gt;flags
op_or_assign
id|SHOWN
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|obj
comma
id|e-&gt;name
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ref_count
op_increment
suffix:semicolon
id|write_or_die
c_func
(paren
id|bundle_fd
comma
id|sha1_to_hex
c_func
(paren
id|e-&gt;item-&gt;sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|bundle_fd
comma
l_string|&quot; &quot;
comma
l_int|1
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|bundle_fd
comma
id|display_ref
comma
id|strlen
c_func
(paren
id|display_ref
)paren
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|bundle_fd
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ref_count
)paren
id|die
(paren
l_string|&quot;Refusing to create empty bundle.&quot;
)paren
suffix:semicolon
multiline_comment|/* end header */
id|write_or_die
c_func
(paren
id|bundle_fd
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* write pack */
id|argv_pack
(braket
l_int|0
)braket
op_assign
l_string|&quot;pack-objects&quot;
suffix:semicolon
id|argv_pack
(braket
l_int|1
)braket
op_assign
l_string|&quot;--all-progress&quot;
suffix:semicolon
id|argv_pack
(braket
l_int|2
)braket
op_assign
l_string|&quot;--stdout&quot;
suffix:semicolon
id|argv_pack
(braket
l_int|3
)braket
op_assign
l_string|&quot;--thin&quot;
suffix:semicolon
id|argv_pack
(braket
l_int|4
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rls
comma
l_int|0
comma
r_sizeof
(paren
id|rls
)paren
)paren
suffix:semicolon
id|rls.argv
op_assign
id|argv_pack
suffix:semicolon
id|rls.in
op_assign
l_int|1
suffix:semicolon
id|rls.out
op_assign
id|bundle_fd
suffix:semicolon
id|rls.git_cmd
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
id|rls
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not spawn pack-objects&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * start_command closed bundle_fd if it was &gt; 1&n;&t; * so set the lock fd to -1 so commit_lock_file()&n;&t; * won&squot;t fail trying to close it.&n;&t; */
id|lock.fd
op_assign
l_int|1
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
id|revs.pending.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|object
op_assign
id|revs.pending.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
r_if
c_cond
(paren
id|object-&gt;flags
op_amp
id|UNINTERESTING
)paren
id|write_or_die
c_func
(paren
id|rls.in
comma
l_string|&quot;^&quot;
comma
l_int|1
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|rls.in
comma
id|sha1_to_hex
c_func
(paren
id|object-&gt;sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
id|rls.in
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|rls.in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|rls
)paren
)paren
r_return
id|error
(paren
l_string|&quot;pack-objects died&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bundle_to_stdout
)paren
id|commit_lock_file
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unbundle
r_int
id|unbundle
c_func
(paren
r_struct
id|bundle_header
op_star
id|header
comma
r_int
id|bundle_fd
)paren
(brace
r_const
r_char
op_star
id|argv_index_pack
(braket
)braket
op_assign
(brace
l_string|&quot;index-pack&quot;
comma
l_string|&quot;--fix-thin&quot;
comma
l_string|&quot;--stdin&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|child_process
id|ip
suffix:semicolon
r_if
c_cond
(paren
id|verify_bundle
c_func
(paren
id|header
comma
l_int|0
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ip
comma
l_int|0
comma
r_sizeof
(paren
id|ip
)paren
)paren
suffix:semicolon
id|ip.argv
op_assign
id|argv_index_pack
suffix:semicolon
id|ip.in
op_assign
id|bundle_fd
suffix:semicolon
id|ip.no_stdout
op_assign
l_int|1
suffix:semicolon
id|ip.git_cmd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|run_command
c_func
(paren
op_amp
id|ip
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;index-pack died&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
