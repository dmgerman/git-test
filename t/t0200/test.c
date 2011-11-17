multiline_comment|/* This is a phony C program that&squot;s only here to test xgettext message extraction */
DECL|variable|help
r_const
r_char
id|help
(braket
)braket
op_assign
multiline_comment|/* TRANSLATORS: This is a test. You don&squot;t need to translate it. */
id|N_
c_func
(paren
l_string|&quot;See &squot;git help COMMAND&squot; for more information on a specific command.&quot;
)paren
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* TRANSLATORS: This is a test. You don&squot;t need to translate it. */
id|puts
c_func
(paren
id|_
c_func
(paren
l_string|&quot;TEST: A C test string&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* TRANSLATORS: This is a test. You don&squot;t need to translate it. */
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;TEST: A C test string %s&quot;
)paren
comma
l_string|&quot;variable&quot;
)paren
suffix:semicolon
multiline_comment|/* TRANSLATORS: This is a test. You don&squot;t need to translate it. */
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;TEST: Hello World!&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* TRANSLATORS: This is a test. You don&squot;t need to translate it. */
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;TEST: Old English Runes&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* TRANSLATORS: This is a test. You don&squot;t need to translate it. */
id|printf
c_func
(paren
id|_
c_func
(paren
l_string|&quot;TEST: &lsquo;single&rsquo; and &ldquo;double&rdquo; quotes&quot;
)paren
)paren
suffix:semicolon
)brace
eof
