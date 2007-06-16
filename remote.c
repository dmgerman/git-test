macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;refs.h&quot;
DECL|variable|remotes
r_static
r_struct
id|remote
op_star
op_star
id|remotes
suffix:semicolon
DECL|variable|allocated_remotes
r_static
r_int
id|allocated_remotes
suffix:semicolon
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE (2048)
DECL|variable|buffer
r_static
r_char
id|buffer
(braket
id|BUF_SIZE
)braket
suffix:semicolon
DECL|function|add_push_refspec
r_static
r_void
id|add_push_refspec
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
id|nr
op_assign
id|remote-&gt;push_refspec_nr
op_plus
l_int|1
suffix:semicolon
id|remote-&gt;push_refspec
op_assign
id|xrealloc
c_func
(paren
id|remote-&gt;push_refspec
comma
id|nr
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|remote-&gt;push_refspec
(braket
id|nr
op_minus
l_int|1
)braket
op_assign
id|ref
suffix:semicolon
id|remote-&gt;push_refspec_nr
op_assign
id|nr
suffix:semicolon
)brace
DECL|function|add_fetch_refspec
r_static
r_void
id|add_fetch_refspec
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
id|nr
op_assign
id|remote-&gt;fetch_refspec_nr
op_plus
l_int|1
suffix:semicolon
id|remote-&gt;fetch_refspec
op_assign
id|xrealloc
c_func
(paren
id|remote-&gt;fetch_refspec
comma
id|nr
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|remote-&gt;fetch_refspec
(braket
id|nr
op_minus
l_int|1
)braket
op_assign
id|ref
suffix:semicolon
id|remote-&gt;fetch_refspec_nr
op_assign
id|nr
suffix:semicolon
)brace
DECL|function|add_uri
r_static
r_void
id|add_uri
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_const
r_char
op_star
id|uri
)paren
(brace
r_int
id|nr
op_assign
id|remote-&gt;uri_nr
op_plus
l_int|1
suffix:semicolon
id|remote-&gt;uri
op_assign
id|xrealloc
c_func
(paren
id|remote-&gt;uri
comma
id|nr
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|remote-&gt;uri
(braket
id|nr
op_minus
l_int|1
)braket
op_assign
id|uri
suffix:semicolon
id|remote-&gt;uri_nr
op_assign
id|nr
suffix:semicolon
)brace
DECL|function|make_remote
r_static
r_struct
id|remote
op_star
id|make_remote
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|i
comma
id|empty
op_assign
l_int|1
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
id|allocated_remotes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|remotes
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|empty
OL
l_int|0
)paren
id|empty
op_assign
id|i
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|len
ques
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|name
comma
id|remotes
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|len
)paren
op_logical_and
op_logical_neg
id|remotes
(braket
id|i
)braket
op_member_access_from_pointer
id|name
(braket
id|len
)braket
)paren
suffix:colon
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
id|remotes
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
r_return
id|remotes
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|empty
OL
l_int|0
)paren
(brace
id|empty
op_assign
id|allocated_remotes
suffix:semicolon
id|allocated_remotes
op_add_assign
id|allocated_remotes
ques
c_cond
id|allocated_remotes
suffix:colon
l_int|1
suffix:semicolon
id|remotes
op_assign
id|xrealloc
c_func
(paren
id|remotes
comma
r_sizeof
(paren
op_star
id|remotes
)paren
op_star
id|allocated_remotes
)paren
suffix:semicolon
id|memset
c_func
(paren
id|remotes
op_plus
id|empty
comma
l_int|0
comma
(paren
id|allocated_remotes
id|empty
)paren
op_star
r_sizeof
(paren
op_star
id|remotes
)paren
)paren
suffix:semicolon
)brace
id|remotes
(braket
id|empty
)braket
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|remote
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
id|remotes
(braket
id|empty
)braket
op_member_access_from_pointer
id|name
op_assign
id|xstrndup
c_func
(paren
id|name
comma
id|len
)paren
suffix:semicolon
r_else
id|remotes
(braket
id|empty
)braket
op_member_access_from_pointer
id|name
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|remotes
(braket
id|empty
)braket
suffix:semicolon
)brace
DECL|function|read_remotes_file
r_static
r_void
id|read_remotes_file
c_func
(paren
r_struct
id|remote
op_star
id|remote
)paren
(brace
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;remotes/%s&quot;
comma
id|remote-&gt;name
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer
comma
id|BUF_SIZE
comma
id|f
)paren
)paren
(brace
r_int
id|value_list
suffix:semicolon
r_char
op_star
id|s
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buffer
comma
l_string|&quot;URL:&quot;
)paren
)paren
(brace
id|value_list
op_assign
l_int|0
suffix:semicolon
id|s
op_assign
id|buffer
op_plus
l_int|4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buffer
comma
l_string|&quot;Push:&quot;
)paren
)paren
(brace
id|value_list
op_assign
l_int|1
suffix:semicolon
id|s
op_assign
id|buffer
op_plus
l_int|5
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|buffer
comma
l_string|&quot;Pull:&quot;
)paren
)paren
(brace
id|value_list
op_assign
l_int|2
suffix:semicolon
id|s
op_assign
id|buffer
op_plus
l_int|5
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|s
)paren
)paren
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|s
)paren
r_continue
suffix:semicolon
id|p
op_assign
id|s
op_plus
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|p
(braket
l_int|1
)braket
)paren
)paren
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|value_list
)paren
(brace
r_case
l_int|0
suffix:colon
id|add_uri
c_func
(paren
id|remote
comma
id|xstrdup
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|add_push_refspec
c_func
(paren
id|remote
comma
id|xstrdup
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|add_fetch_refspec
c_func
(paren
id|remote
comma
id|xstrdup
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
DECL|function|read_branches_file
r_static
r_void
id|read_branches_file
c_func
(paren
r_struct
id|remote
op_star
id|remote
)paren
(brace
r_const
r_char
op_star
id|slash
op_assign
id|strchr
c_func
(paren
id|remote-&gt;name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_int
id|n
op_assign
id|slash
ques
c_cond
id|slash
id|remote-&gt;name
suffix:colon
l_int|1000
suffix:semicolon
id|FILE
op_star
id|f
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;branches/%.*s&quot;
comma
id|n
comma
id|remote-&gt;name
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_char
op_star
id|s
comma
op_star
id|p
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_return
suffix:semicolon
id|s
op_assign
id|fgets
c_func
(paren
id|buffer
comma
id|BUF_SIZE
comma
id|f
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|s
)paren
)paren
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|s
)paren
r_return
suffix:semicolon
id|p
op_assign
id|s
op_plus
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|p
(braket
l_int|1
)braket
)paren
)paren
op_star
op_decrement
id|p
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|p
id|s
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
id|len
op_add_assign
id|strlen
c_func
(paren
id|slash
)paren
suffix:semicolon
id|p
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slash
)paren
id|strcat
c_func
(paren
id|p
comma
id|slash
)paren
suffix:semicolon
id|add_uri
c_func
(paren
id|remote
comma
id|p
)paren
suffix:semicolon
)brace
DECL|variable|default_remote_name
r_static
r_char
op_star
id|default_remote_name
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|current_branch
r_static
r_const
r_char
op_star
id|current_branch
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|current_branch_len
r_static
r_int
id|current_branch_len
op_assign
l_int|0
suffix:semicolon
DECL|function|handle_config
r_static
r_int
id|handle_config
c_func
(paren
r_const
r_char
op_star
id|key
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
id|name
suffix:semicolon
r_const
r_char
op_star
id|subkey
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|key
comma
l_string|&quot;branch.&quot;
)paren
op_logical_and
id|current_branch
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|key
op_plus
l_int|7
comma
id|current_branch
comma
id|current_branch_len
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|key
op_plus
l_int|7
op_plus
id|current_branch_len
comma
l_string|&quot;.remote&quot;
)paren
)paren
(brace
id|free
c_func
(paren
id|default_remote_name
)paren
suffix:semicolon
id|default_remote_name
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|key
comma
l_string|&quot;remote.&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|name
op_assign
id|key
op_plus
l_int|7
suffix:semicolon
id|subkey
op_assign
id|strrchr
c_func
(paren
id|name
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subkey
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Config with no key for remote %s&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|subkey
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;Config remote shorthand cannot begin with &squot;/&squot;: %s&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|remote
op_assign
id|make_remote
c_func
(paren
id|name
comma
id|subkey
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
multiline_comment|/* if we ever have a boolean variable, e.g. &quot;remote.*.disabled&quot;&n;&t;&t; * [remote &quot;frotz&quot;]&n;&t;&t; *      disabled&n;&t;&t; * is a valid way to set it to true; we get NULL in value so&n;&t;&t; * we need to handle it here.&n;&t;&t; *&n;&t;&t; * if (!strcmp(subkey, &quot;.disabled&quot;)) {&n;&t;&t; *      val = git_config_bool(key, value);&n;&t;&t; *      return 0;&n;&t;&t; * } else&n;&t;&t; *&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ignore unknown booleans */
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|subkey
comma
l_string|&quot;.url&quot;
)paren
)paren
(brace
id|add_uri
c_func
(paren
id|remote
comma
id|xstrdup
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|subkey
comma
l_string|&quot;.push&quot;
)paren
)paren
(brace
id|add_push_refspec
c_func
(paren
id|remote
comma
id|xstrdup
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|subkey
comma
l_string|&quot;.fetch&quot;
)paren
)paren
(brace
id|add_fetch_refspec
c_func
(paren
id|remote
comma
id|xstrdup
c_func
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|subkey
comma
l_string|&quot;.receivepack&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|remote-&gt;receivepack
)paren
id|remote-&gt;receivepack
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
id|error
c_func
(paren
l_string|&quot;more than one receivepack given, using the first&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_config
r_static
r_void
id|read_config
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|head_ref
suffix:semicolon
r_int
id|flag
suffix:semicolon
r_if
c_cond
(paren
id|default_remote_name
)paren
singleline_comment|// did this already
r_return
suffix:semicolon
id|default_remote_name
op_assign
id|xstrdup
c_func
(paren
l_string|&quot;origin&quot;
)paren
suffix:semicolon
id|current_branch
op_assign
l_int|NULL
suffix:semicolon
id|head_ref
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1
comma
l_int|0
comma
op_amp
id|flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head_ref
op_logical_and
(paren
id|flag
op_amp
id|REF_ISSYMREF
)paren
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|head_ref
comma
l_string|&quot;refs/heads/&quot;
)paren
)paren
(brace
id|current_branch
op_assign
id|head_ref
op_plus
id|strlen
c_func
(paren
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
id|current_branch_len
op_assign
id|strlen
c_func
(paren
id|current_branch
)paren
suffix:semicolon
)brace
id|git_config
c_func
(paren
id|handle_config
)paren
suffix:semicolon
)brace
DECL|function|parse_ref_spec
r_static
r_struct
id|refspec
op_star
id|parse_ref_spec
c_func
(paren
r_int
id|nr_refspec
comma
r_const
r_char
op_star
op_star
id|refspec
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|refspec
op_star
id|rs
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|rs
)paren
comma
id|nr_refspec
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
id|nr_refspec
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|sp
comma
op_star
id|ep
comma
op_star
id|gp
suffix:semicolon
id|sp
op_assign
id|refspec
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sp
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|rs
(braket
id|i
)braket
dot
id|force
op_assign
l_int|1
suffix:semicolon
id|sp
op_increment
suffix:semicolon
)brace
id|gp
op_assign
id|strchr
c_func
(paren
id|sp
comma
l_char|&squot;*&squot;
)paren
suffix:semicolon
id|ep
op_assign
id|strchr
c_func
(paren
id|sp
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gp
op_logical_and
id|ep
op_logical_and
id|gp
OG
id|ep
)paren
id|gp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ep
)paren
(brace
r_if
c_cond
(paren
id|ep
(braket
l_int|1
)braket
)paren
(brace
r_const
r_char
op_star
id|glob
op_assign
id|strchr
c_func
(paren
id|ep
op_plus
l_int|1
comma
l_char|&squot;*&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|glob
)paren
id|gp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|gp
)paren
id|rs
(braket
id|i
)braket
dot
id|dst
op_assign
id|xstrndup
c_func
(paren
id|ep
op_plus
l_int|1
comma
id|glob
id|ep
l_int|1
)paren
suffix:semicolon
r_else
id|rs
(braket
id|i
)braket
dot
id|dst
op_assign
id|xstrdup
c_func
(paren
id|ep
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ep
op_assign
id|sp
op_plus
id|strlen
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gp
)paren
(brace
id|rs
(braket
id|i
)braket
dot
id|pattern
op_assign
l_int|1
suffix:semicolon
id|ep
op_assign
id|gp
suffix:semicolon
)brace
id|rs
(braket
id|i
)braket
dot
id|src
op_assign
id|xstrndup
c_func
(paren
id|sp
comma
id|ep
id|sp
)paren
suffix:semicolon
)brace
r_return
id|rs
suffix:semicolon
)brace
DECL|function|remote_get
r_struct
id|remote
op_star
id|remote_get
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|remote
op_star
id|ret
suffix:semicolon
id|read_config
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
id|default_remote_name
suffix:semicolon
id|ret
op_assign
id|make_remote
c_func
(paren
id|name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_ne
l_char|&squot;/&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ret-&gt;uri
)paren
id|read_remotes_file
c_func
(paren
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret-&gt;uri
)paren
id|read_branches_file
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret-&gt;uri
)paren
id|add_uri
c_func
(paren
id|ret
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret-&gt;uri
)paren
r_return
l_int|NULL
suffix:semicolon
id|ret-&gt;fetch
op_assign
id|parse_ref_spec
c_func
(paren
id|ret-&gt;fetch_refspec_nr
comma
id|ret-&gt;fetch_refspec
)paren
suffix:semicolon
id|ret-&gt;push
op_assign
id|parse_ref_spec
c_func
(paren
id|ret-&gt;push_refspec_nr
comma
id|ret-&gt;push_refspec
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|remote_has_uri
r_int
id|remote_has_uri
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_const
r_char
op_star
id|uri
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
id|remote-&gt;uri_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|remote-&gt;uri
(braket
id|i
)braket
comma
id|uri
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remote_find_tracking
r_int
id|remote_find_tracking
c_func
(paren
r_struct
id|remote
op_star
id|remote
comma
r_struct
id|refspec
op_star
id|refspec
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
id|remote-&gt;fetch_refspec_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|refspec
op_star
id|fetch
op_assign
op_amp
id|remote-&gt;fetch
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fetch-&gt;dst
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|fetch-&gt;pattern
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|refspec-&gt;src
comma
id|fetch-&gt;src
)paren
)paren
(brace
id|refspec-&gt;dst
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|fetch-&gt;dst
)paren
op_plus
id|strlen
c_func
(paren
id|refspec-&gt;src
)paren
id|strlen
c_func
(paren
id|fetch-&gt;src
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|refspec-&gt;dst
comma
id|fetch-&gt;dst
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|refspec-&gt;dst
op_plus
id|strlen
c_func
(paren
id|fetch-&gt;dst
)paren
comma
id|refspec-&gt;src
op_plus
id|strlen
c_func
(paren
id|fetch-&gt;src
)paren
)paren
suffix:semicolon
id|refspec-&gt;force
op_assign
id|fetch-&gt;force
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|refspec-&gt;src
comma
id|fetch-&gt;src
)paren
)paren
(brace
id|refspec-&gt;dst
op_assign
id|xstrdup
c_func
(paren
id|fetch-&gt;dst
)paren
suffix:semicolon
id|refspec-&gt;force
op_assign
id|fetch-&gt;force
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|refspec-&gt;dst
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|count_refspec_match
r_static
r_int
id|count_refspec_match
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_struct
id|ref
op_star
id|refs
comma
r_struct
id|ref
op_star
op_star
id|matched_ref
)paren
(brace
r_int
id|patlen
op_assign
id|strlen
c_func
(paren
id|pattern
)paren
suffix:semicolon
r_struct
id|ref
op_star
id|matched_weak
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
id|matched
op_assign
l_int|NULL
suffix:semicolon
r_int
id|weak_match
op_assign
l_int|0
suffix:semicolon
r_int
id|match
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|weak_match
op_assign
id|match
op_assign
l_int|0
suffix:semicolon
id|refs
suffix:semicolon
id|refs
op_assign
id|refs-&gt;next
)paren
(brace
r_char
op_star
id|name
op_assign
id|refs-&gt;name
suffix:semicolon
r_int
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
id|namelen
OL
id|patlen
op_logical_or
id|memcmp
c_func
(paren
id|name
op_plus
id|namelen
id|patlen
comma
id|pattern
comma
id|patlen
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|namelen
op_ne
id|patlen
op_logical_and
id|name
(braket
id|namelen
id|patlen
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
r_continue
suffix:semicolon
multiline_comment|/* A match is &quot;weak&quot; if it is with refs outside&n;&t;&t; * heads or tags, and did not specify the pattern&n;&t;&t; * in full (e.g. &quot;refs/remotes/origin/master&quot;) or at&n;&t;&t; * least from the toplevel (e.g. &quot;remotes/origin/master&quot;);&n;&t;&t; * otherwise &quot;git push $URL master&quot; would result in&n;&t;&t; * ambiguity between remotes/origin/master and heads/master&n;&t;&t; * at the remote site.&n;&t;&t; */
r_if
c_cond
(paren
id|namelen
op_ne
id|patlen
op_logical_and
id|patlen
op_ne
id|namelen
l_int|5
op_logical_and
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/heads/&quot;
)paren
op_logical_and
id|prefixcmp
c_func
(paren
id|name
comma
l_string|&quot;refs/tags/&quot;
)paren
)paren
(brace
multiline_comment|/* We want to catch the case where only weak&n;&t;&t;&t; * matches are found and there are multiple&n;&t;&t;&t; * matches, and where more than one strong&n;&t;&t;&t; * matches are found, as ambiguous.  One&n;&t;&t;&t; * strong match with zero or more weak matches&n;&t;&t;&t; * are acceptable as a unique match.&n;&t;&t;&t; */
id|matched_weak
op_assign
id|refs
suffix:semicolon
id|weak_match
op_increment
suffix:semicolon
)brace
r_else
(brace
id|matched
op_assign
id|refs
suffix:semicolon
id|match
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|matched
)paren
(brace
op_star
id|matched_ref
op_assign
id|matched_weak
suffix:semicolon
r_return
id|weak_match
suffix:semicolon
)brace
r_else
(brace
op_star
id|matched_ref
op_assign
id|matched
suffix:semicolon
r_return
id|match
suffix:semicolon
)brace
)brace
DECL|function|link_dst_tail
r_static
r_void
id|link_dst_tail
c_func
(paren
r_struct
id|ref
op_star
id|ref
comma
r_struct
id|ref
op_star
op_star
op_star
id|tail
)paren
(brace
op_star
op_star
id|tail
op_assign
id|ref
suffix:semicolon
op_star
id|tail
op_assign
op_amp
id|ref-&gt;next
suffix:semicolon
op_star
op_star
id|tail
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|try_explicit_object_name
r_static
r_struct
id|ref
op_star
id|try_explicit_object_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_struct
id|ref
op_star
id|ref
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|name
)paren
(brace
id|ref
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ref
)paren
op_plus
l_int|20
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ref-&gt;name
comma
l_string|&quot;(delete)&quot;
)paren
suffix:semicolon
id|hashclr
c_func
(paren
id|ref-&gt;new_sha1
)paren
suffix:semicolon
r_return
id|ref
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|name
comma
id|sha1
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
id|ref
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|ref
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ref-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|ref-&gt;new_sha1
comma
id|sha1
)paren
suffix:semicolon
r_return
id|ref
suffix:semicolon
)brace
DECL|function|make_dst
r_static
r_struct
id|ref
op_star
id|make_dst
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|ref
op_star
op_star
op_star
id|dst_tail
)paren
(brace
r_struct
id|ref
op_star
id|dst
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
id|dst
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|dst
)paren
op_plus
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dst-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|link_dst_tail
c_func
(paren
id|dst
comma
id|dst_tail
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
DECL|function|match_explicit
r_static
r_int
id|match_explicit
c_func
(paren
r_struct
id|ref
op_star
id|src
comma
r_struct
id|ref
op_star
id|dst
comma
r_struct
id|ref
op_star
op_star
op_star
id|dst_tail
comma
r_struct
id|refspec
op_star
id|rs
comma
r_int
id|errs
)paren
(brace
r_struct
id|ref
op_star
id|matched_src
comma
op_star
id|matched_dst
suffix:semicolon
r_const
r_char
op_star
id|dst_value
op_assign
id|rs-&gt;dst
suffix:semicolon
r_if
c_cond
(paren
id|rs-&gt;pattern
)paren
r_return
id|errs
suffix:semicolon
id|matched_src
op_assign
id|matched_dst
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|count_refspec_match
c_func
(paren
id|rs-&gt;src
comma
id|src
comma
op_amp
id|matched_src
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* The source could be in the get_sha1() format&n;&t;&t; * not a reference name.  :refs/other is a&n;&t;&t; * way to delete &squot;other&squot; ref at the remote end.&n;&t;&t; */
id|matched_src
op_assign
id|try_explicit_object_name
c_func
(paren
id|rs-&gt;src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|matched_src
)paren
r_break
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;src refspec %s does not match any.&quot;
comma
id|rs-&gt;src
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|matched_src
op_assign
l_int|NULL
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;src refspec %s matches more than one.&quot;
comma
id|rs-&gt;src
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|matched_src
)paren
id|errs
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dst_value
op_eq
l_int|NULL
)paren
id|dst_value
op_assign
id|matched_src-&gt;name
suffix:semicolon
r_switch
c_cond
(paren
id|count_refspec_match
c_func
(paren
id|dst_value
comma
id|dst
comma
op_amp
id|matched_dst
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|dst_value
comma
l_string|&quot;refs/&quot;
comma
l_int|5
)paren
)paren
id|matched_dst
op_assign
id|make_dst
c_func
(paren
id|dst_value
comma
id|dst_tail
)paren
suffix:semicolon
r_else
id|error
c_func
(paren
l_string|&quot;dst refspec %s does not match any &quot;
l_string|&quot;existing ref on the remote and does &quot;
l_string|&quot;not start with refs/.&quot;
comma
id|dst_value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|matched_dst
op_assign
l_int|NULL
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;dst refspec %s matches more than one.&quot;
comma
id|dst_value
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|errs
op_logical_or
id|matched_dst
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|matched_dst-&gt;peer_ref
)paren
(brace
id|errs
op_assign
l_int|1
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;dst ref %s receives from more than one src.&quot;
comma
id|matched_dst-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|matched_dst-&gt;peer_ref
op_assign
id|matched_src
suffix:semicolon
id|matched_dst-&gt;force
op_assign
id|rs-&gt;force
suffix:semicolon
)brace
r_return
id|errs
suffix:semicolon
)brace
DECL|function|match_explicit_refs
r_static
r_int
id|match_explicit_refs
c_func
(paren
r_struct
id|ref
op_star
id|src
comma
r_struct
id|ref
op_star
id|dst
comma
r_struct
id|ref
op_star
op_star
op_star
id|dst_tail
comma
r_struct
id|refspec
op_star
id|rs
comma
r_int
id|rs_nr
)paren
(brace
r_int
id|i
comma
id|errs
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|errs
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|rs_nr
suffix:semicolon
id|i
op_increment
)paren
id|errs
op_or_assign
id|match_explicit
c_func
(paren
id|src
comma
id|dst
comma
id|dst_tail
comma
op_amp
id|rs
(braket
id|i
)braket
comma
id|errs
)paren
suffix:semicolon
r_return
id|errs
suffix:semicolon
)brace
DECL|function|find_ref_by_name
r_static
r_struct
id|ref
op_star
id|find_ref_by_name
c_func
(paren
r_struct
id|ref
op_star
id|list
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|list-&gt;name
comma
id|name
)paren
)paren
r_return
id|list
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|check_pattern_match
r_static
r_const
r_struct
id|refspec
op_star
id|check_pattern_match
c_func
(paren
r_const
r_struct
id|refspec
op_star
id|rs
comma
r_int
id|rs_nr
comma
r_const
r_struct
id|ref
op_star
id|src
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
id|rs_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|rs
(braket
id|i
)braket
dot
id|pattern
op_logical_and
op_logical_neg
id|prefixcmp
c_func
(paren
id|src-&gt;name
comma
id|rs
(braket
id|i
)braket
dot
id|src
)paren
)paren
r_return
id|rs
op_plus
id|i
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Note. This is used only by &quot;push&quot;; refspec matching rules for&n; * push and fetch are subtly different, so do not try to reuse it&n; * without thinking.&n; */
DECL|function|match_refs
r_int
id|match_refs
c_func
(paren
r_struct
id|ref
op_star
id|src
comma
r_struct
id|ref
op_star
id|dst
comma
r_struct
id|ref
op_star
op_star
op_star
id|dst_tail
comma
r_int
id|nr_refspec
comma
r_char
op_star
op_star
id|refspec
comma
r_int
id|all
)paren
(brace
r_struct
id|refspec
op_star
id|rs
op_assign
id|parse_ref_spec
c_func
(paren
id|nr_refspec
comma
(paren
r_const
r_char
op_star
op_star
)paren
id|refspec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_explicit_refs
c_func
(paren
id|src
comma
id|dst
comma
id|dst_tail
comma
id|rs
comma
id|nr_refspec
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* pick the remainder */
r_for
c_loop
(paren
suffix:semicolon
id|src
suffix:semicolon
id|src
op_assign
id|src-&gt;next
)paren
(brace
r_struct
id|ref
op_star
id|dst_peer
suffix:semicolon
r_const
r_struct
id|refspec
op_star
id|pat
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|dst_name
suffix:semicolon
r_if
c_cond
(paren
id|src-&gt;peer_ref
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|nr_refspec
)paren
(brace
id|pat
op_assign
id|check_pattern_match
c_func
(paren
id|rs
comma
id|nr_refspec
comma
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pat
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pat
)paren
(brace
r_const
r_char
op_star
id|dst_side
op_assign
id|pat-&gt;dst
ques
c_cond
id|pat-&gt;dst
suffix:colon
id|pat-&gt;src
suffix:semicolon
id|dst_name
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|dst_side
)paren
op_plus
id|strlen
c_func
(paren
id|src-&gt;name
)paren
id|strlen
c_func
(paren
id|pat-&gt;src
)paren
op_plus
l_int|2
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|dst_name
comma
id|dst_side
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|dst_name
comma
id|src-&gt;name
op_plus
id|strlen
c_func
(paren
id|pat-&gt;src
)paren
)paren
suffix:semicolon
)brace
r_else
id|dst_name
op_assign
id|xstrdup
c_func
(paren
id|src-&gt;name
)paren
suffix:semicolon
id|dst_peer
op_assign
id|find_ref_by_name
c_func
(paren
id|dst
comma
id|dst_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst_peer
op_logical_and
id|dst_peer-&gt;peer_ref
)paren
multiline_comment|/* We&squot;re already sending something to this ref. */
r_goto
id|free_name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_peer
op_logical_and
op_logical_neg
id|nr_refspec
op_logical_and
op_logical_neg
id|all
)paren
multiline_comment|/* Remote doesn&squot;t have it, and we have no&n;&t;&t;&t; * explicit pattern, and we don&squot;t have&n;&t;&t;&t; * --all. */
r_goto
id|free_name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_peer
)paren
(brace
multiline_comment|/* Create a new one and link it */
id|dst_peer
op_assign
id|make_dst
c_func
(paren
id|dst_name
comma
id|dst_tail
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|dst_peer-&gt;new_sha1
comma
id|src-&gt;new_sha1
)paren
suffix:semicolon
)brace
id|dst_peer-&gt;peer_ref
op_assign
id|src
suffix:semicolon
id|free_name
suffix:colon
id|free
c_func
(paren
id|dst_name
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
