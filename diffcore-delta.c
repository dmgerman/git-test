macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;diffcore.h&quot;
multiline_comment|/*&n; * Idea here is very simple.&n; *&n; * Almost all data we are interested in are text, but sometimes we have&n; * to deal with binary data.  So we cut them into chunks delimited by&n; * LF byte, or 64-byte sequence, whichever comes first, and hash them.&n; *&n; * For those chunks, if the source buffer has more instances of it&n; * than the destination buffer, that means the difference are the&n; * number of bytes not copied from source to destination.  If the&n; * counts are the same, everything was copied from source to&n; * destination.  If the destination has more, everything was copied,&n; * and destination added more.&n; *&n; * We are doing an approximation so we do not really have to waste&n; * memory by actually storing the sequence.  We just hash them into&n; * somewhere around 2^16 hashbuckets and count the occurrences.&n; */
multiline_comment|/* Wild guess at the initial hash size */
DECL|macro|INITIAL_HASH_SIZE
mdefine_line|#define INITIAL_HASH_SIZE 9
multiline_comment|/* We leave more room in smaller hash but do not let it&n; * grow to have unused hole too much.&n; */
DECL|macro|INITIAL_FREE
mdefine_line|#define INITIAL_FREE(sz_log2) ((1&lt;&lt;(sz_log2))*(sz_log2-3)/(sz_log2))
multiline_comment|/* A prime rather carefully chosen between 2^16..2^17, so that&n; * HASHBASE &lt; INITIAL_FREE(17).  We want to keep the maximum hashtable&n; * size under the current 2&lt;&lt;17 maximum, which can hold this many&n; * different values before overflowing to hashtable of size 2&lt;&lt;18.&n; */
DECL|macro|HASHBASE
mdefine_line|#define HASHBASE 107927
DECL|struct|spanhash
r_struct
id|spanhash
(brace
DECL|member|hashval
r_int
r_int
id|hashval
suffix:semicolon
DECL|member|cnt
r_int
r_int
id|cnt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|spanhash_top
r_struct
id|spanhash_top
(brace
DECL|member|alloc_log2
r_int
id|alloc_log2
suffix:semicolon
DECL|member|free
r_int
id|free
suffix:semicolon
DECL|member|data
r_struct
id|spanhash
id|data
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|spanhash_find
r_static
r_struct
id|spanhash
op_star
id|spanhash_find
c_func
(paren
r_struct
id|spanhash_top
op_star
id|top
comma
r_int
r_int
id|hashval
)paren
(brace
r_int
id|sz
op_assign
l_int|1
op_lshift
id|top-&gt;alloc_log2
suffix:semicolon
r_int
id|bucket
op_assign
id|hashval
op_amp
(paren
id|sz
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|spanhash
op_star
id|h
op_assign
op_amp
(paren
id|top-&gt;data
(braket
id|bucket
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h-&gt;cnt
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|h-&gt;hashval
op_eq
id|hashval
)paren
r_return
id|h
suffix:semicolon
r_if
c_cond
(paren
id|sz
op_le
id|bucket
)paren
id|bucket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|spanhash_rehash
r_static
r_struct
id|spanhash_top
op_star
id|spanhash_rehash
c_func
(paren
r_struct
id|spanhash_top
op_star
id|orig
)paren
(brace
r_struct
id|spanhash_top
op_star
r_new
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|osz
op_assign
l_int|1
op_lshift
id|orig-&gt;alloc_log2
suffix:semicolon
r_int
id|sz
op_assign
id|osz
op_lshift
l_int|1
suffix:semicolon
r_new
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|orig
)paren
op_plus
r_sizeof
(paren
r_struct
id|spanhash
)paren
op_star
id|sz
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|alloc_log2
op_assign
id|orig-&gt;alloc_log2
op_plus
l_int|1
suffix:semicolon
r_new
op_member_access_from_pointer
id|free
op_assign
id|INITIAL_FREE
c_func
(paren
r_new
op_member_access_from_pointer
id|alloc_log2
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
op_member_access_from_pointer
id|data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|spanhash
)paren
op_star
id|sz
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
id|osz
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|spanhash
op_star
id|o
op_assign
op_amp
(paren
id|orig-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
r_int
id|bucket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|o-&gt;cnt
)paren
r_continue
suffix:semicolon
id|bucket
op_assign
id|o-&gt;hashval
op_amp
(paren
id|sz
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|spanhash
op_star
id|h
op_assign
op_amp
(paren
r_new
op_member_access_from_pointer
id|data
(braket
id|bucket
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h-&gt;cnt
)paren
(brace
id|h-&gt;hashval
op_assign
id|o-&gt;hashval
suffix:semicolon
id|h-&gt;cnt
op_assign
id|o-&gt;cnt
suffix:semicolon
r_new
op_member_access_from_pointer
id|free
op_decrement
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sz
op_le
id|bucket
)paren
id|bucket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|free
c_func
(paren
id|orig
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
DECL|function|add_spanhash
r_static
r_struct
id|spanhash_top
op_star
id|add_spanhash
c_func
(paren
r_struct
id|spanhash_top
op_star
id|top
comma
r_int
r_int
id|hashval
comma
r_int
id|cnt
)paren
(brace
r_int
id|bucket
comma
id|lim
suffix:semicolon
r_struct
id|spanhash
op_star
id|h
suffix:semicolon
id|lim
op_assign
(paren
l_int|1
op_lshift
id|top-&gt;alloc_log2
)paren
suffix:semicolon
id|bucket
op_assign
id|hashval
op_amp
(paren
id|lim
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|h
op_assign
op_amp
(paren
id|top-&gt;data
(braket
id|bucket
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h-&gt;cnt
)paren
(brace
id|h-&gt;hashval
op_assign
id|hashval
suffix:semicolon
id|h-&gt;cnt
op_assign
id|cnt
suffix:semicolon
id|top-&gt;free
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|top-&gt;free
OL
l_int|0
)paren
r_return
id|spanhash_rehash
c_func
(paren
id|top
)paren
suffix:semicolon
r_return
id|top
suffix:semicolon
)brace
r_if
c_cond
(paren
id|h-&gt;hashval
op_eq
id|hashval
)paren
(brace
id|h-&gt;cnt
op_add_assign
id|cnt
suffix:semicolon
r_return
id|top
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lim
op_le
id|bucket
)paren
id|bucket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|hash_chars
r_static
r_struct
id|spanhash_top
op_star
id|hash_chars
c_func
(paren
r_struct
id|diff_filespec
op_star
id|one
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
r_int
r_int
id|accum1
comma
id|accum2
comma
id|hashval
suffix:semicolon
r_struct
id|spanhash_top
op_star
id|hash
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|one-&gt;data
suffix:semicolon
r_int
r_int
id|sz
op_assign
id|one-&gt;size
suffix:semicolon
r_int
id|is_text
op_assign
op_logical_neg
id|diff_filespec_is_binary
c_func
(paren
id|one
)paren
suffix:semicolon
id|i
op_assign
id|INITIAL_HASH_SIZE
suffix:semicolon
id|hash
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|hash
)paren
op_plus
r_sizeof
(paren
r_struct
id|spanhash
)paren
op_star
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
id|hash-&gt;alloc_log2
op_assign
id|i
suffix:semicolon
id|hash-&gt;free
op_assign
id|INITIAL_FREE
c_func
(paren
id|i
)paren
suffix:semicolon
id|memset
c_func
(paren
id|hash-&gt;data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|spanhash
)paren
op_star
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
id|n
op_assign
l_int|0
suffix:semicolon
id|accum1
op_assign
id|accum2
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|sz
)paren
(brace
r_int
r_int
id|c
op_assign
op_star
id|buf
op_increment
suffix:semicolon
r_int
r_int
id|old_1
op_assign
id|accum1
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
multiline_comment|/* Ignore CR in CRLF sequence if text */
r_if
c_cond
(paren
id|is_text
op_logical_and
id|c
op_eq
l_char|&squot;&bslash;r&squot;
op_logical_and
id|sz
op_logical_and
op_star
id|buf
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
id|accum1
op_assign
(paren
id|accum1
op_lshift
l_int|7
)paren
op_xor
(paren
id|accum2
op_rshift
l_int|25
)paren
suffix:semicolon
id|accum2
op_assign
(paren
id|accum2
op_lshift
l_int|7
)paren
op_xor
(paren
id|old_1
op_rshift
l_int|25
)paren
suffix:semicolon
id|accum1
op_add_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|n
OL
l_int|64
op_logical_and
id|c
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_continue
suffix:semicolon
id|hashval
op_assign
(paren
id|accum1
op_plus
id|accum2
op_star
l_int|0x61
)paren
op_mod
id|HASHBASE
suffix:semicolon
id|hash
op_assign
id|add_spanhash
c_func
(paren
id|hash
comma
id|hashval
comma
id|n
)paren
suffix:semicolon
id|n
op_assign
l_int|0
suffix:semicolon
id|accum1
op_assign
id|accum2
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|hash
suffix:semicolon
)brace
DECL|function|diffcore_count_changes
r_int
id|diffcore_count_changes
c_func
(paren
r_struct
id|diff_filespec
op_star
id|src
comma
r_struct
id|diff_filespec
op_star
id|dst
comma
r_void
op_star
op_star
id|src_count_p
comma
r_void
op_star
op_star
id|dst_count_p
comma
r_int
r_int
id|delta_limit
comma
r_int
r_int
op_star
id|src_copied
comma
r_int
r_int
op_star
id|literal_added
)paren
(brace
r_int
id|i
comma
id|ssz
suffix:semicolon
r_struct
id|spanhash_top
op_star
id|src_count
comma
op_star
id|dst_count
suffix:semicolon
r_int
r_int
id|sc
comma
id|la
suffix:semicolon
id|src_count
op_assign
id|dst_count
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|src_count_p
)paren
id|src_count
op_assign
op_star
id|src_count_p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|src_count
)paren
(brace
id|src_count
op_assign
id|hash_chars
c_func
(paren
id|src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src_count_p
)paren
op_star
id|src_count_p
op_assign
id|src_count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dst_count_p
)paren
id|dst_count
op_assign
op_star
id|dst_count_p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_count
)paren
(brace
id|dst_count
op_assign
id|hash_chars
c_func
(paren
id|dst
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst_count_p
)paren
op_star
id|dst_count_p
op_assign
id|dst_count
suffix:semicolon
)brace
id|sc
op_assign
id|la
op_assign
l_int|0
suffix:semicolon
id|ssz
op_assign
l_int|1
op_lshift
id|src_count-&gt;alloc_log2
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
id|ssz
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|spanhash
op_star
id|s
op_assign
op_amp
(paren
id|src_count-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
r_struct
id|spanhash
op_star
id|d
suffix:semicolon
r_int
id|dst_cnt
comma
id|src_cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;cnt
)paren
r_continue
suffix:semicolon
id|src_cnt
op_assign
id|s-&gt;cnt
suffix:semicolon
id|d
op_assign
id|spanhash_find
c_func
(paren
id|dst_count
comma
id|s-&gt;hashval
)paren
suffix:semicolon
id|dst_cnt
op_assign
id|d
ques
c_cond
id|d-&gt;cnt
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|src_cnt
OL
id|dst_cnt
)paren
(brace
id|la
op_add_assign
id|dst_cnt
id|src_cnt
suffix:semicolon
id|sc
op_add_assign
id|src_cnt
suffix:semicolon
)brace
r_else
id|sc
op_add_assign
id|dst_cnt
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|src_count_p
)paren
id|free
c_func
(paren
id|src_count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst_count_p
)paren
id|free
c_func
(paren
id|dst_count
)paren
suffix:semicolon
op_star
id|src_copied
op_assign
id|sc
suffix:semicolon
op_star
id|literal_added
op_assign
id|la
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
