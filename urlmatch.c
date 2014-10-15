macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;urlmatch.h&quot;
DECL|macro|URL_ALPHA
mdefine_line|#define URL_ALPHA &quot;ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz&quot;
DECL|macro|URL_DIGIT
mdefine_line|#define URL_DIGIT &quot;0123456789&quot;
DECL|macro|URL_ALPHADIGIT
mdefine_line|#define URL_ALPHADIGIT URL_ALPHA URL_DIGIT
DECL|macro|URL_SCHEME_CHARS
mdefine_line|#define URL_SCHEME_CHARS URL_ALPHADIGIT &quot;+.-&quot;
DECL|macro|URL_HOST_CHARS
mdefine_line|#define URL_HOST_CHARS URL_ALPHADIGIT &quot;.-[:]&quot; /* IPv6 literals need [:] */
DECL|macro|URL_UNSAFE_CHARS
mdefine_line|#define URL_UNSAFE_CHARS &quot; &lt;&gt;&bslash;&quot;%{}|&bslash;&bslash;^`&quot; /* plus 0x00-0x1F,0x7F-0xFF */
DECL|macro|URL_GEN_RESERVED
mdefine_line|#define URL_GEN_RESERVED &quot;:/?#[]@&quot;
DECL|macro|URL_SUB_RESERVED
mdefine_line|#define URL_SUB_RESERVED &quot;!$&amp;&squot;()*+,;=&quot;
DECL|macro|URL_RESERVED
mdefine_line|#define URL_RESERVED URL_GEN_RESERVED URL_SUB_RESERVED /* only allowed delims */
DECL|function|append_normalized_escapes
r_static
r_int
id|append_normalized_escapes
c_func
(paren
r_struct
id|strbuf
op_star
id|buf
comma
r_const
r_char
op_star
id|from
comma
r_int
id|from_len
comma
r_const
r_char
op_star
id|esc_extra
comma
r_const
r_char
op_star
id|esc_ok
)paren
(brace
multiline_comment|/*&n;&t; * Append to strbuf &squot;buf&squot; characters from string &squot;from&squot; with length&n;&t; * &squot;from_len&squot; while unescaping characters that do not need to be escaped&n;&t; * and escaping characters that do.  The set of characters to escape&n;&t; * (the complement of which is unescaped) starts out as the RFC 3986&n;&t; * unsafe characters (0x00-0x1F,0x7F-0xFF,&quot; &lt;&gt;&bslash;&quot;#%{}|&bslash;&bslash;^`&quot;).  If&n;&t; * &squot;esc_extra&squot; is not NULL, those additional characters will also always&n;&t; * be escaped.  If &squot;esc_ok&squot; is not NULL, those characters will be left&n;&t; * escaped if found that way, but will not be unescaped otherwise (used&n;&t; * for delimiters).  If a %-escape sequence is encountered that is not&n;&t; * followed by 2 hexadecimal digits, the sequence is invalid and&n;&t; * false (0) will be returned.  Otherwise true (1) will be returned for&n;&t; * success.&n;&t; *&n;&t; * Note that all %-escape sequences will be normalized to UPPERCASE&n;&t; * as indicated in RFC 3986.  Unless included in esc_extra or esc_ok&n;&t; * alphanumerics and &quot;-._~&quot; will always be unescaped as per RFC 3986.&n;&t; */
r_while
c_loop
(paren
id|from_len
)paren
(brace
r_int
id|ch
op_assign
op_star
id|from
op_increment
suffix:semicolon
r_int
id|was_esc
op_assign
l_int|0
suffix:semicolon
id|from_len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;%&squot;
)paren
(brace
r_if
c_cond
(paren
id|from_len
OL
l_int|2
op_logical_or
op_logical_neg
id|isxdigit
c_func
(paren
id|from
(braket
l_int|0
)braket
)paren
op_logical_or
op_logical_neg
id|isxdigit
c_func
(paren
id|from
(braket
l_int|1
)braket
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|ch
op_assign
id|hexval
c_func
(paren
op_star
id|from
op_increment
)paren
op_lshift
l_int|4
suffix:semicolon
id|ch
op_or_assign
id|hexval
c_func
(paren
op_star
id|from
op_increment
)paren
suffix:semicolon
id|from_len
op_sub_assign
l_int|2
suffix:semicolon
id|was_esc
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|ch
op_le
l_int|0x1F
op_logical_or
(paren
r_int
r_char
)paren
id|ch
op_ge
l_int|0x7F
op_logical_or
id|strchr
c_func
(paren
id|URL_UNSAFE_CHARS
comma
id|ch
)paren
op_logical_or
(paren
id|esc_extra
op_logical_and
id|strchr
c_func
(paren
id|esc_extra
comma
id|ch
)paren
)paren
op_logical_or
(paren
id|was_esc
op_logical_and
id|strchr
c_func
(paren
id|esc_ok
comma
id|ch
)paren
)paren
)paren
id|strbuf_addf
c_func
(paren
id|buf
comma
l_string|&quot;%%%02X&quot;
comma
(paren
r_int
r_char
)paren
id|ch
)paren
suffix:semicolon
r_else
id|strbuf_addch
c_func
(paren
id|buf
comma
id|ch
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|url_normalize
r_char
op_star
id|url_normalize
c_func
(paren
r_const
r_char
op_star
id|url
comma
r_struct
id|url_info
op_star
id|out_info
)paren
(brace
multiline_comment|/*&n;&t; * Normalize NUL-terminated url using the following rules:&n;&t; *&n;&t; * 1. Case-insensitive parts of url will be converted to lower case&n;&t; * 2. %-encoded characters that do not need to be will be unencoded&n;&t; * 3. Characters that are not %-encoded and must be will be encoded&n;&t; * 4. All %-encodings will be converted to upper case hexadecimal&n;&t; * 5. Leading 0s are removed from port numbers&n;&t; * 6. If the default port for the scheme is given it will be removed&n;&t; * 7. A path part (including empty) not starting with &squot;/&squot; has one added&n;&t; * 8. Any dot segments (. or ..) in the path are resolved and removed&n;&t; * 9. IPv6 host literals are allowed (but not normalized or validated)&n;&t; *&n;&t; * The rules are based on information in RFC 3986.&n;&t; *&n;&t; * Please note this function requires a full URL including a scheme&n;&t; * and host part (except for file: URLs which may have an empty host).&n;&t; *&n;&t; * The return value is a newly allocated string that must be freed&n;&t; * or NULL if the url is not valid.&n;&t; *&n;&t; * If out_info is non-NULL, the url and err fields therein will always&n;&t; * be set.  If a non-NULL value is returned, it will be stored in&n;&t; * out_info-&gt;url as well, out_info-&gt;err will be set to NULL and the&n;&t; * other fields of *out_info will also be filled in.  If a NULL value&n;&t; * is returned, NULL will be stored in out_info-&gt;url and out_info-&gt;err&n;&t; * will be set to a brief, translated, error message, but no other&n;&t; * fields will be filled in.&n;&t; *&n;&t; * This is NOT a URL validation function.  Full URL validation is NOT&n;&t; * performed.  Some invalid host names are passed through this function&n;&t; * undetected.  However, most all other problems that make a URL invalid&n;&t; * will be detected (including a missing host for non file: URLs).&n;&t; */
r_int
id|url_len
op_assign
id|strlen
c_func
(paren
id|url
)paren
suffix:semicolon
r_struct
id|strbuf
id|norm
suffix:semicolon
r_int
id|spanned
suffix:semicolon
r_int
id|scheme_len
comma
id|user_off
op_assign
l_int|0
comma
id|user_len
op_assign
l_int|0
comma
id|passwd_off
op_assign
l_int|0
comma
id|passwd_len
op_assign
l_int|0
suffix:semicolon
r_int
id|host_off
op_assign
l_int|0
comma
id|host_len
op_assign
l_int|0
comma
id|port_len
op_assign
l_int|0
comma
id|path_off
comma
id|path_len
comma
id|result_len
suffix:semicolon
r_const
r_char
op_star
id|slash_ptr
comma
op_star
id|at_ptr
comma
op_star
id|colon_ptr
comma
op_star
id|path_start
suffix:semicolon
r_char
op_star
id|result
suffix:semicolon
multiline_comment|/*&n;&t; * Copy lowercased scheme and :// suffix, %-escapes are not allowed&n;&t; * First character of scheme must be URL_ALPHA&n;&t; */
id|spanned
op_assign
id|strspn
c_func
(paren
id|url
comma
id|URL_SCHEME_CHARS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|spanned
op_logical_or
op_logical_neg
id|isalpha
c_func
(paren
id|url
(braket
l_int|0
)braket
)paren
op_logical_or
id|spanned
op_plus
l_int|3
OG
id|url_len
op_logical_or
id|url
(braket
id|spanned
)braket
op_ne
l_char|&squot;:&squot;
op_logical_or
id|url
(braket
id|spanned
op_plus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
op_logical_or
id|url
(braket
id|spanned
op_plus
l_int|2
)braket
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid URL scheme name or missing &squot;://&squot; suffix&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Bad scheme and/or missing &quot;://&quot; part */
)brace
id|strbuf_init
c_func
(paren
op_amp
id|norm
comma
id|url_len
)paren
suffix:semicolon
id|scheme_len
op_assign
id|spanned
suffix:semicolon
id|spanned
op_add_assign
l_int|3
suffix:semicolon
id|url_len
op_sub_assign
id|spanned
suffix:semicolon
r_while
c_loop
(paren
id|spanned
op_decrement
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|norm
comma
id|tolower
c_func
(paren
op_star
id|url
op_increment
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Copy any username:password if present normalizing %-escapes&n;&t; */
id|at_ptr
op_assign
id|strchr
c_func
(paren
id|url
comma
l_char|&squot;@&squot;
)paren
suffix:semicolon
id|slash_ptr
op_assign
id|url
op_plus
id|strcspn
c_func
(paren
id|url
comma
l_string|&quot;/?#&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|at_ptr
op_logical_and
id|at_ptr
OL
id|slash_ptr
)paren
(brace
id|user_off
op_assign
id|norm.len
suffix:semicolon
r_if
c_cond
(paren
id|at_ptr
OG
id|url
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|append_normalized_escapes
c_func
(paren
op_amp
id|norm
comma
id|url
comma
id|at_ptr
id|url
comma
l_string|&quot;&quot;
comma
id|URL_RESERVED
)paren
)paren
(brace
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid %XX escape sequence&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|colon_ptr
op_assign
id|strchr
c_func
(paren
id|norm.buf
op_plus
id|scheme_len
op_plus
l_int|3
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|colon_ptr
)paren
(brace
id|passwd_off
op_assign
(paren
id|colon_ptr
op_plus
l_int|1
)paren
id|norm.buf
suffix:semicolon
id|passwd_len
op_assign
id|norm.len
id|passwd_off
suffix:semicolon
id|user_len
op_assign
(paren
id|passwd_off
l_int|1
)paren
(paren
id|scheme_len
op_plus
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
id|user_len
op_assign
id|norm.len
(paren
id|scheme_len
op_plus
l_int|3
)paren
suffix:semicolon
)brace
)brace
id|strbuf_addch
c_func
(paren
op_amp
id|norm
comma
l_char|&squot;@&squot;
)paren
suffix:semicolon
id|url_len
op_sub_assign
(paren
op_increment
id|at_ptr
id|url
)paren
suffix:semicolon
id|url
op_assign
id|at_ptr
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Copy the host part excluding any port part, no %-escapes allowed&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|url_len
op_logical_or
id|strchr
c_func
(paren
l_string|&quot;:/?#&quot;
comma
op_star
id|url
)paren
)paren
(brace
multiline_comment|/* Missing host invalid for all URL schemes except file */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|norm.buf
comma
l_string|&quot;file:&quot;
comma
l_int|5
)paren
)paren
(brace
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;missing host and scheme is not &squot;file:&squot;&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
id|host_off
op_assign
id|norm.len
suffix:semicolon
)brace
id|colon_ptr
op_assign
id|slash_ptr
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|colon_ptr
OG
id|url
op_logical_and
op_star
id|colon_ptr
op_ne
l_char|&squot;:&squot;
op_logical_and
op_star
id|colon_ptr
op_ne
l_char|&squot;]&squot;
)paren
id|colon_ptr
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_star
id|colon_ptr
op_ne
l_char|&squot;:&squot;
)paren
(brace
id|colon_ptr
op_assign
id|slash_ptr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|host_off
op_logical_and
id|colon_ptr
OL
id|slash_ptr
op_logical_and
id|colon_ptr
op_plus
l_int|1
op_ne
id|slash_ptr
)paren
(brace
multiline_comment|/* file: URLs may not have a port number */
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;a &squot;file:&squot; URL may not have a port number&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|spanned
op_assign
id|strspn
c_func
(paren
id|url
comma
id|URL_HOST_CHARS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spanned
OL
id|colon_ptr
id|url
)paren
(brace
multiline_comment|/* Host name has invalid characters */
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid characters in host name&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|url
OL
id|colon_ptr
)paren
(brace
id|strbuf_addch
c_func
(paren
op_amp
id|norm
comma
id|tolower
c_func
(paren
op_star
id|url
op_increment
)paren
)paren
suffix:semicolon
id|url_len
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check the port part and copy if not the default (after removing any&n;&t; * leading 0s); no %-escapes allowed&n;&t; */
r_if
c_cond
(paren
id|colon_ptr
OL
id|slash_ptr
)paren
(brace
multiline_comment|/* skip the &squot;:&squot; and leading 0s but not the last one if all 0s */
id|url
op_increment
suffix:semicolon
id|url
op_add_assign
id|strspn
c_func
(paren
id|url
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|url
op_eq
id|slash_ptr
op_logical_and
id|url
(braket
l_int|1
)braket
op_eq
l_char|&squot;0&squot;
)paren
id|url
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|url
op_eq
id|slash_ptr
)paren
(brace
multiline_comment|/* Skip &quot;:&quot; port with no number, it&squot;s same as default */
)brace
r_else
r_if
c_cond
(paren
id|slash_ptr
id|url
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|norm.buf
comma
l_string|&quot;http:&quot;
comma
l_int|5
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|url
comma
l_string|&quot;80&quot;
comma
l_int|2
)paren
)paren
(brace
multiline_comment|/* Skip http :80 as it&squot;s the default */
)brace
r_else
r_if
c_cond
(paren
id|slash_ptr
id|url
op_eq
l_int|3
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|norm.buf
comma
l_string|&quot;https:&quot;
comma
l_int|6
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|url
comma
l_string|&quot;443&quot;
comma
l_int|3
)paren
)paren
(brace
multiline_comment|/* Skip https :443 as it&squot;s the default */
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Port number must be all digits with leading 0s removed&n;&t;&t;&t; * and since all the protocols we deal with have a 16-bit&n;&t;&t;&t; * port number it must also be in the range 1..65535&n;&t;&t;&t; * 0 is not allowed because that means &quot;next available&quot;&n;&t;&t;&t; * on just about every system and therefore cannot be used&n;&t;&t;&t; */
r_int
r_int
id|pnum
op_assign
l_int|0
suffix:semicolon
id|spanned
op_assign
id|strspn
c_func
(paren
id|url
comma
id|URL_DIGIT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spanned
OL
id|slash_ptr
id|url
)paren
(brace
multiline_comment|/* port number has invalid characters */
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid port number&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slash_ptr
id|url
op_le
l_int|5
)paren
id|pnum
op_assign
id|strtoul
c_func
(paren
id|url
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pnum
op_eq
l_int|0
op_logical_or
id|pnum
OG
l_int|65535
)paren
(brace
multiline_comment|/* port number not in range 1..65535 */
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid port number&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|strbuf_addch
c_func
(paren
op_amp
id|norm
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
op_amp
id|norm
comma
id|url
comma
id|slash_ptr
id|url
)paren
suffix:semicolon
id|port_len
op_assign
id|slash_ptr
id|url
suffix:semicolon
)brace
id|url_len
op_sub_assign
id|slash_ptr
id|colon_ptr
suffix:semicolon
id|url
op_assign
id|slash_ptr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host_off
)paren
id|host_len
op_assign
id|norm.len
id|host_off
suffix:semicolon
multiline_comment|/*&n;&t; * Now copy the path resolving any . and .. segments being careful not&n;&t; * to corrupt the URL by unescaping any delimiters, but do add an&n;&t; * initial &squot;/&squot; if it&squot;s missing and do normalize any %-escape sequences.&n;&t; */
id|path_off
op_assign
id|norm.len
suffix:semicolon
id|path_start
op_assign
id|norm.buf
op_plus
id|path_off
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|norm
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|url
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|url
op_increment
suffix:semicolon
id|url_len
op_decrement
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_const
r_char
op_star
id|seg_start
suffix:semicolon
r_int
id|seg_start_off
op_assign
id|norm.len
suffix:semicolon
r_const
r_char
op_star
id|next_slash
op_assign
id|url
op_plus
id|strcspn
c_func
(paren
id|url
comma
l_string|&quot;/?#&quot;
)paren
suffix:semicolon
r_int
id|skip_add_slash
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * RFC 3689 indicates that any . or .. segments should be&n;&t;&t; * unescaped before being checked for.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|append_normalized_escapes
c_func
(paren
op_amp
id|norm
comma
id|url
comma
id|next_slash
id|url
comma
l_string|&quot;&quot;
comma
id|URL_RESERVED
)paren
)paren
(brace
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid %XX escape sequence&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|seg_start
op_assign
id|norm.buf
op_plus
id|seg_start_off
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|seg_start
comma
l_string|&quot;.&quot;
)paren
)paren
(brace
multiline_comment|/* ignore a . segment; be careful not to remove initial &squot;/&squot; */
r_if
c_cond
(paren
id|seg_start
op_eq
id|path_start
op_plus
l_int|1
)paren
(brace
id|strbuf_setlen
c_func
(paren
op_amp
id|norm
comma
id|norm.len
l_int|1
)paren
suffix:semicolon
id|skip_add_slash
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|strbuf_setlen
c_func
(paren
op_amp
id|norm
comma
id|norm.len
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|seg_start
comma
l_string|&quot;..&quot;
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * ignore a .. segment and remove the previous segment;&n;&t;&t;&t; * be careful not to remove initial &squot;/&squot; from path&n;&t;&t;&t; */
r_const
r_char
op_star
id|prev_slash
op_assign
id|norm.buf
op_plus
id|norm.len
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|prev_slash
op_eq
id|path_start
)paren
(brace
multiline_comment|/* invalid .. because no previous segment to remove */
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid &squot;..&squot; path segment&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
op_decrement
id|prev_slash
op_ne
l_char|&squot;/&squot;
)paren
(brace
)brace
r_if
c_cond
(paren
id|prev_slash
op_eq
id|path_start
)paren
(brace
id|strbuf_setlen
c_func
(paren
op_amp
id|norm
comma
id|prev_slash
id|norm.buf
op_plus
l_int|1
)paren
suffix:semicolon
id|skip_add_slash
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|strbuf_setlen
c_func
(paren
op_amp
id|norm
comma
id|prev_slash
id|norm.buf
)paren
suffix:semicolon
)brace
)brace
id|url_len
op_sub_assign
id|next_slash
id|url
suffix:semicolon
id|url
op_assign
id|next_slash
suffix:semicolon
multiline_comment|/* if the next char is not &squot;/&squot; done with the path */
r_if
c_cond
(paren
op_star
id|url
op_ne
l_char|&squot;/&squot;
)paren
r_break
suffix:semicolon
id|url
op_increment
suffix:semicolon
id|url_len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skip_add_slash
)paren
id|strbuf_addch
c_func
(paren
op_amp
id|norm
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
id|path_len
op_assign
id|norm.len
id|path_off
suffix:semicolon
multiline_comment|/*&n;&t; * Now simply copy the rest, if any, only normalizing %-escapes and&n;&t; * being careful not to corrupt the URL by unescaping any delimiters.&n;&t; */
r_if
c_cond
(paren
op_star
id|url
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|append_normalized_escapes
c_func
(paren
op_amp
id|norm
comma
id|url
comma
id|url_len
comma
l_string|&quot;&quot;
comma
id|URL_RESERVED
)paren
)paren
(brace
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;err
op_assign
id|_
c_func
(paren
l_string|&quot;invalid %XX escape sequence&quot;
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|norm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|result
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|norm
comma
op_amp
id|result_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_info
)paren
(brace
id|out_info-&gt;url
op_assign
id|result
suffix:semicolon
id|out_info-&gt;err
op_assign
l_int|NULL
suffix:semicolon
id|out_info-&gt;url_len
op_assign
id|result_len
suffix:semicolon
id|out_info-&gt;scheme_len
op_assign
id|scheme_len
suffix:semicolon
id|out_info-&gt;user_off
op_assign
id|user_off
suffix:semicolon
id|out_info-&gt;user_len
op_assign
id|user_len
suffix:semicolon
id|out_info-&gt;passwd_off
op_assign
id|passwd_off
suffix:semicolon
id|out_info-&gt;passwd_len
op_assign
id|passwd_len
suffix:semicolon
id|out_info-&gt;host_off
op_assign
id|host_off
suffix:semicolon
id|out_info-&gt;host_len
op_assign
id|host_len
suffix:semicolon
id|out_info-&gt;port_len
op_assign
id|port_len
suffix:semicolon
id|out_info-&gt;path_off
op_assign
id|path_off
suffix:semicolon
id|out_info-&gt;path_len
op_assign
id|path_len
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|url_match_prefix
r_static
r_int
id|url_match_prefix
c_func
(paren
r_const
r_char
op_star
id|url
comma
r_const
r_char
op_star
id|url_prefix
comma
r_int
id|url_prefix_len
)paren
(brace
multiline_comment|/*&n;&t; * url_prefix matches url if url_prefix is an exact match for url or it&n;&t; * is a prefix of url and the match ends on a path component boundary.&n;&t; * Both url and url_prefix are considered to have an implicit &squot;/&squot; on the&n;&t; * end for matching purposes if they do not already.&n;&t; *&n;&t; * url must be NUL terminated.  url_prefix_len is the length of&n;&t; * url_prefix which need not be NUL terminated.&n;&t; *&n;&t; * The return value is the length of the match in characters (including&n;&t; * the final &squot;/&squot; even if it&squot;s implicit) or 0 for no match.&n;&t; *&n;&t; * Passing NULL as url and/or url_prefix will always cause 0 to be&n;&t; * returned without causing any faults.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|url
op_logical_or
op_logical_neg
id|url_prefix
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|url_prefix_len
op_logical_or
(paren
id|url_prefix_len
op_eq
l_int|1
op_logical_and
op_star
id|url_prefix
op_eq
l_char|&squot;/&squot;
)paren
)paren
r_return
(paren
op_logical_neg
op_star
id|url
op_logical_or
op_star
id|url
op_eq
l_char|&squot;/&squot;
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|url_prefix
(braket
id|url_prefix_len
l_int|1
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|url_prefix_len
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|url
comma
id|url_prefix
comma
id|url_prefix_len
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|strlen
c_func
(paren
id|url
)paren
op_eq
id|url_prefix_len
)paren
op_logical_or
(paren
id|url
(braket
id|url_prefix_len
)braket
op_eq
l_char|&squot;/&squot;
)paren
)paren
r_return
id|url_prefix_len
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|match_urls
r_int
id|match_urls
c_func
(paren
r_const
r_struct
id|url_info
op_star
id|url
comma
r_const
r_struct
id|url_info
op_star
id|url_prefix
comma
r_int
op_star
id|exactusermatch
)paren
(brace
multiline_comment|/*&n;&t; * url_prefix matches url if the scheme, host and port of url_prefix&n;&t; * are the same as those of url and the path portion of url_prefix&n;&t; * is the same as the path portion of url or it is a prefix that&n;&t; * matches at a &squot;/&squot; boundary.  If url_prefix contains a user name,&n;&t; * that must also exactly match the user name in url.&n;&t; *&n;&t; * If the user, host, port and path match in this fashion, the returned&n;&t; * value is the length of the path match including any implicit&n;&t; * final &squot;/&squot;.  For example, &quot;http://me@example.com/path&quot; is matched by&n;&t; * &quot;http://example.com&quot; with a path length of 1.&n;&t; *&n;&t; * If there is a match and exactusermatch is not NULL, then&n;&t; * *exactusermatch will be set to true if both url and url_prefix&n;&t; * contained a user name or false if url_prefix did not have a&n;&t; * user name.  If there is no match *exactusermatch is left untouched.&n;&t; */
r_int
id|usermatched
op_assign
l_int|0
suffix:semicolon
r_int
id|pathmatchlen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|url
op_logical_or
op_logical_neg
id|url_prefix
op_logical_or
op_logical_neg
id|url-&gt;url
op_logical_or
op_logical_neg
id|url_prefix-&gt;url
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* check the scheme */
r_if
c_cond
(paren
id|url_prefix-&gt;scheme_len
op_ne
id|url-&gt;scheme_len
op_logical_or
id|strncmp
c_func
(paren
id|url-&gt;url
comma
id|url_prefix-&gt;url
comma
id|url-&gt;scheme_len
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* schemes do not match */
multiline_comment|/* check the user name if url_prefix has one */
r_if
c_cond
(paren
id|url_prefix-&gt;user_off
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|url-&gt;user_off
op_logical_or
id|url-&gt;user_len
op_ne
id|url_prefix-&gt;user_len
op_logical_or
id|strncmp
c_func
(paren
id|url-&gt;url
op_plus
id|url-&gt;user_off
comma
id|url_prefix-&gt;url
op_plus
id|url_prefix-&gt;user_off
comma
id|url-&gt;user_len
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* url_prefix has a user but it&squot;s not a match */
id|usermatched
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* check the host and port */
r_if
c_cond
(paren
id|url_prefix-&gt;host_len
op_ne
id|url-&gt;host_len
op_logical_or
id|strncmp
c_func
(paren
id|url-&gt;url
op_plus
id|url-&gt;host_off
comma
id|url_prefix-&gt;url
op_plus
id|url_prefix-&gt;host_off
comma
id|url-&gt;host_len
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* host names and/or ports do not match */
multiline_comment|/* check the path */
id|pathmatchlen
op_assign
id|url_match_prefix
c_func
(paren
id|url-&gt;url
op_plus
id|url-&gt;path_off
comma
id|url_prefix-&gt;url
op_plus
id|url_prefix-&gt;path_off
comma
id|url_prefix-&gt;url_len
id|url_prefix-&gt;path_off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pathmatchlen
op_logical_and
id|exactusermatch
)paren
op_star
id|exactusermatch
op_assign
id|usermatched
suffix:semicolon
r_return
id|pathmatchlen
suffix:semicolon
)brace
DECL|function|urlmatch_config_entry
r_int
id|urlmatch_config_entry
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
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_struct
id|urlmatch_config
op_star
id|collect
op_assign
id|cb
suffix:semicolon
r_struct
id|urlmatch_item
op_star
id|matched
suffix:semicolon
r_struct
id|url_info
op_star
id|url
op_assign
op_amp
id|collect-&gt;url
suffix:semicolon
r_const
r_char
op_star
id|key
comma
op_star
id|dot
suffix:semicolon
r_struct
id|strbuf
id|synthkey
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|matched_len
op_assign
l_int|0
suffix:semicolon
r_int
id|user_matched
op_assign
l_int|0
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skip_prefix
c_func
(paren
id|var
comma
id|collect-&gt;section
comma
op_amp
id|key
)paren
op_logical_or
op_star
(paren
id|key
op_increment
)paren
op_ne
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
id|collect-&gt;cascade_fn
)paren
r_return
id|collect
op_member_access_from_pointer
id|cascade_fn
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not interested */
)brace
id|dot
op_assign
id|strrchr
c_func
(paren
id|key
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dot
)paren
(brace
r_char
op_star
id|config_url
comma
op_star
id|norm_url
suffix:semicolon
r_struct
id|url_info
id|norm_info
suffix:semicolon
id|config_url
op_assign
id|xmemdupz
c_func
(paren
id|key
comma
id|dot
id|key
)paren
suffix:semicolon
id|norm_url
op_assign
id|url_normalize
c_func
(paren
id|config_url
comma
op_amp
id|norm_info
)paren
suffix:semicolon
id|free
c_func
(paren
id|config_url
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|norm_url
)paren
r_return
l_int|0
suffix:semicolon
id|matched_len
op_assign
id|match_urls
c_func
(paren
id|url
comma
op_amp
id|norm_info
comma
op_amp
id|user_matched
)paren
suffix:semicolon
id|free
c_func
(paren
id|norm_url
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|matched_len
)paren
r_return
l_int|0
suffix:semicolon
id|key
op_assign
id|dot
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|collect-&gt;key
op_logical_and
id|strcmp
c_func
(paren
id|key
comma
id|collect-&gt;key
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|item
op_assign
id|string_list_insert
c_func
(paren
op_amp
id|collect-&gt;vars
comma
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|item-&gt;util
)paren
(brace
id|matched
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|matched
)paren
)paren
suffix:semicolon
id|item-&gt;util
op_assign
id|matched
suffix:semicolon
)brace
r_else
(brace
id|matched
op_assign
id|item-&gt;util
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Is our match shorter?  Is our match the same&n;&t;&t; * length, and without user while the current&n;&t;&t; * candidate is with user?  Then we cannot use it.&n;&t;&t; */
r_if
c_cond
(paren
id|matched_len
OL
id|matched-&gt;matched_len
op_logical_or
(paren
(paren
id|matched_len
op_eq
id|matched-&gt;matched_len
)paren
op_logical_and
(paren
op_logical_neg
id|user_matched
op_logical_and
id|matched-&gt;user_matched
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Otherwise, replace it with this one. */
)brace
id|matched-&gt;matched_len
op_assign
id|matched_len
suffix:semicolon
id|matched-&gt;user_matched
op_assign
id|user_matched
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|synthkey
comma
id|collect-&gt;section
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|synthkey
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|synthkey
comma
id|key
)paren
suffix:semicolon
id|retval
op_assign
id|collect
op_member_access_from_pointer
id|collect_fn
c_func
(paren
id|synthkey.buf
comma
id|value
comma
id|collect-&gt;cb
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|synthkey
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
