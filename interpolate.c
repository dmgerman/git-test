multiline_comment|/*&n; * Copyright 2006 Jon Loeliger&n; */
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;interpolate.h&quot;
multiline_comment|/*&n; * Convert a NUL-terminated string in buffer orig&n; * into the supplied buffer, result, whose length is reslen,&n; * performing substitutions on %-named sub-strings from&n; * the table, interps, with ninterps entries.&n; *&n; * Example interps:&n; *    {&n; *        { &quot;%H&quot;, &quot;example.org&quot;},&n; *        { &quot;%port&quot;, &quot;123&quot;},&n; *        { &quot;%%&quot;, &quot;%&quot;},&n; *    }&n; *&n; * Returns 1 on a successful substitution pass that fits in result,&n; * Returns 0 on a failed or overflowing substitution pass.&n; */
DECL|function|interpolate
r_int
id|interpolate
c_func
(paren
r_char
op_star
id|result
comma
r_int
id|reslen
comma
r_const
r_char
op_star
id|orig
comma
r_const
r_struct
id|interp
op_star
id|interps
comma
r_int
id|ninterps
)paren
(brace
r_const
r_char
op_star
id|src
op_assign
id|orig
suffix:semicolon
r_char
op_star
id|dest
op_assign
id|result
suffix:semicolon
r_int
id|newlen
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|name
comma
op_star
id|value
suffix:semicolon
r_int
id|namelen
comma
id|valuelen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
id|memset
c_func
(paren
id|result
comma
l_int|0
comma
id|reslen
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|src
)paren
op_logical_and
id|newlen
OL
id|reslen
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;%&squot;
)paren
(brace
multiline_comment|/* Try to match an interpolation string. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ninterps
suffix:semicolon
id|i
op_increment
)paren
(brace
id|name
op_assign
id|interps
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|src
comma
id|name
comma
id|namelen
)paren
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Check for valid interpolation. */
r_if
c_cond
(paren
id|i
OL
id|ninterps
)paren
(brace
id|value
op_assign
id|interps
(braket
id|i
)braket
dot
id|value
suffix:semicolon
id|valuelen
op_assign
id|strlen
c_func
(paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newlen
op_plus
id|valuelen
OL
id|reslen
l_int|1
)paren
(brace
multiline_comment|/* Substitute. */
id|strncpy
c_func
(paren
id|dest
comma
id|value
comma
id|valuelen
)paren
suffix:semicolon
id|newlen
op_add_assign
id|valuelen
suffix:semicolon
id|dest
op_add_assign
id|valuelen
suffix:semicolon
id|src
op_add_assign
id|namelen
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Something&squot;s not fitting. */
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Skip bogus interpolation. */
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
id|newlen
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Straight copy one non-interpolation character. */
op_star
id|dest
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
id|newlen
op_increment
suffix:semicolon
)brace
)brace
r_return
id|newlen
OL
id|reslen
l_int|1
suffix:semicolon
)brace
eof
