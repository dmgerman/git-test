macro_line|#include &quot;cache.h&quot;
macro_line|#include &quot;column.h&quot;
macro_line|#include &quot;string-list.h&quot;
macro_line|#include &quot;parse-options.h&quot;
macro_line|#include &quot;run-command.h&quot;
macro_line|#include &quot;utf8.h&quot;
DECL|macro|XY2LINEAR
mdefine_line|#define XY2LINEAR(d, x, y) (COL_LAYOUT((d)-&gt;colopts) == COL_COLUMN ? &bslash;&n;&t;&t;&t;    (x) * (d)-&gt;rows + (y) : &bslash;&n;&t;&t;&t;    (y) * (d)-&gt;cols + (x))
DECL|struct|column_data
r_struct
id|column_data
(brace
DECL|member|list
r_const
r_struct
id|string_list
op_star
id|list
suffix:semicolon
DECL|member|colopts
r_int
r_int
id|colopts
suffix:semicolon
DECL|member|opts
r_struct
id|column_options
id|opts
suffix:semicolon
DECL|member|rows
DECL|member|cols
r_int
id|rows
comma
id|cols
suffix:semicolon
DECL|member|len
r_int
op_star
id|len
suffix:semicolon
multiline_comment|/* cell length */
DECL|member|width
r_int
op_star
id|width
suffix:semicolon
multiline_comment|/* index to the longest row in column */
)brace
suffix:semicolon
multiline_comment|/* return length of &squot;s&squot; in letters, ANSI escapes stripped */
DECL|function|item_length
r_static
r_int
id|item_length
c_func
(paren
r_int
r_int
id|colopts
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|len
comma
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|strbuf
id|str
op_assign
id|STRBUF_INIT
suffix:semicolon
id|strbuf_addstr
c_func
(paren
op_amp
id|str
comma
id|s
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|s
op_assign
id|strstr
c_func
(paren
id|str.buf
op_plus
id|i
comma
l_string|&quot;&bslash;033[&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|len
op_assign
id|strspn
c_func
(paren
id|s
op_plus
l_int|2
comma
l_string|&quot;0123456789;&quot;
)paren
suffix:semicolon
id|i
op_assign
id|s
id|str.buf
suffix:semicolon
id|strbuf_remove
c_func
(paren
op_amp
id|str
comma
id|i
comma
id|len
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* &bslash;033[&lt;len&gt;&lt;func char&gt; */
)brace
id|len
op_assign
id|utf8_strwidth
c_func
(paren
id|str.buf
)paren
suffix:semicolon
id|strbuf_release
c_func
(paren
op_amp
id|str
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Calculate cell width, rows and cols for a table of equal cells, given&n; * table width and how many spaces between cells.&n; */
DECL|function|layout
r_static
r_void
id|layout
c_func
(paren
r_struct
id|column_data
op_star
id|data
comma
r_int
op_star
id|width
)paren
(brace
r_int
id|i
suffix:semicolon
op_star
id|width
op_assign
l_int|0
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
id|data-&gt;list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_star
id|width
OL
id|data-&gt;len
(braket
id|i
)braket
)paren
op_star
id|width
op_assign
id|data-&gt;len
(braket
id|i
)braket
suffix:semicolon
op_star
id|width
op_add_assign
id|data-&gt;opts.padding
suffix:semicolon
id|data-&gt;cols
op_assign
(paren
id|data-&gt;opts.width
id|strlen
c_func
(paren
id|data-&gt;opts.indent
)paren
)paren
op_div
op_star
id|width
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;cols
op_eq
l_int|0
)paren
id|data-&gt;cols
op_assign
l_int|1
suffix:semicolon
id|data-&gt;rows
op_assign
id|DIV_ROUND_UP
c_func
(paren
id|data-&gt;list-&gt;nr
comma
id|data-&gt;cols
)paren
suffix:semicolon
)brace
DECL|function|compute_column_width
r_static
r_void
id|compute_column_width
c_func
(paren
r_struct
id|column_data
op_star
id|data
)paren
(brace
r_int
id|i
comma
id|x
comma
id|y
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|data-&gt;cols
suffix:semicolon
id|x
op_increment
)paren
(brace
id|data-&gt;width
(braket
id|x
)braket
op_assign
id|XY2LINEAR
c_func
(paren
id|data
comma
id|x
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|y
op_assign
l_int|0
suffix:semicolon
id|y
OL
id|data-&gt;rows
suffix:semicolon
id|y
op_increment
)paren
(brace
id|i
op_assign
id|XY2LINEAR
c_func
(paren
id|data
comma
id|x
comma
id|y
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|data-&gt;list-&gt;nr
op_logical_and
id|data-&gt;len
(braket
id|data-&gt;width
(braket
id|x
)braket
)braket
OL
id|data-&gt;len
(braket
id|i
)braket
)paren
id|data-&gt;width
(braket
id|x
)braket
op_assign
id|i
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Shrink all columns by shortening them one row each time (and adding&n; * more columns along the way). Hopefully the longest cell will be&n; * moved to the next column, column is shrunk so we have more space&n; * for new columns. The process ends when the whole thing no longer&n; * fits in data-&gt;total_width.&n; */
DECL|function|shrink_columns
r_static
r_void
id|shrink_columns
c_func
(paren
r_struct
id|column_data
op_star
id|data
)paren
(brace
id|data-&gt;width
op_assign
id|xrealloc
c_func
(paren
id|data-&gt;width
comma
r_sizeof
(paren
op_star
id|data-&gt;width
)paren
op_star
id|data-&gt;cols
)paren
suffix:semicolon
r_while
c_loop
(paren
id|data-&gt;rows
OG
l_int|1
)paren
(brace
r_int
id|x
comma
id|total_width
comma
id|cols
comma
id|rows
suffix:semicolon
id|rows
op_assign
id|data-&gt;rows
suffix:semicolon
id|cols
op_assign
id|data-&gt;cols
suffix:semicolon
id|data-&gt;rows
op_decrement
suffix:semicolon
id|data-&gt;cols
op_assign
id|DIV_ROUND_UP
c_func
(paren
id|data-&gt;list-&gt;nr
comma
id|data-&gt;rows
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;cols
op_ne
id|cols
)paren
id|data-&gt;width
op_assign
id|xrealloc
c_func
(paren
id|data-&gt;width
comma
r_sizeof
(paren
op_star
id|data-&gt;width
)paren
op_star
id|data-&gt;cols
)paren
suffix:semicolon
id|compute_column_width
c_func
(paren
id|data
)paren
suffix:semicolon
id|total_width
op_assign
id|strlen
c_func
(paren
id|data-&gt;opts.indent
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|data-&gt;cols
suffix:semicolon
id|x
op_increment
)paren
(brace
id|total_width
op_add_assign
id|data-&gt;len
(braket
id|data-&gt;width
(braket
id|x
)braket
)braket
suffix:semicolon
id|total_width
op_add_assign
id|data-&gt;opts.padding
suffix:semicolon
)brace
r_if
c_cond
(paren
id|total_width
OG
id|data-&gt;opts.width
)paren
(brace
id|data-&gt;rows
op_assign
id|rows
suffix:semicolon
id|data-&gt;cols
op_assign
id|cols
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|compute_column_width
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/* Display without layout when not enabled */
DECL|function|display_plain
r_static
r_void
id|display_plain
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|list
comma
r_const
r_char
op_star
id|indent
comma
r_const
r_char
op_star
id|nl
)paren
(brace
r_int
id|i
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
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot;%s%s%s&quot;
comma
id|indent
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
comma
id|nl
)paren
suffix:semicolon
)brace
multiline_comment|/* Print a cell to stdout with all necessary leading/traling space */
DECL|function|display_cell
r_static
r_int
id|display_cell
c_func
(paren
r_struct
id|column_data
op_star
id|data
comma
r_int
id|initial_width
comma
r_const
r_char
op_star
id|empty_cell
comma
r_int
id|x
comma
r_int
id|y
)paren
(brace
r_int
id|i
comma
id|len
comma
id|newline
suffix:semicolon
id|i
op_assign
id|XY2LINEAR
c_func
(paren
id|data
comma
id|x
comma
id|y
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|data-&gt;list-&gt;nr
)paren
r_return
l_int|1
suffix:semicolon
id|len
op_assign
id|data-&gt;len
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;width
op_logical_and
id|data-&gt;len
(braket
id|data-&gt;width
(braket
id|x
)braket
)braket
OL
id|initial_width
)paren
(brace
multiline_comment|/*&n;&t;&t; * empty_cell has initial_width chars, if real column&n;&t;&t; * is narrower, increase len a bit so we fill less&n;&t;&t; * space.&n;&t;&t; */
id|len
op_add_assign
id|initial_width
id|data-&gt;len
(braket
id|data-&gt;width
(braket
id|x
)braket
)braket
suffix:semicolon
id|len
op_sub_assign
id|data-&gt;opts.padding
suffix:semicolon
)brace
r_if
c_cond
(paren
id|COL_LAYOUT
c_func
(paren
id|data-&gt;colopts
)paren
op_eq
id|COL_COLUMN
)paren
id|newline
op_assign
id|i
op_plus
id|data-&gt;rows
op_ge
id|data-&gt;list-&gt;nr
suffix:semicolon
r_else
id|newline
op_assign
id|x
op_eq
id|data-&gt;cols
l_int|1
op_logical_or
id|i
op_eq
id|data-&gt;list-&gt;nr
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s%s%s&quot;
comma
id|x
op_eq
l_int|0
ques
c_cond
id|data-&gt;opts.indent
suffix:colon
l_string|&quot;&quot;
comma
id|data-&gt;list-&gt;items
(braket
id|i
)braket
dot
id|string
comma
id|newline
ques
c_cond
id|data-&gt;opts.nl
suffix:colon
id|empty_cell
op_plus
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Display COL_COLUMN or COL_ROW */
DECL|function|display_table
r_static
r_void
id|display_table
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|list
comma
r_int
r_int
id|colopts
comma
r_const
r_struct
id|column_options
op_star
id|opts
)paren
(brace
r_struct
id|column_data
id|data
suffix:semicolon
r_int
id|x
comma
id|y
comma
id|i
comma
id|initial_width
suffix:semicolon
r_char
op_star
id|empty_cell
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|data.list
op_assign
id|list
suffix:semicolon
id|data.colopts
op_assign
id|colopts
suffix:semicolon
id|data.opts
op_assign
op_star
id|opts
suffix:semicolon
id|data.len
op_assign
id|xmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data.len
)paren
op_star
id|list-&gt;nr
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
id|list-&gt;nr
suffix:semicolon
id|i
op_increment
)paren
id|data.len
(braket
id|i
)braket
op_assign
id|item_length
c_func
(paren
id|colopts
comma
id|list-&gt;items
(braket
id|i
)braket
dot
id|string
)paren
suffix:semicolon
id|layout
c_func
(paren
op_amp
id|data
comma
op_amp
id|initial_width
)paren
suffix:semicolon
r_if
c_cond
(paren
id|colopts
op_amp
id|COL_DENSE
)paren
id|shrink_columns
c_func
(paren
op_amp
id|data
)paren
suffix:semicolon
id|empty_cell
op_assign
id|xmalloc
c_func
(paren
id|initial_width
op_plus
l_int|1
)paren
suffix:semicolon
id|memset
c_func
(paren
id|empty_cell
comma
l_char|&squot; &squot;
comma
id|initial_width
)paren
suffix:semicolon
id|empty_cell
(braket
id|initial_width
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
id|y
op_assign
l_int|0
suffix:semicolon
id|y
OL
id|data.rows
suffix:semicolon
id|y
op_increment
)paren
(brace
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|data.cols
suffix:semicolon
id|x
op_increment
)paren
r_if
c_cond
(paren
id|display_cell
c_func
(paren
op_amp
id|data
comma
id|initial_width
comma
id|empty_cell
comma
id|x
comma
id|y
)paren
)paren
r_break
suffix:semicolon
)brace
id|free
c_func
(paren
id|data.len
)paren
suffix:semicolon
id|free
c_func
(paren
id|data.width
)paren
suffix:semicolon
id|free
c_func
(paren
id|empty_cell
)paren
suffix:semicolon
)brace
DECL|function|print_columns
r_void
id|print_columns
c_func
(paren
r_const
r_struct
id|string_list
op_star
id|list
comma
r_int
r_int
id|colopts
comma
r_const
r_struct
id|column_options
op_star
id|opts
)paren
(brace
r_struct
id|column_options
id|nopts
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;nr
)paren
r_return
suffix:semicolon
m_assert
(paren
(paren
id|colopts
op_amp
id|COL_ENABLE_MASK
)paren
op_ne
id|COL_AUTO
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|nopts
comma
l_int|0
comma
r_sizeof
(paren
id|nopts
)paren
)paren
suffix:semicolon
id|nopts.indent
op_assign
id|opts
op_logical_and
id|opts-&gt;indent
ques
c_cond
id|opts-&gt;indent
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
id|nopts.nl
op_assign
id|opts
op_logical_and
id|opts-&gt;nl
ques
c_cond
id|opts-&gt;nl
suffix:colon
l_string|&quot;&bslash;n&quot;
suffix:semicolon
id|nopts.padding
op_assign
id|opts
ques
c_cond
id|opts-&gt;padding
suffix:colon
l_int|1
suffix:semicolon
id|nopts.width
op_assign
id|opts
op_logical_and
id|opts-&gt;width
ques
c_cond
id|opts-&gt;width
suffix:colon
id|term_columns
c_func
(paren
)paren
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|column_active
c_func
(paren
id|colopts
)paren
)paren
(brace
id|display_plain
c_func
(paren
id|list
comma
l_string|&quot;&quot;
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|COL_LAYOUT
c_func
(paren
id|colopts
)paren
)paren
(brace
r_case
id|COL_PLAIN
suffix:colon
id|display_plain
c_func
(paren
id|list
comma
id|nopts.indent
comma
id|nopts.nl
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COL_ROW
suffix:colon
r_case
id|COL_COLUMN
suffix:colon
id|display_table
c_func
(paren
id|list
comma
id|colopts
comma
op_amp
id|nopts
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|die
c_func
(paren
l_string|&quot;BUG: invalid layout mode %d&quot;
comma
id|COL_LAYOUT
c_func
(paren
id|colopts
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|finalize_colopts
r_int
id|finalize_colopts
c_func
(paren
r_int
r_int
op_star
id|colopts
comma
r_int
id|stdout_is_tty
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|colopts
op_amp
id|COL_ENABLE_MASK
)paren
op_eq
id|COL_AUTO
)paren
(brace
r_if
c_cond
(paren
id|stdout_is_tty
OL
l_int|0
)paren
id|stdout_is_tty
op_assign
id|isatty
c_func
(paren
l_int|1
)paren
suffix:semicolon
op_star
id|colopts
op_and_assign
op_complement
id|COL_ENABLE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|stdout_is_tty
)paren
op_star
id|colopts
op_or_assign
id|COL_ENABLED
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|struct|colopt
r_struct
id|colopt
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LAYOUT_SET
mdefine_line|#define LAYOUT_SET 1
DECL|macro|ENABLE_SET
mdefine_line|#define ENABLE_SET 2
DECL|function|parse_option
r_static
r_int
id|parse_option
c_func
(paren
r_const
r_char
op_star
id|arg
comma
r_int
id|len
comma
r_int
r_int
op_star
id|colopts
comma
r_int
op_star
id|group_set
)paren
(brace
r_struct
id|colopt
id|opts
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;always&quot;
comma
id|COL_ENABLED
comma
id|COL_ENABLE_MASK
)brace
comma
(brace
l_string|&quot;never&quot;
comma
id|COL_DISABLED
comma
id|COL_ENABLE_MASK
)brace
comma
(brace
l_string|&quot;auto&quot;
comma
id|COL_AUTO
comma
id|COL_ENABLE_MASK
)brace
comma
(brace
l_string|&quot;plain&quot;
comma
id|COL_PLAIN
comma
id|COL_LAYOUT_MASK
)brace
comma
(brace
l_string|&quot;column&quot;
comma
id|COL_COLUMN
comma
id|COL_LAYOUT_MASK
)brace
comma
(brace
l_string|&quot;row&quot;
comma
id|COL_ROW
comma
id|COL_LAYOUT_MASK
)brace
comma
(brace
l_string|&quot;dense&quot;
comma
id|COL_DENSE
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
r_int
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|opts
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|set
op_assign
l_int|1
comma
id|arg_len
op_assign
id|len
comma
id|name_len
suffix:semicolon
r_const
r_char
op_star
id|arg_str
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts
(braket
id|i
)braket
dot
id|mask
)paren
(brace
r_if
c_cond
(paren
id|arg_len
OG
l_int|2
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|arg_str
comma
l_string|&quot;no&quot;
comma
l_int|2
)paren
)paren
(brace
id|arg_str
op_add_assign
l_int|2
suffix:semicolon
id|arg_len
op_sub_assign
l_int|2
suffix:semicolon
id|set
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|name_len
op_assign
id|strlen
c_func
(paren
id|opts
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg_len
op_ne
id|name_len
op_logical_or
id|strncmp
c_func
(paren
id|arg_str
comma
id|opts
(braket
id|i
)braket
dot
id|name
comma
id|name_len
)paren
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|opts
(braket
id|i
)braket
dot
id|mask
)paren
(brace
r_case
id|COL_ENABLE_MASK
suffix:colon
op_star
id|group_set
op_or_assign
id|ENABLE_SET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COL_LAYOUT_MASK
suffix:colon
op_star
id|group_set
op_or_assign
id|LAYOUT_SET
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|opts
(braket
id|i
)braket
dot
id|mask
)paren
op_star
id|colopts
op_assign
(paren
op_star
id|colopts
op_amp
op_complement
id|opts
(braket
id|i
)braket
dot
id|mask
)paren
op_or
id|opts
(braket
id|i
)braket
dot
id|value
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|set
)paren
op_star
id|colopts
op_or_assign
id|opts
(braket
id|i
)braket
dot
id|value
suffix:semicolon
r_else
op_star
id|colopts
op_and_assign
op_complement
id|opts
(braket
id|i
)braket
dot
id|value
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|error
c_func
(paren
l_string|&quot;unsupported option &squot;%s&squot;&quot;
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|parse_config
r_static
r_int
id|parse_config
c_func
(paren
r_int
r_int
op_star
id|colopts
comma
r_const
r_char
op_star
id|value
)paren
(brace
r_const
r_char
op_star
id|sep
op_assign
l_string|&quot; ,&quot;
suffix:semicolon
r_int
id|group_set
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|value
)paren
(brace
r_int
id|len
op_assign
id|strcspn
c_func
(paren
id|value
comma
id|sep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
id|parse_option
c_func
(paren
id|value
comma
id|len
comma
id|colopts
comma
op_amp
id|group_set
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|value
op_add_assign
id|len
suffix:semicolon
)brace
id|value
op_add_assign
id|strspn
c_func
(paren
id|value
comma
id|sep
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If none of &quot;always&quot;, &quot;never&quot;, and &quot;auto&quot; is specified, then setting&n;&t; * layout implies &quot;always&quot;.&n;&t; *&n;&t; * Current value in COL_ENABLE_MASK is disregarded. This means if&n;&t; * you set column.ui = auto and pass --column=row, then &quot;auto&quot;&n;&t; * will become &quot;always&quot;.&n;&t; */
r_if
c_cond
(paren
(paren
id|group_set
op_amp
id|LAYOUT_SET
)paren
op_logical_and
op_logical_neg
(paren
id|group_set
op_amp
id|ENABLE_SET
)paren
)paren
op_star
id|colopts
op_assign
(paren
op_star
id|colopts
op_amp
op_complement
id|COL_ENABLE_MASK
)paren
op_or
id|COL_ENABLED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|column_config
r_static
r_int
id|column_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_const
r_char
op_star
id|key
comma
r_int
r_int
op_star
id|colopts
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_return
id|config_error_nonbool
c_func
(paren
id|var
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parse_config
c_func
(paren
id|colopts
comma
id|value
)paren
)paren
r_return
id|error
c_func
(paren
l_string|&quot;invalid column.%s mode %s&quot;
comma
id|key
comma
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|git_column_config
r_int
id|git_column_config
c_func
(paren
r_const
r_char
op_star
id|var
comma
r_const
r_char
op_star
id|value
comma
r_const
r_char
op_star
id|command
comma
r_int
r_int
op_star
id|colopts
)paren
(brace
r_const
r_char
op_star
id|it
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skip_prefix
c_func
(paren
id|var
comma
l_string|&quot;column.&quot;
comma
op_amp
id|it
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|it
comma
l_string|&quot;ui&quot;
)paren
)paren
r_return
id|column_config
c_func
(paren
id|var
comma
id|value
comma
l_string|&quot;ui&quot;
comma
id|colopts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|command
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|it
comma
id|command
)paren
)paren
r_return
id|column_config
c_func
(paren
id|var
comma
id|value
comma
id|it
comma
id|colopts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parseopt_column_callback
r_int
id|parseopt_column_callback
c_func
(paren
r_const
r_struct
id|option
op_star
id|opt
comma
r_const
r_char
op_star
id|arg
comma
r_int
id|unset
)paren
(brace
r_int
r_int
op_star
id|colopts
op_assign
id|opt-&gt;value
suffix:semicolon
op_star
id|colopts
op_or_assign
id|COL_PARSEOPT
suffix:semicolon
op_star
id|colopts
op_and_assign
op_complement
id|COL_ENABLE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|unset
)paren
multiline_comment|/* --no-column == never */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* --column == always unless &quot;arg&quot; states otherwise */
op_star
id|colopts
op_or_assign
id|COL_ENABLED
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
r_return
id|parse_config
c_func
(paren
id|colopts
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|fd_out
r_static
r_int
id|fd_out
op_assign
l_int|1
suffix:semicolon
DECL|variable|column_process
r_static
r_struct
id|child_process
id|column_process
op_assign
id|CHILD_PROCESS_INIT
suffix:semicolon
DECL|function|run_column_filter
r_int
id|run_column_filter
c_func
(paren
r_int
id|colopts
comma
r_const
r_struct
id|column_options
op_star
id|opts
)paren
(brace
r_struct
id|argv_array
op_star
id|argv
suffix:semicolon
r_if
c_cond
(paren
id|fd_out
op_ne
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|column_process
comma
l_int|0
comma
r_sizeof
(paren
id|column_process
)paren
)paren
suffix:semicolon
id|argv
op_assign
op_amp
id|column_process.args
suffix:semicolon
id|argv_array_push
c_func
(paren
id|argv
comma
l_string|&quot;column&quot;
)paren
suffix:semicolon
id|argv_array_pushf
c_func
(paren
id|argv
comma
l_string|&quot;--raw-mode=%d&quot;
comma
id|colopts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts
op_logical_and
id|opts-&gt;width
)paren
id|argv_array_pushf
c_func
(paren
id|argv
comma
l_string|&quot;--width=%d&quot;
comma
id|opts-&gt;width
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts
op_logical_and
id|opts-&gt;indent
)paren
id|argv_array_pushf
c_func
(paren
id|argv
comma
l_string|&quot;--indent=%s&quot;
comma
id|opts-&gt;indent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opts
op_logical_and
id|opts-&gt;padding
)paren
id|argv_array_pushf
c_func
(paren
id|argv
comma
l_string|&quot;--padding=%d&quot;
comma
id|opts-&gt;padding
)paren
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|column_process.in
op_assign
l_int|1
suffix:semicolon
id|column_process.out
op_assign
id|dup
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|column_process.git_cmd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start_command
c_func
(paren
op_amp
id|column_process
)paren
)paren
r_return
l_int|2
suffix:semicolon
id|fd_out
op_assign
id|dup
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|column_process.in
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|column_process.in
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|stop_column_filter
r_int
id|stop_column_filter
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|fd_out
op_eq
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|finish_command
c_func
(paren
op_amp
id|column_process
)paren
suffix:semicolon
id|dup2
c_func
(paren
id|fd_out
comma
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd_out
)paren
suffix:semicolon
id|fd_out
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
