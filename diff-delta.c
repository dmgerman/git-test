multiline_comment|/*&n; * diff-delta.c: generate a delta between two buffers&n; *&n; * This code was greatly inspired by parts of LibXDiff from Davide Libenzi&n; * http://www.xmailserver.org/xdiff-lib.html&n; *&n; * Rewritten for GIT by Nicolas Pitre &lt;nico@fluxnic.net&gt;, (C) 2005-2007&n; *&n; * This code is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &quot;git-compat-util.h&quot;
macro_line|#include &quot;delta.h&quot;
multiline_comment|/* maximum hash entry list for the same hash bucket */
DECL|macro|HASH_LIMIT
mdefine_line|#define HASH_LIMIT 64
DECL|macro|RABIN_SHIFT
mdefine_line|#define RABIN_SHIFT 23
DECL|macro|RABIN_WINDOW
mdefine_line|#define RABIN_WINDOW 16
DECL|variable|T
r_static
r_const
r_int
r_int
id|T
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00000000
comma
l_int|0xab59b4d1
comma
l_int|0x56b369a2
comma
l_int|0xfdeadd73
comma
l_int|0x063f6795
comma
l_int|0xad66d344
comma
l_int|0x508c0e37
comma
l_int|0xfbd5bae6
comma
l_int|0x0c7ecf2a
comma
l_int|0xa7277bfb
comma
l_int|0x5acda688
comma
l_int|0xf1941259
comma
l_int|0x0a41a8bf
comma
l_int|0xa1181c6e
comma
l_int|0x5cf2c11d
comma
l_int|0xf7ab75cc
comma
l_int|0x18fd9e54
comma
l_int|0xb3a42a85
comma
l_int|0x4e4ef7f6
comma
l_int|0xe5174327
comma
l_int|0x1ec2f9c1
comma
l_int|0xb59b4d10
comma
l_int|0x48719063
comma
l_int|0xe32824b2
comma
l_int|0x1483517e
comma
l_int|0xbfdae5af
comma
l_int|0x423038dc
comma
l_int|0xe9698c0d
comma
l_int|0x12bc36eb
comma
l_int|0xb9e5823a
comma
l_int|0x440f5f49
comma
l_int|0xef56eb98
comma
l_int|0x31fb3ca8
comma
l_int|0x9aa28879
comma
l_int|0x6748550a
comma
l_int|0xcc11e1db
comma
l_int|0x37c45b3d
comma
l_int|0x9c9defec
comma
l_int|0x6177329f
comma
l_int|0xca2e864e
comma
l_int|0x3d85f382
comma
l_int|0x96dc4753
comma
l_int|0x6b369a20
comma
l_int|0xc06f2ef1
comma
l_int|0x3bba9417
comma
l_int|0x90e320c6
comma
l_int|0x6d09fdb5
comma
l_int|0xc6504964
comma
l_int|0x2906a2fc
comma
l_int|0x825f162d
comma
l_int|0x7fb5cb5e
comma
l_int|0xd4ec7f8f
comma
l_int|0x2f39c569
comma
l_int|0x846071b8
comma
l_int|0x798aaccb
comma
l_int|0xd2d3181a
comma
l_int|0x25786dd6
comma
l_int|0x8e21d907
comma
l_int|0x73cb0474
comma
l_int|0xd892b0a5
comma
l_int|0x23470a43
comma
l_int|0x881ebe92
comma
l_int|0x75f463e1
comma
l_int|0xdeadd730
comma
l_int|0x63f67950
comma
l_int|0xc8afcd81
comma
l_int|0x354510f2
comma
l_int|0x9e1ca423
comma
l_int|0x65c91ec5
comma
l_int|0xce90aa14
comma
l_int|0x337a7767
comma
l_int|0x9823c3b6
comma
l_int|0x6f88b67a
comma
l_int|0xc4d102ab
comma
l_int|0x393bdfd8
comma
l_int|0x92626b09
comma
l_int|0x69b7d1ef
comma
l_int|0xc2ee653e
comma
l_int|0x3f04b84d
comma
l_int|0x945d0c9c
comma
l_int|0x7b0be704
comma
l_int|0xd05253d5
comma
l_int|0x2db88ea6
comma
l_int|0x86e13a77
comma
l_int|0x7d348091
comma
l_int|0xd66d3440
comma
l_int|0x2b87e933
comma
l_int|0x80de5de2
comma
l_int|0x7775282e
comma
l_int|0xdc2c9cff
comma
l_int|0x21c6418c
comma
l_int|0x8a9ff55d
comma
l_int|0x714a4fbb
comma
l_int|0xda13fb6a
comma
l_int|0x27f92619
comma
l_int|0x8ca092c8
comma
l_int|0x520d45f8
comma
l_int|0xf954f129
comma
l_int|0x04be2c5a
comma
l_int|0xafe7988b
comma
l_int|0x5432226d
comma
l_int|0xff6b96bc
comma
l_int|0x02814bcf
comma
l_int|0xa9d8ff1e
comma
l_int|0x5e738ad2
comma
l_int|0xf52a3e03
comma
l_int|0x08c0e370
comma
l_int|0xa39957a1
comma
l_int|0x584ced47
comma
l_int|0xf3155996
comma
l_int|0x0eff84e5
comma
l_int|0xa5a63034
comma
l_int|0x4af0dbac
comma
l_int|0xe1a96f7d
comma
l_int|0x1c43b20e
comma
l_int|0xb71a06df
comma
l_int|0x4ccfbc39
comma
l_int|0xe79608e8
comma
l_int|0x1a7cd59b
comma
l_int|0xb125614a
comma
l_int|0x468e1486
comma
l_int|0xedd7a057
comma
l_int|0x103d7d24
comma
l_int|0xbb64c9f5
comma
l_int|0x40b17313
comma
l_int|0xebe8c7c2
comma
l_int|0x16021ab1
comma
l_int|0xbd5bae60
comma
l_int|0x6cb54671
comma
l_int|0xc7ecf2a0
comma
l_int|0x3a062fd3
comma
l_int|0x915f9b02
comma
l_int|0x6a8a21e4
comma
l_int|0xc1d39535
comma
l_int|0x3c394846
comma
l_int|0x9760fc97
comma
l_int|0x60cb895b
comma
l_int|0xcb923d8a
comma
l_int|0x3678e0f9
comma
l_int|0x9d215428
comma
l_int|0x66f4eece
comma
l_int|0xcdad5a1f
comma
l_int|0x3047876c
comma
l_int|0x9b1e33bd
comma
l_int|0x7448d825
comma
l_int|0xdf116cf4
comma
l_int|0x22fbb187
comma
l_int|0x89a20556
comma
l_int|0x7277bfb0
comma
l_int|0xd92e0b61
comma
l_int|0x24c4d612
comma
l_int|0x8f9d62c3
comma
l_int|0x7836170f
comma
l_int|0xd36fa3de
comma
l_int|0x2e857ead
comma
l_int|0x85dcca7c
comma
l_int|0x7e09709a
comma
l_int|0xd550c44b
comma
l_int|0x28ba1938
comma
l_int|0x83e3ade9
comma
l_int|0x5d4e7ad9
comma
l_int|0xf617ce08
comma
l_int|0x0bfd137b
comma
l_int|0xa0a4a7aa
comma
l_int|0x5b711d4c
comma
l_int|0xf028a99d
comma
l_int|0x0dc274ee
comma
l_int|0xa69bc03f
comma
l_int|0x5130b5f3
comma
l_int|0xfa690122
comma
l_int|0x0783dc51
comma
l_int|0xacda6880
comma
l_int|0x570fd266
comma
l_int|0xfc5666b7
comma
l_int|0x01bcbbc4
comma
l_int|0xaae50f15
comma
l_int|0x45b3e48d
comma
l_int|0xeeea505c
comma
l_int|0x13008d2f
comma
l_int|0xb85939fe
comma
l_int|0x438c8318
comma
l_int|0xe8d537c9
comma
l_int|0x153feaba
comma
l_int|0xbe665e6b
comma
l_int|0x49cd2ba7
comma
l_int|0xe2949f76
comma
l_int|0x1f7e4205
comma
l_int|0xb427f6d4
comma
l_int|0x4ff24c32
comma
l_int|0xe4abf8e3
comma
l_int|0x19412590
comma
l_int|0xb2189141
comma
l_int|0x0f433f21
comma
l_int|0xa41a8bf0
comma
l_int|0x59f05683
comma
l_int|0xf2a9e252
comma
l_int|0x097c58b4
comma
l_int|0xa225ec65
comma
l_int|0x5fcf3116
comma
l_int|0xf49685c7
comma
l_int|0x033df00b
comma
l_int|0xa86444da
comma
l_int|0x558e99a9
comma
l_int|0xfed72d78
comma
l_int|0x0502979e
comma
l_int|0xae5b234f
comma
l_int|0x53b1fe3c
comma
l_int|0xf8e84aed
comma
l_int|0x17bea175
comma
l_int|0xbce715a4
comma
l_int|0x410dc8d7
comma
l_int|0xea547c06
comma
l_int|0x1181c6e0
comma
l_int|0xbad87231
comma
l_int|0x4732af42
comma
l_int|0xec6b1b93
comma
l_int|0x1bc06e5f
comma
l_int|0xb099da8e
comma
l_int|0x4d7307fd
comma
l_int|0xe62ab32c
comma
l_int|0x1dff09ca
comma
l_int|0xb6a6bd1b
comma
l_int|0x4b4c6068
comma
l_int|0xe015d4b9
comma
l_int|0x3eb80389
comma
l_int|0x95e1b758
comma
l_int|0x680b6a2b
comma
l_int|0xc352defa
comma
l_int|0x3887641c
comma
l_int|0x93ded0cd
comma
l_int|0x6e340dbe
comma
l_int|0xc56db96f
comma
l_int|0x32c6cca3
comma
l_int|0x999f7872
comma
l_int|0x6475a501
comma
l_int|0xcf2c11d0
comma
l_int|0x34f9ab36
comma
l_int|0x9fa01fe7
comma
l_int|0x624ac294
comma
l_int|0xc9137645
comma
l_int|0x26459ddd
comma
l_int|0x8d1c290c
comma
l_int|0x70f6f47f
comma
l_int|0xdbaf40ae
comma
l_int|0x207afa48
comma
l_int|0x8b234e99
comma
l_int|0x76c993ea
comma
l_int|0xdd90273b
comma
l_int|0x2a3b52f7
comma
l_int|0x8162e626
comma
l_int|0x7c883b55
comma
l_int|0xd7d18f84
comma
l_int|0x2c043562
comma
l_int|0x875d81b3
comma
l_int|0x7ab75cc0
comma
l_int|0xd1eee811
)brace
suffix:semicolon
DECL|variable|U
r_static
r_const
r_int
r_int
id|U
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00000000
comma
l_int|0x7eb5200d
comma
l_int|0x5633f4cb
comma
l_int|0x2886d4c6
comma
l_int|0x073e5d47
comma
l_int|0x798b7d4a
comma
l_int|0x510da98c
comma
l_int|0x2fb88981
comma
l_int|0x0e7cba8e
comma
l_int|0x70c99a83
comma
l_int|0x584f4e45
comma
l_int|0x26fa6e48
comma
l_int|0x0942e7c9
comma
l_int|0x77f7c7c4
comma
l_int|0x5f711302
comma
l_int|0x21c4330f
comma
l_int|0x1cf9751c
comma
l_int|0x624c5511
comma
l_int|0x4aca81d7
comma
l_int|0x347fa1da
comma
l_int|0x1bc7285b
comma
l_int|0x65720856
comma
l_int|0x4df4dc90
comma
l_int|0x3341fc9d
comma
l_int|0x1285cf92
comma
l_int|0x6c30ef9f
comma
l_int|0x44b63b59
comma
l_int|0x3a031b54
comma
l_int|0x15bb92d5
comma
l_int|0x6b0eb2d8
comma
l_int|0x4388661e
comma
l_int|0x3d3d4613
comma
l_int|0x39f2ea38
comma
l_int|0x4747ca35
comma
l_int|0x6fc11ef3
comma
l_int|0x11743efe
comma
l_int|0x3eccb77f
comma
l_int|0x40799772
comma
l_int|0x68ff43b4
comma
l_int|0x164a63b9
comma
l_int|0x378e50b6
comma
l_int|0x493b70bb
comma
l_int|0x61bda47d
comma
l_int|0x1f088470
comma
l_int|0x30b00df1
comma
l_int|0x4e052dfc
comma
l_int|0x6683f93a
comma
l_int|0x1836d937
comma
l_int|0x250b9f24
comma
l_int|0x5bbebf29
comma
l_int|0x73386bef
comma
l_int|0x0d8d4be2
comma
l_int|0x2235c263
comma
l_int|0x5c80e26e
comma
l_int|0x740636a8
comma
l_int|0x0ab316a5
comma
l_int|0x2b7725aa
comma
l_int|0x55c205a7
comma
l_int|0x7d44d161
comma
l_int|0x03f1f16c
comma
l_int|0x2c4978ed
comma
l_int|0x52fc58e0
comma
l_int|0x7a7a8c26
comma
l_int|0x04cfac2b
comma
l_int|0x73e5d470
comma
l_int|0x0d50f47d
comma
l_int|0x25d620bb
comma
l_int|0x5b6300b6
comma
l_int|0x74db8937
comma
l_int|0x0a6ea93a
comma
l_int|0x22e87dfc
comma
l_int|0x5c5d5df1
comma
l_int|0x7d996efe
comma
l_int|0x032c4ef3
comma
l_int|0x2baa9a35
comma
l_int|0x551fba38
comma
l_int|0x7aa733b9
comma
l_int|0x041213b4
comma
l_int|0x2c94c772
comma
l_int|0x5221e77f
comma
l_int|0x6f1ca16c
comma
l_int|0x11a98161
comma
l_int|0x392f55a7
comma
l_int|0x479a75aa
comma
l_int|0x6822fc2b
comma
l_int|0x1697dc26
comma
l_int|0x3e1108e0
comma
l_int|0x40a428ed
comma
l_int|0x61601be2
comma
l_int|0x1fd53bef
comma
l_int|0x3753ef29
comma
l_int|0x49e6cf24
comma
l_int|0x665e46a5
comma
l_int|0x18eb66a8
comma
l_int|0x306db26e
comma
l_int|0x4ed89263
comma
l_int|0x4a173e48
comma
l_int|0x34a21e45
comma
l_int|0x1c24ca83
comma
l_int|0x6291ea8e
comma
l_int|0x4d29630f
comma
l_int|0x339c4302
comma
l_int|0x1b1a97c4
comma
l_int|0x65afb7c9
comma
l_int|0x446b84c6
comma
l_int|0x3adea4cb
comma
l_int|0x1258700d
comma
l_int|0x6ced5000
comma
l_int|0x4355d981
comma
l_int|0x3de0f98c
comma
l_int|0x15662d4a
comma
l_int|0x6bd30d47
comma
l_int|0x56ee4b54
comma
l_int|0x285b6b59
comma
l_int|0x00ddbf9f
comma
l_int|0x7e689f92
comma
l_int|0x51d01613
comma
l_int|0x2f65361e
comma
l_int|0x07e3e2d8
comma
l_int|0x7956c2d5
comma
l_int|0x5892f1da
comma
l_int|0x2627d1d7
comma
l_int|0x0ea10511
comma
l_int|0x7014251c
comma
l_int|0x5facac9d
comma
l_int|0x21198c90
comma
l_int|0x099f5856
comma
l_int|0x772a785b
comma
l_int|0x4c921c31
comma
l_int|0x32273c3c
comma
l_int|0x1aa1e8fa
comma
l_int|0x6414c8f7
comma
l_int|0x4bac4176
comma
l_int|0x3519617b
comma
l_int|0x1d9fb5bd
comma
l_int|0x632a95b0
comma
l_int|0x42eea6bf
comma
l_int|0x3c5b86b2
comma
l_int|0x14dd5274
comma
l_int|0x6a687279
comma
l_int|0x45d0fbf8
comma
l_int|0x3b65dbf5
comma
l_int|0x13e30f33
comma
l_int|0x6d562f3e
comma
l_int|0x506b692d
comma
l_int|0x2ede4920
comma
l_int|0x06589de6
comma
l_int|0x78edbdeb
comma
l_int|0x5755346a
comma
l_int|0x29e01467
comma
l_int|0x0166c0a1
comma
l_int|0x7fd3e0ac
comma
l_int|0x5e17d3a3
comma
l_int|0x20a2f3ae
comma
l_int|0x08242768
comma
l_int|0x76910765
comma
l_int|0x59298ee4
comma
l_int|0x279caee9
comma
l_int|0x0f1a7a2f
comma
l_int|0x71af5a22
comma
l_int|0x7560f609
comma
l_int|0x0bd5d604
comma
l_int|0x235302c2
comma
l_int|0x5de622cf
comma
l_int|0x725eab4e
comma
l_int|0x0ceb8b43
comma
l_int|0x246d5f85
comma
l_int|0x5ad87f88
comma
l_int|0x7b1c4c87
comma
l_int|0x05a96c8a
comma
l_int|0x2d2fb84c
comma
l_int|0x539a9841
comma
l_int|0x7c2211c0
comma
l_int|0x029731cd
comma
l_int|0x2a11e50b
comma
l_int|0x54a4c506
comma
l_int|0x69998315
comma
l_int|0x172ca318
comma
l_int|0x3faa77de
comma
l_int|0x411f57d3
comma
l_int|0x6ea7de52
comma
l_int|0x1012fe5f
comma
l_int|0x38942a99
comma
l_int|0x46210a94
comma
l_int|0x67e5399b
comma
l_int|0x19501996
comma
l_int|0x31d6cd50
comma
l_int|0x4f63ed5d
comma
l_int|0x60db64dc
comma
l_int|0x1e6e44d1
comma
l_int|0x36e89017
comma
l_int|0x485db01a
comma
l_int|0x3f77c841
comma
l_int|0x41c2e84c
comma
l_int|0x69443c8a
comma
l_int|0x17f11c87
comma
l_int|0x38499506
comma
l_int|0x46fcb50b
comma
l_int|0x6e7a61cd
comma
l_int|0x10cf41c0
comma
l_int|0x310b72cf
comma
l_int|0x4fbe52c2
comma
l_int|0x67388604
comma
l_int|0x198da609
comma
l_int|0x36352f88
comma
l_int|0x48800f85
comma
l_int|0x6006db43
comma
l_int|0x1eb3fb4e
comma
l_int|0x238ebd5d
comma
l_int|0x5d3b9d50
comma
l_int|0x75bd4996
comma
l_int|0x0b08699b
comma
l_int|0x24b0e01a
comma
l_int|0x5a05c017
comma
l_int|0x728314d1
comma
l_int|0x0c3634dc
comma
l_int|0x2df207d3
comma
l_int|0x534727de
comma
l_int|0x7bc1f318
comma
l_int|0x0574d315
comma
l_int|0x2acc5a94
comma
l_int|0x54797a99
comma
l_int|0x7cffae5f
comma
l_int|0x024a8e52
comma
l_int|0x06852279
comma
l_int|0x78300274
comma
l_int|0x50b6d6b2
comma
l_int|0x2e03f6bf
comma
l_int|0x01bb7f3e
comma
l_int|0x7f0e5f33
comma
l_int|0x57888bf5
comma
l_int|0x293dabf8
comma
l_int|0x08f998f7
comma
l_int|0x764cb8fa
comma
l_int|0x5eca6c3c
comma
l_int|0x207f4c31
comma
l_int|0x0fc7c5b0
comma
l_int|0x7172e5bd
comma
l_int|0x59f4317b
comma
l_int|0x27411176
comma
l_int|0x1a7c5765
comma
l_int|0x64c97768
comma
l_int|0x4c4fa3ae
comma
l_int|0x32fa83a3
comma
l_int|0x1d420a22
comma
l_int|0x63f72a2f
comma
l_int|0x4b71fee9
comma
l_int|0x35c4dee4
comma
l_int|0x1400edeb
comma
l_int|0x6ab5cde6
comma
l_int|0x42331920
comma
l_int|0x3c86392d
comma
l_int|0x133eb0ac
comma
l_int|0x6d8b90a1
comma
l_int|0x450d4467
comma
l_int|0x3bb8646a
)brace
suffix:semicolon
DECL|struct|index_entry
r_struct
id|index_entry
(brace
DECL|member|ptr
r_const
r_int
r_char
op_star
id|ptr
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|unpacked_index_entry
r_struct
id|unpacked_index_entry
(brace
DECL|member|entry
r_struct
id|index_entry
id|entry
suffix:semicolon
DECL|member|next
r_struct
id|unpacked_index_entry
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|delta_index
r_struct
id|delta_index
(brace
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
DECL|member|src_buf
r_const
r_void
op_star
id|src_buf
suffix:semicolon
DECL|member|src_size
r_int
r_int
id|src_size
suffix:semicolon
DECL|member|hash_mask
r_int
r_int
id|hash_mask
suffix:semicolon
DECL|member|hash
r_struct
id|index_entry
op_star
id|hash
(braket
id|FLEX_ARRAY
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|create_delta_index
r_struct
id|delta_index
op_star
id|create_delta_index
c_func
(paren
r_const
r_void
op_star
id|buf
comma
r_int
r_int
id|bufsize
)paren
(brace
r_int
r_int
id|i
comma
id|hsize
comma
id|hmask
comma
id|entries
comma
id|prev_val
comma
op_star
id|hash_count
suffix:semicolon
r_const
r_int
r_char
op_star
id|data
comma
op_star
id|buffer
op_assign
id|buf
suffix:semicolon
r_struct
id|delta_index
op_star
id|index
suffix:semicolon
r_struct
id|unpacked_index_entry
op_star
id|entry
comma
op_star
op_star
id|hash
suffix:semicolon
r_struct
id|index_entry
op_star
id|packed_entry
comma
op_star
op_star
id|packed_hash
suffix:semicolon
r_void
op_star
id|mem
suffix:semicolon
r_int
r_int
id|memsize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
op_logical_neg
id|bufsize
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Determine index hash size.  Note that indexing skips the&n;&t;   first byte to allow for optimizing the Rabin&squot;s polynomial&n;&t;   initialization in create_delta(). */
id|entries
op_assign
(paren
id|bufsize
l_int|1
)paren
op_div
id|RABIN_WINDOW
suffix:semicolon
id|hsize
op_assign
id|entries
op_div
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
(paren
l_int|1u
op_lshift
id|i
)paren
OL
id|hsize
op_logical_and
id|i
OL
l_int|31
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
id|hsize
op_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|hmask
op_assign
id|hsize
l_int|1
suffix:semicolon
multiline_comment|/* allocate lookup index */
id|memsize
op_assign
r_sizeof
(paren
op_star
id|hash
)paren
op_star
id|hsize
op_plus
r_sizeof
(paren
op_star
id|entry
)paren
op_star
id|entries
suffix:semicolon
id|mem
op_assign
id|malloc
c_func
(paren
id|memsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
r_return
l_int|NULL
suffix:semicolon
id|hash
op_assign
id|mem
suffix:semicolon
id|mem
op_assign
id|hash
op_plus
id|hsize
suffix:semicolon
id|entry
op_assign
id|mem
suffix:semicolon
id|memset
c_func
(paren
id|hash
comma
l_int|0
comma
id|hsize
op_star
r_sizeof
(paren
op_star
id|hash
)paren
)paren
suffix:semicolon
multiline_comment|/* allocate an array to count hash entries */
id|hash_count
op_assign
id|calloc
c_func
(paren
id|hsize
comma
r_sizeof
(paren
op_star
id|hash_count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash_count
)paren
(brace
id|free
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* then populate the index */
id|prev_val
op_assign
op_complement
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|data
op_assign
id|buffer
op_plus
id|entries
op_star
id|RABIN_WINDOW
id|RABIN_WINDOW
suffix:semicolon
id|data
op_ge
id|buffer
suffix:semicolon
id|data
op_sub_assign
id|RABIN_WINDOW
)paren
(brace
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|RABIN_WINDOW
suffix:semicolon
id|i
op_increment
)paren
id|val
op_assign
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_or
id|data
(braket
id|i
)braket
)paren
op_xor
id|T
(braket
id|val
op_rshift
id|RABIN_SHIFT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
id|prev_val
)paren
(brace
multiline_comment|/* keep the lowest of consecutive identical blocks */
id|entry
(braket
l_int|1
)braket
dot
id|entry.ptr
op_assign
id|data
op_plus
id|RABIN_WINDOW
suffix:semicolon
op_decrement
id|entries
suffix:semicolon
)brace
r_else
(brace
id|prev_val
op_assign
id|val
suffix:semicolon
id|i
op_assign
id|val
op_amp
id|hmask
suffix:semicolon
id|entry-&gt;entry.ptr
op_assign
id|data
op_plus
id|RABIN_WINDOW
suffix:semicolon
id|entry-&gt;entry.val
op_assign
id|val
suffix:semicolon
id|entry-&gt;next
op_assign
id|hash
(braket
id|i
)braket
suffix:semicolon
id|hash
(braket
id|i
)braket
op_assign
id|entry
op_increment
suffix:semicolon
id|hash_count
(braket
id|i
)braket
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Determine a limit on the number of entries in the same hash&n;&t; * bucket.  This guards us against pathological data sets causing&n;&t; * really bad hash distribution with most entries in the same hash&n;&t; * bucket that would bring us to O(m*n) computing costs (m and n&n;&t; * corresponding to reference and target buffer sizes).&n;&t; *&n;&t; * Make sure none of the hash buckets has more entries than&n;&t; * we&squot;re willing to test.  Otherwise we cull the entry list&n;&t; * uniformly to still preserve a good repartition across&n;&t; * the reference buffer.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|hsize
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|acc
suffix:semicolon
r_if
c_cond
(paren
id|hash_count
(braket
id|i
)braket
op_le
id|HASH_LIMIT
)paren
r_continue
suffix:semicolon
multiline_comment|/* We leave exactly HASH_LIMIT entries in the bucket */
id|entries
op_sub_assign
id|hash_count
(braket
id|i
)braket
id|HASH_LIMIT
suffix:semicolon
id|entry
op_assign
id|hash
(braket
id|i
)braket
suffix:semicolon
id|acc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Assume that this loop is gone through exactly&n;&t;&t; * HASH_LIMIT times and is entered and left with&n;&t;&t; * acc==0.  So the first statement in the loop&n;&t;&t; * contributes (hash_count[i]-HASH_LIMIT)*HASH_LIMIT&n;&t;&t; * to the accumulator, and the inner loop consequently&n;&t;&t; * is run (hash_count[i]-HASH_LIMIT) times, removing&n;&t;&t; * one element from the list each time.  Since acc&n;&t;&t; * balances out to 0 at the final run, the inner loop&n;&t;&t; * body can&squot;t be left with entry==NULL.  So we indeed&n;&t;&t; * encounter entry==NULL in the outer loop only.&n;&t;&t; */
r_do
(brace
id|acc
op_add_assign
id|hash_count
(braket
id|i
)braket
id|HASH_LIMIT
suffix:semicolon
r_if
c_cond
(paren
id|acc
OG
l_int|0
)paren
(brace
r_struct
id|unpacked_index_entry
op_star
id|keep
op_assign
id|entry
suffix:semicolon
r_do
(brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
id|acc
op_sub_assign
id|HASH_LIMIT
suffix:semicolon
)brace
r_while
c_loop
(paren
id|acc
OG
l_int|0
)paren
suffix:semicolon
id|keep-&gt;next
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|entry
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|hash_count
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now create the packed index in array form&n;&t; * rather than linked lists.&n;&t; */
id|memsize
op_assign
r_sizeof
(paren
op_star
id|index
)paren
op_plus
r_sizeof
(paren
op_star
id|packed_hash
)paren
op_star
(paren
id|hsize
op_plus
l_int|1
)paren
op_plus
r_sizeof
(paren
op_star
id|packed_entry
)paren
op_star
id|entries
suffix:semicolon
id|mem
op_assign
id|malloc
c_func
(paren
id|memsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
(brace
id|free
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|index
op_assign
id|mem
suffix:semicolon
id|index-&gt;memsize
op_assign
id|memsize
suffix:semicolon
id|index-&gt;src_buf
op_assign
id|buf
suffix:semicolon
id|index-&gt;src_size
op_assign
id|bufsize
suffix:semicolon
id|index-&gt;hash_mask
op_assign
id|hmask
suffix:semicolon
id|mem
op_assign
id|index-&gt;hash
suffix:semicolon
id|packed_hash
op_assign
id|mem
suffix:semicolon
id|mem
op_assign
id|packed_hash
op_plus
(paren
id|hsize
op_plus
l_int|1
)paren
suffix:semicolon
id|packed_entry
op_assign
id|mem
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
id|hsize
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * Coalesce all entries belonging to one linked list&n;&t;&t; * into consecutive array entries.&n;&t;&t; */
id|packed_hash
(braket
id|i
)braket
op_assign
id|packed_entry
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|hash
(braket
id|i
)braket
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
op_star
id|packed_entry
op_increment
op_assign
id|entry-&gt;entry
suffix:semicolon
)brace
multiline_comment|/* Sentinel value to indicate the length of the last hash bucket */
id|packed_hash
(braket
id|hsize
)braket
op_assign
id|packed_entry
suffix:semicolon
m_assert
(paren
id|packed_entry
(paren
r_struct
id|index_entry
op_star
)paren
id|mem
op_eq
id|entries
)paren
suffix:semicolon
id|free
c_func
(paren
id|hash
)paren
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
DECL|function|free_delta_index
r_void
id|free_delta_index
c_func
(paren
r_struct
id|delta_index
op_star
id|index
)paren
(brace
id|free
c_func
(paren
id|index
)paren
suffix:semicolon
)brace
DECL|function|sizeof_delta_index
r_int
r_int
id|sizeof_delta_index
c_func
(paren
r_struct
id|delta_index
op_star
id|index
)paren
(brace
r_if
c_cond
(paren
id|index
)paren
r_return
id|index-&gt;memsize
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The maximum size for any opcode sequence, including the initial header&n; * plus Rabin window plus biggest copy.&n; */
DECL|macro|MAX_OP_SIZE
mdefine_line|#define MAX_OP_SIZE&t;(5 + 5 + 1 + RABIN_WINDOW + 7)
r_void
op_star
DECL|function|create_delta
id|create_delta
c_func
(paren
r_const
r_struct
id|delta_index
op_star
id|index
comma
r_const
r_void
op_star
id|trg_buf
comma
r_int
r_int
id|trg_size
comma
r_int
r_int
op_star
id|delta_size
comma
r_int
r_int
id|max_size
)paren
(brace
r_int
r_int
id|i
comma
id|outpos
comma
id|outsize
comma
id|moff
comma
id|msize
comma
id|val
suffix:semicolon
r_int
id|inscnt
suffix:semicolon
r_const
r_int
r_char
op_star
id|ref_data
comma
op_star
id|ref_top
comma
op_star
id|data
comma
op_star
id|top
suffix:semicolon
r_int
r_char
op_star
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trg_buf
op_logical_or
op_logical_neg
id|trg_size
)paren
r_return
l_int|NULL
suffix:semicolon
id|outpos
op_assign
l_int|0
suffix:semicolon
id|outsize
op_assign
l_int|8192
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outsize
op_ge
id|max_size
)paren
id|outsize
op_assign
id|max_size
op_plus
id|MAX_OP_SIZE
op_plus
l_int|1
suffix:semicolon
id|out
op_assign
id|malloc
c_func
(paren
id|outsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* store reference buffer size */
id|i
op_assign
id|index-&gt;src_size
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ge
l_int|0x80
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|i
op_or
l_int|0x80
suffix:semicolon
id|i
op_rshift_assign
l_int|7
suffix:semicolon
)brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|i
suffix:semicolon
multiline_comment|/* store target buffer size */
id|i
op_assign
id|trg_size
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ge
l_int|0x80
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|i
op_or
l_int|0x80
suffix:semicolon
id|i
op_rshift_assign
l_int|7
suffix:semicolon
)brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|i
suffix:semicolon
id|ref_data
op_assign
id|index-&gt;src_buf
suffix:semicolon
id|ref_top
op_assign
id|ref_data
op_plus
id|index-&gt;src_size
suffix:semicolon
id|data
op_assign
id|trg_buf
suffix:semicolon
id|top
op_assign
(paren
r_const
r_int
r_char
op_star
)paren
id|trg_buf
op_plus
id|trg_size
suffix:semicolon
id|outpos
op_increment
suffix:semicolon
id|val
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
id|RABIN_WINDOW
op_logical_and
id|data
OL
id|top
suffix:semicolon
id|i
op_increment
comma
id|data
op_increment
)paren
(brace
id|out
(braket
id|outpos
op_increment
)braket
op_assign
op_star
id|data
suffix:semicolon
id|val
op_assign
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_or
op_star
id|data
)paren
op_xor
id|T
(braket
id|val
op_rshift
id|RABIN_SHIFT
)braket
suffix:semicolon
)brace
id|inscnt
op_assign
id|i
suffix:semicolon
id|moff
op_assign
l_int|0
suffix:semicolon
id|msize
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
id|top
)paren
(brace
r_if
c_cond
(paren
id|msize
OL
l_int|4096
)paren
(brace
r_struct
id|index_entry
op_star
id|entry
suffix:semicolon
id|val
op_xor_assign
id|U
(braket
id|data
(braket
id|RABIN_WINDOW
)braket
)braket
suffix:semicolon
id|val
op_assign
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_or
op_star
id|data
)paren
op_xor
id|T
(braket
id|val
op_rshift
id|RABIN_SHIFT
)braket
suffix:semicolon
id|i
op_assign
id|val
op_amp
id|index-&gt;hash_mask
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
id|index-&gt;hash
(braket
id|i
)braket
suffix:semicolon
id|entry
OL
id|index-&gt;hash
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|entry
op_increment
)paren
(brace
r_const
r_int
r_char
op_star
id|ref
op_assign
id|entry-&gt;ptr
suffix:semicolon
r_const
r_int
r_char
op_star
id|src
op_assign
id|data
suffix:semicolon
r_int
r_int
id|ref_size
op_assign
id|ref_top
id|ref
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;val
op_ne
id|val
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ref_size
OG
id|top
id|src
)paren
id|ref_size
op_assign
id|top
id|src
suffix:semicolon
r_if
c_cond
(paren
id|ref_size
op_le
id|msize
)paren
r_break
suffix:semicolon
r_while
c_loop
(paren
id|ref_size
op_decrement
op_logical_and
op_star
id|src
op_increment
op_eq
op_star
id|ref
)paren
id|ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|msize
OL
id|ref
id|entry-&gt;ptr
)paren
(brace
multiline_comment|/* this is our best match so far */
id|msize
op_assign
id|ref
id|entry-&gt;ptr
suffix:semicolon
id|moff
op_assign
id|entry-&gt;ptr
id|ref_data
suffix:semicolon
r_if
c_cond
(paren
id|msize
op_ge
l_int|4096
)paren
multiline_comment|/* good enough */
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|msize
OL
l_int|4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inscnt
)paren
id|outpos
op_increment
suffix:semicolon
id|out
(braket
id|outpos
op_increment
)braket
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|inscnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|inscnt
op_eq
l_int|0x7f
)paren
(brace
id|out
(braket
id|outpos
id|inscnt
l_int|1
)braket
op_assign
id|inscnt
suffix:semicolon
id|inscnt
op_assign
l_int|0
suffix:semicolon
)brace
id|msize
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|left
suffix:semicolon
r_int
r_char
op_star
id|op
suffix:semicolon
r_if
c_cond
(paren
id|inscnt
)paren
(brace
r_while
c_loop
(paren
id|moff
op_logical_and
id|ref_data
(braket
id|moff
op_minus
l_int|1
)braket
op_eq
id|data
(braket
l_int|1
)braket
)paren
(brace
multiline_comment|/* we can match one byte back */
id|msize
op_increment
suffix:semicolon
id|moff
op_decrement
suffix:semicolon
id|data
op_decrement
suffix:semicolon
id|outpos
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|inscnt
)paren
r_continue
suffix:semicolon
id|outpos
op_decrement
suffix:semicolon
multiline_comment|/* remove count slot */
id|inscnt
op_decrement
suffix:semicolon
multiline_comment|/* make it -1 */
r_break
suffix:semicolon
)brace
id|out
(braket
id|outpos
id|inscnt
l_int|1
)braket
op_assign
id|inscnt
suffix:semicolon
id|inscnt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* A copy op is currently limited to 64KB (pack v2) */
id|left
op_assign
(paren
id|msize
OL
l_int|0x10000
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|msize
l_int|0x10000
)paren
suffix:semicolon
id|msize
op_sub_assign
id|left
suffix:semicolon
id|op
op_assign
id|out
op_plus
id|outpos
op_increment
suffix:semicolon
id|i
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0x000000ff
)paren
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
op_rshift
l_int|0
comma
id|i
op_or_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0x0000ff00
)paren
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
op_rshift
l_int|8
comma
id|i
op_or_assign
l_int|0x02
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0x00ff0000
)paren
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
op_rshift
l_int|16
comma
id|i
op_or_assign
l_int|0x04
suffix:semicolon
r_if
c_cond
(paren
id|moff
op_amp
l_int|0xff000000
)paren
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|moff
op_rshift
l_int|24
comma
id|i
op_or_assign
l_int|0x08
suffix:semicolon
r_if
c_cond
(paren
id|msize
op_amp
l_int|0x00ff
)paren
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|msize
op_rshift
l_int|0
comma
id|i
op_or_assign
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|msize
op_amp
l_int|0xff00
)paren
id|out
(braket
id|outpos
op_increment
)braket
op_assign
id|msize
op_rshift
l_int|8
comma
id|i
op_or_assign
l_int|0x20
suffix:semicolon
op_star
id|op
op_assign
id|i
suffix:semicolon
id|data
op_add_assign
id|msize
suffix:semicolon
id|moff
op_add_assign
id|msize
suffix:semicolon
id|msize
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|msize
OL
l_int|4096
)paren
(brace
r_int
id|j
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|RABIN_WINDOW
suffix:semicolon
id|j
OL
l_int|0
suffix:semicolon
id|j
op_increment
)paren
id|val
op_assign
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_or
id|data
(braket
id|j
)braket
)paren
op_xor
id|T
(braket
id|val
op_rshift
id|RABIN_SHIFT
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|outpos
op_ge
id|outsize
id|MAX_OP_SIZE
)paren
(brace
r_void
op_star
id|tmp
op_assign
id|out
suffix:semicolon
id|outsize
op_assign
id|outsize
op_star
l_int|3
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outsize
op_ge
id|max_size
)paren
id|outsize
op_assign
id|max_size
op_plus
id|MAX_OP_SIZE
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outpos
OG
id|max_size
)paren
r_break
suffix:semicolon
id|out
op_assign
id|realloc
c_func
(paren
id|out
comma
id|outsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|out
)paren
(brace
id|free
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|inscnt
)paren
id|out
(braket
id|outpos
id|inscnt
l_int|1
)braket
op_assign
id|inscnt
suffix:semicolon
r_if
c_cond
(paren
id|max_size
op_logical_and
id|outpos
OG
id|max_size
)paren
(brace
id|free
c_func
(paren
id|out
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|delta_size
op_assign
id|outpos
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
eof
