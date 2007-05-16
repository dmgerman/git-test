multiline_comment|/*&n; * &quot;git push&quot;&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;remote.h&quot;
DECL|variable|push_usage
r_static
r_const
r_char
id|push_usage
(braket
)braket
op_assign
l_string|&quot;git-push [--all] [--tags] [--receive-pack=&lt;git-receive-pack&gt;] [--repo=all] [-f | --force] [-v] [&lt;repository&gt; &lt;refspec&gt;...]&quot;
suffix:semicolon
DECL|variable|all
DECL|variable|tags
DECL|variable|force
DECL|variable|thin
DECL|variable|verbose
r_static
r_int
id|all
comma
id|tags
comma
id|force
comma
id|thin
op_assign
l_int|1
comma
id|verbose
suffix:semicolon
DECL|variable|receivepack
r_static
r_const
r_char
op_star
id|receivepack
suffix:semicolon
DECL|variable|refspec
r_static
r_const
r_char
op_star
op_star
id|refspec
suffix:semicolon
DECL|variable|refspec_nr
r_static
r_int
id|refspec_nr
suffix:semicolon
DECL|function|add_refspec
r_static
r_void
id|add_refspec
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
id|nr
op_assign
id|refspec_nr
op_plus
l_int|1
suffix:semicolon
id|refspec
op_assign
id|xrealloc
c_func
(paren
id|refspec
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
id|refspec
(braket
id|nr
op_minus
l_int|1
)braket
op_assign
id|ref
suffix:semicolon
id|refspec_nr
op_assign
id|nr
suffix:semicolon
)brace
DECL|function|expand_one_ref
r_static
r_int
id|expand_one_ref
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
multiline_comment|/* Ignore the &quot;refs/&quot; at the beginning of the refname */
id|ref
op_add_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|ref
comma
l_string|&quot;tags/&quot;
)paren
)paren
id|add_refspec
c_func
(paren
id|xstrdup
c_func
(paren
id|ref
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|expand_refspecs
r_static
r_void
id|expand_refspecs
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|all
)paren
(brace
r_if
c_cond
(paren
id|refspec_nr
)paren
id|die
c_func
(paren
l_string|&quot;cannot mix &squot;--all&squot; and a refspec&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * No need to expand &quot;--all&quot; - we&squot;ll just use&n;&t;&t; * the &quot;--all&quot; flag to send-pack&n;&t;&t; */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tags
)paren
r_return
suffix:semicolon
id|for_each_ref
c_func
(paren
id|expand_one_ref
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|struct|wildcard_cb
r_struct
id|wildcard_cb
(brace
DECL|member|from_prefix
r_const
r_char
op_star
id|from_prefix
suffix:semicolon
DECL|member|from_prefix_len
r_int
id|from_prefix_len
suffix:semicolon
DECL|member|to_prefix
r_const
r_char
op_star
id|to_prefix
suffix:semicolon
DECL|member|to_prefix_len
r_int
id|to_prefix_len
suffix:semicolon
DECL|member|force
r_int
id|force
suffix:semicolon
)brace
suffix:semicolon
DECL|function|expand_wildcard_ref
r_static
r_int
id|expand_wildcard_ref
c_func
(paren
r_const
r_char
op_star
id|ref
comma
r_const
r_int
r_char
op_star
id|sha1
comma
r_int
id|flag
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|wildcard_cb
op_star
id|cb
op_assign
id|cb_data
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|ref
)paren
suffix:semicolon
r_char
op_star
id|expanded
comma
op_star
id|newref
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|cb-&gt;from_prefix_len
op_logical_or
id|memcmp
c_func
(paren
id|cb-&gt;from_prefix
comma
id|ref
comma
id|cb-&gt;from_prefix_len
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|expanded
op_assign
id|xmalloc
c_func
(paren
id|len
op_star
l_int|2
op_plus
id|cb-&gt;force
op_plus
(paren
id|cb-&gt;to_prefix_len
id|cb-&gt;from_prefix_len
)paren
op_plus
l_int|2
)paren
suffix:semicolon
id|newref
op_assign
id|expanded
op_plus
id|cb-&gt;force
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;force
)paren
id|expanded
(braket
l_int|0
)braket
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|newref
comma
id|ref
comma
id|len
)paren
suffix:semicolon
id|newref
(braket
id|len
)braket
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|newref
op_plus
id|len
op_plus
l_int|1
comma
id|cb-&gt;to_prefix
comma
id|cb-&gt;to_prefix_len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|newref
op_plus
id|len
op_plus
l_int|1
op_plus
id|cb-&gt;to_prefix_len
comma
id|ref
op_plus
id|cb-&gt;from_prefix_len
)paren
suffix:semicolon
id|add_refspec
c_func
(paren
id|expanded
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wildcard_ref
r_static
r_int
id|wildcard_ref
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|colon
suffix:semicolon
r_struct
id|wildcard_cb
id|cb
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cb
comma
l_int|0
comma
r_sizeof
(paren
id|cb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ref
(braket
l_int|0
)braket
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|cb.force
op_assign
l_int|1
suffix:semicolon
id|ref
op_increment
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|ref
)paren
suffix:semicolon
id|colon
op_assign
id|strchr
c_func
(paren
id|ref
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|colon
op_logical_and
id|ref
OL
id|colon
op_logical_and
id|colon
(braket
l_int|2
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
id|colon
(braket
l_int|1
)braket
op_eq
l_char|&squot;*&squot;
op_logical_and
multiline_comment|/* &quot;&lt;mine&gt;/&lt;asterisk&gt;:&lt;yours&gt;/&lt;asterisk&gt;&quot; is at least 7 bytes */
l_int|7
op_le
id|len
op_logical_and
id|ref
(braket
id|len
op_minus
l_int|2
)braket
op_eq
l_char|&squot;/&squot;
op_logical_and
id|ref
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;*&squot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|cb.from_prefix
op_assign
id|ref
suffix:semicolon
id|cb.from_prefix_len
op_assign
id|colon
id|ref
l_int|1
suffix:semicolon
id|cb.to_prefix
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
id|cb.to_prefix_len
op_assign
id|len
(paren
id|colon
id|ref
)paren
l_int|2
suffix:semicolon
id|for_each_ref
c_func
(paren
id|expand_wildcard_ref
comma
op_amp
id|cb
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|set_refspecs
r_static
r_void
id|set_refspecs
c_func
(paren
r_const
r_char
op_star
op_star
id|refs
comma
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|nr
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|ref
op_assign
id|refs
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;tag&quot;
comma
id|ref
)paren
)paren
(brace
r_char
op_star
id|tag
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_le
op_increment
id|i
)paren
id|die
c_func
(paren
l_string|&quot;tag shorthand without &lt;tag&gt;&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|refs
(braket
id|i
)braket
)paren
op_plus
l_int|11
suffix:semicolon
id|tag
op_assign
id|xmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tag
comma
l_string|&quot;refs/tags/&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|tag
comma
id|refs
(braket
id|i
)braket
)paren
suffix:semicolon
id|ref
op_assign
id|tag
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|wildcard_ref
c_func
(paren
id|ref
)paren
)paren
r_continue
suffix:semicolon
id|add_refspec
c_func
(paren
id|ref
)paren
suffix:semicolon
)brace
)brace
id|expand_refspecs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_push
r_static
r_int
id|do_push
c_func
(paren
r_const
r_char
op_star
id|repo
)paren
(brace
r_int
id|i
comma
id|errs
suffix:semicolon
r_int
id|common_argc
suffix:semicolon
r_const
r_char
op_star
op_star
id|argv
suffix:semicolon
r_int
id|argc
suffix:semicolon
r_struct
id|remote
op_star
id|remote
op_assign
id|remote_get
c_func
(paren
id|repo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|remote
)paren
id|die
c_func
(paren
l_string|&quot;bad repository &squot;%s&squot;&quot;
comma
id|repo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remote-&gt;receivepack
)paren
(brace
r_char
op_star
id|rp
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|remote-&gt;receivepack
)paren
op_plus
l_int|16
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|rp
comma
l_string|&quot;--receive-pack=%s&quot;
comma
id|remote-&gt;receivepack
)paren
suffix:semicolon
id|receivepack
op_assign
id|rp
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|refspec
op_logical_and
op_logical_neg
id|all
op_logical_and
op_logical_neg
id|tags
op_logical_and
id|remote-&gt;push_refspec_nr
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|remote-&gt;push_refspec_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|wildcard_ref
c_func
(paren
id|remote-&gt;push_refspec
(braket
id|i
)braket
)paren
)paren
id|add_refspec
c_func
(paren
id|remote-&gt;push_refspec
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|argv
op_assign
id|xmalloc
c_func
(paren
(paren
id|refspec_nr
op_plus
l_int|10
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
l_string|&quot;dummy-send-pack&quot;
suffix:semicolon
id|argc
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|all
)paren
id|argv
(braket
id|argc
op_increment
)braket
op_assign
l_string|&quot;--all&quot;
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
id|argv
(braket
id|argc
op_increment
)braket
op_assign
l_string|&quot;--force&quot;
suffix:semicolon
r_if
c_cond
(paren
id|receivepack
)paren
id|argv
(braket
id|argc
op_increment
)braket
op_assign
id|receivepack
suffix:semicolon
id|common_argc
op_assign
id|argc
suffix:semicolon
id|errs
op_assign
l_int|0
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
r_int
id|err
suffix:semicolon
r_int
id|dest_argc
op_assign
id|common_argc
suffix:semicolon
r_int
id|dest_refspec_nr
op_assign
id|refspec_nr
suffix:semicolon
r_const
r_char
op_star
op_star
id|dest_refspec
op_assign
id|refspec
suffix:semicolon
r_const
r_char
op_star
id|dest
op_assign
id|remote-&gt;uri
(braket
id|i
)braket
suffix:semicolon
r_const
r_char
op_star
id|sender
op_assign
l_string|&quot;send-pack&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|dest
comma
l_string|&quot;http://&quot;
)paren
op_logical_or
op_logical_neg
id|prefixcmp
c_func
(paren
id|dest
comma
l_string|&quot;https://&quot;
)paren
)paren
id|sender
op_assign
l_string|&quot;http-push&quot;
suffix:semicolon
r_else
(brace
r_char
op_star
id|rem
op_assign
id|xmalloc
c_func
(paren
id|strlen
c_func
(paren
id|remote-&gt;name
)paren
op_plus
l_int|10
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|rem
comma
l_string|&quot;--remote=%s&quot;
comma
id|remote-&gt;name
)paren
suffix:semicolon
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
id|rem
suffix:semicolon
r_if
c_cond
(paren
id|thin
)paren
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
l_string|&quot;--thin&quot;
suffix:semicolon
)brace
id|argv
(braket
l_int|0
)braket
op_assign
id|sender
suffix:semicolon
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
id|dest
suffix:semicolon
r_while
c_loop
(paren
id|dest_refspec_nr
op_decrement
)paren
id|argv
(braket
id|dest_argc
op_increment
)braket
op_assign
op_star
id|dest_refspec
op_increment
suffix:semicolon
id|argv
(braket
id|dest_argc
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Pushing to %s&bslash;n&quot;
comma
id|dest
)paren
suffix:semicolon
id|err
op_assign
id|run_command_v_opt
c_func
(paren
id|argv
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_continue
suffix:semicolon
id|error
c_func
(paren
l_string|&quot;failed to push to &squot;%s&squot;&quot;
comma
id|remote-&gt;uri
(braket
id|i
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|err
)paren
(brace
r_case
id|ERR_RUN_COMMAND_FORK
suffix:colon
id|error
c_func
(paren
l_string|&quot;unable to fork for %s&quot;
comma
id|sender
)paren
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_EXEC
suffix:colon
id|error
c_func
(paren
l_string|&quot;unable to exec %s&quot;
comma
id|sender
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ERR_RUN_COMMAND_WAITPID
suffix:colon
r_case
id|ERR_RUN_COMMAND_WAITPID_WRONG_PID
suffix:colon
r_case
id|ERR_RUN_COMMAND_WAITPID_SIGNAL
suffix:colon
r_case
id|ERR_RUN_COMMAND_WAITPID_NOEXIT
suffix:colon
id|error
c_func
(paren
l_string|&quot;%s died with strange error&quot;
comma
id|sender
)paren
suffix:semicolon
)brace
id|errs
op_increment
suffix:semicolon
)brace
r_return
op_logical_neg
op_logical_neg
id|errs
suffix:semicolon
)brace
DECL|function|cmd_push
r_int
id|cmd_push
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
id|i
suffix:semicolon
r_const
r_char
op_star
id|repo
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* default repository */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
)paren
(brace
id|repo
op_assign
id|arg
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-v&quot;
)paren
)paren
(brace
id|verbose
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--repo=&quot;
)paren
)paren
(brace
id|repo
op_assign
id|arg
op_plus
l_int|7
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--all&quot;
)paren
)paren
(brace
id|all
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--tags&quot;
)paren
)paren
(brace
id|tags
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--force&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-f&quot;
)paren
)paren
(brace
id|force
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--thin&quot;
)paren
)paren
(brace
id|thin
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--no-thin&quot;
)paren
)paren
(brace
id|thin
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--receive-pack=&quot;
)paren
)paren
(brace
id|receivepack
op_assign
id|arg
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|arg
comma
l_string|&quot;--exec=&quot;
)paren
)paren
(brace
id|receivepack
op_assign
id|arg
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|usage
c_func
(paren
id|push_usage
)paren
suffix:semicolon
)brace
id|set_refspecs
c_func
(paren
id|argv
op_plus
id|i
comma
id|argc
id|i
)paren
suffix:semicolon
r_return
id|do_push
c_func
(paren
id|repo
)paren
suffix:semicolon
)brace
eof
