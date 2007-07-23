macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;reflog-walk.h&quot;
DECL|struct|complete_reflogs
r_struct
id|complete_reflogs
(brace
DECL|member|ref
r_char
op_star
id|ref
suffix:semicolon
DECL|struct|reflog_info
r_struct
id|reflog_info
(brace
DECL|member|osha1
DECL|member|nsha1
r_int
r_char
id|osha1
(braket
l_int|20
)braket
comma
id|nsha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|email
r_char
op_star
id|email
suffix:semicolon
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
DECL|member|tz
r_int
id|tz
suffix:semicolon
DECL|member|message
r_char
op_star
id|message
suffix:semicolon
DECL|member|items
)brace
op_star
id|items
suffix:semicolon
DECL|member|nr
DECL|member|alloc
r_int
id|nr
comma
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|function|read_one_reflog
r_static
r_int
id|read_one_reflog
c_func
(paren
r_int
r_char
op_star
id|osha1
comma
r_int
r_char
op_star
id|nsha1
comma
r_const
r_char
op_star
id|email
comma
r_int
r_int
id|timestamp
comma
r_int
id|tz
comma
r_const
r_char
op_star
id|message
comma
r_void
op_star
id|cb_data
)paren
(brace
r_struct
id|complete_reflogs
op_star
id|array
op_assign
id|cb_data
suffix:semicolon
r_struct
id|reflog_info
op_star
id|item
suffix:semicolon
r_if
c_cond
(paren
id|array-&gt;nr
op_ge
id|array-&gt;alloc
)paren
(brace
id|array-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|array-&gt;nr
op_plus
l_int|1
)paren
suffix:semicolon
id|array-&gt;items
op_assign
id|xrealloc
c_func
(paren
id|array-&gt;items
comma
id|array-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|reflog_info
)paren
)paren
suffix:semicolon
)brace
id|item
op_assign
id|array-&gt;items
op_plus
id|array-&gt;nr
suffix:semicolon
id|memcpy
c_func
(paren
id|item-&gt;osha1
comma
id|osha1
comma
l_int|20
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|item-&gt;nsha1
comma
id|nsha1
comma
l_int|20
)paren
suffix:semicolon
id|item-&gt;email
op_assign
id|xstrdup
c_func
(paren
id|email
)paren
suffix:semicolon
id|item-&gt;timestamp
op_assign
id|timestamp
suffix:semicolon
id|item-&gt;tz
op_assign
id|tz
suffix:semicolon
id|item-&gt;message
op_assign
id|xstrdup
c_func
(paren
id|message
)paren
suffix:semicolon
id|array-&gt;nr
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_complete_reflog
r_static
r_struct
id|complete_reflogs
op_star
id|read_complete_reflog
c_func
(paren
r_const
r_char
op_star
id|ref
)paren
(brace
r_struct
id|complete_reflogs
op_star
id|reflogs
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|complete_reflogs
)paren
comma
l_int|1
)paren
suffix:semicolon
id|reflogs-&gt;ref
op_assign
id|xstrdup
c_func
(paren
id|ref
)paren
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|ref
comma
id|read_one_reflog
comma
id|reflogs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reflogs-&gt;nr
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|resolve_ref
c_func
(paren
id|ref
comma
id|sha1
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
)paren
id|for_each_reflog_ent
c_func
(paren
id|name
comma
id|read_one_reflog
comma
id|reflogs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reflogs-&gt;nr
op_eq
l_int|0
)paren
(brace
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
id|refname
op_assign
id|xmalloc
c_func
(paren
id|len
op_plus
l_int|12
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|refname
comma
l_string|&quot;refs/%s&quot;
comma
id|ref
)paren
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|refname
comma
id|read_one_reflog
comma
id|reflogs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reflogs-&gt;nr
op_eq
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|refname
comma
l_string|&quot;refs/heads/%s&quot;
comma
id|ref
)paren
suffix:semicolon
id|for_each_reflog_ent
c_func
(paren
id|refname
comma
id|read_one_reflog
comma
id|reflogs
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|refname
)paren
suffix:semicolon
)brace
r_return
id|reflogs
suffix:semicolon
)brace
DECL|function|get_reflog_recno_by_time
r_static
r_int
id|get_reflog_recno_by_time
c_func
(paren
r_struct
id|complete_reflogs
op_star
id|array
comma
r_int
r_int
id|timestamp
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
id|array-&gt;nr
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|timestamp
op_ge
id|array-&gt;items
(braket
id|i
)braket
dot
id|timestamp
)paren
r_return
id|i
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|struct|commit_info_lifo
r_struct
id|commit_info_lifo
(brace
DECL|struct|commit_info
r_struct
id|commit_info
(brace
DECL|member|commit
r_struct
id|commit
op_star
id|commit
suffix:semicolon
DECL|member|util
r_void
op_star
id|util
suffix:semicolon
DECL|member|items
)brace
op_star
id|items
suffix:semicolon
DECL|member|nr
DECL|member|alloc
r_int
id|nr
comma
id|alloc
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_commit_info
r_static
r_struct
id|commit_info
op_star
id|get_commit_info
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|commit_info_lifo
op_star
id|lifo
comma
r_int
id|pop
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
id|lifo-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|lifo-&gt;items
(braket
id|i
)braket
dot
id|commit
op_eq
id|commit
)paren
(brace
r_struct
id|commit_info
op_star
id|result
op_assign
op_amp
id|lifo-&gt;items
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pop
)paren
(brace
r_if
c_cond
(paren
id|i
op_plus
l_int|1
OL
id|lifo-&gt;nr
)paren
id|memmove
c_func
(paren
id|lifo-&gt;items
op_plus
id|i
comma
id|lifo-&gt;items
op_plus
id|i
op_plus
l_int|1
comma
(paren
id|lifo-&gt;nr
id|i
)paren
op_star
r_sizeof
(paren
r_struct
id|commit_info
)paren
)paren
suffix:semicolon
id|lifo-&gt;nr
op_decrement
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|add_commit_info
r_static
r_void
id|add_commit_info
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_void
op_star
id|util
comma
r_struct
id|commit_info_lifo
op_star
id|lifo
)paren
(brace
r_struct
id|commit_info
op_star
id|info
suffix:semicolon
r_if
c_cond
(paren
id|lifo-&gt;nr
op_ge
id|lifo-&gt;alloc
)paren
(brace
id|lifo-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|lifo-&gt;nr
op_plus
l_int|1
)paren
suffix:semicolon
id|lifo-&gt;items
op_assign
id|xrealloc
c_func
(paren
id|lifo-&gt;items
comma
id|lifo-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|commit_info
)paren
)paren
suffix:semicolon
)brace
id|info
op_assign
id|lifo-&gt;items
op_plus
id|lifo-&gt;nr
suffix:semicolon
id|info-&gt;commit
op_assign
id|commit
suffix:semicolon
id|info-&gt;util
op_assign
id|util
suffix:semicolon
id|lifo-&gt;nr
op_increment
suffix:semicolon
)brace
DECL|struct|commit_reflog
r_struct
id|commit_reflog
(brace
DECL|member|flag
DECL|member|recno
r_int
id|flag
comma
id|recno
suffix:semicolon
DECL|member|reflogs
r_struct
id|complete_reflogs
op_star
id|reflogs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|reflog_walk_info
r_struct
id|reflog_walk_info
(brace
DECL|member|reflogs
r_struct
id|commit_info_lifo
id|reflogs
suffix:semicolon
DECL|member|complete_reflogs
r_struct
id|path_list
id|complete_reflogs
suffix:semicolon
DECL|member|last_commit_reflog
r_struct
id|commit_reflog
op_star
id|last_commit_reflog
suffix:semicolon
)brace
suffix:semicolon
DECL|function|init_reflog_walk
r_void
id|init_reflog_walk
c_func
(paren
r_struct
id|reflog_walk_info
op_star
op_star
id|info
)paren
(brace
op_star
id|info
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|reflog_walk_info
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|add_reflog_for_walk
r_int
id|add_reflog_for_walk
c_func
(paren
r_struct
id|reflog_walk_info
op_star
id|info
comma
r_struct
id|commit
op_star
id|commit
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|timestamp
op_assign
l_int|0
suffix:semicolon
r_int
id|recno
op_assign
l_int|1
suffix:semicolon
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
r_struct
id|complete_reflogs
op_star
id|reflogs
suffix:semicolon
r_char
op_star
id|branch
comma
op_star
id|at
op_assign
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;@&squot;
)paren
suffix:semicolon
r_struct
id|commit_reflog
op_star
id|commit_reflog
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
id|die
(paren
l_string|&quot;Cannot walk reflogs for %s&quot;
comma
id|name
)paren
suffix:semicolon
id|branch
op_assign
id|xstrdup
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|at
op_logical_and
id|at
(braket
l_int|1
)braket
op_eq
l_char|&squot;{&squot;
)paren
(brace
r_char
op_star
id|ep
suffix:semicolon
id|branch
(braket
id|at
id|name
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|recno
op_assign
id|strtoul
c_func
(paren
id|at
op_plus
l_int|2
comma
op_amp
id|ep
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ep
op_ne
l_char|&squot;}&squot;
)paren
(brace
id|recno
op_assign
l_int|1
suffix:semicolon
id|timestamp
op_assign
id|approxidate
c_func
(paren
id|at
op_plus
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_else
id|recno
op_assign
l_int|0
suffix:semicolon
id|item
op_assign
id|path_list_lookup
c_func
(paren
id|branch
comma
op_amp
id|info-&gt;complete_reflogs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item
)paren
id|reflogs
op_assign
id|item-&gt;util
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_star
id|branch
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_const
r_char
op_star
id|head
op_assign
id|resolve_ref
c_func
(paren
l_string|&quot;HEAD&quot;
comma
id|sha1
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
id|die
(paren
l_string|&quot;No current branch&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|branch
)paren
suffix:semicolon
id|branch
op_assign
id|xstrdup
c_func
(paren
id|head
)paren
suffix:semicolon
)brace
id|reflogs
op_assign
id|read_complete_reflog
c_func
(paren
id|branch
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reflogs
op_logical_or
id|reflogs-&gt;nr
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
r_char
op_star
id|b
suffix:semicolon
r_if
c_cond
(paren
id|dwim_log
c_func
(paren
id|branch
comma
id|strlen
c_func
(paren
id|branch
)paren
comma
id|sha1
comma
op_amp
id|b
)paren
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|reflogs
)paren
(brace
id|free
c_func
(paren
id|reflogs-&gt;ref
)paren
suffix:semicolon
id|free
c_func
(paren
id|reflogs
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|branch
)paren
suffix:semicolon
id|branch
op_assign
id|b
suffix:semicolon
id|reflogs
op_assign
id|read_complete_reflog
c_func
(paren
id|branch
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|reflogs
op_logical_or
id|reflogs-&gt;nr
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|path_list_insert
c_func
(paren
id|branch
comma
op_amp
id|info-&gt;complete_reflogs
)paren
op_member_access_from_pointer
id|util
op_assign
id|reflogs
suffix:semicolon
)brace
id|commit_reflog
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_reflog
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recno
OL
l_int|0
)paren
(brace
id|commit_reflog-&gt;flag
op_assign
l_int|1
suffix:semicolon
id|commit_reflog-&gt;recno
op_assign
id|get_reflog_recno_by_time
c_func
(paren
id|reflogs
comma
id|timestamp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_reflog-&gt;recno
OL
l_int|0
)paren
(brace
id|free
c_func
(paren
id|branch
)paren
suffix:semicolon
id|free
c_func
(paren
id|commit_reflog
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|commit_reflog-&gt;recno
op_assign
id|reflogs-&gt;nr
id|recno
l_int|1
suffix:semicolon
id|commit_reflog-&gt;reflogs
op_assign
id|reflogs
suffix:semicolon
id|add_commit_info
c_func
(paren
id|commit
comma
id|commit_reflog
comma
op_amp
id|info-&gt;reflogs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fake_reflog_parent
r_void
id|fake_reflog_parent
c_func
(paren
r_struct
id|reflog_walk_info
op_star
id|info
comma
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_struct
id|commit_info
op_star
id|commit_info
op_assign
id|get_commit_info
c_func
(paren
id|commit
comma
op_amp
id|info-&gt;reflogs
comma
l_int|0
)paren
suffix:semicolon
r_struct
id|commit_reflog
op_star
id|commit_reflog
suffix:semicolon
r_struct
id|reflog_info
op_star
id|reflog
suffix:semicolon
id|info-&gt;last_commit_reflog
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit_info
)paren
r_return
suffix:semicolon
id|commit_reflog
op_assign
id|commit_info-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|commit_reflog-&gt;recno
OL
l_int|0
)paren
(brace
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|reflog
op_assign
op_amp
id|commit_reflog-&gt;reflogs-&gt;items
(braket
id|commit_reflog-&gt;recno
)braket
suffix:semicolon
id|info-&gt;last_commit_reflog
op_assign
id|commit_reflog
suffix:semicolon
id|commit_reflog-&gt;recno
op_decrement
suffix:semicolon
id|commit_info-&gt;commit
op_assign
(paren
r_struct
id|commit
op_star
)paren
id|parse_object
c_func
(paren
id|reflog-&gt;osha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|commit_info-&gt;commit
)paren
(brace
id|commit-&gt;parents
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|commit-&gt;parents
op_assign
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|commit_list
)paren
comma
l_int|1
)paren
suffix:semicolon
id|commit-&gt;parents-&gt;item
op_assign
id|commit_info-&gt;commit
suffix:semicolon
id|commit-&gt;object.flags
op_and_assign
op_complement
(paren
id|ADDED
op_or
id|SEEN
op_or
id|SHOWN
)paren
suffix:semicolon
)brace
DECL|function|show_reflog_message
r_void
id|show_reflog_message
c_func
(paren
r_struct
id|reflog_walk_info
op_star
id|info
comma
r_int
id|oneline
comma
r_int
id|relative_date
)paren
(brace
r_if
c_cond
(paren
id|info
op_logical_and
id|info-&gt;last_commit_reflog
)paren
(brace
r_struct
id|commit_reflog
op_star
id|commit_reflog
op_assign
id|info-&gt;last_commit_reflog
suffix:semicolon
r_struct
id|reflog_info
op_star
id|info
suffix:semicolon
id|info
op_assign
op_amp
id|commit_reflog-&gt;reflogs-&gt;items
(braket
id|commit_reflog-&gt;recno
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|oneline
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s@{&quot;
comma
id|commit_reflog-&gt;reflogs-&gt;ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_reflog-&gt;flag
op_logical_or
id|relative_date
)paren
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|show_date
c_func
(paren
id|info-&gt;timestamp
comma
l_int|0
comma
l_int|1
)paren
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%d&quot;
comma
id|commit_reflog-&gt;reflogs-&gt;nr
l_int|2
id|commit_reflog-&gt;recno
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;}: %s&quot;
comma
id|info-&gt;message
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;Reflog: %s@{&quot;
comma
id|commit_reflog-&gt;reflogs-&gt;ref
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit_reflog-&gt;flag
op_logical_or
id|relative_date
)paren
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
id|show_date
c_func
(paren
id|info-&gt;timestamp
comma
id|info-&gt;tz
comma
id|relative_date
)paren
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;%d&quot;
comma
id|commit_reflog-&gt;reflogs-&gt;nr
l_int|2
id|commit_reflog-&gt;recno
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;} (%s)&bslash;nReflog message: %s&quot;
comma
id|info-&gt;email
comma
id|info-&gt;message
)paren
suffix:semicolon
)brace
)brace
)brace
eof
