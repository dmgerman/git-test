multiline_comment|/*&n; * Copyright (C) 2005 Junio C Hamano&n; */
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;fetch.h&quot;
DECL|variable|use_link
r_static
r_int
id|use_link
op_assign
l_int|0
suffix:semicolon
DECL|variable|use_symlink
r_static
r_int
id|use_symlink
op_assign
l_int|0
suffix:semicolon
DECL|variable|use_filecopy
r_static
r_int
id|use_filecopy
op_assign
l_int|1
suffix:semicolon
DECL|variable|path
r_static
r_char
op_star
id|path
suffix:semicolon
multiline_comment|/* &quot;Remote&quot; git repository */
DECL|function|prefetch
r_void
id|prefetch
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
)brace
DECL|variable|packs
r_static
r_struct
id|packed_git
op_star
id|packs
op_assign
l_int|NULL
suffix:semicolon
DECL|function|setup_index
r_static
r_void
id|setup_index
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|packed_git
op_star
id|new_pack
suffix:semicolon
r_char
id|filename
(braket
id|PATH_MAX
)braket
suffix:semicolon
id|strcpy
c_func
(paren
id|filename
comma
id|path
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|filename
comma
l_string|&quot;/objects/pack/pack-&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|filename
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|filename
comma
l_string|&quot;.idx&quot;
)paren
suffix:semicolon
id|new_pack
op_assign
id|parse_pack_index_file
c_func
(paren
id|sha1
comma
id|filename
)paren
suffix:semicolon
id|new_pack-&gt;next
op_assign
id|packs
suffix:semicolon
id|packs
op_assign
id|new_pack
suffix:semicolon
)brace
DECL|function|setup_indices
r_static
r_int
id|setup_indices
c_func
(paren
r_void
)paren
(brace
id|DIR
op_star
id|dir
suffix:semicolon
r_struct
id|dirent
op_star
id|de
suffix:semicolon
r_char
id|filename
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_int
r_char
id|sha1
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|filename
comma
l_string|&quot;%s/objects/pack/&quot;
comma
id|path
)paren
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
l_int|1
suffix:semicolon
r_while
c_loop
(paren
(paren
id|de
op_assign
id|readdir
c_func
(paren
id|dir
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|namelen
op_assign
id|strlen
c_func
(paren
id|de-&gt;d_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namelen
op_ne
l_int|50
op_logical_or
id|strcmp
c_func
(paren
id|de-&gt;d_name
op_plus
id|namelen
l_int|5
comma
l_string|&quot;.pack&quot;
)paren
)paren
r_continue
suffix:semicolon
id|get_sha1_hex
c_func
(paren
id|de-&gt;d_name
op_plus
l_int|5
comma
id|sha1
)paren
suffix:semicolon
id|setup_index
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
id|closedir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_file
r_static
r_int
id|copy_file
c_func
(paren
r_const
r_char
op_star
id|source
comma
r_const
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|hex
)paren
(brace
r_if
c_cond
(paren
id|use_link
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|link
c_func
(paren
id|source
comma
id|dest
)paren
)paren
(brace
id|pull_say
c_func
(paren
l_string|&quot;link %s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If we got ENOENT there is no point continuing. */
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;does not exist %s&bslash;n&quot;
comma
id|source
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|use_symlink
op_logical_and
op_logical_neg
id|symlink
c_func
(paren
id|source
comma
id|dest
)paren
)paren
(brace
id|pull_say
c_func
(paren
l_string|&quot;symlink %s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|use_filecopy
)paren
(brace
r_int
id|ifd
comma
id|ofd
comma
id|status
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_void
op_star
id|map
suffix:semicolon
id|ifd
op_assign
id|open
c_func
(paren
id|source
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifd
OL
l_int|0
op_logical_or
id|fstat
c_func
(paren
id|ifd
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|ifd
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot open %s&bslash;n&quot;
comma
id|source
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|st.st_size
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|ifd
comma
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
id|ifd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_eq
id|MAP_FAILED
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot mmap %s&bslash;n&quot;
comma
id|source
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|ofd
op_assign
id|open
c_func
(paren
id|dest
comma
id|O_WRONLY
op_or
id|O_CREAT
op_or
id|O_EXCL
comma
l_int|0666
)paren
suffix:semicolon
id|status
op_assign
(paren
(paren
id|ofd
OL
l_int|0
)paren
op_logical_or
(paren
id|write
c_func
(paren
id|ofd
comma
id|map
comma
id|st.st_size
)paren
op_ne
id|st.st_size
)paren
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|st.st_size
)paren
suffix:semicolon
id|close
c_func
(paren
id|ofd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot write %s&bslash;n&quot;
comma
id|dest
)paren
suffix:semicolon
r_else
id|pull_say
c_func
(paren
l_string|&quot;copy %s&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;failed to copy %s with given copy methods.&bslash;n&quot;
comma
id|hex
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|fetch_pack
r_static
r_int
id|fetch_pack
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_struct
id|packed_git
op_star
id|target
suffix:semicolon
r_char
id|filename
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_if
c_cond
(paren
id|setup_indices
c_func
(paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|target
op_assign
id|find_sha1_pack
c_func
(paren
id|sha1
comma
id|packs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target
)paren
r_return
id|error
c_func
(paren
l_string|&quot;Couldn&squot;t find %s: not separate or in any pack&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_verbosely
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Getting pack %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot; which contains %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|filename
comma
l_string|&quot;%s/objects/pack/pack-%s.pack&quot;
comma
id|path
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|copy_file
c_func
(paren
id|filename
comma
id|sha1_pack_name
c_func
(paren
id|target-&gt;sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|filename
comma
l_string|&quot;%s/objects/pack/pack-%s.idx&quot;
comma
id|path
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|copy_file
c_func
(paren
id|filename
comma
id|sha1_pack_index_name
c_func
(paren
id|target-&gt;sha1
)paren
comma
id|sha1_to_hex
c_func
(paren
id|target-&gt;sha1
)paren
)paren
suffix:semicolon
id|install_packed_git
c_func
(paren
id|target
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fetch_file
r_static
r_int
id|fetch_file
c_func
(paren
r_const
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_int
id|object_name_start
op_assign
l_int|1
suffix:semicolon
r_static
r_char
id|filename
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_char
op_star
id|hex
op_assign
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_const
r_char
op_star
id|dest_filename
op_assign
id|sha1_file_name
c_func
(paren
id|sha1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|object_name_start
OL
l_int|0
)paren
(brace
id|strcpy
c_func
(paren
id|filename
comma
id|path
)paren
suffix:semicolon
multiline_comment|/* e.g. git.git */
id|strcat
c_func
(paren
id|filename
comma
l_string|&quot;/objects/&quot;
)paren
suffix:semicolon
id|object_name_start
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
)brace
id|filename
(braket
id|object_name_start
op_plus
l_int|0
)braket
op_assign
id|hex
(braket
l_int|0
)braket
suffix:semicolon
id|filename
(braket
id|object_name_start
op_plus
l_int|1
)braket
op_assign
id|hex
(braket
l_int|1
)braket
suffix:semicolon
id|filename
(braket
id|object_name_start
op_plus
l_int|2
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|strcpy
c_func
(paren
id|filename
op_plus
id|object_name_start
op_plus
l_int|3
comma
id|hex
op_plus
l_int|2
)paren
suffix:semicolon
r_return
id|copy_file
c_func
(paren
id|filename
comma
id|dest_filename
comma
id|hex
)paren
suffix:semicolon
)brace
DECL|function|fetch
r_int
id|fetch
c_func
(paren
r_int
r_char
op_star
id|sha1
)paren
(brace
r_return
id|fetch_file
c_func
(paren
id|sha1
)paren
op_logical_and
id|fetch_pack
c_func
(paren
id|sha1
)paren
suffix:semicolon
)brace
DECL|function|fetch_ref
r_int
id|fetch_ref
c_func
(paren
r_char
op_star
id|ref
comma
r_int
r_char
op_star
id|sha1
)paren
(brace
r_static
r_int
id|ref_name_start
op_assign
l_int|1
suffix:semicolon
r_static
r_char
id|filename
(braket
id|PATH_MAX
)braket
suffix:semicolon
r_static
r_char
id|hex
(braket
l_int|41
)braket
suffix:semicolon
r_int
id|ifd
suffix:semicolon
r_if
c_cond
(paren
id|ref_name_start
OL
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|filename
comma
l_string|&quot;%s/refs/&quot;
comma
id|path
)paren
suffix:semicolon
id|ref_name_start
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|filename
op_plus
id|ref_name_start
comma
id|ref
)paren
suffix:semicolon
id|ifd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ifd
OL
l_int|0
)paren
(brace
id|close
c_func
(paren
id|ifd
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot open %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|ifd
comma
id|hex
comma
l_int|40
)paren
op_ne
l_int|40
op_logical_or
id|get_sha1_hex
c_func
(paren
id|hex
comma
id|sha1
)paren
)paren
(brace
id|close
c_func
(paren
id|ifd
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;cannot read from %s&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|close
c_func
(paren
id|ifd
)paren
suffix:semicolon
id|pull_say
c_func
(paren
l_string|&quot;ref %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|sha1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|local_pull_usage
r_static
r_const
r_char
id|local_pull_usage
(braket
)braket
op_assign
l_string|&quot;git-local-fetch [-c] [-t] [-a] [-d] [-v] [-w filename] [--recover] [-l] [-s] [-n] commit-id path&quot;
suffix:semicolon
multiline_comment|/* &n; * By default we only use file copy.&n; * If -l is specified, a hard link is attempted.&n; * If -s is specified, then a symlink is attempted.&n; * If -n is _not_ specified, then a regular file-to-file copy is done.&n; */
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
id|commit_id
suffix:semicolon
r_int
id|arg
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|arg
OL
id|argc
op_logical_and
id|argv
(braket
id|arg
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
)paren
(brace
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;t&squot;
)paren
id|get_tree
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;c&squot;
)paren
id|get_history
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;a&squot;
)paren
(brace
id|get_all
op_assign
l_int|1
suffix:semicolon
id|get_tree
op_assign
l_int|1
suffix:semicolon
id|get_history
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;l&squot;
)paren
id|use_link
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;s&squot;
)paren
id|use_symlink
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;n&squot;
)paren
id|use_filecopy
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;v&squot;
)paren
id|get_verbosely
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|argv
(braket
id|arg
)braket
(braket
l_int|1
)braket
op_eq
l_char|&squot;w&squot;
)paren
id|write_ref
op_assign
id|argv
(braket
op_increment
id|arg
)braket
suffix:semicolon
r_else
id|usage
c_func
(paren
id|local_pull_usage
)paren
suffix:semicolon
id|arg
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
id|arg
op_plus
l_int|2
)paren
id|usage
c_func
(paren
id|local_pull_usage
)paren
suffix:semicolon
id|commit_id
op_assign
id|argv
(braket
id|arg
)braket
suffix:semicolon
id|path
op_assign
id|argv
(braket
id|arg
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pull
c_func
(paren
id|commit_id
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
