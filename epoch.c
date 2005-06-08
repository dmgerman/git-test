multiline_comment|/*&n; * Copyright (c) 2005, Jon Seymour&n; *&n; * For more information about epoch theory on which this module is based,&n; * refer to http://blackcubes.dyndns.org/epoch/. That web page defines&n; * terms such as &quot;epoch&quot; and &quot;minimal, non-linear epoch&quot; and provides rationales&n; * for some of the algorithms used here.&n; *&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;openssl/bn.h&gt;&t;&t;
singleline_comment|// provides arbitrary precision integers
singleline_comment|// required to accurately represent fractional 
singleline_comment|//mass
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;epoch.h&quot;
DECL|struct|fraction
r_struct
id|fraction
(brace
DECL|member|numerator
id|BIGNUM
id|numerator
suffix:semicolon
DECL|member|denominator
id|BIGNUM
id|denominator
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HAS_EXACTLY_ONE_PARENT
mdefine_line|#define HAS_EXACTLY_ONE_PARENT(n) ((n)-&gt;parents &amp;&amp; !(n)-&gt;parents-&gt;next)
DECL|variable|context
r_static
id|BN_CTX
op_star
id|context
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|one
r_static
r_struct
id|fraction
op_star
id|one
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|zero
r_static
r_struct
id|fraction
op_star
id|zero
op_assign
l_int|NULL
suffix:semicolon
DECL|function|get_BN_CTX
r_static
id|BN_CTX
op_star
id|get_BN_CTX
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|context
)paren
(brace
id|context
op_assign
id|BN_CTX_new
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|context
suffix:semicolon
)brace
DECL|function|new_zero
r_static
r_struct
id|fraction
op_star
id|new_zero
c_func
(paren
)paren
(brace
r_struct
id|fraction
op_star
id|result
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|result
)paren
)paren
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|result-&gt;numerator
)paren
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|result-&gt;denominator
)paren
suffix:semicolon
id|BN_zero
c_func
(paren
op_amp
id|result-&gt;numerator
)paren
suffix:semicolon
id|BN_one
c_func
(paren
op_amp
id|result-&gt;denominator
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|clear_fraction
r_static
r_void
id|clear_fraction
c_func
(paren
r_struct
id|fraction
op_star
id|fraction
)paren
(brace
id|BN_clear
c_func
(paren
op_amp
id|fraction-&gt;numerator
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|fraction-&gt;denominator
)paren
suffix:semicolon
)brace
DECL|function|divide
r_static
r_struct
id|fraction
op_star
id|divide
c_func
(paren
r_struct
id|fraction
op_star
id|result
comma
r_struct
id|fraction
op_star
id|fraction
comma
r_int
id|divisor
)paren
(brace
id|BIGNUM
id|bn_divisor
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|bn_divisor
)paren
suffix:semicolon
id|BN_set_word
c_func
(paren
op_amp
id|bn_divisor
comma
id|divisor
)paren
suffix:semicolon
id|BN_copy
c_func
(paren
op_amp
id|result-&gt;numerator
comma
op_amp
id|fraction-&gt;numerator
)paren
suffix:semicolon
id|BN_mul
c_func
(paren
op_amp
id|result-&gt;denominator
comma
op_amp
id|fraction-&gt;denominator
comma
op_amp
id|bn_divisor
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|bn_divisor
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|init_fraction
r_static
r_struct
id|fraction
op_star
id|init_fraction
c_func
(paren
r_struct
id|fraction
op_star
id|fraction
)paren
(brace
id|BN_init
c_func
(paren
op_amp
id|fraction-&gt;numerator
)paren
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|fraction-&gt;denominator
)paren
suffix:semicolon
id|BN_zero
c_func
(paren
op_amp
id|fraction-&gt;numerator
)paren
suffix:semicolon
id|BN_one
c_func
(paren
op_amp
id|fraction-&gt;denominator
)paren
suffix:semicolon
r_return
id|fraction
suffix:semicolon
)brace
DECL|function|get_one
r_static
r_struct
id|fraction
op_star
id|get_one
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|one
)paren
(brace
id|one
op_assign
id|new_zero
c_func
(paren
)paren
suffix:semicolon
id|BN_one
c_func
(paren
op_amp
id|one-&gt;numerator
)paren
suffix:semicolon
)brace
r_return
id|one
suffix:semicolon
)brace
DECL|function|get_zero
r_static
r_struct
id|fraction
op_star
id|get_zero
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|zero
)paren
(brace
id|zero
op_assign
id|new_zero
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|zero
suffix:semicolon
)brace
DECL|function|copy
r_static
r_struct
id|fraction
op_star
id|copy
c_func
(paren
r_struct
id|fraction
op_star
id|to
comma
r_struct
id|fraction
op_star
id|from
)paren
(brace
id|BN_copy
c_func
(paren
op_amp
id|to-&gt;numerator
comma
op_amp
id|from-&gt;numerator
)paren
suffix:semicolon
id|BN_copy
c_func
(paren
op_amp
id|to-&gt;denominator
comma
op_amp
id|from-&gt;denominator
)paren
suffix:semicolon
r_return
id|to
suffix:semicolon
)brace
DECL|function|add
r_static
r_struct
id|fraction
op_star
id|add
c_func
(paren
r_struct
id|fraction
op_star
id|result
comma
r_struct
id|fraction
op_star
id|left
comma
r_struct
id|fraction
op_star
id|right
)paren
(brace
id|BIGNUM
id|a
comma
id|b
comma
id|gcd
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|a
)paren
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|b
)paren
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|gcd
)paren
suffix:semicolon
id|BN_mul
c_func
(paren
op_amp
id|a
comma
op_amp
id|left-&gt;numerator
comma
op_amp
id|right-&gt;denominator
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_mul
c_func
(paren
op_amp
id|b
comma
op_amp
id|left-&gt;denominator
comma
op_amp
id|right-&gt;numerator
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_mul
c_func
(paren
op_amp
id|result-&gt;denominator
comma
op_amp
id|left-&gt;denominator
comma
op_amp
id|right-&gt;denominator
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_add
c_func
(paren
op_amp
id|result-&gt;numerator
comma
op_amp
id|a
comma
op_amp
id|b
)paren
suffix:semicolon
id|BN_gcd
c_func
(paren
op_amp
id|gcd
comma
op_amp
id|result-&gt;denominator
comma
op_amp
id|result-&gt;numerator
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_div
c_func
(paren
op_amp
id|result-&gt;denominator
comma
l_int|NULL
comma
op_amp
id|result-&gt;denominator
comma
op_amp
id|gcd
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_div
c_func
(paren
op_amp
id|result-&gt;numerator
comma
l_int|NULL
comma
op_amp
id|result-&gt;numerator
comma
op_amp
id|gcd
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|a
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|b
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|gcd
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|compare
r_static
r_int
id|compare
c_func
(paren
r_struct
id|fraction
op_star
id|left
comma
r_struct
id|fraction
op_star
id|right
)paren
(brace
id|BIGNUM
id|a
comma
id|b
suffix:semicolon
r_int
id|result
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|a
)paren
suffix:semicolon
id|BN_init
c_func
(paren
op_amp
id|b
)paren
suffix:semicolon
id|BN_mul
c_func
(paren
op_amp
id|a
comma
op_amp
id|left-&gt;numerator
comma
op_amp
id|right-&gt;denominator
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|BN_mul
c_func
(paren
op_amp
id|b
comma
op_amp
id|left-&gt;denominator
comma
op_amp
id|right-&gt;numerator
comma
id|get_BN_CTX
c_func
(paren
)paren
)paren
suffix:semicolon
id|result
op_assign
id|BN_cmp
c_func
(paren
op_amp
id|a
comma
op_amp
id|b
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|a
)paren
suffix:semicolon
id|BN_clear
c_func
(paren
op_amp
id|b
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|struct|mass_counter
r_struct
id|mass_counter
(brace
DECL|member|seen
r_struct
id|fraction
id|seen
suffix:semicolon
DECL|member|pending
r_struct
id|fraction
id|pending
suffix:semicolon
)brace
suffix:semicolon
DECL|function|new_mass_counter
r_static
r_struct
id|mass_counter
op_star
id|new_mass_counter
c_func
(paren
r_struct
id|commit
op_star
id|commit
comma
r_struct
id|fraction
op_star
id|pending
)paren
(brace
r_struct
id|mass_counter
op_star
id|mass_counter
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mass_counter
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|mass_counter
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mass_counter
)paren
)paren
suffix:semicolon
id|init_fraction
c_func
(paren
op_amp
id|mass_counter-&gt;seen
)paren
suffix:semicolon
id|init_fraction
c_func
(paren
op_amp
id|mass_counter-&gt;pending
)paren
suffix:semicolon
id|copy
c_func
(paren
op_amp
id|mass_counter-&gt;pending
comma
id|pending
)paren
suffix:semicolon
id|copy
c_func
(paren
op_amp
id|mass_counter-&gt;seen
comma
id|get_zero
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|commit-&gt;object.util
)paren
(brace
id|die
c_func
(paren
l_string|&quot;multiple attempts to initialize mass counter for %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|commit-&gt;object.util
op_assign
id|mass_counter
suffix:semicolon
r_return
id|mass_counter
suffix:semicolon
)brace
DECL|function|free_mass_counter
r_static
r_void
id|free_mass_counter
c_func
(paren
r_struct
id|mass_counter
op_star
id|counter
)paren
(brace
id|clear_fraction
c_func
(paren
op_amp
id|counter-&gt;seen
)paren
suffix:semicolon
id|clear_fraction
c_func
(paren
op_amp
id|counter-&gt;pending
)paren
suffix:semicolon
id|free
c_func
(paren
id|counter
)paren
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Finds the base commit of a list of commits.
singleline_comment|//
singleline_comment|// One property of the commit being searched for is that every commit reachable 
singleline_comment|// from the base commit is reachable from the commits in the starting list only 
singleline_comment|// via paths that include the base commit.
singleline_comment|//
singleline_comment|// This algorithm uses a conservation of mass approach to find the base commit.
singleline_comment|//
singleline_comment|// We start by injecting one unit of mass into the graph at each
singleline_comment|// of the commits in the starting list. Injecting mass into a commit
singleline_comment|// is achieved by adding to its pending mass counter and, if it is not already
singleline_comment|// enqueued, enqueuing the commit in a list of pending commits, in latest 
singleline_comment|// commit date first order.
singleline_comment|//
singleline_comment|// The algorithm then preceeds to visit each commit in the pending queue.
singleline_comment|// Upon each visit, the pending mass is added to the mass already seen for that 
singleline_comment|// commit and then divided into N equal portions, where N is the number of 
singleline_comment|// parents of the commit being visited. The divided portions are then injected 
singleline_comment|// into each of the parents.
singleline_comment|//
singleline_comment|// The algorithm continues until we discover a commit which has seen all the
singleline_comment|// mass originally injected or until we run out of things to do. 
singleline_comment|//
singleline_comment|// If we find a commit that has seen all the original mass, we have found
singleline_comment|// the common base of all the commits in the starting list. 
singleline_comment|//
singleline_comment|// The algorithm does _not_ depend on accurate timestamps for correct operation.
singleline_comment|// However, reasonably sane (e.g. non-random) timestamps are required in order 
singleline_comment|// to prevent an exponential performance characteristic. The occasional 
singleline_comment|// timestamp inaccuracy will not dramatically affect performance but may 
singleline_comment|// result in more nodes being processed than strictly necessary.
singleline_comment|//
singleline_comment|// This procedure sets *boundary to the address of the base commit. It returns 
singleline_comment|// non-zero if, and only if, there was a problem parsing one of the 
singleline_comment|// commits discovered during the traversal.
singleline_comment|//
DECL|function|find_base_for_list
r_static
r_int
id|find_base_for_list
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
r_struct
id|commit
op_star
op_star
id|boundary
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|cleaner
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|pending
op_assign
l_int|NULL
suffix:semicolon
op_star
id|boundary
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|fraction
id|injected
suffix:semicolon
id|init_fraction
c_func
(paren
op_amp
id|injected
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|item
op_assign
id|list-&gt;item
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;object.util
)paren
(brace
id|die
c_func
(paren
l_string|&quot;%s:%d:%s: logic error: this should not have happened - commit %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
comma
id|sha1_to_hex
c_func
(paren
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|new_mass_counter
c_func
(paren
id|list-&gt;item
comma
id|get_one
c_func
(paren
)paren
)paren
suffix:semicolon
id|add
c_func
(paren
op_amp
id|injected
comma
op_amp
id|injected
comma
id|get_one
c_func
(paren
)paren
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|list-&gt;item
comma
op_amp
id|cleaner
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|list-&gt;item
comma
op_amp
id|pending
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
op_star
id|boundary
op_logical_and
id|pending
op_logical_and
op_logical_neg
id|ret
)paren
(brace
r_struct
id|commit
op_star
id|latest
op_assign
id|pop_commit
c_func
(paren
op_amp
id|pending
)paren
suffix:semicolon
r_struct
id|mass_counter
op_star
id|latest_node
op_assign
(paren
r_struct
id|mass_counter
op_star
)paren
id|latest-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|parse_commit
c_func
(paren
id|latest
)paren
)paren
)paren
r_continue
suffix:semicolon
id|add
c_func
(paren
op_amp
id|latest_node-&gt;seen
comma
op_amp
id|latest_node-&gt;seen
comma
op_amp
id|latest_node-&gt;pending
)paren
suffix:semicolon
r_int
id|num_parents
op_assign
id|count_parents
c_func
(paren
id|latest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_parents
)paren
(brace
r_struct
id|fraction
id|distribution
suffix:semicolon
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
id|divide
c_func
(paren
id|init_fraction
c_func
(paren
op_amp
id|distribution
)paren
comma
op_amp
id|latest_node-&gt;pending
comma
id|num_parents
)paren
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|latest-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|parents-&gt;item
suffix:semicolon
r_struct
id|mass_counter
op_star
id|parent_node
op_assign
(paren
r_struct
id|mass_counter
op_star
)paren
id|parent-&gt;object.util
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
id|parent_node
op_assign
id|new_mass_counter
c_func
(paren
id|parent
comma
op_amp
id|distribution
)paren
suffix:semicolon
id|insert_by_date
c_func
(paren
op_amp
id|pending
comma
id|parent
)paren
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|parent
comma
op_amp
id|cleaner
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|compare
c_func
(paren
op_amp
id|parent_node-&gt;pending
comma
id|get_zero
c_func
(paren
)paren
)paren
)paren
(brace
id|insert_by_date
c_func
(paren
op_amp
id|pending
comma
id|parent
)paren
suffix:semicolon
)brace
id|add
c_func
(paren
op_amp
id|parent_node-&gt;pending
comma
op_amp
id|parent_node-&gt;pending
comma
op_amp
id|distribution
)paren
suffix:semicolon
)brace
)brace
id|clear_fraction
c_func
(paren
op_amp
id|distribution
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|compare
c_func
(paren
op_amp
id|latest_node-&gt;seen
comma
op_amp
id|injected
)paren
)paren
(brace
op_star
id|boundary
op_assign
id|latest
suffix:semicolon
)brace
id|copy
c_func
(paren
op_amp
id|latest_node-&gt;pending
comma
id|get_zero
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cleaner
)paren
(brace
r_struct
id|commit
op_star
id|next
op_assign
id|pop_commit
c_func
(paren
op_amp
id|cleaner
)paren
suffix:semicolon
id|free_mass_counter
c_func
(paren
(paren
r_struct
id|mass_counter
op_star
)paren
id|next-&gt;object.util
)paren
suffix:semicolon
id|next-&gt;object.util
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pending
)paren
id|free_commit_list
c_func
(paren
id|pending
)paren
suffix:semicolon
id|clear_fraction
c_func
(paren
op_amp
id|injected
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Finds the base of an minimal, non-linear epoch, headed at head, by
singleline_comment|// applying the find_base_for_list to a list consisting of the parents
singleline_comment|//
DECL|function|find_base
r_static
r_int
id|find_base
c_func
(paren
r_struct
id|commit
op_star
id|head
comma
r_struct
id|commit
op_star
op_star
id|boundary
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|commit_list
op_star
id|pending
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit_list
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|head-&gt;parents
suffix:semicolon
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
(brace
id|commit_list_insert
c_func
(paren
id|next-&gt;item
comma
op_amp
id|pending
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|find_base_for_list
c_func
(paren
id|pending
comma
id|boundary
)paren
suffix:semicolon
id|free_commit_list
c_func
(paren
id|pending
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// This procedure traverses to the boundary of the first epoch in the epoch
singleline_comment|// sequence of the epoch headed at head_of_epoch. This is either the end of
singleline_comment|// the maximal linear epoch or the base of a minimal non-linear epoch.
singleline_comment|//
singleline_comment|// The queue of pending nodes is sorted in reverse date order and each node
singleline_comment|// is currently in the queue at most once.
singleline_comment|//
DECL|function|find_next_epoch_boundary
r_static
r_int
id|find_next_epoch_boundary
c_func
(paren
r_struct
id|commit
op_star
id|head_of_epoch
comma
r_struct
id|commit
op_star
op_star
id|boundary
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|commit
op_star
id|item
op_assign
id|head_of_epoch
suffix:semicolon
id|ret
op_assign
id|parse_commit
c_func
(paren
id|item
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|HAS_EXACTLY_ONE_PARENT
c_func
(paren
id|item
)paren
)paren
(brace
singleline_comment|// we are at the start of a maximimal linear epoch .. traverse to the end
singleline_comment|// traverse to the end of a maximal linear epoch
r_while
c_loop
(paren
id|HAS_EXACTLY_ONE_PARENT
c_func
(paren
id|item
)paren
op_logical_and
op_logical_neg
id|ret
)paren
(brace
id|item
op_assign
id|item-&gt;parents-&gt;item
suffix:semicolon
id|ret
op_assign
id|parse_commit
c_func
(paren
id|item
)paren
suffix:semicolon
)brace
op_star
id|boundary
op_assign
id|item
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// otherwise, we are at the start of a minimal, non-linear
singleline_comment|// epoch - find the common base of all parents.
id|ret
op_assign
id|find_base
c_func
(paren
id|item
comma
id|boundary
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Returns non-zero if parent is known to be a parent of child.
singleline_comment|//
DECL|function|is_parent_of
r_static
r_int
id|is_parent_of
c_func
(paren
r_struct
id|commit
op_star
id|parent
comma
r_struct
id|commit
op_star
id|child
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_for
c_loop
(paren
id|parents
op_assign
id|child-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|parent-&gt;object.sha1
comma
id|parents-&gt;item-&gt;object.sha1
comma
r_sizeof
(paren
id|parents-&gt;item-&gt;object.sha1
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Pushes an item onto the merge order stack. If the top of the stack is
singleline_comment|// marked as being a possible &quot;break&quot;, we check to see whether it actually
singleline_comment|// is a break.
singleline_comment|//
DECL|function|push_onto_merge_order_stack
r_static
r_void
id|push_onto_merge_order_stack
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|stack
comma
r_struct
id|commit
op_star
id|item
)paren
(brace
r_struct
id|commit_list
op_star
id|top
op_assign
op_star
id|stack
suffix:semicolon
r_if
c_cond
(paren
id|top
op_logical_and
(paren
id|top-&gt;item-&gt;object.flags
op_amp
id|DISCONTINUITY
)paren
)paren
(brace
r_if
c_cond
(paren
id|is_parent_of
c_func
(paren
id|top-&gt;item
comma
id|item
)paren
)paren
(brace
id|top-&gt;item-&gt;object.flags
op_and_assign
op_complement
id|DISCONTINUITY
suffix:semicolon
)brace
)brace
id|commit_list_insert
c_func
(paren
id|item
comma
id|stack
)paren
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Marks all interesting, visited commits reachable from this commit
singleline_comment|// as uninteresting. We stop recursing when we reach the epoch boundary,
singleline_comment|// an unvisited node or a node that has already been marking uninteresting.
singleline_comment|// This doesn&squot;t actually mark all ancestors between the start node and the
singleline_comment|// epoch boundary uninteresting, but does ensure that they will 
singleline_comment|// eventually be marked uninteresting when the main sort_first_epoch 
singleline_comment|// traversal eventually reaches them. 
singleline_comment|//
DECL|function|mark_ancestors_uninteresting
r_static
r_void
id|mark_ancestors_uninteresting
c_func
(paren
r_struct
id|commit
op_star
id|commit
)paren
(brace
r_int
r_int
id|flags
op_assign
id|commit-&gt;object.flags
suffix:semicolon
r_int
id|visited
op_assign
id|flags
op_amp
id|VISITED
suffix:semicolon
r_int
id|boundary
op_assign
id|flags
op_amp
id|BOUNDARY
suffix:semicolon
r_int
id|uninteresting
op_assign
id|flags
op_amp
id|UNINTERESTING
suffix:semicolon
id|commit-&gt;object.flags
op_or_assign
id|UNINTERESTING
suffix:semicolon
r_if
c_cond
(paren
id|uninteresting
op_logical_or
id|boundary
op_logical_or
op_logical_neg
id|visited
)paren
(brace
r_return
suffix:semicolon
singleline_comment|// we only need to recurse if
singleline_comment|//      we are not on the boundary, and,
singleline_comment|//      we have not already been marked uninteresting, and,
singleline_comment|//      we have already been visited.
singleline_comment|//
singleline_comment|// the main sort_first_epoch traverse will 
singleline_comment|// mark unreachable all uninteresting, unvisited parents 
singleline_comment|// as they are visited so there is no need to duplicate
singleline_comment|// that traversal here.
singleline_comment|//
singleline_comment|// similarly, if we are already marked uninteresting
singleline_comment|// then either all ancestors have already been marked
singleline_comment|// uninteresting or will be once the sort_first_epoch
singleline_comment|// traverse reaches them.
singleline_comment|//
)brace
r_struct
id|commit_list
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|commit-&gt;parents
suffix:semicolon
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
id|mark_ancestors_uninteresting
c_func
(paren
id|next-&gt;item
)paren
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Sorts the nodes of the first epoch of the epoch sequence of the epoch headed at head
singleline_comment|// into merge order.
singleline_comment|//
DECL|function|sort_first_epoch
r_static
r_void
id|sort_first_epoch
c_func
(paren
r_struct
id|commit
op_star
id|head
comma
r_struct
id|commit_list
op_star
op_star
id|stack
)paren
(brace
r_struct
id|commit_list
op_star
id|parents
suffix:semicolon
r_struct
id|commit_list
op_star
id|reversed_parents
op_assign
l_int|NULL
suffix:semicolon
id|head-&gt;object.flags
op_or_assign
id|VISITED
suffix:semicolon
singleline_comment|//
singleline_comment|// parse_commit builds the parent list in reverse order with respect to the order of
singleline_comment|// the git-commit-tree arguments.
singleline_comment|//
singleline_comment|// so we need to reverse this list to output the oldest (or most &quot;local&quot;) commits last.
singleline_comment|//
r_for
c_loop
(paren
id|parents
op_assign
id|head-&gt;parents
suffix:semicolon
id|parents
suffix:semicolon
id|parents
op_assign
id|parents-&gt;next
)paren
id|commit_list_insert
c_func
(paren
id|parents-&gt;item
comma
op_amp
id|reversed_parents
)paren
suffix:semicolon
singleline_comment|//
singleline_comment|// todo: by sorting the parents in a different order, we can alter the 
singleline_comment|// merge order to show contemporaneous changes in parallel branches
singleline_comment|// occurring after &quot;local&quot; changes. This is useful for a developer
singleline_comment|// when a developer wants to see all changes that were incorporated
singleline_comment|// into the same merge as her own changes occur after her own
singleline_comment|// changes.
singleline_comment|//
r_while
c_loop
(paren
id|reversed_parents
)paren
(brace
r_struct
id|commit
op_star
id|parent
op_assign
id|pop_commit
c_func
(paren
op_amp
id|reversed_parents
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
(brace
singleline_comment|// propagates the uninteresting bit to
singleline_comment|// all parents. if we have already visited
singleline_comment|// this parent, then the uninteresting bit
singleline_comment|// will be propagated to each reachable 
singleline_comment|// commit that is still not marked uninteresting
singleline_comment|// and won&squot;t otherwise be reached.
id|mark_ancestors_uninteresting
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|parent-&gt;object.flags
op_amp
id|VISITED
)paren
)paren
(brace
r_if
c_cond
(paren
id|parent-&gt;object.flags
op_amp
id|BOUNDARY
)paren
(brace
r_if
c_cond
(paren
op_star
id|stack
)paren
(brace
id|die
c_func
(paren
l_string|&quot;something else is on the stack - %s&bslash;n&quot;
comma
id|sha1_to_hex
c_func
(paren
(paren
op_star
id|stack
)paren
op_member_access_from_pointer
id|item-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
id|push_onto_merge_order_stack
c_func
(paren
id|stack
comma
id|parent
)paren
suffix:semicolon
id|parent-&gt;object.flags
op_or_assign
id|VISITED
suffix:semicolon
)brace
r_else
(brace
id|sort_first_epoch
c_func
(paren
id|parent
comma
id|stack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reversed_parents
)paren
(brace
singleline_comment|//
singleline_comment|// this indicates a possible discontinuity
singleline_comment|// it may not be be actual discontinuity if
singleline_comment|// the head of parent N happens to be the tail
singleline_comment|// of parent N+1
singleline_comment|//
singleline_comment|// the next push onto the stack will resolve the 
singleline_comment|// question
singleline_comment|//
(paren
op_star
id|stack
)paren
op_member_access_from_pointer
id|item-&gt;object.flags
op_or_assign
id|DISCONTINUITY
suffix:semicolon
)brace
)brace
)brace
)brace
id|push_onto_merge_order_stack
c_func
(paren
id|stack
comma
id|head
)paren
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Emit the contents of the stack. 
singleline_comment|//
singleline_comment|// The stack is freed and replaced by NULL.
singleline_comment|//
singleline_comment|// Sets the return value to STOP if no further output should be generated.
singleline_comment|//
DECL|function|emit_stack
r_static
r_int
id|emit_stack
c_func
(paren
r_struct
id|commit_list
op_star
op_star
id|stack
comma
id|emitter_func
id|emitter
)paren
(brace
r_int
r_int
id|seen
op_assign
l_int|0
suffix:semicolon
r_int
id|action
op_assign
id|CONTINUE
suffix:semicolon
r_while
c_loop
(paren
op_star
id|stack
op_logical_and
(paren
id|action
op_ne
id|STOP
)paren
)paren
(brace
r_struct
id|commit
op_star
id|next
op_assign
id|pop_commit
c_func
(paren
id|stack
)paren
suffix:semicolon
id|seen
op_or_assign
id|next-&gt;object.flags
suffix:semicolon
r_if
c_cond
(paren
op_star
id|stack
)paren
(brace
id|action
op_assign
(paren
op_star
id|emitter
)paren
(paren
id|next
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|stack
)paren
(brace
id|free_commit_list
c_func
(paren
op_star
id|stack
)paren
suffix:semicolon
op_star
id|stack
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|action
op_eq
id|STOP
op_logical_or
(paren
id|seen
op_amp
id|UNINTERESTING
)paren
)paren
ques
c_cond
id|STOP
suffix:colon
id|CONTINUE
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Sorts an arbitrary epoch into merge order by sorting each epoch
singleline_comment|// of its epoch sequence into order.
singleline_comment|//
singleline_comment|// Note: this algorithm currently leaves traces of its execution in the
singleline_comment|// object flags of nodes it discovers. This should probably be fixed.
singleline_comment|//
DECL|function|sort_in_merge_order
r_static
r_int
id|sort_in_merge_order
c_func
(paren
r_struct
id|commit
op_star
id|head_of_epoch
comma
id|emitter_func
id|emitter
)paren
(brace
r_struct
id|commit
op_star
id|next
op_assign
id|head_of_epoch
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|action
op_assign
id|CONTINUE
suffix:semicolon
id|ret
op_assign
id|parse_commit
c_func
(paren
id|head_of_epoch
)paren
suffix:semicolon
r_while
c_loop
(paren
id|next
op_logical_and
id|next-&gt;parents
op_logical_and
op_logical_neg
id|ret
op_logical_and
(paren
id|action
op_ne
id|STOP
)paren
)paren
(brace
r_struct
id|commit
op_star
id|base
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|find_next_epoch_boundary
c_func
(paren
id|next
comma
op_amp
id|base
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|next-&gt;object.flags
op_or_assign
id|BOUNDARY
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
(brace
id|base-&gt;object.flags
op_or_assign
id|BOUNDARY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|HAS_EXACTLY_ONE_PARENT
c_func
(paren
id|next
)paren
)paren
(brace
r_while
c_loop
(paren
id|HAS_EXACTLY_ONE_PARENT
c_func
(paren
id|next
)paren
op_logical_and
(paren
id|action
op_ne
id|STOP
)paren
op_logical_and
op_logical_neg
id|ret
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
(brace
id|action
op_assign
id|STOP
suffix:semicolon
)brace
r_else
(brace
id|action
op_assign
(paren
op_star
id|emitter
)paren
(paren
id|next
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action
op_ne
id|STOP
)paren
(brace
id|next
op_assign
id|next-&gt;parents-&gt;item
suffix:semicolon
id|ret
op_assign
id|parse_commit
c_func
(paren
id|next
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_struct
id|commit_list
op_star
id|stack
op_assign
l_int|NULL
suffix:semicolon
id|sort_first_epoch
c_func
(paren
id|next
comma
op_amp
id|stack
)paren
suffix:semicolon
id|action
op_assign
id|emit_stack
c_func
(paren
op_amp
id|stack
comma
id|emitter
)paren
suffix:semicolon
id|next
op_assign
id|base
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|next
op_logical_and
(paren
id|action
op_ne
id|STOP
)paren
op_logical_and
op_logical_neg
id|ret
)paren
(brace
(paren
op_star
id|emitter
)paren
(paren
id|next
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// Sorts the nodes reachable from a starting list in merge order, we 
singleline_comment|// first find the base for the starting list and then sort all nodes in this 
singleline_comment|// subgraph using the sort_first_epoch algorithm. Once we have reached the base
singleline_comment|// we can continue sorting using sort_in_merge_order.
singleline_comment|//
DECL|function|sort_list_in_merge_order
r_int
id|sort_list_in_merge_order
c_func
(paren
r_struct
id|commit_list
op_star
id|list
comma
id|emitter_func
id|emitter
)paren
(brace
r_struct
id|commit_list
op_star
id|stack
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|commit
op_star
id|base
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|action
op_assign
id|CONTINUE
suffix:semicolon
r_struct
id|commit_list
op_star
id|reversed
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_struct
id|commit
op_star
id|next
op_assign
id|list-&gt;item
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|next-&gt;object.flags
op_amp
id|UNINTERESTING
)paren
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;object.flags
op_amp
id|DUPCHECK
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s: duplicate commit %s ignored&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|sha1_to_hex
c_func
(paren
id|next-&gt;object.sha1
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|next-&gt;object.flags
op_or_assign
id|DUPCHECK
suffix:semicolon
id|commit_list_insert
c_func
(paren
id|list-&gt;item
comma
op_amp
id|reversed
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|reversed-&gt;next
)paren
(brace
singleline_comment|// if there is only one element in the list, we can sort it using 
singleline_comment|// sort_in_merge_order.
id|base
op_assign
id|reversed-&gt;item
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// otherwise, we search for the base of the list
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|find_base_for_list
c_func
(paren
id|reversed
comma
op_amp
id|base
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
(brace
id|base-&gt;object.flags
op_or_assign
id|BOUNDARY
suffix:semicolon
)brace
r_while
c_loop
(paren
id|reversed
)paren
(brace
id|sort_first_epoch
c_func
(paren
id|pop_commit
c_func
(paren
op_amp
id|reversed
)paren
comma
op_amp
id|stack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reversed
)paren
(brace
singleline_comment|//
singleline_comment|// if we have more commits to push, then the
singleline_comment|// first push for the next parent may (or may not)
singleline_comment|// represent a discontinuity with respect to the
singleline_comment|// parent currently on the top of the stack.
singleline_comment|//
singleline_comment|// mark it for checking here, and check it
singleline_comment|// with the next push...see sort_first_epoch for
singleline_comment|// more details.
singleline_comment|//
id|stack-&gt;item-&gt;object.flags
op_or_assign
id|DISCONTINUITY
suffix:semicolon
)brace
)brace
id|action
op_assign
id|emit_stack
c_func
(paren
op_amp
id|stack
comma
id|emitter
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_logical_and
(paren
id|action
op_ne
id|STOP
)paren
)paren
(brace
id|ret
op_assign
id|sort_in_merge_order
c_func
(paren
id|base
comma
id|emitter
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
eof
