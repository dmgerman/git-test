multiline_comment|/*&n; * GIT - The information manager from hell&n; *&n; * Copyright (C) Linus Torvalds, 2005&n; */
macro_line|#include &quot;cache.h&quot;
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
r_char
op_star
id|sha1_dir
op_assign
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
comma
op_star
id|path
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
l_string|&quot;.git&quot;
comma
l_int|0755
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;unable to create .git directory&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If you want to, you can share the DB area with any number of branches.&n;&t; * That has advantages: you can save space by sharing all the SHA1 objects.&n;&t; * On the other hand, it might just make lookup slower and messier. You&n;&t; * be the judge.&n;&t; */
id|sha1_dir
op_assign
id|getenv
c_func
(paren
id|DB_ENVIRONMENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sha1_dir
)paren
(brace
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stat
c_func
(paren
id|sha1_dir
comma
op_amp
id|st
)paren
op_logical_and
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;DB_ENVIRONMENT set to bad directory %s: &quot;
comma
id|sha1_dir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The default case is to have a DB per managed directory.&n;&t; */
id|sha1_dir
op_assign
id|DEFAULT_DB_ENVIRONMENT
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;defaulting to private storage area&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|sha1_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|sha1_dir
comma
l_int|0755
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
(brace
id|perror
c_func
(paren
id|sha1_dir
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|path
op_assign
id|malloc
c_func
(paren
id|len
op_plus
l_int|40
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path
comma
id|sha1_dir
comma
id|len
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|path
op_plus
id|len
comma
l_string|&quot;/%02x&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mkdir
c_func
(paren
id|path
comma
l_int|0755
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|EEXIST
)paren
(brace
id|perror
c_func
(paren
id|path
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
