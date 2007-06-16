macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;netdb.h&gt;
DECL|function|githstrerror
r_const
r_char
op_star
id|githstrerror
c_func
(paren
r_int
id|err
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|48
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|err
)paren
(brace
r_case
id|HOST_NOT_FOUND
suffix:colon
r_return
l_string|&quot;Authoritative answer: host not found&quot;
suffix:semicolon
r_case
id|NO_DATA
suffix:colon
r_return
l_string|&quot;Valid name, no data record of requested type&quot;
suffix:semicolon
r_case
id|NO_RECOVERY
suffix:colon
r_return
l_string|&quot;Non recoverable errors, FORMERR, REFUSED, NOTIMP&quot;
suffix:semicolon
r_case
id|TRY_AGAIN
suffix:colon
r_return
l_string|&quot;Non-authoritative &bslash;&quot;host not found&bslash;&quot;, or SERVERFAIL&quot;
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Name resolution error %d&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
eof
