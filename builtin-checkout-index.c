multiline_comment|/*&n; * Check-out files from the &quot;current cache directory&quot;&n; *&n; * Copyright (C) 2005 Linus Torvalds&n; *&n; * Careful: order of argument flags does matter. For example,&n; *&n; *&t;git-checkout-index -a -f file.c&n; *&n; * Will first check out all files listed in the cache (but not&n; * overwrite any old ones), and then force-checkout &quot;file.c&quot; a&n; * second time (ie that one _will_ overwrite any old contents&n; * with the same filename).&n; *&n; * Also, just doing &quot;git-checkout-index&quot; does nothing. You probably&n; * meant &quot;git-checkout-index -a&quot;. And if you want to force it, you&n; * want &quot;git-checkout-index -f -a&quot;.&n; *&n; * Intuitiveness is not the goal here. Repeatability is. The&n; * reason for the &quot;no arguments means no work&quot; thing is that&n; * from scripts you are supposed to be able to do things like&n; *&n; *&t;find . -name &squot;*.h&squot; -print0 | xargs -0 git-checkout-index -f --&n; *&n; * or:&n; *&n; *&t;find . -name &squot;*.h&squot; -print0 | git-checkout-index -f -z --stdin&n; *&n; * which will force all existing *.h files to be replaced with&n; * their cached copies. If an empty command line implied &quot;all&quot;,&n; * then this would force-refresh everything in the cache, which&n; * was not the point.&n; *&n; * Oh, and the &quot;--&quot; is just a good idea when you know the rest&n; * will be filenames. Just so that you wouldn&squot;t have a filename&n; * of &quot;-a&quot; causing problems (not possible in the above example,&n; * but get used to it in scripting!).&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;quote.h&quot;
macro_line|#include &quot;cache-tree.h&quot;
DECL|macro|CHECKOUT_ALL
mdefine_line|#define CHECKOUT_ALL 4
DECL|variable|line_termination
r_static
r_int
id|line_termination
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
DECL|variable|checkout_stage
r_static
r_int
id|checkout_stage
suffix:semicolon
multiline_comment|/* default to checkout stage0 */
DECL|variable|to_tempfile
r_static
r_int
id|to_tempfile
suffix:semicolon
DECL|variable|topath
r_static
r_char
id|topath
(braket
l_int|4
)braket
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|state
r_static
r_struct
id|checkout
id|state
suffix:semicolon
DECL|function|write_tempfile_record
r_static
r_void
id|write_tempfile_record
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|prefix_length
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|CHECKOUT_ALL
op_eq
id|checkout_stage
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OG
l_int|1
)paren
id|putchar
c_func
(paren
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|topath
(braket
id|i
)braket
(braket
l_int|0
)braket
)paren
id|fputs
c_func
(paren
id|topath
(braket
id|i
)braket
comma
id|stdout
)paren
suffix:semicolon
r_else
id|putchar
c_func
(paren
l_char|&squot;.&squot;
)paren
suffix:semicolon
)brace
)brace
r_else
id|fputs
c_func
(paren
id|topath
(braket
id|checkout_stage
)braket
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;t&squot;
)paren
suffix:semicolon
id|write_name_quoted
c_func
(paren
id|name
op_plus
id|prefix_length
comma
id|stdout
comma
id|line_termination
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|topath
(braket
id|i
)braket
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|checkout_file
r_static
r_int
id|checkout_file
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|prefix_length
)paren
(brace
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_int
id|pos
op_assign
id|cache_name_pos
c_func
(paren
id|name
comma
id|namelen
)paren
suffix:semicolon
r_int
id|has_same_name
op_assign
l_int|0
suffix:semicolon
r_int
id|did_checkout
op_assign
l_int|0
suffix:semicolon
r_int
id|errs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
id|pos
op_assign
id|pos
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|pos
OL
id|active_nr
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_namelen
c_func
(paren
id|ce
)paren
op_ne
id|namelen
op_logical_or
id|memcmp
c_func
(paren
id|ce-&gt;name
comma
id|name
comma
id|namelen
)paren
)paren
r_break
suffix:semicolon
id|has_same_name
op_assign
l_int|1
suffix:semicolon
id|pos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
op_ne
id|checkout_stage
op_logical_and
(paren
id|CHECKOUT_ALL
op_ne
id|checkout_stage
op_logical_or
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
)paren
r_continue
suffix:semicolon
id|did_checkout
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|checkout_entry
c_func
(paren
id|ce
comma
op_amp
id|state
comma
id|to_tempfile
ques
c_cond
id|topath
(braket
id|ce_stage
c_func
(paren
id|ce
)paren
)braket
suffix:colon
l_int|NULL
)paren
OL
l_int|0
)paren
id|errs
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|did_checkout
)paren
(brace
r_if
c_cond
(paren
id|to_tempfile
)paren
id|write_tempfile_record
c_func
(paren
id|name
comma
id|prefix_length
)paren
suffix:semicolon
r_return
id|errs
OG
l_int|0
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|state.quiet
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git-checkout-index: %s &quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|has_same_name
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;is not in the cache&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|checkout_stage
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;does not exist at stage %d&quot;
comma
id|checkout_stage
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;is unmerged&quot;
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|checkout_all
r_static
r_void
id|checkout_all
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_int
id|prefix_length
)paren
(brace
r_int
id|i
comma
id|errs
op_assign
l_int|0
suffix:semicolon
r_struct
id|cache_entry
op_star
id|last_ce
op_assign
l_int|NULL
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
id|active_nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|cache_entry
op_star
id|ce
op_assign
id|active_cache
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ce_stage
c_func
(paren
id|ce
)paren
op_ne
id|checkout_stage
op_logical_and
(paren
id|CHECKOUT_ALL
op_ne
id|checkout_stage
op_logical_or
op_logical_neg
id|ce_stage
c_func
(paren
id|ce
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|prefix
op_logical_and
op_star
id|prefix
op_logical_and
(paren
id|ce_namelen
c_func
(paren
id|ce
)paren
op_le
id|prefix_length
op_logical_or
id|memcmp
c_func
(paren
id|prefix
comma
id|ce-&gt;name
comma
id|prefix_length
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|last_ce
op_logical_and
id|to_tempfile
)paren
(brace
r_if
c_cond
(paren
id|ce_namelen
c_func
(paren
id|last_ce
)paren
op_ne
id|ce_namelen
c_func
(paren
id|ce
)paren
op_logical_or
id|memcmp
c_func
(paren
id|last_ce-&gt;name
comma
id|ce-&gt;name
comma
id|ce_namelen
c_func
(paren
id|ce
)paren
)paren
)paren
id|write_tempfile_record
c_func
(paren
id|last_ce-&gt;name
comma
id|prefix_length
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|checkout_entry
c_func
(paren
id|ce
comma
op_amp
id|state
comma
id|to_tempfile
ques
c_cond
id|topath
(braket
id|ce_stage
c_func
(paren
id|ce
)paren
)braket
suffix:colon
l_int|NULL
)paren
OL
l_int|0
)paren
id|errs
op_increment
suffix:semicolon
id|last_ce
op_assign
id|ce
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_ce
op_logical_and
id|to_tempfile
)paren
id|write_tempfile_record
c_func
(paren
id|last_ce-&gt;name
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errs
)paren
multiline_comment|/* we have already done our error reporting.&n;&t;&t; * exit with the same code as die().&n;&t;&t; */
m_exit
(paren
l_int|128
)paren
suffix:semicolon
)brace
DECL|variable|checkout_cache_usage
r_static
r_const
r_char
id|checkout_cache_usage
(braket
)braket
op_assign
l_string|&quot;git-checkout-index [-u] [-q] [-a] [-f] [-n] [--stage=[123]|all] [--prefix=&lt;string&gt;] [--temp] [--] &lt;file&gt;...&quot;
suffix:semicolon
DECL|variable|lock_file
r_static
r_struct
id|lock_file
id|lock_file
suffix:semicolon
DECL|function|cmd_checkout_index
r_int
id|cmd_checkout_index
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
r_int
id|newfd
op_assign
l_int|1
suffix:semicolon
r_int
id|all
op_assign
l_int|0
suffix:semicolon
r_int
id|read_from_stdin
op_assign
l_int|0
suffix:semicolon
r_int
id|prefix_length
suffix:semicolon
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
suffix:semicolon
id|state.base_dir
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|prefix_length
op_assign
id|prefix
ques
c_cond
id|strlen
c_func
(paren
id|prefix
)paren
suffix:colon
l_int|0
suffix:semicolon
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
(brace
id|die
c_func
(paren
l_string|&quot;invalid cache&quot;
)paren
suffix:semicolon
)brace
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
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--&quot;
)paren
)paren
(brace
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
l_string|&quot;-a&quot;
)paren
op_logical_or
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
l_string|&quot;-f&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--force&quot;
)paren
)paren
(brace
id|state.force
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
l_string|&quot;-q&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--quiet&quot;
)paren
)paren
(brace
id|state.quiet
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
l_string|&quot;-n&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--no-create&quot;
)paren
)paren
(brace
id|state.not_new
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
l_string|&quot;-u&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--index&quot;
)paren
)paren
(brace
id|state.refresh_cache
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|newfd
OL
l_int|0
)paren
id|newfd
op_assign
id|hold_locked_index
c_func
(paren
op_amp
id|lock_file
comma
l_int|1
)paren
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
l_string|&quot;-z&quot;
)paren
)paren
(brace
id|line_termination
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
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--stdin&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
id|argc
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;--stdin must be at the end&quot;
)paren
suffix:semicolon
id|read_from_stdin
op_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
multiline_comment|/* do not consider arg as a file name */
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
l_string|&quot;--temp&quot;
)paren
)paren
(brace
id|to_tempfile
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
l_string|&quot;--prefix=&quot;
)paren
)paren
(brace
id|state.base_dir
op_assign
id|arg
op_plus
l_int|9
suffix:semicolon
id|state.base_dir_len
op_assign
id|strlen
c_func
(paren
id|state.base_dir
)paren
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
l_string|&quot;--stage=&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
op_plus
l_int|8
comma
l_string|&quot;all&quot;
)paren
)paren
(brace
id|to_tempfile
op_assign
l_int|1
suffix:semicolon
id|checkout_stage
op_assign
id|CHECKOUT_ALL
suffix:semicolon
)brace
r_else
(brace
r_int
id|ch
op_assign
id|arg
(braket
l_int|8
)braket
suffix:semicolon
r_if
c_cond
(paren
l_char|&squot;1&squot;
op_le
id|ch
op_logical_and
id|ch
op_le
l_char|&squot;3&squot;
)paren
id|checkout_stage
op_assign
id|arg
(braket
l_int|8
)braket
l_char|&squot;0&squot;
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;stage should be between 1 and 3 or all&quot;
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
id|usage
c_func
(paren
id|checkout_cache_usage
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state.base_dir_len
op_logical_or
id|to_tempfile
)paren
(brace
multiline_comment|/* when --prefix is specified we do not&n;&t;&t; * want to update cache.&n;&t;&t; */
r_if
c_cond
(paren
id|state.refresh_cache
)paren
(brace
id|rollback_lock_file
c_func
(paren
op_amp
id|lock_file
)paren
suffix:semicolon
id|newfd
op_assign
l_int|1
suffix:semicolon
)brace
id|state.refresh_cache
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Check out named files first */
r_for
c_loop
(paren
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
r_const
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|all
)paren
id|die
c_func
(paren
l_string|&quot;git-checkout-index: don&squot;t mix &squot;--all&squot; and explicit filenames&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_from_stdin
)paren
id|die
c_func
(paren
l_string|&quot;git-checkout-index: don&squot;t mix &squot;--stdin&squot; and explicit filenames&quot;
)paren
suffix:semicolon
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|arg
)paren
suffix:semicolon
id|checkout_file
c_func
(paren
id|p
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
template_param
id|arg
op_plus
id|strlen
c_func
(paren
id|arg
)paren
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read_from_stdin
)paren
(brace
r_struct
id|strbuf
id|buf
comma
id|nbuf
suffix:semicolon
r_if
c_cond
(paren
id|all
)paren
id|die
c_func
(paren
l_string|&quot;git-checkout-index: don&squot;t mix &squot;--all&squot; and &squot;--stdin&squot;&quot;
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
op_amp
id|nbuf
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|buf
comma
id|stdin
comma
id|line_termination
)paren
op_ne
id|EOF
)paren
(brace
r_const
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|line_termination
op_logical_and
id|buf.buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
id|strbuf_reset
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unquote_c_style
c_func
(paren
op_amp
id|nbuf
comma
id|buf.buf
comma
l_int|NULL
)paren
)paren
id|die
c_func
(paren
l_string|&quot;line is badly quoted&quot;
)paren
suffix:semicolon
id|strbuf_swap
c_func
(paren
op_amp
id|buf
comma
op_amp
id|nbuf
)paren
suffix:semicolon
)brace
id|p
op_assign
id|prefix_path
c_func
(paren
id|prefix
comma
id|prefix_length
comma
id|buf.buf
)paren
suffix:semicolon
id|checkout_file
c_func
(paren
id|p
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
template_param
id|buf.buf
op_plus
id|buf.len
)paren
id|free
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|nbuf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|all
)paren
id|checkout_all
c_func
(paren
id|prefix
comma
id|prefix_length
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_le
id|newfd
op_logical_and
(paren
id|write_cache
c_func
(paren
id|newfd
comma
id|active_cache
comma
id|active_nr
)paren
op_logical_or
id|commit_locked_index
c_func
(paren
op_amp
id|lock_file
)paren
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to write new index file&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
