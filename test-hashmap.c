macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;hashmap.h&quot;
macro_line|#include &lt;stdio.h&gt;
DECL|struct|test_entry
r_struct
id|test_entry
(brace
DECL|member|ent
r_struct
id|hashmap_entry
id|ent
suffix:semicolon
multiline_comment|/* key and value as two &bslash;0-terminated strings */
DECL|member|key
r_char
id|key
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|get_value
r_static
r_const
r_char
op_star
id|get_value
c_func
(paren
r_const
r_struct
id|test_entry
op_star
id|e
)paren
(brace
r_return
id|e-&gt;key
op_plus
id|strlen
c_func
(paren
id|e-&gt;key
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|test_entry_cmp
r_static
r_int
id|test_entry_cmp
c_func
(paren
r_const
r_struct
id|test_entry
op_star
id|e1
comma
r_const
r_struct
id|test_entry
op_star
id|e2
comma
r_const
r_char
op_star
id|key
)paren
(brace
r_return
id|strcmp
c_func
(paren
id|e1-&gt;key
comma
id|key
ques
c_cond
id|key
suffix:colon
id|e2-&gt;key
)paren
suffix:semicolon
)brace
DECL|function|test_entry_cmp_icase
r_static
r_int
id|test_entry_cmp_icase
c_func
(paren
r_const
r_struct
id|test_entry
op_star
id|e1
comma
r_const
r_struct
id|test_entry
op_star
id|e2
comma
r_const
r_char
op_star
id|key
)paren
(brace
r_return
id|strcasecmp
c_func
(paren
id|e1-&gt;key
comma
id|key
ques
c_cond
id|key
suffix:colon
id|e2-&gt;key
)paren
suffix:semicolon
)brace
DECL|function|alloc_test_entry
r_static
r_struct
id|test_entry
op_star
id|alloc_test_entry
c_func
(paren
r_int
id|hash
comma
r_char
op_star
id|key
comma
r_int
id|klen
comma
r_char
op_star
id|value
comma
r_int
id|vlen
)paren
(brace
r_struct
id|test_entry
op_star
id|entry
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|test_entry
)paren
op_plus
id|klen
op_plus
id|vlen
op_plus
l_int|2
)paren
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
id|entry
comma
id|hash
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|entry-&gt;key
comma
id|key
comma
id|klen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|entry-&gt;key
op_plus
id|klen
op_plus
l_int|1
comma
id|value
comma
id|vlen
op_plus
l_int|1
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|macro|HASH_METHOD_FNV
mdefine_line|#define HASH_METHOD_FNV 0
DECL|macro|HASH_METHOD_I
mdefine_line|#define HASH_METHOD_I 1
DECL|macro|HASH_METHOD_IDIV10
mdefine_line|#define HASH_METHOD_IDIV10 2
DECL|macro|HASH_METHOD_0
mdefine_line|#define HASH_METHOD_0 3
DECL|macro|HASH_METHOD_X2
mdefine_line|#define HASH_METHOD_X2 4
DECL|macro|TEST_SPARSE
mdefine_line|#define TEST_SPARSE 8
DECL|macro|TEST_ADD
mdefine_line|#define TEST_ADD 16
DECL|macro|TEST_SIZE
mdefine_line|#define TEST_SIZE 100000
DECL|function|hash
r_static
r_int
r_int
id|hash
c_func
(paren
r_int
r_int
id|method
comma
r_int
r_int
id|i
comma
r_const
r_char
op_star
id|key
)paren
(brace
r_int
r_int
id|hash
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|method
op_amp
l_int|3
)paren
(brace
r_case
id|HASH_METHOD_FNV
suffix:colon
id|hash
op_assign
id|strhash
c_func
(paren
id|key
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HASH_METHOD_I
suffix:colon
id|hash
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HASH_METHOD_IDIV10
suffix:colon
id|hash
op_assign
id|i
op_div
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HASH_METHOD_0
suffix:colon
id|hash
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|method
op_amp
id|HASH_METHOD_X2
)paren
id|hash
op_assign
l_int|2
op_star
id|hash
suffix:semicolon
r_return
id|hash
suffix:semicolon
)brace
multiline_comment|/*&n; * Test performance of hashmap.[ch]&n; * Usage: time echo &quot;perfhashmap method rounds&quot; | test-hashmap&n; */
DECL|function|perf_hashmap
r_static
r_void
id|perf_hashmap
c_func
(paren
r_int
r_int
id|method
comma
r_int
r_int
id|rounds
)paren
(brace
r_struct
id|hashmap
id|map
suffix:semicolon
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|test_entry
op_star
op_star
id|entries
suffix:semicolon
r_int
r_int
op_star
id|hashes
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
id|entries
op_assign
id|malloc
c_func
(paren
id|TEST_SIZE
op_star
r_sizeof
(paren
r_struct
id|test_entry
op_star
)paren
)paren
suffix:semicolon
id|hashes
op_assign
id|malloc
c_func
(paren
id|TEST_SIZE
op_star
r_sizeof
(paren
r_int
)paren
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
id|TEST_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;%i&quot;
comma
id|i
)paren
suffix:semicolon
id|entries
(braket
id|i
)braket
op_assign
id|alloc_test_entry
c_func
(paren
l_int|0
comma
id|buf
comma
id|strlen
c_func
(paren
id|buf
)paren
comma
l_string|&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
id|hashes
(braket
id|i
)braket
op_assign
id|hash
c_func
(paren
id|method
comma
id|i
comma
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|key
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|method
op_amp
id|TEST_ADD
)paren
(brace
multiline_comment|/* test adding to the map */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rounds
suffix:semicolon
id|j
op_increment
)paren
(brace
id|hashmap_init
c_func
(paren
op_amp
id|map
comma
(paren
id|hashmap_cmp_fn
)paren
id|test_entry_cmp
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* add entries */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TEST_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hashmap_entry_init
c_func
(paren
id|entries
(braket
id|i
)braket
comma
id|hashes
(braket
id|i
)braket
)paren
suffix:semicolon
id|hashmap_add
c_func
(paren
op_amp
id|map
comma
id|entries
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|hashmap_free
c_func
(paren
op_amp
id|map
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* test map lookups */
id|hashmap_init
c_func
(paren
op_amp
id|map
comma
(paren
id|hashmap_cmp_fn
)paren
id|test_entry_cmp
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* fill the map (sparsely if specified) */
id|j
op_assign
(paren
id|method
op_amp
id|TEST_SPARSE
)paren
ques
c_cond
id|TEST_SIZE
op_div
l_int|10
suffix:colon
id|TEST_SIZE
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
id|j
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hashmap_entry_init
c_func
(paren
id|entries
(braket
id|i
)braket
comma
id|hashes
(braket
id|i
)braket
)paren
suffix:semicolon
id|hashmap_add
c_func
(paren
op_amp
id|map
comma
id|entries
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rounds
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TEST_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|hashmap_entry
id|key
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
op_amp
id|key
comma
id|hashes
(braket
id|i
)braket
)paren
suffix:semicolon
id|hashmap_get
c_func
(paren
op_amp
id|map
comma
op_amp
id|key
comma
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|key
)paren
suffix:semicolon
)brace
)brace
id|hashmap_free
c_func
(paren
op_amp
id|map
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|struct|hash_entry
r_struct
id|hash_entry
(brace
DECL|member|next
r_struct
id|hash_entry
op_star
id|next
suffix:semicolon
DECL|member|key
r_char
id|key
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Test performance of hash.[ch]&n; * Usage: time echo &quot;perfhash method rounds&quot; | test-hashmap&n; */
DECL|function|perf_hash
r_static
r_void
id|perf_hash
c_func
(paren
r_int
r_int
id|method
comma
r_int
r_int
id|rounds
)paren
(brace
r_struct
id|hash_table
id|map
suffix:semicolon
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|hash_entry
op_star
op_star
id|entries
comma
op_star
op_star
id|res
comma
op_star
id|entry
suffix:semicolon
r_int
r_int
op_star
id|hashes
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
id|entries
op_assign
id|malloc
c_func
(paren
id|TEST_SIZE
op_star
r_sizeof
(paren
r_struct
id|hash_entry
op_star
)paren
)paren
suffix:semicolon
id|hashes
op_assign
id|malloc
c_func
(paren
id|TEST_SIZE
op_star
r_sizeof
(paren
r_int
)paren
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
id|TEST_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;%i&quot;
comma
id|i
)paren
suffix:semicolon
id|entries
(braket
id|i
)braket
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hash_entry
)paren
op_plus
id|strlen
c_func
(paren
id|buf
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|key
comma
id|buf
)paren
suffix:semicolon
id|hashes
(braket
id|i
)braket
op_assign
id|hash
c_func
(paren
id|method
comma
id|i
comma
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|key
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|method
op_amp
id|TEST_ADD
)paren
(brace
multiline_comment|/* test adding to the map */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rounds
suffix:semicolon
id|j
op_increment
)paren
(brace
id|init_hash
c_func
(paren
op_amp
id|map
)paren
suffix:semicolon
multiline_comment|/* add entries */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TEST_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|res
op_assign
(paren
r_struct
id|hash_entry
op_star
op_star
)paren
id|insert_hash
c_func
(paren
id|hashes
(braket
id|i
)braket
comma
id|entries
(braket
id|i
)braket
comma
op_amp
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|next
op_assign
op_star
id|res
suffix:semicolon
op_star
id|res
op_assign
id|entries
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
(brace
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|free_hash
c_func
(paren
op_amp
id|map
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* test map lookups */
id|init_hash
c_func
(paren
op_amp
id|map
)paren
suffix:semicolon
multiline_comment|/* fill the map (sparsely if specified) */
id|j
op_assign
(paren
id|method
op_amp
id|TEST_SPARSE
)paren
ques
c_cond
id|TEST_SIZE
op_div
l_int|10
suffix:colon
id|TEST_SIZE
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
id|j
suffix:semicolon
id|i
op_increment
)paren
(brace
id|res
op_assign
(paren
r_struct
id|hash_entry
op_star
op_star
)paren
id|insert_hash
c_func
(paren
id|hashes
(braket
id|i
)braket
comma
id|entries
(braket
id|i
)braket
comma
op_amp
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|next
op_assign
op_star
id|res
suffix:semicolon
op_star
id|res
op_assign
id|entries
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
(brace
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|rounds
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TEST_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|lookup_hash
c_func
(paren
id|hashes
(braket
id|i
)braket
comma
op_amp
id|map
)paren
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|entries
(braket
id|i
)braket
op_member_access_from_pointer
id|key
comma
id|entry-&gt;key
)paren
)paren
r_break
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
)brace
)brace
id|free_hash
c_func
(paren
op_amp
id|map
)paren
suffix:semicolon
)brace
)brace
DECL|macro|DELIM
mdefine_line|#define DELIM &quot; &bslash;t&bslash;r&bslash;n&quot;
multiline_comment|/*&n; * Read stdin line by line and print result of commands to stdout:&n; *&n; * hash key -&gt; strhash(key) memhash(key) strihash(key) memihash(key)&n; * put key value -&gt; NULL / old value&n; * get key -&gt; NULL / value&n; * remove key -&gt; NULL / old value&n; * iterate -&gt; key1 value1&bslash;nkey2 value2&bslash;n...&n; * size -&gt; tablesize numentries&n; *&n; * perfhashmap method rounds -&gt; test hashmap.[ch] performance&n; * perfhash method rounds -&gt; test hash.[ch] performance&n; */
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
r_char
id|line
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|hashmap
id|map
suffix:semicolon
r_int
id|icase
suffix:semicolon
multiline_comment|/* init hash map */
id|icase
op_assign
id|argc
OG
l_int|1
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;ignorecase&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|hashmap_init
c_func
(paren
op_amp
id|map
comma
(paren
id|hashmap_cmp_fn
)paren
(paren
id|icase
ques
c_cond
id|test_entry_cmp_icase
suffix:colon
id|test_entry_cmp
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* process commands from stdin */
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|line
comma
r_sizeof
(paren
id|line
)paren
comma
id|stdin
)paren
)paren
(brace
r_char
op_star
id|cmd
comma
op_star
id|p1
op_assign
l_int|NULL
comma
op_star
id|p2
op_assign
l_int|NULL
suffix:semicolon
r_int
id|l1
op_assign
l_int|0
comma
id|l2
op_assign
l_int|0
comma
id|hash
op_assign
l_int|0
suffix:semicolon
r_struct
id|test_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* break line into command and up to two parameters */
id|cmd
op_assign
id|strtok
c_func
(paren
id|line
comma
id|DELIM
)paren
suffix:semicolon
multiline_comment|/* ignore empty lines */
r_if
c_cond
(paren
op_logical_neg
id|cmd
op_logical_or
op_star
id|cmd
op_eq
l_char|&squot;#&squot;
)paren
r_continue
suffix:semicolon
id|p1
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
id|DELIM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p1
)paren
(brace
id|l1
op_assign
id|strlen
c_func
(paren
id|p1
)paren
suffix:semicolon
id|hash
op_assign
id|icase
ques
c_cond
id|strihash
c_func
(paren
id|p1
)paren
suffix:colon
id|strhash
c_func
(paren
id|p1
)paren
suffix:semicolon
id|p2
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
id|DELIM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p2
)paren
id|l2
op_assign
id|strlen
c_func
(paren
id|p2
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
l_string|&quot;hash&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
)paren
(brace
multiline_comment|/* print results of different hash functions */
id|printf
c_func
(paren
l_string|&quot;%u %u %u %u&bslash;n&quot;
comma
id|strhash
c_func
(paren
id|p1
)paren
comma
id|memhash
c_func
(paren
id|p1
comma
id|l1
)paren
comma
id|strihash
c_func
(paren
id|p1
)paren
comma
id|memihash
c_func
(paren
id|p1
comma
id|l1
)paren
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
l_string|&quot;add&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
op_logical_and
id|l2
)paren
(brace
multiline_comment|/* create entry with key = p1, value = p2 */
id|entry
op_assign
id|alloc_test_entry
c_func
(paren
id|hash
comma
id|p1
comma
id|l1
comma
id|p2
comma
id|l2
)paren
suffix:semicolon
multiline_comment|/* add to hashmap */
id|hashmap_add
c_func
(paren
op_amp
id|map
comma
id|entry
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
l_string|&quot;put&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
op_logical_and
id|l2
)paren
(brace
multiline_comment|/* create entry with key = p1, value = p2 */
id|entry
op_assign
id|alloc_test_entry
c_func
(paren
id|hash
comma
id|p1
comma
id|l1
comma
id|p2
comma
id|l2
)paren
suffix:semicolon
multiline_comment|/* add / replace entry */
id|entry
op_assign
id|hashmap_put
c_func
(paren
op_amp
id|map
comma
id|entry
)paren
suffix:semicolon
multiline_comment|/* print and free replaced entry, if any */
id|puts
c_func
(paren
id|entry
ques
c_cond
id|get_value
c_func
(paren
id|entry
)paren
suffix:colon
l_string|&quot;NULL&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry
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
l_string|&quot;get&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
)paren
(brace
multiline_comment|/* setup static key */
r_struct
id|hashmap_entry
id|key
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
op_amp
id|key
comma
id|hash
)paren
suffix:semicolon
multiline_comment|/* lookup entry in hashmap */
id|entry
op_assign
id|hashmap_get
c_func
(paren
op_amp
id|map
comma
op_amp
id|key
comma
id|p1
)paren
suffix:semicolon
multiline_comment|/* print result */
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
id|puts
c_func
(paren
l_string|&quot;NULL&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
id|puts
c_func
(paren
id|get_value
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
id|entry
op_assign
id|hashmap_get_next
c_func
(paren
op_amp
id|map
comma
id|entry
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
l_string|&quot;remove&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
)paren
(brace
multiline_comment|/* setup static key */
r_struct
id|hashmap_entry
id|key
suffix:semicolon
id|hashmap_entry_init
c_func
(paren
op_amp
id|key
comma
id|hash
)paren
suffix:semicolon
multiline_comment|/* remove entry from hashmap */
id|entry
op_assign
id|hashmap_remove
c_func
(paren
op_amp
id|map
comma
op_amp
id|key
comma
id|p1
)paren
suffix:semicolon
multiline_comment|/* print result and free entry*/
id|puts
c_func
(paren
id|entry
ques
c_cond
id|get_value
c_func
(paren
id|entry
)paren
suffix:colon
l_string|&quot;NULL&quot;
)paren
suffix:semicolon
id|free
c_func
(paren
id|entry
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
l_string|&quot;iterate&quot;
comma
id|cmd
)paren
)paren
(brace
r_struct
id|hashmap_iter
id|iter
suffix:semicolon
id|hashmap_iter_init
c_func
(paren
op_amp
id|map
comma
op_amp
id|iter
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|hashmap_iter_next
c_func
(paren
op_amp
id|iter
)paren
)paren
)paren
id|printf
c_func
(paren
l_string|&quot;%s %s&bslash;n&quot;
comma
id|entry-&gt;key
comma
id|get_value
c_func
(paren
id|entry
)paren
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
l_string|&quot;size&quot;
comma
id|cmd
)paren
)paren
(brace
multiline_comment|/* print table sizes */
id|printf
c_func
(paren
l_string|&quot;%u %u&bslash;n&quot;
comma
id|map.tablesize
comma
id|map.size
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
l_string|&quot;perfhashmap&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
op_logical_and
id|l2
)paren
(brace
id|perf_hashmap
c_func
(paren
id|atoi
c_func
(paren
id|p1
)paren
comma
id|atoi
c_func
(paren
id|p2
)paren
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
l_string|&quot;perfhash&quot;
comma
id|cmd
)paren
op_logical_and
id|l1
op_logical_and
id|l2
)paren
(brace
id|perf_hash
c_func
(paren
id|atoi
c_func
(paren
id|p1
)paren
comma
id|atoi
c_func
(paren
id|p2
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;Unknown command %s&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
)brace
)brace
id|hashmap_free
c_func
(paren
op_amp
id|map
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
