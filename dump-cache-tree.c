macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|function|dump_cache_tree
r_static
r_void
id|dump_cache_tree
c_func
(paren
r_struct
id|cache_tree
op_star
id|it
comma
r_const
r_char
op_star
id|pfx
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|it
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|it-&gt;entry_count
OL
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;%-40s %s&bslash;n&quot;
comma
l_string|&quot;invalid&quot;
comma
id|pfx
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s %s (%d entries)&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|it-&gt;sha1
)paren
comma
id|pfx
comma
id|it-&gt;entry_count
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
id|it-&gt;subtree_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_struct
id|cache_tree_sub
op_star
id|down
op_assign
id|it-&gt;down
(braket
id|i
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|path
comma
l_string|&quot;%s%.*s/&quot;
comma
id|pfx
comma
id|down-&gt;namelen
comma
id|down-&gt;name
)paren
suffix:semicolon
id|dump_cache_tree
c_func
(paren
id|down-&gt;cache_tree
comma
id|path
)paren
suffix:semicolon
)brace
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|ac
comma
r_char
op_star
op_star
id|av
)paren
(brace
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to read index file&quot;
)paren
suffix:semicolon
id|dump_cache_tree
c_func
(paren
id|active_cache_tree
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
