macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;notes.h&quot;
macro_line|#include &quot;refs.h&quot;
macro_line|#include &quot;utf8.h&quot;
macro_line|#include &quot;strbuf.h&quot;
macro_line|#include &quot;tree-walk.h&quot;
DECL|struct|entry
r_struct
id|entry
(brace
DECL|member|commit_sha1
r_int
r_char
id|commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|notes_sha1
r_int
r_char
id|notes_sha1
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hash_map
r_struct
id|hash_map
(brace
DECL|member|entries
r_struct
id|entry
op_star
id|entries
suffix:semicolon
DECL|member|count
DECL|member|size
id|off_t
id|count
comma
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
suffix:semicolon
DECL|variable|hash_map
r_static
r_struct
id|hash_map
id|hash_map
suffix:semicolon
DECL|function|hash_index
r_static
r_int
id|hash_index
c_func
(paren
r_struct
id|hash_map
op_star
id|map
comma
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_int
id|i
op_assign
(paren
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|sha1
)paren
op_mod
id|map-&gt;size
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_char
op_star
id|current
op_assign
id|map-&gt;entries
(braket
id|i
)braket
dot
id|commit_sha1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hashcmp
c_func
(paren
id|sha1
comma
id|current
)paren
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|is_null_sha1
c_func
(paren
id|current
)paren
)paren
r_return
l_int|1
id|i
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|i
op_eq
id|map-&gt;size
)paren
id|i
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|add_entry
r_static
r_void
id|add_entry
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
comma
r_const
r_int
r_char
op_star
id|notes_sha1
)paren
(brace
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
id|hash_map.count
op_plus
l_int|1
OG
id|hash_map.size
op_rshift
l_int|1
)paren
(brace
r_int
id|i
comma
id|old_size
op_assign
id|hash_map.size
suffix:semicolon
r_struct
id|entry
op_star
id|old
op_assign
id|hash_map.entries
suffix:semicolon
id|hash_map.size
op_assign
id|old_size
ques
c_cond
id|old_size
op_lshift
l_int|1
suffix:colon
l_int|64
suffix:semicolon
id|hash_map.entries
op_assign
(paren
r_struct
id|entry
op_star
)paren
id|xcalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|entry
)paren
comma
id|hash_map.size
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
id|old_size
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|is_null_sha1
c_func
(paren
id|old
(braket
id|i
)braket
dot
id|commit_sha1
)paren
)paren
(brace
id|index
op_assign
l_int|1
id|hash_index
c_func
(paren
op_amp
id|hash_map
comma
id|old
(braket
id|i
)braket
dot
id|commit_sha1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hash_map.entries
op_plus
id|index
comma
id|old
op_plus
id|i
comma
r_sizeof
(paren
r_struct
id|entry
)paren
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
id|index
op_assign
id|hash_index
c_func
(paren
op_amp
id|hash_map
comma
id|commit_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
)paren
(brace
id|index
op_assign
l_int|1
id|index
suffix:semicolon
id|hash_map.count
op_increment
suffix:semicolon
)brace
id|hashcpy
c_func
(paren
id|hash_map.entries
(braket
id|index
)braket
dot
id|commit_sha1
comma
id|commit_sha1
)paren
suffix:semicolon
id|hashcpy
c_func
(paren
id|hash_map.entries
(braket
id|index
)braket
dot
id|notes_sha1
comma
id|notes_sha1
)paren
suffix:semicolon
)brace
DECL|function|initialize_hash_map
r_static
r_void
id|initialize_hash_map
c_func
(paren
r_const
r_char
op_star
id|notes_ref_name
)paren
(brace
r_int
r_char
id|sha1
(braket
l_int|20
)braket
comma
id|commit_sha1
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_struct
id|tree_desc
id|desc
suffix:semicolon
r_struct
id|name_entry
id|entry
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|notes_ref_name
op_logical_or
id|read_ref
c_func
(paren
id|notes_ref_name
comma
id|commit_sha1
)paren
op_logical_or
id|get_tree_entry
c_func
(paren
id|commit_sha1
comma
l_string|&quot;&quot;
comma
id|sha1
comma
op_amp
id|mode
)paren
)paren
r_return
suffix:semicolon
id|buf
op_assign
id|fill_tree_descriptor
c_func
(paren
op_amp
id|desc
comma
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|die
c_func
(paren
l_string|&quot;Could not read %s for notes-index&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tree_entry
c_func
(paren
op_amp
id|desc
comma
op_amp
id|entry
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|get_sha1
c_func
(paren
id|entry.path
comma
id|commit_sha1
)paren
)paren
id|add_entry
c_func
(paren
id|commit_sha1
comma
id|entry.sha1
)paren
suffix:semicolon
id|free
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|lookup_notes
r_static
r_int
r_char
op_star
id|lookup_notes
c_func
(paren
r_const
r_int
r_char
op_star
id|commit_sha1
)paren
(brace
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash_map.size
)paren
r_return
l_int|NULL
suffix:semicolon
id|index
op_assign
id|hash_index
c_func
(paren
op_amp
id|hash_map
comma
id|commit_sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|hash_map.entries
(braket
id|index
)braket
dot
id|notes_sha1
suffix:semicolon
)brace
DECL|function|get_commit_notes
r_void
id|get_commit_notes
c_func
(paren
r_const
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|strbuf
op_star
id|sb
comma
r_const
r_char
op_star
id|output_encoding
)paren
(brace
r_static
r_const
r_char
op_star
id|utf8
op_assign
l_string|&quot;utf-8&quot;
suffix:semicolon
r_int
r_char
op_star
id|sha1
suffix:semicolon
r_char
op_star
id|msg
suffix:semicolon
r_int
r_int
id|msgoffset
comma
id|msglen
suffix:semicolon
r_enum
id|object_type
id|type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
r_const
r_char
op_star
id|env
op_assign
id|getenv
c_func
(paren
id|GIT_NOTES_REF_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|env
)paren
id|notes_ref_name
op_assign
id|getenv
c_func
(paren
id|GIT_NOTES_REF_ENVIRONMENT
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|notes_ref_name
)paren
id|notes_ref_name
op_assign
id|GIT_NOTES_DEFAULT_REF
suffix:semicolon
id|initialize_hash_map
c_func
(paren
id|notes_ref_name
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
id|sha1
op_assign
id|lookup_notes
c_func
(paren
id|commit-&gt;object.sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sha1
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|msg
op_assign
id|read_sha1_file
c_func
(paren
id|sha1
comma
op_amp
id|type
comma
op_amp
id|msglen
)paren
)paren
op_logical_or
op_logical_neg
id|msglen
op_logical_or
id|type
op_ne
id|OBJ_BLOB
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|output_encoding
op_logical_and
op_star
id|output_encoding
op_logical_and
id|strcmp
c_func
(paren
id|utf8
comma
id|output_encoding
)paren
)paren
(brace
r_char
op_star
id|reencoded
op_assign
id|reencode_string
c_func
(paren
id|msg
comma
id|output_encoding
comma
id|utf8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reencoded
)paren
(brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
id|msg
op_assign
id|reencoded
suffix:semicolon
id|msglen
op_assign
id|strlen
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* we will end the annotation by a newline anyway */
r_if
c_cond
(paren
id|msglen
op_logical_and
id|msg
(braket
id|msglen
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|msglen
op_decrement
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
l_string|&quot;&bslash;nNotes:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|msgoffset
op_assign
l_int|0
suffix:semicolon
id|msgoffset
OL
id|msglen
suffix:semicolon
)paren
(brace
r_int
id|linelen
op_assign
id|strchrnul
c_func
(paren
id|msg
comma
l_char|&squot;&bslash;n&squot;
)paren
id|msg
suffix:semicolon
id|strbuf_addstr
c_func
(paren
id|sb
comma
l_string|&quot;    &quot;
)paren
suffix:semicolon
id|strbuf_add
c_func
(paren
id|sb
comma
id|msg
op_plus
id|msgoffset
comma
id|linelen
)paren
suffix:semicolon
id|msgoffset
op_add_assign
id|linelen
suffix:semicolon
)brace
id|free
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
eof
