multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Eric Biederman, 2005&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;string.h&gt;
DECL|variable|var_usage
r_static
r_const
r_char
id|var_usage
(braket
)braket
op_assign
l_string|&quot;git-var [-l | &lt;variable&gt;]&quot;
suffix:semicolon
DECL|struct|git_var
r_struct
id|git_var
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|read
r_char
op_star
(paren
op_star
id|read
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|git_vars
r_static
r_struct
id|git_var
id|git_vars
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;GIT_COMMITTER_IDENT&quot;
comma
id|git_committer_info
)brace
comma
(brace
l_string|&quot;GIT_AUTHOR_IDENT&quot;
comma
id|git_author_info
)brace
comma
(brace
l_string|&quot;&quot;
comma
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|function|list_vars
r_static
r_void
id|list_vars
c_func
(paren
r_void
)paren
(brace
r_struct
id|git_var
op_star
id|ptr
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|git_vars
suffix:semicolon
id|ptr-&gt;read
suffix:semicolon
id|ptr
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s=%s&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|ptr
op_member_access_from_pointer
id|read
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|read_var
r_static
r_const
r_char
op_star
id|read_var
c_func
(paren
r_const
r_char
op_star
id|var
)paren
(brace
r_struct
id|git_var
op_star
id|ptr
suffix:semicolon
r_const
r_char
op_star
id|val
suffix:semicolon
id|val
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|git_vars
suffix:semicolon
id|ptr-&gt;read
suffix:semicolon
id|ptr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|var
comma
id|ptr-&gt;name
)paren
op_eq
l_int|0
)paren
(brace
id|val
op_assign
id|ptr
op_member_access_from_pointer
id|read
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|show_config
r_static
r_int
id|show_config
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
r_if
c_cond
(paren
id|value
)paren
id|printf
c_func
(paren
l_string|&quot;%s=%s&bslash;n&quot;
comma
id|var
comma
id|value
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|var
)paren
suffix:semicolon
r_return
id|git_default_config
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
)brace
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
r_const
r_char
op_star
id|val
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
(brace
id|usage
c_func
(paren
id|var_usage
)paren
suffix:semicolon
)brace
id|setup_ident
c_func
(paren
)paren
suffix:semicolon
id|val
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-l&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|git_config
c_func
(paren
id|show_config
)paren
suffix:semicolon
id|list_vars
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|git_config
c_func
(paren
id|git_default_config
)paren
suffix:semicolon
id|val
op_assign
id|read_var
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|usage
c_func
(paren
id|var_usage
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
