macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;pack-refs.h&quot;
DECL|variable|pack_refs_usage
r_static
r_char
r_const
op_star
r_const
id|pack_refs_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git pack-refs [options]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|cmd_pack_refs
r_int
id|cmd_pack_refs
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
r_int
id|flags
op_assign
id|PACK_REFS_PRUNE
suffix:semicolon
r_struct
id|option
id|opts
(braket
)braket
op_assign
(brace
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;all&quot;
comma
op_amp
id|flags
comma
id|N_
c_func
(paren
l_string|&quot;pack everything&quot;
)paren
comma
id|PACK_REFS_ALL
)paren
comma
id|OPT_BIT
c_func
(paren
l_int|0
comma
l_string|&quot;prune&quot;
comma
op_amp
id|flags
comma
id|N_
c_func
(paren
l_string|&quot;prune loose refs (default)&quot;
)paren
comma
id|PACK_REFS_PRUNE
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|opts
comma
id|pack_refs_usage
comma
l_int|0
)paren
)paren
id|usage_with_options
c_func
(paren
id|pack_refs_usage
comma
id|opts
)paren
suffix:semicolon
r_return
id|pack_refs
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
