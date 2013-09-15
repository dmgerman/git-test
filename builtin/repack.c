macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;dir.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;sigchain.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;argv-array.h&quot;
DECL|variable|delta_base_offset
r_static
r_int
id|delta_base_offset
op_assign
l_int|1
suffix:semicolon
DECL|variable|packdir
DECL|variable|packtmp
r_static
r_char
op_star
id|packdir
comma
op_star
id|packtmp
suffix:semicolon
DECL|variable|git_repack_usage
r_static
r_const
r_char
op_star
r_const
id|git_repack_usage
(braket
)braket
op_assign
(brace
id|N_
c_func
(paren
l_string|&quot;git repack [options]&quot;
)paren
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|repack_config
r_static
r_int
id|repack_config
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
comma
r_void
op_star
id|cb
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
l_string|&quot;repack.usedeltabaseoffset&quot;
)paren
)paren
(brace
id|delta_base_offset
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
id|git_default_config
c_func
(paren
id|var
comma
id|value
comma
id|cb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove temporary $GIT_OBJECT_DIRECTORY/pack/.tmp-$$-pack-* files.&n; */
DECL|function|remove_temporary_files
r_static
r_void
id|remove_temporary_files
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|dirlen
comma
id|prefixlen
suffix:semicolon
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|e
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|packdir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
suffix:semicolon
multiline_comment|/* Point at the slash at the end of &quot;.../objects/pack/&quot; */
id|dirlen
op_assign
id|strlen
c_func
(paren
id|packdir
)paren
op_plus
l_int|1
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|packtmp
)paren
suffix:semicolon
multiline_comment|/* Hold the length of  &quot;.tmp-%d-pack-&quot; */
id|prefixlen
op_assign
id|buf.len
id|dirlen
suffix:semicolon
r_while
c_loop
(paren
(paren
id|e
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|e-&gt;d_name
comma
id|buf.buf
op_plus
id|dirlen
comma
id|prefixlen
)paren
)paren
r_continue
suffix:semicolon
id|strbuf_setlen
c_func
(paren
op_amp
id|buf
comma
id|dirlen
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|e-&gt;d_name
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|buf.buf
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
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
DECL|function|remove_pack_on_signal
r_static
r_void
id|remove_pack_on_signal
c_func
(paren
r_int
id|signo
)paren
(brace
id|remove_temporary_files
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
multiline_comment|/*&n; * Adds all packs hex strings to the fname list, which do not&n; * have a corresponding .keep file.&n; */
DECL|function|get_non_kept_pack_filenames
r_static
r_void
id|get_non_kept_pack_filenames
c_func
(paren
r_struct
id|string_list
op_star
id|fname_list
)paren
(brace
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|e
suffix:semicolon
r_char
op_star
id|fname
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dir
op_assign
id|opendir
c_func
(paren
id|packdir
)paren
)paren
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|e
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
id|suffixcmp
c_func
(paren
id|e-&gt;d_name
comma
l_string|&quot;.pack&quot;
)paren
)paren
r_continue
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|e-&gt;d_name
)paren
id|strlen
c_func
(paren
l_string|&quot;.pack&quot;
)paren
suffix:semicolon
id|fname
op_assign
id|xmemdupz
c_func
(paren
id|e-&gt;d_name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/%s.keep&quot;
comma
id|packdir
comma
id|fname
)paren
)paren
)paren
id|string_list_append_nodup
c_func
(paren
id|fname_list
comma
id|fname
)paren
suffix:semicolon
r_else
id|free
c_func
(paren
id|fname
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
DECL|function|remove_redundant_pack
r_static
r_void
id|remove_redundant_pack
c_func
(paren
r_const
r_char
op_star
id|dir_name
comma
r_const
r_char
op_star
id|base_name
)paren
(brace
r_const
r_char
op_star
id|exts
(braket
)braket
op_assign
(brace
l_string|&quot;.pack&quot;
comma
l_string|&quot;.idx&quot;
comma
l_string|&quot;.keep&quot;
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|strbuf
id|buf
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|plen
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|buf
comma
l_string|&quot;%s/%s&quot;
comma
id|dir_name
comma
id|base_name
)paren
suffix:semicolon
id|plen
op_assign
id|buf.len
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
id|exts
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strbuf_setlen
c_func
(paren
op_amp
id|buf
comma
id|plen
)paren
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|buf
comma
id|exts
(braket
id|i
)braket
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|buf.buf
)paren
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
DECL|macro|ALL_INTO_ONE
mdefine_line|#define ALL_INTO_ONE 1
DECL|macro|LOOSEN_UNREACHABLE
mdefine_line|#define LOOSEN_UNREACHABLE 2
DECL|function|cmd_repack
r_int
id|cmd_repack
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
r_const
r_char
op_star
id|exts
(braket
l_int|2
)braket
op_assign
(brace
l_string|&quot;.pack&quot;
comma
l_string|&quot;.idx&quot;
)brace
suffix:semicolon
r_struct
id|child_process
id|cmd
suffix:semicolon
r_struct
id|string_list_item
op_star
id|item
suffix:semicolon
r_struct
id|argv_array
id|cmd_args
op_assign
id|ARGV_ARRAY_INIT
suffix:semicolon
r_struct
id|string_list
id|names
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|string_list
id|rollback
op_assign
id|STRING_LIST_INIT_NODUP
suffix:semicolon
r_struct
id|string_list
id|existing_packs
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
r_struct
id|strbuf
id|line
op_assign
id|STRBUF_INIT
suffix:semicolon
r_int
id|nr_packs
comma
id|ext
comma
id|ret
comma
id|failed
suffix:semicolon
id|FILE
op_star
id|out
suffix:semicolon
multiline_comment|/* variables to be filled by option parsing */
r_int
id|pack_everything
op_assign
l_int|0
suffix:semicolon
r_int
id|delete_redundant
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|unpack_unreachable
op_assign
l_int|NULL
suffix:semicolon
r_int
id|window
op_assign
l_int|0
comma
id|window_memory
op_assign
l_int|0
suffix:semicolon
r_int
id|depth
op_assign
l_int|0
suffix:semicolon
r_int
id|max_pack_size
op_assign
l_int|0
suffix:semicolon
r_int
id|no_reuse_delta
op_assign
l_int|0
comma
id|no_reuse_object
op_assign
l_int|0
suffix:semicolon
r_int
id|no_update_server_info
op_assign
l_int|0
suffix:semicolon
r_int
id|quiet
op_assign
l_int|0
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
r_struct
id|option
id|builtin_repack_options
(braket
)braket
op_assign
(brace
id|OPT_BIT
c_func
(paren
l_char|&squot;a&squot;
comma
l_int|NULL
comma
op_amp
id|pack_everything
comma
id|N_
c_func
(paren
l_string|&quot;pack everything in a single pack&quot;
)paren
comma
id|ALL_INTO_ONE
)paren
comma
id|OPT_BIT
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|NULL
comma
op_amp
id|pack_everything
comma
id|N_
c_func
(paren
l_string|&quot;same as -a, and turn unreachable objects loose&quot;
)paren
comma
id|LOOSEN_UNREACHABLE
op_or
id|ALL_INTO_ONE
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;d&squot;
comma
l_int|NULL
comma
op_amp
id|delete_redundant
comma
id|N_
c_func
(paren
l_string|&quot;remove redundant packs, and run git-prune-packed&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;f&squot;
comma
l_int|NULL
comma
op_amp
id|no_reuse_delta
comma
id|N_
c_func
(paren
l_string|&quot;pass --no-reuse-delta to git-pack-objects&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;F&squot;
comma
l_int|NULL
comma
op_amp
id|no_reuse_object
comma
id|N_
c_func
(paren
l_string|&quot;pass --no-reuse-object to git-pack-objects&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;n&squot;
comma
l_int|NULL
comma
op_amp
id|no_update_server_info
comma
id|N_
c_func
(paren
l_string|&quot;do not run git-update-server-info&quot;
)paren
)paren
comma
id|OPT__QUIET
c_func
(paren
op_amp
id|quiet
comma
id|N_
c_func
(paren
l_string|&quot;be quiet&quot;
)paren
)paren
comma
id|OPT_BOOL
c_func
(paren
l_char|&squot;l&squot;
comma
l_string|&quot;local&quot;
comma
op_amp
id|local
comma
id|N_
c_func
(paren
l_string|&quot;pass --local to git-pack-objects&quot;
)paren
)paren
comma
id|OPT_STRING
c_func
(paren
l_int|0
comma
l_string|&quot;unpack-unreachable&quot;
comma
op_amp
id|unpack_unreachable
comma
id|N_
c_func
(paren
l_string|&quot;approxidate&quot;
)paren
comma
id|N_
c_func
(paren
l_string|&quot;with -A, do not loosen objects older than this&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;window&quot;
comma
op_amp
id|window
comma
id|N_
c_func
(paren
l_string|&quot;size of the window used for delta compression&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;window-memory&quot;
comma
op_amp
id|window_memory
comma
id|N_
c_func
(paren
l_string|&quot;same as the above, but limit memory size instead of entries count&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;depth&quot;
comma
op_amp
id|depth
comma
id|N_
c_func
(paren
l_string|&quot;limits the maximum delta depth&quot;
)paren
)paren
comma
id|OPT_INTEGER
c_func
(paren
l_int|0
comma
l_string|&quot;max-pack-size&quot;
comma
op_amp
id|max_pack_size
comma
id|N_
c_func
(paren
l_string|&quot;maximum size of each packfile&quot;
)paren
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
id|repack_config
comma
l_int|NULL
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
id|builtin_repack_options
comma
id|git_repack_usage
comma
l_int|0
)paren
suffix:semicolon
id|packdir
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/pack&quot;
comma
id|get_object_directory
c_func
(paren
)paren
)paren
suffix:semicolon
id|packtmp
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/.tmp-%d-pack&quot;
comma
id|packdir
comma
(paren
r_int
)paren
id|getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|sigchain_push_common
c_func
(paren
id|remove_pack_on_signal
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;pack-objects&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--keep-true-parents&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--honor-pack-keep&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--non-empty&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--all&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--reflog&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|window
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--window=%u&quot;
comma
id|window
)paren
suffix:semicolon
r_if
c_cond
(paren
id|window_memory
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--window-memory=%u&quot;
comma
id|window_memory
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--depth=%u&quot;
comma
id|depth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_pack_size
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--max_pack_size=%u&quot;
comma
id|max_pack_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_reuse_delta
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--no-reuse-delta&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|no_reuse_object
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--no-reuse-object&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pack_everything
op_amp
id|ALL_INTO_ONE
)paren
(brace
id|get_non_kept_pack_filenames
c_func
(paren
op_amp
id|existing_packs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|existing_packs.nr
op_logical_and
id|delete_redundant
)paren
(brace
r_if
c_cond
(paren
id|unpack_unreachable
)paren
id|argv_array_pushf
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--unpack-unreachable=%s&quot;
comma
id|unpack_unreachable
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pack_everything
op_amp
id|LOOSEN_UNREACHABLE
)paren
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--unpack-unreachable&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--unpacked&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--incremental&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|local
)paren
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--local&quot;
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
id|cmd_args
comma
l_string|&quot;--quiet&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta_base_offset
)paren
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;--delta-base-offset&quot;
)paren
suffix:semicolon
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
id|packtmp
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cmd
comma
l_int|0
comma
r_sizeof
(paren
id|cmd
)paren
)paren
suffix:semicolon
id|cmd.argv
op_assign
id|cmd_args.argv
suffix:semicolon
id|cmd.git_cmd
op_assign
l_int|1
suffix:semicolon
id|cmd.out
op_assign
l_int|1
suffix:semicolon
id|cmd.no_stdin
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|start_command
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|nr_packs
op_assign
l_int|0
suffix:semicolon
id|out
op_assign
id|xfdopen
c_func
(paren
id|cmd.out
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|strbuf_getline
c_func
(paren
op_amp
id|line
comma
id|out
comma
l_char|&squot;&bslash;n&squot;
)paren
op_ne
id|EOF
)paren
(brace
r_if
c_cond
(paren
id|line.len
op_ne
l_int|40
)paren
id|die
c_func
(paren
l_string|&quot;repack: Expecting 40 character sha1 lines only from pack-objects.&quot;
)paren
suffix:semicolon
id|string_list_append
c_func
(paren
op_amp
id|names
comma
id|line.buf
)paren
suffix:semicolon
id|nr_packs
op_increment
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|out
)paren
suffix:semicolon
id|ret
op_assign
id|finish_command
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|argv_array_clear
c_func
(paren
op_amp
id|cmd_args
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_packs
op_logical_and
op_logical_neg
id|quiet
)paren
id|printf
c_func
(paren
l_string|&quot;Nothing new to pack.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ok we have prepared all new packfiles.&n;&t; * First see if there are packs of the same name and if so&n;&t; * if we can move them out of the way (this can happen if we&n;&t; * repacked immediately after packing fully.&n;&t; */
id|failed
op_assign
l_int|0
suffix:semicolon
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|names
)paren
(brace
r_for
c_loop
(paren
id|ext
op_assign
l_int|0
suffix:semicolon
id|ext
OL
l_int|2
suffix:semicolon
id|ext
op_increment
)paren
(brace
r_char
op_star
id|fname
comma
op_star
id|fname_old
suffix:semicolon
id|fname
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/%s%s&quot;
comma
id|packdir
comma
id|item-&gt;string
comma
id|exts
(braket
id|ext
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file_exists
c_func
(paren
id|fname
)paren
)paren
(brace
id|free
c_func
(paren
id|fname
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fname_old
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s/old-%s%s&quot;
comma
id|packdir
comma
id|item-&gt;string
comma
id|exts
(braket
id|ext
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file_exists
c_func
(paren
id|fname_old
)paren
)paren
r_if
c_cond
(paren
id|unlink
c_func
(paren
id|fname_old
)paren
)paren
id|failed
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|failed
op_logical_and
id|rename
c_func
(paren
id|fname
comma
id|fname_old
)paren
)paren
(brace
id|free
c_func
(paren
id|fname
)paren
suffix:semicolon
id|failed
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|string_list_append
c_func
(paren
op_amp
id|rollback
comma
id|fname
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|failed
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|failed
)paren
(brace
r_struct
id|string_list
id|rollback_failure
op_assign
id|STRING_LIST_INIT_DUP
suffix:semicolon
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|rollback
)paren
(brace
r_char
op_star
id|fname
comma
op_star
id|fname_old
suffix:semicolon
id|fname
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
id|packdir
comma
id|item-&gt;string
)paren
suffix:semicolon
id|fname_old
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s/old-%s&quot;
comma
id|packdir
comma
id|item-&gt;string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rename
c_func
(paren
id|fname_old
comma
id|fname
)paren
)paren
id|string_list_append
c_func
(paren
op_amp
id|rollback_failure
comma
id|fname
)paren
suffix:semicolon
id|free
c_func
(paren
id|fname
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rollback_failure.nr
)paren
(brace
r_int
id|i
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;WARNING: Some packs in use have been renamed by&bslash;n&quot;
l_string|&quot;WARNING: prefixing old- to their name, in order to&bslash;n&quot;
l_string|&quot;WARNING: replace them with the new version of the&bslash;n&quot;
l_string|&quot;WARNING: file.  But the operation failed, and the&bslash;n&quot;
l_string|&quot;WARNING: attempt to rename them back to their&bslash;n&quot;
l_string|&quot;WARNING: original names also failed.&bslash;n&quot;
l_string|&quot;WARNING: Please rename them in %s manually:&bslash;n&quot;
comma
id|packdir
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
id|rollback_failure.nr
suffix:semicolon
id|i
op_increment
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;WARNING:   old-%s -&gt; %s&bslash;n&quot;
comma
id|rollback_failure.items
(braket
id|i
)braket
dot
id|string
comma
id|rollback_failure.items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
)brace
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Now the ones with the same name are out of the way... */
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|names
)paren
(brace
r_for
c_loop
(paren
id|ext
op_assign
l_int|0
suffix:semicolon
id|ext
OL
l_int|2
suffix:semicolon
id|ext
op_increment
)paren
(brace
r_char
op_star
id|fname
comma
op_star
id|fname_old
suffix:semicolon
r_struct
id|stat
id|statbuffer
suffix:semicolon
id|fname
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s/pack-%s%s&quot;
comma
id|packdir
comma
id|item-&gt;string
comma
id|exts
(braket
id|ext
)braket
)paren
suffix:semicolon
id|fname_old
op_assign
id|mkpathdup
c_func
(paren
l_string|&quot;%s-%s%s&quot;
comma
id|packtmp
comma
id|item-&gt;string
comma
id|exts
(braket
id|ext
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
id|fname_old
comma
op_amp
id|statbuffer
)paren
)paren
(brace
id|statbuffer.st_mode
op_and_assign
op_complement
(paren
id|S_IWUSR
op_or
id|S_IWGRP
op_or
id|S_IWOTH
)paren
suffix:semicolon
id|chmod
c_func
(paren
id|fname_old
comma
id|statbuffer.st_mode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rename
c_func
(paren
id|fname_old
comma
id|fname
)paren
)paren
m_exit
(paren
id|errno
)paren
suffix:semicolon
id|free
c_func
(paren
id|fname
)paren
suffix:semicolon
id|free
c_func
(paren
id|fname_old
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Remove the &quot;old-&quot; files */
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|names
)paren
(brace
r_for
c_loop
(paren
id|ext
op_assign
l_int|0
suffix:semicolon
id|ext
OL
l_int|2
suffix:semicolon
id|ext
op_increment
)paren
(brace
r_char
op_star
id|fname
suffix:semicolon
id|fname
op_assign
id|mkpath
c_func
(paren
l_string|&quot;%s/old-pack-%s%s&quot;
comma
id|packdir
comma
id|item-&gt;string
comma
id|exts
(braket
id|ext
)braket
)paren
suffix:semicolon
id|remove_path
c_func
(paren
id|fname
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* End of pack replacement. */
r_if
c_cond
(paren
id|delete_redundant
)paren
(brace
id|sort_string_list
c_func
(paren
op_amp
id|names
)paren
suffix:semicolon
id|for_each_string_list_item
c_func
(paren
id|item
comma
op_amp
id|existing_packs
)paren
(brace
r_char
op_star
id|sha1
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|item-&gt;string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|40
)paren
r_continue
suffix:semicolon
id|sha1
op_assign
id|item-&gt;string
op_plus
id|len
l_int|40
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|string_list_has_string
c_func
(paren
op_amp
id|names
comma
id|sha1
)paren
)paren
id|remove_redundant_pack
c_func
(paren
id|packdir
comma
id|item-&gt;string
)paren
suffix:semicolon
)brace
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;prune-packed&quot;
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
id|cmd_args
comma
l_string|&quot;--quiet&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cmd
comma
l_int|0
comma
r_sizeof
(paren
id|cmd
)paren
)paren
suffix:semicolon
id|cmd.argv
op_assign
id|cmd_args.argv
suffix:semicolon
id|cmd.git_cmd
op_assign
l_int|1
suffix:semicolon
id|run_command
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
id|argv_array_clear
c_func
(paren
op_amp
id|cmd_args
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|no_update_server_info
)paren
(brace
id|argv_array_push
c_func
(paren
op_amp
id|cmd_args
comma
l_string|&quot;update-server-info&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cmd
comma
l_int|0
comma
r_sizeof
(paren
id|cmd
)paren
)paren
suffix:semicolon
id|cmd.argv
op_assign
id|cmd_args.argv
suffix:semicolon
id|cmd.git_cmd
op_assign
l_int|1
suffix:semicolon
id|run_command
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
id|argv_array_clear
c_func
(paren
op_amp
id|cmd_args
)paren
suffix:semicolon
)brace
id|remove_temporary_files
c_func
(paren
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|names
comma
l_int|0
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|rollback
comma
l_int|0
)paren
suffix:semicolon
id|string_list_clear
c_func
(paren
op_amp
id|existing_packs
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|line
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
