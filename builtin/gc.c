multiline_comment|/*&n; * git gc builtin command&n; *&n; * Cleanup unreachable files and optimize the repository.&n; *&n; * Copyright (c) 2007 James Bowes&n; *&n; * Based on git-gc.sh, which is&n; *&n; * Copyright (c) 2006 Shawn O. Pearce&n; */
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;lockfile.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#include &quot;argv-array.h&quot;
macro_line|#include &quot;commit.h&quot;
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
id|N_
c_func
(paren
l_string|&quot;git gc [options]&quot;
)paren
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
DECL|variable|prune_reflogs
r_static
r_int
id|prune_reflogs
op_assign
l_int|1
suffix:semicolon
DECL|variable|aggressive_depth
r_static
r_int
id|aggressive_depth
op_assign
l_int|250
suffix:semicolon
DECL|variable|aggressive_window
r_static
r_int
id|aggressive_window
op_assign
l_int|250
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
DECL|variable|detach_auto
r_static
r_int
id|detach_auto
op_assign
l_int|1
suffix:semicolon
DECL|variable|prune_expire
r_static
r_const
r_char
op_star
id|prune_expire
op_assign
l_string|&quot;2.weeks.ago&quot;
suffix:semicolon
DECL|variable|pack_refs_cmd
r_static
r_struct
id|argv_array
id|pack_refs_cmd
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
DECL|variable|reflog
r_static
r_struct
id|argv_array
id|reflog
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
DECL|variable|repack
r_static
r_struct
id|argv_array
id|repack
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
DECL|variable|prune
r_static
r_struct
id|argv_array
id|prune
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
DECL|variable|rerere
r_static
r_struct
id|argv_array
id|rerere
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
DECL|variable|pidfile
r_static
r_char
op_star
id|pidfile
suffix:semicolon
DECL|variable|log_lock
r_static
r_struct
id|lock_file
id|log_lock
suffix:semicolon
DECL|function|remove_pidfile
r_static
r_void
id|remove_pidfile
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pidfile
)paren
id|unlink
c_func
(paren
id|pidfile
)paren
suffix:semicolon
)brace
DECL|function|remove_pidfile_on_signal
r_static
r_void
id|remove_pidfile_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_pidfile
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
DECL|function|process_log_file
r_static
r_void
id|process_log_file
c_func
(paren
r_void
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fstat
c_func
(paren
id|log_lock.fd
comma
op_amp
id|st
)paren
op_logical_and
id|st.st_size
)paren
id|commit_lock_file
c_func
(paren
op_amp
id|log_lock
)paren
suffix:semicolon
r_else
id|rollback_lock_file
c_func
(paren
op_amp
id|log_lock
)paren
suffix:semicolon
)brace
DECL|function|process_log_file_at_exit
r_static
r_void
id|process_log_file_at_exit
c_func
(paren
r_void
)paren
(brace
id|fflush
c_func
(paren
id|stderr
)paren
suffix:semicolon
id|process_log_file
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|process_log_file_on_signal
r_static
r_void
id|process_log_file_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|process_log_file
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
DECL|function|gc_config
r_static
r_void
id|gc_config
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_config_get_value
c_func
(paren
l_string|&quot;gc.packrefs&quot;
comma
op_amp
id|value
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
l_string|&quot;gc.packrefs&quot;
comma
id|value
)paren
suffix:semicolon
)brace
id|git_config_get_int
c_func
(paren
l_string|&quot;gc.aggressivewindow&quot;
comma
op_amp
id|aggressive_window
)paren
suffix:semicolon
id|git_config_get_int
c_func
(paren
l_string|&quot;gc.aggressivedepth&quot;
comma
op_amp
id|aggressive_depth
)paren
suffix:semicolon
id|git_config_get_int
c_func
(paren
l_string|&quot;gc.auto&quot;
comma
op_amp
id|gc_auto_threshold
)paren
suffix:semicolon
id|git_config_get_int
c_func
(paren
l_string|&quot;gc.autopacklimit&quot;
comma
op_amp
id|gc_auto_pack_limit
)paren
suffix:semicolon
id|git_config_get_bool
c_func
(paren
l_string|&quot;gc.autodetach&quot;
comma
op_amp
id|detach_auto
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|git_config_get_string_const
c_func
(paren
l_string|&quot;gc.pruneexpire&quot;
comma
op_amp
id|prune_expire
)paren
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|prune_expire
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
id|prune_expire
)paren
op_ge
id|now
)paren
(brace
id|git_die_config
c_func
(paren
l_string|&quot;gc.pruneexpire&quot;
comma
id|_
c_func
(paren
l_string|&quot;Invalid gc.pruneexpire: &squot;%s&squot;&quot;
)paren
comma
id|prune_expire
)paren
suffix:semicolon
)brace
)brace
)brace
id|git_config
c_func
(paren
id|git_default_config
comma
l_int|NULL
)paren
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
id|_
c_func
(paren
l_string|&quot;insanely long object directory %.*s&quot;
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;pack_local
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pack_keep
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
DECL|function|add_repack_all_option
r_static
r_void
id|add_repack_all_option
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|prune_expire
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|prune_expire
comma
l_string|&quot;now&quot;
)paren
)paren
id|argv_array_push
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;-a&quot;
)paren
suffix:semicolon
r_else
(brace
id|argv_array_push
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;-A&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prune_expire
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;--unpack-unreachable=%s&quot;
comma
id|prune_expire
)paren
suffix:semicolon
)brace
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
id|add_repack_all_option
c_func
(paren
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
id|run_hook_le
c_func
(paren
l_int|NULL
comma
l_string|&quot;pre-auto-gc&quot;
comma
l_int|NULL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* return NULL on success, else hostname running the gc */
DECL|function|lock_repo_for_gc
r_static
r_const
r_char
op_star
id|lock_repo_for_gc
c_func
(paren
r_int
id|force
comma
id|pid_t
op_star
id|ret_pid
)paren
(brace
r_static
r_struct
id|lock_file
id|lock
suffix:semicolon
r_char
id|my_host
(braket
l_int|128
)braket
suffix:semicolon
r_struct
id|strbuf
id|sb
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_uintmax
id|pid
suffix:semicolon
id|FILE
op_star
id|fp
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|pidfile
)paren
multiline_comment|/* already locked */
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|gethostname
c_func
(paren
id|my_host
comma
r_sizeof
(paren
id|my_host
)paren
)paren
)paren
id|strcpy
c_func
(paren
id|my_host
comma
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
id|fd
op_assign
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|lock
comma
id|git_path
c_func
(paren
l_string|&quot;gc.pid&quot;
)paren
comma
id|LOCK_DIE_ON_ERROR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|force
)paren
(brace
r_static
r_char
id|locking_host
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|should_exit
suffix:semicolon
id|fp
op_assign
id|fopen
c_func
(paren
id|git_path
c_func
(paren
l_string|&quot;gc.pid&quot;
)paren
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|locking_host
comma
l_int|0
comma
r_sizeof
(paren
id|locking_host
)paren
)paren
suffix:semicolon
id|should_exit
op_assign
id|fp
op_ne
l_int|NULL
op_logical_and
op_logical_neg
id|fstat
c_func
(paren
id|fileno
c_func
(paren
id|fp
)paren
comma
op_amp
id|st
)paren
op_logical_and
multiline_comment|/*&n;&t;&t;&t; * 12 hour limit is very generous as gc should&n;&t;&t;&t; * never take that long. On the other hand we&n;&t;&t;&t; * don&squot;t really need a strict limit here,&n;&t;&t;&t; * running gc --auto one day late is not a big&n;&t;&t;&t; * problem. --force can be used in manual gc&n;&t;&t;&t; * after the user verifies that no gc is&n;&t;&t;&t; * running.&n;&t;&t;&t; */
id|time
c_func
(paren
l_int|NULL
)paren
id|st.st_mtime
op_le
l_int|12
op_star
l_int|3600
op_logical_and
id|fscanf
c_func
(paren
id|fp
comma
l_string|&quot;%&quot;
id|PRIuMAX
l_string|&quot; %127c&quot;
comma
op_amp
id|pid
comma
id|locking_host
)paren
op_eq
l_int|2
op_logical_and
multiline_comment|/* be gentle to concurrent &quot;gc&quot; on remote hosts */
(paren
id|strcmp
c_func
(paren
id|locking_host
comma
id|my_host
)paren
op_logical_or
op_logical_neg
id|kill
c_func
(paren
id|pid
comma
l_int|0
)paren
op_logical_or
id|errno
op_eq
id|EPERM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_ne
l_int|NULL
)paren
id|fclose
c_func
(paren
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|should_exit
)paren
(brace
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
id|rollback_lock_file
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
op_star
id|ret_pid
op_assign
id|pid
suffix:semicolon
r_return
id|locking_host
suffix:semicolon
)brace
)brace
id|strbuf_addf
c_func
(paren
op_amp
id|sb
comma
l_string|&quot;%&quot;
id|PRIuMAX
l_string|&quot; %s&quot;
comma
(paren
r_uintmax
)paren
id|getpid
c_func
(paren
)paren
comma
id|my_host
)paren
suffix:semicolon
id|write_in_full
c_func
(paren
id|fd
comma
id|sb.buf
comma
id|sb.len
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
id|commit_lock_file
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|pidfile
op_assign
id|git_pathdup
c_func
(paren
l_string|&quot;gc.pid&quot;
)paren
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|remove_pidfile_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|remove_pidfile
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|report_last_gc_error
r_static
r_int
id|report_last_gc_error
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
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|strbuf_read_file
c_func
(paren
op_amp
id|sb
comma
id|git_path
c_func
(paren
l_string|&quot;gc.log&quot;
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
r_return
id|error
c_func
(paren
id|_
c_func
(paren
l_string|&quot;The last gc run reported the following. &quot;
l_string|&quot;Please correct the root cause&bslash;n&quot;
l_string|&quot;and remove %s.&bslash;n&quot;
l_string|&quot;Automatic cleanup will not be performed &quot;
l_string|&quot;until the file is removed.&bslash;n&bslash;n&quot;
l_string|&quot;%s&quot;
)paren
comma
id|git_path
c_func
(paren
l_string|&quot;gc.log&quot;
)paren
comma
id|sb.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|sb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gc_before_repack
r_static
r_int
id|gc_before_repack
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pack_refs
op_logical_and
id|run_command_v_opt
c_func
(paren
id|pack_refs_cmd.argv
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
id|pack_refs_cmd.argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prune_reflogs
op_logical_and
id|run_command_v_opt
c_func
(paren
id|reflog.argv
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
id|reflog.argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pack_refs
op_assign
l_int|0
suffix:semicolon
id|prune_reflogs
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
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
r_int
id|force
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
r_int
id|daemonized
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|builtin_gc_options
(braket
)braket
op_assign
(brace
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
id|N_
c_func
(paren
l_string|&quot;suppress progress reporting&quot;
)paren
)paren
comma
(brace
id|OPTION_STRING
comma
l_int|0
comma
l_string|&quot;prune&quot;
comma
op_amp
id|prune_expire
comma
id|N_
c_func
(paren
l_string|&quot;date&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;prune unreferenced objects&quot;
)paren
comma
id|PARSE_OPT_OPTARG
comma
l_int|NULL
comma
(paren
r_intptr
)paren
id|prune_expire
)brace
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;aggressive&quot;
comma
op_amp
id|aggressive
comma
id|N_
c_func
(paren
l_string|&quot;be more thorough (increased runtime)&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;auto&quot;
comma
op_amp
id|auto_gc
comma
id|N_
c_func
(paren
l_string|&quot;enable auto-gc mode&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_int|0
comma
l_string|&quot;force&quot;
comma
op_amp
id|force
comma
id|N_
c_func
(paren
l_string|&quot;force running gc even if there may be another gc running&quot;
)paren
)paren
comma
id|OPT_END
c_func
(paren
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_eq
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
)paren
id|usage_with_options
c_func
(paren
id|builtin_gc_usage
comma
id|builtin_gc_options
)paren
suffix:semicolon
id|argv_array_pushl
c_func
(paren
op_amp
id|pack_refs_cmd
comma
l_string|&quot;pack-refs&quot;
comma
l_string|&quot;--all&quot;
comma
l_string|&quot;--prune&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|argv_array_pushl
c_func
(paren
op_amp
id|reflog
comma
l_string|&quot;reflog&quot;
comma
l_string|&quot;expire&quot;
comma
l_string|&quot;--all&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|argv_array_pushl
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;repack&quot;
comma
l_string|&quot;-d&quot;
comma
l_string|&quot;-l&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|argv_array_pushl
c_func
(paren
op_amp
id|prune
comma
l_string|&quot;prune&quot;
comma
l_string|&quot;--expire&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|argv_array_pushl
c_func
(paren
op_amp
id|rerere
comma
l_string|&quot;rerere&quot;
comma
l_string|&quot;gc&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|gc_config
c_func
(paren
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
id|prefix
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
id|argv_array_push
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;-f&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aggressive_depth
OG
l_int|0
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;--depth=%d&quot;
comma
id|aggressive_depth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aggressive_window
OG
l_int|0
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;--window=%d&quot;
comma
id|aggressive_window
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|quiet
)paren
id|argv_array_push
c_func
(paren
op_amp
id|repack
comma
l_string|&quot;-q&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|auto_gc
)paren
(brace
multiline_comment|/*&n;&t;&t; * Auto-gc should be least intrusive as possible.&n;&t;&t; */
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
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
(brace
r_if
c_cond
(paren
id|detach_auto
)paren
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;Auto packing the repository in background for optimum performance.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
id|_
c_func
(paren
l_string|&quot;Auto packing the repository for optimum performance.&bslash;n&quot;
)paren
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
l_string|&quot;See &bslash;&quot;git help gc&bslash;&quot; for manual housekeeping.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|detach_auto
)paren
(brace
r_if
c_cond
(paren
id|report_last_gc_error
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|gc_before_repack
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * failure to daemonize is ok, we&squot;ll continue&n;&t;&t;&t; * in foreground&n;&t;&t;&t; */
id|daemonized
op_assign
op_logical_neg
id|daemonize
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|add_repack_all_option
c_func
(paren
)paren
suffix:semicolon
id|name
op_assign
id|lock_repo_for_gc
c_func
(paren
id|force
comma
op_amp
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
(brace
r_if
c_cond
(paren
id|auto_gc
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* be quiet on --auto */
id|die
c_func
(paren
id|_
c_func
(paren
l_string|&quot;gc is already running on machine &squot;%s&squot; pid %&quot;
id|PRIuMAX
l_string|&quot; (use --force if not)&quot;
)paren
comma
id|name
comma
(paren
r_uintmax
)paren
id|pid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|daemonized
)paren
(brace
id|hold_lock_file_for_update
c_func
(paren
op_amp
id|log_lock
comma
id|git_path
c_func
(paren
l_string|&quot;gc.log&quot;
)paren
comma
id|LOCK_DIE_ON_ERROR
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|log_lock.fd
comma
l_int|2
)paren
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|process_log_file_on_signal
)paren
suffix:semicolon
id|atexit
c_func
(paren
id|process_log_file_at_exit
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gc_before_repack
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|repack.argv
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
id|repack.argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prune_expire
)paren
(brace
id|argv_array_push
c_func
(paren
op_amp
id|prune
comma
id|prune_expire
)paren
suffix:semicolon
r_if
c_cond
(paren
id|quiet
)paren
id|argv_array_push
c_func
(paren
op_amp
id|prune
comma
l_string|&quot;--no-progress&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|prune.argv
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
id|prune.argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|run_command_v_opt
c_func
(paren
id|rerere.argv
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
id|rerere.argv
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
id|_
c_func
(paren
l_string|&quot;There are too many unreachable loose objects; &quot;
l_string|&quot;run &squot;git prune&squot; to remove them.&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
