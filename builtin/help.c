multiline_comment|/*&n; * builtin-help.c&n; *&n; * Builtin help command&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;common-cmds.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;help.h&quot;
DECL|struct|man_viewer_list
r_static
r_struct
id|man_viewer_list
(brace
DECL|member|next
r_struct
id|man_viewer_list
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
DECL|variable|man_viewer_list
)brace
op_star
id|man_viewer_list
suffix:semicolon
DECL|struct|man_viewer_info_list
r_static
r_struct
id|man_viewer_info_list
(brace
DECL|member|next
r_struct
id|man_viewer_info_list
op_star
id|next
suffix:semicolon
DECL|member|info
r_const
r_char
op_star
id|info
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
DECL|variable|man_viewer_info_list
)brace
op_star
id|man_viewer_info_list
suffix:semicolon
DECL|enum|help_format
r_enum
id|help_format
(brace
DECL|enumerator|HELP_FORMAT_NONE
id|HELP_FORMAT_NONE
comma
DECL|enumerator|HELP_FORMAT_MAN
id|HELP_FORMAT_MAN
comma
DECL|enumerator|HELP_FORMAT_INFO
id|HELP_FORMAT_INFO
comma
DECL|enumerator|HELP_FORMAT_WEB
id|HELP_FORMAT_WEB
)brace
suffix:semicolon
DECL|variable|show_all
r_static
r_int
id|show_all
op_assign
l_int|0
suffix:semicolon
DECL|variable|help_format
r_static
r_enum
id|help_format
id|help_format
op_assign
id|HELP_FORMAT_NONE
suffix:semicolon
DECL|variable|builtin_help_options
r_static
r_struct
id|option
id|builtin_help_options
(braket
)braket
op_assign
(brace
id|OPT_BOOLEAN
c_func
(paren
l_char|&squot;a&squot;
comma
l_string|&quot;all&quot;
comma
op_amp
id|show_all
comma
l_string|&quot;print all available commands&quot;
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;m&squot;
comma
l_string|&quot;man&quot;
comma
op_amp
id|help_format
comma
l_string|&quot;show man page&quot;
comma
id|HELP_FORMAT_MAN
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;w&squot;
comma
l_string|&quot;web&quot;
comma
op_amp
id|help_format
comma
l_string|&quot;show manual in web browser&quot;
comma
id|HELP_FORMAT_WEB
)paren
comma
id|OPT_SET_INT
c_func
(paren
l_char|&squot;i&squot;
comma
l_string|&quot;info&quot;
comma
op_amp
id|help_format
comma
l_string|&quot;show info page&quot;
comma
id|HELP_FORMAT_INFO
)paren
comma
id|OPT_END
c_func
(paren
)paren
comma
)brace
suffix:semicolon
DECL|variable|builtin_help_usage
r_static
r_const
r_char
op_star
r_const
id|builtin_help_usage
(braket
)braket
op_assign
(brace
l_string|&quot;git help [--all] [--man|--web|--info] [command]&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|parse_help_format
r_static
r_enum
id|help_format
id|parse_help_format
c_func
(paren
r_const
r_char
op_star
id|format
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;man&quot;
)paren
)paren
r_return
id|HELP_FORMAT_MAN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;info&quot;
)paren
)paren
r_return
id|HELP_FORMAT_INFO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;web&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|format
comma
l_string|&quot;html&quot;
)paren
)paren
r_return
id|HELP_FORMAT_WEB
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;unrecognized help format &squot;%s&squot;&quot;
comma
id|format
)paren
suffix:semicolon
)brace
DECL|function|get_man_viewer_info
r_static
r_const
r_char
op_star
id|get_man_viewer_info
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|man_viewer_info_list
op_star
id|viewer
suffix:semicolon
r_for
c_loop
(paren
id|viewer
op_assign
id|man_viewer_info_list
suffix:semicolon
id|viewer
suffix:semicolon
id|viewer
op_assign
id|viewer-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|name
comma
id|viewer-&gt;name
)paren
)paren
r_return
id|viewer-&gt;info
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|check_emacsclient_version
r_static
r_int
id|check_emacsclient_version
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|buffer
op_assign
id|STRBUF_INIT
suffix:semicolon
r_struct
id|child_process
id|ec_process
suffix:semicolon
r_const
r_char
op_star
id|argv_ec
(braket
)braket
op_assign
(brace
l_string|&quot;emacsclient&quot;
comma
l_string|&quot;--version&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|version
suffix:semicolon
multiline_comment|/* emacsclient prints its version number on stderr */
id|memset
c_func
(paren
op_amp
id|ec_process
comma
l_int|0
comma
r_sizeof
(paren
id|ec_process
)paren
)paren
suffix:semicolon
id|ec_process.argv
op_assign
id|argv_ec
suffix:semicolon
id|ec_process.err
op_assign
l_int|1
suffix:semicolon
id|ec_process.stdout_to_stderr
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|ec_process
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Failed to start emacsclient.&quot;
)paren
suffix:semicolon
id|strbuf_read
c_func
(paren
op_amp
id|buffer
comma
id|ec_process.err
comma
l_int|20
)paren
suffix:semicolon
id|close
c_func
(paren
id|ec_process.err
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t bother checking return value, because &quot;emacsclient --version&quot;&n;&t; * seems to always exits with code 1.&n;&t; */
id|finish_command
c_func
(paren
op_amp
id|ec_process
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|buffer.buf
comma
l_string|&quot;emacsclient&quot;
)paren
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;Failed to parse emacsclient version.&quot;
)paren
suffix:semicolon
)brace
id|strbuf_remove
c_func
(paren
op_amp
id|buffer
comma
l_int|0
comma
id|strlen
c_func
(paren
l_string|&quot;emacsclient&quot;
)paren
)paren
suffix:semicolon
id|version
op_assign
id|atoi
c_func
(paren
id|buffer.buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|version
OL
l_int|22
)paren
(brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
id|error
c_func
(paren
l_string|&quot;emacsclient version &squot;%d&squot; too old (&lt; 22).&quot;
comma
id|version
)paren
suffix:semicolon
)brace
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exec_woman_emacs
r_static
r_void
id|exec_woman_emacs
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|check_emacsclient_version
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* This works only with emacsclient version &gt;= 22. */
r_struct
id|strbuf
id|man_page
op_assign
id|STRBUF_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|path
op_assign
l_string|&quot;emacsclient&quot;
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|man_page
comma
l_string|&quot;(woman &bslash;&quot;%s&bslash;&quot;)&quot;
comma
id|page
)paren
suffix:semicolon
id|execlp
c_func
(paren
id|path
comma
l_string|&quot;emacsclient&quot;
comma
l_string|&quot;-e&quot;
comma
id|man_page.buf
comma
l_int|NULL
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;failed to exec &squot;%s&squot;: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|exec_man_konqueror
r_static
r_void
id|exec_man_konqueror
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|page
)paren
(brace
r_const
r_char
op_star
id|display
op_assign
id|getenv
c_func
(paren
l_string|&quot;DISPLAY&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|display
op_logical_and
op_star
id|display
)paren
(brace
r_struct
id|strbuf
id|man_page
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|filename
op_assign
l_string|&quot;kfmclient&quot;
suffix:semicolon
multiline_comment|/* It&squot;s simpler to launch konqueror using kfmclient. */
r_if
c_cond
(paren
id|path
)paren
(brace
r_const
r_char
op_star
id|file
op_assign
id|strrchr
c_func
(paren
id|path
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|file
op_plus
l_int|1
comma
l_string|&quot;konqueror&quot;
)paren
)paren
(brace
r_char
op_star
r_new
op_assign
id|xstrdup
c_func
(paren
id|path
)paren
suffix:semicolon
r_char
op_star
id|dest
op_assign
id|strrchr
c_func
(paren
r_new
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
multiline_comment|/* strlen(&quot;konqueror&quot;) == strlen(&quot;kfmclient&quot;) */
id|strcpy
c_func
(paren
id|dest
op_plus
l_int|1
comma
l_string|&quot;kfmclient&quot;
)paren
suffix:semicolon
id|path
op_assign
r_new
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file
)paren
id|filename
op_assign
id|file
suffix:semicolon
)brace
r_else
id|path
op_assign
l_string|&quot;kfmclient&quot;
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|man_page
comma
l_string|&quot;man:%s(1)&quot;
comma
id|page
)paren
suffix:semicolon
id|execlp
c_func
(paren
id|path
comma
id|filename
comma
l_string|&quot;newTab&quot;
comma
id|man_page.buf
comma
l_int|NULL
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;failed to exec &squot;%s&squot;: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|exec_man_man
r_static
r_void
id|exec_man_man
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
id|path
op_assign
l_string|&quot;man&quot;
suffix:semicolon
id|execlp
c_func
(paren
id|path
comma
l_string|&quot;man&quot;
comma
id|page
comma
l_int|NULL
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;failed to exec &squot;%s&squot;: %s&quot;
comma
id|path
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|exec_man_cmd
r_static
r_void
id|exec_man_cmd
c_func
(paren
r_const
r_char
op_star
id|cmd
comma
r_const
r_char
op_star
id|page
)paren
(brace
r_struct
id|strbuf
id|shell_cmd
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addf
c_func
(paren
op_amp
id|shell_cmd
comma
l_string|&quot;%s %s&quot;
comma
id|cmd
comma
id|page
)paren
suffix:semicolon
id|execl
c_func
(paren
l_string|&quot;/bin/sh&quot;
comma
l_string|&quot;sh&quot;
comma
l_string|&quot;-c&quot;
comma
id|shell_cmd.buf
comma
l_int|NULL
)paren
suffix:semicolon
id|warning
c_func
(paren
l_string|&quot;failed to exec &squot;%s&squot;: %s&quot;
comma
id|cmd
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
DECL|function|add_man_viewer
r_static
r_void
id|add_man_viewer
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|man_viewer_list
op_star
op_star
id|p
op_assign
op_amp
id|man_viewer_list
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
id|p
op_assign
op_amp
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|p
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
(paren
r_sizeof
(paren
op_star
op_star
id|p
)paren
op_plus
id|len
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|name
comma
id|name
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|supported_man_viewer
r_static
r_int
id|supported_man_viewer
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
r_return
(paren
op_logical_neg
id|strncasecmp
c_func
(paren
l_string|&quot;man&quot;
comma
id|name
comma
id|len
)paren
op_logical_or
op_logical_neg
id|strncasecmp
c_func
(paren
l_string|&quot;woman&quot;
comma
id|name
comma
id|len
)paren
op_logical_or
op_logical_neg
id|strncasecmp
c_func
(paren
l_string|&quot;konqueror&quot;
comma
id|name
comma
id|len
)paren
)paren
suffix:semicolon
)brace
DECL|function|do_add_man_viewer_info
r_static
r_void
id|do_add_man_viewer_info
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_struct
id|man_viewer_info_list
op_star
r_new
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
r_new
)paren
op_plus
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|strncpy
c_func
(paren
r_new
op_member_access_from_pointer
id|name
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|info
op_assign
id|xstrdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
id|man_viewer_info_list
suffix:semicolon
id|man_viewer_info_list
op_assign
r_new
suffix:semicolon
)brace
DECL|function|add_man_viewer_path
r_static
r_int
id|add_man_viewer_path
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
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
id|supported_man_viewer
c_func
(paren
id|name
comma
id|len
)paren
)paren
id|do_add_man_viewer_info
c_func
(paren
id|name
comma
id|len
comma
id|value
)paren
suffix:semicolon
r_else
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: path for unsupported man viewer.&bslash;n&quot;
l_string|&quot;Please consider using &squot;man.&lt;tool&gt;.cmd&squot; instead.&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_man_viewer_cmd
r_static
r_int
id|add_man_viewer_cmd
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
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
id|supported_man_viewer
c_func
(paren
id|name
comma
id|len
)paren
)paren
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: cmd for supported man viewer.&bslash;n&quot;
l_string|&quot;Please consider using &squot;man.&lt;tool&gt;.path&squot; instead.&quot;
comma
id|name
)paren
suffix:semicolon
r_else
id|do_add_man_viewer_info
c_func
(paren
id|name
comma
id|len
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_man_viewer_info
r_static
r_int
id|add_man_viewer_info
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
id|name
op_assign
id|var
op_plus
l_int|4
suffix:semicolon
r_const
r_char
op_star
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
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|subkey
comma
l_string|&quot;.path&quot;
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
r_return
id|add_man_viewer_path
c_func
(paren
id|name
comma
id|subkey
id|name
comma
id|value
)paren
suffix:semicolon
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
l_string|&quot;.cmd&quot;
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
r_return
id|add_man_viewer_cmd
c_func
(paren
id|name
comma
id|subkey
id|name
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_help_config
r_static
r_int
id|git_help_config
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
l_string|&quot;help.format&quot;
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
id|help_format
op_assign
id|parse_help_format
c_func
(paren
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
l_string|&quot;man.viewer&quot;
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
id|add_man_viewer
c_func
(paren
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
id|prefixcmp
c_func
(paren
id|var
comma
l_string|&quot;man.&quot;
)paren
)paren
r_return
id|add_man_viewer_info
c_func
(paren
id|var
comma
id|value
)paren
suffix:semicolon
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
DECL|variable|main_cmds
DECL|variable|other_cmds
r_static
r_struct
id|cmdnames
id|main_cmds
comma
id|other_cmds
suffix:semicolon
DECL|function|list_common_cmds_help
r_void
id|list_common_cmds_help
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|longest
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
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|longest
OL
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
)paren
id|longest
op_assign
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
id|puts
c_func
(paren
l_string|&quot;The most commonly used git commands are:&quot;
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
id|ARRAY_SIZE
c_func
(paren
id|common_cmds
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;   %s   &quot;
comma
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|mput_char
c_func
(paren
l_char|&squot; &squot;
comma
id|longest
id|strlen
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|name
)paren
)paren
suffix:semicolon
id|puts
c_func
(paren
id|common_cmds
(braket
id|i
)braket
dot
id|help
)paren
suffix:semicolon
)brace
)brace
DECL|function|is_git_command
r_static
r_int
id|is_git_command
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_return
id|is_in_cmdlist
c_func
(paren
op_amp
id|main_cmds
comma
id|s
)paren
op_logical_or
id|is_in_cmdlist
c_func
(paren
op_amp
id|other_cmds
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|prepend
r_static
r_const
r_char
op_star
id|prepend
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|cmd
)paren
(brace
r_int
id|pre_len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
r_int
id|cmd_len
op_assign
id|strlen
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_char
op_star
id|p
op_assign
id|xmalloc
c_func
(paren
id|pre_len
op_plus
id|cmd_len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|prefix
comma
id|pre_len
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
op_plus
id|pre_len
comma
id|cmd
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|cmd_to_page
r_static
r_const
r_char
op_star
id|cmd_to_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|git_cmd
)paren
r_return
l_string|&quot;git&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefixcmp
c_func
(paren
id|git_cmd
comma
l_string|&quot;git&quot;
)paren
)paren
r_return
id|git_cmd
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_git_command
c_func
(paren
id|git_cmd
)paren
)paren
r_return
id|prepend
c_func
(paren
l_string|&quot;git-&quot;
comma
id|git_cmd
)paren
suffix:semicolon
r_else
r_return
id|prepend
c_func
(paren
l_string|&quot;git&quot;
comma
id|git_cmd
)paren
suffix:semicolon
)brace
DECL|function|setup_man_path
r_static
r_void
id|setup_man_path
c_func
(paren
r_void
)paren
(brace
r_struct
id|strbuf
id|new_path
op_assign
id|STRBUF_INIT
suffix:semicolon
r_const
r_char
op_star
id|old_path
op_assign
id|getenv
c_func
(paren
l_string|&quot;MANPATH&quot;
)paren
suffix:semicolon
multiline_comment|/* We should always put &squot;:&squot; after our path. If there is no&n;&t; * old_path, the &squot;:&squot; at the end will let &squot;man&squot; to try&n;&t; * system-wide paths after ours to find the manual page. If&n;&t; * there is old_path, we need &squot;:&squot; as delimiter. */
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
id|system_path
c_func
(paren
id|GIT_MAN_PATH
)paren
)paren
suffix:semicolon
id|strbuf_addch
c_func
(paren
op_amp
id|new_path
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_path
)paren
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
id|old_path
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;MANPATH&quot;
comma
id|new_path.buf
comma
l_int|1
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|new_path
)paren
suffix:semicolon
)brace
DECL|function|exec_viewer
r_static
r_void
id|exec_viewer
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|page
)paren
(brace
r_const
r_char
op_star
id|info
op_assign
id|get_man_viewer_info
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|name
comma
l_string|&quot;man&quot;
)paren
)paren
id|exec_man_man
c_func
(paren
id|info
comma
id|page
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|name
comma
l_string|&quot;woman&quot;
)paren
)paren
id|exec_woman_emacs
c_func
(paren
id|info
comma
id|page
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcasecmp
c_func
(paren
id|name
comma
l_string|&quot;konqueror&quot;
)paren
)paren
id|exec_man_konqueror
c_func
(paren
id|info
comma
id|page
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|info
)paren
id|exec_man_cmd
c_func
(paren
id|info
comma
id|page
)paren
suffix:semicolon
r_else
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: unknown man viewer.&quot;
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|show_man_page
r_static
r_void
id|show_man_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_struct
id|man_viewer_list
op_star
id|viewer
suffix:semicolon
r_const
r_char
op_star
id|page
op_assign
id|cmd_to_page
c_func
(paren
id|git_cmd
)paren
suffix:semicolon
r_const
r_char
op_star
id|fallback
op_assign
id|getenv
c_func
(paren
l_string|&quot;GIT_MAN_VIEWER&quot;
)paren
suffix:semicolon
id|setup_man_path
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|viewer
op_assign
id|man_viewer_list
suffix:semicolon
id|viewer
suffix:semicolon
id|viewer
op_assign
id|viewer-&gt;next
)paren
(brace
id|exec_viewer
c_func
(paren
id|viewer-&gt;name
comma
id|page
)paren
suffix:semicolon
multiline_comment|/* will return when unable */
)brace
r_if
c_cond
(paren
id|fallback
)paren
id|exec_viewer
c_func
(paren
id|fallback
comma
id|page
)paren
suffix:semicolon
id|exec_viewer
c_func
(paren
l_string|&quot;man&quot;
comma
id|page
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;no man viewer handled the request&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_info_page
r_static
r_void
id|show_info_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_const
r_char
op_star
id|page
op_assign
id|cmd_to_page
c_func
(paren
id|git_cmd
)paren
suffix:semicolon
id|setenv
c_func
(paren
l_string|&quot;INFOPATH&quot;
comma
id|system_path
c_func
(paren
id|GIT_INFO_PATH
)paren
comma
l_int|1
)paren
suffix:semicolon
id|execlp
c_func
(paren
l_string|&quot;info&quot;
comma
l_string|&quot;info&quot;
comma
l_string|&quot;gitman&quot;
comma
id|page
comma
l_int|NULL
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;no info viewer handled the request&quot;
)paren
suffix:semicolon
)brace
DECL|function|get_html_page_path
r_static
r_void
id|get_html_page_path
c_func
(paren
r_struct
id|strbuf
op_star
id|page_path
comma
r_const
r_char
op_star
id|page
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_const
r_char
op_star
id|html_path
op_assign
id|system_path
c_func
(paren
id|GIT_HTML_PATH
)paren
suffix:semicolon
multiline_comment|/* Check that we have a git documentation directory. */
r_if
c_cond
(paren
id|stat
c_func
(paren
id|mkpath
c_func
(paren
l_string|&quot;%s/git.html&quot;
comma
id|html_path
)paren
comma
op_amp
id|st
)paren
op_logical_or
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
)paren
id|die
c_func
(paren
l_string|&quot;&squot;%s&squot;: not a documentation directory.&quot;
comma
id|html_path
)paren
suffix:semicolon
id|strbuf_init
c_func
(paren
id|page_path
comma
l_int|0
)paren
suffix:semicolon
id|strbuf_addf
c_func
(paren
id|page_path
comma
l_string|&quot;%s/%s.html&quot;
comma
id|html_path
comma
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If open_html is not defined in a platform-specific way (see for&n; * example compat/mingw.h), we use the script web--browse to display&n; * HTML.&n; */
macro_line|#ifndef open_html
DECL|function|open_html
r_static
r_void
id|open_html
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
id|execl_git_cmd
c_func
(paren
l_string|&quot;web--browse&quot;
comma
l_string|&quot;-c&quot;
comma
l_string|&quot;help.browser&quot;
comma
id|path
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|show_html_page
r_static
r_void
id|show_html_page
c_func
(paren
r_const
r_char
op_star
id|git_cmd
)paren
(brace
r_const
r_char
op_star
id|page
op_assign
id|cmd_to_page
c_func
(paren
id|git_cmd
)paren
suffix:semicolon
r_struct
id|strbuf
id|page_path
suffix:semicolon
multiline_comment|/* it leaks but we exec bellow */
id|get_html_page_path
c_func
(paren
op_amp
id|page_path
comma
id|page
)paren
suffix:semicolon
id|open_html
c_func
(paren
id|page_path.buf
)paren
suffix:semicolon
)brace
DECL|function|cmd_help
r_int
id|cmd_help
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
id|nongit
suffix:semicolon
r_const
r_char
op_star
id|alias
suffix:semicolon
r_enum
id|help_format
id|parsed_help_format
suffix:semicolon
id|load_command_list
c_func
(paren
l_string|&quot;git-&quot;
comma
op_amp
id|main_cmds
comma
op_amp
id|other_cmds
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
id|builtin_help_options
comma
id|builtin_help_usage
comma
l_int|0
)paren
suffix:semicolon
id|parsed_help_format
op_assign
id|help_format
suffix:semicolon
r_if
c_cond
(paren
id|show_all
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;usage: %s&bslash;n&bslash;n&quot;
comma
id|git_usage_string
)paren
suffix:semicolon
id|list_commands
c_func
(paren
l_string|&quot;git commands&quot;
comma
op_amp
id|main_cmds
comma
op_amp
id|other_cmds
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|git_more_info_string
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
id|argv
(braket
l_int|0
)braket
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;usage: %s&bslash;n&bslash;n&quot;
comma
id|git_usage_string
)paren
suffix:semicolon
id|list_common_cmds_help
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|git_more_info_string
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|setup_git_directory_gently
c_func
(paren
op_amp
id|nongit
)paren
suffix:semicolon
id|git_config
c_func
(paren
id|git_help_config
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parsed_help_format
op_ne
id|HELP_FORMAT_NONE
)paren
id|help_format
op_assign
id|parsed_help_format
suffix:semicolon
id|alias
op_assign
id|alias_lookup
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alias
op_logical_and
op_logical_neg
id|is_git_command
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;`git %s&squot; is aliased to `%s&squot;&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|alias
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|help_format
)paren
(brace
r_case
id|HELP_FORMAT_NONE
suffix:colon
r_case
id|HELP_FORMAT_MAN
suffix:colon
id|show_man_page
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HELP_FORMAT_INFO
suffix:colon
id|show_info_page
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HELP_FORMAT_WEB
suffix:colon
id|show_html_page
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
