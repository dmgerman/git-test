multiline_comment|/*&n; * apply.c&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; *&n; * This applies patches on top of some (arbitrary) version of the SCM.&n; *&n; * NOTE! It does all its work in the index file, and only cares about&n; * the files in the working directory if you tell it to &quot;merge&quot; the&n; * patch apply.&n; *&n; * Even when merging it always takes the source from the index, and&n; * uses the working tree as a &quot;branch&quot; for a 3-way merge.&n; */
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &quot;cache.h&quot;
singleline_comment|// We default to the merge behaviour, since that&squot;s what most people would
singleline_comment|// expect
DECL|variable|merge_patch
r_static
r_int
id|merge_patch
op_assign
l_int|1
suffix:semicolon
DECL|variable|apply_usage
r_static
r_const
r_char
id|apply_usage
(braket
)braket
op_assign
l_string|&quot;git-apply &lt;patch&gt;&quot;
suffix:semicolon
DECL|macro|CHUNKSIZE
mdefine_line|#define CHUNKSIZE (8192)
DECL|function|read_patch_file
r_static
r_void
op_star
id|read_patch_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
op_star
id|sizep
)paren
(brace
r_int
r_int
id|size
op_assign
l_int|0
comma
id|alloc
op_assign
id|CHUNKSIZE
suffix:semicolon
r_void
op_star
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|alloc
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
id|nr
op_assign
id|alloc
id|size
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|1024
)paren
(brace
id|alloc
op_add_assign
id|CHUNKSIZE
suffix:semicolon
id|buffer
op_assign
id|xrealloc
c_func
(paren
id|buffer
comma
id|alloc
)paren
suffix:semicolon
id|nr
op_assign
id|alloc
id|size
suffix:semicolon
)brace
id|nr
op_assign
id|read
c_func
(paren
id|fd
comma
id|buffer
op_plus
id|size
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_eq
id|EAGAIN
)paren
r_continue
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;git-apply: read returned %s&quot;
comma
id|strerror
c_func
(paren
id|errno
)paren
)paren
suffix:semicolon
)brace
id|size
op_add_assign
id|nr
suffix:semicolon
)brace
op_star
id|sizep
op_assign
id|size
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|linelen
r_static
r_int
r_int
id|linelen
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
(brace
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buffer
op_increment
op_eq
l_char|&squot;&bslash;n&squot;
)paren
r_break
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|match_word
r_static
r_int
id|match_word
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_const
r_char
op_star
id|match
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
id|c
op_assign
op_star
id|match
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|line
op_increment
op_ne
id|c
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_star
id|line
op_eq
l_char|&squot; &squot;
suffix:semicolon
)brace
multiline_comment|/* Verify that we recognize the lines following a git header */
DECL|function|parse_git_header
r_static
r_int
id|parse_git_header
c_func
(paren
r_char
op_star
id|line
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|offset
comma
id|len
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|size
OG
l_int|0
suffix:semicolon
id|offset
op_add_assign
id|len
comma
id|size
op_sub_assign
id|len
comma
id|line
op_add_assign
id|len
)paren
(brace
id|len
op_assign
id|linelen
c_func
(paren
id|line
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|4
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;@@ -&quot;
comma
l_int|4
)paren
)paren
r_return
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|match_word
c_func
(paren
id|line
comma
l_string|&quot;new file mode&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|match_word
c_func
(paren
id|line
comma
l_string|&quot;deleted file mode&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|match_word
c_func
(paren
id|line
comma
l_string|&quot;copy&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|match_word
c_func
(paren
id|line
comma
l_string|&quot;rename&quot;
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|match_word
c_func
(paren
id|line
comma
l_string|&quot;similarity index&quot;
)paren
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* We want either a patch _or_ something real */
r_return
id|offset
ques
c_cond
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|find_header
r_static
r_int
id|find_header
c_func
(paren
r_char
op_star
id|line
comma
r_int
r_int
id|size
comma
r_int
op_star
id|hdrsize
)paren
(brace
r_int
r_int
id|offset
comma
id|len
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|size
OG
l_int|0
suffix:semicolon
id|offset
op_add_assign
id|len
comma
id|size
op_sub_assign
id|len
comma
id|line
op_add_assign
id|len
)paren
(brace
r_int
r_int
id|nextlen
suffix:semicolon
id|len
op_assign
id|linelen
c_func
(paren
id|line
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
multiline_comment|/* Testing this early allows us to take a few shortcuts.. */
r_if
c_cond
(paren
id|len
OL
l_int|6
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|len
op_plus
l_int|6
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Git patch? It might not have a real patch, just a rename&n;&t;&t; * or mode change, so we handle that specially&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;diff --git &quot;
comma
id|line
comma
l_int|11
)paren
)paren
(brace
r_int
id|git_hdr_len
op_assign
id|parse_git_header
c_func
(paren
id|line
op_plus
id|len
comma
id|size
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|git_hdr_len
OL
l_int|0
)paren
r_continue
suffix:semicolon
op_star
id|hdrsize
op_assign
id|len
op_plus
id|git_hdr_len
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
multiline_comment|/** --- followed by +++ ? */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
l_string|&quot;--- &quot;
comma
id|line
comma
l_int|4
)paren
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;+++ &quot;
comma
id|line
op_plus
id|len
comma
l_int|4
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We only accept unified patches, so we want it to&n;&t;&t; * at least have &quot;@@ -a,b +c,d @@&bslash;n&quot;, which is 14 chars&n;&t;&t; * minimum&n;&t;&t; */
id|nextlen
op_assign
id|linelen
c_func
(paren
id|line
op_plus
id|len
comma
id|size
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|nextlen
op_plus
l_int|14
op_logical_or
id|memcmp
c_func
(paren
l_string|&quot;@@ -&quot;
comma
id|line
op_plus
id|len
op_plus
id|nextlen
comma
l_int|4
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Ok, we&squot;ll consider it a patch */
op_star
id|hdrsize
op_assign
id|len
op_plus
id|nextlen
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|parse_num
r_static
r_int
id|parse_num
c_func
(paren
r_const
r_char
op_star
id|line
comma
r_int
id|len
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|expect
comma
r_int
r_int
op_star
id|p
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
r_int
id|digits
comma
id|ex
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
op_logical_or
id|offset
op_ge
id|len
)paren
r_return
l_int|1
suffix:semicolon
id|line
op_add_assign
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isdigit
c_func
(paren
op_star
id|line
)paren
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|p
op_assign
id|strtoul
c_func
(paren
id|line
comma
op_amp
id|ptr
comma
l_int|10
)paren
suffix:semicolon
id|digits
op_assign
id|ptr
id|line
suffix:semicolon
id|offset
op_add_assign
id|digits
suffix:semicolon
id|line
op_add_assign
id|digits
suffix:semicolon
id|len
op_sub_assign
id|digits
suffix:semicolon
id|ex
op_assign
id|strlen
c_func
(paren
id|expect
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ex
OG
id|len
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|line
comma
id|expect
comma
id|ex
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|offset
op_plus
id|ex
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse a unified diff. Note that this really needs&n; * to parse each fragment separately, since the only&n; * way to know the difference between a &quot;---&quot; that is&n; * part of a patch, and a &quot;---&quot; that starts the next&n; * patch is to look at the line counts..&n; */
DECL|function|apply_fragment
r_static
r_int
id|apply_fragment
c_func
(paren
r_char
op_star
id|line
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|len
op_assign
id|linelen
c_func
(paren
id|line
comma
id|size
)paren
comma
id|offset
suffix:semicolon
r_int
r_int
id|oldpos
comma
id|oldlines
comma
id|newpos
comma
id|newlines
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Figure out the number of lines in a fragment */
id|offset
op_assign
id|parse_num
c_func
(paren
id|line
comma
id|len
comma
l_int|4
comma
l_string|&quot;,&quot;
comma
op_amp
id|oldpos
)paren
suffix:semicolon
id|offset
op_assign
id|parse_num
c_func
(paren
id|line
comma
id|len
comma
id|offset
comma
l_string|&quot; +&quot;
comma
op_amp
id|oldlines
)paren
suffix:semicolon
id|offset
op_assign
id|parse_num
c_func
(paren
id|line
comma
id|len
comma
id|offset
comma
l_string|&quot;,&quot;
comma
op_amp
id|newpos
)paren
suffix:semicolon
id|offset
op_assign
id|parse_num
c_func
(paren
id|line
comma
id|len
comma
id|offset
comma
l_string|&quot; @@&quot;
comma
op_amp
id|newlines
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Parse the thing.. */
id|line
op_add_assign
id|len
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
id|len
suffix:semicolon
id|size
OG
l_int|0
suffix:semicolon
id|offset
op_add_assign
id|len
comma
id|size
op_sub_assign
id|len
comma
id|line
op_add_assign
id|len
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|oldlines
op_logical_and
op_logical_neg
id|newlines
)paren
r_break
suffix:semicolon
id|len
op_assign
id|linelen
c_func
(paren
id|line
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_or
id|line
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|line
)paren
(brace
r_default
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
l_char|&squot; &squot;
suffix:colon
id|oldlines
op_decrement
suffix:semicolon
id|newlines
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;-&squot;
suffix:colon
id|oldlines
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;+&squot;
suffix:colon
id|newlines
op_decrement
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|apply_single_patch
r_static
r_int
id|apply_single_patch
c_func
(paren
r_char
op_star
id|line
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|4
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|line
comma
l_string|&quot;@@ -&quot;
comma
l_int|4
)paren
)paren
(brace
r_int
id|len
op_assign
id|apply_fragment
c_func
(paren
id|line
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;applying fragment:&bslash;n%.*s&bslash;n&bslash;n&quot;
comma
id|len
comma
id|line
)paren
suffix:semicolon
id|offset
op_add_assign
id|len
suffix:semicolon
id|line
op_add_assign
id|len
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
)brace
r_return
id|offset
suffix:semicolon
)brace
DECL|function|apply_chunk
r_static
r_int
id|apply_chunk
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|hdrsize
comma
id|patchsize
suffix:semicolon
r_int
id|offset
op_assign
id|find_header
c_func
(paren
id|buffer
comma
id|size
comma
op_amp
id|hdrsize
)paren
suffix:semicolon
r_char
op_star
id|header
comma
op_star
id|patch
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
id|offset
suffix:semicolon
id|header
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Found header:&bslash;n%.*s&bslash;n&bslash;n&quot;
comma
id|hdrsize
comma
id|header
)paren
suffix:semicolon
id|patch
op_assign
id|header
op_plus
id|hdrsize
suffix:semicolon
id|patchsize
op_assign
id|apply_single_patch
c_func
(paren
id|patch
comma
id|size
id|offset
id|hdrsize
)paren
suffix:semicolon
r_return
id|offset
op_plus
id|hdrsize
op_plus
id|patchsize
suffix:semicolon
)brace
DECL|function|apply_patch
r_static
r_int
id|apply_patch
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
r_int
id|offset
comma
id|size
suffix:semicolon
r_char
op_star
id|buffer
op_assign
id|read_patch_file
c_func
(paren
id|fd
comma
op_amp
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
l_int|1
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
id|nr
op_assign
id|apply_chunk
c_func
(paren
id|buffer
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
r_break
suffix:semicolon
id|offset
op_add_assign
id|nr
suffix:semicolon
id|size
op_sub_assign
id|nr
suffix:semicolon
)brace
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
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
id|i
suffix:semicolon
r_if
c_cond
(paren
id|read_cache
c_func
(paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;unable to read index file&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_char
op_star
id|arg
op_assign
id|argv
(braket
id|i
)braket
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;-&quot;
)paren
)paren
(brace
id|apply_patch
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|arg
comma
l_string|&quot;--no-merge&quot;
)paren
)paren
(brace
id|merge_patch
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|fd
op_assign
id|open
c_func
(paren
id|arg
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
id|usage
c_func
(paren
id|apply_usage
)paren
suffix:semicolon
id|apply_patch
c_func
(paren
id|fd
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
