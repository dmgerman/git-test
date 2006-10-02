macro_line|#include &quot;http.h&quot;
DECL|variable|data_received
r_int
id|data_received
suffix:semicolon
DECL|variable|active_requests
r_int
id|active_requests
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
DECL|variable|max_requests
r_int
id|max_requests
op_assign
l_int|1
suffix:semicolon
DECL|variable|curlm
id|CURLM
op_star
id|curlm
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NO_CURL_EASY_DUPHANDLE
DECL|variable|curl_default
id|CURL
op_star
id|curl_default
suffix:semicolon
macro_line|#endif
DECL|variable|curl_errorstr
r_char
id|curl_errorstr
(braket
id|CURL_ERROR_SIZE
)braket
suffix:semicolon
DECL|variable|curl_ssl_verify
r_int
id|curl_ssl_verify
op_assign
l_int|1
suffix:semicolon
DECL|variable|ssl_cert
r_char
op_star
id|ssl_cert
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070902
DECL|variable|ssl_key
r_char
op_star
id|ssl_key
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070908
DECL|variable|ssl_capath
r_char
op_star
id|ssl_capath
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
DECL|variable|ssl_cainfo
r_char
op_star
id|ssl_cainfo
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|curl_low_speed_limit
r_int
id|curl_low_speed_limit
op_assign
l_int|1
suffix:semicolon
DECL|variable|curl_low_speed_time
r_int
id|curl_low_speed_time
op_assign
l_int|1
suffix:semicolon
DECL|variable|curl_ftp_no_epsv
r_int
id|curl_ftp_no_epsv
op_assign
l_int|0
suffix:semicolon
DECL|variable|pragma_header
r_struct
id|curl_slist
op_star
id|pragma_header
suffix:semicolon
DECL|variable|active_queue_head
r_struct
id|active_request_slot
op_star
id|active_queue_head
op_assign
l_int|NULL
suffix:semicolon
DECL|function|fread_buffer
r_int
id|fread_buffer
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|eltsize
comma
r_int
id|nmemb
comma
r_struct
id|buffer
op_star
id|buffer
)paren
(brace
r_int
id|size
op_assign
id|eltsize
op_star
id|nmemb
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|buffer-&gt;size
id|buffer-&gt;posn
)paren
id|size
op_assign
id|buffer-&gt;size
id|buffer-&gt;posn
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
id|buffer-&gt;buffer
op_plus
id|buffer-&gt;posn
comma
id|size
)paren
suffix:semicolon
id|buffer-&gt;posn
op_add_assign
id|size
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|fwrite_buffer
r_int
id|fwrite_buffer
c_func
(paren
r_const
r_void
op_star
id|ptr
comma
r_int
id|eltsize
comma
r_int
id|nmemb
comma
r_struct
id|buffer
op_star
id|buffer
)paren
(brace
r_int
id|size
op_assign
id|eltsize
op_star
id|nmemb
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|buffer-&gt;size
id|buffer-&gt;posn
)paren
(brace
id|buffer-&gt;size
op_assign
id|buffer-&gt;size
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;size
OL
id|buffer-&gt;posn
op_plus
id|size
)paren
id|buffer-&gt;size
op_assign
id|buffer-&gt;posn
op_plus
id|size
suffix:semicolon
id|buffer-&gt;buffer
op_assign
id|xrealloc
c_func
(paren
id|buffer-&gt;buffer
comma
id|buffer-&gt;size
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|buffer-&gt;buffer
op_plus
id|buffer-&gt;posn
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
id|buffer-&gt;posn
op_add_assign
id|size
suffix:semicolon
id|data_received
op_increment
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|fwrite_null
r_int
id|fwrite_null
c_func
(paren
r_const
r_void
op_star
id|ptr
comma
r_int
id|eltsize
comma
r_int
id|nmemb
comma
r_struct
id|buffer
op_star
id|buffer
)paren
(brace
id|data_received
op_increment
suffix:semicolon
r_return
id|eltsize
op_star
id|nmemb
suffix:semicolon
)brace
r_static
r_void
id|finish_active_slot
c_func
(paren
r_struct
id|active_request_slot
op_star
id|slot
)paren
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
DECL|function|process_curl_messages
r_static
r_void
id|process_curl_messages
c_func
(paren
r_void
)paren
(brace
r_int
id|num_messages
suffix:semicolon
r_struct
id|active_request_slot
op_star
id|slot
suffix:semicolon
id|CURLMsg
op_star
id|curl_message
op_assign
id|curl_multi_info_read
c_func
(paren
id|curlm
comma
op_amp
id|num_messages
)paren
suffix:semicolon
r_while
c_loop
(paren
id|curl_message
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|curl_message-&gt;msg
op_eq
id|CURLMSG_DONE
)paren
(brace
r_int
id|curl_result
op_assign
id|curl_message-&gt;data.result
suffix:semicolon
id|slot
op_assign
id|active_queue_head
suffix:semicolon
r_while
c_loop
(paren
id|slot
op_ne
l_int|NULL
op_logical_and
id|slot-&gt;curl
op_ne
id|curl_message-&gt;easy_handle
)paren
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_ne
l_int|NULL
)paren
(brace
id|curl_multi_remove_handle
c_func
(paren
id|curlm
comma
id|slot-&gt;curl
)paren
suffix:semicolon
id|slot-&gt;curl_result
op_assign
id|curl_result
suffix:semicolon
id|finish_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Received DONE message for unknown request!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unknown CURL message received: %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|curl_message-&gt;msg
)paren
suffix:semicolon
)brace
id|curl_message
op_assign
id|curl_multi_info_read
c_func
(paren
id|curlm
comma
op_amp
id|num_messages
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|http_options
r_static
r_int
id|http_options
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.sslverify&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|curl_ssl_verify
op_eq
l_int|1
)paren
(brace
id|curl_ssl_verify
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
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
l_string|&quot;http.sslcert&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|ssl_cert
op_eq
l_int|NULL
)paren
(brace
id|ssl_cert
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|value
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ssl_cert
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070902
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.sslkey&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|ssl_key
op_eq
l_int|NULL
)paren
(brace
id|ssl_key
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|value
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ssl_key
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070908
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.sslcapath&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|ssl_capath
op_eq
l_int|NULL
)paren
(brace
id|ssl_capath
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|value
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ssl_capath
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.sslcainfo&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|ssl_cainfo
op_eq
l_int|NULL
)paren
(brace
id|ssl_cainfo
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|value
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ssl_cainfo
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI&t;
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.maxrequests&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|max_requests
op_eq
l_int|1
)paren
id|max_requests
op_assign
id|git_config_int
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.lowspeedlimit&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|curl_low_speed_limit
op_eq
l_int|1
)paren
id|curl_low_speed_limit
op_assign
(paren
r_int
)paren
id|git_config_int
c_func
(paren
id|var
comma
id|value
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
l_string|&quot;http.lowspeedtime&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|curl_low_speed_time
op_eq
l_int|1
)paren
id|curl_low_speed_time
op_assign
(paren
r_int
)paren
id|git_config_int
c_func
(paren
id|var
comma
id|value
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
l_string|&quot;http.noepsv&quot;
comma
id|var
)paren
)paren
(brace
id|curl_ftp_no_epsv
op_assign
id|git_config_bool
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fall back on the default ones */
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|get_curl_handle
r_static
id|CURL
op_star
id|get_curl_handle
c_func
(paren
r_void
)paren
(brace
id|CURL
op_star
id|result
op_assign
id|curl_easy_init
c_func
(paren
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_SSL_VERIFYPEER
comma
id|curl_ssl_verify
)paren
suffix:semicolon
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070907
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_NETRC
comma
id|CURL_NETRC_OPTIONAL
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ssl_cert
op_ne
l_int|NULL
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_SSLCERT
comma
id|ssl_cert
)paren
suffix:semicolon
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070902
r_if
c_cond
(paren
id|ssl_key
op_ne
l_int|NULL
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_SSLKEY
comma
id|ssl_key
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070908
r_if
c_cond
(paren
id|ssl_capath
op_ne
l_int|NULL
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_CAPATH
comma
id|ssl_capath
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ssl_cainfo
op_ne
l_int|NULL
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_CAINFO
comma
id|ssl_cainfo
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_FAILONERROR
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_low_speed_limit
OG
l_int|0
op_logical_and
id|curl_low_speed_time
OG
l_int|0
)paren
(brace
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_LOW_SPEED_LIMIT
comma
id|curl_low_speed_limit
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_LOW_SPEED_TIME
comma
id|curl_low_speed_time
)paren
suffix:semicolon
)brace
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_FOLLOWLOCATION
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_CURL_VERBOSE&quot;
)paren
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_VERBOSE
comma
l_int|1
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_USERAGENT
comma
id|GIT_USER_AGENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_ftp_no_epsv
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_FTP_USE_EPSV
comma
l_int|0
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|http_init
r_void
id|http_init
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|low_speed_limit
suffix:semicolon
r_char
op_star
id|low_speed_time
suffix:semicolon
id|curl_global_init
c_func
(paren
id|CURL_GLOBAL_ALL
)paren
suffix:semicolon
id|pragma_header
op_assign
id|curl_slist_append
c_func
(paren
id|pragma_header
comma
l_string|&quot;Pragma: no-cache&quot;
)paren
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
(brace
r_char
op_star
id|http_max_requests
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_HTTP_MAX_REQUESTS&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|http_max_requests
op_ne
l_int|NULL
)paren
id|max_requests
op_assign
id|atoi
c_func
(paren
id|http_max_requests
)paren
suffix:semicolon
)brace
id|curlm
op_assign
id|curl_multi_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curlm
op_eq
l_int|NULL
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Error creating curl multi handle.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_SSL_NO_VERIFY&quot;
)paren
)paren
id|curl_ssl_verify
op_assign
l_int|0
suffix:semicolon
id|ssl_cert
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSL_CERT&quot;
)paren
suffix:semicolon
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070902
id|ssl_key
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSL_KEY&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070908
id|ssl_capath
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSL_CAPATH&quot;
)paren
suffix:semicolon
macro_line|#endif
id|ssl_cainfo
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_SSL_CAINFO&quot;
)paren
suffix:semicolon
id|low_speed_limit
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_HTTP_LOW_SPEED_LIMIT&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|low_speed_limit
op_ne
l_int|NULL
)paren
id|curl_low_speed_limit
op_assign
id|strtol
c_func
(paren
id|low_speed_limit
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|low_speed_time
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_HTTP_LOW_SPEED_TIME&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|low_speed_time
op_ne
l_int|NULL
)paren
id|curl_low_speed_time
op_assign
id|strtol
c_func
(paren
id|low_speed_time
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|http_options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curl_ssl_verify
op_eq
l_int|1
)paren
id|curl_ssl_verify
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
r_if
c_cond
(paren
id|max_requests
OL
l_int|1
)paren
id|max_requests
op_assign
id|DEFAULT_MAX_REQUESTS
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|getenv
c_func
(paren
l_string|&quot;GIT_CURL_FTP_NO_EPSV&quot;
)paren
)paren
id|curl_ftp_no_epsv
op_assign
l_int|1
suffix:semicolon
macro_line|#ifndef NO_CURL_EASY_DUPHANDLE
id|curl_default
op_assign
id|get_curl_handle
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|http_cleanup
r_void
id|http_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|active_request_slot
op_star
id|slot
op_assign
id|active_queue_head
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
r_char
op_star
id|wait_url
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|slot
op_ne
l_int|NULL
)paren
(brace
macro_line|#ifdef USE_CURL_MULTI
r_if
c_cond
(paren
id|slot-&gt;in_use
)paren
(brace
id|curl_easy_getinfo
c_func
(paren
id|slot-&gt;curl
comma
id|CURLINFO_EFFECTIVE_URL
comma
op_amp
id|wait_url
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Waiting for %s&bslash;n&quot;
comma
id|wait_url
)paren
suffix:semicolon
id|run_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|slot-&gt;curl
op_ne
l_int|NULL
)paren
id|curl_easy_cleanup
c_func
(paren
id|slot-&gt;curl
)paren
suffix:semicolon
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
)brace
macro_line|#ifndef NO_CURL_EASY_DUPHANDLE
id|curl_easy_cleanup
c_func
(paren
id|curl_default
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USE_CURL_MULTI
id|curl_multi_cleanup
c_func
(paren
id|curlm
)paren
suffix:semicolon
macro_line|#endif
id|curl_global_cleanup
c_func
(paren
)paren
suffix:semicolon
id|curl_slist_free_all
c_func
(paren
id|pragma_header
)paren
suffix:semicolon
)brace
DECL|function|get_active_slot
r_struct
id|active_request_slot
op_star
id|get_active_slot
c_func
(paren
r_void
)paren
(brace
r_struct
id|active_request_slot
op_star
id|slot
op_assign
id|active_queue_head
suffix:semicolon
r_struct
id|active_request_slot
op_star
id|newslot
suffix:semicolon
macro_line|#ifdef USE_CURL_MULTI
r_int
id|num_transfers
suffix:semicolon
multiline_comment|/* Wait for a slot to open up if the queue is full */
r_while
c_loop
(paren
id|active_requests
op_ge
id|max_requests
)paren
(brace
id|curl_multi_perform
c_func
(paren
id|curlm
comma
op_amp
id|num_transfers
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_transfers
OL
id|active_requests
)paren
(brace
id|process_curl_messages
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_while
c_loop
(paren
id|slot
op_ne
l_int|NULL
op_logical_and
id|slot-&gt;in_use
)paren
(brace
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
(brace
id|newslot
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|newslot
)paren
)paren
suffix:semicolon
id|newslot-&gt;curl
op_assign
l_int|NULL
suffix:semicolon
id|newslot-&gt;in_use
op_assign
l_int|0
suffix:semicolon
id|newslot-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|slot
op_assign
id|active_queue_head
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
(brace
id|active_queue_head
op_assign
id|newslot
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|slot-&gt;next
op_ne
l_int|NULL
)paren
(brace
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
)brace
id|slot-&gt;next
op_assign
id|newslot
suffix:semicolon
)brace
id|slot
op_assign
id|newslot
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot-&gt;curl
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef NO_CURL_EASY_DUPHANDLE
id|slot-&gt;curl
op_assign
id|get_curl_handle
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|slot-&gt;curl
op_assign
id|curl_easy_duphandle
c_func
(paren
id|curl_default
)paren
suffix:semicolon
macro_line|#endif
)brace
id|active_requests
op_increment
suffix:semicolon
id|slot-&gt;in_use
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;local
op_assign
l_int|NULL
suffix:semicolon
id|slot-&gt;results
op_assign
l_int|NULL
suffix:semicolon
id|slot-&gt;finished
op_assign
l_int|NULL
suffix:semicolon
id|slot-&gt;callback_data
op_assign
l_int|NULL
suffix:semicolon
id|slot-&gt;callback_func
op_assign
l_int|NULL
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_HTTPHEADER
comma
l_int|NULL
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_HTTPHEADER
comma
id|pragma_header
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_ERRORBUFFER
comma
id|curl_errorstr
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_CUSTOMREQUEST
comma
l_int|NULL
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_READFUNCTION
comma
l_int|NULL
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_WRITEFUNCTION
comma
l_int|NULL
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_UPLOAD
comma
l_int|0
)paren
suffix:semicolon
id|curl_easy_setopt
c_func
(paren
id|slot-&gt;curl
comma
id|CURLOPT_HTTPGET
comma
l_int|1
)paren
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
DECL|function|start_active_slot
r_int
id|start_active_slot
c_func
(paren
r_struct
id|active_request_slot
op_star
id|slot
)paren
(brace
macro_line|#ifdef USE_CURL_MULTI
id|CURLMcode
id|curlm_result
op_assign
id|curl_multi_add_handle
c_func
(paren
id|curlm
comma
id|slot-&gt;curl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curlm_result
op_ne
id|CURLM_OK
op_logical_and
id|curlm_result
op_ne
id|CURLM_CALL_MULTI_PERFORM
)paren
(brace
id|active_requests
op_decrement
suffix:semicolon
id|slot-&gt;in_use
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
DECL|function|step_active_slots
r_void
id|step_active_slots
c_func
(paren
r_void
)paren
(brace
r_int
id|num_transfers
suffix:semicolon
id|CURLMcode
id|curlm_result
suffix:semicolon
r_do
(brace
id|curlm_result
op_assign
id|curl_multi_perform
c_func
(paren
id|curlm
comma
op_amp
id|num_transfers
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|curlm_result
op_eq
id|CURLM_CALL_MULTI_PERFORM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_transfers
OL
id|active_requests
)paren
(brace
id|process_curl_messages
c_func
(paren
)paren
suffix:semicolon
id|fill_active_slots
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|run_active_slot
r_void
id|run_active_slot
c_func
(paren
r_struct
id|active_request_slot
op_star
id|slot
)paren
(brace
macro_line|#ifdef USE_CURL_MULTI
r_int
id|last_pos
op_assign
l_int|0
suffix:semicolon
r_int
id|current_pos
suffix:semicolon
id|fd_set
id|readfds
suffix:semicolon
id|fd_set
id|writefds
suffix:semicolon
id|fd_set
id|excfds
suffix:semicolon
r_int
id|max_fd
suffix:semicolon
r_struct
id|timeval
id|select_timeout
suffix:semicolon
r_int
id|finished
op_assign
l_int|0
suffix:semicolon
id|slot-&gt;finished
op_assign
op_amp
id|finished
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|finished
)paren
(brace
id|data_received
op_assign
l_int|0
suffix:semicolon
id|step_active_slots
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data_received
op_logical_and
id|slot-&gt;local
op_ne
l_int|NULL
)paren
(brace
id|current_pos
op_assign
id|ftell
c_func
(paren
id|slot-&gt;local
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_pos
OG
id|last_pos
)paren
id|data_received
op_increment
suffix:semicolon
id|last_pos
op_assign
id|current_pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot-&gt;in_use
op_logical_and
op_logical_neg
id|data_received
)paren
(brace
id|max_fd
op_assign
l_int|0
suffix:semicolon
id|FD_ZERO
c_func
(paren
op_amp
id|readfds
)paren
suffix:semicolon
id|FD_ZERO
c_func
(paren
op_amp
id|writefds
)paren
suffix:semicolon
id|FD_ZERO
c_func
(paren
op_amp
id|excfds
)paren
suffix:semicolon
id|select_timeout.tv_sec
op_assign
l_int|0
suffix:semicolon
id|select_timeout.tv_usec
op_assign
l_int|50000
suffix:semicolon
id|select
c_func
(paren
id|max_fd
comma
op_amp
id|readfds
comma
op_amp
id|writefds
comma
op_amp
id|excfds
comma
op_amp
id|select_timeout
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
r_while
c_loop
(paren
id|slot-&gt;in_use
)paren
(brace
id|slot-&gt;curl_result
op_assign
id|curl_easy_perform
c_func
(paren
id|slot-&gt;curl
)paren
suffix:semicolon
id|finish_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|closedown_active_slot
r_static
r_void
id|closedown_active_slot
c_func
(paren
r_struct
id|active_request_slot
op_star
id|slot
)paren
(brace
id|active_requests
op_decrement
suffix:semicolon
id|slot-&gt;in_use
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|release_active_slot
r_void
id|release_active_slot
c_func
(paren
r_struct
id|active_request_slot
op_star
id|slot
)paren
(brace
id|closedown_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;curl
)paren
(brace
macro_line|#ifdef USE_CURL_MULTI
id|curl_multi_remove_handle
c_func
(paren
id|curlm
comma
id|slot-&gt;curl
)paren
suffix:semicolon
macro_line|#endif
id|curl_easy_cleanup
c_func
(paren
id|slot-&gt;curl
)paren
suffix:semicolon
id|slot-&gt;curl
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
id|fill_active_slots
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|finish_active_slot
r_static
r_void
id|finish_active_slot
c_func
(paren
r_struct
id|active_request_slot
op_star
id|slot
)paren
(brace
id|closedown_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
id|curl_easy_getinfo
c_func
(paren
id|slot-&gt;curl
comma
id|CURLINFO_HTTP_CODE
comma
op_amp
id|slot-&gt;http_code
)paren
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
multiline_comment|/* Store slot results so they can be read after the slot is reused */
r_if
c_cond
(paren
id|slot-&gt;results
op_ne
l_int|NULL
)paren
(brace
id|slot-&gt;results-&gt;curl_result
op_assign
id|slot-&gt;curl_result
suffix:semicolon
id|slot-&gt;results-&gt;http_code
op_assign
id|slot-&gt;http_code
suffix:semicolon
)brace
multiline_comment|/* Run callback if appropriate */
r_if
c_cond
(paren
id|slot-&gt;callback_func
op_ne
l_int|NULL
)paren
(brace
id|slot
op_member_access_from_pointer
id|callback_func
c_func
(paren
id|slot-&gt;callback_data
)paren
suffix:semicolon
)brace
)brace
DECL|function|finish_all_active_slots
r_void
id|finish_all_active_slots
c_func
(paren
r_void
)paren
(brace
r_struct
id|active_request_slot
op_star
id|slot
op_assign
id|active_queue_head
suffix:semicolon
r_while
c_loop
(paren
id|slot
op_ne
l_int|NULL
)paren
r_if
c_cond
(paren
id|slot-&gt;in_use
)paren
(brace
id|run_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
id|slot
op_assign
id|active_queue_head
suffix:semicolon
)brace
r_else
(brace
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
)brace
)brace
eof
