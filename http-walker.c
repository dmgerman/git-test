macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;walker.h&quot;
macro_line|#include &quot;http.h&quot;
DECL|struct|alt_base
r_struct
id|alt_base
(brace
DECL|member|base
r_char
op_star
id|base
suffix:semicolon
DECL|member|got_indices
r_int
id|got_indices
suffix:semicolon
DECL|member|packs
r_struct
id|packed_git
op_star
id|packs
suffix:semicolon
DECL|member|next
r_struct
id|alt_base
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|object_request_state
r_enum
id|object_request_state
(brace
DECL|enumerator|WAITING
id|WAITING
comma
DECL|enumerator|ABORTED
id|ABORTED
comma
DECL|enumerator|ACTIVE
id|ACTIVE
comma
DECL|enumerator|COMPLETE
id|COMPLETE
)brace
suffix:semicolon
DECL|struct|object_request
r_struct
id|object_request
(brace
DECL|member|walker
r_struct
id|walker
op_star
id|walker
suffix:semicolon
DECL|member|sha1
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|repo
r_struct
id|alt_base
op_star
id|repo
suffix:semicolon
DECL|member|state
r_enum
id|object_request_state
id|state
suffix:semicolon
DECL|member|req
r_struct
id|http_object_request
op_star
id|req
suffix:semicolon
DECL|member|next
r_struct
id|object_request
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|alternates_request
r_struct
id|alternates_request
(brace
DECL|member|walker
r_struct
id|walker
op_star
id|walker
suffix:semicolon
DECL|member|base
r_const
r_char
op_star
id|base
suffix:semicolon
DECL|member|url
r_char
op_star
id|url
suffix:semicolon
DECL|member|buffer
r_struct
id|strbuf
op_star
id|buffer
suffix:semicolon
DECL|member|slot
r_struct
id|active_request_slot
op_star
id|slot
suffix:semicolon
DECL|member|http_specific
r_int
id|http_specific
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|walker_data
r_struct
id|walker_data
(brace
DECL|member|url
r_const
r_char
op_star
id|url
suffix:semicolon
DECL|member|got_alternates
r_int
id|got_alternates
suffix:semicolon
DECL|member|alt
r_struct
id|alt_base
op_star
id|alt
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|object_queue_head
r_static
r_struct
id|object_request
op_star
id|object_queue_head
suffix:semicolon
r_static
r_void
id|fetch_alternates
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_const
r_char
op_star
id|base
)paren
suffix:semicolon
r_static
r_void
id|process_object_response
c_func
(paren
r_void
op_star
id|callback_data
)paren
suffix:semicolon
DECL|function|start_object_request
r_static
r_void
id|start_object_request
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_struct
id|object_request
op_star
id|obj_req
)paren
(brace
r_struct
id|active_request_slot
op_star
id|slot
suffix:semicolon
r_struct
id|http_object_request
op_star
id|req
suffix:semicolon
id|req
op_assign
id|new_http_object_request
c_func
(paren
id|obj_req-&gt;repo-&gt;base
comma
id|obj_req-&gt;sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req
op_eq
l_int|NULL
)paren
(brace
id|obj_req-&gt;state
op_assign
id|ABORTED
suffix:semicolon
r_return
suffix:semicolon
)brace
id|obj_req-&gt;req
op_assign
id|req
suffix:semicolon
id|slot
op_assign
id|req-&gt;slot
suffix:semicolon
id|slot-&gt;callback_func
op_assign
id|process_object_response
suffix:semicolon
id|slot-&gt;callback_data
op_assign
id|obj_req
suffix:semicolon
multiline_comment|/* Try to get the request started, abort the request on error */
id|obj_req-&gt;state
op_assign
id|ACTIVE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start_active_slot
c_func
(paren
id|slot
)paren
)paren
(brace
id|obj_req-&gt;state
op_assign
id|ABORTED
suffix:semicolon
id|release_http_object_request
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|finish_object_request
r_static
r_void
id|finish_object_request
c_func
(paren
r_struct
id|object_request
op_star
id|obj_req
)paren
(brace
r_if
c_cond
(paren
id|finish_http_object_request
c_func
(paren
id|obj_req-&gt;req
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|obj_req-&gt;req-&gt;rename
op_eq
l_int|0
)paren
id|walker_say
c_func
(paren
id|obj_req-&gt;walker
comma
l_string|&quot;got %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|obj_req-&gt;sha1
)paren
)paren
suffix:semicolon
)brace
DECL|function|process_object_response
r_static
r_void
id|process_object_response
c_func
(paren
r_void
op_star
id|callback_data
)paren
(brace
r_struct
id|object_request
op_star
id|obj_req
op_assign
(paren
r_struct
id|object_request
op_star
)paren
id|callback_data
suffix:semicolon
r_struct
id|walker
op_star
id|walker
op_assign
id|obj_req-&gt;walker
suffix:semicolon
r_struct
id|walker_data
op_star
id|data
op_assign
id|walker-&gt;data
suffix:semicolon
r_struct
id|alt_base
op_star
id|alt
op_assign
id|data-&gt;alt
suffix:semicolon
id|process_http_object_request
c_func
(paren
id|obj_req-&gt;req
)paren
suffix:semicolon
id|obj_req-&gt;state
op_assign
id|COMPLETE
suffix:semicolon
multiline_comment|/* Use alternates if necessary */
r_if
c_cond
(paren
id|missing_target
c_func
(paren
id|obj_req-&gt;req
)paren
)paren
(brace
id|fetch_alternates
c_func
(paren
id|walker
comma
id|alt-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_req-&gt;repo-&gt;next
op_ne
l_int|NULL
)paren
(brace
id|obj_req-&gt;repo
op_assign
id|obj_req-&gt;repo-&gt;next
suffix:semicolon
id|release_http_object_request
c_func
(paren
id|obj_req-&gt;req
)paren
suffix:semicolon
id|start_object_request
c_func
(paren
id|walker
comma
id|obj_req
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|finish_object_request
c_func
(paren
id|obj_req
)paren
suffix:semicolon
)brace
DECL|function|release_object_request
r_static
r_void
id|release_object_request
c_func
(paren
r_struct
id|object_request
op_star
id|obj_req
)paren
(brace
r_struct
id|object_request
op_star
id|entry
op_assign
id|object_queue_head
suffix:semicolon
r_if
c_cond
(paren
id|obj_req-&gt;req
op_ne
l_int|NULL
op_logical_and
id|obj_req-&gt;req-&gt;localfile
op_ne
l_int|1
)paren
id|error
c_func
(paren
l_string|&quot;fd leakage in release: %d&quot;
comma
id|obj_req-&gt;req-&gt;localfile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_req
op_eq
id|object_queue_head
)paren
(brace
id|object_queue_head
op_assign
id|obj_req-&gt;next
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|entry-&gt;next
op_ne
l_int|NULL
op_logical_and
id|entry-&gt;next
op_ne
id|obj_req
)paren
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;next
op_eq
id|obj_req
)paren
id|entry-&gt;next
op_assign
id|entry-&gt;next-&gt;next
suffix:semicolon
)brace
id|free
c_func
(paren
id|obj_req
)paren
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
DECL|function|fill_active_slot
r_static
r_int
id|fill_active_slot
c_func
(paren
r_struct
id|walker
op_star
id|walker
)paren
(brace
r_struct
id|object_request
op_star
id|obj_req
suffix:semicolon
r_for
c_loop
(paren
id|obj_req
op_assign
id|object_queue_head
suffix:semicolon
id|obj_req
suffix:semicolon
id|obj_req
op_assign
id|obj_req-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|obj_req-&gt;state
op_eq
id|WAITING
)paren
(brace
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|obj_req-&gt;sha1
)paren
)paren
id|obj_req-&gt;state
op_assign
id|COMPLETE
suffix:semicolon
r_else
(brace
id|start_object_request
c_func
(paren
id|walker
comma
id|obj_req
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|prefetch
r_static
r_void
id|prefetch
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|object_request
op_star
id|newreq
suffix:semicolon
r_struct
id|object_request
op_star
id|tail
suffix:semicolon
r_struct
id|walker_data
op_star
id|data
op_assign
id|walker-&gt;data
suffix:semicolon
id|newreq
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|newreq
)paren
)paren
suffix:semicolon
id|newreq-&gt;walker
op_assign
id|walker
suffix:semicolon
id|hashcpy
c_func
(paren
id|newreq-&gt;sha1
comma
id|sha1
)paren
suffix:semicolon
id|newreq-&gt;repo
op_assign
id|data-&gt;alt
suffix:semicolon
id|newreq-&gt;state
op_assign
id|WAITING
suffix:semicolon
id|newreq-&gt;req
op_assign
l_int|NULL
suffix:semicolon
id|newreq-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|http_is_verbose
op_assign
id|walker-&gt;get_verbosely
suffix:semicolon
r_if
c_cond
(paren
id|object_queue_head
op_eq
l_int|NULL
)paren
(brace
id|object_queue_head
op_assign
id|newreq
suffix:semicolon
)brace
r_else
(brace
id|tail
op_assign
id|object_queue_head
suffix:semicolon
r_while
c_loop
(paren
id|tail-&gt;next
op_ne
l_int|NULL
)paren
id|tail
op_assign
id|tail-&gt;next
suffix:semicolon
id|tail-&gt;next
op_assign
id|newreq
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
id|fill_active_slots
c_func
(paren
)paren
suffix:semicolon
id|step_active_slots
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|process_alternates_response
r_static
r_void
id|process_alternates_response
c_func
(paren
r_void
op_star
id|callback_data
)paren
(brace
r_struct
id|alternates_request
op_star
id|alt_req
op_assign
(paren
r_struct
id|alternates_request
op_star
)paren
id|callback_data
suffix:semicolon
r_struct
id|walker
op_star
id|walker
op_assign
id|alt_req-&gt;walker
suffix:semicolon
r_struct
id|walker_data
op_star
id|cdata
op_assign
id|walker-&gt;data
suffix:semicolon
r_struct
id|active_request_slot
op_star
id|slot
op_assign
id|alt_req-&gt;slot
suffix:semicolon
r_struct
id|alt_base
op_star
id|tail
op_assign
id|cdata-&gt;alt
suffix:semicolon
r_const
r_char
op_star
id|base
op_assign
id|alt_req-&gt;base
suffix:semicolon
r_static
r_const
r_char
id|null_byte
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|alt_req-&gt;http_specific
)paren
(brace
r_if
c_cond
(paren
id|slot-&gt;curl_result
op_ne
id|CURLE_OK
op_logical_or
op_logical_neg
id|alt_req-&gt;buffer-&gt;len
)paren
(brace
multiline_comment|/* Try reusing the slot to get non-http alternates */
id|alt_req-&gt;http_specific
op_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|alt_req-&gt;url
comma
l_string|&quot;%s/objects/info/alternates&quot;
comma
id|base
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_URL
comma
id|alt_req-&gt;url
)paren
suffix:semicolon
id|active_requests
op_increment
suffix:semicolon
id|slot-&gt;in_use
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;finished
op_ne
l_int|NULL
)paren
(paren
op_star
id|slot-&gt;finished
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start_active_slot
c_func
(paren
id|slot
)paren
)paren
(brace
id|cdata-&gt;got_alternates
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;in_use
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;finished
op_ne
l_int|NULL
)paren
(paren
op_star
id|slot-&gt;finished
)paren
op_assign
l_int|1
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|slot-&gt;curl_result
op_ne
id|CURLE_OK
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|missing_target
c_func
(paren
id|slot
)paren
)paren
(brace
id|cdata-&gt;got_alternates
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|fwrite_buffer
c_func
(paren
op_amp
id|null_byte
comma
l_int|1
comma
l_int|1
comma
id|alt_req-&gt;buffer
)paren
suffix:semicolon
id|alt_req-&gt;buffer-&gt;len
op_decrement
suffix:semicolon
id|data
op_assign
id|alt_req-&gt;buffer-&gt;buf
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|alt_req-&gt;buffer-&gt;len
)paren
(brace
r_int
id|posn
op_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
id|posn
OL
id|alt_req-&gt;buffer-&gt;len
op_logical_and
id|data
(braket
id|posn
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|posn
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
id|posn
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_int
id|okay
op_assign
l_int|0
suffix:semicolon
r_int
id|serverlen
op_assign
l_int|0
suffix:semicolon
r_struct
id|alt_base
op_star
id|newalt
suffix:semicolon
r_char
op_star
id|target
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
id|i
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * This counts&n;&t;&t;&t;&t; * http://git.host/pub/scm/linux.git/&n;&t;&t;&t;&t; * -----------here^&n;&t;&t;&t;&t; * so memcpy(dst, base, serverlen) will&n;&t;&t;&t;&t; * copy up to &quot;...git.host&quot;.&n;&t;&t;&t;&t; */
r_const
r_char
op_star
id|colon_ss
op_assign
id|strstr
c_func
(paren
id|base
comma
l_string|&quot;://&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|colon_ss
)paren
(brace
id|serverlen
op_assign
(paren
id|strchr
c_func
(paren
id|colon_ss
op_plus
l_int|3
comma
l_char|&squot;/&squot;
)paren
id|base
)paren
suffix:semicolon
id|okay
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|data
op_plus
id|i
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Relative URL; chop the corresponding&n;&t;&t;&t;&t; * number of subpath from base (and ../&n;&t;&t;&t;&t; * from data), and concatenate the result.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * The code first drops ../ from data, and&n;&t;&t;&t;&t; * then drops one ../ from data and one path&n;&t;&t;&t;&t; * from base.  IOW, one extra ../ is dropped&n;&t;&t;&t;&t; * from data than path is dropped from base.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * This is not wrong.  The alternate in&n;&t;&t;&t;&t; *     http://git.host/pub/scm/linux.git/&n;&t;&t;&t;&t; * to borrow from&n;&t;&t;&t;&t; *     http://git.host/pub/scm/linus.git/&n;&t;&t;&t;&t; * is ../../linus.git/objects/.  You need&n;&t;&t;&t;&t; * two ../../ to borrow from your direct&n;&t;&t;&t;&t; * neighbour.&n;&t;&t;&t;&t; */
id|i
op_add_assign
l_int|3
suffix:semicolon
id|serverlen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_plus
l_int|2
OL
id|posn
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|data
op_plus
id|i
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
)paren
(brace
r_do
(brace
id|serverlen
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|serverlen
op_logical_and
id|base
(braket
id|serverlen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|i
op_add_assign
l_int|3
suffix:semicolon
)brace
multiline_comment|/* If the server got removed, give up. */
id|okay
op_assign
id|strchr
c_func
(paren
id|base
comma
l_char|&squot;:&squot;
)paren
id|base
op_plus
l_int|3
OL
id|serverlen
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|alt_req-&gt;http_specific
)paren
(brace
r_char
op_star
id|colon
op_assign
id|strchr
c_func
(paren
id|data
op_plus
id|i
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
id|data
op_plus
id|i
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|colon
op_logical_and
id|slash
op_logical_and
id|colon
OL
id|data
op_plus
id|posn
op_logical_and
id|slash
OL
id|data
op_plus
id|posn
op_logical_and
id|colon
OL
id|slash
)paren
(brace
id|okay
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* skip &quot;objects&bslash;n&quot; at end */
r_if
c_cond
(paren
id|okay
)paren
(brace
id|target
op_assign
id|xmalloc
c_func
(paren
id|serverlen
op_plus
id|posn
id|i
l_int|6
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|target
comma
id|base
comma
id|serverlen
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|target
op_plus
id|serverlen
comma
id|data
op_plus
id|i
comma
id|posn
id|i
l_int|7
)paren
suffix:semicolon
id|target
(braket
id|serverlen
op_plus
id|posn
id|i
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Also look at %s&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
id|newalt
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|newalt
)paren
)paren
suffix:semicolon
id|newalt-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|newalt-&gt;base
op_assign
id|target
suffix:semicolon
id|newalt-&gt;got_indices
op_assign
l_int|0
suffix:semicolon
id|newalt-&gt;packs
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|tail-&gt;next
op_ne
l_int|NULL
)paren
id|tail
op_assign
id|tail-&gt;next
suffix:semicolon
id|tail-&gt;next
op_assign
id|newalt
suffix:semicolon
)brace
)brace
id|i
op_assign
id|posn
op_plus
l_int|1
suffix:semicolon
)brace
id|cdata-&gt;got_alternates
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|fetch_alternates
r_static
r_void
id|fetch_alternates
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_const
r_char
op_star
id|base
)paren
(brace
r_struct
id|strbuf
id|buffer
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|url
suffix:semicolon
r_struct
id|active_request_slot
op_star
id|slot
suffix:semicolon
r_struct
id|alternates_request
id|alt_req
suffix:semicolon
r_struct
id|walker_data
op_star
id|cdata
op_assign
id|walker-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; * If another request has already started fetching alternates,&n;&t; * wait for them to arrive and return to processing this request&squot;s&n;&t; * curl message&n;&t; */
macro_line|#ifdef USE_CURL_MULTI
r_while
c_loop
(paren
id|cdata-&gt;got_alternates
op_eq
l_int|0
)paren
(brace
id|step_active_slots
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Nothing to do if they&squot;ve already been fetched */
r_if
c_cond
(paren
id|cdata-&gt;got_alternates
op_eq
l_int|1
)paren
r_return
suffix:semicolon
multiline_comment|/* Start the fetch */
id|cdata-&gt;got_alternates
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting alternates list for %s&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
id|url
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|base
)paren
op_plus
l_int|31
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|url
comma
l_string|&quot;%s/objects/info/http-alternates&quot;
comma
id|base
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use a callback to process the result, since another request&n;&t; * may fail and need to have alternates loaded before continuing&n;&t; */
id|slot
op_assign
id|get_active_slot
c_func
(paren
)paren
suffix:semicolon
id|slot-&gt;callback_func
op_assign
id|process_alternates_response
suffix:semicolon
id|alt_req.walker
op_assign
id|walker
suffix:semicolon
id|slot-&gt;callback_data
op_assign
op_amp
id|alt_req
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_FILE
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_WRITEFUNCTION
comma
id|fwrite_buffer
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_URL
comma
id|url
)paren
suffix:semicolon
id|alt_req.base
op_assign
id|base
suffix:semicolon
id|alt_req.url
op_assign
id|url
suffix:semicolon
id|alt_req.buffer
op_assign
op_amp
id|buffer
suffix:semicolon
id|alt_req.http_specific
op_assign
l_int|1
suffix:semicolon
id|alt_req.slot
op_assign
id|slot
suffix:semicolon
r_if
c_cond
(paren
id|start_active_slot
c_func
(paren
id|slot
)paren
)paren
id|run_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_else
id|cdata-&gt;got_alternates
op_assign
l_int|1
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
id|free
c_func
(paren
id|url
)paren
suffix:semicolon
)brace
DECL|function|fetch_indices
r_static
r_int
id|fetch_indices
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_struct
id|alt_base
op_star
id|repo
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|repo-&gt;got_indices
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;get_verbosely
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting pack list for %s&bslash;n&quot;
comma
id|repo-&gt;base
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|http_get_info_packs
c_func
(paren
id|repo-&gt;base
comma
op_amp
id|repo-&gt;packs
)paren
)paren
(brace
r_case
id|HTTP_OK
suffix:colon
r_case
id|HTTP_MISSING_TARGET
suffix:colon
id|repo-&gt;got_indices
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|repo-&gt;got_indices
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fetch_pack
r_static
r_int
id|fetch_pack
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_struct
id|alt_base
op_star
id|repo
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|packed_git
op_star
id|target
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|slot_results
id|results
suffix:semicolon
r_struct
id|http_pack_request
op_star
id|preq
suffix:semicolon
r_if
c_cond
(paren
id|fetch_indices
c_func
(paren
id|walker
comma
id|repo
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|target
op_assign
id|find_sha1_pack
c_func
(paren
id|sha1
comma
id|repo-&gt;packs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|walker-&gt;get_verbosely
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting pack %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; which contains %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
id|preq
op_assign
id|new_http_pack_request
c_func
(paren
id|target
comma
id|repo-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|preq
op_eq
l_int|NULL
)paren
r_goto
m_abort
suffix:semicolon
id|preq-&gt;lst
op_assign
op_amp
id|repo-&gt;packs
suffix:semicolon
id|preq-&gt;slot-&gt;results
op_assign
op_amp
id|results
suffix:semicolon
r_if
c_cond
(paren
id|start_active_slot
c_func
(paren
id|preq-&gt;slot
)paren
)paren
(brace
id|run_active_slot
c_func
(paren
id|preq-&gt;slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|results.curl_result
op_ne
id|CURLE_OK
)paren
(brace
id|error
c_func
(paren
l_string|&quot;Unable to get pack file %s&bslash;n%s&quot;
comma
id|preq-&gt;url
comma
id|curl_errorstr
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
)brace
r_else
(brace
id|error
c_func
(paren
l_string|&quot;Unable to start request&quot;
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
id|ret
op_assign
id|finish_http_pack_request
c_func
(paren
id|preq
)paren
suffix:semicolon
id|release_http_pack_request
c_func
(paren
id|preq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
m_abort
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|abort_object_request
r_static
r_void
id|abort_object_request
c_func
(paren
r_struct
id|object_request
op_star
id|obj_req
)paren
(brace
id|release_object_request
c_func
(paren
id|obj_req
)paren
suffix:semicolon
)brace
DECL|function|fetch_object
r_static
r_int
id|fetch_object
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_struct
id|alt_base
op_star
id|repo
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|object_request
op_star
id|obj_req
op_assign
id|object_queue_head
suffix:semicolon
r_struct
id|http_object_request
op_star
id|req
suffix:semicolon
r_while
c_loop
(paren
id|obj_req
op_ne
l_int|NULL
op_logical_and
id|hashcmp
c_func
(paren
id|obj_req-&gt;sha1
comma
id|sha1
)paren
)paren
id|obj_req
op_assign
id|obj_req-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|obj_req
op_eq
l_int|NULL
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t find request for %s in the queue&quot;
comma
id|hex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_sha1_file
c_func
(paren
id|obj_req-&gt;sha1
)paren
)paren
(brace
r_if
c_cond
(paren
id|obj_req-&gt;req
op_ne
l_int|NULL
)paren
id|abort_http_object_request
c_func
(paren
id|obj_req-&gt;req
)paren
suffix:semicolon
id|abort_object_request
c_func
(paren
id|obj_req
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
r_while
c_loop
(paren
id|obj_req-&gt;state
op_eq
id|WAITING
)paren
id|step_active_slots
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|start_object_request
c_func
(paren
id|walker
comma
id|obj_req
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * obj_req-&gt;req might change when fetching alternates in the callback&n;&t; * process_object_response; therefore, the &quot;shortcut&quot; variable, req,&n;&t; * is used only after we&squot;re done with slots.&n;&t; */
r_while
c_loop
(paren
id|obj_req-&gt;state
op_eq
id|ACTIVE
)paren
id|run_active_slot
c_func
(paren
id|obj_req-&gt;req-&gt;slot
)paren
suffix:semicolon
id|req
op_assign
id|obj_req-&gt;req
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;localfile
op_ne
l_int|1
)paren
(brace
id|close
c_func
(paren
id|req-&gt;localfile
)paren
suffix:semicolon
id|req-&gt;localfile
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj_req-&gt;state
op_eq
id|ABORTED
)paren
(brace
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Request for %s aborted&quot;
comma
id|hex
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|req-&gt;curl_result
op_ne
id|CURLE_OK
op_logical_and
id|req-&gt;http_code
op_ne
l_int|416
)paren
(brace
r_if
c_cond
(paren
id|missing_target
c_func
(paren
id|req
)paren
)paren
id|ret
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Be silent, it is probably in a pack. */
r_else
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;%s (curl_result = %d, http_code = %ld, sha1 = %s)&quot;
comma
id|req-&gt;errorstr
comma
id|req-&gt;curl_result
comma
id|req-&gt;http_code
comma
id|hex
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|req-&gt;zret
op_ne
id|Z_STREAM_END
)paren
(brace
id|walker-&gt;corrupt_object_found
op_increment
suffix:semicolon
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;File %s (%s) corrupt&quot;
comma
id|hex
comma
id|req-&gt;url
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hashcmp
c_func
(paren
id|obj_req-&gt;sha1
comma
id|req-&gt;real_sha1
)paren
)paren
(brace
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;File %s has bad hash&quot;
comma
id|hex
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|req-&gt;rename
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;unable to write sha1 filename %s&quot;
comma
id|req-&gt;filename
)paren
suffix:semicolon
)brace
id|release_http_object_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|release_object_request
c_func
(paren
id|obj_req
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fetch
r_static
r_int
id|fetch
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|walker_data
op_star
id|data
op_assign
id|walker-&gt;data
suffix:semicolon
r_struct
id|alt_base
op_star
id|altbase
op_assign
id|data-&gt;alt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fetch_object
c_func
(paren
id|walker
comma
id|altbase
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|altbase
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fetch_pack
c_func
(paren
id|walker
comma
id|altbase
comma
id|sha1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fetch_alternates
c_func
(paren
id|walker
comma
id|data-&gt;alt-&gt;base
)paren
suffix:semicolon
id|altbase
op_assign
id|altbase-&gt;next
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;Unable to find %s under %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|data-&gt;alt-&gt;base
)paren
suffix:semicolon
)brace
DECL|function|fetch_ref
r_static
r_int
id|fetch_ref
c_func
(paren
r_struct
id|walker
op_star
id|walker
comma
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_struct
id|walker_data
op_star
id|data
op_assign
id|walker-&gt;data
suffix:semicolon
r_return
id|http_fetch_ref
c_func
(paren
id|data-&gt;alt-&gt;base
comma
id|ref
)paren
suffix:semicolon
)brace
DECL|function|cleanup
r_static
r_void
id|cleanup
c_func
(paren
r_struct
id|walker
op_star
id|walker
)paren
(brace
r_struct
id|walker_data
op_star
id|data
op_assign
id|walker-&gt;data
suffix:semicolon
r_struct
id|alt_base
op_star
id|alt
comma
op_star
id|alt_next
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
id|alt
op_assign
id|data-&gt;alt
suffix:semicolon
r_while
c_loop
(paren
id|alt
)paren
(brace
id|alt_next
op_assign
id|alt-&gt;next
suffix:semicolon
id|free
c_func
(paren
id|alt-&gt;base
)paren
suffix:semicolon
id|free
c_func
(paren
id|alt
)paren
suffix:semicolon
id|alt
op_assign
id|alt_next
suffix:semicolon
)brace
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
id|walker-&gt;data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|get_http_walker
r_struct
id|walker
op_star
id|get_http_walker
c_func
(paren
r_const
r_char
op_star
id|url
)paren
(brace
r_char
op_star
id|s
suffix:semicolon
r_struct
id|walker_data
op_star
id|data
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|walker_data
)paren
)paren
suffix:semicolon
r_struct
id|walker
op_star
id|walker
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|walker
)paren
)paren
suffix:semicolon
id|data-&gt;alt
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data-&gt;alt
)paren
)paren
suffix:semicolon
id|data-&gt;alt-&gt;base
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|url
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|data-&gt;alt-&gt;base
comma
id|url
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|data-&gt;alt-&gt;base
op_plus
id|strlen
c_func
(paren
id|data-&gt;alt-&gt;base
)paren
l_int|1
suffix:semicolon
op_star
id|s
op_eq
l_char|&squot;/&squot;
suffix:semicolon
op_decrement
id|s
)paren
op_star
id|s
op_assign
l_int|0
suffix:semicolon
id|data-&gt;alt-&gt;got_indices
op_assign
l_int|0
suffix:semicolon
id|data-&gt;alt-&gt;packs
op_assign
l_int|NULL
suffix:semicolon
id|data-&gt;alt-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|data-&gt;got_alternates
op_assign
l_int|1
suffix:semicolon
id|walker-&gt;corrupt_object_found
op_assign
l_int|0
suffix:semicolon
id|walker-&gt;fetch
op_assign
id|fetch
suffix:semicolon
id|walker-&gt;fetch_ref
op_assign
id|fetch_ref
suffix:semicolon
id|walker-&gt;prefetch
op_assign
id|prefetch
suffix:semicolon
id|walker-&gt;cleanup
op_assign
id|cleanup
suffix:semicolon
id|walker-&gt;data
op_assign
id|data
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
id|add_fill_function
c_func
(paren
id|walker
comma
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|fill_active_slot
)paren
suffix:semicolon
macro_line|#endif
r_return
id|walker
suffix:semicolon
)brace
eof
