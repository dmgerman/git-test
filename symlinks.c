macro_line|#include &quot;cache.h&quot;
multiline_comment|/*&n; * Returns the length (on a path component basis) of the longest&n; * common prefix match of &squot;name_a&squot; and &squot;name_b&squot;.&n; */
DECL|function|longest_path_match
r_static
r_int
id|longest_path_match
c_func
(paren
r_const
r_char
op_star
id|name_a
comma
r_int
id|len_a
comma
r_const
r_char
op_star
id|name_b
comma
r_int
id|len_b
comma
r_int
op_star
id|previous_slash
)paren
(brace
r_int
id|max_len
comma
id|match_len
op_assign
l_int|0
comma
id|match_len_prev
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|max_len
op_assign
id|len_a
OL
id|len_b
ques
c_cond
id|len_a
suffix:colon
id|len_b
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|max_len
op_logical_and
id|name_a
(braket
id|i
)braket
op_eq
id|name_b
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|name_a
(braket
id|i
)braket
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|match_len_prev
op_assign
id|match_len
suffix:semicolon
id|match_len
op_assign
id|i
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Is &squot;name_b&squot; a substring of &squot;name_a&squot;, the other way around,&n;&t; * or is &squot;name_a&squot; and &squot;name_b&squot; the exact same string?&n;&t; */
r_if
c_cond
(paren
id|i
op_ge
id|max_len
op_logical_and
(paren
(paren
id|len_a
OG
id|len_b
op_logical_and
id|name_a
(braket
id|len_b
)braket
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|len_a
OL
id|len_b
op_logical_and
id|name_b
(braket
id|len_a
)braket
op_eq
l_char|&squot;/&squot;
)paren
op_logical_or
(paren
id|len_a
op_eq
id|len_b
)paren
)paren
)paren
(brace
id|match_len_prev
op_assign
id|match_len
suffix:semicolon
id|match_len
op_assign
id|i
suffix:semicolon
)brace
op_star
id|previous_slash
op_assign
id|match_len_prev
suffix:semicolon
r_return
id|match_len
suffix:semicolon
)brace
DECL|struct|cache_def
r_static
r_struct
id|cache_def
(brace
DECL|member|path
r_char
id|path
(braket
id|PATH_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|track_flags
r_int
id|track_flags
suffix:semicolon
DECL|member|prefix_len_stat_func
r_int
id|prefix_len_stat_func
suffix:semicolon
DECL|variable|cache
)brace
id|cache
suffix:semicolon
DECL|function|reset_lstat_cache
r_static
r_inline
r_void
id|reset_lstat_cache
c_func
(paren
r_void
)paren
(brace
id|cache.path
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|cache.len
op_assign
l_int|0
suffix:semicolon
id|cache.flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * The track_flags and prefix_len_stat_func members is only&n;&t; * set by the safeguard rule inside lstat_cache()&n;&t; */
)brace
DECL|macro|SWITCHES_BEFORE_WARNING
mdefine_line|#define SWITCHES_BEFORE_WARNING 10
DECL|variable|cache_switches
DECL|variable|number_of_warnings
r_static
r_int
r_int
id|cache_switches
comma
id|number_of_warnings
suffix:semicolon
DECL|variable|current_cache_func
DECL|variable|last_cache_func
r_static
r_int
r_int
id|current_cache_func
comma
id|last_cache_func
suffix:semicolon
DECL|variable|total_calls
r_static
r_int
r_int
id|total_calls
suffix:semicolon
DECL|macro|FL_DIR
mdefine_line|#define FL_DIR      (1 &lt;&lt; 0)
DECL|macro|FL_NOENT
mdefine_line|#define FL_NOENT    (1 &lt;&lt; 1)
DECL|macro|FL_SYMLINK
mdefine_line|#define FL_SYMLINK  (1 &lt;&lt; 2)
DECL|macro|FL_LSTATERR
mdefine_line|#define FL_LSTATERR (1 &lt;&lt; 3)
DECL|macro|FL_ERR
mdefine_line|#define FL_ERR      (1 &lt;&lt; 4)
DECL|macro|FL_FULLPATH
mdefine_line|#define FL_FULLPATH (1 &lt;&lt; 5)
multiline_comment|/*&n; * Check if name &squot;name&squot; of length &squot;len&squot; has a symlink leading&n; * component, or if the directory exists and is real, or not.&n; *&n; * To speed up the check, some information is allowed to be cached.&n; * This can be indicated by the &squot;track_flags&squot; argument, which also can&n; * be used to indicate that we should check the full path.&n; *&n; * The &squot;prefix_len_stat_func&squot; parameter can be used to set the length&n; * of the prefix, where the cache should use the stat() function&n; * instead of the lstat() function to test each path component.&n; */
DECL|function|lstat_cache
r_static
r_int
id|lstat_cache
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|track_flags
comma
r_int
id|prefix_len_stat_func
)paren
(brace
r_int
id|match_len
comma
id|last_slash
comma
id|last_slash_dir
comma
id|previous_slash
suffix:semicolon
r_int
id|match_flags
comma
id|ret_flags
comma
id|save_flags
comma
id|max_len
comma
id|ret
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
id|total_calls
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cache.track_flags
op_ne
id|track_flags
op_logical_or
id|cache.prefix_len_stat_func
op_ne
id|prefix_len_stat_func
)paren
(brace
multiline_comment|/*&n;&t;&t; * As a safeguard rule we clear the cache if the&n;&t;&t; * values of track_flags and/or prefix_len_stat_func&n;&t;&t; * does not match with the last supplied values.&n;&t;&t; */
id|reset_lstat_cache
c_func
(paren
)paren
suffix:semicolon
id|cache.track_flags
op_assign
id|track_flags
suffix:semicolon
id|cache.prefix_len_stat_func
op_assign
id|prefix_len_stat_func
suffix:semicolon
id|match_len
op_assign
id|last_slash
op_assign
l_int|0
suffix:semicolon
id|cache_switches
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cache_switches
OG
id|SWITCHES_BEFORE_WARNING
)paren
(brace
r_if
c_cond
(paren
id|number_of_warnings
OL
l_int|10
op_logical_or
id|number_of_warnings
op_mod
l_int|1000
op_eq
l_int|0
)paren
id|printf
c_func
(paren
l_string|&quot;warning from %s:%d cache_switches:%u &gt; %u &quot;
"&bslash;"
l_string|&quot;(current:%u last:%u total:%u)&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|cache_switches
comma
id|SWITCHES_BEFORE_WARNING
comma
id|current_cache_func
comma
id|last_cache_func
comma
id|total_calls
)paren
suffix:semicolon
id|number_of_warnings
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Check to see if we have a match from the cache for&n;&t;&t; * the 2 &quot;excluding&quot; path types.&n;&t;&t; */
id|match_len
op_assign
id|last_slash
op_assign
id|longest_path_match
c_func
(paren
id|name
comma
id|len
comma
id|cache.path
comma
id|cache.len
comma
op_amp
id|previous_slash
)paren
suffix:semicolon
id|match_flags
op_assign
id|cache.flags
op_amp
id|track_flags
op_amp
(paren
id|FL_NOENT
op_or
id|FL_SYMLINK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_flags
op_logical_and
id|match_len
op_eq
id|cache.len
)paren
r_return
id|match_flags
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we now have match_len &gt; 0, we would know that&n;&t;&t; * the matched part will always be a directory.&n;&t;&t; *&n;&t;&t; * Also, if we are tracking directories and &squot;name&squot; is&n;&t;&t; * a substring of the cache on a path component basis,&n;&t;&t; * we can return immediately.&n;&t;&t; */
id|match_flags
op_assign
id|track_flags
op_amp
id|FL_DIR
suffix:semicolon
r_if
c_cond
(paren
id|match_flags
op_logical_and
id|len
op_eq
id|match_len
)paren
r_return
id|match_flags
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Okay, no match from the cache so far, so now we have to&n;&t; * check the rest of the path components.&n;&t; */
id|ret_flags
op_assign
id|FL_DIR
suffix:semicolon
id|last_slash_dir
op_assign
id|last_slash
suffix:semicolon
id|max_len
op_assign
id|len
OL
id|PATH_MAX
ques
c_cond
id|len
suffix:colon
id|PATH_MAX
suffix:semicolon
r_while
c_loop
(paren
id|match_len
OL
id|max_len
)paren
(brace
r_do
(brace
id|cache.path
(braket
id|match_len
)braket
op_assign
id|name
(braket
id|match_len
)braket
suffix:semicolon
id|match_len
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|match_len
OL
id|max_len
op_logical_and
id|name
(braket
id|match_len
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|match_len
op_ge
id|max_len
op_logical_and
op_logical_neg
(paren
id|track_flags
op_amp
id|FL_FULLPATH
)paren
)paren
r_break
suffix:semicolon
id|last_slash
op_assign
id|match_len
suffix:semicolon
id|cache.path
(braket
id|last_slash
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|last_slash
op_le
id|prefix_len_stat_func
)paren
id|ret
op_assign
id|stat
c_func
(paren
id|cache.path
comma
op_amp
id|st
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|lstat
c_func
(paren
id|cache.path
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ret_flags
op_assign
id|FL_LSTATERR
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_eq
id|ENOENT
)paren
id|ret_flags
op_or_assign
id|FL_NOENT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|last_slash_dir
op_assign
id|last_slash
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|st.st_mode
)paren
)paren
(brace
id|ret_flags
op_assign
id|FL_SYMLINK
suffix:semicolon
)brace
r_else
(brace
id|ret_flags
op_assign
id|FL_ERR
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * At the end update the cache.  Note that max 3 different&n;&t; * path types, FL_NOENT, FL_SYMLINK and FL_DIR, can be cached&n;&t; * for the moment!&n;&t; */
id|save_flags
op_assign
id|ret_flags
op_amp
id|track_flags
op_amp
(paren
id|FL_NOENT
op_or
id|FL_SYMLINK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_flags
op_logical_and
id|last_slash
OG
l_int|0
op_logical_and
id|last_slash
op_le
id|PATH_MAX
)paren
(brace
id|cache.path
(braket
id|last_slash
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|cache.len
op_assign
id|last_slash
suffix:semicolon
id|cache.flags
op_assign
id|save_flags
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|track_flags
op_amp
id|FL_DIR
)paren
op_logical_and
id|last_slash_dir
OG
l_int|0
op_logical_and
id|last_slash_dir
op_le
id|PATH_MAX
)paren
(brace
multiline_comment|/*&n;&t;&t; * We have a separate test for the directory case,&n;&t;&t; * since it could be that we have found a symlink or a&n;&t;&t; * non-existing directory and the track_flags says&n;&t;&t; * that we cannot cache this fact, so the cache would&n;&t;&t; * then have been left empty in this case.&n;&t;&t; *&n;&t;&t; * But if we are allowed to track real directories, we&n;&t;&t; * can still cache the path components before the last&n;&t;&t; * one (the found symlink or non-existing component).&n;&t;&t; */
id|cache.path
(braket
id|last_slash_dir
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|cache.len
op_assign
id|last_slash_dir
suffix:semicolon
id|cache.flags
op_assign
id|FL_DIR
suffix:semicolon
)brace
r_else
(brace
id|reset_lstat_cache
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|ret_flags
suffix:semicolon
)brace
multiline_comment|/*&n; * Invalidate the given &squot;name&squot; from the cache, if &squot;name&squot; matches&n; * completely with the cache.&n; */
DECL|function|invalidate_lstat_cache
r_void
id|invalidate_lstat_cache
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|match_len
comma
id|previous_slash
suffix:semicolon
id|match_len
op_assign
id|longest_path_match
c_func
(paren
id|name
comma
id|len
comma
id|cache.path
comma
id|cache.len
comma
op_amp
id|previous_slash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|match_len
)paren
(brace
r_if
c_cond
(paren
(paren
id|cache.track_flags
op_amp
id|FL_DIR
)paren
op_logical_and
id|previous_slash
OG
l_int|0
)paren
(brace
id|cache.path
(braket
id|previous_slash
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|cache.len
op_assign
id|previous_slash
suffix:semicolon
id|cache.flags
op_assign
id|FL_DIR
suffix:semicolon
)brace
r_else
id|reset_lstat_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Completely clear the contents of the cache&n; */
DECL|function|clear_lstat_cache
r_void
id|clear_lstat_cache
c_func
(paren
r_void
)paren
(brace
id|reset_lstat_cache
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|USE_ONLY_LSTAT
mdefine_line|#define USE_ONLY_LSTAT  0
multiline_comment|/*&n; * Return non-zero if path &squot;name&squot; has a leading symlink component&n; */
DECL|function|has_symlink_leading_path
r_int
id|has_symlink_leading_path
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
id|last_cache_func
op_assign
id|current_cache_func
suffix:semicolon
id|current_cache_func
op_assign
l_int|1
suffix:semicolon
r_return
id|lstat_cache
c_func
(paren
id|name
comma
id|len
comma
id|FL_SYMLINK
op_or
id|FL_DIR
comma
id|USE_ONLY_LSTAT
)paren
op_amp
id|FL_SYMLINK
suffix:semicolon
)brace
multiline_comment|/*&n; * Return non-zero if path &squot;name&squot; has a leading symlink component or&n; * if some leading path component does not exists.&n; */
DECL|function|has_symlink_or_noent_leading_path
r_int
id|has_symlink_or_noent_leading_path
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
id|last_cache_func
op_assign
id|current_cache_func
suffix:semicolon
id|current_cache_func
op_assign
l_int|2
suffix:semicolon
r_return
id|lstat_cache
c_func
(paren
id|name
comma
id|len
comma
id|FL_SYMLINK
op_or
id|FL_NOENT
op_or
id|FL_DIR
comma
id|USE_ONLY_LSTAT
)paren
op_amp
(paren
id|FL_SYMLINK
op_or
id|FL_NOENT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return non-zero if all path components of &squot;name&squot; exists as a&n; * directory.  If prefix_len &gt; 0, we will test with the stat()&n; * function instead of the lstat() function for a prefix length of&n; * &squot;prefix_len&squot;, thus we then allow for symlinks in the prefix part as&n; * long as those points to real existing directories.&n; */
DECL|function|has_dirs_only_path
r_int
id|has_dirs_only_path
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_int
id|prefix_len
)paren
(brace
id|last_cache_func
op_assign
id|current_cache_func
suffix:semicolon
id|current_cache_func
op_assign
l_int|3
suffix:semicolon
r_return
id|lstat_cache
c_func
(paren
id|name
comma
id|len
comma
id|FL_DIR
op_or
id|FL_FULLPATH
comma
id|prefix_len
)paren
op_amp
id|FL_DIR
suffix:semicolon
)brace
DECL|struct|removal_def
r_static
r_struct
id|removal_def
(brace
DECL|member|path
r_char
id|path
(braket
id|PATH_MAX
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|variable|removal
)brace
id|removal
suffix:semicolon
DECL|function|do_remove_scheduled_dirs
r_static
r_void
id|do_remove_scheduled_dirs
c_func
(paren
r_int
id|new_len
)paren
(brace
r_while
c_loop
(paren
id|removal.len
OG
id|new_len
)paren
(brace
id|removal.path
(braket
id|removal.len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|rmdir
c_func
(paren
id|removal.path
)paren
)paren
r_break
suffix:semicolon
r_do
(brace
id|removal.len
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|removal.len
OG
id|new_len
op_logical_and
id|removal.path
(braket
id|removal.len
)braket
op_ne
l_char|&squot;/&squot;
)paren
suffix:semicolon
)brace
id|removal.len
op_assign
id|new_len
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|schedule_dir_for_removal
r_void
id|schedule_dir_for_removal
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|match_len
comma
id|last_slash
comma
id|i
comma
id|previous_slash
suffix:semicolon
id|match_len
op_assign
id|last_slash
op_assign
id|i
op_assign
id|longest_path_match
c_func
(paren
id|name
comma
id|len
comma
id|removal.path
comma
id|removal.len
comma
op_amp
id|previous_slash
)paren
suffix:semicolon
multiline_comment|/* Find last slash inside &squot;name&squot; */
r_while
c_loop
(paren
id|i
OL
id|len
)paren
(brace
r_if
c_cond
(paren
id|name
(braket
id|i
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|last_slash
op_assign
id|i
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we are about to go down the directory tree, we check if&n;&t; * we must first go upwards the tree, such that we then can&n;&t; * remove possible empty directories as we go upwards.&n;&t; */
r_if
c_cond
(paren
id|match_len
OL
id|last_slash
op_logical_and
id|match_len
OL
id|removal.len
)paren
id|do_remove_scheduled_dirs
c_func
(paren
id|match_len
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we go deeper down the directory tree, we only need to&n;&t; * save the new path components as we go down.&n;&t; */
r_if
c_cond
(paren
id|match_len
OL
id|last_slash
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|removal.path
(braket
id|match_len
)braket
comma
op_amp
id|name
(braket
id|match_len
)braket
comma
id|last_slash
id|match_len
)paren
suffix:semicolon
id|removal.len
op_assign
id|last_slash
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|remove_scheduled_dirs
r_void
id|remove_scheduled_dirs
c_func
(paren
r_void
)paren
(brace
id|do_remove_scheduled_dirs
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
