macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;sideband.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;connect.h&quot;
macro_line|#include &quot;send-pack.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;version.h&quot;
macro_line|#include &quot;sha1-array.h&quot;
DECL|variable|send_pack_usage
r_static
r_const
r_char
id|send_pack_usage
(braket
)braket
op_assign
l_string|&quot;git send-pack [--all | --mirror] [--dry-run] [--force] [--receive-pack=&lt;git-receive-pack&gt;] [--verbose] [--thin] [&lt;host&gt;:]&lt;directory&gt; [&lt;ref&gt;...]&bslash;n&quot;
l_string|&quot;  --all and explicit &lt;ref&gt; specification are mutually exclusive.&quot;
suffix:semicolon
DECL|variable|args
r_static
r_struct
id|send_pack_args
id|args
suffix:semicolon
DECL|function|print_helper_status
r_static
r_void
id|print_helper_status
c_func
(paren
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
(brace
r_const
r_char
op_star
id|msg
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|res
suffix:semicolon
r_switch
c_cond
(paren
id|ref-&gt;status
)paren
(brace
r_case
id|REF_STATUS_NONE
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;no match&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_OK
suffix:colon
id|res
op_assign
l_string|&quot;ok&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_UPTODATE
suffix:colon
id|res
op_assign
l_string|&quot;ok&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;up to date&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NONFASTFORWARD
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;non-fast forward&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_FETCH_FIRST
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;fetch first&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NEEDS_FORCE
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;needs force&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_STALE
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;stale info&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_ALREADY_EXISTS
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
id|msg
op_assign
l_string|&quot;already exists&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_REJECT_NODELETE
suffix:colon
r_case
id|REF_STATUS_REMOTE_REJECT
suffix:colon
id|res
op_assign
l_string|&quot;error&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_STATUS_EXPECTING_REPORT
suffix:colon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
id|strbuf_reset
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%s %s&quot;
comma
id|res
comma
id|ref-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref-&gt;remote_status
)paren
id|msg
op_assign
id|ref-&gt;remote_status
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
id|quote_two_c_style
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;&quot;
comma
id|msg
comma
l_int|0
)paren
suffix:semicolon
)brace
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|write_or_die
c_func
(paren
l_int|1
comma
id|buf.buf
comma
id|buf.len
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|cmd_send_pack
r_int
id|cmd_send_pack
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
id|i
comma
id|nr_refspecs
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
op_star
id|refspecs
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|remote_name
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|remote
op_star
id|remote
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|child_process
op_star
id|conn
suffix:semicolon
r_struct
id|sha1_array
id|extra_have
op_assign
id|SHA1_ARRAY_INIT
suffix:semicolon
r_struct
id|sha1_array
id|shallow
op_assign
id|SHA1_ARRAY_INIT
suffix:semicolon
r_struct
id|ref
op_star
id|remote_refs
comma
op_star
id|local_refs
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|helper_status
op_assign
l_int|0
suffix:semicolon
r_int
id|send_all
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|receivepack
op_assign
l_string|&quot;git-receive-pack&quot;
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
r_int
id|reject_reasons
suffix:semicolon
r_int
id|progress
op_assign
l_int|1
suffix:semicolon
r_int
id|from_stdin
op_assign
l_int|0
suffix:semicolon
r_struct
id|push_cas_option
id|cas
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|argv
op_increment
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
comma
id|argv
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
op_star
id|argv
suffix:semicolon
r_if
c_cond
(paren
op_star
id|arg
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|arg
comma
l_string|&quot;--receive-pack=&quot;
)paren
)paren
(brace
id|receivepack
op_assign
id|arg
op_plus
l_int|15
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|arg
comma
l_string|&quot;--exec=&quot;
)paren
)paren
(brace
id|receivepack
op_assign
id|arg
op_plus
l_int|7
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|arg
comma
l_string|&quot;--remote=&quot;
)paren
)paren
(brace
id|remote_name
op_assign
id|arg
op_plus
l_int|9
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
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|send_all
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--dry-run&quot;
)paren
)paren
(brace
id|args.dry_run
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--mirror&quot;
)paren
)paren
(brace
id|args.send_mirror
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--force&quot;
)paren
)paren
(brace
id|args.force_update
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--quiet&quot;
)paren
)paren
(brace
id|args.quiet
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--verbose&quot;
)paren
)paren
(brace
id|args.verbose
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--signed&quot;
)paren
)paren
(brace
id|args.push_cert
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--progress&quot;
)paren
)paren
(brace
id|progress
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--no-progress&quot;
)paren
)paren
(brace
id|progress
op_assign
l_int|0
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
l_string|&quot;--thin&quot;
)paren
)paren
(brace
id|args.use_thin_pack
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stateless-rpc&quot;
)paren
)paren
(brace
id|args.stateless_rpc
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
id|from_stdin
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--helper-status&quot;
)paren
)paren
(brace
id|helper_status
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
id|CAS_OPT_NAME
)paren
)paren
(brace
r_if
c_cond
(paren
id|parse_push_cas_option
c_func
(paren
op_amp
id|cas
comma
l_int|NULL
comma
l_int|0
)paren
OL
l_int|0
)paren
m_exit
(paren
l_int|1
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
l_string|&quot;--no-&quot;
id|CAS_OPT_NAME
)paren
)paren
(brace
r_if
c_cond
(paren
id|parse_push_cas_option
c_func
(paren
op_amp
id|cas
comma
l_int|NULL
comma
l_int|1
)paren
OL
l_int|0
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|starts_with
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
id|CAS_OPT_NAME
l_string|&quot;=&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|parse_push_cas_option
c_func
(paren
op_amp
id|cas
comma
id|strchr
c_func
(paren
id|arg
comma
l_char|&squot;=&squot;
)paren
op_plus
l_int|1
comma
l_int|0
)paren
OL
l_int|0
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|send_pack_usage
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
(brace
id|dest
op_assign
id|arg
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|refspecs
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
id|argv
suffix:semicolon
id|nr_refspecs
op_assign
id|argc
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
id|usage
c_func
(paren
id|send_pack_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_stdin
)paren
(brace
r_struct
id|argv_array
id|all_refspecs
op_assign
id|ARGV_ARRAY_INIT
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
id|nr_refspecs
suffix:semicolon
id|i
op_increment
)paren
id|argv_array_push
c_func
(paren
op_amp
id|all_refspecs
comma
id|refspecs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|args.stateless_rpc
)paren
(brace
r_const
r_char
op_star
id|buf
suffix:semicolon
r_while
c_loop
(paren
(paren
id|buf
op_assign
id|packet_read_line
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
)paren
)paren
id|argv_array_push
c_func
(paren
op_amp
id|all_refspecs
comma
id|buf
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|strbuf
id|line
op_assign
id|STRBUF_INIT
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|line
comma
id|stdin
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
id|argv_array_push
c_func
(paren
op_amp
id|all_refspecs
comma
id|line.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
)brace
id|refspecs
op_assign
id|all_refspecs.argv
suffix:semicolon
id|nr_refspecs
op_assign
id|all_refspecs.argc
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * --all and --mirror are incompatible; neither makes sense&n;&t; * with any refspecs.&n;&t; */
r_if
c_cond
(paren
(paren
id|refspecs
op_logical_and
(paren
id|send_all
op_logical_or
id|args.send_mirror
)paren
)paren
op_logical_or
(paren
id|send_all
op_logical_and
id|args.send_mirror
)paren
)paren
id|usage
c_func
(paren
id|send_pack_usage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote_name
)paren
(brace
id|remote
op_assign
id|remote_get
c_func
(paren
id|remote_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote_has_url
c_func
(paren
id|remote
comma
id|dest
)paren
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Destination %s is not a uri for %s&quot;
comma
id|dest
comma
id|remote_name
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|progress
op_eq
l_int|1
)paren
id|progress
op_assign
op_logical_neg
id|args.quiet
op_logical_and
id|isatty
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|args.progress
op_assign
id|progress
suffix:semicolon
r_if
c_cond
(paren
id|args.stateless_rpc
)paren
(brace
id|conn
op_assign
l_int|NULL
suffix:semicolon
id|fd
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|fd
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|conn
op_assign
id|git_connect
c_func
(paren
id|fd
comma
id|dest
comma
id|receivepack
comma
id|args.verbose
ques
c_cond
id|CONNECT_VERBOSE
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|get_remote_heads
c_func
(paren
id|fd
(braket
l_int|0
)braket
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|remote_refs
comma
id|REF_NORMAL
comma
op_amp
id|extra_have
comma
op_amp
id|shallow
)paren
suffix:semicolon
id|transport_verify_remote_names
c_func
(paren
id|nr_refspecs
comma
id|refspecs
)paren
suffix:semicolon
id|local_refs
op_assign
id|get_local_heads
c_func
(paren
)paren
suffix:semicolon
id|flags
op_assign
id|MATCH_REFS_NONE
suffix:semicolon
r_if
c_cond
(paren
id|send_all
)paren
id|flags
op_or_assign
id|MATCH_REFS_ALL
suffix:semicolon
r_if
c_cond
(paren
id|args.send_mirror
)paren
id|flags
op_or_assign
id|MATCH_REFS_MIRROR
suffix:semicolon
multiline_comment|/* match them up */
r_if
c_cond
(paren
id|match_push_refs
c_func
(paren
id|local_refs
comma
op_amp
id|remote_refs
comma
id|nr_refspecs
comma
id|refspecs
comma
id|flags
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_empty_cas
c_func
(paren
op_amp
id|cas
)paren
)paren
id|apply_push_cas
c_func
(paren
op_amp
id|cas
comma
id|remote
comma
id|remote_refs
)paren
suffix:semicolon
id|set_ref_status_for_push
c_func
(paren
id|remote_refs
comma
id|args.send_mirror
comma
id|args.force_update
)paren
suffix:semicolon
id|ret
op_assign
id|send_pack
c_func
(paren
op_amp
id|args
comma
id|fd
comma
id|conn
comma
id|remote_refs
comma
op_amp
id|extra_have
)paren
suffix:semicolon
r_if
c_cond
(paren
id|helper_status
)paren
id|print_helper_status
c_func
(paren
id|remote_refs
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ret
op_or_assign
id|finish_connect
c_func
(paren
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|helper_status
)paren
id|transport_print_push_status
c_func
(paren
id|dest
comma
id|remote_refs
comma
id|args.verbose
comma
l_int|0
comma
op_amp
id|reject_reasons
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|args.dry_run
op_logical_and
id|remote
)paren
(brace
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_for
c_loop
(paren
id|ref
op_assign
id|remote_refs
suffix:semicolon
id|ref
suffix:semicolon
id|ref
op_assign
id|ref-&gt;next
)paren
id|transport_update_tracking_ref
c_func
(paren
id|remote
comma
id|ref
comma
id|args.verbose
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
op_logical_neg
id|transport_refs_pushed
c_func
(paren
id|remote_refs
)paren
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Everything up-to-date&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
