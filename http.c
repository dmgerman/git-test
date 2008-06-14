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
r_static
r_int
id|max_requests
op_assign
l_int|1
suffix:semicolon
DECL|variable|curlm
r_static
id|CURLM
op_star
id|curlm
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NO_CURL_EASY_DUPHANDLE
DECL|variable|curl_default
r_static
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
r_static
r_int
id|curl_ssl_verify
op_assign
l_int|1
suffix:semicolon
DECL|variable|ssl_cert
r_static
r_char
op_star
id|ssl_cert
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070902
DECL|variable|ssl_key
r_static
r_char
op_star
id|ssl_key
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#if LIBCURL_VERSION_NUM &gt;= 0x070908
DECL|variable|ssl_capath
r_static
r_char
op_star
id|ssl_capath
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
DECL|variable|ssl_cainfo
r_static
r_char
op_star
id|ssl_cainfo
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|curl_low_speed_limit
r_static
r_int
id|curl_low_speed_limit
op_assign
l_int|1
suffix:semicolon
DECL|variable|curl_low_speed_time
r_static
r_int
id|curl_low_speed_time
op_assign
l_int|1
suffix:semicolon
DECL|variable|curl_ftp_no_epsv
r_static
r_int
id|curl_ftp_no_epsv
op_assign
l_int|0
suffix:semicolon
DECL|variable|curl_http_proxy
r_static
r_char
op_star
id|curl_http_proxy
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pragma_header
r_static
r_struct
id|curl_slist
op_star
id|pragma_header
suffix:semicolon
DECL|variable|active_queue_head
r_static
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
id|buffer-&gt;buf.len
id|buffer-&gt;posn
)paren
id|size
op_assign
id|buffer-&gt;buf.len
id|buffer-&gt;posn
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|buffer-&gt;buf.buf
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
id|strbuf
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
id|strbuf_add
c_func
(paren
id|buffer
comma
id|ptr
comma
id|size
)paren
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
id|strbuf
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
comma
r_void
op_star
id|cb
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
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|ssl_cert
op_assign
id|xstrdup
c_func
(paren
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
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|ssl_key
op_assign
id|xstrdup
c_func
(paren
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
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|ssl_capath
op_assign
id|xstrdup
c_func
(paren
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
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|ssl_cainfo
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;http.proxy&quot;
comma
id|var
)paren
)paren
(brace
r_if
c_cond
(paren
id|curl_http_proxy
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
id|curl_http_proxy
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
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
comma
id|cb
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
r_if
c_cond
(paren
id|curl_http_proxy
)paren
id|curl_easy_setopt
c_func
(paren
id|result
comma
id|CURLOPT_PROXY
comma
id|curl_http_proxy
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
r_struct
id|remote
op_star
id|remote
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
r_if
c_cond
(paren
id|remote
op_logical_and
id|remote-&gt;http_proxy
)paren
id|curl_http_proxy
op_assign
id|xstrdup
c_func
(paren
id|remote-&gt;http_proxy
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
comma
l_int|NULL
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
r_while
c_loop
(paren
id|slot
op_ne
l_int|NULL
)paren
(brace
r_struct
id|active_request_slot
op_star
id|next
op_assign
id|slot-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;curl
op_ne
l_int|NULL
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
)brace
id|free
c_func
(paren
id|slot
)paren
suffix:semicolon
id|slot
op_assign
id|next
suffix:semicolon
)brace
id|active_queue_head
op_assign
l_int|NULL
suffix:semicolon
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
id|pragma_header
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|curl_http_proxy
)paren
(brace
id|free
c_func
(paren
id|curl_http_proxy
)paren
suffix:semicolon
id|curl_http_proxy
op_assign
l_int|NULL
suffix:semicolon
)brace
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
r_int
id|num_transfers
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
multiline_comment|/*&n;&t; * We know there must be something to do, since we just added&n;&t; * something.&n;&t; */
id|curl_multi_perform
c_func
(paren
id|curlm
comma
op_amp
id|num_transfers
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef USE_CURL_MULTI
DECL|struct|fill_chain
r_struct
id|fill_chain
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|fill
r_int
(paren
op_star
id|fill
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|next
r_struct
id|fill_chain
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|fill_cfg
r_static
r_struct
id|fill_chain
op_star
id|fill_cfg
op_assign
l_int|NULL
suffix:semicolon
DECL|function|add_fill_function
r_void
id|add_fill_function
c_func
(paren
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fill
)paren
(paren
r_void
op_star
)paren
)paren
(brace
r_struct
id|fill_chain
op_star
r_new
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_struct
id|fill_chain
op_star
op_star
id|linkp
op_assign
op_amp
id|fill_cfg
suffix:semicolon
r_new
op_member_access_from_pointer
id|data
op_assign
id|data
suffix:semicolon
r_new
op_member_access_from_pointer
id|fill
op_assign
id|fill
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|linkp
)paren
id|linkp
op_assign
op_amp
(paren
op_star
id|linkp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
op_star
id|linkp
op_assign
r_new
suffix:semicolon
)brace
DECL|function|fill_active_slots
r_void
id|fill_active_slots
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
id|active_requests
OL
id|max_requests
)paren
(brace
r_struct
id|fill_chain
op_star
id|fill
suffix:semicolon
r_for
c_loop
(paren
id|fill
op_assign
id|fill_cfg
suffix:semicolon
id|fill
suffix:semicolon
id|fill
op_assign
id|fill-&gt;next
)paren
r_if
c_cond
(paren
id|fill
op_member_access_from_pointer
id|fill
c_func
(paren
id|fill-&gt;data
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fill
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|slot
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;in_use
op_logical_and
id|slot-&gt;curl
op_ne
l_int|NULL
)paren
(brace
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
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
)brace
)brace
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
DECL|function|needs_quote
r_static
r_inline
r_int
id|needs_quote
c_func
(paren
r_int
id|ch
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|ch
op_ge
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|ch
op_le
l_char|&squot;Z&squot;
)paren
)paren
op_logical_or
(paren
(paren
id|ch
op_ge
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
id|ch
op_le
l_char|&squot;z&squot;
)paren
)paren
op_logical_or
(paren
(paren
id|ch
op_ge
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
id|ch
op_le
l_char|&squot;9&squot;
)paren
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;-&squot;
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;.&squot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hex
r_static
r_inline
r_int
id|hex
c_func
(paren
r_int
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
OL
l_int|10
)paren
r_return
l_char|&squot;0&squot;
op_plus
id|v
suffix:semicolon
r_else
r_return
l_char|&squot;A&squot;
op_plus
id|v
l_int|10
suffix:semicolon
)brace
DECL|function|quote_ref_url
r_static
r_char
op_star
id|quote_ref_url
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_const
r_char
op_star
id|ref
)paren
(brace
r_const
r_char
op_star
id|cp
suffix:semicolon
r_char
op_star
id|dp
comma
op_star
id|qref
suffix:semicolon
r_int
id|len
comma
id|baselen
comma
id|ch
suffix:semicolon
id|baselen
op_assign
id|strlen
c_func
(paren
id|base
)paren
suffix:semicolon
id|len
op_assign
id|baselen
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* &squot;/&squot; after base and terminating NUL */
r_for
c_loop
(paren
id|cp
op_assign
id|ref
suffix:semicolon
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_ne
l_int|0
suffix:semicolon
id|cp
op_increment
comma
id|len
op_increment
)paren
r_if
c_cond
(paren
id|needs_quote
c_func
(paren
id|ch
)paren
)paren
id|len
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* extra two hex plus replacement % */
id|qref
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|qref
comma
id|base
comma
id|baselen
)paren
suffix:semicolon
id|dp
op_assign
id|qref
op_plus
id|baselen
suffix:semicolon
op_star
(paren
id|dp
op_increment
)paren
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
id|ref
suffix:semicolon
(paren
id|ch
op_assign
op_star
id|cp
)paren
op_ne
l_int|0
suffix:semicolon
id|cp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|needs_quote
c_func
(paren
id|ch
)paren
)paren
(brace
op_star
id|dp
op_increment
op_assign
l_char|&squot;%&squot;
suffix:semicolon
op_star
id|dp
op_increment
op_assign
id|hex
c_func
(paren
(paren
id|ch
op_rshift
l_int|4
)paren
op_amp
l_int|0xF
)paren
suffix:semicolon
op_star
id|dp
op_increment
op_assign
id|hex
c_func
(paren
id|ch
op_amp
l_int|0xF
)paren
suffix:semicolon
)brace
r_else
op_star
id|dp
op_increment
op_assign
id|ch
suffix:semicolon
)brace
op_star
id|dp
op_assign
l_int|0
suffix:semicolon
r_return
id|qref
suffix:semicolon
)brace
DECL|function|http_fetch_ref
r_int
id|http_fetch_ref
c_func
(paren
r_const
r_char
op_star
id|base
comma
r_struct
id|ref
op_star
id|ref
)paren
(brace
r_char
op_star
id|url
suffix:semicolon
r_struct
id|strbuf
id|buffer
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|active_request_slot
op_star
id|slot
suffix:semicolon
r_struct
id|slot_results
id|results
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|url
op_assign
id|quote_ref_url
c_func
(paren
id|base
comma
id|ref-&gt;name
)paren
suffix:semicolon
id|slot
op_assign
id|get_active_slot
c_func
(paren
)paren
suffix:semicolon
id|slot-&gt;results
op_assign
op_amp
id|results
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
id|CURLOPT_URL
comma
id|url
)paren
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
(brace
id|run_active_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|results.curl_result
op_eq
id|CURLE_OK
)paren
(brace
id|strbuf_rtrim
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer.len
op_eq
l_int|40
)paren
id|ret
op_assign
id|get_sha1_hex
c_func
(paren
id|buffer.buf
comma
id|ref-&gt;old_sha1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buffer.buf
comma
l_string|&quot;ref: &quot;
)paren
)paren
(brace
id|ref-&gt;symref
op_assign
id|xstrdup
c_func
(paren
id|buffer.buf
op_plus
l_int|5
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t get %s for %s&bslash;n%s&quot;
comma
id|url
comma
id|ref-&gt;name
comma
id|curl_errorstr
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ret
op_assign
id|error
c_func
(paren
l_string|&quot;Unable to start request&quot;
)paren
suffix:semicolon
)brace
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
r_return
id|ret
suffix:semicolon
)brace
eof
