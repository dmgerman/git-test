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
macro_line|#include &quot;gpg-interface.h&quot;
macro_line|#include &quot;gettext.h&quot;
DECL|variable|send_pack_usage
r_static
r_const
r_char
op_star
r_const
id|send_pack_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git send-pack [--all | --mirror] [--dry-run] [--force] &quot;
l_string|&quot;[--receive-pack=&lt;git-receive-pack&gt;] [--verbose] [--thin] [--atomic] &quot;
l_string|&quot;[&lt;host&gt;:]&lt;directory&gt; [&lt;ref&gt;...]&bslash;n&quot;
l_string|&quot;  --all and explicit &lt;ref&gt; specification are mutually exclusive.&quot;
)paren
comma
l_int|NULL
comma
)brace
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
DECL|function|send_pack_config
r_static
r_int
id|send_pack_config
c_func
(paren
r_const
r_char
op_star
id|k
comma
r_const
r_char
op_star
id|v
comma
r_void
op_star
id|cb
)paren
(brace
id|git_gpg_config
c_func
(paren
id|k
comma
id|v
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|k
comma
l_string|&quot;push.gpgsign&quot;
)paren
)paren
(brace
r_const
r_char
op_star
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_config_get_value
c_func
(paren
l_string|&quot;push.gpgsign&quot;
comma
op_amp
id|value
)paren
)paren
(brace
r_switch
c_cond
(paren
id|git_config_maybe_bool
c_func
(paren
l_string|&quot;push.gpgsign&quot;
comma
id|value
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|args.push_cert
op_assign
id|SEND_PACK_PUSH_CERT_NEVER
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|args.push_cert
op_assign
id|SEND_PACK_PUSH_CERT_ALWAYS
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|value
op_logical_and
op_logical_neg
id|strcasecmp
c_func
(paren
id|value
comma
l_string|&quot;if-asked&quot;
)paren
)paren
id|args.push_cert
op_assign
id|SEND_PACK_PUSH_CERT_IF_ASKED
suffix:semicolon
r_else
r_return
id|error
c_func
(paren
l_string|&quot;Invalid value for &squot;%s&squot;&quot;
comma
id|k
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
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
r_int
id|verbose
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
id|dry_run
op_assign
l_int|0
suffix:semicolon
r_int
id|send_mirror
op_assign
l_int|0
suffix:semicolon
r_int
id|force_update
op_assign
l_int|0
suffix:semicolon
r_int
id|quiet
op_assign
l_int|0
suffix:semicolon
r_int
id|push_cert
op_assign
l_int|0
suffix:semicolon
r_int
id|use_thin_pack
op_assign
l_int|0
suffix:semicolon
r_int
id|atomic
op_assign
l_int|0
suffix:semicolon
r_int
id|stateless_rpc
op_assign
l_int|0
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
r_struct
id|option
id|options
(braket
)braket
op_assign
(brace
id|OPT__VERBOSITY
c_func
(paren
op_amp
id|verbose
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;receive-pack&quot;
comma
op_amp
id|receivepack
comma
l_string|&quot;receive-pack&quot;
comma
id|N_
c_func
(paren
l_string|&quot;receive pack program&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;exec&quot;
comma
op_amp
id|receivepack
comma
l_string|&quot;receive-pack&quot;
comma
id|N_
c_func
(paren
l_string|&quot;receive pack program&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;remote&quot;
comma
op_amp
id|remote_name
comma
l_string|&quot;remote&quot;
comma
id|N_
c_func
(paren
l_string|&quot;remote name&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;all&quot;
comma
op_amp
id|send_all
comma
id|N_
c_func
(paren
l_string|&quot;push all refs&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;n&squot;
comma
l_string|&quot;dry-run&quot;
comma
op_amp
id|dry_run
comma
id|N_
c_func
(paren
l_string|&quot;dry run&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;mirror&quot;
comma
op_amp
id|send_mirror
comma
id|N_
c_func
(paren
l_string|&quot;mirror all refs&quot;
)paren
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
id|force_update
comma
id|N_
c_func
(paren
l_string|&quot;force updates&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
l_string|&quot;signed&quot;
comma
op_amp
id|push_cert
comma
l_string|&quot;yes|no|if-asked&quot;
comma
id|N_
c_func
(paren
l_string|&quot;GPG sign the push&quot;
)paren
comma
id|PARSE_OPT_OPTARG
comma
id|option_parse_push_signed
)brace
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;progress&quot;
comma
op_amp
id|progress
comma
id|N_
c_func
(paren
l_string|&quot;force progress reporting&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;thin&quot;
comma
op_amp
id|use_thin_pack
comma
id|N_
c_func
(paren
l_string|&quot;use thin pack&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;atomic&quot;
comma
op_amp
id|atomic
comma
id|N_
c_func
(paren
l_string|&quot;request atomic transaction on remote side&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;stateless-rpc&quot;
comma
op_amp
id|stateless_rpc
comma
id|N_
c_func
(paren
l_string|&quot;use stateless RPC protocol&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;stdin&quot;
comma
op_amp
id|from_stdin
comma
id|N_
c_func
(paren
l_string|&quot;read refs from stdin&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;helper-status&quot;
comma
op_amp
id|helper_status
comma
id|N_
c_func
(paren
l_string|&quot;print status from remote helper&quot;
)paren
)paren
comma
(brace
id|OPTION_CALLBACK
comma
l_int|0
comma
id|CAS_OPT_NAME
comma
op_amp
id|cas
comma
id|N_
c_func
(paren
l_string|&quot;refname&gt;:&lt;expect&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;require old value of ref to be at this value&quot;
)paren
comma
id|PARSE_OPT_OPTARG
comma
id|parseopt_push_cas_option
)brace
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|send_pack_config
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
id|send_pack_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
(brace
id|dest
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|refspecs
op_assign
(paren
r_const
r_char
op_star
op_star
)paren
(paren
id|argv
op_plus
l_int|1
)paren
suffix:semicolon
id|nr_refspecs
op_assign
id|argc
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dest
)paren
id|usage_with_options
c_func
(paren
id|send_pack_usage
comma
id|options
)paren
suffix:semicolon
id|args.verbose
op_assign
id|verbose
suffix:semicolon
id|args.dry_run
op_assign
id|dry_run
suffix:semicolon
id|args.send_mirror
op_assign
id|send_mirror
suffix:semicolon
id|args.force_update
op_assign
id|force_update
suffix:semicolon
id|args.quiet
op_assign
id|quiet
suffix:semicolon
id|args.push_cert
op_assign
id|push_cert
suffix:semicolon
id|args.progress
op_assign
id|progress
suffix:semicolon
id|args.use_thin_pack
op_assign
id|use_thin_pack
suffix:semicolon
id|args.atomic
op_assign
id|atomic
suffix:semicolon
id|args.stateless_rpc
op_assign
id|stateless_rpc
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
id|usage_with_options
c_func
(paren
id|send_pack_usage
comma
id|options
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
