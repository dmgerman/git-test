macro_line|#include &quot;cache.h&quot;
DECL|variable|advice_push_nonfastforward
r_int
id|advice_push_nonfastforward
op_assign
l_int|1
suffix:semicolon
DECL|variable|advice_status_hints
r_int
id|advice_status_hints
op_assign
l_int|1
suffix:semicolon
DECL|variable|advice_commit_before_merge
r_int
id|advice_commit_before_merge
op_assign
l_int|1
suffix:semicolon
DECL|variable|advice_resolve_conflict
r_int
id|advice_resolve_conflict
op_assign
l_int|1
suffix:semicolon
DECL|variable|advice_implicit_identity
r_int
id|advice_implicit_identity
op_assign
l_int|1
suffix:semicolon
DECL|variable|advice_detached_head
r_int
id|advice_detached_head
op_assign
l_int|1
suffix:semicolon
r_static
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|preference
r_int
op_star
id|preference
suffix:semicolon
DECL|variable|advice_config
)brace
id|advice_config
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;pushnonfastforward&quot;
comma
op_amp
id|advice_push_nonfastforward
)brace
comma
(brace
l_string|&quot;statushints&quot;
comma
op_amp
id|advice_status_hints
)brace
comma
(brace
l_string|&quot;commitbeforemerge&quot;
comma
op_amp
id|advice_commit_before_merge
)brace
comma
(brace
l_string|&quot;resolveconflict&quot;
comma
op_amp
id|advice_resolve_conflict
)brace
comma
(brace
l_string|&quot;implicitidentity&quot;
comma
op_amp
id|advice_implicit_identity
)brace
comma
(brace
l_string|&quot;detachedhead&quot;
comma
op_amp
id|advice_detached_head
)brace
comma
)brace
suffix:semicolon
DECL|function|git_default_advice_config
r_int
id|git_default_advice_config
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
r_const
r_char
op_star
id|k
op_assign
id|skip_prefix
c_func
(paren
id|var
comma
l_string|&quot;advice.&quot;
)paren
suffix:semicolon
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
id|advice_config
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|k
comma
id|advice_config
(braket
id|i
)braket
dot
id|name
)paren
)paren
r_continue
suffix:semicolon
op_star
id|advice_config
(braket
id|i
)braket
dot
id|preference
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|die_resolve_conflict
r_void
id|NORETURN
id|die_resolve_conflict
c_func
(paren
r_const
r_char
op_star
id|me
)paren
(brace
r_if
c_cond
(paren
id|advice_resolve_conflict
)paren
multiline_comment|/*&n;&t;&t; * Message used both when &squot;git commit&squot; fails and when&n;&t;&t; * other commands doing a merge do.&n;&t;&t; */
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not possible because you have unmerged files.&bslash;n&quot;
l_string|&quot;Please, fix them up in the work tree, and then use &squot;git add/rm &lt;file&gt;&squot; as&bslash;n&quot;
l_string|&quot;appropriate to mark resolution and make a commit, or use &squot;git commit -a&squot;.&quot;
comma
id|me
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot; is not possible because you have unmerged files.&quot;
comma
id|me
)paren
suffix:semicolon
)brace
eof
