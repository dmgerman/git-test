macro_line|#include &quot;builtin.h&quot;
macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;commit.h&quot;
macro_line|#include &quot;diff.h&quot;
macro_line|#include &quot;path-list.h&quot;
macro_line|#include &quot;revision.h&quot;
macro_line|#include &lt;string.h&gt;
DECL|variable|shortlog_usage
r_static
r_const
r_char
id|shortlog_usage
(braket
)braket
op_assign
l_string|&quot;git-shortlog [-n] [-s] [&lt;commit-id&gt;... ]&bslash;n&quot;
suffix:semicolon
DECL|function|compare_by_number
r_static
r_int
id|compare_by_number
c_func
(paren
r_const
r_void
op_star
id|a1
comma
r_const
r_void
op_star
id|a2
)paren
(brace
r_const
r_struct
id|path_list_item
op_star
id|i1
op_assign
id|a1
comma
op_star
id|i2
op_assign
id|a2
suffix:semicolon
r_const
r_struct
id|path_list
op_star
id|l1
op_assign
id|i1-&gt;util
comma
op_star
id|l2
op_assign
id|i2-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|l1-&gt;nr
OL
id|l2-&gt;nr
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|l1-&gt;nr
op_eq
id|l2-&gt;nr
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_plus
l_int|1
suffix:semicolon
)brace
DECL|variable|mailmap_list
r_static
r_struct
id|path_list_item
id|mailmap_list
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;R.Marek@sh.cvut.cz&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Rudolf Marek&quot;
)brace
comma
(brace
l_string|&quot;Ralf.Wildenhues@gmx.de&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Ralf Wildenhues&quot;
)brace
comma
(brace
l_string|&quot;aherrman@de.ibm.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Andreas Herrmann&quot;
)brace
comma
(brace
l_string|&quot;akpm@osdl.org&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Andrew Morton&quot;
)brace
comma
(brace
l_string|&quot;andrew.vasquez@qlogic.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Andrew Vasquez&quot;
)brace
comma
(brace
l_string|&quot;aquynh@gmail.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Nguyen Anh Quynh&quot;
)brace
comma
(brace
l_string|&quot;axboe@suse.de&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Jens Axboe&quot;
)brace
comma
(brace
l_string|&quot;blaisorblade@yahoo.it&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Paolo &squot;Blaisorblade&squot; Giarrusso&quot;
)brace
comma
(brace
l_string|&quot;bunk@stusta.de&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Adrian Bunk&quot;
)brace
comma
(brace
l_string|&quot;domen@coderock.org&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Domen Puncer&quot;
)brace
comma
(brace
l_string|&quot;dougg@torque.net&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Douglas Gilbert&quot;
)brace
comma
(brace
l_string|&quot;dwmw2@shinybook.infradead.org&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;David Woodhouse&quot;
)brace
comma
(brace
l_string|&quot;ecashin@coraid.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Ed L Cashin&quot;
)brace
comma
(brace
l_string|&quot;felix@derklecks.de&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Felix Moeller&quot;
)brace
comma
(brace
l_string|&quot;fzago@systemfabricworks.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Frank Zago&quot;
)brace
comma
(brace
l_string|&quot;gregkh@suse.de&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Greg Kroah-Hartman&quot;
)brace
comma
(brace
l_string|&quot;hch@lst.de&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Christoph Hellwig&quot;
)brace
comma
(brace
l_string|&quot;htejun@gmail.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Tejun Heo&quot;
)brace
comma
(brace
l_string|&quot;jejb@mulgrave.(none)&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;James Bottomley&quot;
)brace
comma
(brace
l_string|&quot;jejb@titanic.il.steeleye.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;James Bottomley&quot;
)brace
comma
(brace
l_string|&quot;jgarzik@pretzel.yyz.us&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Jeff Garzik&quot;
)brace
comma
(brace
l_string|&quot;johnpol@2ka.mipt.ru&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Evgeniy Polyakov&quot;
)brace
comma
(brace
l_string|&quot;kay.sievers@vrfy.org&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Kay Sievers&quot;
)brace
comma
(brace
l_string|&quot;minyard@acm.org&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Corey Minyard&quot;
)brace
comma
(brace
l_string|&quot;mshah@teja.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Mitesh shah&quot;
)brace
comma
(brace
l_string|&quot;pj@ludd.ltu.se&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Peter A Jonsson&quot;
)brace
comma
(brace
l_string|&quot;rmps@joel.ist.utl.pt&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Rui Saraiva&quot;
)brace
comma
(brace
l_string|&quot;santtu.hyrkko@gmail.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Santtu Hyrkk&#x1b;,Av&#x1b;(B&quot;
)brace
comma
(brace
l_string|&quot;simon@thekelleys.org.uk&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Simon Kelley&quot;
)brace
comma
(brace
l_string|&quot;ssant@in.ibm.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Sachin P Sant&quot;
)brace
comma
(brace
l_string|&quot;terra@gnome.org&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Morten Welinder&quot;
)brace
comma
(brace
l_string|&quot;tony.luck@intel.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Tony Luck&quot;
)brace
comma
(brace
l_string|&quot;welinder@anemone.rentec.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Morten Welinder&quot;
)brace
comma
(brace
l_string|&quot;welinder@darter.rentec.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Morten Welinder&quot;
)brace
comma
(brace
l_string|&quot;welinder@troll.com&quot;
comma
(paren
r_void
op_star
)paren
l_string|&quot;Morten Welinder&quot;
)brace
)brace
suffix:semicolon
DECL|variable|mailmap
r_static
r_struct
id|path_list
id|mailmap
op_assign
(brace
id|mailmap_list
comma
r_sizeof
(paren
id|mailmap_list
)paren
op_div
r_sizeof
(paren
r_struct
id|path_list_item
)paren
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|map_email
r_static
r_int
id|map_email
c_func
(paren
r_char
op_star
id|email
comma
r_char
op_star
id|name
comma
r_int
id|maxlen
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
multiline_comment|/* autocomplete common developers */
id|p
op_assign
id|strchr
c_func
(paren
id|email
comma
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|item
op_assign
id|path_list_lookup
c_func
(paren
id|email
comma
op_amp
id|mailmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item
op_ne
l_int|NULL
)paren
(brace
r_const
r_char
op_star
id|realname
op_assign
(paren
r_const
r_char
op_star
)paren
id|item-&gt;util
suffix:semicolon
id|strncpy
c_func
(paren
id|name
comma
id|realname
comma
id|maxlen
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|insert_author_oneline
r_static
r_void
id|insert_author_oneline
c_func
(paren
r_struct
id|path_list
op_star
id|list
comma
r_const
r_char
op_star
id|author
comma
r_int
id|authorlen
comma
r_const
r_char
op_star
id|oneline
comma
r_int
id|onelinelen
)paren
(brace
r_const
r_char
op_star
id|dot3
op_assign
l_string|&quot;/pub/scm/linux/kernel/git/&quot;
suffix:semicolon
r_char
op_star
id|buffer
comma
op_star
id|p
suffix:semicolon
r_struct
id|path_list_item
op_star
id|item
suffix:semicolon
r_struct
id|path_list
op_star
id|onelines
suffix:semicolon
r_while
c_loop
(paren
id|authorlen
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|author
(braket
id|authorlen
l_int|1
)braket
)paren
)paren
id|authorlen
op_decrement
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|authorlen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|author
comma
id|authorlen
)paren
suffix:semicolon
id|buffer
(braket
id|authorlen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|item
op_assign
id|path_list_insert
c_func
(paren
id|buffer
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|item-&gt;util
op_eq
l_int|NULL
)paren
id|item-&gt;util
op_assign
id|xcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|path_list
)paren
)paren
suffix:semicolon
r_else
id|free
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|oneline
comma
l_string|&quot;[PATCH&quot;
comma
l_int|6
)paren
)paren
(brace
r_char
op_star
id|eob
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot;]&squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|eob
(braket
l_int|1
)braket
)paren
op_logical_and
id|eob
(braket
l_int|1
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|eob
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|eob
id|oneline
OL
id|onelinelen
)paren
(brace
id|onelinelen
op_sub_assign
id|eob
id|oneline
suffix:semicolon
id|oneline
op_assign
id|eob
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|onelinelen
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|oneline
(braket
l_int|0
)braket
)paren
)paren
(brace
id|oneline
op_increment
suffix:semicolon
id|onelinelen
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|onelinelen
OG
l_int|0
op_logical_and
id|isspace
c_func
(paren
id|oneline
(braket
id|onelinelen
l_int|1
)braket
)paren
)paren
id|onelinelen
op_decrement
suffix:semicolon
id|buffer
op_assign
id|xmalloc
c_func
(paren
id|onelinelen
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|oneline
comma
id|onelinelen
)paren
suffix:semicolon
id|buffer
(braket
id|onelinelen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|strstr
c_func
(paren
id|buffer
comma
id|dot3
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|p
comma
l_string|&quot;...&quot;
comma
l_int|3
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|p
op_plus
l_int|2
comma
id|p
op_plus
r_sizeof
(paren
id|dot3
)paren
l_int|1
)paren
suffix:semicolon
)brace
id|onelines
op_assign
id|item-&gt;util
suffix:semicolon
r_if
c_cond
(paren
id|onelines-&gt;nr
op_ge
id|onelines-&gt;alloc
)paren
(brace
id|onelines-&gt;alloc
op_assign
id|alloc_nr
c_func
(paren
id|onelines-&gt;nr
)paren
suffix:semicolon
id|onelines-&gt;items
op_assign
id|xrealloc
c_func
(paren
id|onelines-&gt;items
comma
id|onelines-&gt;alloc
op_star
r_sizeof
(paren
r_struct
id|path_list_item
)paren
)paren
suffix:semicolon
)brace
id|onelines-&gt;items
(braket
id|onelines-&gt;nr
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
id|onelines-&gt;items
(braket
id|onelines-&gt;nr
op_increment
)braket
dot
id|path
op_assign
id|buffer
suffix:semicolon
)brace
DECL|function|read_from_stdin
r_static
r_void
id|read_from_stdin
c_func
(paren
r_struct
id|path_list
op_star
id|list
)paren
(brace
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
comma
id|stdin
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|bob
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;A&squot;
op_logical_or
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;a&squot;
)paren
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
op_plus
l_int|1
comma
l_string|&quot;uthor: &quot;
comma
l_int|7
)paren
op_logical_and
(paren
id|bob
op_assign
id|strchr
c_func
(paren
id|buffer
op_plus
l_int|7
comma
l_char|&squot;&lt;&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
id|buffer2
(braket
l_int|1024
)braket
comma
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|map_email
c_func
(paren
id|bob
op_plus
l_int|1
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
)paren
id|bob
op_assign
id|buffer
op_plus
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_else
(brace
id|offset
op_assign
l_int|8
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
id|bob
(braket
l_int|1
)braket
)paren
)paren
id|bob
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|buffer2
comma
r_sizeof
(paren
id|buffer2
)paren
comma
id|stdin
)paren
op_logical_and
id|buffer2
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
multiline_comment|/* chomp input */
r_if
c_cond
(paren
id|fgets
c_func
(paren
id|buffer2
comma
r_sizeof
(paren
id|buffer2
)paren
comma
id|stdin
)paren
)paren
id|insert_author_oneline
c_func
(paren
id|list
comma
id|buffer
op_plus
id|offset
comma
id|bob
id|buffer
id|offset
comma
id|buffer2
comma
id|strlen
c_func
(paren
id|buffer2
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|get_from_rev
r_static
r_void
id|get_from_rev
c_func
(paren
r_struct
id|rev_info
op_star
id|rev
comma
r_struct
id|path_list
op_star
id|list
)paren
(brace
r_char
id|scratch
(braket
l_int|1024
)braket
suffix:semicolon
r_struct
id|commit
op_star
id|commit
suffix:semicolon
id|prepare_revision_walk
c_func
(paren
id|rev
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|commit
op_assign
id|get_revision
c_func
(paren
id|rev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|author
op_assign
l_int|NULL
comma
op_star
id|oneline
comma
op_star
id|buffer
suffix:semicolon
r_int
id|authorlen
op_assign
id|authorlen
comma
id|onelinelen
suffix:semicolon
multiline_comment|/* get author and oneline */
r_for
c_loop
(paren
id|buffer
op_assign
id|commit-&gt;buffer
suffix:semicolon
id|buffer
op_logical_and
op_star
id|buffer
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
op_star
id|buffer
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)paren
(brace
r_char
op_star
id|eol
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eol
op_eq
l_int|NULL
)paren
id|eol
op_assign
id|buffer
op_plus
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_else
id|eol
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;author &quot;
comma
l_int|7
)paren
)paren
(brace
r_char
op_star
id|bracket
op_assign
id|strchr
c_func
(paren
id|buffer
comma
l_char|&squot;&lt;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bracket
op_eq
l_int|NULL
op_logical_or
id|bracket
OG
id|eol
)paren
id|die
c_func
(paren
l_string|&quot;Invalid commit buffer: %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_email
c_func
(paren
id|bracket
op_plus
l_int|1
comma
id|scratch
comma
r_sizeof
(paren
id|scratch
)paren
)paren
)paren
(brace
id|author
op_assign
id|scratch
suffix:semicolon
id|authorlen
op_assign
id|strlen
c_func
(paren
id|scratch
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|bracket
(braket
l_int|1
)braket
op_eq
l_char|&squot; &squot;
)paren
id|bracket
op_decrement
suffix:semicolon
id|author
op_assign
id|buffer
op_plus
l_int|7
suffix:semicolon
id|authorlen
op_assign
id|bracket
id|buffer
l_int|7
suffix:semicolon
)brace
)brace
id|buffer
op_assign
id|eol
suffix:semicolon
)brace
r_if
c_cond
(paren
id|author
op_eq
l_int|NULL
)paren
id|die
(paren
l_string|&quot;Missing author: %s&quot;
comma
id|sha1_to_hex
c_func
(paren
id|commit-&gt;object.sha1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
op_logical_or
op_star
id|buffer
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|oneline
op_assign
l_string|&quot;&lt;none&gt;&quot;
suffix:semicolon
id|onelinelen
op_assign
r_sizeof
(paren
id|oneline
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_char
op_star
id|eol
suffix:semicolon
id|oneline
op_assign
id|buffer
op_plus
l_int|1
suffix:semicolon
id|eol
op_assign
id|strchr
c_func
(paren
id|oneline
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eol
op_eq
l_int|NULL
)paren
id|onelinelen
op_assign
id|strlen
c_func
(paren
id|oneline
)paren
suffix:semicolon
r_else
id|onelinelen
op_assign
id|eol
id|oneline
suffix:semicolon
)brace
id|insert_author_oneline
c_func
(paren
id|list
comma
id|author
comma
id|authorlen
comma
id|oneline
comma
id|onelinelen
)paren
suffix:semicolon
)brace
)brace
DECL|function|cmd_shortlog
r_int
id|cmd_shortlog
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
id|prefix
)paren
(brace
r_struct
id|rev_info
id|rev
suffix:semicolon
r_struct
id|path_list
id|list
op_assign
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|sort_by_number
op_assign
l_int|0
comma
id|summary
op_assign
l_int|0
suffix:semicolon
id|init_revisions
c_func
(paren
op_amp
id|rev
comma
id|prefix
)paren
suffix:semicolon
id|argc
op_assign
id|setup_revisions
c_func
(paren
id|argc
comma
id|argv
comma
op_amp
id|rev
comma
l_int|NULL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argc
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-n&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--numbered&quot;
)paren
)paren
id|sort_by_number
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-s&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--summary&quot;
)paren
)paren
id|summary
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-h&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;--help&quot;
)paren
)paren
id|usage
c_func
(paren
id|shortlog_usage
)paren
suffix:semicolon
r_else
id|die
(paren
l_string|&quot;unrecognized argument: %s&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|argc
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rev.pending.nr
op_eq
l_int|1
)paren
id|die
(paren
l_string|&quot;Need a range!&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rev.pending.nr
op_eq
l_int|0
)paren
id|read_from_stdin
c_func
(paren
op_amp
id|list
)paren
suffix:semicolon
r_else
id|get_from_rev
c_func
(paren
op_amp
id|rev
comma
op_amp
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sort_by_number
)paren
id|qsort
c_func
(paren
id|list.items
comma
r_sizeof
(paren
r_struct
id|path_list_item
)paren
comma
id|list.nr
comma
id|compare_by_number
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
id|list.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|path_list
op_star
id|onelines
op_assign
id|list.items
(braket
id|i
)braket
dot
id|util
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s (%d):&bslash;n&quot;
comma
id|list.items
(braket
id|i
)braket
dot
id|path
comma
id|onelines-&gt;nr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|summary
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
id|onelines-&gt;nr
l_int|1
suffix:semicolon
id|j
op_ge
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
id|printf
c_func
(paren
l_string|&quot;      %s&bslash;n&quot;
comma
id|onelines-&gt;items
(braket
id|j
)braket
dot
id|path
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|onelines-&gt;strdup_paths
op_assign
l_int|1
suffix:semicolon
id|path_list_clear
c_func
(paren
id|onelines
comma
l_int|1
)paren
suffix:semicolon
id|free
c_func
(paren
id|onelines
)paren
suffix:semicolon
id|list.items
(braket
id|i
)braket
dot
id|util
op_assign
l_int|NULL
suffix:semicolon
)brace
id|list.strdup_paths
op_assign
l_int|1
suffix:semicolon
id|path_list_clear
c_func
(paren
op_amp
id|list
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
