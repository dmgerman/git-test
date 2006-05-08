DECL|macro|_XOPEN_SOURCE
mdefine_line|#define _XOPEN_SOURCE 500 /* glibc2 and AIX 5.3L need this */
DECL|macro|_XOPEN_SOURCE_EXTENDED
mdefine_line|#define _XOPEN_SOURCE_EXTENDED 1 /* AIX 5.3L needs this */
macro_line|#include &lt;time.h&gt;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tree.h&quot;
DECL|struct|entry
r_struct
id|entry
(brace
DECL|member|old_sha1
r_int
r_char
id|old_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|new_sha1
r_int
r_char
id|new_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|converted
r_int
id|converted
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAXOBJECTS
mdefine_line|#define MAXOBJECTS (1000000)
DECL|variable|convert
r_static
r_struct
id|entry
op_star
id|convert
(braket
id|MAXOBJECTS
)braket
suffix:semicolon
DECL|variable|nr_convert
r_static
r_int
id|nr_convert
suffix:semicolon
r_static
r_struct
id|entry
op_star
id|convert_entry
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
suffix:semicolon
DECL|function|insert_new
r_static
r_struct
id|entry
op_star
id|insert_new
c_func
(paren
r_int
r_char
op_star
id|sha1
comma
r_int
id|pos
)paren
(brace
r_struct
id|entry
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
r_struct
id|entry
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
r_new
op_member_access_from_pointer
id|old_sha1
comma
id|sha1
comma
l_int|20
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|convert
op_plus
id|pos
op_plus
l_int|1
comma
id|convert
op_plus
id|pos
comma
(paren
id|nr_convert
id|pos
)paren
op_star
r_sizeof
(paren
r_struct
id|entry
op_star
)paren
)paren
suffix:semicolon
id|convert
(braket
id|pos
)braket
op_assign
r_new
suffix:semicolon
id|nr_convert
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nr_convert
op_eq
id|MAXOBJECTS
)paren
id|die
c_func
(paren
l_string|&quot;you&squot;re kidding me - hit maximum object limit&quot;
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
DECL|function|lookup_entry
r_static
r_struct
id|entry
op_star
id|lookup_entry
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|low
op_assign
l_int|0
comma
id|high
op_assign
id|nr_convert
suffix:semicolon
r_while
c_loop
(paren
id|low
OL
id|high
)paren
(brace
r_int
id|next
op_assign
(paren
id|low
op_plus
id|high
)paren
op_div
l_int|2
suffix:semicolon
r_struct
id|entry
op_star
id|n
op_assign
id|convert
(braket
id|next
)braket
suffix:semicolon
r_int
id|cmp
op_assign
id|memcmp
c_func
(paren
id|sha1
comma
id|n-&gt;old_sha1
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmp
)paren
r_return
id|n
suffix:semicolon
r_if
c_cond
(paren
id|cmp
OL
l_int|0
)paren
(brace
id|high
op_assign
id|next
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|low
op_assign
id|next
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|insert_new
c_func
(paren
id|sha1
comma
id|low
)paren
suffix:semicolon
)brace
DECL|function|convert_binary_sha1
r_static
r_void
id|convert_binary_sha1
c_func
(paren
r_void
op_star
id|buffer
)paren
(brace
r_struct
id|entry
op_star
id|entry
op_assign
id|convert_entry
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|entry-&gt;new_sha1
comma
l_int|20
)paren
suffix:semicolon
)brace
DECL|function|convert_ascii_sha1
r_static
r_void
id|convert_ascii_sha1
c_func
(paren
r_void
op_star
id|buffer
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
id|entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1_hex
c_func
(paren
id|buffer
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;expected sha1, got &squot;%s&squot;&quot;
comma
(paren
r_char
op_star
)paren
id|buffer
)paren
suffix:semicolon
id|entry
op_assign
id|convert_entry
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;new_sha1
)paren
comma
l_int|40
)paren
suffix:semicolon
)brace
DECL|function|convert_mode
r_static
r_int
r_int
id|convert_mode
c_func
(paren
r_int
r_int
id|mode
)paren
(brace
r_int
r_int
id|newmode
suffix:semicolon
id|newmode
op_assign
id|mode
op_amp
id|S_IFMT
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
id|newmode
op_or_assign
(paren
id|mode
op_amp
l_int|0100
)paren
ques
c_cond
l_int|0755
suffix:colon
l_int|0644
suffix:semicolon
r_return
id|newmode
suffix:semicolon
)brace
DECL|function|write_subdirectory
r_static
r_int
id|write_subdirectory
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|base
comma
r_int
id|baselen
comma
r_int
r_char
op_star
id|result_sha1
)paren
(brace
r_char
op_star
r_new
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
r_int
r_int
id|newlen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|used
suffix:semicolon
id|used
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_int
id|len
op_assign
l_int|21
op_plus
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_char
op_star
id|path
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_int
r_int
id|mode
suffix:semicolon
r_char
op_star
id|slash
comma
op_star
id|origpath
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
id|sscanf
c_func
(paren
id|buffer
comma
l_string|&quot;%o&quot;
comma
op_amp
id|mode
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;bad tree conversion&quot;
)paren
suffix:semicolon
id|mode
op_assign
id|convert_mode
c_func
(paren
id|mode
)paren
suffix:semicolon
id|path
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|path
comma
id|base
comma
id|baselen
)paren
)paren
r_break
suffix:semicolon
id|origpath
op_assign
id|path
suffix:semicolon
id|path
op_add_assign
id|baselen
suffix:semicolon
id|slash
op_assign
id|strchr
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
op_logical_neg
id|slash
)paren
(brace
id|newlen
op_add_assign
id|sprintf
c_func
(paren
r_new
op_plus
id|newlen
comma
l_string|&quot;%o %s&quot;
comma
id|mode
comma
id|path
)paren
suffix:semicolon
r_new
(braket
id|newlen
op_increment
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|memcpy
c_func
(paren
r_new
op_plus
id|newlen
comma
id|buffer
op_plus
id|len
l_int|20
comma
l_int|20
)paren
suffix:semicolon
id|newlen
op_add_assign
l_int|20
suffix:semicolon
id|used
op_add_assign
id|len
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|newlen
op_add_assign
id|sprintf
c_func
(paren
r_new
op_plus
id|newlen
comma
l_string|&quot;%o %.*s&quot;
comma
id|S_IFDIR
comma
(paren
r_int
)paren
(paren
id|slash
id|path
)paren
comma
id|path
)paren
suffix:semicolon
r_new
(braket
id|newlen
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|sha1
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
r_new
op_plus
id|newlen
)paren
suffix:semicolon
id|newlen
op_add_assign
l_int|20
suffix:semicolon
id|len
op_assign
id|write_subdirectory
c_func
(paren
id|buffer
comma
id|size
comma
id|origpath
comma
id|slash
op_minus
id|origpath
op_plus
l_int|1
comma
id|sha1
)paren
suffix:semicolon
id|used
op_add_assign
id|len
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
)brace
id|write_sha1_file
c_func
(paren
r_new
comma
id|newlen
comma
id|tree_type
comma
id|result_sha1
)paren
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|used
suffix:semicolon
)brace
DECL|function|convert_tree
r_static
r_void
id|convert_tree
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
comma
r_int
r_char
op_star
id|result_sha1
)paren
(brace
r_void
op_star
id|orig_buffer
op_assign
id|buffer
suffix:semicolon
r_int
r_int
id|orig_size
op_assign
id|size
suffix:semicolon
r_while
c_loop
(paren
id|size
)paren
(brace
r_int
id|len
op_assign
l_int|1
op_plus
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|convert_binary_sha1
c_func
(paren
id|buffer
op_plus
id|len
)paren
suffix:semicolon
id|len
op_add_assign
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|size
)paren
id|die
c_func
(paren
l_string|&quot;corrupt tree object&quot;
)paren
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
)brace
id|write_subdirectory
c_func
(paren
id|orig_buffer
comma
id|orig_size
comma
l_string|&quot;&quot;
comma
l_int|0
comma
id|result_sha1
)paren
suffix:semicolon
)brace
DECL|function|parse_oldstyle_date
r_static
r_int
r_int
id|parse_oldstyle_date
c_func
(paren
r_const
r_char
op_star
id|buf
)paren
(brace
r_char
id|c
comma
op_star
id|p
suffix:semicolon
r_char
id|buffer
(braket
l_int|100
)braket
suffix:semicolon
r_struct
id|tm
id|tm
suffix:semicolon
r_const
r_char
op_star
id|formats
(braket
)braket
op_assign
(brace
l_string|&quot;%c&quot;
comma
l_string|&quot;%a %b %d %T&quot;
comma
l_string|&quot;%Z&quot;
comma
l_string|&quot;%Y&quot;
comma
l_string|&quot; %Y&quot;
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* We only ever did two timezones in the bad old format .. */
r_const
r_char
op_star
id|timezones
(braket
)braket
op_assign
(brace
l_string|&quot;PDT&quot;
comma
l_string|&quot;PST&quot;
comma
l_string|&quot;CEST&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_const
r_char
op_star
op_star
id|fmt
op_assign
id|formats
suffix:semicolon
id|p
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|c
op_assign
op_star
id|buf
)paren
)paren
id|buf
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|buf
op_increment
)paren
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
id|buf
op_assign
id|buffer
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tm
comma
l_int|0
comma
r_sizeof
(paren
id|tm
)paren
)paren
suffix:semicolon
r_do
(brace
r_const
r_char
op_star
id|next
op_assign
id|strptime
c_func
(paren
id|buf
comma
op_star
id|fmt
comma
op_amp
id|tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|next
)paren
r_return
id|mktime
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
id|buf
op_assign
id|next
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
op_star
op_star
id|p
op_assign
id|timezones
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
id|buf
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buf
comma
op_star
id|p
comma
id|strlen
c_func
(paren
op_star
id|p
)paren
)paren
)paren
(brace
id|buf
op_add_assign
id|strlen
c_func
(paren
op_star
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
)brace
)brace
id|fmt
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|buf
op_logical_and
op_star
id|fmt
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;left: %s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
r_return
id|mktime
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
)brace
DECL|function|convert_date_line
r_static
r_int
id|convert_date_line
c_func
(paren
r_char
op_star
id|dst
comma
r_void
op_star
op_star
id|buf
comma
r_int
r_int
op_star
id|sp
)paren
(brace
r_int
r_int
id|size
op_assign
op_star
id|sp
suffix:semicolon
r_char
op_star
id|line
op_assign
op_star
id|buf
suffix:semicolon
r_char
op_star
id|next
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_char
op_star
id|date
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
op_logical_or
op_logical_neg
id|date
)paren
id|die
c_func
(paren
l_string|&quot;missing or bad author/committer line %s&quot;
comma
id|line
)paren
suffix:semicolon
id|next
op_increment
suffix:semicolon
id|date
op_add_assign
l_int|2
suffix:semicolon
op_star
id|buf
op_assign
id|next
suffix:semicolon
op_star
id|sp
op_assign
id|size
(paren
id|next
id|line
)paren
suffix:semicolon
id|len
op_assign
id|date
id|line
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|line
comma
id|len
)paren
suffix:semicolon
id|dst
op_add_assign
id|len
suffix:semicolon
multiline_comment|/* Is it already in new format? */
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|date
)paren
)paren
(brace
r_int
id|datelen
op_assign
id|next
id|date
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|date
comma
id|datelen
)paren
suffix:semicolon
r_return
id|len
op_plus
id|datelen
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Hacky hacky: one of the sparse old-style commits does not have&n;&t; * any date at all, but we can fake it by using the committer date.&n;&t; */
r_if
c_cond
(paren
op_star
id|date
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|strchr
c_func
(paren
id|next
comma
l_char|&squot;&gt;&squot;
)paren
)paren
id|date
op_assign
id|strchr
c_func
(paren
id|next
comma
l_char|&squot;&gt;&squot;
)paren
op_plus
l_int|2
suffix:semicolon
r_return
id|len
op_plus
id|sprintf
c_func
(paren
id|dst
comma
l_string|&quot;%lu -0700&bslash;n&quot;
comma
id|parse_oldstyle_date
c_func
(paren
id|date
)paren
)paren
suffix:semicolon
)brace
DECL|function|convert_date
r_static
r_void
id|convert_date
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
comma
r_int
r_char
op_star
id|result_sha1
)paren
(brace
r_char
op_star
r_new
op_assign
id|xmalloc
c_func
(paren
id|size
op_plus
l_int|100
)paren
suffix:semicolon
r_int
r_int
id|newlen
op_assign
l_int|0
suffix:semicolon
singleline_comment|// &quot;tree &lt;sha1&gt;&bslash;n&quot;
id|memcpy
c_func
(paren
r_new
op_plus
id|newlen
comma
id|buffer
comma
l_int|46
)paren
suffix:semicolon
id|newlen
op_add_assign
l_int|46
suffix:semicolon
id|buffer
op_add_assign
l_int|46
suffix:semicolon
id|size
op_sub_assign
l_int|46
suffix:semicolon
singleline_comment|// &quot;parent &lt;sha1&gt;&bslash;n&quot;
r_while
c_loop
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buffer
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
(brace
id|memcpy
c_func
(paren
r_new
op_plus
id|newlen
comma
id|buffer
comma
l_int|48
)paren
suffix:semicolon
id|newlen
op_add_assign
l_int|48
suffix:semicolon
id|buffer
op_add_assign
l_int|48
suffix:semicolon
id|size
op_sub_assign
l_int|48
suffix:semicolon
)brace
singleline_comment|// &quot;author xyz &lt;xyz&gt; date&quot;
id|newlen
op_add_assign
id|convert_date_line
c_func
(paren
r_new
op_plus
id|newlen
comma
op_amp
id|buffer
comma
op_amp
id|size
)paren
suffix:semicolon
singleline_comment|// &quot;committer xyz &lt;xyz&gt; date&quot;
id|newlen
op_add_assign
id|convert_date_line
c_func
(paren
r_new
op_plus
id|newlen
comma
op_amp
id|buffer
comma
op_amp
id|size
)paren
suffix:semicolon
singleline_comment|// Rest
id|memcpy
c_func
(paren
r_new
op_plus
id|newlen
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
id|newlen
op_add_assign
id|size
suffix:semicolon
id|write_sha1_file
c_func
(paren
r_new
comma
id|newlen
comma
id|commit_type
comma
id|result_sha1
)paren
suffix:semicolon
id|free
c_func
(paren
r_new
)paren
suffix:semicolon
)brace
DECL|function|convert_commit
r_static
r_void
id|convert_commit
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
r_int
id|size
comma
r_int
r_char
op_star
id|result_sha1
)paren
(brace
r_void
op_star
id|orig_buffer
op_assign
id|buffer
suffix:semicolon
r_int
r_int
id|orig_size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buffer
comma
l_string|&quot;tree &quot;
comma
l_int|5
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Bad commit &squot;%s&squot;&quot;
comma
(paren
r_char
op_star
)paren
id|buffer
)paren
suffix:semicolon
id|convert_ascii_sha1
c_func
(paren
id|buffer
op_plus
l_int|5
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|46
suffix:semicolon
multiline_comment|/* &quot;tree &quot; + &quot;hex sha1&quot; + &quot;&bslash;n&quot; */
r_while
c_loop
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|buffer
comma
l_string|&quot;parent &quot;
comma
l_int|7
)paren
)paren
(brace
id|convert_ascii_sha1
c_func
(paren
id|buffer
op_plus
l_int|7
)paren
suffix:semicolon
id|buffer
op_add_assign
l_int|48
suffix:semicolon
)brace
id|convert_date
c_func
(paren
id|orig_buffer
comma
id|orig_size
comma
id|result_sha1
)paren
suffix:semicolon
)brace
DECL|function|convert_entry
r_static
r_struct
id|entry
op_star
id|convert_entry
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|entry
op_star
id|entry
op_assign
id|lookup_entry
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_char
id|type
(braket
l_int|20
)braket
suffix:semicolon
r_void
op_star
id|buffer
comma
op_star
id|data
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;converted
)paren
r_return
id|entry
suffix:semicolon
id|data
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
id|type
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
id|die
c_func
(paren
l_string|&quot;unable to read object %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|data
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|blob_type
)paren
)paren
(brace
id|write_sha1_file
c_func
(paren
id|buffer
comma
id|size
comma
id|blob_type
comma
id|entry-&gt;new_sha1
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
id|type
comma
id|tree_type
)paren
)paren
id|convert_tree
c_func
(paren
id|buffer
comma
id|size
comma
id|entry-&gt;new_sha1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|type
comma
id|commit_type
)paren
)paren
id|convert_commit
c_func
(paren
id|buffer
comma
id|size
comma
id|entry-&gt;new_sha1
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;unknown object type &squot;%s&squot; in %s&quot;
comma
id|type
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|entry-&gt;converted
op_assign
l_int|1
suffix:semicolon
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|free
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|entry
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
op_star
id|argv
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
id|entry
op_star
id|entry
suffix:semicolon
id|setup_git_directory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|2
)paren
id|usage
c_func
(paren
l_string|&quot;git-convert-objects &lt;sha1&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_sha1
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|sha1
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Not a valid object name %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|entry
op_assign
id|convert_entry
c_func
(paren
id|sha1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;new sha1: %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|entry-&gt;new_sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
