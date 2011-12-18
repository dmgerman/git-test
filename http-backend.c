macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;pkt-line.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;tag.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;string-list.h&quot;
DECL|variable|content_type
r_static
r_const
r_char
id|content_type
(braket
)braket
op_assign
l_string|&quot;Content-Type&quot;
suffix:semicolon
DECL|variable|content_length
r_static
r_const
r_char
id|content_length
(braket
)braket
op_assign
l_string|&quot;Content-Length&quot;
suffix:semicolon
DECL|variable|last_modified
r_static
r_const
r_char
id|last_modified
(braket
)braket
op_assign
l_string|&quot;Last-Modified&quot;
suffix:semicolon
DECL|variable|getanyfile
r_static
r_int
id|getanyfile
op_assign
l_int|1
suffix:semicolon
DECL|variable|query_params
r_static
r_struct
id|string_list
op_star
id|query_params
suffix:semicolon
DECL|struct|rpc_service
r_struct
id|rpc_service
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|config_name
r_const
r_char
op_star
id|config_name
suffix:semicolon
DECL|member|enabled
r_int
id|enabled
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|rpc_service
r_static
r_struct
id|rpc_service
id|rpc_service
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;upload-pack&quot;
comma
l_string|&quot;uploadpack&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;receive-pack&quot;
comma
l_string|&quot;receivepack&quot;
comma
l_int|1
)brace
comma
)brace
suffix:semicolon
DECL|function|decode_char
r_static
r_int
id|decode_char
c_func
(paren
r_const
r_char
op_star
id|q
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|val
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|c
op_assign
op_star
id|q
op_increment
suffix:semicolon
id|val
op_lshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
id|val
op_add_assign
id|c
l_char|&squot;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;f&squot;
)paren
id|val
op_add_assign
id|c
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_else
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;A&squot;
op_logical_and
id|c
op_le
l_char|&squot;F&squot;
)paren
id|val
op_add_assign
id|c
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|decode_parameter
r_static
r_char
op_star
id|decode_parameter
c_func
(paren
r_const
r_char
op_star
op_star
id|query
comma
r_int
id|is_name
)paren
(brace
r_const
r_char
op_star
id|q
op_assign
op_star
id|query
suffix:semicolon
r_struct
id|strbuf
id|out
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|out
comma
l_int|16
)paren
suffix:semicolon
r_do
(brace
r_int
r_char
id|c
op_assign
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&amp;&squot;
op_logical_or
(paren
id|is_name
op_logical_and
id|c
op_eq
l_char|&squot;=&squot;
)paren
)paren
(brace
id|q
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;%&squot;
)paren
(brace
r_int
id|val
op_assign
id|decode_char
c_func
(paren
id|q
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|val
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|out
comma
id|val
)paren
suffix:semicolon
id|q
op_add_assign
l_int|3
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;+&squot;
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|out
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_else
id|strbuf_addch
c_func
(paren
op_amp
id|out
comma
id|c
)paren
suffix:semicolon
id|q
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
op_star
id|query
op_assign
id|q
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|out
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|get_parameters
r_static
r_struct
id|string_list
op_star
id|get_parameters
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|query_params
)paren
(brace
r_const
r_char
op_star
id|query
op_assign
id|getenv
c_func
(paren
l_string|&quot;QUERY_STRING&quot;
)paren
suffix:semicolon
id|query_params
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|query_params
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|query
op_logical_and
op_star
id|query
)paren
(brace
r_char
op_star
id|name
op_assign
id|decode_parameter
c_func
(paren
op_amp
id|query
comma
l_int|1
)paren
suffix:semicolon
r_char
op_star
id|value
op_assign
id|decode_parameter
c_func
(paren
op_amp
id|query
comma
l_int|0
)paren
suffix:semicolon
r_struct
id|string_list_item
op_star
id|i
suffix:semicolon
id|i
op_assign
id|string_list_lookup
c_func
(paren
id|name
comma
id|query_params
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
id|i
op_assign
id|string_list_insert
c_func
(paren
id|name
comma
id|query_params
)paren
suffix:semicolon
r_else
id|free
c_func
(paren
id|i-&gt;util
)paren
suffix:semicolon
id|i-&gt;util
op_assign
id|value
suffix:semicolon
)brace
)brace
r_return
id|query_params
suffix:semicolon
)brace
DECL|function|get_parameter
r_static
r_const
r_char
op_star
id|get_parameter
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|string_list_item
op_star
id|i
suffix:semicolon
id|i
op_assign
id|string_list_lookup
c_func
(paren
id|name
comma
id|get_parameters
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|i
ques
c_cond
id|i-&gt;util
suffix:colon
l_int|NULL
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|format
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
DECL|function|format_write
r_static
r_void
id|format_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
r_int
id|n
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|n
op_assign
id|vsnprintf
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
r_sizeof
(paren
id|buffer
)paren
)paren
id|die
c_func
(paren
l_string|&quot;protocol error: impossibly long line&quot;
)paren
suffix:semicolon
id|safe_write
c_func
(paren
id|fd
comma
id|buffer
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|http_status
r_static
r_void
id|http_status
c_func
(paren
r_int
id|code
comma
r_const
r_char
op_star
id|msg
)paren
(brace
id|format_write
c_func
(paren
l_int|1
comma
l_string|&quot;Status: %u %s&bslash;r&bslash;n&quot;
comma
id|code
comma
id|msg
)paren
suffix:semicolon
)brace
DECL|function|hdr_str
r_static
r_void
id|hdr_str
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
id|value
)paren
(brace
id|format_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s: %s&bslash;r&bslash;n&quot;
comma
id|name
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|hdr_int
r_static
r_void
id|hdr_int
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_uintmax
id|value
)paren
(brace
id|format_write
c_func
(paren
l_int|1
comma
l_string|&quot;%s: %&quot;
id|PRIuMAX
l_string|&quot;&bslash;r&bslash;n&quot;
comma
id|name
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|hdr_date
r_static
r_void
id|hdr_date
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|when
)paren
(brace
r_const
r_char
op_star
id|value
op_assign
id|show_date
c_func
(paren
id|when
comma
l_int|0
comma
id|DATE_RFC2822
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
id|name
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|hdr_nocache
r_static
r_void
id|hdr_nocache
c_func
(paren
r_void
)paren
(brace
id|hdr_str
c_func
(paren
l_string|&quot;Expires&quot;
comma
l_string|&quot;Fri, 01 Jan 1980 00:00:00 GMT&quot;
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
l_string|&quot;Pragma&quot;
comma
l_string|&quot;no-cache&quot;
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
l_string|&quot;Cache-Control&quot;
comma
l_string|&quot;no-cache, max-age=0, must-revalidate&quot;
)paren
suffix:semicolon
)brace
DECL|function|hdr_cache_forever
r_static
r_void
id|hdr_cache_forever
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|now
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|hdr_date
c_func
(paren
l_string|&quot;Date&quot;
comma
id|now
)paren
suffix:semicolon
id|hdr_date
c_func
(paren
l_string|&quot;Expires&quot;
comma
id|now
op_plus
l_int|31536000
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
l_string|&quot;Cache-Control&quot;
comma
l_string|&quot;public, max-age=31536000&quot;
)paren
suffix:semicolon
)brace
DECL|function|end_headers
r_static
r_void
id|end_headers
c_func
(paren
r_void
)paren
(brace
id|safe_write
c_func
(paren
l_int|1
comma
l_string|&quot;&bslash;r&bslash;n&quot;
comma
l_int|2
)paren
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
DECL|function|not_found
r_static
id|NORETURN
r_void
id|not_found
c_func
(paren
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|http_status
c_func
(paren
l_int|404
comma
l_string|&quot;Not Found&quot;
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_and
op_star
id|err
)paren
id|vfprintf
c_func
(paren
id|stderr
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
DECL|function|forbidden
r_static
id|NORETURN
r_void
id|forbidden
c_func
(paren
r_const
r_char
op_star
id|err
comma
dot
dot
dot
)paren
(brace
id|va_list
id|params
suffix:semicolon
id|http_status
c_func
(paren
l_int|403
comma
l_string|&quot;Forbidden&quot;
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_and
op_star
id|err
)paren
id|vfprintf
c_func
(paren
id|stderr
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|params
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|select_getanyfile
r_static
r_void
id|select_getanyfile
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|getanyfile
)paren
id|forbidden
c_func
(paren
l_string|&quot;Unsupported service: getanyfile&quot;
)paren
suffix:semicolon
)brace
DECL|function|send_strbuf
r_static
r_void
id|send_strbuf
c_func
(paren
r_const
r_char
op_star
id|type
comma
r_struct
id|strbuf
op_star
id|buf
)paren
(brace
id|hdr_int
c_func
(paren
id|content_length
comma
id|buf-&gt;len
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
id|content_type
comma
id|type
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|safe_write
c_func
(paren
l_int|1
comma
id|buf-&gt;buf
comma
id|buf-&gt;len
)paren
suffix:semicolon
)brace
DECL|function|send_local_file
r_static
r_void
id|send_local_file
c_func
(paren
r_const
r_char
op_star
id|the_type
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
id|git_path
c_func
(paren
l_string|&quot;%s&quot;
comma
id|name
)paren
suffix:semicolon
r_int
id|buf_alloc
op_assign
l_int|8192
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|xmalloc
c_func
(paren
id|buf_alloc
)paren
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_struct
id|stat
id|sb
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|p
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
id|not_found
c_func
(paren
l_string|&quot;Cannot open &squot;%s&squot;: %s&quot;
comma
id|p
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
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|sb
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot stat &squot;%s&squot;&quot;
comma
id|p
)paren
suffix:semicolon
id|hdr_int
c_func
(paren
id|content_length
comma
id|sb.st_size
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
id|content_type
comma
id|the_type
)paren
suffix:semicolon
id|hdr_date
c_func
(paren
id|last_modified
comma
id|sb.st_mtime
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|ssize_t
id|n
op_assign
id|xread
c_func
(paren
id|fd
comma
id|buf
comma
id|buf_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;Cannot read &squot;%s&squot;&quot;
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
r_break
suffix:semicolon
id|safe_write
c_func
(paren
l_int|1
comma
id|buf
comma
id|n
)paren
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|get_text_file
r_static
r_void
id|get_text_file
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|select_getanyfile
c_func
(paren
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|send_local_file
c_func
(paren
l_string|&quot;text/plain&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|get_loose_object
r_static
r_void
id|get_loose_object
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|select_getanyfile
c_func
(paren
)paren
suffix:semicolon
id|hdr_cache_forever
c_func
(paren
)paren
suffix:semicolon
id|send_local_file
c_func
(paren
l_string|&quot;application/x-git-loose-object&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|get_pack_file
r_static
r_void
id|get_pack_file
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|select_getanyfile
c_func
(paren
)paren
suffix:semicolon
id|hdr_cache_forever
c_func
(paren
)paren
suffix:semicolon
id|send_local_file
c_func
(paren
l_string|&quot;application/x-git-packed-objects&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|get_idx_file
r_static
r_void
id|get_idx_file
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|select_getanyfile
c_func
(paren
)paren
suffix:semicolon
id|hdr_cache_forever
c_func
(paren
)paren
suffix:semicolon
id|send_local_file
c_func
(paren
l_string|&quot;application/x-git-packed-objects-toc&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|http_config
r_static
r_int
id|http_config
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
id|var
comma
l_string|&quot;http.getanyfile&quot;
)paren
)paren
(brace
id|getanyfile
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
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;http.&quot;
)paren
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
id|ARRAY_SIZE
c_func
(paren
id|rpc_service
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|rpc_service
op_star
id|svc
op_assign
op_amp
id|rpc_service
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
op_plus
l_int|5
comma
id|svc-&gt;config_name
)paren
)paren
(brace
id|svc-&gt;enabled
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
)brace
)brace
multiline_comment|/* we are not interested in parsing any other configuration here */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|select_service
r_static
r_struct
id|rpc_service
op_star
id|select_service
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|rpc_service
op_star
id|svc
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;git-&quot;
)paren
)paren
id|forbidden
c_func
(paren
l_string|&quot;Unsupported service: &squot;%s&squot;&quot;
comma
id|name
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
id|ARRAY_SIZE
c_func
(paren
id|rpc_service
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|rpc_service
op_star
id|s
op_assign
op_amp
id|rpc_service
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s-&gt;name
comma
id|name
op_plus
l_int|4
)paren
)paren
(brace
id|svc
op_assign
id|s
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|svc
)paren
id|forbidden
c_func
(paren
l_string|&quot;Unsupported service: &squot;%s&squot;&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|svc-&gt;enabled
OL
l_int|0
)paren
(brace
r_const
r_char
op_star
id|user
op_assign
id|getenv
c_func
(paren
l_string|&quot;REMOTE_USER&quot;
)paren
suffix:semicolon
id|svc-&gt;enabled
op_assign
(paren
id|user
op_logical_and
op_star
id|user
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|svc-&gt;enabled
)paren
id|forbidden
c_func
(paren
l_string|&quot;Service not enabled: &squot;%s&squot;&quot;
comma
id|svc-&gt;name
)paren
suffix:semicolon
r_return
id|svc
suffix:semicolon
)brace
DECL|function|inflate_request
r_static
r_void
id|inflate_request
c_func
(paren
r_const
r_char
op_star
id|prog_name
comma
r_int
id|out
)paren
(brace
id|z_stream
id|stream
suffix:semicolon
r_int
r_char
id|in_buf
(braket
l_int|8192
)braket
suffix:semicolon
r_int
r_char
id|out_buf
(braket
l_int|8192
)braket
suffix:semicolon
r_int
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|stream
comma
l_int|0
comma
r_sizeof
(paren
id|stream
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|inflateInit2
c_func
(paren
op_amp
id|stream
comma
(paren
l_int|15
op_plus
l_int|16
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|Z_OK
)paren
id|die
c_func
(paren
l_string|&quot;cannot start zlib inflater, zlib err %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|ssize_t
id|n
op_assign
id|xread
c_func
(paren
l_int|0
comma
id|in_buf
comma
r_sizeof
(paren
id|in_buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;request ended in the middle of the gzip stream&quot;
)paren
suffix:semicolon
id|stream.next_in
op_assign
id|in_buf
suffix:semicolon
id|stream.avail_in
op_assign
id|n
suffix:semicolon
r_while
c_loop
(paren
l_int|0
OL
id|stream.avail_in
)paren
(brace
r_int
id|ret
suffix:semicolon
id|stream.next_out
op_assign
id|out_buf
suffix:semicolon
id|stream.avail_out
op_assign
r_sizeof
(paren
id|out_buf
)paren
suffix:semicolon
id|ret
op_assign
id|inflate
c_func
(paren
op_amp
id|stream
comma
id|Z_NO_FLUSH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|Z_OK
op_logical_and
id|ret
op_ne
id|Z_STREAM_END
)paren
id|die
c_func
(paren
l_string|&quot;zlib error inflating request, result %d&quot;
comma
id|ret
)paren
suffix:semicolon
id|n
op_assign
id|stream.total_out
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|write_in_full
c_func
(paren
id|out
comma
id|out_buf
comma
id|n
)paren
op_ne
id|n
)paren
id|die
c_func
(paren
l_string|&quot;%s aborted reading request&quot;
comma
id|prog_name
)paren
suffix:semicolon
id|cnt
op_add_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|Z_STREAM_END
)paren
r_goto
id|done
suffix:semicolon
)brace
)brace
id|done
suffix:colon
id|inflateEnd
c_func
(paren
op_amp
id|stream
)paren
suffix:semicolon
id|close
c_func
(paren
id|out
)paren
suffix:semicolon
)brace
DECL|function|run_service
r_static
r_void
id|run_service
c_func
(paren
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
id|encoding
op_assign
id|getenv
c_func
(paren
l_string|&quot;HTTP_CONTENT_ENCODING&quot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|user
op_assign
id|getenv
c_func
(paren
l_string|&quot;REMOTE_USER&quot;
)paren
suffix:semicolon
r_const
r_char
op_star
id|host
op_assign
id|getenv
c_func
(paren
l_string|&quot;REMOTE_ADDR&quot;
)paren
suffix:semicolon
r_char
op_star
id|env
(braket
l_int|3
)braket
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|gzipped_request
op_assign
l_int|0
suffix:semicolon
r_struct
id|child_process
id|cld
suffix:semicolon
r_if
c_cond
(paren
id|encoding
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|encoding
comma
l_string|&quot;gzip&quot;
)paren
)paren
id|gzipped_request
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|encoding
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|encoding
comma
l_string|&quot;x-gzip&quot;
)paren
)paren
id|gzipped_request
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user
op_logical_or
op_logical_neg
op_star
id|user
)paren
id|user
op_assign
l_string|&quot;anonymous&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
op_logical_or
op_logical_neg
op_star
id|host
)paren
id|host
op_assign
l_string|&quot;(none)&quot;
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|env
comma
l_int|0
comma
r_sizeof
(paren
id|env
)paren
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;GIT_COMMITTER_NAME=%s&quot;
comma
id|user
)paren
suffix:semicolon
id|env
(braket
l_int|0
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;GIT_COMMITTER_EMAIL=%s@http.%s&quot;
comma
id|user
comma
id|host
)paren
suffix:semicolon
id|env
(braket
l_int|1
)braket
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
id|env
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cld
comma
l_int|0
comma
r_sizeof
(paren
id|cld
)paren
)paren
suffix:semicolon
id|cld.argv
op_assign
id|argv
suffix:semicolon
id|cld.env
op_assign
(paren
r_const
r_char
op_star
r_const
op_star
)paren
id|env
suffix:semicolon
r_if
c_cond
(paren
id|gzipped_request
)paren
id|cld.in
op_assign
l_int|1
suffix:semicolon
id|cld.git_cmd
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
id|cld
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gzipped_request
)paren
id|inflate_request
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|cld.in
)paren
suffix:semicolon
r_else
id|close
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|finish_command
c_func
(paren
op_amp
id|cld
)paren
)paren
m_exit
(paren
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|env
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|free
c_func
(paren
id|env
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|show_text_ref
r_static
r_int
id|show_text_ref
c_func
(paren
r_const
r_char
op_star
id|name
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
id|strbuf
op_star
id|buf
op_assign
id|cb_data
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
r_return
l_int|0
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;t%s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
comma
id|name
)paren
suffix:semicolon
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
id|name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o
)paren
r_return
l_int|0
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;%s&bslash;t%s^{}&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|o-&gt;sha1
)paren
comma
id|name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_info_refs
r_static
r_void
id|get_info_refs
c_func
(paren
r_char
op_star
id|arg
)paren
(brace
r_const
r_char
op_star
id|service_name
op_assign
id|get_parameter
c_func
(paren
l_string|&quot;service&quot;
)paren
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|service_name
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
l_int|NULL
multiline_comment|/* service name */
comma
l_string|&quot;--stateless-rpc&quot;
comma
l_string|&quot;--advertise-refs&quot;
comma
l_string|&quot;.&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|rpc_service
op_star
id|svc
op_assign
id|select_service
c_func
(paren
id|service_name
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;application/x-git-%s-advertisement&quot;
comma
id|svc-&gt;name
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
id|content_type
comma
id|buf.buf
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|packet_write
c_func
(paren
l_int|1
comma
l_string|&quot;# service=git-%s&bslash;n&quot;
comma
id|svc-&gt;name
)paren
suffix:semicolon
id|packet_flush
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|svc-&gt;name
suffix:semicolon
id|run_service
c_func
(paren
id|argv
)paren
suffix:semicolon
)brace
r_else
(brace
id|select_getanyfile
c_func
(paren
)paren
suffix:semicolon
id|for_each_ref
c_func
(paren
id|show_text_ref
comma
op_amp
id|buf
)paren
suffix:semicolon
id|send_strbuf
c_func
(paren
l_string|&quot;text/plain&quot;
comma
op_amp
id|buf
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
DECL|function|get_info_packs
r_static
r_void
id|get_info_packs
c_func
(paren
r_char
op_star
id|arg
)paren
(brace
r_int
id|objdirlen
op_assign
id|strlen
c_func
(paren
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
id|select_getanyfile
c_func
(paren
)paren
suffix:semicolon
id|prepare_packed_git
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|packed_git
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pack_local
)paren
id|cnt
op_increment
suffix:semicolon
)brace
id|strbuf_grow
c_func
(paren
op_amp
id|buf
comma
id|cnt
op_star
l_int|53
op_plus
l_int|2
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|packed_git
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pack_local
)paren
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;P %s&bslash;n&quot;
comma
id|p-&gt;pack_name
op_plus
id|objdirlen
op_plus
l_int|6
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
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|send_strbuf
c_func
(paren
l_string|&quot;text/plain; charset=utf-8&quot;
comma
op_amp
id|buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|check_content_type
r_static
r_void
id|check_content_type
c_func
(paren
r_const
r_char
op_star
id|accepted_type
)paren
(brace
r_const
r_char
op_star
id|actual_type
op_assign
id|getenv
c_func
(paren
l_string|&quot;CONTENT_TYPE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|actual_type
)paren
id|actual_type
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|actual_type
comma
id|accepted_type
)paren
)paren
(brace
id|http_status
c_func
(paren
l_int|415
comma
l_string|&quot;Unsupported Media Type&quot;
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|format_write
c_func
(paren
l_int|1
comma
l_string|&quot;Expected POST with Content-Type &squot;%s&squot;,&quot;
l_string|&quot; but received &squot;%s&squot; instead.&bslash;n&quot;
comma
id|accepted_type
comma
id|actual_type
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|service_rpc
r_static
r_void
id|service_rpc
c_func
(paren
r_char
op_star
id|service_name
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
l_int|NULL
comma
l_string|&quot;--stateless-rpc&quot;
comma
l_string|&quot;.&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|rpc_service
op_star
id|svc
op_assign
id|select_service
c_func
(paren
id|service_name
)paren
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
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
l_string|&quot;application/x-git-%s-request&quot;
comma
id|svc-&gt;name
)paren
suffix:semicolon
id|check_content_type
c_func
(paren
id|buf.buf
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
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
l_string|&quot;application/x-git-%s-result&quot;
comma
id|svc-&gt;name
)paren
suffix:semicolon
id|hdr_str
c_func
(paren
id|content_type
comma
id|buf.buf
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|svc-&gt;name
suffix:semicolon
id|run_service
c_func
(paren
id|argv
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
DECL|function|die_webcgi
r_static
id|NORETURN
r_void
id|die_webcgi
c_func
(paren
r_const
r_char
op_star
id|err
comma
id|va_list
id|params
)paren
(brace
r_char
id|buffer
(braket
l_int|1000
)braket
suffix:semicolon
id|http_status
c_func
(paren
l_int|500
comma
l_string|&quot;Internal Server Error&quot;
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
id|vsnprintf
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|err
comma
id|params
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;fatal: %s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|getdir
r_static
r_char
op_star
id|getdir
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_char
op_star
id|pathinfo
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH_INFO&quot;
)paren
suffix:semicolon
r_char
op_star
id|root
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_PROJECT_ROOT&quot;
)paren
suffix:semicolon
r_char
op_star
id|path
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH_TRANSLATED&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
op_logical_and
op_star
id|root
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pathinfo
op_logical_or
op_logical_neg
op_star
id|pathinfo
)paren
id|die
c_func
(paren
l_string|&quot;GIT_PROJECT_ROOT is set but PATH_INFO is not&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|daemon_avoid_alias
c_func
(paren
id|pathinfo
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: aliased&quot;
comma
id|pathinfo
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf.buf
(braket
id|buf.len
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|buf
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathinfo
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|pathinfo
op_increment
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|pathinfo
)paren
suffix:semicolon
r_return
id|strbuf_detach
c_func
(paren
op_amp
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|path
op_logical_and
op_star
id|path
)paren
(brace
r_return
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
r_else
id|die
c_func
(paren
l_string|&quot;No GIT_PROJECT_ROOT or PATH_TRANSLATED from server&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|struct|service_cmd
r_static
r_struct
id|service_cmd
(brace
DECL|member|method
r_const
r_char
op_star
id|method
suffix:semicolon
DECL|member|pattern
r_const
r_char
op_star
id|pattern
suffix:semicolon
DECL|member|imp
r_void
(paren
op_star
id|imp
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|variable|services
)brace
id|services
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/HEAD$&quot;
comma
id|get_text_file
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/info/refs$&quot;
comma
id|get_info_refs
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/objects/info/alternates$&quot;
comma
id|get_text_file
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/objects/info/http-alternates$&quot;
comma
id|get_text_file
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/objects/info/packs$&quot;
comma
id|get_info_packs
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/objects/[0-9a-f]{2}/[0-9a-f]{38}$&quot;
comma
id|get_loose_object
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/objects/pack/pack-[0-9a-f]{40}&bslash;&bslash;.pack$&quot;
comma
id|get_pack_file
)brace
comma
(brace
l_string|&quot;GET&quot;
comma
l_string|&quot;/objects/pack/pack-[0-9a-f]{40}&bslash;&bslash;.idx$&quot;
comma
id|get_idx_file
)brace
comma
(brace
l_string|&quot;POST&quot;
comma
l_string|&quot;/git-upload-pack$&quot;
comma
id|service_rpc
)brace
comma
(brace
l_string|&quot;POST&quot;
comma
l_string|&quot;/git-receive-pack$&quot;
comma
id|service_rpc
)brace
)brace
suffix:semicolon
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
id|method
op_assign
id|getenv
c_func
(paren
l_string|&quot;REQUEST_METHOD&quot;
)paren
suffix:semicolon
r_char
op_star
id|dir
suffix:semicolon
r_struct
id|service_cmd
op_star
id|cmd
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|cmd_arg
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
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
id|set_die_routine
c_func
(paren
id|die_webcgi
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|method
)paren
id|die
c_func
(paren
l_string|&quot;No REQUEST_METHOD from server&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|method
comma
l_string|&quot;HEAD&quot;
)paren
)paren
id|method
op_assign
l_string|&quot;GET&quot;
suffix:semicolon
id|dir
op_assign
id|getdir
c_func
(paren
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
id|ARRAY_SIZE
c_func
(paren
id|services
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|service_cmd
op_star
id|c
op_assign
op_amp
id|services
(braket
id|i
)braket
suffix:semicolon
id|regex_t
id|re
suffix:semicolon
id|regmatch_t
id|out
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|regcomp
c_func
(paren
op_amp
id|re
comma
id|c-&gt;pattern
comma
id|REG_EXTENDED
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Bogus regex in service table: %s&quot;
comma
id|c-&gt;pattern
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|regexec
c_func
(paren
op_amp
id|re
comma
id|dir
comma
l_int|1
comma
id|out
comma
l_int|0
)paren
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|method
comma
id|c-&gt;method
)paren
)paren
(brace
r_const
r_char
op_star
id|proto
op_assign
id|getenv
c_func
(paren
l_string|&quot;SERVER_PROTOCOL&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proto
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|proto
comma
l_string|&quot;HTTP/1.1&quot;
)paren
)paren
id|http_status
c_func
(paren
l_int|405
comma
l_string|&quot;Method Not Allowed&quot;
)paren
suffix:semicolon
r_else
id|http_status
c_func
(paren
l_int|400
comma
l_string|&quot;Bad Request&quot;
)paren
suffix:semicolon
id|hdr_nocache
c_func
(paren
)paren
suffix:semicolon
id|end_headers
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cmd
op_assign
id|c
suffix:semicolon
id|n
op_assign
id|out
(braket
l_int|0
)braket
dot
id|rm_eo
id|out
(braket
l_int|0
)braket
dot
id|rm_so
suffix:semicolon
id|cmd_arg
op_assign
id|xmalloc
c_func
(paren
id|n
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd_arg
comma
id|dir
op_plus
id|out
(braket
l_int|0
)braket
dot
id|rm_so
op_plus
l_int|1
comma
id|n
op_minus
l_int|1
)paren
suffix:semicolon
id|cmd_arg
(braket
id|n
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|dir
(braket
id|out
(braket
l_int|0
)braket
dot
id|rm_so
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|regfree
c_func
(paren
op_amp
id|re
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cmd
)paren
id|not_found
c_func
(paren
l_string|&quot;Request not supported: &squot;%s&squot;&quot;
comma
id|dir
)paren
suffix:semicolon
id|setup_path
c_func
(paren
)paren
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
l_int|0
)paren
)paren
id|not_found
c_func
(paren
l_string|&quot;Not a git repository: &squot;%s&squot;&quot;
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|getenv
c_func
(paren
l_string|&quot;GIT_HTTP_EXPORT_ALL&quot;
)paren
op_logical_and
id|access
c_func
(paren
l_string|&quot;git-daemon-export-ok&quot;
comma
id|F_OK
)paren
)paren
id|not_found
c_func
(paren
l_string|&quot;Repository not exported: &squot;%s&squot;&quot;
comma
id|dir
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|http_config
comma
l_int|NULL
)paren
suffix:semicolon
id|cmd
op_member_access_from_pointer
id|imp
c_func
(paren
id|cmd_arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
