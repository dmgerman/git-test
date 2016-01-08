multiline_comment|/*&n; * alloc.c  - specialized allocator for internal objects&n; *&n; * Copyright (C) 2006 Linus Torvalds&n; *&n; * The standard malloc/free wastes too much space for objects, partly because&n; * it maintains all the allocation infrastructure (which isn&squot;t needed, since&n; * we never free an object descriptor anyway), but even more because it ends&n; * up with maximal alignment because it doesn&squot;t know what the object alignment&n; * for the new allocation is.&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;object.h&quot;
macro_line|#include &quot;blob.h&quot;
macro_line|#include &quot;tree.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;tag.h&quot;
DECL|macro|BLOCKING
mdefine_line|#define BLOCKING 1024
DECL|macro|DEFINE_ALLOCATOR
mdefine_line|#define DEFINE_ALLOCATOR(name)&t;&t;&t;&t;&t;&bslash;&n;static unsigned int name##_allocs;&t;&t;&t;&t;&bslash;&n;struct name *alloc_##name##_node(void)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static int nr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static struct name *block;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!nr) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;nr = BLOCKING;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;block = xcalloc(BLOCKING, sizeof(struct name));&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nr--;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;name##_allocs++;&t;&t;&t;&t;&t;&bslash;&n;&t;return block++;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|DEFINE_ALLOCATOR
c_func
(paren
id|blob
)paren
id|DEFINE_ALLOCATOR
c_func
(paren
id|tree
)paren
id|DEFINE_ALLOCATOR
c_func
(paren
id|commit
)paren
id|DEFINE_ALLOCATOR
c_func
(paren
id|tag
)paren
macro_line|#ifdef NO_C99_FORMAT
DECL|macro|SZ_FMT
mdefine_line|#define SZ_FMT &quot;%u&quot;
macro_line|#else
mdefine_line|#define SZ_FMT &quot;%zu&quot;
macro_line|#endif
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
l_string|&quot;%10s: %8u (&quot;
id|SZ_FMT
l_string|&quot; kB)&bslash;n&quot;
comma
id|name
comma
id|count
comma
id|size
)paren
suffix:semicolon
)brace
DECL|macro|SZ_FMT
macro_line|#undef SZ_FMT
DECL|macro|REPORT
mdefine_line|#define REPORT(name)&t;&bslash;&n;    report(#name, name##_allocs, name##_allocs*sizeof(struct name) &gt;&gt; 10)
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
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|tree
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|commit
)paren
suffix:semicolon
id|REPORT
c_func
(paren
id|tag
)paren
suffix:semicolon
)brace
eof
