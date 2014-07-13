multiline_comment|/*&n; * alloc.c  - specialized allocator for internal objects&n; *&n; * Copyright (C) 2006 Linus Torvalds&n; *&n; * The standard malloc/free wastes too much space for objects, partly because&n; * it maintains all the allocation infrastructure (which isn&squot;t needed, since&n; * we never free an object descriptor anyway), but even more because it ends&n; * up with maximal alignment because it doesn&squot;t know what the object alignment&n; * for the new allocation is.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
DECL|macro|BLOCKING
mdefine_line|#define BLOCKING 1024
DECL|union|any_object
r_union
id|any_object
(brace
DECL|member|object
r_struct
id|object
id|object
suffix:semicolon
DECL|member|blob
r_struct
id|blob
id|blob
suffix:semicolon
DECL|member|tree
r_struct
id|tree
id|tree
suffix:semicolon
DECL|member|commit
r_struct
id|commit
id|commit
suffix:semicolon
DECL|member|tag
r_struct
id|tag
id|tag
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|alloc_state
r_struct
id|alloc_state
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* total number of nodes allocated */
DECL|member|nr
r_int
id|nr
suffix:semicolon
multiline_comment|/* number of nodes left in current allocation */
DECL|member|p
r_void
op_star
id|p
suffix:semicolon
multiline_comment|/* first free node in current allocation */
)brace
suffix:semicolon
DECL|function|alloc_node
r_static
r_inline
r_void
op_star
id|alloc_node
c_func
(paren
r_struct
id|alloc_state
op_star
id|s
comma
r_int
id|node_size
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;nr
)paren
(brace
id|s-&gt;nr
op_assign
id|BLOCKING
suffix:semicolon
id|s-&gt;p
op_assign
id|xmalloc
c_func
(paren
id|BLOCKING
op_star
id|node_size
)paren
suffix:semicolon
)brace
id|s-&gt;nr
op_decrement
suffix:semicolon
id|s-&gt;count
op_increment
suffix:semicolon
id|ret
op_assign
id|s-&gt;p
suffix:semicolon
id|s-&gt;p
op_assign
(paren
r_char
op_star
)paren
id|s-&gt;p
op_plus
id|node_size
suffix:semicolon
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|node_size
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|blob_state
r_static
r_struct
id|alloc_state
id|blob_state
suffix:semicolon
DECL|function|alloc_blob_node
r_void
op_star
id|alloc_blob_node
c_func
(paren
r_void
)paren
(brace
r_struct
id|blob
op_star
id|b
op_assign
id|alloc_node
c_func
(paren
op_amp
id|blob_state
comma
r_sizeof
(paren
r_struct
id|blob
)paren
)paren
suffix:semicolon
id|b-&gt;object.type
op_assign
id|OBJ_BLOB
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
DECL|variable|tree_state
r_static
r_struct
id|alloc_state
id|tree_state
suffix:semicolon
DECL|function|alloc_tree_node
r_void
op_star
id|alloc_tree_node
c_func
(paren
r_void
)paren
(brace
r_struct
id|tree
op_star
id|t
op_assign
id|alloc_node
c_func
(paren
op_amp
id|tree_state
comma
r_sizeof
(paren
r_struct
id|tree
)paren
)paren
suffix:semicolon
id|t-&gt;object.type
op_assign
id|OBJ_TREE
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|variable|tag_state
r_static
r_struct
id|alloc_state
id|tag_state
suffix:semicolon
DECL|function|alloc_tag_node
r_void
op_star
id|alloc_tag_node
c_func
(paren
r_void
)paren
(brace
r_struct
id|tag
op_star
id|t
op_assign
id|alloc_node
c_func
(paren
op_amp
id|tag_state
comma
r_sizeof
(paren
r_struct
id|tag
)paren
)paren
suffix:semicolon
id|t-&gt;object.type
op_assign
id|OBJ_TAG
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|variable|object_state
r_static
r_struct
id|alloc_state
id|object_state
suffix:semicolon
DECL|function|alloc_object_node
r_void
op_star
id|alloc_object_node
c_func
(paren
r_void
)paren
(brace
r_struct
id|object
op_star
id|obj
op_assign
id|alloc_node
c_func
(paren
op_amp
id|object_state
comma
r_sizeof
(paren
r_union
id|any_object
)paren
)paren
suffix:semicolon
id|obj-&gt;type
op_assign
id|OBJ_NONE
suffix:semicolon
r_return
id|obj
suffix:semicolon
)brace
DECL|variable|commit_state
r_static
r_struct
id|alloc_state
id|commit_state
suffix:semicolon
DECL|function|alloc_commit_index
r_int
r_int
id|alloc_commit_index
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|count
suffix:semicolon
r_return
id|count
op_increment
suffix:semicolon
)brace
DECL|function|alloc_commit_node
r_void
op_star
id|alloc_commit_node
c_func
(paren
r_void
)paren
(brace
r_struct
id|commit
op_star
id|c
op_assign
id|alloc_node
c_func
(paren
op_amp
id|commit_state
comma
r_sizeof
(paren
r_struct
id|commit
)paren
)paren
suffix:semicolon
id|c-&gt;object.type
op_assign
id|OBJ_COMMIT
suffix:semicolon
id|c-&gt;index
op_assign
id|alloc_commit_index
c_func
(paren
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|function|report
r_static
r_void
id|report
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|count
comma
r_int
id|size
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%10s: %8u (%&quot;
id|PRIuMAX
l_string|&quot; kB)&bslash;n&quot;
comma
id|name
comma
id|count
comma
(paren
r_uintmax
)paren
id|size
)paren
suffix:semicolon
)brace
DECL|macro|REPORT
mdefine_line|#define REPORT(name, type)&t;&bslash;&n;    report(#name, name##_state.count, name##_state.count * sizeof(type) &gt;&gt; 10)
DECL|function|alloc_report
r_void
id|alloc_report
c_func
(paren
r_void
)paren
(brace
id|REPORT
c_func
(paren
id|blob
comma
r_struct
id|blob
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|tree
comma
r_struct
id|tree
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|commit
comma
r_struct
id|commit
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|tag
comma
r_struct
id|tag
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|object
comma
r_union
id|any_object
)paren
suffix:semicolon
)brace
eof
