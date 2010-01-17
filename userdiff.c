macro_line|#include &quot;userdiff.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;attr.h&quot;
DECL|variable|drivers
r_static
r_struct
id|userdiff_driver
op_star
id|drivers
suffix:semicolon
DECL|variable|ndrivers
r_static
r_int
id|ndrivers
suffix:semicolon
DECL|variable|drivers_alloc
r_static
r_int
id|drivers_alloc
suffix:semicolon
DECL|macro|PATTERNS
mdefine_line|#define PATTERNS(name, pattern, word_regex)&t;&t;&t;&bslash;&n;&t;{ name, NULL, -1, { pattern, REG_EXTENDED }, word_regex }
DECL|variable|builtin_drivers
r_static
r_struct
id|userdiff_driver
id|builtin_drivers
(braket
)braket
op_assign
(brace
id|PATTERNS
c_func
(paren
l_string|&quot;html&quot;
comma
l_string|&quot;^[ &bslash;t]*(&lt;[Hh][1-6][ &bslash;t].*&gt;.*)$&quot;
comma
l_string|&quot;[^&lt;&gt;= &bslash;t]+|[^[:space:]]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;java&quot;
comma
l_string|&quot;!^[ &bslash;t]*(catch|do|for|if|instanceof|new|return|switch|throw|while)&bslash;n&quot;
l_string|&quot;^[ &bslash;t]*(([A-Za-z_][A-Za-z_0-9]*[ &bslash;t]+)+[A-Za-z_][A-Za-z_0-9]*[ &bslash;t]*&bslash;&bslash;([^;]*)$&quot;
comma
multiline_comment|/* -- */
l_string|&quot;[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+[fFlL]?|0[xXbB]?[0-9a-fA-F]+[lL]?&quot;
l_string|&quot;|[-+*/&lt;&gt;%&amp;^|=!]=&quot;
l_string|&quot;|--|&bslash;&bslash;+&bslash;&bslash;+|&lt;&lt;=?|&gt;&gt;&gt;?=?|&amp;&amp;|&bslash;&bslash;|&bslash;&bslash;|&quot;
l_string|&quot;|[^[:space:]]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;objc&quot;
comma
multiline_comment|/* Negate C statements that can look like functions */
l_string|&quot;!^[ &bslash;t]*(do|for|if|else|return|switch|while)&bslash;n&quot;
multiline_comment|/* Objective-C methods */
l_string|&quot;^[ &bslash;t]*([-+][ &bslash;t]*&bslash;&bslash;([ &bslash;t]*[A-Za-z_][A-Za-z_0-9* &bslash;t]*&bslash;&bslash;)[ &bslash;t]*[A-Za-z_].*)$&bslash;n&quot;
multiline_comment|/* C functions */
l_string|&quot;^[ &bslash;t]*(([A-Za-z_][A-Za-z_0-9]*[ &bslash;t]+)+[A-Za-z_][A-Za-z_0-9]*[ &bslash;t]*&bslash;&bslash;([^;]*)$&bslash;n&quot;
multiline_comment|/* Objective-C class/protocol definitions */
l_string|&quot;^(@(implementation|interface|protocol)[ &bslash;t].*)$&quot;
comma
multiline_comment|/* -- */
l_string|&quot;[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+[fFlL]?|0[xXbB]?[0-9a-fA-F]+[lL]?&quot;
l_string|&quot;|[-+*/&lt;&gt;%&amp;^|=!]=|--|&bslash;&bslash;+&bslash;&bslash;+|&lt;&lt;=?|&gt;&gt;=?|&amp;&amp;|&bslash;&bslash;|&bslash;&bslash;||::|-&gt;&quot;
l_string|&quot;|[^[:space:]]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;pascal&quot;
comma
l_string|&quot;^((procedure|function|constructor|destructor|interface|&quot;
l_string|&quot;implementation|initialization|finalization)[ &bslash;t]*.*)$&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;^(.*=[ &bslash;t]*(class|record).*)$&quot;
comma
multiline_comment|/* -- */
l_string|&quot;[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+|0[xXbB]?[0-9a-fA-F]+&quot;
l_string|&quot;|&lt;&gt;|&lt;=|&gt;=|:=|&bslash;&bslash;.&bslash;&bslash;.&quot;
l_string|&quot;|[^[:space:]]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;php&quot;
comma
l_string|&quot;^[&bslash;t ]*((function|class).*)&quot;
comma
multiline_comment|/* -- */
l_string|&quot;[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+|0[xXbB]?[0-9a-fA-F]+&quot;
l_string|&quot;|[-+*/&lt;&gt;%&amp;^|=!.]=|--|&bslash;&bslash;+&bslash;&bslash;+|&lt;&lt;=?|&gt;&gt;=?|===|&amp;&amp;|&bslash;&bslash;|&bslash;&bslash;||::|-&gt;&quot;
l_string|&quot;|[^[:space:]]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;python&quot;
comma
l_string|&quot;^[ &bslash;t]*((class|def)[ &bslash;t].*)$&quot;
comma
multiline_comment|/* -- */
l_string|&quot;[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+[jJlL]?|0[xX]?[0-9a-fA-F]+[lL]?&quot;
l_string|&quot;|[-+*/&lt;&gt;%&amp;^|=!]=|//=?|&lt;&lt;=?|&gt;&gt;=?|&bslash;&bslash;*&bslash;&bslash;*=?&quot;
l_string|&quot;|[^[:space:]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
multiline_comment|/* -- */
id|PATTERNS
c_func
(paren
l_string|&quot;ruby&quot;
comma
l_string|&quot;^[ &bslash;t]*((class|module|def)[ &bslash;t].*)$&quot;
comma
multiline_comment|/* -- */
l_string|&quot;(@|@@|&bslash;&bslash;$)?[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+|0[xXbB]?[0-9a-fA-F]+|&bslash;&bslash;?(&bslash;&bslash;&bslash;&bslash;C-)?(&bslash;&bslash;&bslash;&bslash;M-)?.&quot;
l_string|&quot;|//=?|[-+*/&lt;&gt;%&amp;^|=!]=|&lt;&lt;=?|&gt;&gt;=?|===|&bslash;&bslash;.{1,3}|::|[!=]~&quot;
l_string|&quot;|[^[:space:]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;bibtex&quot;
comma
l_string|&quot;(@[a-zA-Z]{1,}[ &bslash;t]*&bslash;&bslash;{{0,1}[ &bslash;t]*[^ &bslash;t&bslash;&quot;@&squot;,&bslash;&bslash;#}{~%]*).*$&quot;
comma
l_string|&quot;[={}&bslash;&quot;]|[^={}&bslash;&quot; &bslash;t]+&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;tex&quot;
comma
l_string|&quot;^(&bslash;&bslash;&bslash;&bslash;((sub)*section|chapter|part)&bslash;&bslash;*{0,1}&bslash;&bslash;{.*)$&quot;
comma
l_string|&quot;&bslash;&bslash;&bslash;&bslash;[a-zA-Z@]+|&bslash;&bslash;&bslash;&bslash;.|[a-zA-Z0-9&bslash;x80-&bslash;xff]+|[^[:space:]]&quot;
)paren
comma
id|PATTERNS
c_func
(paren
l_string|&quot;cpp&quot;
comma
multiline_comment|/* Jump targets or access declarations */
l_string|&quot;!^[ &bslash;t]*[A-Za-z_][A-Za-z_0-9]*:.*$&bslash;n&quot;
multiline_comment|/* C/++ functions/methods at top level */
l_string|&quot;^([A-Za-z_][A-Za-z_0-9]*([ &bslash;t]+[A-Za-z_][A-Za-z_0-9]*([ &bslash;t]*::[ &bslash;t]*[^[:space:]]+)?){1,}[ &bslash;t]*&bslash;&bslash;([^;]*)$&bslash;n&quot;
multiline_comment|/* compound type at top level */
l_string|&quot;^((struct|class|enum)[^;]*)$&quot;
comma
multiline_comment|/* -- */
l_string|&quot;[a-zA-Z_][a-zA-Z0-9_]*&quot;
l_string|&quot;|[-+0-9.e]+[fFlL]?|0[xXbB]?[0-9a-fA-F]+[lL]?&quot;
l_string|&quot;|[-+*/&lt;&gt;%&amp;^|=!]=|--|&bslash;&bslash;+&bslash;&bslash;+|&lt;&lt;=?|&gt;&gt;=?|&amp;&amp;|&bslash;&bslash;|&bslash;&bslash;||::|-&gt;&quot;
l_string|&quot;|[^[:space:]]|[&bslash;x80-&bslash;xff]+&quot;
)paren
comma
(brace
l_string|&quot;default&quot;
comma
l_int|NULL
comma
l_int|1
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
comma
)brace
suffix:semicolon
DECL|macro|PATTERNS
macro_line|#undef PATTERNS
DECL|variable|driver_true
r_static
r_struct
id|userdiff_driver
id|driver_true
op_assign
(brace
l_string|&quot;diff=true&quot;
comma
l_int|NULL
comma
l_int|0
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|driver_false
r_static
r_struct
id|userdiff_driver
id|driver_false
op_assign
(brace
l_string|&quot;!diff&quot;
comma
l_int|NULL
comma
l_int|1
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|userdiff_find_by_namelen
r_static
r_struct
id|userdiff_driver
op_star
id|userdiff_find_by_namelen
c_func
(paren
r_const
r_char
op_star
id|k
comma
r_int
id|len
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
id|ndrivers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|userdiff_driver
op_star
id|drv
op_assign
id|drivers
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|drv-&gt;name
comma
id|k
comma
id|len
)paren
op_logical_and
op_logical_neg
id|drv-&gt;name
(braket
id|len
)braket
)paren
r_return
id|drv
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
id|ARRAY_SIZE
c_func
(paren
id|builtin_drivers
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|userdiff_driver
op_star
id|drv
op_assign
id|builtin_drivers
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|drv-&gt;name
comma
id|k
comma
id|len
)paren
op_logical_and
op_logical_neg
id|drv-&gt;name
(braket
id|len
)braket
)paren
r_return
id|drv
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|parse_driver
r_static
r_struct
id|userdiff_driver
op_star
id|parse_driver
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
r_const
r_char
op_star
id|type
)paren
(brace
r_struct
id|userdiff_driver
op_star
id|drv
suffix:semicolon
r_const
r_char
op_star
id|dot
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;diff.&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|dot
op_assign
id|strrchr
c_func
(paren
id|var
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dot
op_eq
id|var
op_plus
l_int|4
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|type
comma
id|dot
op_plus
l_int|1
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|name
op_assign
id|var
op_plus
l_int|5
suffix:semicolon
id|namelen
op_assign
id|dot
id|name
suffix:semicolon
id|drv
op_assign
id|userdiff_find_by_namelen
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
)paren
(brace
id|ALLOC_GROW
c_func
(paren
id|drivers
comma
id|ndrivers
op_plus
l_int|1
comma
id|drivers_alloc
)paren
suffix:semicolon
id|drv
op_assign
op_amp
id|drivers
(braket
id|ndrivers
op_increment
)braket
suffix:semicolon
id|memset
c_func
(paren
id|drv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|drv
)paren
)paren
suffix:semicolon
id|drv-&gt;name
op_assign
id|xmemdupz
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
id|drv-&gt;binary
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|drv
suffix:semicolon
)brace
DECL|function|parse_funcname
r_static
r_int
id|parse_funcname
c_func
(paren
r_struct
id|userdiff_funcname
op_star
id|f
comma
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
r_int
id|cflags
)paren
(brace
r_if
c_cond
(paren
id|git_config_string
c_func
(paren
op_amp
id|f-&gt;pattern
comma
id|k
comma
id|v
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|f-&gt;cflags
op_assign
id|cflags
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parse_string
r_static
r_int
id|parse_string
c_func
(paren
r_const
r_char
op_star
op_star
id|d
comma
r_const
r_char
op_star
id|k
comma
r_const
r_char
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|git_config_string
c_func
(paren
id|d
comma
id|k
comma
id|v
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parse_tristate
r_static
r_int
id|parse_tristate
c_func
(paren
r_int
op_star
id|b
comma
r_const
r_char
op_star
id|k
comma
r_const
r_char
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
op_logical_and
op_logical_neg
id|strcasecmp
c_func
(paren
id|v
comma
l_string|&quot;auto&quot;
)paren
)paren
op_star
id|b
op_assign
l_int|1
suffix:semicolon
r_else
op_star
id|b
op_assign
id|git_config_bool
c_func
(paren
id|k
comma
id|v
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|userdiff_config
r_int
id|userdiff_config
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
)paren
(brace
r_struct
id|userdiff_driver
op_star
id|drv
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|parse_driver
c_func
(paren
id|k
comma
id|v
comma
l_string|&quot;funcname&quot;
)paren
)paren
)paren
r_return
id|parse_funcname
c_func
(paren
op_amp
id|drv-&gt;funcname
comma
id|k
comma
id|v
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|parse_driver
c_func
(paren
id|k
comma
id|v
comma
l_string|&quot;xfuncname&quot;
)paren
)paren
)paren
r_return
id|parse_funcname
c_func
(paren
op_amp
id|drv-&gt;funcname
comma
id|k
comma
id|v
comma
id|REG_EXTENDED
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|parse_driver
c_func
(paren
id|k
comma
id|v
comma
l_string|&quot;binary&quot;
)paren
)paren
)paren
r_return
id|parse_tristate
c_func
(paren
op_amp
id|drv-&gt;binary
comma
id|k
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|parse_driver
c_func
(paren
id|k
comma
id|v
comma
l_string|&quot;command&quot;
)paren
)paren
)paren
r_return
id|parse_string
c_func
(paren
op_amp
id|drv-&gt;external
comma
id|k
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|parse_driver
c_func
(paren
id|k
comma
id|v
comma
l_string|&quot;textconv&quot;
)paren
)paren
)paren
r_return
id|parse_string
c_func
(paren
op_amp
id|drv-&gt;textconv
comma
id|k
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|parse_driver
c_func
(paren
id|k
comma
id|v
comma
l_string|&quot;wordregex&quot;
)paren
)paren
)paren
r_return
id|parse_string
c_func
(paren
op_amp
id|drv-&gt;word_regex
comma
id|k
comma
id|v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|userdiff_find_by_name
r_struct
id|userdiff_driver
op_star
id|userdiff_find_by_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|userdiff_find_by_namelen
c_func
(paren
id|name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|userdiff_find_by_path
r_struct
id|userdiff_driver
op_star
id|userdiff_find_by_path
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_static
r_struct
id|git_attr
op_star
id|attr
suffix:semicolon
r_struct
id|git_attr_check
id|check
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr
)paren
id|attr
op_assign
id|git_attr
c_func
(paren
l_string|&quot;diff&quot;
)paren
suffix:semicolon
id|check.attr
op_assign
id|attr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|git_checkattr
c_func
(paren
id|path
comma
l_int|1
comma
op_amp
id|check
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_TRUE
c_func
(paren
id|check.value
)paren
)paren
r_return
op_amp
id|driver_true
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_FALSE
c_func
(paren
id|check.value
)paren
)paren
r_return
op_amp
id|driver_false
suffix:semicolon
r_if
c_cond
(paren
id|ATTR_UNSET
c_func
(paren
id|check.value
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|userdiff_find_by_name
c_func
(paren
id|check.value
)paren
suffix:semicolon
)brace
eof
