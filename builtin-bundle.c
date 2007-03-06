macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;list-objects.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
multiline_comment|/*&n; * Basic handler for bundle files to connect repositories via sneakernet.&n; * Invocation must include action.&n; * This function can create a bundle or provide information on an existing&n; * bundle supporting git-fetch, git-pull, and git-ls-remote&n; */
DECL|variable|bundle_usage
r_static
r_const
r_char
op_star
id|bundle_usage
op_assign
l_string|&quot;git-bundle (create &lt;bundle&gt; &lt;git-rev-list args&gt; | verify &lt;bundle&gt; | list-heads &lt;bundle&gt; [refname]... | unbundle &lt;bundle&gt; [refname]... )&quot;
suffix:semicolon
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
DECL|struct|ref_list
r_struct
id|ref_list
(brace
DECL|member|nr
DECL|member|alloc
r_int
r_int
id|nr
comma
id|alloc
suffix:semicolon
DECL|struct|ref_list_entry
r_struct
id|ref_list_entry
(brace
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|list
)brace
op_star
id|list
suffix:semicolon
)brace
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
DECL|struct|bundle_header
r_struct
id|bundle_header
(brace
DECL|member|prerequisites
r_struct
id|ref_list
id|prerequisites
suffix:semicolon
DECL|member|references
r_struct
id|ref_list
id|references
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* this function returns the length of the string */
DECL|function|read_string
r_static
r_int
id|read_string
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|buffer
comma
r_int
id|size
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
id|size
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|count
op_assign
id|xread
c_func
(paren
id|fd
comma
id|buffer
op_plus
id|i
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Read error: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|i
op_decrement
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buffer
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
)brace
id|buffer
(braket
id|i
op_plus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|i
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* returns an fd */
DECL|function|read_header
r_static
r_int
id|read_header
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
r_if
c_cond
(paren
id|read_string
c_func
(paren
id|fd
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
OL
l_int|0
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
id|close
c_func
(paren
id|fd
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
id|read_string
c_func
(paren
id|fd
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
OG
l_int|0
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
id|warn
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
r_return
id|fd
suffix:semicolon
)brace
multiline_comment|/* if in &amp;&amp; *in &gt;= 0, take that as input file descriptor instead */
DECL|function|fork_with_pipe
r_static
r_int
id|fork_with_pipe
c_func
(paren
r_const
r_char
op_star
op_star
id|argv
comma
r_int
op_star
id|in
comma
r_int
op_star
id|out
)paren
(brace
r_int
id|needs_in
comma
id|needs_out
suffix:semicolon
r_int
id|fdin
(braket
l_int|2
)braket
comma
id|fdout
(braket
l_int|2
)braket
comma
id|pid
suffix:semicolon
id|needs_in
op_assign
id|in
op_logical_and
op_star
id|in
OL
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|needs_in
)paren
(brace
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fdin
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not setup pipe&quot;
)paren
suffix:semicolon
op_star
id|in
op_assign
id|fdin
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|needs_out
op_assign
id|out
op_logical_and
op_star
id|out
OL
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|needs_out
)paren
(brace
r_if
c_cond
(paren
id|pipe
c_func
(paren
id|fdout
)paren
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;could not setup pipe&quot;
)paren
suffix:semicolon
op_star
id|out
op_assign
id|fdout
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pid
op_assign
id|fork
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|needs_in
)paren
(brace
id|close
c_func
(paren
id|fdin
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdin
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|needs_out
)paren
(brace
id|close
c_func
(paren
id|fdout
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdout
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;could not fork&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_if
c_cond
(paren
id|needs_in
)paren
(brace
id|dup2
c_func
(paren
id|fdin
(braket
l_int|0
)braket
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdin
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdin
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|in
)paren
(brace
id|dup2
c_func
(paren
op_star
id|in
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
op_star
id|in
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|needs_out
)paren
(brace
id|dup2
c_func
(paren
id|fdout
(braket
l_int|1
)braket
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdout
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fdout
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|out
)paren
(brace
id|dup2
c_func
(paren
op_star
id|out
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
op_star
id|out
)paren
suffix:semicolon
)brace
m_exit
(paren
id|execv_git_cmd
c_func
(paren
id|argv
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|needs_in
)paren
id|close
c_func
(paren
id|fdin
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in
)paren
id|close
c_func
(paren
op_star
id|in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|needs_out
)paren
id|close
c_func
(paren
id|fdout
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|out
)paren
id|close
c_func
(paren
op_star
id|out
)paren
suffix:semicolon
r_return
id|pid
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
r_static
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
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
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
DECL|function|list_heads
r_static
r_int
id|list_heads
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
DECL|function|show_commit
r_static
r_void
id|show_commit
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
id|write_or_die
c_func
(paren
l_int|1
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;parents
)paren
(brace
id|free_commit_list
c_func
(paren
id|commit-&gt;parents
)paren
suffix:semicolon
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|show_object
r_static
r_void
id|show_object
c_func
(paren
r_struct
id|object_array_entry
op_star
id|p
)paren
(brace
multiline_comment|/* An object with name &quot;foo&bslash;n0000000...&quot; can be used to&n;&t; * confuse downstream git-pack-objects very badly.&n;&t; */
r_const
r_char
op_star
id|ep
op_assign
id|strchr
c_func
(paren
id|p-&gt;name
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_int
id|len
op_assign
id|ep
ques
c_cond
id|ep
id|p-&gt;name
suffix:colon
id|strlen
c_func
(paren
id|p-&gt;name
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|sha1_to_hex
c_func
(paren
id|p-&gt;item-&gt;sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
l_string|&quot; &quot;
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
id|write_or_die
c_func
(paren
l_int|1
comma
id|p-&gt;name
comma
id|len
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
l_string|&quot;&bslash;n&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|show_edge
r_static
r_void
id|show_edge
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
suffix:semicolon
multiline_comment|/* nothing to do */
)brace
DECL|function|create_bundle
r_static
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
r_int
id|bundle_fd
op_assign
l_int|1
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
l_int|4
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
id|pid
comma
id|in
comma
id|out
comma
id|i
comma
id|status
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
r_struct
id|object_array
id|tips
suffix:semicolon
id|bundle_fd
op_assign
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|path
comma
l_string|&quot;-&quot;
)paren
ques
c_cond
l_int|1
suffix:colon
id|open
c_func
(paren
id|path
comma
id|O_CREAT
op_or
id|O_WRONLY
comma
l_int|0666
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bundle_fd
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not write to &squot;%s&squot;&quot;
comma
id|path
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
id|out
op_assign
l_int|1
suffix:semicolon
id|pid
op_assign
id|fork_with_pipe
c_func
(paren
id|argv_boundary
comma
l_int|NULL
comma
op_amp
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
op_assign
id|read_string
c_func
(paren
id|out
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
)paren
OG
l_int|0
)paren
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
id|write_or_die
c_func
(paren
id|bundle_fd
comma
id|buffer
comma
id|i
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
op_assign
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
r_return
id|error
c_func
(paren
l_string|&quot;rev-list died&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;rev-list died %d&quot;
comma
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
multiline_comment|/* write references */
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
id|revs.tag_objects
op_assign
l_int|1
suffix:semicolon
id|revs.tree_objects
op_assign
l_int|1
suffix:semicolon
id|revs.blob_objects
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
r_if
c_cond
(paren
id|argc
OG
l_int|1
)paren
r_return
id|error
c_func
(paren
l_string|&quot;unrecognized argument: %s&squot;&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tips
comma
l_int|0
comma
r_sizeof
(paren
id|tips
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
id|ref
comma
id|strlen
c_func
(paren
id|ref
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
id|add_object_array
c_func
(paren
id|e-&gt;item
comma
id|e-&gt;name
comma
op_amp
id|tips
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
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
l_int|NULL
suffix:semicolon
id|in
op_assign
l_int|1
suffix:semicolon
id|out
op_assign
id|bundle_fd
suffix:semicolon
id|pid
op_assign
id|fork_with_pipe
c_func
(paren
id|argv_pack
comma
op_amp
id|in
comma
op_amp
id|out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not spawn pack-objects&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|in
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|in
)paren
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
op_amp
id|revs
)paren
suffix:semicolon
id|mark_edges_uninteresting
c_func
(paren
id|revs.commits
comma
op_amp
id|revs
comma
id|show_edge
)paren
suffix:semicolon
id|traverse_commit_list
c_func
(paren
op_amp
id|revs
comma
id|show_commit
comma
id|show_object
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
r_return
id|error
(paren
l_string|&quot;pack-objects died&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure the refs we wrote out is correct; --max-count and&n;&t; * other limiting options could have prevented all the tips&n;&t; * from getting output.&n;&t; */
id|status
op_assign
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
id|tips.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tips.objects
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
id|status
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;%s: not included in the resulting pack&quot;
comma
id|tips.objects
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
r_return
id|status
suffix:semicolon
)brace
DECL|function|unbundle
r_static
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
l_string|&quot;--stdin&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|pid
comma
id|status
comma
id|dev_null
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
id|dev_null
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/null&quot;
comma
id|O_WRONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_null
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not open /dev/null&quot;
)paren
suffix:semicolon
id|pid
op_assign
id|fork_with_pipe
c_func
(paren
id|argv_index_pack
comma
op_amp
id|bundle_fd
comma
op_amp
id|dev_null
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Could not spawn index-pack&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
OL
l_int|0
)paren
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
r_return
id|error
c_func
(paren
l_string|&quot;index-pack died&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;index-pack exited with status %d&quot;
comma
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
r_return
id|list_heads
c_func
(paren
id|header
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
DECL|function|cmd_bundle
r_int
id|cmd_bundle
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
id|bundle_header
id|header
suffix:semicolon
r_int
id|nongit
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|cmd
comma
op_star
id|bundle_file
suffix:semicolon
r_int
id|bundle_fd
op_assign
l_int|1
suffix:semicolon
r_char
id|buffer
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
id|usage
c_func
(paren
id|bundle_usage
)paren
suffix:semicolon
id|cmd
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|bundle_file
op_assign
id|argv
(braket
l_int|2
)braket
suffix:semicolon
id|argc
op_sub_assign
l_int|2
suffix:semicolon
id|argv
op_add_assign
l_int|2
suffix:semicolon
id|prefix
op_assign
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefix
op_logical_and
id|bundle_file
(braket
l_int|0
)braket
op_ne
l_char|&squot;/&squot;
)paren
(brace
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
l_string|&quot;%s/%s&quot;
comma
id|prefix
comma
id|bundle_file
)paren
suffix:semicolon
id|bundle_file
op_assign
id|buffer
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|header
comma
l_int|0
comma
r_sizeof
(paren
id|header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;create&quot;
)paren
op_logical_and
(paren
id|bundle_fd
op_assign
id|read_header
c_func
(paren
id|bundle_file
comma
op_amp
id|header
)paren
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;verify&quot;
)paren
)paren
(brace
id|close
c_func
(paren
id|bundle_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify_bundle
c_func
(paren
op_amp
id|header
comma
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s is okay&bslash;n&quot;
comma
id|bundle_file
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
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;list-heads&quot;
)paren
)paren
(brace
id|close
c_func
(paren
id|bundle_fd
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|list_heads
c_func
(paren
op_amp
id|header
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cmd
comma
l_string|&quot;create&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|nongit
)paren
id|die
c_func
(paren
l_string|&quot;Need a repository to create a bundle.&quot;
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|create_bundle
c_func
(paren
op_amp
id|header
comma
id|bundle_file
comma
id|argc
comma
id|argv
)paren
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
id|cmd
comma
l_string|&quot;unbundle&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|nongit
)paren
id|die
c_func
(paren
l_string|&quot;Need a repository to unbundle.&quot;
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|unbundle
c_func
(paren
op_amp
id|header
comma
id|bundle_fd
comma
id|argc
comma
id|argv
)paren
suffix:semicolon
)brace
r_else
id|usage
c_func
(paren
id|bundle_usage
)paren
suffix:semicolon
)brace
eof
