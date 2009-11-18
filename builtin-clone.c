multiline_comment|/*&n; * Builtin &quot;git clone&quot;&n; *&n; * Copyright (c) 2007 Kristian H&oslash;gsberg &lt;krh@redhat.com&gt;,&n; *&t;&t; 2008 Daniel Barkalow &lt;barkalow@iabervon.org&gt;&n; * Based on git-commit.sh by Junio C Hamano and Linus Torvalds&n; *&n; * Clone a repository into a different directory that does not yet exist.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;fetch-pack.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
macro_line|#include &quot;unpack-trees.h&quot;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;pack-refs.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#include &quot;branch.h&quot;
macro_line|#include &quot;remote.h&quot;
macro_line|#include &quot;run-command.h&quot;
multiline_comment|/*&n; * Overall FIXMEs:&n; *  - respect DB_ENVIRONMENT for .git/objects.&n; *&n; * Implementation notes:&n; *  - dropping use-separate-remote and no-separate-remote compatibility&n; *&n; */
DECL|variable|builtin_clone_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_clone_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git clone [options] [--] &lt;repo&gt; [&lt;dir&gt;]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|option_quiet
DECL|variable|option_no_checkout
DECL|variable|option_bare
DECL|variable|option_mirror
r_static
r_int
id|option_quiet
comma
id|option_no_checkout
comma
id|option_bare
comma
id|option_mirror
suffix:semicolon
DECL|variable|option_local
DECL|variable|option_no_hardlinks
DECL|variable|option_shared
DECL|variable|option_recursive
r_static
r_int
id|option_local
comma
id|option_no_hardlinks
comma
id|option_shared
comma
id|option_recursive
suffix:semicolon
DECL|variable|option_template
DECL|variable|option_reference
DECL|variable|option_depth
r_static
r_char
op_star
id|option_template
comma
op_star
id|option_reference
comma
op_star
id|option_depth
suffix:semicolon
DECL|variable|option_origin
r_static
r_char
op_star
id|option_origin
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|option_branch
r_static
r_char
op_star
id|option_branch
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|option_upload_pack
r_static
r_char
op_star
id|option_upload_pack
op_assign
l_string|&quot;git-upload-pack&quot;
suffix:semicolon
DECL|variable|option_verbose
r_static
r_int
id|option_verbose
suffix:semicolon
DECL|variable|builtin_clone_options
r_static
r_struct
id|option
id|builtin_clone_options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|option_quiet
)paren
comma
id|OPT__VERBOSE
c_func
(paren
op_amp
id|option_verbose
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;n&squot;
comma
l_string|&quot;no-checkout&quot;
comma
op_amp
id|option_no_checkout
comma
l_string|&quot;don&squot;t create a checkout&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;bare&quot;
comma
op_amp
id|option_bare
comma
l_string|&quot;create a bare repository&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;naked&quot;
comma
op_amp
id|option_bare
comma
l_string|&quot;create a bare repository&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;mirror&quot;
comma
op_amp
id|option_mirror
comma
l_string|&quot;create a mirror repository (implies bare)&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;l&squot;
comma
l_string|&quot;local&quot;
comma
op_amp
id|option_local
comma
l_string|&quot;to clone from a local repository&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;no-hardlinks&quot;
comma
op_amp
id|option_no_hardlinks
comma
l_string|&quot;don&squot;t use local hardlinks, always copy&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;s&squot;
comma
l_string|&quot;shared&quot;
comma
op_amp
id|option_shared
comma
l_string|&quot;setup as shared repository&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;recursive&quot;
comma
op_amp
id|option_recursive
comma
l_string|&quot;setup as shared repository&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;template&quot;
comma
op_amp
id|option_template
comma
l_string|&quot;path&quot;
comma
l_string|&quot;path the template repository&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;reference&quot;
comma
op_amp
id|option_reference
comma
l_string|&quot;repo&quot;
comma
l_string|&quot;reference repository&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;o&squot;
comma
l_string|&quot;origin&quot;
comma
op_amp
id|option_origin
comma
l_string|&quot;branch&quot;
comma
l_string|&quot;use &lt;branch&gt; instead of &squot;origin&squot; to track upstream&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;b&squot;
comma
l_string|&quot;branch&quot;
comma
op_amp
id|option_branch
comma
l_string|&quot;branch&quot;
comma
l_string|&quot;checkout &lt;branch&gt; instead of the remote&squot;s HEAD&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_char|&squot;u&squot;
comma
l_string|&quot;upload-pack&quot;
comma
op_amp
id|option_upload_pack
comma
l_string|&quot;path&quot;
comma
l_string|&quot;path to git-upload-pack on the remote&quot;
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;depth&quot;
comma
op_amp
id|option_depth
comma
l_string|&quot;depth&quot;
comma
l_string|&quot;create a shallow clone of that depth&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
DECL|variable|argv_submodule
r_static
r_const
r_char
op_star
id|argv_submodule
(braket
)braket
op_assign
(brace
l_string|&quot;submodule&quot;
comma
l_string|&quot;update&quot;
comma
l_string|&quot;--init&quot;
comma
l_string|&quot;--recursive&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|get_repo_path
r_static
r_char
op_star
id|get_repo_path
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_int
op_star
id|is_bundle
)paren
(brace
r_static
r_char
op_star
id|suffix
(braket
)braket
op_assign
(brace
l_string|&quot;/.git&quot;
comma
l_string|&quot;.git&quot;
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|bundle_suffix
(braket
)braket
op_assign
(brace
l_string|&quot;.bundle&quot;
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
r_struct
id|stat
id|st
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
id|suffix
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
id|path
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|repo
comma
id|suffix
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_directory
c_func
(paren
id|path
)paren
)paren
(brace
op_star
id|is_bundle
op_assign
l_int|0
suffix:semicolon
r_return
id|xstrdup
c_func
(paren
id|make_nonrelative_path
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
)brace
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
id|bundle_suffix
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|path
suffix:semicolon
id|path
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|repo
comma
id|bundle_suffix
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|path
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
op_star
id|is_bundle
op_assign
l_int|1
suffix:semicolon
r_return
id|xstrdup
c_func
(paren
id|make_nonrelative_path
c_func
(paren
id|path
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|guess_dir_name
r_static
r_char
op_star
id|guess_dir_name
c_func
(paren
r_const
r_char
op_star
id|repo
comma
r_int
id|is_bundle
comma
r_int
id|is_bare
)paren
(brace
r_const
r_char
op_star
id|end
op_assign
id|repo
op_plus
id|strlen
c_func
(paren
id|repo
)paren
comma
op_star
id|start
suffix:semicolon
r_char
op_star
id|dir
suffix:semicolon
multiline_comment|/*&n;&t; * Strip trailing spaces, slashes and /.git&n;&t; */
r_while
c_loop
(paren
id|repo
OL
id|end
op_logical_and
(paren
id|is_dir_sep
c_func
(paren
id|end
(braket
l_int|1
)braket
)paren
op_logical_or
id|isspace
c_func
(paren
id|end
(braket
l_int|1
)braket
)paren
)paren
)paren
id|end
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|end
id|repo
OG
l_int|5
op_logical_and
id|is_dir_sep
c_func
(paren
id|end
(braket
l_int|5
)braket
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|end
l_int|4
comma
l_string|&quot;.git&quot;
comma
l_int|4
)paren
)paren
(brace
id|end
op_sub_assign
l_int|5
suffix:semicolon
r_while
c_loop
(paren
id|repo
OL
id|end
op_logical_and
id|is_dir_sep
c_func
(paren
id|end
(braket
l_int|1
)braket
)paren
)paren
id|end
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Find last component, but be prepared that repo could have&n;&t; * the form  &quot;remote.example.com:foo.git&quot;, i.e. no slash&n;&t; * in the directory part.&n;&t; */
id|start
op_assign
id|end
suffix:semicolon
r_while
c_loop
(paren
id|repo
OL
id|start
op_logical_and
op_logical_neg
id|is_dir_sep
c_func
(paren
id|start
(braket
l_int|1
)braket
)paren
op_logical_and
id|start
(braket
l_int|1
)braket
op_ne
l_char|&squot;:&squot;
)paren
id|start
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t; * Strip .{bundle,git}.&n;&t; */
r_if
c_cond
(paren
id|is_bundle
)paren
(brace
r_if
c_cond
(paren
id|end
id|start
OG
l_int|7
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|end
l_int|7
comma
l_string|&quot;.bundle&quot;
comma
l_int|7
)paren
)paren
id|end
op_sub_assign
l_int|7
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|end
id|start
OG
l_int|4
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|end
l_int|4
comma
l_string|&quot;.git&quot;
comma
l_int|4
)paren
)paren
id|end
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_bare
)paren
(brace
r_struct
id|strbuf
id|result
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|result
comma
l_string|&quot;%.*s.git&quot;
comma
(paren
r_int
)paren
(paren
id|end
id|start
)paren
comma
id|start
)paren
suffix:semicolon
id|dir
op_assign
id|strbuf_detach
c_func
(paren
op_amp
id|result
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|dir
op_assign
id|xstrndup
c_func
(paren
id|start
comma
id|end
id|start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Replace sequences of &squot;control&squot; characters and whitespace&n;&t; * with one ascii space, remove leading and trailing spaces.&n;&t; */
r_if
c_cond
(paren
op_star
id|dir
)paren
(brace
r_char
op_star
id|out
op_assign
id|dir
suffix:semicolon
r_int
id|prev_space
op_assign
l_int|1
multiline_comment|/* strip leading whitespace */
suffix:semicolon
r_for
c_loop
(paren
id|end
op_assign
id|dir
suffix:semicolon
op_star
id|end
suffix:semicolon
op_increment
id|end
)paren
(brace
r_char
id|ch
op_assign
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
id|ch
OL
l_char|&squot;&bslash;x20&squot;
)paren
id|ch
op_assign
l_char|&squot;&bslash;x20&squot;
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|ch
)paren
)paren
(brace
r_if
c_cond
(paren
id|prev_space
)paren
r_continue
suffix:semicolon
id|prev_space
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|prev_space
op_assign
l_int|0
suffix:semicolon
op_star
id|out
op_increment
op_assign
id|ch
suffix:semicolon
)brace
op_star
id|out
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|out
OG
id|dir
op_logical_and
id|prev_space
)paren
id|out
(braket
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_return
id|dir
suffix:semicolon
)brace
DECL|function|strip_trailing_slashes
r_static
r_void
id|strip_trailing_slashes
c_func
(paren
r_char
op_star
id|dir
)paren
(brace
r_char
op_star
id|end
op_assign
id|dir
op_plus
id|strlen
c_func
(paren
id|dir
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dir
OL
id|end
l_int|1
op_logical_and
id|is_dir_sep
c_func
(paren
id|end
(braket
l_int|1
)braket
)paren
)paren
id|end
op_decrement
suffix:semicolon
op_star
id|end
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|setup_reference
r_static
r_void
id|setup_reference
c_func
(paren
r_const
r_char
op_star
id|repo
)paren
(brace
r_const
r_char
op_star
id|ref_git
suffix:semicolon
r_char
op_star
id|ref_git_copy
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|extra
suffix:semicolon
id|ref_git
op_assign
id|make_absolute_path
c_func
(paren
id|option_reference
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_directory
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/.git/objects&quot;
comma
id|ref_git
)paren
)paren
)paren
id|ref_git
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s/.git&quot;
comma
id|ref_git
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|is_directory
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/objects&quot;
comma
id|ref_git
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;reference repository &squot;%s&squot; is not a local directory.&quot;
comma
id|option_reference
)paren
suffix:semicolon
id|ref_git_copy
op_assign
id|xstrdup
c_func
(paren
id|ref_git
)paren
suffix:semicolon
id|add_to_alternates_file
c_func
(paren
id|ref_git_copy
)paren
suffix:semicolon
id|remote
op_assign
id|remote_get
c_func
(paren
id|ref_git_copy
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|ref_git_copy
)paren
suffix:semicolon
r_for
c_loop
(paren
id|extra
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
id|extra
suffix:semicolon
id|extra
op_assign
id|extra-&gt;next
)paren
id|add_extra_ref
c_func
(paren
id|extra-&gt;name
comma
id|extra-&gt;old_sha1
comma
l_int|0
)paren
suffix:semicolon
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
id|free
c_func
(paren
id|ref_git_copy
)paren
suffix:semicolon
)brace
DECL|function|copy_or_link_directory
r_static
r_void
id|copy_or_link_directory
c_func
(paren
r_struct
id|strbuf
op_star
id|src
comma
r_struct
id|strbuf
op_star
id|dest
)paren
(brace
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_struct
id|stat
id|buf
suffix:semicolon
r_int
id|src_len
comma
id|dest_len
suffix:semicolon
id|DIR
op_star
id|dir
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|src-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to open &squot;%s&squot;&quot;
comma
id|src-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|dest-&gt;buf
comma
l_int|0777
)paren
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to create directory &squot;%s&squot;&quot;
comma
id|dest-&gt;buf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|stat
c_func
(paren
id|dest-&gt;buf
comma
op_amp
id|buf
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to stat &squot;%s&squot;&quot;
comma
id|dest-&gt;buf
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|buf.st_mode
)paren
)paren
id|die
c_func
(paren
l_string|&quot;%s exists and is not a directory&quot;
comma
id|dest-&gt;buf
)paren
suffix:semicolon
)brace
id|strbuf_addch
c_func
(paren
id|src
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|src_len
op_assign
id|src-&gt;len
suffix:semicolon
id|strbuf_addch
c_func
(paren
id|dest
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|dest_len
op_assign
id|dest-&gt;len
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|strbuf_setlen
c_func
(paren
id|src
comma
id|src_len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|src
comma
id|de-&gt;d_name
)paren
suffix:semicolon
id|strbuf_setlen
c_func
(paren
id|dest
comma
id|dest_len
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|dest
comma
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|src-&gt;buf
comma
op_amp
id|buf
)paren
)paren
(brace
id|warning
(paren
l_string|&quot;failed to stat %s&bslash;n&quot;
comma
id|src-&gt;buf
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;d_name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
id|copy_or_link_directory
c_func
(paren
id|src
comma
id|dest
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|dest-&gt;buf
)paren
op_logical_and
id|errno
op_ne
id|ENOENT
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to unlink &squot;%s&squot;&quot;
comma
id|dest-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option_no_hardlinks
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|link
c_func
(paren
id|src-&gt;buf
comma
id|dest-&gt;buf
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|option_local
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to create link &squot;%s&squot;&quot;
comma
id|dest-&gt;buf
)paren
suffix:semicolon
id|option_no_hardlinks
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_file_with_time
c_func
(paren
id|dest-&gt;buf
comma
id|src-&gt;buf
comma
l_int|0666
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;failed to copy file to &squot;%s&squot;&quot;
comma
id|dest-&gt;buf
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
DECL|function|clone_local
r_static
r_const
r_struct
id|ref
op_star
id|clone_local
c_func
(paren
r_const
r_char
op_star
id|src_repo
comma
r_const
r_char
op_star
id|dest_repo
)paren
(brace
r_const
r_struct
id|ref
op_star
id|ret
suffix:semicolon
r_struct
id|strbuf
id|src
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|dest
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|remote
op_star
id|remote
suffix:semicolon
r_struct
id|transport
op_star
id|transport
suffix:semicolon
r_if
c_cond
(paren
id|option_shared
)paren
id|add_to_alternates_file
c_func
(paren
id|src_repo
)paren
suffix:semicolon
r_else
(brace
id|strbuf_addf
c_func
(paren
op_amp
id|src
comma
l_string|&quot;%s/objects&quot;
comma
id|src_repo
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|dest
comma
l_string|&quot;%s/objects&quot;
comma
id|dest_repo
)paren
suffix:semicolon
id|copy_or_link_directory
c_func
(paren
op_amp
id|src
comma
op_amp
id|dest
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|src
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|dest
)paren
suffix:semicolon
)brace
id|remote
op_assign
id|remote_get
c_func
(paren
id|src_repo
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|src_repo
)paren
suffix:semicolon
id|ret
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|junk_work_tree
r_static
r_const
r_char
op_star
id|junk_work_tree
suffix:semicolon
DECL|variable|junk_git_dir
r_static
r_const
r_char
op_star
id|junk_git_dir
suffix:semicolon
DECL|variable|junk_pid
r_static
id|pid_t
id|junk_pid
suffix:semicolon
DECL|function|remove_junk
r_static
r_void
id|remove_junk
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
id|getpid
c_func
(paren
)paren
op_ne
id|junk_pid
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|junk_git_dir
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|junk_git_dir
)paren
suffix:semicolon
id|remove_dir_recursively
c_func
(paren
op_amp
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|junk_work_tree
)paren
(brace
id|strbuf_addstr
c_func
(paren
op_amp
id|sb
comma
id|junk_work_tree
)paren
suffix:semicolon
id|remove_dir_recursively
c_func
(paren
op_amp
id|sb
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
)brace
)brace
DECL|function|remove_junk_on_signal
r_static
r_void
id|remove_junk_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_junk
c_func
(paren
)paren
suffix:semicolon
id|sigchain_pop
c_func
(paren
id|signo
)paren
suffix:semicolon
id|raise
c_func
(paren
id|signo
)paren
suffix:semicolon
)brace
DECL|function|wanted_peer_refs
r_static
r_struct
id|ref
op_star
id|wanted_peer_refs
c_func
(paren
r_const
r_struct
id|ref
op_star
id|refs
comma
r_struct
id|refspec
op_star
id|refspec
)paren
(brace
r_struct
id|ref
op_star
id|local_refs
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ref
op_star
op_star
id|tail
op_assign
op_amp
id|local_refs
suffix:semicolon
id|get_fetch_map
c_func
(paren
id|refs
comma
id|refspec
comma
op_amp
id|tail
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option_mirror
)paren
id|get_fetch_map
c_func
(paren
id|refs
comma
id|tag_refspec
comma
op_amp
id|tail
comma
l_int|0
)paren
suffix:semicolon
r_return
id|local_refs
suffix:semicolon
)brace
DECL|function|write_remote_refs
r_static
r_void
id|write_remote_refs
c_func
(paren
r_const
r_struct
id|ref
op_star
id|local_refs
)paren
(brace
r_const
r_struct
id|ref
op_star
id|r
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
id|local_refs
suffix:semicolon
id|r
suffix:semicolon
id|r
op_assign
id|r-&gt;next
)paren
id|add_extra_ref
c_func
(paren
id|r-&gt;peer_ref-&gt;name
comma
id|r-&gt;old_sha1
comma
l_int|0
)paren
suffix:semicolon
id|pack_refs
c_func
(paren
id|PACK_REFS_ALL
)paren
suffix:semicolon
id|clear_extra_refs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cmd_clone
r_int
id|cmd_clone
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
id|is_bundle
op_assign
l_int|0
suffix:semicolon
r_struct
id|stat
id|buf
suffix:semicolon
r_const
r_char
op_star
id|repo_name
comma
op_star
id|repo
comma
op_star
id|work_tree
comma
op_star
id|git_dir
suffix:semicolon
r_char
op_star
id|path
comma
op_star
id|dir
suffix:semicolon
r_int
id|dest_exists
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|refs
comma
op_star
id|remote_head
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|remote_head_points_at
suffix:semicolon
r_const
r_struct
id|ref
op_star
id|our_head_points_at
suffix:semicolon
r_struct
id|ref
op_star
id|mapped_refs
suffix:semicolon
r_struct
id|strbuf
id|key
op_assign
id|STRBUF_INIT
comma
id|value
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|strbuf
id|branch_top
op_assign
id|STRBUF_INIT
comma
id|reflog_msg
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|transport
op_star
id|transport
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|src_ref_prefix
op_assign
l_string|&quot;refs/heads/&quot;
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|refspec
op_star
id|refspec
suffix:semicolon
r_const
r_char
op_star
id|fetch_pattern
suffix:semicolon
id|junk_pid
op_assign
id|getpid
c_func
(paren
)paren
suffix:semicolon
id|argc
op_assign
id|parse_options
c_func
(paren
id|argc
comma
id|argv
comma
id|prefix
comma
id|builtin_clone_options
comma
id|builtin_clone_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;You must specify a repository to clone.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_mirror
)paren
id|option_bare
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|option_bare
)paren
(brace
r_if
c_cond
(paren
id|option_origin
)paren
id|die
c_func
(paren
l_string|&quot;--bare and --origin %s options are incompatible.&quot;
comma
id|option_origin
)paren
suffix:semicolon
id|option_no_checkout
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|option_origin
)paren
id|option_origin
op_assign
l_string|&quot;origin&quot;
suffix:semicolon
id|repo_name
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|path
op_assign
id|get_repo_path
c_func
(paren
id|repo_name
comma
op_amp
id|is_bundle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
)paren
id|repo
op_assign
id|xstrdup
c_func
(paren
id|make_nonrelative_path
c_func
(paren
id|repo_name
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strchr
c_func
(paren
id|repo_name
comma
l_char|&squot;:&squot;
)paren
)paren
id|repo
op_assign
id|xstrdup
c_func
(paren
id|make_absolute_path
c_func
(paren
id|repo_name
)paren
)paren
suffix:semicolon
r_else
id|repo
op_assign
id|repo_name
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
)paren
id|dir
op_assign
id|xstrdup
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
id|dir
op_assign
id|guess_dir_name
c_func
(paren
id|repo_name
comma
id|is_bundle
comma
id|option_bare
)paren
suffix:semicolon
id|strip_trailing_slashes
c_func
(paren
id|dir
)paren
suffix:semicolon
id|dest_exists
op_assign
op_logical_neg
id|stat
c_func
(paren
id|dir
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dest_exists
op_logical_and
op_logical_neg
id|is_empty_dir
c_func
(paren
id|dir
)paren
)paren
id|die
c_func
(paren
l_string|&quot;destination path &squot;%s&squot; already exists and is not &quot;
l_string|&quot;an empty directory.&quot;
comma
id|dir
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|reflog_msg
comma
l_string|&quot;clone: from %s&quot;
comma
id|repo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_bare
)paren
id|work_tree
op_assign
l_int|NULL
suffix:semicolon
r_else
(brace
id|work_tree
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_WORK_TREE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|work_tree
op_logical_and
op_logical_neg
id|stat
c_func
(paren
id|work_tree
comma
op_amp
id|buf
)paren
)paren
id|die
c_func
(paren
l_string|&quot;working tree &squot;%s&squot; already exists.&quot;
comma
id|work_tree
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|option_bare
op_logical_or
id|work_tree
)paren
id|git_dir
op_assign
id|xstrdup
c_func
(paren
id|dir
)paren
suffix:semicolon
r_else
(brace
id|work_tree
op_assign
id|dir
suffix:semicolon
id|git_dir
op_assign
id|xstrdup
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/.git&quot;
comma
id|dir
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|option_bare
)paren
(brace
id|junk_work_tree
op_assign
id|work_tree
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories_const
c_func
(paren
id|work_tree
)paren
OL
l_int|0
)paren
id|die_errno
c_func
(paren
l_string|&quot;could not create leading directories of &squot;%s&squot;&quot;
comma
id|work_tree
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest_exists
op_logical_and
id|mkdir
c_func
(paren
id|work_tree
comma
l_int|0755
)paren
)paren
id|die_errno
c_func
(paren
l_string|&quot;could not create work tree dir &squot;%s&squot;.&quot;
comma
id|work_tree
)paren
suffix:semicolon
id|set_git_work_tree
c_func
(paren
id|work_tree
)paren
suffix:semicolon
)brace
id|junk_git_dir
op_assign
id|git_dir
suffix:semicolon
id|atexit
c_func
(paren
id|remove_junk
)paren
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|remove_junk_on_signal
)paren
suffix:semicolon
id|setenv
c_func
(paren
id|CONFIG_ENVIRONMENT
comma
id|mkpath
c_func
(paren
l_string|&quot;%s/config&quot;
comma
id|git_dir
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|safe_create_leading_directories_const
c_func
(paren
id|git_dir
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;could not create leading directories of &squot;%s&squot;&quot;
comma
id|git_dir
)paren
suffix:semicolon
id|set_git_dir
c_func
(paren
id|make_absolute_path
c_func
(paren
id|git_dir
)paren
)paren
suffix:semicolon
id|init_db
c_func
(paren
id|option_template
comma
id|option_quiet
ques
c_cond
id|INIT_DB_QUIET
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * At this point, the config exists, so we do not need the&n;&t; * environment variable.  We actually need to unset it, too, to&n;&t; * re-enable parsing of the global configs.&n;&t; */
id|unsetenv
c_func
(paren
id|CONFIG_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_reference
)paren
id|setup_reference
c_func
(paren
id|git_dir
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_bare
)paren
(brace
r_if
c_cond
(paren
id|option_mirror
)paren
id|src_ref_prefix
op_assign
l_string|&quot;refs/&quot;
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|branch_top
comma
id|src_ref_prefix
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
l_string|&quot;core.bare&quot;
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strbuf_addf
c_func
(paren
op_amp
id|branch_top
comma
l_string|&quot;refs/remotes/%s/&quot;
comma
id|option_origin
)paren
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|value
comma
l_string|&quot;+%s*:%s*&quot;
comma
id|src_ref_prefix
comma
id|branch_top.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_mirror
op_logical_or
op_logical_neg
id|option_bare
)paren
(brace
multiline_comment|/* Configure the remote */
id|strbuf_addf
c_func
(paren
op_amp
id|key
comma
l_string|&quot;remote.%s.fetch&quot;
comma
id|option_origin
)paren
suffix:semicolon
id|git_config_set_multivar
c_func
(paren
id|key.buf
comma
id|value.buf
comma
l_string|&quot;^$&quot;
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_mirror
)paren
(brace
id|strbuf_addf
c_func
(paren
op_amp
id|key
comma
l_string|&quot;remote.%s.mirror&quot;
comma
id|option_origin
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key.buf
comma
l_string|&quot;true&quot;
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|key
comma
l_string|&quot;remote.%s.url&quot;
comma
id|option_origin
)paren
suffix:semicolon
id|git_config_set
c_func
(paren
id|key.buf
comma
id|repo
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
)brace
id|fetch_pattern
op_assign
id|value.buf
suffix:semicolon
id|refspec
op_assign
id|parse_fetch_refspec
c_func
(paren
l_int|1
comma
op_amp
id|fetch_pattern
)paren
suffix:semicolon
id|strbuf_reset
c_func
(paren
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|path
op_logical_and
op_logical_neg
id|is_bundle
)paren
(brace
id|refs
op_assign
id|clone_local
c_func
(paren
id|path
comma
id|git_dir
)paren
suffix:semicolon
id|mapped_refs
op_assign
id|wanted_peer_refs
c_func
(paren
id|refs
comma
id|refspec
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|remote
op_star
id|remote
op_assign
id|remote_get
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|transport
op_assign
id|transport_get
c_func
(paren
id|remote
comma
id|remote-&gt;url
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|transport-&gt;get_refs_list
op_logical_or
op_logical_neg
id|transport-&gt;fetch
)paren
id|die
c_func
(paren
l_string|&quot;Don&squot;t know how to clone %s&quot;
comma
id|transport-&gt;url
)paren
suffix:semicolon
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_KEEP
comma
l_string|&quot;yes&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_depth
)paren
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_DEPTH
comma
id|option_depth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_quiet
)paren
id|transport-&gt;verbose
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|option_verbose
)paren
id|transport-&gt;progress
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|option_upload_pack
)paren
id|transport_set_option
c_func
(paren
id|transport
comma
id|TRANS_OPT_UPLOADPACK
comma
id|option_upload_pack
)paren
suffix:semicolon
id|refs
op_assign
id|transport_get_remote_refs
c_func
(paren
id|transport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|refs
)paren
(brace
id|mapped_refs
op_assign
id|wanted_peer_refs
c_func
(paren
id|refs
comma
id|refspec
)paren
suffix:semicolon
id|transport_fetch_refs
c_func
(paren
id|transport
comma
id|mapped_refs
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|refs
)paren
(brace
id|clear_extra_refs
c_func
(paren
)paren
suffix:semicolon
id|write_remote_refs
c_func
(paren
id|mapped_refs
)paren
suffix:semicolon
id|remote_head
op_assign
id|find_ref_by_name
c_func
(paren
id|refs
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
id|remote_head_points_at
op_assign
id|guess_remote_head
c_func
(paren
id|remote_head
comma
id|mapped_refs
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|option_branch
)paren
(brace
r_struct
id|strbuf
id|head
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|head
comma
id|src_ref_prefix
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|head
comma
id|option_branch
)paren
suffix:semicolon
id|our_head_points_at
op_assign
id|find_ref_by_name
c_func
(paren
id|mapped_refs
comma
id|head.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|our_head_points_at
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;Remote branch %s not found in &quot;
l_string|&quot;upstream %s, using HEAD instead&quot;
comma
id|option_branch
comma
id|option_origin
)paren
suffix:semicolon
id|our_head_points_at
op_assign
id|remote_head_points_at
suffix:semicolon
)brace
)brace
r_else
id|our_head_points_at
op_assign
id|remote_head_points_at
suffix:semicolon
)brace
r_else
(brace
id|warning
c_func
(paren
l_string|&quot;You appear to have cloned an empty repository.&quot;
)paren
suffix:semicolon
id|our_head_points_at
op_assign
l_int|NULL
suffix:semicolon
id|remote_head_points_at
op_assign
l_int|NULL
suffix:semicolon
id|remote_head
op_assign
l_int|NULL
suffix:semicolon
id|option_no_checkout
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option_bare
)paren
id|install_branch_config
c_func
(paren
l_int|0
comma
l_string|&quot;master&quot;
comma
id|option_origin
comma
l_string|&quot;refs/heads/master&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|remote_head_points_at
op_logical_and
op_logical_neg
id|option_bare
)paren
(brace
r_struct
id|strbuf
id|head_ref
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|head_ref
comma
id|branch_top.buf
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|head_ref
comma
l_string|&quot;HEAD&quot;
)paren
suffix:semicolon
id|create_symref
c_func
(paren
id|head_ref.buf
comma
id|remote_head_points_at-&gt;peer_ref-&gt;name
comma
id|reflog_msg.buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|our_head_points_at
)paren
(brace
multiline_comment|/* Local default branch link */
id|create_symref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|our_head_points_at-&gt;name
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option_bare
)paren
(brace
r_const
r_char
op_star
id|head
op_assign
id|skip_prefix
c_func
(paren
id|our_head_points_at-&gt;name
comma
l_string|&quot;refs/heads/&quot;
)paren
suffix:semicolon
id|update_ref
c_func
(paren
id|reflog_msg.buf
comma
l_string|&quot;HEAD&quot;
comma
id|our_head_points_at-&gt;old_sha1
comma
l_int|NULL
comma
l_int|0
comma
id|DIE_ON_ERR
)paren
suffix:semicolon
id|install_branch_config
c_func
(paren
l_int|0
comma
id|head
comma
id|option_origin
comma
id|our_head_points_at-&gt;name
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|remote_head
)paren
(brace
multiline_comment|/* Source had detached HEAD pointing somewhere. */
r_if
c_cond
(paren
op_logical_neg
id|option_bare
)paren
(brace
id|update_ref
c_func
(paren
id|reflog_msg.buf
comma
l_string|&quot;HEAD&quot;
comma
id|remote_head-&gt;old_sha1
comma
l_int|NULL
comma
id|REF_NODEREF
comma
id|DIE_ON_ERR
)paren
suffix:semicolon
id|our_head_points_at
op_assign
id|remote_head
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Nothing to checkout out */
r_if
c_cond
(paren
op_logical_neg
id|option_no_checkout
)paren
id|warning
c_func
(paren
l_string|&quot;remote HEAD refers to nonexistent ref, &quot;
l_string|&quot;unable to checkout.&bslash;n&quot;
)paren
suffix:semicolon
id|option_no_checkout
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|transport
)paren
(brace
id|transport_unlock_pack
c_func
(paren
id|transport
)paren
suffix:semicolon
id|transport_disconnect
c_func
(paren
id|transport
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|option_no_checkout
)paren
(brace
r_struct
id|lock_file
op_star
id|lock_file
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|lock_file
)paren
)paren
suffix:semicolon
r_struct
id|unpack_trees_options
id|opts
suffix:semicolon
r_struct
id|tree
op_star
id|tree
suffix:semicolon
r_struct
id|tree_desc
id|t
suffix:semicolon
r_int
id|fd
suffix:semicolon
multiline_comment|/* We need to be in the new work tree for the checkout */
id|setup_work_tree
c_func
(paren
)paren
suffix:semicolon
id|fd
op_assign
id|hold_locked_index
c_func
(paren
id|lock_file
comma
l_int|1
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|opts
comma
l_int|0
comma
r_sizeof
id|opts
)paren
suffix:semicolon
id|opts.update
op_assign
l_int|1
suffix:semicolon
id|opts.merge
op_assign
l_int|1
suffix:semicolon
id|opts.fn
op_assign
id|oneway_merge
suffix:semicolon
id|opts.verbose_update
op_assign
op_logical_neg
id|option_quiet
suffix:semicolon
id|opts.src_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|opts.dst_index
op_assign
op_amp
id|the_index
suffix:semicolon
id|tree
op_assign
id|parse_tree_indirect
c_func
(paren
id|our_head_points_at-&gt;old_sha1
)paren
suffix:semicolon
id|parse_tree
c_func
(paren
id|tree
)paren
suffix:semicolon
id|init_tree_desc
c_func
(paren
op_amp
id|t
comma
id|tree-&gt;buffer
comma
id|tree-&gt;size
)paren
suffix:semicolon
id|unpack_trees
c_func
(paren
l_int|1
comma
op_amp
id|t
comma
op_amp
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write_cache
c_func
(paren
id|fd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
id|lock_file
)paren
)paren
id|die
c_func
(paren
l_string|&quot;unable to write new index file&quot;
)paren
suffix:semicolon
id|err
op_or_assign
id|run_hook
c_func
(paren
l_int|NULL
comma
l_string|&quot;post-checkout&quot;
comma
id|sha1_to_hex
c_func
(paren
id|null_sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|our_head_points_at-&gt;old_sha1
)paren
comma
l_string|&quot;1&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|option_recursive
)paren
id|err
op_assign
id|run_command_v_opt
c_func
(paren
id|argv_submodule
comma
id|RUN_GIT_CMD
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|reflog_msg
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|branch_top
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|key
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|value
)paren
suffix:semicolon
id|junk_pid
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
