multiline_comment|/*&n; *  LibXDiff by Davide Libenzi ( File Differential Library )&n; *  Copyright (C) 2003-2009 Davide Libenzi, Johannes E. Schindelin&n; *&n; *  This library is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU Lesser General Public&n; *  License as published by the Free Software Foundation; either&n; *  version 2.1 of the License, or (at your option) any later version.&n; *&n; *  This library is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  Lesser General Public License for more details.&n; *&n; *  You should have received a copy of the GNU Lesser General Public&n; *  License along with this library; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  Davide Libenzi &lt;davidel@xmailserver.org&gt;&n; *&n; */
macro_line|#include &quot;xinclude.h&quot;
macro_line|#include &quot;xtypes.h&quot;
macro_line|#include &quot;xdiff.h&quot;
multiline_comment|/*&n; * The basic idea of patience diff is to find lines that are unique in&n; * both files.  These are intuitively the ones that we want to see as&n; * common lines.&n; *&n; * The maximal ordered sequence of such line pairs (where ordered means&n; * that the order in the sequence agrees with the order of the lines in&n; * both files) naturally defines an initial set of common lines.&n; *&n; * Now, the algorithm tries to extend the set of common lines by growing&n; * the line ranges where the files have identical lines.&n; *&n; * Between those common lines, the patience diff algorithm is applied&n; * recursively, until no unique line pairs can be found; these line ranges&n; * are handled by the well-known Myers algorithm.&n; */
DECL|macro|NON_UNIQUE
mdefine_line|#define NON_UNIQUE ULONG_MAX
multiline_comment|/*&n; * This is a hash mapping from line hash to line numbers in the first and&n; * second file.&n; */
DECL|struct|hashmap
r_struct
id|hashmap
(brace
DECL|member|nr
DECL|member|alloc
r_int
id|nr
comma
id|alloc
suffix:semicolon
DECL|struct|entry
r_struct
id|entry
(brace
DECL|member|hash
r_int
r_int
id|hash
suffix:semicolon
multiline_comment|/*&n;&t;&t; * 0 = unused entry, 1 = first line, 2 = second, etc.&n;&t;&t; * line2 is NON_UNIQUE if the line is not unique&n;&t;&t; * in either the first or the second file.&n;&t;&t; */
DECL|member|line1
DECL|member|line2
r_int
r_int
id|line1
comma
id|line2
suffix:semicolon
multiline_comment|/*&n;&t;&t; * &quot;next&quot; &amp; &quot;previous&quot; are used for the longest common&n;&t;&t; * sequence;&n;&t;&t; * initially, &quot;next&quot; reflects only the order in file1.&n;&t;&t; */
DECL|member|next
DECL|member|previous
r_struct
id|entry
op_star
id|next
comma
op_star
id|previous
suffix:semicolon
DECL|member|entries
DECL|member|first
DECL|member|last
)brace
op_star
id|entries
comma
op_star
id|first
comma
op_star
id|last
suffix:semicolon
multiline_comment|/* were common records found? */
DECL|member|has_matches
r_int
r_int
id|has_matches
suffix:semicolon
DECL|member|file1
DECL|member|file2
id|mmfile_t
op_star
id|file1
comma
op_star
id|file2
suffix:semicolon
DECL|member|env
id|xdfenv_t
op_star
id|env
suffix:semicolon
DECL|member|xpp
id|xpparam_t
r_const
op_star
id|xpp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The argument &quot;pass&quot; is 1 for the first file, 2 for the second. */
DECL|function|insert_record
r_static
r_void
id|insert_record
c_func
(paren
r_int
id|line
comma
r_struct
id|hashmap
op_star
id|map
comma
r_int
id|pass
)paren
(brace
id|xrecord_t
op_star
op_star
id|records
op_assign
id|pass
op_eq
l_int|1
ques
c_cond
id|map-&gt;env-&gt;xdf1.recs
suffix:colon
id|map-&gt;env-&gt;xdf2.recs
suffix:semicolon
id|xrecord_t
op_star
id|record
op_assign
id|records
(braket
id|line
l_int|1
)braket
comma
op_star
id|other
suffix:semicolon
multiline_comment|/*&n;&t; * After xdl_prepare_env() (or more precisely, due to&n;&t; * xdl_classify_record()), the &quot;ha&quot; member of the records (AKA lines)&n;&t; * is _not_ the hash anymore, but a linearized version of it.  In&n;&t; * other words, the &quot;ha&quot; member is guaranteed to start with 0 and&n;&t; * the second record&squot;s ha can only be 0 or 1, etc.&n;&t; *&n;&t; * So we multiply ha by 2 in the hope that the hashing was&n;&t; * &quot;unique enough&quot;.&n;&t; */
r_int
id|index
op_assign
(paren
r_int
)paren
(paren
(paren
id|record-&gt;ha
op_lshift
l_int|1
)paren
op_mod
id|map-&gt;alloc
)paren
suffix:semicolon
r_while
c_loop
(paren
id|map-&gt;entries
(braket
id|index
)braket
dot
id|line1
)paren
(brace
id|other
op_assign
id|map-&gt;env-&gt;xdf1.recs
(braket
id|map-&gt;entries
(braket
id|index
)braket
dot
id|line1
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;entries
(braket
id|index
)braket
dot
id|hash
op_ne
id|record-&gt;ha
op_logical_or
op_logical_neg
id|xdl_recmatch
c_func
(paren
id|record-&gt;ptr
comma
id|record-&gt;size
comma
id|other-&gt;ptr
comma
id|other-&gt;size
comma
id|map-&gt;xpp-&gt;flags
)paren
)paren
(brace
r_if
c_cond
(paren
op_increment
id|index
op_ge
id|map-&gt;alloc
)paren
id|index
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pass
op_eq
l_int|2
)paren
id|map-&gt;has_matches
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pass
op_eq
l_int|1
op_logical_or
id|map-&gt;entries
(braket
id|index
)braket
dot
id|line2
)paren
id|map-&gt;entries
(braket
id|index
)braket
dot
id|line2
op_assign
id|NON_UNIQUE
suffix:semicolon
r_else
id|map-&gt;entries
(braket
id|index
)braket
dot
id|line2
op_assign
id|line
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pass
op_eq
l_int|2
)paren
r_return
suffix:semicolon
id|map-&gt;entries
(braket
id|index
)braket
dot
id|line1
op_assign
id|line
suffix:semicolon
id|map-&gt;entries
(braket
id|index
)braket
dot
id|hash
op_assign
id|record-&gt;ha
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map-&gt;first
)paren
id|map-&gt;first
op_assign
id|map-&gt;entries
op_plus
id|index
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;last
)paren
(brace
id|map-&gt;last-&gt;next
op_assign
id|map-&gt;entries
op_plus
id|index
suffix:semicolon
id|map-&gt;entries
(braket
id|index
)braket
dot
id|previous
op_assign
id|map-&gt;last
suffix:semicolon
)brace
id|map-&gt;last
op_assign
id|map-&gt;entries
op_plus
id|index
suffix:semicolon
id|map-&gt;nr
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * This function has to be called for each recursion into the inter-hunk&n; * parts, as previously non-unique lines can become unique when being&n; * restricted to a smaller part of the files.&n; *&n; * It is assumed that env has been prepared using xdl_prepare().&n; */
DECL|function|fill_hashmap
r_static
r_int
id|fill_hashmap
c_func
(paren
id|mmfile_t
op_star
id|file1
comma
id|mmfile_t
op_star
id|file2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|env
comma
r_struct
id|hashmap
op_star
id|result
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
id|result-&gt;file1
op_assign
id|file1
suffix:semicolon
id|result-&gt;file2
op_assign
id|file2
suffix:semicolon
id|result-&gt;xpp
op_assign
id|xpp
suffix:semicolon
id|result-&gt;env
op_assign
id|env
suffix:semicolon
multiline_comment|/* We know exactly how large we want the hash map */
id|result-&gt;alloc
op_assign
id|count1
op_star
l_int|2
suffix:semicolon
id|result-&gt;entries
op_assign
(paren
r_struct
id|entry
op_star
)paren
id|xdl_malloc
c_func
(paren
id|result-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result-&gt;entries
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|result-&gt;entries
comma
l_int|0
comma
id|result-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|entry
)paren
)paren
suffix:semicolon
multiline_comment|/* First, fill with entries from the first file */
r_while
c_loop
(paren
id|count1
op_decrement
)paren
id|insert_record
c_func
(paren
id|line1
op_increment
comma
id|result
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Then search for matches in the second file */
r_while
c_loop
(paren
id|count2
op_decrement
)paren
id|insert_record
c_func
(paren
id|line2
op_increment
comma
id|result
comma
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the longest sequence with a smaller last element (meaning a smaller&n; * line2, as we construct the sequence with entries ordered by line1).&n; */
DECL|function|binary_search
r_static
r_int
id|binary_search
c_func
(paren
r_struct
id|entry
op_star
op_star
id|sequence
comma
r_int
id|longest
comma
r_struct
id|entry
op_star
id|entry
)paren
(brace
r_int
id|left
op_assign
l_int|1
comma
id|right
op_assign
id|longest
suffix:semicolon
r_while
c_loop
(paren
id|left
op_plus
l_int|1
OL
id|right
)paren
(brace
r_int
id|middle
op_assign
(paren
id|left
op_plus
id|right
)paren
op_div
l_int|2
suffix:semicolon
multiline_comment|/* by construction, no two entries can be equal */
r_if
c_cond
(paren
id|sequence
(braket
id|middle
)braket
op_member_access_from_pointer
id|line2
OG
id|entry-&gt;line2
)paren
id|right
op_assign
id|middle
suffix:semicolon
r_else
id|left
op_assign
id|middle
suffix:semicolon
)brace
multiline_comment|/* return the index in &quot;sequence&quot;, _not_ the sequence length */
r_return
id|left
suffix:semicolon
)brace
multiline_comment|/*&n; * The idea is to start with the list of common unique lines sorted by&n; * the order in file1.  For each of these pairs, the longest (partial)&n; * sequence whose last element&squot;s line2 is smaller is determined.&n; *&n; * For efficiency, the sequences are kept in a list containing exactly one&n; * item per sequence length: the sequence with the smallest last&n; * element (in terms of line2).&n; */
DECL|function|find_longest_common_sequence
r_static
r_struct
id|entry
op_star
id|find_longest_common_sequence
c_func
(paren
r_struct
id|hashmap
op_star
id|map
)paren
(brace
r_struct
id|entry
op_star
op_star
id|sequence
op_assign
id|xdl_malloc
c_func
(paren
id|map-&gt;nr
op_star
r_sizeof
(paren
r_struct
id|entry
op_star
)paren
)paren
suffix:semicolon
r_int
id|longest
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_struct
id|entry
op_star
id|entry
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|map-&gt;first
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;line2
op_logical_or
id|entry-&gt;line2
op_eq
id|NON_UNIQUE
)paren
r_continue
suffix:semicolon
id|i
op_assign
id|binary_search
c_func
(paren
id|sequence
comma
id|longest
comma
id|entry
)paren
suffix:semicolon
id|entry-&gt;previous
op_assign
id|i
OL
l_int|0
ques
c_cond
l_int|NULL
suffix:colon
id|sequence
(braket
id|i
)braket
suffix:semicolon
id|sequence
(braket
op_increment
id|i
)braket
op_assign
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|longest
)paren
id|longest
op_increment
suffix:semicolon
)brace
multiline_comment|/* No common unique lines were found */
r_if
c_cond
(paren
op_logical_neg
id|longest
)paren
(brace
id|xdl_free
c_func
(paren
id|sequence
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Iterate starting at the last element, adjusting the &quot;next&quot; members */
id|entry
op_assign
id|sequence
(braket
id|longest
l_int|1
)braket
suffix:semicolon
id|entry-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|entry-&gt;previous
)paren
(brace
id|entry-&gt;previous-&gt;next
op_assign
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;previous
suffix:semicolon
)brace
id|xdl_free
c_func
(paren
id|sequence
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
DECL|function|match
r_static
r_int
id|match
c_func
(paren
r_struct
id|hashmap
op_star
id|map
comma
r_int
id|line1
comma
r_int
id|line2
)paren
(brace
id|xrecord_t
op_star
id|record1
op_assign
id|map-&gt;env-&gt;xdf1.recs
(braket
id|line1
l_int|1
)braket
suffix:semicolon
id|xrecord_t
op_star
id|record2
op_assign
id|map-&gt;env-&gt;xdf2.recs
(braket
id|line2
l_int|1
)braket
suffix:semicolon
r_return
id|xdl_recmatch
c_func
(paren
id|record1-&gt;ptr
comma
id|record1-&gt;size
comma
id|record2-&gt;ptr
comma
id|record2-&gt;size
comma
id|map-&gt;xpp-&gt;flags
)paren
suffix:semicolon
)brace
r_static
r_int
id|patience_diff
c_func
(paren
id|mmfile_t
op_star
id|file1
comma
id|mmfile_t
op_star
id|file2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|env
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
suffix:semicolon
DECL|function|walk_common_sequence
r_static
r_int
id|walk_common_sequence
c_func
(paren
r_struct
id|hashmap
op_star
id|map
comma
r_struct
id|entry
op_star
id|first
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
r_int
id|end1
op_assign
id|line1
op_plus
id|count1
comma
id|end2
op_assign
id|line2
op_plus
id|count2
suffix:semicolon
r_int
id|next1
comma
id|next2
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* Try to grow the line ranges of common lines */
r_if
c_cond
(paren
id|first
)paren
(brace
id|next1
op_assign
id|first-&gt;line1
suffix:semicolon
id|next2
op_assign
id|first-&gt;line2
suffix:semicolon
r_while
c_loop
(paren
id|next1
OG
id|line1
op_logical_and
id|next2
OG
id|line2
op_logical_and
id|match
c_func
(paren
id|map
comma
id|next1
l_int|1
comma
id|next2
l_int|1
)paren
)paren
(brace
id|next1
op_decrement
suffix:semicolon
id|next2
op_decrement
suffix:semicolon
)brace
)brace
r_else
(brace
id|next1
op_assign
id|end1
suffix:semicolon
id|next2
op_assign
id|end2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|line1
OL
id|next1
op_logical_and
id|line2
OL
id|next2
op_logical_and
id|match
c_func
(paren
id|map
comma
id|line1
comma
id|line2
)paren
)paren
(brace
id|line1
op_increment
suffix:semicolon
id|line2
op_increment
suffix:semicolon
)brace
multiline_comment|/* Recurse */
r_if
c_cond
(paren
id|next1
OG
id|line1
op_logical_or
id|next2
OG
id|line2
)paren
(brace
r_struct
id|hashmap
id|submap
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|submap
comma
l_int|0
comma
r_sizeof
(paren
id|submap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|patience_diff
c_func
(paren
id|map-&gt;file1
comma
id|map-&gt;file2
comma
id|map-&gt;xpp
comma
id|map-&gt;env
comma
id|line1
comma
id|next1
id|line1
comma
id|line2
comma
id|next2
id|line2
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|first-&gt;next
op_logical_and
id|first-&gt;next-&gt;line1
op_eq
id|first-&gt;line1
op_plus
l_int|1
op_logical_and
id|first-&gt;next-&gt;line2
op_eq
id|first-&gt;line2
op_plus
l_int|1
)paren
id|first
op_assign
id|first-&gt;next
suffix:semicolon
id|line1
op_assign
id|first-&gt;line1
op_plus
l_int|1
suffix:semicolon
id|line2
op_assign
id|first-&gt;line2
op_plus
l_int|1
suffix:semicolon
id|first
op_assign
id|first-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|fall_back_to_classic_diff
r_static
r_int
id|fall_back_to_classic_diff
c_func
(paren
r_struct
id|hashmap
op_star
id|map
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
id|xpparam_t
id|xpp
suffix:semicolon
id|xpp.flags
op_assign
id|map-&gt;xpp-&gt;flags
op_amp
op_complement
id|XDF_DIFF_ALGORITHM_MASK
suffix:semicolon
r_return
id|xdl_fall_back_diff
c_func
(paren
id|map-&gt;env
comma
op_amp
id|xpp
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Recursively find the longest common sequence of unique lines,&n; * and if none was found, ask xdl_do_diff() to do the job.&n; *&n; * This function assumes that env was prepared with xdl_prepare_env().&n; */
DECL|function|patience_diff
r_static
r_int
id|patience_diff
c_func
(paren
id|mmfile_t
op_star
id|file1
comma
id|mmfile_t
op_star
id|file2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|env
comma
r_int
id|line1
comma
r_int
id|count1
comma
r_int
id|line2
comma
r_int
id|count2
)paren
(brace
r_struct
id|hashmap
id|map
suffix:semicolon
r_struct
id|entry
op_star
id|first
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* trivial case: one side is empty */
r_if
c_cond
(paren
op_logical_neg
id|count1
)paren
(brace
r_while
c_loop
(paren
id|count2
op_decrement
)paren
(brace
id|env-&gt;xdf2.rchg
(braket
id|line2
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|count2
)paren
(brace
r_while
c_loop
(paren
id|count1
op_decrement
)paren
(brace
id|env-&gt;xdf1.rchg
(braket
id|line1
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|map
comma
l_int|0
comma
r_sizeof
(paren
id|map
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fill_hashmap
c_func
(paren
id|file1
comma
id|file2
comma
id|xpp
comma
id|env
comma
op_amp
id|map
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* are there any matching lines at all? */
r_if
c_cond
(paren
op_logical_neg
id|map.has_matches
)paren
(brace
r_while
c_loop
(paren
id|count1
op_decrement
)paren
(brace
id|env-&gt;xdf1.rchg
(braket
id|line1
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count2
op_decrement
)paren
(brace
id|env-&gt;xdf2.rchg
(braket
id|line2
op_increment
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|xdl_free
c_func
(paren
id|map.entries
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|first
op_assign
id|find_longest_common_sequence
c_func
(paren
op_amp
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first
)paren
id|result
op_assign
id|walk_common_sequence
c_func
(paren
op_amp
id|map
comma
id|first
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
suffix:semicolon
r_else
id|result
op_assign
id|fall_back_to_classic_diff
c_func
(paren
op_amp
id|map
comma
id|line1
comma
id|count1
comma
id|line2
comma
id|count2
)paren
suffix:semicolon
id|xdl_free
c_func
(paren
id|map.entries
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|xdl_do_patience_diff
r_int
id|xdl_do_patience_diff
c_func
(paren
id|mmfile_t
op_star
id|file1
comma
id|mmfile_t
op_star
id|file2
comma
id|xpparam_t
r_const
op_star
id|xpp
comma
id|xdfenv_t
op_star
id|env
)paren
(brace
r_if
c_cond
(paren
id|xdl_prepare_env
c_func
(paren
id|file1
comma
id|file2
comma
id|xpp
comma
id|env
)paren
OL
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* environment is cleaned up in xdl_diff() */
r_return
id|patience_diff
c_func
(paren
id|file1
comma
id|file2
comma
id|xpp
comma
id|env
comma
l_int|1
comma
id|env-&gt;xdf1.nrec
comma
l_int|1
comma
id|env-&gt;xdf2.nrec
)paren
suffix:semicolon
)brace
eof
