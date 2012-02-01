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
DECL|function|advise
r_void
id|advise
c_func
(paren
r_const
r_char
op_star
id|advice
comma
dot
dot
dot
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
id|va_list
id|params
suffix:semicolon
r_const
r_char
op_star
id|cp
comma
op_star
id|np
suffix:semicolon
id|va_start
c_func
(paren
id|params
comma
id|advice
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
id|advice
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
r_for
c_loop
(paren
id|cp
op_assign
id|buf.buf
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cp
op_assign
id|np
)paren
(brace
id|np
op_assign
id|strchrnul
c_func
(paren
id|cp
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;hint: %.*s&bslash;n&quot;
)paren
comma
(paren
r_int
)paren
(paren
id|np
id|cp
)paren
comma
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|np
)paren
id|np
op_increment
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
DECL|function|error_resolve_conflict
r_int
id|error_resolve_conflict
c_func
(paren
r_const
r_char
op_star
id|me
)paren
(brace
id|error
c_func
(paren
l_string|&quot;&squot;%s&squot; is not possible because you have unmerged files.&quot;
comma
id|me
)paren
suffix:semicolon
r_if
c_cond
(paren
id|advice_resolve_conflict
)paren
multiline_comment|/*&n;&t;&t; * Message used both when &squot;git commit&squot; fails and when&n;&t;&t; * other commands doing a merge do.&n;&t;&t; */
id|advise
c_func
(paren
id|_
c_func
(paren
l_string|&quot;Fix them up in the work tree,&bslash;n&quot;
l_string|&quot;and then use &squot;git add/rm &lt;file&gt;&squot; as&bslash;n&quot;
l_string|&quot;appropriate to mark resolution and make a commit,&bslash;n&quot;
l_string|&quot;or use &squot;git commit -a&squot;.&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|1
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
id|error_resolve_conflict
c_func
(paren
id|me
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Exiting because of an unresolved conflict.&quot;
)paren
suffix:semicolon
)brace
DECL|function|detach_advice
r_void
id|detach_advice
c_func
(paren
r_const
r_char
op_star
id|new_name
)paren
(brace
r_const
r_char
id|fmt
(braket
)braket
op_assign
l_string|&quot;Note: checking out &squot;%s&squot;.&bslash;n&bslash;n&quot;
l_string|&quot;You are in &squot;detached HEAD&squot; state. You can look around, make experimental&bslash;n&quot;
l_string|&quot;changes and commit them, and you can discard any commits you make in this&bslash;n&quot;
l_string|&quot;state without impacting any branches by performing another checkout.&bslash;n&bslash;n&quot;
l_string|&quot;If you want to create a new branch to retain commits you create, you may&bslash;n&quot;
l_string|&quot;do so (now or later) by using -b with the checkout command again. Example:&bslash;n&bslash;n&quot;
l_string|&quot;  git checkout -b new_branch_name&bslash;n&bslash;n&quot;
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
id|fmt
comma
id|new_name
)paren
suffix:semicolon
)brace
eof
