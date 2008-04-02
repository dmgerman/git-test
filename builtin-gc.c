multiline_comment|/*&n; * git gc builtin command&n; *&n; * Cleanup unreachable files and optimize the repository.&n; *&n; * Copyright (c) 2007 James Bowes&n; *&n; * Based on git-gc.sh, which is&n; *&n; * Copyright (c) 2006 Shawn O. Pearce&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
DECL|macro|FAILED_RUN
mdefine_line|#define FAILED_RUN &quot;failed to run %s&quot;
DECL|variable|builtin_gc_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_gc_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git-gc [options]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|pack_refs
r_static
r_int
id|pack_refs
op_assign
l_int|1
suffix:semicolon
DECL|variable|aggressive_window
r_static
r_int
id|aggressive_window
op_assign
l_int|1
suffix:semicolon
DECL|variable|gc_auto_threshold
r_static
r_int
id|gc_auto_threshold
op_assign
l_int|6700
suffix:semicolon
DECL|variable|gc_auto_pack_limit
r_static
r_int
id|gc_auto_pack_limit
op_assign
l_int|50
suffix:semicolon
DECL|variable|prune_expire
r_static
r_char
op_star
id|prune_expire
op_assign
l_string|&quot;2.weeks.ago&quot;
suffix:semicolon
DECL|macro|MAX_ADD
mdefine_line|#define MAX_ADD 10
DECL|variable|argv_pack_refs
r_static
r_const
r_char
op_star
id|argv_pack_refs
(braket
)braket
op_assign
(brace
l_string|&quot;pack-refs&quot;
comma
l_string|&quot;--all&quot;
comma
l_string|&quot;--prune&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|argv_reflog
r_static
r_const
r_char
op_star
id|argv_reflog
(braket
)braket
op_assign
(brace
l_string|&quot;reflog&quot;
comma
l_string|&quot;expire&quot;
comma
l_string|&quot;--all&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|argv_repack
r_static
r_const
r_char
op_star
id|argv_repack
(braket
id|MAX_ADD
)braket
op_assign
(brace
l_string|&quot;repack&quot;
comma
l_string|&quot;-d&quot;
comma
l_string|&quot;-l&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|argv_prune
r_static
r_const
r_char
op_star
id|argv_prune
(braket
)braket
op_assign
(brace
l_string|&quot;prune&quot;
comma
l_string|&quot;--expire&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|argv_rerere
r_static
r_const
r_char
op_star
id|argv_rerere
(braket
)braket
op_assign
(brace
l_string|&quot;rerere&quot;
comma
l_string|&quot;gc&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|gc_config
r_static
r_int
id|gc_config
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
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.packrefs&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|value
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;notbare&quot;
)paren
)paren
id|pack_refs
op_assign
l_int|1
suffix:semicolon
r_else
id|pack_refs
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.aggressivewindow&quot;
)paren
)paren
(brace
id|aggressive_window
op_assign
id|git_config_int
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.auto&quot;
)paren
)paren
(brace
id|gc_auto_threshold
op_assign
id|git_config_int
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.autopacklimit&quot;
)paren
)paren
(brace
id|gc_auto_pack_limit
op_assign
id|git_config_int
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
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|var
comma
l_string|&quot;gc.pruneexpire&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|value
comma
l_string|&quot;now&quot;
)paren
)paren
(brace
r_int
r_int
id|now
op_assign
id|approxidate
c_func
(paren
l_string|&quot;now&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|approxidate
c_func
(paren
id|value
)paren
op_ge
id|now
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Invalid %s: &squot;%s&squot;&quot;
comma
id|var
comma
id|value
)paren
suffix:semicolon
)brace
id|prune_expire
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
DECL|function|append_option
r_static
r_void
id|append_option
c_func
(paren
r_const
r_char
op_star
op_star
id|cmd
comma
r_const
r_char
op_star
id|opt
comma
r_int
id|max_length
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
id|cmd
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
l_int|2
op_ge
id|max_length
)paren
id|die
c_func
(paren
l_string|&quot;Too many options specified&quot;
)paren
suffix:semicolon
id|cmd
(braket
id|i
op_increment
)braket
op_assign
id|opt
suffix:semicolon
id|cmd
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|too_many_loose_objects
r_static
r_int
id|too_many_loose_objects
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Quickly check if a &quot;gc&quot; is needed, by estimating how&n;&t; * many loose objects there are.  Because SHA-1 is evenly&n;&t; * distributed, we can check only one and get a reasonable&n;&t; * estimate.&n;&t; */
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_const
r_char
op_star
id|objdir
op_assign
id|get_object_directory
c_func
(paren
)paren
suffix:semicolon
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|ent
suffix:semicolon
r_int
id|auto_threshold
suffix:semicolon
r_int
id|num_loose
op_assign
l_int|0
suffix:semicolon
r_int
id|needed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|gc_auto_threshold
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|path
)paren
op_le
id|snprintf
c_func
(paren
id|path
comma
r_sizeof
(paren
id|path
)paren
comma
l_string|&quot;%s/17&quot;
comma
id|objdir
)paren
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;insanely long object directory %.*s&quot;
comma
l_int|50
comma
id|objdir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
l_int|0
suffix:semicolon
id|auto_threshold
op_assign
(paren
id|gc_auto_threshold
op_plus
l_int|255
)paren
op_div
l_int|256
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ent
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
r_if
c_cond
(paren
id|strspn
c_func
(paren
id|ent-&gt;d_name
comma
l_string|&quot;0123456789abcdef&quot;
)paren
op_ne
l_int|38
op_logical_or
id|ent-&gt;d_name
(braket
l_int|38
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|num_loose
OG
id|auto_threshold
)paren
(brace
id|needed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|needed
suffix:semicolon
)brace
DECL|function|too_many_packs
r_static
r_int
id|too_many_packs
c_func
(paren
r_void
)paren
(brace
r_struct
id|packed_git
op_star
id|p
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|gc_auto_pack_limit
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|prepare_packed_git
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
comma
id|p
op_assign
id|packed_git
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|keep
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;pack_local
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|p-&gt;pack_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PATH_MAX
op_le
id|len
op_plus
l_int|1
)paren
r_continue
suffix:semicolon
multiline_comment|/* oops, give up */
id|memcpy
c_func
(paren
id|path
comma
id|p-&gt;pack_name
comma
id|len
op_minus
l_int|5
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
op_plus
id|len
l_int|5
comma
l_string|&quot;.keep&quot;
comma
l_int|6
)paren
suffix:semicolon
id|keep
op_assign
id|access
c_func
(paren
id|p-&gt;pack_name
comma
id|F_OK
)paren
op_logical_and
(paren
id|errno
op_eq
id|ENOENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|keep
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Perhaps check the size of the pack and count only&n;&t;&t; * very small ones here?&n;&t;&t; */
id|cnt
op_increment
suffix:semicolon
)brace
r_return
id|gc_auto_pack_limit
op_le
id|cnt
suffix:semicolon
)brace
DECL|function|run_hook
r_static
r_int
id|run_hook
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|argv
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|child_process
id|hook
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|git_path
c_func
(paren
l_string|&quot;hooks/pre-auto-gc&quot;
)paren
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|X_OK
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hook
comma
l_int|0
comma
r_sizeof
(paren
id|hook
)paren
)paren
suffix:semicolon
id|hook.argv
op_assign
id|argv
suffix:semicolon
id|hook.no_stdin
op_assign
l_int|1
suffix:semicolon
id|hook.stdout_to_stderr
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|start_command
c_func
(paren
op_amp
id|hook
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|warning
c_func
(paren
l_string|&quot;Could not spawn %s&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|finish_command
c_func
(paren
op_amp
id|hook
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|ERR_RUN_COMMAND_WAITPID_SIGNAL
)paren
id|warning
c_func
(paren
l_string|&quot;%s exited due to uncaught signal&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|need_to_gc
r_static
r_int
id|need_to_gc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Setting gc.auto to 0 or negative can disable the&n;&t; * automatic gc.&n;&t; */
r_if
c_cond
(paren
id|gc_auto_threshold
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If there are too many loose objects, but not too many&n;&t; * packs, we run &quot;repack -d -l&quot;.  If there are too many packs,&n;&t; * we run &quot;repack -A -d -l&quot;.  Otherwise we tell the caller&n;&t; * there is no need.&n;&t; */
r_if
c_cond
(paren
id|too_many_packs
c_func
(paren
)paren
)paren
id|append_option
c_func
(paren
id|argv_repack
comma
l_string|&quot;-A&quot;
comma
id|MAX_ADD
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|too_many_loose_objects
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|run_hook
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cmd_gc
r_int
id|cmd_gc
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
id|prune
op_assign
l_int|0
suffix:semicolon
r_int
id|aggressive
op_assign
l_int|0
suffix:semicolon
r_int
id|auto_gc
op_assign
l_int|0
suffix:semicolon
r_int
id|quiet
op_assign
l_int|0
suffix:semicolon
r_char
id|buf
(braket
l_int|80
)braket
suffix:semicolon
r_struct
id|option
id|builtin_gc_options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;prune&quot;
comma
op_amp
id|prune
comma
l_string|&quot;prune unreferenced objects&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;aggressive&quot;
comma
op_amp
id|aggressive
comma
l_string|&quot;be more thorough (increased runtime)&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_int|0
comma
l_string|&quot;auto&quot;
comma
op_amp
id|auto_gc
comma
l_string|&quot;enable auto-gc mode&quot;
)paren
comma
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;q&squot;
comma
l_string|&quot;quiet&quot;
comma
op_amp
id|quiet
comma
l_string|&quot;suppress progress reports&quot;
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
id|git_config
c_func
(paren
id|gc_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pack_refs
OL
l_int|0
)paren
id|pack_refs
op_assign
op_logical_neg
id|is_bare_repository
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
id|builtin_gc_options
comma
id|builtin_gc_usage
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|0
)paren
id|usage_with_options
c_func
(paren
id|builtin_gc_usage
comma
id|builtin_gc_options
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aggressive
)paren
(brace
id|append_option
c_func
(paren
id|argv_repack
comma
l_string|&quot;-f&quot;
comma
id|MAX_ADD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aggressive_window
OG
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;--window=%d&quot;
comma
id|aggressive_window
)paren
suffix:semicolon
id|append_option
c_func
(paren
id|argv_repack
comma
id|buf
comma
id|MAX_ADD
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|quiet
)paren
id|append_option
c_func
(paren
id|argv_repack
comma
l_string|&quot;-q&quot;
comma
id|MAX_ADD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|auto_gc
)paren
(brace
multiline_comment|/*&n;&t;&t; * Auto-gc should be least intrusive as possible.&n;&t;&t; */
id|prune
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_to_gc
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Auto packing your repository for optimum &quot;
l_string|&quot;performance. You may also&bslash;n&quot;
l_string|&quot;run &bslash;&quot;git gc&bslash;&quot; manually. See &quot;
l_string|&quot;&bslash;&quot;git help gc&bslash;&quot; for more information.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Use safer (for shared repos) &quot;-A&quot; option to&n;&t;&t; * repack when not pruning. Auto-gc makes its&n;&t;&t; * own decision.&n;&t;&t; */
r_if
c_cond
(paren
id|prune
)paren
id|append_option
c_func
(paren
id|argv_repack
comma
l_string|&quot;-a&quot;
comma
id|MAX_ADD
)paren
suffix:semicolon
r_else
id|append_option
c_func
(paren
id|argv_repack
comma
l_string|&quot;-A&quot;
comma
id|MAX_ADD
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pack_refs
op_logical_and
id|run_command_v_opt
c_func
(paren
id|argv_pack_refs
comma
id|RUN_GIT_CMD
)paren
)paren
r_return
id|error
c_func
(paren
id|FAILED_RUN
comma
id|argv_pack_refs
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|argv_reflog
comma
id|RUN_GIT_CMD
)paren
)paren
r_return
id|error
c_func
(paren
id|FAILED_RUN
comma
id|argv_reflog
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|argv_repack
comma
id|RUN_GIT_CMD
)paren
)paren
r_return
id|error
c_func
(paren
id|FAILED_RUN
comma
id|argv_repack
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|argv_prune
(braket
l_int|2
)braket
op_assign
id|prune_expire
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|argv_prune
comma
id|RUN_GIT_CMD
)paren
)paren
r_return
id|error
c_func
(paren
id|FAILED_RUN
comma
id|argv_prune
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|argv_rerere
comma
id|RUN_GIT_CMD
)paren
)paren
r_return
id|error
c_func
(paren
id|FAILED_RUN
comma
id|argv_rerere
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|auto_gc
op_logical_and
id|too_many_loose_objects
c_func
(paren
)paren
)paren
id|warning
c_func
(paren
l_string|&quot;There are too many unreachable loose objects; &quot;
l_string|&quot;run &squot;git prune&squot; to remove them.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
