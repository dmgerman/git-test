multiline_comment|/*&n; * Copyright (C) 2011 John Szakmeister &lt;john@szakmeister.net&gt;&n; *               2012 Philipp A. Hartmann &lt;pah@qo.cx&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Credits:&n; * - GNOME Keyring API handling originally written by John Szakmeister&n; * - ported to credential helper API by Philipp A. Hartmann&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;glib.h&gt;
macro_line|#include &lt;gnome-keyring.h&gt;
macro_line|#ifdef GNOME_KEYRING_DEFAULT
multiline_comment|/* Modern gnome-keyring */
macro_line|#include &lt;gnome-keyring-memory.h&gt;
macro_line|#else
multiline_comment|/*&n;    * Support ancient gnome-keyring, circ. RHEL 5.X.&n;    * GNOME_KEYRING_DEFAULT seems to have been introduced with Gnome 2.22,&n;    * and the other features roughly around Gnome 2.20, 6 months before.&n;    * Ubuntu 8.04 used Gnome 2.22 (I think).  Not sure any distro used 2.20.&n;    * So the existence/non-existence of GNOME_KEYRING_DEFAULT seems like&n;    * a decent thing to use as an indicator.&n;    */
DECL|macro|GNOME_KEYRING_DEFAULT
mdefine_line|#define GNOME_KEYRING_DEFAULT NULL
multiline_comment|/*&n; * ancient gnome-keyring returns DENIED when an entry is not found.&n; * Setting NO_MATCH to DENIED will prevent us from reporting DENIED&n; * errors during get and erase operations, but we will still report&n; * DENIED errors during a store.&n; */
DECL|macro|GNOME_KEYRING_RESULT_NO_MATCH
mdefine_line|#define GNOME_KEYRING_RESULT_NO_MATCH GNOME_KEYRING_RESULT_DENIED
DECL|macro|gnome_keyring_memory_alloc
mdefine_line|#define gnome_keyring_memory_alloc g_malloc
DECL|macro|gnome_keyring_memory_free
mdefine_line|#define gnome_keyring_memory_free gnome_keyring_free_password
DECL|macro|gnome_keyring_memory_strdup
mdefine_line|#define gnome_keyring_memory_strdup g_strdup
DECL|function|gnome_keyring_result_to_message
r_static
r_const
r_char
op_star
id|gnome_keyring_result_to_message
c_func
(paren
id|GnomeKeyringResult
id|result
)paren
(brace
r_switch
c_cond
(paren
id|result
)paren
(brace
r_case
id|GNOME_KEYRING_RESULT_OK
suffix:colon
r_return
l_string|&quot;OK&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_DENIED
suffix:colon
r_return
l_string|&quot;Denied&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_NO_KEYRING_DAEMON
suffix:colon
r_return
l_string|&quot;No Keyring Daemon&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_ALREADY_UNLOCKED
suffix:colon
r_return
l_string|&quot;Already UnLocked&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_NO_SUCH_KEYRING
suffix:colon
r_return
l_string|&quot;No Such Keyring&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_BAD_ARGUMENTS
suffix:colon
r_return
l_string|&quot;Bad Arguments&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_IO_ERROR
suffix:colon
r_return
l_string|&quot;IO Error&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_CANCELLED
suffix:colon
r_return
l_string|&quot;Cancelled&quot;
suffix:semicolon
r_case
id|GNOME_KEYRING_RESULT_ALREADY_EXISTS
suffix:colon
r_return
l_string|&quot;Already Exists&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;Unknown Error&quot;
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Support really ancient gnome-keyring, circ. RHEL 4.X.&n; * Just a guess for the Glib version.  Glib 2.8 was roughly Gnome 2.12 ?&n; * Which was released with gnome-keyring 0.4.3 ??&n; */
macro_line|#if GLIB_MAJOR_VERSION == 2 &amp;&amp; GLIB_MINOR_VERSION &lt; 8
DECL|function|gnome_keyring_done_cb
r_static
r_void
id|gnome_keyring_done_cb
c_func
(paren
id|GnomeKeyringResult
id|result
comma
id|gpointer
id|user_data
)paren
(brace
id|gpointer
op_star
id|data
op_assign
(paren
id|gpointer
op_star
)paren
id|user_data
suffix:semicolon
r_int
op_star
id|done
op_assign
(paren
r_int
op_star
)paren
id|data
(braket
l_int|0
)braket
suffix:semicolon
id|GnomeKeyringResult
op_star
id|r
op_assign
(paren
id|GnomeKeyringResult
op_star
)paren
id|data
(braket
l_int|1
)braket
suffix:semicolon
op_star
id|r
op_assign
id|result
suffix:semicolon
op_star
id|done
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|wait_for_request_completion
r_static
r_void
id|wait_for_request_completion
c_func
(paren
r_int
op_star
id|done
)paren
(brace
id|GMainContext
op_star
id|mc
op_assign
id|g_main_context_default
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
op_star
id|done
)paren
id|g_main_context_iteration
c_func
(paren
id|mc
comma
id|TRUE
)paren
suffix:semicolon
)brace
DECL|function|gnome_keyring_item_delete_sync
r_static
id|GnomeKeyringResult
id|gnome_keyring_item_delete_sync
c_func
(paren
r_const
r_char
op_star
id|keyring
comma
id|guint32
id|id
)paren
(brace
r_int
id|done
op_assign
l_int|0
suffix:semicolon
id|GnomeKeyringResult
id|result
suffix:semicolon
id|gpointer
id|data
(braket
)braket
op_assign
(brace
op_amp
id|done
comma
op_amp
id|result
)brace
suffix:semicolon
id|gnome_keyring_item_delete
c_func
(paren
id|keyring
comma
id|id
comma
id|gnome_keyring_done_cb
comma
id|data
comma
l_int|NULL
)paren
suffix:semicolon
id|wait_for_request_completion
c_func
(paren
op_amp
id|done
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * This credential struct and API is simplified from git&squot;s credential.{h,c}&n; */
DECL|struct|credential
r_struct
id|credential
(brace
DECL|member|protocol
r_char
op_star
id|protocol
suffix:semicolon
DECL|member|host
r_char
op_star
id|host
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|username
r_char
op_star
id|username
suffix:semicolon
DECL|member|password
r_char
op_star
id|password
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CREDENTIAL_INIT
mdefine_line|#define CREDENTIAL_INIT { NULL, NULL, 0, NULL, NULL, NULL }
DECL|typedef|credential_op_cb
r_typedef
r_int
(paren
op_star
id|credential_op_cb
)paren
(paren
r_struct
id|credential
op_star
)paren
suffix:semicolon
DECL|struct|credential_operation
r_struct
id|credential_operation
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|op
id|credential_op_cb
id|op
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CREDENTIAL_OP_END
mdefine_line|#define CREDENTIAL_OP_END { NULL, NULL }
multiline_comment|/* ----------------- GNOME Keyring functions ----------------- */
multiline_comment|/* create a special keyring option string, if path is given */
DECL|function|keyring_object
r_static
r_char
op_star
id|keyring_object
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;path
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;port
)paren
r_return
id|g_strdup_printf
c_func
(paren
l_string|&quot;%s:%hd/%s&quot;
comma
id|c-&gt;host
comma
id|c-&gt;port
comma
id|c-&gt;path
)paren
suffix:semicolon
r_return
id|g_strdup_printf
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
id|c-&gt;host
comma
id|c-&gt;path
)paren
suffix:semicolon
)brace
DECL|function|keyring_get
r_static
r_int
id|keyring_get
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
r_char
op_star
id|object
op_assign
l_int|NULL
suffix:semicolon
id|GList
op_star
id|entries
suffix:semicolon
id|GnomeKeyringNetworkPasswordData
op_star
id|password_data
suffix:semicolon
id|GnomeKeyringResult
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;protocol
op_logical_or
op_logical_neg
(paren
id|c-&gt;host
op_logical_or
id|c-&gt;path
)paren
)paren
r_return
id|EXIT_FAILURE
suffix:semicolon
id|object
op_assign
id|keyring_object
c_func
(paren
id|c
)paren
suffix:semicolon
id|result
op_assign
id|gnome_keyring_find_network_password_sync
c_func
(paren
id|c-&gt;username
comma
l_int|NULL
multiline_comment|/* domain */
comma
id|c-&gt;host
comma
id|object
comma
id|c-&gt;protocol
comma
l_int|NULL
multiline_comment|/* authtype */
comma
id|c-&gt;port
comma
op_amp
id|entries
)paren
suffix:semicolon
id|g_free
c_func
(paren
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|GNOME_KEYRING_RESULT_NO_MATCH
)paren
r_return
id|EXIT_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|GNOME_KEYRING_RESULT_CANCELLED
)paren
r_return
id|EXIT_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|GNOME_KEYRING_RESULT_OK
)paren
(brace
id|g_critical
c_func
(paren
l_string|&quot;%s&quot;
comma
id|gnome_keyring_result_to_message
c_func
(paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|EXIT_FAILURE
suffix:semicolon
)brace
multiline_comment|/* pick the first one from the list */
id|password_data
op_assign
(paren
id|GnomeKeyringNetworkPasswordData
op_star
)paren
id|entries-&gt;data
suffix:semicolon
id|gnome_keyring_memory_free
c_func
(paren
id|c-&gt;password
)paren
suffix:semicolon
id|c-&gt;password
op_assign
id|gnome_keyring_memory_strdup
c_func
(paren
id|password_data-&gt;password
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;username
)paren
id|c-&gt;username
op_assign
id|g_strdup
c_func
(paren
id|password_data-&gt;user
)paren
suffix:semicolon
id|gnome_keyring_network_password_list_free
c_func
(paren
id|entries
)paren
suffix:semicolon
r_return
id|EXIT_SUCCESS
suffix:semicolon
)brace
DECL|function|keyring_store
r_static
r_int
id|keyring_store
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
id|guint32
id|item_id
suffix:semicolon
r_char
op_star
id|object
op_assign
l_int|NULL
suffix:semicolon
id|GnomeKeyringResult
id|result
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity check that what we are storing is actually sensible.&n;&t; * In particular, we can&squot;t make a URL without a protocol field.&n;&t; * Without either a host or pathname (depending on the scheme),&n;&t; * we have no primary key. And without a username and password,&n;&t; * we are not actually storing a credential.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;protocol
op_logical_or
op_logical_neg
(paren
id|c-&gt;host
op_logical_or
id|c-&gt;path
)paren
op_logical_or
op_logical_neg
id|c-&gt;username
op_logical_or
op_logical_neg
id|c-&gt;password
)paren
r_return
id|EXIT_FAILURE
suffix:semicolon
id|object
op_assign
id|keyring_object
c_func
(paren
id|c
)paren
suffix:semicolon
id|result
op_assign
id|gnome_keyring_set_network_password_sync
c_func
(paren
id|GNOME_KEYRING_DEFAULT
comma
id|c-&gt;username
comma
l_int|NULL
multiline_comment|/* domain */
comma
id|c-&gt;host
comma
id|object
comma
id|c-&gt;protocol
comma
l_int|NULL
multiline_comment|/* authtype */
comma
id|c-&gt;port
comma
id|c-&gt;password
comma
op_amp
id|item_id
)paren
suffix:semicolon
id|g_free
c_func
(paren
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|GNOME_KEYRING_RESULT_OK
op_logical_and
id|result
op_ne
id|GNOME_KEYRING_RESULT_CANCELLED
)paren
(brace
id|g_critical
c_func
(paren
l_string|&quot;%s&quot;
comma
id|gnome_keyring_result_to_message
c_func
(paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|EXIT_FAILURE
suffix:semicolon
)brace
r_return
id|EXIT_SUCCESS
suffix:semicolon
)brace
DECL|function|keyring_erase
r_static
r_int
id|keyring_erase
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
r_char
op_star
id|object
op_assign
l_int|NULL
suffix:semicolon
id|GList
op_star
id|entries
suffix:semicolon
id|GnomeKeyringNetworkPasswordData
op_star
id|password_data
suffix:semicolon
id|GnomeKeyringResult
id|result
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity check that we actually have something to match&n;&t; * against. The input we get is a restrictive pattern,&n;&t; * so technically a blank credential means &quot;erase everything&quot;.&n;&t; * But it is too easy to accidentally send this, since it is equivalent&n;&t; * to empty input. So explicitly disallow it, and require that the&n;&t; * pattern have some actual content to match.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;protocol
op_logical_and
op_logical_neg
id|c-&gt;host
op_logical_and
op_logical_neg
id|c-&gt;path
op_logical_and
op_logical_neg
id|c-&gt;username
)paren
r_return
id|EXIT_FAILURE
suffix:semicolon
id|object
op_assign
id|keyring_object
c_func
(paren
id|c
)paren
suffix:semicolon
id|result
op_assign
id|gnome_keyring_find_network_password_sync
c_func
(paren
id|c-&gt;username
comma
l_int|NULL
multiline_comment|/* domain */
comma
id|c-&gt;host
comma
id|object
comma
id|c-&gt;protocol
comma
l_int|NULL
multiline_comment|/* authtype */
comma
id|c-&gt;port
comma
op_amp
id|entries
)paren
suffix:semicolon
id|g_free
c_func
(paren
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|GNOME_KEYRING_RESULT_NO_MATCH
)paren
r_return
id|EXIT_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
id|GNOME_KEYRING_RESULT_CANCELLED
)paren
r_return
id|EXIT_SUCCESS
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|GNOME_KEYRING_RESULT_OK
)paren
(brace
id|g_critical
c_func
(paren
l_string|&quot;%s&quot;
comma
id|gnome_keyring_result_to_message
c_func
(paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|EXIT_FAILURE
suffix:semicolon
)brace
multiline_comment|/* pick the first one from the list (delete all matches?) */
id|password_data
op_assign
(paren
id|GnomeKeyringNetworkPasswordData
op_star
)paren
id|entries-&gt;data
suffix:semicolon
id|result
op_assign
id|gnome_keyring_item_delete_sync
c_func
(paren
id|password_data-&gt;keyring
comma
id|password_data-&gt;item_id
)paren
suffix:semicolon
id|gnome_keyring_network_password_list_free
c_func
(paren
id|entries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|GNOME_KEYRING_RESULT_OK
)paren
(brace
id|g_critical
c_func
(paren
l_string|&quot;%s&quot;
comma
id|gnome_keyring_result_to_message
c_func
(paren
id|result
)paren
)paren
suffix:semicolon
r_return
id|EXIT_FAILURE
suffix:semicolon
)brace
r_return
id|EXIT_SUCCESS
suffix:semicolon
)brace
multiline_comment|/*&n; * Table with helper operation callbacks, used by generic&n; * credential helper main function.&n; */
DECL|variable|credential_helper_ops
r_static
r_struct
id|credential_operation
r_const
id|credential_helper_ops
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;get&quot;
comma
id|keyring_get
)brace
comma
(brace
l_string|&quot;store&quot;
comma
id|keyring_store
)brace
comma
(brace
l_string|&quot;erase&quot;
comma
id|keyring_erase
)brace
comma
id|CREDENTIAL_OP_END
)brace
suffix:semicolon
multiline_comment|/* ------------------ credential functions ------------------ */
DECL|function|credential_init
r_static
r_void
id|credential_init
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|c
)paren
)paren
suffix:semicolon
)brace
DECL|function|credential_clear
r_static
r_void
id|credential_clear
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
id|g_free
c_func
(paren
id|c-&gt;protocol
)paren
suffix:semicolon
id|g_free
c_func
(paren
id|c-&gt;host
)paren
suffix:semicolon
id|g_free
c_func
(paren
id|c-&gt;path
)paren
suffix:semicolon
id|g_free
c_func
(paren
id|c-&gt;username
)paren
suffix:semicolon
id|gnome_keyring_memory_free
c_func
(paren
id|c-&gt;password
)paren
suffix:semicolon
id|credential_init
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|credential_read
r_static
r_int
id|credential_read
c_func
(paren
r_struct
id|credential
op_star
id|c
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_int
id|line_len
suffix:semicolon
r_char
op_star
id|key
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
id|key
op_assign
id|buf
op_assign
id|gnome_keyring_memory_alloc
c_func
(paren
l_int|1024
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buf
comma
l_int|1024
comma
id|stdin
)paren
)paren
(brace
id|line_len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line_len
op_logical_and
id|buf
(braket
id|line_len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|buf
(braket
op_decrement
id|line_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line_len
)paren
r_break
suffix:semicolon
id|value
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|g_warning
c_func
(paren
l_string|&quot;invalid credential line: %s&quot;
comma
id|key
)paren
suffix:semicolon
id|gnome_keyring_memory_free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
op_star
id|value
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;protocol&quot;
)paren
)paren
(brace
id|g_free
c_func
(paren
id|c-&gt;protocol
)paren
suffix:semicolon
id|c-&gt;protocol
op_assign
id|g_strdup
c_func
(paren
id|value
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
id|key
comma
l_string|&quot;host&quot;
)paren
)paren
(brace
id|g_free
c_func
(paren
id|c-&gt;host
)paren
suffix:semicolon
id|c-&gt;host
op_assign
id|g_strdup
c_func
(paren
id|value
)paren
suffix:semicolon
id|value
op_assign
id|strrchr
c_func
(paren
id|c-&gt;host
comma
l_char|&squot;:&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
op_star
id|value
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|c-&gt;port
op_assign
id|atoi
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;path&quot;
)paren
)paren
(brace
id|g_free
c_func
(paren
id|c-&gt;path
)paren
suffix:semicolon
id|c-&gt;path
op_assign
id|g_strdup
c_func
(paren
id|value
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
id|key
comma
l_string|&quot;username&quot;
)paren
)paren
(brace
id|g_free
c_func
(paren
id|c-&gt;username
)paren
suffix:semicolon
id|c-&gt;username
op_assign
id|g_strdup
c_func
(paren
id|value
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
id|key
comma
l_string|&quot;password&quot;
)paren
)paren
(brace
id|gnome_keyring_memory_free
c_func
(paren
id|c-&gt;password
)paren
suffix:semicolon
id|c-&gt;password
op_assign
id|gnome_keyring_memory_strdup
c_func
(paren
id|value
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|value
)paren
op_star
id|value
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Ignore other lines; we don&squot;t know what they mean, but&n;&t;&t; * this future-proofs us when later versions of git do&n;&t;&t; * learn new lines, and the helpers are updated to match.&n;&t;&t; */
)brace
id|gnome_keyring_memory_free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|credential_write_item
r_static
r_void
id|credential_write_item
c_func
(paren
id|FILE
op_star
id|fp
comma
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
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
suffix:semicolon
id|fprintf
c_func
(paren
id|fp
comma
l_string|&quot;%s=%s&bslash;n&quot;
comma
id|key
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|credential_write
r_static
r_void
id|credential_write
c_func
(paren
r_const
r_struct
id|credential
op_star
id|c
)paren
(brace
multiline_comment|/* only write username/password, if set */
id|credential_write_item
c_func
(paren
id|stdout
comma
l_string|&quot;username&quot;
comma
id|c-&gt;username
)paren
suffix:semicolon
id|credential_write_item
c_func
(paren
id|stdout
comma
l_string|&quot;password&quot;
comma
id|c-&gt;password
)paren
suffix:semicolon
)brace
DECL|function|usage
r_static
r_void
id|usage
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|credential_operation
r_const
op_star
id|try_op
op_assign
id|credential_helper_ops
suffix:semicolon
r_const
r_char
op_star
id|basename
op_assign
id|strrchr
c_func
(paren
id|name
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|basename
op_assign
(paren
id|basename
)paren
ques
c_cond
id|basename
op_plus
l_int|1
suffix:colon
id|name
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;usage: %s &lt;&quot;
comma
id|basename
)paren
suffix:semicolon
r_while
c_loop
(paren
id|try_op-&gt;name
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&quot;
comma
(paren
id|try_op
op_increment
)paren
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|try_op-&gt;name
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;|&quot;
)paren
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&quot;
comma
l_string|&quot;&gt;&bslash;n&quot;
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
id|argv
(braket
)braket
)paren
(brace
r_int
id|ret
op_assign
id|EXIT_SUCCESS
suffix:semicolon
r_struct
id|credential_operation
r_const
op_star
id|try_op
op_assign
id|credential_helper_ops
suffix:semicolon
r_struct
id|credential
id|cred
op_assign
id|CREDENTIAL_INIT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|argv
(braket
l_int|1
)braket
)paren
(brace
id|usage
c_func
(paren
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
id|EXIT_FAILURE
)paren
suffix:semicolon
)brace
id|g_set_application_name
c_func
(paren
l_string|&quot;Git Credential Helper&quot;
)paren
suffix:semicolon
multiline_comment|/* lookup operation callback */
r_while
c_loop
(paren
id|try_op-&gt;name
op_logical_and
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|try_op-&gt;name
)paren
)paren
id|try_op
op_increment
suffix:semicolon
multiline_comment|/* unsupported operation given -- ignore silently */
r_if
c_cond
(paren
op_logical_neg
id|try_op-&gt;name
op_logical_or
op_logical_neg
id|try_op-&gt;op
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|credential_read
c_func
(paren
op_amp
id|cred
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* perform credential operation */
id|ret
op_assign
(paren
op_star
id|try_op-&gt;op
)paren
(paren
op_amp
id|cred
)paren
suffix:semicolon
id|credential_write
c_func
(paren
op_amp
id|cred
)paren
suffix:semicolon
id|out
suffix:colon
id|credential_clear
c_func
(paren
op_amp
id|cred
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
