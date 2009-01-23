macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;list-objects.h&quot;
macro_line|#include &quot;run-command.h&quot;
DECL|variable|upload_pack_usage
r_static
r_const
r_char
id|upload_pack_usage
(braket
)braket
op_assign
l_string|&quot;git upload-pack [--strict] [--timeout=nn] &lt;dir&gt;&quot;
suffix:semicolon
multiline_comment|/* bits #0..7 in revision.h, #8..10 in commit.c */
DECL|macro|THEY_HAVE
mdefine_line|#define THEY_HAVE&t;(1u &lt;&lt; 11)
DECL|macro|OUR_REF
mdefine_line|#define OUR_REF&t;&t;(1u &lt;&lt; 12)
DECL|macro|WANTED
mdefine_line|#define WANTED&t;&t;(1u &lt;&lt; 13)
DECL|macro|COMMON_KNOWN
mdefine_line|#define COMMON_KNOWN&t;(1u &lt;&lt; 14)
DECL|macro|REACHABLE
mdefine_line|#define REACHABLE&t;(1u &lt;&lt; 15)
DECL|macro|SHALLOW
mdefine_line|#define SHALLOW&t;&t;(1u &lt;&lt; 16)
DECL|macro|NOT_SHALLOW
mdefine_line|#define NOT_SHALLOW&t;(1u &lt;&lt; 17)
DECL|macro|CLIENT_SHALLOW
mdefine_line|#define CLIENT_SHALLOW&t;(1u &lt;&lt; 18)
DECL|variable|oldest_have
r_static
r_int
r_int
id|oldest_have
suffix:semicolon
DECL|variable|multi_ack
DECL|variable|nr_our_refs
r_static
r_int
id|multi_ack
comma
id|nr_our_refs
suffix:semicolon
DECL|variable|use_thin_pack
DECL|variable|use_ofs_delta
DECL|variable|use_include_tag
r_static
r_int
id|use_thin_pack
comma
id|use_ofs_delta
comma
id|use_include_tag
suffix:semicolon
DECL|variable|no_progress
r_static
r_int
id|no_progress
suffix:semicolon
DECL|variable|have_obj
r_static
r_struct
id|object_array
id|have_obj
suffix:semicolon
DECL|variable|want_obj
r_static
r_struct
id|object_array
id|want_obj
suffix:semicolon
DECL|variable|timeout
r_static
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* 0 for no sideband,&n; * otherwise maximum packet size (up to 65520 bytes).&n; */
DECL|variable|use_sideband
r_static
r_int
id|use_sideband
suffix:semicolon
DECL|variable|debug_fd
r_static
r_int
id|debug_fd
suffix:semicolon
DECL|function|reset_timeout
r_static
r_void
id|reset_timeout
c_func
(paren
r_void
)paren
(brace
id|alarm
c_func
(paren
id|timeout
)paren
suffix:semicolon
)brace
DECL|function|strip
r_static
r_int
id|strip
c_func
(paren
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_logical_and
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|line
(braket
op_decrement
id|len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|send_client_data
r_static
id|ssize_t
id|send_client_data
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|data
comma
id|ssize_t
id|sz
)paren
(brace
r_if
c_cond
(paren
id|use_sideband
)paren
r_return
id|send_sideband
c_func
(paren
l_int|1
comma
id|fd
comma
id|data
comma
id|sz
comma
id|use_sideband
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
l_int|3
)paren
multiline_comment|/* emergency quit */
id|fd
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
l_int|2
)paren
(brace
multiline_comment|/* XXX: are we happy to lose stuff here? */
id|xwrite
c_func
(paren
id|fd
comma
id|data
comma
id|sz
)paren
suffix:semicolon
r_return
id|sz
suffix:semicolon
)brace
r_return
id|safe_write
c_func
(paren
id|fd
comma
id|data
comma
id|sz
)paren
suffix:semicolon
)brace
DECL|variable|pack_pipe
r_static
id|FILE
op_star
id|pack_pipe
op_assign
l_int|NULL
suffix:semicolon
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
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|BOUNDARY
)paren
id|fputc
c_func
(paren
l_char|&squot;-&squot;
comma
id|pack_pipe
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fputs
c_func
(paren
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
comma
id|pack_pipe
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;broken output pipe&quot;
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|pack_pipe
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|pack_pipe
)paren
suffix:semicolon
id|free
c_func
(paren
id|commit-&gt;buffer
)paren
suffix:semicolon
id|commit-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|show_object
r_static
r_void
id|show_object
c_func
(paren
r_struct
id|object
op_star
id|obj
comma
r_const
r_struct
id|name_path
op_star
id|path
comma
r_const
r_char
op_star
id|component
)paren
(brace
multiline_comment|/* An object with name &quot;foo&bslash;n0000000...&quot; can be used to&n;&t; * confuse downstream git-pack-objects very badly.&n;&t; */
r_const
r_char
op_star
id|name
op_assign
id|path_name
c_func
(paren
id|path
comma
id|component
)paren
suffix:semicolon
r_const
r_char
op_star
id|ep
op_assign
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
(brace
id|fprintf
c_func
(paren
id|pack_pipe
comma
l_string|&quot;%s %.*s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
(paren
r_int
)paren
(paren
id|ep
id|name
)paren
comma
id|name
)paren
suffix:semicolon
)brace
r_else
id|fprintf
c_func
(paren
id|pack_pipe
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj-&gt;sha1
)paren
comma
id|name
)paren
suffix:semicolon
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|name
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
id|fprintf
c_func
(paren
id|pack_pipe
comma
l_string|&quot;-%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|do_rev_list
r_static
r_int
id|do_rev_list
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|create_full_pack
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|rev_info
id|revs
suffix:semicolon
id|pack_pipe
op_assign
id|fdopen
c_func
(paren
id|fd
comma
l_string|&quot;w&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|create_full_pack
)paren
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no point doing it */
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
r_if
c_cond
(paren
id|use_thin_pack
)paren
id|revs.edge_hint
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|create_full_pack
)paren
(brace
r_const
r_char
op_star
id|args
(braket
)braket
op_assign
(brace
l_string|&quot;rev-list&quot;
comma
l_string|&quot;--all&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|setup_revisions
c_func
(paren
l_int|2
comma
id|args
comma
op_amp
id|revs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|want_obj.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|want_obj.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
multiline_comment|/* why??? */
id|o-&gt;flags
op_and_assign
op_complement
id|UNINTERESTING
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|o
comma
l_int|NULL
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
id|have_obj.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|o
op_assign
id|have_obj.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
id|o-&gt;flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
id|add_pending_object
c_func
(paren
op_amp
id|revs
comma
id|o
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|setup_revisions
c_func
(paren
l_int|0
comma
l_int|NULL
comma
op_amp
id|revs
comma
l_int|NULL
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
comma
l_int|NULL
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|pack_pipe
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|pack_pipe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|create_pack_file
r_static
r_void
id|create_pack_file
c_func
(paren
r_void
)paren
(brace
r_struct
id|async
id|rev_list
suffix:semicolon
r_struct
id|child_process
id|pack_objects
suffix:semicolon
r_int
id|create_full_pack
op_assign
(paren
id|nr_our_refs
op_eq
id|want_obj.nr
op_logical_and
op_logical_neg
id|have_obj.nr
)paren
suffix:semicolon
r_char
id|data
(braket
l_int|8193
)braket
comma
id|progress
(braket
l_int|128
)braket
suffix:semicolon
r_char
id|abort_msg
(braket
)braket
op_assign
l_string|&quot;aborting due to possible repository &quot;
l_string|&quot;corruption on the remote side.&quot;
suffix:semicolon
r_int
id|buffered
op_assign
l_int|1
suffix:semicolon
id|ssize_t
id|sz
suffix:semicolon
r_const
r_char
op_star
id|argv
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|arg
op_assign
l_int|0
suffix:semicolon
id|rev_list.proc
op_assign
id|do_rev_list
suffix:semicolon
multiline_comment|/* .data is just a boolean: any non-NULL value will do */
id|rev_list.data
op_assign
id|create_full_pack
ques
c_cond
op_amp
id|rev_list
suffix:colon
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|start_async
c_func
(paren
op_amp
id|rev_list
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git upload-pack: unable to fork git-rev-list&quot;
)paren
suffix:semicolon
id|argv
(braket
id|arg
op_increment
)braket
op_assign
l_string|&quot;pack-objects&quot;
suffix:semicolon
id|argv
(braket
id|arg
op_increment
)braket
op_assign
l_string|&quot;--stdout&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_progress
)paren
id|argv
(braket
id|arg
op_increment
)braket
op_assign
l_string|&quot;--progress&quot;
suffix:semicolon
r_if
c_cond
(paren
id|use_ofs_delta
)paren
id|argv
(braket
id|arg
op_increment
)braket
op_assign
l_string|&quot;--delta-base-offset&quot;
suffix:semicolon
r_if
c_cond
(paren
id|use_include_tag
)paren
id|argv
(braket
id|arg
op_increment
)braket
op_assign
l_string|&quot;--include-tag&quot;
suffix:semicolon
id|argv
(braket
id|arg
op_increment
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pack_objects
comma
l_int|0
comma
r_sizeof
(paren
id|pack_objects
)paren
)paren
suffix:semicolon
id|pack_objects.in
op_assign
id|rev_list.out
suffix:semicolon
multiline_comment|/* start_command closes it */
id|pack_objects.out
op_assign
l_int|1
suffix:semicolon
id|pack_objects.err
op_assign
l_int|1
suffix:semicolon
id|pack_objects.git_cmd
op_assign
l_int|1
suffix:semicolon
id|pack_objects.argv
op_assign
id|argv
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|pack_objects
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git upload-pack: unable to fork git-pack-objects&quot;
)paren
suffix:semicolon
multiline_comment|/* We read from pack_objects.err to capture stderr output for&n;&t; * progress bar, and pack_objects.out to capture the pack data.&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|pollfd
id|pfd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|pe
comma
id|pu
comma
id|pollsize
suffix:semicolon
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
id|pollsize
op_assign
l_int|0
suffix:semicolon
id|pe
op_assign
id|pu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|pack_objects.out
)paren
(brace
id|pfd
(braket
id|pollsize
)braket
dot
id|fd
op_assign
id|pack_objects.out
suffix:semicolon
id|pfd
(braket
id|pollsize
)braket
dot
id|events
op_assign
id|POLLIN
suffix:semicolon
id|pu
op_assign
id|pollsize
suffix:semicolon
id|pollsize
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|pack_objects.err
)paren
(brace
id|pfd
(braket
id|pollsize
)braket
dot
id|fd
op_assign
id|pack_objects.err
suffix:semicolon
id|pfd
(braket
id|pollsize
)braket
dot
id|events
op_assign
id|POLLIN
suffix:semicolon
id|pe
op_assign
id|pollsize
suffix:semicolon
id|pollsize
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pollsize
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|poll
c_func
(paren
id|pfd
comma
id|pollsize
comma
l_int|1
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EINTR
)paren
(brace
id|error
c_func
(paren
l_string|&quot;poll failed, resuming: %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
id|sleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|pu
op_logical_and
(paren
id|pfd
(braket
id|pu
)braket
dot
id|revents
op_amp
(paren
id|POLLIN
op_or
id|POLLHUP
)paren
)paren
)paren
(brace
multiline_comment|/* Data ready; we keep the last byte to ourselves&n;&t;&t;&t; * in case we detect broken rev-list, so that we&n;&t;&t;&t; * can leave the stream corrupted.  This is&n;&t;&t;&t; * unfortunate -- unpack-objects would happily&n;&t;&t;&t; * accept a valid packdata with trailing garbage,&n;&t;&t;&t; * so appending garbage after we pass all the&n;&t;&t;&t; * pack data is not good enough to signal&n;&t;&t;&t; * breakage to downstream.&n;&t;&t;&t; */
r_char
op_star
id|cp
op_assign
id|data
suffix:semicolon
id|ssize_t
id|outsz
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|buffered
)paren
(brace
op_star
id|cp
op_increment
op_assign
id|buffered
suffix:semicolon
id|outsz
op_increment
suffix:semicolon
)brace
id|sz
op_assign
id|xread
c_func
(paren
id|pack_objects.out
comma
id|cp
comma
r_sizeof
(paren
id|data
)paren
id|outsz
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OL
id|sz
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sz
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|pack_objects.out
)paren
suffix:semicolon
id|pack_objects.out
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|fail
suffix:semicolon
id|sz
op_add_assign
id|outsz
suffix:semicolon
r_if
c_cond
(paren
l_int|1
OL
id|sz
)paren
(brace
id|buffered
op_assign
id|data
(braket
id|sz
op_minus
l_int|1
)braket
op_amp
l_int|0xFF
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
)brace
r_else
id|buffered
op_assign
l_int|1
suffix:semicolon
id|sz
op_assign
id|send_client_data
c_func
(paren
l_int|1
comma
id|data
comma
id|sz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_le
id|pe
op_logical_and
(paren
id|pfd
(braket
id|pe
)braket
dot
id|revents
op_amp
(paren
id|POLLIN
op_or
id|POLLHUP
)paren
)paren
)paren
(brace
multiline_comment|/* Status ready; we ship that in the side-band&n;&t;&t;&t; * or dump to the standard error.&n;&t;&t;&t; */
id|sz
op_assign
id|xread
c_func
(paren
id|pack_objects.err
comma
id|progress
comma
r_sizeof
(paren
id|progress
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
OL
id|sz
)paren
id|send_client_data
c_func
(paren
l_int|2
comma
id|progress
comma
id|sz
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sz
op_eq
l_int|0
)paren
(brace
id|close
c_func
(paren
id|pack_objects.err
)paren
suffix:semicolon
id|pack_objects.err
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_goto
id|fail
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|pack_objects
)paren
)paren
(brace
id|error
c_func
(paren
l_string|&quot;git upload-pack: git-pack-objects died with error.&quot;
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|finish_async
c_func
(paren
op_amp
id|rev_list
)paren
)paren
r_goto
id|fail
suffix:semicolon
multiline_comment|/* error was already reported */
multiline_comment|/* flush the data */
r_if
c_cond
(paren
l_int|0
op_le
id|buffered
)paren
(brace
id|data
(braket
l_int|0
)braket
op_assign
id|buffered
suffix:semicolon
id|sz
op_assign
id|send_client_data
c_func
(paren
l_int|1
comma
id|data
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;flushed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|use_sideband
)paren
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
id|fail
suffix:colon
id|send_client_data
c_func
(paren
l_int|3
comma
id|abort_msg
comma
r_sizeof
(paren
id|abort_msg
)paren
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git upload-pack: %s&quot;
comma
id|abort_msg
)paren
suffix:semicolon
)brace
DECL|function|got_sha1
r_static
r_int
id|got_sha1
c_func
(paren
r_char
op_star
id|hex
comma
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
suffix:semicolon
r_int
id|we_knew_they_have
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git upload-pack: expected SHA1 object, got &squot;%s&squot;&quot;
comma
id|hex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_sha1_file
c_func
(paren
id|sha1
)paren
)paren
r_return
l_int|1
suffix:semicolon
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
op_logical_neg
(paren
id|o
op_logical_and
id|o-&gt;parsed
)paren
)paren
id|o
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
id|o
)paren
id|die
c_func
(paren
l_string|&quot;oops (%s)&quot;
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
id|o-&gt;type
op_eq
id|OBJ_COMMIT
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
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
id|o-&gt;flags
op_amp
id|THEY_HAVE
)paren
id|we_knew_they_have
op_assign
l_int|1
suffix:semicolon
r_else
id|o-&gt;flags
op_or_assign
id|THEY_HAVE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldest_have
op_logical_or
(paren
id|commit-&gt;date
OL
id|oldest_have
)paren
)paren
id|oldest_have
op_assign
id|commit-&gt;date
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
)paren
id|parents-&gt;item-&gt;object.flags
op_or_assign
id|THEY_HAVE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|we_knew_they_have
)paren
(brace
id|add_object_array
c_func
(paren
id|o
comma
l_int|NULL
comma
op_amp
id|have_obj
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|reachable
r_static
r_int
id|reachable
c_func
(paren
r_struct
id|commit
op_star
id|want
)paren
(brace
r_struct
id|commit_list
op_star
id|work
op_assign
l_int|NULL
suffix:semicolon
id|insert_by_date
c_func
(paren
id|want
comma
op_amp
id|work
)paren
suffix:semicolon
r_while
c_loop
(paren
id|work
)paren
(brace
r_struct
id|commit_list
op_star
id|list
op_assign
id|work-&gt;next
suffix:semicolon
r_struct
id|commit
op_star
id|commit
op_assign
id|work-&gt;item
suffix:semicolon
id|free
c_func
(paren
id|work
)paren
suffix:semicolon
id|work
op_assign
id|list
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|THEY_HAVE
)paren
(brace
id|want-&gt;object.flags
op_or_assign
id|COMMON_KNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|commit-&gt;object.parsed
)paren
id|parse_object
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|REACHABLE
)paren
r_continue
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|REACHABLE
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;date
OL
id|oldest_have
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|commit-&gt;parents
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|list-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|parent-&gt;object.flags
op_amp
id|REACHABLE
)paren
)paren
id|insert_by_date
c_func
(paren
id|parent
comma
op_amp
id|work
)paren
suffix:semicolon
)brace
)brace
id|want-&gt;object.flags
op_or_assign
id|REACHABLE
suffix:semicolon
id|clear_commit_marks
c_func
(paren
id|want
comma
id|REACHABLE
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|work
)paren
suffix:semicolon
r_return
(paren
id|want-&gt;object.flags
op_amp
id|COMMON_KNOWN
)paren
suffix:semicolon
)brace
DECL|function|ok_to_give_up
r_static
r_int
id|ok_to_give_up
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_obj.nr
)paren
r_return
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
id|want_obj.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|object
op_star
id|want
op_assign
id|want_obj.objects
(braket
id|i
)braket
dot
id|item
suffix:semicolon
r_if
c_cond
(paren
id|want-&gt;flags
op_amp
id|COMMON_KNOWN
)paren
r_continue
suffix:semicolon
id|want
op_assign
id|deref_tag
c_func
(paren
id|want
comma
l_string|&quot;a want line&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|want
op_logical_or
id|want-&gt;type
op_ne
id|OBJ_COMMIT
)paren
(brace
multiline_comment|/* no way to tell if this is reachable by&n;&t;&t;&t; * looking at the ancestry chain alone, so&n;&t;&t;&t; * leave a note to ourselves not to worry about&n;&t;&t;&t; * this object anymore.&n;&t;&t;&t; */
id|want_obj.objects
(braket
id|i
)braket
dot
id|item-&gt;flags
op_or_assign
id|COMMON_KNOWN
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|reachable
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|want
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_common_commits
r_static
r_int
id|get_common_commits
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|line
(braket
l_int|1000
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
id|hex
(braket
l_int|41
)braket
comma
id|last_hex
(braket
l_int|41
)braket
suffix:semicolon
id|save_commit_buffer
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
(brace
r_if
c_cond
(paren
id|have_obj.nr
op_eq
l_int|0
op_logical_or
id|multi_ack
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NAK&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|strip
c_func
(paren
id|line
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;have &quot;
)paren
)paren
(brace
r_switch
c_cond
(paren
id|got_sha1
c_func
(paren
id|line
op_plus
l_int|5
comma
id|sha1
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* they have what we do not */
r_if
c_cond
(paren
id|multi_ack
op_logical_and
id|ok_to_give_up
c_func
(paren
)paren
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK %s continue&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|memcpy
c_func
(paren
id|hex
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
l_int|41
)paren
suffix:semicolon
r_if
c_cond
(paren
id|multi_ack
)paren
(brace
r_const
r_char
op_star
id|msg
op_assign
l_string|&quot;ACK %s continue&bslash;n&quot;
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
id|msg
comma
id|hex
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|last_hex
comma
id|hex
comma
l_int|41
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|have_obj.nr
op_eq
l_int|1
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK %s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;done&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|have_obj.nr
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|multi_ack
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;ACK %s&bslash;n&quot;
comma
id|last_hex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;NAK&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|die
c_func
(paren
l_string|&quot;git upload-pack: expected SHA1 list, got &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
)brace
)brace
DECL|function|receive_needs
r_static
r_void
id|receive_needs
c_func
(paren
r_void
)paren
(brace
r_struct
id|object_array
id|shallows
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_static
r_char
id|line
(braket
l_int|1000
)braket
suffix:semicolon
r_int
id|len
comma
id|depth
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|debug_fd
)paren
id|write_in_full
c_func
(paren
id|debug_fd
comma
l_string|&quot;#S&bslash;n&quot;
comma
l_int|3
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|object
op_star
id|o
suffix:semicolon
r_int
r_char
id|sha1_buf
(braket
l_int|20
)braket
suffix:semicolon
id|len
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
suffix:semicolon
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|debug_fd
)paren
id|write_in_full
c_func
(paren
id|debug_fd
comma
id|line
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;shallow &quot;
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
r_struct
id|object
op_star
id|object
suffix:semicolon
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|line
op_plus
l_int|8
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;invalid shallow line: %s&quot;
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
c_func
(paren
l_string|&quot;did not find object for %s&quot;
comma
id|line
)paren
suffix:semicolon
id|object-&gt;flags
op_or_assign
id|CLIENT_SHALLOW
suffix:semicolon
id|add_object_array
c_func
(paren
id|object
comma
l_int|NULL
comma
op_amp
id|shallows
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;deepen &quot;
)paren
)paren
(brace
r_char
op_star
id|end
suffix:semicolon
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
id|depth
op_assign
id|strtol
c_func
(paren
id|line
op_plus
l_int|7
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_eq
id|line
op_plus
l_int|7
op_logical_or
id|depth
op_le
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Invalid deepen: %s&quot;
comma
id|line
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|line
comma
l_string|&quot;want &quot;
)paren
op_logical_or
id|get_sha1_hex
c_func
(paren
id|line
op_plus
l_int|5
comma
id|sha1_buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git upload-pack: protocol error, &quot;
l_string|&quot;expected to get sha, not &squot;%s&squot;&quot;
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;multi_ack&quot;
)paren
)paren
id|multi_ack
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;thin-pack&quot;
)paren
)paren
id|use_thin_pack
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;ofs-delta&quot;
)paren
)paren
id|use_ofs_delta
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;side-band-64k&quot;
)paren
)paren
id|use_sideband
op_assign
id|LARGE_PACKET_MAX
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;side-band&quot;
)paren
)paren
id|use_sideband
op_assign
id|DEFAULT_PACKET_MAX
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;no-progress&quot;
)paren
)paren
id|no_progress
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|line
op_plus
l_int|45
comma
l_string|&quot;include-tag&quot;
)paren
)paren
id|use_include_tag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We have sent all our refs already, and the other end&n;&t;&t; * should have chosen out of them; otherwise they are&n;&t;&t; * asking for nonsense.&n;&t;&t; *&n;&t;&t; * Hmph.  We may later want to allow &quot;want&quot; line that&n;&t;&t; * asks for something like &quot;master~10&quot; (symbolic)...&n;&t;&t; * would it make sense?  I don&squot;t know.&n;&t;&t; */
id|o
op_assign
id|lookup_object
c_func
(paren
id|sha1_buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
op_logical_or
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|OUR_REF
)paren
)paren
id|die
c_func
(paren
l_string|&quot;git upload-pack: not our ref %s&quot;
comma
id|line
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|WANTED
)paren
)paren
(brace
id|o-&gt;flags
op_or_assign
id|WANTED
suffix:semicolon
id|add_object_array
c_func
(paren
id|o
comma
l_int|NULL
comma
op_amp
id|want_obj
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|debug_fd
)paren
id|write_in_full
c_func
(paren
id|debug_fd
comma
l_string|&quot;#E&bslash;n&quot;
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_eq
l_int|0
op_logical_and
id|shallows.nr
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|depth
OG
l_int|0
)paren
(brace
r_struct
id|commit_list
op_star
id|result
comma
op_star
id|backup
suffix:semicolon
r_int
id|i
suffix:semicolon
id|backup
op_assign
id|result
op_assign
id|get_shallow_commits
c_func
(paren
op_amp
id|want_obj
comma
id|depth
comma
id|SHALLOW
comma
id|NOT_SHALLOW
)paren
suffix:semicolon
r_while
c_loop
(paren
id|result
)paren
(brace
r_struct
id|object
op_star
id|object
op_assign
op_amp
id|result-&gt;item-&gt;object
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|object-&gt;flags
op_amp
(paren
id|CLIENT_SHALLOW
op_or
id|NOT_SHALLOW
)paren
)paren
)paren
(brace
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;shallow %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|object-&gt;sha1
)paren
)paren
suffix:semicolon
id|register_shallow
c_func
(paren
id|object-&gt;sha1
)paren
suffix:semicolon
)brace
id|result
op_assign
id|result-&gt;next
suffix:semicolon
)brace
id|free_commit_list
c_func
(paren
id|backup
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
id|shallows.nr
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
id|shallows.objects
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
id|NOT_SHALLOW
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;unshallow %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|object-&gt;sha1
)paren
)paren
suffix:semicolon
id|object-&gt;flags
op_and_assign
op_complement
id|CLIENT_SHALLOW
suffix:semicolon
multiline_comment|/* make sure the real parents are parsed */
id|unregister_shallow
c_func
(paren
id|object-&gt;sha1
)paren
suffix:semicolon
id|object-&gt;parsed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|parse_commit
c_func
(paren
(paren
r_struct
id|commit
op_star
)paren
id|object
)paren
)paren
id|die
c_func
(paren
l_string|&quot;invalid commit&quot;
)paren
suffix:semicolon
id|parents
op_assign
(paren
(paren
r_struct
id|commit
op_star
)paren
id|object
)paren
op_member_access_from_pointer
id|parents
suffix:semicolon
r_while
c_loop
(paren
id|parents
)paren
(brace
id|add_object_array
c_func
(paren
op_amp
id|parents-&gt;item-&gt;object
comma
l_int|NULL
comma
op_amp
id|want_obj
)paren
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/* make sure commit traversal conforms to client */
id|register_shallow
c_func
(paren
id|object-&gt;sha1
)paren
suffix:semicolon
)brace
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|shallows.nr
OG
l_int|0
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
id|shallows.nr
suffix:semicolon
id|i
op_increment
)paren
id|register_shallow
c_func
(paren
id|shallows.objects
(braket
id|i
)braket
dot
id|item-&gt;sha1
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|shallows.objects
)paren
suffix:semicolon
)brace
DECL|function|send_ref
r_static
r_int
id|send_ref
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
r_static
r_const
r_char
op_star
id|capabilities
op_assign
l_string|&quot;multi_ack thin-pack side-band&quot;
l_string|&quot; side-band-64k ofs-delta shallow no-progress&quot;
l_string|&quot; include-tag&quot;
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|o
)paren
id|die
c_func
(paren
l_string|&quot;git upload-pack: cannot find object %s:&quot;
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
id|capabilities
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s%c%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|refname
comma
l_int|0
comma
id|capabilities
)paren
suffix:semicolon
r_else
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|refname
)paren
suffix:semicolon
id|capabilities
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o-&gt;flags
op_amp
id|OUR_REF
)paren
)paren
(brace
id|o-&gt;flags
op_or_assign
id|OUR_REF
suffix:semicolon
id|nr_our_refs
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o-&gt;type
op_eq
id|OBJ_TAG
)paren
(brace
id|o
op_assign
id|deref_tag
c_func
(paren
id|o
comma
id|refname
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|o
)paren
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s %s^{}&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
comma
id|refname
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|upload_pack
r_static
r_void
id|upload_pack
c_func
(paren
r_void
)paren
(brace
id|reset_timeout
c_func
(paren
)paren
suffix:semicolon
id|head_ref
c_func
(paren
id|send_ref
comma
l_int|NULL
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|send_ref
comma
l_int|NULL
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|receive_needs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|want_obj.nr
)paren
(brace
id|get_common_commits
c_func
(paren
)paren
suffix:semicolon
id|create_pack_file
c_func
(paren
)paren
suffix:semicolon
)brace
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
r_char
op_star
id|dir
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|strict
op_assign
l_int|0
suffix:semicolon
id|git_extract_argv0_path
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|read_replace_refs
op_assign
l_int|0
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
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--strict&quot;
)paren
)paren
(brace
id|strict
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
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--timeout=&quot;
)paren
)paren
(brace
id|timeout
op_assign
id|atoi
c_func
(paren
id|arg
op_plus
l_int|10
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_ne
id|argc
op_minus
l_int|1
)paren
id|usage
c_func
(paren
id|upload_pack_usage
)paren
suffix:semicolon
id|setup_path
c_func
(paren
)paren
suffix:semicolon
id|dir
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enter_repo
c_func
(paren
id|dir
comma
id|strict
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; does not appear to be a git repository&quot;
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_repository_shallow
c_func
(paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;attempt to fetch/clone from a shallow repository&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_DEBUG_SEND_PACK&quot;
)paren
)paren
id|debug_fd
op_assign
id|atoi
c_func
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_DEBUG_SEND_PACK&quot;
)paren
)paren
suffix:semicolon
id|upload_pack
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
