multiline_comment|/*&n; * builtin-help.c&n; *&n; * Builtin help-related commands (help, usage, version)&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;exec_cmd.h&quot;
macro_line|#include &quot;common-cmds.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
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
DECL|enumerator|HELP_FORMAT_MAN
id|HELP_FORMAT_MAN
comma
DECL|enumerator|HELP_FORMAT_INFO
id|HELP_FORMAT_INFO
comma
DECL|enumerator|HELP_FORMAT_WEB
id|HELP_FORMAT_WEB
comma
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
id|HELP_FORMAT_MAN
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
l_string|&quot;git-help [--all] [--man|--web|--info] [command]&quot;
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
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to start emacsclient.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to parse emacsclient version.&bslash;n&quot;
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|1
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
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;emacsclient version &squot;%d&squot; too old (&lt; 22).&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|buffer
)paren
suffix:semicolon
r_return
l_int|1
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
DECL|function|do_add_man_viewer
r_static
r_void
id|do_add_man_viewer
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
DECL|function|add_man_viewer
r_static
r_int
id|add_man_viewer
c_func
(paren
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
id|value
comma
id|strlen
c_func
(paren
id|value
)paren
)paren
)paren
id|do_add_man_viewer
c_func
(paren
id|value
)paren
suffix:semicolon
r_else
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: unsupported man viewer.&quot;
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
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
l_string|&quot;&squot;%s&squot;: path for unsupported man viewer.&quot;
comma
id|name
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
id|error
c_func
(paren
l_string|&quot;Config with no key for man viewer: %s&quot;
comma
id|name
)paren
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
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: unsupported man viewer sub key.&quot;
comma
id|subkey
)paren
suffix:semicolon
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
r_return
id|add_man_viewer
c_func
(paren
id|value
)paren
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
)paren
suffix:semicolon
)brace
multiline_comment|/* most GUI terminals set COLUMNS (although some don&squot;t export it) */
DECL|function|term_columns
r_static
r_int
id|term_columns
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|col_string
op_assign
id|getenv
c_func
(paren
l_string|&quot;COLUMNS&quot;
)paren
suffix:semicolon
r_int
id|n_cols
suffix:semicolon
r_if
c_cond
(paren
id|col_string
op_logical_and
(paren
id|n_cols
op_assign
id|atoi
c_func
(paren
id|col_string
)paren
)paren
OG
l_int|0
)paren
r_return
id|n_cols
suffix:semicolon
macro_line|#ifdef TIOCGWINSZ
(brace
r_struct
id|winsize
id|ws
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioctl
c_func
(paren
l_int|1
comma
id|TIOCGWINSZ
comma
op_amp
id|ws
)paren
)paren
(brace
r_if
c_cond
(paren
id|ws.ws_col
)paren
r_return
id|ws.ws_col
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|80
suffix:semicolon
)brace
DECL|function|mput_char
r_static
r_inline
r_void
id|mput_char
c_func
(paren
r_char
id|c
comma
r_int
r_int
id|num
)paren
(brace
r_while
c_loop
(paren
id|num
op_decrement
)paren
(brace
id|putchar
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
DECL|struct|cmdnames
r_static
r_struct
id|cmdnames
(brace
DECL|member|alloc
r_int
id|alloc
suffix:semicolon
DECL|member|cnt
r_int
id|cnt
suffix:semicolon
DECL|struct|cmdname
r_struct
id|cmdname
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|names
)brace
op_star
op_star
id|names
suffix:semicolon
DECL|variable|main_cmds
DECL|variable|other_cmds
)brace
id|main_cmds
comma
id|other_cmds
suffix:semicolon
DECL|function|add_cmdname
r_static
r_void
id|add_cmdname
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_struct
id|cmdname
op_star
id|ent
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ent
)paren
op_plus
id|len
)paren
suffix:semicolon
id|ent-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|ent-&gt;name
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|ent-&gt;name
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|ALLOC_GROW
c_func
(paren
id|cmds-&gt;names
comma
id|cmds-&gt;cnt
op_plus
l_int|1
comma
id|cmds-&gt;alloc
)paren
suffix:semicolon
id|cmds-&gt;names
(braket
id|cmds-&gt;cnt
op_increment
)braket
op_assign
id|ent
suffix:semicolon
)brace
DECL|function|cmdname_compare
r_static
r_int
id|cmdname_compare
c_func
(paren
r_const
r_void
op_star
id|a_
comma
r_const
r_void
op_star
id|b_
)paren
(brace
r_struct
id|cmdname
op_star
id|a
op_assign
op_star
(paren
r_struct
id|cmdname
op_star
op_star
)paren
id|a_
suffix:semicolon
r_struct
id|cmdname
op_star
id|b
op_assign
op_star
(paren
r_struct
id|cmdname
op_star
op_star
)paren
id|b_
suffix:semicolon
r_return
id|strcmp
c_func
(paren
id|a-&gt;name
comma
id|b-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|uniq
r_static
r_void
id|uniq
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmds-&gt;cnt
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|cmds-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cmds-&gt;names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|cmds-&gt;names
(braket
id|i
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|name
)paren
)paren
id|cmds-&gt;names
(braket
id|j
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|i
)braket
suffix:semicolon
id|cmds-&gt;cnt
op_assign
id|j
suffix:semicolon
)brace
DECL|function|exclude_cmds
r_static
r_void
id|exclude_cmds
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_struct
id|cmdnames
op_star
id|excludes
)paren
(brace
r_int
id|ci
comma
id|cj
comma
id|ei
suffix:semicolon
r_int
id|cmp
suffix:semicolon
id|ci
op_assign
id|cj
op_assign
id|ei
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ci
OL
id|cmds-&gt;cnt
op_logical_and
id|ei
OL
id|excludes-&gt;cnt
)paren
(brace
id|cmp
op_assign
id|strcmp
c_func
(paren
id|cmds-&gt;names
(braket
id|ci
)braket
op_member_access_from_pointer
id|name
comma
id|excludes-&gt;names
(braket
id|ei
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
id|cmds-&gt;names
(braket
id|cj
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmp
op_eq
l_int|0
)paren
id|ci
op_increment
comma
id|ei
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmp
OG
l_int|0
)paren
id|ei
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ci
OL
id|cmds-&gt;cnt
)paren
id|cmds-&gt;names
(braket
id|cj
op_increment
)braket
op_assign
id|cmds-&gt;names
(braket
id|ci
op_increment
)braket
suffix:semicolon
id|cmds-&gt;cnt
op_assign
id|cj
suffix:semicolon
)brace
DECL|function|pretty_print_string_list
r_static
r_void
id|pretty_print_string_list
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_int
id|longest
)paren
(brace
r_int
id|cols
op_assign
l_int|1
comma
id|rows
suffix:semicolon
r_int
id|space
op_assign
id|longest
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* min 1 SP between words */
r_int
id|max_cols
op_assign
id|term_columns
c_func
(paren
)paren
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t print *on* the edge */
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|space
OL
id|max_cols
)paren
id|cols
op_assign
id|max_cols
op_div
id|space
suffix:semicolon
id|rows
op_assign
(paren
id|cmds-&gt;cnt
op_plus
id|cols
l_int|1
)paren
op_div
id|cols
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
id|rows
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;  &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cols
suffix:semicolon
id|j
op_increment
)paren
(brace
r_int
id|n
op_assign
id|j
op_star
id|rows
op_plus
id|i
suffix:semicolon
r_int
id|size
op_assign
id|space
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
id|cmds-&gt;cnt
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|cols
op_minus
l_int|1
op_logical_or
id|n
op_plus
id|rows
op_ge
id|cmds-&gt;cnt
)paren
id|size
op_assign
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%-*s&quot;
comma
id|size
comma
id|cmds-&gt;names
(braket
id|n
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|list_commands_in_dir
r_static
r_int
r_int
id|list_commands_in_dir
c_func
(paren
r_struct
id|cmdnames
op_star
id|cmds
comma
r_const
r_char
op_star
id|path
)paren
(brace
r_int
r_int
id|longest
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|prefix
op_assign
l_string|&quot;git-&quot;
suffix:semicolon
r_int
id|prefix_len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|DIR
op_star
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
op_logical_or
id|chdir
c_func
(paren
id|path
)paren
)paren
r_return
l_int|0
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
r_struct
id|stat
id|st
suffix:semicolon
r_int
id|entlen
suffix:semicolon
r_if
c_cond
(paren
id|prefixcmp
c_func
(paren
id|de-&gt;d_name
comma
id|prefix
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|stat
c_func
(paren
id|de-&gt;d_name
comma
op_amp
id|st
)paren
op_logical_or
multiline_comment|/* stat, not lstat */
op_logical_neg
id|S_ISREG
c_func
(paren
id|st.st_mode
)paren
op_logical_or
op_logical_neg
(paren
id|st.st_mode
op_amp
id|S_IXUSR
)paren
)paren
r_continue
suffix:semicolon
id|entlen
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
id|prefix_len
suffix:semicolon
r_if
c_cond
(paren
id|has_extension
c_func
(paren
id|de-&gt;d_name
comma
l_string|&quot;.exe&quot;
)paren
)paren
id|entlen
op_sub_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|longest
OL
id|entlen
)paren
id|longest
op_assign
id|entlen
suffix:semicolon
id|add_cmdname
c_func
(paren
id|cmds
comma
id|de-&gt;d_name
op_plus
id|prefix_len
comma
id|entlen
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|longest
suffix:semicolon
)brace
DECL|function|load_command_list
r_static
r_int
r_int
id|load_command_list
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|longest
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_const
r_char
op_star
id|env_path
op_assign
id|getenv
c_func
(paren
l_string|&quot;PATH&quot;
)paren
suffix:semicolon
r_char
op_star
id|paths
comma
op_star
id|path
comma
op_star
id|colon
suffix:semicolon
r_const
r_char
op_star
id|exec_path
op_assign
id|git_exec_path
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exec_path
)paren
id|longest
op_assign
id|list_commands_in_dir
c_func
(paren
op_amp
id|main_cmds
comma
id|exec_path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|env_path
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;PATH not set&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|path
op_assign
id|paths
op_assign
id|xstrdup
c_func
(paren
id|env_path
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|colon
op_assign
id|strchr
c_func
(paren
id|path
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
op_star
id|colon
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|list_commands_in_dir
c_func
(paren
op_amp
id|other_cmds
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|longest
)paren
id|longest
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|colon
)paren
r_break
suffix:semicolon
id|path
op_assign
id|colon
op_plus
l_int|1
suffix:semicolon
)brace
id|free
c_func
(paren
id|paths
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|main_cmds.names
comma
id|main_cmds.cnt
comma
r_sizeof
(paren
op_star
id|main_cmds.names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
op_amp
id|main_cmds
)paren
suffix:semicolon
id|qsort
c_func
(paren
id|other_cmds.names
comma
id|other_cmds.cnt
comma
r_sizeof
(paren
op_star
id|other_cmds.names
)paren
comma
id|cmdname_compare
)paren
suffix:semicolon
id|uniq
c_func
(paren
op_amp
id|other_cmds
)paren
suffix:semicolon
id|exclude_cmds
c_func
(paren
op_amp
id|other_cmds
comma
op_amp
id|main_cmds
)paren
suffix:semicolon
r_return
id|longest
suffix:semicolon
)brace
DECL|function|list_commands
r_static
r_void
id|list_commands
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|longest
op_assign
id|load_command_list
c_func
(paren
)paren
suffix:semicolon
r_const
r_char
op_star
id|exec_path
op_assign
id|git_exec_path
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|main_cmds.cnt
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;available git commands in &squot;%s&squot;&bslash;n&quot;
comma
id|exec_path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;----------------------------&quot;
)paren
suffix:semicolon
id|mput_char
c_func
(paren
l_char|&squot;-&squot;
comma
id|strlen
c_func
(paren
id|exec_path
)paren
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|pretty_print_string_list
c_func
(paren
op_amp
id|main_cmds
comma
id|longest
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|other_cmds.cnt
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;git commands available from elsewhere on your $PATH&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;---------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
id|pretty_print_string_list
c_func
(paren
op_amp
id|other_cmds
comma
id|longest
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
)brace
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
DECL|function|is_in_cmdlist
r_static
r_int
id|is_in_cmdlist
c_func
(paren
r_struct
id|cmdnames
op_star
id|c
comma
r_const
r_char
op_star
id|s
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
id|c-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
id|c-&gt;names
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
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
id|load_command_list
c_func
(paren
)paren
suffix:semicolon
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
(brace
r_int
id|page_len
op_assign
id|strlen
c_func
(paren
id|git_cmd
)paren
op_plus
l_int|4
suffix:semicolon
r_char
op_star
id|p
op_assign
id|xmalloc
c_func
(paren
id|page_len
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
comma
l_string|&quot;git-&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
op_plus
l_int|4
comma
id|git_cmd
)paren
suffix:semicolon
id|p
(braket
id|page_len
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
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
id|strbuf_init
c_func
(paren
op_amp
id|new_path
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* We should always put &squot;:&squot; after our path. If there is no&n;&t; * old_path, the &squot;:&squot; at the end will let &squot;man&squot; to try&n;&t; * system-wide paths after ours to find the manual page. If&n;&t; * there is old_path, we need &squot;:&squot; as delimiter. */
id|strbuf_addstr
c_func
(paren
op_amp
id|new_path
comma
id|GIT_MAN_PATH
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
id|path
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
id|path
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
id|path
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
id|path
comma
id|page
)paren
suffix:semicolon
r_else
id|warning
c_func
(paren
l_string|&quot;&squot;%s&squot;: unsupported man viewer.&quot;
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
id|GIT_INFO_PATH
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
multiline_comment|/* Check that we have a git documentation directory. */
r_if
c_cond
(paren
id|stat
c_func
(paren
id|GIT_HTML_PATH
l_string|&quot;/git.html&quot;
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
id|GIT_HTML_PATH
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
id|GIT_HTML_PATH
l_string|&quot;/%s.html&quot;
comma
id|page
)paren
suffix:semicolon
)brace
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
id|execl_git_cmd
c_func
(paren
l_string|&quot;web--browse&quot;
comma
l_string|&quot;-c&quot;
comma
l_string|&quot;help.browser&quot;
comma
id|page_path.buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|help_unknown_cmd
r_void
id|help_unknown_cmd
c_func
(paren
r_const
r_char
op_star
id|cmd
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;git: &squot;%s&squot; is not a git-command. See &squot;git --help&squot;.&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cmd_version
r_int
id|cmd_version
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
id|printf
c_func
(paren
l_string|&quot;git version %s&bslash;n&quot;
comma
id|git_version_string
)paren
suffix:semicolon
r_return
l_int|0
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
id|builtin_help_options
comma
id|builtin_help_usage
comma
l_int|0
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
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
